#pragma once
#include "pch.h"
#include "main.h"
#include "Player.h"
#include "GeneratorDataBase.h"
#include "Enum_const.h"
#include "ClassGenerationData.h"
#include "PlayerData.h"

inline void checkAffinity(double aff);
class PlayerData;

extern const int INVALID_ID;

class Generator : public GeneratorDataBase
{
public:
	// CIRCULAR HEADER DEPENDENCIES CAUSE BOGUS ERRORS
	/* to solve:
	either access state in cpp only (via global generator pointer), or extract class settings to separate file, or store pointer to default class settings here
	*/

	// PARTY EDITOR AS NECESSARY COMPLEMENT TO GENERATOR

	// generate classes, if affinity is 0 then weight 0, otherwise weight at least 1
	// add openresty luajit to project/libs/iat dll/check lua state/registryindex
	// FIND MAIN LOOP IN MM6/7/8 AND HOOK IT TO SOLVE "different thread access crashes application" PROBLEM
	// !!! MAKE SURE PAUSED GAME WILL STILL USE HOOK !!!
	// begin writing unit tests

	// lua struct generator - split structs between multiple files
	// solve problem of requiring three edits to each file by searching for predefined string
	// and replacing it with new content (if file exists then don't add includes etc.)

	// 2023-01-18 removed generator's and main window's class settings - add a lot of complexity,
	// and player will be able to copy settings around / load part of them
	

	// TOO MANY CONTROLS (500+) IN A SINGLE WINDOW, EVEN IF INVISIBLE, CAUSE EXTREME LAG WHEN MOVING WINDOW
	// SOLUTION - SPLIT INTO DIFFERENT FRAMES/DIALOGS

	std::vector<std::unique_ptr<PlayerData>> playerData; // pointer because by value creates problems related to copying and destruction

	Generator();
	virtual ~Generator();

	PartyType partyType;
	void** players;

	bool unsetArtifactsFoundBits;
	bool setArtifactsFoundBitsIfGenerated;
	bool miscSkillsAtMostOnePlayer; // there's almost no reason to have two trap disarmers or three item identifiers
	unsigned long long seed;
	bool randomSeed;
	bool randomInFileIsExact; // if true, writes exact seed to file, otherwise writes information that it's random
							  // (another user will have random seed too)

	static const unsigned MAX_AVERAGE_LEVEL;
	static const unsigned MIN_AVERAGE_LEVEL;
	unsigned averageLevel;

	struct State // will hold current generation state (like generated classes etc.)
	{
		std::vector<int> classes;
		std::vector<int> levels;
		double averageLevel = 0;
		int currentPlayer = INVALID_ID;
	} state;
	Alignment possibleAlignment; // will override specific ones from class settings

	PlayerData defaultPlayerData;

	virtual bool readFromJson(const Json& json) override;
	virtual bool writeToJson(Json& json) override;
	template<typename Player>
	bool generate();
	virtual void setDefaults() override;


	// Inherited via GeneratorDataBase
	virtual void randomize() override;

	virtual void copyFrom(const GeneratorDataBase& source) override;

	Generator& operator=(const Generator& other);

	bool operator==(const Generator& other) const;
	bool operator!=(const Generator& other) const;

	/*
	GENERATION ORDER:
	- level
	- classes

	unordered yet:
	- items
	- skills
	- spells
	- statistics
	- resistances
	*/
};