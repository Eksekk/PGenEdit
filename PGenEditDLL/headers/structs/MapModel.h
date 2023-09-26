#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct ModelVertex // size: 0xC
	{
		union
		{
			int32_t x; // 0x0 (0 decimal)
			int32_t _1; // 0x0 (0 decimal)
		};
		union
		{
			int32_t y; // 0x4 (4 decimal)
			int32_t _2; // 0x4 (4 decimal)
		};
		union
		{
			int32_t z; // 0x8 (8 decimal)
			int32_t _3; // 0x8 (8 decimal)
		};
	};
	static_assert(sizeof(mm6::ModelVertex) == 0xC, "Invalid \"mm6::ModelVertex\" structure size");
	static_assert(offsetof(mm6::ModelVertex, y) == 4);
	static_assert(offsetof(mm6::ModelVertex, _2) == 4);
	static_assert(offsetof(mm6::ModelVertex, z) == 8);
	static_assert(offsetof(mm6::ModelVertex, _3) == 8);



	struct ModelFacet // size: 0x134
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
		std::array<int16_t, 20> vertexIds; // AccessBeyondLength is active (???) | size field offset is 0x12E | 0x20 (32 decimal)
		std::array<int16_t, 20> UList; // AccessBeyondLength is active (???) | size field offset is 0x12E | 0x48 (72 decimal)
		std::array<int16_t, 20> VList; // AccessBeyondLength is active (???) | size field offset is 0x12E | 0x70 (112 decimal)
		std::array<int16_t, 20> XInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x12E | 0x98 (152 decimal)
		std::array<int16_t, 20> YInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x12E | 0xC0 (192 decimal)
		std::array<int16_t, 20> ZInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x12E | 0xE8 (232 decimal)
		int16_t bitmapId; // 0x110 (272 decimal)
		int16_t bitmapU; // 0x112 (274 decimal)
		int16_t bitmapV; // 0x114 (276 decimal)
		int16_t minX; // 0x116 (278 decimal) | MMExt info: Bounding Box Min X
		int16_t maxX; // 0x118 (280 decimal) | MMExt info: Bounding Box Max X
		int16_t minY; // 0x11A (282 decimal) | MMExt info: Bounding Box Min Y
		int16_t maxY; // 0x11C (284 decimal) | MMExt info: Bounding Box Max Y
		int16_t minZ; // 0x11E (286 decimal) | MMExt info: Bounding Box Min Z
		int16_t maxZ; // 0x120 (288 decimal) | MMExt info: Bounding Box Max Z
		int16_t id; // 0x122 (290 decimal)
		int16_t event; // 0x124 (292 decimal)
		SKIP(4);
		std::array<uint8_t, 4> gradientVertexes; // 0x12A (298 decimal)
		union
		{
			uint8_t UList_size; // 0x12E (302 decimal)
			uint8_t VList_size; // 0x12E (302 decimal)
			uint8_t vertexIds_size; // 0x12E (302 decimal)
			uint8_t vertexesCount; // 0x12E (302 decimal)
			uint8_t XInterceptDisplacement_size; // 0x12E (302 decimal)
			uint8_t YInterceptDisplacement_size; // 0x12E (302 decimal)
			uint8_t ZInterceptDisplacement_size; // 0x12E (302 decimal)
		};
		// MMExt info: Polygon type:
		// 0 = empty
		// 1 = wall
		// 2 = unused
		// 3 = horizontal floor
		// 4 = irregular floor (non-horizontal)
		// 5 = horizontal ceiling
		// 6 = irregular ceiling (non-horizontal)
		uint8_t polygonType; // 0x12F (303 decimal)
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
	static_assert(offsetof(mm6::ModelFacet, UList_size) == 302);
	static_assert(offsetof(mm6::ModelFacet, VList_size) == 302);
	static_assert(offsetof(mm6::ModelFacet, vertexIds_size) == 302);
	static_assert(offsetof(mm6::ModelFacet, vertexesCount) == 302);
	static_assert(offsetof(mm6::ModelFacet, XInterceptDisplacement_size) == 302);
	static_assert(offsetof(mm6::ModelFacet, YInterceptDisplacement_size) == 302);
	static_assert(offsetof(mm6::ModelFacet, ZInterceptDisplacement_size) == 302);
	static_assert(offsetof(mm6::ModelFacet, polygonType) == 303);



	struct BSPNode // size: 0x8
	{
		int16_t frontNode; // 0x0 (0 decimal)
		int16_t backNode; // 0x2 (2 decimal)
		int16_t coplanarOffset; // 0x4 (4 decimal)
		int16_t coplanarSize; // 0x6 (6 decimal)
	};
	static_assert(sizeof(mm6::BSPNode) == 0x8, "Invalid \"mm6::BSPNode\" structure size");
	static_assert(offsetof(mm6::BSPNode, backNode) == 2);
	static_assert(offsetof(mm6::BSPNode, coplanarOffset) == 4);
	static_assert(offsetof(mm6::BSPNode, coplanarSize) == 6);



	struct MapModel // size: 0xBC
	{
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		std::array<char, 32> name2; // fixed size string, requires null terminator | 0x20 (32 decimal)
		union
		{
			uint32_t bits; // 0x40 (64 decimal)
			struct
			{
				bool showOnMap : 1; // 0x40 (64 decimal), bit index 7
			};
		};
		uint32_t vertexes_size; // 0x44 (68 decimal)
		mm6::ModelVertex* vertexes; // size field offset is 0x44 | 0x48 (72 decimal)
		union
		{
			uint32_t facets_size; // 0x4C (76 decimal)
			uint32_t ordering_size; // 0x4C (76 decimal)
		};
		int16_t convexFacetsCount; // 0x50 (80 decimal)
		SKIP(2);
		mm6::ModelFacet* facets; // size field offset is 0x4C | 0x54 (84 decimal)
		int16_t* ordering; // size field offset is 0x4C | 0x58 (88 decimal)
		uint32_t BSPNodes_size; // 0x5C (92 decimal)
		mm6::BSPNode* BSPNodes; // size field offset is 0x5C | 0x60 (96 decimal)
		SKIP(4);
		int32_t gridX; // 0x68 (104 decimal) | MMExt info: center X
		int32_t gridY; // 0x6C (108 decimal) | MMExt info: center Y
		union
		{
			std::array<int32_t, 3> pos; // 0x70 (112 decimal)
			struct
			{
				int32_t x; // 0x70 (112 decimal)
				int32_t y; // 0x74 (116 decimal)
				int32_t z; // 0x78 (120 decimal)
			};
		};
		int32_t minX; // 0x7C (124 decimal) | MMExt info: Bounding MIN X
		int32_t minY; // 0x80 (128 decimal) | MMExt info: Bounding MIN Y
		int32_t minZ; // 0x84 (132 decimal) | MMExt info: Bounding MIN Z
		int32_t maxX; // 0x88 (136 decimal) | MMExt info: Bounding MAX X
		int32_t maxY; // 0x8C (140 decimal) | MMExt info: Bounding MAX Y
		int32_t maxZ; // 0x90 (144 decimal) | MMExt info: Bounding MAX Z
		int32_t BFMinX; // 0x94 (148 decimal)
		int32_t BFMinY; // 0x98 (152 decimal)
		int32_t BFMinZ; // 0x9C (156 decimal)
		int32_t BFMaxX; // 0xA0 (160 decimal)
		int32_t BFMaxY; // 0xA4 (164 decimal)
		int32_t BFMaxZ; // 0xA8 (168 decimal)
		int32_t boxCenterX; // 0xAC (172 decimal) | MMExt info: Bounding center X
		int32_t boxCenterY; // 0xB0 (176 decimal) | MMExt info: Bounding center Y
		int32_t boxCenterZ; // 0xB4 (180 decimal) | MMExt info: Bounding center Z
		int32_t boundingRadius; // 0xB8 (184 decimal)
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
	struct ModelVertex // size: 0xC
	{
		union
		{
			int32_t x; // 0x0 (0 decimal)
			int32_t _1; // 0x0 (0 decimal)
		};
		union
		{
			int32_t y; // 0x4 (4 decimal)
			int32_t _2; // 0x4 (4 decimal)
		};
		union
		{
			int32_t z; // 0x8 (8 decimal)
			int32_t _3; // 0x8 (8 decimal)
		};
	};
	static_assert(sizeof(mm7::ModelVertex) == 0xC, "Invalid \"mm7::ModelVertex\" structure size");
	static_assert(offsetof(mm7::ModelVertex, y) == 4);
	static_assert(offsetof(mm7::ModelVertex, _2) == 4);
	static_assert(offsetof(mm7::ModelVertex, z) == 8);
	static_assert(offsetof(mm7::ModelVertex, _3) == 8);



	struct ModelFacet // size: 0x134
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
				bool isSecret : 1; // 0x1C (28 decimal), bit index 6
				bool scrollDown : 1; // 0x1C (28 decimal), bit index 5
				bool alignTop : 1; // 0x1C (28 decimal), bit index 4
				bool isWater : 1; // 0x1C (28 decimal), bit index 3
				bool scrollUp : 1; // 0x1C (28 decimal), bit index 2
				bool scrollLeft : 1; // 0x1C (28 decimal), bit index 1
				SKIPBITS(1);
				bool projectToXY : 1; // 0x1D (29 decimal), bit index 7
				bool projectToXZ : 1; // 0x1D (29 decimal), bit index 6
				bool projectToYZ : 1; // 0x1D (29 decimal), bit index 5
				bool scrollRight : 1; // 0x1D (29 decimal), bit index 4
				bool alignLeft : 1; // 0x1D (29 decimal), bit index 3
				bool invisible : 1; // 0x1D (29 decimal), bit index 2
				bool animatedTFT : 1; // 0x1D (29 decimal), bit index 1
				bool alignRight : 1; // 0x1D (29 decimal), bit index 0
				SKIPBITS(1);
				bool alignBottom : 1; // 0x1E (30 decimal), bit index 6
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
		std::array<int16_t, 20> vertexIds; // AccessBeyondLength is active (???) | size field offset is 0x12E | 0x20 (32 decimal)
		std::array<int16_t, 20> UList; // AccessBeyondLength is active (???) | size field offset is 0x12E | 0x48 (72 decimal)
		std::array<int16_t, 20> VList; // AccessBeyondLength is active (???) | size field offset is 0x12E | 0x70 (112 decimal)
		std::array<int16_t, 20> XInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x12E | 0x98 (152 decimal)
		std::array<int16_t, 20> YInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x12E | 0xC0 (192 decimal)
		std::array<int16_t, 20> ZInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x12E | 0xE8 (232 decimal)
		int16_t bitmapId; // 0x110 (272 decimal)
		int16_t bitmapU; // 0x112 (274 decimal)
		int16_t bitmapV; // 0x114 (276 decimal)
		int16_t minX; // 0x116 (278 decimal) | MMExt info: Bounding Box Min X
		int16_t maxX; // 0x118 (280 decimal) | MMExt info: Bounding Box Max X
		int16_t minY; // 0x11A (282 decimal) | MMExt info: Bounding Box Min Y
		int16_t maxY; // 0x11C (284 decimal) | MMExt info: Bounding Box Max Y
		int16_t minZ; // 0x11E (286 decimal) | MMExt info: Bounding Box Min Z
		int16_t maxZ; // 0x120 (288 decimal) | MMExt info: Bounding Box Max Z
		int16_t id; // 0x122 (290 decimal)
		int16_t event; // 0x124 (292 decimal)
		SKIP(4);
		std::array<uint8_t, 4> gradientVertexes; // 0x12A (298 decimal)
		union
		{
			uint8_t UList_size; // 0x12E (302 decimal)
			uint8_t VList_size; // 0x12E (302 decimal)
			uint8_t vertexIds_size; // 0x12E (302 decimal)
			uint8_t vertexesCount; // 0x12E (302 decimal)
			uint8_t XInterceptDisplacement_size; // 0x12E (302 decimal)
			uint8_t YInterceptDisplacement_size; // 0x12E (302 decimal)
			uint8_t ZInterceptDisplacement_size; // 0x12E (302 decimal)
		};
		// MMExt info: Polygon type:
		// 0 = empty
		// 1 = wall
		// 2 = unused
		// 3 = horizontal floor
		// 4 = irregular floor (non-horizontal)
		// 5 = horizontal ceiling
		// 6 = irregular ceiling (non-horizontal)
		uint8_t polygonType; // 0x12F (303 decimal)
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
	static_assert(offsetof(mm7::ModelFacet, UList_size) == 302);
	static_assert(offsetof(mm7::ModelFacet, VList_size) == 302);
	static_assert(offsetof(mm7::ModelFacet, vertexIds_size) == 302);
	static_assert(offsetof(mm7::ModelFacet, vertexesCount) == 302);
	static_assert(offsetof(mm7::ModelFacet, XInterceptDisplacement_size) == 302);
	static_assert(offsetof(mm7::ModelFacet, YInterceptDisplacement_size) == 302);
	static_assert(offsetof(mm7::ModelFacet, ZInterceptDisplacement_size) == 302);
	static_assert(offsetof(mm7::ModelFacet, polygonType) == 303);



	struct BSPNode // size: 0x8
	{
		int16_t frontNode; // 0x0 (0 decimal)
		int16_t backNode; // 0x2 (2 decimal)
		int16_t coplanarOffset; // 0x4 (4 decimal)
		int16_t coplanarSize; // 0x6 (6 decimal)
	};
	static_assert(sizeof(mm7::BSPNode) == 0x8, "Invalid \"mm7::BSPNode\" structure size");
	static_assert(offsetof(mm7::BSPNode, backNode) == 2);
	static_assert(offsetof(mm7::BSPNode, coplanarOffset) == 4);
	static_assert(offsetof(mm7::BSPNode, coplanarSize) == 6);



	struct MapModel // size: 0xBC
	{
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		std::array<char, 32> name2; // fixed size string, requires null terminator | 0x20 (32 decimal)
		union
		{
			uint32_t bits; // 0x40 (64 decimal)
			struct
			{
				bool showOnMap : 1; // 0x40 (64 decimal), bit index 7
			};
		};
		uint32_t vertexes_size; // 0x44 (68 decimal)
		mm7::ModelVertex* vertexes; // size field offset is 0x44 | 0x48 (72 decimal)
		union
		{
			uint32_t facets_size; // 0x4C (76 decimal)
			uint32_t ordering_size; // 0x4C (76 decimal)
		};
		int16_t convexFacetsCount; // 0x50 (80 decimal)
		SKIP(2);
		mm7::ModelFacet* facets; // size field offset is 0x4C | 0x54 (84 decimal)
		int16_t* ordering; // size field offset is 0x4C | 0x58 (88 decimal)
		uint32_t BSPNodes_size; // 0x5C (92 decimal)
		mm7::BSPNode* BSPNodes; // size field offset is 0x5C | 0x60 (96 decimal)
		SKIP(4);
		int32_t gridX; // 0x68 (104 decimal) | MMExt info: center X
		int32_t gridY; // 0x6C (108 decimal) | MMExt info: center Y
		union
		{
			std::array<int32_t, 3> pos; // 0x70 (112 decimal)
			struct
			{
				int32_t x; // 0x70 (112 decimal)
				int32_t y; // 0x74 (116 decimal)
				int32_t z; // 0x78 (120 decimal)
			};
		};
		int32_t minX; // 0x7C (124 decimal) | MMExt info: Bounding MIN X
		int32_t minY; // 0x80 (128 decimal) | MMExt info: Bounding MIN Y
		int32_t minZ; // 0x84 (132 decimal) | MMExt info: Bounding MIN Z
		int32_t maxX; // 0x88 (136 decimal) | MMExt info: Bounding MAX X
		int32_t maxY; // 0x8C (140 decimal) | MMExt info: Bounding MAX Y
		int32_t maxZ; // 0x90 (144 decimal) | MMExt info: Bounding MAX Z
		int32_t BFMinX; // 0x94 (148 decimal)
		int32_t BFMinY; // 0x98 (152 decimal)
		int32_t BFMinZ; // 0x9C (156 decimal)
		int32_t BFMaxX; // 0xA0 (160 decimal)
		int32_t BFMaxY; // 0xA4 (164 decimal)
		int32_t BFMaxZ; // 0xA8 (168 decimal)
		int32_t boxCenterX; // 0xAC (172 decimal) | MMExt info: Bounding center X
		int32_t boxCenterY; // 0xB0 (176 decimal) | MMExt info: Bounding center Y
		int32_t boxCenterZ; // 0xB4 (180 decimal) | MMExt info: Bounding center Z
		int32_t boundingRadius; // 0xB8 (184 decimal)
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
	struct ModelVertex // size: 0xC
	{
		union
		{
			int32_t x; // 0x0 (0 decimal)
			int32_t _1; // 0x0 (0 decimal)
		};
		union
		{
			int32_t y; // 0x4 (4 decimal)
			int32_t _2; // 0x4 (4 decimal)
		};
		union
		{
			int32_t z; // 0x8 (8 decimal)
			int32_t _3; // 0x8 (8 decimal)
		};
	};
	static_assert(sizeof(mm8::ModelVertex) == 0xC, "Invalid \"mm8::ModelVertex\" structure size");
	static_assert(offsetof(mm8::ModelVertex, y) == 4);
	static_assert(offsetof(mm8::ModelVertex, _2) == 4);
	static_assert(offsetof(mm8::ModelVertex, z) == 8);
	static_assert(offsetof(mm8::ModelVertex, _3) == 8);



	struct ModelFacet // size: 0x134
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
				bool isSecret : 1; // 0x1C (28 decimal), bit index 6
				bool scrollDown : 1; // 0x1C (28 decimal), bit index 5
				bool alignTop : 1; // 0x1C (28 decimal), bit index 4
				bool isWater : 1; // 0x1C (28 decimal), bit index 3
				bool scrollUp : 1; // 0x1D (29 decimal), bit index 2
				bool scrollLeft : 1; // 0x1D (29 decimal), bit index 1
				SKIPBITS(1);
				bool projectToXY : 1; // 0x1D (29 decimal), bit index 7
				bool projectToXZ : 1; // 0x1D (29 decimal), bit index 6
				bool projectToYZ : 1; // 0x1D (29 decimal), bit index 5
				bool scrollRight : 1; // 0x1D (29 decimal), bit index 4
				bool alignLeft : 1; // 0x1E (30 decimal), bit index 3
				bool invisible : 1; // 0x1E (30 decimal), bit index 2
				bool animatedTFT : 1; // 0x1E (30 decimal), bit index 1
				bool alignRight : 1; // 0x1E (30 decimal), bit index 0
				SKIPBITS(1);
				bool alignBottom : 1; // 0x1E (30 decimal), bit index 6
				bool moveByDoor : 1; // 0x1E (30 decimal), bit index 5
				SKIPBITS(1);
				bool isEventJustHint : 1; // 0x1E (30 decimal), bit index 3
				bool alternativeSound : 1; // 0x1F (31 decimal), bit index 2
				bool isSky : 1; // 0x1F (31 decimal), bit index 1
				bool flipU : 1; // 0x1F (31 decimal), bit index 0
				bool flipV : 1; // 0x1F (31 decimal), bit index 7
				bool triggerByClick : 1; // 0x1F (31 decimal), bit index 6
				bool triggerByStep : 1; // 0x1F (31 decimal), bit index 5
				bool disableEventByCtrlClick : 1; // 0x1F (31 decimal), bit index 4
				bool eventDisabledByCtrlClick : 1; // 0x20 (32 decimal), bit index 3
				bool untouchable : 1; // 0x20 (32 decimal), bit index 2
				bool isLava : 1; // 0x20 (32 decimal), bit index 1
				bool hasData : 1; // 0x20 (32 decimal), bit index 0
			};
		};
		std::array<int16_t, 20> vertexIds; // AccessBeyondLength is active (???) | size field offset is 0x12E | 0x20 (32 decimal)
		std::array<int16_t, 20> UList; // AccessBeyondLength is active (???) | size field offset is 0x12E | 0x48 (72 decimal)
		std::array<int16_t, 20> VList; // AccessBeyondLength is active (???) | size field offset is 0x12E | 0x70 (112 decimal)
		std::array<int16_t, 20> XInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x12E | 0x98 (152 decimal)
		std::array<int16_t, 20> YInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x12E | 0xC0 (192 decimal)
		std::array<int16_t, 20> ZInterceptDisplacement; // AccessBeyondLength is active (???) | size field offset is 0x12E | 0xE8 (232 decimal)
		int16_t bitmapId; // 0x110 (272 decimal)
		int16_t bitmapU; // 0x112 (274 decimal)
		int16_t bitmapV; // 0x114 (276 decimal)
		int16_t minX; // 0x116 (278 decimal) | MMExt info: Bounding Box Min X
		int16_t maxX; // 0x118 (280 decimal) | MMExt info: Bounding Box Max X
		int16_t minY; // 0x11A (282 decimal) | MMExt info: Bounding Box Min Y
		int16_t maxY; // 0x11C (284 decimal) | MMExt info: Bounding Box Max Y
		int16_t minZ; // 0x11E (286 decimal) | MMExt info: Bounding Box Min Z
		int16_t maxZ; // 0x120 (288 decimal) | MMExt info: Bounding Box Max Z
		int16_t id; // 0x122 (290 decimal)
		int16_t event; // 0x124 (292 decimal)
		SKIP(4);
		std::array<uint8_t, 4> gradientVertexes; // 0x12A (298 decimal)
		union
		{
			uint8_t UList_size; // 0x12E (302 decimal)
			uint8_t VList_size; // 0x12E (302 decimal)
			uint8_t vertexIds_size; // 0x12E (302 decimal)
			uint8_t vertexesCount; // 0x12E (302 decimal)
			uint8_t XInterceptDisplacement_size; // 0x12E (302 decimal)
			uint8_t YInterceptDisplacement_size; // 0x12E (302 decimal)
			uint8_t ZInterceptDisplacement_size; // 0x12E (302 decimal)
		};
		// MMExt info: Polygon type:
		// 0 = empty
		// 1 = wall
		// 2 = unused
		// 3 = horizontal floor
		// 4 = irregular floor (non-horizontal)
		// 5 = horizontal ceiling
		// 6 = irregular ceiling (non-horizontal)
		uint8_t polygonType; // 0x12F (303 decimal)
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
	static_assert(offsetof(mm8::ModelFacet, UList_size) == 302);
	static_assert(offsetof(mm8::ModelFacet, VList_size) == 302);
	static_assert(offsetof(mm8::ModelFacet, vertexIds_size) == 302);
	static_assert(offsetof(mm8::ModelFacet, vertexesCount) == 302);
	static_assert(offsetof(mm8::ModelFacet, XInterceptDisplacement_size) == 302);
	static_assert(offsetof(mm8::ModelFacet, YInterceptDisplacement_size) == 302);
	static_assert(offsetof(mm8::ModelFacet, ZInterceptDisplacement_size) == 302);
	static_assert(offsetof(mm8::ModelFacet, polygonType) == 303);



	struct BSPNode // size: 0x8
	{
		int16_t frontNode; // 0x0 (0 decimal)
		int16_t backNode; // 0x2 (2 decimal)
		int16_t coplanarOffset; // 0x4 (4 decimal)
		int16_t coplanarSize; // 0x6 (6 decimal)
	};
	static_assert(sizeof(mm8::BSPNode) == 0x8, "Invalid \"mm8::BSPNode\" structure size");
	static_assert(offsetof(mm8::BSPNode, backNode) == 2);
	static_assert(offsetof(mm8::BSPNode, coplanarOffset) == 4);
	static_assert(offsetof(mm8::BSPNode, coplanarSize) == 6);



	struct MapModel // size: 0xBC
	{
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		std::array<char, 32> name2; // fixed size string, requires null terminator | 0x20 (32 decimal)
		union
		{
			uint32_t bits; // 0x40 (64 decimal)
			struct
			{
				bool showOnMap : 1; // 0x40 (64 decimal), bit index 7
			};
		};
		uint32_t vertexes_size; // 0x44 (68 decimal)
		mm8::ModelVertex* vertexes; // size field offset is 0x44 | 0x48 (72 decimal)
		union
		{
			uint32_t facets_size; // 0x4C (76 decimal)
			uint32_t ordering_size; // 0x4C (76 decimal)
		};
		int16_t convexFacetsCount; // 0x50 (80 decimal)
		SKIP(2);
		mm8::ModelFacet* facets; // size field offset is 0x4C | 0x54 (84 decimal)
		int16_t* ordering; // size field offset is 0x4C | 0x58 (88 decimal)
		uint32_t BSPNodes_size; // 0x5C (92 decimal)
		mm8::BSPNode* BSPNodes; // size field offset is 0x5C | 0x60 (96 decimal)
		SKIP(4);
		int32_t gridX; // 0x68 (104 decimal) | MMExt info: center X
		int32_t gridY; // 0x6C (108 decimal) | MMExt info: center Y
		union
		{
			std::array<int32_t, 3> pos; // 0x70 (112 decimal)
			struct
			{
				int32_t x; // 0x70 (112 decimal)
				int32_t y; // 0x74 (116 decimal)
				int32_t z; // 0x78 (120 decimal)
			};
		};
		int32_t minX; // 0x7C (124 decimal) | MMExt info: Bounding MIN X
		int32_t minY; // 0x80 (128 decimal) | MMExt info: Bounding MIN Y
		int32_t minZ; // 0x84 (132 decimal) | MMExt info: Bounding MIN Z
		int32_t maxX; // 0x88 (136 decimal) | MMExt info: Bounding MAX X
		int32_t maxY; // 0x8C (140 decimal) | MMExt info: Bounding MAX Y
		int32_t maxZ; // 0x90 (144 decimal) | MMExt info: Bounding MAX Z
		int32_t BFMinX; // 0x94 (148 decimal)
		int32_t BFMinY; // 0x98 (152 decimal)
		int32_t BFMinZ; // 0x9C (156 decimal)
		int32_t BFMaxX; // 0xA0 (160 decimal)
		int32_t BFMaxY; // 0xA4 (164 decimal)
		int32_t BFMaxZ; // 0xA8 (168 decimal)
		int32_t boxCenterX; // 0xAC (172 decimal) | MMExt info: Bounding center X
		int32_t boxCenterY; // 0xB0 (176 decimal) | MMExt info: Bounding center Y
		int32_t boxCenterZ; // 0xB4 (180 decimal) | MMExt info: Bounding center Z
		int32_t boundingRadius; // 0xB8 (184 decimal)
	};
	static_assert(sizeof(mm8::MapModel) == 0xBC, "Invalid \"mm8::MapModel\" structure size");
	static_assert(offsetof(mm8::MapModel, name2) == 32);
	static_assert(offsetof(mm8::MapModel, bits) == 64);
	static_assert(offsetof(mm8::MapModel, vertexes_size) == 68);
	static_assert(offsetof(mm8::MapModel, vertexes) == 72);
	static_assert(offsetof(mm8::MapModel, facets_size) == 76);
	static_assert(offsetof(mm8::MapModel, ordering_size) == 76);
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