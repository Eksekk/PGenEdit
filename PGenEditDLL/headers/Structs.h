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

// std::decay doesn't remove pointer after array is converted to it
template<typename Struct>
using decay_fully = std::remove_pointer_t<std::decay_t<Struct>>;

template<typename GameStructure>
struct GameSpecificStructsBase
{
	using Game = std::decay_t<GameStructure>;
	using Party = decay_fully<decltype(Game::party)>;
	using Player = decay_fully<decltype(Party::playersArray[0])>;
	using Item = decay_fully<decltype(Player::items)>;
};

template struct GameSpecificStructsBase<mm6::Game>;

#define genDef(name) using Any##name##Variant = std::variant<mm6::name*, mm7::name*, mm8::name*>;\
namespace mm6\
{\
	using name = mm6::name;\
}
genDef(Item);
genDef(Player);
genDef(Lod);
genDef(LodBitmap);
genDef(GameStructure);
genDef(SpellBuff);
genDef(GameParty);
genDef(GameMap);

#undef genDef