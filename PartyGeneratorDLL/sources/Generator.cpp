#include "pch.h"
#include "main.h"
#include "Generator.h"
#include <cassert>
#include "GameData.h"
#include "PlayerData.h"
#include <algorithm>

extern const int INVALID_ID;

inline void checkAffinity(double aff)
{
	assert(aff >= MINIMUM_AFFINITY && aff <= MAXIMUM_AFFINITY);
}
//#define CHECK_AFFINITY(aff, msg) assert((aff) >= Generator::MINIMUM_AFFINITY && (aff) <= Generator::MAXIMUM_AFFINITY, msg)
//#define CHECK_AFFINITY(aff) CHECK_AFFINITY(aff, "Affinity is outside the bounds [" + Generator::MINIMUM_AFFINITY + ", " + Generator::MINIMUM_AFFINITY + "]")

Generator::Generator()
{
	assert(MAX_PLAYERS >= 4); // set in init() exported dll function
	playerData = new PlayerData[MAX_PLAYERS] {};
	generateForPlayer = new bool[MAX_PLAYERS];
	setDefaults(); // also sets defaults for player data and activates generation for every player
	mockPlayers = nullptr;
	mock = false;
}

Generator::~Generator()
{
	delete[] playerData;
	delete[] generateForPlayer;
}

bool Generator::readFromJson(const Json& json)
{
	return false;
}
bool Generator::writeToJson(Json& json)
{
	return false;
}
void Generator::setDefaults()
{
	for (int i = 0; i < MAX_PLAYERS; ++i)
	{
		playerData[i].setDefaults();
	}
	partyType = PARTY_GENERIC;
	for (int i = 0; i < MAX_PLAYERS; ++i)
	{
		generateForPlayer[i] = true;
	}
	unsetArtifactsFoundBits = false;
	setArtifactsFoundBitsIfGenerated = false;
	defaultGlobalClassSettings.setDefaults();
}

template<typename Player>
void generateClass(Player* player)
{
	// class weights && disable specific (weight 0) && guarantee specific && party type
}

template<typename Player>
bool Generator::generate()
{
	state = Generator::State(); // explicitly create fresh state
	Player** players = (Player**)(mock ? this->mockPlayers : this->players);
	if constexpr (SAME(Player, mm6::Player))
	{
		// PartyMm6 party = (GameMm6)game->party;
	}
	else // if...
	{

	}
	if (unsetArtifactsFoundBits)
	{
		// unset all
	}
	if (setArtifactsFoundBitsIfGenerated)
	{
		// for (Item item: generated items)
		//	 if (item.isArtifact())
		//     setBit(item.id)
	}
	return false;
}