#include "pch.h"
#include "main.h"
#include "PlayerClass.h"
#include "Utility.h"
#include "GameData.h"

extern const int INVALID_ID;
const int MAX_TIER = 2;

PlayerClass::PlayerClass() : id(INVALID_ID), name(""), tier(0), baseClass(nullptr), alignment(ALIGNMENT_NEUTRAL), playerTypeAffinity()
{
	for (int i = 0; i < PLAYER_TYPE_COUNT; ++i)
	{
		playerTypeAffinity.emplace(i, 1);
	}
}

PlayerClass::PlayerClass(int id, std::string name, int tier) : id(id), name(name), tier(0), baseClass(nullptr), alignment(ALIGNMENT_NEUTRAL), playerTypeAffinity()
{
	for (int i = 0; i < PLAYER_TYPE_COUNT; ++i)
	{
		playerTypeAffinity.emplace(i, 1);
	}
}

PlayerClass::PlayerClass(int id, std::string name, int tier, PlayerClass* baseClass, Alignment alignment)
	: id(id), name(name), tier(tier), baseClass(baseClass), alignment(alignment), playerTypeAffinity()
{
	for (int i = 0; i < PLAYER_TYPE_COUNT; ++i)
	{
		playerTypeAffinity.emplace(i, 1);
	}
}

PlayerClass::~PlayerClass()
{
	
}

std::vector<PlayerClass*> PlayerClass::getClassTree(const TreeOptions& options)
{
	auto vals = getEntireClassTree();
	auto itr = std::remove_if(vals.begin(), vals.end(), [this, &options](PlayerClass* const cls) -> bool
	{
		if (!options.equal && cls->tier == this->tier && cls != this)
		{
			return true;
		}
		else if (!options.higher && cls->tier > this->tier)
		{
			return true;
		}
		else if (!options.lower && cls->tier < this->tier)
		{
			return true;
		}
		else
		{
			return false;
		}
	});
	vals.erase(itr, vals.end());
	return vals;
}

// probably overkill to use graph algorithms here, but I recall Merge had two base classes for "mage" class - sorcerer and necromancer
void dfsHelper(PlayerClass* cls, std::vector<PlayerClass*>& visited)
{
	auto toCheck = cls->promotionClasses;
	toCheck.push_back(cls->baseClass);
	for (PlayerClass* neighbor : toCheck)
	{
		if (neighbor != nullptr && !existsInVector(visited, neighbor))
		{
			visited.push_back(neighbor);
			dfsHelper(neighbor, visited);
		}
	}
}

std::vector<PlayerClass*> PlayerClass::getEntireClassTree(PlayerClass* start)
{
	std::vector<PlayerClass*> ret;
	dfsHelper(start != nullptr ? start : this, ret);
	return ret;
}

bool PlayerClass::areInSameClassTree(int id1, int id2)
{
	return GameData::classes.at(id1).isInSameClassTreeAs(id2);
}

bool PlayerClass::areInSameClassTree(PlayerClass* clas1, PlayerClass* clas2)
{
	return clas1->isInSameClassTreeAs(clas2);
}

bool PlayerClass::isInSameClassTreeAs(PlayerClass* other)
{
	return existsInVector(getEntireClassTree(), other);
}

bool PlayerClass::isInSameClassTreeAs(int otherId)
{
	auto vals = getEntireClassTree();
	return std::find_if(vals.begin(), vals.end(), [otherId](PlayerClass* const cls) -> bool
		{
			return cls->id == otherId;
		}) != vals.end();
}

wxString PlayerClass::getFormattedTier()
{
	static wxString tierNames[] = {"basic", "promoted", "fully promoted"};
	assert(tier <= 2);
	return wxString::Format("%d (%s)", tier, tierNames[tier]);
}

wxString PlayerClass::getFormattedAlignment()
{
	if (alignment == ALIGNMENT_ANY) return "any";
	if (alignment == ALIGNMENT_DARK) return "dark";
	if (alignment == ALIGNMENT_LIGHT) return "light";
	return "neutral";
}

PlayerClass* PlayerClass::getStarterClass()
{
	PlayerClass* clas = baseClass;
	while (clas != nullptr)
	{
		clas = clas->baseClass;
	}
	return clas;
}
