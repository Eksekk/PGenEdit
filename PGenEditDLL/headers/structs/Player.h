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
			std::array<uint8_t, 2> sounds; // MMExt: 1..2, here 0..1
			struct
			{
				uint8_t sound1;
				uint8_t sound2;
			};
		};
		SKIP(1);
		union
		{
			std::array<uint8_t, 5> expressions; // MMExt: 1..5, here 0..4
			struct
			{
				uint8_t expression1;
				uint8_t expression2;
				uint8_t expression3;
				uint8_t expression4;
				uint8_t expression5;
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



	struct LloydBeaconSlot // size: 0x1C
	{
		int64_t expireTime;
		union
		{
			std::array<int32_t, 3> pos;
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
			std::array<uint8_t, 2> map; // Unknown type
			int16_t mapIndex;
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



	struct BaseBonus // size: 0x4
	{
		int16_t base;
		int16_t bonus;
	};
	static_assert(sizeof(mm6::BaseBonus) == 0x4, "Invalid \"mm6::BaseBonus\" structure size");
	static_assert(offsetof(mm6::BaseBonus, bonus) == 2);



	struct Player // size: 0x161C
	{
		uint8_t face;
		std::array<char, 16> name; // fixed size string, requires null terminator
		bool sex;
		uint8_t clas;
		SKIP(1);
		union
		{
			struct // size: 0x1C, MMExt union
			{
				mm6::BaseBonus _0;
				mm6::BaseBonus _1;
				mm6::BaseBonus _2;
				mm6::BaseBonus _3;
				mm6::BaseBonus _5;
				mm6::BaseBonus _4;
				mm6::BaseBonus _6;
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
		std::array<uint8_t, 31> skills;
		std::array<uint8_t, 11> awards; // array of abits (real index = 7 - usual)
		SKIP(53);
		std::array<bool, 100> spells; // MMExt: 1..100, here 0..99
		SKIP(5);
		std::array<uint32_t, 7> usedBlackPotions; // MMExt: 181..187, here 0..6 | 4-byte boolean
		std::array<mm6::Item, 138> items; // MMExt: 1..138, here 0..137
		std::array<int32_t, 126> inventory;
		union
		{
			struct // size: 0x14, MMExt union
			{
				mm6::BaseBonus _2;
				mm6::BaseBonus _4;
				mm6::BaseBonus _3;
				mm6::BaseBonus _5;
				mm6::BaseBonus _1;
			} resistances;
			static_assert(sizeof(resistances) == 0x14, "Invalid \"resistances\" structure size");
			struct
			{
				int16_t fireResistanceBase;
				int16_t fireResistanceBonus;
				int16_t coldResistanceBase;
				int16_t coldResistanceBonus;
				int16_t elecResistanceBase;
				int16_t elecResistanceBonus;
				int16_t poisonResistanceBase;
				int16_t poisonResistanceBonus;
				int16_t magicResistanceBase;
				int16_t magicResistanceBonus;
			};
		};
		std::array<mm6::SpellBuff, 16> spellBuffs;
		SKIP(20);
		int16_t recoveryDelay;
		uint8_t attackSpell;
		SKIP(1);
		union
		{
			std::array<int64_t, 17> conditions;
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
			};
		};
		int64_t good;
		int32_t skillPoints;
		union
		{
			int32_t HP;
			int32_t hitPoints;
		};
		union
		{
			int32_t SP;
			int32_t spellPoints;
		};
		int32_t birthYear;
		union
		{
			int64_t exp;
			int64_t experience;
		};
		union
		{
			std::array<int32_t, 16> equippedItems;
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
		std::array<uint8_t, 64> playerBits; // array of abits (real index = 7 - usual)
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
			int8_t fullSPBonus;
			int8_t fullSpellPointsBonus;
		};
		SKIP(1);
		int16_t expression;
		int16_t expressionTimePassed;
		int16_t expressionLength;
		SKIP(10);
		std::array<mm6::LloydBeaconSlot, 5> beacons;
		uint8_t devineInterventionCasts;
		uint8_t armageddonCasts;
		SKIP(2);
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
			std::array<uint8_t, 2> sounds; // MMExt: 1..2, here 0..1
			struct
			{
				uint8_t sound1;
				uint8_t sound2;
			};
		};
		SKIP(1);
		union
		{
			std::array<uint8_t, 5> expressions; // MMExt: 1..5, here 0..4
			struct
			{
				uint8_t expression1;
				uint8_t expression2;
				uint8_t expression3;
				uint8_t expression4;
				uint8_t expression5;
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
		int16_t base;
		int16_t bonus;
	};
	static_assert(sizeof(mm7::BaseBonus) == 0x4, "Invalid \"mm7::BaseBonus\" structure size");
	static_assert(offsetof(mm7::BaseBonus, bonus) == 2);



	struct LloydBeaconSlot // size: 0x1C
	{
		int64_t expireTime;
		union
		{
			std::array<int32_t, 3> pos;
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
			std::array<uint8_t, 2> map; // Unknown type
			int16_t mapIndex;
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
			std::array<int64_t, 20> conditions;
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
		std::array<char, 16> name; // fixed size string, requires null terminator
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
		std::array<int16_t, 37> skills;
		std::array<uint8_t, 13> awards; // MMExt: 1..104, here 0..103 | array of abits (real index = 7 - usual)
		SKIP(51);
		std::array<bool, 100> spells; // MMExt: 1..100, here 0..99
		SKIP(2);
		std::array<uint32_t, 7> usedBlackPotions; // MMExt: 264..270, here 0..6 | 4-byte boolean
		std::array<mm7::Item, 138> items; // MMExt: 1..138, here 0..137
		std::array<int32_t, 126> inventory;
		union
		{
			std::array<int16_t, 11> resistanceBase;
			struct
			{
				int16_t fireResistanceBase;
				int16_t airResistanceBase;
				int16_t waterResistanceBase;
				int16_t earthResistanceBase;
				SKIP(4);
				int16_t spiritResistanceBase;
				int16_t mindResistanceBase;
				int16_t bodyResistanceBase;
				int16_t lightResistanceBase;
				int16_t darkResistanceBase;
			};
		};
		union
		{
			std::array<int16_t, 11> resistanceBonus;
			struct
			{
				int16_t fireResistanceBonus;
				int16_t airResistanceBonus;
				int16_t waterResistanceBonus;
				int16_t earthResistanceBonus;
				SKIP(4);
				int16_t spiritResistanceBonus;
				int16_t mindResistanceBonus;
				int16_t bodyResistanceBonus;
				int16_t lightResistanceBonus;
				int16_t darkResistanceBonus;
			};
		};
		std::array<mm7::SpellBuff, 24> spellBuffs;
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
			std::array<int32_t, 16> equippedItems;
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
		std::array<uint8_t, 64> playerBits; // MMExt: 1..512, here 0..511 | array of abits (real index = 7 - usual)
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
			int8_t fullHitPointsBonus;
			int8_t fullHPBonus;
		};
		SKIP(1);
		union
		{
			int8_t fullSPBonus;
			int8_t fullSpellPointsBonus;
		};
		SKIP(1);
		int16_t expression;
		int16_t expressionTimePassed;
		int16_t expressionLength;
		SKIP(10);
		std::array<mm7::LloydBeaconSlot, 5> beacons;
		uint8_t devineInterventionCasts;
		uint8_t armageddonCasts;
		SKIP(2);
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
	static_assert(offsetof(mm7::Player, originalFace) == 6436);
	static_assert(offsetof(mm7::Player, faceBeforeZombie) == 6436);
	static_assert(offsetof(mm7::Player, originalVoice) == 6440);
	static_assert(offsetof(mm7::Player, voiceBeforeZombie) == 6440);
	static_assert(offsetof(mm7::Player, recoveryDelay) == 6452);
	static_assert(offsetof(mm7::Player, attackSpell) == 6454);
	static_assert(offsetof(mm7::Player, skillPoints) == 6456);
	static_assert(offsetof(mm7::Player, HP) == 6460);
	static_assert(offsetof(mm7::Player, hitPoints) == 6460);
	static_assert(offsetof(mm7::Player, spellPoints) == 6464);
	static_assert(offsetof(mm7::Player, SP) == 6464);
	static_assert(offsetof(mm7::Player, birthYear) == 6468);
	static_assert(offsetof(mm7::Player, equippedItems) == 6472);
	static_assert(offsetof(mm7::Player, itemExtraHand) == 6472);
	static_assert(offsetof(mm7::Player, itemMainHand) == 6476);
	static_assert(offsetof(mm7::Player, itemBow) == 6480);
	static_assert(offsetof(mm7::Player, itemArmor) == 6484);
	static_assert(offsetof(mm7::Player, itemHelm) == 6488);
	static_assert(offsetof(mm7::Player, itemBelt) == 6492);
	static_assert(offsetof(mm7::Player, itemCloak) == 6496);
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
	static_assert(offsetof(mm7::Player, fullHitPointsBonus) == 6808);
	static_assert(offsetof(mm7::Player, fullHPBonus) == 6808);
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
			std::array<uint8_t, 2> sounds; // MMExt: 1..2, here 0..1
			struct
			{
				uint8_t sound1;
				uint8_t sound2;
			};
		};
		SKIP(1);
		union
		{
			std::array<uint8_t, 5> expressions; // MMExt: 1..5, here 0..4
			struct
			{
				uint8_t expression1;
				uint8_t expression2;
				uint8_t expression3;
				uint8_t expression4;
				uint8_t expression5;
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



	struct LloydBeaconSlot // size: 0x1C
	{
		int64_t expireTime;
		union
		{
			std::array<int32_t, 3> pos;
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
			std::array<uint8_t, 2> map; // Unknown type
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
	static_assert(offsetof(mm8::LloydBeaconSlot, mapIndex) == 26);
	static_assert(offsetof(mm8::LloydBeaconSlot, map) == 26);



	struct BaseBonus // size: 0x4
	{
		int16_t base;
		int16_t bonus;
	};
	static_assert(sizeof(mm8::BaseBonus) == 0x4, "Invalid \"mm8::BaseBonus\" structure size");
	static_assert(offsetof(mm8::BaseBonus, bonus) == 2);



	struct Player // size: 0x1D28
	{
		union
		{
			std::array<int64_t, 20> conditions;
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
		std::array<char, 32> name; // fixed size string, requires null terminator
		std::array<char, 256> biography; // fixed size string, requires null terminator
		SKIP(394);
		uint8_t clas;
		uint8_t face;
		union
		{
			struct // size: 0x1C, MMExt union
			{
				mm8::BaseBonus _0;
				mm8::BaseBonus _1;
				mm8::BaseBonus _2;
				mm8::BaseBonus _3;
				mm8::BaseBonus _5;
				mm8::BaseBonus _4;
				mm8::BaseBonus _6;
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
		std::array<int16_t, 39> skills;
		std::array<uint8_t, 13> awards; // MMExt: 1..104, here 0..103 | array of abits (real index = 7 - usual)
		SKIP(51);
		std::array<bool, 132> spells; // MMExt: 1..132, here 0..131
		SKIP(2);
		std::array<uint32_t, 7> usedBlackPotions; // MMExt: 264..270, here 0..6 | 4-byte boolean
		std::array<mm8::Item, 138> items; // MMExt: 1..138, here 0..137
		std::array<int32_t, 126> inventory;
		union
		{
			std::array<int16_t, 11> resistanceBase;
			struct
			{
				int16_t fireResistanceBase;
				int16_t airResistanceBase;
				int16_t waterResistanceBase;
				int16_t earthResistanceBase;
				SKIP(4);
				int16_t spiritResistanceBase;
				int16_t mindResistanceBase;
				int16_t bodyResistanceBase;
				int16_t lightResistanceBase;
				int16_t darkResistanceBase;
			};
		};
		union
		{
			std::array<int16_t, 11> resistanceBonus;
			struct
			{
				int16_t fireResistanceBonus;
				int16_t airResistanceBonus;
				int16_t waterResistanceBonus;
				int16_t earthResistanceBonus;
				SKIP(4);
				int16_t spiritResistanceBonus;
				int16_t mindResistanceBonus;
				int16_t bodyResistanceBonus;
				int16_t lightResistanceBonus;
				int16_t darkResistanceBonus;
			};
		};
		std::array<mm8::SpellBuff, 27> spellBuffs;
		int32_t voice;
		SKIP(8);
		int16_t rosterBitIndex;
		int16_t recoveryDelay;
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
			std::array<int32_t, 16> equippedItems;
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
		int8_t spellBookPage;
		uint8_t quickSpell;
		std::array<uint8_t, 64> playerBits; // MMExt: 1..512, here 0..511 | array of abits (real index = 7 - usual)
		int16_t expression;
		int16_t expressionTimePassed;
		int16_t expressionLength;
		SKIP(12);
		std::array<mm8::LloydBeaconSlot, 5> beacons;
		uint8_t devineInterventionCasts;
		uint8_t armageddonCasts;
		uint8_t fireSpikeCasts;
		SKIP(1);
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
	static_assert(offsetof(mm8::Player, spellPoints) == 7164);
	static_assert(offsetof(mm8::Player, SP) == 7164);
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