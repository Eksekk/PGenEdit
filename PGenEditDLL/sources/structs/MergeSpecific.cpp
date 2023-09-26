#pragma once
#include "pch.h"
#include "main.h"

mm8::ShopRule* mm8::HouseRules::alchemistsSpecial = nullptr;
uint32_t mm8::HouseRules::alchemistsSpecial_size = 0;
mm8::ShopRule* mm8::HouseRules::alchemistsStandart = nullptr;
uint32_t mm8::HouseRules::alchemistsStandart_size = 0;
mm8::ArcomageRule* mm8::HouseRules::arcomage = nullptr;
uint32_t mm8::HouseRules::arcomage_size = 0;
int16_t* mm8::HouseRules::arcomageTexts = nullptr;
uint32_t mm8::HouseRules::arcomageTexts_size = 0;
mm8::ArmorShopRule* mm8::HouseRules::armorShopsSpecial = nullptr;
uint32_t mm8::HouseRules::armorShopsSpecial_size = 0;
mm8::ArmorShopRule* mm8::HouseRules::armorShopsStandart = nullptr;
uint32_t mm8::HouseRules::armorShopsStandart_size = 0;
mm8::ShopRule* mm8::HouseRules::magicShopsSpecial = nullptr;
uint32_t mm8::HouseRules::magicShopsSpecial_size = 0;
mm8::ShopRule* mm8::HouseRules::magicShopsStandart = nullptr;
uint32_t mm8::HouseRules::magicShopsStandart_size = 0;
mm8::ShopRule* mm8::HouseRules::spellbookShops = nullptr;
uint32_t mm8::HouseRules::spellbookShops_size = 0;
mm8::ShopRule* mm8::HouseRules::training = nullptr;
uint32_t mm8::HouseRules::training_size = 0;
mm8::WeaponShopRule* mm8::HouseRules::weaponShopsSpecial = nullptr;
uint32_t mm8::HouseRules::weaponShopsSpecial_size = 0;
mm8::WeaponShopRule* mm8::HouseRules::weaponShopsStandart = nullptr;
uint32_t mm8::HouseRules::weaponShopsStandart_size = 0;

std::array<uint8_t, 6>* mm8::CharacterVoices::avail = nullptr;
uint32_t mm8::CharacterVoices::avail_size = 0;
std::array<uint16_t, 100>* mm8::CharacterVoices::sounds = nullptr;
uint32_t mm8::CharacterVoices::sounds_size = 0;

std::array<mm8::EquipCoordinates, 6>* mm8::ArmorPicsCoords::armors = nullptr;
uint32_t mm8::ArmorPicsCoords::armors_size = 0;
std::array<mm8::EquipCoordinates, 6>* mm8::ArmorPicsCoords::belts = nullptr;
uint32_t mm8::ArmorPicsCoords::belts_size = 0;
std::array<mm8::EquipCoordinates, 6>* mm8::ArmorPicsCoords::boots = nullptr;
uint32_t mm8::ArmorPicsCoords::boots_size = 0;
std::array<mm8::EquipCoordsCloak, 6>* mm8::ArmorPicsCoords::cloaks = nullptr;
uint32_t mm8::ArmorPicsCoords::cloaks_size = 0;
std::array<mm8::EquipCoordinates, 6>* mm8::ArmorPicsCoords::helms = nullptr;
uint32_t mm8::ArmorPicsCoords::helms_size = 0;
