//---------------------------------------------------------------------------


#pragma hdrstop

#include "QuestHandler.h"
#include "GameWorld.h"
#include "SharedDefine.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


QuestHandler::QuestHandler(GameWorld * gameWorld)
{
    m_GameWorld = gameWorld;
//	REG_HANDLER(SMSG_QUESTGIVER_STATUS_MULTIPLE)
//	REG_HANDLER(SMSG_PAGE_TEXT_QUERY_RESPONSE)
//	REG_HANDLER(SMSG_QUESTGIVER_STATUS)
//	REG_HANDLER(SMSG_QUESTGIVER_QUEST_LIST)
//	REG_HANDLER(SMSG_QUESTGIVER_QUEST_DETAILS)
//	REG_HANDLER(SMSG_QUEST_QUERY_RESPONSE)
//	REG_HANDLER(SMSG_QUESTUPDATE_ADD_KILL)
//	REG_HANDLER(SMSG_QUESTGIVER_OFFER_REWARD)
//	REG_HANDLER(SMSG_QUESTGIVER_REQUEST_ITEMS)
//	REG_HANDLER(CMSG_GOSSIP_HELLO)
//	REG_HANDLER(CMSG_QUESTGIVER_QUERY_QUEST)
//	REG_HANDLER(CMSG_QUESTGIVER_CHOOSE_REWARD)
//	REG_HANDLER(SMSG_QUESTGIVER_QUEST_COMPLETE)
}

QuestHandler::~QuestHandler()
{
}

void    QuestHandler::Handler_SMSG_QUESTGIVER_STATUS_MULTIPLE(WOWPackage * packet)
{
    int pos = 0;
    READ_DWORD(count);
    for(DWORD i=0; i<count; i++)
    {
        READ_UINT64(questgiver_guid);
        READ_BYTE(questStatus);
    }
}

void    QuestHandler::Handler_SMSG_PAGE_TEXT_QUERY_RESPONSE(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(pageID)
	READ_STRING(text)
	READ_DWORD(Next_Page)
	READ_FINISH
}

void    QuestHandler::Handler_SMSG_QUESTGIVER_STATUS(WOWPackage * packet)
{
	int pos = 0;
	READ_UINT64(npcGUID)
	READ_BYTE(questStatus)
	READ_FINISH
}

void    QuestHandler::Handler_SMSG_QUESTGIVER_QUEST_LIST(WOWPackage * packet)
{
	int pos = 0;
	READ_UINT64(npcGUID)
	READ_STRING(Title)
	READ_DWORD(eEmote_Delay)
	READ_DWORD(eEmote_Emote)
	READ_BYTE(MenuItemCount)
	for(int i=0; i<MenuItemCount; i++)
	{
		READ_DWORD(questID)
		READ_DWORD(m_qIcon)
		READ_DWORD(QuestLevel)
		READ_STRING(title)
	}
	READ_FINISH
}

void    QuestHandler::Handler_SMSG_QUESTGIVER_QUEST_DETAILS(WOWPackage * packet)
{
	int pos = 0;
	READ_UINT64(npcGUID)
	READ_UINT64(UBZ1)
	READ_DWORD(QuestId)
	READ_STRING(Title)
	READ_STRING(Details)
	READ_STRING(Objectives)
	READ_BYTE(ActivateAccept)
	READ_DWORD(SuggestedPlayers)
	READ_BYTE(U1)
	READ_BYTE(U2)
	READ_BYTE(U3)
	READ_DWORD(ChoiceItemsCount)
	for(DWORD i=0; i<ChoiceItemsCount; i++)
	{
		READ_DWORD(RewChoiceItemId)
		READ_DWORD(RewChoiceItemCount)
		READ_DWORD(DisplayInfoID)
	}
	READ_DWORD(RewItemsCount)
	for(DWORD i=0; i<RewItemsCount; i++)
	{
		READ_DWORD(RewItemId)
		READ_DWORD(RewItemCount)
		READ_DWORD(DisplayInfoID)
	}
	READ_DWORD(RewOrReqMoney)
	READ_DWORD(XPValue)
	READ_DWORD(Honor)
	READ_FLOAT(U_F)
	READ_DWORD(RewSpell)
	READ_DWORD(RewSpellCast)
	READ_DWORD(CharTitleId)
	READ_DWORD(BonusTalents)
	READ_DWORD(BZ1)
	READ_DWORD(BZ2)

	for(int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)
	{
		READ_DWORD(Z1);
	}

	for(int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)
	{
		READ_DWORD(Z2);
	}

	for(int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)
	{
		READ_DWORD(Z3);
	}

	READ_DWORD(Quest_Emote_Count)
	for(DWORD i=0; i<Quest_Emote_Count; i++)
	{
		READ_DWORD(DetailsEmote)
		READ_DWORD(DetailsEmoteDelay)
	}
	READ_FINISH
}

void    QuestHandler::Handler_SMSG_QUEST_QUERY_RESPONSE(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(QuestId)
	READ_DWORD(QuestMethod)
	READ_DWORD(QuestLevel)
	READ_DWORD(MinLevel)
	READ_DWORD(ZoneOrSort)
	READ_DWORD(QuestType)
	READ_DWORD(SuggestedPlayers)
	READ_DWORD(RepObjectiveFaction)
	READ_DWORD(RepObjectiveValue)
	READ_DWORD(Z1)
	READ_DWORD(Z2)
	READ_DWORD(NextQuestInChain)
	READ_DWORD(RewXPId)
	READ_DWORD(RewOrReqMoney)
	READ_DWORD(RewMoneyMaxLevel)
	READ_DWORD(RewSpell)
	READ_DWORD(RewSpellCast)
	READ_DWORD(Honor)
	READ_FLOAT(F1)
	READ_DWORD(SrcItemId)
	READ_DWORD(Flags)
    packet->AddComment("Flags", GetQuestFlags(Flags));
	READ_DWORD(CharTitleId)
	READ_DWORD(PlayersSlain)
	READ_DWORD(BonusTalents)
	READ_DWORD(Z3)
	READ_DWORD(Z4)
	for(int i=0; i<QUEST_REWARDS_COUNT; i++)
	{
		READ_DWORD(RewItemId)
		READ_DWORD(RewItemCount)
	}
	for(int i=0; i<QUEST_REWARD_CHOICES_COUNT; i++)
	{
		READ_DWORD(RewChoiceItemId)
		READ_DWORD(RewChoiceItemCount)
	}
	for(int iI = 0; iI < QUEST_REPUTATIONS_COUNT; ++iI)         // reward factions ids
	{
		READ_DWORD(RewRepFaction);
	}

	for(int iI = 0; iI < QUEST_REPUTATIONS_COUNT; ++iI)         // column index in QuestFactionReward.dbc?
	{
		READ_DWORD(RewRepValueId);
	}

	for(int iI = 0; iI < QUEST_REPUTATIONS_COUNT; ++iI)         // reward reputation override?
	{
		READ_DWORD(BZ3);
	}

	READ_DWORD(PointMapId)
	READ_FLOAT(PointX)
	READ_FLOAT(PointY)
	READ_DWORD(PointOpt)
	READ_STRING(Title)
	READ_STRING(Objectives)
	READ_STRING(Details)
	READ_STRING(EndText)
	READ_STRING(CompletedText)
	for(int i=0; i<QUEST_OBJECTIVES_COUNT; i++)
	{
		READ_DWORD(ReqCreatureOrGOId)
		READ_DWORD(ReqCreatureOrGOCount)
		READ_DWORD(ReqSourceId)
		READ_DWORD(ReqZ)
	}
	for(int i=0; i<QUEST_ITEM_OBJECTIVES_COUNT; i++)
	{
		READ_DWORD(ReqItemId)
		READ_DWORD(ReqItemCount)
	}
	for(int i=0; i<QUEST_OBJECTIVES_COUNT; i++)
	{
		READ_STRING(ObjectiveText)
	}
	READ_FINISH
}

void    QuestHandler::Handler_SMSG_QUESTUPDATE_ADD_KILL(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(QuestId)
	READ_DWORD(entry)
	READ_DWORD(old_count)
	READ_DWORD(add_count)
	READ_DWORD(ReqCreatureOrGOCount)
	READ_UINT64(guid)
	READ_FINISH
}

void    QuestHandler::Handler_SMSG_QUESTGIVER_OFFER_REWARD(WOWPackage * packet)
{
	int pos = 0;
	READ_UINT64(npcGUID)
	READ_DWORD(QuestId)
	READ_STRING(Title)
	READ_STRING(OfferRewardText)
	READ_BYTE(EnableNext)
	READ_DWORD(UZero)
	READ_DWORD(EmoteCount)
	for (uint32 i = 0; i < EmoteCount; ++i)
	{
		READ_DWORD(OfferRewardEmoteDelay)
		READ_DWORD(OfferRewardEmote)
	}
	READ_DWORD(RewChoiceItemsCount)
	for (uint32 i = 0; i < RewChoiceItemsCount; i++)
	{
		READ_DWORD(RewChoiceItemId)
		READ_DWORD(RewChoiceItemCount)
		READ_DWORD(DisplayInfoID)
	}
	READ_DWORD(RewItemsCount)
	for (uint32 i = 0; i < RewItemsCount; i++)
	{
		READ_DWORD(RewItemId)
		READ_DWORD(RewItemCount)
		READ_DWORD(DisplayInfoID)
	}
	READ_DWORD(RewOrReqMoney)
	READ_DWORD(XPValue)
	READ_DWORD(Honor)
	READ_FLOAT(FZero)
	READ_DWORD(U8);
	READ_DWORD(RewSpell)
	READ_DWORD(RewSpellCast)
	READ_DWORD(CharTitleId)
	READ_DWORD(BonusTalents)
	READ_DWORD(U1)
	READ_DWORD(U2)
	for(int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)
	{
		READ_DWORD(uz)
	}
	for(int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)
	{
		READ_DWORD(uz)
	}
	for(int i = 0; i < QUEST_REPUTATIONS_COUNT; ++i)
	{
		READ_DWORD(uz)
	}
	READ_FINISH
}

void    QuestHandler::Handler_SMSG_QUESTGIVER_REQUEST_ITEMS(WOWPackage * packet)
{
	int pos = 0;
	READ_UINT64(npcGUID)
	READ_DWORD(QuestId)
	READ_STRING(Title)
	READ_STRING(RequestItemsText)
	READ_DWORD(Zero)
	READ_DWORD(CompleteOrInCompleteEmote)
	READ_DWORD(CloseOnCancel)
	READ_DWORD(Zero1)
	READ_DWORD(RewOrReqMoney)
	READ_DWORD(ReqItemsCount)
	for(uint32 i=0; i<ReqItemsCount; i++)
	{
		READ_DWORD(ReqItemId)
		READ_DWORD(ReqItemCount)
		READ_DWORD(DisplayInfoID)
	}
	READ_DWORD(Completable_0_or_3)
	READ_DWORD(U0x4)
	READ_DWORD(U0x8)
	READ_DWORD(U0x10)
	READ_FINISH
}

void    QuestHandler::Handler_CMSG_GOSSIP_HELLO(WOWPackage * packet)
{
	int pos = 0;
	READ_UINT64(guid)
	READ_FINISH
}

void    QuestHandler::Handler_CMSG_QUESTGIVER_QUERY_QUEST(WOWPackage * packet)
{
	int pos = 0;
	READ_UINT64(guid)
	READ_DWORD(quest)
	READ_BYTE(unk)
	READ_FINISH
}

void    QuestHandler::Handler_CMSG_QUESTGIVER_CHOOSE_REWARD(WOWPackage * packet)
{
	int pos = 0;
	READ_UINT64(guid)
	READ_DWORD(quest)
	READ_DWORD(reward)
	READ_FINISH
}

void    QuestHandler::Handler_SMSG_QUESTGIVER_QUEST_COMPLETE(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(questid)
	READ_DWORD(XP)
	READ_DWORD(RewOrReqMoney)
	READ_DWORD(Honor)
	READ_DWORD(BonusTalents)
	READ_DWORD(U1)
	READ_FINISH
}
