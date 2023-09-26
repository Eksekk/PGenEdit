#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct MonsterSchedule // size: 0xC
	{
		union
		{
			std::array<int16_t, 3> pos; // 0x0 (0 decimal)
			struct
			{
				int16_t x; // 0x0 (0 decimal)
				int16_t y; // 0x2 (2 decimal)
				int16_t z; // 0x4 (4 decimal)
			};
		};
		uint16_t bits; // 0x6 (6 decimal) | MMExt info: (1 - on)
		uint8_t action; // 0x8 (8 decimal)
		uint8_t hour; // 0x9 (9 decimal)
		uint8_t day; // 0xA (10 decimal)
		uint8_t month; // 0xB (11 decimal)
	};
	static_assert(sizeof(mm6::MonsterSchedule) == 0xC, "Invalid \"mm6::MonsterSchedule\" structure size");
	static_assert(offsetof(mm6::MonsterSchedule, y) == 2);
	static_assert(offsetof(mm6::MonsterSchedule, z) == 4);
	static_assert(offsetof(mm6::MonsterSchedule, bits) == 6);
	static_assert(offsetof(mm6::MonsterSchedule, action) == 8);
	static_assert(offsetof(mm6::MonsterSchedule, hour) == 9);
	static_assert(offsetof(mm6::MonsterSchedule, day) == 10);
	static_assert(offsetof(mm6::MonsterSchedule, month) == 11);



	struct MonsterAttackInfo // size: 0x5
	{
		uint8_t type; // 0x0 (0 decimal)
		uint8_t damageDiceCount; // 0x1 (1 decimal)
		uint8_t damageDiceSides; // 0x2 (2 decimal)
		uint8_t damageAdd; // 0x3 (3 decimal)
		uint8_t missile; // 0x4 (4 decimal)
	};
	static_assert(sizeof(mm6::MonsterAttackInfo) == 0x5, "Invalid \"mm6::MonsterAttackInfo\" structure size");
	static_assert(offsetof(mm6::MonsterAttackInfo, damageDiceCount) == 1);
	static_assert(offsetof(mm6::MonsterAttackInfo, damageDiceSides) == 2);
	static_assert(offsetof(mm6::MonsterAttackInfo, damageAdd) == 3);
	static_assert(offsetof(mm6::MonsterAttackInfo, missile) == 4);



	struct MonstersTxtItem // size: 0x48
	{
		char* name; // EditPChar | 0x0 (0 decimal)
		char* picture; // EditPChar | 0x4 (4 decimal)
		uint8_t id; // 0x8 (8 decimal) | MMExt info: Changing may cause random crashes after loading the game! Be careful.
		uint8_t level; // 0x9 (9 decimal)
		uint8_t treasureItemPercent; // 0xA (10 decimal)
		uint8_t treasureDiceCount; // 0xB (11 decimal)
		uint8_t treasureDiceSides; // 0xC (12 decimal)
		uint8_t treasureItemLevel; // 0xD (13 decimal)
		uint8_t treasureItemType; // 0xE (14 decimal)
		uint8_t fly; // 0xF (15 decimal)
		uint8_t moveType; // 0x10 (16 decimal)
		uint8_t AIType; // 0x11 (17 decimal)
		uint8_t hostileType; // 0x12 (18 decimal)
		union
		{
			uint8_t prefClass; // 0x13 (19 decimal) | MMExt info: Preferred target
			struct // size: 0x1, MMExt union
			{
				bool knight : 1; // 0x13 (19 decimal), bit index 7
				bool paladin : 1; // 0x13 (19 decimal), bit index 6
				bool archer : 1; // 0x13 (19 decimal), bit index 5
				bool druid : 1; // 0x13 (19 decimal), bit index 4
				bool cleric : 1; // 0x13 (19 decimal), bit index 3
				bool sorcerer : 1; // 0x13 (19 decimal), bit index 2
				bool male : 1; // 0x13 (19 decimal), bit index 1
				bool female : 1; // 0x13 (19 decimal), bit index 0
			} prefers;
			static_assert(sizeof(prefers) == 0x1, "Invalid \"prefers\" structure size");;
		};
		uint8_t bonus; // 0x14 (20 decimal) | MMExt info: (steal, curse, ...)
		uint8_t bonusMul; // 0x15 (21 decimal) | MMExt info: Disease1x5 etc. The chance that a monster would use the bonus is 'Level'*'BonusMul'
		mm6::MonsterAttackInfo attack1; // 0x16 (22 decimal)
		uint8_t attack2Chance; // 0x1B (27 decimal)
		mm6::MonsterAttackInfo attack2; // 0x1C (28 decimal)
		uint8_t spellChance; // 0x21 (33 decimal)
		uint8_t spell; // 0x22 (34 decimal)
		uint8_t spellSkill; // 0x23 (35 decimal)
		union
		{
			struct // size: 0x6, MMExt union
			{
				uint8_t _2; // 0x24 (36 decimal)
				uint8_t _3; // 0x25 (37 decimal)
				uint8_t _4; // 0x26 (38 decimal)
				uint8_t _5; // 0x27 (39 decimal)
				uint8_t _0; // 0x28 (40 decimal)
				uint8_t _1; // 0x29 (41 decimal)
			} resistances;
			static_assert(sizeof(resistances) == 0x6, "Invalid \"resistances\" structure size");;
			struct
			{
				uint8_t fireResistance; // 0x24 (36 decimal)
				uint8_t elecResistance; // 0x25 (37 decimal)
				uint8_t coldResistance; // 0x26 (38 decimal)
				uint8_t poisonResistance; // 0x27 (39 decimal)
				uint8_t physResistance; // 0x28 (40 decimal)
				uint8_t magicResistance; // 0x29 (41 decimal)
			};
		};
		uint8_t prefNum; // 0x2A (42 decimal) | MMExt info: Number of party members to hit using Attack1 & Attack2
		SKIP(1);
		int16_t questItem; // 0x2C (44 decimal)
		SKIP(2);
		union
		{
			int32_t fullHP; // 0x30 (48 decimal)
			int32_t fullHitPoints; // 0x30 (48 decimal)
		};
		int32_t armorClass; // 0x34 (52 decimal)
		union
		{
			int32_t exp; // 0x38 (56 decimal)
			int32_t experience; // 0x38 (56 decimal)
		};
		int32_t moveSpeed; // 0x3C (60 decimal)
		int32_t attackRecovery; // 0x40 (64 decimal)
		SKIP(4);
	};
	static_assert(sizeof(mm6::MonstersTxtItem) == 0x48, "Invalid \"mm6::MonstersTxtItem\" structure size");
	static_assert(offsetof(mm6::MonstersTxtItem, picture) == 4);
	static_assert(offsetof(mm6::MonstersTxtItem, id) == 8);
	static_assert(offsetof(mm6::MonstersTxtItem, level) == 9);
	static_assert(offsetof(mm6::MonstersTxtItem, treasureItemPercent) == 10);
	static_assert(offsetof(mm6::MonstersTxtItem, treasureDiceCount) == 11);
	static_assert(offsetof(mm6::MonstersTxtItem, treasureDiceSides) == 12);
	static_assert(offsetof(mm6::MonstersTxtItem, treasureItemLevel) == 13);
	static_assert(offsetof(mm6::MonstersTxtItem, treasureItemType) == 14);
	static_assert(offsetof(mm6::MonstersTxtItem, fly) == 15);
	static_assert(offsetof(mm6::MonstersTxtItem, moveType) == 16);
	static_assert(offsetof(mm6::MonstersTxtItem, AIType) == 17);
	static_assert(offsetof(mm6::MonstersTxtItem, hostileType) == 18);
	static_assert(offsetof(mm6::MonstersTxtItem, prefClass) == 19);
	static_assert(offsetof(mm6::MonstersTxtItem, prefers) == 19);
	static_assert(offsetof(mm6::MonstersTxtItem, bonus) == 20);
	static_assert(offsetof(mm6::MonstersTxtItem, bonusMul) == 21);
	static_assert(offsetof(mm6::MonstersTxtItem, attack1) == 22);
	static_assert(offsetof(mm6::MonstersTxtItem, attack2Chance) == 27);
	static_assert(offsetof(mm6::MonstersTxtItem, attack2) == 28);
	static_assert(offsetof(mm6::MonstersTxtItem, spellChance) == 33);
	static_assert(offsetof(mm6::MonstersTxtItem, spell) == 34);
	static_assert(offsetof(mm6::MonstersTxtItem, spellSkill) == 35);
	static_assert(offsetof(mm6::MonstersTxtItem, resistances) == 36);
	static_assert(offsetof(mm6::MonstersTxtItem, fireResistance) == 36);
	static_assert(offsetof(mm6::MonstersTxtItem, elecResistance) == 37);
	static_assert(offsetof(mm6::MonstersTxtItem, coldResistance) == 38);
	static_assert(offsetof(mm6::MonstersTxtItem, poisonResistance) == 39);
	static_assert(offsetof(mm6::MonstersTxtItem, physResistance) == 40);
	static_assert(offsetof(mm6::MonstersTxtItem, magicResistance) == 41);
	static_assert(offsetof(mm6::MonstersTxtItem, prefNum) == 42);
	static_assert(offsetof(mm6::MonstersTxtItem, questItem) == 44);
	static_assert(offsetof(mm6::MonstersTxtItem, fullHP) == 48);
	static_assert(offsetof(mm6::MonstersTxtItem, fullHitPoints) == 48);
	static_assert(offsetof(mm6::MonstersTxtItem, armorClass) == 52);
	static_assert(offsetof(mm6::MonstersTxtItem, exp) == 56);
	static_assert(offsetof(mm6::MonstersTxtItem, experience) == 56);
	static_assert(offsetof(mm6::MonstersTxtItem, moveSpeed) == 60);
	static_assert(offsetof(mm6::MonstersTxtItem, attackRecovery) == 64);



	struct MapMonster // size: 0x224
	{
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		// MMExt info: [MM6] Index in #Game.StreetNPC:# + 1
		// [MM7+] Index in #Game.NPC:# or index in #Game.StreetNPC:# + 5000
		int16_t NPC_ID; // 0x20 (32 decimal)
		SKIP(2);
		union
		{
			uint32_t bits; // 0x24 (36 decimal)
			struct
			{
				SKIPBITS(8); // skipping 1 bytes and 2 bits, in total 10 bits
				SKIPBITS(2);
				bool active : 1; // 0x25 (37 decimal), bit index 5
				SKIPBITS(4);
				bool showOnMap : 1; // 0x25 (37 decimal), bit index 0
				bool invisible : 1; // 0x26 (38 decimal), bit index 7
				bool noFlee : 1; // 0x26 (38 decimal), bit index 6
				SKIPBITS(1);
				bool hostile : 1; // 0x26 (38 decimal), bit index 4
				bool onAlertMap : 1; // 0x26 (38 decimal), bit index 3
				SKIPBITS(2);
				bool treasureGenerated : 1; // 0x26 (38 decimal), bit index 0
				bool showAsHostile : 1; // 0x27 (39 decimal), bit index 7
			};
		};
		union
		{
			int16_t HP; // 0x28 (40 decimal)
			int16_t hitPoints; // 0x28 (40 decimal)
		};
		SKIP(10);
		uint8_t id; // 0x34 (52 decimal) | MMExt info: Changing may cause random crashes after loading the game! Be careful.
		uint8_t level; // 0x35 (53 decimal)
		uint8_t treasureItemPercent; // 0x36 (54 decimal)
		uint8_t treasureDiceCount; // 0x37 (55 decimal)
		uint8_t treasureDiceSides; // 0x38 (56 decimal)
		uint8_t treasureItemLevel; // 0x39 (57 decimal)
		uint8_t treasureItemType; // 0x3A (58 decimal)
		uint8_t fly; // 0x3B (59 decimal)
		uint8_t moveType; // 0x3C (60 decimal)
		uint8_t AIType; // 0x3D (61 decimal)
		uint8_t hostileType; // 0x3E (62 decimal)
		union
		{
			uint8_t prefClass; // 0x3F (63 decimal) | MMExt info: Preferred target
			struct // size: 0x1, MMExt union
			{
				bool knight : 1; // 0x3F (63 decimal), bit index 7
				bool paladin : 1; // 0x3F (63 decimal), bit index 6
				bool archer : 1; // 0x3F (63 decimal), bit index 5
				bool druid : 1; // 0x3F (63 decimal), bit index 4
				bool cleric : 1; // 0x3F (63 decimal), bit index 3
				bool sorcerer : 1; // 0x3F (63 decimal), bit index 2
				bool male : 1; // 0x3F (63 decimal), bit index 1
				bool female : 1; // 0x3F (63 decimal), bit index 0
			} prefers;
			static_assert(sizeof(prefers) == 0x1, "Invalid \"prefers\" structure size");;
		};
		uint8_t bonus; // 0x40 (64 decimal) | MMExt info: (steal, curse, ...)
		uint8_t bonusMul; // 0x41 (65 decimal) | MMExt info: Disease1x5 etc. The chance that a monster would use the bonus is 'Level'*'BonusMul'
		mm6::MonsterAttackInfo attack1; // 0x42 (66 decimal)
		uint8_t attack2Chance; // 0x47 (71 decimal)
		mm6::MonsterAttackInfo attack2; // 0x48 (72 decimal)
		uint8_t spellChance; // 0x4D (77 decimal)
		uint8_t spell; // 0x4E (78 decimal)
		uint8_t spellSkill; // 0x4F (79 decimal)
		union
		{
			struct // size: 0x6, MMExt union
			{
				uint8_t _2; // 0x50 (80 decimal)
				uint8_t _3; // 0x51 (81 decimal)
				uint8_t _4; // 0x52 (82 decimal)
				uint8_t _5; // 0x53 (83 decimal)
				uint8_t _0; // 0x54 (84 decimal)
				uint8_t _1; // 0x55 (85 decimal)
			} resistances;
			static_assert(sizeof(resistances) == 0x6, "Invalid \"resistances\" structure size");;
			struct
			{
				uint8_t fireResistance; // 0x50 (80 decimal)
				uint8_t elecResistance; // 0x51 (81 decimal)
				uint8_t coldResistance; // 0x52 (82 decimal)
				uint8_t poisonResistance; // 0x53 (83 decimal)
				uint8_t physResistance; // 0x54 (84 decimal)
				uint8_t magicResistance; // 0x55 (85 decimal)
			};
		};
		uint8_t prefNum; // 0x56 (86 decimal) | MMExt info: Number of party members to hit using Attack1 & Attack2
		SKIP(1);
		int16_t questItem; // 0x58 (88 decimal)
		SKIP(2);
		union
		{
			int32_t fullHP; // 0x5C (92 decimal)
			int32_t fullHitPoints; // 0x5C (92 decimal)
		};
		int32_t armorClass; // 0x60 (96 decimal)
		union
		{
			int32_t exp; // 0x64 (100 decimal)
			int32_t experience; // 0x64 (100 decimal)
		};
		int32_t moveSpeed; // 0x68 (104 decimal)
		int32_t attackRecovery; // 0x6C (108 decimal)
		SKIP(4);
		int16_t rangeAttack; // 0x74 (116 decimal)
		int16_t id2; // 0x76 (118 decimal)
		int16_t bodyRadius; // 0x78 (120 decimal)
		int16_t bodyHeight; // 0x7A (122 decimal)
		int16_t velocity; // 0x7C (124 decimal)
		union
		{
			std::array<int16_t, 3> pos; // 0x7E (126 decimal)
			struct
			{
				int16_t x; // 0x7E (126 decimal)
				int16_t y; // 0x80 (128 decimal)
				int16_t z; // 0x82 (130 decimal)
			};
		};
		int16_t velocityX; // 0x84 (132 decimal)
		int16_t velocityY; // 0x86 (134 decimal)
		int16_t velocityZ; // 0x88 (136 decimal)
		int16_t direction; // 0x8A (138 decimal)
		int16_t lookAngle; // 0x8C (140 decimal)
		int16_t room; // 0x8E (142 decimal)
		int16_t currentActionLength; // 0x90 (144 decimal)
		int16_t startX; // 0x92 (146 decimal)
		int16_t startY; // 0x94 (148 decimal)
		int16_t startZ; // 0x96 (150 decimal)
		int16_t guardX; // 0x98 (152 decimal)
		int16_t guardY; // 0x9A (154 decimal)
		int16_t guardZ; // 0x9C (156 decimal)
		int16_t guardRadius; // 0x9E (158 decimal)
		int16_t AIState; // 0xA0 (160 decimal)
		int16_t graphicState; // 0xA2 (162 decimal)
		int16_t item; // 0xA4 (164 decimal)
		SKIP(2);
		int32_t currentActionStep; // 0xA8 (168 decimal)
		union
		{
			std::array<int16_t, 8> frames; // 0xAC (172 decimal)
			struct
			{
				int16_t framesStand; // 0xAC (172 decimal)
				int16_t framesWalk; // 0xAE (174 decimal)
				int16_t framesAttack; // 0xB0 (176 decimal)
				int16_t framesShoot; // 0xB2 (178 decimal)
				union
				{
					int16_t framesStun; // 0xB4 (180 decimal)
					int16_t framesGotHit; // 0xB4 (180 decimal)
				};
				int16_t framesDie; // 0xB6 (182 decimal)
				int16_t framesDead; // 0xB8 (184 decimal)
				int16_t framesFidget; // 0xBA (186 decimal)
			};
		};
		union
		{
			std::array<int16_t, 4> sounds; // 0xBC (188 decimal)
			struct
			{
				int16_t soundAttack; // 0xBC (188 decimal)
				int16_t soundDie; // 0xBE (190 decimal)
				union
				{
					int16_t soundGotHit; // 0xC0 (192 decimal)
					int16_t soundGetHit; // 0xC0 (192 decimal)
				};
				int16_t soundFidget; // 0xC2 (194 decimal)
			};
		};
		std::array<mm6::SpellBuff, 14> spellBuffs; // 0xC4 (196 decimal)
		int32_t group; // 0x1A4 (420 decimal)
		int32_t ally; // 0x1A8 (424 decimal) | MMExt info: Monster class that guards or is guraded by this one. That is, !Lua[[(Id + 2):div(3)]], like in Hostile.txt.
		std::array<mm6::MonsterSchedule, 8> schedules; // 0x1AC (428 decimal)
		int32_t summoner; // 0x20C (524 decimal)
		int32_t lastAttacker; // 0x210 (528 decimal) | MMExt info: Last one who hit the monster
		SKIP(16);
		int __thiscall loadFrames(/*SoundLoaded = false*/); // address: 0x44BF50 | defaults: (this), false
		char* __thiscall updateGraphicState(); // address: 0x44C140 | defaults: (this)
		int __stdcall calcTakenDamage(/*DamageKind, Damage*/); // address: 0x421DC0 | defaults: (this)
		bool __stdcall calcHitOrMiss(/*Player:structs.Player*/); // address: 0x421D50 | defaults: (this)
		int __thiscall chooseTargetPlayer(); // address: 0x4219B0 | defaults: (this)
		bool __thiscall calcHitByEffect(/*DamageKind*/); // address: 0x421E90 | defaults: (this)
	};
	static_assert(sizeof(mm6::MapMonster) == 0x224, "Invalid \"mm6::MapMonster\" structure size");
	static_assert(offsetof(mm6::MapMonster, NPC_ID) == 32);
	static_assert(offsetof(mm6::MapMonster, bits) == 36);
	static_assert(offsetof(mm6::MapMonster, HP) == 40);
	static_assert(offsetof(mm6::MapMonster, hitPoints) == 40);
	static_assert(offsetof(mm6::MapMonster, id) == 52);
	static_assert(offsetof(mm6::MapMonster, level) == 53);
	static_assert(offsetof(mm6::MapMonster, treasureItemPercent) == 54);
	static_assert(offsetof(mm6::MapMonster, treasureDiceCount) == 55);
	static_assert(offsetof(mm6::MapMonster, treasureDiceSides) == 56);
	static_assert(offsetof(mm6::MapMonster, treasureItemLevel) == 57);
	static_assert(offsetof(mm6::MapMonster, treasureItemType) == 58);
	static_assert(offsetof(mm6::MapMonster, fly) == 59);
	static_assert(offsetof(mm6::MapMonster, moveType) == 60);
	static_assert(offsetof(mm6::MapMonster, AIType) == 61);
	static_assert(offsetof(mm6::MapMonster, hostileType) == 62);
	static_assert(offsetof(mm6::MapMonster, prefClass) == 63);
	static_assert(offsetof(mm6::MapMonster, prefers) == 63);
	static_assert(offsetof(mm6::MapMonster, bonus) == 64);
	static_assert(offsetof(mm6::MapMonster, bonusMul) == 65);
	static_assert(offsetof(mm6::MapMonster, attack1) == 66);
	static_assert(offsetof(mm6::MapMonster, attack2Chance) == 71);
	static_assert(offsetof(mm6::MapMonster, attack2) == 72);
	static_assert(offsetof(mm6::MapMonster, spellChance) == 77);
	static_assert(offsetof(mm6::MapMonster, spell) == 78);
	static_assert(offsetof(mm6::MapMonster, spellSkill) == 79);
	static_assert(offsetof(mm6::MapMonster, resistances) == 80);
	static_assert(offsetof(mm6::MapMonster, fireResistance) == 80);
	static_assert(offsetof(mm6::MapMonster, elecResistance) == 81);
	static_assert(offsetof(mm6::MapMonster, coldResistance) == 82);
	static_assert(offsetof(mm6::MapMonster, poisonResistance) == 83);
	static_assert(offsetof(mm6::MapMonster, physResistance) == 84);
	static_assert(offsetof(mm6::MapMonster, magicResistance) == 85);
	static_assert(offsetof(mm6::MapMonster, prefNum) == 86);
	static_assert(offsetof(mm6::MapMonster, questItem) == 88);
	static_assert(offsetof(mm6::MapMonster, fullHP) == 92);
	static_assert(offsetof(mm6::MapMonster, fullHitPoints) == 92);
	static_assert(offsetof(mm6::MapMonster, armorClass) == 96);
	static_assert(offsetof(mm6::MapMonster, exp) == 100);
	static_assert(offsetof(mm6::MapMonster, experience) == 100);
	static_assert(offsetof(mm6::MapMonster, moveSpeed) == 104);
	static_assert(offsetof(mm6::MapMonster, attackRecovery) == 108);
	static_assert(offsetof(mm6::MapMonster, rangeAttack) == 116);
	static_assert(offsetof(mm6::MapMonster, id2) == 118);
	static_assert(offsetof(mm6::MapMonster, bodyRadius) == 120);
	static_assert(offsetof(mm6::MapMonster, bodyHeight) == 122);
	static_assert(offsetof(mm6::MapMonster, velocity) == 124);
	static_assert(offsetof(mm6::MapMonster, pos) == 126);
	static_assert(offsetof(mm6::MapMonster, x) == 126);
	static_assert(offsetof(mm6::MapMonster, y) == 128);
	static_assert(offsetof(mm6::MapMonster, z) == 130);
	static_assert(offsetof(mm6::MapMonster, velocityX) == 132);
	static_assert(offsetof(mm6::MapMonster, velocityY) == 134);
	static_assert(offsetof(mm6::MapMonster, velocityZ) == 136);
	static_assert(offsetof(mm6::MapMonster, direction) == 138);
	static_assert(offsetof(mm6::MapMonster, lookAngle) == 140);
	static_assert(offsetof(mm6::MapMonster, room) == 142);
	static_assert(offsetof(mm6::MapMonster, currentActionLength) == 144);
	static_assert(offsetof(mm6::MapMonster, startX) == 146);
	static_assert(offsetof(mm6::MapMonster, startY) == 148);
	static_assert(offsetof(mm6::MapMonster, startZ) == 150);
	static_assert(offsetof(mm6::MapMonster, guardX) == 152);
	static_assert(offsetof(mm6::MapMonster, guardY) == 154);
	static_assert(offsetof(mm6::MapMonster, guardZ) == 156);
	static_assert(offsetof(mm6::MapMonster, guardRadius) == 158);
	static_assert(offsetof(mm6::MapMonster, AIState) == 160);
	static_assert(offsetof(mm6::MapMonster, graphicState) == 162);
	static_assert(offsetof(mm6::MapMonster, item) == 164);
	static_assert(offsetof(mm6::MapMonster, currentActionStep) == 168);
	static_assert(offsetof(mm6::MapMonster, frames) == 172);
	static_assert(offsetof(mm6::MapMonster, framesStand) == 172);
	static_assert(offsetof(mm6::MapMonster, framesWalk) == 174);
	static_assert(offsetof(mm6::MapMonster, framesAttack) == 176);
	static_assert(offsetof(mm6::MapMonster, framesShoot) == 178);
	static_assert(offsetof(mm6::MapMonster, framesStun) == 180);
	static_assert(offsetof(mm6::MapMonster, framesGotHit) == 180);
	static_assert(offsetof(mm6::MapMonster, framesDie) == 182);
	static_assert(offsetof(mm6::MapMonster, framesDead) == 184);
	static_assert(offsetof(mm6::MapMonster, framesFidget) == 186);
	static_assert(offsetof(mm6::MapMonster, sounds) == 188);
	static_assert(offsetof(mm6::MapMonster, soundAttack) == 188);
	static_assert(offsetof(mm6::MapMonster, soundDie) == 190);
	static_assert(offsetof(mm6::MapMonster, soundGotHit) == 192);
	static_assert(offsetof(mm6::MapMonster, soundGetHit) == 192);
	static_assert(offsetof(mm6::MapMonster, soundFidget) == 194);
	static_assert(offsetof(mm6::MapMonster, spellBuffs) == 196);
	static_assert(offsetof(mm6::MapMonster, group) == 420);
	static_assert(offsetof(mm6::MapMonster, ally) == 424);
	static_assert(offsetof(mm6::MapMonster, schedules) == 428);
	static_assert(offsetof(mm6::MapMonster, summoner) == 524);
	static_assert(offsetof(mm6::MapMonster, lastAttacker) == 528);
}
namespace mm7
{
	struct MonsterKind // size: 0x8
	{
		bool undead; // 0x0 (0 decimal)
		bool demon; // 0x1 (1 decimal)
		bool dragon; // 0x2 (2 decimal)
		bool elf; // 0x3 (3 decimal)
		bool swimmer; // 0x4 (4 decimal)
		bool immobile; // 0x5 (5 decimal)
		bool titan; // 0x6 (6 decimal)
		bool noArena; // 0x7 (7 decimal)
	};
	static_assert(sizeof(mm7::MonsterKind) == 0x8, "Invalid \"mm7::MonsterKind\" structure size");
	static_assert(offsetof(mm7::MonsterKind, demon) == 1);
	static_assert(offsetof(mm7::MonsterKind, dragon) == 2);
	static_assert(offsetof(mm7::MonsterKind, elf) == 3);
	static_assert(offsetof(mm7::MonsterKind, swimmer) == 4);
	static_assert(offsetof(mm7::MonsterKind, immobile) == 5);
	static_assert(offsetof(mm7::MonsterKind, titan) == 6);
	static_assert(offsetof(mm7::MonsterKind, noArena) == 7);



	struct MonsterSchedule // size: 0xC
	{
		union
		{
			std::array<int16_t, 3> pos; // 0x0 (0 decimal)
			struct
			{
				int16_t x; // 0x0 (0 decimal)
				int16_t y; // 0x2 (2 decimal)
				int16_t z; // 0x4 (4 decimal)
			};
		};
		uint16_t bits; // 0x6 (6 decimal) | MMExt info: (1 - on)
		uint8_t action; // 0x8 (8 decimal)
		uint8_t hour; // 0x9 (9 decimal)
		uint8_t day; // 0xA (10 decimal)
		uint8_t month; // 0xB (11 decimal)
	};
	static_assert(sizeof(mm7::MonsterSchedule) == 0xC, "Invalid \"mm7::MonsterSchedule\" structure size");
	static_assert(offsetof(mm7::MonsterSchedule, y) == 2);
	static_assert(offsetof(mm7::MonsterSchedule, z) == 4);
	static_assert(offsetof(mm7::MonsterSchedule, bits) == 6);
	static_assert(offsetof(mm7::MonsterSchedule, action) == 8);
	static_assert(offsetof(mm7::MonsterSchedule, hour) == 9);
	static_assert(offsetof(mm7::MonsterSchedule, day) == 10);
	static_assert(offsetof(mm7::MonsterSchedule, month) == 11);



	struct MonsterAttackInfo // size: 0x5
	{
		uint8_t type; // 0x0 (0 decimal)
		uint8_t damageDiceCount; // 0x1 (1 decimal)
		uint8_t damageDiceSides; // 0x2 (2 decimal)
		uint8_t damageAdd; // 0x3 (3 decimal)
		uint8_t missile; // 0x4 (4 decimal)
	};
	static_assert(sizeof(mm7::MonsterAttackInfo) == 0x5, "Invalid \"mm7::MonsterAttackInfo\" structure size");
	static_assert(offsetof(mm7::MonsterAttackInfo, damageDiceCount) == 1);
	static_assert(offsetof(mm7::MonsterAttackInfo, damageDiceSides) == 2);
	static_assert(offsetof(mm7::MonsterAttackInfo, damageAdd) == 3);
	static_assert(offsetof(mm7::MonsterAttackInfo, missile) == 4);



	struct MonstersTxtItem // size: 0x58
	{
		char* name; // EditPChar | 0x0 (0 decimal)
		char* picture; // EditPChar | 0x4 (4 decimal)
		uint8_t level; // 0x8 (8 decimal)
		uint8_t treasureItemPercent; // 0x9 (9 decimal)
		uint8_t treasureDiceCount; // 0xA (10 decimal)
		uint8_t treasureDiceSides; // 0xB (11 decimal)
		uint8_t treasureItemLevel; // 0xC (12 decimal)
		uint8_t treasureItemType; // 0xD (13 decimal)
		uint8_t fly; // 0xE (14 decimal)
		uint8_t moveType; // 0xF (15 decimal)
		uint8_t AIType; // 0x10 (16 decimal)
		uint8_t hostileType; // 0x11 (17 decimal)
		SKIP(1);
		uint8_t bonus; // 0x13 (19 decimal) | MMExt info: (steal, curse, ...)
		uint8_t bonusMul; // 0x14 (20 decimal) | MMExt info: Disease1x5 etc. The chance that a monster would use the bonus is 'Level'*'BonusMul'
		mm7::MonsterAttackInfo attack1; // 0x15 (21 decimal)
		uint8_t attack2Chance; // 0x1A (26 decimal)
		mm7::MonsterAttackInfo attack2; // 0x1B (27 decimal)
		uint8_t spellChance; // 0x20 (32 decimal)
		uint8_t spell; // 0x21 (33 decimal)
		uint8_t spell2Chance; // 0x22 (34 decimal)
		uint8_t spell2; // 0x23 (35 decimal)
		union
		{
			struct // size: 0xA, MMExt union
			{
				uint8_t _0; // 0x24 (36 decimal)
				uint8_t _1; // 0x25 (37 decimal)
				uint8_t _2; // 0x26 (38 decimal)
				uint8_t _3; // 0x27 (39 decimal)
				uint8_t _7; // 0x28 (40 decimal)
				uint8_t _6; // 0x29 (41 decimal)
				uint8_t _8; // 0x2A (42 decimal)
				uint8_t _9; // 0x2B (43 decimal)
				uint8_t _10; // 0x2C (44 decimal)
				uint8_t _4; // 0x2D (45 decimal)
			} resistances;
			static_assert(sizeof(resistances) == 0xA, "Invalid \"resistances\" structure size");;
			struct
			{
				uint8_t fireResistance; // 0x24 (36 decimal)
				uint8_t airResistance; // 0x25 (37 decimal)
				uint8_t waterResistance; // 0x26 (38 decimal)
				uint8_t earthResistance; // 0x27 (39 decimal)
				uint8_t mindResistance; // 0x28 (40 decimal)
				uint8_t spiritResistance; // 0x29 (41 decimal)
				uint8_t bodyResistance; // 0x2A (42 decimal)
				uint8_t lightResistance; // 0x2B (43 decimal)
				uint8_t darkResistance; // 0x2C (44 decimal)
				uint8_t physResistance; // 0x2D (45 decimal)
			};
		};
		uint8_t special; // 0x2E (46 decimal) | MMExt info: 1 = shot, 2 = summon, 3 = explode
		// MMExt info: shot: C = count
		// summon: A = {RandomLevel = 0, fixed = 1} - monster level (0 means A, B or C is chosen randomly, monster index should be that of A variation. Values of 2 and 3 are the same as 1, but in MM7 before GrayFace Patch v2.1 it was causing a bug), B = {ground = 0, air = 1}, C = already summoned count (up to 3), D = monster index
		// explode: AdB + C, D = attack type
		uint8_t specialA; // 0x2F (47 decimal)
		uint8_t specialB; // 0x30 (48 decimal)
		uint8_t specialC; // 0x31 (49 decimal)
		uint8_t prefNum; // 0x32 (50 decimal) | MMExt info: Number of party members to hit using 'Attack1' & 'Attack2'
		SKIP(1);
		uint16_t id; // 0x34 (52 decimal)
		uint16_t bloodSplat; // 0x36 (54 decimal)
		uint16_t spellSkill; // 0x38 (56 decimal)
		uint16_t spell2Skill; // 0x3A (58 decimal)
		uint16_t specialD; // 0x3C (60 decimal) | MMExt info: (summoned monster or damage type in case of explosive attack)
		SKIP(2);
		union
		{
			int32_t fullHP; // 0x40 (64 decimal)
			int32_t fullHitPoints; // 0x40 (64 decimal)
		};
		int32_t armorClass; // 0x44 (68 decimal)
		union
		{
			int32_t exp; // 0x48 (72 decimal)
			int32_t experience; // 0x48 (72 decimal)
		};
		int32_t moveSpeed; // 0x4C (76 decimal)
		int32_t attackRecovery; // 0x50 (80 decimal)
		union
		{
			int32_t prefClass; // 0x54 (84 decimal)
			struct
			{
				struct // size: 0x2, MMExt union
				{
					bool knight : 1; // 0x54 (84 decimal), bit index 7
					bool paladin : 1; // 0x54 (84 decimal), bit index 6
					bool archer : 1; // 0x54 (84 decimal), bit index 5
					bool druid : 1; // 0x54 (84 decimal), bit index 4
					bool cleric : 1; // 0x54 (84 decimal), bit index 3
					bool sorcerer : 1; // 0x54 (84 decimal), bit index 2
					bool ranger : 1; // 0x54 (84 decimal), bit index 1
					bool thief : 1; // 0x54 (84 decimal), bit index 0
					bool monk : 1; // 0x55 (85 decimal), bit index 7
					bool male : 1; // 0x55 (85 decimal), bit index 6
					bool female : 1; // 0x55 (85 decimal), bit index 5
					bool human : 1; // 0x55 (85 decimal), bit index 4
					bool elf : 1; // 0x55 (85 decimal), bit index 3
					bool dwarf : 1; // 0x55 (85 decimal), bit index 2
					bool goblin : 1; // 0x55 (85 decimal), bit index 1
				} prefers;
				static_assert(sizeof(prefers) == 0x2, "Invalid \"prefers\" structure size");;
			};
		};
	};
	static_assert(sizeof(mm7::MonstersTxtItem) == 0x58, "Invalid \"mm7::MonstersTxtItem\" structure size");
	static_assert(offsetof(mm7::MonstersTxtItem, picture) == 4);
	static_assert(offsetof(mm7::MonstersTxtItem, level) == 8);
	static_assert(offsetof(mm7::MonstersTxtItem, treasureItemPercent) == 9);
	static_assert(offsetof(mm7::MonstersTxtItem, treasureDiceCount) == 10);
	static_assert(offsetof(mm7::MonstersTxtItem, treasureDiceSides) == 11);
	static_assert(offsetof(mm7::MonstersTxtItem, treasureItemLevel) == 12);
	static_assert(offsetof(mm7::MonstersTxtItem, treasureItemType) == 13);
	static_assert(offsetof(mm7::MonstersTxtItem, fly) == 14);
	static_assert(offsetof(mm7::MonstersTxtItem, moveType) == 15);
	static_assert(offsetof(mm7::MonstersTxtItem, AIType) == 16);
	static_assert(offsetof(mm7::MonstersTxtItem, hostileType) == 17);
	static_assert(offsetof(mm7::MonstersTxtItem, bonus) == 19);
	static_assert(offsetof(mm7::MonstersTxtItem, bonusMul) == 20);
	static_assert(offsetof(mm7::MonstersTxtItem, attack1) == 21);
	static_assert(offsetof(mm7::MonstersTxtItem, attack2Chance) == 26);
	static_assert(offsetof(mm7::MonstersTxtItem, attack2) == 27);
	static_assert(offsetof(mm7::MonstersTxtItem, spellChance) == 32);
	static_assert(offsetof(mm7::MonstersTxtItem, spell) == 33);
	static_assert(offsetof(mm7::MonstersTxtItem, spell2Chance) == 34);
	static_assert(offsetof(mm7::MonstersTxtItem, spell2) == 35);
	static_assert(offsetof(mm7::MonstersTxtItem, resistances) == 36);
	static_assert(offsetof(mm7::MonstersTxtItem, fireResistance) == 36);
	static_assert(offsetof(mm7::MonstersTxtItem, airResistance) == 37);
	static_assert(offsetof(mm7::MonstersTxtItem, waterResistance) == 38);
	static_assert(offsetof(mm7::MonstersTxtItem, earthResistance) == 39);
	static_assert(offsetof(mm7::MonstersTxtItem, mindResistance) == 40);
	static_assert(offsetof(mm7::MonstersTxtItem, spiritResistance) == 41);
	static_assert(offsetof(mm7::MonstersTxtItem, bodyResistance) == 42);
	static_assert(offsetof(mm7::MonstersTxtItem, lightResistance) == 43);
	static_assert(offsetof(mm7::MonstersTxtItem, darkResistance) == 44);
	static_assert(offsetof(mm7::MonstersTxtItem, physResistance) == 45);
	static_assert(offsetof(mm7::MonstersTxtItem, special) == 46);
	static_assert(offsetof(mm7::MonstersTxtItem, specialA) == 47);
	static_assert(offsetof(mm7::MonstersTxtItem, specialB) == 48);
	static_assert(offsetof(mm7::MonstersTxtItem, specialC) == 49);
	static_assert(offsetof(mm7::MonstersTxtItem, prefNum) == 50);
	static_assert(offsetof(mm7::MonstersTxtItem, id) == 52);
	static_assert(offsetof(mm7::MonstersTxtItem, bloodSplat) == 54);
	static_assert(offsetof(mm7::MonstersTxtItem, spellSkill) == 56);
	static_assert(offsetof(mm7::MonstersTxtItem, spell2Skill) == 58);
	static_assert(offsetof(mm7::MonstersTxtItem, specialD) == 60);
	static_assert(offsetof(mm7::MonstersTxtItem, fullHP) == 64);
	static_assert(offsetof(mm7::MonstersTxtItem, fullHitPoints) == 64);
	static_assert(offsetof(mm7::MonstersTxtItem, armorClass) == 68);
	static_assert(offsetof(mm7::MonstersTxtItem, exp) == 72);
	static_assert(offsetof(mm7::MonstersTxtItem, experience) == 72);
	static_assert(offsetof(mm7::MonstersTxtItem, moveSpeed) == 76);
	static_assert(offsetof(mm7::MonstersTxtItem, attackRecovery) == 80);
	static_assert(offsetof(mm7::MonstersTxtItem, prefClass) == 84);
	static_assert(offsetof(mm7::MonstersTxtItem, prefers) == 84);



	struct MapMonster // size: 0x344
	{
		SKIP(32);
		// MMExt info: [MM6] Index in #Game.StreetNPC:# + 1
		// [MM7+] Index in #Game.NPC:# or index in #Game.StreetNPC:# + 5000
		int16_t NPC_ID; // 0x20 (32 decimal)
		SKIP(2);
		union
		{
			uint32_t bits; // 0x24 (36 decimal)
			struct
			{
				SKIPBITS(8); // skipping 1 bytes and 2 bits, in total 10 bits
				SKIPBITS(2);
				bool active : 1; // 0x25 (37 decimal), bit index 5
				SKIPBITS(4);
				bool showOnMap : 1; // 0x25 (37 decimal), bit index 0
				bool invisible : 1; // 0x26 (38 decimal), bit index 7
				bool noFlee : 1; // 0x26 (38 decimal), bit index 6
				SKIPBITS(1);
				bool hostile : 1; // 0x26 (38 decimal), bit index 4
				bool onAlertMap : 1; // 0x26 (38 decimal), bit index 3
				SKIPBITS(2);
				bool treasureGenerated : 1; // 0x26 (38 decimal), bit index 0
				bool showAsHostile : 1; // 0x27 (39 decimal), bit index 7
			};
		};
		union
		{
			int16_t HP; // 0x28 (40 decimal)
			int16_t hitPoints; // 0x28 (40 decimal)
		};
		SKIP(10);
		uint8_t level; // 0x34 (52 decimal)
		uint8_t treasureItemPercent; // 0x35 (53 decimal)
		uint8_t treasureDiceCount; // 0x36 (54 decimal)
		uint8_t treasureDiceSides; // 0x37 (55 decimal)
		uint8_t treasureItemLevel; // 0x38 (56 decimal)
		uint8_t treasureItemType; // 0x39 (57 decimal)
		uint8_t fly; // 0x3A (58 decimal)
		uint8_t moveType; // 0x3B (59 decimal)
		uint8_t AIType; // 0x3C (60 decimal)
		uint8_t hostileType; // 0x3D (61 decimal)
		SKIP(1);
		uint8_t bonus; // 0x3F (63 decimal) | MMExt info: (steal, curse, ...)
		uint8_t bonusMul; // 0x40 (64 decimal) | MMExt info: Disease1x5 etc. The chance that a monster would use the bonus is 'Level'*'BonusMul'
		mm7::MonsterAttackInfo attack1; // 0x41 (65 decimal)
		uint8_t attack2Chance; // 0x46 (70 decimal)
		mm7::MonsterAttackInfo attack2; // 0x47 (71 decimal)
		uint8_t spellChance; // 0x4C (76 decimal)
		uint8_t spell; // 0x4D (77 decimal)
		uint8_t spell2Chance; // 0x4E (78 decimal)
		uint8_t spell2; // 0x4F (79 decimal)
		union
		{
			struct // size: 0xA, MMExt union
			{
				uint8_t _0; // 0x50 (80 decimal)
				uint8_t _1; // 0x51 (81 decimal)
				uint8_t _2; // 0x52 (82 decimal)
				uint8_t _3; // 0x53 (83 decimal)
				uint8_t _7; // 0x54 (84 decimal)
				uint8_t _6; // 0x55 (85 decimal)
				uint8_t _8; // 0x56 (86 decimal)
				uint8_t _9; // 0x57 (87 decimal)
				uint8_t _10; // 0x58 (88 decimal)
				uint8_t _4; // 0x59 (89 decimal)
			} resistances;
			static_assert(sizeof(resistances) == 0xA, "Invalid \"resistances\" structure size");;
			struct
			{
				uint8_t fireResistance; // 0x50 (80 decimal)
				uint8_t airResistance; // 0x51 (81 decimal)
				uint8_t waterResistance; // 0x52 (82 decimal)
				uint8_t earthResistance; // 0x53 (83 decimal)
				uint8_t mindResistance; // 0x54 (84 decimal)
				uint8_t spiritResistance; // 0x55 (85 decimal)
				uint8_t bodyResistance; // 0x56 (86 decimal)
				uint8_t lightResistance; // 0x57 (87 decimal)
				uint8_t darkResistance; // 0x58 (88 decimal)
				uint8_t physResistance; // 0x59 (89 decimal)
			};
		};
		uint8_t special; // 0x5A (90 decimal) | MMExt info: 1 = shot, 2 = summon, 3 = explode
		// MMExt info: shot: C = count
		// summon: A = {RandomLevel = 0, fixed = 1} - monster level (0 means A, B or C is chosen randomly, monster index should be that of A variation. Values of 2 and 3 are the same as 1, but in MM7 before GrayFace Patch v2.1 it was causing a bug), B = {ground = 0, air = 1}, C = already summoned count (up to 3), D = monster index
		// explode: AdB + C, D = attack type
		uint8_t specialA; // 0x5B (91 decimal)
		uint8_t specialB; // 0x5C (92 decimal)
		uint8_t specialC; // 0x5D (93 decimal)
		uint8_t prefNum; // 0x5E (94 decimal) | MMExt info: Number of party members to hit using 'Attack1' & 'Attack2'
		SKIP(1);
		uint16_t id; // 0x60 (96 decimal)
		uint16_t bloodSplat; // 0x62 (98 decimal)
		uint16_t spellSkill; // 0x64 (100 decimal)
		uint16_t spell2Skill; // 0x66 (102 decimal)
		uint16_t specialD; // 0x68 (104 decimal) | MMExt info: (summoned monster or damage type in case of explosive attack)
		SKIP(2);
		union
		{
			int32_t fullHP; // 0x6C (108 decimal)
			int32_t fullHitPoints; // 0x6C (108 decimal)
		};
		int32_t armorClass; // 0x70 (112 decimal)
		union
		{
			int32_t exp; // 0x74 (116 decimal)
			int32_t experience; // 0x74 (116 decimal)
		};
		int32_t moveSpeed; // 0x78 (120 decimal)
		int32_t attackRecovery; // 0x7C (124 decimal)
		union
		{
			int32_t prefClass; // 0x80 (128 decimal)
			struct
			{
				struct // size: 0x2, MMExt union
				{
					bool knight : 1; // 0x80 (128 decimal), bit index 7
					bool paladin : 1; // 0x80 (128 decimal), bit index 6
					bool archer : 1; // 0x80 (128 decimal), bit index 5
					bool druid : 1; // 0x80 (128 decimal), bit index 4
					bool cleric : 1; // 0x80 (128 decimal), bit index 3
					bool sorcerer : 1; // 0x80 (128 decimal), bit index 2
					bool ranger : 1; // 0x80 (128 decimal), bit index 1
					bool thief : 1; // 0x80 (128 decimal), bit index 0
					bool monk : 1; // 0x81 (129 decimal), bit index 7
					bool male : 1; // 0x81 (129 decimal), bit index 6
					bool female : 1; // 0x81 (129 decimal), bit index 5
					bool human : 1; // 0x81 (129 decimal), bit index 4
					bool elf : 1; // 0x81 (129 decimal), bit index 3
					bool dwarf : 1; // 0x81 (129 decimal), bit index 2
					bool goblin : 1; // 0x81 (129 decimal), bit index 1
				} prefers;
				static_assert(sizeof(prefers) == 0x2, "Invalid \"prefers\" structure size");;
			};
		};
		int16_t rangeAttack; // 0x84 (132 decimal)
		int16_t id2; // 0x86 (134 decimal)
		int16_t bodyRadius; // 0x88 (136 decimal)
		int16_t bodyHeight; // 0x8A (138 decimal)
		int16_t velocity; // 0x8C (140 decimal)
		union
		{
			std::array<int16_t, 3> pos; // 0x8E (142 decimal)
			struct
			{
				int16_t x; // 0x8E (142 decimal)
				int16_t y; // 0x90 (144 decimal)
				int16_t z; // 0x92 (146 decimal)
			};
		};
		int16_t velocityX; // 0x94 (148 decimal)
		int16_t velocityY; // 0x96 (150 decimal)
		int16_t velocityZ; // 0x98 (152 decimal)
		int16_t direction; // 0x9A (154 decimal)
		int16_t lookAngle; // 0x9C (156 decimal)
		int16_t room; // 0x9E (158 decimal)
		int16_t currentActionLength; // 0xA0 (160 decimal)
		int16_t startX; // 0xA2 (162 decimal)
		int16_t startY; // 0xA4 (164 decimal)
		int16_t startZ; // 0xA6 (166 decimal)
		int16_t guardX; // 0xA8 (168 decimal)
		int16_t guardY; // 0xAA (170 decimal)
		int16_t guardZ; // 0xAC (172 decimal)
		int16_t guardRadius; // 0xAE (174 decimal)
		int16_t AIState; // 0xB0 (176 decimal)
		int16_t graphicState; // 0xB2 (178 decimal)
		int16_t item; // 0xB4 (180 decimal)
		SKIP(2);
		int32_t currentActionStep; // 0xB8 (184 decimal)
		union
		{
			std::array<int16_t, 8> frames; // 0xBC (188 decimal)
			struct
			{
				int16_t framesStand; // 0xBC (188 decimal)
				int16_t framesWalk; // 0xBE (190 decimal)
				int16_t framesAttack; // 0xC0 (192 decimal)
				int16_t framesShoot; // 0xC2 (194 decimal)
				union
				{
					int16_t framesStun; // 0xC4 (196 decimal)
					int16_t framesGotHit; // 0xC4 (196 decimal)
				};
				int16_t framesDie; // 0xC6 (198 decimal)
				int16_t framesDead; // 0xC8 (200 decimal)
				int16_t framesFidget; // 0xCA (202 decimal)
			};
		};
		union
		{
			std::array<int16_t, 4> sounds; // 0xCC (204 decimal)
			struct
			{
				int16_t soundAttack; // 0xCC (204 decimal)
				int16_t soundDie; // 0xCE (206 decimal)
				union
				{
					int16_t soundGotHit; // 0xD0 (208 decimal)
					int16_t soundGetHit; // 0xD0 (208 decimal)
				};
				int16_t soundFidget; // 0xD2 (210 decimal)
			};
		};
		std::array<mm7::SpellBuff, 22> spellBuffs; // 0xD4 (212 decimal)
		std::array<mm7::Item, 4> items; // 0x234 (564 decimal) | MMExt info: Indexes 0 and 1 are used for stolen items, indexes 2 and 3 are used if TreasureGenerated bit is set: index 2 holds the item and index 3 holds the gold.
		int32_t group; // 0x2C4 (708 decimal)
		int32_t ally; // 0x2C8 (712 decimal) | MMExt info: Monster class that guards or is guraded by this one. That is, !Lua[[(Id + 2):div(3)]], like in Hostile.txt.
		std::array<mm7::MonsterSchedule, 8> schedules; // 0x2CC (716 decimal)
		int32_t summoner; // 0x32C (812 decimal)
		int32_t lastAttacker; // 0x330 (816 decimal) | MMExt info: Last one who hit the monster
		int32_t nameId; // 0x334 (820 decimal) | MMExt info: From PlaceMon.txt
		SKIP(12);
		char* __thiscall updateGraphicState(); // address: 0x4597A6 | defaults: (this)
		char* __stdcall showSpellEffect(/*Color24 = 0*/); // address: 0x4A7E19 | defaults: (this), 0
		int __stdcall calcTakenDamage(/*DamageKind, Damage*/); // address: 0x427522 | defaults: (this)
		int __fastcall isAgainst(/*Mon2:structs.MapMonster*/); // address: 0x40104C | defaults: (this), 0
		bool __stdcall calcHitOrMiss(/*Player:structs.Player*/); // address: 0x427464 | defaults: (this)
		bool __thiscall calcHitByEffect(/*DamageKind*/); // address: 0x427619 | defaults: (this)
		int __thiscall loadFrames(/*SoundLoaded = false*/); // address: 0x4595D3 | defaults: (this), false
		int __thiscall chooseTargetPlayer(); // address: 0x426DC7 | defaults: (this)
	};
	static_assert(sizeof(mm7::MapMonster) == 0x344, "Invalid \"mm7::MapMonster\" structure size");
	static_assert(offsetof(mm7::MapMonster, NPC_ID) == 32);
	static_assert(offsetof(mm7::MapMonster, bits) == 36);
	static_assert(offsetof(mm7::MapMonster, HP) == 40);
	static_assert(offsetof(mm7::MapMonster, hitPoints) == 40);
	static_assert(offsetof(mm7::MapMonster, level) == 52);
	static_assert(offsetof(mm7::MapMonster, treasureItemPercent) == 53);
	static_assert(offsetof(mm7::MapMonster, treasureDiceCount) == 54);
	static_assert(offsetof(mm7::MapMonster, treasureDiceSides) == 55);
	static_assert(offsetof(mm7::MapMonster, treasureItemLevel) == 56);
	static_assert(offsetof(mm7::MapMonster, treasureItemType) == 57);
	static_assert(offsetof(mm7::MapMonster, fly) == 58);
	static_assert(offsetof(mm7::MapMonster, moveType) == 59);
	static_assert(offsetof(mm7::MapMonster, AIType) == 60);
	static_assert(offsetof(mm7::MapMonster, hostileType) == 61);
	static_assert(offsetof(mm7::MapMonster, bonus) == 63);
	static_assert(offsetof(mm7::MapMonster, bonusMul) == 64);
	static_assert(offsetof(mm7::MapMonster, attack1) == 65);
	static_assert(offsetof(mm7::MapMonster, attack2Chance) == 70);
	static_assert(offsetof(mm7::MapMonster, attack2) == 71);
	static_assert(offsetof(mm7::MapMonster, spellChance) == 76);
	static_assert(offsetof(mm7::MapMonster, spell) == 77);
	static_assert(offsetof(mm7::MapMonster, spell2Chance) == 78);
	static_assert(offsetof(mm7::MapMonster, spell2) == 79);
	static_assert(offsetof(mm7::MapMonster, resistances) == 80);
	static_assert(offsetof(mm7::MapMonster, fireResistance) == 80);
	static_assert(offsetof(mm7::MapMonster, airResistance) == 81);
	static_assert(offsetof(mm7::MapMonster, waterResistance) == 82);
	static_assert(offsetof(mm7::MapMonster, earthResistance) == 83);
	static_assert(offsetof(mm7::MapMonster, mindResistance) == 84);
	static_assert(offsetof(mm7::MapMonster, spiritResistance) == 85);
	static_assert(offsetof(mm7::MapMonster, bodyResistance) == 86);
	static_assert(offsetof(mm7::MapMonster, lightResistance) == 87);
	static_assert(offsetof(mm7::MapMonster, darkResistance) == 88);
	static_assert(offsetof(mm7::MapMonster, physResistance) == 89);
	static_assert(offsetof(mm7::MapMonster, special) == 90);
	static_assert(offsetof(mm7::MapMonster, specialA) == 91);
	static_assert(offsetof(mm7::MapMonster, specialB) == 92);
	static_assert(offsetof(mm7::MapMonster, specialC) == 93);
	static_assert(offsetof(mm7::MapMonster, prefNum) == 94);
	static_assert(offsetof(mm7::MapMonster, id) == 96);
	static_assert(offsetof(mm7::MapMonster, bloodSplat) == 98);
	static_assert(offsetof(mm7::MapMonster, spellSkill) == 100);
	static_assert(offsetof(mm7::MapMonster, spell2Skill) == 102);
	static_assert(offsetof(mm7::MapMonster, specialD) == 104);
	static_assert(offsetof(mm7::MapMonster, fullHP) == 108);
	static_assert(offsetof(mm7::MapMonster, fullHitPoints) == 108);
	static_assert(offsetof(mm7::MapMonster, armorClass) == 112);
	static_assert(offsetof(mm7::MapMonster, exp) == 116);
	static_assert(offsetof(mm7::MapMonster, experience) == 116);
	static_assert(offsetof(mm7::MapMonster, moveSpeed) == 120);
	static_assert(offsetof(mm7::MapMonster, attackRecovery) == 124);
	static_assert(offsetof(mm7::MapMonster, prefClass) == 128);
	static_assert(offsetof(mm7::MapMonster, prefers) == 128);
	static_assert(offsetof(mm7::MapMonster, rangeAttack) == 132);
	static_assert(offsetof(mm7::MapMonster, id2) == 134);
	static_assert(offsetof(mm7::MapMonster, bodyRadius) == 136);
	static_assert(offsetof(mm7::MapMonster, bodyHeight) == 138);
	static_assert(offsetof(mm7::MapMonster, velocity) == 140);
	static_assert(offsetof(mm7::MapMonster, pos) == 142);
	static_assert(offsetof(mm7::MapMonster, x) == 142);
	static_assert(offsetof(mm7::MapMonster, y) == 144);
	static_assert(offsetof(mm7::MapMonster, z) == 146);
	static_assert(offsetof(mm7::MapMonster, velocityX) == 148);
	static_assert(offsetof(mm7::MapMonster, velocityY) == 150);
	static_assert(offsetof(mm7::MapMonster, velocityZ) == 152);
	static_assert(offsetof(mm7::MapMonster, direction) == 154);
	static_assert(offsetof(mm7::MapMonster, lookAngle) == 156);
	static_assert(offsetof(mm7::MapMonster, room) == 158);
	static_assert(offsetof(mm7::MapMonster, currentActionLength) == 160);
	static_assert(offsetof(mm7::MapMonster, startX) == 162);
	static_assert(offsetof(mm7::MapMonster, startY) == 164);
	static_assert(offsetof(mm7::MapMonster, startZ) == 166);
	static_assert(offsetof(mm7::MapMonster, guardX) == 168);
	static_assert(offsetof(mm7::MapMonster, guardY) == 170);
	static_assert(offsetof(mm7::MapMonster, guardZ) == 172);
	static_assert(offsetof(mm7::MapMonster, guardRadius) == 174);
	static_assert(offsetof(mm7::MapMonster, AIState) == 176);
	static_assert(offsetof(mm7::MapMonster, graphicState) == 178);
	static_assert(offsetof(mm7::MapMonster, item) == 180);
	static_assert(offsetof(mm7::MapMonster, currentActionStep) == 184);
	static_assert(offsetof(mm7::MapMonster, frames) == 188);
	static_assert(offsetof(mm7::MapMonster, framesStand) == 188);
	static_assert(offsetof(mm7::MapMonster, framesWalk) == 190);
	static_assert(offsetof(mm7::MapMonster, framesAttack) == 192);
	static_assert(offsetof(mm7::MapMonster, framesShoot) == 194);
	static_assert(offsetof(mm7::MapMonster, framesStun) == 196);
	static_assert(offsetof(mm7::MapMonster, framesGotHit) == 196);
	static_assert(offsetof(mm7::MapMonster, framesDie) == 198);
	static_assert(offsetof(mm7::MapMonster, framesDead) == 200);
	static_assert(offsetof(mm7::MapMonster, framesFidget) == 202);
	static_assert(offsetof(mm7::MapMonster, sounds) == 204);
	static_assert(offsetof(mm7::MapMonster, soundAttack) == 204);
	static_assert(offsetof(mm7::MapMonster, soundDie) == 206);
	static_assert(offsetof(mm7::MapMonster, soundGotHit) == 208);
	static_assert(offsetof(mm7::MapMonster, soundGetHit) == 208);
	static_assert(offsetof(mm7::MapMonster, soundFidget) == 210);
	static_assert(offsetof(mm7::MapMonster, spellBuffs) == 212);
	static_assert(offsetof(mm7::MapMonster, items) == 564);
	static_assert(offsetof(mm7::MapMonster, group) == 708);
	static_assert(offsetof(mm7::MapMonster, ally) == 712);
	static_assert(offsetof(mm7::MapMonster, schedules) == 716);
	static_assert(offsetof(mm7::MapMonster, summoner) == 812);
	static_assert(offsetof(mm7::MapMonster, lastAttacker) == 816);
	static_assert(offsetof(mm7::MapMonster, nameId) == 820);
}
namespace mm8
{
	struct MonsterKind // size: 0x8
	{
		bool undead; // 0x0 (0 decimal)
		bool dragon; // 0x1 (1 decimal)
		bool swimmer; // 0x2 (2 decimal)
		bool immobile; // 0x3 (3 decimal)
		bool peasant; // 0x4 (4 decimal)
		bool noArena; // 0x5 (5 decimal)
		bool ogre; // 0x6 (6 decimal)
		bool elemental; // 0x7 (7 decimal)
	};
	static_assert(sizeof(mm8::MonsterKind) == 0x8, "Invalid \"mm8::MonsterKind\" structure size");
	static_assert(offsetof(mm8::MonsterKind, dragon) == 1);
	static_assert(offsetof(mm8::MonsterKind, swimmer) == 2);
	static_assert(offsetof(mm8::MonsterKind, immobile) == 3);
	static_assert(offsetof(mm8::MonsterKind, peasant) == 4);
	static_assert(offsetof(mm8::MonsterKind, noArena) == 5);
	static_assert(offsetof(mm8::MonsterKind, ogre) == 6);
	static_assert(offsetof(mm8::MonsterKind, elemental) == 7);



	struct MonsterSchedule // size: 0xC
	{
		union
		{
			std::array<int16_t, 3> pos; // 0x0 (0 decimal)
			struct
			{
				int16_t x; // 0x0 (0 decimal)
				int16_t y; // 0x2 (2 decimal)
				int16_t z; // 0x4 (4 decimal)
			};
		};
		uint16_t bits; // 0x6 (6 decimal) | MMExt info: (1 - on)
		uint8_t action; // 0x8 (8 decimal)
		uint8_t hour; // 0x9 (9 decimal)
		uint8_t day; // 0xA (10 decimal)
		uint8_t month; // 0xB (11 decimal)
	};
	static_assert(sizeof(mm8::MonsterSchedule) == 0xC, "Invalid \"mm8::MonsterSchedule\" structure size");
	static_assert(offsetof(mm8::MonsterSchedule, y) == 2);
	static_assert(offsetof(mm8::MonsterSchedule, z) == 4);
	static_assert(offsetof(mm8::MonsterSchedule, bits) == 6);
	static_assert(offsetof(mm8::MonsterSchedule, action) == 8);
	static_assert(offsetof(mm8::MonsterSchedule, hour) == 9);
	static_assert(offsetof(mm8::MonsterSchedule, day) == 10);
	static_assert(offsetof(mm8::MonsterSchedule, month) == 11);



	struct MonsterAttackInfo // size: 0x5
	{
		uint8_t type; // 0x0 (0 decimal)
		uint8_t damageDiceCount; // 0x1 (1 decimal)
		uint8_t damageDiceSides; // 0x2 (2 decimal)
		uint8_t damageAdd; // 0x3 (3 decimal)
		uint8_t missile; // 0x4 (4 decimal)
	};
	static_assert(sizeof(mm8::MonsterAttackInfo) == 0x5, "Invalid \"mm8::MonsterAttackInfo\" structure size");
	static_assert(offsetof(mm8::MonsterAttackInfo, damageDiceCount) == 1);
	static_assert(offsetof(mm8::MonsterAttackInfo, damageDiceSides) == 2);
	static_assert(offsetof(mm8::MonsterAttackInfo, damageAdd) == 3);
	static_assert(offsetof(mm8::MonsterAttackInfo, missile) == 4);



	struct MonstersTxtItem // size: 0x60
	{
		char* name; // EditPChar | 0x0 (0 decimal)
		char* picture; // EditPChar | 0x4 (4 decimal)
		uint8_t level; // 0x8 (8 decimal)
		uint8_t treasureItemPercent; // 0x9 (9 decimal)
		uint8_t treasureDiceCount; // 0xA (10 decimal)
		uint8_t treasureDiceSides; // 0xB (11 decimal)
		uint8_t treasureItemLevel; // 0xC (12 decimal)
		uint8_t treasureItemType; // 0xD (13 decimal)
		uint8_t fly; // 0xE (14 decimal)
		uint8_t moveType; // 0xF (15 decimal)
		uint8_t AIType; // 0x10 (16 decimal)
		uint8_t hostileType; // 0x11 (17 decimal)
		SKIP(1);
		uint8_t bonus; // 0x13 (19 decimal) | MMExt info: (steal, curse, ...)
		uint8_t bonusMul; // 0x14 (20 decimal) | MMExt info: Disease1x5 etc. The chance that a monster would use the bonus is 'Level'*'BonusMul'
		mm8::MonsterAttackInfo attack1; // 0x15 (21 decimal)
		uint8_t attack2Chance; // 0x1A (26 decimal)
		mm8::MonsterAttackInfo attack2; // 0x1B (27 decimal)
		uint8_t spellChance; // 0x20 (32 decimal)
		uint8_t spell; // 0x21 (33 decimal)
		uint8_t spell2Chance; // 0x22 (34 decimal)
		uint8_t spell2; // 0x23 (35 decimal)
		union
		{
			struct // size: 0x14, MMExt union
			{
				uint16_t _0; // 0x24 (36 decimal)
				uint16_t _1; // 0x26 (38 decimal)
				uint16_t _2; // 0x28 (40 decimal)
				uint16_t _3; // 0x2A (42 decimal)
				uint16_t _7; // 0x2C (44 decimal)
				uint16_t _6; // 0x2E (46 decimal)
				uint16_t _8; // 0x30 (48 decimal)
				uint16_t _9; // 0x32 (50 decimal)
				uint16_t _10; // 0x34 (52 decimal)
				uint16_t _4; // 0x36 (54 decimal)
			} resistances;
			static_assert(sizeof(resistances) == 0x14, "Invalid \"resistances\" structure size");;
			struct
			{
				uint16_t fireResistance; // 0x24 (36 decimal)
				uint16_t airResistance; // 0x26 (38 decimal)
				uint16_t waterResistance; // 0x28 (40 decimal)
				uint16_t earthResistance; // 0x2A (42 decimal)
				uint16_t mindResistance; // 0x2C (44 decimal)
				uint16_t spiritResistance; // 0x2E (46 decimal)
				uint16_t bodyResistance; // 0x30 (48 decimal)
				uint16_t lightResistance; // 0x32 (50 decimal)
				uint16_t darkResistance; // 0x34 (52 decimal)
				uint16_t physResistance; // 0x36 (54 decimal)
			};
		};
		uint8_t special; // 0x38 (56 decimal) | MMExt info: 1 = shot, 2 = summon, 3 = explode
		// MMExt info: shot: C = count
		// summon: A = {RandomLevel = 0, fixed = 1} - monster level (0 means A, B or C is chosen randomly, monster index should be that of A variation. Values of 2 and 3 are the same as 1, but in MM7 before GrayFace Patch v2.1 it was causing a bug), B = {ground = 0, air = 1}, C = already summoned count (up to 3), D = monster index
		// explode: AdB + C, D = attack type
		uint8_t specialA; // 0x39 (57 decimal)
		uint8_t specialB; // 0x3A (58 decimal)
		uint8_t specialC; // 0x3B (59 decimal)
		uint8_t prefNum; // 0x3C (60 decimal) | MMExt info: Number of party members to hit using 'Attack1' & 'Attack2'
		SKIP(1);
		uint16_t id; // 0x3E (62 decimal)
		uint16_t bloodSplat; // 0x40 (64 decimal)
		uint16_t spellSkill; // 0x42 (66 decimal)
		uint16_t spell2Skill; // 0x44 (68 decimal)
		uint16_t specialD; // 0x46 (70 decimal) | MMExt info: (summoned monster or damage type in case of explosive attack)
		union
		{
			int32_t fullHP; // 0x48 (72 decimal)
			int32_t fullHitPoints; // 0x48 (72 decimal)
		};
		int32_t armorClass; // 0x4C (76 decimal)
		union
		{
			int32_t exp; // 0x50 (80 decimal)
			int32_t experience; // 0x50 (80 decimal)
		};
		int32_t moveSpeed; // 0x54 (84 decimal)
		int32_t attackRecovery; // 0x58 (88 decimal)
		union
		{
			int32_t prefClass; // 0x5C (92 decimal)
			struct
			{
				struct // size: 0x2, MMExt union
				{
					bool necro : 1; // 0x5C (92 decimal), bit index 7
					bool cleric : 1; // 0x5C (92 decimal), bit index 6
					bool knight : 1; // 0x5C (92 decimal), bit index 5
					bool troll : 1; // 0x5C (92 decimal), bit index 4
					bool minotaur : 1; // 0x5C (92 decimal), bit index 3
					bool darkElf : 1; // 0x5D (93 decimal), bit index 2
					bool vampire : 1; // 0x5D (93 decimal), bit index 1
					bool dragon : 1; // 0x5D (93 decimal), bit index 0
					bool male : 1; // 0x5D (93 decimal), bit index 7
					bool female : 1; // 0x5D (93 decimal), bit index 6
				} prefers;
				static_assert(sizeof(prefers) == 0x2, "Invalid \"prefers\" structure size");;
			};
		};
	};
	static_assert(sizeof(mm8::MonstersTxtItem) == 0x60, "Invalid \"mm8::MonstersTxtItem\" structure size");
	static_assert(offsetof(mm8::MonstersTxtItem, picture) == 4);
	static_assert(offsetof(mm8::MonstersTxtItem, level) == 8);
	static_assert(offsetof(mm8::MonstersTxtItem, treasureItemPercent) == 9);
	static_assert(offsetof(mm8::MonstersTxtItem, treasureDiceCount) == 10);
	static_assert(offsetof(mm8::MonstersTxtItem, treasureDiceSides) == 11);
	static_assert(offsetof(mm8::MonstersTxtItem, treasureItemLevel) == 12);
	static_assert(offsetof(mm8::MonstersTxtItem, treasureItemType) == 13);
	static_assert(offsetof(mm8::MonstersTxtItem, fly) == 14);
	static_assert(offsetof(mm8::MonstersTxtItem, moveType) == 15);
	static_assert(offsetof(mm8::MonstersTxtItem, AIType) == 16);
	static_assert(offsetof(mm8::MonstersTxtItem, hostileType) == 17);
	static_assert(offsetof(mm8::MonstersTxtItem, bonus) == 19);
	static_assert(offsetof(mm8::MonstersTxtItem, bonusMul) == 20);
	static_assert(offsetof(mm8::MonstersTxtItem, attack1) == 21);
	static_assert(offsetof(mm8::MonstersTxtItem, attack2Chance) == 26);
	static_assert(offsetof(mm8::MonstersTxtItem, attack2) == 27);
	static_assert(offsetof(mm8::MonstersTxtItem, spellChance) == 32);
	static_assert(offsetof(mm8::MonstersTxtItem, spell) == 33);
	static_assert(offsetof(mm8::MonstersTxtItem, spell2Chance) == 34);
	static_assert(offsetof(mm8::MonstersTxtItem, spell2) == 35);
	static_assert(offsetof(mm8::MonstersTxtItem, resistances) == 36);
	static_assert(offsetof(mm8::MonstersTxtItem, fireResistance) == 36);
	static_assert(offsetof(mm8::MonstersTxtItem, airResistance) == 38);
	static_assert(offsetof(mm8::MonstersTxtItem, waterResistance) == 40);
	static_assert(offsetof(mm8::MonstersTxtItem, earthResistance) == 42);
	static_assert(offsetof(mm8::MonstersTxtItem, mindResistance) == 44);
	static_assert(offsetof(mm8::MonstersTxtItem, spiritResistance) == 46);
	static_assert(offsetof(mm8::MonstersTxtItem, bodyResistance) == 48);
	static_assert(offsetof(mm8::MonstersTxtItem, lightResistance) == 50);
	static_assert(offsetof(mm8::MonstersTxtItem, darkResistance) == 52);
	static_assert(offsetof(mm8::MonstersTxtItem, physResistance) == 54);
	static_assert(offsetof(mm8::MonstersTxtItem, special) == 56);
	static_assert(offsetof(mm8::MonstersTxtItem, specialA) == 57);
	static_assert(offsetof(mm8::MonstersTxtItem, specialB) == 58);
	static_assert(offsetof(mm8::MonstersTxtItem, specialC) == 59);
	static_assert(offsetof(mm8::MonstersTxtItem, prefNum) == 60);
	static_assert(offsetof(mm8::MonstersTxtItem, id) == 62);
	static_assert(offsetof(mm8::MonstersTxtItem, bloodSplat) == 64);
	static_assert(offsetof(mm8::MonstersTxtItem, spellSkill) == 66);
	static_assert(offsetof(mm8::MonstersTxtItem, spell2Skill) == 68);
	static_assert(offsetof(mm8::MonstersTxtItem, specialD) == 70);
	static_assert(offsetof(mm8::MonstersTxtItem, fullHP) == 72);
	static_assert(offsetof(mm8::MonstersTxtItem, fullHitPoints) == 72);
	static_assert(offsetof(mm8::MonstersTxtItem, armorClass) == 76);
	static_assert(offsetof(mm8::MonstersTxtItem, exp) == 80);
	static_assert(offsetof(mm8::MonstersTxtItem, experience) == 80);
	static_assert(offsetof(mm8::MonstersTxtItem, moveSpeed) == 84);
	static_assert(offsetof(mm8::MonstersTxtItem, attackRecovery) == 88);
	static_assert(offsetof(mm8::MonstersTxtItem, prefClass) == 92);
	static_assert(offsetof(mm8::MonstersTxtItem, prefers) == 92);



	struct MapMonster // size: 0x3CC
	{
		SKIP(32);
		// MMExt info: [MM6] Index in #Game.StreetNPC:structs.GameStructure.StreetNPC# + 1
		// [MM7+] Index in #Game.NPC:structs.GameStructure.NPC# or index in #Game.StreetNPC:structs.GameStructure.StreetNPC# + 5000
		int16_t NPC_ID; // 0x20 (32 decimal)
		SKIP(2);
		union
		{
			uint32_t bits; // 0x24 (36 decimal)
			struct
			{
				SKIPBITS(8); // skipping 1 bytes and 2 bits, in total 10 bits
				SKIPBITS(2);
				bool active : 1; // 0x25 (37 decimal), bit index 5
				SKIPBITS(4);
				bool showOnMap : 1; // 0x26 (38 decimal), bit index 0
				bool invisible : 1; // 0x26 (38 decimal), bit index 7
				bool noFlee : 1; // 0x26 (38 decimal), bit index 6
				SKIPBITS(1);
				bool hostile : 1; // 0x26 (38 decimal), bit index 4
				bool onAlertMap : 1; // 0x26 (38 decimal), bit index 3
				SKIPBITS(2);
				bool treasureGenerated : 1; // 0x27 (39 decimal), bit index 0
				bool showAsHostile : 1; // 0x27 (39 decimal), bit index 7
				bool isObeliskChest : 1; // 0x27 (39 decimal), bit index 6
			};
		};
		union
		{
			int16_t HP; // 0x28 (40 decimal)
			int16_t hitPoints; // 0x28 (40 decimal)
		};
		SKIP(10);
		uint8_t level; // 0x34 (52 decimal)
		uint8_t treasureItemPercent; // 0x35 (53 decimal)
		uint8_t treasureDiceCount; // 0x36 (54 decimal)
		uint8_t treasureDiceSides; // 0x37 (55 decimal)
		uint8_t treasureItemLevel; // 0x38 (56 decimal)
		uint8_t treasureItemType; // 0x39 (57 decimal)
		uint8_t fly; // 0x3A (58 decimal)
		uint8_t moveType; // 0x3B (59 decimal)
		uint8_t AIType; // 0x3C (60 decimal)
		uint8_t hostileType; // 0x3D (61 decimal)
		SKIP(1);
		uint8_t bonus; // 0x3F (63 decimal) | MMExt info: (steal, curse, ...)
		uint8_t bonusMul; // 0x40 (64 decimal) | MMExt info: Disease1x5 etc. The chance that a monster would use the bonus is 'Level'*'BonusMul'
		mm8::MonsterAttackInfo attack1; // 0x41 (65 decimal)
		uint8_t attack2Chance; // 0x46 (70 decimal)
		mm8::MonsterAttackInfo attack2; // 0x47 (71 decimal)
		uint8_t spellChance; // 0x4C (76 decimal)
		uint8_t spell; // 0x4D (77 decimal)
		uint8_t spell2Chance; // 0x4E (78 decimal)
		uint8_t spell2; // 0x4F (79 decimal)
		union
		{
			struct // size: 0x14, MMExt union
			{
				uint16_t _0; // 0x50 (80 decimal)
				uint16_t _1; // 0x52 (82 decimal)
				uint16_t _2; // 0x54 (84 decimal)
				uint16_t _3; // 0x56 (86 decimal)
				uint16_t _7; // 0x58 (88 decimal)
				uint16_t _6; // 0x5A (90 decimal)
				uint16_t _8; // 0x5C (92 decimal)
				uint16_t _9; // 0x5E (94 decimal)
				uint16_t _10; // 0x60 (96 decimal)
				uint16_t _4; // 0x62 (98 decimal)
			} resistances;
			static_assert(sizeof(resistances) == 0x14, "Invalid \"resistances\" structure size");;
			struct
			{
				uint16_t fireResistance; // 0x50 (80 decimal)
				uint16_t airResistance; // 0x52 (82 decimal)
				uint16_t waterResistance; // 0x54 (84 decimal)
				uint16_t earthResistance; // 0x56 (86 decimal)
				uint16_t mindResistance; // 0x58 (88 decimal)
				uint16_t spiritResistance; // 0x5A (90 decimal)
				uint16_t bodyResistance; // 0x5C (92 decimal)
				uint16_t lightResistance; // 0x5E (94 decimal)
				uint16_t darkResistance; // 0x60 (96 decimal)
				uint16_t physResistance; // 0x62 (98 decimal)
			};
		};
		uint8_t special; // 0x64 (100 decimal) | MMExt info: 1 = shot, 2 = summon, 3 = explode
		// MMExt info: shot: C = count
		// summon: A = {RandomLevel = 0, fixed = 1} - monster level (0 means A, B or C is chosen randomly, monster index should be that of A variation. Values of 2 and 3 are the same as 1, but in MM7 before GrayFace Patch v2.1 it was causing a bug), B = {ground = 0, air = 1}, C = already summoned count (up to 3), D = monster index
		// explode: AdB + C, D = attack type
		uint8_t specialA; // 0x65 (101 decimal)
		uint8_t specialB; // 0x66 (102 decimal)
		uint8_t specialC; // 0x67 (103 decimal)
		uint8_t prefNum; // 0x68 (104 decimal) | MMExt info: Number of party members to hit using 'Attack1' & 'Attack2'
		SKIP(1);
		uint16_t id; // 0x6A (106 decimal)
		uint16_t bloodSplat; // 0x6C (108 decimal)
		uint16_t spellSkill; // 0x6E (110 decimal)
		uint16_t spell2Skill; // 0x70 (112 decimal)
		uint16_t specialD; // 0x72 (114 decimal) | MMExt info: (summoned monster or damage type in case of explosive attack)
		union
		{
			int32_t fullHP; // 0x74 (116 decimal)
			int32_t fullHitPoints; // 0x74 (116 decimal)
		};
		int32_t armorClass; // 0x78 (120 decimal)
		union
		{
			int32_t exp; // 0x7C (124 decimal)
			int32_t experience; // 0x7C (124 decimal)
		};
		int32_t moveSpeed; // 0x80 (128 decimal)
		int32_t attackRecovery; // 0x84 (132 decimal)
		union
		{
			int32_t prefClass; // 0x88 (136 decimal)
			struct
			{
				struct // size: 0x2, MMExt union
				{
					bool necro : 1; // 0x88 (136 decimal), bit index 7
					bool cleric : 1; // 0x88 (136 decimal), bit index 6
					bool knight : 1; // 0x88 (136 decimal), bit index 5
					bool troll : 1; // 0x88 (136 decimal), bit index 4
					bool minotaur : 1; // 0x88 (136 decimal), bit index 3
					bool darkElf : 1; // 0x89 (137 decimal), bit index 2
					bool vampire : 1; // 0x89 (137 decimal), bit index 1
					bool dragon : 1; // 0x89 (137 decimal), bit index 0
					bool male : 1; // 0x89 (137 decimal), bit index 7
					bool female : 1; // 0x89 (137 decimal), bit index 6
				} prefers;
				static_assert(sizeof(prefers) == 0x2, "Invalid \"prefers\" structure size");;
			};
		};
		int16_t rangeAttack; // 0x8C (140 decimal)
		int16_t id2; // 0x8E (142 decimal)
		int16_t bodyRadius; // 0x90 (144 decimal)
		int16_t bodyHeight; // 0x92 (146 decimal)
		int16_t velocity; // 0x94 (148 decimal)
		union
		{
			std::array<int16_t, 3> pos; // 0x96 (150 decimal)
			struct
			{
				int16_t x; // 0x96 (150 decimal)
				int16_t y; // 0x98 (152 decimal)
				int16_t z; // 0x9A (154 decimal)
			};
		};
		int16_t velocityX; // 0x9C (156 decimal)
		int16_t velocityY; // 0x9E (158 decimal)
		int16_t velocityZ; // 0xA0 (160 decimal)
		int16_t direction; // 0xA2 (162 decimal)
		int16_t lookAngle; // 0xA4 (164 decimal)
		int16_t room; // 0xA6 (166 decimal)
		int16_t currentActionLength; // 0xA8 (168 decimal)
		int16_t startX; // 0xAA (170 decimal)
		int16_t startY; // 0xAC (172 decimal)
		int16_t startZ; // 0xAE (174 decimal)
		int16_t guardX; // 0xB0 (176 decimal)
		int16_t guardY; // 0xB2 (178 decimal)
		int16_t guardZ; // 0xB4 (180 decimal)
		int16_t guardRadius; // 0xB6 (182 decimal)
		int16_t AIState; // 0xB8 (184 decimal)
		int16_t graphicState; // 0xBA (186 decimal)
		int16_t item; // 0xBC (188 decimal)
		SKIP(2);
		int32_t currentActionStep; // 0xC0 (192 decimal)
		union
		{
			std::array<int16_t, 8> frames; // 0xC4 (196 decimal)
			struct
			{
				int16_t framesStand; // 0xC4 (196 decimal)
				int16_t framesWalk; // 0xC6 (198 decimal)
				int16_t framesAttack; // 0xC8 (200 decimal)
				int16_t framesShoot; // 0xCA (202 decimal)
				union
				{
					int16_t framesStun; // 0xCC (204 decimal)
					int16_t framesGotHit; // 0xCC (204 decimal)
				};
				int16_t framesDie; // 0xCE (206 decimal)
				int16_t framesDead; // 0xD0 (208 decimal)
				int16_t framesFidget; // 0xD2 (210 decimal)
			};
		};
		union
		{
			std::array<int16_t, 4> sounds; // 0xD4 (212 decimal)
			struct
			{
				int16_t soundAttack; // 0xD4 (212 decimal)
				int16_t soundDie; // 0xD6 (214 decimal)
				union
				{
					int16_t soundGotHit; // 0xD8 (216 decimal)
					int16_t soundGetHit; // 0xD8 (216 decimal)
				};
				int16_t soundFidget; // 0xDA (218 decimal)
			};
		};
		std::array<mm8::SpellBuff, 30> spellBuffs; // 0xDC (220 decimal)
		std::array<mm8::Item, 4> items; // 0x2BC (700 decimal) | MMExt info: Indexes 0 and 1 are used for stolen items, indexes 2 and 3 are used if TreasureGenerated bit is set: index 2 holds the item and index 3 holds the gold.
		int32_t group; // 0x34C (844 decimal)
		int32_t ally; // 0x350 (848 decimal) | MMExt info: Monster class that guards or is guraded by this one. That is, !Lua[[(Id + 2):div(3)]], like in Hostile.txt.
		std::array<mm8::MonsterSchedule, 8> schedules; // 0x354 (852 decimal)
		int32_t summoner; // 0x3B4 (948 decimal)
		int32_t lastAttacker; // 0x3B8 (952 decimal) | MMExt info: Last one who hit the monster
		int32_t nameId; // 0x3BC (956 decimal) | MMExt info: From PlaceMon.txt
		SKIP(12);
		int __fastcall isAgainst(/*Mon2:structs.MapMonster*/); // address: 0x401051 | defaults: (this), 0
		int __thiscall loadFrames(/*SoundLoaded = false*/); // address: 0x456E90 | defaults: (this), false
		int __thiscall chooseTargetPlayer(); // address: 0x425203 | defaults: (this)
		bool __thiscall calcHitByEffect(/*DamageKind*/); // address: 0x425A4F | defaults: (this)
		char* __stdcall showSpellEffect(/*Color24 = 0*/); // address: 0x4A63FA | defaults: (this), 0
		bool __thiscall calcTakenDamage(/*DamageKind, Damage*/); // address: 0x425951 | defaults: (this)
		char* __thiscall updateGraphicState(); // address: 0x457060 | defaults: (this)
		bool __stdcall calcHitOrMiss(/*Player:structs.Player*/); // address: 0x425893 | defaults: (this)
	};
	static_assert(sizeof(mm8::MapMonster) == 0x3CC, "Invalid \"mm8::MapMonster\" structure size");
	static_assert(offsetof(mm8::MapMonster, NPC_ID) == 32);
	static_assert(offsetof(mm8::MapMonster, bits) == 36);
	static_assert(offsetof(mm8::MapMonster, HP) == 40);
	static_assert(offsetof(mm8::MapMonster, hitPoints) == 40);
	static_assert(offsetof(mm8::MapMonster, level) == 52);
	static_assert(offsetof(mm8::MapMonster, treasureItemPercent) == 53);
	static_assert(offsetof(mm8::MapMonster, treasureDiceCount) == 54);
	static_assert(offsetof(mm8::MapMonster, treasureDiceSides) == 55);
	static_assert(offsetof(mm8::MapMonster, treasureItemLevel) == 56);
	static_assert(offsetof(mm8::MapMonster, treasureItemType) == 57);
	static_assert(offsetof(mm8::MapMonster, fly) == 58);
	static_assert(offsetof(mm8::MapMonster, moveType) == 59);
	static_assert(offsetof(mm8::MapMonster, AIType) == 60);
	static_assert(offsetof(mm8::MapMonster, hostileType) == 61);
	static_assert(offsetof(mm8::MapMonster, bonus) == 63);
	static_assert(offsetof(mm8::MapMonster, bonusMul) == 64);
	static_assert(offsetof(mm8::MapMonster, attack1) == 65);
	static_assert(offsetof(mm8::MapMonster, attack2Chance) == 70);
	static_assert(offsetof(mm8::MapMonster, attack2) == 71);
	static_assert(offsetof(mm8::MapMonster, spellChance) == 76);
	static_assert(offsetof(mm8::MapMonster, spell) == 77);
	static_assert(offsetof(mm8::MapMonster, spell2Chance) == 78);
	static_assert(offsetof(mm8::MapMonster, spell2) == 79);
	static_assert(offsetof(mm8::MapMonster, resistances) == 80);
	static_assert(offsetof(mm8::MapMonster, fireResistance) == 80);
	static_assert(offsetof(mm8::MapMonster, airResistance) == 82);
	static_assert(offsetof(mm8::MapMonster, waterResistance) == 84);
	static_assert(offsetof(mm8::MapMonster, earthResistance) == 86);
	static_assert(offsetof(mm8::MapMonster, mindResistance) == 88);
	static_assert(offsetof(mm8::MapMonster, spiritResistance) == 90);
	static_assert(offsetof(mm8::MapMonster, bodyResistance) == 92);
	static_assert(offsetof(mm8::MapMonster, lightResistance) == 94);
	static_assert(offsetof(mm8::MapMonster, darkResistance) == 96);
	static_assert(offsetof(mm8::MapMonster, physResistance) == 98);
	static_assert(offsetof(mm8::MapMonster, special) == 100);
	static_assert(offsetof(mm8::MapMonster, specialA) == 101);
	static_assert(offsetof(mm8::MapMonster, specialB) == 102);
	static_assert(offsetof(mm8::MapMonster, specialC) == 103);
	static_assert(offsetof(mm8::MapMonster, prefNum) == 104);
	static_assert(offsetof(mm8::MapMonster, id) == 106);
	static_assert(offsetof(mm8::MapMonster, bloodSplat) == 108);
	static_assert(offsetof(mm8::MapMonster, spellSkill) == 110);
	static_assert(offsetof(mm8::MapMonster, spell2Skill) == 112);
	static_assert(offsetof(mm8::MapMonster, specialD) == 114);
	static_assert(offsetof(mm8::MapMonster, fullHP) == 116);
	static_assert(offsetof(mm8::MapMonster, fullHitPoints) == 116);
	static_assert(offsetof(mm8::MapMonster, armorClass) == 120);
	static_assert(offsetof(mm8::MapMonster, exp) == 124);
	static_assert(offsetof(mm8::MapMonster, experience) == 124);
	static_assert(offsetof(mm8::MapMonster, moveSpeed) == 128);
	static_assert(offsetof(mm8::MapMonster, attackRecovery) == 132);
	static_assert(offsetof(mm8::MapMonster, prefClass) == 136);
	static_assert(offsetof(mm8::MapMonster, prefers) == 136);
	static_assert(offsetof(mm8::MapMonster, rangeAttack) == 140);
	static_assert(offsetof(mm8::MapMonster, id2) == 142);
	static_assert(offsetof(mm8::MapMonster, bodyRadius) == 144);
	static_assert(offsetof(mm8::MapMonster, bodyHeight) == 146);
	static_assert(offsetof(mm8::MapMonster, velocity) == 148);
	static_assert(offsetof(mm8::MapMonster, pos) == 150);
	static_assert(offsetof(mm8::MapMonster, x) == 150);
	static_assert(offsetof(mm8::MapMonster, y) == 152);
	static_assert(offsetof(mm8::MapMonster, z) == 154);
	static_assert(offsetof(mm8::MapMonster, velocityX) == 156);
	static_assert(offsetof(mm8::MapMonster, velocityY) == 158);
	static_assert(offsetof(mm8::MapMonster, velocityZ) == 160);
	static_assert(offsetof(mm8::MapMonster, direction) == 162);
	static_assert(offsetof(mm8::MapMonster, lookAngle) == 164);
	static_assert(offsetof(mm8::MapMonster, room) == 166);
	static_assert(offsetof(mm8::MapMonster, currentActionLength) == 168);
	static_assert(offsetof(mm8::MapMonster, startX) == 170);
	static_assert(offsetof(mm8::MapMonster, startY) == 172);
	static_assert(offsetof(mm8::MapMonster, startZ) == 174);
	static_assert(offsetof(mm8::MapMonster, guardX) == 176);
	static_assert(offsetof(mm8::MapMonster, guardY) == 178);
	static_assert(offsetof(mm8::MapMonster, guardZ) == 180);
	static_assert(offsetof(mm8::MapMonster, guardRadius) == 182);
	static_assert(offsetof(mm8::MapMonster, AIState) == 184);
	static_assert(offsetof(mm8::MapMonster, graphicState) == 186);
	static_assert(offsetof(mm8::MapMonster, item) == 188);
	static_assert(offsetof(mm8::MapMonster, currentActionStep) == 192);
	static_assert(offsetof(mm8::MapMonster, frames) == 196);
	static_assert(offsetof(mm8::MapMonster, framesStand) == 196);
	static_assert(offsetof(mm8::MapMonster, framesWalk) == 198);
	static_assert(offsetof(mm8::MapMonster, framesAttack) == 200);
	static_assert(offsetof(mm8::MapMonster, framesShoot) == 202);
	static_assert(offsetof(mm8::MapMonster, framesStun) == 204);
	static_assert(offsetof(mm8::MapMonster, framesGotHit) == 204);
	static_assert(offsetof(mm8::MapMonster, framesDie) == 206);
	static_assert(offsetof(mm8::MapMonster, framesDead) == 208);
	static_assert(offsetof(mm8::MapMonster, framesFidget) == 210);
	static_assert(offsetof(mm8::MapMonster, sounds) == 212);
	static_assert(offsetof(mm8::MapMonster, soundAttack) == 212);
	static_assert(offsetof(mm8::MapMonster, soundDie) == 214);
	static_assert(offsetof(mm8::MapMonster, soundGotHit) == 216);
	static_assert(offsetof(mm8::MapMonster, soundGetHit) == 216);
	static_assert(offsetof(mm8::MapMonster, soundFidget) == 218);
	static_assert(offsetof(mm8::MapMonster, spellBuffs) == 220);
	static_assert(offsetof(mm8::MapMonster, items) == 700);
	static_assert(offsetof(mm8::MapMonster, group) == 844);
	static_assert(offsetof(mm8::MapMonster, ally) == 848);
	static_assert(offsetof(mm8::MapMonster, schedules) == 852);
	static_assert(offsetof(mm8::MapMonster, summoner) == 948);
	static_assert(offsetof(mm8::MapMonster, lastAttacker) == 952);
	static_assert(offsetof(mm8::MapMonster, nameId) == 956);
}

#pragma pack(pop)