//---------------------------------------------------------------------------

#ifndef udpsocketH
#define udpsocketH
#include <vcl.h>
#include <winsock.h>
#include "CommFunc.h"
//udp socket对象,即是客户端又是服务器端
typedef void __fastcall (__closure *TOnUDPError)(int ErrorCode,const String &ErrorInfo);
typedef void __fastcall (__closure *TOnUDPRead)(char * SenderIP,char * Data,int Len);
class  CUDPSocket
{
private:
   WORD 		Port;
   WSADATA 		wsd;
   SOCKET  		ServerSocket;
   SOCKET		ClientSocket;
   SOCKADDR_IN  Sender;
   SOCKADDR_IN  Local;
   bool			CreateSocket();
   bool			InitClientSocket();
   bool			Active;
   int			SYSRecvBuffer; //系统接收缓冲区单位KB
protected:
   void ShowError(int ErrorCode,const String &Info);
   static DWORD WINAPI RecvThreadFunc(LPVOID Parameter); //接收封包线程函数
public:
   CUDPSocket();
   ~CUDPSocket();
   void  Open();
   void	 Stop();
   bool  IsActive(){return Active;}
   void	 SetPort(WORD _Port){Port = _Port;}
   int __fastcall SendData(String DesIP,WORD DesPort,char * Data,int Len);
   void	 SetRecvBufSize(int KBSize){SYSRecvBuffer = KBSize*1024;} //系统接收缓冲区单位KB
   //回调通知接口
   TOnUDPError OnError;
   TOnUDPRead  OnRead;  //OnRead是在线程中运行,请注意代码的线程安全保护

};
//---------------------------------------------------------------------------
#endif
