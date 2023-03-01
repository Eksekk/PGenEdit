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
			std::array<int16_t, 3> pos;
			struct
			{
				int16_t x;
				int16_t y;
				int16_t z;
			};
		};
		uint16_t bits;
		uint8_t action;
		uint8_t hour;
		uint8_t day;
		uint8_t month;
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
		uint8_t type;
		uint8_t damageDiceCount;
		uint8_t damageDiceSides;
		uint8_t damageAdd;
		uint8_t missile;
	};
	static_assert(sizeof(mm6::MonsterAttackInfo) == 0x5, "Invalid \"mm6::MonsterAttackInfo\" structure size");
	static_assert(offsetof(mm6::MonsterAttackInfo, damageDiceCount) == 1);
	static_assert(offsetof(mm6::MonsterAttackInfo, damageDiceSides) == 2);
	static_assert(offsetof(mm6::MonsterAttackInfo, damageAdd) == 3);
	static_assert(offsetof(mm6::MonsterAttackInfo, missile) == 4);



	struct MonstersTxtItem // size: 0x48
	{
		char* name; // EditPChar
		char* picture; // EditPChar
		uint8_t id;
		uint8_t level;
		uint8_t treasureItemPercent;
		uint8_t treasureDiceCount;
		uint8_t treasureDiceSides;
		uint8_t treasureItemLevel;
		uint8_t treasureItemType;
		uint8_t fly;
		uint8_t moveType;
		uint8_t AIType;
		uint8_t hostileType;
		union
		{
			uint8_t prefClass;
			struct // size: 0x1, MMExt union
			{
				bool knight : 1;
				bool paladin : 1;
				bool archer : 1;
				bool druid : 1;
				bool cleric : 1;
				bool sorcerer : 1;
				bool male : 1;
				bool female : 1;
			} prefers;
			static_assert(sizeof(prefers) == 0x1, "Invalid \"prefers\" structure size");
		};
		uint8_t bonus;
		uint8_t bonusMul;
		mm6::MonsterAttackInfo attack1;
		uint8_t attack2Chance;
		mm6::MonsterAttackInfo attack2;
		uint8_t spellChance;
		uint8_t spell;
		uint8_t spellSkill;
		union
		{
			struct // size: 0x6, MMExt union
			{
				uint8_t _2;
				uint8_t _3;
				uint8_t _4;
				uint8_t _5;
				uint8_t _0;
				uint8_t _1;
			} resistances;
			static_assert(sizeof(resistances) == 0x6, "Invalid \"resistances\" structure size");
			struct
			{
				uint8_t fireResistance;
				uint8_t elecResistance;
				uint8_t coldResistance;
				uint8_t poisonResistance;
				uint8_t physResistance;
				uint8_t magicResistance;
			};
		};
		uint8_t prefNum;
		SKIP(1);
		int16_t questItem;
		SKIP(2);
		union
		{
			int32_t fullHP;
			int32_t fullHitPoints;
		};
		int32_t armorClass;
		union
		{
			int32_t exp;
			int32_t experience;
		};
		int32_t moveSpeed;
		int32_t attackRecovery;
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
		std::array<char, 32> name; // fixed size string, requires null terminator
		int16_t NPC_ID;
		SKIP(2);
		union
		{
			uint32_t bits;
			struct
			{
				SKIPBITS(8); // skipping 1 bytes and 2 bits, in total 10 bits
				SKIPBITS(2);
				bool active : 1;
				SKIPBITS(4);
				bool showOnMap : 1;
				bool invisible : 1;
				bool noFlee : 1;
				SKIPBITS(1);
				bool hostile : 1;
				bool onAlertMap : 1;
				SKIPBITS(2);
				bool treasureGenerated : 1;
				bool showAsHostile : 1;
			};
		};
		union
		{
			int16_t HP;
			int16_t hitPoints;
		};
		SKIP(10);
		uint8_t id;
		uint8_t level;
		uint8_t treasureItemPercent;
		uint8_t treasureDiceCount;
		uint8_t treasureDiceSides;
		uint8_t treasureItemLevel;
		uint8_t treasureItemType;
		uint8_t fly;
		uint8_t moveType;
		uint8_t AIType;
		uint8_t hostileType;
		union
		{
			uint8_t prefClass;
			struct // size: 0x1, MMExt union
			{
				bool knight : 1;
				bool paladin : 1;
				bool archer : 1;
				bool druid : 1;
				bool cleric : 1;
				bool sorcerer : 1;
				bool male : 1;
				bool female : 1;
			} prefers;
			static_assert(sizeof(prefers) == 0x1, "Invalid \"prefers\" structure size");
		};
		uint8_t bonus;
		uint8_t bonusMul;
		mm6::MonsterAttackInfo attack1;
		uint8_t attack2Chance;
		mm6::MonsterAttackInfo attack2;
		uint8_t spellChance;
		uint8_t spell;
		uint8_t spellSkill;
		union
		{
			struct // size: 0x6, MMExt union
			{
				uint8_t _2;
				uint8_t _3;
				uint8_t _4;
				uint8_t _5;
				uint8_t _0;
				uint8_t _1;
			} resistances;
			static_assert(sizeof(resistances) == 0x6, "Invalid \"resistances\" structure size");
			struct
			{
				uint8_t fireResistance;
				uint8_t elecResistance;
				uint8_t coldResistance;
				uint8_t poisonResistance;
				uint8_t physResistance;
				uint8_t magicResistance;
			};
		};
		uint8_t prefNum;
		SKIP(1);
		int16_t questItem;
		SKIP(2);
		union
		{
			int32_t fullHP;
			int32_t fullHitPoints;
		};
		int32_t armorClass;
		union
		{
			int32_t experience;
			int32_t exp;
		};
		int32_t moveSpeed;
		int32_t attackRecovery;
		SKIP(4);
		int16_t rangeAttack;
		int16_t id2;
		int16_t bodyRadius;
		int16_t bodyHeight;
		int16_t velocity;
		union
		{
			std::array<int16_t, 3> pos;
			struct
			{
				int16_t x;
				int16_t y;
				int16_t z;
			};
		};
		int16_t velocityX;
		int16_t velocityY;
		int16_t velocityZ;
		int16_t direction;
		int16_t lookAngle;
		int16_t room;
		int16_t currentActionLength;
		int16_t startX;
		int16_t startY;
		int16_t startZ;
		int16_t guardX;
		int16_t guardY;
		int16_t guardZ;
		int16_t guardRadius;
		int16_t AIState;
		int16_t graphicState;
		int16_t item;
		SKIP(2);
		int32_t currentActionStep;
		union
		{
			std::array<int16_t, 8> frames;
			struct
			{
				int16_t framesStand;
				int16_t framesWalk;
				int16_t framesAttack;
				int16_t framesShoot;
				union
				{
					int16_t framesStun;
					int16_t framesGotHit;
				};
				int16_t framesDie;
				int16_t framesDead;
				int16_t framesFidget;
			};
		};
		union
		{
			std::array<int16_t, 4> sounds;
			struct
			{
				int16_t soundAttack;
				int16_t soundDie;
				union
				{
					int16_t soundGetHit;
					int16_t soundGotHit;
				};
				int16_t soundFidget;
			};
		};
		std::array<mm6::SpellBuff, 14> spellBuffs;
		int32_t group;
		int32_t ally;
		std::array<mm6::MonsterSchedule, 8> schedules;
		int32_t summoner;
		int32_t lastAttacker;
		SKIP(16);
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
	static_assert(offsetof(mm6::MapMonster, experience) == 100);
	static_assert(offsetof(mm6::MapMonster, exp) == 100);
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
	static_assert(offsetof(mm6::MapMonster, soundGetHit) == 192);
	static_assert(offsetof(mm6::MapMonster, soundGotHit) == 192);
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
		bool undead;
		bool demon;
		bool dragon;
		bool elf;
		bool swimmer;
		bool immobile;
		bool titan;
		bool noArena;
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
			std::array<int16_t, 3> pos;
			struct
			{
				int16_t x;
				int16_t y;
				int16_t z;
			};
		};
		uint16_t bits;
		uint8_t action;
		uint8_t hour;
		uint8_t day;
		uint8_t month;
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
		uint8_t type;
		uint8_t damageDiceCount;
		uint8_t damageDiceSides;
		uint8_t damageAdd;
		uint8_t missile;
	};
	static_assert(sizeof(mm7::MonsterAttackInfo) == 0x5, "Invalid \"mm7::MonsterAttackInfo\" structure size");
	static_assert(offsetof(mm7::MonsterAttackInfo, damageDiceCount) == 1);
	static_assert(offsetof(mm7::MonsterAttackInfo, damageDiceSides) == 2);
	static_assert(offsetof(mm7::MonsterAttackInfo, damageAdd) == 3);
	static_assert(offsetof(mm7::MonsterAttackInfo, missile) == 4);



	struct MonstersTxtItem // size: 0x58
	{
		char* name; // EditPChar
		char* picture; // EditPChar
		uint8_t level;
		uint8_t treasureItemPercent;
		uint8_t treasureDiceCount;
		uint8_t treasureDiceSides;
		uint8_t treasureItemLevel;
		uint8_t treasureItemType;
		uint8_t fly;
		uint8_t moveType;
		uint8_t AIType;
		uint8_t hostileType;
		SKIP(1);
		uint8_t bonus;
		uint8_t bonusMul;
		mm7::MonsterAttackInfo attack1;
		uint8_t attack2Chance;
		mm7::MonsterAttackInfo attack2;
		uint8_t spellChance;
		uint8_t spell;
		uint8_t spell2Chance;
		uint8_t spell2;
		union
		{
			struct // size: 0xA, MMExt union
			{
				uint8_t _0;
				uint8_t _1;
				uint8_t _2;
				uint8_t _3;
				uint8_t _7;
				uint8_t _6;
				uint8_t _8;
				uint8_t _9;
				uint8_t _10;
				uint8_t _4;
			} resistances;
			static_assert(sizeof(resistances) == 0xA, "Invalid \"resistances\" structure size");
			struct
			{
				uint8_t fireResistance;
				uint8_t airResistance;
				uint8_t waterResistance;
				uint8_t earthResistance;
				uint8_t mindResistance;
				uint8_t spiritResistance;
				uint8_t bodyResistance;
				uint8_t lightResistance;
				uint8_t darkResistance;
				uint8_t physResistance;
			};
		};
		uint8_t special;
		uint8_t specialA;
		uint8_t specialB;
		uint8_t specialC;
		uint8_t prefNum;
		SKIP(1);
		uint16_t id;
		uint16_t bloodSplat;
		uint16_t spellSkill;
		uint16_t spell2Skill;
		uint16_t specialD;
		SKIP(2);
		union
		{
			int32_t fullHitPoints;
			int32_t fullHP;
		};
		int32_t armorClass;
		union
		{
			int32_t exp;
			int32_t experience;
		};
		int32_t moveSpeed;
		int32_t attackRecovery;
		union
		{
			int32_t prefClass;
			struct
			{
				struct // size: 0x2, MMExt union
				{
					bool knight : 1;
					bool paladin : 1;
					bool archer : 1;
					bool druid : 1;
					bool cleric : 1;
					bool sorcerer : 1;
					bool ranger : 1;
					bool thief : 1;
					bool monk : 1;
					bool male : 1;
					bool female : 1;
					bool human : 1;
					bool elf : 1;
					bool dwarf : 1;
					bool goblin : 1;
				} prefers;
				static_assert(sizeof(prefers) == 0x2, "Invalid \"prefers\" structure size");
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
	static_assert(offsetof(mm7::MonstersTxtItem, fullHitPoints) == 64);
	static_assert(offsetof(mm7::MonstersTxtItem, fullHP) == 64);
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
		int16_t NPC_ID;
		SKIP(2);
		union
		{
			uint32_t bits;
			struct
			{
				SKIPBITS(8); // skipping 1 bytes and 2 bits, in total 10 bits
				SKIPBITS(2);
				bool active : 1;
				SKIPBITS(4);
				bool showOnMap : 1;
				bool invisible : 1;
				bool noFlee : 1;
				SKIPBITS(1);
				bool hostile : 1;
				bool onAlertMap : 1;
				SKIPBITS(2);
				bool treasureGenerated : 1;
				bool showAsHostile : 1;
			};
		};
		union
		{
			int16_t hitPoints;
			int16_t HP;
		};
		SKIP(10);
		uint8_t level;
		uint8_t treasureItemPercent;
		uint8_t treasureDiceCount;
		uint8_t treasureDiceSides;
		uint8_t treasureItemLevel;
		uint8_t treasureItemType;
		uint8_t fly;
		uint8_t moveType;
		uint8_t AIType;
		uint8_t hostileType;
		SKIP(1);
		uint8_t bonus;
		uint8_t bonusMul;
		mm7::MonsterAttackInfo attack1;
		uint8_t attack2Chance;
		mm7::MonsterAttackInfo attack2;
		uint8_t spellChance;
		uint8_t spell;
		uint8_t spell2Chance;
		uint8_t spell2;
		union
		{
			struct // size: 0xA, MMExt union
			{
				uint8_t _0;
				uint8_t _1;
				uint8_t _2;
				uint8_t _3;
				uint8_t _7;
				uint8_t _6;
				uint8_t _8;
				uint8_t _9;
				uint8_t _10;
				uint8_t _4;
			} resistances;
			static_assert(sizeof(resistances) == 0xA, "Invalid \"resistances\" structure size");
			struct
			{
				uint8_t fireResistance;
				uint8_t airResistance;
				uint8_t waterResistance;
				uint8_t earthResistance;
				uint8_t mindResistance;
				uint8_t spiritResistance;
				uint8_t bodyResistance;
				uint8_t lightResistance;
				uint8_t darkResistance;
				uint8_t physResistance;
			};
		};
		uint8_t special;
		uint8_t specialA;
		uint8_t specialB;
		uint8_t specialC;
		uint8_t prefNum;
		SKIP(1);
		uint16_t id;
		uint16_t bloodSplat;
		uint16_t spellSkill;
		uint16_t spell2Skill;
		uint16_t specialD;
		SKIP(2);
		union
		{
			int32_t fullHitPoints;
			int32_t fullHP;
		};
		int32_t armorClass;
		union
		{
			int32_t exp;
			int32_t experience;
		};
		int32_t moveSpeed;
		int32_t attackRecovery;
		union
		{
			int32_t prefClass;
			struct
			{
				struct // size: 0x2, MMExt union
				{
					bool knight : 1;
					bool paladin : 1;
					bool archer : 1;
					bool druid : 1;
					bool cleric : 1;
					bool sorcerer : 1;
					bool ranger : 1;
					bool thief : 1;
					bool monk : 1;
					bool male : 1;
					bool female : 1;
					bool human : 1;
					bool elf : 1;
					bool dwarf : 1;
					bool goblin : 1;
				} prefers;
				static_assert(sizeof(prefers) == 0x2, "Invalid \"prefers\" structure size");
			};
		};
		int16_t rangeAttack;
		int16_t id2;
		int16_t bodyRadius;
		int16_t bodyHeight;
		int16_t velocity;
		union
		{
			std::array<int16_t, 3> pos;
			struct
			{
				int16_t x;
				int16_t y;
				int16_t z;
			};
		};
		int16_t velocityX;
		int16_t velocityY;
		int16_t velocityZ;
		int16_t direction;
		int16_t lookAngle;
		int16_t room;
		int16_t currentActionLength;
		int16_t startX;
		int16_t startY;
		int16_t startZ;
		int16_t guardX;
		int16_t guardY;
		int16_t guardZ;
		int16_t guardRadius;
		int16_t AIState;
		int16_t graphicState;
		int16_t item;
		SKIP(2);
		int32_t currentActionStep;
		union
		{
			std::array<int16_t, 8> frames;
			struct
			{
				int16_t framesStand;
				int16_t framesWalk;
				int16_t framesAttack;
				int16_t framesShoot;
				union
				{
					int16_t framesStun;
					int16_t framesGotHit;
				};
				int16_t framesDie;
				int16_t framesDead;
				int16_t framesFidget;
			};
		};
		union
		{
			std::array<int16_t, 4> sounds;
			struct
			{
				int16_t soundAttack;
				int16_t soundDie;
				union
				{
					int16_t soundGotHit;
					int16_t soundGetHit;
				};
				int16_t soundFidget;
			};
		};
		std::array<mm7::SpellBuff, 22> spellBuffs;
		std::array<mm7::Item, 4> items;
		int32_t group;
		int32_t ally;
		std::array<mm7::MonsterSchedule, 8> schedules;
		int32_t summoner;
		int32_t lastAttacker;
		int32_t nameId;
		SKIP(12);
	};
	static_assert(sizeof(mm7::MapMonster) == 0x344, "Invalid \"mm7::MapMonster\" structure size");
	static_assert(offsetof(mm7::MapMonster, NPC_ID) == 32);
	static_assert(offsetof(mm7::MapMonster, bits) == 36);
	static_assert(offsetof(mm7::MapMonster, hitPoints) == 40);
	static_assert(offsetof(mm7::MapMonster, HP) == 40);
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
	static_assert(offsetof(mm7::MapMonster, fullHitPoints) == 108);
	static_assert(offsetof(mm7::MapMonster, fullHP) == 108);
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
	struct MonsterSchedule // size: 0xC
	{
		union
		{
			std::array<int16_t, 3> pos;
			struct
			{
				int16_t x;
				int16_t y;
				int16_t z;
			};
		};
		uint16_t bits;
		uint8_t action;
		uint8_t hour;
		uint8_t day;
		uint8_t month;
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
		uint8_t type;
		uint8_t damageDiceCount;
		uint8_t damageDiceSides;
		uint8_t damageAdd;
		uint8_t missile;
	};
	static_assert(sizeof(mm8::MonsterAttackInfo) == 0x5, "Invalid \"mm8::MonsterAttackInfo\" structure size");
	static_assert(offsetof(mm8::MonsterAttackInfo, damageDiceCount) == 1);
	static_assert(offsetof(mm8::MonsterAttackInfo, damageDiceSides) == 2);
	static_assert(offsetof(mm8::MonsterAttackInfo, damageAdd) == 3);
	static_assert(offsetof(mm8::MonsterAttackInfo, missile) == 4);



	struct MonstersTxtItem // size: 0x60
	{
		char* name; // EditPChar
		char* picture; // EditPChar
		uint8_t level;
		uint8_t treasureItemPercent;
		uint8_t treasureDiceCount;
		uint8_t treasureDiceSides;
		uint8_t treasureItemLevel;
		uint8_t treasureItemType;
		uint8_t fly;
		uint8_t moveType;
		uint8_t AIType;
		uint8_t hostileType;
		SKIP(1);
		uint8_t bonus;
		uint8_t bonusMul;
		mm8::MonsterAttackInfo attack1;
		uint8_t attack2Chance;
		mm8::MonsterAttackInfo attack2;
		uint8_t spellChance;
		uint8_t spell;
		uint8_t spell2Chance;
		uint8_t spell2;
		union
		{
			struct // size: 0x14, MMExt union
			{
				uint16_t _0;
				uint16_t _1;
				uint16_t _2;
				uint16_t _3;
				uint16_t _7;
				uint16_t _6;
				uint16_t _8;
				uint16_t _9;
				uint16_t _10;
				uint16_t _4;
			} resistances;
			static_assert(sizeof(resistances) == 0x14, "Invalid \"resistances\" structure size");
			struct
			{
				uint16_t fireResistance;
				uint16_t airResistance;
				uint16_t waterResistance;
				uint16_t earthResistance;
				uint16_t mindResistance;
				uint16_t spiritResistance;
				uint16_t bodyResistance;
				uint16_t lightResistance;
				uint16_t darkResistance;
				uint16_t physResistance;
			};
		};
		uint8_t special;
		uint8_t specialA;
		uint8_t specialB;
		uint8_t specialC;
		uint8_t prefNum;
		SKIP(1);
		uint16_t id;
		uint16_t bloodSplat;
		uint16_t spellSkill;
		uint16_t spell2Skill;
		uint16_t specialD;
		union
		{
			int32_t fullHP;
			int32_t fullHitPoints;
		};
		int32_t armorClass;
		union
		{
			int32_t experience;
			int32_t exp;
		};
		int32_t moveSpeed;
		int32_t attackRecovery;
		union
		{
			int32_t prefClass;
			struct
			{
				struct // size: 0x2, MMExt union
				{
					bool necro : 1;
					bool cleric : 1;
					bool knight : 1;
					bool troll : 1;
					bool minotaur : 1;
					bool darkElf : 1;
					bool vampire : 1;
					bool dragon : 1;
					bool male : 1;
					bool female : 1;
				} prefers;
				static_assert(sizeof(prefers) == 0x2, "Invalid \"prefers\" structure size");
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
	static_assert(offsetof(mm8::MonstersTxtItem, experience) == 80);
	static_assert(offsetof(mm8::MonstersTxtItem, exp) == 80);
	static_assert(offsetof(mm8::MonstersTxtItem, moveSpeed) == 84);
	static_assert(offsetof(mm8::MonstersTxtItem, attackRecovery) == 88);
	static_assert(offsetof(mm8::MonstersTxtItem, prefClass) == 92);
	static_assert(offsetof(mm8::MonstersTxtItem, prefers) == 92);



	struct MapMonster // size: 0x3CC
	{
		SKIP(32);
		int16_t NPC_ID;
		SKIP(2);
		union
		{
			uint32_t bits;
			struct
			{
				SKIPBITS(8); // skipping 1 bytes and 2 bits, in total 10 bits
				SKIPBITS(2);
				bool active : 1;
				SKIPBITS(4);
				bool showOnMap : 1;
				bool invisible : 1;
				bool noFlee : 1;
				SKIPBITS(1);
				bool hostile : 1;
				bool onAlertMap : 1;
				SKIPBITS(2);
				bool treasureGenerated : 1;
				bool showAsHostile : 1;
				bool isObeliskChest : 1;
			};
		};
		union
		{
			int16_t hitPoints;
			int16_t HP;
		};
		SKIP(10);
		uint8_t level;
		uint8_t treasureItemPercent;
		uint8_t treasureDiceCount;
		uint8_t treasureDiceSides;
		uint8_t treasureItemLevel;
		uint8_t treasureItemType;
		uint8_t fly;
		uint8_t moveType;
		uint8_t AIType;
		uint8_t hostileType;
		SKIP(1);
		uint8_t bonus;
		uint8_t bonusMul;
		mm8::MonsterAttackInfo attack1;
		uint8_t attack2Chance;
		mm8::MonsterAttackInfo attack2;
		uint8_t spellChance;
		uint8_t spell;
		uint8_t spell2Chance;
		uint8_t spell2;
		union
		{
			struct // size: 0x14, MMExt union
			{
				uint16_t _0;
				uint16_t _1;
				uint16_t _2;
				uint16_t _3;
				uint16_t _7;
				uint16_t _6;
				uint16_t _8;
				uint16_t _9;
				uint16_t _10;
				uint16_t _4;
			} resistances;
			static_assert(sizeof(resistances) == 0x14, "Invalid \"resistances\" structure size");
			struct
			{
				uint16_t fireResistance;
				uint16_t airResistance;
				uint16_t waterResistance;
				uint16_t earthResistance;
				uint16_t mindResistance;
				uint16_t spiritResistance;
				uint16_t bodyResistance;
				uint16_t lightResistance;
				uint16_t darkResistance;
				uint16_t physResistance;
			};
		};
		uint8_t special;
		uint8_t specialA;
		uint8_t specialB;
		uint8_t specialC;
		uint8_t prefNum;
		SKIP(1);
		uint16_t id;
		uint16_t bloodSplat;
		uint16_t spellSkill;
		uint16_t spell2Skill;
		uint16_t specialD;
		union
		{
			int32_t fullHitPoints;
			int32_t fullHP;
		};
		int32_t armorClass;
		union
		{
			int32_t exp;
			int32_t experience;
		};
		int32_t moveSpeed;
		int32_t attackRecovery;
		union
		{
			int32_t prefClass;
			struct
			{
				struct // size: 0x2, MMExt union
				{
					bool necro : 1;
					bool cleric : 1;
					bool knight : 1;
					bool troll : 1;
					bool minotaur : 1;
					bool darkElf : 1;
					bool vampire : 1;
					bool dragon : 1;
					bool male : 1;
					bool female : 1;
				} prefers;
				static_assert(sizeof(prefers) == 0x2, "Invalid \"prefers\" structure size");
			};
		};
		int16_t rangeAttack;
		int16_t id2;
		int16_t bodyRadius;
		int16_t bodyHeight;
		int16_t velocity;
		union
		{
			std::array<int16_t, 3> pos;
			struct
			{
				int16_t x;
				int16_t y;
				int16_t z;
			};
		};
		int16_t velocityX;
		int16_t velocityY;
		int16_t velocityZ;
		int16_t direction;
		int16_t lookAngle;
		int16_t room;
		int16_t currentActionLength;
		int16_t startX;
		int16_t startY;
		int16_t startZ;
		int16_t guardX;
		int16_t guardY;
		int16_t guardZ;
		int16_t guardRadius;
		int16_t AIState;
		int16_t graphicState;
		int16_t item;
		SKIP(2);
		int32_t currentActionStep;
		union
		{
			std::array<int16_t, 8> frames;
			struct
			{
				int16_t framesStand;
				int16_t framesWalk;
				int16_t framesAttack;
				int16_t framesShoot;
				union
				{
					int16_t framesGotHit;
					int16_t framesStun;
				};
				int16_t framesDie;
				int16_t framesDead;
				int16_t framesFidget;
			};
		};
		union
		{
			std::array<int16_t, 4> sounds;
			struct
			{
				int16_t soundAttack;
				int16_t soundDie;
				union
				{
					int16_t soundGotHit;
					int16_t soundGetHit;
				};
				int16_t soundFidget;
			};
		};
		std::array<mm8::SpellBuff, 30> spellBuffs;
		std::array<mm8::Item, 4> items;
		int32_t group;
		int32_t ally;
		std::array<mm8::MonsterSchedule, 8> schedules;
		int32_t summoner;
		int32_t lastAttacker;
		int32_t nameId;
		SKIP(12);
	};
	static_assert(sizeof(mm8::MapMonster) == 0x3CC, "Invalid \"mm8::MapMonster\" structure size");
	static_assert(offsetof(mm8::MapMonster, NPC_ID) == 32);
	static_assert(offsetof(mm8::MapMonster, bits) == 36);
	static_assert(offsetof(mm8::MapMonster, hitPoints) == 40);
	static_assert(offsetof(mm8::MapMonster, HP) == 40);
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
	static_assert(offsetof(mm8::MapMonster, fullHitPoints) == 116);
	static_assert(offsetof(mm8::MapMonster, fullHP) == 116);
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
	static_assert(offsetof(mm8::MapMonster, framesGotHit) == 204);
	static_assert(offsetof(mm8::MapMonster, framesStun) == 204);
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



	struct MonsterKind // size: 0x8
	{
		bool undead;
		bool dragon;
		bool swimmer;
		bool immobile;
		bool peasant;
		bool noArena;
		bool ogre;
		bool elemental;
	};
	static_assert(sizeof(mm8::MonsterKind) == 0x8, "Invalid \"mm8::MonsterKind\" structure size");
	static_assert(offsetof(mm8::MonsterKind, dragon) == 1);
	static_assert(offsetof(mm8::MonsterKind, swimmer) == 2);
	static_assert(offsetof(mm8::MonsterKind, immobile) == 3);
	static_assert(offsetof(mm8::MonsterKind, peasant) == 4);
	static_assert(offsetof(mm8::MonsterKind, noArena) == 5);
	static_assert(offsetof(mm8::MonsterKind, ogre) == 6);
	static_assert(offsetof(mm8::MonsterKind, elemental) == 7);
}

#pragma pack(pop)