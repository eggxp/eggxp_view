//---------------------------------------------------------------------------


#pragma hdrstop

#include "WorldPackageDispatcher.h"
#include "SharedMemInfo.h"
#include "Opcodes.h"
#include "WOWProxy.h"
#include "GameWorld.h"
#include "AuthLoader.h"
#include "Opcodes.h"
#include "ShareDef.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

#pragma pack(push,1)
//struct ServerPktHeader
//{
//    /**
//     * size is the length of the payload _plus_ the length of the opcode
//     */
//    ServerPktHeader(uint32 size, uint16 cmd) : size(size)
//    {
//        uint8 headerIndex=0;
//        if(isLargePacket())
//        {
//            header[headerIndex++] = 0x80|(0xFF &(size>>16));
//        }
//        //WORD size
//        header[headerIndex++] = 0xFF &(size>>8);
//        header[headerIndex++] = 0xFF &size;
//
//        //WORD  cmd
//        header[headerIndex++] = 0xFF & cmd;
//        header[headerIndex++] = 0xFF & (cmd>>8);
//    }
//
//    uint8 getHeaderLength()
//    {
//        // cmd = 2 bytes, size= 2||3bytes
//        return 2+(isLargePacket()?3:2);
//    }
//
//    bool isLargePacket()
//    {
//        return size > 0x7FFF;
//    }
//
//    uint8 header[5];
//};




#pragma pack(pop)

WorldPackageDispatcher::WorldPackageDispatcher()
{
    m_SendBufferPacket.SetPacketProxyIndex(GetPackageContainerIndex());
    m_RecvBufferPacket.SetPacketProxyIndex(GetPackageContainerIndex());
}

WorldPackageDispatcher::~WorldPackageDispatcher()
{
}

String              WorldPackageDispatcher::GetOPcodeMsgByCMD(uint8 cmd)
{
    return          "";
}

int                WorldPackageDispatcher::IsPacketNeedDecrypt(WOWPackage *packet)
{
    if(packet->GetOrgData().Length() < 4)
    {
        return 1;
    }

    if(GetGameWorld()->GetIsLoginOK())
    {
        return 1;
    }
    BYTE *lpdata = packet->GetOrgData().c_str();
    int length = lpdata[0] * 0x10 + lpdata[1];
    int pos = 2;
    int opcode = ReadWORD(packet->GetOrgData().c_str(), pos);
//    GetLog()->Info("length = %d", length);
//    GetLog()->Info("opcode = %d", opcode);
    if(length < 1024 && (opcode == SMSG_AUTH_CHALLENGE ||
                        opcode == CMSG_AUTH_SESSION ||
                        opcode == CMSG_REDIRECTION_AUTH_PROOF))
    {
        return 0;
    }
    return 1;
}

int                 WorldPackageDispatcher::DigestSendPacket()
{
	if(GetWOWProxyManager()->GetDirectModel())
	{
		return m_SendBufferPacket.GetOrgData().Length();
	}
    if(m_SendBufferPacket.GetOrgData().Length() < (int)sizeof(ClientPktHeader))
    {
        return  0;
    }

    int enableDecrypt = IsPacketNeedDecrypt(&m_SendBufferPacket);
//    GetLog()->Info("DigestSendPacket::enableDecrypt = %d", enableDecrypt);
    if(enableDecrypt)
    {
       m_SendBufferPacket.ClientToServerDecrypt();
    }
//    GetLog()->Warn("SendDecrypt:(%d):%s", m_SendBufferPacket.GetData().Length(), BinToStr(m_SendBufferPacket.GetData().c_str(), m_SendBufferPacket.GetData().Length()));

    ClientPktHeader * header = (ClientPktHeader *)m_SendBufferPacket.GetData().c_str();
    int pos = 0;
    BYTE    a = ReadBYTE(m_SendBufferPacket.GetData().c_str(), pos);
    BYTE    b = ReadBYTE(m_SendBufferPacket.GetData().c_str(), pos);


    int readLen = a * 0x100 + b + 2;

//    GetLog()->Warn("Read Len = %d, cmd = 0x%x", readLen, header->cmd);

    if(m_SendBufferPacket.GetOrgData().Length() < readLen)
    {
        return  0;
    }

	int build = GetSharedMemInfo()->FindSelf()->Build;
	m_SendBufferPacket.SetOpCode(header->cmd);
	if(header->cmd == CMSG_AUTH_SESSION)
	{
		GetLog()->Info("Init Seed! GetPacketProxyIndex = %d", GetPackageContainerIndex());
        InitSeed(GetPackageContainerIndex(), build, GetGameWorld()->GetSessionKey());
//		if(GetGameWorld()->GetSessionKey() == "")
//		{
//			#ifndef	WOW_FISHER
//			GetLog()->Warn("INIT SEED!");
//			String sessionKey;
//			GetGameWorld()->SetInputSessionKey(true);
//			GetLog()->MessageWarn(MSG_TOP_WINDOW, "");
//
//			String msg = "输入游戏服务器中存储的sessionkey";
//			if(InputQuery(msg, msg, sessionKey))
//			{
//				GetGameWorld()->SetSessionKey(sessionKey);
//				InitSeed(build, sessionKey);
//			}
//			#endif
//		}
//		else
//		{
//			InitSeed(build, GetGameWorld()->GetSessionKey());
//		}

		GetGameWorld()->SetInputSessionKey(false);
	}

    if(header->cmd == CMSG_REDIRECTION_AUTH_PROOF)
    {
        GetLog()->Info("Init Seed2. index = %d", GetPackageContainerIndex());
        int build = GetSharedMemInfo()->FindSelf()->Build;
        InitSeed(GetPackageContainerIndex(), build, GetGameWorld()->GetSessionKey());
    }

    if(GetGameWorld()->GetRedirectClientState() == RCS_RECEIVE_AUTH_CHANLLAGE)
    {
//        GetLog()->Info("GetGameWorld()->SetRedirectClientState(RCS_REDIRECT_OK);");
		GetGameWorld()->SetRedirectClientState(RCS_REDIRECT_OK);
//		int build = GetSharedMemInfo()->FindSelf()->Build;
//		InitSeed(build, GetGameWorld()->GetSessionKey());
    }
    return  readLen;
}

void				WorldPackageDispatcher::GetOrignSendPacket(WOWPackage *  packet)
{
    m_SendBufferPacket.SetOrgData(m_SendBufferPacket.GetOrgData() + packet->GetOrgData());
    m_SendBufferPacket.SetData(m_SendBufferPacket.GetData() + packet->GetOrgData());
    m_SendBufferPacket.SetPacketProxyIndex(GetPackageContainerIndex());

//	GetLog()->Info("WorldOrgSend:(%d):%s", packet->GetOrgData().Length(), BinToStr(packet->GetOrgData().c_str(), packet->GetOrgData().Length()));

    int result = 0;
    while(1)
    {
        result = DigestSendPacket();
        if(result == 0)
        {          
            return;
        }

//        GetLog()->Warn(LookupOpcodeName(m_SendBufferPacket.GetOpCode()));
        WOWPackage  retPacket;
        retPacket.SetOpCodeMsg(LookupOpcodeName(m_SendBufferPacket.GetOpCode()));
        retPacket.SetOpCode(m_SendBufferPacket.GetOpCode());
        retPacket.SetData(AnsiString(m_SendBufferPacket.GetData().c_str(), result));
        retPacket.SetOrgData(AnsiString(m_SendBufferPacket.GetOrgData().c_str(), result));
        retPacket.SetMark(SEND_MARK);
        retPacket.SetPacketProxyIndex(GetPackageContainerIndex());
        MoveBuffer(&m_SendBufferPacket, result);
		retPacket.SetPacketProxyType(PROXY_TYPE_WORLD);
        fpOnGetPacket(&retPacket);
        m_SendBufferPacket.SetDecrypted(0);
    }

}

int                 WorldPackageDispatcher::DigestRecvPacket()
{
	if(GetWOWProxyManager()->GetDirectModel())
	{
		return m_RecvBufferPacket.GetOrgData().Length();
	}
    // 80 80 53 7D 04
//    AnsiString dd = HexStrToBinStr("80 80 53 7D 04");
//    m_RecvBufferPacket.SetOrgData(dd);
//    m_RecvBufferPacket.SetData(dd);

    if(m_RecvBufferPacket.GetOrgData().Length() < 4)
        return  0;

//	int enableDecrypt = GetGameWorld()->GetEnableDecrypt() & (GetGameWorld()->GetRedirectClientState() != RCS_DISCONNECT);
    int enableDecrypt = IsPacketNeedDecrypt(&m_RecvBufferPacket);
//    GetLog()->Info("DigestRecvPacket::enableDecrypt = %d", enableDecrypt);
    if(enableDecrypt)
	{
		m_RecvBufferPacket.ServerToClientDecrypt();
	}

//	GetLog()->Warn("DigestRecvPacket! %s", BinToStr(m_RecvBufferPacket.GetData().c_str(), 10));
//    GetLog()->Info("PacketIndex:%d", GetPackageContainerIndex());
//	GetLog()->Warn("OrgRecv:(%d):%s", m_RecvBufferPacket.GetOrgData().Length(), BinToStr(m_RecvBufferPacket.GetOrgData().c_str(), m_RecvBufferPacket.GetOrgData().Length()));

	int lenLen = 2;
	int pos=0;
	BYTE sign = ReadBYTE(m_RecvBufferPacket.GetData().c_str(), pos);
	BYTE a=0,b=0,c=0;
	if(sign > 0x7F)
	{
		//Big package;
		a = sign & 0x7F;
		b = ReadBYTE(m_RecvBufferPacket.GetData().c_str(), pos);
		lenLen = 3;
		if(enableDecrypt)
		{
//            GetLog()->Warn("m_RecvBufferPacket.ServerToClientDecryptForBigPacket(), ConnectionIndex = %d, m_BigPacketDecrypted = %d", m_RecvBufferPacket.GetPacketProxyIndex(), m_RecvBufferPacket.GetBigPacketDecrypted());
			m_RecvBufferPacket.ServerToClientDecryptForBigPacket();
		}
//        GetLog()->Warn("m_RecvBufferPacket.ConnectionIndex = %d. a = %d, b = %d, pos = %d", m_RecvBufferPacket.GetPacketProxyIndex(), a, b, pos);
//		GetLog()->Warn("DigestRecvPacket! len = %d : %s", m_RecvBufferPacket.GetData().Length(), BinToStr(m_RecvBufferPacket.GetData().c_str(), 10));
    }
    else
    {
        b = sign;
	}

    if(enableDecrypt)
	{
//        GetLog()->Warn("m_RecvBufferPacket.ServerToClientDecryptOver(), m_BigPacketDecrypted = %d", m_RecvBufferPacket.GetBigPacketDecrypted());
		m_RecvBufferPacket.ServerToClientDecryptOver();
	}

//    GetLog()->Warn("RecvDecrypt:(%d):%s", m_RecvBufferPacket.GetData().Length(), BinToStr(m_RecvBufferPacket.GetData().c_str(), m_RecvBufferPacket.GetData().Length()));

    c = ReadBYTE(m_RecvBufferPacket.GetData().c_str(), pos);
    int readLen = a*0x10000 + b*0x100 + c + lenLen;
    int opcode = ReadWORD(m_RecvBufferPacket.GetData().c_str(), pos);
    m_RecvBufferPacket.SetOpCode(opcode);

//    GetLog()->Warn("readLen = %d, opcode = 0x%X", readLen, opcode);


    if(m_RecvBufferPacket.GetOpCode() != SMSG_AUTH_CHALLENGE && enableDecrypt == 0)
    {
        //未解密通过
//        GetLog()->Info("NEED SESSION KEY TO DECRYPT!");
        return 0;
	}

//	if(readLen - m_RecvBufferPacket.GetOrgData().Length() > 2048)
//	{
//		GetLog()->Info("Packet Decrypt May Be Wrong. connectionIndex = %d", GetPackageContainerIndex());
//		GetLog()->Info("------------------------begin try decrypt");
//		GetLog()->Info("RecvDecrypt:(%d):%s", m_RecvBufferPacket.GetOrgData().Length(), BinToStr(m_RecvBufferPacket.GetOrgData().c_str(), m_RecvBufferPacket.GetOrgData().Length()));
//		for(int i=0; i<20; i++)
//		{
//			m_RecvBufferPacket.SetDecrypted(0);
//			m_RecvBufferPacket.ServerToClientDecrypt();
//			GetLog()->Info("RecvDecrypt:(%d):%s", m_RecvBufferPacket.GetData().Length(), BinToStr(m_RecvBufferPacket.GetData().c_str(), m_RecvBufferPacket.GetData().Length()));
//		}
//		GetLog()->Info("RecvDecrypt:(%d):%s", m_RecvBufferPacket.GetOrgData().Length(), BinToStr(m_RecvBufferPacket.GetOrgData().c_str(), m_RecvBufferPacket.GetOrgData().Length()));
//		GetLog()->Info("========================end try decrypt");
//
//		GetLog()->Info("------------------------begin try decrypt reinit");
////		int build = GetSharedMemInfo()->FindSelf()->Build;
////		InitServerToClientSeed(build, GetGameWorld()->GetSessionKey());
//		GetLog()->Info("RecvDecrypt:(%d):%s", m_RecvBufferPacket.GetOrgData().Length(), BinToStr(m_RecvBufferPacket.GetOrgData().c_str(), m_RecvBufferPacket.GetOrgData().Length()));
//        int packetIndex = GetPackageContainerIndex();
//        m_RecvBufferPacket.SetPacketProxyIndex(0);
//		for(int i=0; i<20; i++)
//		{
//			m_RecvBufferPacket.SetDecrypted(0);
//			m_RecvBufferPacket.ServerToClientDecrypt();
//			GetLog()->Info("RecvDecrypt:(%d):%s", m_RecvBufferPacket.GetData().Length(), BinToStr(m_RecvBufferPacket.GetData().c_str(), m_RecvBufferPacket.GetData().Length()));
//		}
//		GetLog()->Info("RecvDecrypt:(%d):%s", m_RecvBufferPacket.GetOrgData().Length(), BinToStr(m_RecvBufferPacket.GetOrgData().c_str(), m_RecvBufferPacket.GetOrgData().Length()));
//		GetLog()->Info("========================end try decrypt");
//        m_RecvBufferPacket.SetPacketProxyIndex(packetIndex);
//	}

	if(m_RecvBufferPacket.GetOrgData().Length() < readLen)
        return 0;

	if(m_RecvBufferPacket.GetOpCode() == SMSG_REDIRECT_CLIENT)
	{
//		GetLog()->Info("GetGameWorld()->SetRedirectClientState(RCS_RECEIVE_REDIRECT_PACK);");
        GetGameWorld()->SetRedirectClientState(RCS_RECEIVE_REDIRECT_PACK);
	}
    //GetGameWorld()->GetRedirectClientState() == RCS_DISCONNECT
	if(m_RecvBufferPacket.GetOpCode() == SMSG_AUTH_CHALLENGE && GetPackageContainerIndex() > 0)
	{
		GetGameWorld()->SetRedirectClientState(RCS_RECEIVE_AUTH_CHANLLAGE);
	}
    return  readLen;
}

void				WorldPackageDispatcher::GetOrignRecvPacket(WOWPackage *  packet)
{
//    GetLog()->Info("WorldRecv:(%d):%s", packet->GetOrgData().Length(), BinToStr(packet->GetOrgData().c_str(), packet->GetOrgData().Length()));
    m_RecvBufferPacket.SetOrgData(m_RecvBufferPacket.GetOrgData() + packet->GetOrgData());
    m_RecvBufferPacket.SetData(m_RecvBufferPacket.GetData() + packet->GetOrgData());
    m_RecvBufferPacket.SetPacketProxyIndex(GetPackageContainerIndex());


    int result = 0;
    while(1)
    {
        result = DigestRecvPacket();
        if(result == 0)
        {             
            return;
        }

//        GetLog()->Warn(LookupOpcodeName(m_RecvBufferPacket.GetOpCode()));
        WOWPackage  retPacket;
        retPacket.SetOpCodeMsg(LookupOpcodeName(m_RecvBufferPacket.GetOpCode()));
        retPacket.SetOpCode(m_RecvBufferPacket.GetOpCode());
        retPacket.SetData(AnsiString(m_RecvBufferPacket.GetData().c_str(), result));
        retPacket.SetOrgData(AnsiString(m_RecvBufferPacket.GetOrgData().c_str(), result));
        retPacket.SetMark(RECV_MARK);
        retPacket.SetPacketProxyIndex(GetPackageContainerIndex());
        MoveBuffer(&m_RecvBufferPacket, result);
		retPacket.SetPacketProxyType(PROXY_TYPE_WORLD);
        fpOnGetPacket(&retPacket);

        m_RecvBufferPacket.SetDecrypted(0);
    }
}

//打包发送
void				WorldPackageDispatcher::PackData(char * buf, int len)
{
}

void				WorldPackageDispatcher::Clear()
{
	m_SendBufferPacket.Clear();
    m_RecvBufferPacket.Clear();
}
