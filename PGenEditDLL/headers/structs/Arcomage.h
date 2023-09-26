#pragma once
#include "pch.h"
#include "main.h"

#pragma pack(push, 1)

namespace mm7
{
	struct ArcomagePlayer // size: 0xBC
	{
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		bool human; // 0x20 (32 decimal)
		SKIP(3);
		int32_t tower; // 0x24 (36 decimal)
		int32_t wall; // 0x28 (40 decimal)
		std::array<std::array<uint8_t, 4>, 3> income; // Unknown type | 0x2C (44 decimal)
		std::array<int32_t, 3> res; // 0x38 (56 decimal)
		std::array<int32_t, 10> cards; // 0x44 (68 decimal)
		std::array<std::array<int32_t, 2>, 10> unk; // 0x6C (108 decimal)
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
		std::array<int8_t, 3> income; // 0x0 (0 decimal)
		std::array<int8_t, 3> res; // 0x3 (3 decimal)
		int8_t damage; // 0x6 (6 decimal)
		int8_t wall; // 0x7 (7 decimal)
		int8_t tower; // 0x8 (8 decimal)
	};
	static_assert(sizeof(mm7::ArcomageAction) == 0x9, "Invalid \"mm7::ArcomageAction\" structure size");
	static_assert(offsetof(mm7::ArcomageAction, res) == 3);
	static_assert(offsetof(mm7::ArcomageAction, damage) == 6);
	static_assert(offsetof(mm7::ArcomageAction, wall) == 7);
	static_assert(offsetof(mm7::ArcomageAction, tower) == 8);



	struct ArcomageActions // size: 0x1D
	{
		bool playAgain; // 0x0 (0 decimal)
		int8_t discardCards; // 0x1 (1 decimal)
		mm7::ArcomageAction me; // 0x2 (2 decimal)
		mm7::ArcomageAction enemy; // 0xB (11 decimal)
		mm7::ArcomageAction all; // 0x14 (20 decimal)
	};
	static_assert(sizeof(mm7::ArcomageActions) == 0x1D, "Invalid \"mm7::ArcomageActions\" structure size");
	static_assert(offsetof(mm7::ArcomageActions, discardCards) == 1);
	static_assert(offsetof(mm7::ArcomageActions, me) == 2);
	static_assert(offsetof(mm7::ArcomageActions, enemy) == 11);
	static_assert(offsetof(mm7::ArcomageActions, all) == 20);



	struct ArcomageCard // size: 0x6C
	{
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		int32_t sprite; // 0x20 (32 decimal)
		int8_t costKind; // 0x24 (36 decimal)
		std::array<int8_t, 3> costIncome; // 0x25 (37 decimal)
		std::array<int8_t, 3> costRes; // 0x28 (40 decimal)
		bool discardable; // 0x2B (43 decimal)
		int32_t if_; // 0x2C (44 decimal) | MMExt info: :const.ArcomageIf
		mm7::ArcomageActions then; // 0x30 (48 decimal)
		mm7::ArcomageActions else_; // 0x4D (77 decimal)
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
		int32_t AI; // 0x4DF3A4 (5108644 decimal) | MMExt info: 0 - 2
		std::array<mm7::ArcomageCard, 87> cardKinds; // 0x4DF3A8 (5108648 decimal)
		SKIP(4);
		int32_t startingTower; // 0x4E1860 (5118048 decimal)
		int32_t startingWall; // 0x4E1864 (5118052 decimal)
		union
		{
			std::array<std::array<uint8_t, 4>, 3> startingIncome; // Unknown type | 0x4E1868 (5118056 decimal)
			struct
			{
				std::array<uint8_t, 4> startingIncomeBricks; // Unknown type | 0x4E1868 (5118056 decimal)
				std::array<uint8_t, 4> startingIncomeGems; // Unknown type | 0x4E186C (5118060 decimal)
				std::array<uint8_t, 4> startingIncomeBeasts; // Unknown type | 0x4E1870 (5118064 decimal)
			};
		};
		std::array<uint8_t, 4> cardsCount; // Unknown type | 0x4E1874 (5118068 decimal) | MMExt info: Internally up to 10 cards are supported.
		std::array<int32_t, 3> minIncome; // 0x4E1878 (5118072 decimal)
		int32_t towerToWin; // 0x4E1884 (5118084 decimal)
		int32_t resToWin; // 0x4E1888 (5118088 decimal)
		SKIP(146248);
		std::array<int32_t, 108> deck; // 0x5053D4 (5264340 decimal)
		SKIP(4);
		std::array<mm7::ArcomagePlayer, 2> players; // 0x505588 (5264776 decimal)
		SKIP(4);
		union
		{
			std::array<int32_t, 3> startingRes; // 0x505704 (5265156 decimal)
			struct
			{
				int32_t startingBricks; // 0x505704 (5265156 decimal)
				int32_t startingGems; // 0x505708 (5265160 decimal)
				int32_t startingBeasts; // 0x50570C (5265164 decimal)
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
		std::array<char, 32> name; // fixed size string, requires null terminator | 0x0 (0 decimal)
		bool human; // 0x20 (32 decimal)
		SKIP(3);
		int32_t tower; // 0x24 (36 decimal)
		int32_t wall; // 0x28 (40 decimal)
		std::array<std::array<uint8_t, 4>, 3> income; // Unknown type | 0x2C (44 decimal)
		std::array<int32_t, 3> res; // 0x38 (56 decimal)
		std::array<int32_t, 10> cards; // 0x44 (68 decimal)
		std::array<std::array<int32_t, 2>, 10> unk; // 0x6C (108 decimal)
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
		int32_t AI; // 0x4F0224 (5177892 decimal) | MMExt info: 0 - 2
		SKIP(11020);
		int32_t startingTower; // 0x4F2D34 (5188916 decimal)
		int32_t startingWall; // 0x4F2D38 (5188920 decimal)
		std::array<std::array<uint8_t, 4>, 3> startingIncome; // Unknown type | 0x4F2D3C (5188924 decimal)
		std::array<uint8_t, 4> cardsCount; // Unknown type | 0x4F2D48 (5188936 decimal) | MMExt info: Internally up to 10 cards are supported.
		std::array<int32_t, 3> minIncome; // 0x4F2D4C (5188940 decimal)
		int32_t towerToWin; // 0x4F2D58 (5188952 decimal)
		int32_t resToWin; // 0x4F2D5C (5188956 decimal)
		SKIP(147072);
		std::array<mm8::ArcomagePlayer, 2> players; // 0x516BE0 (5336032 decimal)
		SKIP(4);
		std::array<int32_t, 3> startingRes; // 0x516D5C (5336412 decimal)
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