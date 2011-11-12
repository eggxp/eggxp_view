//---------------------------------------------------------------------------

#ifndef clientsocketH
#define clientsocketH
#include <vcl.h>
#include <winsock.h>
#define ID_SOCKCLIENT_EVENT_MSG		WM_USER + 1000
/***************************************************************************
 *  文 件 名：clientsocket.cpp
 *  版    本：1.00.0                                                  
 *  作    者：Bluely
 *  单元功能： 基于WSAAsyncSelect模式的Socket封装类，适用于客户端
 *  使用举例：见测试demo单元
 *
 *  更新记录：
 *  2005-03-21    第一个版本
 *  2005-03-22    在窗口消息回调函数中判断Message.WParam != m_ClientSocketID判断,防止同一个窗口不同的Client Socket消息混瑶
 *  2005-03-23    修正Disconnect函数没有判断断开状态可能导致用户无穷递归的问题
                  修正析构函数析构的时候没有断开用户通知回调函数,可能导致函数指针调用失败

    问题:
      使用父窗口模式可能会导致一些错误,替换父窗口的消息处理函数,假如有其他类(包括CClientSocket自己的另一个实例)也进行了这项
      动作,可能会导致消息处理函数混乱失效

 *
 ***************************************************************************/
// WSAAsyncSelect模式通过窗口消息通知Socket事件
//所以此类拥有两个构造函数
//  __fastcall CClientSocket(HINSTANCE Instance);   CClientSocket自己创建窗口
//  __fastcall CClientSocket(TForm *ParentForm);    使用已有的VCL窗口,不创建自己的窗口
//---------------------------------------------------------------------------
class CClientSocket;
typedef void __fastcall (__closure *TOnConnect)(CClientSocket  *ClientSocket);
typedef void __fastcall (__closure *TOnDisconnect)(CClientSocket  *ClientSocket,bool ServerDisconnect=false);
typedef void __fastcall (__closure *TOnRecv)(CClientSocket  *ClientSocket,SOCKET SocketID);
typedef void __fastcall (__closure *TOnSend)(CClientSocket  *ClientSocket,SOCKET SocketID);
typedef void __fastcall (__closure *TOnError)(CClientSocket  *ClientSocket,int ErrorCode,char *ErrorInfo);
class CClientSocket
{
private:
   bool         m_Connected;
   SOCKET       m_ClientSocketID;
   HWND         m_HWnd;
   HINSTANCE    m_hInstance;
   bool         m_InitSuccess;
   WNDPROC      m_pfOrgWndProc;
   TWndMethod   m_pfFormUserWndProc;
   WSADATA      wsaData;
   TForm *      m_ParentForm;
   bool         m_ParentWindowMode; //是使用外来窗口模式
   void         Init();
   void         HookWindowWndProc();
   void         UnHookWindowWndProc();
   bool         CreateSocketWindow();
   void         ThrowError(int ErrorCode);
   void         CloseSocket();
protected:
   char          m_ServerIP[256];
   WORD          m_ServerPort;
   //BCB
   void __fastcall OnNetWindowMessage(Messages::TMessage &Message);
   //VC
   static LRESULT CALLBACK DefWindowMessageProc(HWND WinHwnd,UINT Msg, WPARAM wParam, LPARAM lParam);
public:
  CHAR          LastError[256];  //最后的错误信息
  //事件回调函数指针
  TOnConnect    OnConnect;
  TOnDisconnect OnDisconnect;
  TOnRecv       OnRecv;
  TOnSend       OnSend;         //数据缓冲区准备好可以发送
  TOnError      OnError;
  DWORD        UserData;  //用户自定义数据
public:
  //构造和析构
  __fastcall            CClientSocket(HINSTANCE Instance);
  __fastcall            CClientSocket(TForm *ParentForm);
  virtual __fastcall    ~CClientSocket();

  //网络操作函数
  bool                  Connect();                                 //连接
  bool                  Disconnect(bool ServerDisconnect=false);   //断开连接
  int                   ReceiveLength();                           //当前接收封包的长度
  int                   RecvBuf(char * Buf,int Len);              //接收数据,在OnRecv里面调用
  int                   SendBuf(char * Buf,int Len);              //发送数据
  __inline bool         IsConnected(){return (m_Connected && m_ClientSocketID != INVALID_SOCKET);}        //判断当前是否连接
  __inline              SOCKET SocketID(){return m_ClientSocketID;} //获取当前Socket
  //设置和设置读取函数
  void                  SetServerIP(char * IP);
  void                  SetServerPort(WORD Port);
  char *                GetServerIP(){return m_ServerIP;}
  __inline WORD         GetServerPort(){return m_ServerPort;}

};

#endif
