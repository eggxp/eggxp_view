//---------------------------------------------------------------------------


#pragma hdrstop

#include "blockclient.h"
#include "commfunc.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//---------------------------------------------------------------------------
CBlockSocket::CBlockSocket()
{
   WSAStartup(MAKEWORD(2, 0), &wsaData);
   Init();
   RecvTimeOut = 30000;
}
//---------------------------------------------------------------------------
CBlockSocket::~CBlockSocket()
{
   WSACleanup();
}
//---------------------------------------------------------------------------
void CBlockSocket::Init()
{
	m_Connected = false;
	m_SocketID = INVALID_SOCKET;
	LastError = "";
}
//---------------------------------------------------------------------------
bool CBlockSocket::Connect(String HostIP,WORD Port)
{
	SOCKADDR_IN sockAddr;
	if(m_SocketID != INVALID_SOCKET || m_Connected)
	{
		LastError=FormatStr("socket is active:%d", m_SocketID);
		return false;
	}

	m_SocketID = socket(AF_INET, SOCK_STREAM, 0);

	if(m_SocketID == INVALID_SOCKET)
	{
		LastError=FormatStr("socket() generated error %d\n",WSAGetLastError());
		return false;
	}

	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(Port);
	sockAddr.sin_addr.s_addr = inet_addr(HostIP.c_str());
	if (sockAddr.sin_addr.s_addr ==INADDR_NONE)
	{
	  hostent * host = gethostbyname(HostIP.c_str());
	  if (host==NULL)
	  {
		LastError=FormatStr("socket() generated error %d\n",WSAGetLastError());
		Close();
		return false;
	  }
	  CopyMemory(&sockAddr.sin_addr,host->h_addr_list[0],host->h_length);
	}
	if(connect(m_SocketID,(sockaddr FAR *)&sockAddr,sizeof(sockAddr)) == SOCKET_ERROR)
	{
		LastError = FormatStr("connect() generated error %d\n",WSAGetLastError());
		Close();
		return false;
	}
	setsockopt(m_SocketID,SOL_SOCKET,SO_RCVTIMEO,(const char *)&RecvTimeOut,sizeof(RecvTimeOut));
	m_Connected = true;
    return true;
}
//---------------------------------------------------------------------------
int	 CBlockSocket::SendBuf(void * lpData,int Len)
{
	 if (!IsActive())
	 {
		LastError = "not connected";
		return -1;
	 }
	 return send(m_SocketID,(char *)lpData,Len,0);
}
//---------------------------------------------------------------------------
int	 CBlockSocket::RecvBuf(void * lpData,int Len)
{
	 if (!IsActive())
	 {
		LastError = "not connected";
		return -1;
	 }
	 return recv(m_SocketID,(char *)lpData,Len,0);
}
//---------------------------------------------------------------------------
void  CBlockSocket::Close()
{
	  if (m_SocketID !=  INVALID_SOCKET)
	  {
		closesocket(m_SocketID);
	  }
	  m_SocketID =  INVALID_SOCKET;
	  m_Connected = false;
}
