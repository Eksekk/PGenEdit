#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm8
{
	struct ArmorShopRule // size: 0x14
	{
		int16_t qualityShelf;
		std::array<int16_t, 4> itemTypesShelf; // MMExt: 1..4, here 0..3
		int16_t qualityCase;
		std::array<int16_t, 4> itemTypesCase; // MMExt: 1..4, here 0..3
	};
	static_assert(sizeof(mm8::ArmorShopRule) == 0x14, "Invalid \"mm8::ArmorShopRule\" structure size");
	static_assert(offsetof(mm8::ArmorShopRule, itemTypesShelf) == 2);
	static_assert(offsetof(mm8::ArmorShopRule, qualityCase) == 10);
	static_assert(offsetof(mm8::ArmorShopRule, itemTypesCase) == 12);



	struct ShopRule // size: 0x2
	{
		int16_t quality;
	};
	static_assert(sizeof(mm8::ShopRule) == 0x2, "Invalid \"mm8::ShopRule\" structure size");



	struct WeaponShopRule // size: 0xA
	{
		int16_t quality;
		std::array<int16_t, 4> itemTypes; // MMExt: 1..4, here 0..3
	};
	static_assert(sizeof(mm8::WeaponShopRule) == 0xA, "Invalid \"mm8::WeaponShopRule\" structure size");
	static_assert(offsetof(mm8::WeaponShopRule, itemTypes) == 2);



	struct ArcomageRule // size: 0x18
	{
		int16_t towerToWin;
		int16_t resToWin;
		int16_t towerAtStart;
		int16_t wallAtStart;
		int16_t quarry;
		int16_t magic;
		int16_t dungeon;
		int16_t bricks;
		int16_t gems;
		int16_t recruits;
		int32_t ai;
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



	struct HouseRules // size: 0x1CB33A7E
	{
		SKIP(481503760);
		std::array<mm8::WeaponShopRule, 35> weaponShopsStandart; // MMExt: 1..35, here 0..34
		std::array<mm8::WeaponShopRule, 35> weaponShopsSpecial; // MMExt: 1..35, here 0..34
		std::array<mm8::ArmorShopRule, 40> armorShopsStandart; // MMExt: 1..40, here 0..39
		std::array<mm8::ArmorShopRule, 40> armorShopsSpecial; // MMExt: 1..40, here 0..39
		std::array<mm8::ShopRule, 36> magicShopsStandart; // MMExt: 1..36, here 0..35
		std::array<mm8::ShopRule, 36> magicShopsSpecial; // MMExt: 1..36, here 0..35
		std::array<mm8::ShopRule, 22> alchemistsStandart; // MMExt: 1..22, here 0..21
		std::array<mm8::ShopRule, 22> alchemistsSpecial; // MMExt: 1..22, here 0..21
		SKIP(224);
		std::array<mm8::ShopRule, 7> spellbookShops; // MMExt: 1..7, here 0..6
		std::array<mm8::ShopRule, 29> training; // MMExt: 1..29, here 0..28
		std::array<mm8::ArcomageRule, 53> arcomage; // MMExt: 1..53, here 0..52
		std::array<int16_t, 53> arcomageTexts; // MMExt: 1..53, here 0..52
	};
	static_assert(sizeof(mm8::HouseRules) == 0x1CB33A7E, "Invalid \"mm8::HouseRules\" structure size");
	static_assert(offsetof(mm8::HouseRules, weaponShopsStandart) == 481503760);
	static_assert(offsetof(mm8::HouseRules, weaponShopsSpecial) == 481504110);
	static_assert(offsetof(mm8::HouseRules, armorShopsStandart) == 481504460);
	static_assert(offsetof(mm8::HouseRules, armorShopsSpecial) == 481505260);
	static_assert(offsetof(mm8::HouseRules, magicShopsStandart) == 481506060);
	static_assert(offsetof(mm8::HouseRules, magicShopsSpecial) == 481506132);
	static_assert(offsetof(mm8::HouseRules, alchemistsStandart) == 481506204);
	static_assert(offsetof(mm8::HouseRules, alchemistsSpecial) == 481506248);
	static_assert(offsetof(mm8::HouseRules, spellbookShops) == 481506516);
	static_assert(offsetof(mm8::HouseRules, training) == 481506530);
	static_assert(offsetof(mm8::HouseRules, arcomage) == 481506588);
	static_assert(offsetof(mm8::HouseRules, arcomageTexts) == 481507860);



	struct CharacterDollType // size: 0x2F
	{
		bool bow;
		bool armor;
		bool helm;
		bool belt;
		bool boots;
		bool cloak;
		bool weapon;
		int16_t RHoX;
		int16_t RHoY;
		int16_t RHcX;
		int16_t RHcY;
		int16_t RHfX;
		int16_t RHfY;
		int16_t LHoX;
		int16_t LHoY;
		int16_t LHcX;
		int16_t LHcY;
		int16_t LHfX;
		int16_t LHfY;
		int16_t OHOffsetX;
		int16_t OHOffsetY;
		int16_t MHOffsetX;
		int16_t MHOffsetY;
		int16_t bowX;
		int16_t bowY;
		int16_t shieldX;
		int16_t shieldY;
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



	struct HousesExtra // size: 0x4
	{
		int16_t indexByType;
		int16_t map;
	};
	static_assert(sizeof(mm8::HousesExtra) == 0x4, "Invalid \"mm8::HousesExtra\" structure size");
	static_assert(offsetof(mm8::HousesExtra, map) == 2);



	struct EquipCoordsCloak // size: 0x8
	{
		int16_t x;
		int16_t y;
		int16_t colX;
		int16_t colY;
	};
	static_assert(sizeof(mm8::EquipCoordsCloak) == 0x8, "Invalid \"mm8::EquipCoordsCloak\" structure size");
	static_assert(offsetof(mm8::EquipCoordsCloak, y) == 2);
	static_assert(offsetof(mm8::EquipCoordsCloak, colX) == 4);
	static_assert(offsetof(mm8::EquipCoordsCloak, colY) == 6);



	struct EquipCoordinates // size: 0x4
	{
		int16_t x;
		int16_t y;
	};
	static_assert(sizeof(mm8::EquipCoordinates) == 0x4, "Invalid \"mm8::EquipCoordinates\" structure size");
	static_assert(offsetof(mm8::EquipCoordinates, y) == 2);



	struct ArmorPicsCoords // size: 0x46CBAC8
	{
		SKIP(74230224);
		std::array<std::array<mm8::EquipCoordinates, 6>, 54> armors; // MMExt: 1..54, here 0..53
		std::array<std::array<mm8::EquipCoordinates, 6>, 40> helms; // MMExt: 1..40, here 0..39
		std::array<std::array<mm8::EquipCoordinates, 6>, 18> belts; // MMExt: 1..18, here 0..17
		std::array<std::array<mm8::EquipCoordinates, 6>, 21> boots; // MMExt: 1..21, here 0..20
		std::array<std::array<mm8::EquipCoordsCloak, 6>, 24> cloaks; // MMExt: 1..24, here 0..23
	};
	static_assert(sizeof(mm8::ArmorPicsCoords) == 0x46CBAC8, "Invalid \"mm8::ArmorPicsCoords\" structure size");
	static_assert(offsetof(mm8::ArmorPicsCoords, armors) == 74230224);
	static_assert(offsetof(mm8::ArmorPicsCoords, helms) == 74231520);
	static_assert(offsetof(mm8::ArmorPicsCoords, belts) == 74232480);
	static_assert(offsetof(mm8::ArmorPicsCoords, boots) == 74232912);
	static_assert(offsetof(mm8::ArmorPicsCoords, cloaks) == 74233416);



	struct ReagentSettings // size: 0x4
	{
		uint16_t item;
		uint16_t result;
	};
	static_assert(sizeof(mm8::ReagentSettings) == 0x4, "Invalid \"mm8::ReagentSettings\" structure size");
	static_assert(offsetof(mm8::ReagentSettings, result) == 2);



	struct CharacterVoices // size: 0x4729DF2
	{
		SKIP(74604128);
		std::array<std::array<uint16_t, 100>, 79> sounds;
		std::array<std::array<uint8_t, 6>, 79> avail;
	};
	static_assert(sizeof(mm8::CharacterVoices) == 0x4729DF2, "Invalid \"mm8::CharacterVoices\" structure size");
	static_assert(offsetof(mm8::CharacterVoices, sounds) == 74604128);
	static_assert(offsetof(mm8::CharacterVoices, avail) == 74619928);



	struct CharacterPortrait // size: 0x44
	{
		uint8_t dollType;
		uint8_t defClass;
		uint8_t defVoice;
		uint8_t defSex;
		uint8_t availableAtStart;
		int16_t bodyX;
		int16_t bodyY;
		char* background; // EditPChar
		char* body; // EditPChar
		char* head; // EditPChar
		char* LHd; // EditPChar
		char* LHu; // EditPChar
		char* LHo; // EditPChar
		char* RHb; // EditPChar
		char* unk1; // EditPChar
		char* unk2; // EditPChar
		char* RHd; // EditPChar
		char* RHu; // EditPChar
		char* facePrefix; // EditPChar
		uint16_t defAttackM;
		uint16_t defAttackR;
		uint16_t NPCPic;
		uint8_t race;
		int16_t helmX;
		int16_t helmY;
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
}

#pragma pack(pop)