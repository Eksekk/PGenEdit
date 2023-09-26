#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct MapExtra // size: 0x38
	{
		int64_t lastVisitTime; // 0x0 (0 decimal)
		std::array<char, 12> skyBitmap; // fixed size string, requires null terminator | 0x8 (8 decimal)
		union
		{
			uint32_t dayBits; // 0x14 (20 decimal)
			struct
			{
				bool foggy : 1; // 0x14 (20 decimal), bit index 7
			};
		};
		int32_t fogRange1; // 0x18 (24 decimal)
		int32_t fogRange2; // 0x1C (28 decimal)
		SKIP(8);
		uint32_t lastWeeklyTimer; // 0x28 (40 decimal)
		uint32_t lastMonthlyTimer; // 0x2C (44 decimal)
		uint32_t lastYearlyTimer; // 0x30 (48 decimal)
		uint32_t lastDailyTimer; // 0x34 (52 decimal)
	};
	static_assert(sizeof(mm6::MapExtra) == 0x38, "Invalid \"mm6::MapExtra\" structure size");
	static_assert(offsetof(mm6::MapExtra, skyBitmap) == 8);
	static_assert(offsetof(mm6::MapExtra, dayBits) == 20);
	static_assert(offsetof(mm6::MapExtra, fogRange1) == 24);
	static_assert(offsetof(mm6::MapExtra, fogRange2) == 28);
	static_assert(offsetof(mm6::MapExtra, lastWeeklyTimer) == 40);
	static_assert(offsetof(mm6::MapExtra, lastMonthlyTimer) == 44);
	static_assert(offsetof(mm6::MapExtra, lastYearlyTimer) == 48);
	static_assert(offsetof(mm6::MapExtra, lastDailyTimer) == 52);



	struct MapObject // size: 0x64
	{
		int16_t type; // 0x0 (0 decimal) | MMExt info: look type  (see Id in dobjlist.bin)
		int16_t typeIndex; // 0x2 (2 decimal) | MMExt info: line in dobjlist.bin
		union
		{
			std::array<int32_t, 3> pos; // 0x4 (4 decimal)
			struct
			{
				int32_t x; // 0x4 (4 decimal)
				int32_t y; // 0x8 (8 decimal)
				int32_t z; // 0xC (12 decimal)
			};
		};
		union
		{
			std::array<int16_t, 3> velocity; // 0x10 (16 decimal)
			struct
			{
				int16_t velocityX; // 0x10 (16 decimal)
				int16_t velocityY; // 0x12 (18 decimal)
				int16_t velocityZ; // 0x14 (20 decimal)
			};
		};
		int16_t direction; // 0x16 (22 decimal)
		int16_t lookAngle; // 0x18 (24 decimal)
		union
		{
			uint16_t bits; // 0x1A (26 decimal)
			struct
			{
				bool visible : 1; // 0x1A (26 decimal), bit index 7
				bool temporary : 1; // 0x1A (26 decimal), bit index 6
				bool haltTurnBased : 1; // 0x1A (26 decimal), bit index 5
				bool droppedByPlayer : 1; // 0x1A (26 decimal), bit index 4
				bool ignoreRange : 1; // 0x1A (26 decimal), bit index 3
				bool noZBuffer : 1; // 0x1A (26 decimal), bit index 2
				bool skipAFrame : 1; // 0x1A (26 decimal), bit index 1
				bool attachToHead : 1; // 0x1A (26 decimal), bit index 0
				bool missile : 1; // 0x1B (27 decimal), bit index 7
				bool removed : 1; // 0x1B (27 decimal), bit index 6
			};
		};
		int16_t room; // 0x1C (28 decimal)
		int16_t age; // 0x1E (30 decimal)
		int16_t maxAge; // 0x20 (32 decimal)
		int16_t lightMultiplier; // 0x22 (34 decimal)
		mm6::Item item; // 0x24 (36 decimal)
		union
		{
			int32_t spell; // 0x40 (64 decimal) | MMExt info: same as 'SpellType'
			int32_t spellType; // 0x40 (64 decimal)
		};
		int32_t spellSkill; // 0x44 (68 decimal)
		union
		{
			int32_t spellLevel; // 0x48 (72 decimal)
			int32_t spellMastery; // 0x48 (72 decimal) | MMExt info: same as 'SpellLevel'
		};
		int32_t owner; // 0x4C (76 decimal)
		int32_t target; // 0x50 (80 decimal)
		uint8_t range; // 0x54 (84 decimal) | MMExt info: Distance to target: 0 - less than 307.2, 1 - less than 1024, 2 - less then 2560, 3 - 2560 or more
		uint8_t attackType; // 0x55 (85 decimal) | MMExt info: 0 - Attack1, 1 - Attack2, 2 - Spell, 3 - Spell2, 4 - Explode
		SKIP(2);
		union
		{
			std::array<int32_t, 3> startPos; // 0x58 (88 decimal)
			struct
			{
				int32_t startX; // 0x58 (88 decimal) | MMExt info: starting x
				int32_t startY; // 0x5C (92 decimal) | MMExt info: starting y
				int32_t startZ; // 0x60 (96 decimal) | MMExt info: starting z
			};
		};
	};
	static_assert(sizeof(mm6::MapObject) == 0x64, "Invalid \"mm6::MapObject\" structure size");
	static_assert(offsetof(mm6::MapObject, typeIndex) == 2);
	static_assert(offsetof(mm6::MapObject, pos) == 4);
	static_assert(offsetof(mm6::MapObject, x) == 4);
	static_assert(offsetof(mm6::MapObject, y) == 8);
	static_assert(offsetof(mm6::MapObject, z) == 12);
	static_assert(offsetof(mm6::MapObject, velocity) == 16);
	static_assert(offsetof(mm6::MapObject, velocityX) == 16);
	static_assert(offsetof(mm6::MapObject, velocityY) == 18);
	static_assert(offsetof(mm6::MapObject, velocityZ) == 20);
	static_assert(offsetof(mm6::MapObject, direction) == 22);
	static_assert(offsetof(mm6::MapObject, lookAngle) == 24);
	static_assert(offsetof(mm6::MapObject, bits) == 26);
	static_assert(offsetof(mm6::MapObject, room) == 28);
	static_assert(offsetof(mm6::MapObject, age) == 30);
	static_assert(offsetof(mm6::MapObject, maxAge) == 32);
	static_assert(offsetof(mm6::MapObject, lightMultiplier) == 34);
	static_assert(offsetof(mm6::MapObject, item) == 36);
	static_assert(offsetof(mm6::MapObject, spell) == 64);
	static_assert(offsetof(mm6::MapObject, spellType) == 64);
	static_assert(offsetof(mm6::MapObject, spellSkill) == 68);
	static_assert(offsetof(mm6::MapObject, spellLevel) == 72);
	static_assert(offsetof(mm6::MapObject, spellMastery) == 72);
	static_assert(offsetof(mm6::MapObject, owner) == 76);
	static_assert(offsetof(mm6::MapObject, target) == 80);
	static_assert(offsetof(mm6::MapObject, range) == 84);
	static_assert(offsetof(mm6::MapObject, attackType) == 85);
	static_assert(offsetof(mm6::MapObject, startPos) == 88);
	static_assert(offsetof(mm6::MapObject, startX) == 88);
	static_assert(offsetof(mm6::MapObject, startY) == 92);
	static_assert(offsetof(mm6::MapObject, startZ) == 96);



	struct GameMap // size: 0x6A5F5C
	{
		SKIP(5698680);
		std::array<mm6::MapMonster, 500> monsters; // size field offset is 0x5B22F8 | 0x56F478 (5698680 decimal)
		std::array<int32_t, 10> soundSprites; // size field offset is 0x5C9AD0 | 0x5B22C8 (5972680 decimal)
		SKIP(8);
		uint32_t monsters_size; // 0x5B22F8 (5972728 decimal)
		std::array<uint8_t, 200> vars; // 0x5B22FC (5972732 decimal) | MMExt info: Variables for barrels/contests/etc events start at 75
		uint32_t sprites_size; // 0x5B23C4 (5972932 decimal)
		std::array<mm6::MapSprite, 3000> sprites; // size field offset is 0x5B23C4 | 0x5B23C8 (5972936 decimal)
		SKIP(12008);
		uint32_t soundSprites_size; // 0x5C9AD0 (6068944 decimal)
		SKIP(4);
		std::array<mm6::MapObject, 1000> objects; // size field offset is 0x5E2180 | 0x5C9AD8 (6068952 decimal) | MMExt info: Items, spells effects
		SKIP(8);
		uint32_t objects_size; // 0x5E2180 (6168960 decimal)
		uint32_t chests_size; // 0x5E2184 (6168964 decimal)
		SKIP(1016);
		std::array<mm6::MapChest, 20> chests; // size field offset is 0x5E2184 | 0x5E2580 (6169984 decimal)
		SKIP(3744);
		mm6::BlvHeader indoorHeader; // 0x5F7C90 (6257808 decimal)
		uint32_t vertexes_size; // 0x5F7D18 (6257944 decimal)
		mm6::MapVertex* vertexes; // size field offset is 0x5F7D18 | 0x5F7D1C (6257948 decimal)
		uint32_t facets_size; // 0x5F7D20 (6257952 decimal)
		mm6::MapFacet* facets; // size field offset is 0x5F7D20 | 0x5F7D24 (6257956 decimal)
		uint32_t facetData_size; // 0x5F7D28 (6257960 decimal)
		mm6::FacetData* facetData; // size field offset is 0x5F7D28 | 0x5F7D2C (6257964 decimal)
		uint32_t rooms_size; // 0x5F7D30 (6257968 decimal)
		mm6::MapRoom* rooms; // size field offset is 0x5F7D30 | 0x5F7D34 (6257972 decimal)
		uint32_t lights_size; // 0x5F7D38 (6257976 decimal)
		mm6::MapLight* lights; // size field offset is 0x5F7D38 | 0x5F7D3C (6257980 decimal)
		uint32_t doors_size; // 0x5F7D40 (6257984 decimal)
		std::array<mm6::MapDoor, 200>* doors; // size field offset is 0x5F7D40 | 0x5F7D44 (6257988 decimal)
		uint32_t BSPNodes_size; // 0x5F7D48 (6257992 decimal)
		mm6::BSPNode* BSPNodes; // size field offset is 0x5F7D48 | 0x5F7D4C (6257996 decimal)
		mm6::MapOutlines* outlines; // 0x5F7D50 (6258000 decimal)
		SKIP(16);
		uint32_t indoorSpawns_size; // 0x5F7D64 (6258020 decimal)
		mm6::SpawnPoint* indoorSpawns; // size field offset is 0x5F7D64 | 0x5F7D68 (6258024 decimal)
		int32_t indoorRefillCount; // 0x5F7D6C (6258028 decimal)
		uint32_t indoorLastRefillDay; // 0x5F7D70 (6258032 decimal) | MMExt info: The day of refill plus 1
		union
		{
			mm6::MapExtra indoorExtra; // 0x5F7D74 (6258036 decimal)
			struct
			{
				int64_t indoorLastVisitTime; // 0x5F7D74 (6258036 decimal)
			};
		};
		std::array<uint8_t, 875> visibileOutlines; // array of abits (real index = 7 - usual) | 0x5F7DAC (6258092 decimal)
		// uint8_t* extra; // real size is 0 | Unknown type | 0x5F8117 (6258967 decimal)
		// uint8_t* lastRefillDay; // real size is 0 | Unknown type | 0x5F8117 (6258967 decimal) | MMExt info: The day of refill plus 1
		// uint8_t* lastVisitTime; // real size is 0 | Unknown type | 0x5F8117 (6258967 decimal)
		// uint8_t* refillCount; // real size is 0 | Unknown type | 0x5F8117 (6258967 decimal)
		// uint8_t* spawns; // real size is 0 | Unknown type | 0x5F8117 (6258967 decimal)
		SKIP(100005);
		std::array<uint8_t, 20> name; // Unknown type | 0x6107BC (6358972 decimal)
		SKIP(4);
		uint32_t indoorOrOutdoor; // 0x6107D4 (6358996 decimal)
		SKIP(102352);
		union
		{
			mm6::OdmHeader outdoorHeader; // 0x6297A8 (6461352 decimal)
			struct
			{
				SKIP(160);
				std::array<mm6::TilesetDef, 4> tilesets; // 0x629848 (6461512 decimal)
			};
		};
		uint32_t models_size; // 0x629858 (6461528 decimal)
		std::array<std::array<uint8_t, 128>, 128>* heightMap; // 0x62985C (6461532 decimal)
		std::array<std::array<uint8_t, 128>, 128>* tileMap; // 0x629860 (6461536 decimal)
		std::array<std::array<uint8_t, 128>, 128>* unknownMap; // 0x629864 (6461540 decimal)
		SKIP(24);
		mm6::MapModel* models; // size field offset is 0x629858 | 0x629880 (6461568 decimal)
		uint32_t IDList_size; // 0x629884 (6461572 decimal)
		mm6::ObjectRef2* IDList; // size field offset is 0x629884 | 0x629888 (6461576 decimal) | MMExt info: IDs of sprites on map (in ObjectRef:structs.ObjectRef form)
		std::array<std::array<int32_t, 128>, 128>* IDOffsets; // 0x62988C (6461580 decimal)
		int32_t loadedSkyBitmap; // 0x629890 (6461584 decimal)
		SKIP(394196);
		uint32_t outdoorSpawns_size; // 0x689C68 (6855784 decimal)
		mm6::SpawnPoint* outdoorSpawns; // size field offset is 0x689C68 | 0x689C6C (6855788 decimal)
		int32_t outdoorRefillCount; // 0x689C70 (6855792 decimal)
		uint32_t outdoorLastRefillDay; // 0x689C74 (6855796 decimal) | MMExt info: The day of refill plus 1
		union
		{
			mm6::MapExtra outdoorExtra; // 0x689C78 (6855800 decimal)
			struct
			{
				int64_t outdoorLastVisitTime; // 0x689C78 (6855800 decimal)
			};
		};
		std::array<std::array<uint8_t, 11>, 88> visibleMap1; // array of abits (real index = 7 - usual) | 0x689CB0 (6855856 decimal)
		std::array<std::array<uint8_t, 11>, 88> visibleMap2; // array of abits (real index = 7 - usual) | 0x68A078 (6856824 decimal)
		SKIP(113432);
		int32_t mapStatsIndex; // 0x6A5F58 (6971224 decimal)
		int __thiscall removeObject(/*Index*/); // address: 0x42ABD0
	};
	static_assert(sizeof(mm6::GameMap) == 0x6A5F5C, "Invalid \"mm6::GameMap\" structure size");
	static_assert(offsetof(mm6::GameMap, monsters) == 5698680);
	static_assert(offsetof(mm6::GameMap, soundSprites) == 5972680);
	static_assert(offsetof(mm6::GameMap, monsters_size) == 5972728);
	static_assert(offsetof(mm6::GameMap, vars) == 5972732);
	static_assert(offsetof(mm6::GameMap, sprites_size) == 5972932);
	static_assert(offsetof(mm6::GameMap, sprites) == 5972936);
	static_assert(offsetof(mm6::GameMap, soundSprites_size) == 6068944);
	static_assert(offsetof(mm6::GameMap, objects) == 6068952);
	static_assert(offsetof(mm6::GameMap, objects_size) == 6168960);
	static_assert(offsetof(mm6::GameMap, chests_size) == 6168964);
	static_assert(offsetof(mm6::GameMap, chests) == 6169984);
	static_assert(offsetof(mm6::GameMap, indoorHeader) == 6257808);
	static_assert(offsetof(mm6::GameMap, vertexes_size) == 6257944);
	static_assert(offsetof(mm6::GameMap, vertexes) == 6257948);
	static_assert(offsetof(mm6::GameMap, facets_size) == 6257952);
	static_assert(offsetof(mm6::GameMap, facets) == 6257956);
	static_assert(offsetof(mm6::GameMap, facetData_size) == 6257960);
	static_assert(offsetof(mm6::GameMap, facetData) == 6257964);
	static_assert(offsetof(mm6::GameMap, rooms_size) == 6257968);
	static_assert(offsetof(mm6::GameMap, rooms) == 6257972);
	static_assert(offsetof(mm6::GameMap, lights_size) == 6257976);
	static_assert(offsetof(mm6::GameMap, lights) == 6257980);
	static_assert(offsetof(mm6::GameMap, doors_size) == 6257984);
	static_assert(offsetof(mm6::GameMap, doors) == 6257988);
	static_assert(offsetof(mm6::GameMap, BSPNodes_size) == 6257992);
	static_assert(offsetof(mm6::GameMap, BSPNodes) == 6257996);
	static_assert(offsetof(mm6::GameMap, outlines) == 6258000);
	static_assert(offsetof(mm6::GameMap, indoorSpawns_size) == 6258020);
	static_assert(offsetof(mm6::GameMap, indoorSpawns) == 6258024);
	static_assert(offsetof(mm6::GameMap, indoorRefillCount) == 6258028);
	static_assert(offsetof(mm6::GameMap, indoorLastRefillDay) == 6258032);
	static_assert(offsetof(mm6::GameMap, indoorExtra) == 6258036);
	static_assert(offsetof(mm6::GameMap, indoorLastVisitTime) == 6258036);
	static_assert(offsetof(mm6::GameMap, name) == 6358972);
	static_assert(offsetof(mm6::GameMap, indoorOrOutdoor) == 6358996);
	static_assert(offsetof(mm6::GameMap, outdoorHeader) == 6461352);
	static_assert(offsetof(mm6::GameMap, tilesets) == 6461512);
	static_assert(offsetof(mm6::GameMap, models_size) == 6461528);
	static_assert(offsetof(mm6::GameMap, heightMap) == 6461532);
	static_assert(offsetof(mm6::GameMap, tileMap) == 6461536);
	static_assert(offsetof(mm6::GameMap, unknownMap) == 6461540);
	static_assert(offsetof(mm6::GameMap, models) == 6461568);
	static_assert(offsetof(mm6::GameMap, IDList_size) == 6461572);
	static_assert(offsetof(mm6::GameMap, IDList) == 6461576);
	static_assert(offsetof(mm6::GameMap, IDOffsets) == 6461580);
	static_assert(offsetof(mm6::GameMap, loadedSkyBitmap) == 6461584);
	static_assert(offsetof(mm6::GameMap, outdoorSpawns_size) == 6855784);
	static_assert(offsetof(mm6::GameMap, outdoorSpawns) == 6855788);
	static_assert(offsetof(mm6::GameMap, outdoorRefillCount) == 6855792);
	static_assert(offsetof(mm6::GameMap, outdoorLastRefillDay) == 6855796);
	static_assert(offsetof(mm6::GameMap, outdoorExtra) == 6855800);
	static_assert(offsetof(mm6::GameMap, outdoorLastVisitTime) == 6855800);
	static_assert(offsetof(mm6::GameMap, mapStatsIndex) == 6971224);
}
namespace mm7
{
	struct MapExtra // size: 0x38
	{
		int64_t lastVisitTime; // 0x0 (0 decimal)
		std::array<char, 12> skyBitmap; // fixed size string, requires null terminator | 0x8 (8 decimal)
		union
		{
			uint32_t dayBits; // 0x14 (20 decimal)
			struct
			{
				bool foggy : 1; // 0x14 (20 decimal), bit index 7
			};
		};
		int32_t fogRange1; // 0x18 (24 decimal)
		int32_t fogRange2; // 0x1C (28 decimal)
		SKIP(8);
		uint32_t lastWeeklyTimer; // 0x28 (40 decimal)
		uint32_t lastMonthlyTimer; // 0x2C (44 decimal)
		uint32_t lastYearlyTimer; // 0x30 (48 decimal)
		uint32_t lastDailyTimer; // 0x34 (52 decimal)
	};
	static_assert(sizeof(mm7::MapExtra) == 0x38, "Invalid \"mm7::MapExtra\" structure size");
	static_assert(offsetof(mm7::MapExtra, skyBitmap) == 8);
	static_assert(offsetof(mm7::MapExtra, dayBits) == 20);
	static_assert(offsetof(mm7::MapExtra, fogRange1) == 24);
	static_assert(offsetof(mm7::MapExtra, fogRange2) == 28);
	static_assert(offsetof(mm7::MapExtra, lastWeeklyTimer) == 40);
	static_assert(offsetof(mm7::MapExtra, lastMonthlyTimer) == 44);
	static_assert(offsetof(mm7::MapExtra, lastYearlyTimer) == 48);
	static_assert(offsetof(mm7::MapExtra, lastDailyTimer) == 52);



	struct MapObject // size: 0x70
	{
		int16_t type; // 0x0 (0 decimal) | MMExt info: look type  (see Id in dobjlist.bin)
		int16_t typeIndex; // 0x2 (2 decimal) | MMExt info: line in dobjlist.bin
		union
		{
			std::array<int32_t, 3> pos; // 0x4 (4 decimal)
			struct
			{
				int32_t x; // 0x4 (4 decimal)
				int32_t y; // 0x8 (8 decimal)
				int32_t z; // 0xC (12 decimal)
			};
		};
		union
		{
			std::array<int16_t, 3> velocity; // 0x10 (16 decimal)
			struct
			{
				int16_t velocityX; // 0x10 (16 decimal)
				int16_t velocityY; // 0x12 (18 decimal)
				int16_t velocityZ; // 0x14 (20 decimal)
			};
		};
		int16_t direction; // 0x16 (22 decimal)
		int16_t lookAngle; // 0x18 (24 decimal)
		union
		{
			uint16_t bits; // 0x1A (26 decimal)
			struct
			{
				bool visible : 1; // 0x1A (26 decimal), bit index 7
				bool temporary : 1; // 0x1A (26 decimal), bit index 6
				bool haltTurnBased : 1; // 0x1A (26 decimal), bit index 5
				bool droppedByPlayer : 1; // 0x1A (26 decimal), bit index 4
				bool ignoreRange : 1; // 0x1A (26 decimal), bit index 3
				bool noZBuffer : 1; // 0x1A (26 decimal), bit index 2
				bool skipAFrame : 1; // 0x1A (26 decimal), bit index 1
				bool attachToHead : 1; // 0x1A (26 decimal), bit index 0
				bool missile : 1; // 0x1B (27 decimal), bit index 7
				bool removed : 1; // 0x1B (27 decimal), bit index 6
			};
		};
		int16_t room; // 0x1C (28 decimal)
		int16_t age; // 0x1E (30 decimal)
		int16_t maxAge; // 0x20 (32 decimal)
		int16_t lightMultiplier; // 0x22 (34 decimal)
		mm7::Item item; // 0x24 (36 decimal)
		union
		{
			int32_t spell; // 0x48 (72 decimal) | MMExt info: same as 'SpellType'
			int32_t spellType; // 0x48 (72 decimal)
		};
		int32_t spellSkill; // 0x4C (76 decimal)
		union
		{
			int32_t spellLevel; // 0x50 (80 decimal)
			int32_t spellMastery; // 0x50 (80 decimal) | MMExt info: same as 'SpellLevel'
		};
		mm7::SpellEffect* spellEffect; // 0x54 (84 decimal)
		int32_t owner; // 0x58 (88 decimal)
		int32_t target; // 0x5C (92 decimal)
		uint8_t range; // 0x60 (96 decimal) | MMExt info: Distance to target: 0 - less than 307.2, 1 - less than 1024, 2 - less then 2560, 3 - 2560 or more
		uint8_t attackType; // 0x61 (97 decimal) | MMExt info: 0 - Attack1, 1 - Attack2, 2 - Spell, 3 - Spell2, 4 - Explode
		SKIP(2);
		union
		{
			std::array<int32_t, 3> startPos; // 0x64 (100 decimal)
			struct
			{
				int32_t startX; // 0x64 (100 decimal) | MMExt info: starting x
				int32_t startY; // 0x68 (104 decimal) | MMExt info: starting y
				int32_t startZ; // 0x6C (108 decimal) | MMExt info: starting z
			};
		};
	};
	static_assert(sizeof(mm7::MapObject) == 0x70, "Invalid \"mm7::MapObject\" structure size");
	static_assert(offsetof(mm7::MapObject, typeIndex) == 2);
	static_assert(offsetof(mm7::MapObject, pos) == 4);
	static_assert(offsetof(mm7::MapObject, x) == 4);
	static_assert(offsetof(mm7::MapObject, y) == 8);
	static_assert(offsetof(mm7::MapObject, z) == 12);
	static_assert(offsetof(mm7::MapObject, velocity) == 16);
	static_assert(offsetof(mm7::MapObject, velocityX) == 16);
	static_assert(offsetof(mm7::MapObject, velocityY) == 18);
	static_assert(offsetof(mm7::MapObject, velocityZ) == 20);
	static_assert(offsetof(mm7::MapObject, direction) == 22);
	static_assert(offsetof(mm7::MapObject, lookAngle) == 24);
	static_assert(offsetof(mm7::MapObject, bits) == 26);
	static_assert(offsetof(mm7::MapObject, room) == 28);
	static_assert(offsetof(mm7::MapObject, age) == 30);
	static_assert(offsetof(mm7::MapObject, maxAge) == 32);
	static_assert(offsetof(mm7::MapObject, lightMultiplier) == 34);
	static_assert(offsetof(mm7::MapObject, item) == 36);
	static_assert(offsetof(mm7::MapObject, spell) == 72);
	static_assert(offsetof(mm7::MapObject, spellType) == 72);
	static_assert(offsetof(mm7::MapObject, spellSkill) == 76);
	static_assert(offsetof(mm7::MapObject, spellLevel) == 80);
	static_assert(offsetof(mm7::MapObject, spellMastery) == 80);
	static_assert(offsetof(mm7::MapObject, spellEffect) == 84);
	static_assert(offsetof(mm7::MapObject, owner) == 88);
	static_assert(offsetof(mm7::MapObject, target) == 92);
	static_assert(offsetof(mm7::MapObject, range) == 96);
	static_assert(offsetof(mm7::MapObject, attackType) == 97);
	static_assert(offsetof(mm7::MapObject, startPos) == 100);
	static_assert(offsetof(mm7::MapObject, startX) == 100);
	static_assert(offsetof(mm7::MapObject, startY) == 104);
	static_assert(offsetof(mm7::MapObject, startZ) == 108);



	struct GameMap // size: 0x76D398
	{
		SKIP(5342836);
		std::array<mm7::BaseLight, 400> spriteLights; // size field offset is 0x519934 | 0x518674 (5342836 decimal)
		uint32_t spriteLights_size; // 0x519934 (5347636 decimal)
		SKIP(831960);
		std::array<uint8_t, 200> vars; // 0x5E4B10 (6179600 decimal) | MMExt info: Variables for barrels/contests/etc events start at 75
		SKIP(1016);
		std::array<mm7::MapChest, 20> chests; // size field offset is 0x5FEFC0 | 0x5E4FD0 (6180816 decimal)
		uint32_t chests_size; // 0x5FEFC0 (6287296 decimal)
		SKIP(20);
		std::array<mm7::MapMonster, 500> monsters; // size field offset is 0x6650A8 | 0x5FEFD8 (6287320 decimal)
		uint32_t monsters_size; // 0x6650A8 (6705320 decimal)
		uint32_t objects_size; // 0x6650AC (6705324 decimal)
		std::array<mm7::MapObject, 1000> objects; // size field offset is 0x6650AC | 0x6650B0 (6705328 decimal) | MMExt info: Items, spells effects
		SKIP(8);
		std::array<int32_t, 10> soundSprites; // size field offset is 0x680660 | 0x680638 (6817336 decimal)
		uint32_t soundSprites_size; // 0x680660 (6817376 decimal)
		SKIP(12012);
		std::array<mm7::MapSprite, 3000> sprites; // size field offset is 0x69AC50 | 0x683550 (6829392 decimal)
		uint32_t sprites_size; // 0x69AC50 (6925392 decimal)
		SKIP(24604);
		union
		{
			mm7::OdmHeader outdoorHeader; // 0x6A0C70 (6950000 decimal)
			struct
			{
				SKIP(160);
				std::array<mm7::TilesetDef, 4> tilesets; // 0x6A0D10 (6950160 decimal)
			};
		};
		uint32_t models_size; // 0x6A0D20 (6950176 decimal)
		std::array<std::array<uint8_t, 128>, 128>* heightMap; // 0x6A0D24 (6950180 decimal)
		std::array<std::array<uint8_t, 128>, 128>* tileMap; // 0x6A0D28 (6950184 decimal)
		std::array<std::array<uint8_t, 128>, 128>* unknownMap; // 0x6A0D2C (6950188 decimal)
		SKIP(24);
		mm7::MapModel* models; // size field offset is 0x6A0D20 | 0x6A0D48 (6950216 decimal)
		uint32_t IDList_size; // 0x6A0D4C (6950220 decimal)
		mm7::ObjectRef2* IDList; // size field offset is 0x6A0D4C | 0x6A0D50 (6950224 decimal) | MMExt info: IDs of sprites on map (in ObjectRef:structs.ObjectRef form)
		std::array<std::array<int32_t, 128>, 128>* IDOffsets; // 0x6A0D54 (6950228 decimal)
		int32_t loadedSkyBitmap; // 0x6A0D58 (6950232 decimal)
		SKIP(980);
		uint32_t outdoorSpawns_size; // 0x6A1130 (6951216 decimal)
		mm7::SpawnPoint* outdoorSpawns; // size field offset is 0x6A1130 | 0x6A1134 (6951220 decimal)
		int32_t outdoorRefillCount; // 0x6A1138 (6951224 decimal)
		uint32_t outdoorLastRefillDay; // 0x6A113C (6951228 decimal) | MMExt info: The day of refill plus 1
		int32_t outdoorReputation; // 0x6A1140 (6951232 decimal)
		int32_t outdoorAlertState; // 0x6A1144 (6951236 decimal)
		int32_t outdoorSanityFacetsCount; // 0x6A1148 (6951240 decimal)
		int32_t outdoorSanitySpritesCount; // 0x6A114C (6951244 decimal)
		int32_t sanityModelsCount; // 0x6A1150 (6951248 decimal)
		SKIP(12);
		union
		{
			mm7::MapExtra outdoorExtra; // 0x6A1160 (6951264 decimal)
			struct
			{
				int64_t outdoorLastVisitTime; // 0x6A1160 (6951264 decimal)
			};
		};
		std::array<std::array<uint8_t, 11>, 88> visibleMap1; // array of abits (real index = 7 - usual) | 0x6A1198 (6951320 decimal)
		std::array<std::array<uint8_t, 11>, 88> visibleMap2; // array of abits (real index = 7 - usual) | 0x6A1560 (6952288 decimal)
		SKIP(116372);
		int32_t mapStatsIndex; // 0x6BDFBC (7069628 decimal)
		SKIP(516);
		std::array<uint8_t, 20> name; // Unknown type | 0x6BE1C4 (7070148 decimal)
		SKIP(8);
		uint32_t indoorOrOutdoor; // 0x6BE1E0 (7070176 decimal)
		SKIP(97);
		bool noNPC; // 0x6BE245 (7070277 decimal)
		SKIP(490);
		mm7::BlvHeader indoorHeader; // 0x6BE430 (7070768 decimal)
		uint32_t vertexes_size; // 0x6BE4B8 (7070904 decimal)
		mm7::MapVertex* vertexes; // size field offset is 0x6BE4B8 | 0x6BE4BC (7070908 decimal)
		uint32_t facets_size; // 0x6BE4C0 (7070912 decimal)
		mm7::MapFacet* facets; // size field offset is 0x6BE4C0 | 0x6BE4C4 (7070916 decimal)
		uint32_t facetData_size; // 0x6BE4C8 (7070920 decimal)
		mm7::FacetData* facetData; // size field offset is 0x6BE4C8 | 0x6BE4CC (7070924 decimal)
		uint32_t rooms_size; // 0x6BE4D0 (7070928 decimal)
		mm7::MapRoom* rooms; // size field offset is 0x6BE4D0 | 0x6BE4D4 (7070932 decimal)
		uint32_t lights_size; // 0x6BE4D8 (7070936 decimal)
		mm7::MapLight* lights; // size field offset is 0x6BE4D8 | 0x6BE4DC (7070940 decimal)
		uint32_t doors_size; // 0x6BE4E0 (7070944 decimal)
		std::array<mm7::MapDoor, 200>* doors; // size field offset is 0x6BE4E0 | 0x6BE4E4 (7070948 decimal)
		uint32_t BSPNodes_size; // 0x6BE4E8 (7070952 decimal)
		mm7::BSPNode* BSPNodes; // size field offset is 0x6BE4E8 | 0x6BE4EC (7070956 decimal)
		mm7::MapOutlines* outlines; // 0x6BE4F0 (7070960 decimal)
		SKIP(16);
		uint32_t indoorSpawns_size; // 0x6BE504 (7070980 decimal)
		mm7::SpawnPoint* indoorSpawns; // size field offset is 0x6BE504 | 0x6BE508 (7070984 decimal)
		int32_t indoorRefillCount; // 0x6BE50C (7070988 decimal)
		uint32_t indoorLastRefillDay; // 0x6BE510 (7070992 decimal) | MMExt info: The day of refill plus 1
		int32_t indoorReputation; // 0x6BE514 (7070996 decimal)
		int32_t indoorAlertState; // 0x6BE518 (7071000 decimal)
		int32_t indoorSanityFacetsCount; // 0x6BE51C (7071004 decimal)
		int32_t indoorSanitySpritesCount; // 0x6BE520 (7071008 decimal)
		std::array<uint8_t, 4> sanityDoorDataSize; // Unknown type | 0x6BE524 (7071012 decimal) | MMExt info: Added in MMExtension. Instead of being checked against, it actually replaces #Map.IndoorHeader.DoorDataSize:structs.BlvHeader.DoorDataSize# when loading the .dlv, if it's non-zero.
		// uint8_t* alertState; // real size is 0 | Unknown type | 0x6BE528 (7071016 decimal)
		// uint8_t* extra; // real size is 0 | Unknown type | 0x6BE528 (7071016 decimal)
		// uint8_t* lastRefillDay; // real size is 0 | Unknown type | 0x6BE528 (7071016 decimal) | MMExt info: The day of refill plus 1
		// uint8_t* lastVisitTime; // real size is 0 | Unknown type | 0x6BE528 (7071016 decimal)
		// uint8_t* refillCount; // real size is 0 | Unknown type | 0x6BE528 (7071016 decimal)
		// uint8_t* reputation; // real size is 0 | Unknown type | 0x6BE528 (7071016 decimal)
		// uint8_t* sanityFacetsCount; // real size is 0 | Unknown type | 0x6BE528 (7071016 decimal)
		// uint8_t* sanitySpritesCount; // real size is 0 | Unknown type | 0x6BE528 (7071016 decimal)
		// uint8_t* spawns; // real size is 0 | Unknown type | 0x6BE528 (7071016 decimal)
		SKIP(12);
		union
		{
			mm7::MapExtra indoorExtra; // 0x6BE534 (7071028 decimal)
			struct
			{
				int64_t indoorLastVisitTime; // 0x6BE534 (7071028 decimal)
			};
		};
		std::array<uint8_t, 875> visibileOutlines; // array of abits (real index = 7 - usual) | 0x6BE56C (7071084 decimal)
		SKIP(518841);
		uint32_t terNorm_size; // 0x73D390 (7590800 decimal)
		std::array<std::array<std::array<float, 2>, 128>, 128> terNormDist; // 0x73D394 (7590804 decimal)
		std::array<std::array<std::array<int16_t, 2>, 128>, 128> terNormId; // 0x75D394 (7721876 decimal)
		mm7::FloatVector* terNorm; // size field offset is 0x73D390 | 0x76D394 (7787412 decimal)
		int __thiscall removeObject(/*Index*/); // address: 0x42F90F
	};
	static_assert(sizeof(mm7::GameMap) == 0x76D398, "Invalid \"mm7::GameMap\" structure size");
	static_assert(offsetof(mm7::GameMap, spriteLights) == 5342836);
	static_assert(offsetof(mm7::GameMap, spriteLights_size) == 5347636);
	static_assert(offsetof(mm7::GameMap, vars) == 6179600);
	static_assert(offsetof(mm7::GameMap, chests) == 6180816);
	static_assert(offsetof(mm7::GameMap, chests_size) == 6287296);
	static_assert(offsetof(mm7::GameMap, monsters) == 6287320);
	static_assert(offsetof(mm7::GameMap, monsters_size) == 6705320);
	static_assert(offsetof(mm7::GameMap, objects_size) == 6705324);
	static_assert(offsetof(mm7::GameMap, objects) == 6705328);
	static_assert(offsetof(mm7::GameMap, soundSprites) == 6817336);
	static_assert(offsetof(mm7::GameMap, soundSprites_size) == 6817376);
	static_assert(offsetof(mm7::GameMap, sprites) == 6829392);
	static_assert(offsetof(mm7::GameMap, sprites_size) == 6925392);
	static_assert(offsetof(mm7::GameMap, outdoorHeader) == 6950000);
	static_assert(offsetof(mm7::GameMap, tilesets) == 6950160);
	static_assert(offsetof(mm7::GameMap, models_size) == 6950176);
	static_assert(offsetof(mm7::GameMap, heightMap) == 6950180);
	static_assert(offsetof(mm7::GameMap, tileMap) == 6950184);
	static_assert(offsetof(mm7::GameMap, unknownMap) == 6950188);
	static_assert(offsetof(mm7::GameMap, models) == 6950216);
	static_assert(offsetof(mm7::GameMap, IDList_size) == 6950220);
	static_assert(offsetof(mm7::GameMap, IDList) == 6950224);
	static_assert(offsetof(mm7::GameMap, IDOffsets) == 6950228);
	static_assert(offsetof(mm7::GameMap, loadedSkyBitmap) == 6950232);
	static_assert(offsetof(mm7::GameMap, outdoorSpawns_size) == 6951216);
	static_assert(offsetof(mm7::GameMap, outdoorSpawns) == 6951220);
	static_assert(offsetof(mm7::GameMap, outdoorRefillCount) == 6951224);
	static_assert(offsetof(mm7::GameMap, outdoorLastRefillDay) == 6951228);
	static_assert(offsetof(mm7::GameMap, outdoorReputation) == 6951232);
	static_assert(offsetof(mm7::GameMap, outdoorAlertState) == 6951236);
	static_assert(offsetof(mm7::GameMap, outdoorSanityFacetsCount) == 6951240);
	static_assert(offsetof(mm7::GameMap, outdoorSanitySpritesCount) == 6951244);
	static_assert(offsetof(mm7::GameMap, sanityModelsCount) == 6951248);
	static_assert(offsetof(mm7::GameMap, outdoorExtra) == 6951264);
	static_assert(offsetof(mm7::GameMap, outdoorLastVisitTime) == 6951264);
	static_assert(offsetof(mm7::GameMap, mapStatsIndex) == 7069628);
	static_assert(offsetof(mm7::GameMap, name) == 7070148);
	static_assert(offsetof(mm7::GameMap, indoorOrOutdoor) == 7070176);
	static_assert(offsetof(mm7::GameMap, noNPC) == 7070277);
	static_assert(offsetof(mm7::GameMap, indoorHeader) == 7070768);
	static_assert(offsetof(mm7::GameMap, vertexes_size) == 7070904);
	static_assert(offsetof(mm7::GameMap, vertexes) == 7070908);
	static_assert(offsetof(mm7::GameMap, facets_size) == 7070912);
	static_assert(offsetof(mm7::GameMap, facets) == 7070916);
	static_assert(offsetof(mm7::GameMap, facetData_size) == 7070920);
	static_assert(offsetof(mm7::GameMap, facetData) == 7070924);
	static_assert(offsetof(mm7::GameMap, rooms_size) == 7070928);
	static_assert(offsetof(mm7::GameMap, rooms) == 7070932);
	static_assert(offsetof(mm7::GameMap, lights_size) == 7070936);
	static_assert(offsetof(mm7::GameMap, lights) == 7070940);
	static_assert(offsetof(mm7::GameMap, doors_size) == 7070944);
	static_assert(offsetof(mm7::GameMap, doors) == 7070948);
	static_assert(offsetof(mm7::GameMap, BSPNodes_size) == 7070952);
	static_assert(offsetof(mm7::GameMap, BSPNodes) == 7070956);
	static_assert(offsetof(mm7::GameMap, outlines) == 7070960);
	static_assert(offsetof(mm7::GameMap, indoorSpawns_size) == 7070980);
	static_assert(offsetof(mm7::GameMap, indoorSpawns) == 7070984);
	static_assert(offsetof(mm7::GameMap, indoorRefillCount) == 7070988);
	static_assert(offsetof(mm7::GameMap, indoorLastRefillDay) == 7070992);
	static_assert(offsetof(mm7::GameMap, indoorReputation) == 7070996);
	static_assert(offsetof(mm7::GameMap, indoorAlertState) == 7071000);
	static_assert(offsetof(mm7::GameMap, indoorSanityFacetsCount) == 7071004);
	static_assert(offsetof(mm7::GameMap, indoorSanitySpritesCount) == 7071008);
	static_assert(offsetof(mm7::GameMap, sanityDoorDataSize) == 7071012);
	static_assert(offsetof(mm7::GameMap, indoorExtra) == 7071028);
	static_assert(offsetof(mm7::GameMap, indoorLastVisitTime) == 7071028);
	static_assert(offsetof(mm7::GameMap, terNorm_size) == 7590800);
	static_assert(offsetof(mm7::GameMap, terNormDist) == 7590804);
	static_assert(offsetof(mm7::GameMap, terNormId) == 7721876);
	static_assert(offsetof(mm7::GameMap, terNorm) == 7787412);
}
namespace mm8
{
	struct MapExtra // size: 0x38
	{
		int64_t lastVisitTime; // 0x0 (0 decimal)
		std::array<char, 12> skyBitmap; // fixed size string, doesn't require null terminator | 0x8 (8 decimal)
		union
		{
			uint32_t dayBits; // 0x14 (20 decimal)
			struct
			{
				bool foggy : 1; // 0x14 (20 decimal), bit index 7
			};
		};
		int32_t fogRange1; // 0x18 (24 decimal)
		int32_t fogRange2; // 0x1C (28 decimal)
		union
		{
			uint32_t bits; // 0x20 (32 decimal)
			struct
			{
				bool raining : 1; // 0x20 (32 decimal), bit index 7
				bool snowing : 1; // 0x20 (32 decimal), bit index 6
				bool underwater : 1; // 0x20 (32 decimal), bit index 5 | MMExt info: elemw.odm
				bool noTerrain : 1; // 0x20 (32 decimal), bit index 4 | MMExt info: elema.odm
				bool alwaysDark : 1; // 0x20 (32 decimal), bit index 3
				bool alwaysLight : 1; // 0x21 (33 decimal), bit index 2 | MMExt info: elema.odm
				bool alwaysFoggy : 1; // 0x21 (33 decimal), bit index 1 | MMExt info: elemf.odm, elemw.odm
				bool redFog : 1; // 0x21 (33 decimal), bit index 0 | MMExt info: elemf.odm
			};
		};
		int32_t ceiling; // 0x24 (36 decimal)
		uint32_t lastWeeklyTimer; // 0x28 (40 decimal)
		uint32_t lastMonthlyTimer; // 0x2C (44 decimal)
		uint32_t lastYearlyTimer; // 0x30 (48 decimal)
		uint32_t lastDailyTimer; // 0x34 (52 decimal)
	};
	static_assert(sizeof(mm8::MapExtra) == 0x38, "Invalid \"mm8::MapExtra\" structure size");
	static_assert(offsetof(mm8::MapExtra, skyBitmap) == 8);
	static_assert(offsetof(mm8::MapExtra, dayBits) == 20);
	static_assert(offsetof(mm8::MapExtra, fogRange1) == 24);
	static_assert(offsetof(mm8::MapExtra, fogRange2) == 28);
	static_assert(offsetof(mm8::MapExtra, bits) == 32);
	static_assert(offsetof(mm8::MapExtra, ceiling) == 36);
	static_assert(offsetof(mm8::MapExtra, lastWeeklyTimer) == 40);
	static_assert(offsetof(mm8::MapExtra, lastMonthlyTimer) == 44);
	static_assert(offsetof(mm8::MapExtra, lastYearlyTimer) == 48);
	static_assert(offsetof(mm8::MapExtra, lastDailyTimer) == 52);



	struct MapObject // size: 0x70
	{
		int16_t type; // 0x0 (0 decimal) | MMExt info: look type  (see Id in dobjlist.bin)
		int16_t typeIndex; // 0x2 (2 decimal) | MMExt info: line in dobjlist.bin
		union
		{
			std::array<int32_t, 3> pos; // 0x4 (4 decimal)
			struct
			{
				int32_t x; // 0x4 (4 decimal)
				int32_t y; // 0x8 (8 decimal)
				int32_t z; // 0xC (12 decimal)
			};
		};
		union
		{
			std::array<int16_t, 3> velocity; // 0x10 (16 decimal)
			struct
			{
				int16_t velocityX; // 0x10 (16 decimal)
				int16_t velocityY; // 0x12 (18 decimal)
				int16_t velocityZ; // 0x14 (20 decimal)
			};
		};
		int16_t direction; // 0x16 (22 decimal)
		int16_t lookAngle; // 0x18 (24 decimal)
		union
		{
			uint16_t bits; // 0x1A (26 decimal)
			struct
			{
				bool visible : 1; // 0x1A (26 decimal), bit index 7
				bool temporary : 1; // 0x1A (26 decimal), bit index 6
				bool haltTurnBased : 1; // 0x1A (26 decimal), bit index 5
				bool droppedByPlayer : 1; // 0x1A (26 decimal), bit index 4
				bool ignoreRange : 1; // 0x1A (26 decimal), bit index 3
				bool noZBuffer : 1; // 0x1B (27 decimal), bit index 2
				bool skipAFrame : 1; // 0x1B (27 decimal), bit index 1
				bool attachToHead : 1; // 0x1B (27 decimal), bit index 0
				bool missile : 1; // 0x1B (27 decimal), bit index 7
				bool removed : 1; // 0x1B (27 decimal), bit index 6
			};
		};
		int16_t room; // 0x1C (28 decimal)
		int16_t age; // 0x1E (30 decimal)
		int16_t maxAge; // 0x20 (32 decimal)
		int16_t lightMultiplier; // 0x22 (34 decimal)
		mm8::Item item; // 0x24 (36 decimal)
		union
		{
			int32_t spell; // 0x48 (72 decimal) | MMExt info: same as 'SpellType'
			int32_t spellType; // 0x48 (72 decimal)
		};
		int32_t spellSkill; // 0x4C (76 decimal)
		union
		{
			int32_t spellLevel; // 0x50 (80 decimal)
			int32_t spellMastery; // 0x50 (80 decimal) | MMExt info: same as 'SpellLevel'
		};
		mm8::SpellEffect* spellEffect; // 0x54 (84 decimal)
		int32_t owner; // 0x58 (88 decimal)
		int32_t target; // 0x5C (92 decimal)
		uint8_t range; // 0x60 (96 decimal) | MMExt info: Distance to target: 0 - less than 307.2, 1 - less than 1024, 2 - less then 2560, 3 - 2560 or more
		uint8_t attackType; // 0x61 (97 decimal) | MMExt info: 0 - Attack1, 1 - Attack2, 2 - Spell, 3 - Spell2, 4 - Explode
		SKIP(2);
		union
		{
			std::array<int32_t, 3> startPos; // 0x64 (100 decimal)
			struct
			{
				int32_t startX; // 0x64 (100 decimal) | MMExt info: starting x
				int32_t startY; // 0x68 (104 decimal) | MMExt info: starting y
				int32_t startZ; // 0x6C (108 decimal) | MMExt info: starting z
			};
		};
	};
	static_assert(sizeof(mm8::MapObject) == 0x70, "Invalid \"mm8::MapObject\" structure size");
	static_assert(offsetof(mm8::MapObject, typeIndex) == 2);
	static_assert(offsetof(mm8::MapObject, pos) == 4);
	static_assert(offsetof(mm8::MapObject, x) == 4);
	static_assert(offsetof(mm8::MapObject, y) == 8);
	static_assert(offsetof(mm8::MapObject, z) == 12);
	static_assert(offsetof(mm8::MapObject, velocity) == 16);
	static_assert(offsetof(mm8::MapObject, velocityX) == 16);
	static_assert(offsetof(mm8::MapObject, velocityY) == 18);
	static_assert(offsetof(mm8::MapObject, velocityZ) == 20);
	static_assert(offsetof(mm8::MapObject, direction) == 22);
	static_assert(offsetof(mm8::MapObject, lookAngle) == 24);
	static_assert(offsetof(mm8::MapObject, bits) == 26);
	static_assert(offsetof(mm8::MapObject, room) == 28);
	static_assert(offsetof(mm8::MapObject, age) == 30);
	static_assert(offsetof(mm8::MapObject, maxAge) == 32);
	static_assert(offsetof(mm8::MapObject, lightMultiplier) == 34);
	static_assert(offsetof(mm8::MapObject, item) == 36);
	static_assert(offsetof(mm8::MapObject, spell) == 72);
	static_assert(offsetof(mm8::MapObject, spellType) == 72);
	static_assert(offsetof(mm8::MapObject, spellSkill) == 76);
	static_assert(offsetof(mm8::MapObject, spellLevel) == 80);
	static_assert(offsetof(mm8::MapObject, spellMastery) == 80);
	static_assert(offsetof(mm8::MapObject, spellEffect) == 84);
	static_assert(offsetof(mm8::MapObject, owner) == 88);
	static_assert(offsetof(mm8::MapObject, target) == 92);
	static_assert(offsetof(mm8::MapObject, range) == 96);
	static_assert(offsetof(mm8::MapObject, attackType) == 97);
	static_assert(offsetof(mm8::MapObject, startPos) == 100);
	static_assert(offsetof(mm8::MapObject, startX) == 100);
	static_assert(offsetof(mm8::MapObject, startY) == 104);
	static_assert(offsetof(mm8::MapObject, startZ) == 108);



	struct GameMap // size: 0x7AB360
	{
		std::array<mm8::MapMonster, 1500> monsters; // size field offset is 0x692FB0 | 0x0 (0 decimal)
		SKIP(3956748);
		std::array<mm8::BaseLight, 400> spriteLights; // size field offset is 0x52B21C | 0x529F5C (5414748 decimal)
		uint32_t spriteLights_size; // 0x52B21C (5419548 decimal)
		SKIP(880216);
		std::array<uint8_t, 200> vars; // 0x602078 (6299768 decimal) | MMExt info: Variables for barrels/contests/etc events start at 75
		SKIP(1016);
		std::array<mm8::MapChest, 20> chests; // size field offset is 0x61C528 | 0x602538 (6300984 decimal)
		uint32_t chests_size; // 0x61C528 (6407464 decimal)
		SKIP(486020);
		uint32_t monsters_size; // 0x692FB0 (6893488 decimal)
		uint32_t objects_size; // 0x692FB4 (6893492 decimal)
		std::array<mm8::MapObject, 1000> objects; // size field offset is 0x692FB4 | 0x692FB8 (6893496 decimal) | MMExt info: Items, spells effects
		SKIP(8);
		std::array<int32_t, 10> soundSprites; // size field offset is 0x6AE568 | 0x6AE540 (7005504 decimal)
		uint32_t soundSprites_size; // 0x6AE568 (7005544 decimal)
		SKIP(12012);
		std::array<mm8::MapSprite, 3000> sprites; // size field offset is 0x6C8B58 | 0x6B1458 (7017560 decimal)
		uint32_t sprites_size; // 0x6C8B58 (7113560 decimal)
		SKIP(24692);
		union
		{
			mm8::OdmHeader outdoorHeader; // 0x6CEBD0 (7138256 decimal)
			struct
			{
				SKIP(95);
				uint8_t tilesetsFile; // 0x6CEC2F (7138351 decimal) | MMExt info: 0 = dtile.bin, 1 = dtile2.bin, 2 = dtile3.bin
				SKIP(64);
				std::array<mm8::TilesetDef, 4> tilesets; // 0x6CEC70 (7138416 decimal)
			};
		};
		uint32_t models_size; // 0x6CEC84 (7138436 decimal)
		std::array<std::array<uint8_t, 128>, 128>* heightMap; // 0x6CEC88 (7138440 decimal)
		std::array<std::array<uint8_t, 128>, 128>* tileMap; // 0x6CEC8C (7138444 decimal)
		union
		{
			std::array<std::array<uint8_t, 128>, 128>* unknownMap; // 0x6CEC90 (7138448 decimal)
			std::array<std::array<uint8_t, 128>, 128>* unknownMap2; // 0x6CEC90 (7138448 decimal)
		};
		SKIP(24);
		mm8::MapModel* models; // size field offset is 0x6CEC84 | 0x6CECAC (7138476 decimal)
		uint32_t IDList_size; // 0x6CECB0 (7138480 decimal)
		mm8::ObjectRef2* IDList; // size field offset is 0x6CECB0 | 0x6CECB4 (7138484 decimal) | MMExt info: IDs of sprites on map (in ObjectRef:structs.ObjectRef form)
		std::array<std::array<int32_t, 128>, 128>* IDOffsets; // 0x6CECB8 (7138488 decimal)
		int32_t loadedSkyBitmap; // 0x6CECBC (7138492 decimal)
		SKIP(980);
		uint32_t outdoorSpawns_size; // 0x6CF094 (7139476 decimal)
		mm8::SpawnPoint* outdoorSpawns; // size field offset is 0x6CF094 | 0x6CF098 (7139480 decimal)
		int32_t outdoorRefillCount; // 0x6CF09C (7139484 decimal)
		int32_t outdoorLastRefillDay; // 0x6CF0A0 (7139488 decimal) | MMExt info: First visit day
		SKIP(8);
		int32_t outdoorReputation; // 0x6CF0AC (7139500 decimal)
		SKIP(28);
		union
		{
			mm8::MapExtra outdoorExtra; // 0x6CF0CC (7139532 decimal)
			struct
			{
				int64_t outdoorLastVisitTime; // 0x6CF0CC (7139532 decimal)
			};
		};
		std::array<std::array<uint8_t, 11>, 88> visibleMap1; // array of abits (real index = 7 - usual) | 0x6CF104 (7139588 decimal)
		std::array<std::array<uint8_t, 11>, 88> visibleMap2; // array of abits (real index = 7 - usual) | 0x6CF4CC (7140556 decimal)
		std::array<mm8::MapNote, 100> notes; // 0x6CF894 (7141524 decimal)
		SKIP(114856);
		int32_t mapStatsIndex; // 0x6F30C4 (7286980 decimal)
		SKIP(2236);
		std::array<uint8_t, 20> name; // Unknown type | 0x6F3984 (7289220 decimal)
		SKIP(8);
		uint32_t indoorOrOutdoor; // 0x6F39A0 (7289248 decimal)
		SKIP(588);
		mm8::BlvHeader indoorHeader; // 0x6F3BF0 (7289840 decimal)
		uint32_t vertexes_size; // 0x6F3C78 (7289976 decimal)
		mm8::MapVertex* vertexes; // size field offset is 0x6F3C78 | 0x6F3C7C (7289980 decimal)
		uint32_t facets_size; // 0x6F3C80 (7289984 decimal)
		mm8::MapFacet* facets; // size field offset is 0x6F3C80 | 0x6F3C84 (7289988 decimal)
		uint32_t facetData_size; // 0x6F3C88 (7289992 decimal)
		mm8::FacetData* facetData; // size field offset is 0x6F3C88 | 0x6F3C8C (7289996 decimal)
		uint32_t rooms_size; // 0x6F3C90 (7290000 decimal)
		mm8::MapRoom* rooms; // size field offset is 0x6F3C90 | 0x6F3C94 (7290004 decimal)
		uint32_t lights_size; // 0x6F3C98 (7290008 decimal)
		mm8::MapLight* lights; // size field offset is 0x6F3C98 | 0x6F3C9C (7290012 decimal)
		uint32_t doors_size; // 0x6F3CA0 (7290016 decimal)
		std::array<mm8::MapDoor, 200>* doors; // size field offset is 0x6F3CA0 | 0x6F3CA4 (7290020 decimal)
		uint32_t BSPNodes_size; // 0x6F3CA8 (7290024 decimal)
		mm8::BSPNode* BSPNodes; // size field offset is 0x6F3CA8 | 0x6F3CAC (7290028 decimal)
		mm8::MapOutlines* outlines; // 0x6F3CB0 (7290032 decimal)
		SKIP(16);
		uint32_t indoorSpawns_size; // 0x6F3CC4 (7290052 decimal)
		mm8::SpawnPoint* indoorSpawns; // size field offset is 0x6F3CC4 | 0x6F3CC8 (7290056 decimal)
		int32_t indoorRefillCount; // 0x6F3CCC (7290060 decimal)
		int32_t indoorLastRefillDay; // 0x6F3CD0 (7290064 decimal)
		int32_t indoorReputation; // 0x6F3CD4 (7290068 decimal)
		// uint8_t* lastRefillDay; // real size is 0 | Unknown type | 0x6F3CD8 (7290072 decimal)
		// uint8_t* lastVisitTime; // real size is 0 | Unknown type | 0x6F3CD8 (7290072 decimal)
		// uint8_t* refillCount; // real size is 0 | Unknown type | 0x6F3CD8 (7290072 decimal)
		// uint8_t* reputation; // real size is 0 | Unknown type | 0x6F3CD8 (7290072 decimal)
		// uint8_t* spawns; // real size is 0 | Unknown type | 0x6F3CD8 (7290072 decimal)
		SKIP(28);
		union
		{
			mm8::MapExtra indoorExtra; // 0x6F3CF4 (7290100 decimal)
			struct
			{
				int64_t indoorLastVisitTime; // 0x6F3CF4 (7290100 decimal)
			};
		};
		std::array<uint8_t, 875> visibileOutlines; // array of abits (real index = 7 - usual) | 0x6F3D2C (7290156 decimal)
		SKIP(553665);
		uint32_t terNorm_size; // 0x77B358 (7844696 decimal)
		std::array<std::array<std::array<float, 2>, 128>, 128> terNormDist; // 0x77B35C (7844700 decimal)
		std::array<std::array<std::array<int16_t, 2>, 128>, 128> terNormId; // 0x79B35C (7975772 decimal)
		mm8::FloatVector* terNorm; // size field offset is 0x77B358 | 0x7AB35C (8041308 decimal)
		int __thiscall removeObject(/*Index*/); // address: 0x42E392
	};
	static_assert(sizeof(mm8::GameMap) == 0x7AB360, "Invalid \"mm8::GameMap\" structure size");
	static_assert(offsetof(mm8::GameMap, spriteLights) == 5414748);
	static_assert(offsetof(mm8::GameMap, spriteLights_size) == 5419548);
	static_assert(offsetof(mm8::GameMap, vars) == 6299768);
	static_assert(offsetof(mm8::GameMap, chests) == 6300984);
	static_assert(offsetof(mm8::GameMap, chests_size) == 6407464);
	static_assert(offsetof(mm8::GameMap, monsters_size) == 6893488);
	static_assert(offsetof(mm8::GameMap, objects_size) == 6893492);
	static_assert(offsetof(mm8::GameMap, objects) == 6893496);
	static_assert(offsetof(mm8::GameMap, soundSprites) == 7005504);
	static_assert(offsetof(mm8::GameMap, soundSprites_size) == 7005544);
	static_assert(offsetof(mm8::GameMap, sprites) == 7017560);
	static_assert(offsetof(mm8::GameMap, sprites_size) == 7113560);
	static_assert(offsetof(mm8::GameMap, outdoorHeader) == 7138256);
	static_assert(offsetof(mm8::GameMap, tilesetsFile) == 7138351);
	static_assert(offsetof(mm8::GameMap, tilesets) == 7138416);
	static_assert(offsetof(mm8::GameMap, models_size) == 7138436);
	static_assert(offsetof(mm8::GameMap, heightMap) == 7138440);
	static_assert(offsetof(mm8::GameMap, tileMap) == 7138444);
	static_assert(offsetof(mm8::GameMap, unknownMap) == 7138448);
	static_assert(offsetof(mm8::GameMap, unknownMap2) == 7138448);
	static_assert(offsetof(mm8::GameMap, models) == 7138476);
	static_assert(offsetof(mm8::GameMap, IDList_size) == 7138480);
	static_assert(offsetof(mm8::GameMap, IDList) == 7138484);
	static_assert(offsetof(mm8::GameMap, IDOffsets) == 7138488);
	static_assert(offsetof(mm8::GameMap, loadedSkyBitmap) == 7138492);
	static_assert(offsetof(mm8::GameMap, outdoorSpawns_size) == 7139476);
	static_assert(offsetof(mm8::GameMap, outdoorSpawns) == 7139480);
	static_assert(offsetof(mm8::GameMap, outdoorRefillCount) == 7139484);
	static_assert(offsetof(mm8::GameMap, outdoorLastRefillDay) == 7139488);
	static_assert(offsetof(mm8::GameMap, outdoorReputation) == 7139500);
	static_assert(offsetof(mm8::GameMap, outdoorExtra) == 7139532);
	static_assert(offsetof(mm8::GameMap, outdoorLastVisitTime) == 7139532);
	static_assert(offsetof(mm8::GameMap, notes) == 7141524);
	static_assert(offsetof(mm8::GameMap, mapStatsIndex) == 7286980);
	static_assert(offsetof(mm8::GameMap, name) == 7289220);
	static_assert(offsetof(mm8::GameMap, indoorOrOutdoor) == 7289248);
	static_assert(offsetof(mm8::GameMap, indoorHeader) == 7289840);
	static_assert(offsetof(mm8::GameMap, vertexes_size) == 7289976);
	static_assert(offsetof(mm8::GameMap, vertexes) == 7289980);
	static_assert(offsetof(mm8::GameMap, facets_size) == 7289984);
	static_assert(offsetof(mm8::GameMap, facets) == 7289988);
	static_assert(offsetof(mm8::GameMap, facetData_size) == 7289992);
	static_assert(offsetof(mm8::GameMap, facetData) == 7289996);
	static_assert(offsetof(mm8::GameMap, rooms_size) == 7290000);
	static_assert(offsetof(mm8::GameMap, rooms) == 7290004);
	static_assert(offsetof(mm8::GameMap, lights_size) == 7290008);
	static_assert(offsetof(mm8::GameMap, lights) == 7290012);
	static_assert(offsetof(mm8::GameMap, doors_size) == 7290016);
	static_assert(offsetof(mm8::GameMap, doors) == 7290020);
	static_assert(offsetof(mm8::GameMap, BSPNodes_size) == 7290024);
	static_assert(offsetof(mm8::GameMap, BSPNodes) == 7290028);
	static_assert(offsetof(mm8::GameMap, outlines) == 7290032);
	static_assert(offsetof(mm8::GameMap, indoorSpawns_size) == 7290052);
	static_assert(offsetof(mm8::GameMap, indoorSpawns) == 7290056);
	static_assert(offsetof(mm8::GameMap, indoorRefillCount) == 7290060);
	static_assert(offsetof(mm8::GameMap, indoorLastRefillDay) == 7290064);
	static_assert(offsetof(mm8::GameMap, indoorReputation) == 7290068);
	static_assert(offsetof(mm8::GameMap, indoorExtra) == 7290100);
	static_assert(offsetof(mm8::GameMap, indoorLastVisitTime) == 7290100);
	static_assert(offsetof(mm8::GameMap, terNorm_size) == 7844696);
	static_assert(offsetof(mm8::GameMap, terNormDist) == 7844700);
	static_assert(offsetof(mm8::GameMap, terNormId) == 7975772);
	static_assert(offsetof(mm8::GameMap, terNorm) == 8041308);
}

#pragma pack(pop)