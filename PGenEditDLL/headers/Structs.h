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
template<typename Struct>
using decay_fully = std::remove_pointer_t<std::decay_t<Struct>>;

/*
 Structures
structs.BlvHeader
structs.Button
structs.CurrentTileBin
structs.CustomLods
structs.DChestItem
structs.DecListItem
structs.DialogLogic
structs.Dlg
structs.EventLine
structs.Events2DItem
structs.FaceAnimationInfo
structs.FacetData
structs.FloatVector
structs.Fnt
structs.FogChances
structs.GameClassKinds
structs.GameClasses
structs.GameRaces
structs.GeneralStoreItemKind
structs.HistoryTxtItem
structs.HouseMovie
structs.IFTItem
structs.Item
structs.ItemsTxtItem
structs.LanguageLod
structs.LanguageLodFile
structs.LloydBeaconSlot
structs.Lod
structs.LodBitmap
structs.LodFile
structs.LodPcx
structs.LodRecord
structs.LodSprite
structs.LodSpriteD3D
structs.LodSpriteLine
structs.MapChest
structs.MapDoor
structs.MapExtra
structs.MapFacet
structs.MapLight
structs.MapModel
structs.MapMonster
structs.MapNote
structs.MapObject
structs.MapOutline
structs.MapOutlines
structs.MapRoom
structs.MapSprite
structs.MapStatsItem
structs.MapVertex
structs.MissileSetup
structs.ModelFacet
structs.ModelVertex
structs.MonListItem
structs.MonsterAttackInfo
structs.MonsterKind
structs.MonsterSchedule
structs.MonstersTxtItem
structs.MoveToMap
structs.NPC
structs.NPCNewsItem
structs.NPCProfTxtItem
structs.OODialogManager
structs.ObjListItem
structs.ObjectRef
structs.OdmHeader
structs.OverlayItem
structs.PFTItem
structs.PatchOptions
structs.Player
structs.ProgressBar
structs.SFT
structs.SFTItem
structs.ShopItemKind
structs.SoundsItem
structs.SpawnPoint
structs.SpcItemsTxtItem
structs.SpellBuff
structs.SpellEffect
structs.SpellInfo
structs.SpellsTxtItem
structs.SpritesLod
structs.StartStat
structs.StdItemsTxtItem
structs.TFTItem
structs.TileItem
structs.TilesetDef
structs.TownPortalTownInfo
structs.TravelInfo
structs.Weather
 */


/*
structs.Arcomage
structs.ArcomageAction
structs.ArcomageActions
structs.ArcomageCard
structs.ArcomagePlayer
structs.BSPNode
structs.BaseBonus
structs.BaseLight
structs.BitmapsLod
 **/

template<typename GameStructure>
struct GameSpecificStructsBase
{
    using Game = std::decay_t<GameStructure>;
    using Party = decay_fully<decltype(Game::party)>;
    using Map = decay_fully<decltype(Game::map)>;
    using Mouse = decay_fully<decltype(Game::mouse)>;
    using Screen = decay_fully<decltype(Game::mouse)>;
    using Player = decay_fully<decltype(Party::playersArray[0])>;
    using BSPNode = decay_fully<decltype(Map::BSPNodes[0])>;
    using BaseBonus = decay_fully<decltype(Player::stats._0)>;
    using ActionItem = decay_fully<decltype(Game::actions[0])>;
    using Arcomage = decay_fully<decltype(Game::actions[0])>;
    using ItemsTxtItem = decay_fully<decltype(Game::itemsTxt[0])>;
    using SpcItemsTxtItem = decay_fully<decltype(Game::spcItemsTxt[0])>;
    using StdItemsTxtItem = decay_fully<decltype(Game::stdItemsTxt[0])>;
	using Item = decay_fully<decltype(Player::items)>;
};

template struct GameSpecificStructsBase<mm6::Game>;
template struct GameSpecificStructsBase<mm7::Game>;
template struct GameSpecificStructsBase<mm8::Game>;

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