#pragma once
#include "pch.h"
#include "main.h"
#include "Enum_const.h"

extern const int MAX_TIER;

class PlayerClass // holds data about classes, both from game structs and lua
{
public:
	int id;
	std::string name;
	int tier; // 0-2
	PlayerClass* baseClass; // goes towards lower tier, i.e. the class you start with
	Alignment alignment; // light, dark, neutral
	std::vector<PlayerClass*> promotionClasses; // higher tier
	std::unordered_map<int, Mastery> maximumSkillMasteries;
	std::unordered_map<int, double> playerTypeAffinity; // how appropriate is this class for given player type
	int classWindowId;

	PlayerClass();
	PlayerClass(int id, std::string name, int tier);
	PlayerClass(int id, std::string name, int tier, PlayerClass* baseClass, Alignment alignment = ALIGNMENT_NEUTRAL);
	~PlayerClass();

	PlayerClass* getStarterClass();

	struct TreeOptions
	{
		bool lower; // include lower tier?
		bool higher; // include higher tier?
		bool equal; // include same tier?
		TreeOptions(bool lower = true, bool equal = true, bool higher = true) : lower(lower), equal(equal), higher(higher) {}
	};
	std::vector<PlayerClass*> getClassTree(const TreeOptions& options);
	std::vector<PlayerClass*> getEntireClassTree(PlayerClass* start = nullptr);

	static bool areInSameClassTree(int id1, int id2);
	static bool areInSameClassTree(PlayerClass* clas1, PlayerClass* clas2);
	bool isInSameClassTreeAs(PlayerClass* other);
	bool isInSameClassTreeAs(int otherId);

	wxString getFormattedTier();
	wxString getFormattedAlignment();
};

