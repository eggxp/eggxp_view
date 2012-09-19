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
	if (orgkey == "")
	{
		return;
	}
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
		pack->SetData(orgData);
		return;
	}
	BYTE command = orgData.c_str()[8] & ENET_PROTOCOL_COMMAND_MASK;
	BYTE command2 = orgData.c_str()[8] & 0xF0;
	if (command == ENET_PROTOCOL_COMMAND_PING)
	{
		pack->SetNotShowInGui(true);
		pack->SetData(orgData);
		return;
	}
	int header_len = 0;
	DWORD packet_size = 99999999;
	if (command == ENET_PROTOCOL_COMMAND_NONE)
	{
//		pack->SetNotShowInGui(true);
		pack->SetOpCodeMsg("ACK");
		header_len = 14;
		packet_size = orgData.c_str()[13];
	}
	else
	{
		String header_str1;
		String header_str2;
		String header_str3;
		BYTE channel = orgData.c_str()[9];
		header_str3 = channel;
		header_len = 8;
		switch (command2)
		{
			case ENET_PROTOCOL_COMMAND_FLAG_ACKNOWLEDGE:
				header_str1 = "ACKNOWLEDGE";
				break;
			case ENET_PROTOCOL_COMMAND_FLAG_UNSEQUENCED:
				header_str1 = "UNSEQUENCED";
				break;
		}
		switch (command)
		{
			case ENET_PROTOCOL_COMMAND_SEND_RELIABLE:
			{
				header_str2 = "RELIABLE";
				header_len += sizeof(ENetProtocolSendReliable);
				int pos = header_len - 2;
				if (orgData.Length() < pos + 2)
				{
					packet_size = ReadWORD(orgData.c_str(), pos);
				}
				break;
			}
			case ENET_PROTOCOL_COMMAND_SEND_UNRELIABLE:
			{
				header_str2 = "UNRELIABLE";
				header_len += sizeof(ENetProtocolSendUnreliable);
				int pos = header_len - 2;
				if (orgData.Length() < pos + 2)
				{
					packet_size = ReadWORD(orgData.c_str(), pos);
				}
				break;
			}
			case ENET_PROTOCOL_COMMAND_SEND_FRAGMENT:
			{
				header_str2 = "FRAGMENT";
				header_len += sizeof(ENetProtocolSendFragment);
				int pos = header_len - 4 * 4 - 2;
				if (orgData.Length() < pos + 2)
				{
					packet_size = ReadWORD(orgData.c_str(), pos);
				}
				break;
			}
			case ENET_PROTOCOL_COMMAND_SEND_UNSEQUENCED:
			{
				header_str2 = "UNSEQUENCED";
				header_len += sizeof(ENetProtocolSendUnsequenced);
				int pos = header_len - 2;
				if (orgData.Length() < pos + 2)
				{
					packet_size = ReadWORD(orgData.c_str(), pos);
				}
				break;
			}
			default:
				break;
		}
		pack->SetOpCodeMsg(FormatStr("%s_%s_%s", header_str1, header_str2, header_str3));
	}
	if (orgData.Length() < header_len)
	{
		pack->SetData(orgData);
		return;
	}
	AnsiString decryptData = orgData;
	decryptData = decryptData.Unique();
	unsigned char *decrypt_start = (unsigned char *)(decryptData.c_str() + header_len);
	int decrypt_length = decryptData.Length() - header_len;
	if ((DWORD)decrypt_length > packet_size)
	{
		decrypt_length = packet_size;
	}
	pack->SetHeadSize(0);
	if (decrypt_length < 8)
	{
		if (decrypt_length > 4)
		{
			int read_pos = 0;
			int read_opcode = ReadDWORD(decrypt_start, read_pos);
			pack->SetOpCode(read_opcode);
		}
		pack->SetData(AnsiString((char *)decrypt_start, decrypt_length));
		return;
	}
	GetLOLBlowFish()->GetBlowFish()->Decrypt(decrypt_start, decrypt_length - decrypt_length % 8);
	pack->SetNotShowInGui(false);
	int read_pos = 0;
	int read_opcode = ReadDWORD(decrypt_start, read_pos);
	pack->SetOpCode(read_opcode);
	pack->SetData(AnsiString((char *)decrypt_start, decrypt_length));
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
