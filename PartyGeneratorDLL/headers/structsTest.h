#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm7
{
	struct SpellEffect; // 0-size struct, declaration only

	struct ActionItem // size: 0xC
	{
		int32_t action;
		int32_t param;
		int32_t param2;
	};
	static_assert(sizeof(mm7::ActionItem) == 0xC, "Invalid \"mm7::ActionItem\" structure size");
	static_assert(offsetof(mm7::ActionItem, param) == 4);
	static_assert(offsetof(mm7::ActionItem, param2) == 8);

	struct MapStatsItem // size: 0x44
	{
		char* name; // EditPChar
		char* fileName; // EditPChar
		char* monster1Pic; // EditPChar
		char* monster2Pic; // EditPChar
		char* monster3Pic; // EditPChar
		int32_t resetCount;
		int32_t firstVisitDay;
		int32_t refillDays;
		int32_t alertDays;
		int32_t stealPerm;
		int32_t per;
		SKIP(1);
		uint8_t lock;
		uint8_t trap;
		uint8_t tres;
		uint8_t encounterChance;
		uint8_t encounterChanceM1;
		uint8_t encounterChanceM2;
		uint8_t encounterChanceM3;
		uint8_t mon1Dif;
		uint8_t mon1Low;
		uint8_t mon1Hi;
		uint8_t mon2Dif;
		uint8_t mon2Low;
		uint8_t mon2Hi;
		uint8_t mon3Dif;
		uint8_t mon3Low;
		uint8_t mon3Hi;
		SKIP(3);
		uint8_t redbookTrack;
		uint8_t eaxEnvironments;
		SKIP(2);
	};
	static_assert(sizeof(mm7::MapStatsItem) == 0x44, "Invalid \"mm7::MapStatsItem\" structure size");
	static_assert(offsetof(mm7::MapStatsItem, fileName) == 4);
	static_assert(offsetof(mm7::MapStatsItem, monster1Pic) == 8);
	static_assert(offsetof(mm7::MapStatsItem, monster2Pic) == 12);
	static_assert(offsetof(mm7::MapStatsItem, monster3Pic) == 16);
	static_assert(offsetof(mm7::MapStatsItem, resetCount) == 20);
	static_assert(offsetof(mm7::MapStatsItem, firstVisitDay) == 24);
	static_assert(offsetof(mm7::MapStatsItem, refillDays) == 28);
	static_assert(offsetof(mm7::MapStatsItem, alertDays) == 32);
	static_assert(offsetof(mm7::MapStatsItem, stealPerm) == 36);
	static_assert(offsetof(mm7::MapStatsItem, per) == 40);
	static_assert(offsetof(mm7::MapStatsItem, lock) == 45);
	static_assert(offsetof(mm7::MapStatsItem, trap) == 46);
	static_assert(offsetof(mm7::MapStatsItem, tres) == 47);
	static_assert(offsetof(mm7::MapStatsItem, encounterChance) == 48);
	static_assert(offsetof(mm7::MapStatsItem, encounterChanceM1) == 49);
	static_assert(offsetof(mm7::MapStatsItem, encounterChanceM2) == 50);
	static_assert(offsetof(mm7::MapStatsItem, encounterChanceM3) == 51);
	static_assert(offsetof(mm7::MapStatsItem, mon1Dif) == 52);
	static_assert(offsetof(mm7::MapStatsItem, mon1Low) == 53);
	static_assert(offsetof(mm7::MapStatsItem, mon1Hi) == 54);
	static_assert(offsetof(mm7::MapStatsItem, mon2Dif) == 55);
	static_assert(offsetof(mm7::MapStatsItem, mon2Low) == 56);
	static_assert(offsetof(mm7::MapStatsItem, mon2Hi) == 57);
	static_assert(offsetof(mm7::MapStatsItem, mon3Dif) == 58);
	static_assert(offsetof(mm7::MapStatsItem, mon3Low) == 59);
	static_assert(offsetof(mm7::MapStatsItem, mon3Hi) == 60);
	static_assert(offsetof(mm7::MapStatsItem, redbookTrack) == 64);
	static_assert(offsetof(mm7::MapStatsItem, eaxEnvironments) == 65);

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

	struct FaceAnimationInfo // size: 0x8
	{
		union
		{
			std::array<uint8_t, 2> sounds; // MMExt: 1..2, here 0..1
			struct
			{
				uint8_t sound1;
				uint8_t sound2;
			};
		};
		SKIP(1);
		union
		{
			std::array<uint8_t, 5> expressions; // MMExt: 1..5, here 0..4
			struct
			{
				uint8_t expression1;
				uint8_t expression2;
				uint8_t expression3;
				uint8_t expression4;
				uint8_t expression5;
			};
		};
	};
	static_assert(sizeof(mm7::FaceAnimationInfo) == 0x8, "Invalid \"mm7::FaceAnimationInfo\" structure size");
	static_assert(offsetof(mm7::FaceAnimationInfo, sound2) == 1);
	static_assert(offsetof(mm7::FaceAnimationInfo, expressions) == 3);
	static_assert(offsetof(mm7::FaceAnimationInfo, expression1) == 3);
	static_assert(offsetof(mm7::FaceAnimationInfo, expression2) == 4);
	static_assert(offsetof(mm7::FaceAnimationInfo, expression3) == 5);
	static_assert(offsetof(mm7::FaceAnimationInfo, expression4) == 6);
	static_assert(offsetof(mm7::FaceAnimationInfo, expression5) == 7);

	struct TileItem // size: 0x1A
	{
		std::array<char, 16> name; // fixed size string, requires null terminator
		int16_t id;
		int16_t bitmap;
		int16_t tileSet;
		int16_t section;
		union
		{
			uint16_t bits;
			struct
			{
				bool burn : 1;
				bool water : 1;
				bool block : 1;
				bool repulse : 1;
				bool flat : 1;
				bool wave : 1;
				bool noDraw : 1;
				SKIPBITS(1);
				bool waterTransition : 1;
				bool transition : 1;
				bool scrollDown : 1;
				bool scrollUp : 1;
				bool scrollLeft : 1;
				bool scrollRight : 1;
			};
		};
	};
	static_assert(sizeof(mm7::TileItem) == 0x1A, "Invalid \"mm7::TileItem\" structure size");
	static_assert(offsetof(mm7::TileItem, id) == 16);
	static_assert(offsetof(mm7::TileItem, bitmap) == 18);
	static_assert(offsetof(mm7::TileItem, tileSet) == 20);
	static_assert(offsetof(mm7::TileItem, section) == 22);
	static_assert(offsetof(mm7::TileItem, bits) == 24);

	struct SoundsItem // size: 0x78
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		int32_t id;
		int32_t type;
		union
		{
			uint32_t bits;
			struct
			{
				bool locked : 1;
				bool is3D : 1;
			};
		};
		std::array<uint32_t, 17> data;
		uint32_t data3D;
		uint32_t decompressed; // 4-byte boolean
	};
	static_assert(sizeof(mm7::SoundsItem) == 0x78, "Invalid \"mm7::SoundsItem\" structure size");
	static_assert(offsetof(mm7::SoundsItem, id) == 32);
	static_assert(offsetof(mm7::SoundsItem, type) == 36);
	static_assert(offsetof(mm7::SoundsItem, bits) == 40);
	static_assert(offsetof(mm7::SoundsItem, data) == 44);
	static_assert(offsetof(mm7::SoundsItem, data3D) == 112);
	static_assert(offsetof(mm7::SoundsItem, decompressed) == 116);

	struct PFTItem // size: 0xA
	{
		uint16_t groupId;
		uint16_t frameIndex;
		uint16_t time;
		uint16_t totalTime;
		union
		{
			uint16_t bits;
			struct
			{
				bool notGroupEnd : 1;
				SKIPBITS(1);
				bool groupStart : 1;
			};
		};
	};
	static_assert(sizeof(mm7::PFTItem) == 0xA, "Invalid \"mm7::PFTItem\" structure size");
	static_assert(offsetof(mm7::PFTItem, frameIndex) == 2);
	static_assert(offsetof(mm7::PFTItem, time) == 4);
	static_assert(offsetof(mm7::PFTItem, totalTime) == 6);
	static_assert(offsetof(mm7::PFTItem, bits) == 8);

	struct DecListItem // size: 0x54
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		std::array<char, 32> gameName; // fixed size string, requires null terminator
		int16_t type;
		int16_t height;
		int16_t radius;
		int16_t lightRadius;
		union
		{
			int16_t SFTIndex;
			std::array<uint8_t, 2> SFTGroup; // Unknown type
		};
		union
		{
			uint16_t bits;
			struct
			{
				bool noBlockMovement : 1;
				bool noDraw : 1;
				bool flickerSlow : 1;
				bool flickerMedium : 1;
				bool flickerFast : 1;
				bool marker : 1;
				bool slowLoop : 1;
				bool emitFire : 1;
				bool soundOnDawn : 1;
				bool soundOnDusk : 1;
				bool emitSmoke : 1;
			};
		};
		int16_t soundId;
		SKIP(2);
		uint8_t red;
		uint8_t green;
		uint8_t blue;
		SKIP(1);
	};
	static_assert(sizeof(mm7::DecListItem) == 0x54, "Invalid \"mm7::DecListItem\" structure size");
	static_assert(offsetof(mm7::DecListItem, gameName) == 32);
	static_assert(offsetof(mm7::DecListItem, type) == 64);
	static_assert(offsetof(mm7::DecListItem, height) == 66);
	static_assert(offsetof(mm7::DecListItem, radius) == 68);
	static_assert(offsetof(mm7::DecListItem, lightRadius) == 70);
	static_assert(offsetof(mm7::DecListItem, SFTIndex) == 72);
	static_assert(offsetof(mm7::DecListItem, SFTGroup) == 72);
	static_assert(offsetof(mm7::DecListItem, bits) == 74);
	static_assert(offsetof(mm7::DecListItem, soundId) == 76);
	static_assert(offsetof(mm7::DecListItem, red) == 80);
	static_assert(offsetof(mm7::DecListItem, green) == 81);
	static_assert(offsetof(mm7::DecListItem, blue) == 82);

	struct SFTItem // size: 0x3C
	{
		std::array<char, 12> groupName; // fixed size string, requires null terminator
		std::array<char, 12> spriteName; // fixed size string, requires null terminator
		std::array<int16_t, 8> spriteIndex;
		int32_t scale;
		union
		{
			uint32_t bits;
			struct
			{
				bool notGroupEnd : 1;
				bool luminous : 1;
				bool groupStart : 1;
				SKIPBITS(1);
				bool image1 : 1;
				bool center : 1;
				bool fidget : 1;
				bool loaded : 1;
				bool mirror0 : 1;
				bool mirror1 : 1;
				bool mirror2 : 1;
				bool mirror3 : 1;
				bool mirror4 : 1;
				bool mirror5 : 1;
				bool mirror6 : 1;
				bool mirror7 : 1;
				bool images3 : 1;
				bool glow : 1;
				bool transparent : 1;
			};
		};
		int16_t lightRadius;
		int16_t paletteId;
		int16_t paletteIndex;
		int16_t time;
		int16_t totalTime;
		SKIP(2);
	};
	static_assert(sizeof(mm7::SFTItem) == 0x3C, "Invalid \"mm7::SFTItem\" structure size");
	static_assert(offsetof(mm7::SFTItem, spriteName) == 12);
	static_assert(offsetof(mm7::SFTItem, spriteIndex) == 24);
	static_assert(offsetof(mm7::SFTItem, scale) == 40);
	static_assert(offsetof(mm7::SFTItem, bits) == 44);
	static_assert(offsetof(mm7::SFTItem, lightRadius) == 48);
	static_assert(offsetof(mm7::SFTItem, paletteId) == 50);
	static_assert(offsetof(mm7::SFTItem, paletteIndex) == 52);
	static_assert(offsetof(mm7::SFTItem, time) == 54);
	static_assert(offsetof(mm7::SFTItem, totalTime) == 56);

	struct SFT // size: 0x18
	{
		uint32_t frames_size;
		union
		{
			uint32_t groupIndex_size;
			uint32_t groups_size;
		};
		int32_t matchIndex;
		mm7::SFTItem* frames; // size field offset is 0x0
		mm7::SFTItem** groups; // size field offset is 0x4
		int16_t* groupIndex; // size field offset is 0x4
	};
	static_assert(sizeof(mm7::SFT) == 0x18, "Invalid \"mm7::SFT\" structure size");
	static_assert(offsetof(mm7::SFT, groupIndex_size) == 4);
	static_assert(offsetof(mm7::SFT, groups_size) == 4);
	static_assert(offsetof(mm7::SFT, matchIndex) == 8);
	static_assert(offsetof(mm7::SFT, frames) == 12);
	static_assert(offsetof(mm7::SFT, groups) == 16);
	static_assert(offsetof(mm7::SFT, groupIndex) == 20);

	struct GameClassKinds // size: 0x4ED815
	{
		SKIP(5166584);
		std::array<uint8_t, 9> HPBase;
		SKIP(3);
		std::array<uint8_t, 9> SPBase;
		SKIP(187);
		std::array<std::array<uint8_t, 37>, 9> startingSkills;
	};
	static_assert(sizeof(mm7::GameClassKinds) == 0x4ED815, "Invalid \"mm7::GameClassKinds\" structure size");
	static_assert(offsetof(mm7::GameClassKinds, HPBase) == 5166584);
	static_assert(offsetof(mm7::GameClassKinds, SPBase) == 5166596);
	static_assert(offsetof(mm7::GameClassKinds, startingSkills) == 5166792);

	struct GameClasses // size: 0x600201BC
	{
		SKIP(5166608);
		std::array<uint8_t, 36> HPFactor;
		std::array<uint8_t, 36> SPFactor;
		SKIP(448);
		std::array<std::array<uint8_t, 37>, 36> skills;
		SKIP(1605575756);
		std::array<uint8_t, 36> SPStats;
	};
	static_assert(sizeof(mm7::GameClasses) == 0x600201BC, "Invalid \"mm7::GameClasses\" structure size");
	static_assert(offsetof(mm7::GameClasses, HPFactor) == 5166608);
	static_assert(offsetof(mm7::GameClasses, SPFactor) == 5166644);
	static_assert(offsetof(mm7::GameClasses, skills) == 5167128);
	static_assert(offsetof(mm7::GameClasses, SPStats) == 1610744216);

	struct StartStat // size: 0x4
	{
		int8_t base;
		int8_t max;
		int8_t spend;
		int8_t add;
	};
	static_assert(sizeof(mm7::StartStat) == 0x4, "Invalid \"mm7::StartStat\" structure size");
	static_assert(offsetof(mm7::StartStat, max) == 1);
	static_assert(offsetof(mm7::StartStat, spend) == 2);
	static_assert(offsetof(mm7::StartStat, add) == 3);

	struct GameRaces // size: 0x4ED6C8
	{
		SKIP(5166680);
		std::array<std::array<mm7::StartStat, 7>, 4> startingStats;
	};
	static_assert(sizeof(mm7::GameRaces) == 0x4ED6C8, "Invalid \"mm7::GameRaces\" structure size");
	static_assert(offsetof(mm7::GameRaces, startingStats) == 5166680);

	struct TravelInfo // size: 0x20
	{
		union
		{
			uint8_t mapIndex;
			std::array<uint8_t, 1> map; // Unknown type
		};
		union
		{
			std::array<uint8_t, 7> daysAvailable;
			struct
			{
				bool monday;
				bool tuesday;
				bool wednesday;
				bool thursday;
				bool friday;
				bool saturday;
				bool sunday;
			};
		};
		uint8_t daysCount;
		SKIP(3);
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
		int32_t QBit;
	};
	static_assert(sizeof(mm7::TravelInfo) == 0x20, "Invalid \"mm7::TravelInfo\" structure size");
	static_assert(offsetof(mm7::TravelInfo, daysAvailable) == 1);
	static_assert(offsetof(mm7::TravelInfo, monday) == 1);
	static_assert(offsetof(mm7::TravelInfo, tuesday) == 2);
	static_assert(offsetof(mm7::TravelInfo, wednesday) == 3);
	static_assert(offsetof(mm7::TravelInfo, thursday) == 4);
	static_assert(offsetof(mm7::TravelInfo, friday) == 5);
	static_assert(offsetof(mm7::TravelInfo, saturday) == 6);
	static_assert(offsetof(mm7::TravelInfo, sunday) == 7);
	static_assert(offsetof(mm7::TravelInfo, daysCount) == 8);
	static_assert(offsetof(mm7::TravelInfo, pos) == 12);
	static_assert(offsetof(mm7::TravelInfo, x) == 12);
	static_assert(offsetof(mm7::TravelInfo, y) == 16);
	static_assert(offsetof(mm7::TravelInfo, z) == 20);
	static_assert(offsetof(mm7::TravelInfo, direction) == 24);
	static_assert(offsetof(mm7::TravelInfo, QBit) == 28);

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

	struct SpellInfo // size: 0x14
	{
		union
		{
			std::array<int16_t, 4> spellPoints; // MMExt: 1..4, here 0..3
			struct
			{
				int16_t spellPointsNormal;
				int16_t spellPointsExpert;
				int16_t spellPointsMaster;
				int16_t spellPointsGM;
			};
		};
		union
		{
			std::array<int16_t, 4> delay; // MMExt: 1..4, here 0..3
			struct
			{
				int16_t delayNormal;
				int16_t delayExpert;
				int16_t delayMaster;
				int16_t delayGM;
			};
		};
		uint8_t damageAdd;
		uint8_t damageDiceSides;
		union
		{
			uint16_t bits;
			struct
			{
				bool castByMonster : 1;
				bool castByEvent : 1;
				bool causeDamage : 1;
				bool specialDamage : 1;
			};
		};
	};
	static_assert(sizeof(mm7::SpellInfo) == 0x14, "Invalid \"mm7::SpellInfo\" structure size");
	static_assert(offsetof(mm7::SpellInfo, spellPointsExpert) == 2);
	static_assert(offsetof(mm7::SpellInfo, spellPointsMaster) == 4);
	static_assert(offsetof(mm7::SpellInfo, spellPointsGM) == 6);
	static_assert(offsetof(mm7::SpellInfo, delay) == 8);
	static_assert(offsetof(mm7::SpellInfo, delayNormal) == 8);
	static_assert(offsetof(mm7::SpellInfo, delayExpert) == 10);
	static_assert(offsetof(mm7::SpellInfo, delayMaster) == 12);
	static_assert(offsetof(mm7::SpellInfo, delayGM) == 14);
	static_assert(offsetof(mm7::SpellInfo, damageAdd) == 16);
	static_assert(offsetof(mm7::SpellInfo, damageDiceSides) == 17);
	static_assert(offsetof(mm7::SpellInfo, bits) == 18);

	struct MissileSetup // size: 0x1
	{
		bool alwaysShowSprite : 1;
		bool hideSpecialDisplay : 1;
		bool autoCollision : 1;
	};
	static_assert(sizeof(mm7::MissileSetup) == 0x1, "Invalid \"mm7::MissileSetup\" structure size");

	struct ArcomagePlayer // size: 0xBC
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		bool human;
		SKIP(3);
		int32_t tower;
		int32_t wall;
		std::array<std::array<uint8_t, 4>, 3> income; // Unknown type
		std::array<int32_t, 3> res;
		std::array<int32_t, 10> cards;
		std::array<std::array<int32_t, 2>, 10> unk;
	};
	static_assert(sizeof(mm7::ArcomagePlayer) == 0xBC, "Invalid \"mm7::ArcomagePlayer\" structure size");
	static_assert(offsetof(mm7::ArcomagePlayer, human) == 32);
	static_assert(offsetof(mm7::ArcomagePlayer, tower) == 36);
	static_assert(offsetof(mm7::ArcomagePlayer, wall) == 40);
	static_assert(offsetof(mm7::ArcomagePlayer, income) == 44);
	static_assert(offsetof(mm7::ArcomagePlayer, res) == 56);
	static_assert(offsetof(mm7::ArcomagePlayer, cards) == 68);
	static_assert(offsetof(mm7::ArcomagePlayer, unk) == 108);

	struct ArcomageAction // size: 0x9
	{
		std::array<int8_t, 3> income;
		std::array<int8_t, 3> res;
		int8_t damage;
		int8_t wall;
		int8_t tower;
	};
	static_assert(sizeof(mm7::ArcomageAction) == 0x9, "Invalid \"mm7::ArcomageAction\" structure size");
	static_assert(offsetof(mm7::ArcomageAction, res) == 3);
	static_assert(offsetof(mm7::ArcomageAction, damage) == 6);
	static_assert(offsetof(mm7::ArcomageAction, wall) == 7);
	static_assert(offsetof(mm7::ArcomageAction, tower) == 8);

	struct ArcomageActions // size: 0x1D
	{
		bool playAgain;
		int8_t discardCards;
		mm7::ArcomageAction me;
		mm7::ArcomageAction enemy;
		mm7::ArcomageAction all;
	};
	static_assert(sizeof(mm7::ArcomageActions) == 0x1D, "Invalid \"mm7::ArcomageActions\" structure size");
	static_assert(offsetof(mm7::ArcomageActions, discardCards) == 1);
	static_assert(offsetof(mm7::ArcomageActions, me) == 2);
	static_assert(offsetof(mm7::ArcomageActions, enemy) == 11);
	static_assert(offsetof(mm7::ArcomageActions, all) == 20);

	struct ArcomageCard // size: 0x6C
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		int32_t sprite;
		int8_t costKind;
		std::array<int8_t, 3> costIncome;
		std::array<int8_t, 3> costRes;
		bool discardable;
		int32_t if_;
		mm7::ArcomageActions then;
		mm7::ArcomageActions else_;
		SKIP(2);
	};
	static_assert(sizeof(mm7::ArcomageCard) == 0x6C, "Invalid \"mm7::ArcomageCard\" structure size");
	static_assert(offsetof(mm7::ArcomageCard, sprite) == 32);
	static_assert(offsetof(mm7::ArcomageCard, costKind) == 36);
	static_assert(offsetof(mm7::ArcomageCard, costIncome) == 37);
	static_assert(offsetof(mm7::ArcomageCard, costRes) == 40);
	static_assert(offsetof(mm7::ArcomageCard, discardable) == 43);
	static_assert(offsetof(mm7::ArcomageCard, if_) == 44);
	static_assert(offsetof(mm7::ArcomageCard, then) == 48);
	static_assert(offsetof(mm7::ArcomageCard, else_) == 77);

	struct Arcomage // size: 0x505710
	{
		SKIP(5108644);
		int32_t AI;
		std::array<mm7::ArcomageCard, 87> cardKinds;
		SKIP(4);
		int32_t startingTower;
		int32_t startingWall;
		union
		{
			std::array<std::array<uint8_t, 4>, 3> startingIncome; // Unknown type
			struct
			{
				std::array<uint8_t, 4> startingIncomeBricks; // Unknown type
				std::array<uint8_t, 4> startingIncomeGems; // Unknown type
				std::array<uint8_t, 4> startingIncomeBeasts; // Unknown type
			};
		};
		std::array<uint8_t, 4> cardsCount; // Unknown type
		std::array<int32_t, 3> minIncome;
		int32_t towerToWin;
		int32_t resToWin;
		SKIP(146248);
		std::array<int32_t, 108> deck;
		SKIP(4);
		std::array<mm7::ArcomagePlayer, 2> players;
		SKIP(4);
		union
		{
			std::array<int32_t, 3> startingRes;
			struct
			{
				int32_t startingBricks;
				int32_t startingGems;
				int32_t startingBeasts;
			};
		};
	};
	static_assert(sizeof(mm7::Arcomage) == 0x505710, "Invalid \"mm7::Arcomage\" structure size");
	static_assert(offsetof(mm7::Arcomage, AI) == 5108644);
	static_assert(offsetof(mm7::Arcomage, cardKinds) == 5108648);
	static_assert(offsetof(mm7::Arcomage, startingTower) == 5118048);
	static_assert(offsetof(mm7::Arcomage, startingWall) == 5118052);
	static_assert(offsetof(mm7::Arcomage, startingIncome) == 5118056);
	static_assert(offsetof(mm7::Arcomage, startingIncomeBricks) == 5118056);
	static_assert(offsetof(mm7::Arcomage, startingIncomeGems) == 5118060);
	static_assert(offsetof(mm7::Arcomage, startingIncomeBeasts) == 5118064);
	static_assert(offsetof(mm7::Arcomage, cardsCount) == 5118068);
	static_assert(offsetof(mm7::Arcomage, minIncome) == 5118072);
	static_assert(offsetof(mm7::Arcomage, towerToWin) == 5118084);
	static_assert(offsetof(mm7::Arcomage, resToWin) == 5118088);
	static_assert(offsetof(mm7::Arcomage, deck) == 5264340);
	static_assert(offsetof(mm7::Arcomage, players) == 5264776);
	static_assert(offsetof(mm7::Arcomage, startingRes) == 5265156);
	static_assert(offsetof(mm7::Arcomage, startingBricks) == 5265156);
	static_assert(offsetof(mm7::Arcomage, startingGems) == 5265160);
	static_assert(offsetof(mm7::Arcomage, startingBeasts) == 5265164);

	struct NPCProfTxtItem // size: 0x14
	{
		int32_t cost;
		char* benefit; // EditPChar
		char* actionText; // EditPChar
		char* joinText; // EditPChar
		char* dismissText; // EditPChar
	};
	static_assert(sizeof(mm7::NPCProfTxtItem) == 0x14, "Invalid \"mm7::NPCProfTxtItem\" structure size");
	static_assert(offsetof(mm7::NPCProfTxtItem, benefit) == 4);
	static_assert(offsetof(mm7::NPCProfTxtItem, actionText) == 8);
	static_assert(offsetof(mm7::NPCProfTxtItem, joinText) == 12);
	static_assert(offsetof(mm7::NPCProfTxtItem, dismissText) == 16);

	struct Events2DItem // size: 0x34
	{
		int16_t type;
		int16_t picture;
		char* name; // EditPChar
		char* ownerName; // EditPChar
		char* enterText; // EditPChar
		char* ownerTitle; // EditPChar
		int16_t pictureUnk;
		int16_t state;
		int16_t rep;
		int16_t per;
		int16_t c;
		SKIP(2);
		float val;
		float a;
		int16_t openHour;
		int16_t closeHour;
		int16_t exitPic;
		int16_t exitMap;
		union
		{
			int16_t questBitRestriction;
			int16_t QBit;
		};
		SKIP(2);
	};
	static_assert(sizeof(mm7::Events2DItem) == 0x34, "Invalid \"mm7::Events2DItem\" structure size");
	static_assert(offsetof(mm7::Events2DItem, picture) == 2);
	static_assert(offsetof(mm7::Events2DItem, name) == 4);
	static_assert(offsetof(mm7::Events2DItem, ownerName) == 8);
	static_assert(offsetof(mm7::Events2DItem, enterText) == 12);
	static_assert(offsetof(mm7::Events2DItem, ownerTitle) == 16);
	static_assert(offsetof(mm7::Events2DItem, pictureUnk) == 20);
	static_assert(offsetof(mm7::Events2DItem, state) == 22);
	static_assert(offsetof(mm7::Events2DItem, rep) == 24);
	static_assert(offsetof(mm7::Events2DItem, per) == 26);
	static_assert(offsetof(mm7::Events2DItem, c) == 28);
	static_assert(offsetof(mm7::Events2DItem, val) == 32);
	static_assert(offsetof(mm7::Events2DItem, a) == 36);
	static_assert(offsetof(mm7::Events2DItem, openHour) == 40);
	static_assert(offsetof(mm7::Events2DItem, closeHour) == 42);
	static_assert(offsetof(mm7::Events2DItem, exitPic) == 44);
	static_assert(offsetof(mm7::Events2DItem, exitMap) == 46);
	static_assert(offsetof(mm7::Events2DItem, questBitRestriction) == 48);
	static_assert(offsetof(mm7::Events2DItem, QBit) == 48);

	struct HistoryTxtItem // size: 0xC
	{
		char* text; // EditPChar
		char* title; // EditPChar
		int8_t time;
		SKIP(3);
	};
	static_assert(sizeof(mm7::HistoryTxtItem) == 0xC, "Invalid \"mm7::HistoryTxtItem\" structure size");
	static_assert(offsetof(mm7::HistoryTxtItem, title) == 4);
	static_assert(offsetof(mm7::HistoryTxtItem, time) == 8);

	struct HouseMovie // size: 0x10
	{
		char* fileName; // EditPChar
		uint8_t background;
		SKIP(3);
		int32_t NPCPic;
		uint8_t houseType;
		uint8_t sounds;
		SKIP(2);
	};
	static_assert(sizeof(mm7::HouseMovie) == 0x10, "Invalid \"mm7::HouseMovie\" structure size");
	static_assert(offsetof(mm7::HouseMovie, background) == 4);
	static_assert(offsetof(mm7::HouseMovie, NPCPic) == 8);
	static_assert(offsetof(mm7::HouseMovie, houseType) == 12);
	static_assert(offsetof(mm7::HouseMovie, sounds) == 13);

	struct EventLine // size: 0xC
	{
		int32_t event;
		int32_t line;
		int32_t offset;
	};
	static_assert(sizeof(mm7::EventLine) == 0xC, "Invalid \"mm7::EventLine\" structure size");
	static_assert(offsetof(mm7::EventLine, line) == 4);
	static_assert(offsetof(mm7::EventLine, offset) == 8);

	struct IFTItem // size: 0x20
	{
		std::array<char, 12> groupName; // fixed size string, requires null terminator
		std::array<char, 12> iconName; // fixed size string, requires null terminator
		uint16_t time;
		uint16_t totalTime;
		union
		{
			uint16_t bits;
			struct
			{
				bool notGroupEnd : 1;
				SKIPBITS(1);
				bool groupStart : 1;
			};
		};
		uint16_t iconIndex;
	};
	static_assert(sizeof(mm7::IFTItem) == 0x20, "Invalid \"mm7::IFTItem\" structure size");
	static_assert(offsetof(mm7::IFTItem, iconName) == 12);
	static_assert(offsetof(mm7::IFTItem, time) == 24);
	static_assert(offsetof(mm7::IFTItem, totalTime) == 26);
	static_assert(offsetof(mm7::IFTItem, bits) == 28);
	static_assert(offsetof(mm7::IFTItem, iconIndex) == 30);

	struct TFTItem // size: 0x14
	{
		std::array<char, 12> name; // fixed size string, requires null terminator
		int16_t index;
		int16_t time;
		int16_t totalTime;
		union
		{
			uint16_t bits;
			struct
			{
				bool notGroupEnd : 1;
				bool groupStart : 1;
			};
		};
	};
	static_assert(sizeof(mm7::TFTItem) == 0x14, "Invalid \"mm7::TFTItem\" structure size");
	static_assert(offsetof(mm7::TFTItem, index) == 12);
	static_assert(offsetof(mm7::TFTItem, time) == 14);
	static_assert(offsetof(mm7::TFTItem, totalTime) == 16);
	static_assert(offsetof(mm7::TFTItem, bits) == 18);

	struct DChestItem // size: 0x24
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		uint8_t width;
		uint8_t height;
		int16_t imageIndex;
	};
	static_assert(sizeof(mm7::DChestItem) == 0x24, "Invalid \"mm7::DChestItem\" structure size");
	static_assert(offsetof(mm7::DChestItem, width) == 32);
	static_assert(offsetof(mm7::DChestItem, height) == 33);
	static_assert(offsetof(mm7::DChestItem, imageIndex) == 34);

	struct ShopItemKind // size: 0xA
	{
		int16_t level;
		std::array<int16_t, 4> types; // MMExt: 1..4, here 0..3
	};
	static_assert(sizeof(mm7::ShopItemKind) == 0xA, "Invalid \"mm7::ShopItemKind\" structure size");
	static_assert(offsetof(mm7::ShopItemKind, types) == 2);

	struct ItemsTxtItem // size: 0x30
	{
		char* picture; // EditPChar
		char* name; // EditPChar
		char* notIdentifiedName; // EditPChar
		char* notes; // EditPChar
		int32_t value;
		int16_t spriteIndex;
		SKIP(2);
		int16_t equipX;
		int16_t equipY;
		uint8_t equipStat;
		uint8_t skill;
		uint8_t mod1DiceCount;
		uint8_t mod1DiceSides;
		uint8_t mod2;
		uint8_t material;
		uint8_t bonus2;
		uint8_t bonus;
		uint8_t bonusStrength;
		SKIP(3);
		std::array<uint8_t, 6> chanceByLevel; // MMExt: 1..6, here 0..5
		int8_t idRepSt;
		SKIP(1);
	};
	static_assert(sizeof(mm7::ItemsTxtItem) == 0x30, "Invalid \"mm7::ItemsTxtItem\" structure size");
	static_assert(offsetof(mm7::ItemsTxtItem, name) == 4);
	static_assert(offsetof(mm7::ItemsTxtItem, notIdentifiedName) == 8);
	static_assert(offsetof(mm7::ItemsTxtItem, notes) == 12);
	static_assert(offsetof(mm7::ItemsTxtItem, value) == 16);
	static_assert(offsetof(mm7::ItemsTxtItem, spriteIndex) == 20);
	static_assert(offsetof(mm7::ItemsTxtItem, equipX) == 24);
	static_assert(offsetof(mm7::ItemsTxtItem, equipY) == 26);
	static_assert(offsetof(mm7::ItemsTxtItem, equipStat) == 28);
	static_assert(offsetof(mm7::ItemsTxtItem, skill) == 29);
	static_assert(offsetof(mm7::ItemsTxtItem, mod1DiceCount) == 30);
	static_assert(offsetof(mm7::ItemsTxtItem, mod1DiceSides) == 31);
	static_assert(offsetof(mm7::ItemsTxtItem, mod2) == 32);
	static_assert(offsetof(mm7::ItemsTxtItem, material) == 33);
	static_assert(offsetof(mm7::ItemsTxtItem, bonus2) == 34);
	static_assert(offsetof(mm7::ItemsTxtItem, bonus) == 35);
	static_assert(offsetof(mm7::ItemsTxtItem, bonusStrength) == 36);
	static_assert(offsetof(mm7::ItemsTxtItem, chanceByLevel) == 40);
	static_assert(offsetof(mm7::ItemsTxtItem, idRepSt) == 46);

	struct OverlayItem // size: 0x8
	{
		int16_t id;
		int16_t type;
		union
		{
			int16_t SFTIndex;
			std::array<uint8_t, 2> SFTGroup; // Unknown type
		};
		SKIP(2);
	};
	static_assert(sizeof(mm7::OverlayItem) == 0x8, "Invalid \"mm7::OverlayItem\" structure size");
	static_assert(offsetof(mm7::OverlayItem, type) == 2);
	static_assert(offsetof(mm7::OverlayItem, SFTIndex) == 4);
	static_assert(offsetof(mm7::OverlayItem, SFTGroup) == 4);

	struct ObjListItem // size: 0x38
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		int16_t id;
		int16_t radius;
		int16_t height;
		union
		{
			uint16_t bits;
			struct
			{
				bool invisible : 1;
				bool untouchable : 1;
				bool temporary : 1;
				bool lifetimeInSFT : 1;
				bool noPickup : 1;
				bool noGravity : 1;
				bool interceptAction : 1;
				bool bounce : 1;
				bool trailParticles : 1;
				bool trailFire : 1;
				bool trailLine : 1;
			};
		};
		union
		{
			int16_t SFTIndex;
			std::array<uint8_t, 2> SFTGroup; // Unknown type
		};
		int16_t lifeTime;
		uint32_t loadedParticlesColor;
		uint16_t speed;
		union
		{
			std::array<uint8_t, 4> particlesColor;
			struct
			{
				uint8_t particleR;
				uint8_t particleG;
				uint8_t particleB;
				uint8_t particleA;
			};
		};
		SKIP(2);
	};
	static_assert(sizeof(mm7::ObjListItem) == 0x38, "Invalid \"mm7::ObjListItem\" structure size");
	static_assert(offsetof(mm7::ObjListItem, id) == 32);
	static_assert(offsetof(mm7::ObjListItem, radius) == 34);
	static_assert(offsetof(mm7::ObjListItem, height) == 36);
	static_assert(offsetof(mm7::ObjListItem, bits) == 38);
	static_assert(offsetof(mm7::ObjListItem, SFTIndex) == 40);
	static_assert(offsetof(mm7::ObjListItem, SFTGroup) == 40);
	static_assert(offsetof(mm7::ObjListItem, lifeTime) == 42);
	static_assert(offsetof(mm7::ObjListItem, loadedParticlesColor) == 44);
	static_assert(offsetof(mm7::ObjListItem, speed) == 48);
	static_assert(offsetof(mm7::ObjListItem, particlesColor) == 50);
	static_assert(offsetof(mm7::ObjListItem, particleR) == 50);
	static_assert(offsetof(mm7::ObjListItem, particleG) == 51);
	static_assert(offsetof(mm7::ObjListItem, particleB) == 52);
	static_assert(offsetof(mm7::ObjListItem, particleA) == 53);

	struct MonListItem // size: 0x98
	{
		int16_t height;
		int16_t radius;
		int16_t velocity;
		int16_t radius2;
		union
		{
			int32_t tint;
			struct
			{
				uint8_t tintB;
				uint8_t tintG;
				uint8_t tintR;
				uint8_t tintA;
			};
		};
		union
		{
			std::array<int16_t, 4> sounds;
			struct
			{
				int16_t soundAttack;
				int16_t soundDie;
				int16_t soundGetHit;
				int16_t soundFidget;
			};
		};
		std::array<char, 32> name; // fixed size string, requires null terminator
		union
		{
			std::array<std::array<char, 10>, 10> frameNames; // fixed size string, requires null terminator
			struct
			{
				std::array<char, 10> framesStand; // fixed size string, requires null terminator
				std::array<char, 10> framesWalk; // fixed size string, requires null terminator
				std::array<char, 10> framesAttack; // fixed size string, requires null terminator
				std::array<char, 10> framesShoot; // fixed size string, requires null terminator
				std::array<char, 10> framesStun; // fixed size string, requires null terminator
				std::array<char, 10> framesDie; // fixed size string, requires null terminator
				std::array<char, 10> framesDead; // fixed size string, requires null terminator
				std::array<char, 10> framesFidget; // fixed size string, requires null terminator
			};
		};
	};
	static_assert(sizeof(mm7::MonListItem) == 0x98, "Invalid \"mm7::MonListItem\" structure size");
	static_assert(offsetof(mm7::MonListItem, radius) == 2);
	static_assert(offsetof(mm7::MonListItem, velocity) == 4);
	static_assert(offsetof(mm7::MonListItem, radius2) == 6);
	static_assert(offsetof(mm7::MonListItem, tint) == 8);
	static_assert(offsetof(mm7::MonListItem, tintB) == 8);
	static_assert(offsetof(mm7::MonListItem, tintG) == 9);
	static_assert(offsetof(mm7::MonListItem, tintR) == 10);
	static_assert(offsetof(mm7::MonListItem, tintA) == 11);
	static_assert(offsetof(mm7::MonListItem, sounds) == 12);
	static_assert(offsetof(mm7::MonListItem, soundAttack) == 12);
	static_assert(offsetof(mm7::MonListItem, soundDie) == 14);
	static_assert(offsetof(mm7::MonListItem, soundGetHit) == 16);
	static_assert(offsetof(mm7::MonListItem, soundFidget) == 18);
	static_assert(offsetof(mm7::MonListItem, name) == 20);
	static_assert(offsetof(mm7::MonListItem, frameNames) == 52);
	static_assert(offsetof(mm7::MonListItem, framesStand) == 52);
	static_assert(offsetof(mm7::MonListItem, framesWalk) == 62);
	static_assert(offsetof(mm7::MonListItem, framesAttack) == 72);
	static_assert(offsetof(mm7::MonListItem, framesShoot) == 82);
	static_assert(offsetof(mm7::MonListItem, framesStun) == 92);
	static_assert(offsetof(mm7::MonListItem, framesDie) == 102);
	static_assert(offsetof(mm7::MonListItem, framesDead) == 112);
	static_assert(offsetof(mm7::MonListItem, framesFidget) == 122);

	struct SpellsTxtItem // size: 0x24
	{
		char* name; // EditPChar
		char* shortName; // EditPChar
		char* description; // EditPChar
		char* normal; // EditPChar
		char* expert; // EditPChar
		char* master; // EditPChar
		union
		{
			char* GM; // EditPChar
			char* grandMaster; // EditPChar
		};
		uint8_t damageType;
		union
		{
			std::array<uint8_t, 4> spellPoints; // MMExt: 1..4, here 0..3
			struct
			{
				uint8_t spellPointsNormal;
				uint8_t spellPointsExpert;
				uint8_t spellPointsMaster;
				uint8_t spellPointsGM;
			};
		};
		SKIP(3);
	};
	static_assert(sizeof(mm7::SpellsTxtItem) == 0x24, "Invalid \"mm7::SpellsTxtItem\" structure size");
	static_assert(offsetof(mm7::SpellsTxtItem, shortName) == 4);
	static_assert(offsetof(mm7::SpellsTxtItem, description) == 8);
	static_assert(offsetof(mm7::SpellsTxtItem, normal) == 12);
	static_assert(offsetof(mm7::SpellsTxtItem, expert) == 16);
	static_assert(offsetof(mm7::SpellsTxtItem, master) == 20);
	static_assert(offsetof(mm7::SpellsTxtItem, GM) == 24);
	static_assert(offsetof(mm7::SpellsTxtItem, grandMaster) == 24);
	static_assert(offsetof(mm7::SpellsTxtItem, damageType) == 28);
	static_assert(offsetof(mm7::SpellsTxtItem, spellPoints) == 29);
	static_assert(offsetof(mm7::SpellsTxtItem, spellPointsNormal) == 29);
	static_assert(offsetof(mm7::SpellsTxtItem, spellPointsExpert) == 30);
	static_assert(offsetof(mm7::SpellsTxtItem, spellPointsMaster) == 31);
	static_assert(offsetof(mm7::SpellsTxtItem, spellPointsGM) == 32);

	struct Weather // size: 0x6BDEC8
	{
		SKIP(7069344);
		int32_t shade;
		uint32_t snow; // 4-byte boolean
		SKIP(8);
		// uint8_t* fog; // real size is 0 | Unknown type
		SKIP(16);
		std::array<uint8_t, 4> fogRange1; // Unknown type
		std::array<uint8_t, 4> fogRange2; // Unknown type
	};
	static_assert(sizeof(mm7::Weather) == 0x6BDEC8, "Invalid \"mm7::Weather\" structure size");
	static_assert(offsetof(mm7::Weather, shade) == 7069344);
	static_assert(offsetof(mm7::Weather, snow) == 7069348);
	static_assert(offsetof(mm7::Weather, fogRange1) == 7069376);
	static_assert(offsetof(mm7::Weather, fogRange2) == 7069380);

	struct MonsterKind // size: 0x8
	{
		bool undead;
		bool demon;
		bool dragon;
		bool elf;
		bool swimmer;
		bool immobile;
		bool titan;
		bool noArena;
	};
	static_assert(sizeof(mm7::MonsterKind) == 0x8, "Invalid \"mm7::MonsterKind\" structure size");
	static_assert(offsetof(mm7::MonsterKind, demon) == 1);
	static_assert(offsetof(mm7::MonsterKind, dragon) == 2);
	static_assert(offsetof(mm7::MonsterKind, elf) == 3);
	static_assert(offsetof(mm7::MonsterKind, swimmer) == 4);
	static_assert(offsetof(mm7::MonsterKind, immobile) == 5);
	static_assert(offsetof(mm7::MonsterKind, titan) == 6);
	static_assert(offsetof(mm7::MonsterKind, noArena) == 7);

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

	struct SpritesLod // size: 0xECB8
	{
		static mm7::LodSprite* spritesSW; // array converted to pointer to not break with limits removal scripts
		static uint32_t* spritesSW_size; // pointer to size, set during initialization by getting data from lua

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
			uint32_t bitmaps_size;
			uint32_t D3D_Textures_size;
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
	static_assert(offsetof(mm7::BitmapsLod, bitmaps_size) == 72572);
	static_assert(offsetof(mm7::BitmapsLod, D3D_Textures_size) == 72572);
	static_assert(offsetof(mm7::BitmapsLod, keepCompressed) == 72612);
	static_assert(offsetof(mm7::BitmapsLod, isHardware) == 72616);
	static_assert(offsetof(mm7::BitmapsLod, D3D_Surfaces) == 72620);
	static_assert(offsetof(mm7::BitmapsLod, D3D_Textures) == 72624);

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

	struct PatchOptions // size: 0x178
	{
		int32_t size;
		int32_t maxMLookAngle;
		uint32_t mouseLook; // 4-byte boolean
		uint32_t mouseLookUseAltMode; // 4-byte boolean
		uint32_t capsLockToggleMouseLook; // 4-byte boolean
		uint32_t mouseFly; // 4-byte boolean
		uint32_t mouseWheelFly; // 4-byte boolean
		int32_t mouseLookTempKey;
		int32_t mouseLookChangeKey;
		int32_t inventoryKey;
		int32_t charScreenKey;
		int32_t doubleSpeedKey;
		int32_t quickLoadKey;
		int32_t autorunKey;
		uint32_t HDWTRCount;
		uint32_t HDWTRDelay;
		int32_t horsemanSpeakTime;
		int32_t boatmanSpeakTime;
		float paletteSMul;
		float paletteVMul;
		uint32_t noBitmapsHwl; // 4-byte boolean
		uint32_t playMP3; // 4-byte boolean
		int32_t musicLoopsCount;
		uint32_t hardenArtifacts; // 4-byte boolean
		uint32_t progressiveDaggerTrippleDamage; // 4-byte boolean
		uint32_t fixChests; // 4-byte boolean
		uint32_t dataFiles; // 4-byte boolean
		uint32_t fixDualWeaponsRecovery; // 4-byte boolean
		int32_t increaseRecoveryRateStrength;
		int32_t blasterRecovery;
		uint32_t fixSkyBitmap; // 4-byte boolean
		uint32_t noCD; // 4-byte boolean
		uint32_t fixChestsByReorder; // 4-byte boolean
		int32_t lastLoadedFileSize;
		uint32_t fixTimers; // 4-byte boolean
		uint32_t fixMovement; // 4-byte boolean
		int32_t monsterJumpDownLimit;
		uint32_t fixHeroismPedestal; // 4-byte boolean
		uint32_t skipUnsellableItemCheck; // 4-byte boolean
		uint32_t fixGMStaff; // 4-byte boolean
		uint32_t fixObelisks; // 4-byte boolean
		uint32_t borderlessWindowed; // 4-byte boolean
		uint32_t compatibleMovieRender; // 4-byte boolean
		uint32_t smoothMovieScaling; // 4-byte boolean
		uint32_t supportTrueColor; // 4-byte boolean
		int32_t renderRectLeft;
		int32_t renderRectTop;
		int32_t renderRectRight;
		int32_t renderRectBottom;
		uint32_t fixUnimplementedSpells; // 4-byte boolean
		int32_t indoorMinimapZoomMul;
		int32_t indoorMinimapZoomPower;
		uint32_t fixMonsterSummon; // 4-byte boolean
		uint32_t fixInterfaceBugs; // 4-byte boolean
		const char* UILayout; // PChar (read-only)
		int32_t paperDollInChests;
		uint32_t higherCloseRingsButton; // 4-byte boolean
		int32_t renderBottomPixel;
		uint32_t trueColorTextures; // 4-byte boolean
		uint32_t resetPalettes; // 4-byte boolean
		uint32_t fixSFT; // 4-byte boolean
		uint32_t axeGMFullProbabilityAt; // 4-byte boolean
		double mouseDX;
		double mouseDY;
		uint32_t trueColorSprites; // 4-byte boolean
		uint32_t fixMonstersBlockingShots; // 4-byte boolean
		uint32_t fixParalyze; // 4-byte boolean
		uint32_t enableAttackSpell; // 4-byte boolean
		int32_t shooterMode;
		int32_t maxMLookUpAngle;
		uint32_t fixIceBoltBlast; // 4-byte boolean
		int32_t monSpritesSizeMul;
		uint32_t fixMonsterAttackTypes; // 4-byte boolean
		uint32_t fixMonsterSpells; // 4-byte boolean
		uint32_t fixSouldrinker; // 4-byte boolean
		int32_t mouseLookPermKey;
		int32_t lastSoundSample;
		int32_t waterWalkDamage;
		uint32_t fixUnmarkedArtifacts; // 4-byte boolean
		uint32_t fixClubsDelay; // 4-byte boolean
		uint32_t fixDarkTrainers; // 4-byte boolean
		uint32_t fixLightBolt; // 4-byte boolean
		int32_t armageddonElement;
		uint32_t fixKelebrim; // 4-byte boolean
		uint32_t fixBarrels; // 4-byte boolean
		uint32_t climbBetter; // 4-byte boolean
		uint32_t fixWaterWalkManaDrain; // 4-byte boolean
		uint32_t keepEmptyWands; // 4-byte boolean
		uint32_t dontSkipSimpleMessage; // 4-byte boolean
		uint32_t fixItemDuplicates; // 4-byte boolean
		uint32_t fixClubsGeneration; // 4-byte boolean
		uint32_t fixAcidBurst; // 4-byte boolean
	};
	static_assert(sizeof(mm7::PatchOptions) == 0x178, "Invalid \"mm7::PatchOptions\" structure size");
	static_assert(offsetof(mm7::PatchOptions, maxMLookAngle) == 4);
	static_assert(offsetof(mm7::PatchOptions, mouseLook) == 8);
	static_assert(offsetof(mm7::PatchOptions, mouseLookUseAltMode) == 12);
	static_assert(offsetof(mm7::PatchOptions, capsLockToggleMouseLook) == 16);
	static_assert(offsetof(mm7::PatchOptions, mouseFly) == 20);
	static_assert(offsetof(mm7::PatchOptions, mouseWheelFly) == 24);
	static_assert(offsetof(mm7::PatchOptions, mouseLookTempKey) == 28);
	static_assert(offsetof(mm7::PatchOptions, mouseLookChangeKey) == 32);
	static_assert(offsetof(mm7::PatchOptions, inventoryKey) == 36);
	static_assert(offsetof(mm7::PatchOptions, charScreenKey) == 40);
	static_assert(offsetof(mm7::PatchOptions, doubleSpeedKey) == 44);
	static_assert(offsetof(mm7::PatchOptions, quickLoadKey) == 48);
	static_assert(offsetof(mm7::PatchOptions, autorunKey) == 52);
	static_assert(offsetof(mm7::PatchOptions, HDWTRCount) == 56);
	static_assert(offsetof(mm7::PatchOptions, HDWTRDelay) == 60);
	static_assert(offsetof(mm7::PatchOptions, horsemanSpeakTime) == 64);
	static_assert(offsetof(mm7::PatchOptions, boatmanSpeakTime) == 68);
	static_assert(offsetof(mm7::PatchOptions, paletteSMul) == 72);
	static_assert(offsetof(mm7::PatchOptions, paletteVMul) == 76);
	static_assert(offsetof(mm7::PatchOptions, noBitmapsHwl) == 80);
	static_assert(offsetof(mm7::PatchOptions, playMP3) == 84);
	static_assert(offsetof(mm7::PatchOptions, musicLoopsCount) == 88);
	static_assert(offsetof(mm7::PatchOptions, hardenArtifacts) == 92);
	static_assert(offsetof(mm7::PatchOptions, progressiveDaggerTrippleDamage) == 96);
	static_assert(offsetof(mm7::PatchOptions, fixChests) == 100);
	static_assert(offsetof(mm7::PatchOptions, dataFiles) == 104);
	static_assert(offsetof(mm7::PatchOptions, fixDualWeaponsRecovery) == 108);
	static_assert(offsetof(mm7::PatchOptions, increaseRecoveryRateStrength) == 112);
	static_assert(offsetof(mm7::PatchOptions, blasterRecovery) == 116);
	static_assert(offsetof(mm7::PatchOptions, fixSkyBitmap) == 120);
	static_assert(offsetof(mm7::PatchOptions, noCD) == 124);
	static_assert(offsetof(mm7::PatchOptions, fixChestsByReorder) == 128);
	static_assert(offsetof(mm7::PatchOptions, lastLoadedFileSize) == 132);
	static_assert(offsetof(mm7::PatchOptions, fixTimers) == 136);
	static_assert(offsetof(mm7::PatchOptions, fixMovement) == 140);
	static_assert(offsetof(mm7::PatchOptions, monsterJumpDownLimit) == 144);
	static_assert(offsetof(mm7::PatchOptions, fixHeroismPedestal) == 148);
	static_assert(offsetof(mm7::PatchOptions, skipUnsellableItemCheck) == 152);
	static_assert(offsetof(mm7::PatchOptions, fixGMStaff) == 156);
	static_assert(offsetof(mm7::PatchOptions, fixObelisks) == 160);
	static_assert(offsetof(mm7::PatchOptions, borderlessWindowed) == 164);
	static_assert(offsetof(mm7::PatchOptions, compatibleMovieRender) == 168);
	static_assert(offsetof(mm7::PatchOptions, smoothMovieScaling) == 172);
	static_assert(offsetof(mm7::PatchOptions, supportTrueColor) == 176);
	static_assert(offsetof(mm7::PatchOptions, renderRectLeft) == 180);
	static_assert(offsetof(mm7::PatchOptions, renderRectTop) == 184);
	static_assert(offsetof(mm7::PatchOptions, renderRectRight) == 188);
	static_assert(offsetof(mm7::PatchOptions, renderRectBottom) == 192);
	static_assert(offsetof(mm7::PatchOptions, fixUnimplementedSpells) == 196);
	static_assert(offsetof(mm7::PatchOptions, indoorMinimapZoomMul) == 200);
	static_assert(offsetof(mm7::PatchOptions, indoorMinimapZoomPower) == 204);
	static_assert(offsetof(mm7::PatchOptions, fixMonsterSummon) == 208);
	static_assert(offsetof(mm7::PatchOptions, fixInterfaceBugs) == 212);
	static_assert(offsetof(mm7::PatchOptions, UILayout) == 216);
	static_assert(offsetof(mm7::PatchOptions, paperDollInChests) == 220);
	static_assert(offsetof(mm7::PatchOptions, higherCloseRingsButton) == 224);
	static_assert(offsetof(mm7::PatchOptions, renderBottomPixel) == 228);
	static_assert(offsetof(mm7::PatchOptions, trueColorTextures) == 232);
	static_assert(offsetof(mm7::PatchOptions, resetPalettes) == 236);
	static_assert(offsetof(mm7::PatchOptions, fixSFT) == 240);
	static_assert(offsetof(mm7::PatchOptions, axeGMFullProbabilityAt) == 244);
	static_assert(offsetof(mm7::PatchOptions, mouseDX) == 248);
	static_assert(offsetof(mm7::PatchOptions, mouseDY) == 256);
	static_assert(offsetof(mm7::PatchOptions, trueColorSprites) == 264);
	static_assert(offsetof(mm7::PatchOptions, fixMonstersBlockingShots) == 268);
	static_assert(offsetof(mm7::PatchOptions, fixParalyze) == 272);
	static_assert(offsetof(mm7::PatchOptions, enableAttackSpell) == 276);
	static_assert(offsetof(mm7::PatchOptions, shooterMode) == 280);
	static_assert(offsetof(mm7::PatchOptions, maxMLookUpAngle) == 284);
	static_assert(offsetof(mm7::PatchOptions, fixIceBoltBlast) == 288);
	static_assert(offsetof(mm7::PatchOptions, monSpritesSizeMul) == 292);
	static_assert(offsetof(mm7::PatchOptions, fixMonsterAttackTypes) == 296);
	static_assert(offsetof(mm7::PatchOptions, fixMonsterSpells) == 300);
	static_assert(offsetof(mm7::PatchOptions, fixSouldrinker) == 304);
	static_assert(offsetof(mm7::PatchOptions, mouseLookPermKey) == 308);
	static_assert(offsetof(mm7::PatchOptions, lastSoundSample) == 312);
	static_assert(offsetof(mm7::PatchOptions, waterWalkDamage) == 316);
	static_assert(offsetof(mm7::PatchOptions, fixUnmarkedArtifacts) == 320);
	static_assert(offsetof(mm7::PatchOptions, fixClubsDelay) == 324);
	static_assert(offsetof(mm7::PatchOptions, fixDarkTrainers) == 328);
	static_assert(offsetof(mm7::PatchOptions, fixLightBolt) == 332);
	static_assert(offsetof(mm7::PatchOptions, armageddonElement) == 336);
	static_assert(offsetof(mm7::PatchOptions, fixKelebrim) == 340);
	static_assert(offsetof(mm7::PatchOptions, fixBarrels) == 344);
	static_assert(offsetof(mm7::PatchOptions, climbBetter) == 348);
	static_assert(offsetof(mm7::PatchOptions, fixWaterWalkManaDrain) == 352);
	static_assert(offsetof(mm7::PatchOptions, keepEmptyWands) == 356);
	static_assert(offsetof(mm7::PatchOptions, dontSkipSimpleMessage) == 360);
	static_assert(offsetof(mm7::PatchOptions, fixItemDuplicates) == 364);
	static_assert(offsetof(mm7::PatchOptions, fixClubsGeneration) == 368);
	static_assert(offsetof(mm7::PatchOptions, fixAcidBurst) == 372);

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

	struct FloatVector // size: 0xC
	{
		union
		{
			float _1;
			float x;
		};
		union
		{
			float y;
			float _2;
		};
		union
		{
			float z;
			float _3;
		};
	};
	static_assert(sizeof(mm7::FloatVector) == 0xC, "Invalid \"mm7::FloatVector\" structure size");
	static_assert(offsetof(mm7::FloatVector, y) == 4);
	static_assert(offsetof(mm7::FloatVector, _2) == 4);
	static_assert(offsetof(mm7::FloatVector, z) == 8);
	static_assert(offsetof(mm7::FloatVector, _3) == 8);

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
			uint16_t facetStartV_size;
			uint16_t facetIds_size;
		};
		uint16_t roomIds_size;
		union
		{
			uint16_t vertexStartZ_size;
			uint16_t vertexStartX_size;
			uint16_t vertexStartY_size;
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
	static_assert(offsetof(mm7::MapDoor, facetStartU_size) == 70);
	static_assert(offsetof(mm7::MapDoor, facetStartV_size) == 70);
	static_assert(offsetof(mm7::MapDoor, facetIds_size) == 70);
	static_assert(offsetof(mm7::MapDoor, roomIds_size) == 72);
	static_assert(offsetof(mm7::MapDoor, vertexStartZ_size) == 74);
	static_assert(offsetof(mm7::MapDoor, vertexStartX_size) == 74);
	static_assert(offsetof(mm7::MapDoor, vertexStartY_size) == 74);
	static_assert(offsetof(mm7::MapDoor, state) == 76);

	struct ObjectRef2 // size: 0x2
	{
		union
		{
			std::array<uint8_t, 2> index; // Unknown type
			uint16_t value;
			struct
			{
				// uint8_t* kind; // real size is 0 | Unknown type
			};
		};
	};
	static_assert(sizeof(mm7::ObjectRef2) == 0x2, "Invalid \"mm7::ObjectRef2\" structure size");

	struct MonsterSchedule // size: 0xC
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
		uint16_t bits;
		uint8_t action;
		uint8_t hour;
		uint8_t day;
		uint8_t month;
	};
	static_assert(sizeof(mm7::MonsterSchedule) == 0xC, "Invalid \"mm7::MonsterSchedule\" structure size");
	static_assert(offsetof(mm7::MonsterSchedule, y) == 2);
	static_assert(offsetof(mm7::MonsterSchedule, z) == 4);
	static_assert(offsetof(mm7::MonsterSchedule, bits) == 6);
	static_assert(offsetof(mm7::MonsterSchedule, action) == 8);
	static_assert(offsetof(mm7::MonsterSchedule, hour) == 9);
	static_assert(offsetof(mm7::MonsterSchedule, day) == 10);
	static_assert(offsetof(mm7::MonsterSchedule, month) == 11);

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

	struct TilesetDef // size: 0x4
	{
		std::array<uint8_t, 2> group; // Unknown type
		int16_t offset;
	};
	static_assert(sizeof(mm7::TilesetDef) == 0x4, "Invalid \"mm7::TilesetDef\" structure size");
	static_assert(offsetof(mm7::TilesetDef, offset) == 2);

	struct OdmHeader // size: 0xB0
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		std::array<char, 32> fileName; // fixed size string, requires null terminator
		std::array<char, 31> versionStr; // fixed size string, requires null terminator
		SKIP(65);
		std::array<mm7::TilesetDef, 4> tilesets;
	};
	static_assert(sizeof(mm7::OdmHeader) == 0xB0, "Invalid \"mm7::OdmHeader\" structure size");
	static_assert(offsetof(mm7::OdmHeader, fileName) == 32);
	static_assert(offsetof(mm7::OdmHeader, versionStr) == 64);
	static_assert(offsetof(mm7::OdmHeader, tilesets) == 160);

	struct MapExtra // size: 0x38
	{
		int64_t lastVisitTime;
		std::array<char, 12> skyBitmap; // fixed size string, requires null terminator
		union
		{
			uint32_t dayBits;
			struct
			{
				bool foggy : 1;
			};
		};
		int32_t fogRange1;
		int32_t fogRange2;
		SKIP(8);
		uint32_t lastWeeklyTimer;
		uint32_t lastMonthlyTimer;
		uint32_t lastYearlyTimer;
		uint32_t lastDailyTimer;
	};
	static_assert(sizeof(mm7::MapExtra) == 0x38, "Invalid \"mm7::MapExtra\" structure size");
	static_assert(offsetof(mm7::MapExtra, skyBitmap) == 8);
	static_assert(offsetof(mm7::MapExtra, dayBits) == 20);
	static_assert(offsetof(mm7::MapExtra, fogRange1) == 24);
	static_assert(offsetof(mm7::MapExtra, fogRange2) == 28);
	static_assert(offsetof(mm7::MapExtra, lastWeeklyTimer) == 40);
	static_assert(offsetof(mm7::MapExtra, lastMonthlyTimer) == 44);
	static_assert(offsetof(mm7::MapExtra, lastYearlyTimer) == 48);
	static_assert(offsetof(mm7::MapExtra, lastDailyTimer) == 52);

	struct BlvHeader // size: 0x88
	{
		SKIP(4);
		std::array<char, 60> name; // fixed size string, requires null terminator
		SKIP(40);
		int32_t facetDataSize;
		int32_t roomDataSize;
		int32_t roomLightDataSize;
		int32_t doorDataSize;
		SKIP(16);
	};
	static_assert(sizeof(mm7::BlvHeader) == 0x88, "Invalid \"mm7::BlvHeader\" structure size");
	static_assert(offsetof(mm7::BlvHeader, name) == 4);
	static_assert(offsetof(mm7::BlvHeader, facetDataSize) == 104);
	static_assert(offsetof(mm7::BlvHeader, roomDataSize) == 108);
	static_assert(offsetof(mm7::BlvHeader, roomLightDataSize) == 112);
	static_assert(offsetof(mm7::BlvHeader, doorDataSize) == 116);

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
				bool triggerByMonster : 1;
				bool triggerByObject : 1;
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
			uint8_t vertexesCount;
			uint8_t vertexIds_size;
			uint8_t VList_size;
			uint8_t XInterceptDisplacement_size;
			uint8_t ZInterceptDisplacement_size;
			uint8_t UList_size;
			uint8_t YInterceptDisplacement_size;
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
	static_assert(offsetof(mm7::MapFacet, vertexesCount) == 93);
	static_assert(offsetof(mm7::MapFacet, vertexIds_size) == 93);
	static_assert(offsetof(mm7::MapFacet, VList_size) == 93);
	static_assert(offsetof(mm7::MapFacet, XInterceptDisplacement_size) == 93);
	static_assert(offsetof(mm7::MapFacet, ZInterceptDisplacement_size) == 93);
	static_assert(offsetof(mm7::MapFacet, UList_size) == 93);
	static_assert(offsetof(mm7::MapFacet, YInterceptDisplacement_size) == 93);

	struct BaseLight // size: 0xC
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
	};
	static_assert(sizeof(mm7::BaseLight) == 0xC, "Invalid \"mm7::BaseLight\" structure size");
	static_assert(offsetof(mm7::BaseLight, y) == 2);
	static_assert(offsetof(mm7::BaseLight, z) == 4);
	static_assert(offsetof(mm7::BaseLight, radius) == 6);
	static_assert(offsetof(mm7::BaseLight, r) == 8);
	static_assert(offsetof(mm7::BaseLight, g) == 9);
	static_assert(offsetof(mm7::BaseLight, b) == 10);
	static_assert(offsetof(mm7::BaseLight, type) == 11);

	struct MapObject // size: 0x70
	{
		int16_t type;
		int16_t typeIndex;
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
		union
		{
			std::array<int16_t, 3> velocity;
			struct
			{
				int16_t velocityX;
				int16_t velocityY;
				int16_t velocityZ;
			};
		};
		int16_t direction;
		int16_t lookAngle;
		union
		{
			uint16_t bits;
			struct
			{
				bool visible : 1;
				bool temporary : 1;
				bool haltTurnBased : 1;
				bool droppedByPlayer : 1;
				bool ignoreRange : 1;
				bool noZBuffer : 1;
				bool skipAFrame : 1;
				bool attachToHead : 1;
				bool missile : 1;
				bool removed : 1;
			};
		};
		int16_t room;
		int16_t age;
		int16_t maxAge;
		int16_t lightMultiplier;
		mm7::Item item;
		union
		{
			int32_t spell;
			int32_t spellType;
		};
		int32_t spellSkill;
		union
		{
			int32_t spellMastery;
			int32_t spellLevel;
		};
		mm7::SpellEffect* spellEffect;
		int32_t owner;
		int32_t target;
		uint8_t range;
		uint8_t attackType;
		SKIP(2);
		union
		{
			std::array<int32_t, 3> startPos;
			struct
			{
				int32_t startX;
				int32_t startY;
				int32_t startZ;
			};
		};
	};
	static_assert(sizeof(mm7::MapObject) == 0x70, "Invalid \"mm7::MapObject\" structure size");
	static_assert(offsetof(mm7::MapObject, typeIndex) == 2);
	static_assert(offsetof(mm7::MapObject, pos) == 4);
	static_assert(offsetof(mm7::MapObject, x) == 4);
	static_assert(offsetof(mm7::MapObject, y) == 8);
	static_assert(offsetof(mm7::MapObject, z) == 12);
	static_assert(offsetof(mm7::MapObject, velocity) == 16);
	static_assert(offsetof(mm7::MapObject, velocityX) == 16);
	static_assert(offsetof(mm7::MapObject, velocityY) == 18);
	static_assert(offsetof(mm7::MapObject, velocityZ) == 20);
	static_assert(offsetof(mm7::MapObject, direction) == 22);
	static_assert(offsetof(mm7::MapObject, lookAngle) == 24);
	static_assert(offsetof(mm7::MapObject, bits) == 26);
	static_assert(offsetof(mm7::MapObject, room) == 28);
	static_assert(offsetof(mm7::MapObject, age) == 30);
	static_assert(offsetof(mm7::MapObject, maxAge) == 32);
	static_assert(offsetof(mm7::MapObject, lightMultiplier) == 34);
	static_assert(offsetof(mm7::MapObject, item) == 36);
	static_assert(offsetof(mm7::MapObject, spell) == 72);
	static_assert(offsetof(mm7::MapObject, spellType) == 72);
	static_assert(offsetof(mm7::MapObject, spellSkill) == 76);
	static_assert(offsetof(mm7::MapObject, spellMastery) == 80);
	static_assert(offsetof(mm7::MapObject, spellLevel) == 80);
	static_assert(offsetof(mm7::MapObject, spellEffect) == 84);
	static_assert(offsetof(mm7::MapObject, owner) == 88);
	static_assert(offsetof(mm7::MapObject, target) == 92);
	static_assert(offsetof(mm7::MapObject, range) == 96);
	static_assert(offsetof(mm7::MapObject, attackType) == 97);
	static_assert(offsetof(mm7::MapObject, startPos) == 100);
	static_assert(offsetof(mm7::MapObject, startX) == 100);
	static_assert(offsetof(mm7::MapObject, startY) == 104);
	static_assert(offsetof(mm7::MapObject, startZ) == 108);

	struct StdItemsTxtItem // size: 0x14
	{
		char* nameAdd; // EditPChar
		char* bonusStat; // EditPChar
		union
		{
			std::array<uint8_t, 9> chanceForSlot;
			struct
			{
				uint8_t arm;
				uint8_t shld;
				uint8_t helm;
				uint8_t belt;
				uint8_t cape;
				uint8_t gaunt;
				uint8_t boot;
				uint8_t ring;
				uint8_t amul;
			};
		};
		SKIP(3);
	};
	static_assert(sizeof(mm7::StdItemsTxtItem) == 0x14, "Invalid \"mm7::StdItemsTxtItem\" structure size");
	static_assert(offsetof(mm7::StdItemsTxtItem, bonusStat) == 4);
	static_assert(offsetof(mm7::StdItemsTxtItem, chanceForSlot) == 8);
	static_assert(offsetof(mm7::StdItemsTxtItem, arm) == 8);
	static_assert(offsetof(mm7::StdItemsTxtItem, shld) == 9);
	static_assert(offsetof(mm7::StdItemsTxtItem, helm) == 10);
	static_assert(offsetof(mm7::StdItemsTxtItem, belt) == 11);
	static_assert(offsetof(mm7::StdItemsTxtItem, cape) == 12);
	static_assert(offsetof(mm7::StdItemsTxtItem, gaunt) == 13);
	static_assert(offsetof(mm7::StdItemsTxtItem, boot) == 14);
	static_assert(offsetof(mm7::StdItemsTxtItem, ring) == 15);
	static_assert(offsetof(mm7::StdItemsTxtItem, amul) == 16);

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
			uint8_t vertexesCount;
			uint8_t UList_size;
			uint8_t YInterceptDisplacement_size;
			uint8_t XInterceptDisplacement_size;
			uint8_t ZInterceptDisplacement_size;
			uint8_t vertexIds_size;
			uint8_t VList_size;
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
	static_assert(offsetof(mm7::ModelFacet, vertexesCount) == 302);
	static_assert(offsetof(mm7::ModelFacet, UList_size) == 302);
	static_assert(offsetof(mm7::ModelFacet, YInterceptDisplacement_size) == 302);
	static_assert(offsetof(mm7::ModelFacet, XInterceptDisplacement_size) == 302);
	static_assert(offsetof(mm7::ModelFacet, ZInterceptDisplacement_size) == 302);
	static_assert(offsetof(mm7::ModelFacet, vertexIds_size) == 302);
	static_assert(offsetof(mm7::ModelFacet, VList_size) == 302);
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

	struct SpawnPoint // size: 0x18
	{
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
		int16_t radius;
		int16_t kind;
		int16_t index;
		union
		{
			uint16_t bits;
			struct
			{
				bool onAlertMap : 1;
			};
		};
		int32_t group;
	};
	static_assert(sizeof(mm7::SpawnPoint) == 0x18, "Invalid \"mm7::SpawnPoint\" structure size");
	static_assert(offsetof(mm7::SpawnPoint, y) == 4);
	static_assert(offsetof(mm7::SpawnPoint, z) == 8);
	static_assert(offsetof(mm7::SpawnPoint, radius) == 12);
	static_assert(offsetof(mm7::SpawnPoint, kind) == 14);
	static_assert(offsetof(mm7::SpawnPoint, index) == 16);
	static_assert(offsetof(mm7::SpawnPoint, bits) == 18);
	static_assert(offsetof(mm7::SpawnPoint, group) == 20);

	struct MapOutline // size: 0xC
	{
		int16_t vertex1;
		int16_t vertex2;
		int16_t facet1;
		int16_t facet2;
		int16_t z;
		union
		{
			uint16_t bits;
			struct
			{
				bool visible : 1;
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
		uint32_t items_size;
		std::array<mm7::MapOutline, 7000> items; // size field offset is 0x0
	};
	static_assert(sizeof(mm7::MapOutlines) == 0x14824, "Invalid \"mm7::MapOutlines\" structure size");
	static_assert(offsetof(mm7::MapOutlines, items) == 4);

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

	struct ObjectRef // size: 0x4
	{
		union
		{
			std::array<uint8_t, 2> index; // Unknown type
			uint16_t value;
			struct
			{
				// uint8_t* kind; // real size is 0 | Unknown type
			};
		};
		int16_t ZBuf;
	};
	static_assert(sizeof(mm7::ObjectRef) == 0x4, "Invalid \"mm7::ObjectRef\" structure size");
	static_assert(offsetof(mm7::ObjectRef, ZBuf) == 2);

	struct MouseStruct // size: 0x110
	{
		mm7::ObjectRef target;
		SKIP(260);
		int32_t x;
		int32_t y;
	};
	static_assert(sizeof(mm7::MouseStruct) == 0x110, "Invalid \"mm7::MouseStruct\" structure size");
	static_assert(offsetof(mm7::MouseStruct, x) == 264);
	static_assert(offsetof(mm7::MouseStruct, y) == 268);

	struct GameMouse // size: 0xAD45B0
	{
		SKIP(7473160);
		mm7::MouseStruct* mouseStruct;
		SKIP(3882368);
		mm7::Item item;
	};
	static_assert(sizeof(mm7::GameMouse) == 0xAD45B0, "Invalid \"mm7::GameMouse\" structure size");
	static_assert(offsetof(mm7::GameMouse, mouseStruct) == 7473160);
	static_assert(offsetof(mm7::GameMouse, item) == 11355532);

	struct TownPortalTownInfo // size: 0x14
	{
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
		int16_t direction;
		int16_t lookAngle;
		union
		{
			int16_t mapStatsIndex;
			std::array<uint8_t, 2> map; // Unknown type
		};
		SKIP(2);
	};
	static_assert(sizeof(mm7::TownPortalTownInfo) == 0x14, "Invalid \"mm7::TownPortalTownInfo\" structure size");
	static_assert(offsetof(mm7::TownPortalTownInfo, y) == 4);
	static_assert(offsetof(mm7::TownPortalTownInfo, z) == 8);
	static_assert(offsetof(mm7::TownPortalTownInfo, direction) == 12);
	static_assert(offsetof(mm7::TownPortalTownInfo, lookAngle) == 14);
	static_assert(offsetof(mm7::TownPortalTownInfo, mapStatsIndex) == 16);
	static_assert(offsetof(mm7::TownPortalTownInfo, map) == 16);

	struct MoveToMap // size: 0x1C
	{
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
		int32_t lookAngle;
		int32_t speedZ;
		uint32_t defined; // 4-byte boolean
	};
	static_assert(sizeof(mm7::MoveToMap) == 0x1C, "Invalid \"mm7::MoveToMap\" structure size");
	static_assert(offsetof(mm7::MoveToMap, y) == 4);
	static_assert(offsetof(mm7::MoveToMap, z) == 8);
	static_assert(offsetof(mm7::MoveToMap, direction) == 12);
	static_assert(offsetof(mm7::MoveToMap, lookAngle) == 16);
	static_assert(offsetof(mm7::MoveToMap, speedZ) == 20);
	static_assert(offsetof(mm7::MoveToMap, defined) == 24);

	struct ProgressBar // size: 0x10
	{
		SKIP(10);
		uint8_t max;
		uint8_t current;
		int32_t kind;
	};
	static_assert(sizeof(mm7::ProgressBar) == 0x10, "Invalid \"mm7::ProgressBar\" structure size");
	static_assert(offsetof(mm7::ProgressBar, max) == 10);
	static_assert(offsetof(mm7::ProgressBar, current) == 11);
	static_assert(offsetof(mm7::ProgressBar, kind) == 12);

	struct FogChances // size: 0x4
	{
		uint8_t thick;
		uint8_t medium;
		uint8_t light;
		SKIP(1);
	};
	static_assert(sizeof(mm7::FogChances) == 0x4, "Invalid \"mm7::FogChances\" structure size");
	static_assert(offsetof(mm7::FogChances, medium) == 1);
	static_assert(offsetof(mm7::FogChances, light) == 2);

	struct MonsterAttackInfo // size: 0x5
	{
		uint8_t type;
		uint8_t damageDiceCount;
		uint8_t damageDiceSides;
		uint8_t damageAdd;
		uint8_t missile;
	};
	static_assert(sizeof(mm7::MonsterAttackInfo) == 0x5, "Invalid \"mm7::MonsterAttackInfo\" structure size");
	static_assert(offsetof(mm7::MonsterAttackInfo, damageDiceCount) == 1);
	static_assert(offsetof(mm7::MonsterAttackInfo, damageDiceSides) == 2);
	static_assert(offsetof(mm7::MonsterAttackInfo, damageAdd) == 3);
	static_assert(offsetof(mm7::MonsterAttackInfo, missile) == 4);

	struct MapMonster // size: 0x344
	{
		SKIP(32);
		int16_t NPC_ID;
		SKIP(2);
		union
		{
			uint32_t bits;
			struct
			{
				SKIPBITS(8); // skipping 1 bytes and 2 bits, in total 10 bits
				SKIPBITS(2);
				bool active : 1;
				SKIPBITS(4);
				bool showOnMap : 1;
				bool invisible : 1;
				bool noFlee : 1;
				SKIPBITS(1);
				bool hostile : 1;
				bool onAlertMap : 1;
				SKIPBITS(2);
				bool treasureGenerated : 1;
				bool showAsHostile : 1;
			};
		};
		union
		{
			int16_t hitPoints;
			int16_t HP;
		};
		SKIP(10);
		uint8_t level;
		uint8_t treasureItemPercent;
		uint8_t treasureDiceCount;
		uint8_t treasureDiceSides;
		uint8_t treasureItemLevel;
		uint8_t treasureItemType;
		uint8_t fly;
		uint8_t moveType;
		uint8_t AIType;
		uint8_t hostileType;
		SKIP(1);
		uint8_t bonus;
		uint8_t bonusMul;
		mm7::MonsterAttackInfo attack1;
		uint8_t attack2Chance;
		mm7::MonsterAttackInfo attack2;
		uint8_t spellChance;
		uint8_t spell;
		uint8_t spell2Chance;
		uint8_t spell2;
		union
		{
			struct // size: 0xA, MMExt union
			{
				uint8_t _0;
				uint8_t _1;
				uint8_t _2;
				uint8_t _3;
				uint8_t _7;
				uint8_t _6;
				uint8_t _8;
				uint8_t _9;
				uint8_t _10;
				uint8_t _4;
			} resistances;
			static_assert(sizeof(resistances) == 0xA, "Invalid \"resistances\" structure size");
			struct
			{
				uint8_t fireResistance;
				uint8_t airResistance;
				uint8_t waterResistance;
				uint8_t earthResistance;
				uint8_t mindResistance;
				uint8_t spiritResistance;
				uint8_t bodyResistance;
				uint8_t lightResistance;
				uint8_t darkResistance;
				uint8_t physResistance;
			};
		};
		uint8_t special;
		uint8_t specialA;
		uint8_t specialB;
		uint8_t specialC;
		uint8_t prefNum;
		SKIP(1);
		uint16_t id;
		uint16_t bloodSplat;
		uint16_t spellSkill;
		uint16_t spell2Skill;
		uint16_t specialD;
		SKIP(2);
		union
		{
			int32_t fullHitPoints;
			int32_t fullHP;
		};
		int32_t armorClass;
		union
		{
			int32_t exp;
			int32_t experience;
		};
		int32_t moveSpeed;
		int32_t attackRecovery;
		union
		{
			int32_t prefClass;
			struct
			{
				struct // size: 0x2, MMExt union
				{
					bool knight : 1;
					bool paladin : 1;
					bool archer : 1;
					bool druid : 1;
					bool cleric : 1;
					bool sorcerer : 1;
					bool ranger : 1;
					bool thief : 1;
					bool monk : 1;
					bool male : 1;
					bool female : 1;
					bool human : 1;
					bool elf : 1;
					bool dwarf : 1;
					bool goblin : 1;
				} prefers;
				static_assert(sizeof(prefers) == 0x2, "Invalid \"prefers\" structure size");
			};
		};
		int16_t rangeAttack;
		int16_t id2;
		int16_t bodyRadius;
		int16_t bodyHeight;
		int16_t velocity;
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
		int16_t velocityX;
		int16_t velocityY;
		int16_t velocityZ;
		int16_t direction;
		int16_t lookAngle;
		int16_t room;
		int16_t currentActionLength;
		int16_t startX;
		int16_t startY;
		int16_t startZ;
		int16_t guardX;
		int16_t guardY;
		int16_t guardZ;
		int16_t guardRadius;
		int16_t AIState;
		int16_t graphicState;
		int16_t item;
		SKIP(2);
		int32_t currentActionStep;
		union
		{
			std::array<int16_t, 8> frames;
			struct
			{
				int16_t framesStand;
				int16_t framesWalk;
				int16_t framesAttack;
				int16_t framesShoot;
				union
				{
					int16_t framesStun;
					int16_t framesGotHit;
				};
				int16_t framesDie;
				int16_t framesDead;
				int16_t framesFidget;
			};
		};
		union
		{
			std::array<int16_t, 4> sounds;
			struct
			{
				int16_t soundAttack;
				int16_t soundDie;
				union
				{
					int16_t soundGetHit;
					int16_t soundGotHit;
				};
				int16_t soundFidget;
			};
		};
		std::array<mm7::SpellBuff, 22> spellBuffs;
		std::array<mm7::Item, 4> items;
		int32_t group;
		int32_t ally;
		std::array<mm7::MonsterSchedule, 8> schedules;
		int32_t summoner;
		int32_t lastAttacker;
		int32_t nameId;
		SKIP(12);
	};
	static_assert(sizeof(mm7::MapMonster) == 0x344, "Invalid \"mm7::MapMonster\" structure size");
	static_assert(offsetof(mm7::MapMonster, NPC_ID) == 32);
	static_assert(offsetof(mm7::MapMonster, bits) == 36);
	static_assert(offsetof(mm7::MapMonster, hitPoints) == 40);
	static_assert(offsetof(mm7::MapMonster, HP) == 40);
	static_assert(offsetof(mm7::MapMonster, level) == 52);
	static_assert(offsetof(mm7::MapMonster, treasureItemPercent) == 53);
	static_assert(offsetof(mm7::MapMonster, treasureDiceCount) == 54);
	static_assert(offsetof(mm7::MapMonster, treasureDiceSides) == 55);
	static_assert(offsetof(mm7::MapMonster, treasureItemLevel) == 56);
	static_assert(offsetof(mm7::MapMonster, treasureItemType) == 57);
	static_assert(offsetof(mm7::MapMonster, fly) == 58);
	static_assert(offsetof(mm7::MapMonster, moveType) == 59);
	static_assert(offsetof(mm7::MapMonster, AIType) == 60);
	static_assert(offsetof(mm7::MapMonster, hostileType) == 61);
	static_assert(offsetof(mm7::MapMonster, bonus) == 63);
	static_assert(offsetof(mm7::MapMonster, bonusMul) == 64);
	static_assert(offsetof(mm7::MapMonster, attack1) == 65);
	static_assert(offsetof(mm7::MapMonster, attack2Chance) == 70);
	static_assert(offsetof(mm7::MapMonster, attack2) == 71);
	static_assert(offsetof(mm7::MapMonster, spellChance) == 76);
	static_assert(offsetof(mm7::MapMonster, spell) == 77);
	static_assert(offsetof(mm7::MapMonster, spell2Chance) == 78);
	static_assert(offsetof(mm7::MapMonster, spell2) == 79);
	static_assert(offsetof(mm7::MapMonster, resistances) == 80);
	static_assert(offsetof(mm7::MapMonster, fireResistance) == 80);
	static_assert(offsetof(mm7::MapMonster, airResistance) == 81);
	static_assert(offsetof(mm7::MapMonster, waterResistance) == 82);
	static_assert(offsetof(mm7::MapMonster, earthResistance) == 83);
	static_assert(offsetof(mm7::MapMonster, mindResistance) == 84);
	static_assert(offsetof(mm7::MapMonster, spiritResistance) == 85);
	static_assert(offsetof(mm7::MapMonster, bodyResistance) == 86);
	static_assert(offsetof(mm7::MapMonster, lightResistance) == 87);
	static_assert(offsetof(mm7::MapMonster, darkResistance) == 88);
	static_assert(offsetof(mm7::MapMonster, physResistance) == 89);
	static_assert(offsetof(mm7::MapMonster, special) == 90);
	static_assert(offsetof(mm7::MapMonster, specialA) == 91);
	static_assert(offsetof(mm7::MapMonster, specialB) == 92);
	static_assert(offsetof(mm7::MapMonster, specialC) == 93);
	static_assert(offsetof(mm7::MapMonster, prefNum) == 94);
	static_assert(offsetof(mm7::MapMonster, id) == 96);
	static_assert(offsetof(mm7::MapMonster, bloodSplat) == 98);
	static_assert(offsetof(mm7::MapMonster, spellSkill) == 100);
	static_assert(offsetof(mm7::MapMonster, spell2Skill) == 102);
	static_assert(offsetof(mm7::MapMonster, specialD) == 104);
	static_assert(offsetof(mm7::MapMonster, fullHitPoints) == 108);
	static_assert(offsetof(mm7::MapMonster, fullHP) == 108);
	static_assert(offsetof(mm7::MapMonster, armorClass) == 112);
	static_assert(offsetof(mm7::MapMonster, exp) == 116);
	static_assert(offsetof(mm7::MapMonster, experience) == 116);
	static_assert(offsetof(mm7::MapMonster, moveSpeed) == 120);
	static_assert(offsetof(mm7::MapMonster, attackRecovery) == 124);
	static_assert(offsetof(mm7::MapMonster, prefClass) == 128);
	static_assert(offsetof(mm7::MapMonster, prefers) == 128);
	static_assert(offsetof(mm7::MapMonster, rangeAttack) == 132);
	static_assert(offsetof(mm7::MapMonster, id2) == 134);
	static_assert(offsetof(mm7::MapMonster, bodyRadius) == 136);
	static_assert(offsetof(mm7::MapMonster, bodyHeight) == 138);
	static_assert(offsetof(mm7::MapMonster, velocity) == 140);
	static_assert(offsetof(mm7::MapMonster, pos) == 142);
	static_assert(offsetof(mm7::MapMonster, x) == 142);
	static_assert(offsetof(mm7::MapMonster, y) == 144);
	static_assert(offsetof(mm7::MapMonster, z) == 146);
	static_assert(offsetof(mm7::MapMonster, velocityX) == 148);
	static_assert(offsetof(mm7::MapMonster, velocityY) == 150);
	static_assert(offsetof(mm7::MapMonster, velocityZ) == 152);
	static_assert(offsetof(mm7::MapMonster, direction) == 154);
	static_assert(offsetof(mm7::MapMonster, lookAngle) == 156);
	static_assert(offsetof(mm7::MapMonster, room) == 158);
	static_assert(offsetof(mm7::MapMonster, currentActionLength) == 160);
	static_assert(offsetof(mm7::MapMonster, startX) == 162);
	static_assert(offsetof(mm7::MapMonster, startY) == 164);
	static_assert(offsetof(mm7::MapMonster, startZ) == 166);
	static_assert(offsetof(mm7::MapMonster, guardX) == 168);
	static_assert(offsetof(mm7::MapMonster, guardY) == 170);
	static_assert(offsetof(mm7::MapMonster, guardZ) == 172);
	static_assert(offsetof(mm7::MapMonster, guardRadius) == 174);
	static_assert(offsetof(mm7::MapMonster, AIState) == 176);
	static_assert(offsetof(mm7::MapMonster, graphicState) == 178);
	static_assert(offsetof(mm7::MapMonster, item) == 180);
	static_assert(offsetof(mm7::MapMonster, currentActionStep) == 184);
	static_assert(offsetof(mm7::MapMonster, frames) == 188);
	static_assert(offsetof(mm7::MapMonster, framesStand) == 188);
	static_assert(offsetof(mm7::MapMonster, framesWalk) == 190);
	static_assert(offsetof(mm7::MapMonster, framesAttack) == 192);
	static_assert(offsetof(mm7::MapMonster, framesShoot) == 194);
	static_assert(offsetof(mm7::MapMonster, framesStun) == 196);
	static_assert(offsetof(mm7::MapMonster, framesGotHit) == 196);
	static_assert(offsetof(mm7::MapMonster, framesDie) == 198);
	static_assert(offsetof(mm7::MapMonster, framesDead) == 200);
	static_assert(offsetof(mm7::MapMonster, framesFidget) == 202);
	static_assert(offsetof(mm7::MapMonster, sounds) == 204);
	static_assert(offsetof(mm7::MapMonster, soundAttack) == 204);
	static_assert(offsetof(mm7::MapMonster, soundDie) == 206);
	static_assert(offsetof(mm7::MapMonster, soundGetHit) == 208);
	static_assert(offsetof(mm7::MapMonster, soundGotHit) == 208);
	static_assert(offsetof(mm7::MapMonster, soundFidget) == 210);
	static_assert(offsetof(mm7::MapMonster, spellBuffs) == 212);
	static_assert(offsetof(mm7::MapMonster, items) == 564);
	static_assert(offsetof(mm7::MapMonster, group) == 708);
	static_assert(offsetof(mm7::MapMonster, ally) == 712);
	static_assert(offsetof(mm7::MapMonster, schedules) == 716);
	static_assert(offsetof(mm7::MapMonster, summoner) == 812);
	static_assert(offsetof(mm7::MapMonster, lastAttacker) == 816);
	static_assert(offsetof(mm7::MapMonster, nameId) == 820);

	struct DialogLogic // size: 0x5C4430
	{
		SKIP(5122552);
		std::array<int32_t, 5> armorSkills; // Requires unprotect before change
		std::array<int32_t, 9> weaponSkills; // Requires unprotect before change
		std::array<int32_t, 12> miscSkills; // Requires unprotect before change
		std::array<int32_t, 9> magicSkills; // Requires unprotect before change
		SKIP(145688);
		int32_t scrollPage;
		int32_t countOnScreen;
		union
		{
			uint32_t list_size;
			int32_t listCount;
		};
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
		SKIP(773452);
		std::array<int32_t, 1000> list; // size field offset is 0x5063A4
	};
	static_assert(sizeof(mm7::DialogLogic) == 0x5C4430, "Invalid \"mm7::DialogLogic\" structure size");
	static_assert(offsetof(mm7::DialogLogic, armorSkills) == 5122552);
	static_assert(offsetof(mm7::DialogLogic, weaponSkills) == 5122572);
	static_assert(offsetof(mm7::DialogLogic, miscSkills) == 5122608);
	static_assert(offsetof(mm7::DialogLogic, magicSkills) == 5122656);
	static_assert(offsetof(mm7::DialogLogic, scrollPage) == 5268380);
	static_assert(offsetof(mm7::DialogLogic, countOnScreen) == 5268384);
	static_assert(offsetof(mm7::DialogLogic, list_size) == 5268388);
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
	static_assert(offsetof(mm7::DialogLogic, list) == 6042768);

	struct GameMap // size: 0x76D398
	{
		SKIP(5342836);
		std::array<mm7::BaseLight, 400> spriteLights; // size field offset is 0x519934
		uint32_t spriteLights_size;
		SKIP(831960);
		std::array<uint8_t, 200> vars;
		SKIP(1016);
		std::array<mm7::MapChest, 20> chests; // size field offset is 0x5FEFC0
		uint32_t chests_size;
		SKIP(20);
		std::array<mm7::MapMonster, 500> monsters; // size field offset is 0x6650A8
		uint32_t monsters_size;
		uint32_t objects_size;
		std::array<mm7::MapObject, 1000> objects; // size field offset is 0x6650AC
		SKIP(8);
		std::array<int32_t, 10> soundSprites; // size field offset is 0x680660
		uint32_t soundSprites_size;
		SKIP(12012);
		std::array<mm7::MapSprite, 3000> sprites; // size field offset is 0x69AC50
		uint32_t sprites_size;
		SKIP(24604);
		union
		{
			mm7::OdmHeader outdoorHeader;
			struct
			{
				SKIP(160);
				std::array<mm7::TilesetDef, 4> tilesets;
			};
		};
		uint32_t models_size;
		std::array<std::array<uint8_t, 128>, 128>* heightMap;
		std::array<std::array<uint8_t, 128>, 128>* tileMap;
		std::array<std::array<uint8_t, 128>, 128>* unknownMap;
		SKIP(24);
		mm7::MapModel* models; // size field offset is 0x6A0D20
		uint32_t IDList_size;
		mm7::ObjectRef2* IDList; // size field offset is 0x6A0D4C
		std::array<std::array<int32_t, 128>, 128>* IDOffsets;
		int32_t loadedSkyBitmap;
		SKIP(980);
		uint32_t outdoorSpawns_size;
		mm7::SpawnPoint* outdoorSpawns; // size field offset is 0x6A1130
		int32_t outdoorRefillCount;
		uint32_t outdoorLastRefillDay;
		int32_t outdoorReputation;
		SKIP(4);
		int32_t outdoorSanityFacetsCount;
		int32_t outdoorSanitySpritesCount;
		int32_t sanityModelsCount;
		SKIP(12);
		union
		{
			mm7::MapExtra outdoorExtra;
			struct
			{
				int64_t outdoorLastVisitTime;
			};
		};
		std::array<std::array<uint8_t, 11>, 88> visibleMap1; // array of abits (real index = 7 - usual)
		std::array<std::array<uint8_t, 11>, 88> visibleMap2; // array of abits (real index = 7 - usual)
		SKIP(116372);
		int32_t mapStatsIndex;
		SKIP(516);
		std::array<uint8_t, 20> name; // Unknown type
		SKIP(8);
		uint32_t indoorOrOutdoor;
		SKIP(97);
		bool noNPC;
		SKIP(490);
		mm7::BlvHeader indoorHeader;
		uint32_t vertexes_size;
		mm7::MapVertex* vertexes; // size field offset is 0x6BE4B8
		uint32_t facets_size;
		mm7::MapFacet* facets; // size field offset is 0x6BE4C0
		uint32_t facetData_size;
		mm7::FacetData* facetData; // size field offset is 0x6BE4C8
		uint32_t rooms_size;
		mm7::MapRoom* rooms; // size field offset is 0x6BE4D0
		uint32_t lights_size;
		mm7::MapLight* lights; // size field offset is 0x6BE4D8
		uint32_t doors_size;
		std::array<mm7::MapDoor, 200>* doors; // size field offset is 0x6BE4E0
		uint32_t BSPNodes_size;
		mm7::BSPNode* BSPNodes; // size field offset is 0x6BE4E8
		mm7::MapOutlines* outlines;
		SKIP(16);
		uint32_t indoorSpawns_size;
		mm7::SpawnPoint* indoorSpawns; // size field offset is 0x6BE504
		int32_t indoorRefillCount;
		uint32_t indoorLastRefillDay;
		int32_t indoorReputation;
		SKIP(4);
		int32_t indoorSanityFacetsCount;
		int32_t indoorSanitySpritesCount;
		std::array<uint8_t, 4> sanityDoorDataSize; // Unknown type
		// uint8_t* reputation; // real size is 0 | Unknown type
		// uint8_t* spawns; // real size is 0 | Unknown type
		// uint8_t* sanitySpritesCount; // real size is 0 | Unknown type
		// uint8_t* lastVisitTime; // real size is 0 | Unknown type
		// uint8_t* sanityFacetsCount; // real size is 0 | Unknown type
		// uint8_t* refillCount; // real size is 0 | Unknown type
		// uint8_t* lastRefillDay; // real size is 0 | Unknown type
		SKIP(12);
		union
		{
			mm7::MapExtra indoorExtra;
			struct
			{
				int64_t indoorLastVisitTime;
			};
		};
		std::array<uint8_t, 875> visibileOutlines; // array of abits (real index = 7 - usual)
		SKIP(518841);
		uint32_t terNorm_size;
		std::array<std::array<std::array<float, 2>, 128>, 128> terNormDist;
		std::array<std::array<std::array<int16_t, 2>, 128>, 128> terNormId;
		mm7::FloatVector* terNorm; // size field offset is 0x73D390
	};
	static_assert(sizeof(mm7::GameMap) == 0x76D398, "Invalid \"mm7::GameMap\" structure size");
	static_assert(offsetof(mm7::GameMap, spriteLights) == 5342836);
	static_assert(offsetof(mm7::GameMap, spriteLights_size) == 5347636);
	static_assert(offsetof(mm7::GameMap, vars) == 6179600);
	static_assert(offsetof(mm7::GameMap, chests) == 6180816);
	static_assert(offsetof(mm7::GameMap, chests_size) == 6287296);
	static_assert(offsetof(mm7::GameMap, monsters) == 6287320);
	static_assert(offsetof(mm7::GameMap, monsters_size) == 6705320);
	static_assert(offsetof(mm7::GameMap, objects_size) == 6705324);
	static_assert(offsetof(mm7::GameMap, objects) == 6705328);
	static_assert(offsetof(mm7::GameMap, soundSprites) == 6817336);
	static_assert(offsetof(mm7::GameMap, soundSprites_size) == 6817376);
	static_assert(offsetof(mm7::GameMap, sprites) == 6829392);
	static_assert(offsetof(mm7::GameMap, sprites_size) == 6925392);
	static_assert(offsetof(mm7::GameMap, outdoorHeader) == 6950000);
	static_assert(offsetof(mm7::GameMap, tilesets) == 6950160);
	static_assert(offsetof(mm7::GameMap, models_size) == 6950176);
	static_assert(offsetof(mm7::GameMap, heightMap) == 6950180);
	static_assert(offsetof(mm7::GameMap, tileMap) == 6950184);
	static_assert(offsetof(mm7::GameMap, unknownMap) == 6950188);
	static_assert(offsetof(mm7::GameMap, models) == 6950216);
	static_assert(offsetof(mm7::GameMap, IDList_size) == 6950220);
	static_assert(offsetof(mm7::GameMap, IDList) == 6950224);
	static_assert(offsetof(mm7::GameMap, IDOffsets) == 6950228);
	static_assert(offsetof(mm7::GameMap, loadedSkyBitmap) == 6950232);
	static_assert(offsetof(mm7::GameMap, outdoorSpawns_size) == 6951216);
	static_assert(offsetof(mm7::GameMap, outdoorSpawns) == 6951220);
	static_assert(offsetof(mm7::GameMap, outdoorRefillCount) == 6951224);
	static_assert(offsetof(mm7::GameMap, outdoorLastRefillDay) == 6951228);
	static_assert(offsetof(mm7::GameMap, outdoorReputation) == 6951232);
	static_assert(offsetof(mm7::GameMap, outdoorSanityFacetsCount) == 6951240);
	static_assert(offsetof(mm7::GameMap, outdoorSanitySpritesCount) == 6951244);
	static_assert(offsetof(mm7::GameMap, sanityModelsCount) == 6951248);
	static_assert(offsetof(mm7::GameMap, outdoorExtra) == 6951264);
	static_assert(offsetof(mm7::GameMap, outdoorLastVisitTime) == 6951264);
	static_assert(offsetof(mm7::GameMap, mapStatsIndex) == 7069628);
	static_assert(offsetof(mm7::GameMap, name) == 7070148);
	static_assert(offsetof(mm7::GameMap, indoorOrOutdoor) == 7070176);
	static_assert(offsetof(mm7::GameMap, noNPC) == 7070277);
	static_assert(offsetof(mm7::GameMap, indoorHeader) == 7070768);
	static_assert(offsetof(mm7::GameMap, vertexes_size) == 7070904);
	static_assert(offsetof(mm7::GameMap, vertexes) == 7070908);
	static_assert(offsetof(mm7::GameMap, facets_size) == 7070912);
	static_assert(offsetof(mm7::GameMap, facets) == 7070916);
	static_assert(offsetof(mm7::GameMap, facetData_size) == 7070920);
	static_assert(offsetof(mm7::GameMap, facetData) == 7070924);
	static_assert(offsetof(mm7::GameMap, rooms_size) == 7070928);
	static_assert(offsetof(mm7::GameMap, rooms) == 7070932);
	static_assert(offsetof(mm7::GameMap, lights_size) == 7070936);
	static_assert(offsetof(mm7::GameMap, lights) == 7070940);
	static_assert(offsetof(mm7::GameMap, doors_size) == 7070944);
	static_assert(offsetof(mm7::GameMap, doors) == 7070948);
	static_assert(offsetof(mm7::GameMap, BSPNodes_size) == 7070952);
	static_assert(offsetof(mm7::GameMap, BSPNodes) == 7070956);
	static_assert(offsetof(mm7::GameMap, outlines) == 7070960);
	static_assert(offsetof(mm7::GameMap, indoorSpawns_size) == 7070980);
	static_assert(offsetof(mm7::GameMap, indoorSpawns) == 7070984);
	static_assert(offsetof(mm7::GameMap, indoorRefillCount) == 7070988);
	static_assert(offsetof(mm7::GameMap, indoorLastRefillDay) == 7070992);
	static_assert(offsetof(mm7::GameMap, indoorReputation) == 7070996);
	static_assert(offsetof(mm7::GameMap, indoorSanityFacetsCount) == 7071004);
	static_assert(offsetof(mm7::GameMap, indoorSanitySpritesCount) == 7071008);
	static_assert(offsetof(mm7::GameMap, sanityDoorDataSize) == 7071012);
	static_assert(offsetof(mm7::GameMap, indoorExtra) == 7071028);
	static_assert(offsetof(mm7::GameMap, indoorLastVisitTime) == 7071028);
	static_assert(offsetof(mm7::GameMap, terNorm_size) == 7590800);
	static_assert(offsetof(mm7::GameMap, terNormDist) == 7590804);
	static_assert(offsetof(mm7::GameMap, terNormId) == 7721876);
	static_assert(offsetof(mm7::GameMap, terNorm) == 7787412);

	struct MonstersTxtItem // size: 0x58
	{
		char* name; // EditPChar
		char* picture; // EditPChar
		uint8_t level;
		uint8_t treasureItemPercent;
		uint8_t treasureDiceCount;
		uint8_t treasureDiceSides;
		uint8_t treasureItemLevel;
		uint8_t treasureItemType;
		uint8_t fly;
		uint8_t moveType;
		uint8_t AIType;
		uint8_t hostileType;
		SKIP(1);
		uint8_t bonus;
		uint8_t bonusMul;
		mm7::MonsterAttackInfo attack1;
		uint8_t attack2Chance;
		mm7::MonsterAttackInfo attack2;
		uint8_t spellChance;
		uint8_t spell;
		uint8_t spell2Chance;
		uint8_t spell2;
		union
		{
			struct // size: 0xA, MMExt union
			{
				uint8_t _0;
				uint8_t _1;
				uint8_t _2;
				uint8_t _3;
				uint8_t _7;
				uint8_t _6;
				uint8_t _8;
				uint8_t _9;
				uint8_t _10;
				uint8_t _4;
			} resistances;
			static_assert(sizeof(resistances) == 0xA, "Invalid \"resistances\" structure size");
			struct
			{
				uint8_t fireResistance;
				uint8_t airResistance;
				uint8_t waterResistance;
				uint8_t earthResistance;
				uint8_t mindResistance;
				uint8_t spiritResistance;
				uint8_t bodyResistance;
				uint8_t lightResistance;
				uint8_t darkResistance;
				uint8_t physResistance;
			};
		};
		uint8_t special;
		uint8_t specialA;
		uint8_t specialB;
		uint8_t specialC;
		uint8_t prefNum;
		SKIP(1);
		uint16_t id;
		uint16_t bloodSplat;
		uint16_t spellSkill;
		uint16_t spell2Skill;
		uint16_t specialD;
		SKIP(2);
		union
		{
			int32_t fullHitPoints;
			int32_t fullHP;
		};
		int32_t armorClass;
		union
		{
			int32_t experience;
			int32_t exp;
		};
		int32_t moveSpeed;
		int32_t attackRecovery;
		union
		{
			int32_t prefClass;
			struct
			{
				struct // size: 0x2, MMExt union
				{
					bool knight : 1;
					bool paladin : 1;
					bool archer : 1;
					bool druid : 1;
					bool cleric : 1;
					bool sorcerer : 1;
					bool ranger : 1;
					bool thief : 1;
					bool monk : 1;
					bool male : 1;
					bool female : 1;
					bool human : 1;
					bool elf : 1;
					bool dwarf : 1;
					bool goblin : 1;
				} prefers;
				static_assert(sizeof(prefers) == 0x2, "Invalid \"prefers\" structure size");
			};
		};
	};
	static_assert(sizeof(mm7::MonstersTxtItem) == 0x58, "Invalid \"mm7::MonstersTxtItem\" structure size");
	static_assert(offsetof(mm7::MonstersTxtItem, picture) == 4);
	static_assert(offsetof(mm7::MonstersTxtItem, level) == 8);
	static_assert(offsetof(mm7::MonstersTxtItem, treasureItemPercent) == 9);
	static_assert(offsetof(mm7::MonstersTxtItem, treasureDiceCount) == 10);
	static_assert(offsetof(mm7::MonstersTxtItem, treasureDiceSides) == 11);
	static_assert(offsetof(mm7::MonstersTxtItem, treasureItemLevel) == 12);
	static_assert(offsetof(mm7::MonstersTxtItem, treasureItemType) == 13);
	static_assert(offsetof(mm7::MonstersTxtItem, fly) == 14);
	static_assert(offsetof(mm7::MonstersTxtItem, moveType) == 15);
	static_assert(offsetof(mm7::MonstersTxtItem, AIType) == 16);
	static_assert(offsetof(mm7::MonstersTxtItem, hostileType) == 17);
	static_assert(offsetof(mm7::MonstersTxtItem, bonus) == 19);
	static_assert(offsetof(mm7::MonstersTxtItem, bonusMul) == 20);
	static_assert(offsetof(mm7::MonstersTxtItem, attack1) == 21);
	static_assert(offsetof(mm7::MonstersTxtItem, attack2Chance) == 26);
	static_assert(offsetof(mm7::MonstersTxtItem, attack2) == 27);
	static_assert(offsetof(mm7::MonstersTxtItem, spellChance) == 32);
	static_assert(offsetof(mm7::MonstersTxtItem, spell) == 33);
	static_assert(offsetof(mm7::MonstersTxtItem, spell2Chance) == 34);
	static_assert(offsetof(mm7::MonstersTxtItem, spell2) == 35);
	static_assert(offsetof(mm7::MonstersTxtItem, resistances) == 36);
	static_assert(offsetof(mm7::MonstersTxtItem, fireResistance) == 36);
	static_assert(offsetof(mm7::MonstersTxtItem, airResistance) == 37);
	static_assert(offsetof(mm7::MonstersTxtItem, waterResistance) == 38);
	static_assert(offsetof(mm7::MonstersTxtItem, earthResistance) == 39);
	static_assert(offsetof(mm7::MonstersTxtItem, mindResistance) == 40);
	static_assert(offsetof(mm7::MonstersTxtItem, spiritResistance) == 41);
	static_assert(offsetof(mm7::MonstersTxtItem, bodyResistance) == 42);
	static_assert(offsetof(mm7::MonstersTxtItem, lightResistance) == 43);
	static_assert(offsetof(mm7::MonstersTxtItem, darkResistance) == 44);
	static_assert(offsetof(mm7::MonstersTxtItem, physResistance) == 45);
	static_assert(offsetof(mm7::MonstersTxtItem, special) == 46);
	static_assert(offsetof(mm7::MonstersTxtItem, specialA) == 47);
	static_assert(offsetof(mm7::MonstersTxtItem, specialB) == 48);
	static_assert(offsetof(mm7::MonstersTxtItem, specialC) == 49);
	static_assert(offsetof(mm7::MonstersTxtItem, prefNum) == 50);
	static_assert(offsetof(mm7::MonstersTxtItem, id) == 52);
	static_assert(offsetof(mm7::MonstersTxtItem, bloodSplat) == 54);
	static_assert(offsetof(mm7::MonstersTxtItem, spellSkill) == 56);
	static_assert(offsetof(mm7::MonstersTxtItem, spell2Skill) == 58);
	static_assert(offsetof(mm7::MonstersTxtItem, specialD) == 60);
	static_assert(offsetof(mm7::MonstersTxtItem, fullHitPoints) == 64);
	static_assert(offsetof(mm7::MonstersTxtItem, fullHP) == 64);
	static_assert(offsetof(mm7::MonstersTxtItem, armorClass) == 68);
	static_assert(offsetof(mm7::MonstersTxtItem, experience) == 72);
	static_assert(offsetof(mm7::MonstersTxtItem, exp) == 72);
	static_assert(offsetof(mm7::MonstersTxtItem, moveSpeed) == 76);
	static_assert(offsetof(mm7::MonstersTxtItem, attackRecovery) == 80);
	static_assert(offsetof(mm7::MonstersTxtItem, prefClass) == 84);
	static_assert(offsetof(mm7::MonstersTxtItem, prefers) == 84);

	struct NPC // size: 0x4C
	{
		union
		{
			char* name; // EditPChar
			uint32_t exist; // 4-byte boolean
		};
		int32_t pic;
		union
		{
			uint32_t bits;
			struct
			{
				bool bribedBefore : 1;
				bool talkedBefore : 1;
				bool threatenedBefore : 1;
				SKIPBITS(4);
				bool hired : 1;
			};
		};
		int32_t fame;
		int32_t rep;
		int32_t house;
		int32_t profession;
		int32_t greet;
		int32_t joins;
		int32_t tellsNews;
		union
		{
			std::array<int32_t, 6> events;
			struct
			{
				int32_t eventA;
				int32_t eventB;
				int32_t eventC;
				int32_t eventD;
				int32_t eventE;
				int32_t eventF;
			};
		};
		int32_t sex;
		int32_t usedSpell;
		int32_t newsTopic;
	};
	static_assert(sizeof(mm7::NPC) == 0x4C, "Invalid \"mm7::NPC\" structure size");
	static_assert(offsetof(mm7::NPC, pic) == 4);
	static_assert(offsetof(mm7::NPC, bits) == 8);
	static_assert(offsetof(mm7::NPC, fame) == 12);
	static_assert(offsetof(mm7::NPC, rep) == 16);
	static_assert(offsetof(mm7::NPC, house) == 20);
	static_assert(offsetof(mm7::NPC, profession) == 24);
	static_assert(offsetof(mm7::NPC, greet) == 28);
	static_assert(offsetof(mm7::NPC, joins) == 32);
	static_assert(offsetof(mm7::NPC, tellsNews) == 36);
	static_assert(offsetof(mm7::NPC, events) == 40);
	static_assert(offsetof(mm7::NPC, eventA) == 40);
	static_assert(offsetof(mm7::NPC, eventB) == 44);
	static_assert(offsetof(mm7::NPC, eventC) == 48);
	static_assert(offsetof(mm7::NPC, eventD) == 52);
	static_assert(offsetof(mm7::NPC, eventE) == 56);
	static_assert(offsetof(mm7::NPC, eventF) == 60);
	static_assert(offsetof(mm7::NPC, sex) == 64);
	static_assert(offsetof(mm7::NPC, usedSpell) == 68);
	static_assert(offsetof(mm7::NPC, newsTopic) == 72);

	struct GameParty // size: 0xAE3064
	{
		SKIP(5274220);
		std::array<uint8_t, 4> currentPlayer; // Unknown type
		SKIP(5690584);
		std::array<std::array<uint8_t, 4>, 4> players; // Unknown type
		SKIP(360212);
		int64_t lastRegenerationTime;
		union
		{
			std::array<int64_t, 5> monsHuntReset;
			std::array<int64_t, 5> nextBountyHunt;
		};
		SKIP(1224);
		std::array<int64_t, 29> history; // MMExt: 1..29, here 0..28
		std::array<int64_t, 20> specialDates; // MMExt: 1..20, here 0..19
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
		int32_t lookAngle;
		int32_t lastX;
		int32_t lastY;
		int32_t lastZ;
		int32_t lastDirection;
		int32_t lastLookAngle;
		int32_t lastEyeLevel;
		int32_t speedX;
		int32_t speedY;
		int32_t speedZ;
		SKIP(4);
		int32_t stableZ;
		int32_t lastStandFacet;
		SKIP(8);
		int32_t fallStartZ;
		uint32_t flying; // 4-byte boolean
		SKIP(32);
		int32_t food;
		SKIP(8);
		int32_t gold;
		int32_t bankGold;
		int32_t deaths;
		SKIP(4);
		union
		{
			int32_t pritsonTerms;
			int32_t prisonTerms;
		};
		int32_t bountiesCollected;
		SKIP(4);
		union
		{
			std::array<int16_t, 5> bountyHuntTarget;
			std::array<int16_t, 5> monsHuntTarget;
		};
		union
		{
			std::array<uint16_t, 5> bountyHuntKilled; // 2-byte boolean
			std::array<int16_t, 5> monsHuntKilled;
		};
		SKIP(1);
		std::array<uint8_t, 64> QBits; // MMExt: 1..512, here 0..511 | array of abits (real index = 7 - usual)
		std::array<bool, 16> arcomageWins; // MMExt: 108..123, here 0..15
		int8_t inArenaQuest;
		int8_t arenaWinsPage;
		int8_t arenaWinsSquire;
		int8_t arenaWinsKnight;
		int8_t arenaWinsLord;
		std::array<bool, 68> artifactsFound; // MMExt: 500..567, here 0..67
		std::array<uint8_t, 31> autonotesBits; // MMExt: 1..255, here 0..254 | array of abits (real index = 7 - usual)
		SKIP(107);
		int32_t alignment;
		union
		{
			std::array<mm7::SpellBuff, 20> spellBuffs;
			struct
			{
				// uint8_t* reputation; // real size is 0 | Unknown type
			};
		};
		std::array<mm7::Player, 4> playersArray;
		std::array<mm7::NPC, 2> hiredNPC; // MMExt: 1..2, here 0..1
		SKIP(36);
		union
		{
			int32_t stateBits;
			struct
			{
				SKIPBITS(1);
				bool needRender : 1;
				bool drowning : 1;
				bool inAir : 1;
				bool enemyDetectorRed : 1;
				bool enemyDetectorYellow : 1;
				bool flyingBit : 1;
				bool waterWalkingBit : 1;
				bool inJumpSpell : 1;
				bool inLava : 1;
			};
		};
		SKIP(59640);
		std::array<std::array<char, 100>, 2> hiredNPCName; // MMExt: 1..2, here 0..1 | fixed size string, requires null terminator
		SKIP(236);
		int32_t fine;
	};
	static_assert(sizeof(mm7::GameParty) == 0xAE3064, "Invalid \"mm7::GameParty\" structure size");
	static_assert(offsetof(mm7::GameParty, currentPlayer) == 5274220);
	static_assert(offsetof(mm7::GameParty, players) == 10964808);
	static_assert(offsetof(mm7::GameParty, lastRegenerationTime) == 11325036);
	static_assert(offsetof(mm7::GameParty, monsHuntReset) == 11325044);
	static_assert(offsetof(mm7::GameParty, nextBountyHunt) == 11325044);
	static_assert(offsetof(mm7::GameParty, history) == 11326308);
	static_assert(offsetof(mm7::GameParty, specialDates) == 11326540);
	static_assert(offsetof(mm7::GameParty, pos) == 11326700);
	static_assert(offsetof(mm7::GameParty, x) == 11326700);
	static_assert(offsetof(mm7::GameParty, y) == 11326704);
	static_assert(offsetof(mm7::GameParty, z) == 11326708);
	static_assert(offsetof(mm7::GameParty, direction) == 11326712);
	static_assert(offsetof(mm7::GameParty, lookAngle) == 11326716);
	static_assert(offsetof(mm7::GameParty, lastX) == 11326720);
	static_assert(offsetof(mm7::GameParty, lastY) == 11326724);
	static_assert(offsetof(mm7::GameParty, lastZ) == 11326728);
	static_assert(offsetof(mm7::GameParty, lastDirection) == 11326732);
	static_assert(offsetof(mm7::GameParty, lastLookAngle) == 11326736);
	static_assert(offsetof(mm7::GameParty, lastEyeLevel) == 11326740);
	static_assert(offsetof(mm7::GameParty, speedX) == 11326744);
	static_assert(offsetof(mm7::GameParty, speedY) == 11326748);
	static_assert(offsetof(mm7::GameParty, speedZ) == 11326752);
	static_assert(offsetof(mm7::GameParty, stableZ) == 11326760);
	static_assert(offsetof(mm7::GameParty, lastStandFacet) == 11326764);
	static_assert(offsetof(mm7::GameParty, fallStartZ) == 11326776);
	static_assert(offsetof(mm7::GameParty, flying) == 11326780);
	static_assert(offsetof(mm7::GameParty, food) == 11326816);
	static_assert(offsetof(mm7::GameParty, gold) == 11326828);
	static_assert(offsetof(mm7::GameParty, bankGold) == 11326832);
	static_assert(offsetof(mm7::GameParty, deaths) == 11326836);
	static_assert(offsetof(mm7::GameParty, pritsonTerms) == 11326844);
	static_assert(offsetof(mm7::GameParty, prisonTerms) == 11326844);
	static_assert(offsetof(mm7::GameParty, bountiesCollected) == 11326848);
	static_assert(offsetof(mm7::GameParty, bountyHuntTarget) == 11326856);
	static_assert(offsetof(mm7::GameParty, monsHuntTarget) == 11326856);
	static_assert(offsetof(mm7::GameParty, bountyHuntKilled) == 11326866);
	static_assert(offsetof(mm7::GameParty, monsHuntKilled) == 11326866);
	static_assert(offsetof(mm7::GameParty, arcomageWins) == 11326941);
	static_assert(offsetof(mm7::GameParty, inArenaQuest) == 11326957);
	static_assert(offsetof(mm7::GameParty, arenaWinsPage) == 11326958);
	static_assert(offsetof(mm7::GameParty, arenaWinsSquire) == 11326959);
	static_assert(offsetof(mm7::GameParty, arenaWinsKnight) == 11326960);
	static_assert(offsetof(mm7::GameParty, arenaWinsLord) == 11326961);
	static_assert(offsetof(mm7::GameParty, artifactsFound) == 11326962);
	static_assert(offsetof(mm7::GameParty, alignment) == 11327168);
	static_assert(offsetof(mm7::GameParty, spellBuffs) == 11327172);
	static_assert(offsetof(mm7::GameParty, playersArray) == 11327492);
	static_assert(offsetof(mm7::GameParty, hiredNPC) == 11355380);
	static_assert(offsetof(mm7::GameParty, stateBits) == 11355568);
	static_assert(offsetof(mm7::GameParty, hiredNPCName) == 11415212);
	static_assert(offsetof(mm7::GameParty, fine) == 11415648);

	struct SpcItemsTxtItem // size: 0x1C
	{
		char* nameAdd; // EditPChar
		char* bonusStat; // EditPChar
		union
		{
			std::array<uint8_t, 12> chanceForSlot;
			struct
			{
				uint8_t W1;
				uint8_t W2;
				uint8_t miss;
				uint8_t arm;
				uint8_t shld;
				uint8_t helm;
				uint8_t belt;
				uint8_t cape;
				uint8_t gaunt;
				uint8_t boot;
				uint8_t ring;
				uint8_t amul;
			};
		};
		int32_t value;
		uint8_t lvl;
		SKIP(3);
	};
	static_assert(sizeof(mm7::SpcItemsTxtItem) == 0x1C, "Invalid \"mm7::SpcItemsTxtItem\" structure size");
	static_assert(offsetof(mm7::SpcItemsTxtItem, bonusStat) == 4);
	static_assert(offsetof(mm7::SpcItemsTxtItem, chanceForSlot) == 8);
	static_assert(offsetof(mm7::SpcItemsTxtItem, W1) == 8);
	static_assert(offsetof(mm7::SpcItemsTxtItem, W2) == 9);
	static_assert(offsetof(mm7::SpcItemsTxtItem, miss) == 10);
	static_assert(offsetof(mm7::SpcItemsTxtItem, arm) == 11);
	static_assert(offsetof(mm7::SpcItemsTxtItem, shld) == 12);
	static_assert(offsetof(mm7::SpcItemsTxtItem, helm) == 13);
	static_assert(offsetof(mm7::SpcItemsTxtItem, belt) == 14);
	static_assert(offsetof(mm7::SpcItemsTxtItem, cape) == 15);
	static_assert(offsetof(mm7::SpcItemsTxtItem, gaunt) == 16);
	static_assert(offsetof(mm7::SpcItemsTxtItem, boot) == 17);
	static_assert(offsetof(mm7::SpcItemsTxtItem, ring) == 18);
	static_assert(offsetof(mm7::SpcItemsTxtItem, amul) == 19);
	static_assert(offsetof(mm7::SpcItemsTxtItem, value) == 20);
	static_assert(offsetof(mm7::SpcItemsTxtItem, lvl) == 24);

	struct GameStructure // size: 0x600201BC
	{
		static inline mm7::GameParty* const party = 0;
		static inline mm7::GameMouse* const mouse = 0;
		static inline mm7::GameMap* const map = 0;
		static inline mm7::Weather* const weather = 0;
		static inline mm7::Arcomage* const arcomage = 0;
		static inline mm7::GameRaces* const races = 0;
		static inline mm7::GameClasses* const classes = 0;
		static inline mm7::GameClassKinds* const classKinds = 0;
		static inline mm7::DialogLogic* const dialogLogic = 0;

		static mm7::MonstersTxtItem* monstersTxt; // array converted to pointer to not break with limits removal scripts
		static uint32_t* monstersTxt_size; // pointer to size, set during initialization by getting data from lua
		static char** placeMonTxt; // array converted to pointer to not break with limits removal scripts
		static uint32_t* placeMonTxt_size; // pointer to size, set during initialization by getting data from lua
		static int16_t* mapDoorSound; // array converted to pointer to not break with limits removal scripts
		static mm7::FogChances* mapFogChances; // array converted to pointer to not break with limits removal scripts
		static char** classNames; // array converted to pointer to not break with limits removal scripts
		static int64_t* shopNextRefill; // array converted to pointer to not break with limits removal scripts
		static char** questsTxt; // array converted to pointer to not break with limits removal scripts
		static mm7::ItemsTxtItem* itemsTxt; // array converted to pointer to not break with limits removal scripts
		static uint32_t* itemsTxt_size; // pointer to size, set during initialization by getting data from lua
		static int64_t* shopTheftExpireTime; // array converted to pointer to not break with limits removal scripts
		static char** NPCTopic; // array converted to pointer to not break with limits removal scripts
		static mm7::EventLine* globalEvtLines; // array converted to pointer to not break with limits removal scripts
		static uint32_t* globalEvtLines_size; // pointer to size, set during initialization by getting data from lua
		static int16_t* NPCGroup; // array converted to pointer to not break with limits removal scripts
		static mm7::HouseMovie* houseMovies; // array converted to pointer to not break with limits removal scripts
		static char** transTxt; // array converted to pointer to not break with limits removal scripts
		static mm7::NPC* NPCDataTxt; // array converted to pointer to not break with limits removal scripts
		static mm7::NPC* NPC; // array converted to pointer to not break with limits removal scripts
		static uint32_t* NPC_size; // pointer to size, set during initialization by getting data from lua
		static mm7::Events2DItem* houses; // array converted to pointer to not break with limits removal scripts
		static int32_t* autonoteCategory; // array converted to pointer to not break with limits removal scripts
		static char** autonoteTxt; // array converted to pointer to not break with limits removal scripts
		static mm7::TravelInfo* transportLocations; // array converted to pointer to not break with limits removal scripts
		static char** NPCNews; // array converted to pointer to not break with limits removal scripts
		static char** NPCText; // array converted to pointer to not break with limits removal scripts
		static mm7::MapStatsItem* mapStats; // array converted to pointer to not break with limits removal scripts
		static uint32_t* mapStats_size; // pointer to size, set during initialization by getting data from lua

		// uint8_t* randSeed; // real size is 0 | Unknown type
		SKIP(4386761);
		std::array<uint8_t, 1> minMeleeRecoveryTime; // Unknown type
		SKIP(19266);
		char* winMapIndex; // EditConstPChar - unprotect before/protect after edit
		SKIP(114554);
		char* summonElementalC; // EditConstPChar - unprotect before/protect after edit
		SKIP(8);
		char* summonElementalB; // EditConstPChar - unprotect before/protect after edit
		SKIP(3);
		char* summonElementalA; // EditConstPChar - unprotect before/protect after edit
		SKIP(68036);
		// uint8_t* baseYear; // real size is 0 | Unknown type
		SKIP(24090);
		std::array<uint8_t, 4> newGameMap; // Unknown type
		SKIP(55777);
		std::array<uint8_t, 4> flyCeiling; // Unknown type
		SKIP(3243);
		std::array<uint8_t, 4> modelClimbRequirement; // Unknown type
		SKIP(113063);
		std::array<uint8_t, 4> maxBirthYear; // Unknown type
		SKIP(147788);
		std::array<uint8_t, 1> dialogTopicsLimit; // Unknown type
		SKIP(46115);
		std::array<uint8_t, 1> titleTrack; // Unknown type
		SKIP(140537);
		std::array<int16_t, 6> townPortalX;
		std::array<int16_t, 6> townPortalY;
		std::array<int16_t, 6> townPortalWidth;
		std::array<int16_t, 6> townPortalHeight;
		SKIP(2940);
		int32_t currentScreen;
		SKIP(628);
		std::array<int8_t, 88> monsterClassInfoY;
		SKIP(3848);
		std::array<std::array<uint8_t, 4>, 99> spellObjId; // MMExt: 1..99, here 0..98 | Unknown type
		SKIP(12);
		std::array<mm7::SpellInfo, 100> spells;
		SKIP(296);
		std::array<int32_t, 6> specialEnterX; // MMExt: 1..6, here 0..5
		std::array<int32_t, 6> specialEnterY; // MMExt: 1..6, here 0..5
		std::array<int32_t, 6> specialEnterZ; // MMExt: 1..6, here 0..5
		std::array<int32_t, 6> specialEnterDirection; // MMExt: 1..6, here 0..5
		SKIP(15784);
		std::array<uint8_t, 20> equipStat2ItemSlot;
		std::array<bool, 88> monsterClassSex; // MMExt: 1..88, here 0..87
		std::array<uint8_t, 88> monsterClassRace; // MMExt: 1..88, here 0..87
		SKIP(18004);
		std::array<mm7::TownPortalTownInfo, 6> townPortalInfo;
		std::array<char*, 25> playerFaces; // EditConstPChar - unprotect before/protect after edit
		SKIP(628);
		std::array<std::array<uint8_t, 25>, 49> standardPlayerSoundsCount; // MMExt: 1..49, here 0..48
		SKIP(7);
		std::array<mm7::FaceAnimationInfo, 110> standardFaceAnimations;
		SKIP(1936);
		std::array<int16_t, 13> skillRecoveryTimes;
		SKIP(408);
		std::array<int16_t, 99> spellSounds; // MMExt: 1..99, here 0..98
		SKIP(8768);
		std::array<char*, 19> shopBackgroundByType; // EditConstPChar - unprotect before/protect after edit
		SKIP(4);
		std::array<mm7::ShopItemKind, 14> shopWeaponKinds; // MMExt: 1..14, here 0..13
		SKIP(4);
		std::array<std::array<mm7::ShopItemKind, 2>, 14> shopArmorKinds; // MMExt: 15..28, here 0..13 | MMExt: 1..2, here 0..1
		std::array<int16_t, 13> shopMagicLevels; // MMExt: 29..41, here 0..12
		SKIP(2);
		std::array<int16_t, 12> shopAlchemistLevels; // MMExt: 42..53, here 0..11
		SKIP(100);
		std::array<mm7::ShopItemKind, 14> shopWeaponKindsSpecial; // MMExt: 1..14, here 0..13
		SKIP(4);
		std::array<std::array<mm7::ShopItemKind, 2>, 14> shopArmorKindsSpecial; // MMExt: 15..28, here 0..13 | MMExt: 1..2, here 0..1
		std::array<int16_t, 13> shopMagicLevelsSpecial; // MMExt: 29..41, here 0..12
		SKIP(2);
		std::array<int16_t, 12> shopAlchemistLevelsSpecial; // MMExt: 42..53, here 0..11
		SKIP(200);
		std::array<int32_t, 11> guildJoinCost;
		std::array<int16_t, 10> trainingLevels; // MMExt: 89..98, here 0..9
		SKIP(4);
		std::array<int32_t, 32> guildAwards; // MMExt: 139..170, here 0..31
		SKIP(1120);
		std::array<std::array<int8_t, 4>, 20> transportIndex; // MMExt: 54..73, here 0..19 | MMExt: 1..4, here 0..3
		SKIP(208);
		std::array<int16_t, 32> guildSpellLevels; // MMExt: 139..170, here 0..31
		SKIP(30956);
		int32_t turnBasedPhase;
		SKIP(53576);
		std::array<int32_t, 480> scanlineOffset;
		SKIP(3616);
		int32_t currentCharScreen;
		SKIP(2556);
		bool flashHistoryBook;
		bool flashAutonotesBook;
		bool flashQuestBook;
		SKIP(557);
		std::array<char*, 7> statsNames; // EditPChar
		SKIP(4);
		uint32_t ctrlPressed; // 4-byte boolean
		SKIP(32);
		mm7::Dlg* currentNPCDialog;
		SKIP(44);
		std::array<uint8_t, 4> currentPlayer; // Unknown type
		bool rightButtonPressed;
		SKIP(16331);
		uint32_t paused2; // 4-byte boolean
		SKIP(20);
		int32_t timeDelta2;
		SKIP(12);
		uint32_t paused; // 4-byte boolean
		SKIP(20);
		int32_t timeDelta;
		SKIP(3560);
		uint32_t actionsNext_size;
		std::array<mm7::ActionItem, 40> actionsNext; // size field offset is 0x50C868
		SKIP(4);
		uint32_t actions_size;
		std::array<mm7::ActionItem, 40> actions; // size field offset is 0x50CA50
		SKIP(434300);
		mm7::ProgressBar progressBar;
		SKIP(44);
		uint32_t loadingScreen; // 4-byte boolean
		SKIP(444);
		uint32_t needRedraw; // 4-byte boolean
		SKIP(106576);
		int32_t houseOwnerPic;
		SKIP(8);
		int32_t NPCCommand;
		int32_t dialogNPC;
		SKIP(836);
		std::array<int32_t, 6> houseNPCs; // MMExt: 1..6, here 0..5
		int32_t houseNPCSlot;
		SKIP(48);
		int32_t houseNPCSlotsCount;
		SKIP(128272);
		std::array<char, 2000> streetMessage; // fixed size string, requires null terminator
		SKIP(8);
		uint32_t mapEvtLines_size;
		SKIP(21652);
		mm7::MoveToMap moveToMap;
		SKIP(20);
		std::array<mm7::EventLine, 4400> mapEvtLines; // size field offset is 0x5B0F90
		SKIP(16);
		std::array<char, 200> statusMessage; // fixed size string, requires null terminator
		std::array<char, 200> mouseOverStatusMessage; // fixed size string, requires null terminator
		int32_t statusDisappearTime;
		SKIP(20);
		int32_t houseExitMap;
		SKIP(12);
		int32_t autonote_fnt;
		int32_t spell_fnt;
		int32_t arrus_fnt;
		int32_t lucida_fnt;
		int32_t book2_fnt;
		int32_t book_fnt;
		SKIP(4);
		int32_t create_fnt;
		int32_t cchar_fnt;
		int32_t comic_fnt;
		int32_t smallnum_fnt;
		SKIP(10148);
		std::array<char, 2000> textBuffer; // fixed size string, requires null terminator
		std::array<char, 2000> textBuffer2; // fixed size string, requires null terminator
		SKIP(104);
		uint32_t TFTBin_size;
		mm7::TFTItem* TFTBin; // size field offset is 0x5C6C38
		mm7::SFT SFTBin;
		SKIP(6408);
		std::array<char*, 36> classDescriptions; // EditPChar
		SKIP(8);
		std::array<char*, 7> statsDescriptions; // EditPChar
		SKIP(124);
		std::array<char*, 37> skillDesGM; // EditPChar
		SKIP(4);
		std::array<char*, 37> skillDesMaster; // EditPChar
		SKIP(4);
		std::array<char*, 37> skillDesExpert; // EditPChar
		SKIP(4);
		std::array<char*, 37> skillDesNormal; // EditPChar
		SKIP(4);
		std::array<char*, 37> skillDescriptions; // EditPChar
		SKIP(92);
		std::array<mm7::HistoryTxtItem, 29> historyTxt; // MMExt: 1..29, here 0..28
		SKIP(4);
		std::array<std::array<uint8_t, 89>, 89> hostileTxt;
		SKIP(5247);
		std::array<mm7::SpellsTxtItem, 100> spellsTxt;
		SKIP(61860);
		std::array<mm7::StdItemsTxtItem, 24> stdItemsTxt;
		std::array<mm7::SpcItemsTxtItem, 72> spcItemsTxt;
		SKIP(20384);
		std::array<std::array<int16_t, 50>, 50> potionTxt; // MMExt: 222..271, here 0..49 | MMExt: 222..271, here 0..49
		std::array<std::array<int16_t, 50>, 50> potNotesTxt; // MMExt: 222..271, here 0..49 | MMExt: 222..271, here 0..49
		SKIP(300);
		std::array<char*, 677> globalTxt; // EditPChar
		SKIP(1332);
		uint32_t overlayBin_size;
		mm7::OverlayItem* overlayBin; // size field offset is 0x5E4FC8
		SKIP(106484);
		uint32_t chestBin_size;
		mm7::DChestItem* chestBin; // size field offset is 0x5FEFC4
		uint32_t monListBin_size;
		mm7::MonListItem* monListBin; // MMExt: 1..0, here 0..-1 | size field offset is 0x5FEFCC
		SKIP(530012);
		uint32_t objListBin_size;
		mm7::ObjListItem* objListBin; // size field offset is 0x680630
		SKIP(108060);
		uint32_t decListBin_size;
		mm7::DecListItem* decListBin; // size field offset is 0x69AC54
		SKIP(48);
		std::array<int32_t, 30> keyCodes;
		std::array<int32_t, 30> keyTypes;
		SKIP(22820);
		mm7::Lod saveGameLod;
		SKIP(4);
		mm7::Lod gamesLod;
		SKIP(168);
		int32_t mainMenuCode;
		int32_t exitMapAction;
		SKIP(119548);
		uint32_t tileBin_size;
		mm7::TileItem* tileBin; // size field offset is 0x6BDEC8
		int32_t exitLevelCode;
		SKIP(48);
		int32_t outdoorViewMul;
		int32_t outdoorViewDiv;
		SKIP(616);
		uint32_t windowHandle;
		SKIP(119);
		int32_t soundVolume;
		SKIP(1765);
		mm7::Lod eventsLod;
		SKIP(72060);
		mm7::BitmapsLod iconsLod;
		mm7::SpritesLod spritesLod;
		mm7::BitmapsLod bitmapsLod;
		SKIP(135936);
		std::array<char*, 82> scrollTxt; // MMExt: 700..781, here 0..81 | EditPChar
		union
		{
			struct __awardsTxt
			{
				char* value;
				SKIP(4);
			};
			std::array<__awardsTxt, 105> awardsTxt; // EditPChar
			struct
			{
				SKIP(4);
				struct __awardsSort
				{
					int32_t value;
					SKIP(4);
				};
				std::array<__awardsSort, 105> awardsSort;
			};
		};
		SKIP(76156);
		std::array<std::array<char*, 2>, 540> NPCNames; // EditPChar
		std::array<mm7::NPCProfTxtItem, 59> NPCProfTxt;
		std::array<mm7::NPC, 100> streetNPC; // size field offset is 0x73C010
		SKIP(7136);
		std::array<std::array<char*, 2>, 206> NPCGreet; // EditPChar
		SKIP(204);
		uint32_t streetNPC_size;
		SKIP(12);
		std::array<int32_t, 2> NPCNamesCount;
		SKIP(232);
		std::array<char*, 59> NPCProfNames; // EditPChar
		SKIP(12);
		std::array<std::array<char*, 7>, 4> merchantTxt; // EditPChar
		SKIP(3378400);
		struct // size: 0xC, MMExt union
		{
			int64_t delay;
			int16_t animation;
			int16_t playerIndex;
		} delayedFaceAnimation;
		static_assert(sizeof(delayedFaceAnimation) == 0xC, "Invalid \"delayedFaceAnimation\" structure size");
		uint32_t IFTBin_size;
		mm7::IFTItem* IFTBin; // size field offset is 0xA74F64
		uint32_t PFTBin_size;
		mm7::PFTItem* PFTBin; // size field offset is 0xA74F6C
		SKIP(360176);
		int64_t time;
		SKIP(512);
		std::array<int64_t, 32> guildNextRefill; // MMExt: 139..170, here 0..31
		SKIP(984);
		int32_t year;
		int32_t month;
		int32_t weekOfMonth;
		int32_t dayOfMonth;
		int32_t hour;
		int32_t minute;
		int32_t second;
		SKIP(340);
		uint32_t turnBased; // 4-byte boolean
		SKIP(28408);
		bool needRender : 1;
		SKIP(3);
		std::array<std::array<mm7::Item, 12>, 53> shopItems;
		std::array<std::array<mm7::Item, 12>, 53> shopSpecialItems;
		std::array<std::array<std::array<mm7::Item, 12>, 1>, 32> guildItems; // MMExt: 139..170, here 0..31
		SKIP(224);
		int32_t armageddonTimeLeft;
		int32_t armageddonSkill;
		std::array<int32_t, 4> turnBasedDelays;
		SKIP(452);
		std::array<char*, 37> skillNames; // EditPChar
		SKIP(3205252);
		union
		{
			mm7::GameScreen screen;
			struct
			{
				SKIP(262196);
				std::array<std::array<mm7::ObjectRef, 640>, 480>* objectByPixel;
				SKIP(32);
				uint32_t windowed;
				SKIP(44);
				uint32_t rendererD3D;
			};
		};
		SKIP(1341092);
		int32_t redbookHandle;
		int32_t MSSHandle;
		SKIP(2520);
		uint32_t soundsBin_size;
		mm7::SoundsItem* soundsBin; // size field offset is 0xF79BDC
		SKIP(70660);
		std::array<int32_t, 12> guildItemIconPtr;
		int32_t housePicType;
		int32_t houseScreen;
		SKIP(8);
		int32_t houseAllowAction;
		int32_t houseActionInfo;
		int32_t houseTeachMastery;
		int32_t houseCost;
		SKIP(40);
		int32_t houseItemsCount;
		SKIP(4);
		char* NPCMessage; // EditPChar
		SKIP(2372);
		int32_t smackVideo;
		SKIP(56);
		uint32_t isMovieLooped; // 4-byte boolean
		SKIP(24);
		int32_t binkVideo;
		SKIP(24);
		int32_t movieKind;
		SKIP(37230932);
		mm7::PatchOptions patchOptions;
		SKIP(1644144);
		mm7::CustomLods customLods;
		SKIP(6676064);
		std::array<uint8_t, 4> titleTrackOffset; // Unknown type
		SKIP(7836);
		mm7::MonsterKind* monsterKinds; // size field offset is 0x3B0306C
		uint32_t monsterKinds_size;
		SKIP(184);
		mm7::MissileSetup* missileSetup; // size field offset is 0x3B0312C
		uint32_t missileSetup_size;
		SKIP(1548865676);
	};
	static_assert(sizeof(mm7::GameStructure) == 0x600201BC, "Invalid \"mm7::GameStructure\" structure size");
	static_assert(offsetof(mm7::GameStructure, minMeleeRecoveryTime) == 4386761);
	static_assert(offsetof(mm7::GameStructure, winMapIndex) == 4406028);
	static_assert(offsetof(mm7::GameStructure, summonElementalC) == 4520586);
	static_assert(offsetof(mm7::GameStructure, summonElementalB) == 4520598);
	static_assert(offsetof(mm7::GameStructure, summonElementalA) == 4520605);
	static_assert(offsetof(mm7::GameStructure, newGameMap) == 4612735);
	static_assert(offsetof(mm7::GameStructure, flyCeiling) == 4668516);
	static_assert(offsetof(mm7::GameStructure, modelClimbRequirement) == 4671763);
	static_assert(offsetof(mm7::GameStructure, maxBirthYear) == 4784830);
	static_assert(offsetof(mm7::GameStructure, dialogTopicsLimit) == 4932622);
	static_assert(offsetof(mm7::GameStructure, titleTrack) == 4978738);
	static_assert(offsetof(mm7::GameStructure, townPortalX) == 5119276);
	static_assert(offsetof(mm7::GameStructure, townPortalY) == 5119288);
	static_assert(offsetof(mm7::GameStructure, townPortalWidth) == 5119300);
	static_assert(offsetof(mm7::GameStructure, townPortalHeight) == 5119312);
	static_assert(offsetof(mm7::GameStructure, currentScreen) == 5122264);
	static_assert(offsetof(mm7::GameStructure, monsterClassInfoY) == 5122896);
	static_assert(offsetof(mm7::GameStructure, spellObjId) == 5126832);
	static_assert(offsetof(mm7::GameStructure, spells) == 5127240);
	static_assert(offsetof(mm7::GameStructure, specialEnterX) == 5129536);
	static_assert(offsetof(mm7::GameStructure, specialEnterY) == 5129560);
	static_assert(offsetof(mm7::GameStructure, specialEnterZ) == 5129584);
	static_assert(offsetof(mm7::GameStructure, specialEnterDirection) == 5129608);
	static_assert(offsetof(mm7::GameStructure, equipStat2ItemSlot) == 5145416);
	static_assert(offsetof(mm7::GameStructure, monsterClassSex) == 5145436);
	static_assert(offsetof(mm7::GameStructure, monsterClassRace) == 5145524);
	static_assert(offsetof(mm7::GameStructure, townPortalInfo) == 5163616);
	static_assert(offsetof(mm7::GameStructure, playerFaces) == 5163736);
	static_assert(offsetof(mm7::GameStructure, standardPlayerSoundsCount) == 5164464);
	static_assert(offsetof(mm7::GameStructure, standardFaceAnimations) == 5165696);
	static_assert(offsetof(mm7::GameStructure, skillRecoveryTimes) == 5168512);
	static_assert(offsetof(mm7::GameStructure, spellSounds) == 5168946);
	static_assert(offsetof(mm7::GameStructure, shopBackgroundByType) == 5177912);
	static_assert(offsetof(mm7::GameStructure, shopWeaponKinds) == 5177992);
	static_assert(offsetof(mm7::GameStructure, shopArmorKinds) == 5178136);
	static_assert(offsetof(mm7::GameStructure, shopMagicLevels) == 5178416);
	static_assert(offsetof(mm7::GameStructure, shopAlchemistLevels) == 5178444);
	static_assert(offsetof(mm7::GameStructure, shopWeaponKindsSpecial) == 5178568);
	static_assert(offsetof(mm7::GameStructure, shopArmorKindsSpecial) == 5178712);
	static_assert(offsetof(mm7::GameStructure, shopMagicLevelsSpecial) == 5178992);
	static_assert(offsetof(mm7::GameStructure, shopAlchemistLevelsSpecial) == 5179020);
	static_assert(offsetof(mm7::GameStructure, guildJoinCost) == 5179244);
	static_assert(offsetof(mm7::GameStructure, trainingLevels) == 5179288);
	static_assert(offsetof(mm7::GameStructure, guildAwards) == 5179312);
	static_assert(offsetof(mm7::GameStructure, transportIndex) == 5180560);
	static_assert(offsetof(mm7::GameStructure, guildSpellLevels) == 5180848);
	static_assert(offsetof(mm7::GameStructure, turnBasedPhase) == 5211868);
	static_assert(offsetof(mm7::GameStructure, scanlineOffset) == 5265448);
	static_assert(offsetof(mm7::GameStructure, currentCharScreen) == 5270984);
	static_assert(offsetof(mm7::GameStructure, flashHistoryBook) == 5273544);
	static_assert(offsetof(mm7::GameStructure, flashAutonotesBook) == 5273545);
	static_assert(offsetof(mm7::GameStructure, flashQuestBook) == 5273546);
	static_assert(offsetof(mm7::GameStructure, statsNames) == 5274104);
	static_assert(offsetof(mm7::GameStructure, ctrlPressed) == 5274136);
	static_assert(offsetof(mm7::GameStructure, currentNPCDialog) == 5274172);
	static_assert(offsetof(mm7::GameStructure, currentPlayer) == 5274220);
	static_assert(offsetof(mm7::GameStructure, rightButtonPressed) == 5274224);
	static_assert(offsetof(mm7::GameStructure, paused2) == 5290556);
	static_assert(offsetof(mm7::GameStructure, timeDelta2) == 5290580);
	static_assert(offsetof(mm7::GameStructure, paused) == 5290596);
	static_assert(offsetof(mm7::GameStructure, timeDelta) == 5290620);
	static_assert(offsetof(mm7::GameStructure, actionsNext_size) == 5294184);
	static_assert(offsetof(mm7::GameStructure, actionsNext) == 5294188);
	static_assert(offsetof(mm7::GameStructure, actions_size) == 5294672);
	static_assert(offsetof(mm7::GameStructure, actions) == 5294676);
	static_assert(offsetof(mm7::GameStructure, progressBar) == 5729456);
	static_assert(offsetof(mm7::GameStructure, loadingScreen) == 5729516);
	static_assert(offsetof(mm7::GameStructure, needRedraw) == 5729964);
	static_assert(offsetof(mm7::GameStructure, houseOwnerPic) == 5836544);
	static_assert(offsetof(mm7::GameStructure, NPCCommand) == 5836556);
	static_assert(offsetof(mm7::GameStructure, dialogNPC) == 5836560);
	static_assert(offsetof(mm7::GameStructure, houseNPCs) == 5837400);
	static_assert(offsetof(mm7::GameStructure, houseNPCSlot) == 5837424);
	static_assert(offsetof(mm7::GameStructure, houseNPCSlotsCount) == 5837476);
	static_assert(offsetof(mm7::GameStructure, streetMessage) == 5965752);
	static_assert(offsetof(mm7::GameStructure, mapEvtLines_size) == 5967760);
	static_assert(offsetof(mm7::GameStructure, moveToMap) == 5989416);
	static_assert(offsetof(mm7::GameStructure, mapEvtLines) == 5989464);
	static_assert(offsetof(mm7::GameStructure, statusMessage) == 6042280);
	static_assert(offsetof(mm7::GameStructure, mouseOverStatusMessage) == 6042480);
	static_assert(offsetof(mm7::GameStructure, statusDisappearTime) == 6042680);
	static_assert(offsetof(mm7::GameStructure, houseExitMap) == 6042704);
	static_assert(offsetof(mm7::GameStructure, autonote_fnt) == 6042720);
	static_assert(offsetof(mm7::GameStructure, spell_fnt) == 6042724);
	static_assert(offsetof(mm7::GameStructure, arrus_fnt) == 6042728);
	static_assert(offsetof(mm7::GameStructure, lucida_fnt) == 6042732);
	static_assert(offsetof(mm7::GameStructure, book2_fnt) == 6042736);
	static_assert(offsetof(mm7::GameStructure, book_fnt) == 6042740);
	static_assert(offsetof(mm7::GameStructure, create_fnt) == 6042748);
	static_assert(offsetof(mm7::GameStructure, cchar_fnt) == 6042752);
	static_assert(offsetof(mm7::GameStructure, comic_fnt) == 6042756);
	static_assert(offsetof(mm7::GameStructure, smallnum_fnt) == 6042760);
	static_assert(offsetof(mm7::GameStructure, textBuffer) == 6052912);
	static_assert(offsetof(mm7::GameStructure, textBuffer2) == 6054912);
	static_assert(offsetof(mm7::GameStructure, TFTBin_size) == 6057016);
	static_assert(offsetof(mm7::GameStructure, TFTBin) == 6057020);
	static_assert(offsetof(mm7::GameStructure, SFTBin) == 6057024);
	static_assert(offsetof(mm7::GameStructure, classDescriptions) == 6063456);
	static_assert(offsetof(mm7::GameStructure, statsDescriptions) == 6063608);
	static_assert(offsetof(mm7::GameStructure, skillDesGM) == 6063760);
	static_assert(offsetof(mm7::GameStructure, skillDesMaster) == 6063912);
	static_assert(offsetof(mm7::GameStructure, skillDesExpert) == 6064064);
	static_assert(offsetof(mm7::GameStructure, skillDesNormal) == 6064216);
	static_assert(offsetof(mm7::GameStructure, skillDescriptions) == 6064368);
	static_assert(offsetof(mm7::GameStructure, historyTxt) == 6064608);
	static_assert(offsetof(mm7::GameStructure, hostileTxt) == 6064960);
	static_assert(offsetof(mm7::GameStructure, spellsTxt) == 6078128);
	static_assert(offsetof(mm7::GameStructure, stdItemsTxt) == 6143588);
	static_assert(offsetof(mm7::GameStructure, spcItemsTxt) == 6144068);
	static_assert(offsetof(mm7::GameStructure, potionTxt) == 6166468);
	static_assert(offsetof(mm7::GameStructure, potNotesTxt) == 6171468);
	static_assert(offsetof(mm7::GameStructure, globalTxt) == 6176768);
	static_assert(offsetof(mm7::GameStructure, overlayBin_size) == 6180808);
	static_assert(offsetof(mm7::GameStructure, overlayBin) == 6180812);
	static_assert(offsetof(mm7::GameStructure, chestBin_size) == 6287300);
	static_assert(offsetof(mm7::GameStructure, chestBin) == 6287304);
	static_assert(offsetof(mm7::GameStructure, monListBin_size) == 6287308);
	static_assert(offsetof(mm7::GameStructure, monListBin) == 6287312);
	static_assert(offsetof(mm7::GameStructure, objListBin_size) == 6817328);
	static_assert(offsetof(mm7::GameStructure, objListBin) == 6817332);
	static_assert(offsetof(mm7::GameStructure, decListBin_size) == 6925396);
	static_assert(offsetof(mm7::GameStructure, decListBin) == 6925400);
	static_assert(offsetof(mm7::GameStructure, keyCodes) == 6925452);
	static_assert(offsetof(mm7::GameStructure, keyTypes) == 6925572);
	static_assert(offsetof(mm7::GameStructure, saveGameLod) == 6948512);
	static_assert(offsetof(mm7::GameStructure, gamesLod) == 6949088);
	static_assert(offsetof(mm7::GameStructure, mainMenuCode) == 6949828);
	static_assert(offsetof(mm7::GameStructure, exitMapAction) == 6949832);
	static_assert(offsetof(mm7::GameStructure, tileBin_size) == 7069384);
	static_assert(offsetof(mm7::GameStructure, tileBin) == 7069388);
	static_assert(offsetof(mm7::GameStructure, exitLevelCode) == 7069392);
	static_assert(offsetof(mm7::GameStructure, outdoorViewMul) == 7069444);
	static_assert(offsetof(mm7::GameStructure, outdoorViewDiv) == 7069448);
	static_assert(offsetof(mm7::GameStructure, windowHandle) == 7070068);
	static_assert(offsetof(mm7::GameStructure, soundVolume) == 7070191);
	static_assert(offsetof(mm7::GameStructure, eventsLod) == 7071960);
	static_assert(offsetof(mm7::GameStructure, iconsLod) == 7144592);
	static_assert(offsetof(mm7::GameStructure, spritesLod) == 7217224);
	static_assert(offsetof(mm7::GameStructure, bitmapsLod) == 7277824);
	static_assert(offsetof(mm7::GameStructure, scrollTxt) == 7486392);
	static_assert(offsetof(mm7::GameStructure, awardsTxt) == 7486720);
	static_assert(offsetof(mm7::GameStructure, awardsSort) == 7486724);
	static_assert(offsetof(mm7::GameStructure, NPCNames) == 7563720);
	static_assert(offsetof(mm7::GameStructure, NPCProfTxt) == 7568040);
	static_assert(offsetof(mm7::GameStructure, streetNPC) == 7569220);
	static_assert(offsetof(mm7::GameStructure, NPCGreet) == 7583956);
	static_assert(offsetof(mm7::GameStructure, streetNPC_size) == 7585808);
	static_assert(offsetof(mm7::GameStructure, NPCNamesCount) == 7585824);
	static_assert(offsetof(mm7::GameStructure, NPCProfNames) == 7586064);
	static_assert(offsetof(mm7::GameStructure, merchantTxt) == 7586312);
	static_assert(offsetof(mm7::GameStructure, delayedFaceAnimation) == 10964824);
	static_assert(offsetof(mm7::GameStructure, IFTBin_size) == 10964836);
	static_assert(offsetof(mm7::GameStructure, IFTBin) == 10964840);
	static_assert(offsetof(mm7::GameStructure, PFTBin_size) == 10964844);
	static_assert(offsetof(mm7::GameStructure, PFTBin) == 10964848);
	static_assert(offsetof(mm7::GameStructure, time) == 11325028);
	static_assert(offsetof(mm7::GameStructure, guildNextRefill) == 11325548);
	static_assert(offsetof(mm7::GameStructure, year) == 11326788);
	static_assert(offsetof(mm7::GameStructure, month) == 11326792);
	static_assert(offsetof(mm7::GameStructure, weekOfMonth) == 11326796);
	static_assert(offsetof(mm7::GameStructure, dayOfMonth) == 11326800);
	static_assert(offsetof(mm7::GameStructure, hour) == 11326804);
	static_assert(offsetof(mm7::GameStructure, minute) == 11326808);
	static_assert(offsetof(mm7::GameStructure, second) == 11326812);
	static_assert(offsetof(mm7::GameStructure, turnBased) == 11327156);
	static_assert(offsetof(mm7::GameStructure, shopItems) == 11355572);
	static_assert(offsetof(mm7::GameStructure, shopSpecialItems) == 11378468);
	static_assert(offsetof(mm7::GameStructure, guildItems) == 11401364);
	static_assert(offsetof(mm7::GameStructure, armageddonTimeLeft) == 11415412);
	static_assert(offsetof(mm7::GameStructure, armageddonSkill) == 11415416);
	static_assert(offsetof(mm7::GameStructure, turnBasedDelays) == 11415420);
	static_assert(offsetof(mm7::GameStructure, skillNames) == 11415888);
	static_assert(offsetof(mm7::GameStructure, screen) == 14621288);
	static_assert(offsetof(mm7::GameStructure, objectByPixel) == 14883484);
	static_assert(offsetof(mm7::GameStructure, windowed) == 14883520);
	static_assert(offsetof(mm7::GameStructure, rendererD3D) == 14883568);
	static_assert(offsetof(mm7::GameStructure, redbookHandle) == 16224764);
	static_assert(offsetof(mm7::GameStructure, MSSHandle) == 16224768);
	static_assert(offsetof(mm7::GameStructure, soundsBin_size) == 16227292);
	static_assert(offsetof(mm7::GameStructure, soundsBin) == 16227296);
	static_assert(offsetof(mm7::GameStructure, guildItemIconPtr) == 16297960);
	static_assert(offsetof(mm7::GameStructure, housePicType) == 16298008);
	static_assert(offsetof(mm7::GameStructure, houseScreen) == 16298012);
	static_assert(offsetof(mm7::GameStructure, houseAllowAction) == 16298024);
	static_assert(offsetof(mm7::GameStructure, houseActionInfo) == 16298028);
	static_assert(offsetof(mm7::GameStructure, houseTeachMastery) == 16298032);
	static_assert(offsetof(mm7::GameStructure, houseCost) == 16298036);
	static_assert(offsetof(mm7::GameStructure, houseItemsCount) == 16298080);
	static_assert(offsetof(mm7::GameStructure, NPCMessage) == 16298088);
	static_assert(offsetof(mm7::GameStructure, smackVideo) == 16300464);
	static_assert(offsetof(mm7::GameStructure, isMovieLooped) == 16300524);
	static_assert(offsetof(mm7::GameStructure, binkVideo) == 16300552);
	static_assert(offsetof(mm7::GameStructure, movieKind) == 16300580);
	static_assert(offsetof(mm7::GameStructure, patchOptions) == 53531516);
	static_assert(offsetof(mm7::GameStructure, customLods) == 55176036);
	static_assert(offsetof(mm7::GameStructure, titleTrackOffset) == 61870536);
	static_assert(offsetof(mm7::GameStructure, monsterKinds) == 61878376);
	static_assert(offsetof(mm7::GameStructure, monsterKinds_size) == 61878380);
	static_assert(offsetof(mm7::GameStructure, missileSetup) == 61878568);
	static_assert(offsetof(mm7::GameStructure, missileSetup_size) == 61878572);

}
#pragma pack(pop)