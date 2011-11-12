//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "commfunc.h"
#include "srvthread.h"
#include "blockserver.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------
DWORD WINAPI CServerThread::ThreadProc(LPVOID lpParameter)
{
	CServerThread * lpOwnThreadObj = (CServerThread *)lpParameter;
	lpOwnThreadObj->Execute();
	return 0;
}
//---------------------------------------------------------------------------
__fastcall CServerThread::CServerThread(bool CreateSuspended,CServerSocket * ServerSocket,DWORD StackSize,int Index)

{
     m_ClientSocket = INVALID_SOCKET;
	 m_ServerSocket = ServerSocket;
	 m_Index	= Index;
	 m_RecvBufSize =   m_ServerSocket->RecvBufSize;
	 m_SendBufSize =   m_ServerSocket->SendBufSize;
	 lpRecvBuffer = new char[m_RecvBufSize];
	 lpSendBuffer = new char[m_SendBufSize];
	 m_Terminated = false;
	 lpUserData     = NULL;
	 m_ThreadID=0;
	 if (CreateSuspended)
	 {
		 m_Handle	 = CreateThread(NULL,0,ThreadProc,this, CREATE_SUSPENDED,&m_ThreadID);
	 }
	 else
	 {
		 m_Handle	 = CreateThread(NULL,StackSize,ThreadProc,this, STACK_SIZE_PARAM_IS_A_RESERVATION,&m_ThreadID);
	 }
	 if (m_Handle==NULL)
	 {
		  m_LastError = SysErrorMessage(GetLastError());
		  m_ThreadID=0;
		  State = tsCREATE_FAIL;
		  return;
	 }
}
//------------------------------------------------------------------------------
__fastcall CServerThread::~CServerThread()
{
	  delete []lpRecvBuffer;
	  delete []lpSendBuffer;
}
//------------------------------------------------------------------------------
void   __fastcall CServerThread::Log()
{
   m_ServerSocket->ShowLog(m_LastError);
}
//------------------------------------------------------------------------------
void   __fastcall CServerThread::ErrLog()
{
  m_ServerSocket->ShowErrorLog(m_LastError);
}
//------------------------------------------------------------------------------
void CServerThread::ShowLog(String LogStr)
{
		m_LastError = LogStr;
		//this->Synchronize((TThreadMethod)&Log);
}
//------------------------------------------------------------------------------
void CServerThread::ShowErrLog(String LogStr)
{
        m_LastError = LogStr;
		//this->Synchronize((TThreadMethod)&ErrLog);
}
//---------------------------------------------------------------------------
void __fastcall CServerThread::Execute()
{
    try
    {
        if(m_ServerSocket->OnThreadBegin != NULL)
        {
            m_ServerSocket->OnThreadBegin(this);
        }
	}

	catch(Exception &exception)
	{
		ShowLog(FormatStr("m_ServerSocket->OnThreadBegin Error=%s",exception.Message));
	}

	sockaddr_in ClientSocketAddr;
	int         AddrLen = sizeof(ClientSocketAddr);
	m_ClientSocket = INVALID_SOCKET;
	m_ClientConnect = false;
    try
    {

    while(!this->m_Terminated)
	{
		m_ClientIP = "";
		State = tsWAIT;
		m_ClientSocket = m_ServerSocket->SafeAccept((sockaddr FAR *) &ClientSocketAddr,
													&AddrLen);
		 if(m_ClientSocket != INVALID_SOCKET)    //有效的连接
		{
			m_ClientConnect = true;
			m_ClientIP = inet_ntoa(ClientSocketAddr.sin_addr);
			try
			{
				State = tsCLIENT_CONNECT;
				if(m_ServerSocket->OnThreadClientAccept != NULL)
                {
                    m_ServerSocket->OnThreadClientAccept(this);
				}
				State = tsWAIT;
			}

			catch(Exception &exception)
			{
				ShowLog(FormatStr("m_ServerSocket->OnThreadClientAccept Error=%s",exception.Message));
				CloseSocket();
			}
        }
		//else
		//{
        //   ShowLog("Accept Client Error");
		//}
	}
    }
    catch (Exception &exception)
    {
        ShowDebugInfo(FormatStr("thread while Error=%s",exception.Message));
    }
	//通知客户端线程即将结束
    if(m_ServerSocket->OnThreadEnd != NULL)
    {
        m_ServerSocket->OnThreadEnd(this);
    }

}
//---------------------------------------------------------------------------
int CServerThread::Recv(char * lpBuffer,int Len)
{
  return recv(m_ClientSocket,lpBuffer,Len,0);
}
//------------------------------------------------------------------------------
int CServerThread::Send(char * lpBuffer,int Len)
{
  return send(m_ClientSocket,lpBuffer,Len,0);
}
//---------------------------------------------------------------------------
int CServerThread::RecvLen()
{
  int ResultLen=0;
  ioctlsocket(m_ClientSocket, FIONREAD,(u_long *)&ResultLen);
  return ResultLen;
}
//---------------------------------------------------------------------------
void CServerThread::CloseSocket()
{
  if(m_ClientSocket != INVALID_SOCKET)
  {
	 closesocket(m_ClientSocket);
	 m_ServerSocket->DecClientCount();
     m_ClientSocket=INVALID_SOCKET;
  }
}
//---------------------------------------------------------------------------
String GetThreadStateName(ThreadState StateFlag)
{
	  switch (StateFlag) {
		  case tsWAIT: return "Wait Accept";
		  case tsCLIENT_CONNECT: return "Client connected";
		  case tsSERVERCONNECT: return "Server connected";
		  case tsPROCESS_CLIENT: return "Client Process";
		  case tsPROCESS_SERVER: return "Server Process";
		  case tsCLOSE: return "Close";
		  case tsCREATE_FAIL: return "Create Fail";
	  default:
		  return FormatStr("Unknow State:%d",StateFlag);
	  }
}
//---------------------------------------------------------------------------
String  CServerThread::GetState()
{
	 return GetThreadStateName(State);
          
}

