#pragma once
#include "main.h"
#include "StructAccessor.h"

class GameStructAccessor;
extern GameStructAccessor* gameAccessor;
// structures mm6::GameStructure, mm7::GameStructure, mm8::GameStructure are similar
// most contain same fields, maybe slightly with different data types
// what we need to do is to create a class that will be able to access all of them via getters/setters
// so, we need to add getter/setter methods for each field in each structure, with caveat that some fields have different widths
// (for example, int16_t in mm6, int32_t in mm7, int32_t in mm8)
// and we need to choose the widest type for each field
// for now I only want to handle primitives and single-level arrays of primitives (no arrays here, only below)
// the define below is of form (type, fieldName, accessorNamePart)

//,(int8_t, minMeleeRecoveryTime, MinMeleeRecoveryTime, Game) // this one is actually an array (custom type), and even if I put it into array section, it requires custom behavior


#define PGENEDIT_GETTERS_SETTERS\
	(char**, autonoteTxt, AutonoteTxt, Game),\
	(int32_t, currentScreen, CurrentScreen, Game),\
	(int32_t, mainMenuCode, MainMenuCode, Game),\
	(bool, inQuestionDialog, InQuestionDialog, Game, (8)),\
	(int32_t, currentCharScreen, CurrentCharScreen, Game),\
	(int32_t, windowed, Windowed, Game),\
	(int32_t, dialogNPC, DialogNpc, Game),\
	(int32_t, NPCCommand, npcCommand, Game),\
	(int32_t, houseScreen, HouseScreen, Game),\
	(int32_t, houseNPCSlot, HouseNPCSlot, Game),\
	(int32_t, houseNPCSlotsCount, HouseNPCSlotsCount, Game),\
	(int32_t, houseCost, HouseCost, Game),\
	(int32_t, houseAllowAction, HouseAllowAction, Game),\
	(int32_t, houseActionInfo, HouseActionInfo, Game),\
	(int32_t, houseTeachMastery, HouseTeachMastery, Game),\
	(int32_t, housePicType, HousePicType, Game),\
	(int32_t, houseOwnerPic, HouseOwnerPic, Game),\
	(int32_t, houseExitMap, HouseExitMap, Game),\
	(int32_t, loadingScreen, LoadingScreen, Game),\
	(char**, classNames, ClassNames, Game)/* this is here, because it's changed into pointer by me*/

/*
// lua code which defines some of the fields
// if a line has "array" declaration before, it should go into array section
// EditPChar is simply char*
define
	[mmv(0x4C3E10, 0x4F076C, 0x500D30)].array(mmv(17, 11, 11)).i4  'GuildJoinCost'
	[mmv(0x4D5088, 0x5079F8, 0x5192EC)].array(7).EditPChar  'StatsNames'
	 .Info{Sig = "[stat:const.Stats]"}
	[mmv(0x56F27C, 0x5C85F8, 0x5E4990)].array(7).EditPChar  'StatsDescriptions'
	 .Info{Sig = "[stat:const.Stats]"}
	[mmv(0x970C7C, 0xAE3150, 0xBB3060)].array(mmv(31, 37, 39)).EditPChar  'SkillNames'
	 .Info{Sig = "[skill:const.Skills]"}
	[mmv(0x56F394, 0x5C88F0, 0x5E4CB0)].array(mmv(31, 37, 39)).EditPChar  'SkillDescriptions'
	 .Info{Sig = "[skill:const.Skills]"}
	[mmv(0x56B76C, 0x5C8858, 0x5E4C10)].array(mmv(31, 37, 39)).EditPChar  'SkillDesNormal'
	 .Info{Sig = "[skill:const.Skills]"}
	[mmv(0x56F29C, 0x5C87C0, 0x5E4B70)].array(mmv(31, 37, 39)).EditPChar  'SkillDesExpert'
	 .Info{Sig = "[skill:const.Skills]"}
	[mmv(0x56F318, 0x5C8728, 0x5E4AD0)].array(mmv(31, 37, 39)).EditPChar  'SkillDesMaster'
	 .Info{Sig = "[skill:const.Skills]"}
	if mmver > 6 then
		define[mm78(0x5C8690, 0x5E4A30)].array(mmv(31, 37, 39)).EditPChar  'SkillDesGM'
	 .Info{Sig = "[skill:const.Skills]"}
	end
	define[mmv(0x970BEC, 0xAE3070, 0xBB2FD0)].array(mmv(18, 36, 36)).EditPChar  'ClassNames'
	 .Info{Sig = "[class:const.Class]"}
	[mmv(0x56B6C0, 0x5C8560, 0x5E48F0)].array(mmv(18, 36, 36)).EditPChar  'ClassDescriptions'
*/

#define PGENEDIT_ARRAY_GETTERS_SETTERS \
	(int16_t, spellSounds, SpellSounds, Game),\
	(int16_t, skillRecoveryTimes, SkillRecoveryTimes, Game),\
	(int32_t, houseNPCs, HouseNpcs, Game),\
	(int32_t, guildJoinCost, GuildJoinCost, Game),\
	(char*, statsNames, StatsNames, Game),\
	(char*, statsDescriptions, StatsDescriptions, Game),\
	(char*, skillNames, SkillNames, Game),\
	(char*, skillDescriptions, SkillDescriptions, Game),\
/*	(char*, skillDesNormal, SkillDesNormal, Game),\
	(char*, skillDesExpert, SkillDesExpert, Game),\
	(char*, skillDesMaster, SkillDesMaster, Game),\
	(char*, skillDesGM, SkillDesGM, Game), \*/\
	(char*, classDescriptions, ClassDescriptions, Game)


//,(int32_t*, autonoteCategory, AutonoteCategory)
class GameStructAccessor : StructAccessorGenericFor
{
public:
	virtual HWND getWindowHandle() = 0;
	virtual int getCurrentPlayer() = 0;

	virtual void* getIconsLodPtr() = 0;
	virtual ArrayData getItemsTxtArrayData() = 0;
	virtual ArrayData getStdItemsTxtArrayData() = 0;
	virtual ArrayData getSpcItemsTxtArrayData() = 0;
	virtual int64_t getTime() = 0;
	virtual void setTime(int64_t time) = 0;

	template<typename Function>
	static auto forAnyGameStructExecute(Function&& func)
	{
		return StructAccessorGenericFor::genericForSingleStructExecute<Function, mm6::Game, mm7::Game, mm8::Game>(nullptr, std::forward<Function>(func));
	}

	PGENEDIT_GETTER_SETTER_METHODS_DECL(PGENEDIT_GETTERS_SETTERS)

	PGENEDIT_ARRAY_GETTER_SETTER_METHODS_DECL(PGENEDIT_ARRAY_GETTERS_SETTERS)

	virtual ~GameStructAccessor();
};
template<typename Game>
class TemplatedGameStructAccessor : public GameStructAccessor
{
	using GameType = std::decay_t<Game>;
	static inline GameType* const game = reinterpret_cast<GameType*>(0);
public:
	HWND getWindowHandle() override;
	int getCurrentPlayer() override;

	// Inherited via GameStructAccessor
	virtual int64_t getTime() override;

	virtual void setTime(int64_t time) override;

	// Inherited via GameStructAccessor
	virtual void* getIconsLodPtr() override
	{
		return &game->iconsLod;
	}
	virtual ArrayData getItemsTxtArrayData() override
	{
		return ArrayData(game->itemsTxt, game->itemsTxt_sizePtr);
	}
	virtual ArrayData getStdItemsTxtArrayData() override
	{
		return ArrayData(game->stdItemsTxt, game->stdItemsTxt_size);
    }
    virtual ArrayData getSpcItemsTxtArrayData() override
    {
        return ArrayData(game->spcItemsTxt, game->spcItemsTxt_size);
    }

	PGENEDIT_GETTER_SETTER_METHODS_DEF(game->, PGENEDIT_GETTERS_SETTERS)

	PGENEDIT_ARRAY_GETTER_SETTER_METHODS_DEF(game->, PGENEDIT_ARRAY_GETTERS_SETTERS)
};

#undef PGENEDIT_GETTERS_SETTERS
#undef PGENEDIT_ARRAY_GETTERS_SETTERS

using GameStructAccessor_6 = TemplatedGameStructAccessor<mm6::Game>;
using GameStructAccessor_7 = TemplatedGameStructAccessor<mm7::Game>;
using GameStructAccessor_8 = TemplatedGameStructAccessor<mm8::Game>;
