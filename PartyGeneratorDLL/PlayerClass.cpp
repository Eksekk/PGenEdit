#include "pch.h"
#include "main.h"
#include "PlayerClass.h"

extern const int INVALID_ID;

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

std::vector<PlayerClass*> PlayerClass::getEntireClassTree(int id)
{
	try
	{

	}
	catch (...)
	{
	}
	return std::vector<PlayerClass*>();
}

std::vector<PlayerClass*> PlayerClass::getEntireClassTree(PlayerClass* clas)
{
	return std::vector<PlayerClass*>();
}

std::vector<PlayerClass*> PlayerClass::getEntireClassTree()
{
	return std::vector<PlayerClass*>();
}

bool PlayerClass::areInSameClassTree(int id1, int id2)
{
	return false;
}

bool PlayerClass::areInSameClassTree(PlayerClass* clas1, PlayerClass* clas2)
{
	return false;
}

bool PlayerClass::areInSameClassTree(PlayerClass* other)
{
	return false;
}

bool PlayerClass::areInSameClassTree(int otherId)
{
	return false;
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
