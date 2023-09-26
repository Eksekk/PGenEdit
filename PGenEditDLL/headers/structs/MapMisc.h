#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct MapOutline // size: 0xC
	{
		int16_t vertex1; // 0x0 (0 decimal)
		int16_t vertex2; // 0x2 (2 decimal)
		int16_t facet1; // 0x4 (4 decimal)
		int16_t facet2; // 0x6 (6 decimal)
		int16_t z; // 0x8 (8 decimal)
		union
		{
			uint16_t bits; // 0xA (10 decimal)
			struct
			{
				bool visible : 1; // 0xA (10 decimal), bit index 7
			};
		};
	};
	static_assert(sizeof(mm6::MapOutline) == 0xC, "Invalid \"mm6::MapOutline\" structure size");
	static_assert(offsetof(mm6::MapOutline, vertex2) == 2);
	static_assert(offsetof(mm6::MapOutline, facet1) == 4);
	static_assert(offsetof(mm6::MapOutline, facet2) == 6);
	static_assert(offsetof(mm6::MapOutline, z) == 8);
	static_assert(offsetof(mm6::MapOutline, bits) == 10);



	struct MapOutlines // size: 0x14824
	{
		uint32_t items_size; // 0x0 (0 decimal)
		std::array<mm6::MapOutline, 7000> items; // size field offset is 0x0 | 0x4 (4 decimal)
	};
	static_assert(sizeof(mm6::MapOutlines) == 0x14824, "Invalid \"mm6::MapOutlines\" structure size");
	static_assert(offsetof(mm6::MapOutlines, items) == 4);



	struct TilesetDef // size: 0x4
	{
		std::array<uint8_t, 2> group; // Unknown type | 0x0 (0 decimal)
		int16_t offset; // 0x2 (2 decimal)
	};
	static_assert(sizeof(mm6::TilesetDef) == 0x4, "Invalid \"mm6::TilesetDef\" structure size");
	static_assert(offsetof(mm6::TilesetDef, offset) == 2);



	struct OdmHeader // size: 0xB0
	{
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		std::array<char, 32> fileName; // fixed size string, requires null terminator | 0x20 (32 decimal)
		std::array<char, 31> versionStr; // fixed size string, requires null terminator | 0x40 (64 decimal)
		SKIP(65);
		std::array<mm6::TilesetDef, 4> tilesets; // 0xA0 (160 decimal)
	};
	static_assert(sizeof(mm6::OdmHeader) == 0xB0, "Invalid \"mm6::OdmHeader\" structure size");
	static_assert(offsetof(mm6::OdmHeader, fileName) == 32);
	static_assert(offsetof(mm6::OdmHeader, versionStr) == 64);
	static_assert(offsetof(mm6::OdmHeader, tilesets) == 160);



	struct SpawnPoint // size: 0x14
	{
		union
		{
			std::array<int32_t, 3> pos; // 0x0 (0 decimal)
			struct
			{
				int32_t x; // 0x0 (0 decimal)
				int32_t y; // 0x4 (4 decimal)
				int32_t z; // 0x8 (8 decimal)
			};
		};
		int16_t radius; // 0xC (12 decimal)
		int16_t kind; // 0xE (14 decimal)
		int16_t index; // 0x10 (16 decimal) | MMExt info: Index: monster (1-3: M1-M3,  4-6: M1a-M3a,  7-9: M1b-M3b,  10-12: M1c-M3c) or item (1-6 for regular items, 7 for artifact)
		union
		{
			uint16_t bits; // 0x12 (18 decimal)
			struct
			{
				bool onAlertMap : 1; // 0x12 (18 decimal), bit index 7
			};
		};
	};
	static_assert(sizeof(mm6::SpawnPoint) == 0x14, "Invalid \"mm6::SpawnPoint\" structure size");
	static_assert(offsetof(mm6::SpawnPoint, y) == 4);
	static_assert(offsetof(mm6::SpawnPoint, z) == 8);
	static_assert(offsetof(mm6::SpawnPoint, radius) == 12);
	static_assert(offsetof(mm6::SpawnPoint, kind) == 14);
	static_assert(offsetof(mm6::SpawnPoint, index) == 16);
	static_assert(offsetof(mm6::SpawnPoint, bits) == 18);



	struct BlvHeader // size: 0x88
	{
		SKIP(4);
		std::array<char, 60> name; // fixed size string, requires null terminator | 0x4 (4 decimal)
		SKIP(40);
		int32_t facetDataSize; // 0x68 (104 decimal)
		int32_t roomDataSize; // 0x6C (108 decimal)
		int32_t roomLightDataSize; // 0x70 (112 decimal)
		int32_t doorDataSize; // 0x74 (116 decimal)
		SKIP(16);
	};
	static_assert(sizeof(mm6::BlvHeader) == 0x88, "Invalid \"mm6::BlvHeader\" structure size");
	static_assert(offsetof(mm6::BlvHeader, name) == 4);
	static_assert(offsetof(mm6::BlvHeader, facetDataSize) == 104);
	static_assert(offsetof(mm6::BlvHeader, roomDataSize) == 108);
	static_assert(offsetof(mm6::BlvHeader, roomLightDataSize) == 112);
	static_assert(offsetof(mm6::BlvHeader, doorDataSize) == 116);
}
namespace mm7
{
	struct BaseLight // size: 0xC
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
	};
	static_assert(sizeof(mm7::BaseLight) == 0xC, "Invalid \"mm7::BaseLight\" structure size");
	static_assert(offsetof(mm7::BaseLight, y) == 2);
	static_assert(offsetof(mm7::BaseLight, z) == 4);
	static_assert(offsetof(mm7::BaseLight, radius) == 6);
	static_assert(offsetof(mm7::BaseLight, r) == 8);
	static_assert(offsetof(mm7::BaseLight, g) == 9);
	static_assert(offsetof(mm7::BaseLight, b) == 10);
	static_assert(offsetof(mm7::BaseLight, type) == 11);



	struct MapOutline // size: 0xC
	{
		int16_t vertex1; // 0x0 (0 decimal)
		int16_t vertex2; // 0x2 (2 decimal)
		int16_t facet1; // 0x4 (4 decimal)
		int16_t facet2; // 0x6 (6 decimal)
		int16_t z; // 0x8 (8 decimal)
		union
		{
			uint16_t bits; // 0xA (10 decimal)
			struct
			{
				bool visible : 1; // 0xA (10 decimal), bit index 7
			};
		};
	};
	static_assert(sizeof(mm7::MapOutline) == 0xC, "Invalid \"mm7::MapOutline\" structure size");
	static_assert(offsetof(mm7::MapOutline, vertex2) == 2);
	static_assert(offsetof(mm7::MapOutline, facet1) == 4);
	static_assert(offsetof(mm7::MapOutline, facet2) == 6);
	static_assert(offsetof(mm7::MapOutline, z) == 8);
	static_assert(offsetof(mm7::MapOutline, bits) == 10);



	struct MapOutlines // size: 0x14824
	{
		uint32_t items_size; // 0x0 (0 decimal)
		std::array<mm7::MapOutline, 7000> items; // size field offset is 0x0 | 0x4 (4 decimal)
	};
	static_assert(sizeof(mm7::MapOutlines) == 0x14824, "Invalid \"mm7::MapOutlines\" structure size");
	static_assert(offsetof(mm7::MapOutlines, items) == 4);



	struct TilesetDef // size: 0x4
	{
		std::array<uint8_t, 2> group; // Unknown type | 0x0 (0 decimal)
		int16_t offset; // 0x2 (2 decimal)
	};
	static_assert(sizeof(mm7::TilesetDef) == 0x4, "Invalid \"mm7::TilesetDef\" structure size");
	static_assert(offsetof(mm7::TilesetDef, offset) == 2);



	struct OdmHeader // size: 0xB0
	{
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		std::array<char, 32> fileName; // fixed size string, requires null terminator | 0x20 (32 decimal)
		std::array<char, 31> versionStr; // fixed size string, requires null terminator | 0x40 (64 decimal)
		SKIP(65);
		std::array<mm7::TilesetDef, 4> tilesets; // 0xA0 (160 decimal)
	};
	static_assert(sizeof(mm7::OdmHeader) == 0xB0, "Invalid \"mm7::OdmHeader\" structure size");
	static_assert(offsetof(mm7::OdmHeader, fileName) == 32);
	static_assert(offsetof(mm7::OdmHeader, versionStr) == 64);
	static_assert(offsetof(mm7::OdmHeader, tilesets) == 160);



	struct SpawnPoint // size: 0x18
	{
		union
		{
			std::array<int32_t, 3> pos; // 0x0 (0 decimal)
			struct
			{
				int32_t x; // 0x0 (0 decimal)
				int32_t y; // 0x4 (4 decimal)
				int32_t z; // 0x8 (8 decimal)
			};
		};
		int16_t radius; // 0xC (12 decimal)
		int16_t kind; // 0xE (14 decimal)
		int16_t index; // 0x10 (16 decimal) | MMExt info: Index: monster (1-3: M1-M3,  4-6: M1a-M3a,  7-9: M1b-M3b,  10-12: M1c-M3c) or item (1-6 for regular items, 7 for artifact)
		union
		{
			uint16_t bits; // 0x12 (18 decimal)
			struct
			{
				bool onAlertMap : 1; // 0x12 (18 decimal), bit index 7
			};
		};
		int32_t group; // 0x14 (20 decimal)
	};
	static_assert(sizeof(mm7::SpawnPoint) == 0x18, "Invalid \"mm7::SpawnPoint\" structure size");
	static_assert(offsetof(mm7::SpawnPoint, y) == 4);
	static_assert(offsetof(mm7::SpawnPoint, z) == 8);
	static_assert(offsetof(mm7::SpawnPoint, radius) == 12);
	static_assert(offsetof(mm7::SpawnPoint, kind) == 14);
	static_assert(offsetof(mm7::SpawnPoint, index) == 16);
	static_assert(offsetof(mm7::SpawnPoint, bits) == 18);
	static_assert(offsetof(mm7::SpawnPoint, group) == 20);



	struct BlvHeader // size: 0x88
	{
		SKIP(4);
		std::array<char, 60> name; // fixed size string, requires null terminator | 0x4 (4 decimal)
		SKIP(40);
		int32_t facetDataSize; // 0x68 (104 decimal)
		int32_t roomDataSize; // 0x6C (108 decimal)
		int32_t roomLightDataSize; // 0x70 (112 decimal)
		int32_t doorDataSize; // 0x74 (116 decimal)
		SKIP(16);
	};
	static_assert(sizeof(mm7::BlvHeader) == 0x88, "Invalid \"mm7::BlvHeader\" structure size");
	static_assert(offsetof(mm7::BlvHeader, name) == 4);
	static_assert(offsetof(mm7::BlvHeader, facetDataSize) == 104);
	static_assert(offsetof(mm7::BlvHeader, roomDataSize) == 108);
	static_assert(offsetof(mm7::BlvHeader, roomLightDataSize) == 112);
	static_assert(offsetof(mm7::BlvHeader, doorDataSize) == 116);
}
namespace mm8
{
	struct BaseLight // size: 0xC
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
	};
	static_assert(sizeof(mm8::BaseLight) == 0xC, "Invalid \"mm8::BaseLight\" structure size");
	static_assert(offsetof(mm8::BaseLight, y) == 2);
	static_assert(offsetof(mm8::BaseLight, z) == 4);
	static_assert(offsetof(mm8::BaseLight, radius) == 6);
	static_assert(offsetof(mm8::BaseLight, r) == 8);
	static_assert(offsetof(mm8::BaseLight, g) == 9);
	static_assert(offsetof(mm8::BaseLight, b) == 10);
	static_assert(offsetof(mm8::BaseLight, type) == 11);



	struct MapOutline // size: 0xC
	{
		int16_t vertex1; // 0x0 (0 decimal)
		int16_t vertex2; // 0x2 (2 decimal)
		int16_t facet1; // 0x4 (4 decimal)
		int16_t facet2; // 0x6 (6 decimal)
		int16_t z; // 0x8 (8 decimal)
		union
		{
			uint16_t bits; // 0xA (10 decimal)
			struct
			{
				bool visible : 1; // 0xA (10 decimal), bit index 7
			};
		};
	};
	static_assert(sizeof(mm8::MapOutline) == 0xC, "Invalid \"mm8::MapOutline\" structure size");
	static_assert(offsetof(mm8::MapOutline, vertex2) == 2);
	static_assert(offsetof(mm8::MapOutline, facet1) == 4);
	static_assert(offsetof(mm8::MapOutline, facet2) == 6);
	static_assert(offsetof(mm8::MapOutline, z) == 8);
	static_assert(offsetof(mm8::MapOutline, bits) == 10);



	struct MapOutlines // size: 0x14824
	{
		uint32_t items_size; // 0x0 (0 decimal)
		std::array<mm8::MapOutline, 7000> items; // size field offset is 0x0 | 0x4 (4 decimal)
	};
	static_assert(sizeof(mm8::MapOutlines) == 0x14824, "Invalid \"mm8::MapOutlines\" structure size");
	static_assert(offsetof(mm8::MapOutlines, items) == 4);



	struct TilesetDef // size: 0x4
	{
		std::array<uint8_t, 2> group; // Unknown type | 0x0 (0 decimal)
		int16_t offset; // 0x2 (2 decimal)
	};
	static_assert(sizeof(mm8::TilesetDef) == 0x4, "Invalid \"mm8::TilesetDef\" structure size");
	static_assert(offsetof(mm8::TilesetDef, offset) == 2);



	struct OdmHeader // size: 0xB4
	{
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		std::array<char, 32> fileName; // fixed size string, requires null terminator | 0x20 (32 decimal)
		std::array<char, 31> versionStr; // fixed size string, requires null terminator | 0x40 (64 decimal)
		uint8_t tilesetsFile; // 0x5F (95 decimal) | MMExt info: 0 = dtile.bin, 1 = dtile2.bin, 2 = dtile3.bin
		SKIP(64);
		std::array<mm8::TilesetDef, 4> tilesets; // 0xA0 (160 decimal)
		uint32_t bits; // 0xB0 (176 decimal)
	};
	static_assert(sizeof(mm8::OdmHeader) == 0xB4, "Invalid \"mm8::OdmHeader\" structure size");
	static_assert(offsetof(mm8::OdmHeader, fileName) == 32);
	static_assert(offsetof(mm8::OdmHeader, versionStr) == 64);
	static_assert(offsetof(mm8::OdmHeader, tilesetsFile) == 95);
	static_assert(offsetof(mm8::OdmHeader, tilesets) == 160);
	static_assert(offsetof(mm8::OdmHeader, bits) == 176);



	struct MapNote // size: 0x132
	{
		bool active; // 0x0 (0 decimal)
		SKIP(1);
		int16_t x; // 0x2 (2 decimal)
		int16_t y; // 0x4 (4 decimal)
		std::array<char, 298> text; // fixed size string, requires null terminator | 0x6 (6 decimal)
		int16_t id; // 0x130 (304 decimal)
	};
	static_assert(sizeof(mm8::MapNote) == 0x132, "Invalid \"mm8::MapNote\" structure size");
	static_assert(offsetof(mm8::MapNote, x) == 2);
	static_assert(offsetof(mm8::MapNote, y) == 4);
	static_assert(offsetof(mm8::MapNote, text) == 6);
	static_assert(offsetof(mm8::MapNote, id) == 304);



	struct SpawnPoint // size: 0x18
	{
		union
		{
			std::array<int32_t, 3> pos; // 0x0 (0 decimal)
			struct
			{
				int32_t x; // 0x0 (0 decimal)
				int32_t y; // 0x4 (4 decimal)
				int32_t z; // 0x8 (8 decimal)
			};
		};
		int16_t radius; // 0xC (12 decimal)
		int16_t kind; // 0xE (14 decimal)
		int16_t index; // 0x10 (16 decimal) | MMExt info: Index: monster (1-3: M1-M3,  4-6: M1a-M3a,  7-9: M1b-M3b,  10-12: M1c-M3c) or item (1-6 for regular items, 7 for artifact)
		union
		{
			uint16_t bits; // 0x12 (18 decimal)
			struct
			{
				bool onAlertMap : 1; // 0x12 (18 decimal), bit index 7
			};
		};
		int32_t group; // 0x14 (20 decimal)
	};
	static_assert(sizeof(mm8::SpawnPoint) == 0x18, "Invalid \"mm8::SpawnPoint\" structure size");
	static_assert(offsetof(mm8::SpawnPoint, y) == 4);
	static_assert(offsetof(mm8::SpawnPoint, z) == 8);
	static_assert(offsetof(mm8::SpawnPoint, radius) == 12);
	static_assert(offsetof(mm8::SpawnPoint, kind) == 14);
	static_assert(offsetof(mm8::SpawnPoint, index) == 16);
	static_assert(offsetof(mm8::SpawnPoint, bits) == 18);
	static_assert(offsetof(mm8::SpawnPoint, group) == 20);



	struct BlvHeader // size: 0x88
	{
		SKIP(4);
		std::array<char, 60> name; // fixed size string, requires null terminator | 0x4 (4 decimal)
		SKIP(40);
		int32_t facetDataSize; // 0x68 (104 decimal)
		int32_t roomDataSize; // 0x6C (108 decimal)
		int32_t roomLightDataSize; // 0x70 (112 decimal)
		int32_t doorDataSize; // 0x74 (116 decimal)
		SKIP(16);
	};
	static_assert(sizeof(mm8::BlvHeader) == 0x88, "Invalid \"mm8::BlvHeader\" structure size");
	static_assert(offsetof(mm8::BlvHeader, name) == 4);
	static_assert(offsetof(mm8::BlvHeader, facetDataSize) == 104);
	static_assert(offsetof(mm8::BlvHeader, roomDataSize) == 108);
	static_assert(offsetof(mm8::BlvHeader, roomLightDataSize) == 112);
	static_assert(offsetof(mm8::BlvHeader, doorDataSize) == 116);
}

#pragma pack(pop)