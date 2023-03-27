#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct GameClassKinds // size: 0x4C274E
	{
		static std::array<uint8_t, 31>* startingSkills; // converted to pointer to not break with limits removal scripts
		static uint32_t startingSkills_size; // size field, set during initialization by getting data from lua

		SKIP(4990512);
		std::array<uint8_t, 6> HPBase;
		SKIP(2);
		std::array<uint8_t, 6> SPBase;
		SKIP(42);
		std::array<std::array<uint8_t, 7>, 6> startingStats;
		SKIP(188);
	};
	static_assert(sizeof(mm6::GameClassKinds) == 0x4C274E, "Invalid \"mm6::GameClassKinds\" structure size");
	static_assert(offsetof(mm6::GameClassKinds, HPBase) == 4990512);
	static_assert(offsetof(mm6::GameClassKinds, SPBase) == 4990520);
	static_assert(offsetof(mm6::GameClassKinds, startingStats) == 4990568);



	struct GameClasses // size: 0x60020196
	{
		static uint8_t* HPFactor; // converted to pointer to not break with limits removal scripts
		static uint32_t HPFactor_size; // size field, set during initialization by getting data from lua
		static uint8_t* SPFactor; // converted to pointer to not break with limits removal scripts
		static uint32_t SPFactor_size; // size field, set during initialization by getting data from lua
		static uint8_t* SPStats; // converted to pointer to not break with limits removal scripts
		static uint32_t SPStats_size; // size field, set during initialization by getting data from lua

		SKIP(1610744214);
	};
	static_assert(sizeof(mm6::GameClasses) == 0x60020196, "Invalid \"mm6::GameClasses\" structure size");



	struct Dlg // size: 0x54
	{
		int32_t left;
		int32_t top;
		int32_t width;
		int32_t height;
		int32_t right_;
		int32_t bottom_;
		int32_t dlgID;
		int16_t param;
		SKIP(2);
		int32_t itemsCount;
		SKIP(4);
		int32_t keyboardItemsCount;
		int32_t keyboardItem;
		int32_t keyboardNavigationTrackMouse;
		int32_t keyboardLeftRightStep;
		int32_t keyboardItemsStart;
		int32_t index;
		SKIP(4);
		int32_t useKeyboadNavigation;
		SKIP(4);
		uint32_t firstItemPtr;
		uint32_t lastItemPtr;
	};
	static_assert(sizeof(mm6::Dlg) == 0x54, "Invalid \"mm6::Dlg\" structure size");
	static_assert(offsetof(mm6::Dlg, top) == 4);
	static_assert(offsetof(mm6::Dlg, width) == 8);
	static_assert(offsetof(mm6::Dlg, height) == 12);
	static_assert(offsetof(mm6::Dlg, right_) == 16);
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
	static_assert(offsetof(mm6::Dlg, useKeyboadNavigation) == 68);
	static_assert(offsetof(mm6::Dlg, firstItemPtr) == 76);
	static_assert(offsetof(mm6::Dlg, lastItemPtr) == 80);



	struct GameScreen // size: 0x400C4
	{
		SKIP(4);
		int32_t width;
		int32_t height;
		int32_t pitch;
		int32_t cx1;
		int32_t cy1;
		int32_t cx2;
		int32_t cy2;
		SKIP(262148);
		uint32_t buffer;
		uint32_t objectByPixel;
		SKIP(128);
		uint32_t redBits;
		uint32_t blueBits;
		uint32_t greenBits;
		uint32_t redMask;
		uint32_t greenMask;
		uint32_t blueMask;
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



	struct DialogLogic // size: 0x3243C34
	{
		static int32_t* list; // converted to pointer to not break with limits removal scripts
		static uint32_t* list_sizePtr; // pointer to size, set during initialization by getting data from lua

		SKIP(5025464);
		int32_t scrollPage;
		SKIP(4);
		union
		{
			int32_t mapMoveDownClicked;
			uint32_t autonoteTab2Clicked; // 4-byte boolean
		};
		SKIP(4);
		int32_t scrollPos;
		SKIP(592);
		uint32_t autonoteTab5Clicked; // 4-byte boolean
		SKIP(8);
		uint32_t scrollUpClicked; // 4-byte boolean
		SKIP(124);
		union
		{
			uint32_t autonoteTab3Clicked; // 4-byte boolean
			int32_t mapMoveLeftClicked;
		};
		SKIP(4);
		union
		{
			int32_t mapMoveUpClicked;
			uint32_t autonoteTab1Clicked; // 4-byte boolean
		};
		SKIP(36);
		int32_t countOnScreen;
		SKIP(4);
		int32_t listCount;
		SKIP(12);
		uint32_t scrollDownClicked; // 4-byte boolean
		union
		{
			uint32_t autonoteTab4Clicked; // 4-byte boolean
			int32_t mapMoveRightClicked;
		};
		SKIP(4);
		int32_t autonotesCategory;
		SKIP(20);
		int32_t spellBookSelection;
		SKIP(416);
		mm6::MapMonster monsterInfoMonster;
		SKIP(47679064);
	};
	static_assert(sizeof(mm6::DialogLogic) == 0x3243C34, "Invalid \"mm6::DialogLogic\" structure size");
	static_assert(offsetof(mm6::DialogLogic, scrollPage) == 5025464);
	static_assert(offsetof(mm6::DialogLogic, mapMoveDownClicked) == 5025472);
	static_assert(offsetof(mm6::DialogLogic, autonoteTab2Clicked) == 5025472);
	static_assert(offsetof(mm6::DialogLogic, scrollPos) == 5025480);
	static_assert(offsetof(mm6::DialogLogic, autonoteTab5Clicked) == 5026076);
	static_assert(offsetof(mm6::DialogLogic, scrollUpClicked) == 5026088);
	static_assert(offsetof(mm6::DialogLogic, autonoteTab3Clicked) == 5026216);
	static_assert(offsetof(mm6::DialogLogic, mapMoveLeftClicked) == 5026216);
	static_assert(offsetof(mm6::DialogLogic, mapMoveUpClicked) == 5026224);
	static_assert(offsetof(mm6::DialogLogic, autonoteTab1Clicked) == 5026224);
	static_assert(offsetof(mm6::DialogLogic, countOnScreen) == 5026264);
	static_assert(offsetof(mm6::DialogLogic, listCount) == 5026272);
	static_assert(offsetof(mm6::DialogLogic, scrollDownClicked) == 5026288);
	static_assert(offsetof(mm6::DialogLogic, autonoteTab4Clicked) == 5026292);
	static_assert(offsetof(mm6::DialogLogic, mapMoveRightClicked) == 5026292);
	static_assert(offsetof(mm6::DialogLogic, autonotesCategory) == 5026300);
	static_assert(offsetof(mm6::DialogLogic, spellBookSelection) == 5026324);
	static_assert(offsetof(mm6::DialogLogic, monsterInfoMonster) == 5026744);
}
namespace mm7
{
	struct GameClassKinds // size: 0x4ED815
	{
		static std::array<uint8_t, 37>* startingSkills; // converted to pointer to not break with limits removal scripts
		static uint32_t startingSkills_size; // size field, set during initialization by getting data from lua

		SKIP(5166584);
		std::array<uint8_t, 9> HPBase;
		SKIP(3);
		std::array<uint8_t, 9> SPBase;
		SKIP(520);
	};
	static_assert(sizeof(mm7::GameClassKinds) == 0x4ED815, "Invalid \"mm7::GameClassKinds\" structure size");
	static_assert(offsetof(mm7::GameClassKinds, HPBase) == 5166584);
	static_assert(offsetof(mm7::GameClassKinds, SPBase) == 5166596);



	struct GameClasses // size: 0x600201BC
	{
		static std::array<uint8_t, 37>* skills; // converted to pointer to not break with limits removal scripts
		static uint32_t skills_size; // size field, set during initialization by getting data from lua
		static uint8_t* HPFactor; // converted to pointer to not break with limits removal scripts
		static uint32_t HPFactor_size; // size field, set during initialization by getting data from lua
		static uint8_t* SPFactor; // converted to pointer to not break with limits removal scripts
		static uint32_t SPFactor_size; // size field, set during initialization by getting data from lua
		static uint8_t* SPStats; // converted to pointer to not break with limits removal scripts
		static uint32_t SPStats_size; // size field, set during initialization by getting data from lua

		SKIP(1610744252);
	};
	static_assert(sizeof(mm7::GameClasses) == 0x600201BC, "Invalid \"mm7::GameClasses\" structure size");



	struct GameRaces // size: 0x4ED6C8
	{
		SKIP(5166680);
		std::array<std::array<mm7::StartStat, 7>, 4> startingStats;
	};
	static_assert(sizeof(mm7::GameRaces) == 0x4ED6C8, "Invalid \"mm7::GameRaces\" structure size");
	static_assert(offsetof(mm7::GameRaces, startingStats) == 5166680);



	struct GameScreen // size: 0x400F0
	{
		uint32_t isD3D; // 4-byte boolean
		SKIP(12);
		int32_t width;
		int32_t height;
		int32_t pitch;
		int32_t cx1;
		int32_t cy1;
		int32_t cx2;
		int32_t cy2;
		SKIP(262152);
		uint32_t objectByPixel;
		SKIP(148);
		uint32_t redBits;
		uint32_t blueBits;
		uint32_t greenBits;
		uint32_t redMask;
		uint32_t greenMask;
		uint32_t blueMask;
		SKIP(8);
		uint32_t buffer;
	};
	static_assert(sizeof(mm7::GameScreen) == 0x400F0, "Invalid \"mm7::GameScreen\" structure size");
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



	struct DialogLogic // size: 0x5C4430
	{
		static int32_t* list; // converted to pointer to not break with limits removal scripts
		static uint32_t* list_sizePtr; // pointer to size, set during initialization by getting data from lua

		SKIP(5122552);
		std::array<int32_t, 5> armorSkills; // requires unprotect before change
		std::array<int32_t, 9> weaponSkills; // requires unprotect before change
		std::array<int32_t, 12> miscSkills; // requires unprotect before change
		std::array<int32_t, 9> magicSkills; // requires unprotect before change
		SKIP(145688);
		int32_t scrollPage;
		int32_t countOnScreen;
		int32_t listCount;
		int32_t scrollPos;
		uint32_t autonoteTab6Clicked; // 4-byte boolean
		uint32_t autonoteTab5Clicked; // 4-byte boolean
		union
		{
			uint32_t autonoteTab4Clicked; // 4-byte boolean
			uint32_t mapMoveRightClicked; // 4-byte boolean
		};
		union
		{
			uint32_t autonoteTab3Clicked; // 4-byte boolean
			uint32_t mapMoveLeftClicked; // 4-byte boolean
		};
		union
		{
			uint32_t autonoteTab2Clicked; // 4-byte boolean
			uint32_t mapMoveDownClicked; // 4-byte boolean
		};
		union
		{
			uint32_t autonoteTab1Clicked; // 4-byte boolean
			uint32_t mapMoveUpClicked; // 4-byte boolean
		};
		uint32_t scrollDownClicked; // 4-byte boolean
		uint32_t scrollUpClicked; // 4-byte boolean
		int32_t spellBookSelection;
		bool spellBookSelectedNewSpell;
		SKIP(23);
		int32_t autonotesCategory;
		SKIP(20);
		mm7::MapMonster monsterInfoMonster;
		SKIP(777452);
	};
	static_assert(sizeof(mm7::DialogLogic) == 0x5C4430, "Invalid \"mm7::DialogLogic\" structure size");
	static_assert(offsetof(mm7::DialogLogic, armorSkills) == 5122552);
	static_assert(offsetof(mm7::DialogLogic, weaponSkills) == 5122572);
	static_assert(offsetof(mm7::DialogLogic, miscSkills) == 5122608);
	static_assert(offsetof(mm7::DialogLogic, magicSkills) == 5122656);
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



	struct Dlg // size: 0x54
	{
		int32_t left;
		int32_t top;
		int32_t width;
		int32_t height;
		int32_t right_;
		int32_t bottom_;
		int32_t dlgID;
		int32_t param;
		int32_t itemsCount;
		SKIP(4);
		int32_t keyboardItemsCount;
		int32_t keyboardItem;
		int32_t keyboardNavigationTrackMouse;
		int32_t keyboardLeftRightStep;
		int32_t keyboardItemsStart;
		int32_t index;
		SKIP(4);
		int32_t useKeyboadNavigation;
		SKIP(4);
		uint32_t firstItemPtr;
		uint32_t lastItemPtr;
	};
	static_assert(sizeof(mm7::Dlg) == 0x54, "Invalid \"mm7::Dlg\" structure size");
	static_assert(offsetof(mm7::Dlg, top) == 4);
	static_assert(offsetof(mm7::Dlg, width) == 8);
	static_assert(offsetof(mm7::Dlg, height) == 12);
	static_assert(offsetof(mm7::Dlg, right_) == 16);
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
	static_assert(offsetof(mm7::Dlg, useKeyboadNavigation) == 68);
	static_assert(offsetof(mm7::Dlg, firstItemPtr) == 76);
	static_assert(offsetof(mm7::Dlg, lastItemPtr) == 80);
}
namespace mm8
{
	struct GameScreen // size: 0x400F0
	{
		uint32_t isD3D; // 4-byte boolean
		SKIP(12);
		int32_t width;
		int32_t height;
		int32_t pitch;
		int32_t cx1;
		int32_t cy1;
		int32_t cx2;
		int32_t cy2;
		SKIP(262152);
		uint32_t objectByPixel;
		SKIP(148);
		uint32_t redBits;
		uint32_t blueBits;
		uint32_t greenBits;
		uint32_t redMask;
		uint32_t greenMask;
		uint32_t blueMask;
		SKIP(8);
		uint32_t buffer;
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



	struct GameClassKinds // size: 0x4FDD18
	{
		static std::array<uint8_t, 39>* startingSkills; // converted to pointer to not break with limits removal scripts
		static uint32_t startingSkills_size; // size field, set during initialization by getting data from lua

		SKIP(5233944);
	};
	static_assert(sizeof(mm8::GameClassKinds) == 0x4FDD18, "Invalid \"mm8::GameClassKinds\" structure size");



	struct GameClasses // size: 0x6007A8CC
	{
		static std::array<mm8::StartStat, 7>* startingStats; // converted to pointer to not break with limits removal scripts
		static uint32_t startingStats_size; // size field, set during initialization by getting data from lua
		static uint8_t* SPBase; // converted to pointer to not break with limits removal scripts
		static uint32_t SPBase_size; // size field, set during initialization by getting data from lua
		static uint8_t* SPStats; // converted to pointer to not break with limits removal scripts
		static uint32_t SPStats_size; // size field, set during initialization by getting data from lua
		static uint8_t* HPBase; // converted to pointer to not break with limits removal scripts
		static uint32_t HPBase_size; // size field, set during initialization by getting data from lua
		static std::array<uint8_t, 39>* skills; // converted to pointer to not break with limits removal scripts
		static uint32_t skills_size; // size field, set during initialization by getting data from lua
		static uint8_t* SPFactor; // converted to pointer to not break with limits removal scripts
		static uint32_t SPFactor_size; // size field, set during initialization by getting data from lua
		static uint8_t* HPFactor; // converted to pointer to not break with limits removal scripts
		static uint32_t HPFactor_size; // size field, set during initialization by getting data from lua

		SKIP(1611114700);
	};
	static_assert(sizeof(mm8::GameClasses) == 0x6007A8CC, "Invalid \"mm8::GameClasses\" structure size");



	struct DialogLogic // size: 0x5DC8E0
	{
		static int32_t* list; // converted to pointer to not break with limits removal scripts
		static uint32_t* list_sizePtr; // pointer to size, set during initialization by getting data from lua

		SKIP(5191936);
		std::array<int32_t, 5> armorSkills; // requires unprotect before change
		std::array<int32_t, 9> weaponSkills; // requires unprotect before change
		std::array<int32_t, 12> miscSkills; // requires unprotect before change
		std::array<int32_t, 12> magicSkills; // requires unprotect before change
		SKIP(147796);
		int32_t scrollPage;
		int32_t countOnScreen;
		int32_t listCount;
		int32_t scrollPos;
		uint32_t autonoteTab6Clicked; // 4-byte boolean
		uint32_t autonoteTab5Clicked; // 4-byte boolean
		union
		{
			uint32_t mapMoveRightClicked; // 4-byte boolean
			uint32_t autonoteTab4Clicked; // 4-byte boolean
		};
		union
		{
			uint32_t autonoteTab3Clicked; // 4-byte boolean
			uint32_t mapMoveLeftClicked; // 4-byte boolean
		};
		union
		{
			uint32_t autonoteTab2Clicked; // 4-byte boolean
			uint32_t mapMoveDownClicked; // 4-byte boolean
		};
		union
		{
			uint32_t mapMoveUpClicked; // 4-byte boolean
			uint32_t autonoteTab1Clicked; // 4-byte boolean
		};
		uint32_t scrollDownClicked; // 4-byte boolean
		uint32_t scrollUpClicked; // 4-byte boolean
		int32_t spellBookSelection;
		bool spellBookSelectedNewSpell;
		SKIP(23);
		int32_t autonotesCategory;
		SKIP(20);
		mm8::MapMonster monsterInfoMonster;
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
	static_assert(offsetof(mm8::DialogLogic, mapMoveRightClicked) == 5339908);
	static_assert(offsetof(mm8::DialogLogic, autonoteTab4Clicked) == 5339908);
	static_assert(offsetof(mm8::DialogLogic, autonoteTab3Clicked) == 5339912);
	static_assert(offsetof(mm8::DialogLogic, mapMoveLeftClicked) == 5339912);
	static_assert(offsetof(mm8::DialogLogic, autonoteTab2Clicked) == 5339916);
	static_assert(offsetof(mm8::DialogLogic, mapMoveDownClicked) == 5339916);
	static_assert(offsetof(mm8::DialogLogic, mapMoveUpClicked) == 5339920);
	static_assert(offsetof(mm8::DialogLogic, autonoteTab1Clicked) == 5339920);
	static_assert(offsetof(mm8::DialogLogic, scrollDownClicked) == 5339924);
	static_assert(offsetof(mm8::DialogLogic, scrollUpClicked) == 5339928);
	static_assert(offsetof(mm8::DialogLogic, spellBookSelection) == 5339932);
	static_assert(offsetof(mm8::DialogLogic, spellBookSelectedNewSpell) == 5339936);
	static_assert(offsetof(mm8::DialogLogic, autonotesCategory) == 5339960);
	static_assert(offsetof(mm8::DialogLogic, monsterInfoMonster) == 5339984);



	struct Dlg // size: 0x54
	{
		int32_t left;
		int32_t top;
		int32_t width;
		int32_t height;
		int32_t right_;
		int32_t bottom_;
		int32_t dlgID;
		int32_t param;
		int32_t itemsCount;
		SKIP(4);
		int32_t keyboardItemsCount;
		int32_t keyboardItem;
		int32_t keyboardNavigationTrackMouse;
		int32_t keyboardLeftRightStep;
		int32_t keyboardItemsStart;
		int32_t index;
		SKIP(4);
		int32_t useKeyboadNavigation;
		SKIP(4);
		uint32_t firstItemPtr;
		uint32_t lastItemPtr;
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
}

#pragma pack(pop)