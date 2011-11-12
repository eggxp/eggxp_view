//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "srvthread.h"
#include "blockserver.h"
#pragma package(smart_init)
//---------------------------------------------------------------------------

//   Important: Methods and properties of objects in VCL can only be
//   used in a method called using Synchronize, for example:
//
//      Synchronize(UpdateCaption);
//
//   where UpdateCaption could look like:
//
//      void __fastcall ServerThread::UpdateCaption()
//      {
//        Form1->Caption = "Updated in a thread";
//      }
//---------------------------------------------------------------------------

__fastcall CServerThread::CServerThread(bool CreateSuspended,CServerSocket * ServerSocket,DWORD StackSize,int Index)
{
     m_ClientSocket = INVALID_SOCKET;
     m_ServerSocket = ServerSocket;
     lpUserData     = NULL;
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
//		this->Synchronize((TThreadMethod)&Log);
}
//------------------------------------------------------------------------------
void CServerThread::ShowErrLog(String LogStr)
{
        m_LastError = LogStr;
//        this->Synchronize((TThreadMethod)&ErrLog);
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

    catch(...)
    {
       ShowLog("m_ServerSocket->OnThreadBegin Error");
    }

    sockaddr_in ClientSocketAddr;
    int         AddrLen = sizeof(ClientSocketAddr);
    m_ClientSocket = INVALID_SOCKET;
    m_ClientConnect = false;
    while(!this->m_Terminated)
    {
        m_ClientIP = "";
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

            catch(...)
            {
                ShowLog("m_ServerSocket->OnThreadBegin Error");
            }
        }
        //else
        //{
        //   ShowLog("Accept Client Error");
        //}
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
     m_ClientSocket=INVALID_SOCKET;
  }
}
