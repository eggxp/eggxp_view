//---------------------------------------------------------------------------

#ifndef DBCStoresH
#define DBCStoresH
//---------------------------------------------------------------------------
#include "DBCStore.h"
#include "DBCStructure.h"
#include "sharedDefine.h"
#include <list>

#define     MANGOS_DLL_SPEC
struct LocaleNameStr
{
    char const* name;
    LocaleConstant locale;
};

// used for search by name or iterate all names
static LocaleNameStr fullLocaleNameList[] =
{
    { "enUS", LOCALE_enUS },
    { "enGB", LOCALE_enUS },
    { "enTW", LOCALE_enUS },
    { "koKR", LOCALE_koKR },
    { "frFR", LOCALE_frFR },
    { "deDE", LOCALE_deDE },
    { "zhCN", LOCALE_zhCN },
    { "zhTW", LOCALE_zhTW },
    { "esES", LOCALE_esES },
    { "esMX", LOCALE_esMX },
    { "ruRU", LOCALE_ruRU },
    { NULL,   LOCALE_enUS }
};

std::string AcceptableClientBuildsListStr();

typedef std::list<uint32> SimpleFactionsList;

SimpleFactionsList const* GetFactionTeamList(uint32 faction);
char* GetPetName(uint32 petfamily, uint32 dbclang);
uint32 GetTalentSpellCost(uint32 spellId);
TalentSpellPos const* GetTalentSpellPos(uint32 spellId);

int32 GetAreaFlagByAreaID(uint32 area_id);                  // -1 if not found
uint32 GetAreaFlagByMapId(uint32 mapid);

MANGOS_DLL_SPEC AreaTableEntry const* GetAreaEntryByAreaID(uint32 area_id);
MANGOS_DLL_SPEC AreaTableEntry const* GetAreaEntryByAreaFlagAndMap(uint32 area_flag,uint32 map_id);

uint32 GetVirtualMapForMapAndZone(uint32 mapid, uint32 zoneId);

enum ContentLevels
{
    CONTENT_1_60 = 0,
    CONTENT_61_70,
    CONTENT_71_80
};
ContentLevels GetContentLevelsForMapAndZone(uint32 mapid, uint32 zoneId);

ChatChannelsEntry const* GetChannelEntryFor(uint32 channel_id);

bool IsTotemCategoryCompatiableWith(uint32 itemTotemCategoryId, uint32 requiredTotemCategoryId);

bool Zone2MapCoordinates(float& x,float& y,uint32 zone);
bool Map2ZoneCoordinates(float& x,float& y,uint32 zone);

/*pair32(map,diff)*/
typedef std::map<uint32,MapDifficulty> MapDifficultyMap;
MapDifficulty const* GetMapDifficultyData(uint32 mapId, Difficulty difficulty);

/*[3]*/
uint32 const*  GetTalentTabPages(uint32 cls);

PvPDifficultyEntry const* GetBattlegroundBracketByLevel(uint32 mapid, uint32 level);
PvPDifficultyEntry const* GetBattlegroundBracketById(uint32 mapid, BattleGroundBracketId id);

//extern DBCStorage <AchievementEntry>             sAchievementStore;
//extern DBCStorage <AchievementCriteriaEntry>     sAchievementCriteriaStore;
//extern DBCStorage <AreaTableEntry>               sAreaStore;// recommend access using functions
//extern DBCStorage <AreaGroupEntry>               sAreaGroupStore;
//extern DBCStorage <AreaTriggerEntry>             sAreaTriggerStore;
//extern DBCStorage <AuctionHouseEntry>            sAuctionHouseStore;
//extern DBCStorage <BankBagSlotPricesEntry>       sBankBagSlotPricesStore;
//extern DBCStorage <BarberShopStyleEntry>         sBarberShopStyleStore;
//extern DBCStorage <BattlemasterListEntry>        sBattlemasterListStore;
////extern DBCStorage <ChatChannelsEntry>           sChatChannelsStore; -- accessed using function, no usable index
//extern DBCStorage <CharStartOutfitEntry>         sCharStartOutfitStore;
//extern DBCStorage <CharTitlesEntry>              sCharTitlesStore;
//extern DBCStorage <ChrClassesEntry>              sChrClassesStore;
//extern DBCStorage <ChrRacesEntry>                sChrRacesStore;
//extern DBCStorage <CinematicSequencesEntry>      sCinematicSequencesStore;
//extern DBCStorage <CreatureDisplayInfoEntry>     sCreatureDisplayInfoStore;
//extern DBCStorage <CreatureFamilyEntry>          sCreatureFamilyStore;
//extern DBCStorage <CreatureSpellDataEntry>       sCreatureSpellDataStore;
//extern DBCStorage <CreatureTypeEntry>            sCreatureTypeStore;
//extern DBCStorage <CurrencyTypesEntry>           sCurrencyTypesStore;
//extern DBCStorage <DurabilityCostsEntry>         sDurabilityCostsStore;
//extern DBCStorage <DurabilityQualityEntry>       sDurabilityQualityStore;
//extern DBCStorage <EmotesEntry>                  sEmotesStore;
//extern DBCStorage <EmotesTextEntry>              sEmotesTextStore;
//extern DBCStorage <FactionEntry>                 sFactionStore;
//extern DBCStorage <FactionTemplateEntry>         sFactionTemplateStore;
//extern DBCStorage <GameObjectDisplayInfoEntry>   sGameObjectDisplayInfoStore;
//extern DBCStorage <GemPropertiesEntry>           sGemPropertiesStore;
//extern DBCStorage <GlyphPropertiesEntry>         sGlyphPropertiesStore;
//extern DBCStorage <GlyphSlotEntry>               sGlyphSlotStore;
//
//extern DBCStorage <GtBarberShopCostBaseEntry>    sGtBarberShopCostBaseStore;
//extern DBCStorage <GtCombatRatingsEntry>         sGtCombatRatingsStore;
//extern DBCStorage <GtChanceToMeleeCritBaseEntry> sGtChanceToMeleeCritBaseStore;
//extern DBCStorage <GtChanceToMeleeCritEntry>     sGtChanceToMeleeCritStore;
//extern DBCStorage <GtChanceToSpellCritBaseEntry> sGtChanceToSpellCritBaseStore;
//extern DBCStorage <GtChanceToSpellCritEntry>     sGtChanceToSpellCritStore;
//extern DBCStorage <GtOCTRegenHPEntry>            sGtOCTRegenHPStore;
////extern DBCStorage <GtOCTRegenMPEntry>            sGtOCTRegenMPStore; -- not used currently
//extern DBCStorage <GtRegenHPPerSptEntry>         sGtRegenHPPerSptStore;
//extern DBCStorage <GtRegenMPPerSptEntry>         sGtRegenMPPerSptStore;
//extern DBCStorage <HolidaysEntry>                sHolidaysStore;
//extern DBCStorage <ItemEntry>                    sItemStore;
//extern DBCStorage <ItemBagFamilyEntry>           sItemBagFamilyStore;
////extern DBCStorage <ItemDisplayInfoEntry>      sItemDisplayInfoStore; -- not used currently
//extern DBCStorage <ItemExtendedCostEntry>        sItemExtendedCostStore;
//extern DBCStorage <ItemLimitCategoryEntry>       sItemLimitCategoryStore;
//extern DBCStorage <ItemRandomPropertiesEntry>    sItemRandomPropertiesStore;
//extern DBCStorage <ItemRandomSuffixEntry>        sItemRandomSuffixStore;
//extern DBCStorage <ItemSetEntry>                 sItemSetStore;
//extern DBCStorage <LockEntry>                    sLockStore;
//extern DBCStorage <MailTemplateEntry>            sMailTemplateStore;
//extern DBCStorage <MapEntry>                     sMapStore;
////extern DBCStorage <MapDifficultyEntry>           sMapDifficultyStore; -- use GetMapDifficultyData insteed
//extern MapDifficultyMap                          sMapDifficultyMap;
//extern DBCStorage <MovieEntry>                   sMovieStore;
//extern DBCStorage <QuestFactionRewardEntry>      sQuestFactionRewardStore;
//extern DBCStorage <QuestSortEntry>               sQuestSortStore;
//extern DBCStorage <QuestXPLevel>                 sQuestXPLevelStore;
////extern DBCStorage <PvPDifficultyEntry>           sPvPDifficultyStore; -- use GetBattlegroundSlotByLevel for access
//extern DBCStorage <RandomPropertiesPointsEntry>  sRandomPropertiesPointsStore;
//extern DBCStorage <ScalingStatDistributionEntry> sScalingStatDistributionStore;
//extern DBCStorage <ScalingStatValuesEntry>       sScalingStatValuesStore;
//extern DBCStorage <SkillLineEntry>               sSkillLineStore;
//extern DBCStorage <SkillLineAbilityEntry>        sSkillLineAbilityStore;
//extern DBCStorage <SoundEntriesEntry>            sSoundEntriesStore;
//extern DBCStorage <SpellCastTimesEntry>          sSpellCastTimesStore;
//extern DBCStorage <SpellDurationEntry>           sSpellDurationStore;
//extern DBCStorage <SpellFocusObjectEntry>        sSpellFocusObjectStore;
//extern DBCStorage <SpellItemEnchantmentEntry>    sSpellItemEnchantmentStore;
//extern DBCStorage <SpellItemEnchantmentConditionEntry> sSpellItemEnchantmentConditionStore;
//extern SpellCategoryStore                        sSpellCategoryStore;
//extern PetFamilySpellsStore                      sPetFamilySpellsStore;
//extern DBCStorage <SpellRadiusEntry>             sSpellRadiusStore;
//extern DBCStorage <SpellRangeEntry>              sSpellRangeStore;
//extern DBCStorage <SpellRuneCostEntry>           sSpellRuneCostStore;
//extern DBCStorage <SpellShapeshiftEntry>         sSpellShapeshiftStore;
//extern DBCStorage <SpellEntry>                   sSpellStore;
//extern DBCStorage <StableSlotPricesEntry>        sStableSlotPricesStore;
//extern DBCStorage <SummonPropertiesEntry>        sSummonPropertiesStore;
//extern DBCStorage <TalentEntry>                  sTalentStore;
//extern DBCStorage <TalentTabEntry>               sTalentTabStore;
//extern DBCStorage <TaxiNodesEntry>               sTaxiNodesStore;
//extern DBCStorage <TaxiPathEntry>                sTaxiPathStore;
//extern TaxiMask                                  sTaxiNodesMask;
//extern TaxiMask                                  sOldContinentsNodesMask;
//extern TaxiPathSetBySource                       sTaxiPathSetBySource;
//extern TaxiPathNodesByPath                       sTaxiPathNodesByPath;
//extern DBCStorage <TotemCategoryEntry>           sTotemCategoryStore;
//extern DBCStorage <VehicleEntry>                 sVehicleStore;
//extern DBCStorage <VehicleSeatEntry>             sVehicleSeatStore;
////extern DBCStorage <WorldMapAreaEntry>           sWorldMapAreaStore; -- use Zone2MapCoordinates and Map2ZoneCoordinates
//extern DBCStorage <WorldMapOverlayEntry>         sWorldMapOverlayStore;
//extern DBCStorage <WorldSafeLocsEntry>           sWorldSafeLocsStore;

bool LoadDBCStores(const std::string& dataPath, int build);

bool LoadMyDBCStores(const std::string& dataPath, int build);

// script support functions
//MANGOS_DLL_SPEC DBCStorage <SoundEntriesEntry>          const* GetSoundEntriesStore();
//MANGOS_DLL_SPEC DBCStorage <SpellEntry>                 const* GetSpellStore();
//MANGOS_DLL_SPEC DBCStorage <SpellRangeEntry>            const* GetSpellRangeStore();
//MANGOS_DLL_SPEC DBCStorage <FactionEntry>               const* GetFactionStore();
//MANGOS_DLL_SPEC DBCStorage <ItemEntry>                  const* GetItemDisplayStore();
//MANGOS_DLL_SPEC DBCStorage <CreatureDisplayInfoEntry>   const* GetCreatureDisplayStore();
//MANGOS_DLL_SPEC DBCStorage <EmotesEntry>                const* GetEmotesStore();
//MANGOS_DLL_SPEC DBCStorage <EmotesTextEntry>            const* GetEmotesTextStore();


MANGOS_DLL_SPEC DBCStorage<TaxiPathEntry>  const* GetTaxiPathStore();
MANGOS_DLL_SPEC DBCStorage<SkillLineAbilityEntry>  const* GetSkillLineAbilityStore();
MANGOS_DLL_SPEC DBCStorage<ItemRandomSuffixEntry>  const* GetItemRandomSuffixStore();
MANGOS_DLL_SPEC DBCStorage<QuestXPLevel>  const* GetQuestXPLevelStore();
MANGOS_DLL_SPEC DBCStorage<TotemCategoryEntry>  const* GetTotemCategoryStore();
MANGOS_DLL_SPEC DBCStorage<GlyphSlotEntry>  const* GetGlyphSlotStore();
MANGOS_DLL_SPEC DBCStorage<QuestSortEntry>  const* GetQuestSortStore();
MANGOS_DLL_SPEC DBCStorage<MovieEntry>  const* GetMovieStore();
MANGOS_DLL_SPEC DBCStorage<RandomPropertiesPointsEntry>  const* GetRandomPropertiesPointsStore();
MANGOS_DLL_SPEC DBCStorage<ScalingStatDistributionEntry>  const* GetScalingStatDistributionStore();
MANGOS_DLL_SPEC DBCStorage<ScalingStatValuesEntry>  const* GetScalingStatValuesStore();
MANGOS_DLL_SPEC DBCStorage<WorldSafeLocsEntry>  const* GetWorldSafeLocsStore();
MANGOS_DLL_SPEC DBCStorage<WorldMapOverlayEntry>  const* GetWorldMapOverlayStore();
MANGOS_DLL_SPEC DBCStorage<DurabilityCostsEntry>  const* GetDurabilityCostsStore();
MANGOS_DLL_SPEC DBCStorage<ItemRandomPropertiesEntry>  const* GetItemRandomPropertiesStore();
MANGOS_DLL_SPEC DBCStorage<GtOCTRegenHPEntry>  const* GetGtOCTRegenHPStore();
MANGOS_DLL_SPEC DBCStorage<TalentTabEntry>  const* GetTalentTabStore();
MANGOS_DLL_SPEC DBCStorage<SpellItemEnchantmentEntry>  const* GetSpellItemEnchantmentStore();
MANGOS_DLL_SPEC DBCStorage<VehicleEntry>  const* GetVehicleStore();
MANGOS_DLL_SPEC DBCStorage<ChrClassesEntry>  const* GetChrClassesStore();
MANGOS_DLL_SPEC DBCStorage<BarberShopStyleEntry>  const* GetBarberShopStyleStore();
MANGOS_DLL_SPEC DBCStorage<MailTemplateEntry>  const* GetMailTemplateStore();
MANGOS_DLL_SPEC DBCStorage<SpellEntry>  const* GetSpellStore();
MANGOS_DLL_SPEC DBCStorage<AreaTriggerEntry>  const* GetAreaTriggerStore();
MANGOS_DLL_SPEC DBCStorage<MapEntry>  const* GetMapStore();
MANGOS_DLL_SPEC DBCStorage<ChrRacesEntry>  const* GetChrRacesStore();
MANGOS_DLL_SPEC DBCStorage<FactionEntry>  const* GetFactionStore();
MANGOS_DLL_SPEC DBCStorage<ItemLimitCategoryEntry>  const* GetItemLimitCategoryStore();
MANGOS_DLL_SPEC DBCStorage<AuctionHouseEntry>  const* GetAuctionHouseStore();
MANGOS_DLL_SPEC DBCStorage<SpellRadiusEntry>  const* GetSpellRadiusStore();
MANGOS_DLL_SPEC DBCStorage<HolidaysEntry>  const* GetHolidaysStore();
MANGOS_DLL_SPEC DBCStorage<ItemBagFamilyEntry>  const* GetItemBagFamilyStore();
MANGOS_DLL_SPEC DBCStorage<CreatureSpellDataEntry>  const* GetCreatureSpellDataStore();
MANGOS_DLL_SPEC DBCStorage<CharTitlesEntry>  const* GetCharTitlesStore();
MANGOS_DLL_SPEC DBCStorage<CreatureDisplayInfoEntry>  const* GetCreatureDisplayInfoStore();
MANGOS_DLL_SPEC DBCStorage<AchievementCriteriaEntry>  const* GetAchievementCriteriaStore();
MANGOS_DLL_SPEC DBCStorage<GtCombatRatingsEntry>  const* GetGtCombatRatingsStore();
MANGOS_DLL_SPEC DBCStorage<GtChanceToSpellCritBaseEntry>  const* GetGtChanceToSpellCritBaseStore();
MANGOS_DLL_SPEC DBCStorage<GtChanceToMeleeCritBaseEntry>  const* GetGtChanceToMeleeCritBaseStore();
MANGOS_DLL_SPEC DBCStorage<EmotesTextEntry>  const* GetEmotesTextStore();
MANGOS_DLL_SPEC DBCStorage<CreatureFamilyEntry>  const* GetCreatureFamilyStore();
MANGOS_DLL_SPEC DBCStorage<AchievementEntry>  const* GetAchievementStore();
MANGOS_DLL_SPEC DBCStorage<SpellFocusObjectEntry>  const* GetSpellFocusObjectStore();
MANGOS_DLL_SPEC DBCStorage<SpellShapeshiftEntry>  const* GetSpellShapeshiftStore();
MANGOS_DLL_SPEC DBCStorage<SoundEntriesEntry>  const* GetSoundEntriesStore();
MANGOS_DLL_SPEC DBCStorage<TalentEntry>  const* GetTalentStore();
MANGOS_DLL_SPEC DBCStorage<EmotesEntry>  const* GetEmotesStore();
MANGOS_DLL_SPEC DBCStorage<CurrencyTypesEntry>  const* GetCurrencyTypesStore();
MANGOS_DLL_SPEC DBCStorage<ItemSetEntry>  const* GetItemSetStore();
MANGOS_DLL_SPEC DBCStorage<ItemEntry>  const* GetItemStore();
MANGOS_DLL_SPEC DBCStorage<ItemExtendedCostEntry>  const* GetItemExtendedCostStore();
MANGOS_DLL_SPEC DBCStorage<CharStartOutfitEntry>  const* GetCharStartOutfitStore();
MANGOS_DLL_SPEC DBCStorage<SpellRangeEntry>  const* GetSpellRangeStore();
MANGOS_DLL_SPEC DBCStorage<QuestFactionRewardEntry>  const* GetQuestFactionRewardStore();
MANGOS_DLL_SPEC DBCStorage<SpellRuneCostEntry>  const* GetSpellRuneCostStore();
MANGOS_DLL_SPEC DBCStorage<SpellItemEnchantmentConditionEntry>  const* GetSpellItemEnchantmentConditionStore();
MANGOS_DLL_SPEC DBCStorage<LockEntry>  const* GetLockStore();
MANGOS_DLL_SPEC DBCStorage<DurabilityQualityEntry>  const* GetDurabilityQualityStore();
MANGOS_DLL_SPEC DBCStorage<BattlemasterListEntry>  const* GetBattlemasterListStore();
MANGOS_DLL_SPEC DBCStorage<SpellDurationEntry>  const* GetSpellDurationStore();
MANGOS_DLL_SPEC DBCStorage<CreatureTypeEntry>  const* GetCreatureTypeStore();
MANGOS_DLL_SPEC DBCStorage<GtRegenMPPerSptEntry>  const* GetGtRegenMPPerSptStore();
MANGOS_DLL_SPEC DBCStorage<GlyphPropertiesEntry>  const* GetGlyphPropertiesStore();
MANGOS_DLL_SPEC DBCStorage<GameObjectDisplayInfoEntry>  const* GetGameObjectDisplayInfoStore();
MANGOS_DLL_SPEC DBCStorage<GtRegenHPPerSptEntry>  const* GetGtRegenHPPerSptStore();
MANGOS_DLL_SPEC DBCStorage<CinematicSequencesEntry>  const* GetCinematicSequencesStore();
MANGOS_DLL_SPEC DBCStorage<GtChanceToSpellCritEntry>  const* GetGtChanceToSpellCritStore();
MANGOS_DLL_SPEC DBCStorage<SkillLineEntry>  const* GetSkillLineStore();
MANGOS_DLL_SPEC DBCStorage<GtChanceToMeleeCritEntry>  const* GetGtChanceToMeleeCritStore();
MANGOS_DLL_SPEC DBCStorage<VehicleSeatEntry>  const* GetVehicleSeatStore();
MANGOS_DLL_SPEC DBCStorage<FactionTemplateEntry>  const* GetFactionTemplateStore();
MANGOS_DLL_SPEC DBCStorage<TaxiNodesEntry>  const* GetTaxiNodesStore();
MANGOS_DLL_SPEC DBCStorage<BankBagSlotPricesEntry>  const* GetBankBagSlotPricesStore();
MANGOS_DLL_SPEC DBCStorage<SummonPropertiesEntry>  const* GetSummonPropertiesStore();
MANGOS_DLL_SPEC DBCStorage<GemPropertiesEntry>  const* GetGemPropertiesStore();
MANGOS_DLL_SPEC DBCStorage<AreaGroupEntry>  const* GetAreaGroupStore();
MANGOS_DLL_SPEC DBCStorage<StableSlotPricesEntry>  const* GetStableSlotPricesStore();
MANGOS_DLL_SPEC DBCStorage<SpellCastTimesEntry>  const* GetSpellCastTimesStore();
MANGOS_DLL_SPEC DBCStorage<SpellDifficultyEntry>  const* GetSpellDifficultyStore();
MANGOS_DLL_SPEC DBCStorage<GtBarberShopCostBaseEntry>  const* GetGtBarberShopCostBaseStore();
//MANGOS_DLL_SPEC DBCStorage<AchievementCategoryEntry>  const* GetAchievementCategoryStore();
MANGOS_DLL_SPEC DBCStorage<MapDifficultyEntry>  const* GetMapDifficultyStore();
//MANGOS_DLL_SPEC DBCStorage<ItemDisplayInfoEntry>  const* GetItemDisplayInfoStore();
MANGOS_DLL_SPEC DBCStorage<WorldMapAreaEntry>  const* GetWorldMapAreaStore();
MANGOS_DLL_SPEC DBCStorage<AreaTableEntry>  const* GetAreaTableStore();
MANGOS_DLL_SPEC DBCStorage<PvPDifficultyEntry>  const* GetPvPDifficultyStore();
//MANGOS_DLL_SPEC DBCStorage<GtOCTRegenMPEntry>  const* GetGtOCTRegenMPStore();
MANGOS_DLL_SPEC DBCStorage<ChatChannelsEntry>  const* GetChatChannelsStore();
MANGOS_DLL_SPEC DBCStorage<TaxiPathNodeEntry>  const* GetTaxiPathNodeStore();
#endif
