//---------------------------------------------------------------------------


#pragma hdrstop

#include "SpellHandler.h"
#include "GameWorld.h"
#include "shareddefine.h"
#include "DBCStores.h"
#include "KOEItlbm.h"
#include "FishAI.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)



SpellHandler::SpellHandler(GameWorld * gameworld)
{
    m_GameWorld = gameworld;
//    REG_HANDLER(CMSG_CAST_SPELL)
//    REG_HANDLER(SMSG_SPELL_START)
//    REG_HANDLER(SMSG_SPELL_GO)
//    REG_HANDLER(MSG_CHANNEL_START)
//    REG_HANDLER(SMSG_SPELLLOGEXECUTE)
//	REG_HANDLER(SMSG_INITIAL_SPELLS)
//	REG_HANDLER(SMSG_LEARNED_SPELL)
//	REG_HANDLER(SMSG_SUPERCEDED_SPELL)
//	REG_HANDLER(SMSG_CAST_FAILED)
//	REG_HANDLER(SMSG_AURA_UPDATE)
//	REG_HANDLER(SMSG_SPELLNONMELEEDAMAGELOG)
//	REG_HANDLER(SMSG_SPELLHEALLOG)
//	REG_HANDLER(SMSG_TRAINER_LIST)
//	REG_HANDLER(SMSG_SET_FLAT_SPELL_MODIFIER)
//	REG_HANDLER(SMSG_SET_PCT_SPELL_MODIFIER)
}

SpellHandler::~SpellHandler()
{
}

void	SpellHandler::Handler_SMSG_AURA_UPDATE(WOWPackage * packet)
{
    int pos = 0;
	READ_GUID(guid);
	while (pos != packet->GetContentLen())
	{
		READ_BYTE(aura_slot);
		READ_DWORD(remove_id);
		if(!remove_id)
		{
			READ_FINISH
			return;
		}
		packet->AddComment("Spell Name", GetSpellNameBySpellID(remove_id));
		READ_BYTE(aura_flags);
		packet->GetComment()->Add(GetAURA_FLAGS(aura_flags));
		READ_BYTE(aura_level);
		READ_BYTE(stack_amount);

		if(!(aura_flags & AFLAG_NOT_CASTER))
		{
			READ_BYTE(pguid);
			READ_BYTE(u1);
		}

		if(aura_flags & AFLAG_DURATION)
		{
			READ_DWORD(aura_max_duration);
			READ_DWORD(aura_duration);
		}
	}
	READ_FINISH
}

void    SpellHandler::Handler_CMSG_CAST_SPELL(WOWPackage * packet)
{
    {
    //每个技能发送, index都会自增
    //这样就不能主动插入封包了
    //所以在这里强制修改技能index
	static  int     cast_index = 1;
	int cast_index_pos = 0;
	int org_case_index = ReadBYTE(packet->GetContent(), cast_index_pos);
	packet->AddComment("PackIndex", org_case_index);
	cast_index_pos = 0;
//	WriteBYTE(packet->GetContent(), cast_index_pos, cast_index);
    cast_index++;
    }

    int pos = 0;
    READ_TYPE(int, cast_count, ReadBYTE);
    READ_TYPE(int, spellId, ReadDWORD);
    packet->AddComment("Spell Name", GetSpellNameBySpellID(spellId));

    READ_TYPE(int, unk_flags, ReadBYTE);
    READ_TYPE(DWORD, target_mask, ReadDWORD);

    if(target_mask == TARGET_FLAG_SELF)
    {
        packet->GetComment()->Add("TARGET_FLAG_SELF");
    }

    // TARGET_FLAG_UNK2 is used for non-combat pets, maybe other?
    if( target_mask & ( TARGET_FLAG_UNIT | TARGET_FLAG_UNK2 ))
    {
        packet->GetComment()->Add("TARGET_FLAG_UNIT | TARGET_FLAG_UNK2");
        READ_GUID(guid);
    }

    if( target_mask & ( TARGET_FLAG_OBJECT ))
    {
        packet->GetComment()->Add("TARGET_FLAG_OBJECT");
        READ_GUID(guid);
    }

    if(( target_mask & ( TARGET_FLAG_ITEM | TARGET_FLAG_TRADE_ITEM )) )
    {
        packet->GetComment()->Add("TARGET_FLAG_ITEM | TARGET_FLAG_TRADE_ITEM");
        READ_GUID(guid);
    }

    if( target_mask & (TARGET_FLAG_CORPSE | TARGET_FLAG_PVP_CORPSE ) )
    {
        packet->GetComment()->Add("TARGET_FLAG_CORPSE | TARGET_FLAG_PVP_CORPSE");
        READ_GUID(guid);
    }

    if( target_mask & TARGET_FLAG_SOURCE_LOCATION )
    {
        packet->GetComment()->Add("TARGET_FLAG_SOURCE_LOCATION");
        READ_GUID(guid);

        READ_TYPE(float, srcx, ReadFloat);
        READ_TYPE(float, srcy, ReadFloat);
        READ_TYPE(float, srcz, ReadFloat);
    }

    if( target_mask & TARGET_FLAG_DEST_LOCATION )
    {
        packet->GetComment()->Add("TARGET_FLAG_DEST_LOCATION");
        READ_GUID(guid);
        READ_TYPE(float, destx, ReadFloat);
        READ_TYPE(float, desty, ReadFloat);
        READ_TYPE(float, destz, ReadFloat);
    }

    if( target_mask & TARGET_FLAG_STRING )
    {
        packet->GetComment()->Add("TARGET_FLAG_STRING");
        READ_STRING(target); 
	}
	READ_FINISH
}

void    SpellHandler::Handler_SMSG_SPELL_START(WOWPackage * packet)
{
    int pos = 0;
    READ_GUID(caster_item);

    READ_GUID(caster_guid);

    READ_TYPE(DWORD, cast_count, ReadBYTE);
	READ_TYPE(DWORD, spell_id, ReadDWORD);
	packet->AddComment("Spell Name", GetSpellNameBySpellID(spell_id));
	READ_TYPE(DWORD, cast_flags, ReadDWORD);
	packet->AddComment("cast_flags", GetSpellCastFlagsName(cast_flags));
	READ_TYPE(DWORD, timer, ReadDWORD);

	READ_TYPE(DWORD, target_mask, ReadDWORD);
	packet->AddComment("target_mask", GetSpellCastTargetFlags(target_mask));

    if( target_mask & ( TARGET_FLAG_UNIT | TARGET_FLAG_PVP_CORPSE | TARGET_FLAG_OBJECT | TARGET_FLAG_CORPSE | TARGET_FLAG_UNK2 ) )
    {
        if(target_mask & TARGET_FLAG_UNIT)
        {
            packet->GetComment()->Add("TARGET_FLAG_UNIT");
            READ_GUID(target);
        }
        else if( target_mask & TARGET_FLAG_OBJECT )
        {
            packet->GetComment()->Add("TARGET_FLAG_OBJECT");
            READ_GUID(target);
        }
        else if( target_mask & ( TARGET_FLAG_CORPSE | TARGET_FLAG_PVP_CORPSE ) )
        {
            packet->GetComment()->Add("TARGET_FLAG_CORPSE | TARGET_FLAG_PVP_CORPSE");
            READ_GUID(target);
        }
        else
        {
            packet->GetComment()->Add("TARGET_FLAG_UNK2");
            READ_GUID(target);
        }
    }

    if( target_mask & ( TARGET_FLAG_ITEM | TARGET_FLAG_TRADE_ITEM ) )
    {
        packet->GetComment()->Add("TARGET_FLAG_ITEM | TARGET_FLAG_TRADE_ITEM");
        READ_GUID(item_target);
    }

    if( target_mask & TARGET_FLAG_SOURCE_LOCATION )
    {
        packet->GetComment()->Add("TARGET_FLAG_SOURCE_LOCATION");
        READ_GUID(item_target);

        READ_TYPE(int, srcx, ReadFloat);
        READ_TYPE(int, srcy, ReadFloat);
        READ_TYPE(int, srcz, ReadFloat);
    }

    if( target_mask & TARGET_FLAG_DEST_LOCATION )
    {
        packet->GetComment()->Add("TARGET_FLAG_DEST_LOCATION");
        READ_GUID(item_target);

        READ_TYPE(int, destx, ReadFloat);
        READ_TYPE(int, desty, ReadFloat);
        READ_TYPE(int, destz, ReadFloat);
    }

    if( target_mask & TARGET_FLAG_STRING )
    {
        packet->GetComment()->Add("TARGET_FLAG_STRING");
        READ_STRING(target); 
    }
    READ_FINISH
}

void   	SpellHandler::ReadSpellGoTargets(WOWPackage * packet, int &pos, uint64 caster_guid)
{
	READ_BYTE(hit)
    for(int i=0; i<hit; i++)
    {
        READ_UINT64(target)
    }

    READ_TYPE(DWORD, miss, ReadBYTE);
    for(DWORD i=0; i<miss; i++)
    {
        packet->AddComment("i = ", i);
        READ_UINT64(target)

        READ_BYTE(condition)
		String HitInfoStr = GetSpellMissInfoName(condition);
		packet->GetComment()->Add(HitInfoStr);

		if(condition == SPELL_MISS_REFLECT)
		{
			READ_BYTE(reflect_result)
		}

		if (caster_guid == m_GameWorld->GetSelfGUID() || target == m_GameWorld->GetSelfGUID())
		{
			if (caster_guid == m_GameWorld->GetSelfGUID())
			{
				RefreshGridTotal(m_GameWorld, HitInfoStr, "spell", "attack");
			}
			else
			{
				RefreshGridTotal(m_GameWorld, HitInfoStr, "spell", "be_attack");
			}
		}
	}
}

void	SpellHandler::ReadSpellTargets(WOWPackage * packet, int &pos, DWORD &targetMask)
{
	READ_DWORD(m_targetMask)
	targetMask = m_targetMask;
	packet->GetComment()->Add(GetSpellCastTargetFlags(m_targetMask));
	if( m_targetMask & ( TARGET_FLAG_UNIT | TARGET_FLAG_PVP_CORPSE | TARGET_FLAG_OBJECT | TARGET_FLAG_CORPSE | TARGET_FLAG_UNK2 ) )
	{
		packet->GetComment()->Add("Enter : TARGET_FLAG_UNIT | TARGET_FLAG_PVP_CORPSE | TARGET_FLAG_OBJECT | TARGET_FLAG_CORPSE | TARGET_FLAG_UNK2 :");
		READ_GUID(guid)
	}

	if( m_targetMask & ( TARGET_FLAG_ITEM | TARGET_FLAG_TRADE_ITEM ) )
	{
		packet->GetComment()->Add("Enter : TARGET_FLAG_ITEM | TARGET_FLAG_TRADE_ITEM");
		READ_GUID(guid)
	}

	if( m_targetMask & TARGET_FLAG_SOURCE_LOCATION )
	{
		packet->GetComment()->Add("Enter : TARGET_FLAG_SOURCE_LOCATION");
		READ_GUID(guid)
		READ_FLOAT(src_x)
		READ_FLOAT(src_y)
		READ_FLOAT(src_z)
	}

	if( m_targetMask & TARGET_FLAG_DEST_LOCATION )
	{
		packet->GetComment()->Add("Enter : TARGET_FLAG_DEST_LOCATION");
		READ_GUID(guid)
		READ_FLOAT(dest_x)
		READ_FLOAT(dest_y)
		READ_FLOAT(dest_z)
	}

	if( m_targetMask & TARGET_FLAG_STRING )
	{
		READ_STRING(m_strTarget)
    }
}

void	SpellHandler::ReadAmmoToPacket(WOWPackage * packet, int &pos)
{
	READ_DWORD(ammoDisplayID)
	READ_DWORD(ammoInventoryType)
}

void    SpellHandler::Handler_SMSG_SPELL_GO(WOWPackage * packet)
{
    int pos = 0;
    READ_GUID(caster_item);

	READ_GUID(caster_guid);

    READ_TYPE(DWORD, cast_count, ReadBYTE)
	READ_TYPE(DWORD, spell_id, ReadDWORD)
	packet->AddComment("SpellName", GetSpellNameBySpellID(spell_id));

//	#ifdef	WOW_FISHER
	{
		FishAI *fishAI = m_GameWorld->GetFishAI();
		if(fishAI->GetActive() == 0 && caster_guid == m_GameWorld->GetSelfGUID() && fishAI->IsFishSpellID(spell_id))
		{
			fishAI->ActiveAI(FEC_USER_USE_SKILL);
		}
	}
//	#endif

	READ_TYPE(DWORD, castFlags, ReadDWORD)
	packet->GetComment()->Add(GetSpellCastFlags(castFlags));
    READ_TYPE(DWORD, timer, ReadDWORD)
	tagServerMSTimeMutiParam *param = m_GameWorld->GetServerMSTimeMutiParamData(STM_SMSG_SPELL_GO);
	param->ServerMSTime = timer;
	param->MoveNPCName = GetObjectNameByGuid(caster_guid);

	ReadSpellGoTargets(packet, pos, caster_guid);
	DWORD targetMask = 0;
	ReadSpellTargets(packet, pos, targetMask);

	if ( castFlags & CAST_FLAG_UNKNOWN6 )                   // unknown wotlk, predicted power?
	{
		READ_DWORD(zero)
	}

    if ( castFlags & CAST_FLAG_UNKNOWN7 )                   // rune cooldowns list
    {
		READ_BYTE(v1);
		READ_BYTE(v2);

        for(uint8 i = 0; i < MAX_RUNES; ++i)
        {
			uint8 m = (1 << i);
			// usable before...
			if(m & v1)
			{
				// ...but on cooldown now...
				if(!(m & v2))
				{
					// some unknown byte (time?)
					READ_BYTE(u_zero);
				}
			}
        }
    }

    if ( castFlags & CAST_FLAG_UNKNOWN4 )                   // unknown wotlk
	{
		READ_FLOAT(float_zero)
        READ_DWORD(zero)
    }

	if ( castFlags & CAST_FLAG_AMMO )
	{
		ReadAmmoToPacket(packet, pos);
	}

    if ( castFlags & CAST_FLAG_UNKNOWN5 )                   // unknown wotlk
    {
		READ_DWORD(zero1);
		READ_DWORD(zero2);
    }

    if ( targetMask & TARGET_FLAG_DEST_LOCATION )
    {
		READ_BYTE(zero);
    }



    READ_FINISH
}

void    SpellHandler::Handler_MSG_CHANNEL_START(WOWPackage * packet)
{
    int pos = 0;
    READ_GUID(caster_guid);

    READ_TYPE(DWORD, spell_id, ReadDWORD)
	READ_TYPE(DWORD, duration, ReadDWORD)
	READ_FINISH
}

void    SpellHandler::Handler_SMSG_SPELLLOGEXECUTE(WOWPackage * packet)
{
    int pos = 0;
    READ_GUID(tag_guid);
    READ_DWORD(spell_id);
    READ_DWORD(count1);
    for(DWORD i=0; i<count1; i++)
    {
        READ_DWORD(spell_effect);
        packet->GetComment()->Add(GetSpellEffectsName(spell_effect));
        READ_DWORD(count2);
        for(DWORD j=0; j<count2; j++)
        {
            switch(spell_effect)
            {
                case SPELL_EFFECT_CREATE_ITEM:
                case SPELL_EFFECT_CREATE_ITEM_2:
                {
                    READ_DWORD(item_type_effect);
                    break;
                }
                case SPELL_EFFECT_FEED_PET:
                {
                    READ_DWORD(target_entry);
                    break;
                }
                default:
                {
                    READ_GUID(guid);
                }
            }
        }
    }
    READ_FINISH
}

void    SpellHandler::Handler_SMSG_INITIAL_SPELLS(WOWPackage * packet)
{
    m_GameWorld->GetDataByKey("self/spell")->Clear();
    int pos = 0;
    READ_BYTE(be_zero)
    READ_WORD(spell_count)
    for(int i=0; i<spell_count; i++)
    {
        READ_DWORD(spell_id)
        packet->AddComment("Spell Name", GetSpellNameBySpellID(spell_id));
        READ_WORD(zero)
		m_GameWorld->SetData(FormatStr("self/spell/%d", spell_id), spell_id);
	}
	READ_WORD(spell_cooldown)
	for(int i=0; i<spell_cooldown; i++)
	{
		READ_DWORD(cooldown_id)
		READ_WORD(item_id)
		READ_WORD(category)
		READ_DWORD(cooldown)
		READ_DWORD(category_cooldown)
	}
	READ_FINISH
}

void    SpellHandler::Handler_SMSG_LEARNED_SPELL(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(spell_id)
	m_GameWorld->SetData(FormatStr("self/spell/%d", spell_id), spell_id);
	READ_FINISH
}

void    SpellHandler::Handler_SMSG_SUPERCEDED_SPELL(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(old_spell)
	READ_DWORD(new_spell)
	m_GameWorld->GetDataByKey("self/spell")->DeleteDataObject(old_spell);
	m_GameWorld->SetData(FormatStr("self/spell/%d", new_spell), new_spell);
	READ_FINISH
}

void    SpellHandler::Handler_SMSG_CAST_FAILED(WOWPackage * packet)
{
	int pos = 0;
	READ_BYTE(cast_count)
	READ_DWORD(spell_id)
	FishAI *fishAI = m_GameWorld->GetFishAI();
	if(fishAI->GetActive() && fishAI->IsFishSpellID(spell_id))
	{
		GetFiberManager()->Awake(FWC_FISH_HOOK, FEC_SPELL_FAIL);
	}
	READ_BYTE(result)
	READ_DWORD(reson1)
	READ_DWORD(reson2)
	READ_FINISH
}

void    SpellHandler::Handler_SMSG_SPELLNONMELEEDAMAGELOG(WOWPackage * packet)
{
	int pos = 0;
	READ_GUID(target)
	READ_GUID(attacker)
	READ_DWORD(SpellID)
	packet->AddComment("Spell Name", GetSpellNameBySpellID(SpellID));
	READ_DWORD(damage)
	READ_DWORD(overkill)
	READ_BYTE(schoolMask)
	READ_DWORD(absorb)
	READ_DWORD(resist)
	READ_BYTE(physicalLog)
	READ_BYTE(unused)
	READ_DWORD(blocked)
	READ_DWORD(HitInfo)
	String HitInfoStr = GetSpellHitTypeFlag(HitInfo);
	packet->AddComment("hit info", HitInfoStr);
	READ_BYTE(zero)
	READ_FINISH

	if (attacker == m_GameWorld->GetSelfGUID() || target == m_GameWorld->GetSelfGUID())
	{
		if (attacker == m_GameWorld->GetSelfGUID())
		{
			RefreshGridTotal(m_GameWorld, HitInfoStr, "spell", "attack");
		}
		else
		{
			RefreshGridTotal(m_GameWorld, HitInfoStr, "spell", "be_attack");
		}
	}
}

void    SpellHandler::Handler_SMSG_SPELLHEALLOG(WOWPackage * packet)
{
	int pos = 0;
	READ_GUID(target)
	READ_GUID(attacker)
	READ_DWORD(SpellID)
	packet->AddComment("Spell Name", GetSpellNameBySpellID(SpellID));
	READ_DWORD(Damage)
	READ_DWORD(OverHeal)
	READ_DWORD(Absorb)
	READ_BYTE(critical)
	READ_BYTE(zero)
	READ_FINISH
}

void    SpellHandler::Handler_SMSG_TRAINER_LIST(WOWPackage * packet)
{
	int pos = 0;
	READ_UINT64(guid)
	READ_DWORD(trainer_type)
	READ_DWORD(spell_list_size)
	for(DWORD i=0; i<spell_list_size; i++)
	{
		READ_DWORD(SpellID)
		packet->AddComment("Spell Name", GetSpellNameBySpellID(SpellID));
		READ_BYTE(state)
		packet->AddComment("state", GetTrainerSpellStateType(state));
		READ_DWORD(spellCost)
		READ_DWORD(can_learn_primary_prof)
		READ_DWORD(primary_prof_first_rank)
		READ_BYTE(reqLevel)
		READ_DWORD(reqSkill)
		READ_DWORD(reqSkillValue)
		READ_DWORD(prev)
		READ_DWORD(req)
		READ_DWORD(zero)
	}
	READ_STRING(strTitle)
	READ_FINISH
}

void    SpellHandler::Handler_SMSG_SET_FLAT_SPELL_MODIFIER(WOWPackage * packet)
{
	Handler_SMSG_SET_SPELL_Normal(packet);
}

void    SpellHandler::Handler_SMSG_SET_PCT_SPELL_MODIFIER(WOWPackage * packet)
{
	Handler_SMSG_SET_SPELL_Normal(packet);
}

bool    SpellHandler::IsSpellIDCanApplyEffIndex(DWORD spellID, DWORD effidx)
{
	const  SpellEntry * curSpellEntry = GetSpellStore()->LookupEntry(spellID);

	if(!curSpellEntry)
	{
		return  false;
	}
    bool canApply = false;
    if (effidx < 64)
    {
        if (curSpellEntry->SpellFamilyFlags & (1 << effidx))
        {
            canApply = true;
        }
    }
    else
    {
        if (curSpellEntry->SpellFamilyFlags2 & (1 << (effidx - 64)))
        {
            canApply = true;
        }
    }
    if (!canApply)
    {
        return false;
    }
    return true;
}

void    SpellHandler::Handler_SMSG_SET_SPELL_Normal(WOWPackage * packet)
{
	int pos = 0;
	READ_BYTE(effidx)
	READ_BYTE(spellmodop)
	packet->AddComment("name", GetSpellModOpName(spellmodop));
	READ_DWORD(value)
    packet->AddComment("value(int32)", int(value));

    set<String> temp;
    map<int, vector<String> > result;
	for (DWORD i=0; i<GetSpellStore()->GetRecordCount(); i++)
	{
        const  SpellEntry * curSpellEntry = GetSpellStore()->LookupByIndex(i);
        if(curSpellEntry->SpellFamilyName == 0)
        {
            continue;
        }
		int spellID = curSpellEntry->Id;
		if(IsSpellIDCanApplyEffIndex(spellID, effidx))
		{
            String name = GetSpellNameBySpellID(spellID);
            if(temp.find(name) != temp.end())
            {
                continue;
            }
            temp.insert(name);
            result[curSpellEntry->SpellFamilyName].push_back(name);
		}
	}
    for(map<int, vector<String> >::iterator it = result.begin(); it != result.end(); ++it)
    {
        packet->AddComment(GetSpellFamilyNamesName(it->first), it->first);
        for(size_t i=0; i<it->second.size(); i++)
        {
            packet->AddComment("ApplySpellName", FormatStr("%s", it->second[i]));
        }
    }
	READ_FINISH
}
