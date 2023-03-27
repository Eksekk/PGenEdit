#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct NPCProfTxtItem // size: 0x4C
	{
		int32_t chance;
		int32_t cost;
		int32_t personality;
		char* benefit; // EditPChar
		char* joinText; // EditPChar
		std::array<char*, 7> profNewsTopic; // EditPChar
		std::array<char*, 7> profNewsText; // EditPChar
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
		char* name; // EditPChar
		char* fileName; // EditPChar
		char* monster1Pic; // EditPChar
		char* monster2Pic; // EditPChar
		char* monster3Pic; // EditPChar
		int32_t resetCount;
		int32_t firstVisitDay;
		int32_t refillDays;
		SKIP(1);
		uint8_t lock;
		uint8_t trap;
		uint8_t tres;
		uint8_t encounterChance;
		uint8_t encounterChanceM1;
		uint8_t encounterChanceM2;
		uint8_t encounterChanceM3;
		uint8_t mon1Dif;
		uint8_t mon1Low;
		uint8_t mon1Hi;
		uint8_t mon2Dif;
		uint8_t mon2Low;
		uint8_t mon2Hi;
		uint8_t mon3Dif;
		uint8_t mon3Low;
		uint8_t mon3Hi;
		SKIP(3);
		uint8_t redbookTrack;
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



	struct SpcItemsTxtItem // size: 0x1C
	{
		char* nameAdd; // EditPChar
		char* bonusStat; // EditPChar
		union
		{
			std::array<uint8_t, 12> chanceForSlot;
			struct
			{
				uint8_t W1;
				uint8_t W2;
				uint8_t miss;
				uint8_t arm;
				uint8_t shld;
				uint8_t helm;
				uint8_t belt;
				uint8_t cape;
				uint8_t gaunt;
				uint8_t boot;
				uint8_t ring;
				uint8_t amul;
			};
		};
		int32_t value;
		uint8_t lvl;
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



	struct StdItemsTxtItem // size: 0x14
	{
		char* nameAdd; // EditPChar
		char* bonusStat; // EditPChar
		union
		{
			std::array<uint8_t, 9> chanceForSlot;
			struct
			{
				uint8_t arm;
				uint8_t shld;
				uint8_t helm;
				uint8_t belt;
				uint8_t cape;
				uint8_t gaunt;
				uint8_t boot;
				uint8_t ring;
				uint8_t amul;
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



	struct Events2DItem // size: 0x30
	{
		int16_t type;
		int16_t picture;
		char* name; // EditPChar
		char* ownerName; // EditPChar
		char* enterText; // EditPChar
		char* ownerTitle; // EditPChar
		int16_t pictureUnk;
		int16_t state;
		int16_t rep;
		int16_t per;
		int16_t c;
		SKIP(2);
		float val;
		int16_t openHour;
		int16_t closeHour;
		int16_t exitPic;
		int16_t exitMap;
		union
		{
			int16_t questBitRestriction;
			int16_t QBit;
		};
		SKIP(2);
	};
	static_assert(sizeof(mm6::Events2DItem) == 0x30, "Invalid \"mm6::Events2DItem\" structure size");
	static_assert(offsetof(mm6::Events2DItem, picture) == 2);
	static_assert(offsetof(mm6::Events2DItem, name) == 4);
	static_assert(offsetof(mm6::Events2DItem, ownerName) == 8);
	static_assert(offsetof(mm6::Events2DItem, enterText) == 12);
	static_assert(offsetof(mm6::Events2DItem, ownerTitle) == 16);
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
	static_assert(offsetof(mm6::Events2DItem, questBitRestriction) == 44);
	static_assert(offsetof(mm6::Events2DItem, QBit) == 44);



	struct ItemsTxtItem // size: 0x28
	{
		char* picture; // EditPChar
		char* name; // EditPChar
		char* notIdentifiedName; // EditPChar
		char* notes; // EditPChar
		int32_t value;
		uint8_t equipStat;
		std::array<uint8_t, 1> skill; // Unknown type
		uint8_t mod1DiceCount;
		uint8_t mod1DiceSides;
		uint8_t mod2;
		uint8_t material;
		std::array<uint8_t, 6> chanceByLevel; // MMExt: 1..6, here 0..5
		int8_t idRepSt;
		int8_t spriteIndex;
		int16_t equipX;
		int16_t equipY;
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



	struct SpellsTxtItem // size: 0x1C
	{
		char* name; // EditPChar
		char* shortName; // EditPChar
		char* description; // EditPChar
		char* normal; // EditPChar
		char* expert; // EditPChar
		char* master; // EditPChar
		uint8_t damageType;
		union
		{
			std::array<uint8_t, 3> spellPoints; // MMExt: 1..3, here 0..2
			struct
			{
				uint8_t spellPointsNormal;
				uint8_t spellPointsExpert;
				uint8_t spellPointsMaster;
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
}
namespace mm7
{
	struct SpcItemsTxtItem // size: 0x1C
	{
		char* nameAdd; // EditPChar
		char* bonusStat; // EditPChar
		union
		{
			std::array<uint8_t, 12> chanceForSlot;
			struct
			{
				uint8_t W1;
				uint8_t W2;
				uint8_t miss;
				uint8_t arm;
				uint8_t shld;
				uint8_t helm;
				uint8_t belt;
				uint8_t cape;
				uint8_t gaunt;
				uint8_t boot;
				uint8_t ring;
				uint8_t amul;
			};
		};
		int32_t value;
		uint8_t lvl;
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



	struct StdItemsTxtItem // size: 0x14
	{
		char* nameAdd; // EditPChar
		char* bonusStat; // EditPChar
		union
		{
			std::array<uint8_t, 9> chanceForSlot;
			struct
			{
				uint8_t arm;
				uint8_t shld;
				uint8_t helm;
				uint8_t belt;
				uint8_t cape;
				uint8_t gaunt;
				uint8_t boot;
				uint8_t ring;
				uint8_t amul;
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



	struct Events2DItem // size: 0x34
	{
		int16_t type;
		int16_t picture;
		char* name; // EditPChar
		char* ownerName; // EditPChar
		char* enterText; // EditPChar
		char* ownerTitle; // EditPChar
		int16_t pictureUnk;
		int16_t state;
		int16_t rep;
		int16_t per;
		int16_t c;
		SKIP(2);
		float val;
		float a;
		int16_t openHour;
		int16_t closeHour;
		int16_t exitPic;
		int16_t exitMap;
		union
		{
			int16_t questBitRestriction;
			int16_t QBit;
		};
		SKIP(2);
	};
	static_assert(sizeof(mm7::Events2DItem) == 0x34, "Invalid \"mm7::Events2DItem\" structure size");
	static_assert(offsetof(mm7::Events2DItem, picture) == 2);
	static_assert(offsetof(mm7::Events2DItem, name) == 4);
	static_assert(offsetof(mm7::Events2DItem, ownerName) == 8);
	static_assert(offsetof(mm7::Events2DItem, enterText) == 12);
	static_assert(offsetof(mm7::Events2DItem, ownerTitle) == 16);
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
	static_assert(offsetof(mm7::Events2DItem, questBitRestriction) == 48);
	static_assert(offsetof(mm7::Events2DItem, QBit) == 48);



	struct MapStatsItem // size: 0x44
	{
		char* name; // EditPChar
		char* fileName; // EditPChar
		char* monster1Pic; // EditPChar
		char* monster2Pic; // EditPChar
		char* monster3Pic; // EditPChar
		int32_t resetCount;
		int32_t firstVisitDay;
		int32_t refillDays;
		int32_t alertDays;
		int32_t stealPerm;
		int32_t per;
		SKIP(1);
		uint8_t lock;
		uint8_t trap;
		uint8_t tres;
		uint8_t encounterChance;
		uint8_t encounterChanceM1;
		uint8_t encounterChanceM2;
		uint8_t encounterChanceM3;
		uint8_t mon1Dif;
		uint8_t mon1Low;
		uint8_t mon1Hi;
		uint8_t mon2Dif;
		uint8_t mon2Low;
		uint8_t mon2Hi;
		uint8_t mon3Dif;
		uint8_t mon3Low;
		uint8_t mon3Hi;
		SKIP(3);
		uint8_t redbookTrack;
		uint8_t eaxEnvironments;
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
		char* picture; // EditPChar
		char* name; // EditPChar
		char* notIdentifiedName; // EditPChar
		char* notes; // EditPChar
		int32_t value;
		int16_t spriteIndex;
		SKIP(2);
		int16_t equipX;
		int16_t equipY;
		uint8_t equipStat;
		uint8_t skill;
		uint8_t mod1DiceCount;
		uint8_t mod1DiceSides;
		uint8_t mod2;
		uint8_t material;
		uint8_t bonus2;
		uint8_t bonus;
		uint8_t bonusStrength;
		SKIP(3);
		std::array<uint8_t, 6> chanceByLevel; // MMExt: 1..6, here 0..5
		int8_t idRepSt;
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



	struct SpellsTxtItem // size: 0x24
	{
		char* name; // EditPChar
		char* shortName; // EditPChar
		char* description; // EditPChar
		char* normal; // EditPChar
		char* expert; // EditPChar
		char* master; // EditPChar
		union
		{
			char* GM; // EditPChar
			char* grandMaster; // EditPChar
		};
		uint8_t damageType;
		union
		{
			std::array<uint8_t, 4> spellPoints; // MMExt: 1..4, here 0..3
			struct
			{
				uint8_t spellPointsNormal;
				uint8_t spellPointsExpert;
				uint8_t spellPointsMaster;
				uint8_t spellPointsGM;
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



	struct NPCProfTxtItem // size: 0x14
	{
		int32_t cost;
		char* benefit; // EditPChar
		char* actionText; // EditPChar
		char* joinText; // EditPChar
		char* dismissText; // EditPChar
	};
	static_assert(sizeof(mm7::NPCProfTxtItem) == 0x14, "Invalid \"mm7::NPCProfTxtItem\" structure size");
	static_assert(offsetof(mm7::NPCProfTxtItem, benefit) == 4);
	static_assert(offsetof(mm7::NPCProfTxtItem, actionText) == 8);
	static_assert(offsetof(mm7::NPCProfTxtItem, joinText) == 12);
	static_assert(offsetof(mm7::NPCProfTxtItem, dismissText) == 16);



	struct HistoryTxtItem // size: 0xC
	{
		char* text; // EditPChar
		char* title; // EditPChar
		int8_t time;
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
		char* nameAdd; // EditPChar
		char* bonusStat; // EditPChar
		union
		{
			std::array<uint8_t, 9> chanceForSlot;
			struct
			{
				uint8_t arm;
				uint8_t shld;
				uint8_t helm;
				uint8_t belt;
				uint8_t cape;
				uint8_t gaunt;
				uint8_t boot;
				uint8_t ring;
				uint8_t amul;
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



	struct SpcItemsTxtItem // size: 0x1C
	{
		char* nameAdd; // EditPChar
		char* bonusStat; // EditPChar
		union
		{
			std::array<uint8_t, 12> chanceForSlot;
			struct
			{
				uint8_t W1;
				uint8_t W2;
				uint8_t miss;
				uint8_t arm;
				uint8_t shld;
				uint8_t helm;
				uint8_t belt;
				uint8_t cape;
				uint8_t gaunt;
				uint8_t boot;
				uint8_t ring;
				uint8_t amul;
			};
		};
		int32_t value;
		uint8_t lvl;
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



	struct ItemsTxtItem // size: 0x30
	{
		char* picture; // EditPChar
		char* name; // EditPChar
		char* notIdentifiedName; // EditPChar
		char* notes; // EditPChar
		int32_t value;
		int16_t spriteIndex;
		SKIP(2);
		int16_t equipX;
		int16_t equipY;
		uint8_t equipStat;
		uint8_t skill;
		uint8_t mod1DiceCount;
		uint8_t mod1DiceSides;
		uint8_t mod2;
		uint8_t material;
		uint8_t bonus2;
		uint8_t bonus;
		uint8_t bonusStrength;
		SKIP(4);
		union
		{
			std::array<uint8_t, 6> chanceByLevel; // MMExt: 1..6, here 0..5
			struct
			{
				SKIP(5);
				int8_t idRepSt;
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



	struct SpellsTxtItem // size: 0x24
	{
		char* name; // EditPChar
		char* shortName; // EditPChar
		char* description; // EditPChar
		char* normal; // EditPChar
		char* expert; // EditPChar
		char* master; // EditPChar
		union
		{
			char* grandMaster; // EditPChar
			char* GM; // EditPChar
		};
		uint8_t damageType;
		union
		{
			std::array<uint8_t, 4> spellPoints; // MMExt: 1..4, here 0..3
			struct
			{
				uint8_t spellPointsNormal;
				uint8_t spellPointsExpert;
				uint8_t spellPointsMaster;
				uint8_t spellPointsGM;
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
	static_assert(offsetof(mm8::SpellsTxtItem, grandMaster) == 24);
	static_assert(offsetof(mm8::SpellsTxtItem, GM) == 24);
	static_assert(offsetof(mm8::SpellsTxtItem, damageType) == 28);
	static_assert(offsetof(mm8::SpellsTxtItem, spellPoints) == 29);
	static_assert(offsetof(mm8::SpellsTxtItem, spellPointsNormal) == 29);
	static_assert(offsetof(mm8::SpellsTxtItem, spellPointsExpert) == 30);
	static_assert(offsetof(mm8::SpellsTxtItem, spellPointsMaster) == 31);
	static_assert(offsetof(mm8::SpellsTxtItem, spellPointsGM) == 32);



	struct Events2DItem // size: 0x34
	{
		int16_t type;
		int16_t picture;
		char* name; // EditPChar
		char* ownerName; // EditPChar
		char* enterText; // EditPChar
		char* ownerTitle; // EditPChar
		int16_t pictureUnk;
		int16_t state;
		int16_t rep;
		int16_t per;
		int16_t c;
		SKIP(2);
		float val;
		float a;
		int16_t openHour;
		int16_t closeHour;
		int16_t exitPic;
		int16_t exitMap;
		union
		{
			int16_t questBitRestriction;
			int16_t QBit;
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
	static_assert(offsetof(mm8::Events2DItem, questBitRestriction) == 48);
	static_assert(offsetof(mm8::Events2DItem, QBit) == 48);



	struct HistoryTxtItem // size: 0xC
	{
		char* text; // EditPChar
		char* title; // EditPChar
		int8_t time;
		SKIP(3);
	};
	static_assert(sizeof(mm8::HistoryTxtItem) == 0xC, "Invalid \"mm8::HistoryTxtItem\" structure size");
	static_assert(offsetof(mm8::HistoryTxtItem, title) == 4);
	static_assert(offsetof(mm8::HistoryTxtItem, time) == 8);



	struct MapStatsItem // size: 0x44
	{
		char* name; // EditPChar
		char* fileName; // EditPChar
		char* monster1Pic; // EditPChar
		char* monster2Pic; // EditPChar
		char* monster3Pic; // EditPChar
		int32_t resetCount;
		int32_t firstVisitDay;
		int32_t refillDays;
		int32_t alertDays;
		int32_t stealPerm;
		int32_t per;
		SKIP(1);
		uint8_t lock;
		uint8_t trap;
		uint8_t tres;
		uint8_t encounterChance;
		uint8_t encounterChanceM1;
		uint8_t encounterChanceM2;
		uint8_t encounterChanceM3;
		uint8_t mon1Dif;
		uint8_t mon1Low;
		uint8_t mon1Hi;
		uint8_t mon2Dif;
		uint8_t mon2Low;
		uint8_t mon2Hi;
		uint8_t mon3Dif;
		uint8_t mon3Low;
		uint8_t mon3Hi;
		SKIP(3);
		uint8_t redbookTrack;
		uint8_t eaxEnvironments;
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
}

#pragma pack(pop)