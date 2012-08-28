//---------------------------------------------------------------------------


#pragma hdrstop

#include "LOLPackageDispatcher.h"
#include "SharedMemInfo.h"
#include "Opcodes.h"
#include "base64.h"
#include "WOWProxy.h"
#include "GameWorld.h"
#include "AuthLoader.h"
#include "Opcodes.h"
#include "ShareDef.h"
#include "enet_protocol.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

static LOLBlowFish gLOLBlowFish;

LOLBlowFish * GetLOLBlowFish()
{
	return &gLOLBlowFish;
}

LOLBlowFish::LOLBlowFish()
{
	m_BlowFish = NULL;
}

LOLBlowFish::~LOLBlowFish()
{
	if (m_BlowFish)
	{
		delete m_BlowFish;
	}
}

BlowFish	*	LOLBlowFish::GetBlowFish()
{
	return m_BlowFish;
}

void	LOLBlowFish::Init(AnsiString key)
{
	if (m_BlowFish)
	{
		delete m_BlowFish;
	}
	std::string orgkey = base64_decode(key.c_str());
	m_BlowFish = new BlowFish((unsigned char*)orgkey.c_str(), orgkey.length());
}

////////////////////////////////////////////////////////////////////////////////////


LOLPackageDispatcher::LOLPackageDispatcher()
{
    m_SendBufferPacket.SetPacketProxyIndex(GetPackageContainerIndex());
    m_RecvBufferPacket.SetPacketProxyIndex(GetPackageContainerIndex());
}

LOLPackageDispatcher::~LOLPackageDispatcher()
{
}

String              LOLPackageDispatcher::GetOPcodeMsgByCMD(uint8 cmd)
{
    return          "";
}

int                LOLPackageDispatcher::IsPacketNeedDecrypt(WOWPackage *packet)
{
	return 0;
}

int                 LOLPackageDispatcher::DigestSendPacket()
{
	return m_SendBufferPacket.GetOrgData().Length();
}

void				LOLPackageDispatcher::GetOrignSendPacket(WOWPackage *  packet)
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
        retPacket.SetOrgData(AnsiString(m_SendBufferPacket.GetOrgData().c_str(), result));
        retPacket.SetMark(SEND_MARK);
		retPacket.SetPacketProxyIndex(GetPackageContainerIndex());
		retPacket.SetOrgPrefixData(retPacket.GetData());
        MoveBuffer(&m_SendBufferPacket, result);
		retPacket.SetPacketProxyType(packet->GetPacketProxyType());
		DecryptData(&retPacket);
        fpOnGetPacket(&retPacket);
        m_SendBufferPacket.SetDecrypted(0);
	}
}

void				LOLPackageDispatcher::DecryptData(WOWPackage* pack)
{
	AnsiString orgData = pack->GetOrgData();
	if(orgData.Length() < 10)
	{
		pack->SetNotShowInGui(true);
		pack->SetData(orgData);
		return;
	}
	BYTE command = orgData.c_str()[8] & ENET_PROTOCOL_COMMAND_MASK;
	if ((command == ENET_PROTOCOL_COMMAND_PING) ||
		(command == ENET_PROTOCOL_COMMAND_ACKNOWLEDGE))
	{
		pack->SetNotShowInGui(true);
		pack->SetData(orgData);
		return;
	}
	int header_len = 8;
	switch (command)
	{
		case ENET_PROTOCOL_COMMAND_SEND_RELIABLE:
		{
			pack->SetOpCodeMsg("RELIABLE");
			header_len += sizeof(ENetProtocolSendReliable);
			break;
		}
		case ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE:
		{
			pack->SetOpCodeMsg("UNRELIABLE");
			header_len += sizeof(ENetProtocolSendUnreliable);
			break;
		}
		case ENET_PROTOCOL_COMMAND_SEND_FRAGMENT:
		{
			pack->SetOpCodeMsg("FRAGMENT");
			header_len += sizeof(ENetProtocolSendFragment);
			break;
		}
		case ENET_PROTOCOL_COMMAND_SEND_UNSEQUENCED:
		{
			pack->SetOpCodeMsg("UNSEQUENCED");
			header_len += sizeof(ENetProtocolSendUnsequenced);
			break;
		}
		default:
			break;
	}
	if (orgData.Length() < header_len)
	{
		return;
	}
	AnsiString decryptData = orgData;
	decryptData = decryptData.Unique();
	unsigned char *decrypt_start = (unsigned char *)(decryptData.c_str() + header_len);
	int decrypt_length = decryptData.Length() - header_len;
	if (decrypt_length < 8)
	{
		pack->SetData(orgData);
		return;
	}
	GetLOLBlowFish()->GetBlowFish()->Decrypt(decrypt_start, decrypt_length - decrypt_length % 8);
	pack->SetNotShowInGui(false);
	pack->SetData(AnsiString((char *)decrypt_start, decrypt_length));
	pack->SetHeadSize(header_len);
	return;
}

int                 LOLPackageDispatcher::DigestRecvPacket()
{
	return m_RecvBufferPacket.GetOrgData().Length();
}

void				LOLPackageDispatcher::GetOrignRecvPacket(WOWPackage *  packet)
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
		retPacket.SetOrgData(AnsiString(m_RecvBufferPacket.GetOrgData().c_str(), result));
		retPacket.SetMark(RECV_MARK);
		retPacket.SetPacketProxyIndex(GetPackageContainerIndex());
		retPacket.SetOrgPrefixData(retPacket.GetData());
		MoveBuffer(&m_RecvBufferPacket, result);
		retPacket.SetPacketProxyType(packet->GetPacketProxyType());
		DecryptData(&retPacket);
		fpOnGetPacket(&retPacket);

        m_RecvBufferPacket.SetDecrypted(0);
    }
}

//´ò°ü·¢ËÍ
void				LOLPackageDispatcher::PackData(char * buf, int len)
{
}

void				LOLPackageDispatcher::Clear()
{
	m_SendBufferPacket.Clear();
    m_RecvBufferPacket.Clear();
}
