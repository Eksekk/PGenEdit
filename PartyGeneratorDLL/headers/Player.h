#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)
namespace mm6
{
    struct Player
    {
        int items[5];
    };
}

namespace mm7
{
	struct BaseBonus // size: 0x4
	{
		int16_t base;
		int16_t bonus;
	};
	static_assert(sizeof(mm7::BaseBonus) == 0x4, "Invalid \"mm7::BaseBonus\" structure size");

	struct SpellBuff // size: 0x10
	{
		int64_t expireTime;
		int16_t power;
		int16_t skill;
		int16_t overlayId;
		uint8_t caster;
		uint8_t bits;
	};
	static_assert(sizeof(mm7::SpellBuff) == 0x10, "Invalid \"mm7::SpellBuff\" structure size");

	struct LloydBeaconSlot // size: 0x1C
	{
		int64_t expireTime;
		union
		{
			int32_t pos[3];
			struct
			{
				int32_t x;
				int32_t y;
				int32_t z;
			};
		};
		int16_t direction;
		int16_t lookAngle;
		int16_t active;
		union
		{
			int16_t mapIndex;
			uint8_t nil[2]; // Unknown type
		};
	};
	static_assert(sizeof(mm7::LloydBeaconSlot) == 0x1C, "Invalid \"mm7::LloydBeaconSlot\" structure size");

	struct Item // size: 0x24
	{
		int32_t number;
		int32_t bonus;
		int32_t bonusStrength;
		int32_t bonus2;
		int32_t charges;
		union
		{
			int32_t condition;
			struct
			{
				bool identified : 1;
				bool broken : 1;
				SKIPBITS(1);
				bool temporaryBonus : 1;
				SKIPBITS(4);
				bool stolen : 1;
				bool hardened : 1;
				bool refundable : 1;
			};
		};
		int8_t bodyLocation;
		uint8_t maxCharges;
		int8_t owner;
		SKIP(1);
		int64_t bonusExpireTime;
	};
	static_assert(sizeof(mm7::Item) == 0x24, "Invalid \"mm7::Item\" structure size");

	struct Player // size: 0x1B3C
	{
		union
		{
			int64_t conditions[20];
			struct
			{
				int64_t cursed;
				int64_t weak;
				int64_t asleep;
				int64_t afraid;
				int64_t drunk;
				int64_t insane;
				int64_t poison1;
				int64_t disease1;
				int64_t poison2;
				int64_t disease2;
				int64_t poison3;
				int64_t disease3;
				int64_t paralyzed;
				int64_t unconscious;
				int64_t dead;
				int64_t stoned;
				int64_t eradicated;
				int64_t zombie;
				int64_t good;
			};
		};
		union
		{
			int64_t exp;
			int64_t experience;
		};
		char name[16]; // requires null terminator
		bool sex;
		uint8_t clas;
		uint8_t face;
		SKIP(1);
		union
		{
			struct // size: 0x1C, MMExt union
			{
				mm7::BaseBonus _0;
				mm7::BaseBonus _1;
				mm7::BaseBonus _2;
				mm7::BaseBonus _3;
				mm7::BaseBonus _5;
				mm7::BaseBonus _4;
				mm7::BaseBonus _6;
			} stats;
			static_assert(sizeof(stats) == 0x1C, "Invalid \"stats\" structure size");
			struct
			{
				int16_t mightBase;
				int16_t mightBonus;
				int16_t intellectBase;
				int16_t intellectBonus;
				int16_t personalityBase;
				int16_t personalityBonus;
				int16_t enduranceBase;
				int16_t enduranceBonus;
				int16_t speedBase;
				int16_t speedBonus;
				int16_t accuracyBase;
				int16_t accuracyBonus;
				int16_t luckBase;
				int16_t luckBonus;
			};
		};
		int16_t armorClassBonus;
		int16_t levelBase;
		int16_t levelBonus;
		int16_t ageBonus;
		SKIP(40);
		int16_t skills[37];
		uint8_t awards[13]; // MMExt: 1..104, here 0..103 | array of abits (real index = 7 - usual)
		SKIP(51);
		bool spells[100]; // MMExt: 1..100, here 0..99
		SKIP(2);
		uint32_t usedBlackPotions[7]; // MMExt: 264..270, here 0..6 | 4-byte boolean
		mm7::Item items[138]; // MMExt: 1..138, here 0..137
		int32_t inventory[126];
		union
		{
			int16_t resistanceBase[11];
			struct
			{
				int16_t fireResistanceBase;
				int16_t airResistanceBase;
				int16_t waterResistanceBase;
				int16_t earthResistanceBase;
				SKIPBITS(8); // skipping 4 bytes and 0 bits, in total 32 bits
				SKIPBITS(8);
				SKIPBITS(8);
				SKIPBITS(8);
				int16_t spiritResistanceBase;
				int16_t mindResistanceBase;
				int16_t bodyResistanceBase;
				int16_t lightResistanceBase;
				int16_t darkResistanceBase;
			};
		};
		union
		{
			int16_t resistanceBonus[11];
			struct
			{
				int16_t fireResistanceBonus;
				int16_t airResistanceBonus;
				int16_t waterResistanceBonus;
				int16_t earthResistanceBonus;
				SKIPBITS(8); // skipping 4 bytes and 0 bits, in total 32 bits
				SKIPBITS(8);
				SKIPBITS(8);
				SKIPBITS(8);
				int16_t spiritResistanceBonus;
				int16_t mindResistanceBonus;
				int16_t bodyResistanceBonus;
				int16_t lightResistanceBonus;
				int16_t darkResistanceBonus;
			};
		};
		mm7::SpellBuff spellBuffs[24];
		int32_t voice;
		union
		{
			int32_t originalFace;
			int32_t faceBeforeZombie;
		};
		union
		{
			int32_t originalVoice;
			int32_t voiceBeforeZombie;
		};
		SKIP(8);
		int16_t recoveryDelay;
		uint8_t attackSpell;
		SKIP(1);
		int32_t skillPoints;
		union
		{
			int32_t HP;
			int32_t hitPoints;
		};
		union
		{
			int32_t spellPoints;
			int32_t SP;
		};
		int32_t birthYear;
		union
		{
			int32_t equippedItems[16];
			struct
			{
				int32_t itemExtraHand;
				int32_t itemMainHand;
				int32_t itemBow;
				int32_t itemArmor;
				int32_t itemHelm;
				int32_t itemBelt;
				int32_t itemCloak;
				int32_t itemGountlets;
				int32_t itemBoots;
				int32_t itemAmulet;
				int32_t itemRing1;
				int32_t itemRing2;
				int32_t itemRing3;
				int32_t itemRing4;
				int32_t itemRing5;
				int32_t itemRing6;
			};
		};
		SKIP(198);
		int8_t spellBookPage;
		uint8_t quickSpell;
		uint8_t playerBits[64]; // MMExt: 1..512, here 0..511 | array of abits (real index = 7 - usual)
		int8_t meleeAttackBonus;
		SKIP(1);
		int8_t meleeDamageBonus;
		SKIP(1);
		int8_t rangedAttackBonus;
		SKIP(1);
		int8_t rangedDamageBonus;
		SKIP(1);
		union
		{
			int8_t fullHPBonus;
			int8_t fullHitPointsBonus;
		};
		SKIP(1);
		union
		{
			int8_t fullSpellPointsBonus;
			int8_t fullSPBonus;
		};
		SKIP(1);
		int16_t expression;
		int16_t expressionTimePassed;
		int16_t expressionLength;
		SKIP(10);
		mm7::LloydBeaconSlot beacons[5];
		uint8_t devineInterventionCasts;
		uint8_t armageddonCasts;
		SKIP(2);
	};
	static_assert(sizeof(mm7::Player) == 0x1B3C, "Invalid \"mm7::Player\" structure size");
}

namespace mm8
{
    struct Player
    {
        int items[7];
    };
}

#pragma pack(pop)