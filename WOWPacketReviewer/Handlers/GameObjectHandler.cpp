//---------------------------------------------------------------------------


#pragma hdrstop

#include "GameObjectHandler.h"
#include "GameWorld.h"
#include "zlib.h"
#include "SharedDefine.h"
#include "ShowAllMapAI.h"
#include "FishAI.h"
#include "DBCStores.h"
#include "KOEItlbm.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


GameObjectHandler::GameObjectHandler(GameWorld * gameWorld)
{
    m_GameWorld = gameWorld;
    REG_HANDLER(SMSG_COMPRESSED_UPDATE_OBJECT)
    REG_HANDLER(SMSG_UPDATE_OBJECT)
    REG_HANDLER(SMSG_NAME_QUERY_RESPONSE)
    REG_HANDLER(SMSG_GAMEOBJECT_SPAWN_ANIM_OBSOLETE)
    REG_HANDLER(SMSG_GAMEOBJECT_DESPAWN_ANIM)
    REG_HANDLER(SMSG_GAMEOBJECT_CUSTOM_ANIM)
    REG_HANDLER(SMSG_CRITERIA_UPDATE)
    REG_HANDLER(SMSG_ALL_ACHIEVEMENT_DATA)
	REG_HANDLER(SMSG_RESPOND_INSPECT_ACHIEVEMENTS)
	REG_HANDLER(SMSG_DESTROY_OBJECT)
}

GameObjectHandler::~GameObjectHandler()
{
}

void    GameObjectHandler::Handler_SMSG_COMPRESSED_UPDATE_OBJECT(WOWPackage * packet)
{                                  
    int pos = 0;
    int len = ReadDWORD(packet->GetContent(), pos);

    AnsiString buf(packet->GetContent() + pos, packet->GetContentLen() - pos);
    AnsiString uncompress;
    uncompress.SetLength(len);

    z_stream d_stream;

    d_stream.zalloc = (alloc_func)0;
    d_stream.zfree = (free_func)0;
    d_stream.opaque = (voidpf)0;

    d_stream.next_out = (BYTE*)uncompress.c_str();
    d_stream.next_in = (BYTE*)buf.c_str();
    d_stream.avail_in = buf.Length();

    // infault Z_BEST_SPEED (1)
    int z_res = inflateInit(&d_stream);
    if (z_res != Z_OK)
    {
        GetLog()->Error("Can't compress update packet (zlib: inflateInit) Error code: %i (%s)",z_res,zError(z_res));
        return;
    }

    z_res = inflate(&d_stream, Z_NO_FLUSH);
    if (z_res != Z_STREAM_END)
    {
        GetLog()->Error("Can't compress update packet (zlib: inflate should report Z_STREAM_END instead %i (%s)",z_res,zError(z_res));
        return;
    }

    z_res = inflateEnd(&d_stream);
    if (z_res != Z_OK)
    {
        GetLog()->Error("Can't compress update packet (zlib: inflateEnd) Error code: %i (%s)",z_res,zError(z_res));
        return;
    }

    packet->SetDecompress(uncompress);
    ProcessUpdateObject(packet);
}

void    GameObjectHandler::Handler_SMSG_UPDATE_OBJECT(WOWPackage * packet)
{                                                 
    ProcessUpdateObject(packet);
}

void    GameObjectHandler::ReadMovementUpdate(uint64 guid, WOWPackage * packet, int &pos)
{
    packet->GetComment()->Add("ReadMovementUpdate");
    READ_TYPE(int, update_flag, ReadWORD)
    packet->GetComment()->Add(GetUpdateFlagComment(update_flag));
    if (update_flag & UPDATEFLAG_LIVING)
    {
        //Write Movement Info
        DWORD move_flags = 0;
        m_GameWorld->GetMoveHandler()->ReadMovementInfo(guid, packet, pos, &move_flags);

        //End Write Movement Info
        READ_TYPE(float, walk_speed, ReadFloat);
        READ_TYPE(float, run_speed, ReadFloat);
        READ_TYPE(float, swim_back_speed, ReadFloat);
        READ_TYPE(float, swim_speed, ReadFloat);
        READ_TYPE(float, run_back_speed, ReadFloat);
        READ_TYPE(float, fly_speed, ReadFloat);
        READ_TYPE(float, fly_back_speed, ReadFloat);
        READ_TYPE(float, turn_speed, ReadFloat);
        READ_TYPE(float, pitch_speed, ReadFloat);

        if(move_flags & MOVEFLAG_SPLINE_ENABLED)
        {
            READ_TYPE(DWORD, flags3, ReadDWORD)
            if(flags3 & SPLINEFLAG_FINALFACING)
            {
                READ_TYPE(float, zero, ReadFloat)
            }
            else
            {
                if(flags3 & SPLINEFLAG_FINALTARGET)
                {
                    READ_TYPE(uint64, guid, ReadUINT64)
                }
                else
                {
                    if(flags3 & SPLINEFLAG_FINALPOINT)
                    {
                        READ_TYPE(float, ux, ReadFloat)
                        READ_TYPE(float, uy, ReadFloat)
                        READ_TYPE(float, uz, ReadFloat)
                    }
                }
            }
            //
            READ_TYPE(DWORD, inflighttime, ReadDWORD)
            READ_TYPE(DWORD, traveltime, ReadDWORD)
            READ_TYPE(DWORD, sequenceId, ReadDWORD)

            READ_TYPE(float, zx, ReadFloat)
            READ_TYPE(float, zy, ReadFloat)
            READ_TYPE(float, zz, ReadFloat)
            READ_TYPE(DWORD, u31, ReadDWORD)

            READ_TYPE(DWORD, poscount, ReadDWORD)
            for(DWORD node_index = 0; node_index < poscount; node_index++)
            {
                READ_TYPE(float, node_x, ReadFloat)
                READ_TYPE(float, node_y, ReadFloat)
                READ_TYPE(float, node_z, ReadFloat)
            }
            READ_TYPE(int, splineMode, ReadBYTE)
            READ_TYPE(float, dest_x, ReadFloat)
            READ_TYPE(float, dest_y, ReadFloat)
            READ_TYPE(float, dest_z, ReadFloat)
        } // MOVEFLAG_SPLINE_ENABLED
    }   // end UPDATEFLAG_LIVING
    else
    {
        if(update_flag & UPDATEFLAG_POSITION)
        {
            READ_TYPE(int, unk_pguid, ReadBYTE)
            READ_TYPE(float, this_x, ReadFloat)
            READ_TYPE(float, this_y, ReadFloat)
            READ_TYPE(float, this_z, ReadFloat)
            READ_TYPE(float, this_xs, ReadFloat)
            READ_TYPE(float, this_ys, ReadFloat)
            READ_TYPE(float, this_zs, ReadFloat)
            READ_TYPE(float, this_orientation, ReadFloat)
			READ_TYPE(float, this_orientations, ReadFloat)

			m_GameWorld->GetMoveHandler()->SetPos(guid, this_x, this_y, this_z, this_orientation);
		}
		else
		{
			if(update_flag & UPDATEFLAG_HAS_POSITION)
			{
				READ_TYPE(float, this_x, ReadFloat)
				READ_TYPE(float, this_y, ReadFloat)
				READ_TYPE(float, this_z, ReadFloat)
				READ_TYPE(float, this_orientation, ReadFloat)

				m_GameWorld->GetMoveHandler()->SetPos(guid, this_x, this_y, this_z, this_orientation);
            }
        }
    } // end UPDATEFLAG_LIVING else
    if(update_flag & UPDATEFLAG_LOWGUID)
    {
        READ_TYPE(DWORD, low_guid, ReadDWORD)
    }
    if(update_flag & UPDATEFLAG_HIGHGUID)
    {
        READ_TYPE(DWORD, high_guid, ReadDWORD)
    }
    if(update_flag & UPDATEFLAG_HAS_ATTACKING_TARGET)
    {
        READ_GUID(target)
    }
    if(update_flag & UPDATEFLAG_TRANSPORT)
    {
        READ_TYPE(DWORD, tick, ReadDWORD)
    }
    if(update_flag & UPDATEFLAG_VEHICLE)
    {
        READ_TYPE(DWORD, vehicle_id, ReadDWORD)
        READ_TYPE(float, orientation, ReadFloat)
    }
    if(update_flag & UPDATEFLAG_ROTATION)
    {
        READ_TYPE(uint64, rotation, ReadUINT64)
    }
}

String GetIndexInfo(int objtypeid, int index)
{
	if(objtypeid == TYPEID_CONTAINER && index >= ITEM_END)
	{
		return FormatStr("[%d(ITEM_END + 0x%04x)]", index, uint32(index-ITEM_END));
	}
	if(index >= UNIT_END)
	{
		return FormatStr("[%d(UNIT_END + 0x%04x)]", index, uint32(index-UNIT_END));
    }
    if(index >= OBJECT_END)
    {
        return FormatStr("[%d(OBJECT_END + 0x%04x)]", index, uint32(index-OBJECT_END));
    }
    return FormatStr("[%d]", index);
}

bool MayBeFloatIndexIsActureDWORD(int index)
{
	if(index >= ITEM_FIELD_ENCHANTMENT_1_1 && index <= ITEM_FIELD_ENCHANTMENT_12_3)
	{
		return true;
	}
	return false;
}

bool 	IsIndexForceDWORD(int objtypeid, int index)
{
	if(objtypeid == TYPEID_ITEM || objtypeid == TYPEID_CONTAINER)
	{
		return true;
	}
	if(objtypeid == TYPEID_PLAYER)
	{
		if(index >= PLAYER_FIELD_PAD_0 && index <= PLAYER_TRACK_RESOURCES)
		{
			return true;
		}
	}
	return false;
}

bool IsIndexMaybeFloat(char *content, int objtypeid, int index)
{
	if(objtypeid == TYPEID_PLAYER || objtypeid == TYPEID_UNIT)
	{
		if(index == UNIT_FIELD_POWER_REGEN_FLAT_MODIFIER ||
			index == UNIT_FIELD_POWER_REGEN_INTERRUPTED_FLAT_MODIFIER ||
			index == UNIT_FIELD_POWER_COST_MULTIPLIER ||
			index == UNIT_FIELD_MAXHEALTHMODIFIER ||
			index == UNIT_FIELD_HOVERHEIGHT)
		{
			return true;
		}
	}
	if(content[sizeof(DWORD)-1] <= 0x10)
	{
		return false;
	}
	if(MayBeFloatIndexIsActureDWORD(index))
	{
		return false;
	}
	if(IsIndexForceDWORD(objtypeid, index))
	{
		return false;
	}
	try
	{
		int pos = 0;
		String floatValue = FormatStr("%f", ReadFloat(content, pos));
	}
	catch(Exception &e)
	{
		return false;
	}
	return true;
}

String  GetDWORDInfo(int objtypeid, int index, BYTE * content)
{
	String result;
	if(objtypeid == TYPEID_PLAYER)
	{
		if(index >= PLAYER_SKILL_INFO_1_1 && index < PLAYER_CHARACTER_POINTS1)
		{
			int pos = 0;
			WORD skill1 = ReadWORD(content, pos);
			WORD skill2 = ReadWORD(content, pos);
			if((index - PLAYER_SKILL_INFO_1_1) % 3 == 0)
			{
				String skillname;
				const SkillLineEntry *skillline = GetSkillLineStore()->LookupEntry(skill1);
				if(skillline)
				{
					skillname = Utf8ToAnsi(skillline->name[5]);
				}
				result = FormatStr("SkillID:%d(%s)/Unlearn:%d", skill1, skillname, skill2);
			}
			else
			{
				result = FormatStr("Value:%d/Max:%d", skill1, skill2);
			}
		}
	}
	if(result == "")
	{
		result = FormatStr("[%s]", BinToStr(content, sizeof(DWORD)));
		int pos = 0;
		if(IsIndexMaybeFloat(content, objtypeid, index))
		{
			result += FormatStr("%f", ReadFloat(content, pos));
		}
		else
		{
			result += FormatStr("%d", ReadDWORD(content, pos));
		}
	}
    return  result;
}

bool    CheckIsGUIDValue(int index, int objtypeid, AnsiString update_mask)
{
	if(update_mask.Length() <= (index+1) >> 3)
		return false;
    if(!ReadBit(update_mask.c_str(), update_mask.Length(), index+1))
        return false;

    if(index == OBJECT_FIELD_GUID)
        return true;

    if(!(objtypeid == TYPEID_UNIT || objtypeid == TYPEID_PLAYER))
        return false;

    if(!(index >= UNIT_FIELD_CHARM && index < UNIT_FIELD_BYTES_0))
        return false;

    if((index - OBJECT_END)%2 != 0)
        return false;

    return true;
}

String FindFieldName(int objtypeid, int index)
{
	String fieldName = GetFieldName(objtypeid, index);
	if(fieldName != "")
		return fieldName;

	int searchIndex = index-1;
	for(searchIndex = index-1; searchIndex >= 0; searchIndex--)
	{
		if(GetFieldName(objtypeid, searchIndex) != "")
			break;
	}

	return FormatStr("%s[%02d]", GetFieldName(objtypeid, searchIndex), index - searchIndex);
}

void    GameObjectHandler::ReadValuesUpdate(int objtypeid, uint64 guid, WOWPackage * packet, int &pos, tagUpdateObjectValuesResult *curResult)
{
	curResult->ValuePosStart = pos;
    packet->GetComment()->Add(FormatStr("ReadValuesUpdate:%s", GetTypeIDName(objtypeid)));
	READ_TYPE(int, value_block_count, ReadBYTE)
	int maskSize = value_block_count * sizeof(int);
	curResult->MaskSize = maskSize;
	curResult->MaskPos = pos;
    READ_BUFF(update_mask, maskSize)
    int count = value_block_count * 32;
    map<int, uint64>  update_map;
    for(int index=0; index<count; index++)
    {
		if(ReadBit(update_mask.c_str(), update_mask.Length(), index))
		{
			{
			tagUpdateObjectValueResult vr;
			vr.Type = index;
			int temPos = pos;
			vr.Pos = temPos;
			vr.Value = ReadDWORD(packet->GetContent(), temPos);
			curResult->Values.push_back(vr);
			}
			if(CheckIsGUIDValue(index, objtypeid, update_mask))
			{
				{
				tagUpdateObjectValueResult vr;
				vr.Type = index+1;
				int temPos = pos+4;
				vr.Pos = temPos;
				vr.Value = ReadDWORD(packet->GetContent(), temPos);
				curResult->Values.push_back(vr);
				}

				packet->GetComment()->Add(FormatStr("[#%d]%s:%s", pos, GetIndexInfo(objtypeid, index), GetFieldName(objtypeid, index)));
				READ_UINT64(guid)
				update_map[index] = guid;
				index++;
                continue;
            }

			packet->GetComment()->Add(FormatStr("[#%d]%s:%s", pos, GetIndexInfo(objtypeid, index), FindFieldName(objtypeid, index)));
			packet->GetComment()->Add(GetDWORDInfo(objtypeid, index, packet->GetContent()+pos));
			int int_value = ReadDWORD(packet->GetContent(), pos);
			if (index == OBJECT_FIELD_ENTRY)
			{
				String name;
				if (objtypeid == TYPEID_ITEM || objtypeid == TYPEID_CONTAINER)
				{
					name = GetGameWorld()->GetItemNameByID(int_value);
					packet->AddComment("ItemName", name);
				}
				else if (objtypeid == TYPEID_GAMEOBJECT)
				{
					name = GetGameWorld()->GetGameObjectNameByID(int_value);
					packet->AddComment("GameObjectName", name);
				}
				else if (objtypeid == TYPEID_UNIT)
				{
					name = GetGameWorld()->GetCreatureNameByID(int_value);
					packet->AddComment("CreatureName", name);
				}
				m_GameWorld->SetData(FormatStr("world/%llu/name", guid), name);
				if (name != "")
				{
					m_GameWorld->SetData(FormatStr("world/%llu", guid), name);
				}
			}
			if(index == OBJECT_FIELD_TYPE)
			{
				packet->AddComment("ObjectType", GetTypeMaskFlag(int_value));
			}
			update_map[index] = int_value;
			if(index == ITEM_FIELD_ENCHANTMENT_2_1+1)
			{
				m_GameWorld->SetItemFieldEnchantmentValue1(int_value);
			}
        }
	}

	m_GameWorld->SetData(FormatStr("world/%llu/guid_info", guid), GetGUIDInfo(guid));
	for (map<int, uint64>::iterator it=update_map.begin(); it!=update_map.end(); it++)
	{
		String fieldName = FindFieldName(objtypeid, it->first);
		m_GameWorld->SetData(FormatStr("world/%llu/%s", guid, fieldName), FormatStr("%s", GetDWORDInfo(objtypeid, it->first, (char *)&it->second)));
		if(objtypeid == TYPEID_DYNAMICOBJECT && it->first == DYNAMICOBJECT_CASTTIME)
		{
			tagServerMSTimeMutiParam *param = m_GameWorld->GetServerMSTimeMutiParamData(STM_DYNAMICOBJECT_CASTTIME);
			param->ServerMSTime = it->second;
			param->MoveNPCName = GetObjectNameByGuid(guid);
		}
	}

	if(m_GameWorld->GetSelfGUID() == guid)
	{
		bool needRefreshZone = false;
		for (map<int, uint64>::iterator it=update_map.begin(); it!=update_map.end(); it++)
		{
			m_GameWorld->SetData(FormatStr("self/data_view/%s", FindFieldName(objtypeid, it->first)), FormatStr("%s", GetDWORDInfo(objtypeid, it->first, (char *)&it->second)));

			#ifdef WOW_FISHER
			if(it->first >= PLAYER_EXPLORED_ZONES_1 && it->first < PLAYER_REST_STATE_EXPERIENCE && it->second != -1)
			{
				needRefreshZone = true;
			}
			#endif
		}
		#ifdef WOW_FISHER
		if(needRefreshZone && !GetGameWorld()->GetFishAI()->GetIsStop())
		{
			GetFiberManager()->Awake(FWC_WAIT_SHOW_ALL_MAP);
		}
		#endif
		if(update_map.find(UNIT_FIELD_CHANNEL_OBJECT) != update_map.end() &&
			update_map.find(UNIT_CHANNEL_SPELL) != update_map.end())
		{
			{
				if(m_GameWorld->GetFishAI()->IsFishSpellID(update_map[UNIT_CHANNEL_SPELL]))
				{
					m_GameWorld->SetData("self/fish/fishobjl", LOW_GUID(update_map[UNIT_FIELD_CHANNEL_OBJECT]));
					m_GameWorld->SetData("self/fish/fishobjh", HIGH_GUID(update_map[UNIT_FIELD_CHANNEL_OBJECT]));
				}
	//            GetLog()->Info("Casting Spell : %d. objectID : 0x%x", update_map[UNIT_CHANNEL_SPELL], update_map[UNIT_FIELD_CHANNEL_OBJECT]);
			}
		}
	}

	curResult->ValuePosEnd = pos;
}

void    GameObjectHandler::Handler_SMSG_DESTROY_OBJECT(WOWPackage * packet)
{
	int pos = 0;
	READ_UINT64(guid)
	READ_BYTE(anim)
	READ_FINISH

    m_GameWorld->DeleteData(FormatStr("world/%llu", guid));
}

void    GameObjectHandler::ProcessUpdateObject(WOWPackage * packet)
{
	m_UpdateValueResults.clear();
    int pos = 0;
    READ_TYPE(DWORD, block_count, ReadDWORD);

    for(DWORD block = 0; block < block_count; block++)
    {
        packet->GetComment()->Add(FormatStr("UPDATE BLOCK: %d", block));
        READ_TYPE(int, update_type, ReadBYTE);
		packet->GetComment()->Add(GetOBJECT_UPDATE_TYPEName(update_type));

		tagUpdateObjectValuesResult result;
		result.BlockName = GetOBJECT_UPDATE_TYPEName(update_type);
		result.ValuePosStart = pos;
		m_UpdateValueResults.push_back(result);

		tagUpdateObjectValuesResult *curValue = &m_UpdateValueResults[m_UpdateValueResults.size()-1];

        if(update_type == UPDATETYPE_OUT_OF_RANGE_OBJECTS)
        {
			//disappear
            READ_TYPE(int, out_of_range_guid, ReadDWORD);
            for(int i=0; i<out_of_range_guid; i++)
            {
				READ_GUID(disappear_guid)
				m_GameWorld->DeleteData(FormatStr("world/%llu", disappear_guid));
            }
        }
        else if(update_type == UPDATETYPE_CREATE_OBJECT || update_type == UPDATETYPE_CREATE_OBJECT2)
        {
			READ_GUID(guid)
			if(block_count == 1)
			{
				packet->SetGuid(guid);
			}
			READ_TYPE(int, obj_type_id, ReadBYTE)
			AddGUIDToHignGuidTypeMapping(GUID_HIPART(guid), obj_type_id);
			packet->GetComment()->Add(GetTypeIDName(obj_type_id));
//			m_GameWorld->SetData(FormatStr("world/%llu", guid), GetTypeIDName(obj_type_id));
			m_GameWorld->SetData(FormatStr("world/%llu/type_id", guid), obj_type_id);
			m_GameWorld->SetData(FormatStr("world/%llu/type_id_name", guid), GetTypeIDName(obj_type_id));
			ReadMovementUpdate(guid, packet, pos);
			curValue->ObjTypeID = obj_type_id;
			ReadValuesUpdate(obj_type_id, guid, packet, pos, curValue);
		} // end UPDATETYPE_CREATE_OBJECT
		else if(update_type == UPDATETYPE_MOVEMENT)
		{
			READ_GUID(guid)
			if(block_count == 1)
			{
				packet->SetGuid(guid);
			}
			ReadMovementUpdate(guid, packet, pos);
		}
		else if(update_type == UPDATETYPE_VALUES)
		{
			READ_GUID(guid)
			if(block_count == 1)
			{
				packet->SetGuid(guid);
			}
			int obj_type_id = GuidHigh2TypeId(GUID_HIPART(guid));
			curValue->ObjTypeID = obj_type_id;
			ReadValuesUpdate(obj_type_id, guid, packet, pos, curValue);
        }

		packet->GetComment()->Add("");
    }// end for

    READ_FINISH
}

void                GameObjectHandler::Handler_SMSG_NAME_QUERY_RESPONSE(WOWPackage * packet)
{
    int pos = 0;
    READ_GUID(guid);
    READ_BYTE(zero);
	READ_UTF8_STRING(name);
	m_GameWorld->SetData(FormatStr("world/%llu", guid), name);
	m_GameWorld->SetData(FormatStr("world/%llu/name", guid), name);
    READ_UTF8_STRING(realm_name);
    READ_BYTE(race);
    READ_BYTE(gender);
    READ_BYTE(cur_class);
    READ_BYTE(have_decline_name);
    if(have_decline_name)
    {
        for(int i = 0; i < MAX_DECLINED_NAME_CASES; ++i)
        {
            READ_UTF8_STRING(decline_name);
        }
    }
    READ_FINISH
}

void                GameObjectHandler::Handler_SMSG_GAMEOBJECT_SPAWN_ANIM_OBSOLETE(WOWPackage * packet)
{
    int pos = 0;
    READ_UINT64(guid);
    READ_FINISH
}

void                GameObjectHandler::Handler_SMSG_GAMEOBJECT_DESPAWN_ANIM(WOWPackage * packet)
{
    int pos = 0;
    READ_UINT64(guid);
    READ_FINISH
}

void                GameObjectHandler::Handler_SMSG_GAMEOBJECT_CUSTOM_ANIM(WOWPackage * packet)
{
    int pos = 0;
    READ_UINT64(guid);
    READ_DWORD(type);
    READ_FINISH

    if(m_GameWorld->IsSameGUID(guid, "self/fish/fishobjl", "self/fish/fishobjh"))
    {
        GetFiberManager()->Awake(FWC_FISH_HOOK);
    }
}

void                GameObjectHandler::Handler_SMSG_CRITERIA_UPDATE(WOWPackage * packet)
{
    int pos = 0;
	READ_DWORD(id);
	packet->AddComment("name", GetAchievementCriteriaName(id));
    READ_GUID(counter);
    READ_GUID(player_guid);
    READ_DWORD(zero);
	READ_TIMEBIT(time_bit);
    READ_DWORD(timer1);
    READ_DWORD(timer2);
    READ_FINISH
}

void                GameObjectHandler::Handler_SMSG_ALL_ACHIEVEMENT_DATA(WOWPackage * packet)
{
    int pos = 0;
	ReadAllDataPacket(packet, pos);
}

void                GameObjectHandler::Handler_SMSG_RESPOND_INSPECT_ACHIEVEMENTS(WOWPackage * packet)
{
    int pos = 0;
    READ_GUID(player_guid)
    ReadAllDataPacket(packet, pos);
}

void                GameObjectHandler::ReadAllDataPacket(WOWPackage * packet, int &pos)
{
    while(pos <= packet->GetContentLen())
    {
		READ_TYPE(int, achievement, ReadDWORD)
		if(achievement == -1)
		{
			break;
		}
		packet->AddComment("achievement", GetAchievementName(achievement));
        READ_TIMEBIT(time_bit)
    }

    while(pos <= packet->GetContentLen())
    {
        READ_TYPE(int, first, ReadDWORD)
        if(first == -1)
        {
            break;
        }
        READ_GUID(counter)
        READ_GUID(player_guid)
        READ_TYPE(DWORD, zero1, ReadDWORD)
        READ_TIMEBIT(time_bit)
        READ_TYPE(DWORD, zero2, ReadDWORD)
        READ_TYPE(DWORD, zero3, ReadDWORD)
    }

    READ_FINISH
}
