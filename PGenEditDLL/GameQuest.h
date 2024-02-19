#pragma once
#include "main.h"

class AwardBit;
class QuestBit;

class GameQuest
{
	// a list of award bits related to this quest
	std::vector<AwardBit*> awardBits;
	// a list of quest bits related to this quest
	std::vector<QuestBit*> questBits;
	// a list of names of maps where this quest takes place
	std::vector<std::string> takesPlaceOn;
public:

};

