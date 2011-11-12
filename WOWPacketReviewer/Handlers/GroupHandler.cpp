//---------------------------------------------------------------------------


#pragma hdrstop

#include "GroupHandler.h"
#include "GameWorld.h"
#include "SharedDefine.h"
#include "SharedMemInfo.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

GroupHandler::GroupHandler(GameWorld * gameWorld)
{
    m_GameWorld = gameWorld;
    REG_HANDLER(SMSG_GROUP_LIST)
    REG_HANDLER(SMSG_PARTY_MEMBER_STATS)
    REG_HANDLER(SMSG_PARTY_MEMBER_STATS_FULL)
}

GroupHandler::~GroupHandler()
{
}

void    GroupHandler::Handler_SMSG_GROUP_LIST(WOWPackage * packet)
{
    int pos = 0;
    READ_TYPE(int, group_type, ReadBYTE)
    READ_TYPE(int, is_big_group, ReadBYTE)
    READ_TYPE(int, group, ReadBYTE)
    READ_TYPE(int, assisant, ReadBYTE)
    if(group_type & GROUPTYPE_LFD)
    {
        READ_TYPE(int, lfd_u1, ReadBYTE)
        READ_TYPE(int, lfd_u2, ReadDWORD)
    }
    READ_TYPE(uint64, u_mark, ReadUINT64)
    if(GetSharedMemInfo()->FindSelf()->Build != 10146)
    {
        READ_TYPE(int, u_0, ReadDWORD)
    }
    READ_TYPE(DWORD, member_count, ReadDWORD)

    for(DWORD i=0; i<member_count; i++)
    {
        READ_STRING(member_name)
        READ_TYPE(uint64, member_guid, ReadUINT64)
        READ_TYPE(int, member_online, ReadBYTE)
        READ_TYPE(int, member_group, ReadBYTE)
        READ_TYPE(int, member_assistant, ReadBYTE)
		if(GetSharedMemInfo()->FindSelf()->Build != 10146)
		{
			READ_TYPE(int, member_zero, ReadBYTE)
		}
    }

    READ_TYPE(uint64, leader_guid, ReadUINT64)
    if(member_count)
    {
        READ_TYPE(int, loot_method, ReadBYTE)
        READ_TYPE(uint64, looter_guid, ReadUINT64)

        READ_TYPE(int, loot_Threshold, ReadBYTE)
        READ_TYPE(int, dungeonDifficulty, ReadBYTE)
        READ_TYPE(int, raidDifficulty, ReadBYTE)
		if(GetSharedMemInfo()->FindSelf()->Build != 10146)
		{
			READ_TYPE(int, u_zero, ReadBYTE)
		}
    }
}

void    GroupHandler::Handler_SMSG_PARTY_MEMBER_STATS(WOWPackage * packet)
{
    int pos = 0;
    READ_GUID(guid)
    READ_DWORD(mask)
    packet->GetComment()->Add(GetGroupUpdateFlagsName(mask));


	if (mask & GROUP_UPDATE_FLAG_STATUS)
	{
		READ_WORD(state)
		packet->GetComment()->Add(GetGroupMemberOnlineStatus(state));
	}

	if(mask & GROUP_UPDATE_FLAG_CUR_HP)
	{
		READ_DWORD(curHP)
	}

	if(mask & GROUP_UPDATE_FLAG_MAX_HP)
	{
		READ_DWORD(maxHP)
	}


	if(mask & GROUP_UPDATE_FLAG_POWER_TYPE)
	{
		READ_BYTE(power_type)
	}

	if(mask & GROUP_UPDATE_FLAG_CUR_POWER)
	{
		READ_WORD(curPower)
	}

	if(mask & GROUP_UPDATE_FLAG_MAX_POWER)
	{
		READ_WORD(maxPower)
	}

	if(mask & GROUP_UPDATE_FLAG_LEVEL)
	{
		READ_WORD(level)
	}

	if(mask & GROUP_UPDATE_FLAG_ZONE)
	{
		READ_WORD(zoneID)
	}

	if(mask & GROUP_UPDATE_FLAG_AURAS)
	{
		READ_UINT64(aura_mask)
		for(uint32 i = 0; i < MAX_AURAS; ++i)
		{
			if(aura_mask & (uint64(1) << i))
			{
				READ_DWORD(visible_aura)
				READ_BYTE(u_1)
			}
		}
	}

	if (mask & GROUP_UPDATE_FLAG_PET_GUID)
	{
		READ_UINT64(pet_guid)
		if(pet_guid == 0)
			return;
	}

	if (mask & GROUP_UPDATE_FLAG_PET_NAME)
	{
		READ_STRING(pet_name)
	}

	if (mask & GROUP_UPDATE_FLAG_PET_MODEL_ID)
	{
		READ_WORD(pet_display_id)
	}

	if (mask & GROUP_UPDATE_FLAG_PET_CUR_HP)
	{
		READ_DWORD(curHP)
	}

	if (mask & GROUP_UPDATE_FLAG_PET_MAX_HP)
	{
		READ_DWORD(maxHP)
	}


	if (mask & GROUP_UPDATE_FLAG_PET_POWER_TYPE)
	{
		READ_BYTE(pet_power_type)
	}

	if (mask & GROUP_UPDATE_FLAG_PET_CUR_POWER)
	{
		READ_WORD(curPower)
	}

	if (mask & GROUP_UPDATE_FLAG_PET_MAX_POWER)
	{
		READ_WORD(maxPower)
	}

	if (mask & GROUP_UPDATE_FLAG_PET_AURAS)
	{
		READ_UINT64(aura_mask)
		for(uint32 i = 0; i < MAX_AURAS; ++i)
		{
			if(aura_mask & (uint64(1) << i))
			{
				READ_DWORD(visible_aura)
				READ_BYTE(u_1)
			}
		}
	}
}

void    GroupHandler::Handler_SMSG_PARTY_MEMBER_STATS_FULL(WOWPackage * packet)
{
    int pos = 0;
    READ_BYTE(zero)
    READ_GUID(player_guid)
    READ_DWORD(mask)
    READ_WORD(online)

    READ_DWORD(health)
    READ_DWORD(max_health)

    READ_BYTE(power_type)
    READ_WORD(power)
    READ_WORD(max_power)
    
    READ_WORD(lv)
    READ_WORD(zone_id)
    READ_WORD(posx)
    READ_WORD(posy)

    READ_UINT64(aura_mask)
    for(uint32 i = 0; i < MAX_AURAS; ++i)
    {
        if(aura_mask & (uint64(1) << i))
        {
            READ_DWORD(visible_aura)
            READ_BYTE(u_1)
        }
    }

    READ_UINT64(pet_guid)
    if(pet_guid)
    {
        READ_STRING(pet_name)
        READ_WORD(pet_display_id)
        READ_DWORD(health)
        READ_DWORD(max_health)
        READ_BYTE(power_type)
        READ_WORD(power)
        READ_WORD(max_power)

        READ_UINT64(aura_mask)
        for(uint32 i = 0; i < MAX_AURAS; ++i)
        {
            if(aura_mask & (uint64(1) << i))
            {
                READ_DWORD(visible_aura)
                READ_BYTE(u_1)
            }
        }
    }
}
