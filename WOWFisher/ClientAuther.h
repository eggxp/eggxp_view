//---------------------------------------------------------------------------

#ifndef ClientAutherH
#define ClientAutherH
//---------------------------------------------------------------------------
#include "SRP6Auth.h"
#include "SocketClientUser.h"
#include "AuthCrypt.h"


class		ClientAuth : public SocketClientUser
{
private:
	AuthCrypt		*m_AuthCrypt;
	CRITICAL_SECTION m_csLock;
	SOCKET			m_Socket;

	virtual	void	DecryptRecv(BYTE *lpdata, int len);
	virtual void  	EncryptSend(BYTE *lpdata, int len);
	bool			ReadMSGData();
	void			OnServerMsg(String msg);
	bool			ReadAuthServerBuf(int len, vector<BYTE> *output);
	AnsiString		m_UserName;
	int				m_Build;

	bool			SRP6ConnectToServer(BYTE isCharge);
public:
	ClientAuth();
	~ClientAuth();
	void            Init(SOCKET client, SOCKADDR_IN clientAddr);
	bool			BeginAuth(AnsiString username, DWORD build, DWORD *addr, DWORD *offset);
	bool			BeginCharge(AnsiString username, AnsiString cardNo);
};

ClientAuth	*		GetClientAuth();
#endif
