#include "pch.h"
#include "main.h"
#include "Generator.h"
#include <cassert>
#include "GameData.h"

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
	currentPlayer = INVALID_ID;
	generateForPlayer = new bool[MAX_PLAYERS];
	setDefaults(); // also sets defaults for player data and activates generation for every player
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
}

template<typename Player>
bool Generator::generate()
{
	return false;
}