#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct MapVertex // size: 0x6
	{
		union
		{
			int16_t x; // 0x0 (0 decimal)
			int16_t _1; // 0x0 (0 decimal)
		};
		union
		{
			int16_t y; // 0x2 (2 decimal)
			int16_t _2; // 0x2 (2 decimal)
		};
		union
		{
			int16_t z; // 0x4 (4 decimal)
			int16_t _3; // 0x4 (4 decimal)
		};
	};
	static_assert(sizeof(mm6::MapVertex) == 0x6, "Invalid \"mm6::MapVertex\" structure size");
	static_assert(offsetof(mm6::MapVertex, y) == 2);
	static_assert(offsetof(mm6::MapVertex, _2) == 2);
	static_assert(offsetof(mm6::MapVertex, z) == 4);
	static_assert(offsetof(mm6::MapVertex, _3) == 4);



	struct MapSprite // size: 0x1C
	{
		union
		{
			int16_t decListId; // 0x0 (0 decimal)
			std::array<uint8_t, 2> decName; // Unknown type | 0x0 (0 decimal)
		};
		union
		{
			uint16_t bits; // 0x2 (2 decimal)
			struct
			{
				bool triggerByTouch : 1; // 0x2 (2 decimal), bit index 7
				bool triggerByMonster : 1; // 0x2 (2 decimal), bit index 6
				bool triggerByObject : 1; // 0x2 (2 decimal), bit index 5
				bool showOnMap : 1; // 0x2 (2 decimal), bit index 4
				bool isChest : 1; // 0x2 (2 decimal), bit index 3
				bool invisible : 1; // 0x2 (2 decimal), bit index 2
				bool isShip : 1; // 0x2 (2 decimal), bit index 1
			};
		};
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
		int32_t direction; // 0x10 (16 decimal)
		int16_t eventVariable; // 0x14 (20 decimal)
		int16_t event; // 0x16 (22 decimal) | MMExt info: normal event
		int16_t triggerRadius; // 0x18 (24 decimal)
		int16_t directionDegrees; // 0x1A (26 decimal) | MMExt info: only used if 'Direction' is '0'
	};
	static_assert(sizeof(mm6::MapSprite) == 0x1C, "Invalid \"mm6::MapSprite\" structure size");
	static_assert(offsetof(mm6::MapSprite, bits) == 2);
	static_assert(offsetof(mm6::MapSprite, pos) == 4);
	static_assert(offsetof(mm6::MapSprite, x) == 4);
	static_assert(offsetof(mm6::MapSprite, y) == 8);
	static_assert(offsetof(mm6::MapSprite, z) == 12);
	static_assert(offsetof(mm6::MapSprite, direction) == 16);
	static_assert(offsetof(mm6::MapSprite, eventVariable) == 20);
	static_assert(offsetof(mm6::MapSprite, event) == 22);
	static_assert(offsetof(mm6::MapSprite, triggerRadius) == 24);
	static_assert(offsetof(mm6::MapSprite, directionDegrees) == 26);



	struct MapRoom // size: 0x74
	{
		union
		{
			uint32_t bits; // 0x0 (0 decimal)
			struct
			{
				SKIPBITS(3);
				bool hasNonVerticalPortals : 1; // 0x0 (0 decimal), bit index 4
				bool hasBSP : 1; // 0x0 (0 decimal), bit index 3
			};
		};
		uint16_t floors_size; // 0x4 (4 decimal)
		SKIP(2);
		int16_t* floors; // size field offset is 0x4 | 0x8 (8 decimal)
		uint16_t walls_size; // 0xC (12 decimal)
		SKIP(2);
		int16_t* walls; // size field offset is 0xC | 0x10 (16 decimal)
		uint16_t ceils_size; // 0x14 (20 decimal)
		SKIP(2);
		int16_t* ceils; // size field offset is 0x14 | 0x18 (24 decimal)
		uint16_t fluids_size; // 0x1C (28 decimal)
		SKIP(2);
		int16_t* fluids; // size field offset is 0x1C | 0x20 (32 decimal)
		uint16_t portals_size; // 0x24 (36 decimal)
		SKIP(2);
		int16_t* portals; // size field offset is 0x24 | 0x28 (40 decimal)
		uint16_t drawFacets_size; // 0x2C (44 decimal)
		int16_t nonBSPDrawFacetsCount; // 0x2E (46 decimal) | MMExt info: # of non-BSP Node facets to draw
		int16_t* drawFacets; // size field offset is 0x2C | 0x30 (48 decimal) | MMExt info: drawing order
		SKIP(8);
		uint16_t cogs_size; // 0x3C (60 decimal)
		SKIP(2);
		int16_t* cogs; // size field offset is 0x3C | 0x40 (64 decimal)
		uint16_t sprites_size; // 0x44 (68 decimal)
		SKIP(2);
		int16_t* sprites; // size field offset is 0x44 | 0x48 (72 decimal)
		uint16_t markers_size; // 0x4C (76 decimal)
		SKIP(2);
		int16_t* markers; // size field offset is 0x4C | 0x50 (80 decimal)
		uint16_t lights_size; // 0x54 (84 decimal)
		SKIP(2);
		int16_t* lights; // size field offset is 0x54 | 0x58 (88 decimal)
		SKIP(6);
		int16_t darkness; // 0x62 (98 decimal) | MMExt info: Min Ambient Light Level
		int16_t firstBSPNode; // 0x64 (100 decimal) | MMExt info: First BSP Node Index
		SKIP(1);
		uint8_t exitTag; // 0x67 (103 decimal)
		int16_t minX; // 0x68 (104 decimal) | MMExt info: Bounding Box Min X
		int16_t maxX; // 0x6A (106 decimal) | MMExt info: Bounding Box Max X
		int16_t minY; // 0x6C (108 decimal) | MMExt info: Bounding Box Min Y
		int16_t maxY; // 0x6E (110 decimal) | MMExt info: Bounding Box Max Y
		int16_t minZ; // 0x70 (112 decimal) | MMExt info: Bounding Box Min Z
		int16_t maxZ; // 0x72 (114 decimal) | MMExt info: Bounding Box Max Z
	};
	static_assert(sizeof(mm6::MapRoom) == 0x74, "Invalid \"mm6::MapRoom\" structure size");
	static_assert(offsetof(mm6::MapRoom, floors_size) == 4);
	static_assert(offsetof(mm6::MapRoom, floors) == 8);
	static_assert(offsetof(mm6::MapRoom, walls_size) == 12);
	static_assert(offsetof(mm6::MapRoom, walls) == 16);
	static_assert(offsetof(mm6::MapRoom, ceils_size) == 20);
	static_assert(offsetof(mm6::MapRoom, ceils) == 24);
	static_assert(offsetof(mm6::MapRoom, fluids_size) == 28);
	static_assert(offsetof(mm6::MapRoom, fluids) == 32);
	static_assert(offsetof(mm6::MapRoom, portals_size) == 36);
	static_assert(offsetof(mm6::MapRoom, portals) == 40);
	static_assert(offsetof(mm6::MapRoom, drawFacets_size) == 44);
	static_assert(offsetof(mm6::MapRoom, nonBSPDrawFacetsCount) == 46);
	static_assert(offsetof(mm6::MapRoom, drawFacets) == 48);
	static_assert(offsetof(mm6::MapRoom, cogs_size) == 60);
	static_assert(offsetof(mm6::MapRoom, cogs) == 64);
	static_assert(offsetof(mm6::MapRoom, sprites_size) == 68);
	static_assert(offsetof(mm6::MapRoom, sprites) == 72);
	static_assert(offsetof(mm6::MapRoom, markers_size) == 76);
	static_assert(offsetof(mm6::MapRoom, markers) == 80);
	static_assert(offsetof(mm6::MapRoom, lights_size) == 84);
	static_assert(offsetof(mm6::MapRoom, lights) == 88);
	static_assert(offsetof(mm6::MapRoom, darkness) == 98);
	static_assert(offsetof(mm6::MapRoom, firstBSPNode) == 100);
	static_assert(offsetof(mm6::MapRoom, exitTag) == 103);
	static_assert(offsetof(mm6::MapRoom, minX) == 104);
	static_assert(offsetof(mm6::MapRoom, maxX) == 106);
	static_assert(offsetof(mm6::MapRoom, minY) == 108);
	static_assert(offsetof(mm6::MapRoom, maxY) == 110);
	static_assert(offsetof(mm6::MapRoom, minZ) == 112);
	static_assert(offsetof(mm6::MapRoom, maxZ) == 114);



	struct MapLight // size: 0xC
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
		union
		{
			uint16_t bits; // 0x6 (6 decimal)
			struct
			{
				SKIPBITS(3);
				bool off : 1; // 0x6 (6 decimal), bit index 4
			};
		};
		int16_t brightness; // 0x8 (8 decimal)
		int16_t radius; // 0xA (10 decimal)
	};
	static_assert(sizeof(mm6::MapLight) == 0xC, "Invalid \"mm6::MapLight\" structure size");
	static_assert(offsetof(mm6::MapLight, y) == 2);
	static_assert(offsetof(mm6::MapLight, z) == 4);
	static_assert(offsetof(mm6::MapLight, bits) == 6);
	static_assert(offsetof(mm6::MapLight, brightness) == 8);
	static_assert(offsetof(mm6::MapLight, radius) == 10);



	struct MapFacet // size: 0x50
	{
		union
		{
			std::array<int32_t, 3> normal; // 0x0 (0 decimal) | MMExt info: normal fixed pt (0..0x10000)
			struct
			{
				int32_t normalX; // 0x0 (0 decimal) | MMExt info: normal X fixed pt (0..0x10000)
				int32_t normalY; // 0x4 (4 decimal) | MMExt info: normal Y fixed pt (0..0x10000)
				int32_t normalZ; // 0x8 (8 decimal) | MMExt info: normal Z fixed pt (0..0x10000)
			};
		};
		int32_t normalDistance; // 0xC (12 decimal) | MMExt info: normal distance fixed pt (0..0x10000)
		int32_t ZCalc1; // 0x10 (16 decimal) | MMExt info:   !Lua[[= -(NormalX * 2^16) / NormalZ         ]](or 0 if 'NormalZ' is 0)
		int32_t ZCalc2; // 0x14 (20 decimal) | MMExt info:   !Lua[[= -(NormalY * 2^16) / NormalZ         ]](or 0 if 'NormalZ' is 0)
		int32_t ZCalc3; // 0x18 (24 decimal) | MMExt info:   !Lua[[= -(NormalDistance * 2^16) / NormalZ  ]](or 0 if 'NormalZ' is 0)
		union
		{
			uint32_t bits; // 0x1C (28 decimal)
			struct
			{
				bool isPortal : 1; // 0x1C (28 decimal), bit index 7
				SKIPBITS(3);
				bool isWater : 1; // 0x1C (28 decimal), bit index 3
				SKIPBITS(3);
				bool projectToXY : 1; // 0x1D (29 decimal), bit index 7
				bool projectToXZ : 1; // 0x1D (29 decimal), bit index 6
				bool projectToYZ : 1; // 0x1D (29 decimal), bit index 5
				SKIPBITS(2);
				bool invisible : 1; // 0x1D (29 decimal), bit index 2
				bool animatedTFT : 1; // 0x1D (29 decimal), bit index 1
				SKIPBITS(1); // skipping 0 bytes and 3 bits, in total 3 bits
				SKIPBITS(2);
				bool moveByDoor : 1; // 0x1E (30 decimal), bit index 5
				SKIPBITS(1);
				bool isEventJustHint : 1; // 0x1E (30 decimal), bit index 3
				bool alternativeSound : 1; // 0x1E (30 decimal), bit index 2
				bool isSky : 1; // 0x1E (30 decimal), bit index 1
				bool flipU : 1; // 0x1E (30 decimal), bit index 0
				bool flipV : 1; // 0x1F (31 decimal), bit index 7
				bool triggerByClick : 1; // 0x1F (31 decimal), bit index 6
				bool triggerByStep : 1; // 0x1F (31 decimal), bit index 5
				bool triggerByMonster : 1; // 0x1F (31 decimal), bit index 4
				bool triggerByObject : 1; // 0x1F (31 decimal), bit index 3
				bool untouchable : 1; // 0x1F (31 decimal), bit index 2
				bool isLava : 1; // 0x1F (31 decimal), bit index 1
				bool hasData : 1; // 0x1F (31 decimal), bit index 0
			};
		};
		uint16_t* vertexIds; // AccessBeyondLength is active (???) | size field offset is 0x4D | 0x20 (32 decimal)
		int16_t* XInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x4D | 0x24 (36 decimal)
		int16_t* YInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x4D | 0x28 (40 decimal)
		int16_t* ZInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x4D | 0x2C (44 decimal)
		int16_t* UList; // AccessBeyondLength is active (???) | size field offset is 0x4D | 0x30 (48 decimal)
		int16_t* VList; // AccessBeyondLength is active (???) | size field offset is 0x4D | 0x34 (52 decimal)
		uint16_t dataIndex; // 0x38 (56 decimal)
		int16_t bitmapId; // 0x3A (58 decimal) | MMExt info: Bitmap Index
		int16_t room; // 0x3C (60 decimal) | MMExt info: Room #
		int16_t roomBehind; // 0x3E (62 decimal) | MMExt info: Room # Behind facet
		int16_t minX; // 0x40 (64 decimal) | MMExt info: Bounding Box Min X
		int16_t maxX; // 0x42 (66 decimal) | MMExt info: Bounding Box Max X
		int16_t minY; // 0x44 (68 decimal) | MMExt info: Bounding Box Min Y
		int16_t maxY; // 0x46 (70 decimal) | MMExt info: Bounding Box Max Y
		int16_t minZ; // 0x48 (72 decimal) | MMExt info: Bounding Box Min Z
		int16_t maxZ; // 0x4A (74 decimal) | MMExt info: Bounding Box Max Z
		// MMExt info: Polygon type:
		// 0 = empty
		// 1 = wall
		// 2 = unused
		// 3 = horizontal floor
		// 4 = irregular floor (non-horizontal)
		// 5 = horizontal ceiling
		// 6 = irregular ceiling (non-horizontal)
		uint8_t polygonType; // 0x4C (76 decimal)
		union
		{
			uint8_t UList_size; // 0x4D (77 decimal)
			uint8_t VList_size; // 0x4D (77 decimal)
			uint8_t vertexIds_size; // 0x4D (77 decimal)
			uint8_t vertexesCount; // 0x4D (77 decimal)
			uint8_t XInterceptDisplacement_size; // 0x4D (77 decimal)
			uint8_t YInterceptDisplacement_size; // 0x4D (77 decimal)
			uint8_t ZInterceptDisplacement_size; // 0x4D (77 decimal)
		};
		SKIP(2);
	};
	static_assert(sizeof(mm6::MapFacet) == 0x50, "Invalid \"mm6::MapFacet\" structure size");
	static_assert(offsetof(mm6::MapFacet, normalY) == 4);
	static_assert(offsetof(mm6::MapFacet, normalZ) == 8);
	static_assert(offsetof(mm6::MapFacet, normalDistance) == 12);
	static_assert(offsetof(mm6::MapFacet, ZCalc1) == 16);
	static_assert(offsetof(mm6::MapFacet, ZCalc2) == 20);
	static_assert(offsetof(mm6::MapFacet, ZCalc3) == 24);
	static_assert(offsetof(mm6::MapFacet, bits) == 28);
	static_assert(offsetof(mm6::MapFacet, vertexIds) == 32);
	static_assert(offsetof(mm6::MapFacet, XInterceptDisplacement) == 36);
	static_assert(offsetof(mm6::MapFacet, YInterceptDisplacement) == 40);
	static_assert(offsetof(mm6::MapFacet, ZInterceptDisplacement) == 44);
	static_assert(offsetof(mm6::MapFacet, UList) == 48);
	static_assert(offsetof(mm6::MapFacet, VList) == 52);
	static_assert(offsetof(mm6::MapFacet, dataIndex) == 56);
	static_assert(offsetof(mm6::MapFacet, bitmapId) == 58);
	static_assert(offsetof(mm6::MapFacet, room) == 60);
	static_assert(offsetof(mm6::MapFacet, roomBehind) == 62);
	static_assert(offsetof(mm6::MapFacet, minX) == 64);
	static_assert(offsetof(mm6::MapFacet, maxX) == 66);
	static_assert(offsetof(mm6::MapFacet, minY) == 68);
	static_assert(offsetof(mm6::MapFacet, maxY) == 70);
	static_assert(offsetof(mm6::MapFacet, minZ) == 72);
	static_assert(offsetof(mm6::MapFacet, maxZ) == 74);
	static_assert(offsetof(mm6::MapFacet, polygonType) == 76);
	static_assert(offsetof(mm6::MapFacet, UList_size) == 77);
	static_assert(offsetof(mm6::MapFacet, VList_size) == 77);
	static_assert(offsetof(mm6::MapFacet, vertexIds_size) == 77);
	static_assert(offsetof(mm6::MapFacet, vertexesCount) == 77);
	static_assert(offsetof(mm6::MapFacet, XInterceptDisplacement_size) == 77);
	static_assert(offsetof(mm6::MapFacet, YInterceptDisplacement_size) == 77);
	static_assert(offsetof(mm6::MapFacet, ZInterceptDisplacement_size) == 77);



	struct FacetData // size: 0x24
	{
		SKIP(12);
		int16_t facetIndex; // 0xC (12 decimal)
		int16_t bitmapIndex; // 0xE (14 decimal)
		int16_t TFTIndex; // 0x10 (16 decimal)
		SKIP(2);
		int16_t bitmapU; // 0x14 (20 decimal) | MMExt info: Bitmap U Offset
		int16_t bitmapV; // 0x16 (22 decimal) | MMExt info: Bitmap V Offset
		int16_t id; // 0x18 (24 decimal)
		int16_t event; // 0x1A (26 decimal)
		SKIP(8);
	};
	static_assert(sizeof(mm6::FacetData) == 0x24, "Invalid \"mm6::FacetData\" structure size");
	static_assert(offsetof(mm6::FacetData, facetIndex) == 12);
	static_assert(offsetof(mm6::FacetData, bitmapIndex) == 14);
	static_assert(offsetof(mm6::FacetData, TFTIndex) == 16);
	static_assert(offsetof(mm6::FacetData, bitmapU) == 20);
	static_assert(offsetof(mm6::FacetData, bitmapV) == 22);
	static_assert(offsetof(mm6::FacetData, id) == 24);
	static_assert(offsetof(mm6::FacetData, event) == 26);



	struct MapDoor // size: 0x50
	{
		union
		{
			uint32_t bits; // 0x0 (0 decimal)
			struct
			{
				bool startState2 : 1; // 0x0 (0 decimal), bit index 7
				bool silentMove : 1; // 0x0 (0 decimal), bit index 6
				bool noSound : 1; // 0x0 (0 decimal), bit index 5
				bool stopped : 1; // 0x0 (0 decimal), bit index 4
			};
		};
		int32_t id; // 0x4 (4 decimal)
		int32_t timeStep; // 0x8 (8 decimal) | MMExt info: time since triggered
		union
		{
			std::array<int32_t, 3> direction; // 0xC (12 decimal)
			struct
			{
				int32_t directionX; // 0xC (12 decimal)
				int32_t directionY; // 0x10 (16 decimal)
				int32_t directionZ; // 0x14 (20 decimal)
			};
		};
		int32_t moveLength; // 0x18 (24 decimal)
		union
		{
			int32_t openSpeed; // 0x1C (28 decimal) | MMExt info: State 3 velocity (speed*time/128 = position)
			int32_t speed2; // 0x1C (28 decimal) | MMExt info: State 3 velocity (speed*time/128 = position)
		};
		union
		{
			int32_t closeSpeed; // 0x20 (32 decimal) | MMExt info: State 1 velocity
			int32_t speed1; // 0x20 (32 decimal) | MMExt info: State 1 velocity (speed*time/128 = position)
		};
		int16_t* vertexIds; // size field offset is 0x44 | 0x24 (36 decimal)
		int16_t* facetIds; // size field offset is 0x46 | 0x28 (40 decimal)
		int16_t* roomIds; // size field offset is 0x48 | 0x2C (44 decimal)
		int16_t* facetStartU; // size field offset is 0x46 | 0x30 (48 decimal)
		int16_t* facetStartV; // size field offset is 0x46 | 0x34 (52 decimal)
		int16_t* vertexStartX; // size field offset is 0x4A | 0x38 (56 decimal)
		int16_t* vertexStartY; // size field offset is 0x4A | 0x3C (60 decimal)
		int16_t* vertexStartZ; // size field offset is 0x4A | 0x40 (64 decimal)
		uint16_t vertexIds_size; // 0x44 (68 decimal)
		union
		{
			uint16_t facetIds_size; // 0x46 (70 decimal)
			uint16_t facetStartU_size; // 0x46 (70 decimal)
			uint16_t facetStartV_size; // 0x46 (70 decimal)
		};
		uint16_t roomIds_size; // 0x48 (72 decimal)
		union
		{
			uint16_t vertexStartX_size; // 0x4A (74 decimal)
			uint16_t vertexStartY_size; // 0x4A (74 decimal)
			uint16_t vertexStartZ_size; // 0x4A (74 decimal)
		};
		// MMExt info: 'State' compared with evt.SetDoorState:
		// 0 = state (0)
		// 1 = move to (1)
		// 2 = state (1)
		// 3 = move to (0)
		int16_t state; // 0x4C (76 decimal)
		SKIP(2);
	};
	static_assert(sizeof(mm6::MapDoor) == 0x50, "Invalid \"mm6::MapDoor\" structure size");
	static_assert(offsetof(mm6::MapDoor, id) == 4);
	static_assert(offsetof(mm6::MapDoor, timeStep) == 8);
	static_assert(offsetof(mm6::MapDoor, direction) == 12);
	static_assert(offsetof(mm6::MapDoor, directionX) == 12);
	static_assert(offsetof(mm6::MapDoor, directionY) == 16);
	static_assert(offsetof(mm6::MapDoor, directionZ) == 20);
	static_assert(offsetof(mm6::MapDoor, moveLength) == 24);
	static_assert(offsetof(mm6::MapDoor, openSpeed) == 28);
	static_assert(offsetof(mm6::MapDoor, speed2) == 28);
	static_assert(offsetof(mm6::MapDoor, closeSpeed) == 32);
	static_assert(offsetof(mm6::MapDoor, speed1) == 32);
	static_assert(offsetof(mm6::MapDoor, vertexIds) == 36);
	static_assert(offsetof(mm6::MapDoor, facetIds) == 40);
	static_assert(offsetof(mm6::MapDoor, roomIds) == 44);
	static_assert(offsetof(mm6::MapDoor, facetStartU) == 48);
	static_assert(offsetof(mm6::MapDoor, facetStartV) == 52);
	static_assert(offsetof(mm6::MapDoor, vertexStartX) == 56);
	static_assert(offsetof(mm6::MapDoor, vertexStartY) == 60);
	static_assert(offsetof(mm6::MapDoor, vertexStartZ) == 64);
	static_assert(offsetof(mm6::MapDoor, vertexIds_size) == 68);
	static_assert(offsetof(mm6::MapDoor, facetIds_size) == 70);
	static_assert(offsetof(mm6::MapDoor, facetStartU_size) == 70);
	static_assert(offsetof(mm6::MapDoor, facetStartV_size) == 70);
	static_assert(offsetof(mm6::MapDoor, roomIds_size) == 72);
	static_assert(offsetof(mm6::MapDoor, vertexStartX_size) == 74);
	static_assert(offsetof(mm6::MapDoor, vertexStartY_size) == 74);
	static_assert(offsetof(mm6::MapDoor, vertexStartZ_size) == 74);
	static_assert(offsetof(mm6::MapDoor, state) == 76);



	struct MapChest // size: 0x106C
	{
		int16_t chestPicture; // 0x0 (0 decimal) | MMExt info: 0..7  chest id
		union
		{
			uint16_t bits; // 0x2 (2 decimal)
			struct
			{
				bool trapped : 1; // 0x2 (2 decimal), bit index 7
				bool itemsPlaced : 1; // 0x2 (2 decimal), bit index 6
				bool identified : 1; // 0x2 (2 decimal), bit index 5
			};
		};
		std::array<mm6::Item, 140> items; // MMExt: 1..140, here 0..139 | 0x4 (4 decimal)
		std::array<int16_t, 140> inventory; // 0xF54 (3924 decimal) | MMExt info: ('Items' index) for main item cell,  -(1 + main 'Inventory' cell index) for other cells
	};
	static_assert(sizeof(mm6::MapChest) == 0x106C, "Invalid \"mm6::MapChest\" structure size");
	static_assert(offsetof(mm6::MapChest, bits) == 2);
	static_assert(offsetof(mm6::MapChest, items) == 4);
	static_assert(offsetof(mm6::MapChest, inventory) == 3924);
}
namespace mm7
{
	struct MapVertex // size: 0x6
	{
		union
		{
			int16_t x; // 0x0 (0 decimal)
			int16_t _1; // 0x0 (0 decimal)
		};
		union
		{
			int16_t y; // 0x2 (2 decimal)
			int16_t _2; // 0x2 (2 decimal)
		};
		union
		{
			int16_t z; // 0x4 (4 decimal)
			int16_t _3; // 0x4 (4 decimal)
		};
	};
	static_assert(sizeof(mm7::MapVertex) == 0x6, "Invalid \"mm7::MapVertex\" structure size");
	static_assert(offsetof(mm7::MapVertex, y) == 2);
	static_assert(offsetof(mm7::MapVertex, _2) == 2);
	static_assert(offsetof(mm7::MapVertex, z) == 4);
	static_assert(offsetof(mm7::MapVertex, _3) == 4);



	struct MapSprite // size: 0x20
	{
		union
		{
			int16_t decListId; // 0x0 (0 decimal)
			std::array<uint8_t, 2> decName; // Unknown type | 0x0 (0 decimal)
		};
		union
		{
			uint16_t bits; // 0x2 (2 decimal)
			struct
			{
				bool triggerByTouch : 1; // 0x2 (2 decimal), bit index 7
				bool triggerByMonster : 1; // 0x2 (2 decimal), bit index 6
				bool triggerByObject : 1; // 0x2 (2 decimal), bit index 5
				bool showOnMap : 1; // 0x2 (2 decimal), bit index 4
				bool isChest : 1; // 0x2 (2 decimal), bit index 3
				bool invisible : 1; // 0x2 (2 decimal), bit index 2
				bool isObeliskChest : 1; // 0x2 (2 decimal), bit index 1
			};
		};
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
		int32_t direction; // 0x10 (16 decimal)
		int16_t id; // 0x14 (20 decimal)
		int16_t event; // 0x16 (22 decimal) | MMExt info: normal event
		int16_t triggerRadius; // 0x18 (24 decimal)
		int16_t directionDegrees; // 0x1A (26 decimal) | MMExt info: only used if 'Direction' is '0'
		int16_t eventVariable; // 0x1C (28 decimal) | MMExt info: event variable for barrels etc.
		SKIP(2);
	};
	static_assert(sizeof(mm7::MapSprite) == 0x20, "Invalid \"mm7::MapSprite\" structure size");
	static_assert(offsetof(mm7::MapSprite, bits) == 2);
	static_assert(offsetof(mm7::MapSprite, pos) == 4);
	static_assert(offsetof(mm7::MapSprite, x) == 4);
	static_assert(offsetof(mm7::MapSprite, y) == 8);
	static_assert(offsetof(mm7::MapSprite, z) == 12);
	static_assert(offsetof(mm7::MapSprite, direction) == 16);
	static_assert(offsetof(mm7::MapSprite, id) == 20);
	static_assert(offsetof(mm7::MapSprite, event) == 22);
	static_assert(offsetof(mm7::MapSprite, triggerRadius) == 24);
	static_assert(offsetof(mm7::MapSprite, directionDegrees) == 26);
	static_assert(offsetof(mm7::MapSprite, eventVariable) == 28);



	struct MapRoom // size: 0x74
	{
		union
		{
			uint32_t bits; // 0x0 (0 decimal)
			struct
			{
				SKIPBITS(3);
				bool hasNonVerticalPortals : 1; // 0x0 (0 decimal), bit index 4
				bool hasBSP : 1; // 0x0 (0 decimal), bit index 3
			};
		};
		uint16_t floors_size; // 0x4 (4 decimal)
		SKIP(2);
		int16_t* floors; // size field offset is 0x4 | 0x8 (8 decimal)
		uint16_t walls_size; // 0xC (12 decimal)
		SKIP(2);
		int16_t* walls; // size field offset is 0xC | 0x10 (16 decimal)
		uint16_t ceils_size; // 0x14 (20 decimal)
		SKIP(2);
		int16_t* ceils; // size field offset is 0x14 | 0x18 (24 decimal)
		uint16_t fluids_size; // 0x1C (28 decimal)
		SKIP(2);
		int16_t* fluids; // size field offset is 0x1C | 0x20 (32 decimal)
		uint16_t portals_size; // 0x24 (36 decimal)
		SKIP(2);
		int16_t* portals; // size field offset is 0x24 | 0x28 (40 decimal)
		uint16_t drawFacets_size; // 0x2C (44 decimal)
		int16_t nonBSPDrawFacetsCount; // 0x2E (46 decimal) | MMExt info: # of non-BSP Node facets to draw
		int16_t* drawFacets; // size field offset is 0x2C | 0x30 (48 decimal) | MMExt info: drawing order
		SKIP(8);
		uint16_t cogs_size; // 0x3C (60 decimal)
		SKIP(2);
		int16_t* cogs; // size field offset is 0x3C | 0x40 (64 decimal)
		uint16_t sprites_size; // 0x44 (68 decimal)
		SKIP(2);
		int16_t* sprites; // size field offset is 0x44 | 0x48 (72 decimal)
		uint16_t markers_size; // 0x4C (76 decimal)
		SKIP(2);
		int16_t* markers; // size field offset is 0x4C | 0x50 (80 decimal)
		uint16_t lights_size; // 0x54 (84 decimal)
		SKIP(2);
		int16_t* lights; // size field offset is 0x54 | 0x58 (88 decimal)
		SKIP(6);
		int16_t darkness; // 0x62 (98 decimal) | MMExt info: Min Ambient Light Level
		int16_t firstBSPNode; // 0x64 (100 decimal) | MMExt info: First BSP Node Index
		SKIP(1);
		uint8_t exitTag; // 0x67 (103 decimal)
		int16_t minX; // 0x68 (104 decimal) | MMExt info: Bounding Box Min X
		int16_t maxX; // 0x6A (106 decimal) | MMExt info: Bounding Box Max X
		int16_t minY; // 0x6C (108 decimal) | MMExt info: Bounding Box Min Y
		int16_t maxY; // 0x6E (110 decimal) | MMExt info: Bounding Box Max Y
		int16_t minZ; // 0x70 (112 decimal) | MMExt info: Bounding Box Min Z
		int16_t maxZ; // 0x72 (114 decimal) | MMExt info: Bounding Box Max Z
	};
	static_assert(sizeof(mm7::MapRoom) == 0x74, "Invalid \"mm7::MapRoom\" structure size");
	static_assert(offsetof(mm7::MapRoom, floors_size) == 4);
	static_assert(offsetof(mm7::MapRoom, floors) == 8);
	static_assert(offsetof(mm7::MapRoom, walls_size) == 12);
	static_assert(offsetof(mm7::MapRoom, walls) == 16);
	static_assert(offsetof(mm7::MapRoom, ceils_size) == 20);
	static_assert(offsetof(mm7::MapRoom, ceils) == 24);
	static_assert(offsetof(mm7::MapRoom, fluids_size) == 28);
	static_assert(offsetof(mm7::MapRoom, fluids) == 32);
	static_assert(offsetof(mm7::MapRoom, portals_size) == 36);
	static_assert(offsetof(mm7::MapRoom, portals) == 40);
	static_assert(offsetof(mm7::MapRoom, drawFacets_size) == 44);
	static_assert(offsetof(mm7::MapRoom, nonBSPDrawFacetsCount) == 46);
	static_assert(offsetof(mm7::MapRoom, drawFacets) == 48);
	static_assert(offsetof(mm7::MapRoom, cogs_size) == 60);
	static_assert(offsetof(mm7::MapRoom, cogs) == 64);
	static_assert(offsetof(mm7::MapRoom, sprites_size) == 68);
	static_assert(offsetof(mm7::MapRoom, sprites) == 72);
	static_assert(offsetof(mm7::MapRoom, markers_size) == 76);
	static_assert(offsetof(mm7::MapRoom, markers) == 80);
	static_assert(offsetof(mm7::MapRoom, lights_size) == 84);
	static_assert(offsetof(mm7::MapRoom, lights) == 88);
	static_assert(offsetof(mm7::MapRoom, darkness) == 98);
	static_assert(offsetof(mm7::MapRoom, firstBSPNode) == 100);
	static_assert(offsetof(mm7::MapRoom, exitTag) == 103);
	static_assert(offsetof(mm7::MapRoom, minX) == 104);
	static_assert(offsetof(mm7::MapRoom, maxX) == 106);
	static_assert(offsetof(mm7::MapRoom, minY) == 108);
	static_assert(offsetof(mm7::MapRoom, maxY) == 110);
	static_assert(offsetof(mm7::MapRoom, minZ) == 112);
	static_assert(offsetof(mm7::MapRoom, maxZ) == 114);



	struct MapLight // size: 0x10
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
		int16_t radius; // 0x6 (6 decimal)
		uint8_t r; // 0x8 (8 decimal)
		uint8_t g; // 0x9 (9 decimal)
		uint8_t b; // 0xA (10 decimal)
		uint8_t type; // 0xB (11 decimal)
		union
		{
			uint16_t bits; // 0xC (12 decimal)
			struct
			{
				SKIPBITS(3);
				bool off : 1; // 0xC (12 decimal), bit index 4
			};
		};
		int16_t brightness; // 0xE (14 decimal)
	};
	static_assert(sizeof(mm7::MapLight) == 0x10, "Invalid \"mm7::MapLight\" structure size");
	static_assert(offsetof(mm7::MapLight, y) == 2);
	static_assert(offsetof(mm7::MapLight, z) == 4);
	static_assert(offsetof(mm7::MapLight, radius) == 6);
	static_assert(offsetof(mm7::MapLight, r) == 8);
	static_assert(offsetof(mm7::MapLight, g) == 9);
	static_assert(offsetof(mm7::MapLight, b) == 10);
	static_assert(offsetof(mm7::MapLight, type) == 11);
	static_assert(offsetof(mm7::MapLight, bits) == 12);
	static_assert(offsetof(mm7::MapLight, brightness) == 14);



	struct MapFacet // size: 0x60
	{
		union
		{
			std::array<float, 3> normalF; // 0x0 (0 decimal) | MMExt info: normal float
			struct
			{
				float normalFX; // 0x0 (0 decimal) | MMExt info: normal X float
				float normalFY; // 0x4 (4 decimal) | MMExt info: normal Y float
				float normalFZ; // 0x8 (8 decimal) | MMExt info: normal Z float
			};
		};
		float normalFDistance; // 0xC (12 decimal) | MMExt info: normal distance float
		union
		{
			std::array<int32_t, 3> normal; // 0x10 (16 decimal) | MMExt info: normal fixed pt (0..0x10000)
			struct
			{
				int32_t normalX; // 0x10 (16 decimal) | MMExt info: normal X fixed pt (0..0x10000)
				int32_t normalY; // 0x14 (20 decimal) | MMExt info: normal Y fixed pt (0..0x10000)
				int32_t normalZ; // 0x18 (24 decimal) | MMExt info: normal Z fixed pt (0..0x10000)
			};
		};
		int32_t normalDistance; // 0x1C (28 decimal) | MMExt info: normal distance fixed pt (0..0x10000)
		int32_t ZCalc1; // 0x20 (32 decimal) | MMExt info:   !Lua[[= -(NormalX * 2^16) / NormalZ         ]](or 0 if 'NormalZ' is 0)
		int32_t ZCalc2; // 0x24 (36 decimal) | MMExt info:   !Lua[[= -(NormalY * 2^16) / NormalZ         ]](or 0 if 'NormalZ' is 0)
		int32_t ZCalc3; // 0x28 (40 decimal) | MMExt info:   !Lua[[= -(NormalDistance * 2^16) / NormalZ  ]](or 0 if 'NormalZ' is 0)
		union
		{
			uint32_t bits; // 0x2C (44 decimal)
			struct
			{
				bool isPortal : 1; // 0x2C (44 decimal), bit index 7
				bool isSecret : 1; // 0x2C (44 decimal), bit index 6
				bool scrollDown : 1; // 0x2C (44 decimal), bit index 5
				bool alignTop : 1; // 0x2C (44 decimal), bit index 4
				bool isWater : 1; // 0x2C (44 decimal), bit index 3
				bool scrollUp : 1; // 0x2C (44 decimal), bit index 2
				bool scrollLeft : 1; // 0x2C (44 decimal), bit index 1
				SKIPBITS(1);
				bool projectToXY : 1; // 0x2D (45 decimal), bit index 7
				bool projectToXZ : 1; // 0x2D (45 decimal), bit index 6
				bool projectToYZ : 1; // 0x2D (45 decimal), bit index 5
				bool scrollRight : 1; // 0x2D (45 decimal), bit index 4
				bool alignLeft : 1; // 0x2D (45 decimal), bit index 3
				bool invisible : 1; // 0x2D (45 decimal), bit index 2
				bool animatedTFT : 1; // 0x2D (45 decimal), bit index 1
				bool alignRight : 1; // 0x2D (45 decimal), bit index 0
				SKIPBITS(1);
				bool alignBottom : 1; // 0x2E (46 decimal), bit index 6
				bool moveByDoor : 1; // 0x2E (46 decimal), bit index 5
				SKIPBITS(1);
				bool isEventJustHint : 1; // 0x2E (46 decimal), bit index 3
				bool alternativeSound : 1; // 0x2E (46 decimal), bit index 2
				bool isSky : 1; // 0x2E (46 decimal), bit index 1
				bool flipU : 1; // 0x2E (46 decimal), bit index 0
				bool flipV : 1; // 0x2F (47 decimal), bit index 7
				bool triggerByClick : 1; // 0x2F (47 decimal), bit index 6
				bool triggerByStep : 1; // 0x2F (47 decimal), bit index 5
				bool triggerByMonster : 1; // 0x2F (47 decimal), bit index 4
				bool triggerByObject : 1; // 0x2F (47 decimal), bit index 3
				bool untouchable : 1; // 0x2F (47 decimal), bit index 2
				bool isLava : 1; // 0x2F (47 decimal), bit index 1
				bool hasData : 1; // 0x2F (47 decimal), bit index 0
			};
		};
		uint16_t* vertexIds; // AccessBeyondLength is active (???) | size field offset is 0x5D | 0x30 (48 decimal)
		int16_t* XInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x5D | 0x34 (52 decimal)
		int16_t* YInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x5D | 0x38 (56 decimal)
		int16_t* ZInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x5D | 0x3C (60 decimal)
		int16_t* UList; // AccessBeyondLength is active (???) | size field offset is 0x5D | 0x40 (64 decimal)
		int16_t* VList; // AccessBeyondLength is active (???) | size field offset is 0x5D | 0x44 (68 decimal)
		uint16_t dataIndex; // 0x48 (72 decimal)
		int16_t bitmapId; // 0x4A (74 decimal) | MMExt info: Bitmap Index
		int16_t room; // 0x4C (76 decimal) | MMExt info: Room #
		int16_t roomBehind; // 0x4E (78 decimal) | MMExt info: Room # Behind facet
		int16_t minX; // 0x50 (80 decimal) | MMExt info: Bounding Box Min X
		int16_t maxX; // 0x52 (82 decimal) | MMExt info: Bounding Box Max X
		int16_t minY; // 0x54 (84 decimal) | MMExt info: Bounding Box Min Y
		int16_t maxY; // 0x56 (86 decimal) | MMExt info: Bounding Box Max Y
		int16_t minZ; // 0x58 (88 decimal) | MMExt info: Bounding Box Min Z
		int16_t maxZ; // 0x5A (90 decimal) | MMExt info: Bounding Box Max Z
		// MMExt info: Polygon type:
		// 0 = empty
		// 1 = wall
		// 2 = unused
		// 3 = horizontal floor
		// 4 = irregular floor (non-horizontal)
		// 5 = horizontal ceiling
		// 6 = irregular ceiling (non-horizontal)
		uint8_t polygonType; // 0x5C (92 decimal)
		union
		{
			uint8_t UList_size; // 0x5D (93 decimal)
			uint8_t VList_size; // 0x5D (93 decimal)
			uint8_t vertexIds_size; // 0x5D (93 decimal)
			uint8_t vertexesCount; // 0x5D (93 decimal)
			uint8_t XInterceptDisplacement_size; // 0x5D (93 decimal)
			uint8_t YInterceptDisplacement_size; // 0x5D (93 decimal)
			uint8_t ZInterceptDisplacement_size; // 0x5D (93 decimal)
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
	static_assert(offsetof(mm7::MapFacet, UList_size) == 93);
	static_assert(offsetof(mm7::MapFacet, VList_size) == 93);
	static_assert(offsetof(mm7::MapFacet, vertexIds_size) == 93);
	static_assert(offsetof(mm7::MapFacet, vertexesCount) == 93);
	static_assert(offsetof(mm7::MapFacet, XInterceptDisplacement_size) == 93);
	static_assert(offsetof(mm7::MapFacet, YInterceptDisplacement_size) == 93);
	static_assert(offsetof(mm7::MapFacet, ZInterceptDisplacement_size) == 93);



	struct FacetData // size: 0x24
	{
		SKIP(12);
		int16_t facetIndex; // 0xC (12 decimal)
		int16_t bitmapIndex; // 0xE (14 decimal)
		int16_t TFTIndex; // 0x10 (16 decimal)
		SKIP(2);
		int16_t bitmapU; // 0x14 (20 decimal) | MMExt info: Bitmap U Offset
		int16_t bitmapV; // 0x16 (22 decimal) | MMExt info: Bitmap V Offset
		int16_t id; // 0x18 (24 decimal)
		int16_t event; // 0x1A (26 decimal)
		SKIP(8);
	};
	static_assert(sizeof(mm7::FacetData) == 0x24, "Invalid \"mm7::FacetData\" structure size");
	static_assert(offsetof(mm7::FacetData, facetIndex) == 12);
	static_assert(offsetof(mm7::FacetData, bitmapIndex) == 14);
	static_assert(offsetof(mm7::FacetData, TFTIndex) == 16);
	static_assert(offsetof(mm7::FacetData, bitmapU) == 20);
	static_assert(offsetof(mm7::FacetData, bitmapV) == 22);
	static_assert(offsetof(mm7::FacetData, id) == 24);
	static_assert(offsetof(mm7::FacetData, event) == 26);



	struct MapDoor // size: 0x50
	{
		union
		{
			uint32_t bits; // 0x0 (0 decimal)
			struct
			{
				bool startState2 : 1; // 0x0 (0 decimal), bit index 7
				bool silentMove : 1; // 0x0 (0 decimal), bit index 6
				bool noSound : 1; // 0x0 (0 decimal), bit index 5
				bool stopped : 1; // 0x0 (0 decimal), bit index 4
			};
		};
		int32_t id; // 0x4 (4 decimal)
		int32_t timeStep; // 0x8 (8 decimal) | MMExt info: time since triggered
		union
		{
			std::array<int32_t, 3> direction; // 0xC (12 decimal)
			struct
			{
				int32_t directionX; // 0xC (12 decimal)
				int32_t directionY; // 0x10 (16 decimal)
				int32_t directionZ; // 0x14 (20 decimal)
			};
		};
		int32_t moveLength; // 0x18 (24 decimal)
		union
		{
			int32_t openSpeed; // 0x1C (28 decimal) | MMExt info: State 3 velocity (speed*time/128 = position)
			int32_t speed2; // 0x1C (28 decimal) | MMExt info: State 3 velocity (speed*time/128 = position)
		};
		union
		{
			int32_t closeSpeed; // 0x20 (32 decimal) | MMExt info: State 1 velocity
			int32_t speed1; // 0x20 (32 decimal) | MMExt info: State 1 velocity (speed*time/128 = position)
		};
		int16_t* vertexIds; // size field offset is 0x44 | 0x24 (36 decimal)
		int16_t* facetIds; // size field offset is 0x46 | 0x28 (40 decimal)
		int16_t* roomIds; // size field offset is 0x48 | 0x2C (44 decimal)
		int16_t* facetStartU; // size field offset is 0x46 | 0x30 (48 decimal)
		int16_t* facetStartV; // size field offset is 0x46 | 0x34 (52 decimal)
		int16_t* vertexStartX; // size field offset is 0x4A | 0x38 (56 decimal)
		int16_t* vertexStartY; // size field offset is 0x4A | 0x3C (60 decimal)
		int16_t* vertexStartZ; // size field offset is 0x4A | 0x40 (64 decimal)
		uint16_t vertexIds_size; // 0x44 (68 decimal)
		union
		{
			uint16_t facetIds_size; // 0x46 (70 decimal)
			uint16_t facetStartU_size; // 0x46 (70 decimal)
			uint16_t facetStartV_size; // 0x46 (70 decimal)
		};
		uint16_t roomIds_size; // 0x48 (72 decimal)
		union
		{
			uint16_t vertexStartX_size; // 0x4A (74 decimal)
			uint16_t vertexStartY_size; // 0x4A (74 decimal)
			uint16_t vertexStartZ_size; // 0x4A (74 decimal)
		};
		// MMExt info: 'State' compared with evt.SetDoorState:
		// 0 = state (0)
		// 1 = move to (1)
		// 2 = state (1)
		// 3 = move to (0)
		int16_t state; // 0x4C (76 decimal)
		SKIP(2);
	};
	static_assert(sizeof(mm7::MapDoor) == 0x50, "Invalid \"mm7::MapDoor\" structure size");
	static_assert(offsetof(mm7::MapDoor, id) == 4);
	static_assert(offsetof(mm7::MapDoor, timeStep) == 8);
	static_assert(offsetof(mm7::MapDoor, direction) == 12);
	static_assert(offsetof(mm7::MapDoor, directionX) == 12);
	static_assert(offsetof(mm7::MapDoor, directionY) == 16);
	static_assert(offsetof(mm7::MapDoor, directionZ) == 20);
	static_assert(offsetof(mm7::MapDoor, moveLength) == 24);
	static_assert(offsetof(mm7::MapDoor, openSpeed) == 28);
	static_assert(offsetof(mm7::MapDoor, speed2) == 28);
	static_assert(offsetof(mm7::MapDoor, closeSpeed) == 32);
	static_assert(offsetof(mm7::MapDoor, speed1) == 32);
	static_assert(offsetof(mm7::MapDoor, vertexIds) == 36);
	static_assert(offsetof(mm7::MapDoor, facetIds) == 40);
	static_assert(offsetof(mm7::MapDoor, roomIds) == 44);
	static_assert(offsetof(mm7::MapDoor, facetStartU) == 48);
	static_assert(offsetof(mm7::MapDoor, facetStartV) == 52);
	static_assert(offsetof(mm7::MapDoor, vertexStartX) == 56);
	static_assert(offsetof(mm7::MapDoor, vertexStartY) == 60);
	static_assert(offsetof(mm7::MapDoor, vertexStartZ) == 64);
	static_assert(offsetof(mm7::MapDoor, vertexIds_size) == 68);
	static_assert(offsetof(mm7::MapDoor, facetIds_size) == 70);
	static_assert(offsetof(mm7::MapDoor, facetStartU_size) == 70);
	static_assert(offsetof(mm7::MapDoor, facetStartV_size) == 70);
	static_assert(offsetof(mm7::MapDoor, roomIds_size) == 72);
	static_assert(offsetof(mm7::MapDoor, vertexStartX_size) == 74);
	static_assert(offsetof(mm7::MapDoor, vertexStartY_size) == 74);
	static_assert(offsetof(mm7::MapDoor, vertexStartZ_size) == 74);
	static_assert(offsetof(mm7::MapDoor, state) == 76);



	struct MapChest // size: 0x14CC
	{
		int16_t chestPicture; // 0x0 (0 decimal) | MMExt info: 0..7  chest id
		union
		{
			uint16_t bits; // 0x2 (2 decimal)
			struct
			{
				bool trapped : 1; // 0x2 (2 decimal), bit index 7
				bool itemsPlaced : 1; // 0x2 (2 decimal), bit index 6
				bool identified : 1; // 0x2 (2 decimal), bit index 5
			};
		};
		std::array<mm7::Item, 140> items; // MMExt: 1..140, here 0..139 | 0x4 (4 decimal)
		std::array<int16_t, 140> inventory; // 0x13B4 (5044 decimal) | MMExt info: ('Items' index) for main item cell,  -(1 + main 'Inventory' cell index) for other cells
	};
	static_assert(sizeof(mm7::MapChest) == 0x14CC, "Invalid \"mm7::MapChest\" structure size");
	static_assert(offsetof(mm7::MapChest, bits) == 2);
	static_assert(offsetof(mm7::MapChest, items) == 4);
	static_assert(offsetof(mm7::MapChest, inventory) == 5044);
}
namespace mm8
{
	struct MapVertex // size: 0x6
	{
		union
		{
			int16_t x; // 0x0 (0 decimal)
			int16_t _1; // 0x0 (0 decimal)
		};
		union
		{
			int16_t y; // 0x2 (2 decimal)
			int16_t _2; // 0x2 (2 decimal)
		};
		union
		{
			int16_t z; // 0x4 (4 decimal)
			int16_t _3; // 0x4 (4 decimal)
		};
	};
	static_assert(sizeof(mm8::MapVertex) == 0x6, "Invalid \"mm8::MapVertex\" structure size");
	static_assert(offsetof(mm8::MapVertex, y) == 2);
	static_assert(offsetof(mm8::MapVertex, _2) == 2);
	static_assert(offsetof(mm8::MapVertex, z) == 4);
	static_assert(offsetof(mm8::MapVertex, _3) == 4);



	struct MapSprite // size: 0x20
	{
		union
		{
			int16_t decListId; // 0x0 (0 decimal)
			std::array<uint8_t, 2> decName; // Unknown type | 0x0 (0 decimal)
		};
		union
		{
			uint16_t bits; // 0x2 (2 decimal)
			struct
			{
				bool triggerByTouch : 1; // 0x2 (2 decimal), bit index 7
				bool triggerByMonster : 1; // 0x2 (2 decimal), bit index 6
				bool triggerByObject : 1; // 0x2 (2 decimal), bit index 5
				bool showOnMap : 1; // 0x2 (2 decimal), bit index 4
				bool isChest : 1; // 0x2 (2 decimal), bit index 3
				bool invisible : 1; // 0x3 (3 decimal), bit index 2
				bool isObeliskChest : 1; // 0x3 (3 decimal), bit index 1
			};
		};
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
		int32_t direction; // 0x10 (16 decimal)
		int16_t id; // 0x14 (20 decimal)
		int16_t event; // 0x16 (22 decimal) | MMExt info: normal event
		int16_t triggerRadius; // 0x18 (24 decimal)
		SKIP(2);
		int16_t eventVariable; // 0x1C (28 decimal) | MMExt info: event variable for barrels etc.
		SKIP(2);
	};
	static_assert(sizeof(mm8::MapSprite) == 0x20, "Invalid \"mm8::MapSprite\" structure size");
	static_assert(offsetof(mm8::MapSprite, bits) == 2);
	static_assert(offsetof(mm8::MapSprite, pos) == 4);
	static_assert(offsetof(mm8::MapSprite, x) == 4);
	static_assert(offsetof(mm8::MapSprite, y) == 8);
	static_assert(offsetof(mm8::MapSprite, z) == 12);
	static_assert(offsetof(mm8::MapSprite, direction) == 16);
	static_assert(offsetof(mm8::MapSprite, id) == 20);
	static_assert(offsetof(mm8::MapSprite, event) == 22);
	static_assert(offsetof(mm8::MapSprite, triggerRadius) == 24);
	static_assert(offsetof(mm8::MapSprite, eventVariable) == 28);



	struct MapRoom // size: 0x78
	{
		union
		{
			uint32_t bits; // 0x0 (0 decimal)
			struct
			{
				SKIPBITS(3);
				bool hasNonVerticalPortals : 1; // 0x0 (0 decimal), bit index 4
				bool hasBSP : 1; // 0x0 (0 decimal), bit index 3
			};
		};
		int32_t eaxEnvironment; // 0x4 (4 decimal)
		uint16_t floors_size; // 0x8 (8 decimal)
		SKIP(2);
		int16_t* floors; // size field offset is 0x8 | 0xC (12 decimal)
		uint16_t walls_size; // 0x10 (16 decimal)
		SKIP(2);
		int16_t* walls; // size field offset is 0x10 | 0x14 (20 decimal)
		uint16_t ceils_size; // 0x18 (24 decimal)
		SKIP(2);
		int16_t* ceils; // size field offset is 0x18 | 0x1C (28 decimal)
		uint16_t fluids_size; // 0x20 (32 decimal)
		SKIP(2);
		int16_t* fluids; // size field offset is 0x20 | 0x24 (36 decimal)
		uint16_t portals_size; // 0x28 (40 decimal)
		SKIP(2);
		int16_t* portals; // size field offset is 0x28 | 0x2C (44 decimal)
		uint16_t drawFacets_size; // 0x30 (48 decimal)
		int16_t nonBSPDrawFacetsCount; // 0x32 (50 decimal) | MMExt info: # of non-BSP Node facets to draw
		int16_t* drawFacets; // size field offset is 0x30 | 0x34 (52 decimal) | MMExt info: drawing order
		SKIP(8);
		uint16_t cogs_size; // 0x40 (64 decimal)
		SKIP(2);
		int16_t* cogs; // size field offset is 0x40 | 0x44 (68 decimal)
		uint16_t sprites_size; // 0x48 (72 decimal)
		SKIP(2);
		int16_t* sprites; // size field offset is 0x48 | 0x4C (76 decimal)
		uint16_t markers_size; // 0x50 (80 decimal)
		SKIP(2);
		int16_t* markers; // size field offset is 0x50 | 0x54 (84 decimal)
		uint16_t lights_size; // 0x58 (88 decimal)
		SKIP(2);
		int16_t* lights; // size field offset is 0x58 | 0x5C (92 decimal)
		SKIP(6);
		int16_t darkness; // 0x66 (102 decimal) | MMExt info: Min Ambient Light Level
		int16_t firstBSPNode; // 0x68 (104 decimal) | MMExt info: First BSP Node Index
		SKIP(1);
		uint8_t exitTag; // 0x6B (107 decimal)
		int16_t minX; // 0x6C (108 decimal) | MMExt info: Bounding Box Min X
		int16_t maxX; // 0x6E (110 decimal) | MMExt info: Bounding Box Max X
		int16_t minY; // 0x70 (112 decimal) | MMExt info: Bounding Box Min Y
		int16_t maxY; // 0x72 (114 decimal) | MMExt info: Bounding Box Max Y
		int16_t minZ; // 0x74 (116 decimal) | MMExt info: Bounding Box Min Z
		int16_t maxZ; // 0x76 (118 decimal) | MMExt info: Bounding Box Max Z
	};
	static_assert(sizeof(mm8::MapRoom) == 0x78, "Invalid \"mm8::MapRoom\" structure size");
	static_assert(offsetof(mm8::MapRoom, eaxEnvironment) == 4);
	static_assert(offsetof(mm8::MapRoom, floors_size) == 8);
	static_assert(offsetof(mm8::MapRoom, floors) == 12);
	static_assert(offsetof(mm8::MapRoom, walls_size) == 16);
	static_assert(offsetof(mm8::MapRoom, walls) == 20);
	static_assert(offsetof(mm8::MapRoom, ceils_size) == 24);
	static_assert(offsetof(mm8::MapRoom, ceils) == 28);
	static_assert(offsetof(mm8::MapRoom, fluids_size) == 32);
	static_assert(offsetof(mm8::MapRoom, fluids) == 36);
	static_assert(offsetof(mm8::MapRoom, portals_size) == 40);
	static_assert(offsetof(mm8::MapRoom, portals) == 44);
	static_assert(offsetof(mm8::MapRoom, drawFacets_size) == 48);
	static_assert(offsetof(mm8::MapRoom, nonBSPDrawFacetsCount) == 50);
	static_assert(offsetof(mm8::MapRoom, drawFacets) == 52);
	static_assert(offsetof(mm8::MapRoom, cogs_size) == 64);
	static_assert(offsetof(mm8::MapRoom, cogs) == 68);
	static_assert(offsetof(mm8::MapRoom, sprites_size) == 72);
	static_assert(offsetof(mm8::MapRoom, sprites) == 76);
	static_assert(offsetof(mm8::MapRoom, markers_size) == 80);
	static_assert(offsetof(mm8::MapRoom, markers) == 84);
	static_assert(offsetof(mm8::MapRoom, lights_size) == 88);
	static_assert(offsetof(mm8::MapRoom, lights) == 92);
	static_assert(offsetof(mm8::MapRoom, darkness) == 102);
	static_assert(offsetof(mm8::MapRoom, firstBSPNode) == 104);
	static_assert(offsetof(mm8::MapRoom, exitTag) == 107);
	static_assert(offsetof(mm8::MapRoom, minX) == 108);
	static_assert(offsetof(mm8::MapRoom, maxX) == 110);
	static_assert(offsetof(mm8::MapRoom, minY) == 112);
	static_assert(offsetof(mm8::MapRoom, maxY) == 114);
	static_assert(offsetof(mm8::MapRoom, minZ) == 116);
	static_assert(offsetof(mm8::MapRoom, maxZ) == 118);



	struct MapLight // size: 0x14
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
		int16_t radius; // 0x6 (6 decimal)
		uint8_t r; // 0x8 (8 decimal)
		uint8_t g; // 0x9 (9 decimal)
		uint8_t b; // 0xA (10 decimal)
		uint8_t type; // 0xB (11 decimal)
		union
		{
			uint16_t bits; // 0xC (12 decimal)
			struct
			{
				SKIPBITS(3);
				bool off : 1; // 0xC (12 decimal), bit index 4
			};
		};
		int16_t brightness; // 0xE (14 decimal)
		int32_t id; // 0x10 (16 decimal)
	};
	static_assert(sizeof(mm8::MapLight) == 0x14, "Invalid \"mm8::MapLight\" structure size");
	static_assert(offsetof(mm8::MapLight, y) == 2);
	static_assert(offsetof(mm8::MapLight, z) == 4);
	static_assert(offsetof(mm8::MapLight, radius) == 6);
	static_assert(offsetof(mm8::MapLight, r) == 8);
	static_assert(offsetof(mm8::MapLight, g) == 9);
	static_assert(offsetof(mm8::MapLight, b) == 10);
	static_assert(offsetof(mm8::MapLight, type) == 11);
	static_assert(offsetof(mm8::MapLight, bits) == 12);
	static_assert(offsetof(mm8::MapLight, brightness) == 14);
	static_assert(offsetof(mm8::MapLight, id) == 16);



	struct MapFacet // size: 0x60
	{
		union
		{
			std::array<float, 3> normalF; // 0x0 (0 decimal) | MMExt info: normal float
			struct
			{
				float normalFX; // 0x0 (0 decimal) | MMExt info: normal X float
				float normalFY; // 0x4 (4 decimal) | MMExt info: normal Y float
				float normalFZ; // 0x8 (8 decimal) | MMExt info: normal Z float
			};
		};
		float normalFDistance; // 0xC (12 decimal) | MMExt info: normal distance float
		union
		{
			std::array<int32_t, 3> normal; // 0x10 (16 decimal) | MMExt info: normal fixed pt (0..0x10000)
			struct
			{
				int32_t normalX; // 0x10 (16 decimal) | MMExt info: normal X fixed pt (0..0x10000)
				int32_t normalY; // 0x14 (20 decimal) | MMExt info: normal Y fixed pt (0..0x10000)
				int32_t normalZ; // 0x18 (24 decimal) | MMExt info: normal Z fixed pt (0..0x10000)
			};
		};
		int32_t normalDistance; // 0x1C (28 decimal) | MMExt info: normal distance fixed pt (0..0x10000)
		int32_t ZCalc1; // 0x20 (32 decimal) | MMExt info:   !Lua[[= -(NormalX * 2^16) / NormalZ         ]](or 0 if 'NormalZ' is 0)
		int32_t ZCalc2; // 0x24 (36 decimal) | MMExt info:   !Lua[[= -(NormalY * 2^16) / NormalZ         ]](or 0 if 'NormalZ' is 0)
		int32_t ZCalc3; // 0x28 (40 decimal) | MMExt info:   !Lua[[= -(NormalDistance * 2^16) / NormalZ  ]](or 0 if 'NormalZ' is 0)
		union
		{
			uint32_t bits; // 0x2C (44 decimal)
			struct
			{
				bool isPortal : 1; // 0x2C (44 decimal), bit index 7
				bool isSecret : 1; // 0x2C (44 decimal), bit index 6
				bool scrollDown : 1; // 0x2C (44 decimal), bit index 5
				bool alignTop : 1; // 0x2C (44 decimal), bit index 4
				bool isWater : 1; // 0x2C (44 decimal), bit index 3
				bool scrollUp : 1; // 0x2D (45 decimal), bit index 2
				bool scrollLeft : 1; // 0x2D (45 decimal), bit index 1
				SKIPBITS(1);
				bool projectToXY : 1; // 0x2D (45 decimal), bit index 7
				bool projectToXZ : 1; // 0x2D (45 decimal), bit index 6
				bool projectToYZ : 1; // 0x2D (45 decimal), bit index 5
				bool scrollRight : 1; // 0x2D (45 decimal), bit index 4
				bool alignLeft : 1; // 0x2E (46 decimal), bit index 3
				bool invisible : 1; // 0x2E (46 decimal), bit index 2
				bool animatedTFT : 1; // 0x2E (46 decimal), bit index 1
				bool alignRight : 1; // 0x2E (46 decimal), bit index 0
				SKIPBITS(1);
				bool alignBottom : 1; // 0x2E (46 decimal), bit index 6
				bool moveByDoor : 1; // 0x2E (46 decimal), bit index 5
				SKIPBITS(1);
				bool isEventJustHint : 1; // 0x2E (46 decimal), bit index 3
				bool alternativeSound : 1; // 0x2F (47 decimal), bit index 2
				bool isSky : 1; // 0x2F (47 decimal), bit index 1
				bool flipU : 1; // 0x2F (47 decimal), bit index 0
				bool flipV : 1; // 0x2F (47 decimal), bit index 7
				bool triggerByClick : 1; // 0x2F (47 decimal), bit index 6
				bool triggerByStep : 1; // 0x2F (47 decimal), bit index 5
				bool disableEventByCtrlClick : 1; // 0x2F (47 decimal), bit index 4
				bool eventDisabledByCtrlClick : 1; // 0x30 (48 decimal), bit index 3
				bool untouchable : 1; // 0x30 (48 decimal), bit index 2
				bool isLava : 1; // 0x30 (48 decimal), bit index 1
				bool hasData : 1; // 0x30 (48 decimal), bit index 0
			};
		};
		uint16_t* vertexIds; // AccessBeyondLength is active (???) | size field offset is 0x5D | 0x30 (48 decimal)
		int16_t* XInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x5D | 0x34 (52 decimal)
		int16_t* YInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x5D | 0x38 (56 decimal)
		int16_t* ZInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x5D | 0x3C (60 decimal)
		int16_t* UList; // AccessBeyondLength is active (???) | size field offset is 0x5D | 0x40 (64 decimal)
		int16_t* VList; // AccessBeyondLength is active (???) | size field offset is 0x5D | 0x44 (68 decimal)
		uint16_t dataIndex; // 0x48 (72 decimal)
		int16_t bitmapId; // 0x4A (74 decimal) | MMExt info: Bitmap Index
		int16_t room; // 0x4C (76 decimal) | MMExt info: Room #
		int16_t roomBehind; // 0x4E (78 decimal) | MMExt info: Room # Behind facet
		int16_t minX; // 0x50 (80 decimal) | MMExt info: Bounding Box Min X
		int16_t maxX; // 0x52 (82 decimal) | MMExt info: Bounding Box Max X
		int16_t minY; // 0x54 (84 decimal) | MMExt info: Bounding Box Min Y
		int16_t maxY; // 0x56 (86 decimal) | MMExt info: Bounding Box Max Y
		int16_t minZ; // 0x58 (88 decimal) | MMExt info: Bounding Box Min Z
		int16_t maxZ; // 0x5A (90 decimal) | MMExt info: Bounding Box Max Z
		// MMExt info: Polygon type:
		// 0 = empty
		// 1 = wall
		// 2 = unused
		// 3 = horizontal floor
		// 4 = irregular floor (non-horizontal)
		// 5 = horizontal ceiling
		// 6 = irregular ceiling (non-horizontal)
		uint8_t polygonType; // 0x5C (92 decimal)
		union
		{
			uint8_t UList_size; // 0x5D (93 decimal)
			uint8_t VList_size; // 0x5D (93 decimal)
			uint8_t vertexIds_size; // 0x5D (93 decimal)
			uint8_t vertexesCount; // 0x5D (93 decimal)
			uint8_t XInterceptDisplacement_size; // 0x5D (93 decimal)
			uint8_t YInterceptDisplacement_size; // 0x5D (93 decimal)
			uint8_t ZInterceptDisplacement_size; // 0x5D (93 decimal)
		};
		SKIP(2);
	};
	static_assert(sizeof(mm8::MapFacet) == 0x60, "Invalid \"mm8::MapFacet\" structure size");
	static_assert(offsetof(mm8::MapFacet, normalFY) == 4);
	static_assert(offsetof(mm8::MapFacet, normalFZ) == 8);
	static_assert(offsetof(mm8::MapFacet, normalFDistance) == 12);
	static_assert(offsetof(mm8::MapFacet, normal) == 16);
	static_assert(offsetof(mm8::MapFacet, normalX) == 16);
	static_assert(offsetof(mm8::MapFacet, normalY) == 20);
	static_assert(offsetof(mm8::MapFacet, normalZ) == 24);
	static_assert(offsetof(mm8::MapFacet, normalDistance) == 28);
	static_assert(offsetof(mm8::MapFacet, ZCalc1) == 32);
	static_assert(offsetof(mm8::MapFacet, ZCalc2) == 36);
	static_assert(offsetof(mm8::MapFacet, ZCalc3) == 40);
	static_assert(offsetof(mm8::MapFacet, bits) == 44);
	static_assert(offsetof(mm8::MapFacet, vertexIds) == 48);
	static_assert(offsetof(mm8::MapFacet, XInterceptDisplacement) == 52);
	static_assert(offsetof(mm8::MapFacet, YInterceptDisplacement) == 56);
	static_assert(offsetof(mm8::MapFacet, ZInterceptDisplacement) == 60);
	static_assert(offsetof(mm8::MapFacet, UList) == 64);
	static_assert(offsetof(mm8::MapFacet, VList) == 68);
	static_assert(offsetof(mm8::MapFacet, dataIndex) == 72);
	static_assert(offsetof(mm8::MapFacet, bitmapId) == 74);
	static_assert(offsetof(mm8::MapFacet, room) == 76);
	static_assert(offsetof(mm8::MapFacet, roomBehind) == 78);
	static_assert(offsetof(mm8::MapFacet, minX) == 80);
	static_assert(offsetof(mm8::MapFacet, maxX) == 82);
	static_assert(offsetof(mm8::MapFacet, minY) == 84);
	static_assert(offsetof(mm8::MapFacet, maxY) == 86);
	static_assert(offsetof(mm8::MapFacet, minZ) == 88);
	static_assert(offsetof(mm8::MapFacet, maxZ) == 90);
	static_assert(offsetof(mm8::MapFacet, polygonType) == 92);
	static_assert(offsetof(mm8::MapFacet, UList_size) == 93);
	static_assert(offsetof(mm8::MapFacet, VList_size) == 93);
	static_assert(offsetof(mm8::MapFacet, vertexIds_size) == 93);
	static_assert(offsetof(mm8::MapFacet, vertexesCount) == 93);
	static_assert(offsetof(mm8::MapFacet, XInterceptDisplacement_size) == 93);
	static_assert(offsetof(mm8::MapFacet, YInterceptDisplacement_size) == 93);
	static_assert(offsetof(mm8::MapFacet, ZInterceptDisplacement_size) == 93);



	struct FacetData // size: 0x24
	{
		SKIP(12);
		int16_t facetIndex; // 0xC (12 decimal)
		int16_t bitmapIndex; // 0xE (14 decimal)
		int16_t TFTIndex; // 0x10 (16 decimal)
		SKIP(2);
		int16_t bitmapU; // 0x14 (20 decimal) | MMExt info: Bitmap U Offset
		int16_t bitmapV; // 0x16 (22 decimal) | MMExt info: Bitmap V Offset
		int16_t id; // 0x18 (24 decimal)
		int16_t event; // 0x1A (26 decimal)
		SKIP(8);
	};
	static_assert(sizeof(mm8::FacetData) == 0x24, "Invalid \"mm8::FacetData\" structure size");
	static_assert(offsetof(mm8::FacetData, facetIndex) == 12);
	static_assert(offsetof(mm8::FacetData, bitmapIndex) == 14);
	static_assert(offsetof(mm8::FacetData, TFTIndex) == 16);
	static_assert(offsetof(mm8::FacetData, bitmapU) == 20);
	static_assert(offsetof(mm8::FacetData, bitmapV) == 22);
	static_assert(offsetof(mm8::FacetData, id) == 24);
	static_assert(offsetof(mm8::FacetData, event) == 26);



	struct MapDoor // size: 0x50
	{
		union
		{
			uint32_t bits; // 0x0 (0 decimal)
			struct
			{
				bool startState2 : 1; // 0x0 (0 decimal), bit index 7
				bool silentMove : 1; // 0x0 (0 decimal), bit index 6
				bool noSound : 1; // 0x0 (0 decimal), bit index 5
				bool stopped : 1; // 0x0 (0 decimal), bit index 4
			};
		};
		int32_t id; // 0x4 (4 decimal)
		int32_t timeStep; // 0x8 (8 decimal) | MMExt info: time since triggered
		union
		{
			std::array<int32_t, 3> direction; // 0xC (12 decimal)
			struct
			{
				int32_t directionX; // 0xC (12 decimal)
				int32_t directionY; // 0x10 (16 decimal)
				int32_t directionZ; // 0x14 (20 decimal)
			};
		};
		int32_t moveLength; // 0x18 (24 decimal)
		union
		{
			int32_t openSpeed; // 0x1C (28 decimal) | MMExt info: State 3 velocity (speed*time/128 = position)
			int32_t speed2; // 0x1C (28 decimal) | MMExt info: State 3 velocity (speed*time/128 = position)
		};
		union
		{
			int32_t closeSpeed; // 0x20 (32 decimal) | MMExt info: State 1 velocity
			int32_t speed1; // 0x20 (32 decimal) | MMExt info: State 1 velocity (speed*time/128 = position)
		};
		int16_t* vertexIds; // size field offset is 0x44 | 0x24 (36 decimal)
		int16_t* facetIds; // size field offset is 0x46 | 0x28 (40 decimal)
		int16_t* roomIds; // size field offset is 0x48 | 0x2C (44 decimal)
		int16_t* facetStartU; // size field offset is 0x46 | 0x30 (48 decimal)
		int16_t* facetStartV; // size field offset is 0x46 | 0x34 (52 decimal)
		int16_t* vertexStartX; // size field offset is 0x4A | 0x38 (56 decimal)
		int16_t* vertexStartY; // size field offset is 0x4A | 0x3C (60 decimal)
		int16_t* vertexStartZ; // size field offset is 0x4A | 0x40 (64 decimal)
		uint16_t vertexIds_size; // 0x44 (68 decimal)
		union
		{
			uint16_t facetIds_size; // 0x46 (70 decimal)
			uint16_t facetStartU_size; // 0x46 (70 decimal)
			uint16_t facetStartV_size; // 0x46 (70 decimal)
		};
		uint16_t roomIds_size; // 0x48 (72 decimal)
		union
		{
			uint16_t vertexStartX_size; // 0x4A (74 decimal)
			uint16_t vertexStartY_size; // 0x4A (74 decimal)
			uint16_t vertexStartZ_size; // 0x4A (74 decimal)
		};
		// MMExt info: 'State' compared with evt.SetDoorState:
		// 0 = state (0)
		// 1 = move to (1)
		// 2 = state (1)
		// 3 = move to (0)
		int16_t state; // 0x4C (76 decimal)
		SKIP(2);
	};
	static_assert(sizeof(mm8::MapDoor) == 0x50, "Invalid \"mm8::MapDoor\" structure size");
	static_assert(offsetof(mm8::MapDoor, id) == 4);
	static_assert(offsetof(mm8::MapDoor, timeStep) == 8);
	static_assert(offsetof(mm8::MapDoor, direction) == 12);
	static_assert(offsetof(mm8::MapDoor, directionX) == 12);
	static_assert(offsetof(mm8::MapDoor, directionY) == 16);
	static_assert(offsetof(mm8::MapDoor, directionZ) == 20);
	static_assert(offsetof(mm8::MapDoor, moveLength) == 24);
	static_assert(offsetof(mm8::MapDoor, openSpeed) == 28);
	static_assert(offsetof(mm8::MapDoor, speed2) == 28);
	static_assert(offsetof(mm8::MapDoor, closeSpeed) == 32);
	static_assert(offsetof(mm8::MapDoor, speed1) == 32);
	static_assert(offsetof(mm8::MapDoor, vertexIds) == 36);
	static_assert(offsetof(mm8::MapDoor, facetIds) == 40);
	static_assert(offsetof(mm8::MapDoor, roomIds) == 44);
	static_assert(offsetof(mm8::MapDoor, facetStartU) == 48);
	static_assert(offsetof(mm8::MapDoor, facetStartV) == 52);
	static_assert(offsetof(mm8::MapDoor, vertexStartX) == 56);
	static_assert(offsetof(mm8::MapDoor, vertexStartY) == 60);
	static_assert(offsetof(mm8::MapDoor, vertexStartZ) == 64);
	static_assert(offsetof(mm8::MapDoor, vertexIds_size) == 68);
	static_assert(offsetof(mm8::MapDoor, facetIds_size) == 70);
	static_assert(offsetof(mm8::MapDoor, facetStartU_size) == 70);
	static_assert(offsetof(mm8::MapDoor, facetStartV_size) == 70);
	static_assert(offsetof(mm8::MapDoor, roomIds_size) == 72);
	static_assert(offsetof(mm8::MapDoor, vertexStartX_size) == 74);
	static_assert(offsetof(mm8::MapDoor, vertexStartY_size) == 74);
	static_assert(offsetof(mm8::MapDoor, vertexStartZ_size) == 74);
	static_assert(offsetof(mm8::MapDoor, state) == 76);



	struct MapChest // size: 0x14CC
	{
		int16_t chestPicture; // 0x0 (0 decimal) | MMExt info: 0..7  chest id
		union
		{
			uint16_t bits; // 0x2 (2 decimal)
			struct
			{
				bool trapped : 1; // 0x2 (2 decimal), bit index 7
				bool itemsPlaced : 1; // 0x2 (2 decimal), bit index 6
				bool identified : 1; // 0x2 (2 decimal), bit index 5
			};
		};
		std::array<mm8::Item, 140> items; // MMExt: 1..140, here 0..139 | 0x4 (4 decimal)
		std::array<int16_t, 140> inventory; // 0x13B4 (5044 decimal) | MMExt info: ('Items' index) for main item cell,  -(1 + main 'Inventory' cell index) for other cells
	};
	static_assert(sizeof(mm8::MapChest) == 0x14CC, "Invalid \"mm8::MapChest\" structure size");
	static_assert(offsetof(mm8::MapChest, bits) == 2);
	static_assert(offsetof(mm8::MapChest, items) == 4);
	static_assert(offsetof(mm8::MapChest, inventory) == 5044);
}

#pragma pack(pop)