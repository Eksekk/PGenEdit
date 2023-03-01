#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct SpellInfo // size: 0xE
	{
		union
		{
			std::array<int16_t, 3> spellPoints; // MMExt: 1..3, here 0..2
			struct
			{
				int16_t spellPointsNormal;
				int16_t spellPointsExpert;
				int16_t spellPointsMaster;
			};
		};
		union
		{
			std::array<int16_t, 3> delay; // MMExt: 1..3, here 0..2
			struct
			{
				int16_t delayNormal;
				int16_t delayExpert;
				int16_t delayMaster;
			};
		};
		uint16_t bits;
	};
	static_assert(sizeof(mm6::SpellInfo) == 0xE, "Invalid \"mm6::SpellInfo\" structure size");
	static_assert(offsetof(mm6::SpellInfo, spellPointsExpert) == 2);
	static_assert(offsetof(mm6::SpellInfo, spellPointsMaster) == 4);
	static_assert(offsetof(mm6::SpellInfo, delay) == 6);
	static_assert(offsetof(mm6::SpellInfo, delayNormal) == 6);
	static_assert(offsetof(mm6::SpellInfo, delayExpert) == 8);
	static_assert(offsetof(mm6::SpellInfo, delayMaster) == 10);
	static_assert(offsetof(mm6::SpellInfo, bits) == 12);



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
	static_assert(sizeof(mm6::HouseMovie) == 0x10, "Invalid \"mm6::HouseMovie\" structure size");
	static_assert(offsetof(mm6::HouseMovie, background) == 4);
	static_assert(offsetof(mm6::HouseMovie, NPCPic) == 8);
	static_assert(offsetof(mm6::HouseMovie, houseType) == 12);
	static_assert(offsetof(mm6::HouseMovie, sounds) == 13);



	struct Weather // size: 0x61A990
	{
		SKIP(6400360);
		int32_t shade;
		uint32_t snow; // 4-byte boolean
		SKIP(8);
		// uint8_t* fog; // real size is 0 | Unknown type
		SKIP(16);
		std::array<uint8_t, 4> fogRange1; // Unknown type
		std::array<uint8_t, 4> fogRange2; // Unknown type
	};
	static_assert(sizeof(mm6::Weather) == 0x61A990, "Invalid \"mm6::Weather\" structure size");
	static_assert(offsetof(mm6::Weather, shade) == 6400360);
	static_assert(offsetof(mm6::Weather, snow) == 6400364);
	static_assert(offsetof(mm6::Weather, fogRange1) == 6400392);
	static_assert(offsetof(mm6::Weather, fogRange2) == 6400396);



	struct GeneralStoreItemKind // size: 0xE
	{
		int16_t level;
		std::array<int16_t, 6> items; // MMExt: 1..6, here 0..5
	};
	static_assert(sizeof(mm6::GeneralStoreItemKind) == 0xE, "Invalid \"mm6::GeneralStoreItemKind\" structure size");
	static_assert(offsetof(mm6::GeneralStoreItemKind, items) == 2);



	struct ShopItemKind // size: 0xA
	{
		int16_t level;
		std::array<int16_t, 4> types; // MMExt: 1..4, here 0..3
	};
	static_assert(sizeof(mm6::ShopItemKind) == 0xA, "Invalid \"mm6::ShopItemKind\" structure size");
	static_assert(offsetof(mm6::ShopItemKind, types) == 2);



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
	static_assert(sizeof(mm6::MoveToMap) == 0x1C, "Invalid \"mm6::MoveToMap\" structure size");
	static_assert(offsetof(mm6::MoveToMap, y) == 4);
	static_assert(offsetof(mm6::MoveToMap, z) == 8);
	static_assert(offsetof(mm6::MoveToMap, direction) == 12);
	static_assert(offsetof(mm6::MoveToMap, lookAngle) == 16);
	static_assert(offsetof(mm6::MoveToMap, speedZ) == 20);
	static_assert(offsetof(mm6::MoveToMap, defined) == 24);



	struct ProgressBar // size: 0x10
	{
		SKIP(10);
		uint8_t max;
		uint8_t current;
		int32_t kind;
	};
	static_assert(sizeof(mm6::ProgressBar) == 0x10, "Invalid \"mm6::ProgressBar\" structure size");
	static_assert(offsetof(mm6::ProgressBar, max) == 10);
	static_assert(offsetof(mm6::ProgressBar, current) == 11);
	static_assert(offsetof(mm6::ProgressBar, kind) == 12);



	struct FogChances // size: 0x3
	{
		uint8_t thick;
		uint8_t medium;
		uint8_t light;
	};
	static_assert(sizeof(mm6::FogChances) == 0x3, "Invalid \"mm6::FogChances\" structure size");
	static_assert(offsetof(mm6::FogChances, medium) == 1);
	static_assert(offsetof(mm6::FogChances, light) == 2);



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
	static_assert(sizeof(mm6::PatchOptions) == 0x178, "Invalid \"mm6::PatchOptions\" structure size");
	static_assert(offsetof(mm6::PatchOptions, maxMLookAngle) == 4);
	static_assert(offsetof(mm6::PatchOptions, mouseLook) == 8);
	static_assert(offsetof(mm6::PatchOptions, mouseLookUseAltMode) == 12);
	static_assert(offsetof(mm6::PatchOptions, capsLockToggleMouseLook) == 16);
	static_assert(offsetof(mm6::PatchOptions, mouseFly) == 20);
	static_assert(offsetof(mm6::PatchOptions, mouseWheelFly) == 24);
	static_assert(offsetof(mm6::PatchOptions, mouseLookTempKey) == 28);
	static_assert(offsetof(mm6::PatchOptions, mouseLookChangeKey) == 32);
	static_assert(offsetof(mm6::PatchOptions, inventoryKey) == 36);
	static_assert(offsetof(mm6::PatchOptions, charScreenKey) == 40);
	static_assert(offsetof(mm6::PatchOptions, doubleSpeedKey) == 44);
	static_assert(offsetof(mm6::PatchOptions, quickLoadKey) == 48);
	static_assert(offsetof(mm6::PatchOptions, autorunKey) == 52);
	static_assert(offsetof(mm6::PatchOptions, HDWTRCount) == 56);
	static_assert(offsetof(mm6::PatchOptions, HDWTRDelay) == 60);
	static_assert(offsetof(mm6::PatchOptions, horsemanSpeakTime) == 64);
	static_assert(offsetof(mm6::PatchOptions, boatmanSpeakTime) == 68);
	static_assert(offsetof(mm6::PatchOptions, paletteSMul) == 72);
	static_assert(offsetof(mm6::PatchOptions, paletteVMul) == 76);
	static_assert(offsetof(mm6::PatchOptions, noBitmapsHwl) == 80);
	static_assert(offsetof(mm6::PatchOptions, playMP3) == 84);
	static_assert(offsetof(mm6::PatchOptions, musicLoopsCount) == 88);
	static_assert(offsetof(mm6::PatchOptions, hardenArtifacts) == 92);
	static_assert(offsetof(mm6::PatchOptions, progressiveDaggerTrippleDamage) == 96);
	static_assert(offsetof(mm6::PatchOptions, fixChests) == 100);
	static_assert(offsetof(mm6::PatchOptions, dataFiles) == 104);
	static_assert(offsetof(mm6::PatchOptions, fixDualWeaponsRecovery) == 108);
	static_assert(offsetof(mm6::PatchOptions, increaseRecoveryRateStrength) == 112);
	static_assert(offsetof(mm6::PatchOptions, blasterRecovery) == 116);
	static_assert(offsetof(mm6::PatchOptions, fixSkyBitmap) == 120);
	static_assert(offsetof(mm6::PatchOptions, noCD) == 124);
	static_assert(offsetof(mm6::PatchOptions, fixChestsByReorder) == 128);
	static_assert(offsetof(mm6::PatchOptions, lastLoadedFileSize) == 132);
	static_assert(offsetof(mm6::PatchOptions, fixTimers) == 136);
	static_assert(offsetof(mm6::PatchOptions, fixMovement) == 140);
	static_assert(offsetof(mm6::PatchOptions, monsterJumpDownLimit) == 144);
	static_assert(offsetof(mm6::PatchOptions, fixHeroismPedestal) == 148);
	static_assert(offsetof(mm6::PatchOptions, skipUnsellableItemCheck) == 152);
	static_assert(offsetof(mm6::PatchOptions, fixGMStaff) == 156);
	static_assert(offsetof(mm6::PatchOptions, fixObelisks) == 160);
	static_assert(offsetof(mm6::PatchOptions, borderlessWindowed) == 164);
	static_assert(offsetof(mm6::PatchOptions, compatibleMovieRender) == 168);
	static_assert(offsetof(mm6::PatchOptions, smoothMovieScaling) == 172);
	static_assert(offsetof(mm6::PatchOptions, supportTrueColor) == 176);
	static_assert(offsetof(mm6::PatchOptions, renderRectLeft) == 180);
	static_assert(offsetof(mm6::PatchOptions, renderRectTop) == 184);
	static_assert(offsetof(mm6::PatchOptions, renderRectRight) == 188);
	static_assert(offsetof(mm6::PatchOptions, renderRectBottom) == 192);
	static_assert(offsetof(mm6::PatchOptions, fixUnimplementedSpells) == 196);
	static_assert(offsetof(mm6::PatchOptions, indoorMinimapZoomMul) == 200);
	static_assert(offsetof(mm6::PatchOptions, indoorMinimapZoomPower) == 204);
	static_assert(offsetof(mm6::PatchOptions, fixMonsterSummon) == 208);
	static_assert(offsetof(mm6::PatchOptions, fixInterfaceBugs) == 212);
	static_assert(offsetof(mm6::PatchOptions, UILayout) == 216);
	static_assert(offsetof(mm6::PatchOptions, paperDollInChests) == 220);
	static_assert(offsetof(mm6::PatchOptions, higherCloseRingsButton) == 224);
	static_assert(offsetof(mm6::PatchOptions, renderBottomPixel) == 228);
	static_assert(offsetof(mm6::PatchOptions, trueColorTextures) == 232);
	static_assert(offsetof(mm6::PatchOptions, resetPalettes) == 236);
	static_assert(offsetof(mm6::PatchOptions, fixSFT) == 240);
	static_assert(offsetof(mm6::PatchOptions, axeGMFullProbabilityAt) == 244);
	static_assert(offsetof(mm6::PatchOptions, mouseDX) == 248);
	static_assert(offsetof(mm6::PatchOptions, mouseDY) == 256);
	static_assert(offsetof(mm6::PatchOptions, trueColorSprites) == 264);
	static_assert(offsetof(mm6::PatchOptions, fixMonstersBlockingShots) == 268);
	static_assert(offsetof(mm6::PatchOptions, fixParalyze) == 272);
	static_assert(offsetof(mm6::PatchOptions, enableAttackSpell) == 276);
	static_assert(offsetof(mm6::PatchOptions, shooterMode) == 280);
	static_assert(offsetof(mm6::PatchOptions, maxMLookUpAngle) == 284);
	static_assert(offsetof(mm6::PatchOptions, fixIceBoltBlast) == 288);
	static_assert(offsetof(mm6::PatchOptions, monSpritesSizeMul) == 292);
	static_assert(offsetof(mm6::PatchOptions, fixMonsterAttackTypes) == 296);
	static_assert(offsetof(mm6::PatchOptions, fixMonsterSpells) == 300);
	static_assert(offsetof(mm6::PatchOptions, fixSouldrinker) == 304);
	static_assert(offsetof(mm6::PatchOptions, mouseLookPermKey) == 308);
	static_assert(offsetof(mm6::PatchOptions, lastSoundSample) == 312);
	static_assert(offsetof(mm6::PatchOptions, waterWalkDamage) == 316);
	static_assert(offsetof(mm6::PatchOptions, fixUnmarkedArtifacts) == 320);
	static_assert(offsetof(mm6::PatchOptions, fixClubsDelay) == 324);
	static_assert(offsetof(mm6::PatchOptions, fixDarkTrainers) == 328);
	static_assert(offsetof(mm6::PatchOptions, fixLightBolt) == 332);
	static_assert(offsetof(mm6::PatchOptions, armageddonElement) == 336);
	static_assert(offsetof(mm6::PatchOptions, fixKelebrim) == 340);
	static_assert(offsetof(mm6::PatchOptions, fixBarrels) == 344);
	static_assert(offsetof(mm6::PatchOptions, climbBetter) == 348);
	static_assert(offsetof(mm6::PatchOptions, fixWaterWalkManaDrain) == 352);
	static_assert(offsetof(mm6::PatchOptions, keepEmptyWands) == 356);
	static_assert(offsetof(mm6::PatchOptions, dontSkipSimpleMessage) == 360);
	static_assert(offsetof(mm6::PatchOptions, fixItemDuplicates) == 364);
	static_assert(offsetof(mm6::PatchOptions, fixClubsGeneration) == 368);
	static_assert(offsetof(mm6::PatchOptions, fixAcidBurst) == 372);



	struct EventLine // size: 0xC
	{
		int32_t event;
		int32_t line;
		int32_t offset;
	};
	static_assert(sizeof(mm6::EventLine) == 0xC, "Invalid \"mm6::EventLine\" structure size");
	static_assert(offsetof(mm6::EventLine, line) == 4);
	static_assert(offsetof(mm6::EventLine, offset) == 8);



	struct TravelInfo // size: 0x20
	{
		union
		{
			std::array<uint8_t, 1> map; // Unknown type
			uint8_t mapIndex;
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
	static_assert(sizeof(mm6::TravelInfo) == 0x20, "Invalid \"mm6::TravelInfo\" structure size");
	static_assert(offsetof(mm6::TravelInfo, daysAvailable) == 1);
	static_assert(offsetof(mm6::TravelInfo, monday) == 1);
	static_assert(offsetof(mm6::TravelInfo, tuesday) == 2);
	static_assert(offsetof(mm6::TravelInfo, wednesday) == 3);
	static_assert(offsetof(mm6::TravelInfo, thursday) == 4);
	static_assert(offsetof(mm6::TravelInfo, friday) == 5);
	static_assert(offsetof(mm6::TravelInfo, saturday) == 6);
	static_assert(offsetof(mm6::TravelInfo, sunday) == 7);
	static_assert(offsetof(mm6::TravelInfo, daysCount) == 8);
	static_assert(offsetof(mm6::TravelInfo, pos) == 12);
	static_assert(offsetof(mm6::TravelInfo, x) == 12);
	static_assert(offsetof(mm6::TravelInfo, y) == 16);
	static_assert(offsetof(mm6::TravelInfo, z) == 20);
	static_assert(offsetof(mm6::TravelInfo, direction) == 24);
	static_assert(offsetof(mm6::TravelInfo, QBit) == 28);



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
			std::array<uint8_t, 2> map; // Unknown type
			int16_t mapStatsIndex;
		};
		SKIP(2);
		// uint8_t* mapIndex; // real size is 0 | Unknown type
	};
	static_assert(sizeof(mm6::TownPortalTownInfo) == 0x14, "Invalid \"mm6::TownPortalTownInfo\" structure size");
	static_assert(offsetof(mm6::TownPortalTownInfo, y) == 4);
	static_assert(offsetof(mm6::TownPortalTownInfo, z) == 8);
	static_assert(offsetof(mm6::TownPortalTownInfo, direction) == 12);
	static_assert(offsetof(mm6::TownPortalTownInfo, lookAngle) == 14);
	static_assert(offsetof(mm6::TownPortalTownInfo, map) == 16);
	static_assert(offsetof(mm6::TownPortalTownInfo, mapStatsIndex) == 16);



	struct MissileSetup // size: 0x1
	{
		bool alwaysShowSprite : 1;
		bool hideSpecialDisplay : 1;
		bool autoCollision : 1;
	};
	static_assert(sizeof(mm6::MissileSetup) == 0x1, "Invalid \"mm6::MissileSetup\" structure size");



	struct ActionItem // size: 0xC
	{
		int32_t action;
		int32_t param;
		int32_t param2;
	};
	static_assert(sizeof(mm6::ActionItem) == 0xC, "Invalid \"mm6::ActionItem\" structure size");
	static_assert(offsetof(mm6::ActionItem, param) == 4);
	static_assert(offsetof(mm6::ActionItem, param2) == 8);



	struct GameMouse // size: 0x268728
	{
		static inline mm6::ObjectRef* const target = 0;

		SKIP(16);
		int32_t x;
		int32_t y;
		SKIP(2524916);
		mm6::Item item;
	};
	static_assert(sizeof(mm6::GameMouse) == 0x268728, "Invalid \"mm6::GameMouse\" structure size");
	static_assert(offsetof(mm6::GameMouse, x) == 16);
	static_assert(offsetof(mm6::GameMouse, y) == 20);
	static_assert(offsetof(mm6::GameMouse, item) == 2524940);
}
namespace mm7
{
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



	struct ActionItem // size: 0xC
	{
		int32_t action;
		int32_t param;
		int32_t param2;
	};
	static_assert(sizeof(mm7::ActionItem) == 0xC, "Invalid \"mm7::ActionItem\" structure size");
	static_assert(offsetof(mm7::ActionItem, param) == 4);
	static_assert(offsetof(mm7::ActionItem, param2) == 8);



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



	struct TravelInfo // size: 0x20
	{
		union
		{
			std::array<uint8_t, 1> map; // Unknown type
			uint8_t mapIndex;
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



	struct MissileSetup // size: 0x1
	{
		bool alwaysShowSprite : 1;
		bool hideSpecialDisplay : 1;
		bool autoCollision : 1;
	};
	static_assert(sizeof(mm7::MissileSetup) == 0x1, "Invalid \"mm7::MissileSetup\" structure size");



	struct EventLine // size: 0xC
	{
		int32_t event;
		int32_t line;
		int32_t offset;
	};
	static_assert(sizeof(mm7::EventLine) == 0xC, "Invalid \"mm7::EventLine\" structure size");
	static_assert(offsetof(mm7::EventLine, line) == 4);
	static_assert(offsetof(mm7::EventLine, offset) == 8);



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



	struct ShopItemKind // size: 0xA
	{
		int16_t level;
		std::array<int16_t, 4> types; // MMExt: 1..4, here 0..3
	};
	static_assert(sizeof(mm7::ShopItemKind) == 0xA, "Invalid \"mm7::ShopItemKind\" structure size");
	static_assert(offsetof(mm7::ShopItemKind, types) == 2);



	struct MouseStruct // size: 0x110
	{
		static inline mm7::ObjectRef* const target = 0;

		SKIP(264);
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
}
namespace mm8
{
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
	static_assert(sizeof(mm8::MoveToMap) == 0x1C, "Invalid \"mm8::MoveToMap\" structure size");
	static_assert(offsetof(mm8::MoveToMap, y) == 4);
	static_assert(offsetof(mm8::MoveToMap, z) == 8);
	static_assert(offsetof(mm8::MoveToMap, direction) == 12);
	static_assert(offsetof(mm8::MoveToMap, lookAngle) == 16);
	static_assert(offsetof(mm8::MoveToMap, speedZ) == 20);
	static_assert(offsetof(mm8::MoveToMap, defined) == 24);



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
	static_assert(sizeof(mm8::PatchOptions) == 0x178, "Invalid \"mm8::PatchOptions\" structure size");
	static_assert(offsetof(mm8::PatchOptions, maxMLookAngle) == 4);
	static_assert(offsetof(mm8::PatchOptions, mouseLook) == 8);
	static_assert(offsetof(mm8::PatchOptions, mouseLookUseAltMode) == 12);
	static_assert(offsetof(mm8::PatchOptions, capsLockToggleMouseLook) == 16);
	static_assert(offsetof(mm8::PatchOptions, mouseFly) == 20);
	static_assert(offsetof(mm8::PatchOptions, mouseWheelFly) == 24);
	static_assert(offsetof(mm8::PatchOptions, mouseLookTempKey) == 28);
	static_assert(offsetof(mm8::PatchOptions, mouseLookChangeKey) == 32);
	static_assert(offsetof(mm8::PatchOptions, inventoryKey) == 36);
	static_assert(offsetof(mm8::PatchOptions, charScreenKey) == 40);
	static_assert(offsetof(mm8::PatchOptions, doubleSpeedKey) == 44);
	static_assert(offsetof(mm8::PatchOptions, quickLoadKey) == 48);
	static_assert(offsetof(mm8::PatchOptions, autorunKey) == 52);
	static_assert(offsetof(mm8::PatchOptions, HDWTRCount) == 56);
	static_assert(offsetof(mm8::PatchOptions, HDWTRDelay) == 60);
	static_assert(offsetof(mm8::PatchOptions, horsemanSpeakTime) == 64);
	static_assert(offsetof(mm8::PatchOptions, boatmanSpeakTime) == 68);
	static_assert(offsetof(mm8::PatchOptions, paletteSMul) == 72);
	static_assert(offsetof(mm8::PatchOptions, paletteVMul) == 76);
	static_assert(offsetof(mm8::PatchOptions, noBitmapsHwl) == 80);
	static_assert(offsetof(mm8::PatchOptions, playMP3) == 84);
	static_assert(offsetof(mm8::PatchOptions, musicLoopsCount) == 88);
	static_assert(offsetof(mm8::PatchOptions, hardenArtifacts) == 92);
	static_assert(offsetof(mm8::PatchOptions, progressiveDaggerTrippleDamage) == 96);
	static_assert(offsetof(mm8::PatchOptions, fixChests) == 100);
	static_assert(offsetof(mm8::PatchOptions, dataFiles) == 104);
	static_assert(offsetof(mm8::PatchOptions, fixDualWeaponsRecovery) == 108);
	static_assert(offsetof(mm8::PatchOptions, increaseRecoveryRateStrength) == 112);
	static_assert(offsetof(mm8::PatchOptions, blasterRecovery) == 116);
	static_assert(offsetof(mm8::PatchOptions, fixSkyBitmap) == 120);
	static_assert(offsetof(mm8::PatchOptions, noCD) == 124);
	static_assert(offsetof(mm8::PatchOptions, fixChestsByReorder) == 128);
	static_assert(offsetof(mm8::PatchOptions, lastLoadedFileSize) == 132);
	static_assert(offsetof(mm8::PatchOptions, fixTimers) == 136);
	static_assert(offsetof(mm8::PatchOptions, fixMovement) == 140);
	static_assert(offsetof(mm8::PatchOptions, monsterJumpDownLimit) == 144);
	static_assert(offsetof(mm8::PatchOptions, fixHeroismPedestal) == 148);
	static_assert(offsetof(mm8::PatchOptions, skipUnsellableItemCheck) == 152);
	static_assert(offsetof(mm8::PatchOptions, fixGMStaff) == 156);
	static_assert(offsetof(mm8::PatchOptions, fixObelisks) == 160);
	static_assert(offsetof(mm8::PatchOptions, borderlessWindowed) == 164);
	static_assert(offsetof(mm8::PatchOptions, compatibleMovieRender) == 168);
	static_assert(offsetof(mm8::PatchOptions, smoothMovieScaling) == 172);
	static_assert(offsetof(mm8::PatchOptions, supportTrueColor) == 176);
	static_assert(offsetof(mm8::PatchOptions, renderRectLeft) == 180);
	static_assert(offsetof(mm8::PatchOptions, renderRectTop) == 184);
	static_assert(offsetof(mm8::PatchOptions, renderRectRight) == 188);
	static_assert(offsetof(mm8::PatchOptions, renderRectBottom) == 192);
	static_assert(offsetof(mm8::PatchOptions, fixUnimplementedSpells) == 196);
	static_assert(offsetof(mm8::PatchOptions, indoorMinimapZoomMul) == 200);
	static_assert(offsetof(mm8::PatchOptions, indoorMinimapZoomPower) == 204);
	static_assert(offsetof(mm8::PatchOptions, fixMonsterSummon) == 208);
	static_assert(offsetof(mm8::PatchOptions, fixInterfaceBugs) == 212);
	static_assert(offsetof(mm8::PatchOptions, UILayout) == 216);
	static_assert(offsetof(mm8::PatchOptions, paperDollInChests) == 220);
	static_assert(offsetof(mm8::PatchOptions, higherCloseRingsButton) == 224);
	static_assert(offsetof(mm8::PatchOptions, renderBottomPixel) == 228);
	static_assert(offsetof(mm8::PatchOptions, trueColorTextures) == 232);
	static_assert(offsetof(mm8::PatchOptions, resetPalettes) == 236);
	static_assert(offsetof(mm8::PatchOptions, fixSFT) == 240);
	static_assert(offsetof(mm8::PatchOptions, axeGMFullProbabilityAt) == 244);
	static_assert(offsetof(mm8::PatchOptions, mouseDX) == 248);
	static_assert(offsetof(mm8::PatchOptions, mouseDY) == 256);
	static_assert(offsetof(mm8::PatchOptions, trueColorSprites) == 264);
	static_assert(offsetof(mm8::PatchOptions, fixMonstersBlockingShots) == 268);
	static_assert(offsetof(mm8::PatchOptions, fixParalyze) == 272);
	static_assert(offsetof(mm8::PatchOptions, enableAttackSpell) == 276);
	static_assert(offsetof(mm8::PatchOptions, shooterMode) == 280);
	static_assert(offsetof(mm8::PatchOptions, maxMLookUpAngle) == 284);
	static_assert(offsetof(mm8::PatchOptions, fixIceBoltBlast) == 288);
	static_assert(offsetof(mm8::PatchOptions, monSpritesSizeMul) == 292);
	static_assert(offsetof(mm8::PatchOptions, fixMonsterAttackTypes) == 296);
	static_assert(offsetof(mm8::PatchOptions, fixMonsterSpells) == 300);
	static_assert(offsetof(mm8::PatchOptions, fixSouldrinker) == 304);
	static_assert(offsetof(mm8::PatchOptions, mouseLookPermKey) == 308);
	static_assert(offsetof(mm8::PatchOptions, lastSoundSample) == 312);
	static_assert(offsetof(mm8::PatchOptions, waterWalkDamage) == 316);
	static_assert(offsetof(mm8::PatchOptions, fixUnmarkedArtifacts) == 320);
	static_assert(offsetof(mm8::PatchOptions, fixClubsDelay) == 324);
	static_assert(offsetof(mm8::PatchOptions, fixDarkTrainers) == 328);
	static_assert(offsetof(mm8::PatchOptions, fixLightBolt) == 332);
	static_assert(offsetof(mm8::PatchOptions, armageddonElement) == 336);
	static_assert(offsetof(mm8::PatchOptions, fixKelebrim) == 340);
	static_assert(offsetof(mm8::PatchOptions, fixBarrels) == 344);
	static_assert(offsetof(mm8::PatchOptions, climbBetter) == 348);
	static_assert(offsetof(mm8::PatchOptions, fixWaterWalkManaDrain) == 352);
	static_assert(offsetof(mm8::PatchOptions, keepEmptyWands) == 356);
	static_assert(offsetof(mm8::PatchOptions, dontSkipSimpleMessage) == 360);
	static_assert(offsetof(mm8::PatchOptions, fixItemDuplicates) == 364);
	static_assert(offsetof(mm8::PatchOptions, fixClubsGeneration) == 368);
	static_assert(offsetof(mm8::PatchOptions, fixAcidBurst) == 372);



	struct Weather // size: 0x6F2FBC
	{
		SKIP(7286676);
		uint32_t rain; // 4-byte boolean
		int32_t shade;
		SKIP(8);
		// uint8_t* fog; // real size is 0 | Unknown type
		SKIP(16);
		std::array<uint8_t, 4> fogRange1; // Unknown type
		std::array<uint8_t, 4> fogRange2; // Unknown type
	};
	static_assert(sizeof(mm8::Weather) == 0x6F2FBC, "Invalid \"mm8::Weather\" structure size");
	static_assert(offsetof(mm8::Weather, rain) == 7286676);
	static_assert(offsetof(mm8::Weather, shade) == 7286680);
	static_assert(offsetof(mm8::Weather, fogRange1) == 7286708);
	static_assert(offsetof(mm8::Weather, fogRange2) == 7286712);



	struct MissileSetup // size: 0x1
	{
		bool alwaysShowSprite : 1;
		bool hideSpecialDisplay : 1;
		bool autoCollision : 1;
	};
	static_assert(sizeof(mm8::MissileSetup) == 0x1, "Invalid \"mm8::MissileSetup\" structure size");



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
	static_assert(sizeof(mm8::TravelInfo) == 0x20, "Invalid \"mm8::TravelInfo\" structure size");
	static_assert(offsetof(mm8::TravelInfo, daysAvailable) == 1);
	static_assert(offsetof(mm8::TravelInfo, monday) == 1);
	static_assert(offsetof(mm8::TravelInfo, tuesday) == 2);
	static_assert(offsetof(mm8::TravelInfo, wednesday) == 3);
	static_assert(offsetof(mm8::TravelInfo, thursday) == 4);
	static_assert(offsetof(mm8::TravelInfo, friday) == 5);
	static_assert(offsetof(mm8::TravelInfo, saturday) == 6);
	static_assert(offsetof(mm8::TravelInfo, sunday) == 7);
	static_assert(offsetof(mm8::TravelInfo, daysCount) == 8);
	static_assert(offsetof(mm8::TravelInfo, pos) == 12);
	static_assert(offsetof(mm8::TravelInfo, x) == 12);
	static_assert(offsetof(mm8::TravelInfo, y) == 16);
	static_assert(offsetof(mm8::TravelInfo, z) == 20);
	static_assert(offsetof(mm8::TravelInfo, direction) == 24);
	static_assert(offsetof(mm8::TravelInfo, QBit) == 28);



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
	static_assert(sizeof(mm8::TownPortalTownInfo) == 0x14, "Invalid \"mm8::TownPortalTownInfo\" structure size");
	static_assert(offsetof(mm8::TownPortalTownInfo, y) == 4);
	static_assert(offsetof(mm8::TownPortalTownInfo, z) == 8);
	static_assert(offsetof(mm8::TownPortalTownInfo, direction) == 12);
	static_assert(offsetof(mm8::TownPortalTownInfo, lookAngle) == 14);
	static_assert(offsetof(mm8::TownPortalTownInfo, mapStatsIndex) == 16);
	static_assert(offsetof(mm8::TownPortalTownInfo, map) == 16);



	struct ActionItem // size: 0xC
	{
		int32_t action;
		int32_t param;
		int32_t param2;
	};
	static_assert(sizeof(mm8::ActionItem) == 0xC, "Invalid \"mm8::ActionItem\" structure size");
	static_assert(offsetof(mm8::ActionItem, param) == 4);
	static_assert(offsetof(mm8::ActionItem, param2) == 8);



	struct MouseStruct // size: 0x110
	{
		static inline mm8::ObjectRef* const target = 0;

		SKIP(264);
		int32_t x;
		int32_t y;
	};
	static_assert(sizeof(mm8::MouseStruct) == 0x110, "Invalid \"mm8::MouseStruct\" structure size");
	static_assert(offsetof(mm8::MouseStruct, x) == 264);
	static_assert(offsetof(mm8::MouseStruct, y) == 268);



	struct EventLine // size: 0xC
	{
		int32_t event;
		int32_t line;
		int32_t offset;
	};
	static_assert(sizeof(mm8::EventLine) == 0xC, "Invalid \"mm8::EventLine\" structure size");
	static_assert(offsetof(mm8::EventLine, line) == 4);
	static_assert(offsetof(mm8::EventLine, offset) == 8);



	struct FogChances // size: 0x4
	{
		uint8_t thick;
		uint8_t medium;
		uint8_t light;
		SKIP(1);
	};
	static_assert(sizeof(mm8::FogChances) == 0x4, "Invalid \"mm8::FogChances\" structure size");
	static_assert(offsetof(mm8::FogChances, medium) == 1);
	static_assert(offsetof(mm8::FogChances, light) == 2);



	struct ShopItemKind // size: 0xA
	{
		int16_t level;
		std::array<int16_t, 4> types; // MMExt: 1..4, here 0..3
	};
	static_assert(sizeof(mm8::ShopItemKind) == 0xA, "Invalid \"mm8::ShopItemKind\" structure size");
	static_assert(offsetof(mm8::ShopItemKind, types) == 2);



	struct ProgressBar // size: 0x10
	{
		SKIP(10);
		uint8_t max;
		uint8_t current;
		int32_t kind;
	};
	static_assert(sizeof(mm8::ProgressBar) == 0x10, "Invalid \"mm8::ProgressBar\" structure size");
	static_assert(offsetof(mm8::ProgressBar, max) == 10);
	static_assert(offsetof(mm8::ProgressBar, current) == 11);
	static_assert(offsetof(mm8::ProgressBar, kind) == 12);



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
	static_assert(sizeof(mm8::SpellInfo) == 0x14, "Invalid \"mm8::SpellInfo\" structure size");
	static_assert(offsetof(mm8::SpellInfo, spellPointsExpert) == 2);
	static_assert(offsetof(mm8::SpellInfo, spellPointsMaster) == 4);
	static_assert(offsetof(mm8::SpellInfo, spellPointsGM) == 6);
	static_assert(offsetof(mm8::SpellInfo, delay) == 8);
	static_assert(offsetof(mm8::SpellInfo, delayNormal) == 8);
	static_assert(offsetof(mm8::SpellInfo, delayExpert) == 10);
	static_assert(offsetof(mm8::SpellInfo, delayMaster) == 12);
	static_assert(offsetof(mm8::SpellInfo, delayGM) == 14);
	static_assert(offsetof(mm8::SpellInfo, damageAdd) == 16);
	static_assert(offsetof(mm8::SpellInfo, damageDiceSides) == 17);
	static_assert(offsetof(mm8::SpellInfo, bits) == 18);



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
	static_assert(sizeof(mm8::HouseMovie) == 0x10, "Invalid \"mm8::HouseMovie\" structure size");
	static_assert(offsetof(mm8::HouseMovie, background) == 4);
	static_assert(offsetof(mm8::HouseMovie, NPCPic) == 8);
	static_assert(offsetof(mm8::HouseMovie, houseType) == 12);
	static_assert(offsetof(mm8::HouseMovie, sounds) == 13);



	struct GameMouse // size: 0xB7CA88
	{
		SKIP(7722864);
		mm8::MouseStruct* mouseStruct;
		SKIP(4322032);
		mm8::Item item;
	};
	static_assert(sizeof(mm8::GameMouse) == 0xB7CA88, "Invalid \"mm8::GameMouse\" structure size");
	static_assert(offsetof(mm8::GameMouse, mouseStruct) == 7722864);
	static_assert(offsetof(mm8::GameMouse, item) == 12044900);
}

#pragma pack(pop)