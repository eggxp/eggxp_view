//---------------------------------------------------------------------------


#pragma hdrstop

#include "AutoChatAI.h"
#include "DBCStructure.h"
#include "DBCStores.h"
#include "KOEItlbm.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

AutoChatAI::AutoChatAI()
{
    this->SetName("AutoChatAI");
    m_ActiveTick = 0;
}

AutoChatAI::~AutoChatAI()
{
}

void		AutoChatAI::InitAreas()
{
	for(DWORD i=0; i<GetAreaTableStore()->GetRecordCount(); i++)
	{
		const	AreaTableEntry *area = GetAreaTableStore()->LookupByIndex(i);
		if(area->flags != 2097216 && area->flags != 2097464 && area->area_level != 0)
			continue;

		tagAreaChatAIResult areaResult;
		areaResult.AreaName = AnsiUTF8BIGDataToUnicodeGB(area->area_name[5], strlen(area->area_name[5]));
		String testStr = areaResult.AreaName.UpperCase();
		if(testStr.Pos("TEST") != 0)
			continue;
		if(testStr.Pos("USE") != 0)
			continue;
		if(testStr.Pos("GM") != 0)
			continue;
		if(testStr.Pos("JEFF") != 0)
			continue;
		if(testStr.Pos("K3") != 0)
			continue;
		if(testStr.Pos("NINE") != 0)
			continue;
		if(testStr.Pos("DELETE") != 0)
			continue;
		m_AreaChatAIResult[areaResult.AreaName] = areaResult;
	}
}

void        AutoChatAI::OnProcess()
{
	this->WaitFor(FWC_WAIT_AUTO_CHAT_START, "FWC_WAIT_AUTO_CHAT_START", 0);
	this->SetActive(1);
	InitAreas();
	while(this->GetActive())
	{
		for(map<String, tagAreaChatAIResult>::iterator it = m_AreaChatAIResult.begin();
			it != m_AreaChatAIResult.end(); it++)
		{
			if(!this->GetActive())
				break;

			if(it->second.ProcessCount - it->second.PlayerCount > 5)
				continue;

			GetGameWorld()->GetPackSender()->SendWho(it->first, 0, 100);
			map<String, tagWhoPlayerInfo>   *result = GetGameWorld()->GetPlayerHandler()->GetWhoInfo();
			result->clear();
			int ret = 0;
			if(!this->WaitFor(FWC_WAIT_AUTO_CHAT_WHO, "FWC_WAIT_AUTO_CHAT_WHO", 5000))
			{
				ret = this->GetErrorCode();
			}

			if(ret == FEC_TIMEOUT)
			{
				it->second.Expired = 1;
			}
			else
			{
				for(map<String, tagWhoPlayerInfo>::iterator mit = result->begin();
					mit != result->end(); mit++)
				{
					m_AreaPlayerWhoInfo[mit->first] = mit->second;
					tagWhoPlayerInfo *whoInfo = &m_AreaPlayerWhoInfo[mit->first];
					if(!m_SendText.IsEmpty() && (GetTickCount() - whoInfo->MiTick >= 1000*60*60*2))
					{
						GetGameWorld()->GetPackSender()->SendChatMi(mit->second.Player_Name, m_SendText);
						whoInfo->MiTick = GetTickCount();
						this->FiberSleep(100);
					}
				}
				it->second.ProcessCount++;
				it->second.PlayerCount = result->size();
				this->FiberSleep(5000);
			}
		}
	}
	this->SetActive(0);
}
