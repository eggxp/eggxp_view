//---------------------------------------------------------------------------
//更新记录

#ifndef srvthreadH
#define srvthreadH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <ScktComp.hpp>
class CServerSocket;
enum ThreadState{tsWAIT,tsCLIENT_CONNECT,tsSERVERCONNECT,tsPROCESS_CLIENT,tsPROCESS_SERVER,tsCLOSE};
//---------------------------------------------------------------------------
class CServerThread : public TThread
{            
private:
       SOCKET m_ClientSocket;
       CServerSocket  * m_ServerSocket;
       bool             m_ClientConnect; //客户端是否连接中
       String           m_ClientIP;
       String           m_LastError;
protected:
        void __fastcall Execute();
public:
       void * lpUserData; //用户自定义数据
       int    State;
       int    RecvLen();
       void   __fastcall Log();
       void   __fastcall ErrLog();
public:
        __fastcall CServerThread(bool CreateSuspended,CServerSocket * ServerSocket);
        int Recv(char * lpBuffer,int Len);
        int Send(char * lpBuffer,int Len);
        void CloseSocket();
        void ShowLog(String LogStr);
        void ShowErrLog(String LogStr);
        String GetClientIP(){return m_ClientIP;}
        SOCKET GetSocket(){return m_ClientSocket;}
};
//---------------------------------------------------------------------------
#endif
