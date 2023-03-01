#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct GameStructure // size: 0x60020196
	{
		static inline mm6::GameParty* const party = 0;
		static inline mm6::GameMap* const map = 0;
		static inline mm6::DialogLogic* const dialogLogic = 0;
		static inline mm6::GameClasses* const classes = 0;
		static inline mm6::GameClassKinds* const classKinds = 0;
		static inline mm6::Weather* const weather = 0;

		static char** NPCTopic; // converted to pointer to not break with limits removal scripts
		static uint32_t NPCTopic_size; // size field, set during initialization by getting data from lua
		static char** classNames; // converted to pointer to not break with limits removal scripts
		static uint32_t classNames_size; // size field, set during initialization by getting data from lua
		static uint8_t* titleTrackOffset; // converted to pointer to not break with limits removal scripts
		static uint32_t titleTrackOffset_size; // size field, set during initialization by getting data from lua
		static mm6::MissileSetup* missileSetup; // converted to pointer to not break with limits removal scripts
		static uint32_t* missileSetup_sizePtr; // pointer to size, set during initialization by getting data from lua
		static char** NPCText; // converted to pointer to not break with limits removal scripts
		static uint32_t NPCText_size; // size field, set during initialization by getting data from lua
		static mm6::TravelInfo* transportLocations; // converted to pointer to not break with limits removal scripts
		static uint32_t transportLocations_size; // size field, set during initialization by getting data from lua
		static std::array<int8_t, 3>* transportIndex; // converted to pointer to not break with limits removal scripts
		static uint32_t transportIndex_size; // size field, set during initialization by getting data from lua
		static char** questsTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t questsTxt_size; // size field, set during initialization by getting data from lua
		static mm6::ItemsTxtItem* itemsTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t* itemsTxt_sizePtr; // pointer to size, set during initialization by getting data from lua
		static mm6::EventLine* globalEvtLines; // converted to pointer to not break with limits removal scripts
		static uint32_t* globalEvtLines_sizePtr; // pointer to size, set during initialization by getting data from lua
		static mm6::PatchOptions* patchOptions; // converted to pointer to not break with limits removal scripts
		static int32_t* awardsSort; // converted to pointer to not break with limits removal scripts
		static uint32_t* awardsSort_sizePtr; // pointer to size, set during initialization by getting data from lua
		static mm6::Events2DItem* houses; // converted to pointer to not break with limits removal scripts
		static uint32_t houses_size; // size field, set during initialization by getting data from lua
		static mm6::CustomLods* customLods; // converted to pointer to not break with limits removal scripts
		static mm6::MonstersTxtItem* monstersTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t* monstersTxt_sizePtr; // pointer to size, set during initialization by getting data from lua
		static int16_t* mapDoorSound; // converted to pointer to not break with limits removal scripts
		static uint32_t mapDoorSound_size; // size field, set during initialization by getting data from lua
		static mm6::FogChances* mapFogChances; // converted to pointer to not break with limits removal scripts
		static uint32_t mapFogChances_size; // size field, set during initialization by getting data from lua
		static mm6::MapStatsItem* mapStats; // converted to pointer to not break with limits removal scripts
		static uint32_t* mapStats_sizePtr; // pointer to size, set during initialization by getting data from lua
		static char** autonoteTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t autonoteTxt_size; // size field, set during initialization by getting data from lua
		static mm6::NPC* NPC; // converted to pointer to not break with limits removal scripts
		static uint32_t* NPC_sizePtr; // pointer to size, set during initialization by getting data from lua
		static mm6::NPC* NPCDataTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t NPCDataTxt_size; // size field, set during initialization by getting data from lua
		static mm6::NPCNewsItem* NPCNews; // converted to pointer to not break with limits removal scripts
		static uint32_t NPCNews_size; // size field, set during initialization by getting data from lua
		static std::array<mm6::Item, 12>* shopItems; // converted to pointer to not break with limits removal scripts
		static uint32_t shopItems_size; // size field, set during initialization by getting data from lua
		static std::array<mm6::Item, 12>* shopSpecialItems; // converted to pointer to not break with limits removal scripts
		static uint32_t shopSpecialItems_size; // size field, set during initialization by getting data from lua
		static std::array<std::array<mm6::Item, 12>, 1>* guildItems; // converted to pointer to not break with limits removal scripts
		static uint32_t guildItems_size; // size field, set during initialization by getting data from lua
		static int64_t* shopNextRefill; // converted to pointer to not break with limits removal scripts
		static uint32_t shopNextRefill_size; // size field, set during initialization by getting data from lua
		static mm6::HouseMovie* houseMovies; // converted to pointer to not break with limits removal scripts
		static uint32_t houseMovies_size; // size field, set during initialization by getting data from lua
		static char** transTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t transTxt_size; // size field, set during initialization by getting data from lua

		// uint8_t* randSeed; // real size is 0 | Unknown type
		SKIP(4366905);
		std::array<uint8_t, 1> minMeleeRecoveryTime; // Unknown type
		SKIP(20301);
		char* winMapIndex; // EditConstPChar - unprotect before/protect after edit
		SKIP(135569);
		// uint8_t* baseYear; // real size is 0 | Unknown type
		SKIP(11458);
		std::array<uint8_t, 1> narratorTrack; // Unknown type
		SKIP(20339);
		std::array<uint8_t, 4> newGameMap; // Unknown type
		SKIP(53997);
		std::array<uint8_t, 4> flyCeiling; // Unknown type
		SKIP(125975);
		std::array<uint8_t, 4> maxBirthYear; // Unknown type
		SKIP(142776);
		std::array<uint8_t, 1> titleTrack; // Unknown type
		SKIP(87517);
		std::array<std::array<int16_t, 48>, 5> autonotesByCategory;
		SKIP(1804);
		std::array<int16_t, 6> townPortalX;
		std::array<int16_t, 6> townPortalY;
		std::array<int16_t, 6> townPortalWidth;
		std::array<int16_t, 6> townPortalHeight;
		SKIP(708);
		int32_t currentScreen;
		SKIP(816);
		std::array<int8_t, 60> monsterClassInfoY;
		SKIP(2704);
		std::array<std::array<uint8_t, 4>, 99> spellObjId; // MMExt: 1..99, here 0..98 | Unknown type
		SKIP(12);
		std::array<mm6::SpellInfo, 100> spells;
		SKIP(208);
		std::array<int32_t, 6> specialEnterX; // MMExt: 1..6, here 0..5
		std::array<int32_t, 6> specialEnterY; // MMExt: 1..6, here 0..5
		std::array<int32_t, 6> specialEnterZ; // MMExt: 1..6, here 0..5
		std::array<int32_t, 6> specialEnterDirection; // MMExt: 1..6, here 0..5
		SKIP(5256);
		std::array<uint8_t, 20> equipStat2ItemSlot;
		std::array<bool, 180> monsterSex; // MMExt: 1..180, here 0..179
		SKIP(9776);
		std::array<mm6::TownPortalTownInfo, 6> townPortalInfo;
		std::array<char*, 12> playerFaces; // EditConstPChar - unprotect before/protect after edit
		SKIP(156);
		std::array<std::array<uint8_t, 12>, 44> standardPlayerSoundsCount; // MMExt: 1..44, here 0..43
		SKIP(4);
		std::array<mm6::FaceAnimationInfo, 103> standardFaceAnimations;
		SKIP(296);
		std::array<int16_t, 13> skillRecoveryTimes;
		SKIP(376);
		std::array<int16_t, 99> spellSounds; // MMExt: 1..99, here 0..98
		SKIP(5048);
		std::array<char*, 19> shopBackgroundByType; // EditConstPChar - unprotect before/protect after edit
		SKIP(100);
		std::array<int32_t, 17> guildJoinCost;
		SKIP(44);
		std::array<int16_t, 10> trainingLevels; // MMExt: 79..88, here 0..9
		std::array<int32_t, 34> guildAwards; // MMExt: 119..152, here 0..33
		SKIP(1216);
		std::array<mm6::ShopItemKind, 14> shopWeaponKinds; // MMExt: 1..14, here 0..13
		std::array<std::array<mm6::ShopItemKind, 2>, 14> shopArmorKinds; // MMExt: 15..28, here 0..13 | MMExt: 1..2, here 0..1
		std::array<int16_t, 13> shopMagicLevels; // MMExt: 29..41, here 0..12
		SKIP(2);
		std::array<mm6::GeneralStoreItemKind, 6> generalStoreItemKinds; // MMExt: 42..47, here 0..5
		SKIP(8);
		std::array<mm6::ShopItemKind, 14> shopWeaponKindsSpecial; // MMExt: 1..14, here 0..13
		std::array<std::array<mm6::ShopItemKind, 2>, 14> shopArmorKindsSpecial; // MMExt: 15..28, here 0..13 | MMExt: 1..2, here 0..1
		std::array<int16_t, 13> shopMagicLevelsSpecial; // MMExt: 29..41, here 0..12
		SKIP(2);
		std::array<mm6::GeneralStoreItemKind, 6> generalStoreItemKindsSpecial; // MMExt: 42..47, here 0..5
		SKIP(164);
		std::array<int16_t, 22> guildSpellLevels; // MMExt: 119..140, here 0..21
		SKIP(9164);
		std::array<int32_t, 4> turnBasedDelays;
		SKIP(4412);
		int32_t turnBasedPhase;
		SKIP(10528);
		std::array<int32_t, 480> scanlineOffset;
		SKIP(2104);
		mm6::BitmapsLod iconsLod;
		SKIP(356);
		int32_t currentCharScreen;
		SKIP(2416);
		std::array<char*, 7> statsNames; // EditPChar
		SKIP(4);
		uint32_t ctrlPressed; // 4-byte boolean
		SKIP(20);
		mm6::Dlg* currentNPCDialog;
		SKIP(36);
		std::array<uint8_t, 4> currentPlayer; // Unknown type
		bool rightButtonPressed;
		SKIP(151);
		uint32_t paused; // 4-byte boolean
		SKIP(20);
		int32_t timeDelta;
		SKIP(12);
		uint32_t paused2; // 4-byte boolean
		SKIP(20);
		int32_t timeDelta2;
		SKIP(3456);
		uint32_t actions_size;
		std::array<mm6::ActionItem, 40> actions; // size field offset is 0x4D5F48
		SKIP(356220);
		mm6::ProgressBar progressBar;
		SKIP(44);
		uint32_t loadingScreen; // 4-byte boolean
		SKIP(436);
		uint32_t needRedraw; // 4-byte boolean
		SKIP(27668);
		uint32_t mapEvtLines_size;
		int32_t dialogNPC;
		SKIP(36004);
		int32_t houseNPCSlotsCount;
		SKIP(66748);
		std::array<int32_t, 6> houseNPCs; // MMExt: 1..6, here 0..5
		SKIP(8);
		int32_t NPCCommand;
		SKIP(19676);
		mm6::MoveToMap moveToMap;
		SKIP(600);
		int32_t houseNPCSlot;
		SKIP(2004);
		std::array<char, 2000> streetMessage; // fixed size string, requires null terminator
		SKIP(12);
		int32_t houseOwnerPic;
		SKIP(12);
		std::array<mm6::EventLine, 3000> mapEvtLines; // size field offset is 0x533EB4
		SKIP(12);
		std::array<char, 200> statusMessage; // fixed size string, requires null terminator
		std::array<char, 200> mouseOverStatusMessage; // fixed size string, requires null terminator
		int32_t statusDisappearTime;
		SKIP(12);
		int32_t houseExitMap;
		SKIP(12);
		int32_t lucida_fnt;
		int32_t smallnum_fnt;
		int32_t book_fnt;
		int32_t spell_fnt;
		int32_t arrus_fnt;
		int32_t create_fnt;
		int32_t comic_fnt;
		int32_t autonote_fnt;
		int32_t book2_fnt;
		SKIP(4);
		int32_t cchar_fnt;
		SKIP(4096);
		std::array<char, 2000> textBuffer; // fixed size string, requires null terminator
		std::array<char, 2000> textBuffer2; // fixed size string, requires null terminator
		SKIP(8);
		mm6::SFT SFTBin;
		uint32_t TFTBin_size;
		mm6::TFTItem* TFTBin; // size field offset is 0x55DDA0
		SKIP(35124);
		std::array<mm6::StdItemsTxtItem, 14> stdItemsTxt;
		std::array<mm6::SpcItemsTxtItem, 59> spcItemsTxt;
		SKIP(14616);
		std::array<std::array<uint8_t, 29>, 29> potionTxt; // MMExt: 160..188, here 0..28 | MMExt: 160..188, here 0..28
		SKIP(263);
		std::array<mm6::SpellsTxtItem, 100> spellsTxt;
		std::array<char*, 18> classDescriptions; // EditPChar
		SKIP(100);
		std::array<char*, 31> skillDesNormal; // EditPChar
		SKIP(72);
		std::array<char*, 596> globalTxt; // EditPChar
		SKIP(12540);
		std::array<char*, 7> statsDescriptions; // EditPChar
		SKIP(4);
		std::array<char*, 31> skillDesExpert; // EditPChar
		std::array<char*, 31> skillDesMaster; // EditPChar
		std::array<char*, 31> skillDescriptions; // EditPChar
		SKIP(274144);
		uint32_t chestBin_size;
		mm6::DChestItem* chestBin; // size field offset is 0x5B22F0
		SKIP(84208);
		uint32_t overlayBin_size;
		mm6::OverlayItem* overlayBin; // size field offset is 0x5C6BE8
		SKIP(112008);
		uint32_t monListBin_size;
		mm6::MonListItem* monListBin; // MMExt: 1..0, here 0..-1 | size field offset is 0x5E2178
		SKIP(8);
		uint32_t decListBin_size;
		mm6::DecListItem* decListBin; // size field offset is 0x5E2188
		SKIP(85088);
		uint32_t objListBin_size;
		mm6::ObjListItem* objListBin; // size field offset is 0x5F6DF0
		SKIP(20);
		std::array<int32_t, 12> keyCodes;
		std::array<int32_t, 12> keyTypes;
		SKIP(4784);
		int32_t mainMenuCode;
		SKIP(99288);
		mm6::Lod gamesLod;
		SKIP(12);
		uint32_t tileBin_size;
		mm6::TileItem* tileBin; // size field offset is 0x610740
		SKIP(36);
		uint32_t windowHandle;
		SKIP(115);
		int32_t soundVolume;
		SKIP(73);
		mm6::Lod saveGameLod;
		SKIP(76);
		mm6::BitmapsLod bitmapsLod;
		SKIP(40);
		union
		{
			int32_t exitLevelCode;
			int32_t exitMapAction;
		};
		SKIP(4172);
		mm6::SpritesLod spritesLod;
		SKIP(44);
		int32_t outdoorViewMul;
		int32_t outdoorViewDiv;
		SKIP(510484);
		union
		{
			mm6::GameMouse mouse;
			struct
			{
				SKIP(9624);
				std::array<char*, 87> scrollTxt; // MMExt: 500..586, here 0..86 | EditPChar
				SKIP(2052);
				std::array<char*, 88> awardsTxt; // EditPChar
				SKIP(48000);
				std::array<std::array<char*, 2>, 540> NPCNames; // EditPChar
				std::array<mm6::NPCProfTxtItem, 78> NPCProfTxt;
				std::array<mm6::NPC, 100> streetNPC; // size field offset is 0x6BA530
				SKIP(6352);
				uint32_t streetNPC_size;
				SKIP(12);
				std::array<int32_t, 2> NPCNamesCount;
				SKIP(32);
				std::array<int16_t, 96> NPCNewsCountByMap;
				SKIP(564);
				std::array<char*, 78> NPCProfNames; // EditPChar
				SKIP(12);
				std::array<std::array<char*, 6>, 4> merchantTxt; // EditPChar
				SKIP(2417416);
				int64_t time;
				int32_t year;
				int32_t month;
				int32_t weekOfMonth;
				int32_t dayOfMonth;
				int32_t hour;
				int32_t minute;
				int32_t second;
				SKIP(260);
				uint32_t turnBased; // 4-byte boolean
			};
		};
		bool needRender : 1;
		SKIP(467);
		std::array<int64_t, 22> guildNextRefill; // MMExt: 119..140, here 0..21
		SKIP(40572);
		int32_t armageddonTimeLeft;
		int32_t armageddonSkill;
		SKIP(181016);
		uint32_t IFTBin_size;
		mm6::IFTItem* IFTBin; // size field offset is 0x944C58
		SKIP(180088);
		uint32_t PFTBin_size;
		mm6::PFTItem* PFTBin; // size field offset is 0x970BD8
		struct // size: 0xC, MMExt union
		{
			int64_t delay;
			int16_t animation;
			int16_t playerIndex;
		} delayedFaceAnimation;
		static_assert(sizeof(delayedFaceAnimation) == 0xC, "Invalid \"delayedFaceAnimation\" structure size");
		SKIP(144);
		std::array<char*, 31> skillNames; // EditPChar
		SKIP(880);
		union
		{
			mm6::GameScreen screen;
			struct
			{
				SKIP(262184);
				std::array<std::array<mm6::ObjectRef, 640>, 480>* objectByPixel;
				SKIP(32);
				uint32_t windowed;
			};
		};
		SKIP(124020);
		int32_t redbookHandle;
		int32_t MSSHandle;
		SKIP(344);
		uint32_t soundsBin_size;
		mm6::SoundsItem* soundsBin; // size field offset is 0x9CF700
		SKIP(58984);
		int32_t houseAllowAction;
		SKIP(12);
		int32_t housePicType;
		SKIP(4);
		int32_t houseActionInfo;
		int32_t houseScreen;
		SKIP(8);
		int32_t houseTeachMastery;
		int32_t houseCost;
		SKIP(4);
		std::array<int32_t, 12> guildItemIconPtr;
		SKIP(40);
		int32_t houseItemsCount;
		SKIP(4);
		char* NPCMessage; // EditPChar
		SKIP(1320);
		int32_t movieKind;
		SKIP(12);
		uint32_t isMovieLooped; // 4-byte boolean
		SKIP(32);
		int32_t smackVideo;
		SKIP(1600396846);
	};
	static_assert(sizeof(mm6::GameStructure) == 0x60020196, "Invalid \"mm6::GameStructure\" structure size");
	static_assert(offsetof(mm6::GameStructure, minMeleeRecoveryTime) == 4366905);
	static_assert(offsetof(mm6::GameStructure, winMapIndex) == 4387207);
	static_assert(offsetof(mm6::GameStructure, narratorTrack) == 4534238);
	static_assert(offsetof(mm6::GameStructure, newGameMap) == 4554578);
	static_assert(offsetof(mm6::GameStructure, flyCeiling) == 4608579);
	static_assert(offsetof(mm6::GameStructure, maxBirthYear) == 4734558);
	static_assert(offsetof(mm6::GameStructure, titleTrack) == 4877338);
	static_assert(offsetof(mm6::GameStructure, autonotesByCategory) == 4964856);
	static_assert(offsetof(mm6::GameStructure, townPortalX) == 4967140);
	static_assert(offsetof(mm6::GameStructure, townPortalY) == 4967152);
	static_assert(offsetof(mm6::GameStructure, townPortalWidth) == 4967164);
	static_assert(offsetof(mm6::GameStructure, townPortalHeight) == 4967176);
	static_assert(offsetof(mm6::GameStructure, currentScreen) == 4967896);
	static_assert(offsetof(mm6::GameStructure, monsterClassInfoY) == 4968716);
	static_assert(offsetof(mm6::GameStructure, spellObjId) == 4971480);
	static_assert(offsetof(mm6::GameStructure, spells) == 4971888);
	static_assert(offsetof(mm6::GameStructure, specialEnterX) == 4973496);
	static_assert(offsetof(mm6::GameStructure, specialEnterY) == 4973520);
	static_assert(offsetof(mm6::GameStructure, specialEnterZ) == 4973544);
	static_assert(offsetof(mm6::GameStructure, specialEnterDirection) == 4973568);
	static_assert(offsetof(mm6::GameStructure, equipStat2ItemSlot) == 4978848);
	static_assert(offsetof(mm6::GameStructure, monsterSex) == 4978868);
	static_assert(offsetof(mm6::GameStructure, townPortalInfo) == 4988824);
	static_assert(offsetof(mm6::GameStructure, playerFaces) == 4988944);
	static_assert(offsetof(mm6::GameStructure, standardPlayerSoundsCount) == 4989148);
	static_assert(offsetof(mm6::GameStructure, standardFaceAnimations) == 4989680);
	static_assert(offsetof(mm6::GameStructure, skillRecoveryTimes) == 4990800);
	static_assert(offsetof(mm6::GameStructure, spellSounds) == 4991202);
	static_assert(offsetof(mm6::GameStructure, shopBackgroundByType) == 4996448);
	static_assert(offsetof(mm6::GameStructure, guildJoinCost) == 4996624);
	static_assert(offsetof(mm6::GameStructure, trainingLevels) == 4996736);
	static_assert(offsetof(mm6::GameStructure, guildAwards) == 4996756);
	static_assert(offsetof(mm6::GameStructure, shopWeaponKinds) == 4998108);
	static_assert(offsetof(mm6::GameStructure, shopArmorKinds) == 4998248);
	static_assert(offsetof(mm6::GameStructure, shopMagicLevels) == 4998528);
	static_assert(offsetof(mm6::GameStructure, generalStoreItemKinds) == 4998556);
	static_assert(offsetof(mm6::GameStructure, shopWeaponKindsSpecial) == 4998648);
	static_assert(offsetof(mm6::GameStructure, shopArmorKindsSpecial) == 4998788);
	static_assert(offsetof(mm6::GameStructure, shopMagicLevelsSpecial) == 4999068);
	static_assert(offsetof(mm6::GameStructure, generalStoreItemKindsSpecial) == 4999096);
	static_assert(offsetof(mm6::GameStructure, guildSpellLevels) == 4999344);
	static_assert(offsetof(mm6::GameStructure, turnBasedDelays) == 5008552);
	static_assert(offsetof(mm6::GameStructure, turnBasedPhase) == 5012980);
	static_assert(offsetof(mm6::GameStructure, scanlineOffset) == 5023512);
	static_assert(offsetof(mm6::GameStructure, iconsLod) == 5027536);
	static_assert(offsetof(mm6::GameStructure, currentCharScreen) == 5064468);
	static_assert(offsetof(mm6::GameStructure, statsNames) == 5066888);
	static_assert(offsetof(mm6::GameStructure, ctrlPressed) == 5066920);
	static_assert(offsetof(mm6::GameStructure, currentNPCDialog) == 5066944);
	static_assert(offsetof(mm6::GameStructure, currentPlayer) == 5066984);
	static_assert(offsetof(mm6::GameStructure, rightButtonPressed) == 5066988);
	static_assert(offsetof(mm6::GameStructure, paused) == 5067140);
	static_assert(offsetof(mm6::GameStructure, timeDelta) == 5067164);
	static_assert(offsetof(mm6::GameStructure, paused2) == 5067180);
	static_assert(offsetof(mm6::GameStructure, timeDelta2) == 5067204);
	static_assert(offsetof(mm6::GameStructure, actions_size) == 5070664);
	static_assert(offsetof(mm6::GameStructure, actions) == 5070668);
	static_assert(offsetof(mm6::GameStructure, progressBar) == 5427368);
	static_assert(offsetof(mm6::GameStructure, loadingScreen) == 5427428);
	static_assert(offsetof(mm6::GameStructure, needRedraw) == 5427868);
	static_assert(offsetof(mm6::GameStructure, mapEvtLines_size) == 5455540);
	static_assert(offsetof(mm6::GameStructure, dialogNPC) == 5455544);
	static_assert(offsetof(mm6::GameStructure, houseNPCSlotsCount) == 5491552);
	static_assert(offsetof(mm6::GameStructure, houseNPCs) == 5558304);
	static_assert(offsetof(mm6::GameStructure, NPCCommand) == 5558336);
	static_assert(offsetof(mm6::GameStructure, moveToMap) == 5578016);
	static_assert(offsetof(mm6::GameStructure, houseNPCSlot) == 5578644);
	static_assert(offsetof(mm6::GameStructure, streetMessage) == 5580652);
	static_assert(offsetof(mm6::GameStructure, houseOwnerPic) == 5582664);
	static_assert(offsetof(mm6::GameStructure, mapEvtLines) == 5582680);
	static_assert(offsetof(mm6::GameStructure, statusMessage) == 5618692);
	static_assert(offsetof(mm6::GameStructure, mouseOverStatusMessage) == 5618892);
	static_assert(offsetof(mm6::GameStructure, statusDisappearTime) == 5619092);
	static_assert(offsetof(mm6::GameStructure, houseExitMap) == 5619108);
	static_assert(offsetof(mm6::GameStructure, lucida_fnt) == 5619124);
	static_assert(offsetof(mm6::GameStructure, smallnum_fnt) == 5619128);
	static_assert(offsetof(mm6::GameStructure, book_fnt) == 5619132);
	static_assert(offsetof(mm6::GameStructure, spell_fnt) == 5619136);
	static_assert(offsetof(mm6::GameStructure, arrus_fnt) == 5619140);
	static_assert(offsetof(mm6::GameStructure, create_fnt) == 5619144);
	static_assert(offsetof(mm6::GameStructure, comic_fnt) == 5619148);
	static_assert(offsetof(mm6::GameStructure, autonote_fnt) == 5619152);
	static_assert(offsetof(mm6::GameStructure, book2_fnt) == 5619156);
	static_assert(offsetof(mm6::GameStructure, cchar_fnt) == 5619164);
	static_assert(offsetof(mm6::GameStructure, textBuffer) == 5623264);
	static_assert(offsetof(mm6::GameStructure, textBuffer2) == 5625264);
	static_assert(offsetof(mm6::GameStructure, SFTBin) == 5627272);
	static_assert(offsetof(mm6::GameStructure, TFTBin_size) == 5627296);
	static_assert(offsetof(mm6::GameStructure, TFTBin) == 5627300);
	static_assert(offsetof(mm6::GameStructure, stdItemsTxt) == 5662428);
	static_assert(offsetof(mm6::GameStructure, spcItemsTxt) == 5662708);
	static_assert(offsetof(mm6::GameStructure, potionTxt) == 5678976);
	static_assert(offsetof(mm6::GameStructure, spellsTxt) == 5680080);
	static_assert(offsetof(mm6::GameStructure, classDescriptions) == 5682880);
	static_assert(offsetof(mm6::GameStructure, skillDesNormal) == 5683052);
	static_assert(offsetof(mm6::GameStructure, globalTxt) == 5683248);
	static_assert(offsetof(mm6::GameStructure, statsDescriptions) == 5698172);
	static_assert(offsetof(mm6::GameStructure, skillDesExpert) == 5698204);
	static_assert(offsetof(mm6::GameStructure, skillDesMaster) == 5698328);
	static_assert(offsetof(mm6::GameStructure, skillDescriptions) == 5698452);
	static_assert(offsetof(mm6::GameStructure, chestBin_size) == 5972720);
	static_assert(offsetof(mm6::GameStructure, chestBin) == 5972724);
	static_assert(offsetof(mm6::GameStructure, overlayBin_size) == 6056936);
	static_assert(offsetof(mm6::GameStructure, overlayBin) == 6056940);
	static_assert(offsetof(mm6::GameStructure, monListBin_size) == 6168952);
	static_assert(offsetof(mm6::GameStructure, monListBin) == 6168956);
	static_assert(offsetof(mm6::GameStructure, decListBin_size) == 6168968);
	static_assert(offsetof(mm6::GameStructure, decListBin) == 6168972);
	static_assert(offsetof(mm6::GameStructure, objListBin_size) == 6254064);
	static_assert(offsetof(mm6::GameStructure, objListBin) == 6254068);
	static_assert(offsetof(mm6::GameStructure, keyCodes) == 6254092);
	static_assert(offsetof(mm6::GameStructure, keyTypes) == 6254140);
	static_assert(offsetof(mm6::GameStructure, mainMenuCode) == 6258972);
	static_assert(offsetof(mm6::GameStructure, gamesLod) == 6358264);
	static_assert(offsetof(mm6::GameStructure, tileBin_size) == 6358848);
	static_assert(offsetof(mm6::GameStructure, tileBin) == 6358852);
	static_assert(offsetof(mm6::GameStructure, windowHandle) == 6358892);
	static_assert(offsetof(mm6::GameStructure, soundVolume) == 6359011);
	static_assert(offsetof(mm6::GameStructure, saveGameLod) == 6359088);
	static_assert(offsetof(mm6::GameStructure, bitmapsLod) == 6359736);
	static_assert(offsetof(mm6::GameStructure, exitLevelCode) == 6396352);
	static_assert(offsetof(mm6::GameStructure, exitMapAction) == 6396352);
	static_assert(offsetof(mm6::GameStructure, spritesLod) == 6400528);
	static_assert(offsetof(mm6::GameStructure, outdoorViewMul) == 6461172);
	static_assert(offsetof(mm6::GameStructure, outdoorViewDiv) == 6461176);
	static_assert(offsetof(mm6::GameStructure, mouse) == 6971664);
	static_assert(offsetof(mm6::GameStructure, scrollTxt) == 6981288);
	static_assert(offsetof(mm6::GameStructure, awardsTxt) == 6983688);
	static_assert(offsetof(mm6::GameStructure, NPCNames) == 7032040);
	static_assert(offsetof(mm6::GameStructure, NPCProfTxt) == 7036360);
	static_assert(offsetof(mm6::GameStructure, streetNPC) == 7042288);
	static_assert(offsetof(mm6::GameStructure, streetNPC_size) == 7054640);
	static_assert(offsetof(mm6::GameStructure, NPCNamesCount) == 7054656);
	static_assert(offsetof(mm6::GameStructure, NPCNewsCountByMap) == 7054696);
	static_assert(offsetof(mm6::GameStructure, NPCProfNames) == 7055452);
	static_assert(offsetof(mm6::GameStructure, merchantTxt) == 7055776);
	static_assert(offsetof(mm6::GameStructure, time) == 9473288);
	static_assert(offsetof(mm6::GameStructure, year) == 9473296);
	static_assert(offsetof(mm6::GameStructure, month) == 9473300);
	static_assert(offsetof(mm6::GameStructure, weekOfMonth) == 9473304);
	static_assert(offsetof(mm6::GameStructure, dayOfMonth) == 9473308);
	static_assert(offsetof(mm6::GameStructure, hour) == 9473312);
	static_assert(offsetof(mm6::GameStructure, minute) == 9473316);
	static_assert(offsetof(mm6::GameStructure, second) == 9473320);
	static_assert(offsetof(mm6::GameStructure, turnBased) == 9473584);
	static_assert(offsetof(mm6::GameStructure, guildNextRefill) == 9497100);
	static_assert(offsetof(mm6::GameStructure, armageddonTimeLeft) == 9537848);
	static_assert(offsetof(mm6::GameStructure, armageddonSkill) == 9537852);
	static_assert(offsetof(mm6::GameStructure, IFTBin_size) == 9718872);
	static_assert(offsetof(mm6::GameStructure, IFTBin) == 9718876);
	static_assert(offsetof(mm6::GameStructure, PFTBin_size) == 9898968);
	static_assert(offsetof(mm6::GameStructure, PFTBin) == 9898972);
	static_assert(offsetof(mm6::GameStructure, delayedFaceAnimation) == 9898976);
	static_assert(offsetof(mm6::GameStructure, skillNames) == 9899132);
	static_assert(offsetof(mm6::GameStructure, screen) == 9900136);
	static_assert(offsetof(mm6::GameStructure, objectByPixel) == 10162320);
	static_assert(offsetof(mm6::GameStructure, windowed) == 10162356);
	static_assert(offsetof(mm6::GameStructure, redbookHandle) == 10286496);
	static_assert(offsetof(mm6::GameStructure, MSSHandle) == 10286500);
	static_assert(offsetof(mm6::GameStructure, soundsBin_size) == 10286848);
	static_assert(offsetof(mm6::GameStructure, soundsBin) == 10286852);
	static_assert(offsetof(mm6::GameStructure, houseAllowAction) == 10345840);
	static_assert(offsetof(mm6::GameStructure, housePicType) == 10345856);
	static_assert(offsetof(mm6::GameStructure, houseActionInfo) == 10345864);
	static_assert(offsetof(mm6::GameStructure, houseScreen) == 10345868);
	static_assert(offsetof(mm6::GameStructure, houseTeachMastery) == 10345880);
	static_assert(offsetof(mm6::GameStructure, houseCost) == 10345884);
	static_assert(offsetof(mm6::GameStructure, guildItemIconPtr) == 10345892);
	static_assert(offsetof(mm6::GameStructure, houseItemsCount) == 10345980);
	static_assert(offsetof(mm6::GameStructure, NPCMessage) == 10345988);
	static_assert(offsetof(mm6::GameStructure, movieKind) == 10347312);
	static_assert(offsetof(mm6::GameStructure, isMovieLooped) == 10347328);
	static_assert(offsetof(mm6::GameStructure, smackVideo) == 10347364);
}
namespace mm7
{
	struct GameStructure // size: 0x600201BC
	{
		static inline mm7::Arcomage* const arcomage = 0;
		static inline mm7::GameMouse* const mouse = 0;
		static inline mm7::GameRaces* const races = 0;
		static inline mm7::GameClasses* const classes = 0;
		static inline mm7::GameClassKinds* const classKinds = 0;
		static inline mm7::Weather* const weather = 0;
		static inline mm7::GameMap* const map = 0;
		static inline mm7::GameParty* const party = 0;
		static inline mm7::DialogLogic* const dialogLogic = 0;

		static mm7::CustomLods* customLods; // converted to pointer to not break with limits removal scripts
		static std::array<mm7::Item, 12>* shopItems; // converted to pointer to not break with limits removal scripts
		static uint32_t shopItems_size; // size field, set during initialization by getting data from lua
		static std::array<mm7::Item, 12>* shopSpecialItems; // converted to pointer to not break with limits removal scripts
		static uint32_t shopSpecialItems_size; // size field, set during initialization by getting data from lua
		static std::array<std::array<mm7::Item, 12>, 1>* guildItems; // converted to pointer to not break with limits removal scripts
		static uint32_t guildItems_size; // size field, set during initialization by getting data from lua
		static int64_t* shopNextRefill; // converted to pointer to not break with limits removal scripts
		static uint32_t shopNextRefill_size; // size field, set during initialization by getting data from lua
		static int64_t* shopTheftExpireTime; // converted to pointer to not break with limits removal scripts
		static uint32_t shopTheftExpireTime_size; // size field, set during initialization by getting data from lua
		static mm7::HouseMovie* houseMovies; // converted to pointer to not break with limits removal scripts
		static uint32_t houseMovies_size; // size field, set during initialization by getting data from lua
		static uint8_t* titleTrackOffset; // converted to pointer to not break with limits removal scripts
		static uint32_t titleTrackOffset_size; // size field, set during initialization by getting data from lua
		static mm7::MissileSetup* missileSetup; // converted to pointer to not break with limits removal scripts
		static uint32_t* missileSetup_sizePtr; // pointer to size, set during initialization by getting data from lua
		static int32_t* autonoteCategory; // converted to pointer to not break with limits removal scripts
		static uint32_t autonoteCategory_size; // size field, set during initialization by getting data from lua
		static mm7::NPC* NPC; // converted to pointer to not break with limits removal scripts
		static uint32_t* NPC_sizePtr; // pointer to size, set during initialization by getting data from lua
		static int16_t* NPCGroup; // converted to pointer to not break with limits removal scripts
		static uint32_t NPCGroup_size; // size field, set during initialization by getting data from lua
		static mm7::MonsterKind* monsterKinds; // converted to pointer to not break with limits removal scripts
		static uint32_t* monsterKinds_sizePtr; // pointer to size, set during initialization by getting data from lua
		static char** NPCText; // converted to pointer to not break with limits removal scripts
		static uint32_t NPCText_size; // size field, set during initialization by getting data from lua
		static mm7::TravelInfo* transportLocations; // converted to pointer to not break with limits removal scripts
		static uint32_t transportLocations_size; // size field, set during initialization by getting data from lua
		static std::array<int8_t, 4>* transportIndex; // converted to pointer to not break with limits removal scripts
		static uint32_t transportIndex_size; // size field, set during initialization by getting data from lua
		static char** questsTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t questsTxt_size; // size field, set during initialization by getting data from lua
		static mm7::ItemsTxtItem* itemsTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t* itemsTxt_sizePtr; // pointer to size, set during initialization by getting data from lua
		static char** autonoteTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t autonoteTxt_size; // size field, set during initialization by getting data from lua
		static mm7::NPC* NPCDataTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t NPCDataTxt_size; // size field, set during initialization by getting data from lua
		static char** NPCTopic; // converted to pointer to not break with limits removal scripts
		static uint32_t NPCTopic_size; // size field, set during initialization by getting data from lua
		static mm7::MapStatsItem* mapStats; // converted to pointer to not break with limits removal scripts
		static uint32_t* mapStats_sizePtr; // pointer to size, set during initialization by getting data from lua
		static mm7::EventLine* globalEvtLines; // converted to pointer to not break with limits removal scripts
		static uint32_t* globalEvtLines_sizePtr; // pointer to size, set during initialization by getting data from lua
		static std::array<uint8_t, 89>* hostileTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t hostileTxt_size; // size field, set during initialization by getting data from lua
		static int32_t* awardsSort; // converted to pointer to not break with limits removal scripts
		static uint32_t awardsSort_size; // size field, set during initialization by getting data from lua
		static char** NPCNews; // converted to pointer to not break with limits removal scripts
		static uint32_t NPCNews_size; // size field, set during initialization by getting data from lua
		static std::array<char*, 2>* NPCGreet; // converted to pointer to not break with limits removal scripts
		static uint32_t NPCGreet_size; // size field, set during initialization by getting data from lua
		static char** transTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t transTxt_size; // size field, set during initialization by getting data from lua
		static mm7::Events2DItem* houses; // converted to pointer to not break with limits removal scripts
		static uint32_t houses_size; // size field, set during initialization by getting data from lua
		static char** placeMonTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t* placeMonTxt_sizePtr; // pointer to size, set during initialization by getting data from lua
		static mm7::MonstersTxtItem* monstersTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t* monstersTxt_sizePtr; // pointer to size, set during initialization by getting data from lua
		static char** classNames; // converted to pointer to not break with limits removal scripts
		static uint32_t classNames_size; // size field, set during initialization by getting data from lua
		static mm7::PatchOptions* patchOptions; // converted to pointer to not break with limits removal scripts
		static int16_t* mapDoorSound; // converted to pointer to not break with limits removal scripts
		static uint32_t mapDoorSound_size; // size field, set during initialization by getting data from lua
		static mm7::FogChances* mapFogChances; // converted to pointer to not break with limits removal scripts
		static uint32_t mapFogChances_size; // size field, set during initialization by getting data from lua

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
		SKIP(1408);
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
		SKIP(13172);
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
		struct __awardsTxt
		{
			char* value;
			SKIP(4);
		};
		std::array<__awardsTxt, 105> awardsTxt; // EditPChar
		SKIP(76160);
		std::array<std::array<char*, 2>, 540> NPCNames; // EditPChar
		std::array<mm7::NPCProfTxtItem, 59> NPCProfTxt;
		std::array<mm7::NPC, 100> streetNPC; // size field offset is 0x73C010
		SKIP(8988);
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
		SKIP(59843);
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
		SKIP(1594443668);
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
	static_assert(offsetof(mm7::GameStructure, NPCNames) == 7563720);
	static_assert(offsetof(mm7::GameStructure, NPCProfTxt) == 7568040);
	static_assert(offsetof(mm7::GameStructure, streetNPC) == 7569220);
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
}
namespace mm8
{
	struct GameStructure // size: 0x6007A8CC
	{
		static inline mm8::Arcomage* const arcomage = 0;
		static inline mm8::GameParty* const party = 0;
		static inline mm8::DialogLogic* const dialogLogic = 0;
		static inline mm8::GameMap* const map = 0;
		static inline mm8::CharacterVoices* const characterVoices = 0;
		static inline mm8::GameClasses* const classes = 0;
		static inline mm8::ArmorPicsCoords* const armorPicsCoords = 0;
		static inline mm8::GameClassKinds* const classKinds = 0;
		static inline mm8::GameMouse* const mouse = 0;
		static inline mm8::Weather* const weather = 0;
		static inline mm8::HouseRules* const houseRules = 0;

		static int16_t* NPCGroup; // converted to pointer to not break with limits removal scripts
		static uint32_t NPCGroup_size; // size field, set during initialization by getting data from lua
		static char** transTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t transTxt_size; // size field, set during initialization by getting data from lua
		static mm8::MonsterKind* monsterKinds; // converted to pointer to not break with limits removal scripts
		static uint32_t* monsterKinds_sizePtr; // pointer to size, set during initialization by getting data from lua
		static int64_t* shopTheftExpireTime; // converted to pointer to not break with limits removal scripts
		static uint32_t shopTheftExpireTime_size; // size field, set during initialization by getting data from lua
		static std::array<std::array<mm8::Item, 12>, 12>* guildItems; // converted to pointer to not break with limits removal scripts
		static uint32_t guildItems_size; // size field, set during initialization by getting data from lua
		static std::array<mm8::Item, 12>* shopSpecialItems; // converted to pointer to not break with limits removal scripts
		static uint32_t shopSpecialItems_size; // size field, set during initialization by getting data from lua
		static uint8_t* titleTrackOffset; // converted to pointer to not break with limits removal scripts
		static uint32_t titleTrackOffset_size; // size field, set during initialization by getting data from lua
		static char** placeMonTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t* placeMonTxt_sizePtr; // pointer to size, set during initialization by getting data from lua
		static mm8::HouseMovie* houseMovies; // converted to pointer to not break with limits removal scripts
		static uint32_t houseMovies_size; // size field, set during initialization by getting data from lua
		static mm8::CharacterPortrait* characterPortraits; // converted to pointer to not break with limits removal scripts
		static uint32_t characterPortraits_size; // size field, set during initialization by getting data from lua
		static mm8::NPC* NPC; // converted to pointer to not break with limits removal scripts
		static uint32_t NPC_size; // size field, set during initialization by getting data from lua
		static mm8::FogChances* mapFogChances; // converted to pointer to not break with limits removal scripts
		static uint32_t mapFogChances_size; // size field, set during initialization by getting data from lua
		static char** autonoteTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t autonoteTxt_size; // size field, set during initialization by getting data from lua
		static mm8::MapStatsItem* mapStats; // converted to pointer to not break with limits removal scripts
		static uint32_t* mapStats_sizePtr; // pointer to size, set during initialization by getting data from lua
		static mm8::ReagentSettings* reagentSettings; // converted to pointer to not break with limits removal scripts
		static uint32_t reagentSettings_size; // size field, set during initialization by getting data from lua
		static std::array<uint16_t, 70>* mixPotions; // converted to pointer to not break with limits removal scripts
		static uint32_t mixPotions_size; // size field, set during initialization by getting data from lua
		static int64_t* guildNextRefill2; // converted to pointer to not break with limits removal scripts
		static uint32_t guildNextRefill2_size; // size field, set during initialization by getting data from lua
		static mm8::NPC* NPCDataTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t NPCDataTxt_size; // size field, set during initialization by getting data from lua
		static mm8::HousesExtra* housesExtra; // converted to pointer to not break with limits removal scripts
		static uint32_t housesExtra_size; // size field, set during initialization by getting data from lua
		static mm8::CharacterDollType* characterDollTypes; // converted to pointer to not break with limits removal scripts
		static uint32_t characterDollTypes_size; // size field, set during initialization by getting data from lua
		static mm8::CustomLods* customLods; // converted to pointer to not break with limits removal scripts
		static mm8::EventLine* globalEvtLines; // converted to pointer to not break with limits removal scripts
		static uint32_t* globalEvtLines_sizePtr; // pointer to size, set during initialization by getting data from lua
		static mm8::Events2DItem* houses; // converted to pointer to not break with limits removal scripts
		static uint32_t houses_size; // size field, set during initialization by getting data from lua
		static char** NPCNews; // converted to pointer to not break with limits removal scripts
		static uint32_t NPCNews_size; // size field, set during initialization by getting data from lua
		static std::array<mm8::Item, 12>* shopItems; // converted to pointer to not break with limits removal scripts
		static uint32_t shopItems_size; // size field, set during initialization by getting data from lua
		static std::array<uint8_t, 218>* hostileTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t hostileTxt_size; // size field, set during initialization by getting data from lua
		static std::array<int8_t, 4>* transportIndex; // converted to pointer to not break with limits removal scripts
		static uint32_t transportIndex_size; // size field, set during initialization by getting data from lua
		static int64_t* shopNextRefill; // converted to pointer to not break with limits removal scripts
		static uint32_t shopNextRefill_size; // size field, set during initialization by getting data from lua
		static char** classNames; // converted to pointer to not break with limits removal scripts
		static uint32_t classNames_size; // size field, set during initialization by getting data from lua
		static int32_t* autonoteCategory; // converted to pointer to not break with limits removal scripts
		static uint32_t autonoteCategory_size; // size field, set during initialization by getting data from lua
		static int32_t* awardsSort; // converted to pointer to not break with limits removal scripts
		static uint32_t awardsSort_size; // size field, set during initialization by getting data from lua
		static char** questsTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t questsTxt_size; // size field, set during initialization by getting data from lua
		static mm8::TravelInfo* transportLocations; // converted to pointer to not break with limits removal scripts
		static uint32_t transportLocations_size; // size field, set during initialization by getting data from lua
		static mm8::MissileSetup* missileSetup; // converted to pointer to not break with limits removal scripts
		static uint32_t* missileSetup_sizePtr; // pointer to size, set during initialization by getting data from lua
		static char** NPCText; // converted to pointer to not break with limits removal scripts
		static uint32_t NPCText_size; // size field, set during initialization by getting data from lua
		static std::array<char*, 2>* NPCGreet; // converted to pointer to not break with limits removal scripts
		static uint32_t NPCGreet_size; // size field, set during initialization by getting data from lua
		static char** NPCTopic; // converted to pointer to not break with limits removal scripts
		static uint32_t NPCTopic_size; // size field, set during initialization by getting data from lua
		static int16_t* mapDoorSound; // converted to pointer to not break with limits removal scripts
		static uint32_t mapDoorSound_size; // size field, set during initialization by getting data from lua
		static mm8::ItemsTxtItem* itemsTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t* itemsTxt_sizePtr; // pointer to size, set during initialization by getting data from lua
		static mm8::PatchOptions* patchOptions; // converted to pointer to not break with limits removal scripts
		static mm8::MonstersTxtItem* monstersTxt; // converted to pointer to not break with limits removal scripts
		static uint32_t* monstersTxt_sizePtr; // pointer to size, set during initialization by getting data from lua

		// uint8_t* randSeed; // real size is 0 | Unknown type
		SKIP(4381266);
		std::array<uint8_t, 1> minMeleeRecoveryTime; // Unknown type
		SKIP(14553);
		char* winMapIndex; // EditConstPChar - unprotect before/protect after edit
		SKIP(114349);
		char* summonElementalC; // EditConstPChar - unprotect before/protect after edit
		SKIP(19);
		char* summonElementalB; // EditConstPChar - unprotect before/protect after edit
		SKIP(3);
		char* summonElementalA; // EditConstPChar - unprotect before/protect after edit
		SKIP(68796);
		// uint8_t* baseYear; // real size is 0 | Unknown type
		SKIP(26481);
		std::array<uint8_t, 4> newGameMap; // Unknown type
		SKIP(179895);
		std::array<uint8_t, 4> maxBirthYear; // Unknown type
		SKIP(141777);
		std::array<uint8_t, 1> dialogTopicsLimit; // Unknown type
		SKIP(42192);
		std::array<uint8_t, 1> titleTrack; // Unknown type
		SKIP(222282);
		int32_t currentScreen;
		SKIP(676);
		std::array<int8_t, 66> monsterClassInfoY;
		SKIP(2950);
		std::array<std::array<uint8_t, 4>, 132> spellObjId; // MMExt: 1..132, here 0..131 | Unknown type
		SKIP(24);
		std::array<mm8::SpellInfo, 133> spells;
		SKIP(284);
		std::array<int32_t, 6> specialEnterX; // MMExt: 1..6, here 0..5
		std::array<int32_t, 6> specialEnterY; // MMExt: 1..6, here 0..5
		std::array<int32_t, 6> specialEnterZ; // MMExt: 1..6, here 0..5
		std::array<int32_t, 6> specialEnterDirection; // MMExt: 1..6, here 0..5
		SKIP(11004);
		std::array<uint8_t, 20> equipStat2ItemSlot;
		SKIP(19240);
		std::array<mm8::TownPortalTownInfo, 6> townPortalInfo;
		SKIP(120);
		std::array<char*, 30> playerFaces; // EditConstPChar - unprotect before/protect after edit
		SKIP(1200);
		std::array<std::array<uint8_t, 30>, 49> standardPlayerSoundsCount; // MMExt: 1..49, here 0..48
		SKIP(2);
		std::array<mm8::FaceAnimationInfo, 110> standardFaceAnimations;
		SKIP(1464);
		std::array<int16_t, 13> skillRecoveryTimes;
		SKIP(392);
		std::array<int16_t, 132> spellSounds; // MMExt: 1..132, here 0..131
		SKIP(9662);
		std::array<mm8::ShopItemKind, 14> shopWeaponKinds; // MMExt: 1..14, here 0..13
		SKIP(4);
		std::array<std::array<mm8::ShopItemKind, 2>, 14> shopArmorKinds; // MMExt: 15..28, here 0..13 | MMExt: 1..2, here 0..1
		union
		{
			std::array<int16_t, 13> shopMagicLevels; // MMExt: 29..41, here 0..12
			struct
			{
				SKIP(6);
				std::array<int16_t, 12> shopAlchemistLevels; // MMExt: 42..53, here 0..11
			};
		};
		SKIP(122);
		std::array<mm8::ShopItemKind, 14> shopWeaponKindsSpecial; // MMExt: 1..14, here 0..13
		SKIP(4);
		std::array<std::array<mm8::ShopItemKind, 2>, 14> shopArmorKindsSpecial; // MMExt: 15..28, here 0..13 | MMExt: 1..2, here 0..1
		std::array<int16_t, 13> shopMagicLevelsSpecial; // MMExt: 29..41, here 0..12
		SKIP(2);
		std::array<int16_t, 12> shopAlchemistLevelsSpecial; // MMExt: 42..53, here 0..11
		SKIP(292);
		std::array<int32_t, 11> guildJoinCost;
		std::array<int16_t, 13> trainingLevels; // MMExt: 89..101, here 0..12
		SKIP(2);
		std::array<int32_t, 32> guildAwards; // MMExt: 139..170, here 0..31
		SKIP(1088);
		std::array<int16_t, 34> guildSpellLevels; // MMExt: 139..172, here 0..33
		SKIP(2380);
		std::array<int16_t, 6> townPortalX;
		std::array<int16_t, 6> townPortalY;
		SKIP(32956);
		int32_t turnBasedPhase;
		SKIP(59656);
		int32_t currentCharScreen;
		SKIP(3392);
		std::array<char*, 7> statsNames; // EditPChar
		SKIP(4);
		uint32_t ctrlPressed; // 4-byte boolean
		SKIP(20);
		mm8::Dlg* currentNPCDialog;
		SKIP(40);
		std::array<uint8_t, 4> currentPlayer; // Unknown type
		bool rightButtonPressed;
		SKIP(16319);
		uint32_t paused2; // 4-byte boolean
		SKIP(36);
		uint32_t paused; // 4-byte boolean
		SKIP(20);
		int32_t timeDelta;
		SKIP(3568);
		uint32_t actionsNext_size;
		std::array<mm8::ActionItem, 40> actionsNext; // size field offset is 0x51E148
		SKIP(4);
		uint32_t actions_size;
		std::array<mm8::ActionItem, 40> actions; // size field offset is 0x51E330
		SKIP(431044);
		mm8::ProgressBar progressBar;
		SKIP(44);
		uint32_t loadingScreen; // 4-byte boolean
		SKIP(452);
		uint32_t needRedraw; // 4-byte boolean
		SKIP(120984);
		int32_t NPCCommand;
		int32_t dialogNPC;
		SKIP(4);
		int32_t houseOwnerPic;
		SKIP(832);
		std::array<int32_t, 6> houseNPCs; // MMExt: 1..6, here 0..5
		int32_t houseNPCSlot;
		SKIP(48);
		int32_t houseNPCSlotsCount;
		SKIP(135472);
		std::array<char, 2000> streetMessage; // fixed size string, requires null terminator
		SKIP(8);
		uint32_t mapEvtLines_size;
		SKIP(23700);
		mm8::MoveToMap moveToMap;
		SKIP(16);
		bool inQuestionDialog;
		SKIP(3);
		std::array<mm8::EventLine, 5000> mapEvtLines; // size field offset is 0x5C7020
		SKIP(16);
		std::array<char, 200> statusMessage; // fixed size string, requires null terminator
		std::array<char, 200> mouseOverStatusMessage; // fixed size string, requires null terminator
		int32_t statusDisappearTime;
		SKIP(16);
		int32_t houseExitMap;
		SKIP(16);
		int32_t autonote_fnt;
		int32_t spell_fnt;
		int32_t arrus_fnt;
		int32_t lucida_fnt;
		int32_t book2_fnt;
		int32_t book_fnt;
		SKIP(4);
		int32_t create_fnt;
		SKIP(4);
		int32_t comic_fnt;
		int32_t smallnum_fnt;
		SKIP(14244);
		std::array<char, 2000> textBuffer; // fixed size string, requires null terminator
		SKIP(6000);
		std::array<char, 2000> textBuffer2; // fixed size string, requires null terminator
		SKIP(6104);
		uint32_t TFTBin_size;
		mm8::TFTItem* TFTBin; // size field offset is 0x5E2FC8
		mm8::SFT SFTBin;
		SKIP(6408);
		std::array<char*, 36> classDescriptions; // EditPChar
		SKIP(16);
		std::array<char*, 7> statsDescriptions; // EditPChar
		SKIP(772);
		std::array<char*, 39> skillDescriptions; // EditPChar
		SKIP(92);
		std::array<mm8::HistoryTxtItem, 29> historyTxt; // MMExt: 1..29, here 0..28
		SKIP(13172);
		std::array<mm8::SpellsTxtItem, 133> spellsTxt;
		SKIP(87780);
		std::array<std::array<int16_t, 50>, 50> potionTxt; // MMExt: 222..271, here 0..49 | MMExt: 222..271, here 0..49
		SKIP(5296);
		std::array<char*, 750> globalTxt; // EditPChar
		SKIP(1328);
		uint32_t overlayBin_size;
		mm8::OverlayItem* overlayBin; // size field offset is 0x602530
		SKIP(106484);
		uint32_t chestBin_size;
		mm8::DChestItem* chestBin; // size field offset is 0x61C52C
		uint32_t monListBin_size;
		mm8::MonListItem* monListBin; // MMExt: 1..0, here 0..-1 | size field offset is 0x61C534
		SKIP(598012);
		uint32_t objListBin_size;
		mm8::ObjListItem* objListBin; // size field offset is 0x6AE538
		SKIP(108060);
		uint32_t decListBin_size;
		mm8::DecListItem* decListBin; // size field offset is 0x6C8B5C
		SKIP(96);
		std::array<int32_t, 30> keyCodes;
		std::array<int32_t, 30> keyTypes;
		SKIP(22852);
		mm8::Lod saveGameLod;
		SKIP(4);
		mm8::Lod gamesLod;
		SKIP(176);
		int32_t mainMenuCode;
		int32_t exitMapAction;
		SKIP(148624);
		uint32_t tile3Bin_size;
		mm8::TileItem* tile3Bin; // size field offset is 0x6F2FBC
		uint32_t tile2Bin_size;
		mm8::TileItem* tile2Bin; // size field offset is 0x6F2FC4
		uint32_t tileBin_size;
		mm8::TileItem* tileBin; // size field offset is 0x6F2FCC
		mm8::CurrentTileBin* currentTileBin;
		int32_t exitLevelCode;
		SKIP(48);
		int32_t outdoorViewMul;
		SKIP(1908);
		std::array<float, 4> speedModifiers;
		SKIP(416);
		uint32_t windowHandle;
		SKIP(119);
		int32_t soundVolume;
		SKIP(105013);
		mm8::BitmapsLod iconsLod;
		SKIP(8);
		mm8::SpritesLod spritesLod;
		mm8::BitmapsLod bitmapsLod;
		SKIP(138800);
		struct __awardsTxt
		{
			char* value;
			SKIP(4);
		};
		std::array<__awardsTxt, 105> awardsTxt; // EditPChar
		SKIP(88080);
		std::array<mm8::NPC, 100> streetNPC; // size field offset is 0x779FF4
		SKIP(4260);
		uint32_t streetNPC_size;
		SKIP(488);
		std::array<std::array<char*, 7>, 4> merchantTxt; // EditPChar
		SKIP(3378608);
		struct // size: 0xC, MMExt union
		{
			int64_t delay;
			int16_t animation;
			int16_t playerIndex;
		} delayedFaceAnimation;
		static_assert(sizeof(delayedFaceAnimation) == 0xC, "Invalid \"delayedFaceAnimation\" structure size");
		uint32_t IFTBin_size;
		mm8::IFTItem* IFTBin; // size field offset is 0xAB300C
		uint32_t PFTBin_size;
		mm8::PFTItem* PFTBin; // size field offset is 0xAB3014
		SKIP(450208);
		int64_t time;
		SKIP(512);
		std::array<int64_t, 34> guildNextRefill; // MMExt: 139..172, here 0..33
		SKIP(984);
		int32_t year;
		int32_t month;
		int32_t weekOfMonth;
		int32_t dayOfMonth;
		int32_t hour;
		int32_t minute;
		int32_t second;
		SKIP(352);
		uint32_t turnBased; // 4-byte boolean
		SKIP(373596);
		bool needRender : 1;
		SKIP(222075);
		int32_t armageddonTimeLeft;
		int32_t armageddonSkill;
		std::array<int32_t, 5> turnBasedDelays;
		SKIP(576);
		std::array<char*, 39> skillNames; // EditPChar
		SKIP(3205252);
		union
		{
			mm8::GameScreen screen;
			struct
			{
				SKIP(262196);
				std::array<std::array<mm8::ObjectRef, 640>, 480>* objectByPixel;
				SKIP(32);
				uint32_t windowed;
				SKIP(44);
				uint32_t rendererD3D;
			};
		};
		SKIP(957332);
		int32_t redbookHandle;
		int32_t MSSHandle;
		SKIP(2520);
		uint32_t soundsBin_size;
		mm8::SoundsItem* soundsBin; // size field offset is 0xFEBFE4
		SKIP(70632);
		std::array<int32_t, 12> guildItemIconPtr;
		int32_t housePicType;
		int32_t houseScreen;
		SKIP(8);
		int32_t houseAllowAction;
		int32_t houseActionInfo;
		int32_t houseTeachMastery;
		int32_t houseCost;
		SKIP(44);
		int32_t houseItemsCount;
		SKIP(4);
		char* NPCMessage; // EditPChar
		SKIP(2380);
		int32_t smackVideo;
		SKIP(56);
		uint32_t isMovieLooped; // 4-byte boolean
		SKIP(24);
		int32_t binkVideo;
		SKIP(24);
		int32_t movieKind;
		SKIP(33580);
		uint32_t inOODialog; // 4-byte boolean
		SKIP(58181388);
		std::array<mm8::StdItemsTxtItem, 29> stdItemsTxt;
		std::array<mm8::SpcItemsTxtItem, 138> spcItemsTxt;
		SKIP(1536126740);
	};
	static_assert(sizeof(mm8::GameStructure) == 0x6007A8CC, "Invalid \"mm8::GameStructure\" structure size");
	static_assert(offsetof(mm8::GameStructure, minMeleeRecoveryTime) == 4381266);
	static_assert(offsetof(mm8::GameStructure, winMapIndex) == 4395820);
	static_assert(offsetof(mm8::GameStructure, summonElementalC) == 4510173);
	static_assert(offsetof(mm8::GameStructure, summonElementalB) == 4510196);
	static_assert(offsetof(mm8::GameStructure, summonElementalA) == 4510203);
	static_assert(offsetof(mm8::GameStructure, newGameMap) == 4605484);
	static_assert(offsetof(mm8::GameStructure, maxBirthYear) == 4785383);
	static_assert(offsetof(mm8::GameStructure, dialogTopicsLimit) == 4927164);
	static_assert(offsetof(mm8::GameStructure, titleTrack) == 4969357);
	static_assert(offsetof(mm8::GameStructure, currentScreen) == 5191640);
	static_assert(offsetof(mm8::GameStructure, monsterClassInfoY) == 5192320);
	static_assert(offsetof(mm8::GameStructure, spellObjId) == 5195336);
	static_assert(offsetof(mm8::GameStructure, spells) == 5195888);
	static_assert(offsetof(mm8::GameStructure, specialEnterX) == 5198832);
	static_assert(offsetof(mm8::GameStructure, specialEnterY) == 5198856);
	static_assert(offsetof(mm8::GameStructure, specialEnterZ) == 5198880);
	static_assert(offsetof(mm8::GameStructure, specialEnterDirection) == 5198904);
	static_assert(offsetof(mm8::GameStructure, equipStat2ItemSlot) == 5209932);
	static_assert(offsetof(mm8::GameStructure, townPortalInfo) == 5229192);
	static_assert(offsetof(mm8::GameStructure, playerFaces) == 5229432);
	static_assert(offsetof(mm8::GameStructure, standardPlayerSoundsCount) == 5230752);
	static_assert(offsetof(mm8::GameStructure, standardFaceAnimations) == 5232224);
	static_assert(offsetof(mm8::GameStructure, skillRecoveryTimes) == 5234568);
	static_assert(offsetof(mm8::GameStructure, spellSounds) == 5234986);
	static_assert(offsetof(mm8::GameStructure, shopWeaponKinds) == 5244912);
	static_assert(offsetof(mm8::GameStructure, shopArmorKinds) == 5245056);
	static_assert(offsetof(mm8::GameStructure, shopMagicLevels) == 5245336);
	static_assert(offsetof(mm8::GameStructure, shopAlchemistLevels) == 5245342);
	static_assert(offsetof(mm8::GameStructure, shopWeaponKindsSpecial) == 5245488);
	static_assert(offsetof(mm8::GameStructure, shopArmorKindsSpecial) == 5245632);
	static_assert(offsetof(mm8::GameStructure, shopMagicLevelsSpecial) == 5245912);
	static_assert(offsetof(mm8::GameStructure, shopAlchemistLevelsSpecial) == 5245940);
	static_assert(offsetof(mm8::GameStructure, guildJoinCost) == 5246256);
	static_assert(offsetof(mm8::GameStructure, trainingLevels) == 5246300);
	static_assert(offsetof(mm8::GameStructure, guildAwards) == 5246328);
	static_assert(offsetof(mm8::GameStructure, guildSpellLevels) == 5247544);
	static_assert(offsetof(mm8::GameStructure, townPortalX) == 5249992);
	static_assert(offsetof(mm8::GameStructure, townPortalY) == 5250004);
	static_assert(offsetof(mm8::GameStructure, turnBasedPhase) == 5282972);
	static_assert(offsetof(mm8::GameStructure, currentCharScreen) == 5342632);
	static_assert(offsetof(mm8::GameStructure, statsNames) == 5346028);
	static_assert(offsetof(mm8::GameStructure, ctrlPressed) == 5346060);
	static_assert(offsetof(mm8::GameStructure, currentNPCDialog) == 5346084);
	static_assert(offsetof(mm8::GameStructure, currentPlayer) == 5346128);
	static_assert(offsetof(mm8::GameStructure, rightButtonPressed) == 5346132);
	static_assert(offsetof(mm8::GameStructure, paused2) == 5362452);
	static_assert(offsetof(mm8::GameStructure, paused) == 5362492);
	static_assert(offsetof(mm8::GameStructure, timeDelta) == 5362516);
	static_assert(offsetof(mm8::GameStructure, actionsNext_size) == 5366088);
	static_assert(offsetof(mm8::GameStructure, actionsNext) == 5366092);
	static_assert(offsetof(mm8::GameStructure, actions_size) == 5366576);
	static_assert(offsetof(mm8::GameStructure, actions) == 5366580);
	static_assert(offsetof(mm8::GameStructure, progressBar) == 5798104);
	static_assert(offsetof(mm8::GameStructure, loadingScreen) == 5798164);
	static_assert(offsetof(mm8::GameStructure, needRedraw) == 5798620);
	static_assert(offsetof(mm8::GameStructure, NPCCommand) == 5919608);
	static_assert(offsetof(mm8::GameStructure, dialogNPC) == 5919612);
	static_assert(offsetof(mm8::GameStructure, houseOwnerPic) == 5919620);
	static_assert(offsetof(mm8::GameStructure, houseNPCs) == 5920456);
	static_assert(offsetof(mm8::GameStructure, houseNPCSlot) == 5920480);
	static_assert(offsetof(mm8::GameStructure, houseNPCSlotsCount) == 5920532);
	static_assert(offsetof(mm8::GameStructure, streetMessage) == 6056008);
	static_assert(offsetof(mm8::GameStructure, mapEvtLines_size) == 6058016);
	static_assert(offsetof(mm8::GameStructure, moveToMap) == 6081720);
	static_assert(offsetof(mm8::GameStructure, inQuestionDialog) == 6081764);
	static_assert(offsetof(mm8::GameStructure, mapEvtLines) == 6081768);
	static_assert(offsetof(mm8::GameStructure, statusMessage) == 6141784);
	static_assert(offsetof(mm8::GameStructure, mouseOverStatusMessage) == 6141984);
	static_assert(offsetof(mm8::GameStructure, statusDisappearTime) == 6142184);
	static_assert(offsetof(mm8::GameStructure, houseExitMap) == 6142204);
	static_assert(offsetof(mm8::GameStructure, autonote_fnt) == 6142224);
	static_assert(offsetof(mm8::GameStructure, spell_fnt) == 6142228);
	static_assert(offsetof(mm8::GameStructure, arrus_fnt) == 6142232);
	static_assert(offsetof(mm8::GameStructure, lucida_fnt) == 6142236);
	static_assert(offsetof(mm8::GameStructure, book2_fnt) == 6142240);
	static_assert(offsetof(mm8::GameStructure, book_fnt) == 6142244);
	static_assert(offsetof(mm8::GameStructure, create_fnt) == 6142252);
	static_assert(offsetof(mm8::GameStructure, comic_fnt) == 6142260);
	static_assert(offsetof(mm8::GameStructure, smallnum_fnt) == 6142264);
	static_assert(offsetof(mm8::GameStructure, textBuffer) == 6156512);
	static_assert(offsetof(mm8::GameStructure, textBuffer2) == 6164512);
	static_assert(offsetof(mm8::GameStructure, TFTBin_size) == 6172616);
	static_assert(offsetof(mm8::GameStructure, TFTBin) == 6172620);
	static_assert(offsetof(mm8::GameStructure, SFTBin) == 6172624);
	static_assert(offsetof(mm8::GameStructure, classDescriptions) == 6179056);
	static_assert(offsetof(mm8::GameStructure, statsDescriptions) == 6179216);
	static_assert(offsetof(mm8::GameStructure, skillDescriptions) == 6180016);
	static_assert(offsetof(mm8::GameStructure, historyTxt) == 6180264);
	static_assert(offsetof(mm8::GameStructure, spellsTxt) == 6193784);
	static_assert(offsetof(mm8::GameStructure, potionTxt) == 6286352);
	static_assert(offsetof(mm8::GameStructure, globalTxt) == 6296648);
	static_assert(offsetof(mm8::GameStructure, overlayBin_size) == 6300976);
	static_assert(offsetof(mm8::GameStructure, overlayBin) == 6300980);
	static_assert(offsetof(mm8::GameStructure, chestBin_size) == 6407468);
	static_assert(offsetof(mm8::GameStructure, chestBin) == 6407472);
	static_assert(offsetof(mm8::GameStructure, monListBin_size) == 6407476);
	static_assert(offsetof(mm8::GameStructure, monListBin) == 6407480);
	static_assert(offsetof(mm8::GameStructure, objListBin_size) == 7005496);
	static_assert(offsetof(mm8::GameStructure, objListBin) == 7005500);
	static_assert(offsetof(mm8::GameStructure, decListBin_size) == 7113564);
	static_assert(offsetof(mm8::GameStructure, decListBin) == 7113568);
	static_assert(offsetof(mm8::GameStructure, keyCodes) == 7113668);
	static_assert(offsetof(mm8::GameStructure, keyTypes) == 7113788);
	static_assert(offsetof(mm8::GameStructure, saveGameLod) == 7136760);
	static_assert(offsetof(mm8::GameStructure, gamesLod) == 7137336);
	static_assert(offsetof(mm8::GameStructure, mainMenuCode) == 7138084);
	static_assert(offsetof(mm8::GameStructure, exitMapAction) == 7138088);
	static_assert(offsetof(mm8::GameStructure, tile3Bin_size) == 7286716);
	static_assert(offsetof(mm8::GameStructure, tile3Bin) == 7286720);
	static_assert(offsetof(mm8::GameStructure, tile2Bin_size) == 7286724);
	static_assert(offsetof(mm8::GameStructure, tile2Bin) == 7286728);
	static_assert(offsetof(mm8::GameStructure, tileBin_size) == 7286732);
	static_assert(offsetof(mm8::GameStructure, tileBin) == 7286736);
	static_assert(offsetof(mm8::GameStructure, currentTileBin) == 7286740);
	static_assert(offsetof(mm8::GameStructure, exitLevelCode) == 7286744);
	static_assert(offsetof(mm8::GameStructure, outdoorViewMul) == 7286796);
	static_assert(offsetof(mm8::GameStructure, speedModifiers) == 7288708);
	static_assert(offsetof(mm8::GameStructure, windowHandle) == 7289140);
	static_assert(offsetof(mm8::GameStructure, soundVolume) == 7289263);
	static_assert(offsetof(mm8::GameStructure, iconsLod) == 7394280);
	static_assert(offsetof(mm8::GameStructure, spritesLod) == 7466920);
	static_assert(offsetof(mm8::GameStructure, bitmapsLod) == 7527520);
	static_assert(offsetof(mm8::GameStructure, awardsTxt) == 7738952);
	static_assert(offsetof(mm8::GameStructure, streetNPC) == 7827872);
	static_assert(offsetof(mm8::GameStructure, streetNPC_size) == 7839732);
	static_assert(offsetof(mm8::GameStructure, merchantTxt) == 7840224);
	static_assert(offsetof(mm8::GameStructure, delayedFaceAnimation) == 11218944);
	static_assert(offsetof(mm8::GameStructure, IFTBin_size) == 11218956);
	static_assert(offsetof(mm8::GameStructure, IFTBin) == 11218960);
	static_assert(offsetof(mm8::GameStructure, PFTBin_size) == 11218964);
	static_assert(offsetof(mm8::GameStructure, PFTBin) == 11218968);
	static_assert(offsetof(mm8::GameStructure, time) == 11669180);
	static_assert(offsetof(mm8::GameStructure, guildNextRefill) == 11669700);
	static_assert(offsetof(mm8::GameStructure, year) == 11670956);
	static_assert(offsetof(mm8::GameStructure, month) == 11670960);
	static_assert(offsetof(mm8::GameStructure, weekOfMonth) == 11670964);
	static_assert(offsetof(mm8::GameStructure, dayOfMonth) == 11670968);
	static_assert(offsetof(mm8::GameStructure, hour) == 11670972);
	static_assert(offsetof(mm8::GameStructure, minute) == 11670976);
	static_assert(offsetof(mm8::GameStructure, second) == 11670980);
	static_assert(offsetof(mm8::GameStructure, turnBased) == 11671336);
	static_assert(offsetof(mm8::GameStructure, armageddonTimeLeft) == 12267012);
	static_assert(offsetof(mm8::GameStructure, armageddonSkill) == 12267016);
	static_assert(offsetof(mm8::GameStructure, turnBasedDelays) == 12267020);
	static_assert(offsetof(mm8::GameStructure, skillNames) == 12267616);
	static_assert(offsetof(mm8::GameStructure, screen) == 15473024);
	static_assert(offsetof(mm8::GameStructure, objectByPixel) == 15735220);
	static_assert(offsetof(mm8::GameStructure, windowed) == 15735256);
	static_assert(offsetof(mm8::GameStructure, rendererD3D) == 15735304);
	static_assert(offsetof(mm8::GameStructure, redbookHandle) == 16692740);
	static_assert(offsetof(mm8::GameStructure, MSSHandle) == 16692744);
	static_assert(offsetof(mm8::GameStructure, soundsBin_size) == 16695268);
	static_assert(offsetof(mm8::GameStructure, soundsBin) == 16695272);
	static_assert(offsetof(mm8::GameStructure, guildItemIconPtr) == 16765908);
	static_assert(offsetof(mm8::GameStructure, housePicType) == 16765956);
	static_assert(offsetof(mm8::GameStructure, houseScreen) == 16765960);
	static_assert(offsetof(mm8::GameStructure, houseAllowAction) == 16765972);
	static_assert(offsetof(mm8::GameStructure, houseActionInfo) == 16765976);
	static_assert(offsetof(mm8::GameStructure, houseTeachMastery) == 16765980);
	static_assert(offsetof(mm8::GameStructure, houseCost) == 16765984);
	static_assert(offsetof(mm8::GameStructure, houseItemsCount) == 16766032);
	static_assert(offsetof(mm8::GameStructure, NPCMessage) == 16766040);
	static_assert(offsetof(mm8::GameStructure, smackVideo) == 16768424);
	static_assert(offsetof(mm8::GameStructure, isMovieLooped) == 16768484);
	static_assert(offsetof(mm8::GameStructure, binkVideo) == 16768512);
	static_assert(offsetof(mm8::GameStructure, movieKind) == 16768540);
	static_assert(offsetof(mm8::GameStructure, inOODialog) == 16802124);
	static_assert(offsetof(mm8::GameStructure, stdItemsTxt) == 74983516);
	static_assert(offsetof(mm8::GameStructure, spcItemsTxt) == 74984096);
}

#pragma pack(pop)