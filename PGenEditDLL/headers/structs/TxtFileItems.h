#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct StdItemsTxtItem // size: 0x14
	{
		char* nameAdd; // EditPChar | 0x0 (0 decimal)
		char* bonusStat; // EditPChar | 0x4 (4 decimal)
		union
		{
			std::array<uint8_t, 9> chanceForSlot; // 0x8 (8 decimal)
			struct
			{
				uint8_t arm; // 0x8 (8 decimal)
				uint8_t shld; // 0x9 (9 decimal)
				uint8_t helm; // 0xA (10 decimal)
				uint8_t belt; // 0xB (11 decimal)
				uint8_t cape; // 0xC (12 decimal)
				uint8_t gaunt; // 0xD (13 decimal)
				uint8_t boot; // 0xE (14 decimal)
				uint8_t ring; // 0xF (15 decimal)
				uint8_t amul; // 0x10 (16 decimal)
			};
		};
		SKIP(3);
	};
	static_assert(sizeof(mm6::StdItemsTxtItem) == 0x14, "Invalid \"mm6::StdItemsTxtItem\" structure size");
	static_assert(offsetof(mm6::StdItemsTxtItem, bonusStat) == 4);
	static_assert(offsetof(mm6::StdItemsTxtItem, chanceForSlot) == 8);
	static_assert(offsetof(mm6::StdItemsTxtItem, arm) == 8);
	static_assert(offsetof(mm6::StdItemsTxtItem, shld) == 9);
	static_assert(offsetof(mm6::StdItemsTxtItem, helm) == 10);
	static_assert(offsetof(mm6::StdItemsTxtItem, belt) == 11);
	static_assert(offsetof(mm6::StdItemsTxtItem, cape) == 12);
	static_assert(offsetof(mm6::StdItemsTxtItem, gaunt) == 13);
	static_assert(offsetof(mm6::StdItemsTxtItem, boot) == 14);
	static_assert(offsetof(mm6::StdItemsTxtItem, ring) == 15);
	static_assert(offsetof(mm6::StdItemsTxtItem, amul) == 16);



	struct SpellsTxtItem // size: 0x1C
	{
		char* name; // EditPChar | 0x0 (0 decimal)
		char* shortName; // EditPChar | 0x4 (4 decimal)
		char* description; // EditPChar | 0x8 (8 decimal)
		char* normal; // EditPChar | 0xC (12 decimal)
		char* expert; // EditPChar | 0x10 (16 decimal)
		char* master; // EditPChar | 0x14 (20 decimal)
		uint8_t damageType; // 0x18 (24 decimal)
		union
		{
			std::array<uint8_t, 3> spellPoints; // MMExt: 1..3, here 0..2 | 0x19 (25 decimal)
			struct
			{
				uint8_t spellPointsNormal; // 0x19 (25 decimal)
				uint8_t spellPointsExpert; // 0x1A (26 decimal)
				uint8_t spellPointsMaster; // 0x1B (27 decimal)
			};
		};
	};
	static_assert(sizeof(mm6::SpellsTxtItem) == 0x1C, "Invalid \"mm6::SpellsTxtItem\" structure size");
	static_assert(offsetof(mm6::SpellsTxtItem, shortName) == 4);
	static_assert(offsetof(mm6::SpellsTxtItem, description) == 8);
	static_assert(offsetof(mm6::SpellsTxtItem, normal) == 12);
	static_assert(offsetof(mm6::SpellsTxtItem, expert) == 16);
	static_assert(offsetof(mm6::SpellsTxtItem, master) == 20);
	static_assert(offsetof(mm6::SpellsTxtItem, damageType) == 24);
	static_assert(offsetof(mm6::SpellsTxtItem, spellPoints) == 25);
	static_assert(offsetof(mm6::SpellsTxtItem, spellPointsNormal) == 25);
	static_assert(offsetof(mm6::SpellsTxtItem, spellPointsExpert) == 26);
	static_assert(offsetof(mm6::SpellsTxtItem, spellPointsMaster) == 27);



	struct SpcItemsTxtItem // size: 0x1C
	{
		char* nameAdd; // EditPChar | 0x0 (0 decimal)
		char* bonusStat; // EditPChar | 0x4 (4 decimal)
		union
		{
			std::array<uint8_t, 12> chanceForSlot; // 0x8 (8 decimal)
			struct
			{
				uint8_t W1; // 0x8 (8 decimal)
				uint8_t W2; // 0x9 (9 decimal)
				uint8_t miss; // 0xA (10 decimal)
				uint8_t arm; // 0xB (11 decimal)
				uint8_t shld; // 0xC (12 decimal)
				uint8_t helm; // 0xD (13 decimal)
				uint8_t belt; // 0xE (14 decimal)
				uint8_t cape; // 0xF (15 decimal)
				uint8_t gaunt; // 0x10 (16 decimal)
				uint8_t boot; // 0x11 (17 decimal)
				uint8_t ring; // 0x12 (18 decimal)
				uint8_t amul; // 0x13 (19 decimal)
			};
		};
		int32_t value; // 0x14 (20 decimal)
		uint8_t lvl; // 0x18 (24 decimal)
		SKIP(3);
	};
	static_assert(sizeof(mm6::SpcItemsTxtItem) == 0x1C, "Invalid \"mm6::SpcItemsTxtItem\" structure size");
	static_assert(offsetof(mm6::SpcItemsTxtItem, bonusStat) == 4);
	static_assert(offsetof(mm6::SpcItemsTxtItem, chanceForSlot) == 8);
	static_assert(offsetof(mm6::SpcItemsTxtItem, W1) == 8);
	static_assert(offsetof(mm6::SpcItemsTxtItem, W2) == 9);
	static_assert(offsetof(mm6::SpcItemsTxtItem, miss) == 10);
	static_assert(offsetof(mm6::SpcItemsTxtItem, arm) == 11);
	static_assert(offsetof(mm6::SpcItemsTxtItem, shld) == 12);
	static_assert(offsetof(mm6::SpcItemsTxtItem, helm) == 13);
	static_assert(offsetof(mm6::SpcItemsTxtItem, belt) == 14);
	static_assert(offsetof(mm6::SpcItemsTxtItem, cape) == 15);
	static_assert(offsetof(mm6::SpcItemsTxtItem, gaunt) == 16);
	static_assert(offsetof(mm6::SpcItemsTxtItem, boot) == 17);
	static_assert(offsetof(mm6::SpcItemsTxtItem, ring) == 18);
	static_assert(offsetof(mm6::SpcItemsTxtItem, amul) == 19);
	static_assert(offsetof(mm6::SpcItemsTxtItem, value) == 20);
	static_assert(offsetof(mm6::SpcItemsTxtItem, lvl) == 24);



	struct NPCProfTxtItem // size: 0x4C
	{
		int32_t chance; // 0x0 (0 decimal)
		int32_t cost; // 0x4 (4 decimal)
		int32_t personality; // 0x8 (8 decimal)
		char* benefit; // EditPChar | 0xC (12 decimal)
		char* joinText; // EditPChar | 0x10 (16 decimal)
		std::array<char*, 7> profNewsTopic; // EditPChar | 0x14 (20 decimal)
		std::array<char*, 7> profNewsText; // EditPChar | 0x30 (48 decimal)
	};
	static_assert(sizeof(mm6::NPCProfTxtItem) == 0x4C, "Invalid \"mm6::NPCProfTxtItem\" structure size");
	static_assert(offsetof(mm6::NPCProfTxtItem, cost) == 4);
	static_assert(offsetof(mm6::NPCProfTxtItem, personality) == 8);
	static_assert(offsetof(mm6::NPCProfTxtItem, benefit) == 12);
	static_assert(offsetof(mm6::NPCProfTxtItem, joinText) == 16);
	static_assert(offsetof(mm6::NPCProfTxtItem, profNewsTopic) == 20);
	static_assert(offsetof(mm6::NPCProfTxtItem, profNewsText) == 48);



	struct MapStatsItem // size: 0x38
	{
		char* name; // EditPChar | 0x0 (0 decimal)
		char* fileName; // EditPChar | 0x4 (4 decimal)
		char* monster1Pic; // EditPChar | 0x8 (8 decimal)
		char* monster2Pic; // EditPChar | 0xC (12 decimal)
		char* monster3Pic; // EditPChar | 0x10 (16 decimal)
		int32_t resetCount; // 0x14 (20 decimal)
		int32_t firstVisitDay; // 0x18 (24 decimal)
		int32_t refillDays; // 0x1C (28 decimal)
		SKIP(1);
		uint8_t lock; // 0x21 (33 decimal) | MMExt info: "x5 Lock" from MapStats.txt. In MM6 the condition for successful disarming is !Lua[[Lock*5 < player:GetDisarmTrapTotalSkill() + math.random(0, 9)]]. In MM7+ the condition is !Lua[[Lock*2 <= player:GetDisarmTrapTotalSkill()]].
		uint8_t trap; // 0x22 (34 decimal) | MMExt info: "D20's Trap" from MapStats.txt. The damage is 'Trap' rolls of '1'-'20' damage.
		uint8_t tres; // 0x23 (35 decimal)
		uint8_t encounterChance; // 0x24 (36 decimal)
		uint8_t encounterChanceM1; // 0x25 (37 decimal)
		uint8_t encounterChanceM2; // 0x26 (38 decimal)
		uint8_t encounterChanceM3; // 0x27 (39 decimal)
		uint8_t mon1Dif; // 0x28 (40 decimal)
		uint8_t mon1Low; // 0x29 (41 decimal)
		uint8_t mon1Hi; // 0x2A (42 decimal)
		uint8_t mon2Dif; // 0x2B (43 decimal)
		uint8_t mon2Low; // 0x2C (44 decimal)
		uint8_t mon2Hi; // 0x2D (45 decimal)
		uint8_t mon3Dif; // 0x2E (46 decimal)
		uint8_t mon3Low; // 0x2F (47 decimal)
		uint8_t mon3Hi; // 0x30 (48 decimal)
		SKIP(3);
		uint8_t redbookTrack; // 0x34 (52 decimal)
		SKIP(3);
	};
	static_assert(sizeof(mm6::MapStatsItem) == 0x38, "Invalid \"mm6::MapStatsItem\" structure size");
	static_assert(offsetof(mm6::MapStatsItem, fileName) == 4);
	static_assert(offsetof(mm6::MapStatsItem, monster1Pic) == 8);
	static_assert(offsetof(mm6::MapStatsItem, monster2Pic) == 12);
	static_assert(offsetof(mm6::MapStatsItem, monster3Pic) == 16);
	static_assert(offsetof(mm6::MapStatsItem, resetCount) == 20);
	static_assert(offsetof(mm6::MapStatsItem, firstVisitDay) == 24);
	static_assert(offsetof(mm6::MapStatsItem, refillDays) == 28);
	static_assert(offsetof(mm6::MapStatsItem, lock) == 33);
	static_assert(offsetof(mm6::MapStatsItem, trap) == 34);
	static_assert(offsetof(mm6::MapStatsItem, tres) == 35);
	static_assert(offsetof(mm6::MapStatsItem, encounterChance) == 36);
	static_assert(offsetof(mm6::MapStatsItem, encounterChanceM1) == 37);
	static_assert(offsetof(mm6::MapStatsItem, encounterChanceM2) == 38);
	static_assert(offsetof(mm6::MapStatsItem, encounterChanceM3) == 39);
	static_assert(offsetof(mm6::MapStatsItem, mon1Dif) == 40);
	static_assert(offsetof(mm6::MapStatsItem, mon1Low) == 41);
	static_assert(offsetof(mm6::MapStatsItem, mon1Hi) == 42);
	static_assert(offsetof(mm6::MapStatsItem, mon2Dif) == 43);
	static_assert(offsetof(mm6::MapStatsItem, mon2Low) == 44);
	static_assert(offsetof(mm6::MapStatsItem, mon2Hi) == 45);
	static_assert(offsetof(mm6::MapStatsItem, mon3Dif) == 46);
	static_assert(offsetof(mm6::MapStatsItem, mon3Low) == 47);
	static_assert(offsetof(mm6::MapStatsItem, mon3Hi) == 48);
	static_assert(offsetof(mm6::MapStatsItem, redbookTrack) == 52);



	struct ItemsTxtItem // size: 0x28
	{
		char* picture; // EditPChar | 0x0 (0 decimal)
		char* name; // EditPChar | 0x4 (4 decimal)
		char* notIdentifiedName; // EditPChar | 0x8 (8 decimal)
		char* notes; // EditPChar | 0xC (12 decimal)
		int32_t value; // 0x10 (16 decimal)
		uint8_t equipStat; // 0x14 (20 decimal) | MMExt info: Subtract 1 from #const.ItemType:# value
		std::array<uint8_t, 1> skill; // Unknown type | 0x15 (21 decimal)
		uint8_t mod1DiceCount; // 0x16 (22 decimal)
		uint8_t mod1DiceSides; // 0x17 (23 decimal)
		uint8_t mod2; // 0x18 (24 decimal)
		uint8_t material; // 0x19 (25 decimal) | MMExt info: 0 = normal,  1 = artifact,  2 = relic,  3 = special
		std::array<uint8_t, 6> chanceByLevel; // MMExt: 1..6, here 0..5 | 0x1A (26 decimal)
		int8_t idRepSt; // 0x20 (32 decimal)
		int8_t spriteIndex; // 0x21 (33 decimal)
		int16_t equipX; // 0x22 (34 decimal)
		int16_t equipY; // 0x24 (36 decimal)
		SKIP(2);
	};
	static_assert(sizeof(mm6::ItemsTxtItem) == 0x28, "Invalid \"mm6::ItemsTxtItem\" structure size");
	static_assert(offsetof(mm6::ItemsTxtItem, name) == 4);
	static_assert(offsetof(mm6::ItemsTxtItem, notIdentifiedName) == 8);
	static_assert(offsetof(mm6::ItemsTxtItem, notes) == 12);
	static_assert(offsetof(mm6::ItemsTxtItem, value) == 16);
	static_assert(offsetof(mm6::ItemsTxtItem, equipStat) == 20);
	static_assert(offsetof(mm6::ItemsTxtItem, skill) == 21);
	static_assert(offsetof(mm6::ItemsTxtItem, mod1DiceCount) == 22);
	static_assert(offsetof(mm6::ItemsTxtItem, mod1DiceSides) == 23);
	static_assert(offsetof(mm6::ItemsTxtItem, mod2) == 24);
	static_assert(offsetof(mm6::ItemsTxtItem, material) == 25);
	static_assert(offsetof(mm6::ItemsTxtItem, chanceByLevel) == 26);
	static_assert(offsetof(mm6::ItemsTxtItem, idRepSt) == 32);
	static_assert(offsetof(mm6::ItemsTxtItem, spriteIndex) == 33);
	static_assert(offsetof(mm6::ItemsTxtItem, equipX) == 34);
	static_assert(offsetof(mm6::ItemsTxtItem, equipY) == 36);



	struct Events2DItem // size: 0x30
	{
		int16_t type; // 0x0 (0 decimal)
		int16_t picture; // 0x2 (2 decimal)
		char* name; // EditPChar | 0x4 (4 decimal)
		char* ownerName; // EditPChar | 0x8 (8 decimal)
		char* enterText; // EditPChar | 0xC (12 decimal)
		char* ownerTitle; // EditPChar | 0x10 (16 decimal)
		union
		{
			int16_t ownerPicture; // 0x14 (20 decimal) | MMExt info: Was called 'PictureUnk' before MMExtension v2.3, old name is supported for backward compatibility
			int16_t pictureUnk; // 0x14 (20 decimal)
		};
		int16_t state; // 0x16 (22 decimal)
		int16_t rep; // 0x18 (24 decimal)
		int16_t per; // 0x1A (26 decimal)
		int16_t c; // 0x1C (28 decimal)
		SKIP(2);
		float val; // 0x20 (32 decimal)
		int16_t openHour; // 0x24 (36 decimal)
		int16_t closeHour; // 0x26 (38 decimal)
		int16_t exitPic; // 0x28 (40 decimal)
		int16_t exitMap; // 0x2A (42 decimal)
		union
		{
			int16_t QBit; // 0x2C (44 decimal) | MMExt info: Was called 'QuestBitRestriction' before MMExtension v2.3, old name is supported for backward compatibility
			int16_t questBitRestriction; // 0x2C (44 decimal)
		};
		SKIP(2);
	};
	static_assert(sizeof(mm6::Events2DItem) == 0x30, "Invalid \"mm6::Events2DItem\" structure size");
	static_assert(offsetof(mm6::Events2DItem, picture) == 2);
	static_assert(offsetof(mm6::Events2DItem, name) == 4);
	static_assert(offsetof(mm6::Events2DItem, ownerName) == 8);
	static_assert(offsetof(mm6::Events2DItem, enterText) == 12);
	static_assert(offsetof(mm6::Events2DItem, ownerTitle) == 16);
	static_assert(offsetof(mm6::Events2DItem, ownerPicture) == 20);
	static_assert(offsetof(mm6::Events2DItem, pictureUnk) == 20);
	static_assert(offsetof(mm6::Events2DItem, state) == 22);
	static_assert(offsetof(mm6::Events2DItem, rep) == 24);
	static_assert(offsetof(mm6::Events2DItem, per) == 26);
	static_assert(offsetof(mm6::Events2DItem, c) == 28);
	static_assert(offsetof(mm6::Events2DItem, val) == 32);
	static_assert(offsetof(mm6::Events2DItem, openHour) == 36);
	static_assert(offsetof(mm6::Events2DItem, closeHour) == 38);
	static_assert(offsetof(mm6::Events2DItem, exitPic) == 40);
	static_assert(offsetof(mm6::Events2DItem, exitMap) == 42);
	static_assert(offsetof(mm6::Events2DItem, QBit) == 44);
	static_assert(offsetof(mm6::Events2DItem, questBitRestriction) == 44);
}
namespace mm7
{
	struct StdItemsTxtItem // size: 0x14
	{
		char* nameAdd; // EditPChar | 0x0 (0 decimal)
		char* bonusStat; // EditPChar | 0x4 (4 decimal)
		union
		{
			std::array<uint8_t, 9> chanceForSlot; // 0x8 (8 decimal)
			struct
			{
				uint8_t arm; // 0x8 (8 decimal)
				uint8_t shld; // 0x9 (9 decimal)
				uint8_t helm; // 0xA (10 decimal)
				uint8_t belt; // 0xB (11 decimal)
				uint8_t cape; // 0xC (12 decimal)
				uint8_t gaunt; // 0xD (13 decimal)
				uint8_t boot; // 0xE (14 decimal)
				uint8_t ring; // 0xF (15 decimal)
				uint8_t amul; // 0x10 (16 decimal)
			};
		};
		SKIP(3);
	};
	static_assert(sizeof(mm7::StdItemsTxtItem) == 0x14, "Invalid \"mm7::StdItemsTxtItem\" structure size");
	static_assert(offsetof(mm7::StdItemsTxtItem, bonusStat) == 4);
	static_assert(offsetof(mm7::StdItemsTxtItem, chanceForSlot) == 8);
	static_assert(offsetof(mm7::StdItemsTxtItem, arm) == 8);
	static_assert(offsetof(mm7::StdItemsTxtItem, shld) == 9);
	static_assert(offsetof(mm7::StdItemsTxtItem, helm) == 10);
	static_assert(offsetof(mm7::StdItemsTxtItem, belt) == 11);
	static_assert(offsetof(mm7::StdItemsTxtItem, cape) == 12);
	static_assert(offsetof(mm7::StdItemsTxtItem, gaunt) == 13);
	static_assert(offsetof(mm7::StdItemsTxtItem, boot) == 14);
	static_assert(offsetof(mm7::StdItemsTxtItem, ring) == 15);
	static_assert(offsetof(mm7::StdItemsTxtItem, amul) == 16);



	struct SpellsTxtItem // size: 0x24
	{
		char* name; // EditPChar | 0x0 (0 decimal)
		char* shortName; // EditPChar | 0x4 (4 decimal)
		char* description; // EditPChar | 0x8 (8 decimal)
		char* normal; // EditPChar | 0xC (12 decimal)
		char* expert; // EditPChar | 0x10 (16 decimal)
		char* master; // EditPChar | 0x14 (20 decimal)
		union
		{
			char* GM; // EditPChar | 0x18 (24 decimal)
			char* grandMaster; // EditPChar | 0x18 (24 decimal)
		};
		uint8_t damageType; // 0x1C (28 decimal)
		union
		{
			std::array<uint8_t, 4> spellPoints; // MMExt: 1..4, here 0..3 | 0x1D (29 decimal)
			struct
			{
				uint8_t spellPointsNormal; // 0x1D (29 decimal)
				uint8_t spellPointsExpert; // 0x1E (30 decimal)
				uint8_t spellPointsMaster; // 0x1F (31 decimal)
				uint8_t spellPointsGM; // 0x20 (32 decimal)
			};
		};
		SKIP(3);
	};
	static_assert(sizeof(mm7::SpellsTxtItem) == 0x24, "Invalid \"mm7::SpellsTxtItem\" structure size");
	static_assert(offsetof(mm7::SpellsTxtItem, shortName) == 4);
	static_assert(offsetof(mm7::SpellsTxtItem, description) == 8);
	static_assert(offsetof(mm7::SpellsTxtItem, normal) == 12);
	static_assert(offsetof(mm7::SpellsTxtItem, expert) == 16);
	static_assert(offsetof(mm7::SpellsTxtItem, master) == 20);
	static_assert(offsetof(mm7::SpellsTxtItem, GM) == 24);
	static_assert(offsetof(mm7::SpellsTxtItem, grandMaster) == 24);
	static_assert(offsetof(mm7::SpellsTxtItem, damageType) == 28);
	static_assert(offsetof(mm7::SpellsTxtItem, spellPoints) == 29);
	static_assert(offsetof(mm7::SpellsTxtItem, spellPointsNormal) == 29);
	static_assert(offsetof(mm7::SpellsTxtItem, spellPointsExpert) == 30);
	static_assert(offsetof(mm7::SpellsTxtItem, spellPointsMaster) == 31);
	static_assert(offsetof(mm7::SpellsTxtItem, spellPointsGM) == 32);



	struct SpcItemsTxtItem // size: 0x1C
	{
		char* nameAdd; // EditPChar | 0x0 (0 decimal)
		char* bonusStat; // EditPChar | 0x4 (4 decimal)
		union
		{
			std::array<uint8_t, 12> chanceForSlot; // 0x8 (8 decimal)
			struct
			{
				uint8_t W1; // 0x8 (8 decimal)
				uint8_t W2; // 0x9 (9 decimal)
				uint8_t miss; // 0xA (10 decimal)
				uint8_t arm; // 0xB (11 decimal)
				uint8_t shld; // 0xC (12 decimal)
				uint8_t helm; // 0xD (13 decimal)
				uint8_t belt; // 0xE (14 decimal)
				uint8_t cape; // 0xF (15 decimal)
				uint8_t gaunt; // 0x10 (16 decimal)
				uint8_t boot; // 0x11 (17 decimal)
				uint8_t ring; // 0x12 (18 decimal)
				uint8_t amul; // 0x13 (19 decimal)
			};
		};
		int32_t value; // 0x14 (20 decimal)
		uint8_t lvl; // 0x18 (24 decimal)
		SKIP(3);
	};
	static_assert(sizeof(mm7::SpcItemsTxtItem) == 0x1C, "Invalid \"mm7::SpcItemsTxtItem\" structure size");
	static_assert(offsetof(mm7::SpcItemsTxtItem, bonusStat) == 4);
	static_assert(offsetof(mm7::SpcItemsTxtItem, chanceForSlot) == 8);
	static_assert(offsetof(mm7::SpcItemsTxtItem, W1) == 8);
	static_assert(offsetof(mm7::SpcItemsTxtItem, W2) == 9);
	static_assert(offsetof(mm7::SpcItemsTxtItem, miss) == 10);
	static_assert(offsetof(mm7::SpcItemsTxtItem, arm) == 11);
	static_assert(offsetof(mm7::SpcItemsTxtItem, shld) == 12);
	static_assert(offsetof(mm7::SpcItemsTxtItem, helm) == 13);
	static_assert(offsetof(mm7::SpcItemsTxtItem, belt) == 14);
	static_assert(offsetof(mm7::SpcItemsTxtItem, cape) == 15);
	static_assert(offsetof(mm7::SpcItemsTxtItem, gaunt) == 16);
	static_assert(offsetof(mm7::SpcItemsTxtItem, boot) == 17);
	static_assert(offsetof(mm7::SpcItemsTxtItem, ring) == 18);
	static_assert(offsetof(mm7::SpcItemsTxtItem, amul) == 19);
	static_assert(offsetof(mm7::SpcItemsTxtItem, value) == 20);
	static_assert(offsetof(mm7::SpcItemsTxtItem, lvl) == 24);



	struct NPCProfTxtItem // size: 0x14
	{
		int32_t cost; // 0x0 (0 decimal)
		char* benefit; // EditPChar | 0x4 (4 decimal)
		char* actionText; // EditPChar | 0x8 (8 decimal)
		char* joinText; // EditPChar | 0xC (12 decimal)
		char* dismissText; // EditPChar | 0x10 (16 decimal)
	};
	static_assert(sizeof(mm7::NPCProfTxtItem) == 0x14, "Invalid \"mm7::NPCProfTxtItem\" structure size");
	static_assert(offsetof(mm7::NPCProfTxtItem, benefit) == 4);
	static_assert(offsetof(mm7::NPCProfTxtItem, actionText) == 8);
	static_assert(offsetof(mm7::NPCProfTxtItem, joinText) == 12);
	static_assert(offsetof(mm7::NPCProfTxtItem, dismissText) == 16);



	struct MapStatsItem // size: 0x44
	{
		char* name; // EditPChar | 0x0 (0 decimal)
		char* fileName; // EditPChar | 0x4 (4 decimal)
		char* monster1Pic; // EditPChar | 0x8 (8 decimal)
		char* monster2Pic; // EditPChar | 0xC (12 decimal)
		char* monster3Pic; // EditPChar | 0x10 (16 decimal)
		int32_t resetCount; // 0x14 (20 decimal)
		int32_t firstVisitDay; // 0x18 (24 decimal)
		int32_t refillDays; // 0x1C (28 decimal)
		int32_t alertDays; // 0x20 (32 decimal)
		int32_t stealPerm; // 0x24 (36 decimal)
		int32_t per; // 0x28 (40 decimal)
		SKIP(1);
		uint8_t lock; // 0x2D (45 decimal) | MMExt info: "x5 Lock" from MapStats.txt. In MM6 the condition for successful disarming is !Lua[[Lock*5 < player:GetDisarmTrapTotalSkill() + math.random(0, 9)]]. In MM7+ the condition is !Lua[[Lock*2 <= player:GetDisarmTrapTotalSkill()]].
		uint8_t trap; // 0x2E (46 decimal) | MMExt info: "D20's Trap" from MapStats.txt. The damage is 'Trap' rolls of '1'-'20' damage.
		uint8_t tres; // 0x2F (47 decimal)
		uint8_t encounterChance; // 0x30 (48 decimal)
		uint8_t encounterChanceM1; // 0x31 (49 decimal)
		uint8_t encounterChanceM2; // 0x32 (50 decimal)
		uint8_t encounterChanceM3; // 0x33 (51 decimal)
		uint8_t mon1Dif; // 0x34 (52 decimal)
		uint8_t mon1Low; // 0x35 (53 decimal)
		uint8_t mon1Hi; // 0x36 (54 decimal)
		uint8_t mon2Dif; // 0x37 (55 decimal)
		uint8_t mon2Low; // 0x38 (56 decimal)
		uint8_t mon2Hi; // 0x39 (57 decimal)
		uint8_t mon3Dif; // 0x3A (58 decimal)
		uint8_t mon3Low; // 0x3B (59 decimal)
		uint8_t mon3Hi; // 0x3C (60 decimal)
		SKIP(3);
		uint8_t redbookTrack; // 0x40 (64 decimal)
		uint8_t eaxEnvironments; // 0x41 (65 decimal)
		SKIP(2);
	};
	static_assert(sizeof(mm7::MapStatsItem) == 0x44, "Invalid \"mm7::MapStatsItem\" structure size");
	static_assert(offsetof(mm7::MapStatsItem, fileName) == 4);
	static_assert(offsetof(mm7::MapStatsItem, monster1Pic) == 8);
	static_assert(offsetof(mm7::MapStatsItem, monster2Pic) == 12);
	static_assert(offsetof(mm7::MapStatsItem, monster3Pic) == 16);
	static_assert(offsetof(mm7::MapStatsItem, resetCount) == 20);
	static_assert(offsetof(mm7::MapStatsItem, firstVisitDay) == 24);
	static_assert(offsetof(mm7::MapStatsItem, refillDays) == 28);
	static_assert(offsetof(mm7::MapStatsItem, alertDays) == 32);
	static_assert(offsetof(mm7::MapStatsItem, stealPerm) == 36);
	static_assert(offsetof(mm7::MapStatsItem, per) == 40);
	static_assert(offsetof(mm7::MapStatsItem, lock) == 45);
	static_assert(offsetof(mm7::MapStatsItem, trap) == 46);
	static_assert(offsetof(mm7::MapStatsItem, tres) == 47);
	static_assert(offsetof(mm7::MapStatsItem, encounterChance) == 48);
	static_assert(offsetof(mm7::MapStatsItem, encounterChanceM1) == 49);
	static_assert(offsetof(mm7::MapStatsItem, encounterChanceM2) == 50);
	static_assert(offsetof(mm7::MapStatsItem, encounterChanceM3) == 51);
	static_assert(offsetof(mm7::MapStatsItem, mon1Dif) == 52);
	static_assert(offsetof(mm7::MapStatsItem, mon1Low) == 53);
	static_assert(offsetof(mm7::MapStatsItem, mon1Hi) == 54);
	static_assert(offsetof(mm7::MapStatsItem, mon2Dif) == 55);
	static_assert(offsetof(mm7::MapStatsItem, mon2Low) == 56);
	static_assert(offsetof(mm7::MapStatsItem, mon2Hi) == 57);
	static_assert(offsetof(mm7::MapStatsItem, mon3Dif) == 58);
	static_assert(offsetof(mm7::MapStatsItem, mon3Low) == 59);
	static_assert(offsetof(mm7::MapStatsItem, mon3Hi) == 60);
	static_assert(offsetof(mm7::MapStatsItem, redbookTrack) == 64);
	static_assert(offsetof(mm7::MapStatsItem, eaxEnvironments) == 65);



	struct ItemsTxtItem // size: 0x30
	{
		char* picture; // EditPChar | 0x0 (0 decimal)
		char* name; // EditPChar | 0x4 (4 decimal)
		char* notIdentifiedName; // EditPChar | 0x8 (8 decimal)
		char* notes; // EditPChar | 0xC (12 decimal)
		int32_t value; // 0x10 (16 decimal)
		int16_t spriteIndex; // 0x14 (20 decimal)
		SKIP(2);
		int16_t equipX; // 0x18 (24 decimal)
		int16_t equipY; // 0x1A (26 decimal)
		uint8_t equipStat; // 0x1C (28 decimal) | MMExt info: Subtract 1 from #const.ItemType:# value
		uint8_t skill; // 0x1D (29 decimal)
		uint8_t mod1DiceCount; // 0x1E (30 decimal)
		uint8_t mod1DiceSides; // 0x1F (31 decimal)
		uint8_t mod2; // 0x20 (32 decimal)
		uint8_t material; // 0x21 (33 decimal) | MMExt info: 0 = normal,  1 = artifact,  2 = relic,  3 = special
		uint8_t bonus2; // 0x22 (34 decimal) | MMExt info: VarA
		uint8_t bonus; // 0x23 (35 decimal) | MMExt info: VarA
		uint8_t bonusStrength; // 0x24 (36 decimal) | MMExt info: VarB
		SKIP(3);
		std::array<uint8_t, 6> chanceByLevel; // MMExt: 1..6, here 0..5 | 0x28 (40 decimal)
		int8_t idRepSt; // 0x2E (46 decimal)
		SKIP(1);
	};
	static_assert(sizeof(mm7::ItemsTxtItem) == 0x30, "Invalid \"mm7::ItemsTxtItem\" structure size");
	static_assert(offsetof(mm7::ItemsTxtItem, name) == 4);
	static_assert(offsetof(mm7::ItemsTxtItem, notIdentifiedName) == 8);
	static_assert(offsetof(mm7::ItemsTxtItem, notes) == 12);
	static_assert(offsetof(mm7::ItemsTxtItem, value) == 16);
	static_assert(offsetof(mm7::ItemsTxtItem, spriteIndex) == 20);
	static_assert(offsetof(mm7::ItemsTxtItem, equipX) == 24);
	static_assert(offsetof(mm7::ItemsTxtItem, equipY) == 26);
	static_assert(offsetof(mm7::ItemsTxtItem, equipStat) == 28);
	static_assert(offsetof(mm7::ItemsTxtItem, skill) == 29);
	static_assert(offsetof(mm7::ItemsTxtItem, mod1DiceCount) == 30);
	static_assert(offsetof(mm7::ItemsTxtItem, mod1DiceSides) == 31);
	static_assert(offsetof(mm7::ItemsTxtItem, mod2) == 32);
	static_assert(offsetof(mm7::ItemsTxtItem, material) == 33);
	static_assert(offsetof(mm7::ItemsTxtItem, bonus2) == 34);
	static_assert(offsetof(mm7::ItemsTxtItem, bonus) == 35);
	static_assert(offsetof(mm7::ItemsTxtItem, bonusStrength) == 36);
	static_assert(offsetof(mm7::ItemsTxtItem, chanceByLevel) == 40);
	static_assert(offsetof(mm7::ItemsTxtItem, idRepSt) == 46);



	struct Events2DItem // size: 0x34
	{
		int16_t type; // 0x0 (0 decimal)
		int16_t picture; // 0x2 (2 decimal)
		char* name; // EditPChar | 0x4 (4 decimal)
		char* ownerName; // EditPChar | 0x8 (8 decimal)
		char* enterText; // EditPChar | 0xC (12 decimal)
		char* ownerTitle; // EditPChar | 0x10 (16 decimal)
		union
		{
			int16_t ownerPicture; // 0x14 (20 decimal) | MMExt info: Was called 'PictureUnk' before MMExtension v2.3, old name is supported for backward compatibility
			int16_t pictureUnk; // 0x14 (20 decimal)
		};
		int16_t state; // 0x16 (22 decimal)
		int16_t rep; // 0x18 (24 decimal)
		int16_t per; // 0x1A (26 decimal)
		int16_t c; // 0x1C (28 decimal)
		SKIP(2);
		float val; // 0x20 (32 decimal)
		float a; // 0x24 (36 decimal)
		int16_t openHour; // 0x28 (40 decimal)
		int16_t closeHour; // 0x2A (42 decimal)
		int16_t exitPic; // 0x2C (44 decimal)
		int16_t exitMap; // 0x2E (46 decimal)
		union
		{
			int16_t QBit; // 0x30 (48 decimal) | MMExt info: Was called 'QuestBitRestriction' before MMExtension v2.3, old name is supported for backward compatibility
			int16_t questBitRestriction; // 0x30 (48 decimal)
		};
		SKIP(2);
	};
	static_assert(sizeof(mm7::Events2DItem) == 0x34, "Invalid \"mm7::Events2DItem\" structure size");
	static_assert(offsetof(mm7::Events2DItem, picture) == 2);
	static_assert(offsetof(mm7::Events2DItem, name) == 4);
	static_assert(offsetof(mm7::Events2DItem, ownerName) == 8);
	static_assert(offsetof(mm7::Events2DItem, enterText) == 12);
	static_assert(offsetof(mm7::Events2DItem, ownerTitle) == 16);
	static_assert(offsetof(mm7::Events2DItem, ownerPicture) == 20);
	static_assert(offsetof(mm7::Events2DItem, pictureUnk) == 20);
	static_assert(offsetof(mm7::Events2DItem, state) == 22);
	static_assert(offsetof(mm7::Events2DItem, rep) == 24);
	static_assert(offsetof(mm7::Events2DItem, per) == 26);
	static_assert(offsetof(mm7::Events2DItem, c) == 28);
	static_assert(offsetof(mm7::Events2DItem, val) == 32);
	static_assert(offsetof(mm7::Events2DItem, a) == 36);
	static_assert(offsetof(mm7::Events2DItem, openHour) == 40);
	static_assert(offsetof(mm7::Events2DItem, closeHour) == 42);
	static_assert(offsetof(mm7::Events2DItem, exitPic) == 44);
	static_assert(offsetof(mm7::Events2DItem, exitMap) == 46);
	static_assert(offsetof(mm7::Events2DItem, QBit) == 48);
	static_assert(offsetof(mm7::Events2DItem, questBitRestriction) == 48);



	struct HistoryTxtItem // size: 0xC
	{
		char* text; // EditPChar | 0x0 (0 decimal)
		char* title; // EditPChar | 0x4 (4 decimal)
		int8_t time; // 0x8 (8 decimal)
		SKIP(3);
	};
	static_assert(sizeof(mm7::HistoryTxtItem) == 0xC, "Invalid \"mm7::HistoryTxtItem\" structure size");
	static_assert(offsetof(mm7::HistoryTxtItem, title) == 4);
	static_assert(offsetof(mm7::HistoryTxtItem, time) == 8);
}
namespace mm8
{
	struct StdItemsTxtItem // size: 0x14
	{
		char* nameAdd; // EditPChar | 0x0 (0 decimal)
		char* bonusStat; // EditPChar | 0x4 (4 decimal)
		union
		{
			std::array<uint8_t, 9> chanceForSlot; // 0x8 (8 decimal)
			struct
			{
				uint8_t arm; // 0x8 (8 decimal)
				uint8_t shld; // 0x9 (9 decimal)
				uint8_t helm; // 0xA (10 decimal)
				uint8_t belt; // 0xB (11 decimal)
				uint8_t cape; // 0xC (12 decimal)
				uint8_t gaunt; // 0xD (13 decimal)
				uint8_t boot; // 0xE (14 decimal)
				uint8_t ring; // 0xF (15 decimal)
				uint8_t amul; // 0x10 (16 decimal)
			};
		};
		SKIP(3);
	};
	static_assert(sizeof(mm8::StdItemsTxtItem) == 0x14, "Invalid \"mm8::StdItemsTxtItem\" structure size");
	static_assert(offsetof(mm8::StdItemsTxtItem, bonusStat) == 4);
	static_assert(offsetof(mm8::StdItemsTxtItem, chanceForSlot) == 8);
	static_assert(offsetof(mm8::StdItemsTxtItem, arm) == 8);
	static_assert(offsetof(mm8::StdItemsTxtItem, shld) == 9);
	static_assert(offsetof(mm8::StdItemsTxtItem, helm) == 10);
	static_assert(offsetof(mm8::StdItemsTxtItem, belt) == 11);
	static_assert(offsetof(mm8::StdItemsTxtItem, cape) == 12);
	static_assert(offsetof(mm8::StdItemsTxtItem, gaunt) == 13);
	static_assert(offsetof(mm8::StdItemsTxtItem, boot) == 14);
	static_assert(offsetof(mm8::StdItemsTxtItem, ring) == 15);
	static_assert(offsetof(mm8::StdItemsTxtItem, amul) == 16);



	struct SpellsTxtItem // size: 0x24
	{
		char* name; // EditPChar | 0x0 (0 decimal)
		char* shortName; // EditPChar | 0x4 (4 decimal)
		char* description; // EditPChar | 0x8 (8 decimal)
		char* normal; // EditPChar | 0xC (12 decimal)
		char* expert; // EditPChar | 0x10 (16 decimal)
		char* master; // EditPChar | 0x14 (20 decimal)
		union
		{
			char* GM; // EditPChar | 0x18 (24 decimal)
			char* grandMaster; // EditPChar | 0x18 (24 decimal)
		};
		uint8_t damageType; // 0x1C (28 decimal)
		union
		{
			std::array<uint8_t, 4> spellPoints; // MMExt: 1..4, here 0..3 | 0x1D (29 decimal)
			struct
			{
				uint8_t spellPointsNormal; // 0x1D (29 decimal)
				uint8_t spellPointsExpert; // 0x1E (30 decimal)
				uint8_t spellPointsMaster; // 0x1F (31 decimal)
				uint8_t spellPointsGM; // 0x20 (32 decimal)
			};
		};
		SKIP(3);
	};
	static_assert(sizeof(mm8::SpellsTxtItem) == 0x24, "Invalid \"mm8::SpellsTxtItem\" structure size");
	static_assert(offsetof(mm8::SpellsTxtItem, shortName) == 4);
	static_assert(offsetof(mm8::SpellsTxtItem, description) == 8);
	static_assert(offsetof(mm8::SpellsTxtItem, normal) == 12);
	static_assert(offsetof(mm8::SpellsTxtItem, expert) == 16);
	static_assert(offsetof(mm8::SpellsTxtItem, master) == 20);
	static_assert(offsetof(mm8::SpellsTxtItem, GM) == 24);
	static_assert(offsetof(mm8::SpellsTxtItem, grandMaster) == 24);
	static_assert(offsetof(mm8::SpellsTxtItem, damageType) == 28);
	static_assert(offsetof(mm8::SpellsTxtItem, spellPoints) == 29);
	static_assert(offsetof(mm8::SpellsTxtItem, spellPointsNormal) == 29);
	static_assert(offsetof(mm8::SpellsTxtItem, spellPointsExpert) == 30);
	static_assert(offsetof(mm8::SpellsTxtItem, spellPointsMaster) == 31);
	static_assert(offsetof(mm8::SpellsTxtItem, spellPointsGM) == 32);



	struct SpcItemsTxtItem // size: 0x1C
	{
		char* nameAdd; // EditPChar | 0x0 (0 decimal)
		char* bonusStat; // EditPChar | 0x4 (4 decimal)
		union
		{
			std::array<uint8_t, 12> chanceForSlot; // 0x8 (8 decimal)
			struct
			{
				uint8_t W1; // 0x8 (8 decimal)
				uint8_t W2; // 0x9 (9 decimal)
				uint8_t miss; // 0xA (10 decimal)
				uint8_t arm; // 0xB (11 decimal)
				uint8_t shld; // 0xC (12 decimal)
				uint8_t helm; // 0xD (13 decimal)
				uint8_t belt; // 0xE (14 decimal)
				uint8_t cape; // 0xF (15 decimal)
				uint8_t gaunt; // 0x10 (16 decimal)
				uint8_t boot; // 0x11 (17 decimal)
				uint8_t ring; // 0x12 (18 decimal)
				uint8_t amul; // 0x13 (19 decimal)
			};
		};
		int32_t value; // 0x14 (20 decimal)
		uint8_t lvl; // 0x18 (24 decimal)
		SKIP(3);
	};
	static_assert(sizeof(mm8::SpcItemsTxtItem) == 0x1C, "Invalid \"mm8::SpcItemsTxtItem\" structure size");
	static_assert(offsetof(mm8::SpcItemsTxtItem, bonusStat) == 4);
	static_assert(offsetof(mm8::SpcItemsTxtItem, chanceForSlot) == 8);
	static_assert(offsetof(mm8::SpcItemsTxtItem, W1) == 8);
	static_assert(offsetof(mm8::SpcItemsTxtItem, W2) == 9);
	static_assert(offsetof(mm8::SpcItemsTxtItem, miss) == 10);
	static_assert(offsetof(mm8::SpcItemsTxtItem, arm) == 11);
	static_assert(offsetof(mm8::SpcItemsTxtItem, shld) == 12);
	static_assert(offsetof(mm8::SpcItemsTxtItem, helm) == 13);
	static_assert(offsetof(mm8::SpcItemsTxtItem, belt) == 14);
	static_assert(offsetof(mm8::SpcItemsTxtItem, cape) == 15);
	static_assert(offsetof(mm8::SpcItemsTxtItem, gaunt) == 16);
	static_assert(offsetof(mm8::SpcItemsTxtItem, boot) == 17);
	static_assert(offsetof(mm8::SpcItemsTxtItem, ring) == 18);
	static_assert(offsetof(mm8::SpcItemsTxtItem, amul) == 19);
	static_assert(offsetof(mm8::SpcItemsTxtItem, value) == 20);
	static_assert(offsetof(mm8::SpcItemsTxtItem, lvl) == 24);



	struct MapStatsItem // size: 0x44
	{
		char* name; // EditPChar | 0x0 (0 decimal)
		char* fileName; // EditPChar | 0x4 (4 decimal)
		char* monster1Pic; // EditPChar | 0x8 (8 decimal)
		char* monster2Pic; // EditPChar | 0xC (12 decimal)
		char* monster3Pic; // EditPChar | 0x10 (16 decimal)
		int32_t resetCount; // 0x14 (20 decimal)
		int32_t firstVisitDay; // 0x18 (24 decimal)
		int32_t refillDays; // 0x1C (28 decimal)
		int32_t alertDays; // 0x20 (32 decimal)
		int32_t stealPerm; // 0x24 (36 decimal)
		int32_t per; // 0x28 (40 decimal)
		SKIP(1);
		uint8_t lock; // 0x2D (45 decimal) | MMExt info: x5Lock
		uint8_t trap; // 0x2E (46 decimal) | MMExt info: D20sTrap
		uint8_t tres; // 0x2F (47 decimal)
		uint8_t encounterChance; // 0x30 (48 decimal)
		uint8_t encounterChanceM1; // 0x31 (49 decimal)
		uint8_t encounterChanceM2; // 0x32 (50 decimal)
		uint8_t encounterChanceM3; // 0x33 (51 decimal)
		uint8_t mon1Dif; // 0x34 (52 decimal)
		uint8_t mon1Low; // 0x35 (53 decimal)
		uint8_t mon1Hi; // 0x36 (54 decimal)
		uint8_t mon2Dif; // 0x37 (55 decimal)
		uint8_t mon2Low; // 0x38 (56 decimal)
		uint8_t mon2Hi; // 0x39 (57 decimal)
		uint8_t mon3Dif; // 0x3A (58 decimal)
		uint8_t mon3Low; // 0x3B (59 decimal)
		uint8_t mon3Hi; // 0x3C (60 decimal)
		SKIP(3);
		uint8_t redbookTrack; // 0x40 (64 decimal)
		uint8_t eaxEnvironments; // 0x41 (65 decimal)
		SKIP(2);
	};
	static_assert(sizeof(mm8::MapStatsItem) == 0x44, "Invalid \"mm8::MapStatsItem\" structure size");
	static_assert(offsetof(mm8::MapStatsItem, fileName) == 4);
	static_assert(offsetof(mm8::MapStatsItem, monster1Pic) == 8);
	static_assert(offsetof(mm8::MapStatsItem, monster2Pic) == 12);
	static_assert(offsetof(mm8::MapStatsItem, monster3Pic) == 16);
	static_assert(offsetof(mm8::MapStatsItem, resetCount) == 20);
	static_assert(offsetof(mm8::MapStatsItem, firstVisitDay) == 24);
	static_assert(offsetof(mm8::MapStatsItem, refillDays) == 28);
	static_assert(offsetof(mm8::MapStatsItem, alertDays) == 32);
	static_assert(offsetof(mm8::MapStatsItem, stealPerm) == 36);
	static_assert(offsetof(mm8::MapStatsItem, per) == 40);
	static_assert(offsetof(mm8::MapStatsItem, lock) == 45);
	static_assert(offsetof(mm8::MapStatsItem, trap) == 46);
	static_assert(offsetof(mm8::MapStatsItem, tres) == 47);
	static_assert(offsetof(mm8::MapStatsItem, encounterChance) == 48);
	static_assert(offsetof(mm8::MapStatsItem, encounterChanceM1) == 49);
	static_assert(offsetof(mm8::MapStatsItem, encounterChanceM2) == 50);
	static_assert(offsetof(mm8::MapStatsItem, encounterChanceM3) == 51);
	static_assert(offsetof(mm8::MapStatsItem, mon1Dif) == 52);
	static_assert(offsetof(mm8::MapStatsItem, mon1Low) == 53);
	static_assert(offsetof(mm8::MapStatsItem, mon1Hi) == 54);
	static_assert(offsetof(mm8::MapStatsItem, mon2Dif) == 55);
	static_assert(offsetof(mm8::MapStatsItem, mon2Low) == 56);
	static_assert(offsetof(mm8::MapStatsItem, mon2Hi) == 57);
	static_assert(offsetof(mm8::MapStatsItem, mon3Dif) == 58);
	static_assert(offsetof(mm8::MapStatsItem, mon3Low) == 59);
	static_assert(offsetof(mm8::MapStatsItem, mon3Hi) == 60);
	static_assert(offsetof(mm8::MapStatsItem, redbookTrack) == 64);
	static_assert(offsetof(mm8::MapStatsItem, eaxEnvironments) == 65);



	struct ItemsTxtItem // size: 0x30
	{
		char* picture; // EditPChar | 0x0 (0 decimal)
		char* name; // EditPChar | 0x4 (4 decimal)
		char* notIdentifiedName; // EditPChar | 0x8 (8 decimal)
		char* notes; // EditPChar | 0xC (12 decimal)
		int32_t value; // 0x10 (16 decimal)
		int16_t spriteIndex; // 0x14 (20 decimal)
		SKIP(2);
		int16_t equipX; // 0x18 (24 decimal)
		int16_t equipY; // 0x1A (26 decimal)
		uint8_t equipStat; // 0x1C (28 decimal) | MMExt info: Subtract 1 from #const.ItemType:# value
		uint8_t skill; // 0x1D (29 decimal)
		uint8_t mod1DiceCount; // 0x1E (30 decimal)
		uint8_t mod1DiceSides; // 0x1F (31 decimal)
		uint8_t mod2; // 0x20 (32 decimal)
		uint8_t material; // 0x21 (33 decimal) | MMExt info: 0 = normal,  1 = artifact,  2 = relic,  3 = special
		uint8_t bonus2; // 0x22 (34 decimal) | MMExt info: VarA
		uint8_t bonus; // 0x23 (35 decimal) | MMExt info: VarA
		uint8_t bonusStrength; // 0x24 (36 decimal) | MMExt info: VarB
		SKIP(4);
		union
		{
			std::array<uint8_t, 6> chanceByLevel; // MMExt: 1..6, here 0..5 | 0x29 (41 decimal)
			struct
			{
				SKIP(5);
				int8_t idRepSt; // 0x2E (46 decimal)
			};
		};
		SKIP(1);
	};
	static_assert(sizeof(mm8::ItemsTxtItem) == 0x30, "Invalid \"mm8::ItemsTxtItem\" structure size");
	static_assert(offsetof(mm8::ItemsTxtItem, name) == 4);
	static_assert(offsetof(mm8::ItemsTxtItem, notIdentifiedName) == 8);
	static_assert(offsetof(mm8::ItemsTxtItem, notes) == 12);
	static_assert(offsetof(mm8::ItemsTxtItem, value) == 16);
	static_assert(offsetof(mm8::ItemsTxtItem, spriteIndex) == 20);
	static_assert(offsetof(mm8::ItemsTxtItem, equipX) == 24);
	static_assert(offsetof(mm8::ItemsTxtItem, equipY) == 26);
	static_assert(offsetof(mm8::ItemsTxtItem, equipStat) == 28);
	static_assert(offsetof(mm8::ItemsTxtItem, skill) == 29);
	static_assert(offsetof(mm8::ItemsTxtItem, mod1DiceCount) == 30);
	static_assert(offsetof(mm8::ItemsTxtItem, mod1DiceSides) == 31);
	static_assert(offsetof(mm8::ItemsTxtItem, mod2) == 32);
	static_assert(offsetof(mm8::ItemsTxtItem, material) == 33);
	static_assert(offsetof(mm8::ItemsTxtItem, bonus2) == 34);
	static_assert(offsetof(mm8::ItemsTxtItem, bonus) == 35);
	static_assert(offsetof(mm8::ItemsTxtItem, bonusStrength) == 36);
	static_assert(offsetof(mm8::ItemsTxtItem, chanceByLevel) == 41);
	static_assert(offsetof(mm8::ItemsTxtItem, idRepSt) == 46);



	struct Events2DItem // size: 0x34
	{
		int16_t type; // 0x0 (0 decimal)
		int16_t picture; // 0x2 (2 decimal)
		char* name; // EditPChar | 0x4 (4 decimal)
		char* ownerName; // EditPChar | 0x8 (8 decimal)
		char* enterText; // EditPChar | 0xC (12 decimal)
		char* ownerTitle; // EditPChar | 0x10 (16 decimal)
		int16_t pictureUnk; // 0x14 (20 decimal)
		int16_t state; // 0x16 (22 decimal)
		int16_t rep; // 0x18 (24 decimal)
		int16_t per; // 0x1A (26 decimal)
		int16_t c; // 0x1C (28 decimal)
		SKIP(2);
		float val; // 0x20 (32 decimal)
		float a; // 0x24 (36 decimal)
		int16_t openHour; // 0x28 (40 decimal)
		int16_t closeHour; // 0x2A (42 decimal)
		int16_t exitPic; // 0x2C (44 decimal)
		int16_t exitMap; // 0x2E (46 decimal)
		union
		{
			int16_t QBit; // 0x30 (48 decimal)
			int16_t questBitRestriction; // 0x30 (48 decimal) | MMExt info: (old name)
		};
		SKIP(2);
	};
	static_assert(sizeof(mm8::Events2DItem) == 0x34, "Invalid \"mm8::Events2DItem\" structure size");
	static_assert(offsetof(mm8::Events2DItem, picture) == 2);
	static_assert(offsetof(mm8::Events2DItem, name) == 4);
	static_assert(offsetof(mm8::Events2DItem, ownerName) == 8);
	static_assert(offsetof(mm8::Events2DItem, enterText) == 12);
	static_assert(offsetof(mm8::Events2DItem, ownerTitle) == 16);
	static_assert(offsetof(mm8::Events2DItem, pictureUnk) == 20);
	static_assert(offsetof(mm8::Events2DItem, state) == 22);
	static_assert(offsetof(mm8::Events2DItem, rep) == 24);
	static_assert(offsetof(mm8::Events2DItem, per) == 26);
	static_assert(offsetof(mm8::Events2DItem, c) == 28);
	static_assert(offsetof(mm8::Events2DItem, val) == 32);
	static_assert(offsetof(mm8::Events2DItem, a) == 36);
	static_assert(offsetof(mm8::Events2DItem, openHour) == 40);
	static_assert(offsetof(mm8::Events2DItem, closeHour) == 42);
	static_assert(offsetof(mm8::Events2DItem, exitPic) == 44);
	static_assert(offsetof(mm8::Events2DItem, exitMap) == 46);
	static_assert(offsetof(mm8::Events2DItem, QBit) == 48);
	static_assert(offsetof(mm8::Events2DItem, questBitRestriction) == 48);



	struct HistoryTxtItem // size: 0xC
	{
		char* text; // EditPChar | 0x0 (0 decimal)
		char* title; // EditPChar | 0x4 (4 decimal)
		int8_t time; // 0x8 (8 decimal)
		SKIP(3);
	};
	static_assert(sizeof(mm8::HistoryTxtItem) == 0xC, "Invalid \"mm8::HistoryTxtItem\" structure size");
	static_assert(offsetof(mm8::HistoryTxtItem, title) == 4);
	static_assert(offsetof(mm8::HistoryTxtItem, time) == 8);
}

#pragma pack(pop)