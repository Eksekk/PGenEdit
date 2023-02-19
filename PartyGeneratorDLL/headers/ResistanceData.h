#pragma once
#include "pch.h"
#include "main.h"
#include "GeneratorDataBase.h"
#include "Player.h"

class PlayerData;

struct ResistanceDataInner : public GeneratorDataBase
{
	int resistanceId;
	bool useExact; // always sets exact value
	int exactVal;
	bool scaleByLevel; // scales amount by level
	bool subtractFromResistancePoints; // if unset, resistance will get a value in range regardless of available points, and doesn't decrease them
	bool allowMoreThanResistancePoints;
	int priority; // if using resistance points and exact/range, value with most priority will be generated first
	int weight; // relative amount of points that this resistance will get out of total available
	bool useRange;
	std::pair<int, int> rangeVal; // if use range is true, value in this range will be chosen
	bool disabled; // not generated

	// TODO: isExclusive, set in lua

	ResistanceDataInner();

	// Inherited via GeneratorDataBase
	virtual bool readFromJson(const Json& json) override;
	virtual bool writeToJson(Json& json) override;
	virtual void randomize() override;
	virtual void setDefaults() override;
	virtual void copyFrom(const GeneratorDataBase& source) override;

	ResistanceDataInner& operator=(const ResistanceDataInner& other);

	bool operator==(const ResistanceDataInner& other);
	bool operator!=(const ResistanceDataInner& other);
};

class ResistanceData : public GeneratorDataBase
{
public:
	int playerResistancePoints;
	std::vector<ResistanceDataInner> lines;
	bool disabled; // not generated
	int index;
	bool generationEnabled;
	PlayerData& playerData;
	ResistanceData(int index, PlayerData& playerData);
	ResistanceData() = delete;

	template<typename Player>
	bool generate(Player* player);
	bool writeToJson(Json& json) override;
	bool readFromJson(const Json& json) override;
	void setDefaults() override;

	// Inherited via GeneratorDataBase
	virtual void randomize() override;
	virtual void copyFrom(const GeneratorDataBase& source) override;

	ResistanceData& operator=(const ResistanceData& other);

	bool operator==(const ResistanceData& other) const;
	bool operator!=(const ResistanceData& other) const;
};

//base resistances weight/range/exact value, exact number of resistance points or range, scale by level or not
