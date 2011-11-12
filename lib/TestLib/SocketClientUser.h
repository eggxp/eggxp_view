//---------------------------------------------------------------------------

#ifndef SocketClientUserH
#define SocketClientUserH
//---------------------------------------------------------------------------
#include <VCL.h>
#include <WINSOCK2.H>
#include "ThreadManager.h"
#include "Log4Me.h"

class	SocketClientUser
{
private:
	int				m_ReadPos;
	int             m_RecvLen;
	vector<BYTE>	m_RecvBuf;
	int				m_IsClosed;

	void			InitRecvBuf();
	bool			SocketReadBuf(int needsize);
protected:
	String			m_ClientIP;
	SOCKET			m_ClientSocket;


	virtual	void	DecryptRecv(BYTE *lpdata, int len){}
	virtual void  	EncryptSend(BYTE *lpdata, int len){}
public:
	virtual	bool			SocketReadBYTE(BYTE *input);
	virtual	bool			SocketReadWORD(WORD *input);
	virtual	bool			SocketReadDWORD(DWORD *input);
	virtual	bool			SocketReadBuff(int len, vector<BYTE> *output);
	virtual	bool			SocketSendBuff(BYTE *lpData, int len);
	virtual	bool			SocketSendBYTE(BYTE data);
	virtual	bool			SocketSendWORD(WORD data);
	virtual	bool			SocketSendDWORD(DWORD data);

public:
	SocketClientUser();
	~SocketClientUser();

	virtual		void            Init(SOCKET client, SOCKADDR_IN clientAddr);
	GEN_GET_SET(int, IsClosed);
	GEN_GET_SET(SOCKET, ClientSocket)
	GEN_GET_SET(String, ClientIP)
};
#endif
