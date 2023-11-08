#pragma once
#include "pch.h"
#include "main.h"
#include "globals.h"

/*
template<size_t ver>
struct GameSpecificStructs;*/

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

/*
enum GameStructType
{
	GAME_STRUCT_TYPE_ITEM,
	GAME_STRUCT_TYPE_PLAYER,
	GAME_STRUCT_TYPE_GAME,
};

using MM6Structs = GameSpecificStructs<6>;
using MM7Structs = GameSpecificStructs<7>;
using MM8Structs = GameSpecificStructs<8>;*/

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

/*
void gameVersionDispatch(void* stru, int what, auto func)
{
	GENERATE_DISPATCH_CODE(Item, stru, func, what, GAME_STRUCT_TYPE_ITEM);
}

inline void gameVersionDispatchItem(void* stru, auto func)
{
	gameVersionDispatch(stru, GAME_STRUCT_TYPE_ITEM, func);
}*/

#undef GENERATE_DISPATCH_CODE

// std::decay doesn't remove pointer after array is converted to it
// first duplicated std::decay is for cases, where qualifier removal order (for reference to pointer to const value for example) causes some of them to remain
// TODO: some recursive template version?
template<typename Struct>
using decay_fully = std::decay_t<std::remove_pointer_t<std::decay_t<Struct>>>;

template<size_t s>
	requires (s == 6) || (s == 7) || (s == 8)
struct GameVersionStructs;

template<class>
struct GameSpecificStructs;

namespace
{
    template<class T, class Type6, class Type7, class Type8>
    using GetTypeMM = std::conditional_t<SAME(T, Type6), Type6, std::conditional_t<SAME(T, Type7), Type7, Type8>>;

    template<class T, class Type6, class Type7, class Type8>
    constexpr bool hasTypeMM = SAME(T, Type6) || SAME(T, Type7) || SAME(T, Type8);

    template<class T, class Type6, class Type7, class Type8>
    constexpr size_t GetVersionMM = SAME(T, Type6) ? 6 : (SAME(T, Type7) ? 7 : 8);
}

// TODO: a way to index a struct by one struct type and get the corresponding type for any other game (so, you do:
// GameSpecificStructs<mm6::Lod>::currentStructVersion7
// and get back mm7::Lod type

#define SAME_BASE(a, b) std::is_same<std::decay_t<a>, b>
#define GEN_DEF_1(name) GEN_DEF_2(name, name)
#define GEN_DEF_2(name, codeName) using Any##name##Variant = std::variant<mm6::codeName*, mm7::codeName*, mm8::codeName*>;\
template<typename T>\
concept Any##name##Struct = SAME(T, mm6::codeName) || SAME(T, mm7::codeName) || SAME(T, mm8::codeName);\
template<Any##name##Struct T>\
struct GameSpecificStructs<T> : GameVersionStructs<GetVersionMM<T, mm6::codeName, mm7::codeName, mm8::codeName>>\
{\
	static constexpr const size_t gameVersion = GetVersionMM<T, mm6::codeName, mm7::codeName, mm8::codeName>;\
};

// X macro
#define GEN_DEF(...) GEN_DEF_CURRENT(__VA_ARGS__)

/* commented out are those that aren't in all games */
#define GEN_STRUCT_DEFS \
GEN_DEF(ActionItem);\
/* GEN_DEF(Arcomage); */\
/* GEN_DEF(ArcomageAction); */\
/* GEN_DEF(ArcomageActions); */\
/* GEN_DEF(ArcomageCard); */\
/* GEN_DEF(ArcomagePlayer); */\
GEN_DEF(BSPNode);\
GEN_DEF(BaseBonus);\
/* GEN_DEF(BaseLight); */\
GEN_DEF(BitmapsLod);\
GEN_DEF(BlvHeader);\
GEN_DEF(CustomLods);\
GEN_DEF(DChestItem);\
GEN_DEF(DecListItem);\
GEN_DEF(DialogLogic);\
GEN_DEF(Dlg);\
/* GEN_DEF(EditablePChar); */\
GEN_DEF(EventLine);\
GEN_DEF(Events2DItem);\
GEN_DEF(FaceAnimationInfo);\
GEN_DEF(FacetData);\
/* GEN_DEF(FloatVector); */\
/* GEN_DEF(Fnt); */\
/* GEN_DEF(FogChances); */\
GEN_DEF(Game, GameStructure);\
GEN_DEF(GameClassKinds);\
GEN_DEF(GameClasses);\
GEN_DEF(Map, GameMap);\
GEN_DEF(Mouse, GameMouse);\
GEN_DEF(Party, GameParty);\
/* GEN_DEF(GameRaces); */\
GEN_DEF(Screen, GameScreen);\
/* GEN_DEF(HistoryTxtItem); */\
GEN_DEF(HouseMovie);\
GEN_DEF(IFTItem);\
GEN_DEF(Item);\
GEN_DEF(ItemsTxtItem);\
GEN_DEF(LloydBeaconSlot);\
GEN_DEF(Lod);\
GEN_DEF(LodBitmap);\
GEN_DEF(LodFile);\
/* GEN_DEF(LodPcx); */\
GEN_DEF(LodRecord);\
GEN_DEF(LodSprite);\
GEN_DEF(LodSpriteD3D);\
GEN_DEF(LodSpriteLine);\
GEN_DEF(MapChest);\
GEN_DEF(MapDoor);\
GEN_DEF(MapExtra);\
GEN_DEF(MapFacet);\
GEN_DEF(MapLight);\
GEN_DEF(MapModel);\
GEN_DEF(MapMonster);\
GEN_DEF(MapObject);\
GEN_DEF(MapOutline);\
GEN_DEF(MapOutlines);\
GEN_DEF(MapRoom);\
GEN_DEF(MapSprite);\
GEN_DEF(MapStatsItem);\
GEN_DEF(MapVertex);\
GEN_DEF(MissileSetup);\
GEN_DEF(ModelFacet);\
GEN_DEF(ModelVertex);\
GEN_DEF(MonListItem);\
GEN_DEF(MonsterAttackInfo);\
/* GEN_DEF(MonsterKind); */\
GEN_DEF(MonsterSchedule);\
GEN_DEF(MonstersTxtItem);\
/* GEN_DEF(MouseStruct); */\
GEN_DEF(MoveToMap);\
GEN_DEF(NPC);\
/* GEN_DEF(NPCProfTxtItem); */\
GEN_DEF(ObjListItem);\
GEN_DEF(ObjectRef2);\
GEN_DEF(OdmHeader);\
GEN_DEF(OverlayItem);\
GEN_DEF(PFTItem);\
GEN_DEF(PatchOptions);\
/* GEN_DEF(PlayerResistanceBaseBonus); */\
GEN_DEF(ProgressBar);\
GEN_DEF(SFT);\
/* GEN_DEF(SFTGroupType); */\
GEN_DEF(SFTItem);\
GEN_DEF(ShopItemKind);\
GEN_DEF(SoundsItem);\
GEN_DEF(SpawnPoint);\
GEN_DEF(SpcItemsTxtItem);\
GEN_DEF(SpellBuff);\
/* GEN_DEF(SpellEffect); */\
GEN_DEF(SpellInfo);\
GEN_DEF(SpellsTxtItem);\
GEN_DEF(SpritesLod);\
/* GEN_DEF(StartStat); */\
GEN_DEF(StdItemsTxtItem);\
GEN_DEF(TFTItem);\
GEN_DEF(TileItem);\
GEN_DEF(TilesetDef);\
GEN_DEF(TownPortalTownInfo);\
GEN_DEF(TravelInfo);\
GEN_DEF(Weather);

// "macro overloading" on number of arguments
#define GET_MACRO(_1, _2, name, ...) name

#pragma warning(push)
#pragma warning(disable: 4005) // "macro redefinition"
// base definitions, incl. structure template taking any game type
#define GEN_DEF_CURRENT(...) GET_MACRO(__VA_ARGS__, GEN_DEF_2, GEN_DEF_1)(__VA_ARGS__)
GEN_STRUCT_DEFS;
#define GEN_DEF_2(name, codeName) using name = mm6::codeName;

template<>
struct GameVersionStructs<6>
{
	// mm6 definitions
	GEN_STRUCT_DEFS;
};

#define GEN_DEF_2(name, codeName) using name = mm7::codeName;

template<>
struct GameVersionStructs<7>
{
	// mm7 definitions
    GEN_STRUCT_DEFS;
};

#define GEN_DEF_2(name, codeName) using name = mm8::codeName;

template<>
struct GameVersionStructs<8>
{
	// mm8 definitions
    GEN_STRUCT_DEFS;
};

#pragma warning(pop)
#undef GEN_DEF
#undef GEN_DEF_1
#undef GEN_DEF_2
#undef GET_MACRO
#undef GEN_DEF_CURRENT
#undef GEN_STRUCT_DEFS
#undef SAME_BASE