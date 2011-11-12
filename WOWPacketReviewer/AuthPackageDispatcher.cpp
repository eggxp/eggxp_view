//---------------------------------------------------------------------------


#pragma hdrstop

#include "AuthPackageDispatcher.h"
#include "CommFunc.h"
#include "GameWorld.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//#include "Eay32DllLoader.h"





const AuthHandler table[] =
{
    { AUTH_LOGON_CHALLENGE, "AUTH_LOGON_CHALLENGE", &AuthPackageDispatcher::_HandleLogonChallenge                                 },
    { AUTH_LOGON_PROOF,        "AUTH_LOGON_PROOF",  &AuthPackageDispatcher::_HandleLogonProof                                  },
    { AUTH_RECONNECT_CHALLENGE, "AUTH_RECONNECT_CHALLENGE", &AuthPackageDispatcher::_HandleReconnectChallenge                                  },
    { AUTH_RECONNECT_PROOF,     "AUTH_RECONNECT_PROOF", &AuthPackageDispatcher::_HandleReconnectProof                                  },
    { REALM_LIST,               "REALM_LIST",       &AuthPackageDispatcher::_HandleRealmList                                  },
    { XFER_ACCEPT,              "XFER_ACCEPT",      &AuthPackageDispatcher::_HandleXferAccept                                  },
    { XFER_RESUME,              "XFER_RESUME",      &AuthPackageDispatcher::_HandleXferResume                                  },
    { XFER_CANCEL,              "XFER_CANCEL",      &AuthPackageDispatcher::_HandleXferCancel                                          }
};

enum eAuthResults
{
    REALM_AUTH_SUCCESS              = 0x00,
    REALM_AUTH_FAILURE              = 0x01,                 ///< Unable to connect
    REALM_AUTH_UNKNOWN1             = 0x02,                 ///< Unable to connect
    REALM_AUTH_ACCOUNT_BANNED       = 0x03,                 ///< This <game> account has been closed and is no longer available for use. Please go to <site>/banned.html for further information.
    REALM_AUTH_NO_MATCH             = 0x04,                 ///< The information you have entered is not valid. Please check the spelling of the account name and password. If you need help in retrieving a lost or stolen password, see <site> for more information
    REALM_AUTH_UNKNOWN2             = 0x05,                 ///< The information you have entered is not valid. Please check the spelling of the account name and password. If you need help in retrieving a lost or stolen password, see <site> for more information
    REALM_AUTH_ACCOUNT_IN_USE       = 0x06,                 ///< This account is already logged into <game>. Please check the spelling and try again.
    REALM_AUTH_PREPAID_TIME_LIMIT   = 0x07,                 ///< You have used up your prepaid time for this account. Please purchase more to continue playing
    REALM_AUTH_SERVER_FULL          = 0x08,                 ///< Could not log in to <game> at this time. Please try again later.
    REALM_AUTH_WRONG_BUILD_NUMBER   = 0x09,                 ///< Unable to validate game version. This may be caused by file corruption or interference of another program. Please visit <site> for more information and possible solutions to this issue.
    REALM_AUTH_UPDATE_CLIENT        = 0x0a,                 ///< Downloading
    REALM_AUTH_UNKNOWN3             = 0x0b,                 ///< Unable to connect
    REALM_AUTH_ACCOUNT_FREEZED      = 0x0c,                 ///< This <game> account has been temporarily suspended. Please go to <site>/banned.html for further information
    REALM_AUTH_UNKNOWN4             = 0x0d,                 ///< Unable to connect
    REALM_AUTH_UNKNOWN5             = 0x0e,                 ///< Connected.
    REALM_AUTH_PARENTAL_CONTROL     = 0x0f                  ///< Access to this account has been blocked by parental controls. Your settings may be changed in your account preferences at <site>
};


AuthPackageDispatcher::AuthPackageDispatcher()
{

}

AuthPackageDispatcher::~AuthPackageDispatcher()
{
    
}

int         AuthPackageDispatcher::DigestRecvBuffer()
{
//    int cmd = m_RecvBufferPacket.GetOrgData().c_str()[0];
//    if(cmd == AUTH_LOGON_CHALLENGE)
//    {
//        if(m_RecvBufferPacket.GetOrgData().Length() < 3)
//            return 0;
//        int pos = 2;
//        int result = ReadBYTE(m_RecvBufferPacket.GetOrgData().c_str(), pos);
//        if(result != REALM_AUTH_SUCCESS)
//        {
//            return  pos;
//        }
//
//        int len = 119;
//        if(m_RecvBufferPacket.GetOrgData().Length() < len)
//            return m_RecvBufferPacket.GetOrgData().Length();
//        return      len;
//    }
//    else if(cmd == AUTH_LOGON_PROOF)
//    {
//        if(m_RecvBufferPacket.GetOrgData().Length() < (int)sizeof(AUTH_LOGON_PROOF_S))
//            return 0;
//
//        return  sizeof(AUTH_LOGON_PROOF_S);
//    }
//    else if(cmd == REALM_LIST)
//    {
//    }
//    else if(cmd == XFER_INITIATE)
//    {
//    }
//
//
//
//    //错误了
//	GetLog()->Warn("[Auth] ERROR! Recv Pack cmd = %d Unknown!", cmd);
	return      m_RecvBufferPacket.GetOrgData().Length();
}

String      AuthPackageDispatcher::GetOPcodeMsgByCMD(uint8 cmd)
{
    for(DWORD i=0; i<AUTH_TOTAL_COMMANDS; i++)
    {
        if((uint8)table[i].cmd == cmd)
        {
            return  table[i].name;
        }
    }
    return      "";
}

void		AuthPackageDispatcher::GetOrignRecvPacket(WOWPackage *  packet)
{
//    GetLog()->Warn("AuthRecv:%d:%s", packet.Length(), BinToStr(packet.c_str(), packet.Length()));
    m_RecvBufferPacket.SetOrgData(m_RecvBufferPacket.GetOrgData() + packet->GetOrgData());


    int result = 0;
    while(m_RecvBufferPacket.GetOrgData().Length())
    {
        result = DigestRecvBuffer();
        if(result == 0)
        {
            return;
        }

		WOWPackage  packetResult;
		int opCode = m_RecvBufferPacket.GetOrgData().c_str()[0];
		packetResult.SetOpCodeMsg(GetOPcodeMsgByCMD(opCode));
		packetResult.SetOpCode(opCode);
		packetResult.SetData(AnsiString(m_RecvBufferPacket.GetOrgData().c_str(), result ));
		packetResult.SetOrgData(packetResult.GetData());
		packetResult.SetOrgPrefixData(packetResult.GetData());
		packetResult.SetMark(RECV_MARK);
		packetResult.SetPackType(1);
		packetResult.SetPacketProxyType(PROXY_TYPE_REALM);
		MoveBuffer(&m_RecvBufferPacket, result);
		fpOnGetPacket(&packetResult);
    }
}

void		AuthPackageDispatcher::GetOrignSendPacket(WOWPackage *  packet)
{
    //合并封包
//    GetLog()->Warn("AuthSend:%d:%s", packet.Length(), BinToStr(packet.c_str(), packet.Length()));
    m_SendBufferPacket.SetOrgData(m_SendBufferPacket.GetOrgData() + packet->GetOrgData());

    while (m_SendBufferPacket.GetOrgData().Length())
    {
        int cmd = m_SendBufferPacket.GetOrgData().c_str()[0];
        DWORD i = 0;
        int readLen = 0;
        for (i = 0; i < AUTH_TOTAL_COMMANDS; i++)
        {
            if((uint8)table[i].cmd == cmd)
            {
                readLen = (this->*table[i].handler)();
                if(readLen == 0)
                    return;

                WOWPackage  packetResult;
                packetResult.SetOpCodeMsg(table[i].name);
                packetResult.SetOpCode(table[i].cmd);
                packetResult.SetData(AnsiString(m_SendBufferPacket.GetOrgData().c_str(), readLen ));
                packetResult.SetMark(SEND_MARK);
				packetResult.SetPackType(1);
				packetResult.SetOrgData(packetResult.GetData());
				packetResult.SetPacketProxyType(PROXY_TYPE_REALM);
				packetResult.SetOrgPrefixData(packetResult.GetData());
                MoveBuffer(&m_SendBufferPacket, readLen);
                fpOnGetPacket(&packetResult);
                break;
            }
        }

        if(i == AUTH_TOTAL_COMMANDS)
        {
            GetLog()->Warn("[Auth] got unknown packet %u", (uint32)cmd);

            WOWPackage  packetResult;
            packetResult.SetOpCodeMsg("");
            packetResult.SetData(AnsiString(m_SendBufferPacket.GetOrgData().c_str(), m_SendBufferPacket.GetOrgData().Length() ));
            packetResult.SetMark(SEND_MARK);
			packetResult.SetPackType(1);
			MoveBuffer(&m_SendBufferPacket, m_SendBufferPacket.GetOrgData().Length());
			packetResult.SetOrgData(packetResult.GetData());
			packetResult.SetPacketProxyType(PROXY_TYPE_REALM);
			packetResult.SetOrgPrefixData(packetResult.GetData());
			fpOnGetPacket(&packetResult);
            return;
        }
    }

}

void		AuthPackageDispatcher::PackData(char * buf, int len)
{
	return ;
}

void				AuthPackageDispatcher::Clear()
{
	m_SendBufferPacket.Clear();
    m_RecvBufferPacket.Clear();
}


int        AuthPackageDispatcher::_HandleLogonChallenge()
{
    int readLend = sizeof(sAuthLogonChallenge_C);
    if (m_SendBufferPacket.GetOrgData().Length() < readLend)
        return 0;

    int pos = 0;
//    BYTE    cmd = ReadBYTE(m_SendBufferPacket.c_str(), pos);
//    BYTE    error = ReadBYTE(m_SendBufferPacket.c_str(), pos);

    pos += 2;
    WORD    size = ReadWORD(m_SendBufferPacket.GetOrgData().c_str(), pos);
    

    return      pos + size;
}

int        AuthPackageDispatcher::_HandleLogonProof()
{
    int readLend = sizeof(sAuthLogonProof_C);
    if (m_SendBufferPacket.GetOrgData().Length() < readLend)
        return 0;

    AUTH_LOGON_PROOF_C  * proof = (AUTH_LOGON_PROOF_C *)m_SendBufferPacket.GetOrgData().c_str();

    GetLog()->Warn("Get A  :%s", BinToStr(proof->A, sizeof(proof->A)));

    
    GetLog()->Warn("Get psw:%s", BinToStr(proof->M1, sizeof(proof->M1)));

	//密码转换方式未知...未知是否可以逆向转换
	return      readLend;
}

int        AuthPackageDispatcher::_HandleReconnectChallenge()
{
    int readLend = sizeof(sAuthLogonChallenge_C);
    if (m_SendBufferPacket.GetOrgData().Length() < readLend)
        return 0;


    return      readLend;
}

int        AuthPackageDispatcher::_HandleReconnectProof()
{
    int readLend = sizeof(sAuthReconnectProof_C);
    if (m_SendBufferPacket.GetOrgData().Length() < readLend)
        return 0;

    return      readLend;
}

int        AuthPackageDispatcher::_HandleRealmList()
{
    int readLend = 5;
    if (m_SendBufferPacket.GetOrgData().Length() < readLend)
        return 0;

    return      readLend;
}

int        AuthPackageDispatcher::_HandleXferAccept()
{
    int readLend = 1;
    if (m_SendBufferPacket.GetOrgData().Length() < 1)
        return 0;

    return      readLend;
}

int        AuthPackageDispatcher::_HandleXferResume()
{
    int readLend = 9;
    if (m_SendBufferPacket.GetOrgData().Length() < readLend)
        return 0;

    return      readLend;
}

int        AuthPackageDispatcher::_HandleXferCancel()
{
    int readLend = 1;
    if (m_SendBufferPacket.GetOrgData().Length() < readLend)
        return 0;

    return      readLend;
}

