#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct Weather // size: 0x61A990
	{
		SKIP(6400360);
		int32_t shade; // 0x61A968 (6400360 decimal) | MMExt info: 0 = sunny, 1 = dark, 2 = misty
		uint32_t snow; // 4-byte boolean | 0x61A96C (6400364 decimal)
		SKIP(8);
		// uint8_t* fog; // real size is 0 | Unknown type | 0x61A978 (6400376 decimal)
		SKIP(16);
		std::array<uint8_t, 4> fogRange1; // Unknown type | 0x61A988 (6400392 decimal)
		std::array<uint8_t, 4> fogRange2; // Unknown type | 0x61A98C (6400396 decimal)
	};
	static_assert(sizeof(mm6::Weather) == 0x61A990, "Invalid \"mm6::Weather\" structure size");
	static_assert(offsetof(mm6::Weather, shade) == 6400360);
	static_assert(offsetof(mm6::Weather, snow) == 6400364);
	static_assert(offsetof(mm6::Weather, fogRange1) == 6400392);
	static_assert(offsetof(mm6::Weather, fogRange2) == 6400396);



	struct TravelInfo // size: 0x20
	{
		union
		{
			std::array<uint8_t, 1> map; // Unknown type | 0x0 (0 decimal)
			uint8_t mapIndex; // 0x0 (0 decimal)
		};
		union
		{
			std::array<uint8_t, 7> daysAvailable; // 0x1 (1 decimal)
			struct
			{
				bool monday; // 0x1 (1 decimal)
				bool tuesday; // 0x2 (2 decimal)
				bool wednesday; // 0x3 (3 decimal)
				bool thursday; // 0x4 (4 decimal)
				bool friday; // 0x5 (5 decimal)
				bool saturday; // 0x6 (6 decimal)
				bool sunday; // 0x7 (7 decimal)
			};
		};
		uint8_t daysCount; // 0x8 (8 decimal)
		SKIP(3);
		union
		{
			std::array<int32_t, 3> pos; // 0xC (12 decimal)
			struct
			{
				int32_t x; // 0xC (12 decimal)
				int32_t y; // 0x10 (16 decimal)
				int32_t z; // 0x14 (20 decimal)
			};
		};
		int32_t direction; // 0x18 (24 decimal)
		int32_t QBit; // 0x1C (28 decimal)
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
			std::array<int32_t, 3> pos; // 0x0 (0 decimal)
			struct
			{
				int32_t x; // 0x0 (0 decimal)
				int32_t y; // 0x4 (4 decimal)
				int32_t z; // 0x8 (8 decimal)
			};
		};
		int16_t direction; // 0xC (12 decimal)
		int16_t lookAngle; // 0xE (14 decimal)
		union
		{
			std::array<uint8_t, 2> map; // Unknown type | 0x10 (16 decimal)
			int16_t mapStatsIndex; // 0x10 (16 decimal)
		};
		SKIP(2);
		// uint8_t* mapIndex; // real size is 0 | Unknown type | 0x14 (20 decimal)
	};
	static_assert(sizeof(mm6::TownPortalTownInfo) == 0x14, "Invalid \"mm6::TownPortalTownInfo\" structure size");
	static_assert(offsetof(mm6::TownPortalTownInfo, y) == 4);
	static_assert(offsetof(mm6::TownPortalTownInfo, z) == 8);
	static_assert(offsetof(mm6::TownPortalTownInfo, direction) == 12);
	static_assert(offsetof(mm6::TownPortalTownInfo, lookAngle) == 14);
	static_assert(offsetof(mm6::TownPortalTownInfo, map) == 16);
	static_assert(offsetof(mm6::TownPortalTownInfo, mapStatsIndex) == 16);



	struct SpellInfo // size: 0xE
	{
		union
		{
			std::array<int16_t, 3> spellPoints; // MMExt: 1..3, here 0..2 | 0x0 (0 decimal)
			struct
			{
				int16_t spellPointsNormal; // 0x0 (0 decimal)
				int16_t spellPointsExpert; // 0x2 (2 decimal)
				int16_t spellPointsMaster; // 0x4 (4 decimal)
			};
		};
		union
		{
			std::array<int16_t, 3> delay; // MMExt: 1..3, here 0..2 | 0x6 (6 decimal)
			struct
			{
				int16_t delayNormal; // 0x6 (6 decimal)
				int16_t delayExpert; // 0x8 (8 decimal)
				int16_t delayMaster; // 0xA (10 decimal)
			};
		};
		uint16_t bits; // 0xC (12 decimal)
	};
	static_assert(sizeof(mm6::SpellInfo) == 0xE, "Invalid \"mm6::SpellInfo\" structure size");
	static_assert(offsetof(mm6::SpellInfo, spellPointsExpert) == 2);
	static_assert(offsetof(mm6::SpellInfo, spellPointsMaster) == 4);
	static_assert(offsetof(mm6::SpellInfo, delay) == 6);
	static_assert(offsetof(mm6::SpellInfo, delayNormal) == 6);
	static_assert(offsetof(mm6::SpellInfo, delayExpert) == 8);
	static_assert(offsetof(mm6::SpellInfo, delayMaster) == 10);
	static_assert(offsetof(mm6::SpellInfo, bits) == 12);



	struct ShopItemKind // size: 0xA
	{
		int16_t level; // 0x0 (0 decimal)
		std::array<int16_t, 4> types; // MMExt: 1..4, here 0..3 | 0x2 (2 decimal)
	};
	static_assert(sizeof(mm6::ShopItemKind) == 0xA, "Invalid \"mm6::ShopItemKind\" structure size");
	static_assert(offsetof(mm6::ShopItemKind, types) == 2);



	struct PatchOptions // size: 0x178
	{
		int32_t size; // 0x0 (0 decimal)
		int32_t maxMLookAngle; // 0x4 (4 decimal)
		uint32_t mouseLook; // 4-byte boolean | 0x8 (8 decimal)
		uint32_t mouseLookUseAltMode; // 4-byte boolean | 0xC (12 decimal)
		uint32_t capsLockToggleMouseLook; // 4-byte boolean | 0x10 (16 decimal)
		uint32_t mouseFly; // 4-byte boolean | 0x14 (20 decimal)
		uint32_t mouseWheelFly; // 4-byte boolean | 0x18 (24 decimal)
		int32_t mouseLookTempKey; // 0x1C (28 decimal)
		int32_t mouseLookChangeKey; // 0x20 (32 decimal)
		int32_t inventoryKey; // 0x24 (36 decimal)
		int32_t charScreenKey; // 0x28 (40 decimal)
		int32_t doubleSpeedKey; // 0x2C (44 decimal)
		int32_t quickLoadKey; // 0x30 (48 decimal)
		int32_t autorunKey; // 0x34 (52 decimal)
		uint32_t HDWTRCount; // 0x38 (56 decimal) | MMExt info: [MM7+]
		uint32_t HDWTRDelay; // 0x3C (60 decimal) | MMExt info: [MM7+]
		int32_t horsemanSpeakTime; // 0x40 (64 decimal)
		int32_t boatmanSpeakTime; // 0x44 (68 decimal)
		union
		{
			float paletteSMul; // 0x48 (72 decimal) | MMExt info: [MM7+]
			float rawPaletteSMul; // 0x48 (72 decimal) | MMExt info: [MM7+]
		};
		union
		{
			float paletteVMul; // 0x4C (76 decimal) | MMExt info: [MM7+]
			float rawPaletteVMul; // 0x4C (76 decimal) | MMExt info: [MM7+]
		};
		uint32_t noBitmapsHwl; // 4-byte boolean | 0x50 (80 decimal) | MMExt info: [MM7+]
		uint32_t playMP3; // 4-byte boolean | 0x54 (84 decimal)
		int32_t musicLoopsCount; // 0x58 (88 decimal)
		uint32_t hardenArtifacts; // 4-byte boolean | 0x5C (92 decimal) | MMExt info: [MM7+]
		uint32_t progressiveDaggerTrippleDamage; // 4-byte boolean | 0x60 (96 decimal)
		uint32_t fixChests; // 4-byte boolean | 0x64 (100 decimal)
		uint32_t dataFiles; // 4-byte boolean | 0x68 (104 decimal)
		uint32_t fixDualWeaponsRecovery; // 4-byte boolean | 0x6C (108 decimal) | MMExt info: [MM6]
		int32_t increaseRecoveryRateStrength; // 0x70 (112 decimal) | MMExt info: [MM6]
		int32_t blasterRecovery; // 0x74 (116 decimal) | MMExt info: [MM6, MM7]
		uint32_t fixSkyBitmap; // 4-byte boolean | 0x78 (120 decimal) | MMExt info: [MM8]
		uint32_t noCD; // 4-byte boolean | 0x7C (124 decimal)
		uint32_t fixChestsByReorder; // 4-byte boolean | 0x80 (128 decimal)
		int32_t lastLoadedFileSize; // 0x84 (132 decimal)
		uint32_t fixTimers; // 4-byte boolean | 0x88 (136 decimal)
		uint32_t fixMovement; // 4-byte boolean | 0x8C (140 decimal)
		int32_t monsterJumpDownLimit; // 0x90 (144 decimal)
		uint32_t fixHeroismPedestal; // 4-byte boolean | 0x94 (148 decimal) | MMExt info: [MM8]
		uint32_t skipUnsellableItemCheck; // 4-byte boolean | 0x98 (152 decimal) | MMExt info: [MM7]
		uint32_t fixGMStaff; // 4-byte boolean | 0x9C (156 decimal) | MMExt info: [MM7]
		uint32_t fixObelisks; // 4-byte boolean | 0xA0 (160 decimal) | MMExt info: [MM8]
		uint32_t borderlessWindowed; // 4-byte boolean | 0xA4 (164 decimal) | MMExt info: Actually, it should be read as "not borderless fulscreen". It's set to false only when the game is in Borderless Fullscreen mode
		uint32_t compatibleMovieRender; // 4-byte boolean | 0xA8 (168 decimal)
		uint32_t smoothMovieScaling; // 4-byte boolean | 0xAC (172 decimal)
		uint32_t supportTrueColor; // 4-byte boolean | 0xB0 (176 decimal)
		int32_t renderRectLeft; // 0xB4 (180 decimal)
		int32_t renderRectTop; // 0xB8 (184 decimal)
		int32_t renderRectRight; // 0xBC (188 decimal)
		int32_t renderRectBottom; // 0xC0 (192 decimal)
		uint32_t fixUnimplementedSpells; // 4-byte boolean | 0xC4 (196 decimal) | MMExt info: [MM7+]
		int32_t indoorMinimapZoomMul; // 0xC8 (200 decimal)
		int32_t indoorMinimapZoomPower; // 0xCC (204 decimal)
		uint32_t fixMonsterSummon; // 4-byte boolean | 0xD0 (208 decimal) | MMExt info: [MM7+]
		uint32_t fixInterfaceBugs; // 4-byte boolean | 0xD4 (212 decimal) | MMExt info: [MM7]
		const char* UILayout; // PChar (read-only) | 0xD8 (216 decimal) | MMExt info: [MM7+]
		int32_t paperDollInChests; // 0xDC (220 decimal)
		uint32_t higherCloseRingsButton; // 4-byte boolean | 0xE0 (224 decimal) | MMExt info: [MM7]
		int32_t renderBottomPixel; // 0xE4 (228 decimal)
		uint32_t trueColorTextures; // 4-byte boolean | 0xE8 (232 decimal) | MMExt info: [MM7+]
		uint32_t resetPalettes; // 4-byte boolean | 0xEC (236 decimal) | MMExt info: [MM7+]
		uint32_t fixSFT; // 4-byte boolean | 0xF0 (240 decimal)
		uint32_t axeGMFullProbabilityAt; // 4-byte boolean | 0xF4 (244 decimal) | MMExt info: [MM7+]
		double mouseDX; // 0xF8 (248 decimal)
		double mouseDY; // 0x100 (256 decimal)
		uint32_t trueColorSprites; // 4-byte boolean | 0x108 (264 decimal) | MMExt info: [MM7+]
		uint32_t fixMonstersBlockingShots; // 4-byte boolean | 0x10C (268 decimal) | MMExt info: [MM7+]
		uint32_t fixParalyze; // 4-byte boolean | 0x110 (272 decimal) | MMExt info: [MM6] May come to MM7 and MM8 in the future.
		uint32_t enableAttackSpell; // 4-byte boolean | 0x114 (276 decimal)
		int32_t shooterMode; // 0x118 (280 decimal)
		int32_t maxMLookUpAngle; // 0x11C (284 decimal)
		uint32_t fixIceBoltBlast; // 4-byte boolean | 0x120 (288 decimal) | MMExt info: [MM7+]
		int32_t monSpritesSizeMul; // 0x124 (292 decimal) | MMExt info: Default is 0 - disabled. 0x10000 stands for 1.0.
		uint32_t fixMonsterAttackTypes; // 4-byte boolean | 0x128 (296 decimal) | MMExt info: [MM7+]
		uint32_t fixMonsterSpells; // 4-byte boolean | 0x12C (300 decimal)
		uint32_t fixSouldrinker; // 4-byte boolean | 0x130 (304 decimal)
		int32_t mouseLookPermKey; // 0x134 (308 decimal)
		int32_t lastSoundSample; // 0x138 (312 decimal)
		int32_t waterWalkDamage; // 0x13C (316 decimal) | MMExt info: [MM7+]
		uint32_t fixUnmarkedArtifacts; // 4-byte boolean | 0x140 (320 decimal) | MMExt info: [MM6, MM7]
		uint32_t fixClubsDelay; // 4-byte boolean | 0x144 (324 decimal) | MMExt info: [MM7+]
		uint32_t fixDarkTrainers; // 4-byte boolean | 0x148 (328 decimal) | MMExt info: [MM7]
		uint32_t fixLightBolt; // 4-byte boolean | 0x14C (332 decimal) | MMExt info: [MM7+]
		int32_t armageddonElement; // 0x150 (336 decimal)
		uint32_t fixKelebrim; // 4-byte boolean | 0x154 (340 decimal) | MMExt info: [MM7]
		uint32_t fixBarrels; // 4-byte boolean | 0x158 (344 decimal) | MMExt info: [MM7]
		uint32_t climbBetter; // 4-byte boolean | 0x15C (348 decimal) | MMExt info: [MM7+]
		uint32_t fixWaterWalkManaDrain; // 4-byte boolean | 0x160 (352 decimal)
		uint32_t keepEmptyWands; // 4-byte boolean | 0x164 (356 decimal)
		uint32_t dontSkipSimpleMessage; // 4-byte boolean | 0x168 (360 decimal) | MMExt info: [MM6, MM7]
		uint32_t fixItemDuplicates; // 4-byte boolean | 0x16C (364 decimal)
		uint32_t fixClubsGeneration; // 4-byte boolean | 0x170 (368 decimal) | MMExt info: [MM8]
		uint32_t fixAcidBurst; // 4-byte boolean | 0x174 (372 decimal) | MMExt info: [MM7+]
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
	static_assert(offsetof(mm6::PatchOptions, rawPaletteSMul) == 72);
	static_assert(offsetof(mm6::PatchOptions, paletteVMul) == 76);
	static_assert(offsetof(mm6::PatchOptions, rawPaletteVMul) == 76);
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



	struct MoveToMap // size: 0x1C
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
		int32_t direction; // 0xC (12 decimal) | MMExt info: 0 - 2047. 0 is East.
		int32_t lookAngle; // 0x10 (16 decimal)
		int32_t speedZ; // 0x14 (20 decimal)
		uint32_t defined; // 4-byte boolean | 0x18 (24 decimal)
	};
	static_assert(sizeof(mm6::MoveToMap) == 0x1C, "Invalid \"mm6::MoveToMap\" structure size");
	static_assert(offsetof(mm6::MoveToMap, y) == 4);
	static_assert(offsetof(mm6::MoveToMap, z) == 8);
	static_assert(offsetof(mm6::MoveToMap, direction) == 12);
	static_assert(offsetof(mm6::MoveToMap, lookAngle) == 16);
	static_assert(offsetof(mm6::MoveToMap, speedZ) == 20);
	static_assert(offsetof(mm6::MoveToMap, defined) == 24);



	struct MissileSetup // size: 0x1
	{
		bool alwaysShowSprite : 1; // 0x0 (0 decimal) | MMExt info: When there's a special way to display the object, still show the sprite as well
		bool hideSpecialDisplay : 1; // 0x0 (0 decimal) | MMExt info: Don't display the object in a special way
		bool autoCollision : 1; // 0x0 (0 decimal) | MMExt info: When the object hits anything, show an explosion, play explosion sound of the spell and call #MonsterAttacked:events.MonsterAttacked# or #PlayerAttacked:events.PlayerAttacked# appropriately
	};
	static_assert(sizeof(mm6::MissileSetup) == 0x1, "Invalid \"mm6::MissileSetup\" structure size");



	struct FogChances // size: 0x3
	{
		uint8_t thick; // 0x0 (0 decimal)
		uint8_t medium; // 0x1 (1 decimal)
		uint8_t light; // 0x2 (2 decimal)
	};
	static_assert(sizeof(mm6::FogChances) == 0x3, "Invalid \"mm6::FogChances\" structure size");
	static_assert(offsetof(mm6::FogChances, medium) == 1);
	static_assert(offsetof(mm6::FogChances, light) == 2);



	struct HouseMovie // size: 0x10
	{
		char* fileName; // EditPChar | 0x0 (0 decimal)
		uint8_t background; // 0x4 (4 decimal) | MMExt info: EVTPAR* index, used only in MM6
		SKIP(3);
		int32_t NPCPic; // 0x8 (8 decimal)
		uint8_t houseType; // 0xC (12 decimal)
		uint8_t sounds; // 0xD (13 decimal) | MMExt info: 30000 + Sounds*100 is the Id in Sounds.txt
		SKIP(2);
	};
	static_assert(sizeof(mm6::HouseMovie) == 0x10, "Invalid \"mm6::HouseMovie\" structure size");
	static_assert(offsetof(mm6::HouseMovie, background) == 4);
	static_assert(offsetof(mm6::HouseMovie, NPCPic) == 8);
	static_assert(offsetof(mm6::HouseMovie, houseType) == 12);
	static_assert(offsetof(mm6::HouseMovie, sounds) == 13);



	struct GameMouse // size: 0x268728
	{
		static inline mm6::ObjectRef* const target = 0;

		SKIP(16);
		int32_t x; // 0x10 (16 decimal)
		int32_t y; // 0x14 (20 decimal)
		SKIP(2524916);
		mm6::Item item; // 0x26870C (2524940 decimal)
		int __thiscall addItem(/*Item:structs.Item*/); // address: 0x487750 | defaults: (this)
		int __thiscall removeItem(); // address: 0x45A910 | defaults: (this)
		int __thiscall setIcon(/*Icon = "MICON1"*/); // address: 0x45A990 | defaults: (this), "MICON1"
		int __thiscall releaseItem(); // address: 0x41FE70 | defaults: (this)
	};
	static_assert(sizeof(mm6::GameMouse) == 0x268728, "Invalid \"mm6::GameMouse\" structure size");
	static_assert(offsetof(mm6::GameMouse, x) == 16);
	static_assert(offsetof(mm6::GameMouse, y) == 20);
	static_assert(offsetof(mm6::GameMouse, item) == 2524940);



	struct EventLine // size: 0xC
	{
		int32_t event; // 0x0 (0 decimal)
		int32_t line; // 0x4 (4 decimal)
		int32_t offset; // 0x8 (8 decimal)
	};
	static_assert(sizeof(mm6::EventLine) == 0xC, "Invalid \"mm6::EventLine\" structure size");
	static_assert(offsetof(mm6::EventLine, line) == 4);
	static_assert(offsetof(mm6::EventLine, offset) == 8);



	struct GeneralStoreItemKind // size: 0xE
	{
		int16_t level; // 0x0 (0 decimal)
		std::array<int16_t, 6> items; // MMExt: 1..6, here 0..5 | 0x2 (2 decimal)
	};
	static_assert(sizeof(mm6::GeneralStoreItemKind) == 0xE, "Invalid \"mm6::GeneralStoreItemKind\" structure size");
	static_assert(offsetof(mm6::GeneralStoreItemKind, items) == 2);



	struct ProgressBar // size: 0x168
	{
		SKIP(10);
		uint8_t max; // 0xA (10 decimal)
		uint8_t current; // 0xB (11 decimal)
		int32_t kind; // 0xC (12 decimal)
		mm6::LodPcx pcxLoading; // 0x10 (16 decimal)
		mm6::LodPcx pcxWomover; // 0x38 (56 decimal)
		mm6::LodPcx pcxDemover; // 0x60 (96 decimal)
		mm6::LodPcx pcxWomover2; // 0x88 (136 decimal)
		mm6::LodPcx pcxDemover2; // 0xB0 (176 decimal)
		mm6::LodBitmap bmpFireball; // 0xD8 (216 decimal)
		mm6::LodBitmap bmpBardata; // 0x120 (288 decimal)
		int __thiscall show(); // address: 0x438C30 | defaults: (this)
		int __thiscall hide(); // address: 0x438D40 | defaults: (this)
		int __thiscall increment(); // address: 0x438D20 | defaults: (this)
		int __thiscall setMax(); // address: 0x438D00 | defaults: (this)
		int __thiscall draw(); // address: 0x438E20 | defaults: (this)
	};
	static_assert(sizeof(mm6::ProgressBar) == 0x168, "Invalid \"mm6::ProgressBar\" structure size");
	static_assert(offsetof(mm6::ProgressBar, max) == 10);
	static_assert(offsetof(mm6::ProgressBar, current) == 11);
	static_assert(offsetof(mm6::ProgressBar, kind) == 12);
	static_assert(offsetof(mm6::ProgressBar, pcxLoading) == 16);
	static_assert(offsetof(mm6::ProgressBar, pcxWomover) == 56);
	static_assert(offsetof(mm6::ProgressBar, pcxDemover) == 96);
	static_assert(offsetof(mm6::ProgressBar, pcxWomover2) == 136);
	static_assert(offsetof(mm6::ProgressBar, pcxDemover2) == 176);
	static_assert(offsetof(mm6::ProgressBar, bmpFireball) == 216);
	static_assert(offsetof(mm6::ProgressBar, bmpBardata) == 288);



	struct Fnt // size: 0x1120
	{
		uint8_t minChar; // 0x0 (0 decimal)
		uint8_t maxChar; // 0x1 (1 decimal)
		SKIP(3);
		uint8_t height; // 0x5 (5 decimal)
		SKIP(2);
		union
		{
			int32_t palettesCount; // 0x8 (8 decimal)
			uint32_t palettes_size; // 0x8 (8 decimal)
		};
		std::array<mm6::LodBitmap*, 5> palettes; // size field offset is 0x8 | 0xC (12 decimal)
		std::array<std::array<int32_t, 3>, 256> ABC; // 0x20 (32 decimal)
		std::array<int32_t, 256> glyphOffsets; // 0xC20 (3104 decimal)
		std::array<uint8_t, 256> glyphData; // 0x1020 (4128 decimal)
	};
	static_assert(sizeof(mm6::Fnt) == 0x1120, "Invalid \"mm6::Fnt\" structure size");
	static_assert(offsetof(mm6::Fnt, maxChar) == 1);
	static_assert(offsetof(mm6::Fnt, height) == 5);
	static_assert(offsetof(mm6::Fnt, palettesCount) == 8);
	static_assert(offsetof(mm6::Fnt, palettes_size) == 8);
	static_assert(offsetof(mm6::Fnt, palettes) == 12);
	static_assert(offsetof(mm6::Fnt, ABC) == 32);
	static_assert(offsetof(mm6::Fnt, glyphOffsets) == 3104);
	static_assert(offsetof(mm6::Fnt, glyphData) == 4128);



	struct ActionItem // size: 0xC
	{
		int32_t action; // 0x0 (0 decimal)
		int32_t param; // 0x4 (4 decimal)
		int32_t param2; // 0x8 (8 decimal)
	};
	static_assert(sizeof(mm6::ActionItem) == 0xC, "Invalid \"mm6::ActionItem\" structure size");
	static_assert(offsetof(mm6::ActionItem, param) == 4);
	static_assert(offsetof(mm6::ActionItem, param2) == 8);
}
namespace mm7
{
	struct Weather // size: 0x6BDEC8
	{
		SKIP(7069344);
		int32_t shade; // 0x6BDEA0 (7069344 decimal) | MMExt info: 0 = sunny, 1 = dark, 2 = misty
		uint32_t snow; // 4-byte boolean | 0x6BDEA4 (7069348 decimal)
		SKIP(8);
		// uint8_t* fog; // real size is 0 | Unknown type | 0x6BDEB0 (7069360 decimal)
		SKIP(16);
		std::array<uint8_t, 4> fogRange1; // Unknown type | 0x6BDEC0 (7069376 decimal)
		std::array<uint8_t, 4> fogRange2; // Unknown type | 0x6BDEC4 (7069380 decimal)
	};
	static_assert(sizeof(mm7::Weather) == 0x6BDEC8, "Invalid \"mm7::Weather\" structure size");
	static_assert(offsetof(mm7::Weather, shade) == 7069344);
	static_assert(offsetof(mm7::Weather, snow) == 7069348);
	static_assert(offsetof(mm7::Weather, fogRange1) == 7069376);
	static_assert(offsetof(mm7::Weather, fogRange2) == 7069380);



	struct TravelInfo // size: 0x20
	{
		union
		{
			std::array<uint8_t, 1> map; // Unknown type | 0x0 (0 decimal)
			uint8_t mapIndex; // 0x0 (0 decimal)
		};
		union
		{
			std::array<uint8_t, 7> daysAvailable; // 0x1 (1 decimal)
			struct
			{
				bool monday; // 0x1 (1 decimal)
				bool tuesday; // 0x2 (2 decimal)
				bool wednesday; // 0x3 (3 decimal)
				bool thursday; // 0x4 (4 decimal)
				bool friday; // 0x5 (5 decimal)
				bool saturday; // 0x6 (6 decimal)
				bool sunday; // 0x7 (7 decimal)
			};
		};
		uint8_t daysCount; // 0x8 (8 decimal)
		SKIP(3);
		union
		{
			std::array<int32_t, 3> pos; // 0xC (12 decimal)
			struct
			{
				int32_t x; // 0xC (12 decimal)
				int32_t y; // 0x10 (16 decimal)
				int32_t z; // 0x14 (20 decimal)
			};
		};
		int32_t direction; // 0x18 (24 decimal)
		int32_t QBit; // 0x1C (28 decimal)
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
			std::array<int32_t, 3> pos; // 0x0 (0 decimal)
			struct
			{
				int32_t x; // 0x0 (0 decimal)
				int32_t y; // 0x4 (4 decimal)
				int32_t z; // 0x8 (8 decimal)
			};
		};
		int16_t direction; // 0xC (12 decimal)
		int16_t lookAngle; // 0xE (14 decimal)
		union
		{
			std::array<uint8_t, 2> map; // Unknown type | 0x10 (16 decimal)
			int16_t mapStatsIndex; // 0x10 (16 decimal)
		};
		SKIP(2);
	};
	static_assert(sizeof(mm7::TownPortalTownInfo) == 0x14, "Invalid \"mm7::TownPortalTownInfo\" structure size");
	static_assert(offsetof(mm7::TownPortalTownInfo, y) == 4);
	static_assert(offsetof(mm7::TownPortalTownInfo, z) == 8);
	static_assert(offsetof(mm7::TownPortalTownInfo, direction) == 12);
	static_assert(offsetof(mm7::TownPortalTownInfo, lookAngle) == 14);
	static_assert(offsetof(mm7::TownPortalTownInfo, map) == 16);
	static_assert(offsetof(mm7::TownPortalTownInfo, mapStatsIndex) == 16);



	struct SpellInfo // size: 0x14
	{
		union
		{
			std::array<int16_t, 4> spellPoints; // MMExt: 1..4, here 0..3 | 0x0 (0 decimal)
			struct
			{
				int16_t spellPointsNormal; // 0x0 (0 decimal)
				int16_t spellPointsExpert; // 0x2 (2 decimal)
				int16_t spellPointsMaster; // 0x4 (4 decimal)
				int16_t spellPointsGM; // 0x6 (6 decimal)
			};
		};
		union
		{
			std::array<int16_t, 4> delay; // MMExt: 1..4, here 0..3 | 0x8 (8 decimal)
			struct
			{
				int16_t delayNormal; // 0x8 (8 decimal)
				int16_t delayExpert; // 0xA (10 decimal)
				int16_t delayMaster; // 0xC (12 decimal)
				int16_t delayGM; // 0xE (14 decimal)
			};
		};
		uint8_t damageAdd; // 0x10 (16 decimal)
		uint8_t damageDiceSides; // 0x11 (17 decimal)
		union
		{
			uint16_t bits; // 0x12 (18 decimal)
			struct
			{
				bool castByMonster : 1; // 0x12 (18 decimal), bit index 7 | MMExt info: "M" in "Stats" from spells.txt
				bool castByEvent : 1; // 0x12 (18 decimal), bit index 6 | MMExt info: "E" in "Stats" from spells.txt
				bool causeDamage : 1; // 0x12 (18 decimal), bit index 5 | MMExt info: "C" in "Stats" from spells.txt
				bool specialDamage : 1; // 0x12 (18 decimal), bit index 4 | MMExt info: "X" in "Stats" from spells.txt
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



	struct ShopItemKind // size: 0xA
	{
		int16_t level; // 0x0 (0 decimal)
		std::array<int16_t, 4> types; // MMExt: 1..4, here 0..3 | 0x2 (2 decimal)
	};
	static_assert(sizeof(mm7::ShopItemKind) == 0xA, "Invalid \"mm7::ShopItemKind\" structure size");
	static_assert(offsetof(mm7::ShopItemKind, types) == 2);



	struct PatchOptions // size: 0x178
	{
		int32_t size; // 0x0 (0 decimal)
		int32_t maxMLookAngle; // 0x4 (4 decimal)
		uint32_t mouseLook; // 4-byte boolean | 0x8 (8 decimal)
		uint32_t mouseLookUseAltMode; // 4-byte boolean | 0xC (12 decimal)
		uint32_t capsLockToggleMouseLook; // 4-byte boolean | 0x10 (16 decimal)
		uint32_t mouseFly; // 4-byte boolean | 0x14 (20 decimal)
		uint32_t mouseWheelFly; // 4-byte boolean | 0x18 (24 decimal)
		int32_t mouseLookTempKey; // 0x1C (28 decimal)
		int32_t mouseLookChangeKey; // 0x20 (32 decimal)
		int32_t inventoryKey; // 0x24 (36 decimal)
		int32_t charScreenKey; // 0x28 (40 decimal)
		int32_t doubleSpeedKey; // 0x2C (44 decimal)
		int32_t quickLoadKey; // 0x30 (48 decimal)
		int32_t autorunKey; // 0x34 (52 decimal)
		uint32_t HDWTRCount; // 0x38 (56 decimal) | MMExt info: [MM7+]
		uint32_t HDWTRDelay; // 0x3C (60 decimal) | MMExt info: [MM7+]
		int32_t horsemanSpeakTime; // 0x40 (64 decimal)
		int32_t boatmanSpeakTime; // 0x44 (68 decimal)
		union
		{
			std::array<uint8_t, 4> paletteSMul; // Unknown type | 0x48 (72 decimal) | MMExt info: [MM7+]
			float rawPaletteSMul; // 0x48 (72 decimal) | MMExt info: [MM7+]
		};
		union
		{
			std::array<uint8_t, 4> paletteVMul; // Unknown type | 0x4C (76 decimal) | MMExt info: [MM7+]
			float rawPaletteVMul; // 0x4C (76 decimal) | MMExt info: [MM7+]
		};
		uint32_t noBitmapsHwl; // 4-byte boolean | 0x50 (80 decimal) | MMExt info: [MM7+]
		uint32_t playMP3; // 4-byte boolean | 0x54 (84 decimal)
		int32_t musicLoopsCount; // 0x58 (88 decimal)
		uint32_t hardenArtifacts; // 4-byte boolean | 0x5C (92 decimal) | MMExt info: [MM7+]
		uint32_t progressiveDaggerTrippleDamage; // 4-byte boolean | 0x60 (96 decimal)
		uint32_t fixChests; // 4-byte boolean | 0x64 (100 decimal)
		uint32_t dataFiles; // 4-byte boolean | 0x68 (104 decimal)
		uint32_t fixDualWeaponsRecovery; // 4-byte boolean | 0x6C (108 decimal) | MMExt info: [MM6]
		int32_t increaseRecoveryRateStrength; // 0x70 (112 decimal) | MMExt info: [MM6]
		int32_t blasterRecovery; // 0x74 (116 decimal) | MMExt info: [MM6, MM7]
		uint32_t fixSkyBitmap; // 4-byte boolean | 0x78 (120 decimal) | MMExt info: [MM8]
		uint32_t noCD; // 4-byte boolean | 0x7C (124 decimal)
		uint32_t fixChestsByReorder; // 4-byte boolean | 0x80 (128 decimal)
		int32_t lastLoadedFileSize; // 0x84 (132 decimal)
		uint32_t fixTimers; // 4-byte boolean | 0x88 (136 decimal)
		uint32_t fixMovement; // 4-byte boolean | 0x8C (140 decimal)
		int32_t monsterJumpDownLimit; // 0x90 (144 decimal)
		uint32_t fixHeroismPedestal; // 4-byte boolean | 0x94 (148 decimal) | MMExt info: [MM8]
		uint32_t skipUnsellableItemCheck; // 4-byte boolean | 0x98 (152 decimal) | MMExt info: [MM7]
		uint32_t fixGMStaff; // 4-byte boolean | 0x9C (156 decimal) | MMExt info: [MM7]
		uint32_t fixObelisks; // 4-byte boolean | 0xA0 (160 decimal) | MMExt info: [MM8]
		uint32_t borderlessWindowed; // 4-byte boolean | 0xA4 (164 decimal) | MMExt info: Actually, it should be read as "not borderless fulscreen". It's set to false only when the game is in Borderless Fullscreen mode
		uint32_t compatibleMovieRender; // 4-byte boolean | 0xA8 (168 decimal)
		uint32_t smoothMovieScaling; // 4-byte boolean | 0xAC (172 decimal)
		uint32_t supportTrueColor; // 4-byte boolean | 0xB0 (176 decimal)
		int32_t renderRectLeft; // 0xB4 (180 decimal)
		int32_t renderRectTop; // 0xB8 (184 decimal)
		int32_t renderRectRight; // 0xBC (188 decimal)
		int32_t renderRectBottom; // 0xC0 (192 decimal)
		uint32_t fixUnimplementedSpells; // 4-byte boolean | 0xC4 (196 decimal) | MMExt info: [MM7+]
		int32_t indoorMinimapZoomMul; // 0xC8 (200 decimal)
		int32_t indoorMinimapZoomPower; // 0xCC (204 decimal)
		uint32_t fixMonsterSummon; // 4-byte boolean | 0xD0 (208 decimal) | MMExt info: [MM7+]
		uint32_t fixInterfaceBugs; // 4-byte boolean | 0xD4 (212 decimal) | MMExt info: [MM7]
		const char* UILayout; // PChar (read-only) | 0xD8 (216 decimal) | MMExt info: [MM7+]
		int32_t paperDollInChests; // 0xDC (220 decimal)
		uint32_t higherCloseRingsButton; // 4-byte boolean | 0xE0 (224 decimal) | MMExt info: [MM7]
		int32_t renderBottomPixel; // 0xE4 (228 decimal)
		uint32_t trueColorTextures; // 4-byte boolean | 0xE8 (232 decimal) | MMExt info: [MM7+]
		uint32_t resetPalettes; // 4-byte boolean | 0xEC (236 decimal) | MMExt info: [MM7+]
		uint32_t fixSFT; // 4-byte boolean | 0xF0 (240 decimal)
		uint32_t axeGMFullProbabilityAt; // 4-byte boolean | 0xF4 (244 decimal) | MMExt info: [MM7+]
		double mouseDX; // 0xF8 (248 decimal)
		double mouseDY; // 0x100 (256 decimal)
		uint32_t trueColorSprites; // 4-byte boolean | 0x108 (264 decimal) | MMExt info: [MM7+]
		uint32_t fixMonstersBlockingShots; // 4-byte boolean | 0x10C (268 decimal) | MMExt info: [MM7+]
		uint32_t fixParalyze; // 4-byte boolean | 0x110 (272 decimal) | MMExt info: [MM6] May come to MM7 and MM8 in the future.
		uint32_t enableAttackSpell; // 4-byte boolean | 0x114 (276 decimal)
		int32_t shooterMode; // 0x118 (280 decimal)
		int32_t maxMLookUpAngle; // 0x11C (284 decimal)
		uint32_t fixIceBoltBlast; // 4-byte boolean | 0x120 (288 decimal) | MMExt info: [MM7+]
		int32_t monSpritesSizeMul; // 0x124 (292 decimal) | MMExt info: Default is 0 - disabled. 0x10000 stands for 1.0.
		uint32_t fixMonsterAttackTypes; // 4-byte boolean | 0x128 (296 decimal) | MMExt info: [MM7+]
		uint32_t fixMonsterSpells; // 4-byte boolean | 0x12C (300 decimal)
		uint32_t fixSouldrinker; // 4-byte boolean | 0x130 (304 decimal)
		int32_t mouseLookPermKey; // 0x134 (308 decimal)
		int32_t lastSoundSample; // 0x138 (312 decimal)
		int32_t waterWalkDamage; // 0x13C (316 decimal) | MMExt info: [MM7+]
		uint32_t fixUnmarkedArtifacts; // 4-byte boolean | 0x140 (320 decimal) | MMExt info: [MM6, MM7]
		uint32_t fixClubsDelay; // 4-byte boolean | 0x144 (324 decimal) | MMExt info: [MM7+]
		uint32_t fixDarkTrainers; // 4-byte boolean | 0x148 (328 decimal) | MMExt info: [MM7]
		uint32_t fixLightBolt; // 4-byte boolean | 0x14C (332 decimal) | MMExt info: [MM7+]
		int32_t armageddonElement; // 0x150 (336 decimal)
		uint32_t fixKelebrim; // 4-byte boolean | 0x154 (340 decimal) | MMExt info: [MM7]
		uint32_t fixBarrels; // 4-byte boolean | 0x158 (344 decimal) | MMExt info: [MM7]
		uint32_t climbBetter; // 4-byte boolean | 0x15C (348 decimal) | MMExt info: [MM7+]
		uint32_t fixWaterWalkManaDrain; // 4-byte boolean | 0x160 (352 decimal)
		uint32_t keepEmptyWands; // 4-byte boolean | 0x164 (356 decimal)
		uint32_t dontSkipSimpleMessage; // 4-byte boolean | 0x168 (360 decimal) | MMExt info: [MM6, MM7]
		uint32_t fixItemDuplicates; // 4-byte boolean | 0x16C (364 decimal)
		uint32_t fixClubsGeneration; // 4-byte boolean | 0x170 (368 decimal) | MMExt info: [MM8]
		uint32_t fixAcidBurst; // 4-byte boolean | 0x174 (372 decimal) | MMExt info: [MM7+]
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
	static_assert(offsetof(mm7::PatchOptions, rawPaletteSMul) == 72);
	static_assert(offsetof(mm7::PatchOptions, paletteVMul) == 76);
	static_assert(offsetof(mm7::PatchOptions, rawPaletteVMul) == 76);
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



	struct MoveToMap // size: 0x1C
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
		int32_t direction; // 0xC (12 decimal) | MMExt info: 0 - 2047. 0 is East.
		int32_t lookAngle; // 0x10 (16 decimal)
		int32_t speedZ; // 0x14 (20 decimal)
		uint32_t defined; // 4-byte boolean | 0x18 (24 decimal)
	};
	static_assert(sizeof(mm7::MoveToMap) == 0x1C, "Invalid \"mm7::MoveToMap\" structure size");
	static_assert(offsetof(mm7::MoveToMap, y) == 4);
	static_assert(offsetof(mm7::MoveToMap, z) == 8);
	static_assert(offsetof(mm7::MoveToMap, direction) == 12);
	static_assert(offsetof(mm7::MoveToMap, lookAngle) == 16);
	static_assert(offsetof(mm7::MoveToMap, speedZ) == 20);
	static_assert(offsetof(mm7::MoveToMap, defined) == 24);



	struct MouseStruct // size: 0x110
	{
		static inline mm7::ObjectRef* const target = 0;

		SKIP(264);
		int32_t x; // 0x108 (264 decimal)
		int32_t y; // 0x10C (268 decimal)
		int __thiscall removeItem(); // address: 0x4698AA | defaults: (this)
		int __thiscall setIcon(/*Icon = "MICON1"*/); // address: 0x469907 | defaults: (this), "MICON1"
		int __thiscall releaseItem(); // address: 0x421AD5 | defaults: (this)
		int __thiscall addItem(/*Item:structs.Item*/); // address: 0x4936D9 | defaults: (this)
	};
	static_assert(sizeof(mm7::MouseStruct) == 0x110, "Invalid \"mm7::MouseStruct\" structure size");
	static_assert(offsetof(mm7::MouseStruct, x) == 264);
	static_assert(offsetof(mm7::MouseStruct, y) == 268);



	struct MissileSetup // size: 0x1
	{
		bool alwaysShowSprite : 1; // 0x0 (0 decimal) | MMExt info: When there's a special way to display the object, still show the sprite as well
		bool hideSpecialDisplay : 1; // 0x0 (0 decimal) | MMExt info: Don't display the object in a special way
		bool autoCollision : 1; // 0x0 (0 decimal) | MMExt info: When the object hits anything, show an explosion, play explosion sound of the spell and call #MonsterAttacked:events.MonsterAttacked# or #PlayerAttacked:events.PlayerAttacked# appropriately
	};
	static_assert(sizeof(mm7::MissileSetup) == 0x1, "Invalid \"mm7::MissileSetup\" structure size");



	struct FogChances // size: 0x4
	{
		uint8_t thick; // 0x0 (0 decimal)
		uint8_t medium; // 0x1 (1 decimal)
		uint8_t light; // 0x2 (2 decimal)
		SKIP(1);
	};
	static_assert(sizeof(mm7::FogChances) == 0x4, "Invalid \"mm7::FogChances\" structure size");
	static_assert(offsetof(mm7::FogChances, medium) == 1);
	static_assert(offsetof(mm7::FogChances, light) == 2);



	struct HouseMovie // size: 0x10
	{
		char* fileName; // EditPChar | 0x0 (0 decimal)
		uint8_t background; // 0x4 (4 decimal) | MMExt info: EVTPAR* index, used only in MM6
		SKIP(3);
		int32_t NPCPic; // 0x8 (8 decimal)
		uint8_t houseType; // 0xC (12 decimal)
		uint8_t sounds; // 0xD (13 decimal) | MMExt info: 30000 + Sounds*100 is the Id in Sounds.txt
		SKIP(2);
	};
	static_assert(sizeof(mm7::HouseMovie) == 0x10, "Invalid \"mm7::HouseMovie\" structure size");
	static_assert(offsetof(mm7::HouseMovie, background) == 4);
	static_assert(offsetof(mm7::HouseMovie, NPCPic) == 8);
	static_assert(offsetof(mm7::HouseMovie, houseType) == 12);
	static_assert(offsetof(mm7::HouseMovie, sounds) == 13);



	struct EventLine // size: 0xC
	{
		int32_t event; // 0x0 (0 decimal)
		int32_t line; // 0x4 (4 decimal)
		int32_t offset; // 0x8 (8 decimal)
	};
	static_assert(sizeof(mm7::EventLine) == 0xC, "Invalid \"mm7::EventLine\" structure size");
	static_assert(offsetof(mm7::EventLine, line) == 4);
	static_assert(offsetof(mm7::EventLine, offset) == 8);



	struct GameMouse // size: 0xAD45B0
	{
		SKIP(7473160);
		mm7::MouseStruct* mouseStruct; // 0x720808 (7473160 decimal)
		SKIP(3882368);
		mm7::Item item; // 0xAD458C (11355532 decimal)
	};
	static_assert(sizeof(mm7::GameMouse) == 0xAD45B0, "Invalid \"mm7::GameMouse\" structure size");
	static_assert(offsetof(mm7::GameMouse, mouseStruct) == 7473160);
	static_assert(offsetof(mm7::GameMouse, item) == 11355532);



	struct ProgressBar // size: 0x1B8
	{
		SKIP(10);
		uint8_t max; // 0xA (10 decimal)
		uint8_t current; // 0xB (11 decimal)
		int32_t kind; // 0xC (12 decimal)
		std::array<bool, 8> seenScreens; // 0x10 (16 decimal)
		mm7::LodPcx pcxLoading; // 0x18 (24 decimal)
		mm7::LodPcx pcxWomover; // 0x40 (64 decimal)
		mm7::LodPcx pcxDemover; // 0x68 (104 decimal)
		mm7::LodPcx pcxWomover2; // 0x90 (144 decimal)
		mm7::LodPcx pcxDemover2; // 0xB8 (184 decimal)
		mm7::LodBitmap bmpFireball; // 0xE0 (224 decimal)
		mm7::LodBitmap bmpBardata; // 0x128 (296 decimal)
		mm7::LodBitmap bmpLoadprog; // 0x170 (368 decimal)
		int __thiscall hide(); // address: 0x443605 | defaults: (this)
		int __thiscall increment(); // address: 0x4435F0 | defaults: (this)
		int __thiscall setMax(); // address: 0x4435DE | defaults: (this)
		int __thiscall draw(); // address: 0x443693 | defaults: (this)
		int __thiscall show(); // address: 0x4434A7 | defaults: (this)
	};
	static_assert(sizeof(mm7::ProgressBar) == 0x1B8, "Invalid \"mm7::ProgressBar\" structure size");
	static_assert(offsetof(mm7::ProgressBar, max) == 10);
	static_assert(offsetof(mm7::ProgressBar, current) == 11);
	static_assert(offsetof(mm7::ProgressBar, kind) == 12);
	static_assert(offsetof(mm7::ProgressBar, seenScreens) == 16);
	static_assert(offsetof(mm7::ProgressBar, pcxLoading) == 24);
	static_assert(offsetof(mm7::ProgressBar, pcxWomover) == 64);
	static_assert(offsetof(mm7::ProgressBar, pcxDemover) == 104);
	static_assert(offsetof(mm7::ProgressBar, pcxWomover2) == 144);
	static_assert(offsetof(mm7::ProgressBar, pcxDemover2) == 184);
	static_assert(offsetof(mm7::ProgressBar, bmpFireball) == 224);
	static_assert(offsetof(mm7::ProgressBar, bmpBardata) == 296);
	static_assert(offsetof(mm7::ProgressBar, bmpLoadprog) == 368);



	struct Fnt // size: 0x1120
	{
		uint8_t minChar; // 0x0 (0 decimal)
		uint8_t maxChar; // 0x1 (1 decimal)
		SKIP(3);
		uint8_t height; // 0x5 (5 decimal)
		SKIP(2);
		union
		{
			int32_t palettesCount; // 0x8 (8 decimal)
			uint32_t palettes_size; // 0x8 (8 decimal)
		};
		std::array<mm7::LodBitmap*, 5> palettes; // size field offset is 0x8 | 0xC (12 decimal)
		std::array<std::array<int32_t, 3>, 256> ABC; // 0x20 (32 decimal)
		std::array<int32_t, 256> glyphOffsets; // 0xC20 (3104 decimal)
		std::array<uint8_t, 256> glyphData; // 0x1020 (4128 decimal)
	};
	static_assert(sizeof(mm7::Fnt) == 0x1120, "Invalid \"mm7::Fnt\" structure size");
	static_assert(offsetof(mm7::Fnt, maxChar) == 1);
	static_assert(offsetof(mm7::Fnt, height) == 5);
	static_assert(offsetof(mm7::Fnt, palettesCount) == 8);
	static_assert(offsetof(mm7::Fnt, palettes_size) == 8);
	static_assert(offsetof(mm7::Fnt, palettes) == 12);
	static_assert(offsetof(mm7::Fnt, ABC) == 32);
	static_assert(offsetof(mm7::Fnt, glyphOffsets) == 3104);
	static_assert(offsetof(mm7::Fnt, glyphData) == 4128);



	struct ActionItem // size: 0xC
	{
		int32_t action; // 0x0 (0 decimal)
		int32_t param; // 0x4 (4 decimal)
		int32_t param2; // 0x8 (8 decimal)
	};
	static_assert(sizeof(mm7::ActionItem) == 0xC, "Invalid \"mm7::ActionItem\" structure size");
	static_assert(offsetof(mm7::ActionItem, param) == 4);
	static_assert(offsetof(mm7::ActionItem, param2) == 8);
}
namespace mm8
{
	struct Weather // size: 0x6F2FBC
	{
		SKIP(7286676);
		uint32_t rain; // 4-byte boolean | 0x6F2F94 (7286676 decimal)
		int32_t shade; // 0x6F2F98 (7286680 decimal) | MMExt info: 0 = sunny, 1 = dark, 2 = misty
		SKIP(8);
		// uint8_t* fog; // real size is 0 | Unknown type | 0x6F2FA4 (7286692 decimal)
		SKIP(16);
		std::array<uint8_t, 4> fogRange1; // Unknown type | 0x6F2FB4 (7286708 decimal)
		std::array<uint8_t, 4> fogRange2; // Unknown type | 0x6F2FB8 (7286712 decimal)
	};
	static_assert(sizeof(mm8::Weather) == 0x6F2FBC, "Invalid \"mm8::Weather\" structure size");
	static_assert(offsetof(mm8::Weather, rain) == 7286676);
	static_assert(offsetof(mm8::Weather, shade) == 7286680);
	static_assert(offsetof(mm8::Weather, fogRange1) == 7286708);
	static_assert(offsetof(mm8::Weather, fogRange2) == 7286712);



	struct TravelInfo // size: 0x20
	{
		union
		{
			std::array<uint8_t, 1> map; // Unknown type | 0x0 (0 decimal)
			uint8_t mapIndex; // 0x0 (0 decimal)
		};
		union
		{
			std::array<uint8_t, 7> daysAvailable; // 0x1 (1 decimal)
			struct
			{
				bool monday; // 0x1 (1 decimal)
				bool tuesday; // 0x2 (2 decimal)
				bool wednesday; // 0x3 (3 decimal)
				bool thursday; // 0x4 (4 decimal)
				bool friday; // 0x5 (5 decimal)
				bool saturday; // 0x6 (6 decimal)
				bool sunday; // 0x7 (7 decimal)
			};
		};
		uint8_t daysCount; // 0x8 (8 decimal)
		SKIP(3);
		union
		{
			std::array<int32_t, 3> pos; // 0xC (12 decimal)
			struct
			{
				int32_t x; // 0xC (12 decimal)
				int32_t y; // 0x10 (16 decimal)
				int32_t z; // 0x14 (20 decimal)
			};
		};
		int32_t direction; // 0x18 (24 decimal)
		int32_t QBit; // 0x1C (28 decimal)
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
			std::array<int32_t, 3> pos; // 0x0 (0 decimal)
			struct
			{
				int32_t x; // 0x0 (0 decimal)
				int32_t y; // 0x4 (4 decimal)
				int32_t z; // 0x8 (8 decimal)
			};
		};
		int16_t direction; // 0xC (12 decimal)
		int16_t lookAngle; // 0xE (14 decimal)
		union
		{
			std::array<uint8_t, 2> map; // Unknown type | 0x10 (16 decimal)
			int16_t mapStatsIndex; // 0x10 (16 decimal)
		};
		SKIP(2);
	};
	static_assert(sizeof(mm8::TownPortalTownInfo) == 0x14, "Invalid \"mm8::TownPortalTownInfo\" structure size");
	static_assert(offsetof(mm8::TownPortalTownInfo, y) == 4);
	static_assert(offsetof(mm8::TownPortalTownInfo, z) == 8);
	static_assert(offsetof(mm8::TownPortalTownInfo, direction) == 12);
	static_assert(offsetof(mm8::TownPortalTownInfo, lookAngle) == 14);
	static_assert(offsetof(mm8::TownPortalTownInfo, map) == 16);
	static_assert(offsetof(mm8::TownPortalTownInfo, mapStatsIndex) == 16);



	struct SpellInfo // size: 0x14
	{
		union
		{
			std::array<int16_t, 4> spellPoints; // MMExt: 1..4, here 0..3 | 0x0 (0 decimal)
			struct
			{
				int16_t spellPointsNormal; // 0x0 (0 decimal)
				int16_t spellPointsExpert; // 0x2 (2 decimal)
				int16_t spellPointsMaster; // 0x4 (4 decimal)
				int16_t spellPointsGM; // 0x6 (6 decimal)
			};
		};
		union
		{
			std::array<int16_t, 4> delay; // MMExt: 1..4, here 0..3 | 0x8 (8 decimal)
			struct
			{
				int16_t delayNormal; // 0x8 (8 decimal)
				int16_t delayExpert; // 0xA (10 decimal)
				int16_t delayMaster; // 0xC (12 decimal)
				int16_t delayGM; // 0xE (14 decimal)
			};
		};
		uint8_t damageAdd; // 0x10 (16 decimal)
		uint8_t damageDiceSides; // 0x11 (17 decimal)
		union
		{
			uint16_t bits; // 0x12 (18 decimal)
			struct
			{
				bool castByMonster : 1; // 0x12 (18 decimal), bit index 7 | MMExt info: "M" in "Stats" from spells.txt
				bool castByEvent : 1; // 0x12 (18 decimal), bit index 6 | MMExt info: "E" in "Stats" from spells.txt
				bool causeDamage : 1; // 0x12 (18 decimal), bit index 5 | MMExt info: "C" in "Stats" from spells.txt
				bool specialDamage : 1; // 0x12 (18 decimal), bit index 4 | MMExt info: "X" in "Stats" from spells.txt
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



	struct ShopItemKind // size: 0xA
	{
		int16_t level; // 0x0 (0 decimal)
		std::array<int16_t, 4> types; // MMExt: 1..4, here 0..3 | 0x2 (2 decimal)
	};
	static_assert(sizeof(mm8::ShopItemKind) == 0xA, "Invalid \"mm8::ShopItemKind\" structure size");
	static_assert(offsetof(mm8::ShopItemKind, types) == 2);



	struct ProgressBar // size: 0x10
	{
		SKIP(10);
		uint8_t max; // 0xA (10 decimal)
		uint8_t current; // 0xB (11 decimal)
		int32_t kind; // 0xC (12 decimal)
		int __thiscall show(); // address: 0x440288 | defaults: (this)
		int __thiscall draw(); // address: 0x44047E | defaults: (this)
		int __thiscall hide(); // address: 0x4403DA | defaults: (this)
		int __thiscall increment(); // address: 0x4403C5 | defaults: (this)
		int __thiscall setMax(); // address: 0x4403B3 | defaults: (this)
	};
	static_assert(sizeof(mm8::ProgressBar) == 0x10, "Invalid \"mm8::ProgressBar\" structure size");
	static_assert(offsetof(mm8::ProgressBar, max) == 10);
	static_assert(offsetof(mm8::ProgressBar, current) == 11);
	static_assert(offsetof(mm8::ProgressBar, kind) == 12);



	struct PatchOptions // size: 0x178
	{
		int32_t size; // 0x0 (0 decimal)
		int32_t maxMLookAngle; // 0x4 (4 decimal)
		uint32_t mouseLook; // 4-byte boolean | 0x8 (8 decimal)
		uint32_t mouseLookUseAltMode; // 4-byte boolean | 0xC (12 decimal)
		uint32_t capsLockToggleMouseLook; // 4-byte boolean | 0x10 (16 decimal)
		uint32_t mouseFly; // 4-byte boolean | 0x14 (20 decimal)
		uint32_t mouseWheelFly; // 4-byte boolean | 0x18 (24 decimal)
		int32_t mouseLookTempKey; // 0x1C (28 decimal)
		int32_t mouseLookChangeKey; // 0x20 (32 decimal)
		int32_t inventoryKey; // 0x24 (36 decimal)
		int32_t charScreenKey; // 0x28 (40 decimal)
		int32_t doubleSpeedKey; // 0x2C (44 decimal)
		int32_t quickLoadKey; // 0x30 (48 decimal)
		int32_t autorunKey; // 0x34 (52 decimal)
		uint32_t HDWTRCount; // 0x38 (56 decimal) | MMExt info: [MM7+]
		uint32_t HDWTRDelay; // 0x3C (60 decimal) | MMExt info: [MM7+]
		int32_t horsemanSpeakTime; // 0x40 (64 decimal)
		int32_t boatmanSpeakTime; // 0x44 (68 decimal)
		float paletteSMul; // 0x48 (72 decimal) | MMExt info: [MM7+]
		float paletteVMul; // 0x4C (76 decimal) | MMExt info: [MM7+]
		uint32_t noBitmapsHwl; // 4-byte boolean | 0x50 (80 decimal) | MMExt info: [MM7+]
		uint32_t playMP3; // 4-byte boolean | 0x54 (84 decimal)
		int32_t musicLoopsCount; // 0x58 (88 decimal)
		uint32_t hardenArtifacts; // 4-byte boolean | 0x5C (92 decimal) | MMExt info: [MM7+]
		uint32_t progressiveDaggerTrippleDamage; // 4-byte boolean | 0x60 (96 decimal)
		uint32_t fixChests; // 4-byte boolean | 0x64 (100 decimal)
		uint32_t dataFiles; // 4-byte boolean | 0x68 (104 decimal)
		uint32_t fixDualWeaponsRecovery; // 4-byte boolean | 0x6C (108 decimal) | MMExt info: [MM6]
		int32_t increaseRecoveryRateStrength; // 0x70 (112 decimal) | MMExt info: [MM6]
		int32_t blasterRecovery; // 0x74 (116 decimal) | MMExt info: [MM6, MM7]
		uint32_t fixSkyBitmap; // 4-byte boolean | 0x78 (120 decimal) | MMExt info: [MM8]
		uint32_t noCD; // 4-byte boolean | 0x7C (124 decimal)
		uint32_t fixChestsByReorder; // 4-byte boolean | 0x80 (128 decimal)
		int32_t lastLoadedFileSize; // 0x84 (132 decimal)
		uint32_t fixTimers; // 4-byte boolean | 0x88 (136 decimal)
		uint32_t fixMovement; // 4-byte boolean | 0x8C (140 decimal)
		int32_t monsterJumpDownLimit; // 0x90 (144 decimal)
		uint32_t fixHeroismPedestal; // 4-byte boolean | 0x94 (148 decimal) | MMExt info: [MM8]
		uint32_t skipUnsellableItemCheck; // 4-byte boolean | 0x98 (152 decimal) | MMExt info: [MM7]
		uint32_t fixGMStaff; // 4-byte boolean | 0x9C (156 decimal) | MMExt info: [MM7]
		uint32_t fixObelisks; // 4-byte boolean | 0xA0 (160 decimal) | MMExt info: [MM8]
		uint32_t borderlessWindowed; // 4-byte boolean | 0xA4 (164 decimal) | MMExt info: Actually, it should be read as "not borderless fulscreen". It's set to false only when the game is in Borderless Fullscreen mode
		uint32_t compatibleMovieRender; // 4-byte boolean | 0xA8 (168 decimal)
		uint32_t smoothMovieScaling; // 4-byte boolean | 0xAC (172 decimal)
		uint32_t supportTrueColor; // 4-byte boolean | 0xB0 (176 decimal)
		int32_t renderRectLeft; // 0xB4 (180 decimal)
		int32_t renderRectTop; // 0xB8 (184 decimal)
		int32_t renderRectRight; // 0xBC (188 decimal)
		int32_t renderRectBottom; // 0xC0 (192 decimal)
		uint32_t fixUnimplementedSpells; // 4-byte boolean | 0xC4 (196 decimal) | MMExt info: [MM7+]
		int32_t indoorMinimapZoomMul; // 0xC8 (200 decimal)
		int32_t indoorMinimapZoomPower; // 0xCC (204 decimal)
		uint32_t fixMonsterSummon; // 4-byte boolean | 0xD0 (208 decimal) | MMExt info: [MM7+]
		uint32_t fixInterfaceBugs; // 4-byte boolean | 0xD4 (212 decimal) | MMExt info: [MM7]
		const char* UILayout; // PChar (read-only) | 0xD8 (216 decimal) | MMExt info: [MM7+]
		int32_t paperDollInChests; // 0xDC (220 decimal)
		uint32_t higherCloseRingsButton; // 4-byte boolean | 0xE0 (224 decimal) | MMExt info: [MM7]
		int32_t renderBottomPixel; // 0xE4 (228 decimal)
		uint32_t trueColorTextures; // 4-byte boolean | 0xE8 (232 decimal) | MMExt info: [MM7+]
		uint32_t resetPalettes; // 4-byte boolean | 0xEC (236 decimal) | MMExt info: [MM7+]
		uint32_t fixSFT; // 4-byte boolean | 0xF0 (240 decimal)
		uint32_t axeGMFullProbabilityAt; // 4-byte boolean | 0xF4 (244 decimal) | MMExt info: [MM7+]
		double mouseDX; // 0xF8 (248 decimal)
		double mouseDY; // 0x100 (256 decimal)
		uint32_t trueColorSprites; // 4-byte boolean | 0x108 (264 decimal) | MMExt info: [MM7+]
		uint32_t fixMonstersBlockingShots; // 4-byte boolean | 0x10C (268 decimal) | MMExt info: [MM7+]
		uint32_t fixParalyze; // 4-byte boolean | 0x110 (272 decimal) | MMExt info: [MM6] May come to MM7 and MM8 in the future.
		uint32_t enableAttackSpell; // 4-byte boolean | 0x114 (276 decimal)
		int32_t shooterMode; // 0x118 (280 decimal)
		int32_t maxMLookUpAngle; // 0x11C (284 decimal)
		uint32_t fixIceBoltBlast; // 4-byte boolean | 0x120 (288 decimal) | MMExt info: [MM7+]
		int32_t monSpritesSizeMul; // 0x124 (292 decimal) | MMExt info: Default is 0 - disabled. 0x10000 stands for 1.0.
		uint32_t fixMonsterAttackTypes; // 4-byte boolean | 0x128 (296 decimal) | MMExt info: [MM7+]
		uint32_t fixMonsterSpells; // 4-byte boolean | 0x12C (300 decimal)
		uint32_t fixSouldrinker; // 4-byte boolean | 0x130 (304 decimal)
		int32_t mouseLookPermKey; // 0x134 (308 decimal)
		int32_t lastSoundSample; // 0x138 (312 decimal)
		int32_t waterWalkDamage; // 0x13C (316 decimal) | MMExt info: [MM7+]
		uint32_t fixUnmarkedArtifacts; // 4-byte boolean | 0x140 (320 decimal) | MMExt info: [MM6, MM7]
		uint32_t fixClubsDelay; // 4-byte boolean | 0x144 (324 decimal) | MMExt info: [MM7+]
		uint32_t fixDarkTrainers; // 4-byte boolean | 0x148 (328 decimal) | MMExt info: [MM7]
		uint32_t fixLightBolt; // 4-byte boolean | 0x14C (332 decimal) | MMExt info: [MM7+]
		int32_t armageddonElement; // 0x150 (336 decimal)
		uint32_t fixKelebrim; // 4-byte boolean | 0x154 (340 decimal) | MMExt info: [MM7]
		uint32_t fixBarrels; // 4-byte boolean | 0x158 (344 decimal) | MMExt info: [MM7]
		uint32_t climbBetter; // 4-byte boolean | 0x15C (348 decimal) | MMExt info: [MM7+]
		uint32_t fixWaterWalkManaDrain; // 4-byte boolean | 0x160 (352 decimal)
		uint32_t keepEmptyWands; // 4-byte boolean | 0x164 (356 decimal)
		uint32_t dontSkipSimpleMessage; // 4-byte boolean | 0x168 (360 decimal) | MMExt info: [MM6, MM7]
		uint32_t fixItemDuplicates; // 4-byte boolean | 0x16C (364 decimal)
		uint32_t fixClubsGeneration; // 4-byte boolean | 0x170 (368 decimal) | MMExt info: [MM8]
		uint32_t fixAcidBurst; // 4-byte boolean | 0x174 (372 decimal) | MMExt info: [MM7+]
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



	struct MoveToMap // size: 0x1C
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
		int32_t direction; // 0xC (12 decimal) | MMExt info: 0 - 2047. 0 is East.
		int32_t lookAngle; // 0x10 (16 decimal)
		int32_t speedZ; // 0x14 (20 decimal)
		uint32_t defined; // 4-byte boolean | 0x18 (24 decimal)
	};
	static_assert(sizeof(mm8::MoveToMap) == 0x1C, "Invalid \"mm8::MoveToMap\" structure size");
	static_assert(offsetof(mm8::MoveToMap, y) == 4);
	static_assert(offsetof(mm8::MoveToMap, z) == 8);
	static_assert(offsetof(mm8::MoveToMap, direction) == 12);
	static_assert(offsetof(mm8::MoveToMap, lookAngle) == 16);
	static_assert(offsetof(mm8::MoveToMap, speedZ) == 20);
	static_assert(offsetof(mm8::MoveToMap, defined) == 24);



	struct MouseStruct // size: 0x110
	{
		static inline mm8::ObjectRef* const target = 0;

		SKIP(264);
		int32_t x; // 0x108 (264 decimal)
		int32_t y; // 0x10C (268 decimal)
		int __thiscall removeItem(); // address: 0x467C0A | defaults: (this)
		int __thiscall addItem(/*Item:structs.Item*/); // address: 0x491A27 | defaults: (this)
		int __thiscall setIcon(/*Icon = "MICON1"*/); // address: 0x467C67 | defaults: (this), "MICON1"
		int __thiscall releaseItem(); // address: 0x4209D4 | defaults: (this)
	};
	static_assert(sizeof(mm8::MouseStruct) == 0x110, "Invalid \"mm8::MouseStruct\" structure size");
	static_assert(offsetof(mm8::MouseStruct, x) == 264);
	static_assert(offsetof(mm8::MouseStruct, y) == 268);



	struct MissileSetup // size: 0x1
	{
		bool alwaysShowSprite : 1; // 0x0 (0 decimal) | MMExt info: When there's a special way to display the object, still show the sprite as well
		bool hideSpecialDisplay : 1; // 0x0 (0 decimal) | MMExt info: Don't display the object in a special way
		bool autoCollision : 1; // 0x0 (0 decimal) | MMExt info: When the object hits anything, show an explosion, play explosion sound of the spell and call #MonsterAttacked:events.MonsterAttacked# or #PlayerAttacked:events.PlayerAttacked# appropriately
	};
	static_assert(sizeof(mm8::MissileSetup) == 0x1, "Invalid \"mm8::MissileSetup\" structure size");



	struct FogChances // size: 0x4
	{
		uint8_t thick; // 0x0 (0 decimal)
		uint8_t medium; // 0x1 (1 decimal)
		uint8_t light; // 0x2 (2 decimal)
		SKIP(1);
	};
	static_assert(sizeof(mm8::FogChances) == 0x4, "Invalid \"mm8::FogChances\" structure size");
	static_assert(offsetof(mm8::FogChances, medium) == 1);
	static_assert(offsetof(mm8::FogChances, light) == 2);



	struct HouseMovie // size: 0x10
	{
		char* fileName; // EditPChar | 0x0 (0 decimal)
		uint8_t background; // 0x4 (4 decimal) | MMExt info: EVTPAR* index, used only in MM6
		SKIP(3);
		int32_t NPCPic; // 0x8 (8 decimal)
		uint8_t houseType; // 0xC (12 decimal)
		uint8_t sounds; // 0xD (13 decimal) | MMExt info: 30000 + Sounds*100 is the Id in Sounds.txt
		SKIP(2);
	};
	static_assert(sizeof(mm8::HouseMovie) == 0x10, "Invalid \"mm8::HouseMovie\" structure size");
	static_assert(offsetof(mm8::HouseMovie, background) == 4);
	static_assert(offsetof(mm8::HouseMovie, NPCPic) == 8);
	static_assert(offsetof(mm8::HouseMovie, houseType) == 12);
	static_assert(offsetof(mm8::HouseMovie, sounds) == 13);



	struct EventLine // size: 0xC
	{
		int32_t event; // 0x0 (0 decimal)
		int32_t line; // 0x4 (4 decimal)
		int32_t offset; // 0x8 (8 decimal)
	};
	static_assert(sizeof(mm8::EventLine) == 0xC, "Invalid \"mm8::EventLine\" structure size");
	static_assert(offsetof(mm8::EventLine, line) == 4);
	static_assert(offsetof(mm8::EventLine, offset) == 8);



	struct GameMouse // size: 0xB7CA88
	{
		SKIP(7722864);
		mm8::MouseStruct* mouseStruct; // 0x75D770 (7722864 decimal)
		SKIP(4322032);
		mm8::Item item; // 0xB7CA64 (12044900 decimal)
	};
	static_assert(sizeof(mm8::GameMouse) == 0xB7CA88, "Invalid \"mm8::GameMouse\" structure size");
	static_assert(offsetof(mm8::GameMouse, mouseStruct) == 7722864);
	static_assert(offsetof(mm8::GameMouse, item) == 12044900);



	struct ActionItem // size: 0xC
	{
		int32_t action; // 0x0 (0 decimal)
		int32_t param; // 0x4 (4 decimal)
		int32_t param2; // 0x8 (8 decimal)
	};
	static_assert(sizeof(mm8::ActionItem) == 0xC, "Invalid \"mm8::ActionItem\" structure size");
	static_assert(offsetof(mm8::ActionItem, param) == 4);
	static_assert(offsetof(mm8::ActionItem, param2) == 8);
}

#pragma pack(pop)