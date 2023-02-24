#pragma once
#include "pch.h"
#include "main.h"
#include "Item.h"
#include "Player.h"
#include "Game.h"

template<size_t ver>
struct GameSpecificStructs;

template<>
struct GameSpecificStructs<6>
{
	using Item = mm6::Item;
	using Player = mm6::Player;
	using Game = mm6::Game;
};

template<>
struct GameSpecificStructs<7>
{
	using Item = mm7::Item;
	using Player = mm7::Player;
	using Game = mm7::Game;
};

template<>
struct GameSpecificStructs<8>
{
	using Item = mm8::Item;
	using Player = mm8::Player;
	using Game = mm8::Game;
};

using MM6Structs = GameSpecificStructs<6>;
using MM7Structs = GameSpecificStructs<7>;
using MM8Structs = GameSpecificStructs<8>;