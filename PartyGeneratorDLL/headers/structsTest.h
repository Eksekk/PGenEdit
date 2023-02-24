#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm7
{
	struct SpellEffect; // 0-size struct, declaration only

	struct TileItem // size: 0x1A
	{
		std::array<char, 16> name; // requires null terminator | .0, 0x0
		int16_t id; // .16, 0x10
		static_assert(offsetof(mm7::TileItem, id) == 16);
		int16_t bitmap; // .18, 0x12
		static_assert(offsetof(mm7::TileItem, bitmap) == 18);
		int16_t tileSet; // .20, 0x14
		static_assert(offsetof(mm7::TileItem, tileSet) == 20);
		int16_t section; // .22, 0x16
		static_assert(offsetof(mm7::TileItem, section) == 22);
		union
		{
			uint16_t bits; // .24, 0x18
			static_assert(offsetof(mm7::TileItem, bits) == 24);
			struct
			{
				bool burn : 1; // .24, 0x18
				bool water : 1; // .24, 0x18
				bool block : 1; // .24, 0x18
				bool repulse : 1; // .24, 0x18
				bool flat : 1; // .24, 0x18
				bool wave : 1; // .24, 0x18
				bool noDraw : 1; // .24, 0x18
				SKIPBITS(1);
				bool waterTransition : 1; // .25, 0x19
				bool transition : 1; // .25, 0x19
				bool scrollDown : 1; // .25, 0x19
				bool scrollUp : 1; // .25, 0x19
				bool scrollLeft : 1; // .25, 0x19
				bool scrollRight : 1; // .25, 0x19
			};
		};
	};
	static_assert(sizeof(mm7::TileItem) == 0x1A, "Invalid \"mm7::TileItem\" structure size");

	struct SoundsItem // size: 0x78
	{
		std::array<char, 32> name; // requires null terminator | .0, 0x0
		int32_t id; // .32, 0x20
		static_assert(offsetof(mm7::SoundsItem, id) == 32);
		int32_t type; // .36, 0x24
		static_assert(offsetof(mm7::SoundsItem, type) == 36);
		union
		{
			uint32_t bits; // .40, 0x28
			static_assert(offsetof(mm7::SoundsItem, bits) == 40);
			struct
			{
				bool locked : 1; // .40, 0x28
				bool is3D : 1; // .40, 0x28
			};
		};
		std::array<uint32_t, 17> data; // .44, 0x2C
		static_assert(offsetof(mm7::SoundsItem, data) == 44);
		uint32_t data3D; // .112, 0x70
		static_assert(offsetof(mm7::SoundsItem, data3D) == 112);
		uint32_t decompressed; // 4-byte boolean | .116, 0x74
		static_assert(offsetof(mm7::SoundsItem, decompressed) == 116);
	};
	static_assert(sizeof(mm7::SoundsItem) == 0x78, "Invalid \"mm7::SoundsItem\" structure size");

	struct Dlg // size: 0x54
	{
		int32_t left; // .0, 0x0
		int32_t top; // .4, 0x4
		static_assert(offsetof(mm7::Dlg, top) == 4);
		int32_t width; // .8, 0x8
		static_assert(offsetof(mm7::Dlg, width) == 8);
		int32_t height; // .12, 0xC
		static_assert(offsetof(mm7::Dlg, height) == 12);
		int32_t right_; // .16, 0x10
		static_assert(offsetof(mm7::Dlg, right_) == 16);
		int32_t bottom_; // .20, 0x14
		static_assert(offsetof(mm7::Dlg, bottom_) == 20);
		int32_t dlgID; // .24, 0x18
		static_assert(offsetof(mm7::Dlg, dlgID) == 24);
		int32_t param; // .28, 0x1C
		static_assert(offsetof(mm7::Dlg, param) == 28);
		int32_t itemsCount; // .32, 0x20
		static_assert(offsetof(mm7::Dlg, itemsCount) == 32);
		SKIP(4);
		int32_t keyboardItemsCount; // .40, 0x28
		static_assert(offsetof(mm7::Dlg, keyboardItemsCount) == 40);
		int32_t keyboardItem; // .44, 0x2C
		static_assert(offsetof(mm7::Dlg, keyboardItem) == 44);
		int32_t keyboardNavigationTrackMouse; // .48, 0x30
		static_assert(offsetof(mm7::Dlg, keyboardNavigationTrackMouse) == 48);
		int32_t keyboardLeftRightStep; // .52, 0x34
		static_assert(offsetof(mm7::Dlg, keyboardLeftRightStep) == 52);
		int32_t keyboardItemsStart; // .56, 0x38
		static_assert(offsetof(mm7::Dlg, keyboardItemsStart) == 56);
		int32_t index; // .60, 0x3C
		static_assert(offsetof(mm7::Dlg, index) == 60);
		SKIP(4);
		int32_t useKeyboadNavigation; // .68, 0x44
		static_assert(offsetof(mm7::Dlg, useKeyboadNavigation) == 68);
		SKIP(4);
		uint32_t firstItemPtr; // .76, 0x4C
		static_assert(offsetof(mm7::Dlg, firstItemPtr) == 76);
		uint32_t lastItemPtr; // .80, 0x50
		static_assert(offsetof(mm7::Dlg, lastItemPtr) == 80);
	};
	static_assert(sizeof(mm7::Dlg) == 0x54, "Invalid \"mm7::Dlg\" structure size");

	struct DecListItem // size: 0x54
	{
		std::array<char, 32> name; // requires null terminator | .0, 0x0
		std::array<char, 32> gameName; // requires null terminator | .0, 0x0
		int16_t type; // .64, 0x40
		static_assert(offsetof(mm7::DecListItem, type) == 64);
		int16_t height; // .66, 0x42
		static_assert(offsetof(mm7::DecListItem, height) == 66);
		int16_t radius; // .68, 0x44
		static_assert(offsetof(mm7::DecListItem, radius) == 68);
		int16_t lightRadius; // .70, 0x46
		static_assert(offsetof(mm7::DecListItem, lightRadius) == 70);
		union
		{
			std::array<uint8_t, 2> SFTGroup; // Unknown type | .0, 0x0
			int16_t SFTIndex; // .72, 0x48
			static_assert(offsetof(mm7::DecListItem, SFTIndex) == 72);
		};
		union
		{
			uint16_t bits; // .74, 0x4A
			static_assert(offsetof(mm7::DecListItem, bits) == 74);
			struct
			{
				bool noBlockMovement : 1; // .74, 0x4A
				bool noDraw : 1; // .74, 0x4A
				bool flickerSlow : 1; // .74, 0x4A
				bool flickerMedium : 1; // .74, 0x4A
				bool flickerFast : 1; // .74, 0x4A
				bool marker : 1; // .74, 0x4A
				bool slowLoop : 1; // .74, 0x4A
				bool emitFire : 1; // .74, 0x4A
				bool soundOnDawn : 1; // .75, 0x4B
				bool soundOnDusk : 1; // .75, 0x4B
				bool emitSmoke : 1; // .75, 0x4B
			};
		};
		int16_t soundId; // .76, 0x4C
		static_assert(offsetof(mm7::DecListItem, soundId) == 76);
		SKIP(2);
		uint8_t red; // .80, 0x50
		static_assert(offsetof(mm7::DecListItem, red) == 80);
		uint8_t green; // .81, 0x51
		static_assert(offsetof(mm7::DecListItem, green) == 81);
		uint8_t blue; // .82, 0x52
		static_assert(offsetof(mm7::DecListItem, blue) == 82);
		SKIP(1);
	};
	static_assert(sizeof(mm7::DecListItem) == 0x54, "Invalid \"mm7::DecListItem\" structure size");

	struct SFTItem // size: 0x3C
	{
		std::array<char, 12> groupName; // requires null terminator | .0, 0x0
		std::array<char, 12> spriteName; // requires null terminator | .0, 0x0
		std::array<int16_t, 8> spriteIndex; // .24, 0x18
		static_assert(offsetof(mm7::SFTItem, spriteIndex) == 24);
		int32_t scale; // .40, 0x28
		static_assert(offsetof(mm7::SFTItem, scale) == 40);
		union
		{
			uint32_t bits; // .44, 0x2C
			static_assert(offsetof(mm7::SFTItem, bits) == 44);
			struct
			{
				bool notGroupEnd : 1; // .44, 0x2C
				bool luminous : 1; // .44, 0x2C
				bool groupStart : 1; // .44, 0x2C
				SKIPBITS(1);
				bool image1 : 1; // .44, 0x2C
				bool center : 1; // .44, 0x2C
				bool fidget : 1; // .44, 0x2C
				bool loaded : 1; // .44, 0x2C
				bool mirror0 : 1; // .45, 0x2D
				bool mirror1 : 1; // .45, 0x2D
				bool mirror2 : 1; // .45, 0x2D
				bool mirror3 : 1; // .45, 0x2D
				bool mirror4 : 1; // .45, 0x2D
				bool mirror5 : 1; // .45, 0x2D
				bool mirror6 : 1; // .45, 0x2D
				bool mirror7 : 1; // .45, 0x2D
				bool images3 : 1; // .46, 0x2E
				bool glow : 1; // .46, 0x2E
				bool transparent : 1; // .46, 0x2E
			};
		};
		int16_t lightRadius; // .48, 0x30
		static_assert(offsetof(mm7::SFTItem, lightRadius) == 48);
		int16_t paletteId; // .50, 0x32
		static_assert(offsetof(mm7::SFTItem, paletteId) == 50);
		int16_t paletteIndex; // .52, 0x34
		static_assert(offsetof(mm7::SFTItem, paletteIndex) == 52);
		int16_t time; // .54, 0x36
		static_assert(offsetof(mm7::SFTItem, time) == 54);
		int16_t totalTime; // .56, 0x38
		static_assert(offsetof(mm7::SFTItem, totalTime) == 56);
		SKIP(2);
	};
	static_assert(sizeof(mm7::SFTItem) == 0x3C, "Invalid \"mm7::SFTItem\" structure size");

	struct SFT // size: 0x18
	{
		uint32_t frames_size; // .0, 0x0
		union
		{
			uint32_t groups_size; // .4, 0x4
			static_assert(offsetof(mm7::SFT, groups_size) == 4);
			uint32_t groupIndex_size; // .4, 0x4
			static_assert(offsetof(mm7::SFT, groupIndex_size) == 4);
		};
		int32_t matchIndex; // .8, 0x8
		static_assert(offsetof(mm7::SFT, matchIndex) == 8);
		mm7::SFTItem* frames; // size offset is 0x0 | .12, 0xC
		static_assert(offsetof(mm7::SFT, frames) == 12);
		mm7::SFTItem** groups; // size offset is 0x4 | .16, 0x10
		static_assert(offsetof(mm7::SFT, groups) == 16);
		int16_t* groupIndex; // size offset is 0x4 | .20, 0x14
		static_assert(offsetof(mm7::SFT, groupIndex) == 20);
	};
	static_assert(sizeof(mm7::SFT) == 0x18, "Invalid \"mm7::SFT\" structure size");

	struct GameClassKinds // size: 0x4ED815
	{
		SKIP(5166584);
		std::array<uint8_t, 9> HPBase; // .5166584, 0x4ED5F8
		static_assert(offsetof(mm7::GameClassKinds, HPBase) == 5166584);
		SKIP(3);
		std::array<uint8_t, 9> SPBase; // .5166596, 0x4ED604
		static_assert(offsetof(mm7::GameClassKinds, SPBase) == 5166596);
		SKIP(187);
		std::array<std::array<uint8_t, 37>, 9> startingSkills; // .5166792, 0x4ED6C8
		static_assert(offsetof(mm7::GameClassKinds, startingSkills) == 5166792);
	};
	static_assert(sizeof(mm7::GameClassKinds) == 0x4ED815, "Invalid \"mm7::GameClassKinds\" structure size");

	struct GameClasses // size: 0x600201BC
	{
		SKIP(5166608);
		std::array<uint8_t, 36> HPFactor; // .5166608, 0x4ED610
		static_assert(offsetof(mm7::GameClasses, HPFactor) == 5166608);
		std::array<uint8_t, 36> SPFactor; // .5166644, 0x4ED634
		static_assert(offsetof(mm7::GameClasses, SPFactor) == 5166644);
		SKIP(448);
		std::array<std::array<uint8_t, 37>, 36> skills; // .5167128, 0x4ED818
		static_assert(offsetof(mm7::GameClasses, skills) == 5167128);
		SKIP(1605575756);
		std::array<uint8_t, 36> SPStats; // .1610744216, 0x60020198
		static_assert(offsetof(mm7::GameClasses, SPStats) == 1610744216);
	};
	static_assert(sizeof(mm7::GameClasses) == 0x600201BC, "Invalid \"mm7::GameClasses\" structure size");

	struct StartStat // size: 0x4
	{
		int8_t base; // .0, 0x0
		int8_t max; // .1, 0x1
		static_assert(offsetof(mm7::StartStat, max) == 1);
		int8_t spend; // .2, 0x2
		static_assert(offsetof(mm7::StartStat, spend) == 2);
		int8_t add; // .3, 0x3
		static_assert(offsetof(mm7::StartStat, add) == 3);
	};
	static_assert(sizeof(mm7::StartStat) == 0x4, "Invalid \"mm7::StartStat\" structure size");

	struct GameRaces // size: 0x4ED6C8
	{
		SKIP(5166680);
		std::array<std::array<mm7::StartStat, 7>, 4> startingStats; // .5166680, 0x4ED658
		static_assert(offsetof(mm7::GameRaces, startingStats) == 5166680);
	};
	static_assert(sizeof(mm7::GameRaces) == 0x4ED6C8, "Invalid \"mm7::GameRaces\" structure size");

	struct TravelInfo // size: 0x20
	{
		union
		{
			uint8_t mapIndex; // .0, 0x0
			std::array<uint8_t, 1> map; // Unknown type | .0, 0x0
		};
		union
		{
			std::array<uint8_t, 7> daysAvailable; // .1, 0x1
			static_assert(offsetof(mm7::TravelInfo, daysAvailable) == 1);
			struct
			{
				bool monday; // .1, 0x1
				static_assert(offsetof(mm7::TravelInfo, monday) == 1);
				bool tuesday; // .2, 0x2
				static_assert(offsetof(mm7::TravelInfo, tuesday) == 2);
				bool wednesday; // .3, 0x3
				static_assert(offsetof(mm7::TravelInfo, wednesday) == 3);
				bool thursday; // .4, 0x4
				static_assert(offsetof(mm7::TravelInfo, thursday) == 4);
				bool friday; // .5, 0x5
				static_assert(offsetof(mm7::TravelInfo, friday) == 5);
				bool saturday; // .6, 0x6
				static_assert(offsetof(mm7::TravelInfo, saturday) == 6);
				bool sunday; // .7, 0x7
				static_assert(offsetof(mm7::TravelInfo, sunday) == 7);
			};
		};
		uint8_t daysCount; // .8, 0x8
		static_assert(offsetof(mm7::TravelInfo, daysCount) == 8);
		SKIP(3);
		union
		{
			std::array<int32_t, 3> pos; // .12, 0xC
			static_assert(offsetof(mm7::TravelInfo, pos) == 12);
			struct
			{
				int32_t x; // .12, 0xC
				static_assert(offsetof(mm7::TravelInfo, x) == 12);
				int32_t y; // .16, 0x10
				static_assert(offsetof(mm7::TravelInfo, y) == 16);
				int32_t z; // .20, 0x14
				static_assert(offsetof(mm7::TravelInfo, z) == 20);
			};
		};
		int32_t direction; // .24, 0x18
		static_assert(offsetof(mm7::TravelInfo, direction) == 24);
		int32_t QBit; // .28, 0x1C
		static_assert(offsetof(mm7::TravelInfo, QBit) == 28);
	};
	static_assert(sizeof(mm7::TravelInfo) == 0x20, "Invalid \"mm7::TravelInfo\" structure size");

	struct HouseMovie // size: 0x10
	{
		char* fileName; // .0, 0x0
		uint8_t background; // .4, 0x4
		static_assert(offsetof(mm7::HouseMovie, background) == 4);
		SKIP(3);
		int32_t NPCPic; // .8, 0x8
		static_assert(offsetof(mm7::HouseMovie, NPCPic) == 8);
		uint8_t houseType; // .12, 0xC
		static_assert(offsetof(mm7::HouseMovie, houseType) == 12);
		uint8_t sounds; // .13, 0xD
		static_assert(offsetof(mm7::HouseMovie, sounds) == 13);
		SKIP(2);
	};
	static_assert(sizeof(mm7::HouseMovie) == 0x10, "Invalid \"mm7::HouseMovie\" structure size");

	struct ShopItemKind // size: 0xA
	{
		int16_t level; // .0, 0x0
		std::array<int16_t, 4> types; // MMExt: 1..4, here 0..3 | .2, 0x2
		static_assert(offsetof(mm7::ShopItemKind, types) == 2);
	};
	static_assert(sizeof(mm7::ShopItemKind) == 0xA, "Invalid \"mm7::ShopItemKind\" structure size");

	struct FogChances // size: 0x4
	{
		uint8_t thick; // .0, 0x0
		uint8_t medium; // .1, 0x1
		static_assert(offsetof(mm7::FogChances, medium) == 1);
		uint8_t light; // .2, 0x2
		static_assert(offsetof(mm7::FogChances, light) == 2);
		SKIP(1);
	};
	static_assert(sizeof(mm7::FogChances) == 0x4, "Invalid \"mm7::FogChances\" structure size");

	struct HistoryTxtItem // size: 0xC
	{
		char* text; // .0, 0x0
		char* title; // .4, 0x4
		static_assert(offsetof(mm7::HistoryTxtItem, title) == 4);
		int8_t time; // .8, 0x8
		static_assert(offsetof(mm7::HistoryTxtItem, time) == 8);
		SKIP(3);
	};
	static_assert(sizeof(mm7::HistoryTxtItem) == 0xC, "Invalid \"mm7::HistoryTxtItem\" structure size");

	struct SpcItemsTxtItem // size: 0x1C
	{
		char* nameAdd; // .0, 0x0
		char* bonusStat; // .4, 0x4
		static_assert(offsetof(mm7::SpcItemsTxtItem, bonusStat) == 4);
		union
		{
			std::array<uint8_t, 12> chanceForSlot; // .8, 0x8
			static_assert(offsetof(mm7::SpcItemsTxtItem, chanceForSlot) == 8);
			struct
			{
				uint8_t W1; // .8, 0x8
				static_assert(offsetof(mm7::SpcItemsTxtItem, W1) == 8);
				uint8_t W2; // .9, 0x9
				static_assert(offsetof(mm7::SpcItemsTxtItem, W2) == 9);
				uint8_t miss; // .10, 0xA
				static_assert(offsetof(mm7::SpcItemsTxtItem, miss) == 10);
				uint8_t arm; // .11, 0xB
				static_assert(offsetof(mm7::SpcItemsTxtItem, arm) == 11);
				uint8_t shld; // .12, 0xC
				static_assert(offsetof(mm7::SpcItemsTxtItem, shld) == 12);
				uint8_t helm; // .13, 0xD
				static_assert(offsetof(mm7::SpcItemsTxtItem, helm) == 13);
				uint8_t belt; // .14, 0xE
				static_assert(offsetof(mm7::SpcItemsTxtItem, belt) == 14);
				uint8_t cape; // .15, 0xF
				static_assert(offsetof(mm7::SpcItemsTxtItem, cape) == 15);
				uint8_t gaunt; // .16, 0x10
				static_assert(offsetof(mm7::SpcItemsTxtItem, gaunt) == 16);
				uint8_t boot; // .17, 0x11
				static_assert(offsetof(mm7::SpcItemsTxtItem, boot) == 17);
				uint8_t ring; // .18, 0x12
				static_assert(offsetof(mm7::SpcItemsTxtItem, ring) == 18);
				uint8_t amul; // .19, 0x13
				static_assert(offsetof(mm7::SpcItemsTxtItem, amul) == 19);
			};
		};
		int32_t value; // .20, 0x14
		static_assert(offsetof(mm7::SpcItemsTxtItem, value) == 20);
		uint8_t lvl; // .24, 0x18
		static_assert(offsetof(mm7::SpcItemsTxtItem, lvl) == 24);
		SKIP(3);
	};
	static_assert(sizeof(mm7::SpcItemsTxtItem) == 0x1C, "Invalid \"mm7::SpcItemsTxtItem\" structure size");

	struct StdItemsTxtItem // size: 0x14
	{
		char* nameAdd; // .0, 0x0
		char* bonusStat; // .4, 0x4
		static_assert(offsetof(mm7::StdItemsTxtItem, bonusStat) == 4);
		union
		{
			std::array<uint8_t, 9> chanceForSlot; // .8, 0x8
			static_assert(offsetof(mm7::StdItemsTxtItem, chanceForSlot) == 8);
			struct
			{
				uint8_t arm; // .8, 0x8
				static_assert(offsetof(mm7::StdItemsTxtItem, arm) == 8);
				uint8_t shld; // .9, 0x9
				static_assert(offsetof(mm7::StdItemsTxtItem, shld) == 9);
				uint8_t helm; // .10, 0xA
				static_assert(offsetof(mm7::StdItemsTxtItem, helm) == 10);
				uint8_t belt; // .11, 0xB
				static_assert(offsetof(mm7::StdItemsTxtItem, belt) == 11);
				uint8_t cape; // .12, 0xC
				static_assert(offsetof(mm7::StdItemsTxtItem, cape) == 12);
				uint8_t gaunt; // .13, 0xD
				static_assert(offsetof(mm7::StdItemsTxtItem, gaunt) == 13);
				uint8_t boot; // .14, 0xE
				static_assert(offsetof(mm7::StdItemsTxtItem, boot) == 14);
				uint8_t ring; // .15, 0xF
				static_assert(offsetof(mm7::StdItemsTxtItem, ring) == 15);
				uint8_t amul; // .16, 0x10
				static_assert(offsetof(mm7::StdItemsTxtItem, amul) == 16);
			};
		};
		SKIP(3);
	};
	static_assert(sizeof(mm7::StdItemsTxtItem) == 0x14, "Invalid \"mm7::StdItemsTxtItem\" structure size");

	struct NPCProfTxtItem // size: 0x14
	{
		int32_t cost; // .0, 0x0
		char* benefit; // .4, 0x4
		static_assert(offsetof(mm7::NPCProfTxtItem, benefit) == 4);
		char* actionText; // .8, 0x8
		static_assert(offsetof(mm7::NPCProfTxtItem, actionText) == 8);
		char* joinText; // .12, 0xC
		static_assert(offsetof(mm7::NPCProfTxtItem, joinText) == 12);
		char* dismissText; // .16, 0x10
		static_assert(offsetof(mm7::NPCProfTxtItem, dismissText) == 16);
	};
	static_assert(sizeof(mm7::NPCProfTxtItem) == 0x14, "Invalid \"mm7::NPCProfTxtItem\" structure size");

	struct Events2DItem // size: 0x34
	{
		int16_t type; // .0, 0x0
		int16_t picture; // .2, 0x2
		static_assert(offsetof(mm7::Events2DItem, picture) == 2);
		char* name; // .4, 0x4
		static_assert(offsetof(mm7::Events2DItem, name) == 4);
		char* ownerName; // .8, 0x8
		static_assert(offsetof(mm7::Events2DItem, ownerName) == 8);
		char* enterText; // .12, 0xC
		static_assert(offsetof(mm7::Events2DItem, enterText) == 12);
		char* ownerTitle; // .16, 0x10
		static_assert(offsetof(mm7::Events2DItem, ownerTitle) == 16);
		int16_t pictureUnk; // .20, 0x14
		static_assert(offsetof(mm7::Events2DItem, pictureUnk) == 20);
		int16_t state; // .22, 0x16
		static_assert(offsetof(mm7::Events2DItem, state) == 22);
		int16_t rep; // .24, 0x18
		static_assert(offsetof(mm7::Events2DItem, rep) == 24);
		int16_t per; // .26, 0x1A
		static_assert(offsetof(mm7::Events2DItem, per) == 26);
		int16_t c; // .28, 0x1C
		static_assert(offsetof(mm7::Events2DItem, c) == 28);
		SKIP(2);
		float val; // .32, 0x20
		static_assert(offsetof(mm7::Events2DItem, val) == 32);
		float a; // .36, 0x24
		static_assert(offsetof(mm7::Events2DItem, a) == 36);
		int16_t openHour; // .40, 0x28
		static_assert(offsetof(mm7::Events2DItem, openHour) == 40);
		int16_t closeHour; // .42, 0x2A
		static_assert(offsetof(mm7::Events2DItem, closeHour) == 42);
		int16_t exitPic; // .44, 0x2C
		static_assert(offsetof(mm7::Events2DItem, exitPic) == 44);
		int16_t exitMap; // .46, 0x2E
		static_assert(offsetof(mm7::Events2DItem, exitMap) == 46);
		union
		{
			int16_t QBit; // .48, 0x30
			static_assert(offsetof(mm7::Events2DItem, QBit) == 48);
			int16_t questBitRestriction; // .48, 0x30
			static_assert(offsetof(mm7::Events2DItem, questBitRestriction) == 48);
		};
		SKIP(2);
	};
	static_assert(sizeof(mm7::Events2DItem) == 0x34, "Invalid \"mm7::Events2DItem\" structure size");

	struct MapStatsItem // size: 0x44
	{
		char* name; // .0, 0x0
		char* fileName; // .4, 0x4
		static_assert(offsetof(mm7::MapStatsItem, fileName) == 4);
		char* monster1Pic; // .8, 0x8
		static_assert(offsetof(mm7::MapStatsItem, monster1Pic) == 8);
		char* monster2Pic; // .12, 0xC
		static_assert(offsetof(mm7::MapStatsItem, monster2Pic) == 12);
		char* monster3Pic; // .16, 0x10
		static_assert(offsetof(mm7::MapStatsItem, monster3Pic) == 16);
		int32_t resetCount; // .20, 0x14
		static_assert(offsetof(mm7::MapStatsItem, resetCount) == 20);
		int32_t firstVisitDay; // .24, 0x18
		static_assert(offsetof(mm7::MapStatsItem, firstVisitDay) == 24);
		int32_t refillDays; // .28, 0x1C
		static_assert(offsetof(mm7::MapStatsItem, refillDays) == 28);
		int32_t alertDays; // .32, 0x20
		static_assert(offsetof(mm7::MapStatsItem, alertDays) == 32);
		int32_t stealPerm; // .36, 0x24
		static_assert(offsetof(mm7::MapStatsItem, stealPerm) == 36);
		int32_t per; // .40, 0x28
		static_assert(offsetof(mm7::MapStatsItem, per) == 40);
		SKIP(1);
		uint8_t lock; // .45, 0x2D
		static_assert(offsetof(mm7::MapStatsItem, lock) == 45);
		uint8_t trap; // .46, 0x2E
		static_assert(offsetof(mm7::MapStatsItem, trap) == 46);
		uint8_t tres; // .47, 0x2F
		static_assert(offsetof(mm7::MapStatsItem, tres) == 47);
		uint8_t encounterChance; // .48, 0x30
		static_assert(offsetof(mm7::MapStatsItem, encounterChance) == 48);
		uint8_t encounterChanceM1; // .49, 0x31
		static_assert(offsetof(mm7::MapStatsItem, encounterChanceM1) == 49);
		uint8_t encounterChanceM2; // .50, 0x32
		static_assert(offsetof(mm7::MapStatsItem, encounterChanceM2) == 50);
		uint8_t encounterChanceM3; // .51, 0x33
		static_assert(offsetof(mm7::MapStatsItem, encounterChanceM3) == 51);
		uint8_t mon1Dif; // .52, 0x34
		static_assert(offsetof(mm7::MapStatsItem, mon1Dif) == 52);
		uint8_t mon1Low; // .53, 0x35
		static_assert(offsetof(mm7::MapStatsItem, mon1Low) == 53);
		uint8_t mon1Hi; // .54, 0x36
		static_assert(offsetof(mm7::MapStatsItem, mon1Hi) == 54);
		uint8_t mon2Dif; // .55, 0x37
		static_assert(offsetof(mm7::MapStatsItem, mon2Dif) == 55);
		uint8_t mon2Low; // .56, 0x38
		static_assert(offsetof(mm7::MapStatsItem, mon2Low) == 56);
		uint8_t mon2Hi; // .57, 0x39
		static_assert(offsetof(mm7::MapStatsItem, mon2Hi) == 57);
		uint8_t mon3Dif; // .58, 0x3A
		static_assert(offsetof(mm7::MapStatsItem, mon3Dif) == 58);
		uint8_t mon3Low; // .59, 0x3B
		static_assert(offsetof(mm7::MapStatsItem, mon3Low) == 59);
		uint8_t mon3Hi; // .60, 0x3C
		static_assert(offsetof(mm7::MapStatsItem, mon3Hi) == 60);
		SKIP(3);
		uint8_t redbookTrack; // .64, 0x40
		static_assert(offsetof(mm7::MapStatsItem, redbookTrack) == 64);
		uint8_t eaxEnvironments; // .65, 0x41
		static_assert(offsetof(mm7::MapStatsItem, eaxEnvironments) == 65);
		SKIP(2);
	};
	static_assert(sizeof(mm7::MapStatsItem) == 0x44, "Invalid \"mm7::MapStatsItem\" structure size");

	struct BaseBonus // size: 0x4
	{
		int16_t base; // .0, 0x0
		int16_t bonus; // .2, 0x2
		static_assert(offsetof(mm7::BaseBonus, bonus) == 2);
	};
	static_assert(sizeof(mm7::BaseBonus) == 0x4, "Invalid \"mm7::BaseBonus\" structure size");

	struct LloydBeaconSlot // size: 0x1C
	{
		int64_t expireTime; // .0, 0x0
		union
		{
			std::array<int32_t, 3> pos; // .8, 0x8
			static_assert(offsetof(mm7::LloydBeaconSlot, pos) == 8);
			struct
			{
				int32_t x; // .8, 0x8
				static_assert(offsetof(mm7::LloydBeaconSlot, x) == 8);
				int32_t y; // .12, 0xC
				static_assert(offsetof(mm7::LloydBeaconSlot, y) == 12);
				int32_t z; // .16, 0x10
				static_assert(offsetof(mm7::LloydBeaconSlot, z) == 16);
			};
		};
		int16_t direction; // .20, 0x14
		static_assert(offsetof(mm7::LloydBeaconSlot, direction) == 20);
		int16_t lookAngle; // .22, 0x16
		static_assert(offsetof(mm7::LloydBeaconSlot, lookAngle) == 22);
		int16_t active; // .24, 0x18
		static_assert(offsetof(mm7::LloydBeaconSlot, active) == 24);
		union
		{
			int16_t mapIndex; // .26, 0x1A
			static_assert(offsetof(mm7::LloydBeaconSlot, mapIndex) == 26);
			std::array<uint8_t, 2> map; // Unknown type | .0, 0x0
		};
	};
	static_assert(sizeof(mm7::LloydBeaconSlot) == 0x1C, "Invalid \"mm7::LloydBeaconSlot\" structure size");

	struct ActionItem // size: 0xC
	{
		int32_t action; // .0, 0x0
		int32_t param; // .4, 0x4
		static_assert(offsetof(mm7::ActionItem, param) == 4);
		int32_t param2; // .8, 0x8
		static_assert(offsetof(mm7::ActionItem, param2) == 8);
	};
	static_assert(sizeof(mm7::ActionItem) == 0xC, "Invalid \"mm7::ActionItem\" structure size");

	struct ObjListItem // size: 0x38
	{
		std::array<char, 32> name; // requires null terminator | .0, 0x0
		int16_t id; // .32, 0x20
		static_assert(offsetof(mm7::ObjListItem, id) == 32);
		int16_t radius; // .34, 0x22
		static_assert(offsetof(mm7::ObjListItem, radius) == 34);
		int16_t height; // .36, 0x24
		static_assert(offsetof(mm7::ObjListItem, height) == 36);
		union
		{
			uint16_t bits; // .38, 0x26
			static_assert(offsetof(mm7::ObjListItem, bits) == 38);
			struct
			{
				bool invisible : 1; // .38, 0x26
				bool untouchable : 1; // .38, 0x26
				bool temporary : 1; // .38, 0x26
				bool lifetimeInSFT : 1; // .38, 0x26
				bool noPickup : 1; // .38, 0x26
				bool noGravity : 1; // .38, 0x26
				bool interceptAction : 1; // .38, 0x26
				bool bounce : 1; // .38, 0x26
				bool trailParticles : 1; // .39, 0x27
				bool trailFire : 1; // .39, 0x27
				bool trailLine : 1; // .39, 0x27
			};
		};
		union
		{
			std::array<uint8_t, 2> SFTGroup; // Unknown type | .0, 0x0
			int16_t SFTIndex; // .40, 0x28
			static_assert(offsetof(mm7::ObjListItem, SFTIndex) == 40);
		};
		int16_t lifeTime; // .42, 0x2A
		static_assert(offsetof(mm7::ObjListItem, lifeTime) == 42);
		uint32_t loadedParticlesColor; // .44, 0x2C
		static_assert(offsetof(mm7::ObjListItem, loadedParticlesColor) == 44);
		uint16_t speed; // .48, 0x30
		static_assert(offsetof(mm7::ObjListItem, speed) == 48);
		union
		{
			std::array<uint8_t, 4> particlesColor; // .50, 0x32
			static_assert(offsetof(mm7::ObjListItem, particlesColor) == 50);
			struct
			{
				uint8_t particleR; // .50, 0x32
				static_assert(offsetof(mm7::ObjListItem, particleR) == 50);
				uint8_t particleG; // .51, 0x33
				static_assert(offsetof(mm7::ObjListItem, particleG) == 51);
				uint8_t particleB; // .52, 0x34
				static_assert(offsetof(mm7::ObjListItem, particleB) == 52);
				uint8_t particleA; // .53, 0x35
				static_assert(offsetof(mm7::ObjListItem, particleA) == 53);
			};
		};
		SKIP(2);
	};
	static_assert(sizeof(mm7::ObjListItem) == 0x38, "Invalid \"mm7::ObjListItem\" structure size");

	struct MissileSetup // size: 0x1
	{
		bool alwaysShowSprite : 1; // .0, 0x0
		bool hideSpecialDisplay : 1; // .0, 0x0
		bool autoCollision : 1; // .0, 0x0
	};
	static_assert(sizeof(mm7::MissileSetup) == 0x1, "Invalid \"mm7::MissileSetup\" structure size");

	struct ProgressBar // size: 0x10
	{
		SKIP(10);
		uint8_t max; // .10, 0xA
		static_assert(offsetof(mm7::ProgressBar, max) == 10);
		uint8_t current; // .11, 0xB
		static_assert(offsetof(mm7::ProgressBar, current) == 11);
		int32_t kind; // .12, 0xC
		static_assert(offsetof(mm7::ProgressBar, kind) == 12);
	};
	static_assert(sizeof(mm7::ProgressBar) == 0x10, "Invalid \"mm7::ProgressBar\" structure size");

	struct TownPortalTownInfo // size: 0x14
	{
		union
		{
			std::array<int32_t, 3> pos; // .0, 0x0
			struct
			{
				int32_t x; // .0, 0x0
				int32_t y; // .4, 0x4
				static_assert(offsetof(mm7::TownPortalTownInfo, y) == 4);
				int32_t z; // .8, 0x8
				static_assert(offsetof(mm7::TownPortalTownInfo, z) == 8);
			};
		};
		int16_t direction; // .12, 0xC
		static_assert(offsetof(mm7::TownPortalTownInfo, direction) == 12);
		int16_t lookAngle; // .14, 0xE
		static_assert(offsetof(mm7::TownPortalTownInfo, lookAngle) == 14);
		union
		{
			int16_t mapStatsIndex; // .16, 0x10
			static_assert(offsetof(mm7::TownPortalTownInfo, mapStatsIndex) == 16);
			std::array<uint8_t, 2> map; // Unknown type | .0, 0x0
		};
		SKIP(2);
	};
	static_assert(sizeof(mm7::TownPortalTownInfo) == 0x14, "Invalid \"mm7::TownPortalTownInfo\" structure size");

	struct ItemsTxtItem // size: 0x30
	{
		char* picture; // .0, 0x0
		char* name; // .4, 0x4
		static_assert(offsetof(mm7::ItemsTxtItem, name) == 4);
		char* notIdentifiedName; // .8, 0x8
		static_assert(offsetof(mm7::ItemsTxtItem, notIdentifiedName) == 8);
		char* notes; // .12, 0xC
		static_assert(offsetof(mm7::ItemsTxtItem, notes) == 12);
		int32_t value; // .16, 0x10
		static_assert(offsetof(mm7::ItemsTxtItem, value) == 16);
		int16_t spriteIndex; // .20, 0x14
		static_assert(offsetof(mm7::ItemsTxtItem, spriteIndex) == 20);
		SKIP(2);
		int16_t equipX; // .24, 0x18
		static_assert(offsetof(mm7::ItemsTxtItem, equipX) == 24);
		int16_t equipY; // .26, 0x1A
		static_assert(offsetof(mm7::ItemsTxtItem, equipY) == 26);
		uint8_t equipStat; // .28, 0x1C
		static_assert(offsetof(mm7::ItemsTxtItem, equipStat) == 28);
		uint8_t skill; // .29, 0x1D
		static_assert(offsetof(mm7::ItemsTxtItem, skill) == 29);
		uint8_t mod1DiceCount; // .30, 0x1E
		static_assert(offsetof(mm7::ItemsTxtItem, mod1DiceCount) == 30);
		uint8_t mod1DiceSides; // .31, 0x1F
		static_assert(offsetof(mm7::ItemsTxtItem, mod1DiceSides) == 31);
		uint8_t mod2; // .32, 0x20
		static_assert(offsetof(mm7::ItemsTxtItem, mod2) == 32);
		uint8_t material; // .33, 0x21
		static_assert(offsetof(mm7::ItemsTxtItem, material) == 33);
		uint8_t bonus2; // .34, 0x22
		static_assert(offsetof(mm7::ItemsTxtItem, bonus2) == 34);
		uint8_t bonus; // .35, 0x23
		static_assert(offsetof(mm7::ItemsTxtItem, bonus) == 35);
		uint8_t bonusStrength; // .36, 0x24
		static_assert(offsetof(mm7::ItemsTxtItem, bonusStrength) == 36);
		SKIP(3);
		std::array<uint8_t, 6> chanceByLevel; // MMExt: 1..6, here 0..5 | .40, 0x28
		static_assert(offsetof(mm7::ItemsTxtItem, chanceByLevel) == 40);
		int8_t idRepSt; // .46, 0x2E
		static_assert(offsetof(mm7::ItemsTxtItem, idRepSt) == 46);
		SKIP(1);
	};
	static_assert(sizeof(mm7::ItemsTxtItem) == 0x30, "Invalid \"mm7::ItemsTxtItem\" structure size");

	struct Weather // size: 0x6BDEC8
	{
		SKIP(7069344);
		int32_t shade; // .7069344, 0x6BDEA0
		static_assert(offsetof(mm7::Weather, shade) == 7069344);
		uint32_t snow; // 4-byte boolean | .7069348, 0x6BDEA4
		static_assert(offsetof(mm7::Weather, snow) == 7069348);
		SKIP(8);
		// uint8_t* fog; // real size is 0 | Unknown type | .0, 0x0
		SKIP(16);
		std::array<uint8_t, 4> fogRange1; // Unknown type | .0, 0x0
		std::array<uint8_t, 4> fogRange2; // Unknown type | .0, 0x0
	};
	static_assert(sizeof(mm7::Weather) == 0x6BDEC8, "Invalid \"mm7::Weather\" structure size");

	struct NPC // size: 0x4C
	{
		union
		{
			uint32_t exist; // 4-byte boolean | .0, 0x0
			char* name; // .0, 0x0
		};
		int32_t pic; // .4, 0x4
		static_assert(offsetof(mm7::NPC, pic) == 4);
		union
		{
			uint32_t bits; // .8, 0x8
			static_assert(offsetof(mm7::NPC, bits) == 8);
			struct
			{
				bool bribedBefore : 1; // .8, 0x8
				bool talkedBefore : 1; // .8, 0x8
				bool threatenedBefore : 1; // .8, 0x8
				SKIPBITS(4);
				bool hired : 1; // .8, 0x8
			};
		};
		int32_t fame; // .12, 0xC
		static_assert(offsetof(mm7::NPC, fame) == 12);
		int32_t rep; // .16, 0x10
		static_assert(offsetof(mm7::NPC, rep) == 16);
		int32_t house; // .20, 0x14
		static_assert(offsetof(mm7::NPC, house) == 20);
		int32_t profession; // .24, 0x18
		static_assert(offsetof(mm7::NPC, profession) == 24);
		int32_t greet; // .28, 0x1C
		static_assert(offsetof(mm7::NPC, greet) == 28);
		int32_t joins; // .32, 0x20
		static_assert(offsetof(mm7::NPC, joins) == 32);
		int32_t tellsNews; // .36, 0x24
		static_assert(offsetof(mm7::NPC, tellsNews) == 36);
		union
		{
			std::array<int32_t, 6> events; // .40, 0x28
			static_assert(offsetof(mm7::NPC, events) == 40);
			struct
			{
				int32_t eventA; // .40, 0x28
				static_assert(offsetof(mm7::NPC, eventA) == 40);
				int32_t eventB; // .44, 0x2C
				static_assert(offsetof(mm7::NPC, eventB) == 44);
				int32_t eventC; // .48, 0x30
				static_assert(offsetof(mm7::NPC, eventC) == 48);
				int32_t eventD; // .52, 0x34
				static_assert(offsetof(mm7::NPC, eventD) == 52);
				int32_t eventE; // .56, 0x38
				static_assert(offsetof(mm7::NPC, eventE) == 56);
				int32_t eventF; // .60, 0x3C
				static_assert(offsetof(mm7::NPC, eventF) == 60);
			};
		};
		int32_t sex; // .64, 0x40
		static_assert(offsetof(mm7::NPC, sex) == 64);
		int32_t usedSpell; // .68, 0x44
		static_assert(offsetof(mm7::NPC, usedSpell) == 68);
		int32_t newsTopic; // .72, 0x48
		static_assert(offsetof(mm7::NPC, newsTopic) == 72);
	};
	static_assert(sizeof(mm7::NPC) == 0x4C, "Invalid \"mm7::NPC\" structure size");

	struct ArcomageAction // size: 0x9
	{
		std::array<int8_t, 3> income; // .0, 0x0
		std::array<int8_t, 3> res; // .3, 0x3
		static_assert(offsetof(mm7::ArcomageAction, res) == 3);
		int8_t damage; // .6, 0x6
		static_assert(offsetof(mm7::ArcomageAction, damage) == 6);
		int8_t wall; // .7, 0x7
		static_assert(offsetof(mm7::ArcomageAction, wall) == 7);
		int8_t tower; // .8, 0x8
		static_assert(offsetof(mm7::ArcomageAction, tower) == 8);
	};
	static_assert(sizeof(mm7::ArcomageAction) == 0x9, "Invalid \"mm7::ArcomageAction\" structure size");

	struct ArcomageActions // size: 0x1D
	{
		bool playAgain; // .0, 0x0
		int8_t discardCards; // .1, 0x1
		static_assert(offsetof(mm7::ArcomageActions, discardCards) == 1);
		mm7::ArcomageAction me; // .2, 0x2
		static_assert(offsetof(mm7::ArcomageActions, me) == 2);
		mm7::ArcomageAction enemy; // .11, 0xB
		static_assert(offsetof(mm7::ArcomageActions, enemy) == 11);
		mm7::ArcomageAction all; // .20, 0x14
		static_assert(offsetof(mm7::ArcomageActions, all) == 20);
	};
	static_assert(sizeof(mm7::ArcomageActions) == 0x1D, "Invalid \"mm7::ArcomageActions\" structure size");

	struct ArcomageCard // size: 0x6C
	{
		std::array<char, 32> name; // requires null terminator | .0, 0x0
		int32_t sprite; // .32, 0x20
		static_assert(offsetof(mm7::ArcomageCard, sprite) == 32);
		int8_t costKind; // .36, 0x24
		static_assert(offsetof(mm7::ArcomageCard, costKind) == 36);
		std::array<int8_t, 3> costIncome; // .37, 0x25
		static_assert(offsetof(mm7::ArcomageCard, costIncome) == 37);
		std::array<int8_t, 3> costRes; // .40, 0x28
		static_assert(offsetof(mm7::ArcomageCard, costRes) == 40);
		bool discardable; // .43, 0x2B
		static_assert(offsetof(mm7::ArcomageCard, discardable) == 43);
		int32_t if_; // .44, 0x2C
		static_assert(offsetof(mm7::ArcomageCard, if_) == 44);
		mm7::ArcomageActions then; // .48, 0x30
		static_assert(offsetof(mm7::ArcomageCard, then) == 48);
		mm7::ArcomageActions else_; // .77, 0x4D
		static_assert(offsetof(mm7::ArcomageCard, else_) == 77);
		SKIP(2);
	};
	static_assert(sizeof(mm7::ArcomageCard) == 0x6C, "Invalid \"mm7::ArcomageCard\" structure size");

	struct ArcomagePlayer // size: 0xBC
	{
		std::array<char, 32> name; // requires null terminator | .0, 0x0
		bool human; // .32, 0x20
		static_assert(offsetof(mm7::ArcomagePlayer, human) == 32);
		SKIP(3);
		int32_t tower; // .36, 0x24
		static_assert(offsetof(mm7::ArcomagePlayer, tower) == 36);
		int32_t wall; // .40, 0x28
		static_assert(offsetof(mm7::ArcomagePlayer, wall) == 40);
		std::array<std::array<uint8_t, 4>, 3> income; // Unknown type | .0, 0x0
		std::array<int32_t, 3> res; // .56, 0x38
		static_assert(offsetof(mm7::ArcomagePlayer, res) == 56);
		std::array<int32_t, 10> cards; // .68, 0x44
		static_assert(offsetof(mm7::ArcomagePlayer, cards) == 68);
		std::array<std::array<int32_t, 2>, 10> unk; // .108, 0x6C
		static_assert(offsetof(mm7::ArcomagePlayer, unk) == 108);
	};
	static_assert(sizeof(mm7::ArcomagePlayer) == 0xBC, "Invalid \"mm7::ArcomagePlayer\" structure size");

	struct Arcomage // size: 0x505710
	{
		SKIP(5108644);
		int32_t AI; // .5108644, 0x4DF3A4
		static_assert(offsetof(mm7::Arcomage, AI) == 5108644);
		std::array<mm7::ArcomageCard, 87> cardKinds; // .5108648, 0x4DF3A8
		static_assert(offsetof(mm7::Arcomage, cardKinds) == 5108648);
		SKIP(4);
		int32_t startingTower; // .5118048, 0x4E1860
		static_assert(offsetof(mm7::Arcomage, startingTower) == 5118048);
		int32_t startingWall; // .5118052, 0x4E1864
		static_assert(offsetof(mm7::Arcomage, startingWall) == 5118052);
		union
		{
			std::array<std::array<uint8_t, 4>, 3> startingIncome; // Unknown type | .0, 0x0
			struct
			{
				std::array<uint8_t, 4> startingIncomeBricks; // Unknown type | .0, 0x0
				std::array<uint8_t, 4> startingIncomeGems; // Unknown type | .0, 0x0
				std::array<uint8_t, 4> startingIncomeBeasts; // Unknown type | .0, 0x0
			};
		};
		std::array<uint8_t, 4> cardsCount; // Unknown type | .0, 0x0
		std::array<int32_t, 3> minIncome; // .5118072, 0x4E1878
		static_assert(offsetof(mm7::Arcomage, minIncome) == 5118072);
		int32_t towerToWin; // .5118084, 0x4E1884
		static_assert(offsetof(mm7::Arcomage, towerToWin) == 5118084);
		int32_t resToWin; // .5118088, 0x4E1888
		static_assert(offsetof(mm7::Arcomage, resToWin) == 5118088);
		SKIP(146248);
		std::array<int32_t, 108> deck; // .5264340, 0x5053D4
		static_assert(offsetof(mm7::Arcomage, deck) == 5264340);
		SKIP(4);
		std::array<mm7::ArcomagePlayer, 2> players; // .5264776, 0x505588
		static_assert(offsetof(mm7::Arcomage, players) == 5264776);
		SKIP(4);
		union
		{
			std::array<int32_t, 3> startingRes; // .5265156, 0x505704
			static_assert(offsetof(mm7::Arcomage, startingRes) == 5265156);
			struct
			{
				int32_t startingBricks; // .5265156, 0x505704
				static_assert(offsetof(mm7::Arcomage, startingBricks) == 5265156);
				int32_t startingGems; // .5265160, 0x505708
				static_assert(offsetof(mm7::Arcomage, startingGems) == 5265160);
				int32_t startingBeasts; // .5265164, 0x50570C
				static_assert(offsetof(mm7::Arcomage, startingBeasts) == 5265164);
			};
		};
	};
	static_assert(sizeof(mm7::Arcomage) == 0x505710, "Invalid \"mm7::Arcomage\" structure size");

	struct MoveToMap // size: 0x1C
	{
		union
		{
			std::array<int32_t, 3> pos; // .0, 0x0
			struct
			{
				int32_t x; // .0, 0x0
				int32_t y; // .4, 0x4
				static_assert(offsetof(mm7::MoveToMap, y) == 4);
				int32_t z; // .8, 0x8
				static_assert(offsetof(mm7::MoveToMap, z) == 8);
			};
		};
		int32_t direction; // .12, 0xC
		static_assert(offsetof(mm7::MoveToMap, direction) == 12);
		int32_t lookAngle; // .16, 0x10
		static_assert(offsetof(mm7::MoveToMap, lookAngle) == 16);
		int32_t speedZ; // .20, 0x14
		static_assert(offsetof(mm7::MoveToMap, speedZ) == 20);
		uint32_t defined; // 4-byte boolean | .24, 0x18
		static_assert(offsetof(mm7::MoveToMap, defined) == 24);
	};
	static_assert(sizeof(mm7::MoveToMap) == 0x1C, "Invalid \"mm7::MoveToMap\" structure size");

	struct PFTItem // size: 0xA
	{
		uint16_t groupId; // .0, 0x0
		uint16_t frameIndex; // .2, 0x2
		static_assert(offsetof(mm7::PFTItem, frameIndex) == 2);
		uint16_t time; // .4, 0x4
		static_assert(offsetof(mm7::PFTItem, time) == 4);
		uint16_t totalTime; // .6, 0x6
		static_assert(offsetof(mm7::PFTItem, totalTime) == 6);
		union
		{
			uint16_t bits; // .8, 0x8
			static_assert(offsetof(mm7::PFTItem, bits) == 8);
			struct
			{
				bool notGroupEnd : 1; // .8, 0x8
				SKIPBITS(1);
				bool groupStart : 1; // .8, 0x8
			};
		};
	};
	static_assert(sizeof(mm7::PFTItem) == 0xA, "Invalid \"mm7::PFTItem\" structure size");

	struct IFTItem // size: 0x20
	{
		std::array<char, 12> groupName; // requires null terminator | .0, 0x0
		std::array<char, 12> iconName; // requires null terminator | .0, 0x0
		uint16_t time; // .24, 0x18
		static_assert(offsetof(mm7::IFTItem, time) == 24);
		uint16_t totalTime; // .26, 0x1A
		static_assert(offsetof(mm7::IFTItem, totalTime) == 26);
		union
		{
			uint16_t bits; // .28, 0x1C
			static_assert(offsetof(mm7::IFTItem, bits) == 28);
			struct
			{
				bool notGroupEnd : 1; // .28, 0x1C
				SKIPBITS(1);
				bool groupStart : 1; // .28, 0x1C
			};
		};
		uint16_t iconIndex; // .30, 0x1E
		static_assert(offsetof(mm7::IFTItem, iconIndex) == 30);
	};
	static_assert(sizeof(mm7::IFTItem) == 0x20, "Invalid \"mm7::IFTItem\" structure size");

	struct TFTItem // size: 0x14
	{
		std::array<char, 12> name; // requires null terminator | .0, 0x0
		int16_t index; // .12, 0xC
		static_assert(offsetof(mm7::TFTItem, index) == 12);
		int16_t time; // .14, 0xE
		static_assert(offsetof(mm7::TFTItem, time) == 14);
		int16_t totalTime; // .16, 0x10
		static_assert(offsetof(mm7::TFTItem, totalTime) == 16);
		union
		{
			uint16_t bits; // .18, 0x12
			static_assert(offsetof(mm7::TFTItem, bits) == 18);
			struct
			{
				bool notGroupEnd : 1; // .18, 0x12
				bool groupStart : 1; // .18, 0x12
			};
		};
	};
	static_assert(sizeof(mm7::TFTItem) == 0x14, "Invalid \"mm7::TFTItem\" structure size");

	struct DChestItem // size: 0x24
	{
		std::array<char, 32> name; // requires null terminator | .0, 0x0
		uint8_t width; // .32, 0x20
		static_assert(offsetof(mm7::DChestItem, width) == 32);
		uint8_t height; // .33, 0x21
		static_assert(offsetof(mm7::DChestItem, height) == 33);
		int16_t imageIndex; // .34, 0x22
		static_assert(offsetof(mm7::DChestItem, imageIndex) == 34);
	};
	static_assert(sizeof(mm7::DChestItem) == 0x24, "Invalid \"mm7::DChestItem\" structure size");

	struct OverlayItem // size: 0x8
	{
		int16_t id; // .0, 0x0
		int16_t type; // .2, 0x2
		static_assert(offsetof(mm7::OverlayItem, type) == 2);
		union
		{
			std::array<uint8_t, 2> SFTGroup; // Unknown type | .0, 0x0
			int16_t SFTIndex; // .4, 0x4
			static_assert(offsetof(mm7::OverlayItem, SFTIndex) == 4);
		};
		SKIP(2);
	};
	static_assert(sizeof(mm7::OverlayItem) == 0x8, "Invalid \"mm7::OverlayItem\" structure size");

	struct SpellsTxtItem // size: 0x24
	{
		char* name; // .0, 0x0
		char* shortName; // .4, 0x4
		static_assert(offsetof(mm7::SpellsTxtItem, shortName) == 4);
		char* description; // .8, 0x8
		static_assert(offsetof(mm7::SpellsTxtItem, description) == 8);
		char* normal; // .12, 0xC
		static_assert(offsetof(mm7::SpellsTxtItem, normal) == 12);
		char* expert; // .16, 0x10
		static_assert(offsetof(mm7::SpellsTxtItem, expert) == 16);
		char* master; // .20, 0x14
		static_assert(offsetof(mm7::SpellsTxtItem, master) == 20);
		union
		{
			char* grandMaster; // .24, 0x18
			static_assert(offsetof(mm7::SpellsTxtItem, grandMaster) == 24);
			char* GM; // .24, 0x18
			static_assert(offsetof(mm7::SpellsTxtItem, GM) == 24);
		};
		uint8_t damageType; // .28, 0x1C
		static_assert(offsetof(mm7::SpellsTxtItem, damageType) == 28);
		union
		{
			std::array<uint8_t, 4> spellPoints; // MMExt: 1..4, here 0..3 | .29, 0x1D
			static_assert(offsetof(mm7::SpellsTxtItem, spellPoints) == 29);
			struct
			{
				uint8_t spellPointsNormal; // .29, 0x1D
				static_assert(offsetof(mm7::SpellsTxtItem, spellPointsNormal) == 29);
				uint8_t spellPointsExpert; // .30, 0x1E
				static_assert(offsetof(mm7::SpellsTxtItem, spellPointsExpert) == 30);
				uint8_t spellPointsMaster; // .31, 0x1F
				static_assert(offsetof(mm7::SpellsTxtItem, spellPointsMaster) == 31);
				uint8_t spellPointsGM; // .32, 0x20
				static_assert(offsetof(mm7::SpellsTxtItem, spellPointsGM) == 32);
			};
		};
		SKIP(3);
	};
	static_assert(sizeof(mm7::SpellsTxtItem) == 0x24, "Invalid \"mm7::SpellsTxtItem\" structure size");

	struct MonListItem // size: 0x98
	{
		int16_t height; // .0, 0x0
		int16_t radius; // .2, 0x2
		static_assert(offsetof(mm7::MonListItem, radius) == 2);
		int16_t velocity; // .4, 0x4
		static_assert(offsetof(mm7::MonListItem, velocity) == 4);
		int16_t radius2; // .6, 0x6
		static_assert(offsetof(mm7::MonListItem, radius2) == 6);
		union
		{
			int32_t tint; // .8, 0x8
			static_assert(offsetof(mm7::MonListItem, tint) == 8);
			struct
			{
				uint8_t tintB; // .8, 0x8
				static_assert(offsetof(mm7::MonListItem, tintB) == 8);
				uint8_t tintG; // .9, 0x9
				static_assert(offsetof(mm7::MonListItem, tintG) == 9);
				uint8_t tintR; // .10, 0xA
				static_assert(offsetof(mm7::MonListItem, tintR) == 10);
				uint8_t tintA; // .11, 0xB
				static_assert(offsetof(mm7::MonListItem, tintA) == 11);
			};
		};
		union
		{
			std::array<int16_t, 4> sounds; // .12, 0xC
			static_assert(offsetof(mm7::MonListItem, sounds) == 12);
			struct
			{
				int16_t soundAttack; // .12, 0xC
				static_assert(offsetof(mm7::MonListItem, soundAttack) == 12);
				int16_t soundDie; // .14, 0xE
				static_assert(offsetof(mm7::MonListItem, soundDie) == 14);
				int16_t soundGetHit; // .16, 0x10
				static_assert(offsetof(mm7::MonListItem, soundGetHit) == 16);
				int16_t soundFidget; // .18, 0x12
				static_assert(offsetof(mm7::MonListItem, soundFidget) == 18);
			};
		};
		std::array<char, 32> name; // requires null terminator | .0, 0x0
		union
		{
			std::array<std::array<char, 10>, 10> frameNames; // requires null terminator | .0, 0x0
			struct
			{
				std::array<char, 10> framesStand; // requires null terminator | .0, 0x0
				std::array<char, 10> framesWalk; // requires null terminator | .0, 0x0
				std::array<char, 10> framesAttack; // requires null terminator | .0, 0x0
				std::array<char, 10> framesShoot; // requires null terminator | .0, 0x0
				std::array<char, 10> framesStun; // requires null terminator | .0, 0x0
				std::array<char, 10> framesDie; // requires null terminator | .0, 0x0
				std::array<char, 10> framesDead; // requires null terminator | .0, 0x0
				std::array<char, 10> framesFidget; // requires null terminator | .0, 0x0
			};
		};
	};
	static_assert(sizeof(mm7::MonListItem) == 0x98, "Invalid \"mm7::MonListItem\" structure size");

	struct SpellInfo // size: 0x14
	{
		union
		{
			std::array<int16_t, 4> spellPoints; // MMExt: 1..4, here 0..3 | .0, 0x0
			struct
			{
				int16_t spellPointsNormal; // .0, 0x0
				int16_t spellPointsExpert; // .2, 0x2
				static_assert(offsetof(mm7::SpellInfo, spellPointsExpert) == 2);
				int16_t spellPointsMaster; // .4, 0x4
				static_assert(offsetof(mm7::SpellInfo, spellPointsMaster) == 4);
				int16_t spellPointsGM; // .6, 0x6
				static_assert(offsetof(mm7::SpellInfo, spellPointsGM) == 6);
			};
		};
		union
		{
			std::array<int16_t, 4> delay; // MMExt: 1..4, here 0..3 | .8, 0x8
			static_assert(offsetof(mm7::SpellInfo, delay) == 8);
			struct
			{
				int16_t delayNormal; // .8, 0x8
				static_assert(offsetof(mm7::SpellInfo, delayNormal) == 8);
				int16_t delayExpert; // .10, 0xA
				static_assert(offsetof(mm7::SpellInfo, delayExpert) == 10);
				int16_t delayMaster; // .12, 0xC
				static_assert(offsetof(mm7::SpellInfo, delayMaster) == 12);
				int16_t delayGM; // .14, 0xE
				static_assert(offsetof(mm7::SpellInfo, delayGM) == 14);
			};
		};
		uint8_t damageAdd; // .16, 0x10
		static_assert(offsetof(mm7::SpellInfo, damageAdd) == 16);
		uint8_t damageDiceSides; // .17, 0x11
		static_assert(offsetof(mm7::SpellInfo, damageDiceSides) == 17);
		union
		{
			uint16_t bits; // .18, 0x12
			static_assert(offsetof(mm7::SpellInfo, bits) == 18);
			struct
			{
				bool castByMonster : 1; // .18, 0x12
				bool castByEvent : 1; // .18, 0x12
				bool causeDamage : 1; // .18, 0x12
				bool specialDamage : 1; // .18, 0x12
			};
		};
	};
	static_assert(sizeof(mm7::SpellInfo) == 0x14, "Invalid \"mm7::SpellInfo\" structure size");

	struct LodSpriteD3D // size: 0x28
	{
		const char* name; // .0, 0x0
		int32_t palette; // .4, 0x4
		static_assert(offsetof(mm7::LodSpriteD3D, palette) == 4);
		uint32_t surface; // .8, 0x8
		static_assert(offsetof(mm7::LodSpriteD3D, surface) == 8);
		uint32_t texture; // .12, 0xC
		static_assert(offsetof(mm7::LodSpriteD3D, texture) == 12);
		int32_t areaX; // .16, 0x10
		static_assert(offsetof(mm7::LodSpriteD3D, areaX) == 16);
		int32_t areaY; // .20, 0x14
		static_assert(offsetof(mm7::LodSpriteD3D, areaY) == 20);
		int32_t bufferWidth; // .24, 0x18
		static_assert(offsetof(mm7::LodSpriteD3D, bufferWidth) == 24);
		int32_t bufferHeight; // .28, 0x1C
		static_assert(offsetof(mm7::LodSpriteD3D, bufferHeight) == 28);
		int32_t areaWidth; // .32, 0x20
		static_assert(offsetof(mm7::LodSpriteD3D, areaWidth) == 32);
		int32_t areaHeight; // .36, 0x24
		static_assert(offsetof(mm7::LodSpriteD3D, areaHeight) == 36);
	};
	static_assert(sizeof(mm7::LodSpriteD3D) == 0x28, "Invalid \"mm7::LodSpriteD3D\" structure size");

	struct LodSpriteLine // size: 0x8
	{
		int16_t l; // .0, 0x0
		int16_t r; // .2, 0x2
		static_assert(offsetof(mm7::LodSpriteLine, r) == 2);
		uint8_t* pos; // .4, 0x4
		static_assert(offsetof(mm7::LodSpriteLine, pos) == 4);
	};
	static_assert(sizeof(mm7::LodSpriteLine) == 0x8, "Invalid \"mm7::LodSpriteLine\" structure size");

	struct LodSprite // size: 0x28
	{
		std::array<char, 12> name; // requires null terminator | .0, 0x0
		int32_t dataSize; // .12, 0xC
		static_assert(offsetof(mm7::LodSprite, dataSize) == 12);
		int16_t width; // .16, 0x10
		static_assert(offsetof(mm7::LodSprite, width) == 16);
		union
		{
			uint32_t lines_size; // .18, 0x12
			static_assert(offsetof(mm7::LodSprite, lines_size) == 18);
			struct
			{
				int16_t height; // .18, 0x12
				static_assert(offsetof(mm7::LodSprite, height) == 18);
				int16_t palette; // .20, 0x14
				static_assert(offsetof(mm7::LodSprite, palette) == 20);
			};
		};
		SKIP(2);
		int16_t YSkip; // .24, 0x18
		static_assert(offsetof(mm7::LodSprite, YSkip) == 24);
		SKIP(2);
		int32_t unpackedSize; // .28, 0x1C
		static_assert(offsetof(mm7::LodSprite, unpackedSize) == 28);
		mm7::LodSpriteLine* lines; // size offset is 0x12 | .32, 0x20
		static_assert(offsetof(mm7::LodSprite, lines) == 32);
		uint32_t buffer; // .36, 0x24
		static_assert(offsetof(mm7::LodSprite, buffer) == 36);
	};
	static_assert(sizeof(mm7::LodSprite) == 0x28, "Invalid \"mm7::LodSprite\" structure size");

	struct MonsterKind // size: 0x8
	{
		bool undead; // .0, 0x0
		bool demon; // .1, 0x1
		static_assert(offsetof(mm7::MonsterKind, demon) == 1);
		bool dragon; // .2, 0x2
		static_assert(offsetof(mm7::MonsterKind, dragon) == 2);
		bool elf; // .3, 0x3
		static_assert(offsetof(mm7::MonsterKind, elf) == 3);
		bool swimmer; // .4, 0x4
		static_assert(offsetof(mm7::MonsterKind, swimmer) == 4);
		bool immobile; // .5, 0x5
		static_assert(offsetof(mm7::MonsterKind, immobile) == 5);
		bool titan; // .6, 0x6
		static_assert(offsetof(mm7::MonsterKind, titan) == 6);
		bool noArena; // .7, 0x7
		static_assert(offsetof(mm7::MonsterKind, noArena) == 7);
	};
	static_assert(sizeof(mm7::MonsterKind) == 0x8, "Invalid \"mm7::MonsterKind\" structure size");

	struct FacetData // size: 0x24
	{
		SKIP(12);
		int16_t facetIndex; // .12, 0xC
		static_assert(offsetof(mm7::FacetData, facetIndex) == 12);
		int16_t bitmapIndex; // .14, 0xE
		static_assert(offsetof(mm7::FacetData, bitmapIndex) == 14);
		int16_t TFTIndex; // .16, 0x10
		static_assert(offsetof(mm7::FacetData, TFTIndex) == 16);
		SKIP(2);
		int16_t bitmapU; // .20, 0x14
		static_assert(offsetof(mm7::FacetData, bitmapU) == 20);
		int16_t bitmapV; // .22, 0x16
		static_assert(offsetof(mm7::FacetData, bitmapV) == 22);
		int16_t id; // .24, 0x18
		static_assert(offsetof(mm7::FacetData, id) == 24);
		int16_t event; // .26, 0x1A
		static_assert(offsetof(mm7::FacetData, event) == 26);
		SKIP(8);
	};
	static_assert(sizeof(mm7::FacetData) == 0x24, "Invalid \"mm7::FacetData\" structure size");

	struct MapDoor // size: 0x50
	{
		union
		{
			uint32_t bits; // .0, 0x0
			struct
			{
				bool startState2 : 1; // .0, 0x0
				bool silentMove : 1; // .0, 0x0
				bool noSound : 1; // .0, 0x0
				bool stopped : 1; // .0, 0x0
			};
		};
		int32_t id; // .4, 0x4
		static_assert(offsetof(mm7::MapDoor, id) == 4);
		int32_t timeStep; // .8, 0x8
		static_assert(offsetof(mm7::MapDoor, timeStep) == 8);
		union
		{
			std::array<int32_t, 3> direction; // .12, 0xC
			static_assert(offsetof(mm7::MapDoor, direction) == 12);
			struct
			{
				int32_t directionX; // .12, 0xC
				static_assert(offsetof(mm7::MapDoor, directionX) == 12);
				int32_t directionY; // .16, 0x10
				static_assert(offsetof(mm7::MapDoor, directionY) == 16);
				int32_t directionZ; // .20, 0x14
				static_assert(offsetof(mm7::MapDoor, directionZ) == 20);
			};
		};
		int32_t moveLength; // .24, 0x18
		static_assert(offsetof(mm7::MapDoor, moveLength) == 24);
		union
		{
			int32_t openSpeed; // .28, 0x1C
			static_assert(offsetof(mm7::MapDoor, openSpeed) == 28);
			int32_t speed2; // .28, 0x1C
			static_assert(offsetof(mm7::MapDoor, speed2) == 28);
		};
		union
		{
			int32_t closeSpeed; // .32, 0x20
			static_assert(offsetof(mm7::MapDoor, closeSpeed) == 32);
			int32_t speed1; // .32, 0x20
			static_assert(offsetof(mm7::MapDoor, speed1) == 32);
		};
		int16_t* vertexIds; // size offset is 0x44 | .36, 0x24
		static_assert(offsetof(mm7::MapDoor, vertexIds) == 36);
		int16_t* facetIds; // size offset is 0x46 | .40, 0x28
		static_assert(offsetof(mm7::MapDoor, facetIds) == 40);
		int16_t* roomIds; // size offset is 0x48 | .44, 0x2C
		static_assert(offsetof(mm7::MapDoor, roomIds) == 44);
		int16_t* facetStartU; // size offset is 0x46 | .48, 0x30
		static_assert(offsetof(mm7::MapDoor, facetStartU) == 48);
		int16_t* facetStartV; // size offset is 0x46 | .52, 0x34
		static_assert(offsetof(mm7::MapDoor, facetStartV) == 52);
		int16_t* vertexStartX; // size offset is 0x4A | .56, 0x38
		static_assert(offsetof(mm7::MapDoor, vertexStartX) == 56);
		int16_t* vertexStartY; // size offset is 0x4A | .60, 0x3C
		static_assert(offsetof(mm7::MapDoor, vertexStartY) == 60);
		int16_t* vertexStartZ; // size offset is 0x4A | .64, 0x40
		static_assert(offsetof(mm7::MapDoor, vertexStartZ) == 64);
		uint16_t vertexIds_size; // .68, 0x44
		static_assert(offsetof(mm7::MapDoor, vertexIds_size) == 68);
		union
		{
			uint16_t facetStartU_size; // .70, 0x46
			static_assert(offsetof(mm7::MapDoor, facetStartU_size) == 70);
			uint16_t facetIds_size; // .70, 0x46
			static_assert(offsetof(mm7::MapDoor, facetIds_size) == 70);
			uint16_t facetStartV_size; // .70, 0x46
			static_assert(offsetof(mm7::MapDoor, facetStartV_size) == 70);
		};
		uint16_t roomIds_size; // .72, 0x48
		static_assert(offsetof(mm7::MapDoor, roomIds_size) == 72);
		union
		{
			uint16_t vertexStartY_size; // .74, 0x4A
			static_assert(offsetof(mm7::MapDoor, vertexStartY_size) == 74);
			uint16_t vertexStartZ_size; // .74, 0x4A
			static_assert(offsetof(mm7::MapDoor, vertexStartZ_size) == 74);
			uint16_t vertexStartX_size; // .74, 0x4A
			static_assert(offsetof(mm7::MapDoor, vertexStartX_size) == 74);
		};
		int16_t state; // .76, 0x4C
		static_assert(offsetof(mm7::MapDoor, state) == 76);
		SKIP(2);
	};
	static_assert(sizeof(mm7::MapDoor) == 0x50, "Invalid \"mm7::MapDoor\" structure size");

	struct MapOutline // size: 0xC
	{
		int16_t vertex1; // .0, 0x0
		int16_t vertex2; // .2, 0x2
		static_assert(offsetof(mm7::MapOutline, vertex2) == 2);
		int16_t facet1; // .4, 0x4
		static_assert(offsetof(mm7::MapOutline, facet1) == 4);
		int16_t facet2; // .6, 0x6
		static_assert(offsetof(mm7::MapOutline, facet2) == 6);
		int16_t z; // .8, 0x8
		static_assert(offsetof(mm7::MapOutline, z) == 8);
		union
		{
			uint16_t bits; // .10, 0xA
			static_assert(offsetof(mm7::MapOutline, bits) == 10);
			struct
			{
				bool visible : 1; // .10, 0xA
			};
		};
	};
	static_assert(sizeof(mm7::MapOutline) == 0xC, "Invalid \"mm7::MapOutline\" structure size");

	struct MapOutlines // size: 0x14824
	{
		uint32_t items_size; // .0, 0x0
		std::array<mm7::MapOutline, 7000> items; // size offset is 0x0 | .4, 0x4
		static_assert(offsetof(mm7::MapOutlines, items) == 4);
	};
	static_assert(sizeof(mm7::MapOutlines) == 0x14824, "Invalid \"mm7::MapOutlines\" structure size");

	struct BaseLight // size: 0xC
	{
		union
		{
			std::array<int16_t, 3> pos; // .0, 0x0
			struct
			{
				int16_t x; // .0, 0x0
				int16_t y; // .2, 0x2
				static_assert(offsetof(mm7::BaseLight, y) == 2);
				int16_t z; // .4, 0x4
				static_assert(offsetof(mm7::BaseLight, z) == 4);
			};
		};
		int16_t radius; // .6, 0x6
		static_assert(offsetof(mm7::BaseLight, radius) == 6);
		uint8_t r; // .8, 0x8
		static_assert(offsetof(mm7::BaseLight, r) == 8);
		uint8_t g; // .9, 0x9
		static_assert(offsetof(mm7::BaseLight, g) == 9);
		uint8_t b; // .10, 0xA
		static_assert(offsetof(mm7::BaseLight, b) == 10);
		uint8_t type; // .11, 0xB
		static_assert(offsetof(mm7::BaseLight, type) == 11);
	};
	static_assert(sizeof(mm7::BaseLight) == 0xC, "Invalid \"mm7::BaseLight\" structure size");

	struct ModelVertex // size: 0xC
	{
		union
		{
			int32_t _1; // .0, 0x0
			int32_t x; // .0, 0x0
		};
		union
		{
			int32_t y; // .4, 0x4
			static_assert(offsetof(mm7::ModelVertex, y) == 4);
			int32_t _2; // .4, 0x4
			static_assert(offsetof(mm7::ModelVertex, _2) == 4);
		};
		union
		{
			int32_t _3; // .8, 0x8
			static_assert(offsetof(mm7::ModelVertex, _3) == 8);
			int32_t z; // .8, 0x8
			static_assert(offsetof(mm7::ModelVertex, z) == 8);
		};
	};
	static_assert(sizeof(mm7::ModelVertex) == 0xC, "Invalid \"mm7::ModelVertex\" structure size");

	struct ModelFacet // size: 0x134
	{
		union
		{
			std::array<int32_t, 3> normal; // .0, 0x0
			struct
			{
				int32_t normalX; // .0, 0x0
				int32_t normalY; // .4, 0x4
				static_assert(offsetof(mm7::ModelFacet, normalY) == 4);
				int32_t normalZ; // .8, 0x8
				static_assert(offsetof(mm7::ModelFacet, normalZ) == 8);
			};
		};
		int32_t normalDistance; // .12, 0xC
		static_assert(offsetof(mm7::ModelFacet, normalDistance) == 12);
		int32_t ZCalc1; // .16, 0x10
		static_assert(offsetof(mm7::ModelFacet, ZCalc1) == 16);
		int32_t ZCalc2; // .20, 0x14
		static_assert(offsetof(mm7::ModelFacet, ZCalc2) == 20);
		int32_t ZCalc3; // .24, 0x18
		static_assert(offsetof(mm7::ModelFacet, ZCalc3) == 24);
		union
		{
			uint32_t bits; // .28, 0x1C
			static_assert(offsetof(mm7::ModelFacet, bits) == 28);
			struct
			{
				bool isPortal : 1; // .28, 0x1C
				bool isSecret : 1; // .28, 0x1C
				bool scrollDown : 1; // .28, 0x1C
				bool alignTop : 1; // .28, 0x1C
				bool isWater : 1; // .28, 0x1C
				bool scrollUp : 1; // .28, 0x1C
				bool scrollLeft : 1; // .28, 0x1C
				SKIPBITS(1);
				bool projectToXY : 1; // .29, 0x1D
				bool projectToXZ : 1; // .29, 0x1D
				bool projectToYZ : 1; // .29, 0x1D
				bool scrollRight : 1; // .29, 0x1D
				bool alignLeft : 1; // .29, 0x1D
				bool invisible : 1; // .29, 0x1D
				bool animatedTFT : 1; // .29, 0x1D
				bool alignRight : 1; // .29, 0x1D
				SKIPBITS(1);
				bool alignBottom : 1; // .30, 0x1E
				bool moveByDoor : 1; // .30, 0x1E
				SKIPBITS(1);
				bool isEventJustHint : 1; // .30, 0x1E
				bool alternativeSound : 1; // .30, 0x1E
				bool isSky : 1; // .30, 0x1E
				bool flipU : 1; // .30, 0x1E
				bool flipV : 1; // .31, 0x1F
				bool triggerByClick : 1; // .31, 0x1F
				bool triggerByStep : 1; // .31, 0x1F
				bool triggerByMonster : 1; // .31, 0x1F
				bool triggerByObject : 1; // .31, 0x1F
				bool untouchable : 1; // .31, 0x1F
				bool isLava : 1; // .31, 0x1F
				bool hasData : 1; // .31, 0x1F
			};
		};
		std::array<int16_t, 20> vertexIds; // AccessBeyondLength is active (???) | size offset is 0x12E | .32, 0x20
		static_assert(offsetof(mm7::ModelFacet, vertexIds) == 32);
		std::array<int16_t, 20> UList; // AccessBeyondLength is active (???) | size offset is 0x12E | .72, 0x48
		static_assert(offsetof(mm7::ModelFacet, UList) == 72);
		std::array<int16_t, 20> VList; // AccessBeyondLength is active (???) | size offset is 0x12E | .112, 0x70
		static_assert(offsetof(mm7::ModelFacet, VList) == 112);
		std::array<int16_t, 20> XInterceptDisplacement; // AccessBeyondLength is active (???) | size offset is 0x12E | .152, 0x98
		static_assert(offsetof(mm7::ModelFacet, XInterceptDisplacement) == 152);
		std::array<int16_t, 20> YInterceptDisplacement; // AccessBeyondLength is active (???) | size offset is 0x12E | .192, 0xC0
		static_assert(offsetof(mm7::ModelFacet, YInterceptDisplacement) == 192);
		std::array<int16_t, 20> ZInterceptDisplacement; // AccessBeyondLength is active (???) | size offset is 0x12E | .232, 0xE8
		static_assert(offsetof(mm7::ModelFacet, ZInterceptDisplacement) == 232);
		int16_t bitmapId; // .272, 0x110
		static_assert(offsetof(mm7::ModelFacet, bitmapId) == 272);
		int16_t bitmapU; // .274, 0x112
		static_assert(offsetof(mm7::ModelFacet, bitmapU) == 274);
		int16_t bitmapV; // .276, 0x114
		static_assert(offsetof(mm7::ModelFacet, bitmapV) == 276);
		int16_t minX; // .278, 0x116
		static_assert(offsetof(mm7::ModelFacet, minX) == 278);
		int16_t maxX; // .280, 0x118
		static_assert(offsetof(mm7::ModelFacet, maxX) == 280);
		int16_t minY; // .282, 0x11A
		static_assert(offsetof(mm7::ModelFacet, minY) == 282);
		int16_t maxY; // .284, 0x11C
		static_assert(offsetof(mm7::ModelFacet, maxY) == 284);
		int16_t minZ; // .286, 0x11E
		static_assert(offsetof(mm7::ModelFacet, minZ) == 286);
		int16_t maxZ; // .288, 0x120
		static_assert(offsetof(mm7::ModelFacet, maxZ) == 288);
		int16_t id; // .290, 0x122
		static_assert(offsetof(mm7::ModelFacet, id) == 290);
		int16_t event; // .292, 0x124
		static_assert(offsetof(mm7::ModelFacet, event) == 292);
		SKIP(4);
		std::array<uint8_t, 4> gradientVertexes; // .298, 0x12A
		static_assert(offsetof(mm7::ModelFacet, gradientVertexes) == 298);
		union
		{
			uint8_t vertexIds_size; // .302, 0x12E
			static_assert(offsetof(mm7::ModelFacet, vertexIds_size) == 302);
			uint8_t VList_size; // .302, 0x12E
			static_assert(offsetof(mm7::ModelFacet, VList_size) == 302);
			uint8_t UList_size; // .302, 0x12E
			static_assert(offsetof(mm7::ModelFacet, UList_size) == 302);
			uint8_t vertexesCount; // .302, 0x12E
			static_assert(offsetof(mm7::ModelFacet, vertexesCount) == 302);
			uint8_t XInterceptDisplacement_size; // .302, 0x12E
			static_assert(offsetof(mm7::ModelFacet, XInterceptDisplacement_size) == 302);
			uint8_t YInterceptDisplacement_size; // .302, 0x12E
			static_assert(offsetof(mm7::ModelFacet, YInterceptDisplacement_size) == 302);
			uint8_t ZInterceptDisplacement_size; // .302, 0x12E
			static_assert(offsetof(mm7::ModelFacet, ZInterceptDisplacement_size) == 302);
		};
		uint8_t polygonType; // .303, 0x12F
		static_assert(offsetof(mm7::ModelFacet, polygonType) == 303);
		SKIP(4);
	};
	static_assert(sizeof(mm7::ModelFacet) == 0x134, "Invalid \"mm7::ModelFacet\" structure size");

	struct MonsterAttackInfo // size: 0x5
	{
		uint8_t type; // .0, 0x0
		uint8_t damageDiceCount; // .1, 0x1
		static_assert(offsetof(mm7::MonsterAttackInfo, damageDiceCount) == 1);
		uint8_t damageDiceSides; // .2, 0x2
		static_assert(offsetof(mm7::MonsterAttackInfo, damageDiceSides) == 2);
		uint8_t damageAdd; // .3, 0x3
		static_assert(offsetof(mm7::MonsterAttackInfo, damageAdd) == 3);
		uint8_t missile; // .4, 0x4
		static_assert(offsetof(mm7::MonsterAttackInfo, missile) == 4);
	};
	static_assert(sizeof(mm7::MonsterAttackInfo) == 0x5, "Invalid \"mm7::MonsterAttackInfo\" structure size");

	struct MonstersTxtItem // size: 0x58
	{
		char* name; // .0, 0x0
		char* picture; // .4, 0x4
		static_assert(offsetof(mm7::MonstersTxtItem, picture) == 4);
		uint8_t level; // .8, 0x8
		static_assert(offsetof(mm7::MonstersTxtItem, level) == 8);
		uint8_t treasureItemPercent; // .9, 0x9
		static_assert(offsetof(mm7::MonstersTxtItem, treasureItemPercent) == 9);
		uint8_t treasureDiceCount; // .10, 0xA
		static_assert(offsetof(mm7::MonstersTxtItem, treasureDiceCount) == 10);
		uint8_t treasureDiceSides; // .11, 0xB
		static_assert(offsetof(mm7::MonstersTxtItem, treasureDiceSides) == 11);
		uint8_t treasureItemLevel; // .12, 0xC
		static_assert(offsetof(mm7::MonstersTxtItem, treasureItemLevel) == 12);
		uint8_t treasureItemType; // .13, 0xD
		static_assert(offsetof(mm7::MonstersTxtItem, treasureItemType) == 13);
		uint8_t fly; // .14, 0xE
		static_assert(offsetof(mm7::MonstersTxtItem, fly) == 14);
		uint8_t moveType; // .15, 0xF
		static_assert(offsetof(mm7::MonstersTxtItem, moveType) == 15);
		uint8_t AIType; // .16, 0x10
		static_assert(offsetof(mm7::MonstersTxtItem, AIType) == 16);
		uint8_t hostileType; // .17, 0x11
		static_assert(offsetof(mm7::MonstersTxtItem, hostileType) == 17);
		SKIP(1);
		uint8_t bonus; // .19, 0x13
		static_assert(offsetof(mm7::MonstersTxtItem, bonus) == 19);
		uint8_t bonusMul; // .20, 0x14
		static_assert(offsetof(mm7::MonstersTxtItem, bonusMul) == 20);
		mm7::MonsterAttackInfo attack1; // .21, 0x15
		static_assert(offsetof(mm7::MonstersTxtItem, attack1) == 21);
		uint8_t attack2Chance; // .26, 0x1A
		static_assert(offsetof(mm7::MonstersTxtItem, attack2Chance) == 26);
		mm7::MonsterAttackInfo attack2; // .27, 0x1B
		static_assert(offsetof(mm7::MonstersTxtItem, attack2) == 27);
		uint8_t spellChance; // .32, 0x20
		static_assert(offsetof(mm7::MonstersTxtItem, spellChance) == 32);
		uint8_t spell; // .33, 0x21
		static_assert(offsetof(mm7::MonstersTxtItem, spell) == 33);
		uint8_t spell2Chance; // .34, 0x22
		static_assert(offsetof(mm7::MonstersTxtItem, spell2Chance) == 34);
		uint8_t spell2; // .35, 0x23
		static_assert(offsetof(mm7::MonstersTxtItem, spell2) == 35);
		uint8_t fireResistance; // .36, 0x24
		static_assert(offsetof(mm7::MonstersTxtItem, fireResistance) == 36);
		uint8_t airResistance; // .37, 0x25
		static_assert(offsetof(mm7::MonstersTxtItem, airResistance) == 37);
		uint8_t waterResistance; // .38, 0x26
		static_assert(offsetof(mm7::MonstersTxtItem, waterResistance) == 38);
		uint8_t earthResistance; // .39, 0x27
		static_assert(offsetof(mm7::MonstersTxtItem, earthResistance) == 39);
		uint8_t mindResistance; // .40, 0x28
		static_assert(offsetof(mm7::MonstersTxtItem, mindResistance) == 40);
		uint8_t spiritResistance; // .41, 0x29
		static_assert(offsetof(mm7::MonstersTxtItem, spiritResistance) == 41);
		uint8_t bodyResistance; // .42, 0x2A
		static_assert(offsetof(mm7::MonstersTxtItem, bodyResistance) == 42);
		uint8_t lightResistance; // .43, 0x2B
		static_assert(offsetof(mm7::MonstersTxtItem, lightResistance) == 43);
		uint8_t darkResistance; // .44, 0x2C
		static_assert(offsetof(mm7::MonstersTxtItem, darkResistance) == 44);
		uint8_t physResistance; // .45, 0x2D
		static_assert(offsetof(mm7::MonstersTxtItem, physResistance) == 45);
		uint8_t special; // .46, 0x2E
		static_assert(offsetof(mm7::MonstersTxtItem, special) == 46);
		uint8_t specialA; // .47, 0x2F
		static_assert(offsetof(mm7::MonstersTxtItem, specialA) == 47);
		uint8_t specialB; // .48, 0x30
		static_assert(offsetof(mm7::MonstersTxtItem, specialB) == 48);
		uint8_t specialC; // .49, 0x31
		static_assert(offsetof(mm7::MonstersTxtItem, specialC) == 49);
		uint8_t prefNum; // .50, 0x32
		static_assert(offsetof(mm7::MonstersTxtItem, prefNum) == 50);
		SKIP(1);
		uint16_t id; // .52, 0x34
		static_assert(offsetof(mm7::MonstersTxtItem, id) == 52);
		uint16_t bloodSplat; // .54, 0x36
		static_assert(offsetof(mm7::MonstersTxtItem, bloodSplat) == 54);
		uint16_t spellSkill; // .56, 0x38
		static_assert(offsetof(mm7::MonstersTxtItem, spellSkill) == 56);
		uint16_t spell2Skill; // .58, 0x3A
		static_assert(offsetof(mm7::MonstersTxtItem, spell2Skill) == 58);
		uint16_t specialD; // .60, 0x3C
		static_assert(offsetof(mm7::MonstersTxtItem, specialD) == 60);
		SKIP(2);
		union
		{
			int32_t fullHitPoints; // .64, 0x40
			static_assert(offsetof(mm7::MonstersTxtItem, fullHitPoints) == 64);
			int32_t fullHP; // .64, 0x40
			static_assert(offsetof(mm7::MonstersTxtItem, fullHP) == 64);
		};
		int32_t armorClass; // .68, 0x44
		static_assert(offsetof(mm7::MonstersTxtItem, armorClass) == 68);
		union
		{
			int32_t exp; // .72, 0x48
			static_assert(offsetof(mm7::MonstersTxtItem, exp) == 72);
			int32_t experience; // .72, 0x48
			static_assert(offsetof(mm7::MonstersTxtItem, experience) == 72);
		};
		int32_t moveSpeed; // .76, 0x4C
		static_assert(offsetof(mm7::MonstersTxtItem, moveSpeed) == 76);
		int32_t attackRecovery; // .80, 0x50
		static_assert(offsetof(mm7::MonstersTxtItem, attackRecovery) == 80);
		int32_t prefClass; // .84, 0x54
		static_assert(offsetof(mm7::MonstersTxtItem, prefClass) == 84);
	};
	static_assert(sizeof(mm7::MonstersTxtItem) == 0x58, "Invalid \"mm7::MonstersTxtItem\" structure size");

	struct SpellBuff // size: 0x10
	{
		int64_t expireTime; // .0, 0x0
		int16_t power; // .8, 0x8
		static_assert(offsetof(mm7::SpellBuff, power) == 8);
		int16_t skill; // .10, 0xA
		static_assert(offsetof(mm7::SpellBuff, skill) == 10);
		int16_t overlayId; // .12, 0xC
		static_assert(offsetof(mm7::SpellBuff, overlayId) == 12);
		uint8_t caster; // .14, 0xE
		static_assert(offsetof(mm7::SpellBuff, caster) == 14);
		uint8_t bits; // .15, 0xF
		static_assert(offsetof(mm7::SpellBuff, bits) == 15);
	};
	static_assert(sizeof(mm7::SpellBuff) == 0x10, "Invalid \"mm7::SpellBuff\" structure size");

	struct MonsterSchedule // size: 0xC
	{
		union
		{
			std::array<int16_t, 3> pos; // .0, 0x0
			struct
			{
				int16_t x; // .0, 0x0
				int16_t y; // .2, 0x2
				static_assert(offsetof(mm7::MonsterSchedule, y) == 2);
				int16_t z; // .4, 0x4
				static_assert(offsetof(mm7::MonsterSchedule, z) == 4);
			};
		};
		uint16_t bits; // .6, 0x6
		static_assert(offsetof(mm7::MonsterSchedule, bits) == 6);
		uint8_t action; // .8, 0x8
		static_assert(offsetof(mm7::MonsterSchedule, action) == 8);
		uint8_t hour; // .9, 0x9
		static_assert(offsetof(mm7::MonsterSchedule, hour) == 9);
		uint8_t day; // .10, 0xA
		static_assert(offsetof(mm7::MonsterSchedule, day) == 10);
		uint8_t month; // .11, 0xB
		static_assert(offsetof(mm7::MonsterSchedule, month) == 11);
	};
	static_assert(sizeof(mm7::MonsterSchedule) == 0xC, "Invalid \"mm7::MonsterSchedule\" structure size");

	struct BlvHeader // size: 0x88
	{
		SKIP(4);
		std::array<char, 60> name; // requires null terminator | .0, 0x0
		SKIP(40);
		int32_t facetDataSize; // .104, 0x68
		static_assert(offsetof(mm7::BlvHeader, facetDataSize) == 104);
		int32_t roomDataSize; // .108, 0x6C
		static_assert(offsetof(mm7::BlvHeader, roomDataSize) == 108);
		int32_t roomLightDataSize; // .112, 0x70
		static_assert(offsetof(mm7::BlvHeader, roomLightDataSize) == 112);
		int32_t doorDataSize; // .116, 0x74
		static_assert(offsetof(mm7::BlvHeader, doorDataSize) == 116);
		SKIP(16);
	};
	static_assert(sizeof(mm7::BlvHeader) == 0x88, "Invalid \"mm7::BlvHeader\" structure size");

	struct LodFile // size: 0x20
	{
		std::array<char, 16> name; // requires null terminator | .0, 0x0
		int32_t offset; // .16, 0x10
		static_assert(offsetof(mm7::LodFile, offset) == 16);
		int32_t size; // .20, 0x14
		static_assert(offsetof(mm7::LodFile, size) == 20);
		SKIP(8);
	};
	static_assert(sizeof(mm7::LodFile) == 0x20, "Invalid \"mm7::LodFile\" structure size");

	struct SpritesLod // size: 0xECB8
	{
		uint32_t file; // .0, 0x0
		std::array<char, 256> fileName; // requires null terminator | .0, 0x0
		uint32_t loaded; // 4-byte boolean | .260, 0x104
		static_assert(offsetof(mm7::SpritesLod, loaded) == 260);
		uint32_t IOBuffer; // .264, 0x108
		static_assert(offsetof(mm7::SpritesLod, IOBuffer) == 264);
		int32_t IOBufferSize; // .268, 0x10C
		static_assert(offsetof(mm7::SpritesLod, IOBufferSize) == 268);
		int32_t lodHeaderSignature; // .272, 0x110
		static_assert(offsetof(mm7::SpritesLod, lodHeaderSignature) == 272);
		SKIP(80);
		std::array<char, 80> description; // requires null terminator | .0, 0x0
		SKIP(8);
		int32_t archivesCount; // .444, 0x1BC
		static_assert(offsetof(mm7::SpritesLod, archivesCount) == 444);
		SKIP(80);
		uint32_t archivesCArray; // .528, 0x210
		static_assert(offsetof(mm7::SpritesLod, archivesCArray) == 528);
		std::array<char, 16> type; // requires null terminator | .0, 0x0
		uint32_t chapterHandle; // .548, 0x224
		static_assert(offsetof(mm7::SpritesLod, chapterHandle) == 548);
		uint32_t chapterSize; // .552, 0x228
		static_assert(offsetof(mm7::SpritesLod, chapterSize) == 552);
		uint32_t files_size; // .556, 0x22C
		static_assert(offsetof(mm7::SpritesLod, files_size) == 556);
		mm7::LodFile* files; // size offset is 0x22C | .560, 0x230
		static_assert(offsetof(mm7::SpritesLod, files) == 560);
		uint32_t filesOffset; // .564, 0x234
		static_assert(offsetof(mm7::SpritesLod, filesOffset) == 564);
		SKIP(60020);
		uint32_t isHardware; // 4-byte boolean | .60588, 0xECAC
		static_assert(offsetof(mm7::SpritesLod, isHardware) == 60588);
		mm7::LodSpriteD3D* spritesD3D; // size offset is 0xECB4 | .60592, 0xECB0
		static_assert(offsetof(mm7::SpritesLod, spritesD3D) == 60592);
		uint32_t spritesD3D_size; // .60596, 0xECB4
		static_assert(offsetof(mm7::SpritesLod, spritesD3D_size) == 60596);
		static mm7::LodSprite* spritesSW; // .46368492, 0x2C386EC
	};
	static_assert(sizeof(mm7::SpritesLod) == 0xECB8, "Invalid \"mm7::SpritesLod\" structure size");

	struct Lod // size: 0x23C
	{
		uint32_t file; // .0, 0x0
		std::array<char, 256> fileName; // requires null terminator | .0, 0x0
		uint32_t loaded; // 4-byte boolean | .260, 0x104
		static_assert(offsetof(mm7::Lod, loaded) == 260);
		uint32_t IOBuffer; // .264, 0x108
		static_assert(offsetof(mm7::Lod, IOBuffer) == 264);
		int32_t IOBufferSize; // .268, 0x10C
		static_assert(offsetof(mm7::Lod, IOBufferSize) == 268);
		int32_t lodHeaderSignature; // .272, 0x110
		static_assert(offsetof(mm7::Lod, lodHeaderSignature) == 272);
		SKIP(80);
		std::array<char, 80> description; // requires null terminator | .0, 0x0
		SKIP(8);
		int32_t archivesCount; // .444, 0x1BC
		static_assert(offsetof(mm7::Lod, archivesCount) == 444);
		SKIP(80);
		uint32_t archivesCArray; // .528, 0x210
		static_assert(offsetof(mm7::Lod, archivesCArray) == 528);
		std::array<char, 16> type; // requires null terminator | .0, 0x0
		uint32_t chapterHandle; // .548, 0x224
		static_assert(offsetof(mm7::Lod, chapterHandle) == 548);
		uint32_t chapterSize; // .552, 0x228
		static_assert(offsetof(mm7::Lod, chapterSize) == 552);
		uint32_t files_size; // .556, 0x22C
		static_assert(offsetof(mm7::Lod, files_size) == 556);
		mm7::LodFile* files; // size offset is 0x22C | .560, 0x230
		static_assert(offsetof(mm7::Lod, files) == 560);
		uint32_t filesOffset; // .564, 0x234
		static_assert(offsetof(mm7::Lod, filesOffset) == 564);
		SKIP(4);
	};
	static_assert(sizeof(mm7::Lod) == 0x23C, "Invalid \"mm7::Lod\" structure size");

	struct MapFacet // size: 0x60
	{
		union
		{
			std::array<float, 3> normalF; // .0, 0x0
			struct
			{
				float normalFX; // .0, 0x0
				float normalFY; // .4, 0x4
				static_assert(offsetof(mm7::MapFacet, normalFY) == 4);
				float normalFZ; // .8, 0x8
				static_assert(offsetof(mm7::MapFacet, normalFZ) == 8);
			};
		};
		float normalFDistance; // .12, 0xC
		static_assert(offsetof(mm7::MapFacet, normalFDistance) == 12);
		union
		{
			std::array<int32_t, 3> normal; // .16, 0x10
			static_assert(offsetof(mm7::MapFacet, normal) == 16);
			struct
			{
				int32_t normalX; // .16, 0x10
				static_assert(offsetof(mm7::MapFacet, normalX) == 16);
				int32_t normalY; // .20, 0x14
				static_assert(offsetof(mm7::MapFacet, normalY) == 20);
				int32_t normalZ; // .24, 0x18
				static_assert(offsetof(mm7::MapFacet, normalZ) == 24);
			};
		};
		int32_t normalDistance; // .28, 0x1C
		static_assert(offsetof(mm7::MapFacet, normalDistance) == 28);
		int32_t ZCalc1; // .32, 0x20
		static_assert(offsetof(mm7::MapFacet, ZCalc1) == 32);
		int32_t ZCalc2; // .36, 0x24
		static_assert(offsetof(mm7::MapFacet, ZCalc2) == 36);
		int32_t ZCalc3; // .40, 0x28
		static_assert(offsetof(mm7::MapFacet, ZCalc3) == 40);
		union
		{
			uint32_t bits; // .44, 0x2C
			static_assert(offsetof(mm7::MapFacet, bits) == 44);
			struct
			{
				bool isPortal : 1; // .44, 0x2C
				bool isSecret : 1; // .44, 0x2C
				bool scrollDown : 1; // .44, 0x2C
				bool alignTop : 1; // .44, 0x2C
				bool isWater : 1; // .44, 0x2C
				bool scrollUp : 1; // .44, 0x2C
				bool scrollLeft : 1; // .44, 0x2C
				SKIPBITS(1);
				bool projectToXY : 1; // .45, 0x2D
				bool projectToXZ : 1; // .45, 0x2D
				bool projectToYZ : 1; // .45, 0x2D
				bool scrollRight : 1; // .45, 0x2D
				bool alignLeft : 1; // .45, 0x2D
				bool invisible : 1; // .45, 0x2D
				bool animatedTFT : 1; // .45, 0x2D
				bool alignRight : 1; // .45, 0x2D
				SKIPBITS(1);
				bool alignBottom : 1; // .46, 0x2E
				bool moveByDoor : 1; // .46, 0x2E
				SKIPBITS(1);
				bool isEventJustHint : 1; // .46, 0x2E
				bool alternativeSound : 1; // .46, 0x2E
				bool isSky : 1; // .46, 0x2E
				bool flipU : 1; // .46, 0x2E
				bool flipV : 1; // .47, 0x2F
				bool triggerByClick : 1; // .47, 0x2F
				bool triggerByStep : 1; // .47, 0x2F
				bool triggerByMonster : 1; // .47, 0x2F
				bool triggerByObject : 1; // .47, 0x2F
				bool untouchable : 1; // .47, 0x2F
				bool isLava : 1; // .47, 0x2F
				bool hasData : 1; // .47, 0x2F
			};
		};
		uint16_t* vertexIds; // AccessBeyondLength is active (???) | size offset is 0x5D | .48, 0x30
		static_assert(offsetof(mm7::MapFacet, vertexIds) == 48);
		int16_t* XInterceptDisplacement; // AccessBeyondLength is active (???) | size offset is 0x5D | .52, 0x34
		static_assert(offsetof(mm7::MapFacet, XInterceptDisplacement) == 52);
		int16_t* YInterceptDisplacement; // AccessBeyondLength is active (???) | size offset is 0x5D | .56, 0x38
		static_assert(offsetof(mm7::MapFacet, YInterceptDisplacement) == 56);
		int16_t* ZInterceptDisplacement; // AccessBeyondLength is active (???) | size offset is 0x5D | .60, 0x3C
		static_assert(offsetof(mm7::MapFacet, ZInterceptDisplacement) == 60);
		int16_t* UList; // AccessBeyondLength is active (???) | size offset is 0x5D | .64, 0x40
		static_assert(offsetof(mm7::MapFacet, UList) == 64);
		int16_t* VList; // AccessBeyondLength is active (???) | size offset is 0x5D | .68, 0x44
		static_assert(offsetof(mm7::MapFacet, VList) == 68);
		uint16_t dataIndex; // .72, 0x48
		static_assert(offsetof(mm7::MapFacet, dataIndex) == 72);
		int16_t bitmapId; // .74, 0x4A
		static_assert(offsetof(mm7::MapFacet, bitmapId) == 74);
		int16_t room; // .76, 0x4C
		static_assert(offsetof(mm7::MapFacet, room) == 76);
		int16_t roomBehind; // .78, 0x4E
		static_assert(offsetof(mm7::MapFacet, roomBehind) == 78);
		int16_t minX; // .80, 0x50
		static_assert(offsetof(mm7::MapFacet, minX) == 80);
		int16_t maxX; // .82, 0x52
		static_assert(offsetof(mm7::MapFacet, maxX) == 82);
		int16_t minY; // .84, 0x54
		static_assert(offsetof(mm7::MapFacet, minY) == 84);
		int16_t maxY; // .86, 0x56
		static_assert(offsetof(mm7::MapFacet, maxY) == 86);
		int16_t minZ; // .88, 0x58
		static_assert(offsetof(mm7::MapFacet, minZ) == 88);
		int16_t maxZ; // .90, 0x5A
		static_assert(offsetof(mm7::MapFacet, maxZ) == 90);
		uint8_t polygonType; // .92, 0x5C
		static_assert(offsetof(mm7::MapFacet, polygonType) == 92);
		union
		{
			uint8_t UList_size; // .93, 0x5D
			static_assert(offsetof(mm7::MapFacet, UList_size) == 93);
			uint8_t XInterceptDisplacement_size; // .93, 0x5D
			static_assert(offsetof(mm7::MapFacet, XInterceptDisplacement_size) == 93);
			uint8_t vertexesCount; // .93, 0x5D
			static_assert(offsetof(mm7::MapFacet, vertexesCount) == 93);
			uint8_t VList_size; // .93, 0x5D
			static_assert(offsetof(mm7::MapFacet, VList_size) == 93);
			uint8_t YInterceptDisplacement_size; // .93, 0x5D
			static_assert(offsetof(mm7::MapFacet, YInterceptDisplacement_size) == 93);
			uint8_t vertexIds_size; // .93, 0x5D
			static_assert(offsetof(mm7::MapFacet, vertexIds_size) == 93);
			uint8_t ZInterceptDisplacement_size; // .93, 0x5D
			static_assert(offsetof(mm7::MapFacet, ZInterceptDisplacement_size) == 93);
		};
		SKIP(2);
	};
	static_assert(sizeof(mm7::MapFacet) == 0x60, "Invalid \"mm7::MapFacet\" structure size");

	struct BSPNode // size: 0x8
	{
		int16_t frontNode; // .0, 0x0
		int16_t backNode; // .2, 0x2
		static_assert(offsetof(mm7::BSPNode, backNode) == 2);
		int16_t coplanarOffset; // .4, 0x4
		static_assert(offsetof(mm7::BSPNode, coplanarOffset) == 4);
		int16_t coplanarSize; // .6, 0x6
		static_assert(offsetof(mm7::BSPNode, coplanarSize) == 6);
	};
	static_assert(sizeof(mm7::BSPNode) == 0x8, "Invalid \"mm7::BSPNode\" structure size");

	struct MapModel // size: 0xBC
	{
		std::array<char, 32> name; // requires null terminator | .0, 0x0
		std::array<char, 32> name2; // requires null terminator | .0, 0x0
		union
		{
			uint32_t bits; // .64, 0x40
			static_assert(offsetof(mm7::MapModel, bits) == 64);
			struct
			{
				bool showOnMap : 1; // .64, 0x40
			};
		};
		uint32_t vertexes_size; // .68, 0x44
		static_assert(offsetof(mm7::MapModel, vertexes_size) == 68);
		mm7::ModelVertex* vertexes; // size offset is 0x44 | .72, 0x48
		static_assert(offsetof(mm7::MapModel, vertexes) == 72);
		union
		{
			uint32_t ordering_size; // .76, 0x4C
			static_assert(offsetof(mm7::MapModel, ordering_size) == 76);
			uint32_t facets_size; // .76, 0x4C
			static_assert(offsetof(mm7::MapModel, facets_size) == 76);
		};
		int16_t convexFacetsCount; // .80, 0x50
		static_assert(offsetof(mm7::MapModel, convexFacetsCount) == 80);
		SKIP(2);
		mm7::ModelFacet* facets; // size offset is 0x4C | .84, 0x54
		static_assert(offsetof(mm7::MapModel, facets) == 84);
		int16_t* ordering; // size offset is 0x4C | .88, 0x58
		static_assert(offsetof(mm7::MapModel, ordering) == 88);
		uint32_t BSPNodes_size; // .92, 0x5C
		static_assert(offsetof(mm7::MapModel, BSPNodes_size) == 92);
		mm7::BSPNode* BSPNodes; // size offset is 0x5C | .96, 0x60
		static_assert(offsetof(mm7::MapModel, BSPNodes) == 96);
		SKIP(4);
		int32_t gridX; // .104, 0x68
		static_assert(offsetof(mm7::MapModel, gridX) == 104);
		int32_t gridY; // .108, 0x6C
		static_assert(offsetof(mm7::MapModel, gridY) == 108);
		union
		{
			std::array<int32_t, 3> pos; // .112, 0x70
			static_assert(offsetof(mm7::MapModel, pos) == 112);
			struct
			{
				int32_t x; // .112, 0x70
				static_assert(offsetof(mm7::MapModel, x) == 112);
				int32_t y; // .116, 0x74
				static_assert(offsetof(mm7::MapModel, y) == 116);
				int32_t z; // .120, 0x78
				static_assert(offsetof(mm7::MapModel, z) == 120);
			};
		};
		int32_t minX; // .124, 0x7C
		static_assert(offsetof(mm7::MapModel, minX) == 124);
		int32_t minY; // .128, 0x80
		static_assert(offsetof(mm7::MapModel, minY) == 128);
		int32_t minZ; // .132, 0x84
		static_assert(offsetof(mm7::MapModel, minZ) == 132);
		int32_t maxX; // .136, 0x88
		static_assert(offsetof(mm7::MapModel, maxX) == 136);
		int32_t maxY; // .140, 0x8C
		static_assert(offsetof(mm7::MapModel, maxY) == 140);
		int32_t maxZ; // .144, 0x90
		static_assert(offsetof(mm7::MapModel, maxZ) == 144);
		int32_t BFMinX; // .148, 0x94
		static_assert(offsetof(mm7::MapModel, BFMinX) == 148);
		int32_t BFMinY; // .152, 0x98
		static_assert(offsetof(mm7::MapModel, BFMinY) == 152);
		int32_t BFMinZ; // .156, 0x9C
		static_assert(offsetof(mm7::MapModel, BFMinZ) == 156);
		int32_t BFMaxX; // .160, 0xA0
		static_assert(offsetof(mm7::MapModel, BFMaxX) == 160);
		int32_t BFMaxY; // .164, 0xA4
		static_assert(offsetof(mm7::MapModel, BFMaxY) == 164);
		int32_t BFMaxZ; // .168, 0xA8
		static_assert(offsetof(mm7::MapModel, BFMaxZ) == 168);
		int32_t boxCenterX; // .172, 0xAC
		static_assert(offsetof(mm7::MapModel, boxCenterX) == 172);
		int32_t boxCenterY; // .176, 0xB0
		static_assert(offsetof(mm7::MapModel, boxCenterY) == 176);
		int32_t boxCenterZ; // .180, 0xB4
		static_assert(offsetof(mm7::MapModel, boxCenterZ) == 180);
		int32_t boundingRadius; // .184, 0xB8
		static_assert(offsetof(mm7::MapModel, boundingRadius) == 184);
	};
	static_assert(sizeof(mm7::MapModel) == 0xBC, "Invalid \"mm7::MapModel\" structure size");

	struct MapLight // size: 0x10
	{
		union
		{
			std::array<int16_t, 3> pos; // .0, 0x0
			struct
			{
				int16_t x; // .0, 0x0
				int16_t y; // .2, 0x2
				static_assert(offsetof(mm7::MapLight, y) == 2);
				int16_t z; // .4, 0x4
				static_assert(offsetof(mm7::MapLight, z) == 4);
			};
		};
		int16_t radius; // .6, 0x6
		static_assert(offsetof(mm7::MapLight, radius) == 6);
		uint8_t r; // .8, 0x8
		static_assert(offsetof(mm7::MapLight, r) == 8);
		uint8_t g; // .9, 0x9
		static_assert(offsetof(mm7::MapLight, g) == 9);
		uint8_t b; // .10, 0xA
		static_assert(offsetof(mm7::MapLight, b) == 10);
		uint8_t type; // .11, 0xB
		static_assert(offsetof(mm7::MapLight, type) == 11);
		union
		{
			uint16_t bits; // .12, 0xC
			static_assert(offsetof(mm7::MapLight, bits) == 12);
			struct
			{
				SKIPBITS(3);
				bool off : 1; // .12, 0xC
			};
		};
		int16_t brightness; // .14, 0xE
		static_assert(offsetof(mm7::MapLight, brightness) == 14);
	};
	static_assert(sizeof(mm7::MapLight) == 0x10, "Invalid \"mm7::MapLight\" structure size");

	struct MapRoom // size: 0x74
	{
		union
		{
			uint32_t bits; // .0, 0x0
			struct
			{
				SKIPBITS(3);
				bool hasNonVerticalPortals : 1; // .0, 0x0
				bool hasBSP : 1; // .0, 0x0
			};
		};
		uint16_t floors_size; // .4, 0x4
		static_assert(offsetof(mm7::MapRoom, floors_size) == 4);
		SKIP(2);
		int16_t* floors; // size offset is 0x4 | .8, 0x8
		static_assert(offsetof(mm7::MapRoom, floors) == 8);
		uint16_t walls_size; // .12, 0xC
		static_assert(offsetof(mm7::MapRoom, walls_size) == 12);
		SKIP(2);
		int16_t* walls; // size offset is 0xC | .16, 0x10
		static_assert(offsetof(mm7::MapRoom, walls) == 16);
		uint16_t ceils_size; // .20, 0x14
		static_assert(offsetof(mm7::MapRoom, ceils_size) == 20);
		SKIP(2);
		int16_t* ceils; // size offset is 0x14 | .24, 0x18
		static_assert(offsetof(mm7::MapRoom, ceils) == 24);
		uint16_t fluids_size; // .28, 0x1C
		static_assert(offsetof(mm7::MapRoom, fluids_size) == 28);
		SKIP(2);
		int16_t* fluids; // size offset is 0x1C | .32, 0x20
		static_assert(offsetof(mm7::MapRoom, fluids) == 32);
		uint16_t portals_size; // .36, 0x24
		static_assert(offsetof(mm7::MapRoom, portals_size) == 36);
		SKIP(2);
		int16_t* portals; // size offset is 0x24 | .40, 0x28
		static_assert(offsetof(mm7::MapRoom, portals) == 40);
		uint16_t drawFacets_size; // .44, 0x2C
		static_assert(offsetof(mm7::MapRoom, drawFacets_size) == 44);
		int16_t nonBSPDrawFacetsCount; // .46, 0x2E
		static_assert(offsetof(mm7::MapRoom, nonBSPDrawFacetsCount) == 46);
		int16_t* drawFacets; // size offset is 0x2C | .48, 0x30
		static_assert(offsetof(mm7::MapRoom, drawFacets) == 48);
		SKIP(8);
		uint16_t cogs_size; // .60, 0x3C
		static_assert(offsetof(mm7::MapRoom, cogs_size) == 60);
		SKIP(2);
		int16_t* cogs; // size offset is 0x3C | .64, 0x40
		static_assert(offsetof(mm7::MapRoom, cogs) == 64);
		uint16_t sprites_size; // .68, 0x44
		static_assert(offsetof(mm7::MapRoom, sprites_size) == 68);
		SKIP(2);
		int16_t* sprites; // size offset is 0x44 | .72, 0x48
		static_assert(offsetof(mm7::MapRoom, sprites) == 72);
		uint16_t markers_size; // .76, 0x4C
		static_assert(offsetof(mm7::MapRoom, markers_size) == 76);
		SKIP(2);
		int16_t* markers; // size offset is 0x4C | .80, 0x50
		static_assert(offsetof(mm7::MapRoom, markers) == 80);
		uint16_t lights_size; // .84, 0x54
		static_assert(offsetof(mm7::MapRoom, lights_size) == 84);
		SKIP(2);
		int16_t* lights; // size offset is 0x54 | .88, 0x58
		static_assert(offsetof(mm7::MapRoom, lights) == 88);
		SKIP(6);
		int16_t darkness; // .98, 0x62
		static_assert(offsetof(mm7::MapRoom, darkness) == 98);
		int16_t firstBSPNode; // .100, 0x64
		static_assert(offsetof(mm7::MapRoom, firstBSPNode) == 100);
		SKIP(1);
		uint8_t exitTag; // .103, 0x67
		static_assert(offsetof(mm7::MapRoom, exitTag) == 103);
		int16_t minX; // .104, 0x68
		static_assert(offsetof(mm7::MapRoom, minX) == 104);
		int16_t maxX; // .106, 0x6A
		static_assert(offsetof(mm7::MapRoom, maxX) == 106);
		int16_t minY; // .108, 0x6C
		static_assert(offsetof(mm7::MapRoom, minY) == 108);
		int16_t maxY; // .110, 0x6E
		static_assert(offsetof(mm7::MapRoom, maxY) == 110);
		int16_t minZ; // .112, 0x70
		static_assert(offsetof(mm7::MapRoom, minZ) == 112);
		int16_t maxZ; // .114, 0x72
		static_assert(offsetof(mm7::MapRoom, maxZ) == 114);
	};
	static_assert(sizeof(mm7::MapRoom) == 0x74, "Invalid \"mm7::MapRoom\" structure size");

	struct MapVertex // size: 0x6
	{
		union
		{
			int16_t _1; // .0, 0x0
			int16_t x; // .0, 0x0
		};
		union
		{
			int16_t y; // .2, 0x2
			static_assert(offsetof(mm7::MapVertex, y) == 2);
			int16_t _2; // .2, 0x2
			static_assert(offsetof(mm7::MapVertex, _2) == 2);
		};
		union
		{
			int16_t _3; // .4, 0x4
			static_assert(offsetof(mm7::MapVertex, _3) == 4);
			int16_t z; // .4, 0x4
			static_assert(offsetof(mm7::MapVertex, z) == 4);
		};
	};
	static_assert(sizeof(mm7::MapVertex) == 0x6, "Invalid \"mm7::MapVertex\" structure size");

	struct FloatVector // size: 0xC
	{
		union
		{
			float _1; // .0, 0x0
			float x; // .0, 0x0
		};
		union
		{
			float y; // .4, 0x4
			static_assert(offsetof(mm7::FloatVector, y) == 4);
			float _2; // .4, 0x4
			static_assert(offsetof(mm7::FloatVector, _2) == 4);
		};
		union
		{
			float _3; // .8, 0x8
			static_assert(offsetof(mm7::FloatVector, _3) == 8);
			float z; // .8, 0x8
			static_assert(offsetof(mm7::FloatVector, z) == 8);
		};
	};
	static_assert(sizeof(mm7::FloatVector) == 0xC, "Invalid \"mm7::FloatVector\" structure size");

	struct MapExtra // size: 0x38
	{
		int64_t lastVisitTime; // .0, 0x0
		std::array<char, 12> skyBitmap; // requires null terminator | .0, 0x0
		union
		{
			uint32_t dayBits; // .20, 0x14
			static_assert(offsetof(mm7::MapExtra, dayBits) == 20);
			struct
			{
				bool foggy : 1; // .20, 0x14
			};
		};
		int32_t fogRange1; // .24, 0x18
		static_assert(offsetof(mm7::MapExtra, fogRange1) == 24);
		int32_t fogRange2; // .28, 0x1C
		static_assert(offsetof(mm7::MapExtra, fogRange2) == 28);
		SKIP(8);
		uint32_t lastWeeklyTimer; // .40, 0x28
		static_assert(offsetof(mm7::MapExtra, lastWeeklyTimer) == 40);
		uint32_t lastMonthlyTimer; // .44, 0x2C
		static_assert(offsetof(mm7::MapExtra, lastMonthlyTimer) == 44);
		uint32_t lastYearlyTimer; // .48, 0x30
		static_assert(offsetof(mm7::MapExtra, lastYearlyTimer) == 48);
		uint32_t lastDailyTimer; // .52, 0x34
		static_assert(offsetof(mm7::MapExtra, lastDailyTimer) == 52);
	};
	static_assert(sizeof(mm7::MapExtra) == 0x38, "Invalid \"mm7::MapExtra\" structure size");

	struct SpawnPoint // size: 0x18
	{
		union
		{
			std::array<int32_t, 3> pos; // .0, 0x0
			struct
			{
				int32_t x; // .0, 0x0
				int32_t y; // .4, 0x4
				static_assert(offsetof(mm7::SpawnPoint, y) == 4);
				int32_t z; // .8, 0x8
				static_assert(offsetof(mm7::SpawnPoint, z) == 8);
			};
		};
		int16_t radius; // .12, 0xC
		static_assert(offsetof(mm7::SpawnPoint, radius) == 12);
		int16_t kind; // .14, 0xE
		static_assert(offsetof(mm7::SpawnPoint, kind) == 14);
		int16_t index; // .16, 0x10
		static_assert(offsetof(mm7::SpawnPoint, index) == 16);
		union
		{
			uint16_t bits; // .18, 0x12
			static_assert(offsetof(mm7::SpawnPoint, bits) == 18);
			struct
			{
				bool onAlertMap : 1; // .18, 0x12
			};
		};
		int32_t group; // .20, 0x14
		static_assert(offsetof(mm7::SpawnPoint, group) == 20);
	};
	static_assert(sizeof(mm7::SpawnPoint) == 0x18, "Invalid \"mm7::SpawnPoint\" structure size");

	struct ObjectRef2 // size: 0x2
	{
		union
		{
			uint16_t value; // .0, 0x0
			std::array<uint8_t, 2> index; // Unknown type | .0, 0x0
			struct
			{
				// uint8_t* kind; // real size is 0 | Unknown type | .0, 0x0
			};
		};
	};
	static_assert(sizeof(mm7::ObjectRef2) == 0x2, "Invalid \"mm7::ObjectRef2\" structure size");

	struct MapSprite // size: 0x20
	{
		union
		{
			int16_t decListId; // .0, 0x0
			std::array<uint8_t, 2> decName; // Unknown type | .0, 0x0
		};
		union
		{
			uint16_t bits; // .2, 0x2
			static_assert(offsetof(mm7::MapSprite, bits) == 2);
			struct
			{
				bool triggerByTouch : 1; // .2, 0x2
				bool triggerByMonster : 1; // .2, 0x2
				bool triggerByObject : 1; // .2, 0x2
				bool showOnMap : 1; // .2, 0x2
				bool isChest : 1; // .2, 0x2
				bool invisible : 1; // .2, 0x2
				bool isObeliskChest : 1; // .2, 0x2
			};
		};
		union
		{
			std::array<int32_t, 3> pos; // .4, 0x4
			static_assert(offsetof(mm7::MapSprite, pos) == 4);
			struct
			{
				int32_t x; // .4, 0x4
				static_assert(offsetof(mm7::MapSprite, x) == 4);
				int32_t y; // .8, 0x8
				static_assert(offsetof(mm7::MapSprite, y) == 8);
				int32_t z; // .12, 0xC
				static_assert(offsetof(mm7::MapSprite, z) == 12);
			};
		};
		int32_t direction; // .16, 0x10
		static_assert(offsetof(mm7::MapSprite, direction) == 16);
		int16_t id; // .20, 0x14
		static_assert(offsetof(mm7::MapSprite, id) == 20);
		int16_t event; // .22, 0x16
		static_assert(offsetof(mm7::MapSprite, event) == 22);
		int16_t triggerRadius; // .24, 0x18
		static_assert(offsetof(mm7::MapSprite, triggerRadius) == 24);
		int16_t directionDegrees; // .26, 0x1A
		static_assert(offsetof(mm7::MapSprite, directionDegrees) == 26);
		int16_t eventVariable; // .28, 0x1C
		static_assert(offsetof(mm7::MapSprite, eventVariable) == 28);
		SKIP(2);
	};
	static_assert(sizeof(mm7::MapSprite) == 0x20, "Invalid \"mm7::MapSprite\" structure size");

	struct TilesetDef // size: 0x4
	{
		std::array<uint8_t, 2> group; // Unknown type | .0, 0x0
		int16_t offset; // .2, 0x2
		static_assert(offsetof(mm7::TilesetDef, offset) == 2);
	};
	static_assert(sizeof(mm7::TilesetDef) == 0x4, "Invalid \"mm7::TilesetDef\" structure size");

	struct OdmHeader // size: 0xB0
	{
		std::array<char, 32> name; // requires null terminator | .0, 0x0
		std::array<char, 32> fileName; // requires null terminator | .0, 0x0
		std::array<char, 31> versionStr; // requires null terminator | .0, 0x0
		SKIP(65);
		std::array<mm7::TilesetDef, 4> tilesets; // .160, 0xA0
		static_assert(offsetof(mm7::OdmHeader, tilesets) == 160);
	};
	static_assert(sizeof(mm7::OdmHeader) == 0xB0, "Invalid \"mm7::OdmHeader\" structure size");

	struct GameScreen // size: 0x400F0
	{
		uint32_t isD3D; // 4-byte boolean | .0, 0x0
		SKIP(12);
		int32_t width; // .16, 0x10
		static_assert(offsetof(mm7::GameScreen, width) == 16);
		int32_t height; // .20, 0x14
		static_assert(offsetof(mm7::GameScreen, height) == 20);
		int32_t pitch; // .24, 0x18
		static_assert(offsetof(mm7::GameScreen, pitch) == 24);
		int32_t cx1; // .28, 0x1C
		static_assert(offsetof(mm7::GameScreen, cx1) == 28);
		int32_t cy1; // .32, 0x20
		static_assert(offsetof(mm7::GameScreen, cy1) == 32);
		int32_t cx2; // .36, 0x24
		static_assert(offsetof(mm7::GameScreen, cx2) == 36);
		int32_t cy2; // .40, 0x28
		static_assert(offsetof(mm7::GameScreen, cy2) == 40);
		SKIP(262152);
		uint32_t objectByPixel; // .262196, 0x40034
		static_assert(offsetof(mm7::GameScreen, objectByPixel) == 262196);
		SKIP(148);
		uint32_t redBits; // .262348, 0x400CC
		static_assert(offsetof(mm7::GameScreen, redBits) == 262348);
		uint32_t blueBits; // .262352, 0x400D0
		static_assert(offsetof(mm7::GameScreen, blueBits) == 262352);
		uint32_t greenBits; // .262356, 0x400D4
		static_assert(offsetof(mm7::GameScreen, greenBits) == 262356);
		uint32_t redMask; // .262360, 0x400D8
		static_assert(offsetof(mm7::GameScreen, redMask) == 262360);
		uint32_t greenMask; // .262364, 0x400DC
		static_assert(offsetof(mm7::GameScreen, greenMask) == 262364);
		uint32_t blueMask; // .262368, 0x400E0
		static_assert(offsetof(mm7::GameScreen, blueMask) == 262368);
		SKIP(8);
		uint32_t buffer; // .262380, 0x400EC
		static_assert(offsetof(mm7::GameScreen, buffer) == 262380);
	};
	static_assert(sizeof(mm7::GameScreen) == 0x400F0, "Invalid \"mm7::GameScreen\" structure size");

	struct Item // size: 0x24
	{
		int32_t number; // .0, 0x0
		int32_t bonus; // .4, 0x4
		static_assert(offsetof(mm7::Item, bonus) == 4);
		int32_t bonusStrength; // .8, 0x8
		static_assert(offsetof(mm7::Item, bonusStrength) == 8);
		int32_t bonus2; // .12, 0xC
		static_assert(offsetof(mm7::Item, bonus2) == 12);
		int32_t charges; // .16, 0x10
		static_assert(offsetof(mm7::Item, charges) == 16);
		union
		{
			int32_t condition; // .20, 0x14
			static_assert(offsetof(mm7::Item, condition) == 20);
			struct
			{
				bool identified : 1; // .20, 0x14
				bool broken : 1; // .20, 0x14
				SKIPBITS(1);
				bool temporaryBonus : 1; // .20, 0x14
				SKIPBITS(4);
				bool stolen : 1; // .21, 0x15
				bool hardened : 1; // .21, 0x15
				bool refundable : 1; // .21, 0x15
			};
		};
		int8_t bodyLocation; // .24, 0x18
		static_assert(offsetof(mm7::Item, bodyLocation) == 24);
		uint8_t maxCharges; // .25, 0x19
		static_assert(offsetof(mm7::Item, maxCharges) == 25);
		int8_t owner; // .26, 0x1A
		static_assert(offsetof(mm7::Item, owner) == 26);
		SKIP(1);
		int64_t bonusExpireTime; // .28, 0x1C
		static_assert(offsetof(mm7::Item, bonusExpireTime) == 28);
	};
	static_assert(sizeof(mm7::Item) == 0x24, "Invalid \"mm7::Item\" structure size");

	struct Player // size: 0x1B3C
	{
		union
		{
			std::array<int64_t, 20> conditions; // .0, 0x0
			struct
			{
				int64_t cursed; // .0, 0x0
				int64_t weak; // .8, 0x8
				static_assert(offsetof(mm7::Player, weak) == 8);
				int64_t asleep; // .16, 0x10
				static_assert(offsetof(mm7::Player, asleep) == 16);
				int64_t afraid; // .24, 0x18
				static_assert(offsetof(mm7::Player, afraid) == 24);
				int64_t drunk; // .32, 0x20
				static_assert(offsetof(mm7::Player, drunk) == 32);
				int64_t insane; // .40, 0x28
				static_assert(offsetof(mm7::Player, insane) == 40);
				int64_t poison1; // .48, 0x30
				static_assert(offsetof(mm7::Player, poison1) == 48);
				int64_t disease1; // .56, 0x38
				static_assert(offsetof(mm7::Player, disease1) == 56);
				int64_t poison2; // .64, 0x40
				static_assert(offsetof(mm7::Player, poison2) == 64);
				int64_t disease2; // .72, 0x48
				static_assert(offsetof(mm7::Player, disease2) == 72);
				int64_t poison3; // .80, 0x50
				static_assert(offsetof(mm7::Player, poison3) == 80);
				int64_t disease3; // .88, 0x58
				static_assert(offsetof(mm7::Player, disease3) == 88);
				int64_t paralyzed; // .96, 0x60
				static_assert(offsetof(mm7::Player, paralyzed) == 96);
				int64_t unconscious; // .104, 0x68
				static_assert(offsetof(mm7::Player, unconscious) == 104);
				int64_t dead; // .112, 0x70
				static_assert(offsetof(mm7::Player, dead) == 112);
				int64_t stoned; // .120, 0x78
				static_assert(offsetof(mm7::Player, stoned) == 120);
				int64_t eradicated; // .128, 0x80
				static_assert(offsetof(mm7::Player, eradicated) == 128);
				int64_t zombie; // .136, 0x88
				static_assert(offsetof(mm7::Player, zombie) == 136);
				int64_t good; // .144, 0x90
				static_assert(offsetof(mm7::Player, good) == 144);
			};
		};
		union
		{
			int64_t exp; // .160, 0xA0
			static_assert(offsetof(mm7::Player, exp) == 160);
			int64_t experience; // .160, 0xA0
			static_assert(offsetof(mm7::Player, experience) == 160);
		};
		std::array<char, 16> name; // requires null terminator | .0, 0x0
		bool sex; // .184, 0xB8
		static_assert(offsetof(mm7::Player, sex) == 184);
		uint8_t clas; // .185, 0xB9
		static_assert(offsetof(mm7::Player, clas) == 185);
		uint8_t face; // .186, 0xBA
		static_assert(offsetof(mm7::Player, face) == 186);
		SKIP(1);
		int16_t mightBase; // .188, 0xBC
		static_assert(offsetof(mm7::Player, mightBase) == 188);
		int16_t mightBonus; // .190, 0xBE
		static_assert(offsetof(mm7::Player, mightBonus) == 190);
		int16_t intellectBase; // .192, 0xC0
		static_assert(offsetof(mm7::Player, intellectBase) == 192);
		int16_t intellectBonus; // .194, 0xC2
		static_assert(offsetof(mm7::Player, intellectBonus) == 194);
		int16_t personalityBase; // .196, 0xC4
		static_assert(offsetof(mm7::Player, personalityBase) == 196);
		int16_t personalityBonus; // .198, 0xC6
		static_assert(offsetof(mm7::Player, personalityBonus) == 198);
		int16_t enduranceBase; // .200, 0xC8
		static_assert(offsetof(mm7::Player, enduranceBase) == 200);
		int16_t enduranceBonus; // .202, 0xCA
		static_assert(offsetof(mm7::Player, enduranceBonus) == 202);
		int16_t speedBase; // .204, 0xCC
		static_assert(offsetof(mm7::Player, speedBase) == 204);
		int16_t speedBonus; // .206, 0xCE
		static_assert(offsetof(mm7::Player, speedBonus) == 206);
		int16_t accuracyBase; // .208, 0xD0
		static_assert(offsetof(mm7::Player, accuracyBase) == 208);
		int16_t accuracyBonus; // .210, 0xD2
		static_assert(offsetof(mm7::Player, accuracyBonus) == 210);
		int16_t luckBase; // .212, 0xD4
		static_assert(offsetof(mm7::Player, luckBase) == 212);
		int16_t luckBonus; // .214, 0xD6
		static_assert(offsetof(mm7::Player, luckBonus) == 214);
		int16_t armorClassBonus; // .216, 0xD8
		static_assert(offsetof(mm7::Player, armorClassBonus) == 216);
		int16_t levelBase; // .218, 0xDA
		static_assert(offsetof(mm7::Player, levelBase) == 218);
		int16_t levelBonus; // .220, 0xDC
		static_assert(offsetof(mm7::Player, levelBonus) == 220);
		int16_t ageBonus; // .222, 0xDE
		static_assert(offsetof(mm7::Player, ageBonus) == 222);
		SKIP(40);
		std::array<int16_t, 37> skills; // .264, 0x108
		static_assert(offsetof(mm7::Player, skills) == 264);
		std::array<uint8_t, 13> awards; // MMExt: 1..104, here 0..103 | array of abits (real index = 7 - usual) | .338, 0x152
		SKIP(51);
		std::array<bool, 100> spells; // MMExt: 1..100, here 0..99 | .402, 0x192
		static_assert(offsetof(mm7::Player, spells) == 402);
		SKIP(2);
		std::array<uint32_t, 7> usedBlackPotions; // MMExt: 264..270, here 0..6 | 4-byte boolean | .504, 0x1F8
		static_assert(offsetof(mm7::Player, usedBlackPotions) == 504);
		std::array<mm7::Item, 138> items; // MMExt: 1..138, here 0..137 | .532, 0x214
		static_assert(offsetof(mm7::Player, items) == 532);
		std::array<int32_t, 126> inventory; // .5500, 0x157C
		static_assert(offsetof(mm7::Player, inventory) == 5500);
		union
		{
			std::array<int16_t, 11> resistanceBase; // .6004, 0x1774
			static_assert(offsetof(mm7::Player, resistanceBase) == 6004);
			struct
			{
				int16_t fireResistanceBase; // .6004, 0x1774
				static_assert(offsetof(mm7::Player, fireResistanceBase) == 6004);
				int16_t airResistanceBase; // .6006, 0x1776
				static_assert(offsetof(mm7::Player, airResistanceBase) == 6006);
				int16_t waterResistanceBase; // .6008, 0x1778
				static_assert(offsetof(mm7::Player, waterResistanceBase) == 6008);
				int16_t earthResistanceBase; // .6010, 0x177A
				static_assert(offsetof(mm7::Player, earthResistanceBase) == 6010);
				SKIP(4);
				int16_t spiritResistanceBase; // .6016, 0x1780
				static_assert(offsetof(mm7::Player, spiritResistanceBase) == 6016);
				int16_t mindResistanceBase; // .6018, 0x1782
				static_assert(offsetof(mm7::Player, mindResistanceBase) == 6018);
				int16_t bodyResistanceBase; // .6020, 0x1784
				static_assert(offsetof(mm7::Player, bodyResistanceBase) == 6020);
				int16_t lightResistanceBase; // .6022, 0x1786
				static_assert(offsetof(mm7::Player, lightResistanceBase) == 6022);
				int16_t darkResistanceBase; // .6024, 0x1788
				static_assert(offsetof(mm7::Player, darkResistanceBase) == 6024);
			};
		};
		union
		{
			std::array<int16_t, 11> resistanceBonus; // .6026, 0x178A
			static_assert(offsetof(mm7::Player, resistanceBonus) == 6026);
			struct
			{
				int16_t fireResistanceBonus; // .6026, 0x178A
				static_assert(offsetof(mm7::Player, fireResistanceBonus) == 6026);
				int16_t airResistanceBonus; // .6028, 0x178C
				static_assert(offsetof(mm7::Player, airResistanceBonus) == 6028);
				int16_t waterResistanceBonus; // .6030, 0x178E
				static_assert(offsetof(mm7::Player, waterResistanceBonus) == 6030);
				int16_t earthResistanceBonus; // .6032, 0x1790
				static_assert(offsetof(mm7::Player, earthResistanceBonus) == 6032);
				SKIP(4);
				int16_t spiritResistanceBonus; // .6038, 0x1796
				static_assert(offsetof(mm7::Player, spiritResistanceBonus) == 6038);
				int16_t mindResistanceBonus; // .6040, 0x1798
				static_assert(offsetof(mm7::Player, mindResistanceBonus) == 6040);
				int16_t bodyResistanceBonus; // .6042, 0x179A
				static_assert(offsetof(mm7::Player, bodyResistanceBonus) == 6042);
				int16_t lightResistanceBonus; // .6044, 0x179C
				static_assert(offsetof(mm7::Player, lightResistanceBonus) == 6044);
				int16_t darkResistanceBonus; // .6046, 0x179E
				static_assert(offsetof(mm7::Player, darkResistanceBonus) == 6046);
			};
		};
		std::array<mm7::SpellBuff, 24> spellBuffs; // .6048, 0x17A0
		static_assert(offsetof(mm7::Player, spellBuffs) == 6048);
		int32_t voice; // .6432, 0x1920
		static_assert(offsetof(mm7::Player, voice) == 6432);
		union
		{
			int32_t originalFace; // .6436, 0x1924
			static_assert(offsetof(mm7::Player, originalFace) == 6436);
			int32_t faceBeforeZombie; // .6436, 0x1924
			static_assert(offsetof(mm7::Player, faceBeforeZombie) == 6436);
		};
		union
		{
			int32_t originalVoice; // .6440, 0x1928
			static_assert(offsetof(mm7::Player, originalVoice) == 6440);
			int32_t voiceBeforeZombie; // .6440, 0x1928
			static_assert(offsetof(mm7::Player, voiceBeforeZombie) == 6440);
		};
		SKIP(8);
		int16_t recoveryDelay; // .6452, 0x1934
		static_assert(offsetof(mm7::Player, recoveryDelay) == 6452);
		uint8_t attackSpell; // .6454, 0x1936
		static_assert(offsetof(mm7::Player, attackSpell) == 6454);
		SKIP(1);
		int32_t skillPoints; // .6456, 0x1938
		static_assert(offsetof(mm7::Player, skillPoints) == 6456);
		union
		{
			int32_t hitPoints; // .6460, 0x193C
			static_assert(offsetof(mm7::Player, hitPoints) == 6460);
			int32_t HP; // .6460, 0x193C
			static_assert(offsetof(mm7::Player, HP) == 6460);
		};
		union
		{
			int32_t spellPoints; // .6464, 0x1940
			static_assert(offsetof(mm7::Player, spellPoints) == 6464);
			int32_t SP; // .6464, 0x1940
			static_assert(offsetof(mm7::Player, SP) == 6464);
		};
		int32_t birthYear; // .6468, 0x1944
		static_assert(offsetof(mm7::Player, birthYear) == 6468);
		union
		{
			std::array<int32_t, 16> equippedItems; // .6472, 0x1948
			static_assert(offsetof(mm7::Player, equippedItems) == 6472);
			struct
			{
				int32_t itemExtraHand; // .6472, 0x1948
				static_assert(offsetof(mm7::Player, itemExtraHand) == 6472);
				int32_t itemMainHand; // .6476, 0x194C
				static_assert(offsetof(mm7::Player, itemMainHand) == 6476);
				int32_t itemBow; // .6480, 0x1950
				static_assert(offsetof(mm7::Player, itemBow) == 6480);
				int32_t itemArmor; // .6484, 0x1954
				static_assert(offsetof(mm7::Player, itemArmor) == 6484);
				int32_t itemHelm; // .6488, 0x1958
				static_assert(offsetof(mm7::Player, itemHelm) == 6488);
				int32_t itemBelt; // .6492, 0x195C
				static_assert(offsetof(mm7::Player, itemBelt) == 6492);
				int32_t itemCloak; // .6496, 0x1960
				static_assert(offsetof(mm7::Player, itemCloak) == 6496);
				int32_t itemGountlets; // .6500, 0x1964
				static_assert(offsetof(mm7::Player, itemGountlets) == 6500);
				int32_t itemBoots; // .6504, 0x1968
				static_assert(offsetof(mm7::Player, itemBoots) == 6504);
				int32_t itemAmulet; // .6508, 0x196C
				static_assert(offsetof(mm7::Player, itemAmulet) == 6508);
				int32_t itemRing1; // .6512, 0x1970
				static_assert(offsetof(mm7::Player, itemRing1) == 6512);
				int32_t itemRing2; // .6516, 0x1974
				static_assert(offsetof(mm7::Player, itemRing2) == 6516);
				int32_t itemRing3; // .6520, 0x1978
				static_assert(offsetof(mm7::Player, itemRing3) == 6520);
				int32_t itemRing4; // .6524, 0x197C
				static_assert(offsetof(mm7::Player, itemRing4) == 6524);
				int32_t itemRing5; // .6528, 0x1980
				static_assert(offsetof(mm7::Player, itemRing5) == 6528);
				int32_t itemRing6; // .6532, 0x1984
				static_assert(offsetof(mm7::Player, itemRing6) == 6532);
			};
		};
		SKIP(198);
		int8_t spellBookPage; // .6734, 0x1A4E
		static_assert(offsetof(mm7::Player, spellBookPage) == 6734);
		uint8_t quickSpell; // .6735, 0x1A4F
		static_assert(offsetof(mm7::Player, quickSpell) == 6735);
		std::array<uint8_t, 64> playerBits; // MMExt: 1..512, here 0..511 | array of abits (real index = 7 - usual) | .6736, 0x1A50
		int8_t meleeAttackBonus; // .6800, 0x1A90
		static_assert(offsetof(mm7::Player, meleeAttackBonus) == 6800);
		SKIP(1);
		int8_t meleeDamageBonus; // .6802, 0x1A92
		static_assert(offsetof(mm7::Player, meleeDamageBonus) == 6802);
		SKIP(1);
		int8_t rangedAttackBonus; // .6804, 0x1A94
		static_assert(offsetof(mm7::Player, rangedAttackBonus) == 6804);
		SKIP(1);
		int8_t rangedDamageBonus; // .6806, 0x1A96
		static_assert(offsetof(mm7::Player, rangedDamageBonus) == 6806);
		SKIP(1);
		union
		{
			int8_t fullHPBonus; // .6808, 0x1A98
			static_assert(offsetof(mm7::Player, fullHPBonus) == 6808);
			int8_t fullHitPointsBonus; // .6808, 0x1A98
			static_assert(offsetof(mm7::Player, fullHitPointsBonus) == 6808);
		};
		SKIP(1);
		union
		{
			int8_t fullSpellPointsBonus; // .6810, 0x1A9A
			static_assert(offsetof(mm7::Player, fullSpellPointsBonus) == 6810);
			int8_t fullSPBonus; // .6810, 0x1A9A
			static_assert(offsetof(mm7::Player, fullSPBonus) == 6810);
		};
		SKIP(1);
		int16_t expression; // .6812, 0x1A9C
		static_assert(offsetof(mm7::Player, expression) == 6812);
		int16_t expressionTimePassed; // .6814, 0x1A9E
		static_assert(offsetof(mm7::Player, expressionTimePassed) == 6814);
		int16_t expressionLength; // .6816, 0x1AA0
		static_assert(offsetof(mm7::Player, expressionLength) == 6816);
		SKIP(10);
		std::array<mm7::LloydBeaconSlot, 5> beacons; // .6828, 0x1AAC
		static_assert(offsetof(mm7::Player, beacons) == 6828);
		uint8_t devineInterventionCasts; // .6968, 0x1B38
		static_assert(offsetof(mm7::Player, devineInterventionCasts) == 6968);
		uint8_t armageddonCasts; // .6969, 0x1B39
		static_assert(offsetof(mm7::Player, armageddonCasts) == 6969);
		SKIP(2);
	};
	static_assert(sizeof(mm7::Player) == 0x1B3C, "Invalid \"mm7::Player\" structure size");

	struct GameParty // size: 0xAE3064
	{
		SKIP(5274220);
		std::array<uint8_t, 4> currentPlayer; // Unknown type | .0, 0x0
		SKIP(5690584);
		std::array<std::array<uint8_t, 4>, 4> players; // Unknown type | .0, 0x0
		SKIP(360212);
		int64_t lastRegenerationTime; // .11325036, 0xACCE6C
		static_assert(offsetof(mm7::GameParty, lastRegenerationTime) == 11325036);
		union
		{
			std::array<int64_t, 5> monsHuntReset; // .11325044, 0xACCE74
			static_assert(offsetof(mm7::GameParty, monsHuntReset) == 11325044);
			std::array<int64_t, 5> nextBountyHunt; // .11325044, 0xACCE74
			static_assert(offsetof(mm7::GameParty, nextBountyHunt) == 11325044);
		};
		SKIP(1224);
		std::array<int64_t, 29> history; // MMExt: 1..29, here 0..28 | .11326308, 0xACD364
		static_assert(offsetof(mm7::GameParty, history) == 11326308);
		std::array<int64_t, 20> specialDates; // MMExt: 1..20, here 0..19 | .11326540, 0xACD44C
		static_assert(offsetof(mm7::GameParty, specialDates) == 11326540);
		union
		{
			std::array<int32_t, 3> pos; // .11326700, 0xACD4EC
			static_assert(offsetof(mm7::GameParty, pos) == 11326700);
			struct
			{
				int32_t x; // .11326700, 0xACD4EC
				static_assert(offsetof(mm7::GameParty, x) == 11326700);
				int32_t y; // .11326704, 0xACD4F0
				static_assert(offsetof(mm7::GameParty, y) == 11326704);
				int32_t z; // .11326708, 0xACD4F4
				static_assert(offsetof(mm7::GameParty, z) == 11326708);
			};
		};
		int32_t direction; // .11326712, 0xACD4F8
		static_assert(offsetof(mm7::GameParty, direction) == 11326712);
		int32_t lookAngle; // .11326716, 0xACD4FC
		static_assert(offsetof(mm7::GameParty, lookAngle) == 11326716);
		int32_t lastX; // .11326720, 0xACD500
		static_assert(offsetof(mm7::GameParty, lastX) == 11326720);
		int32_t lastY; // .11326724, 0xACD504
		static_assert(offsetof(mm7::GameParty, lastY) == 11326724);
		int32_t lastZ; // .11326728, 0xACD508
		static_assert(offsetof(mm7::GameParty, lastZ) == 11326728);
		int32_t lastDirection; // .11326732, 0xACD50C
		static_assert(offsetof(mm7::GameParty, lastDirection) == 11326732);
		int32_t lastLookAngle; // .11326736, 0xACD510
		static_assert(offsetof(mm7::GameParty, lastLookAngle) == 11326736);
		int32_t lastEyeLevel; // .11326740, 0xACD514
		static_assert(offsetof(mm7::GameParty, lastEyeLevel) == 11326740);
		int32_t speedX; // .11326744, 0xACD518
		static_assert(offsetof(mm7::GameParty, speedX) == 11326744);
		int32_t speedY; // .11326748, 0xACD51C
		static_assert(offsetof(mm7::GameParty, speedY) == 11326748);
		int32_t speedZ; // .11326752, 0xACD520
		static_assert(offsetof(mm7::GameParty, speedZ) == 11326752);
		SKIP(4);
		int32_t stableZ; // .11326760, 0xACD528
		static_assert(offsetof(mm7::GameParty, stableZ) == 11326760);
		int32_t lastStandFacet; // .11326764, 0xACD52C
		static_assert(offsetof(mm7::GameParty, lastStandFacet) == 11326764);
		SKIP(8);
		int32_t fallStartZ; // .11326776, 0xACD538
		static_assert(offsetof(mm7::GameParty, fallStartZ) == 11326776);
		uint32_t flying; // 4-byte boolean | .11326780, 0xACD53C
		static_assert(offsetof(mm7::GameParty, flying) == 11326780);
		SKIP(32);
		int32_t food; // .11326816, 0xACD560
		static_assert(offsetof(mm7::GameParty, food) == 11326816);
		SKIP(8);
		int32_t gold; // .11326828, 0xACD56C
		static_assert(offsetof(mm7::GameParty, gold) == 11326828);
		int32_t bankGold; // .11326832, 0xACD570
		static_assert(offsetof(mm7::GameParty, bankGold) == 11326832);
		int32_t deaths; // .11326836, 0xACD574
		static_assert(offsetof(mm7::GameParty, deaths) == 11326836);
		SKIP(4);
		union
		{
			int32_t pritsonTerms; // .11326844, 0xACD57C
			static_assert(offsetof(mm7::GameParty, pritsonTerms) == 11326844);
			int32_t prisonTerms; // .11326844, 0xACD57C
			static_assert(offsetof(mm7::GameParty, prisonTerms) == 11326844);
		};
		int32_t bountiesCollected; // .11326848, 0xACD580
		static_assert(offsetof(mm7::GameParty, bountiesCollected) == 11326848);
		SKIP(4);
		union
		{
			std::array<int16_t, 5> monsHuntTarget; // .11326856, 0xACD588
			static_assert(offsetof(mm7::GameParty, monsHuntTarget) == 11326856);
			std::array<int16_t, 5> bountyHuntTarget; // .11326856, 0xACD588
			static_assert(offsetof(mm7::GameParty, bountyHuntTarget) == 11326856);
		};
		union
		{
			std::array<uint16_t, 5> bountyHuntKilled; // 2-byte boolean | .11326866, 0xACD592
			static_assert(offsetof(mm7::GameParty, bountyHuntKilled) == 11326866);
			std::array<int16_t, 5> monsHuntKilled; // .11326866, 0xACD592
			static_assert(offsetof(mm7::GameParty, monsHuntKilled) == 11326866);
		};
		SKIP(1);
		std::array<uint8_t, 64> QBits; // MMExt: 1..512, here 0..511 | array of abits (real index = 7 - usual) | .11326877, 0xACD59D
		std::array<bool, 16> arcomageWins; // MMExt: 108..123, here 0..15 | .11326941, 0xACD5DD
		static_assert(offsetof(mm7::GameParty, arcomageWins) == 11326941);
		int8_t inArenaQuest; // .11326957, 0xACD5ED
		static_assert(offsetof(mm7::GameParty, inArenaQuest) == 11326957);
		int8_t arenaWinsPage; // .11326958, 0xACD5EE
		static_assert(offsetof(mm7::GameParty, arenaWinsPage) == 11326958);
		int8_t arenaWinsSquire; // .11326959, 0xACD5EF
		static_assert(offsetof(mm7::GameParty, arenaWinsSquire) == 11326959);
		int8_t arenaWinsKnight; // .11326960, 0xACD5F0
		static_assert(offsetof(mm7::GameParty, arenaWinsKnight) == 11326960);
		int8_t arenaWinsLord; // .11326961, 0xACD5F1
		static_assert(offsetof(mm7::GameParty, arenaWinsLord) == 11326961);
		std::array<bool, 68> artifactsFound; // MMExt: 500..567, here 0..67 | .11326962, 0xACD5F2
		static_assert(offsetof(mm7::GameParty, artifactsFound) == 11326962);
		std::array<uint8_t, 31> autonotesBits; // MMExt: 1..255, here 0..254 | array of abits (real index = 7 - usual) | .11327030, 0xACD636
		SKIP(107);
		int32_t alignment; // .11327168, 0xACD6C0
		static_assert(offsetof(mm7::GameParty, alignment) == 11327168);
		union
		{
			std::array<mm7::SpellBuff, 20> spellBuffs; // .11327172, 0xACD6C4
			static_assert(offsetof(mm7::GameParty, spellBuffs) == 11327172);
			struct
			{
				// uint8_t* reputation; // real size is 0 | Unknown type | .0, 0x0
			};
		};
		std::array<mm7::Player, 4> playersArray; // .11327492, 0xACD804
		static_assert(offsetof(mm7::GameParty, playersArray) == 11327492);
		std::array<mm7::NPC, 2> hiredNPC; // MMExt: 1..2, here 0..1 | .11355380, 0xAD44F4
		static_assert(offsetof(mm7::GameParty, hiredNPC) == 11355380);
		SKIP(36);
		union
		{
			int32_t stateBits; // .11355568, 0xAD45B0
			static_assert(offsetof(mm7::GameParty, stateBits) == 11355568);
			struct
			{
				SKIPBITS(1);
				bool needRender : 1; // .11355568, 0xAD45B0
				bool drowning : 1; // .11355568, 0xAD45B0
				bool inAir : 1; // .11355568, 0xAD45B0
				bool enemyDetectorRed : 1; // .11355568, 0xAD45B0
				bool enemyDetectorYellow : 1; // .11355568, 0xAD45B0
				bool flyingBit : 1; // .11355568, 0xAD45B0
				bool waterWalkingBit : 1; // .11355568, 0xAD45B0
				bool inJumpSpell : 1; // .11355569, 0xAD45B1
				bool inLava : 1; // .11355569, 0xAD45B1
			};
		};
		SKIP(59640);
		std::array<std::array<char, 100>, 2> hiredNPCName; // MMExt: 1..2, here 0..1 | requires null terminator | .0, 0x0
		SKIP(236);
		int32_t fine; // .11415648, 0xAE3060
		static_assert(offsetof(mm7::GameParty, fine) == 11415648);
	};
	static_assert(sizeof(mm7::GameParty) == 0xAE3064, "Invalid \"mm7::GameParty\" structure size");

	struct MapChest // size: 0x14CC
	{
		int16_t chestPicture; // .0, 0x0
		union
		{
			uint16_t bits; // .2, 0x2
			static_assert(offsetof(mm7::MapChest, bits) == 2);
			struct
			{
				bool trapped : 1; // .2, 0x2
				bool itemsPlaced : 1; // .2, 0x2
				bool identified : 1; // .2, 0x2
			};
		};
		std::array<mm7::Item, 140> items; // MMExt: 1..140, here 0..139 | .4, 0x4
		static_assert(offsetof(mm7::MapChest, items) == 4);
		std::array<int16_t, 140> inventory; // .5044, 0x13B4
		static_assert(offsetof(mm7::MapChest, inventory) == 5044);
	};
	static_assert(sizeof(mm7::MapChest) == 0x14CC, "Invalid \"mm7::MapChest\" structure size");

	struct MapMonster // size: 0x344
	{
		SKIP(32);
		int16_t NPC_ID; // .32, 0x20
		static_assert(offsetof(mm7::MapMonster, NPC_ID) == 32);
		SKIP(2);
		union
		{
			uint32_t bits; // .36, 0x24
			static_assert(offsetof(mm7::MapMonster, bits) == 36);
			struct
			{
				SKIPBITS(8); // skipping 1 bytes and 2 bits, in total 10 bits
				SKIPBITS(2);
				bool active : 1; // .37, 0x25
				SKIPBITS(4);
				bool showOnMap : 1; // .37, 0x25
				bool invisible : 1; // .38, 0x26
				bool noFlee : 1; // .38, 0x26
				SKIPBITS(1);
				bool hostile : 1; // .38, 0x26
				bool onAlertMap : 1; // .38, 0x26
				SKIPBITS(2);
				bool treasureGenerated : 1; // .38, 0x26
				bool showAsHostile : 1; // .39, 0x27
			};
		};
		union
		{
			int16_t hitPoints; // .40, 0x28
			static_assert(offsetof(mm7::MapMonster, hitPoints) == 40);
			int16_t HP; // .40, 0x28
			static_assert(offsetof(mm7::MapMonster, HP) == 40);
		};
		SKIP(10);
		uint8_t level; // .52, 0x34
		static_assert(offsetof(mm7::MapMonster, level) == 52);
		uint8_t treasureItemPercent; // .53, 0x35
		static_assert(offsetof(mm7::MapMonster, treasureItemPercent) == 53);
		uint8_t treasureDiceCount; // .54, 0x36
		static_assert(offsetof(mm7::MapMonster, treasureDiceCount) == 54);
		uint8_t treasureDiceSides; // .55, 0x37
		static_assert(offsetof(mm7::MapMonster, treasureDiceSides) == 55);
		uint8_t treasureItemLevel; // .56, 0x38
		static_assert(offsetof(mm7::MapMonster, treasureItemLevel) == 56);
		uint8_t treasureItemType; // .57, 0x39
		static_assert(offsetof(mm7::MapMonster, treasureItemType) == 57);
		uint8_t fly; // .58, 0x3A
		static_assert(offsetof(mm7::MapMonster, fly) == 58);
		uint8_t moveType; // .59, 0x3B
		static_assert(offsetof(mm7::MapMonster, moveType) == 59);
		uint8_t AIType; // .60, 0x3C
		static_assert(offsetof(mm7::MapMonster, AIType) == 60);
		uint8_t hostileType; // .61, 0x3D
		static_assert(offsetof(mm7::MapMonster, hostileType) == 61);
		SKIP(1);
		uint8_t bonus; // .63, 0x3F
		static_assert(offsetof(mm7::MapMonster, bonus) == 63);
		uint8_t bonusMul; // .64, 0x40
		static_assert(offsetof(mm7::MapMonster, bonusMul) == 64);
		mm7::MonsterAttackInfo attack1; // .65, 0x41
		static_assert(offsetof(mm7::MapMonster, attack1) == 65);
		uint8_t attack2Chance; // .70, 0x46
		static_assert(offsetof(mm7::MapMonster, attack2Chance) == 70);
		mm7::MonsterAttackInfo attack2; // .71, 0x47
		static_assert(offsetof(mm7::MapMonster, attack2) == 71);
		uint8_t spellChance; // .76, 0x4C
		static_assert(offsetof(mm7::MapMonster, spellChance) == 76);
		uint8_t spell; // .77, 0x4D
		static_assert(offsetof(mm7::MapMonster, spell) == 77);
		uint8_t spell2Chance; // .78, 0x4E
		static_assert(offsetof(mm7::MapMonster, spell2Chance) == 78);
		uint8_t spell2; // .79, 0x4F
		static_assert(offsetof(mm7::MapMonster, spell2) == 79);
		uint8_t fireResistance; // .80, 0x50
		static_assert(offsetof(mm7::MapMonster, fireResistance) == 80);
		uint8_t airResistance; // .81, 0x51
		static_assert(offsetof(mm7::MapMonster, airResistance) == 81);
		uint8_t waterResistance; // .82, 0x52
		static_assert(offsetof(mm7::MapMonster, waterResistance) == 82);
		uint8_t earthResistance; // .83, 0x53
		static_assert(offsetof(mm7::MapMonster, earthResistance) == 83);
		uint8_t mindResistance; // .84, 0x54
		static_assert(offsetof(mm7::MapMonster, mindResistance) == 84);
		uint8_t spiritResistance; // .85, 0x55
		static_assert(offsetof(mm7::MapMonster, spiritResistance) == 85);
		uint8_t bodyResistance; // .86, 0x56
		static_assert(offsetof(mm7::MapMonster, bodyResistance) == 86);
		uint8_t lightResistance; // .87, 0x57
		static_assert(offsetof(mm7::MapMonster, lightResistance) == 87);
		uint8_t darkResistance; // .88, 0x58
		static_assert(offsetof(mm7::MapMonster, darkResistance) == 88);
		uint8_t physResistance; // .89, 0x59
		static_assert(offsetof(mm7::MapMonster, physResistance) == 89);
		uint8_t special; // .90, 0x5A
		static_assert(offsetof(mm7::MapMonster, special) == 90);
		uint8_t specialA; // .91, 0x5B
		static_assert(offsetof(mm7::MapMonster, specialA) == 91);
		uint8_t specialB; // .92, 0x5C
		static_assert(offsetof(mm7::MapMonster, specialB) == 92);
		uint8_t specialC; // .93, 0x5D
		static_assert(offsetof(mm7::MapMonster, specialC) == 93);
		uint8_t prefNum; // .94, 0x5E
		static_assert(offsetof(mm7::MapMonster, prefNum) == 94);
		SKIP(1);
		uint16_t id; // .96, 0x60
		static_assert(offsetof(mm7::MapMonster, id) == 96);
		uint16_t bloodSplat; // .98, 0x62
		static_assert(offsetof(mm7::MapMonster, bloodSplat) == 98);
		uint16_t spellSkill; // .100, 0x64
		static_assert(offsetof(mm7::MapMonster, spellSkill) == 100);
		uint16_t spell2Skill; // .102, 0x66
		static_assert(offsetof(mm7::MapMonster, spell2Skill) == 102);
		uint16_t specialD; // .104, 0x68
		static_assert(offsetof(mm7::MapMonster, specialD) == 104);
		SKIP(2);
		union
		{
			int32_t fullHP; // .108, 0x6C
			static_assert(offsetof(mm7::MapMonster, fullHP) == 108);
			int32_t fullHitPoints; // .108, 0x6C
			static_assert(offsetof(mm7::MapMonster, fullHitPoints) == 108);
		};
		int32_t armorClass; // .112, 0x70
		static_assert(offsetof(mm7::MapMonster, armorClass) == 112);
		union
		{
			int32_t exp; // .116, 0x74
			static_assert(offsetof(mm7::MapMonster, exp) == 116);
			int32_t experience; // .116, 0x74
			static_assert(offsetof(mm7::MapMonster, experience) == 116);
		};
		int32_t moveSpeed; // .120, 0x78
		static_assert(offsetof(mm7::MapMonster, moveSpeed) == 120);
		int32_t attackRecovery; // .124, 0x7C
		static_assert(offsetof(mm7::MapMonster, attackRecovery) == 124);
		int32_t prefClass; // .128, 0x80
		static_assert(offsetof(mm7::MapMonster, prefClass) == 128);
		int16_t rangeAttack; // .132, 0x84
		static_assert(offsetof(mm7::MapMonster, rangeAttack) == 132);
		int16_t id2; // .134, 0x86
		static_assert(offsetof(mm7::MapMonster, id2) == 134);
		int16_t bodyRadius; // .136, 0x88
		static_assert(offsetof(mm7::MapMonster, bodyRadius) == 136);
		int16_t bodyHeight; // .138, 0x8A
		static_assert(offsetof(mm7::MapMonster, bodyHeight) == 138);
		int16_t velocity; // .140, 0x8C
		static_assert(offsetof(mm7::MapMonster, velocity) == 140);
		union
		{
			std::array<int16_t, 3> pos; // .142, 0x8E
			static_assert(offsetof(mm7::MapMonster, pos) == 142);
			struct
			{
				int16_t x; // .142, 0x8E
				static_assert(offsetof(mm7::MapMonster, x) == 142);
				int16_t y; // .144, 0x90
				static_assert(offsetof(mm7::MapMonster, y) == 144);
				int16_t z; // .146, 0x92
				static_assert(offsetof(mm7::MapMonster, z) == 146);
			};
		};
		int16_t velocityX; // .148, 0x94
		static_assert(offsetof(mm7::MapMonster, velocityX) == 148);
		int16_t velocityY; // .150, 0x96
		static_assert(offsetof(mm7::MapMonster, velocityY) == 150);
		int16_t velocityZ; // .152, 0x98
		static_assert(offsetof(mm7::MapMonster, velocityZ) == 152);
		int16_t direction; // .154, 0x9A
		static_assert(offsetof(mm7::MapMonster, direction) == 154);
		int16_t lookAngle; // .156, 0x9C
		static_assert(offsetof(mm7::MapMonster, lookAngle) == 156);
		int16_t room; // .158, 0x9E
		static_assert(offsetof(mm7::MapMonster, room) == 158);
		int16_t currentActionLength; // .160, 0xA0
		static_assert(offsetof(mm7::MapMonster, currentActionLength) == 160);
		int16_t startX; // .162, 0xA2
		static_assert(offsetof(mm7::MapMonster, startX) == 162);
		int16_t startY; // .164, 0xA4
		static_assert(offsetof(mm7::MapMonster, startY) == 164);
		int16_t startZ; // .166, 0xA6
		static_assert(offsetof(mm7::MapMonster, startZ) == 166);
		int16_t guardX; // .168, 0xA8
		static_assert(offsetof(mm7::MapMonster, guardX) == 168);
		int16_t guardY; // .170, 0xAA
		static_assert(offsetof(mm7::MapMonster, guardY) == 170);
		int16_t guardZ; // .172, 0xAC
		static_assert(offsetof(mm7::MapMonster, guardZ) == 172);
		int16_t guardRadius; // .174, 0xAE
		static_assert(offsetof(mm7::MapMonster, guardRadius) == 174);
		int16_t AIState; // .176, 0xB0
		static_assert(offsetof(mm7::MapMonster, AIState) == 176);
		int16_t graphicState; // .178, 0xB2
		static_assert(offsetof(mm7::MapMonster, graphicState) == 178);
		int16_t item; // .180, 0xB4
		static_assert(offsetof(mm7::MapMonster, item) == 180);
		SKIP(2);
		int32_t currentActionStep; // .184, 0xB8
		static_assert(offsetof(mm7::MapMonster, currentActionStep) == 184);
		union
		{
			std::array<int16_t, 8> frames; // .188, 0xBC
			static_assert(offsetof(mm7::MapMonster, frames) == 188);
			struct
			{
				int16_t framesStand; // .188, 0xBC
				static_assert(offsetof(mm7::MapMonster, framesStand) == 188);
				int16_t framesWalk; // .190, 0xBE
				static_assert(offsetof(mm7::MapMonster, framesWalk) == 190);
				int16_t framesAttack; // .192, 0xC0
				static_assert(offsetof(mm7::MapMonster, framesAttack) == 192);
				int16_t framesShoot; // .194, 0xC2
				static_assert(offsetof(mm7::MapMonster, framesShoot) == 194);
				union
				{
					int16_t framesGotHit; // .196, 0xC4
					static_assert(offsetof(mm7::MapMonster, framesGotHit) == 196);
					int16_t framesStun; // .196, 0xC4
					static_assert(offsetof(mm7::MapMonster, framesStun) == 196);
				};
				int16_t framesDie; // .198, 0xC6
				static_assert(offsetof(mm7::MapMonster, framesDie) == 198);
				int16_t framesDead; // .200, 0xC8
				static_assert(offsetof(mm7::MapMonster, framesDead) == 200);
				int16_t framesFidget; // .202, 0xCA
				static_assert(offsetof(mm7::MapMonster, framesFidget) == 202);
			};
		};
		union
		{
			std::array<int16_t, 4> sounds; // .204, 0xCC
			static_assert(offsetof(mm7::MapMonster, sounds) == 204);
			struct
			{
				int16_t soundAttack; // .204, 0xCC
				static_assert(offsetof(mm7::MapMonster, soundAttack) == 204);
				int16_t soundDie; // .206, 0xCE
				static_assert(offsetof(mm7::MapMonster, soundDie) == 206);
				union
				{
					int16_t soundGetHit; // .208, 0xD0
					static_assert(offsetof(mm7::MapMonster, soundGetHit) == 208);
					int16_t soundGotHit; // .208, 0xD0
					static_assert(offsetof(mm7::MapMonster, soundGotHit) == 208);
				};
				int16_t soundFidget; // .210, 0xD2
				static_assert(offsetof(mm7::MapMonster, soundFidget) == 210);
			};
		};
		std::array<mm7::SpellBuff, 22> spellBuffs; // .212, 0xD4
		static_assert(offsetof(mm7::MapMonster, spellBuffs) == 212);
		std::array<mm7::Item, 4> items; // .564, 0x234
		static_assert(offsetof(mm7::MapMonster, items) == 564);
		int32_t group; // .708, 0x2C4
		static_assert(offsetof(mm7::MapMonster, group) == 708);
		int32_t ally; // .712, 0x2C8
		static_assert(offsetof(mm7::MapMonster, ally) == 712);
		std::array<mm7::MonsterSchedule, 8> schedules; // .716, 0x2CC
		static_assert(offsetof(mm7::MapMonster, schedules) == 716);
		int32_t summoner; // .812, 0x32C
		static_assert(offsetof(mm7::MapMonster, summoner) == 812);
		int32_t lastAttacker; // .816, 0x330
		static_assert(offsetof(mm7::MapMonster, lastAttacker) == 816);
		int32_t nameId; // .820, 0x334
		static_assert(offsetof(mm7::MapMonster, nameId) == 820);
		SKIP(12);
	};
	static_assert(sizeof(mm7::MapMonster) == 0x344, "Invalid \"mm7::MapMonster\" structure size");

	struct DialogLogic // size: 0x5C4430
	{
		SKIP(5122552);
		std::array<int32_t, 5> armorSkills; // Requires unprotect before change | .5122552, 0x4E29F8
		static_assert(offsetof(mm7::DialogLogic, armorSkills) == 5122552);
		std::array<int32_t, 9> weaponSkills; // Requires unprotect before change | .5122572, 0x4E2A0C
		static_assert(offsetof(mm7::DialogLogic, weaponSkills) == 5122572);
		std::array<int32_t, 12> miscSkills; // Requires unprotect before change | .5122608, 0x4E2A30
		static_assert(offsetof(mm7::DialogLogic, miscSkills) == 5122608);
		std::array<int32_t, 9> magicSkills; // Requires unprotect before change | .5122656, 0x4E2A60
		static_assert(offsetof(mm7::DialogLogic, magicSkills) == 5122656);
		SKIP(145688);
		int32_t scrollPage; // .5268380, 0x50639C
		static_assert(offsetof(mm7::DialogLogic, scrollPage) == 5268380);
		int32_t countOnScreen; // .5268384, 0x5063A0
		static_assert(offsetof(mm7::DialogLogic, countOnScreen) == 5268384);
		union
		{
			int32_t listCount; // .5268388, 0x5063A4
			static_assert(offsetof(mm7::DialogLogic, listCount) == 5268388);
			uint32_t list_size; // .5268388, 0x5063A4
			static_assert(offsetof(mm7::DialogLogic, list_size) == 5268388);
		};
		int32_t scrollPos; // .5268392, 0x5063A8
		static_assert(offsetof(mm7::DialogLogic, scrollPos) == 5268392);
		uint32_t autonoteTab6Clicked; // 4-byte boolean | .5268396, 0x5063AC
		static_assert(offsetof(mm7::DialogLogic, autonoteTab6Clicked) == 5268396);
		uint32_t autonoteTab5Clicked; // 4-byte boolean | .5268400, 0x5063B0
		static_assert(offsetof(mm7::DialogLogic, autonoteTab5Clicked) == 5268400);
		union
		{
			uint32_t autonoteTab4Clicked; // 4-byte boolean | .5268404, 0x5063B4
			static_assert(offsetof(mm7::DialogLogic, autonoteTab4Clicked) == 5268404);
			uint32_t mapMoveRightClicked; // 4-byte boolean | .5268404, 0x5063B4
			static_assert(offsetof(mm7::DialogLogic, mapMoveRightClicked) == 5268404);
		};
		union
		{
			uint32_t autonoteTab3Clicked; // 4-byte boolean | .5268408, 0x5063B8
			static_assert(offsetof(mm7::DialogLogic, autonoteTab3Clicked) == 5268408);
			uint32_t mapMoveLeftClicked; // 4-byte boolean | .5268408, 0x5063B8
			static_assert(offsetof(mm7::DialogLogic, mapMoveLeftClicked) == 5268408);
		};
		union
		{
			uint32_t autonoteTab2Clicked; // 4-byte boolean | .5268412, 0x5063BC
			static_assert(offsetof(mm7::DialogLogic, autonoteTab2Clicked) == 5268412);
			uint32_t mapMoveDownClicked; // 4-byte boolean | .5268412, 0x5063BC
			static_assert(offsetof(mm7::DialogLogic, mapMoveDownClicked) == 5268412);
		};
		union
		{
			uint32_t autonoteTab1Clicked; // 4-byte boolean | .5268416, 0x5063C0
			static_assert(offsetof(mm7::DialogLogic, autonoteTab1Clicked) == 5268416);
			uint32_t mapMoveUpClicked; // 4-byte boolean | .5268416, 0x5063C0
			static_assert(offsetof(mm7::DialogLogic, mapMoveUpClicked) == 5268416);
		};
		uint32_t scrollDownClicked; // 4-byte boolean | .5268420, 0x5063C4
		static_assert(offsetof(mm7::DialogLogic, scrollDownClicked) == 5268420);
		uint32_t scrollUpClicked; // 4-byte boolean | .5268424, 0x5063C8
		static_assert(offsetof(mm7::DialogLogic, scrollUpClicked) == 5268424);
		int32_t spellBookSelection; // .5268428, 0x5063CC
		static_assert(offsetof(mm7::DialogLogic, spellBookSelection) == 5268428);
		bool spellBookSelectedNewSpell; // .5268432, 0x5063D0
		static_assert(offsetof(mm7::DialogLogic, spellBookSelectedNewSpell) == 5268432);
		SKIP(23);
		int32_t autonotesCategory; // .5268456, 0x5063E8
		static_assert(offsetof(mm7::DialogLogic, autonotesCategory) == 5268456);
		SKIP(20);
		mm7::MapMonster monsterInfoMonster; // .5268480, 0x506400
		static_assert(offsetof(mm7::DialogLogic, monsterInfoMonster) == 5268480);
		SKIP(773452);
		std::array<int32_t, 1000> list; // size offset is 0x5063A4 | .6042768, 0x5C3490
		static_assert(offsetof(mm7::DialogLogic, list) == 6042768);
	};
	static_assert(sizeof(mm7::DialogLogic) == 0x5C4430, "Invalid \"mm7::DialogLogic\" structure size");

	struct MapObject // size: 0x70
	{
		int16_t type; // .0, 0x0
		int16_t typeIndex; // .2, 0x2
		static_assert(offsetof(mm7::MapObject, typeIndex) == 2);
		union
		{
			std::array<int32_t, 3> pos; // .4, 0x4
			static_assert(offsetof(mm7::MapObject, pos) == 4);
			struct
			{
				int32_t x; // .4, 0x4
				static_assert(offsetof(mm7::MapObject, x) == 4);
				int32_t y; // .8, 0x8
				static_assert(offsetof(mm7::MapObject, y) == 8);
				int32_t z; // .12, 0xC
				static_assert(offsetof(mm7::MapObject, z) == 12);
			};
		};
		union
		{
			std::array<int16_t, 3> velocity; // .16, 0x10
			static_assert(offsetof(mm7::MapObject, velocity) == 16);
			struct
			{
				int16_t velocityX; // .16, 0x10
				static_assert(offsetof(mm7::MapObject, velocityX) == 16);
				int16_t velocityY; // .18, 0x12
				static_assert(offsetof(mm7::MapObject, velocityY) == 18);
				int16_t velocityZ; // .20, 0x14
				static_assert(offsetof(mm7::MapObject, velocityZ) == 20);
			};
		};
		int16_t direction; // .22, 0x16
		static_assert(offsetof(mm7::MapObject, direction) == 22);
		int16_t lookAngle; // .24, 0x18
		static_assert(offsetof(mm7::MapObject, lookAngle) == 24);
		union
		{
			uint16_t bits; // .26, 0x1A
			static_assert(offsetof(mm7::MapObject, bits) == 26);
			struct
			{
				bool visible : 1; // .26, 0x1A
				bool temporary : 1; // .26, 0x1A
				bool haltTurnBased : 1; // .26, 0x1A
				bool droppedByPlayer : 1; // .26, 0x1A
				bool ignoreRange : 1; // .26, 0x1A
				bool noZBuffer : 1; // .26, 0x1A
				bool skipAFrame : 1; // .26, 0x1A
				bool attachToHead : 1; // .26, 0x1A
				bool missile : 1; // .27, 0x1B
				bool removed : 1; // .27, 0x1B
			};
		};
		int16_t room; // .28, 0x1C
		static_assert(offsetof(mm7::MapObject, room) == 28);
		int16_t age; // .30, 0x1E
		static_assert(offsetof(mm7::MapObject, age) == 30);
		int16_t maxAge; // .32, 0x20
		static_assert(offsetof(mm7::MapObject, maxAge) == 32);
		int16_t lightMultiplier; // .34, 0x22
		static_assert(offsetof(mm7::MapObject, lightMultiplier) == 34);
		mm7::Item item; // .36, 0x24
		static_assert(offsetof(mm7::MapObject, item) == 36);
		union
		{
			int32_t spell; // .72, 0x48
			static_assert(offsetof(mm7::MapObject, spell) == 72);
			int32_t spellType; // .72, 0x48
			static_assert(offsetof(mm7::MapObject, spellType) == 72);
		};
		int32_t spellSkill; // .76, 0x4C
		static_assert(offsetof(mm7::MapObject, spellSkill) == 76);
		union
		{
			int32_t spellMastery; // .80, 0x50
			static_assert(offsetof(mm7::MapObject, spellMastery) == 80);
			int32_t spellLevel; // .80, 0x50
			static_assert(offsetof(mm7::MapObject, spellLevel) == 80);
		};
		mm7::SpellEffect* spellEffect; // .84, 0x54
		static_assert(offsetof(mm7::MapObject, spellEffect) == 84);
		int32_t owner; // .88, 0x58
		static_assert(offsetof(mm7::MapObject, owner) == 88);
		int32_t target; // .92, 0x5C
		static_assert(offsetof(mm7::MapObject, target) == 92);
		uint8_t range; // .96, 0x60
		static_assert(offsetof(mm7::MapObject, range) == 96);
		uint8_t attackType; // .97, 0x61
		static_assert(offsetof(mm7::MapObject, attackType) == 97);
		SKIP(2);
		union
		{
			std::array<int32_t, 3> startPos; // .100, 0x64
			static_assert(offsetof(mm7::MapObject, startPos) == 100);
			struct
			{
				int32_t startX; // .100, 0x64
				static_assert(offsetof(mm7::MapObject, startX) == 100);
				int32_t startY; // .104, 0x68
				static_assert(offsetof(mm7::MapObject, startY) == 104);
				int32_t startZ; // .108, 0x6C
				static_assert(offsetof(mm7::MapObject, startZ) == 108);
			};
		};
	};
	static_assert(sizeof(mm7::MapObject) == 0x70, "Invalid \"mm7::MapObject\" structure size");

	struct GameMap // size: 0x76D398
	{
		SKIP(5342836);
		std::array<mm7::BaseLight, 400> spriteLights; // size offset is 0x519934 | .5342836, 0x518674
		static_assert(offsetof(mm7::GameMap, spriteLights) == 5342836);
		uint32_t spriteLights_size; // .5347636, 0x519934
		static_assert(offsetof(mm7::GameMap, spriteLights_size) == 5347636);
		SKIP(831960);
		std::array<uint8_t, 200> vars; // .6179600, 0x5E4B10
		static_assert(offsetof(mm7::GameMap, vars) == 6179600);
		SKIP(1016);
		std::array<mm7::MapChest, 20> chests; // size offset is 0x5FEFC0 | .6180816, 0x5E4FD0
		static_assert(offsetof(mm7::GameMap, chests) == 6180816);
		uint32_t chests_size; // .6287296, 0x5FEFC0
		static_assert(offsetof(mm7::GameMap, chests_size) == 6287296);
		SKIP(20);
		std::array<mm7::MapMonster, 500> monsters; // size offset is 0x6650A8 | .6287320, 0x5FEFD8
		static_assert(offsetof(mm7::GameMap, monsters) == 6287320);
		uint32_t monsters_size; // .6705320, 0x6650A8
		static_assert(offsetof(mm7::GameMap, monsters_size) == 6705320);
		uint32_t objects_size; // .6705324, 0x6650AC
		static_assert(offsetof(mm7::GameMap, objects_size) == 6705324);
		std::array<mm7::MapObject, 1000> objects; // size offset is 0x6650AC | .6705328, 0x6650B0
		static_assert(offsetof(mm7::GameMap, objects) == 6705328);
		SKIP(8);
		std::array<int32_t, 10> soundSprites; // size offset is 0x680660 | .6817336, 0x680638
		static_assert(offsetof(mm7::GameMap, soundSprites) == 6817336);
		uint32_t soundSprites_size; // .6817376, 0x680660
		static_assert(offsetof(mm7::GameMap, soundSprites_size) == 6817376);
		SKIP(12012);
		std::array<mm7::MapSprite, 3000> sprites; // size offset is 0x69AC50 | .6829392, 0x683550
		static_assert(offsetof(mm7::GameMap, sprites) == 6829392);
		uint32_t sprites_size; // .6925392, 0x69AC50
		static_assert(offsetof(mm7::GameMap, sprites_size) == 6925392);
		SKIP(24604);
		union
		{
			mm7::OdmHeader outdoorHeader; // .6950000, 0x6A0C70
			static_assert(offsetof(mm7::GameMap, outdoorHeader) == 6950000);
			struct
			{
				SKIP(160);
				std::array<mm7::TilesetDef, 4> tilesets; // .6950160, 0x6A0D10
				static_assert(offsetof(mm7::GameMap, tilesets) == 6950160);
			};
		};
		uint32_t models_size; // .6950176, 0x6A0D20
		static_assert(offsetof(mm7::GameMap, models_size) == 6950176);
		std::array<std::array<uint8_t, 128>, 128>* heightMap; // .6950180, 0x6A0D24
		static_assert(offsetof(mm7::GameMap, heightMap) == 6950180);
		std::array<std::array<uint8_t, 128>, 128>* tileMap; // .6950184, 0x6A0D28
		static_assert(offsetof(mm7::GameMap, tileMap) == 6950184);
		std::array<std::array<uint8_t, 128>, 128>* unknownMap; // .6950188, 0x6A0D2C
		static_assert(offsetof(mm7::GameMap, unknownMap) == 6950188);
		SKIP(24);
		mm7::MapModel* models; // size offset is 0x6A0D20 | .6950216, 0x6A0D48
		static_assert(offsetof(mm7::GameMap, models) == 6950216);
		uint32_t IDList_size; // .6950220, 0x6A0D4C
		static_assert(offsetof(mm7::GameMap, IDList_size) == 6950220);
		mm7::ObjectRef2* IDList; // size offset is 0x6A0D4C | .6950224, 0x6A0D50
		static_assert(offsetof(mm7::GameMap, IDList) == 6950224);
		std::array<std::array<int32_t, 128>, 128>* IDOffsets; // .6950228, 0x6A0D54
		static_assert(offsetof(mm7::GameMap, IDOffsets) == 6950228);
		int32_t loadedSkyBitmap; // .6950232, 0x6A0D58
		static_assert(offsetof(mm7::GameMap, loadedSkyBitmap) == 6950232);
		SKIP(980);
		uint32_t outdoorSpawns_size; // .6951216, 0x6A1130
		static_assert(offsetof(mm7::GameMap, outdoorSpawns_size) == 6951216);
		mm7::SpawnPoint* outdoorSpawns; // size offset is 0x6A1130 | .6951220, 0x6A1134
		static_assert(offsetof(mm7::GameMap, outdoorSpawns) == 6951220);
		int32_t outdoorRefillCount; // .6951224, 0x6A1138
		static_assert(offsetof(mm7::GameMap, outdoorRefillCount) == 6951224);
		uint32_t outdoorLastRefillDay; // .6951228, 0x6A113C
		static_assert(offsetof(mm7::GameMap, outdoorLastRefillDay) == 6951228);
		int32_t outdoorReputation; // .6951232, 0x6A1140
		static_assert(offsetof(mm7::GameMap, outdoorReputation) == 6951232);
		SKIP(4);
		int32_t outdoorSanityFacetsCount; // .6951240, 0x6A1148
		static_assert(offsetof(mm7::GameMap, outdoorSanityFacetsCount) == 6951240);
		int32_t outdoorSanitySpritesCount; // .6951244, 0x6A114C
		static_assert(offsetof(mm7::GameMap, outdoorSanitySpritesCount) == 6951244);
		int32_t sanityModelsCount; // .6951248, 0x6A1150
		static_assert(offsetof(mm7::GameMap, sanityModelsCount) == 6951248);
		SKIP(12);
		union
		{
			mm7::MapExtra outdoorExtra; // .6951264, 0x6A1160
			static_assert(offsetof(mm7::GameMap, outdoorExtra) == 6951264);
			struct
			{
				int64_t outdoorLastVisitTime; // .6951264, 0x6A1160
				static_assert(offsetof(mm7::GameMap, outdoorLastVisitTime) == 6951264);
			};
		};
		std::array<std::array<uint8_t, 11>, 88> visibleMap1; // array of abits (real index = 7 - usual) | .6951320, 0x6A1198
		std::array<std::array<uint8_t, 11>, 88> visibleMap2; // array of abits (real index = 7 - usual) | .6952288, 0x6A1560
		SKIP(116372);
		int32_t mapStatsIndex; // .7069628, 0x6BDFBC
		static_assert(offsetof(mm7::GameMap, mapStatsIndex) == 7069628);
		SKIP(516);
		std::array<uint8_t, 20> name; // Unknown type | .0, 0x0
		SKIP(8);
		uint32_t indoorOrOutdoor; // .7070176, 0x6BE1E0
		static_assert(offsetof(mm7::GameMap, indoorOrOutdoor) == 7070176);
		SKIP(97);
		bool noNPC; // .7070277, 0x6BE245
		static_assert(offsetof(mm7::GameMap, noNPC) == 7070277);
		SKIP(490);
		mm7::BlvHeader indoorHeader; // .7070768, 0x6BE430
		static_assert(offsetof(mm7::GameMap, indoorHeader) == 7070768);
		uint32_t vertexes_size; // .7070904, 0x6BE4B8
		static_assert(offsetof(mm7::GameMap, vertexes_size) == 7070904);
		mm7::MapVertex* vertexes; // size offset is 0x6BE4B8 | .7070908, 0x6BE4BC
		static_assert(offsetof(mm7::GameMap, vertexes) == 7070908);
		uint32_t facets_size; // .7070912, 0x6BE4C0
		static_assert(offsetof(mm7::GameMap, facets_size) == 7070912);
		mm7::MapFacet* facets; // size offset is 0x6BE4C0 | .7070916, 0x6BE4C4
		static_assert(offsetof(mm7::GameMap, facets) == 7070916);
		uint32_t facetData_size; // .7070920, 0x6BE4C8
		static_assert(offsetof(mm7::GameMap, facetData_size) == 7070920);
		mm7::FacetData* facetData; // size offset is 0x6BE4C8 | .7070924, 0x6BE4CC
		static_assert(offsetof(mm7::GameMap, facetData) == 7070924);
		uint32_t rooms_size; // .7070928, 0x6BE4D0
		static_assert(offsetof(mm7::GameMap, rooms_size) == 7070928);
		mm7::MapRoom* rooms; // size offset is 0x6BE4D0 | .7070932, 0x6BE4D4
		static_assert(offsetof(mm7::GameMap, rooms) == 7070932);
		uint32_t lights_size; // .7070936, 0x6BE4D8
		static_assert(offsetof(mm7::GameMap, lights_size) == 7070936);
		mm7::MapLight* lights; // size offset is 0x6BE4D8 | .7070940, 0x6BE4DC
		static_assert(offsetof(mm7::GameMap, lights) == 7070940);
		uint32_t doors_size; // .7070944, 0x6BE4E0
		static_assert(offsetof(mm7::GameMap, doors_size) == 7070944);
		std::array<mm7::MapDoor, 200>* doors; // size offset is 0x6BE4E0 | .7070948, 0x6BE4E4
		static_assert(offsetof(mm7::GameMap, doors) == 7070948);
		uint32_t BSPNodes_size; // .7070952, 0x6BE4E8
		static_assert(offsetof(mm7::GameMap, BSPNodes_size) == 7070952);
		mm7::BSPNode* BSPNodes; // size offset is 0x6BE4E8 | .7070956, 0x6BE4EC
		static_assert(offsetof(mm7::GameMap, BSPNodes) == 7070956);
		mm7::MapOutlines* outlines; // .7070960, 0x6BE4F0
		static_assert(offsetof(mm7::GameMap, outlines) == 7070960);
		SKIP(16);
		uint32_t indoorSpawns_size; // .7070980, 0x6BE504
		static_assert(offsetof(mm7::GameMap, indoorSpawns_size) == 7070980);
		mm7::SpawnPoint* indoorSpawns; // size offset is 0x6BE504 | .7070984, 0x6BE508
		static_assert(offsetof(mm7::GameMap, indoorSpawns) == 7070984);
		int32_t indoorRefillCount; // .7070988, 0x6BE50C
		static_assert(offsetof(mm7::GameMap, indoorRefillCount) == 7070988);
		uint32_t indoorLastRefillDay; // .7070992, 0x6BE510
		static_assert(offsetof(mm7::GameMap, indoorLastRefillDay) == 7070992);
		int32_t indoorReputation; // .7070996, 0x6BE514
		static_assert(offsetof(mm7::GameMap, indoorReputation) == 7070996);
		SKIP(4);
		int32_t indoorSanityFacetsCount; // .7071004, 0x6BE51C
		static_assert(offsetof(mm7::GameMap, indoorSanityFacetsCount) == 7071004);
		int32_t indoorSanitySpritesCount; // .7071008, 0x6BE520
		static_assert(offsetof(mm7::GameMap, indoorSanitySpritesCount) == 7071008);
		std::array<uint8_t, 4> sanityDoorDataSize; // Unknown type | .0, 0x0
		// uint8_t* lastVisitTime; // real size is 0 | Unknown type | .0, 0x0
		// uint8_t* sanitySpritesCount; // real size is 0 | Unknown type | .0, 0x0
		// uint8_t* reputation; // real size is 0 | Unknown type | .0, 0x0
		// uint8_t* spawns; // real size is 0 | Unknown type | .0, 0x0
		// uint8_t* lastRefillDay; // real size is 0 | Unknown type | .0, 0x0
		// uint8_t* sanityFacetsCount; // real size is 0 | Unknown type | .0, 0x0
		// uint8_t* refillCount; // real size is 0 | Unknown type | .0, 0x0
		SKIP(12);
		union
		{
			mm7::MapExtra indoorExtra; // .7071028, 0x6BE534
			static_assert(offsetof(mm7::GameMap, indoorExtra) == 7071028);
			struct
			{
				int64_t indoorLastVisitTime; // .7071028, 0x6BE534
				static_assert(offsetof(mm7::GameMap, indoorLastVisitTime) == 7071028);
			};
		};
		std::array<uint8_t, 875> visibileOutlines; // array of abits (real index = 7 - usual) | .7071084, 0x6BE56C
		SKIP(518841);
		uint32_t terNorm_size; // .7590800, 0x73D390
		static_assert(offsetof(mm7::GameMap, terNorm_size) == 7590800);
		std::array<std::array<std::array<float, 2>, 128>, 128> terNormDist; // .7590804, 0x73D394
		static_assert(offsetof(mm7::GameMap, terNormDist) == 7590804);
		std::array<std::array<std::array<int16_t, 2>, 128>, 128> terNormId; // .7721876, 0x75D394
		static_assert(offsetof(mm7::GameMap, terNormId) == 7721876);
		mm7::FloatVector* terNorm; // size offset is 0x73D390 | .7787412, 0x76D394
		static_assert(offsetof(mm7::GameMap, terNorm) == 7787412);
	};
	static_assert(sizeof(mm7::GameMap) == 0x76D398, "Invalid \"mm7::GameMap\" structure size");

	struct LodRecord // size: 0x48
	{
		uint32_t lodPtr; // .0, 0x0
		uint32_t namePtr; // .4, 0x4
		static_assert(offsetof(mm7::LodRecord, namePtr) == 4);
		std::array<char, 64> name; // requires null terminator | .0, 0x0
	};
	static_assert(sizeof(mm7::LodRecord) == 0x48, "Invalid \"mm7::LodRecord\" structure size");

	struct CustomLods // size: 0x4804
	{
		int32_t recordIndex; // .0, 0x0
		std::array<mm7::LodRecord, 256> records; // .4, 0x4
		static_assert(offsetof(mm7::CustomLods, records) == 4);
	};
	static_assert(sizeof(mm7::CustomLods) == 0x4804, "Invalid \"mm7::CustomLods\" structure size");

	struct PatchOptions // size: 0x178
	{
		int32_t size; // .0, 0x0
		int32_t maxMLookAngle; // .4, 0x4
		static_assert(offsetof(mm7::PatchOptions, maxMLookAngle) == 4);
		uint32_t mouseLook; // 4-byte boolean | .8, 0x8
		static_assert(offsetof(mm7::PatchOptions, mouseLook) == 8);
		uint32_t mouseLookUseAltMode; // 4-byte boolean | .12, 0xC
		static_assert(offsetof(mm7::PatchOptions, mouseLookUseAltMode) == 12);
		uint32_t capsLockToggleMouseLook; // 4-byte boolean | .16, 0x10
		static_assert(offsetof(mm7::PatchOptions, capsLockToggleMouseLook) == 16);
		uint32_t mouseFly; // 4-byte boolean | .20, 0x14
		static_assert(offsetof(mm7::PatchOptions, mouseFly) == 20);
		uint32_t mouseWheelFly; // 4-byte boolean | .24, 0x18
		static_assert(offsetof(mm7::PatchOptions, mouseWheelFly) == 24);
		int32_t mouseLookTempKey; // .28, 0x1C
		static_assert(offsetof(mm7::PatchOptions, mouseLookTempKey) == 28);
		int32_t mouseLookChangeKey; // .32, 0x20
		static_assert(offsetof(mm7::PatchOptions, mouseLookChangeKey) == 32);
		int32_t inventoryKey; // .36, 0x24
		static_assert(offsetof(mm7::PatchOptions, inventoryKey) == 36);
		int32_t charScreenKey; // .40, 0x28
		static_assert(offsetof(mm7::PatchOptions, charScreenKey) == 40);
		int32_t doubleSpeedKey; // .44, 0x2C
		static_assert(offsetof(mm7::PatchOptions, doubleSpeedKey) == 44);
		int32_t quickLoadKey; // .48, 0x30
		static_assert(offsetof(mm7::PatchOptions, quickLoadKey) == 48);
		int32_t autorunKey; // .52, 0x34
		static_assert(offsetof(mm7::PatchOptions, autorunKey) == 52);
		uint32_t HDWTRCount; // .56, 0x38
		static_assert(offsetof(mm7::PatchOptions, HDWTRCount) == 56);
		uint32_t HDWTRDelay; // .60, 0x3C
		static_assert(offsetof(mm7::PatchOptions, HDWTRDelay) == 60);
		int32_t horsemanSpeakTime; // .64, 0x40
		static_assert(offsetof(mm7::PatchOptions, horsemanSpeakTime) == 64);
		int32_t boatmanSpeakTime; // .68, 0x44
		static_assert(offsetof(mm7::PatchOptions, boatmanSpeakTime) == 68);
		float paletteSMul; // .72, 0x48
		static_assert(offsetof(mm7::PatchOptions, paletteSMul) == 72);
		float paletteVMul; // .76, 0x4C
		static_assert(offsetof(mm7::PatchOptions, paletteVMul) == 76);
		uint32_t noBitmapsHwl; // 4-byte boolean | .80, 0x50
		static_assert(offsetof(mm7::PatchOptions, noBitmapsHwl) == 80);
		uint32_t playMP3; // 4-byte boolean | .84, 0x54
		static_assert(offsetof(mm7::PatchOptions, playMP3) == 84);
		int32_t musicLoopsCount; // .88, 0x58
		static_assert(offsetof(mm7::PatchOptions, musicLoopsCount) == 88);
		uint32_t hardenArtifacts; // 4-byte boolean | .92, 0x5C
		static_assert(offsetof(mm7::PatchOptions, hardenArtifacts) == 92);
		uint32_t progressiveDaggerTrippleDamage; // 4-byte boolean | .96, 0x60
		static_assert(offsetof(mm7::PatchOptions, progressiveDaggerTrippleDamage) == 96);
		uint32_t fixChests; // 4-byte boolean | .100, 0x64
		static_assert(offsetof(mm7::PatchOptions, fixChests) == 100);
		uint32_t dataFiles; // 4-byte boolean | .104, 0x68
		static_assert(offsetof(mm7::PatchOptions, dataFiles) == 104);
		uint32_t fixDualWeaponsRecovery; // 4-byte boolean | .108, 0x6C
		static_assert(offsetof(mm7::PatchOptions, fixDualWeaponsRecovery) == 108);
		int32_t increaseRecoveryRateStrength; // .112, 0x70
		static_assert(offsetof(mm7::PatchOptions, increaseRecoveryRateStrength) == 112);
		int32_t blasterRecovery; // .116, 0x74
		static_assert(offsetof(mm7::PatchOptions, blasterRecovery) == 116);
		uint32_t fixSkyBitmap; // 4-byte boolean | .120, 0x78
		static_assert(offsetof(mm7::PatchOptions, fixSkyBitmap) == 120);
		uint32_t noCD; // 4-byte boolean | .124, 0x7C
		static_assert(offsetof(mm7::PatchOptions, noCD) == 124);
		uint32_t fixChestsByReorder; // 4-byte boolean | .128, 0x80
		static_assert(offsetof(mm7::PatchOptions, fixChestsByReorder) == 128);
		int32_t lastLoadedFileSize; // .132, 0x84
		static_assert(offsetof(mm7::PatchOptions, lastLoadedFileSize) == 132);
		uint32_t fixTimers; // 4-byte boolean | .136, 0x88
		static_assert(offsetof(mm7::PatchOptions, fixTimers) == 136);
		uint32_t fixMovement; // 4-byte boolean | .140, 0x8C
		static_assert(offsetof(mm7::PatchOptions, fixMovement) == 140);
		int32_t monsterJumpDownLimit; // .144, 0x90
		static_assert(offsetof(mm7::PatchOptions, monsterJumpDownLimit) == 144);
		uint32_t fixHeroismPedestal; // 4-byte boolean | .148, 0x94
		static_assert(offsetof(mm7::PatchOptions, fixHeroismPedestal) == 148);
		uint32_t skipUnsellableItemCheck; // 4-byte boolean | .152, 0x98
		static_assert(offsetof(mm7::PatchOptions, skipUnsellableItemCheck) == 152);
		uint32_t fixGMStaff; // 4-byte boolean | .156, 0x9C
		static_assert(offsetof(mm7::PatchOptions, fixGMStaff) == 156);
		uint32_t fixObelisks; // 4-byte boolean | .160, 0xA0
		static_assert(offsetof(mm7::PatchOptions, fixObelisks) == 160);
		uint32_t borderlessWindowed; // 4-byte boolean | .164, 0xA4
		static_assert(offsetof(mm7::PatchOptions, borderlessWindowed) == 164);
		uint32_t compatibleMovieRender; // 4-byte boolean | .168, 0xA8
		static_assert(offsetof(mm7::PatchOptions, compatibleMovieRender) == 168);
		uint32_t smoothMovieScaling; // 4-byte boolean | .172, 0xAC
		static_assert(offsetof(mm7::PatchOptions, smoothMovieScaling) == 172);
		uint32_t supportTrueColor; // 4-byte boolean | .176, 0xB0
		static_assert(offsetof(mm7::PatchOptions, supportTrueColor) == 176);
		int32_t renderRectLeft; // .180, 0xB4
		static_assert(offsetof(mm7::PatchOptions, renderRectLeft) == 180);
		int32_t renderRectTop; // .184, 0xB8
		static_assert(offsetof(mm7::PatchOptions, renderRectTop) == 184);
		int32_t renderRectRight; // .188, 0xBC
		static_assert(offsetof(mm7::PatchOptions, renderRectRight) == 188);
		int32_t renderRectBottom; // .192, 0xC0
		static_assert(offsetof(mm7::PatchOptions, renderRectBottom) == 192);
		uint32_t fixUnimplementedSpells; // 4-byte boolean | .196, 0xC4
		static_assert(offsetof(mm7::PatchOptions, fixUnimplementedSpells) == 196);
		int32_t indoorMinimapZoomMul; // .200, 0xC8
		static_assert(offsetof(mm7::PatchOptions, indoorMinimapZoomMul) == 200);
		int32_t indoorMinimapZoomPower; // .204, 0xCC
		static_assert(offsetof(mm7::PatchOptions, indoorMinimapZoomPower) == 204);
		uint32_t fixMonsterSummon; // 4-byte boolean | .208, 0xD0
		static_assert(offsetof(mm7::PatchOptions, fixMonsterSummon) == 208);
		uint32_t fixInterfaceBugs; // 4-byte boolean | .212, 0xD4
		static_assert(offsetof(mm7::PatchOptions, fixInterfaceBugs) == 212);
		const char* UILayout; // .216, 0xD8
		static_assert(offsetof(mm7::PatchOptions, UILayout) == 216);
		int32_t paperDollInChests; // .220, 0xDC
		static_assert(offsetof(mm7::PatchOptions, paperDollInChests) == 220);
		uint32_t higherCloseRingsButton; // 4-byte boolean | .224, 0xE0
		static_assert(offsetof(mm7::PatchOptions, higherCloseRingsButton) == 224);
		int32_t renderBottomPixel; // .228, 0xE4
		static_assert(offsetof(mm7::PatchOptions, renderBottomPixel) == 228);
		uint32_t trueColorTextures; // 4-byte boolean | .232, 0xE8
		static_assert(offsetof(mm7::PatchOptions, trueColorTextures) == 232);
		uint32_t resetPalettes; // 4-byte boolean | .236, 0xEC
		static_assert(offsetof(mm7::PatchOptions, resetPalettes) == 236);
		uint32_t fixSFT; // 4-byte boolean | .240, 0xF0
		static_assert(offsetof(mm7::PatchOptions, fixSFT) == 240);
		uint32_t axeGMFullProbabilityAt; // 4-byte boolean | .244, 0xF4
		static_assert(offsetof(mm7::PatchOptions, axeGMFullProbabilityAt) == 244);
		double mouseDX; // .248, 0xF8
		static_assert(offsetof(mm7::PatchOptions, mouseDX) == 248);
		double mouseDY; // .256, 0x100
		static_assert(offsetof(mm7::PatchOptions, mouseDY) == 256);
		uint32_t trueColorSprites; // 4-byte boolean | .264, 0x108
		static_assert(offsetof(mm7::PatchOptions, trueColorSprites) == 264);
		uint32_t fixMonstersBlockingShots; // 4-byte boolean | .268, 0x10C
		static_assert(offsetof(mm7::PatchOptions, fixMonstersBlockingShots) == 268);
		uint32_t fixParalyze; // 4-byte boolean | .272, 0x110
		static_assert(offsetof(mm7::PatchOptions, fixParalyze) == 272);
		uint32_t enableAttackSpell; // 4-byte boolean | .276, 0x114
		static_assert(offsetof(mm7::PatchOptions, enableAttackSpell) == 276);
		int32_t shooterMode; // .280, 0x118
		static_assert(offsetof(mm7::PatchOptions, shooterMode) == 280);
		int32_t maxMLookUpAngle; // .284, 0x11C
		static_assert(offsetof(mm7::PatchOptions, maxMLookUpAngle) == 284);
		uint32_t fixIceBoltBlast; // 4-byte boolean | .288, 0x120
		static_assert(offsetof(mm7::PatchOptions, fixIceBoltBlast) == 288);
		int32_t monSpritesSizeMul; // .292, 0x124
		static_assert(offsetof(mm7::PatchOptions, monSpritesSizeMul) == 292);
		uint32_t fixMonsterAttackTypes; // 4-byte boolean | .296, 0x128
		static_assert(offsetof(mm7::PatchOptions, fixMonsterAttackTypes) == 296);
		uint32_t fixMonsterSpells; // 4-byte boolean | .300, 0x12C
		static_assert(offsetof(mm7::PatchOptions, fixMonsterSpells) == 300);
		uint32_t fixSouldrinker; // 4-byte boolean | .304, 0x130
		static_assert(offsetof(mm7::PatchOptions, fixSouldrinker) == 304);
		int32_t mouseLookPermKey; // .308, 0x134
		static_assert(offsetof(mm7::PatchOptions, mouseLookPermKey) == 308);
		int32_t lastSoundSample; // .312, 0x138
		static_assert(offsetof(mm7::PatchOptions, lastSoundSample) == 312);
		int32_t waterWalkDamage; // .316, 0x13C
		static_assert(offsetof(mm7::PatchOptions, waterWalkDamage) == 316);
		uint32_t fixUnmarkedArtifacts; // 4-byte boolean | .320, 0x140
		static_assert(offsetof(mm7::PatchOptions, fixUnmarkedArtifacts) == 320);
		uint32_t fixClubsDelay; // 4-byte boolean | .324, 0x144
		static_assert(offsetof(mm7::PatchOptions, fixClubsDelay) == 324);
		uint32_t fixDarkTrainers; // 4-byte boolean | .328, 0x148
		static_assert(offsetof(mm7::PatchOptions, fixDarkTrainers) == 328);
		uint32_t fixLightBolt; // 4-byte boolean | .332, 0x14C
		static_assert(offsetof(mm7::PatchOptions, fixLightBolt) == 332);
		int32_t armageddonElement; // .336, 0x150
		static_assert(offsetof(mm7::PatchOptions, armageddonElement) == 336);
		uint32_t fixKelebrim; // 4-byte boolean | .340, 0x154
		static_assert(offsetof(mm7::PatchOptions, fixKelebrim) == 340);
		uint32_t fixBarrels; // 4-byte boolean | .344, 0x158
		static_assert(offsetof(mm7::PatchOptions, fixBarrels) == 344);
		uint32_t climbBetter; // 4-byte boolean | .348, 0x15C
		static_assert(offsetof(mm7::PatchOptions, climbBetter) == 348);
		uint32_t fixWaterWalkManaDrain; // 4-byte boolean | .352, 0x160
		static_assert(offsetof(mm7::PatchOptions, fixWaterWalkManaDrain) == 352);
		uint32_t keepEmptyWands; // 4-byte boolean | .356, 0x164
		static_assert(offsetof(mm7::PatchOptions, keepEmptyWands) == 356);
		uint32_t dontSkipSimpleMessage; // 4-byte boolean | .360, 0x168
		static_assert(offsetof(mm7::PatchOptions, dontSkipSimpleMessage) == 360);
		uint32_t fixItemDuplicates; // 4-byte boolean | .364, 0x16C
		static_assert(offsetof(mm7::PatchOptions, fixItemDuplicates) == 364);
		uint32_t fixClubsGeneration; // 4-byte boolean | .368, 0x170
		static_assert(offsetof(mm7::PatchOptions, fixClubsGeneration) == 368);
		uint32_t fixAcidBurst; // 4-byte boolean | .372, 0x174
		static_assert(offsetof(mm7::PatchOptions, fixAcidBurst) == 372);
	};
	static_assert(sizeof(mm7::PatchOptions) == 0x178, "Invalid \"mm7::PatchOptions\" structure size");

	struct ObjectRef // size: 0x4
	{
		union
		{
			uint16_t value; // .0, 0x0
			std::array<uint8_t, 2> index; // Unknown type | .0, 0x0
			struct
			{
				// uint8_t* kind; // real size is 0 | Unknown type | .0, 0x0
			};
		};
		int16_t ZBuf; // .2, 0x2
		static_assert(offsetof(mm7::ObjectRef, ZBuf) == 2);
	};
	static_assert(sizeof(mm7::ObjectRef) == 0x4, "Invalid \"mm7::ObjectRef\" structure size");

	struct MouseStruct // size: 0x110
	{
		mm7::ObjectRef target; // .0, 0x0
		SKIP(260);
		int32_t x; // .264, 0x108
		static_assert(offsetof(mm7::MouseStruct, x) == 264);
		int32_t y; // .268, 0x10C
		static_assert(offsetof(mm7::MouseStruct, y) == 268);
	};
	static_assert(sizeof(mm7::MouseStruct) == 0x110, "Invalid \"mm7::MouseStruct\" structure size");

	struct GameMouse // size: 0xAD45B0
	{
		SKIP(7473160);
		mm7::MouseStruct* mouseStruct; // .7473160, 0x720808
		static_assert(offsetof(mm7::GameMouse, mouseStruct) == 7473160);
		SKIP(3882368);
		mm7::Item item; // .11355532, 0xAD458C
		static_assert(offsetof(mm7::GameMouse, item) == 11355532);
	};
	static_assert(sizeof(mm7::GameMouse) == 0xAD45B0, "Invalid \"mm7::GameMouse\" structure size");

	struct EventLine // size: 0xC
	{
		int32_t event; // .0, 0x0
		int32_t line; // .4, 0x4
		static_assert(offsetof(mm7::EventLine, line) == 4);
		int32_t offset; // .8, 0x8
		static_assert(offsetof(mm7::EventLine, offset) == 8);
	};
	static_assert(sizeof(mm7::EventLine) == 0xC, "Invalid \"mm7::EventLine\" structure size");

	struct FaceAnimationInfo // size: 0x8
	{
		union
		{
			std::array<uint8_t, 2> sounds; // MMExt: 1..2, here 0..1 | .0, 0x0
			struct
			{
				uint8_t sound1; // .0, 0x0
				uint8_t sound2; // .1, 0x1
				static_assert(offsetof(mm7::FaceAnimationInfo, sound2) == 1);
			};
		};
		SKIP(1);
		union
		{
			std::array<uint8_t, 5> expressions; // MMExt: 1..5, here 0..4 | .3, 0x3
			static_assert(offsetof(mm7::FaceAnimationInfo, expressions) == 3);
			struct
			{
				uint8_t expression1; // .3, 0x3
				static_assert(offsetof(mm7::FaceAnimationInfo, expression1) == 3);
				uint8_t expression2; // .4, 0x4
				static_assert(offsetof(mm7::FaceAnimationInfo, expression2) == 4);
				uint8_t expression3; // .5, 0x5
				static_assert(offsetof(mm7::FaceAnimationInfo, expression3) == 5);
				uint8_t expression4; // .6, 0x6
				static_assert(offsetof(mm7::FaceAnimationInfo, expression4) == 6);
				uint8_t expression5; // .7, 0x7
				static_assert(offsetof(mm7::FaceAnimationInfo, expression5) == 7);
			};
		};
	};
	static_assert(sizeof(mm7::FaceAnimationInfo) == 0x8, "Invalid \"mm7::FaceAnimationInfo\" structure size");

	struct LodBitmap // size: 0x48
	{
		std::array<char, 16> name; // requires null terminator | .0, 0x0
		int32_t bmpSize; // .16, 0x10
		static_assert(offsetof(mm7::LodBitmap, bmpSize) == 16);
		int32_t dataSize; // .20, 0x14
		static_assert(offsetof(mm7::LodBitmap, dataSize) == 20);
		int16_t width; // .24, 0x18
		static_assert(offsetof(mm7::LodBitmap, width) == 24);
		int16_t height; // .26, 0x1A
		static_assert(offsetof(mm7::LodBitmap, height) == 26);
		int16_t widthLn2; // .28, 0x1C
		static_assert(offsetof(mm7::LodBitmap, widthLn2) == 28);
		int16_t heightLn2; // .30, 0x1E
		static_assert(offsetof(mm7::LodBitmap, heightLn2) == 30);
		int16_t widthMinus1; // .32, 0x20
		static_assert(offsetof(mm7::LodBitmap, widthMinus1) == 32);
		int16_t heightMinus1; // .34, 0x22
		static_assert(offsetof(mm7::LodBitmap, heightMinus1) == 34);
		int16_t palette; // .36, 0x24
		static_assert(offsetof(mm7::LodBitmap, palette) == 36);
		int16_t loadedPalette; // .38, 0x26
		static_assert(offsetof(mm7::LodBitmap, loadedPalette) == 38);
		int32_t unpackedSize; // .40, 0x28
		static_assert(offsetof(mm7::LodBitmap, unpackedSize) == 40);
		uint32_t bits; // .44, 0x2C
		static_assert(offsetof(mm7::LodBitmap, bits) == 44);
		int32_t image; // .48, 0x30
		static_assert(offsetof(mm7::LodBitmap, image) == 48);
		int32_t imageDiv2; // .52, 0x34
		static_assert(offsetof(mm7::LodBitmap, imageDiv2) == 52);
		int32_t imageDiv4; // .56, 0x38
		static_assert(offsetof(mm7::LodBitmap, imageDiv4) == 56);
		int32_t imageDiv8; // .60, 0x3C
		static_assert(offsetof(mm7::LodBitmap, imageDiv8) == 60);
		int32_t palette16; // .64, 0x40
		static_assert(offsetof(mm7::LodBitmap, palette16) == 64);
		int32_t palette24; // .68, 0x44
		static_assert(offsetof(mm7::LodBitmap, palette24) == 68);
	};
	static_assert(sizeof(mm7::LodBitmap) == 0x48, "Invalid \"mm7::LodBitmap\" structure size");

	struct BitmapsLod // size: 0x11BB8
	{
		uint32_t file; // .0, 0x0
		std::array<char, 256> fileName; // requires null terminator | .0, 0x0
		uint32_t loaded; // 4-byte boolean | .260, 0x104
		static_assert(offsetof(mm7::BitmapsLod, loaded) == 260);
		uint32_t IOBuffer; // .264, 0x108
		static_assert(offsetof(mm7::BitmapsLod, IOBuffer) == 264);
		int32_t IOBufferSize; // .268, 0x10C
		static_assert(offsetof(mm7::BitmapsLod, IOBufferSize) == 268);
		int32_t lodHeaderSignature; // .272, 0x110
		static_assert(offsetof(mm7::BitmapsLod, lodHeaderSignature) == 272);
		SKIP(80);
		std::array<char, 80> description; // requires null terminator | .0, 0x0
		SKIP(8);
		int32_t archivesCount; // .444, 0x1BC
		static_assert(offsetof(mm7::BitmapsLod, archivesCount) == 444);
		SKIP(80);
		uint32_t archivesCArray; // .528, 0x210
		static_assert(offsetof(mm7::BitmapsLod, archivesCArray) == 528);
		std::array<char, 16> type; // requires null terminator | .0, 0x0
		uint32_t chapterHandle; // .548, 0x224
		static_assert(offsetof(mm7::BitmapsLod, chapterHandle) == 548);
		uint32_t chapterSize; // .552, 0x228
		static_assert(offsetof(mm7::BitmapsLod, chapterSize) == 552);
		uint32_t files_size; // .556, 0x22C
		static_assert(offsetof(mm7::BitmapsLod, files_size) == 556);
		mm7::LodFile* files; // size offset is 0x22C | .560, 0x230
		static_assert(offsetof(mm7::BitmapsLod, files) == 560);
		uint32_t filesOffset; // .564, 0x234
		static_assert(offsetof(mm7::BitmapsLod, filesOffset) == 564);
		SKIP(4);
		std::array<mm7::LodBitmap, 1000> bitmaps; // size offset is 0x11B7C | .572, 0x23C
		static_assert(offsetof(mm7::BitmapsLod, bitmaps) == 572);
		union
		{
			uint32_t D3D_Surfaces_size; // .72572, 0x11B7C
			static_assert(offsetof(mm7::BitmapsLod, D3D_Surfaces_size) == 72572);
			uint32_t bitmaps_size; // .72572, 0x11B7C
			static_assert(offsetof(mm7::BitmapsLod, bitmaps_size) == 72572);
			uint32_t D3D_Textures_size; // .72572, 0x11B7C
			static_assert(offsetof(mm7::BitmapsLod, D3D_Textures_size) == 72572);
		};
		SKIP(36);
		uint32_t keepCompressed; // 4-byte boolean | .72612, 0x11BA4
		static_assert(offsetof(mm7::BitmapsLod, keepCompressed) == 72612);
		uint32_t isHardware; // 4-byte boolean | .72616, 0x11BA8
		static_assert(offsetof(mm7::BitmapsLod, isHardware) == 72616);
		uint32_t* D3D_Surfaces; // size offset is 0x11B7C | .72620, 0x11BAC
		static_assert(offsetof(mm7::BitmapsLod, D3D_Surfaces) == 72620);
		uint32_t* D3D_Textures; // size offset is 0x11B7C | .72624, 0x11BB0
		static_assert(offsetof(mm7::BitmapsLod, D3D_Textures) == 72624);
		SKIP(4);
	};
	static_assert(sizeof(mm7::BitmapsLod) == 0x11BB8, "Invalid \"mm7::BitmapsLod\" structure size");

	struct GameStructure // size: 0x600201BC
	{
		static inline mm7::GameMouse* const mouse = 0;
		static inline mm7::GameMap* const map = 0;
		static inline mm7::Arcomage* const arcomage = 0;
		static inline mm7::DialogLogic* const dialogLogic = 0;
		static inline mm7::Weather* const weather = 0;
		static inline mm7::GameParty* const party = 0;
		static inline mm7::GameRaces* const races = 0;
		static inline mm7::GameClasses* const classes = 0;
		static inline mm7::GameClassKinds* const classKinds = 0;

		// uint8_t* randSeed; // real size is 0 | Unknown type | .0, 0x0
		SKIP(4386761);
		std::array<uint8_t, 1> minMeleeRecoveryTime; // Unknown type | .0, 0x0
		SKIP(19266);
		char* winMapIndex; // unprotect before/protect after edit | .4406028, 0x433B0C
		static_assert(offsetof(mm7::GameStructure, winMapIndex) == 4406028);
		SKIP(114554);
		char* summonElementalC; // unprotect before/protect after edit | .4520586, 0x44FA8A
		static_assert(offsetof(mm7::GameStructure, summonElementalC) == 4520586);
		SKIP(8);
		char* summonElementalB; // unprotect before/protect after edit | .4520598, 0x44FA96
		static_assert(offsetof(mm7::GameStructure, summonElementalB) == 4520598);
		SKIP(3);
		char* summonElementalA; // unprotect before/protect after edit | .4520605, 0x44FA9D
		static_assert(offsetof(mm7::GameStructure, summonElementalA) == 4520605);
		SKIP(68036);
		// uint8_t* baseYear; // real size is 0 | Unknown type | .0, 0x0
		SKIP(24090);
		std::array<uint8_t, 4> newGameMap; // Unknown type | .0, 0x0
		SKIP(55777);
		std::array<uint8_t, 4> flyCeiling; // Unknown type | .0, 0x0
		SKIP(3243);
		std::array<uint8_t, 4> modelClimbRequirement; // Unknown type | .0, 0x0
		SKIP(113063);
		std::array<uint8_t, 4> maxBirthYear; // Unknown type | .0, 0x0
		SKIP(147788);
		std::array<uint8_t, 1> dialogTopicsLimit; // Unknown type | .0, 0x0
		SKIP(46115);
		std::array<uint8_t, 1> titleTrack; // Unknown type | .0, 0x0
		SKIP(140537);
		std::array<int16_t, 6> townPortalX; // .5119276, 0x4E1D2C
		static_assert(offsetof(mm7::GameStructure, townPortalX) == 5119276);
		std::array<int16_t, 6> townPortalY; // .5119288, 0x4E1D38
		static_assert(offsetof(mm7::GameStructure, townPortalY) == 5119288);
		std::array<int16_t, 6> townPortalWidth; // .5119300, 0x4E1D44
		static_assert(offsetof(mm7::GameStructure, townPortalWidth) == 5119300);
		std::array<int16_t, 6> townPortalHeight; // .5119312, 0x4E1D50
		static_assert(offsetof(mm7::GameStructure, townPortalHeight) == 5119312);
		SKIP(2940);
		int32_t currentScreen; // .5122264, 0x4E28D8
		static_assert(offsetof(mm7::GameStructure, currentScreen) == 5122264);
		SKIP(628);
		std::array<int8_t, 88> monsterClassInfoY; // .5122896, 0x4E2B50
		static_assert(offsetof(mm7::GameStructure, monsterClassInfoY) == 5122896);
		SKIP(3848);
		std::array<std::array<uint8_t, 4>, 99> spellObjId; // MMExt: 1..99, here 0..98 | Unknown type | .0, 0x0
		SKIP(12);
		std::array<mm7::SpellInfo, 100> spells; // .5127240, 0x4E3C48
		static_assert(offsetof(mm7::GameStructure, spells) == 5127240);
		SKIP(296);
		std::array<int32_t, 6> specialEnterX; // MMExt: 1..6, here 0..5 | .5129536, 0x4E4540
		static_assert(offsetof(mm7::GameStructure, specialEnterX) == 5129536);
		std::array<int32_t, 6> specialEnterY; // MMExt: 1..6, here 0..5 | .5129560, 0x4E4558
		static_assert(offsetof(mm7::GameStructure, specialEnterY) == 5129560);
		std::array<int32_t, 6> specialEnterZ; // MMExt: 1..6, here 0..5 | .5129584, 0x4E4570
		static_assert(offsetof(mm7::GameStructure, specialEnterZ) == 5129584);
		std::array<int32_t, 6> specialEnterDirection; // MMExt: 1..6, here 0..5 | .5129608, 0x4E4588
		static_assert(offsetof(mm7::GameStructure, specialEnterDirection) == 5129608);
		SKIP(6560);
		std::array<mm7::HouseMovie, 196> houseMovies; // .5136192, 0x4E5F40
		static_assert(offsetof(mm7::GameStructure, houseMovies) == 5136192);
		SKIP(6088);
		std::array<uint8_t, 20> equipStat2ItemSlot; // .5145416, 0x4E8348
		static_assert(offsetof(mm7::GameStructure, equipStat2ItemSlot) == 5145416);
		std::array<bool, 88> monsterClassSex; // MMExt: 1..88, here 0..87 | .5145436, 0x4E835C
		static_assert(offsetof(mm7::GameStructure, monsterClassSex) == 5145436);
		std::array<uint8_t, 88> monsterClassRace; // MMExt: 1..88, here 0..87 | .5145524, 0x4E83B4
		static_assert(offsetof(mm7::GameStructure, monsterClassRace) == 5145524);
		SKIP(11056);
		std::array<char*, 464> transTxt; // MMExt: 1..464, here 0..463 | .5156668, 0x4EAF3C
		static_assert(offsetof(mm7::GameStructure, transTxt) == 5156668);
		SKIP(5092);
		std::array<mm7::TownPortalTownInfo, 6> townPortalInfo; // .5163616, 0x4ECA60
		static_assert(offsetof(mm7::GameStructure, townPortalInfo) == 5163616);
		std::array<char*, 25> playerFaces; // unprotect before/protect after edit | .5163736, 0x4ECAD8
		static_assert(offsetof(mm7::GameStructure, playerFaces) == 5163736);
		SKIP(628);
		std::array<std::array<uint8_t, 25>, 49> standardPlayerSoundsCount; // MMExt: 1..49, here 0..48 | .5164464, 0x4ECDB0
		static_assert(offsetof(mm7::GameStructure, standardPlayerSoundsCount) == 5164464);
		SKIP(7);
		std::array<mm7::FaceAnimationInfo, 110> standardFaceAnimations; // .5165696, 0x4ED280
		static_assert(offsetof(mm7::GameStructure, standardFaceAnimations) == 5165696);
		SKIP(1936);
		std::array<int16_t, 13> skillRecoveryTimes; // .5168512, 0x4EDD80
		static_assert(offsetof(mm7::GameStructure, skillRecoveryTimes) == 5168512);
		SKIP(408);
		std::array<int16_t, 99> spellSounds; // MMExt: 1..99, here 0..98 | .5168946, 0x4EDF32
		static_assert(offsetof(mm7::GameStructure, spellSounds) == 5168946);
		SKIP(7888);
		std::array<int16_t, 78> mapDoorSound; // .5177032, 0x4EFEC8
		static_assert(offsetof(mm7::GameStructure, mapDoorSound) == 5177032);
		SKIP(724);
		std::array<char*, 19> shopBackgroundByType; // unprotect before/protect after edit | .5177912, 0x4F0238
		static_assert(offsetof(mm7::GameStructure, shopBackgroundByType) == 5177912);
		SKIP(4);
		std::array<mm7::ShopItemKind, 14> shopWeaponKinds; // MMExt: 1..14, here 0..13 | .5177992, 0x4F0288
		static_assert(offsetof(mm7::GameStructure, shopWeaponKinds) == 5177992);
		SKIP(4);
		std::array<std::array<mm7::ShopItemKind, 2>, 14> shopArmorKinds; // MMExt: 15..28, here 0..13 | MMExt: 1..2, here 0..1 | .5178136, 0x4F0318
		static_assert(offsetof(mm7::GameStructure, shopArmorKinds) == 5178136);
		std::array<int16_t, 13> shopMagicLevels; // MMExt: 29..41, here 0..12 | .5178416, 0x4F0430
		static_assert(offsetof(mm7::GameStructure, shopMagicLevels) == 5178416);
		SKIP(2);
		std::array<int16_t, 12> shopAlchemistLevels; // MMExt: 42..53, here 0..11 | .5178444, 0x4F044C
		static_assert(offsetof(mm7::GameStructure, shopAlchemistLevels) == 5178444);
		SKIP(100);
		std::array<mm7::ShopItemKind, 14> shopWeaponKindsSpecial; // MMExt: 1..14, here 0..13 | .5178568, 0x4F04C8
		static_assert(offsetof(mm7::GameStructure, shopWeaponKindsSpecial) == 5178568);
		SKIP(4);
		std::array<std::array<mm7::ShopItemKind, 2>, 14> shopArmorKindsSpecial; // MMExt: 15..28, here 0..13 | MMExt: 1..2, here 0..1 | .5178712, 0x4F0558
		static_assert(offsetof(mm7::GameStructure, shopArmorKindsSpecial) == 5178712);
		std::array<int16_t, 13> shopMagicLevelsSpecial; // MMExt: 29..41, here 0..12 | .5178992, 0x4F0670
		static_assert(offsetof(mm7::GameStructure, shopMagicLevelsSpecial) == 5178992);
		SKIP(2);
		std::array<int16_t, 12> shopAlchemistLevelsSpecial; // MMExt: 42..53, here 0..11 | .5179020, 0x4F068C
		static_assert(offsetof(mm7::GameStructure, shopAlchemistLevelsSpecial) == 5179020);
		SKIP(200);
		std::array<int32_t, 11> guildJoinCost; // .5179244, 0x4F076C
		static_assert(offsetof(mm7::GameStructure, guildJoinCost) == 5179244);
		std::array<int16_t, 10> trainingLevels; // MMExt: 89..98, here 0..9 | .5179288, 0x4F0798
		static_assert(offsetof(mm7::GameStructure, trainingLevels) == 5179288);
		SKIP(4);
		std::array<int32_t, 32> guildAwards; // MMExt: 139..170, here 0..31 | .5179312, 0x4F07B0
		static_assert(offsetof(mm7::GameStructure, guildAwards) == 5179312);
		std::array<mm7::TravelInfo, 35> transportLocations; // .5179440, 0x4F0830
		static_assert(offsetof(mm7::GameStructure, transportLocations) == 5179440);
		std::array<std::array<int8_t, 4>, 20> transportIndex; // MMExt: 54..73, here 0..19 | MMExt: 1..4, here 0..3 | .5180560, 0x4F0C90
		static_assert(offsetof(mm7::GameStructure, transportIndex) == 5180560);
		SKIP(208);
		std::array<int16_t, 32> guildSpellLevels; // MMExt: 139..170, here 0..31 | .5180848, 0x4F0DB0
		static_assert(offsetof(mm7::GameStructure, guildSpellLevels) == 5180848);
		SKIP(30956);
		int32_t turnBasedPhase; // .5211868, 0x4F86DC
		static_assert(offsetof(mm7::GameStructure, turnBasedPhase) == 5211868);
		SKIP(53576);
		std::array<int32_t, 480> scanlineOffset; // .5265448, 0x505828
		static_assert(offsetof(mm7::GameStructure, scanlineOffset) == 5265448);
		SKIP(3616);
		int32_t currentCharScreen; // .5270984, 0x506DC8
		static_assert(offsetof(mm7::GameStructure, currentCharScreen) == 5270984);
		SKIP(2556);
		bool flashHistoryBook; // .5273544, 0x5077C8
		static_assert(offsetof(mm7::GameStructure, flashHistoryBook) == 5273544);
		bool flashAutonotesBook; // .5273545, 0x5077C9
		static_assert(offsetof(mm7::GameStructure, flashAutonotesBook) == 5273545);
		bool flashQuestBook; // .5273546, 0x5077CA
		static_assert(offsetof(mm7::GameStructure, flashQuestBook) == 5273546);
		SKIP(557);
		std::array<char*, 7> statsNames; // .5274104, 0x5079F8
		static_assert(offsetof(mm7::GameStructure, statsNames) == 5274104);
		SKIP(4);
		uint32_t ctrlPressed; // 4-byte boolean | .5274136, 0x507A18
		static_assert(offsetof(mm7::GameStructure, ctrlPressed) == 5274136);
		SKIP(32);
		mm7::Dlg* currentNPCDialog; // .5274172, 0x507A3C
		static_assert(offsetof(mm7::GameStructure, currentNPCDialog) == 5274172);
		SKIP(44);
		std::array<uint8_t, 4> currentPlayer; // Unknown type | .0, 0x0
		bool rightButtonPressed; // .5274224, 0x507A70
		static_assert(offsetof(mm7::GameStructure, rightButtonPressed) == 5274224);
		SKIP(16331);
		uint32_t paused2; // 4-byte boolean | .5290556, 0x50BA3C
		static_assert(offsetof(mm7::GameStructure, paused2) == 5290556);
		SKIP(20);
		int32_t timeDelta2; // .5290580, 0x50BA54
		static_assert(offsetof(mm7::GameStructure, timeDelta2) == 5290580);
		SKIP(12);
		uint32_t paused; // 4-byte boolean | .5290596, 0x50BA64
		static_assert(offsetof(mm7::GameStructure, paused) == 5290596);
		SKIP(20);
		int32_t timeDelta; // .5290620, 0x50BA7C
		static_assert(offsetof(mm7::GameStructure, timeDelta) == 5290620);
		SKIP(3560);
		uint32_t actionsNext_size; // .5294184, 0x50C868
		static_assert(offsetof(mm7::GameStructure, actionsNext_size) == 5294184);
		std::array<mm7::ActionItem, 40> actionsNext; // size offset is 0x50C868 | .5294188, 0x50C86C
		static_assert(offsetof(mm7::GameStructure, actionsNext) == 5294188);
		SKIP(4);
		uint32_t actions_size; // .5294672, 0x50CA50
		static_assert(offsetof(mm7::GameStructure, actions_size) == 5294672);
		std::array<mm7::ActionItem, 40> actions; // size offset is 0x50CA50 | .5294676, 0x50CA54
		static_assert(offsetof(mm7::GameStructure, actions) == 5294676);
		SKIP(434300);
		mm7::ProgressBar progressBar; // .5729456, 0x576CB0
		static_assert(offsetof(mm7::GameStructure, progressBar) == 5729456);
		SKIP(44);
		uint32_t loadingScreen; // 4-byte boolean | .5729516, 0x576CEC
		static_assert(offsetof(mm7::GameStructure, loadingScreen) == 5729516);
		SKIP(444);
		uint32_t needRedraw; // 4-byte boolean | .5729964, 0x576EAC
		static_assert(offsetof(mm7::GameStructure, needRedraw) == 5729964);
		SKIP(106576);
		int32_t houseOwnerPic; // .5836544, 0x590F00
		static_assert(offsetof(mm7::GameStructure, houseOwnerPic) == 5836544);
		SKIP(8);
		int32_t NPCCommand; // .5836556, 0x590F0C
		static_assert(offsetof(mm7::GameStructure, NPCCommand) == 5836556);
		int32_t dialogNPC; // .5836560, 0x590F10
		static_assert(offsetof(mm7::GameStructure, dialogNPC) == 5836560);
		SKIP(836);
		std::array<int32_t, 6> houseNPCs; // MMExt: 1..6, here 0..5 | .5837400, 0x591258
		static_assert(offsetof(mm7::GameStructure, houseNPCs) == 5837400);
		int32_t houseNPCSlot; // .5837424, 0x591270
		static_assert(offsetof(mm7::GameStructure, houseNPCSlot) == 5837424);
		SKIP(48);
		int32_t houseNPCSlotsCount; // .5837476, 0x5912A4
		static_assert(offsetof(mm7::GameStructure, houseNPCSlotsCount) == 5837476);
		SKIP(16);
		std::array<mm7::Events2DItem, 523> houses; // .5837496, 0x5912B8
		static_assert(offsetof(mm7::GameStructure, houses) == 5837496);
		SKIP(2172);
		std::array<mm7::EventLine, 4400> globalEvtLines; // size offset is 0x5A53B0 | .5866864, 0x598570
		static_assert(offsetof(mm7::GameStructure, globalEvtLines) == 5866864);
		uint32_t globalEvtLines_size; // .5919664, 0x5A53B0
		static_assert(offsetof(mm7::GameStructure, globalEvtLines_size) == 5919664);
		SKIP(46084);
		std::array<char, 2000> streetMessage; // requires null terminator | .0, 0x0
		SKIP(8);
		uint32_t mapEvtLines_size; // .5967760, 0x5B0F90
		static_assert(offsetof(mm7::GameStructure, mapEvtLines_size) == 5967760);
		SKIP(21652);
		mm7::MoveToMap moveToMap; // .5989416, 0x5B6428
		static_assert(offsetof(mm7::GameStructure, moveToMap) == 5989416);
		SKIP(20);
		std::array<mm7::EventLine, 4400> mapEvtLines; // size offset is 0x5B0F90 | .5989464, 0x5B6458
		static_assert(offsetof(mm7::GameStructure, mapEvtLines) == 5989464);
		SKIP(16);
		std::array<char, 200> statusMessage; // requires null terminator | .0, 0x0
		std::array<char, 200> mouseOverStatusMessage; // requires null terminator | .0, 0x0
		int32_t statusDisappearTime; // .6042680, 0x5C3438
		static_assert(offsetof(mm7::GameStructure, statusDisappearTime) == 6042680);
		SKIP(20);
		int32_t houseExitMap; // .6042704, 0x5C3450
		static_assert(offsetof(mm7::GameStructure, houseExitMap) == 6042704);
		SKIP(12);
		int32_t autonote_fnt; // .6042720, 0x5C3460
		static_assert(offsetof(mm7::GameStructure, autonote_fnt) == 6042720);
		int32_t spell_fnt; // .6042724, 0x5C3464
		static_assert(offsetof(mm7::GameStructure, spell_fnt) == 6042724);
		int32_t arrus_fnt; // .6042728, 0x5C3468
		static_assert(offsetof(mm7::GameStructure, arrus_fnt) == 6042728);
		int32_t lucida_fnt; // .6042732, 0x5C346C
		static_assert(offsetof(mm7::GameStructure, lucida_fnt) == 6042732);
		int32_t book2_fnt; // .6042736, 0x5C3470
		static_assert(offsetof(mm7::GameStructure, book2_fnt) == 6042736);
		int32_t book_fnt; // .6042740, 0x5C3474
		static_assert(offsetof(mm7::GameStructure, book_fnt) == 6042740);
		SKIP(4);
		int32_t create_fnt; // .6042748, 0x5C347C
		static_assert(offsetof(mm7::GameStructure, create_fnt) == 6042748);
		int32_t cchar_fnt; // .6042752, 0x5C3480
		static_assert(offsetof(mm7::GameStructure, cchar_fnt) == 6042752);
		int32_t comic_fnt; // .6042756, 0x5C3484
		static_assert(offsetof(mm7::GameStructure, comic_fnt) == 6042756);
		int32_t smallnum_fnt; // .6042760, 0x5C3488
		static_assert(offsetof(mm7::GameStructure, smallnum_fnt) == 6042760);
		SKIP(10148);
		std::array<char, 2000> textBuffer; // requires null terminator | .0, 0x0
		std::array<char, 2000> textBuffer2; // requires null terminator | .0, 0x0
		SKIP(104);
		uint32_t TFTBin_size; // .6057016, 0x5C6C38
		static_assert(offsetof(mm7::GameStructure, TFTBin_size) == 6057016);
		mm7::TFTItem* TFTBin; // size offset is 0x5C6C38 | .6057020, 0x5C6C3C
		static_assert(offsetof(mm7::GameStructure, TFTBin) == 6057020);
		mm7::SFT SFTBin; // .6057024, 0x5C6C40
		static_assert(offsetof(mm7::GameStructure, SFTBin) == 6057024);
		SKIP(6408);
		std::array<char*, 36> classDescriptions; // .6063456, 0x5C8560
		static_assert(offsetof(mm7::GameStructure, classDescriptions) == 6063456);
		SKIP(8);
		std::array<char*, 7> statsDescriptions; // .6063608, 0x5C85F8
		static_assert(offsetof(mm7::GameStructure, statsDescriptions) == 6063608);
		SKIP(124);
		std::array<char*, 37> skillDesGM; // .6063760, 0x5C8690
		static_assert(offsetof(mm7::GameStructure, skillDesGM) == 6063760);
		SKIP(4);
		std::array<char*, 37> skillDesMaster; // .6063912, 0x5C8728
		static_assert(offsetof(mm7::GameStructure, skillDesMaster) == 6063912);
		SKIP(4);
		std::array<char*, 37> skillDesExpert; // .6064064, 0x5C87C0
		static_assert(offsetof(mm7::GameStructure, skillDesExpert) == 6064064);
		SKIP(4);
		std::array<char*, 37> skillDesNormal; // .6064216, 0x5C8858
		static_assert(offsetof(mm7::GameStructure, skillDesNormal) == 6064216);
		SKIP(4);
		std::array<char*, 37> skillDescriptions; // .6064368, 0x5C88F0
		static_assert(offsetof(mm7::GameStructure, skillDescriptions) == 6064368);
		SKIP(92);
		std::array<mm7::HistoryTxtItem, 29> historyTxt; // MMExt: 1..29, here 0..28 | .6064608, 0x5C89E0
		static_assert(offsetof(mm7::GameStructure, historyTxt) == 6064608);
		SKIP(4);
		std::array<std::array<uint8_t, 89>, 89> hostileTxt; // .6064960, 0x5C8B40
		static_assert(offsetof(mm7::GameStructure, hostileTxt) == 6064960);
		SKIP(5247);
		std::array<mm7::SpellsTxtItem, 100> spellsTxt; // .6078128, 0x5CBEB0
		static_assert(offsetof(mm7::GameStructure, spellsTxt) == 6078128);
		std::array<mm7::MonstersTxtItem, 265> monstersTxt; // size offset is 0x5D2854 | .6081728, 0x5CCCC0
		static_assert(offsetof(mm7::GameStructure, monstersTxt) == 6081728);
		std::array<char*, 31> placeMonTxt; // size offset is 0x5D2858 | .6105048, 0x5D27D8
		static_assert(offsetof(mm7::GameStructure, placeMonTxt) == 6105048);
		uint32_t monstersTxt_size; // .6105172, 0x5D2854
		static_assert(offsetof(mm7::GameStructure, monstersTxt_size) == 6105172);
		uint32_t placeMonTxt_size; // .6105176, 0x5D2858
		static_assert(offsetof(mm7::GameStructure, placeMonTxt_size) == 6105176);
		SKIP(4);
		uint32_t itemsTxt_size; // .6105184, 0x5D2860
		static_assert(offsetof(mm7::GameStructure, itemsTxt_size) == 6105184);
		std::array<mm7::ItemsTxtItem, 800> itemsTxt; // size offset is 0x5D2860 | .6105188, 0x5D2864
		static_assert(offsetof(mm7::GameStructure, itemsTxt) == 6105188);
		std::array<mm7::StdItemsTxtItem, 24> stdItemsTxt; // .6143588, 0x5DBE64
		static_assert(offsetof(mm7::GameStructure, stdItemsTxt) == 6143588);
		std::array<mm7::SpcItemsTxtItem, 72> spcItemsTxt; // .6144068, 0x5DC044
		static_assert(offsetof(mm7::GameStructure, spcItemsTxt) == 6144068);
		SKIP(20384);
		std::array<std::array<int16_t, 50>, 50> potionTxt; // MMExt: 222..271, here 0..49 | MMExt: 222..271, here 0..49 | .6166468, 0x5E17C4
		static_assert(offsetof(mm7::GameStructure, potionTxt) == 6166468);
		std::array<std::array<int16_t, 50>, 50> potNotesTxt; // MMExt: 222..271, here 0..49 | MMExt: 222..271, here 0..49 | .6171468, 0x5E2B4C
		static_assert(offsetof(mm7::GameStructure, potNotesTxt) == 6171468);
		SKIP(300);
		std::array<char*, 677> globalTxt; // .6176768, 0x5E4000
		static_assert(offsetof(mm7::GameStructure, globalTxt) == 6176768);
		SKIP(1332);
		uint32_t overlayBin_size; // .6180808, 0x5E4FC8
		static_assert(offsetof(mm7::GameStructure, overlayBin_size) == 6180808);
		mm7::OverlayItem* overlayBin; // size offset is 0x5E4FC8 | .6180812, 0x5E4FCC
		static_assert(offsetof(mm7::GameStructure, overlayBin) == 6180812);
		SKIP(106484);
		uint32_t chestBin_size; // .6287300, 0x5FEFC4
		static_assert(offsetof(mm7::GameStructure, chestBin_size) == 6287300);
		mm7::DChestItem* chestBin; // size offset is 0x5FEFC4 | .6287304, 0x5FEFC8
		static_assert(offsetof(mm7::GameStructure, chestBin) == 6287304);
		uint32_t monListBin_size; // .6287308, 0x5FEFCC
		static_assert(offsetof(mm7::GameStructure, monListBin_size) == 6287308);
		mm7::MonListItem* monListBin; // MMExt: 1..0, here 0..-1 | size offset is 0x5FEFCC | .6287312, 0x5FEFD0
		static_assert(offsetof(mm7::GameStructure, monListBin) == 6287312);
		SKIP(530012);
		uint32_t objListBin_size; // .6817328, 0x680630
		static_assert(offsetof(mm7::GameStructure, objListBin_size) == 6817328);
		mm7::ObjListItem* objListBin; // size offset is 0x680630 | .6817332, 0x680634
		static_assert(offsetof(mm7::GameStructure, objListBin) == 6817332);
		SKIP(108060);
		uint32_t decListBin_size; // .6925396, 0x69AC54
		static_assert(offsetof(mm7::GameStructure, decListBin_size) == 6925396);
		mm7::DecListItem* decListBin; // size offset is 0x69AC54 | .6925400, 0x69AC58
		static_assert(offsetof(mm7::GameStructure, decListBin) == 6925400);
		SKIP(48);
		std::array<int32_t, 30> keyCodes; // .6925452, 0x69AC8C
		static_assert(offsetof(mm7::GameStructure, keyCodes) == 6925452);
		std::array<int32_t, 30> keyTypes; // .6925572, 0x69AD04
		static_assert(offsetof(mm7::GameStructure, keyTypes) == 6925572);
		SKIP(22820);
		mm7::Lod saveGameLod; // .6948512, 0x6A06A0
		static_assert(offsetof(mm7::GameStructure, saveGameLod) == 6948512);
		SKIP(4);
		mm7::Lod gamesLod; // .6949088, 0x6A08E0
		static_assert(offsetof(mm7::GameStructure, gamesLod) == 6949088);
		SKIP(168);
		int32_t mainMenuCode; // .6949828, 0x6A0BC4
		static_assert(offsetof(mm7::GameStructure, mainMenuCode) == 6949828);
		int32_t exitMapAction; // .6949832, 0x6A0BC8
		static_assert(offsetof(mm7::GameStructure, exitMapAction) == 6949832);
		SKIP(119548);
		uint32_t tileBin_size; // .7069384, 0x6BDEC8
		static_assert(offsetof(mm7::GameStructure, tileBin_size) == 7069384);
		mm7::TileItem* tileBin; // size offset is 0x6BDEC8 | .7069388, 0x6BDECC
		static_assert(offsetof(mm7::GameStructure, tileBin) == 7069388);
		int32_t exitLevelCode; // .7069392, 0x6BDED0
		static_assert(offsetof(mm7::GameStructure, exitLevelCode) == 7069392);
		SKIP(48);
		int32_t outdoorViewMul; // .7069444, 0x6BDF04
		static_assert(offsetof(mm7::GameStructure, outdoorViewMul) == 7069444);
		int32_t outdoorViewDiv; // .7069448, 0x6BDF08
		static_assert(offsetof(mm7::GameStructure, outdoorViewDiv) == 7069448);
		SKIP(616);
		uint32_t windowHandle; // .7070068, 0x6BE174
		static_assert(offsetof(mm7::GameStructure, windowHandle) == 7070068);
		SKIP(119);
		int32_t soundVolume; // .7070191, 0x6BE1EF
		static_assert(offsetof(mm7::GameStructure, soundVolume) == 7070191);
		SKIP(1765);
		mm7::Lod eventsLod; // .7071960, 0x6BE8D8
		static_assert(offsetof(mm7::GameStructure, eventsLod) == 7071960);
		SKIP(72060);
		mm7::BitmapsLod iconsLod; // .7144592, 0x6D0490
		static_assert(offsetof(mm7::GameStructure, iconsLod) == 7144592);
		mm7::SpritesLod spritesLod; // .7217224, 0x6E2048
		static_assert(offsetof(mm7::GameStructure, spritesLod) == 7217224);
		mm7::BitmapsLod bitmapsLod; // .7277824, 0x6F0D00
		static_assert(offsetof(mm7::GameStructure, bitmapsLod) == 7277824);
		SKIP(126000);
		union
		{
			struct __NPCTopic
			{
				char* value;
				SKIP(4);
			};
			std::array<__NPCTopic, 789> NPCTopic; // MMExt: 1..789, here 0..788 | .7476456, 0x7214E8 | .7476456, 0x7214E8
			static_assert(offsetof(mm7::GameStructure, NPCTopic) == 7476456);
			struct __NPCText
			{
				SKIP(4);
				char* value;
			};
			std::array<__NPCText, 789> NPCText; // MMExt: 1..789, here 0..788 | .7476460, 0x7214EC | .7476460, 0x7214EC
			static_assert(offsetof(mm7::GameStructure, NPCText) == 7476460);
		};
		SKIP(3152);
		std::array<char*, 513> questsTxt; // .7482768, 0x722D90
		static_assert(offsetof(mm7::GameStructure, questsTxt) == 7482768);
		SKIP(1572);
		std::array<char*, 82> scrollTxt; // MMExt: 700..781, here 0..81 | .7486392, 0x723BB8
		static_assert(offsetof(mm7::GameStructure, scrollTxt) == 7486392);
		union
		{
			struct __awardsTxt
			{
				char* value;
				SKIP(4);
			};
			std::array<__awardsTxt, 105> awardsTxt; // .7486720, 0x723D00 | .7486720, 0x723D00
			static_assert(offsetof(mm7::GameStructure, awardsTxt) == 7486720);
			struct __awardsSort
			{
				SKIP(4);
				int32_t value;
			};
			std::array<__awardsSort, 105> awardsSort; // .7486724, 0x723D04 | .7486724, 0x723D04
			static_assert(offsetof(mm7::GameStructure, awardsSort) == 7486724);
		};
		SKIP(424);
		std::array<mm7::NPC, 501> NPCDataTxt; // .7487568, 0x724050
		static_assert(offsetof(mm7::GameStructure, NPCDataTxt) == 7487568);
		std::array<mm7::NPC, 501> NPC; // size offset is 0x73C014 | .7525644, 0x72D50C
		static_assert(offsetof(mm7::GameStructure, NPC) == 7525644);
		std::array<std::array<char*, 2>, 540> NPCNames; // .7563720, 0x7369C8
		static_assert(offsetof(mm7::GameStructure, NPCNames) == 7563720);
		std::array<mm7::NPCProfTxtItem, 59> NPCProfTxt; // .7568040, 0x737AA8
		static_assert(offsetof(mm7::GameStructure, NPCProfTxt) == 7568040);
		std::array<mm7::NPC, 100> streetNPC; // size offset is 0x73C010 | .7569220, 0x737F44
		static_assert(offsetof(mm7::GameStructure, streetNPC) == 7569220);
		std::array<char*, 51> NPCNews; // .7576820, 0x739CF4
		static_assert(offsetof(mm7::GameStructure, NPCNews) == 7576820);
		SKIP(6932);
		std::array<std::array<char*, 2>, 206> NPCGreet; // .7583956, 0x73B8D4
		static_assert(offsetof(mm7::GameStructure, NPCGreet) == 7583956);
		SKIP(102);
		std::array<int16_t, 51> NPCGroup; // .7585706, 0x73BFAA
		static_assert(offsetof(mm7::GameStructure, NPCGroup) == 7585706);
		uint32_t streetNPC_size; // .7585808, 0x73C010
		static_assert(offsetof(mm7::GameStructure, streetNPC_size) == 7585808);
		uint32_t NPC_size; // .7585812, 0x73C014
		static_assert(offsetof(mm7::GameStructure, NPC_size) == 7585812);
		SKIP(8);
		std::array<int32_t, 2> NPCNamesCount; // .7585824, 0x73C020
		static_assert(offsetof(mm7::GameStructure, NPCNamesCount) == 7585824);
		SKIP(232);
		std::array<char*, 59> NPCProfNames; // .7586064, 0x73C110
		static_assert(offsetof(mm7::GameStructure, NPCProfNames) == 7586064);
		SKIP(12);
		std::array<std::array<char*, 7>, 4> merchantTxt; // .7586312, 0x73C208
		static_assert(offsetof(mm7::GameStructure, merchantTxt) == 7586312);
		SKIP(3378412);
		uint32_t IFTBin_size; // .10964836, 0xA74F64
		static_assert(offsetof(mm7::GameStructure, IFTBin_size) == 10964836);
		mm7::IFTItem* IFTBin; // size offset is 0xA74F64 | .10964840, 0xA74F68
		static_assert(offsetof(mm7::GameStructure, IFTBin) == 10964840);
		uint32_t PFTBin_size; // .10964844, 0xA74F6C
		static_assert(offsetof(mm7::GameStructure, PFTBin_size) == 10964844);
		mm7::PFTItem* PFTBin; // size offset is 0xA74F6C | .10964848, 0xA74F70
		static_assert(offsetof(mm7::GameStructure, PFTBin) == 10964848);
		SKIP(360176);
		int64_t time; // .11325028, 0xACCE64
		static_assert(offsetof(mm7::GameStructure, time) == 11325028);
		SKIP(88);
		std::array<int64_t, 53> shopNextRefill; // .11325124, 0xACCEC4
		static_assert(offsetof(mm7::GameStructure, shopNextRefill) == 11325124);
		std::array<int64_t, 32> guildNextRefill; // MMExt: 139..170, here 0..31 | .11325548, 0xACD06C
		static_assert(offsetof(mm7::GameStructure, guildNextRefill) == 11325548);
		std::array<int64_t, 53> shopTheftExpireTime; // .11325804, 0xACD16C
		static_assert(offsetof(mm7::GameStructure, shopTheftExpireTime) == 11325804);
		SKIP(560);
		int32_t year; // .11326788, 0xACD544
		static_assert(offsetof(mm7::GameStructure, year) == 11326788);
		int32_t month; // .11326792, 0xACD548
		static_assert(offsetof(mm7::GameStructure, month) == 11326792);
		int32_t weekOfMonth; // .11326796, 0xACD54C
		static_assert(offsetof(mm7::GameStructure, weekOfMonth) == 11326796);
		int32_t dayOfMonth; // .11326800, 0xACD550
		static_assert(offsetof(mm7::GameStructure, dayOfMonth) == 11326800);
		int32_t hour; // .11326804, 0xACD554
		static_assert(offsetof(mm7::GameStructure, hour) == 11326804);
		int32_t minute; // .11326808, 0xACD558
		static_assert(offsetof(mm7::GameStructure, minute) == 11326808);
		int32_t second; // .11326812, 0xACD55C
		static_assert(offsetof(mm7::GameStructure, second) == 11326812);
		SKIP(340);
		uint32_t turnBased; // 4-byte boolean | .11327156, 0xACD6B4
		static_assert(offsetof(mm7::GameStructure, turnBased) == 11327156);
		SKIP(28408);
		bool needRender : 1; // .11355568, 0xAD45B0
		SKIP(3);
		std::array<std::array<mm7::Item, 12>, 53> shopItems; // .11355572, 0xAD45B4
		static_assert(offsetof(mm7::GameStructure, shopItems) == 11355572);
		std::array<std::array<mm7::Item, 12>, 53> shopSpecialItems; // .11378468, 0xAD9F24
		static_assert(offsetof(mm7::GameStructure, shopSpecialItems) == 11378468);
		std::array<std::array<std::array<mm7::Item, 12>, 1>, 32> guildItems; // MMExt: 139..170, here 0..31 | .11401364, 0xADF894
		static_assert(offsetof(mm7::GameStructure, guildItems) == 11401364);
		SKIP(224);
		int32_t armageddonTimeLeft; // .11415412, 0xAE2F74
		static_assert(offsetof(mm7::GameStructure, armageddonTimeLeft) == 11415412);
		int32_t armageddonSkill; // .11415416, 0xAE2F78
		static_assert(offsetof(mm7::GameStructure, armageddonSkill) == 11415416);
		std::array<int32_t, 4> turnBasedDelays; // .11415420, 0xAE2F7C
		static_assert(offsetof(mm7::GameStructure, turnBasedDelays) == 11415420);
		SKIP(228);
		std::array<char*, 36> classNames; // .11415664, 0xAE3070
		static_assert(offsetof(mm7::GameStructure, classNames) == 11415664);
		SKIP(80);
		std::array<char*, 37> skillNames; // .11415888, 0xAE3150
		static_assert(offsetof(mm7::GameStructure, skillNames) == 11415888);
		SKIP(3205252);
		union
		{
			mm7::GameScreen screen; // .14621288, 0xDF1A68
			static_assert(offsetof(mm7::GameStructure, screen) == 14621288);
			struct
			{
				SKIP(262196);
				std::array<std::array<mm7::ObjectRef, 640>, 480>* objectByPixel; // .14883484, 0xE31A9C
				static_assert(offsetof(mm7::GameStructure, objectByPixel) == 14883484);
				SKIP(32);
				uint32_t windowed; // .14883520, 0xE31AC0
				static_assert(offsetof(mm7::GameStructure, windowed) == 14883520);
				SKIP(44);
				uint32_t rendererD3D; // .14883568, 0xE31AF0
				static_assert(offsetof(mm7::GameStructure, rendererD3D) == 14883568);
			};
		};
		SKIP(1341092);
		int32_t redbookHandle; // .16224764, 0xF791FC
		static_assert(offsetof(mm7::GameStructure, redbookHandle) == 16224764);
		int32_t MSSHandle; // .16224768, 0xF79200
		static_assert(offsetof(mm7::GameStructure, MSSHandle) == 16224768);
		SKIP(2520);
		uint32_t soundsBin_size; // .16227292, 0xF79BDC
		static_assert(offsetof(mm7::GameStructure, soundsBin_size) == 16227292);
		mm7::SoundsItem* soundsBin; // size offset is 0xF79BDC | .16227296, 0xF79BE0
		static_assert(offsetof(mm7::GameStructure, soundsBin) == 16227296);
		SKIP(70660);
		std::array<int32_t, 12> guildItemIconPtr; // .16297960, 0xF8AFE8
		static_assert(offsetof(mm7::GameStructure, guildItemIconPtr) == 16297960);
		int32_t housePicType; // .16298008, 0xF8B018
		static_assert(offsetof(mm7::GameStructure, housePicType) == 16298008);
		int32_t houseScreen; // .16298012, 0xF8B01C
		static_assert(offsetof(mm7::GameStructure, houseScreen) == 16298012);
		SKIP(8);
		int32_t houseAllowAction; // .16298024, 0xF8B028
		static_assert(offsetof(mm7::GameStructure, houseAllowAction) == 16298024);
		int32_t houseActionInfo; // .16298028, 0xF8B02C
		static_assert(offsetof(mm7::GameStructure, houseActionInfo) == 16298028);
		int32_t houseTeachMastery; // .16298032, 0xF8B030
		static_assert(offsetof(mm7::GameStructure, houseTeachMastery) == 16298032);
		int32_t houseCost; // .16298036, 0xF8B034
		static_assert(offsetof(mm7::GameStructure, houseCost) == 16298036);
		SKIP(40);
		int32_t houseItemsCount; // .16298080, 0xF8B060
		static_assert(offsetof(mm7::GameStructure, houseItemsCount) == 16298080);
		SKIP(4);
		char* NPCMessage; // .16298088, 0xF8B068
		static_assert(offsetof(mm7::GameStructure, NPCMessage) == 16298088);
		SKIP(2372);
		int32_t smackVideo; // .16300464, 0xF8B9B0
		static_assert(offsetof(mm7::GameStructure, smackVideo) == 16300464);
		SKIP(56);
		uint32_t isMovieLooped; // 4-byte boolean | .16300524, 0xF8B9EC
		static_assert(offsetof(mm7::GameStructure, isMovieLooped) == 16300524);
		SKIP(24);
		int32_t binkVideo; // .16300552, 0xF8BA08
		static_assert(offsetof(mm7::GameStructure, binkVideo) == 16300552);
		SKIP(24);
		int32_t movieKind; // .16300580, 0xF8BA24
		static_assert(offsetof(mm7::GameStructure, movieKind) == 16300580);
		SKIP(35183160);
		std::array<mm7::FogChances, 78> mapFogChances; // .51483744, 0x3119460
		static_assert(offsetof(mm7::GameStructure, mapFogChances) == 51483744);
		SKIP(101032);
		union
		{
			struct __autonoteTxt
			{
				char* value;
				SKIP(4);
			};
			std::array<__autonoteTxt, 256> autonoteTxt; // .51585088, 0x3132040 | .51585088, 0x3132040
			static_assert(offsetof(mm7::GameStructure, autonoteTxt) == 51585088);
			struct __autonoteCategory
			{
				SKIP(4);
				int32_t value;
			};
			std::array<__autonoteCategory, 256> autonoteCategory; // .51585092, 0x3132044 | .51585092, 0x3132044
			static_assert(offsetof(mm7::GameStructure, autonoteCategory) == 51585092);
		};
		SKIP(1945400);
		mm7::PatchOptions patchOptions; // .53531516, 0x330D37C
		static_assert(offsetof(mm7::GameStructure, patchOptions) == 53531516);
		SKIP(1644144);
		mm7::CustomLods customLods; // .55176036, 0x349EB64
		static_assert(offsetof(mm7::GameStructure, customLods) == 55176036);
		SKIP(7536488);
		std::array<uint8_t, 4> titleTrackOffset; // Unknown type | .0, 0x0
		SKIP(100);
		mm7::MonsterKind* monsterKinds; // size offset is 0x3BD333C | .62731064, 0x3BD3338
		static_assert(offsetof(mm7::GameStructure, monsterKinds) == 62731064);
		uint32_t monsterKinds_size; // .62731068, 0x3BD333C
		static_assert(offsetof(mm7::GameStructure, monsterKinds_size) == 62731068);
		SKIP(184);
		mm7::MissileSetup* missileSetup; // size offset is 0x3BD33FC | .62731256, 0x3BD33F8
		static_assert(offsetof(mm7::GameStructure, missileSetup) == 62731256);
		uint32_t missileSetup_size; // .62731260, 0x3BD33FC
		static_assert(offsetof(mm7::GameStructure, missileSetup_size) == 62731260);
		SKIP(159098896);
		std::array<mm7::MapStatsItem, 78> mapStats; // size offset is 0xD38F0C8 | .221830160, 0xD38DC10
		static_assert(offsetof(mm7::GameStructure, mapStats) == 221830160);
		uint32_t mapStats_size; // .221835464, 0xD38F0C8
		static_assert(offsetof(mm7::GameStructure, mapStats_size) == 221835464);
		SKIP(1388908784);
	};
	static_assert(sizeof(mm7::GameStructure) == 0x600201BC, "Invalid \"mm7::GameStructure\" structure size");

}
#pragma pack(pop)