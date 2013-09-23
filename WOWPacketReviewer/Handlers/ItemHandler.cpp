//---------------------------------------------------------------------------


#pragma hdrstop

#include "ItemHandler.h"
#include "GameWorld.h"
#include "SharedDefine.h"
#include "KOEItlbm.h"
#include "SharedMemInfo.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

ItemHandler::ItemHandler(GameWorld * gameWorld)
{
    m_GameWorld = gameWorld;
//    REG_HANDLER(SMSG_ITEM_QUERY_SINGLE_RESPONSE)
//    REG_HANDLER(SMSG_LOOT_RESPONSE)
//    REG_HANDLER(SMSG_LOOT_REMOVED)
//    REG_HANDLER(SMSG_ITEM_PUSH_RESULT)
//	REG_HANDLER(SMSG_LOOT_RELEASE_RESPONSE)
//	REG_HANDLER(SMSG_LIST_INVENTORY)
//	REG_HANDLER(SMSG_ITEM_COOLDOWN)
}

ItemHandler::~ItemHandler()
{
}

void    ItemHandler::Handler_SMSG_ITEM_QUERY_SINGLE_RESPONSE(WOWPackage * packet)
{
    int pos = 0;
    READ_DWORD(ItemId);
    READ_DWORD(Class);
    READ_DWORD(SubClass);
    READ_DWORD(Unk0);
    READ_UTF8_STRING(Name);

	GetGameWorld()->SetData(FormatStr("items_data/%d/Name", ItemId), Name);

    
    READ_UTF8_STRING(Name2);
    READ_UTF8_STRING(Name3);
    READ_UTF8_STRING(Name4);
    READ_DWORD(DisplayInfoID);
    READ_DWORD(Quality);
    READ_DWORD(Flags);
	// 3.3.2 faction?
    if(GetSharedMemInfo()->FindSelf()->Build != 10146)
    {
        READ_DWORD(Faction);
	}

    READ_DWORD(BuyPrice);
    READ_DWORD(SellPrice);
    READ_DWORD(InventoryType);
    READ_DWORD(AllowableClass);
    READ_DWORD(AllowableRace);
    READ_DWORD(ItemLevel);
    READ_DWORD(RequiredLevel);
    READ_DWORD(RequiredSkill);
    READ_DWORD(RequiredSkillRank);
    READ_DWORD(RequiredSpell);
    READ_DWORD(RequiredHonorRank);
    READ_DWORD(RequiredCityRank);
    READ_DWORD(RequiredReputationFaction);
    READ_DWORD(RequiredReputationRank);
    READ_DWORD(MaxCount);
    READ_DWORD(Stackable);
    READ_DWORD(ContainerSlots);
    // item stats count
    READ_DWORD(StatsCount);

    for(uint32 i = 0; i < StatsCount; ++i)
    {
        READ_DWORD(ItemStatType);
        READ_DWORD(ItemStatValue);
    }

    READ_DWORD(ScalingStatDistribution)
    READ_DWORD(ScalingStatValue)

    for(int i = 0; i < MAX_ITEM_PROTO_DAMAGES; ++i)
    {
        READ_FLOAT(DamageMin);
        READ_FLOAT(DamageMax);
        READ_DWORD(DamageType);
    }
    READ_DWORD(Armor);
    READ_DWORD(HolyRes);
    READ_DWORD(FireRes);
    READ_DWORD(NatureRes);
    READ_DWORD(FrostRes);
    READ_DWORD(ShadowRes);
    READ_DWORD(ArcaneRes);
    READ_DWORD(Delay);
    READ_DWORD(AmmoType);
    READ_FLOAT(RangedModRange)

    for(int s = 0; s < MAX_ITEM_PROTO_SPELLS; ++s)
    {
        READ_DWORD(SpellId);
        READ_DWORD(SpellTrigger);
        READ_DWORD(SpellCharges);
        READ_DWORD(SpellCooldown);
        READ_DWORD(SpellCategory);
        READ_DWORD(SpellCategoryCooldown);
    }

    READ_DWORD(Bonding);
    READ_UTF8_STRING(Description);
    READ_DWORD(PageText);
    READ_DWORD(LanguageID);
    READ_DWORD(PageMaterial);
    READ_DWORD(StartQuest);
    READ_DWORD(LockID);
    READ_DWORD(Material);
    READ_DWORD(Sheath);
    READ_DWORD(RandomProperty);
    READ_DWORD(RandomSuffix);
    READ_DWORD(Block);
    READ_DWORD(ItemSet);
    READ_DWORD(MaxDurability);
    READ_DWORD(Area);
    // Added in 1.12.x & 2.0.1 client branch
    READ_DWORD(Map);
    READ_DWORD(BagFamily);
    READ_DWORD(TotemCategory);
    for(int s = 0; s < MAX_ITEM_PROTO_SOCKETS; ++s)
    {
        READ_DWORD(Color);
        READ_DWORD(Content);
    }
    READ_DWORD(socketBonus);
    READ_DWORD(GemProperties);
    READ_DWORD(RequiredDisenchantSkill);
    READ_FLOAT(ArmorDamageModifier);
    READ_DWORD(Duration);                      // added in 2.4.2.8209, duration (seconds)
    READ_DWORD(ItemLimitCategory);                  // WotLK, ItemLimitCategory
    READ_DWORD(HolidayId);                          // Holiday.dbc?
    READ_FINISH
}

void    ItemHandler::ReadLootItem(int index, int packIndex, WOWPackage * packet, int &pos)
{
    READ_DWORD(itemid)
    READ_DWORD(count)
    READ_DWORD(display_info_id)
    READ_DWORD(random_suffix)
    READ_DWORD(random_property_id)
    GetGameWorld()->SetData(FormatStr("self/loot/items/%d/itemid", index), itemid);
	GetGameWorld()->SetData(FormatStr("self/loot/items/%d/count", index), count);
	GetGameWorld()->SetData(FormatStr("self/loot/items/%d/index", index), packIndex);
}

void    ItemHandler::ReadLootView(WOWPackage * packet, int &pos)
{
    READ_DWORD(gold)
    READ_BYTE(item_count)
    for(int i=0; i<item_count; i++)
    {
        READ_BYTE(index)
        ReadLootItem(i, index, packet, pos);
        READ_BYTE(get_or_lookonly_slot_type)
    }

    GetGameWorld()->SetData("self/loot/count", item_count);
}

void    ItemHandler::Handler_SMSG_LOOT_RESPONSE(WOWPackage * packet)
{
    int pos = 0;
    READ_UINT64(guid)
    READ_BYTE(loot_type)
    this->ReadLootView(packet, pos);
    READ_FINISH
    GetFiberManager()->Awake(FWC_WAIT_LOOT);
}

void    ItemHandler::Handler_SMSG_LOOT_REMOVED(WOWPackage * packet)
{
    int pos = 0;
    READ_BYTE(index)
    READ_FINISH
}

void    ItemHandler::Handler_SMSG_ITEM_PUSH_RESULT(WOWPackage * packet)
{
    int pos = 0;
    READ_UINT64(guid)
    READ_DWORD(received)
    READ_DWORD(created)
    READ_DWORD(one)
    READ_BYTE(bag_slot)
    READ_DWORD(put_slot)
    READ_DWORD(item_id)
    READ_DWORD(ItemSuffixFactor)
    READ_DWORD(ItemRandomPropertyId)
    READ_DWORD(count)
    READ_DWORD(count_in_bag)
    READ_FINISH    
}

void    ItemHandler::Handler_SMSG_LOOT_RELEASE_RESPONSE(WOWPackage * packet)
{
    int pos = 0;
    READ_UINT64(guid)
    READ_BYTE(one)
    READ_FINISH 
}

void    ItemHandler::Handler_SMSG_LIST_INVENTORY(WOWPackage * packet)
{
	int pos = 0;
	READ_UINT64(vendorguid)
	READ_BYTE(numitems)
	packet->GetComment()->Add("");
	for(int i=0; i<numitems; i++)
	{
		READ_DWORD(index)
		READ_DWORD(itemID)
		packet->AddComment("ItemName", m_GameWorld->GetItemNameByID(itemID));
		READ_DWORD(DisplayInfoID)
		READ_DWORD(maxcount)
		READ_DWORD(price)
		READ_DWORD(MaxDurability)
		READ_DWORD(BuyCount)
		READ_DWORD(ExtendedCost)
		packet->GetComment()->Add("");
	}
	READ_FINISH
}

void    ItemHandler::Handler_SMSG_ITEM_COOLDOWN(WOWPackage * packet)
{
	int pos = 0;
	READ_UINT64(itemGuid)
	READ_DWORD(SpellID)
	packet->AddComment("name", GetSpellNameBySpellID(SpellID));
	READ_FINISH
}
