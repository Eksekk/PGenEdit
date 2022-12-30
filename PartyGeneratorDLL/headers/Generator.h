#pragma once
#include "pch.h"
#include "main.h"
#include "Player.h"
#include "GeneratorDataBase.h"
#include "Enum_const.h"
#include "ClassGenerationData.h"

inline void checkAffinity(double aff);
class PlayerData;

class Generator : public GeneratorDataBase
{
public:
	// CIRCULAR HEADER DEPENDENCIES CAUSE BOGUS ERRORS
	/* to solve:
	either access state in cpp only (via global generator pointer), or extract class settings to separate file, or store pointer to default class settings here
	*/
	static bool IS_ELEMENTAL_MOD; // changes some game structures, different parsing needed
	static bool IS_MERGE; // ditto, todo: merge versions
	static const double MINIMUM_AFFINITY; // multiplied by weights
	static const double MAXIMUM_AFFINITY; // ditto

	PlayerData* playerData;

	Generator();
	virtual ~Generator();

	bool* generateForPlayer;
	PartyType partyType;
	void** players;
	void** mockPlayers; // for testing
	bool mock;

	bool unsetArtifactsFoundBits;
	bool setArtifactsFoundBitsIfGenerated;

	struct State // will hold current generation state (like generated classes etc.)
	{
		std::vector<int> classes;
		std::vector<int> levels;
		double averageLevel = 0;
		int currentPlayer = INVALID_ID;
	} state;

	ClassGenerationSettings defaultGlobalClassSettings;

	virtual bool readFromJson(const Json& json) override;
	virtual bool writeToJson(Json& json) override;
	template<typename Player>
	bool generate();
	virtual void setDefaults() override;

	/*
	GENERATION ORDER:
	- classes
	- level

	- items
	- skills
	- spells
	- statistics
	- resistances
	*/
};