#pragma once
#include "main.h"

class AwardBit;
class QuestBit;

enum class QuestType
{
	PROMOTION,
	MAINLINE,
	SIDE,
};

class GameQuest
{
	const QuestType type;
	// a list of award bits related to this quest
	std::vector<AwardBit*> awardBits;
	// a list of quest bits related to this quest
	std::vector<QuestBit*> questBits;
	// a list of names of maps where this quest takes place
	std::vector<std::string> takesPlaceOn;
	// TODO: NPC pointers
public:
	GameQuest(QuestType type);
	~GameQuest();

	void addAwardBit(AwardBit* bit);
	void addQuestBit(QuestBit* bit);
	void addMapName(std::string mapName);

	void unsetAllQuestBits();
	void unsetAllAwardBitsSinglePlayer(int rosterIndex);
	void unsetAllAwardBitsAllPlayers();

	void setAllQuestBits();
	void setAllAwardBitsSinglePlayer(int rosterIndex);
	void setAllAwardBitsAllPlayers();

	std::vector<AwardBit*> getAwardBits();
	std::vector<QuestBit*> getQuestBits();
	std::vector<std::string> getMapNames();
	QuestType getType();

};

