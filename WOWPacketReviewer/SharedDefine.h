//---------------------------------------------------------------------------

#ifndef SharedDefineH
#define SharedDefineH
//---------------------------------------------------------------------------
#include <vcl.h>
#include "ReviewerCommon.h"
#include "UpdateFields.h"


///////////////////////////////////////////////////////////////////////////

enum SpellCastTargetFlags
{
    TARGET_FLAG_SELF            = 0x00000000,
    TARGET_FLAG_UNUSED1         = 0x00000001,               // not used in any spells as of 3.0.3 (can be set dynamically)
    TARGET_FLAG_UNIT            = 0x00000002,               // pguid
    TARGET_FLAG_UNUSED2         = 0x00000004,               // not used in any spells as of 3.0.3 (can be set dynamically)
    TARGET_FLAG_UNUSED3         = 0x00000008,               // not used in any spells as of 3.0.3 (can be set dynamically)
    TARGET_FLAG_ITEM            = 0x00000010,               // pguid
    TARGET_FLAG_SOURCE_LOCATION = 0x00000020,               // 3 float
    TARGET_FLAG_DEST_LOCATION   = 0x00000040,               // 3 float
    TARGET_FLAG_OBJECT_UNK      = 0x00000080,               // used in 7 spells only
    TARGET_FLAG_UNIT_UNK        = 0x00000100,               // looks like self target (480 spells)
    TARGET_FLAG_PVP_CORPSE      = 0x00000200,               // pguid
    TARGET_FLAG_UNIT_CORPSE     = 0x00000400,               // 10 spells (gathering professions)
    TARGET_FLAG_OBJECT          = 0x00000800,               // pguid, 2 spells
    TARGET_FLAG_TRADE_ITEM      = 0x00001000,               // pguid, 0 spells
    TARGET_FLAG_STRING          = 0x00002000,               // string, 0 spells
    TARGET_FLAG_UNK1            = 0x00004000,               // 199 spells, opening object/lock
    TARGET_FLAG_CORPSE          = 0x00008000,               // pguid, resurrection spells
    TARGET_FLAG_UNK2            = 0x00010000,               // pguid, not used in any spells as of 3.0.3 (can be set dynamically)
    TARGET_FLAG_GLYPH           = 0x00020000,               // used in glyph spells
    TARGET_FLAG_UNK3            = 0x00040000,               // 
    TARGET_FLAG_UNK4            = 0x00080000                // uint32, loop { vec3, guid -> if guid == 0 break }
};


enum SpellCastFlags
{
    CAST_FLAG_NONE               = 0x00000000,
    CAST_FLAG_UNKNOWN0           = 0x00000001,              // may be pending spell cast
    CAST_FLAG_UNKNOWN1           = 0x00000002,
    CAST_FLAG_UNKNOWN11          = 0x00000004,
    CAST_FLAG_UNKNOWN12          = 0x00000008,
    CAST_FLAG_UNKNOWN2           = 0x00000010,
    CAST_FLAG_AMMO               = 0x00000020,              // Projectiles visual
    CAST_FLAG_UNKNOWN8           = 0x00000040,
    CAST_FLAG_UNKNOWN9           = 0x00000080,
    CAST_FLAG_UNKNOWN3           = 0x00000100,
    CAST_FLAG_UNKNOWN13          = 0x00000200,
    CAST_FLAG_UNKNOWN14          = 0x00000400,
    CAST_FLAG_UNKNOWN6           = 0x00000800,              // wotlk, trigger rune cooldown
    CAST_FLAG_UNKNOWN15          = 0x00001000,
    CAST_FLAG_UNKNOWN16          = 0x00002000,
    CAST_FLAG_UNKNOWN17          = 0x00004000,
    CAST_FLAG_UNKNOWN18          = 0x00008000,
    CAST_FLAG_UNKNOWN19          = 0x00010000,
    CAST_FLAG_UNKNOWN4           = 0x00020000,              // wotlk
    CAST_FLAG_UNKNOWN10          = 0x00040000,
    CAST_FLAG_UNKNOWN5           = 0x00080000,              // wotlk
    CAST_FLAG_UNKNOWN20          = 0x00100000,
    CAST_FLAG_UNKNOWN7           = 0x00200000,              // wotlk, rune cooldown list
    CAST_FLAG_UNKNOWN21          = 0x04000000
};

enum SpellNotifyPushType
{
    PUSH_IN_FRONT,
    PUSH_IN_FRONT_90,
    PUSH_IN_FRONT_30,
    PUSH_IN_FRONT_15,
    PUSH_IN_BACK,
    PUSH_SELF_CENTER,
    PUSH_DEST_CENTER,
    PUSH_TARGET_CENTER
};

enum SpellMissInfo
{
    SPELL_MISS_NONE                    = 0,
    SPELL_MISS_MISS                    = 1,
    SPELL_MISS_RESIST                  = 2,
    SPELL_MISS_DODGE                   = 3,
    SPELL_MISS_PARRY                   = 4,
    SPELL_MISS_BLOCK                   = 5,
    SPELL_MISS_EVADE                   = 6,
    SPELL_MISS_IMMUNE                  = 7,
    SPELL_MISS_IMMUNE2                 = 8,
    SPELL_MISS_DEFLECT                 = 9,
    SPELL_MISS_ABSORB                  = 10,
    SPELL_MISS_REFLECT                 = 11
};

enum MovementFlags2
{
    MOVEFLAG2_NONE              = 0x0000,
    MOVEFLAG2_UNK1              = 0x0001,
    MOVEFLAG2_UNK2              = 0x0002,
    MOVEFLAG2_UNK3              = 0x0004,
    MOVEFLAG2_FULLSPEEDTURNING  = 0x0008,
    MOVEFLAG2_FULLSPEEDPITCHING = 0x0010,
    MOVEFLAG2_ALLOW_PITCHING    = 0x0020,
    MOVEFLAG2_UNK4              = 0x0040,
    MOVEFLAG2_UNK5              = 0x0080,
    MOVEFLAG2_UNK6              = 0x0100,
    MOVEFLAG2_UNK7              = 0x0200,
    MOVEFLAG2_INTERP_MOVEMENT   = 0x0400,
    MOVEFLAG2_INTERP_TURNING    = 0x0800,
    MOVEFLAG2_INTERP_PITCHING   = 0x1000,
    MOVEFLAG2_UNK8              = 0x2000,
    MOVEFLAG2_UNK9              = 0x4000,
    MOVEFLAG2_UNK10             = 0x8000,
    MOVEFLAG2_INTERP_MASK       = MOVEFLAG2_INTERP_MOVEMENT | MOVEFLAG2_INTERP_TURNING | MOVEFLAG2_INTERP_PITCHING
};

enum SplineFlags
{
    SPLINEFLAG_NONE         = 0x00000000,
    SPLINEFLAG_FORWARD      = 0x00000001,
    SPLINEFLAG_BACKWARD     = 0x00000002,
    SPLINEFLAG_STRAFE_LEFT  = 0x00000004,
    SPLINEFLAG_STRAFE_RIGHT = 0x00000008,
    SPLINEFLAG_LEFT         = 0x00000010,
    SPLINEFLAG_RIGHT        = 0x00000020,
    SPLINEFLAG_PITCH_UP     = 0x00000040,
    SPLINEFLAG_PITCH_DOWN   = 0x00000080,
    SPLINEFLAG_DONE         = 0x00000100,
    SPLINEFLAG_FALLING      = 0x00000200,
    SPLINEFLAG_NO_SPLINE    = 0x00000400,
    SPLINEFLAG_TRAJECTORY   = 0x00000800,
    SPLINEFLAG_WALKMODE     = 0x00001000,
    SPLINEFLAG_FLYING       = 0x00002000,
    SPLINEFLAG_KNOCKBACK    = 0x00004000,
    SPLINEFLAG_FINALPOINT   = 0x00008000,
    SPLINEFLAG_FINALTARGET  = 0x00010000,
    SPLINEFLAG_FINALFACING  = 0x00020000,
    SPLINEFLAG_CATMULLROM   = 0x00040000,
    SPLINEFLAG_UNKNOWN1     = 0x00080000,
    SPLINEFLAG_UNKNOWN2     = 0x00100000,
    SPLINEFLAG_TAKEOFF      = 0x00200000,
    SPLINEFLAG_UNKNOWN4     = 0x00400000,
    SPLINEFLAG_UNKNOWN5     = 0x00800000,
    SPLINEFLAG_UNKNOWN6     = 0x01000000,
    SPLINEFLAG_UNKNOWN7     = 0x02000000,
    SPLINEFLAG_UNKNOWN8     = 0x04000000,
    SPLINEFLAG_UNKNOWN9     = 0x08000000,
    SPLINEFLAG_UNKNOWN10    = 0x10000000,
    SPLINEFLAG_UNKNOWN11    = 0x20000000,
    SPLINEFLAG_UNKNOWN12    = 0x40000000
};

enum SplineMode
{
    SPLINEMODE_LINEAR       = 0,
    SPLINEMODE_CATMULLROM   = 1,
    SPLINEMODE_BEZIER3      = 2
};

enum SplineType
{
    SPLINETYPE_NORMAL       = 0,
    SPLINETYPE_STOP         = 1,
    SPLINETYPE_FACINGSPOT   = 2,
    SPLINETYPE_FACINGTARGET = 3,
    SPLINETYPE_FACINGANGLE  = 4
};


enum UnitModifierType
{
    BASE_VALUE = 0,
    BASE_PCT = 1,
    TOTAL_VALUE = 2,
    TOTAL_PCT = 3,
    MODIFIER_TYPE_END = 4
};

enum WeaponDamageRange
{
    MINDAMAGE,
    MAXDAMAGE
};

enum DamageTypeToSchool
{
    RESISTANCE,
    DAMAGE_DEALT,
    DAMAGE_TAKEN
};

enum AuraRemoveMode
{
    AURA_REMOVE_BY_DEFAULT,
    AURA_REMOVE_BY_STACK,                                   // at replace by similar aura
    AURA_REMOVE_BY_CANCEL,
    AURA_REMOVE_BY_DISPEL,
    AURA_REMOVE_BY_DEATH,
    AURA_REMOVE_BY_DELETE,                                  // use for speedup and prevent unexpected effects at player logout/pet unsummon (must be used _only_ after save), delete.
};

enum UnitMods
{
    UNIT_MOD_STAT_STRENGTH,                                 // UNIT_MOD_STAT_STRENGTH..UNIT_MOD_STAT_SPIRIT must be in existed order, it's accessed by index values of Stats enum.
    UNIT_MOD_STAT_AGILITY,
    UNIT_MOD_STAT_STAMINA,
    UNIT_MOD_STAT_INTELLECT,
    UNIT_MOD_STAT_SPIRIT,
    UNIT_MOD_HEALTH,
    UNIT_MOD_MANA,                                          // UNIT_MOD_MANA..UNIT_MOD_RUNIC_POWER must be in existed order, it's accessed by index values of Powers enum.
    UNIT_MOD_RAGE,
    UNIT_MOD_FOCUS,
    UNIT_MOD_ENERGY,
    UNIT_MOD_HAPPINESS,
    UNIT_MOD_RUNE,
    UNIT_MOD_RUNIC_POWER,
    UNIT_MOD_ARMOR,                                         // UNIT_MOD_ARMOR..UNIT_MOD_RESISTANCE_ARCANE must be in existed order, it's accessed by index values of SpellSchools enum.
    UNIT_MOD_RESISTANCE_HOLY,
    UNIT_MOD_RESISTANCE_FIRE,
    UNIT_MOD_RESISTANCE_NATURE,
    UNIT_MOD_RESISTANCE_FROST,
    UNIT_MOD_RESISTANCE_SHADOW,
    UNIT_MOD_RESISTANCE_ARCANE,
    UNIT_MOD_ATTACK_POWER,
    UNIT_MOD_ATTACK_POWER_RANGED,
    UNIT_MOD_DAMAGE_MAINHAND,
    UNIT_MOD_DAMAGE_OFFHAND,
    UNIT_MOD_DAMAGE_RANGED,
    UNIT_MOD_END,
    // synonyms
    UNIT_MOD_STAT_START = UNIT_MOD_STAT_STRENGTH,
    UNIT_MOD_STAT_END = UNIT_MOD_STAT_SPIRIT + 1,
    UNIT_MOD_RESISTANCE_START = UNIT_MOD_ARMOR,
    UNIT_MOD_RESISTANCE_END = UNIT_MOD_RESISTANCE_ARCANE + 1,
    UNIT_MOD_POWER_START = UNIT_MOD_MANA,
    UNIT_MOD_POWER_END = UNIT_MOD_RUNIC_POWER + 1
};

enum BaseModGroup
{
    CRIT_PERCENTAGE,
    RANGED_CRIT_PERCENTAGE,
    OFFHAND_CRIT_PERCENTAGE,
    SHIELD_BLOCK_VALUE,
    BASEMOD_END
};

enum BaseModType
{
    FLAT_MOD,
    PCT_MOD
};

#define MOD_END (PCT_MOD+1)

enum DeathState
{
    ALIVE       = 0,
    JUST_DIED   = 1,
    CORPSE      = 2,
    DEAD        = 3,
    JUST_ALIVED = 4,
    DEAD_FALLING= 5
};

// internal state flags for some auras and movement generators, other.
enum UnitState
{
    // persistent state (applied by aura/etc until expire)
    UNIT_STAT_MELEE_ATTACKING = 0x00000001,                     // unit is melee attacking someone Unit::Attack
    UNIT_STAT_ATTACK_PLAYER   = 0x00000002,                     // unit attack player or player's controlled unit and have contested pvpv timer setup, until timer expire, combat end and etc
    UNIT_STAT_DIED            = 0x00000004,                     // Unit::SetFeignDeath
    UNIT_STAT_STUNNED         = 0x00000008,                     // Aura::HandleAuraModStun
    UNIT_STAT_ROOT            = 0x00000010,                     // Aura::HandleAuraModRoot
    UNIT_STAT_ISOLATED        = 0x00000020,                     // area auras do not affect other players, Aura::HandleAuraModSchoolImmunity

    // persistent movement generator state (all time while movement generator applied to unit (independent from top state of movegen)
    UNIT_STAT_IN_FLIGHT       = 0x00000040,                     // player is in flight mode (in fact interrupted at far teleport until next map telport landing)
    UNIT_STAT_DISTRACTED      = 0x00000080,                     // DistractedMovementGenerator active

    // persistent movement generator state with non-persistent mirror states for stop support
    // (can be removed temporary by stop command or another movement generator apply)
    // not use _MOVE versions for generic movegen state, it can be removed temporary for unit stop and etc
    UNIT_STAT_CONFUSED        = 0x00000100,                     // ConfusedMovementGenerator active/onstack
    UNIT_STAT_CONFUSED_MOVE   = 0x00000200,
    UNIT_STAT_ROAMING         = 0x00000400,                     // RandomMovementGenerator/PointMovementGenerator/WaypointMovementGenerator active (now always set)
    UNIT_STAT_ROAMING_MOVE    = 0x00000800,
    UNIT_STAT_CHASE           = 0x00001000,                     // ChaseMovementGenerator active
    UNIT_STAT_CHASE_MOVE      = 0x00002000,
    UNIT_STAT_FOLLOW          = 0x00004000,                     // FollowMovementGenerator active
    UNIT_STAT_FOLLOW_MOVE     = 0x00008000,
    UNIT_STAT_FLEEING         = 0x00010000,                     // FleeMovementGenerator/TimedFleeingMovementGenerator active/onstack
    UNIT_STAT_FLEEING_MOVE    = 0x00020000,

    // masks (only for check)

    // can't move currently
    UNIT_STAT_CAN_NOT_MOVE    = UNIT_STAT_ROOT | UNIT_STAT_STUNNED | UNIT_STAT_DIED,

    // stay by different reasons
    UNIT_STAT_NOT_MOVE        = UNIT_STAT_ROOT | UNIT_STAT_STUNNED | UNIT_STAT_DIED |
                                UNIT_STAT_DISTRACTED,

    // stay or scripted movement for effect( = in player case you can't move by client command)
    UNIT_STAT_NO_FREE_MOVE    = UNIT_STAT_ROOT | UNIT_STAT_STUNNED | UNIT_STAT_DIED |
                                UNIT_STAT_IN_FLIGHT |
                                UNIT_STAT_CONFUSED | UNIT_STAT_FLEEING,

    // not react at move in sight or other
    UNIT_STAT_CAN_NOT_REACT   = UNIT_STAT_STUNNED | UNIT_STAT_DIED |
                                UNIT_STAT_CONFUSED | UNIT_STAT_FLEEING,

    // masks (for check or reset)

    // for real move using movegen check and stop (except unstoppable flight)
    UNIT_STAT_MOVING          = UNIT_STAT_ROAMING_MOVE | UNIT_STAT_CHASE_MOVE | UNIT_STAT_FOLLOW_MOVE | UNIT_STAT_FLEEING_MOVE,

    UNIT_STAT_ALL_STATE       = 0xFFFFFFFF
};

enum UnitMoveType
{
    MOVE_WALK           = 0,
    MOVE_RUN            = 1,
    MOVE_RUN_BACK       = 2,
    MOVE_SWIM           = 3,
    MOVE_SWIM_BACK      = 4,
    MOVE_TURN_RATE      = 5,
    MOVE_FLIGHT         = 6,
    MOVE_FLIGHT_BACK    = 7,
    MOVE_PITCH_RATE     = 8
};

#define MAX_MOVE_TYPE     9

extern float baseMoveSpeed[MAX_MOVE_TYPE];

enum CombatRating
{
    CR_WEAPON_SKILL             = 0,
    CR_DEFENSE_SKILL            = 1,
    CR_DODGE                    = 2,
    CR_PARRY                    = 3,
    CR_BLOCK                    = 4,
    CR_HIT_MELEE                = 5,
    CR_HIT_RANGED               = 6,
    CR_HIT_SPELL                = 7,
    CR_CRIT_MELEE               = 8,
    CR_CRIT_RANGED              = 9,
    CR_CRIT_SPELL               = 10,
    CR_HIT_TAKEN_MELEE          = 11,
    CR_HIT_TAKEN_RANGED         = 12,
    CR_HIT_TAKEN_SPELL          = 13,
    CR_CRIT_TAKEN_MELEE         = 14,
    CR_CRIT_TAKEN_RANGED        = 15,
    CR_CRIT_TAKEN_SPELL         = 16,
    CR_HASTE_MELEE              = 17,
    CR_HASTE_RANGED             = 18,
    CR_HASTE_SPELL              = 19,
    CR_WEAPON_SKILL_MAINHAND    = 20,
    CR_WEAPON_SKILL_OFFHAND     = 21,
    CR_WEAPON_SKILL_RANGED      = 22,
    CR_EXPERTISE                = 23,
    CR_ARMOR_PENETRATION        = 24
};

#define MAX_COMBAT_RATING         25

enum DamageEffectType
{
    DIRECT_DAMAGE           = 0,                            // used for normal weapon damage (not for class abilities or spells)
    SPELL_DIRECT_DAMAGE     = 1,                            // spell/class abilities damage
    DOT                     = 2,
    HEAL                    = 3,
    NODAMAGE                = 4,                            // used also in case when damage applied to health but not applied to spell channelInterruptFlags/etc
    SELF_DAMAGE             = 5
};

/// internal used flags for marking special auras - for example some dummy-auras
enum UnitAuraFlags
{
    UNIT_AURAFLAG_ALIVE_INVISIBLE   = 0x1,                  // aura which makes unit invisible for alive
};

enum UnitVisibility
{
    VISIBILITY_OFF                = 0,                      // absolute, not detectable, GM-like, can see all other
    VISIBILITY_ON                 = 1,
    VISIBILITY_GROUP_STEALTH      = 2,                      // detect chance, seen and can see group members
    VISIBILITY_GROUP_INVISIBILITY = 3,                      // invisibility, can see and can be seen only another invisible unit or invisible detection unit, set only if not stealthed, and in checks not used (mask used instead)
    VISIBILITY_GROUP_NO_DETECT    = 4,                      // state just at stealth apply for update Grid state. Don't remove, otherwise stealth spells will break
    VISIBILITY_RESPAWN            = 5                       // special totally not detectable visibility for force delete object at respawn command
};

// Value masks for UNIT_FIELD_FLAGS
enum UnitFlags
{
    UNIT_FLAG_UNK_0                 = 0x00000001,
    UNIT_FLAG_NON_ATTACKABLE        = 0x00000002,           // not attackable
    UNIT_FLAG_DISABLE_MOVE          = 0x00000004,
    UNIT_FLAG_PVP_ATTACKABLE        = 0x00000008,           // allow apply pvp rules to attackable state in addition to faction dependent state
    UNIT_FLAG_RENAME                = 0x00000010,
    UNIT_FLAG_PREPARATION           = 0x00000020,           // don't take reagents for spells with SPELL_ATTR_EX5_NO_REAGENT_WHILE_PREP
    UNIT_FLAG_UNK_6                 = 0x00000040,
    UNIT_FLAG_NOT_ATTACKABLE_1      = 0x00000080,           // ?? (UNIT_FLAG_PVP_ATTACKABLE | UNIT_FLAG_NOT_ATTACKABLE_1) is NON_PVP_ATTACKABLE
    UNIT_FLAG_OOC_NOT_ATTACKABLE    = 0x00000100,           // 2.0.8 - (OOC Out Of Combat) Can not be attacked when not in combat. Removed if unit for some reason enter combat.
    UNIT_FLAG_UNK_9                 = 0x00000200,           // 3.0.3 - makes you unable to attack everything
    UNIT_FLAG_LOOTING               = 0x00000400,           // loot animation
    UNIT_FLAG_PET_IN_COMBAT         = 0x00000800,           // in combat?, 2.0.8
    UNIT_FLAG_PVP                   = 0x00001000,           // changed in 3.0.3
    UNIT_FLAG_SILENCED              = 0x00002000,           // silenced, 2.1.1
    UNIT_FLAG_UNK_14                = 0x00004000,           // 2.0.8
    UNIT_FLAG_UNK_15                = 0x00008000,
    UNIT_FLAG_UNK_16                = 0x00010000,           // removes attackable icon
    UNIT_FLAG_PACIFIED              = 0x00020000,           // 3.0.3 ok
    UNIT_FLAG_STUNNED               = 0x00040000,           // 3.0.3 ok
    UNIT_FLAG_IN_COMBAT             = 0x00080000,
    UNIT_FLAG_TAXI_FLIGHT           = 0x00100000,           // disable casting at client side spell not allowed by taxi flight (mounted?), probably used with 0x4 flag
    UNIT_FLAG_DISARMED              = 0x00200000,           // 3.0.3, disable melee spells casting..., "Required melee weapon" added to melee spells tooltip.
    UNIT_FLAG_CONFUSED              = 0x00400000,
    UNIT_FLAG_FLEEING               = 0x00800000,
    UNIT_FLAG_PLAYER_CONTROLLED     = 0x01000000,           // used in spell Eyes of the Beast for pet... let attack by controlled creature
    UNIT_FLAG_NOT_SELECTABLE        = 0x02000000,
    UNIT_FLAG_SKINNABLE             = 0x04000000,
    UNIT_FLAG_MOUNT                 = 0x08000000,
    UNIT_FLAG_UNK_28                = 0x10000000,
    UNIT_FLAG_UNK_29                = 0x20000000,           // used in Feing Death spell
    UNIT_FLAG_SHEATHE               = 0x40000000,
    UNIT_FLAG_UNK_31                = 0x80000000            // set skinnable icon and also changes color of portrait
};

// Value masks for UNIT_FIELD_FLAGS_2
enum UnitFlags2
{
    UNIT_FLAG2_FEIGN_DEATH      = 0x00000001,
    UNIT_FLAG2_UNK1             = 0x00000002,               // Hide unit model (show only player equip)
    UNIT_FLAG2_COMPREHEND_LANG  = 0x00000008,
    UNIT_FLAG2_FORCE_MOVE       = 0x00000040,
    UNIT_FLAG2_REGENERATE_POWER = 0x00000800
};

/// Non Player Character flags
enum NPCFlags
{
    UNIT_NPC_FLAG_NONE                  = 0x00000000,
    UNIT_NPC_FLAG_GOSSIP                = 0x00000001,       // 100%
    UNIT_NPC_FLAG_QUESTGIVER            = 0x00000002,       // guessed, probably ok
    UNIT_NPC_FLAG_UNK1                  = 0x00000004,
    UNIT_NPC_FLAG_UNK2                  = 0x00000008,
    UNIT_NPC_FLAG_TRAINER               = 0x00000010,       // 100%
    UNIT_NPC_FLAG_TRAINER_CLASS         = 0x00000020,       // 100%
    UNIT_NPC_FLAG_TRAINER_PROFESSION    = 0x00000040,       // 100%
    UNIT_NPC_FLAG_VENDOR                = 0x00000080,       // 100%
    UNIT_NPC_FLAG_VENDOR_AMMO           = 0x00000100,       // 100%, general goods vendor
    UNIT_NPC_FLAG_VENDOR_FOOD           = 0x00000200,       // 100%
    UNIT_NPC_FLAG_VENDOR_POISON         = 0x00000400,       // guessed
    UNIT_NPC_FLAG_VENDOR_REAGENT        = 0x00000800,       // 100%
    UNIT_NPC_FLAG_REPAIR                = 0x00001000,       // 100%
    UNIT_NPC_FLAG_FLIGHTMASTER          = 0x00002000,       // 100%
    UNIT_NPC_FLAG_SPIRITHEALER          = 0x00004000,       // guessed
    UNIT_NPC_FLAG_SPIRITGUIDE           = 0x00008000,       // guessed
    UNIT_NPC_FLAG_INNKEEPER             = 0x00010000,       // 100%
    UNIT_NPC_FLAG_BANKER                = 0x00020000,       // 100%
    UNIT_NPC_FLAG_PETITIONER            = 0x00040000,       // 100% 0xC0000 = guild petitions, 0x40000 = arena team petitions
    UNIT_NPC_FLAG_TABARDDESIGNER        = 0x00080000,       // 100%
    UNIT_NPC_FLAG_BATTLEMASTER          = 0x00100000,       // 100%
    UNIT_NPC_FLAG_AUCTIONEER            = 0x00200000,       // 100%
    UNIT_NPC_FLAG_STABLEMASTER          = 0x00400000,       // 100%
    UNIT_NPC_FLAG_GUILD_BANKER          = 0x00800000,       // cause client to send 997 opcode
    UNIT_NPC_FLAG_SPELLCLICK            = 0x01000000,       // cause client to send 1015 opcode (spell click), dynamic, set at loading and don't must be set in DB
    UNIT_NPC_FLAG_GUARD                 = 0x10000000        // custom flag for guards
};

// used in most movement packets (send and received)
enum MovementFlags
{
    MOVEFLAG_NONE               = 0x00000000,
    MOVEFLAG_FORWARD            = 0x00000001,
    MOVEFLAG_BACKWARD           = 0x00000002,
    MOVEFLAG_STRAFE_LEFT        = 0x00000004,
    MOVEFLAG_STRAFE_RIGHT       = 0x00000008,
    MOVEFLAG_TURN_LEFT          = 0x00000010,
    MOVEFLAG_TURN_RIGHT         = 0x00000020,
    MOVEFLAG_PITCH_UP           = 0x00000040,
    MOVEFLAG_PITCH_DOWN         = 0x00000080,
    MOVEFLAG_WALK_MODE          = 0x00000100,               // Walking
    MOVEFLAG_ONTRANSPORT        = 0x00000200,
    MOVEFLAG_LEVITATING         = 0x00000400,
    MOVEFLAG_ROOT               = 0x00000800,
    MOVEFLAG_FALLING            = 0x00001000,
    MOVEFLAG_FALLINGFAR         = 0x00002000,
    MOVEFLAG_PENDINGSTOP        = 0x00004000,
    MOVEFLAG_PENDINGSTRAFESTOP  = 0x00008000,
    MOVEFLAG_PENDINGFORWARD     = 0x00010000,
    MOVEFLAG_PENDINGBACKWARD    = 0x00020000,
    MOVEFLAG_PENDINGSTRAFELEFT  = 0x00040000,
    MOVEFLAG_PENDINGSTRAFERIGHT = 0x00080000,
    MOVEFLAG_PENDINGROOT        = 0x00100000,
    MOVEFLAG_SWIMMING           = 0x00200000,               // appears with fly flag also
    MOVEFLAG_ASCENDING          = 0x00400000,               // swim up also
    MOVEFLAG_DESCENDING         = 0x00800000,               // swim down also
    MOVEFLAG_CAN_FLY            = 0x01000000,               // can fly in 3.3?
    MOVEFLAG_FLYING             = 0x02000000,               // Actual flying mode
    MOVEFLAG_SPLINE_ELEVATION   = 0x04000000,               // used for flight paths
    MOVEFLAG_SPLINE_ENABLED     = 0x08000000,               // used for flight paths
    MOVEFLAG_WATERWALKING       = 0x10000000,               // prevent unit from falling through water
    MOVEFLAG_SAFE_FALL          = 0x20000000,               // active rogue safe fall spell (passive)
    MOVEFLAG_HOVER              = 0x40000000
};



enum Gender
{
    GENDER_MALE                        = 0,
    GENDER_FEMALE                      = 1,
    GENDER_NONE                        = 2
};

// Race value is index in ChrRaces.dbc
enum Races
{
    RACE_HUMAN          = 1,
    RACE_ORC            = 2,
    RACE_DWARF          = 3,
    RACE_NIGHTELF       = 4,
    RACE_UNDEAD_PLAYER  = 5,
    RACE_TAUREN         = 6,
    RACE_GNOME          = 7,
    RACE_TROLL          = 8,
    //RACE_GOBLIN         = 9,
    RACE_BLOODELF       = 10,
    RACE_DRAENEI        = 11,
    //RACE_FEL_ORC        = 12,
    //RACE_NAGA           = 13,
    //RACE_BROKEN         = 14,
    //RACE_SKELETON       = 15,
    //RACE_VRYKUL         = 16,
    //RACE_TUSKARR        = 17,
    //RACE_FOREST_TROLL   = 18,
    //RACE_TAUNKA         = 19,
    //RACE_NORTHREND_SKELETON = 20,
    //RACE_ICE_TROLL      = 21
};

// max+1 for player race
#define MAX_RACES         12

#define RACEMASK_ALL_PLAYABLE \
    ((1<<(RACE_HUMAN-1))   |(1<<(RACE_ORC-1))          |(1<<(RACE_DWARF-1))   | \
    (1<<(RACE_NIGHTELF-1))|(1<<(RACE_UNDEAD_PLAYER-1))|(1<<(RACE_TAUREN-1))  | \
    (1<<(RACE_GNOME-1))   |(1<<(RACE_TROLL-1))        |(1<<(RACE_BLOODELF-1))| \
    (1<<(RACE_DRAENEI-1)) )

// Class value is index in ChrClasses.dbc
enum WOW_Classes
{
    CLASS_WARRIOR       = 1,
    CLASS_PALADIN       = 2,
    CLASS_HUNTER        = 3,
    CLASS_ROGUE         = 4,
    CLASS_PRIEST        = 5,
    CLASS_DEATH_KNIGHT  = 6,
    CLASS_SHAMAN        = 7,
    CLASS_MAGE          = 8,
    CLASS_WARLOCK       = 9,
    // CLASS_UNK2       = 10,unused
    CLASS_DRUID         = 11,
};

// max+1 for player class
#define MAX_CLASSES       12

#define CLASSMASK_ALL_PLAYABLE \
    ((1<<(CLASS_WARRIOR-1))|(1<<(CLASS_PALADIN-1))|(1<<(CLASS_HUNTER-1))| \
    (1<<(CLASS_ROGUE-1))  |(1<<(CLASS_PRIEST-1)) |(1<<(CLASS_SHAMAN-1))| \
    (1<<(CLASS_MAGE-1))   |(1<<(CLASS_WARLOCK-1))|(1<<(CLASS_DRUID-1)) | \
    (1<<(CLASS_DEATH_KNIGHT-1)) )

#define CLASSMASK_ALL_CREATURES ((1<<(CLASS_WARRIOR-1)) | (1<<(CLASS_PALADIN-1)) | (1<<(CLASS_ROGUE-1)) | (1<<(CLASS_MAGE-1)) )

#define CLASSMASK_WAND_USERS ((1<<(CLASS_PRIEST-1))|(1<<(CLASS_MAGE-1))|(1<<(CLASS_WARLOCK-1)))

#define PLAYER_MAX_BATTLEGROUND_QUEUES 2

enum ReputationRank
{
    REP_HATED       = 0,
    REP_HOSTILE     = 1,
    REP_UNFRIENDLY  = 2,
    REP_NEUTRAL     = 3,
    REP_FRIENDLY    = 4,
    REP_HONORED     = 5,
    REP_REVERED     = 6,
    REP_EXALTED     = 7
};

#define MIN_REPUTATION_RANK (REP_HATED)
#define MAX_REPUTATION_RANK 8

enum MoneyConstants
{
    COPPER = 1,
    SILVER = COPPER*100,
    GOLD   = SILVER*100
};

enum Stats
{
    STAT_STRENGTH                      = 0,
    STAT_AGILITY                       = 1,
    STAT_STAMINA                       = 2,
    STAT_INTELLECT                     = 3,
    STAT_SPIRIT                        = 4
};

#define MAX_STATS                        5

enum Powers
{
    POWER_MANA                          = 0,
    POWER_RAGE                          = 1,
    POWER_FOCUS                         = 2,
    POWER_ENERGY                        = 3,
    POWER_HAPPINESS                     = 4,
    POWER_RUNE                          = 5,
    POWER_RUNIC_POWER                   = 6,
    POWER_HEALTH                        = 0xFFFFFFFE    // (-2 as signed value)
};

#define MAX_POWERS                        7

enum SpellSchools
{
    SPELL_SCHOOL_NORMAL                 = 0,
    SPELL_SCHOOL_HOLY                   = 1,
    SPELL_SCHOOL_FIRE                   = 2,
    SPELL_SCHOOL_NATURE                 = 3,
    SPELL_SCHOOL_FROST                  = 4,
    SPELL_SCHOOL_SHADOW                 = 5,
    SPELL_SCHOOL_ARCANE                 = 6
};

#define MAX_SPELL_SCHOOL                  7

enum SpellSchoolMask
{
    SPELL_SCHOOL_MASK_NONE    = 0x00,                       // not exist
    SPELL_SCHOOL_MASK_NORMAL  = (1 << SPELL_SCHOOL_NORMAL), // PHYSICAL (Armor)
    SPELL_SCHOOL_MASK_HOLY    = (1 << SPELL_SCHOOL_HOLY  ),
    SPELL_SCHOOL_MASK_FIRE    = (1 << SPELL_SCHOOL_FIRE  ),
    SPELL_SCHOOL_MASK_NATURE  = (1 << SPELL_SCHOOL_NATURE),
    SPELL_SCHOOL_MASK_FROST   = (1 << SPELL_SCHOOL_FROST ),
    SPELL_SCHOOL_MASK_SHADOW  = (1 << SPELL_SCHOOL_SHADOW),
    SPELL_SCHOOL_MASK_ARCANE  = (1 << SPELL_SCHOOL_ARCANE),

    // unions

    // 124, not include normal and holy damage
    SPELL_SCHOOL_MASK_SPELL   = ( SPELL_SCHOOL_MASK_FIRE   |
                                  SPELL_SCHOOL_MASK_NATURE | SPELL_SCHOOL_MASK_FROST  |
                                  SPELL_SCHOOL_MASK_SHADOW | SPELL_SCHOOL_MASK_ARCANE ),
    // 126
    SPELL_SCHOOL_MASK_MAGIC   = ( SPELL_SCHOOL_MASK_HOLY | SPELL_SCHOOL_MASK_SPELL ),

    // 127
    SPELL_SCHOOL_MASK_ALL     = ( SPELL_SCHOOL_MASK_NORMAL | SPELL_SCHOOL_MASK_MAGIC )
};

inline SpellSchools GetFirstSchoolInMask(SpellSchoolMask mask)
{
    for(int i = 0; i < MAX_SPELL_SCHOOL; ++i)
        if(mask & (1 << i))
            return SpellSchools(i);

    return SPELL_SCHOOL_NORMAL;
}

enum ItemQualities
{
    ITEM_QUALITY_POOR                  = 0,                 //GREY
    ITEM_QUALITY_NORMAL                = 1,                 //WHITE
    ITEM_QUALITY_UNCOMMON              = 2,                 //GREEN
    ITEM_QUALITY_RARE                  = 3,                 //BLUE
    ITEM_QUALITY_EPIC                  = 4,                 //PURPLE
    ITEM_QUALITY_LEGENDARY             = 5,                 //ORANGE
    ITEM_QUALITY_ARTIFACT              = 6,                 //LIGHT YELLOW
    ITEM_QUALITY_HEIRLOOM              = 7
};

#define MAX_ITEM_QUALITY                 8

const uint32 ItemQualityColors[MAX_ITEM_QUALITY] = {
    0xff9d9d9d,        //GREY
    0xffffffff,        //WHITE
    0xff1eff00,        //GREEN
    0xff0070dd,        //BLUE
    0xffa335ee,        //PURPLE
    0xffff8000,        //ORANGE
    0xffe6cc80,        //LIGHT YELLOW
    0xffe6cc80         //LIGHT YELLOW
};


// ***********************************
// Spell Attributes definitions
// ***********************************

#define SPELL_ATTR_UNK0                           0x00000001            // 0
#define SPELL_ATTR_RANGED                         0x00000002            // 1 All ranged abilites have this flag
#define SPELL_ATTR_ON_NEXT_SWING_1                0x00000004            // 2 on next swing
#define SPELL_ATTR_UNK3                           0x00000008            // 3 not set in 3.0.3
#define SPELL_ATTR_UNK4                           0x00000010            // 4 isAbility
#define SPELL_ATTR_TRADESPELL                     0x00000020            // 5 trade spells, will be added by client to a sublist of profession spell
#define SPELL_ATTR_PASSIVE                        0x00000040            // 6 Passive spell
#define SPELL_ATTR_UNK7                           0x00000080            // 7 can't be linked in chat?
#define SPELL_ATTR_UNK8                           0x00000100            // 8 hide created item in tooltip (for effect=24)
#define SPELL_ATTR_UNK9                           0x00000200            // 9
#define SPELL_ATTR_ON_NEXT_SWING_2                0x00000400            // 10 on next swing 2
#define SPELL_ATTR_UNK11                          0x00000800            // 11
#define SPELL_ATTR_DAYTIME_ONLY                   0x00001000            // 12 only useable at daytime, not set in 2.4.2
#define SPELL_ATTR_NIGHT_ONLY                     0x00002000            // 13 only useable at night, not set in 2.4.2
#define SPELL_ATTR_INDOORS_ONLY                   0x00004000            // 14 only useable indoors, not set in 2.4.2
#define SPELL_ATTR_OUTDOORS_ONLY                  0x00008000            // 15 Only useable outdoors.
#define SPELL_ATTR_NOT_SHAPESHIFT                 0x00010000            // 16 Not while shapeshifted
#define SPELL_ATTR_ONLY_STEALTHED                 0x00020000            // 17 Must be in stealth
#define SPELL_ATTR_UNK18                          0x00040000            // 18
#define SPELL_ATTR_LEVEL_DAMAGE_CALCULATION       0x00080000            // 19 spelldamage depends on caster level
#define SPELL_ATTR_STOP_ATTACK_TARGET             0x00100000            // 20 Stop attack after use this spell (and not begin attack if use)
#define SPELL_ATTR_IMPOSSIBLE_DODGE_PARRY_BLOCK   0x00200000            // 21 Cannot be dodged/parried/blocked
#define SPELL_ATTR_UNK22                          0x00400000            // 22
#define SPELL_ATTR_UNK23                          0x00800000            // 23 castable while dead?
#define SPELL_ATTR_CASTABLE_WHILE_MOUNTED         0x01000000            // 24 castable while mounted
#define SPELL_ATTR_DISABLED_WHILE_ACTIVE          0x02000000            // 25 Activate and start cooldown after aura fade or remove summoned creature or go
#define SPELL_ATTR_UNK26                          0x04000000            // 26
#define SPELL_ATTR_CASTABLE_WHILE_SITTING         0x08000000            // 27 castable while sitting
#define SPELL_ATTR_CANT_USED_IN_COMBAT            0x10000000            // 28 Cannot be used in combat
#define SPELL_ATTR_UNAFFECTED_BY_INVULNERABILITY  0x20000000            // 29 unaffected by invulnerability (hmm possible not...)
#define SPELL_ATTR_UNK30                          0x40000000            // 30 breakable by damage?
#define SPELL_ATTR_CANT_CANCEL                    0x80000000            // 31 positive aura can't be canceled

#define SPELL_ATTR_EX_UNK0                        0x00000001            // 0
#define SPELL_ATTR_EX_DRAIN_ALL_POWER             0x00000002            // 1 use all power (Only paladin Lay of Hands and Bunyanize)
#define SPELL_ATTR_EX_CHANNELED_1                 0x00000004            // 2 channeled 1
#define SPELL_ATTR_EX_UNK3                        0x00000008            // 3
#define SPELL_ATTR_EX_UNK4                        0x00000010            // 4
#define SPELL_ATTR_EX_NOT_BREAK_STEALTH           0x00000020            // 5 Not break stealth
#define SPELL_ATTR_EX_CHANNELED_2                 0x00000040            // 6 channeled 2
#define SPELL_ATTR_EX_NEGATIVE                    0x00000080            // 7
#define SPELL_ATTR_EX_NOT_IN_COMBAT_TARGET        0x00000100            // 8 Spell req target not to be in combat state
#define SPELL_ATTR_EX_UNK9                        0x00000200            // 9
#define SPELL_ATTR_EX_NO_INITIAL_AGGRO            0x00000400            // 10 no generates threat on cast 100%
#define SPELL_ATTR_EX_UNK11                       0x00000800            // 11
#define SPELL_ATTR_EX_UNK12                       0x00001000            // 12
#define SPELL_ATTR_EX_UNK13                       0x00002000            // 13
#define SPELL_ATTR_EX_UNK14                       0x00004000            // 14
#define SPELL_ATTR_EX_DISPEL_AURAS_ON_IMMUNITY    0x00008000            // 15 remove auras on immunity
#define SPELL_ATTR_EX_UNAFFECTED_BY_SCHOOL_IMMUNE 0x00010000            // 16 unaffected by school immunity
#define SPELL_ATTR_EX_UNK17                       0x00020000            // 17
#define SPELL_ATTR_EX_UNK18                       0x00040000            // 18
#define SPELL_ATTR_EX_UNK19                       0x00080000            // 19
#define SPELL_ATTR_EX_REQ_COMBO_POINTS1           0x00100000            // 20 Req combo points on target
#define SPELL_ATTR_EX_UNK21                       0x00200000            // 21
#define SPELL_ATTR_EX_REQ_COMBO_POINTS2           0x00400000            // 22 Req combo points on target
#define SPELL_ATTR_EX_UNK23                       0x00800000            // 23
#define SPELL_ATTR_EX_UNK24                       0x01000000            // 24 Req fishing pole??
#define SPELL_ATTR_EX_UNK25                       0x02000000            // 25
#define SPELL_ATTR_EX_UNK26                       0x04000000            // 26
#define SPELL_ATTR_EX_UNK27                       0x08000000            // 27
#define SPELL_ATTR_EX_UNK28                       0x10000000            // 28
#define SPELL_ATTR_EX_UNK29                       0x20000000            // 29
#define SPELL_ATTR_EX_UNK30                       0x40000000            // 30 overpower
#define SPELL_ATTR_EX_UNK31                       0x80000000            // 31

#define SPELL_ATTR_EX2_UNK0                       0x00000001            // 0
#define SPELL_ATTR_EX2_UNK1                       0x00000002            // 1
#define SPELL_ATTR_EX2_CANT_REFLECTED             0x00000004            // 2 ? used for detect can or not spell reflected
#define SPELL_ATTR_EX2_UNK3                       0x00000008            // 3
#define SPELL_ATTR_EX2_UNK4                       0x00000010            // 4
#define SPELL_ATTR_EX2_AUTOREPEAT_FLAG            0x00000020            // 5
#define SPELL_ATTR_EX2_UNK6                       0x00000040            // 6
#define SPELL_ATTR_EX2_UNK7                       0x00000080            // 7
#define SPELL_ATTR_EX2_UNK8                       0x00000100            // 8 not set in 3.0.3
#define SPELL_ATTR_EX2_UNK9                       0x00000200            // 9
#define SPELL_ATTR_EX2_UNK10                      0x00000400            // 10
#define SPELL_ATTR_EX2_HEALTH_FUNNEL              0x00000800            // 11
#define SPELL_ATTR_EX2_UNK12                      0x00001000            // 12
#define SPELL_ATTR_EX2_UNK13                      0x00002000            // 13
#define SPELL_ATTR_EX2_UNK14                      0x00004000            // 14
#define SPELL_ATTR_EX2_UNK15                      0x00008000            // 15 not set in 3.0.3
#define SPELL_ATTR_EX2_UNK16                      0x00010000            // 16
#define SPELL_ATTR_EX2_UNK17                      0x00020000            // 17 Hunters Shot and Stings only have this flag
#define SPELL_ATTR_EX2_UNK18                      0x00040000            // 18 Only Revive pet - possible req dead pet
#define SPELL_ATTR_EX2_NOT_NEED_SHAPESHIFT        0x00080000            // 19 does not necessarly need shapeshift
#define SPELL_ATTR_EX2_UNK20                      0x00100000            // 20
#define SPELL_ATTR_EX2_DAMAGE_REDUCED_SHIELD      0x00200000            // 21 for ice blocks, pala immunity buffs, priest absorb shields, but used also for other spells -> not sure!
#define SPELL_ATTR_EX2_UNK22                      0x00400000            // 22
#define SPELL_ATTR_EX2_UNK23                      0x00800000            // 23 Only mage Arcane Concentration have this flag
#define SPELL_ATTR_EX2_UNK24                      0x01000000            // 24
#define SPELL_ATTR_EX2_UNK25                      0x02000000            // 25
#define SPELL_ATTR_EX2_UNK26                      0x04000000            // 26 unaffected by school immunity
#define SPELL_ATTR_EX2_UNK27                      0x08000000            // 27
#define SPELL_ATTR_EX2_UNK28                      0x10000000            // 28 no breaks stealth if it fails??
#define SPELL_ATTR_EX2_CANT_CRIT                  0x20000000            // 29 Spell can't crit
#define SPELL_ATTR_EX2_UNK30                      0x40000000            // 30
#define SPELL_ATTR_EX2_FOOD_BUFF                  0x80000000            // 31 Food or Drink Buff (like Well Fed)

#define SPELL_ATTR_EX3_UNK0                       0x00000001            // 0
#define SPELL_ATTR_EX3_UNK1                       0x00000002            // 1
#define SPELL_ATTR_EX3_UNK2                       0x00000004            // 2
#define SPELL_ATTR_EX3_UNK3                       0x00000008            // 3
#define SPELL_ATTR_EX3_UNK4                       0x00000010            // 4 Druid Rebirth only this spell have this flag
#define SPELL_ATTR_EX3_UNK5                       0x00000020            // 5
#define SPELL_ATTR_EX3_UNK6                       0x00000040            // 6
#define SPELL_ATTR_EX3_UNK7                       0x00000080            // 7
#define SPELL_ATTR_EX3_UNK8                       0x00000100            // 8
#define SPELL_ATTR_EX3_UNK9                       0x00000200            // 9
#define SPELL_ATTR_EX3_MAIN_HAND                  0x00000400            // 10 Main hand weapon required
#define SPELL_ATTR_EX3_BATTLEGROUND               0x00000800            // 11 Can casted only on battleground
#define SPELL_ATTR_EX3_CAST_ON_DEAD               0x00001000            // 12 target is a dead player (not every spell has this flag)
#define SPELL_ATTR_EX3_UNK13                      0x00002000            // 13
#define SPELL_ATTR_EX3_UNK14                      0x00004000            // 14 "Honorless Target" only this spells have this flag
#define SPELL_ATTR_EX3_UNK15                      0x00008000            // 15 Auto Shoot, Shoot, Throw,  - this is autoshot flag
#define SPELL_ATTR_EX3_UNK16                      0x00010000            // 16 no triggers effects that trigger on casting a spell??
#define SPELL_ATTR_EX3_UNK17                      0x00020000            // 17 no triggers effects that trigger on casting a spell??
#define SPELL_ATTR_EX3_UNK18                      0x00040000            // 18
#define SPELL_ATTR_EX3_UNK19                      0x00080000            // 19
#define SPELL_ATTR_EX3_DEATH_PERSISTENT           0x00100000            // 20 Death persistent spells
#define SPELL_ATTR_EX3_UNK21                      0x00200000            // 21
#define SPELL_ATTR_EX3_REQ_WAND                   0x00400000            // 22 Req wand
#define SPELL_ATTR_EX3_UNK23                      0x00800000            // 23
#define SPELL_ATTR_EX3_REQ_OFFHAND                0x01000000            // 24 Req offhand weapon
#define SPELL_ATTR_EX3_UNK25                      0x02000000            // 25 no cause spell pushback ?
#define SPELL_ATTR_EX3_UNK26                      0x04000000            // 26
#define SPELL_ATTR_EX3_UNK27                      0x08000000            // 27
#define SPELL_ATTR_EX3_UNK28                      0x10000000            // 28
#define SPELL_ATTR_EX3_UNK29                      0x20000000            // 29
#define SPELL_ATTR_EX3_UNK30                      0x40000000            // 30
#define SPELL_ATTR_EX3_UNK31                      0x80000000            // 31

#define SPELL_ATTR_EX4_UNK0                       0x00000001            // 0
#define SPELL_ATTR_EX4_UNK1                       0x00000002            // 1 proc on finishing move?
#define SPELL_ATTR_EX4_UNK2                       0x00000004            // 2
#define SPELL_ATTR_EX4_UNK3                       0x00000008            // 3
#define SPELL_ATTR_EX4_UNK4                       0x00000010            // 4 This will no longer cause guards to attack on use??
#define SPELL_ATTR_EX4_UNK5                       0x00000020            // 5
#define SPELL_ATTR_EX4_NOT_STEALABLE              0x00000040            // 6 although such auras might be dispellable, they cannot be stolen
#define SPELL_ATTR_EX4_UNK7                       0x00000080            // 7
#define SPELL_ATTR_EX4_STACK_DOT_MODIFIER         0x00000100            // 8 no effect on non DoTs?
#define SPELL_ATTR_EX4_UNK9                       0x00000200            // 9
#define SPELL_ATTR_EX4_SPELL_VS_EXTEND_COST       0x00000400            // 10 Rogue Shiv have this flag
#define SPELL_ATTR_EX4_UNK11                      0x00000800            // 11
#define SPELL_ATTR_EX4_UNK12                      0x00001000            // 12
#define SPELL_ATTR_EX4_UNK13                      0x00002000            // 13
#define SPELL_ATTR_EX4_UNK14                      0x00004000            // 14
#define SPELL_ATTR_EX4_UNK15                      0x00008000            // 15
#define SPELL_ATTR_EX4_NOT_USABLE_IN_ARENA        0x00010000            // 16 not usable in arena
#define SPELL_ATTR_EX4_USABLE_IN_ARENA            0x00020000            // 17 usable in arena
#define SPELL_ATTR_EX4_UNK18                      0x00040000            // 18
#define SPELL_ATTR_EX4_UNK19                      0x00080000            // 19
#define SPELL_ATTR_EX4_UNK20                      0x00100000            // 20
#define SPELL_ATTR_EX4_UNK21                      0x00200000            // 21
#define SPELL_ATTR_EX4_UNK22                      0x00400000            // 22
#define SPELL_ATTR_EX4_UNK23                      0x00800000            // 23
#define SPELL_ATTR_EX4_UNK24                      0x01000000            // 24
#define SPELL_ATTR_EX4_UNK25                      0x02000000            // 25 pet scaling auras
#define SPELL_ATTR_EX4_CAST_ONLY_IN_OUTLAND       0x04000000            // 26 Can only be used in Outland.
#define SPELL_ATTR_EX4_UNK27                      0x08000000            // 27
#define SPELL_ATTR_EX4_UNK28                      0x10000000            // 28
#define SPELL_ATTR_EX4_UNK29                      0x20000000            // 29
#define SPELL_ATTR_EX4_UNK30                      0x40000000            // 30
#define SPELL_ATTR_EX4_UNK31                      0x80000000            // 31

#define SPELL_ATTR_EX5_UNK0                       0x00000001            // 0
#define SPELL_ATTR_EX5_NO_REAGENT_WHILE_PREP      0x00000002            // 1 not need reagents if UNIT_FLAG_PREPARATION
#define SPELL_ATTR_EX5_UNK2                       0x00000004            // 2
#define SPELL_ATTR_EX5_USABLE_WHILE_STUNNED       0x00000008            // 3 usable while stunned
#define SPELL_ATTR_EX5_UNK4                       0x00000010            // 4
#define SPELL_ATTR_EX5_SINGLE_TARGET_SPELL        0x00000020            // 5 Only one target can be apply at a time
#define SPELL_ATTR_EX5_UNK6                       0x00000040            // 6
#define SPELL_ATTR_EX5_UNK7                       0x00000080            // 7
#define SPELL_ATTR_EX5_UNK8                       0x00000100            // 8
#define SPELL_ATTR_EX5_START_PERIODIC_AT_APPLY    0x00000200            // 9  begin periodic tick at aura apply
#define SPELL_ATTR_EX5_UNK10                      0x00000400            // 10
#define SPELL_ATTR_EX5_UNK11                      0x00000800            // 11
#define SPELL_ATTR_EX5_UNK12                      0x00001000            // 12
#define SPELL_ATTR_EX5_UNK13                      0x00002000            // 13
#define SPELL_ATTR_EX5_UNK14                      0x00004000            // 14
#define SPELL_ATTR_EX5_UNK15                      0x00008000            // 15
#define SPELL_ATTR_EX5_UNK16                      0x00010000            // 16
#define SPELL_ATTR_EX5_USABLE_WHILE_FEARED        0x00020000            // 17 usable while feared
#define SPELL_ATTR_EX5_USABLE_WHILE_CONFUSED      0x00040000            // 18 usable while confused
#define SPELL_ATTR_EX5_UNK19                      0x00080000            // 19
#define SPELL_ATTR_EX5_UNK20                      0x00100000            // 20
#define SPELL_ATTR_EX5_UNK21                      0x00200000            // 21
#define SPELL_ATTR_EX5_UNK22                      0x00400000            // 22
#define SPELL_ATTR_EX5_UNK23                      0x00800000            // 23
#define SPELL_ATTR_EX5_UNK24                      0x01000000            // 24
#define SPELL_ATTR_EX5_UNK25                      0x02000000            // 25
#define SPELL_ATTR_EX5_UNK26                      0x04000000            // 26
#define SPELL_ATTR_EX5_UNK27                      0x08000000            // 27
#define SPELL_ATTR_EX5_UNK28                      0x10000000            // 28
#define SPELL_ATTR_EX5_UNK29                      0x20000000            // 29
#define SPELL_ATTR_EX5_UNK30                      0x40000000            // 30
#define SPELL_ATTR_EX5_UNK31                      0x80000000            // 31 Forces all nearby enemies to focus attacks caster

#define SPELL_ATTR_EX6_UNK0                       0x00000001            // 0 Only Move spell have this flag
#define SPELL_ATTR_EX6_ONLY_IN_ARENA              0x00000002            // 1 only usable in arena, not used in 3.2.0a and early
#define SPELL_ATTR_EX6_UNK2                       0x00000004            // 2
#define SPELL_ATTR_EX6_UNK3                       0x00000008            // 3
#define SPELL_ATTR_EX6_UNK4                       0x00000010            // 4
#define SPELL_ATTR_EX6_UNK5                       0x00000020            // 5
#define SPELL_ATTR_EX6_UNK6                       0x00000040            // 6
#define SPELL_ATTR_EX6_UNK7                       0x00000080            // 7
#define SPELL_ATTR_EX6_UNK8                       0x00000100            // 8
#define SPELL_ATTR_EX6_UNK9                       0x00000200            // 9
#define SPELL_ATTR_EX6_UNK10                      0x00000400            // 10
#define SPELL_ATTR_EX6_NOT_IN_RAID_INSTANCE       0x00000800            // 11 not usable in raid instance
#define SPELL_ATTR_EX6_UNK12                      0x00001000            // 12
#define SPELL_ATTR_EX6_UNK13                      0x00002000            // 13
#define SPELL_ATTR_EX6_UNK14                      0x00004000            // 14
#define SPELL_ATTR_EX6_UNK15                      0x00008000            // 15 not set in 3.0.3
#define SPELL_ATTR_EX6_UNK16                      0x00010000            // 16
#define SPELL_ATTR_EX6_UNK17                      0x00020000            // 17
#define SPELL_ATTR_EX6_UNK18                      0x00040000            // 18
#define SPELL_ATTR_EX6_UNK19                      0x00080000            // 19
#define SPELL_ATTR_EX6_UNK20                      0x00100000            // 20
#define SPELL_ATTR_EX6_UNK21                      0x00200000            // 21
#define SPELL_ATTR_EX6_UNK22                      0x00400000            // 22
#define SPELL_ATTR_EX6_UNK23                      0x00800000            // 23 not set in 3.0.3
#define SPELL_ATTR_EX6_UNK24                      0x01000000            // 24 not set in 3.0.3
#define SPELL_ATTR_EX6_UNK25                      0x02000000            // 25 not set in 3.0.3
#define SPELL_ATTR_EX6_UNK26                      0x04000000            // 26 not set in 3.0.3
#define SPELL_ATTR_EX6_UNK27                      0x08000000            // 27 not set in 3.0.3
#define SPELL_ATTR_EX6_UNK28                      0x10000000            // 28 not set in 3.0.3
#define SPELL_ATTR_EX6_NO_DMG_PERCENT_MODS        0x20000000            // 29 do not apply damage percent mods (usually in cases where it has already been applied)
#define SPELL_ATTR_EX6_UNK30                      0x40000000            // 30 not set in 3.0.3
#define SPELL_ATTR_EX6_UNK31                      0x80000000            // 31 not set in 3.0.3

#define MAX_TALENT_SPEC_COUNT   2
#define MAX_GLYPH_SLOT_INDEX    6

enum SheathTypes
{
    SHEATHETYPE_NONE                   = 0,
    SHEATHETYPE_MAINHAND               = 1,
    SHEATHETYPE_OFFHAND                = 2,
    SHEATHETYPE_LARGEWEAPONLEFT        = 3,
    SHEATHETYPE_LARGEWEAPONRIGHT       = 4,
    SHEATHETYPE_HIPWEAPONLEFT          = 5,
    SHEATHETYPE_HIPWEAPONRIGHT         = 6,
    SHEATHETYPE_SHIELD                 = 7
};

#define MAX_SHEATHETYPE                  8

enum CharacterSlot
{
    SLOT_HEAD                          = 0,
    SLOT_NECK                          = 1,
    SLOT_SHOULDERS                     = 2,
    SLOT_SHIRT                         = 3,
    SLOT_CHEST                         = 4,
    SLOT_WAIST                         = 5,
    SLOT_LEGS                          = 6,
    SLOT_FEET                          = 7,
    SLOT_WRISTS                        = 8,
    SLOT_HANDS                         = 9,
    SLOT_FINGER1                       = 10,
    SLOT_FINGER2                       = 11,
    SLOT_TRINKET1                      = 12,
    SLOT_TRINKET2                      = 13,
    SLOT_BACK                          = 14,
    SLOT_MAIN_HAND                     = 15,
    SLOT_OFF_HAND                      = 16,
    SLOT_RANGED                        = 17,
    SLOT_TABARD                        = 18,
    SLOT_EMPTY                         = 19
};

enum Language
{
    LANG_UNIVERSAL      = 0,
    LANG_ORCISH         = 1,
    LANG_DARNASSIAN     = 2,
    LANG_TAURAHE        = 3,
    LANG_DWARVISH       = 6,
    LANG_COMMON         = 7,
    LANG_DEMONIC        = 8,
    LANG_TITAN          = 9,
    LANG_THALASSIAN     = 10,
    LANG_DRACONIC       = 11,
    LANG_KALIMAG        = 12,
    LANG_GNOMISH        = 13,
    LANG_TROLL          = 14,
    LANG_GUTTERSPEAK    = 33,
    LANG_DRAENEI        = 35,
    LANG_ZOMBIE         = 36,
    LANG_GNOMISH_BINARY = 37,
    LANG_GOBLIN_BINARY  = 38,
    LANG_ADDON          = 0xFFFFFFFF                        // used by addons, in 2.4.0 not exit, replaced by messagetype?
};

#define LANGUAGES_COUNT   19

enum Team
{
    HORDE               = 67,
    ALLIANCE            = 469,
    //TEAM_STEAMWHEEDLE_CARTEL = 169,                       // not used in code
    //TEAM_ALLIANCE_FORCES     = 891,
    //TEAM_HORDE_FORCES        = 892,
    //TEAM_SANCTUARY           = 936,
    //TEAM_OUTLAND             = 980,
    //TEAM_OTHER               = 0,                         // if ReputationListId > 0 && Flags != FACTION_FLAG_TEAM_HEADER
};

enum SpellEffects
{
    SPELL_EFFECT_INSTAKILL                 = 1,
    SPELL_EFFECT_SCHOOL_DAMAGE             = 2,
    SPELL_EFFECT_DUMMY                     = 3,
    SPELL_EFFECT_PORTAL_TELEPORT           = 4,
    SPELL_EFFECT_TELEPORT_UNITS            = 5,
    SPELL_EFFECT_APPLY_AURA                = 6,
    SPELL_EFFECT_ENVIRONMENTAL_DAMAGE      = 7,
    SPELL_EFFECT_POWER_DRAIN               = 8,
    SPELL_EFFECT_HEALTH_LEECH              = 9,
    SPELL_EFFECT_HEAL                      = 10,
    SPELL_EFFECT_BIND                      = 11,
    SPELL_EFFECT_PORTAL                    = 12,
    SPELL_EFFECT_RITUAL_BASE               = 13,
    SPELL_EFFECT_RITUAL_SPECIALIZE         = 14,
    SPELL_EFFECT_RITUAL_ACTIVATE_PORTAL    = 15,
    SPELL_EFFECT_QUEST_COMPLETE            = 16,
    SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL    = 17,
    SPELL_EFFECT_RESURRECT                 = 18,
    SPELL_EFFECT_ADD_EXTRA_ATTACKS         = 19,
    SPELL_EFFECT_DODGE                     = 20,
    SPELL_EFFECT_EVADE                     = 21,
    SPELL_EFFECT_PARRY                     = 22,
    SPELL_EFFECT_BLOCK                     = 23,
    SPELL_EFFECT_CREATE_ITEM               = 24,
    SPELL_EFFECT_WEAPON                    = 25,
    SPELL_EFFECT_DEFENSE                   = 26,
    SPELL_EFFECT_PERSISTENT_AREA_AURA      = 27,
    SPELL_EFFECT_SUMMON                    = 28,
    SPELL_EFFECT_LEAP                      = 29,
    SPELL_EFFECT_ENERGIZE                  = 30,
    SPELL_EFFECT_WEAPON_PERCENT_DAMAGE     = 31,
    SPELL_EFFECT_TRIGGER_MISSILE           = 32,
    SPELL_EFFECT_OPEN_LOCK                 = 33,
    SPELL_EFFECT_SUMMON_CHANGE_ITEM        = 34,
    SPELL_EFFECT_APPLY_AREA_AURA_PARTY     = 35,
    SPELL_EFFECT_LEARN_SPELL               = 36,
    SPELL_EFFECT_SPELL_DEFENSE             = 37,
    SPELL_EFFECT_DISPEL                    = 38,
    SPELL_EFFECT_LANGUAGE                  = 39,
    SPELL_EFFECT_DUAL_WIELD                = 40,
    SPELL_EFFECT_JUMP                      = 41,
    SPELL_EFFECT_JUMP2                     = 42,
    SPELL_EFFECT_TELEPORT_UNITS_FACE_CASTER= 43,
    SPELL_EFFECT_SKILL_STEP                = 44,
    SPELL_EFFECT_ADD_HONOR                 = 45,
    SPELL_EFFECT_SPAWN                     = 46,
    SPELL_EFFECT_TRADE_SKILL               = 47,
    SPELL_EFFECT_STEALTH                   = 48,
    SPELL_EFFECT_DETECT                    = 49,
    SPELL_EFFECT_TRANS_DOOR                = 50,
    SPELL_EFFECT_FORCE_CRITICAL_HIT        = 51,
    SPELL_EFFECT_GUARANTEE_HIT             = 52,
    SPELL_EFFECT_ENCHANT_ITEM              = 53,
    SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY    = 54,
    SPELL_EFFECT_TAMECREATURE              = 55,
    SPELL_EFFECT_SUMMON_PET                = 56,
    SPELL_EFFECT_LEARN_PET_SPELL           = 57,
    SPELL_EFFECT_WEAPON_DAMAGE             = 58,
    SPELL_EFFECT_CREATE_RANDOM_ITEM        = 59,
    SPELL_EFFECT_PROFICIENCY               = 60,
    SPELL_EFFECT_SEND_EVENT                = 61,
    SPELL_EFFECT_POWER_BURN                = 62,
    SPELL_EFFECT_THREAT                    = 63,
    SPELL_EFFECT_TRIGGER_SPELL             = 64,
    SPELL_EFFECT_APPLY_AREA_AURA_RAID      = 65,
    SPELL_EFFECT_RESTORE_ITEM_CHARGES      = 66,
    SPELL_EFFECT_HEAL_MAX_HEALTH           = 67,
    SPELL_EFFECT_INTERRUPT_CAST            = 68,
    SPELL_EFFECT_DISTRACT                  = 69,
    SPELL_EFFECT_PULL                      = 70,
    SPELL_EFFECT_PICKPOCKET                = 71,
    SPELL_EFFECT_ADD_FARSIGHT              = 72,
    SPELL_EFFECT_UNTRAIN_TALENTS           = 73,
    SPELL_EFFECT_APPLY_GLYPH               = 74,
    SPELL_EFFECT_HEAL_MECHANICAL           = 75,
    SPELL_EFFECT_SUMMON_OBJECT_WILD        = 76,
    SPELL_EFFECT_SCRIPT_EFFECT             = 77,
    SPELL_EFFECT_ATTACK                    = 78,
    SPELL_EFFECT_SANCTUARY                 = 79,
    SPELL_EFFECT_ADD_COMBO_POINTS          = 80,
    SPELL_EFFECT_CREATE_HOUSE              = 81,
    SPELL_EFFECT_BIND_SIGHT                = 82,
    SPELL_EFFECT_DUEL                      = 83,
    SPELL_EFFECT_STUCK                     = 84,
    SPELL_EFFECT_SUMMON_PLAYER             = 85,
    SPELL_EFFECT_ACTIVATE_OBJECT           = 86,
    SPELL_EFFECT_WMO_DAMAGE                = 87,
    SPELL_EFFECT_WMO_REPAIR                = 88,
    SPELL_EFFECT_WMO_CHANGE                = 89,
    SPELL_EFFECT_KILL_CREDIT               = 90,
    SPELL_EFFECT_THREAT_ALL                = 91,
    SPELL_EFFECT_ENCHANT_HELD_ITEM         = 92,
    SPELL_EFFECT_93                        = 93,            // old SPELL_EFFECT_SUMMON_PHANTASM
    SPELL_EFFECT_SELF_RESURRECT            = 94,
    SPELL_EFFECT_SKINNING                  = 95,
    SPELL_EFFECT_CHARGE                    = 96,
    SPELL_EFFECT_SUMMON_ALL_TOTEMS         = 97,
    SPELL_EFFECT_KNOCK_BACK                = 98,
    SPELL_EFFECT_DISENCHANT                = 99,
    SPELL_EFFECT_INEBRIATE                 = 100,
    SPELL_EFFECT_FEED_PET                  = 101,
    SPELL_EFFECT_DISMISS_PET               = 102,
    SPELL_EFFECT_REPUTATION                = 103,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT1       = 104,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT2       = 105,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT3       = 106,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT4       = 107,
    SPELL_EFFECT_DISPEL_MECHANIC           = 108,
    SPELL_EFFECT_SUMMON_DEAD_PET           = 109,
    SPELL_EFFECT_DESTROY_ALL_TOTEMS        = 110,
    SPELL_EFFECT_DURABILITY_DAMAGE         = 111,
    SPELL_EFFECT_112                       = 112,           // old SPELL_EFFECT_SUMMON_DEMON
    SPELL_EFFECT_RESURRECT_NEW             = 113,
    SPELL_EFFECT_ATTACK_ME                 = 114,
    SPELL_EFFECT_DURABILITY_DAMAGE_PCT     = 115,
    SPELL_EFFECT_SKIN_PLAYER_CORPSE        = 116,
    SPELL_EFFECT_SPIRIT_HEAL               = 117,
    SPELL_EFFECT_SKILL                     = 118,
    SPELL_EFFECT_APPLY_AREA_AURA_PET       = 119,
    SPELL_EFFECT_TELEPORT_GRAVEYARD        = 120,
    SPELL_EFFECT_NORMALIZED_WEAPON_DMG     = 121,
    SPELL_EFFECT_122                       = 122,
    SPELL_EFFECT_SEND_TAXI                 = 123,
    SPELL_EFFECT_PLAYER_PULL               = 124,
    SPELL_EFFECT_MODIFY_THREAT_PERCENT     = 125,
    SPELL_EFFECT_STEAL_BENEFICIAL_BUFF     = 126,
    SPELL_EFFECT_PROSPECTING               = 127,
    SPELL_EFFECT_APPLY_AREA_AURA_FRIEND    = 128,
    SPELL_EFFECT_APPLY_AREA_AURA_ENEMY     = 129,
    SPELL_EFFECT_REDIRECT_THREAT           = 130,
    SPELL_EFFECT_131                       = 131,
    SPELL_EFFECT_PLAY_MUSIC                = 132,
    SPELL_EFFECT_UNLEARN_SPECIALIZATION    = 133,
    SPELL_EFFECT_KILL_CREDIT2              = 134,
    SPELL_EFFECT_CALL_PET                  = 135,
    SPELL_EFFECT_HEAL_PCT                  = 136,
    SPELL_EFFECT_ENERGIZE_PCT              = 137,
    SPELL_EFFECT_LEAP_BACK                 = 138,
    SPELL_EFFECT_CLEAR_QUEST               = 139,
    SPELL_EFFECT_FORCE_CAST                = 140,
    SPELL_EFFECT_141                       = 141,
    SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE  = 142,
    SPELL_EFFECT_APPLY_AREA_AURA_OWNER     = 143,
    SPELL_EFFECT_144                       = 144,
    SPELL_EFFECT_145                       = 145,
    SPELL_EFFECT_ACTIVATE_RUNE             = 146,
    SPELL_EFFECT_QUEST_FAIL                = 147,
    SPELL_EFFECT_148                       = 148,
    SPELL_EFFECT_149                       = 149,
    SPELL_EFFECT_150                       = 150,
    SPELL_EFFECT_TRIGGER_SPELL_2           = 151,
    SPELL_EFFECT_152                       = 152,
    SPELL_EFFECT_153                       = 153,
    SPELL_EFFECT_TEACH_TAXI_NODE           = 154,
    SPELL_EFFECT_TITAN_GRIP                = 155,
    SPELL_EFFECT_ENCHANT_ITEM_PRISMATIC    = 156,
    SPELL_EFFECT_CREATE_ITEM_2             = 157,
    SPELL_EFFECT_MILLING                   = 158,
    SPELL_EFFECT_ALLOW_RENAME_PET          = 159,
    SPELL_EFFECT_160                       = 160,
    SPELL_EFFECT_TALENT_SPEC_COUNT         = 161,
    SPELL_EFFECT_TALENT_SPEC_SELECT        = 162,
    TOTAL_SPELL_EFFECTS                    = 163
};

enum SpellCastResult
{
    SPELL_FAILED_SUCCESS = 0,
    SPELL_FAILED_AFFECTING_COMBAT = 1,
    SPELL_FAILED_ALREADY_AT_FULL_HEALTH = 2,
    SPELL_FAILED_ALREADY_AT_FULL_MANA = 3,
    SPELL_FAILED_ALREADY_AT_FULL_POWER = 4,
    SPELL_FAILED_ALREADY_BEING_TAMED = 5,
    SPELL_FAILED_ALREADY_HAVE_CHARM = 6,
    SPELL_FAILED_ALREADY_HAVE_SUMMON = 7,
    SPELL_FAILED_ALREADY_OPEN = 8,
    SPELL_FAILED_AURA_BOUNCED = 9,
    SPELL_FAILED_AUTOTRACK_INTERRUPTED = 10,
    SPELL_FAILED_BAD_IMPLICIT_TARGETS = 11,
    SPELL_FAILED_BAD_TARGETS = 12,
    SPELL_FAILED_CANT_BE_CHARMED = 13,
    SPELL_FAILED_CANT_BE_DISENCHANTED = 14,
    SPELL_FAILED_CANT_BE_DISENCHANTED_SKILL = 15,
    SPELL_FAILED_CANT_BE_MILLED = 16,
    SPELL_FAILED_CANT_BE_PROSPECTED = 17,
    SPELL_FAILED_CANT_CAST_ON_TAPPED = 18,
    SPELL_FAILED_CANT_DUEL_WHILE_INVISIBLE = 19,
    SPELL_FAILED_CANT_DUEL_WHILE_STEALTHED = 20,
    SPELL_FAILED_CANT_STEALTH = 21,
    SPELL_FAILED_CASTER_AURASTATE = 22,
    SPELL_FAILED_CASTER_DEAD = 23,
    SPELL_FAILED_CHARMED = 24,
    SPELL_FAILED_CHEST_IN_USE = 25,
    SPELL_FAILED_CONFUSED = 26,
    SPELL_FAILED_DONT_REPORT = 27,
    SPELL_FAILED_EQUIPPED_ITEM = 28,
    SPELL_FAILED_EQUIPPED_ITEM_CLASS = 29,
    SPELL_FAILED_EQUIPPED_ITEM_CLASS_MAINHAND = 30,
    SPELL_FAILED_EQUIPPED_ITEM_CLASS_OFFHAND = 31,
    SPELL_FAILED_ERROR = 32,
    SPELL_FAILED_FIZZLE = 33,
    SPELL_FAILED_FLEEING = 34,
    SPELL_FAILED_FOOD_LOWLEVEL = 35,
    SPELL_FAILED_HIGHLEVEL = 36,
    SPELL_FAILED_HUNGER_SATIATED = 37,
    SPELL_FAILED_IMMUNE = 38,
    SPELL_FAILED_INCORRECT_AREA = 39,
    SPELL_FAILED_INTERRUPTED = 40,
    SPELL_FAILED_INTERRUPTED_COMBAT = 41,
    SPELL_FAILED_ITEM_ALREADY_ENCHANTED = 42,
    SPELL_FAILED_ITEM_GONE = 43,
    SPELL_FAILED_ITEM_NOT_FOUND = 44,
    SPELL_FAILED_ITEM_NOT_READY = 45,
    SPELL_FAILED_LEVEL_REQUIREMENT = 46,
    SPELL_FAILED_LINE_OF_SIGHT = 47,
    SPELL_FAILED_LOWLEVEL = 48,
    SPELL_FAILED_LOW_CASTLEVEL = 49,
    SPELL_FAILED_MAINHAND_EMPTY = 50,
    SPELL_FAILED_MOVING = 51,
    SPELL_FAILED_NEED_AMMO = 52,
    SPELL_FAILED_NEED_AMMO_POUCH = 53,
    SPELL_FAILED_NEED_EXOTIC_AMMO = 54,
    SPELL_FAILED_NEED_MORE_ITEMS = 55,
    SPELL_FAILED_NOPATH = 56,
    SPELL_FAILED_NOT_BEHIND = 57,
    SPELL_FAILED_NOT_FISHABLE = 58,
    SPELL_FAILED_NOT_FLYING = 59,
    SPELL_FAILED_NOT_HERE = 60,
    SPELL_FAILED_NOT_INFRONT = 61,
    SPELL_FAILED_NOT_IN_CONTROL = 62,
    SPELL_FAILED_NOT_KNOWN = 63,
    SPELL_FAILED_NOT_MOUNTED = 64,
    SPELL_FAILED_NOT_ON_TAXI = 65,
    SPELL_FAILED_NOT_ON_TRANSPORT = 66,
    SPELL_FAILED_NOT_READY = 67,
    SPELL_FAILED_NOT_SHAPESHIFT = 68,
    SPELL_FAILED_NOT_STANDING = 69,
    SPELL_FAILED_NOT_TRADEABLE = 70,
    SPELL_FAILED_NOT_TRADING = 71,
    SPELL_FAILED_NOT_UNSHEATHED = 72,
    SPELL_FAILED_NOT_WHILE_GHOST = 73,
    SPELL_FAILED_NOT_WHILE_LOOTING = 74,
    SPELL_FAILED_NO_AMMO = 75,
    SPELL_FAILED_NO_CHARGES_REMAIN = 76,
    SPELL_FAILED_NO_CHAMPION = 77,
    SPELL_FAILED_NO_COMBO_POINTS = 78,
    SPELL_FAILED_NO_DUELING = 79,
    SPELL_FAILED_NO_ENDURANCE = 80,
    SPELL_FAILED_NO_FISH = 81,
    SPELL_FAILED_NO_ITEMS_WHILE_SHAPESHIFTED = 82,
    SPELL_FAILED_NO_MOUNTS_ALLOWED = 83,
    SPELL_FAILED_NO_PET = 84,
    SPELL_FAILED_NO_POWER = 85,
    SPELL_FAILED_NOTHING_TO_DISPEL = 86,
    SPELL_FAILED_NOTHING_TO_STEAL = 87,
    SPELL_FAILED_ONLY_ABOVEWATER = 88,
    SPELL_FAILED_ONLY_DAYTIME = 89,
    SPELL_FAILED_ONLY_INDOORS = 90,
    SPELL_FAILED_ONLY_MOUNTED = 91,
    SPELL_FAILED_ONLY_NIGHTTIME = 92,
    SPELL_FAILED_ONLY_OUTDOORS = 93,
    SPELL_FAILED_ONLY_SHAPESHIFT = 94,
    SPELL_FAILED_ONLY_STEALTHED = 95,
    SPELL_FAILED_ONLY_UNDERWATER = 96,
    SPELL_FAILED_OUT_OF_RANGE = 97,
    SPELL_FAILED_PACIFIED = 98,
    SPELL_FAILED_POSSESSED = 99,
    SPELL_FAILED_REAGENTS = 100,
    SPELL_FAILED_REQUIRES_AREA = 101,
    SPELL_FAILED_REQUIRES_SPELL_FOCUS = 102,
    SPELL_FAILED_ROOTED = 103,
    SPELL_FAILED_SILENCED = 104,
    SPELL_FAILED_SPELL_IN_PROGRESS = 105,
    SPELL_FAILED_SPELL_LEARNED = 106,
    SPELL_FAILED_SPELL_UNAVAILABLE = 107,
    SPELL_FAILED_STUNNED = 108,
    SPELL_FAILED_TARGETS_DEAD = 109,
    SPELL_FAILED_TARGET_AFFECTING_COMBAT = 110,
    SPELL_FAILED_TARGET_AURASTATE = 111,
    SPELL_FAILED_TARGET_DUELING = 112,
    SPELL_FAILED_TARGET_ENEMY = 113,
    SPELL_FAILED_TARGET_ENRAGED = 114,
    SPELL_FAILED_TARGET_FRIENDLY = 115,
    SPELL_FAILED_TARGET_IN_COMBAT = 116,
    SPELL_FAILED_TARGET_IS_PLAYER = 117,
    SPELL_FAILED_TARGET_IS_PLAYER_CONTROLLED = 118,
    SPELL_FAILED_TARGET_NOT_DEAD = 119,
    SPELL_FAILED_TARGET_NOT_IN_PARTY = 120,
    SPELL_FAILED_TARGET_NOT_LOOTED = 121,
    SPELL_FAILED_TARGET_NOT_PLAYER = 122,
    SPELL_FAILED_TARGET_NO_POCKETS = 123,
    SPELL_FAILED_TARGET_NO_WEAPONS = 124,
    SPELL_FAILED_TARGET_NO_RANGED_WEAPONS = 125,
    SPELL_FAILED_TARGET_UNSKINNABLE = 126,
    SPELL_FAILED_THIRST_SATIATED = 127,
    SPELL_FAILED_TOO_CLOSE = 128,
    SPELL_FAILED_TOO_MANY_OF_ITEM = 129,
    SPELL_FAILED_TOTEM_CATEGORY = 130,
    SPELL_FAILED_TOTEMS = 131,
    SPELL_FAILED_TRY_AGAIN = 132,
    SPELL_FAILED_UNIT_NOT_BEHIND = 133,
    SPELL_FAILED_UNIT_NOT_INFRONT = 134,
    SPELL_FAILED_WRONG_PET_FOOD = 135,
    SPELL_FAILED_NOT_WHILE_FATIGUED = 136,
    SPELL_FAILED_TARGET_NOT_IN_INSTANCE = 137,
    SPELL_FAILED_NOT_WHILE_TRADING = 138,
    SPELL_FAILED_TARGET_NOT_IN_RAID = 139,
    SPELL_FAILED_TARGET_FREEFORALL = 140,
    SPELL_FAILED_NO_EDIBLE_CORPSES = 141,
    SPELL_FAILED_ONLY_BATTLEGROUNDS = 142,
    SPELL_FAILED_TARGET_NOT_GHOST = 143,
    SPELL_FAILED_TRANSFORM_UNUSABLE = 144,
    SPELL_FAILED_WRONG_WEATHER = 145,
    SPELL_FAILED_DAMAGE_IMMUNE = 146,
    SPELL_FAILED_PREVENTED_BY_MECHANIC = 147,
    SPELL_FAILED_PLAY_TIME = 148,
    SPELL_FAILED_REPUTATION = 149,
    SPELL_FAILED_MIN_SKILL = 150,
    SPELL_FAILED_NOT_IN_ARENA = 151,
    SPELL_FAILED_NOT_ON_SHAPESHIFT = 152,
    SPELL_FAILED_NOT_ON_STEALTHED = 153,
    SPELL_FAILED_NOT_ON_DAMAGE_IMMUNE = 154,
    SPELL_FAILED_NOT_ON_MOUNTED = 155,
    SPELL_FAILED_TOO_SHALLOW = 156,
    SPELL_FAILED_TARGET_NOT_IN_SANCTUARY = 157,
    SPELL_FAILED_TARGET_IS_TRIVIAL = 158,
    SPELL_FAILED_BM_OR_INVISGOD = 159,
    SPELL_FAILED_EXPERT_RIDING_REQUIREMENT = 160,
    SPELL_FAILED_ARTISAN_RIDING_REQUIREMENT = 161,
    SPELL_FAILED_NOT_IDLE = 162,
    SPELL_FAILED_NOT_INACTIVE = 163,
    SPELL_FAILED_PARTIAL_PLAYTIME = 164,
    SPELL_FAILED_NO_PLAYTIME = 165,
    SPELL_FAILED_NOT_IN_BATTLEGROUND = 166,
    SPELL_FAILED_NOT_IN_RAID_INSTANCE = 167,
    SPELL_FAILED_ONLY_IN_ARENA = 168,
    SPELL_FAILED_TARGET_LOCKED_TO_RAID_INSTANCE = 169,
    SPELL_FAILED_ON_USE_ENCHANT = 170,
    SPELL_FAILED_NOT_ON_GROUND = 171,
    SPELL_FAILED_CUSTOM_ERROR = 172,
    SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW = 173,
    SPELL_FAILED_TOO_MANY_SOCKETS = 174,
    SPELL_FAILED_INVALID_GLYPH = 175,
    SPELL_FAILED_UNIQUE_GLYPH = 176,
    SPELL_FAILED_GLYPH_SOCKET_LOCKED = 177,
    SPELL_FAILED_NO_VALID_TARGETS = 178,
    SPELL_FAILED_ITEM_AT_MAX_CHARGES = 179,
    SPELL_FAILED_NOT_IN_BARBERSHOP = 180,
    SPELL_FAILED_FISHING_TOO_LOW = 181,
    SPELL_FAILED_ITEM_ENCHANT_TRADE_WINDOW = 182,
    SPELL_FAILED_SUMMON_PENDING = 183,
    SPELL_FAILED_MAX_SOCKETS = 184,
    SPELL_FAILED_PET_CAN_RENAME = 185,
    SPELL_FAILED_TARGET_CANNOT_BE_RESURRECTED = 186,
    SPELL_FAILED_UNKNOWN = 187,                             // actually doesn't exist in client

    SPELL_CAST_OK = 255                                     // custom value, don't must be send to client
};

// Spell aura states
enum AuraState
{   // (C) used in caster aura state     (T) used in target aura state
    // (c) used in caster aura state-not (t) used in target aura state-not
    AURA_STATE_DEFENSE                      = 1,            // C   |
    AURA_STATE_HEALTHLESS_20_PERCENT        = 2,            // CcT |
    AURA_STATE_BERSERKING                   = 3,            // C T |
    AURA_STATE_FROZEN                       = 4,            //  c t| frozen target
    AURA_STATE_JUDGEMENT                    = 5,            // C   |
    //AURA_STATE_UNKNOWN6                   = 6,            //     | not used
    AURA_STATE_HUNTER_PARRY                 = 7,            // C   |
    AURA_STATE_ROGUE_ATTACK_FROM_STEALTH    = 7,            // C   | FIX ME: not implemented yet!
    //AURA_STATE_UNKNOWN7                   = 7,            //  c  | random/focused bursts spells (?)
    //AURA_STATE_UNKNOWN8                   = 8,            //     | not used
    //AURA_STATE_UNKNOWN9                   = 9,            //     | not used
    AURA_STATE_WARRIOR_VICTORY_RUSH         = 10,           // C   | warrior victory rush
    //AURA_STATE_UNKNOWN11                  = 11,           //    t|
    AURA_STATE_FAERIE_FIRE                  = 12,           //  c t|
    AURA_STATE_HEALTHLESS_35_PERCENT        = 13,           // C T |
    AURA_STATE_CONFLAGRATE                  = 14,           //   T | per-caster
    AURA_STATE_SWIFTMEND                    = 15,           //   T |
    AURA_STATE_DEADLY_POISON                = 16,           //   T |
    AURA_STATE_ENRAGE                       = 17,           // C   |
    //AURA_STATE_UNKNOWN18                  = 18,           // C  t|
    //AURA_STATE_UNKNOWN19                  = 19,           //     | not used
    //AURA_STATE_UNKNOWN20                  = 20,           //  c  | only (45317 Suicide)
    //AURA_STATE_UNKNOWN21                  = 21,           //     | not used
    //AURA_STATE_UNKNOWN22                  = 22,           // C   | not implemented yet (Requires Evasive Charges to use)
    AURA_STATE_HEALTH_ABOVE_75_PERCENT      = 23,           // C   |
};

// Spell mechanics
enum Mechanics
{
    MECHANIC_NONE             = 0,
    MECHANIC_CHARM            = 1,
    MECHANIC_DISORIENTED      = 2,
    MECHANIC_DISARM           = 3,
    MECHANIC_DISTRACT         = 4,
    MECHANIC_FEAR             = 5,
    MECHANIC_GRIP             = 6,
    MECHANIC_ROOT             = 7,
    MECHANIC_PACIFY           = 8,                          //0 spells use this mechanic
    MECHANIC_SILENCE          = 9,
    MECHANIC_SLEEP            = 10,
    MECHANIC_SNARE            = 11,
    MECHANIC_STUN             = 12,
    MECHANIC_FREEZE           = 13,
    MECHANIC_KNOCKOUT         = 14,
    MECHANIC_BLEED            = 15,
    MECHANIC_BANDAGE          = 16,
    MECHANIC_POLYMORPH        = 17,
    MECHANIC_BANISH           = 18,
    MECHANIC_SHIELD           = 19,
    MECHANIC_SHACKLE          = 20,
    MECHANIC_MOUNT            = 21,
    MECHANIC_INFECTED         = 22,
    MECHANIC_TURN             = 23,
    MECHANIC_HORROR           = 24,
    MECHANIC_INVULNERABILITY  = 25,
    MECHANIC_INTERRUPT        = 26,
    MECHANIC_DAZE             = 27,
    MECHANIC_DISCOVERY        = 28,
    MECHANIC_IMMUNE_SHIELD    = 29,                         // Divine (Blessing) Shield/Protection and Ice Block
    MECHANIC_SAPPED           = 30,
    MECHANIC_ENRAGED          = 31
};

// Used for spell 42292 Immune Movement Impairment and Loss of Control (0x49967da6)
#define IMMUNE_TO_MOVEMENT_IMPAIRMENT_AND_LOSS_CONTROL_MASK ( \
    (1<<(MECHANIC_CHARM   -1))|(1<<(MECHANIC_DISORIENTED-1))|(1<<(MECHANIC_FEAR  -1))| \
    (1<<(MECHANIC_ROOT    -1))|(1<<(MECHANIC_PACIFY     -1))|(1<<(MECHANIC_SLEEP -1))| \
    (1<<(MECHANIC_SNARE   -1))|(1<<(MECHANIC_STUN       -1))|(1<<(MECHANIC_FREEZE-1))| \
    (1<<(MECHANIC_KNOCKOUT-1))|(1<<(MECHANIC_POLYMORPH  -1))|(1<<(MECHANIC_BANISH-1))| \
    (1<<(MECHANIC_SHACKLE -1))|(1<<(MECHANIC_TURN       -1))|(1<<(MECHANIC_HORROR-1))| \
    (1<<(MECHANIC_DAZE    -1))|(1<<(MECHANIC_SAPPED     -1)))

#define IMMUNE_TO_ROOT_AND_SNARE_MASK ( \
    (1<<(MECHANIC_ROOT-1))|(1<<(MECHANIC_SNARE-1)))

#define IMMUNE_TO_ROOT_AND_STUN_MASK ( \
    (1<<(MECHANIC_ROOT-1))|(1<<(MECHANIC_STUN-1)))

#define IMMUNE_TO_SILENCE_AND_STUN_AND_FEAR_MASK ( \
    (1<<(MECHANIC_SILENCE-1))|(1<<(MECHANIC_STUN-1))|(1<<(MECHANIC_FEAR-1)))

#define IMMUNE_TO_INTERRUPT_AND_SILENCE_MASK ( \
    (1<<(MECHANIC_INTERRUPT-1))|(1<<(MECHANIC_SILENCE-1)))

// Daze and all croud control spells except polymorph are not removed
#define MECHANIC_NOT_REMOVED_BY_SHAPESHIFT ( \
    (1<<(MECHANIC_CHARM -1))|(1<<(MECHANIC_DISORIENTED-1))|(1<<(MECHANIC_FEAR  -1))| \
    (1<<(MECHANIC_PACIFY-1))|(1<<(MECHANIC_STUN       -1))|(1<<(MECHANIC_FREEZE-1))| \
    (1<<(MECHANIC_BANISH-1))|(1<<(MECHANIC_SHACKLE    -1))|(1<<(MECHANIC_HORROR-1))| \
    (1<<(MECHANIC_TURN  -1))|(1<<(MECHANIC_DAZE       -1))|(1<<(MECHANIC_SAPPED-1)))

// Spell dispell type
enum DispelType
{
    DISPEL_NONE         = 0,
    DISPEL_MAGIC        = 1,
    DISPEL_CURSE        = 2,
    DISPEL_DISEASE      = 3,
    DISPEL_POISON       = 4,
    DISPEL_STEALTH      = 5,
    DISPEL_INVISIBILITY = 6,
    DISPEL_ALL          = 7,
    DISPEL_SPE_NPC_ONLY = 8,
    DISPEL_ENRAGE       = 9,
    DISPEL_ZG_TICKET    = 10,
    DESPEL_OLD_UNUSED   = 11
};

#define DISPEL_ALL_MASK ( (1<<DISPEL_MAGIC) | (1<<DISPEL_CURSE) | (1<<DISPEL_DISEASE) | (1<<DISPEL_POISON) )

//To all Immune system,if target has immunes,
//some spell that related to ImmuneToDispel or ImmuneToSchool or ImmuneToDamage type can't cast to it,
//some spell_effects that related to ImmuneToEffect<effect>(only this effect in the spell) can't cast to it,
//some aura(related to Mechanics or ImmuneToState<aura>) can't apply to it.
enum SpellImmunity
{
    IMMUNITY_EFFECT                = 0,                     // enum SpellEffects
    IMMUNITY_STATE                 = 1,                     // enum AuraType
    IMMUNITY_SCHOOL                = 2,                     // enum SpellSchoolMask
    IMMUNITY_DAMAGE                = 3,                     // enum SpellSchoolMask
    IMMUNITY_DISPEL                = 4,                     // enum DispelType
    IMMUNITY_MECHANIC              = 5                      // enum Mechanics
};

#define MAX_SPELL_IMMUNITY           6

enum WeaponAttackType
{
    BASE_ATTACK   = 0,
    OFF_ATTACK    = 1,
    RANGED_ATTACK = 2
};

#define MAX_ATTACK  3

enum Targets
{
    TARGET_SELF                        = 1,
    TARGET_RANDOM_ENEMY_CHAIN_IN_AREA  = 2,                 // only one spell has that, but regardless, it's a target type after all
    TARGET_RANDOM_FRIEND_CHAIN_IN_AREA = 3,
    TARGET_PET                         = 5,
    TARGET_CHAIN_DAMAGE                = 6,
    TARGET_AREAEFFECT_INSTANT          = 7,                 // targets around provided destination point
    TARGET_AREAEFFECT_CUSTOM           = 8,
    TARGET_INNKEEPER_COORDINATES       = 9,                 // uses in teleport to innkeeper spells
    TARGET_ALL_ENEMY_IN_AREA           = 15,
    TARGET_ALL_ENEMY_IN_AREA_INSTANT   = 16,
    TARGET_TABLE_X_Y_Z_COORDINATES     = 17,                // uses in teleport spells and some other
    TARGET_EFFECT_SELECT               = 18,                // highly depends on the spell effect
    TARGET_ALL_PARTY_AROUND_CASTER     = 20,
    TARGET_SINGLE_FRIEND               = 21,
    TARGET_CASTER_COORDINATES          = 22,                // used only in TargetA, target selection dependent from TargetB
    TARGET_GAMEOBJECT                  = 23,
    TARGET_IN_FRONT_OF_CASTER          = 24,
    TARGET_DUELVSPLAYER                = 25,
    TARGET_GAMEOBJECT_ITEM             = 26,
    TARGET_MASTER                      = 27,
    TARGET_ALL_ENEMY_IN_AREA_CHANNELED = 28,
    TARGET_ALL_FRIENDLY_UNITS_AROUND_CASTER = 30,           // in TargetB used only with TARGET_ALL_AROUND_CASTER and in self casting range in TargetA
    TARGET_ALL_FRIENDLY_UNITS_IN_AREA  = 31,
    TARGET_MINION                      = 32,
    TARGET_ALL_PARTY                   = 33,
    TARGET_ALL_PARTY_AROUND_CASTER_2   = 34,                // used in Tranquility
    TARGET_SINGLE_PARTY                = 35,
    TARGET_ALL_HOSTILE_UNITS_AROUND_CASTER = 36,
    TARGET_AREAEFFECT_PARTY            = 37,
    TARGET_SCRIPT                      = 38,
    TARGET_SELF_FISHING                = 39,
    TARGET_FOCUS_OR_SCRIPTED_GAMEOBJECT= 40,
    TARGET_TOTEM_EARTH                 = 41,
    TARGET_TOTEM_WATER                 = 42,
    TARGET_TOTEM_AIR                   = 43,
    TARGET_TOTEM_FIRE                  = 44,
    TARGET_CHAIN_HEAL                  = 45,
    TARGET_SCRIPT_COORDINATES          = 46,
    TARGET_DYNAMIC_OBJECT_FRONT        = 47,
    TARGET_DYNAMIC_OBJECT_BEHIND       = 48,
    TARGET_DYNAMIC_OBJECT_LEFT_SIDE    = 49,
    TARGET_DYNAMIC_OBJECT_RIGHT_SIDE   = 50,
    TARGET_AREAEFFECT_CUSTOM_2         = 52,
    TARGET_CURRENT_ENEMY_COORDINATES   = 53,                // set unit coordinates as dest, only 16 target B imlemented
    TARGET_LARGE_FRONTAL_CONE          = 54,
    TARGET_ALL_RAID_AROUND_CASTER      = 56,
    TARGET_SINGLE_FRIEND_2             = 57,
    TARGET_NARROW_FRONTAL_CONE         = 60,
    TARGET_AREAEFFECT_PARTY_AND_CLASS  = 61,
    TARGET_DUELVSPLAYER_COORDINATES    = 63,
    TARGET_INFRONT_OF_VICTIM           = 64,
    TARGET_BEHIND_VICTIM               = 65,                // used in teleport behind spells, caster/target dependent from spell effect
    TARGET_RIGHT_FROM_VICTIM           = 66,
    TARGET_LEFT_FROM_VICTIM            = 67,
    TARGET_RANDOM_NEARBY_LOC           = 72,                // used in teleport onto nearby locations
    TARGET_RANDOM_CIRCUMFERENCE_POINT  = 73,
    TARGET_DYNAMIC_OBJECT_COORDINATES  = 76,
    TARGET_SINGLE_ENEMY                = 77,
    TARGET_POINT_AT_NORTH              = 78,                // 78-85 possible _COORDINATES at radius with pi/4 step around target in unknown order, N?
    TARGET_POINT_AT_SOUTH              = 79,                // S?
    TARGET_POINT_AT_EAST               = 80,                // 80/81 must be symmetric from line caster->target, E (base at 82/83, 84/85 order) ?
    TARGET_POINT_AT_WEST               = 81,                // 80/81 must be symmetric from line caster->target, W (base at 82/83, 84/85 order) ?
    TARGET_POINT_AT_NE                 = 82,                // from spell desc: "(NE)"
    TARGET_POINT_AT_NW                 = 83,                // from spell desc: "(NW)"
    TARGET_POINT_AT_SE                 = 84,                // from spell desc: "(SE)"
    TARGET_POINT_AT_SW                 = 85,                // from spell desc: "(SW)"
    TARGET_RANDOM_NEARBY_DEST          = 86,                // "Test Nearby Dest Random" - random around selected destination
    TARGET_SELF2                       = 87,
    TARGET_DIRECTLY_FORWARD            = 89,
    TARGET_NONCOMBAT_PET               = 90,
    TARGET_IN_FRONT_OF_CASTER_30       = 104,
};

enum SpellHitType
{
    SPELL_HIT_TYPE_UNK1 = 0x00001,
    SPELL_HIT_TYPE_CRIT = 0x00002,
    SPELL_HIT_TYPE_UNK3 = 0x00004,
    SPELL_HIT_TYPE_UNK4 = 0x00008,
    SPELL_HIT_TYPE_UNK5 = 0x00010,                          // replace caster?
    SPELL_HIT_TYPE_UNK6 = 0x00020
};

enum SpellDmgClass
{
    SPELL_DAMAGE_CLASS_NONE     = 0,
    SPELL_DAMAGE_CLASS_MAGIC    = 1,
    SPELL_DAMAGE_CLASS_MELEE    = 2,
    SPELL_DAMAGE_CLASS_RANGED   = 3
};

enum SpellPreventionType
{
    SPELL_PREVENTION_TYPE_NONE      = 0,
    SPELL_PREVENTION_TYPE_SILENCE   = 1,
    SPELL_PREVENTION_TYPE_PACIFY    = 2
};

enum GameobjectTypes
{
    GAMEOBJECT_TYPE_DOOR                   = 0,
    GAMEOBJECT_TYPE_BUTTON                 = 1,
    GAMEOBJECT_TYPE_QUESTGIVER             = 2,
    GAMEOBJECT_TYPE_CHEST                  = 3,
    GAMEOBJECT_TYPE_BINDER                 = 4,
    GAMEOBJECT_TYPE_GENERIC                = 5,
    GAMEOBJECT_TYPE_TRAP                   = 6,
    GAMEOBJECT_TYPE_CHAIR                  = 7,
    GAMEOBJECT_TYPE_SPELL_FOCUS            = 8,
    GAMEOBJECT_TYPE_TEXT                   = 9,
    GAMEOBJECT_TYPE_GOOBER                 = 10,
    GAMEOBJECT_TYPE_TRANSPORT              = 11,
    GAMEOBJECT_TYPE_AREADAMAGE             = 12,
    GAMEOBJECT_TYPE_CAMERA                 = 13,
    GAMEOBJECT_TYPE_MAP_OBJECT             = 14,
    GAMEOBJECT_TYPE_MO_TRANSPORT           = 15,
    GAMEOBJECT_TYPE_DUEL_ARBITER           = 16,
    GAMEOBJECT_TYPE_FISHINGNODE            = 17,
    GAMEOBJECT_TYPE_SUMMONING_RITUAL       = 18,
    GAMEOBJECT_TYPE_MAILBOX                = 19,
    GAMEOBJECT_TYPE_DO_NOT_USE             = 20,
    GAMEOBJECT_TYPE_GUARDPOST              = 21,
    GAMEOBJECT_TYPE_SPELLCASTER            = 22,
    GAMEOBJECT_TYPE_MEETINGSTONE           = 23,
    GAMEOBJECT_TYPE_FLAGSTAND              = 24,
    GAMEOBJECT_TYPE_FISHINGHOLE            = 25,
    GAMEOBJECT_TYPE_FLAGDROP               = 26,
    GAMEOBJECT_TYPE_MINI_GAME              = 27,
    GAMEOBJECT_TYPE_DO_NOT_USE_2           = 28,
    GAMEOBJECT_TYPE_CAPTURE_POINT          = 29,
    GAMEOBJECT_TYPE_AURA_GENERATOR         = 30,
    GAMEOBJECT_TYPE_DUNGEON_DIFFICULTY     = 31,
    GAMEOBJECT_TYPE_BARBER_CHAIR           = 32,
    GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING  = 33,
    GAMEOBJECT_TYPE_GUILD_BANK             = 34,
    GAMEOBJECT_TYPE_TRAPDOOR               = 35
};

#define MAX_GAMEOBJECT_TYPE                  36             // sending to client this or greater value can crash client.

#define GAMEOBJECT_FISHINGNODE_ENTRY        35591           // Better to define it somewhere instead of hardcoding everywhere

enum GameObjectFlags
{
    GO_FLAG_IN_USE          = 0x00000001,                   //disables interaction while animated
    GO_FLAG_LOCKED          = 0x00000002,                   //require key, spell, event, etc to be opened. Makes "Locked" appear in tooltip
    GO_FLAG_INTERACT_COND   = 0x00000004,                   //cannot interact (condition to interact)
    GO_FLAG_TRANSPORT       = 0x00000008,                   //any kind of transport? Object can transport (elevator, boat, car)
    GO_FLAG_UNK1            = 0x00000010,                   //
    GO_FLAG_NODESPAWN       = 0x00000020,                   //never despawn, typically for doors, they just change state
    GO_FLAG_TRIGGERED       = 0x00000040,                   //typically, summoned objects. Triggered by spell or other events
    GO_FLAG_UNK_8           = 0x00000080,
    GO_FLAG_UNK_9           = 0x00000100,                   //? Seen on type 33, possible meaning "destruct in progress"
    GO_FLAG_UNK_10          = 0x00000200,                   //? Seen on type 33
    GO_FLAG_UNK_11          = 0x00000400                    //? Seen on type 33, possibly meaning "destructed"
};

enum TextEmotes
{
    TEXTEMOTE_AGREE                = 1,
    TEXTEMOTE_AMAZE                = 2,
    TEXTEMOTE_ANGRY                = 3,
    TEXTEMOTE_APOLOGIZE            = 4,
    TEXTEMOTE_APPLAUD              = 5,
    TEXTEMOTE_BASHFUL              = 6,
    TEXTEMOTE_BECKON               = 7,
    TEXTEMOTE_BEG                  = 8,
    TEXTEMOTE_BITE                 = 9,
    TEXTEMOTE_BLEED                = 10,
    TEXTEMOTE_BLINK                = 11,
    TEXTEMOTE_BLUSH                = 12,
    TEXTEMOTE_BONK                 = 13,
    TEXTEMOTE_BORED                = 14,
    TEXTEMOTE_BOUNCE               = 15,
    TEXTEMOTE_BRB                  = 16,
    TEXTEMOTE_BOW                  = 17,
    TEXTEMOTE_BURP                 = 18,
    TEXTEMOTE_BYE                  = 19,
    TEXTEMOTE_CACKLE               = 20,
    TEXTEMOTE_CHEER                = 21,
    TEXTEMOTE_CHICKEN              = 22,
    TEXTEMOTE_CHUCKLE              = 23,
    TEXTEMOTE_CLAP                 = 24,
    TEXTEMOTE_CONFUSED             = 25,
    TEXTEMOTE_CONGRATULATE         = 26,
    TEXTEMOTE_COUGH                = 27,
    TEXTEMOTE_COWER                = 28,
    TEXTEMOTE_CRACK                = 29,
    TEXTEMOTE_CRINGE               = 30,
    TEXTEMOTE_CRY                  = 31,
    TEXTEMOTE_CURIOUS              = 32,
    TEXTEMOTE_CURTSEY              = 33,
    TEXTEMOTE_DANCE                = 34,
    TEXTEMOTE_DRINK                = 35,
    TEXTEMOTE_DROOL                = 36,
    TEXTEMOTE_EAT                  = 37,
    TEXTEMOTE_EYE                  = 38,
    TEXTEMOTE_FART                 = 39,
    TEXTEMOTE_FIDGET               = 40,
    TEXTEMOTE_FLEX                 = 41,
    TEXTEMOTE_FROWN                = 42,
    TEXTEMOTE_GASP                 = 43,
    TEXTEMOTE_GAZE                 = 44,
    TEXTEMOTE_GIGGLE               = 45,
    TEXTEMOTE_GLARE                = 46,
    TEXTEMOTE_GLOAT                = 47,
    TEXTEMOTE_GREET                = 48,
    TEXTEMOTE_GRIN                 = 49,
    TEXTEMOTE_GROAN                = 50,
    TEXTEMOTE_GROVEL               = 51,
    TEXTEMOTE_GUFFAW               = 52,
    TEXTEMOTE_HAIL                 = 53,
    TEXTEMOTE_HAPPY                = 54,
    TEXTEMOTE_HELLO                = 55,
    TEXTEMOTE_HUG                  = 56,
    TEXTEMOTE_HUNGRY               = 57,
    TEXTEMOTE_KISS                 = 58,
    TEXTEMOTE_KNEEL                = 59,
    TEXTEMOTE_LAUGH                = 60,
    TEXTEMOTE_LAYDOWN              = 61,
    TEXTEMOTE_MESSAGE              = 62,
    TEXTEMOTE_MOAN                 = 63,
    TEXTEMOTE_MOON                 = 64,
    TEXTEMOTE_MOURN                = 65,
    TEXTEMOTE_NO                   = 66,
    TEXTEMOTE_NOD                  = 67,
    TEXTEMOTE_NOSEPICK             = 68,
    TEXTEMOTE_PANIC                = 69,
    TEXTEMOTE_PEER                 = 70,
    TEXTEMOTE_PLEAD                = 71,
    TEXTEMOTE_POINT                = 72,
    TEXTEMOTE_POKE                 = 73,
    TEXTEMOTE_PRAY                 = 74,
    TEXTEMOTE_ROAR                 = 75,
    TEXTEMOTE_ROFL                 = 76,
    TEXTEMOTE_RUDE                 = 77,
    TEXTEMOTE_SALUTE               = 78,
    TEXTEMOTE_SCRATCH              = 79,
    TEXTEMOTE_SEXY                 = 80,
    TEXTEMOTE_SHAKE                = 81,
    TEXTEMOTE_SHOUT                = 82,
    TEXTEMOTE_SHRUG                = 83,
    TEXTEMOTE_SHY                  = 84,
    TEXTEMOTE_SIGH                 = 85,
    TEXTEMOTE_SIT                  = 86,
    TEXTEMOTE_SLEEP                = 87,
    TEXTEMOTE_SNARL                = 88,
    TEXTEMOTE_SPIT                 = 89,
    TEXTEMOTE_STARE                = 90,
    TEXTEMOTE_SURPRISED            = 91,
    TEXTEMOTE_SURRENDER            = 92,
    TEXTEMOTE_TALK                 = 93,
    TEXTEMOTE_TALKEX               = 94,
    TEXTEMOTE_TALKQ                = 95,
    TEXTEMOTE_TAP                  = 96,
    TEXTEMOTE_THANK                = 97,
    TEXTEMOTE_THREATEN             = 98,
    TEXTEMOTE_TIRED                = 99,
    TEXTEMOTE_VICTORY              = 100,
    TEXTEMOTE_WAVE                 = 101,
    TEXTEMOTE_WELCOME              = 102,
    TEXTEMOTE_WHINE                = 103,
    TEXTEMOTE_WHISTLE              = 104,
    TEXTEMOTE_WORK                 = 105,
    TEXTEMOTE_YAWN                 = 106,
    TEXTEMOTE_BOGGLE               = 107,
    TEXTEMOTE_CALM                 = 108,
    TEXTEMOTE_COLD                 = 109,
    TEXTEMOTE_COMFORT              = 110,
    TEXTEMOTE_CUDDLE               = 111,
    TEXTEMOTE_DUCK                 = 112,
    TEXTEMOTE_INSULT               = 113,
    TEXTEMOTE_INTRODUCE            = 114,
    TEXTEMOTE_JK                   = 115,
    TEXTEMOTE_LICK                 = 116,
    TEXTEMOTE_LISTEN               = 117,
    TEXTEMOTE_LOST                 = 118,
    TEXTEMOTE_MOCK                 = 119,
    TEXTEMOTE_PONDER               = 120,
    TEXTEMOTE_POUNCE               = 121,
    TEXTEMOTE_PRAISE               = 122,
    TEXTEMOTE_PURR                 = 123,
    TEXTEMOTE_PUZZLE               = 124,
    TEXTEMOTE_RAISE                = 125,
    TEXTEMOTE_READY                = 126,
    TEXTEMOTE_SHIMMY               = 127,
    TEXTEMOTE_SHIVER               = 128,
    TEXTEMOTE_SHOO                 = 129,
    TEXTEMOTE_SLAP                 = 130,
    TEXTEMOTE_SMIRK                = 131,
    TEXTEMOTE_SNIFF                = 132,
    TEXTEMOTE_SNUB                 = 133,
    TEXTEMOTE_SOOTHE               = 134,
    TEXTEMOTE_STINK                = 135,
    TEXTEMOTE_TAUNT                = 136,
    TEXTEMOTE_TEASE                = 137,
    TEXTEMOTE_THIRSTY              = 138,
    TEXTEMOTE_VETO                 = 139,
    TEXTEMOTE_SNICKER              = 140,
    TEXTEMOTE_STAND                = 141,
    TEXTEMOTE_TICKLE               = 142,
    TEXTEMOTE_VIOLIN               = 143,
    TEXTEMOTE_SMILE                = 163,
    TEXTEMOTE_RASP                 = 183,
    TEXTEMOTE_PITY                 = 203,
    TEXTEMOTE_GROWL                = 204,
    TEXTEMOTE_BARK                 = 205,
    TEXTEMOTE_SCARED               = 223,
    TEXTEMOTE_FLOP                 = 224,
    TEXTEMOTE_LOVE                 = 225,
    TEXTEMOTE_MOO                  = 226,
    TEXTEMOTE_OPENFIRE             = 327,
    TEXTEMOTE_FLIRT                = 328,
    TEXTEMOTE_JOKE                 = 329,
    TEXTEMOTE_COMMEND              = 243,
    TEXTEMOTE_WINK                 = 363,
    TEXTEMOTE_PAT                  = 364,
    TEXTEMOTE_SERIOUS              = 365,
    TEXTEMOTE_MOUNTSPECIAL         = 366,
    TEXTEMOTE_GOODLUCK             = 367,
    TEXTEMOTE_BLAME                = 368,
    TEXTEMOTE_BLANK                = 369,
    TEXTEMOTE_BRANDISH             = 370,
    TEXTEMOTE_BREATH               = 371,
    TEXTEMOTE_DISAGREE             = 372,
    TEXTEMOTE_DOUBT                = 373,
    TEXTEMOTE_EMBARRASS            = 374,
    TEXTEMOTE_ENCOURAGE            = 375,
    TEXTEMOTE_ENEMY                = 376,
    TEXTEMOTE_EYEBROW              = 377,
    TEXTEMOTE_TOAST                = 378
};

enum Emote
{
    EMOTE_ONESHOT_NONE                 = 0,
    EMOTE_ONESHOT_TALK                 = 1,
    EMOTE_ONESHOT_BOW                  = 2,
    EMOTE_ONESHOT_WAVE                 = 3,
    EMOTE_ONESHOT_CHEER                = 4,
    EMOTE_ONESHOT_EXCLAMATION          = 5,
    EMOTE_ONESHOT_QUESTION             = 6,
    EMOTE_ONESHOT_EAT                  = 7,
    EMOTE_STATE_DANCE                  = 10,
    EMOTE_ONESHOT_LAUGH                = 11,
    EMOTE_STATE_SLEEP                  = 12,
    EMOTE_STATE_SIT                    = 13,
    EMOTE_ONESHOT_RUDE                 = 14,
    EMOTE_ONESHOT_ROAR                 = 15,
    EMOTE_ONESHOT_KNEEL                = 16,
    EMOTE_ONESHOT_KISS                 = 17,
    EMOTE_ONESHOT_CRY                  = 18,
    EMOTE_ONESHOT_CHICKEN              = 19,
    EMOTE_ONESHOT_BEG                  = 20,
    EMOTE_ONESHOT_APPLAUD              = 21,
    EMOTE_ONESHOT_SHOUT                = 22,
    EMOTE_ONESHOT_FLEX                 = 23,
    EMOTE_ONESHOT_SHY                  = 24,
    EMOTE_ONESHOT_POINT                = 25,
    EMOTE_STATE_STAND                  = 26,
    EMOTE_STATE_READYUNARMED           = 27,
    EMOTE_STATE_WORK_SHEATHED          = 28,
    EMOTE_STATE_POINT                  = 29,
    EMOTE_STATE_NONE                   = 30,
    EMOTE_ONESHOT_WOUND                = 33,
    EMOTE_ONESHOT_WOUNDCRITICAL        = 34,
    EMOTE_ONESHOT_ATTACKUNARMED        = 35,
    EMOTE_ONESHOT_ATTACK1H             = 36,
    EMOTE_ONESHOT_ATTACK2HTIGHT        = 37,
    EMOTE_ONESHOT_ATTACK2HLOOSE        = 38,
    EMOTE_ONESHOT_PARRYUNARMED         = 39,
    EMOTE_ONESHOT_PARRYSHIELD          = 43,
    EMOTE_ONESHOT_READYUNARMED         = 44,
    EMOTE_ONESHOT_READY1H              = 45,
    EMOTE_ONESHOT_READYBOW             = 48,
    EMOTE_ONESHOT_SPELLPRECAST         = 50,
    EMOTE_ONESHOT_SPELLCAST            = 51,
    EMOTE_ONESHOT_BATTLEROAR           = 53,
    EMOTE_ONESHOT_SPECIALATTACK1H      = 54,
    EMOTE_ONESHOT_KICK                 = 60,
    EMOTE_ONESHOT_ATTACKTHROWN         = 61,
    EMOTE_STATE_STUN                   = 64,
    EMOTE_STATE_DEAD                   = 65,
    EMOTE_ONESHOT_SALUTE               = 66,
    EMOTE_STATE_KNEEL                  = 68,
    EMOTE_STATE_USESTANDING            = 69,
    EMOTE_ONESHOT_WAVE_NOSHEATHE       = 70,
    EMOTE_ONESHOT_CHEER_NOSHEATHE      = 71,
    EMOTE_ONESHOT_EAT_NOSHEATHE        = 92,
    EMOTE_STATE_STUN_NOSHEATHE         = 93,
    EMOTE_ONESHOT_DANCE                = 94,
    EMOTE_ONESHOT_SALUTE_NOSHEATH      = 113,
    EMOTE_STATE_USESTANDING_NOSHEATHE  = 133,
    EMOTE_ONESHOT_LAUGH_NOSHEATHE      = 153,
    EMOTE_STATE_WORK                   = 173,
    EMOTE_STATE_SPELLPRECAST           = 193,
    EMOTE_ONESHOT_READYRIFLE           = 213,
    EMOTE_STATE_READYRIFLE             = 214,
    EMOTE_STATE_WORK_MINING            = 233,
    EMOTE_STATE_WORK_CHOPWOOD          = 234,
    EMOTE_STATE_APPLAUD                = 253,
    EMOTE_ONESHOT_LIFTOFF              = 254,
    EMOTE_ONESHOT_YES                  = 273,
    EMOTE_ONESHOT_NO                   = 274,
    EMOTE_ONESHOT_TRAIN                = 275,
    EMOTE_ONESHOT_LAND                 = 293,
    EMOTE_STATE_AT_EASE                = 313,
    EMOTE_STATE_READY1H                = 333,
    EMOTE_STATE_SPELLKNEELSTART        = 353,
    EMOTE_STATE_SUBMERGED              = 373,
    EMOTE_ONESHOT_SUBMERGE             = 374,
    EMOTE_STATE_READY2H                = 375,
    EMOTE_STATE_READYBOW               = 376,
    EMOTE_ONESHOT_MOUNTSPECIAL         = 377,
    EMOTE_STATE_TALK                   = 378,
    EMOTE_STATE_FISHING                = 379,
    EMOTE_ONESHOT_FISHING              = 380,
    EMOTE_ONESHOT_LOOT                 = 381,
    EMOTE_STATE_WHIRLWIND              = 382,
    EMOTE_STATE_DROWNED                = 383,
    EMOTE_STATE_HOLD_BOW               = 384,
    EMOTE_STATE_HOLD_RIFLE             = 385,
    EMOTE_STATE_HOLD_THROWN            = 386,
    EMOTE_ONESHOT_DROWN                = 387,
    EMOTE_ONESHOT_STOMP                = 388,
    EMOTE_ONESHOT_ATTACKOFF            = 389,
    EMOTE_ONESHOT_ATTACKOFFPIERCE      = 390,
    EMOTE_STATE_ROAR                   = 391,
    EMOTE_STATE_LAUGH                  = 392,
    EMOTE_ONESHOT_CREATURE_SPECIAL     = 393,
    EMOTE_ONESHOT_JUMPLANDRUN          = 394,
    EMOTE_ONESHOT_JUMPEND              = 395,
    EMOTE_ONESHOT_TALK_NOSHEATHE       = 396,
    EMOTE_ONESHOT_POINT_NOSHEATHE      = 397,
    EMOTE_STATE_CANNIBALIZE            = 398,
    EMOTE_ONESHOT_JUMPSTART            = 399,
    EMOTE_STATE_DANCESPECIAL           = 400,
    EMOTE_ONESHOT_DANCESPECIAL         = 401,
    EMOTE_ONESHOT_CUSTOMSPELL01        = 402,
    EMOTE_ONESHOT_CUSTOMSPELL02        = 403,
    EMOTE_ONESHOT_CUSTOMSPELL03        = 404,
    EMOTE_ONESHOT_CUSTOMSPELL04        = 405,
    EMOTE_ONESHOT_CUSTOMSPELL05        = 406,
    EMOTE_ONESHOT_CUSTOMSPELL06        = 407,
    EMOTE_ONESHOT_CUSTOMSPELL07        = 408,
    EMOTE_ONESHOT_CUSTOMSPELL08        = 409,
    EMOTE_ONESHOT_CUSTOMSPELL09        = 410,
    EMOTE_ONESHOT_CUSTOMSPELL10        = 411,
    EMOTE_STATE_EXCLAIM                = 412,
    EMOTE_STATE_DANCE_CUSTOM           = 413,
    EMOTE_STATE_SIT_CHAIR_MED          = 415,
    EMOTE_STATE_CUSTOM_SPELL_01        = 416,
    EMOTE_STATE_CUSTOM_SPELL_02        = 417,
    EMOTE_STATE_EAT                    = 418,
    EMOTE_STATE_CUSTOM_SPELL_04        = 419,
    EMOTE_STATE_CUSTOM_SPELL_03        = 420,
    EMOTE_STATE_CUSTOM_SPELL_05        = 421,
    EMOTE_STATE_SPELLEFFECT_HOLD       = 422,
    EMOTE_STATE_EAT_NO_SHEATHE         = 423,
    EMOTE_STATE_MOUNT                  = 424,
    EMOTE_STATE_READY2HL               = 425,
    EMOTE_STATE_SIT_CHAIR_HIGH         = 426,
    EMOTE_STATE_FALL                   = 427,
    EMOTE_STATE_LOOT                   = 428,
    EMOTE_STATE_SUBMERGED_NEW          = 429,
    EMOTE_ONESHOT_COWER                = 430,
    EMOTE_STATE_COWER                  = 431,
    EMOTE_ONESHOT_USESTANDING          = 432,
    EMOTE_STATE_STEALTH_STAND          = 433,
    EMOTE_ONESHOT_OMNICAST_GHOUL       = 434,
    EMOTE_ONESHOT_ATTACKBOW            = 435,
    EMOTE_ONESHOT_ATTACKRIFLE          = 436,
    EMOTE_STATE_SWIM_IDLE              = 437,
    EMOTE_STATE_ATTACK_UNARMED         = 438,
    EMOTE_ONESHOT_SPELLCAST_W_SOUND    = 439,
    EMOTE_ONESHOT_DODGE                = 440,
    EMOTE_ONESHOT_PARRY1H              = 441,
    EMOTE_ONESHOT_PARRY2H              = 442,
    EMOTE_ONESHOT_PARRY2HL             = 443,
    EMOTE_STATE_FLYFALL                = 444,
    EMOTE_ONESHOT_FLYDEATH             = 445,
    EMOTE_STATE_FLY_FALL               = 446,
    EMOTE_ONESHOT_FLY_SIT_GROUND_DOWN  = 447,
    EMOTE_ONESHOT_FLY_SIT_GROUND_UP    = 448,
    EMOTE_ONESHOT_EMERGE               = 449,
    EMOTE_ONESHOT_DRAGONSPIT           = 450,
    EMOTE_STATE_SPECIALUNARMED         = 451,
    EMOTE_ONESHOT_FLYGRAB              = 452,
    EMOTE_STATE_FLYGRABCLOSED          = 453,
    EMOTE_ONESHOT_FLYGRABTHROWN        = 454,
    EMOTE_STATE_FLY_SIT_GROUND         = 455,
    EMOTE_STATE_WALKBACKWARDS          = 456,
    EMOTE_ONESHOT_FLYTALK              = 457,
    EMOTE_ONESHOT_FLYATTACK1H          = 458,
    EMOTE_STATE_CUSTOMSPELL08          = 459,
    EMOTE_ONESHOT_FLY_DRAGONSPIT       = 460,
    EMOTE_STATE_SIT_CHAIR_LOW          = 461,
    EMOTE_ONE_SHOT_STUN                = 462,
    EMOTE_ONESHOT_SPELLCAST_OMNI       = 463,
    EMOTE_STATE_READYTHROWN            = 464
};

enum Anim
{
    ANIM_STAND                     = 0x0,
    ANIM_DEATH                     = 0x1,
    ANIM_SPELL                     = 0x2,
    ANIM_STOP                      = 0x3,
    ANIM_WALK                      = 0x4,
    ANIM_RUN                       = 0x5,
    ANIM_DEAD                      = 0x6,
    ANIM_RISE                      = 0x7,
    ANIM_STANDWOUND                = 0x8,
    ANIM_COMBATWOUND               = 0x9,
    ANIM_COMBATCRITICAL            = 0xA,
    ANIM_SHUFFLE_LEFT              = 0xB,
    ANIM_SHUFFLE_RIGHT             = 0xC,
    ANIM_WALK_BACKWARDS            = 0xD,
    ANIM_STUN                      = 0xE,
    ANIM_HANDS_CLOSED              = 0xF,
    ANIM_ATTACKUNARMED             = 0x10,
    ANIM_ATTACK1H                  = 0x11,
    ANIM_ATTACK2HTIGHT             = 0x12,
    ANIM_ATTACK2HLOOSE             = 0x13,
    ANIM_PARRYUNARMED              = 0x14,
    ANIM_PARRY1H                   = 0x15,
    ANIM_PARRY2HTIGHT              = 0x16,
    ANIM_PARRY2HLOOSE              = 0x17,
    ANIM_PARRYSHIELD               = 0x18,
    ANIM_READYUNARMED              = 0x19,
    ANIM_READY1H                   = 0x1A,
    ANIM_READY2HTIGHT              = 0x1B,
    ANIM_READY2HLOOSE              = 0x1C,
    ANIM_READYBOW                  = 0x1D,
    ANIM_DODGE                     = 0x1E,
    ANIM_SPELLPRECAST              = 0x1F,
    ANIM_SPELLCAST                 = 0x20,
    ANIM_SPELLCASTAREA             = 0x21,
    ANIM_NPCWELCOME                = 0x22,
    ANIM_NPCGOODBYE                = 0x23,
    ANIM_BLOCK                     = 0x24,
    ANIM_JUMPSTART                 = 0x25,
    ANIM_JUMP                      = 0x26,
    ANIM_JUMPEND                   = 0x27,
    ANIM_FALL                      = 0x28,
    ANIM_SWIMIDLE                  = 0x29,
    ANIM_SWIM                      = 0x2A,
    ANIM_SWIM_LEFT                 = 0x2B,
    ANIM_SWIM_RIGHT                = 0x2C,
    ANIM_SWIM_BACKWARDS            = 0x2D,
    ANIM_ATTACKBOW                 = 0x2E,
    ANIM_FIREBOW                   = 0x2F,
    ANIM_READYRIFLE                = 0x30,
    ANIM_ATTACKRIFLE               = 0x31,
    ANIM_LOOT                      = 0x32,
    ANIM_SPELL_PRECAST_DIRECTED    = 0x33,
    ANIM_SPELL_PRECAST_OMNI        = 0x34,
    ANIM_SPELL_CAST_DIRECTED       = 0x35,
    ANIM_SPELL_CAST_OMNI           = 0x36,
    ANIM_SPELL_BATTLEROAR          = 0x37,
    ANIM_SPELL_READYABILITY        = 0x38,
    ANIM_SPELL_SPECIAL1H           = 0x39,
    ANIM_SPELL_SPECIAL2H           = 0x3A,
    ANIM_SPELL_SHIELDBASH          = 0x3B,
    ANIM_EMOTE_TALK                = 0x3C,
    ANIM_EMOTE_EAT                 = 0x3D,
    ANIM_EMOTE_WORK                = 0x3E,
    ANIM_EMOTE_USE_STANDING        = 0x3F,
    ANIM_EMOTE_EXCLAMATION         = 0x40,
    ANIM_EMOTE_QUESTION            = 0x41,
    ANIM_EMOTE_BOW                 = 0x42,
    ANIM_EMOTE_WAVE                = 0x43,
    ANIM_EMOTE_CHEER               = 0x44,
    ANIM_EMOTE_DANCE               = 0x45,
    ANIM_EMOTE_LAUGH               = 0x46,
    ANIM_EMOTE_SLEEP               = 0x47,
    ANIM_EMOTE_SIT_GROUND          = 0x48,
    ANIM_EMOTE_RUDE                = 0x49,
    ANIM_EMOTE_ROAR                = 0x4A,
    ANIM_EMOTE_KNEEL               = 0x4B,
    ANIM_EMOTE_KISS                = 0x4C,
    ANIM_EMOTE_CRY                 = 0x4D,
    ANIM_EMOTE_CHICKEN             = 0x4E,
    ANIM_EMOTE_BEG                 = 0x4F,
    ANIM_EMOTE_APPLAUD             = 0x50,
    ANIM_EMOTE_SHOUT               = 0x51,
    ANIM_EMOTE_FLEX                = 0x52,
    ANIM_EMOTE_SHY                 = 0x53,
    ANIM_EMOTE_POINT               = 0x54,
    ANIM_ATTACK1HPIERCE            = 0x55,
    ANIM_ATTACK2HLOOSEPIERCE       = 0x56,
    ANIM_ATTACKOFF                 = 0x57,
    ANIM_ATTACKOFFPIERCE           = 0x58,
    ANIM_SHEATHE                   = 0x59,
    ANIM_HIPSHEATHE                = 0x5A,
    ANIM_MOUNT                     = 0x5B,
    ANIM_RUN_LEANRIGHT             = 0x5C,
    ANIM_RUN_LEANLEFT              = 0x5D,
    ANIM_MOUNT_SPECIAL             = 0x5E,
    ANIM_KICK                      = 0x5F,
    ANIM_SITDOWN                   = 0x60,
    ANIM_SITTING                   = 0x61,
    ANIM_SITUP                     = 0x62,
    ANIM_SLEEPDOWN                 = 0x63,
    ANIM_SLEEPING                  = 0x64,
    ANIM_SLEEPUP                   = 0x65,
    ANIM_SITCHAIRLOW               = 0x66,
    ANIM_SITCHAIRMEDIUM            = 0x67,
    ANIM_SITCHAIRHIGH              = 0x68,
    ANIM_LOADBOW                   = 0x69,
    ANIM_LOADRIFLE                 = 0x6A,
    ANIM_ATTACKTHROWN              = 0x6B,
    ANIM_READYTHROWN               = 0x6C,
    ANIM_HOLDBOW                   = 0x6D,
    ANIM_HOLDRIFLE                 = 0x6E,
    ANIM_HOLDTHROWN                = 0x6F,
    ANIM_LOADTHROWN                = 0x70,
    ANIM_EMOTE_SALUTE              = 0x71,
    ANIM_KNEELDOWN                 = 0x72,
    ANIM_KNEELING                  = 0x73,
    ANIM_KNEELUP                   = 0x74,
    ANIM_ATTACKUNARMEDOFF          = 0x75,
    ANIM_SPECIALUNARMED            = 0x76,
    ANIM_STEALTHWALK               = 0x77,
    ANIM_STEALTHSTAND              = 0x78,
    ANIM_KNOCKDOWN                 = 0x79,
    ANIM_EATING                    = 0x7A,
    ANIM_USESTANDINGLOOP           = 0x7B,
    ANIM_CHANNELCASTDIRECTED       = 0x7C,
    ANIM_CHANNELCASTOMNI           = 0x7D,
    ANIM_WHIRLWIND                 = 0x7E,
    ANIM_BIRTH                     = 0x7F,
    ANIM_USESTANDINGSTART          = 0x80,
    ANIM_USESTANDINGEND            = 0x81,
    ANIM_HOWL                      = 0x82,
    ANIM_DROWN                     = 0x83,
    ANIM_DROWNED                   = 0x84,
    ANIM_FISHINGCAST               = 0x85,
    ANIM_FISHINGLOOP               = 0x86,
    ANIM_FLY                       = 0x87,
    ANIM_EMOTE_WORK_NO_SHEATHE     = 0x88,
    ANIM_EMOTE_STUN_NO_SHEATHE     = 0x89,
    ANIM_EMOTE_USE_STANDING_NO_SHEATHE= 0x8A,
    ANIM_SPELL_SLEEP_DOWN          = 0x8B,
    ANIM_SPELL_KNEEL_START         = 0x8C,
    ANIM_SPELL_KNEEL_LOOP          = 0x8D,
    ANIM_SPELL_KNEEL_END           = 0x8E,
    ANIM_SPRINT                    = 0x8F,
    ANIM_IN_FIGHT                  = 0x90,

    ANIM_GAMEOBJ_SPAWN             = 145,
    ANIM_GAMEOBJ_CLOSE             = 146,
    ANIM_GAMEOBJ_CLOSED            = 147,
    ANIM_GAMEOBJ_OPEN              = 148,
    ANIM_GAMEOBJ_OPENED            = 149,
    ANIM_GAMEOBJ_DESTROY           = 150,
    ANIM_GAMEOBJ_DESTROYED         = 151,
    ANIM_GAMEOBJ_REBUILD           = 152,
    ANIM_GAMEOBJ_CUSTOM0           = 153,
    ANIM_GAMEOBJ_CUSTOM1           = 154,
    ANIM_GAMEOBJ_CUSTOM2           = 155,
    ANIM_GAMEOBJ_CUSTOM3           = 156,
    ANIM_GAMEOBJ_DESPAWN           = 157,
    ANIM_HOLD                      = 158,
    ANIM_DECAY                     = 159,
    ANIM_BOWPULL                   = 160,
    ANIM_BOWRELEASE                = 161,
    ANIM_SHIPSTART                 = 162,
    ANIM_SHIPMOVEING               = 163,
    ANIM_SHIPSTOP                  = 164,
    ANIM_GROUPARROW                = 165,
    ANIM_ARROW                     = 166,
    ANIM_CORPSEARROW               = 167,
    ANIM_GUIDEARROW                = 168,
    ANIM_SWAY                      = 169,
    ANIM_DRUIDCATPOUNCE            = 170,
    ANIM_DRUIDCATRIP               = 171,
    ANIM_DRUIDCATRAKE              = 172,
    ANIM_DRUIDCATRAVAGE            = 173,
    ANIM_DRUIDCATCLAW              = 174,
    ANIM_DRUIDCATCOWER             = 175,
    ANIM_DRUIDBEARSWIPE            = 176,
    ANIM_DRUIDBEARBITE             = 177,
    ANIM_DRUIDBEARMAUL             = 178,
    ANIM_DRUIDBEARBASH             = 179,
    ANIM_DRAGONTAIL                = 180,
    ANIM_DRAGONSTOMP               = 181,
    ANIM_DRAGONSPIT                = 182,
    ANIM_DRAGONSPITHOVER           = 183,
    ANIM_DRAGONSPITFLY             = 184,
    ANIM_EMOTEYES                  = 185,
    ANIM_EMOTENO                   = 186,
    ANIM_JUMPLANDRUN               = 187,
    ANIM_LOOTHOLD                  = 188,
    ANIM_LOOTUP                    = 189,
    ANIM_STANDHIGH                 = 190,
    ANIM_IMPACT                    = 191,
    ANIM_LIFTOFF                   = 192,
    ANIM_HOVER                     = 193,
    ANIM_SUCCUBUSENTICE            = 194,
    ANIM_EMOTETRAIN                = 195,
    ANIM_EMOTEDEAD                 = 196,
    ANIM_EMOTEDANCEONCE            = 197,
    ANIM_DEFLECT                   = 198,
    ANIM_EMOTEEATNOSHEATHE         = 199,
    ANIM_LAND                      = 200,
    ANIM_SUBMERGE                  = 201,
    ANIM_SUBMERGED                 = 202,
    ANIM_CANNIBALIZE               = 203,
    ANIM_ARROWBIRTH                = 204,
    ANIM_GROURARROWBIRTH           = 205,
    ANIM_CORPSEARROWBIRTH          = 206,
    ANIM_GUIDEARROWBIRTH           = 207,
    ANIM_EMOTETALKNOSHEATHE        = 208,
    ANIM_EMOTEPOINTNOSHEATHE       = 209,
    ANIM_EMOTESALUTENOSHEATHE      = 210,
    ANIM_EMOTEDANCESPECIAL         = 211,
    ANIM_MUTILATE                  = 212,
    ANIM_CUSTOMSPELL01             = 213,
    ANIM_CUSTOMSPELL02             = 214,
    ANIM_CUSTOMSPELL03             = 215,
    ANIM_CUSTOMSPELL04             = 216,
    ANIM_CUSTOMSPELL05             = 217,
    ANIM_CUSTOMSPELL06             = 218,
    ANIM_CUSTOMSPELL07             = 219,
    ANIM_CUSTOMSPELL08             = 220,
    ANIM_CUSTOMSPELL09             = 221,
    ANIM_CUSTOMSPELL10             = 222,
    ANIM_StealthRun                = 223
};

enum LockKeyType
{
    LOCK_KEY_NONE  = 0,
    LOCK_KEY_ITEM  = 1,
    LOCK_KEY_SKILL = 2
};

enum LockType
{
    LOCKTYPE_PICKLOCK              = 1,
    LOCKTYPE_HERBALISM             = 2,
    LOCKTYPE_MINING                = 3,
    LOCKTYPE_DISARM_TRAP           = 4,
    LOCKTYPE_OPEN                  = 5,
    LOCKTYPE_TREASURE              = 6,
    LOCKTYPE_CALCIFIED_ELVEN_GEMS  = 7,
    LOCKTYPE_CLOSE                 = 8,
    LOCKTYPE_ARM_TRAP              = 9,
    LOCKTYPE_QUICK_OPEN            = 10,
    LOCKTYPE_QUICK_CLOSE           = 11,
    LOCKTYPE_OPEN_TINKERING        = 12,
    LOCKTYPE_OPEN_KNEELING         = 13,
    LOCKTYPE_OPEN_ATTACKING        = 14,
    LOCKTYPE_GAHZRIDIAN            = 15,
    LOCKTYPE_BLASTING              = 16,
    LOCKTYPE_SLOW_OPEN             = 17,
    LOCKTYPE_SLOW_CLOSE            = 18,
    LOCKTYPE_FISHING               = 19,
    LOCKTYPE_INSCRIPTION           = 20,
    LOCKTYPE_OPEN_FROM_VEHICLE     = 21
};

enum TrainerType                                            // this is important type for npcs!
{
    TRAINER_TYPE_CLASS             = 0,
    TRAINER_TYPE_MOUNTS            = 1,                     // on blizz it's 2
    TRAINER_TYPE_TRADESKILLS       = 2,
    TRAINER_TYPE_PETS              = 3
};

#define MAX_TRAINER_TYPE 4

// CreatureType.dbc
enum CreatureType
{
    CREATURE_TYPE_BEAST            = 1,
    CREATURE_TYPE_DRAGONKIN        = 2,
    CREATURE_TYPE_DEMON            = 3,
    CREATURE_TYPE_ELEMENTAL        = 4,
    CREATURE_TYPE_GIANT            = 5,
    CREATURE_TYPE_UNDEAD           = 6,
    CREATURE_TYPE_HUMANOID         = 7,
    CREATURE_TYPE_CRITTER          = 8,
    CREATURE_TYPE_MECHANICAL       = 9,
    CREATURE_TYPE_NOT_SPECIFIED    = 10,
    CREATURE_TYPE_TOTEM            = 11,
    CREATURE_TYPE_NON_COMBAT_PET   = 12,
    CREATURE_TYPE_GAS_CLOUD        = 13
};

uint32 const CREATURE_TYPEMASK_DEMON_OR_UNDEAD = (1 << (CREATURE_TYPE_DEMON-1)) | (1 << (CREATURE_TYPE_UNDEAD-1));
uint32 const CREATURE_TYPEMASK_HUMANOID_OR_UNDEAD = (1 << (CREATURE_TYPE_HUMANOID-1)) | (1 << (CREATURE_TYPE_UNDEAD-1));
uint32 const CREATURE_TYPEMASK_MECHANICAL_OR_ELEMENTAL = (1 << (CREATURE_TYPE_MECHANICAL-1)) | (1 << (CREATURE_TYPE_ELEMENTAL-1));

// CreatureFamily.dbc
enum CreatureFamily
{
    CREATURE_FAMILY_WOLF           = 1,
    CREATURE_FAMILY_CAT            = 2,
    CREATURE_FAMILY_SPIDER         = 3,
    CREATURE_FAMILY_BEAR           = 4,
    CREATURE_FAMILY_BOAR           = 5,
    CREATURE_FAMILY_CROCOLISK      = 6,
    CREATURE_FAMILY_CARRION_BIRD   = 7,
    CREATURE_FAMILY_CRAB           = 8,
    CREATURE_FAMILY_GORILLA        = 9,
    CREATURE_FAMILY_HORSE_CUSTOM   = 10,                    // not exist in DBC but used for horse like beasts in DB
    CREATURE_FAMILY_RAPTOR         = 11,
    CREATURE_FAMILY_TALLSTRIDER    = 12,
    CREATURE_FAMILY_FELHUNTER      = 15,
    CREATURE_FAMILY_VOIDWALKER     = 16,
    CREATURE_FAMILY_SUCCUBUS       = 17,
    CREATURE_FAMILY_DOOMGUARD      = 19,
    CREATURE_FAMILY_SCORPID        = 20,
    CREATURE_FAMILY_TURTLE         = 21,
    CREATURE_FAMILY_IMP            = 23,
    CREATURE_FAMILY_BAT            = 24,
    CREATURE_FAMILY_HYENA          = 25,
    CREATURE_FAMILY_BIRD_OF_PREY   = 26,
    CREATURE_FAMILY_WIND_SERPENT   = 27,
    CREATURE_FAMILY_REMOTE_CONTROL = 28,
    CREATURE_FAMILY_FELGUARD       = 29,
    CREATURE_FAMILY_DRAGONHAWK     = 30,
    CREATURE_FAMILY_RAVAGER        = 31,
    CREATURE_FAMILY_WARP_STALKER   = 32,
    CREATURE_FAMILY_SPOREBAT       = 33,
    CREATURE_FAMILY_NETHER_RAY     = 34,
    CREATURE_FAMILY_SERPENT        = 35,
    CREATURE_FAMILY_MOTH           = 37,
    CREATURE_FAMILY_CHIMAERA       = 38,
    CREATURE_FAMILY_DEVILSAUR      = 39,
    CREATURE_FAMILY_GHOUL          = 40,
    CREATURE_FAMILY_SILITHID       = 41,
    CREATURE_FAMILY_WORM           = 42,
    CREATURE_FAMILY_RHINO          = 43,
    CREATURE_FAMILY_WASP           = 44,
    CREATURE_FAMILY_CORE_HOUND     = 45,
    CREATURE_FAMILY_SPIRIT_BEAST   = 46
};

enum CreatureTypeFlags
{
    CREATURE_TYPEFLAGS_TAMEABLE         = 0x000001,         // Tameable by any hunter
    CREATURE_TYPEFLAGS_GHOST_VISIBLE    = 0x000002,         // Creatures which can _also_ be seen when player is a ghost
    CREATURE_TYPEFLAGS_UNK3             = 0x000004,
    CREATURE_TYPEFLAGS_UNK4             = 0x000008,
    CREATURE_TYPEFLAGS_UNK5             = 0x000010,
    CREATURE_TYPEFLAGS_UNK6             = 0x000020,
    CREATURE_TYPEFLAGS_UNK7             = 0x000040,
    CREATURE_TYPEFLAGS_UNK8             = 0x000080,
    CREATURE_TYPEFLAGS_HERBLOOT         = 0x000100,         // Can be looted by herbalist
    CREATURE_TYPEFLAGS_MININGLOOT       = 0x000200,         // Can be looted by miner
    CREATURE_TYPEFLAGS_UNK11            = 0x000400,
    CREATURE_TYPEFLAGS_UNK12            = 0x000800,         // ? Related to mounts in some way. If mounted, fight mounted, mount appear as independant when rider dies?
    CREATURE_TYPEFLAGS_UNK13            = 0x001000,         // ? Can aid any player in combat if in range?
    CREATURE_TYPEFLAGS_UNK14            = 0x002000,
    CREATURE_TYPEFLAGS_UNK15            = 0x004000,         // ? Possibly not in use
    CREATURE_TYPEFLAGS_ENGINEERLOOT     = 0x008000,         // Can be looted by engineer
    CREATURE_TYPEFLAGS_EXOTIC           = 0x010000,         // Can be tamed by hunter as exotic pet
    CREATURE_TYPEFLAGS_UNK18            = 0x020000,         // ? Related to vehicles/pvp?
    CREATURE_TYPEFLAGS_UNK19            = 0x040000,         // ? Related to vehicle/siege weapons?
    CREATURE_TYPEFLAGS_UNK20            = 0x080000,
    CREATURE_TYPEFLAGS_UNK21            = 0x100000,
    CREATURE_TYPEFLAGS_UNK22            = 0x200000,
    CREATURE_TYPEFLAGS_UNK23            = 0x400000,
    CREATURE_TYPEFLAGS_UNK24            = 0x800000          // ? First seen in 3.2.2. Related to banner/backpack of creature/companion?
};

enum CreatureEliteType
{
    CREATURE_ELITE_NORMAL          = 0,
    CREATURE_ELITE_ELITE           = 1,
    CREATURE_ELITE_RAREELITE       = 2,
    CREATURE_ELITE_WORLDBOSS       = 3,
    CREATURE_ELITE_RARE            = 4,
    CREATURE_UNKNOWN               = 5                      // found in 2.2.3 for 2 mobs
};

// values based at Holidays.dbc
enum HolidayIds
{
    HOLIDAY_FIREWORKS_SPECTACULAR    = 62,
    HOLIDAY_FEAST_OF_WINTER_VEIL     = 141,
    HOLIDAY_NOBLEGARDEN              = 181,
    HOLIDAY_CHILDRENS_WEEK           = 201,
    HOLIDAY_CALL_TO_ARMS_AV          = 283,
    HOLIDAY_CALL_TO_ARMS_WS          = 284,
    HOLIDAY_CALL_TO_ARMS_AB          = 285,
    HOLIDAY_FISHING_EXTRAVAGANZA     = 301,
    HOLIDAY_HARVEST_FESTIVAL         = 321,
    HOLIDAY_HALLOWS_END              = 324,
    HOLIDAY_LUNAR_FESTIVAL           = 327,
    HOLIDAY_LOVE_IS_IN_THE_AIR       = 335,
    HOLIDAY_FIRE_FESTIVAL            = 341,
    HOLIDAY_CALL_TO_ARMS_EY          = 353,
    HOLIDAY_BREWFEST                 = 372,
    HOLIDAY_DARKMOON_FAIRE_ELWYNN    = 374,
    HOLIDAY_DARKMOON_FAIRE_THUNDER   = 375,
    HOLIDAY_DARKMOON_FAIRE_SHATTRATH = 376,
    HOLIDAY_PIRATES_DAY              = 398,
    HOLIDAY_CALL_TO_ARMS_SA          = 400,
    HOLIDAY_PILGRIMS_BOUNTY          = 404,
    HOLIDAY_WOTLK_LAUNCH             = 406,
    HOLIDAY_DAY_OF_DEAD              = 409,
    HOLIDAY_CALL_TO_ARMS_ISLE_OF_C   = 420
};

// values based at QuestInfo.dbc
enum QuestTypes
{
    QUEST_TYPE_ELITE               = 1,
    QUEST_TYPE_LIFE                = 21,
    QUEST_TYPE_PVP                 = 41,
    QUEST_TYPE_RAID                = 62,
    QUEST_TYPE_DUNGEON             = 81,
    QUEST_TYPE_WORLD_EVENT         = 82,
    QUEST_TYPE_LEGENDARY           = 83,
    QUEST_TYPE_ESCORT              = 84,
    QUEST_TYPE_HEROIC              = 85,
    QUEST_TYPE_RAID_10             = 88,
    QUEST_TYPE_RAID_25             = 89
};

// values based at QuestSort.dbc
enum QuestSort
{
    QUEST_SORT_EPIC                = 1,
    QUEST_SORT_WAILING_CAVERNS_OLD = 21,
    QUEST_SORT_SEASONAL            = 22,
    QUEST_SORT_UNDERCITY_OLD       = 23,
    QUEST_SORT_HERBALISM           = 24,
    QUEST_SORT_BATTLEGROUNDS       = 25,
    QUEST_SORT_ULDAMN_OLD          = 41,
    QUEST_SORT_WARLOCK             = 61,
    QUEST_SORT_WARRIOR             = 81,
    QUEST_SORT_SHAMAN              = 82,
    QUEST_SORT_FISHING             = 101,
    QUEST_SORT_BLACKSMITHING       = 121,
    QUEST_SORT_PALADIN             = 141,
    QUEST_SORT_MAGE                = 161,
    QUEST_SORT_ROGUE               = 162,
    QUEST_SORT_ALCHEMY             = 181,
    QUEST_SORT_LEATHERWORKING      = 182,
    QUEST_SORT_ENGINERING          = 201,
    QUEST_SORT_TREASURE_MAP        = 221,
    QUEST_SORT_SUNKEN_TEMPLE_OLD   = 241,
    QUEST_SORT_HUNTER              = 261,
    QUEST_SORT_PRIEST              = 262,
    QUEST_SORT_DRUID               = 263,
    QUEST_SORT_TAILORING           = 264,
    QUEST_SORT_SPECIAL             = 284,
    QUEST_SORT_COOKING             = 304,
    QUEST_SORT_FIRST_AID           = 324,
    QUEST_SORT_LEGENDARY           = 344,
    QUEST_SORT_DARKMOON_FAIRE      = 364,
    QUEST_SORT_AHN_QIRAJ_WAR       = 365,
    QUEST_SORT_LUNAR_FESTIVAL      = 366,
    QUEST_SORT_REPUTATION          = 367,
    QUEST_SORT_INVASION            = 368,
    QUEST_SORT_MIDSUMMER           = 369,
    QUEST_SORT_BREWFEST            = 370,
    QUEST_SORT_INSCRIPTION         = 371,
    QUEST_SORT_DEATH_KNIGHT        = 372,
    QUEST_SORT_JEWELCRAFTING       = 373
};

inline uint8 ClassByQuestSort(int32 QuestSort)
{
    switch(QuestSort)
    {
        case QUEST_SORT_WARLOCK:        return CLASS_WARLOCK;
        case QUEST_SORT_WARRIOR:        return CLASS_WARRIOR;
        case QUEST_SORT_SHAMAN:         return CLASS_SHAMAN;
        case QUEST_SORT_PALADIN:        return CLASS_PALADIN;
        case QUEST_SORT_MAGE:           return CLASS_MAGE;
        case QUEST_SORT_ROGUE:          return CLASS_ROGUE;
        case QUEST_SORT_HUNTER:         return CLASS_HUNTER;
        case QUEST_SORT_PRIEST:         return CLASS_PRIEST;
        case QUEST_SORT_DRUID:          return CLASS_DRUID;
        case QUEST_SORT_DEATH_KNIGHT:   return CLASS_DEATH_KNIGHT;
    }
    return 0;
}

enum SkillType
{
    SKILL_NONE                     = 0,

    SKILL_FROST                    = 6,
    SKILL_FIRE                     = 8,
    SKILL_ARMS                     = 26,
    SKILL_COMBAT                   = 38,
    SKILL_SUBTLETY                 = 39,
    SKILL_SWORDS                   = 43,
    SKILL_AXES                     = 44,
    SKILL_BOWS                     = 45,
    SKILL_GUNS                     = 46,
    SKILL_BEAST_MASTERY            = 50,
    SKILL_SURVIVAL                 = 51,
    SKILL_MACES                    = 54,
    SKILL_2H_SWORDS                = 55,
    SKILL_HOLY                     = 56,
    SKILL_SHADOW                   = 78,
    SKILL_DEFENSE                  = 95,
    SKILL_LANG_COMMON              = 98,
    SKILL_RACIAL_DWARVEN           = 101,
    SKILL_LANG_ORCISH              = 109,
    SKILL_LANG_DWARVEN             = 111,
    SKILL_LANG_DARNASSIAN          = 113,
    SKILL_LANG_TAURAHE             = 115,
    SKILL_DUAL_WIELD               = 118,
    SKILL_RACIAL_TAUREN            = 124,
    SKILL_ORC_RACIAL               = 125,
    SKILL_RACIAL_NIGHT_ELF         = 126,
    SKILL_FIRST_AID                = 129,
    SKILL_FERAL_COMBAT             = 134,
    SKILL_STAVES                   = 136,
    SKILL_LANG_THALASSIAN          = 137,
    SKILL_LANG_DRACONIC            = 138,
    SKILL_LANG_DEMON_TONGUE        = 139,
    SKILL_LANG_TITAN               = 140,
    SKILL_LANG_OLD_TONGUE          = 141,
    SKILL_SURVIVAL2                = 142,
    SKILL_RIDING_HORSE             = 148,
    SKILL_RIDING_WOLF              = 149,
    SKILL_RIDING_RAM               = 152,
    SKILL_RIDING_TIGER             = 150,
    SKILL_SWIMING                  = 155,
    SKILL_2H_MACES                 = 160,
    SKILL_UNARMED                  = 162,
    SKILL_MARKSMANSHIP             = 163,
    SKILL_BLACKSMITHING            = 164,
    SKILL_LEATHERWORKING           = 165,
    SKILL_ALCHEMY                  = 171,
    SKILL_2H_AXES                  = 172,
    SKILL_DAGGERS                  = 173,
    SKILL_THROWN                   = 176,
    SKILL_HERBALISM                = 182,
    SKILL_GENERIC_DND              = 183,
    SKILL_RETRIBUTION              = 184,
    SKILL_COOKING                  = 185,
    SKILL_MINING                   = 186,
    SKILL_PET_IMP                  = 188,
    SKILL_PET_FELHUNTER            = 189,
    SKILL_TAILORING                = 197,
    SKILL_ENGINERING               = 202,
    SKILL_PET_SPIDER               = 203,
    SKILL_PET_VOIDWALKER           = 204,
    SKILL_PET_SUCCUBUS             = 205,
    SKILL_PET_INFERNAL             = 206,
    SKILL_PET_DOOMGUARD            = 207,
    SKILL_PET_WOLF                 = 208,
    SKILL_PET_CAT                  = 209,
    SKILL_PET_BEAR                 = 210,
    SKILL_PET_BOAR                 = 211,
    SKILL_PET_CROCILISK            = 212,
    SKILL_PET_CARRION_BIRD         = 213,
    SKILL_PET_CRAB                 = 214,
    SKILL_PET_GORILLA              = 215,
    SKILL_PET_RAPTOR               = 217,
    SKILL_PET_TALLSTRIDER          = 218,
    SKILL_RACIAL_UNDED             = 220,
    SKILL_CROSSBOWS                = 226,
    SKILL_WANDS                    = 228,
    SKILL_POLEARMS                 = 229,
    SKILL_PET_SCORPID              = 236,
    SKILL_ARCANE                   = 237,
    SKILL_PET_TURTLE               = 251,
    SKILL_ASSASSINATION            = 253,
    SKILL_FURY                     = 256,
    SKILL_PROTECTION               = 257,
    SKILL_PROTECTION2              = 267,
    SKILL_PET_TALENTS              = 270,
    SKILL_PLATE_MAIL               = 293,
    SKILL_LANG_GNOMISH             = 313,
    SKILL_LANG_TROLL               = 315,
    SKILL_ENCHANTING               = 333,
    SKILL_DEMONOLOGY               = 354,
    SKILL_AFFLICTION               = 355,
    SKILL_FISHING                  = 356,
    SKILL_ENHANCEMENT              = 373,
    SKILL_RESTORATION              = 374,
    SKILL_ELEMENTAL_COMBAT         = 375,
    SKILL_SKINNING                 = 393,
    SKILL_MAIL                     = 413,
    SKILL_LEATHER                  = 414,
    SKILL_CLOTH                    = 415,
    SKILL_SHIELD                   = 433,
    SKILL_FIST_WEAPONS             = 473,
    SKILL_RIDING_RAPTOR            = 533,
    SKILL_RIDING_MECHANOSTRIDER    = 553,
    SKILL_RIDING_UNDEAD_HORSE      = 554,
    SKILL_RESTORATION2             = 573,
    SKILL_BALANCE                  = 574,
    SKILL_DESTRUCTION              = 593,
    SKILL_HOLY2                    = 594,
    SKILL_DISCIPLINE               = 613,
    SKILL_LOCKPICKING              = 633,
    SKILL_PET_BAT                  = 653,
    SKILL_PET_HYENA                = 654,
    SKILL_PET_BIRD_OF_PREY         = 655,
    SKILL_PET_WIND_SERPENT         = 656,
    SKILL_LANG_GUTTERSPEAK         = 673,
    SKILL_RIDING_KODO              = 713,
    SKILL_RACIAL_TROLL             = 733,
    SKILL_RACIAL_GNOME             = 753,
    SKILL_RACIAL_HUMAN             = 754,
    SKILL_JEWELCRAFTING            = 755,
    SKILL_RACIAL_BLOODELF          = 756,
    SKILL_PET_EVENT_RC             = 758,
    SKILL_LANG_DRAENEI             = 759,
    SKILL_RACIAL_DRAENEI           = 760,
    SKILL_PET_FELGUARD             = 761,
    SKILL_RIDING                   = 762,
    SKILL_PET_DRAGONHAWK           = 763,
    SKILL_PET_NETHER_RAY           = 764,
    SKILL_PET_SPOREBAT             = 765,
    SKILL_PET_WARP_STALKER         = 766,
    SKILL_PET_RAVAGER              = 767,
    SKILL_PET_SERPENT              = 768,
    SKILL_INTERNAL                 = 769,
    SKILL_DK_BLOOD                 = 770,
    SKILL_DK_FROST                 = 771,
    SKILL_DK_UNHOLY                = 772,
    SKILL_INSCRIPTION              = 773,
    SKILL_PET_MOTH                 = 775,
    SKILL_RUNEFORGING              = 776,
    SKILL_MOUNTS                   = 777,
    SKILL_COMPANIONS               = 778,
    SKILL_PET_EXOTIC_CHIMAERA      = 780,
    SKILL_PET_EXOTIC_DEVILSAUR     = 781,
    SKILL_PET_GHOUL                = 782,
    SKILL_PET_EXOTIC_SILITHID      = 783,
    SKILL_PET_EXOTIC_WORM          = 784,
    SKILL_PET_WASP                 = 785,
    SKILL_PET_EXOTIC_RHINO         = 786,
    SKILL_PET_EXOTIC_CORE_HOUND    = 787,
    SKILL_PET_EXOTIC_SPIRIT_BEAST  = 788
};

#define MAX_SKILL_TYPE               789

inline SkillType SkillByLockType(LockType locktype)
{
    switch(locktype)
    {
        case LOCKTYPE_PICKLOCK:    return SKILL_LOCKPICKING;
        case LOCKTYPE_HERBALISM:   return SKILL_HERBALISM;
        case LOCKTYPE_MINING:      return SKILL_MINING;
        case LOCKTYPE_FISHING:     return SKILL_FISHING;
        case LOCKTYPE_INSCRIPTION: return SKILL_INSCRIPTION;
        default: break;
    }
    return SKILL_NONE;
}

inline uint32 SkillByQuestSort(int32 QuestSort)
{
    switch(QuestSort)
    {
        case QUEST_SORT_HERBALISM:      return SKILL_HERBALISM;
        case QUEST_SORT_FISHING:        return SKILL_FISHING;
        case QUEST_SORT_BLACKSMITHING:  return SKILL_BLACKSMITHING;
        case QUEST_SORT_ALCHEMY:        return SKILL_ALCHEMY;
        case QUEST_SORT_LEATHERWORKING: return SKILL_LEATHERWORKING;
        case QUEST_SORT_ENGINERING:     return SKILL_ENGINERING;
        case QUEST_SORT_TAILORING:      return SKILL_TAILORING;
        case QUEST_SORT_COOKING:        return SKILL_COOKING;
        case QUEST_SORT_FIRST_AID:      return SKILL_FIRST_AID;
        case QUEST_SORT_JEWELCRAFTING:  return SKILL_JEWELCRAFTING;
        case QUEST_SORT_INSCRIPTION:    return SKILL_INSCRIPTION;
    }
    return 0;
}

enum SkillCategory
{
    SKILL_CATEGORY_ATTRIBUTES    = 5,
    SKILL_CATEGORY_WEAPON        = 6,
    SKILL_CATEGORY_CLASS         = 7,
    SKILL_CATEGORY_ARMOR         = 8,
    SKILL_CATEGORY_SECONDARY     = 9,                       // secondary professions
    SKILL_CATEGORY_LANGUAGES     = 10,
    SKILL_CATEGORY_PROFESSION    = 11,                      // primary professions
    SKILL_CATEGORY_GENERIC       = 12
};

enum TotemCategory
{
    TC_SKINNING_SKIFE_OLD          = 1,
    TC_EARTH_TOTEM                 = 2,
    TC_AIR_TOTEM                   = 3,
    TC_FIRE_TOTEM                  = 4,
    TC_WATER_TOTEM                 = 5,
    TC_COPPER_ROD                  = 6,
    TC_SILVER_ROD                  = 7,
    TC_GOLDEN_ROD                  = 8,
    TC_TRUESILVER_ROD              = 9,
    TC_ARCANITE_ROD                = 10,
    TC_MINING_PICK_OLD             = 11,
    TC_PHILOSOPHERS_STONE          = 12,
    TC_BLACKSMITH_HAMMER_OLD       = 13,
    TC_ARCLIGHT_SPANNER            = 14,
    TC_GYROMATIC_MA                = 15,
    TC_MASTER_TOTEM                = 21,
    TC_FEL_IRON_ROD                = 41,
    TC_ADAMANTITE_ROD              = 62,
    TC_ETERNIUM_ROD                = 63,
    TC_HOLLOW_QUILL                = 81,
    TC_RUNED_AZURITE_ROD           = 101,
    TC_VIRTUOSO_INKING_SET         = 121,
    TC_DRUMS                       = 141,
    TC_GNOMISH_ARMY_KNIFE          = 161,
    TC_BLACKSMITH_HAMMER           = 162,
    TC_MINING_PICK                 = 165,
    TC_SKINNING_KNIFE              = 166,
    TC_HAMMER_PICK                 = 167,
    TC_BLADED_PICKAXE              = 168,
    TC_FLINT_AND_TINDER            = 169,
    TC_RUNED_COBALT_ROD            = 189,
    TC_RUNED_TITANIUM_ROD          = 190
};

enum UnitDynFlags
{
    UNIT_DYNFLAG_NONE                       = 0x0000,
    UNIT_DYNFLAG_LOOTABLE                   = 0x0001,
    UNIT_DYNFLAG_TRACK_UNIT                 = 0x0002,
    UNIT_DYNFLAG_TAPPED                     = 0x0004,       // Lua_UnitIsTapped
    UNIT_DYNFLAG_TAPPED_BY_PLAYER           = 0x0008,       // Lua_UnitIsTappedByPlayer
    UNIT_DYNFLAG_SPECIALINFO                = 0x0010,
    UNIT_DYNFLAG_DEAD                       = 0x0020,
    UNIT_DYNFLAG_REFER_A_FRIEND             = 0x0040,
    UNIT_DYNFLAG_TAPPED_BY_ALL_THREAT_LIST  = 0x0080        // Lua_UnitIsTappedByAllThreatList
};

enum CorpseDynFlags
{
    CORPSE_DYNFLAG_LOOTABLE        = 0x0001
};

// Passive Spell codes explicit used in code
#define SPELL_ID_GENERIC_LEARN                  483
#define SPELL_ID_GENERIC_LEARN_PET              55884       // used for learning mounts and companions
#define SPELL_ID_PASSIVE_BATTLE_STANCE          2457
#define SPELL_ID_PASSIVE_RESURRECTION_SICKNESS  15007
#define SPELL_ID_WEAPON_SWITCH_COOLDOWN_1_5s    6119
#define SPELL_ID_WEAPON_SWITCH_COOLDOWN_1_0s    6123
#define SPELL_ID_AUTOSHOT                       75          // used for checks in other spells interruption
#define SPELL_ID_SHADOWMELD                     58984       // used for check ignore stealth stance state

enum WeatherType
{
    WEATHER_TYPE_FINE       = 0,
    WEATHER_TYPE_RAIN       = 1,
    WEATHER_TYPE_SNOW       = 2,
    WEATHER_TYPE_STORM      = 3,
    WEATHER_TYPE_THUNDERS   = 86,
    WEATHER_TYPE_BLACKRAIN  = 90
};

#define MAX_WEATHER_TYPE 4

enum ChatMsg
{
    CHAT_MSG_ADDON                  = 0xFFFFFFFF,
    CHAT_MSG_SYSTEM                 = 0x00,
    CHAT_MSG_SAY                    = 0x01,
    CHAT_MSG_PARTY                  = 0x02,
    CHAT_MSG_RAID                   = 0x03,
    CHAT_MSG_GUILD                  = 0x04,
    CHAT_MSG_OFFICER                = 0x05,
    CHAT_MSG_YELL                   = 0x06,
    CHAT_MSG_WHISPER                = 0x07,
    CHAT_MSG_WHISPER_FOREIGN        = 0x08,
    CHAT_MSG_WHISPER_INFORM         = 0x09,
    CHAT_MSG_EMOTE                  = 0x0A,
    CHAT_MSG_TEXT_EMOTE             = 0x0B,
    CHAT_MSG_MONSTER_SAY            = 0x0C,
    CHAT_MSG_MONSTER_PARTY          = 0x0D,
    CHAT_MSG_MONSTER_YELL           = 0x0E,
    CHAT_MSG_MONSTER_WHISPER        = 0x0F,
    CHAT_MSG_MONSTER_EMOTE          = 0x10,
    CHAT_MSG_CHANNEL                = 0x11,
    CHAT_MSG_CHANNEL_JOIN           = 0x12,
    CHAT_MSG_CHANNEL_LEAVE          = 0x13,
    CHAT_MSG_CHANNEL_LIST           = 0x14,
    CHAT_MSG_CHANNEL_NOTICE         = 0x15,
    CHAT_MSG_CHANNEL_NOTICE_USER    = 0x16,
    CHAT_MSG_AFK                    = 0x17,
    CHAT_MSG_DND                    = 0x18,
    CHAT_MSG_IGNORED                = 0x19,
    CHAT_MSG_SKILL                  = 0x1A,
    CHAT_MSG_LOOT                   = 0x1B,
    CHAT_MSG_MONEY                  = 0x1C,
    CHAT_MSG_OPENING                = 0x1D,
    CHAT_MSG_TRADESKILLS            = 0x1E,
    CHAT_MSG_PET_INFO               = 0x1F,
    CHAT_MSG_COMBAT_MISC_INFO       = 0x20,
    CHAT_MSG_COMBAT_XP_GAIN         = 0x21,
    CHAT_MSG_COMBAT_HONOR_GAIN      = 0x22,
    CHAT_MSG_COMBAT_FACTION_CHANGE  = 0x23,
    CHAT_MSG_BG_SYSTEM_NEUTRAL      = 0x24,
    CHAT_MSG_BG_SYSTEM_ALLIANCE     = 0x25,
    CHAT_MSG_BG_SYSTEM_HORDE        = 0x26,
    CHAT_MSG_RAID_LEADER            = 0x27,
    CHAT_MSG_RAID_WARNING           = 0x28,
    CHAT_MSG_RAID_BOSS_EMOTE        = 0x29,
    CHAT_MSG_RAID_BOSS_WHISPER      = 0x2A,
    CHAT_MSG_FILTERED               = 0x2B,
    CHAT_MSG_BATTLEGROUND           = 0x2C,
    CHAT_MSG_BATTLEGROUND_LEADER    = 0x2D,
    CHAT_MSG_RESTRICTED             = 0x2E,
    CHAT_MSG_BATTLENET              = 0x2F,
    CHAT_MSG_ACHIEVEMENT            = 0x30,
    CHAT_MSG_GUILD_ACHIEVEMENT      = 0x31,
    CHAT_MSG_ARENA_POINTS           = 0x32,
    CHAT_MSG_PARTY_LEADER           = 0x33
};

#define MAX_CHAT_MSG_TYPE 0x34

enum ChatLinkColors
{
    CHAT_LINK_COLOR_TRADE       = 0xffffd000,   // orange
    CHAT_LINK_COLOR_TALENT      = 0xff4e96f7,   // blue
    CHAT_LINK_COLOR_SPELL       = 0xff71d5ff,   // bright blue
    CHAT_LINK_COLOR_ENCHANT     = 0xffffd000,   // orange
    CHAT_LINK_COLOR_ACHIEVEMENT = 0xffffff00,
    CHAT_LINK_COLOR_GLYPH       = 0xff66bbff
};

// Values from ItemPetFood (power of (value-1) used for compare with CreatureFamilyEntry.petDietMask
enum PetDiet
{
    PET_DIET_MEAT     = 1,
    PET_DIET_FISH     = 2,
    PET_DIET_CHEESE   = 3,
    PET_DIET_BREAD    = 4,
    PET_DIET_FUNGAS   = 5,
    PET_DIET_FRUIT    = 6,
    PET_DIET_RAW_MEAT = 7,
    PET_DIET_RAW_FISH = 8
};

#define MAX_PET_DIET 9

#define CHAIN_SPELL_JUMP_RADIUS 10

// Max values for Guild & Guild Bank
#define GUILD_BANK_MAX_TABS         6                       // send by client for money log also
#define GUILD_BANK_MAX_SLOTS        98
#define GUILD_BANK_MAX_LOGS         25
#define GUILD_BANK_MONEY_LOGS_TAB   100                     // used for money log in DB
#define GUILD_EVENTLOG_MAX_RECORDS  100
#define GUILD_RANKS_MIN_COUNT       5
#define GUILD_RANKS_MAX_COUNT       10

enum AiReaction
{
    AI_REACTION_ALERT    = 0,                               // pre-aggro (used in client packet handler)
    AI_REACTION_FRIENDLY = 1,                               // (NOT used in client packet handler)
    AI_REACTION_HOSTILE  = 2,                               // sent on every attack, triggers aggro sound (used in client packet handler)
    AI_REACTION_AFRAID   = 3,                               // seen for polymorph (when AI not in control of self?) (NOT used in client packet handler)
    AI_REACTION_DESTROY  = 4,                               // used on object destroy (NOT used in client packet handler)
};

// Diminishing Returns Types
enum DiminishingReturnsType
{
    DRTYPE_NONE         = 0,                                // this spell is not diminished, but may have limited it's duration to 10s
    DRTYPE_PLAYER       = 1,                                // this spell is diminished only when applied on players
    DRTYPE_ALL          = 2                                 // this spell is diminished in every case
};

// Diminishing Return Groups
enum DiminishingGroup
{
    // Common Groups
    DIMINISHING_NONE,
    DIMINISHING_CONTROL_STUN,                               // Player Controlled stuns
    DIMINISHING_TRIGGER_STUN,                               // By aura proced stuns, usualy chance on hit talents
    DIMINISHING_CONTROL_ROOT,                               // Immobilizing effects from casted spells
    DIMINISHING_TRIGGER_ROOT,                               // Immobilizing effects from triggered spells like Frostbite
    // Shared Class Specific
    DIMINISHING_FEAR_CHARM_BLIND,                           // Fears & charm and Blind
    DIMINISHING_DISORIENT,
    DIMINISHING_HORROR,
    // Druid Specific
    DIMINISHING_CYCLONE,
    DIMINISHING_CHEAPSHOT_POUNCE,
    DIMINISHING_DISARM,                                     // From 2.3.0
    DIMINISHING_SILENCE,                                    // From 2.3.0
    DIMINISHING_FREEZE_SLEEP,                               // Hunter's Freezing Trap
    DIMINISHING_BANISH,
    // Other
    // Don't Diminish, but limit duration to 10s
    DIMINISHING_LIMITONLY
};

enum ResponseCodes
{
    RESPONSE_SUCCESS                                       = 0x00,
    RESPONSE_FAILURE                                       = 0x01,
    RESPONSE_CANCELLED                                     = 0x02,
    RESPONSE_DISCONNECTED                                  = 0x03,
    RESPONSE_FAILED_TO_CONNECT                             = 0x04,
    RESPONSE_CONNECTED                                     = 0x05,
    RESPONSE_VERSION_MISMATCH                              = 0x06,

    CSTATUS_CONNECTING                                     = 0x07,
    CSTATUS_NEGOTIATING_SECURITY                           = 0x08,
    CSTATUS_NEGOTIATION_COMPLETE                           = 0x09,
    CSTATUS_NEGOTIATION_FAILED                             = 0x0A,
    CSTATUS_AUTHENTICATING                                 = 0x0B,

    AUTH_OK                                                = 0x0C,
    AUTH_FAILED                                            = 0x0D,
    AUTH_REJECT                                            = 0x0E,
    AUTH_BAD_SERVER_PROOF                                  = 0x0F,
    AUTH_UNAVAILABLE                                       = 0x10,
    AUTH_SYSTEM_ERROR                                      = 0x11,
    AUTH_BILLING_ERROR                                     = 0x12,
    AUTH_BILLING_EXPIRED                                   = 0x13,
    AUTH_VERSION_MISMATCH                                  = 0x14,
    AUTH_UNKNOWN_ACCOUNT                                   = 0x15,
    AUTH_INCORRECT_PASSWORD                                = 0x16,
    AUTH_SESSION_EXPIRED                                   = 0x17,
    AUTH_SERVER_SHUTTING_DOWN                              = 0x18,
    AUTH_ALREADY_LOGGING_IN                                = 0x19,
    AUTH_LOGIN_SERVER_NOT_FOUND                            = 0x1A,
    AUTH_WAIT_QUEUE                                        = 0x1B,
    AUTH_BANNED                                            = 0x1C,
    AUTH_ALREADY_ONLINE                                    = 0x1D,
    AUTH_NO_TIME                                           = 0x1E,
    AUTH_DB_BUSY                                           = 0x1F,
    AUTH_SUSPENDED                                         = 0x20,
    AUTH_PARENTAL_CONTROL                                  = 0x21,
    AUTH_LOCKED_ENFORCED                                   = 0x22,

    REALM_LIST_IN_PROGRESS                                 = 0x23,
    REALM_LIST_SUCCESS                                     = 0x24,
    REALM_LIST_FAILED                                      = 0x25,
    REALM_LIST_INVALID                                     = 0x26,
    REALM_LIST_REALM_NOT_FOUND                             = 0x27,

    ACCOUNT_CREATE_IN_PROGRESS                             = 0x28,
    ACCOUNT_CREATE_SUCCESS                                 = 0x29,
    ACCOUNT_CREATE_FAILED                                  = 0x2A,

    CHAR_LIST_RETRIEVING                                   = 0x2B,
    CHAR_LIST_RETRIEVED                                    = 0x2C,
    CHAR_LIST_FAILED                                       = 0x2D,

    CHAR_CREATE_IN_PROGRESS                                = 0x2E,
    CHAR_CREATE_SUCCESS                                    = 0x2F,
    CHAR_CREATE_ERROR                                      = 0x30,
    CHAR_CREATE_FAILED                                     = 0x31,
    CHAR_CREATE_NAME_IN_USE                                = 0x32,
    CHAR_CREATE_DISABLED                                   = 0x33,
    CHAR_CREATE_PVP_TEAMS_VIOLATION                        = 0x34,
    CHAR_CREATE_SERVER_LIMIT                               = 0x35,
    CHAR_CREATE_ACCOUNT_LIMIT                              = 0x36,
    CHAR_CREATE_SERVER_QUEUE                               = 0x37,
    CHAR_CREATE_ONLY_EXISTING                              = 0x38,
    CHAR_CREATE_EXPANSION                                  = 0x39,
    CHAR_CREATE_EXPANSION_CLASS                            = 0x3A,
    CHAR_CREATE_LEVEL_REQUIREMENT                          = 0x3B,
    CHAR_CREATE_UNIQUE_CLASS_LIMIT                         = 0x3C,
    CHAR_CREATE_CHARACTER_IN_GUILD                         = 0x3D,
    CHAR_CREATE_RESTRICTED_RACECLASS                       = 0x3E,
    CHAR_CREATE_CHARACTER_CHOOSE_RACE                      = 0x3F,
    CHAR_CREATE_CHARACTER_ARENA_LEADER                     = 0x40,
    CHAR_CREATE_CHARACTER_DELETE_MAIL                      = 0x41,
    CHAR_CREATE_CHARACTER_SWAP_FACTION                     = 0x42,
    CHAR_CREATE_CHARACTER_RACE_ONLY                        = 0x43,
    CHAR_CREATE_CHARACTER_GOLD_LIMIT                       = 0x44,
    CHAR_CREATE_FORCE_LOGIN                                = 0x45,

    CHAR_DELETE_IN_PROGRESS                                = 0x46,
    CHAR_DELETE_SUCCESS                                    = 0x47,
    CHAR_DELETE_FAILED                                     = 0x48,
    CHAR_DELETE_FAILED_LOCKED_FOR_TRANSFER                 = 0x49,
    CHAR_DELETE_FAILED_GUILD_LEADER                        = 0x4A,
    CHAR_DELETE_FAILED_ARENA_CAPTAIN                       = 0x4B,

    CHAR_LOGIN_IN_PROGRESS                                 = 0x4C,
    CHAR_LOGIN_SUCCESS                                     = 0x4D,
    CHAR_LOGIN_NO_WORLD                                    = 0x4E,
    CHAR_LOGIN_DUPLICATE_CHARACTER                         = 0x4F,
    CHAR_LOGIN_NO_INSTANCES                                = 0x50,
    CHAR_LOGIN_FAILED                                      = 0x51,
    CHAR_LOGIN_DISABLED                                    = 0x52,
    CHAR_LOGIN_NO_CHARACTER                                = 0x53,
    CHAR_LOGIN_LOCKED_FOR_TRANSFER                         = 0x54,
    CHAR_LOGIN_LOCKED_BY_BILLING                           = 0x55,
    CHAR_LOGIN_LOCKED_BY_MOBILE_AH                         = 0x56,

    CHAR_NAME_SUCCESS                                      = 0x57,
    CHAR_NAME_FAILURE                                      = 0x58,
    CHAR_NAME_NO_NAME                                      = 0x59,
    CHAR_NAME_TOO_SHORT                                    = 0x5A,
    CHAR_NAME_TOO_LONG                                     = 0x5B,
    CHAR_NAME_INVALID_CHARACTER                            = 0x5C,
    CHAR_NAME_MIXED_LANGUAGES                              = 0x5D,
    CHAR_NAME_PROFANE                                      = 0x5E,
    CHAR_NAME_RESERVED                                     = 0x5F,
    CHAR_NAME_INVALID_APOSTROPHE                           = 0x60,
    CHAR_NAME_MULTIPLE_APOSTROPHES                         = 0x61,
    CHAR_NAME_THREE_CONSECUTIVE                            = 0x62,
    CHAR_NAME_INVALID_SPACE                                = 0x63,
    CHAR_NAME_CONSECUTIVE_SPACES                           = 0x64,
    CHAR_NAME_RUSSIAN_CONSECUTIVE_SILENT_CHARACTERS        = 0x65,
    CHAR_NAME_RUSSIAN_SILENT_CHARACTER_AT_BEGINNING_OR_END = 0x66,
    CHAR_NAME_DECLENSION_DOESNT_MATCH_BASE_NAME            = 0x67
};


/// Ban function modes
enum BanMode
{
    BAN_ACCOUNT,
    BAN_CHARACTER,
    BAN_IP
};

/// Ban function return codes
enum BanReturn
{
    BAN_SUCCESS,
    BAN_SYNTAX_ERROR,
    BAN_NOTFOUND
};

// indexes of BattlemasterList.dbc
enum BattleGroundTypeId
{
    BATTLEGROUND_TYPE_NONE     = 0,
    BATTLEGROUND_AV            = 1,
    BATTLEGROUND_WS            = 2,
    BATTLEGROUND_AB            = 3,
    BATTLEGROUND_NA            = 4,
    BATTLEGROUND_BE            = 5,
    BATTLEGROUND_AA            = 6,
    BATTLEGROUND_EY            = 7,
    BATTLEGROUND_RL            = 8,
    BATTLEGROUND_SA            = 9,
    BATTLEGROUND_DS            = 10,
    BATTLEGROUND_RV            = 11,
    BATTLEGROUND_IC            = 30,
    BATTLEGROUND_ABG           = 32
};
#define MAX_BATTLEGROUND_TYPE_ID 33

enum MailResponseType
{
    MAIL_SEND               = 0,
    MAIL_MONEY_TAKEN        = 1,
    MAIL_ITEM_TAKEN         = 2,
    MAIL_RETURNED_TO_SENDER = 3,
    MAIL_DELETED            = 4,
    MAIL_MADE_PERMANENT     = 5
};

enum MailResponseResult
{
    MAIL_OK                            = 0,
    MAIL_ERR_EQUIP_ERROR               = 1,
    MAIL_ERR_CANNOT_SEND_TO_SELF       = 2,
    MAIL_ERR_NOT_ENOUGH_MONEY          = 3,
    MAIL_ERR_RECIPIENT_NOT_FOUND       = 4,
    MAIL_ERR_NOT_YOUR_TEAM             = 5,
    MAIL_ERR_INTERNAL_ERROR            = 6,
    MAIL_ERR_DISABLED_FOR_TRIAL_ACC    = 14,
    MAIL_ERR_RECIPIENT_CAP_REACHED     = 15,
    MAIL_ERR_CANT_SEND_WRAPPED_COD     = 16,
    MAIL_ERR_MAIL_AND_CHAT_SUSPENDED   = 17,
    MAIL_ERR_TOO_MANY_ATTACHMENTS      = 18,
    MAIL_ERR_MAIL_ATTACHMENT_INVALID   = 19,
    MAIL_ERR_ITEM_HAS_EXPIRED          = 21,
};

// reasons for why pet tame may fail
// in fact, these are also used elsewhere
enum PetTameFailureReason
{
    PETTAME_INVALIDCREATURE         = 1,
    PETTAME_TOOMANY                 = 2,
    PETTAME_CREATUREALREADYOWNED    = 3,
    PETTAME_NOTTAMEABLE             = 4,
    PETTAME_ANOTHERSUMMONACTIVE     = 5,
    PETTAME_UNITSCANTTAME           = 6,
    PETTAME_NOPETAVAILABLE          = 7,                    // not used in taming
    PETTAME_INTERNALERROR           = 8,
    PETTAME_TOOHIGHLEVEL            = 9,
    PETTAME_DEAD                    = 10,                   // not used in taming
    PETTAME_NOTDEAD                 = 11,                   // not used in taming
    PETTAME_CANTCONTROLEXOTIC       = 12,                   // 3.x
    PETTAME_UNKNOWNERROR            = 13
};

// Stored in SummonProperties.dbc with slot+1 values
enum TotemSlot
{
    TOTEM_SLOT_FIRE   = 0,
    TOTEM_SLOT_EARTH  = 1,
    TOTEM_SLOT_WATER  = 2,
    TOTEM_SLOT_AIR    = 3,
};

#define TOTEM_SLOT_NONE 255                                 // custom value for no slot case

#define MAX_TOTEM_SLOT  4

// we need to stick to 1 version or half of the stuff will work for someone
// others will not and opposite
// will only support WoW, WoW:TBC and WoW:WotLK 3.3.2 client build 11403...

#define EXPECTED_MANGOSD_CLIENT_BUILD        {11403, 0}

// max supported expansion level in mangosd
// NOTE: not set it more that supported by targeted client version with all expansions installed
// account with expansion > client supported will rejected at connection by client
// because if client receive unsupported expansion level it think
// that it not have expansion installed and reject
#define MAX_EXPANSION 2



enum OBJECT_UPDATE_TYPE
{
    UPDATETYPE_VALUES               = 0,
    UPDATETYPE_MOVEMENT             = 1,
    UPDATETYPE_CREATE_OBJECT        = 2,
    UPDATETYPE_CREATE_OBJECT2       = 3,
    UPDATETYPE_OUT_OF_RANGE_OBJECTS = 4,
    UPDATETYPE_NEAR_OBJECTS         = 5
};

enum OBJECT_UPDATE_FLAGS
{
    UPDATEFLAG_NONE                 = 0x0000,
    UPDATEFLAG_SELF                 = 0x0001,
    UPDATEFLAG_TRANSPORT            = 0x0002,
    UPDATEFLAG_HAS_ATTACKING_TARGET = 0x0004,
    UPDATEFLAG_LOWGUID              = 0x0008,
    UPDATEFLAG_HIGHGUID             = 0x0010,
    UPDATEFLAG_LIVING               = 0x0020,
    UPDATEFLAG_HAS_POSITION         = 0x0040,
    UPDATEFLAG_VEHICLE              = 0x0080,
    UPDATEFLAG_POSITION             = 0x0100,
    UPDATEFLAG_ROTATION             = 0x0200
};

enum AccountDataType
{
    GLOBAL_CONFIG_CACHE             = 0,                    // 0x01 g
    PER_CHARACTER_CONFIG_CACHE      = 1,                    // 0x02 p
    GLOBAL_BINDINGS_CACHE           = 2,                    // 0x04 g
    PER_CHARACTER_BINDINGS_CACHE    = 3,                    // 0x08 p
    GLOBAL_MACROS_CACHE             = 4,                    // 0x10 g
    PER_CHARACTER_MACROS_CACHE      = 5,                    // 0x20 p
    PER_CHARACTER_LAYOUT_CACHE      = 6,                    // 0x40 p
    PER_CHARACTER_CHAT_CACHE        = 7,                    // 0x80 p
    NUM_ACCOUNT_DATA_TYPES          = 8
};

#define MAXGROUPSIZE 5
#define MAXRAIDSIZE 40
#define TARGETICONCOUNT 8

enum RollVote
{
    PASS              = 0,
    NEED              = 1,
    GREED             = 2,
    DISENCHANT        = 3,
    NOT_EMITED_YET    = 4,
    NOT_VALID         = 5
};

enum GroupMemberOnlineStatus
{
    MEMBER_STATUS_OFFLINE   = 0x0000,
    MEMBER_STATUS_ONLINE    = 0x0001,
    MEMBER_STATUS_PVP       = 0x0002,
    MEMBER_STATUS_UNK0      = 0x0004,                       // dead? (health=0)
    MEMBER_STATUS_UNK1      = 0x0008,                       // ghost? (health=1)
    MEMBER_STATUS_UNK2      = 0x0010,                       // never seen
    MEMBER_STATUS_UNK3      = 0x0020,                       // never seen
    MEMBER_STATUS_UNK4      = 0x0040,                       // appears with dead and ghost flags
    MEMBER_STATUS_UNK5      = 0x0080,                       // never seen
};

enum GroupType                                              // group type flags?
{
    GROUPTYPE_NORMAL = 0x00,
    GROUPTYPE_BG     = 0x01,
    GROUPTYPE_RAID   = 0x02,
    GROUPTYPE_BGRAID = GROUPTYPE_BG | GROUPTYPE_RAID,       // mask
    // 0x04?
    GROUPTYPE_LFD    = 0x08,
    // 0x10, leave/change group?, I saw this flag when leaving group and after leaving BG while in group
};

enum GroupUpdateFlags
{
    GROUP_UPDATE_FLAG_NONE              = 0x00000000,       // nothing
    GROUP_UPDATE_FLAG_STATUS            = 0x00000001,       // uint16, flags
    GROUP_UPDATE_FLAG_CUR_HP            = 0x00000002,       // uint32
    GROUP_UPDATE_FLAG_MAX_HP            = 0x00000004,       // uint32
    GROUP_UPDATE_FLAG_POWER_TYPE        = 0x00000008,       // uint8
    GROUP_UPDATE_FLAG_CUR_POWER         = 0x00000010,       // uint16
    GROUP_UPDATE_FLAG_MAX_POWER         = 0x00000020,       // uint16
    GROUP_UPDATE_FLAG_LEVEL             = 0x00000040,       // uint16
    GROUP_UPDATE_FLAG_ZONE              = 0x00000080,       // uint16
    GROUP_UPDATE_FLAG_POSITION          = 0x00000100,       // uint16, uint16
    GROUP_UPDATE_FLAG_AURAS             = 0x00000200,       // uint64 mask, for each bit set uint32 spellid + uint8 unk
    GROUP_UPDATE_FLAG_PET_GUID          = 0x00000400,       // uint64 pet guid
    GROUP_UPDATE_FLAG_PET_NAME          = 0x00000800,       // pet name, NULL terminated string
    GROUP_UPDATE_FLAG_PET_MODEL_ID      = 0x00001000,       // uint16, model id
    GROUP_UPDATE_FLAG_PET_CUR_HP        = 0x00002000,       // uint32 pet cur health
    GROUP_UPDATE_FLAG_PET_MAX_HP        = 0x00004000,       // uint32 pet max health
    GROUP_UPDATE_FLAG_PET_POWER_TYPE    = 0x00008000,       // uint8 pet power type
    GROUP_UPDATE_FLAG_PET_CUR_POWER     = 0x00010000,       // uint16 pet cur power
    GROUP_UPDATE_FLAG_PET_MAX_POWER     = 0x00020000,       // uint16 pet max power
    GROUP_UPDATE_FLAG_PET_AURAS         = 0x00040000,       // uint64 mask, for each bit set uint32 spellid + uint8 unk, pet auras...
    GROUP_UPDATE_FLAG_VEHICLE_SEAT      = 0x00080000,       // uint32 vehicle_seat_id (index from VehicleSeat.dbc)
    GROUP_UPDATE_PET                    = 0x0007FC00,       // all pet flags
    GROUP_UPDATE_FULL                   = 0x0007FFFF,       // all known flags
};

#define GROUP_UPDATE_FLAGS_COUNT          20
#define MAX_AURAS 64

enum AURA_FLAGS
{
    AFLAG_NONE              = 0x00,
    AFLAG_EFF_INDEX_0       = 0x01,
    AFLAG_EFF_INDEX_1       = 0x02,
    AFLAG_EFF_INDEX_2       = 0x04,
    AFLAG_NOT_CASTER        = 0x08,
    AFLAG_POSITIVE          = 0x10,
    AFLAG_DURATION          = 0x20,
    AFLAG_UNK2              = 0x40,
    AFLAG_NEGATIVE          = 0x80
};

//m_schoolAbsorb
enum DAMAGE_ABSORB_TYPE
{
    ALL_DAMAGE_ABSORB       = -2,
    ONLY_MAGIC_ABSORB       = -1,
};

enum AuraType
{
    SPELL_AURA_NONE = 0,
    SPELL_AURA_BIND_SIGHT = 1,
    SPELL_AURA_MOD_POSSESS = 2,
    SPELL_AURA_PERIODIC_DAMAGE = 3,
    SPELL_AURA_DUMMY = 4,
    SPELL_AURA_MOD_CONFUSE = 5,
    SPELL_AURA_MOD_CHARM = 6,
    SPELL_AURA_MOD_FEAR = 7,
    SPELL_AURA_PERIODIC_HEAL = 8,
    SPELL_AURA_MOD_ATTACKSPEED = 9,
    SPELL_AURA_MOD_THREAT = 10,
    SPELL_AURA_MOD_TAUNT = 11,
    SPELL_AURA_MOD_STUN = 12,
    SPELL_AURA_MOD_DAMAGE_DONE = 13,
    SPELL_AURA_MOD_DAMAGE_TAKEN = 14,
    SPELL_AURA_DAMAGE_SHIELD = 15,
    SPELL_AURA_MOD_STEALTH = 16,
    SPELL_AURA_MOD_STEALTH_DETECT = 17,
    SPELL_AURA_MOD_INVISIBILITY = 18,
    SPELL_AURA_MOD_INVISIBILITY_DETECTION = 19,
    SPELL_AURA_OBS_MOD_HEALTH = 20,                         //20,21 unofficial
    SPELL_AURA_OBS_MOD_MANA = 21,
    SPELL_AURA_MOD_RESISTANCE = 22,
    SPELL_AURA_PERIODIC_TRIGGER_SPELL = 23,
    SPELL_AURA_PERIODIC_ENERGIZE = 24,
    SPELL_AURA_MOD_PACIFY = 25,
    SPELL_AURA_MOD_ROOT = 26,
    SPELL_AURA_MOD_SILENCE = 27,
    SPELL_AURA_REFLECT_SPELLS = 28,
    SPELL_AURA_MOD_STAT = 29,
    SPELL_AURA_MOD_SKILL = 30,
    SPELL_AURA_MOD_INCREASE_SPEED = 31,
    SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED = 32,
    SPELL_AURA_MOD_DECREASE_SPEED = 33,
    SPELL_AURA_MOD_INCREASE_HEALTH = 34,
    SPELL_AURA_MOD_INCREASE_ENERGY = 35,
    SPELL_AURA_MOD_SHAPESHIFT = 36,
    SPELL_AURA_EFFECT_IMMUNITY = 37,
    SPELL_AURA_STATE_IMMUNITY = 38,
    SPELL_AURA_SCHOOL_IMMUNITY = 39,
    SPELL_AURA_DAMAGE_IMMUNITY = 40,
    SPELL_AURA_DISPEL_IMMUNITY = 41,
    SPELL_AURA_PROC_TRIGGER_SPELL = 42,
    SPELL_AURA_PROC_TRIGGER_DAMAGE = 43,
    SPELL_AURA_TRACK_CREATURES = 44,
    SPELL_AURA_TRACK_RESOURCES = 45,
    SPELL_AURA_46 = 46,                                     // Ignore all Gear test spells
    SPELL_AURA_MOD_PARRY_PERCENT = 47,
    SPELL_AURA_48 = 48,                                     // One periodic spell
    SPELL_AURA_MOD_DODGE_PERCENT = 49,
    SPELL_AURA_MOD_CRITICAL_HEALING_AMOUNT = 50,
    SPELL_AURA_MOD_BLOCK_PERCENT = 51,
    SPELL_AURA_MOD_CRIT_PERCENT = 52,
    SPELL_AURA_PERIODIC_LEECH = 53,
    SPELL_AURA_MOD_HIT_CHANCE = 54,
    SPELL_AURA_MOD_SPELL_HIT_CHANCE = 55,
    SPELL_AURA_TRANSFORM = 56,
    SPELL_AURA_MOD_SPELL_CRIT_CHANCE = 57,
    SPELL_AURA_MOD_INCREASE_SWIM_SPEED = 58,
    SPELL_AURA_MOD_DAMAGE_DONE_CREATURE = 59,
    SPELL_AURA_MOD_PACIFY_SILENCE = 60,
    SPELL_AURA_MOD_SCALE = 61,
    SPELL_AURA_PERIODIC_HEALTH_FUNNEL = 62,
    SPELL_AURA_63 = 63,                                     // old SPELL_AURA_PERIODIC_MANA_FUNNEL
    SPELL_AURA_PERIODIC_MANA_LEECH = 64,
    SPELL_AURA_MOD_CASTING_SPEED_NOT_STACK = 65,
    SPELL_AURA_FEIGN_DEATH = 66,
    SPELL_AURA_MOD_DISARM = 67,
    SPELL_AURA_MOD_STALKED = 68,
    SPELL_AURA_SCHOOL_ABSORB = 69,
    SPELL_AURA_EXTRA_ATTACKS = 70,
    SPELL_AURA_MOD_SPELL_CRIT_CHANCE_SCHOOL = 71,
    SPELL_AURA_MOD_POWER_COST_SCHOOL_PCT = 72,
    SPELL_AURA_MOD_POWER_COST_SCHOOL = 73,
    SPELL_AURA_REFLECT_SPELLS_SCHOOL = 74,
    SPELL_AURA_MOD_LANGUAGE = 75,
    SPELL_AURA_FAR_SIGHT = 76,
    SPELL_AURA_MECHANIC_IMMUNITY = 77,
    SPELL_AURA_MOUNTED = 78,
    SPELL_AURA_MOD_DAMAGE_PERCENT_DONE = 79,
    SPELL_AURA_MOD_PERCENT_STAT = 80,
    SPELL_AURA_SPLIT_DAMAGE_PCT = 81,
    SPELL_AURA_WATER_BREATHING = 82,
    SPELL_AURA_MOD_BASE_RESISTANCE = 83,
    SPELL_AURA_MOD_REGEN = 84,
    SPELL_AURA_MOD_POWER_REGEN = 85,
    SPELL_AURA_CHANNEL_DEATH_ITEM = 86,
    SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN = 87,
    SPELL_AURA_MOD_HEALTH_REGEN_PERCENT = 88,
    SPELL_AURA_PERIODIC_DAMAGE_PERCENT = 89,
    SPELL_AURA_90 = 90,                                     // old SPELL_AURA_MOD_RESIST_CHANCE
    SPELL_AURA_MOD_DETECT_RANGE = 91,
    SPELL_AURA_PREVENTS_FLEEING = 92,
    SPELL_AURA_MOD_UNATTACKABLE = 93,
    SPELL_AURA_INTERRUPT_REGEN = 94,
    SPELL_AURA_GHOST = 95,
    SPELL_AURA_SPELL_MAGNET = 96,
    SPELL_AURA_MANA_SHIELD = 97,
    SPELL_AURA_MOD_SKILL_TALENT = 98,
    SPELL_AURA_MOD_ATTACK_POWER = 99,
    SPELL_AURA_AURAS_VISIBLE = 100,
    SPELL_AURA_MOD_RESISTANCE_PCT = 101,
    SPELL_AURA_MOD_MELEE_ATTACK_POWER_VERSUS = 102,
    SPELL_AURA_MOD_TOTAL_THREAT = 103,
    SPELL_AURA_WATER_WALK = 104,
    SPELL_AURA_FEATHER_FALL = 105,
    SPELL_AURA_HOVER = 106,
    SPELL_AURA_ADD_FLAT_MODIFIER = 107,
    SPELL_AURA_ADD_PCT_MODIFIER = 108,
    SPELL_AURA_ADD_TARGET_TRIGGER = 109,
    SPELL_AURA_MOD_POWER_REGEN_PERCENT = 110,
    SPELL_AURA_ADD_CASTER_HIT_TRIGGER = 111,
    SPELL_AURA_OVERRIDE_CLASS_SCRIPTS = 112,
    SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN = 113,
    SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN_PCT = 114,
    SPELL_AURA_MOD_HEALING = 115,
    SPELL_AURA_MOD_REGEN_DURING_COMBAT = 116,
    SPELL_AURA_MOD_MECHANIC_RESISTANCE = 117,
    SPELL_AURA_MOD_HEALING_PCT = 118,
    SPELL_AURA_119 = 119,                                   // old SPELL_AURA_SHARE_PET_TRACKING
    SPELL_AURA_UNTRACKABLE = 120,
    SPELL_AURA_EMPATHY = 121,
    SPELL_AURA_MOD_OFFHAND_DAMAGE_PCT = 122,
    SPELL_AURA_MOD_TARGET_RESISTANCE = 123,
    SPELL_AURA_MOD_RANGED_ATTACK_POWER = 124,
    SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN = 125,
    SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN_PCT = 126,
    SPELL_AURA_RANGED_ATTACK_POWER_ATTACKER_BONUS = 127,
    SPELL_AURA_MOD_POSSESS_PET = 128,
    SPELL_AURA_MOD_SPEED_ALWAYS = 129,
    SPELL_AURA_MOD_MOUNTED_SPEED_ALWAYS = 130,
    SPELL_AURA_MOD_RANGED_ATTACK_POWER_VERSUS = 131,
    SPELL_AURA_MOD_INCREASE_ENERGY_PERCENT = 132,
    SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT = 133,
    SPELL_AURA_MOD_MANA_REGEN_INTERRUPT = 134,
    SPELL_AURA_MOD_HEALING_DONE = 135,
    SPELL_AURA_MOD_HEALING_DONE_PERCENT = 136,
    SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE = 137,
    SPELL_AURA_MOD_HASTE = 138,
    SPELL_AURA_FORCE_REACTION = 139,
    SPELL_AURA_MOD_RANGED_HASTE = 140,
    SPELL_AURA_MOD_RANGED_AMMO_HASTE = 141,
    SPELL_AURA_MOD_BASE_RESISTANCE_PCT = 142,
    SPELL_AURA_MOD_RESISTANCE_EXCLUSIVE = 143,
    SPELL_AURA_SAFE_FALL = 144,
    SPELL_AURA_MOD_PET_TALENT_POINTS = 145,
    SPELL_AURA_ALLOW_TAME_PET_TYPE = 146,
    SPELL_AURA_MECHANIC_IMMUNITY_MASK = 147,
    SPELL_AURA_RETAIN_COMBO_POINTS = 148,
    SPELL_AURA_REDUCE_PUSHBACK  = 149,                      //    Reduce Pushback
    SPELL_AURA_MOD_SHIELD_BLOCKVALUE_PCT = 150,
    SPELL_AURA_TRACK_STEALTHED  = 151,                      //    Track Stealthed
    SPELL_AURA_MOD_DETECTED_RANGE = 152,                    //    Mod Detected Range
    SPELL_AURA_SPLIT_DAMAGE_FLAT = 153,                     //    Split Damage Flat
    SPELL_AURA_MOD_STEALTH_LEVEL = 154,                     //    Stealth Level Modifier
    SPELL_AURA_MOD_WATER_BREATHING = 155,                   //    Mod Water Breathing
    SPELL_AURA_MOD_REPUTATION_GAIN = 156,                   //    Mod Reputation Gain
    SPELL_AURA_PET_DAMAGE_MULTI = 157,                      //    Mod Pet Damage
    SPELL_AURA_MOD_SHIELD_BLOCKVALUE = 158,
    SPELL_AURA_NO_PVP_CREDIT = 159,
    SPELL_AURA_MOD_AOE_AVOIDANCE = 160,
    SPELL_AURA_MOD_HEALTH_REGEN_IN_COMBAT = 161,
    SPELL_AURA_POWER_BURN_MANA = 162,
    SPELL_AURA_MOD_CRIT_DAMAGE_BONUS = 163,
    SPELL_AURA_164 = 164,
    SPELL_AURA_MELEE_ATTACK_POWER_ATTACKER_BONUS = 165,
    SPELL_AURA_MOD_ATTACK_POWER_PCT = 166,
    SPELL_AURA_MOD_RANGED_ATTACK_POWER_PCT = 167,
    SPELL_AURA_MOD_DAMAGE_DONE_VERSUS = 168,
    SPELL_AURA_MOD_CRIT_PERCENT_VERSUS = 169,
    SPELL_AURA_DETECT_AMORE = 170,
    SPELL_AURA_MOD_SPEED_NOT_STACK = 171,
    SPELL_AURA_MOD_MOUNTED_SPEED_NOT_STACK = 172,
    SPELL_AURA_173 = 173,                                   // old SPELL_AURA_ALLOW_CHAMPION_SPELLS
    SPELL_AURA_MOD_SPELL_DAMAGE_OF_STAT_PERCENT = 174,      // by defeult intelect, dependent from SPELL_AURA_MOD_SPELL_HEALING_OF_STAT_PERCENT
    SPELL_AURA_MOD_SPELL_HEALING_OF_STAT_PERCENT = 175,
    SPELL_AURA_SPIRIT_OF_REDEMPTION = 176,
    SPELL_AURA_AOE_CHARM = 177,
    SPELL_AURA_MOD_DEBUFF_RESISTANCE = 178,
    SPELL_AURA_MOD_ATTACKER_SPELL_CRIT_CHANCE = 179,
    SPELL_AURA_MOD_FLAT_SPELL_DAMAGE_VERSUS = 180,
    SPELL_AURA_181 = 181,                                   // old SPELL_AURA_MOD_FLAT_SPELL_CRIT_DAMAGE_VERSUS - possible flat spell crit damage versus
    SPELL_AURA_MOD_RESISTANCE_OF_STAT_PERCENT = 182,
    SPELL_AURA_MOD_CRITICAL_THREAT = 183,
    SPELL_AURA_MOD_ATTACKER_MELEE_HIT_CHANCE = 184,
    SPELL_AURA_MOD_ATTACKER_RANGED_HIT_CHANCE= 185,
    SPELL_AURA_MOD_ATTACKER_SPELL_HIT_CHANCE = 186,
    SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_CHANCE = 187,
    SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_CHANCE = 188,
    SPELL_AURA_MOD_RATING = 189,
    SPELL_AURA_MOD_FACTION_REPUTATION_GAIN = 190,
    SPELL_AURA_USE_NORMAL_MOVEMENT_SPEED = 191,
    SPELL_AURA_HASTE_MELEE = 192,
    SPELL_AURA_MELEE_SLOW = 193,
    SPELL_AURA_MOD_IGNORE_ABSORB_SCHOOL  = 194,
    SPELL_AURA_MOD_IGNORE_ABSORB_FOR_SPELL  = 195,
    SPELL_AURA_MOD_COOLDOWN = 196,                          // only 24818 Noxious Breath
    SPELL_AURA_MOD_ATTACKER_SPELL_AND_WEAPON_CRIT_CHANCE = 197,
    SPELL_AURA_198 = 198,                                   // old SPELL_AURA_MOD_ALL_WEAPON_SKILLS
    SPELL_AURA_MOD_INCREASES_SPELL_PCT_TO_HIT = 199,
    SPELL_AURA_MOD_KILL_XP_PCT = 200,
    SPELL_AURA_FLY = 201,
    SPELL_AURA_IGNORE_COMBAT_RESULT = 202,
    SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_DAMAGE = 203,
    SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_DAMAGE = 204,
    SPELL_AURA_MOD_ATTACKER_SPELL_CRIT_DAMAGE = 205,
    SPELL_AURA_MOD_SPEED_MOUNTED = 206,                     // ? used in strange spells
    SPELL_AURA_MOD_INCREASE_FLIGHT_SPEED = 207,
    SPELL_AURA_MOD_SPEED_FLIGHT = 208,
    SPELL_AURA_MOD_FLIGHT_SPEED_ALWAYS = 209,
    SPELL_AURA_210 = 210,                                   // unused
    SPELL_AURA_MOD_FLIGHT_SPEED_NOT_STACK = 211,
    SPELL_AURA_MOD_RANGED_ATTACK_POWER_OF_STAT_PERCENT = 212,
    SPELL_AURA_MOD_RAGE_FROM_DAMAGE_DEALT = 213,
    SPELL_AURA_214 = 214,
    SPELL_AURA_ARENA_PREPARATION = 215,
    SPELL_AURA_HASTE_SPELLS = 216,
    SPELL_AURA_217 = 217,
    SPELL_AURA_HASTE_RANGED = 218,
    SPELL_AURA_MOD_MANA_REGEN_FROM_STAT = 219,
    SPELL_AURA_MOD_RATING_FROM_STAT = 220,
    SPELL_AURA_221 = 221,
    SPELL_AURA_222 = 222,
    SPELL_AURA_223 = 223,
    SPELL_AURA_224 = 224,
    SPELL_AURA_PRAYER_OF_MENDING = 225,
    SPELL_AURA_PERIODIC_DUMMY = 226,
    SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE = 227,
    SPELL_AURA_DETECT_STEALTH = 228,
    SPELL_AURA_MOD_AOE_DAMAGE_AVOIDANCE = 229,
    SPELL_AURA_230 = 230,
    SPELL_AURA_PROC_TRIGGER_SPELL_WITH_VALUE = 231,
    SPELL_AURA_MECHANIC_DURATION_MOD = 232,
    SPELL_AURA_233 = 233,
    SPELL_AURA_MECHANIC_DURATION_MOD_NOT_STACK = 234,
    SPELL_AURA_MOD_DISPEL_RESIST = 235,
    SPELL_AURA_CONTROL_VEHICLE = 236,
    SPELL_AURA_MOD_SPELL_DAMAGE_OF_ATTACK_POWER = 237,
    SPELL_AURA_MOD_SPELL_HEALING_OF_ATTACK_POWER = 238,
    SPELL_AURA_MOD_SCALE_2 = 239,
    SPELL_AURA_MOD_EXPERTISE = 240,
    SPELL_AURA_FORCE_MOVE_FORWARD = 241,
    SPELL_AURA_MOD_SPELL_DAMAGE_FROM_HEALING = 242,
    SPELL_AURA_243 = 243,
    SPELL_AURA_COMPREHEND_LANGUAGE = 244,
    SPELL_AURA_MOD_DURATION_OF_MAGIC_EFFECTS = 245,
    SPELL_AURA_MOD_DURATION_OF_EFFECTS_BY_DISPEL = 246,
    SPELL_AURA_247 = 247,
    SPELL_AURA_MOD_COMBAT_RESULT_CHANCE = 248,
    SPELL_AURA_CONVERT_RUNE = 249,
    SPELL_AURA_MOD_INCREASE_HEALTH_2 = 250,
    SPELL_AURA_MOD_ENEMY_DODGE = 251,
    SPELL_AURA_252 = 252,
    SPELL_AURA_MOD_BLOCK_CRIT_CHANCE = 253,
    SPELL_AURA_MOD_DISARM_SHIELD = 254,
    SPELL_AURA_MOD_MECHANIC_DAMAGE_TAKEN_PERCENT = 255,
    SPELL_AURA_NO_REAGENT_USE = 256,
    SPELL_AURA_MOD_TARGET_RESIST_BY_SPELL_CLASS = 257,
    SPELL_AURA_258 = 258,
    SPELL_AURA_259 = 259,
    SPELL_AURA_SCREEN_EFFECT = 260,
    SPELL_AURA_PHASE = 261,
    SPELL_AURA_262 = 262,
    SPELL_AURA_ALLOW_ONLY_ABILITY = 263,
    SPELL_AURA_264 = 264,
    SPELL_AURA_265 = 265,
    SPELL_AURA_266 = 266,
    SPELL_AURA_MOD_IMMUNE_AURA_APPLY_SCHOOL = 267,
    SPELL_AURA_MOD_ATTACK_POWER_OF_STAT_PERCENT = 268,
    SPELL_AURA_MOD_IGNORE_DAMAGE_REDUCTION_SCHOOL = 269,
    SPELL_AURA_MOD_IGNORE_TARGET_RESIST = 270,              // Possibly need swap vs 195 aura used only in 1 spell Chaos Bolt Passive
    SPELL_AURA_MOD_DAMAGE_FROM_CASTER = 271,
    SPELL_AURA_MAELSTROM_WEAPON = 272,
    SPELL_AURA_X_RAY = 273,
    SPELL_AURA_274 = 274,
    SPELL_AURA_MOD_IGNORE_SHAPESHIFT = 275,
    SPELL_AURA_276 = 276,                                   // Only "Test Mod Damage % Mechanic" spell, possible mod damage done
    SPELL_AURA_MOD_MAX_AFFECTED_TARGETS = 277,
    SPELL_AURA_MOD_DISARM_RANGED = 278,
    SPELL_AURA_279 = 279,
    SPELL_AURA_MOD_TARGET_ARMOR_PCT = 280,
    SPELL_AURA_MOD_HONOR_GAIN = 281,
    SPELL_AURA_MOD_BASE_HEALTH_PCT = 282,
    SPELL_AURA_MOD_HEALING_RECEIVED = 283,                  // Possibly only for some spell family class spells
    SPELL_AURA_284,
    SPELL_AURA_MOD_ATTACK_POWER_OF_ARMOR = 285,
    SPELL_AURA_ABILITY_PERIODIC_CRIT = 286,
    SPELL_AURA_DEFLECT_SPELLS = 287,
    SPELL_AURA_288 = 288,
    SPELL_AURA_289 = 289,
    SPELL_AURA_MOD_ALL_CRIT_CHANCE = 290,
    SPELL_AURA_MOD_QUEST_XP_PCT = 291,
    SPELL_AURA_292 = 292,
    SPELL_AURA_293 = 293,
    SPELL_AURA_294 = 294,
    SPELL_AURA_295 = 295,
    SPELL_AURA_296 = 296,
    SPELL_AURA_297 = 297,
    SPELL_AURA_298 = 298,
    SPELL_AURA_299 = 299,
    SPELL_AURA_300 = 300,
    SPELL_AURA_301 = 301,
    SPELL_AURA_302 = 302,
    SPELL_AURA_303 = 303,
    SPELL_AURA_304 = 304,
    SPELL_AURA_MOD_MINIMUM_SPEED = 305,
    SPELL_AURA_306 = 306,
    SPELL_AURA_307 = 307,
    SPELL_AURA_308 = 308,
    SPELL_AURA_309 = 309,
    SPELL_AURA_310 = 310,
    SPELL_AURA_311 = 311,
    SPELL_AURA_312 = 312,
    SPELL_AURA_313 = 313,
    SPELL_AURA_314 = 314,
    SPELL_AURA_315 = 315,
    SPELL_AURA_316 = 316,
    TOTAL_AURAS = 317
};

enum AreaAuraType
{
    AREA_AURA_PARTY,
    AREA_AURA_RAID,
    AREA_AURA_FRIEND,
    AREA_AURA_ENEMY,
    AREA_AURA_PET,
    AREA_AURA_OWNER
};

#define MAX_DECLINED_NAME_CASES 5

enum ItemModType
{
    ITEM_MOD_MANA                     = 0,
    ITEM_MOD_HEALTH                   = 1,
    ITEM_MOD_AGILITY                  = 3,
    ITEM_MOD_STRENGTH                 = 4,
    ITEM_MOD_INTELLECT                = 5,
    ITEM_MOD_SPIRIT                   = 6,
    ITEM_MOD_STAMINA                  = 7,
    ITEM_MOD_DEFENSE_SKILL_RATING     = 12,
    ITEM_MOD_DODGE_RATING             = 13,
    ITEM_MOD_PARRY_RATING             = 14,
    ITEM_MOD_BLOCK_RATING             = 15,
    ITEM_MOD_HIT_MELEE_RATING         = 16,
    ITEM_MOD_HIT_RANGED_RATING        = 17,
    ITEM_MOD_HIT_SPELL_RATING         = 18,
    ITEM_MOD_CRIT_MELEE_RATING        = 19,
    ITEM_MOD_CRIT_RANGED_RATING       = 20,
    ITEM_MOD_CRIT_SPELL_RATING        = 21,
    ITEM_MOD_HIT_TAKEN_MELEE_RATING   = 22,
    ITEM_MOD_HIT_TAKEN_RANGED_RATING  = 23,
    ITEM_MOD_HIT_TAKEN_SPELL_RATING   = 24,
    ITEM_MOD_CRIT_TAKEN_MELEE_RATING  = 25,
    ITEM_MOD_CRIT_TAKEN_RANGED_RATING = 26,
    ITEM_MOD_CRIT_TAKEN_SPELL_RATING  = 27,
    ITEM_MOD_HASTE_MELEE_RATING       = 28,
    ITEM_MOD_HASTE_RANGED_RATING      = 29,
    ITEM_MOD_HASTE_SPELL_RATING       = 30,
    ITEM_MOD_HIT_RATING               = 31,
    ITEM_MOD_CRIT_RATING              = 32,
    ITEM_MOD_HIT_TAKEN_RATING         = 33,
    ITEM_MOD_CRIT_TAKEN_RATING        = 34,
    ITEM_MOD_RESILIENCE_RATING        = 35,
    ITEM_MOD_HASTE_RATING             = 36,
    ITEM_MOD_EXPERTISE_RATING         = 37,
    ITEM_MOD_ATTACK_POWER             = 38,
    ITEM_MOD_RANGED_ATTACK_POWER      = 39,
    ITEM_MOD_FERAL_ATTACK_POWER       = 40,                 // deprecated
    ITEM_MOD_SPELL_HEALING_DONE       = 41,                 // deprecated
    ITEM_MOD_SPELL_DAMAGE_DONE        = 42,                 // deprecated
    ITEM_MOD_MANA_REGENERATION        = 43,
    ITEM_MOD_ARMOR_PENETRATION_RATING = 44,
    ITEM_MOD_SPELL_POWER              = 45,
    ITEM_MOD_HEALTH_REGEN             = 46,
    ITEM_MOD_SPELL_PENETRATION        = 47,
    ITEM_MOD_BLOCK_VALUE              = 48
};

#define MAX_ITEM_MOD                    49

enum ItemSpelltriggerType
{
    ITEM_SPELLTRIGGER_ON_USE          = 0,                  // use after equip cooldown
    ITEM_SPELLTRIGGER_ON_EQUIP        = 1,
    ITEM_SPELLTRIGGER_CHANCE_ON_HIT   = 2,
    ITEM_SPELLTRIGGER_SOULSTONE       = 4,
    /*
     * ItemSpelltriggerType 5 might have changed on 2.4.3/3.0.3: Such auras
     * will be applied on item pickup and removed on item loss - maybe on the
     * other hand the item is destroyed if the aura is removed ("removed on
     * death" of spell 57348 makes me think so)
     */
    ITEM_SPELLTRIGGER_ON_NO_DELAY_USE = 5,                  // no equip cooldown
    ITEM_SPELLTRIGGER_LEARN_SPELL_ID  = 6                   // used in item_template.spell_2 with spell_id with SPELL_GENERIC_LEARN in spell_1
};

#define MAX_ITEM_SPELLTRIGGER           7

enum ItemBondingType
{
    NO_BIND                                     = 0,
    BIND_WHEN_PICKED_UP                         = 1,
    BIND_WHEN_EQUIPED                           = 2,
    BIND_WHEN_USE                               = 3,
    BIND_QUEST_ITEM                             = 4,
    BIND_QUEST_ITEM1                            = 5         // not used in game
};

#define MAX_BIND_TYPE                             6

// masks for ITEM_FIELD_FLAGS field
enum ITEM_FLAGS
{
    ITEM_FLAGS_BINDED                         = 0x00000001, // set in game at binding, not set in template
    ITEM_FLAGS_CONJURED                       = 0x00000002,
    ITEM_FLAGS_OPENABLE                       = 0x00000004,
    ITEM_FLAGS_WRAPPED                        = 0x00000008,
    ITEM_FLAGS_HEROIC                         = 0x00000008, // weird...
    ITEM_FLAGS_BROKEN                         = 0x00000010, // appears red icon (like when item durability==0)
    ITEM_FLAGS_TOTEM                          = 0x00000020, // ?
    ITEM_FLAGS_USABLE                         = 0x00000040, // ?
    ITEM_FLAGS_NO_EQUIP_COOLDOWN              = 0x00000080, // ?
    ITEM_FLAGS_WRAPPER                        = 0x00000200, // used or not used wrapper
    ITEM_FLAGS_IGNORE_BAG_SPACE               = 0x00000400, // ignore bag space at new item creation?
    ITEM_FLAGS_PARTY_LOOT                     = 0x00000800, // determines if item is party loot or not
    ITEM_FLAGS_REFUNDABLE                     = 0x00001000, // item cost can be refunded within 2 hours after purchase
    ITEM_FLAGS_CHARTER                        = 0x00002000, // arena/guild charter
    ITEM_FLAGS_REFUNDABLE_2                   = 0x00008000, // ?
    ITEM_FLAGS_PROSPECTABLE                   = 0x00040000,
    ITEM_FLAGS_UNIQUE_EQUIPPED                = 0x00080000,
    ITEM_FLAGS_USEABLE_IN_ARENA               = 0x00200000,
    ITEM_FLAGS_THROWABLE                      = 0x00400000, // not used in game for check trow possibility, only for item in game tooltip
    ITEM_FLAGS_SPECIALUSE                     = 0x00800000, // last used flag in 2.3.0
    ITEM_FLAGS_BOA                            = 0x08000000, // bind on account (set in template for items that can binded in like way)
    ITEM_FLAGS_ENCHANT_SCROLL                 = 0x10000000, // for enchant scrolls
    ITEM_FLAGS_MILLABLE                       = 0x20000000,
    ITEM_FLAGS_BOP_TRADEABLE                  = 0x80000000
};

enum BAG_FAMILY_MASK
{
    BAG_FAMILY_MASK_NONE                      = 0x00000000,
    BAG_FAMILY_MASK_ARROWS                    = 0x00000001,
    BAG_FAMILY_MASK_BULLETS                   = 0x00000002,
    BAG_FAMILY_MASK_SOUL_SHARDS               = 0x00000004,
    BAG_FAMILY_MASK_LEATHERWORKING_SUPP       = 0x00000008,
    BAG_FAMILY_MASK_INSCRIPTION_SUPP          = 0x00000010,
    BAG_FAMILY_MASK_HERBS                     = 0x00000020,
    BAG_FAMILY_MASK_ENCHANTING_SUPP           = 0x00000040,
    BAG_FAMILY_MASK_ENGINEERING_SUPP          = 0x00000080,
    BAG_FAMILY_MASK_KEYS                      = 0x00000100,
    BAG_FAMILY_MASK_GEMS                      = 0x00000200,
    BAG_FAMILY_MASK_MINING_SUPP               = 0x00000400,
    BAG_FAMILY_MASK_SOULBOUND_EQUIPMENT       = 0x00000800,
    BAG_FAMILY_MASK_VANITY_PETS               = 0x00001000,
    BAG_FAMILY_MASK_CURRENCY_TOKENS           = 0x00002000,
    BAG_FAMILY_MASK_QUEST_ITEMS               = 0x00004000
};

enum SocketColor
{
    SOCKET_COLOR_META                           = 1,
    SOCKET_COLOR_RED                            = 2,
    SOCKET_COLOR_YELLOW                         = 4,
    SOCKET_COLOR_BLUE                           = 8
};

#define SOCKET_COLOR_ALL (SOCKET_COLOR_META | SOCKET_COLOR_RED | SOCKET_COLOR_YELLOW | SOCKET_COLOR_BLUE)

enum InventoryType
{
    INVTYPE_NON_EQUIP                           = 0,
    INVTYPE_HEAD                                = 1,
    INVTYPE_NECK                                = 2,
    INVTYPE_SHOULDERS                           = 3,
    INVTYPE_BODY                                = 4,
    INVTYPE_CHEST                               = 5,
    INVTYPE_WAIST                               = 6,
    INVTYPE_LEGS                                = 7,
    INVTYPE_FEET                                = 8,
    INVTYPE_WRISTS                              = 9,
    INVTYPE_HANDS                               = 10,
    INVTYPE_FINGER                              = 11,
    INVTYPE_TRINKET                             = 12,
    INVTYPE_WEAPON                              = 13,
    INVTYPE_SHIELD                              = 14,
    INVTYPE_RANGED                              = 15,
    INVTYPE_CLOAK                               = 16,
    INVTYPE_2HWEAPON                            = 17,
    INVTYPE_BAG                                 = 18,
    INVTYPE_TABARD                              = 19,
    INVTYPE_ROBE                                = 20,
    INVTYPE_WEAPONMAINHAND                      = 21,
    INVTYPE_WEAPONOFFHAND                       = 22,
    INVTYPE_HOLDABLE                            = 23,
    INVTYPE_AMMO                                = 24,
    INVTYPE_THROWN                              = 25,
    INVTYPE_RANGEDRIGHT                         = 26,
    INVTYPE_QUIVER                              = 27,
    INVTYPE_RELIC                               = 28
};

#define MAX_INVTYPE                               29

enum ItemClass
{
    ITEM_CLASS_CONSUMABLE                       = 0,
    ITEM_CLASS_CONTAINER                        = 1,
    ITEM_CLASS_WEAPON                           = 2,
    ITEM_CLASS_GEM                              = 3,
    ITEM_CLASS_ARMOR                            = 4,
    ITEM_CLASS_REAGENT                          = 5,
    ITEM_CLASS_PROJECTILE                       = 6,
    ITEM_CLASS_TRADE_GOODS                      = 7,
    ITEM_CLASS_GENERIC                          = 8,
    ITEM_CLASS_RECIPE                           = 9,
    ITEM_CLASS_MONEY                            = 10,
    ITEM_CLASS_QUIVER                           = 11,
    ITEM_CLASS_QUEST                            = 12,
    ITEM_CLASS_KEY                              = 13,
    ITEM_CLASS_PERMANENT                        = 14,
    ITEM_CLASS_MISC                             = 15,
    ITEM_CLASS_GLYPH                            = 16
};

#define MAX_ITEM_CLASS                            17

enum ItemSubclassConsumable
{
    ITEM_SUBCLASS_CONSUMABLE                    = 0,
    ITEM_SUBCLASS_POTION                        = 1,
    ITEM_SUBCLASS_ELIXIR                        = 2,
    ITEM_SUBCLASS_FLASK                         = 3,
    ITEM_SUBCLASS_SCROLL                        = 4,
    ITEM_SUBCLASS_FOOD                          = 5,
    ITEM_SUBCLASS_ITEM_ENHANCEMENT              = 6,
    ITEM_SUBCLASS_BANDAGE                       = 7,
    ITEM_SUBCLASS_CONSUMABLE_OTHER              = 8
};

#define MAX_ITEM_SUBCLASS_CONSUMABLE              9

enum ItemSubclassContainer
{
    ITEM_SUBCLASS_CONTAINER                     = 0,
    ITEM_SUBCLASS_SOUL_CONTAINER                = 1,
    ITEM_SUBCLASS_HERB_CONTAINER                = 2,
    ITEM_SUBCLASS_ENCHANTING_CONTAINER          = 3,
    ITEM_SUBCLASS_ENGINEERING_CONTAINER         = 4,
    ITEM_SUBCLASS_GEM_CONTAINER                 = 5,
    ITEM_SUBCLASS_MINING_CONTAINER              = 6,
    ITEM_SUBCLASS_LEATHERWORKING_CONTAINER      = 7,
    ITEM_SUBCLASS_INSCRIPTION_CONTAINER         = 8
};

#define MAX_ITEM_SUBCLASS_CONTAINER               9

enum ItemSubclassWeapon
{
    ITEM_SUBCLASS_WEAPON_AXE                    = 0,
    ITEM_SUBCLASS_WEAPON_AXE2                   = 1,
    ITEM_SUBCLASS_WEAPON_BOW                    = 2,
    ITEM_SUBCLASS_WEAPON_GUN                    = 3,
    ITEM_SUBCLASS_WEAPON_MACE                   = 4,
    ITEM_SUBCLASS_WEAPON_MACE2                  = 5,
    ITEM_SUBCLASS_WEAPON_POLEARM                = 6,
    ITEM_SUBCLASS_WEAPON_SWORD                  = 7,
    ITEM_SUBCLASS_WEAPON_SWORD2                 = 8,
    ITEM_SUBCLASS_WEAPON_obsolete               = 9,
    ITEM_SUBCLASS_WEAPON_STAFF                  = 10,
    ITEM_SUBCLASS_WEAPON_EXOTIC                 = 11,
    ITEM_SUBCLASS_WEAPON_EXOTIC2                = 12,
    ITEM_SUBCLASS_WEAPON_FIST                   = 13,
    ITEM_SUBCLASS_WEAPON_MISC                   = 14,
    ITEM_SUBCLASS_WEAPON_DAGGER                 = 15,
    ITEM_SUBCLASS_WEAPON_THROWN                 = 16,
    ITEM_SUBCLASS_WEAPON_SPEAR                  = 17,
    ITEM_SUBCLASS_WEAPON_CROSSBOW               = 18,
    ITEM_SUBCLASS_WEAPON_WAND                   = 19,
    ITEM_SUBCLASS_WEAPON_FISHING_POLE           = 20
};

#define MAX_ITEM_SUBCLASS_WEAPON                  21

enum ItemSubclassGem
{
    ITEM_SUBCLASS_GEM_RED                       = 0,
    ITEM_SUBCLASS_GEM_BLUE                      = 1,
    ITEM_SUBCLASS_GEM_YELLOW                    = 2,
    ITEM_SUBCLASS_GEM_PURPLE                    = 3,
    ITEM_SUBCLASS_GEM_GREEN                     = 4,
    ITEM_SUBCLASS_GEM_ORANGE                    = 5,
    ITEM_SUBCLASS_GEM_META                      = 6,
    ITEM_SUBCLASS_GEM_SIMPLE                    = 7,
    ITEM_SUBCLASS_GEM_PRISMATIC                 = 8
};

#define MAX_ITEM_SUBCLASS_GEM                     9

enum ItemSubclassArmor
{
    ITEM_SUBCLASS_ARMOR_MISC                    = 0,
    ITEM_SUBCLASS_ARMOR_CLOTH                   = 1,
    ITEM_SUBCLASS_ARMOR_LEATHER                 = 2,
    ITEM_SUBCLASS_ARMOR_MAIL                    = 3,
    ITEM_SUBCLASS_ARMOR_PLATE                   = 4,
    ITEM_SUBCLASS_ARMOR_BUCKLER                 = 5,
    ITEM_SUBCLASS_ARMOR_SHIELD                  = 6,
    ITEM_SUBCLASS_ARMOR_LIBRAM                  = 7,
    ITEM_SUBCLASS_ARMOR_IDOL                    = 8,
    ITEM_SUBCLASS_ARMOR_TOTEM                   = 9,
    ITEM_SUBCLASS_ARMOR_SIGIL                   = 10
};

#define MAX_ITEM_SUBCLASS_ARMOR                   11

enum ItemSubclassReagent
{
    ITEM_SUBCLASS_REAGENT                       = 0
};

#define MAX_ITEM_SUBCLASS_REAGENT                 1

enum ItemSubclassProjectile
{
    ITEM_SUBCLASS_WAND                          = 0,        // ABS
    ITEM_SUBCLASS_BOLT                          = 1,        // ABS
    ITEM_SUBCLASS_ARROW                         = 2,
    ITEM_SUBCLASS_BULLET                        = 3,
    ITEM_SUBCLASS_THROWN                        = 4         // ABS
};

#define MAX_ITEM_SUBCLASS_PROJECTILE              5

enum ItemSubclassTradeGoods
{
    ITEM_SUBCLASS_TRADE_GOODS                   = 0,
    ITEM_SUBCLASS_PARTS                         = 1,
    ITEM_SUBCLASS_EXPLOSIVES                    = 2,
    ITEM_SUBCLASS_DEVICES                       = 3,
    ITEM_SUBCLASS_JEWELCRAFTING                 = 4,
    ITEM_SUBCLASS_CLOTH                         = 5,
    ITEM_SUBCLASS_LEATHER                       = 6,
    ITEM_SUBCLASS_METAL_STONE                   = 7,
    ITEM_SUBCLASS_MEAT                          = 8,
    ITEM_SUBCLASS_HERB                          = 9,
    ITEM_SUBCLASS_ELEMENTAL                     = 10,
    ITEM_SUBCLASS_TRADE_GOODS_OTHER             = 11,
    ITEM_SUBCLASS_ENCHANTING                    = 12,
    ITEM_SUBCLASS_MATERIAL                      = 13,
    ITEM_SUBCLASS_ARMOR_ENCHANTMENT             = 14,
    ITEM_SUBCLASS_WEAPON_ENCHANTMENT            = 15
};

#define MAX_ITEM_SUBCLASS_TRADE_GOODS             16

enum ItemSubclassGeneric
{
    ITEM_SUBCLASS_GENERIC                       = 0
};

#define MAX_ITEM_SUBCLASS_GENERIC                 1

enum ItemSubclassRecipe
{
    ITEM_SUBCLASS_BOOK                          = 0,
    ITEM_SUBCLASS_LEATHERWORKING_PATTERN        = 1,
    ITEM_SUBCLASS_TAILORING_PATTERN             = 2,
    ITEM_SUBCLASS_ENGINEERING_SCHEMATIC         = 3,
    ITEM_SUBCLASS_BLACKSMITHING                 = 4,
    ITEM_SUBCLASS_COOKING_RECIPE                = 5,
    ITEM_SUBCLASS_ALCHEMY_RECIPE                = 6,
    ITEM_SUBCLASS_FIRST_AID_MANUAL              = 7,
    ITEM_SUBCLASS_ENCHANTING_FORMULA            = 8,
    ITEM_SUBCLASS_FISHING_MANUAL                = 9,
    ITEM_SUBCLASS_JEWELCRAFTING_RECIPE          = 10
};

#define MAX_ITEM_SUBCLASS_RECIPE                  11

enum ItemSubclassMoney
{
    ITEM_SUBCLASS_MONEY                         = 0
};

#define MAX_ITEM_SUBCLASS_MONEY                   1

enum ItemSubclassQuiver
{
    ITEM_SUBCLASS_QUIVER0                       = 0,        // ABS
    ITEM_SUBCLASS_QUIVER1                       = 1,        // ABS
    ITEM_SUBCLASS_QUIVER                        = 2,
    ITEM_SUBCLASS_AMMO_POUCH                    = 3
};

#define MAX_ITEM_SUBCLASS_QUIVER                  4

enum ItemSubclassQuest
{
    ITEM_SUBCLASS_QUEST                         = 0
};

#define MAX_ITEM_SUBCLASS_QUEST                   1

enum ItemSubclassKey
{
    ITEM_SUBCLASS_KEY                           = 0,
    ITEM_SUBCLASS_LOCKPICK                      = 1
};

#define MAX_ITEM_SUBCLASS_KEY                     2

enum ItemSubclassPermanent
{
    ITEM_SUBCLASS_PERMANENT                     = 0
};

#define MAX_ITEM_SUBCLASS_PERMANENT               1

enum ItemSubclassJunk
{
    ITEM_SUBCLASS_JUNK                          = 0,
    ITEM_SUBCLASS_JUNK_REAGENT                  = 1,
    ITEM_SUBCLASS_JUNK_PET                      = 2,
    ITEM_SUBCLASS_JUNK_HOLIDAY                  = 3,
    ITEM_SUBCLASS_JUNK_OTHER                    = 4,
    ITEM_SUBCLASS_JUNK_MOUNT                    = 5
};

#define MAX_ITEM_SUBCLASS_JUNK                    6

enum ItemSubclassGlyph
{
    ITEM_SUBCLASS_GLYPH_WARRIOR                 = 1,
    ITEM_SUBCLASS_GLYPH_PALADIN                 = 2,
    ITEM_SUBCLASS_GLYPH_HUNTER                  = 3,
    ITEM_SUBCLASS_GLYPH_ROGUE                   = 4,
    ITEM_SUBCLASS_GLYPH_PRIEST                  = 5,
    ITEM_SUBCLASS_GLYPH_DEATH_KNIGHT            = 6,
    ITEM_SUBCLASS_GLYPH_SHAMAN                  = 7,
    ITEM_SUBCLASS_GLYPH_MAGE                    = 8,
    ITEM_SUBCLASS_GLYPH_WARLOCK                 = 9,
    ITEM_SUBCLASS_GLYPH_DRUID                   = 11
};

#define MAX_ITEM_SUBCLASS_GLYPH                   12

const uint32 MaxItemSubclassValues[MAX_ITEM_CLASS] =
{
    MAX_ITEM_SUBCLASS_CONSUMABLE,
    MAX_ITEM_SUBCLASS_CONTAINER,
    MAX_ITEM_SUBCLASS_WEAPON,
    MAX_ITEM_SUBCLASS_GEM,
    MAX_ITEM_SUBCLASS_ARMOR,
    MAX_ITEM_SUBCLASS_REAGENT,
    MAX_ITEM_SUBCLASS_PROJECTILE,
    MAX_ITEM_SUBCLASS_TRADE_GOODS,
    MAX_ITEM_SUBCLASS_GENERIC,
    MAX_ITEM_SUBCLASS_RECIPE,
    MAX_ITEM_SUBCLASS_MONEY,
    MAX_ITEM_SUBCLASS_QUIVER,
    MAX_ITEM_SUBCLASS_QUEST,
    MAX_ITEM_SUBCLASS_KEY,
    MAX_ITEM_SUBCLASS_PERMANENT,
    MAX_ITEM_SUBCLASS_JUNK,
    MAX_ITEM_SUBCLASS_GLYPH
};

#define MAX_ITEM_PROTO_DAMAGES 2                            // changed in 3.1.0
#define MAX_ITEM_PROTO_SOCKETS 3
#define MAX_ITEM_PROTO_SPELLS  5
#define MAX_ITEM_PROTO_STATS  10

enum TypeID
{
    TYPEID_OBJECT        = 0,
    TYPEID_ITEM          = 1,
    TYPEID_CONTAINER     = 2,
    TYPEID_UNIT          = 3,
    TYPEID_PLAYER        = 4,
    TYPEID_GAMEOBJECT    = 5,
    TYPEID_DYNAMICOBJECT = 6,
    TYPEID_CORPSE        = 7
};

#define MAX_TYPE_ID        8

enum TypeMask
{
    TYPEMASK_OBJECT         = 0x0001,
    TYPEMASK_ITEM           = 0x0002,
    TYPEMASK_CONTAINER      = 0x0006,                       // TYPEMASK_ITEM | 0x0004
    TYPEMASK_UNIT           = 0x0008,
    TYPEMASK_PLAYER         = 0x0010,
    TYPEMASK_GAMEOBJECT     = 0x0020,
    TYPEMASK_DYNAMICOBJECT  = 0x0040,
    TYPEMASK_CORPSE         = 0x0080
};

enum HighGuid
{
    HIGHGUID_ITEM           = 0x4000,                       // blizz 4000
	HIGHGUID_CONTAINER      = 0x4000,                       // blizz 4000
	HIGHGUID_PLAYER         = 0x0000,                       // blizz 0000
    HIGHGUID_GAMEOBJECT     = 0xF110,                       // blizz F110
    HIGHGUID_TRANSPORT      = 0xF120,                       // blizz F120 (for GAMEOBJECT_TYPE_TRANSPORT)
    HIGHGUID_UNIT           = 0xF130,                       // blizz F130
    HIGHGUID_PET            = 0xF140,                       // blizz F140
    HIGHGUID_VEHICLE        = 0xF150,                       // blizz F550
    HIGHGUID_DYNAMICOBJECT  = 0xF100,                       // blizz F100
    HIGHGUID_CORPSE         = 0xF101,                       // blizz F100
    HIGHGUID_MO_TRANSPORT   = 0x1FC0,                       // blizz 1FC0 (for GAMEOBJECT_TYPE_MO_TRANSPORT)
};

uint64 IntBiteAppend(int32 value)
{
	if(value >= 0)
	{
		return value;
	}
    return ((value ^ uint32(0x80000000))|uint64(0x80000000));
}

uint32	GuidHigh2TypeId(uint32 guidhigh);
void	AddGUIDToHignGuidTypeMapping(uint32 guidhigh, uint32 objTypeiD);

#define MAKE_NEW_GUID(l, e, h)   uint64( IntBiteAppend(l) | ( IntBiteAppend(e) << 24 ) | ( IntBiteAppend(h) << 48 ) )
#define MAKE_GUID(h,l)  uint64(IntBiteAppend(l) | (IntBiteAppend(h) << 32))
#define GUID_HIPART(x)   (uint32)((uint64(x) >> 48) & 0x0000FFFF)
#define LI64LIT(x)  x ##LL
#define UI64LIT(x)  x ##LL

#define LOW_GUID(x) (uint32)(uint64(x) & 0xFFFFFFFF)
#define HIGH_GUID(x) (uint32)(uint64(x) >> 32)

#define IS_CREATURE_GUID(Guid)       ( GUID_HIPART(Guid) == HIGHGUID_UNIT )
#define IS_PET_GUID(Guid)            ( GUID_HIPART(Guid) == HIGHGUID_PET )
#define IS_VEHICLE_GUID(Guid)        ( GUID_HIPART(Guid) == HIGHGUID_VEHICLE )
#define IS_CREATURE_OR_PET_GUID(Guid)( IS_CREATURE_GUID(Guid) || IS_PET_GUID(Guid) )
bool IS_PLAYER_GUID(uint64 Guid)
{
	if(Guid == 0)
		return false;
	return	GuidHigh2TypeId(GUID_HIPART(Guid)) == TYPEID_PLAYER;
}

#define IS_UNIT_GUID(Guid)           ( IS_CREATURE_OR_PET_GUID(Guid) || IS_PLAYER_GUID(Guid) )
                                                            // special case for empty guid need check
#define IS_ITEM_GUID(Guid)           ( GUID_HIPART(Guid) == HIGHGUID_ITEM || GUID_HIPART(Guid) == HIGHGUID_ITEM2)
#define IS_GAMEOBJECT_GUID(Guid)     ( GUID_HIPART(Guid) == HIGHGUID_GAMEOBJECT )
#define IS_CORPSE_GUID(Guid)         ( GUID_HIPART(Guid) == HIGHGUID_CORPSE )
#define IS_MO_TRANSPORT(Guid)        ( GUID_HIPART(Guid) == HIGHGUID_MO_TRANSPORT )

// We have different low and middle part size for different guid types
#define _GUID_ENPART_2(x) (uint32)((uint64(x) >> 32) & UI64LIT(0x000000000000FFFF))
#define _GUID_ENPART_3(x) (uint32)((uint64(x) >> 24) & UI64LIT(0x0000000000FFFFFF))
#define _GUID_LOPART_2(x) (uint32)(uint64(x)         & UI64LIT(0x00000000FFFFFFFF))
#define _GUID_LOPART_3(x) (uint32)(uint64(x)         & UI64LIT(0x0000000000FFFFFF))

inline bool IsGuidHaveEnPart(uint64 const& guid)
{
    switch(GuidHigh2TypeId(GUID_HIPART(guid)))
    {
		case TYPEID_ITEM:
		case TYPEID_PLAYER:
		case TYPEID_DYNAMICOBJECT:
		case TYPEID_CORPSE:
			return false;
		case TYPEID_GAMEOBJECT:
        case TYPEID_UNIT:
        default:
            return true;
    }
}

#define GUID_ENPART(x) (IsGuidHaveEnPart(x) ? _GUID_ENPART_3(x) : _GUID_ENPART_2(x))
#define GUID_LOPART(x) (IsGuidHaveEnPart(x) ? _GUID_LOPART_3(x) : _GUID_LOPART_2(x))


enum TradeSlots
{
    TRADE_SLOT_COUNT            = 7,
    TRADE_SLOT_TRADED_COUNT     = 6,
    TRADE_SLOT_NONTRADED        = 6
};

enum TransferAbortReason
{
    TRANSFER_ABORT_NONE                     = 0x00,
    TRANSFER_ABORT_ERROR                    = 0x01,
    TRANSFER_ABORT_MAX_PLAYERS              = 0x02,         // Transfer Aborted: instance is full
    TRANSFER_ABORT_NOT_FOUND                = 0x03,         // Transfer Aborted: instance not found
    TRANSFER_ABORT_TOO_MANY_INSTANCES       = 0x04,         // You have entered too many instances recently.
    TRANSFER_ABORT_ZONE_IN_COMBAT           = 0x06,         // Unable to zone in while an encounter is in progress.
    TRANSFER_ABORT_INSUF_EXPAN_LVL          = 0x07,         // You must have <TBC,WotLK> expansion installed to access this area.
    TRANSFER_ABORT_DIFFICULTY               = 0x08,         // <Normal,Heroic,Epic> difficulty mode is not available for %s.
    TRANSFER_ABORT_UNIQUE_MESSAGE           = 0x09,         // Until you've escaped TLK's grasp, you cannot leave this place!
    TRANSFER_ABORT_TOO_MANY_REALM_INSTANCES = 0x0A,         // Additional instances cannot be launched, please try again later.
    TRANSFER_ABORT_NEED_GROUP               = 0x0B,         // 3.1
    TRANSFER_ABORT_NOT_FOUND2               = 0x0C,         // 3.1
    TRANSFER_ABORT_NOT_FOUND3               = 0x0D,         // 3.1
    TRANSFER_ABORT_NOT_FOUND4               = 0x0E,         // 3.2
    TRANSFER_ABORT_REALM_ONLY               = 0x0F,         // All players on party must be from the same realm.
    TRANSFER_ABORT_MAP_NOT_ALLOWED          = 0x10,         // Map can't be entered at this time.
};

enum InstanceResetWarningType
{
    RAID_INSTANCE_WARNING_HOURS     = 1,                    // WARNING! %s is scheduled to reset in %d hour(s).
    RAID_INSTANCE_WARNING_MIN       = 2,                    // WARNING! %s is scheduled to reset in %d minute(s)!
    RAID_INSTANCE_WARNING_MIN_SOON  = 3,                    // WARNING! %s is scheduled to reset in %d minute(s). Please exit the zone or you will be returned to your bind location!
    RAID_INSTANCE_WELCOME           = 4,                    // Welcome to %s. This raid instance is scheduled to reset in %s.
    RAID_INSTANCE_EXPIRED           = 5
};

// PLAYER_FIELD_ARENA_TEAM_INFO_1_1 offsets
enum ArenaTeamInfoType
{
    ARENA_TEAM_ID               = 0,
    ARENA_TEAM_TYPE             = 1,                        // new in 3.2 - team type?
    ARENA_TEAM_MEMBER           = 2,                        // 0 - captain, 1 - member
    ARENA_TEAM_GAMES_WEEK       = 3,
    ARENA_TEAM_GAMES_SEASON     = 4,
    ARENA_TEAM_WINS_SEASON      = 5,
    ARENA_TEAM_PERSONAL_RATING  = 6,
    ARENA_TEAM_END              = 7
};

enum RestType
{
    REST_TYPE_NO        = 0,
    REST_TYPE_IN_TAVERN = 1,
    REST_TYPE_IN_CITY   = 2
};

enum DuelCompleteType
{
    DUEL_INTERUPTED = 0,
    DUEL_WON        = 1,
    DUEL_FLED       = 2
};

enum TeleportToOptions
{
    TELE_TO_GM_MODE             = 0x01,
    TELE_TO_NOT_LEAVE_TRANSPORT = 0x02,
    TELE_TO_NOT_LEAVE_COMBAT    = 0x04,
    TELE_TO_NOT_UNSUMMON_PET    = 0x08,
    TELE_TO_SPELL               = 0x10,
};

/// Type of environmental damages
enum EnviromentalDamage
{
    DAMAGE_EXHAUSTED = 0,
    DAMAGE_DROWNING  = 1,
    DAMAGE_FALL      = 2,
    DAMAGE_LAVA      = 3,
    DAMAGE_SLIME     = 4,
    DAMAGE_FIRE      = 5,
    DAMAGE_FALL_TO_VOID = 6                                 // custom case for fall without durability loss
};

enum PlayedTimeIndex
{
    PLAYED_TIME_TOTAL = 0,
    PLAYED_TIME_LEVEL = 1
};

#define MAX_PLAYED_TIME_INDEX 2

// used at player loading query list preparing, and later result selection
enum PlayerLoginQueryIndex
{
    PLAYER_LOGIN_QUERY_LOADFROM                 = 0,
    PLAYER_LOGIN_QUERY_LOADGROUP                = 1,
    PLAYER_LOGIN_QUERY_LOADBOUNDINSTANCES       = 2,
    PLAYER_LOGIN_QUERY_LOADAURAS                = 3,
    PLAYER_LOGIN_QUERY_LOADSPELLS               = 4,
    PLAYER_LOGIN_QUERY_LOADQUESTSTATUS          = 5,
    PLAYER_LOGIN_QUERY_LOADDAILYQUESTSTATUS     = 6,
    PLAYER_LOGIN_QUERY_LOADREPUTATION           = 7,
    PLAYER_LOGIN_QUERY_LOADINVENTORY            = 8,
    PLAYER_LOGIN_QUERY_LOADACTIONS              = 9,
    PLAYER_LOGIN_QUERY_LOADSOCIALLIST           = 10,
    PLAYER_LOGIN_QUERY_LOADHOMEBIND             = 11,
    PLAYER_LOGIN_QUERY_LOADSPELLCOOLDOWNS       = 12,
    PLAYER_LOGIN_QUERY_LOADDECLINEDNAMES        = 13,
    PLAYER_LOGIN_QUERY_LOADGUILD                = 14,
    PLAYER_LOGIN_QUERY_LOADARENAINFO            = 15,
    PLAYER_LOGIN_QUERY_LOADACHIEVEMENTS         = 16,
    PLAYER_LOGIN_QUERY_LOADCRITERIAPROGRESS     = 17,
    PLAYER_LOGIN_QUERY_LOADEQUIPMENTSETS        = 18,
    PLAYER_LOGIN_QUERY_LOADBGDATA               = 19,
    PLAYER_LOGIN_QUERY_LOADACCOUNTDATA          = 20,
    PLAYER_LOGIN_QUERY_LOADSKILLS               = 21,
    PLAYER_LOGIN_QUERY_LOADGLYPHS               = 22,
    MAX_PLAYER_LOGIN_QUERY                      = 23
};

enum PlayerDelayedOperations
{
    DELAYED_SAVE_PLAYER         = 0x01,
    DELAYED_RESURRECT_PLAYER    = 0x02,
    DELAYED_SPELL_CAST_DESERTER = 0x04,
    DELAYED_BG_MOUNT_RESTORE    = 0x08,                     ///< Flag to restore mount state after teleport from BG
    DELAYED_BG_TAXI_RESTORE     = 0x10,                     ///< Flag to restore taxi state after teleport from BG
    DELAYED_END
};

// Player summoning auto-decline time (in secs)
#define MAX_PLAYER_SUMMON_DELAY                   (2*MINUTE)
#define MAX_MONEY_AMOUNT                       (0x7FFFFFFF-1)


enum RaidGroupError
{
    ERR_RAID_GROUP_NONE                 = 0,
    ERR_RAID_GROUP_LOWLEVEL             = 1,
    ERR_RAID_GROUP_ONLY                 = 2,
    ERR_RAID_GROUP_FULL                 = 3,
    ERR_RAID_GROUP_REQUIREMENTS_UNMATCH = 4
};

enum PlayerMovementType
{
    MOVE_ROOT       = 1,
    MOVE_UNROOT     = 2,
    MOVE_WATER_WALK = 3,
    MOVE_LAND_WALK  = 4
};

enum DrunkenState
{
    DRUNKEN_SOBER   = 0,
    DRUNKEN_TIPSY   = 1,
    DRUNKEN_DRUNK   = 2,
    DRUNKEN_SMASHED = 3
};

#define MAX_DRUNKEN   4

enum PlayerFlags
{
    PLAYER_FLAGS_NONE              = 0x00000000,
    PLAYER_FLAGS_GROUP_LEADER      = 0x00000001,
    PLAYER_FLAGS_AFK               = 0x00000002,
    PLAYER_FLAGS_DND               = 0x00000004,
    PLAYER_FLAGS_GM                = 0x00000008,
    PLAYER_FLAGS_GHOST             = 0x00000010,
    PLAYER_FLAGS_RESTING           = 0x00000020,
    PLAYER_FLAGS_UNK7              = 0x00000040,
    PLAYER_FLAGS_UNK8              = 0x00000080,            // pre-3.0.3 PLAYER_FLAGS_FFA_PVP flag for FFA PVP state
    PLAYER_FLAGS_CONTESTED_PVP     = 0x00000100,            // Player has been involved in a PvP combat and will be attacked by contested guards
    PLAYER_FLAGS_IN_PVP            = 0x00000200,
    PLAYER_FLAGS_HIDE_HELM         = 0x00000400,
    PLAYER_FLAGS_HIDE_CLOAK        = 0x00000800,
    PLAYER_FLAGS_PARTIAL_PLAY_TIME = 0x00001000,            // played long time
    PLAYER_FLAGS_NO_PLAY_TIME      = 0x00002000,            // played too long time
    PLAYER_FLAGS_IS_OUT_OF_BOUNDS  = 0x00004000,            // Lua_IsOutOfBounds
    PLAYER_FLAGS_DEVELOPER         = 0x00008000,            // <Dev> prefix for something?
    PLAYER_FLAGS_UNK17             = 0x00010000,            // pre-3.0.3 PLAYER_FLAGS_SANCTUARY flag for player entered sanctuary
    PLAYER_FLAGS_TAXI_BENCHMARK    = 0x00020000,            // taxi benchmark mode (on/off) (2.0.1)
    PLAYER_FLAGS_PVP_TIMER         = 0x00040000,            // 3.0.2, pvp timer active (after you disable pvp manually)
    PLAYER_FLAGS_COMMENTATOR       = 0x00080000,
    PLAYER_FLAGS_UNK21             = 0x00100000,
    PLAYER_FLAGS_UNK22             = 0x00200000,
    PLAYER_FLAGS_COMMENTATOR2      = 0x00400000,            // something like COMMENTATOR_CAN_USE_INSTANCE_COMMAND
    PLAYER_FLAGS_UNK24             = 0x00800000,            // EVENT_SPELL_UPDATE_USABLE and EVENT_UPDATE_SHAPESHIFT_USABLE, disabled all abilitys on tab except autoattack
    PLAYER_FLAGS_UNK25             = 0x01000000,            // EVENT_SPELL_UPDATE_USABLE and EVENT_UPDATE_SHAPESHIFT_USABLE, disabled all melee ability on tab include autoattack
    PLAYER_FLAGS_XP_USER_DISABLED  = 0x02000000,
};

// used for PLAYER__FIELD_KNOWN_TITLES field (uint64), (1<<bit_index) without (-1)
// can't use enum for uint64 values
#define PLAYER_TITLE_DISABLED              UI64LIT(0x0000000000000000)
#define PLAYER_TITLE_NONE                  UI64LIT(0x0000000000000001)
#define PLAYER_TITLE_PRIVATE               UI64LIT(0x0000000000000002) // 1
#define PLAYER_TITLE_CORPORAL              UI64LIT(0x0000000000000004) // 2
#define PLAYER_TITLE_SERGEANT_A            UI64LIT(0x0000000000000008) // 3
#define PLAYER_TITLE_MASTER_SERGEANT       UI64LIT(0x0000000000000010) // 4
#define PLAYER_TITLE_SERGEANT_MAJOR        UI64LIT(0x0000000000000020) // 5
#define PLAYER_TITLE_KNIGHT                UI64LIT(0x0000000000000040) // 6
#define PLAYER_TITLE_KNIGHT_LIEUTENANT     UI64LIT(0x0000000000000080) // 7
#define PLAYER_TITLE_KNIGHT_CAPTAIN        UI64LIT(0x0000000000000100) // 8
#define PLAYER_TITLE_KNIGHT_CHAMPION       UI64LIT(0x0000000000000200) // 9
#define PLAYER_TITLE_LIEUTENANT_COMMANDER  UI64LIT(0x0000000000000400) // 10
#define PLAYER_TITLE_COMMANDER             UI64LIT(0x0000000000000800) // 11
#define PLAYER_TITLE_MARSHAL               UI64LIT(0x0000000000001000) // 12
#define PLAYER_TITLE_FIELD_MARSHAL         UI64LIT(0x0000000000002000) // 13
#define PLAYER_TITLE_GRAND_MARSHAL         UI64LIT(0x0000000000004000) // 14
#define PLAYER_TITLE_SCOUT                 UI64LIT(0x0000000000008000) // 15
#define PLAYER_TITLE_GRUNT                 UI64LIT(0x0000000000010000) // 16
#define PLAYER_TITLE_SERGEANT_H            UI64LIT(0x0000000000020000) // 17
#define PLAYER_TITLE_SENIOR_SERGEANT       UI64LIT(0x0000000000040000) // 18
#define PLAYER_TITLE_FIRST_SERGEANT        UI64LIT(0x0000000000080000) // 19
#define PLAYER_TITLE_STONE_GUARD           UI64LIT(0x0000000000100000) // 20
#define PLAYER_TITLE_BLOOD_GUARD           UI64LIT(0x0000000000200000) // 21
#define PLAYER_TITLE_LEGIONNAIRE           UI64LIT(0x0000000000400000) // 22
#define PLAYER_TITLE_CENTURION             UI64LIT(0x0000000000800000) // 23
#define PLAYER_TITLE_CHAMPION              UI64LIT(0x0000000001000000) // 24
#define PLAYER_TITLE_LIEUTENANT_GENERAL    UI64LIT(0x0000000002000000) // 25
#define PLAYER_TITLE_GENERAL               UI64LIT(0x0000000004000000) // 26
#define PLAYER_TITLE_WARLORD               UI64LIT(0x0000000008000000) // 27
#define PLAYER_TITLE_HIGH_WARLORD          UI64LIT(0x0000000010000000) // 28
#define PLAYER_TITLE_GLADIATOR             UI64LIT(0x0000000020000000) // 29
#define PLAYER_TITLE_DUELIST               UI64LIT(0x0000000040000000) // 30
#define PLAYER_TITLE_RIVAL                 UI64LIT(0x0000000080000000) // 31
#define PLAYER_TITLE_CHALLENGER            UI64LIT(0x0000000100000000) // 32
#define PLAYER_TITLE_SCARAB_LORD           UI64LIT(0x0000000200000000) // 33
#define PLAYER_TITLE_CONQUEROR             UI64LIT(0x0000000400000000) // 34
#define PLAYER_TITLE_JUSTICAR              UI64LIT(0x0000000800000000) // 35
#define PLAYER_TITLE_CHAMPION_OF_THE_NAARU UI64LIT(0x0000001000000000) // 36
#define PLAYER_TITLE_MERCILESS_GLADIATOR   UI64LIT(0x0000002000000000) // 37
#define PLAYER_TITLE_OF_THE_SHATTERED_SUN  UI64LIT(0x0000004000000000) // 38
#define PLAYER_TITLE_HAND_OF_ADAL          UI64LIT(0x0000008000000000) // 39
#define PLAYER_TITLE_VENGEFUL_GLADIATOR    UI64LIT(0x0000010000000000) // 40

#define MAX_TITLE_INDEX     (3*64)                          // 3 uint64 fields

// used in PLAYER_FIELD_BYTES values
enum PlayerFieldByteFlags
{
    PLAYER_FIELD_BYTE_TRACK_STEALTHED   = 0x00000002,
    PLAYER_FIELD_BYTE_RELEASE_TIMER     = 0x00000008,       // Display time till auto release spirit
    PLAYER_FIELD_BYTE_NO_RELEASE_WINDOW = 0x00000010        // Display no "release spirit" window at all
};

// used in PLAYER_FIELD_BYTES2 values
enum PlayerFieldByte2Flags
{
    PLAYER_FIELD_BYTE2_NONE              = 0x0000,
    PLAYER_FIELD_BYTE2_INVISIBILITY_GLOW = 0x4000
};

enum ActivateTaxiReplies
{
    ERR_TAXIOK                      = 0,
    ERR_TAXIUNSPECIFIEDSERVERERROR  = 1,
    ERR_TAXINOSUCHPATH              = 2,
    ERR_TAXINOTENOUGHMONEY          = 3,
    ERR_TAXITOOFARAWAY              = 4,
    ERR_TAXINOVENDORNEARBY          = 5,
    ERR_TAXINOTVISITED              = 6,
    ERR_TAXIPLAYERBUSY              = 7,
    ERR_TAXIPLAYERALREADYMOUNTED    = 8,
    ERR_TAXIPLAYERSHAPESHIFTED      = 9,
    ERR_TAXIPLAYERMOVING            = 10,
    ERR_TAXISAMENODE                = 11,
    ERR_TAXINOTSTANDING             = 12
};

enum MirrorTimerType
{
    FATIGUE_TIMER      = 0,
    BREATH_TIMER       = 1,
    FIRE_TIMER         = 2
};
#define MAX_TIMERS      3
#define DISABLED_MIRROR_TIMER   -1

// 2^n values
enum PlayerExtraFlags
{
    // gm abilities
    PLAYER_EXTRA_GM_ON              = 0x0001,
    PLAYER_EXTRA_GM_ACCEPT_TICKETS  = 0x0002,
    PLAYER_EXTRA_ACCEPT_WHISPERS    = 0x0004,
    PLAYER_EXTRA_TAXICHEAT          = 0x0008,
    PLAYER_EXTRA_GM_INVISIBLE       = 0x0010,
    PLAYER_EXTRA_GM_CHAT            = 0x0020,               // Show GM badge in chat messages

    // other states
    PLAYER_EXTRA_PVP_DEATH          = 0x0100                // store PvP death status until corpse creating.
};

// 2^n values
enum AtLoginFlags
{
    AT_LOGIN_NONE              = 0x00,
    AT_LOGIN_RENAME            = 0x01,
    AT_LOGIN_RESET_SPELLS      = 0x02,
    AT_LOGIN_RESET_TALENTS     = 0x04,
    AT_LOGIN_CUSTOMIZE         = 0x08,
    AT_LOGIN_RESET_PET_TALENTS = 0x10,
    AT_LOGIN_FIRST             = 0x20,
};

enum QuestSlotOffsets
{
    QUEST_ID_OFFSET         = 0,
    QUEST_STATE_OFFSET      = 1,
    QUEST_COUNTS_OFFSET     = 2,                            // 2 and 3
    QUEST_TIME_OFFSET       = 4
};

#define MAX_RUNES       6
#define RUNE_COOLDOWN   (2*5*IN_MILISECONDS)                // msec

enum RuneType
{
    RUNE_BLOOD      = 0,
    RUNE_UNHOLY     = 1,
    RUNE_FROST      = 2,
    RUNE_DEATH      = 3,
    NUM_RUNE_TYPES  = 4
};

enum TrainerSpellState
{
    TRAINER_SPELL_GREEN = 0,
    TRAINER_SPELL_RED   = 1,
    TRAINER_SPELL_GRAY  = 2,
    TRAINER_SPELL_GREEN_DISABLED = 10                       // custom value, not send to client: formally green but learn not allowed
};

enum ActionButtonUpdateState
{
    ACTIONBUTTON_UNCHANGED = 0,
    ACTIONBUTTON_CHANGED   = 1,
    ACTIONBUTTON_NEW       = 2,
    ACTIONBUTTON_DELETED   = 3
};

enum ActionButtonType
{
    ACTION_BUTTON_SPELL     = 0x00,
    ACTION_BUTTON_C         = 0x01,                         // click?
    ACTION_BUTTON_EQSET     = 0x20,
    ACTION_BUTTON_MACRO     = 0x40,
    ACTION_BUTTON_CMACRO    = ACTION_BUTTON_C | ACTION_BUTTON_MACRO,
    ACTION_BUTTON_ITEM      = 0x80
};

#define ACTION_BUTTON_ACTION(X) (uint32(X) & 0x00FFFFFF)
#define ACTION_BUTTON_TYPE(X)   ((uint32(X) & 0xFF000000) >> 24)
#define MAX_ACTION_BUTTON_ACTION_VALUE (0x00FFFFFF+1)

#define PLAYER_MAX_SKILLS       127
#define PLAYER_MAX_DAILY_QUESTS 25

// Note: SPELLMOD_* values is aura types in fact
enum SpellModType
{
    SPELLMOD_FLAT         = 107,                            // SPELL_AURA_ADD_FLAT_MODIFIER
    SPELLMOD_PCT          = 108                             // SPELL_AURA_ADD_PCT_MODIFIER
};

// 2^n values, Player::m_isunderwater is a bitmask. These are mangos internal values, they are never send to any client
enum PlayerUnderwaterState
{
    UNDERWATER_NONE                     = 0x00,
    UNDERWATER_INWATER                  = 0x01,             // terrain type is water and player is afflicted by it
    UNDERWATER_INLAVA                   = 0x02,             // terrain type is lava and player is afflicted by it
    UNDERWATER_INSLIME                  = 0x04,             // terrain type is lava and player is afflicted by it
    UNDERWARER_INDARKWATER              = 0x08,             // terrain type is dark water and player is afflicted by it

    UNDERWATER_EXIST_TIMERS             = 0x10
};

enum PlayerSpellState
{
    PLAYERSPELL_UNCHANGED = 0,
    PLAYERSPELL_CHANGED   = 1,
    PLAYERSPELL_NEW       = 2,
    PLAYERSPELL_REMOVED   = 3
};
#define MAX_QUEST_OFFSET 5

enum QuestSlotStateMask
{
    QUEST_STATE_NONE     = 0x0000,
    QUEST_STATE_COMPLETE = 0x0001,
    QUEST_STATE_FAIL     = 0x0002
};

enum SkillUpdateState
{
    SKILL_UNCHANGED     = 0,
    SKILL_CHANGED       = 1,
    SKILL_NEW           = 2,
    SKILL_DELETED       = 3
};

enum PlayerSlots
{
    // first slot for item stored (in any way in player m_items data)
    PLAYER_SLOT_START           = 0,
    // last+1 slot for item stored (in any way in player m_items data)
    PLAYER_SLOT_END             = 150,
    PLAYER_SLOTS_COUNT          = (PLAYER_SLOT_END - PLAYER_SLOT_START)
};

#define INVENTORY_SLOT_BAG_0    255

enum EquipmentSlots                                         // 19 slots
{
    EQUIPMENT_SLOT_START        = 0,
    EQUIPMENT_SLOT_HEAD         = 0,
    EQUIPMENT_SLOT_NECK         = 1,
    EQUIPMENT_SLOT_SHOULDERS    = 2,
    EQUIPMENT_SLOT_BODY         = 3,
    EQUIPMENT_SLOT_CHEST        = 4,
    EQUIPMENT_SLOT_WAIST        = 5,
    EQUIPMENT_SLOT_LEGS         = 6,
    EQUIPMENT_SLOT_FEET         = 7,
    EQUIPMENT_SLOT_WRISTS       = 8,
    EQUIPMENT_SLOT_HANDS        = 9,
    EQUIPMENT_SLOT_FINGER1      = 10,
    EQUIPMENT_SLOT_FINGER2      = 11,
    EQUIPMENT_SLOT_TRINKET1     = 12,
    EQUIPMENT_SLOT_TRINKET2     = 13,
    EQUIPMENT_SLOT_BACK         = 14,
    EQUIPMENT_SLOT_MAINHAND     = 15,
    EQUIPMENT_SLOT_OFFHAND      = 16,
    EQUIPMENT_SLOT_RANGED       = 17,
    EQUIPMENT_SLOT_TABARD       = 18,
    EQUIPMENT_SLOT_END          = 19
};

enum InventorySlots                                         // 4 slots
{
    INVENTORY_SLOT_BAG_START    = 19,
    INVENTORY_SLOT_BAG_END      = 23
};

enum InventoryPackSlots                                     // 16 slots
{
    INVENTORY_SLOT_ITEM_START   = 23,
    INVENTORY_SLOT_ITEM_END     = 39
};

enum BankItemSlots                                          // 28 slots
{
    BANK_SLOT_ITEM_START        = 39,
    BANK_SLOT_ITEM_END          = 67
};

enum BankBagSlots                                           // 7 slots
{
    BANK_SLOT_BAG_START         = 67,
    BANK_SLOT_BAG_END           = 74
};

enum BuyBackSlots                                           // 12 slots
{
    // stored in m_buybackitems
    BUYBACK_SLOT_START          = 74,
    BUYBACK_SLOT_END            = 86
};

enum KeyRingSlots                                           // 32 slots
{
    KEYRING_SLOT_START          = 86,
    KEYRING_SLOT_END            = 118
};

enum CurrencyTokenSlots                                     // 32 slots
{
    CURRENCYTOKEN_SLOT_START    = 118,
    CURRENCYTOKEN_SLOT_END      = 150
};

enum EquipmentSetUpdateState
{
    EQUIPMENT_SET_UNCHANGED = 0,
    EQUIPMENT_SET_CHANGED   = 1,
    EQUIPMENT_SET_NEW       = 2,
    EQUIPMENT_SET_DELETED   = 3
};

struct EquipmentSet
{
    EquipmentSet() : Guid(0), state(EQUIPMENT_SET_NEW)
    {
        for(int i = 0; i < EQUIPMENT_SLOT_END; ++i)
            Items[i] = 0;
    }

    uint64 Guid;
    std::string Name;
    std::string IconName;
    uint32 Items[EQUIPMENT_SLOT_END];
    EquipmentSetUpdateState state;
};

#define MAX_EQUIPMENT_SET_INDEX 10                          // client limit

enum MapTypes                                               // Lua_IsInInstance
{
    MAP_COMMON          = 0,                                // none
    MAP_INSTANCE        = 1,                                // party
    MAP_RAID            = 2,                                // raid
    MAP_BATTLEGROUND    = 3,                                // pvp
    MAP_ARENA           = 4                                 // arena
};

// Client expected level limitation, like as used in DBC item max levels for "until max player level"
// use as default max player level, must be fit max level for used client
// also see MAX_LEVEL and STRONG_MAX_LEVEL define
#define DEFAULT_MAX_LEVEL 80

// client supported max level for player/pets/etc. Avoid overflow or client stability affected.
// also see GT_MAX_LEVEL define
#define MAX_LEVEL    100

// Server side limitation. Base at used code requirements.
// also see MAX_LEVEL and GT_MAX_LEVEL define
#define STRONG_MAX_LEVEL 255

enum BattleGroundBracketId                                  // bracketId for level ranges
{
    BG_BRACKET_ID_FIRST          = 0,
    BG_BRACKET_ID_LAST           = 15
};

// must be max value in PvPDificulty slot+1
#define MAX_BATTLEGROUND_BRACKETS  16

enum AreaTeams
{
    AREATEAM_NONE  = 0,
    AREATEAM_ALLY  = 2,
    AREATEAM_HORDE = 4
};

enum AchievementFactionFlags
{
    ACHIEVEMENT_FACTION_FLAG_HORDE    = 0x00000000,
    ACHIEVEMENT_FACTION_FLAG_ALLIANCE = 0x00000001,
};

enum AchievementFlags
{
    ACHIEVEMENT_FLAG_COUNTER           = 0x00000001,        // Just count statistic (never stop and complete)
    ACHIEVEMENT_FLAG_UNK2              = 0x00000002,        // not used
    ACHIEVEMENT_FLAG_STORE_MAX_VALUE   = 0x00000004,        // Store only max value? used only in "Reach level xx"
    ACHIEVEMENT_FLAG_SUMM              = 0x00000008,        // Use summ criteria value from all reqirements (and calculate max value)
    ACHIEVEMENT_FLAG_MAX_USED          = 0x00000010,        // Show max criteria (and calculate max value ??)
    ACHIEVEMENT_FLAG_REQ_COUNT         = 0x00000020,        // Use not zero req count (and calculate max value)
    ACHIEVEMENT_FLAG_AVERAGE           = 0x00000040,        // Show as average value (value / time_in_days) depend from other flag (by def use last criteria value)
    ACHIEVEMENT_FLAG_BAR               = 0x00000080,        // Show as progress bar (value / max vale) depend from other flag (by def use last criteria value)
    ACHIEVEMENT_FLAG_REALM_FIRST_REACH = 0x00000100,        //
    ACHIEVEMENT_FLAG_REALM_FIRST_KILL  = 0x00000200,        //
};

enum AchievementCriteriaCondition
{
    ACHIEVEMENT_CRITERIA_CONDITION_NONE      = 0,
    ACHIEVEMENT_CRITERIA_CONDITION_NO_DEATH  = 1,
    ACHIEVEMENT_CRITERIA_CONDITION_UNK1      = 2,           // only used in "Complete a daily quest every day for five consecutive days"
    ACHIEVEMENT_CRITERIA_CONDITION_MAP       = 3,           // requires you to be on specific map
    ACHIEVEMENT_CRITERIA_CONDITION_NO_LOOSE  = 4,           // only used in "Win 10 arenas without losing"
    ACHIEVEMENT_CRITERIA_CONDITION_UNK2      = 9,           // unk
    ACHIEVEMENT_CRITERIA_CONDITION_UNK3      = 13,          // unk
};

enum AchievementCriteriaCompletionFlags
{
    ACHIEVEMENT_CRITERIA_FLAG_SHOW_PROGRESS_BAR = 0x00000001,         // Show progress as bar
    ACHIEVEMENT_CRITERIA_FLAG_HIDE_CRITERIA     = 0x00000002,         // Not show criteria in client
    ACHIEVEMENT_CRITERIA_FLAG_UNK3              = 0x00000004,         // BG related??
    ACHIEVEMENT_CRITERIA_FLAG_UNK4              = 0x00000008,         //
    ACHIEVEMENT_CRITERIA_FLAG_UNK5              = 0x00000010,         // not used
    ACHIEVEMENT_CRITERIA_FLAG_MONEY_COUNTER     = 0x00000020,         // Displays counter as money
};

enum AchievementCriteriaGroupFlags
{
    // you mustn't be in a group while fulfilling this achievement
    ACHIEVEMENT_CRITERIA_GROUP_NOT_IN_GROUP = 2,
};

enum AchievementCriteriaTypes
{
    ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE = 0,
    ACHIEVEMENT_CRITERIA_TYPE_WIN_BG = 1,
    ACHIEVEMENT_CRITERIA_TYPE_REACH_LEVEL = 5,
    ACHIEVEMENT_CRITERIA_TYPE_REACH_SKILL_LEVEL = 7,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_ACHIEVEMENT = 8,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUEST_COUNT = 9,
    // you have to complete a daily quest x times in a row
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_DAILY_QUEST_DAILY = 10,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUESTS_IN_ZONE = 11,
    ACHIEVEMENT_CRITERIA_TYPE_DAMAGE_DONE = 13,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_DAILY_QUEST = 14,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_BATTLEGROUND= 15,
    ACHIEVEMENT_CRITERIA_TYPE_DEATH_AT_MAP= 16,
    ACHIEVEMENT_CRITERIA_TYPE_DEATH= 17,
    ACHIEVEMENT_CRITERIA_TYPE_DEATH_IN_DUNGEON = 18,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_RAID = 19,
    ACHIEVEMENT_CRITERIA_TYPE_KILLED_BY_CREATURE = 20,
    ACHIEVEMENT_CRITERIA_TYPE_KILLED_BY_PLAYER = 23,
    ACHIEVEMENT_CRITERIA_TYPE_FALL_WITHOUT_DYING = 24,
    ACHIEVEMENT_CRITERIA_TYPE_DEATHS_FROM = 26,
    ACHIEVEMENT_CRITERIA_TYPE_COMPLETE_QUEST = 27,
    ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET = 28,
    ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL= 29,
    ACHIEVEMENT_CRITERIA_TYPE_BG_OBJECTIVE_CAPTURE = 30,
    ACHIEVEMENT_CRITERIA_TYPE_HONORABLE_KILL_AT_AREA = 31,
    ACHIEVEMENT_CRITERIA_TYPE_WIN_ARENA = 32,
    ACHIEVEMENT_CRITERIA_TYPE_PLAY_ARENA = 33,
    ACHIEVEMENT_CRITERIA_TYPE_LEARN_SPELL = 34,
    // TODO: this criteria has additional conditions which can not be found in the dbcs
    ACHIEVEMENT_CRITERIA_TYPE_HONORABLE_KILL = 35,
    ACHIEVEMENT_CRITERIA_TYPE_OWN_ITEM = 36,
    // TODO: the archievements 1162 and 1163 requires a special rating which can't be found in the dbc
    ACHIEVEMENT_CRITERIA_TYPE_WIN_RATED_ARENA = 37,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_TEAM_RATING = 38,
    ACHIEVEMENT_CRITERIA_TYPE_REACH_TEAM_RATING = 39,
    ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILL_LEVEL = 40,
    ACHIEVEMENT_CRITERIA_TYPE_USE_ITEM = 41,
    ACHIEVEMENT_CRITERIA_TYPE_LOOT_ITEM= 42,
    ACHIEVEMENT_CRITERIA_TYPE_EXPLORE_AREA = 43,
    ACHIEVEMENT_CRITERIA_TYPE_OWN_RANK= 44,
    ACHIEVEMENT_CRITERIA_TYPE_BUY_BANK_SLOT= 45,
    ACHIEVEMENT_CRITERIA_TYPE_GAIN_REPUTATION= 46,
    ACHIEVEMENT_CRITERIA_TYPE_GAIN_EXALTED_REPUTATION= 47,
    // noted: rewarded as soon as the player payed, not at taking place at the seat
    ACHIEVEMENT_CRITERIA_TYPE_VISIT_BARBER_SHOP= 48,
    ACHIEVEMENT_CRITERIA_TYPE_EQUIP_EPIC_ITEM = 49,
    // TODO: itemlevel is mentioned in text but not present in dbc
    ACHIEVEMENT_CRITERIA_TYPE_ROLL_NEED_ON_LOOT = 50,
    ACHIEVEMENT_CRITERIA_TYPE_ROLL_GREED_ON_LOOT= 51,
    ACHIEVEMENT_CRITERIA_TYPE_HK_CLASS = 52,
    ACHIEVEMENT_CRITERIA_TYPE_HK_RACE = 53,
    ACHIEVEMENT_CRITERIA_TYPE_DO_EMOTE = 54,
    ACHIEVEMENT_CRITERIA_TYPE_HEALING_DONE = 55,
    // TODO: in some cases map not present, and in some cases need do without die
    ACHIEVEMENT_CRITERIA_TYPE_GET_KILLING_BLOWS = 56,
    ACHIEVEMENT_CRITERIA_TYPE_EQUIP_ITEM = 57,
    ACHIEVEMENT_CRITERIA_TYPE_MONEY_FROM_VENDORS = 59,
    ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_FOR_TALENTS = 60,
    ACHIEVEMENT_CRITERIA_TYPE_NUMBER_OF_TALENT_RESETS = 61,
    ACHIEVEMENT_CRITERIA_TYPE_MONEY_FROM_QUEST_REWARD = 62,
    ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_FOR_TRAVELLING = 63,
    ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_AT_BARBER = 65,
    ACHIEVEMENT_CRITERIA_TYPE_GOLD_SPENT_FOR_MAIL = 66,
    ACHIEVEMENT_CRITERIA_TYPE_LOOT_MONEY = 67,
    ACHIEVEMENT_CRITERIA_TYPE_USE_GAMEOBJECT = 68,
    ACHIEVEMENT_CRITERIA_TYPE_BE_SPELL_TARGET2= 69,
    ACHIEVEMENT_CRITERIA_TYPE_SPECIAL_PVP_KILL= 70,
    ACHIEVEMENT_CRITERIA_TYPE_FISH_IN_GAMEOBJECT = 72,
    // TODO: title id is not mentioned in dbc
    ACHIEVEMENT_CRITERIA_TYPE_EARNED_PVP_TITLE = 74,
    ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILLLINE_SPELLS= 75,
    ACHIEVEMENT_CRITERIA_TYPE_WIN_DUEL = 76,
    ACHIEVEMENT_CRITERIA_TYPE_LOSE_DUEL = 77,
    // TODO: creature type (demon, undead etc.) is not stored in dbc
    ACHIEVEMENT_CRITERIA_TYPE_KILL_CREATURE_TYPE = 78,
    ACHIEVEMENT_CRITERIA_TYPE_GOLD_EARNED_BY_AUCTIONS= 80,
    ACHIEVEMENT_CRITERIA_TYPE_CREATE_AUCTION= 82,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_AUCTION_BID= 83,
    ACHIEVEMENT_CRITERIA_TYPE_WON_AUCTIONS= 84,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_AUCTION_SOLD = 85,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_GOLD_VALUE_OWNED = 86,
    ACHIEVEMENT_CRITERIA_TYPE_GAIN_REVERED_REPUTATION = 87,
    ACHIEVEMENT_CRITERIA_TYPE_GAIN_HONORED_REPUTATION = 88,
    ACHIEVEMENT_CRITERIA_TYPE_KNOWN_FACTIONS = 89,
    ACHIEVEMENT_CRITERIA_TYPE_LOOT_EPIC_ITEM = 90,
    ACHIEVEMENT_CRITERIA_TYPE_RECEIVE_EPIC_ITEM = 91,
    ACHIEVEMENT_CRITERIA_TYPE_ROLL_NEED = 93,
    ACHIEVEMENT_CRITERIA_TYPE_ROLL_GREED = 94,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HEALTH = 95,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_POWER = 96,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_STAT = 97,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_SPELLPOWER = 98,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_ARMOR = 99,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_RATING = 100,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HIT_DEALT = 101,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HIT_RECEIVED = 102,
    ACHIEVEMENT_CRITERIA_TYPE_TOTAL_DAMAGE_RECEIVED = 103,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HEAL_CASTED = 104,
    ACHIEVEMENT_CRITERIA_TYPE_TOTAL_HEALING_RECEIVED = 105,
    ACHIEVEMENT_CRITERIA_TYPE_HIGHEST_HEALING_RECEIVED = 106,
    ACHIEVEMENT_CRITERIA_TYPE_QUEST_ABANDONED = 107,
    ACHIEVEMENT_CRITERIA_TYPE_FLIGHT_PATHS_TAKEN = 108,
    ACHIEVEMENT_CRITERIA_TYPE_LOOT_TYPE = 109,
    // TODO: target entry is missing
    ACHIEVEMENT_CRITERIA_TYPE_CAST_SPELL2 = 110,
    ACHIEVEMENT_CRITERIA_TYPE_LEARN_SKILL_LINE= 112,
    ACHIEVEMENT_CRITERIA_TYPE_EARN_HONORABLE_KILL = 113,
    ACHIEVEMENT_CRITERIA_TYPE_ACCEPTED_SUMMONINGS = 114,
    ACHIEVEMENT_CRITERIA_TYPE_EARN_ACHIEVEMENT_POINTS = 115,
    ACHIEVEMENT_CRITERIA_TYPE_USE_LFD_TO_GROUP_WITH_PLAYERS = 119,
    // 0..119 => 120 criteria types total
    ACHIEVEMENT_CRITERIA_TYPE_TOTAL = 120,
};

enum AreaFlags
{
    AREA_FLAG_SNOW                  = 0x00000001,           // snow (only Dun Morogh, Naxxramas, Razorfen Downs and Winterspring)
    AREA_FLAG_UNK1                  = 0x00000002,           // may be necropolis?
    AREA_FLAG_UNK2                  = 0x00000004,           // Only used for areas on map 571 (development before)
    AREA_FLAG_SLAVE_CAPITAL         = 0x00000008,           // city and city subsones
    AREA_FLAG_UNK3                  = 0x00000010,           // can't find common meaning
    AREA_FLAG_SLAVE_CAPITAL2        = 0x00000020,           // slave capital city flag?
    AREA_FLAG_UNK4                  = 0x00000040,           // many zones have this flag
    AREA_FLAG_ARENA                 = 0x00000080,           // arena, both instanced and world arenas
    AREA_FLAG_CAPITAL               = 0x00000100,           // main capital city flag
    AREA_FLAG_CITY                  = 0x00000200,           // only for one zone named "City" (where it located?)
    AREA_FLAG_OUTLAND               = 0x00000400,           // expansion zones? (only Eye of the Storm not have this flag, but have 0x00004000 flag)
    AREA_FLAG_SANCTUARY             = 0x00000800,           // sanctuary area (PvP disabled)
    AREA_FLAG_NEED_FLY              = 0x00001000,           // only Netherwing Ledge, Socrethar's Seat, Tempest Keep, The Arcatraz, The Botanica, The Mechanar, Sorrow Wing Point, Dragonspine Ridge, Netherwing Mines, Dragonmaw Base Camp, Dragonmaw Skyway
    AREA_FLAG_UNUSED1               = 0x00002000,           // not used now (no area/zones with this flag set in 3.0.3)
    AREA_FLAG_OUTLAND2              = 0x00004000,           // expansion zones? (only Circle of Blood Arena not have this flag, but have 0x00000400 flag)
    AREA_FLAG_PVP                   = 0x00008000,           // pvp objective area? (Death's Door also has this flag although it's no pvp object area)
    AREA_FLAG_ARENA_INSTANCE        = 0x00010000,           // used by instanced arenas only
    AREA_FLAG_UNUSED2               = 0x00020000,           // not used now (no area/zones with this flag set in 3.0.3)
    AREA_FLAG_UNK5                  = 0x00040000,           // only used for Amani Pass, Hatchet Hills
    AREA_FLAG_UNK6                  = 0x00080000,           // Valgarde and Acherus: The Ebon Hold
    AREA_FLAG_LOWLEVEL              = 0x00100000,           // used for some starting areas with area_level <=15
    AREA_FLAG_TOWN                  = 0x00200000,           // small towns with Inn
    AREA_FLAG_UNK7                  = 0x00400000,           // Warsong Hold, Acherus: The Ebon Hold, New Agamand Inn, Vengeance Landing Inn
    AREA_FLAG_UNK8                  = 0x00800000,           // Westguard Inn, Acherus: The Ebon Hold, Valgarde
    AREA_FLAG_OUTDOOR_PVP           = 0x01000000,           // Wintergrasp and it's subzones
    AREA_FLAG_UNK9                  = 0x02000000,           // unknown
    AREA_FLAG_UNK10                 = 0x04000000,           // unknown
    AREA_FLAG_CAN_HEARTH_AND_RES    = 0x08000000            // Wintergrasp and it's subzones
    // 0x20000000 not flyable?
};

enum Difficulty
{
    REGULAR_DIFFICULTY           = 0,

    DUNGEON_DIFFICULTY_NORMAL    = 0,
    DUNGEON_DIFFICULTY_HEROIC    = 1,
    //DUNGEON_DIFFICULTY_EPIC    = 2,                       // not used, but exists

    RAID_DIFFICULTY_10MAN_NORMAL = 0,
    RAID_DIFFICULTY_25MAN_NORMAL = 1,
    RAID_DIFFICULTY_10MAN_HEROIC = 2,
    RAID_DIFFICULTY_25MAN_HEROIC = 3,
};

#define MAX_DUNGEON_DIFFICULTY     2
#define MAX_RAID_DIFFICULTY        4
#define MAX_DIFFICULTY             4

enum SpawnMask
{
    SPAWNMASK_REGULAR           = (1 << REGULAR_DIFFICULTY),// any any maps without spawn modes (continents/subway) or in minimal spawnmode

    SPAWNMASK_DUNGEON_NORMAL    = (1 << DUNGEON_DIFFICULTY_NORMAL),
    SPAWNMASK_DUNGEON_HEROIC    = (1 << DUNGEON_DIFFICULTY_HEROIC),
    SPAWNMASK_DUNGEON_ALL       = (SPAWNMASK_DUNGEON_NORMAL | SPAWNMASK_DUNGEON_HEROIC),

    SPAWNMASK_RAID_10MAN_NORMAL = (1 << RAID_DIFFICULTY_10MAN_NORMAL),
    SPAWNMASK_RAID_25MAN_NORMAL = (1 << RAID_DIFFICULTY_25MAN_NORMAL),
    SPAWNMASK_RAID_NORMAL_ALL   = (SPAWNMASK_RAID_10MAN_NORMAL | SPAWNMASK_RAID_25MAN_NORMAL),

    SPAWNMASK_RAID_10MAN_HEROIC = (1 << RAID_DIFFICULTY_10MAN_HEROIC),
    SPAWNMASK_RAID_25MAN_HEROIC = (1 << RAID_DIFFICULTY_25MAN_HEROIC),
    SPAWNMASK_RAID_HEROIC_ALL   = (SPAWNMASK_RAID_10MAN_HEROIC | SPAWNMASK_RAID_25MAN_HEROIC),

    SPAWNMASK_RAID_ALL          = (SPAWNMASK_RAID_NORMAL_ALL | SPAWNMASK_RAID_HEROIC_ALL),
};

enum FactionTemplateFlags
{
    FACTION_TEMPLATE_FLAG_PVP               = 0x00000800,   // flagged for PvP
    FACTION_TEMPLATE_FLAG_CONTESTED_GUARD   = 0x00001000,   // faction will attack players that were involved in PvP combats
};

enum FactionMasks
{
    FACTION_MASK_PLAYER   = 1,                              // any player
    FACTION_MASK_ALLIANCE = 2,                              // player or creature from alliance team
    FACTION_MASK_HORDE    = 4,                              // player or creature from horde team
    FACTION_MASK_MONSTER  = 8                               // aggressive creature from monster team
    // if none flags set then non-aggressive creature
};

enum AbilytyLearnType
{
    ABILITY_LEARNED_ON_GET_PROFESSION_SKILL     = 1,
    ABILITY_LEARNED_ON_GET_RACE_OR_CLASS_SKILL  = 2
};

enum ItemEnchantmentType
{
    ITEM_ENCHANTMENT_TYPE_NONE             = 0,
    ITEM_ENCHANTMENT_TYPE_COMBAT_SPELL     = 1,
    ITEM_ENCHANTMENT_TYPE_DAMAGE           = 2,
    ITEM_ENCHANTMENT_TYPE_EQUIP_SPELL      = 3,
    ITEM_ENCHANTMENT_TYPE_RESISTANCE       = 4,
    ITEM_ENCHANTMENT_TYPE_STAT             = 5,
    ITEM_ENCHANTMENT_TYPE_TOTEM            = 6,
    ITEM_ENCHANTMENT_TYPE_USE_SPELL        = 7,
    ITEM_ENCHANTMENT_TYPE_PRISMATIC_SOCKET = 8
};

enum ItemLimitCategoryMode
{
    ITEM_LIMIT_CATEGORY_MODE_HAVE  = 0,                      // limit applied to amount items in inventory/bank
    ITEM_LIMIT_CATEGORY_MODE_EQUIP = 1,                      // limit applied to amount equipped items (including used gems)
};

// some used in code cases
enum ItemLimitCategory
{
    ITEM_LIMIT_CATEGORY_MANA_GEM   = 4,
};

enum TotemCategoryType
{
    TOTEM_CATEGORY_TYPE_KNIFE   = 1,
    TOTEM_CATEGORY_TYPE_TOTEM   = 2,
    TOTEM_CATEGORY_TYPE_ROD     = 3,
    TOTEM_CATEGORY_TYPE_PICK    = 21,
    TOTEM_CATEGORY_TYPE_STONE   = 22,
    TOTEM_CATEGORY_TYPE_HAMMER  = 23,
    TOTEM_CATEGORY_TYPE_SPANNER = 24
};

// SummonProperties.dbc, col 1
enum SummonPropGroup
{
    SUMMON_PROP_GROUP_WILD           = 0,
    SUMMON_PROP_GROUP_FRIENDLY       = 1,
    SUMMON_PROP_GROUP_PETS           = 2,
    SUMMON_PROP_GROUP_CONTROLLABLE   = 3,
    SUMMON_PROP_GROUP_VEHICLE        = 4
};

// SummonProperties.dbc, col 3
enum SummonPropType
{
    SUMMON_PROP_TYPE_OTHER           = 0,                   // different summons, 1330 spells in 3.0.3
    SUMMON_PROP_TYPE_SUMMON          = 1,                   // generic summons, 49 spells in 3.0.3
    SUMMON_PROP_TYPE_GUARDIAN        = 2,                   // summon guardian, 393 spells in 3.0.3
    SUMMON_PROP_TYPE_ARMY            = 3,                   // summon army, 5 spells in 3.0.3
    SUMMON_PROP_TYPE_TOTEM           = 4,                   // summon totem, 169 spells in 3.0.3
    SUMMON_PROP_TYPE_CRITTER         = 5,                   // critter/minipet, 195 spells in 3.0.3
    SUMMON_PROP_TYPE_DK              = 6,                   // summon DRW/Ghoul, 2 spells in 3.0.3 "%s's Runeblade"
    SUMMON_PROP_TYPE_CONSTRUCT       = 7,                   // summon bot/bomb, 4 spells in 3.0.3 "%s's Construct"
    SUMMON_PROP_TYPE_PHASING         = 8,                   // something todo with DK prequest line, 2 spells in 3.0.3 "%s's Opponent"
    SUMMON_PROP_TYPE_SIEGE_VEH       = 9,                   // summon different vehicles, 14 spells in 3.0.3 "%s's Vehicle"
    SUMMON_PROP_TYPE_DRAKE_VEH       = 10,                  // summon drake (vehicle), 3 spells
    SUMMON_PROP_TYPE_LIGHTWELL       = 11,                  // summon lightwell, 6 spells in 3.0.3
    SUMMON_PROP_TYPE_REPAIR_BOT      = 12                   // summon repir bot, 1 spells in 3.2.2a
};

// SummonProperties.dbc, col 5
enum SummonPropFlags
{
    SUMMON_PROP_FLAG_NONE              = 0x0000,            // 1342 spells in 3.0.3
    SUMMON_PROP_FLAG_UNK1              = 0x0001,            // 75 spells in 3.0.3, something unfriendly
    SUMMON_PROP_FLAG_UNK2              = 0x0002,            // 616 spells in 3.0.3, something friendly
    SUMMON_PROP_FLAG_UNK3              = 0x0004,            // 22 spells in 3.0.3, no idea...
    SUMMON_PROP_FLAG_UNK4              = 0x0008,            // 49 spells in 3.0.3, some mounts
    SUMMON_PROP_FLAG_UNK5              = 0x0010,            // 25 spells in 3.0.3, quest related?
    SUMMON_PROP_FLAG_CANT_BE_DISMISSED = 0x0020,            // 0 spells in 3.0.3, unused
    SUMMON_PROP_FLAG_UNK7              = 0x0040,            // 12 spells in 3.0.3, no idea
    SUMMON_PROP_FLAG_UNK8              = 0x0080,            // 4 spells in 3.0.3, no idea
    SUMMON_PROP_FLAG_UNK9              = 0x0100,            // 51 spells in 3.0.3, no idea, many quest related
    SUMMON_PROP_FLAG_UNK10             = 0x0200,            // 51 spells in 3.0.3, something defensive
    SUMMON_PROP_FLAG_UNK11             = 0x0400,            // 3 spells, requires something near?
    SUMMON_PROP_FLAG_UNK12             = 0x0800,            // 30 spells in 3.0.3, no idea
    SUMMON_PROP_FLAG_UNK13             = 0x1000,            // 8 spells in 3.0.3, siege vehicle
    SUMMON_PROP_FLAG_UNK14             = 0x2000,            // 2 spells in 3.0.3, escort?
};

enum SpellEffectIndex
{
    EFFECT_INDEX_0     = 0,
    EFFECT_INDEX_1     = 1,
    EFFECT_INDEX_2     = 2
};

#define MAX_EFFECT_INDEX 3
enum LocaleConstant
{
    LOCALE_enUS = 0,                                        // also enGB
    LOCALE_koKR = 1,
    LOCALE_frFR = 2,
    LOCALE_deDE = 3,
    LOCALE_zhCN = 4,
    LOCALE_zhTW = 5,
    LOCALE_esES = 6,
    LOCALE_esMX = 7,
    LOCALE_ruRU = 8
};

#define MAKE_PAIR64(l, h)  uint64( uint32(l) | ( uint64(h) << 32 ) )
#define PAIR64_HIPART(x)   (uint32)((uint64(x) >> 32) & UI64LIT(0x00000000FFFFFFFF))
#define PAIR64_LOPART(x)   (uint32)(uint64(x)         & UI64LIT(0x00000000FFFFFFFF))

#define MAKE_PAIR32(l, h)  uint32( uint16(l) | ( uint32(h) << 16 ) )
#define PAIR32_HIPART(x)   (uint16)((uint32(x) >> 16) & 0x0000FFFF)
#define PAIR32_LOPART(x)   (uint16)(uint32(x)         & 0x0000FFFF)

#define TaxiMaskSize 12

#define MAX_HEIGHT            100000.0f                     // can be use for find ground height at surface
#define INVALID_HEIGHT       -100000.0f                     // for check, must be equal to VMAP_INVALID_HEIGHT, real value for unknown height is VMAP_INVALID_HEIGHT_VALUE
#define MIN_UNLOAD_DELAY      1                             // immediate unload

#define MAX_NUMBER_OF_GRIDS      64

#define SIZE_OF_GRIDS            533.33333f
#define CENTER_GRID_ID           (MAX_NUMBER_OF_GRIDS/2)

#define CENTER_GRID_OFFSET      (SIZE_OF_GRIDS/2)

#define MIN_GRID_DELAY          (MINUTE*IN_MILISECONDS)
#define MIN_MAP_UPDATE_DELAY    50

#define MAX_NUMBER_OF_CELLS     8
#define SIZE_OF_GRID_CELL       (SIZE_OF_GRIDS/MAX_NUMBER_OF_CELLS)

#define CENTER_GRID_CELL_ID     (MAX_NUMBER_OF_CELLS*MAX_NUMBER_OF_GRIDS/2)
#define CENTER_GRID_CELL_OFFSET (SIZE_OF_GRID_CELL/2)

#define TOTAL_NUMBER_OF_CELLS_PER_MAP    (MAX_NUMBER_OF_GRIDS*MAX_NUMBER_OF_CELLS)

#define MAP_RESOLUTION 128

#define MAP_SIZE                (SIZE_OF_GRIDS*MAX_NUMBER_OF_GRIDS)
#define MAP_HALFSIZE            (MAP_SIZE/2)

enum ZLiquidStatus
{
    LIQUID_MAP_NO_WATER     = 0x00000000,
    LIQUID_MAP_ABOVE_WATER  = 0x00000001,
    LIQUID_MAP_WATER_WALK   = 0x00000002,
    LIQUID_MAP_IN_WATER     = 0x00000004,
    LIQUID_MAP_UNDER_WATER  = 0x00000008
};

enum CharacterFlags
{
    CHARACTER_FLAG_NONE                 = 0x00000000,
    CHARACTER_FLAG_UNK1                 = 0x00000001,
    CHARACTER_FLAG_UNK2                 = 0x00000002,
    CHARACTER_LOCKED_FOR_TRANSFER       = 0x00000004,
    CHARACTER_FLAG_UNK4                 = 0x00000008,
    CHARACTER_FLAG_UNK5                 = 0x00000010,
    CHARACTER_FLAG_UNK6                 = 0x00000020,
    CHARACTER_FLAG_UNK7                 = 0x00000040,
    CHARACTER_FLAG_UNK8                 = 0x00000080,
    CHARACTER_FLAG_UNK9                 = 0x00000100,
    CHARACTER_FLAG_UNK10                = 0x00000200,
    CHARACTER_FLAG_HIDE_HELM            = 0x00000400,
    CHARACTER_FLAG_HIDE_CLOAK           = 0x00000800,
    CHARACTER_FLAG_UNK13                = 0x00001000,
    CHARACTER_FLAG_GHOST                = 0x00002000,
    CHARACTER_FLAG_RENAME               = 0x00004000,
    CHARACTER_FLAG_UNK16                = 0x00008000,
    CHARACTER_FLAG_UNK17                = 0x00010000,
    CHARACTER_FLAG_UNK18                = 0x00020000,
    CHARACTER_FLAG_UNK19                = 0x00040000,
    CHARACTER_FLAG_UNK20                = 0x00080000,
    CHARACTER_FLAG_UNK21                = 0x00100000,
    CHARACTER_FLAG_UNK22                = 0x00200000,
    CHARACTER_FLAG_UNK23                = 0x00400000,
    CHARACTER_FLAG_UNK24                = 0x00800000,
    CHARACTER_FLAG_LOCKED_BY_BILLING    = 0x01000000,
    CHARACTER_FLAG_DECLINED             = 0x02000000,
    CHARACTER_FLAG_UNK27                = 0x04000000,
    CHARACTER_FLAG_UNK28                = 0x08000000,
    CHARACTER_FLAG_UNK29                = 0x10000000,
    CHARACTER_FLAG_UNK30                = 0x20000000,
    CHARACTER_FLAG_UNK31                = 0x40000000,
    CHARACTER_FLAG_UNK32                = 0x80000000
};

enum eAuthCmd
{
    AUTH_LOGON_CHALLENGE        = 0x00,
    AUTH_LOGON_PROOF            = 0x01,
    AUTH_RECONNECT_CHALLENGE    = 0x02,
    AUTH_RECONNECT_PROOF        = 0x03,
    //update srv =4
    REALM_LIST                  = 0x10,
    XFER_INITIATE               = 0x30,
    XFER_DATA                   = 0x31,
    XFER_ACCEPT                 = 0x32,
    XFER_RESUME                 = 0x33,
    XFER_CANCEL                 = 0x34
};

enum __QuestFlags
{
    // Flags used at server and sent to client
    QUEST_FLAGS_STAY_ALIVE     = 0x00000001,                // Not used currently
    QUEST_FLAGS_PARTY_ACCEPT   = 0x00000002,                // If player in party, all players that can accept this quest will receive confirmation box to accept quest CMSG_QUEST_CONFIRM_ACCEPT/SMSG_QUEST_CONFIRM_ACCEPT
    QUEST_FLAGS_EXPLORATION    = 0x00000004,                // Not used currently
    QUEST_FLAGS_SHARABLE       = 0x00000008,                // Can be shared: Player::CanShareQuest()
    //QUEST_FLAGS_NONE2        = 0x00000010,                // Not used currently
    QUEST_FLAGS_EPIC           = 0x00000020,                // Not used currently - 1 quest in 3.3
    QUEST_FLAGS_RAID           = 0x00000040,                // Not used currently
    QUEST_FLAGS_TBC            = 0x00000080,                // Not used currently: Available if TBC expansion enabled only
    QUEST_FLAGS_UNK2           = 0x00000100,                // Not used currently: _DELIVER_MORE Quest needs more than normal _q-item_ drops from mobs
    QUEST_FLAGS_HIDDEN_REWARDS = 0x00000200,                // Items and money rewarded only sent in SMSG_QUESTGIVER_OFFER_REWARD (not in SMSG_QUESTGIVER_QUEST_DETAILS or in client quest log(SMSG_QUEST_QUERY_RESPONSE))
    QUEST_FLAGS_AUTO_REWARDED  = 0x00000400,                // These quests are automatically rewarded on quest complete and they will never appear in quest log client side.
    QUEST_FLAGS_TBC_RACES      = 0x00000800,                // Not used currently: Blood elf/Draenei starting zone quests
    QUEST_FLAGS_DAILY          = 0x00001000,                // Used to know quest is Daily one
    QUEST_FLAGS_UNK3           = 0x00002000,                // activates PvP?
    QUEST_FLAGS_UNK4           = 0x00004000,                // ? Membership Card Renewal
    QUEST_FLAGS_WEEKLY         = 0x00008000,                // Not used currently: Weekly quests
    // 0x20000 - 1 quest in 3.3, 0x40000 - 1 quest in 3.3
    QUEST_FLAGS_LOW_LEVEL      = 0x00080000,                // quests in starting areas

    // Mangos flags for set SpecialFlags in DB if required but used only at server
    QUEST_MANGOS_FLAGS_REPEATABLE           = 0x01000000,   // Set by 1 in SpecialFlags from DB
    QUEST_MANGOS_FLAGS_EXPLORATION_OR_EVENT = 0x02000000,   // Set by 2 in SpecialFlags from DB (if required area explore, spell SPELL_EFFECT_QUEST_COMPLETE casting, table `*_script` command SCRIPT_COMMAND_QUEST_EXPLORED use, set from script DLL)
    QUEST_MANGOS_FLAGS_DB_ALLOWED = 0xFFFFFF | QUEST_MANGOS_FLAGS_REPEATABLE | QUEST_MANGOS_FLAGS_EXPLORATION_OR_EVENT,

    // Mangos flags for internal use only
    QUEST_MANGOS_FLAGS_DELIVER              = 0x04000000,   // Internal flag computed only
    QUEST_MANGOS_FLAGS_SPEAKTO              = 0x08000000,   // Internal flag computed only
    QUEST_MANGOS_FLAGS_KILL_OR_CAST         = 0x10000000,   // Internal flag computed only
    QUEST_MANGOS_FLAGS_TIMED                = 0x20000000,   // Internal flag computed only
};

enum HitInfo
{
    HITINFO_NORMALSWING         = 0x00000000,
    HITINFO_UNK1                = 0x00000001,               // req correct packet structure
    HITINFO_NORMALSWING2        = 0x00000002,
    HITINFO_LEFTSWING           = 0x00000004,
    HITINFO_UNK2                = 0x00000008,
    HITINFO_MISS                = 0x00000010,
    HITINFO_ABSORB              = 0x00000020,               // absorbed damage
    HITINFO_ABSORB2             = 0x00000040,               // absorbed damage
    HITINFO_RESIST              = 0x00000080,               // resisted atleast some damage
    HITINFO_RESIST2             = 0x00000100,               // resisted atleast some damage
    HITINFO_CRITICALHIT         = 0x00000200,               // critical hit
    // 0x00000400
    // 0x00000800
    // 0x00001000
    HITINFO_BLOCK               = 0x00002000,               // blocked damage
    // 0x00004000
    // 0x00008000
    HITINFO_GLANCING            = 0x00010000,
    HITINFO_CRUSHING            = 0x00020000,
    HITINFO_NOACTION            = 0x00040000,               // guessed
    // 0x00080000
    // 0x00100000
    HITINFO_SWINGNOHITSOUND     = 0x00200000,               // guessed
    // 0x00400000
    HITINFO_UNK3                = 0x00800000
};

enum VictimState
{
    VICTIMSTATE_UNKNOWN1       = 0,
    VICTIMSTATE_NORMAL         = 1,
    VICTIMSTATE_DODGE          = 2,
    VICTIMSTATE_PARRY          = 3,
    VICTIMSTATE_INTERRUPT      = 4,
    VICTIMSTATE_BLOCKS         = 5,
    VICTIMSTATE_EVADES         = 6,
    VICTIMSTATE_IS_IMMUNE      = 7,
    VICTIMSTATE_DEFLECTS       = 8
};

enum AuthResult
{
    WOW_SUCCESS                     = 0x00,
    WOW_FAIL_UNKNOWN0               = 0x01,                 ///< ? Unable to connect
    WOW_FAIL_UNKNOWN1               = 0x02,                 ///< ? Unable to connect
    WOW_FAIL_BANNED                 = 0x03,                 ///< This <game> account has been closed and is no longer available for use. Please go to <site>/banned.html for further information.
    WOW_FAIL_UNKNOWN_ACCOUNT        = 0x04,                 ///< The information you have entered is not valid. Please check the spelling of the account name and password. If you need help in retrieving a lost or stolen password, see <site> for more information
    WOW_FAIL_INCORRECT_PASSWORD     = 0x05,                 ///< The information you have entered is not valid. Please check the spelling of the account name and password. If you need help in retrieving a lost or stolen password, see <site> for more information
                                                            // client reject next login attempts after this error, so in code used WOW_FAIL_UNKNOWN_ACCOUNT for both cases
    WOW_FAIL_ALREADY_ONLINE         = 0x06,                 ///< This account is already logged into <game>. Please check the spelling and try again.
    WOW_FAIL_NO_TIME                = 0x07,                 ///< You have used up your prepaid time for this account. Please purchase more to continue playing
    WOW_FAIL_DB_BUSY                = 0x08,                 ///< Could not log in to <game> at this time. Please try again later.
    WOW_FAIL_VERSION_INVALID        = 0x09,                 ///< Unable to validate game version. This may be caused by file corruption or interference of another program. Please visit <site> for more information and possible solutions to this issue.
    WOW_FAIL_VERSION_UPDATE         = 0x0A,                 ///< Downloading
    WOW_FAIL_INVALID_SERVER         = 0x0B,                 ///< Unable to connect
    WOW_FAIL_SUSPENDED              = 0x0C,                 ///< This <game> account has been temporarily suspended. Please go to <site>/banned.html for further information
    WOW_FAIL_FAIL_NOACCESS          = 0x0D,                 ///< Unable to connect
    WOW_SUCCESS_SURVEY              = 0x0E,                 ///< Connected.
    WOW_FAIL_PARENTCONTROL          = 0x0F,                 ///< Access to this account has been blocked by parental controls. Your settings may be changed in your account preferences at <site>
    WOW_FAIL_LOCKED_ENFORCED        = 0x10,                 ///< You have applied a lock to your account. You can change your locked status by calling your account lock phone number.
    WOW_FAIL_TRIAL_ENDED            = 0x11,                 ///< Your trial subscription has expired. Please visit <site> to upgrade your account.
    WOW_FAIL_USE_BATTLENET          = 0x12,                 ///< WOW_FAIL_OTHER This account is now attached to a Battle.net account. Please login with your Battle.net account email address and password.
};

enum RealmFlags
{
    REALM_FLAG_NONE         = 0x00,
    REALM_FLAG_INVALID      = 0x01,
    REALM_FLAG_OFFLINE      = 0x02,
    REALM_FLAG_SPECIFYBUILD = 0x04,                         // client will show realm version in RealmList screen in form "RealmName (major.minor.revision.build)"
    REALM_FLAG_UNK1         = 0x08,
    REALM_FLAG_UNK2         = 0x10,
    REALM_FLAG_NEW_PLAYERS  = 0x20,
    REALM_FLAG_RECOMMENDED  = 0x40,
    REALM_FLAG_FULL         = 0x80
};

enum FactionFlags
{
    FACTION_FLAG_VISIBLE            = 0x01,                 // makes visible in client (set or can be set at interaction with target of this faction)
    FACTION_FLAG_AT_WAR             = 0x02,                 // enable AtWar-button in client. player controlled (except opposition team always war state), Flag only set on initial creation
    FACTION_FLAG_HIDDEN             = 0x04,                 // hidden faction from reputation pane in client (player can gain reputation, but this update not sent to client)
    FACTION_FLAG_INVISIBLE_FORCED   = 0x08,                 // always overwrite FACTION_FLAG_VISIBLE and hide faction in rep.list, used for hide opposite team factions
    FACTION_FLAG_PEACE_FORCED       = 0x10,                 // always overwrite FACTION_FLAG_AT_WAR, used for prevent war with own team factions
    FACTION_FLAG_INACTIVE           = 0x20,                 // player controlled, state stored in characters.data ( CMSG_SET_FACTION_INACTIVE )
    FACTION_FLAG_RIVAL              = 0x40                  // flag for the two competing outland factions
};

enum SpellModOp
{
    SPELLMOD_DAMAGE                 = 0,
    SPELLMOD_DURATION               = 1,
    SPELLMOD_THREAT                 = 2,
    SPELLMOD_EFFECT1                = 3,
    SPELLMOD_CHARGES                = 4,
    SPELLMOD_RANGE                  = 5,
    SPELLMOD_RADIUS                 = 6,
    SPELLMOD_CRITICAL_CHANCE        = 7,
    SPELLMOD_ALL_EFFECTS            = 8,
    SPELLMOD_NOT_LOSE_CASTING_TIME  = 9,
    SPELLMOD_CASTING_TIME           = 10,
    SPELLMOD_COOLDOWN               = 11,
    SPELLMOD_EFFECT2                = 12,
    // spellmod 13 unused
    SPELLMOD_COST                   = 14,
    SPELLMOD_CRIT_DAMAGE_BONUS      = 15,
    SPELLMOD_RESIST_MISS_CHANCE     = 16,
    SPELLMOD_JUMP_TARGETS           = 17,
    SPELLMOD_CHANCE_OF_SUCCESS      = 18,                   // Only used with SPELL_AURA_ADD_FLAT_MODIFIER and affects proc spells
    SPELLMOD_ACTIVATION_TIME        = 19,
    SPELLMOD_EFFECT_PAST_FIRST      = 20,
    SPELLMOD_GLOBAL_COOLDOWN        = 21,
    SPELLMOD_DOT                    = 22,
    SPELLMOD_EFFECT3                = 23,
    SPELLMOD_SPELL_BONUS_DAMAGE     = 24,
    // spellmod 25 unused
    SPELLMOD_FREQUENCY_OF_SUCCESS   = 26,                   // Only used with SPELL_AURA_ADD_PCT_MODIFIER and affects used on proc spells
    SPELLMOD_MULTIPLE_VALUE         = 27,
    SPELLMOD_RESIST_DISPEL_CHANCE   = 28
};

enum ServerMSTimeMutiParamType
{
	STM_MONSTER_MOVE = 1,
	STM_MOVEMENT_INFO,
	STM_DYNAMICOBJECT_CASTTIME,
	STM_MSG_MOVE_TELEPORT_ACK,
	STM_MSG_MOVE_SPEED_CHANGE,
	STM_SMSG_SPELL_GO,
	STM_MAX_MS_TIME_TYPE
};

enum SpellFamilyNames
{
    SPELLFAMILY_GENERIC     = 0,
    SPELLFAMILY_UNK1        = 1,                            // events, holidays
    // 2 - unused
    SPELLFAMILY_MAGE        = 3,
    SPELLFAMILY_WARRIOR     = 4,
    SPELLFAMILY_WARLOCK     = 5,
    SPELLFAMILY_PRIEST      = 6,
    SPELLFAMILY_DRUID       = 7,
    SPELLFAMILY_ROGUE       = 8,
    SPELLFAMILY_HUNTER      = 9,
    SPELLFAMILY_PALADIN     = 10,
    SPELLFAMILY_SHAMAN      = 11,
    SPELLFAMILY_UNK2        = 12,                           // 2 spells (silence resistance)
    SPELLFAMILY_POTION      = 13,
    // 14 - unused
    SPELLFAMILY_DEATHKNIGHT = 15,
    // 16 - unused
    SPELLFAMILY_PET         = 17
};

enum ActiveStates
{
    ACT_PASSIVE  = 0x01,                                    // 0x01 - passive
    ACT_DISABLED = 0x81,                                    // 0x80 - castable
    ACT_ENABLED  = 0xC1,                                    // 0x40 | 0x80 - auto cast + castable
    ACT_COMMAND  = 0x07,                                    // 0x01 | 0x02 | 0x04
    ACT_REACTION = 0x06,                                    // 0x02 | 0x04
    ACT_DECIDE   = 0x00                                     // custom
};

enum ActionBarIndex
{
    ACTION_BAR_INDEX_START = 0,
    ACTION_BAR_INDEX_PET_SPELL_START = 3,
    ACTION_BAR_INDEX_PET_SPELL_END = 7,
    ACTION_BAR_INDEX_END = 10,
};

#define MAX_SPELLMOD 32

#define MAP_LIQUID_TYPE_NO_WATER    0x00
#define MAP_LIQUID_TYPE_WATER       0x01
#define MAP_LIQUID_TYPE_OCEAN       0x02
#define MAP_LIQUID_TYPE_MAGMA       0x04
#define MAP_LIQUID_TYPE_SLIME       0x08

#define MAP_ALL_LIQUIDS   (MAP_LIQUID_TYPE_WATER | MAP_LIQUID_TYPE_OCEAN | MAP_LIQUID_TYPE_MAGMA | MAP_LIQUID_TYPE_SLIME)

#define MAP_LIQUID_TYPE_DARK_WATER  0x10
#define MAP_LIQUID_TYPE_WMO_WATER   0x20

#define MAP_LIQUID_NO_TYPE    0x0001
#define MAP_LIQUID_NO_HEIGHT  0x0002

#define MAP_HEIGHT_NO_HEIGHT  0x0001
#define MAP_HEIGHT_AS_INT16   0x0002
#define MAP_HEIGHT_AS_INT8    0x0004

#define MAP_AREA_NO_AREA      0x0001

#define MAX_QUEST_LOG_SIZE 25

#define QUEST_OBJECTIVES_COUNT 4
#define QUEST_ITEM_OBJECTIVES_COUNT 6
#define QUEST_SOURCE_ITEM_IDS_COUNT 4
#define QUEST_REWARD_CHOICES_COUNT 6
#define QUEST_REWARDS_COUNT 4
#define QUEST_DEPLINK_COUNT 10
#define QUEST_REPUTATIONS_COUNT 5
#define QUEST_EMOTE_COUNT 4
#define MAX_ACTION_BUTTONS 144                             //checked in 3.2.0

#define UNIT_ACTION_BUTTON_ACTION(X) (uint32(X) & 0x00FFFFFF)
#define UNIT_ACTION_BUTTON_TYPE(X)   ((uint32(X) & 0xFF000000) >> 24)
#define MAX_UNIT_ACTION_BUTTON_ACTION_VALUE (0x00FFFFFF+1)
#define MAKE_UNIT_ACTION_BUTTON(A,T) (uint32(A) | (uint32(T) << 24))


#define MAX_UNIT_ACTION_BAR_INDEX (ACTION_BAR_INDEX_END-ACTION_BAR_INDEX_START)


String              GetEUnitFieldsName(int input);
String              GetEItemFieldsName(int input);
String              GetEObjectFieldsName(int input);
String              GetEContainerFieldsName(int input);
String              GetECorpseFieldsName(int input);
String              GetEDynamicObjectFieldsName(int input);
String              GetEGameObjectFieldsName(int input);

String              GetUpdateFlagComment(int input_flag);
String              GetMoveFlagComment(int input_flag);
String              GetMoveFlag2Comment(int input_flag);
String              GetFieldName(int fieldtype, int input);
String              GetSpellMissInfoName(int input);
String              GetOBJECT_UPDATE_TYPEName(int input);
String              GetGroupUpdateFlagsName(int input);
String              GetGroupMemberOnlineStatus(int input);
String              GetAURA_FLAGS(int input_flag);
String              GetSpellEffectsName(int effect);
String              GetTypeIDName(int input);
String              GetTypeNameByGUID(uint64 guid);
String              GetItemClassName(int input);
String              GetChatMsgName(int input);
String              GetLanguageName(int input);
String              GetSplineTypeName(int input);
String              GetSplineFlags(int input_flag);
String              GetEnviromentalDamageName(int input);
String              GetMapTypesName(int input);
String              GetCharacterFlags(int input_flag);
String              GetAtLoginFlags(int input_flag);
String 				GetSpellCastFlags(int input_flag);
String 				GetSpellCastTargetFlags(int input_flag);
String 				GetQuestFlags(int input_flag);
String 				GetHitInfoFlag(int input_flag);
String 				GetVictimState(int input);
String 				GetAccountDataTypeMask(int input_flag);
String 				GetAccountDataType(int input);
String 				GetTypeMaskFlag(int input_flag);
String 				GetTrainerSpellStateType(int input);
String 				GetSpellHitTypeFlag(int input_flag);
String 				GetAuthResultName(int input);
String 				GetRealmFlagsName(int input_flag);
String 				GetResponseCodesName(int input);
String 				GetPowersName(int input);
String 				GetFactionFlagsName(int input_flag);
String 				GetSpellModOpName(int input);
String 				GetSpellCastFlagsName(int input_flag);
String 				GetDifficultyName(int input);
String 				GetActionButtonTypeName(int input_flag);
String 				GetServerMSTimeMutiParamTypeName(int input);
String              GetWOWClassesName(int input);
String              GetSpellFamilyNamesName(int input);
String              GetCreatureFamilyName(int input);
String              GetActiveStatesName(int input);



//////////////////////////////////////////////////////////////////////////////////
//WAR3¶¨Òå
#define MAPSPEED_SLOW     0x00000000
#define MAPSPEED_NORMAL     0x00000001
#define MAPSPEED_FAST     0x00000002

#define MAPVIS_HIDETERRAIN    0x00000100
#define MAPVIS_EXPLORED     0x00000200
#define MAPVIS_ALWAYSVISIBLE  0x00000400
#define MAPVIS_DEFAULT      0x00000800

#define MAPOBS_ONDEFEAT     0x00002000
#define MAPOBS_ALLOWED      0x00003000
#define MAPOBS_REFEREES     0x40000000

#define MAPFLAG_TEAMSTOGETHER 0x00004000
#define MAPFLAG_FIXEDTEAMS    0x00060000
#define MAPFLAG_UNITSHARE   0x01000000
#define MAPFLAG_RANDOMHERO    0x02000000
#define MAPFLAG_RANDOMRACES   0x04000000

#define MAPOBS_NONE       1

#define MAPOPT_HIDEMINIMAP        1 << 0
#define MAPOPT_MODIFYALLYPRIORITIES   1 << 1
#define MAPOPT_MELEE          1 << 2    // the bot cares about this one...
#define MAPOPT_REVEALTERRAIN      1 << 4
#define MAPOPT_FIXEDPLAYERSETTINGS    1 << 5    // and this one...
#define MAPOPT_CUSTOMFORCES       1 << 6    // and this one, the rest don't affect the bot's logic
#define MAPOPT_CUSTOMTECHTREE     1 << 7
#define MAPOPT_CUSTOMABILITIES      1 << 8
#define MAPOPT_CUSTOMUPGRADES     1 << 9
#define MAPOPT_WATERWAVESONCLIFFSHORES  1 << 11
#define MAPOPT_WATERWAVESONSLOPESHORES  1 << 12

#define MAPFILTER_MAKER_USER      1
#define MAPFILTER_MAKER_BLIZZARD    2

#define MAPFILTER_TYPE_MELEE      1
#define MAPFILTER_TYPE_SCENARIO     2

#define MAPFILTER_SIZE_SMALL      1
#define MAPFILTER_SIZE_MEDIUM     2
#define MAPFILTER_SIZE_LARGE      4

#define MAPFILTER_OBS_FULL        1
#define MAPFILTER_OBS_ONDEATH     2
#define MAPFILTER_OBS_NONE        4

#define MAPGAMETYPE_UNKNOWN0      1     // always set except for saved games?
String              GetWar3MapFlags(int input);
//////////////////////////////////////////////////////////////////////////////////

#endif



