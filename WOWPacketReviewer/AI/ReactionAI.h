//---------------------------------------------------------------------------

#ifndef ReactionAIH
#define ReactionAIH
//---------------------------------------------------------------------------

#include <VCL.h>
#include "GameWorld.h"
#include "FiberContext.h"

class ReactionAI : public FiberProcesser
{
private:
    void        SendDZZhaoJia();
	DWORD       m_ActiveTick;
public:
    ReactionAI();
    ~ReactionAI();
    int         HaveDZZhaoJiaSpellID();
    void        OnProcess();
    bool        IsFishSpellID(DWORD spellid);
};


#endif
