#pragma once
#include "pch.h"
#include <unordered_map>
#include <string>
#include <vector>
#include "main.h"
#include "GeneratorDataBase.h"
#include "Player.h"

struct ResistanceDataInner
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
	void setDefaults();
};

class ResistanceData : public GeneratorDataBase
{
public:
	int playerResistancePoints;
	std::vector<ResistanceDataInner> lines;
	bool disabled; // not generated

	template<typename Player>
	bool generate(Player* player);
	bool writeToJson(Json& json) override;
	bool readFromJson(const Json& json) override;
	void setDefaults() override;
};

//base resistances weight/range/exact value, exact number of resistance points or range, scale by level or not
