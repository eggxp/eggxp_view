//---------------------------------------------------------------------------


#pragma hdrstop

#include "DiabloIIIPackageDispatcher.h"
#include "SharedMemInfo.h"
#include "Opcodes.h"
#include "WOWProxy.h"
#include "GameWorld.h"
#include "AuthLoader.h"
#include "Opcodes.h"
#include "ShareDef.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


DiabloIIIPackageDispatcher::DiabloIIIPackageDispatcher()
{
    m_SendBufferPacket.SetPacketProxyIndex(GetPackageContainerIndex());
    m_RecvBufferPacket.SetPacketProxyIndex(GetPackageContainerIndex());
}

DiabloIIIPackageDispatcher::~DiabloIIIPackageDispatcher()
{
}

String              DiabloIIIPackageDispatcher::GetOPcodeMsgByCMD(uint8 cmd)
{
    return          "";
}

int                DiabloIIIPackageDispatcher::IsPacketNeedDecrypt(WOWPackage *packet)
{
	return 0;
}

int                 DiabloIIIPackageDispatcher::DigestSendPacket()
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
	BYTE a=0,b=0,c=0,d=0;
	a = ReadBYTE(m_SendBufferPacket.GetOrgData().c_str(), pos);
	b = ReadBYTE(m_SendBufferPacket.GetOrgData().c_str(), pos);
	c = ReadBYTE(m_SendBufferPacket.GetOrgData().c_str(), pos);
	d = ReadBYTE(m_SendBufferPacket.GetOrgData().c_str(), pos);
	int readLen = a*0x1000000 + b*0x10000 + c*0x100 + d;

	if(m_SendBufferPacket.GetOrgData().Length() < readLen)
	{
		return  0;
	}
	int opcode = ReadWORD(m_SendBufferPacket.GetOrgData().c_str(), pos);
	m_SendBufferPacket.SetOpCode(opcode);
    return  readLen;
}

void				DiabloIIIPackageDispatcher::GetOrignSendPacket(WOWPackage *  packet)
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
        MoveBuffer(&m_SendBufferPacket, result);
		retPacket.SetPacketProxyType(PROXY_TYPE_WORLD);
        fpOnGetPacket(&retPacket);
        m_SendBufferPacket.SetDecrypted(0);
    }

}

int                 DiabloIIIPackageDispatcher::DigestRecvPacket()
{
//	return m_RecvBufferPacket.GetOrgData().Length();
	if (m_RecvBufferPacket.GetOrgData() == "") {
        return 0;
	}
    if(m_RecvBufferPacket.GetOrgData().Length() < 4)
        return  0;
	int pos = 0;
	BYTE a=0,b=0,c=0,d=0;
	a = ReadBYTE(m_RecvBufferPacket.GetOrgData().c_str(), pos);
	b = ReadBYTE(m_RecvBufferPacket.GetOrgData().c_str(), pos);
	c = ReadBYTE(m_RecvBufferPacket.GetOrgData().c_str(), pos);
	d = ReadBYTE(m_RecvBufferPacket.GetOrgData().c_str(), pos);
	int readLen = a*0x1000000 + b*0x10000 + c*0x100 + d;

	if(m_RecvBufferPacket.GetOrgData().Length() < readLen)
		return 0;
	int opcode = ReadWORD(m_RecvBufferPacket.GetOrgData().c_str(), pos);
	m_RecvBufferPacket.SetOpCode(opcode);
	return  readLen;
}

void				DiabloIIIPackageDispatcher::GetOrignRecvPacket(WOWPackage *  packet)
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
        MoveBuffer(&m_RecvBufferPacket, result);
		retPacket.SetPacketProxyType(PROXY_TYPE_WORLD);
        fpOnGetPacket(&retPacket);

        m_RecvBufferPacket.SetDecrypted(0);
    }
}

//´ò°ü·¢ËÍ
void				DiabloIIIPackageDispatcher::PackData(char * buf, int len)
{
}

void				DiabloIIIPackageDispatcher::Clear()
{
	m_SendBufferPacket.Clear();
    m_RecvBufferPacket.Clear();
}
