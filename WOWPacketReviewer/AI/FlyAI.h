//---------------------------------------------------------------------------

#ifndef FlyAIH
#define FlyAIH
//---------------------------------------------------------------------------

#include <VCL.h>
#include "GameWorld.h"
#include "FiberContext.h"

class FlyAI : public FiberProcesser
{
private:
	bool			m_ActiveSetting;
public:
	FlyAI();
	~FlyAI();
	void        OnProcess();
	GEN_GET_SET(bool, ActiveSetting);
};


class SpeedChangeAI : public FiberProcesser
{
private:
	bool			m_ActiveSetting;
public:
	SpeedChangeAI();
	~SpeedChangeAI();
	void        OnProcess();
	GEN_GET_SET(bool, ActiveSetting);
};

class WaterWalkingAI : public FiberProcesser
{
private:
	bool			m_ActiveSetting;
public:
	WaterWalkingAI();
	~WaterWalkingAI();
	void        OnProcess();
	GEN_GET_SET(bool, ActiveSetting);
};

#endif
