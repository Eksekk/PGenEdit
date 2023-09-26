#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct GameScreen // size: 0x400C4
	{
		SKIP(4);
		int32_t width; // 0x4 (4 decimal)
		int32_t height; // 0x8 (8 decimal)
		int32_t pitch; // 0xC (12 decimal)
		int32_t cx1; // 0x10 (16 decimal)
		int32_t cy1; // 0x14 (20 decimal)
		int32_t cx2; // 0x18 (24 decimal)
		int32_t cy2; // 0x1C (28 decimal)
		SKIP(262148);
		uint32_t buffer; // 0x40024 (262180 decimal)
		uint32_t objectByPixel; // 0x40028 (262184 decimal)
		SKIP(128);
		uint32_t redBits; // 0x400AC (262316 decimal)
		uint32_t blueBits; // 0x400B0 (262320 decimal)
		uint32_t greenBits; // 0x400B4 (262324 decimal)
		uint32_t redMask; // 0x400B8 (262328 decimal)
		uint32_t greenMask; // 0x400BC (262332 decimal)
		uint32_t blueMask; // 0x400C0 (262336 decimal)
		int __thiscall saveToPcx(/*name, x = 0, y = 0, width = 640, height = 480*/); // address: 0x48D130 | defaults: (this), "", 0, 0, 640, 480
	};
	static_assert(sizeof(mm6::GameScreen) == 0x400C4, "Invalid \"mm6::GameScreen\" structure size");
	static_assert(offsetof(mm6::GameScreen, width) == 4);
	static_assert(offsetof(mm6::GameScreen, height) == 8);
	static_assert(offsetof(mm6::GameScreen, pitch) == 12);
	static_assert(offsetof(mm6::GameScreen, cx1) == 16);
	static_assert(offsetof(mm6::GameScreen, cy1) == 20);
	static_assert(offsetof(mm6::GameScreen, cx2) == 24);
	static_assert(offsetof(mm6::GameScreen, cy2) == 28);
	static_assert(offsetof(mm6::GameScreen, buffer) == 262180);
	static_assert(offsetof(mm6::GameScreen, objectByPixel) == 262184);
	static_assert(offsetof(mm6::GameScreen, redBits) == 262316);
	static_assert(offsetof(mm6::GameScreen, blueBits) == 262320);
	static_assert(offsetof(mm6::GameScreen, greenBits) == 262324);
	static_assert(offsetof(mm6::GameScreen, redMask) == 262328);
	static_assert(offsetof(mm6::GameScreen, greenMask) == 262332);
	static_assert(offsetof(mm6::GameScreen, blueMask) == 262336);



	struct Dlg // size: 0x54
	{
		int32_t left; // 0x0 (0 decimal)
		int32_t top; // 0x4 (4 decimal)
		int32_t width; // 0x8 (8 decimal)
		int32_t height; // 0xC (12 decimal)
		union
		{
			int32_t rightPixel; // 0x10 (16 decimal) | MMExt info: !Lua[[= Left + Width - 1]]  (it was called 'Right_' before MMExtension v2.3, old name is supported for backward compatibility)
			int32_t right_; // 0x10 (16 decimal)
		};
		union
		{
			int32_t bottomPixel; // 0x14 (20 decimal) | MMExt info: !Lua[[= Top + Height - 1]]  (it was called 'Bottom_' before MMExtension v2.3, old name is supported for backward compatibility)
			int32_t bottom_; // 0x14 (20 decimal)
		};
		int32_t dlgID; // 0x18 (24 decimal)
		int16_t param; // 0x1C (28 decimal) | MMExt info: 2D Events Id / Chest Id / ...
		SKIP(2);
		int32_t itemsCount; // 0x20 (32 decimal)
		SKIP(4);
		int32_t keyboardItemsCount; // 0x28 (40 decimal)
		int32_t keyboardItem; // 0x2C (44 decimal)
		int32_t keyboardNavigationTrackMouse; // 0x30 (48 decimal)
		int32_t keyboardLeftRightStep; // 0x34 (52 decimal)
		int32_t keyboardItemsStart; // 0x38 (56 decimal)
		int32_t index; // 0x3C (60 decimal) | MMExt info: Current index in #Game.Dialogs:# array.
		int32_t textInputState; // 0x40 (64 decimal)
		int32_t useKeyboadNavigation; // 0x44 (68 decimal)
		union
		{
			char* strParam; // EditPChar | 0x48 (72 decimal)
			uint32_t strParamPtr; // 0x48 (72 decimal)
		};
		uint32_t firstItemPtr; // 0x4C (76 decimal)
		uint32_t lastItemPtr; // 0x50 (80 decimal)
		int __thiscall setKeyboardNavigation(/*KeyboardItemsCount, KeyboardNavigationTrackMouse, KeyboardLeftRightStep, KeyboardItemsStart*/); // address: 0x41A0E0 | defaults: (this), 0, 1, 0, 0
		int __thiscall getItemPtrByIndex(/*Index*/); // address: 0x419D50 | defaults: (this), 0
	};
	static_assert(sizeof(mm6::Dlg) == 0x54, "Invalid \"mm6::Dlg\" structure size");
	static_assert(offsetof(mm6::Dlg, top) == 4);
	static_assert(offsetof(mm6::Dlg, width) == 8);
	static_assert(offsetof(mm6::Dlg, height) == 12);
	static_assert(offsetof(mm6::Dlg, rightPixel) == 16);
	static_assert(offsetof(mm6::Dlg, right_) == 16);
	static_assert(offsetof(mm6::Dlg, bottomPixel) == 20);
	static_assert(offsetof(mm6::Dlg, bottom_) == 20);
	static_assert(offsetof(mm6::Dlg, dlgID) == 24);
	static_assert(offsetof(mm6::Dlg, param) == 28);
	static_assert(offsetof(mm6::Dlg, itemsCount) == 32);
	static_assert(offsetof(mm6::Dlg, keyboardItemsCount) == 40);
	static_assert(offsetof(mm6::Dlg, keyboardItem) == 44);
	static_assert(offsetof(mm6::Dlg, keyboardNavigationTrackMouse) == 48);
	static_assert(offsetof(mm6::Dlg, keyboardLeftRightStep) == 52);
	static_assert(offsetof(mm6::Dlg, keyboardItemsStart) == 56);
	static_assert(offsetof(mm6::Dlg, index) == 60);
	static_assert(offsetof(mm6::Dlg, textInputState) == 64);
	static_assert(offsetof(mm6::Dlg, useKeyboadNavigation) == 68);
	static_assert(offsetof(mm6::Dlg, strParam) == 72);
	static_assert(offsetof(mm6::Dlg, strParamPtr) == 72);
	static_assert(offsetof(mm6::Dlg, firstItemPtr) == 76);
	static_assert(offsetof(mm6::Dlg, lastItemPtr) == 80);



	struct DialogLogic // size: 0x3121334
	{
		static int32_t* list; // original offset 0x3121330 (51516208 decimal)element size: 0x4 (4 decimal)
		static uint32_t* list_sizePtr; // Offset/size: 0x4CB1E0 (5026272 decimal)

		SKIP(5025464);
		int32_t scrollPage; // 0x4CAEB8 (5025464 decimal)
		SKIP(4);
		union
		{
			uint32_t autonoteTab2Clicked; // 4-byte boolean | 0x4CAEC0 (5025472 decimal)
			int32_t mapMoveDownClicked; // 0x4CAEC0 (5025472 decimal)
		};
		SKIP(4);
		int32_t scrollPos; // 0x4CAEC8 (5025480 decimal)
		SKIP(592);
		uint32_t autonoteTab5Clicked; // 4-byte boolean | 0x4CB11C (5026076 decimal)
		SKIP(8);
		uint32_t scrollUpClicked; // 4-byte boolean | 0x4CB128 (5026088 decimal)
		SKIP(124);
		union
		{
			uint32_t autonoteTab3Clicked; // 4-byte boolean | 0x4CB1A8 (5026216 decimal)
			int32_t mapMoveLeftClicked; // 0x4CB1A8 (5026216 decimal)
		};
		SKIP(4);
		union
		{
			uint32_t autonoteTab1Clicked; // 4-byte boolean | 0x4CB1B0 (5026224 decimal)
			int32_t mapMoveUpClicked; // 0x4CB1B0 (5026224 decimal)
		};
		SKIP(36);
		int32_t countOnScreen; // 0x4CB1D8 (5026264 decimal)
		SKIP(4);
		int32_t listCount; // 0x4CB1E0 (5026272 decimal)
		SKIP(12);
		uint32_t scrollDownClicked; // 4-byte boolean | 0x4CB1F0 (5026288 decimal)
		union
		{
			uint32_t autonoteTab4Clicked; // 4-byte boolean | 0x4CB1F4 (5026292 decimal)
			int32_t mapMoveRightClicked; // 0x4CB1F4 (5026292 decimal)
		};
		SKIP(4);
		int32_t autonotesCategory; // 0x4CB1FC (5026300 decimal)
		SKIP(20);
		int32_t spellBookSelection; // 0x4CB214 (5026324 decimal)
		SKIP(416);
		mm6::MapMonster monsterInfoMonster; // 0x4CB3B8 (5026744 decimal)
		SKIP(39700);
		uint32_t playerRingsOpen; // 4-byte boolean | 0x4D50F0 (5066992 decimal)
		// uint8_t* paperDollPositionX; // real size is 0 | Unknown type | 0x4D50F4 (5066996 decimal)
		// uint8_t* paperDollPositionY; // real size is 0 | Unknown type | 0x4D50F4 (5066996 decimal)
		SKIP(46449216);
	};
	static_assert(sizeof(mm6::DialogLogic) == 0x3121334, "Invalid \"mm6::DialogLogic\" structure size");
	static_assert(offsetof(mm6::DialogLogic, scrollPage) == 5025464);
	static_assert(offsetof(mm6::DialogLogic, autonoteTab2Clicked) == 5025472);
	static_assert(offsetof(mm6::DialogLogic, mapMoveDownClicked) == 5025472);
	static_assert(offsetof(mm6::DialogLogic, scrollPos) == 5025480);
	static_assert(offsetof(mm6::DialogLogic, autonoteTab5Clicked) == 5026076);
	static_assert(offsetof(mm6::DialogLogic, scrollUpClicked) == 5026088);
	static_assert(offsetof(mm6::DialogLogic, autonoteTab3Clicked) == 5026216);
	static_assert(offsetof(mm6::DialogLogic, mapMoveLeftClicked) == 5026216);
	static_assert(offsetof(mm6::DialogLogic, autonoteTab1Clicked) == 5026224);
	static_assert(offsetof(mm6::DialogLogic, mapMoveUpClicked) == 5026224);
	static_assert(offsetof(mm6::DialogLogic, countOnScreen) == 5026264);
	static_assert(offsetof(mm6::DialogLogic, listCount) == 5026272);
	static_assert(offsetof(mm6::DialogLogic, scrollDownClicked) == 5026288);
	static_assert(offsetof(mm6::DialogLogic, autonoteTab4Clicked) == 5026292);
	static_assert(offsetof(mm6::DialogLogic, mapMoveRightClicked) == 5026292);
	static_assert(offsetof(mm6::DialogLogic, autonotesCategory) == 5026300);
	static_assert(offsetof(mm6::DialogLogic, spellBookSelection) == 5026324);
	static_assert(offsetof(mm6::DialogLogic, monsterInfoMonster) == 5026744);
	static_assert(offsetof(mm6::DialogLogic, playerRingsOpen) == 5066992);



	struct GameClasses // size: 0x60020196
	{
		static uint8_t* HPFactor; // original offset 0x4C2640 (4990528 decimal)element size: 0x1 (1 decimal)
		static uint32_t HPFactor_size; // Offset/size: 0x12 (18 decimal)
		static uint8_t* SPFactor; // original offset 0x4C2654 (4990548 decimal)element size: 0x1 (1 decimal)
		static uint32_t SPFactor_size; // Offset/size: 0x12 (18 decimal)
		static uint8_t* SPStats; // original offset 0x60020184 (1610744196 decimal)element size: 0x1 (1 decimal)
		static uint32_t SPStats_size; // Offset/size: 0x12 (18 decimal)

		SKIP(1610744214);
	};
	static_assert(sizeof(mm6::GameClasses) == 0x60020196, "Invalid \"mm6::GameClasses\" structure size");



	struct GameClassKinds // size: 0x4C274E
	{
		static std::array<uint8_t, 31>* startingSkills; // original offset 0x4C2694 (4990612 decimal)element size: 0x1F (31 decimal)
		static uint32_t startingSkills_size; // Offset/size: 0x6 (6 decimal)

		SKIP(4990512);
		std::array<uint8_t, 6> HPBase; // 0x4C2630 (4990512 decimal)
		SKIP(2);
		std::array<uint8_t, 6> SPBase; // 0x4C2638 (4990520 decimal)
		SKIP(42);
		std::array<std::array<uint8_t, 7>, 6> startingStats; // 0x4C2668 (4990568 decimal)
		SKIP(188);
	};
	static_assert(sizeof(mm6::GameClassKinds) == 0x4C274E, "Invalid \"mm6::GameClassKinds\" structure size");
	static_assert(offsetof(mm6::GameClassKinds, HPBase) == 4990512);
	static_assert(offsetof(mm6::GameClassKinds, SPBase) == 4990520);
	static_assert(offsetof(mm6::GameClassKinds, startingStats) == 4990568);
}
namespace mm7
{
	struct GameScreen // size: 0x40104
	{
		uint32_t isD3D; // 4-byte boolean | 0x0 (0 decimal)
		SKIP(12);
		int32_t width; // 0x10 (16 decimal)
		int32_t height; // 0x14 (20 decimal)
		int32_t pitch; // 0x18 (24 decimal)
		int32_t cx1; // 0x1C (28 decimal)
		int32_t cy1; // 0x20 (32 decimal)
		int32_t cx2; // 0x24 (36 decimal)
		int32_t cy2; // 0x28 (40 decimal)
		SKIP(262152);
		uint32_t objectByPixel; // 0x40034 (262196 decimal)
		SKIP(148);
		uint32_t redBits; // 0x400CC (262348 decimal)
		uint32_t blueBits; // 0x400D0 (262352 decimal)
		uint32_t greenBits; // 0x400D4 (262356 decimal)
		uint32_t redMask; // 0x400D8 (262360 decimal)
		uint32_t greenMask; // 0x400DC (262364 decimal)
		uint32_t blueMask; // 0x400E0 (262368 decimal)
		SKIP(8);
		uint32_t buffer; // 0x400EC (262380 decimal)
		int32_t pitch2; // 0x400F0 (262384 decimal)
		int32_t clipTop; // 0x400F4 (262388 decimal)
		int32_t clipLeft; // 0x400F8 (262392 decimal)
		int32_t clipBottom; // 0x400FC (262396 decimal)
		int32_t clipRight; // 0x40100 (262400 decimal)
		int __thiscall saveToPcx(/*name, x = 0, y = 0, width = 640, height = 480*/); // address: 0x49F14C | defaults: (this), ""
		int __thiscall setClipRect(/*left = 0, top = 0, right = 640, bottom = 480*/); // address: 0x4A5B11 | defaults: (this), 0, 0, 640, 480
		int __thiscall saveBufferToPcx(/*name, buf, width = 640, height = 480*/); // address: 0x49F845 | defaults: (this), "", 0, 640, 480
	};
	static_assert(sizeof(mm7::GameScreen) == 0x40104, "Invalid \"mm7::GameScreen\" structure size");
	static_assert(offsetof(mm7::GameScreen, width) == 16);
	static_assert(offsetof(mm7::GameScreen, height) == 20);
	static_assert(offsetof(mm7::GameScreen, pitch) == 24);
	static_assert(offsetof(mm7::GameScreen, cx1) == 28);
	static_assert(offsetof(mm7::GameScreen, cy1) == 32);
	static_assert(offsetof(mm7::GameScreen, cx2) == 36);
	static_assert(offsetof(mm7::GameScreen, cy2) == 40);
	static_assert(offsetof(mm7::GameScreen, objectByPixel) == 262196);
	static_assert(offsetof(mm7::GameScreen, redBits) == 262348);
	static_assert(offsetof(mm7::GameScreen, blueBits) == 262352);
	static_assert(offsetof(mm7::GameScreen, greenBits) == 262356);
	static_assert(offsetof(mm7::GameScreen, redMask) == 262360);
	static_assert(offsetof(mm7::GameScreen, greenMask) == 262364);
	static_assert(offsetof(mm7::GameScreen, blueMask) == 262368);
	static_assert(offsetof(mm7::GameScreen, buffer) == 262380);
	static_assert(offsetof(mm7::GameScreen, pitch2) == 262384);
	static_assert(offsetof(mm7::GameScreen, clipTop) == 262388);
	static_assert(offsetof(mm7::GameScreen, clipLeft) == 262392);
	static_assert(offsetof(mm7::GameScreen, clipBottom) == 262396);
	static_assert(offsetof(mm7::GameScreen, clipRight) == 262400);



	struct GameRaces // size: 0x4ED6C8
	{
		SKIP(5166680);
		std::array<std::array<mm7::StartStat, 7>, 4> startingStats; // 0x4ED658 (5166680 decimal)
	};
	static_assert(sizeof(mm7::GameRaces) == 0x4ED6C8, "Invalid \"mm7::GameRaces\" structure size");
	static_assert(offsetof(mm7::GameRaces, startingStats) == 5166680);



	struct Dlg // size: 0x54
	{
		int32_t left; // 0x0 (0 decimal)
		int32_t top; // 0x4 (4 decimal)
		int32_t width; // 0x8 (8 decimal)
		int32_t height; // 0xC (12 decimal)
		union
		{
			int32_t rightPixel; // 0x10 (16 decimal) | MMExt info: !Lua[[= Left + Width - 1]]  (it was called 'Right_' before MMExtension v2.3, old name is supported for backward compatibility)
			int32_t right_; // 0x10 (16 decimal)
		};
		union
		{
			int32_t bottomPixel; // 0x14 (20 decimal) | MMExt info: !Lua[[= Top + Height - 1]]  (it was called 'Bottom_' before MMExtension v2.3, old name is supported for backward compatibility)
			int32_t bottom_; // 0x14 (20 decimal)
		};
		int32_t dlgID; // 0x18 (24 decimal)
		int32_t param; // 0x1C (28 decimal) | MMExt info: 2D Events Id / Chest Id / ...
		int32_t itemsCount; // 0x20 (32 decimal)
		SKIP(4);
		int32_t keyboardItemsCount; // 0x28 (40 decimal)
		int32_t keyboardItem; // 0x2C (44 decimal)
		int32_t keyboardNavigationTrackMouse; // 0x30 (48 decimal)
		int32_t keyboardLeftRightStep; // 0x34 (52 decimal)
		int32_t keyboardItemsStart; // 0x38 (56 decimal)
		int32_t index; // 0x3C (60 decimal) | MMExt info: Current index in #Game.Dialogs:# array.
		int32_t textInputState; // 0x40 (64 decimal)
		int32_t useKeyboadNavigation; // 0x44 (68 decimal)
		union
		{
			char* strParam; // EditPChar | 0x48 (72 decimal)
			uint32_t strParamPtr; // 0x48 (72 decimal)
		};
		uint32_t firstItemPtr; // 0x4C (76 decimal)
		uint32_t lastItemPtr; // 0x50 (80 decimal)
		int __thiscall getItemPtrByIndex(/*Index*/); // address: 0x41CCE4 | defaults: (this), 0
		int __thiscall setKeyboardNavigation(/*KeyboardItemsCount, KeyboardNavigationTrackMouse, KeyboardLeftRightStep, KeyboardItemsStart*/); // address: 0x41D038 | defaults: (this), 0, 1, 0, 0
	};
	static_assert(sizeof(mm7::Dlg) == 0x54, "Invalid \"mm7::Dlg\" structure size");
	static_assert(offsetof(mm7::Dlg, top) == 4);
	static_assert(offsetof(mm7::Dlg, width) == 8);
	static_assert(offsetof(mm7::Dlg, height) == 12);
	static_assert(offsetof(mm7::Dlg, rightPixel) == 16);
	static_assert(offsetof(mm7::Dlg, right_) == 16);
	static_assert(offsetof(mm7::Dlg, bottomPixel) == 20);
	static_assert(offsetof(mm7::Dlg, bottom_) == 20);
	static_assert(offsetof(mm7::Dlg, dlgID) == 24);
	static_assert(offsetof(mm7::Dlg, param) == 28);
	static_assert(offsetof(mm7::Dlg, itemsCount) == 32);
	static_assert(offsetof(mm7::Dlg, keyboardItemsCount) == 40);
	static_assert(offsetof(mm7::Dlg, keyboardItem) == 44);
	static_assert(offsetof(mm7::Dlg, keyboardNavigationTrackMouse) == 48);
	static_assert(offsetof(mm7::Dlg, keyboardLeftRightStep) == 52);
	static_assert(offsetof(mm7::Dlg, keyboardItemsStart) == 56);
	static_assert(offsetof(mm7::Dlg, index) == 60);
	static_assert(offsetof(mm7::Dlg, textInputState) == 64);
	static_assert(offsetof(mm7::Dlg, useKeyboadNavigation) == 68);
	static_assert(offsetof(mm7::Dlg, strParam) == 72);
	static_assert(offsetof(mm7::Dlg, strParamPtr) == 72);
	static_assert(offsetof(mm7::Dlg, firstItemPtr) == 76);
	static_assert(offsetof(mm7::Dlg, lastItemPtr) == 80);



	struct DialogLogic // size: 0x5C4430
	{
		static int32_t* list; // original offset 0x5C3490 (6042768 decimal)element size: 0x4 (4 decimal)
		static uint32_t* list_sizePtr; // Offset/size: 0x5063A4 (5268388 decimal)

		SKIP(5122552);
		std::array<int32_t, 5> armorSkills; // requires unprotect before change | 0x4E29F8 (5122552 decimal)
		std::array<int32_t, 9> weaponSkills; // requires unprotect before change | 0x4E2A0C (5122572 decimal)
		std::array<int32_t, 12> miscSkills; // requires unprotect before change | 0x4E2A30 (5122608 decimal)
		std::array<int32_t, 9> magicSkills; // requires unprotect before change | 0x4E2A60 (5122656 decimal)
		SKIP(8564);
		int32_t paperDollPositionX; // 0x4E4BF8 (5131256 decimal)
		int32_t paperDollPositionY; // 0x4E4BFC (5131260 decimal)
		SKIP(137116);
		int32_t scrollPage; // 0x50639C (5268380 decimal)
		int32_t countOnScreen; // 0x5063A0 (5268384 decimal)
		int32_t listCount; // 0x5063A4 (5268388 decimal)
		int32_t scrollPos; // 0x5063A8 (5268392 decimal)
		uint32_t autonoteTab6Clicked; // 4-byte boolean | 0x5063AC (5268396 decimal)
		uint32_t autonoteTab5Clicked; // 4-byte boolean | 0x5063B0 (5268400 decimal)
		union
		{
			uint32_t autonoteTab4Clicked; // 4-byte boolean | 0x5063B4 (5268404 decimal)
			uint32_t mapMoveRightClicked; // 4-byte boolean | 0x5063B4 (5268404 decimal)
		};
		union
		{
			uint32_t autonoteTab3Clicked; // 4-byte boolean | 0x5063B8 (5268408 decimal)
			uint32_t mapMoveLeftClicked; // 4-byte boolean | 0x5063B8 (5268408 decimal)
		};
		union
		{
			uint32_t autonoteTab2Clicked; // 4-byte boolean | 0x5063BC (5268412 decimal)
			uint32_t mapMoveDownClicked; // 4-byte boolean | 0x5063BC (5268412 decimal)
		};
		union
		{
			uint32_t autonoteTab1Clicked; // 4-byte boolean | 0x5063C0 (5268416 decimal)
			uint32_t mapMoveUpClicked; // 4-byte boolean | 0x5063C0 (5268416 decimal)
		};
		uint32_t scrollDownClicked; // 4-byte boolean | 0x5063C4 (5268420 decimal)
		uint32_t scrollUpClicked; // 4-byte boolean | 0x5063C8 (5268424 decimal)
		int32_t spellBookSelection; // 0x5063CC (5268428 decimal) | MMExt info: Selected spell index within current page (1..11)
		bool spellBookSelectedNewSpell; // 0x5063D0 (5268432 decimal)
		SKIP(23);
		int32_t autonotesCategory; // 0x5063E8 (5268456 decimal)
		SKIP(20);
		mm7::MapMonster monsterInfoMonster; // 0x506400 (5268480 decimal)
		SKIP(45084);
		uint32_t playerRingsOpen; // 4-byte boolean | 0x511760 (5314400 decimal)
		SKIP(732364);
	};
	static_assert(sizeof(mm7::DialogLogic) == 0x5C4430, "Invalid \"mm7::DialogLogic\" structure size");
	static_assert(offsetof(mm7::DialogLogic, armorSkills) == 5122552);
	static_assert(offsetof(mm7::DialogLogic, weaponSkills) == 5122572);
	static_assert(offsetof(mm7::DialogLogic, miscSkills) == 5122608);
	static_assert(offsetof(mm7::DialogLogic, magicSkills) == 5122656);
	static_assert(offsetof(mm7::DialogLogic, paperDollPositionX) == 5131256);
	static_assert(offsetof(mm7::DialogLogic, paperDollPositionY) == 5131260);
	static_assert(offsetof(mm7::DialogLogic, scrollPage) == 5268380);
	static_assert(offsetof(mm7::DialogLogic, countOnScreen) == 5268384);
	static_assert(offsetof(mm7::DialogLogic, listCount) == 5268388);
	static_assert(offsetof(mm7::DialogLogic, scrollPos) == 5268392);
	static_assert(offsetof(mm7::DialogLogic, autonoteTab6Clicked) == 5268396);
	static_assert(offsetof(mm7::DialogLogic, autonoteTab5Clicked) == 5268400);
	static_assert(offsetof(mm7::DialogLogic, autonoteTab4Clicked) == 5268404);
	static_assert(offsetof(mm7::DialogLogic, mapMoveRightClicked) == 5268404);
	static_assert(offsetof(mm7::DialogLogic, autonoteTab3Clicked) == 5268408);
	static_assert(offsetof(mm7::DialogLogic, mapMoveLeftClicked) == 5268408);
	static_assert(offsetof(mm7::DialogLogic, autonoteTab2Clicked) == 5268412);
	static_assert(offsetof(mm7::DialogLogic, mapMoveDownClicked) == 5268412);
	static_assert(offsetof(mm7::DialogLogic, autonoteTab1Clicked) == 5268416);
	static_assert(offsetof(mm7::DialogLogic, mapMoveUpClicked) == 5268416);
	static_assert(offsetof(mm7::DialogLogic, scrollDownClicked) == 5268420);
	static_assert(offsetof(mm7::DialogLogic, scrollUpClicked) == 5268424);
	static_assert(offsetof(mm7::DialogLogic, spellBookSelection) == 5268428);
	static_assert(offsetof(mm7::DialogLogic, spellBookSelectedNewSpell) == 5268432);
	static_assert(offsetof(mm7::DialogLogic, autonotesCategory) == 5268456);
	static_assert(offsetof(mm7::DialogLogic, monsterInfoMonster) == 5268480);
	static_assert(offsetof(mm7::DialogLogic, playerRingsOpen) == 5314400);



	struct GameClasses // size: 0x600201BC
	{
		static uint8_t* HPFactor; // original offset 0x4ED610 (5166608 decimal)element size: 0x1 (1 decimal)
		static uint32_t HPFactor_size; // Offset/size: 0x24 (36 decimal)
		static uint8_t* SPFactor; // original offset 0x4ED634 (5166644 decimal)element size: 0x1 (1 decimal)
		static uint32_t SPFactor_size; // Offset/size: 0x24 (36 decimal)
		static uint8_t* SPStats; // original offset 0x60020198 (1610744216 decimal)element size: 0x1 (1 decimal)
		static uint32_t SPStats_size; // Offset/size: 0x24 (36 decimal)
		static std::array<uint8_t, 37>* skills; // original offset 0x4ED818 (5167128 decimal)element size: 0x25 (37 decimal)
		static uint32_t skills_size; // Offset/size: 0x24 (36 decimal)

		SKIP(1610744252);
	};
	static_assert(sizeof(mm7::GameClasses) == 0x600201BC, "Invalid \"mm7::GameClasses\" structure size");



	struct GameClassKinds // size: 0x4ED815
	{
		static std::array<uint8_t, 37>* startingSkills; // original offset 0x4ED6C8 (5166792 decimal)element size: 0x25 (37 decimal)
		static uint32_t startingSkills_size; // Offset/size: 0x9 (9 decimal)

		SKIP(5166584);
		std::array<uint8_t, 9> HPBase; // 0x4ED5F8 (5166584 decimal)
		SKIP(3);
		std::array<uint8_t, 9> SPBase; // 0x4ED604 (5166596 decimal)
		SKIP(520);
	};
	static_assert(sizeof(mm7::GameClassKinds) == 0x4ED815, "Invalid \"mm7::GameClassKinds\" structure size");
	static_assert(offsetof(mm7::GameClassKinds, HPBase) == 5166584);
	static_assert(offsetof(mm7::GameClassKinds, SPBase) == 5166596);
}
namespace mm8
{
	struct GameScreen // size: 0x400F0
	{
		uint32_t isD3D; // 4-byte boolean | 0x0 (0 decimal)
		SKIP(12);
		int32_t width; // 0x10 (16 decimal)
		int32_t height; // 0x14 (20 decimal)
		int32_t pitch; // 0x18 (24 decimal)
		int32_t cx1; // 0x1C (28 decimal)
		int32_t cy1; // 0x20 (32 decimal)
		int32_t cx2; // 0x24 (36 decimal)
		int32_t cy2; // 0x28 (40 decimal)
		SKIP(262152);
		uint32_t objectByPixel; // 0x40034 (262196 decimal)
		SKIP(148);
		uint32_t redBits; // 0x400CC (262348 decimal)
		uint32_t blueBits; // 0x400D0 (262352 decimal)
		uint32_t greenBits; // 0x400D4 (262356 decimal)
		uint32_t redMask; // 0x400D8 (262360 decimal)
		uint32_t greenMask; // 0x400DC (262364 decimal)
		uint32_t blueMask; // 0x400E0 (262368 decimal)
		SKIP(8);
		uint32_t buffer; // 0x400EC (262380 decimal)
		int __thiscall saveBufferToPcx(/*name, buf, width = 640, height = 480*/); // address: 0x49CEB9 | defaults: (this), "", 0, 640, 480
		int __thiscall saveToPcx(/*name, x = 0, y = 0, width = 640, height = 480*/); // address: 0x49C7C0 | defaults: (this), ""
	};
	static_assert(sizeof(mm8::GameScreen) == 0x400F0, "Invalid \"mm8::GameScreen\" structure size");
	static_assert(offsetof(mm8::GameScreen, width) == 16);
	static_assert(offsetof(mm8::GameScreen, height) == 20);
	static_assert(offsetof(mm8::GameScreen, pitch) == 24);
	static_assert(offsetof(mm8::GameScreen, cx1) == 28);
	static_assert(offsetof(mm8::GameScreen, cy1) == 32);
	static_assert(offsetof(mm8::GameScreen, cx2) == 36);
	static_assert(offsetof(mm8::GameScreen, cy2) == 40);
	static_assert(offsetof(mm8::GameScreen, objectByPixel) == 262196);
	static_assert(offsetof(mm8::GameScreen, redBits) == 262348);
	static_assert(offsetof(mm8::GameScreen, blueBits) == 262352);
	static_assert(offsetof(mm8::GameScreen, greenBits) == 262356);
	static_assert(offsetof(mm8::GameScreen, redMask) == 262360);
	static_assert(offsetof(mm8::GameScreen, greenMask) == 262364);
	static_assert(offsetof(mm8::GameScreen, blueMask) == 262368);
	static_assert(offsetof(mm8::GameScreen, buffer) == 262380);



	struct DialogLogic // size: 0x5DC8E0
	{
		static int32_t* list; // original offset 0x5DB940 (6142272 decimal)element size: 0x4 (4 decimal)
		static uint32_t* list_sizePtr; // Offset/size: 0x517AF4 (5339892 decimal)

		SKIP(5191936);
		std::array<int32_t, 5> armorSkills; // requires unprotect before change | 0x4F3900 (5191936 decimal)
		std::array<int32_t, 9> weaponSkills; // requires unprotect before change | 0x4F3914 (5191956 decimal)
		std::array<int32_t, 12> miscSkills; // requires unprotect before change | 0x4F3938 (5191992 decimal)
		std::array<int32_t, 12> magicSkills; // requires unprotect before change | 0x4F3968 (5192040 decimal)
		SKIP(147796);
		int32_t scrollPage; // 0x517AEC (5339884 decimal)
		int32_t countOnScreen; // 0x517AF0 (5339888 decimal)
		int32_t listCount; // 0x517AF4 (5339892 decimal)
		int32_t scrollPos; // 0x517AF8 (5339896 decimal)
		uint32_t autonoteTab6Clicked; // 4-byte boolean | 0x517AFC (5339900 decimal)
		uint32_t autonoteTab5Clicked; // 4-byte boolean | 0x517B00 (5339904 decimal)
		union
		{
			uint32_t autonoteTab4Clicked; // 4-byte boolean | 0x517B04 (5339908 decimal)
			uint32_t mapMoveRightClicked; // 4-byte boolean | 0x517B04 (5339908 decimal)
		};
		union
		{
			uint32_t autonoteTab3Clicked; // 4-byte boolean | 0x517B08 (5339912 decimal)
			uint32_t mapMoveLeftClicked; // 4-byte boolean | 0x517B08 (5339912 decimal)
		};
		union
		{
			uint32_t autonoteTab2Clicked; // 4-byte boolean | 0x517B0C (5339916 decimal)
			uint32_t mapMoveDownClicked; // 4-byte boolean | 0x517B0C (5339916 decimal)
		};
		union
		{
			uint32_t autonoteTab1Clicked; // 4-byte boolean | 0x517B10 (5339920 decimal)
			uint32_t mapMoveUpClicked; // 4-byte boolean | 0x517B10 (5339920 decimal)
		};
		uint32_t scrollDownClicked; // 4-byte boolean | 0x517B14 (5339924 decimal)
		uint32_t scrollUpClicked; // 4-byte boolean | 0x517B18 (5339928 decimal)
		int32_t spellBookSelection; // 0x517B1C (5339932 decimal) | MMExt info: Selected spell index within current page (1..11)
		bool spellBookSelectedNewSpell; // 0x517B20 (5339936 decimal)
		SKIP(23);
		int32_t autonotesCategory; // 0x517B38 (5339960 decimal)
		SKIP(20);
		mm8::MapMonster monsterInfoMonster; // 0x517B50 (5339984 decimal)
		SKIP(805316);
	};
	static_assert(sizeof(mm8::DialogLogic) == 0x5DC8E0, "Invalid \"mm8::DialogLogic\" structure size");
	static_assert(offsetof(mm8::DialogLogic, armorSkills) == 5191936);
	static_assert(offsetof(mm8::DialogLogic, weaponSkills) == 5191956);
	static_assert(offsetof(mm8::DialogLogic, miscSkills) == 5191992);
	static_assert(offsetof(mm8::DialogLogic, magicSkills) == 5192040);
	static_assert(offsetof(mm8::DialogLogic, scrollPage) == 5339884);
	static_assert(offsetof(mm8::DialogLogic, countOnScreen) == 5339888);
	static_assert(offsetof(mm8::DialogLogic, listCount) == 5339892);
	static_assert(offsetof(mm8::DialogLogic, scrollPos) == 5339896);
	static_assert(offsetof(mm8::DialogLogic, autonoteTab6Clicked) == 5339900);
	static_assert(offsetof(mm8::DialogLogic, autonoteTab5Clicked) == 5339904);
	static_assert(offsetof(mm8::DialogLogic, autonoteTab4Clicked) == 5339908);
	static_assert(offsetof(mm8::DialogLogic, mapMoveRightClicked) == 5339908);
	static_assert(offsetof(mm8::DialogLogic, autonoteTab3Clicked) == 5339912);
	static_assert(offsetof(mm8::DialogLogic, mapMoveLeftClicked) == 5339912);
	static_assert(offsetof(mm8::DialogLogic, autonoteTab2Clicked) == 5339916);
	static_assert(offsetof(mm8::DialogLogic, mapMoveDownClicked) == 5339916);
	static_assert(offsetof(mm8::DialogLogic, autonoteTab1Clicked) == 5339920);
	static_assert(offsetof(mm8::DialogLogic, mapMoveUpClicked) == 5339920);
	static_assert(offsetof(mm8::DialogLogic, scrollDownClicked) == 5339924);
	static_assert(offsetof(mm8::DialogLogic, scrollUpClicked) == 5339928);
	static_assert(offsetof(mm8::DialogLogic, spellBookSelection) == 5339932);
	static_assert(offsetof(mm8::DialogLogic, spellBookSelectedNewSpell) == 5339936);
	static_assert(offsetof(mm8::DialogLogic, autonotesCategory) == 5339960);
	static_assert(offsetof(mm8::DialogLogic, monsterInfoMonster) == 5339984);



	struct Dlg // size: 0x54
	{
		int32_t left; // 0x0 (0 decimal)
		int32_t top; // 0x4 (4 decimal)
		int32_t width; // 0x8 (8 decimal)
		int32_t height; // 0xC (12 decimal)
		int32_t right_; // 0x10 (16 decimal)
		int32_t bottom_; // 0x14 (20 decimal)
		int32_t dlgID; // 0x18 (24 decimal)
		int32_t param; // 0x1C (28 decimal) | MMExt info: 2D Events Id / Chest Id / ...
		int32_t itemsCount; // 0x20 (32 decimal)
		SKIP(4);
		int32_t keyboardItemsCount; // 0x28 (40 decimal)
		int32_t keyboardItem; // 0x2C (44 decimal)
		int32_t keyboardNavigationTrackMouse; // 0x30 (48 decimal)
		int32_t keyboardLeftRightStep; // 0x34 (52 decimal)
		int32_t keyboardItemsStart; // 0x38 (56 decimal)
		int32_t index; // 0x3C (60 decimal)
		SKIP(4);
		int32_t useKeyboadNavigation; // 0x44 (68 decimal)
		SKIP(4);
		uint32_t firstItemPtr; // 0x4C (76 decimal)
		uint32_t lastItemPtr; // 0x50 (80 decimal)
		int __thiscall getItemPtrByIndex(/*Index*/); // address: 0x41C205 | defaults: (this), 0
		int __stdcall addButton(/*X, Y, Width, Height, Shape = 1, HintAction, ActionType, ActionInfo, Key, Hint, Sprites..., 0*/); // address: 0x41C513 | defaults: (this), 0, 0, 0, 0, 1, 0, 0, 0, 0, "", 0, 0, 0, 0, 0, 0
		int __thiscall setKeyboardNavigation(/*KeyboardItemsCount, KeyboardNavigationTrackMouse, KeyboardLeftRightStep, KeyboardItemsStart*/); // address: 0x41C473 | defaults: (this), 0, 1, 0, 0
	};
	static_assert(sizeof(mm8::Dlg) == 0x54, "Invalid \"mm8::Dlg\" structure size");
	static_assert(offsetof(mm8::Dlg, top) == 4);
	static_assert(offsetof(mm8::Dlg, width) == 8);
	static_assert(offsetof(mm8::Dlg, height) == 12);
	static_assert(offsetof(mm8::Dlg, right_) == 16);
	static_assert(offsetof(mm8::Dlg, bottom_) == 20);
	static_assert(offsetof(mm8::Dlg, dlgID) == 24);
	static_assert(offsetof(mm8::Dlg, param) == 28);
	static_assert(offsetof(mm8::Dlg, itemsCount) == 32);
	static_assert(offsetof(mm8::Dlg, keyboardItemsCount) == 40);
	static_assert(offsetof(mm8::Dlg, keyboardItem) == 44);
	static_assert(offsetof(mm8::Dlg, keyboardNavigationTrackMouse) == 48);
	static_assert(offsetof(mm8::Dlg, keyboardLeftRightStep) == 52);
	static_assert(offsetof(mm8::Dlg, keyboardItemsStart) == 56);
	static_assert(offsetof(mm8::Dlg, index) == 60);
	static_assert(offsetof(mm8::Dlg, useKeyboadNavigation) == 68);
	static_assert(offsetof(mm8::Dlg, firstItemPtr) == 76);
	static_assert(offsetof(mm8::Dlg, lastItemPtr) == 80);



	struct GameClasses // size: 0x6007A8CC
	{
		static uint8_t* HPBase; // original offset 0x4FD9DC (5233116 decimal)element size: 0x1 (1 decimal)
		static uint32_t HPBase_size; // Offset/size: 0x7A (122 decimal)
		static uint8_t* HPFactor; // original offset 0x4FD9FC (5233148 decimal)element size: 0x1 (1 decimal)
		static uint32_t HPFactor_size; // Offset/size: 0x7A (122 decimal)
		static uint8_t* SPBase; // original offset 0x4FD9EC (5233132 decimal)element size: 0x1 (1 decimal)
		static uint32_t SPBase_size; // Offset/size: 0x7A (122 decimal)
		static uint8_t* SPFactor; // original offset 0x4FDA0C (5233164 decimal)element size: 0x1 (1 decimal)
		static uint32_t SPFactor_size; // Offset/size: 0x7A (122 decimal)
		static uint8_t* SPStats; // original offset 0x6007A8BC (1611114684 decimal)element size: 0x1 (1 decimal)
		static uint32_t SPStats_size; // Offset/size: 0x7A (122 decimal)
		static std::array<uint8_t, 39>* skills; // original offset 0x4FDD18 (5233944 decimal)element size: 0x27 (39 decimal)
		static uint32_t skills_size; // Offset/size: 0x7A (122 decimal)
		static std::array<mm8::StartStat, 7>* startingStats; // original offset 0x4FDA20 (5233184 decimal)element size: 0x1C (28 decimal)
		static uint32_t startingStats_size; // Offset/size: 0x28 (40 decimal)

		SKIP(1611114700);
	};
	static_assert(sizeof(mm8::GameClasses) == 0x6007A8CC, "Invalid \"mm8::GameClasses\" structure size");



	struct GameClassKinds // size: 0x4FDD18
	{
		static std::array<uint8_t, 39>* startingSkills; // original offset 0x4FDBE0 (5233632 decimal)element size: 0x27 (39 decimal)
		static uint32_t startingSkills_size; // Offset/size: 0x3D (61 decimal)

		SKIP(5233944);
	};
	static_assert(sizeof(mm8::GameClassKinds) == 0x4FDD18, "Invalid \"mm8::GameClassKinds\" structure size");
}

#pragma pack(pop)