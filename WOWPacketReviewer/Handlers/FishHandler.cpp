//---------------------------------------------------------------------------


#pragma hdrstop

#include "FishHandler.h"
#include "GameWorld.h"
#include "SharedDefine.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

FishHandler::FishHandler(GameWorld * gameWorld)
{
    m_GameWorld = gameWorld;
    REG_HANDLER(SMSG_FISH_NOT_HOOKED)
}

FishHandler::~FishHandler()
{
}

void    FishHandler::Handler_SMSG_FISH_NOT_HOOKED(WOWPackage * packet)
{
	int pos = 0;
	READ_FINISH
}

