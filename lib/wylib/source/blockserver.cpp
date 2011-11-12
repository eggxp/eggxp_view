//---------------------------------------------------------------------------


#pragma hdrstop

#include "blockserver.h"
#include "CommFunc.h"
#include "srvthread.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall CServerSocket::CServerSocket()
{
    m_ThreadPool = new AList < CServerThread > (true, 5);
    m_LogList = new TStringList;
    m_GlobalLock = new TCriticalSection();
    Port = 0;
    m_ListenSocket = INVALID_SOCKET;
    m_IsActive = false;
    OnThreadEnd = NULL;
    OnThreadClientAccept = NULL;
    OnThreadBegin = NULL;
    OnOutputLog = NULL;
    OnOutputErrorLog = NULL;
    CanShowLog = false;
    WORD    wVersionRequested;
    WSADATA wsaData;
    int     err;
    RecvTimeOut = 30000;
    wVersionRequested = MAKEWORD(2, 0);

    err = WSAStartup(wVersionRequested, &wsaData);
    if(err != 0)
    {
        m_LastErrorStr ="WSAStartup Error";
        return;
    }

}
//---------------------------------------------------------------------------
__fastcall CServerSocket::~CServerSocket()
{
        delete m_GlobalLock;
        FreeThreadPool();
        delete m_ThreadPool;
        delete m_LogList;
        WSACleanup();
}
//---------------------------------------------------------------------------
void       CServerSocket::SetThreadPool(int ThreadNumber)
{
     for(int i=0;i<ThreadNumber;i++)
     {
        m_ThreadPool->Add(new CServerThread(false,this));
     }

}
//---------------------------------------------------------------------------
void       CServerSocket::FreeThreadPool()
{
     CServerThread * lpCurrentThread;
     //关闭所有线程
     for(int i=0;i<m_ThreadPool->Count();i++)
     {
       lpCurrentThread =  m_ThreadPool->At(i);
       lpCurrentThread->CloseSocket();
       lpCurrentThread->Terminate();
     }
     //释放线程池
     m_ThreadPool->Clear();
}
//---------------------------------------------------------------------------
bool CServerSocket::Start(int PoolSize)
{
    if(m_IsActive)
    {
        m_LastErrorStr = "server already active.";
        return false;
    };
    if(PoolSize < 1)
    {
        m_LastErrorStr = "PooSize must be great 1";
        return false;
    }

    sockaddr_in SocketAddr;
    m_ListenSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_IP);
    if(m_ListenSocket == INVALID_SOCKET)
    {
        m_LastErrorStr = FormatStr("call the socket() fail,error = %d(%s)",
                                   WSAGetLastError(),SysErrorMessage(WSAGetLastError()));
        return false;
    }

    SocketAddr.sin_family = PF_INET;
    SocketAddr.sin_port = htons(Port);
    SocketAddr.sin_addr.s_addr = INADDR_ANY;
    if(bind(m_ListenSocket,(const sockaddr *)&SocketAddr, sizeof(SocketAddr)) == SOCKET_ERROR)
    {
        m_LastErrorStr = FormatStr("call the bind() fail,error = %d(%s)",
                                   WSAGetLastError(),SysErrorMessage(WSAGetLastError()));
        closesocket(m_ListenSocket);
        return false;
    }

    if(listen(m_ListenSocket, 10) == SOCKET_ERROR)
    {
        m_LastErrorStr = FormatStr("call the listen() fail,error = %d(%s)",
                                   WSAGetLastError(),SysErrorMessage(WSAGetLastError()));
        closesocket(m_ListenSocket);
        return false;
    }

    SetThreadPool(PoolSize);
    m_IsActive = true;
    return true;
}
//---------------------------------------------------------------------------
bool       CServerSocket::Stop()
{
    if(!m_IsActive)
    {
        m_LastErrorStr = "server not active.";
        return false;
    };
    //关闭监听端口
    if (m_ListenSocket != INVALID_SOCKET)
    {
      closesocket(m_ListenSocket);
    };
    //释放线程池
    FreeThreadPool();
    m_IsActive = false;
    return true;
}
//------------------------------------------------------------------------------
SOCKET  CServerSocket::SafeAccept(struct sockaddr FAR* addr,int FAR* addrlen)
{
  SOCKET AcceptSocket;
  m_GlobalLock->Enter();   //加锁抢占客户端链接请求
  AcceptSocket = accept(m_ListenSocket,addr,addrlen);
  m_GlobalLock->Leave();
  setsockopt(AcceptSocket,SOL_SOCKET,SO_RCVTIMEO,(const char *)&RecvTimeOut,sizeof(RecvTimeOut));
  return AcceptSocket;
}
//------------------------------------------------------------------------------
bool CServerSocket::GetThreadInfo(int ThreadIndex,ThreadInfo * ThreadInfoOut)
{
     CServerThread * lpCurrentThread;
     //关闭所有线程
     if(ThreadIndex<m_ThreadPool->Count())
     {
       lpCurrentThread =  m_ThreadPool->At(ThreadIndex);
       ThreadInfoOut->ThreadID = lpCurrentThread->ThreadID;
       ThreadInfoOut->State    = lpCurrentThread->State;
       ThreadInfoOut->ClientSocket =  lpCurrentThread->GetSocket();
       ThreadInfoOut->ClientIP =      lpCurrentThread->GetClientIP();
       ThreadInfoOut->UserData =     lpCurrentThread->lpUserData;
       return true;
     }
     return false;
}
//------------------------------------------------------------------------------
void  CServerSocket::ShowLog(String Log)
{
   if (OnOutputLog)
   {
     OnOutputLog(Log);
   }
}
//------------------------------------------------------------------------------
void  CServerSocket::ShowErrorLog(String Log)
{
   if (OnOutputErrorLog)
   {
     OnOutputErrorLog(Log);
   }
}
