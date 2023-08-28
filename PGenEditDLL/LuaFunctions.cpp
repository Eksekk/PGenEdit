#include "pch.h"
#include "LuaFunctions.h"
#include "Structs.h"
#include "SaveGameData.h"

extern "C"
{
	lua_State* Lua = nullptr;

	int runScript(const char* str)
	{
		bool error = luaL_loadstring(Lua, str);
		if (!error)
		{
			error = lua_pcall(Lua, 0, 0, 0);
		}
		if (error)
		{
			const char* msg = lua_tostring(Lua, -1);
			lua_pop(Lua, 1);
			luaL_error(Lua, msg);
			return 0;
		}
		lua_pushboolean(Lua, true);
		return 1;
	}

	// need to be static to work correctly, otherwise lua calls into invalid address
	static int runScript2(lua_State* L)
	{
		// like in asm, if gettop is 2, there are 2 parameters on the stack and stack points at last parameter (not at next free one)
		if (lua_gettop(L) == 0)
		{
			luaL_error(L, "Source code parameter missing");
			return 0;
		}
		if (lua_type(L, -1) != LUA_TSTRING)
		{
			luaL_error(L, "String parameter required");
			return 0;
		}
		const char* str = lua_tostring(L, -1);
		lua_pop(L, 1);
		return runScript(str);
	}

	const luaL_Reg lib[] =
	{
		{"runScript", runScript2},
		{0, 0}
	};

	void luaInit()
	{
		lua_getglobal(Lua, "pgen");
		if (lua_type(Lua, -1) == LUA_TNIL)
		{
			luaL_openlib(Lua, "pgen", lib, 0);
			lua_pop(Lua, 2);
		}
		else
		{
			lua_pop(Lua, 1);
		}
		/*lua_getglobal(Lua, "pgen");
		if (lua_type(Lua, -1) == LUA_TNIL)
		{
			lua_createtable(Lua, 0, 0);
			lua_pushcfunction(Lua, runScript2);
			lua_setfield(L, -1, )
		}
		else
		{
			lua_pop(Lua, 1);
		}*/
		setupGameSaveHandler();
		// fillGameStaticPointersAndSizes();
	}

	bool checkIsInGame()
	{
		lua_pushstring(Lua, "InGame");
		lua_rawget(Lua, LUA_REGISTRYINDEX);
		if (lua_type(Lua, -1) == LUA_TNIL)
		{
			lua_settop(Lua, 0);
			return false;
		}
		else
		{
			bool ret = lua_toboolean(Lua, -1);
			lua_settop(Lua, 0);
			return ret;
		}
	}
}

template<typename Game>
struct GameStructureDataFromLua
{
	const char* luaStructureField;
	
	//int countFieldSize;
};

void fillGameStaticPointersAndSizes()
{
	mm7::GameStructure* game = (mm7::GameStructure*)nullptr;
	lua_getglobal(Lua, "getU");
	lua_getglobal(Lua, "Game");

	// TODOOOOOOOOOOOOOOO

	lua_getfield(Lua, -1, "ItemsTxt");
	lua_getfield(Lua, -1, "?ptr");
	game->itemsTxt = (mm7::ItemsTxtItem*)lua_tointeger(Lua, -1);
	lua_pop(Lua, 2);
	bool fixedSize = false;
	if (fixedSize)
	{
		lua_getfield(Lua, -2, "count");
		uint32_t val = lua_tointeger(Lua, -1);
		game->itemsTxt_sizePtr = (uint32_t*)val;
		lua_pop(Lua, 1);
	}
	else
	{
		lua_getglobal(Lua, "structs");
		lua_getfield(Lua, -1, "m");
		lua_getfield(Lua, -1, "GameStructure");
		lua_pushvalue(Lua, -5); // getU
		lua_getfield(Lua, -2, "ItemsTxt");
		lua_pushstring(Lua, "lenP");
		if (lua_pcall(Lua, 2, 1, 0) != 0) // remember: pops function and arguments from stack before pushing result
		{
			wxLogError("Couldn't get lenP for ItemsTxt array");
			wxLog::FlushActive();
			lua_settop(Lua, 0);
			return;
		}
		game->itemsTxt_sizePtr = (uint32_t*)lua_tointeger(Lua, -1);
		lua_pop(Lua, 4);
	}
}

extern "C" static int saveGameHandler(lua_State* L)
{
	// TODO: autoupdate from save data checkbox?
	bool ret = true;
	if (!saveGameData.saveAllToSaveFile())
	{
		wxLogError("Couldn't load data from save file");
		wxLog::FlushActive();
		ret = false;
	}
	/*else if (!saveGameData.updateAllFromUpdatedData())
	{
        wxLogError("Couldn't update existing windows from new data from save file");
        wxLog::FlushActive();
		ret = false;
	}*/
	lua_pushboolean(L, ret);
	return 1;
}

void setupGameSaveHandler()
{
	lua_getglobal(Lua, "events");
	lua_getglobal(Lua, "pgenedit");
	if (lua_type(Lua, -1) != LUA_TTABLE)
	{
		lua_pop(Lua, 1);
		// create table
		lua_newtable(Lua);
		lua_pushvalue(Lua, -1); // push twice to still have it on stack after setglobal
		lua_setglobal(Lua, "pgenedit");
	}
	lua_pushcfunction(Lua, saveGameHandler);
    lua_pushvalue(Lua, -1);
    lua_setfield(Lua, -3, "saveGameHandler"); // pgenedit
	lua_setfield(Lua, -3, "BeforeSaveGame"); // events; same index, because setfield pops value from stack
	lua_pop(Lua, 2);
}

void luaDeInit()
{
	removeGameSaveHandler();
}

// TODO (fun!): lua wrappers? like tget wrapper which you call like pgenedit_lua_tget(Lua, "pgenedit", "saveGameData"), or lua_call/lua_pcall wrapper to do smth like
// pgenedit_lua_pcall(Lua, []{pgenedit_lua_tget_field(Lua, "pgenedit", "saveGameHandler");}, []{pgenedit_lua_args(Lua, "myglobal.test", 4, 8, false, PGENEDIT_LUA_TNIL)});
// (using lambdas to defer setting stack values to ensure they are pushed in order; also need to somehow take care of functions/userdata/etc.)

void removeGameSaveHandler()
{
    lua_getglobal(Lua, "events"); // 1
	lua_getglobal(Lua, "pgenedit"); // 2
	if (lua_type(Lua, -1) != LUA_TTABLE)
	{
		wxLogError("Lua error: pgenedit global is missing or not a table");
        wxLog::FlushActive();
        lua_pop(Lua, 1);
        lua_newtable(Lua);
        lua_setglobal(Lua, "pgenedit");
	}
    lua_getfield(Lua, -2, "Remove");
    lua_pushstring(Lua, "BeforeSaveGame");
	
	// get handler and clear it
    lua_getfield(Lua, -3, "saveGameHandler");
	lua_pushnil(Lua);
	lua_setfield(Lua, -5, "saveGameHandler");
	if (lua_type(Lua, -1) != LUA_TFUNCTION)
	{
		wxLogError("Lua error: pgenedit.saveGameHandler is missing or not a function");
		wxLog::FlushActive();
	}
    int result = lua_pcall(Lua, 2, 1, 0);
	if (result != 0) // error
	{
		wxLogError("Lua pcall to remove save game handler failed (error code %d, message: '%s')", result, lua_tostring(Lua, -1));
		wxLog::FlushActive();
		lua_pop(Lua, 3); // error msg, pgenedit, events
	}
    int type = lua_type(Lua, -1); // if removed successfully, returns function, otherwise nothing (nil)
    wxASSERT_MSG(type == LUA_TFUNCTION, wxString::Format("Couldn't remove save game handler, received lua type %d", type));
    lua_pop(Lua, 4); // type, result, pgenedit, events
}
/*
// struct "GameClasses", field name "StartingStats", pointer name: "StartingStats"
// struct "GameClasses", field name "HPFactor", size field/pointer name: "HPFactor_size"
// struct "GameClasses", field name "SPBase", size field/pointer name: "SPBase_size"
// struct "GameClasses", field name "startingStats", size field/pointer name: "startingStats_size"
// struct "GameClasses", field name "SPFactor", size field/pointer name: "SPFactor_size"
// struct "GameClasses", field name "SPFactor", pointer name: "SPFactor"
// struct "GameClasses", field name "skills", size field/pointer name: "skills_size"
// struct "GameClasses", field name "Skills", pointer name: "Skills"
// struct "GameClasses", field name "SPBase", pointer name: "SPBase"
// struct "GameClasses", field name "HPBase", size field/pointer name: "HPBase_size"
// struct "GameClasses", field name "HPBase", pointer name: "HPBase"
// struct "GameClasses", field name "SPStats", pointer name: "SPStats"
// struct "GameClasses", field name "SPStats", size field/pointer name: "SPStats_size"
// struct "GameClasses", field name "HPFactor", pointer name: "HPFactor"
// struct "GameClassKinds", field name "StartingSkills", pointer name: "StartingSkills"
// struct "GameClassKinds", field name "startingSkills", size field/pointer name: "startingSkills_size"
// struct "SpritesLod", field name "spritesSW", size field/pointer name: "spritesSW_size"
// struct "SpritesLod", field name "SpritesSW", pointer name: "SpritesSW"
// struct "GameStructure", field name "NPCDataTxt", pointer name: "NPCDataTxt"
// struct "GameStructure", field name "transportLocations", size field/pointer name: "transportLocations_size"
// struct "GameStructure", field name "titleTrackOffset", size field/pointer name: "titleTrackOffset_size"
// struct "GameStructure", field name "hostileTxt", size field/pointer name: "hostileTxt_size"
// struct "GameStructure", field name "NPCGroup", pointer name: "NPCGroup"
// struct "GameStructure", field name "monstersTxt", size field/pointer name: "monstersTxt_size"
// struct "GameStructure", field name "TransTxt", pointer name: "TransTxt"
// struct "GameStructure", field name "MonsterKinds", pointer name: "MonsterKinds"
// struct "GameStructure", field name "shopSpecialItems", size field/pointer name: "shopSpecialItems_size"
// struct "GameStructure", field name "ShopTheftExpireTime", pointer name: "ShopTheftExpireTime"
// struct "GameStructure", field name "transTxt", size field/pointer name: "transTxt_size"
// struct "GameStructure", field name "guildItems", size field/pointer name: "guildItems_size"
// struct "GameStructure", field name "shopItems", size field/pointer name: "shopItems_size"
// struct "GameStructure", field name "questsTxt", size field/pointer name: "questsTxt_size"
// struct "GameStructure", field name "GlobalEvtLines", pointer name: "GlobalEvtLines"
// struct "GameStructure", field name "TransportIndex", pointer name: "TransportIndex"
// struct "GameStructure", field name "Houses", pointer name: "Houses"
// struct "GameStructure", field name "AwardsSort", pointer name: "AwardsSort"
// struct "GameStructure", field name "NPCGroup", size field/pointer name: "NPCGroup_size"
// struct "GameStructure", field name "NPCNews", pointer name: "NPCNews"
// struct "GameStructure", field name "autonoteCategory", size field/pointer name: "autonoteCategory_size"
// struct "GameStructure", field name "globalEvtLines", size field/pointer name: "globalEvtLines_size"
// struct "GameStructure", field name "ShopItems", pointer name: "ShopItems"
// struct "GameStructure", field name "QuestsTxt", pointer name: "QuestsTxt"
// struct "GameStructure", field name "ShopSpecialItems", pointer name: "ShopSpecialItems"
// struct "GameStructure", field name "AutonoteCategory", pointer name: "AutonoteCategory"
// struct "GameStructure", field name "TitleTrackOffset", pointer name: "TitleTrackOffset"
// struct "GameStructure", field name "ClassNames", pointer name: "ClassNames"
// struct "GameStructure", field name "HousesExtra", pointer name: "HousesExtra"
// struct "GameStructure", field name "HouseMovies", pointer name: "HouseMovies"
// struct "GameStructure", field name "GuildNextRefill2", pointer name: "GuildNextRefill2"
// struct "GameStructure", field name "ShopNextRefill", pointer name: "ShopNextRefill"
// struct "GameStructure", field name "monsterKinds", size field/pointer name: "monsterKinds_size"
// struct "GameStructure", field name "CharacterPortraits", pointer name: "CharacterPortraits"
// struct "GameStructure", field name "transportIndex", size field/pointer name: "transportIndex_size"
// struct "GameStructure", field name "mapDoorSound", size field/pointer name: "mapDoorSound_size"
// struct "GameStructure", field name "NPCDataTxt", size field/pointer name: "NPCDataTxt_size"
// struct "GameStructure", field name "TransportLocations", pointer name: "TransportLocations"
// struct "GameStructure", field name "NPCText", pointer name: "NPCText"
// struct "GameStructure", field name "MonstersTxt", pointer name: "MonstersTxt"
// struct "GameStructure", field name "placeMonTxt", size field/pointer name: "placeMonTxt_size"
// struct "GameStructure", field name "PatchOptions", pointer name: "PatchOptions"
// struct "GameStructure", field name "itemsTxt", size field/pointer name: "itemsTxt_size"
// struct "GameStructure", field name "shopTheftExpireTime", size field/pointer name: "shopTheftExpireTime_size"
// struct "GameStructure", field name "ItemsTxt", pointer name: "ItemsTxt"
// struct "GameStructure", field name "autonoteTxt", size field/pointer name: "autonoteTxt_size"
// struct "GameStructure", field name "NPCTopic", size field/pointer name: "NPCTopic_size"
// struct "GameStructure", field name "NPC", pointer name: "NPC"
// struct "GameStructure", field name "MapDoorSound", pointer name: "MapDoorSound"
// struct "GameStructure", field name "mixPotions", size field/pointer name: "mixPotions_size"
// struct "GameStructure", field name "houses", size field/pointer name: "houses_size"
// struct "GameStructure", field name "characterDollTypes", size field/pointer name: "characterDollTypes_size"
// struct "GameStructure", field name "characterPortraits", size field/pointer name: "characterPortraits_size"
// struct "GameStructure", field name "MixPotions", pointer name: "MixPotions"
// struct "GameStructure", field name "ReagentSettings", pointer name: "ReagentSettings"
// struct "GameStructure", field name "NPCGreet", size field/pointer name: "NPCGreet_size"
// struct "GameStructure", field name "NPCText", size field/pointer name: "NPCText_size"
// struct "GameStructure", field name "mapFogChances", size field/pointer name: "mapFogChances_size"
// struct "GameStructure", field name "MissileSetup", pointer name: "MissileSetup"
// struct "GameStructure", field name "MapFogChances", pointer name: "MapFogChances"
// struct "GameStructure", field name "mapStats", size field/pointer name: "mapStats_size"
// struct "GameStructure", field name "NPC", size field/pointer name: "NPC_size"
// struct "GameStructure", field name "missileSetup", size field/pointer name: "missileSetup_size"
// struct "GameStructure", field name "NPCTopic", pointer name: "NPCTopic"
// struct "GameStructure", field name "NPCGreet", pointer name: "NPCGreet"
// struct "GameStructure", field name "AutonoteTxt", pointer name: "AutonoteTxt"
// struct "GameStructure", field name "MapStats", pointer name: "MapStats"
// struct "GameStructure", field name "CharacterDollTypes", pointer name: "CharacterDollTypes"
// struct "GameStructure", field name "housesExtra", size field/pointer name: "housesExtra_size"
// struct "GameStructure", field name "CustomLods", pointer name: "CustomLods"
// struct "GameStructure", field name "PlaceMonTxt", pointer name: "PlaceMonTxt"
// struct "GameStructure", field name "NPCNews", size field/pointer name: "NPCNews_size"
// struct "GameStructure", field name "guildNextRefill2", size field/pointer name: "guildNextRefill2_size"
// struct "GameStructure", field name "reagentSettings", size field/pointer name: "reagentSettings_size"
// struct "GameStructure", field name "houseMovies", size field/pointer name: "houseMovies_size"
// struct "GameStructure", field name "GuildItems", pointer name: "GuildItems"
// struct "GameStructure", field name "awardsSort", size field/pointer name: "awardsSort_size"
// struct "GameStructure", field name "HostileTxt", pointer name: "HostileTxt"
// struct "GameStructure", field name "classNames", size field/pointer name: "classNames_size"
// struct "GameStructure", field name "shopNextRefill", size field/pointer name: "shopNextRefill_size"
// struct "DialogLogic", field name "List", pointer name: "List"
// struct "DialogLogic", field name "list", size field/pointer name: "list_size"
*/