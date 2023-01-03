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
	static bool IS_MERGE; // ditto, todo: merge versions !!!!! structs.Player.Attrs support
	static const double MINIMUM_AFFINITY; // multiplied by weights
	static const double MAXIMUM_AFFINITY; // ditto

	// generate classes, if affinity is 0 then weight 0, otherwise weight at least 1
	// add openresty luajit to project/libs/iat dll/check lua state/registryindex
	// FIND MAIN LOOP IN MM6/7/8 AND HOOK IT TO SOLVE "different thread access crashes application" PROBLEM
	// !!! MAKE SURE PAUSED GAME WILL STILL USE HOOK !!!
	// begin writing unit tests

	// lua struct generator - split structs between multiple files
	// solve problem of requiring three edits to each file by searching for predefined string
	// and replacing it with new content (if file exists then don't add includes etc.)

	std::vector<PlayerData> playerData;

	Generator();
	virtual ~Generator();

	bool* generateForPlayer;
	PartyType partyType;
	void** players;
	void** mockPlayers; // for testing
	bool mock;

	bool unsetArtifactsFoundBits;
	bool setArtifactsFoundBitsIfGenerated;
	bool miscSkillsAtMostOnePlayer; // there's almost no reason to have two trap disarmers or three item identifiers

	struct State // will hold current generation state (like generated classes etc.)
	{
		std::vector<int> classes;
		std::vector<int> levels;
		double averageLevel = 0;
		int currentPlayer = INVALID_ID;
	} state;

	ClassGenerationSettings defaultGlobalClassSettings;
	std::unordered_map<int, ClassGenerationSettings> globalClassSettings;

	void createClassSettings(); // fill map with default settings for base classes

	virtual bool readFromJson(const Json& json) override;
	virtual bool writeToJson(Json& json) override;
	template<typename Player>
	bool generate();
	virtual void setDefaults() override;

	/*
	GENERATION ORDER:
	- classes
	- level

	unordered yet:
	- items
	- skills
	- spells
	- statistics
	- resistances
	*/
};