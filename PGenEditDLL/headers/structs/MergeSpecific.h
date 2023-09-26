#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm8
{
	struct ReagentSettings // size: 0x4
	{
		uint16_t item; // 0x0 (0 decimal)
		uint16_t result; // 0x2 (2 decimal)
	};
	static_assert(sizeof(mm8::ReagentSettings) == 0x4, "Invalid \"mm8::ReagentSettings\" structure size");
	static_assert(offsetof(mm8::ReagentSettings, result) == 2);



	struct HousesExtra // size: 0x4
	{
		int16_t indexByType; // 0x0 (0 decimal)
		int16_t map; // 0x2 (2 decimal)
	};
	static_assert(sizeof(mm8::HousesExtra) == 0x4, "Invalid \"mm8::HousesExtra\" structure size");
	static_assert(offsetof(mm8::HousesExtra, map) == 2);



	struct WeaponShopRule // size: 0xA
	{
		int16_t quality; // 0x0 (0 decimal)
		std::array<int16_t, 4> itemTypes; // MMExt: 1..4, here 0..3 | 0x2 (2 decimal)
	};
	static_assert(sizeof(mm8::WeaponShopRule) == 0xA, "Invalid \"mm8::WeaponShopRule\" structure size");
	static_assert(offsetof(mm8::WeaponShopRule, itemTypes) == 2);



	struct ArmorShopRule // size: 0x14
	{
		int16_t qualityShelf; // 0x0 (0 decimal)
		std::array<int16_t, 4> itemTypesShelf; // MMExt: 1..4, here 0..3 | 0x2 (2 decimal)
		int16_t qualityCase; // 0xA (10 decimal)
		std::array<int16_t, 4> itemTypesCase; // MMExt: 1..4, here 0..3 | 0xC (12 decimal)
	};
	static_assert(sizeof(mm8::ArmorShopRule) == 0x14, "Invalid \"mm8::ArmorShopRule\" structure size");
	static_assert(offsetof(mm8::ArmorShopRule, itemTypesShelf) == 2);
	static_assert(offsetof(mm8::ArmorShopRule, qualityCase) == 10);
	static_assert(offsetof(mm8::ArmorShopRule, itemTypesCase) == 12);



	struct ArcomageRule // size: 0x18
	{
		int16_t towerToWin; // 0x0 (0 decimal)
		int16_t resToWin; // 0x2 (2 decimal)
		int16_t towerAtStart; // 0x4 (4 decimal)
		int16_t wallAtStart; // 0x6 (6 decimal)
		int16_t quarry; // 0x8 (8 decimal)
		int16_t magic; // 0xA (10 decimal)
		int16_t dungeon; // 0xC (12 decimal)
		int16_t bricks; // 0xE (14 decimal)
		int16_t gems; // 0x10 (16 decimal)
		int16_t recruits; // 0x12 (18 decimal)
		int32_t ai; // 0x14 (20 decimal)
	};
	static_assert(sizeof(mm8::ArcomageRule) == 0x18, "Invalid \"mm8::ArcomageRule\" structure size");
	static_assert(offsetof(mm8::ArcomageRule, resToWin) == 2);
	static_assert(offsetof(mm8::ArcomageRule, towerAtStart) == 4);
	static_assert(offsetof(mm8::ArcomageRule, wallAtStart) == 6);
	static_assert(offsetof(mm8::ArcomageRule, quarry) == 8);
	static_assert(offsetof(mm8::ArcomageRule, magic) == 10);
	static_assert(offsetof(mm8::ArcomageRule, dungeon) == 12);
	static_assert(offsetof(mm8::ArcomageRule, bricks) == 14);
	static_assert(offsetof(mm8::ArcomageRule, gems) == 16);
	static_assert(offsetof(mm8::ArcomageRule, recruits) == 18);
	static_assert(offsetof(mm8::ArcomageRule, ai) == 20);



	struct ShopRule // size: 0x2
	{
		int16_t quality; // 0x0 (0 decimal)
	};
	static_assert(sizeof(mm8::ShopRule) == 0x2, "Invalid \"mm8::ShopRule\" structure size");



	struct HouseRules // size: 0x50124C
	{
		static mm8::ShopRule* alchemistsSpecial; // original offset 0x649E700 (105506560 decimal)element size: 0x2 (2 decimal)
		static uint32_t alchemistsSpecial_size; // Offset/size: 0x16 (22 decimal)
		static mm8::ShopRule* alchemistsStandart; // original offset 0x649E6D4 (105506516 decimal)element size: 0x2 (2 decimal)
		static uint32_t alchemistsStandart_size; // Offset/size: 0x16 (22 decimal)
		static mm8::ArcomageRule* arcomage; // original offset 0x649E854 (105506900 decimal)element size: 0x18 (24 decimal)
		static uint32_t arcomage_size; // Offset/size: 0x35 (53 decimal)
		static int16_t* arcomageTexts; // original offset 0x649ED4C (105508172 decimal)element size: 0x2 (2 decimal)
		static uint32_t arcomageTexts_size; // Offset/size: 0x35 (53 decimal)
		static mm8::ArmorShopRule* armorShopsSpecial; // original offset 0x649E324 (105505572 decimal)element size: 0x14 (20 decimal)
		static uint32_t armorShopsSpecial_size; // Offset/size: 0x28 (40 decimal)
		static mm8::ArmorShopRule* armorShopsStandart; // original offset 0x649E004 (105504772 decimal)element size: 0x14 (20 decimal)
		static uint32_t armorShopsStandart_size; // Offset/size: 0x28 (40 decimal)
		static mm8::ShopRule* magicShopsSpecial; // original offset 0x649E68C (105506444 decimal)element size: 0x2 (2 decimal)
		static uint32_t magicShopsSpecial_size; // Offset/size: 0x24 (36 decimal)
		static mm8::ShopRule* magicShopsStandart; // original offset 0x649E644 (105506372 decimal)element size: 0x2 (2 decimal)
		static uint32_t magicShopsStandart_size; // Offset/size: 0x24 (36 decimal)
		static mm8::ShopRule* spellbookShops; // original offset 0x649E80C (105506828 decimal)element size: 0x2 (2 decimal)
		static uint32_t spellbookShops_size; // Offset/size: 0x7 (7 decimal)
		static mm8::ShopRule* training; // original offset 0x649E81A (105506842 decimal)element size: 0x2 (2 decimal)
		static uint32_t training_size; // Offset/size: 0x1D (29 decimal)
		static mm8::WeaponShopRule* weaponShopsSpecial; // original offset 0x649DEA6 (105504422 decimal)element size: 0xA (10 decimal)
		static uint32_t weaponShopsSpecial_size; // Offset/size: 0x23 (35 decimal)
		static mm8::WeaponShopRule* weaponShopsStandart; // original offset 0x649DD48 (105504072 decimal)element size: 0xA (10 decimal)
		static uint32_t weaponShopsStandart_size; // Offset/size: 0x23 (35 decimal)

		SKIP(5247564);
	};
	static_assert(sizeof(mm8::HouseRules) == 0x50124C, "Invalid \"mm8::HouseRules\" structure size");



	struct CharacterVoices // size: 0x4FCB78
	{
		static std::array<uint8_t, 6>* avail; // original offset 0x3B1BB98 (61979544 decimal)element size: 0x6 (6 decimal)
		static uint32_t avail_size; // Offset/size: 0x4F (79 decimal)
		static std::array<uint16_t, 100>* sounds; // original offset 0x3B17DE0 (61963744 decimal)element size: 0xC8 (200 decimal)
		static uint32_t sounds_size; // Offset/size: 0x4F (79 decimal)

		SKIP(5229432);
	};
	static_assert(sizeof(mm8::CharacterVoices) == 0x4FCB78, "Invalid \"mm8::CharacterVoices\" structure size");



	struct CharacterPortrait // size: 0x44
	{
		uint8_t dollType; // 0x0 (0 decimal)
		uint8_t defClass; // 0x1 (1 decimal)
		uint8_t defVoice; // 0x2 (2 decimal)
		uint8_t defSex; // 0x3 (3 decimal)
		uint8_t availableAtStart; // 0x4 (4 decimal)
		int16_t bodyX; // 0x5 (5 decimal)
		int16_t bodyY; // 0x7 (7 decimal)
		char* background; // EditPChar | 0x9 (9 decimal)
		char* body; // EditPChar | 0xD (13 decimal)
		char* head; // EditPChar | 0x11 (17 decimal)
		char* LHd; // EditPChar | 0x15 (21 decimal)
		char* LHu; // EditPChar | 0x19 (25 decimal)
		char* LHo; // EditPChar | 0x1D (29 decimal)
		char* RHb; // EditPChar | 0x21 (33 decimal)
		char* unk1; // EditPChar | 0x25 (37 decimal)
		char* unk2; // EditPChar | 0x29 (41 decimal)
		char* RHd; // EditPChar | 0x2D (45 decimal)
		char* RHu; // EditPChar | 0x31 (49 decimal)
		char* facePrefix; // EditPChar | 0x35 (53 decimal)
		uint16_t defAttackM; // 0x39 (57 decimal)
		uint16_t defAttackR; // 0x3B (59 decimal)
		uint16_t NPCPic; // 0x3D (61 decimal)
		uint8_t race; // 0x3F (63 decimal)
		int16_t helmX; // 0x40 (64 decimal)
		int16_t helmY; // 0x42 (66 decimal)
	};
	static_assert(sizeof(mm8::CharacterPortrait) == 0x44, "Invalid \"mm8::CharacterPortrait\" structure size");
	static_assert(offsetof(mm8::CharacterPortrait, defClass) == 1);
	static_assert(offsetof(mm8::CharacterPortrait, defVoice) == 2);
	static_assert(offsetof(mm8::CharacterPortrait, defSex) == 3);
	static_assert(offsetof(mm8::CharacterPortrait, availableAtStart) == 4);
	static_assert(offsetof(mm8::CharacterPortrait, bodyX) == 5);
	static_assert(offsetof(mm8::CharacterPortrait, bodyY) == 7);
	static_assert(offsetof(mm8::CharacterPortrait, background) == 9);
	static_assert(offsetof(mm8::CharacterPortrait, body) == 13);
	static_assert(offsetof(mm8::CharacterPortrait, head) == 17);
	static_assert(offsetof(mm8::CharacterPortrait, LHd) == 21);
	static_assert(offsetof(mm8::CharacterPortrait, LHu) == 25);
	static_assert(offsetof(mm8::CharacterPortrait, LHo) == 29);
	static_assert(offsetof(mm8::CharacterPortrait, RHb) == 33);
	static_assert(offsetof(mm8::CharacterPortrait, unk1) == 37);
	static_assert(offsetof(mm8::CharacterPortrait, unk2) == 41);
	static_assert(offsetof(mm8::CharacterPortrait, RHd) == 45);
	static_assert(offsetof(mm8::CharacterPortrait, RHu) == 49);
	static_assert(offsetof(mm8::CharacterPortrait, facePrefix) == 53);
	static_assert(offsetof(mm8::CharacterPortrait, defAttackM) == 57);
	static_assert(offsetof(mm8::CharacterPortrait, defAttackR) == 59);
	static_assert(offsetof(mm8::CharacterPortrait, NPCPic) == 61);
	static_assert(offsetof(mm8::CharacterPortrait, race) == 63);
	static_assert(offsetof(mm8::CharacterPortrait, helmX) == 64);
	static_assert(offsetof(mm8::CharacterPortrait, helmY) == 66);



	struct CharacterDollType // size: 0x2F
	{
		bool bow; // 0x0 (0 decimal)
		bool armor; // 0x1 (1 decimal)
		bool helm; // 0x2 (2 decimal)
		bool belt; // 0x3 (3 decimal)
		bool boots; // 0x4 (4 decimal)
		bool cloak; // 0x5 (5 decimal)
		bool weapon; // 0x6 (6 decimal)
		int16_t RHoX; // 0x7 (7 decimal)
		int16_t RHoY; // 0x9 (9 decimal)
		int16_t RHcX; // 0xB (11 decimal)
		int16_t RHcY; // 0xD (13 decimal)
		int16_t RHfX; // 0xF (15 decimal)
		int16_t RHfY; // 0x11 (17 decimal)
		int16_t LHoX; // 0x13 (19 decimal)
		int16_t LHoY; // 0x15 (21 decimal)
		int16_t LHcX; // 0x17 (23 decimal)
		int16_t LHcY; // 0x19 (25 decimal)
		int16_t LHfX; // 0x1B (27 decimal)
		int16_t LHfY; // 0x1D (29 decimal)
		int16_t OHOffsetX; // 0x1F (31 decimal)
		int16_t OHOffsetY; // 0x21 (33 decimal)
		int16_t MHOffsetX; // 0x23 (35 decimal)
		int16_t MHOffsetY; // 0x25 (37 decimal)
		int16_t bowX; // 0x27 (39 decimal)
		int16_t bowY; // 0x29 (41 decimal)
		int16_t shieldX; // 0x2B (43 decimal)
		int16_t shieldY; // 0x2D (45 decimal)
	};
	static_assert(sizeof(mm8::CharacterDollType) == 0x2F, "Invalid \"mm8::CharacterDollType\" structure size");
	static_assert(offsetof(mm8::CharacterDollType, armor) == 1);
	static_assert(offsetof(mm8::CharacterDollType, helm) == 2);
	static_assert(offsetof(mm8::CharacterDollType, belt) == 3);
	static_assert(offsetof(mm8::CharacterDollType, boots) == 4);
	static_assert(offsetof(mm8::CharacterDollType, cloak) == 5);
	static_assert(offsetof(mm8::CharacterDollType, weapon) == 6);
	static_assert(offsetof(mm8::CharacterDollType, RHoX) == 7);
	static_assert(offsetof(mm8::CharacterDollType, RHoY) == 9);
	static_assert(offsetof(mm8::CharacterDollType, RHcX) == 11);
	static_assert(offsetof(mm8::CharacterDollType, RHcY) == 13);
	static_assert(offsetof(mm8::CharacterDollType, RHfX) == 15);
	static_assert(offsetof(mm8::CharacterDollType, RHfY) == 17);
	static_assert(offsetof(mm8::CharacterDollType, LHoX) == 19);
	static_assert(offsetof(mm8::CharacterDollType, LHoY) == 21);
	static_assert(offsetof(mm8::CharacterDollType, LHcX) == 23);
	static_assert(offsetof(mm8::CharacterDollType, LHcY) == 25);
	static_assert(offsetof(mm8::CharacterDollType, LHfX) == 27);
	static_assert(offsetof(mm8::CharacterDollType, LHfY) == 29);
	static_assert(offsetof(mm8::CharacterDollType, OHOffsetX) == 31);
	static_assert(offsetof(mm8::CharacterDollType, OHOffsetY) == 33);
	static_assert(offsetof(mm8::CharacterDollType, MHOffsetX) == 35);
	static_assert(offsetof(mm8::CharacterDollType, MHOffsetY) == 37);
	static_assert(offsetof(mm8::CharacterDollType, bowX) == 39);
	static_assert(offsetof(mm8::CharacterDollType, bowY) == 41);
	static_assert(offsetof(mm8::CharacterDollType, shieldX) == 43);
	static_assert(offsetof(mm8::CharacterDollType, shieldY) == 45);



	struct EquipCoordsCloak // size: 0x8
	{
		int16_t x; // 0x0 (0 decimal)
		int16_t y; // 0x2 (2 decimal)
		int16_t colX; // 0x4 (4 decimal)
		int16_t colY; // 0x6 (6 decimal)
	};
	static_assert(sizeof(mm8::EquipCoordsCloak) == 0x8, "Invalid \"mm8::EquipCoordsCloak\" structure size");
	static_assert(offsetof(mm8::EquipCoordsCloak, y) == 2);
	static_assert(offsetof(mm8::EquipCoordsCloak, colX) == 4);
	static_assert(offsetof(mm8::EquipCoordsCloak, colY) == 6);



	struct EquipCoordinates // size: 0x4
	{
		int16_t x; // 0x0 (0 decimal)
		int16_t y; // 0x2 (2 decimal)
	};
	static_assert(sizeof(mm8::EquipCoordinates) == 0x4, "Invalid \"mm8::EquipCoordinates\" structure size");
	static_assert(offsetof(mm8::EquipCoordinates, y) == 2);



	struct ArmorPicsCoords // size: 0x4F5AB8
	{
		static std::array<mm8::EquipCoordinates, 6>* armors; // original offset 0x18562A10 (408300048 decimal)element size: 0x18 (24 decimal)
		static uint32_t armors_size; // Offset/size: 0x37 (55 decimal)
		static std::array<mm8::EquipCoordinates, 6>* belts; // original offset 0x18563310 (408302352 decimal)element size: 0x18 (24 decimal)
		static uint32_t belts_size; // Offset/size: 0x13 (19 decimal)
		static std::array<mm8::EquipCoordinates, 6>* boots; // original offset 0x185634D8 (408302808 decimal)element size: 0x18 (24 decimal)
		static uint32_t boots_size; // Offset/size: 0x15 (21 decimal)
		static std::array<mm8::EquipCoordsCloak, 6>* cloaks; // original offset 0x185636D0 (408303312 decimal)element size: 0x30 (48 decimal)
		static uint32_t cloaks_size; // Offset/size: 0x19 (25 decimal)
		static std::array<mm8::EquipCoordinates, 6>* helms; // original offset 0x18562F38 (408301368 decimal)element size: 0x18 (24 decimal)
		static uint32_t helms_size; // Offset/size: 0x29 (41 decimal)

		SKIP(5200568);
	};
	static_assert(sizeof(mm8::ArmorPicsCoords) == 0x4F5AB8, "Invalid \"mm8::ArmorPicsCoords\" structure size");
}

#pragma pack(pop)