#include "pch.h"
#include "main.h"
#include "Generator.h"
#include <cassert>
#include "GameData.h"
#include "PlayerData.h"
#include <algorithm>

extern const int DEFAULT_SETTINGS_INDEX;
const unsigned Generator::MAX_AVERAGE_LEVEL = 200;
const unsigned Generator::MIN_AVERAGE_LEVEL = 1;

inline void checkAffinity(double aff)
{
	assert(aff >= MINIMUM_AFFINITY && aff <= MAXIMUM_AFFINITY);
}
//#define CHECK_AFFINITY(aff, msg) assert((aff) >= Generator::MINIMUM_AFFINITY && (aff) <= Generator::MAXIMUM_AFFINITY, msg)
//#define CHECK_AFFINITY(aff) CHECK_AFFINITY(aff, "Affinity is outside the bounds [" + Generator::MINIMUM_AFFINITY + ", " + Generator::MINIMUM_AFFINITY + "]")

Generator::Generator() : defaultPlayerData(DEFAULT_SETTINGS_INDEX)
{
	assert(MAX_PLAYERS >= 4); // set in dllmain
	playerData.reserve(MAX_PLAYERS);
	for (int i = 0; i < MAX_PLAYERS; ++i)
	{
		playerData.push_back(std::make_unique<PlayerData>(i));
	}
	randomSeed = true;
	seed = 0;
	randomInFileIsExact = true;
	setDefaults(); // also sets defaults for player data and activates generation for every player
}

Generator::~Generator()
{
	
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
	averageLevel = std::clamp(25U, MIN_AVERAGE_LEVEL, MAX_AVERAGE_LEVEL);
	for (int i = 0; i < MAX_PLAYERS; ++i)
	{
		playerData[i]->setDefaults();
	}
	partyType = PARTY_GENERIC;
	unsetArtifactsFoundBits = false;
	setArtifactsFoundBitsIfGenerated = false;
	miscSkillsAtMostOnePlayer = true;
	possibleAlignment = ALIGNMENT_ANY;
	defaultPlayerData.setDefaults();
}

void Generator::randomize()
{
}

void Generator::copyFrom(const GeneratorDataBase& source)
{
	const Generator* other = dynamic_cast<const Generator*>(&source);
	if (!other)
	{
		throw std::runtime_error(wxString::Format("%s:%d %s", __FILE__, __LINE__, "Dynamic cast from GeneratorDataBase to Generator failed"));
	}

}

Generator& Generator::operator=(const Generator& other)
{
	return *this;
}

bool Generator::operator==(const Generator& other) const
{
	return false;
}

bool Generator::operator!=(const Generator& other) const
{
	return false;
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
	Player** players = (Player**)players;
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