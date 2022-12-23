#pragma once
#include "pch.h"
#include "main.h"
#include "Enum_const.h"
#include <string>
#include <vector>
#include <unordered_map>
class PlayerClass
{
public:
	int id;
	std::string name;
	int tier; // 0-2
	PlayerClass* baseClass; // goes towards lower tier, i.e. the class you start with
	Alignment alignment; // light, dark, neutral
	std::vector<PlayerClass*> promotionClasses; // higher tier
	std::unordered_map<int, Mastery> maximumSkillMasteries;
	double playerTypeAffinity[PLAYER_TYPE_COUNT]; // how appropriate is this class for given player type

	PlayerClass() = delete;
	PlayerClass(int id, std::string name, int tier);
	PlayerClass(int id, std::string name, int tier, PlayerClass* baseClass, Alignment alignment = ALIGNMENT_NEUTRAL);
	~PlayerClass();

	static std::vector<PlayerClass*> getEntireClassTree(int id);
	static std::vector<PlayerClass*> getEntireClassTree(PlayerClass* clas);
	std::vector<PlayerClass*> getEntireClassTree();

	static bool areInSameClassTree(int id1, int id2);
	static bool areInSameClassTree(PlayerClass* clas1, PlayerClass* clas2);
	bool areInSameClassTree(PlayerClass* other);
	bool areInSameClassTree(int otherId);
};

