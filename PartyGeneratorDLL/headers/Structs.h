#pragma once
#include "pch.h"
#include "main.h"

template<size_t ver>
struct GameSpecificStructs;

namespace mm6
{
	using Game = mm6::GameStructure;
}
namespace mm7
{
	using Game = mm7::GameStructure;
}
namespace mm8
{
	using Game = mm8::GameStructure;
}

template<>
struct GameSpecificStructs<6>
{
	using Item = mm6::Item;
	using Player = mm6::Player;
	using Game = mm6::GameStructure;
};

template<>
struct GameSpecificStructs<7>
{
	using Item = mm7::Item;
	using Player = mm7::Player;
	using Game = mm7::GameStructure;
};

template<>
struct GameSpecificStructs<8>
{
	using Item = mm8::Item;
	using Player = mm8::Player;
	using Game = mm8::GameStructure;
};

using MM6Structs = GameSpecificStructs<6>;
using MM7Structs = GameSpecificStructs<7>;
using MM8Structs = GameSpecificStructs<8>;