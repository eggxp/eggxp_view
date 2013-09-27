//---------------------------------------------------------------------------


#pragma hdrstop

#include "EventHandler.h"
#include "GameWorld.h"
#include "SharedDefine.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

EventHandler::EventHandler(GameWorld * gameWorld)
{
    m_GameWorld = gameWorld;
//	REG_HANDLER(SMSG_GOSSIP_MESSAGE)
//	REG_HANDLER(SMSG_NPC_TEXT_UPDATE)
//	REG_HANDLER(SMSG_GOSSIP_POI)
}

EventHandler::~EventHandler()
{
}

void    EventHandler::Handler_SMSG_GOSSIP_MESSAGE(WOWPackage * packet)
{
	int pos = 0;
	READ_UINT64(objectGUID)
	READ_DWORD(MenuId)
	READ_DWORD(TitleTextId)
	READ_DWORD(GossipMenuItemCount)
	for(DWORD i=0; i<GossipMenuItemCount; i++)
	{
		READ_DWORD(iI)
		READ_BYTE(m_gIcon)
		READ_BYTE(m_gCoded)
		READ_DWORD(m_gBoxMoney)
		READ_STRING(m_gMessage)
		READ_STRING(m_gBoxMessage)
	}

	READ_DWORD(QuestMenuItemCount)
	for(DWORD i=0; i<QuestMenuItemCount; i++)
	{
		READ_DWORD(questID)
		READ_DWORD(m_qIcon)
		READ_DWORD(QuestLevel)
		READ_STRING(Title)
	}
	READ_FINISH
}

void    EventHandler::Handler_SMSG_NPC_TEXT_UPDATE(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(textID)
	for(uint32 i = 0; i < 8; ++i)
	{
		READ_FLOAT(Probability)
		READ_STRING(text0)
		READ_STRING(text1)
		READ_DWORD(Language)
		for(int j = 0; j < 3; ++j)
		{
			READ_DWORD(Delay)
			READ_DWORD(Emote)
		}
	}
	READ_FINISH
}

void    EventHandler::Handler_SMSG_GOSSIP_POI(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(Flags)
	READ_FLOAT(X)
	READ_FLOAT(Y)
	READ_DWORD(Icon)
	READ_DWORD(Data)
	READ_STRING(locName)
	READ_FINISH
}


