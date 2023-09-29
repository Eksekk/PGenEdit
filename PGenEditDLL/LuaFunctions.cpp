#include "pch.h"
#include "LuaFunctions.h"
#include "Structs.h"
#include "SaveGameData.h"
#include "LuaWrapper.h"

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
			lua_pop(Lua, 1);
			return false;
		}
		else
		{
			bool ret = lua_toboolean(Lua, -1);
			lua_pop(Lua, 1);
			return ret;
		}
	}
}

// can be no array but single dataPtr (patchOptions, frameCounter etc.)
struct StructArray
{
	std::string arrayPath; // from global environment
	void*& ptr; // reference to ptr to data
	std::variant<std::monostate, std::reference_wrapper<uint32_t*>, std::reference_wrapper<uint32_t>> size; // reference to either unchangeable size or ptr to size
};

template<AnyGameStruct GameStructure>
std::vector<StructArray> arraysBase =
{
	{ "Game.ItemsTxt", (void*&)(GameStructure::itemsTxt), std::ref((uint32_t*&)(GameStructure::itemsTxt_sizePtr)) },
	{ "Game.StdItemsTxt", (void*&)(GameStructure::stdItemsTxt), std::ref((uint32_t*&)(GameStructure::stdItemsTxt_size)) },
	{ "Game.SpcItemsTxt", (void*&)(GameStructure::spcItemsTxt), std::ref((uint32_t*&)(GameStructure::spcItemsTxt_size)) },
	{ "Game.SpcItemsTxt", (void*&)(GameStructure::spcItemsTxt), std::ref((uint32_t*&)(GameStructure::spcItemsTxt_size)) },
	{ "Game.SpcItemsTxt", (void*&)(GameStructure::spcItemsTxt), std::ref((uint32_t*&)(GameStructure::spcItemsTxt_size)) },
	{ "Game.SpcItemsTxt", (void*&)(GameStructure::spcItemsTxt), std::ref((uint32_t*&)(GameStructure::spcItemsTxt_size)) },
};

/*
 // ArmorPicsCoords::Belts, dataPtr name: "Belts"
// ArmorPicsCoords::cloaks, size field/dataPtr name: "cloaks_size"
// ArmorPicsCoords::Cloaks, dataPtr name: "Cloaks"
// ArmorPicsCoords::boots, size field/dataPtr name: "boots_size"
// ArmorPicsCoords::belts, size field/dataPtr name: "belts_size"
// ArmorPicsCoords::helms, size field/dataPtr name: "helms_size"
// ArmorPicsCoords::Helms, dataPtr name: "Helms"
// ArmorPicsCoords::Boots, dataPtr name: "Boots"
// ArmorPicsCoords::Armors, dataPtr name: "Armors"
// ArmorPicsCoords::armors, size field/dataPtr name: "armors_size"
// CharacterVoices::Sounds, dataPtr name: "Sounds"
// CharacterVoices::avail, size field/dataPtr name: "avail_size"
// CharacterVoices::Avail, dataPtr name: "Avail"
// CharacterVoices::sounds, size field/dataPtr name: "sounds_size"
 **/
using Game8 = mm8::GameStructure;
std::vector<StructArray> arraysMerge =
{
	{"Game.ArmorPicsCoords.Belts", (void*&)Game8::armorPicsCoords->belts, std::monostate()},
};

void fillGameStaticPointersAndSizes()
{
	mm7::GameStructure* game = (mm7::GameStructure*)nullptr;
	lua_getglobal(Lua, "internal");
	lua_getfield(Lua, -1, "GetArrayUpval");
	lua_replace(Lua, -2);
	lua_pop(Lua, 1);

	int stackPos = lua_gettop(Lua);
	for (auto& [path, dataPtr, sizeVariant] : arraysBase<mm7::Game>)
	{
		luaWrapper.getPath(path);
		lua_getfield(Lua, -1, "?sizePtr");
		dataPtr = reinterpret_cast<void*>((uint32_t)lua_tonumber(Lua, -1));
		lua_pop(Lua, 1);
		if (std::reference_wrapper<uint32_t*>* sizePtr = std::get_if<std::reference_wrapper<uint32_t*>>(&sizeVariant))
		{
			lua_pushvalue(Lua, -1); // array
			lua_pushstring(Lua, "lenP");
			int error = lua_pcall(Lua, 2, 1, 0);
			if (error)
			{
				wxLogFatalError("Error while trying to get lenP of '%s' array: %s", path, lua_tostring(Lua, -1));
				lua_settop(Lua, stackPos);
				return;
			}
			sizePtr->get() = reinterpret_cast<uint32_t*>((uint32_t)lua_tonumber(Lua, -1));
			if (dataPtr) // add offset
			{
				wxLogInfo("Adding nonzero data offset (0x%X) to lenP of array '%s'", (uint32_t)dataPtr, path);
				wxLog::FlushActive();
				sizePtr->get() += (uint32_t)dataPtr;
			}
		}
		else if (std::reference_wrapper<uint32_t>* size = std::get_if<std::reference_wrapper<uint32_t>>(&sizeVariant))
		{
			lua_pushvalue(Lua, -1);
			lua_pushstring(Lua, "count");
            int error = lua_pcall(Lua, 2, 1, 0);
            if (error)
            {
                wxLogFatalError("Error while trying to get count of '%s' array: %s", path, lua_tostring(Lua, -1));
                lua_settop(Lua, stackPos);
                return;
            }
		}
	}
	lua_settop(Lua, stackPos);
}

extern "C" static int saveGameHandler(lua_State* L)
{
	// TODO: autoupdate from save data checkbox?
	bool ret = true;
	if (!saveGameData.saveAllToSaveFile())
	{
		wxLogError("Couldn't save data to save file");
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
		return;
	}
    int type = lua_type(Lua, -1); // if removed successfully, returns function, otherwise nothing (nil)
    wxASSERT_MSG(type == LUA_TFUNCTION, wxString::Format("Couldn't remove save game handler, received lua type %d", type));
    lua_pop(Lua, 4); // type, result, pgenedit, events
}
/*
// struct "GameClasses", field name "StartingStats", dataPtr name: "StartingStats"
// struct "GameClasses", field name "HPFactor", size field/dataPtr name: "HPFactor_size"
// struct "GameClasses", field name "SPBase", size field/dataPtr name: "SPBase_size"
// struct "GameClasses", field name "startingStats", size field/dataPtr name: "startingStats_size"
// struct "GameClasses", field name "SPFactor", size field/dataPtr name: "SPFactor_size"
// struct "GameClasses", field name "SPFactor", dataPtr name: "SPFactor"
// struct "GameClasses", field name "skills", size field/dataPtr name: "skills_size"
// struct "GameClasses", field name "Skills", dataPtr name: "Skills"
// struct "GameClasses", field name "SPBase", dataPtr name: "SPBase"
// struct "GameClasses", field name "HPBase", size field/dataPtr name: "HPBase_size"
// struct "GameClasses", field name "HPBase", dataPtr name: "HPBase"
// struct "GameClasses", field name "SPStats", dataPtr name: "SPStats"
// struct "GameClasses", field name "SPStats", size field/dataPtr name: "SPStats_size"
// struct "GameClasses", field name "HPFactor", dataPtr name: "HPFactor"
// struct "GameClassKinds", field name "StartingSkills", dataPtr name: "StartingSkills"
// struct "GameClassKinds", field name "startingSkills", size field/dataPtr name: "startingSkills_size"
// struct "SpritesLod", field name "spritesSW", size field/dataPtr name: "spritesSW_size"
// struct "SpritesLod", field name "SpritesSW", dataPtr name: "SpritesSW"
// struct "GameStructure", field name "NPCDataTxt", dataPtr name: "NPCDataTxt"
// struct "GameStructure", field name "transportLocations", size field/dataPtr name: "transportLocations_size"
// struct "GameStructure", field name "titleTrackOffset", size field/dataPtr name: "titleTrackOffset_size"
// struct "GameStructure", field name "hostileTxt", size field/dataPtr name: "hostileTxt_size"
// struct "GameStructure", field name "NPCGroup", dataPtr name: "NPCGroup"
// struct "GameStructure", field name "monstersTxt", size field/dataPtr name: "monstersTxt_size"
// struct "GameStructure", field name "TransTxt", dataPtr name: "TransTxt"
// struct "GameStructure", field name "MonsterKinds", dataPtr name: "MonsterKinds"
// struct "GameStructure", field name "shopSpecialItems", size field/dataPtr name: "shopSpecialItems_size"
// struct "GameStructure", field name "ShopTheftExpireTime", dataPtr name: "ShopTheftExpireTime"
// struct "GameStructure", field name "transTxt", size field/dataPtr name: "transTxt_size"
// struct "GameStructure", field name "guildItems", size field/dataPtr name: "guildItems_size"
// struct "GameStructure", field name "shopItems", size field/dataPtr name: "shopItems_size"
// struct "GameStructure", field name "questsTxt", size field/dataPtr name: "questsTxt_size"
// struct "GameStructure", field name "GlobalEvtLines", dataPtr name: "GlobalEvtLines"
// struct "GameStructure", field name "TransportIndex", dataPtr name: "TransportIndex"
// struct "GameStructure", field name "Houses", dataPtr name: "Houses"
// struct "GameStructure", field name "AwardsSort", dataPtr name: "AwardsSort"
// struct "GameStructure", field name "NPCGroup", size field/dataPtr name: "NPCGroup_size"
// struct "GameStructure", field name "NPCNews", dataPtr name: "NPCNews"
// struct "GameStructure", field name "autonoteCategory", size field/dataPtr name: "autonoteCategory_size"
// struct "GameStructure", field name "globalEvtLines", size field/dataPtr name: "globalEvtLines_size"
// struct "GameStructure", field name "ShopItems", dataPtr name: "ShopItems"
// struct "GameStructure", field name "QuestsTxt", dataPtr name: "QuestsTxt"
// struct "GameStructure", field name "ShopSpecialItems", dataPtr name: "ShopSpecialItems"
// struct "GameStructure", field name "AutonoteCategory", dataPtr name: "AutonoteCategory"
// struct "GameStructure", field name "TitleTrackOffset", dataPtr name: "TitleTrackOffset"
// struct "GameStructure", field name "ClassNames", dataPtr name: "ClassNames"
// struct "GameStructure", field name "HousesExtra", dataPtr name: "HousesExtra"
// struct "GameStructure", field name "HouseMovies", dataPtr name: "HouseMovies"
// struct "GameStructure", field name "GuildNextRefill2", dataPtr name: "GuildNextRefill2"
// struct "GameStructure", field name "ShopNextRefill", dataPtr name: "ShopNextRefill"
// struct "GameStructure", field name "monsterKinds", size field/dataPtr name: "monsterKinds_size"
// struct "GameStructure", field name "CharacterPortraits", dataPtr name: "CharacterPortraits"
// struct "GameStructure", field name "transportIndex", size field/dataPtr name: "transportIndex_size"
// struct "GameStructure", field name "mapDoorSound", size field/dataPtr name: "mapDoorSound_size"
// struct "GameStructure", field name "NPCDataTxt", size field/dataPtr name: "NPCDataTxt_size"
// struct "GameStructure", field name "TransportLocations", dataPtr name: "TransportLocations"
// struct "GameStructure", field name "NPCText", dataPtr name: "NPCText"
// struct "GameStructure", field name "MonstersTxt", dataPtr name: "MonstersTxt"
// struct "GameStructure", field name "placeMonTxt", size field/dataPtr name: "placeMonTxt_size"
// struct "GameStructure", field name "PatchOptions", dataPtr name: "PatchOptions"
// struct "GameStructure", field name "itemsTxt", size field/dataPtr name: "itemsTxt_size"
// struct "GameStructure", field name "shopTheftExpireTime", size field/dataPtr name: "shopTheftExpireTime_size"
// struct "GameStructure", field name "ItemsTxt", dataPtr name: "ItemsTxt"
// struct "GameStructure", field name "autonoteTxt", size field/dataPtr name: "autonoteTxt_size"
// struct "GameStructure", field name "NPCTopic", size field/dataPtr name: "NPCTopic_size"
// struct "GameStructure", field name "NPC", dataPtr name: "NPC"
// struct "GameStructure", field name "MapDoorSound", dataPtr name: "MapDoorSound"
// struct "GameStructure", field name "mixPotions", size field/dataPtr name: "mixPotions_size"
// struct "GameStructure", field name "houses", size field/dataPtr name: "houses_size"
// struct "GameStructure", field name "characterDollTypes", size field/dataPtr name: "characterDollTypes_size"
// struct "GameStructure", field name "characterPortraits", size field/dataPtr name: "characterPortraits_size"
// struct "GameStructure", field name "MixPotions", dataPtr name: "MixPotions"
// struct "GameStructure", field name "ReagentSettings", dataPtr name: "ReagentSettings"
// struct "GameStructure", field name "NPCGreet", size field/dataPtr name: "NPCGreet_size"
// struct "GameStructure", field name "NPCText", size field/dataPtr name: "NPCText_size"
// struct "GameStructure", field name "mapFogChances", size field/dataPtr name: "mapFogChances_size"
// struct "GameStructure", field name "MissileSetup", dataPtr name: "MissileSetup"
// struct "GameStructure", field name "MapFogChances", dataPtr name: "MapFogChances"
// struct "GameStructure", field name "mapStats", size field/dataPtr name: "mapStats_size"
// struct "GameStructure", field name "NPC", size field/dataPtr name: "NPC_size"
// struct "GameStructure", field name "missileSetup", size field/dataPtr name: "missileSetup_size"
// struct "GameStructure", field name "NPCTopic", dataPtr name: "NPCTopic"
// struct "GameStructure", field name "NPCGreet", dataPtr name: "NPCGreet"
// struct "GameStructure", field name "AutonoteTxt", dataPtr name: "AutonoteTxt"
// struct "GameStructure", field name "MapStats", dataPtr name: "MapStats"
// struct "GameStructure", field name "CharacterDollTypes", dataPtr name: "CharacterDollTypes"
// struct "GameStructure", field name "housesExtra", size field/dataPtr name: "housesExtra_size"
// struct "GameStructure", field name "CustomLods", dataPtr name: "CustomLods"
// struct "GameStructure", field name "PlaceMonTxt", dataPtr name: "PlaceMonTxt"
// struct "GameStructure", field name "NPCNews", size field/dataPtr name: "NPCNews_size"
// struct "GameStructure", field name "guildNextRefill2", size field/dataPtr name: "guildNextRefill2_size"
// struct "GameStructure", field name "reagentSettings", size field/dataPtr name: "reagentSettings_size"
// struct "GameStructure", field name "houseMovies", size field/dataPtr name: "houseMovies_size"
// struct "GameStructure", field name "GuildItems", dataPtr name: "GuildItems"
// struct "GameStructure", field name "awardsSort", size field/dataPtr name: "awardsSort_size"
// struct "GameStructure", field name "HostileTxt", dataPtr name: "HostileTxt"
// struct "GameStructure", field name "classNames", size field/dataPtr name: "classNames_size"
// struct "GameStructure", field name "shopNextRefill", size field/dataPtr name: "shopNextRefill_size"
// struct "DialogLogic", field name "List", dataPtr name: "List"
// struct "DialogLogic", field name "list", size field/dataPtr name: "list_size"
*/