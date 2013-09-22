//---------------------------------------------------------------------------


#pragma hdrstop

#include "War3PackageDispatcher.h"
#include "SharedMemInfo.h"
#include "Opcodes.h"
#include "WOWProxy.h"
#include "GameWorld.h"
#include "AuthLoader.h"
#include "Opcodes.h"
#include "ShareDef.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


War3PackageDispatcher::War3PackageDispatcher()
{
    m_SendBufferPacket.SetPacketProxyIndex(GetPackageContainerIndex());
    m_RecvBufferPacket.SetPacketProxyIndex(GetPackageContainerIndex());
}

War3PackageDispatcher::~War3PackageDispatcher()
{
}

String              War3PackageDispatcher::GetOPcodeMsgByCMD(uint8 cmd)
{
    return          "";
}

int                War3PackageDispatcher::IsPacketNeedDecrypt(WOWPackage *packet)
{
	return 0;
}

int                 War3PackageDispatcher::DigestSendPacket()
{
	if (m_SendBufferPacket.GetOrgData() == "")
	{
        return 0;
	}
	if(m_SendBufferPacket.GetOrgData().Length() < 4)
	{
		return  0;
	}

	int pos = 0;
	BYTE a=0,b=0;
	a = ReadBYTE(m_SendBufferPacket.GetOrgData().c_str(), pos);
	b = ReadBYTE(m_SendBufferPacket.GetOrgData().c_str(), pos);
	int readLen = ReadWORD(m_SendBufferPacket.GetOrgData().c_str(), pos);
	int opcode = a * 0x100 + b;

	if(m_SendBufferPacket.GetOrgData().Length() < readLen)
	{
		return  0;
	}

	m_SendBufferPacket.SetOpCode(opcode);
    return  readLen;
}

void				War3PackageDispatcher::GetOrignSendPacket(WOWPackage *  packet)
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
        retPacket.SetData(AnsiString(m_SendBufferPacket.GetOrgData().c_str(), result));
        retPacket.SetOrgData(AnsiString(m_SendBufferPacket.GetOrgData().c_str(), result));
        retPacket.SetMark(SEND_MARK);
		retPacket.SetPacketProxyIndex(GetPackageContainerIndex());
		retPacket.SetOrgPrefixData(retPacket.GetData());
        MoveBuffer(&m_SendBufferPacket, result);
		retPacket.SetPacketProxyType(packet->GetPacketProxyType());
        fpOnGetPacket(&retPacket);
        m_SendBufferPacket.SetDecrypted(0);
    }
}

int                 War3PackageDispatcher::DigestRecvPacket()
{
//	return m_RecvBufferPacket.GetOrgData().Length();
	if (m_RecvBufferPacket.GetOrgData() == "") {
        return 0;
	}
    if(m_RecvBufferPacket.GetOrgData().Length() < 4)
        return  0;
	int pos = 0;
	BYTE a=0,b=0;
	a = ReadBYTE(m_RecvBufferPacket.GetOrgData().c_str(), pos);
	b = ReadBYTE(m_RecvBufferPacket.GetOrgData().c_str(), pos);
	int readLen = ReadWORD(m_RecvBufferPacket.GetOrgData().c_str(), pos);
	int opcode = a * 0x100 + b;

	if(m_RecvBufferPacket.GetOrgData().Length() < readLen)
		return 0;

	m_RecvBufferPacket.SetOpCode(opcode);
	return  readLen;
}

void				War3PackageDispatcher::GetOrignRecvPacket(WOWPackage *  packet)
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
        retPacket.SetData(AnsiString(m_RecvBufferPacket.GetOrgData().c_str(), result));
        retPacket.SetOrgData(AnsiString(m_RecvBufferPacket.GetOrgData().c_str(), result));
		retPacket.SetMark(RECV_MARK);
		retPacket.SetPacketProxyIndex(GetPackageContainerIndex());
		retPacket.SetOrgPrefixData(retPacket.GetData());
		MoveBuffer(&m_RecvBufferPacket, result);
		retPacket.SetPacketProxyType(packet->GetPacketProxyType());
        fpOnGetPacket(&retPacket);

        m_RecvBufferPacket.SetDecrypted(0);
    }
}

//´ò°ü·¢ËÍ
void				War3PackageDispatcher::PackData(char * buf, int len)
{
}

void				War3PackageDispatcher::Clear()
{
	m_SendBufferPacket.Clear();
    m_RecvBufferPacket.Clear();
}
