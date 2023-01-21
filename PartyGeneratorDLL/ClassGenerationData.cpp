#include "pch.h"
#include "main.h"
#include "ClassGenerationData.h"
#include "GameData.h"

ClassGenerationData::ClassGenerationData(int index, PlayerData& playerData) : index(index), playerData(playerData)
{
	setDefaults();
}

void ClassGenerationSettings::randomize()
{
}

void ClassGenerationSettings::copyFrom(const GeneratorDataBase& source)
{

}

ClassGenerationSettings::ClassGenerationSettings()
{
	setDefaults();
}

bool ClassGenerationSettings::readFromJson(const Json& json)
{
	/*int id = INVALID_ID; // not used in general settings
	int weight;
	std::vector<int> tierWeights;
	Alignment alignment;
	bool disabled; // not used in general settings
	bool equalChances;*/
	weight = json["weight"];
	tierWeights = json["tierWeights"].get<std::vector<int>>();
	auto itr = alignmentStringToId.find(json["alignment"]);
	assert(itr != alignmentStringToId.end());
	alignment = (Alignment)itr->second;
	disabled = json["disabled"];
	equalChances = json["equalChances"];
	return true;
}

bool ClassGenerationSettings::writeToJson(Json& json)
{
	json["weight"] = weight;
	json["tierWeights"] = tierWeights;
	//json["alignment"] = 
	return false;
}

void ClassGenerationSettings::setDefaults()
{
	weight = 1;
	for (int& i : tierWeights)
	{
		i = 1;
	}
	alignment = ALIGNMENT_NEUTRAL;
	disabled = false;
	equalChances = false;
}

bool ClassGenerationData::readFromJson(const Json& json)
{
	return false;
}

bool ClassGenerationData::writeToJson(Json& json)
{
	return false;
}

void ClassGenerationData::setDefaults()
{
	for (auto& [i, classGenerationSettings] : settings)
	{
		classGenerationSettings.setDefaults();
	}
	possibleAlignment = ALIGNMENT_ANY;
}

void ClassGenerationData::randomize()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	possibleAlignment = (Alignment)std::uniform_int_distribution(0, 3)(gen);
	if (std::uniform_int_distribution(0, 9)(gen) == 9)
	{
		generationEnabled = false;
	}
	std::uniform_int_distribution weightRand(0, 10);
	std::uniform_int_distribution alignmentRand(0, 3);
	std::uniform_int_distribution disabledRand(0, 5);
	std::uniform_int_distribution equalChancesRand(0, 5);
	auto randomSettings = [&](ClassGenerationSettings& s)
	{
		s.weight = weightRand(gen);
		s.tierWeights.clear();
		for (int i = 0; i <= 2; ++i)
		{
			s.tierWeights.push_back(weightRand(gen));
		}
		s.alignment = (Alignment)alignmentRand(gen);
		s.disabled = disabledRand(gen) == 5;
		s.equalChances = equalChancesRand(gen) == 5;
	};
	randomSettings(defaultSettings);
	for (auto& [id, s] : settings)
	{
		randomSettings(s);
	}
	/*
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
	Alignment possibleAlignment;
	int index;
	bool generationEnabled;
	PlayerData& playerData;
	*/
}

void ClassGenerationData::copyFrom(const GeneratorDataBase& source)
{
}

void ClassGenerationData::createSettings()
{
	for (auto& [id, data]: GameData::classes)
	{
		settings.emplace(id, ClassGenerationSettings());
	}
}

template<typename Player>
bool ClassGenerationData::generate(Player* player/*, Generator::State state*/)
{
	return false;
}