#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct FaceAnimationInfo // size: 0x8
	{
		union
		{
			std::array<uint8_t, 2> sounds; // MMExt: 1..2, here 0..1 | 0x0 (0 decimal)
			struct
			{
				uint8_t sound1; // 0x0 (0 decimal)
				uint8_t sound2; // 0x1 (1 decimal)
			};
		};
		SKIP(1);
		union
		{
			std::array<uint8_t, 5> expressions; // MMExt: 1..5, here 0..4 | 0x3 (3 decimal)
			struct
			{
				uint8_t expression1; // 0x3 (3 decimal)
				uint8_t expression2; // 0x4 (4 decimal)
				uint8_t expression3; // 0x5 (5 decimal)
				uint8_t expression4; // 0x6 (6 decimal)
				uint8_t expression5; // 0x7 (7 decimal)
			};
		};
	};
	static_assert(sizeof(mm6::FaceAnimationInfo) == 0x8, "Invalid \"mm6::FaceAnimationInfo\" structure size");
	static_assert(offsetof(mm6::FaceAnimationInfo, sound2) == 1);
	static_assert(offsetof(mm6::FaceAnimationInfo, expressions) == 3);
	static_assert(offsetof(mm6::FaceAnimationInfo, expression1) == 3);
	static_assert(offsetof(mm6::FaceAnimationInfo, expression2) == 4);
	static_assert(offsetof(mm6::FaceAnimationInfo, expression3) == 5);
	static_assert(offsetof(mm6::FaceAnimationInfo, expression4) == 6);
	static_assert(offsetof(mm6::FaceAnimationInfo, expression5) == 7);



	struct BaseBonus // size: 0x4
	{
		int16_t base; // 0x0 (0 decimal)
		int16_t bonus; // 0x2 (2 decimal)
	};
	static_assert(sizeof(mm6::BaseBonus) == 0x4, "Invalid \"mm6::BaseBonus\" structure size");
	static_assert(offsetof(mm6::BaseBonus, bonus) == 2);



	struct LloydBeaconSlot // size: 0x1C
	{
		int64_t expireTime; // 0x0 (0 decimal)
		union
		{
			std::array<int32_t, 3> pos; // 0x8 (8 decimal)
			struct
			{
				int32_t x; // 0x8 (8 decimal)
				int32_t y; // 0xC (12 decimal)
				int32_t z; // 0x10 (16 decimal)
			};
		};
		int16_t direction; // 0x14 (20 decimal)
		int16_t lookAngle; // 0x16 (22 decimal)
		int16_t active; // 0x18 (24 decimal)
		union
		{
			std::array<uint8_t, 2> map; // Unknown type | 0x1A (26 decimal)
			int16_t mapIndex; // 0x1A (26 decimal)
		};
	};
	static_assert(sizeof(mm6::LloydBeaconSlot) == 0x1C, "Invalid \"mm6::LloydBeaconSlot\" structure size");
	static_assert(offsetof(mm6::LloydBeaconSlot, pos) == 8);
	static_assert(offsetof(mm6::LloydBeaconSlot, x) == 8);
	static_assert(offsetof(mm6::LloydBeaconSlot, y) == 12);
	static_assert(offsetof(mm6::LloydBeaconSlot, z) == 16);
	static_assert(offsetof(mm6::LloydBeaconSlot, direction) == 20);
	static_assert(offsetof(mm6::LloydBeaconSlot, lookAngle) == 22);
	static_assert(offsetof(mm6::LloydBeaconSlot, active) == 24);
	static_assert(offsetof(mm6::LloydBeaconSlot, map) == 26);
	static_assert(offsetof(mm6::LloydBeaconSlot, mapIndex) == 26);



	struct Player // size: 0x161C
	{
		uint8_t face; // 0x0 (0 decimal)
		std::array<char, 16> name; // fixed size string, requires null terminator | 0x1 (1 decimal)
		bool sex; // 0x11 (17 decimal)
		uint8_t clas; // 0x12 (18 decimal)
		SKIP(1);
		union
		{
			struct // size: 0x1C, MMExt union
			{
				mm6::BaseBonus _0; // 0x14 (20 decimal)
				mm6::BaseBonus _1; // 0x18 (24 decimal)
				mm6::BaseBonus _2; // 0x1C (28 decimal)
				mm6::BaseBonus _3; // 0x20 (32 decimal)
				mm6::BaseBonus _5; // 0x24 (36 decimal)
				mm6::BaseBonus _4; // 0x28 (40 decimal)
				mm6::BaseBonus _6; // 0x2C (44 decimal)
			} stats;
			static_assert(sizeof(stats) == 0x1C, "Invalid \"stats\" structure size");;
			struct
			{
				int16_t mightBase; // 0x14 (20 decimal)
				int16_t mightBonus; // 0x16 (22 decimal)
				int16_t intellectBase; // 0x18 (24 decimal)
				int16_t intellectBonus; // 0x1A (26 decimal)
				int16_t personalityBase; // 0x1C (28 decimal)
				int16_t personalityBonus; // 0x1E (30 decimal)
				int16_t enduranceBase; // 0x20 (32 decimal)
				int16_t enduranceBonus; // 0x22 (34 decimal)
				int16_t speedBase; // 0x24 (36 decimal)
				int16_t speedBonus; // 0x26 (38 decimal)
				int16_t accuracyBase; // 0x28 (40 decimal)
				int16_t accuracyBonus; // 0x2A (42 decimal)
				int16_t luckBase; // 0x2C (44 decimal)
				int16_t luckBonus; // 0x2E (46 decimal)
			};
		};
		int16_t armorClassBonus; // 0x30 (48 decimal)
		int16_t levelBase; // 0x32 (50 decimal)
		int16_t levelBonus; // 0x34 (52 decimal)
		int16_t ageBonus; // 0x36 (54 decimal)
		SKIP(40);
		std::array<uint8_t, 31> skills; // 0x60 (96 decimal)
		std::array<uint8_t, 11> awards; // array of abits (real index = 7 - usual) | 0x7F (127 decimal)
		SKIP(53);
		std::array<bool, 100> spells; // MMExt: 1..100, here 0..99 | 0xBF (191 decimal)
		SKIP(5);
		std::array<uint32_t, 7> usedBlackPotions; // MMExt: 181..187, here 0..6 | 4-byte boolean | 0x128 (296 decimal)
		std::array<mm6::Item, 138> items; // MMExt: 1..138, here 0..137 | 0x144 (324 decimal)
		std::array<int32_t, 126> inventory; // 0x105C (4188 decimal) | MMExt info: ('Items' index) for main item cell,  -(1 + main 'Inventory' cell index) for other cells
		union
		{
			struct // size: 0x14, MMExt union
			{
				mm6::BaseBonus _2; // 0x1254 (4692 decimal)
				mm6::BaseBonus _4; // 0x1258 (4696 decimal)
				mm6::BaseBonus _3; // 0x125C (4700 decimal)
				mm6::BaseBonus _5; // 0x1260 (4704 decimal)
				mm6::BaseBonus _1; // 0x1264 (4708 decimal)
			} resistances;
			static_assert(sizeof(resistances) == 0x14, "Invalid \"resistances\" structure size");;
			struct
			{
				int16_t fireResistanceBase; // 0x1254 (4692 decimal)
				int16_t fireResistanceBonus; // 0x1256 (4694 decimal)
				int16_t coldResistanceBase; // 0x1258 (4696 decimal)
				int16_t coldResistanceBonus; // 0x125A (4698 decimal)
				int16_t elecResistanceBase; // 0x125C (4700 decimal)
				int16_t elecResistanceBonus; // 0x125E (4702 decimal)
				int16_t poisonResistanceBase; // 0x1260 (4704 decimal)
				int16_t poisonResistanceBonus; // 0x1262 (4706 decimal)
				int16_t magicResistanceBase; // 0x1264 (4708 decimal)
				int16_t magicResistanceBonus; // 0x1266 (4710 decimal)
			};
		};
		std::array<mm6::SpellBuff, 16> spellBuffs; // 0x1268 (4712 decimal)
		SKIP(20);
		int16_t recoveryDelay; // 0x137C (4988 decimal)
		uint8_t attackSpell; // 0x137E (4990 decimal) | MMExt info: Added in version 2.5 of my patches
		SKIP(1);
		union
		{
			std::array<int64_t, 17> conditions; // 0x1380 (4992 decimal)
			struct
			{
				int64_t cursed; // 0x1380 (4992 decimal)
				int64_t weak; // 0x1388 (5000 decimal)
				int64_t asleep; // 0x1390 (5008 decimal)
				int64_t afraid; // 0x1398 (5016 decimal)
				int64_t drunk; // 0x13A0 (5024 decimal)
				int64_t insane; // 0x13A8 (5032 decimal)
				int64_t poison1; // 0x13B0 (5040 decimal)
				int64_t disease1; // 0x13B8 (5048 decimal)
				int64_t poison2; // 0x13C0 (5056 decimal)
				int64_t disease2; // 0x13C8 (5064 decimal)
				int64_t poison3; // 0x13D0 (5072 decimal)
				int64_t disease3; // 0x13D8 (5080 decimal)
				int64_t paralyzed; // 0x13E0 (5088 decimal)
				int64_t unconscious; // 0x13E8 (5096 decimal)
				int64_t dead; // 0x13F0 (5104 decimal)
				int64_t stoned; // 0x13F8 (5112 decimal)
				int64_t eradicated; // 0x1400 (5120 decimal)
			};
		};
		int64_t good; // 0x1408 (5128 decimal)
		int32_t skillPoints; // 0x1410 (5136 decimal)
		union
		{
			int32_t HP; // 0x1414 (5140 decimal)
			int32_t hitPoints; // 0x1414 (5140 decimal)
		};
		union
		{
			int32_t SP; // 0x1418 (5144 decimal)
			int32_t spellPoints; // 0x1418 (5144 decimal)
		};
		int32_t birthYear; // 0x141C (5148 decimal)
		union
		{
			int64_t exp; // 0x1420 (5152 decimal)
			int64_t experience; // 0x1420 (5152 decimal)
		};
		union
		{
			std::array<int32_t, 16> equippedItems; // 0x1428 (5160 decimal)
			struct
			{
				int32_t itemExtraHand; // 0x1428 (5160 decimal)
				int32_t itemMainHand; // 0x142C (5164 decimal)
				int32_t itemBow; // 0x1430 (5168 decimal)
				int32_t itemArmor; // 0x1434 (5172 decimal)
				int32_t itemHelm; // 0x1438 (5176 decimal)
				int32_t itemBelt; // 0x143C (5180 decimal)
				int32_t itemCloak; // 0x1440 (5184 decimal)
				union
				{
					int32_t itemGauntlets; // 0x1444 (5188 decimal) | MMExt info: Was called 'ItemGountlets' before MMExtension v2.3, old name is supported for backward compatibility
					int32_t itemGountlets; // 0x1444 (5188 decimal)
				};
				int32_t itemBoots; // 0x1448 (5192 decimal)
				int32_t itemAmulet; // 0x144C (5196 decimal)
				int32_t itemRing1; // 0x1450 (5200 decimal)
				int32_t itemRing2; // 0x1454 (5204 decimal)
				int32_t itemRing3; // 0x1458 (5208 decimal)
				int32_t itemRing4; // 0x145C (5212 decimal)
				int32_t itemRing5; // 0x1460 (5216 decimal)
				int32_t itemRing6; // 0x1464 (5220 decimal)
			};
		};
		SKIP(198);
		int8_t spellBookPage; // 0x152E (5422 decimal)
		uint8_t quickSpell; // 0x152F (5423 decimal)
		std::array<uint8_t, 64> playerBits; // array of abits (real index = 7 - usual) | 0x1530 (5424 decimal)
		int8_t meleeAttackBonus; // 0x1570 (5488 decimal)
		SKIP(1);
		int8_t meleeDamageBonus; // 0x1572 (5490 decimal)
		SKIP(1);
		int8_t rangedAttackBonus; // 0x1574 (5492 decimal)
		SKIP(1);
		int8_t rangedDamageBonus; // 0x1576 (5494 decimal)
		SKIP(1);
		union
		{
			int8_t fullHPBonus; // 0x1578 (5496 decimal)
			int8_t fullHitPointsBonus; // 0x1578 (5496 decimal)
		};
		SKIP(1);
		union
		{
			int8_t fullSPBonus; // 0x157A (5498 decimal)
			int8_t fullSpellPointsBonus; // 0x157A (5498 decimal)
		};
		SKIP(1);
		int16_t expression; // 0x157C (5500 decimal)
		int16_t expressionTimePassed; // 0x157E (5502 decimal)
		int16_t expressionLength; // 0x1580 (5504 decimal)
		SKIP(10);
		std::array<mm6::LloydBeaconSlot, 5> beacons; // 0x158C (5516 decimal)
		uint8_t devineInterventionCasts; // 0x1618 (5656 decimal)
		uint8_t armageddonCasts; // 0x1619 (5657 decimal)
		SKIP(2);
		int __thiscall removeFromInventory(/*Slot*/); // address: 0x4873F0 | defaults: (this)
		int __thiscall getBaseArmorClass(); // address: 0x482570 | defaults: (this)
		int __thiscall getArmorClass(); // address: 0x482700 | defaults: (this)
		int __thiscall getBaseAge(); // address: 0x4828A0 | defaults: (this)
		int __thiscall getBaseMight(); // address: 0x47D830 | defaults: (this)
		int __thiscall recover(/*ByAmount*/); // address: 0x482BB0 | defaults: (this)
		int __thiscall getBasePersonality(); // address: 0x47D870 | defaults: (this)
		int __thiscall getBaseEndurance(); // address: 0x47D890 | defaults: (this)
		int __thiscall getBaseAccuracy(); // address: 0x47D8B0 | defaults: (this)
		int __thiscall getBaseSpeed(); // address: 0x47D8D0 | defaults: (this)
		int __thiscall getBaseLuck(); // address: 0x47D8F0 | defaults: (this)
		int __thiscall getBaseLevel(); // address: 0x47D910 | defaults: (this)
		int __thiscall getLevel(); // address: 0x47D930 | defaults: (this)
		int __thiscall getMight(); // address: 0x47D960 | defaults: (this)
		int __thiscall getIntellect(); // address: 0x47DAA0 | defaults: (this)
		int __thiscall getPersonality(); // address: 0x47DBE0 | defaults: (this)
		int __thiscall getEndurance(); // address: 0x47DD20 | defaults: (this)
		int __thiscall getAccuracy(); // address: 0x47DE60 | defaults: (this)
		int __thiscall getSpeed(); // address: 0x47DFA0 | defaults: (this)
		int __thiscall getLuck(); // address: 0x47E0E0 | defaults: (this)
		int __thiscall getMeleeAttack(/*IgnoreExtraHand [MM7+] = false*/); // address: 0x47E270 | defaults: (this), false
		int __thiscall calcMeleeDamage(/*JustWeaponDamage = false, IgnoreExtraHand = false, MonsterId = -1*/); // address: 0x47E410 | defaults: (this), false, false, -1
		int __thiscall getRangedAttack(); // address: 0x47E810 | defaults: (this)
		int __thiscall calcRangedDamage(/*MonsterId = -1*/); // address: 0x47EAD0 | defaults: (this), -1
		bool __thiscall isConscious(); // address: 0x4876E0 | defaults: (this)
		bool __stdcall calcHitOrMiss(/*Monster:structs.MapMonster, Range = 0, Bonus = 0*/); // address: 0x421CB0 | defaults: (this), 0, 0, 0
		int __thiscall setRecoveryDelayRaw(/*Delay*/); // address: 0x482C80 | defaults: (this)
		int __thiscall getAge(); // address: 0x482920 | defaults: (this)
		char* __thiscall getMeleeDamageRangeText(); // address: 0x47EB80 | defaults: (this)
		char* __thiscall getRangedDamageRangeText(); // address: 0x47EEB0 | defaults: (this)
		int __thiscall canTrain(); // address: 0x47F010 | defaults: (this)
		int __thiscall getFullHP(); // address: 0x481EA0 | defaults: (this)
		int __thiscall doDamage(/*Damage, DamageKind:const.Damage = const.Damage.Phys*/); // address: 0x47FEE0 | defaults: (this), 0, 0
		int __thiscall addHP(/*Amount*/); // address: 0x47FB60 | defaults: (this)
		int __thiscall getFullHitPoints(); // address: 0x481EA0 | defaults: 0
		int __thiscall getFullSpellPoints(); // address: 0x482090 | defaults: 0
		int __thiscall getFullSP(); // address: 0x482090 | defaults: (this)
		int __thiscall calcStatBonusByItems(/*Stat:const.Stats, IgnoreExtraHand [MM7+] = false*/); // address: 0x482E80 | defaults: (this), 0, false
		int __thiscall calcStatBonusByMagic(/*Stat:const.Stats*/); // address: 0x483800 | defaults: (this)
		int __thiscall calcStatBonusBySkills(/*Stat:const.Stats*/); // address: 0x483930 | defaults: (this)
		int __thiscall getBaseMagicResistance(); // address: 0x482A20 | defaults: (this)
		int __thiscall getAttackDelay(/*Shoot = false*/); // address: 0x481A80 | defaults: (this), false
		int __thiscall doBadThing(/*Thing:const.MonsterBonus, Monster:structs.MapMonster[MM7+]*/); // address: 0x480010 | defaults: (this), 0, 0
		int __thiscall getMerchantTotalSkill(); // address: 0x485340 | defaults: (this)
		int __thiscall getDisarmTrapTotalSkill(); // address: 0x4853E0 | defaults: (this)
		int __thiscall getDiplomacyTotalSkill(); // address: 0x4852D0 | defaults: (this)
		int __thiscall getBaseColdResistance(); // address: 0x4829E0 | defaults: (this)
		int __thiscall getBaseIntellect(); // address: 0x47D850 | defaults: (this)
		int __thiscall resetToClass(); // address: 0x483D90 | defaults: (this)
		int __thiscall addHitPoints(); // address: 0x47FB60 | defaults: 0
		int __thiscall getBaseFireResistance(); // address: 0x4829A0 | defaults: (this)
		int __thiscall getBaseElectricityResistance(); // address: 0x4829C0 | defaults: (this)
		int __thiscall showFaceExpression(/*Expression, Time = 0*/); // address: 0x488F50 | defaults: (this), 0, 0
		int __thiscall getBasePoisonResistance(); // address: 0x482A00 | defaults: (this)
		int __thiscall showFaceAnimation(/*Animation:const.FaceAnimation*/); // address: 0x488CA0 | defaults: (this), 0, 0
		int __thiscall getFireResistance(); // address: 0x482A40 | defaults: (this)
		int __thiscall getElectricityResistance(); // address: 0x482A90 | defaults: (this)
		int __thiscall getColdResistance(); // address: 0x482AE0 | defaults: (this)
		int __thiscall getPoisonResistance(); // address: 0x482B30 | defaults: (this)
		int __thiscall getMagicResistance(); // address: 0x482B80 | defaults: (this)
	};
	static_assert(sizeof(mm6::Player) == 0x161C, "Invalid \"mm6::Player\" structure size");
	static_assert(offsetof(mm6::Player, name) == 1);
	static_assert(offsetof(mm6::Player, sex) == 17);
	static_assert(offsetof(mm6::Player, clas) == 18);
	static_assert(offsetof(mm6::Player, stats) == 20);
	static_assert(offsetof(mm6::Player, mightBase) == 20);
	static_assert(offsetof(mm6::Player, mightBonus) == 22);
	static_assert(offsetof(mm6::Player, intellectBase) == 24);
	static_assert(offsetof(mm6::Player, intellectBonus) == 26);
	static_assert(offsetof(mm6::Player, personalityBase) == 28);
	static_assert(offsetof(mm6::Player, personalityBonus) == 30);
	static_assert(offsetof(mm6::Player, enduranceBase) == 32);
	static_assert(offsetof(mm6::Player, enduranceBonus) == 34);
	static_assert(offsetof(mm6::Player, speedBase) == 36);
	static_assert(offsetof(mm6::Player, speedBonus) == 38);
	static_assert(offsetof(mm6::Player, accuracyBase) == 40);
	static_assert(offsetof(mm6::Player, accuracyBonus) == 42);
	static_assert(offsetof(mm6::Player, luckBase) == 44);
	static_assert(offsetof(mm6::Player, luckBonus) == 46);
	static_assert(offsetof(mm6::Player, armorClassBonus) == 48);
	static_assert(offsetof(mm6::Player, levelBase) == 50);
	static_assert(offsetof(mm6::Player, levelBonus) == 52);
	static_assert(offsetof(mm6::Player, ageBonus) == 54);
	static_assert(offsetof(mm6::Player, skills) == 96);
	static_assert(offsetof(mm6::Player, spells) == 191);
	static_assert(offsetof(mm6::Player, usedBlackPotions) == 296);
	static_assert(offsetof(mm6::Player, items) == 324);
	static_assert(offsetof(mm6::Player, inventory) == 4188);
	static_assert(offsetof(mm6::Player, resistances) == 4692);
	static_assert(offsetof(mm6::Player, fireResistanceBase) == 4692);
	static_assert(offsetof(mm6::Player, fireResistanceBonus) == 4694);
	static_assert(offsetof(mm6::Player, coldResistanceBase) == 4696);
	static_assert(offsetof(mm6::Player, coldResistanceBonus) == 4698);
	static_assert(offsetof(mm6::Player, elecResistanceBase) == 4700);
	static_assert(offsetof(mm6::Player, elecResistanceBonus) == 4702);
	static_assert(offsetof(mm6::Player, poisonResistanceBase) == 4704);
	static_assert(offsetof(mm6::Player, poisonResistanceBonus) == 4706);
	static_assert(offsetof(mm6::Player, magicResistanceBase) == 4708);
	static_assert(offsetof(mm6::Player, magicResistanceBonus) == 4710);
	static_assert(offsetof(mm6::Player, spellBuffs) == 4712);
	static_assert(offsetof(mm6::Player, recoveryDelay) == 4988);
	static_assert(offsetof(mm6::Player, attackSpell) == 4990);
	static_assert(offsetof(mm6::Player, conditions) == 4992);
	static_assert(offsetof(mm6::Player, cursed) == 4992);
	static_assert(offsetof(mm6::Player, weak) == 5000);
	static_assert(offsetof(mm6::Player, asleep) == 5008);
	static_assert(offsetof(mm6::Player, afraid) == 5016);
	static_assert(offsetof(mm6::Player, drunk) == 5024);
	static_assert(offsetof(mm6::Player, insane) == 5032);
	static_assert(offsetof(mm6::Player, poison1) == 5040);
	static_assert(offsetof(mm6::Player, disease1) == 5048);
	static_assert(offsetof(mm6::Player, poison2) == 5056);
	static_assert(offsetof(mm6::Player, disease2) == 5064);
	static_assert(offsetof(mm6::Player, poison3) == 5072);
	static_assert(offsetof(mm6::Player, disease3) == 5080);
	static_assert(offsetof(mm6::Player, paralyzed) == 5088);
	static_assert(offsetof(mm6::Player, unconscious) == 5096);
	static_assert(offsetof(mm6::Player, dead) == 5104);
	static_assert(offsetof(mm6::Player, stoned) == 5112);
	static_assert(offsetof(mm6::Player, eradicated) == 5120);
	static_assert(offsetof(mm6::Player, good) == 5128);
	static_assert(offsetof(mm6::Player, skillPoints) == 5136);
	static_assert(offsetof(mm6::Player, HP) == 5140);
	static_assert(offsetof(mm6::Player, hitPoints) == 5140);
	static_assert(offsetof(mm6::Player, SP) == 5144);
	static_assert(offsetof(mm6::Player, spellPoints) == 5144);
	static_assert(offsetof(mm6::Player, birthYear) == 5148);
	static_assert(offsetof(mm6::Player, exp) == 5152);
	static_assert(offsetof(mm6::Player, experience) == 5152);
	static_assert(offsetof(mm6::Player, equippedItems) == 5160);
	static_assert(offsetof(mm6::Player, itemExtraHand) == 5160);
	static_assert(offsetof(mm6::Player, itemMainHand) == 5164);
	static_assert(offsetof(mm6::Player, itemBow) == 5168);
	static_assert(offsetof(mm6::Player, itemArmor) == 5172);
	static_assert(offsetof(mm6::Player, itemHelm) == 5176);
	static_assert(offsetof(mm6::Player, itemBelt) == 5180);
	static_assert(offsetof(mm6::Player, itemCloak) == 5184);
	static_assert(offsetof(mm6::Player, itemGauntlets) == 5188);
	static_assert(offsetof(mm6::Player, itemGountlets) == 5188);
	static_assert(offsetof(mm6::Player, itemBoots) == 5192);
	static_assert(offsetof(mm6::Player, itemAmulet) == 5196);
	static_assert(offsetof(mm6::Player, itemRing1) == 5200);
	static_assert(offsetof(mm6::Player, itemRing2) == 5204);
	static_assert(offsetof(mm6::Player, itemRing3) == 5208);
	static_assert(offsetof(mm6::Player, itemRing4) == 5212);
	static_assert(offsetof(mm6::Player, itemRing5) == 5216);
	static_assert(offsetof(mm6::Player, itemRing6) == 5220);
	static_assert(offsetof(mm6::Player, spellBookPage) == 5422);
	static_assert(offsetof(mm6::Player, quickSpell) == 5423);
	static_assert(offsetof(mm6::Player, meleeAttackBonus) == 5488);
	static_assert(offsetof(mm6::Player, meleeDamageBonus) == 5490);
	static_assert(offsetof(mm6::Player, rangedAttackBonus) == 5492);
	static_assert(offsetof(mm6::Player, rangedDamageBonus) == 5494);
	static_assert(offsetof(mm6::Player, fullHPBonus) == 5496);
	static_assert(offsetof(mm6::Player, fullHitPointsBonus) == 5496);
	static_assert(offsetof(mm6::Player, fullSPBonus) == 5498);
	static_assert(offsetof(mm6::Player, fullSpellPointsBonus) == 5498);
	static_assert(offsetof(mm6::Player, expression) == 5500);
	static_assert(offsetof(mm6::Player, expressionTimePassed) == 5502);
	static_assert(offsetof(mm6::Player, expressionLength) == 5504);
	static_assert(offsetof(mm6::Player, beacons) == 5516);
	static_assert(offsetof(mm6::Player, devineInterventionCasts) == 5656);
	static_assert(offsetof(mm6::Player, armageddonCasts) == 5657);
}
namespace mm7
{
	struct FaceAnimationInfo // size: 0x8
	{
		union
		{
			std::array<uint8_t, 2> sounds; // MMExt: 1..2, here 0..1 | 0x0 (0 decimal)
			struct
			{
				uint8_t sound1; // 0x0 (0 decimal)
				uint8_t sound2; // 0x1 (1 decimal)
			};
		};
		SKIP(1);
		union
		{
			std::array<uint8_t, 5> expressions; // MMExt: 1..5, here 0..4 | 0x3 (3 decimal)
			struct
			{
				uint8_t expression1; // 0x3 (3 decimal)
				uint8_t expression2; // 0x4 (4 decimal)
				uint8_t expression3; // 0x5 (5 decimal)
				uint8_t expression4; // 0x6 (6 decimal)
				uint8_t expression5; // 0x7 (7 decimal)
			};
		};
	};
	static_assert(sizeof(mm7::FaceAnimationInfo) == 0x8, "Invalid \"mm7::FaceAnimationInfo\" structure size");
	static_assert(offsetof(mm7::FaceAnimationInfo, sound2) == 1);
	static_assert(offsetof(mm7::FaceAnimationInfo, expressions) == 3);
	static_assert(offsetof(mm7::FaceAnimationInfo, expression1) == 3);
	static_assert(offsetof(mm7::FaceAnimationInfo, expression2) == 4);
	static_assert(offsetof(mm7::FaceAnimationInfo, expression3) == 5);
	static_assert(offsetof(mm7::FaceAnimationInfo, expression4) == 6);
	static_assert(offsetof(mm7::FaceAnimationInfo, expression5) == 7);



	struct BaseBonus // size: 0x4
	{
		int16_t base; // 0x0 (0 decimal)
		int16_t bonus; // 0x2 (2 decimal)
	};
	static_assert(sizeof(mm7::BaseBonus) == 0x4, "Invalid \"mm7::BaseBonus\" structure size");
	static_assert(offsetof(mm7::BaseBonus, bonus) == 2);



	struct LloydBeaconSlot // size: 0x1C
	{
		int64_t expireTime; // 0x0 (0 decimal)
		union
		{
			std::array<int32_t, 3> pos; // 0x8 (8 decimal)
			struct
			{
				int32_t x; // 0x8 (8 decimal)
				int32_t y; // 0xC (12 decimal)
				int32_t z; // 0x10 (16 decimal)
			};
		};
		int16_t direction; // 0x14 (20 decimal)
		int16_t lookAngle; // 0x16 (22 decimal)
		int16_t active; // 0x18 (24 decimal)
		union
		{
			std::array<uint8_t, 2> map; // Unknown type | 0x1A (26 decimal)
			int16_t mapIndex; // 0x1A (26 decimal)
		};
	};
	static_assert(sizeof(mm7::LloydBeaconSlot) == 0x1C, "Invalid \"mm7::LloydBeaconSlot\" structure size");
	static_assert(offsetof(mm7::LloydBeaconSlot, pos) == 8);
	static_assert(offsetof(mm7::LloydBeaconSlot, x) == 8);
	static_assert(offsetof(mm7::LloydBeaconSlot, y) == 12);
	static_assert(offsetof(mm7::LloydBeaconSlot, z) == 16);
	static_assert(offsetof(mm7::LloydBeaconSlot, direction) == 20);
	static_assert(offsetof(mm7::LloydBeaconSlot, lookAngle) == 22);
	static_assert(offsetof(mm7::LloydBeaconSlot, active) == 24);
	static_assert(offsetof(mm7::LloydBeaconSlot, map) == 26);
	static_assert(offsetof(mm7::LloydBeaconSlot, mapIndex) == 26);



	struct Player // size: 0x1B3C
	{
		union
		{
			std::array<int64_t, 20> conditions; // 0x0 (0 decimal)
			struct
			{
				int64_t cursed; // 0x0 (0 decimal)
				int64_t weak; // 0x8 (8 decimal)
				int64_t asleep; // 0x10 (16 decimal)
				int64_t afraid; // 0x18 (24 decimal)
				int64_t drunk; // 0x20 (32 decimal)
				int64_t insane; // 0x28 (40 decimal)
				int64_t poison1; // 0x30 (48 decimal)
				int64_t disease1; // 0x38 (56 decimal)
				int64_t poison2; // 0x40 (64 decimal)
				int64_t disease2; // 0x48 (72 decimal)
				int64_t poison3; // 0x50 (80 decimal)
				int64_t disease3; // 0x58 (88 decimal)
				int64_t paralyzed; // 0x60 (96 decimal)
				int64_t unconscious; // 0x68 (104 decimal)
				int64_t dead; // 0x70 (112 decimal)
				int64_t stoned; // 0x78 (120 decimal)
				int64_t eradicated; // 0x80 (128 decimal)
				int64_t zombie; // 0x88 (136 decimal)
				int64_t good; // 0x90 (144 decimal)
			};
		};
		union
		{
			int64_t exp; // 0xA0 (160 decimal)
			int64_t experience; // 0xA0 (160 decimal)
		};
		std::array<char, 16> name; // fixed size string, requires null terminator | 0xA8 (168 decimal)
		bool sex; // 0xB8 (184 decimal)
		uint8_t clas; // 0xB9 (185 decimal)
		uint8_t face; // 0xBA (186 decimal)
		SKIP(1);
		union
		{
			struct // size: 0x1C, MMExt union
			{
				mm7::BaseBonus _0; // 0xBC (188 decimal)
				mm7::BaseBonus _1; // 0xC0 (192 decimal)
				mm7::BaseBonus _2; // 0xC4 (196 decimal)
				mm7::BaseBonus _3; // 0xC8 (200 decimal)
				mm7::BaseBonus _5; // 0xCC (204 decimal)
				mm7::BaseBonus _4; // 0xD0 (208 decimal)
				mm7::BaseBonus _6; // 0xD4 (212 decimal)
			} stats;
			static_assert(sizeof(stats) == 0x1C, "Invalid \"stats\" structure size");;
			struct
			{
				int16_t mightBase; // 0xBC (188 decimal)
				int16_t mightBonus; // 0xBE (190 decimal)
				int16_t intellectBase; // 0xC0 (192 decimal)
				int16_t intellectBonus; // 0xC2 (194 decimal)
				int16_t personalityBase; // 0xC4 (196 decimal)
				int16_t personalityBonus; // 0xC6 (198 decimal)
				int16_t enduranceBase; // 0xC8 (200 decimal)
				int16_t enduranceBonus; // 0xCA (202 decimal)
				int16_t speedBase; // 0xCC (204 decimal)
				int16_t speedBonus; // 0xCE (206 decimal)
				int16_t accuracyBase; // 0xD0 (208 decimal)
				int16_t accuracyBonus; // 0xD2 (210 decimal)
				int16_t luckBase; // 0xD4 (212 decimal)
				int16_t luckBonus; // 0xD6 (214 decimal)
			};
		};
		int16_t armorClassBonus; // 0xD8 (216 decimal)
		int16_t levelBase; // 0xDA (218 decimal)
		int16_t levelBonus; // 0xDC (220 decimal)
		int16_t ageBonus; // 0xDE (222 decimal)
		SKIP(40);
		std::array<int16_t, 37> skills; // 0x108 (264 decimal)
		std::array<uint8_t, 13> awards; // MMExt: 1..104, here 0..103 | array of abits (real index = 7 - usual) | 0x152 (338 decimal)
		SKIP(51);
		std::array<bool, 100> spells; // MMExt: 1..100, here 0..99 | 0x192 (402 decimal)
		SKIP(2);
		std::array<uint32_t, 7> usedBlackPotions; // MMExt: 264..270, here 0..6 | 4-byte boolean | 0x1F8 (504 decimal)
		std::array<mm7::Item, 138> items; // MMExt: 1..138, here 0..137 | 0x214 (532 decimal)
		std::array<int32_t, 126> inventory; // 0x157C (5500 decimal) | MMExt info: ('Items' index) for main item cell,  -(1 + main 'Inventory' cell index) for other cells
		union
		{
			std::array<int16_t, 11> resistanceBase; // 0x1774 (6004 decimal)
			struct
			{
				int16_t fireResistanceBase; // 0x1774 (6004 decimal)
				int16_t airResistanceBase; // 0x1776 (6006 decimal)
				int16_t waterResistanceBase; // 0x1778 (6008 decimal)
				int16_t earthResistanceBase; // 0x177A (6010 decimal)
				SKIP(4);
				int16_t spiritResistanceBase; // 0x1780 (6016 decimal)
				int16_t mindResistanceBase; // 0x1782 (6018 decimal)
				int16_t bodyResistanceBase; // 0x1784 (6020 decimal)
				int16_t lightResistanceBase; // 0x1786 (6022 decimal)
				int16_t darkResistanceBase; // 0x1788 (6024 decimal)
			};
		};
		union
		{
			std::array<int16_t, 11> resistanceBonus; // 0x178A (6026 decimal)
			struct
			{
				int16_t fireResistanceBonus; // 0x178A (6026 decimal)
				int16_t airResistanceBonus; // 0x178C (6028 decimal)
				int16_t waterResistanceBonus; // 0x178E (6030 decimal)
				int16_t earthResistanceBonus; // 0x1790 (6032 decimal)
				SKIP(4);
				int16_t spiritResistanceBonus; // 0x1796 (6038 decimal)
				int16_t mindResistanceBonus; // 0x1798 (6040 decimal)
				int16_t bodyResistanceBonus; // 0x179A (6042 decimal)
				int16_t lightResistanceBonus; // 0x179C (6044 decimal)
				int16_t darkResistanceBonus; // 0x179E (6046 decimal)
			};
		};
		std::array<mm7::SpellBuff, 24> spellBuffs; // 0x17A0 (6048 decimal)
		int32_t voice; // 0x1920 (6432 decimal)
		union
		{
			int32_t faceBeforeZombie; // 0x1924 (6436 decimal)
			int32_t originalFace; // 0x1924 (6436 decimal)
		};
		union
		{
			int32_t originalVoice; // 0x1928 (6440 decimal)
			int32_t voiceBeforeZombie; // 0x1928 (6440 decimal)
		};
		SKIP(8);
		int16_t recoveryDelay; // 0x1934 (6452 decimal)
		uint8_t attackSpell; // 0x1936 (6454 decimal) | MMExt info: Added in version 2.5 of my patches
		SKIP(1);
		int32_t skillPoints; // 0x1938 (6456 decimal)
		union
		{
			int32_t HP; // 0x193C (6460 decimal)
			int32_t hitPoints; // 0x193C (6460 decimal)
		};
		union
		{
			int32_t SP; // 0x1940 (6464 decimal)
			int32_t spellPoints; // 0x1940 (6464 decimal)
		};
		int32_t birthYear; // 0x1944 (6468 decimal)
		union
		{
			std::array<int32_t, 16> equippedItems; // 0x1948 (6472 decimal)
			struct
			{
				int32_t itemExtraHand; // 0x1948 (6472 decimal)
				int32_t itemMainHand; // 0x194C (6476 decimal)
				int32_t itemBow; // 0x1950 (6480 decimal)
				int32_t itemArmor; // 0x1954 (6484 decimal)
				int32_t itemHelm; // 0x1958 (6488 decimal)
				int32_t itemBelt; // 0x195C (6492 decimal)
				int32_t itemCloak; // 0x1960 (6496 decimal)
				union
				{
					int32_t itemGauntlets; // 0x1964 (6500 decimal) | MMExt info: Was called 'ItemGountlets' before MMExtension v2.3, old name is supported for backward compatibility
					int32_t itemGountlets; // 0x1964 (6500 decimal)
				};
				int32_t itemBoots; // 0x1968 (6504 decimal)
				int32_t itemAmulet; // 0x196C (6508 decimal)
				int32_t itemRing1; // 0x1970 (6512 decimal)
				int32_t itemRing2; // 0x1974 (6516 decimal)
				int32_t itemRing3; // 0x1978 (6520 decimal)
				int32_t itemRing4; // 0x197C (6524 decimal)
				int32_t itemRing5; // 0x1980 (6528 decimal)
				int32_t itemRing6; // 0x1984 (6532 decimal)
			};
		};
		SKIP(198);
		int8_t spellBookPage; // 0x1A4E (6734 decimal)
		uint8_t quickSpell; // 0x1A4F (6735 decimal)
		std::array<uint8_t, 64> playerBits; // MMExt: 1..512, here 0..511 | array of abits (real index = 7 - usual) | 0x1A50 (6736 decimal)
		int8_t meleeAttackBonus; // 0x1A90 (6800 decimal)
		SKIP(1);
		int8_t meleeDamageBonus; // 0x1A92 (6802 decimal)
		SKIP(1);
		int8_t rangedAttackBonus; // 0x1A94 (6804 decimal)
		SKIP(1);
		int8_t rangedDamageBonus; // 0x1A96 (6806 decimal)
		SKIP(1);
		union
		{
			int8_t fullHPBonus; // 0x1A98 (6808 decimal)
			int8_t fullHitPointsBonus; // 0x1A98 (6808 decimal)
		};
		SKIP(1);
		union
		{
			int8_t fullSPBonus; // 0x1A9A (6810 decimal)
			int8_t fullSpellPointsBonus; // 0x1A9A (6810 decimal)
		};
		SKIP(1);
		int16_t expression; // 0x1A9C (6812 decimal)
		int16_t expressionTimePassed; // 0x1A9E (6814 decimal)
		int16_t expressionLength; // 0x1AA0 (6816 decimal)
		SKIP(10);
		std::array<mm7::LloydBeaconSlot, 5> beacons; // 0x1AAC (6828 decimal)
		uint8_t devineInterventionCasts; // 0x1B38 (6968 decimal)
		uint8_t armageddonCasts; // 0x1B39 (6969 decimal)
		SKIP(2);
		int __thiscall recover(/*ByAmount*/); // address: 0x48E8ED | defaults: (this)
		char* __thiscall getMeleeDamageRangeText(); // address: 0x48D2D0 | defaults: (this)
		char* __thiscall getRangedDamageRangeText(); // address: 0x48D37C | defaults: (this)
		int __thiscall canTrain(); // address: 0x48D440 | defaults: (this)
		int __thiscall showFaceExpression(/*Expression, Time = 0*/); // address: 0x494A1D | defaults: (this), 0, 0
		int __thiscall doDamage(/*Damage, DamageKind:const.Damage = const.Damage.Phys*/); // address: 0x48DC04 | defaults: (this), 0, 4
		int __thiscall showFaceAnimation(/*Animation:const.FaceAnimation*/); // address: 0x4948A9 | defaults: (this), 0, 0
		bool __thiscall wearsItem(/*ItemNum, Slot:const.ItemSlot = 16*/); // address: 0x48D6EF | defaults: (this), 0, 16
		int __thiscall doBadThing(/*Thing:const.MonsterBonus, Monster:structs.MapMonster[MM7+]*/); // address: 0x48DCDC | defaults: (this), 0, 0
		int __thiscall addCondition(/*Condition:const.Condition, CanResist = false*/); // address: 0x492D5D | defaults: (this), 0, false
		int __thiscall getSex(/*BasedOnVoice[MM8] = false*/); // address: 0x490139 | defaults: (this)
		int __thiscall getFullHP(); // address: 0x48E4F0 | defaults: (this)
		int __thiscall getMainCondition(); // address: 0x48E9EC | defaults: (this)
		int __thiscall addHitPoints(); // address: 0x48DB9F | defaults: 0
		int __thiscall getFullSP(); // address: 0x48E55D | defaults: (this)
		int __thiscall resetToClass(); // address: 0x490242 | defaults: (this)
		int __thiscall getBaseMight(); // address: 0x48C83B | defaults: (this)
		int __thiscall getBasePersonality(); // address: 0x48C869 | defaults: (this)
		int __thiscall getBaseEndurance(); // address: 0x48C880 | defaults: (this)
		int __thiscall calcMeleeDamage(/*JustWeaponDamage = false, IgnoreExtraHand = false, MonsterId = -1*/); // address: 0x48CDC1 | defaults: (this), false, false, -1
		int __thiscall calcRangedDamage(/*MonsterId = -1*/); // address: 0x48D1E4 | defaults: (this), -1
		bool __stdcall calcHitOrMiss(/*Monster:structs.MapMonster, Range = 0, Bonus = 0*/); // address: 0x4272AC | defaults: (this), 0, 0, 0
		int __thiscall addHP(/*Amount*/); // address: 0x48DB9F | defaults: (this)
		int __thiscall getRangedDamageMin(); // address: 0x48D10A | defaults: (this)
		int __thiscall getLearningTotalSkill(); // address: 0x49130F | defaults: (this)
		int __thiscall getPerceptionTotalSkill(); // address: 0x491252 | defaults: (this)
		int __thiscall getMerchantTotalSkill(); // address: 0x4911EB | defaults: (this)
		int __thiscall calcStatBonusByItems(/*Stat:const.Stats, IgnoreExtraHand [MM7+] = false*/); // address: 0x48EAA6 | defaults: (this), 0, false
		int __thiscall calcStatBonusByMagic(/*Stat:const.Stats*/); // address: 0x48F734 | defaults: (this)
		int __thiscall calcStatBonusBySkills(/*Stat:const.Stats*/); // address: 0x48FBF8 | defaults: (this)
		int __thiscall getSkill(/*Skill:const.Skills*/); // address: 0x48F87A | defaults: (this)
		int __thiscall getAttackDelay(/*Shoot = false*/); // address: 0x48E19B | defaults: (this), false
		int __thiscall getFullHitPoints(); // address: 0x48E4F0 | defaults: 0
		int __thiscall getFullSpellPoints(); // address: 0x48E55D | defaults: 0
		int __thiscall getDisarmTrapTotalSkill(); // address: 0x4912A8 | defaults: (this)
		int __thiscall getMeleeDamageMin(); // address: 0x48CD2B | defaults: (this)
		int __thiscall getMeleeDamageMax(); // address: 0x48CD76 | defaults: (this)
		bool __thiscall isConscious(); // address: 0x492C03 | defaults: (this)
		int __thiscall getRangedDamageMax(); // address: 0x48D177 | defaults: (this)
		int __thiscall getBaseResistance(/*Res:const.Damage*/); // address: 0x48E737 | defaults: (this)
		int __thiscall getBaseIntellect(); // address: 0x48C852 | defaults: (this)
		int __thiscall getResistance(/*Res:const.Damage*/); // address: 0x48E7C8 | defaults: (this)
		int __thiscall hasItemBonus(/*Bonus2*/); // address: 0x48D6B6 | defaults: (this)
		int __thiscall getBaseAccuracy(); // address: 0x48C897 | defaults: (this)
		int __thiscall getBaseSpeed(); // address: 0x48C8AE | defaults: (this)
		int __thiscall getBaseLuck(); // address: 0x48C8C5 | defaults: (this)
		int __thiscall getBaseLevel(); // address: 0x48C8DC | defaults: (this)
		int __thiscall getLevel(); // address: 0x48C8F3 | defaults: (this)
		int __thiscall getMight(); // address: 0x48C922 | defaults: (this)
		int __thiscall getIntellect(); // address: 0x48C9A8 | defaults: (this)
		int __thiscall getPersonality(); // address: 0x48CA25 | defaults: (this)
		int __thiscall getEndurance(); // address: 0x48CAA2 | defaults: (this)
		int __thiscall getAccuracy(); // address: 0x48CB1F | defaults: (this)
		int __thiscall getSpeed(); // address: 0x48CB9C | defaults: (this)
		int __thiscall getLuck(); // address: 0x48CC19 | defaults: (this)
		int __thiscall getMeleeAttack(/*IgnoreExtraHand [MM7+] = false*/); // address: 0x48CCDB | defaults: (this), false
		int __thiscall setRecoveryDelayRaw(/*Delay*/); // address: 0x48E962 | defaults: (this)
		int __thiscall removeFromInventory(/*Slot*/); // address: 0x492A2E | defaults: (this)
		int __thiscall getRace(); // address: 0x490101 | defaults: (this)
		int __thiscall getRangedAttack(); // address: 0x48D09F | defaults: (this)
		int __thiscall getBaseArmorClass(); // address: 0x48E64E | defaults: (this)
		int __thiscall getArmorClass(); // address: 0x48E687 | defaults: (this)
		int __thiscall getBaseAge(); // address: 0x48E6D4 | defaults: (this)
		int __thiscall getAge(); // address: 0x48E724 | defaults: (this)
	};
	static_assert(sizeof(mm7::Player) == 0x1B3C, "Invalid \"mm7::Player\" structure size");
	static_assert(offsetof(mm7::Player, weak) == 8);
	static_assert(offsetof(mm7::Player, asleep) == 16);
	static_assert(offsetof(mm7::Player, afraid) == 24);
	static_assert(offsetof(mm7::Player, drunk) == 32);
	static_assert(offsetof(mm7::Player, insane) == 40);
	static_assert(offsetof(mm7::Player, poison1) == 48);
	static_assert(offsetof(mm7::Player, disease1) == 56);
	static_assert(offsetof(mm7::Player, poison2) == 64);
	static_assert(offsetof(mm7::Player, disease2) == 72);
	static_assert(offsetof(mm7::Player, poison3) == 80);
	static_assert(offsetof(mm7::Player, disease3) == 88);
	static_assert(offsetof(mm7::Player, paralyzed) == 96);
	static_assert(offsetof(mm7::Player, unconscious) == 104);
	static_assert(offsetof(mm7::Player, dead) == 112);
	static_assert(offsetof(mm7::Player, stoned) == 120);
	static_assert(offsetof(mm7::Player, eradicated) == 128);
	static_assert(offsetof(mm7::Player, zombie) == 136);
	static_assert(offsetof(mm7::Player, good) == 144);
	static_assert(offsetof(mm7::Player, exp) == 160);
	static_assert(offsetof(mm7::Player, experience) == 160);
	static_assert(offsetof(mm7::Player, name) == 168);
	static_assert(offsetof(mm7::Player, sex) == 184);
	static_assert(offsetof(mm7::Player, clas) == 185);
	static_assert(offsetof(mm7::Player, face) == 186);
	static_assert(offsetof(mm7::Player, stats) == 188);
	static_assert(offsetof(mm7::Player, mightBase) == 188);
	static_assert(offsetof(mm7::Player, mightBonus) == 190);
	static_assert(offsetof(mm7::Player, intellectBase) == 192);
	static_assert(offsetof(mm7::Player, intellectBonus) == 194);
	static_assert(offsetof(mm7::Player, personalityBase) == 196);
	static_assert(offsetof(mm7::Player, personalityBonus) == 198);
	static_assert(offsetof(mm7::Player, enduranceBase) == 200);
	static_assert(offsetof(mm7::Player, enduranceBonus) == 202);
	static_assert(offsetof(mm7::Player, speedBase) == 204);
	static_assert(offsetof(mm7::Player, speedBonus) == 206);
	static_assert(offsetof(mm7::Player, accuracyBase) == 208);
	static_assert(offsetof(mm7::Player, accuracyBonus) == 210);
	static_assert(offsetof(mm7::Player, luckBase) == 212);
	static_assert(offsetof(mm7::Player, luckBonus) == 214);
	static_assert(offsetof(mm7::Player, armorClassBonus) == 216);
	static_assert(offsetof(mm7::Player, levelBase) == 218);
	static_assert(offsetof(mm7::Player, levelBonus) == 220);
	static_assert(offsetof(mm7::Player, ageBonus) == 222);
	static_assert(offsetof(mm7::Player, skills) == 264);
	static_assert(offsetof(mm7::Player, spells) == 402);
	static_assert(offsetof(mm7::Player, usedBlackPotions) == 504);
	static_assert(offsetof(mm7::Player, items) == 532);
	static_assert(offsetof(mm7::Player, inventory) == 5500);
	static_assert(offsetof(mm7::Player, resistanceBase) == 6004);
	static_assert(offsetof(mm7::Player, fireResistanceBase) == 6004);
	static_assert(offsetof(mm7::Player, airResistanceBase) == 6006);
	static_assert(offsetof(mm7::Player, waterResistanceBase) == 6008);
	static_assert(offsetof(mm7::Player, earthResistanceBase) == 6010);
	static_assert(offsetof(mm7::Player, spiritResistanceBase) == 6016);
	static_assert(offsetof(mm7::Player, mindResistanceBase) == 6018);
	static_assert(offsetof(mm7::Player, bodyResistanceBase) == 6020);
	static_assert(offsetof(mm7::Player, lightResistanceBase) == 6022);
	static_assert(offsetof(mm7::Player, darkResistanceBase) == 6024);
	static_assert(offsetof(mm7::Player, resistanceBonus) == 6026);
	static_assert(offsetof(mm7::Player, fireResistanceBonus) == 6026);
	static_assert(offsetof(mm7::Player, airResistanceBonus) == 6028);
	static_assert(offsetof(mm7::Player, waterResistanceBonus) == 6030);
	static_assert(offsetof(mm7::Player, earthResistanceBonus) == 6032);
	static_assert(offsetof(mm7::Player, spiritResistanceBonus) == 6038);
	static_assert(offsetof(mm7::Player, mindResistanceBonus) == 6040);
	static_assert(offsetof(mm7::Player, bodyResistanceBonus) == 6042);
	static_assert(offsetof(mm7::Player, lightResistanceBonus) == 6044);
	static_assert(offsetof(mm7::Player, darkResistanceBonus) == 6046);
	static_assert(offsetof(mm7::Player, spellBuffs) == 6048);
	static_assert(offsetof(mm7::Player, voice) == 6432);
	static_assert(offsetof(mm7::Player, faceBeforeZombie) == 6436);
	static_assert(offsetof(mm7::Player, originalFace) == 6436);
	static_assert(offsetof(mm7::Player, originalVoice) == 6440);
	static_assert(offsetof(mm7::Player, voiceBeforeZombie) == 6440);
	static_assert(offsetof(mm7::Player, recoveryDelay) == 6452);
	static_assert(offsetof(mm7::Player, attackSpell) == 6454);
	static_assert(offsetof(mm7::Player, skillPoints) == 6456);
	static_assert(offsetof(mm7::Player, HP) == 6460);
	static_assert(offsetof(mm7::Player, hitPoints) == 6460);
	static_assert(offsetof(mm7::Player, SP) == 6464);
	static_assert(offsetof(mm7::Player, spellPoints) == 6464);
	static_assert(offsetof(mm7::Player, birthYear) == 6468);
	static_assert(offsetof(mm7::Player, equippedItems) == 6472);
	static_assert(offsetof(mm7::Player, itemExtraHand) == 6472);
	static_assert(offsetof(mm7::Player, itemMainHand) == 6476);
	static_assert(offsetof(mm7::Player, itemBow) == 6480);
	static_assert(offsetof(mm7::Player, itemArmor) == 6484);
	static_assert(offsetof(mm7::Player, itemHelm) == 6488);
	static_assert(offsetof(mm7::Player, itemBelt) == 6492);
	static_assert(offsetof(mm7::Player, itemCloak) == 6496);
	static_assert(offsetof(mm7::Player, itemGauntlets) == 6500);
	static_assert(offsetof(mm7::Player, itemGountlets) == 6500);
	static_assert(offsetof(mm7::Player, itemBoots) == 6504);
	static_assert(offsetof(mm7::Player, itemAmulet) == 6508);
	static_assert(offsetof(mm7::Player, itemRing1) == 6512);
	static_assert(offsetof(mm7::Player, itemRing2) == 6516);
	static_assert(offsetof(mm7::Player, itemRing3) == 6520);
	static_assert(offsetof(mm7::Player, itemRing4) == 6524);
	static_assert(offsetof(mm7::Player, itemRing5) == 6528);
	static_assert(offsetof(mm7::Player, itemRing6) == 6532);
	static_assert(offsetof(mm7::Player, spellBookPage) == 6734);
	static_assert(offsetof(mm7::Player, quickSpell) == 6735);
	static_assert(offsetof(mm7::Player, meleeAttackBonus) == 6800);
	static_assert(offsetof(mm7::Player, meleeDamageBonus) == 6802);
	static_assert(offsetof(mm7::Player, rangedAttackBonus) == 6804);
	static_assert(offsetof(mm7::Player, rangedDamageBonus) == 6806);
	static_assert(offsetof(mm7::Player, fullHPBonus) == 6808);
	static_assert(offsetof(mm7::Player, fullHitPointsBonus) == 6808);
	static_assert(offsetof(mm7::Player, fullSPBonus) == 6810);
	static_assert(offsetof(mm7::Player, fullSpellPointsBonus) == 6810);
	static_assert(offsetof(mm7::Player, expression) == 6812);
	static_assert(offsetof(mm7::Player, expressionTimePassed) == 6814);
	static_assert(offsetof(mm7::Player, expressionLength) == 6816);
	static_assert(offsetof(mm7::Player, beacons) == 6828);
	static_assert(offsetof(mm7::Player, devineInterventionCasts) == 6968);
	static_assert(offsetof(mm7::Player, armageddonCasts) == 6969);
}
namespace mm8
{
	struct FaceAnimationInfo // size: 0x8
	{
		union
		{
			std::array<uint8_t, 2> sounds; // MMExt: 1..2, here 0..1 | 0x0 (0 decimal)
			struct
			{
				uint8_t sound1; // 0x0 (0 decimal)
				uint8_t sound2; // 0x1 (1 decimal)
			};
		};
		SKIP(1);
		union
		{
			std::array<uint8_t, 5> expressions; // MMExt: 1..5, here 0..4 | 0x3 (3 decimal)
			struct
			{
				uint8_t expression1; // 0x3 (3 decimal)
				uint8_t expression2; // 0x4 (4 decimal)
				uint8_t expression3; // 0x5 (5 decimal)
				uint8_t expression4; // 0x6 (6 decimal)
				uint8_t expression5; // 0x7 (7 decimal)
			};
		};
	};
	static_assert(sizeof(mm8::FaceAnimationInfo) == 0x8, "Invalid \"mm8::FaceAnimationInfo\" structure size");
	static_assert(offsetof(mm8::FaceAnimationInfo, sound2) == 1);
	static_assert(offsetof(mm8::FaceAnimationInfo, expressions) == 3);
	static_assert(offsetof(mm8::FaceAnimationInfo, expression1) == 3);
	static_assert(offsetof(mm8::FaceAnimationInfo, expression2) == 4);
	static_assert(offsetof(mm8::FaceAnimationInfo, expression3) == 5);
	static_assert(offsetof(mm8::FaceAnimationInfo, expression4) == 6);
	static_assert(offsetof(mm8::FaceAnimationInfo, expression5) == 7);



	struct BaseBonus // size: 0x4
	{
		int16_t base; // 0x0 (0 decimal)
		int16_t bonus; // 0x2 (2 decimal)
	};
	static_assert(sizeof(mm8::BaseBonus) == 0x4, "Invalid \"mm8::BaseBonus\" structure size");
	static_assert(offsetof(mm8::BaseBonus, bonus) == 2);



	struct LloydBeaconSlot // size: 0x1C
	{
		int64_t expireTime; // 0x0 (0 decimal)
		union
		{
			std::array<int32_t, 3> pos; // 0x8 (8 decimal)
			struct
			{
				int32_t x; // 0x8 (8 decimal)
				int32_t y; // 0xC (12 decimal)
				int32_t z; // 0x10 (16 decimal)
			};
		};
		int16_t direction; // 0x14 (20 decimal)
		int16_t lookAngle; // 0x16 (22 decimal)
		int16_t active; // 0x18 (24 decimal)
		union
		{
			std::array<uint8_t, 2> map; // Unknown type | 0x1A (26 decimal)
			int16_t mapIndex; // 0x1A (26 decimal)
		};
	};
	static_assert(sizeof(mm8::LloydBeaconSlot) == 0x1C, "Invalid \"mm8::LloydBeaconSlot\" structure size");
	static_assert(offsetof(mm8::LloydBeaconSlot, pos) == 8);
	static_assert(offsetof(mm8::LloydBeaconSlot, x) == 8);
	static_assert(offsetof(mm8::LloydBeaconSlot, y) == 12);
	static_assert(offsetof(mm8::LloydBeaconSlot, z) == 16);
	static_assert(offsetof(mm8::LloydBeaconSlot, direction) == 20);
	static_assert(offsetof(mm8::LloydBeaconSlot, lookAngle) == 22);
	static_assert(offsetof(mm8::LloydBeaconSlot, active) == 24);
	static_assert(offsetof(mm8::LloydBeaconSlot, map) == 26);
	static_assert(offsetof(mm8::LloydBeaconSlot, mapIndex) == 26);



	struct Player // size: 0x1D28
	{
		union
		{
			std::array<int64_t, 20> conditions; // 0x0 (0 decimal)
			struct
			{
				int64_t cursed; // 0x0 (0 decimal)
				int64_t weak; // 0x8 (8 decimal)
				int64_t asleep; // 0x10 (16 decimal)
				int64_t afraid; // 0x18 (24 decimal)
				int64_t drunk; // 0x20 (32 decimal)
				int64_t insane; // 0x28 (40 decimal)
				int64_t poison1; // 0x30 (48 decimal)
				int64_t disease1; // 0x38 (56 decimal)
				int64_t poison2; // 0x40 (64 decimal)
				int64_t disease2; // 0x48 (72 decimal)
				int64_t poison3; // 0x50 (80 decimal)
				int64_t disease3; // 0x58 (88 decimal)
				int64_t paralyzed; // 0x60 (96 decimal)
				int64_t unconscious; // 0x68 (104 decimal)
				int64_t dead; // 0x70 (112 decimal)
				int64_t stoned; // 0x78 (120 decimal)
				int64_t eradicated; // 0x80 (128 decimal)
				int64_t zombie; // 0x88 (136 decimal)
				int64_t good; // 0x90 (144 decimal)
			};
		};
		union
		{
			int64_t exp; // 0xA0 (160 decimal)
			int64_t experience; // 0xA0 (160 decimal)
		};
		std::array<char, 32> name; // fixed size string, requires null terminator | 0xA8 (168 decimal)
		std::array<char, 256> biography; // fixed size string, requires null terminator | 0xC8 (200 decimal)
		SKIP(394);
		uint8_t clas; // 0x352 (850 decimal)
		uint8_t face; // 0x353 (851 decimal)
		union
		{
			struct // size: 0x1C, MMExt union
			{
				mm8::BaseBonus _0; // 0x354 (852 decimal)
				mm8::BaseBonus _1; // 0x358 (856 decimal)
				mm8::BaseBonus _2; // 0x35C (860 decimal)
				mm8::BaseBonus _3; // 0x360 (864 decimal)
				mm8::BaseBonus _5; // 0x364 (868 decimal)
				mm8::BaseBonus _4; // 0x368 (872 decimal)
				mm8::BaseBonus _6; // 0x36C (876 decimal)
			} stats;
			static_assert(sizeof(stats) == 0x1C, "Invalid \"stats\" structure size");;
			struct
			{
				int16_t mightBase; // 0x354 (852 decimal)
				int16_t mightBonus; // 0x356 (854 decimal)
				int16_t intellectBase; // 0x358 (856 decimal)
				int16_t intellectBonus; // 0x35A (858 decimal)
				int16_t personalityBase; // 0x35C (860 decimal)
				int16_t personalityBonus; // 0x35E (862 decimal)
				int16_t enduranceBase; // 0x360 (864 decimal)
				int16_t enduranceBonus; // 0x362 (866 decimal)
				int16_t speedBase; // 0x364 (868 decimal)
				int16_t speedBonus; // 0x366 (870 decimal)
				int16_t accuracyBase; // 0x368 (872 decimal)
				int16_t accuracyBonus; // 0x36A (874 decimal)
				int16_t luckBase; // 0x36C (876 decimal)
				int16_t luckBonus; // 0x36E (878 decimal)
			};
		};
		int16_t armorClassBonus; // 0x370 (880 decimal)
		int16_t levelBase; // 0x372 (882 decimal)
		int16_t levelBonus; // 0x374 (884 decimal)
		int16_t ageBonus; // 0x376 (886 decimal)
		std::array<int16_t, 39> skills; // 0x378 (888 decimal)
		std::array<uint8_t, 16> awards; // MMExt: 1..135, here 0..134 | array of abits (real index = 7 - usual) | 0x3C6 (966 decimal)
		SKIP(48);
		std::array<bool, 132> spells; // MMExt: 1..132, here 0..131 | 0x406 (1030 decimal)
		SKIP(2);
		std::array<uint32_t, 7> usedBlackPotions; // MMExt: 264..270, here 0..6 | 4-byte boolean | 0x48C (1164 decimal)
		std::array<mm8::Item, 138> items; // MMExt: 1..138, here 0..137 | 0x4A8 (1192 decimal)
		std::array<int32_t, 126> inventory; // 0x1810 (6160 decimal) | MMExt info: ('Items' index) for main item cell,  -(1 + main 'Inventory' cell index) for other cells
		union
		{
			std::array<int16_t, 11> resistanceBase; // 0x1A08 (6664 decimal)
			struct
			{
				int16_t fireResistanceBase; // 0x1A08 (6664 decimal)
				int16_t airResistanceBase; // 0x1A0A (6666 decimal)
				int16_t waterResistanceBase; // 0x1A0C (6668 decimal)
				int16_t earthResistanceBase; // 0x1A0E (6670 decimal)
				SKIP(4);
				int16_t spiritResistanceBase; // 0x1A14 (6676 decimal)
				int16_t mindResistanceBase; // 0x1A16 (6678 decimal)
				int16_t bodyResistanceBase; // 0x1A18 (6680 decimal)
				int16_t lightResistanceBase; // 0x1A1A (6682 decimal)
				int16_t darkResistanceBase; // 0x1A1C (6684 decimal)
			};
		};
		union
		{
			std::array<int16_t, 11> resistanceBonus; // 0x1A1E (6686 decimal)
			struct
			{
				int16_t fireResistanceBonus; // 0x1A1E (6686 decimal)
				int16_t airResistanceBonus; // 0x1A20 (6688 decimal)
				int16_t waterResistanceBonus; // 0x1A22 (6690 decimal)
				int16_t earthResistanceBonus; // 0x1A24 (6692 decimal)
				SKIP(4);
				int16_t spiritResistanceBonus; // 0x1A2A (6698 decimal)
				int16_t mindResistanceBonus; // 0x1A2C (6700 decimal)
				int16_t bodyResistanceBonus; // 0x1A2E (6702 decimal)
				int16_t lightResistanceBonus; // 0x1A30 (6704 decimal)
				int16_t darkResistanceBonus; // 0x1A32 (6706 decimal)
			};
		};
		std::array<mm8::SpellBuff, 27> spellBuffs; // 0x1A34 (6708 decimal)
		int32_t voice; // 0x1BE4 (7140 decimal)
		SKIP(8);
		int16_t rosterBitIndex; // 0x1BF0 (7152 decimal)
		int16_t recoveryDelay; // 0x1BF2 (7154 decimal)
		int32_t skillPoints; // 0x1BF4 (7156 decimal)
		union
		{
			int32_t HP; // 0x1BF8 (7160 decimal)
			int32_t hitPoints; // 0x1BF8 (7160 decimal)
		};
		union
		{
			int32_t SP; // 0x1BFC (7164 decimal)
			int32_t spellPoints; // 0x1BFC (7164 decimal)
		};
		int32_t birthYear; // 0x1C00 (7168 decimal)
		union
		{
			std::array<int32_t, 16> equippedItems; // 0x1C04 (7172 decimal)
			struct
			{
				int32_t itemExtraHand; // 0x1C04 (7172 decimal)
				int32_t itemMainHand; // 0x1C08 (7176 decimal)
				int32_t itemBow; // 0x1C0C (7180 decimal)
				int32_t itemArmor; // 0x1C10 (7184 decimal)
				int32_t itemHelm; // 0x1C14 (7188 decimal)
				int32_t itemBelt; // 0x1C18 (7192 decimal)
				int32_t itemCloak; // 0x1C1C (7196 decimal)
				int32_t itemGountlets; // 0x1C20 (7200 decimal)
				int32_t itemBoots; // 0x1C24 (7204 decimal)
				int32_t itemAmulet; // 0x1C28 (7208 decimal)
				int32_t itemRing1; // 0x1C2C (7212 decimal)
				int32_t itemRing2; // 0x1C30 (7216 decimal)
				int32_t itemRing3; // 0x1C34 (7220 decimal)
				int32_t itemRing4; // 0x1C38 (7224 decimal)
				int32_t itemRing5; // 0x1C3C (7228 decimal)
				int32_t itemRing6; // 0x1C40 (7232 decimal)
			};
		};
		int8_t spellBookPage; // 0x1C44 (7236 decimal)
		uint8_t quickSpell; // 0x1C45 (7237 decimal)
		std::array<uint8_t, 64> playerBits; // MMExt: 1..512, here 0..511 | array of abits (real index = 7 - usual) | 0x1C46 (7238 decimal)
		int16_t expression; // 0x1C86 (7302 decimal)
		int16_t expressionTimePassed; // 0x1C88 (7304 decimal)
		int16_t expressionLength; // 0x1C8A (7306 decimal)
		SKIP(12);
		std::array<mm8::LloydBeaconSlot, 5> beacons; // 0x1C98 (7320 decimal)
		uint8_t devineInterventionCasts; // 0x1D24 (7460 decimal)
		uint8_t armageddonCasts; // 0x1D25 (7461 decimal)
		uint8_t fireSpikeCasts; // 0x1D26 (7462 decimal)
		SKIP(1);
		int __thiscall getMeleeDamageMin(); // address: 0x48C6D5 | defaults: (this)
		int __thiscall showFaceAnimation(/*Animation:const.FaceAnimation*/); // address: 0x492BCD | defaults: (this), 0, 0
		int __thiscall getIntellect(); // address: 0x48C462 | defaults: (this)
		int __thiscall getAge(); // address: 0x48DB8F | defaults: (this)
		int __thiscall getBaseResistance(/*Res:const.Damage*/); // address: 0x48DBA2 | defaults: (this)
		int __thiscall calcStatBonusBySkills(/*Stat:const.Stats*/); // address: 0x48F084 | defaults: (this)
		int __thiscall getBaseLevel(); // address: 0x48C3C0 | defaults: (this)
		int __thiscall showFaceExpression(/*Expression, Time = 0*/); // address: 0x492D6A | defaults: (this), 0, 0
		int __thiscall getFullHitPoints(); // address: 0x48D9B4 | defaults: 0
		int __thiscall doBadThing(/*Thing:const.MonsterBonus, Monster:structs.MapMonster[MM7+]*/); // address: 0x48D166 | defaults: (this), 0, 0
		int __thiscall getBaseLuck(); // address: 0x48C3A9 | defaults: (this)
		int __thiscall getRangedAttack(); // address: 0x48C9FE | defaults: (this)
		int __thiscall doDamage(/*Damage, DamageKind:const.Damage = const.Damage.Phys*/); // address: 0x48D078 | defaults: (this), 0, 4
		int __thiscall canTrain(); // address: 0x48CD4D | defaults: (this)
		int __thiscall getMerchantTotalSkill(); // address: 0x49028F | defaults: (this)
		int __thiscall getRangedDamageMin(); // address: 0x48CA37 | defaults: (this)
		int __thiscall addCondition(/*Condition:const.Condition, CanResist = false*/); // address: 0x49165D | defaults: (this), 0, false
		int __thiscall getPerceptionTotalSkill(); // address: 0x4902DF | defaults: (this)
		int __thiscall getLearningTotalSkill(); // address: 0x49036E | defaults: (this)
		int __thiscall getMainCondition(); // address: 0x48E127 | defaults: (this)
		int __thiscall getFullSP(); // address: 0x48DA18 | defaults: (this)
		int __thiscall getDisarmTrapTotalSkill(); // address: 0x49031C | defaults: (this)
		bool __stdcall calcHitOrMiss(/*Monster:structs.MapMonster, Range = 0, Bonus = 0*/); // address: 0x4256DB | defaults: (this), 0, 0, 0
		int __thiscall calcRangedDamage(/*MonsterId = -1*/); // address: 0x48CB07 | defaults: (this), -1
		int __thiscall recover(/*ByAmount*/); // address: 0x48DF81 | defaults: (this)
		int __thiscall getStartingClass(); // address: 0x48F552 | defaults: (this)
		int __thiscall getBaseIntellect(); // address: 0x48C336 | defaults: (this)
		int __thiscall calcStatBonusByItems(/*Stat:const.Stats, IgnoreExtraHand [MM7+] = false*/); // address: 0x48E213 | defaults: (this), 0, false
		bool __thiscall wearsItem(/*ItemNum, Slot:const.ItemSlot = 16*/); // address: 0x48CFC3 | defaults: (this), 0, 16
		int __thiscall getFullSpellPoints(); // address: 0x48DA18 | defaults: 0
		int __thiscall getAttackDelay(/*Shoot = false*/); // address: 0x48D62A | defaults: (this), false
		int __thiscall hasItemBonus(/*Bonus2*/); // address: 0x48CF8A | defaults: (this)
		int __thiscall calcMeleeDamage(/*JustWeaponDamage = false, IgnoreExtraHand = false, MonsterId = -1*/); // address: 0x48C759 | defaults: (this), false, false, -1
		int __thiscall getResistance(/*Res:const.Damage*/); // address: 0x48DD6B | defaults: (this)
		int __thiscall getAccuracy(); // address: 0x48C579 | defaults: (this)
		int __thiscall getBaseMight(); // address: 0x48C31F | defaults: (this)
		int __thiscall getSex(/*BasedOnVoice[MM8] = false*/); // address: 0x48F5CE | defaults: (this), false
		char* __thiscall getRangedDamageRangeText(); // address: 0x48CC98 | defaults: (this)
		int __thiscall getMeleeDamageMax(); // address: 0x48C717 | defaults: (this)
		int __thiscall getRangedDamageMax(); // address: 0x48CA9F | defaults: (this)
		int __thiscall getBaseSpeed(); // address: 0x48C392 | defaults: (this)
		int __thiscall getBaseAccuracy(); // address: 0x48C37B | defaults: (this)
		int __thiscall getMeleeAttack(/*IgnoreExtraHand [MM7+] = false*/); // address: 0x48C690 | defaults: (this), false
		int __thiscall addHP(/*Amount*/); // address: 0x48D026 | defaults: (this)
		int __thiscall addHitPoints(); // address: 0x48D026 | defaults: 0
		int __thiscall getBaseArmorClass(); // address: 0x48DAB9 | defaults: (this)
		int __thiscall getBaseAge(); // address: 0x48DB3F | defaults: (this)
		int __thiscall getMight(); // address: 0x48C406 | defaults: (this)
		int __thiscall getSkill(/*Skill:const.Skills*/); // address: 0x48EF4F | defaults: (this)
		int __thiscall getSpeed(); // address: 0x48C5D6 | defaults: (this)
		int __thiscall getBasePersonality(); // address: 0x48C34D | defaults: (this)
		bool __thiscall isConscious(); // address: 0x491514 | defaults: (this)
		int __thiscall removeFromInventory(/*Slot*/); // address: 0x49133B | defaults: (this)
		int __thiscall getBaseEndurance(); // address: 0x48C364 | defaults: (this)
		int __thiscall getEndurance(); // address: 0x48C51C | defaults: (this)
		int __thiscall calcStatBonusByMagic(/*Stat:const.Stats*/); // address: 0x48EE09 | defaults: (this)
		int __thiscall setRecoveryDelayRaw(/*Delay*/); // address: 0x48DFF8 | defaults: (this)
		int __thiscall getPersonality(); // address: 0x48C4BF | defaults: (this)
		char* __thiscall getMeleeDamageRangeText(); // address: 0x48CBFB | defaults: (this)
		int __thiscall getLevel(); // address: 0x48C3D7 | defaults: (this)
		int __thiscall getFullHP(); // address: 0x48D9B4 | defaults: (this)
		int __thiscall getArmorClass(); // address: 0x48DAF2 | defaults: (this)
		int __thiscall getLuck(); // address: 0x48C633 | defaults: (this)
	};
	static_assert(sizeof(mm8::Player) == 0x1D28, "Invalid \"mm8::Player\" structure size");
	static_assert(offsetof(mm8::Player, weak) == 8);
	static_assert(offsetof(mm8::Player, asleep) == 16);
	static_assert(offsetof(mm8::Player, afraid) == 24);
	static_assert(offsetof(mm8::Player, drunk) == 32);
	static_assert(offsetof(mm8::Player, insane) == 40);
	static_assert(offsetof(mm8::Player, poison1) == 48);
	static_assert(offsetof(mm8::Player, disease1) == 56);
	static_assert(offsetof(mm8::Player, poison2) == 64);
	static_assert(offsetof(mm8::Player, disease2) == 72);
	static_assert(offsetof(mm8::Player, poison3) == 80);
	static_assert(offsetof(mm8::Player, disease3) == 88);
	static_assert(offsetof(mm8::Player, paralyzed) == 96);
	static_assert(offsetof(mm8::Player, unconscious) == 104);
	static_assert(offsetof(mm8::Player, dead) == 112);
	static_assert(offsetof(mm8::Player, stoned) == 120);
	static_assert(offsetof(mm8::Player, eradicated) == 128);
	static_assert(offsetof(mm8::Player, zombie) == 136);
	static_assert(offsetof(mm8::Player, good) == 144);
	static_assert(offsetof(mm8::Player, exp) == 160);
	static_assert(offsetof(mm8::Player, experience) == 160);
	static_assert(offsetof(mm8::Player, name) == 168);
	static_assert(offsetof(mm8::Player, biography) == 200);
	static_assert(offsetof(mm8::Player, clas) == 850);
	static_assert(offsetof(mm8::Player, face) == 851);
	static_assert(offsetof(mm8::Player, stats) == 852);
	static_assert(offsetof(mm8::Player, mightBase) == 852);
	static_assert(offsetof(mm8::Player, mightBonus) == 854);
	static_assert(offsetof(mm8::Player, intellectBase) == 856);
	static_assert(offsetof(mm8::Player, intellectBonus) == 858);
	static_assert(offsetof(mm8::Player, personalityBase) == 860);
	static_assert(offsetof(mm8::Player, personalityBonus) == 862);
	static_assert(offsetof(mm8::Player, enduranceBase) == 864);
	static_assert(offsetof(mm8::Player, enduranceBonus) == 866);
	static_assert(offsetof(mm8::Player, speedBase) == 868);
	static_assert(offsetof(mm8::Player, speedBonus) == 870);
	static_assert(offsetof(mm8::Player, accuracyBase) == 872);
	static_assert(offsetof(mm8::Player, accuracyBonus) == 874);
	static_assert(offsetof(mm8::Player, luckBase) == 876);
	static_assert(offsetof(mm8::Player, luckBonus) == 878);
	static_assert(offsetof(mm8::Player, armorClassBonus) == 880);
	static_assert(offsetof(mm8::Player, levelBase) == 882);
	static_assert(offsetof(mm8::Player, levelBonus) == 884);
	static_assert(offsetof(mm8::Player, ageBonus) == 886);
	static_assert(offsetof(mm8::Player, skills) == 888);
	static_assert(offsetof(mm8::Player, spells) == 1030);
	static_assert(offsetof(mm8::Player, usedBlackPotions) == 1164);
	static_assert(offsetof(mm8::Player, items) == 1192);
	static_assert(offsetof(mm8::Player, inventory) == 6160);
	static_assert(offsetof(mm8::Player, resistanceBase) == 6664);
	static_assert(offsetof(mm8::Player, fireResistanceBase) == 6664);
	static_assert(offsetof(mm8::Player, airResistanceBase) == 6666);
	static_assert(offsetof(mm8::Player, waterResistanceBase) == 6668);
	static_assert(offsetof(mm8::Player, earthResistanceBase) == 6670);
	static_assert(offsetof(mm8::Player, spiritResistanceBase) == 6676);
	static_assert(offsetof(mm8::Player, mindResistanceBase) == 6678);
	static_assert(offsetof(mm8::Player, bodyResistanceBase) == 6680);
	static_assert(offsetof(mm8::Player, lightResistanceBase) == 6682);
	static_assert(offsetof(mm8::Player, darkResistanceBase) == 6684);
	static_assert(offsetof(mm8::Player, resistanceBonus) == 6686);
	static_assert(offsetof(mm8::Player, fireResistanceBonus) == 6686);
	static_assert(offsetof(mm8::Player, airResistanceBonus) == 6688);
	static_assert(offsetof(mm8::Player, waterResistanceBonus) == 6690);
	static_assert(offsetof(mm8::Player, earthResistanceBonus) == 6692);
	static_assert(offsetof(mm8::Player, spiritResistanceBonus) == 6698);
	static_assert(offsetof(mm8::Player, mindResistanceBonus) == 6700);
	static_assert(offsetof(mm8::Player, bodyResistanceBonus) == 6702);
	static_assert(offsetof(mm8::Player, lightResistanceBonus) == 6704);
	static_assert(offsetof(mm8::Player, darkResistanceBonus) == 6706);
	static_assert(offsetof(mm8::Player, spellBuffs) == 6708);
	static_assert(offsetof(mm8::Player, voice) == 7140);
	static_assert(offsetof(mm8::Player, rosterBitIndex) == 7152);
	static_assert(offsetof(mm8::Player, recoveryDelay) == 7154);
	static_assert(offsetof(mm8::Player, skillPoints) == 7156);
	static_assert(offsetof(mm8::Player, HP) == 7160);
	static_assert(offsetof(mm8::Player, hitPoints) == 7160);
	static_assert(offsetof(mm8::Player, SP) == 7164);
	static_assert(offsetof(mm8::Player, spellPoints) == 7164);
	static_assert(offsetof(mm8::Player, birthYear) == 7168);
	static_assert(offsetof(mm8::Player, equippedItems) == 7172);
	static_assert(offsetof(mm8::Player, itemExtraHand) == 7172);
	static_assert(offsetof(mm8::Player, itemMainHand) == 7176);
	static_assert(offsetof(mm8::Player, itemBow) == 7180);
	static_assert(offsetof(mm8::Player, itemArmor) == 7184);
	static_assert(offsetof(mm8::Player, itemHelm) == 7188);
	static_assert(offsetof(mm8::Player, itemBelt) == 7192);
	static_assert(offsetof(mm8::Player, itemCloak) == 7196);
	static_assert(offsetof(mm8::Player, itemGountlets) == 7200);
	static_assert(offsetof(mm8::Player, itemBoots) == 7204);
	static_assert(offsetof(mm8::Player, itemAmulet) == 7208);
	static_assert(offsetof(mm8::Player, itemRing1) == 7212);
	static_assert(offsetof(mm8::Player, itemRing2) == 7216);
	static_assert(offsetof(mm8::Player, itemRing3) == 7220);
	static_assert(offsetof(mm8::Player, itemRing4) == 7224);
	static_assert(offsetof(mm8::Player, itemRing5) == 7228);
	static_assert(offsetof(mm8::Player, itemRing6) == 7232);
	static_assert(offsetof(mm8::Player, spellBookPage) == 7236);
	static_assert(offsetof(mm8::Player, quickSpell) == 7237);
	static_assert(offsetof(mm8::Player, expression) == 7302);
	static_assert(offsetof(mm8::Player, expressionTimePassed) == 7304);
	static_assert(offsetof(mm8::Player, expressionLength) == 7306);
	static_assert(offsetof(mm8::Player, beacons) == 7320);
	static_assert(offsetof(mm8::Player, devineInterventionCasts) == 7460);
	static_assert(offsetof(mm8::Player, armageddonCasts) == 7461);
	static_assert(offsetof(mm8::Player, fireSpikeCasts) == 7462);
}

#pragma pack(pop)