#pragma once
#include "main.h"

class GameQuest;

enum class QuestBitType
{
	COMPLETE_QUEST,
	KILL_MONSTERS,
	KILL_SPECIFIC_MONSTER,
	TAKE_DUNGEON_ACTION, // such as purifying/desecrating altar in MM7
	TAKE_WORLD_ACTION, // such as druid altars in MM7
	ONE_TIME_USE, // like barrels in BDJ mod
	DELIVER_ITEM_TO_NPC, // mainly for cases where you get required item after accepting quest and just need to deliver it
	FIND_ITEM, // for cases where you need to find an item in the world
	TALK_TO_NPC, // like that "cure knight of plague" quest in MM8, where you need to talk to cleric and get recovery gem
	VISIT_OBELISK,
	LOST_IT, // marks items which seer can return to you
	FRIENDS_ARE_ANGRY, // when you attack guards in friendly city and they become hostile
	TOWN_PORTAL_AVAILABLE, // marks areas which you have visited (MM7) or drank from their fountain (MM8) and as such can be town portalled to

	// TODO: add more types
	
	OTHER
};
using enum QuestBitType;

using QuestBitTypeVariant = std::variant<void*, void**>; // TODO: add all small data holder classes for specific bit types

struct QuestBitTypeData
{
	QuestBitType type;
	QuestBitTypeVariant data;
};

class QuestBit
{
	// a list of quests this bit is related to
	std::vector<GameQuest*> relatedToQuests;
	std::string description;
	// a list of quest bits that depend on this bit and can't be set until this one is set
	std::vector<QuestBit*> childQuestBits;
	// a list of quest bits that this bit depends on and can't be set until they are set
	std::vector<QuestBit*> parentQuestBits;
	// a list of types of this bit along with some data (for example, for FIND_ITEM it will contain id of item to be found)
	std::vector<QuestBitTypeData> types;
};

