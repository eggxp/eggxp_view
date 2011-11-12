//---------------------------------------------------------------------------
//更新记录

#ifndef srvthreadH
#define srvthreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <ScktComp.hpp>
//注意
//线程池每个线程的堆栈大小只有32K
class CServerSocket;
enum ThreadState{tsWAIT,tsCLIENT_CONNECT,tsSERVERCONNECT,tsPROCESS_CLIENT,tsPROCESS_SERVER,tsCLOSE,tsCREATE_FAIL};
String GetThreadStateName(ThreadState StateFlag);
//---------------------------------------------------------------------------
class CServerThread
{
private:
	   int				m_Index;        //线程池当中的编号
	   SOCKET 			m_ClientSocket;
	   CServerSocket  * m_ServerSocket;
       bool             m_ClientConnect; //客户端是否连接中
	   String           m_ClientIP;
	   String           m_LastError;
	   bool				m_Terminated; //是否需要结束线程
	   HANDLE 			m_Handle;  // 线程句柄
	   DWORD			m_ThreadID;      //线程ID
	   DWORD  			m_StackSize;
	   char			   * lpRecvBuffer;    //接收缓冲区
	   char			   * lpSendBuffer;	  //发送缓冲区
	   DWORD			m_RecvBufSize; //实际分配的接收缓冲区大小
	   DWORD			m_SendBufSize; //实际分配的发送缓冲区大小
protected:
		void __fastcall Execute();
		static DWORD WINAPI ThreadProc(LPVOID lpParameter);
public:
	   void * 			lpUserData; //用户自定义数据
	   ThreadState      State;

	   int    RecvLen();
       void   __fastcall Log();
	   void   __fastcall ErrLog();
public:
		__fastcall CServerThread(bool CreateSuspended,CServerSocket * ServerSocket,DWORD StackSize,int Index);
		__fastcall ~CServerThread();
        int Recv(char * lpBuffer,int Len);
        int Send(char * lpBuffer,int Len);
        void CloseSocket();
        void ShowLog(String LogStr);
        void ShowErrLog(String LogStr);
        String GetClientIP(){return m_ClientIP;}
		SOCKET GetSocket(){return m_ClientSocket;}
		void   Terminate(){m_Terminated=true;}//结束线程运行
		DWORD  GetThreadID(){return m_ThreadID;}
		HANDLE  GetThreadHandle(){return  m_Handle;}
		String  LastError(){return m_LastError;}
		char *  RecvBufPtr(){return lpRecvBuffer;} //获取接收数据缓冲区指针
		char *  SendBufPtr(){return lpSendBuffer;} //获取发送数据缓冲区指针
		DWORD   RecvBufSize(){return m_RecvBufSize;}  //获取实际分配的接收缓冲区大小
		DWORD   SendBufSize(){return m_SendBufSize;}//获取实际分配的发送缓冲区大小
		String  GetState();
		int		GetIndex(){return  m_Index;}  //获取该线程对象在线程池当中的编号
};
//---------------------------------------------------------------------------
#endif
