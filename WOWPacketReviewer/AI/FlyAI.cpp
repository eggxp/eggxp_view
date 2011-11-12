//---------------------------------------------------------------------------


#pragma hdrstop

#include "FlyAI.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

FlyAI::FlyAI()
{
	this->SetName("FlyAI");
	m_ActiveSetting = false;
}

FlyAI::~FlyAI()
{
}

void        FlyAI::OnProcess()
{
	this->SetActive(1);
	while(this->GetActive())
	{
		this->WaitFor(FWC_WAIT_FLY_AI_START, "FWC_WAIT_FLY_AI_START", 0);
		m_ActiveSetting = true;
		GetGameWorld()->GetPackSender()->SendToClientSetCanFly(GetGameWorld()->GetSelfGUID());
		this->WaitFor(FWC_WAIT_FLY_ACK, "FWC_WAIT_FLY_ACK", 0);
		GetGameWorld()->GetCurrentHandleringWOWPackage()->SetProcessed(-1);

		this->WaitFor(FWC_WAIT_FLY_AI_START, "FWC_WAIT_FLY_AI_START", 0);
		GetGameWorld()->GetPackSender()->SendToClientUnSetCanFly(GetGameWorld()->GetSelfGUID());
		this->WaitFor(FWC_WAIT_FLY_ACK, "FWC_WAIT_FLY_ACK", 0);
		GetGameWorld()->GetCurrentHandleringWOWPackage()->SetProcessed(-1);
		m_ActiveSetting = false;
	}
}

//==============================================================================

SpeedChangeAI::SpeedChangeAI()
{
	this->SetName("SpeedChangeAI");
	m_ActiveSetting = false;
}

SpeedChangeAI::~SpeedChangeAI()
{
}

void        SpeedChangeAI::OnProcess()
{
	this->SetActive(1);
	while(this->GetActive())
	{
		this->WaitFor(FWC_WAIT_RUN_SPEED_CHANGE_AI_START, "FWC_WAIT_RUN_SPEED_CHANGE_AI_START", 0);
		float speed = GetGameWorld()->GetDataFloat("self/speed");
		if(speed == 0)
		{
			speed = 7.0f;
		}
		float rate = 3.0f;
		if(m_ActiveSetting)
		{
			GetGameWorld()->GetPackSender()->SendToClientSetRunSpeedChange(GetGameWorld()->GetSelfGUID(), speed * rate);
			this->WaitFor(FWC_WAIT_RUN_SPEED_CHANGE_ACK, "FWC_WAIT_RUN_SPEED_CHANGE_ACK", 0);
			GetGameWorld()->GetCurrentHandleringWOWPackage()->SetProcessed(-1);
		}
		else
		{
			GetGameWorld()->GetPackSender()->SendToClientSetRunSpeedChange(GetGameWorld()->GetSelfGUID(), speed / rate);
			this->WaitFor(FWC_WAIT_RUN_SPEED_CHANGE_ACK, "FWC_WAIT_RUN_SPEED_CHANGE_ACK", 0);
			GetGameWorld()->GetCurrentHandleringWOWPackage()->SetProcessed(-1);
		}
	}
}

//==============================================================================
WaterWalkingAI::WaterWalkingAI()
{
	this->SetName("WaterWalkingAI");
	m_ActiveSetting = false;
}

WaterWalkingAI::~WaterWalkingAI()
{
}

void        WaterWalkingAI::OnProcess()
{
	this->SetActive(1);
	while(this->GetActive())
	{
		this->WaitFor(FWC_WAIT_WATER_WALKING_AI_START, "FWC_WAIT_WATER_WALKING_AI_START", 0);

		m_ActiveSetting = true;
		GetGameWorld()->GetPackSender()->SendToClientMoveWaterWalk(GetGameWorld()->GetSelfGUID());
		this->WaitFor(FWC_WAIT_WATER_WALKING_ACK, "FWC_WAIT_WATER_WALKING_ACK", 0);
		GetGameWorld()->GetCurrentHandleringWOWPackage()->SetProcessed(-1);
		this->WaitFor(FWC_WAIT_WATER_WALKING_AI_START, "FWC_WAIT_WATER_WALKING_AI_START", 0);
		GetGameWorld()->GetPackSender()->SendToClientMoveLandWalk(GetGameWorld()->GetSelfGUID());
		this->WaitFor(FWC_WAIT_WATER_WALKING_ACK, "FWC_WAIT_WATER_WALKING_ACK", 0);
		GetGameWorld()->GetCurrentHandleringWOWPackage()->SetProcessed(-1);
		m_ActiveSetting = false;
	}
}
