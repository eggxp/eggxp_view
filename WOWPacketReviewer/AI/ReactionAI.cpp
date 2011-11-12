//---------------------------------------------------------------------------


#pragma hdrstop

#include "ReactionAI.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

static int  gDZ_ZhaoJiaSpellID = 14251;

#define     KEEP_ACTIVE_TICK        1000*60*4

ReactionAI::ReactionAI()
{
    this->SetName("ReactionAI");
    m_ActiveTick = 0;
}

ReactionAI::~ReactionAI()
{
}

int         ReactionAI::HaveDZZhaoJiaSpellID()
{
    shared_ptr<DataObject>  dataObj = GetGameWorld()->GetDataByKey("self/spell");
	if(dataObj->HaveDataObject(gDZ_ZhaoJiaSpellID))
	{
		return 1;
	}
    return  0;
}

void        ReactionAI::SendDZZhaoJia()
{
	uint64 target = GetGameWorld()->GetDataGUID("attacker/guidl", "attacker/guidh");
	GetGameWorld()->GetPackSender()->SendCastSpellTarget(gDZ_ZhaoJiaSpellID, TARGET_FLAG_UNIT, target);
}

void        ReactionAI::OnProcess()
{
	//不启用这个AI了
	return;
//	this->WaitFor(FWC_REACTION_START, "FWC_REACTION_START", 0);
//
//	this->SetActive(1);
//
//	int ret = 0;
//	while(this->GetActive())
//	{
//		if(!this->WaitFor(FWC_REACTION, "FWC_REACTION", 0))
//		{
//			ret = this->GetErrorCode();
//		}
//		if(ret == FEC_DZ_ZHAOJIA)
//		{
//			if(HaveDZZhaoJiaSpellID())
//			{
//				SendDZZhaoJia();
//			}
//		}
//	}
}