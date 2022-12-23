#pragma once
#include "pch.h"
#include "main.h"
#include "Player.h"
#include "PlayerData.h"
#include "GeneratorDataBase.h"
#include "Enum_const.h"

inline void checkAffinity(double aff);

class Generator : public GeneratorDataBase
{
public:
	static bool IS_ELEMENTAL_MOD; // changes some game structures, different parsing needed
	static bool IS_MERGE; // ditto, todo: merge versions
	static const double MINIMUM_AFFINITY; // multiplied by weights
	static const double MAXIMUM_AFFINITY; // ditto

	PlayerData* playerData;

	Generator();
	virtual ~Generator();

	int currentPlayer;
	bool* generateForPlayer;
	PartyType partyType;
	void** players;

	virtual bool readFromJson(const Json& json) override;
	virtual bool writeToJson(Json& json) override;
	template<typename Player>
	bool generate();
	virtual void setDefaults() override;
};