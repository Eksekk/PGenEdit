#pragma once
#include "pch.h"
#include "main.h"
#include "Enum_const.h"
#include "GeneratorDataBase.h"

extern const int INVALID_ID;

struct ClassGenerationSettings // settings from GUI
{
	int id = INVALID_ID; // not used in general settings
	int weight;
	std::vector<int> tierWeights;
	Alignment alignment;
	bool disabled; // not used in general settings
	bool equalChances;

	ClassGenerationSettings();
	void setDefaults();
};

class ClassGenerationData : public GeneratorDataBase
{
public:
	std::unordered_map<int, ClassGenerationSettings> settings; // rehash doesn't invalidate pointers
	ClassGenerationSettings defaultSettings; // for player
	// TODO: guaranteed classes

	template<typename Player>
	bool generate(Player* player/*, Generator::State state*/);

	// TODO: guarantee class in spells/skills window, if so show note in class window

	void createSettings(); // fill map with default settings for base classes

	// Inherited via GeneratorDataBase
	virtual bool readFromJson(const Json& json) override;

	virtual bool writeToJson(Json& json) override;

	virtual void setDefaults() override;
};