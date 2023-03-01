#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct Button // size: 0xB8
	{
		int32_t left;
		int32_t top;
		int32_t width;
		int32_t height;
		int32_t right;
		int32_t bottom;
		int32_t shape;
		int32_t hintAction;
		int32_t actionType;
		int32_t actionParam;
		uint32_t pressed; // 4-byte boolean
		uint32_t prevItemPtr;
		uint32_t nextItemPtr;
		union
		{
			uint32_t parentPtr;
			mm6::Dlg* parent;
		};
		std::array<int32_t, 5> sprites; // size field offset is 0x4C
		uint32_t sprites_size;
		uint8_t shortCut;
		std::array<char, 103> hint; // fixed size string, requires null terminator
	};
	static_assert(sizeof(mm6::Button) == 0xB8, "Invalid \"mm6::Button\" structure size");
	static_assert(offsetof(mm6::Button, top) == 4);
	static_assert(offsetof(mm6::Button, width) == 8);
	static_assert(offsetof(mm6::Button, height) == 12);
	static_assert(offsetof(mm6::Button, right) == 16);
	static_assert(offsetof(mm6::Button, bottom) == 20);
	static_assert(offsetof(mm6::Button, shape) == 24);
	static_assert(offsetof(mm6::Button, hintAction) == 28);
	static_assert(offsetof(mm6::Button, actionType) == 32);
	static_assert(offsetof(mm6::Button, actionParam) == 36);
	static_assert(offsetof(mm6::Button, pressed) == 40);
	static_assert(offsetof(mm6::Button, prevItemPtr) == 44);
	static_assert(offsetof(mm6::Button, nextItemPtr) == 48);
	static_assert(offsetof(mm6::Button, parentPtr) == 52);
	static_assert(offsetof(mm6::Button, parent) == 52);
	static_assert(offsetof(mm6::Button, sprites) == 56);
	static_assert(offsetof(mm6::Button, sprites_size) == 76);
	static_assert(offsetof(mm6::Button, shortCut) == 80);
	static_assert(offsetof(mm6::Button, hint) == 81);



	struct NPCNewsItem // size: 0xC
	{
		char* topic; // EditPChar
		char* text; // EditPChar
		int8_t map;
		SKIP(3);
	};
	static_assert(sizeof(mm6::NPCNewsItem) == 0xC, "Invalid \"mm6::NPCNewsItem\" structure size");
	static_assert(offsetof(mm6::NPCNewsItem, text) == 4);
	static_assert(offsetof(mm6::NPCNewsItem, map) == 8);



	struct NPC // size: 0x3C
	{
		union
		{
			char* name; // EditPChar
			uint32_t exist; // 4-byte boolean
		};
		int32_t pic;
		union
		{
			uint32_t bits;
			struct
			{
				bool bribedBefore : 1;
				bool beggedBefore : 1;
				bool threatenedBefore : 1;
				SKIPBITS(4);
				bool hired : 1;
			};
		};
		int32_t fame;
		int32_t rep;
		int32_t house;
		int32_t profession;
		int32_t joins;
		int32_t tellsNews;
		union
		{
			std::array<int32_t, 3> events;
			struct
			{
				int32_t eventA;
				int32_t eventB;
				int32_t eventC;
			};
		};
		int32_t sex;
		int32_t usedSpell;
		int32_t newsTopic;
	};
	static_assert(sizeof(mm6::NPC) == 0x3C, "Invalid \"mm6::NPC\" structure size");
	static_assert(offsetof(mm6::NPC, pic) == 4);
	static_assert(offsetof(mm6::NPC, bits) == 8);
	static_assert(offsetof(mm6::NPC, fame) == 12);
	static_assert(offsetof(mm6::NPC, rep) == 16);
	static_assert(offsetof(mm6::NPC, house) == 20);
	static_assert(offsetof(mm6::NPC, profession) == 24);
	static_assert(offsetof(mm6::NPC, joins) == 28);
	static_assert(offsetof(mm6::NPC, tellsNews) == 32);
	static_assert(offsetof(mm6::NPC, events) == 36);
	static_assert(offsetof(mm6::NPC, eventA) == 36);
	static_assert(offsetof(mm6::NPC, eventB) == 40);
	static_assert(offsetof(mm6::NPC, eventC) == 44);
	static_assert(offsetof(mm6::NPC, sex) == 48);
	static_assert(offsetof(mm6::NPC, usedSpell) == 52);
	static_assert(offsetof(mm6::NPC, newsTopic) == 56);



	struct GameParty // size: 0x944C78
	{
		SKIP(5066984);
		std::array<uint8_t, 4> currentPlayer; // Unknown type
		SKIP(4406188);
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
		int32_t direction;
		int32_t lookAngle;
		int32_t lastX;
		int32_t lastY;
		int32_t lastZ;
		int32_t lastDirection;
		int32_t lastLookAngle;
		int32_t lastEyeLevel;
		int32_t speedX;
		int32_t speedY;
		int32_t speedZ;
		SKIP(4);
		int32_t stableZ;
		int32_t lastStandFacet;
		SKIP(8);
		int32_t fallStartZ;
		uint32_t flying; // 4-byte boolean
		SKIP(64);
		int32_t food;
		SKIP(24);
		int32_t reputation;
		SKIP(4);
		int32_t gold;
		int32_t bankGold;
		int32_t deaths;
		SKIP(4);
		union
		{
			int32_t pritsonTerms;
			int32_t prisonTerms;
		};
		int32_t bountiesCollected;
		SKIP(5);
		std::array<uint8_t, 64> QBits; // array of abits (real index = 7 - usual)
		std::array<uint8_t, 16> autonotesBits; // MMExt: 1..128, here 0..127 | array of abits (real index = 7 - usual)
		int8_t inArenaQuest;
		int8_t arenaWinsPage;
		int8_t arenaWinsSquire;
		int8_t arenaWinsKnight;
		int8_t arenaWinsLord;
		SKIP(3);
		union
		{
			std::array<uint8_t, 3> monsHuntTarget;
			std::array<uint8_t, 3> bountyHuntTarget;
		};
		union
		{
			std::array<bool, 3> bountyHuntKilled;
			std::array<bool, 3> monsHuntKilled;
		};
		std::array<bool, 30> artifactsFound; // MMExt: 400..429, here 0..29
		SKIP(75);
		std::array<mm6::SpellBuff, 16> spellBuffs;
		std::array<mm6::Player, 4> playersArray;
		std::array<mm6::NPC, 2> hiredNPC; // MMExt: 1..2, here 0..1
		SKIP(28);
		union
		{
			int32_t stateBits;
			struct
			{
				SKIPBITS(1);
				bool needRender : 1;
				bool drowning : 1;
				bool inAir : 1;
				bool enemyDetectorRed : 1;
				bool enemyDetectorYellow : 1;
				bool flyingBit : 1;
				bool waterWalkingBit : 1;
				bool inJumpSpell : 1;
				bool inLava : 1;
			};
		};
		int64_t lastRegenerationTime;
		union
		{
			std::array<int64_t, 3> monsHuntReset;
			std::array<int64_t, 3> nextBountyHunt;
		};
		SKIP(40978);
		std::array<std::array<char, 100>, 2> hiredNPCName; // MMExt: 1..2, here 0..1 | fixed size string, requires null terminator
		SKIP(181042);
		std::array<std::array<uint8_t, 4>, 4> players; // Unknown type
	};
	static_assert(sizeof(mm6::GameParty) == 0x944C78, "Invalid \"mm6::GameParty\" structure size");
	static_assert(offsetof(mm6::GameParty, currentPlayer) == 5066984);
	static_assert(offsetof(mm6::GameParty, pos) == 9473176);
	static_assert(offsetof(mm6::GameParty, x) == 9473176);
	static_assert(offsetof(mm6::GameParty, y) == 9473180);
	static_assert(offsetof(mm6::GameParty, z) == 9473184);
	static_assert(offsetof(mm6::GameParty, direction) == 9473188);
	static_assert(offsetof(mm6::GameParty, lookAngle) == 9473192);
	static_assert(offsetof(mm6::GameParty, lastX) == 9473196);
	static_assert(offsetof(mm6::GameParty, lastY) == 9473200);
	static_assert(offsetof(mm6::GameParty, lastZ) == 9473204);
	static_assert(offsetof(mm6::GameParty, lastDirection) == 9473208);
	static_assert(offsetof(mm6::GameParty, lastLookAngle) == 9473212);
	static_assert(offsetof(mm6::GameParty, lastEyeLevel) == 9473216);
	static_assert(offsetof(mm6::GameParty, speedX) == 9473220);
	static_assert(offsetof(mm6::GameParty, speedY) == 9473224);
	static_assert(offsetof(mm6::GameParty, speedZ) == 9473228);
	static_assert(offsetof(mm6::GameParty, stableZ) == 9473236);
	static_assert(offsetof(mm6::GameParty, lastStandFacet) == 9473240);
	static_assert(offsetof(mm6::GameParty, fallStartZ) == 9473252);
	static_assert(offsetof(mm6::GameParty, flying) == 9473256);
	static_assert(offsetof(mm6::GameParty, food) == 9473324);
	static_assert(offsetof(mm6::GameParty, reputation) == 9473352);
	static_assert(offsetof(mm6::GameParty, gold) == 9473360);
	static_assert(offsetof(mm6::GameParty, bankGold) == 9473364);
	static_assert(offsetof(mm6::GameParty, deaths) == 9473368);
	static_assert(offsetof(mm6::GameParty, pritsonTerms) == 9473376);
	static_assert(offsetof(mm6::GameParty, prisonTerms) == 9473376);
	static_assert(offsetof(mm6::GameParty, bountiesCollected) == 9473380);
	static_assert(offsetof(mm6::GameParty, inArenaQuest) == 9473469);
	static_assert(offsetof(mm6::GameParty, arenaWinsPage) == 9473470);
	static_assert(offsetof(mm6::GameParty, arenaWinsSquire) == 9473471);
	static_assert(offsetof(mm6::GameParty, arenaWinsKnight) == 9473472);
	static_assert(offsetof(mm6::GameParty, arenaWinsLord) == 9473473);
	static_assert(offsetof(mm6::GameParty, monsHuntTarget) == 9473477);
	static_assert(offsetof(mm6::GameParty, bountyHuntTarget) == 9473477);
	static_assert(offsetof(mm6::GameParty, bountyHuntKilled) == 9473480);
	static_assert(offsetof(mm6::GameParty, monsHuntKilled) == 9473480);
	static_assert(offsetof(mm6::GameParty, artifactsFound) == 9473483);
	static_assert(offsetof(mm6::GameParty, spellBuffs) == 9473588);
	static_assert(offsetof(mm6::GameParty, playersArray) == 9473844);
	static_assert(offsetof(mm6::GameParty, hiredNPC) == 9496484);
	static_assert(offsetof(mm6::GameParty, stateBits) == 9496632);
	static_assert(offsetof(mm6::GameParty, lastRegenerationTime) == 9496636);
	static_assert(offsetof(mm6::GameParty, monsHuntReset) == 9496644);
	static_assert(offsetof(mm6::GameParty, nextBountyHunt) == 9496644);
	static_assert(offsetof(mm6::GameParty, hiredNPCName) == 9537646);
	static_assert(offsetof(mm6::GameParty, players) == 9718888);
}
namespace mm7
{
	struct NPC // size: 0x4C
	{
		union
		{
			char* name; // EditPChar
			uint32_t exist; // 4-byte boolean
		};
		int32_t pic;
		union
		{
			uint32_t bits;
			struct
			{
				bool bribedBefore : 1;
				bool talkedBefore : 1;
				bool threatenedBefore : 1;
				SKIPBITS(4);
				bool hired : 1;
			};
		};
		int32_t fame;
		int32_t rep;
		int32_t house;
		int32_t profession;
		int32_t greet;
		int32_t joins;
		int32_t tellsNews;
		union
		{
			std::array<int32_t, 6> events;
			struct
			{
				int32_t eventA;
				int32_t eventB;
				int32_t eventC;
				int32_t eventD;
				int32_t eventE;
				int32_t eventF;
			};
		};
		int32_t sex;
		int32_t usedSpell;
		int32_t newsTopic;
	};
	static_assert(sizeof(mm7::NPC) == 0x4C, "Invalid \"mm7::NPC\" structure size");
	static_assert(offsetof(mm7::NPC, pic) == 4);
	static_assert(offsetof(mm7::NPC, bits) == 8);
	static_assert(offsetof(mm7::NPC, fame) == 12);
	static_assert(offsetof(mm7::NPC, rep) == 16);
	static_assert(offsetof(mm7::NPC, house) == 20);
	static_assert(offsetof(mm7::NPC, profession) == 24);
	static_assert(offsetof(mm7::NPC, greet) == 28);
	static_assert(offsetof(mm7::NPC, joins) == 32);
	static_assert(offsetof(mm7::NPC, tellsNews) == 36);
	static_assert(offsetof(mm7::NPC, events) == 40);
	static_assert(offsetof(mm7::NPC, eventA) == 40);
	static_assert(offsetof(mm7::NPC, eventB) == 44);
	static_assert(offsetof(mm7::NPC, eventC) == 48);
	static_assert(offsetof(mm7::NPC, eventD) == 52);
	static_assert(offsetof(mm7::NPC, eventE) == 56);
	static_assert(offsetof(mm7::NPC, eventF) == 60);
	static_assert(offsetof(mm7::NPC, sex) == 64);
	static_assert(offsetof(mm7::NPC, usedSpell) == 68);
	static_assert(offsetof(mm7::NPC, newsTopic) == 72);



	struct GameParty // size: 0xAE3064
	{
		SKIP(5274220);
		std::array<uint8_t, 4> currentPlayer; // Unknown type
		SKIP(5690584);
		std::array<std::array<uint8_t, 4>, 4> players; // Unknown type
		SKIP(360212);
		int64_t lastRegenerationTime;
		union
		{
			std::array<int64_t, 5> nextBountyHunt;
			std::array<int64_t, 5> monsHuntReset;
		};
		SKIP(1224);
		std::array<int64_t, 29> history; // MMExt: 1..29, here 0..28
		std::array<int64_t, 20> specialDates; // MMExt: 1..20, here 0..19
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
		int32_t direction;
		int32_t lookAngle;
		int32_t lastX;
		int32_t lastY;
		int32_t lastZ;
		int32_t lastDirection;
		int32_t lastLookAngle;
		int32_t lastEyeLevel;
		int32_t speedX;
		int32_t speedY;
		int32_t speedZ;
		SKIP(4);
		int32_t stableZ;
		int32_t lastStandFacet;
		SKIP(8);
		int32_t fallStartZ;
		uint32_t flying; // 4-byte boolean
		SKIP(32);
		int32_t food;
		SKIP(8);
		int32_t gold;
		int32_t bankGold;
		int32_t deaths;
		SKIP(4);
		union
		{
			int32_t prisonTerms;
			int32_t pritsonTerms;
		};
		int32_t bountiesCollected;
		SKIP(4);
		union
		{
			std::array<int16_t, 5> bountyHuntTarget;
			std::array<int16_t, 5> monsHuntTarget;
		};
		union
		{
			std::array<int16_t, 5> monsHuntKilled;
			std::array<uint16_t, 5> bountyHuntKilled; // 2-byte boolean
		};
		SKIP(1);
		std::array<uint8_t, 64> QBits; // MMExt: 1..512, here 0..511 | array of abits (real index = 7 - usual)
		std::array<bool, 16> arcomageWins; // MMExt: 108..123, here 0..15
		int8_t inArenaQuest;
		int8_t arenaWinsPage;
		int8_t arenaWinsSquire;
		int8_t arenaWinsKnight;
		int8_t arenaWinsLord;
		std::array<bool, 68> artifactsFound; // MMExt: 500..567, here 0..67
		std::array<uint8_t, 31> autonotesBits; // MMExt: 1..255, here 0..254 | array of abits (real index = 7 - usual)
		SKIP(107);
		int32_t alignment;
		union
		{
			std::array<mm7::SpellBuff, 20> spellBuffs;
			struct
			{
				// uint8_t* reputation; // real size is 0 | Unknown type
			};
		};
		std::array<mm7::Player, 4> playersArray;
		std::array<mm7::NPC, 2> hiredNPC; // MMExt: 1..2, here 0..1
		SKIP(36);
		union
		{
			int32_t stateBits;
			struct
			{
				SKIPBITS(1);
				bool needRender : 1;
				bool drowning : 1;
				bool inAir : 1;
				bool enemyDetectorRed : 1;
				bool enemyDetectorYellow : 1;
				bool flyingBit : 1;
				bool waterWalkingBit : 1;
				bool inJumpSpell : 1;
				bool inLava : 1;
			};
		};
		SKIP(59640);
		std::array<std::array<char, 100>, 2> hiredNPCName; // MMExt: 1..2, here 0..1 | fixed size string, requires null terminator
		SKIP(236);
		int32_t fine;
	};
	static_assert(sizeof(mm7::GameParty) == 0xAE3064, "Invalid \"mm7::GameParty\" structure size");
	static_assert(offsetof(mm7::GameParty, currentPlayer) == 5274220);
	static_assert(offsetof(mm7::GameParty, players) == 10964808);
	static_assert(offsetof(mm7::GameParty, lastRegenerationTime) == 11325036);
	static_assert(offsetof(mm7::GameParty, nextBountyHunt) == 11325044);
	static_assert(offsetof(mm7::GameParty, monsHuntReset) == 11325044);
	static_assert(offsetof(mm7::GameParty, history) == 11326308);
	static_assert(offsetof(mm7::GameParty, specialDates) == 11326540);
	static_assert(offsetof(mm7::GameParty, pos) == 11326700);
	static_assert(offsetof(mm7::GameParty, x) == 11326700);
	static_assert(offsetof(mm7::GameParty, y) == 11326704);
	static_assert(offsetof(mm7::GameParty, z) == 11326708);
	static_assert(offsetof(mm7::GameParty, direction) == 11326712);
	static_assert(offsetof(mm7::GameParty, lookAngle) == 11326716);
	static_assert(offsetof(mm7::GameParty, lastX) == 11326720);
	static_assert(offsetof(mm7::GameParty, lastY) == 11326724);
	static_assert(offsetof(mm7::GameParty, lastZ) == 11326728);
	static_assert(offsetof(mm7::GameParty, lastDirection) == 11326732);
	static_assert(offsetof(mm7::GameParty, lastLookAngle) == 11326736);
	static_assert(offsetof(mm7::GameParty, lastEyeLevel) == 11326740);
	static_assert(offsetof(mm7::GameParty, speedX) == 11326744);
	static_assert(offsetof(mm7::GameParty, speedY) == 11326748);
	static_assert(offsetof(mm7::GameParty, speedZ) == 11326752);
	static_assert(offsetof(mm7::GameParty, stableZ) == 11326760);
	static_assert(offsetof(mm7::GameParty, lastStandFacet) == 11326764);
	static_assert(offsetof(mm7::GameParty, fallStartZ) == 11326776);
	static_assert(offsetof(mm7::GameParty, flying) == 11326780);
	static_assert(offsetof(mm7::GameParty, food) == 11326816);
	static_assert(offsetof(mm7::GameParty, gold) == 11326828);
	static_assert(offsetof(mm7::GameParty, bankGold) == 11326832);
	static_assert(offsetof(mm7::GameParty, deaths) == 11326836);
	static_assert(offsetof(mm7::GameParty, prisonTerms) == 11326844);
	static_assert(offsetof(mm7::GameParty, pritsonTerms) == 11326844);
	static_assert(offsetof(mm7::GameParty, bountiesCollected) == 11326848);
	static_assert(offsetof(mm7::GameParty, bountyHuntTarget) == 11326856);
	static_assert(offsetof(mm7::GameParty, monsHuntTarget) == 11326856);
	static_assert(offsetof(mm7::GameParty, monsHuntKilled) == 11326866);
	static_assert(offsetof(mm7::GameParty, bountyHuntKilled) == 11326866);
	static_assert(offsetof(mm7::GameParty, arcomageWins) == 11326941);
	static_assert(offsetof(mm7::GameParty, inArenaQuest) == 11326957);
	static_assert(offsetof(mm7::GameParty, arenaWinsPage) == 11326958);
	static_assert(offsetof(mm7::GameParty, arenaWinsSquire) == 11326959);
	static_assert(offsetof(mm7::GameParty, arenaWinsKnight) == 11326960);
	static_assert(offsetof(mm7::GameParty, arenaWinsLord) == 11326961);
	static_assert(offsetof(mm7::GameParty, artifactsFound) == 11326962);
	static_assert(offsetof(mm7::GameParty, alignment) == 11327168);
	static_assert(offsetof(mm7::GameParty, spellBuffs) == 11327172);
	static_assert(offsetof(mm7::GameParty, playersArray) == 11327492);
	static_assert(offsetof(mm7::GameParty, hiredNPC) == 11355380);
	static_assert(offsetof(mm7::GameParty, stateBits) == 11355568);
	static_assert(offsetof(mm7::GameParty, hiredNPCName) == 11415212);
	static_assert(offsetof(mm7::GameParty, fine) == 11415648);



	struct Button // size: 0xBC
	{
		int32_t left;
		int32_t top;
		int32_t width;
		int32_t height;
		int32_t right;
		int32_t bottom;
		int32_t shape;
		int32_t hintAction;
		int32_t actionType;
		int32_t actionParam;
		int32_t actionParam2;
		uint32_t pressed; // 4-byte boolean
		uint32_t prevItemPtr;
		uint32_t nextItemPtr;
		union
		{
			mm7::Dlg* parent;
			uint32_t parentPtr;
		};
		std::array<int32_t, 5> sprites; // size field offset is 0x50
		uint32_t sprites_size;
		uint8_t shortCut;
		std::array<char, 103> hint; // fixed size string, requires null terminator
	};
	static_assert(sizeof(mm7::Button) == 0xBC, "Invalid \"mm7::Button\" structure size");
	static_assert(offsetof(mm7::Button, top) == 4);
	static_assert(offsetof(mm7::Button, width) == 8);
	static_assert(offsetof(mm7::Button, height) == 12);
	static_assert(offsetof(mm7::Button, right) == 16);
	static_assert(offsetof(mm7::Button, bottom) == 20);
	static_assert(offsetof(mm7::Button, shape) == 24);
	static_assert(offsetof(mm7::Button, hintAction) == 28);
	static_assert(offsetof(mm7::Button, actionType) == 32);
	static_assert(offsetof(mm7::Button, actionParam) == 36);
	static_assert(offsetof(mm7::Button, actionParam2) == 40);
	static_assert(offsetof(mm7::Button, pressed) == 44);
	static_assert(offsetof(mm7::Button, prevItemPtr) == 48);
	static_assert(offsetof(mm7::Button, nextItemPtr) == 52);
	static_assert(offsetof(mm7::Button, parent) == 56);
	static_assert(offsetof(mm7::Button, parentPtr) == 56);
	static_assert(offsetof(mm7::Button, sprites) == 60);
	static_assert(offsetof(mm7::Button, sprites_size) == 80);
	static_assert(offsetof(mm7::Button, shortCut) == 84);
	static_assert(offsetof(mm7::Button, hint) == 85);
}
namespace mm8
{
	struct NPC // size: 0x4C
	{
		union
		{
			char* name; // EditPChar
			uint32_t exist; // 4-byte boolean
		};
		int32_t pic;
		union
		{
			uint32_t bits;
			struct
			{
				bool bribedBefore : 1;
				bool talkedBefore : 1;
				bool threatenedBefore : 1;
				SKIPBITS(4);
				bool hired : 1;
			};
		};
		int32_t fame;
		int32_t rep;
		int32_t house;
		int32_t profession;
		int32_t greet;
		int32_t joins;
		int32_t tellsNews;
		union
		{
			std::array<int32_t, 6> events;
			struct
			{
				int32_t eventA;
				int32_t eventB;
				int32_t eventC;
				int32_t eventD;
				int32_t eventE;
				int32_t eventF;
			};
		};
		int32_t sex;
		int32_t usedSpell;
		int32_t newsTopic;
	};
	static_assert(sizeof(mm8::NPC) == 0x4C, "Invalid \"mm8::NPC\" structure size");
	static_assert(offsetof(mm8::NPC, pic) == 4);
	static_assert(offsetof(mm8::NPC, bits) == 8);
	static_assert(offsetof(mm8::NPC, fame) == 12);
	static_assert(offsetof(mm8::NPC, rep) == 16);
	static_assert(offsetof(mm8::NPC, house) == 20);
	static_assert(offsetof(mm8::NPC, profession) == 24);
	static_assert(offsetof(mm8::NPC, greet) == 28);
	static_assert(offsetof(mm8::NPC, joins) == 32);
	static_assert(offsetof(mm8::NPC, tellsNews) == 36);
	static_assert(offsetof(mm8::NPC, events) == 40);
	static_assert(offsetof(mm8::NPC, eventA) == 40);
	static_assert(offsetof(mm8::NPC, eventB) == 44);
	static_assert(offsetof(mm8::NPC, eventC) == 48);
	static_assert(offsetof(mm8::NPC, eventD) == 52);
	static_assert(offsetof(mm8::NPC, eventE) == 56);
	static_assert(offsetof(mm8::NPC, eventF) == 60);
	static_assert(offsetof(mm8::NPC, sex) == 64);
	static_assert(offsetof(mm8::NPC, usedSpell) == 68);
	static_assert(offsetof(mm8::NPC, newsTopic) == 72);



	struct GameParty // size: 0xBB2EF8
	{
		SKIP(5346128);
		std::array<uint8_t, 4> currentPlayer; // Unknown type
		SKIP(6323056);
		int64_t lastRegenerationTime;
		union
		{
			std::array<int64_t, 5> nextBountyHunt;
			std::array<int64_t, 5> monsHuntReset;
		};
		SKIP(1240);
		std::array<int64_t, 29> history; // MMExt: 1..29, here 0..28
		std::array<int64_t, 20> specialDates; // MMExt: 1..20, here 0..19
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
		int32_t direction;
		int32_t lookAngle;
		int32_t lastX;
		int32_t lastY;
		int32_t lastZ;
		int32_t lastDirection;
		int32_t lastLookAngle;
		int32_t lastEyeLevel;
		int32_t speedX;
		int32_t speedY;
		int32_t speedZ;
		SKIP(4);
		int32_t stableZ;
		int32_t lastStandFacet;
		SKIP(8);
		int32_t fallStartZ;
		uint32_t flying; // 4-byte boolean
		SKIP(32);
		int32_t food;
		SKIP(8);
		int32_t gold;
		int32_t bankGold;
		int32_t deaths;
		SKIP(4);
		union
		{
			int32_t prisonTerms;
			int32_t pritsonTerms;
		};
		int32_t bountiesCollected;
		SKIP(4);
		union
		{
			std::array<int16_t, 5> bountyHuntTarget;
			std::array<int16_t, 5> monsHuntTarget;
		};
		union
		{
			std::array<uint16_t, 5> bountyHuntKilled; // 2-byte boolean
			std::array<int16_t, 5> monsHuntKilled;
		};
		SKIP(11);
		union
		{
			std::array<uint8_t, 216> QBits; // MMExt: 1..1734, here 0..1733 | array of abits (real index = 7 - usual)
			struct
			{
				SKIP(64);
				std::array<bool, 16> arcomageWins; // MMExt: 107..122, here 0..15
				int8_t inArenaQuest;
				int8_t arenaWinsPage;
				int8_t arenaWinsSquire;
				int8_t arenaWinsKnight;
				int8_t arenaWinsLord;
				std::array<bool, 68> artifactsFound; // MMExt: 500..567, here 0..67
				union
				{
					std::array<uint8_t, 87> autonotesBits; // MMExt: 1..697, here 0..696 | array of abits (real index = 7 - usual)
					struct
					{
						// uint8_t* reputation; // real size is 0 | Unknown type
					};
				};
			};
		};
		SKIP(57);
		std::array<mm8::SpellBuff, 20> spellBuffs;
		SKIP(4);
		std::array<mm8::Player, 50> playersArray;
		union
		{
			std::array<std::array<uint8_t, 4>, 5> players; // size field offset is 0xB7CA60 | Unknown type
			std::array<int32_t, 5> playersIndexes;
		};
		uint32_t players_size;
		SKIP(36);
		union
		{
			int32_t stateBits;
			struct
			{
				SKIPBITS(1);
				bool needRender : 1;
				bool drowning : 1;
				bool inAir : 1;
				bool enemyDetectorRed : 1;
				bool enemyDetectorYellow : 1;
				bool flyingBit : 1;
				bool waterWalkingBit : 1;
				bool inJumpSpell : 1;
				bool inLava : 1;
			};
		};
		SKIP(222312);
		int32_t fine;
	};
	static_assert(sizeof(mm8::GameParty) == 0xBB2EF8, "Invalid \"mm8::GameParty\" structure size");
	static_assert(offsetof(mm8::GameParty, currentPlayer) == 5346128);
	static_assert(offsetof(mm8::GameParty, lastRegenerationTime) == 11669188);
	static_assert(offsetof(mm8::GameParty, nextBountyHunt) == 11669196);
	static_assert(offsetof(mm8::GameParty, monsHuntReset) == 11669196);
	static_assert(offsetof(mm8::GameParty, history) == 11670476);
	static_assert(offsetof(mm8::GameParty, specialDates) == 11670708);
	static_assert(offsetof(mm8::GameParty, pos) == 11670868);
	static_assert(offsetof(mm8::GameParty, x) == 11670868);
	static_assert(offsetof(mm8::GameParty, y) == 11670872);
	static_assert(offsetof(mm8::GameParty, z) == 11670876);
	static_assert(offsetof(mm8::GameParty, direction) == 11670880);
	static_assert(offsetof(mm8::GameParty, lookAngle) == 11670884);
	static_assert(offsetof(mm8::GameParty, lastX) == 11670888);
	static_assert(offsetof(mm8::GameParty, lastY) == 11670892);
	static_assert(offsetof(mm8::GameParty, lastZ) == 11670896);
	static_assert(offsetof(mm8::GameParty, lastDirection) == 11670900);
	static_assert(offsetof(mm8::GameParty, lastLookAngle) == 11670904);
	static_assert(offsetof(mm8::GameParty, lastEyeLevel) == 11670908);
	static_assert(offsetof(mm8::GameParty, speedX) == 11670912);
	static_assert(offsetof(mm8::GameParty, speedY) == 11670916);
	static_assert(offsetof(mm8::GameParty, speedZ) == 11670920);
	static_assert(offsetof(mm8::GameParty, stableZ) == 11670928);
	static_assert(offsetof(mm8::GameParty, lastStandFacet) == 11670932);
	static_assert(offsetof(mm8::GameParty, fallStartZ) == 11670944);
	static_assert(offsetof(mm8::GameParty, flying) == 11670948);
	static_assert(offsetof(mm8::GameParty, food) == 11670984);
	static_assert(offsetof(mm8::GameParty, gold) == 11670996);
	static_assert(offsetof(mm8::GameParty, bankGold) == 11671000);
	static_assert(offsetof(mm8::GameParty, deaths) == 11671004);
	static_assert(offsetof(mm8::GameParty, prisonTerms) == 11671012);
	static_assert(offsetof(mm8::GameParty, pritsonTerms) == 11671012);
	static_assert(offsetof(mm8::GameParty, bountiesCollected) == 11671016);
	static_assert(offsetof(mm8::GameParty, bountyHuntTarget) == 11671024);
	static_assert(offsetof(mm8::GameParty, monsHuntTarget) == 11671024);
	static_assert(offsetof(mm8::GameParty, bountyHuntKilled) == 11671034);
	static_assert(offsetof(mm8::GameParty, monsHuntKilled) == 11671034);
	static_assert(offsetof(mm8::GameParty, arcomageWins) == 11671119);
	static_assert(offsetof(mm8::GameParty, inArenaQuest) == 11671135);
	static_assert(offsetof(mm8::GameParty, arenaWinsPage) == 11671136);
	static_assert(offsetof(mm8::GameParty, arenaWinsSquire) == 11671137);
	static_assert(offsetof(mm8::GameParty, arenaWinsKnight) == 11671138);
	static_assert(offsetof(mm8::GameParty, arenaWinsLord) == 11671139);
	static_assert(offsetof(mm8::GameParty, artifactsFound) == 11671140);
	static_assert(offsetof(mm8::GameParty, spellBuffs) == 11671352);
	static_assert(offsetof(mm8::GameParty, playersArray) == 11671676);
	static_assert(offsetof(mm8::GameParty, players) == 12044876);
	static_assert(offsetof(mm8::GameParty, playersIndexes) == 12044876);
	static_assert(offsetof(mm8::GameParty, players_size) == 12044896);
	static_assert(offsetof(mm8::GameParty, stateBits) == 12044936);
	static_assert(offsetof(mm8::GameParty, fine) == 12267252);



	struct Button // size: 0xBC
	{
		int32_t left;
		int32_t top;
		int32_t width;
		int32_t height;
		int32_t right;
		int32_t bottom;
		int32_t shape;
		int32_t hintAction;
		int32_t actionType;
		int32_t actionParam;
		int32_t actionParam2;
		uint32_t pressed; // 4-byte boolean
		uint32_t prevItemPtr;
		uint32_t nextItemPtr;
		union
		{
			mm8::Dlg* parent;
			uint32_t parentPtr;
		};
		std::array<int32_t, 5> sprites; // size field offset is 0x50
		uint32_t sprites_size;
		uint8_t shortCut;
		std::array<char, 103> hint; // fixed size string, requires null terminator
	};
	static_assert(sizeof(mm8::Button) == 0xBC, "Invalid \"mm8::Button\" structure size");
	static_assert(offsetof(mm8::Button, top) == 4);
	static_assert(offsetof(mm8::Button, width) == 8);
	static_assert(offsetof(mm8::Button, height) == 12);
	static_assert(offsetof(mm8::Button, right) == 16);
	static_assert(offsetof(mm8::Button, bottom) == 20);
	static_assert(offsetof(mm8::Button, shape) == 24);
	static_assert(offsetof(mm8::Button, hintAction) == 28);
	static_assert(offsetof(mm8::Button, actionType) == 32);
	static_assert(offsetof(mm8::Button, actionParam) == 36);
	static_assert(offsetof(mm8::Button, actionParam2) == 40);
	static_assert(offsetof(mm8::Button, pressed) == 44);
	static_assert(offsetof(mm8::Button, prevItemPtr) == 48);
	static_assert(offsetof(mm8::Button, nextItemPtr) == 52);
	static_assert(offsetof(mm8::Button, parent) == 56);
	static_assert(offsetof(mm8::Button, parentPtr) == 56);
	static_assert(offsetof(mm8::Button, sprites) == 60);
	static_assert(offsetof(mm8::Button, sprites_size) == 80);
	static_assert(offsetof(mm8::Button, shortCut) == 84);
	static_assert(offsetof(mm8::Button, hint) == 85);
}

#pragma pack(pop)