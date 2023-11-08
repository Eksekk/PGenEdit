#pragma once
#include "main.h"
#include "GeneratorDataBase.h"

class PlayerData;

class StatisticsData : public GeneratorDataBase
{
public:
	int index;
	bool generationEnabled;
	bool efficientUseOfBreakpoints;
	PlayerData& playerData;
	StatisticsData(int index, PlayerData& playerData);
	StatisticsData() = delete;
	// Inherited via GeneratorDataBase
	virtual bool readFromJson(const Json& json) override;
	virtual bool writeToJson(Json& json) override;
	virtual void setDefaults() override;
	template<typename Player>
	bool generate(Player* player);

	// Inherited via GeneratorDataBase
	virtual void randomize() override;
	virtual void copyFrom(const GeneratorDataBase& source) override;

	StatisticsData& operator=(const StatisticsData& other);

	bool operator==(const StatisticsData& other) const;
	bool operator!=(const StatisticsData& other) const;
};

template<typename Player>
inline bool StatisticsData::generate(Player* player)
{
	return false;
}
