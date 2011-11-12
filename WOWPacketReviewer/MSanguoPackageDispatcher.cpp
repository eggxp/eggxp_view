//---------------------------------------------------------------------------


#pragma hdrstop

#include "MSanguoPackageDispatcher.h"
#include "SharedMemInfo.h"
#include "Opcodes.h"
#include "WOWProxy.h"
#include "GameWorld.h"
#include "AuthLoader.h"
#include "Opcodes.h"
#include "ShareDef.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


MSanguoPackageDispatcher::MSanguoPackageDispatcher()
{
    m_SendBufferPacket.SetPacketProxyIndex(GetPackageContainerIndex());
    m_RecvBufferPacket.SetPacketProxyIndex(GetPackageContainerIndex());
}

MSanguoPackageDispatcher::~MSanguoPackageDispatcher()
{
}

String              MSanguoPackageDispatcher::GetOPcodeMsgByCMD(uint8 cmd)
{
    return          "";
}

int                MSanguoPackageDispatcher::IsPacketNeedDecrypt(WOWPackage *packet)
{
	return 0;
}

int                 MSanguoPackageDispatcher::DigestSendPacket()
{
	if(GetWOWProxyManager()->GetDirectModel())
	{
		return m_SendBufferPacket.GetOrgData().Length();
	}
	if (m_SendBufferPacket.GetOrgData() == "")
	{
        return 0;
	}
	if(m_SendBufferPacket.GetOrgData().Length() < 6)
	{
		return  0;
	}

	int pos = 0;
	int readLen = ReadWORD(m_SendBufferPacket.GetOrgData().c_str(), pos) + 2;

	if(m_SendBufferPacket.GetOrgData().Length() < readLen)
	{
		return  0;
	}
	int opcode = ReadDWORD(m_SendBufferPacket.GetOrgData().c_str(), pos);
	m_SendBufferPacket.SetOpCode(opcode);
    return  readLen;
}

void				MSanguoPackageDispatcher::GetOrignSendPacket(WOWPackage *  packet)
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

int                 MSanguoPackageDispatcher::DigestRecvPacket()
{
	if (m_RecvBufferPacket.GetOrgData() == "") {
        return 0;
	}
    if(m_RecvBufferPacket.GetOrgData().Length() < 2)
        return  0;
	int pos = 0;
	int readLen = ReadWORD(m_RecvBufferPacket.GetOrgData().c_str(), pos) + 2;

	if(m_RecvBufferPacket.GetOrgData().Length() < readLen)
		return 0;
	if (m_RecvBufferPacket.GetOrgData().Length() < pos + 4) {
		m_RecvBufferPacket.SetOpCode(0);
		return  readLen;
	}
	int opcode = ReadDWORD(m_RecvBufferPacket.GetOrgData().c_str(), pos);
	m_RecvBufferPacket.SetOpCode(opcode);
	return  readLen;
}

void				MSanguoPackageDispatcher::GetOrignRecvPacket(WOWPackage *  packet)
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
void				MSanguoPackageDispatcher::PackData(char * buf, int len)
{
}

void				MSanguoPackageDispatcher::Clear()
{
	m_SendBufferPacket.Clear();
    m_RecvBufferPacket.Clear();
}
