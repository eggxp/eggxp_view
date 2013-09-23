//---------------------------------------------------------------------------

#include <windows.h>
#pragma hdrstop

#include "PlayerHandler.h"
#include "GameWorld.h"
#include "SharedDefine.h"
#include "KOEItlbm.h"
#include "SharedMemInfo.h"
#include "ByteBuffer.h"
#include "zlib.h"
#include "FishAI.h"
#include "themidasdk.h"
#include "DBCStores.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

PlayerHandler::PlayerHandler(GameWorld * gameWorld)
{
    m_GameWorld = gameWorld;
//    REG_HANDLER(SMSG_SET_PROFICIENCY)
//	REG_HANDLER(CMSG_PLAYER_LOGIN)
//    REG_HANDLER(CMSG_LOGOUT_REQUEST)
//    REG_HANDLER(CMSG_ACTIVATETAXI)
//    REG_HANDLER(SMSG_SHOWTAXINODES)
//    REG_HANDLER(SMSG_INIT_WORLD_STATES)
//	REG_HANDLER(SMSG_CHAR_ENUM)
//	REG_HANDLER(SMSG_ACCOUNT_DATA_TIMES)
//	REG_HANDLER(CMSG_UPDATE_ACCOUNT_DATA)
//	REG_HANDLER(SMSG_UPDATE_ACCOUNT_DATA)
//	REG_HANDLER(SMSG_WORLD_STATE_UI_TIMER_UPDATE)
//	REG_HANDLER(SMSG_QUERY_TIME_RESPONSE)
//	REG_HANDLER(SMSG_PLAYED_TIME)
//	REG_HANDLER(CMSG_TIME_SYNC_RESP)
//	REG_HANDLER(SMSG_LOGIN_SETTIMESPEED)
//	REG_HANDLER(CMSG_WHO)
//	REG_HANDLER(SMSG_WHO)
//	REG_HANDLER(CMSG_SET_SELECTION)
//	REG_HANDLER(SMSG_TRADE_STATUS_EXTENDED)
//	REG_HANDLER(SMSG_TALENTS_INFO)
//	REG_HANDLER(SMSG_POWER_UPDATE)
//	REG_HANDLER(SMSG_INITIALIZE_FACTIONS)
//	REG_HANDLER(SMSG_LOGIN_VERIFY_WORLD)
//	REG_HANDLER(CMSG_MOVE_SET_CAN_FLY_ACK)
//	REG_HANDLER(MSG_SET_DUNGEON_DIFFICULTY)
//	REG_HANDLER(SMSG_FEATURE_SYSTEM_STATUS)
//	REG_HANDLER(SMSG_MOTD)
//	REG_HANDLER(SMSG_LEARNED_DANCE_MOVES)
//	REG_HANDLER(SMSG_BINDPOINTUPDATE)
//	REG_HANDLER(SMSG_ACTION_BUTTONS)
//	REG_HANDLER(MSG_MOVE_TELEPORT_ACK)
//	REG_HANDLER(CMSG_MOVE_WATER_WALK_ACK)
//	REG_HANDLER(SMSG_MOVE_WATER_WALK)
//	REG_HANDLER(SMSG_MOVE_LAND_WALK)
}

PlayerHandler::~PlayerHandler()
{
}

void    PlayerHandler::Handler_SMSG_SET_PROFICIENCY(WOWPackage * packet)
{
    int pos = 0;
    READ_TYPE(int, type, ReadBYTE);
    packet->GetComment()->Add(GetItemClassName(type));
    READ_TYPE(DWORD, value, ReadDWORD);
    READ_FINISH
}

void    PlayerHandler::Handler_CMSG_PLAYER_LOGIN(WOWPackage * packet)
{
    GetSharedMemInfo()->FindSelf()->ForbiddenAnyMortConnection = 1;
    int pos = 0;
	READ_UINT64(guid)

	AddGUIDToHignGuidTypeMapping(GUID_HIPART(guid), TYPEID_PLAYER);

	m_GameWorld->SetData("self/guidl", DWORD(guid & 0xFFFFFFFF));
	m_GameWorld->SetData("self/guidh", DWORD(guid>>32));

	GetLog()->Warn("GUIDL : %d", m_GameWorld->GetDataInt("self/guidl"));
	GetLog()->Warn("GUIDH : %d", m_GameWorld->GetDataInt("self/guidh"));
    m_GameWorld->SetIsLoginOK(1);
}

void    PlayerHandler::Handler_CMSG_ACTIVATETAXI(WOWPackage * packet)
{
    int pos = 0;
    READ_UINT64(guid)
    READ_DWORD(node0)
    READ_DWORD(node1)
    READ_FINISH
}

void    PlayerHandler::Handler_SMSG_SHOWTAXINODES(WOWPackage * packet)
{
    int pos = 0;
    READ_DWORD(one)
    READ_UINT64(guid)
    READ_DWORD(curloc)
    for(int i=0; i<TaxiMaskSize; i++)
    {
        READ_DWORD(taxi_node_mask)
    }
    READ_FINISH
}

void    PlayerHandler::Handler_SMSG_INIT_WORLD_STATES(WOWPackage * packet)
{
	#ifdef WOW_FISHER
	GetFiberManager()->Awake(FWC_WAIT_SHOW_ALL_MAP);
	#endif
    int pos = 0;
    READ_DWORD(mapid)
    READ_DWORD(zoneid)
	READ_DWORD(areaid)
	packet->AddComment("name", GetAreaNameByMapAndZone(mapid, zoneid));
    READ_WORD(NumberOfFields)
    m_GameWorld->SetData("self/mapid", mapid);
    m_GameWorld->SetData("self/zoneid", zoneid);
    m_GameWorld->SetData("self/areaid", areaid);
	m_GameWorld->SetData("self/NumberOfFields", NumberOfFields);
	for(int i=0; i<NumberOfFields; i++)
	{
		packet->AddComment("------------------field:", i);
		READ_DWORD(state)
		READ_DWORD(value)
	}
	READ_FINISH
}

void    PlayerHandler::Handler_SMSG_CHAR_ENUM(WOWPackage * packet)
{
    int pos = 0;
	READ_BYTE(num)
	m_GameWorld->OnRelogin();
    for(int i=0; i<num; i++)
    {
        READ_UINT64(guid)
        READ_UTF8_STRING(name)
        m_GameWorld->SetData("self/name", name);
        READ_BYTE(pRace)
        READ_BYTE(pClass)
        READ_BYTE(gender)
        READ_BYTE(skin)
        READ_BYTE(face)
        READ_BYTE(hair_style)
        READ_BYTE(hair_color)
        READ_BYTE(facial_hair)
        READ_BYTE(level)
        READ_DWORD(zone)
        READ_DWORD(map)
        READ_FLOAT(x)
        READ_FLOAT(y)
        READ_FLOAT(z)
        READ_DWORD(guild_id)
        READ_DWORD(char_flags)
        packet->GetComment()->Add(GetCharacterFlags(char_flags));
        READ_DWORD(atLoginFlags)
        packet->GetComment()->Add(GetAtLoginFlags(atLoginFlags));
        READ_BYTE(first_login)
        READ_DWORD(petDisplayId)
        READ_DWORD(petLevel)
        READ_DWORD(petFamily)
        for(int i=0; i<EQUIPMENT_SLOT_END; i++)
        {
            READ_DWORD(InventoryDisplayInfoID)
            READ_BYTE(InventoryType)
            READ_DWORD(InventoryEnchant_ID)
        }

		for(int i=0; i<4; i++)
		{
			READ_DWORD(bagDisplayID)
			READ_BYTE(bagInventoryType)
			READ_DWORD(bagEnchant)
		}
        packet->GetComment()->Add("");
    }
    READ_FINISH
}

void    PlayerHandler::Handler_SMSG_ACCOUNT_DATA_TIMES(WOWPackage * packet)
{
	int pos = 0;
	READ_TIME(cur_time)
	READ_TYPE(int, one, ReadBYTE)
	READ_TYPE(DWORD, mask, ReadDWORD)
	packet->AddComment("AccountDataType", GetAccountDataTypeMask(mask));
	for(uint32 i = 0; i < NUM_ACCOUNT_DATA_TYPES; ++i)
	{
		if(mask & (1 << i))
		{
			READ_TIME(account_time)
		}
	}
	READ_FINISH
}

void    PlayerHandler::Handler_CMSG_UPDATE_ACCOUNT_DATA(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(type)
	packet->AddComment("AccountDataType", GetAccountDataType(type));
	READ_TIME(cur_time)
	READ_DWORD(decompressedSize)
    ByteBuffer dest;
    dest.resize(decompressedSize);
	DWORD realSize = decompressedSize;
	if(uncompress(const_cast<uint8*>(dest.contents()), &realSize,
		packet->GetContent() + pos, packet->GetContentLen() - pos) != Z_OK)
	{
		packet->GetComment()->Add("read error");
		return;
	}
	string adata;
	dest >> adata;
	String strData = UTF8ToUnicodeString(adata.c_str());
	packet->AddComment("Data", strData);

	pos = packet->GetContentLen();
	READ_FINISH
}

void    PlayerHandler::Handler_SMSG_UPDATE_ACCOUNT_DATA(WOWPackage * packet)
{
	int pos = 0;
	READ_UINT64(guid)
	READ_DWORD(type)
	packet->AddComment("AccountDataType", GetAccountDataType(type));
	READ_TIME(cur_time)
	READ_DWORD(decompressedSize)
    ByteBuffer dest;
    dest.resize(decompressedSize);
	DWORD realSize = decompressedSize;
	if(uncompress(const_cast<uint8*>(dest.contents()), &realSize,
		packet->GetContent() + pos, packet->GetContentLen() - pos) != Z_OK)
	{
		packet->GetComment()->Add("read error");
		return;
	}
	string adata;
	dest >> adata;
	String strData = UTF8ToUnicodeString(adata.c_str());
	packet->AddComment("Data", strData);
	pos = packet->GetContentLen();
	READ_FINISH
}

void    PlayerHandler::Handler_SMSG_WORLD_STATE_UI_TIMER_UPDATE(WOWPackage * packet)
{
    int pos = 0;
	READ_TIME(time)
	CheckExpriedTime(time);

	READ_FINISH
}

void	PlayerHandler::CheckExpriedTime(int year, int month, int day, int hour, int min)
{
	TDateTime rv;
	rv = TDateTime(year, month, day);
	rv += TDateTime(hour, min, 0, 0);
	CheckExpriedTime(rv);
}

void	PlayerHandler::CheckExpriedTime(TDateTime curtime)
{
	#ifndef WOW_FISHER
	return;
	#else
	#ifndef _DEBUG
	VM_START
	TDateTime cur_time = curtime;
	TDateTime expireTime = m_GameWorld->GetExpireTime();
	if(cur_time > expireTime)
	{
		SetExpried();
	}
	VM_END
	#endif
	#endif
}

void	PlayerHandler::CheckExpriedTimeByTimebit(DWORD timebit)
{
	CheckExpriedTime(TimeBitToDateTime(timebit));
}

void	PlayerHandler::CheckExpriedTime(DWORD time)
{
	#ifndef WOW_FISHER
	return;
	#else
	#ifndef _DEBUG
	VM_START
	TDateTime cur_time = TTimeToDateTime(time);
	TDateTime expireTime = m_GameWorld->GetExpireTime();
	if(cur_time > expireTime)
	{
		SetExpried();
	}
	VM_END
	#endif
	#endif
}

void    PlayerHandler::Handler_SMSG_QUERY_TIME_RESPONSE(WOWPackage * packet)
{
	int pos = 0;
	READ_TIME(time)
	CheckExpriedTime(time);
	READ_DWORD(NextDailyQuestsResetTime);
	long next_time = NextDailyQuestsResetTime + time;
	packet->AddComment("NextDailyQuestsResetTime", ctime(&next_time));
	READ_FINISH
}

void    PlayerHandler::Handler_SMSG_PLAYED_TIME(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(TotalPlayedTime)
	READ_DWORD(LevelPlayedTime)
	READ_BYTE(unk1)
	READ_FINISH
}

void    PlayerHandler::SetExpried()
{
	FishAI *fishAI = m_GameWorld->GetFishAI();
	if(!fishAI->GetIsStop())
	{
		fishAI->StopAI(true);
	}
}

void    PlayerHandler::Handler_CMSG_TIME_SYNC_RESP(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(counter)
	READ_DWORD(time_tick)
	packet->AddComment("diff", time_tick - timeGetTime());
	packet->AddComment("diff", float(time_tick) / (timeGetTime()));
	SetWowInitTick(time_tick);

	#ifdef WOW_FISHER
	m_GameWorld->SetData("self/tick/current", time_tick);
	if(counter == 0)
	{
		double timeDiff = m_GameWorld->GetExpireTime() - m_GameWorld->GetLoginTime();
		DWORD counterTick = timeDiff * 24 * 3600 * 1000 + time_tick;
		m_GameWorld->SetEndCounter(counterTick);
		m_GameWorld->SetData("self/tick/end", counterTick);
	}
	else
	{
		if(GetGameWorld()->GetEndCounter() != 0 && time_tick >= GetGameWorld()->GetEndCounter())
		{
         	SetExpried();
		}
	}
	#endif
	READ_FINISH
}

void    PlayerHandler::Handler_SMSG_LOGIN_SETTIMESPEED(WOWPackage * packet)
{
	int pos = 0;
	READ_TIMEBIT(time)
	#ifdef  WOW_FISHER
	CheckExpriedTimeByTimebit(time);
	#endif
	TDateTime dateTime = TimeBitToDateTime(time);
	m_GameWorld->SetLoginTime(dateTime);
	m_GameWorld->SetData("self/login_time", dateTime);
	READ_FLOAT(game_speed)
	READ_DWORD(u)
	READ_FINISH
}

void    PlayerHandler::Handler_CMSG_WHO(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(level_min)
	READ_DWORD(level_max)
	READ_STRING(player_name)
	READ_STRING(guild_name)
	READ_DWORD(racemask)
	READ_DWORD(classmask)
	READ_DWORD(zones_count)
	for (DWORD i=0; i<zones_count; i++)
	{
		READ_DWORD(zoneID)
	}
	READ_DWORD(str_count)
	for (DWORD i=0; i<str_count; i++)
	{
		READ_STRING(strs)
	}
	READ_FINISH
}

void    PlayerHandler::Handler_SMSG_WHO(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(clientcount)
	READ_DWORD(clientcount2)
	m_WhoInfo.clear();
	for(DWORD i=0; i<clientcount; i++)
	{
		READ_STRING(player_name)
		READ_STRING(guild_name)
		READ_DWORD(level)
		READ_DWORD(class_)
		READ_DWORD(race)
		READ_BYTE(zero)
		READ_DWORD(pzoneid)

		tagWhoPlayerInfo	info;
		info.Player_Name = player_name;
		info.Guild_Name = guild_name;
		info.level = level;
		info.Class = class_;
		info.Race = race;
		info.ZoneID = pzoneid;
		m_WhoInfo[player_name] = info;
	}
	READ_FINISH

	GetFiberManager()->Awake(FWC_WAIT_AUTO_CHAT_WHO);
}

void    PlayerHandler::Handler_CMSG_SET_SELECTION(WOWPackage * packet)
{
	int pos = 0;
	READ_UINT64(guid)
	READ_FINISH

	m_GameWorld->SetData("self/selection", guid);
}

void    PlayerHandler::Handler_SMSG_TRADE_STATUS_EXTENDED(WOWPackage * packet)
{
	int pos = 0;
	READ_BYTE(can_trade)
	READ_DWORD(zero)
	READ_DWORD(trade_slot_count)
	READ_DWORD(trade_slot_count2)
	READ_DWORD(trade_gold)
	READ_DWORD(zero1)
	for(uint8 i = 0; i < TRADE_SLOT_COUNT; ++i)
	{
		READ_BYTE(index)
		READ_DWORD(item_id)
		packet->AddComment("Name", m_GameWorld->GetItemNameByID(item_id));
		READ_DWORD(displat_id)
		READ_DWORD(stack_count)
		READ_DWORD(zero)
		READ_UINT64(gift_creator)
		READ_DWORD(enchantment_id)
		for(uint8 j = 0; j < 3; ++j)
		{
			READ_DWORD(zero)
		}
		READ_UINT64(creator)
		READ_DWORD(spell_charge)
		READ_DWORD(ItemSuffixFactor)
		READ_DWORD(ItemRandomPropertyId)
		READ_DWORD(LockID)
		READ_DWORD(MAX_DURABILITY)
		READ_DWORD(DURABILITY)
	}
	READ_FINISH
}

void    PlayerHandler::Handler_SMSG_TALENTS_INFO(WOWPackage * packet)
{
	int pos = 0;
	READ_BYTE(IsPet)
	if(!IsPet)
	{
		READ_DWORD(GetFreeTalentPoints)
		READ_BYTE(m_specsCount)
		READ_BYTE(m_activeSpec)
		if(!m_specsCount)
		{
			READ_FINISH
			return;
		}
		for(int specIdx = 0; specIdx < m_specsCount; ++specIdx)
		{
			READ_BYTE(talentIdCount);
			for(int i = 0; i < talentIdCount; ++i)
			{
				READ_DWORD(TalentID);
				READ_BYTE(curtalent_maxrank);
				packet->AddComment("Talent Name", GetTalentNameByTalent(TalentID, curtalent_maxrank));
			}
			READ_BYTE(nMAX_GLYPH_SLOT_INDEX)
			for(uint8 i = 0; i < nMAX_GLYPH_SLOT_INDEX; ++i)
			{
				READ_WORD(Glyph);
			}
		}
		READ_FINISH
		return;
	}
	// pet
	READ_DWORD(unspentTalentPoints)
	READ_BYTE(talentIdCount)
	for(int i=0; i<talentIdCount; i++)
	{
		READ_DWORD(TalentID);
		// packet->AddComment("Talent Name", GetSpellNameBySpellID(TalentID));
		READ_BYTE(curtalent_maxrank);
	}

	READ_FINISH
}

void    PlayerHandler::Handler_SMSG_POWER_UPDATE(WOWPackage * packet)
{
	int pos = 0;
	READ_GUID(guid)
	READ_BYTE(power)
	packet->AddComment("power", GetPowersName(power));
	READ_DWORD(val)
	READ_FINISH
}

void    PlayerHandler::Handler_SMSG_INITIALIZE_FACTIONS(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(factionSize)
	for(DWORD i=0; i<factionSize; i++)
	{
		packet->AddComment("name", GetFactionNameByReputationListID(i));
		READ_BYTE(Flags)
		packet->AddComment("Flag", GetFactionFlagsName(Flags));
		READ_DWORD(Standing)
	}
	READ_FINISH
}

void    PlayerHandler::Handler_SMSG_LOGIN_VERIFY_WORLD(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(mapID)
	packet->AddComment("map", GetMapNameByMapID(mapID));
	READ_FLOAT(x)
	READ_FLOAT(y)
	READ_FLOAT(z)
	READ_FLOAT(o)
	READ_FINISH
}

void    PlayerHandler::Handler_CMSG_MOVE_SET_CAN_FLY_ACK(WOWPackage * packet)
{
	int pos = 0;
	READ_FINISH

	GetFiberManager()->Awake(FWC_WAIT_FLY_ACK);
}

void    PlayerHandler::Handler_MSG_SET_DUNGEON_DIFFICULTY(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(dungeonDifficuty)
	packet->AddComment("difficuty", GetDifficultyName(dungeonDifficuty));
	READ_DWORD(val)
	READ_DWORD(isInGroup)
	READ_FINISH
}

void    PlayerHandler::Handler_SMSG_FEATURE_SYSTEM_STATUS(WOWPackage * packet)
{
	int pos = 0;
	READ_BYTE(two)
	READ_BYTE(enableVoiceChat)
	READ_FINISH
}

void    PlayerHandler::Handler_SMSG_MOTD(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(linecount)
	for (DWORD i=0; i<linecount; i++)
	{
		READ_STRING(motd)
	}
	READ_FINISH
}

void    PlayerHandler::Handler_SMSG_LEARNED_DANCE_MOVES(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(z1)
	READ_DWORD(z2)
	READ_FINISH
}

void    PlayerHandler::Handler_SMSG_BINDPOINTUPDATE(WOWPackage * packet)
{
	int pos = 0;
	READ_FLOAT(x)
	READ_FLOAT(y)
	READ_FLOAT(z)
	READ_DWORD(mapID)
	READ_DWORD(areaID)
	packet->AddComment("name", GetAreaNameByMapAndZone(mapID, areaID));
	READ_FINISH
}

void    PlayerHandler::Handler_SMSG_ACTION_BUTTONS(WOWPackage * packet)
{
	int pos = 0;
	READ_BYTE(talentSpec)
	for(int i=0; i<MAX_ACTION_BUTTONS; i++)
	{
		packet->AddComment("-------------->", i);
		READ_DWORD(packedData)
		int action = ACTION_BUTTON_ACTION(packedData);
		packet->AddComment("action", ACTION_BUTTON_ACTION(packedData));
		int type = ACTION_BUTTON_TYPE(packedData);
		packet->AddComment("type", type);
		packet->AddComment("typeName", GetActionButtonTypeName(type));
		if(type == ACTION_BUTTON_SPELL)
		{
			packet->AddComment("spellName", GetSpellNameBySpellID(action));
		}
	}
	READ_FINISH
}

void    PlayerHandler::Handler_MSG_MOVE_TELEPORT_ACK(WOWPackage * packet)
{
	int pos = 0;
	if(packet->GetMark() == SEND_MARK)
	{
		READ_GUID(guid)
		READ_DWORD(flags)
		packet->AddComment("moveFlag", GetMoveFlagComment(flags));
		READ_DWORD(time)
		READ_FINISH
		return;
	}
	else
	{
		READ_GUID(guid)
		READ_DWORD(counter)
		READ_DWORD(moveFlag)
		packet->AddComment("moveFlag", GetMoveFlagComment(moveFlag));
		READ_WORD(specialFlags)
		READ_DWORD(tick)
		tagServerMSTimeMutiParam *param = m_GameWorld->GetServerMSTimeMutiParamData(STM_MSG_MOVE_TELEPORT_ACK);
		param->ServerMSTime = tick;
		param->MoveNPCName = GetObjectNameByGuid(guid);
		READ_FLOAT(x)
		READ_FLOAT(y)
		READ_FLOAT(z)
		READ_FLOAT(o)
		if(packet->GetContentLen() - pos == 4)
		{
			READ_DWORD(zero_mark)
			READ_FINISH
			return;
		}
		READ_GUID(vehicleGuid)
		READ_FLOAT(attachmentOffsetX)
		READ_FLOAT(attachmentOffsetY)
		READ_FLOAT(attachmentOffsetZ)
		READ_FLOAT(z1)
		READ_DWORD(transportTime)
		READ_BYTE(seat)
		READ_DWORD(fallTime)
		READ_FINISH
		return;
	}
}

void    PlayerHandler::Handler_CMSG_MOVE_WATER_WALK_ACK(WOWPackage * packet)
{
	int pos = 0;
	READ_FINISH

	GetFiberManager()->Awake(FWC_WAIT_WATER_WALKING_ACK);
}

void    PlayerHandler::Handler_SMSG_MOVE_WATER_WALK(WOWPackage * packet)
{
	int pos = 0;
	READ_GUID(guid)
	READ_DWORD(zero)
	READ_FINISH
}

void    PlayerHandler::Handler_SMSG_MOVE_LAND_WALK(WOWPackage * packet)
{
	int pos = 0;
	READ_GUID(guid)
	READ_DWORD(zero)
	READ_FINISH
}

void    PlayerHandler::Handler_CMSG_LOGOUT_REQUEST(WOWPackage * packet)
{
    int pos = 0;
    GetSharedMemInfo()->FindSelf()->ForbiddenAnyMortConnection = 0;
    READ_FINISH
}
