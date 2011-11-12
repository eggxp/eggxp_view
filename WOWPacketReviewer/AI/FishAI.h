//---------------------------------------------------------------------------

#ifndef FishAIH
#define FishAIH
//---------------------------------------------------------------------------
#include <VCL.h>
#include "GameWorld.h"
#include "FiberContext.h"

class FishAI : public FiberProcesser
{
private:
    void        SendStartFish();
	DWORD       m_ActiveTick;
	bool		m_IsStop;
public:
    FishAI();
    ~FishAI();
    int         GetFishSpellID();
    void        OnProcess();
	bool        IsFishSpellID(DWORD spellid);
	void		ActiveAI(int err = 0);
	void		PauseAI();
	void		StopAI(bool showMsg);
	bool		GetIsStop(){return	m_IsStop;}
};

#endif
