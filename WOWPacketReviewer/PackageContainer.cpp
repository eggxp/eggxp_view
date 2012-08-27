//---------------------------------------------------------------------------


#pragma hdrstop

#include "PackageContainer.h"
#include "GameWorld.h"
#include "WOWProxy.h"
#include "AuthLoader.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

static      int         gLogicPackIndex = 0;
int GetLogicPackIndex()
{
	return	gLogicPackIndex;
}

void SetLogicPackIndex(int index)
{
	gLogicPackIndex = index;
}

void AddLogicPackIndex()
{
	gLogicPackIndex++;
}

static      PackageContainerManager     *gPackageContainerManager = NULL;
PackageContainerManager     *       GetPackageContainerManager()
{
    if(!gPackageContainerManager)
    {
        gPackageContainerManager = new PackageContainerManager();
    }
    return      gPackageContainerManager;
}

PackageContainer::PackageContainer(PackageDispatcher   * sendDispatcher, PackageDispatcher   * recvDispatcher, int packetContainerIndex) : m_All(false),
					m_Recv(false), m_Send(false),
                    m_RecvFilter(false),
                    m_SendFilter(false),
                    m_AllFilter(false)
{
    m_PackageContainerIndex = packetContainerIndex;
    m_SendPackageDispatcher = sendDispatcher;
    m_RecvPackageDispatcher = recvDispatcher;
    m_SendPackageDispatcher->fpOnGetPacket = OnGetSendWOWPack;
    m_RecvPackageDispatcher->fpOnGetPacket = OnGetRecvWOWPack;

    m_SendPackageDispatcher->SetPackageContainerIndex(m_PackageContainerIndex);
    m_RecvPackageDispatcher->SetPackageContainerIndex(m_PackageContainerIndex);

    m_EnableFilter = false;
	m_ReverseFilter = false;
	m_CreatureFilter = false;
	m_ForbiddenSend = false;
}

PackageContainer::~PackageContainer()
{
}

String					PackageContainer::GetSaveFilterName()
{
	String path = ExtractFilePath(Application->ExeName);
	String name = path + "filter.txt";
	return		name;
}

void					PackageContainer::LoadFilter()
{
	String name = GetSaveFilterName();

	if(!FileExists(name))
	{
		return;
	}

	auto_ptr<TStringList>	saveStr(new TStringList);
	auto_ptr<TStringList>	splitStr(new TStringList);
	saveStr->LoadFromFile(name);
	FilterType * curFilterType;
	for(int i=0; i<saveStr->Count; i++)
	{
		splitStr->Clear();
		SplitStr(saveStr->Strings[i], "\t", splitStr.get());
		curFilterType = new FilterType;
		if (splitStr->Count > 0)
		{
			curFilterType->Opcode = splitStr->Strings[0].ToIntDef(0);
		}
		if (splitStr->Count > 1)
		{
			curFilterType->Guid = StrToUint64Def(splitStr->Strings[1], 0);
		}
		m_FilterOpcode.Add(curFilterType);
	}
}

void					PackageContainer::SaveFilter()
{
	String name = GetSaveFilterName();

	auto_ptr<TStringList>	saveStr(new TStringList);
	for(int i=0; i<m_FilterOpcode.Count(); i++)
	{
		saveStr->Add(FormatStr("%s\t%s", String(m_FilterOpcode[i]->Opcode), String(m_FilterOpcode[i]->Guid)));
	}
	saveStr->SaveToFile(name);
}

bool                    PackageContainer::FindFilterOpcode(int opcode, uint64 guid)
{
    for(int i=0; i<m_FilterOpcode.Count(); i++)
	{
		if(m_FilterOpcode[i]->Opcode != opcode)
			continue;
		if(m_FilterOpcode[i]->Guid == 0)
			return  true;
		if(m_FilterOpcode[i]->Guid == guid)
			return true;
	}
    return false;
}

void                    PackageContainer::AddFilterOpcode(int opcode, uint64 guid)
{
    if(FindFilterOpcode(opcode, guid))
        return;

    FilterType  * curFilter = new FilterType;
	curFilter->Opcode = opcode;
	curFilter->Guid = guid;
	m_FilterOpcode.Add(curFilter);
	SaveFilter();
}

bool					PackageContainer::NeedHidePackage(WOWPackage *	packet)
{
	if(packet->GetNotShowInGui())
	{
		return true;
	}
	return HideFilterOpcode(packet->GetOpCode(), packet->GetGuid());
}

bool					PackageContainer::HideFilterOpcode(int opcode, uint64 guid)
{
	if(!m_EnableFilter)
		return false;

	bool result = FindFilterOpcode(opcode, guid);
	if(!m_ReverseFilter && result)
	{
		return true;
	}
	else if(m_ReverseFilter && !result)
	{
		return true;
	}

	if(m_CreatureFilter && guid)
	{
		if(IS_CREATURE_GUID(guid))
			return true;
	}
	return false;
}

void                    PackageContainer::AddPackToFilter(AList<WOWPackage> * source, AList<WOWPackage> * dest)
{
	dest->Clear();
	for(int i=0; i<source->Count(); i++)
	{
		if(NeedHidePackage(source->At(i)))
		{
			continue;
		}

        dest->Add(source->At(i));
    }
}

void                    PackageContainer::RefreshFilter()
{
    AddPackToFilter(&m_Recv, &m_RecvFilter);
    AddPackToFilter(&m_Send, &m_SendFilter);
    AddPackToFilter(&m_All, &m_AllFilter);
}

void                    PackageContainer::OnGetSendWOWPack(WOWPackage *	packet)
{
    WOWPackage *	curPack = new WOWPackage;
    curPack->Assign(packet);
    curPack->SetPacketProxyIndex(this->GetPackageContainerIndex());
	curPack->SetIndex(gLogicPackIndex);
	gLogicPackIndex++;

	GetPackageContainerManager()->AddAllWOWPackage(curPack);
}

void                    PackageContainer::OnGetRecvWOWPack(WOWPackage *	packet)
{
	WOWPackage *	curPack = new WOWPackage;
	curPack->Assign(packet);
    curPack->SetPacketProxyIndex(this->GetPackageContainerIndex());
	curPack->SetIndex(gLogicPackIndex);
	gLogicPackIndex++;
	GetPackageContainerManager()->AddAllWOWPackage(curPack);

	if(curPack->GetPacketProxyType() == PROXY_TYPE_REALM)
	{
		int a=0;
	}
}

void                    PackageContainer::ClearPackageContainer()
{
    m_Recv.Clear();
    m_Send.Clear();
    m_All.Clear();
    GetGameWorld()->SetCurrentProcessIndex(0);
}

void                    PackageContainer::GetPack(WOWPackage * packet)
{
    ASSERT(packet)
    ASSERT(m_SendPackageDispatcher)
	ASSERT(m_RecvPackageDispatcher)

//	if(packet->GetMark() == SEND_MARK)
//	{
//		GetLog()->Info("[%s]Pack(%s) : %s", this->GetName(), packet->GetMark(), BinToStr(packet->GetOrgData().c_str(), packet->GetOrgData().Length()));
//	}

    if(GetGameWorld()->GetEnableShowOrgPacket())
    {
        GetLog()->Info("[%s]Pack(%s) : %s", this->GetName(), packet->GetMark(), BinToStr(packet->GetOrgData().c_str(), packet->GetOrgData().Length()));
    }

	if(packet->GetMark() == SEND_MARK)
	{
		m_SendPackageDispatcher->GetOrignSendPacket(packet);
	}
	else if(packet->GetMark() == RECV_MARK)
	{
		m_RecvPackageDispatcher->GetOrignRecvPacket(packet);
	}
}
////////////////////////////////////////////////////////////////////////////////////

PackageContainerManager::PackageContainerManager() : m_AuthPackageContainer(&m_SendAuthPackageDispatcher, &m_RecvAuthPackageDispatcher, 0)
{
    m_AuthPackageContainer.SetName("Auth");
    AddWorldPackageContainer();
}

PackageContainerManager::~PackageContainerManager()
{
}

void                        PackageContainerManager::AddWorldPackageContainer()
{
	LOLPackageDispatcher *send = new LOLPackageDispatcher;
    LOLPackageDispatcher *recv = new LOLPackageDispatcher;
    PackageContainer *c = new PackageContainer(send, recv, m_WorldPackageContainer.Count());
    c->SetName(FormatStr("World%d", m_WorldPackageContainer.Count()));
    m_WorldPackageContainer.Add(c);
    m_SendWorldPackageDispatcher.Add(send);
    m_RecvWorldPackageDispatcher.Add(recv);
}

void                        PackageContainerManager::ProcessClientMessage(int forcemove, int processCnt, int toIndex)
{
	if(GetWOWProxyManager()->GetDirectModel())
	{
		return;
	}
    int processTotal = 0;

    WOWPackage * curWOWPackage = NULL;

	int     processIndex = 0;

	for(int i=0; i<GetPackageContainerManager()->GetAllPackage()->Count(); i++)
	{
		curWOWPackage = GetPackageContainerManager()->GetAllPackage()->At(i);
		if(curWOWPackage->GetForceSend())
		{
			ProcessOneClientMessage(curWOWPackage);
		}
	}

//	//处理心跳包
//	for(int i=0; i<GetPackageContainerManager()->GetAllPackage()->Count(); i++)
//	{
//		curWOWPackage = GetPackageContainerManager()->GetAllPackage()->At(i);
//		if(curWOWPackage->GetProcessed())
//			continue;
//		if(curWOWPackage->GetMark() != SEND_MARK)
//		{
//			continue;
//		}
//		if(curWOWPackage->GetPacketProxyType() != PROXY_TYPE_WORLD)
//		{
//			//REALM封包直接pass
//			ProcessOneClientMessage(curWOWPackage);
//			continue;
//		}
//		if(curWOWPackage->GetOrgData().c_str()[4] == 0x5C)
//		{
//			ProcessOneClientMessage(curWOWPackage);
//		}
//	}

	for(int i=0; i<GetPackageContainerManager()->GetAllPackage()->Count(); i++)
	{
		if(curWOWPackage->GetIndex() == GetGameWorld()->GetCurrentProcessIndex())
		{
			processIndex = i;
			break;
		}
	}

	for(; processIndex<GetPackageContainerManager()->GetAllPackage()->Count(); processIndex++)
	{
		curWOWPackage = GetPackageContainerManager()->GetAllPackage()->At(processIndex);
		if(curWOWPackage->GetProcessed())
			continue;

		if(curWOWPackage->GetPacketProxyType() == PROXY_TYPE_WORLD)
		{
			PackageContainer * worldPackageContainer = GetPackageContainerManager()->GetWorldPackageContainer(curWOWPackage->GetPacketProxyIndex());
			if(!worldPackageContainer->NeedHidePackage(curWOWPackage))
			{
				// Can Process
				if(forcemove == 0 && GetGameWorld()->GetBlockMode())
				{
					// Block 加了过滤模式, 所以在这里检查Block
					if(!GetGameWorld()->GetBlockOnlyMode())
					{
						return;
					}
					else
					{
						continue;
					}
				}
			}
		}

        if(!ProcessOneClientMessage(curWOWPackage))
        {
            continue;
		}

        processTotal++;
        if(processCnt != -1 && processTotal >= processCnt)
        {
            break;
        }

        if(curWOWPackage->GetIndex() == toIndex)
        {
            break;
        }
    }
}

bool                        PackageContainerManager::ProcessOneClientMessage(WOWPackage * curWOWPackage)
{
	WOWProxy * curWOWProxyWorld = NULL;
	if(curWOWPackage->GetPacketProxyType() == PROXY_TYPE_REALM)
	{
		curWOWProxyWorld = GetWOWProxyManager()->GetActiveRealmd(curWOWPackage->GetPacketProxyIndex());
		if(!curWOWProxyWorld)
		{
			return false;
		}
		curWOWPackage->SetProcessed(1);
		shared_ptr<WOWPackage> newWOWPackage(new WOWPackage);
		newWOWPackage->Assign(curWOWPackage);
		if(newWOWPackage->GetMark() == SEND_MARK)
		{
			curWOWProxyWorld->GetClientToServerQueue()->Push(newWOWPackage);
		}
		else    if(newWOWPackage->GetMark() == RECV_MARK)
		{
			curWOWProxyWorld->GetServerToClientQueue()->Push(newWOWPackage);
		}
		return true;
	}
	curWOWProxyWorld = GetWOWProxyManager()->GetActiveWorld(curWOWPackage->GetPacketProxyIndex());
    if(!curWOWProxyWorld)
    {
        GetLog()->Warn("No world:%d", curWOWPackage->GetPacketProxyIndex());
		return false;
    }

	PackageContainer * worldPackageContainer = GetPackageContainerManager()->GetWorldPackageContainer(curWOWPackage->GetPacketProxyIndex());
	if(curWOWPackage->GetProcessed())
		return false;

	if(GetGameWorld()->IsPacketForbidden(curWOWPackage->GetOpCodeMsg()))
	{
		curWOWPackage->SetProcessed(-1);
		return false;
	}


    curWOWPackage->SetProcessed(1);
    shared_ptr<WOWPackage> newWOWPackage(new WOWPackage);
    newWOWPackage->Assign(curWOWPackage);

	newWOWPackage->SetOrgPrefixData(newWOWPackage->GetOrgData());
    if(newWOWPackage->GetMark() == SEND_MARK)
    {
//        if(newWOWPackage->GetData() != newWOWPackage->GetOrgData())
//        {
//            newWOWPackage->ClientToServerEncrypt();
//		}
		curWOWProxyWorld->GetClientToServerQueue()->Push(newWOWPackage);
	}
	else    if(newWOWPackage->GetMark() == RECV_MARK)
	{
//		if(newWOWPackage->GetData() != newWOWPackage->GetOrgData())
//		{
//			newWOWPackage->ServerToClientEncrypt();
//		}
//		GetLog()->Warn("Push : %s", newWOWPackage->GetOpCodeMsg());
        curWOWProxyWorld->GetServerToClientQueue()->Push(newWOWPackage);
	}

	GetGameWorld()->SetCurrentProcessIndex(curWOWPackage->GetIndex());
	if(worldPackageContainer->NeedHidePackage(curWOWPackage))
	{
		return false;
	}

	return  true;
}


void                    PackageContainerManager::PopQueue(ASharedPtrQueue<WOWPackage> * packetQueue)
{
	shared_ptr<WOWPackage>  packet;
	while(!packetQueue->IsEmpty())
	{
		if(!packetQueue->Pop(&packet))
			return;

		PackageContainer * curPackageContainer = NULL;
		if(packet->GetPacketProxyType() == PROXY_TYPE_REALM)
		{
			curPackageContainer = this->GetAuthPackageContainer();
		}
		else if(packet->GetPacketProxyType() == PROXY_TYPE_WORLD)
		{
			curPackageContainer = this->GetWorldPackageContainer(packet->GetPacketProxyIndex());
		}
		else
		{
			GetLog()->Error("packet->GetPacketProxyType() = %d", packet->GetPacketProxyType());
			WY_ASSERT(packet->GetPacketProxyType() == PROXY_TYPE_WORLD);
		}
		if(!curPackageContainer)
		{
            GetLog()->Warn("No PackageContainer. index = %d", packet->GetPacketProxyIndex());
			continue;
		}
		curPackageContainer->GetPack(packet.get());
	}
}

void						PackageContainerManager::AddAllWOWPackage(WOWPackage *packet)
{
	PackageContainer * curPackageContainer = NULL;
	if(packet->GetPacketProxyType() == PROXY_TYPE_REALM)
	{
		curPackageContainer = this->GetAuthPackageContainer();
	}
	else if(packet->GetPacketProxyType() == PROXY_TYPE_WORLD)
	{
		curPackageContainer = this->GetWorldPackageContainer(packet->GetPacketProxyIndex());
	}
	else
	{
		GetLog()->Error("packet->GetPacketProxyType() = %d", packet->GetPacketProxyType());
		WY_ASSERT(packet->GetPacketProxyType() == PROXY_TYPE_WORLD);
	}

	if(packet->GetMark() == SEND_MARK)
	{
		curPackageContainer->GetSend()->Add(packet);
	}
	else if (packet->GetMark() == RECV_MARK)
	{
		curPackageContainer->GetRecv()->Add(packet);
	}
	else
	{
		GetLog()->Error("packet->GetMark() = %s", packet->GetMark());
		WY_ASSERT(packet->GetMark() == RECV_MARK);
	}
	curPackageContainer->GetAll()->Add(packet);

	m_AllPackage.Add(packet);

	if(packet->GetPacketProxyType() == PROXY_TYPE_REALM)
	{
		GetGameWorld()->HandlerAuthPacket(packet);
	}
	else if(packet->GetPacketProxyType() == PROXY_TYPE_WORLD)
	{
		GetGameWorld()->HandlerPacket(packet);
	}
}

void						PackageContainerManager::ClearAllPackage()
{
	GetAuthPackageContainer()->ClearPackageContainer();
    for(int i=0; i<m_WorldPackageContainer.Count(); i++)
    {
    	m_WorldPackageContainer[i]->ClearPackageContainer();
    }
	m_AllPackage.Clear();
}

PackageContainer    *       PackageContainerManager::GetWorldPackageContainer(int index)
{
    while(index >= m_WorldPackageContainer.Count())
    {
        AddWorldPackageContainer();
    }
    return m_WorldPackageContainer[index];
}

int                         PackageContainerManager::GetWorldPackageContainerCount()
{
    return m_WorldPackageContainer.Count();
}

PackageContainer    *       PackageContainerManager::GetDefaultWorldPackageContainer()
{
    return m_WorldPackageContainer[m_WorldPackageContainer.Count() - 1];
}

void                        PackageContainerManager::FreeWorldPackageContainer()
{
    m_WorldPackageContainer.Clear();
    m_SendWorldPackageDispatcher.Clear();
    m_RecvWorldPackageDispatcher.Clear();
    AddWorldPackageContainer();
}
