#pragma once
#include "main.h"

class GameQuest;

enum class AwardBitCategory
{
	PROMOTION,
	PROMOTION_HONORARY,
	MAINLINE_QUEST,
	SIDE_QUEST,
	GUILD_MEMBERSHIP
};
using enum AwardBitCategory;

class AwardBit
{
	const int id;
	const AwardBitCategory category;
	// a list of pointers to all quests this bit is associated with
	std::vector<GameQuest*> quests;
	std::string description;
};

