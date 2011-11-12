//---------------------------------------------------------------------------


#pragma hdrstop

#include "FishAI.h"
#include "FiberCode.h"
#include "ByteBuffer.h"
#include "ThreadManager.h"
#include "DBCStores.h"
#include "ShareDef.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


#define     KEEP_ACTIVE_TICK        1000*60*4

FishAI::FishAI()
{
    this->SetName("FishAI");
	m_ActiveTick = 0;
	m_IsStop = 0;
}

FishAI::~FishAI()
{
}

void        FishAI::SendStartFish()
{
    if(GetTickCount() - m_ActiveTick >= KEEP_ACTIVE_TICK)
    {
        m_ActiveTick = GetTickCount();
		SendMessage(GetGameWorld()->GetWOWWindowHandle(), WM_KEYDOWN, VK_SPACE, 0);
        SendMessage(GetGameWorld()->GetWOWWindowHandle(), WM_KEYUP, VK_SPACE, 0);
        this->FiberSleep(2000);
    }
    
    int spell_id = GetFishSpellID();
    //使用钓鱼技能
    GetGameWorld()->GetPackSender()->SendCastSpell(spell_id);
}

bool        FishAI::IsFishSpellID(DWORD spellid)
{
	const  SpellEntry * curSpellEntry = GetSpellStore()->LookupEntry(spellid);

	if(!curSpellEntry)
	{
		return  false;
	}

	if(curSpellEntry->Attributes != 402980880)
	{
		return false;
	}

	return true;
}

int         FishAI::GetFishSpellID()
{
	shared_ptr<DataObject>  dataObj = GetGameWorld()->GetDataByKey("self/spell");
	for (int i=0; i<dataObj->GetChildCount(); i++)
	{
		int spellID = dataObj->GetAt(i)->GetKeyName().ToIntDef(0);
		if(IsFishSpellID(spellID))
		{
			return spellID;
		}
	}
    return  0;
}

//初级：.learn 7620
//中级：.learn 7731
//高级：.learn 7732
//专家：.learn 18248
//大师：.learn 33095

void        FishAI::OnProcess()
{
	int ret = 0;
	if(!this->WaitFor(FWC_FISH_AI_START, "FWC_FISH_AI_START", 0))
	{
		//如果是用户触发钓鱼的话, 不发出第一个钓鱼封包
		ret = this->GetErrorCode();
	}
	if(!m_IsStop)
	{
		GetThreadManager()->AddGUIMessage(GBText("开始自动钓鱼!"));
	}
	else
	{
		return;
	}
    m_ActiveTick = GetTickCount();
    this->SetActive(1);
	int failTime = 0;
    while(this->GetActive())
	{
		if(ret != FEC_USER_USE_SKILL)
		{
			SendStartFish();
		}
		ret = 0;
		if(!this->WaitFor(FWC_FISH_HOOK, "FWC_FISH_HOOK"))
		{
			if(failTime > 3)
			{
				//3次失败强制中断
				this->SetActive(0);
			}
			if(this->GetErrorCode() == FEC_SPELL_FAIL)
			{
				this->FiberSleep(2000);
				failTime++;
			}
			continue;
		}
		failTime = 0;
        uint64 guid = GetGameWorld()->GetDataGUID("self/fish/fishobjl", "self/fish/fishobjh");
        GetGameWorld()->GetPackSender()->SendUseGameObject(guid);
        GetGameWorld()->GetPackSender()->SendReportUseGameObject(guid);
        if(!this->WaitFor(FWC_WAIT_LOOT, "FWC_WAIT_LOOT"))
            continue;
        for(int i=0; i<GetGameWorld()->GetDataInt("self/loot/count"); i++)
        {
            int itemid = GetGameWorld()->GetDataInt(FormatStr("self/loot/items/%d/itemid", i));
			int itemcount = GetGameWorld()->GetDataInt(FormatStr("self/loot/items/%d/count", i));
			int itemIndex = GetGameWorld()->GetDataInt(FormatStr("self/loot/items/%d/index", i));
//            String name = GetGameWorld()->GetItemNameByID(itemid);
            if(GetGameWorld()->FindItemInPickupList(itemid))
			{
    	        String key = FormatStr("fish_no_pick/%d", itemid);
				GetGameWorld()->SetData(key, GetGameWorld()->GetDataInt(key) + itemcount);
                continue;
            }

			String key = FormatStr("fish_results/%d", itemid);
            GetGameWorld()->SetData(key, GetGameWorld()->GetDataInt(key) + itemcount);
            GetGameWorld()->GetPackSender()->SendAutoStoreLootItem(itemIndex);
        }
		GetGameWorld()->RefreshFishResult();
//        this->WaitFor(FWC_WAIT_LOOT_PICK, "FWC_WAIT_LOOT_PICK");
	}
	if(!m_IsStop)
	{
		GetThreadManager()->AddGUIMessage(GBText("结束自动钓鱼!"));
	}
}

void		FishAI::ActiveAI(int err)
{
	if(m_IsStop)
	{
		return;
	}
	GetFiberManager()->Awake(FWC_FISH_AI_START, err);
}

void		FishAI::PauseAI()
{
	this->SetActive(0);
	this->ForceAwake();
}

void		FishAI::StopAI(bool showMsg)
{
	if(showMsg)
		GetThreadManager()->AddGUIMessage(GBText("你的有效时间已到, 请续费!"));
	m_IsStop = 1;
	PauseAI();
}
