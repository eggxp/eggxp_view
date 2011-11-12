//---------------------------------------------------------------------------


#pragma hdrstop

#include "ClientAuther.h"
#include "ClientServerShared.h"
#include "AThreadLock.h"
#include "GameWorld.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
#define		CONNECT_ADDR	L"wowggg.com"

static		ClientAuth	 	gClientAuth;
ClientAuth	*		GetClientAuth()
{
	return		&gClientAuth;
}

ClientAuth::ClientAuth()
{
	m_Build = 0;
	InitializeCriticalSection(&m_csLock);
	m_AuthCrypt = NULL;
	m_Socket = NULL;
}

ClientAuth::~ClientAuth()
{
	DeleteCriticalSection(&m_csLock);
}

void	ClientAuth::DecryptRecv(BYTE *lpdata, int len)
{
	m_AuthCrypt->ServerToClientDecrypt(lpdata, len);
}

void  	ClientAuth::EncryptSend(BYTE *lpdata, int len)
{
	m_AuthCrypt->ClientToServerEncrypt(lpdata, len);
}

void		ClientAuth::OnServerMsg(String msg)
{
    GetThreadManager()->AddGUIMessage(msg);
}

bool		ClientAuth::ReadMSGData()
{
	BYTE			packType = 0;
	if(!this->SocketReadBYTE(&packType))
	{
		return false;
	}
	if(packType != PT_MSG)
	{
		if(packType == PT_S_REQ_CHARGE)
		{
			GetThreadManager()->AddGUIMessage("REQ_CHARGE");
			return ReadMSGData();
		}
		return true;
	}

	WORD	len = 0;
	if(!this->SocketReadWORD(&len))
	{
		return false;
	}

	vector<BYTE>	recv_msg;
	if(!this->SocketReadBuff(len, &recv_msg))
		return false;

	AnsiString recv_str((char *)&recv_msg[0], len);
	OnServerMsg(recv_str);
	return	ReadMSGData();
}

bool		ClientAuth::ReadAuthServerBuf(int len, vector<BYTE> *output)
{
	if(!this->ReadMSGData())
		return false;
	return	this->SocketReadBuff(len, output);
}

void        ClientAuth::Init(SOCKET client, SOCKADDR_IN clientAddr)
{
	ThreadLock lock(&m_csLock);
	SAFE_DELETE(m_AuthCrypt)
	m_AuthCrypt = new AuthCrypt;
	SocketClientUser::Init(client, clientAddr);
}

bool		ClientAuth::SRP6ConnectToServer(BYTE isCharge)
{
	if(m_Socket)
		closesocket(m_Socket);

	hostent *remoteHost = NULL;
	AnsiString addr = CONNECT_ADDR;
	remoteHost = gethostbyname(addr.c_str());
	String address;
	if (remoteHost)
	{
		address = inet_ntoa (*(struct in_addr *)*remoteHost->h_addr_list);
	}
	else
	{
		GetLog()->Info("Can't Connect To %s. Use 127.0.0.1", CONNECT_ADDR);
		address = "127.0.0.1";
	}

    m_Socket = socket(AF_INET,SOCK_STREAM,0);

    sockaddr_in their_addr; /* connector's address information */
	their_addr.sin_family = AF_INET; /* host byte order */
	their_addr.sin_port = htons(AUTH_SERVER_LIST_PORT); /* 远程主机端口 */
	AnsiString ansiIP = address;
	their_addr.sin_addr.s_addr=inet_addr(ansiIP.c_str()); /* 远程主机ip地址 */

	if (connect(m_Socket, (const sockaddr *)&their_addr, sizeof(their_addr)) == -1)
	{
		GetLog()->Error("WOWProxy::Start, Error");
        return false;
	}

	this->Init(m_Socket, their_addr);

	SRP6Client client;
	BigNumber A, s, B, K;

	client.CalcA(&A);
	tagCClientAuth	cAuth;
	strncpy(cAuth.UserName, m_UserName.c_str(), m_UserName.Length());
	memcpy(cAuth.A, A.AsByteArray(), sizeof(cAuth.A));
	cAuth.IsChargeProcess = isCharge;
	cAuth.Build = m_Build;
	if(!this->SocketSendBuff((BYTE *)&cAuth, sizeof(cAuth)))
	{
		return false;
	}

	vector<BYTE>	output;
	if(!this->ReadAuthServerBuf(sizeof(tagSClientAuth), &output))
	{
		return false;
	}

	tagSClientAuth	*sAuth = (tagSClientAuth *)&output[0];
	s.SetBinary(sAuth->s, sizeof(sAuth->s));
	B.SetBinary(sAuth->B, sizeof(sAuth->B));
	if(!client.CalcKey(m_UserName.c_str(), m_UserName.c_str(), s, B, &K))
	{
		return false;
	}

	BYTE	M1[20] = {0};
	client.GetResultM(m_UserName.c_str(), M1);
	tagCAuthCheck	cCheck;
	memcpy(cCheck.M, M1, sizeof(M1));
	if(!this->SocketSendBuff((BYTE *)&cCheck, sizeof(cCheck)))
	{
		return false;
	}

	if(!this->ReadAuthServerBuf(sizeof(tagSAuthCheck), &output))
	{
		return false;
	}

	tagSAuthCheck * sCheck = (tagSAuthCheck *)&output[0];
	if(!client.CheckServerAuth(m_UserName.c_str(), sCheck->M2))
	{
		return false;
	}

	m_AuthCrypt->Init(&K, WOWWGUserServerEncryptionKey, WOWWGUserServerDecryptionKey);
	A.SetDword(0);
	s.SetDword(0);
	B.SetDword(0);
	K.SetDword(0);
	return	true;
}

bool		ClientAuth::BeginAuth(AnsiString username, DWORD build, DWORD *addr, DWORD *offset)
{
	m_UserName = username;
	m_Build = build;
	vector<BYTE>	output;

	SRP6ConnectToServer(0);

	if(!this->ReadAuthServerBuf(sizeof(tagClientAddrInfo), &output))
	{
		return false;
	}
	tagClientAddrInfo *addrInfo = (tagClientAddrInfo *)&output[0];

//	GetSharedMemInfo()->FindSelf()->BaseAddr = baseaddr;
//	GetSharedMemInfo()->FindSelf()->BaseAddrOffset = baseaddroffset;
	*addr = addrInfo->Address;
	*offset = addrInfo->Offset;
	GetGameWorld()->SetExpireTime(addrInfo->ExpireTime);
	ReadMSGData();
	return true;
}

bool			ClientAuth::BeginCharge(AnsiString username, AnsiString cardNo)
{
	username = username.LowerCase();
	username = username.Trim();
	cardNo = cardNo.UpperCase();
	cardNo = cardNo.Trim();
	m_UserName = username;
	if(!SRP6ConnectToServer(1))
	{
		return false;
	}

	if(!this->SocketSendBYTE(cardNo.Length()))
		return false;

	if(!this->SocketSendBuff((BYTE *)cardNo.c_str(), cardNo.Length()))
		return false;

	ReadMSGData();
	return true;
}
