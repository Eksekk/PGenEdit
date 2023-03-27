#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct FacetData // size: 0x24
	{
		SKIP(12);
		int16_t facetIndex;
		int16_t bitmapIndex;
		int16_t TFTIndex;
		SKIP(2);
		int16_t bitmapU;
		int16_t bitmapV;
		int16_t id;
		int16_t event;
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



	struct MapFacet // size: 0x50
	{
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
				SKIPBITS(3);
				bool isWater : 1;
				SKIPBITS(3);
				bool projectToXY : 1;
				bool projectToXZ : 1;
				bool projectToYZ : 1;
				SKIPBITS(2);
				bool invisible : 1;
				bool animatedTFT : 1;
				SKIPBITS(1); // skipping 0 bytes and 3 bits, in total 3 bits
				SKIPBITS(2);
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
		uint16_t* vertexIds; // AccessBeyondLength is active (???) | size field offset is 0x4D
		int16_t* XInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x4D
		int16_t* YInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x4D
		int16_t* ZInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x4D
		int16_t* UList; // AccessBeyondLength is active (???) | size field offset is 0x4D
		int16_t* VList; // AccessBeyondLength is active (???) | size field offset is 0x4D
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
			uint8_t YInterceptDisplacement_size;
			uint8_t vertexIds_size;
			uint8_t VList_size;
			uint8_t ZInterceptDisplacement_size;
			uint8_t vertexesCount;
			uint8_t UList_size;
			uint8_t XInterceptDisplacement_size;
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
	static_assert(offsetof(mm6::MapFacet, YInterceptDisplacement_size) == 77);
	static_assert(offsetof(mm6::MapFacet, vertexIds_size) == 77);
	static_assert(offsetof(mm6::MapFacet, VList_size) == 77);
	static_assert(offsetof(mm6::MapFacet, ZInterceptDisplacement_size) == 77);
	static_assert(offsetof(mm6::MapFacet, vertexesCount) == 77);
	static_assert(offsetof(mm6::MapFacet, UList_size) == 77);
	static_assert(offsetof(mm6::MapFacet, XInterceptDisplacement_size) == 77);



	struct MapLight // size: 0xC
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
		union
		{
			uint16_t bits;
			struct
			{
				SKIPBITS(3);
				bool off : 1;
			};
		};
		int16_t brightness;
		int16_t radius;
	};
	static_assert(sizeof(mm6::MapLight) == 0xC, "Invalid \"mm6::MapLight\" structure size");
	static_assert(offsetof(mm6::MapLight, y) == 2);
	static_assert(offsetof(mm6::MapLight, z) == 4);
	static_assert(offsetof(mm6::MapLight, bits) == 6);
	static_assert(offsetof(mm6::MapLight, brightness) == 8);
	static_assert(offsetof(mm6::MapLight, radius) == 10);



	struct MapRoom // size: 0x74
	{
		union
		{
			uint32_t bits;
			struct
			{
				SKIPBITS(3);
				bool hasNonVerticalPortals : 1;
				bool hasBSP : 1;
			};
		};
		uint16_t floors_size;
		SKIP(2);
		int16_t* floors; // size field offset is 0x4
		uint16_t walls_size;
		SKIP(2);
		int16_t* walls; // size field offset is 0xC
		uint16_t ceils_size;
		SKIP(2);
		int16_t* ceils; // size field offset is 0x14
		uint16_t fluids_size;
		SKIP(2);
		int16_t* fluids; // size field offset is 0x1C
		uint16_t portals_size;
		SKIP(2);
		int16_t* portals; // size field offset is 0x24
		uint16_t drawFacets_size;
		int16_t nonBSPDrawFacetsCount;
		int16_t* drawFacets; // size field offset is 0x2C
		SKIP(8);
		uint16_t cogs_size;
		SKIP(2);
		int16_t* cogs; // size field offset is 0x3C
		uint16_t sprites_size;
		SKIP(2);
		int16_t* sprites; // size field offset is 0x44
		uint16_t markers_size;
		SKIP(2);
		int16_t* markers; // size field offset is 0x4C
		uint16_t lights_size;
		SKIP(2);
		int16_t* lights; // size field offset is 0x54
		SKIP(6);
		int16_t darkness;
		int16_t firstBSPNode;
		SKIP(1);
		uint8_t exitTag;
		int16_t minX;
		int16_t maxX;
		int16_t minY;
		int16_t maxY;
		int16_t minZ;
		int16_t maxZ;
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



	struct MapVertex // size: 0x6
	{
		union
		{
			int16_t _1;
			int16_t x;
		};
		union
		{
			int16_t y;
			int16_t _2;
		};
		union
		{
			int16_t _3;
			int16_t z;
		};
	};
	static_assert(sizeof(mm6::MapVertex) == 0x6, "Invalid \"mm6::MapVertex\" structure size");
	static_assert(offsetof(mm6::MapVertex, y) == 2);
	static_assert(offsetof(mm6::MapVertex, _2) == 2);
	static_assert(offsetof(mm6::MapVertex, _3) == 4);
	static_assert(offsetof(mm6::MapVertex, z) == 4);



	struct MapSprite // size: 0x1C
	{
		union
		{
			int16_t decListId;
			std::array<uint8_t, 2> decName; // Unknown type
		};
		union
		{
			uint16_t bits;
			struct
			{
				bool triggerByTouch : 1;
				bool triggerByMonster : 1;
				bool triggerByObject : 1;
				bool showOnMap : 1;
				bool isChest : 1;
				bool invisible : 1;
				bool isShip : 1;
			};
		};
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
		int16_t eventVariable;
		int16_t event;
		int16_t triggerRadius;
		int16_t directionDegrees;
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



	struct MapDoor // size: 0x50
	{
		union
		{
			uint32_t bits;
			struct
			{
				bool startState2 : 1;
				bool silentMove : 1;
				bool noSound : 1;
				bool stopped : 1;
			};
		};
		int32_t id;
		int32_t timeStep;
		union
		{
			std::array<int32_t, 3> direction;
			struct
			{
				int32_t directionX;
				int32_t directionY;
				int32_t directionZ;
			};
		};
		int32_t moveLength;
		union
		{
			int32_t openSpeed;
			int32_t speed2;
		};
		union
		{
			int32_t closeSpeed;
			int32_t speed1;
		};
		int16_t* vertexIds; // size field offset is 0x44
		int16_t* facetIds; // size field offset is 0x46
		int16_t* roomIds; // size field offset is 0x48
		int16_t* facetStartU; // size field offset is 0x46
		int16_t* facetStartV; // size field offset is 0x46
		int16_t* vertexStartX; // size field offset is 0x4A
		int16_t* vertexStartY; // size field offset is 0x4A
		int16_t* vertexStartZ; // size field offset is 0x4A
		uint16_t vertexIds_size;
		union
		{
			uint16_t facetStartU_size;
			uint16_t facetIds_size;
			uint16_t facetStartV_size;
		};
		uint16_t roomIds_size;
		union
		{
			uint16_t vertexStartX_size;
			uint16_t vertexStartZ_size;
			uint16_t vertexStartY_size;
		};
		int16_t state;
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
	static_assert(offsetof(mm6::MapDoor, facetStartU_size) == 70);
	static_assert(offsetof(mm6::MapDoor, facetIds_size) == 70);
	static_assert(offsetof(mm6::MapDoor, facetStartV_size) == 70);
	static_assert(offsetof(mm6::MapDoor, roomIds_size) == 72);
	static_assert(offsetof(mm6::MapDoor, vertexStartX_size) == 74);
	static_assert(offsetof(mm6::MapDoor, vertexStartZ_size) == 74);
	static_assert(offsetof(mm6::MapDoor, vertexStartY_size) == 74);
	static_assert(offsetof(mm6::MapDoor, state) == 76);



	struct MapChest // size: 0x106C
	{
		int16_t chestPicture;
		union
		{
			uint16_t bits;
			struct
			{
				bool trapped : 1;
				bool itemsPlaced : 1;
				bool identified : 1;
			};
		};
		std::array<mm6::Item, 140> items; // MMExt: 1..140, here 0..139
		std::array<int16_t, 140> inventory;
	};
	static_assert(sizeof(mm6::MapChest) == 0x106C, "Invalid \"mm6::MapChest\" structure size");
	static_assert(offsetof(mm6::MapChest, bits) == 2);
	static_assert(offsetof(mm6::MapChest, items) == 4);
	static_assert(offsetof(mm6::MapChest, inventory) == 3924);
}
namespace mm7
{
	struct MapDoor // size: 0x50
	{
		union
		{
			uint32_t bits;
			struct
			{
				bool startState2 : 1;
				bool silentMove : 1;
				bool noSound : 1;
				bool stopped : 1;
			};
		};
		int32_t id;
		int32_t timeStep;
		union
		{
			std::array<int32_t, 3> direction;
			struct
			{
				int32_t directionX;
				int32_t directionY;
				int32_t directionZ;
			};
		};
		int32_t moveLength;
		union
		{
			int32_t speed2;
			int32_t openSpeed;
		};
		union
		{
			int32_t speed1;
			int32_t closeSpeed;
		};
		int16_t* vertexIds; // size field offset is 0x44
		int16_t* facetIds; // size field offset is 0x46
		int16_t* roomIds; // size field offset is 0x48
		int16_t* facetStartU; // size field offset is 0x46
		int16_t* facetStartV; // size field offset is 0x46
		int16_t* vertexStartX; // size field offset is 0x4A
		int16_t* vertexStartY; // size field offset is 0x4A
		int16_t* vertexStartZ; // size field offset is 0x4A
		uint16_t vertexIds_size;
		union
		{
			uint16_t facetStartV_size;
			uint16_t facetIds_size;
			uint16_t facetStartU_size;
		};
		uint16_t roomIds_size;
		union
		{
			uint16_t vertexStartZ_size;
			uint16_t vertexStartY_size;
			uint16_t vertexStartX_size;
		};
		int16_t state;
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
	static_assert(offsetof(mm7::MapDoor, speed2) == 28);
	static_assert(offsetof(mm7::MapDoor, openSpeed) == 28);
	static_assert(offsetof(mm7::MapDoor, speed1) == 32);
	static_assert(offsetof(mm7::MapDoor, closeSpeed) == 32);
	static_assert(offsetof(mm7::MapDoor, vertexIds) == 36);
	static_assert(offsetof(mm7::MapDoor, facetIds) == 40);
	static_assert(offsetof(mm7::MapDoor, roomIds) == 44);
	static_assert(offsetof(mm7::MapDoor, facetStartU) == 48);
	static_assert(offsetof(mm7::MapDoor, facetStartV) == 52);
	static_assert(offsetof(mm7::MapDoor, vertexStartX) == 56);
	static_assert(offsetof(mm7::MapDoor, vertexStartY) == 60);
	static_assert(offsetof(mm7::MapDoor, vertexStartZ) == 64);
	static_assert(offsetof(mm7::MapDoor, vertexIds_size) == 68);
	static_assert(offsetof(mm7::MapDoor, facetStartV_size) == 70);
	static_assert(offsetof(mm7::MapDoor, facetIds_size) == 70);
	static_assert(offsetof(mm7::MapDoor, facetStartU_size) == 70);
	static_assert(offsetof(mm7::MapDoor, roomIds_size) == 72);
	static_assert(offsetof(mm7::MapDoor, vertexStartZ_size) == 74);
	static_assert(offsetof(mm7::MapDoor, vertexStartY_size) == 74);
	static_assert(offsetof(mm7::MapDoor, vertexStartX_size) == 74);
	static_assert(offsetof(mm7::MapDoor, state) == 76);



	struct MapRoom // size: 0x74
	{
		union
		{
			uint32_t bits;
			struct
			{
				SKIPBITS(3);
				bool hasNonVerticalPortals : 1;
				bool hasBSP : 1;
			};
		};
		uint16_t floors_size;
		SKIP(2);
		int16_t* floors; // size field offset is 0x4
		uint16_t walls_size;
		SKIP(2);
		int16_t* walls; // size field offset is 0xC
		uint16_t ceils_size;
		SKIP(2);
		int16_t* ceils; // size field offset is 0x14
		uint16_t fluids_size;
		SKIP(2);
		int16_t* fluids; // size field offset is 0x1C
		uint16_t portals_size;
		SKIP(2);
		int16_t* portals; // size field offset is 0x24
		uint16_t drawFacets_size;
		int16_t nonBSPDrawFacetsCount;
		int16_t* drawFacets; // size field offset is 0x2C
		SKIP(8);
		uint16_t cogs_size;
		SKIP(2);
		int16_t* cogs; // size field offset is 0x3C
		uint16_t sprites_size;
		SKIP(2);
		int16_t* sprites; // size field offset is 0x44
		uint16_t markers_size;
		SKIP(2);
		int16_t* markers; // size field offset is 0x4C
		uint16_t lights_size;
		SKIP(2);
		int16_t* lights; // size field offset is 0x54
		SKIP(6);
		int16_t darkness;
		int16_t firstBSPNode;
		SKIP(1);
		uint8_t exitTag;
		int16_t minX;
		int16_t maxX;
		int16_t minY;
		int16_t maxY;
		int16_t minZ;
		int16_t maxZ;
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



	struct MapVertex // size: 0x6
	{
		union
		{
			int16_t _1;
			int16_t x;
		};
		union
		{
			int16_t y;
			int16_t _2;
		};
		union
		{
			int16_t z;
			int16_t _3;
		};
	};
	static_assert(sizeof(mm7::MapVertex) == 0x6, "Invalid \"mm7::MapVertex\" structure size");
	static_assert(offsetof(mm7::MapVertex, y) == 2);
	static_assert(offsetof(mm7::MapVertex, _2) == 2);
	static_assert(offsetof(mm7::MapVertex, z) == 4);
	static_assert(offsetof(mm7::MapVertex, _3) == 4);



	struct FacetData // size: 0x24
	{
		SKIP(12);
		int16_t facetIndex;
		int16_t bitmapIndex;
		int16_t TFTIndex;
		SKIP(2);
		int16_t bitmapU;
		int16_t bitmapV;
		int16_t id;
		int16_t event;
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



	struct MapSprite // size: 0x20
	{
		union
		{
			int16_t decListId;
			std::array<uint8_t, 2> decName; // Unknown type
		};
		union
		{
			uint16_t bits;
			struct
			{
				bool triggerByTouch : 1;
				bool triggerByMonster : 1;
				bool triggerByObject : 1;
				bool showOnMap : 1;
				bool isChest : 1;
				bool invisible : 1;
				bool isObeliskChest : 1;
			};
		};
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
		int16_t id;
		int16_t event;
		int16_t triggerRadius;
		int16_t directionDegrees;
		int16_t eventVariable;
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



	struct MapLight // size: 0x10
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
		int16_t radius;
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t type;
		union
		{
			uint16_t bits;
			struct
			{
				SKIPBITS(3);
				bool off : 1;
			};
		};
		int16_t brightness;
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



	struct MapChest // size: 0x14CC
	{
		int16_t chestPicture;
		union
		{
			uint16_t bits;
			struct
			{
				bool trapped : 1;
				bool itemsPlaced : 1;
				bool identified : 1;
			};
		};
		std::array<mm7::Item, 140> items; // MMExt: 1..140, here 0..139
		std::array<int16_t, 140> inventory;
	};
	static_assert(sizeof(mm7::MapChest) == 0x14CC, "Invalid \"mm7::MapChest\" structure size");
	static_assert(offsetof(mm7::MapChest, bits) == 2);
	static_assert(offsetof(mm7::MapChest, items) == 4);
	static_assert(offsetof(mm7::MapChest, inventory) == 5044);
}
namespace mm8
{
	struct MapLight // size: 0x14
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
		int16_t radius;
		uint8_t r;
		uint8_t g;
		uint8_t b;
		uint8_t type;
		union
		{
			uint16_t bits;
			struct
			{
				SKIPBITS(3);
				bool off : 1;
			};
		};
		int16_t brightness;
		int32_t id;
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



	struct FacetData // size: 0x24
	{
		SKIP(12);
		int16_t facetIndex;
		int16_t bitmapIndex;
		int16_t TFTIndex;
		SKIP(2);
		int16_t bitmapU;
		int16_t bitmapV;
		int16_t id;
		int16_t event;
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
			uint32_t bits;
			struct
			{
				bool startState2 : 1;
				bool silentMove : 1;
				bool noSound : 1;
				bool stopped : 1;
			};
		};
		int32_t id;
		int32_t timeStep;
		union
		{
			std::array<int32_t, 3> direction;
			struct
			{
				int32_t directionX;
				int32_t directionY;
				int32_t directionZ;
			};
		};
		int32_t moveLength;
		union
		{
			int32_t openSpeed;
			int32_t speed2;
		};
		union
		{
			int32_t speed1;
			int32_t closeSpeed;
		};
		int16_t* vertexIds; // size field offset is 0x44
		int16_t* facetIds; // size field offset is 0x46
		int16_t* roomIds; // size field offset is 0x48
		int16_t* facetStartU; // size field offset is 0x46
		int16_t* facetStartV; // size field offset is 0x46
		int16_t* vertexStartX; // size field offset is 0x4A
		int16_t* vertexStartY; // size field offset is 0x4A
		int16_t* vertexStartZ; // size field offset is 0x4A
		uint16_t vertexIds_size;
		union
		{
			uint16_t facetStartU_size;
			uint16_t facetStartV_size;
			uint16_t facetIds_size;
		};
		uint16_t roomIds_size;
		union
		{
			uint16_t vertexStartY_size;
			uint16_t vertexStartZ_size;
			uint16_t vertexStartX_size;
		};
		int16_t state;
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
	static_assert(offsetof(mm8::MapDoor, speed1) == 32);
	static_assert(offsetof(mm8::MapDoor, closeSpeed) == 32);
	static_assert(offsetof(mm8::MapDoor, vertexIds) == 36);
	static_assert(offsetof(mm8::MapDoor, facetIds) == 40);
	static_assert(offsetof(mm8::MapDoor, roomIds) == 44);
	static_assert(offsetof(mm8::MapDoor, facetStartU) == 48);
	static_assert(offsetof(mm8::MapDoor, facetStartV) == 52);
	static_assert(offsetof(mm8::MapDoor, vertexStartX) == 56);
	static_assert(offsetof(mm8::MapDoor, vertexStartY) == 60);
	static_assert(offsetof(mm8::MapDoor, vertexStartZ) == 64);
	static_assert(offsetof(mm8::MapDoor, vertexIds_size) == 68);
	static_assert(offsetof(mm8::MapDoor, facetStartU_size) == 70);
	static_assert(offsetof(mm8::MapDoor, facetStartV_size) == 70);
	static_assert(offsetof(mm8::MapDoor, facetIds_size) == 70);
	static_assert(offsetof(mm8::MapDoor, roomIds_size) == 72);
	static_assert(offsetof(mm8::MapDoor, vertexStartY_size) == 74);
	static_assert(offsetof(mm8::MapDoor, vertexStartZ_size) == 74);
	static_assert(offsetof(mm8::MapDoor, vertexStartX_size) == 74);
	static_assert(offsetof(mm8::MapDoor, state) == 76);



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
				bool disableEventByCtrlClick : 1;
				bool eventDisabledByCtrlClick : 1;
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
			uint8_t VList_size;
			uint8_t UList_size;
			uint8_t vertexIds_size;
			uint8_t ZInterceptDisplacement_size;
			uint8_t XInterceptDisplacement_size;
			uint8_t YInterceptDisplacement_size;
			uint8_t vertexesCount;
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
	static_assert(offsetof(mm8::MapFacet, VList_size) == 93);
	static_assert(offsetof(mm8::MapFacet, UList_size) == 93);
	static_assert(offsetof(mm8::MapFacet, vertexIds_size) == 93);
	static_assert(offsetof(mm8::MapFacet, ZInterceptDisplacement_size) == 93);
	static_assert(offsetof(mm8::MapFacet, XInterceptDisplacement_size) == 93);
	static_assert(offsetof(mm8::MapFacet, YInterceptDisplacement_size) == 93);
	static_assert(offsetof(mm8::MapFacet, vertexesCount) == 93);



	struct MapSprite // size: 0x20
	{
		union
		{
			std::array<uint8_t, 2> decName; // Unknown type
			int16_t decListId;
		};
		union
		{
			uint16_t bits;
			struct
			{
				bool triggerByTouch : 1;
				bool triggerByMonster : 1;
				bool triggerByObject : 1;
				bool showOnMap : 1;
				bool isChest : 1;
				bool invisible : 1;
				bool isObeliskChest : 1;
			};
		};
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
		int16_t id;
		int16_t event;
		int16_t triggerRadius;
		SKIP(2);
		int16_t eventVariable;
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



	struct MapVertex // size: 0x6
	{
		union
		{
			int16_t _1;
			int16_t x;
		};
		union
		{
			int16_t _2;
			int16_t y;
		};
		union
		{
			int16_t _3;
			int16_t z;
		};
	};
	static_assert(sizeof(mm8::MapVertex) == 0x6, "Invalid \"mm8::MapVertex\" structure size");
	static_assert(offsetof(mm8::MapVertex, _2) == 2);
	static_assert(offsetof(mm8::MapVertex, y) == 2);
	static_assert(offsetof(mm8::MapVertex, _3) == 4);
	static_assert(offsetof(mm8::MapVertex, z) == 4);



	struct MapRoom // size: 0x78
	{
		union
		{
			uint32_t bits;
			struct
			{
				SKIPBITS(3);
				bool hasNonVerticalPortals : 1;
				bool hasBSP : 1;
			};
		};
		int32_t eaxEnvironment;
		uint16_t floors_size;
		SKIP(2);
		int16_t* floors; // size field offset is 0x8
		uint16_t walls_size;
		SKIP(2);
		int16_t* walls; // size field offset is 0x10
		uint16_t ceils_size;
		SKIP(2);
		int16_t* ceils; // size field offset is 0x18
		uint16_t fluids_size;
		SKIP(2);
		int16_t* fluids; // size field offset is 0x20
		uint16_t portals_size;
		SKIP(2);
		int16_t* portals; // size field offset is 0x28
		uint16_t drawFacets_size;
		int16_t nonBSPDrawFacetsCount;
		int16_t* drawFacets; // size field offset is 0x30
		SKIP(8);
		uint16_t cogs_size;
		SKIP(2);
		int16_t* cogs; // size field offset is 0x40
		uint16_t sprites_size;
		SKIP(2);
		int16_t* sprites; // size field offset is 0x48
		uint16_t markers_size;
		SKIP(2);
		int16_t* markers; // size field offset is 0x50
		uint16_t lights_size;
		SKIP(2);
		int16_t* lights; // size field offset is 0x58
		SKIP(6);
		int16_t darkness;
		int16_t firstBSPNode;
		SKIP(1);
		uint8_t exitTag;
		int16_t minX;
		int16_t maxX;
		int16_t minY;
		int16_t maxY;
		int16_t minZ;
		int16_t maxZ;
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



	struct MapChest // size: 0x14CC
	{
		int16_t chestPicture;
		union
		{
			uint16_t bits;
			struct
			{
				bool trapped : 1;
				bool itemsPlaced : 1;
				bool identified : 1;
			};
		};
		std::array<mm8::Item, 140> items; // MMExt: 1..140, here 0..139
		std::array<int16_t, 140> inventory;
	};
	static_assert(sizeof(mm8::MapChest) == 0x14CC, "Invalid \"mm8::MapChest\" structure size");
	static_assert(offsetof(mm8::MapChest, bits) == 2);
	static_assert(offsetof(mm8::MapChest, items) == 4);
	static_assert(offsetof(mm8::MapChest, inventory) == 5044);
}

#pragma pack(pop)