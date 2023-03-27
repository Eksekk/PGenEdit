#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct ModelFacet // size: 0x134
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
		std::array<int16_t, 20> vertexIds; // AccessBeyondLength is active (???) | size field offset is 0x12E
		std::array<int16_t, 20> UList; // AccessBeyondLength is active (???) | size field offset is 0x12E
		std::array<int16_t, 20> VList; // AccessBeyondLength is active (???) | size field offset is 0x12E
		std::array<int16_t, 20> XInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x12E
		std::array<int16_t, 20> YInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x12E
		std::array<int16_t, 20> ZInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x12E
		int16_t bitmapId;
		int16_t bitmapU;
		int16_t bitmapV;
		int16_t minX;
		int16_t maxX;
		int16_t minY;
		int16_t maxY;
		int16_t minZ;
		int16_t maxZ;
		int16_t id;
		int16_t event;
		SKIP(4);
		std::array<uint8_t, 4> gradientVertexes;
		union
		{
			uint8_t vertexIds_size;
			uint8_t ZInterceptDisplacement_size;
			uint8_t vertexesCount;
			uint8_t VList_size;
			uint8_t UList_size;
			uint8_t YInterceptDisplacement_size;
			uint8_t XInterceptDisplacement_size;
		};
		uint8_t polygonType;
		SKIP(4);
	};
	static_assert(sizeof(mm6::ModelFacet) == 0x134, "Invalid \"mm6::ModelFacet\" structure size");
	static_assert(offsetof(mm6::ModelFacet, normalY) == 4);
	static_assert(offsetof(mm6::ModelFacet, normalZ) == 8);
	static_assert(offsetof(mm6::ModelFacet, normalDistance) == 12);
	static_assert(offsetof(mm6::ModelFacet, ZCalc1) == 16);
	static_assert(offsetof(mm6::ModelFacet, ZCalc2) == 20);
	static_assert(offsetof(mm6::ModelFacet, ZCalc3) == 24);
	static_assert(offsetof(mm6::ModelFacet, bits) == 28);
	static_assert(offsetof(mm6::ModelFacet, vertexIds) == 32);
	static_assert(offsetof(mm6::ModelFacet, UList) == 72);
	static_assert(offsetof(mm6::ModelFacet, VList) == 112);
	static_assert(offsetof(mm6::ModelFacet, XInterceptDisplacement) == 152);
	static_assert(offsetof(mm6::ModelFacet, YInterceptDisplacement) == 192);
	static_assert(offsetof(mm6::ModelFacet, ZInterceptDisplacement) == 232);
	static_assert(offsetof(mm6::ModelFacet, bitmapId) == 272);
	static_assert(offsetof(mm6::ModelFacet, bitmapU) == 274);
	static_assert(offsetof(mm6::ModelFacet, bitmapV) == 276);
	static_assert(offsetof(mm6::ModelFacet, minX) == 278);
	static_assert(offsetof(mm6::ModelFacet, maxX) == 280);
	static_assert(offsetof(mm6::ModelFacet, minY) == 282);
	static_assert(offsetof(mm6::ModelFacet, maxY) == 284);
	static_assert(offsetof(mm6::ModelFacet, minZ) == 286);
	static_assert(offsetof(mm6::ModelFacet, maxZ) == 288);
	static_assert(offsetof(mm6::ModelFacet, id) == 290);
	static_assert(offsetof(mm6::ModelFacet, event) == 292);
	static_assert(offsetof(mm6::ModelFacet, gradientVertexes) == 298);
	static_assert(offsetof(mm6::ModelFacet, vertexIds_size) == 302);
	static_assert(offsetof(mm6::ModelFacet, ZInterceptDisplacement_size) == 302);
	static_assert(offsetof(mm6::ModelFacet, vertexesCount) == 302);
	static_assert(offsetof(mm6::ModelFacet, VList_size) == 302);
	static_assert(offsetof(mm6::ModelFacet, UList_size) == 302);
	static_assert(offsetof(mm6::ModelFacet, YInterceptDisplacement_size) == 302);
	static_assert(offsetof(mm6::ModelFacet, XInterceptDisplacement_size) == 302);
	static_assert(offsetof(mm6::ModelFacet, polygonType) == 303);



	struct ModelVertex // size: 0xC
	{
		union
		{
			int32_t _1;
			int32_t x;
		};
		union
		{
			int32_t y;
			int32_t _2;
		};
		union
		{
			int32_t _3;
			int32_t z;
		};
	};
	static_assert(sizeof(mm6::ModelVertex) == 0xC, "Invalid \"mm6::ModelVertex\" structure size");
	static_assert(offsetof(mm6::ModelVertex, y) == 4);
	static_assert(offsetof(mm6::ModelVertex, _2) == 4);
	static_assert(offsetof(mm6::ModelVertex, _3) == 8);
	static_assert(offsetof(mm6::ModelVertex, z) == 8);



	struct BSPNode // size: 0x8
	{
		int16_t frontNode;
		int16_t backNode;
		int16_t coplanarOffset;
		int16_t coplanarSize;
	};
	static_assert(sizeof(mm6::BSPNode) == 0x8, "Invalid \"mm6::BSPNode\" structure size");
	static_assert(offsetof(mm6::BSPNode, backNode) == 2);
	static_assert(offsetof(mm6::BSPNode, coplanarOffset) == 4);
	static_assert(offsetof(mm6::BSPNode, coplanarSize) == 6);



	struct MapModel // size: 0xBC
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		std::array<char, 32> name2; // fixed size string, requires null terminator
		union
		{
			uint32_t bits;
			struct
			{
				bool showOnMap : 1;
			};
		};
		uint32_t vertexes_size;
		mm6::ModelVertex* vertexes; // size field offset is 0x44
		union
		{
			uint32_t facets_size;
			uint32_t ordering_size;
		};
		int16_t convexFacetsCount;
		SKIP(2);
		mm6::ModelFacet* facets; // size field offset is 0x4C
		int16_t* ordering; // size field offset is 0x4C
		uint32_t BSPNodes_size;
		mm6::BSPNode* BSPNodes; // size field offset is 0x5C
		SKIP(4);
		int32_t gridX;
		int32_t gridY;
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
		int32_t minX;
		int32_t minY;
		int32_t minZ;
		int32_t maxX;
		int32_t maxY;
		int32_t maxZ;
		int32_t BFMinX;
		int32_t BFMinY;
		int32_t BFMinZ;
		int32_t BFMaxX;
		int32_t BFMaxY;
		int32_t BFMaxZ;
		int32_t boxCenterX;
		int32_t boxCenterY;
		int32_t boxCenterZ;
		int32_t boundingRadius;
	};
	static_assert(sizeof(mm6::MapModel) == 0xBC, "Invalid \"mm6::MapModel\" structure size");
	static_assert(offsetof(mm6::MapModel, name2) == 32);
	static_assert(offsetof(mm6::MapModel, bits) == 64);
	static_assert(offsetof(mm6::MapModel, vertexes_size) == 68);
	static_assert(offsetof(mm6::MapModel, vertexes) == 72);
	static_assert(offsetof(mm6::MapModel, facets_size) == 76);
	static_assert(offsetof(mm6::MapModel, ordering_size) == 76);
	static_assert(offsetof(mm6::MapModel, convexFacetsCount) == 80);
	static_assert(offsetof(mm6::MapModel, facets) == 84);
	static_assert(offsetof(mm6::MapModel, ordering) == 88);
	static_assert(offsetof(mm6::MapModel, BSPNodes_size) == 92);
	static_assert(offsetof(mm6::MapModel, BSPNodes) == 96);
	static_assert(offsetof(mm6::MapModel, gridX) == 104);
	static_assert(offsetof(mm6::MapModel, gridY) == 108);
	static_assert(offsetof(mm6::MapModel, pos) == 112);
	static_assert(offsetof(mm6::MapModel, x) == 112);
	static_assert(offsetof(mm6::MapModel, y) == 116);
	static_assert(offsetof(mm6::MapModel, z) == 120);
	static_assert(offsetof(mm6::MapModel, minX) == 124);
	static_assert(offsetof(mm6::MapModel, minY) == 128);
	static_assert(offsetof(mm6::MapModel, minZ) == 132);
	static_assert(offsetof(mm6::MapModel, maxX) == 136);
	static_assert(offsetof(mm6::MapModel, maxY) == 140);
	static_assert(offsetof(mm6::MapModel, maxZ) == 144);
	static_assert(offsetof(mm6::MapModel, BFMinX) == 148);
	static_assert(offsetof(mm6::MapModel, BFMinY) == 152);
	static_assert(offsetof(mm6::MapModel, BFMinZ) == 156);
	static_assert(offsetof(mm6::MapModel, BFMaxX) == 160);
	static_assert(offsetof(mm6::MapModel, BFMaxY) == 164);
	static_assert(offsetof(mm6::MapModel, BFMaxZ) == 168);
	static_assert(offsetof(mm6::MapModel, boxCenterX) == 172);
	static_assert(offsetof(mm6::MapModel, boxCenterY) == 176);
	static_assert(offsetof(mm6::MapModel, boxCenterZ) == 180);
	static_assert(offsetof(mm6::MapModel, boundingRadius) == 184);
}
namespace mm7
{
	struct ModelFacet // size: 0x134
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
		std::array<int16_t, 20> vertexIds; // AccessBeyondLength is active (???) | size field offset is 0x12E
		std::array<int16_t, 20> UList; // AccessBeyondLength is active (???) | size field offset is 0x12E
		std::array<int16_t, 20> VList; // AccessBeyondLength is active (???) | size field offset is 0x12E
		std::array<int16_t, 20> XInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x12E
		std::array<int16_t, 20> YInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x12E
		std::array<int16_t, 20> ZInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x12E
		int16_t bitmapId;
		int16_t bitmapU;
		int16_t bitmapV;
		int16_t minX;
		int16_t maxX;
		int16_t minY;
		int16_t maxY;
		int16_t minZ;
		int16_t maxZ;
		int16_t id;
		int16_t event;
		SKIP(4);
		std::array<uint8_t, 4> gradientVertexes;
		union
		{
			uint8_t ZInterceptDisplacement_size;
			uint8_t VList_size;
			uint8_t YInterceptDisplacement_size;
			uint8_t XInterceptDisplacement_size;
			uint8_t vertexIds_size;
			uint8_t vertexesCount;
			uint8_t UList_size;
		};
		uint8_t polygonType;
		SKIP(4);
	};
	static_assert(sizeof(mm7::ModelFacet) == 0x134, "Invalid \"mm7::ModelFacet\" structure size");
	static_assert(offsetof(mm7::ModelFacet, normalY) == 4);
	static_assert(offsetof(mm7::ModelFacet, normalZ) == 8);
	static_assert(offsetof(mm7::ModelFacet, normalDistance) == 12);
	static_assert(offsetof(mm7::ModelFacet, ZCalc1) == 16);
	static_assert(offsetof(mm7::ModelFacet, ZCalc2) == 20);
	static_assert(offsetof(mm7::ModelFacet, ZCalc3) == 24);
	static_assert(offsetof(mm7::ModelFacet, bits) == 28);
	static_assert(offsetof(mm7::ModelFacet, vertexIds) == 32);
	static_assert(offsetof(mm7::ModelFacet, UList) == 72);
	static_assert(offsetof(mm7::ModelFacet, VList) == 112);
	static_assert(offsetof(mm7::ModelFacet, XInterceptDisplacement) == 152);
	static_assert(offsetof(mm7::ModelFacet, YInterceptDisplacement) == 192);
	static_assert(offsetof(mm7::ModelFacet, ZInterceptDisplacement) == 232);
	static_assert(offsetof(mm7::ModelFacet, bitmapId) == 272);
	static_assert(offsetof(mm7::ModelFacet, bitmapU) == 274);
	static_assert(offsetof(mm7::ModelFacet, bitmapV) == 276);
	static_assert(offsetof(mm7::ModelFacet, minX) == 278);
	static_assert(offsetof(mm7::ModelFacet, maxX) == 280);
	static_assert(offsetof(mm7::ModelFacet, minY) == 282);
	static_assert(offsetof(mm7::ModelFacet, maxY) == 284);
	static_assert(offsetof(mm7::ModelFacet, minZ) == 286);
	static_assert(offsetof(mm7::ModelFacet, maxZ) == 288);
	static_assert(offsetof(mm7::ModelFacet, id) == 290);
	static_assert(offsetof(mm7::ModelFacet, event) == 292);
	static_assert(offsetof(mm7::ModelFacet, gradientVertexes) == 298);
	static_assert(offsetof(mm7::ModelFacet, ZInterceptDisplacement_size) == 302);
	static_assert(offsetof(mm7::ModelFacet, VList_size) == 302);
	static_assert(offsetof(mm7::ModelFacet, YInterceptDisplacement_size) == 302);
	static_assert(offsetof(mm7::ModelFacet, XInterceptDisplacement_size) == 302);
	static_assert(offsetof(mm7::ModelFacet, vertexIds_size) == 302);
	static_assert(offsetof(mm7::ModelFacet, vertexesCount) == 302);
	static_assert(offsetof(mm7::ModelFacet, UList_size) == 302);
	static_assert(offsetof(mm7::ModelFacet, polygonType) == 303);



	struct ModelVertex // size: 0xC
	{
		union
		{
			int32_t _1;
			int32_t x;
		};
		union
		{
			int32_t y;
			int32_t _2;
		};
		union
		{
			int32_t z;
			int32_t _3;
		};
	};
	static_assert(sizeof(mm7::ModelVertex) == 0xC, "Invalid \"mm7::ModelVertex\" structure size");
	static_assert(offsetof(mm7::ModelVertex, y) == 4);
	static_assert(offsetof(mm7::ModelVertex, _2) == 4);
	static_assert(offsetof(mm7::ModelVertex, z) == 8);
	static_assert(offsetof(mm7::ModelVertex, _3) == 8);



	struct BSPNode // size: 0x8
	{
		int16_t frontNode;
		int16_t backNode;
		int16_t coplanarOffset;
		int16_t coplanarSize;
	};
	static_assert(sizeof(mm7::BSPNode) == 0x8, "Invalid \"mm7::BSPNode\" structure size");
	static_assert(offsetof(mm7::BSPNode, backNode) == 2);
	static_assert(offsetof(mm7::BSPNode, coplanarOffset) == 4);
	static_assert(offsetof(mm7::BSPNode, coplanarSize) == 6);



	struct MapModel // size: 0xBC
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		std::array<char, 32> name2; // fixed size string, requires null terminator
		union
		{
			uint32_t bits;
			struct
			{
				bool showOnMap : 1;
			};
		};
		uint32_t vertexes_size;
		mm7::ModelVertex* vertexes; // size field offset is 0x44
		union
		{
			uint32_t facets_size;
			uint32_t ordering_size;
		};
		int16_t convexFacetsCount;
		SKIP(2);
		mm7::ModelFacet* facets; // size field offset is 0x4C
		int16_t* ordering; // size field offset is 0x4C
		uint32_t BSPNodes_size;
		mm7::BSPNode* BSPNodes; // size field offset is 0x5C
		SKIP(4);
		int32_t gridX;
		int32_t gridY;
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
		int32_t minX;
		int32_t minY;
		int32_t minZ;
		int32_t maxX;
		int32_t maxY;
		int32_t maxZ;
		int32_t BFMinX;
		int32_t BFMinY;
		int32_t BFMinZ;
		int32_t BFMaxX;
		int32_t BFMaxY;
		int32_t BFMaxZ;
		int32_t boxCenterX;
		int32_t boxCenterY;
		int32_t boxCenterZ;
		int32_t boundingRadius;
	};
	static_assert(sizeof(mm7::MapModel) == 0xBC, "Invalid \"mm7::MapModel\" structure size");
	static_assert(offsetof(mm7::MapModel, name2) == 32);
	static_assert(offsetof(mm7::MapModel, bits) == 64);
	static_assert(offsetof(mm7::MapModel, vertexes_size) == 68);
	static_assert(offsetof(mm7::MapModel, vertexes) == 72);
	static_assert(offsetof(mm7::MapModel, facets_size) == 76);
	static_assert(offsetof(mm7::MapModel, ordering_size) == 76);
	static_assert(offsetof(mm7::MapModel, convexFacetsCount) == 80);
	static_assert(offsetof(mm7::MapModel, facets) == 84);
	static_assert(offsetof(mm7::MapModel, ordering) == 88);
	static_assert(offsetof(mm7::MapModel, BSPNodes_size) == 92);
	static_assert(offsetof(mm7::MapModel, BSPNodes) == 96);
	static_assert(offsetof(mm7::MapModel, gridX) == 104);
	static_assert(offsetof(mm7::MapModel, gridY) == 108);
	static_assert(offsetof(mm7::MapModel, pos) == 112);
	static_assert(offsetof(mm7::MapModel, x) == 112);
	static_assert(offsetof(mm7::MapModel, y) == 116);
	static_assert(offsetof(mm7::MapModel, z) == 120);
	static_assert(offsetof(mm7::MapModel, minX) == 124);
	static_assert(offsetof(mm7::MapModel, minY) == 128);
	static_assert(offsetof(mm7::MapModel, minZ) == 132);
	static_assert(offsetof(mm7::MapModel, maxX) == 136);
	static_assert(offsetof(mm7::MapModel, maxY) == 140);
	static_assert(offsetof(mm7::MapModel, maxZ) == 144);
	static_assert(offsetof(mm7::MapModel, BFMinX) == 148);
	static_assert(offsetof(mm7::MapModel, BFMinY) == 152);
	static_assert(offsetof(mm7::MapModel, BFMinZ) == 156);
	static_assert(offsetof(mm7::MapModel, BFMaxX) == 160);
	static_assert(offsetof(mm7::MapModel, BFMaxY) == 164);
	static_assert(offsetof(mm7::MapModel, BFMaxZ) == 168);
	static_assert(offsetof(mm7::MapModel, boxCenterX) == 172);
	static_assert(offsetof(mm7::MapModel, boxCenterY) == 176);
	static_assert(offsetof(mm7::MapModel, boxCenterZ) == 180);
	static_assert(offsetof(mm7::MapModel, boundingRadius) == 184);
}
namespace mm8
{
	struct ModelFacet // size: 0x134
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
		std::array<int16_t, 20> vertexIds; // AccessBeyondLength is active (???) | size field offset is 0x12E
		std::array<int16_t, 20> UList; // AccessBeyondLength is active (???) | size field offset is 0x12E
		std::array<int16_t, 20> VList; // AccessBeyondLength is active (???) | size field offset is 0x12E
		std::array<int16_t, 20> XInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x12E
		std::array<int16_t, 20> YInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x12E
		std::array<int16_t, 20> ZInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x12E
		int16_t bitmapId;
		int16_t bitmapU;
		int16_t bitmapV;
		int16_t minX;
		int16_t maxX;
		int16_t minY;
		int16_t maxY;
		int16_t minZ;
		int16_t maxZ;
		int16_t id;
		int16_t event;
		SKIP(4);
		std::array<uint8_t, 4> gradientVertexes;
		union
		{
			uint8_t VList_size;
			uint8_t XInterceptDisplacement_size;
			uint8_t ZInterceptDisplacement_size;
			uint8_t vertexesCount;
			uint8_t vertexIds_size;
			uint8_t UList_size;
			uint8_t YInterceptDisplacement_size;
		};
		uint8_t polygonType;
		SKIP(4);
	};
	static_assert(sizeof(mm8::ModelFacet) == 0x134, "Invalid \"mm8::ModelFacet\" structure size");
	static_assert(offsetof(mm8::ModelFacet, normalY) == 4);
	static_assert(offsetof(mm8::ModelFacet, normalZ) == 8);
	static_assert(offsetof(mm8::ModelFacet, normalDistance) == 12);
	static_assert(offsetof(mm8::ModelFacet, ZCalc1) == 16);
	static_assert(offsetof(mm8::ModelFacet, ZCalc2) == 20);
	static_assert(offsetof(mm8::ModelFacet, ZCalc3) == 24);
	static_assert(offsetof(mm8::ModelFacet, bits) == 28);
	static_assert(offsetof(mm8::ModelFacet, vertexIds) == 32);
	static_assert(offsetof(mm8::ModelFacet, UList) == 72);
	static_assert(offsetof(mm8::ModelFacet, VList) == 112);
	static_assert(offsetof(mm8::ModelFacet, XInterceptDisplacement) == 152);
	static_assert(offsetof(mm8::ModelFacet, YInterceptDisplacement) == 192);
	static_assert(offsetof(mm8::ModelFacet, ZInterceptDisplacement) == 232);
	static_assert(offsetof(mm8::ModelFacet, bitmapId) == 272);
	static_assert(offsetof(mm8::ModelFacet, bitmapU) == 274);
	static_assert(offsetof(mm8::ModelFacet, bitmapV) == 276);
	static_assert(offsetof(mm8::ModelFacet, minX) == 278);
	static_assert(offsetof(mm8::ModelFacet, maxX) == 280);
	static_assert(offsetof(mm8::ModelFacet, minY) == 282);
	static_assert(offsetof(mm8::ModelFacet, maxY) == 284);
	static_assert(offsetof(mm8::ModelFacet, minZ) == 286);
	static_assert(offsetof(mm8::ModelFacet, maxZ) == 288);
	static_assert(offsetof(mm8::ModelFacet, id) == 290);
	static_assert(offsetof(mm8::ModelFacet, event) == 292);
	static_assert(offsetof(mm8::ModelFacet, gradientVertexes) == 298);
	static_assert(offsetof(mm8::ModelFacet, VList_size) == 302);
	static_assert(offsetof(mm8::ModelFacet, XInterceptDisplacement_size) == 302);
	static_assert(offsetof(mm8::ModelFacet, ZInterceptDisplacement_size) == 302);
	static_assert(offsetof(mm8::ModelFacet, vertexesCount) == 302);
	static_assert(offsetof(mm8::ModelFacet, vertexIds_size) == 302);
	static_assert(offsetof(mm8::ModelFacet, UList_size) == 302);
	static_assert(offsetof(mm8::ModelFacet, YInterceptDisplacement_size) == 302);
	static_assert(offsetof(mm8::ModelFacet, polygonType) == 303);



	struct ModelVertex // size: 0xC
	{
		union
		{
			int32_t _1;
			int32_t x;
		};
		union
		{
			int32_t _2;
			int32_t y;
		};
		union
		{
			int32_t _3;
			int32_t z;
		};
	};
	static_assert(sizeof(mm8::ModelVertex) == 0xC, "Invalid \"mm8::ModelVertex\" structure size");
	static_assert(offsetof(mm8::ModelVertex, _2) == 4);
	static_assert(offsetof(mm8::ModelVertex, y) == 4);
	static_assert(offsetof(mm8::ModelVertex, _3) == 8);
	static_assert(offsetof(mm8::ModelVertex, z) == 8);



	struct BSPNode // size: 0x8
	{
		int16_t frontNode;
		int16_t backNode;
		int16_t coplanarOffset;
		int16_t coplanarSize;
	};
	static_assert(sizeof(mm8::BSPNode) == 0x8, "Invalid \"mm8::BSPNode\" structure size");
	static_assert(offsetof(mm8::BSPNode, backNode) == 2);
	static_assert(offsetof(mm8::BSPNode, coplanarOffset) == 4);
	static_assert(offsetof(mm8::BSPNode, coplanarSize) == 6);



	struct MapModel // size: 0xBC
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		std::array<char, 32> name2; // fixed size string, requires null terminator
		union
		{
			uint32_t bits;
			struct
			{
				bool showOnMap : 1;
			};
		};
		uint32_t vertexes_size;
		mm8::ModelVertex* vertexes; // size field offset is 0x44
		union
		{
			uint32_t ordering_size;
			uint32_t facets_size;
		};
		int16_t convexFacetsCount;
		SKIP(2);
		mm8::ModelFacet* facets; // size field offset is 0x4C
		int16_t* ordering; // size field offset is 0x4C
		uint32_t BSPNodes_size;
		mm8::BSPNode* BSPNodes; // size field offset is 0x5C
		SKIP(4);
		int32_t gridX;
		int32_t gridY;
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
		int32_t minX;
		int32_t minY;
		int32_t minZ;
		int32_t maxX;
		int32_t maxY;
		int32_t maxZ;
		int32_t BFMinX;
		int32_t BFMinY;
		int32_t BFMinZ;
		int32_t BFMaxX;
		int32_t BFMaxY;
		int32_t BFMaxZ;
		int32_t boxCenterX;
		int32_t boxCenterY;
		int32_t boxCenterZ;
		int32_t boundingRadius;
	};
	static_assert(sizeof(mm8::MapModel) == 0xBC, "Invalid \"mm8::MapModel\" structure size");
	static_assert(offsetof(mm8::MapModel, name2) == 32);
	static_assert(offsetof(mm8::MapModel, bits) == 64);
	static_assert(offsetof(mm8::MapModel, vertexes_size) == 68);
	static_assert(offsetof(mm8::MapModel, vertexes) == 72);
	static_assert(offsetof(mm8::MapModel, ordering_size) == 76);
	static_assert(offsetof(mm8::MapModel, facets_size) == 76);
	static_assert(offsetof(mm8::MapModel, convexFacetsCount) == 80);
	static_assert(offsetof(mm8::MapModel, facets) == 84);
	static_assert(offsetof(mm8::MapModel, ordering) == 88);
	static_assert(offsetof(mm8::MapModel, BSPNodes_size) == 92);
	static_assert(offsetof(mm8::MapModel, BSPNodes) == 96);
	static_assert(offsetof(mm8::MapModel, gridX) == 104);
	static_assert(offsetof(mm8::MapModel, gridY) == 108);
	static_assert(offsetof(mm8::MapModel, pos) == 112);
	static_assert(offsetof(mm8::MapModel, x) == 112);
	static_assert(offsetof(mm8::MapModel, y) == 116);
	static_assert(offsetof(mm8::MapModel, z) == 120);
	static_assert(offsetof(mm8::MapModel, minX) == 124);
	static_assert(offsetof(mm8::MapModel, minY) == 128);
	static_assert(offsetof(mm8::MapModel, minZ) == 132);
	static_assert(offsetof(mm8::MapModel, maxX) == 136);
	static_assert(offsetof(mm8::MapModel, maxY) == 140);
	static_assert(offsetof(mm8::MapModel, maxZ) == 144);
	static_assert(offsetof(mm8::MapModel, BFMinX) == 148);
	static_assert(offsetof(mm8::MapModel, BFMinY) == 152);
	static_assert(offsetof(mm8::MapModel, BFMinZ) == 156);
	static_assert(offsetof(mm8::MapModel, BFMaxX) == 160);
	static_assert(offsetof(mm8::MapModel, BFMaxY) == 164);
	static_assert(offsetof(mm8::MapModel, BFMaxZ) == 168);
	static_assert(offsetof(mm8::MapModel, boxCenterX) == 172);
	static_assert(offsetof(mm8::MapModel, boxCenterY) == 176);
	static_assert(offsetof(mm8::MapModel, boxCenterZ) == 180);
	static_assert(offsetof(mm8::MapModel, boundingRadius) == 184);
}

#pragma pack(pop)