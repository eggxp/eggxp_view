//---------------------------------------------------------------------------


#pragma hdrstop

#include "GameNPCHandler.h"
#include "GameWorld.h"
#include "SharedMemInfo.h"
#include "SharedDefine.h"
#include "ByteBuffer.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

GameNPCHandler::GameNPCHandler(GameWorld * gameWorld)
{
    m_GameWorld = gameWorld;
//	REG_HANDLER(SMSG_MONSTER_MOVE)
//	REG_HANDLER(SMSG_CREATURE_QUERY_RESPONSE)
//	REG_HANDLER(SMSG_THREAT_UPDATE)
//	REG_HANDLER(SMSG_HIGHEST_THREAT_UPDATE)
//	REG_HANDLER(SMSG_THREAT_CLEAR)
//    REG_HANDLER(SMSG_PET_SPELLS)
//    REG_HANDLER(SMSG_MIRRORIMAGE_DATA)
}

GameNPCHandler::~GameNPCHandler()
{
}

void    GameNPCHandler::Handler_SMSG_MONSTER_MOVE(WOWPackage * packet)
{
    int pos = 0;
	READ_GUID(guid)
	packet->SetGuid(guid);
	int entry = GUID_ENPART(guid);
	String creatureName = GetGameWorld()->GetDataStr(FormatStr("world/%llu/name", guid));
	packet->AddComment("CreatureName", creatureName);
	READ_BYTE(zero)
	READ_FLOAT(position_x)
	READ_FLOAT(position_y)
	READ_FLOAT(position_z)
	READ_DWORD(ms_time)
	tagServerMSTimeMutiParam *param = m_GameWorld->GetServerMSTimeMutiParamData(STM_MONSTER_MOVE);
	param->ServerMSTime = ms_time;
	param->MoveNPCName = creatureName;
	READ_BYTE(type)
    packet->GetComment()->Add(GetSplineTypeName(type));
    switch(type)
    {
        case SPLINETYPE_STOP:
        {
            return;
        }
        case SPLINETYPE_FACINGSPOT:                         // facing spot, not used currently
        {
            READ_FLOAT(x)
            READ_FLOAT(y)
            READ_FLOAT(z)
            break;
        }
        case SPLINETYPE_FACINGTARGET:
        {
            READ_UINT64(interaction_object);            // set in SetFacingToObject()
            break;
        }
        case SPLINETYPE_FACINGANGLE:                        // not used currently
        {
            READ_FLOAT(face);                               // facing angle
            break;
        }
    }

    READ_DWORD(flags)
    packet->GetComment()->Add(GetSplineFlags(flags));
    if (flags & SPLINEFLAG_TAKEOFF)
    {
        READ_DWORD(TakeOffStyle)
        READ_BYTE(TakeOffUNK1)
    }
    READ_DWORD(move_time)
    if((flags & SPLINEFLAG_KNOCKBACK) && (flags & SPLINEFLAG_TRAJECTORY))
    {
        READ_FLOAT(u1)
        READ_DWORD(u2)
    }
    if (flags & SPLINEFLAG_TRAJECTORY)
    {
        READ_FLOAT(height)
        READ_DWORD(zero1)
    }
	READ_DWORD(node_count)
	if (node_count > 0)
	{
		READ_FLOAT(new_x)
		READ_FLOAT(new_y)
		READ_FLOAT(new_z)
		float startOffsetX = (position_x + new_x) / 2;
		float startOffsetY = (position_y + new_y) / 2;
		float startOffsetZ = (position_z + new_z) / 2;
		for(DWORD i=1; i<node_count; i++)
		{
			if(!(flags & 0x80200))
			{
				READ_DWORD(packedFloatUnsigned)
				int packedFloat = packedFloatUnsigned;
				char *lpdate = (char *)&packedFloat;
				packet->GetComment()->Add(FormatStr("node %d : %s", i, BinToStr(lpdate, sizeof(int))));

				float offsetX = (float)((packedFloat & 0x7FF) << 21 >> 21) * 0.25f;
				float offsetY = (float)((((packedFloat >> 11) & 0x7FF) << 21) >> 21) * 0.25f;
				float offsetZ = (float)((packedFloat >> 22 << 22) >> 22) * 0.25f;
				packet->AddComment("offsetX", offsetX);
				packet->AddComment("offsetY", offsetY);
				packet->AddComment("offsetZ", offsetZ);

				float packed_posx = startOffsetX - offsetX;
				float packed_posy = startOffsetY - offsetY;
				float packed_posz = startOffsetZ - offsetZ;

				packet->AddComment("position_x", packed_posx);
				packet->AddComment("position_y", packed_posy);
				packet->AddComment("position_z", packed_posz);
			}
			else
			{
				READ_FLOAT(way_point_x)
				READ_FLOAT(way_point_y)
				READ_FLOAT(way_point_z)
			}
		}
	}
	READ_FINISH
}

void    GameNPCHandler::Handler_SMSG_CREATURE_QUERY_RESPONSE(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(entry)
	if((int)entry < 0)
	{
		READ_FINISH
		return;
	}
	READ_STRING(Name)
	READ_STRING(Name2)
	READ_STRING(Name3)
	READ_STRING(Name4)
	READ_STRING(SubName)
	READ_STRING(IconName)
	READ_DWORD(type_flags)
	READ_DWORD(type)
	READ_DWORD(family)
	READ_DWORD(rank)
	READ_DWORD(KillCredit0)
	READ_DWORD(KillCredit1)
	READ_DWORD(DisplayID_A0)
	READ_DWORD(DisplayID_H0)
	READ_DWORD(DisplayID_A1)
	READ_DWORD(DisplayID_H1)
	READ_FLOAT(unk16)
	READ_FLOAT(unk17)
	READ_BYTE(RacialLeader)
	for(uint32 i = 0; i < 6; ++i)
	{
		READ_DWORD(questItems)
	}
	READ_DWORD(movementId)
	READ_FINISH
}

void    GameNPCHandler::Handler_SMSG_THREAT_UPDATE(WOWPackage * packet)
{
	int pos = 0;
	READ_GUID(guid)
	READ_DWORD(count)
	for(DWORD i=0; i<count; i++)
	{
		READ_GUID(target)
		READ_DWORD(threat)
	}
	READ_FINISH

	m_GameWorld->SetData(FormatStr("threat/%llu", guid), packet->GetComment()->Text);
}

void    GameNPCHandler::Handler_SMSG_HIGHEST_THREAT_UPDATE(WOWPackage * packet)
{
	int pos = 0;
	READ_GUID(guid)
	READ_GUID(highest_guid)
	READ_DWORD(count)
	for(DWORD i=0; i<count; i++)
	{
		READ_GUID(target)
		READ_DWORD(threat)
	}
	READ_FINISH
	m_GameWorld->SetData(FormatStr("threat/%llu", guid), packet->GetComment()->Text);
}

void    GameNPCHandler::Handler_SMSG_THREAT_CLEAR(WOWPackage * packet)
{
	int pos = 0;
	READ_GUID(guid)
	READ_FINISH
	m_GameWorld->SetData(FormatStr("threat/%llu", guid), packet->GetComment()->Text);
}

void    GameNPCHandler::ReadPetActionBarData(WOWPackage * packet, int &pos)
{
    READ_DWORD(ActionBarPackedData)
    int type = UNIT_ACTION_BUTTON_TYPE(ActionBarPackedData);
    packet->AddComment("Type", type);
    packet->AddComment("TypeName", GetActiveStatesName(type));
    int action = UNIT_ACTION_BUTTON_ACTION(ActionBarPackedData);
    packet->AddComment("Action", action);
    packet->AddComment("ActionSpellName", GetSpellNameBySpellID(action));
}

void    GameNPCHandler::Handler_SMSG_PET_SPELLS(WOWPackage * packet)
{
    int pos = 0;
    READ_UINT64(petGuid)
    READ_WORD(petFamily)
    packet->AddComment("petFamily", GetCreatureFamilyName(petFamily));
    READ_DWORD(zero)
    READ_BYTE(ReactState)
    READ_BYTE(CommandState)
    READ_WORD(zero2)
    for(int i = 0; i < MAX_UNIT_ACTION_BAR_INDEX; ++i)
    {
        packet->AddComment("ACTION_BAR_INDEX", i);
        ReadPetActionBarData(packet, pos);

    }
    READ_BYTE(spellsCount)
    for(int i=0; i<spellsCount; i++)
    {
        packet->AddComment("spell", i);
        ReadPetActionBarData(packet, pos);
    }
    READ_BYTE(cooldownsCount)
    for(int i=0; i<cooldownsCount; i++)
    {
        READ_DWORD(spellid)
        packet->AddComment("SpellName", GetSpellNameBySpellID(spellid));
        READ_WORD(category)
        READ_DWORD(cooldown)
        READ_WORD(categoryCooldown)
        READ_WORD(U1)
    }
    READ_FINISH
}

void    GameNPCHandler::Handler_SMSG_MIRRORIMAGE_DATA(WOWPackage * packet)
{
    int pos = 0;
    READ_UINT64(guid)
    READ_DWORD(display_id)
    READ_BYTE(race)
    READ_BYTE(gender)
    READ_BYTE(cls)
    READ_BYTE(skin)
    READ_BYTE(face)
    READ_BYTE(hair)
    READ_BYTE(hairColor)
    READ_BYTE(facialHair)
    READ_DWORD(GuidID)
    static const EquipmentSlots ItemSlots[] =
    {
        EQUIPMENT_SLOT_HEAD,
        EQUIPMENT_SLOT_SHOULDERS,
        EQUIPMENT_SLOT_BODY,
        EQUIPMENT_SLOT_CHEST,
        EQUIPMENT_SLOT_WAIST,
        EQUIPMENT_SLOT_LEGS,
        EQUIPMENT_SLOT_FEET,
        EQUIPMENT_SLOT_WRISTS,
        EQUIPMENT_SLOT_HANDS,
        EQUIPMENT_SLOT_BACK,
        EQUIPMENT_SLOT_TABARD,
        EQUIPMENT_SLOT_END
    };
    for (EquipmentSlots const* itr = &ItemSlots[0]; *itr != EQUIPMENT_SLOT_END; ++itr)
    {
        READ_DWORD(DisplayInfoID)
    }
    READ_FINISH
}
