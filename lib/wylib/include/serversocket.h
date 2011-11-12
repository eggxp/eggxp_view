//---------------------------------------------------------------------------

#ifndef serversocketH
#define serversocketH
#include <vcl.h>
#include <winsock.h>
#include "CommFunc.h"
#define ID_SOCKSERVER_EVENT_MSG		WM_USER + 1010
//异步AsyncSelect服务器
typedef void __fastcall (__closure *TOnServerError)(SOCKET   ClientSocket,int ErrorCode,String ErrorInfo);
typedef void __fastcall (__closure *TOnData)(SOCKET   ClientSocket,char * Buf,int Len);
typedef void __fastcall (__closure *TOnSocketEvent)(SOCKET ClientSocket);

enum CESocketEvent{seCONNECT=0,seDISCONNECT,seSEND,seRECV,seERROR};
class CAsyncServerSocket
{
private:
  HINSTANCE    m_hInstance;
  SOCKET       m_ListenSocket;
  WNDPROC      m_pfOrgWndProc;
protected:
  bool          m_InitSuccess;
  bool          m_Connected;
  WORD          m_ServerPort;
  HWND          m_HWnd;
  void          Init();
  String        LastError;
  void         ThrowError(SOCKET   ClientSocket,int ErrorCode,const String &ErrorInfo);
  void         HookWindowWndProc();
  void         UnHookWindowWndProc();
  void __fastcall OnNetWindowMessage(Messages::TMessage &Message);
  bool         CreateSocketWindow();
  virtual void  OnSocketEvent(CESocketEvent Event,SOCKET SocketID);
public:
  __fastcall CAsyncServerSocket(HINSTANCE Instance);
  virtual __fastcall ~CAsyncServerSocket();
  bool        Start(WORD ListenPort);
  virtual bool        Stop();
  bool        IsActive(){return m_Connected;}
  SOCKET      GetSocketID(){return m_ListenSocket;}
  TOnServerError    OnError;            //错误事件
  TOnSocketEvent  OnRecv;               //FD_READ 有数据到达,可以接收时
  TOnSocketEvent  OnSend;             //FD_WRITE事件,服务器发送缓冲区准备就绪 ,可以发送时
  TOnSocketEvent  OnClientConnect;      //FD_ACCEPT连接请求同意以后
  TOnSocketEvent  OnClientDisconnect;   //FD_CLOSE  客户端关闭连接时
  String      GetIP(SOCKET Socket);
  String      GetLastErrorStr(){return LastError;}
  WORD        ListenPort(){return m_ServerPort;}
};



//---------------------------------------------------------------------------
#endif
