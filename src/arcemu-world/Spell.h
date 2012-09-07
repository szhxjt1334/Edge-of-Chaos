/*
 * ArcEmu MMORPG Server
 * Copyright (C) 2005-2007 Ascent Team <http://www.ascentemu.com/>
 * Copyright (C) 2008-2011 <http://www.ArcEmu.org/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __SPELL_H
#define __SPELL_H

#include "SpellTarget.h"
#include "SpellFailure.h"
#include "StdAfx.h"

class WorldSession;
class Unit;
class DynamicObj;
class Player;
class Item;
class Group;
class Aura;


struct SpellClickSpell
{
	uint32 CreatureID;
	uint32 SpellID;
};

/* Spell Ranges:(for 1.10.2)
Range ID|Range|Description
1       0-0     Self Only
2       0-5     Combat Range
3       0-20    Short Range
4       0-30    Medium Range
5       0-40    Long Range
6       0-100   Vision Range
7       0-10    Very Short Range
8       10-20   Short Range
9       10-30   Medium Range
10      10-40   Long Range
11      0-15    Shorter Range
12      0-5     Interact Range
13      0-50000 Anywhere
14      0-60    Extra Long Range
34      0-25    Medium-Short Range
35      0-35    Medium-Long Range
36      0-45    Longer Range
37      0-50    Extended Range
38      10-25   Extra Medium Range
54      5-30    Geoff Monster Shoot
74      8-30    Ranged Weapon
94      8-40    Sting
95      8-25    Charge
96      0-2     Trap
114     8-35    Hunter Range Hunter
134     0-80    Tower 80 Tower
135     0-100   Tower 100 Tower
*/

enum SPELL_INFRONT_STATUS
{
    SPELL_INFRONT_STATUS_REQUIRE_SKIPCHECK	= 0,
    SPELL_INFRONT_STATUS_REQUIRE_INFRONT	= 1,
    SPELL_INFRONT_STATUS_REQUIRE_INBACK		= 2,
};

//bool IsBeneficSpell(SpellEntry *sp);
//AI_SpellTargetType RecommandAISpellTargetType(SpellEntry *sp);

enum DmgClass // SPELL_ENTRY_DmgClass
{
    DmgClass_NONE   = 0,
    DmgClass_MAGIC  = 1,
    DmgClass_MELEE  = 2,
    DmgClass_RANGED = 3
};

// value's for SendSpellLog
enum SPELL_LOG
{
    SPELL_LOG_NONE,
    SPELL_LOG_MISS,
    SPELL_LOG_RESIST,
    SPELL_LOG_DODGE,
    SPELL_LOG_PARRY,
    SPELL_LOG_BLOCK,
    SPELL_LOG_EVADE,
    SPELL_LOG_IMMUNE,
    SPELL_LOG_IMMUNE2,
    SPELL_LOG_DEFLECT,
    SPELL_LOG_ABSORB,
    SPELL_LOG_REFLECT
};
/*
enum SpellCastTargetFlags
{
    TARGET_FLAG_SELF                = 0x0000, // they are checked in following order
    TARGET_FLAG_UNK1                = 0x0001,
    TARGET_FLAG_UNIT                = 0x0002,
    TARGET_FLAG_UNK2                = 0x0004,
    TARGET_FLAG_UNK3                = 0x0008,
    TARGET_FLAG_ITEM                = 0x0010,
    TARGET_FLAG_SOURCE_LOCATION     = 0x0020,
    TARGET_FLAG_DEST_LOCATION       = 0x0040,
    TARGET_FLAG_OBJECT_CASTER       = 0x0080,
    TARGET_FLAG_UNIT_CASTER         = 0x0100,
    TARGET_FLAG_CORPSE              = 0x0200, // PvP Corpse
    TARGET_FLAG_UNIT_CORPSE         = 0x0400, // Gathering professions
    TARGET_FLAG_OBJECT              = 0x0800,
    TARGET_FLAG_TRADE_ITEM          = 0x1000,
    TARGET_FLAG_STRING              = 0x2000,
    TARGET_FLAG_OPEN_LOCK           = 0x4000, // opening object/lock
    TARGET_FLAG_CORPSE2             = 0x8000, // for resurrection spells
    TARGET_FLAG_GLYPH               = 0x20000
};*/

enum SpellCastTargetFlags
{
    TARGET_FLAG_NONE            = 0x00000000,
    TARGET_FLAG_UNUSED_1        = 0x00000001,               // not used
    TARGET_FLAG_UNIT            = 0x00000002,               // pguid
    TARGET_FLAG_UNIT_RAID       = 0x00000004,               // not sent, used to validate target (if raid member)
    TARGET_FLAG_UNIT_PARTY      = 0x00000008,               // not sent, used to validate target (if party member)
    TARGET_FLAG_ITEM            = 0x00000010,               // pguid
    TARGET_FLAG_SOURCE_LOCATION = 0x00000020,               // pguid, 3 float
    TARGET_FLAG_DEST_LOCATION   = 0x00000040,               // pguid, 3 float
    TARGET_FLAG_UNIT_ENEMY      = 0x00000080,               // not sent, used to validate target (if enemy)
    TARGET_FLAG_UNIT_ALLY       = 0x00000100,               // not sent, used to validate target (if ally)
    TARGET_FLAG_CORPSE_ENEMY    = 0x00000200,               // pguid
    TARGET_FLAG_UNIT_DEAD       = 0x00000400,               // not sent, used to validate target (if dead creature)
    TARGET_FLAG_GAMEOBJECT      = 0x00000800,               // pguid, used with TARGET_GAMEOBJECT_TARGET
    TARGET_FLAG_TRADE_ITEM      = 0x00001000,               // pguid
    TARGET_FLAG_STRING          = 0x00002000,               // string
    TARGET_FLAG_GAMEOBJECT_ITEM = 0x00004000,               // not sent, used with TARGET_GAMEOBJECT_ITEM_TARGET
    TARGET_FLAG_CORPSE_ALLY     = 0x00008000,               // pguid
    TARGET_FLAG_UNIT_MINIPET    = 0x00010000,               // pguid, used to validate target (if non combat pet)
    TARGET_FLAG_GLYPH_SLOT      = 0x00020000,               // used in glyph spells
    TARGET_FLAG_DEST_TARGET     = 0x00040000,               // sometimes appears with DEST_TARGET spells (may appear or not for a given spell)
    TARGET_FLAG_UNUSED20        = 0x00080000,               // uint32 counter, loop { vec3 - screen position (?), guid }, not used so far
    TARGET_FLAG_UNIT_PASSENGER  = 0x00100000,               // guessed, used to validate target (if vehicle passenger)

    TARGET_FLAG_UNIT_MASK = TARGET_FLAG_UNIT | TARGET_FLAG_UNIT_RAID | TARGET_FLAG_UNIT_PARTY
        | TARGET_FLAG_UNIT_ENEMY | TARGET_FLAG_UNIT_ALLY | TARGET_FLAG_UNIT_DEAD | TARGET_FLAG_UNIT_MINIPET | TARGET_FLAG_UNIT_PASSENGER,
    TARGET_FLAG_GAMEOBJECT_MASK = TARGET_FLAG_GAMEOBJECT | TARGET_FLAG_GAMEOBJECT_ITEM,
    TARGET_FLAG_CORPSE_MASK = TARGET_FLAG_CORPSE_ALLY | TARGET_FLAG_CORPSE_ENEMY,
    TARGET_FLAG_ITEM_MASK = TARGET_FLAG_TRADE_ITEM | TARGET_FLAG_ITEM | TARGET_FLAG_GAMEOBJECT_ITEM,
};

enum procFlags
{
    PROC_NULL							= 0x0,			//0
    PROC_ON_ANY_HOSTILE_ACTION			= 0x1,			//1
    PROC_ON_GAIN_EXPIERIENCE			= 0x2,			//2
    PROC_ON_MELEE_ATTACK				= 0x4,			//4
    PROC_ON_CRIT_HIT_VICTIM				= 0x8,			//8
    PROC_ON_CAST_SPELL					= 0x10,			//16
    PROC_ON_PHYSICAL_ATTACK_VICTIM		= 0x20,			//32
    PROC_ON_RANGED_ATTACK				= 0x40,			//64
    PROC_ON_RANGED_CRIT_ATTACK			= 0x80,			//128
    PROC_ON_PHYSICAL_ATTACK				= 0x100,		//256
    PROC_ON_MELEE_ATTACK_VICTIM			= 0x200,		//512
    PROC_ON_SPELL_HIT					= 0x400,		//1024
    PROC_ON_RANGED_CRIT_ATTACK_VICTIM	= 0x800,		//2048
    PROC_ON_CRIT_ATTACK					= 0x1000,		//4096
    PROC_ON_RANGED_ATTACK_VICTIM		= 0x2000,		//8192
    PROC_ON_PRE_DISPELL_AURA_VICTIM		= 0x4000,		//16384
    PROC_ON_SPELL_LAND_VICTIM			= 0x8000,		//32768
    PROC_ON_CAST_SPECIFIC_SPELL			= 0x10000,		//65536
    PROC_ON_SPELL_HIT_VICTIM			= 0x20000,		//131072
    PROC_ON_SPELL_CRIT_HIT_VICTIM		= 0x40000,		//262144
    PROC_ON_TARGET_DIE					= 0x80000,		//524288
    PROC_ON_ANY_DAMAGE_VICTIM			= 0x100000,		//1048576
    PROC_ON_TRAP_TRIGGER				= 0x200000,		//2097152 triggers on trap activation)
    PROC_ON_AUTO_SHOT_HIT				= 0x400000,		//4194304
    PROC_ON_ABSORB						= 0x800000,		//8388608
    PROC_ON_RESIST_VICTIM				= 0x1000000,	//16777216
    PROC_ON_DODGE_VICTIM				= 0x2000000,	//33554432
    PROC_ON_DIE							= 0x4000000,	//67108864
    PROC_REMOVEONUSE					= 0x8000000,	//134217728 remove prochcharge only when it is used
    PROC_MISC							= 0x10000000,	//268435456 our custom flag to decide if proc dmg or shield
    PROC_ON_BLOCK_VICTIM				= 0x20000000,	//536870912
    PROC_ON_SPELL_CRIT_HIT				= 0x40000000,	//1073741824
    PROC_TARGET_SELF					= 0x80000000,	//-2147483648 our custom flag to decide if proc target is self or victim
};


enum CastInterruptFlags
{
    CAST_INTERRUPT_NULL                 = 0x0,
    CAST_INTERRUPT_ON_MOVEMENT          = 0x1,
    CAST_INTERRUPT_PUSHBACK             = 0x2, // seems to be whether or not the spell is pushed back on dmg
    CAST_INTERRUPT_ON_INTERRUPT_CAST    = 0x4, // ? probably interrupt only cast
    CAST_INTERRUPT_ON_INTERRUPT_SCHOOL  = 0x8, // seems that on 3.2.0 spell with this interrupts only 1 school, like counterspell
    CAST_INTERRUPT_ON_DAMAGE_TAKEN      = 0x10,
    CAST_INTERRUPT_ON_INTERRUPT_ALL     = 0x20 // guessed

};

enum AuraInterruptFlags
{
    AURA_INTERRUPT_NULL							= 0x0,
    AURA_INTERRUPT_ON_HOSTILE_SPELL_INFLICTED	= 0x1,
    AURA_INTERRUPT_ON_ANY_DAMAGE_TAKEN			= 0x2,
    AURA_INTERRUPT_ON_UNK1						= 0x4,
    AURA_INTERRUPT_ON_MOVEMENT					= 0x8,
    AURA_INTERRUPT_ON_TURNING					= 0x10,
    AURA_INTERRUPT_ON_ENTER_COMBAT				= 0x20,
    AURA_INTERRUPT_ON_DISMOUNT					= 0x40,
    AURA_INTERRUPT_ON_ENTER_WATER				= 0x80,
    AURA_INTERRUPT_ON_LEAVE_WATER				= 0x100, // could be AURA_INTERRUPT_ON_LEAVE_CURRENT_SURFACE
    AURA_INTERRUPT_ON_UNUSED2					= 0x200,
    AURA_INTERRUPT_ON_UNK4						= 0x400,
    AURA_INTERRUPT_ON_UNK5						= 0x800,
    AURA_INTERRUPT_ON_START_ATTACK				= 0x1000,
    AURA_INTERRUPT_ON_UNK6						= 0x2000,
    AURA_INTERRUPT_ON_UNUSED3					= 0x4000,
    AURA_INTERRUPT_ON_CAST_SPELL				= 0x8000,
    AURA_INTERRUPT_ON_UNK7						= 0x10000,
    AURA_INTERRUPT_ON_MOUNT						= 0x20000,
    AURA_INTERRUPT_ON_STAND_UP					= 0x40000,
    AURA_INTERRUPT_ON_LEAVE_AREA				= 0x80000,
    AURA_INTERRUPT_ON_INVINCIBLE				= 0x100000,
    AURA_INTERRUPT_ON_STEALTH					= 0x200000,
    AURA_INTERRUPT_ON_UNK8						= 0x400000,
    AURA_INTERRUPT_ON_PVP_ENTER					= 0x800000,
    AURA_INTERRUPT_ON_DIRECT_DAMAGE				= 0x1000000,
	AURA_INTERRUPT_ON_LANDING                   = 0x2000000,
    AURA_INTERRUPT_ON_AFTER_CAST_SPELL			= 0x80000000,
};

enum ChannelInterruptFlags
{
    CHANNEL_INTERRUPT_NULL  = 0x0,
    CHANNEL_INTERRUPT_ON_1  = 0x1,
    CHANNEL_INTERRUPT_ON_2  = 0x2,
    CHANNEL_INTERRUPT_ON_3  = 0x4,
    CHANNEL_INTERRUPT_ON_4  = 0x8,
    CHANNEL_INTERRUPT_ON_5  = 0x10,
    CHANNEL_INTERRUPT_ON_6  = 0x20,
    CHANNEL_INTERRUPT_ON_7  = 0x40,
    CHANNEL_INTERRUPT_ON_8  = 0x80,
    CHANNEL_INTERRUPT_ON_9  = 0x100,
    CHANNEL_INTERRUPT_ON_10 = 0x200,
    CHANNEL_INTERRUPT_ON_11 = 0x400,
    CHANNEL_INTERRUPT_ON_12 = 0x800,
    CHANNEL_INTERRUPT_ON_13 = 0x1000,
    CHANNEL_INTERRUPT_ON_14 = 0x2000,
    CHANNEL_INTERRUPT_ON_15 = 0x4000,
    CHANNEL_INTERRUPT_ON_16 = 0x8000,
    CHANNEL_INTERRUPT_ON_17 = 0x10000,
    CHANNEL_INTERRUPT_ON_18 = 0x20000
};

enum SpellAttr0
{
    SPELL_ATTR0_UNK0                             = 0x00000001, //  0
    SPELL_ATTR0_REQ_AMMO                         = 0x00000002, //  1 on next ranged
    SPELL_ATTR0_ON_NEXT_SWING                    = 0x00000004, //  2
    SPELL_ATTR0_UNK3                             = 0x00000008, //  3 not set in 3.0.3
    SPELL_ATTR0_ABILITY                          = 0x00000010, //  4 client puts 'ability' instead of 'spell' in game strings for these spells
    SPELL_ATTR0_TRADESPELL                       = 0x00000020, //  5 trade spells (recipes), will be added by client to a sublist of profession spell
    SPELL_ATTR0_PASSIVE                          = 0x00000040, //  6 Passive spell
    SPELL_ATTR0_HIDDEN_CLIENTSIDE                = 0x00000080, //  7 Spells with this attribute are not visible in spellbook or aura bar
    SPELL_ATTR0_HIDE_IN_COMBAT_LOG               = 0x00000100, //  8 This attribite controls whether spell appears in combat logs
    SPELL_ATTR0_TARGET_MAINHAND_ITEM             = 0x00000200, //  9 Client automatically selects item from mainhand slot as a cast target
    SPELL_ATTR0_ON_NEXT_SWING_2                  = 0x00000400, // 10
    SPELL_ATTR0_UNK11                            = 0x00000800, // 11
    SPELL_ATTR0_DAYTIME_ONLY                     = 0x00001000, // 12 only useable at daytime, not set in 2.4.2
    SPELL_ATTR0_NIGHT_ONLY                       = 0x00002000, // 13 only useable at night, not set in 2.4.2
    SPELL_ATTR0_INDOORS_ONLY                     = 0x00004000, // 14 only useable indoors, not set in 2.4.2
    SPELL_ATTR0_OUTDOORS_ONLY                    = 0x00008000, // 15 Only useable outdoors.
    SPELL_ATTR0_NOT_SHAPESHIFT                   = 0x00010000, // 16 Not while shapeshifted
    SPELL_ATTR0_ONLY_STEALTHED                   = 0x00020000, // 17 Must be in stealth
    SPELL_ATTR0_DONT_AFFECT_SHEATH_STATE         = 0x00040000, // 18 client won't hide unit weapons in sheath on cast/channel
    SPELL_ATTR0_LEVEL_DAMAGE_CALCULATION         = 0x00080000, // 19 spelldamage depends on caster level
    SPELL_ATTR0_STOP_ATTACK_TARGET               = 0x00100000, // 20 Stop attack after use this spell (and not begin attack if use)
    SPELL_ATTR0_IMPOSSIBLE_DODGE_PARRY_BLOCK     = 0x00200000, // 21 Cannot be dodged/parried/blocked
    SPELL_ATTR0_CAST_TRACK_TARGET                = 0x00400000, // 22 Client automatically forces player to face target when casting
    SPELL_ATTR0_CASTABLE_WHILE_DEAD              = 0x00800000, // 23 castable while dead?
    SPELL_ATTR0_CASTABLE_WHILE_MOUNTED           = 0x01000000, // 24 castable while mounted
    SPELL_ATTR0_DISABLED_WHILE_ACTIVE            = 0x02000000, // 25 Activate and start cooldown after aura fade or remove summoned creature or go
    SPELL_ATTR0_NEGATIVE_1                       = 0x04000000, // 26 Many negative spells have this attr
    SPELL_ATTR0_CASTABLE_WHILE_SITTING           = 0x08000000, // 27 castable while sitting
    SPELL_ATTR0_CANT_USED_IN_COMBAT              = 0x10000000, // 28 Cannot be used in combat
    SPELL_ATTR0_UNAFFECTED_BY_INVULNERABILITY    = 0x20000000, // 29 unaffected by invulnerability (hmm possible not...)
    SPELL_ATTR0_BREAKABLE_BY_DAMAGE              = 0x40000000, // 30
    SPELL_ATTR0_CANT_CANCEL                      = 0x80000000  // 31 positive aura can't be canceled
};

enum SpellAttr1
{
    SPELL_ATTR1_DISMISS_PET                      = 0x00000001, //  0 for spells without this flag client doesn't allow to summon pet if caster has a pet
    SPELL_ATTR1_DRAIN_ALL_POWER                  = 0x00000002, //  1 use all power (Only paladin Lay of Hands and Bunyanize)
    SPELL_ATTR1_CHANNELED_1                      = 0x00000004, //  2 clientside checked? cancelable?
    SPELL_ATTR1_CANT_BE_REDIRECTED               = 0x00000008, //  3
    SPELL_ATTR1_UNK4                             = 0x00000010, //  4 stealth and whirlwind
    SPELL_ATTR1_NOT_BREAK_STEALTH                = 0x00000020, //  5 Not break stealth
    SPELL_ATTR1_CHANNELED_2                      = 0x00000040, //  6
    SPELL_ATTR1_CANT_BE_REFLECTED                = 0x00000080, //  7
    SPELL_ATTR1_CANT_TARGET_IN_COMBAT            = 0x00000100, //  8 can target only out of combat units
    SPELL_ATTR1_MELEE_COMBAT_START               = 0x00000200, //  9 player starts melee combat after this spell is cast
    SPELL_ATTR1_NO_THREAT                        = 0x00000400, // 10 no generates threat on cast 100% (old NO_INITIAL_AGGRO)
    SPELL_ATTR1_UNK11                            = 0x00000800, // 11 aura
    SPELL_ATTR1_UNK12                            = 0x00001000, // 12 pickpoket
    SPELL_ATTR1_FARSIGHT                         = 0x00002000, // 13 Client removes farsight on aura loss
    SPELL_ATTR1_CHANNEL_TRACK_TARGET             = 0x00004000, // 14 Client automatically forces player to face target when channeling
    SPELL_ATTR1_DISPEL_AURAS_ON_IMMUNITY         = 0x00008000, // 15 remove auras on immunity
    SPELL_ATTR1_UNAFFECTED_BY_SCHOOL_IMMUNE      = 0x00010000, // 16 on immuniy
    SPELL_ATTR1_UNAUTOCASTABLE_BY_PET            = 0x00020000, // 17
    SPELL_ATTR1_UNK18                            = 0x00040000, // 18 stun, polymorph, daze, hex
    SPELL_ATTR1_CANT_TARGET_SELF                 = 0x00080000, // 19
    SPELL_ATTR1_REQ_COMBO_POINTS1                = 0x00100000, // 20 Req combo points on target
    SPELL_ATTR1_UNK21                            = 0x00200000, // 21
    SPELL_ATTR1_REQ_COMBO_POINTS2                = 0x00400000, // 22 Req combo points on target
    SPELL_ATTR1_UNK23                            = 0x00800000, // 23
    SPELL_ATTR1_UNK24                            = 0x01000000, // 24 only fishing spells
    SPELL_ATTR1_UNK25                            = 0x02000000, // 25
    SPELL_ATTR1_UNK26                            = 0x04000000, // 26 works correctly with [target=focus] and [target=mouseover] macros?
    SPELL_ATTR1_UNK27                            = 0x08000000, // 27 melee spell?
    SPELL_ATTR1_DONT_DISPLAY_IN_AURA_BAR         = 0x10000000, // 28 client doesn't display these spells in aura bar
    SPELL_ATTR1_CHANNEL_DISPLAY_SPELL_NAME       = 0x20000000, // 29 spell name is displayed in cast bar instead of 'channeling' text
    SPELL_ATTR1_ENABLE_AT_DODGE                  = 0x40000000, // 30 Overpower
    SPELL_ATTR1_UNK31                            = 0x80000000  // 31
};

enum SpellAttr2
{
    SPELL_ATTR2_CAN_TARGET_DEAD                  = 0x00000001, //  0 can target dead unit or corpse
    SPELL_ATTR2_UNK1                             = 0x00000002, //  1 vanish, shadowform, Ghost Wolf and other
    SPELL_ATTR2_CAN_TARGET_NOT_IN_LOS            = 0x00000004, //  2 26368 4.0.1 dbc change
    SPELL_ATTR2_UNK3                             = 0x00000008, //  3
    SPELL_ATTR2_DISPLAY_IN_STANCE_BAR            = 0x00000010, //  4 client displays icon in stance bar when learned, even if not shapeshift
    SPELL_ATTR2_AUTOREPEAT_FLAG                  = 0x00000020, //  5
    SPELL_ATTR2_CANT_TARGET_TAPPED               = 0x00000040, //  6 target must be tapped by caster
    SPELL_ATTR2_UNK7                             = 0x00000080, //  7
    SPELL_ATTR2_UNK8                             = 0x00000100, //  8 not set in 3.0.3
    SPELL_ATTR2_UNK9                             = 0x00000200, //  9
    SPELL_ATTR2_UNK10                            = 0x00000400, // 10 related to tame
    SPELL_ATTR2_HEALTH_FUNNEL                    = 0x00000800, // 11
    SPELL_ATTR2_UNK12                            = 0x00001000, // 12 Cleave, Heart Strike, Maul, Sunder Armor, Swipe
    SPELL_ATTR2_UNK13                            = 0x00002000, // 13 Items enchanted by spells with this flag preserve the enchant to arenas
    SPELL_ATTR2_UNK14                            = 0x00004000, // 14
    SPELL_ATTR2_UNK15                            = 0x00008000, // 15 not set in 3.0.3
    SPELL_ATTR2_TAME_BEAST                       = 0x00010000, // 16
    SPELL_ATTR2_NOT_RESET_AUTO_ACTIONS           = 0x00020000, // 17 don't reset timers for melee autoattacks (swings) or ranged autoattacks (autoshoots)
    SPELL_ATTR2_UNK18                            = 0x00040000, // 18 Only Revive pet - possible req dead pet
    SPELL_ATTR2_NOT_NEED_SHAPESHIFT              = 0x00080000, // 19 does not necessarly need shapeshift
    SPELL_ATTR2_UNK20                            = 0x00100000, // 20
    SPELL_ATTR2_DAMAGE_REDUCED_SHIELD            = 0x00200000, // 21 for ice blocks, pala immunity buffs, priest absorb shields, but used also for other spells -> not sure!
    SPELL_ATTR2_UNK22                            = 0x00400000, // 22 Ambush, Backstab, Cheap Shot, Death Grip, Garrote, Judgements, Mutilate, Pounce, Ravage, Shiv, Shred
    SPELL_ATTR2_UNK23                            = 0x00800000, // 23 Only mage Arcane Concentration have this flag
    SPELL_ATTR2_UNK24                            = 0x01000000, // 24
    SPELL_ATTR2_UNK25                            = 0x02000000, // 25
    SPELL_ATTR2_UNK26                            = 0x04000000, // 26 unaffected by school immunity
    SPELL_ATTR2_UNK27                            = 0x08000000, // 27
    SPELL_ATTR2_UNK28                            = 0x10000000, // 28
    SPELL_ATTR2_CANT_CRIT                        = 0x20000000, // 29 Spell can't crit
    SPELL_ATTR2_TRIGGERED_CAN_TRIGGER_PROC       = 0x40000000, // 30 spell can trigger even if triggered
    SPELL_ATTR2_FOOD_BUFF                        = 0x80000000  // 31 Food or Drink Buff (like Well Fed)
};

enum SpellAttr3
{
    SPELL_ATTR3_UNK0                             = 0x00000001, //  0
    SPELL_ATTR3_UNK1                             = 0x00000002, //  1
    SPELL_ATTR3_UNK2                             = 0x00000004, //  2
    SPELL_ATTR3_BLOCKABLE_SPELL                  = 0x00000008, //  3 Only dmg class melee in 3.1.3
    SPELL_ATTR3_IGNORE_RESURRECTION_TIMER        = 0x00000010, //  4 you don't have to wait to be resurrected with these spells
    SPELL_ATTR3_UNK5                             = 0x00000020, //  5
    SPELL_ATTR3_UNK6                             = 0x00000040, //  6
    SPELL_ATTR3_STACK_FOR_DIFF_CASTERS           = 0x00000080, //  7 separate stack for every caster
    SPELL_ATTR3_ONLY_TARGET_PLAYERS              = 0x00000100, //  8 can only target players
    SPELL_ATTR3_TRIGGERED_CAN_TRIGGER_PROC_2     = 0x00000200, //  9 triggered from effect?
    SPELL_ATTR3_MAIN_HAND                        = 0x00000400, // 10 Main hand weapon required
    SPELL_ATTR3_BATTLEGROUND                     = 0x00000800, // 11 Can casted only on battleground
    SPELL_ATTR3_ONLY_TARGET_GHOSTS               = 0x00001000, // 12
    SPELL_ATTR3_UNK13                            = 0x00002000, // 13
    SPELL_ATTR3_UNK14                            = 0x00004000, // 14 "Honorless Target" only this spells have this flag
    SPELL_ATTR3_UNK15                            = 0x00008000, // 15 Auto Shoot, Shoot, Throw,  - this is autoshot flag
    SPELL_ATTR3_CANT_TRIGGER_PROC                = 0x00010000, // 16 confirmed with many patchnotes
    SPELL_ATTR3_NO_INITIAL_AGGRO                 = 0x00020000, // 17 Soothe Animal, 39758, Mind Soothe
    SPELL_ATTR3_IGNORE_HIT_RESULT                = 0x00040000, // 18 Spell should always hit its target
    SPELL_ATTR3_DISABLE_PROC                     = 0x00080000, // 19 during aura proc no spells can trigger (20178, 20375)
    SPELL_ATTR3_DEATH_PERSISTENT                 = 0x00100000, // 20 Death persistent spells
    SPELL_ATTR3_UNK21                            = 0x00200000, // 21 unused
    SPELL_ATTR3_REQ_WAND                         = 0x00400000, // 22 Req wand
    SPELL_ATTR3_UNK23                            = 0x00800000, // 23
    SPELL_ATTR3_REQ_OFFHAND                      = 0x01000000, // 24 Req offhand weapon
    SPELL_ATTR3_UNK25                            = 0x02000000, // 25 no cause spell pushback ?
    SPELL_ATTR3_CAN_PROC_WITH_TRIGGERED          = 0x04000000, // 26 auras with this attribute can proc from triggered spell casts with SPELL_ATTR3_TRIGGERED_CAN_TRIGGER_PROC_2 (67736 + 52999)
    SPELL_ATTR3_DRAIN_SOUL                       = 0x08000000, // 27 only drain soul has this flag
    SPELL_ATTR3_UNK28                            = 0x10000000, // 28
    SPELL_ATTR3_NO_DONE_BONUS                    = 0x20000000, // 29 Ignore caster spellpower and done damage mods?  client doesn't apply spellmods for those spells
    SPELL_ATTR3_DONT_DISPLAY_RANGE               = 0x40000000, // 30 client doesn't display range in tooltip for those spells
    SPELL_ATTR3_UNK31                            = 0x80000000  // 31
};

enum SpellAttr4
{
    SPELL_ATTR4_UNK0                             = 0x00000001, //  0
    SPELL_ATTR4_PROC_ONLY_ON_DUMMY               = 0x00000002, //  1 proc only on SPELL_EFFECT_DUMMY?
    SPELL_ATTR4_UNK2                             = 0x00000004, //  2
    SPELL_ATTR4_UNK3                             = 0x00000008, //  3
    SPELL_ATTR4_UNK4                             = 0x00000010, //  4 This will no longer cause guards to attack on use??
    SPELL_ATTR4_UNK5                             = 0x00000020, //  5
    SPELL_ATTR4_NOT_STEALABLE                    = 0x00000040, //  6 although such auras might be dispellable, they cannot be stolen
    SPELL_ATTR4_TRIGGERED                        = 0x00000080, //  7 spells forced to be triggered
    SPELL_ATTR4_UNK8                             = 0x00000100, //  8 ignores taken percent damage mods?
    SPELL_ATTR4_TRIGGER_ACTIVATE                 = 0x00000200, //  9 initially disabled / trigger activate from event (Execute, Riposte, Deep Freeze end other)
    SPELL_ATTR4_SPELL_VS_EXTEND_COST             = 0x00000400, // 10 Rogue Shiv have this flag
    SPELL_ATTR4_UNK11                            = 0x00000800, // 11
    SPELL_ATTR4_UNK12                            = 0x00001000, // 12
    SPELL_ATTR4_UNK13                            = 0x00002000, // 13
    SPELL_ATTR4_DAMAGE_DOESNT_BREAK_AURAS        = 0x00004000, // 14 doesn't break auras by damage from these spells
    SPELL_ATTR4_UNK15                            = 0x00008000, // 15
    SPELL_ATTR4_NOT_USABLE_IN_ARENA              = 0x00010000, // 16
    SPELL_ATTR4_USABLE_IN_ARENA                  = 0x00020000, // 17
    SPELL_ATTR4_AREA_TARGET_CHAIN                = 0x00040000, // 18 (NYI)hits area targets one after another instead of all at once
    SPELL_ATTR4_UNK19                            = 0x00080000, // 19 proc dalayed, after damage or don't proc on absorb?
    SPELL_ATTR4_NOT_CHECK_SELFCAST_POWER         = 0x00100000, // 20 supersedes message "More powerful spell applied" for self casts.
    SPELL_ATTR4_UNK21                            = 0x00200000, // 21 Pally aura, dk presence, dudu form, warrior stance, shadowform, hunter track
    SPELL_ATTR4_UNK22                            = 0x00400000, // 22
    SPELL_ATTR4_UNK23                            = 0x00800000, // 23
    SPELL_ATTR4_UNK24                            = 0x01000000, // 24 some shoot spell
    SPELL_ATTR4_UNK25                            = 0x02000000, // 25 pet scaling auras
    SPELL_ATTR4_CAST_ONLY_IN_OUTLAND             = 0x04000000, // 26 Can only be used in Outland.
    SPELL_ATTR4_UNK27                            = 0x08000000, // 27
    SPELL_ATTR4_UNK28                            = 0x10000000, // 28 Aimed Shot
    SPELL_ATTR4_UNK29                            = 0x20000000, // 29
    SPELL_ATTR4_UNK30                            = 0x40000000, // 30
    SPELL_ATTR4_UNK31                            = 0x80000000  // 31
};

enum SpellAttr5
{
    SPELL_ATTR5_UNK0                             = 0x00000001, //  0
    SPELL_ATTR5_NO_REAGENT_WHILE_PREP            = 0x00000002, //  1 not need reagents if UNIT_FLAG_PREPARATION
    SPELL_ATTR5_UNK2                             = 0x00000004, //  2
    SPELL_ATTR5_USABLE_WHILE_STUNNED             = 0x00000008, //  3 usable while stunned
    SPELL_ATTR5_UNK4                             = 0x00000010, //  4
    SPELL_ATTR5_SINGLE_TARGET_SPELL              = 0x00000020, //  5 Only one target can be apply at a time
    SPELL_ATTR5_UNK6                             = 0x00000040, //  6
    SPELL_ATTR5_UNK7                             = 0x00000080, //  7
    SPELL_ATTR5_UNK8                             = 0x00000100, //  8
    SPELL_ATTR5_START_PERIODIC_AT_APPLY          = 0x00000200, //  9 begin periodic tick at aura apply
    SPELL_ATTR5_HIDE_DURATION                    = 0x00000400, // 10 do not send duration to client
    SPELL_ATTR5_ALLOW_TARGET_OF_TARGET_AS_TARGET = 0x00000800, // 11 (NYI) uses target's target as target if original target not valid (intervene for example)
    SPELL_ATTR5_UNK12                            = 0x00001000, // 12 Cleave related?
    SPELL_ATTR5_HASTE_AFFECT_DURATION            = 0x00002000, // 13 haste effects decrease duration of this
    SPELL_ATTR5_UNK14                            = 0x00004000, // 14
    SPELL_ATTR5_UNK15                            = 0x00008000, // 15
    SPELL_ATTR5_SPECIAL_ITEM_CLASS_CHECK         = 0x00010000, // 16 this allows spells with EquippedItemClass to affect spells from other items if the required item is equipped
    SPELL_ATTR5_USABLE_WHILE_FEARED              = 0x00020000, // 17 usable while feared
    SPELL_ATTR5_USABLE_WHILE_CONFUSED            = 0x00040000, // 18 usable while confused
    SPELL_ATTR5_UNK19                            = 0x00080000, // 19
    SPELL_ATTR5_UNK20                            = 0x00100000, // 20
    SPELL_ATTR5_UNK21                            = 0x00200000, // 21
    SPELL_ATTR5_UNK22                            = 0x00400000, // 22
    SPELL_ATTR5_UNK23                            = 0x00800000, // 23
    SPELL_ATTR5_UNK24                            = 0x01000000, // 24
    SPELL_ATTR5_UNK25                            = 0x02000000, // 25
    SPELL_ATTR5_UNK26                            = 0x04000000, // 26 aoe related - Boulder, Cannon, Corpse Explosion, Fire Nova, Flames, Frost Bomb, Living Bomb, Seed of Corruption, Starfall, Thunder Clap, Volley
    SPELL_ATTR5_UNK27                            = 0x08000000, // 27
    SPELL_ATTR5_UNK28                            = 0x10000000, // 28
    SPELL_ATTR5_UNK29                            = 0x20000000, // 29
    SPELL_ATTR5_UNK30                            = 0x40000000, // 30
    SPELL_ATTR5_UNK31                            = 0x80000000  // 31 Forces all nearby enemies to focus attacks caster
};

enum SpellAttr6
{
    SPELL_ATTR6_DONT_DISPLAY_COOLDOWN            = 0x00000001, //  0 client doesn't display cooldown in tooltip for these spells
    SPELL_ATTR6_ONLY_IN_ARENA                    = 0x00000002, //  1 only usable in arena
    SPELL_ATTR6_IGNORE_CASTER_AURAS              = 0x00000004, //  2
    SPELL_ATTR6_UNK3                             = 0x00000008, //  3
    SPELL_ATTR6_UNK4                             = 0x00000010, //  4
    SPELL_ATTR6_UNK5                             = 0x00000020, //  5
    SPELL_ATTR6_UNK6                             = 0x00000040, //  6
    SPELL_ATTR6_UNK7                             = 0x00000080, //  7
    SPELL_ATTR6_CANT_TARGET_CROWD_CONTROLLED     = 0x00000100, //  8
    SPELL_ATTR6_UNK9                             = 0x00000200, //  9
    SPELL_ATTR6_CAN_TARGET_POSSESSED_FRIENDS     = 0x00000400, // 10 NYI!
    SPELL_ATTR6_NOT_IN_RAID_INSTANCE             = 0x00000800, // 11 not usable in raid instance
    SPELL_ATTR6_CASTABLE_WHILE_ON_VEHICLE        = 0x00001000, // 12 castable while caster is on vehicle
    SPELL_ATTR6_CAN_TARGET_INVISIBLE             = 0x00002000, // 13 ignore visibility requirement for spell target (phases, invisibility, etc.)
    SPELL_ATTR6_UNK14                            = 0x00004000, // 14
    SPELL_ATTR6_UNK15                            = 0x00008000, // 15 only 54368, 67892
    SPELL_ATTR6_UNK16                            = 0x00010000, // 16
    SPELL_ATTR6_UNK17                            = 0x00020000, // 17 Mount spell
    SPELL_ATTR6_CAST_BY_CHARMER                  = 0x00040000, // 18 client won't allow to cast these spells when unit is not possessed && charmer of caster will be original caster
    SPELL_ATTR6_UNK19                            = 0x00080000, // 19 only 47488, 50782
    SPELL_ATTR6_UNK20                            = 0x00100000, // 20 only 58371, 62218
    SPELL_ATTR6_CLIENT_UI_TARGET_EFFECTS         = 0x00200000, // 21 it's only client-side attribute
    SPELL_ATTR6_UNK22                            = 0x00400000, // 22 only 72054
    SPELL_ATTR6_UNK23                            = 0x00800000, // 23
    SPELL_ATTR6_CAN_TARGET_UNTARGETABLE          = 0x01000000, // 24
    SPELL_ATTR6_UNK25                            = 0x02000000, // 25 Exorcism, Flash of Light
    SPELL_ATTR6_UNK26                            = 0x04000000, // 26 related to player castable positive buff
    SPELL_ATTR6_UNK27                            = 0x08000000, // 27
    SPELL_ATTR6_UNK28                            = 0x10000000, // 28 Death Grip
    SPELL_ATTR6_NO_DONE_PCT_DAMAGE_MODS          = 0x20000000, // 29 ignores done percent damage mods?
    SPELL_ATTR6_UNK30                            = 0x40000000, // 30
    SPELL_ATTR6_UNK31                            = 0x80000000  // 31 some special cooldown calc? only 2894
};

enum SpellAttr7
{
    SPELL_ATTR7_UNK0                             = 0x00000001, //  0 Shaman's new spells (Call of the ...), Feign Death.
    SPELL_ATTR7_UNK1                             = 0x00000002, //  1 Not set in 3.2.2a.
    SPELL_ATTR7_REACTIVATE_AT_RESURRECT          = 0x00000004, //  2 Paladin's auras and 65607 only.
    SPELL_ATTR7_IS_CHEAT_SPELL                   = 0x00000008, //  3 Cannot cast if caster doesn't have UnitFlag2 & UNIT_FLAG2_ALLOW_CHEAT_SPELLS
    SPELL_ATTR7_UNK4                             = 0x00000010, //  4 Only 47883 (Soulstone Resurrection) and test spell.
    SPELL_ATTR7_SUMMON_PLAYER_TOTEM              = 0x00000020, //  5 Only Shaman player totems.
    SPELL_ATTR7_UNK6                             = 0x00000040, //  6 Dark Surge, Surge of Light, Burning Breath triggers (boss spells).
    SPELL_ATTR7_UNK7                             = 0x00000080, //  7 66218 (Launch) spell.
    SPELL_ATTR7_HORDE_ONLY                       = 0x00000100, //  8 Teleports, mounts and other spells.
    SPELL_ATTR7_ALLIANCE_ONLY                    = 0x00000200, //  9 Teleports, mounts and other spells.
    SPELL_ATTR7_DISPEL_CHARGES                   = 0x00000400, // 10 Dispel and Spellsteal individual charges instead of whole aura.
    SPELL_ATTR7_INTERRUPT_ONLY_NONPLAYER         = 0x00000800, // 11 Only non-player casts interrupt, though Feral Charge - Bear has it.
    SPELL_ATTR7_UNK12                            = 0x00001000, // 12 Not set in 3.2.2a.
    SPELL_ATTR7_UNK13                            = 0x00002000, // 13 Not set in 3.2.2a.
    SPELL_ATTR7_UNK14                            = 0x00004000, // 14 Only 52150 (Raise Dead - Pet) spell.
    SPELL_ATTR7_UNK15                            = 0x00008000, // 15 Exorcism. Usable on players? 100% crit chance on undead and demons?
    SPELL_ATTR7_UNK16                            = 0x00010000, // 16 Druid spells (29166, 54833, 64372, 68285).
    SPELL_ATTR7_UNK17                            = 0x00020000, // 17 Only 27965 (Suicide) spell.
    SPELL_ATTR7_HAS_CHARGE_EFFECT                = 0x00040000, // 18 Only spells that have Charge among effects.
    SPELL_ATTR7_ZONE_TELEPORT                    = 0x00080000, // 19 Teleports to specific zones.
    SPELL_ATTR7_UNK20                            = 0x00100000, // 20 Blink, Divine Shield, Ice Block
    SPELL_ATTR7_UNK21                            = 0x00200000, // 21 Not set
    SPELL_ATTR7_UNK22                            = 0x00400000, // 22
    SPELL_ATTR7_UNK23                            = 0x00800000, // 23 Motivate, Mutilate, Shattering Throw
    SPELL_ATTR7_UNK24                            = 0x01000000, // 24 Motivate, Mutilate, Perform Speech, Shattering Throw
    SPELL_ATTR7_UNK25                            = 0x02000000, // 25
    SPELL_ATTR7_UNK26                            = 0x04000000, // 26
    SPELL_ATTR7_UNK27                            = 0x08000000, // 27 Not set
    SPELL_ATTR7_UNK28                            = 0x10000000, // 28 related to player positive buff
    SPELL_ATTR7_UNK29                            = 0x20000000, // 29 only 69028, 71237
    SPELL_ATTR7_UNK30                            = 0x40000000, // 30 Burning Determination, Divine Sacrifice, Earth Shield, Prayer of Mending
    SPELL_ATTR7_UNK31                            = 0x80000000  // 31 only 70769
};

enum SpellCustomFlags
{
    CUSTOM_FLAG_SPELL_REQUIRES_COMBAT		= 0x1
};


/************************************************************************/
/* General Spell Go Flags, for documentation reasons                    */
/************************************************************************/
enum SpellCastFlags
{
    CAST_FLAG_NONE               = 0x00000000,
    CAST_FLAG_PENDING            = 0x00000001,              // aoe combat log?
    CAST_FLAG_UNKNOWN_2          = 0x00000002,
    CAST_FLAG_UNKNOWN_3          = 0x00000004,
    CAST_FLAG_UNKNOWN_4          = 0x00000008,              // ignore AOE visual
    CAST_FLAG_UNKNOWN_5          = 0x00000010,
    CAST_FLAG_AMMO               = 0x00000020,              // Projectiles visual
    CAST_FLAG_UNKNOWN_7          = 0x00000040,
    CAST_FLAG_UNKNOWN_8          = 0x00000080,
    CAST_FLAG_UNKNOWN_9          = 0x00000100,
    CAST_FLAG_UNKNOWN_10         = 0x00000200,
    CAST_FLAG_UNKNOWN_11         = 0x00000400,
    CAST_FLAG_POWER_LEFT_SELF    = 0x00000800,
    CAST_FLAG_UNKNOWN_13         = 0x00001000,
    CAST_FLAG_UNKNOWN_14         = 0x00002000,
    CAST_FLAG_UNKNOWN_15         = 0x00004000,
    CAST_FLAG_UNKNOWN_16         = 0x00008000,
    CAST_FLAG_UNKNOWN_17         = 0x00010000,
    CAST_FLAG_ADJUST_MISSILE     = 0x00020000,
    CAST_FLAG_UNKNOWN_19         = 0x00040000,
    CAST_FLAG_VISUAL_CHAIN       = 0x00080000,
    CAST_FLAG_UNKNOWN_21         = 0x00100000,
    CAST_FLAG_RUNE_LIST          = 0x00200000,
    CAST_FLAG_UNKNOWN_23         = 0x00400000,
    CAST_FLAG_UNKNOWN_24         = 0x00800000,
    CAST_FLAG_UNKNOWN_25         = 0x01000000,
    CAST_FLAG_UNKNOWN_26         = 0x02000000,
    CAST_FLAG_IMMUNITY           = 0x04000000,
    CAST_FLAG_UNKNOWN_28         = 0x08000000,
    CAST_FLAG_UNKNOWN_29         = 0x10000000,
    CAST_FLAG_UNKNOWN_30         = 0x20000000,
    CAST_FLAG_UNKNOWN_31         = 0x40000000,
    CAST_FLAG_UNKNOWN_32         = 0x80000000,
};

/*enum School //moved to Unit.hack for headers dependencies.
{
	SCHOOL_NORMAL = 0,
	SCHOOL_HOLY   = 1,
	SCHOOL_FIRE   = 2,
	SCHOOL_NATURE = 3,
	SCHOOL_FROST  = 4,
	SCHOOL_SHADOW = 5,
	SCHOOL_ARCANE = 6,
	SCHOOL_COUNT
};*/

// converting schools for 2.4.0 client
static const uint32 g_spellSchoolConversionTable[SCHOOL_COUNT] =
{
	1,				// SCHOOL_NORMAL
	2,				// SCHOOL_HOLY
	4,				// SCHOOL_FIRE
	8,				// SCHOOL_NATURE
	16,				// SCHOOL_FROST
	32,				// SCHOOL_SHADOW
	64,				// SCHOOL_ARCANE
};

enum ReplenishType
{
    REPLENISH_UNDEFINED = 0,
    REPLENISH_HEALTH    = 20,
    REPLENISH_MANA      = 21,
    REPLENISH_RAGE      = 22 //don't know if rage is 22 or what, but will do for now
};

enum SpellTargetType
{
    TARGET_TYPE_NULL       = 0x0,
    TARGET_TYPE_BEAST      = 0x1,
    TARGET_TYPE_DRAGONKIN  = 0x2,
    TARGET_TYPE_DEMON      = 0x4,
    TARGET_TYPE_ELEMENTAL  = 0x8,
    TARGET_TYPE_GIANT      = 0x10,
    TARGET_TYPE_UNDEAD     = 0x20,
    TARGET_TYPE_HUMANOID   = 0x40,
    TARGET_TYPE_CRITTER    = 0x80,
    TARGET_TYPE_MECHANICAL = 0x100,
};

enum PreventionType
{
    PREVENTION_TYPE_NONE      = 0,
    PREVENTION_TYPE_SILENCE   = 1,
    PREVENTION_TYPE_PACIFY    = 2
};

/****************SpellExtraFlags*****************/
/* SpellExtraFlags defines                      */
/*                                              */
/* Used for infront check and other checks      */
/* when they are not in spell.dbc               */
/*                                              */
/************************************************/
#define SPELL_EXTRA_INFRONT 1
#define SPELL_EXTRA_BEHIND  2
#define SPELL_EXTRA_UNDEF0  4 // not used yet
#define SPELL_EXTRA_UNDEF1  8 // not used yet


/***************Ranged spellid*******************/
/* Note: These spell id's are checked for 2.0.x */
/************************************************/
#define SPELL_RANGED_GENERAL    3018
#define SPELL_RANGED_THROW      2764
#define SPELL_RANGED_WAND       5019

#pragma pack(push,1)
struct TeleportCoords
{
	uint32 id;
	uint32 mapId;
	float x;
	float y;
	float z;
};
#pragma pack(pop)

struct TotemSpells
{
	uint32 spellId;
	uint32 spellToCast[3];
};

enum LOCKTYPES
{
    LOCKTYPE_PICKLOCK               = 1,
    LOCKTYPE_HERBALISM              = 2,
    LOCKTYPE_MINING                 = 3,
    LOCKTYPE_DISARM_TRAP            = 4,
    LOCKTYPE_OPEN                   = 5,
    LOCKTYPE_TREASURE               = 6,
    LOCKTYPE_CALCIFIED_ELVEN_GEMS   = 7,
    LOCKTYPE_CLOSE                  = 8,
    LOCKTYPE_ARM_TRAP               = 9,
    LOCKTYPE_QUICK_OPEN             = 10,
    LOCKTYPE_QUICK_CLOSE            = 11,
    LOCKTYPE_OPEN_TINKERING         = 12,
    LOCKTYPE_OPEN_KNEELING          = 13,
    LOCKTYPE_OPEN_ATTACKING         = 14,
    LOCKTYPE_GAHZRIDIAN             = 15,
    LOCKTYPE_BLASTING               = 16,
    LOCKTYPE_SLOW_OPEN              = 17,
    LOCKTYPE_SLOW_CLOSE             = 18
};

enum TIMER_TYPE
{
    TIMER_EXHAUSTION,
    TIMER_BREATH,
    TIMER_FEIGNDEATH,
    TIMER_UNKNOWN
};

enum SpellEffects
{
    SPELL_EFFECT_NULL = 0,
    SPELL_EFFECT_INSTANT_KILL,              //    1
    SPELL_EFFECT_SCHOOL_DAMAGE,             //    2
    SPELL_EFFECT_DUMMY,                     //    3
    SPELL_EFFECT_PORTAL_TELEPORT,           //    4
    SPELL_EFFECT_TELEPORT_UNITS,            //    5
    SPELL_EFFECT_APPLY_AURA,                //    6
    SPELL_EFFECT_ENVIRONMENTAL_DAMAGE,      //    7
    SPELL_EFFECT_POWER_DRAIN,               //    8
    SPELL_EFFECT_HEALTH_LEECH,              //    9
    SPELL_EFFECT_HEAL,                      //    10
    SPELL_EFFECT_BIND,                      //    11
    SPELL_EFFECT_PORTAL,                    //    12
    SPELL_EFFECT_RITUAL_BASE,               //    13
    SPELL_EFFECT_RITUAL_SPECIALIZE,         //    14
    SPELL_EFFECT_RITUAL_ACTIVATE_PORTAL,    //    15
    SPELL_EFFECT_QUEST_COMPLETE,            //    16
    SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL,    //    17
    SPELL_EFFECT_RESURRECT,                 //    18
    SPELL_EFFECT_ADD_EXTRA_ATTACKS,         //    19
    SPELL_EFFECT_DODGE,                     //    20
    SPELL_EFFECT_EVADE,                     //    21
    SPELL_EFFECT_PARRY,                     //    22
    SPELL_EFFECT_BLOCK,                     //    23
    SPELL_EFFECT_CREATE_ITEM,               //    24
    SPELL_EFFECT_WEAPON,                    //    25
    SPELL_EFFECT_DEFENSE,                   //    26
    SPELL_EFFECT_PERSISTENT_AREA_AURA,      //    27
    SPELL_EFFECT_SUMMON,                    //    28
    SPELL_EFFECT_LEAP,                      //    29
    SPELL_EFFECT_ENERGIZE,                  //    30
    SPELL_EFFECT_WEAPON_PERCENT_DAMAGE,     //    31
    SPELL_EFFECT_TRIGGER_MISSILE,           //    32
    SPELL_EFFECT_OPEN_LOCK,                 //    33
    SPELL_EFFECT_TRANSFORM_ITEM,            //    34
    SPELL_EFFECT_APPLY_GROUP_AREA_AURA,     //    35
    SPELL_EFFECT_LEARN_SPELL,               //    36
    SPELL_EFFECT_SPELL_DEFENSE,             //    37
    SPELL_EFFECT_DISPEL,                    //    38
    SPELL_EFFECT_LANGUAGE,                  //    39
    SPELL_EFFECT_DUAL_WIELD,                //    40
    SPELL_EFFECT_LEAP_41,                   //    41
    SPELL_EFFECT_SUMMON_GUARDIAN,           //    42
    SPELL_EFFECT_TELEPORT_UNITS_FACE_CASTER,//    43
    SPELL_EFFECT_SKILL_STEP,                //    44
    SPELL_EFFECT_UNDEFINED_45,              //    45
    SPELL_EFFECT_SPAWN,                     //    46
    SPELL_EFFECT_TRADE_SKILL,               //    47
    SPELL_EFFECT_STEALTH,                   //    48
    SPELL_EFFECT_DETECT,                    //    49
    SPELL_EFFECT_SUMMON_OBJECT,             //    50
    SPELL_EFFECT_FORCE_CRITICAL_HIT,        //    51
    SPELL_EFFECT_GUARANTEE_HIT,             //    52
    SPELL_EFFECT_ENCHANT_ITEM,              //    53
    SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY,    //    54
    SPELL_EFFECT_TAMECREATURE,              //    55
    SPELL_EFFECT_SUMMON_PET,                //    56
    SPELL_EFFECT_LEARN_PET_SPELL,           //    57
    SPELL_EFFECT_WEAPON_DAMAGE,             //    58
    SPELL_EFFECT_OPEN_LOCK_ITEM,            //    59
    SPELL_EFFECT_PROFICIENCY,               //    60
    SPELL_EFFECT_SEND_EVENT,                //    61
    SPELL_EFFECT_POWER_BURN,                //    62
    SPELL_EFFECT_THREAT,                    //    63
    SPELL_EFFECT_TRIGGER_SPELL,             //    64
    SPELL_EFFECT_APPLY_RAID_AREA_AURA,      //    65
    SPELL_EFFECT_POWER_FUNNEL,              //    66
    SPELL_EFFECT_HEAL_MAX_HEALTH,           //    67
    SPELL_EFFECT_INTERRUPT_CAST,            //    68
    SPELL_EFFECT_DISTRACT,                  //    69
    SPELL_EFFECT_PULL,                      //    70
    SPELL_EFFECT_PICKPOCKET,                //    71
    SPELL_EFFECT_ADD_FARSIGHT,              //    72
    SPELL_EFFECT_UNTRAIN_TALENTS,           //    73
    SPELL_EFFECT_USE_GLYPH,	                //    74
    SPELL_EFFECT_HEAL_MECHANICAL,           //    75
    SPELL_EFFECT_SUMMON_OBJECT_WILD,        //    76
    SPELL_EFFECT_SCRIPT_EFFECT,             //    77
    SPELL_EFFECT_ATTACK,                    //    78
    SPELL_EFFECT_SANCTUARY,                 //    79
    SPELL_EFFECT_ADD_COMBO_POINTS,          //    80
    SPELL_EFFECT_CREATE_HOUSE,              //    81
    SPELL_EFFECT_BIND_SIGHT,                //    82
    SPELL_EFFECT_DUEL,                      //    83
    SPELL_EFFECT_STUCK,                     //    84
    SPELL_EFFECT_SUMMON_PLAYER,             //    85
    SPELL_EFFECT_ACTIVATE_OBJECT,           //    86
    SPELL_EFFECT_BUILDING_DAMAGE,           //    87
    SPELL_EFFECT_BUILDING_REPAIR,           //    88
    SPELL_EFFECT_BUILDING_SWITCH_STATE,     //    89
    SPELL_EFFECT_KILL_CREDIT_90,            //    90
    SPELL_EFFECT_THREAT_ALL,                //    91
    SPELL_EFFECT_ENCHANT_HELD_ITEM,         //    92
    SPELL_EFFECT_SUMMON_PHANTASM,           //    93
    SPELL_EFFECT_SELF_RESURRECT,            //    94
    SPELL_EFFECT_SKINNING,                  //    95
    SPELL_EFFECT_CHARGE,                    //    96
    SPELL_EFFECT_SUMMON_MULTIPLE_TOTEMS,    //    97
    SPELL_EFFECT_KNOCK_BACK,                //    98
    SPELL_EFFECT_DISENCHANT,                //    99
    SPELL_EFFECT_INEBRIATE,                 //    100
    SPELL_EFFECT_FEED_PET,                  //    101
    SPELL_EFFECT_DISMISS_PET,               //    102
    SPELL_EFFECT_REPUTATION,                //    103
    SPELL_EFFECT_SUMMON_OBJECT_SLOT1,       //    104
    SPELL_EFFECT_SUMMON_OBJECT_SLOT2,       //    105
    SPELL_EFFECT_SUMMON_OBJECT_SLOT3,       //    106
    SPELL_EFFECT_SUMMON_OBJECT_SLOT4,       //    107
    SPELL_EFFECT_DISPEL_MECHANIC,           //    108
    SPELL_EFFECT_SUMMON_DEAD_PET,           //    109
    SPELL_EFFECT_DESTROY_ALL_TOTEMS,        //    110
    SPELL_EFFECT_DURABILITY_DAMAGE,         //    111
    SPELL_EFFECT_NONE_112,                  //    112
    SPELL_EFFECT_RESURRECT_FLAT,            //    113
    SPELL_EFFECT_ATTACK_ME,                 //    114
    SPELL_EFFECT_DURABILITY_DAMAGE_PCT,     //    115
    SPELL_EFFECT_SKIN_PLAYER_CORPSE,        //    116
    SPELL_EFFECT_SPIRIT_HEAL,               //    117
    SPELL_EFFECT_SKILL,                     //    118
    SPELL_EFFECT_APPLY_PET_AREA_AURA,       //    119
    SPELL_EFFECT_TELEPORT_GRAVEYARD,        //    120
    SPELL_EFFECT_DUMMYMELEE,                //    121
    SPELL_EFFECT_UNKNOWN1,                  //    122
    SPELL_EFFECT_START_TAXI,                //    123
    SPELL_EFFECT_PLAYER_PULL,               //    124
    SPELL_EFFECT_UNKNOWN4,                  //    125
    SPELL_EFFECT_UNKNOWN5,                  //    126
    SPELL_EFFECT_PROSPECTING,               //    127
    SPELL_EFFECT_APPLY_FRIEND_AREA_AURA,    //    128
    SPELL_EFFECT_APPLY_ENEMY_AREA_AURA,     //    129
    SPELL_EFFECT_UNKNOWN10,                 //    130
    SPELL_EFFECT_UNKNOWN11,                 //    131
    SPELL_EFFECT_PLAY_MUSIC,                //    132
    SPELL_EFFECT_FORGET_SPECIALIZATION,     //    133
    SPELL_EFFECT_KILL_CREDIT,               //    134
    SPELL_EFFECT_UNKNOWN15,                 //    135
    SPELL_EFFECT_UNKNOWN16,                 //    136
    SPELL_EFFECT_UNKNOWN17,                 //    137
    SPELL_EFFECT_UNKNOWN18,                 //    138
    SPELL_EFFECT_CLEAR_QUEST,               //    139
    SPELL_EFFECT_UNKNOWN20,                 //    140
    SPELL_EFFECT_UNKNOWN21,                 //    141
    SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE,  //    142
    SPELL_EFFECT_APPLY_OWNER_AREA_AURA,     //    143
    SPELL_EFFECT_UNKNOWN23,                 //    144
    SPELL_EFFECT_UNKNOWN24,                 //    145
    SPELL_EFFECT_ACTIVATE_RUNES,            //    146
    SPELL_EFFECT_UNKNOWN26,                 //    147
    SPELL_EFFECT_UNKNOWN27,                 //    148
    SPELL_EFFECT_QUEST_FAIL,                //    149
    SPELL_EFFECT_UNKNOWN28,                 //    150
    SPELL_EFFECT_UNKNOWN29,                 //    151
    SPELL_EFFECT_UNKNOWN30,                 //    152
    SPELL_EFFECT_SUMMON_TARGET,             //    153
    SPELL_EFFECT_SUMMON_REFER_A_FRIEND,     //    154
    SPELL_EFFECT_TAME_CREATURE,             //    155
    SPELL_EFFECT_ADD_SOCKET,                //    156
    SPELL_EFFECT_CREATE_ITEM2,				//    157
    SPELL_EFFECT_MILLING,					//    158
    SPELL_EFFECT_UNKNOWN37,                 //    159
    SPELL_EFFECT_UNKNOWN38,                 //    160
    SPELL_EFFECT_LEARN_SPEC,                //    161
    SPELL_EFFECT_ACTIVATE_SPEC,             //    162
    TOTAL_SPELL_EFFECTS,                    //    163
};

// target type flags
enum SpellTargetTypes
{
    SPELL_TARGET_TYPE_NONE              = 0x01,
    SPELL_TARGET_TYPE_PROFESSION        = 0x02,
    SPELL_TARGET_TYPE_NONE1             = 0x04,
    SPELL_TARGET_TYPE_NONE2             = 0x08,
    SPELL_TARGET_TYPE_ENCHANTABLE_ITEM  = 0x10,
    SPELL_TARGET_TYPE_UNK               = 0x20,     // seems to be scripted stuff
    SPELL_TARGET_TYPE_UNK0              = 0x40,     // lots of spells interesting to research this one further
    SPELL_TARGET_TYPE_UNK1              = 0x80,     // something todo with scripted and GM stuff
    SPELL_TARGET_TYPE_UNK2              = 0x100,    // lots of spells interesting to research this one further...
    SPELL_TARGET_TYPE_PLAYER_CORPSE     = 0x200,
    SPELL_TARGET_TYPE_DEATHx            = 0x400,
    SPELL_TARGET_TYPE_NONE3             = 0x800,
    SPELL_TARGET_TYPE_NONE4             = 0x1000,
    SPELL_TARGET_TYPE_NONE5             = 0x2000,
    SPELL_TARGET_TYPE_GAME_OBJECTS      = 0x4000, // like chests and mining
    SPELL_TARGET_TYPE_DEATH             = 0x8000,
};

enum SpellTypes // SPELL_ENTRY_buffType
{
    SPELL_TYPE_NONE                 = 0x00000000,
    SPELL_TYPE_SEAL                 = 0x00000001,
    SPELL_TYPE_ASPECT               = 0x00000002,
    SPELL_TYPE_BLESSING             = 0x00000004,
    SPELL_TYPE_CURSE                = 0x00000008,
    SPELL_TYPE_STING                = 0x00000010,
    SPELL_TYPE_ARMOR                = 0x00000020,
    SPELL_TYPE_AURA                 = 0x00000040,
    //hmm these could be named simply incompatible spells. One active at a time
    SPELL_TYPE_MARK_GIFT            = 0x00000080,
    SPELL_TYPE_TRACK                = 0x00000100,
    SPELL_TYPE_HUNTER_TRAP          = 0x00000200,
    SPELL_TYPE_MAGE_INTEL           = 0x00000400,
    SPELL_TYPE_MAGE_MAGI            = 0x00000800,
    SPELL_TYPE_MAGE_WARDS           = 0x00001000,
    SPELL_TYPE_PRIEST_SH_PPROT      = 0x00002000,
    SPELL_TYPE_SHIELD               = 0x00004000,
    SPELL_TYPE_FORTITUDE            = 0x00008000,
    SPELL_TYPE_SPIRIT               = 0x00010000,
    SPELL_TYPE_MAGE_AMPL_DUMP       = 0x00020000,
    SPELL_TYPE_WARLOCK_IMMOLATE     = 0x00040000, //maybe there is a better way to trigger the aura state for immolate spell
    SPELL_TYPE_ELIXIR_BATTLE		= 0x00080000,
    SPELL_TYPE_ELIXIR_GUARDIAN      = 0x00100000,
    SPELL_TYPE_ELIXIR_FLASK         = SPELL_TYPE_ELIXIR_BATTLE | SPELL_TYPE_ELIXIR_GUARDIAN, //weee, this contains both battle and guardian elixirs ;)
    SPELL_TYPE_HUNTER_MARK			= 0x00200000,
    SPELL_TYPE_WARRIOR_SHOUT        = 0x00400000,
    SPELL_TYPE_QUIVER_HASTE			= 0x00800000,
    SPELL_TYPE_CORRUPTION			= 0x01000000,
    SPELL_TYPE_HAND					= 0x02000000,
};

//custom stuff generated for spells that will not change in time
enum SpellIsFlags
{
    SPELL_FLAG_IS_DAMAGING				= 0x00000001,
    SPELL_FLAG_IS_HEALING				= 0x00000002,
    SPELL_FLAG_IS_TARGETINGSTEALTHED	= 0x00000004,
    SPELL_FLAG_IS_REQUIRECOOLDOWNUPDATE	= 0x00000008, //it started with rogue cold blood but I'm sure others will come
    SPELL_FLAG_IS_POISON				= 0x00000010, //rogue has a few spells that can stack so can't use the spell_type enum ;)
    SPELL_FLAG_IS_FINISHING_MOVE		= 0x00000020, //rogue has a few spells that can stack so can't use the spell_type enum ;)
    SPELL_FLAG_IS_NOT_USING_DMG_BONUS	= 0x00000040,
    SPELL_FLAG_IS_CHILD_SPELL			= 0x00000080, //auras proc auras that have same name, these should not remove mother aura when adding to target
    SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_ON_PET		= 0x00000100, //we should cast these on pet too
    SPELL_FLAG_IS_CASTED_ON_PET_SUMMON_PET_OWNER	= 0x00000200, //we should cast these on owner too
    SPELL_FLAG_IS_EXPIREING_WITH_PET	= 0x00000400, //when pet dies, we remove this too
    SPELL_FLAG_IS_EXPIREING_ON_PET		= 0x00000800, //when pet is summoned
    SPELL_FLAG_IS_FORCEDDEBUFF			= 0x00001000, // forced to be a debuff
    SPELL_FLAG_IS_FORCEDBUFF			= 0x00002000, // forced to be a buff
    SPELL_FLAG_IS_INHERITING_LEVEL		= 0x00004000, // summons to inherit caster level or not
    SPELL_FLAG_IS_MAXSTACK_FOR_DEBUFF	= 0x00008000, // summons to inherit caster level or not
};

enum SpellCoefficientsFlags
{
    SPELL_FLAG_IS_DOT_OR_HOT_SPELL		= 0x00000001, //Damage over Time or Healing over Time Spells
    SPELL_FLAG_IS_DD_OR_DH_SPELL		= 0x00000002, //Direct Damage or Direct Healing Spells
    SPELL_FLAG_IS_DD_DH_DOT_SPELL		= SPELL_FLAG_IS_DOT_OR_HOT_SPELL | SPELL_FLAG_IS_DD_OR_DH_SPELL, //DoT+(DD|DH) Spells
    SPELL_FLAG_AOE_SPELL				= 0x00000004, //AoE Spells
    SPELL_FLAG_ADITIONAL_EFFECT			= 0x00000008, //Spells with additional effect not DD or DoT or HoT
};

enum DiminishingGroup
{
    DIMINISHING_GROUP_STUN				= 0,
    DIMINISHING_GROUP_STUN_PROC			= 1,
    DIMINISHING_GROUP_ROOT				= 2,
    DIMINISHING_GROUP_ROOT_PROC			= 3,
    DIMINISHING_GROUP_SLEEP				= 4,
    DIMINISHING_GROUP_BLIND_CYCLONE		= 5,
    DIMINISHING_GROUP_GOUGE_POLY_SAP	= 6,
    DIMINISHING_GROUP_FEAR				= 7,
    DIMINISHING_GROUP_CHARM				= 8,
    DIMINISHING_GROUP_KIDNEY_SHOT		= 9,
    DIMINISHING_GROUP_HORROR			= 10,
    DIMINISHING_GROUP_BANISH			= 11,
    DIMINISHING_GROUP_NOT_DIMINISHED	= 12,
    DIMINISHING_GROUP_DISARM			= 13,
    DIMINISHING_GROUP_SILENCE			= 14,
};

enum TeleportEffectCustomFlags
{
    TELEPORT_TO_BINDPOINT				= 1,
    TELEPORT_TO_COORDINATES				= 2,
    TELEPORT_BEHIND_TARGET				= 4,
    TELEPORT_TO_CASTER					= 8
};

ARCEMU_INLINE bool CanAgroHash(uint32 spellhashname)
{
	if(spellhashname == SPELL_HASH_HUNTER_S_MARK)   //hunter's mark
		return false;
	else
		return true;
}

/////////////////////////////////////////////////////////////////////////////////
//bool IsDamagingSpell( SpellEntry *sp )
//  Tells if a Spell is damaging
//
//Parameters
//  SpellEntry *sp  -  Pointer to a SpellEntry structure
//
//Return Value
//  Returns true if the Spell is damaging
//  Returns false otherwise.
//
////////////////////////////////////////////////////////////////////////////////
bool IsDamagingSpell(SpellEntry* sp);
bool CanAggro( SpellEntry *sp );
ARCEMU_INLINE uint32 IsHealingSpell(SpellEntry* sp)
{
	switch(sp->Effect[0])
	{
		case SPELL_EFFECT_HEALTH_LEECH:
		case SPELL_EFFECT_HEAL:
		case SPELL_EFFECT_HEAL_MAX_HEALTH:
			return 1;
		default:
			break;
	}
	switch(sp->Effect[1])
	{
		case SPELL_EFFECT_HEALTH_LEECH:
		case SPELL_EFFECT_HEAL:
		case SPELL_EFFECT_HEAL_MAX_HEALTH:
			return 2;
		default:
			break;
	}
	switch(sp->Effect[2])
	{
		case SPELL_EFFECT_HEALTH_LEECH:
		case SPELL_EFFECT_HEAL:
		case SPELL_EFFECT_HEAL_MAX_HEALTH:
			return 3;
		default:
			break;
	}
	if(sp->Effect[0] == SPELL_EFFECT_APPLY_AURA ||
	        sp->Effect[0] == SPELL_EFFECT_APPLY_GROUP_AREA_AURA ||
	        sp->Effect[0] == SPELL_EFFECT_APPLY_RAID_AREA_AURA)
	{
		switch(sp->EffectApplyAuraName[0])
		{
			case 8://SPELL_AURA_PERIODIC_HEAL:
			case 62://SPELL_AURA_PERIODIC_HEALTH_FUNNEL:
				return 1;
			default:
				break;
		}
	}
	if(sp->Effect[1] == SPELL_EFFECT_APPLY_AURA ||
	        sp->Effect[1] == SPELL_EFFECT_APPLY_GROUP_AREA_AURA ||
	        sp->Effect[1] == SPELL_EFFECT_APPLY_RAID_AREA_AURA)
	{
		switch(sp->EffectApplyAuraName[1])
		{
			case 8://SPELL_AURA_PERIODIC_HEAL:
			case 62://SPELL_AURA_PERIODIC_HEALTH_FUNNEL:
				return 2;
			default:
				break;
		}
	}
	if(sp->Effect[2] == SPELL_EFFECT_APPLY_AURA ||
	        sp->Effect[2] == SPELL_EFFECT_APPLY_GROUP_AREA_AURA ||
	        sp->Effect[2] == SPELL_EFFECT_APPLY_RAID_AREA_AURA)
	{
		switch(sp->EffectApplyAuraName[2])
		{
			case 8://SPELL_AURA_PERIODIC_HEAL:
			case 62://SPELL_AURA_PERIODIC_HEALTH_FUNNEL:
				return 3;
			default:
				break;
		}
	}
	//flash of light, holy light uses scripted effect which is not neciserally heal spell
	if(sp->NameHash == SPELL_HASH_HOLY_LIGHT || sp->NameHash == SPELL_HASH_FLASH_OF_LIGHT)
		return true;

	return false;
}

ARCEMU_INLINE bool IsInrange(LocationVector & location, Object* o, float square_r)
{
	float r = o->GetDistanceSq(location);
	return (r <= square_r);
}

ARCEMU_INLINE bool IsInrange(float x1, float y1, float z1, Object* o, float square_r)
{
	float r = o->GetDistanceSq(x1, y1, z1);
	return (r <= square_r);
}

ARCEMU_INLINE bool IsInrange(float x1, float y1, float z1, float x2, float y2, float z2, float square_r)
{
	float t;
	float r;
	t = x1 - x2;
	r = t * t;
	t = y1 - y2;
	r += t * t;
	t = z1 - z2;
	r += t * t;
	return (r <= square_r);
}

ARCEMU_INLINE bool IsInrange(Object* o1, Object* o2, float square_r)
{
	return IsInrange(o1->GetPositionX(), o1->GetPositionY(), o1->GetPositionZ(),
	                 o2->GetPositionX(), o2->GetPositionY(), o2->GetPositionZ(), square_r);
}

ARCEMU_INLINE bool TargetTypeCheck(Object* obj, uint32 ReqCreatureTypeMask)
{
	if(!ReqCreatureTypeMask)
		return true;

	if(obj->IsCreature())
	{
		CreatureInfo* inf = TO< Creature* >(obj)->GetCreatureInfo();
		if(!(1 << (inf->Type - 1) & ReqCreatureTypeMask))
			return false;
	}
	else if(obj->IsPlayer() && !(UNIT_TYPE_HUMANOID_BIT & ReqCreatureTypeMask))
		return false;
	else
		return false;//mg, how in the hack did we cast it on a GO ? But who cares ?

	return true;
}

class SpellCastTargets
{
	public:
		void read(WorldPacket & data, Object* caster);
		void write(WorldPacket & data);
		SpellCastTargets() : m_targetMask(0), m_unitTarget(0), m_itemTarget(0), m_srcX(0), m_srcY(0), m_srcZ(0),
			m_destX(0), m_destY(0), m_destZ(0), m_srcTransportGuid(0), m_destTransportGuid(0), m_elevation(0.0f), m_speed(0.0f), _transportOffset(0.0f, 0.0f, 0.0f, 0.0f){}

		SpellCastTargets(uint16 TargetMask, uint64 unitTarget, uint64 itemTarget, float srcX, float srcY,
		                 float srcZ, float destX, float destY, float destZ) : m_targetMask(TargetMask), m_unitTarget(unitTarget),
			m_itemTarget(itemTarget), m_srcX(srcX), m_srcY(srcY), m_srcZ(srcZ), m_destX(destX), m_destY(destY), m_destZ(destZ), m_srcTransportGuid(0), m_destTransportGuid(0), m_elevation(0.0f), m_speed(0.0f), _transportOffset(0.0f, 0.0f, 0.0f, 0.0f){}

		SpellCastTargets(uint64 unitTarget) : m_targetMask(0x2), m_unitTarget(unitTarget), m_itemTarget(0),
			m_srcX(0), m_srcY(0), m_srcZ(0), m_destX(0), m_destY(0), m_destZ(0), m_srcTransportGuid(0), m_destTransportGuid(0), m_elevation(0.0f), m_speed(0.0f), _transportOffset(0.0f, 0.0f, 0.0f, 0.0f) {}

		SpellCastTargets(WorldPacket & data, Object * caster) : m_targetMask(0), m_unitTarget(0), m_itemTarget(0), m_srcX(0), m_srcY(0), m_srcZ(0),
			m_destX(0), m_destY(0), m_destZ(0), m_srcTransportGuid(0), m_destTransportGuid(0), m_elevation(0.0f), m_speed(0.0f), _transportOffset(0.0f, 0.0f, 0.0f, 0.0f)
		{
			read(data, caster);
		}

		SpellCastTargets & operator=(const SpellCastTargets & target)
		{
			m_unitTarget = target.m_unitTarget;
			m_itemTarget = target.m_itemTarget;

			m_srcX = target.m_srcX;
			m_srcY = target.m_srcY;
			m_srcZ = target.m_srcZ;

			m_destX = target.m_destX;
			m_destY = target.m_destY;
			m_destZ = target.m_destZ;

			m_strTarget = target.m_strTarget;

			m_targetMask = target.m_targetMask;
			m_srcTransportGuid = target.m_srcTransportGuid;
			m_destTransportGuid = target.m_destTransportGuid;
			m_elevation = target.m_elevation;
			m_speed = target.m_speed;
			_transportOffset = target._transportOffset;
			return *this;
		}

		~SpellCastTargets()	{ m_strTarget.clear(); }
		uint32 m_targetMask;
		uint64 m_unitTarget;
		uint64 m_itemTarget;

		uint64 m_srcTransportGuid;
		float m_srcX, m_srcY, m_srcZ;
		uint64 m_destTransportGuid;
		float m_destX, m_destY, m_destZ;
		string m_strTarget;
		float m_elevation, m_speed;
		LocationVector _transportOffset;
		uint32 GetTargetMask() { return m_targetMask; }
		bool HasSrc()
		{
			if(GetTargetMask() & TARGET_FLAG_SOURCE_LOCATION)
				return true;
			return false;
		}
		bool HasDst() 
		{
			if(GetTargetMask() & TARGET_FLAG_DEST_LOCATION)
				return true;
			return false;
		}
		bool HasDstOrSrc() { return (HasSrc() || HasDst()); }
		float GetElevation() { return m_elevation; }
		void SetElevation(float elevation) { m_elevation = elevation; }
		float GetSpeed() { return m_speed; }
		void SetSpeed(float speed) { m_speed = speed; }
		bool HasTraj() { return m_speed != 0; }
        float GetDist2d() 
		{
			LocationVector src(m_srcX, m_srcY, m_srcZ);
			return sqrt(src.Distance2DSq(m_destX, m_destY));
		}

        float GetSpeedXY() { return m_speed * cos(m_elevation); }
        float GetSpeedZ() { return m_speed * sin(m_elevation); }
};

enum SpellState
{
    SPELL_STATE_NULL      = 0,
    SPELL_STATE_PREPARING = 1,
    SPELL_STATE_CASTING   = 2,
    SPELL_STATE_FINISHED  = 3,
    SPELL_STATE_IDLE      = 4
};

enum DISPEL_TYPE
{
    DISPEL_ZGTRINKETS		= -1,
    DISPEL_NULL				= 0,
    DISPEL_MAGIC			= 1,
    DISPEL_CURSE			= 2,
    DISPEL_DISEASE			= 3,
    DISPEL_POISON			= 4,
    DISPEL_STEALTH			= 5,
    DISPEL_INVISIBILTY		= 6,
    DISPEL_ALL				= 7,
    DISPEL_SPECIAL_NPCONLY	= 8,
    DISPEL_FRENZY			= 9,
};

enum MECHANICS
{
    MECHANIC_NONE = 0,
    MECHANIC_CHARMED, // 1
    MECHANIC_DISORIENTED, // 2
    MECHANIC_DISARMED, // 3
    MECHANIC_DISTRACED, // 4
    MECHANIC_FLEEING, // 5
    MECHANIC_CLUMSY, // 6
    MECHANIC_ROOTED, // 7
    MECHANIC_PACIFIED, // 8
    MECHANIC_SILENCED, // 9
    MECHANIC_ASLEEP, // 10
    MECHANIC_ENSNARED, // 11
    MECHANIC_STUNNED, // 12
    MECHANIC_FROZEN, // 13
    MECHANIC_INCAPACIPATED, // 14
    MECHANIC_BLEEDING, // 15
    MECHANIC_HEALING, // 16
    MECHANIC_POLYMORPHED, // 17
    MECHANIC_BANISHED, // 18
    MECHANIC_SHIELDED, // 19
    MECHANIC_SHACKLED, // 20
    MECHANIC_MOUNTED, // 21
    MECHANIC_SEDUCED, // 22
    MECHANIC_TURNED, // 23
    MECHANIC_HORRIFIED, // 24
    MECHANIC_INVULNARABLE, // 25
    MECHANIC_INTERRUPTED, // 26
    MECHANIC_DAZED, // 27
    MECHANIC_DISCOVERY, // 28
    MECHANIC_INVULNERABLE, // 29
    MECHANIC_SAPPED, // 30
    MECHANIC_ENRAGED, // 31
    MECHANIC_END
};

typedef enum
{
    EFF_TARGET_NONE										= 0,
    EFF_TARGET_SELF										= 1,
    EFF_TARGET_INVISIBLE_OR_HIDDEN_ENEMIES_AT_LOCATION_RADIUS		= 3,
    EFF_TARGET_PET										= 5,
    EFF_TARGET_SINGLE_ENEMY								= 6,
    EFF_TARGET_SCRIPTED_TARGET							= 7,
    EFF_TARGET_ALL_TARGETABLE_AROUND_LOCATION_IN_RADIUS  = 8,
    EFF_TARGET_HEARTSTONE_LOCATION						= 9,
    EFF_TARGET_ALL_ENEMY_IN_AREA							= 15,
    EFF_TARGET_ALL_ENEMY_IN_AREA_INSTANT					= 16,
    EFF_TARGET_TELEPORT_LOCATION							= 17,
    EFF_TARGET_LOCATION_TO_SUMMON						= 18,
    EFF_TARGET_ALL_PARTY_AROUND_CASTER					= 20,
    EFF_TARGET_SINGLE_FRIEND								= 21,
    EFF_TARGET_ALL_ENEMIES_AROUND_CASTER					= 22,
    EFF_TARGET_GAMEOBJECT								= 23,
    EFF_TARGET_IN_FRONT_OF_CASTER						= 24,
    EFF_TARGET_DUEL										= 25,//Don't know the real name!!!
    EFF_TARGET_GAMEOBJECT_ITEM							= 26,
    EFF_TARGET_PET_MASTER								= 27,
    EFF_TARGET_ALL_ENEMY_IN_AREA_CHANNELED				= 28,
    EFF_TARGET_ALL_PARTY_IN_AREA_CHANNELED				= 29,
    EFF_TARGET_ALL_FRIENDLY_IN_AREA						= 30,
    EFF_TARGET_ALL_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME	= 31,
    EFF_TARGET_MINION									= 32,
    EFF_TARGET_ALL_PARTY_IN_AREA							= 33,
    EFF_TARGET_SINGLE_PARTY								= 35,
    EFF_TARGET_PET_SUMMON_LOCATION						= 36,
    EFF_TARGET_ALL_PARTY									= 37,
    EFF_TARGET_SCRIPTED_OR_SINGLE_TARGET					= 38,
    EFF_TARGET_SELF_FISHING								= 39,
    EFF_TARGET_SCRIPTED_GAMEOBJECT						= 40,
    EFF_TARGET_TOTEM_EARTH								= 41,
    EFF_TARGET_TOTEM_WATER								= 42,
    EFF_TARGET_TOTEM_AIR									= 43,
    EFF_TARGET_TOTEM_FIRE								= 44,
    EFF_TARGET_CHAIN										= 45,
    EFF_TARGET_SCIPTED_OBJECT_LOCATION					= 46,
    EFF_TARGET_DYNAMIC_OBJECT							= 47,//not sure exactly where is used
    EFF_TARGET_MULTIPLE_SUMMON_LOCATION					= 48,
    EFF_TARGET_MULTIPLE_SUMMON_PET_LOCATION				= 49,
    EFF_TARGET_SUMMON_LOCATION							= 50,
    EFF_TARGET_CALIRI_EGS								= 51,
    EFF_TARGET_LOCATION_NEAR_CASTER						= 52,
    EFF_TARGET_CURRENT_SELECTION							= 53,
    EFF_TARGET_TARGET_AT_ORIENTATION_TO_CASTER			= 54,
    EFF_TARGET_LOCATION_INFRONT_CASTER					= 55,
    EFF_TARGET_ALL_RAID									= 56,
    EFF_TARGET_PARTY_MEMBER								= 57,
    EFF_TARGET_TARGET_FOR_VISUAL_EFFECT					= 59,
    EFF_TARGET_SCRIPTED_TARGET2							= 60,
    EFF_TARGET_AREAEFFECT_PARTY_AND_CLASS				= 61,
    EFF_TARGET_PRIEST_CHAMPION							= 62, //wtf ?
    EFF_TARGET_NATURE_SUMMON_LOCATION					= 63,
    EFF_TARGET_BEHIND_TARGET_LOCATION					= 65,
    EFF_TARGET_MULTIPLE_GUARDIAN_SUMMON_LOCATION			= 72,
    EFF_TARGET_NETHETDRAKE_SUMMON_LOCATION				= 73,
    EFF_TARGET_SCRIPTED_LOCATION							= 74,
    EFF_TARGET_LOCATION_INFRONT_CASTER_AT_RANGE			= 75,
    EFF_TARGET_ENEMIES_IN_AREA_CHANNELED_WITH_EXCEPTIONS	= 76,
    EFF_TARGET_SELECTED_ENEMY_CHANNELED					= 77,
    EFF_TARGET_SELECTED_ENEMY_DEADLY_POISON				= 86,
    EFF_TARGET_NON_COMBAT_PET							= 90,
    //these are custom, feel free to move them further if targeting gets extended
    EFF_TARGET_CUSTOM_PARTY_INJURED_SINGLE				= 99,
    EFF_TARGET_CUSTOM_PARTY_INJURED_MULTI				= 100,
    EFF_TARGET_CONE_IN_FRONT								= 104,
    EFF_TARGET_LIST_LENGTH_MARKER						= 111,
} SpellEffectTarget;


inline bool HasTargetType(SpellEntry* sp, uint32 ttype)
{
	if(
	    sp->EffectImplicitTargetA[0] == ttype ||
	    sp->EffectImplicitTargetA[1] == ttype ||
	    sp->EffectImplicitTargetA[2] == ttype ||
	    sp->EffectImplicitTargetB[0] == ttype ||
	    sp->EffectImplicitTargetB[1] == ttype ||
	    sp->EffectImplicitTargetB[2] == ttype
	)
		return true;
	return false;
}

inline int GetAiTargetType(SpellEntry* sp)
{
	/*	this is not good as one spell effect can target self and other one an enemy,
		maybe we should make it for each spell effect or use as flags */
	if(
	    HasTargetType(sp, EFF_TARGET_INVISIBLE_OR_HIDDEN_ENEMIES_AT_LOCATION_RADIUS) ||
	    HasTargetType(sp, EFF_TARGET_ALL_TARGETABLE_AROUND_LOCATION_IN_RADIUS) ||
	    HasTargetType(sp, EFF_TARGET_ALL_ENEMY_IN_AREA) ||
	    HasTargetType(sp, EFF_TARGET_ALL_ENEMY_IN_AREA_INSTANT) ||
	    HasTargetType(sp, EFF_TARGET_ALL_ENEMY_IN_AREA_CHANNELED) ||
	    HasTargetType(sp, EFF_TARGET_ALL_TARGETABLE_AROUND_LOCATION_IN_RADIUS_OVER_TIME)
	)
		return TTYPE_DESTINATION;
	if(
	    HasTargetType(sp, EFF_TARGET_LOCATION_TO_SUMMON) ||
	    HasTargetType(sp, EFF_TARGET_IN_FRONT_OF_CASTER) ||
	    HasTargetType(sp, EFF_TARGET_ALL_FRIENDLY_IN_AREA) ||
	    HasTargetType(sp, EFF_TARGET_PET_SUMMON_LOCATION) ||
	    HasTargetType(sp, EFF_TARGET_LOCATION_INFRONT_CASTER) ||
	    HasTargetType(sp, EFF_TARGET_CONE_IN_FRONT)
	)
		return TTYPE_SOURCE;
	if(
	    HasTargetType(sp, EFF_TARGET_SINGLE_ENEMY) ||
	    HasTargetType(sp, EFF_TARGET_ALL_ENEMIES_AROUND_CASTER) ||
	    HasTargetType(sp, EFF_TARGET_DUEL) ||
	    HasTargetType(sp, EFF_TARGET_SCRIPTED_OR_SINGLE_TARGET) ||
	    HasTargetType(sp, EFF_TARGET_CHAIN) ||
	    HasTargetType(sp, EFF_TARGET_CURRENT_SELECTION) ||
	    HasTargetType(sp, EFF_TARGET_TARGET_AT_ORIENTATION_TO_CASTER) ||
	    HasTargetType(sp, EFF_TARGET_MULTIPLE_GUARDIAN_SUMMON_LOCATION) ||
	    HasTargetType(sp, EFF_TARGET_SELECTED_ENEMY_CHANNELED)
	)
		return TTYPE_SINGLETARGET;
	if(
	    HasTargetType(sp, EFF_TARGET_ALL_PARTY_AROUND_CASTER) ||
	    HasTargetType(sp, EFF_TARGET_SINGLE_FRIEND) ||
	    HasTargetType(sp, EFF_TARGET_PET_MASTER) ||
	    HasTargetType(sp, EFF_TARGET_ALL_PARTY_IN_AREA_CHANNELED) ||
	    HasTargetType(sp, EFF_TARGET_ALL_PARTY_IN_AREA) ||
	    HasTargetType(sp, EFF_TARGET_SINGLE_PARTY) ||
	    HasTargetType(sp, EFF_TARGET_ALL_PARTY) ||
	    HasTargetType(sp, EFF_TARGET_ALL_RAID) ||
	    HasTargetType(sp, EFF_TARGET_PARTY_MEMBER) ||
	    HasTargetType(sp, EFF_TARGET_AREAEFFECT_PARTY_AND_CLASS)
	)
		return TTYPE_OWNER;
	if(
	    HasTargetType(sp, EFF_TARGET_SELF) ||
	    HasTargetType(sp, 4) ||
	    HasTargetType(sp, EFF_TARGET_PET) ||
	    HasTargetType(sp, EFF_TARGET_MINION)
	)
		return TTYPE_CASTER;
	return TTYPE_NULL;
}

ARCEMU_INLINE bool IsTargetingStealthed(SpellEntry* sp)
{
	if(
	    HasTargetType(sp, EFF_TARGET_INVISIBLE_OR_HIDDEN_ENEMIES_AT_LOCATION_RADIUS) ||
	    HasTargetType(sp, EFF_TARGET_ALL_ENEMIES_AROUND_CASTER) ||
	    HasTargetType(sp, EFF_TARGET_ALL_ENEMY_IN_AREA_CHANNELED) ||
	    HasTargetType(sp, EFF_TARGET_ALL_ENEMY_IN_AREA_INSTANT)
	)
		return 1;

	if(
	    sp->NameHash == SPELL_HASH_MAGMA_TOTEM
	)
		return 1;

	return 0;
}

// slow
struct SpellTargetMod
{
	SpellTargetMod(uint64 _TargetGuid, uint8 _TargetModType) : TargetGuid(_TargetGuid), TargetModType(_TargetModType)
	{

	}
	uint64 TargetGuid;
	uint8  TargetModType;
};

typedef std::vector<uint64> TargetsList;
typedef std::vector<SpellTargetMod> SpellTargetsList;

typedef void(Spell::*pSpellEffect)(uint32 i);
typedef void(Spell::*pSpellTarget)(uint32 i, uint32 j);

#define POWER_TYPE_HEALTH -2

enum PowerType
{
    POWER_TYPE_MANA         = 0,
    POWER_TYPE_RAGE         = 1,
    POWER_TYPE_FOCUS        = 2,
    POWER_TYPE_ENERGY       = 3,
    POWER_TYPE_HAPPINESS    = 4,
    POWER_TYPE_RUNES        = 5,
    POWER_TYPE_RUNIC_POWER  = 6,
	POWER_TYPE_STEAM        = 61,
	POWER_TYPE_PYRITE       = 41,
	POWER_TYPE_HEAT         = 101,
	POWER_TYPE_OOZE         = 121,
	POWER_TYPE_BLOOD        = 141,
	POWER_TYPE_WRATH        = 142,
};
// we have power type 15 and 31 :S

#define SPEC_PRIMARY 0
#define SPEC_SECONDARY 1

#define GO_FISHING_BOBBER 35591

#define SPELL_SPELL_CHANNEL_UPDATE_INTERVAL 1000
class DummySpellHandler;

enum SpellDidHitResult
{
    SPELL_DID_HIT_SUCCESS					= 0,
    SPELL_DID_HIT_MISS						= 1,
    SPELL_DID_HIT_RESIST					= 2,
    SPELL_DID_HIT_DODGE						= 3,
    SPELL_DID_HIT_PARRY						= 4,
    SPELL_DID_HIT_BLOCK						= 5,
    SPELL_DID_HIT_EVADE						= 6,
    SPELL_DID_HIT_IMMUNE					= 7,
    SPELL_DID_HIT_IMMUNE2					= 8,
    SPELL_DID_HIT_DEFLECT					= 9,  // See - http://www.wowwiki.com/Deflect
    SPELL_DID_HIT_ABSORB					= 10, // See - http://www.wowwiki.com/Absorb
    SPELL_DID_HIT_REFLECT					= 11, // See - http://www.wowwiki.com/Reflect
    NUM_SPELL_DID_HIT_RESULTS,
};

// Target constraints for spells ( mostly scripted stuff )
class SpellTargetConstraint
{

	public:
		SpellTargetConstraint() { }
		~SpellTargetConstraint()
		{
			CreatureTargets.clear();
			GameobjectTargets.clear();
		}

		bool HasCreature(int id)
		{
			size_t size = CreatureTargets.size();

			for(size_t i = 0; i < size; ++i)
				if(CreatureTargets[ i ] == id)
					return true;

			return false;
		}

		bool HasGameobject(int id)
		{
			size_t size = GameobjectTargets.size();

			for(size_t i = 0; i < size; ++i)
				if(GameobjectTargets[ i ] == id)
					return true;

			return false;
		}

		void AddCreature(int id)
		{

			if(!HasCreature(id))
				CreatureTargets.push_back(id);
		}

		void AddGameobject(int id)
		{

			if(!HasGameobject(id))
				GameobjectTargets.push_back(id);
		}

	private:
		std::vector< int > CreatureTargets;
		std::vector< int > GameobjectTargets;
};

// Spell instance
class SERVER_DECL Spell : public EventableObject
{
	public:
		friend class DummySpellHandler;
		Spell(Object* Caster, SpellEntry* info, bool triggered, Aura* aur);
		~Spell();
		typedef std::set<Aura*> UsedSpellMods;
		int32 event_GetInstanceID() { return m_caster->GetInstanceID(); }

		bool m_overrideBasePoints;
		uint32 m_overridenBasePoints[3];

		// Fills specified targets at the area of effect
		void FillSpecifiedTargetsInArea(float srcx, float srcy, float srcz, uint32 ind, uint32 specification);
		// Fills specified targets at the area of effect. We suppose we already inited this spell and know the details
		void FillSpecifiedTargetsInArea(uint32 i, float srcx, float srcy, float srcz, float range, uint32 specification);
		// Fills the targets at the area of effect
		void FillAllTargetsInArea(uint32 i, float srcx, float srcy, float srcz, float range);
		// Fills the targets at the area of effect. We suppose we already inited this spell and know the details
		void FillAllTargetsInArea(float srcx, float srcy, float srcz, uint32 ind);
		// Fills the targets at the area of effect. We suppose we already inited this spell and know the details
		void FillAllTargetsInArea(LocationVector & location, uint32 ind);
		// Fills the targets at the area of effect. We suppose we already inited this spell and know the details
		void FillAllFriendlyInArea(uint32 i, float srcx, float srcy, float srcz, float range);
		//get single Enemy as target
		uint64 GetSinglePossibleEnemy(uint32 i, float prange = 0);
		//get single Enemy as target
		uint64 GetSinglePossibleFriend(uint32 i, float prange = 0);
		//generate possible target list for a spell. Use as last resort since it is not accurate
		bool GenerateTargets(SpellCastTargets* store_buff);
		// Fills the target map of the spell packet
		void FillTargetMap(uint32);
		float GetDirectionAngle(uint32 TargetType);

		void SelectTrajectoryTargets();
		void HandleTargetNoObject();

		// See if we hit the target or can it resist (evade/immune/resist on spellgo) (0=success)
		uint8 DidHit(uint32 effindex, Unit* target);
		// Prepares the spell that's going to cast to targets
		uint8 prepare(SpellCastTargets* targets);
		// Cancels the current spell
		void cancel();
		// Update spell state based on time difference
		void update(uint32 difftime);
		// Casts the spell
		void cast(bool);
		// Finishes the casted spell
		void finish(bool successful = true);
		// Handle the Effects of the Spell
		virtual void HandleEffects(uint64 guid, uint32 i);
		void HandleCastEffects(uint64 guid, uint32 i);

		void HandleModeratedTarget(uint64 guid);

		void HandleModeratedEffects(uint64 guid);

		// Take Power from the caster based on spell power usage
		bool TakePower();
		// Has power?
		bool HasPower();
		// Trigger Spell function that triggers triggered spells
		//void TriggerSpell();

		// Checks the caster is ready for cast
		virtual uint8 CanCast(bool);

		bool HasCustomFlag(uint32 flag)
		{
			if((GetProto()->CustomFlags & flag) != 0)
				return true;
			else
				return false;
		}

		ARCEMU_INLINE bool hasAttribute(uint32 attribute)
		{
			return ((GetProto()->Attributes & attribute) > 0);
		}
		ARCEMU_INLINE bool hasAttributeEx(uint32 attribute)
		{
			return ((GetProto()->AttributesEx & attribute) > 0);
		}
		ARCEMU_INLINE bool hasAttributeExB(uint32 attribute)
		{
			return ((GetProto()->AttributesEx2 & attribute) > 0);
		}
		ARCEMU_INLINE bool hasAttributeExC(uint32 attribute)
		{
			return ((GetProto()->AttributesEx3 & attribute) > 0);
		}
		ARCEMU_INLINE bool hasAttributeExD(uint32 attribute)
		{
			return ((GetProto()->AttributesEx4 & attribute) > 0);
		}
		ARCEMU_INLINE bool hasAttributeExE(uint32 attribute)
		{
			return ((GetProto()->AttributesEx5 & attribute) > 0);
		}
		// Removes reagents, ammo, and items/charges
		void RemoveItems();
		// Calculates the i'th effect value
		int32 CalculateEffect(uint32, Unit* target);
		// Handles Teleport function
		void HandleTeleport(float x, float y, float z, uint32 mapid, Unit* Target);
		// Determines how much skill caster going to gain
		void DetermineSkillUp();
		// Increases cast time of the spell
		void AddTime(uint32 type);
		void AddCooldown();
		void AddStartCooldown();
		//
		uint8 GetErrorAtShapeshiftedCast(SpellEntry* spellInfo, uint32 form);


		bool Reflect(Unit* refunit);

		ARCEMU_INLINE uint32 getState() { return m_spellState; }
		ARCEMU_INLINE void SetUnitTarget(Unit* punit) {unitTarget = punit;}

		// Send Packet functions
		void SendCustomError(uint32 message);
		void SendCastResult(uint8 result, uint32 custommessage = 0);
		void SendSpellStart();
		void SendSpellGo();
		void SendLogExecute();
		void SendInterrupted(uint8 result);
		void SendChannelUpdate(uint32 time);
		void SendChannelStart(uint32 duration);
		void SendResurrectRequest(Player* target);
		void SendTameFailure(uint8 failure);
		static void SendHealSpellOnPlayer(Object* caster, Object* target, uint32 healed, bool critical, uint32 overhealed, uint32 spellid, uint32 absorbed = 0);
		static void SendHealManaSpellOnPlayer(Object* caster, Object* target, uint32 dmg, uint32 powertype, uint32 spellid);


		void HandleAddAura(uint64 guid);
		void writeSpellGoTargets(WorldPacket* data);
		void writeSpellMissedTargets(WorldPacket* data);
		void WriteAmmoToPacket(WorldPacket* data);
		uint32 pSpellId;
		SpellEntry* ProcedOnSpell; //some spells need to know the origins of the proc too
		SpellCastTargets m_targets;
		UsedSpellMods m_appliedMods;
		void CreateItem(uint32 itemId);

		void ApplyAA(uint32 i);

		// Effect Handlers
		void SpellEffectNULL(uint32 i);
		void SpellEffectInstantKill(uint32 i);
		void SpellEffectSchoolDMG(uint32 i);
		virtual void SpellEffectDummy(uint32 i);
		void SpellEffectTeleportUnits(uint32 i);
		void SpellEffectApplyAura(uint32 i);
		void SpellEffectEnvironmentalDamage(uint32 i);
		void SpellEffectPowerDrain(uint32 i);
		void SpellEffectHealthLeech(uint32 i);
		void SpellEffectHeal(uint32 i);
		void SpellEffectBind(uint32 i);
		void SpellEffectQuestComplete(uint32 i);
		void SpellEffectWeapondamageNoschool(uint32 i);
		void SpellEffectResurrect(uint32 i);
		void SpellEffectAddExtraAttacks(uint32 i);
		void SpellEffectDodge(uint32 i);
		void SpellEffectParry(uint32 i);
		void SpellEffectBlock(uint32 i);
		void SpellEffectCreateItem(uint32 i);
		void SpellEffectWeapon(uint32 i);
		void SpellEffectDefense(uint32 i);
		void SpellEffectPersistentAA(uint32 i);

		virtual void SpellEffectSummon(uint32 i);
		void SpellEffectSummonWild(uint32 i, SummonPropertiesEntry* spe, CreatureProto* proto, LocationVector & v);
		void SpellEffectSummonGuardian(uint32 i, SummonPropertiesEntry* spe, CreatureProto* proto, LocationVector & v);
		void SpellEffectSummonTemporaryPet(uint32 i, SummonPropertiesEntry* spe, CreatureProto* proto, LocationVector & v);
		void SpellEffectSummonTotem(uint32 i, SummonPropertiesEntry* spe, CreatureProto* proto, LocationVector & v);
		void SpellEffectSummonPossessed(uint32 i, SummonPropertiesEntry* spe, CreatureProto* proto, LocationVector & v);
		void SpellEffectSummonCompanion(uint32 i, SummonPropertiesEntry* spe, CreatureProto* proto, LocationVector & v);
		void SpellEffectSummonVehicle( uint32 i, SummonPropertiesEntry *spe, CreatureProto *proto, LocationVector &v );
		void SpellEffectLeap(uint32 i);
		void SpellEffectEnergize(uint32 i);
		void SpellEffectWeaponDmgPerc(uint32 i);
		void SpellEffectTriggerMissile(uint32 i);
		void SpellEffectTriggerMissileWithValue(uint32 i);
		void SpellEffectOpenLock(uint32 i);
		void SpellEffectTransformItem(uint32 i);
		void SpellEffectApplyGroupAA(uint32 i);
		void SpellEffectLearnSpell(uint32 i);
		void SpellEffectSpellDefense(uint32 i);
		void SpellEffectDispel(uint32 i);
		void SpellEffectLanguage(uint32 i);
		void SpellEffectDualWield(uint32 i);
		void SpellEffectSkillStep(uint32 i);
		void SpellEffectAddHonor(uint32 i);
		void SpellEffectSpawn(uint32 i);
		void SpellEffectSummonObject(uint32 i);
		void SpellEffectEnchantItem(uint32 i);
		void SpellEffectEnchantItemTemporary(uint32 i);
		void SpellEffectTameCreature(uint32 i);
		void SpellEffectSummonPet(uint32 i);
		void SpellEffectLearnPetSpell(uint32 i);
		void SpellEffectWeapondamage(uint32 i);
		void SpellEffectOpenLockItem(uint32 i);
		void SpellEffectProficiency(uint32 i);
		void SpellEffectSendEvent(uint32 i);
		void SpellEffectPowerBurn(uint32 i);
		void SpellEffectThreat(uint32 i);
		void SpellEffectClearQuest(uint32 i);
		void SpellEffectTriggerSpell(uint32 i);
		void SpellEffectForceCast(uint32 i);
		void SpellEffectApplyRaidAA(uint32 i);
		void SpellEffectPowerFunnel(uint32 i);
		void SpellEffectHealMaxHealth(uint32 i);
		void SpellEffectInterruptCast(uint32 i);
		void SpellEffectDistract(uint32 i);
		void SpellEffectPickpocket(uint32 i);
		void SpellEffectAddFarsight(uint32 i);
		void SpellEffectUseGlyph(uint32 i);
		void SpellEffectHealMechanical(uint32 i);
		void SpellEffectSummonObjectWild(uint32 i);
		void SpellEffectScriptEffect(uint32 i);
		void SpellEffectSanctuary(uint32 i);
		void SpellEffectAddComboPoints(uint32 i);
		void SpellEffectCreateHouse(uint32 i);
		void SpellEffectDuel(uint32 i);
		void SpellEffectStuck(uint32 i);
		void SpellEffectSummonPlayer(uint32 i);
		void SpellEffectActivateObject(uint32 i);
		void SpellEffectBuildingDamage(uint32 i);
		void SpellEffectEnchantHeldItem(uint32 i);
		void SpellEffectSetMirrorName(uint32 i);
		void SpellEffectSelfResurrect(uint32 i);
		void SpellEffectSkinning(uint32 i);
		void SpellEffectCharge(uint32 i);
		void SpellEffectKnockBack(uint32 i);
		void SpellEffectKnockBack2(uint32 i);
		void SpellEffectDisenchant(uint32 i);
		void SpellEffectInebriate(uint32 i);
		void SpellEffectFeedPet(uint32 i);
		void SpellEffectDismissPet(uint32 i);
		void SpellEffectReputation(uint32 i);
		void SpellEffectSummonObjectSlot(uint32 i);
		void SpellEffectDispelMechanic(uint32 i);
		void SpellEffectSummonDeadPet(uint32 i);
		void SpellEffectDestroyAllTotems(uint32 i);
		void SpellEffectDurabilityDamage(uint32 i);
		void SpellEffectDurabilityDamagePCT(uint32 i);
		void SpellEffectResurrectNew(uint32 i);
		void SpellEffectAttackMe(uint32 i);
		void SpellEffectSkinPlayerCorpse(uint32 i);
		void SpellEffectSkill(uint32 i);
		void SpellEffectApplyPetAA(uint32 i);
		void SpellEffectDummyMelee(uint32 i);
		void SpellEffectStartTaxi(uint32 i);
		void SpellEffectPlayerPull(uint32 i);
		void SpellEffectReduceThreatPercent(uint32 i);
		void SpellEffectSpellSteal(uint32 i);
		void SpellEffectProspecting(uint32 i);
		void SpellEffectApplyFriendAA(uint32 i);
		void SpellEffectApplyEnemyAA(uint32 i);
		void SpellEffectRedirectThreat(uint32 i);
		void SpellEffectPlayMusic(uint32 i);
		void SpellEffectForgetSpecialization(uint32 i);
		void SpellEffectKillCredit(uint32 i);
		void SpellEffectRestorePowerPct(uint32 i);
		void SpellEffectTriggerSpellWithValue(uint32 i);
		void SpellEffectApplyOwnerAA(uint32 i);
		void SpellEffectCreatePet(uint32 i);
		void SpellEffectTeachTaxiPath(uint32 i);
		void SpellEffectDualWield2H(uint32 i);
		void SpellEffectEnchantItemPrismatic(uint32 i);
		void SpellEffectCreateItem2(uint32 i);
		void SpellEffectMilling(uint32 i);
		void SpellEffectRenamePet(uint32 i);
		void SpellEffectRestoreHealthPct(uint32 i);
		void SpellEffectLearnSpec(uint32 i);
		void SpellEffectActivateSpec(uint32 i);
		void SpellEffectActivateRunes(uint32 i);
		void SpellEffectJumpTarget(uint32 i);
		void SpellEffectJumpBehindTarget(uint32 i);

		// Spell Targets Handlers
		void SpellTargetNULL(uint32 i, uint32 j);
		void SpellTargetDefault(uint32 i, uint32 j);
		void SpellTargetSelf(uint32 i, uint32 j);
		void SpellTargetInvisibleAOE(uint32 i, uint32 j);
		void SpellTargetFriendly(uint32 i, uint32 j);
		void SpellTargetPet(uint32 i, uint32 j);
		void SpellTargetSingleTargetEnemy(uint32 i, uint32 j);
		void SpellTargetCustomAreaOfEffect(uint32 i, uint32 j);
		void SpellTargetAreaOfEffect(uint32 i, uint32 j);
		void SpellTargetLandUnderCaster(uint32 i, uint32 j); /// I don't think this is the correct name for this one
		void SpellTargetAllPartyMembersRangeNR(uint32 i, uint32 j);
		void SpellTargetSingleTargetFriend(uint32 i, uint32 j);
		void SpellTargetAoE(uint32 i, uint32 j); // something special
		void SpellTargetSingleGameobjectTarget(uint32 i, uint32 j);
		void SpellTargetInFrontOfCaster(uint32 i, uint32 j);
		void SpellTargetSingleFriend(uint32 i, uint32 j);
		void SpellTargetGameobject_itemTarget(uint32 i, uint32 j);
		void SpellTargetPetOwner(uint32 i, uint32 j);
		void SpellTargetEnemysAreaOfEffect(uint32 i, uint32 j);
		void SpellTargetTypeTAOE(uint32 i, uint32 j);
		void SpellTargetAllyBasedAreaEffect(uint32 i, uint32 j);
		void SpellTargetScriptedEffects(uint32 i, uint32 j);
		void SpellTargetSummon(uint32 i, uint32 j);
		void SpellTargetNearbyPartyMembers(uint32 i, uint32 j);
		void SpellTargetSingleTargetPartyMember(uint32 i, uint32 j);
		void SpellTargetScriptedEffects2(uint32 i, uint32 j);
		void SpellTargetPartyMember(uint32 i, uint32 j);
		void SpellTargetDummyTarget(uint32 i, uint32 j);
		void SpellTargetFishing(uint32 i, uint32 j);
		void SpellTargetType40(uint32 i, uint32 j);
		void SpellTargetTotem(uint32 i, uint32 j);
		void SpellTargetChainTargeting(uint32 i, uint32 j);
		void SpellTargetSimpleTargetAdd(uint32 i, uint32 j);
		void SpellTargetAllRaid(uint32 i, uint32 j);
		void SpellTargetTargetAreaSelectedUnit(uint32 i, uint32 j);
		void SpellTargetInFrontOfCaster2(uint32 i, uint32 j);
		void SpellTargetTargetPartyMember(uint32 i, uint32 j);
		void SpellTargetSameGroupSameClass(uint32 i, uint32 j);
		//these are custom
		void SpellTargetSinglePartyInjured(uint32 i, uint32 j);
		void SpellTargetMultiplePartyInjured(uint32 i, uint32 j);
		void SpellTargetNonCombatPet(uint32 i, uint32 j);

		void Heal(int32 amount, bool ForceCrit = false);

		GameObject*		g_caster;
		Unit*			u_caster;
		Item*			i_caster;
		Player*			p_caster;
		Object*			m_caster;

		// 15007 = resurrection sickness

		// This returns SPELL_ENTRY_DmgClass where 0 = DmgClass_NONE, 1 = DmgClass_MAGIC, 2 = DmgClass_MELEE, 3 = DmgClass_RANGED
		// It should NOT be used for weapon_damage_type which needs: 0 = MELEE, 1 = OFFHAND, 2 = RANGED
		ARCEMU_INLINE uint32 GetType() { return (GetProto()->DmgClass == DmgClass_NONE ? DmgClass_MAGIC : GetProto()->DmgClass); }

		std::map<uint64, Aura*> m_pendingAuras;
		TargetsList UniqueTargets;
		SpellTargetsList    ModeratedTargets;

		ARCEMU_INLINE Item* GetItemTarget() { return itemTarget; }
		ARCEMU_INLINE Unit* GetUnitTarget() { return unitTarget; }
		ARCEMU_INLINE Player* GetPlayerTarget() { return playerTarget; }
		ARCEMU_INLINE GameObject* GetGameObjectTarget() { return gameObjTarget; }
		Corpse* GetCorpseTarget() { return corpseTarget; }

		uint32 chaindamage;
		// -------------------------------------------

		bool IsAspect();
		bool IsSeal();

		ARCEMU_INLINE SpellEntry* GetProto() { return (m_spellInfo_override == NULL) ?  m_spellInfo : m_spellInfo_override; }
		void InitProtoOverride()
		{
			if(m_spellInfo_override != NULL)
				return;
			m_spellInfo_override = dbcSpell.CreateCopy(m_spellInfo);
		}
		uint32 GetDuration()
		{
			if(bDurSet)return Dur;
			bDurSet = true;
			int32 c_dur = 0;

			if(GetProto()->DurationIndex)
			{
				SpellDuration* sd = dbcSpellDuration.LookupEntryForced(GetProto()->DurationIndex);
				if(sd)
				{
					//check for negative and 0 durations.
					//duration affected by level
					if((int32)sd->Duration1 < 0 && sd->Duration2 && u_caster)
					{
						this->Dur = uint32(((int32)sd->Duration1 + (sd->Duration2 * u_caster->getLevel())));
						if((int32)this->Dur > 0 && sd->Duration3 > 0 && (int32)this->Dur > (int32)sd->Duration3)
						{
							this->Dur = sd->Duration3;
						}

						if((int32)this->Dur < 0)
							this->Dur = 0;
						c_dur = this->Dur;
					}
					if(!c_dur)
					{
						this->Dur = sd->Duration1;
					}
					//combo point lolerCopter? ;P
					if(p_caster)
					{
						uint32 cp = p_caster->m_comboPoints;
						if(cp)
						{
							uint32 bonus = (cp * (sd->Duration3 - sd->Duration1)) / 5;
							if(bonus)
							{
								this->Dur += bonus;
								m_requiresCP = true;
							}
						}
					}

					/*if(GetProto()->SpellFamilyFlags && u_caster)
					{
						if(Player * p = u_caster->GetSpellModOwner())
							p->ApplySpellMod(GetProto()->Id, SPELLMOD_DURATION, Dur, this);
					}*/
				}
				else
				{
					this->Dur = (uint32) - 1;
				}
			}
			else
			{
				this->Dur = (uint32) - 1;
			}

			return this->Dur;
		}

		ARCEMU_INLINE float GetRadius(uint32 i)
		{
			if(bRadSet[i])return Rad[i];
			bRadSet[i] = true;
			Rad[i] =::GetRadius(dbcSpellRadius.LookupEntry(GetProto()->EffectRadiusIndex[i]));
			if(GetProto()->SpellFamilyFlags && u_caster)
			{
				if(Player * p = u_caster->GetSpellModOwner())
					p->ApplySpellMod(GetProto()->Id, SPELLMOD_RADIUS, Rad[i]);				
			}

			return Rad[i];
		}

		ARCEMU_INLINE static uint32 GetBaseThreat(uint32 dmg)
		{
			//there should be a formula to determine what spell cause threat and which don't
			/*        switch(GetProto()->NameHash)
			        {
			            //hunter's mark
			            case 4287212498:
			                {
			                    return 0;
			                }break;
			        }*/
			return dmg;
		}

		ARCEMU_INLINE static uint32 GetMechanic(SpellEntry* sp)
		{
			if(sp->Mechanic)
				return sp->Mechanic;
			if(sp->EffectMechanic[2])
				return sp->EffectMechanic[2];
			if(sp->EffectMechanic[1])
				return sp->EffectMechanic[1];
			if(sp->EffectMechanic[0])
				return sp->EffectMechanic[0];

			return 0;
		}

		bool IsStealthSpell();
		bool IsInvisibilitySpell();

		int32 damage;
		Aura* m_triggeredByAura;
		signed int	forced_basepoints[3]; //some talent inherit base points from previous caster spells

		bool m_triggeredSpell;
		bool m_AreaAura;
		//uint32 TriggerSpellId;  // used to set next spell to use
		//uint64 TriggerSpellTarget; // used to set next spell target
		bool m_requiresCP;
		float m_castPositionX;
		float m_castPositionY;
		float m_castPositionZ;
		int32 m_charges;

		int32 damageToHit;
		uint32 castedItemId;
		uint8 extra_cast_number;
		uint32 m_glyphslot;

		void SendCastSuccess(Object* target);
		void SendCastSuccess(const uint64 & guid);

		bool duelSpell;

		////////////////////////////////////////////////////////////////////////////////
		//bool DuelSpellNoMoreValid()
		//  Tells if the Spell was being casted while dueling but now the duel is over
		//
		//Return Value
		//  Returns true if Spell is now invalid because the duel is over.
		//  Returns false if Spell is valid.
		//
		///////////////////////////////////////////////////////////////////////////////
		bool DuelSpellNoMoreValid()
		{
			if(duelSpell && (
	            (p_caster != NULL && p_caster->GetDuelState() != DUEL_STATE_STARTED) ||
	            (u_caster != NULL && u_caster->IsPet() && TO< Pet* >(u_caster)->GetPetOwner() && TO< Pet* >(u_caster)->GetPetOwner()->GetDuelState() != DUEL_STATE_STARTED)))
				return true;
			else
				return false;
		}

		ARCEMU_INLINE void safe_cancel()
		{
			m_cancelled = true;
		}

		/// Spell state's
		/// Spell failed
		ARCEMU_INLINE bool GetSpellFailed() {return m_Spell_Failed;}
		ARCEMU_INLINE void SetSpellFailed(bool failed = true) {m_Spell_Failed = failed;}

		ARCEMU_INLINE bool IsReflected() {return m_IsReflected;}
		ARCEMU_INLINE void SetReflected(bool reflected = true) {m_IsReflected = reflected;}

		/// Spell possibility's
		ARCEMU_INLINE bool GetCanReflect() {return m_CanRelect;}
		ARCEMU_INLINE void SetCanReflect(bool reflect = true) {m_CanRelect = reflect;}


		Spell* m_reflectedParent;
		int32 GetTimer() { return m_timer; }
	protected:

		/// Spell state's
		bool    m_usesMana;
		bool    m_Spell_Failed;			//for 5sr
		bool    m_IsReflected;
		bool    m_Delayed;
		uint8	m_DelayStep;			//3.0.2 - spells can only be delayed twice.

		// Spell possibility's
		bool m_CanRelect;

		bool m_IsCastedOnSelf;

		bool hadEffect;

		uint32  m_spellState;
		int32   m_castTime;
		int32   m_timer;
		int64 m_magnetTarget;

		// Current Targets to be used in effect handler
		Unit*       unitTarget;
		Item*       itemTarget;
		GameObject* gameObjTarget;
		Player*     playerTarget;
		Corpse*     corpseTarget;
		uint32      add_damage;

		uint8       cancastresult;
		uint32      Dur;
		bool        bDurSet;
		float       Rad[3];
		bool        bRadSet[3];
		bool        m_cancelled;
		bool		m_isCasting;
		uint8		m_rune_avail_before;
		ByteBuffer * m_effectExecuteData[MAX_SPELL_EFFECTS];
		
		//void _DamageRangeUpdate();

		ARCEMU_INLINE bool HasTarget(const uint64 & guid, TargetsList* tmpMap)
		{
			for(TargetsList::iterator itr = tmpMap->begin(); itr != tmpMap->end(); ++itr)
			{
				if(*itr == guid)
					return true;
			}

			for(SpellTargetsList::iterator itr = ModeratedTargets.begin(); itr != ModeratedTargets.end(); ++itr)
				if((*itr).TargetGuid == guid)
					return true;

			return false;
		}

		SpellTargetConstraint* m_target_constraint;

		virtual void DoAfterHandleEffect(Unit* target, uint32 i) {}

	public: //Modified by LUAppArc private->public
		virtual int32 DoCalculateEffect(uint32 i, Unit* target, int32 value);
		uint64 m_delayMoment;

		TargetsList m_targetUnits[3];
		void SafeAddTarget(TargetsList* tgt, uint64 guid);

		void SafeAddMissedTarget(uint64 guid);
		void SafeAddModeratedTarget(uint64 guid, uint16 type);

		friend class DynamicObject;
		void DetermineSkillUp(uint32 skillid, uint32 targetlevel, uint32 multiplicator = 1);
		void DetermineSkillUp(uint32 skillid);

		uint32 GetTargetType(uint32 value, uint32 i);
		bool AddTarget(uint32 i, uint32 TargetType, Object* obj);
		void AddAOETargets(uint32 i, uint32 TargetType, float r, uint32 maxtargets);
		void AddPartyTargets(uint32 i, uint32 TargetType, float r, uint32 maxtargets);
		void AddRaidTargets(uint32 i, uint32 TargetType, float r, uint32 maxtargets, bool partylimit = false);
		void AddChainTargets(uint32 i, uint32 TargetType, float r, uint32 maxtargets);
		void AddConeTargets(uint32 i, uint32 TargetType, float r, uint32 maxtargets);
		void AddScriptedOrSpellFocusTargets(uint32 i, uint32 TargetType, float r, uint32 maxtargets);
		void InitEffectExecuteData(uint8 effIndex);
		void CleanupEffectExecuteData();
        void ExecuteLogEffectTakeTargetPower(uint8 effIndex, Unit* target, uint32 powerType, uint32 powerTaken, float gainMultiplier);
        void ExecuteLogEffectExtraAttacks(uint8 effIndex, uint64 victim, uint32 attCount);
        void ExecuteLogEffectInterruptCast(uint8 effIndex, Unit* victim, uint32 spellId);
        void ExecuteLogEffectDurabilityDamage(uint8 effIndex, Unit* victim, uint32 damage);
        void ExecuteLogEffectOpenLock(uint8 effIndex, Object* obj);
        void ExecuteLogEffectCreateItem(uint8 effIndex, uint32 entry);
        void ExecuteLogEffectDestroyItem(uint8 effIndex, uint32 entry);
        void ExecuteLogEffectSummonObject(uint8 effIndex, Object* obj);
        void ExecuteLogEffectUnsummonObject(uint8 effIndex, Object* obj);
        void ExecuteLogEffectResurrect(uint8 effIndex, Unit* target);
		bool CooldownCanCast();
	public:
		SpellEntry* m_spellInfo;
		SpellEntry* m_spellInfo_override;//used by spells that should have dynamic variables in spellentry.

};

void ApplyDiminishingReturnTimer(uint32* Duration, Unit* Target, SpellEntry* spell);
void UnapplyDiminishingReturnTimer(Unit* Target, SpellEntry* spell);
uint32 GetDiminishingGroup(uint32 NameHash);
uint32 GetSpellDuration(SpellEntry* sp, Unit* caster = NULL);
//Logs if the spell doesn't exist, using Debug loglevel.
SpellEntry* CheckAndReturnSpellEntry(uint32 spellid);

#endif
