//---------------------------------------------------------------------------


#pragma hdrstop

#include "DBCStructureInfo.h"
#include "DBCFmt.h"
#include "KOEItlbm.h"
#include <map>
#include <vector>
using namespace std;

//---------------------------------------------------------------------------

#pragma package(smart_init)

String AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(char *lpdata, int len)
{
	String result = AnsiUTF8BIGDataToUnicodeGB(lpdata, len);
	TReplaceFlags   flag;
	flag << rfReplaceAll;
	result = StringReplace(result, "\r\n", " | ", flag);
	result = StringReplace(result, "\n", " | ", flag);
	result = StringReplace(result, "\r", " | ", flag);
	return result;
}


//    output->Add(input->raw.field3);
//    output->Add(input->raw.count);
//    output->Add(input->raw.additionalRequirement1_type);
//    output->Add(input->raw.additionalRequirement1_value);
//    output->Add(input->raw.additionalRequirement2_type);
//    output->Add(input->raw.additionalRequirement2_value);

//    output->Add(FormatStr("(%d)%s_Instanceable(%d)_IsMountAllowed(%d)_IsContinent(%d)", input->map_type, GetMapTypesName(input->map_type), input->Instanceable(),
//            input->IsMountAllowed(), input->IsContinent()));

map<String, tagDBCTableContent >    gTableColumns;
map<String, tagDBCTableContent >    *GetTableColumns()
{
    return  &gTableColumns;
}
void    InitTableColumns()
{
    {
    tagDBCTableContent values;
    values.Columns.push_back("questLevel");
    values.Columns.push_back("xpIndex_0");
    values.Columns.push_back("xpIndex_1");
    values.Columns.push_back("xpIndex_2");
    values.Columns.push_back("xpIndex_3");
    values.Columns.push_back("xpIndex_4");
    values.Columns.push_back("xpIndex_5");
    values.Columns.push_back("xpIndex_6");
    values.Columns.push_back("xpIndex_7");
    values.Columns.push_back("xpIndex_8");
    gTableColumns["QuestXPLevel"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("Id");
    gTableColumns["SoundEntries"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("map_id");
    values.Columns.push_back("x");
    values.Columns.push_back("y");
    values.Columns.push_back("z");
    gTableColumns["WorldSafeLocs"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ratio");
    gTableColumns["GtOCTRegenHP"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("m_ID");
    values.Columns.push_back("m_flags");
    values.Columns.push_back("m_turnSpeed");
    values.Columns.push_back("m_pitchSpeed");
    values.Columns.push_back("m_pitchMin");
    values.Columns.push_back("m_pitchMax");
    values.Columns.push_back("m_seatID_0");
    values.Columns.push_back("m_seatID_1");
    values.Columns.push_back("m_seatID_2");
    values.Columns.push_back("m_seatID_3");
    values.Columns.push_back("m_seatID_4");
    values.Columns.push_back("m_seatID_5");
    values.Columns.push_back("m_seatID_6");
    values.Columns.push_back("m_seatID_7");
    values.Columns.push_back("m_mouseLookOffsetPitch");
    values.Columns.push_back("m_cameraFadeDistScalarMin");
    values.Columns.push_back("m_cameraFadeDistScalarMax");
    values.Columns.push_back("m_cameraPitchOffset");
    values.Columns.push_back("m_facingLimitRight");
    values.Columns.push_back("m_facingLimitLeft");
    values.Columns.push_back("m_msslTrgtTurnLingering");
    values.Columns.push_back("m_msslTrgtPitchLingering");
    values.Columns.push_back("m_msslTrgtMouseLingering");
    values.Columns.push_back("m_msslTrgtEndOpacity");
    values.Columns.push_back("m_msslTrgtArcSpeed");
    values.Columns.push_back("m_msslTrgtArcRepeat");
    values.Columns.push_back("m_msslTrgtArcWidth");
    values.Columns.push_back("m_msslTrgtImpactRadius_0");
    values.Columns.push_back("m_msslTrgtImpactRadius_1");
    values.Columns.push_back("m_msslTrgtArcTexture");
    values.Columns.push_back("m_msslTrgtImpactTexture");
    values.Columns.push_back("m_msslTrgtImpactModel_0");
    values.Columns.push_back("m_msslTrgtImpactModel_1");
    values.Columns.push_back("m_cameraYawOffset");
    values.Columns.push_back("m_uiLocomotionType");
    values.Columns.push_back("m_msslTrgtImpactTexRadius");
    values.Columns.push_back("m_uiSeatIndicatorType");
    gTableColumns["Vehicle"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("content_0");
    values.Columns.push_back("content_1");
    values.Columns.push_back("content_2");
    values.Columns.push_back("content_3");
    values.Columns.push_back("content_4");
    values.Columns.push_back("content_5");
    values.Columns.push_back("content_6");
    values.Columns.push_back("content_7");
    values.Columns.push_back("content_8");
    values.Columns.push_back("content_9");
    values.Columns.push_back("content_10");
    values.Columns.push_back("content_11");
    values.Columns.push_back("content_12");
    values.Columns.push_back("content_13");
    values.Columns.push_back("content_14");
    values.Columns.push_back("content_15");
    gTableColumns["MailTemplate"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("RaceID");
    values.Columns.push_back("FactionID");
    values.Columns.push_back("model_m");
    values.Columns.push_back("model_f");
    values.Columns.push_back("TeamID");
    values.Columns.push_back("CinematicSequence");
    values.Columns.push_back("name_0");
    values.Columns.push_back("name_1");
    values.Columns.push_back("name_2");
    values.Columns.push_back("name_3");
    values.Columns.push_back("name_4");
    values.Columns.push_back("name_5");
    values.Columns.push_back("name_6");
    values.Columns.push_back("name_7");
    values.Columns.push_back("name_8");
    values.Columns.push_back("name_9");
    values.Columns.push_back("name_10");
    values.Columns.push_back("name_11");
    values.Columns.push_back("name_12");
    values.Columns.push_back("name_13");
    values.Columns.push_back("name_14");
    values.Columns.push_back("name_15");
    values.Columns.push_back("expansion");
    gTableColumns["ChrRaces"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("minRange");
    values.Columns.push_back("minRangeFriendly");
    values.Columns.push_back("maxRange");
    values.Columns.push_back("maxRangeFriendly");
    gTableColumns["SpellRange"] = values;
    }
    {
    tagDBCTableContent values;
	values.Columns.push_back("TalentTabID");
    values.Columns.push_back("name_0");
    values.Columns.push_back("name_1");
    values.Columns.push_back("name_2");
    values.Columns.push_back("name_3");
    values.Columns.push_back("name_4");
    values.Columns.push_back("name_5");
    values.Columns.push_back("name_6");
    values.Columns.push_back("name_7");
    values.Columns.push_back("name_8");
    values.Columns.push_back("name_9");
    values.Columns.push_back("name_10");
    values.Columns.push_back("name_11");
    values.Columns.push_back("name_12");
    values.Columns.push_back("name_13");
    values.Columns.push_back("name_14");
	values.Columns.push_back("name_15");
	values.Columns.push_back("nameFlags");
	values.Columns.push_back("spellicon");
    values.Columns.push_back("ClassMask");
    values.Columns.push_back("petTalentMask");
    values.Columns.push_back("tabpage");
    gTableColumns["TalentTab"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    gTableColumns["Holidays"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("spellId_0");
    values.Columns.push_back("spellId_1");
    values.Columns.push_back("spellId_2");
    values.Columns.push_back("spellId_3");
    gTableColumns["CreatureSpellData"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("RuneCost_0");
    values.Columns.push_back("RuneCost_1");
    values.Columns.push_back("RuneCost_2");
    values.Columns.push_back("runePowerGain");
    gTableColumns["SpellRuneCost"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("base");
    gTableColumns["GtChanceToMeleeCritBase"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ratio");
    gTableColumns["GtChanceToMeleeCrit"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("id");
    values.Columns.push_back("mapid_0");
    values.Columns.push_back("mapid_1");
    values.Columns.push_back("mapid_2");
    values.Columns.push_back("mapid_3");
    values.Columns.push_back("mapid_4");
    values.Columns.push_back("mapid_5");
    values.Columns.push_back("mapid_6");
    values.Columns.push_back("mapid_7");
	values.Columns.push_back("type");
	values.Columns.push_back("name_0");
	values.Columns.push_back("name_1");
	values.Columns.push_back("name_2");
	values.Columns.push_back("name_3");
	values.Columns.push_back("name_4");
	values.Columns.push_back("name_5");
	values.Columns.push_back("name_6");
	values.Columns.push_back("name_7");
	values.Columns.push_back("name_8");
	values.Columns.push_back("name_9");
	values.Columns.push_back("name_10");
	values.Columns.push_back("name_11");
	values.Columns.push_back("name_12");
	values.Columns.push_back("name_13");
	values.Columns.push_back("name_14");
	values.Columns.push_back("name_15");
	values.Columns.push_back("maxGroupSize");
	values.Columns.push_back("HolidayWorldStateId");
	values.Columns.push_back("minLevel");
	values.Columns.push_back("maxLevel");
    gTableColumns["BattlemasterList"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("Id");
    values.Columns.push_back("Flags");
    values.Columns.push_back("EmoteType");
    values.Columns.push_back("UnitStandState");
    gTableColumns["Emotes"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("flags1");
    values.Columns.push_back("creatureType");
    values.Columns.push_back("attackSpeed");
    values.Columns.push_back("modelID_A");
    values.Columns.push_back("modelID_H");
    values.Columns.push_back("spellId_0");
    values.Columns.push_back("spellId_1");
    values.Columns.push_back("spellId_2");
    values.Columns.push_back("spellId_3");
    values.Columns.push_back("spellId_4");
    values.Columns.push_back("spellId_5");
    values.Columns.push_back("spellId_6");
    values.Columns.push_back("spellId_7");
    gTableColumns["SpellShapeshift"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("Displayid");
    gTableColumns["GameObjectDisplayInfo"] = values;
    }
    {
    tagDBCTableContent values;
	values.Columns.push_back("ID");
    values.Columns.push_back("name_0");
    values.Columns.push_back("name_1");
    values.Columns.push_back("name_2");
    values.Columns.push_back("name_3");
    values.Columns.push_back("name_4");
    values.Columns.push_back("name_5");
    values.Columns.push_back("name_6");
    values.Columns.push_back("name_7");
    values.Columns.push_back("name_8");
    values.Columns.push_back("name_9");
    values.Columns.push_back("name_10");
    values.Columns.push_back("name_11");
    values.Columns.push_back("name_12");
    values.Columns.push_back("name_13");
    values.Columns.push_back("name_14");
    values.Columns.push_back("name_15");
    values.Columns.push_back("categoryType");
    values.Columns.push_back("categoryMask");
    gTableColumns["TotemCategory"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("price");
    gTableColumns["BankBagSlotPrices"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("spellitemenchantement");
    values.Columns.push_back("color");
    gTableColumns["GemProperties"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("from");
    values.Columns.push_back("to");
    values.Columns.push_back("price");
    gTableColumns["TaxiPath"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("maxCount");
    values.Columns.push_back("mode");
    gTableColumns["ItemLimitCategory"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("areatableID_0");
    values.Columns.push_back("areatableID_1");
    values.Columns.push_back("areatableID_2");
    values.Columns.push_back("areatableID_3");
    gTableColumns["WorldMapOverlay"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("type_0");
    values.Columns.push_back("type_1");
    values.Columns.push_back("type_2");
    values.Columns.push_back("amount_0");
    values.Columns.push_back("amount_1");
    values.Columns.push_back("amount_2");
    values.Columns.push_back("spellid_0");
    values.Columns.push_back("spellid_1");
    values.Columns.push_back("spellid_2");
    values.Columns.push_back("description_0");
    values.Columns.push_back("description_1");
    values.Columns.push_back("description_2");
    values.Columns.push_back("description_3");
    values.Columns.push_back("description_4");
    values.Columns.push_back("description_5");
    values.Columns.push_back("description_6");
    values.Columns.push_back("description_7");
    values.Columns.push_back("description_8");
    values.Columns.push_back("description_9");
    values.Columns.push_back("description_10");
    values.Columns.push_back("description_11");
    values.Columns.push_back("description_12");
    values.Columns.push_back("description_13");
    values.Columns.push_back("description_14");
    values.Columns.push_back("description_15");
    values.Columns.push_back("aura_id");
    values.Columns.push_back("slot");
    values.Columns.push_back("GemID");
    values.Columns.push_back("EnchantmentCondition");
    gTableColumns["SpellItemEnchantment"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("reputationListID");
    values.Columns.push_back("BaseRepRaceMask_0");
    values.Columns.push_back("BaseRepRaceMask_1");
    values.Columns.push_back("BaseRepRaceMask_2");
    values.Columns.push_back("BaseRepRaceMask_3");
    values.Columns.push_back("BaseRepClassMask_0");
    values.Columns.push_back("BaseRepClassMask_1");
    values.Columns.push_back("BaseRepClassMask_2");
    values.Columns.push_back("BaseRepClassMask_3");
    values.Columns.push_back("BaseRepValue_0");
    values.Columns.push_back("BaseRepValue_1");
    values.Columns.push_back("BaseRepValue_2");
    values.Columns.push_back("BaseRepValue_3");
    values.Columns.push_back("ReputationFlags_0");
    values.Columns.push_back("ReputationFlags_1");
    values.Columns.push_back("ReputationFlags_2");
    values.Columns.push_back("ReputationFlags_3");
    values.Columns.push_back("team");
    values.Columns.push_back("name_0");
    values.Columns.push_back("name_1");
    values.Columns.push_back("name_2");
    values.Columns.push_back("name_3");
    values.Columns.push_back("name_4");
    values.Columns.push_back("name_5");
    values.Columns.push_back("name_6");
    values.Columns.push_back("name_7");
    values.Columns.push_back("name_8");
    values.Columns.push_back("name_9");
    values.Columns.push_back("name_10");
    values.Columns.push_back("name_11");
    values.Columns.push_back("name_12");
    values.Columns.push_back("name_13");
    values.Columns.push_back("name_14");
    values.Columns.push_back("name_15");
    gTableColumns["Faction"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("houseId");
    values.Columns.push_back("faction");
    values.Columns.push_back("depositPercent");
	values.Columns.push_back("cutPercent");
    values.Columns.push_back("name_0");
    values.Columns.push_back("name_1");
    values.Columns.push_back("name_2");
    values.Columns.push_back("name_3");
    values.Columns.push_back("name_4");
    values.Columns.push_back("name_5");
    values.Columns.push_back("name_6");
    values.Columns.push_back("name_7");
    values.Columns.push_back("name_8");
    values.Columns.push_back("name_9");
    values.Columns.push_back("name_10");
    values.Columns.push_back("name_11");
    values.Columns.push_back("name_12");
    values.Columns.push_back("name_13");
    values.Columns.push_back("name_14");
    values.Columns.push_back("name_15");
    gTableColumns["AuctionHouse"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("Duration_0");
    values.Columns.push_back("Duration_1");
    values.Columns.push_back("Duration_2");
    gTableColumns["SpellDuration"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("base");
    gTableColumns["GtChanceToSpellCritBase"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("referredAchievement");
    values.Columns.push_back("requiredType");
    values.Columns.push_back("Value1");
    values.Columns.push_back("Value2");
    values.Columns.push_back("Value3");
    values.Columns.push_back("Value4");
    values.Columns.push_back("Value5");
	values.Columns.push_back("Value6");
    values.Columns.push_back("name_0");
    values.Columns.push_back("name_1");
    values.Columns.push_back("name_2");
    values.Columns.push_back("name_3");
    values.Columns.push_back("name_4");
    values.Columns.push_back("name_5");
    values.Columns.push_back("name_6");
    values.Columns.push_back("name_7");
    values.Columns.push_back("name_8");
    values.Columns.push_back("name_9");
    values.Columns.push_back("name_10");
    values.Columns.push_back("name_11");
    values.Columns.push_back("name_12");
    values.Columns.push_back("name_13");
    values.Columns.push_back("name_14");
    values.Columns.push_back("name_15");
    values.Columns.push_back("completionFlag");
    values.Columns.push_back("groupFlag");
    values.Columns.push_back("timeLimit");
    gTableColumns["AchievementCriteria"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("reqhonorpoints");
    values.Columns.push_back("reqarenapoints");
    values.Columns.push_back("reqarenaslot");
    values.Columns.push_back("reqitem_0");
    values.Columns.push_back("reqitem_1");
    values.Columns.push_back("reqitem_2");
    values.Columns.push_back("reqitem_3");
    values.Columns.push_back("reqitem_4");
    values.Columns.push_back("reqitemcount_0");
    values.Columns.push_back("reqitemcount_1");
    values.Columns.push_back("reqitemcount_2");
    values.Columns.push_back("reqitemcount_3");
    values.Columns.push_back("reqitemcount_4");
    values.Columns.push_back("reqpersonalarenarating");
    gTableColumns["ItemExtendedCost"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("AreaGroupId");
    values.Columns.push_back("AreaId_0");
    values.Columns.push_back("AreaId_1");
    values.Columns.push_back("AreaId_2");
    values.Columns.push_back("AreaId_3");
    values.Columns.push_back("AreaId_4");
    values.Columns.push_back("AreaId_5");
    values.Columns.push_back("nextGroup");
    gTableColumns["AreaGroup"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("id");
    values.Columns.push_back("rewardValue_0");
    values.Columns.push_back("rewardValue_1");
    values.Columns.push_back("rewardValue_2");
    values.Columns.push_back("rewardValue_3");
    values.Columns.push_back("rewardValue_4");
    values.Columns.push_back("rewardValue_5");
    values.Columns.push_back("rewardValue_6");
    values.Columns.push_back("rewardValue_7");
    values.Columns.push_back("rewardValue_8");
    values.Columns.push_back("rewardValue_9");
    gTableColumns["QuestFactionReward"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("Id");
    values.Columns.push_back("SpellId");
    values.Columns.push_back("TypeFlags");
    values.Columns.push_back("Unk1");
    gTableColumns["GlyphProperties"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("Class");
    values.Columns.push_back("SubClass");
    values.Columns.push_back("Unk0");
    values.Columns.push_back("Material");
    values.Columns.push_back("DisplayId");
    values.Columns.push_back("InventoryType");
    values.Columns.push_back("Sheath");
    gTableColumns["Item"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("id");
    values.Columns.push_back("categoryId");
    values.Columns.push_back("name_0");
    values.Columns.push_back("name_1");
    values.Columns.push_back("name_2");
    values.Columns.push_back("name_3");
    values.Columns.push_back("name_4");
    values.Columns.push_back("name_5");
    values.Columns.push_back("name_6");
    values.Columns.push_back("name_7");
    values.Columns.push_back("name_8");
    values.Columns.push_back("name_9");
    values.Columns.push_back("name_10");
    values.Columns.push_back("name_11");
    values.Columns.push_back("name_12");
    values.Columns.push_back("name_13");
    values.Columns.push_back("name_14");
	values.Columns.push_back("name_15");
    values.Columns.push_back("description_0");
    values.Columns.push_back("description_1");
    values.Columns.push_back("description_2");
    values.Columns.push_back("description_3");
    values.Columns.push_back("description_4");
    values.Columns.push_back("description_5");
    values.Columns.push_back("description_6");
    values.Columns.push_back("description_7");
    values.Columns.push_back("description_8");
    values.Columns.push_back("description_9");
    values.Columns.push_back("description_10");
    values.Columns.push_back("description_11");
    values.Columns.push_back("description_12");
    values.Columns.push_back("description_13");
    values.Columns.push_back("description_14");
	values.Columns.push_back("description_15");
    values.Columns.push_back("alternateVerb_0");
    values.Columns.push_back("alternateVerb_1");
    values.Columns.push_back("alternateVerb_2");
    values.Columns.push_back("alternateVerb_3");
    values.Columns.push_back("alternateVerb_4");
    values.Columns.push_back("alternateVerb_5");
    values.Columns.push_back("alternateVerb_6");
    values.Columns.push_back("alternateVerb_7");
    values.Columns.push_back("alternateVerb_8");
    values.Columns.push_back("alternateVerb_9");
    values.Columns.push_back("alternateVerb_10");
    values.Columns.push_back("alternateVerb_11");
    values.Columns.push_back("alternateVerb_12");
    values.Columns.push_back("alternateVerb_13");
    values.Columns.push_back("alternateVerb_14");
    values.Columns.push_back("alternateVerb_15");
    values.Columns.push_back("spellIcon");
    values.Columns.push_back("canLink");
    gTableColumns["SkillLine"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("m_ID");
    values.Columns.push_back("m_flags");
    values.Columns.push_back("m_attachmentID");
    values.Columns.push_back("m_attachmentOffsetX");
    values.Columns.push_back("m_attachmentOffsetY");
    values.Columns.push_back("m_attachmentOffsetZ");
    values.Columns.push_back("m_enterPreDelay");
    values.Columns.push_back("m_enterSpeed");
    values.Columns.push_back("m_enterGravity");
    values.Columns.push_back("m_enterMinDuration");
    values.Columns.push_back("m_enterMaxDuration");
    values.Columns.push_back("m_enterMinArcHeight");
    values.Columns.push_back("m_enterMaxArcHeight");
    values.Columns.push_back("m_enterAnimStart");
    values.Columns.push_back("m_enterAnimLoop");
    values.Columns.push_back("m_rideAnimStart");
    values.Columns.push_back("m_rideAnimLoop");
    values.Columns.push_back("m_rideUpperAnimStart");
    values.Columns.push_back("m_rideUpperAnimLoop");
    values.Columns.push_back("m_exitPreDelay");
    values.Columns.push_back("m_exitSpeed");
    values.Columns.push_back("m_exitGravity");
    values.Columns.push_back("m_exitMinDuration");
    values.Columns.push_back("m_exitMaxDuration");
    values.Columns.push_back("m_exitMinArcHeight");
    values.Columns.push_back("m_exitMaxArcHeight");
    values.Columns.push_back("m_exitAnimStart");
    values.Columns.push_back("m_exitAnimLoop");
    values.Columns.push_back("m_exitAnimEnd");
    values.Columns.push_back("m_passengerYaw");
    values.Columns.push_back("m_passengerPitch");
    values.Columns.push_back("m_passengerRoll");
    values.Columns.push_back("m_passengerAttachmentID");
    values.Columns.push_back("m_vehicleEnterAnim");
    values.Columns.push_back("m_vehicleExitAnim");
    values.Columns.push_back("m_vehicleRideAnimLoop");
    values.Columns.push_back("m_vehicleEnterAnimBone");
    values.Columns.push_back("m_vehicleExitAnimBone");
    values.Columns.push_back("m_vehicleRideAnimLoopBone");
    values.Columns.push_back("m_vehicleEnterAnimDelay");
    values.Columns.push_back("m_vehicleExitAnimDelay");
    values.Columns.push_back("m_vehicleAbilityDisplay");
    values.Columns.push_back("m_enterUISoundID");
    values.Columns.push_back("m_exitUISoundID");
    values.Columns.push_back("m_uiSkin");
    values.Columns.push_back("m_flagsB");
    gTableColumns["VehicleSeat"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("faction");
    values.Columns.push_back("factionFlags");
    values.Columns.push_back("ourMask");
    values.Columns.push_back("friendlyMask");
    values.Columns.push_back("hostileMask");
    values.Columns.push_back("enemyFaction_0");
    values.Columns.push_back("enemyFaction_1");
    values.Columns.push_back("enemyFaction_2");
    values.Columns.push_back("enemyFaction_3");
    values.Columns.push_back("friendFaction_0");
    values.Columns.push_back("friendFaction_1");
    values.Columns.push_back("friendFaction_2");
    values.Columns.push_back("friendFaction_3");
    gTableColumns["FactionTemplate"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("map_id");
    values.Columns.push_back("x");
    values.Columns.push_back("y");
    values.Columns.push_back("z");
    values.Columns.push_back("name_0");
    values.Columns.push_back("name_1");
    values.Columns.push_back("name_2");
    values.Columns.push_back("name_3");
    values.Columns.push_back("name_4");
    values.Columns.push_back("name_5");
    values.Columns.push_back("name_6");
    values.Columns.push_back("name_7");
    values.Columns.push_back("name_8");
    values.Columns.push_back("name_9");
    values.Columns.push_back("name_10");
    values.Columns.push_back("name_11");
    values.Columns.push_back("name_12");
    values.Columns.push_back("name_13");
    values.Columns.push_back("name_14");
    values.Columns.push_back("name_15");
    values.Columns.push_back("MountCreatureID_0");
    values.Columns.push_back("MountCreatureID_1");
    gTableColumns["TaxiNodes"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("MapId");
    values.Columns.push_back("Difficulty");
    values.Columns.push_back("resetTime");
    values.Columns.push_back("maxPlayers");
    gTableColumns["MapDifficulty"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("Id");
    values.Columns.push_back("Level");
    values.Columns.push_back("ssdMultiplier_0");
    values.Columns.push_back("ssdMultiplier_1");
    values.Columns.push_back("ssdMultiplier_2");
    values.Columns.push_back("ssdMultiplier_3");
    values.Columns.push_back("armorMod_0");
    values.Columns.push_back("armorMod_1");
    values.Columns.push_back("armorMod_2");
    values.Columns.push_back("armorMod_3");
    values.Columns.push_back("dpsMod_0");
    values.Columns.push_back("dpsMod_1");
    values.Columns.push_back("dpsMod_2");
    values.Columns.push_back("dpsMod_3");
    values.Columns.push_back("dpsMod_4");
    values.Columns.push_back("dpsMod_5");
    values.Columns.push_back("spellBonus");
    values.Columns.push_back("ssdMultiplier2");
    values.Columns.push_back("ssdMultiplier3");
    values.Columns.push_back("armorMod2_0");
    values.Columns.push_back("armorMod2_1");
    values.Columns.push_back("armorMod2_2");
    values.Columns.push_back("armorMod2_3");
    gTableColumns["ScalingStatValues"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("path");
    values.Columns.push_back("index");
    values.Columns.push_back("mapid");
    values.Columns.push_back("x");
    values.Columns.push_back("y");
    values.Columns.push_back("z");
    values.Columns.push_back("actionFlag");
	values.Columns.push_back("delay");
	values.Columns.push_back("delay");
	values.Columns.push_back("arrivalEventID");
	values.Columns.push_back("departureEventID");
    gTableColumns["TaxiPathNode"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ClassID");
	values.Columns.push_back("powerType");
    values.Columns.push_back("name_0");
    values.Columns.push_back("name_1");
    values.Columns.push_back("name_2");
    values.Columns.push_back("name_3");
    values.Columns.push_back("name_4");
    values.Columns.push_back("name_5");
    values.Columns.push_back("name_6");
    values.Columns.push_back("name_7");
    values.Columns.push_back("name_8");
    values.Columns.push_back("name_9");
    values.Columns.push_back("name_10");
    values.Columns.push_back("name_11");
    values.Columns.push_back("name_12");
    values.Columns.push_back("name_13");
    values.Columns.push_back("name_14");
	values.Columns.push_back("name_15");
    values.Columns.push_back("spellfamily");
    values.Columns.push_back("CinematicSequence");
    values.Columns.push_back("expansion");
    gTableColumns["ChrClasses"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("Id");
	values.Columns.push_back("type");
    values.Columns.push_back("name_0");
    values.Columns.push_back("name_1");
    values.Columns.push_back("name_2");
    values.Columns.push_back("name_3");
    values.Columns.push_back("name_4");
    values.Columns.push_back("name_5");
    values.Columns.push_back("name_6");
    values.Columns.push_back("name_7");
    values.Columns.push_back("name_8");
    values.Columns.push_back("name_9");
    values.Columns.push_back("name_10");
    values.Columns.push_back("name_11");
    values.Columns.push_back("name_12");
    values.Columns.push_back("name_13");
    values.Columns.push_back("name_14");
	values.Columns.push_back("name_15");
    values.Columns.push_back("unk_name_0");
    values.Columns.push_back("unk_name_1");
    values.Columns.push_back("unk_name_2");
    values.Columns.push_back("unk_name_3");
    values.Columns.push_back("unk_name_4");
    values.Columns.push_back("unk_name_5");
    values.Columns.push_back("unk_name_6");
    values.Columns.push_back("unk_name_7");
    values.Columns.push_back("unk_name_8");
    values.Columns.push_back("unk_name_9");
    values.Columns.push_back("unk_name_10");
    values.Columns.push_back("unk_name_11");
    values.Columns.push_back("unk_name_12");
    values.Columns.push_back("unk_name_13");
    values.Columns.push_back("unk_name_14");
    values.Columns.push_back("unk_name_15");
	values.Columns.push_back("race");
	values.Columns.push_back("gender");
	values.Columns.push_back("hair_id");
	gTableColumns["BarberShopStyle"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("Id");
    values.Columns.push_back("quality_mod");
    gTableColumns["DurabilityQuality"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("mapid");
    values.Columns.push_back("zone");
    values.Columns.push_back("exploreFlag");
    values.Columns.push_back("flags");
    values.Columns.push_back("area_level");
    values.Columns.push_back("area_name_0");
    values.Columns.push_back("area_name_1");
    values.Columns.push_back("area_name_2");
    values.Columns.push_back("area_name_3");
    values.Columns.push_back("area_name_4");
    values.Columns.push_back("area_name_5");
    values.Columns.push_back("area_name_6");
    values.Columns.push_back("area_name_7");
    values.Columns.push_back("area_name_8");
    values.Columns.push_back("area_name_9");
    values.Columns.push_back("area_name_10");
    values.Columns.push_back("area_name_11");
    values.Columns.push_back("area_name_12");
    values.Columns.push_back("area_name_13");
    values.Columns.push_back("area_name_14");
    values.Columns.push_back("area_name_15");
    values.Columns.push_back("team");
    gTableColumns["AreaTable"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("Id");
    values.Columns.push_back("Category");
    values.Columns.push_back("Dispel");
    values.Columns.push_back("Mechanic");
    values.Columns.push_back("Attributes");
    values.Columns.push_back("AttributesEx");
    values.Columns.push_back("AttributesEx2");
    values.Columns.push_back("AttributesEx3");
    values.Columns.push_back("AttributesEx4");
    values.Columns.push_back("AttributesEx5");
    values.Columns.push_back("AttributesEx6");
    values.Columns.push_back("Stances");
    values.Columns.push_back("StancesNot");
    values.Columns.push_back("Targets");
    values.Columns.push_back("TargetCreatureType");
    values.Columns.push_back("RequiresSpellFocus");
    values.Columns.push_back("FacingCasterFlags");
    values.Columns.push_back("CasterAuraState");
    values.Columns.push_back("TargetAuraState");
    values.Columns.push_back("CasterAuraStateNot");
    values.Columns.push_back("TargetAuraStateNot");
    values.Columns.push_back("casterAuraSpell");
    values.Columns.push_back("targetAuraSpell");
    values.Columns.push_back("excludeCasterAuraSpell");
    values.Columns.push_back("excludeTargetAuraSpell");
    values.Columns.push_back("CastingTimeIndex");
    values.Columns.push_back("RecoveryTime");
    values.Columns.push_back("CategoryRecoveryTime");
    values.Columns.push_back("InterruptFlags");
    values.Columns.push_back("AuraInterruptFlags");
    values.Columns.push_back("ChannelInterruptFlags");
    values.Columns.push_back("procFlags");
    values.Columns.push_back("procChance");
    values.Columns.push_back("procCharges");
    values.Columns.push_back("maxLevel");
    values.Columns.push_back("baseLevel");
    values.Columns.push_back("spellLevel");
    values.Columns.push_back("DurationIndex");
    values.Columns.push_back("powerType");
    values.Columns.push_back("manaCost");
    values.Columns.push_back("manaCostPerlevel");
    values.Columns.push_back("manaPerSecond");
    values.Columns.push_back("manaPerSecondPerLevel");
    values.Columns.push_back("rangeIndex");
    values.Columns.push_back("speed");
    values.Columns.push_back("StackAmount");
    values.Columns.push_back("Totem_0");
    values.Columns.push_back("Totem_1");
    values.Columns.push_back("Reagent_0");
    values.Columns.push_back("Reagent_1");
    values.Columns.push_back("Reagent_2");
    values.Columns.push_back("Reagent_3");
    values.Columns.push_back("Reagent_4");
    values.Columns.push_back("Reagent_5");
    values.Columns.push_back("Reagent_6");
    values.Columns.push_back("Reagent_7");
    values.Columns.push_back("ReagentCount_0");
    values.Columns.push_back("ReagentCount_1");
    values.Columns.push_back("ReagentCount_2");
    values.Columns.push_back("ReagentCount_3");
    values.Columns.push_back("ReagentCount_4");
    values.Columns.push_back("ReagentCount_5");
    values.Columns.push_back("ReagentCount_6");
    values.Columns.push_back("ReagentCount_7");
    values.Columns.push_back("EquippedItemClass");
    values.Columns.push_back("EquippedItemSubClassMask");
    values.Columns.push_back("EquippedItemInventoryTypeMask");
    values.Columns.push_back("Effect_0");
    values.Columns.push_back("Effect_1");
    values.Columns.push_back("Effect_2");
    values.Columns.push_back("EffectDieSides_0");
    values.Columns.push_back("EffectDieSides_1");
    values.Columns.push_back("EffectDieSides_2");
    values.Columns.push_back("EffectRealPointsPerLevel_0");
    values.Columns.push_back("EffectRealPointsPerLevel_1");
    values.Columns.push_back("EffectRealPointsPerLevel_2");
    values.Columns.push_back("EffectBasePoints_0");
    values.Columns.push_back("EffectBasePoints_1");
    values.Columns.push_back("EffectBasePoints_2");
    values.Columns.push_back("EffectMechanic_0");
    values.Columns.push_back("EffectMechanic_1");
    values.Columns.push_back("EffectMechanic_2");
    values.Columns.push_back("EffectImplicitTargetA_0");
    values.Columns.push_back("EffectImplicitTargetA_1");
    values.Columns.push_back("EffectImplicitTargetA_2");
    values.Columns.push_back("EffectImplicitTargetB_0");
    values.Columns.push_back("EffectImplicitTargetB_1");
    values.Columns.push_back("EffectImplicitTargetB_2");
    values.Columns.push_back("EffectRadiusIndex_0");
    values.Columns.push_back("EffectRadiusIndex_1");
    values.Columns.push_back("EffectRadiusIndex_2");
    values.Columns.push_back("EffectApplyAuraName_0");
    values.Columns.push_back("EffectApplyAuraName_1");
    values.Columns.push_back("EffectApplyAuraName_2");
    values.Columns.push_back("EffectAmplitude_0");
    values.Columns.push_back("EffectAmplitude_1");
    values.Columns.push_back("EffectAmplitude_2");
    values.Columns.push_back("EffectMultipleValue_0");
    values.Columns.push_back("EffectMultipleValue_1");
    values.Columns.push_back("EffectMultipleValue_2");
    values.Columns.push_back("EffectChainTarget_0");
    values.Columns.push_back("EffectChainTarget_1");
    values.Columns.push_back("EffectChainTarget_2");
    values.Columns.push_back("EffectItemType_0");
    values.Columns.push_back("EffectItemType_1");
    values.Columns.push_back("EffectItemType_2");
    values.Columns.push_back("EffectMiscValue_0");
    values.Columns.push_back("EffectMiscValue_1");
    values.Columns.push_back("EffectMiscValue_2");
    values.Columns.push_back("EffectMiscValueB_0");
    values.Columns.push_back("EffectMiscValueB_1");
    values.Columns.push_back("EffectMiscValueB_2");
    values.Columns.push_back("EffectTriggerSpell_0");
    values.Columns.push_back("EffectTriggerSpell_1");
    values.Columns.push_back("EffectTriggerSpell_2");
    values.Columns.push_back("EffectPointsPerComboPoint_0");
    values.Columns.push_back("EffectPointsPerComboPoint_1");
    values.Columns.push_back("EffectPointsPerComboPoint_2");
    values.Columns.push_back("EffectSpellClassMaskA_0");
    values.Columns.push_back("EffectSpellClassMaskA_1");
    values.Columns.push_back("EffectSpellClassMaskA_2");
    values.Columns.push_back("EffectSpellClassMaskB_0");
    values.Columns.push_back("EffectSpellClassMaskB_1");
    values.Columns.push_back("EffectSpellClassMaskB_2");
    values.Columns.push_back("EffectSpellClassMaskC_0");
    values.Columns.push_back("EffectSpellClassMaskC_1");
    values.Columns.push_back("EffectSpellClassMaskC_2");
    values.Columns.push_back("SpellVisual_0");
    values.Columns.push_back("SpellVisual_1");
    values.Columns.push_back("SpellIconID");
    values.Columns.push_back("activeIconID");
    values.Columns.push_back("SpellName_0");
    values.Columns.push_back("SpellName_1");
    values.Columns.push_back("SpellName_2");
    values.Columns.push_back("SpellName_3");
    values.Columns.push_back("SpellName_4");
    values.Columns.push_back("SpellName_5");
    values.Columns.push_back("SpellName_6");
    values.Columns.push_back("SpellName_7");
    values.Columns.push_back("SpellName_8");
    values.Columns.push_back("SpellName_9");
    values.Columns.push_back("SpellName_10");
    values.Columns.push_back("SpellName_11");
    values.Columns.push_back("SpellName_12");
    values.Columns.push_back("SpellName_13");
    values.Columns.push_back("SpellName_14");
    values.Columns.push_back("SpellName_15");
    values.Columns.push_back("Rank_0");
    values.Columns.push_back("Rank_1");
    values.Columns.push_back("Rank_2");
    values.Columns.push_back("Rank_3");
    values.Columns.push_back("Rank_4");
    values.Columns.push_back("Rank_5");
    values.Columns.push_back("Rank_6");
    values.Columns.push_back("Rank_7");
    values.Columns.push_back("Rank_8");
    values.Columns.push_back("Rank_9");
    values.Columns.push_back("Rank_10");
    values.Columns.push_back("Rank_11");
    values.Columns.push_back("Rank_12");
    values.Columns.push_back("Rank_13");
    values.Columns.push_back("Rank_14");
	values.Columns.push_back("Rank_15");
	values.Columns.push_back("Description_0");
    values.Columns.push_back("Description_1");
    values.Columns.push_back("Description_2");
    values.Columns.push_back("Description_3");
    values.Columns.push_back("Description_4");
    values.Columns.push_back("Description_5");
    values.Columns.push_back("Description_6");
    values.Columns.push_back("Description_7");
    values.Columns.push_back("Description_8");
    values.Columns.push_back("Description_9");
    values.Columns.push_back("Description_10");
    values.Columns.push_back("Description_11");
    values.Columns.push_back("Description_12");
    values.Columns.push_back("Description_13");
    values.Columns.push_back("Description_14");
	values.Columns.push_back("Description_15");
	values.Columns.push_back("ToolTip_0");
    values.Columns.push_back("ToolTip_1");
    values.Columns.push_back("ToolTip_2");
    values.Columns.push_back("ToolTip_3");
    values.Columns.push_back("ToolTip_4");
    values.Columns.push_back("ToolTip_5");
    values.Columns.push_back("ToolTip_6");
    values.Columns.push_back("ToolTip_7");
    values.Columns.push_back("ToolTip_8");
    values.Columns.push_back("ToolTip_9");
    values.Columns.push_back("ToolTip_10");
    values.Columns.push_back("ToolTip_11");
    values.Columns.push_back("ToolTip_12");
    values.Columns.push_back("ToolTip_13");
    values.Columns.push_back("ToolTip_14");
    values.Columns.push_back("ToolTip_15");
    values.Columns.push_back("ManaCostPercentage");
    values.Columns.push_back("StartRecoveryCategory");
    values.Columns.push_back("StartRecoveryTime");
    values.Columns.push_back("MaxTargetLevel");
    values.Columns.push_back("SpellFamilyName");
    values.Columns.push_back("SpellFamilyFlags");
    values.Columns.push_back("SpellFamilyFlags2");
    values.Columns.push_back("MaxAffectedTargets");
    values.Columns.push_back("DmgClass");
    values.Columns.push_back("PreventionType");
    values.Columns.push_back("DmgMultiplier_0");
    values.Columns.push_back("DmgMultiplier_1");
    values.Columns.push_back("DmgMultiplier_2");
    values.Columns.push_back("TotemCategory_0");
    values.Columns.push_back("TotemCategory_1");
    values.Columns.push_back("AreaGroupId");
    values.Columns.push_back("SchoolMask");
	values.Columns.push_back("runeCostID");
	values.Columns.push_back("SpellDifficultyId");
    gTableColumns["Spell"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    gTableColumns["ItemDisplayInfo"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    gTableColumns["ItemBagFamily"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ratio");
    gTableColumns["GtCombatRatings"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("Id");
    values.Columns.push_back("textid");
    gTableColumns["EmotesText"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("TalentID");
    values.Columns.push_back("TalentTab");
    values.Columns.push_back("Row");
    values.Columns.push_back("Col");
    values.Columns.push_back("RankID_0");
    values.Columns.push_back("RankID_1");
    values.Columns.push_back("RankID_2");
    values.Columns.push_back("RankID_3");
    values.Columns.push_back("RankID_4");
    values.Columns.push_back("DependsOn");
    values.Columns.push_back("DependsOnRank");
    gTableColumns["Talent"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ItemId");
    values.Columns.push_back("BitIndex");
    gTableColumns["CurrencyTypes"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("name_0");
    values.Columns.push_back("name_1");
    values.Columns.push_back("name_2");
    values.Columns.push_back("name_3");
    values.Columns.push_back("name_4");
    values.Columns.push_back("name_5");
    values.Columns.push_back("name_6");
    values.Columns.push_back("name_7");
    values.Columns.push_back("name_8");
    values.Columns.push_back("name_9");
    values.Columns.push_back("name_10");
    values.Columns.push_back("name_11");
    values.Columns.push_back("name_12");
    values.Columns.push_back("name_13");
    values.Columns.push_back("name_14");
    values.Columns.push_back("name_15");
    values.Columns.push_back("spells_0");
    values.Columns.push_back("spells_1");
    values.Columns.push_back("spells_2");
    values.Columns.push_back("spells_3");
    values.Columns.push_back("spells_4");
    values.Columns.push_back("spells_5");
    values.Columns.push_back("spells_6");
    values.Columns.push_back("spells_7");
    values.Columns.push_back("items_to_triggerspell_0");
    values.Columns.push_back("items_to_triggerspell_1");
    values.Columns.push_back("items_to_triggerspell_2");
    values.Columns.push_back("items_to_triggerspell_3");
    values.Columns.push_back("items_to_triggerspell_4");
    values.Columns.push_back("items_to_triggerspell_5");
    values.Columns.push_back("items_to_triggerspell_6");
    values.Columns.push_back("items_to_triggerspell_7");
    values.Columns.push_back("required_skill_id");
    values.Columns.push_back("required_skill_value");
    gTableColumns["ItemSet"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("mapId");
    values.Columns.push_back("bracketId");
    values.Columns.push_back("minLevel");
    values.Columns.push_back("maxLevel");
    values.Columns.push_back("difficulty");
    gTableColumns["PvPDifficulty"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    gTableColumns["CreatureType"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ratio");
    gTableColumns["GtRegenMPPerSpt"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ratio");
    gTableColumns["GtRegenHPPerSpt"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("Id");
    gTableColumns["CinematicSequences"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("id");
    gTableColumns["QuestSort"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("map_id");
    values.Columns.push_back("area_id");
    values.Columns.push_back("y1");
    values.Columns.push_back("y2");
    values.Columns.push_back("x1");
    values.Columns.push_back("x2");
    values.Columns.push_back("virtual_map_id");
    gTableColumns["WorldMapArea"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("nameSuffix_0");
    values.Columns.push_back("nameSuffix_1");
    values.Columns.push_back("nameSuffix_2");
    values.Columns.push_back("nameSuffix_3");
    values.Columns.push_back("nameSuffix_4");
    values.Columns.push_back("nameSuffix_5");
    values.Columns.push_back("nameSuffix_6");
    values.Columns.push_back("nameSuffix_7");
    values.Columns.push_back("nameSuffix_8");
    values.Columns.push_back("nameSuffix_9");
    values.Columns.push_back("nameSuffix_10");
    values.Columns.push_back("nameSuffix_11");
    values.Columns.push_back("nameSuffix_12");
    values.Columns.push_back("nameSuffix_13");
    values.Columns.push_back("nameSuffix_14");
    values.Columns.push_back("nameSuffix_15");
    values.Columns.push_back("enchant_id_0");
    values.Columns.push_back("enchant_id_1");
    values.Columns.push_back("enchant_id_2");
    values.Columns.push_back("enchant_id_3");
    values.Columns.push_back("enchant_id_4");
    values.Columns.push_back("prefix_0");
    values.Columns.push_back("prefix_1");
    values.Columns.push_back("prefix_2");
    values.Columns.push_back("prefix_3");
    values.Columns.push_back("prefix_4");
    gTableColumns["ItemRandomSuffix"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("Id");
    values.Columns.push_back("TypeFlags");
    values.Columns.push_back("Order");
    gTableColumns["GlyphSlot"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("Id");
    gTableColumns["Movie"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("Slot");
    values.Columns.push_back("Price");
    gTableColumns["StableSlotPrices"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("Id");
    values.Columns.push_back("StatMod_0");
    values.Columns.push_back("StatMod_1");
    values.Columns.push_back("StatMod_2");
    values.Columns.push_back("StatMod_3");
    values.Columns.push_back("StatMod_4");
    values.Columns.push_back("StatMod_5");
    values.Columns.push_back("StatMod_6");
    values.Columns.push_back("StatMod_7");
    values.Columns.push_back("StatMod_8");
    values.Columns.push_back("StatMod_9");
    values.Columns.push_back("Modifier_0");
    values.Columns.push_back("Modifier_1");
    values.Columns.push_back("Modifier_2");
    values.Columns.push_back("Modifier_3");
    values.Columns.push_back("Modifier_4");
    values.Columns.push_back("Modifier_5");
    values.Columns.push_back("Modifier_6");
    values.Columns.push_back("Modifier_7");
    values.Columns.push_back("Modifier_8");
    values.Columns.push_back("Modifier_9");
    values.Columns.push_back("MaxLevel");
    gTableColumns["ScalingStatDistribution"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("Itemlvl");
    values.Columns.push_back("multiplier_0");
    values.Columns.push_back("multiplier_1");
    values.Columns.push_back("multiplier_2");
    values.Columns.push_back("multiplier_3");
    values.Columns.push_back("multiplier_4");
    values.Columns.push_back("multiplier_5");
    values.Columns.push_back("multiplier_6");
    values.Columns.push_back("multiplier_7");
    values.Columns.push_back("multiplier_8");
    values.Columns.push_back("multiplier_9");
    values.Columns.push_back("multiplier_10");
    values.Columns.push_back("multiplier_11");
    values.Columns.push_back("multiplier_12");
    values.Columns.push_back("multiplier_13");
    values.Columns.push_back("multiplier_14");
    values.Columns.push_back("multiplier_15");
    values.Columns.push_back("multiplier_16");
    values.Columns.push_back("multiplier_17");
    values.Columns.push_back("multiplier_18");
    values.Columns.push_back("multiplier_19");
    values.Columns.push_back("multiplier_20");
    values.Columns.push_back("multiplier_21");
    values.Columns.push_back("multiplier_22");
    values.Columns.push_back("multiplier_23");
    values.Columns.push_back("multiplier_24");
    values.Columns.push_back("multiplier_25");
    values.Columns.push_back("multiplier_26");
    values.Columns.push_back("multiplier_27");
    values.Columns.push_back("multiplier_28");
    gTableColumns["DurabilityCosts"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("enchant_id_0");
    values.Columns.push_back("enchant_id_1");
    values.Columns.push_back("enchant_id_2");
    values.Columns.push_back("enchant_id_3");
    values.Columns.push_back("enchant_id_4");
    values.Columns.push_back("nameSuffix_0");
    values.Columns.push_back("nameSuffix_1");
    values.Columns.push_back("nameSuffix_2");
    values.Columns.push_back("nameSuffix_3");
    values.Columns.push_back("nameSuffix_4");
    values.Columns.push_back("nameSuffix_5");
    values.Columns.push_back("nameSuffix_6");
    values.Columns.push_back("nameSuffix_7");
    values.Columns.push_back("nameSuffix_8");
    values.Columns.push_back("nameSuffix_9");
    values.Columns.push_back("nameSuffix_10");
    values.Columns.push_back("nameSuffix_11");
    values.Columns.push_back("nameSuffix_12");
    values.Columns.push_back("nameSuffix_13");
    values.Columns.push_back("nameSuffix_14");
    values.Columns.push_back("nameSuffix_15");
    gTableColumns["ItemRandomProperties"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("id");
    values.Columns.push_back("mapid");
    values.Columns.push_back("x");
    values.Columns.push_back("y");
    values.Columns.push_back("z");
    values.Columns.push_back("radius");
    values.Columns.push_back("box_x");
    values.Columns.push_back("box_y");
    values.Columns.push_back("box_z");
    values.Columns.push_back("box_orientation");
    gTableColumns["AreaTrigger"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("MapID");
    values.Columns.push_back("map_type");
    values.Columns.push_back("name_0");
    values.Columns.push_back("name_1");
    values.Columns.push_back("name_2");
    values.Columns.push_back("name_3");
    values.Columns.push_back("name_4");
    values.Columns.push_back("name_5");
    values.Columns.push_back("name_6");
    values.Columns.push_back("name_7");
    values.Columns.push_back("name_8");
    values.Columns.push_back("name_9");
    values.Columns.push_back("name_10");
    values.Columns.push_back("name_11");
    values.Columns.push_back("name_12");
    values.Columns.push_back("name_13");
    values.Columns.push_back("name_14");
    values.Columns.push_back("name_15");
	values.Columns.push_back("linked_zone");
    values.Columns.push_back("hordeIntro_0");
    values.Columns.push_back("hordeIntro_1");
    values.Columns.push_back("hordeIntro_2");
    values.Columns.push_back("hordeIntro_3");
    values.Columns.push_back("hordeIntro_4");
    values.Columns.push_back("hordeIntro_5");
    values.Columns.push_back("hordeIntro_6");
    values.Columns.push_back("hordeIntro_7");
    values.Columns.push_back("hordeIntro_8");
    values.Columns.push_back("hordeIntro_9");
    values.Columns.push_back("hordeIntro_10");
    values.Columns.push_back("hordeIntro_11");
    values.Columns.push_back("hordeIntro_12");
    values.Columns.push_back("hordeIntro_13");
    values.Columns.push_back("hordeIntro_14");
	values.Columns.push_back("hordeIntro_15");
    values.Columns.push_back("allianceIntro_0");
    values.Columns.push_back("allianceIntro_1");
    values.Columns.push_back("allianceIntro_2");
    values.Columns.push_back("allianceIntro_3");
    values.Columns.push_back("allianceIntro_4");
    values.Columns.push_back("allianceIntro_5");
    values.Columns.push_back("allianceIntro_6");
    values.Columns.push_back("allianceIntro_7");
    values.Columns.push_back("allianceIntro_8");
    values.Columns.push_back("allianceIntro_9");
    values.Columns.push_back("allianceIntro_10");
    values.Columns.push_back("allianceIntro_11");
    values.Columns.push_back("allianceIntro_12");
    values.Columns.push_back("allianceIntro_13");
    values.Columns.push_back("allianceIntro_14");
    values.Columns.push_back("allianceIntro_15");
    values.Columns.push_back("multimap_id");
	values.Columns.push_back("ghost_entrance_map");
	values.Columns.push_back("ghost_entrance_x");
	values.Columns.push_back("ghost_entrance_y");
    values.Columns.push_back("addon");
    gTableColumns["Map"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("itemLevel");
    values.Columns.push_back("EpicPropertiesPoints_0");
    values.Columns.push_back("EpicPropertiesPoints_1");
    values.Columns.push_back("EpicPropertiesPoints_2");
    values.Columns.push_back("EpicPropertiesPoints_3");
    values.Columns.push_back("EpicPropertiesPoints_4");
    values.Columns.push_back("RarePropertiesPoints_0");
    values.Columns.push_back("RarePropertiesPoints_1");
    values.Columns.push_back("RarePropertiesPoints_2");
    values.Columns.push_back("RarePropertiesPoints_3");
    values.Columns.push_back("RarePropertiesPoints_4");
    values.Columns.push_back("UncommonPropertiesPoints_0");
    values.Columns.push_back("UncommonPropertiesPoints_1");
    values.Columns.push_back("UncommonPropertiesPoints_2");
    values.Columns.push_back("UncommonPropertiesPoints_3");
    values.Columns.push_back("UncommonPropertiesPoints_4");
    gTableColumns["RandomPropertiesPoints"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("name_0");
    values.Columns.push_back("name_1");
    values.Columns.push_back("name_2");
    values.Columns.push_back("name_3");
    values.Columns.push_back("name_4");
    values.Columns.push_back("name_5");
    values.Columns.push_back("name_6");
    values.Columns.push_back("name_7");
    values.Columns.push_back("name_8");
    values.Columns.push_back("name_9");
    values.Columns.push_back("name_10");
    values.Columns.push_back("name_11");
    values.Columns.push_back("name_12");
    values.Columns.push_back("name_13");
    values.Columns.push_back("name_14");
    values.Columns.push_back("name_15");
    values.Columns.push_back("bit_index");
    gTableColumns["CharTitles"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("Displayid");
    values.Columns.push_back("scale");
    gTableColumns["CreatureDisplayInfo"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("minScale");
    values.Columns.push_back("minScaleLevel");
    values.Columns.push_back("maxScale");
    values.Columns.push_back("maxScaleLevel");
    values.Columns.push_back("skillLine_0");
    values.Columns.push_back("skillLine_1");
    values.Columns.push_back("petFoodMask");
    values.Columns.push_back("petTalentType");
    values.Columns.push_back("Name_0");
    values.Columns.push_back("Name_1");
    values.Columns.push_back("Name_2");
    values.Columns.push_back("Name_3");
    values.Columns.push_back("Name_4");
    values.Columns.push_back("Name_5");
    values.Columns.push_back("Name_6");
    values.Columns.push_back("Name_7");
    values.Columns.push_back("Name_8");
    values.Columns.push_back("Name_9");
    values.Columns.push_back("Name_10");
    values.Columns.push_back("Name_11");
    values.Columns.push_back("Name_12");
    values.Columns.push_back("Name_13");
    values.Columns.push_back("Name_14");
    values.Columns.push_back("Name_15");
    gTableColumns["CreatureFamily"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("factionFlag");
    values.Columns.push_back("mapID");
    values.Columns.push_back("name_0");
    values.Columns.push_back("name_1");
    values.Columns.push_back("name_2");
    values.Columns.push_back("name_3");
    values.Columns.push_back("name_4");
    values.Columns.push_back("name_5");
    values.Columns.push_back("name_6");
    values.Columns.push_back("name_7");
    values.Columns.push_back("name_8");
    values.Columns.push_back("name_9");
    values.Columns.push_back("name_10");
    values.Columns.push_back("name_11");
    values.Columns.push_back("name_12");
    values.Columns.push_back("name_13");
    values.Columns.push_back("name_14");
	values.Columns.push_back("name_15");
    values.Columns.push_back("description_0");
    values.Columns.push_back("description_1");
    values.Columns.push_back("description_2");
    values.Columns.push_back("description_3");
    values.Columns.push_back("description_4");
    values.Columns.push_back("description_5");
    values.Columns.push_back("description_6");
    values.Columns.push_back("description_7");
    values.Columns.push_back("description_8");
    values.Columns.push_back("description_9");
    values.Columns.push_back("description_10");
    values.Columns.push_back("description_11");
    values.Columns.push_back("description_12");
    values.Columns.push_back("description_13");
    values.Columns.push_back("description_14");
    values.Columns.push_back("description_15");
    values.Columns.push_back("categoryId");
    values.Columns.push_back("points");
	values.Columns.push_back("flags");
    values.Columns.push_back("titleReward_0");
    values.Columns.push_back("titleReward_1");
    values.Columns.push_back("titleReward_2");
    values.Columns.push_back("titleReward_3");
    values.Columns.push_back("titleReward_4");
    values.Columns.push_back("titleReward_5");
    values.Columns.push_back("titleReward_6");
    values.Columns.push_back("titleReward_7");
    values.Columns.push_back("titleReward_8");
    values.Columns.push_back("titleReward_9");
    values.Columns.push_back("titleReward_10");
    values.Columns.push_back("titleReward_11");
    values.Columns.push_back("titleReward_12");
    values.Columns.push_back("titleReward_13");
    values.Columns.push_back("titleReward_14");
    values.Columns.push_back("titleReward_15");
    values.Columns.push_back("count");
    values.Columns.push_back("refAchievement");
    gTableColumns["Achievement"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    gTableColumns["SpellFocusObject"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("Radius");
    values.Columns.push_back("Radius2");
    gTableColumns["SpellRadius"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ChannelID");
    values.Columns.push_back("flags");
    values.Columns.push_back("pattern_0");
    values.Columns.push_back("pattern_1");
    values.Columns.push_back("pattern_2");
    values.Columns.push_back("pattern_3");
    values.Columns.push_back("pattern_4");
    values.Columns.push_back("pattern_5");
    values.Columns.push_back("pattern_6");
    values.Columns.push_back("pattern_7");
    values.Columns.push_back("pattern_8");
    values.Columns.push_back("pattern_9");
    values.Columns.push_back("pattern_10");
    values.Columns.push_back("pattern_11");
    values.Columns.push_back("pattern_12");
    values.Columns.push_back("pattern_13");
    values.Columns.push_back("pattern_14");
    values.Columns.push_back("pattern_15");
    gTableColumns["ChatChannels"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("id");
    values.Columns.push_back("skillId");
    values.Columns.push_back("spellId");
    values.Columns.push_back("racemask");
    values.Columns.push_back("classmask");
    values.Columns.push_back("req_skill_value");
    values.Columns.push_back("forward_spellid");
    values.Columns.push_back("learnOnGetSkill");
    values.Columns.push_back("max_value");
    values.Columns.push_back("min_value");
    gTableColumns["SkillLineAbility"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("RaceClassGender");
    values.Columns.push_back("ItemId_0");
    values.Columns.push_back("ItemId_1");
    values.Columns.push_back("ItemId_2");
    values.Columns.push_back("ItemId_3");
    values.Columns.push_back("ItemId_4");
    values.Columns.push_back("ItemId_5");
    values.Columns.push_back("ItemId_6");
    values.Columns.push_back("ItemId_7");
    values.Columns.push_back("ItemId_8");
    values.Columns.push_back("ItemId_9");
    values.Columns.push_back("ItemId_10");
    values.Columns.push_back("ItemId_11");
    values.Columns.push_back("ItemId_12");
    values.Columns.push_back("ItemId_13");
    values.Columns.push_back("ItemId_14");
    values.Columns.push_back("ItemId_15");
    values.Columns.push_back("ItemId_16");
    values.Columns.push_back("ItemId_17");
    values.Columns.push_back("ItemId_18");
    values.Columns.push_back("ItemId_19");
    values.Columns.push_back("ItemId_20");
    values.Columns.push_back("ItemId_21");
    values.Columns.push_back("ItemId_22");
    values.Columns.push_back("ItemId_23");
    gTableColumns["CharStartOutfit"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("parentCategory");
    gTableColumns["AchievementCategory"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("Type_0");
    values.Columns.push_back("Type_1");
    values.Columns.push_back("Type_2");
    values.Columns.push_back("Type_3");
    values.Columns.push_back("Type_4");
    values.Columns.push_back("Type_5");
    values.Columns.push_back("Type_6");
    values.Columns.push_back("Type_7");
    values.Columns.push_back("Index_0");
    values.Columns.push_back("Index_1");
    values.Columns.push_back("Index_2");
    values.Columns.push_back("Index_3");
    values.Columns.push_back("Index_4");
    values.Columns.push_back("Index_5");
    values.Columns.push_back("Index_6");
    values.Columns.push_back("Index_7");
    values.Columns.push_back("Skill_0");
    values.Columns.push_back("Skill_1");
    values.Columns.push_back("Skill_2");
    values.Columns.push_back("Skill_3");
    values.Columns.push_back("Skill_4");
    values.Columns.push_back("Skill_5");
    values.Columns.push_back("Skill_6");
    values.Columns.push_back("Skill_7");
    gTableColumns["Lock"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ratio");
    gTableColumns["GtChanceToSpellCrit"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("Color_0");
    values.Columns.push_back("Color_1");
    values.Columns.push_back("Color_2");
    values.Columns.push_back("Color_3");
    values.Columns.push_back("Color_4");
    values.Columns.push_back("Comparator_0");
    values.Columns.push_back("Comparator_1");
    values.Columns.push_back("Comparator_2");
    values.Columns.push_back("Comparator_3");
    values.Columns.push_back("Comparator_4");
    values.Columns.push_back("CompareColor_0");
    values.Columns.push_back("CompareColor_1");
    values.Columns.push_back("CompareColor_2");
    values.Columns.push_back("CompareColor_3");
    values.Columns.push_back("CompareColor_4");
    values.Columns.push_back("Value_0");
    values.Columns.push_back("Value_1");
    values.Columns.push_back("Value_2");
    values.Columns.push_back("Value_3");
    values.Columns.push_back("Value_4");
    gTableColumns["SpellItemEnchantmentCondition"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("Id");
    values.Columns.push_back("Group");
    values.Columns.push_back("FactionId");
    values.Columns.push_back("Type");
    values.Columns.push_back("Slot");
    values.Columns.push_back("Flags");
    gTableColumns["SummonProperties"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
    values.Columns.push_back("CastTime");
    gTableColumns["SpellCastTimes"] = values;
	}
    {
    tagDBCTableContent values;
    values.Columns.push_back("ID");
	values.Columns.push_back("spellId_0");
	values.Columns.push_back("spellId_1");
	values.Columns.push_back("spellId_2");
	values.Columns.push_back("spellId_3");
    gTableColumns["SpellDifficulty"] = values;
    }
    {
    tagDBCTableContent values;
    values.Columns.push_back("cost");
    gTableColumns["GtBarberShopCostBase"] = values;
    }

}


//====================================================================================
void QuestXPLevel_Output(const QuestXPLevel *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->questLevel);
    output->Add(input->xpIndex[0]);
    output->Add(input->xpIndex[1]);
    output->Add(input->xpIndex[2]);
    output->Add(input->xpIndex[3]);
    output->Add(input->xpIndex[4]);
    output->Add(input->xpIndex[5]);
    output->Add(input->xpIndex[6]);
    output->Add(input->xpIndex[7]);
    output->Add(input->xpIndex[8]);
}
void SoundEntries_Output(const SoundEntriesEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->Id);
}
void WorldSafeLocs_Output(const WorldSafeLocsEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->map_id);
    output->Add(input->x);
    output->Add(input->y);
    output->Add(input->z);
}
void GtOCTRegenHP_Output(const GtOCTRegenHPEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ratio);
}
void Vehicle_Output(const VehicleEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->m_ID);
    output->Add(input->m_flags);
    output->Add(input->m_turnSpeed);
    output->Add(input->m_pitchSpeed);
    output->Add(input->m_pitchMin);
    output->Add(input->m_pitchMax);
    output->Add(input->m_seatID[0]);
    output->Add(input->m_seatID[1]);
    output->Add(input->m_seatID[2]);
    output->Add(input->m_seatID[3]);
    output->Add(input->m_seatID[4]);
    output->Add(input->m_seatID[5]);
    output->Add(input->m_seatID[6]);
    output->Add(input->m_seatID[7]);
    output->Add(input->m_mouseLookOffsetPitch);
    output->Add(input->m_cameraFadeDistScalarMin);
    output->Add(input->m_cameraFadeDistScalarMax);
    output->Add(input->m_cameraPitchOffset);
    output->Add(input->m_facingLimitRight);
    output->Add(input->m_facingLimitLeft);
    output->Add(input->m_msslTrgtTurnLingering);
    output->Add(input->m_msslTrgtPitchLingering);
    output->Add(input->m_msslTrgtMouseLingering);
    output->Add(input->m_msslTrgtEndOpacity);
    output->Add(input->m_msslTrgtArcSpeed);
    output->Add(input->m_msslTrgtArcRepeat);
    output->Add(input->m_msslTrgtArcWidth);
    output->Add(input->m_msslTrgtImpactRadius[0]);
    output->Add(input->m_msslTrgtImpactRadius[1]);
	output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->m_msslTrgtArcTexture, strlen(input->m_msslTrgtArcTexture)));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->m_msslTrgtImpactTexture, strlen(input->m_msslTrgtImpactTexture)));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->m_msslTrgtImpactModel[0], strlen(input->m_msslTrgtImpactModel[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->m_msslTrgtImpactModel[1], strlen(input->m_msslTrgtImpactModel[1])));
    output->Add(input->m_cameraYawOffset);
    output->Add(input->m_uiLocomotionType);
    output->Add(input->m_msslTrgtImpactTexRadius);
    output->Add(input->m_uiSeatIndicatorType);
}
void MailTemplate_Output(const MailTemplateEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->content[0], strlen(input->content[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->content[1], strlen(input->content[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->content[2], strlen(input->content[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->content[3], strlen(input->content[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->content[4], strlen(input->content[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->content[5], strlen(input->content[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->content[6], strlen(input->content[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->content[7], strlen(input->content[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->content[8], strlen(input->content[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->content[9], strlen(input->content[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->content[10], strlen(input->content[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->content[11], strlen(input->content[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->content[12], strlen(input->content[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->content[13], strlen(input->content[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->content[14], strlen(input->content[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->content[15], strlen(input->content[15])));
}
void ChrRaces_Output(const ChrRacesEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->RaceID);
    output->Add(input->FactionID);
    output->Add(input->model_m);
    output->Add(input->model_f);
    output->Add(input->TeamID);
    output->Add(input->CinematicSequence);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[0], strlen(input->name[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[1], strlen(input->name[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[2], strlen(input->name[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[3], strlen(input->name[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[4], strlen(input->name[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[5], strlen(input->name[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[6], strlen(input->name[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[7], strlen(input->name[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[8], strlen(input->name[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[9], strlen(input->name[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[10], strlen(input->name[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[11], strlen(input->name[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[12], strlen(input->name[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[13], strlen(input->name[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[14], strlen(input->name[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[15], strlen(input->name[15])));
    output->Add(input->expansion);
}
void SpellRange_Output(const SpellRangeEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->minRange);
    output->Add(input->minRangeFriendly);
    output->Add(input->maxRange);
    output->Add(input->maxRangeFriendly);
}
void TalentTab_Output(const TalentTabEntry *input, TStrings *output)
{
    if(!input) return;
	output->Add(input->TalentTabID);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[0], strlen(input->name[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[1], strlen(input->name[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[2], strlen(input->name[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[3], strlen(input->name[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[4], strlen(input->name[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[5], strlen(input->name[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[6], strlen(input->name[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[7], strlen(input->name[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[8], strlen(input->name[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[9], strlen(input->name[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[10], strlen(input->name[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[11], strlen(input->name[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[12], strlen(input->name[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[13], strlen(input->name[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[14], strlen(input->name[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[15], strlen(input->name[15])));
	output->Add(input->nameFlags);
	output->Add(input->spellicon);
	output->Add(input->ClassMask);
    output->Add(input->petTalentMask);
    output->Add(input->tabpage);
}
void Holidays_Output(const HolidaysEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
}
void CreatureSpellData_Output(const CreatureSpellDataEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->spellId[0]);
    output->Add(input->spellId[1]);
    output->Add(input->spellId[2]);
    output->Add(input->spellId[3]);
}
void SpellRuneCost_Output(const SpellRuneCostEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->RuneCost[0]);
    output->Add(input->RuneCost[1]);
    output->Add(input->RuneCost[2]);
    output->Add(input->runePowerGain);
}
void GtChanceToMeleeCritBase_Output(const GtChanceToMeleeCritBaseEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->base);
}
void GtChanceToMeleeCrit_Output(const GtChanceToMeleeCritEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ratio);
}
void BattlemasterList_Output(const BattlemasterListEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->id);
    output->Add(input->mapid[0]);
    output->Add(input->mapid[1]);
    output->Add(input->mapid[2]);
    output->Add(input->mapid[3]);
    output->Add(input->mapid[4]);
    output->Add(input->mapid[5]);
    output->Add(input->mapid[6]);
    output->Add(input->mapid[7]);
    output->Add(input->type);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[0], strlen(input->name[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[1], strlen(input->name[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[2], strlen(input->name[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[3], strlen(input->name[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[4], strlen(input->name[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[5], strlen(input->name[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[6], strlen(input->name[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[7], strlen(input->name[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[8], strlen(input->name[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[9], strlen(input->name[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[10], strlen(input->name[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[11], strlen(input->name[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[12], strlen(input->name[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[13], strlen(input->name[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[14], strlen(input->name[14])));
	output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[15], strlen(input->name[15])));
	output->Add(input->maxGroupSize);
	output->Add(input->HolidayWorldStateId);
	output->Add(input->minLevel);
	output->Add(input->maxLevel);
}
void Emotes_Output(const EmotesEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->Id);
    output->Add(input->Flags);
    output->Add(input->EmoteType);
    output->Add(input->UnitStandState);
}
void SpellShapeshift_Output(const SpellShapeshiftEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->flags1);
    output->Add(input->creatureType);
    output->Add(input->attackSpeed);
    output->Add(input->modelID_A);
    output->Add(input->modelID_H);
    output->Add(input->spellId[0]);
    output->Add(input->spellId[1]);
    output->Add(input->spellId[2]);
    output->Add(input->spellId[3]);
    output->Add(input->spellId[4]);
    output->Add(input->spellId[5]);
    output->Add(input->spellId[6]);
    output->Add(input->spellId[7]);
}
void GameObjectDisplayInfo_Output(const GameObjectDisplayInfoEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->Displayid);
}
void TotemCategory_Output(const TotemCategoryEntry *input, TStrings *output)
{
    if(!input) return;
	output->Add(input->ID);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[0], strlen(input->name[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[1], strlen(input->name[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[2], strlen(input->name[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[3], strlen(input->name[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[4], strlen(input->name[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[5], strlen(input->name[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[6], strlen(input->name[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[7], strlen(input->name[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[8], strlen(input->name[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[9], strlen(input->name[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[10], strlen(input->name[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[11], strlen(input->name[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[12], strlen(input->name[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[13], strlen(input->name[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[14], strlen(input->name[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[15], strlen(input->name[15])));
    output->Add(input->categoryType);
    output->Add(input->categoryMask);
}
void BankBagSlotPrices_Output(const BankBagSlotPricesEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->price);
}
void GemProperties_Output(const GemPropertiesEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->spellitemenchantement);
    output->Add(input->color);
}
void TaxiPath_Output(const TaxiPathEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->from);
    output->Add(input->to);
    output->Add(input->price);
}
void ItemLimitCategory_Output(const ItemLimitCategoryEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->maxCount);
    output->Add(input->mode);
}
void WorldMapOverlay_Output(const WorldMapOverlayEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->areatableID[0]);
    output->Add(input->areatableID[1]);
    output->Add(input->areatableID[2]);
    output->Add(input->areatableID[3]);
}
void SpellItemEnchantment_Output(const SpellItemEnchantmentEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->type[0]);
    output->Add(input->type[1]);
    output->Add(input->type[2]);
    output->Add(input->amount[0]);
    output->Add(input->amount[1]);
    output->Add(input->amount[2]);
    output->Add(input->spellid[0]);
    output->Add(input->spellid[1]);
    output->Add(input->spellid[2]);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[0], strlen(input->description[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[1], strlen(input->description[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[2], strlen(input->description[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[3], strlen(input->description[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[4], strlen(input->description[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[5], strlen(input->description[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[6], strlen(input->description[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[7], strlen(input->description[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[8], strlen(input->description[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[9], strlen(input->description[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[10], strlen(input->description[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[11], strlen(input->description[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[12], strlen(input->description[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[13], strlen(input->description[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[14], strlen(input->description[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[15], strlen(input->description[15])));
    output->Add(input->aura_id);
    output->Add(input->slot);
    output->Add(input->GemID);
    output->Add(input->EnchantmentCondition);
}
void Faction_Output(const FactionEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->reputationListID);
    output->Add(input->BaseRepRaceMask[0]);
    output->Add(input->BaseRepRaceMask[1]);
    output->Add(input->BaseRepRaceMask[2]);
    output->Add(input->BaseRepRaceMask[3]);
    output->Add(input->BaseRepClassMask[0]);
    output->Add(input->BaseRepClassMask[1]);
    output->Add(input->BaseRepClassMask[2]);
    output->Add(input->BaseRepClassMask[3]);
    output->Add(input->BaseRepValue[0]);
    output->Add(input->BaseRepValue[1]);
    output->Add(input->BaseRepValue[2]);
    output->Add(input->BaseRepValue[3]);
    output->Add(input->ReputationFlags[0]);
    output->Add(input->ReputationFlags[1]);
    output->Add(input->ReputationFlags[2]);
    output->Add(input->ReputationFlags[3]);
    output->Add(input->team);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[0], strlen(input->name[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[1], strlen(input->name[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[2], strlen(input->name[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[3], strlen(input->name[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[4], strlen(input->name[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[5], strlen(input->name[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[6], strlen(input->name[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[7], strlen(input->name[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[8], strlen(input->name[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[9], strlen(input->name[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[10], strlen(input->name[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[11], strlen(input->name[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[12], strlen(input->name[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[13], strlen(input->name[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[14], strlen(input->name[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[15], strlen(input->name[15])));
}
void AuctionHouse_Output(const AuctionHouseEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->houseId);
    output->Add(input->faction);
    output->Add(input->depositPercent);
	output->Add(input->cutPercent);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[0], strlen(input->name[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[1], strlen(input->name[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[2], strlen(input->name[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[3], strlen(input->name[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[4], strlen(input->name[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[5], strlen(input->name[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[6], strlen(input->name[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[7], strlen(input->name[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[8], strlen(input->name[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[9], strlen(input->name[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[10], strlen(input->name[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[11], strlen(input->name[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[12], strlen(input->name[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[13], strlen(input->name[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[14], strlen(input->name[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[15], strlen(input->name[15])));
}
void SpellDuration_Output(const SpellDurationEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->Duration[0]);
    output->Add(input->Duration[1]);
    output->Add(input->Duration[2]);
}
void GtChanceToSpellCritBase_Output(const GtChanceToSpellCritBaseEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->base);
}
void AchievementCriteria_Output(const AchievementCriteriaEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->referredAchievement);
    output->Add(input->requiredType);
    output->Add(input->raw.field3);
    output->Add(input->raw.count);
    output->Add(input->raw.additionalRequirement1_type);
    output->Add(input->raw.additionalRequirement1_value);
    output->Add(input->raw.additionalRequirement2_type);
	output->Add(input->raw.additionalRequirement2_value);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[0], strlen(input->name[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[1], strlen(input->name[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[2], strlen(input->name[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[3], strlen(input->name[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[4], strlen(input->name[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[5], strlen(input->name[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[6], strlen(input->name[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[7], strlen(input->name[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[8], strlen(input->name[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[9], strlen(input->name[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[10], strlen(input->name[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[11], strlen(input->name[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[12], strlen(input->name[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[13], strlen(input->name[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[14], strlen(input->name[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[15], strlen(input->name[15])));
    output->Add(input->completionFlag);
    output->Add(input->groupFlag);
    output->Add(input->timeLimit);
}
void ItemExtendedCost_Output(const ItemExtendedCostEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->reqhonorpoints);
    output->Add(input->reqarenapoints);
    output->Add(input->reqarenaslot);
    output->Add(input->reqitem[0]);
    output->Add(input->reqitem[1]);
    output->Add(input->reqitem[2]);
    output->Add(input->reqitem[3]);
    output->Add(input->reqitem[4]);
    output->Add(input->reqitemcount[0]);
    output->Add(input->reqitemcount[1]);
    output->Add(input->reqitemcount[2]);
    output->Add(input->reqitemcount[3]);
    output->Add(input->reqitemcount[4]);
    output->Add(input->reqpersonalarenarating);
}
void AreaGroup_Output(const AreaGroupEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->AreaGroupId);
    output->Add(input->AreaId[0]);
    output->Add(input->AreaId[1]);
    output->Add(input->AreaId[2]);
    output->Add(input->AreaId[3]);
    output->Add(input->AreaId[4]);
    output->Add(input->AreaId[5]);
    output->Add(input->nextGroup);
}
void QuestFactionReward_Output(const QuestFactionRewardEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->id);
    output->Add(input->rewardValue[0]);
    output->Add(input->rewardValue[1]);
    output->Add(input->rewardValue[2]);
    output->Add(input->rewardValue[3]);
    output->Add(input->rewardValue[4]);
    output->Add(input->rewardValue[5]);
    output->Add(input->rewardValue[6]);
    output->Add(input->rewardValue[7]);
    output->Add(input->rewardValue[8]);
    output->Add(input->rewardValue[9]);
}
void GlyphProperties_Output(const GlyphPropertiesEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->Id);
    output->Add(input->SpellId);
    output->Add(input->TypeFlags);
    output->Add(input->Unk1);
}
void Item_Output(const ItemEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->Class);
    output->Add(input->SubClass);
    output->Add(input->Unk0);
    output->Add(input->Material);
    output->Add(input->DisplayId);
    output->Add(input->InventoryType);
    output->Add(input->Sheath);
}
void SkillLine_Output(const SkillLineEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->id);
    output->Add(input->categoryId);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[0], strlen(input->name[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[1], strlen(input->name[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[2], strlen(input->name[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[3], strlen(input->name[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[4], strlen(input->name[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[5], strlen(input->name[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[6], strlen(input->name[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[7], strlen(input->name[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[8], strlen(input->name[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[9], strlen(input->name[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[10], strlen(input->name[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[11], strlen(input->name[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[12], strlen(input->name[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[13], strlen(input->name[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[14], strlen(input->name[14])));
	output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[15], strlen(input->name[15])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[0], strlen(input->description[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[1], strlen(input->description[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[2], strlen(input->description[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[3], strlen(input->description[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[4], strlen(input->description[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[5], strlen(input->description[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[6], strlen(input->description[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[7], strlen(input->description[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[8], strlen(input->description[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[9], strlen(input->description[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[10], strlen(input->description[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[11], strlen(input->description[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[12], strlen(input->description[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[13], strlen(input->description[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[14], strlen(input->description[14])));
	output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[15], strlen(input->description[15])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->alternateVerb[0], strlen(input->alternateVerb[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->alternateVerb[1], strlen(input->alternateVerb[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->alternateVerb[2], strlen(input->alternateVerb[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->alternateVerb[3], strlen(input->alternateVerb[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->alternateVerb[4], strlen(input->alternateVerb[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->alternateVerb[5], strlen(input->alternateVerb[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->alternateVerb[6], strlen(input->alternateVerb[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->alternateVerb[7], strlen(input->alternateVerb[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->alternateVerb[8], strlen(input->alternateVerb[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->alternateVerb[9], strlen(input->alternateVerb[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->alternateVerb[10], strlen(input->alternateVerb[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->alternateVerb[11], strlen(input->alternateVerb[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->alternateVerb[12], strlen(input->alternateVerb[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->alternateVerb[13], strlen(input->alternateVerb[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->alternateVerb[14], strlen(input->alternateVerb[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->alternateVerb[15], strlen(input->alternateVerb[15])));
    output->Add(input->spellIcon);
    output->Add(input->canLink);
}
void VehicleSeat_Output(const VehicleSeatEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->m_ID);
    output->Add(input->m_flags);
    output->Add(input->m_attachmentID);
    output->Add(input->m_attachmentOffsetX);
    output->Add(input->m_attachmentOffsetY);
    output->Add(input->m_attachmentOffsetZ);
    output->Add(input->m_enterPreDelay);
    output->Add(input->m_enterSpeed);
    output->Add(input->m_enterGravity);
    output->Add(input->m_enterMinDuration);
    output->Add(input->m_enterMaxDuration);
    output->Add(input->m_enterMinArcHeight);
    output->Add(input->m_enterMaxArcHeight);
    output->Add(input->m_enterAnimStart);
    output->Add(input->m_enterAnimLoop);
    output->Add(input->m_rideAnimStart);
    output->Add(input->m_rideAnimLoop);
    output->Add(input->m_rideUpperAnimStart);
    output->Add(input->m_rideUpperAnimLoop);
    output->Add(input->m_exitPreDelay);
    output->Add(input->m_exitSpeed);
    output->Add(input->m_exitGravity);
    output->Add(input->m_exitMinDuration);
    output->Add(input->m_exitMaxDuration);
    output->Add(input->m_exitMinArcHeight);
    output->Add(input->m_exitMaxArcHeight);
    output->Add(input->m_exitAnimStart);
    output->Add(input->m_exitAnimLoop);
    output->Add(input->m_exitAnimEnd);
    output->Add(input->m_passengerYaw);
    output->Add(input->m_passengerPitch);
    output->Add(input->m_passengerRoll);
    output->Add(input->m_passengerAttachmentID);
    output->Add(input->m_vehicleEnterAnim);
    output->Add(input->m_vehicleExitAnim);
    output->Add(input->m_vehicleRideAnimLoop);
    output->Add(input->m_vehicleEnterAnimBone);
    output->Add(input->m_vehicleExitAnimBone);
    output->Add(input->m_vehicleRideAnimLoopBone);
    output->Add(input->m_vehicleEnterAnimDelay);
    output->Add(input->m_vehicleExitAnimDelay);
    output->Add(input->m_vehicleAbilityDisplay);
    output->Add(input->m_enterUISoundID);
    output->Add(input->m_exitUISoundID);
    output->Add(input->m_uiSkin);
    output->Add(input->m_flagsB);
}
void FactionTemplate_Output(const FactionTemplateEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->faction);
    output->Add(input->factionFlags);
    output->Add(input->ourMask);
    output->Add(input->friendlyMask);
    output->Add(input->hostileMask);
    output->Add(input->enemyFaction[0]);
    output->Add(input->enemyFaction[1]);
    output->Add(input->enemyFaction[2]);
    output->Add(input->enemyFaction[3]);
    output->Add(input->friendFaction[0]);
    output->Add(input->friendFaction[1]);
    output->Add(input->friendFaction[2]);
    output->Add(input->friendFaction[3]);
}
void TaxiNodes_Output(const TaxiNodesEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->map_id);
    output->Add(input->x);
    output->Add(input->y);
    output->Add(input->z);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[0], strlen(input->name[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[1], strlen(input->name[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[2], strlen(input->name[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[3], strlen(input->name[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[4], strlen(input->name[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[5], strlen(input->name[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[6], strlen(input->name[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[7], strlen(input->name[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[8], strlen(input->name[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[9], strlen(input->name[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[10], strlen(input->name[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[11], strlen(input->name[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[12], strlen(input->name[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[13], strlen(input->name[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[14], strlen(input->name[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[15], strlen(input->name[15])));
    output->Add(input->MountCreatureID[0]);
    output->Add(input->MountCreatureID[1]);
}
void MapDifficulty_Output(const MapDifficultyEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->MapId);
    output->Add(input->Difficulty);
    output->Add(input->resetTime);
    output->Add(input->maxPlayers);
}
void ScalingStatValues_Output(const ScalingStatValuesEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->Id);
    output->Add(input->Level);
    output->Add(input->ssdMultiplier[0]);
    output->Add(input->ssdMultiplier[1]);
    output->Add(input->ssdMultiplier[2]);
    output->Add(input->ssdMultiplier[3]);
    output->Add(input->armorMod[0]);
    output->Add(input->armorMod[1]);
    output->Add(input->armorMod[2]);
    output->Add(input->armorMod[3]);
    output->Add(input->dpsMod[0]);
    output->Add(input->dpsMod[1]);
    output->Add(input->dpsMod[2]);
    output->Add(input->dpsMod[3]);
    output->Add(input->dpsMod[4]);
    output->Add(input->dpsMod[5]);
    output->Add(input->spellBonus);
    output->Add(input->ssdMultiplier2);
    output->Add(input->ssdMultiplier3);
    output->Add(input->armorMod2[0]);
    output->Add(input->armorMod2[1]);
    output->Add(input->armorMod2[2]);
    output->Add(input->armorMod2[3]);
}
void TaxiPathNode_Output(const TaxiPathNodeEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->path);
    output->Add(input->index);
    output->Add(input->mapid);
    output->Add(input->x);
    output->Add(input->y);
    output->Add(input->z);
    output->Add(input->actionFlag);
	output->Add(input->delay);
	output->Add(input->arrivalEventID);
	output->Add(input->departureEventID);
}
void ChrClasses_Output(const ChrClassesEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ClassID);
	output->Add(input->powerType);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[0], strlen(input->name[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[1], strlen(input->name[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[2], strlen(input->name[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[3], strlen(input->name[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[4], strlen(input->name[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[5], strlen(input->name[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[6], strlen(input->name[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[7], strlen(input->name[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[8], strlen(input->name[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[9], strlen(input->name[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[10], strlen(input->name[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[11], strlen(input->name[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[12], strlen(input->name[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[13], strlen(input->name[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[14], strlen(input->name[14])));
	output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[15], strlen(input->name[15])));
    output->Add(input->spellfamily);
    output->Add(input->CinematicSequence);
    output->Add(input->expansion);
}
void BarberShopStyle_Output(const BarberShopStyleEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->Id);
	output->Add(input->type);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[0], strlen(input->name[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[1], strlen(input->name[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[2], strlen(input->name[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[3], strlen(input->name[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[4], strlen(input->name[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[5], strlen(input->name[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[6], strlen(input->name[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[7], strlen(input->name[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[8], strlen(input->name[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[9], strlen(input->name[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[10], strlen(input->name[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[11], strlen(input->name[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[12], strlen(input->name[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[13], strlen(input->name[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[14], strlen(input->name[14])));
	output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[15], strlen(input->name[15])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->unk_name[0], strlen(input->unk_name[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->unk_name[1], strlen(input->unk_name[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->unk_name[2], strlen(input->unk_name[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->unk_name[3], strlen(input->unk_name[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->unk_name[4], strlen(input->unk_name[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->unk_name[5], strlen(input->unk_name[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->unk_name[6], strlen(input->unk_name[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->unk_name[7], strlen(input->unk_name[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->unk_name[8], strlen(input->unk_name[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->unk_name[9], strlen(input->unk_name[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->unk_name[10], strlen(input->unk_name[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->unk_name[11], strlen(input->unk_name[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->unk_name[12], strlen(input->unk_name[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->unk_name[13], strlen(input->unk_name[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->unk_name[14], strlen(input->unk_name[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->unk_name[15], strlen(input->unk_name[15])));
    output->Add(input->race);
    output->Add(input->gender);
    output->Add(input->hair_id);
}
void DurabilityQuality_Output(const DurabilityQualityEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->Id);
    output->Add(input->quality_mod);
}
void AreaTable_Output(const AreaTableEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->mapid);
    output->Add(input->zone);
    output->Add(input->exploreFlag);
    output->Add(input->flags);
    output->Add(input->area_level);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->area_name[0], strlen(input->area_name[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->area_name[1], strlen(input->area_name[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->area_name[2], strlen(input->area_name[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->area_name[3], strlen(input->area_name[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->area_name[4], strlen(input->area_name[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->area_name[5], strlen(input->area_name[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->area_name[6], strlen(input->area_name[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->area_name[7], strlen(input->area_name[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->area_name[8], strlen(input->area_name[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->area_name[9], strlen(input->area_name[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->area_name[10], strlen(input->area_name[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->area_name[11], strlen(input->area_name[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->area_name[12], strlen(input->area_name[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->area_name[13], strlen(input->area_name[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->area_name[14], strlen(input->area_name[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->area_name[15], strlen(input->area_name[15])));
    output->Add(input->team);
}
void Spell_Output(const SpellEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->Id);
    output->Add(input->Category);
    output->Add(input->Dispel);
    output->Add(input->Mechanic);
    output->Add(input->Attributes);
    output->Add(input->AttributesEx);
    output->Add(input->AttributesEx2);
    output->Add(input->AttributesEx3);
    output->Add(input->AttributesEx4);
    output->Add(input->AttributesEx5);
    output->Add(input->AttributesEx6);
    output->Add(input->Stances);
    output->Add(input->StancesNot);
    output->Add(input->Targets);
    output->Add(input->TargetCreatureType);
    output->Add(input->RequiresSpellFocus);
    output->Add(input->FacingCasterFlags);
    output->Add(input->CasterAuraState);
    output->Add(input->TargetAuraState);
    output->Add(input->CasterAuraStateNot);
    output->Add(input->TargetAuraStateNot);
    output->Add(input->casterAuraSpell);
    output->Add(input->targetAuraSpell);
    output->Add(input->excludeCasterAuraSpell);
    output->Add(input->excludeTargetAuraSpell);
    output->Add(input->CastingTimeIndex);
    output->Add(input->RecoveryTime);
    output->Add(input->CategoryRecoveryTime);
    output->Add(input->InterruptFlags);
    output->Add(input->AuraInterruptFlags);
    output->Add(input->ChannelInterruptFlags);
    output->Add(input->procFlags);
    output->Add(input->procChance);
    output->Add(input->procCharges);
    output->Add(input->maxLevel);
    output->Add(input->baseLevel);
    output->Add(input->spellLevel);
    output->Add(input->DurationIndex);
    output->Add(input->powerType);
    output->Add(input->manaCost);
    output->Add(input->manaCostPerlevel);
    output->Add(input->manaPerSecond);
    output->Add(input->manaPerSecondPerLevel);
    output->Add(input->rangeIndex);
    output->Add(input->speed);
    output->Add(input->StackAmount);
    output->Add(input->Totem[0]);
    output->Add(input->Totem[1]);
    output->Add(input->Reagent[0]);
    output->Add(input->Reagent[1]);
    output->Add(input->Reagent[2]);
    output->Add(input->Reagent[3]);
    output->Add(input->Reagent[4]);
    output->Add(input->Reagent[5]);
    output->Add(input->Reagent[6]);
    output->Add(input->Reagent[7]);
    output->Add(input->ReagentCount[0]);
    output->Add(input->ReagentCount[1]);
    output->Add(input->ReagentCount[2]);
    output->Add(input->ReagentCount[3]);
    output->Add(input->ReagentCount[4]);
    output->Add(input->ReagentCount[5]);
    output->Add(input->ReagentCount[6]);
    output->Add(input->ReagentCount[7]);
    output->Add(input->EquippedItemClass);
    output->Add(input->EquippedItemSubClassMask);
    output->Add(input->EquippedItemInventoryTypeMask);
    output->Add(input->Effect[0]);
    output->Add(input->Effect[1]);
    output->Add(input->Effect[2]);
    output->Add(input->EffectDieSides[0]);
    output->Add(input->EffectDieSides[1]);
    output->Add(input->EffectDieSides[2]);
    output->Add(input->EffectRealPointsPerLevel[0]);
    output->Add(input->EffectRealPointsPerLevel[1]);
    output->Add(input->EffectRealPointsPerLevel[2]);
    output->Add(input->EffectBasePoints[0]);
    output->Add(input->EffectBasePoints[1]);
    output->Add(input->EffectBasePoints[2]);
    output->Add(input->EffectMechanic[0]);
    output->Add(input->EffectMechanic[1]);
    output->Add(input->EffectMechanic[2]);
    output->Add(input->EffectImplicitTargetA[0]);
    output->Add(input->EffectImplicitTargetA[1]);
    output->Add(input->EffectImplicitTargetA[2]);
    output->Add(input->EffectImplicitTargetB[0]);
    output->Add(input->EffectImplicitTargetB[1]);
    output->Add(input->EffectImplicitTargetB[2]);
    output->Add(input->EffectRadiusIndex[0]);
    output->Add(input->EffectRadiusIndex[1]);
    output->Add(input->EffectRadiusIndex[2]);
    output->Add(input->EffectApplyAuraName[0]);
    output->Add(input->EffectApplyAuraName[1]);
    output->Add(input->EffectApplyAuraName[2]);
    output->Add(input->EffectAmplitude[0]);
    output->Add(input->EffectAmplitude[1]);
    output->Add(input->EffectAmplitude[2]);
    output->Add(input->EffectMultipleValue[0]);
    output->Add(input->EffectMultipleValue[1]);
    output->Add(input->EffectMultipleValue[2]);
    output->Add(input->EffectChainTarget[0]);
    output->Add(input->EffectChainTarget[1]);
    output->Add(input->EffectChainTarget[2]);
    output->Add(input->EffectItemType[0]);
    output->Add(input->EffectItemType[1]);
    output->Add(input->EffectItemType[2]);
    output->Add(input->EffectMiscValue[0]);
    output->Add(input->EffectMiscValue[1]);
    output->Add(input->EffectMiscValue[2]);
    output->Add(input->EffectMiscValueB[0]);
    output->Add(input->EffectMiscValueB[1]);
    output->Add(input->EffectMiscValueB[2]);
    output->Add(input->EffectTriggerSpell[0]);
    output->Add(input->EffectTriggerSpell[1]);
    output->Add(input->EffectTriggerSpell[2]);
    output->Add(input->EffectPointsPerComboPoint[0]);
    output->Add(input->EffectPointsPerComboPoint[1]);
    output->Add(input->EffectPointsPerComboPoint[2]);
    output->Add(input->EffectSpellClassMaskA[0]);
    output->Add(input->EffectSpellClassMaskA[1]);
    output->Add(input->EffectSpellClassMaskA[2]);
    output->Add(input->EffectSpellClassMaskB[0]);
    output->Add(input->EffectSpellClassMaskB[1]);
    output->Add(input->EffectSpellClassMaskB[2]);
    output->Add(input->EffectSpellClassMaskC[0]);
    output->Add(input->EffectSpellClassMaskC[1]);
    output->Add(input->EffectSpellClassMaskC[2]);
    output->Add(input->SpellVisual[0]);
    output->Add(input->SpellVisual[1]);
    output->Add(input->SpellIconID);
    output->Add(input->activeIconID);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->SpellName[0], strlen(input->SpellName[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->SpellName[1], strlen(input->SpellName[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->SpellName[2], strlen(input->SpellName[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->SpellName[3], strlen(input->SpellName[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->SpellName[4], strlen(input->SpellName[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->SpellName[5], strlen(input->SpellName[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->SpellName[6], strlen(input->SpellName[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->SpellName[7], strlen(input->SpellName[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->SpellName[8], strlen(input->SpellName[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->SpellName[9], strlen(input->SpellName[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->SpellName[10], strlen(input->SpellName[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->SpellName[11], strlen(input->SpellName[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->SpellName[12], strlen(input->SpellName[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->SpellName[13], strlen(input->SpellName[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->SpellName[14], strlen(input->SpellName[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->SpellName[15], strlen(input->SpellName[15])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Rank[0], strlen(input->Rank[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Rank[1], strlen(input->Rank[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Rank[2], strlen(input->Rank[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Rank[3], strlen(input->Rank[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Rank[4], strlen(input->Rank[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Rank[5], strlen(input->Rank[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Rank[6], strlen(input->Rank[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Rank[7], strlen(input->Rank[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Rank[8], strlen(input->Rank[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Rank[9], strlen(input->Rank[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Rank[10], strlen(input->Rank[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Rank[11], strlen(input->Rank[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Rank[12], strlen(input->Rank[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Rank[13], strlen(input->Rank[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Rank[14], strlen(input->Rank[14])));
	output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Rank[15], strlen(input->Rank[15])));
	output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Description[0], strlen(input->Description[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Description[1], strlen(input->Description[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Description[2], strlen(input->Description[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Description[3], strlen(input->Description[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Description[4], strlen(input->Description[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Description[5], strlen(input->Description[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Description[6], strlen(input->Description[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Description[7], strlen(input->Description[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Description[8], strlen(input->Description[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Description[9], strlen(input->Description[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Description[10], strlen(input->Description[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Description[11], strlen(input->Description[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Description[12], strlen(input->Description[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Description[13], strlen(input->Description[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Description[14], strlen(input->Description[14])));
	output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Description[15], strlen(input->Description[15])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->ToolTip[0], strlen(input->ToolTip[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->ToolTip[1], strlen(input->ToolTip[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->ToolTip[2], strlen(input->ToolTip[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->ToolTip[3], strlen(input->ToolTip[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->ToolTip[4], strlen(input->ToolTip[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->ToolTip[5], strlen(input->ToolTip[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->ToolTip[6], strlen(input->ToolTip[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->ToolTip[7], strlen(input->ToolTip[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->ToolTip[8], strlen(input->ToolTip[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->ToolTip[9], strlen(input->ToolTip[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->ToolTip[10], strlen(input->ToolTip[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->ToolTip[11], strlen(input->ToolTip[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->ToolTip[12], strlen(input->ToolTip[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->ToolTip[13], strlen(input->ToolTip[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->ToolTip[14], strlen(input->ToolTip[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->ToolTip[15], strlen(input->ToolTip[15])));
    output->Add(input->ManaCostPercentage);
    output->Add(input->StartRecoveryCategory);
    output->Add(input->StartRecoveryTime);
    output->Add(input->MaxTargetLevel);
    output->Add(input->SpellFamilyName);
    output->Add(input->SpellFamilyFlags);
    output->Add(input->SpellFamilyFlags2);
    output->Add(input->MaxAffectedTargets);
    output->Add(input->DmgClass);
    output->Add(input->PreventionType);
    output->Add(input->DmgMultiplier[0]);
    output->Add(input->DmgMultiplier[1]);
    output->Add(input->DmgMultiplier[2]);
    output->Add(input->TotemCategory[0]);
    output->Add(input->TotemCategory[1]);
    output->Add(input->AreaGroupId);
    output->Add(input->SchoolMask);
	output->Add(input->runeCostID);
	output->Add(input->SpellDifficultyId);
}
void ItemDisplayInfo_Output(const ItemDisplayInfoEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
}
void ItemBagFamily_Output(const ItemBagFamilyEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
}
void GtCombatRatings_Output(const GtCombatRatingsEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ratio);
}
void EmotesText_Output(const EmotesTextEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->Id);
    output->Add(input->textid);
}
void Talent_Output(const TalentEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->TalentID);
    output->Add(input->TalentTab);
    output->Add(input->Row);
    output->Add(input->Col);
    output->Add(input->RankID[0]);
    output->Add(input->RankID[1]);
    output->Add(input->RankID[2]);
    output->Add(input->RankID[3]);
    output->Add(input->RankID[4]);
    output->Add(input->DependsOn);
    output->Add(input->DependsOnRank);
}
void CurrencyTypes_Output(const CurrencyTypesEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ItemId);
    output->Add(input->BitIndex);
}
void ItemSet_Output(const ItemSetEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[0], strlen(input->name[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[1], strlen(input->name[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[2], strlen(input->name[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[3], strlen(input->name[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[4], strlen(input->name[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[5], strlen(input->name[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[6], strlen(input->name[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[7], strlen(input->name[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[8], strlen(input->name[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[9], strlen(input->name[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[10], strlen(input->name[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[11], strlen(input->name[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[12], strlen(input->name[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[13], strlen(input->name[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[14], strlen(input->name[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[15], strlen(input->name[15])));
    output->Add(input->spells[0]);
    output->Add(input->spells[1]);
    output->Add(input->spells[2]);
    output->Add(input->spells[3]);
    output->Add(input->spells[4]);
    output->Add(input->spells[5]);
    output->Add(input->spells[6]);
    output->Add(input->spells[7]);
    output->Add(input->items_to_triggerspell[0]);
    output->Add(input->items_to_triggerspell[1]);
    output->Add(input->items_to_triggerspell[2]);
    output->Add(input->items_to_triggerspell[3]);
    output->Add(input->items_to_triggerspell[4]);
    output->Add(input->items_to_triggerspell[5]);
    output->Add(input->items_to_triggerspell[6]);
    output->Add(input->items_to_triggerspell[7]);
    output->Add(input->required_skill_id);
    output->Add(input->required_skill_value);
}
void PvPDifficulty_Output(const PvPDifficultyEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->mapId);
    output->Add(input->bracketId);
    output->Add(input->minLevel);
    output->Add(input->maxLevel);
    output->Add(input->difficulty);
}
void CreatureType_Output(const CreatureTypeEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
}
void GtRegenMPPerSpt_Output(const GtRegenMPPerSptEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ratio);
}
void GtRegenHPPerSpt_Output(const GtRegenHPPerSptEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ratio);
}
void CinematicSequences_Output(const CinematicSequencesEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->Id);
}
void QuestSort_Output(const QuestSortEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->id);
}
void WorldMapArea_Output(const WorldMapAreaEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->map_id);
    output->Add(input->area_id);
    output->Add(input->y1);
    output->Add(input->y2);
    output->Add(input->x1);
    output->Add(input->x2);
    output->Add(input->virtual_map_id);
}
void ItemRandomSuffix_Output(const ItemRandomSuffixEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[0], strlen(input->nameSuffix[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[1], strlen(input->nameSuffix[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[2], strlen(input->nameSuffix[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[3], strlen(input->nameSuffix[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[4], strlen(input->nameSuffix[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[5], strlen(input->nameSuffix[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[6], strlen(input->nameSuffix[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[7], strlen(input->nameSuffix[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[8], strlen(input->nameSuffix[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[9], strlen(input->nameSuffix[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[10], strlen(input->nameSuffix[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[11], strlen(input->nameSuffix[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[12], strlen(input->nameSuffix[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[13], strlen(input->nameSuffix[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[14], strlen(input->nameSuffix[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[15], strlen(input->nameSuffix[15])));
    output->Add(input->enchant_id[0]);
    output->Add(input->enchant_id[1]);
    output->Add(input->enchant_id[2]);
    output->Add(input->enchant_id[3]);
    output->Add(input->enchant_id[4]);
    output->Add(input->prefix[0]);
    output->Add(input->prefix[1]);
    output->Add(input->prefix[2]);
    output->Add(input->prefix[3]);
    output->Add(input->prefix[4]);
}
void GlyphSlot_Output(const GlyphSlotEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->Id);
    output->Add(input->TypeFlags);
    output->Add(input->Order);
}
void Movie_Output(const MovieEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->Id);
}
void StableSlotPrices_Output(const StableSlotPricesEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->Slot);
    output->Add(input->Price);
}
void ScalingStatDistribution_Output(const ScalingStatDistributionEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->Id);
    output->Add(input->StatMod[0]);
    output->Add(input->StatMod[1]);
    output->Add(input->StatMod[2]);
    output->Add(input->StatMod[3]);
    output->Add(input->StatMod[4]);
    output->Add(input->StatMod[5]);
    output->Add(input->StatMod[6]);
    output->Add(input->StatMod[7]);
    output->Add(input->StatMod[8]);
    output->Add(input->StatMod[9]);
    output->Add(input->Modifier[0]);
    output->Add(input->Modifier[1]);
    output->Add(input->Modifier[2]);
    output->Add(input->Modifier[3]);
    output->Add(input->Modifier[4]);
    output->Add(input->Modifier[5]);
    output->Add(input->Modifier[6]);
    output->Add(input->Modifier[7]);
    output->Add(input->Modifier[8]);
    output->Add(input->Modifier[9]);
    output->Add(input->MaxLevel);
}
void DurabilityCosts_Output(const DurabilityCostsEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->Itemlvl);
    output->Add(input->multiplier[0]);
    output->Add(input->multiplier[1]);
    output->Add(input->multiplier[2]);
    output->Add(input->multiplier[3]);
    output->Add(input->multiplier[4]);
    output->Add(input->multiplier[5]);
    output->Add(input->multiplier[6]);
    output->Add(input->multiplier[7]);
    output->Add(input->multiplier[8]);
    output->Add(input->multiplier[9]);
    output->Add(input->multiplier[10]);
    output->Add(input->multiplier[11]);
    output->Add(input->multiplier[12]);
    output->Add(input->multiplier[13]);
    output->Add(input->multiplier[14]);
    output->Add(input->multiplier[15]);
    output->Add(input->multiplier[16]);
    output->Add(input->multiplier[17]);
    output->Add(input->multiplier[18]);
    output->Add(input->multiplier[19]);
    output->Add(input->multiplier[20]);
    output->Add(input->multiplier[21]);
    output->Add(input->multiplier[22]);
    output->Add(input->multiplier[23]);
    output->Add(input->multiplier[24]);
    output->Add(input->multiplier[25]);
    output->Add(input->multiplier[26]);
    output->Add(input->multiplier[27]);
    output->Add(input->multiplier[28]);
}
void ItemRandomProperties_Output(const ItemRandomPropertiesEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->enchant_id[0]);
    output->Add(input->enchant_id[1]);
    output->Add(input->enchant_id[2]);
    output->Add(input->enchant_id[3]);
    output->Add(input->enchant_id[4]);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[0], strlen(input->nameSuffix[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[1], strlen(input->nameSuffix[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[2], strlen(input->nameSuffix[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[3], strlen(input->nameSuffix[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[4], strlen(input->nameSuffix[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[5], strlen(input->nameSuffix[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[6], strlen(input->nameSuffix[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[7], strlen(input->nameSuffix[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[8], strlen(input->nameSuffix[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[9], strlen(input->nameSuffix[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[10], strlen(input->nameSuffix[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[11], strlen(input->nameSuffix[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[12], strlen(input->nameSuffix[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[13], strlen(input->nameSuffix[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[14], strlen(input->nameSuffix[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->nameSuffix[15], strlen(input->nameSuffix[15])));
}
void AreaTrigger_Output(const AreaTriggerEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->id);
    output->Add(input->mapid);
    output->Add(input->x);
    output->Add(input->y);
    output->Add(input->z);
    output->Add(input->radius);
    output->Add(input->box_x);
    output->Add(input->box_y);
    output->Add(input->box_z);
    output->Add(input->box_orientation);
}
void Map_Output(const MapEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->MapID);
    output->Add(input->map_type);
    output->Add(FormatStr("(%d)%s_Instanceable(%d)_IsMountAllowed(%d)_IsContinent(%d)", input->map_type, GetMapTypesName(input->map_type), input->Instanceable(),
        input->IsMountAllowed(), input->IsContinent()));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[0], strlen(input->name[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[1], strlen(input->name[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[2], strlen(input->name[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[3], strlen(input->name[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[4], strlen(input->name[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[5], strlen(input->name[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[6], strlen(input->name[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[7], strlen(input->name[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[8], strlen(input->name[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[9], strlen(input->name[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[10], strlen(input->name[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[11], strlen(input->name[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[12], strlen(input->name[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[13], strlen(input->name[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[14], strlen(input->name[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[15], strlen(input->name[15])));
	output->Add(input->linked_zone);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->hordeIntro[0], strlen(input->hordeIntro[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->hordeIntro[1], strlen(input->hordeIntro[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->hordeIntro[2], strlen(input->hordeIntro[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->hordeIntro[3], strlen(input->hordeIntro[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->hordeIntro[4], strlen(input->hordeIntro[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->hordeIntro[5], strlen(input->hordeIntro[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->hordeIntro[6], strlen(input->hordeIntro[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->hordeIntro[7], strlen(input->hordeIntro[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->hordeIntro[8], strlen(input->hordeIntro[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->hordeIntro[9], strlen(input->hordeIntro[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->hordeIntro[10], strlen(input->hordeIntro[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->hordeIntro[11], strlen(input->hordeIntro[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->hordeIntro[12], strlen(input->hordeIntro[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->hordeIntro[13], strlen(input->hordeIntro[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->hordeIntro[14], strlen(input->hordeIntro[14])));
	output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->hordeIntro[15], strlen(input->hordeIntro[15])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->allianceIntro[0], strlen(input->allianceIntro[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->allianceIntro[1], strlen(input->allianceIntro[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->allianceIntro[2], strlen(input->allianceIntro[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->allianceIntro[3], strlen(input->allianceIntro[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->allianceIntro[4], strlen(input->allianceIntro[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->allianceIntro[5], strlen(input->allianceIntro[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->allianceIntro[6], strlen(input->allianceIntro[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->allianceIntro[7], strlen(input->allianceIntro[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->allianceIntro[8], strlen(input->allianceIntro[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->allianceIntro[9], strlen(input->allianceIntro[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->allianceIntro[10], strlen(input->allianceIntro[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->allianceIntro[11], strlen(input->allianceIntro[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->allianceIntro[12], strlen(input->allianceIntro[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->allianceIntro[13], strlen(input->allianceIntro[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->allianceIntro[14], strlen(input->allianceIntro[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->allianceIntro[15], strlen(input->allianceIntro[15])));
    output->Add(input->multimap_id);
	output->Add(input->ghost_entrance_map);
	output->Add(input->ghost_entrance_x);
    output->Add(input->ghost_entrance_y);
    output->Add(input->addon);
}
void RandomPropertiesPoints_Output(const RandomPropertiesPointsEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->itemLevel);
    output->Add(input->EpicPropertiesPoints[0]);
    output->Add(input->EpicPropertiesPoints[1]);
    output->Add(input->EpicPropertiesPoints[2]);
    output->Add(input->EpicPropertiesPoints[3]);
    output->Add(input->EpicPropertiesPoints[4]);
    output->Add(input->RarePropertiesPoints[0]);
    output->Add(input->RarePropertiesPoints[1]);
    output->Add(input->RarePropertiesPoints[2]);
    output->Add(input->RarePropertiesPoints[3]);
    output->Add(input->RarePropertiesPoints[4]);
    output->Add(input->UncommonPropertiesPoints[0]);
    output->Add(input->UncommonPropertiesPoints[1]);
    output->Add(input->UncommonPropertiesPoints[2]);
    output->Add(input->UncommonPropertiesPoints[3]);
    output->Add(input->UncommonPropertiesPoints[4]);
}
void CharTitles_Output(const CharTitlesEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[0], strlen(input->name[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[1], strlen(input->name[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[2], strlen(input->name[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[3], strlen(input->name[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[4], strlen(input->name[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[5], strlen(input->name[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[6], strlen(input->name[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[7], strlen(input->name[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[8], strlen(input->name[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[9], strlen(input->name[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[10], strlen(input->name[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[11], strlen(input->name[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[12], strlen(input->name[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[13], strlen(input->name[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[14], strlen(input->name[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[15], strlen(input->name[15])));
    output->Add(input->bit_index);
}
void CreatureDisplayInfo_Output(const CreatureDisplayInfoEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->Displayid);
    output->Add(input->scale);
}
void CreatureFamily_Output(const CreatureFamilyEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->minScale);
    output->Add(input->minScaleLevel);
    output->Add(input->maxScale);
    output->Add(input->maxScaleLevel);
    output->Add(input->skillLine[0]);
    output->Add(input->skillLine[1]);
    output->Add(input->petFoodMask);
    output->Add(input->petTalentType);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Name[0], strlen(input->Name[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Name[1], strlen(input->Name[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Name[2], strlen(input->Name[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Name[3], strlen(input->Name[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Name[4], strlen(input->Name[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Name[5], strlen(input->Name[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Name[6], strlen(input->Name[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Name[7], strlen(input->Name[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Name[8], strlen(input->Name[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Name[9], strlen(input->Name[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Name[10], strlen(input->Name[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Name[11], strlen(input->Name[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Name[12], strlen(input->Name[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Name[13], strlen(input->Name[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Name[14], strlen(input->Name[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->Name[15], strlen(input->Name[15])));
}
void Achievement_Output(const AchievementEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->factionFlag);
    output->Add(input->mapID);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[0], strlen(input->name[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[1], strlen(input->name[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[2], strlen(input->name[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[3], strlen(input->name[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[4], strlen(input->name[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[5], strlen(input->name[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[6], strlen(input->name[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[7], strlen(input->name[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[8], strlen(input->name[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[9], strlen(input->name[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[10], strlen(input->name[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[11], strlen(input->name[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[12], strlen(input->name[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[13], strlen(input->name[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[14], strlen(input->name[14])));
	output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->name[15], strlen(input->name[15])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[0], strlen(input->description[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[1], strlen(input->description[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[2], strlen(input->description[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[3], strlen(input->description[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[4], strlen(input->description[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[5], strlen(input->description[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[6], strlen(input->description[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[7], strlen(input->description[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[8], strlen(input->description[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[9], strlen(input->description[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[10], strlen(input->description[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[11], strlen(input->description[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[12], strlen(input->description[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[13], strlen(input->description[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[14], strlen(input->description[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->description[15], strlen(input->description[15])));
    output->Add(input->categoryId);
    output->Add(input->points);
	output->Add(input->flags);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->titleReward[0], strlen(input->titleReward[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->titleReward[1], strlen(input->titleReward[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->titleReward[2], strlen(input->titleReward[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->titleReward[3], strlen(input->titleReward[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->titleReward[4], strlen(input->titleReward[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->titleReward[5], strlen(input->titleReward[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->titleReward[6], strlen(input->titleReward[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->titleReward[7], strlen(input->titleReward[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->titleReward[8], strlen(input->titleReward[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->titleReward[9], strlen(input->titleReward[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->titleReward[10], strlen(input->titleReward[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->titleReward[11], strlen(input->titleReward[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->titleReward[12], strlen(input->titleReward[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->titleReward[13], strlen(input->titleReward[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->titleReward[14], strlen(input->titleReward[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->titleReward[15], strlen(input->titleReward[15])));
    output->Add(input->count);
    output->Add(input->refAchievement);
}
void SpellFocusObject_Output(const SpellFocusObjectEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
}
void SpellRadius_Output(const SpellRadiusEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->Radius);
    output->Add(input->Radius2);
}
void ChatChannels_Output(const ChatChannelsEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ChannelID);
    output->Add(input->flags);
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->pattern[0], strlen(input->pattern[0])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->pattern[1], strlen(input->pattern[1])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->pattern[2], strlen(input->pattern[2])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->pattern[3], strlen(input->pattern[3])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->pattern[4], strlen(input->pattern[4])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->pattern[5], strlen(input->pattern[5])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->pattern[6], strlen(input->pattern[6])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->pattern[7], strlen(input->pattern[7])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->pattern[8], strlen(input->pattern[8])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->pattern[9], strlen(input->pattern[9])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->pattern[10], strlen(input->pattern[10])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->pattern[11], strlen(input->pattern[11])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->pattern[12], strlen(input->pattern[12])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->pattern[13], strlen(input->pattern[13])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->pattern[14], strlen(input->pattern[14])));
    output->Add(AnsiUTF8BIGDataToUnicodeGBNoEnterCharacter(input->pattern[15], strlen(input->pattern[15])));
}
void SkillLineAbility_Output(const SkillLineAbilityEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->id);
    output->Add(input->skillId);
    output->Add(input->spellId);
    output->Add(input->racemask);
    output->Add(input->classmask);
    output->Add(input->req_skill_value);
    output->Add(input->forward_spellid);
    output->Add(input->learnOnGetSkill);
    output->Add(input->max_value);
    output->Add(input->min_value);
}
void CharStartOutfit_Output(const CharStartOutfitEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->RaceClassGender);
    output->Add(input->ItemId[0]);
    output->Add(input->ItemId[1]);
    output->Add(input->ItemId[2]);
    output->Add(input->ItemId[3]);
    output->Add(input->ItemId[4]);
    output->Add(input->ItemId[5]);
    output->Add(input->ItemId[6]);
    output->Add(input->ItemId[7]);
    output->Add(input->ItemId[8]);
    output->Add(input->ItemId[9]);
    output->Add(input->ItemId[10]);
    output->Add(input->ItemId[11]);
    output->Add(input->ItemId[12]);
    output->Add(input->ItemId[13]);
    output->Add(input->ItemId[14]);
    output->Add(input->ItemId[15]);
    output->Add(input->ItemId[16]);
    output->Add(input->ItemId[17]);
    output->Add(input->ItemId[18]);
    output->Add(input->ItemId[19]);
    output->Add(input->ItemId[20]);
    output->Add(input->ItemId[21]);
    output->Add(input->ItemId[22]);
    output->Add(input->ItemId[23]);
}
void AchievementCategory_Output(const AchievementCategoryEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->parentCategory);
}
void Lock_Output(const LockEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->Type[0]);
    output->Add(input->Type[1]);
    output->Add(input->Type[2]);
    output->Add(input->Type[3]);
    output->Add(input->Type[4]);
    output->Add(input->Type[5]);
    output->Add(input->Type[6]);
    output->Add(input->Type[7]);
    output->Add(input->Index[0]);
    output->Add(input->Index[1]);
    output->Add(input->Index[2]);
    output->Add(input->Index[3]);
    output->Add(input->Index[4]);
    output->Add(input->Index[5]);
    output->Add(input->Index[6]);
    output->Add(input->Index[7]);
    output->Add(input->Skill[0]);
    output->Add(input->Skill[1]);
    output->Add(input->Skill[2]);
    output->Add(input->Skill[3]);
    output->Add(input->Skill[4]);
    output->Add(input->Skill[5]);
    output->Add(input->Skill[6]);
    output->Add(input->Skill[7]);
}
void GtChanceToSpellCrit_Output(const GtChanceToSpellCritEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ratio);
}
void SpellItemEnchantmentCondition_Output(const SpellItemEnchantmentConditionEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->Color[0]);
    output->Add(input->Color[1]);
    output->Add(input->Color[2]);
    output->Add(input->Color[3]);
    output->Add(input->Color[4]);
    output->Add(input->Comparator[0]);
    output->Add(input->Comparator[1]);
    output->Add(input->Comparator[2]);
    output->Add(input->Comparator[3]);
    output->Add(input->Comparator[4]);
    output->Add(input->CompareColor[0]);
    output->Add(input->CompareColor[1]);
    output->Add(input->CompareColor[2]);
    output->Add(input->CompareColor[3]);
    output->Add(input->CompareColor[4]);
    output->Add(input->Value[0]);
    output->Add(input->Value[1]);
    output->Add(input->Value[2]);
    output->Add(input->Value[3]);
    output->Add(input->Value[4]);
}
void SummonProperties_Output(const SummonPropertiesEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->Id);
    output->Add(input->Group);
    output->Add(input->FactionId);
    output->Add(input->Type);
    output->Add(input->Slot);
    output->Add(input->Flags);
}
void SpellCastTimes_Output(const SpellCastTimesEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
    output->Add(input->CastTime);
}
void SpellDifficulty_Output(const SpellDifficultyEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->ID);
	output->Add(input->spellId[0]);
	output->Add(input->spellId[1]);
	output->Add(input->spellId[2]);
	output->Add(input->spellId[3]);
}
void GtBarberShopCostBase_Output(const GtBarberShopCostBaseEntry *input, TStrings *output)
{
    if(!input) return;
    output->Add(input->cost);
}
//======================================================================================


void    GetTableColumns(String tableName, TStrings * output)
{
    output->Clear();
    for(DWORD i=0; i<gTableColumns[tableName].Columns.size(); i++)
    {
        output->Add(gTableColumns[tableName].Columns[i]);
    }
}

void    GetTableColumnNames(TStrings * output)
{
    output->Clear();
    for(map<String, tagDBCTableContent >::iterator it = gTableColumns.begin(); it != gTableColumns.end(); it++)
    {
        output->Add(it->first);
    }
}

int     GetStoresCountByName(String tableName)
{
    if(tableName == "TaxiPath")
        return GetTaxiPathStore()->GetRecordCount();
    if(tableName == "SkillLineAbility")
        return GetSkillLineAbilityStore()->GetRecordCount();
    if(tableName == "ItemRandomSuffix")
        return GetItemRandomSuffixStore()->GetRecordCount();
    if(tableName == "QuestXPLevel")
        return GetQuestXPLevelStore()->GetRecordCount();
    if(tableName == "TotemCategory")
        return GetTotemCategoryStore()->GetRecordCount();
    if(tableName == "GlyphSlot")
        return GetGlyphSlotStore()->GetRecordCount();
    if(tableName == "QuestSort")
        return GetQuestSortStore()->GetRecordCount();
    if(tableName == "Movie")
        return GetMovieStore()->GetRecordCount();
    if(tableName == "RandomPropertiesPoints")
        return GetRandomPropertiesPointsStore()->GetRecordCount();
    if(tableName == "ScalingStatDistribution")
        return GetScalingStatDistributionStore()->GetRecordCount();
    if(tableName == "ScalingStatValues")
        return GetScalingStatValuesStore()->GetRecordCount();
    if(tableName == "WorldSafeLocs")
        return GetWorldSafeLocsStore()->GetRecordCount();
    if(tableName == "WorldMapOverlay")
        return GetWorldMapOverlayStore()->GetRecordCount();
    if(tableName == "DurabilityCosts")
        return GetDurabilityCostsStore()->GetRecordCount();
    if(tableName == "ItemRandomProperties")
        return GetItemRandomPropertiesStore()->GetRecordCount();
    if(tableName == "GtOCTRegenHP")
        return GetGtOCTRegenHPStore()->GetRecordCount();
    if(tableName == "TalentTab")
        return GetTalentTabStore()->GetRecordCount();
    if(tableName == "SpellItemEnchantment")
        return GetSpellItemEnchantmentStore()->GetRecordCount();
    if(tableName == "TaxiPathNode")
        return GetTaxiPathNodeStore()->GetRecordCount();
    if(tableName == "ChrClasses")
        return GetChrClassesStore()->GetRecordCount();
    if(tableName == "BarberShopStyle")
        return GetBarberShopStyleStore()->GetRecordCount();
    if(tableName == "MailTemplate")
        return GetMailTemplateStore()->GetRecordCount();
    if(tableName == "Spell")
        return GetSpellStore()->GetRecordCount();
    if(tableName == "AreaTrigger")
        return GetAreaTriggerStore()->GetRecordCount();
    if(tableName == "Map")
        return GetMapStore()->GetRecordCount();
    if(tableName == "ChrRaces")
        return GetChrRacesStore()->GetRecordCount();
    if(tableName == "Faction")
        return GetFactionStore()->GetRecordCount();
    if(tableName == "AreaTable")
        return GetAreaTableStore()->GetRecordCount();
    if(tableName == "ItemLimitCategory")
        return GetItemLimitCategoryStore()->GetRecordCount();
    if(tableName == "AuctionHouse")
        return GetAuctionHouseStore()->GetRecordCount();
    if(tableName == "SpellRadius")
        return GetSpellRadiusStore()->GetRecordCount();
    if(tableName == "Holidays")
        return GetHolidaysStore()->GetRecordCount();
    if(tableName == "ItemBagFamily")
        return GetItemBagFamilyStore()->GetRecordCount();
    if(tableName == "CreatureSpellData")
        return GetCreatureSpellDataStore()->GetRecordCount();
    if(tableName == "CharTitles")
        return GetCharTitlesStore()->GetRecordCount();
    if(tableName == "CreatureDisplayInfo")
        return GetCreatureDisplayInfoStore()->GetRecordCount();
    if(tableName == "AchievementCriteria")
        return GetAchievementCriteriaStore()->GetRecordCount();
    if(tableName == "GtCombatRatings")
        return GetGtCombatRatingsStore()->GetRecordCount();
    if(tableName == "GtChanceToSpellCritBase")
        return GetGtChanceToSpellCritBaseStore()->GetRecordCount();
    if(tableName == "GtChanceToMeleeCritBase")
        return GetGtChanceToMeleeCritBaseStore()->GetRecordCount();
    if(tableName == "EmotesText")
        return GetEmotesTextStore()->GetRecordCount();
    if(tableName == "CreatureFamily")
        return GetCreatureFamilyStore()->GetRecordCount();
    if(tableName == "Achievement")
        return GetAchievementStore()->GetRecordCount();
    if(tableName == "SpellFocusObject")
        return GetSpellFocusObjectStore()->GetRecordCount();
    if(tableName == "SpellShapeshift")
        return GetSpellShapeshiftStore()->GetRecordCount();
    if(tableName == "SoundEntries")
        return GetSoundEntriesStore()->GetRecordCount();
    if(tableName == "Talent")
        return GetTalentStore()->GetRecordCount();
    if(tableName == "CurrencyTypes")
        return GetCurrencyTypesStore()->GetRecordCount();
    if(tableName == "ChatChannels")
        return GetChatChannelsStore()->GetRecordCount();
    if(tableName == "Emotes")
        return GetEmotesStore()->GetRecordCount();
    if(tableName == "ItemSet")
        return GetItemSetStore()->GetRecordCount();
    if(tableName == "Item")
        return GetItemStore()->GetRecordCount();
    if(tableName == "Vehicle")
        return GetVehicleStore()->GetRecordCount();
    if(tableName == "PvPDifficulty")
        return GetPvPDifficultyStore()->GetRecordCount();
    if(tableName == "ItemExtendedCost")
        return GetItemExtendedCostStore()->GetRecordCount();
    if(tableName == "CharStartOutfit")
        return GetCharStartOutfitStore()->GetRecordCount();
    if(tableName == "WorldMapArea")
        return GetWorldMapAreaStore()->GetRecordCount();
    if(tableName == "SpellRange")
        return GetSpellRangeStore()->GetRecordCount();
    if(tableName == "QuestFactionReward")
        return GetQuestFactionRewardStore()->GetRecordCount();
    if(tableName == "SpellRuneCost")
        return GetSpellRuneCostStore()->GetRecordCount();
    if(tableName == "SpellItemEnchantmentCondition")
        return GetSpellItemEnchantmentConditionStore()->GetRecordCount();
    if(tableName == "Lock")
        return GetLockStore()->GetRecordCount();
    if(tableName == "DurabilityQuality")
        return GetDurabilityQualityStore()->GetRecordCount();
    if(tableName == "BattlemasterList")
        return GetBattlemasterListStore()->GetRecordCount();
    if(tableName == "SpellDuration")
        return GetSpellDurationStore()->GetRecordCount();
    if(tableName == "CreatureType")
        return GetCreatureTypeStore()->GetRecordCount();
    if(tableName == "GtRegenMPPerSpt")
        return GetGtRegenMPPerSptStore()->GetRecordCount();
    if(tableName == "GlyphProperties")
        return GetGlyphPropertiesStore()->GetRecordCount();
    if(tableName == "GameObjectDisplayInfo")
        return GetGameObjectDisplayInfoStore()->GetRecordCount();
    if(tableName == "GtRegenHPPerSpt")
        return GetGtRegenHPPerSptStore()->GetRecordCount();
    if(tableName == "CinematicSequences")
        return GetCinematicSequencesStore()->GetRecordCount();
    if(tableName == "GtChanceToSpellCrit")
        return GetGtChanceToSpellCritStore()->GetRecordCount();
    if(tableName == "SkillLine")
        return GetSkillLineStore()->GetRecordCount();
    if(tableName == "GtChanceToMeleeCrit")
        return GetGtChanceToMeleeCritStore()->GetRecordCount();
    if(tableName == "VehicleSeat")
        return GetVehicleSeatStore()->GetRecordCount();
    if(tableName == "FactionTemplate")
        return GetFactionTemplateStore()->GetRecordCount();
    if(tableName == "TaxiNodes")
        return GetTaxiNodesStore()->GetRecordCount();
    if(tableName == "BankBagSlotPrices")
        return GetBankBagSlotPricesStore()->GetRecordCount();
    if(tableName == "MapDifficulty")
        return GetMapDifficultyStore()->GetRecordCount();
    if(tableName == "SummonProperties")
        return GetSummonPropertiesStore()->GetRecordCount();
    if(tableName == "GemProperties")
        return GetGemPropertiesStore()->GetRecordCount();
    if(tableName == "AreaGroup")
        return GetAreaGroupStore()->GetRecordCount();
    if(tableName == "StableSlotPrices")
        return GetStableSlotPricesStore()->GetRecordCount();
    if(tableName == "SpellCastTimes")
		return GetSpellCastTimesStore()->GetRecordCount();
    if(tableName == "SpellDifficulty")
        return GetSpellDifficultyStore()->GetRecordCount();
    if(tableName == "GtBarberShopCostBase")
        return GetGtBarberShopCostBaseStore()->GetRecordCount();
    return  0;
}

void    AddDBCToStringList(String tableName, int index, TStrings * output)
{
    if(tableName == "TaxiPath")
        TaxiPath_Output(GetTaxiPathStore()->LookupByIndex(index), output);
    if(tableName == "SkillLineAbility")
        SkillLineAbility_Output(GetSkillLineAbilityStore()->LookupByIndex(index), output);
    if(tableName == "ItemRandomSuffix")
        ItemRandomSuffix_Output(GetItemRandomSuffixStore()->LookupByIndex(index), output);
    if(tableName == "QuestXPLevel")
        QuestXPLevel_Output(GetQuestXPLevelStore()->LookupByIndex(index), output);
    if(tableName == "TotemCategory")
        TotemCategory_Output(GetTotemCategoryStore()->LookupByIndex(index), output);
    if(tableName == "GlyphSlot")
        GlyphSlot_Output(GetGlyphSlotStore()->LookupByIndex(index), output);
    if(tableName == "QuestSort")
        QuestSort_Output(GetQuestSortStore()->LookupByIndex(index), output);
    if(tableName == "Movie")
        Movie_Output(GetMovieStore()->LookupByIndex(index), output);
    if(tableName == "RandomPropertiesPoints")
        RandomPropertiesPoints_Output(GetRandomPropertiesPointsStore()->LookupByIndex(index), output);
    if(tableName == "ScalingStatDistribution")
        ScalingStatDistribution_Output(GetScalingStatDistributionStore()->LookupByIndex(index), output);
    if(tableName == "ScalingStatValues")
        ScalingStatValues_Output(GetScalingStatValuesStore()->LookupByIndex(index), output);
    if(tableName == "WorldSafeLocs")
        WorldSafeLocs_Output(GetWorldSafeLocsStore()->LookupByIndex(index), output);
    if(tableName == "WorldMapOverlay")
        WorldMapOverlay_Output(GetWorldMapOverlayStore()->LookupByIndex(index), output);
    if(tableName == "DurabilityCosts")
        DurabilityCosts_Output(GetDurabilityCostsStore()->LookupByIndex(index), output);
    if(tableName == "ItemRandomProperties")
        ItemRandomProperties_Output(GetItemRandomPropertiesStore()->LookupByIndex(index), output);
    if(tableName == "GtOCTRegenHP")
        GtOCTRegenHP_Output(GetGtOCTRegenHPStore()->LookupByIndex(index), output);
    if(tableName == "TalentTab")
        TalentTab_Output(GetTalentTabStore()->LookupByIndex(index), output);
    if(tableName == "SpellItemEnchantment")
        SpellItemEnchantment_Output(GetSpellItemEnchantmentStore()->LookupByIndex(index), output);
    if(tableName == "TaxiPathNode")
        TaxiPathNode_Output(GetTaxiPathNodeStore()->LookupByIndex(index), output);
    if(tableName == "ChrClasses")
        ChrClasses_Output(GetChrClassesStore()->LookupByIndex(index), output);
    if(tableName == "BarberShopStyle")
        BarberShopStyle_Output(GetBarberShopStyleStore()->LookupByIndex(index), output);
    if(tableName == "MailTemplate")
        MailTemplate_Output(GetMailTemplateStore()->LookupByIndex(index), output);
    if(tableName == "Spell")
        Spell_Output(GetSpellStore()->LookupByIndex(index), output);
    if(tableName == "AreaTrigger")
        AreaTrigger_Output(GetAreaTriggerStore()->LookupByIndex(index), output);
    if(tableName == "Map")
        Map_Output(GetMapStore()->LookupByIndex(index), output);
    if(tableName == "ChrRaces")
        ChrRaces_Output(GetChrRacesStore()->LookupByIndex(index), output);
    if(tableName == "Faction")
        Faction_Output(GetFactionStore()->LookupByIndex(index), output);
    if(tableName == "AreaTable")
        AreaTable_Output(GetAreaTableStore()->LookupByIndex(index), output);
    if(tableName == "ItemLimitCategory")
        ItemLimitCategory_Output(GetItemLimitCategoryStore()->LookupByIndex(index), output);
    if(tableName == "AuctionHouse")
        AuctionHouse_Output(GetAuctionHouseStore()->LookupByIndex(index), output);
    if(tableName == "SpellRadius")
        SpellRadius_Output(GetSpellRadiusStore()->LookupByIndex(index), output);
    if(tableName == "Holidays")
        Holidays_Output(GetHolidaysStore()->LookupByIndex(index), output);
    if(tableName == "ItemBagFamily")
        ItemBagFamily_Output(GetItemBagFamilyStore()->LookupByIndex(index), output);
    if(tableName == "CreatureSpellData")
        CreatureSpellData_Output(GetCreatureSpellDataStore()->LookupByIndex(index), output);
    if(tableName == "CharTitles")
        CharTitles_Output(GetCharTitlesStore()->LookupByIndex(index), output);
    if(tableName == "CreatureDisplayInfo")
        CreatureDisplayInfo_Output(GetCreatureDisplayInfoStore()->LookupByIndex(index), output);
    if(tableName == "AchievementCriteria")
        AchievementCriteria_Output(GetAchievementCriteriaStore()->LookupByIndex(index), output);
    if(tableName == "GtCombatRatings")
        GtCombatRatings_Output(GetGtCombatRatingsStore()->LookupByIndex(index), output);
    if(tableName == "GtChanceToSpellCritBase")
        GtChanceToSpellCritBase_Output(GetGtChanceToSpellCritBaseStore()->LookupByIndex(index), output);
    if(tableName == "GtChanceToMeleeCritBase")
        GtChanceToMeleeCritBase_Output(GetGtChanceToMeleeCritBaseStore()->LookupByIndex(index), output);
    if(tableName == "EmotesText")
        EmotesText_Output(GetEmotesTextStore()->LookupByIndex(index), output);
    if(tableName == "CreatureFamily")
        CreatureFamily_Output(GetCreatureFamilyStore()->LookupByIndex(index), output);
    if(tableName == "Achievement")
        Achievement_Output(GetAchievementStore()->LookupByIndex(index), output);
    if(tableName == "SpellFocusObject")
        SpellFocusObject_Output(GetSpellFocusObjectStore()->LookupByIndex(index), output);
    if(tableName == "SpellShapeshift")
        SpellShapeshift_Output(GetSpellShapeshiftStore()->LookupByIndex(index), output);
    if(tableName == "SoundEntries")
        SoundEntries_Output(GetSoundEntriesStore()->LookupByIndex(index), output);
    if(tableName == "Talent")
        Talent_Output(GetTalentStore()->LookupByIndex(index), output);
    if(tableName == "CurrencyTypes")
        CurrencyTypes_Output(GetCurrencyTypesStore()->LookupByIndex(index), output);
    if(tableName == "ChatChannels")
        ChatChannels_Output(GetChatChannelsStore()->LookupByIndex(index), output);
    if(tableName == "Emotes")
        Emotes_Output(GetEmotesStore()->LookupByIndex(index), output);
    if(tableName == "ItemSet")
        ItemSet_Output(GetItemSetStore()->LookupByIndex(index), output);
    if(tableName == "Item")
        Item_Output(GetItemStore()->LookupByIndex(index), output);
    if(tableName == "Vehicle")
        Vehicle_Output(GetVehicleStore()->LookupByIndex(index), output);
    if(tableName == "PvPDifficulty")
        PvPDifficulty_Output(GetPvPDifficultyStore()->LookupByIndex(index), output);
    if(tableName == "ItemExtendedCost")
        ItemExtendedCost_Output(GetItemExtendedCostStore()->LookupByIndex(index), output);
    if(tableName == "CharStartOutfit")
        CharStartOutfit_Output(GetCharStartOutfitStore()->LookupByIndex(index), output);
    if(tableName == "WorldMapArea")
        WorldMapArea_Output(GetWorldMapAreaStore()->LookupByIndex(index), output);
    if(tableName == "SpellRange")
        SpellRange_Output(GetSpellRangeStore()->LookupByIndex(index), output);
    if(tableName == "QuestFactionReward")
        QuestFactionReward_Output(GetQuestFactionRewardStore()->LookupByIndex(index), output);
    if(tableName == "SpellRuneCost")
        SpellRuneCost_Output(GetSpellRuneCostStore()->LookupByIndex(index), output);
    if(tableName == "SpellItemEnchantmentCondition")
        SpellItemEnchantmentCondition_Output(GetSpellItemEnchantmentConditionStore()->LookupByIndex(index), output);
    if(tableName == "Lock")
        Lock_Output(GetLockStore()->LookupByIndex(index), output);
    if(tableName == "DurabilityQuality")
        DurabilityQuality_Output(GetDurabilityQualityStore()->LookupByIndex(index), output);
    if(tableName == "BattlemasterList")
        BattlemasterList_Output(GetBattlemasterListStore()->LookupByIndex(index), output);
    if(tableName == "SpellDuration")
        SpellDuration_Output(GetSpellDurationStore()->LookupByIndex(index), output);
    if(tableName == "CreatureType")
        CreatureType_Output(GetCreatureTypeStore()->LookupByIndex(index), output);
    if(tableName == "GtRegenMPPerSpt")
        GtRegenMPPerSpt_Output(GetGtRegenMPPerSptStore()->LookupByIndex(index), output);
    if(tableName == "GlyphProperties")
        GlyphProperties_Output(GetGlyphPropertiesStore()->LookupByIndex(index), output);
    if(tableName == "GameObjectDisplayInfo")
        GameObjectDisplayInfo_Output(GetGameObjectDisplayInfoStore()->LookupByIndex(index), output);
    if(tableName == "GtRegenHPPerSpt")
        GtRegenHPPerSpt_Output(GetGtRegenHPPerSptStore()->LookupByIndex(index), output);
    if(tableName == "CinematicSequences")
        CinematicSequences_Output(GetCinematicSequencesStore()->LookupByIndex(index), output);
    if(tableName == "GtChanceToSpellCrit")
        GtChanceToSpellCrit_Output(GetGtChanceToSpellCritStore()->LookupByIndex(index), output);
    if(tableName == "SkillLine")
        SkillLine_Output(GetSkillLineStore()->LookupByIndex(index), output);
    if(tableName == "GtChanceToMeleeCrit")
        GtChanceToMeleeCrit_Output(GetGtChanceToMeleeCritStore()->LookupByIndex(index), output);
    if(tableName == "VehicleSeat")
        VehicleSeat_Output(GetVehicleSeatStore()->LookupByIndex(index), output);
    if(tableName == "FactionTemplate")
        FactionTemplate_Output(GetFactionTemplateStore()->LookupByIndex(index), output);
    if(tableName == "TaxiNodes")
        TaxiNodes_Output(GetTaxiNodesStore()->LookupByIndex(index), output);
    if(tableName == "BankBagSlotPrices")
        BankBagSlotPrices_Output(GetBankBagSlotPricesStore()->LookupByIndex(index), output);
    if(tableName == "MapDifficulty")
        MapDifficulty_Output(GetMapDifficultyStore()->LookupByIndex(index), output);
    if(tableName == "SummonProperties")
        SummonProperties_Output(GetSummonPropertiesStore()->LookupByIndex(index), output);
    if(tableName == "GemProperties")
        GemProperties_Output(GetGemPropertiesStore()->LookupByIndex(index), output);
    if(tableName == "AreaGroup")
        AreaGroup_Output(GetAreaGroupStore()->LookupByIndex(index), output);
    if(tableName == "StableSlotPrices")
        StableSlotPrices_Output(GetStableSlotPricesStore()->LookupByIndex(index), output);
    if(tableName == "SpellCastTimes")
		SpellCastTimes_Output(GetSpellCastTimesStore()->LookupByIndex(index), output);
    if(tableName == "SpellDifficulty")
        SpellDifficulty_Output(GetSpellDifficultyStore()->LookupByIndex(index), output);
    if(tableName == "GtBarberShopCostBase")
        GtBarberShopCostBase_Output(GetGtBarberShopCostBaseStore()->LookupByIndex(index), output);
}

void    AddDBCToListItem(String tableName, int index, TListItem * curItem)
{
    auto_ptr<TStringList> output(new TStringList);
    AddDBCToStringList(tableName, index, output.get());

    if(output->Count == 0)
        return;
    curItem->Caption = output->Strings[0];
    if(output->Count <= 1)
        return;

//    curItem->SubItems->BeginUpdate();
    for(int i=1; i<output->Count; i++)
    {
        curItem->SubItems->Add(output->Strings[i]);
    }
//    curItem->SubItems->EndUpdate();
}

void    OutputValuesToList(String tableName, TListView * curList, TCGauge *progress)
{
    curList->Items->BeginUpdate();
    curList->Items->Clear();
    curList->Items->EndUpdate();
    curList->Columns->BeginUpdate();
    curList->Columns->Clear();
    curList->Columns->EndUpdate();
    
    curList->Columns->BeginUpdate();
    for(DWORD i=0; i<gTableColumns[tableName].Columns.size(); i++)
    {
        TListColumn * column = curList->Columns->Add();
        column->Caption = gTableColumns[tableName].Columns[i];
        column->Width = 100;
    }
    curList->Columns->EndUpdate();

    curList->Items->BeginUpdate();
    int rowCount = GetStoresCountByName(tableName);
    int split = rowCount / 100;
    if(split == 0)
        split = 1;
    progress->MaxValue = rowCount / split; 
    for(int i=0; i<rowCount; i++)
    {
        TListItem * curItem = curList->Items->Add();
        AddDBCToListItem(tableName, i, curItem);
        if(i%split == 0)
        {
            progress->Progress = i / split;
            Application->ProcessMessages();
        }
    }
    curList->Items->EndUpdate();
    progress->Progress = progress->MaxValue;    
}
