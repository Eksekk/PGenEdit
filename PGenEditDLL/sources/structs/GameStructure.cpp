#pragma once
#include "pch.h"
#include "main.h"
#include "GameMisc.h"
#include "Lod.h"
#include "Bin.h"
#include "GameDataStructs.h"
#include "Common.h"
#include "TxtFileItems.h"
#include "GameMap.h"
#include "Monster.h"
#include "GameParty.h"
#include "Player.h"
#include "MapModel.h"
#include "MapElements.h"
#include "MapMisc.h"
#include "Arcomage.h"
#include "MergeSpecific.h"

char** mm6::GameStructure::autonoteTxt = nullptr;
uint32_t mm6::GameStructure::autonoteTxt_size = 0;
int32_t* mm6::GameStructure::awardsSort = nullptr;
uint32_t* mm6::GameStructure::awardsSort_sizePtr = nullptr;
char** mm6::GameStructure::awardsTxt = nullptr;
uint32_t mm6::GameStructure::awardsTxt_size = 0;
char** mm6::GameStructure::classNames = nullptr;
uint32_t mm6::GameStructure::classNames_size = 0;
mm6::CustomLods* mm6::GameStructure::customLods = nullptr;
uint32_t* mm6::GameStructure::frameCounter = nullptr;
mm6::EventLine* mm6::GameStructure::globalEvtLines = nullptr;
uint32_t* mm6::GameStructure::globalEvtLines_sizePtr = nullptr;
std::array<std::array<mm6::Item, 12>, 1>* mm6::GameStructure::guildItems = nullptr;
uint32_t mm6::GameStructure::guildItems_size = 0;
mm6::HouseMovie* mm6::GameStructure::houseMovies = nullptr;
uint32_t mm6::GameStructure::houseMovies_size = 0;
mm6::Events2DItem* mm6::GameStructure::houses = nullptr;
uint32_t mm6::GameStructure::houses_size = 0;
mm6::ItemsTxtItem* mm6::GameStructure::itemsTxt = nullptr;
uint32_t* mm6::GameStructure::itemsTxt_sizePtr = nullptr;
int16_t* mm6::GameStructure::mapDoorSound = nullptr;
uint32_t mm6::GameStructure::mapDoorSound_size = 0;
mm6::FogChances* mm6::GameStructure::mapFogChances = nullptr;
uint32_t mm6::GameStructure::mapFogChances_size = 0;
mm6::MapStatsItem* mm6::GameStructure::mapStats = nullptr;
uint32_t* mm6::GameStructure::mapStats_sizePtr = nullptr;
mm6::MissileSetup* mm6::GameStructure::missileSetup = nullptr;
uint32_t* mm6::GameStructure::missileSetup_sizePtr = nullptr;
mm6::MonstersTxtItem* mm6::GameStructure::monstersTxt = nullptr;
uint32_t* mm6::GameStructure::monstersTxt_sizePtr = nullptr;
mm6::NPC* mm6::GameStructure::NPC = nullptr;
uint32_t* mm6::GameStructure::NPC_sizePtr = nullptr;
mm6::NPC* mm6::GameStructure::NPCDataTxt = nullptr;
uint32_t mm6::GameStructure::NPCDataTxt_size = 0;
std::array<char*, 2>* mm6::GameStructure::NPCNames = nullptr;
uint32_t mm6::GameStructure::NPCNames_size = 0;
mm6::NPCNewsItem* mm6::GameStructure::NPCNews = nullptr;
uint32_t mm6::GameStructure::NPCNews_size = 0;
char** mm6::GameStructure::NPCText = nullptr;
uint32_t mm6::GameStructure::NPCText_size = 0;
char** mm6::GameStructure::NPCTopic = nullptr;
uint32_t mm6::GameStructure::NPCTopic_size = 0;
mm6::PatchOptions* mm6::GameStructure::patchOptions = nullptr;
char** mm6::GameStructure::questsTxt = nullptr;
uint32_t mm6::GameStructure::questsTxt_size = 0;
std::array<mm6::Item, 12>* mm6::GameStructure::shopItems = nullptr;
uint32_t mm6::GameStructure::shopItems_size = 0;
int64_t* mm6::GameStructure::shopNextRefill = nullptr;
uint32_t mm6::GameStructure::shopNextRefill_size = 0;
std::array<mm6::Item, 12>* mm6::GameStructure::shopSpecialItems = nullptr;
uint32_t mm6::GameStructure::shopSpecialItems_size = 0;
mm6::SpcItemsTxtItem* mm6::GameStructure::spcItemsTxt = nullptr;
uint32_t mm6::GameStructure::spcItemsTxt_size = 0;
mm6::StdItemsTxtItem* mm6::GameStructure::stdItemsTxt = nullptr;
uint32_t mm6::GameStructure::stdItemsTxt_size = 0;
uint8_t* mm6::GameStructure::titleTrackOffset = nullptr;
uint32_t mm6::GameStructure::titleTrackOffset_size = 0;
char** mm6::GameStructure::transTxt = nullptr;
uint32_t mm6::GameStructure::transTxt_size = 0;
std::array<int8_t, 3>* mm6::GameStructure::transportIndex = nullptr;
uint32_t mm6::GameStructure::transportIndex_size = 0;
mm6::TravelInfo* mm6::GameStructure::transportLocations = nullptr;
uint32_t mm6::GameStructure::transportLocations_size = 0;

int mm6::GameStructure::endMovie(/**/)
{
	return 0;
}

int mm6::GameStructure::rand()
{
	return 0;
}

int mm6::GameStructure::restartHouseMovie(/**/)
{
	return 0;
}

int mm6::GameStructure::playShopSound(/*House, SoundIndex*/)
{
	return 0;
}

int mm6::GameStructure::doPause(/**/)
{
	return 0;
}

int mm6::GameStructure::doResume(/**/)
{
	return 0;
}

int mm6::GameStructure::getSpellDamageType(/*Spell*/)
{
	return 0;
}

int mm6::GameStructure::summonObjects(/*Type, X, Y, Z, Speed, Count = 1, RandomAngle = false, Bits = 0, pItem:structs.Item [MM7+]*/)
{
	return 0;
}

int mm6::GameStructure::generateChests()
{
	return 0;
}

int mm6::GameStructure::processActions()
{
	return 0;
}

int mm6::GameStructure::calcSpellDamage(/*Spell, Skill, Mastery, MonsterHP*/)
{
	return 0;
}

int mm6::GameStructure::endTextInput(/*State*/)
{
	return 0;
}

int mm6::GameStructure::fileRead(/*pTarget, Size, Count, FileStream*/)
{
	return 0;
}

int mm6::GameStructure::fileSeek(/*FileStream, Offset, Origin = 0*/)
{
	return 0;
}

int mm6::GameStructure::doPause2(/**/)
{
	return 0;
}

int mm6::GameStructure::getStatisticEffect(/*Stat*/)
{
	return 0;
}

int mm6::GameStructure::summonMonster(/*Id, X, Y, Z*/)
{
	return 0;
}

int mm6::GameStructure::uncompress(/*pTarget, pTargetSize, pSrc, SrcSize*/)
{
	return 0;
}

int mm6::GameStructure::fileTell(/*FileStream*/)
{
	return 0;
}

int mm6::GameStructure::doResume2(/**/)
{
	return 0;
}

int mm6::GameStructure::doShowMovie(/*Name, Y, DoubleSize, ExitCurrentScreen*/)
{
	return 0;
}

bool mm6::GameStructure::exitHouseScreen()
{
	return false;
}

int mm6::GameStructure::getCurrentNPCPtr()
{
	return 0;
}

char* mm6::GameStructure::compress(/*pTarget, pTargetSize, pSrc, SrcSize, Compression[MM7+] = -1*/)
{
	return nullptr;
}

int mm6::GameStructure::loadHouseMovie(/*Name, Loop = true*/)
{
	return 0;
}

int mm6::GameStructure::playMapTrack()
{
	return 0;
}


int32_t* mm7::GameStructure::autonoteCategory = nullptr;
uint32_t mm7::GameStructure::autonoteCategory_size = 0;
char** mm7::GameStructure::autonoteTxt = nullptr;
uint32_t mm7::GameStructure::autonoteTxt_size = 0;
int32_t* mm7::GameStructure::awardsSort = nullptr;
uint32_t mm7::GameStructure::awardsSort_size = 0;
char** mm7::GameStructure::awardsTxt = nullptr;
uint32_t mm7::GameStructure::awardsTxt_size = 0;
char** mm7::GameStructure::classNames = nullptr;
uint32_t mm7::GameStructure::classNames_size = 0;
mm7::CustomLods* mm7::GameStructure::customLods = nullptr;
bool* mm7::GameStructure::foodGoldVisible = nullptr;
uint32_t* mm7::GameStructure::frameCounter = nullptr;
mm7::EventLine* mm7::GameStructure::globalEvtLines = nullptr;
uint32_t* mm7::GameStructure::globalEvtLines_sizePtr = nullptr;
std::array<std::array<mm7::Item, 12>, 1>* mm7::GameStructure::guildItems = nullptr;
uint32_t mm7::GameStructure::guildItems_size = 0;
std::array<uint8_t, 89>* mm7::GameStructure::hostileTxt = nullptr;
uint32_t mm7::GameStructure::hostileTxt_size = 0;
mm7::HouseMovie* mm7::GameStructure::houseMovies = nullptr;
uint32_t mm7::GameStructure::houseMovies_size = 0;
mm7::Events2DItem* mm7::GameStructure::houses = nullptr;
uint32_t mm7::GameStructure::houses_size = 0;
mm7::ItemsTxtItem* mm7::GameStructure::itemsTxt = nullptr;
uint32_t* mm7::GameStructure::itemsTxt_sizePtr = nullptr;
int16_t* mm7::GameStructure::mapDoorSound = nullptr;
uint32_t mm7::GameStructure::mapDoorSound_size = 0;
mm7::FogChances* mm7::GameStructure::mapFogChances = nullptr;
uint32_t mm7::GameStructure::mapFogChances_size = 0;
mm7::MapStatsItem* mm7::GameStructure::mapStats = nullptr;
uint32_t* mm7::GameStructure::mapStats_sizePtr = nullptr;
mm7::MissileSetup* mm7::GameStructure::missileSetup = nullptr;
uint32_t* mm7::GameStructure::missileSetup_sizePtr = nullptr;
mm7::MonsterKind* mm7::GameStructure::monsterKinds = nullptr;
uint32_t* mm7::GameStructure::monsterKinds_sizePtr = nullptr;
mm7::MonstersTxtItem* mm7::GameStructure::monstersTxt = nullptr;
uint32_t* mm7::GameStructure::monstersTxt_sizePtr = nullptr;
mm7::NPC* mm7::GameStructure::NPC = nullptr;
uint32_t* mm7::GameStructure::NPC_sizePtr = nullptr;
mm7::NPC* mm7::GameStructure::NPCDataTxt = nullptr;
uint32_t mm7::GameStructure::NPCDataTxt_size = 0;
std::array<char*, 2>* mm7::GameStructure::NPCGreet = nullptr;
uint32_t mm7::GameStructure::NPCGreet_size = 0;
int16_t* mm7::GameStructure::NPCGroup = nullptr;
uint32_t mm7::GameStructure::NPCGroup_size = 0;
std::array<char*, 2>* mm7::GameStructure::NPCNames = nullptr;
uint32_t mm7::GameStructure::NPCNames_size = 0;
char** mm7::GameStructure::NPCNews = nullptr;
uint32_t mm7::GameStructure::NPCNews_size = 0;
char** mm7::GameStructure::NPCText = nullptr;
uint32_t mm7::GameStructure::NPCText_size = 0;
char** mm7::GameStructure::NPCTopic = nullptr;
uint32_t mm7::GameStructure::NPCTopic_size = 0;
mm7::PatchOptions* mm7::GameStructure::patchOptions = nullptr;
char** mm7::GameStructure::placeMonTxt = nullptr;
uint32_t* mm7::GameStructure::placeMonTxt_sizePtr = nullptr;
char** mm7::GameStructure::questsTxt = nullptr;
uint32_t mm7::GameStructure::questsTxt_size = 0;
std::array<mm7::Item, 12>* mm7::GameStructure::shopItems = nullptr;
uint32_t mm7::GameStructure::shopItems_size = 0;
int64_t* mm7::GameStructure::shopNextRefill = nullptr;
uint32_t mm7::GameStructure::shopNextRefill_size = 0;
std::array<mm7::Item, 12>* mm7::GameStructure::shopSpecialItems = nullptr;
uint32_t mm7::GameStructure::shopSpecialItems_size = 0;
int64_t* mm7::GameStructure::shopTheftExpireTime = nullptr;
uint32_t mm7::GameStructure::shopTheftExpireTime_size = 0;
mm7::SpcItemsTxtItem* mm7::GameStructure::spcItemsTxt = nullptr;
uint32_t mm7::GameStructure::spcItemsTxt_size = 0;
mm7::StdItemsTxtItem* mm7::GameStructure::stdItemsTxt = nullptr;
uint32_t mm7::GameStructure::stdItemsTxt_size = 0;
uint8_t* mm7::GameStructure::titleTrackOffset = nullptr;
uint32_t mm7::GameStructure::titleTrackOffset_size = 0;
char** mm7::GameStructure::transTxt = nullptr;
uint32_t mm7::GameStructure::transTxt_size = 0;
std::array<int8_t, 4>* mm7::GameStructure::transportIndex = nullptr;
uint32_t mm7::GameStructure::transportIndex_size = 0;
mm7::TravelInfo* mm7::GameStructure::transportLocations = nullptr;
uint32_t mm7::GameStructure::transportLocations_size = 0;

bool mm7::GameStructure::exitHouseScreen()
{
	return false;
}

int mm7::GameStructure::doPause2(/**/)
{
	return 0;
}

int mm7::GameStructure::doResume2(/**/)
{
	return 0;
}

int mm7::GameStructure::getNPCPtrFromIndex(/*Index*/)
{
	return 0;
}

int mm7::GameStructure::setInterfaceColor(/*Color, Unk = 1*/)
{
	return 0;
}

char* mm7::GameStructure::compress(/*pTarget, pTargetSize, pSrc, SrcSize, Compression[MM7+] = -1*/)
{
	return nullptr;
}

int mm7::GameStructure::getStatisticEffect(/*Stat*/)
{
	return 0;
}

int mm7::GameStructure::doShowMovie(/*Name, Y, DoubleSize, ExitCurrentScreen*/)
{
	return 0;
}

int mm7::GameStructure::isMoviePlaying(/**/)
{
	return 0;
}

int mm7::GameStructure::loadHouseMovie(/*Name, Loop = true*/)
{
	return 0;
}

int mm7::GameStructure::fileRead(/*pTarget, Size, Count, FileStream*/)
{
	return 0;
}

int mm7::GameStructure::endMovie(/**/)
{
	return 0;
}

int mm7::GameStructure::uncompress(/*pTarget, pTargetSize, pSrc, SrcSize*/)
{
	return 0;
}

int mm7::GameStructure::playMapTrack()
{
	return 0;
}

int mm7::GameStructure::rand()
{
	return 0;
}

int mm7::GameStructure::restartHouseMovie(/**/)
{
	return 0;
}

int mm7::GameStructure::playShopSound(/*House, SoundIndex*/)
{
	return 0;
}

int mm7::GameStructure::fileTell(/*FileStream*/)
{
	return 0;
}

int mm7::GameStructure::calcSpellDamage(/*Spell, Skill, Mastery, MonsterHP*/)
{
	return 0;
}

int mm7::GameStructure::getSpellDamageType(/*Spell*/)
{
	return 0;
}

int mm7::GameStructure::summonMonster(/*Id, X, Y, Z*/)
{
	return 0;
}

int mm7::GameStructure::summonObjects(/*Type, X, Y, Z, Speed, Count = 1, RandomAngle = false, Bits = 0, pItem:structs.Item [MM7+]*/)
{
	return 0;
}

int mm7::GameStructure::processActions()
{
	return 0;
}

int mm7::GameStructure::doResume(/**/)
{
	return 0;
}

int mm7::GameStructure::generateChests()
{
	return 0;
}

int mm7::GameStructure::doPause(/**/)
{
	return 0;
}

int mm7::GameStructure::fileSeek(/*FileStream, Offset, Origin = 0*/)
{
	return 0;
}

int mm7::GameStructure::isMonsterOfKind(/*Id, Kind:const.MonsterKind*/)
{
	return 0;
}

int mm7::GameStructure::endTextInput(/*State*/)
{
	return 0;
}


int32_t* mm8::GameStructure::autonoteCategory = nullptr;
uint32_t mm8::GameStructure::autonoteCategory_size = 0;
char** mm8::GameStructure::autonoteTxt = nullptr;
uint32_t mm8::GameStructure::autonoteTxt_size = 0;
int32_t* mm8::GameStructure::awardsSort = nullptr;
uint32_t mm8::GameStructure::awardsSort_size = 0;
char** mm8::GameStructure::awardsTxt = nullptr;
uint32_t mm8::GameStructure::awardsTxt_size = 0;
mm8::CharacterDollType* mm8::GameStructure::characterDollTypes = nullptr;
uint32_t mm8::GameStructure::characterDollTypes_size = 0;
mm8::CharacterPortrait* mm8::GameStructure::characterPortraits = nullptr;
uint32_t mm8::GameStructure::characterPortraits_size = 0;
char** mm8::GameStructure::classNames = nullptr;
uint32_t mm8::GameStructure::classNames_size = 0;
mm8::CustomLods* mm8::GameStructure::customLods = nullptr;
mm8::EventLine* mm8::GameStructure::globalEvtLines = nullptr;
uint32_t* mm8::GameStructure::globalEvtLines_sizePtr = nullptr;
std::array<std::array<mm8::Item, 12>, 12>* mm8::GameStructure::guildItems = nullptr;
uint32_t mm8::GameStructure::guildItems_size = 0;
int64_t* mm8::GameStructure::guildNextRefill2 = nullptr;
uint32_t mm8::GameStructure::guildNextRefill2_size = 0;
std::array<uint8_t, 218>* mm8::GameStructure::hostileTxt = nullptr;
uint32_t mm8::GameStructure::hostileTxt_size = 0;
mm8::HouseMovie* mm8::GameStructure::houseMovies = nullptr;
uint32_t mm8::GameStructure::houseMovies_size = 0;
mm8::Events2DItem* mm8::GameStructure::houses = nullptr;
uint32_t mm8::GameStructure::houses_size = 0;
mm8::HousesExtra* mm8::GameStructure::housesExtra = nullptr;
uint32_t mm8::GameStructure::housesExtra_size = 0;
uint32_t* mm8::GameStructure::inOODialog = nullptr;
mm8::ItemsTxtItem* mm8::GameStructure::itemsTxt = nullptr;
uint32_t* mm8::GameStructure::itemsTxt_sizePtr = nullptr;
int16_t* mm8::GameStructure::mapDoorSound = nullptr;
uint32_t mm8::GameStructure::mapDoorSound_size = 0;
mm8::FogChances* mm8::GameStructure::mapFogChances = nullptr;
uint32_t mm8::GameStructure::mapFogChances_size = 0;
mm8::MapStatsItem* mm8::GameStructure::mapStats = nullptr;
uint32_t* mm8::GameStructure::mapStats_sizePtr = nullptr;
mm8::MissileSetup* mm8::GameStructure::missileSetup = nullptr;
uint32_t* mm8::GameStructure::missileSetup_sizePtr = nullptr;
std::array<uint16_t, 70>* mm8::GameStructure::mixPotions = nullptr;
uint32_t mm8::GameStructure::mixPotions_size = 0;
mm8::MonsterKind* mm8::GameStructure::monsterKinds = nullptr;
uint32_t* mm8::GameStructure::monsterKinds_sizePtr = nullptr;
mm8::MonstersTxtItem* mm8::GameStructure::monstersTxt = nullptr;
uint32_t* mm8::GameStructure::monstersTxt_sizePtr = nullptr;
mm8::NPC* mm8::GameStructure::NPC = nullptr;
uint32_t mm8::GameStructure::NPC_size = 0;
mm8::NPC* mm8::GameStructure::NPCDataTxt = nullptr;
uint32_t mm8::GameStructure::NPCDataTxt_size = 0;
std::array<char*, 2>* mm8::GameStructure::NPCGreet = nullptr;
uint32_t mm8::GameStructure::NPCGreet_size = 0;
int16_t* mm8::GameStructure::NPCGroup = nullptr;
uint32_t mm8::GameStructure::NPCGroup_size = 0;
char** mm8::GameStructure::NPCNews = nullptr;
uint32_t mm8::GameStructure::NPCNews_size = 0;
char** mm8::GameStructure::NPCText = nullptr;
uint32_t mm8::GameStructure::NPCText_size = 0;
char** mm8::GameStructure::NPCTopic = nullptr;
uint32_t mm8::GameStructure::NPCTopic_size = 0;
mm8::PatchOptions* mm8::GameStructure::patchOptions = nullptr;
char** mm8::GameStructure::placeMonTxt = nullptr;
uint32_t* mm8::GameStructure::placeMonTxt_sizePtr = nullptr;
char** mm8::GameStructure::questsTxt = nullptr;
uint32_t mm8::GameStructure::questsTxt_size = 0;
mm8::ReagentSettings* mm8::GameStructure::reagentSettings = nullptr;
uint32_t mm8::GameStructure::reagentSettings_size = 0;
std::array<mm8::Item, 12>* mm8::GameStructure::shopItems = nullptr;
uint32_t mm8::GameStructure::shopItems_size = 0;
int64_t* mm8::GameStructure::shopNextRefill = nullptr;
uint32_t mm8::GameStructure::shopNextRefill_size = 0;
std::array<mm8::Item, 12>* mm8::GameStructure::shopSpecialItems = nullptr;
uint32_t mm8::GameStructure::shopSpecialItems_size = 0;
int64_t* mm8::GameStructure::shopTheftExpireTime = nullptr;
uint32_t mm8::GameStructure::shopTheftExpireTime_size = 0;
mm8::SpcItemsTxtItem* mm8::GameStructure::spcItemsTxt = nullptr;
uint32_t mm8::GameStructure::spcItemsTxt_size = 0;
mm8::StdItemsTxtItem* mm8::GameStructure::stdItemsTxt = nullptr;
uint32_t mm8::GameStructure::stdItemsTxt_size = 0;
uint8_t* mm8::GameStructure::titleTrackOffset = nullptr;
uint32_t mm8::GameStructure::titleTrackOffset_size = 0;
char** mm8::GameStructure::transTxt = nullptr;
uint32_t mm8::GameStructure::transTxt_size = 0;
std::array<int8_t, 4>* mm8::GameStructure::transportIndex = nullptr;
uint32_t mm8::GameStructure::transportIndex_size = 0;
mm8::TravelInfo* mm8::GameStructure::transportLocations = nullptr;
uint32_t mm8::GameStructure::transportLocations_size = 0;

int mm8::GameStructure::playMapTrack()
{
	return 0;
}

int mm8::GameStructure::doShowMovie(/*Name, Y, DoubleSize, ExitCurrentScreen*/)
{
	return 0;
}

int mm8::GameStructure::calcSpellDamage(/*Spell, Skill, Mastery, MonsterHP*/)
{
	return 0;
}

int mm8::GameStructure::isMonsterOfKind(/*Id, Kind:const.MonsterKind*/)
{
	return 0;
}

int mm8::GameStructure::isMoviePlaying(/**/)
{
	return 0;
}

int mm8::GameStructure::getSpellDamageType(/*Spell*/)
{
	return 0;
}

int mm8::GameStructure::rand()
{
	return 0;
}

int mm8::GameStructure::restartHouseMovie(/**/)
{
	return 0;
}

int mm8::GameStructure::getNPCPtrFromIndex(/*Index*/)
{
	return 0;
}

int mm8::GameStructure::summonMonster(/*Id, X, Y, Z*/)
{
	return 0;
}

int mm8::GameStructure::playShopSound(/*House, SoundIndex*/)
{
	return 0;
}

int mm8::GameStructure::uncompress(/*pTarget, pTargetSize, pSrc, SrcSize*/)
{
	return 0;
}

int mm8::GameStructure::processActions()
{
	return 0;
}

int mm8::GameStructure::getStatisticEffect(/*Stat*/)
{
	return 0;
}

int mm8::GameStructure::endMovie(/**/)
{
	return 0;
}

char* mm8::GameStructure::compress(/*pTarget, pTargetSize, pSrc, SrcSize, Compression[MM7+] = -1*/)
{
	return nullptr;
}

int mm8::GameStructure::escMessage(/*Text, Unk = 0*/)
{
	return 0;
}

int mm8::GameStructure::loadHouseMovie(/*Name, Loop = true*/)
{
	return 0;
}

int mm8::GameStructure::generateChests()
{
	return 0;
}

bool mm8::GameStructure::exitHouseScreen()
{
	return false;
}

