#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct LodBitmap // size: 0x48
	{
		std::array<char, 16> name; // fixed size string, requires null terminator
		int32_t bmpSize;
		int32_t dataSize;
		int16_t width;
		int16_t height;
		int16_t widthLn2;
		int16_t heightLn2;
		int16_t widthMinus1;
		int16_t heightMinus1;
		int16_t palette;
		int16_t loadedPalette;
		int32_t unpackedSize;
		uint32_t bits;
		int32_t image;
		int32_t imageDiv2;
		int32_t imageDiv4;
		int32_t imageDiv8;
		int32_t palette16;
		int32_t palette24;
	};
	static_assert(sizeof(mm6::LodBitmap) == 0x48, "Invalid \"mm6::LodBitmap\" structure size");
	static_assert(offsetof(mm6::LodBitmap, bmpSize) == 16);
	static_assert(offsetof(mm6::LodBitmap, dataSize) == 20);
	static_assert(offsetof(mm6::LodBitmap, width) == 24);
	static_assert(offsetof(mm6::LodBitmap, height) == 26);
	static_assert(offsetof(mm6::LodBitmap, widthLn2) == 28);
	static_assert(offsetof(mm6::LodBitmap, heightLn2) == 30);
	static_assert(offsetof(mm6::LodBitmap, widthMinus1) == 32);
	static_assert(offsetof(mm6::LodBitmap, heightMinus1) == 34);
	static_assert(offsetof(mm6::LodBitmap, palette) == 36);
	static_assert(offsetof(mm6::LodBitmap, loadedPalette) == 38);
	static_assert(offsetof(mm6::LodBitmap, unpackedSize) == 40);
	static_assert(offsetof(mm6::LodBitmap, bits) == 44);
	static_assert(offsetof(mm6::LodBitmap, image) == 48);
	static_assert(offsetof(mm6::LodBitmap, imageDiv2) == 52);
	static_assert(offsetof(mm6::LodBitmap, imageDiv4) == 56);
	static_assert(offsetof(mm6::LodBitmap, imageDiv8) == 60);
	static_assert(offsetof(mm6::LodBitmap, palette16) == 64);
	static_assert(offsetof(mm6::LodBitmap, palette24) == 68);



	struct LodRecord // size: 0x48
	{
		uint32_t lodPtr;
		uint32_t namePtr;
		std::array<char, 64> name; // fixed size string, requires null terminator
	};
	static_assert(sizeof(mm6::LodRecord) == 0x48, "Invalid \"mm6::LodRecord\" structure size");
	static_assert(offsetof(mm6::LodRecord, namePtr) == 4);
	static_assert(offsetof(mm6::LodRecord, name) == 8);



	struct CustomLods // size: 0x4804
	{
		int32_t recordIndex;
		std::array<mm6::LodRecord, 256> records;
	};
	static_assert(sizeof(mm6::CustomLods) == 0x4804, "Invalid \"mm6::CustomLods\" structure size");
	static_assert(offsetof(mm6::CustomLods, records) == 4);



	struct LodSpriteD3D // size: 0x28
	{
		const char* name; // PChar (read-only)
		int32_t palette;
		uint32_t surface;
		uint32_t texture;
		int32_t areaX;
		int32_t areaY;
		int32_t bufferWidth;
		int32_t bufferHeight;
		int32_t areaWidth;
		int32_t areaHeight;
	};
	static_assert(sizeof(mm6::LodSpriteD3D) == 0x28, "Invalid \"mm6::LodSpriteD3D\" structure size");
	static_assert(offsetof(mm6::LodSpriteD3D, palette) == 4);
	static_assert(offsetof(mm6::LodSpriteD3D, surface) == 8);
	static_assert(offsetof(mm6::LodSpriteD3D, texture) == 12);
	static_assert(offsetof(mm6::LodSpriteD3D, areaX) == 16);
	static_assert(offsetof(mm6::LodSpriteD3D, areaY) == 20);
	static_assert(offsetof(mm6::LodSpriteD3D, bufferWidth) == 24);
	static_assert(offsetof(mm6::LodSpriteD3D, bufferHeight) == 28);
	static_assert(offsetof(mm6::LodSpriteD3D, areaWidth) == 32);
	static_assert(offsetof(mm6::LodSpriteD3D, areaHeight) == 36);



	struct LodSpriteLine // size: 0x8
	{
		int16_t l;
		int16_t r;
		uint8_t* pos;
	};
	static_assert(sizeof(mm6::LodSpriteLine) == 0x8, "Invalid \"mm6::LodSpriteLine\" structure size");
	static_assert(offsetof(mm6::LodSpriteLine, r) == 2);
	static_assert(offsetof(mm6::LodSpriteLine, pos) == 4);



	struct LodSprite // size: 0x28
	{
		std::array<char, 12> name; // fixed size string, requires null terminator
		int32_t dataSize;
		int16_t width;
		union
		{
			uint32_t lines_size;
			struct
			{
				int16_t height;
				int16_t palette;
			};
		};
		SKIP(2);
		int16_t YSkip;
		SKIP(2);
		int32_t unpackedSize;
		mm6::LodSpriteLine* lines; // size field offset is 0x12
		uint32_t buffer;
	};
	static_assert(sizeof(mm6::LodSprite) == 0x28, "Invalid \"mm6::LodSprite\" structure size");
	static_assert(offsetof(mm6::LodSprite, dataSize) == 12);
	static_assert(offsetof(mm6::LodSprite, width) == 16);
	static_assert(offsetof(mm6::LodSprite, lines_size) == 18);
	static_assert(offsetof(mm6::LodSprite, height) == 18);
	static_assert(offsetof(mm6::LodSprite, palette) == 20);
	static_assert(offsetof(mm6::LodSprite, YSkip) == 24);
	static_assert(offsetof(mm6::LodSprite, unpackedSize) == 28);
	static_assert(offsetof(mm6::LodSprite, lines) == 32);
	static_assert(offsetof(mm6::LodSprite, buffer) == 36);



	struct LodFile // size: 0x20
	{
		std::array<char, 16> name; // fixed size string, requires null terminator
		int32_t offset;
		int32_t size;
		SKIP(8);
	};
	static_assert(sizeof(mm6::LodFile) == 0x20, "Invalid \"mm6::LodFile\" structure size");
	static_assert(offsetof(mm6::LodFile, offset) == 16);
	static_assert(offsetof(mm6::LodFile, size) == 20);



	struct BitmapsLod // size: 0x8EE0
	{
		uint32_t file;
		std::array<char, 256> fileName; // fixed size string, requires null terminator
		uint32_t loaded; // 4-byte boolean
		uint32_t IOBuffer;
		int32_t IOBufferSize;
		int32_t lodHeaderSignature;
		SKIP(80);
		std::array<char, 80> description; // fixed size string, requires null terminator
		SKIP(8);
		int32_t archivesCount;
		SKIP(80);
		uint32_t archivesCArray;
		std::array<char, 16> type; // fixed size string, requires null terminator
		uint32_t chapterHandle;
		uint32_t chapterSize;
		uint32_t files_size;
		mm6::LodFile* files; // size field offset is 0x22C
		uint32_t filesOffset;
		SKIP(4);
		std::array<mm6::LodBitmap, 500> bitmaps; // size field offset is 0x8EDC
		uint32_t bitmaps_size;
	};
	static_assert(sizeof(mm6::BitmapsLod) == 0x8EE0, "Invalid \"mm6::BitmapsLod\" structure size");
	static_assert(offsetof(mm6::BitmapsLod, fileName) == 4);
	static_assert(offsetof(mm6::BitmapsLod, loaded) == 260);
	static_assert(offsetof(mm6::BitmapsLod, IOBuffer) == 264);
	static_assert(offsetof(mm6::BitmapsLod, IOBufferSize) == 268);
	static_assert(offsetof(mm6::BitmapsLod, lodHeaderSignature) == 272);
	static_assert(offsetof(mm6::BitmapsLod, description) == 356);
	static_assert(offsetof(mm6::BitmapsLod, archivesCount) == 444);
	static_assert(offsetof(mm6::BitmapsLod, archivesCArray) == 528);
	static_assert(offsetof(mm6::BitmapsLod, type) == 532);
	static_assert(offsetof(mm6::BitmapsLod, chapterHandle) == 548);
	static_assert(offsetof(mm6::BitmapsLod, chapterSize) == 552);
	static_assert(offsetof(mm6::BitmapsLod, files_size) == 556);
	static_assert(offsetof(mm6::BitmapsLod, files) == 560);
	static_assert(offsetof(mm6::BitmapsLod, filesOffset) == 564);
	static_assert(offsetof(mm6::BitmapsLod, bitmaps) == 572);
	static_assert(offsetof(mm6::BitmapsLod, bitmaps_size) == 36572);



	struct Lod // size: 0x23C
	{
		uint32_t file;
		std::array<char, 256> fileName; // fixed size string, requires null terminator
		uint32_t loaded; // 4-byte boolean
		uint32_t IOBuffer;
		int32_t IOBufferSize;
		int32_t lodHeaderSignature;
		SKIP(80);
		std::array<char, 80> description; // fixed size string, requires null terminator
		SKIP(8);
		int32_t archivesCount;
		SKIP(80);
		uint32_t archivesCArray;
		std::array<char, 16> type; // fixed size string, requires null terminator
		uint32_t chapterHandle;
		uint32_t chapterSize;
		uint32_t files_size;
		mm6::LodFile* files; // size field offset is 0x22C
		uint32_t filesOffset;
		SKIP(4);
	};
	static_assert(sizeof(mm6::Lod) == 0x23C, "Invalid \"mm6::Lod\" structure size");
	static_assert(offsetof(mm6::Lod, fileName) == 4);
	static_assert(offsetof(mm6::Lod, loaded) == 260);
	static_assert(offsetof(mm6::Lod, IOBuffer) == 264);
	static_assert(offsetof(mm6::Lod, IOBufferSize) == 268);
	static_assert(offsetof(mm6::Lod, lodHeaderSignature) == 272);
	static_assert(offsetof(mm6::Lod, description) == 356);
	static_assert(offsetof(mm6::Lod, archivesCount) == 444);
	static_assert(offsetof(mm6::Lod, archivesCArray) == 528);
	static_assert(offsetof(mm6::Lod, type) == 532);
	static_assert(offsetof(mm6::Lod, chapterHandle) == 548);
	static_assert(offsetof(mm6::Lod, chapterSize) == 552);
	static_assert(offsetof(mm6::Lod, files_size) == 556);
	static_assert(offsetof(mm6::Lod, files) == 560);
	static_assert(offsetof(mm6::Lod, filesOffset) == 564);



	struct SpritesLod // size: 0xECB8
	{
		static mm6::LodSprite* spritesSW; // converted to pointer to not break with limits removal scripts
		static uint32_t* spritesSW_sizePtr; // pointer to size, set during initialization by getting data from lua

		uint32_t file;
		std::array<char, 256> fileName; // fixed size string, requires null terminator
		uint32_t loaded; // 4-byte boolean
		uint32_t IOBuffer;
		int32_t IOBufferSize;
		int32_t lodHeaderSignature;
		SKIP(80);
		std::array<char, 80> description; // fixed size string, requires null terminator
		SKIP(8);
		int32_t archivesCount;
		SKIP(80);
		uint32_t archivesCArray;
		std::array<char, 16> type; // fixed size string, requires null terminator
		uint32_t chapterHandle;
		uint32_t chapterSize;
		uint32_t files_size;
		mm6::LodFile* files; // size field offset is 0x22C
		uint32_t filesOffset;
		SKIP(60020);
		uint32_t isHardware; // 4-byte boolean
		mm6::LodSpriteD3D* spritesD3D; // size field offset is 0xECB4
		uint32_t spritesD3D_size;
	};
	static_assert(sizeof(mm6::SpritesLod) == 0xECB8, "Invalid \"mm6::SpritesLod\" structure size");
	static_assert(offsetof(mm6::SpritesLod, fileName) == 4);
	static_assert(offsetof(mm6::SpritesLod, loaded) == 260);
	static_assert(offsetof(mm6::SpritesLod, IOBuffer) == 264);
	static_assert(offsetof(mm6::SpritesLod, IOBufferSize) == 268);
	static_assert(offsetof(mm6::SpritesLod, lodHeaderSignature) == 272);
	static_assert(offsetof(mm6::SpritesLod, description) == 356);
	static_assert(offsetof(mm6::SpritesLod, archivesCount) == 444);
	static_assert(offsetof(mm6::SpritesLod, archivesCArray) == 528);
	static_assert(offsetof(mm6::SpritesLod, type) == 532);
	static_assert(offsetof(mm6::SpritesLod, chapterHandle) == 548);
	static_assert(offsetof(mm6::SpritesLod, chapterSize) == 552);
	static_assert(offsetof(mm6::SpritesLod, files_size) == 556);
	static_assert(offsetof(mm6::SpritesLod, files) == 560);
	static_assert(offsetof(mm6::SpritesLod, filesOffset) == 564);
	static_assert(offsetof(mm6::SpritesLod, isHardware) == 60588);
	static_assert(offsetof(mm6::SpritesLod, spritesD3D) == 60592);
	static_assert(offsetof(mm6::SpritesLod, spritesD3D_size) == 60596);
}
namespace mm7
{
	struct LodBitmap // size: 0x48
	{
		std::array<char, 16> name; // fixed size string, requires null terminator
		int32_t bmpSize;
		int32_t dataSize;
		int16_t width;
		int16_t height;
		int16_t widthLn2;
		int16_t heightLn2;
		int16_t widthMinus1;
		int16_t heightMinus1;
		int16_t palette;
		int16_t loadedPalette;
		int32_t unpackedSize;
		uint32_t bits;
		int32_t image;
		int32_t imageDiv2;
		int32_t imageDiv4;
		int32_t imageDiv8;
		int32_t palette16;
		int32_t palette24;
	};
	static_assert(sizeof(mm7::LodBitmap) == 0x48, "Invalid \"mm7::LodBitmap\" structure size");
	static_assert(offsetof(mm7::LodBitmap, bmpSize) == 16);
	static_assert(offsetof(mm7::LodBitmap, dataSize) == 20);
	static_assert(offsetof(mm7::LodBitmap, width) == 24);
	static_assert(offsetof(mm7::LodBitmap, height) == 26);
	static_assert(offsetof(mm7::LodBitmap, widthLn2) == 28);
	static_assert(offsetof(mm7::LodBitmap, heightLn2) == 30);
	static_assert(offsetof(mm7::LodBitmap, widthMinus1) == 32);
	static_assert(offsetof(mm7::LodBitmap, heightMinus1) == 34);
	static_assert(offsetof(mm7::LodBitmap, palette) == 36);
	static_assert(offsetof(mm7::LodBitmap, loadedPalette) == 38);
	static_assert(offsetof(mm7::LodBitmap, unpackedSize) == 40);
	static_assert(offsetof(mm7::LodBitmap, bits) == 44);
	static_assert(offsetof(mm7::LodBitmap, image) == 48);
	static_assert(offsetof(mm7::LodBitmap, imageDiv2) == 52);
	static_assert(offsetof(mm7::LodBitmap, imageDiv4) == 56);
	static_assert(offsetof(mm7::LodBitmap, imageDiv8) == 60);
	static_assert(offsetof(mm7::LodBitmap, palette16) == 64);
	static_assert(offsetof(mm7::LodBitmap, palette24) == 68);



	struct LodSpriteD3D // size: 0x28
	{
		const char* name; // PChar (read-only)
		int32_t palette;
		uint32_t surface;
		uint32_t texture;
		int32_t areaX;
		int32_t areaY;
		int32_t bufferWidth;
		int32_t bufferHeight;
		int32_t areaWidth;
		int32_t areaHeight;
	};
	static_assert(sizeof(mm7::LodSpriteD3D) == 0x28, "Invalid \"mm7::LodSpriteD3D\" structure size");
	static_assert(offsetof(mm7::LodSpriteD3D, palette) == 4);
	static_assert(offsetof(mm7::LodSpriteD3D, surface) == 8);
	static_assert(offsetof(mm7::LodSpriteD3D, texture) == 12);
	static_assert(offsetof(mm7::LodSpriteD3D, areaX) == 16);
	static_assert(offsetof(mm7::LodSpriteD3D, areaY) == 20);
	static_assert(offsetof(mm7::LodSpriteD3D, bufferWidth) == 24);
	static_assert(offsetof(mm7::LodSpriteD3D, bufferHeight) == 28);
	static_assert(offsetof(mm7::LodSpriteD3D, areaWidth) == 32);
	static_assert(offsetof(mm7::LodSpriteD3D, areaHeight) == 36);



	struct LodSpriteLine // size: 0x8
	{
		int16_t l;
		int16_t r;
		uint8_t* pos;
	};
	static_assert(sizeof(mm7::LodSpriteLine) == 0x8, "Invalid \"mm7::LodSpriteLine\" structure size");
	static_assert(offsetof(mm7::LodSpriteLine, r) == 2);
	static_assert(offsetof(mm7::LodSpriteLine, pos) == 4);



	struct LodSprite // size: 0x28
	{
		std::array<char, 12> name; // fixed size string, requires null terminator
		int32_t dataSize;
		int16_t width;
		union
		{
			uint32_t lines_size;
			struct
			{
				int16_t height;
				int16_t palette;
			};
		};
		SKIP(2);
		int16_t YSkip;
		SKIP(2);
		int32_t unpackedSize;
		mm7::LodSpriteLine* lines; // size field offset is 0x12
		uint32_t buffer;
	};
	static_assert(sizeof(mm7::LodSprite) == 0x28, "Invalid \"mm7::LodSprite\" structure size");
	static_assert(offsetof(mm7::LodSprite, dataSize) == 12);
	static_assert(offsetof(mm7::LodSprite, width) == 16);
	static_assert(offsetof(mm7::LodSprite, lines_size) == 18);
	static_assert(offsetof(mm7::LodSprite, height) == 18);
	static_assert(offsetof(mm7::LodSprite, palette) == 20);
	static_assert(offsetof(mm7::LodSprite, YSkip) == 24);
	static_assert(offsetof(mm7::LodSprite, unpackedSize) == 28);
	static_assert(offsetof(mm7::LodSprite, lines) == 32);
	static_assert(offsetof(mm7::LodSprite, buffer) == 36);



	struct LodFile // size: 0x20
	{
		std::array<char, 16> name; // fixed size string, requires null terminator
		int32_t offset;
		int32_t size;
		SKIP(8);
	};
	static_assert(sizeof(mm7::LodFile) == 0x20, "Invalid \"mm7::LodFile\" structure size");
	static_assert(offsetof(mm7::LodFile, offset) == 16);
	static_assert(offsetof(mm7::LodFile, size) == 20);



	struct BitmapsLod // size: 0x11BB8
	{
		uint32_t file;
		std::array<char, 256> fileName; // fixed size string, requires null terminator
		uint32_t loaded; // 4-byte boolean
		uint32_t IOBuffer;
		int32_t IOBufferSize;
		int32_t lodHeaderSignature;
		SKIP(80);
		std::array<char, 80> description; // fixed size string, requires null terminator
		SKIP(8);
		int32_t archivesCount;
		SKIP(80);
		uint32_t archivesCArray;
		std::array<char, 16> type; // fixed size string, requires null terminator
		uint32_t chapterHandle;
		uint32_t chapterSize;
		uint32_t files_size;
		mm7::LodFile* files; // size field offset is 0x22C
		uint32_t filesOffset;
		SKIP(4);
		std::array<mm7::LodBitmap, 1000> bitmaps; // size field offset is 0x11B7C
		union
		{
			uint32_t D3D_Surfaces_size;
			uint32_t D3D_Textures_size;
			uint32_t bitmaps_size;
		};
		SKIP(36);
		uint32_t keepCompressed; // 4-byte boolean
		uint32_t isHardware; // 4-byte boolean
		uint32_t* D3D_Surfaces; // size field offset is 0x11B7C
		uint32_t* D3D_Textures; // size field offset is 0x11B7C
		SKIP(4);
	};
	static_assert(sizeof(mm7::BitmapsLod) == 0x11BB8, "Invalid \"mm7::BitmapsLod\" structure size");
	static_assert(offsetof(mm7::BitmapsLod, fileName) == 4);
	static_assert(offsetof(mm7::BitmapsLod, loaded) == 260);
	static_assert(offsetof(mm7::BitmapsLod, IOBuffer) == 264);
	static_assert(offsetof(mm7::BitmapsLod, IOBufferSize) == 268);
	static_assert(offsetof(mm7::BitmapsLod, lodHeaderSignature) == 272);
	static_assert(offsetof(mm7::BitmapsLod, description) == 356);
	static_assert(offsetof(mm7::BitmapsLod, archivesCount) == 444);
	static_assert(offsetof(mm7::BitmapsLod, archivesCArray) == 528);
	static_assert(offsetof(mm7::BitmapsLod, type) == 532);
	static_assert(offsetof(mm7::BitmapsLod, chapterHandle) == 548);
	static_assert(offsetof(mm7::BitmapsLod, chapterSize) == 552);
	static_assert(offsetof(mm7::BitmapsLod, files_size) == 556);
	static_assert(offsetof(mm7::BitmapsLod, files) == 560);
	static_assert(offsetof(mm7::BitmapsLod, filesOffset) == 564);
	static_assert(offsetof(mm7::BitmapsLod, bitmaps) == 572);
	static_assert(offsetof(mm7::BitmapsLod, D3D_Surfaces_size) == 72572);
	static_assert(offsetof(mm7::BitmapsLod, D3D_Textures_size) == 72572);
	static_assert(offsetof(mm7::BitmapsLod, bitmaps_size) == 72572);
	static_assert(offsetof(mm7::BitmapsLod, keepCompressed) == 72612);
	static_assert(offsetof(mm7::BitmapsLod, isHardware) == 72616);
	static_assert(offsetof(mm7::BitmapsLod, D3D_Surfaces) == 72620);
	static_assert(offsetof(mm7::BitmapsLod, D3D_Textures) == 72624);



	struct SpritesLod // size: 0xECB8
	{
		static mm7::LodSprite* spritesSW; // converted to pointer to not break with limits removal scripts
		static uint32_t* spritesSW_sizePtr; // pointer to size, set during initialization by getting data from lua

		uint32_t file;
		std::array<char, 256> fileName; // fixed size string, requires null terminator
		uint32_t loaded; // 4-byte boolean
		uint32_t IOBuffer;
		int32_t IOBufferSize;
		int32_t lodHeaderSignature;
		SKIP(80);
		std::array<char, 80> description; // fixed size string, requires null terminator
		SKIP(8);
		int32_t archivesCount;
		SKIP(80);
		uint32_t archivesCArray;
		std::array<char, 16> type; // fixed size string, requires null terminator
		uint32_t chapterHandle;
		uint32_t chapterSize;
		uint32_t files_size;
		mm7::LodFile* files; // size field offset is 0x22C
		uint32_t filesOffset;
		SKIP(60020);
		uint32_t isHardware; // 4-byte boolean
		mm7::LodSpriteD3D* spritesD3D; // size field offset is 0xECB4
		uint32_t spritesD3D_size;
	};
	static_assert(sizeof(mm7::SpritesLod) == 0xECB8, "Invalid \"mm7::SpritesLod\" structure size");
	static_assert(offsetof(mm7::SpritesLod, fileName) == 4);
	static_assert(offsetof(mm7::SpritesLod, loaded) == 260);
	static_assert(offsetof(mm7::SpritesLod, IOBuffer) == 264);
	static_assert(offsetof(mm7::SpritesLod, IOBufferSize) == 268);
	static_assert(offsetof(mm7::SpritesLod, lodHeaderSignature) == 272);
	static_assert(offsetof(mm7::SpritesLod, description) == 356);
	static_assert(offsetof(mm7::SpritesLod, archivesCount) == 444);
	static_assert(offsetof(mm7::SpritesLod, archivesCArray) == 528);
	static_assert(offsetof(mm7::SpritesLod, type) == 532);
	static_assert(offsetof(mm7::SpritesLod, chapterHandle) == 548);
	static_assert(offsetof(mm7::SpritesLod, chapterSize) == 552);
	static_assert(offsetof(mm7::SpritesLod, files_size) == 556);
	static_assert(offsetof(mm7::SpritesLod, files) == 560);
	static_assert(offsetof(mm7::SpritesLod, filesOffset) == 564);
	static_assert(offsetof(mm7::SpritesLod, isHardware) == 60588);
	static_assert(offsetof(mm7::SpritesLod, spritesD3D) == 60592);
	static_assert(offsetof(mm7::SpritesLod, spritesD3D_size) == 60596);



	struct Lod // size: 0x23C
	{
		uint32_t file;
		std::array<char, 256> fileName; // fixed size string, requires null terminator
		uint32_t loaded; // 4-byte boolean
		uint32_t IOBuffer;
		int32_t IOBufferSize;
		int32_t lodHeaderSignature;
		SKIP(80);
		std::array<char, 80> description; // fixed size string, requires null terminator
		SKIP(8);
		int32_t archivesCount;
		SKIP(80);
		uint32_t archivesCArray;
		std::array<char, 16> type; // fixed size string, requires null terminator
		uint32_t chapterHandle;
		uint32_t chapterSize;
		uint32_t files_size;
		mm7::LodFile* files; // size field offset is 0x22C
		uint32_t filesOffset;
		SKIP(4);
	};
	static_assert(sizeof(mm7::Lod) == 0x23C, "Invalid \"mm7::Lod\" structure size");
	static_assert(offsetof(mm7::Lod, fileName) == 4);
	static_assert(offsetof(mm7::Lod, loaded) == 260);
	static_assert(offsetof(mm7::Lod, IOBuffer) == 264);
	static_assert(offsetof(mm7::Lod, IOBufferSize) == 268);
	static_assert(offsetof(mm7::Lod, lodHeaderSignature) == 272);
	static_assert(offsetof(mm7::Lod, description) == 356);
	static_assert(offsetof(mm7::Lod, archivesCount) == 444);
	static_assert(offsetof(mm7::Lod, archivesCArray) == 528);
	static_assert(offsetof(mm7::Lod, type) == 532);
	static_assert(offsetof(mm7::Lod, chapterHandle) == 548);
	static_assert(offsetof(mm7::Lod, chapterSize) == 552);
	static_assert(offsetof(mm7::Lod, files_size) == 556);
	static_assert(offsetof(mm7::Lod, files) == 560);
	static_assert(offsetof(mm7::Lod, filesOffset) == 564);



	struct LodRecord // size: 0x48
	{
		uint32_t lodPtr;
		uint32_t namePtr;
		std::array<char, 64> name; // fixed size string, requires null terminator
	};
	static_assert(sizeof(mm7::LodRecord) == 0x48, "Invalid \"mm7::LodRecord\" structure size");
	static_assert(offsetof(mm7::LodRecord, namePtr) == 4);
	static_assert(offsetof(mm7::LodRecord, name) == 8);



	struct CustomLods // size: 0x4804
	{
		int32_t recordIndex;
		std::array<mm7::LodRecord, 256> records;
	};
	static_assert(sizeof(mm7::CustomLods) == 0x4804, "Invalid \"mm7::CustomLods\" structure size");
	static_assert(offsetof(mm7::CustomLods, records) == 4);
}
namespace mm8
{
	struct LodSpriteD3D // size: 0x28
	{
		const char* name; // PChar (read-only)
		int32_t palette;
		uint32_t surface;
		uint32_t texture;
		int32_t areaX;
		int32_t areaY;
		int32_t bufferWidth;
		int32_t bufferHeight;
		int32_t areaWidth;
		int32_t areaHeight;
	};
	static_assert(sizeof(mm8::LodSpriteD3D) == 0x28, "Invalid \"mm8::LodSpriteD3D\" structure size");
	static_assert(offsetof(mm8::LodSpriteD3D, palette) == 4);
	static_assert(offsetof(mm8::LodSpriteD3D, surface) == 8);
	static_assert(offsetof(mm8::LodSpriteD3D, texture) == 12);
	static_assert(offsetof(mm8::LodSpriteD3D, areaX) == 16);
	static_assert(offsetof(mm8::LodSpriteD3D, areaY) == 20);
	static_assert(offsetof(mm8::LodSpriteD3D, bufferWidth) == 24);
	static_assert(offsetof(mm8::LodSpriteD3D, bufferHeight) == 28);
	static_assert(offsetof(mm8::LodSpriteD3D, areaWidth) == 32);
	static_assert(offsetof(mm8::LodSpriteD3D, areaHeight) == 36);



	struct LodSpriteLine // size: 0x8
	{
		int16_t l;
		int16_t r;
		uint8_t* pos;
	};
	static_assert(sizeof(mm8::LodSpriteLine) == 0x8, "Invalid \"mm8::LodSpriteLine\" structure size");
	static_assert(offsetof(mm8::LodSpriteLine, r) == 2);
	static_assert(offsetof(mm8::LodSpriteLine, pos) == 4);



	struct LodSprite // size: 0x28
	{
		std::array<char, 12> name; // fixed size string, requires null terminator
		int32_t dataSize;
		int16_t width;
		union
		{
			uint32_t lines_size;
			struct
			{
				int16_t height;
				int16_t palette;
			};
		};
		SKIP(2);
		int16_t YSkip;
		SKIP(2);
		int32_t unpackedSize;
		mm8::LodSpriteLine* lines; // size field offset is 0x12
		uint32_t buffer;
	};
	static_assert(sizeof(mm8::LodSprite) == 0x28, "Invalid \"mm8::LodSprite\" structure size");
	static_assert(offsetof(mm8::LodSprite, dataSize) == 12);
	static_assert(offsetof(mm8::LodSprite, width) == 16);
	static_assert(offsetof(mm8::LodSprite, lines_size) == 18);
	static_assert(offsetof(mm8::LodSprite, height) == 18);
	static_assert(offsetof(mm8::LodSprite, palette) == 20);
	static_assert(offsetof(mm8::LodSprite, YSkip) == 24);
	static_assert(offsetof(mm8::LodSprite, unpackedSize) == 28);
	static_assert(offsetof(mm8::LodSprite, lines) == 32);
	static_assert(offsetof(mm8::LodSprite, buffer) == 36);



	struct LodRecord // size: 0x48
	{
		uint32_t lodPtr;
		uint32_t namePtr;
		std::array<char, 64> name; // fixed size string, requires null terminator
	};
	static_assert(sizeof(mm8::LodRecord) == 0x48, "Invalid \"mm8::LodRecord\" structure size");
	static_assert(offsetof(mm8::LodRecord, namePtr) == 4);
	static_assert(offsetof(mm8::LodRecord, name) == 8);



	struct CustomLods // size: 0x4804
	{
		int32_t recordIndex;
		std::array<mm8::LodRecord, 256> records;
	};
	static_assert(sizeof(mm8::CustomLods) == 0x4804, "Invalid \"mm8::CustomLods\" structure size");
	static_assert(offsetof(mm8::CustomLods, records) == 4);



	struct LodFile // size: 0x20
	{
		std::array<char, 16> name; // fixed size string, requires null terminator
		int32_t offset;
		int32_t size;
		SKIP(8);
	};
	static_assert(sizeof(mm8::LodFile) == 0x20, "Invalid \"mm8::LodFile\" structure size");
	static_assert(offsetof(mm8::LodFile, offset) == 16);
	static_assert(offsetof(mm8::LodFile, size) == 20);



	struct SpritesLod // size: 0xECB8
	{
		static mm8::LodSprite* spritesSW; // converted to pointer to not break with limits removal scripts
		static uint32_t* spritesSW_sizePtr; // pointer to size, set during initialization by getting data from lua

		uint32_t file;
		std::array<char, 256> fileName; // fixed size string, requires null terminator
		uint32_t loaded; // 4-byte boolean
		uint32_t IOBuffer;
		int32_t IOBufferSize;
		int32_t lodHeaderSignature;
		SKIP(80);
		std::array<char, 80> description; // fixed size string, requires null terminator
		SKIP(8);
		int32_t archivesCount;
		SKIP(80);
		uint32_t archivesCArray;
		std::array<char, 16> type; // fixed size string, requires null terminator
		uint32_t chapterHandle;
		uint32_t chapterSize;
		uint32_t files_size;
		mm8::LodFile* files; // size field offset is 0x22C
		uint32_t filesOffset;
		SKIP(60020);
		uint32_t isHardware; // 4-byte boolean
		mm8::LodSpriteD3D* spritesD3D; // size field offset is 0xECB4
		uint32_t spritesD3D_size;
	};
	static_assert(sizeof(mm8::SpritesLod) == 0xECB8, "Invalid \"mm8::SpritesLod\" structure size");
	static_assert(offsetof(mm8::SpritesLod, fileName) == 4);
	static_assert(offsetof(mm8::SpritesLod, loaded) == 260);
	static_assert(offsetof(mm8::SpritesLod, IOBuffer) == 264);
	static_assert(offsetof(mm8::SpritesLod, IOBufferSize) == 268);
	static_assert(offsetof(mm8::SpritesLod, lodHeaderSignature) == 272);
	static_assert(offsetof(mm8::SpritesLod, description) == 356);
	static_assert(offsetof(mm8::SpritesLod, archivesCount) == 444);
	static_assert(offsetof(mm8::SpritesLod, archivesCArray) == 528);
	static_assert(offsetof(mm8::SpritesLod, type) == 532);
	static_assert(offsetof(mm8::SpritesLod, chapterHandle) == 548);
	static_assert(offsetof(mm8::SpritesLod, chapterSize) == 552);
	static_assert(offsetof(mm8::SpritesLod, files_size) == 556);
	static_assert(offsetof(mm8::SpritesLod, files) == 560);
	static_assert(offsetof(mm8::SpritesLod, filesOffset) == 564);
	static_assert(offsetof(mm8::SpritesLod, isHardware) == 60588);
	static_assert(offsetof(mm8::SpritesLod, spritesD3D) == 60592);
	static_assert(offsetof(mm8::SpritesLod, spritesD3D_size) == 60596);



	struct Lod // size: 0x23C
	{
		uint32_t file;
		std::array<char, 256> fileName; // fixed size string, requires null terminator
		uint32_t loaded; // 4-byte boolean
		uint32_t IOBuffer;
		int32_t IOBufferSize;
		int32_t lodHeaderSignature;
		SKIP(80);
		std::array<char, 80> description; // fixed size string, requires null terminator
		SKIP(8);
		int32_t archivesCount;
		SKIP(80);
		uint32_t archivesCArray;
		std::array<char, 16> type; // fixed size string, requires null terminator
		uint32_t chapterHandle;
		uint32_t chapterSize;
		uint32_t files_size;
		mm8::LodFile* files; // size field offset is 0x22C
		uint32_t filesOffset;
		SKIP(4);
	};
	static_assert(sizeof(mm8::Lod) == 0x23C, "Invalid \"mm8::Lod\" structure size");
	static_assert(offsetof(mm8::Lod, fileName) == 4);
	static_assert(offsetof(mm8::Lod, loaded) == 260);
	static_assert(offsetof(mm8::Lod, IOBuffer) == 264);
	static_assert(offsetof(mm8::Lod, IOBufferSize) == 268);
	static_assert(offsetof(mm8::Lod, lodHeaderSignature) == 272);
	static_assert(offsetof(mm8::Lod, description) == 356);
	static_assert(offsetof(mm8::Lod, archivesCount) == 444);
	static_assert(offsetof(mm8::Lod, archivesCArray) == 528);
	static_assert(offsetof(mm8::Lod, type) == 532);
	static_assert(offsetof(mm8::Lod, chapterHandle) == 548);
	static_assert(offsetof(mm8::Lod, chapterSize) == 552);
	static_assert(offsetof(mm8::Lod, files_size) == 556);
	static_assert(offsetof(mm8::Lod, files) == 560);
	static_assert(offsetof(mm8::Lod, filesOffset) == 564);



	struct LodBitmap // size: 0x48
	{
		std::array<char, 16> name; // fixed size string, requires null terminator
		int32_t bmpSize;
		int32_t dataSize;
		int16_t width;
		int16_t height;
		int16_t widthLn2;
		int16_t heightLn2;
		int16_t widthMinus1;
		int16_t heightMinus1;
		int16_t palette;
		int16_t loadedPalette;
		int32_t unpackedSize;
		uint32_t bits;
		int32_t image;
		int32_t imageDiv2;
		int32_t imageDiv4;
		int32_t imageDiv8;
		int32_t palette16;
		int32_t palette24;
	};
	static_assert(sizeof(mm8::LodBitmap) == 0x48, "Invalid \"mm8::LodBitmap\" structure size");
	static_assert(offsetof(mm8::LodBitmap, bmpSize) == 16);
	static_assert(offsetof(mm8::LodBitmap, dataSize) == 20);
	static_assert(offsetof(mm8::LodBitmap, width) == 24);
	static_assert(offsetof(mm8::LodBitmap, height) == 26);
	static_assert(offsetof(mm8::LodBitmap, widthLn2) == 28);
	static_assert(offsetof(mm8::LodBitmap, heightLn2) == 30);
	static_assert(offsetof(mm8::LodBitmap, widthMinus1) == 32);
	static_assert(offsetof(mm8::LodBitmap, heightMinus1) == 34);
	static_assert(offsetof(mm8::LodBitmap, palette) == 36);
	static_assert(offsetof(mm8::LodBitmap, loadedPalette) == 38);
	static_assert(offsetof(mm8::LodBitmap, unpackedSize) == 40);
	static_assert(offsetof(mm8::LodBitmap, bits) == 44);
	static_assert(offsetof(mm8::LodBitmap, image) == 48);
	static_assert(offsetof(mm8::LodBitmap, imageDiv2) == 52);
	static_assert(offsetof(mm8::LodBitmap, imageDiv4) == 56);
	static_assert(offsetof(mm8::LodBitmap, imageDiv8) == 60);
	static_assert(offsetof(mm8::LodBitmap, palette16) == 64);
	static_assert(offsetof(mm8::LodBitmap, palette24) == 68);



	struct BitmapsLod // size: 0x11BB8
	{
		uint32_t file;
		std::array<char, 256> fileName; // fixed size string, requires null terminator
		uint32_t loaded; // 4-byte boolean
		uint32_t IOBuffer;
		int32_t IOBufferSize;
		int32_t lodHeaderSignature;
		SKIP(80);
		std::array<char, 80> description; // fixed size string, requires null terminator
		SKIP(8);
		int32_t archivesCount;
		SKIP(80);
		uint32_t archivesCArray;
		std::array<char, 16> type; // fixed size string, requires null terminator
		uint32_t chapterHandle;
		uint32_t chapterSize;
		uint32_t files_size;
		mm8::LodFile* files; // size field offset is 0x22C
		uint32_t filesOffset;
		SKIP(4);
		std::array<mm8::LodBitmap, 1000> bitmaps; // size field offset is 0x11B7C
		union
		{
			uint32_t D3D_Textures_size;
			uint32_t D3D_Surfaces_size;
			uint32_t bitmaps_size;
		};
		SKIP(36);
		uint32_t keepCompressed; // 4-byte boolean
		uint32_t isHardware; // 4-byte boolean
		SKIP(4);
		uint32_t* D3D_Surfaces; // size field offset is 0x11B7C
		uint32_t* D3D_Textures; // size field offset is 0x11B7C
	};
	static_assert(sizeof(mm8::BitmapsLod) == 0x11BB8, "Invalid \"mm8::BitmapsLod\" structure size");
	static_assert(offsetof(mm8::BitmapsLod, fileName) == 4);
	static_assert(offsetof(mm8::BitmapsLod, loaded) == 260);
	static_assert(offsetof(mm8::BitmapsLod, IOBuffer) == 264);
	static_assert(offsetof(mm8::BitmapsLod, IOBufferSize) == 268);
	static_assert(offsetof(mm8::BitmapsLod, lodHeaderSignature) == 272);
	static_assert(offsetof(mm8::BitmapsLod, description) == 356);
	static_assert(offsetof(mm8::BitmapsLod, archivesCount) == 444);
	static_assert(offsetof(mm8::BitmapsLod, archivesCArray) == 528);
	static_assert(offsetof(mm8::BitmapsLod, type) == 532);
	static_assert(offsetof(mm8::BitmapsLod, chapterHandle) == 548);
	static_assert(offsetof(mm8::BitmapsLod, chapterSize) == 552);
	static_assert(offsetof(mm8::BitmapsLod, files_size) == 556);
	static_assert(offsetof(mm8::BitmapsLod, files) == 560);
	static_assert(offsetof(mm8::BitmapsLod, filesOffset) == 564);
	static_assert(offsetof(mm8::BitmapsLod, bitmaps) == 572);
	static_assert(offsetof(mm8::BitmapsLod, D3D_Textures_size) == 72572);
	static_assert(offsetof(mm8::BitmapsLod, D3D_Surfaces_size) == 72572);
	static_assert(offsetof(mm8::BitmapsLod, bitmaps_size) == 72572);
	static_assert(offsetof(mm8::BitmapsLod, keepCompressed) == 72612);
	static_assert(offsetof(mm8::BitmapsLod, isHardware) == 72616);
	static_assert(offsetof(mm8::BitmapsLod, D3D_Surfaces) == 72624);
	static_assert(offsetof(mm8::BitmapsLod, D3D_Textures) == 72628);
}

#pragma pack(pop)