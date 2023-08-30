#pragma once
#include "pch.h"
#include "main.h"
#include "globals.h"

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

enum GameStructType
{
	GAME_STRUCT_TYPE_ITEM,
	GAME_STRUCT_TYPE_PLAYER,
	GAME_STRUCT_TYPE_GAME,
};

using MM6Structs = GameSpecificStructs<6>;
using MM7Structs = GameSpecificStructs<7>;
using MM8Structs = GameSpecificStructs<8>;

#define GENERATE_DISPATCH_CODE(name, stru, func, what, whatEnum)\
if (whatEnum == what)\
{\
	if (MMVER == 6)\
	{\
		func(reinterpret_cast<mm6::name*>(stru));\
    }\
	else if (MMVER == 7)\
	{\
		func(reinterpret_cast<mm7::name*>(stru));\
    }\
	else if (MMVER == 6)\
	{\
		func(reinterpret_cast<mm8::name*>(stru));\
    }\
}

void gameVersionDispatch(void* stru, int what, auto func)
{
	GENERATE_DISPATCH_CODE(Item, stru, func, what, GAME_STRUCT_TYPE_ITEM);
}

inline void gameVersionDispatchItem(void* stru, auto func)
{
	gameVersionDispatch(stru, GAME_STRUCT_TYPE_ITEM, func);
}

#undef GENERATE_DISPATCH_CODE