#include "pch.h"
#include "main.h"
#include "ClassGenerationData.h"
#include "GameData.h"
#include "Globals.h"

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
	auto itr = alignmentIdToString.find(alignment);
	assert(itr != alignmentIdToString.end());
	json["alignment"] = itr->second;
	json["disabled"] = disabled;
	json["equalChances"] = equalChances;
	return true;
}

void ClassGenerationSettings::setDefaults()
{
	weight = 1;
	for (int& i : tierWeights)
	{
		i = 1;
	}
	alignment = ALIGNMENT_ANY;
	disabled = false;
	equalChances = false;
}

void ClassGenerationSettings::randomize()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

	static std::uniform_int_distribution weightRand(0, 10);
	static std::uniform_int_distribution alignmentRand(0, 3);
	static std::uniform_int_distribution disabledRand(0, 5);
	static std::uniform_int_distribution equalChancesRand(0, 5);

	weight = weightRand(gen);
	for (int i = 0; i <= 2; ++i)
	{
		tierWeights.at(i) = weightRand(gen);
	}
	alignment = (Alignment)alignmentRand(gen);
	disabled = disabledRand(gen) == 5; // 16.66%
	equalChances = equalChancesRand(gen) == 5; // 16.66%
}

void ClassGenerationSettings::copyFrom(const GeneratorDataBase& source)
{
	const ClassGenerationSettings* other = dynamic_cast<const ClassGenerationSettings*>(&source);
	assert(other);
	weight = other->weight;
	tierWeights = other->tierWeights;
	alignment = other->alignment;
	disabled = other->disabled;
	equalChances = other->equalChances;
}

ClassGenerationData::ClassGenerationData(int index, PlayerData& playerData) : index(index), playerData(playerData)
{
	setDefaults();
}

/*std::unordered_map<int, ClassGenerationSettings> settings; // rehash doesn't invalidate pointers
	ClassGenerationSettings defaultSettings; // for player
	Alignment possibleAlignment;
	int index;
	bool generationEnabled;*/

bool ClassGenerationData::readFromJson(const Json& json)
{
	auto s = json["settings"].get<std::unordered_map<int, Json>>();
	for (auto& [id, data] : s)
	{
		if (!GameData::classes.contains(id))
		{
			jsonErrors.push_back(wxString::Format("Class entry for player %d doesn't contain class settings with id %d", index, id));
		}
		ClassGenerationSettings s;
		s.readFromJson(data);
		settings[id] = std::move(s);
	}
	if (s.size() != GameData::classes.size())
	{
		jsonErrors.push_back(wxString::Format("Class entry for player %d contains %d entries (%d expected)", index, s.size(), GameData::classes.size()));
	}
	defaultSettings.readFromJson(json["defaultSettings"]);
	std::string astr = json["possibleAlignment"];
	auto itr = alignmentStringToId.find(astr);
	assert(itr != alignmentStringToId.end());
	possibleAlignment = (Alignment)itr->second;
	generationEnabled = json["generationEnabled"];
	return true;
}

bool ClassGenerationData::writeToJson(Json& json)
{
	Json s;
	for (auto& [id, data] : settings)
	{
		Json tmp;
		data.writeToJson(tmp);
		s[id] = tmp;
	}
	json["settings"] = s;
	Json tmp;
	defaultSettings.writeToJson(tmp);
	json["defaultSettings"] = tmp;
	auto itr = alignmentIdToString.find(possibleAlignment);
	assert(itr != alignmentIdToString.end());
	json["possibleAlignment"] = itr->second;
	json["generationEnabled"] = generationEnabled;
	return true;
}

void ClassGenerationData::setDefaults()
{
	for (auto& [i, classGenerationSettings] : settings)
	{
		classGenerationSettings.setDefaults();
	}
	possibleAlignment = ALIGNMENT_ANY;
	generationEnabled = true;
}

void ClassGenerationData::randomize()
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	possibleAlignment = (Alignment)std::uniform_int_distribution(0, 3)(gen);
	if (std::uniform_int_distribution(0, 9)(gen)) // 90%
	{
		possibleAlignment = ALIGNMENT_ANY;
	}
	if (std::uniform_int_distribution(0, 9)(gen) == 9) // 10%
	{
		generationEnabled = false;
	}
	defaultSettings.randomize();
	for (auto& [id, s] : settings)
	{
		s.randomize();
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
	const ClassGenerationData* other = dynamic_cast<const ClassGenerationData*>(&source);
	assert(other);
	settings = other->settings;
	defaultSettings = other->defaultSettings;
	possibleAlignment = other->possibleAlignment;
	generationEnabled = other->generationEnabled;
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