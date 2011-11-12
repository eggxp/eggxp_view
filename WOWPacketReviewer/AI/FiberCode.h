//---------------------------------------------------------------------------

#ifndef FiberCodeH
#define FiberCodeH
//---------------------------------------------------------------------------
#include "FiberContext.h"

enum    TFiberWaitCode
{
	// Fish AI
    FWC_FISH_AI_START = FWC_USER,
    FWC_CAST_FISH_SPELL,
    FWC_FISH_HOOK,
    FWC_WAIT_LOOT,
	FWC_WAIT_LOOT_PICK,

	//ReactionAI
	FWC_REACTION_START,
	FWC_REACTION,

	FWC_WAIT_SHOW_ALL_MAP,
	//AutoChatAI
	FWC_WAIT_AUTO_CHAT_START,
	FWC_WAIT_AUTO_CHAT_WHO,

	//FlyAI
	FWC_WAIT_FLY_AI_START,
	FWC_WAIT_FLY_ACK,

	FWC_WAIT_RUN_SPEED_CHANGE_AI_START,
	FWC_WAIT_RUN_SPEED_CHANGE_ACK,

	// waterwalking ai
	FWC_WAIT_WATER_WALKING_AI_START,
	FWC_WAIT_WATER_WALKING_ACK,
	FWC_WAIT_WATER_WALKING_MOVEMENT_OPCODE
};

enum	TFiberErrorCode
{
	FEC_SPELL_FAIL = FEC_USER,
	FEC_USER_USE_SKILL,

	//Reaction AI
	FEC_DZ_ZHAOJIA
};



#endif
