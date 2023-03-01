#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct MapExtra // size: 0x38
	{
		int64_t lastVisitTime;
		std::array<char, 12> skyBitmap; // fixed size string, requires null terminator
		union
		{
			uint32_t dayBits;
			struct
			{
				bool foggy : 1;
			};
		};
		int32_t fogRange1;
		int32_t fogRange2;
		SKIP(8);
		uint32_t lastWeeklyTimer;
		uint32_t lastMonthlyTimer;
		uint32_t lastYearlyTimer;
		uint32_t lastDailyTimer;
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
		int16_t type;
		int16_t typeIndex;
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
		union
		{
			std::array<int16_t, 3> velocity;
			struct
			{
				int16_t velocityX;
				int16_t velocityY;
				int16_t velocityZ;
			};
		};
		int16_t direction;
		int16_t lookAngle;
		union
		{
			uint16_t bits;
			struct
			{
				bool visible : 1;
				bool temporary : 1;
				bool haltTurnBased : 1;
				bool droppedByPlayer : 1;
				bool ignoreRange : 1;
				bool noZBuffer : 1;
				bool skipAFrame : 1;
				bool attachToHead : 1;
				bool missile : 1;
				bool removed : 1;
			};
		};
		int16_t room;
		int16_t age;
		int16_t maxAge;
		int16_t lightMultiplier;
		mm6::Item item;
		union
		{
			int32_t spellType;
			int32_t spell;
		};
		int32_t spellSkill;
		union
		{
			int32_t spellLevel;
			int32_t spellMastery;
		};
		int32_t owner;
		int32_t target;
		uint8_t range;
		uint8_t attackType;
		SKIP(2);
		union
		{
			std::array<int32_t, 3> startPos;
			struct
			{
				int32_t startX;
				int32_t startY;
				int32_t startZ;
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
	static_assert(offsetof(mm6::MapObject, spellType) == 64);
	static_assert(offsetof(mm6::MapObject, spell) == 64);
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
		std::array<mm6::MapMonster, 500> monsters; // size field offset is 0x5B22F8
		std::array<int32_t, 10> soundSprites; // size field offset is 0x5C9AD0
		SKIP(8);
		uint32_t monsters_size;
		std::array<uint8_t, 200> vars;
		uint32_t sprites_size;
		std::array<mm6::MapSprite, 3000> sprites; // size field offset is 0x5B23C4
		SKIP(12008);
		uint32_t soundSprites_size;
		SKIP(4);
		std::array<mm6::MapObject, 1000> objects; // size field offset is 0x5E2180
		SKIP(8);
		uint32_t objects_size;
		uint32_t chests_size;
		SKIP(1016);
		std::array<mm6::MapChest, 20> chests; // size field offset is 0x5E2184
		SKIP(3744);
		mm6::BlvHeader indoorHeader;
		uint32_t vertexes_size;
		mm6::MapVertex* vertexes; // size field offset is 0x5F7D18
		uint32_t facets_size;
		mm6::MapFacet* facets; // size field offset is 0x5F7D20
		uint32_t facetData_size;
		mm6::FacetData* facetData; // size field offset is 0x5F7D28
		uint32_t rooms_size;
		mm6::MapRoom* rooms; // size field offset is 0x5F7D30
		uint32_t lights_size;
		mm6::MapLight* lights; // size field offset is 0x5F7D38
		uint32_t doors_size;
		std::array<mm6::MapDoor, 200>* doors; // size field offset is 0x5F7D40
		uint32_t BSPNodes_size;
		mm6::BSPNode* BSPNodes; // size field offset is 0x5F7D48
		mm6::MapOutlines* outlines;
		SKIP(16);
		uint32_t indoorSpawns_size;
		mm6::SpawnPoint* indoorSpawns; // size field offset is 0x5F7D64
		int32_t indoorRefillCount;
		uint32_t indoorLastRefillDay;
		union
		{
			mm6::MapExtra indoorExtra;
			struct
			{
				int64_t indoorLastVisitTime;
			};
		};
		std::array<uint8_t, 875> visibileOutlines; // array of abits (real index = 7 - usual)
		// uint8_t* lastVisitTime; // real size is 0 | Unknown type
		// uint8_t* spawns; // real size is 0 | Unknown type
		// uint8_t* reputation; // real size is 0 | Unknown type
		// uint8_t* lastRefillDay; // real size is 0 | Unknown type
		// uint8_t* refillCount; // real size is 0 | Unknown type
		SKIP(100005);
		std::array<uint8_t, 20> name; // Unknown type
		SKIP(4);
		uint32_t indoorOrOutdoor;
		SKIP(102352);
		union
		{
			mm6::OdmHeader outdoorHeader;
			struct
			{
				SKIP(160);
				std::array<mm6::TilesetDef, 4> tilesets;
			};
		};
		uint32_t models_size;
		std::array<std::array<uint8_t, 128>, 128>* heightMap;
		std::array<std::array<uint8_t, 128>, 128>* tileMap;
		std::array<std::array<uint8_t, 128>, 128>* unknownMap;
		SKIP(24);
		mm6::MapModel* models; // size field offset is 0x629858
		uint32_t IDList_size;
		mm6::ObjectRef2* IDList; // size field offset is 0x629884
		std::array<std::array<int32_t, 128>, 128>* IDOffsets;
		int32_t loadedSkyBitmap;
		SKIP(394196);
		uint32_t outdoorSpawns_size;
		mm6::SpawnPoint* outdoorSpawns; // size field offset is 0x689C68
		int32_t outdoorRefillCount;
		uint32_t outdoorLastRefillDay;
		union
		{
			mm6::MapExtra outdoorExtra;
			struct
			{
				int64_t outdoorLastVisitTime;
			};
		};
		std::array<std::array<uint8_t, 11>, 88> visibleMap1; // array of abits (real index = 7 - usual)
		std::array<std::array<uint8_t, 11>, 88> visibleMap2; // array of abits (real index = 7 - usual)
		SKIP(113432);
		int32_t mapStatsIndex;
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
	struct MapFacet // size: 0x60
	{
		union
		{
			std::array<float, 3> normalF;
			struct
			{
				float normalFX;
				float normalFY;
				float normalFZ;
			};
		};
		float normalFDistance;
		union
		{
			std::array<int32_t, 3> normal;
			struct
			{
				int32_t normalX;
				int32_t normalY;
				int32_t normalZ;
			};
		};
		int32_t normalDistance;
		int32_t ZCalc1;
		int32_t ZCalc2;
		int32_t ZCalc3;
		union
		{
			uint32_t bits;
			struct
			{
				bool isPortal : 1;
				bool isSecret : 1;
				bool scrollDown : 1;
				bool alignTop : 1;
				bool isWater : 1;
				bool scrollUp : 1;
				bool scrollLeft : 1;
				SKIPBITS(1);
				bool projectToXY : 1;
				bool projectToXZ : 1;
				bool projectToYZ : 1;
				bool scrollRight : 1;
				bool alignLeft : 1;
				bool invisible : 1;
				bool animatedTFT : 1;
				bool alignRight : 1;
				SKIPBITS(1);
				bool alignBottom : 1;
				bool moveByDoor : 1;
				SKIPBITS(1);
				bool isEventJustHint : 1;
				bool alternativeSound : 1;
				bool isSky : 1;
				bool flipU : 1;
				bool flipV : 1;
				bool triggerByClick : 1;
				bool triggerByStep : 1;
				bool triggerByMonster : 1;
				bool triggerByObject : 1;
				bool untouchable : 1;
				bool isLava : 1;
				bool hasData : 1;
			};
		};
		uint16_t* vertexIds; // AccessBeyondLength is active (???) | size field offset is 0x5D
		int16_t* XInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x5D
		int16_t* YInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x5D
		int16_t* ZInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x5D
		int16_t* UList; // AccessBeyondLength is active (???) | size field offset is 0x5D
		int16_t* VList; // AccessBeyondLength is active (???) | size field offset is 0x5D
		uint16_t dataIndex;
		int16_t bitmapId;
		int16_t room;
		int16_t roomBehind;
		int16_t minX;
		int16_t maxX;
		int16_t minY;
		int16_t maxY;
		int16_t minZ;
		int16_t maxZ;
		uint8_t polygonType;
		union
		{
			uint8_t ZInterceptDisplacement_size;
			uint8_t vertexIds_size;
			uint8_t UList_size;
			uint8_t vertexesCount;
			uint8_t YInterceptDisplacement_size;
			uint8_t XInterceptDisplacement_size;
			uint8_t VList_size;
		};
		SKIP(2);
	};
	static_assert(sizeof(mm7::MapFacet) == 0x60, "Invalid \"mm7::MapFacet\" structure size");
	static_assert(offsetof(mm7::MapFacet, normalFY) == 4);
	static_assert(offsetof(mm7::MapFacet, normalFZ) == 8);
	static_assert(offsetof(mm7::MapFacet, normalFDistance) == 12);
	static_assert(offsetof(mm7::MapFacet, normal) == 16);
	static_assert(offsetof(mm7::MapFacet, normalX) == 16);
	static_assert(offsetof(mm7::MapFacet, normalY) == 20);
	static_assert(offsetof(mm7::MapFacet, normalZ) == 24);
	static_assert(offsetof(mm7::MapFacet, normalDistance) == 28);
	static_assert(offsetof(mm7::MapFacet, ZCalc1) == 32);
	static_assert(offsetof(mm7::MapFacet, ZCalc2) == 36);
	static_assert(offsetof(mm7::MapFacet, ZCalc3) == 40);
	static_assert(offsetof(mm7::MapFacet, bits) == 44);
	static_assert(offsetof(mm7::MapFacet, vertexIds) == 48);
	static_assert(offsetof(mm7::MapFacet, XInterceptDisplacement) == 52);
	static_assert(offsetof(mm7::MapFacet, YInterceptDisplacement) == 56);
	static_assert(offsetof(mm7::MapFacet, ZInterceptDisplacement) == 60);
	static_assert(offsetof(mm7::MapFacet, UList) == 64);
	static_assert(offsetof(mm7::MapFacet, VList) == 68);
	static_assert(offsetof(mm7::MapFacet, dataIndex) == 72);
	static_assert(offsetof(mm7::MapFacet, bitmapId) == 74);
	static_assert(offsetof(mm7::MapFacet, room) == 76);
	static_assert(offsetof(mm7::MapFacet, roomBehind) == 78);
	static_assert(offsetof(mm7::MapFacet, minX) == 80);
	static_assert(offsetof(mm7::MapFacet, maxX) == 82);
	static_assert(offsetof(mm7::MapFacet, minY) == 84);
	static_assert(offsetof(mm7::MapFacet, maxY) == 86);
	static_assert(offsetof(mm7::MapFacet, minZ) == 88);
	static_assert(offsetof(mm7::MapFacet, maxZ) == 90);
	static_assert(offsetof(mm7::MapFacet, polygonType) == 92);
	static_assert(offsetof(mm7::MapFacet, ZInterceptDisplacement_size) == 93);
	static_assert(offsetof(mm7::MapFacet, vertexIds_size) == 93);
	static_assert(offsetof(mm7::MapFacet, UList_size) == 93);
	static_assert(offsetof(mm7::MapFacet, vertexesCount) == 93);
	static_assert(offsetof(mm7::MapFacet, YInterceptDisplacement_size) == 93);
	static_assert(offsetof(mm7::MapFacet, XInterceptDisplacement_size) == 93);
	static_assert(offsetof(mm7::MapFacet, VList_size) == 93);



	struct MapExtra // size: 0x38
	{
		int64_t lastVisitTime;
		std::array<char, 12> skyBitmap; // fixed size string, requires null terminator
		union
		{
			uint32_t dayBits;
			struct
			{
				bool foggy : 1;
			};
		};
		int32_t fogRange1;
		int32_t fogRange2;
		SKIP(8);
		uint32_t lastWeeklyTimer;
		uint32_t lastMonthlyTimer;
		uint32_t lastYearlyTimer;
		uint32_t lastDailyTimer;
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
		int16_t type;
		int16_t typeIndex;
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
		union
		{
			std::array<int16_t, 3> velocity;
			struct
			{
				int16_t velocityX;
				int16_t velocityY;
				int16_t velocityZ;
			};
		};
		int16_t direction;
		int16_t lookAngle;
		union
		{
			uint16_t bits;
			struct
			{
				bool visible : 1;
				bool temporary : 1;
				bool haltTurnBased : 1;
				bool droppedByPlayer : 1;
				bool ignoreRange : 1;
				bool noZBuffer : 1;
				bool skipAFrame : 1;
				bool attachToHead : 1;
				bool missile : 1;
				bool removed : 1;
			};
		};
		int16_t room;
		int16_t age;
		int16_t maxAge;
		int16_t lightMultiplier;
		mm7::Item item;
		union
		{
			int32_t spellType;
			int32_t spell;
		};
		int32_t spellSkill;
		union
		{
			int32_t spellMastery;
			int32_t spellLevel;
		};
		mm7::SpellEffect* spellEffect;
		int32_t owner;
		int32_t target;
		uint8_t range;
		uint8_t attackType;
		SKIP(2);
		union
		{
			std::array<int32_t, 3> startPos;
			struct
			{
				int32_t startX;
				int32_t startY;
				int32_t startZ;
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
	static_assert(offsetof(mm7::MapObject, spellType) == 72);
	static_assert(offsetof(mm7::MapObject, spell) == 72);
	static_assert(offsetof(mm7::MapObject, spellSkill) == 76);
	static_assert(offsetof(mm7::MapObject, spellMastery) == 80);
	static_assert(offsetof(mm7::MapObject, spellLevel) == 80);
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
		std::array<mm7::BaseLight, 400> spriteLights; // size field offset is 0x519934
		uint32_t spriteLights_size;
		SKIP(831960);
		std::array<uint8_t, 200> vars;
		SKIP(1016);
		std::array<mm7::MapChest, 20> chests; // size field offset is 0x5FEFC0
		uint32_t chests_size;
		SKIP(20);
		std::array<mm7::MapMonster, 500> monsters; // size field offset is 0x6650A8
		uint32_t monsters_size;
		uint32_t objects_size;
		std::array<mm7::MapObject, 1000> objects; // size field offset is 0x6650AC
		SKIP(8);
		std::array<int32_t, 10> soundSprites; // size field offset is 0x680660
		uint32_t soundSprites_size;
		SKIP(12012);
		std::array<mm7::MapSprite, 3000> sprites; // size field offset is 0x69AC50
		uint32_t sprites_size;
		SKIP(24604);
		union
		{
			mm7::OdmHeader outdoorHeader;
			struct
			{
				SKIP(160);
				std::array<mm7::TilesetDef, 4> tilesets;
			};
		};
		uint32_t models_size;
		std::array<std::array<uint8_t, 128>, 128>* heightMap;
		std::array<std::array<uint8_t, 128>, 128>* tileMap;
		std::array<std::array<uint8_t, 128>, 128>* unknownMap;
		SKIP(24);
		mm7::MapModel* models; // size field offset is 0x6A0D20
		uint32_t IDList_size;
		mm7::ObjectRef2* IDList; // size field offset is 0x6A0D4C
		std::array<std::array<int32_t, 128>, 128>* IDOffsets;
		int32_t loadedSkyBitmap;
		SKIP(980);
		uint32_t outdoorSpawns_size;
		mm7::SpawnPoint* outdoorSpawns; // size field offset is 0x6A1130
		int32_t outdoorRefillCount;
		uint32_t outdoorLastRefillDay;
		int32_t outdoorReputation;
		SKIP(4);
		int32_t outdoorSanityFacetsCount;
		int32_t outdoorSanitySpritesCount;
		int32_t sanityModelsCount;
		SKIP(12);
		union
		{
			mm7::MapExtra outdoorExtra;
			struct
			{
				int64_t outdoorLastVisitTime;
			};
		};
		std::array<std::array<uint8_t, 11>, 88> visibleMap1; // array of abits (real index = 7 - usual)
		std::array<std::array<uint8_t, 11>, 88> visibleMap2; // array of abits (real index = 7 - usual)
		SKIP(116372);
		int32_t mapStatsIndex;
		SKIP(516);
		std::array<uint8_t, 20> name; // Unknown type
		SKIP(8);
		uint32_t indoorOrOutdoor;
		SKIP(97);
		bool noNPC;
		SKIP(490);
		mm7::BlvHeader indoorHeader;
		uint32_t vertexes_size;
		mm7::MapVertex* vertexes; // size field offset is 0x6BE4B8
		uint32_t facets_size;
		mm7::MapFacet* facets; // size field offset is 0x6BE4C0
		uint32_t facetData_size;
		mm7::FacetData* facetData; // size field offset is 0x6BE4C8
		uint32_t rooms_size;
		mm7::MapRoom* rooms; // size field offset is 0x6BE4D0
		uint32_t lights_size;
		mm7::MapLight* lights; // size field offset is 0x6BE4D8
		uint32_t doors_size;
		std::array<mm7::MapDoor, 200>* doors; // size field offset is 0x6BE4E0
		uint32_t BSPNodes_size;
		mm7::BSPNode* BSPNodes; // size field offset is 0x6BE4E8
		mm7::MapOutlines* outlines;
		SKIP(16);
		uint32_t indoorSpawns_size;
		mm7::SpawnPoint* indoorSpawns; // size field offset is 0x6BE504
		int32_t indoorRefillCount;
		uint32_t indoorLastRefillDay;
		int32_t indoorReputation;
		SKIP(4);
		int32_t indoorSanityFacetsCount;
		int32_t indoorSanitySpritesCount;
		std::array<uint8_t, 4> sanityDoorDataSize; // Unknown type
		// uint8_t* sanityFacetsCount; // real size is 0 | Unknown type
		// uint8_t* spawns; // real size is 0 | Unknown type
		// uint8_t* sanitySpritesCount; // real size is 0 | Unknown type
		// uint8_t* lastVisitTime; // real size is 0 | Unknown type
		// uint8_t* reputation; // real size is 0 | Unknown type
		// uint8_t* refillCount; // real size is 0 | Unknown type
		// uint8_t* lastRefillDay; // real size is 0 | Unknown type
		SKIP(12);
		union
		{
			mm7::MapExtra indoorExtra;
			struct
			{
				int64_t indoorLastVisitTime;
			};
		};
		std::array<uint8_t, 875> visibileOutlines; // array of abits (real index = 7 - usual)
		SKIP(518841);
		uint32_t terNorm_size;
		std::array<std::array<std::array<float, 2>, 128>, 128> terNormDist;
		std::array<std::array<std::array<int16_t, 2>, 128>, 128> terNormId;
		mm7::FloatVector* terNorm; // size field offset is 0x73D390
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
		int64_t lastVisitTime;
		std::array<char, 12> skyBitmap; // fixed size string, doesn't require null terminator
		union
		{
			uint32_t dayBits;
			struct
			{
				bool foggy : 1;
			};
		};
		int32_t fogRange1;
		int32_t fogRange2;
		union
		{
			uint32_t bits;
			struct
			{
				bool raining : 1;
				bool snowing : 1;
				bool underwater : 1;
				bool noTerrain : 1;
				bool alwaysDark : 1;
				bool alwaysLight : 1;
				bool alwaysFoggy : 1;
				bool redFog : 1;
			};
		};
		int32_t ceiling;
		uint32_t lastWeeklyTimer;
		uint32_t lastMonthlyTimer;
		uint32_t lastYearlyTimer;
		uint32_t lastDailyTimer;
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
		int16_t type;
		int16_t typeIndex;
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
		union
		{
			std::array<int16_t, 3> velocity;
			struct
			{
				int16_t velocityX;
				int16_t velocityY;
				int16_t velocityZ;
			};
		};
		int16_t direction;
		int16_t lookAngle;
		union
		{
			uint16_t bits;
			struct
			{
				bool visible : 1;
				bool temporary : 1;
				bool haltTurnBased : 1;
				bool droppedByPlayer : 1;
				bool ignoreRange : 1;
				bool noZBuffer : 1;
				bool skipAFrame : 1;
				bool attachToHead : 1;
				bool missile : 1;
				bool removed : 1;
			};
		};
		int16_t room;
		int16_t age;
		int16_t maxAge;
		int16_t lightMultiplier;
		mm8::Item item;
		union
		{
			int32_t spell;
			int32_t spellType;
		};
		int32_t spellSkill;
		union
		{
			int32_t spellLevel;
			int32_t spellMastery;
		};
		mm8::SpellEffect* spellEffect;
		int32_t owner;
		int32_t target;
		uint8_t range;
		uint8_t attackType;
		SKIP(2);
		union
		{
			std::array<int32_t, 3> startPos;
			struct
			{
				int32_t startX;
				int32_t startY;
				int32_t startZ;
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
		std::array<mm8::MapMonster, 1500> monsters; // size field offset is 0x692FB0
		SKIP(3956748);
		std::array<mm8::BaseLight, 400> spriteLights; // size field offset is 0x52B21C
		uint32_t spriteLights_size;
		SKIP(880216);
		std::array<uint8_t, 200> vars;
		SKIP(1016);
		std::array<mm8::MapChest, 20> chests; // size field offset is 0x61C528
		uint32_t chests_size;
		SKIP(486020);
		uint32_t monsters_size;
		uint32_t objects_size;
		std::array<mm8::MapObject, 1000> objects; // size field offset is 0x692FB4
		SKIP(8);
		std::array<int32_t, 10> soundSprites; // size field offset is 0x6AE568
		uint32_t soundSprites_size;
		SKIP(12012);
		std::array<mm8::MapSprite, 3000> sprites; // size field offset is 0x6C8B58
		uint32_t sprites_size;
		SKIP(24692);
		union
		{
			mm8::OdmHeader outdoorHeader;
			struct
			{
				SKIP(95);
				uint8_t tilesetsFile;
				SKIP(64);
				std::array<mm8::TilesetDef, 4> tilesets;
			};
		};
		uint32_t models_size;
		std::array<std::array<uint8_t, 128>, 128>* heightMap;
		std::array<std::array<uint8_t, 128>, 128>* tileMap;
		union
		{
			std::array<std::array<uint8_t, 128>, 128>* unknownMap;
			std::array<std::array<uint8_t, 128>, 128>* unknownMap2;
		};
		SKIP(24);
		mm8::MapModel* models; // size field offset is 0x6CEC84
		uint32_t IDList_size;
		mm8::ObjectRef2* IDList; // size field offset is 0x6CECB0
		std::array<std::array<int32_t, 128>, 128>* IDOffsets;
		int32_t loadedSkyBitmap;
		SKIP(980);
		uint32_t outdoorSpawns_size;
		mm8::SpawnPoint* outdoorSpawns; // size field offset is 0x6CF094
		int32_t outdoorRefillCount;
		int32_t outdoorLastRefillDay;
		SKIP(8);
		int32_t outdoorReputation;
		SKIP(28);
		union
		{
			mm8::MapExtra outdoorExtra;
			struct
			{
				int64_t outdoorLastVisitTime;
			};
		};
		std::array<std::array<uint8_t, 11>, 88> visibleMap1; // array of abits (real index = 7 - usual)
		std::array<std::array<uint8_t, 11>, 88> visibleMap2; // array of abits (real index = 7 - usual)
		std::array<mm8::MapNote, 100> notes;
		SKIP(114856);
		int32_t mapStatsIndex;
		SKIP(2236);
		std::array<uint8_t, 20> name; // Unknown type
		SKIP(8);
		uint32_t indoorOrOutdoor;
		SKIP(588);
		mm8::BlvHeader indoorHeader;
		uint32_t vertexes_size;
		mm8::MapVertex* vertexes; // size field offset is 0x6F3C78
		uint32_t facets_size;
		mm8::MapFacet* facets; // size field offset is 0x6F3C80
		uint32_t facetData_size;
		mm8::FacetData* facetData; // size field offset is 0x6F3C88
		uint32_t rooms_size;
		mm8::MapRoom* rooms; // size field offset is 0x6F3C90
		uint32_t lights_size;
		mm8::MapLight* lights; // size field offset is 0x6F3C98
		uint32_t doors_size;
		std::array<mm8::MapDoor, 200>* doors; // size field offset is 0x6F3CA0
		uint32_t BSPNodes_size;
		mm8::BSPNode* BSPNodes; // size field offset is 0x6F3CA8
		mm8::MapOutlines* outlines;
		SKIP(16);
		uint32_t indoorSpawns_size;
		mm8::SpawnPoint* indoorSpawns; // size field offset is 0x6F3CC4
		int32_t indoorRefillCount;
		int32_t indoorLastRefillDay;
		int32_t indoorReputation;
		// uint8_t* lastRefillDay; // real size is 0 | Unknown type
		// uint8_t* lastVisitTime; // real size is 0 | Unknown type
		// uint8_t* refillCount; // real size is 0 | Unknown type
		// uint8_t* reputation; // real size is 0 | Unknown type
		// uint8_t* spawns; // real size is 0 | Unknown type
		SKIP(28);
		union
		{
			mm8::MapExtra indoorExtra;
			struct
			{
				int64_t indoorLastVisitTime;
			};
		};
		std::array<uint8_t, 875> visibileOutlines; // array of abits (real index = 7 - usual)
		SKIP(553665);
		uint32_t terNorm_size;
		std::array<std::array<std::array<float, 2>, 128>, 128> terNormDist;
		std::array<std::array<std::array<int16_t, 2>, 128>, 128> terNormId;
		mm8::FloatVector* terNorm; // size field offset is 0x77B358
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