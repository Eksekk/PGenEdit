#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct LodSpriteLine // size: 0x8
	{
		int16_t l; // 0x0 (0 decimal)
		int16_t r; // 0x2 (2 decimal)
		uint8_t* pos; // 0x4 (4 decimal)
	};
	static_assert(sizeof(mm6::LodSpriteLine) == 0x8, "Invalid \"mm6::LodSpriteLine\" structure size");
	static_assert(offsetof(mm6::LodSpriteLine, r) == 2);
	static_assert(offsetof(mm6::LodSpriteLine, pos) == 4);



	struct LodSprite // size: 0x28
	{
		std::array<char, 12> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		int32_t dataSize; // 0xC (12 decimal)
		int16_t width; // 0x10 (16 decimal)
		union
		{
			uint32_t lines_size; // 0x12 (18 decimal)
			struct
			{
				int16_t height; // 0x12 (18 decimal)
				int16_t palette; // 0x14 (20 decimal)
			};
		};
		SKIP(2);
		int16_t YSkip; // 0x18 (24 decimal)
		SKIP(2);
		int32_t unpackedSize; // 0x1C (28 decimal)
		mm6::LodSpriteLine* lines; // size field offset is 0x12 | 0x20 (32 decimal)
		uint32_t buffer; // 0x24 (36 decimal)
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



	struct LodSpriteD3D // size: 0x28
	{
		const char* name; // PChar (read-only) | 0x0 (0 decimal)
		int32_t palette; // 0x4 (4 decimal)
		uint32_t surface; // 0x8 (8 decimal)
		uint32_t texture; // 0xC (12 decimal)
		int32_t areaX; // 0x10 (16 decimal)
		int32_t areaY; // 0x14 (20 decimal)
		int32_t bufferWidth; // 0x18 (24 decimal)
		int32_t bufferHeight; // 0x1C (28 decimal)
		int32_t areaWidth; // 0x20 (32 decimal)
		int32_t areaHeight; // 0x24 (36 decimal)
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



	struct LodPcx // size: 0x28
	{
		SKIP(16);
		int32_t bufSize; // 0x10 (16 decimal)
		int16_t width; // 0x14 (20 decimal)
		int16_t height; // 0x16 (22 decimal)
		int16_t widthLn2; // 0x18 (24 decimal)
		int16_t heightLn2; // 0x1A (26 decimal)
		int16_t widthMinus1; // 0x1C (28 decimal)
		int16_t heightMinus1; // 0x1E (30 decimal)
		uint32_t bits; // 0x20 (32 decimal)
		int32_t image; // 0x24 (36 decimal)
	};
	static_assert(sizeof(mm6::LodPcx) == 0x28, "Invalid \"mm6::LodPcx\" structure size");
	static_assert(offsetof(mm6::LodPcx, bufSize) == 16);
	static_assert(offsetof(mm6::LodPcx, width) == 20);
	static_assert(offsetof(mm6::LodPcx, height) == 22);
	static_assert(offsetof(mm6::LodPcx, widthLn2) == 24);
	static_assert(offsetof(mm6::LodPcx, heightLn2) == 26);
	static_assert(offsetof(mm6::LodPcx, widthMinus1) == 28);
	static_assert(offsetof(mm6::LodPcx, heightMinus1) == 30);
	static_assert(offsetof(mm6::LodPcx, bits) == 32);
	static_assert(offsetof(mm6::LodPcx, image) == 36);



	struct LodRecord // size: 0x48
	{
		uint32_t lodPtr; // 0x0 (0 decimal)
		uint32_t namePtr; // 0x4 (4 decimal) | MMExt info: Pointer passed to Load* function
		std::array<char, 64> name; // fixed size string, requires null terminator | 0x8 (8 decimal)
	};
	static_assert(sizeof(mm6::LodRecord) == 0x48, "Invalid \"mm6::LodRecord\" structure size");
	static_assert(offsetof(mm6::LodRecord, namePtr) == 4);
	static_assert(offsetof(mm6::LodRecord, name) == 8);



	struct CustomLods // size: 0x4804
	{
		int32_t recordIndex; // 0x0 (0 decimal)
		std::array<mm6::LodRecord, 256> records; // 0x4 (4 decimal)
	};
	static_assert(sizeof(mm6::CustomLods) == 0x4804, "Invalid \"mm6::CustomLods\" structure size");
	static_assert(offsetof(mm6::CustomLods, records) == 4);



	struct LodFile // size: 0x20
	{
		std::array<char, 16> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		int32_t offset; // 0x10 (16 decimal)
		int32_t size; // 0x14 (20 decimal)
		SKIP(8);
	};
	static_assert(sizeof(mm6::LodFile) == 0x20, "Invalid \"mm6::LodFile\" structure size");
	static_assert(offsetof(mm6::LodFile, offset) == 16);
	static_assert(offsetof(mm6::LodFile, size) == 20);



	struct SpritesLod // size: 0xECB8
	{
		static mm6::LodSprite* spritesSW; // original offset 0x23C (572 decimal)element size: 0x28 (40 decimal)
		static uint32_t* spritesSW_sizePtr; // Offset/size: 0xEC9C (60572 decimal)

		uint32_t file; // 0x0 (0 decimal)
		std::array<char, 256> fileName; // fixed size string, requires null terminator | 0x4 (4 decimal)
		uint32_t loaded; // 4-byte boolean | 0x104 (260 decimal)
		uint32_t IOBuffer; // 0x108 (264 decimal)
		int32_t IOBufferSize; // 0x10C (268 decimal)
		int32_t lodHeaderSignature; // 0x110 (272 decimal)
		SKIP(80);
		std::array<char, 80> description; // fixed size string, requires null terminator | 0x164 (356 decimal)
		SKIP(8);
		int32_t archivesCount; // 0x1BC (444 decimal)
		SKIP(80);
		uint32_t archivesCArray; // 0x210 (528 decimal)
		std::array<char, 16> type; // fixed size string, requires null terminator | 0x214 (532 decimal)
		uint32_t chapterHandle; // 0x224 (548 decimal)
		uint32_t chapterSize; // 0x228 (552 decimal)
		uint32_t files_size; // 0x22C (556 decimal)
		mm6::LodFile* files; // size field offset is 0x22C | 0x230 (560 decimal)
		uint32_t filesOffset; // 0x234 (564 decimal)
		SKIP(60020);
		uint32_t isHardware; // 4-byte boolean | 0xECAC (60588 decimal)
		mm6::LodSpriteD3D* spritesD3D; // size field offset is 0xECB4 | 0xECB0 (60592 decimal)
		uint32_t spritesD3D_size; // 0xECB4 (60596 decimal)
		bool __thiscall hasFile(/*name*/); // address: 0x44CCA0 | defaults: (this), ""
		char* __thiscall findFile(/*name, unsorted = false*/); // address: 0x44CBC0 | defaults: (this), "", false
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



	struct Lod // size: 0x23C
	{
		uint32_t file; // 0x0 (0 decimal)
		std::array<char, 256> fileName; // fixed size string, requires null terminator | 0x4 (4 decimal)
		uint32_t loaded; // 4-byte boolean | 0x104 (260 decimal)
		uint32_t IOBuffer; // 0x108 (264 decimal)
		int32_t IOBufferSize; // 0x10C (268 decimal)
		int32_t lodHeaderSignature; // 0x110 (272 decimal)
		SKIP(80);
		std::array<char, 80> description; // fixed size string, requires null terminator | 0x164 (356 decimal)
		SKIP(8);
		int32_t archivesCount; // 0x1BC (444 decimal)
		SKIP(80);
		uint32_t archivesCArray; // 0x210 (528 decimal)
		std::array<char, 16> type; // fixed size string, requires null terminator | 0x214 (532 decimal)
		uint32_t chapterHandle; // 0x224 (548 decimal)
		uint32_t chapterSize; // 0x228 (552 decimal)
		uint32_t files_size; // 0x22C (556 decimal)
		mm6::LodFile* files; // size field offset is 0x22C | 0x230 (560 decimal)
		uint32_t filesOffset; // 0x234 (564 decimal)
		SKIP(4);
		bool __thiscall hasFile(/*name*/); // address: 0x44CCA0 | defaults: (this), ""
		char* __thiscall findFile(/*name, unsorted = false*/); // address: 0x44CBC0 | defaults: (this), "", false
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



	struct LodBitmap // size: 0x48
	{
		std::array<char, 16> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		int32_t bmpSize; // 0x10 (16 decimal)
		int32_t dataSize; // 0x14 (20 decimal)
		int16_t width; // 0x18 (24 decimal)
		int16_t height; // 0x1A (26 decimal)
		int16_t widthLn2; // 0x1C (28 decimal)
		int16_t heightLn2; // 0x1E (30 decimal)
		int16_t widthMinus1; // 0x20 (32 decimal)
		int16_t heightMinus1; // 0x22 (34 decimal)
		int16_t palette; // 0x24 (36 decimal)
		int16_t loadedPalette; // 0x26 (38 decimal)
		int32_t unpackedSize; // 0x28 (40 decimal)
		uint32_t bits; // 0x2C (44 decimal)
		int32_t image; // 0x30 (48 decimal)
		int32_t imageDiv2; // 0x34 (52 decimal)
		int32_t imageDiv4; // 0x38 (56 decimal)
		int32_t imageDiv8; // 0x3C (60 decimal)
		int32_t palette16; // 0x40 (64 decimal)
		int32_t palette24; // 0x44 (68 decimal)
		int __thiscall destroy(); // address: 0x40A0C0 | defaults: (this)
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



	struct BitmapsLod // size: 0x8F08
	{
		uint32_t file; // 0x0 (0 decimal)
		std::array<char, 256> fileName; // fixed size string, requires null terminator | 0x4 (4 decimal)
		uint32_t loaded; // 4-byte boolean | 0x104 (260 decimal)
		uint32_t IOBuffer; // 0x108 (264 decimal)
		int32_t IOBufferSize; // 0x10C (268 decimal)
		int32_t lodHeaderSignature; // 0x110 (272 decimal)
		SKIP(80);
		std::array<char, 80> description; // fixed size string, requires null terminator | 0x164 (356 decimal)
		SKIP(8);
		int32_t archivesCount; // 0x1BC (444 decimal)
		SKIP(80);
		uint32_t archivesCArray; // 0x210 (528 decimal)
		std::array<char, 16> type; // fixed size string, requires null terminator | 0x214 (532 decimal)
		uint32_t chapterHandle; // 0x224 (548 decimal)
		uint32_t chapterSize; // 0x228 (552 decimal)
		uint32_t files_size; // 0x22C (556 decimal)
		mm6::LodFile* files; // size field offset is 0x22C | 0x230 (560 decimal)
		uint32_t filesOffset; // 0x234 (564 decimal)
		SKIP(4);
		std::array<mm6::LodBitmap, 500> bitmaps; // size field offset is 0x8EDC | 0x23C (572 decimal)
		union
		{
			int32_t bitmapsCount; // 0x8EDC (36572 decimal)
			uint32_t bitmaps_size; // 0x8EDC (36572 decimal)
		};
		SKIP(12);
		int32_t redBits; // 0x8EEC (36588 decimal)
		int32_t greenBits; // 0x8EF0 (36592 decimal)
		int32_t blueBits; // 0x8EF4 (36596 decimal)
		int32_t nonTmpCount; // 0x8EF8 (36600 decimal)
		int32_t tmpIndex; // 0x8EFC (36604 decimal)
		SKIP(4);
		uint32_t keepCompressed; // 4-byte boolean | 0x8F04 (36612 decimal)
		int __thiscall cleanup(); // address: 0x40B2F0 | defaults: (this)
		char* __thiscall findFile(/*name, unsorted = false*/); // address: 0x44CBC0 | defaults: (this), "", false
		bool __thiscall hasFile(/*name*/); // address: 0x44CCA0 | defaults: (this), ""
		int __thiscall loadBitmapInPlace(/*bmp:structs.LodBitmap, name, unused_must_be_2 = 2*/); // address: 0x40BD30 | defaults: (this), 0, "", 2
	};
	static_assert(sizeof(mm6::BitmapsLod) == 0x8F08, "Invalid \"mm6::BitmapsLod\" structure size");
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
	static_assert(offsetof(mm6::BitmapsLod, bitmapsCount) == 36572);
	static_assert(offsetof(mm6::BitmapsLod, bitmaps_size) == 36572);
	static_assert(offsetof(mm6::BitmapsLod, redBits) == 36588);
	static_assert(offsetof(mm6::BitmapsLod, greenBits) == 36592);
	static_assert(offsetof(mm6::BitmapsLod, blueBits) == 36596);
	static_assert(offsetof(mm6::BitmapsLod, nonTmpCount) == 36600);
	static_assert(offsetof(mm6::BitmapsLod, tmpIndex) == 36604);
	static_assert(offsetof(mm6::BitmapsLod, keepCompressed) == 36612);
}
namespace mm7
{
	struct LodSpriteLine // size: 0x8
	{
		int16_t l; // 0x0 (0 decimal)
		int16_t r; // 0x2 (2 decimal)
		uint8_t* pos; // 0x4 (4 decimal)
	};
	static_assert(sizeof(mm7::LodSpriteLine) == 0x8, "Invalid \"mm7::LodSpriteLine\" structure size");
	static_assert(offsetof(mm7::LodSpriteLine, r) == 2);
	static_assert(offsetof(mm7::LodSpriteLine, pos) == 4);



	struct LodSprite // size: 0x28
	{
		std::array<char, 12> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		int32_t dataSize; // 0xC (12 decimal)
		int16_t width; // 0x10 (16 decimal)
		union
		{
			uint32_t lines_size; // 0x12 (18 decimal)
			struct
			{
				int16_t height; // 0x12 (18 decimal)
				int16_t palette; // 0x14 (20 decimal)
			};
		};
		SKIP(2);
		int16_t YSkip; // 0x18 (24 decimal)
		SKIP(2);
		int32_t unpackedSize; // 0x1C (28 decimal)
		mm7::LodSpriteLine* lines; // size field offset is 0x12 | 0x20 (32 decimal)
		uint32_t buffer; // 0x24 (36 decimal)
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



	struct LodSpriteD3D // size: 0x28
	{
		const char* name; // PChar (read-only) | 0x0 (0 decimal)
		int32_t palette; // 0x4 (4 decimal)
		uint32_t surface; // 0x8 (8 decimal)
		uint32_t texture; // 0xC (12 decimal)
		int32_t areaX; // 0x10 (16 decimal)
		int32_t areaY; // 0x14 (20 decimal)
		int32_t bufferWidth; // 0x18 (24 decimal)
		int32_t bufferHeight; // 0x1C (28 decimal)
		int32_t areaWidth; // 0x20 (32 decimal)
		int32_t areaHeight; // 0x24 (36 decimal)
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



	struct LodPcx // size: 0x28
	{
		SKIP(16);
		int32_t bufSize; // 0x10 (16 decimal)
		int16_t width; // 0x14 (20 decimal)
		int16_t height; // 0x16 (22 decimal)
		int16_t widthLn2; // 0x18 (24 decimal)
		int16_t heightLn2; // 0x1A (26 decimal)
		int16_t widthMinus1; // 0x1C (28 decimal)
		int16_t heightMinus1; // 0x1E (30 decimal)
		uint32_t bits; // 0x20 (32 decimal)
		int32_t image; // 0x24 (36 decimal)
	};
	static_assert(sizeof(mm7::LodPcx) == 0x28, "Invalid \"mm7::LodPcx\" structure size");
	static_assert(offsetof(mm7::LodPcx, bufSize) == 16);
	static_assert(offsetof(mm7::LodPcx, width) == 20);
	static_assert(offsetof(mm7::LodPcx, height) == 22);
	static_assert(offsetof(mm7::LodPcx, widthLn2) == 24);
	static_assert(offsetof(mm7::LodPcx, heightLn2) == 26);
	static_assert(offsetof(mm7::LodPcx, widthMinus1) == 28);
	static_assert(offsetof(mm7::LodPcx, heightMinus1) == 30);
	static_assert(offsetof(mm7::LodPcx, bits) == 32);
	static_assert(offsetof(mm7::LodPcx, image) == 36);



	struct LodRecord // size: 0x48
	{
		uint32_t lodPtr; // 0x0 (0 decimal)
		uint32_t namePtr; // 0x4 (4 decimal) | MMExt info: Pointer passed to Load* function
		std::array<char, 64> name; // fixed size string, requires null terminator | 0x8 (8 decimal)
	};
	static_assert(sizeof(mm7::LodRecord) == 0x48, "Invalid \"mm7::LodRecord\" structure size");
	static_assert(offsetof(mm7::LodRecord, namePtr) == 4);
	static_assert(offsetof(mm7::LodRecord, name) == 8);



	struct CustomLods // size: 0x4804
	{
		int32_t recordIndex; // 0x0 (0 decimal)
		std::array<mm7::LodRecord, 256> records; // 0x4 (4 decimal)
	};
	static_assert(sizeof(mm7::CustomLods) == 0x4804, "Invalid \"mm7::CustomLods\" structure size");
	static_assert(offsetof(mm7::CustomLods, records) == 4);



	struct LodFile // size: 0x20
	{
		std::array<char, 16> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		int32_t offset; // 0x10 (16 decimal)
		int32_t size; // 0x14 (20 decimal)
		SKIP(8);
	};
	static_assert(sizeof(mm7::LodFile) == 0x20, "Invalid \"mm7::LodFile\" structure size");
	static_assert(offsetof(mm7::LodFile, offset) == 16);
	static_assert(offsetof(mm7::LodFile, size) == 20);



	struct SpritesLod // size: 0xECB8
	{
		static mm7::LodSprite* spritesSW; // original offset 0x2C386EC (46368492 decimal)element size: 0x28 (40 decimal)
		static uint32_t* spritesSW_sizePtr; // Offset/size: 0xEC9C (60572 decimal)

		uint32_t file; // 0x0 (0 decimal)
		std::array<char, 256> fileName; // fixed size string, requires null terminator | 0x4 (4 decimal)
		uint32_t loaded; // 4-byte boolean | 0x104 (260 decimal)
		uint32_t IOBuffer; // 0x108 (264 decimal)
		int32_t IOBufferSize; // 0x10C (268 decimal)
		int32_t lodHeaderSignature; // 0x110 (272 decimal)
		SKIP(80);
		std::array<char, 80> description; // fixed size string, requires null terminator | 0x164 (356 decimal)
		SKIP(8);
		int32_t archivesCount; // 0x1BC (444 decimal)
		SKIP(80);
		uint32_t archivesCArray; // 0x210 (528 decimal)
		std::array<char, 16> type; // fixed size string, requires null terminator | 0x214 (532 decimal)
		uint32_t chapterHandle; // 0x224 (548 decimal)
		uint32_t chapterSize; // 0x228 (552 decimal)
		uint32_t files_size; // 0x22C (556 decimal)
		mm7::LodFile* files; // size field offset is 0x22C | 0x230 (560 decimal)
		uint32_t filesOffset; // 0x234 (564 decimal)
		SKIP(60020);
		uint32_t isHardware; // 4-byte boolean | 0xECAC (60588 decimal)
		mm7::LodSpriteD3D* spritesD3D; // size field offset is 0xECB4 | 0xECB0 (60592 decimal)
		uint32_t spritesD3D_size; // 0xECB4 (60596 decimal)
		bool __thiscall hasFile(/*name*/); // address: 0x461659 | defaults: (this), ""
		char* __thiscall findFile(/*name, unsorted = false*/); // address: 0x4615BD | defaults: (this), "", false
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
		uint32_t file; // 0x0 (0 decimal)
		std::array<char, 256> fileName; // fixed size string, requires null terminator | 0x4 (4 decimal)
		uint32_t loaded; // 4-byte boolean | 0x104 (260 decimal)
		uint32_t IOBuffer; // 0x108 (264 decimal)
		int32_t IOBufferSize; // 0x10C (268 decimal)
		int32_t lodHeaderSignature; // 0x110 (272 decimal)
		SKIP(80);
		std::array<char, 80> description; // fixed size string, requires null terminator | 0x164 (356 decimal)
		SKIP(8);
		int32_t archivesCount; // 0x1BC (444 decimal)
		SKIP(80);
		uint32_t archivesCArray; // 0x210 (528 decimal)
		std::array<char, 16> type; // fixed size string, requires null terminator | 0x214 (532 decimal)
		uint32_t chapterHandle; // 0x224 (548 decimal)
		uint32_t chapterSize; // 0x228 (552 decimal)
		uint32_t files_size; // 0x22C (556 decimal)
		mm7::LodFile* files; // size field offset is 0x22C | 0x230 (560 decimal)
		uint32_t filesOffset; // 0x234 (564 decimal)
		SKIP(4);
		bool __thiscall hasFile(/*name*/); // address: 0x461659 | defaults: (this), ""
		char* __thiscall findFile(/*name, unsorted = false*/); // address: 0x4615BD | defaults: (this), "", false
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



	struct LodBitmap // size: 0x48
	{
		std::array<char, 16> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		int32_t bmpSize; // 0x10 (16 decimal)
		int32_t dataSize; // 0x14 (20 decimal)
		int16_t width; // 0x18 (24 decimal)
		int16_t height; // 0x1A (26 decimal)
		int16_t widthLn2; // 0x1C (28 decimal)
		int16_t heightLn2; // 0x1E (30 decimal)
		int16_t widthMinus1; // 0x20 (32 decimal)
		int16_t heightMinus1; // 0x22 (34 decimal)
		int16_t palette; // 0x24 (36 decimal)
		int16_t loadedPalette; // 0x26 (38 decimal)
		int32_t unpackedSize; // 0x28 (40 decimal)
		uint32_t bits; // 0x2C (44 decimal)
		int32_t image; // 0x30 (48 decimal)
		int32_t imageDiv2; // 0x34 (52 decimal)
		int32_t imageDiv4; // 0x38 (56 decimal)
		int32_t imageDiv8; // 0x3C (60 decimal)
		int32_t palette16; // 0x40 (64 decimal)
		int32_t palette24; // 0x44 (68 decimal)
		int __thiscall destroy(); // address: 0x40F788 | defaults: (this)
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



	struct BitmapsLod // size: 0x11BB8
	{
		uint32_t file; // 0x0 (0 decimal)
		std::array<char, 256> fileName; // fixed size string, requires null terminator | 0x4 (4 decimal)
		uint32_t loaded; // 4-byte boolean | 0x104 (260 decimal)
		uint32_t IOBuffer; // 0x108 (264 decimal)
		int32_t IOBufferSize; // 0x10C (268 decimal)
		int32_t lodHeaderSignature; // 0x110 (272 decimal)
		SKIP(80);
		std::array<char, 80> description; // fixed size string, requires null terminator | 0x164 (356 decimal)
		SKIP(8);
		int32_t archivesCount; // 0x1BC (444 decimal)
		SKIP(80);
		uint32_t archivesCArray; // 0x210 (528 decimal)
		std::array<char, 16> type; // fixed size string, requires null terminator | 0x214 (532 decimal)
		uint32_t chapterHandle; // 0x224 (548 decimal)
		uint32_t chapterSize; // 0x228 (552 decimal)
		uint32_t files_size; // 0x22C (556 decimal)
		mm7::LodFile* files; // size field offset is 0x22C | 0x230 (560 decimal)
		uint32_t filesOffset; // 0x234 (564 decimal)
		SKIP(4);
		std::array<mm7::LodBitmap, 1000> bitmaps; // size field offset is 0x11B7C | 0x23C (572 decimal)
		union
		{
			int32_t bitmapsCount; // 0x11B7C (72572 decimal)
			uint32_t bitmaps_size; // 0x11B7C (72572 decimal)
			uint32_t D3D_Surfaces_size; // 0x11B7C (72572 decimal)
			uint32_t D3D_Textures_size; // 0x11B7C (72572 decimal)
		};
		SKIP(12);
		int32_t redBits; // 0x11B8C (72588 decimal)
		int32_t greenBits; // 0x11B90 (72592 decimal)
		int32_t blueBits; // 0x11B94 (72596 decimal)
		int32_t nonTmpCount; // 0x11B98 (72600 decimal)
		int32_t tmpIndex; // 0x11B9C (72604 decimal)
		SKIP(4);
		uint32_t keepCompressed; // 4-byte boolean | 0x11BA4 (72612 decimal)
		uint32_t isHardware; // 4-byte boolean | 0x11BA8 (72616 decimal)
		uint32_t* D3D_Surfaces; // size field offset is 0x11B7C | 0x11BAC (72620 decimal)
		uint32_t* D3D_Textures; // size field offset is 0x11B7C | 0x11BB0 (72624 decimal)
		SKIP(4);
		int __thiscall endTmp(); // address: 0x4114FE | defaults: (this)
		int __thiscall cleanup(); // address: 0x40F9D1 | defaults: (this)
		bool __thiscall hasFile(/*name*/); // address: 0x461659 | defaults: (this), ""
		int __thiscall loadBitmapInPlace(/*bmp:structs.LodBitmap, name, unused_must_be_2 = 2*/); // address: 0x41052E | defaults: (this), 0, "", 2
		char* __thiscall findFile(/*name, unsorted = false*/); // address: 0x4615BD | defaults: (this), "", false
		int __thiscall replaceBitmap(/*bmp:structs.LodBitmap, name, unused_must_be_2 = 2*/); // address: 0x4101BD | defaults: (this), 0, "", 2
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
	static_assert(offsetof(mm7::BitmapsLod, bitmapsCount) == 72572);
	static_assert(offsetof(mm7::BitmapsLod, bitmaps_size) == 72572);
	static_assert(offsetof(mm7::BitmapsLod, D3D_Surfaces_size) == 72572);
	static_assert(offsetof(mm7::BitmapsLod, D3D_Textures_size) == 72572);
	static_assert(offsetof(mm7::BitmapsLod, redBits) == 72588);
	static_assert(offsetof(mm7::BitmapsLod, greenBits) == 72592);
	static_assert(offsetof(mm7::BitmapsLod, blueBits) == 72596);
	static_assert(offsetof(mm7::BitmapsLod, nonTmpCount) == 72600);
	static_assert(offsetof(mm7::BitmapsLod, tmpIndex) == 72604);
	static_assert(offsetof(mm7::BitmapsLod, keepCompressed) == 72612);
	static_assert(offsetof(mm7::BitmapsLod, isHardware) == 72616);
	static_assert(offsetof(mm7::BitmapsLod, D3D_Surfaces) == 72620);
	static_assert(offsetof(mm7::BitmapsLod, D3D_Textures) == 72624);
}
namespace mm8
{
	struct LodSpriteLine // size: 0x8
	{
		int16_t l; // 0x0 (0 decimal)
		int16_t r; // 0x2 (2 decimal)
		uint8_t* pos; // 0x4 (4 decimal)
	};
	static_assert(sizeof(mm8::LodSpriteLine) == 0x8, "Invalid \"mm8::LodSpriteLine\" structure size");
	static_assert(offsetof(mm8::LodSpriteLine, r) == 2);
	static_assert(offsetof(mm8::LodSpriteLine, pos) == 4);



	struct LodSprite // size: 0x28
	{
		std::array<char, 12> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		int32_t dataSize; // 0xC (12 decimal)
		int16_t width; // 0x10 (16 decimal)
		union
		{
			uint32_t lines_size; // 0x12 (18 decimal)
			struct
			{
				int16_t height; // 0x12 (18 decimal)
				int16_t palette; // 0x14 (20 decimal)
			};
		};
		SKIP(2);
		int16_t YSkip; // 0x18 (24 decimal)
		SKIP(2);
		int32_t unpackedSize; // 0x1C (28 decimal)
		mm8::LodSpriteLine* lines; // size field offset is 0x12 | 0x20 (32 decimal)
		uint32_t buffer; // 0x24 (36 decimal)
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



	struct LodSpriteD3D // size: 0x28
	{
		const char* name; // PChar (read-only) | 0x0 (0 decimal)
		int32_t palette; // 0x4 (4 decimal)
		uint32_t surface; // 0x8 (8 decimal)
		uint32_t texture; // 0xC (12 decimal)
		int32_t areaX; // 0x10 (16 decimal)
		int32_t areaY; // 0x14 (20 decimal)
		int32_t bufferWidth; // 0x18 (24 decimal)
		int32_t bufferHeight; // 0x1C (28 decimal)
		int32_t areaWidth; // 0x20 (32 decimal)
		int32_t areaHeight; // 0x24 (36 decimal)
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



	struct LodRecord // size: 0x48
	{
		uint32_t lodPtr; // 0x0 (0 decimal)
		uint32_t namePtr; // 0x4 (4 decimal) | MMExt info: Pointer passed to Load* function
		std::array<char, 64> name; // fixed size string, requires null terminator | 0x8 (8 decimal)
	};
	static_assert(sizeof(mm8::LodRecord) == 0x48, "Invalid \"mm8::LodRecord\" structure size");
	static_assert(offsetof(mm8::LodRecord, namePtr) == 4);
	static_assert(offsetof(mm8::LodRecord, name) == 8);



	struct CustomLods // size: 0x4804
	{
		int32_t recordIndex; // 0x0 (0 decimal)
		std::array<mm8::LodRecord, 256> records; // 0x4 (4 decimal)
	};
	static_assert(sizeof(mm8::CustomLods) == 0x4804, "Invalid \"mm8::CustomLods\" structure size");
	static_assert(offsetof(mm8::CustomLods, records) == 4);



	struct LodFile // size: 0x20
	{
		std::array<char, 16> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		int32_t offset; // 0x10 (16 decimal)
		int32_t size; // 0x14 (20 decimal)
		SKIP(8);
	};
	static_assert(sizeof(mm8::LodFile) == 0x20, "Invalid \"mm8::LodFile\" structure size");
	static_assert(offsetof(mm8::LodFile, offset) == 16);
	static_assert(offsetof(mm8::LodFile, size) == 20);



	struct SpritesLod // size: 0xECB8
	{
		static mm8::LodSprite* spritesSW; // original offset 0x2BFA790 (46114704 decimal)element size: 0x28 (40 decimal)
		static uint32_t* spritesSW_sizePtr; // Offset/size: 0xEC9C (60572 decimal)

		uint32_t file; // 0x0 (0 decimal)
		std::array<char, 256> fileName; // fixed size string, requires null terminator | 0x4 (4 decimal)
		uint32_t loaded; // 4-byte boolean | 0x104 (260 decimal)
		uint32_t IOBuffer; // 0x108 (264 decimal)
		int32_t IOBufferSize; // 0x10C (268 decimal)
		int32_t lodHeaderSignature; // 0x110 (272 decimal)
		SKIP(80);
		std::array<char, 80> description; // fixed size string, requires null terminator | 0x164 (356 decimal)
		SKIP(8);
		int32_t archivesCount; // 0x1BC (444 decimal)
		SKIP(80);
		uint32_t archivesCArray; // 0x210 (528 decimal)
		std::array<char, 16> type; // fixed size string, requires null terminator | 0x214 (532 decimal)
		uint32_t chapterHandle; // 0x224 (548 decimal)
		uint32_t chapterSize; // 0x228 (552 decimal)
		uint32_t files_size; // 0x22C (556 decimal)
		mm8::LodFile* files; // size field offset is 0x22C | 0x230 (560 decimal)
		uint32_t filesOffset; // 0x234 (564 decimal)
		SKIP(60020);
		uint32_t isHardware; // 4-byte boolean | 0xECAC (60588 decimal)
		mm8::LodSpriteD3D* spritesD3D; // size field offset is 0xECB4 | 0xECB0 (60592 decimal)
		uint32_t spritesD3D_size; // 0xECB4 (60596 decimal)
		bool __thiscall hasFile(); // address: 0x45F09B | defaults: (this), ""
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
		uint32_t file; // 0x0 (0 decimal)
		std::array<char, 256> fileName; // fixed size string, requires null terminator | 0x4 (4 decimal)
		uint32_t loaded; // 4-byte boolean | 0x104 (260 decimal)
		uint32_t IOBuffer; // 0x108 (264 decimal)
		int32_t IOBufferSize; // 0x10C (268 decimal)
		int32_t lodHeaderSignature; // 0x110 (272 decimal)
		SKIP(80);
		std::array<char, 80> description; // fixed size string, requires null terminator | 0x164 (356 decimal)
		SKIP(8);
		int32_t archivesCount; // 0x1BC (444 decimal)
		SKIP(80);
		uint32_t archivesCArray; // 0x210 (528 decimal)
		std::array<char, 16> type; // fixed size string, requires null terminator | 0x214 (532 decimal)
		uint32_t chapterHandle; // 0x224 (548 decimal)
		uint32_t chapterSize; // 0x228 (552 decimal)
		uint32_t files_size; // 0x22C (556 decimal)
		mm8::LodFile* files; // size field offset is 0x22C | 0x230 (560 decimal)
		uint32_t filesOffset; // 0x234 (564 decimal)
		SKIP(4);
		bool __thiscall hasFile(); // address: 0x45F09B | defaults: (this), ""
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
		std::array<char, 16> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		int32_t bmpSize; // 0x10 (16 decimal)
		int32_t dataSize; // 0x14 (20 decimal)
		int16_t width; // 0x18 (24 decimal)
		int16_t height; // 0x1A (26 decimal)
		int16_t widthLn2; // 0x1C (28 decimal)
		int16_t heightLn2; // 0x1E (30 decimal)
		int16_t widthMinus1; // 0x20 (32 decimal)
		int16_t heightMinus1; // 0x22 (34 decimal)
		int16_t palette; // 0x24 (36 decimal)
		int16_t loadedPalette; // 0x26 (38 decimal)
		int32_t unpackedSize; // 0x28 (40 decimal)
		uint32_t bits; // 0x2C (44 decimal)
		int32_t image; // 0x30 (48 decimal)
		int32_t imageDiv2; // 0x34 (52 decimal)
		int32_t imageDiv4; // 0x38 (56 decimal)
		int32_t imageDiv8; // 0x3C (60 decimal)
		int32_t palette16; // 0x40 (64 decimal)
		int32_t palette24; // 0x44 (68 decimal)
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
		uint32_t file; // 0x0 (0 decimal)
		std::array<char, 256> fileName; // fixed size string, requires null terminator | 0x4 (4 decimal)
		uint32_t loaded; // 4-byte boolean | 0x104 (260 decimal)
		uint32_t IOBuffer; // 0x108 (264 decimal)
		int32_t IOBufferSize; // 0x10C (268 decimal)
		int32_t lodHeaderSignature; // 0x110 (272 decimal)
		SKIP(80);
		std::array<char, 80> description; // fixed size string, requires null terminator | 0x164 (356 decimal)
		SKIP(8);
		int32_t archivesCount; // 0x1BC (444 decimal)
		SKIP(80);
		uint32_t archivesCArray; // 0x210 (528 decimal)
		std::array<char, 16> type; // fixed size string, requires null terminator | 0x214 (532 decimal)
		uint32_t chapterHandle; // 0x224 (548 decimal)
		uint32_t chapterSize; // 0x228 (552 decimal)
		uint32_t files_size; // 0x22C (556 decimal)
		mm8::LodFile* files; // size field offset is 0x22C | 0x230 (560 decimal)
		uint32_t filesOffset; // 0x234 (564 decimal)
		SKIP(4);
		std::array<mm8::LodBitmap, 1000> bitmaps; // size field offset is 0x11B7C | 0x23C (572 decimal)
		union
		{
			uint32_t bitmaps_size; // 0x11B7C (72572 decimal)
			uint32_t D3D_Surfaces_size; // 0x11B7C (72572 decimal)
			uint32_t D3D_Textures_size; // 0x11B7C (72572 decimal)
		};
		SKIP(36);
		uint32_t keepCompressed; // 4-byte boolean | 0x11BA4 (72612 decimal)
		uint32_t isHardware; // 4-byte boolean | 0x11BA8 (72616 decimal)
		SKIP(4);
		uint32_t* D3D_Surfaces; // size field offset is 0x11B7C | 0x11BB0 (72624 decimal)
		uint32_t* D3D_Textures; // size field offset is 0x11B7C | 0x11BB4 (72628 decimal)
		bool __thiscall hasFile(); // address: 0x45F09B | defaults: (this), ""
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
	static_assert(offsetof(mm8::BitmapsLod, bitmaps_size) == 72572);
	static_assert(offsetof(mm8::BitmapsLod, D3D_Surfaces_size) == 72572);
	static_assert(offsetof(mm8::BitmapsLod, D3D_Textures_size) == 72572);
	static_assert(offsetof(mm8::BitmapsLod, keepCompressed) == 72612);
	static_assert(offsetof(mm8::BitmapsLod, isHardware) == 72616);
	static_assert(offsetof(mm8::BitmapsLod, D3D_Surfaces) == 72624);
	static_assert(offsetof(mm8::BitmapsLod, D3D_Textures) == 72628);
}

#pragma pack(pop)