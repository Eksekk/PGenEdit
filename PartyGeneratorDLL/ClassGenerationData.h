#pragma once
#include "pch.h"
#include "main.h"
#include "Enum_const.h"
#include "GeneratorDataBase.h"

extern const int DEFAULT_SETTINGS_INDEX;

class PlayerData;

class ClassGenerationSettings : public GeneratorDataBase // settings from GUI
{
public:
	int id = DEFAULT_SETTINGS_INDEX; // not used in general settings
	int weight;
	std::vector<int> tierWeights;
	Alignment alignment;
	bool disabled; // not used in general settings
	bool equalChances;

	ClassGenerationSettings();

	// Inherited via GeneratorDataBase
	virtual bool readFromJson(const Json& json) override;
	virtual bool writeToJson(Json& json) override;
	virtual void setDefaults() override;
	virtual void randomize() override;
	virtual void copyFrom(const GeneratorDataBase& source) override;

	ClassGenerationSettings& operator=(const ClassGenerationSettings& other);

	bool operator==(const ClassGenerationSettings& other) const;
	bool operator!=(const ClassGenerationSettings& other) const;
	bool useDefaults;
};

class ClassGenerationData : public GeneratorDataBase
{
public:
	std::unordered_map<int, ClassGenerationSettings> settings; // rehash doesn't invalidate pointers
	ClassGenerationSettings defaultSettings; // for player
	Alignment possibleAlignment;
	int index;
	bool generationEnabled;
	PlayerData& playerData;
	// TODO: guaranteed classes
	// TODO: MM7 & MERGE unavailable promotion quests if generating two path characters

	template<typename Player>
	bool generate(Player* player/*, Generator::State state*/);

	ClassGenerationData(int index, PlayerData& playerData);
	ClassGenerationData() = delete;

	// TODO: guarantee class in spells/skills window, if so show note in class window

	void createSettings(); // fill map with default settings for base classes

	// Inherited via GeneratorDataBase
	virtual bool readFromJson(const Json& json) override;

	virtual bool writeToJson(Json& json) override;

	virtual void setDefaults() override;

	virtual void randomize() override;
	virtual void copyFrom(const GeneratorDataBase& source) override;

	ClassGenerationData& operator=(const ClassGenerationData& other);

	bool operator==(const ClassGenerationData& other);
	bool operator!=(const ClassGenerationData& other);
};