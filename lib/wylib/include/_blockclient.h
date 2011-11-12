//---------------------------------------------------------------------------

#ifndef blockclientH
#define blockclientH
#include <vcl.h>
#include <winsock.h>

//×èÈû¿Í»§¶ËSocket
class CBlockSocket
{
private:
	WSADATA  wsaData;
	bool		 m_Connected;
	SOCKET		 m_SocketID;
	int			 RecvTimeOut;
protected:
	 void Init();
public:
	String		 LastError;
public:
	CBlockSocket();
	~CBlockSocket();
	bool Connect(String HostIP,WORD Port);
	int	 SendBuf(void * lpData,int Len);
	int	 RecvBuf(void * lpData,int Len);
	bool  IsActive(){return m_Connected;}
	void   Close();
};
//---------------------------------------------------------------------------
#endif
