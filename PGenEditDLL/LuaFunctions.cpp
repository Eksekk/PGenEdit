#include "pch.h"
#include "LuaFunctions.h"
#include "Structs.h"
#include "SaveGameData.h"
#include "LuaWrapper.h"
#include "Utility.h"
#include "CallEvents.h"
#include "Reflection.h"

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

	const luaL_Reg pgeneditDebugApiReg[] =
	{
		{"getClassField", luaDebug::getClassField},
		{"getClassObjectField", luaDebug::getClassObjectField},
		{"getGlobalField", luaDebug::getGlobalField},
		{"setClassField", luaDebug::setClassField},
		{"setClassObjectField", luaDebug::setClassObjectField},
		{"setGlobalField", luaDebug::setGlobalField},
		{"invokeClassMethod", luaDebug::invokeClassMethod},
		{"invokeClassObjectMethod", luaDebug::invokeClassObjectMethod},
		{"invokeGlobalMethod", luaDebug::invokeGlobalMethod},
		{"classExists", luaDebug::classExists},
		{"copyObject", luaDebug::copyObject},
		{"createObject", luaDebug::createObject},
		{"destroyObject", luaDebug::destroyObject},
		{"getClassInfo", luaDebug::getClassInfo},
		{"getGlobalEnvironmentInfo", luaDebug::getGlobalEnvironmentInfo},
		{0, 0}
	};

	static int eventTestHandler(lua_State* L)
	{
		int i = lua_tonumber(L, -2);
		bool b = lua_toboolean(L, -1);
		wxLogInfo("Event handler: received int %d and bool %d, returning %d", i, b, i * 3);
		lua_pushnumber(L, i * 3);
		return 1;
	}

	void luaInit()
	{
		lua_getglobal(Lua, "pgenedit");
		if (lua_type(Lua, -1) == LUA_TNIL)
		{
			luaL_openlib(Lua, "pgenedit", lib, 0);
			lua_replace(Lua, -2);
        }
		lua_getfield(Lua, -1, "events");
		if (lua_type(Lua, -1) != LUA_TTABLE)
		{
			lua_pop(Lua, 1);
			luaWrapper.getPath("events.new");
			lua_call(Lua, 0, 1);
			lua_setfield(Lua, -2, "events");
		}
		else
		{
			lua_pop(Lua, 1);
		}
		lua_pushcfunction(Lua, eventTestHandler);
		luaWrapper.setPath("pgenedit.events.testEvent", -1);

// 		auto f = getEventActivator<int, bool>("testEvent", std::tuple<int>());
// 		auto [i1] = std::get<1>(f(5, true));
//         wxLogInfo("Event caller: received %d", i1);
// 		wxLog::FlushActive();
//         std::tie(i1) = std::get<1>(f(2, false));
//         wxLogInfo("Event caller: received %d", i1);
//         wxLog::FlushActive();
//         std::tie(i1) = std::get<1>(f(88, false));
//         wxLogInfo("Event caller: received %d", i1);
//         wxLog::FlushActive();
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
		detectIfIsMerge();
		setupGameSaveHandler();
		fillGameStaticPointersAndSizes();
		luaL_openlib(Lua, "pgeneditDebugApi", pgeneditDebugApiReg, 0);
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

std::string buildWantedLuaTypeString(std::initializer_list<int> list)
{
    static const std::string singleFormat = "%s", multipleFormat = "any of [%s]";
    std::string s;
	std::vector<std::string> parts;
	std::ranges::transform(list, std::back_inserter(parts), [](int arg) { return luaTypeToString(Lua, arg); });
	return wxString::Format(wxString(list.size() <= 1 ? singleFormat : multipleFormat), (wxString)stringConcat(parts)).ToStdString();
}

bool detectIfIsMerge()
{
	if (MMVER != 8)
	{
		IS_MERGE = false;
		return false;
	}
	lua_getglobal(Lua, "Merge");
	bool r = false;
	if (lua_type(Lua, -1) != LUA_TNIL)
	{
		r = true;
	}
	else
	{
		r = false;
	}
	lua_pop(Lua, 1);
	IS_MERGE = r;
	return r;
}

// can be no array but single dataPtr (patchOptions, frameCounter etc.)
struct StructArray
{
	std::string arrayPath; // from global environment
	void*& ptr; // reference to ptr to data
	std::variant<std::monostate, std::reference_wrapper<uint32_t*>, std::reference_wrapper<uint32_t>> size; // reference to either dummy value, unchangeable size, or ptr to size
	bool customType = false; // if set, path is of form "structs.o.GameStructure.TitleTrackOffset", because custom types don't have useful upvalues
};

using StructVector = std::vector<StructArray>;

template<typename T>
void*& dataRef(T& t)
{
	return (void*&)t;
}

template<typename T>
auto sizeRef(T& t)
{
	if constexpr (std::is_pointer_v<T>)
    {
		return std::ref((uint32_t*&)t);
	}
	else
	{
		return std::ref((uint32_t&)t);
	}
}

template<AnyGameStruct Game>
const StructVector arraysBase =
{
	{ "Game.ItemsTxt", dataRef(Game::itemsTxt), sizeRef(Game::itemsTxt_sizePtr)},
	{ "Game.StdItemsTxt", dataRef(Game::stdItemsTxt), sizeRef(Game::stdItemsTxt_size) },
	{ "Game.SpcItemsTxt", dataRef(Game::spcItemsTxt), sizeRef(Game::spcItemsTxt_size) },
	{ "Game.AwardsTxt", dataRef(Game::awardsTxt), sizeRef(Game::awardsTxt_size) },
	{ "Game.MonstersTxt", dataRef(Game::monstersTxt), sizeRef(Game::monstersTxt_sizePtr) },
	{ "Game.TransTxt", dataRef(Game::transTxt), sizeRef(Game::transTxt_size) },
	{ "Game.Houses", dataRef(Game::houses), sizeRef(Game::houses_size) },
    { "Game.QuestsTxt", dataRef(Game::questsTxt), sizeRef(Game::questsTxt_size) },
    { "Game.AutonoteTxt", dataRef(Game::autonoteTxt), sizeRef(Game::autonoteTxt_size) },
    { "Game.MapStats", dataRef(Game::mapStats), sizeRef(Game::mapStats_sizePtr) },

    { "Game.NPCNews", dataRef(Game::NPCNews), sizeRef(Game::NPCNews_size) },
    { "Game.NPCDataTxt", dataRef(Game::NPCDataTxt), sizeRef(Game::NPCDataTxt_size) },
    { "Game.NPCTopic", dataRef(Game::NPCTopic), sizeRef(Game::NPCTopic_size) },
    { "Game.NPCText", dataRef(Game::NPCText), sizeRef(Game::NPCText_size) },

	{ "Game.ClassNames", dataRef(Game::classNames), sizeRef(Game::classNames_size) },
	{ "Game.HouseMovies", dataRef(Game::houseMovies), sizeRef(Game::houseMovies_size) },
	{ "Game.ShopNextRefill", dataRef(Game::shopNextRefill), sizeRef(Game::shopNextRefill_size) },
	{ "Game.PatchOptions", dataRef(Game::patchOptions), std::monostate()},
    { "Game.MissileSetup", dataRef(Game::missileSetup), sizeRef(Game::missileSetup_sizePtr) },
    { "Game.MapFogChances", dataRef(Game::mapFogChances), sizeRef(Game::mapFogChances_size) },

	{ "Game.TransportLocations", dataRef(Game::transportLocations), sizeRef(Game::transportLocations_size) },
	{ "Game.TransportIndex", dataRef(Game::transportIndex), sizeRef(Game::transportIndex_size) },
	{ "Game.ShopItems", dataRef(Game::shopItems), sizeRef(Game::shopItems_size) },
	{ "Game.ShopSpecialItems", dataRef(Game::shopSpecialItems), sizeRef(Game::shopSpecialItems_size) },
	{ "Game.GuildItems", dataRef(Game::guildItems), sizeRef(Game::guildItems_size) },
	{ "Game.GlobalEvtLines", dataRef(Game::globalEvtLines), sizeRef(Game::globalEvtLines_sizePtr) },
	{ "structs.o.GameStructure.TitleTrackOffset", dataRef(Game::titleTrackOffset), std::monostate(), true},
	{ "Game.MapDoorSound", dataRef(Game::mapDoorSound), sizeRef(Game::mapDoorSound_size) },

	{ "Game.Classes.HPFactor", dataRef(Game::classes->HPFactor), sizeRef(Game::classes->HPFactor_size) },
	{ "Game.Classes.SPFactor", dataRef(Game::classes->SPFactor), sizeRef(Game::classes->SPFactor_size) },
	{ "Game.Classes.SPStats", dataRef(Game::classes->SPStats), sizeRef(Game::classes->SPStats_size) },

	{ "Game.SpritesLod.SpritesSW", dataRef(((Game*)nullptr)->spritesLod.spritesSW), sizeRef(((Game*)nullptr)->spritesLod.spritesSW_sizePtr)},

	{ "Game.CustomLods", dataRef(Game::customLods), std::monostate()},


	{ "Party.QBits", dataRef(decay_fully<decltype(Game::party)>::QBits), sizeRef(decay_fully<decltype(Game::party)>::QBits_size) },

	{ "Game.DialogLogic.List", dataRef(decay_fully<decltype(Game::dialogLogic)>::list), sizeRef(decay_fully<decltype(Game::dialogLogic)>::list_sizePtr) },
};

using Game6 = mm6::GameStructure;
using Game7 = mm7::GameStructure;
using Game8 = mm8::GameStructure;

const StructVector arraysMm6 =
{
    { "Game.AwardsSort", dataRef(Game6::awardsSort), sizeRef(Game6::awardsSort_sizePtr) },
    { "Game.NPC", dataRef(Game6::NPC), sizeRef(Game6::NPC_sizePtr) },
};

const StructVector arraysMm7 =
{
    { "Game.Classes.Skills", dataRef(Game7::classes->skills), sizeRef(Game7::classes->skills_size) },

    { "Game.ShopTheftExpireTime", dataRef(Game7::shopTheftExpireTime), sizeRef(Game7::shopTheftExpireTime_size) },
    { "Game.HostileTxt", dataRef(Game7::hostileTxt), sizeRef(Game7::hostileTxt_size) },
    { "Game.AwardsSort", dataRef(Game7::awardsSort), sizeRef(Game7::awardsSort_size) },
    { "Game.MonsterKinds", dataRef(Game7::monsterKinds), sizeRef(Game7::monsterKinds_sizePtr) },
    { "Game.AutonoteCategory", dataRef(Game7::autonoteCategory), sizeRef(Game7::autonoteCategory_size) },
    { "Game.PlaceMonTxt", dataRef(Game7::placeMonTxt), sizeRef(Game7::placeMonTxt_sizePtr) },

    { "Game.NPC", dataRef(Game7::NPC), sizeRef(Game7::NPC_sizePtr) },
    { "Game.NPCGreet", dataRef(Game7::NPCGreet), sizeRef(Game7::NPCGreet_size) },
    { "Game.NPCGroup", dataRef(Game7::NPCGroup), sizeRef(Game7::NPCGroup_size) },
};

const StructVector arraysMm8 =
{
    { "Game.Classes.HPBase", dataRef(Game8::classes->HPBase), sizeRef(Game8::classes->HPBase_size) },
    { "Game.Classes.SPBase", dataRef(Game8::classes->SPBase), sizeRef(Game8::classes->SPBase_size) },
    { "Game.Classes.StartingSkills", dataRef(Game8::classes->SPBase), sizeRef(Game8::classes->SPBase_size) },
    { "Game.Classes.Skills", dataRef(Game8::classes->skills), sizeRef(Game8::classes->skills_size) },

    { "Game.ShopTheftExpireTime", dataRef(Game8::shopTheftExpireTime), sizeRef(Game8::shopTheftExpireTime_size) },
    { "Game.HostileTxt", dataRef(Game8::hostileTxt), sizeRef(Game8::hostileTxt_size) },
    { "Game.AwardsSort", dataRef(Game8::awardsSort), sizeRef(Game8::awardsSort_size) },
    { "Game.MonsterKinds", dataRef(Game8::monsterKinds), sizeRef(Game8::monsterKinds_sizePtr) },
    { "Game.AutonoteCategory", dataRef(Game8::autonoteCategory), sizeRef(Game8::autonoteCategory_size) },
    { "Game.PlaceMonTxt", dataRef(Game8::placeMonTxt), sizeRef(Game8::placeMonTxt_sizePtr) },

    { "Game.NPC", dataRef(Game8::NPC), sizeRef(Game8::NPC_size) },
    { "Game.NPCGreet", dataRef(Game8::NPCGreet), sizeRef(Game8::NPCGreet_size) },
    { "Game.NPCGroup", dataRef(Game8::NPCGroup), sizeRef(Game8::NPCGroup_size) },
};

const StructVector arraysMerge =
{
	{"Game.ArmorPicsCoords.Belts", dataRef(Game8::armorPicsCoords->belts), sizeRef(Game8::armorPicsCoords->belts_size)},
	{"Game.ArmorPicsCoords.Cloaks", dataRef(Game8::armorPicsCoords->cloaks), sizeRef(Game8::armorPicsCoords->cloaks_size)},
	{"Game.ArmorPicsCoords.Boots", dataRef(Game8::armorPicsCoords->boots), sizeRef(Game8::armorPicsCoords->boots_size)},
	{"Game.ArmorPicsCoords.Helms", dataRef(Game8::armorPicsCoords->helms), sizeRef(Game8::armorPicsCoords->helms_size)},
	{"Game.ArmorPicsCoords.Armors", dataRef(Game8::armorPicsCoords->armors), sizeRef(Game8::armorPicsCoords->armors_size)},

	{"Game.CharacterVoices.Sounds", dataRef(Game8::characterVoices->sounds), sizeRef(Game8::characterVoices->sounds_size)},
	{"Game.CharacterVoices.Avail", dataRef(Game8::characterVoices->avail), sizeRef(Game8::characterVoices->avail_size)},

	{"Game.HouseRules.WeaponShopsStandart", dataRef(Game8::houseRules->weaponShopsStandart), sizeRef(Game8::houseRules->weaponShopsStandart_size)},
    {"Game.HouseRules.WeaponShopsSpecial", dataRef(Game8::houseRules->weaponShopsSpecial), sizeRef(Game8::houseRules->weaponShopsSpecial_size)},
    {"Game.HouseRules.ArmorShopsStandart", dataRef(Game8::houseRules->armorShopsStandart), sizeRef(Game8::houseRules->armorShopsStandart_size)},
    {"Game.HouseRules.ArmorShopsSpecial", dataRef(Game8::houseRules->armorShopsSpecial), sizeRef(Game8::houseRules->armorShopsSpecial_size)},
    {"Game.HouseRules.MagicShopsStandart", dataRef(Game8::houseRules->magicShopsStandart), sizeRef(Game8::houseRules->magicShopsStandart_size)},
    {"Game.HouseRules.MagicShopsSpecial", dataRef(Game8::houseRules->magicShopsSpecial), sizeRef(Game8::houseRules->magicShopsSpecial_size)},
    {"Game.HouseRules.AlchemistsStandart", dataRef(Game8::houseRules->alchemistsStandart), sizeRef(Game8::houseRules->alchemistsStandart_size)},
    {"Game.HouseRules.AlchemistsSpecial", dataRef(Game8::houseRules->alchemistsSpecial), sizeRef(Game8::houseRules->alchemistsSpecial_size)},
    {"Game.HouseRules.Arcomage", dataRef(Game8::houseRules->arcomage), sizeRef(Game8::houseRules->arcomage_size)},
    {"Game.HouseRules.ArcomageTexts", dataRef(Game8::houseRules->arcomageTexts), sizeRef(Game8::houseRules->arcomageTexts_size)},
    {"Game.HouseRules.SpellbookShops", dataRef(Game8::houseRules->spellbookShops), sizeRef(Game8::houseRules->spellbookShops_size)},
    {"Game.HouseRules.Training", dataRef(Game8::houseRules->training), sizeRef(Game8::houseRules->training_size)},

    { "Game.HousesExtra", dataRef(Game8::housesExtra), sizeRef(Game8::housesExtra_size) },
    { "Game.GuildNextRefill2", dataRef(Game8::guildNextRefill2), sizeRef(Game8::guildNextRefill2_size) },
    { "Game.CharacterPortraits", dataRef(Game8::characterPortraits), sizeRef(Game8::characterPortraits_size) },
    { "Game.CharacterDollTypes", dataRef(Game8::characterDollTypes), sizeRef(Game8::characterDollTypes_size) },

    { "Game.MixPotions", dataRef(Game8::mixPotions), sizeRef(Game8::mixPotions_size) },
    { "Game.ReagentSettings", dataRef(Game8::reagentSettings), sizeRef(Game8::reagentSettings_size) },
};

void fillGameStaticPointersAndSizes()
{
	int origStack = lua_gettop(Lua);
	luaWrapper.getPath("internal.GetArrayUpval");
	StructVector singleGameSpecific = mmv(arraysMm6, arraysMm7, arraysMm8);
	std::ranges::copy(mmv(arraysBase<mm6::Game>, arraysBase<mm7::Game>, arraysBase<mm8::Game>), std::back_inserter(singleGameSpecific));
	if (IS_MERGE)
	{
		std::ranges::copy(arraysMerge, std::back_inserter(singleGameSpecific));
	}

	for (auto& [path, dataPtr, sizeVariant, customType] : singleGameSpecific)
    {
        int stackPos = lua_gettop(Lua);
		luaWrapper.getPath(path);
		if (!customType) // otherwise path directly refers to offset
		{
            lua_getfield(Lua, -1, "pptr"); // parray
            if (lua_type(Lua, -1) == LUA_TNUMBER)
            {
                //wxLogWarning("Array '%s' has 'pptr' field, using this instead of '?ptr'", path);
            }
            else
            {
                lua_getfield(Lua, -2, "?ptr");
                lua_replace(Lua, -2);
            }
		}
		dataPtr = reinterpret_cast<void*>((uint32_t)lua_tonumber(Lua, -1));
		lua_pop(Lua, 1);
		if (customType)
		{
			continue; // only offset
		}
		lua_pushvalue(Lua, -2); // GetArrayUpval
        lua_pushvalue(Lua, -2); // array
		uint32_t sizeValue = 0;
		// TODO: can use simply getfield instead of extracting upvalues
		if (std::reference_wrapper<uint32_t*>* sizePtr = std::get_if<std::reference_wrapper<uint32_t*>>(&sizeVariant))
		{
			lua_pushstring(Lua, "lenP");
			int error = lua_pcall(Lua, 2, 1, 0);
			if (error)
			{
				wxLogFatalError("Error while trying to get lenP of '%s' array: %s", path, lua_tostring(Lua, -1));
				lua_settop(Lua, origStack);
				return;
			}
			sizePtr->get() = reinterpret_cast<uint32_t*>((uint32_t)lua_tonumber(Lua, -1));
			sizeValue = (uint32_t)sizePtr->get();
			/*if (dataPtr) // add offset // disabled, because since these arrays are at 0 pos, lenP uses full pointer, so result would be wrong
			{
				wxLogInfo("Adding nonzero data offset (0x%X) to lenP of array '%s'", (uint32_t)dataPtr, path);
				wxLog::FlushActive();
				sizePtr->get() += (uint32_t)dataPtr;
			}*/
		}
		else if (std::reference_wrapper<uint32_t>* size = std::get_if<std::reference_wrapper<uint32_t>>(&sizeVariant))
		{
			lua_pushstring(Lua, "count");
            int error = lua_pcall(Lua, 2, 1, 0);
            if (error)
            {
                wxLogError("Error while trying to get count of '%s' array: %s", path, lua_tostring(Lua, -1));
				lua_settop(Lua, origStack);
                return;
            }
			size->get() = lua_tonumber(Lua, -1);
			sizeValue = size->get();
		}
		else // std::monostate
		{
			sizeValue = 1;
		}
		lua_settop(Lua, stackPos);
		wxASSERT_MSG(dataPtr && sizeValue, wxString::Format("[Array '%s'] invalid values: dataPtr is 0x%X, %s is 0x%X",
			path, (uint32_t)dataPtr, std::holds_alternative<std::reference_wrapper<uint32_t*>>(sizeVariant) ? "sizePtr" : "size", sizeValue
		));
	}
	lua_settop(Lua, origStack);
}



std::string luaTypeToString(lua_State* L, int idx)
{
    switch (lua_type(L, idx))
    {
    case LUA_TNIL:
        return "nil";
    case LUA_TBOOLEAN:
        return "boolean";
    case LUA_TSTRING:
        return "string";
    case LUA_TNUMBER:
        return "number";
    case LUA_TTABLE:
        return "table";
    case LUA_TTHREAD:
        return "thread";
    case LUA_TUSERDATA:
        return "userdata";
	case LUA_TFUNCTION:
		return "function";
    }
    return "";
}

std::string getLuaTypeMismatchString(std::initializer_list<int> wanted, int provided, int stackIndex)
{
    return wxString::Format("Expected %s, got %s (stack index of parameter is %d)", buildWantedLuaTypeString(wanted), luaTypeToString(Lua, provided), stackIndex).ToStdString();
}

std::string getLuaTypeMismatchString(int wanted, int provided, int stackIndex)
{
    return getLuaTypeMismatchString({ wanted }, provided, stackIndex);
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
	int stackPos = lua_gettop(Lua);
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
		lua_settop(Lua, stackPos);
		return;
	}
    int type = lua_type(Lua, -1); // if removed successfully, returns function, otherwise nothing (nil)
    wxASSERT_MSG(type == LUA_TFUNCTION, wxString::Format("Couldn't remove save game handler, received lua type %d", type));
	lua_settop(Lua, stackPos);
}