//---------------------------------------------------------------------------


#pragma hdrstop

#include "DefaultPackageDispatcher.h"
#include "SharedMemInfo.h"
#include "Opcodes.h"
#include "WOWProxy.h"
#include "GameWorld.h"
#include "AuthLoader.h"
#include "Opcodes.h"
#include "ShareDef.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


DefaultPackageDispatcher::DefaultPackageDispatcher()
{
    m_SendBufferPacket.SetPacketProxyIndex(GetPackageContainerIndex());
    m_RecvBufferPacket.SetPacketProxyIndex(GetPackageContainerIndex());
}

DefaultPackageDispatcher::~DefaultPackageDispatcher()
{
}

String              DefaultPackageDispatcher::GetOPcodeMsgByCMD(uint8 cmd)
{
    return          "";
}

int                DefaultPackageDispatcher::IsPacketNeedDecrypt(WOWPackage *packet)
{
	return 0;
}

int                 DefaultPackageDispatcher::DigestSendPacket()
{
	return m_SendBufferPacket.GetOrgData().Length();
}

void				DefaultPackageDispatcher::GetOrignSendPacket(WOWPackage *  packet)
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

int                 DefaultPackageDispatcher::DigestRecvPacket()
{
	return m_RecvBufferPacket.GetOrgData().Length();
}

void				DefaultPackageDispatcher::GetOrignRecvPacket(WOWPackage *  packet)
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
void				DefaultPackageDispatcher::PackData(char * buf, int len)
{
}

void				DefaultPackageDispatcher::Clear()
{
	m_SendBufferPacket.Clear();
    m_RecvBufferPacket.Clear();
}
