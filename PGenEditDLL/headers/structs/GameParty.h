#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct Button // size: 0xB8
	{
		int32_t left; // 0x0 (0 decimal)
		int32_t top; // 0x4 (4 decimal)
		int32_t width; // 0x8 (8 decimal)
		int32_t height; // 0xC (12 decimal)
		union
		{
			int32_t right; // 0x10 (16 decimal)
			int32_t rightPixel; // 0x10 (16 decimal) | MMExt info: !Lua[[= Left + Width - 1]]  (it was called 'Right' before MMExtension v2.3, old name is supported for backward compatibility)
		};
		union
		{
			int32_t bottom; // 0x14 (20 decimal)
			int32_t bottomPixel; // 0x14 (20 decimal) | MMExt info: !Lua[[= Top + Height - 1]]  (it was called 'Bottom' before MMExtension v2.3, old name is supported for backward compatibility)
		};
		// MMExt info: 1 - Rectangle.
		// 2 - Ellipse. 'Left' and 'Top' are center coordinates, 'Width' and 'Height' are radii. In MM6 it's always a circle and 'Height' is '0'.
		// 3 - Skill rectangle.
		int32_t shape; // 0x18 (24 decimal)
		int32_t hintAction; // 0x1C (28 decimal)
		union
		{
			int32_t action; // 0x20 (32 decimal)
			int32_t actionType; // 0x20 (32 decimal)
		};
		int32_t actionParam; // 0x24 (36 decimal)
		uint32_t pressed; // 4-byte boolean | 0x28 (40 decimal)
		uint32_t prevItemPtr; // 0x2C (44 decimal)
		uint32_t nextItemPtr; // 0x30 (48 decimal)
		union
		{
			std::array<uint8_t, 4> parent; // Unknown type | 0x34 (52 decimal)
			uint32_t parentPtr; // 0x34 (52 decimal)
		};
		std::array<int32_t, 5> sprites; // size field offset is 0x4C | 0x38 (56 decimal)
		uint32_t sprites_size; // 0x4C (76 decimal)
		union
		{
			uint8_t key; // 0x50 (80 decimal)
			uint8_t shortCut; // 0x50 (80 decimal)
		};
		std::array<char, 103> hint; // fixed size string, requires null terminator | 0x51 (81 decimal)
	};
	static_assert(sizeof(mm6::Button) == 0xB8, "Invalid \"mm6::Button\" structure size");
	static_assert(offsetof(mm6::Button, top) == 4);
	static_assert(offsetof(mm6::Button, width) == 8);
	static_assert(offsetof(mm6::Button, height) == 12);
	static_assert(offsetof(mm6::Button, right) == 16);
	static_assert(offsetof(mm6::Button, rightPixel) == 16);
	static_assert(offsetof(mm6::Button, bottom) == 20);
	static_assert(offsetof(mm6::Button, bottomPixel) == 20);
	static_assert(offsetof(mm6::Button, shape) == 24);
	static_assert(offsetof(mm6::Button, hintAction) == 28);
	static_assert(offsetof(mm6::Button, action) == 32);
	static_assert(offsetof(mm6::Button, actionType) == 32);
	static_assert(offsetof(mm6::Button, actionParam) == 36);
	static_assert(offsetof(mm6::Button, pressed) == 40);
	static_assert(offsetof(mm6::Button, prevItemPtr) == 44);
	static_assert(offsetof(mm6::Button, nextItemPtr) == 48);
	static_assert(offsetof(mm6::Button, parent) == 52);
	static_assert(offsetof(mm6::Button, parentPtr) == 52);
	static_assert(offsetof(mm6::Button, sprites) == 56);
	static_assert(offsetof(mm6::Button, sprites_size) == 76);
	static_assert(offsetof(mm6::Button, key) == 80);
	static_assert(offsetof(mm6::Button, shortCut) == 80);
	static_assert(offsetof(mm6::Button, hint) == 81);



	struct NPCNewsItem // size: 0xC
	{
		char* topic; // EditPChar | 0x0 (0 decimal)
		char* text; // EditPChar | 0x4 (4 decimal)
		int8_t map; // 0x8 (8 decimal)
		SKIP(3);
	};
	static_assert(sizeof(mm6::NPCNewsItem) == 0xC, "Invalid \"mm6::NPCNewsItem\" structure size");
	static_assert(offsetof(mm6::NPCNewsItem, text) == 4);
	static_assert(offsetof(mm6::NPCNewsItem, map) == 8);



	struct NPC // size: 0x3C
	{
		union
		{
			uint32_t exist; // 4-byte boolean | 0x0 (0 decimal) | MMExt info: Use to check if a slot is empty in Party.HiredNPC array
			char* name; // EditPChar | 0x0 (0 decimal)
		};
		int32_t pic; // 0x4 (4 decimal)
		union
		{
			uint32_t bits; // 0x8 (8 decimal)
			struct
			{
				bool bribedBefore : 1; // 0x8 (8 decimal), bit index 7 | MMExt info: Set to 'true' the first time you interact with the NPC, set to 'false' the second time
				bool beggedBefore : 1; // 0x8 (8 decimal), bit index 6 | MMExt info: Set to 'true' when you visit the NPC the second time
				bool threatenedBefore : 1; // 0x8 (8 decimal), bit index 5
				SKIPBITS(4);
				bool hired : 1; // 0x8 (8 decimal), bit index 0
			};
		};
		int32_t fame; // 0xC (12 decimal)
		int32_t rep; // 0x10 (16 decimal)
		int32_t house; // 0x14 (20 decimal)
		int32_t profession; // 0x18 (24 decimal)
		int32_t joins; // 0x1C (28 decimal)
		int32_t tellsNews; // 0x20 (32 decimal)
		union
		{
			std::array<int32_t, 3> events; // 0x24 (36 decimal)
			struct
			{
				int32_t eventA; // 0x24 (36 decimal)
				int32_t eventB; // 0x28 (40 decimal)
				int32_t eventC; // 0x2C (44 decimal)
			};
		};
		int32_t sex; // 0x30 (48 decimal)
		int32_t usedSpell; // 0x34 (52 decimal)
		int32_t newsTopic; // 0x38 (56 decimal)
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
		static uint8_t* QBits; // original offset 0x908D6D (9473389 decimal)element size: 0x0 (0 decimal)
		static uint32_t QBits_size; // Offset/size: 0x40 (64 decimal)

		SKIP(5066984);
		std::array<uint8_t, 4> currentPlayer; // Unknown type | 0x4D50E8 (5066984 decimal)
		SKIP(4406188);
		union
		{
			std::array<int32_t, 3> pos; // 0x908C98 (9473176 decimal)
			struct
			{
				int32_t x; // 0x908C98 (9473176 decimal)
				int32_t y; // 0x908C9C (9473180 decimal)
				int32_t z; // 0x908CA0 (9473184 decimal)
			};
		};
		int32_t direction; // 0x908CA4 (9473188 decimal) | MMExt info: 0 - 2047. 0 is East, 512 is North and so on.
		int32_t lookAngle; // 0x908CA8 (9473192 decimal) | MMExt info: -512 - 512. Values allowed with mouse look: -240 - 300 (prior to patch 2.5: -200 - 200). Without mouse look: -128 - 128
		int32_t lastX; // 0x908CAC (9473196 decimal)
		int32_t lastY; // 0x908CB0 (9473200 decimal)
		int32_t lastZ; // 0x908CB4 (9473204 decimal)
		int32_t lastDirection; // 0x908CB8 (9473208 decimal)
		int32_t lastLookAngle; // 0x908CBC (9473212 decimal)
		int32_t lastEyeLevel; // 0x908CC0 (9473216 decimal)
		int32_t speedX; // 0x908CC4 (9473220 decimal)
		int32_t speedY; // 0x908CC8 (9473224 decimal)
		int32_t speedZ; // 0x908CCC (9473228 decimal)
		SKIP(4);
		int32_t stableZ; // 0x908CD4 (9473236 decimal) | MMExt info: 'Z' changes up and down while flying, 'StableZ' stays the same
		int32_t lastStandFacet; // 0x908CD8 (9473240 decimal)
		SKIP(8);
		int32_t fallStartZ; // 0x908CE4 (9473252 decimal)
		uint32_t flying; // 4-byte boolean | 0x908CE8 (9473256 decimal)
		SKIP(64);
		int32_t food; // 0x908D2C (9473324 decimal)
		SKIP(24);
		int32_t reputation; // 0x908D48 (9473352 decimal)
		SKIP(4);
		int32_t gold; // 0x908D50 (9473360 decimal)
		int32_t bankGold; // 0x908D54 (9473364 decimal)
		int32_t deaths; // 0x908D58 (9473368 decimal)
		SKIP(4);
		union
		{
			int32_t prisonTerms; // 0x908D60 (9473376 decimal)
			int32_t pritsonTerms; // 0x908D60 (9473376 decimal)
		};
		int32_t bountiesCollected; // 0x908D64 (9473380 decimal)
		SKIP(69);
		std::array<uint8_t, 16> autonotesBits; // MMExt: 1..128, here 0..127 | array of abits (real index = 7 - usual) | 0x908DAD (9473453 decimal)
		int8_t inArenaQuest; // 0x908DBD (9473469 decimal)
		int8_t arenaWinsPage; // 0x908DBE (9473470 decimal)
		int8_t arenaWinsSquire; // 0x908DBF (9473471 decimal)
		int8_t arenaWinsKnight; // 0x908DC0 (9473472 decimal)
		int8_t arenaWinsLord; // 0x908DC1 (9473473 decimal)
		SKIP(3);
		union
		{
			std::array<uint8_t, 3> bountyHuntTarget; // 0x908DC5 (9473477 decimal)
			std::array<uint8_t, 3> monsHuntTarget; // 0x908DC5 (9473477 decimal)
		};
		union
		{
			std::array<bool, 3> bountyHuntKilled; // 0x908DC8 (9473480 decimal)
			std::array<bool, 3> monsHuntKilled; // 0x908DC8 (9473480 decimal)
		};
		std::array<bool, 30> artifactsFound; // MMExt: 400..429, here 0..29 | 0x908DCB (9473483 decimal)
		SKIP(75);
		std::array<mm6::SpellBuff, 16> spellBuffs; // 0x908E34 (9473588 decimal)
		std::array<mm6::Player, 4> playersArray; // 0x908F34 (9473844 decimal) | MMExt info: Array of all players
		std::array<mm6::NPC, 2> hiredNPC; // MMExt: 1..2, here 0..1 | 0x90E7A4 (9496484 decimal)
		SKIP(28);
		union
		{
			int32_t stateBits; // 0x90E838 (9496632 decimal)
			struct
			{
				SKIPBITS(1);
				bool needRender : 1; // 0x90E838 (9496632 decimal), bit index 6
				bool drowning : 1; // 0x90E838 (9496632 decimal), bit index 5
				bool inAir : 1; // 0x90E838 (9496632 decimal), bit index 4
				bool enemyDetectorRed : 1; // 0x90E838 (9496632 decimal), bit index 3
				bool enemyDetectorYellow : 1; // 0x90E838 (9496632 decimal), bit index 2
				bool flyingBit : 1; // 0x90E838 (9496632 decimal), bit index 1
				bool waterWalkingBit : 1; // 0x90E838 (9496632 decimal), bit index 0
				bool inJumpSpell : 1; // 0x90E839 (9496633 decimal), bit index 7
				bool inLava : 1; // 0x90E839 (9496633 decimal), bit index 6
			};
		};
		int64_t lastRegenerationTime; // 0x90E83C (9496636 decimal)
		union
		{
			std::array<int64_t, 3> monsHuntReset; // 0x90E844 (9496644 decimal)
			std::array<int64_t, 3> nextBountyHunt; // 0x90E844 (9496644 decimal)
		};
		SKIP(40978);
		std::array<std::array<char, 100>, 2> hiredNPCName; // MMExt: 1..2, here 0..1 | fixed size string, requires null terminator | 0x91886E (9537646 decimal)
		SKIP(181042);
		std::array<std::array<uint8_t, 4>, 4> players; // Unknown type | 0x944C68 (9718888 decimal) | MMExt info: Array of players corresponding to each player slot
		int __thiscall findActivePlayer(); // address: 0x487780 | defaults: 9473136
		int __thiscall getFame(); // address: 0x485510 | defaults: 9473136
		int __thiscall getReputation(); // address: 0x47D600 | defaults: 9473136
		int __thiscall getRepuataion (); // address: 0x47D600 | defaults: 9473136
		int __fastcall addGold(/*Gold, Kind = 0*/); // address: 0x41EDE0 | defaults: 0, 0
		bool __thiscall hasNPCProfession(); // address: 0x467F30
		int __fastcall wait(/*Minutes*/); // address: 0x487980
		int __fastcall addKillExp(/*Experience*/); // address: 0x421520
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
	static_assert(offsetof(mm6::GameParty, prisonTerms) == 9473376);
	static_assert(offsetof(mm6::GameParty, pritsonTerms) == 9473376);
	static_assert(offsetof(mm6::GameParty, bountiesCollected) == 9473380);
	static_assert(offsetof(mm6::GameParty, inArenaQuest) == 9473469);
	static_assert(offsetof(mm6::GameParty, arenaWinsPage) == 9473470);
	static_assert(offsetof(mm6::GameParty, arenaWinsSquire) == 9473471);
	static_assert(offsetof(mm6::GameParty, arenaWinsKnight) == 9473472);
	static_assert(offsetof(mm6::GameParty, arenaWinsLord) == 9473473);
	static_assert(offsetof(mm6::GameParty, bountyHuntTarget) == 9473477);
	static_assert(offsetof(mm6::GameParty, monsHuntTarget) == 9473477);
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
	struct Button // size: 0xBC
	{
		int32_t left; // 0x0 (0 decimal)
		int32_t top; // 0x4 (4 decimal)
		int32_t width; // 0x8 (8 decimal)
		int32_t height; // 0xC (12 decimal)
		union
		{
			int32_t right; // 0x10 (16 decimal)
			int32_t rightPixel; // 0x10 (16 decimal) | MMExt info: !Lua[[= Left + Width - 1]]  (it was called 'Right' before MMExtension v2.3, old name is supported for backward compatibility)
		};
		union
		{
			int32_t bottom; // 0x14 (20 decimal)
			int32_t bottomPixel; // 0x14 (20 decimal) | MMExt info: !Lua[[= Top + Height - 1]]  (it was called 'Bottom' before MMExtension v2.3, old name is supported for backward compatibility)
		};
		// MMExt info: 1 - Rectangle.
		// 2 - Ellipse. 'Left' and 'Top' are center coordinates, 'Width' and 'Height' are radii. In MM6 it's always a circle and 'Height' is '0'.
		// 3 - Skill rectangle.
		int32_t shape; // 0x18 (24 decimal)
		int32_t hintAction; // 0x1C (28 decimal)
		union
		{
			int32_t action; // 0x20 (32 decimal)
			int32_t actionType; // 0x20 (32 decimal)
		};
		int32_t actionParam; // 0x24 (36 decimal)
		int32_t actionParam2; // 0x28 (40 decimal)
		uint32_t pressed; // 4-byte boolean | 0x2C (44 decimal)
		uint32_t prevItemPtr; // 0x30 (48 decimal)
		uint32_t nextItemPtr; // 0x34 (52 decimal)
		union
		{
			std::array<uint8_t, 4> parent; // Unknown type | 0x38 (56 decimal)
			uint32_t parentPtr; // 0x38 (56 decimal)
		};
		std::array<int32_t, 5> sprites; // size field offset is 0x50 | 0x3C (60 decimal)
		uint32_t sprites_size; // 0x50 (80 decimal)
		union
		{
			uint8_t key; // 0x54 (84 decimal)
			uint8_t shortCut; // 0x54 (84 decimal)
		};
		std::array<char, 103> hint; // fixed size string, requires null terminator | 0x55 (85 decimal)
	};
	static_assert(sizeof(mm7::Button) == 0xBC, "Invalid \"mm7::Button\" structure size");
	static_assert(offsetof(mm7::Button, top) == 4);
	static_assert(offsetof(mm7::Button, width) == 8);
	static_assert(offsetof(mm7::Button, height) == 12);
	static_assert(offsetof(mm7::Button, right) == 16);
	static_assert(offsetof(mm7::Button, rightPixel) == 16);
	static_assert(offsetof(mm7::Button, bottom) == 20);
	static_assert(offsetof(mm7::Button, bottomPixel) == 20);
	static_assert(offsetof(mm7::Button, shape) == 24);
	static_assert(offsetof(mm7::Button, hintAction) == 28);
	static_assert(offsetof(mm7::Button, action) == 32);
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
	static_assert(offsetof(mm7::Button, key) == 84);
	static_assert(offsetof(mm7::Button, shortCut) == 84);
	static_assert(offsetof(mm7::Button, hint) == 85);



	struct NPC // size: 0x4C
	{
		union
		{
			uint32_t exist; // 4-byte boolean | 0x0 (0 decimal) | MMExt info: Use to check if a slot is empty in Party.HiredNPC array
			char* name; // EditPChar | 0x0 (0 decimal)
		};
		int32_t pic; // 0x4 (4 decimal)
		union
		{
			uint32_t bits; // 0x8 (8 decimal)
			struct
			{
				bool talkedOnce : 1; // 0x8 (8 decimal), bit index 7 | MMExt info: Set to 'true' the first time you interact with the NPC, set to 'false' the second time
				bool talkedBefore : 1; // 0x8 (8 decimal), bit index 6 | MMExt info: Set to 'true' when you visit the NPC the second time
				bool threatenedBefore : 1; // 0x8 (8 decimal), bit index 5
				SKIPBITS(4);
				bool hired : 1; // 0x8 (8 decimal), bit index 0
			};
		};
		int32_t fame; // 0xC (12 decimal)
		int32_t rep; // 0x10 (16 decimal)
		int32_t house; // 0x14 (20 decimal)
		int32_t profession; // 0x18 (24 decimal)
		int32_t greet; // 0x1C (28 decimal)
		int32_t joins; // 0x20 (32 decimal)
		int32_t tellsNews; // 0x24 (36 decimal)
		union
		{
			std::array<int32_t, 6> events; // 0x28 (40 decimal)
			struct
			{
				int32_t eventA; // 0x28 (40 decimal)
				int32_t eventB; // 0x2C (44 decimal)
				int32_t eventC; // 0x30 (48 decimal)
				int32_t eventD; // 0x34 (52 decimal)
				int32_t eventE; // 0x38 (56 decimal)
				int32_t eventF; // 0x3C (60 decimal)
			};
		};
		int32_t sex; // 0x40 (64 decimal)
		int32_t usedSpell; // 0x44 (68 decimal)
		int32_t newsTopic; // 0x48 (72 decimal)
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
		static uint8_t* QBits; // original offset 0xACD59D (11326877 decimal)element size: 0x0 (0 decimal)
		static uint32_t QBits_size; // Offset/size: 0x40 (64 decimal)

		SKIP(5274220);
		std::array<uint8_t, 4> currentPlayer; // Unknown type | 0x507A6C (5274220 decimal)
		SKIP(5690584);
		std::array<std::array<uint8_t, 4>, 4> players; // Unknown type | 0xA74F48 (10964808 decimal) | MMExt info: Array of players corresponding to each player slot
		SKIP(360212);
		int64_t lastRegenerationTime; // 0xACCE6C (11325036 decimal)
		union
		{
			std::array<int64_t, 5> monsHuntReset; // 0xACCE74 (11325044 decimal) | MMExt info: (deprecated old name)
			std::array<int64_t, 5> nextBountyHunt; // 0xACCE74 (11325044 decimal)
		};
		SKIP(1224);
		std::array<int64_t, 29> history; // MMExt: 1..29, here 0..28 | 0xACD364 (11326308 decimal)
		// MMExt info: E.g. set date 1:!Lua[[
		// evt.Add("SpecialDate1", 0)]]
		// Use date 1: "%51" in any NPC message
		std::array<int64_t, 20> specialDates; // MMExt: 1..20, here 0..19 | 0xACD44C (11326540 decimal)
		union
		{
			std::array<int32_t, 3> pos; // 0xACD4EC (11326700 decimal)
			struct
			{
				int32_t x; // 0xACD4EC (11326700 decimal)
				int32_t y; // 0xACD4F0 (11326704 decimal)
				int32_t z; // 0xACD4F4 (11326708 decimal)
			};
		};
		int32_t direction; // 0xACD4F8 (11326712 decimal) | MMExt info: 0 - 2047. 0 is East, 512 is North and so on.
		int32_t lookAngle; // 0xACD4FC (11326716 decimal) | MMExt info: -512 - 512. Values allowed with mouse look: -240 - 300 (prior to patch 2.5: -200 - 200). Without mouse look: -128 - 128
		int32_t lastX; // 0xACD500 (11326720 decimal)
		int32_t lastY; // 0xACD504 (11326724 decimal)
		int32_t lastZ; // 0xACD508 (11326728 decimal)
		int32_t lastDirection; // 0xACD50C (11326732 decimal)
		int32_t lastLookAngle; // 0xACD510 (11326736 decimal)
		int32_t lastEyeLevel; // 0xACD514 (11326740 decimal)
		int32_t speedX; // 0xACD518 (11326744 decimal)
		int32_t speedY; // 0xACD51C (11326748 decimal)
		int32_t speedZ; // 0xACD520 (11326752 decimal)
		SKIP(4);
		int32_t stableZ; // 0xACD528 (11326760 decimal) | MMExt info: 'Z' changes up and down while flying, 'StableZ' stays the same
		int32_t lastStandFacet; // 0xACD52C (11326764 decimal)
		SKIP(8);
		int32_t fallStartZ; // 0xACD538 (11326776 decimal)
		uint32_t flying; // 4-byte boolean | 0xACD53C (11326780 decimal)
		SKIP(32);
		int32_t food; // 0xACD560 (11326816 decimal)
		SKIP(8);
		int32_t gold; // 0xACD56C (11326828 decimal)
		int32_t bankGold; // 0xACD570 (11326832 decimal)
		int32_t deaths; // 0xACD574 (11326836 decimal)
		SKIP(4);
		union
		{
			int32_t prisonTerms; // 0xACD57C (11326844 decimal)
			int32_t pritsonTerms; // 0xACD57C (11326844 decimal)
		};
		int32_t bountiesCollected; // 0xACD580 (11326848 decimal)
		SKIP(4);
		union
		{
			std::array<int16_t, 5> bountyHuntTarget; // 0xACD588 (11326856 decimal) | MMExt info: Only index 0 is normally used in MM8
			std::array<int16_t, 5> monsHuntTarget; // 0xACD588 (11326856 decimal) | MMExt info: (deprecated old name)
		};
		union
		{
			std::array<uint16_t, 5> bountyHuntKilled; // 2-byte boolean | 0xACD592 (11326866 decimal) | MMExt info: Only index 0 is normally used in MM8
			std::array<int16_t, 5> monsHuntKilled; // 0xACD592 (11326866 decimal) | MMExt info: (deprecated old name, integer in MM7+ instead of boolean)
		};
		SKIP(65);
		std::array<bool, 16> arcomageWins; // MMExt: 108..123, here 0..15 | 0xACD5DD (11326941 decimal)
		int8_t inArenaQuest; // 0xACD5ED (11326957 decimal)
		int8_t arenaWinsPage; // 0xACD5EE (11326958 decimal)
		int8_t arenaWinsSquire; // 0xACD5EF (11326959 decimal)
		int8_t arenaWinsKnight; // 0xACD5F0 (11326960 decimal)
		int8_t arenaWinsLord; // 0xACD5F1 (11326961 decimal)
		std::array<bool, 68> artifactsFound; // MMExt: 500..567, here 0..67 | 0xACD5F2 (11326962 decimal)
		std::array<uint8_t, 31> autonotesBits; // MMExt: 1..255, here 0..254 | array of abits (real index = 7 - usual) | 0xACD636 (11327030 decimal)
		SKIP(107);
		int32_t alignment; // 0xACD6C0 (11327168 decimal) | MMExt info: 0 = good, 1 = neutral, 2 = evil
		union
		{
			std::array<mm7::SpellBuff, 20> spellBuffs; // 0xACD6C4 (11327172 decimal)
			struct
			{
				// uint8_t* reputation; // real size is 0 | Unknown type | 0xACD6C4 (11327172 decimal)
			};
		};
		std::array<mm7::Player, 4> playersArray; // 0xACD804 (11327492 decimal) | MMExt info: Array of all players
		std::array<mm7::NPC, 2> hiredNPC; // MMExt: 1..2, here 0..1 | 0xAD44F4 (11355380 decimal)
		SKIP(36);
		union
		{
			int32_t stateBits; // 0xAD45B0 (11355568 decimal)
			struct
			{
				SKIPBITS(1);
				bool needRender : 1; // 0xAD45B0 (11355568 decimal), bit index 6
				bool drowning : 1; // 0xAD45B0 (11355568 decimal), bit index 5
				bool inAir : 1; // 0xAD45B0 (11355568 decimal), bit index 4
				bool enemyDetectorRed : 1; // 0xAD45B0 (11355568 decimal), bit index 3
				bool enemyDetectorYellow : 1; // 0xAD45B0 (11355568 decimal), bit index 2
				bool flyingBit : 1; // 0xAD45B0 (11355568 decimal), bit index 1
				bool waterWalkingBit : 1; // 0xAD45B0 (11355568 decimal), bit index 0
				bool inJumpSpell : 1; // 0xAD45B1 (11355569 decimal), bit index 7
				bool inLava : 1; // 0xAD45B1 (11355569 decimal), bit index 6
			};
		};
		SKIP(59640);
		std::array<std::array<char, 100>, 2> hiredNPCName; // MMExt: 1..2, here 0..1 | fixed size string, requires null terminator | 0xAE2EAC (11415212 decimal)
		SKIP(236);
		int32_t fine; // 0xAE3060 (11415648 decimal)
		int __fastcall wait(/*Minutes*/); // address: 0x4938C9
		int __fastcall addGold(/*Gold, Kind = 0*/); // address: 0x420BAE | defaults: 0, 0
		int __thiscall findActivePlayer(); // address: 0x493707 | defaults: 11324984
		int __thiscall getFame(); // address: 0x491356 | defaults: 11324984
		int __thiscall getReputation(); // address: 0x47752F | defaults: 11324984
		int __fastcall addKillExp(/*Experience*/); // address: 0x42694B
		bool __thiscall hasNPCProfession(); // address: 0x476399
		int __thiscall getRepuataion (); // address: 0x47752F | defaults: 11324984
	};
	static_assert(sizeof(mm7::GameParty) == 0xAE3064, "Invalid \"mm7::GameParty\" structure size");
	static_assert(offsetof(mm7::GameParty, currentPlayer) == 5274220);
	static_assert(offsetof(mm7::GameParty, players) == 10964808);
	static_assert(offsetof(mm7::GameParty, lastRegenerationTime) == 11325036);
	static_assert(offsetof(mm7::GameParty, monsHuntReset) == 11325044);
	static_assert(offsetof(mm7::GameParty, nextBountyHunt) == 11325044);
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
	static_assert(offsetof(mm7::GameParty, bountyHuntKilled) == 11326866);
	static_assert(offsetof(mm7::GameParty, monsHuntKilled) == 11326866);
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
}
namespace mm8
{
	struct NPC // size: 0x4C
	{
		union
		{
			uint32_t exist; // 4-byte boolean | 0x0 (0 decimal) | MMExt info: Use to check if a slot is empty in Party.HiredNPC array
			char* name; // EditPChar | 0x0 (0 decimal)
		};
		int32_t pic; // 0x4 (4 decimal)
		union
		{
			uint32_t bits; // 0x8 (8 decimal)
			struct
			{
				bool bribedBefore : 1; // 0x8 (8 decimal), bit index 7
				bool talkedBefore : 1; // 0x8 (8 decimal), bit index 6
				bool threatenedBefore : 1; // 0x8 (8 decimal), bit index 5
				SKIPBITS(4);
				bool hired : 1; // 0x9 (9 decimal), bit index 0
			};
		};
		int32_t fame; // 0xC (12 decimal)
		int32_t rep; // 0x10 (16 decimal)
		int32_t house; // 0x14 (20 decimal)
		int32_t profession; // 0x18 (24 decimal)
		int32_t greet; // 0x1C (28 decimal)
		int32_t joins; // 0x20 (32 decimal)
		int32_t tellsNews; // 0x24 (36 decimal)
		union
		{
			std::array<int32_t, 6> events; // 0x28 (40 decimal)
			struct
			{
				int32_t eventA; // 0x28 (40 decimal)
				int32_t eventB; // 0x2C (44 decimal)
				int32_t eventC; // 0x30 (48 decimal)
				int32_t eventD; // 0x34 (52 decimal)
				int32_t eventE; // 0x38 (56 decimal)
				int32_t eventF; // 0x3C (60 decimal)
			};
		};
		int32_t sex; // 0x40 (64 decimal)
		int32_t usedSpell; // 0x44 (68 decimal)
		int32_t newsTopic; // 0x48 (72 decimal)
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
		static uint8_t* QBits; // original offset 0xB2160F (11671055 decimal)element size: 0x0 (0 decimal)
		static uint32_t QBits_size; // Offset/size: 0x101 (257 decimal)

		SKIP(5346128);
		std::array<uint8_t, 4> currentPlayer; // Unknown type | 0x519350 (5346128 decimal)
		SKIP(6323056);
		int64_t lastRegenerationTime; // 0xB20EC4 (11669188 decimal)
		union
		{
			std::array<int64_t, 5> monsHuntReset; // 0xB20ECC (11669196 decimal) | MMExt info: (deprecated old name)
			std::array<int64_t, 5> nextBountyHunt; // 0xB20ECC (11669196 decimal)
		};
		SKIP(1240);
		std::array<int64_t, 29> history; // MMExt: 1..29, here 0..28 | 0xB213CC (11670476 decimal)
		// MMExt info: E.g. set date 1:!Lua[[
		// evt.Add("SpecialDate1", 0)]]
		// Use date 1: "%51" in any NPC message
		std::array<int64_t, 20> specialDates; // MMExt: 1..20, here 0..19 | 0xB214B4 (11670708 decimal)
		union
		{
			std::array<int32_t, 3> pos; // 0xB21554 (11670868 decimal)
			struct
			{
				int32_t x; // 0xB21554 (11670868 decimal)
				int32_t y; // 0xB21558 (11670872 decimal)
				int32_t z; // 0xB2155C (11670876 decimal)
			};
		};
		int32_t direction; // 0xB21560 (11670880 decimal) | MMExt info: 0 - 2047. 0 is East, 512 is North and so on.
		int32_t lookAngle; // 0xB21564 (11670884 decimal) | MMExt info: -512 - 512. Values allowed with mouse look: -240 - 300 (prior to patch 2.5: -200 - 200). Without mouse look: -128 - 128
		int32_t lastX; // 0xB21568 (11670888 decimal)
		int32_t lastY; // 0xB2156C (11670892 decimal)
		int32_t lastZ; // 0xB21570 (11670896 decimal)
		int32_t lastDirection; // 0xB21574 (11670900 decimal)
		int32_t lastLookAngle; // 0xB21578 (11670904 decimal)
		int32_t lastEyeLevel; // 0xB2157C (11670908 decimal)
		int32_t speedX; // 0xB21580 (11670912 decimal)
		int32_t speedY; // 0xB21584 (11670916 decimal)
		int32_t speedZ; // 0xB21588 (11670920 decimal)
		SKIP(4);
		int32_t stableZ; // 0xB21590 (11670928 decimal) | MMExt info: 'Z' changes up and down while flying, 'StableZ' stays the same
		int32_t lastStandFacet; // 0xB21594 (11670932 decimal)
		SKIP(8);
		int32_t fallStartZ; // 0xB215A0 (11670944 decimal)
		uint32_t flying; // 4-byte boolean | 0xB215A4 (11670948 decimal)
		SKIP(32);
		int32_t food; // 0xB215C8 (11670984 decimal)
		SKIP(8);
		int32_t gold; // 0xB215D4 (11670996 decimal)
		int32_t bankGold; // 0xB215D8 (11671000 decimal)
		int32_t deaths; // 0xB215DC (11671004 decimal)
		SKIP(4);
		union
		{
			int32_t prisonTerms; // 0xB215E4 (11671012 decimal)
			int32_t pritsonTerms; // 0xB215E4 (11671012 decimal)
		};
		int32_t bountiesCollected; // 0xB215E8 (11671016 decimal)
		SKIP(4);
		union
		{
			std::array<int16_t, 5> bountyHuntTarget; // 0xB215F0 (11671024 decimal) | MMExt info: Only index 0 is normally used in MM8
			std::array<int16_t, 5> monsHuntTarget; // 0xB215F0 (11671024 decimal) | MMExt info: (deprecated old name)
		};
		union
		{
			std::array<uint16_t, 5> bountyHuntKilled; // 2-byte boolean | 0xB215FA (11671034 decimal) | MMExt info: Only index 0 is normally used in MM8
			std::array<int16_t, 5> monsHuntKilled; // 0xB215FA (11671034 decimal) | MMExt info: (deprecated old name, integer in MM7+ instead of boolean)
		};
		SKIP(75);
		std::array<bool, 16> arcomageWins; // MMExt: 107..122, here 0..15 | 0xB2164F (11671119 decimal)
		int8_t inArenaQuest; // 0xB2165F (11671135 decimal)
		int8_t arenaWinsPage; // 0xB21660 (11671136 decimal)
		int8_t arenaWinsSquire; // 0xB21661 (11671137 decimal)
		int8_t arenaWinsKnight; // 0xB21662 (11671138 decimal)
		int8_t arenaWinsLord; // 0xB21663 (11671139 decimal)
		std::array<bool, 68> artifactsFound; // MMExt: 500..567, here 0..67 | 0xB21664 (11671140 decimal)
		union
		{
			std::array<uint8_t, 87> autonotesBits; // MMExt: 1..697, here 0..696 | array of abits (real index = 7 - usual) | 0xB216A8 (11671208 decimal)
			struct
			{
				// uint8_t* reputation; // real size is 0 | Unknown type | 0xB216A8 (11671208 decimal)
			};
		};
		SKIP(57);
		std::array<mm8::SpellBuff, 20> spellBuffs; // 0xB21738 (11671352 decimal)
		SKIP(4);
		std::array<mm8::Player, 50> playersArray; // 0xB2187C (11671676 decimal)
		union
		{
			std::array<std::array<uint8_t, 4>, 5> players; // size field offset is 0xB7CA60 | Unknown type | 0xB7CA4C (12044876 decimal)
			std::array<int32_t, 5> playersIndexes; // 0xB7CA4C (12044876 decimal)
		};
		uint32_t players_size; // 0xB7CA60 (12044896 decimal)
		SKIP(36);
		union
		{
			int32_t stateBits; // 0xB7CA88 (12044936 decimal)
			struct
			{
				SKIPBITS(1);
				bool needRender : 1; // 0xB7CA88 (12044936 decimal), bit index 6
				bool drowning : 1; // 0xB7CA88 (12044936 decimal), bit index 5
				bool inAir : 1; // 0xB7CA88 (12044936 decimal), bit index 4
				bool enemyDetectorRed : 1; // 0xB7CA88 (12044936 decimal), bit index 3
				bool enemyDetectorYellow : 1; // 0xB7CA89 (12044937 decimal), bit index 2
				bool flyingBit : 1; // 0xB7CA89 (12044937 decimal), bit index 1
				bool waterWalkingBit : 1; // 0xB7CA89 (12044937 decimal), bit index 0
				bool inJumpSpell : 1; // 0xB7CA89 (12044937 decimal), bit index 7
				bool inLava : 1; // 0xB7CA89 (12044937 decimal), bit index 6
			};
		};
		SKIP(222312);
		int32_t fine; // 0xBB2EF4 (12267252 decimal)
		int __fastcall wait(/*Minutes*/); // address: 0x491C65
		int __thiscall getFame(); // address: 0x49039B | defaults: 11669136
		int __fastcall addGold(/*Gold, Kind = 0*/); // address: 0x420131 | defaults: 0, 0
		int __thiscall getReputation(); // address: 0x47603F | defaults: 11669136
		int __thiscall findActivePlayer(); // address: 0x491A55 | defaults: 11669136
		int __thiscall resetStartingPlayer(); // address: 0x4903C0 | defaults: (this), false, false
		int __thiscall getRepuataion (); // address: 0x47603F | defaults: 11669136
		int __fastcall addKillExp(/*Experience*/); // address: 0x424D5B
	};
	static_assert(sizeof(mm8::GameParty) == 0xBB2EF8, "Invalid \"mm8::GameParty\" structure size");
	static_assert(offsetof(mm8::GameParty, currentPlayer) == 5346128);
	static_assert(offsetof(mm8::GameParty, lastRegenerationTime) == 11669188);
	static_assert(offsetof(mm8::GameParty, monsHuntReset) == 11669196);
	static_assert(offsetof(mm8::GameParty, nextBountyHunt) == 11669196);
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
		int32_t left; // 0x0 (0 decimal)
		int32_t top; // 0x4 (4 decimal)
		int32_t width; // 0x8 (8 decimal)
		int32_t height; // 0xC (12 decimal)
		int32_t right; // 0x10 (16 decimal)
		int32_t bottom; // 0x14 (20 decimal)
		int32_t shape; // 0x18 (24 decimal)
		int32_t hintAction; // 0x1C (28 decimal)
		int32_t actionType; // 0x20 (32 decimal)
		int32_t actionParam; // 0x24 (36 decimal)
		int32_t actionParam2; // 0x28 (40 decimal)
		uint32_t pressed; // 4-byte boolean | 0x2C (44 decimal)
		uint32_t prevItemPtr; // 0x30 (48 decimal)
		uint32_t nextItemPtr; // 0x34 (52 decimal)
		union
		{
			mm8::Dlg* parent; // 0x38 (56 decimal)
			uint32_t parentPtr; // 0x38 (56 decimal)
		};
		std::array<int32_t, 5> sprites; // size field offset is 0x50 | 0x3C (60 decimal)
		uint32_t sprites_size; // 0x50 (80 decimal)
		uint8_t shortCut; // 0x54 (84 decimal)
		std::array<char, 103> hint; // fixed size string, requires null terminator | 0x55 (85 decimal)
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