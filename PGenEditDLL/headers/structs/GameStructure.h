#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm6
{
	struct GameStructure // size: 0x60020196
	{
		static inline mm6::GameClassKinds* const classKinds = 0;
		static inline mm6::GameClasses* const classes = 0;
		static inline mm6::DialogLogic* const dialogLogic = 0;
		static inline mm6::GameMap* const map = 0;
		static inline mm6::GameParty* const party = 0;
		static inline mm6::Weather* const weather = 0;

		static char** autonoteTxt; // original offset 0x6BA628 (7054888 decimal)element size: 0x4 (4 decimal)
		static uint32_t autonoteTxt_size; // Offset/size: 0x81 (129 decimal)
		static int32_t* awardsSort; // original offset 0x3121334 (51516212 decimal)element size: 0x4 (4 decimal)
		static uint32_t* awardsSort_sizePtr; // Offset/size: 0x3121338 (51516216 decimal)
		static char** awardsTxt; // original offset 0x6A9008 (6983688 decimal)element size: 0x4 (4 decimal)
		static uint32_t awardsTxt_size; // Offset/size: 0x58 (88 decimal)
		static char** classNames; // original offset 0x970BEC (9898988 decimal)element size: 0x4 (4 decimal)
		static uint32_t classNames_size; // Offset/size: 0x12 (18 decimal)
		static mm6::CustomLods* customLods; // original offset 0x3405D5C (54549852 decimal)
		static uint32_t* frameCounter; // original offset 0x3121348 (51516232 decimal)
		static mm6::EventLine* globalEvtLines; // original offset 0x53CB6C (5491564 decimal)element size: 0xC (12 decimal)
		static uint32_t* globalEvtLines_sizePtr; // Offset/size: 0x54D038 (5558328 decimal)
		static std::array<std::array<mm6::Item, 12>, 1>* guildItems; // original offset 0x91663C (9528892 decimal)element size: 0x150 (336 decimal)
		static uint32_t guildItems_size; // Offset/size: 0x16 (22 decimal)
		static mm6::HouseMovie* houseMovies; // original offset 0x4BE888 (4974728 decimal)element size: 0x10 (16 decimal)
		static uint32_t houseMovies_size; // Offset/size: 0x77 (119 decimal)
		static mm6::Events2DItem* houses; // original offset 0x52D530 (5428528 decimal)element size: 0x30 (48 decimal)
		static uint32_t houses_size; // Offset/size: 0x22E (558 decimal)
		static mm6::ItemsTxtItem* itemsTxt; // original offset 0x560C14 (5639188 decimal)element size: 0x28 (40 decimal)
		static uint32_t* itemsTxt_sizePtr; // Offset/size: 0x560C10 (5639184 decimal)
		static int16_t* mapDoorSound; // original offset 0x4C3B74 (4995956 decimal)element size: 0x2 (2 decimal)
		static uint32_t mapDoorSound_size; // Offset/size: 0x44 (68 decimal)
		static mm6::FogChances* mapFogChances; // original offset 0x4C1F18 (4988696 decimal)element size: 0x3 (3 decimal)
		static uint32_t mapFogChances_size; // Offset/size: 0x10 (16 decimal)
		static mm6::MapStatsItem* mapStats; // original offset 0x55F628 (5633576 decimal)element size: 0x38 (56 decimal)
		static uint32_t* mapStats_sizePtr; // Offset/size: 0x560C08 (5639176 decimal)
		static mm6::MissileSetup* missileSetup; // original offset 0x3122BF8 (51522552 decimal)element size: 0x1 (1 decimal)
		static uint32_t* missileSetup_sizePtr; // Offset/size: 0x3122BFC (51522556 decimal)
		static mm6::MonstersTxtItem* monstersTxt; // original offset 0x56C188 (5685640 decimal)element size: 0x48 (72 decimal)
		static uint32_t* monstersTxt_sizePtr; // Offset/size: 0x56F278 (5698168 decimal)
		static mm6::NPC* NPC; // original offset 0x6AEF28 (7008040 decimal)element size: 0x3C (60 decimal)
		static uint32_t* NPC_sizePtr; // Offset/size: 0x6BA534 (7054644 decimal)
		static mm6::NPC* NPCDataTxt; // original offset 0x6A9168 (6984040 decimal)element size: 0x3C (60 decimal)
		static uint32_t NPCDataTxt_size; // Offset/size: 0x190 (400 decimal)
		static std::array<char*, 2>* NPCNames; // original offset 0x6B4CE8 (7032040 decimal)element size: 0x8 (8 decimal)
		static uint32_t NPCNames_size; // Offset/size: 0x21C (540 decimal)
		static mm6::NPCNewsItem* NPCNews; // original offset 0x6B8C60 (7048288 decimal)element size: 0xC (12 decimal)
		static uint32_t NPCNews_size; // Offset/size: 0x118 (280 decimal)
		static char** NPCText; // original offset 0x6A7684 (6977156 decimal)element size: 0x4 (4 decimal)
		static uint32_t NPCText_size; // Offset/size: 0x205 (517 decimal)
		static char** NPCTopic; // original offset 0x6A7680 (6977152 decimal)element size: 0x4 (4 decimal)
		static uint32_t NPCTopic_size; // Offset/size: 0x205 (517 decimal)
		static mm6::PatchOptions* patchOptions; // original offset 0x32F9364 (53449572 decimal)
		static char** questsTxt; // original offset 0x6A8804 (6981636 decimal)element size: 0x4 (4 decimal)
		static uint32_t questsTxt_size; // Offset/size: 0x201 (513 decimal)
		static std::array<mm6::Item, 12>* shopItems; // original offset 0x90EADC (9497308 decimal)element size: 0x150 (336 decimal)
		static uint32_t shopItems_size; // Offset/size: 0x30 (48 decimal)
		static int64_t* shopNextRefill; // original offset 0x2AEA020 (44998688 decimal)element size: 0x8 (8 decimal)
		static uint32_t shopNextRefill_size; // Offset/size: 0x30 (48 decimal)
		static std::array<mm6::Item, 12>* shopSpecialItems; // original offset 0xADBA510 (182166800 decimal)element size: 0x150 (336 decimal)
		static uint32_t shopSpecialItems_size; // Offset/size: 0x2F (47 decimal)
		static mm6::SpcItemsTxtItem* spcItemsTxt; // original offset 0x5667F4 (5662708 decimal)element size: 0x1C (28 decimal)
		static uint32_t spcItemsTxt_size; // Offset/size: 0x3B (59 decimal)
		static mm6::StdItemsTxtItem* stdItemsTxt; // original offset 0x5666DC (5662428 decimal)element size: 0x14 (20 decimal)
		static uint32_t stdItemsTxt_size; // Offset/size: 0xE (14 decimal)
		static uint8_t* titleTrackOffset; // original offset 0x4A6C31 (4877361 decimal)element size: 0x1 (1 decimal)
		static uint32_t titleTrackOffset_size; // Offset/size: 0x4 (4 decimal)
		static char** transTxt; // original offset 0x4C1048 (4984904 decimal)element size: 0x4 (4 decimal)
		static uint32_t transTxt_size; // Offset/size: 0xEA (234 decimal)
		static std::array<int8_t, 3>* transportIndex; // original offset 0x4C43A0 (4998048 decimal)element size: 0x3 (3 decimal)
		static uint32_t transportIndex_size; // Offset/size: 0x15 (21 decimal)
		static mm6::TravelInfo* transportLocations; // original offset 0x4C3F20 (4996896 decimal)element size: 0x20 (32 decimal)
		static uint32_t transportLocations_size; // Offset/size: 0x24 (36 decimal)

		// uint8_t* randSeed; // real size is 0 | Unknown type | 0x0 (0 decimal)
		SKIP(4366905);
		std::array<uint8_t, 1> minMeleeRecoveryTime; // Unknown type | 0x42A239 (4366905 decimal)
		SKIP(20301);
		// MMExt info: Number represented as a string.
		// [MM6] Index in games.lod
		// [MM7+] Index in mapstats.txt
		char* winMapIndex; // EditConstPChar - unprotect before/protect after edit | 0x42F187 (4387207 decimal)
		SKIP(135569);
		// uint8_t* baseYear; // real size is 0 | Unknown type | 0x45031C (4522780 decimal)
		SKIP(11458);
		std::array<uint8_t, 1> narratorTrack; // Unknown type | 0x452FDE (4534238 decimal)
		SKIP(20339);
		std::array<uint8_t, 4> newGameMap; // Unknown type | 0x457F52 (4554578 decimal)
		SKIP(53997);
		std::array<uint8_t, 4> flyCeiling; // Unknown type | 0x465243 (4608579 decimal) | MMExt info: 3000 in MM6, 4000 in MM7+, in MM8 it's configured per map (!Lua[[Map.OutdoorExtra.Ceiling]])
		SKIP(125975);
		std::array<uint8_t, 4> maxBirthYear; // Unknown type | 0x483E5E (4734558 decimal)
		SKIP(142776);
		std::array<uint8_t, 1> titleTrack; // Unknown type | 0x4A6C1A (4877338 decimal)
		SKIP(87517);
		std::array<std::array<int16_t, 48>, 5> autonotesByCategory; // 0x4BC1F8 (4964856 decimal)
		SKIP(1804);
		std::array<int16_t, 6> townPortalX; // 0x4BCAE4 (4967140 decimal) | MMExt info: (Town portal picture: townport)
		std::array<int16_t, 6> townPortalY; // 0x4BCAF0 (4967152 decimal) | MMExt info: (Town portal icons [MM7+]: tpharmndy, tpelf, tpwarlock, tpisland, tpheaven, tphell)
		std::array<int16_t, 6> townPortalWidth; // 0x4BCAFC (4967164 decimal)
		std::array<int16_t, 6> townPortalHeight; // 0x4BCB08 (4967176 decimal)
		SKIP(708);
		int32_t currentScreen; // 0x4BCDD8 (4967896 decimal) | MMExt info: :const.Screens
		SKIP(816);
		std::array<int8_t, 60> monsterClassInfoY; // 0x4BD10C (4968716 decimal)
		SKIP(2704);
		std::array<std::array<uint8_t, 4>, 99> spellObjId; // MMExt: 1..99, here 0..98 | Unknown type | 0x4BDBD8 (4971480 decimal)
		SKIP(12);
		std::array<mm6::SpellInfo, 100> spells; // 0x4BDD70 (4971888 decimal)
		SKIP(208);
		std::array<int32_t, 6> specialEnterX; // MMExt: 1..6, here 0..5 | 0x4BE3B8 (4973496 decimal) | MMExt info: Used for Free Haven Sewer entrances in MM6. Negative Questbit Restrictions field in '2DEvents.txt' corresponds to array index
		std::array<int32_t, 6> specialEnterY; // MMExt: 1..6, here 0..5 | 0x4BE3D0 (4973520 decimal)
		std::array<int32_t, 6> specialEnterZ; // MMExt: 1..6, here 0..5 | 0x4BE3E8 (4973544 decimal)
		std::array<int32_t, 6> specialEnterDirection; // MMExt: 1..6, here 0..5 | 0x4BE400 (4973568 decimal)
		SKIP(5256);
		std::array<uint8_t, 20> equipStat2ItemSlot; // 0x4BF8A0 (4978848 decimal)
		std::array<bool, 180> monsterSex; // MMExt: 1..180, here 0..179 | 0x4BF8B4 (4978868 decimal)
		SKIP(9776);
		std::array<mm6::TownPortalTownInfo, 6> townPortalInfo; // 0x4C1F98 (4988824 decimal)
		std::array<char*, 12> playerFaces; // EditConstPChar - unprotect before/protect after edit | 0x4C2010 (4988944 decimal)
		SKIP(156);
		std::array<std::array<uint8_t, 12>, 44> standardPlayerSoundsCount; // MMExt: 1..44, here 0..43 | 0x4C20DC (4989148 decimal)
		SKIP(4);
		std::array<mm6::FaceAnimationInfo, 103> standardFaceAnimations; // 0x4C22F0 (4989680 decimal)
		SKIP(296);
		std::array<int16_t, 13> skillRecoveryTimes; // 0x4C2750 (4990800 decimal)
		SKIP(376);
		std::array<int16_t, 99> spellSounds; // MMExt: 1..99, here 0..98 | 0x4C28E2 (4991202 decimal)
		SKIP(5048);
		std::array<char*, 19> shopBackgroundByType; // EditConstPChar - unprotect before/protect after edit | 0x4C3D60 (4996448 decimal)
		SKIP(100);
		std::array<int32_t, 17> guildJoinCost; // 0x4C3E10 (4996624 decimal)
		SKIP(44);
		std::array<int16_t, 10> trainingLevels; // MMExt: 79..88, here 0..9 | 0x4C3E80 (4996736 decimal)
		std::array<int32_t, 34> guildAwards; // MMExt: 119..152, here 0..33 | 0x4C3E94 (4996756 decimal)
		SKIP(1216);
		std::array<mm6::ShopItemKind, 14> shopWeaponKinds; // MMExt: 1..14, here 0..13 | 0x4C43DC (4998108 decimal)
		std::array<std::array<mm6::ShopItemKind, 2>, 14> shopArmorKinds; // MMExt: 15..28, here 0..13 | MMExt: 1..2, here 0..1 | 0x4C4468 (4998248 decimal)
		std::array<int16_t, 13> shopMagicLevels; // MMExt: 29..41, here 0..12 | 0x4C4580 (4998528 decimal)
		SKIP(2);
		std::array<mm6::GeneralStoreItemKind, 6> generalStoreItemKinds; // MMExt: 42..47, here 0..5 | 0x4C459C (4998556 decimal)
		SKIP(8);
		std::array<mm6::ShopItemKind, 14> shopWeaponKindsSpecial; // MMExt: 1..14, here 0..13 | 0x4C45F8 (4998648 decimal)
		std::array<std::array<mm6::ShopItemKind, 2>, 14> shopArmorKindsSpecial; // MMExt: 15..28, here 0..13 | MMExt: 1..2, here 0..1 | 0x4C4684 (4998788 decimal)
		std::array<int16_t, 13> shopMagicLevelsSpecial; // MMExt: 29..41, here 0..12 | 0x4C479C (4999068 decimal)
		SKIP(2);
		std::array<mm6::GeneralStoreItemKind, 6> generalStoreItemKindsSpecial; // MMExt: 42..47, here 0..5 | 0x4C47B8 (4999096 decimal) | MMExt info: Yes, MM6 generates special items in general stores, but doesn't support buying them.
		SKIP(164);
		std::array<int16_t, 22> guildSpellLevels; // MMExt: 119..140, here 0..21 | 0x4C48B0 (4999344 decimal)
		SKIP(9164);
		std::array<int32_t, 4> turnBasedDelays; // 0x4C6CA8 (5008552 decimal)
		SKIP(4412);
		int32_t turnBasedPhase; // 0x4C7DF4 (5012980 decimal) | MMExt info: 1 = monsters move, 2 = combat, 3 = party walking
		SKIP(10528);
		std::array<int32_t, 480> scanlineOffset; // 0x4CA718 (5023512 decimal)
		SKIP(1888);
		std::array<std::array<uint8_t, 4>, 20> dialogIndexes; // Unknown type | 0x4CB5F8 (5027320 decimal)
		SKIP(88);
		int32_t escMessageLastScreen; // 0x4CB6A0 (5027488 decimal)
		SKIP(44);
		mm6::BitmapsLod iconsLod; // 0x4CB6D0 (5027536 decimal)
		SKIP(316);
		int32_t currentCharScreen; // 0x4D4714 (5064468 decimal) | MMExt info: :const.CharScreens
		SKIP(480);
		std::array<mm6::Dlg, 20> dialogsArray; // 0x4D48F8 (5064952 decimal)
		SKIP(256);
		std::array<char*, 7> statsNames; // EditPChar | 0x4D5088 (5066888 decimal)
		SKIP(4);
		uint32_t ctrlPressed; // 4-byte boolean | 0x4D50A8 (5066920 decimal)
		SKIP(20);
		std::array<uint8_t, 4> currentNPCDialog; // Unknown type | 0x4D50C0 (5066944 decimal)
		std::array<uint8_t, 4> currentHouseDialog; // Unknown type | 0x4D50C4 (5066948 decimal)
		SKIP(20);
		std::array<uint8_t, 4> escMessageDialog; // Unknown type | 0x4D50DC (5066972 decimal)
		SKIP(8);
		std::array<uint8_t, 4> currentPlayer; // Unknown type | 0x4D50E8 (5066984 decimal)
		bool rightButtonPressed; // 0x4D50EC (5066988 decimal)
		SKIP(151);
		uint32_t paused; // 4-byte boolean | 0x4D5184 (5067140 decimal) | MMExt info: Game logic is paused
		SKIP(20);
		int32_t timeDelta; // 0x4D519C (5067164 decimal) | MMExt info: Time since last tick
		SKIP(12);
		uint32_t paused2; // 4-byte boolean | 0x4D51AC (5067180 decimal) | MMExt info: Updates of 3D view are paused
		SKIP(20);
		int32_t timeDelta2; // 0x4D51C4 (5067204 decimal) | MMExt info: Time since last tick of updating 3D view
		SKIP(3456);
		uint32_t actions_size; // 0x4D5F48 (5070664 decimal)
		std::array<mm6::ActionItem, 40> actions; // size field offset is 0x4D5F48 | 0x4D5F4C (5070668 decimal)
		SKIP(356220);
		union
		{
			mm6::ProgressBar progressBar; // 0x52D0A8 (5427368 decimal)
			struct
			{
				SKIP(60);
				uint32_t loadingScreen; // 4-byte boolean | 0x52D0E4 (5427428 decimal)
			};
		};
		SKIP(140);
		uint32_t needRedraw; // 4-byte boolean | 0x52D29C (5427868 decimal)
		SKIP(27668);
		uint32_t mapEvtLines_size; // 0x533EB4 (5455540 decimal)
		int32_t dialogNPC; // 0x533EB8 (5455544 decimal)
		SKIP(36004);
		int32_t houseNPCSlotsCount; // 0x53CB60 (5491552 decimal)
		SKIP(66748);
		std::array<int32_t, 6> houseNPCs; // MMExt: 1..6, here 0..5 | 0x54D020 (5558304 decimal) | MMExt info: If #Game.HouseExitMap:# isn't '0', last slot is occupied by map enter pseudo-NPC.
		SKIP(8);
		int32_t NPCCommand; // 0x54D040 (5558336 decimal)
		SKIP(19676);
		mm6::MoveToMap moveToMap; // 0x551D20 (5578016 decimal)
		SKIP(600);
		// MMExt info: If #Game.HouseOwnerPic:# isn't '0', the value of '1' refers to the shop keeper and higher value needs to be reduced by 1 before accessing .
		// If #Game.HouseExitMap:# isn't '0', last slot is occupied by map enter icon.
		int32_t houseNPCSlot; // 0x551F94 (5578644 decimal)
		SKIP(2004);
		std::array<char, 2000> streetMessage; // fixed size string, requires null terminator | 0x55276C (5580652 decimal) | MMExt info: Message displayed by #Message:#, #Question:#, #evt.SimpleMessage:# and #evt.Question:# when not talking to NPC.
		SKIP(12);
		int32_t houseOwnerPic; // 0x552F48 (5582664 decimal)
		SKIP(12);
		std::array<mm6::EventLine, 3000> mapEvtLines; // size field offset is 0x533EB4 | 0x552F58 (5582680 decimal)
		SKIP(12);
		union
		{
			std::array<char, 200> statusMessage; // fixed size string, requires null terminator | 0x55BC04 (5618692 decimal)
			std::array<uint8_t, 200> statusMessageBytes; // 0x55BC04 (5618692 decimal)
		};
		union
		{
			std::array<char, 200> mouseOverStatusMessage; // fixed size string, requires null terminator | 0x55BCCC (5618892 decimal)
			std::array<uint8_t, 200> mouseOverStatusMessageBytes; // 0x55BCCC (5618892 decimal)
		};
		int32_t statusDisappearTime; // 0x55BD94 (5619092 decimal)
		SKIP(12);
		int32_t houseExitMap; // 0x55BDA4 (5619108 decimal)
		SKIP(12);
		union
		{
			mm6::Fnt* fontLucida; // 0x55BDB4 (5619124 decimal)
			int32_t lucida_fnt; // 0x55BDB4 (5619124 decimal)
		};
		union
		{
			mm6::Fnt* fontSmallnum; // 0x55BDB8 (5619128 decimal)
			int32_t smallnum_fnt; // 0x55BDB8 (5619128 decimal)
		};
		union
		{
			int32_t book_fnt; // 0x55BDBC (5619132 decimal)
			mm6::Fnt* fontBook; // 0x55BDBC (5619132 decimal)
		};
		union
		{
			mm6::Fnt* fontSpell; // 0x55BDC0 (5619136 decimal)
			int32_t spell_fnt; // 0x55BDC0 (5619136 decimal)
		};
		union
		{
			int32_t arrus_fnt; // 0x55BDC4 (5619140 decimal)
			mm6::Fnt* fontArrus; // 0x55BDC4 (5619140 decimal)
		};
		union
		{
			int32_t create_fnt; // 0x55BDC8 (5619144 decimal)
			mm6::Fnt* fontCreate; // 0x55BDC8 (5619144 decimal)
		};
		union
		{
			int32_t comic_fnt; // 0x55BDCC (5619148 decimal)
			mm6::Fnt* fontComic; // 0x55BDCC (5619148 decimal)
		};
		union
		{
			int32_t autonote_fnt; // 0x55BDD0 (5619152 decimal)
			mm6::Fnt* fontAutonote; // 0x55BDD0 (5619152 decimal)
		};
		union
		{
			int32_t book2_fnt; // 0x55BDD4 (5619156 decimal)
			mm6::Fnt* fontBook2; // 0x55BDD4 (5619156 decimal)
		};
		SKIP(4);
		union
		{
			int32_t cchar_fnt; // 0x55BDDC (5619164 decimal)
			mm6::Fnt* fontCchar; // 0x55BDDC (5619164 decimal)
		};
		union
		{
			std::array<char, 2048> wordWrappedText; // fixed size string, requires null terminator | 0x55BDE0 (5619168 decimal)
			std::array<uint8_t, 2048> wordWrappedTextBytes; // 0x55BDE0 (5619168 decimal) | MMExt info: Lets you get address of 'WordWrappedText' or access it byte by byte (note: traversing it like that is very slow)
		};
		SKIP(2048);
		union
		{
			std::array<char, 2000> textBuffer; // fixed size string, requires null terminator | 0x55CDE0 (5623264 decimal)
			std::array<uint8_t, 2000> textBufferBytes; // 0x55CDE0 (5623264 decimal) | MMExt info: Lets you get address of 'TextBuffer' or access it byte by byte (note: traversing it like that is very slow)
		};
		union
		{
			std::array<char, 2000> textBuffer2; // fixed size string, requires null terminator | 0x55D5B0 (5625264 decimal)
			std::array<uint8_t, 2000> textBuffer2Bytes; // 0x55D5B0 (5625264 decimal) | MMExt info: Lets you get address of 'TextBuffer2' or access it byte by byte (note: traversing it like that is very slow)
		};
		SKIP(8);
		mm6::SFT SFTBin; // 0x55DD88 (5627272 decimal)
		uint32_t TFTBin_size; // 0x55DDA0 (5627296 decimal)
		mm6::TFTItem* TFTBin; // size field offset is 0x55DDA0 | 0x55DDA4 (5627300 decimal)
		SKIP(51672);
		std::array<std::array<uint8_t, 29>, 29> potionTxt; // MMExt: 160..188, here 0..28 | MMExt: 160..188, here 0..28 | 0x56A780 (5678976 decimal)
		SKIP(263);
		std::array<mm6::SpellsTxtItem, 100> spellsTxt; // 0x56ABD0 (5680080 decimal)
		std::array<char*, 18> classDescriptions; // EditPChar | 0x56B6C0 (5682880 decimal)
		SKIP(100);
		std::array<char*, 31> skillDesNormal; // EditPChar | 0x56B76C (5683052 decimal)
		SKIP(72);
		std::array<char*, 596> globalTxt; // EditPChar | 0x56B830 (5683248 decimal)
		SKIP(12540);
		std::array<char*, 7> statsDescriptions; // EditPChar | 0x56F27C (5698172 decimal)
		SKIP(4);
		std::array<char*, 31> skillDesExpert; // EditPChar | 0x56F29C (5698204 decimal)
		std::array<char*, 31> skillDesMaster; // EditPChar | 0x56F318 (5698328 decimal)
		std::array<char*, 31> skillDescriptions; // EditPChar | 0x56F394 (5698452 decimal)
		SKIP(274144);
		uint32_t chestBin_size; // 0x5B22F0 (5972720 decimal)
		mm6::DChestItem* chestBin; // size field offset is 0x5B22F0 | 0x5B22F4 (5972724 decimal)
		SKIP(84208);
		uint32_t overlayBin_size; // 0x5C6BE8 (6056936 decimal)
		mm6::OverlayItem* overlayBin; // size field offset is 0x5C6BE8 | 0x5C6BEC (6056940 decimal)
		SKIP(112008);
		uint32_t monListBin_size; // 0x5E2178 (6168952 decimal)
		mm6::MonListItem* monListBin; // MMExt: 1..0, here 0..-1 | size field offset is 0x5E2178 | 0x5E217C (6168956 decimal)
		SKIP(8);
		uint32_t decListBin_size; // 0x5E2188 (6168968 decimal)
		mm6::DecListItem* decListBin; // size field offset is 0x5E2188 | 0x5E218C (6168972 decimal)
		SKIP(85088);
		uint32_t objListBin_size; // 0x5F6DF0 (6254064 decimal)
		mm6::ObjListItem* objListBin; // size field offset is 0x5F6DF0 | 0x5F6DF4 (6254068 decimal)
		SKIP(20);
		std::array<int32_t, 12> keyCodes; // 0x5F6E0C (6254092 decimal)
		std::array<int32_t, 12> keyTypes; // 0x5F6E3C (6254140 decimal)
		int32_t textInputLimit; // 0x5F6E6C (6254188 decimal)
		union
		{
			std::array<char, 257> textInput; // fixed size string, requires null terminator | 0x5F6E70 (6254192 decimal)
			std::array<uint8_t, 257> textInputBytes; // 0x5F6E70 (6254192 decimal)
		};
		uint8_t textInputLength; // 0x5F6F71 (6254449 decimal)
		SKIP(2);
		int32_t textInputMode; // 0x5F6F74 (6254452 decimal)
		std::array<uint8_t, 4> textInputDialog; // Unknown type | 0x5F6F78 (6254456 decimal)
		SKIP(4512);
		int32_t mainMenuCode; // 0x5F811C (6258972 decimal) | MMExt info: -1 = in game, 0 = in main menu, 1 = show new game, 2 = show credits, 3 = show load menu, 4 = exit, 5 = loading game, 6 = in new game screen, 8 = in credits, 9 = load game, 10 = load level [MM7+]
		SKIP(99288);
		mm6::Lod gamesLod; // 0x6104F8 (6358264 decimal)
		SKIP(12);
		uint32_t tileBin_size; // 0x610740 (6358848 decimal)
		mm6::TileItem* tileBin; // size field offset is 0x610740 | 0x610744 (6358852 decimal)
		SKIP(36);
		uint32_t windowHandle; // 0x61076C (6358892 decimal)
		SKIP(115);
		int32_t soundVolume; // 0x6107E3 (6359011 decimal)
		SKIP(73);
		mm6::Lod saveGameLod; // 0x610830 (6359088 decimal)
		SKIP(76);
		mm6::BitmapsLod bitmapsLod; // 0x610AB8 (6359736 decimal)
		union
		{
			int32_t exitLevelCode; // 0x6199C0 (6396352 decimal) | MMExt info: 0 = in game, 2 = load other map, 8 = death
			int32_t exitMapAction; // 0x6199C0 (6396352 decimal) | MMExt info: :const.ExitMapAction
		};
		SKIP(4172);
		mm6::SpritesLod spritesLod; // 0x61AA10 (6400528 decimal)
		SKIP(36);
		int32_t dist_mist; // 0x6296EC (6461164 decimal)
		SKIP(4);
		int32_t outdoorViewMul; // 0x6296F4 (6461172 decimal) | MMExt info: Acts as the opposite of FOV
		int32_t outdoorViewDiv; // 0x6296F8 (6461176 decimal) | MMExt info: !Lua[[= math.floor(0x10000/Game.OutdoorViewMul)]]
		SKIP(510484);
		union
		{
			mm6::GameMouse mouse; // 0x6A6110 (6971664 decimal)
			struct
			{
				SKIP(9624);
				std::array<char*, 87> scrollTxt; // MMExt: 500..586, here 0..86 | EditPChar | 0x6A86A8 (6981288 decimal)
				SKIP(54724);
				std::array<mm6::NPCProfTxtItem, 78> NPCProfTxt; // 0x6B5DC8 (7036360 decimal)
				std::array<mm6::NPC, 100> streetNPC; // size field offset is 0x6BA530 | 0x6B74F0 (7042288 decimal)
				SKIP(6352);
				uint32_t streetNPC_size; // 0x6BA530 (7054640 decimal)
				SKIP(12);
				std::array<int32_t, 2> NPCNamesCount; // 0x6BA540 (7054656 decimal)
				SKIP(32);
				std::array<int16_t, 96> NPCNewsCountByMap; // 0x6BA568 (7054696 decimal)
				SKIP(564);
				std::array<char*, 78> NPCProfNames; // EditPChar | 0x6BA85C (7055452 decimal)
				SKIP(12);
				std::array<std::array<char*, 6>, 4> merchantTxt; // EditPChar | 0x6BA9A0 (7055776 decimal)
				SKIP(2417416);
				int64_t time; // 0x908D08 (9473288 decimal) | MMExt info: Since 00 AM, January 1st, 1165/1168/1172
				int32_t year; // 0x908D10 (9473296 decimal) | MMExt info: Actual value, like 1172
				int32_t month; // 0x908D14 (9473300 decimal) | MMExt info: (0 - 11)
				int32_t weekOfMonth; // 0x908D18 (9473304 decimal) | MMExt info: (0 - 3)
				int32_t dayOfMonth; // 0x908D1C (9473308 decimal) | MMExt info: (0 - 27)
				int32_t hour; // 0x908D20 (9473312 decimal) | MMExt info: (0 - 23)
				int32_t minute; // 0x908D24 (9473316 decimal) | MMExt info: (0 - 59)
				int32_t second; // 0x908D28 (9473320 decimal) | MMExt info: (0 - 59)
				SKIP(260);
				uint32_t turnBased; // 4-byte boolean | 0x908E30 (9473584 decimal)
			};
		};
		bool needRender : 1; // 0x90E838 (9496632 decimal), bit index 6 | MMExt info: Same as Party.NeedRender
		SKIP(467);
		std::array<int64_t, 22> guildNextRefill; // MMExt: 119..140, here 0..21 | 0x90EA0C (9497100 decimal)
		SKIP(40572);
		int32_t armageddonTimeLeft; // 0x918938 (9537848 decimal) | MMExt info: maximum is 417
		int32_t armageddonSkill; // 0x91893C (9537852 decimal) | MMExt info: damage is 50 + skill
		SKIP(181016);
		uint32_t IFTBin_size; // 0x944C58 (9718872 decimal)
		mm6::IFTItem* IFTBin; // size field offset is 0x944C58 | 0x944C5C (9718876 decimal)
		SKIP(180088);
		uint32_t PFTBin_size; // 0x970BD8 (9898968 decimal)
		mm6::PFTItem* PFTBin; // size field offset is 0x970BD8 | 0x970BDC (9898972 decimal)
		struct // size: 0xC, MMExt union
		{
			int64_t delay; // 0x970BE0 (9898976 decimal)
			int16_t animation; // 0x970BE8 (9898984 decimal)
			int16_t playerIndex; // 0x970BEA (9898986 decimal)
		} delayedFaceAnimation;
		static_assert(sizeof(delayedFaceAnimation) == 0xC, "Invalid \"delayedFaceAnimation\" structure size");;
		SKIP(144);
		std::array<char*, 31> skillNames; // EditPChar | 0x970C7C (9899132 decimal)
		SKIP(880);
		union
		{
			mm6::GameScreen screen; // 0x971068 (9900136 decimal)
			struct
			{
				SKIP(262184);
				std::array<std::array<mm6::ObjectRef, 640>, 480>* objectByPixel; // 0x9B1090 (10162320 decimal)
				SKIP(32);
				uint32_t windowed; // 0x9B10B4 (10162356 decimal)
			};
		};
		SKIP(124020);
		int32_t redbookHandle; // 0x9CF5A0 (10286496 decimal)
		int32_t MSSHandle; // 0x9CF5A4 (10286500 decimal)
		SKIP(344);
		uint32_t soundsBin_size; // 0x9CF700 (10286848 decimal)
		mm6::SoundsItem* soundsBin; // size field offset is 0x9CF700 | 0x9CF704 (10286852 decimal)
		SKIP(58984);
		int32_t houseAllowAction; // 0x9DDD70 (10345840 decimal)
		SKIP(12);
		int32_t housePicType; // 0x9DDD80 (10345856 decimal)
		SKIP(4);
		int32_t houseActionInfo; // 0x9DDD88 (10345864 decimal)
		int32_t houseScreen; // 0x9DDD8C (10345868 decimal)
		SKIP(8);
		int32_t houseTeachMastery; // 0x9DDD98 (10345880 decimal)
		int32_t houseCost; // 0x9DDD9C (10345884 decimal)
		SKIP(4);
		std::array<int32_t, 12> guildItemIconPtr; // 0x9DDDA4 (10345892 decimal)
		SKIP(40);
		int32_t houseItemsCount; // 0x9DDDFC (10345980 decimal) | MMExt info: Number of interactive items of the dialog. Items count of the dialog object gets changed to this or 0 depending on selected player being concious.
		SKIP(4);
		char* NPCMessage; // EditPChar | 0x9DDE04 (10345988 decimal) | MMExt info: Current message displayed in a dialog with some NPC
		SKIP(1320);
		int32_t movieKind; // 0x9DE330 (10347312 decimal) | MMExt info: 0 - No movie, 1 - Smack, 2 - Bink
		SKIP(12);
		uint32_t isMovieLooped; // 4-byte boolean | 0x9DE340 (10347328 decimal)
		SKIP(32);
		int32_t smackVideo; // 0x9DE364 (10347364 decimal)
		SKIP(1600396846);
		int __thiscall endMovie(/**/); // address: 0x4A5D10 | defaults: 10347312
		int __stdcall rand(); // address: 0x4AE22B
		int __thiscall restartHouseMovie(/**/); // address: 0x4A68B0 | defaults: 10347312
		int __fastcall playShopSound(/*House, SoundIndex*/); // address: 0x496520
		int __thiscall doPause(/**/); // address: 0x420DB0 | defaults: 5067136
		int __thiscall doResume(/**/); // address: 0x420DF0 | defaults: 5067136
		int __stdcall getSpellDamageType(/*Spell*/); // address: 0x481A60
		int __fastcall summonObjects(/*Type, X, Y, Z, Speed, Count = 1, RandomAngle = false, Bits = 0, pItem:structs.Item [MM7+]*/); // address: 0x42AA10 | defaults: 0, 0, 0, 0, 0, 1, false, 0, 0
		int __stdcall generateChests(); // address: 0x456300
		int __stdcall processActions(); // address: 0x42ADA0
		int __stdcall calcSpellDamage(/*Spell, Skill, Mastery, MonsterHP*/); // address: 0x47F0A0
		int __thiscall endTextInput(/*State*/); // address: 0x44C920 | defaults: 0
		int __stdcall fileRead(/*pTarget, Size, Count, FileStream*/); // address: 0x4AE63C | defaults: 0, 1, 0, 0
		int __stdcall fileSeek(/*FileStream, Offset, Origin = 0*/); // address: 0x4AE5B0 | defaults: 0, 0, 0
		int __thiscall doPause2(/**/); // address: 0x420DB0 | defaults: 5067176
		int __stdcall getStatisticEffect(/*Stat*/); // address: 0x482DC0
		int __fastcall summonMonster(/*Id, X, Y, Z*/); // address: 0x4A35F0
		int __fastcall uncompress(/*pTarget, pTargetSize, pSrc, SrcSize*/); // address: 0x4A7AA0
		int __stdcall fileTell(/*FileStream*/); // address: 0x4AE458 | defaults: 0
		int __thiscall doResume2(/**/); // address: 0x420DF0 | defaults: 5067176
		int __fastcall doShowMovie(/*Name, Y, DoubleSize, ExitCurrentScreen*/); // address: 0x4A59A0 | defaults: "", 0, true, true
		bool __stdcall exitHouseScreen(); // address: 0x4A4AA0
		int __stdcall getCurrentNPCPtr(); // address: 0x43BCF0
		char* __fastcall compress(/*pTarget, pTargetSize, pSrc, SrcSize, Compression[MM7+] = -1*/); // address: 0x4A7B20 | defaults: 0, 0, 0, 0, -1
		int __thiscall loadHouseMovie(/*Name, Loop = true*/); // address: 0x4A63E0 | defaults: "", true
		int __stdcall playMapTrack(); // address: 0x454F90
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
	static_assert(offsetof(mm6::GameStructure, dialogIndexes) == 5027320);
	static_assert(offsetof(mm6::GameStructure, escMessageLastScreen) == 5027488);
	static_assert(offsetof(mm6::GameStructure, iconsLod) == 5027536);
	static_assert(offsetof(mm6::GameStructure, currentCharScreen) == 5064468);
	static_assert(offsetof(mm6::GameStructure, dialogsArray) == 5064952);
	static_assert(offsetof(mm6::GameStructure, statsNames) == 5066888);
	static_assert(offsetof(mm6::GameStructure, ctrlPressed) == 5066920);
	static_assert(offsetof(mm6::GameStructure, currentNPCDialog) == 5066944);
	static_assert(offsetof(mm6::GameStructure, currentHouseDialog) == 5066948);
	static_assert(offsetof(mm6::GameStructure, escMessageDialog) == 5066972);
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
	static_assert(offsetof(mm6::GameStructure, statusMessageBytes) == 5618692);
	static_assert(offsetof(mm6::GameStructure, mouseOverStatusMessage) == 5618892);
	static_assert(offsetof(mm6::GameStructure, mouseOverStatusMessageBytes) == 5618892);
	static_assert(offsetof(mm6::GameStructure, statusDisappearTime) == 5619092);
	static_assert(offsetof(mm6::GameStructure, houseExitMap) == 5619108);
	static_assert(offsetof(mm6::GameStructure, fontLucida) == 5619124);
	static_assert(offsetof(mm6::GameStructure, lucida_fnt) == 5619124);
	static_assert(offsetof(mm6::GameStructure, fontSmallnum) == 5619128);
	static_assert(offsetof(mm6::GameStructure, smallnum_fnt) == 5619128);
	static_assert(offsetof(mm6::GameStructure, book_fnt) == 5619132);
	static_assert(offsetof(mm6::GameStructure, fontBook) == 5619132);
	static_assert(offsetof(mm6::GameStructure, fontSpell) == 5619136);
	static_assert(offsetof(mm6::GameStructure, spell_fnt) == 5619136);
	static_assert(offsetof(mm6::GameStructure, arrus_fnt) == 5619140);
	static_assert(offsetof(mm6::GameStructure, fontArrus) == 5619140);
	static_assert(offsetof(mm6::GameStructure, create_fnt) == 5619144);
	static_assert(offsetof(mm6::GameStructure, fontCreate) == 5619144);
	static_assert(offsetof(mm6::GameStructure, comic_fnt) == 5619148);
	static_assert(offsetof(mm6::GameStructure, fontComic) == 5619148);
	static_assert(offsetof(mm6::GameStructure, autonote_fnt) == 5619152);
	static_assert(offsetof(mm6::GameStructure, fontAutonote) == 5619152);
	static_assert(offsetof(mm6::GameStructure, book2_fnt) == 5619156);
	static_assert(offsetof(mm6::GameStructure, fontBook2) == 5619156);
	static_assert(offsetof(mm6::GameStructure, cchar_fnt) == 5619164);
	static_assert(offsetof(mm6::GameStructure, fontCchar) == 5619164);
	static_assert(offsetof(mm6::GameStructure, wordWrappedText) == 5619168);
	static_assert(offsetof(mm6::GameStructure, wordWrappedTextBytes) == 5619168);
	static_assert(offsetof(mm6::GameStructure, textBuffer) == 5623264);
	static_assert(offsetof(mm6::GameStructure, textBufferBytes) == 5623264);
	static_assert(offsetof(mm6::GameStructure, textBuffer2) == 5625264);
	static_assert(offsetof(mm6::GameStructure, textBuffer2Bytes) == 5625264);
	static_assert(offsetof(mm6::GameStructure, SFTBin) == 5627272);
	static_assert(offsetof(mm6::GameStructure, TFTBin_size) == 5627296);
	static_assert(offsetof(mm6::GameStructure, TFTBin) == 5627300);
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
	static_assert(offsetof(mm6::GameStructure, textInputLimit) == 6254188);
	static_assert(offsetof(mm6::GameStructure, textInput) == 6254192);
	static_assert(offsetof(mm6::GameStructure, textInputBytes) == 6254192);
	static_assert(offsetof(mm6::GameStructure, textInputLength) == 6254449);
	static_assert(offsetof(mm6::GameStructure, textInputMode) == 6254452);
	static_assert(offsetof(mm6::GameStructure, textInputDialog) == 6254456);
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
	static_assert(offsetof(mm6::GameStructure, dist_mist) == 6461164);
	static_assert(offsetof(mm6::GameStructure, outdoorViewMul) == 6461172);
	static_assert(offsetof(mm6::GameStructure, outdoorViewDiv) == 6461176);
	static_assert(offsetof(mm6::GameStructure, mouse) == 6971664);
	static_assert(offsetof(mm6::GameStructure, scrollTxt) == 6981288);
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
		static inline mm7::GameClassKinds* const classKinds = 0;
		static inline mm7::GameClasses* const classes = 0;
		static inline mm7::DialogLogic* const dialogLogic = 0;
		static inline mm7::GameMap* const map = 0;
		static inline mm7::GameMouse* const mouse = 0;
		static inline mm7::GameParty* const party = 0;
		static inline mm7::GameRaces* const races = 0;
		static inline mm7::Weather* const weather = 0;

		static int32_t* autonoteCategory; // original offset 0x31A2044 (52043844 decimal)element size: 0x4 (4 decimal)
		static uint32_t autonoteCategory_size; // Offset/size: 0x100 (256 decimal)
		static char** autonoteTxt; // original offset 0x31A2040 (52043840 decimal)element size: 0x4 (4 decimal)
		static uint32_t autonoteTxt_size; // Offset/size: 0x100 (256 decimal)
		static int32_t* awardsSort; // original offset 0x723D04 (7486724 decimal)element size: 0x4 (4 decimal)
		static uint32_t awardsSort_size; // Offset/size: 0x69 (105 decimal)
		static char** awardsTxt; // original offset 0x723D00 (7486720 decimal)element size: 0x4 (4 decimal)
		static uint32_t awardsTxt_size; // Offset/size: 0x69 (105 decimal)
		static char** classNames; // original offset 0xAE3070 (11415664 decimal)element size: 0x4 (4 decimal)
		static uint32_t classNames_size; // Offset/size: 0x24 (36 decimal)
		static mm7::CustomLods* customLods; // original offset 0x349EB64 (55176036 decimal)
		static bool* foodGoldVisible; // original offset 0x3BB13D0 (62591952 decimal)
		static uint32_t* frameCounter; // original offset 0x5C6C70 (6057072 decimal)
		static mm7::EventLine* globalEvtLines; // original offset 0x598570 (5866864 decimal)element size: 0xC (12 decimal)
		static uint32_t* globalEvtLines_sizePtr; // Offset/size: 0x5A53B0 (5919664 decimal)
		static std::array<std::array<mm7::Item, 12>, 1>* guildItems; // original offset 0xADF894 (11401364 decimal)element size: 0x1B0 (432 decimal)
		static uint32_t guildItems_size; // Offset/size: 0x20 (32 decimal)
		static std::array<uint8_t, 89>* hostileTxt; // original offset 0x5C8B40 (6064960 decimal)element size: 0x59 (89 decimal)
		static uint32_t hostileTxt_size; // Offset/size: 0x59 (89 decimal)
		static mm7::HouseMovie* houseMovies; // original offset 0x4E5F40 (5136192 decimal)element size: 0x10 (16 decimal)
		static uint32_t houseMovies_size; // Offset/size: 0xC4 (196 decimal)
		static mm7::Events2DItem* houses; // original offset 0x5912B8 (5837496 decimal)element size: 0x34 (52 decimal)
		static uint32_t houses_size; // Offset/size: 0x20B (523 decimal)
		static mm7::ItemsTxtItem* itemsTxt; // original offset 0x5D2864 (6105188 decimal)element size: 0x30 (48 decimal)
		static uint32_t* itemsTxt_sizePtr; // Offset/size: 0x5D2860 (6105184 decimal)
		static int16_t* mapDoorSound; // original offset 0x4EFEC8 (5177032 decimal)element size: 0x2 (2 decimal)
		static uint32_t mapDoorSound_size; // Offset/size: 0x4E (78 decimal)
		static mm7::FogChances* mapFogChances; // original offset 0x31896A0 (51943072 decimal)element size: 0x4 (4 decimal)
		static uint32_t mapFogChances_size; // Offset/size: 0x4E (78 decimal)
		static mm7::MapStatsItem* mapStats; // original offset 0xD49ED40 (222948672 decimal)element size: 0x44 (68 decimal)
		static uint32_t* mapStats_sizePtr; // Offset/size: 0xD4A01F8 (222953976 decimal)
		static mm7::MissileSetup* missileSetup; // original offset 0x3BB3128 (62599464 decimal)element size: 0x1 (1 decimal)
		static uint32_t* missileSetup_sizePtr; // Offset/size: 0x3BB312C (62599468 decimal)
		static mm7::MonsterKind* monsterKinds; // original offset 0x3BB13B0 (62591920 decimal)element size: 0x8 (8 decimal)
		static uint32_t* monsterKinds_sizePtr; // Offset/size: 0x3BB13B4 (62591924 decimal)
		static mm7::MonstersTxtItem* monstersTxt; // original offset 0x5CCCC0 (6081728 decimal)element size: 0x58 (88 decimal)
		static uint32_t* monstersTxt_sizePtr; // Offset/size: 0x5D2854 (6105172 decimal)
		static mm7::NPC* NPC; // original offset 0x6003BA0 (100678560 decimal)element size: 0x4C (76 decimal)
		static uint32_t* NPC_sizePtr; // Offset/size: 0x73C014 (7585812 decimal)
		static mm7::NPC* NPCDataTxt; // original offset 0x5FF0D10 (100601104 decimal)element size: 0x4C (76 decimal)
		static uint32_t NPCDataTxt_size; // Offset/size: 0x3FB (1019 decimal)
		static std::array<char*, 2>* NPCGreet; // original offset 0x6016A30 (100756016 decimal)element size: 0x8 (8 decimal)
		static uint32_t NPCGreet_size; // Offset/size: 0xD9 (217 decimal)
		static int16_t* NPCGroup; // original offset 0x6017100 (100757760 decimal)element size: 0x2 (2 decimal)
		static uint32_t NPCGroup_size; // Offset/size: 0x3D (61 decimal)
		static std::array<char*, 2>* NPCNames; // original offset 0x3BB5910 (62609680 decimal)element size: 0x8 (8 decimal)
		static uint32_t NPCNames_size; // Offset/size: 0x2DF (735 decimal)
		static char** NPCNews; // original offset 0x6017188 (100757896 decimal)element size: 0x4 (4 decimal)
		static uint32_t NPCNews_size; // Offset/size: 0x3A (58 decimal)
		static char** NPCText; // original offset 0x3BB3FD4 (62603220 decimal)element size: 0x4 (4 decimal)
		static uint32_t NPCText_size; // Offset/size: 0x327 (807 decimal)
		static char** NPCTopic; // original offset 0x3BB3FD0 (62603216 decimal)element size: 0x4 (4 decimal)
		static uint32_t NPCTopic_size; // Offset/size: 0x315 (789 decimal)
		static mm7::PatchOptions* patchOptions; // original offset 0x330D37C (53531516 decimal)
		static char** placeMonTxt; // original offset 0x5D27D8 (6105048 decimal)element size: 0x4 (4 decimal)
		static uint32_t* placeMonTxt_sizePtr; // Offset/size: 0x5D2858 (6105176 decimal)
		static char** questsTxt; // original offset 0x722D90 (7482768 decimal)element size: 0x4 (4 decimal)
		static uint32_t questsTxt_size; // Offset/size: 0x201 (513 decimal)
		static std::array<mm7::Item, 12>* shopItems; // original offset 0xAD45B4 (11355572 decimal)element size: 0x1B0 (432 decimal)
		static uint32_t shopItems_size; // Offset/size: 0x35 (53 decimal)
		static int64_t* shopNextRefill; // original offset 0xACCEC4 (11325124 decimal)element size: 0x8 (8 decimal)
		static uint32_t shopNextRefill_size; // Offset/size: 0x35 (53 decimal)
		static std::array<mm7::Item, 12>* shopSpecialItems; // original offset 0xAD9F24 (11378468 decimal)element size: 0x1B0 (432 decimal)
		static uint32_t shopSpecialItems_size; // Offset/size: 0x35 (53 decimal)
		static int64_t* shopTheftExpireTime; // original offset 0xACD16C (11325804 decimal)element size: 0x8 (8 decimal)
		static uint32_t shopTheftExpireTime_size; // Offset/size: 0x35 (53 decimal)
		static mm7::SpcItemsTxtItem* spcItemsTxt; // original offset 0x5DC044 (6144068 decimal)element size: 0x1C (28 decimal)
		static uint32_t spcItemsTxt_size; // Offset/size: 0x48 (72 decimal)
		static mm7::StdItemsTxtItem* stdItemsTxt; // original offset 0x5DBE64 (6143588 decimal)element size: 0x14 (20 decimal)
		static uint32_t stdItemsTxt_size; // Offset/size: 0x18 (24 decimal)
		static uint8_t* titleTrackOffset; // original offset 0x3BB1378 (62591864 decimal)element size: 0x1 (1 decimal)
		static uint32_t titleTrackOffset_size; // Offset/size: 0x4 (4 decimal)
		static char** transTxt; // original offset 0x4EAF3C (5156668 decimal)element size: 0x4 (4 decimal)
		static uint32_t transTxt_size; // Offset/size: 0x1D0 (464 decimal)
		static std::array<int8_t, 4>* transportIndex; // original offset 0x4F0C90 (5180560 decimal)element size: 0x4 (4 decimal)
		static uint32_t transportIndex_size; // Offset/size: 0x14 (20 decimal)
		static mm7::TravelInfo* transportLocations; // original offset 0x4F0830 (5179440 decimal)element size: 0x20 (32 decimal)
		static uint32_t transportLocations_size; // Offset/size: 0x23 (35 decimal)

		// uint8_t* randSeed; // real size is 0 | Unknown type | 0x0 (0 decimal)
		SKIP(4386761);
		std::array<uint8_t, 1> minMeleeRecoveryTime; // Unknown type | 0x42EFC9 (4386761 decimal)
		SKIP(19266);
		// MMExt info: Number represented as a string.
		// [MM6] Index in games.lod
		// [MM7+] Index in mapstats.txt
		char* winMapIndex; // EditConstPChar - unprotect before/protect after edit | 0x433B0C (4406028 decimal)
		SKIP(114554);
		char* summonElementalC; // EditConstPChar - unprotect before/protect after edit | 0x44FA8A (4520586 decimal)
		SKIP(8);
		char* summonElementalB; // EditConstPChar - unprotect before/protect after edit | 0x44FA96 (4520598 decimal)
		SKIP(3);
		char* summonElementalA; // EditConstPChar - unprotect before/protect after edit | 0x44FA9D (4520605 decimal)
		SKIP(68036);
		// uint8_t* baseYear; // real size is 0 | Unknown type | 0x460465 (4588645 decimal)
		SKIP(24090);
		std::array<uint8_t, 4> newGameMap; // Unknown type | 0x46627F (4612735 decimal)
		SKIP(55777);
		std::array<uint8_t, 4> flyCeiling; // Unknown type | 0x473C64 (4668516 decimal) | MMExt info: 3000 in MM6, 4000 in MM7+, in MM8 it's configured per map (!Lua[[Map.OutdoorExtra.Ceiling]])
		SKIP(3243);
		std::array<uint8_t, 4> modelClimbRequirement; // Unknown type | 0x474913 (4671763 decimal) | MMExt info: Minimum required Z coordinate of the normal to climb a building surface. MM6 default is 1 (any non-vertical surface), MM7+ default is 46378, which corresponds to Lua[[46378/0x10000 = 0.7]].
		SKIP(113063);
		std::array<uint8_t, 4> maxBirthYear; // Unknown type | 0x4902BE (4784830 decimal)
		SKIP(147788);
		std::array<uint8_t, 1> dialogTopicsLimit; // Unknown type | 0x4B440E (4932622 decimal)
		SKIP(46115);
		std::array<uint8_t, 1> titleTrack; // Unknown type | 0x4BF832 (4978738 decimal)
		SKIP(140537);
		std::array<int16_t, 6> townPortalX; // 0x4E1D2C (5119276 decimal) | MMExt info: (Town portal picture: townport)
		std::array<int16_t, 6> townPortalY; // 0x4E1D38 (5119288 decimal) | MMExt info: (Town portal icons [MM7+]: tpharmndy, tpelf, tpwarlock, tpisland, tpheaven, tphell)
		std::array<int16_t, 6> townPortalWidth; // 0x4E1D44 (5119300 decimal)
		std::array<int16_t, 6> townPortalHeight; // 0x4E1D50 (5119312 decimal)
		SKIP(2940);
		int32_t currentScreen; // 0x4E28D8 (5122264 decimal) | MMExt info: :const.Screens
		SKIP(628);
		std::array<int8_t, 88> monsterClassInfoY; // 0x4E2B50 (5122896 decimal)
		SKIP(3848);
		std::array<std::array<uint8_t, 4>, 99> spellObjId; // MMExt: 1..99, here 0..98 | Unknown type | 0x4E3AB0 (5126832 decimal)
		SKIP(12);
		std::array<mm7::SpellInfo, 100> spells; // 0x4E3C48 (5127240 decimal)
		SKIP(296);
		std::array<int32_t, 6> specialEnterX; // MMExt: 1..6, here 0..5 | 0x4E4540 (5129536 decimal) | MMExt info: Used for Free Haven Sewer entrances in MM6. Negative Questbit Restrictions field in '2DEvents.txt' corresponds to array index
		std::array<int32_t, 6> specialEnterY; // MMExt: 1..6, here 0..5 | 0x4E4558 (5129560 decimal)
		std::array<int32_t, 6> specialEnterZ; // MMExt: 1..6, here 0..5 | 0x4E4570 (5129584 decimal)
		std::array<int32_t, 6> specialEnterDirection; // MMExt: 1..6, here 0..5 | 0x4E4588 (5129608 decimal)
		SKIP(15784);
		std::array<uint8_t, 20> equipStat2ItemSlot; // 0x4E8348 (5145416 decimal)
		std::array<bool, 88> monsterClassSex; // MMExt: 1..88, here 0..87 | 0x4E835C (5145436 decimal) | MMExt info: !Lua[[MonClass = (Id + 2):div(3)]]
		std::array<uint8_t, 88> monsterClassRace; // MMExt: 1..88, here 0..87 | 0x4E83B4 (5145524 decimal) | MMExt info: !Lua[[MonClass = (Id + 2):div(3)]]
		SKIP(18004);
		std::array<mm7::TownPortalTownInfo, 6> townPortalInfo; // 0x4ECA60 (5163616 decimal)
		std::array<char*, 25> playerFaces; // EditConstPChar - unprotect before/protect after edit | 0x4ECAD8 (5163736 decimal)
		SKIP(628);
		std::array<std::array<uint8_t, 25>, 49> standardPlayerSoundsCount; // MMExt: 1..49, here 0..48 | 0x4ECDB0 (5164464 decimal)
		SKIP(7);
		std::array<mm7::FaceAnimationInfo, 110> standardFaceAnimations; // 0x4ED280 (5165696 decimal)
		SKIP(1936);
		std::array<int16_t, 13> skillRecoveryTimes; // 0x4EDD80 (5168512 decimal)
		SKIP(408);
		std::array<int16_t, 99> spellSounds; // MMExt: 1..99, here 0..98 | 0x4EDF32 (5168946 decimal)
		SKIP(8768);
		std::array<char*, 19> shopBackgroundByType; // EditConstPChar - unprotect before/protect after edit | 0x4F0238 (5177912 decimal)
		SKIP(4);
		std::array<mm7::ShopItemKind, 14> shopWeaponKinds; // MMExt: 1..14, here 0..13 | 0x4F0288 (5177992 decimal)
		SKIP(4);
		std::array<std::array<mm7::ShopItemKind, 2>, 14> shopArmorKinds; // MMExt: 15..28, here 0..13 | MMExt: 1..2, here 0..1 | 0x4F0318 (5178136 decimal)
		std::array<int16_t, 13> shopMagicLevels; // MMExt: 29..41, here 0..12 | 0x4F0430 (5178416 decimal)
		SKIP(2);
		std::array<int16_t, 12> shopAlchemistLevels; // MMExt: 42..53, here 0..11 | 0x4F044C (5178444 decimal)
		SKIP(100);
		std::array<mm7::ShopItemKind, 14> shopWeaponKindsSpecial; // MMExt: 1..14, here 0..13 | 0x4F04C8 (5178568 decimal)
		SKIP(4);
		std::array<std::array<mm7::ShopItemKind, 2>, 14> shopArmorKindsSpecial; // MMExt: 15..28, here 0..13 | MMExt: 1..2, here 0..1 | 0x4F0558 (5178712 decimal)
		std::array<int16_t, 13> shopMagicLevelsSpecial; // MMExt: 29..41, here 0..12 | 0x4F0670 (5178992 decimal)
		SKIP(2);
		std::array<int16_t, 12> shopAlchemistLevelsSpecial; // MMExt: 42..53, here 0..11 | 0x4F068C (5179020 decimal)
		SKIP(200);
		std::array<int32_t, 11> guildJoinCost; // 0x4F076C (5179244 decimal)
		std::array<int16_t, 10> trainingLevels; // MMExt: 89..98, here 0..9 | 0x4F0798 (5179288 decimal)
		SKIP(4);
		std::array<int32_t, 32> guildAwards; // MMExt: 139..170, here 0..31 | 0x4F07B0 (5179312 decimal)
		SKIP(1408);
		std::array<int16_t, 32> guildSpellLevels; // MMExt: 139..170, here 0..31 | 0x4F0DB0 (5180848 decimal)
		SKIP(30956);
		int32_t turnBasedPhase; // 0x4F86DC (5211868 decimal) | MMExt info: 1 = monsters move, 2 = combat, 3 = party walking
		SKIP(53576);
		std::array<int32_t, 480> scanlineOffset; // 0x505828 (5265448 decimal)
		SKIP(3556);
		int32_t escMessageLastScreen; // 0x506D8C (5270924 decimal)
		SKIP(56);
		int32_t currentCharScreen; // 0x506DC8 (5270984 decimal) | MMExt info: :const.CharScreens
		SKIP(4);
		std::array<mm7::Dlg, 20> dialogsArray; // 0x506DD0 (5270992 decimal)
		std::array<std::array<uint8_t, 4>, 20> dialogIndexes; // Unknown type | 0x507460 (5272672 decimal)
		SKIP(792);
		bool flashHistoryBook; // 0x5077C8 (5273544 decimal)
		bool flashAutonotesBook; // 0x5077C9 (5273545 decimal)
		bool flashQuestBook; // 0x5077CA (5273546 decimal)
		SKIP(557);
		std::array<char*, 7> statsNames; // EditPChar | 0x5079F8 (5274104 decimal)
		SKIP(4);
		uint32_t ctrlPressed; // 4-byte boolean | 0x507A18 (5274136 decimal)
		SKIP(32);
		std::array<uint8_t, 4> currentNPCDialog; // Unknown type | 0x507A3C (5274172 decimal)
		std::array<uint8_t, 4> currentHouseDialog; // Unknown type | 0x507A40 (5274176 decimal)
		SKIP(24);
		std::array<uint8_t, 4> escMessageDialog; // Unknown type | 0x507A5C (5274204 decimal)
		SKIP(12);
		std::array<uint8_t, 4> currentPlayer; // Unknown type | 0x507A6C (5274220 decimal)
		bool rightButtonPressed; // 0x507A70 (5274224 decimal)
		SKIP(16331);
		uint32_t paused2; // 4-byte boolean | 0x50BA3C (5290556 decimal) | MMExt info: Updates of 3D view are paused
		SKIP(20);
		int32_t timeDelta2; // 0x50BA54 (5290580 decimal) | MMExt info: Time since last tick of updating 3D view
		SKIP(12);
		uint32_t paused; // 4-byte boolean | 0x50BA64 (5290596 decimal) | MMExt info: Game logic is paused
		SKIP(20);
		int32_t timeDelta; // 0x50BA7C (5290620 decimal) | MMExt info: Time since last tick
		SKIP(3560);
		uint32_t actionsNext_size; // 0x50C868 (5294184 decimal)
		std::array<mm7::ActionItem, 40> actionsNext; // size field offset is 0x50C868 | 0x50C86C (5294188 decimal)
		SKIP(4);
		uint32_t actions_size; // 0x50CA50 (5294672 decimal)
		std::array<mm7::ActionItem, 40> actions; // size field offset is 0x50CA50 | 0x50CA54 (5294676 decimal)
		SKIP(434300);
		union
		{
			mm7::ProgressBar progressBar; // 0x576CB0 (5729456 decimal)
			struct
			{
				SKIP(60);
				uint32_t loadingScreen; // 4-byte boolean | 0x576CEC (5729516 decimal)
			};
		};
		SKIP(68);
		uint32_t needRedraw; // 4-byte boolean | 0x576EAC (5729964 decimal)
		SKIP(106576);
		int32_t houseOwnerPic; // 0x590F00 (5836544 decimal)
		SKIP(8);
		int32_t NPCCommand; // 0x590F0C (5836556 decimal)
		int32_t dialogNPC; // 0x590F10 (5836560 decimal)
		SKIP(836);
		std::array<int32_t, 6> houseNPCs; // MMExt: 1..6, here 0..5 | 0x591258 (5837400 decimal) | MMExt info: If #Game.HouseExitMap:# isn't '0', last slot is occupied by map enter pseudo-NPC.
		// MMExt info: If #Game.HouseOwnerPic:# isn't '0', the value of '1' refers to the shop keeper and higher value needs to be reduced by 1 before accessing .
		// If #Game.HouseExitMap:# isn't '0', last slot is occupied by map enter icon.
		int32_t houseNPCSlot; // 0x591270 (5837424 decimal)
		SKIP(48);
		int32_t houseNPCSlotsCount; // 0x5912A4 (5837476 decimal)
		SKIP(128272);
		std::array<char, 2000> streetMessage; // fixed size string, requires null terminator | 0x5B07B8 (5965752 decimal) | MMExt info: Message displayed by #Message:#, #Question:#, #evt.SimpleMessage:# and #evt.Question:# when not talking to NPC.
		SKIP(8);
		uint32_t mapEvtLines_size; // 0x5B0F90 (5967760 decimal)
		SKIP(21652);
		mm7::MoveToMap moveToMap; // 0x5B6428 (5989416 decimal)
		SKIP(20);
		std::array<mm7::EventLine, 4400> mapEvtLines; // size field offset is 0x5B0F90 | 0x5B6458 (5989464 decimal)
		SKIP(16);
		union
		{
			std::array<char, 200> statusMessage; // fixed size string, requires null terminator | 0x5C32A8 (6042280 decimal)
			std::array<uint8_t, 200> statusMessageBytes; // 0x5C32A8 (6042280 decimal)
		};
		union
		{
			std::array<char, 200> mouseOverStatusMessage; // fixed size string, requires null terminator | 0x5C3370 (6042480 decimal)
			std::array<uint8_t, 200> mouseOverStatusMessageBytes; // 0x5C3370 (6042480 decimal)
		};
		int32_t statusDisappearTime; // 0x5C3438 (6042680 decimal)
		uint32_t needUpdateStatusBar; // 4-byte boolean | 0x5C343C (6042684 decimal)
		SKIP(16);
		int32_t houseExitMap; // 0x5C3450 (6042704 decimal)
		SKIP(12);
		union
		{
			int32_t autonote_fnt; // 0x5C3460 (6042720 decimal)
			mm7::Fnt* fontAutonote; // 0x5C3460 (6042720 decimal)
		};
		union
		{
			mm7::Fnt* fontSpell; // 0x5C3464 (6042724 decimal)
			int32_t spell_fnt; // 0x5C3464 (6042724 decimal)
		};
		union
		{
			int32_t arrus_fnt; // 0x5C3468 (6042728 decimal)
			mm7::Fnt* fontArrus; // 0x5C3468 (6042728 decimal)
		};
		union
		{
			mm7::Fnt* fontLucida; // 0x5C346C (6042732 decimal)
			int32_t lucida_fnt; // 0x5C346C (6042732 decimal)
		};
		union
		{
			int32_t book2_fnt; // 0x5C3470 (6042736 decimal)
			mm7::Fnt* fontBook2; // 0x5C3470 (6042736 decimal)
		};
		union
		{
			int32_t book_fnt; // 0x5C3474 (6042740 decimal)
			mm7::Fnt* fontBook; // 0x5C3474 (6042740 decimal)
		};
		SKIP(4);
		union
		{
			int32_t create_fnt; // 0x5C347C (6042748 decimal)
			mm7::Fnt* fontCreate; // 0x5C347C (6042748 decimal)
		};
		union
		{
			int32_t cchar_fnt; // 0x5C3480 (6042752 decimal)
			mm7::Fnt* fontCchar; // 0x5C3480 (6042752 decimal)
		};
		union
		{
			int32_t comic_fnt; // 0x5C3484 (6042756 decimal)
			mm7::Fnt* fontComic; // 0x5C3484 (6042756 decimal)
		};
		union
		{
			mm7::Fnt* fontSmallnum; // 0x5C3488 (6042760 decimal)
			int32_t smallnum_fnt; // 0x5C3488 (6042760 decimal)
		};
		SKIP(4004);
		union
		{
			std::array<char, 2048> wordWrappedText; // fixed size string, requires null terminator | 0x5C4430 (6046768 decimal)
			std::array<uint8_t, 2048> wordWrappedTextBytes; // 0x5C4430 (6046768 decimal) | MMExt info: Lets you get address of 'WordWrappedText' or access it byte by byte (note: traversing it like that is very slow)
		};
		SKIP(4096);
		union
		{
			std::array<char, 2000> textBuffer; // fixed size string, requires null terminator | 0x5C5C30 (6052912 decimal)
			std::array<uint8_t, 2000> textBufferBytes; // 0x5C5C30 (6052912 decimal) | MMExt info: Lets you get address of 'TextBuffer' or access it byte by byte (note: traversing it like that is very slow)
		};
		union
		{
			std::array<char, 2000> textBuffer2; // fixed size string, requires null terminator | 0x5C6400 (6054912 decimal)
			std::array<uint8_t, 2000> textBuffer2Bytes; // 0x5C6400 (6054912 decimal) | MMExt info: Lets you get address of 'TextBuffer2' or access it byte by byte (note: traversing it like that is very slow)
		};
		SKIP(104);
		uint32_t TFTBin_size; // 0x5C6C38 (6057016 decimal)
		mm7::TFTItem* TFTBin; // size field offset is 0x5C6C38 | 0x5C6C3C (6057020 decimal)
		mm7::SFT SFTBin; // 0x5C6C40 (6057024 decimal)
		SKIP(6408);
		std::array<char*, 36> classDescriptions; // EditPChar | 0x5C8560 (6063456 decimal)
		SKIP(8);
		std::array<char*, 7> statsDescriptions; // EditPChar | 0x5C85F8 (6063608 decimal)
		SKIP(124);
		std::array<char*, 37> skillDesGM; // EditPChar | 0x5C8690 (6063760 decimal)
		SKIP(4);
		std::array<char*, 37> skillDesMaster; // EditPChar | 0x5C8728 (6063912 decimal)
		SKIP(4);
		std::array<char*, 37> skillDesExpert; // EditPChar | 0x5C87C0 (6064064 decimal)
		SKIP(4);
		std::array<char*, 37> skillDesNormal; // EditPChar | 0x5C8858 (6064216 decimal)
		SKIP(4);
		std::array<char*, 37> skillDescriptions; // EditPChar | 0x5C88F0 (6064368 decimal)
		SKIP(92);
		std::array<mm7::HistoryTxtItem, 30> historyTxt; // 0x5C89E0 (6064608 decimal)
		SKIP(13160);
		std::array<mm7::SpellsTxtItem, 100> spellsTxt; // 0x5CBEB0 (6078128 decimal)
		SKIP(84740);
		std::array<std::array<int16_t, 50>, 50> potionTxt; // MMExt: 222..271, here 0..49 | MMExt: 222..271, here 0..49 | 0x5E17C4 (6166468 decimal)
		std::array<std::array<int16_t, 50>, 50> potNotesTxt; // MMExt: 222..271, here 0..49 | MMExt: 222..271, here 0..49 | 0x5E2B4C (6171468 decimal)
		SKIP(300);
		std::array<char*, 677> globalTxt; // EditPChar | 0x5E4000 (6176768 decimal)
		SKIP(1332);
		uint32_t overlayBin_size; // 0x5E4FC8 (6180808 decimal)
		mm7::OverlayItem* overlayBin; // size field offset is 0x5E4FC8 | 0x5E4FCC (6180812 decimal)
		SKIP(106484);
		uint32_t chestBin_size; // 0x5FEFC4 (6287300 decimal)
		mm7::DChestItem* chestBin; // size field offset is 0x5FEFC4 | 0x5FEFC8 (6287304 decimal)
		uint32_t monListBin_size; // 0x5FEFCC (6287308 decimal)
		mm7::MonListItem* monListBin; // MMExt: 1..0, here 0..-1 | size field offset is 0x5FEFCC | 0x5FEFD0 (6287312 decimal)
		SKIP(530012);
		uint32_t objListBin_size; // 0x680630 (6817328 decimal)
		mm7::ObjListItem* objListBin; // size field offset is 0x680630 | 0x680634 (6817332 decimal)
		SKIP(108060);
		uint32_t decListBin_size; // 0x69AC54 (6925396 decimal)
		mm7::DecListItem* decListBin; // size field offset is 0x69AC54 | 0x69AC58 (6925400 decimal)
		SKIP(48);
		std::array<int32_t, 30> keyCodes; // 0x69AC8C (6925452 decimal)
		std::array<int32_t, 30> keyTypes; // 0x69AD04 (6925572 decimal)
		int32_t textInputLimit; // 0x69AD7C (6925692 decimal)
		union
		{
			std::array<char, 257> textInput; // fixed size string, requires null terminator | 0x69AD80 (6925696 decimal)
			std::array<uint8_t, 257> textInputBytes; // 0x69AD80 (6925696 decimal)
		};
		uint8_t textInputLength; // 0x69AE81 (6925953 decimal)
		SKIP(2);
		int32_t textInputMode; // 0x69AE84 (6925956 decimal)
		std::array<uint8_t, 4> textInputDialog; // Unknown type | 0x69AE88 (6925960 decimal)
		SKIP(22548);
		mm7::Lod saveGameLod; // 0x6A06A0 (6948512 decimal)
		SKIP(4);
		mm7::Lod gamesLod; // 0x6A08E0 (6949088 decimal)
		SKIP(168);
		int32_t mainMenuCode; // 0x6A0BC4 (6949828 decimal) | MMExt info: -1 = in game, 0 = in main menu, 1 = show new game, 2 = show credits, 3 = show load menu, 4 = exit, 5 = loading game, 6 = in new game screen, 8 = in credits, 9 = load game, 10 = load level [MM7+]
		int32_t exitMapAction; // 0x6A0BC8 (6949832 decimal) | MMExt info: :const.ExitMapAction
		SKIP(119548);
		uint32_t tileBin_size; // 0x6BDEC8 (7069384 decimal)
		mm7::TileItem* tileBin; // size field offset is 0x6BDEC8 | 0x6BDECC (7069388 decimal)
		int32_t exitLevelCode; // 0x6BDED0 (7069392 decimal) | MMExt info: 0 = in game, 2 = load other map, 8 = death
		SKIP(40);
		int32_t dist_mist; // 0x6BDEFC (7069436 decimal)
		SKIP(4);
		int32_t outdoorViewMul; // 0x6BDF04 (7069444 decimal) | MMExt info: Acts as the opposite of FOV
		int32_t outdoorViewDiv; // 0x6BDF08 (7069448 decimal) | MMExt info: !Lua[[= math.floor(0x10000/Game.OutdoorViewMul)]]
		SKIP(616);
		uint32_t windowHandle; // 0x6BE174 (7070068 decimal)
		SKIP(119);
		int32_t soundVolume; // 0x6BE1EF (7070191 decimal)
		SKIP(1765);
		mm7::Lod eventsLod; // 0x6BE8D8 (7071960 decimal)
		SKIP(72060);
		mm7::BitmapsLod iconsLod; // 0x6D0490 (7144592 decimal)
		mm7::SpritesLod spritesLod; // 0x6E2048 (7217224 decimal)
		mm7::BitmapsLod bitmapsLod; // 0x6F0D00 (7277824 decimal)
		SKIP(135936);
		std::array<char*, 82> scrollTxt; // MMExt: 700..781, here 0..81 | EditPChar | 0x723BB8 (7486392 decimal)
		SKIP(81320);
		std::array<mm7::NPCProfTxtItem, 59> NPCProfTxt; // 0x737AA8 (7568040 decimal)
		std::array<mm7::NPC, 100> streetNPC; // size field offset is 0x73C010 | 0x737F44 (7569220 decimal)
		SKIP(8988);
		uint32_t streetNPC_size; // 0x73C010 (7585808 decimal)
		SKIP(12);
		std::array<int32_t, 2> NPCNamesCount; // 0x73C020 (7585824 decimal)
		SKIP(232);
		std::array<char*, 59> NPCProfNames; // EditPChar | 0x73C110 (7586064 decimal)
		SKIP(12);
		std::array<std::array<char*, 7>, 4> merchantTxt; // EditPChar | 0x73C208 (7586312 decimal)
		SKIP(3378400);
		struct // size: 0xC, MMExt union
		{
			int64_t delay; // 0xA74F58 (10964824 decimal)
			int16_t animation; // 0xA74F60 (10964832 decimal)
			int16_t playerIndex; // 0xA74F62 (10964834 decimal)
		} delayedFaceAnimation;
		static_assert(sizeof(delayedFaceAnimation) == 0xC, "Invalid \"delayedFaceAnimation\" structure size");;
		uint32_t IFTBin_size; // 0xA74F64 (10964836 decimal)
		mm7::IFTItem* IFTBin; // size field offset is 0xA74F64 | 0xA74F68 (10964840 decimal)
		uint32_t PFTBin_size; // 0xA74F6C (10964844 decimal)
		mm7::PFTItem* PFTBin; // size field offset is 0xA74F6C | 0xA74F70 (10964848 decimal)
		SKIP(360176);
		int64_t time; // 0xACCE64 (11325028 decimal) | MMExt info: Since 00 AM, January 1st, 1165/1168/1172
		SKIP(512);
		std::array<int64_t, 32> guildNextRefill; // MMExt: 139..170, here 0..31 | 0xACD06C (11325548 decimal)
		SKIP(984);
		int32_t year; // 0xACD544 (11326788 decimal) | MMExt info: Actual value, like 1172
		int32_t month; // 0xACD548 (11326792 decimal) | MMExt info: (0 - 11)
		int32_t weekOfMonth; // 0xACD54C (11326796 decimal) | MMExt info: (0 - 3)
		int32_t dayOfMonth; // 0xACD550 (11326800 decimal) | MMExt info: (0 - 27)
		int32_t hour; // 0xACD554 (11326804 decimal) | MMExt info: (0 - 23)
		int32_t minute; // 0xACD558 (11326808 decimal) | MMExt info: (0 - 59)
		int32_t second; // 0xACD55C (11326812 decimal) | MMExt info: (0 - 59)
		SKIP(340);
		uint32_t turnBased; // 4-byte boolean | 0xACD6B4 (11327156 decimal)
		SKIP(28408);
		bool needRender : 1; // 0xAD45B0 (11355568 decimal), bit index 6 | MMExt info: Same as Party.NeedRender
		SKIP(59843);
		int32_t armageddonTimeLeft; // 0xAE2F74 (11415412 decimal) | MMExt info: maximum is 417
		int32_t armageddonSkill; // 0xAE2F78 (11415416 decimal) | MMExt info: damage is 50 + skill
		std::array<int32_t, 4> turnBasedDelays; // 0xAE2F7C (11415420 decimal)
		SKIP(452);
		std::array<char*, 37> skillNames; // EditPChar | 0xAE3150 (11415888 decimal)
		SKIP(3205252);
		union
		{
			mm7::GameScreen screen; // 0xDF1A68 (14621288 decimal)
			struct
			{
				SKIP(262196);
				std::array<std::array<mm7::ObjectRef, 640>, 480>* objectByPixel; // 0xE31A9C (14883484 decimal)
				SKIP(32);
				uint32_t windowed; // 0xE31AC0 (14883520 decimal)
				SKIP(44);
				uint32_t rendererD3D; // 0xE31AF0 (14883568 decimal)
			};
		};
		SKIP(1341072);
		int32_t redbookHandle; // 0xF791FC (16224764 decimal)
		int32_t MSSHandle; // 0xF79200 (16224768 decimal)
		SKIP(2520);
		uint32_t soundsBin_size; // 0xF79BDC (16227292 decimal)
		mm7::SoundsItem* soundsBin; // size field offset is 0xF79BDC | 0xF79BE0 (16227296 decimal)
		SKIP(70660);
		std::array<int32_t, 12> guildItemIconPtr; // 0xF8AFE8 (16297960 decimal)
		int32_t housePicType; // 0xF8B018 (16298008 decimal)
		int32_t houseScreen; // 0xF8B01C (16298012 decimal)
		SKIP(8);
		int32_t houseAllowAction; // 0xF8B028 (16298024 decimal)
		int32_t houseActionInfo; // 0xF8B02C (16298028 decimal)
		int32_t houseTeachMastery; // 0xF8B030 (16298032 decimal)
		int32_t houseCost; // 0xF8B034 (16298036 decimal)
		SKIP(40);
		int32_t houseItemsCount; // 0xF8B060 (16298080 decimal) | MMExt info: Number of interactive items of the dialog. Items count of the dialog object gets changed to this or 0 depending on selected player being concious.
		SKIP(4);
		char* NPCMessage; // EditPChar | 0xF8B068 (16298088 decimal) | MMExt info: Current message displayed in a dialog with some NPC
		SKIP(2372);
		int32_t smackVideo; // 0xF8B9B0 (16300464 decimal)
		SKIP(56);
		uint32_t isMovieLooped; // 4-byte boolean | 0xF8B9EC (16300524 decimal)
		SKIP(24);
		int32_t binkVideo; // 0xF8BA08 (16300552 decimal)
		SKIP(24);
		int32_t movieKind; // 0xF8BA24 (16300580 decimal) | MMExt info: 0 - No movie, 1 - Smack, 2 - Bink
		SKIP(1594443668);
		bool __stdcall exitHouseScreen(); // address: 0x4BD818
		int __thiscall doPause2(/**/); // address: 0x4262F2 | defaults: 5290552
		int __thiscall doResume2(/**/); // address: 0x42630C | defaults: 5290552
		int __fastcall getNPCPtrFromIndex(/*Index*/); // address: 0x445A1C
		int __fastcall setInterfaceColor(/*Color, Unk = 1*/); // address: 0x422698 | defaults: 1, 1
		char* __fastcall compress(/*pTarget, pTargetSize, pSrc, SrcSize, Compression[MM7+] = -1*/); // address: 0x4C2FF0 | defaults: 0, 0, 0, 0, -1
		int __stdcall getStatisticEffect(/*Stat*/); // address: 0x48EA13
		int __fastcall doShowMovie(/*Name, Y, DoubleSize, ExitCurrentScreen*/); // address: 0x4BE671 | defaults: "", 0, true, true
		int __thiscall isMoviePlaying(/**/); // address: 0x4BF35F | defaults: 16300424
		int __thiscall loadHouseMovie(/*Name, Loop = true*/); // address: 0x4BF1F5 | defaults: "", true
		int __stdcall fileRead(/*pTarget, Size, Count, FileStream*/); // address: 0x4CB8A5 | defaults: 0, 1, 0, 0
		int __thiscall endMovie(/**/); // address: 0x4BEB3A | defaults: 16300424
		int __fastcall uncompress(/*pTarget, pTargetSize, pSrc, SrcSize*/); // address: 0x4C2F60
		int __stdcall playMapTrack(); // address: 0x4ABF53
		int __stdcall rand(); // address: 0x4CAAC2
		int __thiscall restartHouseMovie(/**/); // address: 0x4BF518 | defaults: 16300424
		int __fastcall playShopSound(/*House, SoundIndex*/); // address: 0x4B1DF5
		int __stdcall fileTell(/*FileStream*/); // address: 0x4CB669 | defaults: 0
		int __fastcall calcSpellDamage(/*Spell, Skill, Mastery, MonsterHP*/); // address: 0x43B006
		int __stdcall getSpellDamageType(/*Spell*/); // address: 0x48E189
		int __fastcall summonMonster(/*Id, X, Y, Z*/); // address: 0x4BBEC4
		int __fastcall summonObjects(/*Type, X, Y, Z, Speed, Count = 1, RandomAngle = false, Bits = 0, pItem:structs.Item [MM7+]*/); // address: 0x42F7C7 | defaults: 0, 0, 0, 0, 0, 1, false, 0, 0
		int __stdcall processActions(); // address: 0x4304D6
		int __thiscall doResume(/**/); // address: 0x42630C | defaults: 5290592
		int __stdcall generateChests(); // address: 0x450244
		int __thiscall doPause(/**/); // address: 0x4262F2 | defaults: 5290592
		int __stdcall fileSeek(/*FileStream, Offset, Origin = 0*/); // address: 0x4CB7EC | defaults: 0, 0, 0
		int __fastcall isMonsterOfKind(/*Id, Kind:const.MonsterKind*/); // address: 0x438BCE
		int __thiscall endTextInput(/*State*/); // address: 0x459F0A | defaults: 0
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
	static_assert(offsetof(mm7::GameStructure, escMessageLastScreen) == 5270924);
	static_assert(offsetof(mm7::GameStructure, currentCharScreen) == 5270984);
	static_assert(offsetof(mm7::GameStructure, dialogsArray) == 5270992);
	static_assert(offsetof(mm7::GameStructure, dialogIndexes) == 5272672);
	static_assert(offsetof(mm7::GameStructure, flashHistoryBook) == 5273544);
	static_assert(offsetof(mm7::GameStructure, flashAutonotesBook) == 5273545);
	static_assert(offsetof(mm7::GameStructure, flashQuestBook) == 5273546);
	static_assert(offsetof(mm7::GameStructure, statsNames) == 5274104);
	static_assert(offsetof(mm7::GameStructure, ctrlPressed) == 5274136);
	static_assert(offsetof(mm7::GameStructure, currentNPCDialog) == 5274172);
	static_assert(offsetof(mm7::GameStructure, currentHouseDialog) == 5274176);
	static_assert(offsetof(mm7::GameStructure, escMessageDialog) == 5274204);
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
	static_assert(offsetof(mm7::GameStructure, statusMessageBytes) == 6042280);
	static_assert(offsetof(mm7::GameStructure, mouseOverStatusMessage) == 6042480);
	static_assert(offsetof(mm7::GameStructure, mouseOverStatusMessageBytes) == 6042480);
	static_assert(offsetof(mm7::GameStructure, statusDisappearTime) == 6042680);
	static_assert(offsetof(mm7::GameStructure, needUpdateStatusBar) == 6042684);
	static_assert(offsetof(mm7::GameStructure, houseExitMap) == 6042704);
	static_assert(offsetof(mm7::GameStructure, autonote_fnt) == 6042720);
	static_assert(offsetof(mm7::GameStructure, fontAutonote) == 6042720);
	static_assert(offsetof(mm7::GameStructure, fontSpell) == 6042724);
	static_assert(offsetof(mm7::GameStructure, spell_fnt) == 6042724);
	static_assert(offsetof(mm7::GameStructure, arrus_fnt) == 6042728);
	static_assert(offsetof(mm7::GameStructure, fontArrus) == 6042728);
	static_assert(offsetof(mm7::GameStructure, fontLucida) == 6042732);
	static_assert(offsetof(mm7::GameStructure, lucida_fnt) == 6042732);
	static_assert(offsetof(mm7::GameStructure, book2_fnt) == 6042736);
	static_assert(offsetof(mm7::GameStructure, fontBook2) == 6042736);
	static_assert(offsetof(mm7::GameStructure, book_fnt) == 6042740);
	static_assert(offsetof(mm7::GameStructure, fontBook) == 6042740);
	static_assert(offsetof(mm7::GameStructure, create_fnt) == 6042748);
	static_assert(offsetof(mm7::GameStructure, fontCreate) == 6042748);
	static_assert(offsetof(mm7::GameStructure, cchar_fnt) == 6042752);
	static_assert(offsetof(mm7::GameStructure, fontCchar) == 6042752);
	static_assert(offsetof(mm7::GameStructure, comic_fnt) == 6042756);
	static_assert(offsetof(mm7::GameStructure, fontComic) == 6042756);
	static_assert(offsetof(mm7::GameStructure, fontSmallnum) == 6042760);
	static_assert(offsetof(mm7::GameStructure, smallnum_fnt) == 6042760);
	static_assert(offsetof(mm7::GameStructure, wordWrappedText) == 6046768);
	static_assert(offsetof(mm7::GameStructure, wordWrappedTextBytes) == 6046768);
	static_assert(offsetof(mm7::GameStructure, textBuffer) == 6052912);
	static_assert(offsetof(mm7::GameStructure, textBufferBytes) == 6052912);
	static_assert(offsetof(mm7::GameStructure, textBuffer2) == 6054912);
	static_assert(offsetof(mm7::GameStructure, textBuffer2Bytes) == 6054912);
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
	static_assert(offsetof(mm7::GameStructure, textInputLimit) == 6925692);
	static_assert(offsetof(mm7::GameStructure, textInput) == 6925696);
	static_assert(offsetof(mm7::GameStructure, textInputBytes) == 6925696);
	static_assert(offsetof(mm7::GameStructure, textInputLength) == 6925953);
	static_assert(offsetof(mm7::GameStructure, textInputMode) == 6925956);
	static_assert(offsetof(mm7::GameStructure, textInputDialog) == 6925960);
	static_assert(offsetof(mm7::GameStructure, saveGameLod) == 6948512);
	static_assert(offsetof(mm7::GameStructure, gamesLod) == 6949088);
	static_assert(offsetof(mm7::GameStructure, mainMenuCode) == 6949828);
	static_assert(offsetof(mm7::GameStructure, exitMapAction) == 6949832);
	static_assert(offsetof(mm7::GameStructure, tileBin_size) == 7069384);
	static_assert(offsetof(mm7::GameStructure, tileBin) == 7069388);
	static_assert(offsetof(mm7::GameStructure, exitLevelCode) == 7069392);
	static_assert(offsetof(mm7::GameStructure, dist_mist) == 7069436);
	static_assert(offsetof(mm7::GameStructure, outdoorViewMul) == 7069444);
	static_assert(offsetof(mm7::GameStructure, outdoorViewDiv) == 7069448);
	static_assert(offsetof(mm7::GameStructure, windowHandle) == 7070068);
	static_assert(offsetof(mm7::GameStructure, soundVolume) == 7070191);
	static_assert(offsetof(mm7::GameStructure, eventsLod) == 7071960);
	static_assert(offsetof(mm7::GameStructure, iconsLod) == 7144592);
	static_assert(offsetof(mm7::GameStructure, spritesLod) == 7217224);
	static_assert(offsetof(mm7::GameStructure, bitmapsLod) == 7277824);
	static_assert(offsetof(mm7::GameStructure, scrollTxt) == 7486392);
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
		static inline mm8::ArmorPicsCoords* const armorPicsCoords = 0;
		static inline mm8::CharacterVoices* const characterVoices = 0;
		static inline mm8::GameClassKinds* const classKinds = 0;
		static inline mm8::GameClasses* const classes = 0;
		static inline mm8::DialogLogic* const dialogLogic = 0;
		static inline mm8::HouseRules* const houseRules = 0;
		static inline mm8::GameMap* const map = 0;
		static inline mm8::GameMouse* const mouse = 0;
		static inline mm8::GameParty* const party = 0;
		static inline mm8::Weather* const weather = 0;

		static int32_t* autonoteCategory; // original offset 0x172C7544 (388789572 decimal)element size: 0x4 (4 decimal)
		static uint32_t autonoteCategory_size; // Offset/size: 0x2BA (698 decimal)
		static char** autonoteTxt; // original offset 0x172C7540 (388789568 decimal)element size: 0x4 (4 decimal)
		static uint32_t autonoteTxt_size; // Offset/size: 0x2BA (698 decimal)
		static int32_t* awardsSort; // original offset 0xF8E5954 (260987220 decimal)element size: 0x4 (4 decimal)
		static uint32_t awardsSort_size; // Offset/size: 0x88 (136 decimal)
		static char** awardsTxt; // original offset 0xF8E5950 (260987216 decimal)element size: 0x4 (4 decimal)
		static uint32_t awardsTxt_size; // Offset/size: 0x88 (136 decimal)
		static mm8::CharacterDollType* characterDollTypes; // original offset 0x3B1CD88 (61984136 decimal)element size: 0x2F (47 decimal)
		static uint32_t characterDollTypes_size; // Offset/size: 0x6 (6 decimal)
		static mm8::CharacterPortrait* characterPortraits; // original offset 0x6429120 (105025824 decimal)element size: 0x44 (68 decimal)
		static uint32_t characterPortraits_size; // Offset/size: 0x4D (77 decimal)
		static char** classNames; // original offset 0xBB2FD0 (12267472 decimal)element size: 0x4 (4 decimal)
		static uint32_t classNames_size; // Offset/size: 0x7A (122 decimal)
		static mm8::CustomLods* customLods; // original offset 0x349DE00 (55172608 decimal)
		static mm8::EventLine* globalEvtLines; // original offset 0x1851BC39 (408009785 decimal)element size: 0xC (12 decimal)
		static uint32_t* globalEvtLines_sizePtr; // Offset/size: 0x18500048 (407896136 decimal)
		static std::array<std::array<mm8::Item, 12>, 12>* guildItems; // original offset 0x64BB9BE (105626046 decimal)element size: 0x1440 (5184 decimal)
		static uint32_t guildItems_size; // Offset/size: 0x7 (7 decimal)
		static int64_t* guildNextRefill2; // original offset 0x649F446 (105509958 decimal)element size: 0x8 (8 decimal)
		static uint32_t guildNextRefill2_size; // Offset/size: 0x7 (7 decimal)
		static std::array<uint8_t, 218>* hostileTxt; // original offset 0xE800000 (243269632 decimal)element size: 0xDA (218 decimal)
		static uint32_t hostileTxt_size; // Offset/size: 0xDA (218 decimal)
		static mm8::HouseMovie* houseMovies; // original offset 0x7C845B0 (130565552 decimal)element size: 0x10 (16 decimal)
		static uint32_t houseMovies_size; // Offset/size: 0x1E8 (488 decimal)
		static mm8::Events2DItem* houses; // original offset 0x7B8A070 (129540208 decimal)element size: 0x34 (52 decimal)
		static uint32_t houses_size; // Offset/size: 0x649 (1609 decimal)
		static mm8::HousesExtra* housesExtra; // original offset 0x6453668 (105199208 decimal)element size: 0x4 (4 decimal)
		static uint32_t housesExtra_size; // Offset/size: 0x648 (1608 decimal)
		static uint32_t* inOODialog; // original offset 0x100614C (16802124 decimal)
		static mm8::ItemsTxtItem* itemsTxt; // original offset 0x6432FFC (105066492 decimal)element size: 0x30 (48 decimal)
		static uint32_t* itemsTxt_sizePtr; // Offset/size: 0x5EFBC8 (6224840 decimal)
		static int16_t* mapDoorSound; // original offset 0x7BDF330 (129889072 decimal)element size: 0x2 (2 decimal)
		static uint32_t mapDoorSound_size; // Offset/size: 0xF1 (241 decimal)
		static mm8::FogChances* mapFogChances; // original offset 0x3580070 (56098928 decimal)element size: 0x4 (4 decimal)
		static uint32_t mapFogChances_size; // Offset/size: 0xF1 (241 decimal)
		static mm8::MapStatsItem* mapStats; // original offset 0xE7C4770 (243025776 decimal)element size: 0x44 (68 decimal)
		static uint32_t* mapStats_sizePtr; // Offset/size: 0xE7C8774 (243042164 decimal)
		static mm8::MissileSetup* missileSetup; // original offset 0x3B14960 (61950304 decimal)element size: 0x1 (1 decimal)
		static uint32_t* missileSetup_sizePtr; // Offset/size: 0x3B14964 (61950308 decimal)
		static std::array<uint16_t, 70>* mixPotions; // original offset 0x644E5E4 (105178596 decimal)element size: 0x8C (140 decimal)
		static uint32_t mixPotions_size; // Offset/size: 0x46 (70 decimal)
		static mm8::MonsterKind* monsterKinds; // original offset 0x3B11360 (61936480 decimal)element size: 0x8 (8 decimal)
		static uint32_t* monsterKinds_sizePtr; // Offset/size: 0x3B11364 (61936484 decimal)
		static mm8::MonstersTxtItem* monstersTxt; // original offset 0xD480000 (222822400 decimal)element size: 0x60 (96 decimal)
		static uint32_t* monstersTxt_sizePtr; // Offset/size: 0x5EFBBC (6224828 decimal)
		static mm8::NPC* NPC; // original offset 0x646CDAC (105303468 decimal)element size: 0x4C (76 decimal)
		static uint32_t NPC_size; // Offset/size: 0x507 (1287 decimal)
		static mm8::NPC* NPCDataTxt; // original offset 0x6454F98 (105205656 decimal)element size: 0x4C (76 decimal)
		static uint32_t NPCDataTxt_size; // Offset/size: 0x507 (1287 decimal)
		static std::array<char*, 2>* NPCGreet; // original offset 0x6486F00 (105410304 decimal)element size: 0x8 (8 decimal)
		static uint32_t NPCGreet_size; // Offset/size: 0x174 (372 decimal)
		static int16_t* NPCGroup; // original offset 0x6487B96 (105413526 decimal)element size: 0x2 (2 decimal)
		static uint32_t NPCGroup_size; // Offset/size: 0x66 (102 decimal)
		static char** NPCNews; // original offset 0x6484C68 (105401448 decimal)element size: 0x4 (4 decimal)
		static uint32_t NPCNews_size; // Offset/size: 0x399 (921 decimal)
		static char** NPCText; // original offset 0x6488354 (105415508 decimal)element size: 0x4 (4 decimal)
		static uint32_t NPCText_size; // Offset/size: 0xB39 (2873 decimal)
		static char** NPCTopic; // original offset 0x6488350 (105415504 decimal)element size: 0x4 (4 decimal)
		static uint32_t NPCTopic_size; // Offset/size: 0x802 (2050 decimal)
		static mm8::PatchOptions* patchOptions; // original offset 0x330D364 (53531492 decimal)
		static char** placeMonTxt; // original offset 0x7C49FE0 (130326496 decimal)element size: 0x4 (4 decimal)
		static uint32_t* placeMonTxt_sizePtr; // Offset/size: 0x5EFBC0 (6224832 decimal)
		static char** questsTxt; // original offset 0x171852D0 (387470032 decimal)element size: 0x4 (4 decimal)
		static uint32_t questsTxt_size; // Offset/size: 0x80F (2063 decimal)
		static mm8::ReagentSettings* reagentSettings; // original offset 0x3B104B0 (61932720 decimal)element size: 0x4 (4 decimal)
		static uint32_t reagentSettings_size; // Offset/size: 0x2B (43 decimal)
		static std::array<mm8::Item, 12>* shopItems; // original offset 0x649F8DE (105511134 decimal)element size: 0x1B0 (432 decimal)
		static uint32_t shopItems_size; // Offset/size: 0x85 (133 decimal)
		static int64_t* shopNextRefill; // original offset 0x649EDB6 (105508278 decimal)element size: 0x8 (8 decimal)
		static uint32_t shopNextRefill_size; // Offset/size: 0x85 (133 decimal)
		static std::array<mm8::Item, 12>* shopSpecialItems; // original offset 0x64AD94E (105568590 decimal)element size: 0x1B0 (432 decimal)
		static uint32_t shopSpecialItems_size; // Offset/size: 0x85 (133 decimal)
		static int64_t* shopTheftExpireTime; // original offset 0x649F47E (105510014 decimal)element size: 0x8 (8 decimal)
		static uint32_t shopTheftExpireTime_size; // Offset/size: 0x460 (1120 decimal)
		static mm8::SpcItemsTxtItem* spcItemsTxt; // original offset 0x644D224 (105173540 decimal)element size: 0x1C (28 decimal)
		static uint32_t spcItemsTxt_size; // Offset/size: 0xB4 (180 decimal)
		static mm8::StdItemsTxtItem* stdItemsTxt; // original offset 0x644CCAC (105172140 decimal)element size: 0x14 (20 decimal)
		static uint32_t stdItemsTxt_size; // Offset/size: 0x46 (70 decimal)
		static uint8_t* titleTrackOffset; // original offset 0x3B11328 (61936424 decimal)element size: 0x1 (1 decimal)
		static uint32_t titleTrackOffset_size; // Offset/size: 0x4 (4 decimal)
		static char** transTxt; // original offset 0x3B1CED0 (61984464 decimal)element size: 0x4 (4 decimal)
		static uint32_t transTxt_size; // Offset/size: 0x10F (271 decimal)
		static std::array<int8_t, 4>* transportIndex; // original offset 0x649E72C (105506604 decimal)element size: 0x4 (4 decimal)
		static uint32_t transportIndex_size; // Offset/size: 0x38 (56 decimal)
		static mm8::TravelInfo* transportLocations; // original offset 0x500DF8 (5246456 decimal)element size: 0x20 (32 decimal)
		static uint32_t transportLocations_size; // Offset/size: 0x66 (102 decimal)

		// uint8_t* randSeed; // real size is 0 | Unknown type | 0x0 (0 decimal)
		SKIP(4381266);
		std::array<uint8_t, 1> minMeleeRecoveryTime; // Unknown type | 0x42DA52 (4381266 decimal)
		SKIP(14553);
		// MMExt info: Number represented as a string.
		// [MM6] Index in games.lod
		// [MM7+] Index in mapstats.txt
		char* winMapIndex; // EditConstPChar - unprotect before/protect after edit | 0x43132C (4395820 decimal)
		SKIP(114349);
		char* summonElementalC; // EditConstPChar - unprotect before/protect after edit | 0x44D1DD (4510173 decimal)
		SKIP(19);
		char* summonElementalB; // EditConstPChar - unprotect before/protect after edit | 0x44D1F4 (4510196 decimal)
		SKIP(3);
		char* summonElementalA; // EditConstPChar - unprotect before/protect after edit | 0x44D1FB (4510203 decimal)
		SKIP(68796);
		// uint8_t* baseYear; // real size is 0 | Unknown type | 0x45DEBB (4579003 decimal)
		SKIP(26481);
		std::array<uint8_t, 4> newGameMap; // Unknown type | 0x46462C (4605484 decimal)
		SKIP(179895);
		std::array<uint8_t, 4> maxBirthYear; // Unknown type | 0x4904E7 (4785383 decimal)
		SKIP(141777);
		std::array<uint8_t, 1> dialogTopicsLimit; // Unknown type | 0x4B2EBC (4927164 decimal)
		SKIP(42192);
		std::array<uint8_t, 1> titleTrack; // Unknown type | 0x4BD38D (4969357 decimal)
		SKIP(222282);
		int32_t currentScreen; // 0x4F37D8 (5191640 decimal) | MMExt info: :const.Screens
		SKIP(676);
		std::array<int8_t, 66> monsterClassInfoY; // 0x4F3A80 (5192320 decimal)
		SKIP(2950);
		std::array<std::array<uint8_t, 4>, 132> spellObjId; // MMExt: 1..132, here 0..131 | Unknown type | 0x4F4648 (5195336 decimal)
		SKIP(24);
		std::array<mm8::SpellInfo, 133> spells; // 0x4F4870 (5195888 decimal)
		SKIP(284);
		std::array<int32_t, 6> specialEnterX; // MMExt: 1..6, here 0..5 | 0x4F53F0 (5198832 decimal) | MMExt info: Used for Free Haven Sewer entrances in MM6. Negative Questbit Restrictions field in '2DEvents.txt' corresponds to array index
		std::array<int32_t, 6> specialEnterY; // MMExt: 1..6, here 0..5 | 0x4F5408 (5198856 decimal)
		std::array<int32_t, 6> specialEnterZ; // MMExt: 1..6, here 0..5 | 0x4F5420 (5198880 decimal)
		std::array<int32_t, 6> specialEnterDirection; // MMExt: 1..6, here 0..5 | 0x4F5438 (5198904 decimal)
		SKIP(11004);
		std::array<uint8_t, 20> equipStat2ItemSlot; // 0x4F7F4C (5209932 decimal)
		SKIP(19240);
		std::array<mm8::TownPortalTownInfo, 6> townPortalInfo; // 0x4FCA88 (5229192 decimal)
		SKIP(120);
		std::array<char*, 30> playerFaces; // EditConstPChar - unprotect before/protect after edit | 0x4FCB78 (5229432 decimal)
		SKIP(1200);
		std::array<std::array<uint8_t, 30>, 49> standardPlayerSoundsCount; // MMExt: 1..49, here 0..48 | 0x4FD0A0 (5230752 decimal)
		SKIP(2);
		std::array<mm8::FaceAnimationInfo, 110> standardFaceAnimations; // 0x4FD660 (5232224 decimal)
		SKIP(1464);
		std::array<int16_t, 13> skillRecoveryTimes; // 0x4FDF88 (5234568 decimal)
		SKIP(392);
		std::array<int16_t, 132> spellSounds; // MMExt: 1..132, here 0..131 | 0x4FE12A (5234986 decimal)
		SKIP(9662);
		std::array<mm8::ShopItemKind, 14> shopWeaponKinds; // MMExt: 1..14, here 0..13 | 0x5007F0 (5244912 decimal)
		SKIP(4);
		std::array<std::array<mm8::ShopItemKind, 2>, 14> shopArmorKinds; // MMExt: 15..28, here 0..13 | MMExt: 1..2, here 0..1 | 0x500880 (5245056 decimal)
		union
		{
			std::array<int16_t, 13> shopMagicLevels; // MMExt: 29..41, here 0..12 | 0x500998 (5245336 decimal)
			struct
			{
				SKIP(6);
				std::array<int16_t, 12> shopAlchemistLevels; // MMExt: 42..53, here 0..11 | 0x50099E (5245342 decimal)
			};
		};
		SKIP(122);
		std::array<mm8::ShopItemKind, 14> shopWeaponKindsSpecial; // MMExt: 1..14, here 0..13 | 0x500A30 (5245488 decimal)
		SKIP(4);
		std::array<std::array<mm8::ShopItemKind, 2>, 14> shopArmorKindsSpecial; // MMExt: 15..28, here 0..13 | MMExt: 1..2, here 0..1 | 0x500AC0 (5245632 decimal)
		std::array<int16_t, 13> shopMagicLevelsSpecial; // MMExt: 29..41, here 0..12 | 0x500BD8 (5245912 decimal)
		SKIP(2);
		std::array<int16_t, 12> shopAlchemistLevelsSpecial; // MMExt: 42..53, here 0..11 | 0x500BF4 (5245940 decimal)
		SKIP(292);
		std::array<int32_t, 11> guildJoinCost; // 0x500D30 (5246256 decimal)
		std::array<int16_t, 13> trainingLevels; // MMExt: 89..101, here 0..12 | 0x500D5C (5246300 decimal)
		SKIP(2);
		std::array<int32_t, 32> guildAwards; // MMExt: 139..170, here 0..31 | 0x500D78 (5246328 decimal)
		SKIP(1088);
		std::array<int16_t, 34> guildSpellLevels; // MMExt: 139..172, here 0..33 | 0x501238 (5247544 decimal)
		SKIP(2380);
		std::array<int16_t, 6> townPortalX; // 0x501BC8 (5249992 decimal) | MMExt info: (Town portal picture: townport)
		std::array<int16_t, 6> townPortalY; // 0x501BD4 (5250004 decimal) | MMExt info: (Town portal icons [MM7+]: tpharmndy, tpelf, tpwarlock, tpisland, tpheaven, tphell)
		SKIP(32956);
		int32_t turnBasedPhase; // 0x509C9C (5282972 decimal) | MMExt info: 1 = monsters move, 2 = combat, 3 = party walking
		SKIP(59656);
		int32_t currentCharScreen; // 0x5185A8 (5342632 decimal) | MMExt info: :const.CharScreens
		SKIP(3392);
		std::array<char*, 7> statsNames; // EditPChar | 0x5192EC (5346028 decimal)
		SKIP(4);
		uint32_t ctrlPressed; // 4-byte boolean | 0x51930C (5346060 decimal)
		SKIP(20);
		mm8::Dlg* currentNPCDialog; // 0x519324 (5346084 decimal) | MMExt info: If #HouseExitMap:structs.GameStructure.HouseExitMap# isn't '0', last slot is occupied by map enter pseudo-NPC.
		SKIP(40);
		std::array<uint8_t, 4> currentPlayer; // Unknown type | 0x519350 (5346128 decimal)
		bool rightButtonPressed; // 0x519354 (5346132 decimal)
		SKIP(16319);
		uint32_t paused2; // 4-byte boolean | 0x51D314 (5362452 decimal) | MMExt info: pauses updating view
		SKIP(36);
		uint32_t paused; // 4-byte boolean | 0x51D33C (5362492 decimal) | MMExt info: pauses game logic
		SKIP(20);
		int32_t timeDelta; // 0x51D354 (5362516 decimal) | MMExt info: Time since last tick
		SKIP(3568);
		uint32_t actionsNext_size; // 0x51E148 (5366088 decimal)
		std::array<mm8::ActionItem, 40> actionsNext; // size field offset is 0x51E148 | 0x51E14C (5366092 decimal)
		SKIP(4);
		uint32_t actions_size; // 0x51E330 (5366576 decimal)
		std::array<mm8::ActionItem, 40> actions; // size field offset is 0x51E330 | 0x51E334 (5366580 decimal)
		SKIP(431044);
		mm8::ProgressBar progressBar; // 0x5878D8 (5798104 decimal)
		SKIP(44);
		uint32_t loadingScreen; // 4-byte boolean | 0x587914 (5798164 decimal)
		SKIP(452);
		uint32_t needRedraw; // 4-byte boolean | 0x587ADC (5798620 decimal)
		SKIP(120984);
		int32_t NPCCommand; // 0x5A5378 (5919608 decimal)
		int32_t dialogNPC; // 0x5A537C (5919612 decimal)
		SKIP(4);
		int32_t houseOwnerPic; // 0x5A5384 (5919620 decimal)
		SKIP(832);
		std::array<int32_t, 6> houseNPCs; // MMExt: 1..6, here 0..5 | 0x5A56C8 (5920456 decimal)
		// MMExt info: If #HouseOwnerPic:structs.GameStructure.HouseOwnerPic# isn't '0', the value of '1' refers to the shop keeper and higher value needs to be reduce by 1 before accessing .
		// If #HouseExitMap:structs.GameStructure.HouseExitMap# isn't '0', last slot is occupied by map enter icon.
		int32_t houseNPCSlot; // 0x5A56E0 (5920480 decimal)
		SKIP(48);
		int32_t houseNPCSlotsCount; // 0x5A5714 (5920532 decimal)
		SKIP(135472);
		std::array<char, 2000> streetMessage; // fixed size string, requires null terminator | 0x5C6848 (6056008 decimal) | MMExt info: Message displayed by #Message:#, #Question:#, #evt.SimpleMessage:# and #evt.Question:# when not talking to NPC.
		SKIP(8);
		uint32_t mapEvtLines_size; // 0x5C7020 (6058016 decimal)
		SKIP(23700);
		mm8::MoveToMap moveToMap; // 0x5CCCB8 (6081720 decimal)
		SKIP(16);
		bool inQuestionDialog; // 0x5CCCE4 (6081764 decimal)
		SKIP(3);
		std::array<mm8::EventLine, 5000> mapEvtLines; // size field offset is 0x5C7020 | 0x5CCCE8 (6081768 decimal)
		SKIP(16);
		std::array<char, 200> statusMessage; // fixed size string, requires null terminator | 0x5DB758 (6141784 decimal)
		std::array<char, 200> mouseOverStatusMessage; // fixed size string, requires null terminator | 0x5DB820 (6141984 decimal)
		int32_t statusDisappearTime; // 0x5DB8E8 (6142184 decimal)
		SKIP(16);
		int32_t houseExitMap; // 0x5DB8FC (6142204 decimal)
		SKIP(16);
		int32_t autonote_fnt; // 0x5DB910 (6142224 decimal)
		int32_t spell_fnt; // 0x5DB914 (6142228 decimal)
		int32_t arrus_fnt; // 0x5DB918 (6142232 decimal)
		int32_t lucida_fnt; // 0x5DB91C (6142236 decimal)
		int32_t book2_fnt; // 0x5DB920 (6142240 decimal)
		int32_t book_fnt; // 0x5DB924 (6142244 decimal)
		SKIP(4);
		int32_t create_fnt; // 0x5DB92C (6142252 decimal)
		SKIP(4);
		int32_t comic_fnt; // 0x5DB934 (6142260 decimal)
		int32_t smallnum_fnt; // 0x5DB938 (6142264 decimal)
		SKIP(14244);
		std::array<char, 2000> textBuffer; // fixed size string, requires null terminator | 0x5DF0E0 (6156512 decimal)
		SKIP(6000);
		std::array<char, 2000> textBuffer2; // fixed size string, requires null terminator | 0x5E1020 (6164512 decimal)
		SKIP(6104);
		uint32_t TFTBin_size; // 0x5E2FC8 (6172616 decimal)
		mm8::TFTItem* TFTBin; // size field offset is 0x5E2FC8 | 0x5E2FCC (6172620 decimal)
		mm8::SFT SFTBin; // 0x5E2FD0 (6172624 decimal)
		SKIP(6408);
		std::array<char*, 36> classDescriptions; // EditPChar | 0x5E48F0 (6179056 decimal)
		SKIP(16);
		std::array<char*, 7> statsDescriptions; // EditPChar | 0x5E4990 (6179216 decimal)
		SKIP(132);
		std::array<char*, 40> skillDescriptionsGM; // EditPChar | 0x5E4A30 (6179376 decimal)
		std::array<char*, 40> skillDescriptionsMaster; // EditPChar | 0x5E4AD0 (6179536 decimal)
		std::array<char*, 40> skillDescriptionsExpert; // EditPChar | 0x5E4B70 (6179696 decimal)
		std::array<char*, 40> skillDescriptionsNovice; // EditPChar | 0x5E4C10 (6179856 decimal)
		std::array<char*, 39> skillDescriptions; // EditPChar | 0x5E4CB0 (6180016 decimal)
		SKIP(92);
		std::array<mm8::HistoryTxtItem, 29> historyTxt; // MMExt: 1..29, here 0..28 | 0x5E4DA8 (6180264 decimal)
		SKIP(13172);
		std::array<mm8::SpellsTxtItem, 133> spellsTxt; // 0x5E8278 (6193784 decimal)
		SKIP(87780);
		std::array<std::array<int16_t, 50>, 50> potionTxt; // MMExt: 222..271, here 0..49 | MMExt: 222..271, here 0..49 | 0x5FEC10 (6286352 decimal)
		SKIP(5296);
		std::array<char*, 750> globalTxt; // EditPChar | 0x601448 (6296648 decimal)
		SKIP(1328);
		uint32_t overlayBin_size; // 0x602530 (6300976 decimal)
		mm8::OverlayItem* overlayBin; // size field offset is 0x602530 | 0x602534 (6300980 decimal)
		SKIP(106484);
		uint32_t chestBin_size; // 0x61C52C (6407468 decimal)
		mm8::DChestItem* chestBin; // size field offset is 0x61C52C | 0x61C530 (6407472 decimal)
		uint32_t monListBin_size; // 0x61C534 (6407476 decimal)
		mm8::MonListItem* monListBin; // MMExt: 1..0, here 0..-1 | size field offset is 0x61C534 | 0x61C538 (6407480 decimal)
		SKIP(598012);
		uint32_t objListBin_size; // 0x6AE538 (7005496 decimal)
		mm8::ObjListItem* objListBin; // size field offset is 0x6AE538 | 0x6AE53C (7005500 decimal)
		SKIP(108060);
		uint32_t decListBin_size; // 0x6C8B5C (7113564 decimal)
		mm8::DecListItem* decListBin; // size field offset is 0x6C8B5C | 0x6C8B60 (7113568 decimal)
		SKIP(96);
		std::array<int32_t, 30> keyCodes; // 0x6C8BC4 (7113668 decimal)
		std::array<int32_t, 30> keyTypes; // 0x6C8C3C (7113788 decimal)
		SKIP(22852);
		mm8::Lod saveGameLod; // 0x6CE5F8 (7136760 decimal)
		SKIP(4);
		mm8::Lod gamesLod; // 0x6CE838 (7137336 decimal)
		SKIP(176);
		int32_t mainMenuCode; // 0x6CEB24 (7138084 decimal) | MMExt info: -1 = in game, 1 = show new game, 6 = in new game, 3 = load menu, 4 = exit, 2 = show credits, 8 = in credits, 9 = load game
		int32_t exitMapAction; // 0x6CEB28 (7138088 decimal) | MMExt info: :const.ExitMapAction
		SKIP(148624);
		uint32_t tile3Bin_size; // 0x6F2FBC (7286716 decimal)
		mm8::TileItem* tile3Bin; // size field offset is 0x6F2FBC | 0x6F2FC0 (7286720 decimal)
		uint32_t tile2Bin_size; // 0x6F2FC4 (7286724 decimal)
		mm8::TileItem* tile2Bin; // size field offset is 0x6F2FC4 | 0x6F2FC8 (7286728 decimal)
		uint32_t tileBin_size; // 0x6F2FCC (7286732 decimal)
		mm8::TileItem* tileBin; // size field offset is 0x6F2FCC | 0x6F2FD0 (7286736 decimal)
		mm8::CurrentTileBin* currentTileBin; // 0x6F2FD4 (7286740 decimal)
		int32_t exitLevelCode; // 0x6F2FD8 (7286744 decimal) | MMExt info: 0 = in game, 2 = load other map, 8 = death
		SKIP(48);
		int32_t outdoorViewMul; // 0x6F300C (7286796 decimal) | MMExt info: Acts as the opposite of FOV
		SKIP(1908);
		std::array<float, 4> speedModifiers; // 0x6F3784 (7288708 decimal)
		SKIP(416);
		uint32_t windowHandle; // 0x6F3934 (7289140 decimal)
		SKIP(119);
		int32_t soundVolume; // 0x6F39AF (7289263 decimal)
		SKIP(105013);
		mm8::BitmapsLod iconsLod; // 0x70D3E8 (7394280 decimal)
		SKIP(8);
		mm8::SpritesLod spritesLod; // 0x71EFA8 (7466920 decimal)
		mm8::BitmapsLod bitmapsLod; // 0x72DC60 (7527520 decimal)
		SKIP(227720);
		std::array<mm8::NPC, 100> streetNPC; // size field offset is 0x779FF4 | 0x7771A0 (7827872 decimal)
		SKIP(4260);
		uint32_t streetNPC_size; // 0x779FF4 (7839732 decimal)
		SKIP(488);
		std::array<std::array<char*, 7>, 4> merchantTxt; // EditPChar | 0x77A1E0 (7840224 decimal)
		SKIP(3378608);
		struct // size: 0xC, MMExt union
		{
			int64_t delay; // 0xAB3000 (11218944 decimal)
			int16_t animation; // 0xAB3008 (11218952 decimal)
			int16_t playerIndex; // 0xAB300A (11218954 decimal)
		} delayedFaceAnimation;
		static_assert(sizeof(delayedFaceAnimation) == 0xC, "Invalid \"delayedFaceAnimation\" structure size");;
		uint32_t IFTBin_size; // 0xAB300C (11218956 decimal)
		mm8::IFTItem* IFTBin; // size field offset is 0xAB300C | 0xAB3010 (11218960 decimal)
		uint32_t PFTBin_size; // 0xAB3014 (11218964 decimal)
		mm8::PFTItem* PFTBin; // size field offset is 0xAB3014 | 0xAB3018 (11218968 decimal)
		SKIP(450208);
		int64_t time; // 0xB20EBC (11669180 decimal) | MMExt info: Since 00 AM, January 1st, 1165/1168/1172
		SKIP(512);
		std::array<int64_t, 34> guildNextRefill; // MMExt: 139..172, here 0..33 | 0xB210C4 (11669700 decimal)
		SKIP(984);
		int32_t year; // 0xB215AC (11670956 decimal) | MMExt info: Actual value, like 1172
		int32_t month; // 0xB215B0 (11670960 decimal) | MMExt info: (0 - 11)
		int32_t weekOfMonth; // 0xB215B4 (11670964 decimal) | MMExt info: (0 - 3)
		int32_t dayOfMonth; // 0xB215B8 (11670968 decimal) | MMExt info: (0 - 27)
		int32_t hour; // 0xB215BC (11670972 decimal) | MMExt info: (0 - 23)
		int32_t minute; // 0xB215C0 (11670976 decimal) | MMExt info: (0 - 59)
		int32_t second; // 0xB215C4 (11670980 decimal) | MMExt info: (0 - 59)
		SKIP(352);
		uint32_t turnBased; // 4-byte boolean | 0xB21728 (11671336 decimal)
		SKIP(373596);
		bool needRender : 1; // 0xB7CA88 (12044936 decimal), bit index 6 | MMExt info: Same as Party.NeedRender
		SKIP(222075);
		int32_t armageddonTimeLeft; // 0xBB2E04 (12267012 decimal) | MMExt info: maximum is 417
		int32_t armageddonSkill; // 0xBB2E08 (12267016 decimal) | MMExt info: damage is 50 + skill
		std::array<int32_t, 5> turnBasedDelays; // 0xBB2E0C (12267020 decimal)
		SKIP(576);
		std::array<char*, 39> skillNames; // EditPChar | 0xBB3060 (12267616 decimal)
		SKIP(3205252);
		union
		{
			mm8::GameScreen screen; // 0xEC1980 (15473024 decimal)
			struct
			{
				SKIP(262196);
				std::array<std::array<mm8::ObjectRef, 640>, 480>* objectByPixel; // 0xF019B4 (15735220 decimal)
				SKIP(32);
				uint32_t windowed; // 0xF019D8 (15735256 decimal)
				SKIP(44);
				uint32_t rendererD3D; // 0xF01A08 (15735304 decimal)
			};
		};
		SKIP(957332);
		int32_t redbookHandle; // 0xFEB604 (16692740 decimal)
		int32_t MSSHandle; // 0xFEB608 (16692744 decimal)
		SKIP(2520);
		uint32_t soundsBin_size; // 0xFEBFE4 (16695268 decimal)
		mm8::SoundsItem* soundsBin; // size field offset is 0xFEBFE4 | 0xFEBFE8 (16695272 decimal)
		SKIP(70632);
		std::array<int32_t, 12> guildItemIconPtr; // 0xFFD3D4 (16765908 decimal)
		int32_t housePicType; // 0xFFD404 (16765956 decimal)
		int32_t houseScreen; // 0xFFD408 (16765960 decimal)
		SKIP(8);
		int32_t houseAllowAction; // 0xFFD414 (16765972 decimal)
		int32_t houseActionInfo; // 0xFFD418 (16765976 decimal)
		int32_t houseTeachMastery; // 0xFFD41C (16765980 decimal)
		int32_t houseCost; // 0xFFD420 (16765984 decimal)
		SKIP(44);
		int32_t houseItemsCount; // 0xFFD450 (16766032 decimal) | MMExt info: Number of interactive items of the dialog. Items count of the dialog object gets changed to this or 0 depending on selected player being concious.
		SKIP(4);
		char* NPCMessage; // EditPChar | 0xFFD458 (16766040 decimal) | MMExt info: Current message displayed in a dialog with some NPC
		SKIP(2380);
		int32_t smackVideo; // 0xFFDDA8 (16768424 decimal)
		SKIP(56);
		uint32_t isMovieLooped; // 4-byte boolean | 0xFFDDE4 (16768484 decimal)
		SKIP(24);
		int32_t binkVideo; // 0xFFDE00 (16768512 decimal)
		SKIP(24);
		int32_t movieKind; // 0xFFDE1C (16768540 decimal) | MMExt info: 0 - No movie, 1 - Smack, 2 - Bink
		SKIP(1594346156);
		int __stdcall playMapTrack(); // address: 0x4AA3E7
		int __fastcall doShowMovie(/*Name, Y, DoubleSize, ExitCurrentScreen*/); // address: 0x4BC1F1 | defaults: "", 0, true, true
		int __stdcall calcSpellDamage(/*Spell, Skill, Mastery, MonsterHP*/); // address: 0x438B05
		int __fastcall isMonsterOfKind(/*Id, Kind:const.MonsterKind*/); // address: 0x436542
		int __thiscall isMoviePlaying(/**/); // address: 0x4BCFA0 | defaults: 16768384
		int __stdcall getSpellDamageType(/*Spell*/); // address: 0x48D618
		int __stdcall rand(); // address: 0x4D99F2
		int __thiscall restartHouseMovie(/**/); // address: 0x4BD165 | defaults: 16768384
		int __fastcall getNPCPtrFromIndex(/*Index*/); // address: 0x442BCE
		int __fastcall summonMonster(/*Id, X, Y, Z*/); // address: 0x4BA076
		int __fastcall playShopSound(/*House, SoundIndex*/); // address: 0x4B065F
		int __fastcall uncompress(/*pTarget, pTargetSize, pSrc, SrcSize*/); // address: 0x4D1EC0
		int __stdcall processActions(); // address: 0x42EDD8
		int __stdcall getStatisticEffect(/*Stat*/); // address: 0x48E18E
		int __thiscall endMovie(/**/); // address: 0x4BC755 | defaults: 16768384
		char* __fastcall compress(/*pTarget, pTargetSize, pSrc, SrcSize, Compression[MM7+] = -1*/); // address: 0x4D1F50 | defaults: 0, 0, 0, 0, -1
		int __fastcall escMessage(/*Text, Unk = 0*/); // address: 0x41365A | defaults: "", 0
		int __thiscall loadHouseMovie(/*Name, Loop = true*/); // address: 0x4BCE28 | defaults: "", true
		int __stdcall generateChests(); // address: 0x44D96C
		bool __stdcall exitHouseScreen(); // address: 0x4BB3F8
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
	static_assert(offsetof(mm8::GameStructure, skillDescriptionsGM) == 6179376);
	static_assert(offsetof(mm8::GameStructure, skillDescriptionsMaster) == 6179536);
	static_assert(offsetof(mm8::GameStructure, skillDescriptionsExpert) == 6179696);
	static_assert(offsetof(mm8::GameStructure, skillDescriptionsNovice) == 6179856);
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
}

#pragma pack(pop)