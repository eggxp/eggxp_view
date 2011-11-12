//---------------------------------------------------------------------------


#pragma hdrstop

#include "serversocket.h"
#include "CommFunc.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
#define HIDE_WINDOW_CLASS   "CServerSocketWindow"
#define HIDE_WINDOW_CAPTION "CServerSocketWindow"
//------------------------------------------------------------------------------
__fastcall CAsyncServerSocket::CAsyncServerSocket(HINSTANCE Instance)
{
   Init();
   m_hInstance = Instance;
   m_InitSuccess = CreateSocketWindow();
}

//------------------------------------------------------------------------------
__fastcall CAsyncServerSocket::~CAsyncServerSocket()
{
   Stop();
   WSACleanup();
}
//---------------------------------------------------------------------------
void CAsyncServerSocket::Init()
{
    WSADATA      wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    m_Connected = false;
    m_ListenSocket = INVALID_SOCKET;
    m_ServerPort = 0;
    m_HWnd = NULL;
    m_hInstance        = NULL;
    m_pfOrgWndProc = NULL;
    OnError = NULL;
    OnRecv =  NULL;
    OnSend = NULL;
    OnClientConnect = NULL;
    OnClientDisconnect = NULL;
}
//------------------------------------------------------------------------------
bool CAsyncServerSocket::CreateSocketWindow()
{
    WNDCLASSEX  wc;
    if(!GetClassInfoEx(m_hInstance, HIDE_WINDOW_CLASS, &wc))    //如果获取类信息失败,证明还没注册窗口类
    {
        wc.cbSize = sizeof(wc);
        wc.lpszClassName = HIDE_WINDOW_CLASS;
        wc.lpfnWndProc = &DefWindowProc;
        wc.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
        wc.hInstance = m_hInstance;
        wc.hIcon = NULL;
        wc.hIconSm = NULL;
        wc.hCursor = NULL;                                      //LoadCursor(m_hInstance, IDC_ARROW);
        wc.hbrBackground = (HBRUSH) (GRAY_BRUSH);               //(COLOR_WINDOW + 1);
        wc.lpszMenuName = NULL;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        if(RegisterClassEx(&wc) == 0)                           //注册窗口类
        {
            int ClassError = GetLastError();
            LastError = FormatStr("RegisterClassEx Fail,ErrorCode:%d",
                     ClassError);
            ThrowError(INVALID_SOCKET,ClassError,LastError);
        }
    }

    DWORD   dwStyle = WS_POPUPWINDOW /*WS_OVERLAPPEDWINDOW*/ &~WS_MAXIMIZEBOX;
    m_HWnd = CreateWindowEx(WS_EX_TOOLWINDOW,
                            HIDE_WINDOW_CLASS,
                            HIDE_WINDOW_CAPTION,
                            dwStyle,
                            0,
                            0,
                            0,
                            0,
                            NULL,
                            NULL,
                            m_hInstance,
                            NULL);

    if(m_HWnd == NULL)
    {
        LastError = FormatStr("Creare Window Fail,ErrorCode:%d", GetLastError());
        ThrowError(INVALID_SOCKET,GetLastError(),LastError);
        return false;
    }
    else
    {
        HookWindowWndProc();
        return true;
    }
}
//------------------------------------------------------------------------------
void CAsyncServerSocket::ThrowError(SOCKET   ClientSocket,int ErrorCode,const String &ErrorInfo)
{
    if (OnError)
    {
      OnError(ClientSocket,ErrorCode,ErrorInfo);
    }
}
//---------------------------------------------------------------------------
void CAsyncServerSocket::HookWindowWndProc()
{
    //把消息窗口处理函数替换成类成员函数
    m_pfOrgWndProc = (WNDPROC)GetWindowLong(m_HWnd, GWL_WNDPROC);
    SetWindowLong(m_HWnd,
                  GWL_WNDPROC,
                  LONG(MakeObjectInstance(&OnNetWindowMessage)));
}
//---------------------------------------------------------------------------
void CAsyncServerSocket::UnHookWindowWndProc()
{
    void    *lpWindowProc = (void *)GetWindowLong(m_HWnd, GWL_WNDPROC);
    if(lpWindowProc != (void *) m_pfOrgWndProc)
    {
        FreeObjectInstance(lpWindowProc);
        SetWindowLong(m_HWnd,
                      GWL_WNDPROC,
                      LONG(m_pfOrgWndProc));
    }
}
//------------------------------------------------------------------------------
void __fastcall CAsyncServerSocket::OnNetWindowMessage(Messages::TMessage  &Message)
{
    try
    {
        if(Message.Msg == ID_SOCKSERVER_EVENT_MSG)
        {
            SOCKET  CurSocket = (SOCKET) Message.WParam;
            if(WSAGETSELECTERROR(Message.LParam))   //检查错误
            {
                LastError =  SysErrorMessage(WSAGETSELECTERROR(Message.LParam));
                ThrowError(CurSocket,WSAGETSELECTERROR(Message.LParam),LastError);
                return;
            }


            switch(WSAGETSELECTEVENT(Message.LParam))
            {
                case FD_ACCEPT:
                    {

                        //同意客户端连接
                        SOCKET  AcceptSocket = accept(CurSocket, NULL, NULL);
                        if(INVALID_SOCKET == AcceptSocket)
                        {
                            LastError = FormatStr("accept  Fail,ErrorCode:%d",
                                                  GetLastError());
                            ThrowError(AcceptSocket,GetLastError(),LastError);
                            return;
                        }
                        //设置关闭模式为从容关闭(等到数据全部发送完毕再关闭)
                        //linger LingerSet;
                        //int    lingerlen = sizeof(linger);
                        //LingerSet.l_onoff  = 1;
                        //LingerSet.l_linger = 0; //延时1秒
                        //setsockopt(AcceptSocket,SOL_SOCKET,SO_LINGER,(char *)&LingerSet,lingerlen);
                        //设置客户端连接通讯模式为异步方式
                        if(WSAAsyncSelect(AcceptSocket,
                                          m_HWnd,
                                          ID_SOCKSERVER_EVENT_MSG,
                                          FD_READ | FD_WRITE | FD_CLOSE) == SOCKET_ERROR)
                        {
                            LastError = FormatStr("accept WSAAsyncSelect Fail,ErrorCode:%d",
                                                  GetLastError());
                            ThrowError(AcceptSocket,WSAGetLastError(),LastError);
                            closesocket(AcceptSocket);
                            return;
                        }

                        //通知使用者
                        if(OnClientConnect)
                        {
                            OnClientConnect(AcceptSocket);
                        }
                        break;
                    }

                case FD_CLOSE:
                    {
                        if(OnClientDisconnect)
                        {
                            OnClientDisconnect(CurSocket);
                        }

                        closesocket(CurSocket);
                        break;
                    }

                case FD_READ:
                    {
                        if (!m_Connected)   //服务器已经关闭了
                        {
                          closesocket(CurSocket);
                          return;
                        }
                        if(OnRecv)                  //不处理接收数据,数据交给使用者来接收
                        {
                            OnRecv(CurSocket);
                        }

                        break;
                    }
                case FD_WRITE:
                    {
                        if (!m_Connected)   //服务器已经关闭了
                        {
                          closesocket(CurSocket);
                          return;
                        }
                        if(OnSend)                  //不处理接收数据,数据交给使用者来接收
                        {
                            OnSend(CurSocket);
                        }

                        break;
                    }
            }
        }
    }

    catch(...)
    {
        LastError = FormatStr("OnNetWindowMessage Error,ErrorCode:%d",
                              GetLastError());
        ThrowError(INVALID_SOCKET,WSAGetLastError(),LastError);
    }

}
//------------------------------------------------------------------------------
bool CAsyncServerSocket::Start(WORD    ListenPort)
{
    if (m_Connected)
    {
        LastError = "server already active.";
        ThrowError(INVALID_SOCKET,WSAGetLastError(),LastError);
        return false;
    }
    m_ServerPort = ListenPort;
    m_ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_IP);
    if(m_ListenSocket == INVALID_SOCKET)
    {
        LastError = FormatStr("socket() generated error %d\n", WSAGetLastError());
        ThrowError(INVALID_SOCKET,WSAGetLastError(),LastError);
        return false;
    }

    SOCKADDR_IN sockAddr;
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(m_ServerPort);
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(m_ListenSocket,
            (const sockaddr *) &sockAddr,
            sizeof(sockAddr)) == SOCKET_ERROR)
    {
        LastError = FormatStr("call the bind() fail,error = %d(%s)",
                                  WSAGetLastError(),
                                  SysErrorMessage(WSAGetLastError()));
        ThrowError(m_ListenSocket,WSAGetLastError(),LastError);
        closesocket(m_ListenSocket);
        return false;
    }
    if (WSAAsyncSelect(m_ListenSocket,m_HWnd,ID_SOCKSERVER_EVENT_MSG,FD_ACCEPT | FD_CLOSE)== SOCKET_ERROR)
    {
        LastError = SysErrorMessage(WSAGetLastError());
        ThrowError(m_ListenSocket,WSAGetLastError(),LastError);
        closesocket(m_ListenSocket);
        return false;
    }
    if(listen(m_ListenSocket, 10) == SOCKET_ERROR)
    {
        LastError = FormatStr("call the listen() fail,error = %d(%s)",
                                   WSAGetLastError(),SysErrorMessage(WSAGetLastError()));
        closesocket(m_ListenSocket);
        return false;
    }
    m_Connected = true;
    return true;
}
//------------------------------------------------------------------------------
bool   CAsyncServerSocket::Stop()
{
    if (!m_Connected || m_ListenSocket == INVALID_SOCKET)
    {
        return false;
    }
    closesocket(m_ListenSocket);
    m_Connected = false;
    return true;
}
//------------------------------------------------------------------------------
String  CAsyncServerSocket::GetIP(SOCKET Socket)
{
     sockaddr_in ClientSocketAddr;
     int         AddLen = sizeof(sockaddr_in);
     getpeername(Socket,(sockaddr *)&ClientSocketAddr,&AddLen);
     return  inet_ntoa(ClientSocketAddr.sin_addr);
}
