#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm7
{
	struct ArcomagePlayer // size: 0xBC
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		bool human;
		SKIP(3);
		int32_t tower;
		int32_t wall;
		std::array<std::array<uint8_t, 4>, 3> income; // Unknown type
		std::array<int32_t, 3> res;
		std::array<int32_t, 10> cards;
		std::array<std::array<int32_t, 2>, 10> unk;
	};
	static_assert(sizeof(mm7::ArcomagePlayer) == 0xBC, "Invalid \"mm7::ArcomagePlayer\" structure size");
	static_assert(offsetof(mm7::ArcomagePlayer, human) == 32);
	static_assert(offsetof(mm7::ArcomagePlayer, tower) == 36);
	static_assert(offsetof(mm7::ArcomagePlayer, wall) == 40);
	static_assert(offsetof(mm7::ArcomagePlayer, income) == 44);
	static_assert(offsetof(mm7::ArcomagePlayer, res) == 56);
	static_assert(offsetof(mm7::ArcomagePlayer, cards) == 68);
	static_assert(offsetof(mm7::ArcomagePlayer, unk) == 108);



	struct ArcomageAction // size: 0x9
	{
		std::array<int8_t, 3> income;
		std::array<int8_t, 3> res;
		int8_t damage;
		int8_t wall;
		int8_t tower;
	};
	static_assert(sizeof(mm7::ArcomageAction) == 0x9, "Invalid \"mm7::ArcomageAction\" structure size");
	static_assert(offsetof(mm7::ArcomageAction, res) == 3);
	static_assert(offsetof(mm7::ArcomageAction, damage) == 6);
	static_assert(offsetof(mm7::ArcomageAction, wall) == 7);
	static_assert(offsetof(mm7::ArcomageAction, tower) == 8);



	struct ArcomageActions // size: 0x1D
	{
		bool playAgain;
		int8_t discardCards;
		mm7::ArcomageAction me;
		mm7::ArcomageAction enemy;
		mm7::ArcomageAction all;
	};
	static_assert(sizeof(mm7::ArcomageActions) == 0x1D, "Invalid \"mm7::ArcomageActions\" structure size");
	static_assert(offsetof(mm7::ArcomageActions, discardCards) == 1);
	static_assert(offsetof(mm7::ArcomageActions, me) == 2);
	static_assert(offsetof(mm7::ArcomageActions, enemy) == 11);
	static_assert(offsetof(mm7::ArcomageActions, all) == 20);



	struct ArcomageCard // size: 0x6C
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		int32_t sprite;
		int8_t costKind;
		std::array<int8_t, 3> costIncome;
		std::array<int8_t, 3> costRes;
		bool discardable;
		int32_t if_;
		mm7::ArcomageActions then;
		mm7::ArcomageActions else_;
		SKIP(2);
	};
	static_assert(sizeof(mm7::ArcomageCard) == 0x6C, "Invalid \"mm7::ArcomageCard\" structure size");
	static_assert(offsetof(mm7::ArcomageCard, sprite) == 32);
	static_assert(offsetof(mm7::ArcomageCard, costKind) == 36);
	static_assert(offsetof(mm7::ArcomageCard, costIncome) == 37);
	static_assert(offsetof(mm7::ArcomageCard, costRes) == 40);
	static_assert(offsetof(mm7::ArcomageCard, discardable) == 43);
	static_assert(offsetof(mm7::ArcomageCard, if_) == 44);
	static_assert(offsetof(mm7::ArcomageCard, then) == 48);
	static_assert(offsetof(mm7::ArcomageCard, else_) == 77);



	struct Arcomage // size: 0x505710
	{
		SKIP(5108644);
		int32_t AI;
		std::array<mm7::ArcomageCard, 87> cardKinds;
		SKIP(4);
		int32_t startingTower;
		int32_t startingWall;
		union
		{
			std::array<std::array<uint8_t, 4>, 3> startingIncome; // Unknown type
			struct
			{
				std::array<uint8_t, 4> startingIncomeBricks; // Unknown type
				std::array<uint8_t, 4> startingIncomeGems; // Unknown type
				std::array<uint8_t, 4> startingIncomeBeasts; // Unknown type
			};
		};
		std::array<uint8_t, 4> cardsCount; // Unknown type
		std::array<int32_t, 3> minIncome;
		int32_t towerToWin;
		int32_t resToWin;
		SKIP(146248);
		std::array<int32_t, 108> deck;
		SKIP(4);
		std::array<mm7::ArcomagePlayer, 2> players;
		SKIP(4);
		union
		{
			std::array<int32_t, 3> startingRes;
			struct
			{
				int32_t startingBricks;
				int32_t startingGems;
				int32_t startingBeasts;
			};
		};
	};
	static_assert(sizeof(mm7::Arcomage) == 0x505710, "Invalid \"mm7::Arcomage\" structure size");
	static_assert(offsetof(mm7::Arcomage, AI) == 5108644);
	static_assert(offsetof(mm7::Arcomage, cardKinds) == 5108648);
	static_assert(offsetof(mm7::Arcomage, startingTower) == 5118048);
	static_assert(offsetof(mm7::Arcomage, startingWall) == 5118052);
	static_assert(offsetof(mm7::Arcomage, startingIncome) == 5118056);
	static_assert(offsetof(mm7::Arcomage, startingIncomeBricks) == 5118056);
	static_assert(offsetof(mm7::Arcomage, startingIncomeGems) == 5118060);
	static_assert(offsetof(mm7::Arcomage, startingIncomeBeasts) == 5118064);
	static_assert(offsetof(mm7::Arcomage, cardsCount) == 5118068);
	static_assert(offsetof(mm7::Arcomage, minIncome) == 5118072);
	static_assert(offsetof(mm7::Arcomage, towerToWin) == 5118084);
	static_assert(offsetof(mm7::Arcomage, resToWin) == 5118088);
	static_assert(offsetof(mm7::Arcomage, deck) == 5264340);
	static_assert(offsetof(mm7::Arcomage, players) == 5264776);
	static_assert(offsetof(mm7::Arcomage, startingRes) == 5265156);
	static_assert(offsetof(mm7::Arcomage, startingBricks) == 5265156);
	static_assert(offsetof(mm7::Arcomage, startingGems) == 5265160);
	static_assert(offsetof(mm7::Arcomage, startingBeasts) == 5265164);
}
namespace mm8
{
	struct ArcomagePlayer // size: 0xBC
	{
		std::array<char, 32> name; // fixed size string, requires null terminator
		bool human;
		SKIP(3);
		int32_t tower;
		int32_t wall;
		std::array<std::array<uint8_t, 4>, 3> income; // Unknown type
		std::array<int32_t, 3> res;
		std::array<int32_t, 10> cards;
		std::array<std::array<int32_t, 2>, 10> unk;
	};
	static_assert(sizeof(mm8::ArcomagePlayer) == 0xBC, "Invalid \"mm8::ArcomagePlayer\" structure size");
	static_assert(offsetof(mm8::ArcomagePlayer, human) == 32);
	static_assert(offsetof(mm8::ArcomagePlayer, tower) == 36);
	static_assert(offsetof(mm8::ArcomagePlayer, wall) == 40);
	static_assert(offsetof(mm8::ArcomagePlayer, income) == 44);
	static_assert(offsetof(mm8::ArcomagePlayer, res) == 56);
	static_assert(offsetof(mm8::ArcomagePlayer, cards) == 68);
	static_assert(offsetof(mm8::ArcomagePlayer, unk) == 108);



	struct Arcomage // size: 0x516D68
	{
		SKIP(5177892);
		int32_t AI;
		SKIP(11020);
		int32_t startingTower;
		int32_t startingWall;
		std::array<std::array<uint8_t, 4>, 3> startingIncome; // Unknown type
		std::array<uint8_t, 4> cardsCount; // Unknown type
		std::array<int32_t, 3> minIncome;
		int32_t towerToWin;
		int32_t resToWin;
		SKIP(147072);
		std::array<mm8::ArcomagePlayer, 2> players;
		SKIP(4);
		std::array<int32_t, 3> startingRes;
	};
	static_assert(sizeof(mm8::Arcomage) == 0x516D68, "Invalid \"mm8::Arcomage\" structure size");
	static_assert(offsetof(mm8::Arcomage, AI) == 5177892);
	static_assert(offsetof(mm8::Arcomage, startingTower) == 5188916);
	static_assert(offsetof(mm8::Arcomage, startingWall) == 5188920);
	static_assert(offsetof(mm8::Arcomage, startingIncome) == 5188924);
	static_assert(offsetof(mm8::Arcomage, cardsCount) == 5188936);
	static_assert(offsetof(mm8::Arcomage, minIncome) == 5188940);
	static_assert(offsetof(mm8::Arcomage, towerToWin) == 5188952);
	static_assert(offsetof(mm8::Arcomage, resToWin) == 5188956);
	static_assert(offsetof(mm8::Arcomage, players) == 5336032);
	static_assert(offsetof(mm8::Arcomage, startingRes) == 5336412);
}

#pragma pack(pop)