//---------------------------------------------------------------------------


#pragma hdrstop

#include "SocketClientUser.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

#define		RECV_BUFF			1024 * 4


SocketClientUser::SocketClientUser()
{
	m_IsClosed = 0;
	InitRecvBuf();
}

SocketClientUser::~SocketClientUser()
{
}

void			SocketClientUser::InitRecvBuf()
{
	m_ReadPos = 0;
	m_RecvLen = 0;
	m_RecvBuf.resize(RECV_BUFF);
}

bool			SocketClientUser::SocketReadBuf(int needsize)
{
	int remainLen = m_RecvBuf.size() - (m_ReadPos + m_RecvLen);
	ASSERT(remainLen >= 0)

	if(remainLen < (int)m_RecvBuf.size() / 4 || (int)m_RecvBuf.size() - m_RecvLen < needsize)
	{
		int newBuffSize = RECV_BUFF;
		if((int)m_RecvBuf.size() - m_RecvLen < needsize)
		{
			newBuffSize = m_RecvLen + needsize + 1024;
			GetLog()->Warn("Require Big Pack, Resize = %d", newBuffSize);
		}
		AnsiString remain;
		if(m_RecvLen > 0)
		{
			remain = AnsiString((char *)&m_RecvBuf[m_ReadPos], m_RecvLen);
		}
		m_ReadPos = 0;
		m_RecvBuf.resize(newBuffSize);
		memcpy(&m_RecvBuf[0], remain.c_str(), remain.Length());
	}

	while(m_RecvLen < needsize)
	{
		int writePos = m_ReadPos + m_RecvLen;
		ASSERT(writePos < (int)m_RecvBuf.size())
		int curLen = recv(m_ClientSocket, &m_RecvBuf[writePos], m_RecvBuf.size() - writePos, 0);
		if(curLen <= 0)
		{
			return false;
		}
		m_RecvLen += curLen;
	}

    this->DecryptRecv(&m_RecvBuf[m_ReadPos], needsize);
	return	true;
}

bool			SocketClientUser::SocketReadBYTE(BYTE *input)
{
	int needsize = sizeof(BYTE);
	if(m_RecvLen < needsize)
	{
		if(!SocketReadBuf(needsize))
			return	false;
	}
	else
	{
		this->DecryptRecv(&m_RecvBuf[m_ReadPos], needsize);
	}
	ASSERT(m_RecvLen >= needsize)
	ASSERT(m_ReadPos + m_RecvLen <= (int)m_RecvBuf.size())
	m_RecvLen -= needsize;
	BYTE result = ReadBYTE(&m_RecvBuf[0], m_ReadPos);
	if(input)
	{
		*input = result;
	}
	return true;
}

bool			SocketClientUser::SocketReadWORD(WORD *input)
{
	int needsize = sizeof(WORD);
	if(m_RecvLen < needsize)
	{
		if(!SocketReadBuf(needsize))
			return	false;
	}
	else
	{
		this->DecryptRecv(&m_RecvBuf[m_ReadPos], needsize);
	}
	ASSERT(m_RecvLen >= needsize)
	ASSERT(m_ReadPos + m_RecvLen <= (int)m_RecvBuf.size())
	m_RecvLen -= needsize;
	WORD result = ReadWORD(&m_RecvBuf[0], m_ReadPos);
	if(input)
	{
		*input = result;
	}
	return true;
}

bool			SocketClientUser::SocketReadDWORD(DWORD *input)
{
	int needsize = sizeof(DWORD);
	if(m_RecvLen < needsize)
	{
		if(!SocketReadBuf(needsize))
			return	false;
	}
	else
	{
		this->DecryptRecv(&m_RecvBuf[m_ReadPos], needsize);
	}
	ASSERT(m_RecvLen >= needsize)
	ASSERT(m_ReadPos + m_RecvLen <= (int)m_RecvBuf.size())
	m_RecvLen -= needsize;
	DWORD result = ReadDWORD(&m_RecvBuf[0], m_ReadPos);
	if(input)
	{
		*input = result;
	}
	return true;
}

bool	      	SocketClientUser::SocketReadBuff(int len, vector<BYTE> *output)
{
	int needsize = len;
	if(m_RecvLen < needsize)
	{
		if(!SocketReadBuf(needsize))
			return false;
	}
	else
	{
		this->DecryptRecv(&m_RecvBuf[m_ReadPos], needsize);
	}
	ASSERT(m_RecvLen >= needsize)
	ASSERT(m_ReadPos + m_RecvLen <= (int)m_RecvBuf.size())

	if((int)output->size() < len)
	{
		output->resize(len);
	}
	m_RecvLen -= needsize;
	ReadBuf(&m_RecvBuf[0], m_ReadPos, &output->at(0), len);
	return	true;
}

bool			SocketClientUser::SocketSendBuff(BYTE *lpData, int len)
{
	this->EncryptSend(lpData, len);
    int result = 0;
    while(len != 0)
    {
        result = send(m_ClientSocket, lpData, len, 0);
        if(result == SOCKET_ERROR)
		{
            return  false;
        }

        len = len - result;
        lpData = lpData + result;

        if(len == 0)
            return true;
    }

    return  true;
}

bool			SocketClientUser::SocketSendBYTE(BYTE data)
{
	return	SocketSendBuff((BYTE *)&data, sizeof(data));
}

bool			SocketClientUser::SocketSendWORD(WORD data)
{
	return	SocketSendBuff((BYTE *)&data, sizeof(data));
}

bool			SocketClientUser::SocketSendDWORD(DWORD data)
{
	return	SocketSendBuff((BYTE *)&data, sizeof(data));
}

void            SocketClientUser::Init(SOCKET client, SOCKADDR_IN clientAddr)
{
	InitRecvBuf();

	m_ClientSocket = client;
	in_addr ip;
	ip.S_un.S_addr = clientAddr.sin_addr.S_un.S_addr;        //unsigned longÀàÐÍ
	char* clientIp = inet_ntoa( ip );
	m_ClientIP = clientIp;
	GetLog()->Warn("Client Connect, Socket(%d), IP(%s)", m_ClientSocket, m_ClientIP);
}