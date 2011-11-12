//---------------------------------------------------------------------------


#pragma hdrstop

#include "ShowAllMapAI.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


ShowAllMapAI::ShowAllMapAI()
{
    this->SetName("ShowAllMapAI");
	m_ActiveTick = 0;
	m_MapShowed = 0;
}

ShowAllMapAI::~ShowAllMapAI()
{
}

void        ShowAllMapAI::OnProcess()
{
	this->SetActive(1);
	while(this->GetActive())
	{
		this->WaitFor(FWC_WAIT_SHOW_ALL_MAP, "FWC_WAIT_SHOW_ALL_MAP", 0);
		GetGameWorld()->GetPackSender()->SendRecvOpenAllMap(GetGameWorld()->GetSelfGUID());
		m_MapShowed = 1;
	}
}