//---------------------------------------------------------------------------

#ifndef ShowAllMapAIH
#define ShowAllMapAIH
//---------------------------------------------------------------------------

#include <VCL.h>
#include "GameWorld.h"
#include "FiberContext.h"

class ShowAllMapAI : public FiberProcesser
{
private:
	DWORD       m_ActiveTick;
	int			m_MapShowed;
public:
    ShowAllMapAI();
    ~ShowAllMapAI();
    void        OnProcess();
	bool        IsFishSpellID(DWORD spellid);
	GEN_GET_SET(int, MapShowed)
};
#endif
