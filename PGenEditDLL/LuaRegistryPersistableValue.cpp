#include "pch.h"
#include "LuaRegistryPersistableValue.h"
#include "Utility.h"
#include "LuaWrapper.h"

static const std::initializer_list<int> acceptableTypes = { LUA_TFUNCTION, LUA_TTABLE, LUA_TUSERDATA, LUA_TTHREAD };

const std::string LuaRegistryPersistableValue::registrySubtableKeyFunctions = "functions";
const std::string LuaRegistryPersistableValue::registrySubtableKeyTables = "tables";
const std::string LuaRegistryPersistableValue::registrySubtableKeyUserdata = "userdata";
const std::string LuaRegistryPersistableValue::registrySubtableKeyThreads = "threads";

const std::map<int, const std::string> LuaRegistryPersistableValue::registrySubtableKeyByLuaType{
	{LUA_TFUNCTION, registrySubtableKeyFunctions}, {LUA_TTABLE, registrySubtableKeyTables}, {LUA_TUSERDATA, registrySubtableKeyUserdata}, {LUA_TTHREAD, registrySubtableKeyThreads}
};

std::map<int, bool> LuaRegistryPersistableValue::initPerformedFor{
	{LUA_TFUNCTION, false}, {LUA_TTABLE, false}, {LUA_TUSERDATA, false}, {LUA_TTHREAD, false}
};

void LuaRegistryPersistableValue::initFor(int type)
{
	wxASSERT_MSG(util::container::existsInContainer(acceptableTypes, type), "LuaRegistryPersistableValue can only be used with LUA_TFUNCTION, LUA_TTABLE, LUA_TUSERDATA, LUA_TTHREAD");
	wxASSERT_MSG(!initPerformedFor.at(type), "initFor should only be called once for each type");
	constexpr auto&& w = luaWrapper;

	LuaStackAutoRestore sr(w.getLuaState());
	w.getPath({ "pgenedit", registrySubtableKeyByLuaType.at(type) }, LUA_REGISTRYINDEX, true, true);

	// need weak values for functions table to not prevent garbage collection of functions
	w.setmetatableArg(-2, LuaTable{ {{"__mode", "v"}}});
// 	w.createtable(0, 0);
// 	w.pushstring("v");
// 	w.setfield(-2, "__mode");
// 	w.setmetatable(-2);

	initPerformedFor[type] = true;
}

void LuaRegistryPersistableValue::tryInitOnceFor(int type)
{
	// lazy initialization - should be called in constructors
	if (!initPerformedFor.at(type))
	{
		initFor(type);
	}
}

LuaRegistryPersistableValue::LuaRegistryPersistableValue(int luaType) : registryKey(util::guid::newGuidString()), luaType(luaType)
{
	wxASSERT_MSG(util::container::existsInContainer(acceptableTypes, luaType), "LuaRegistryPersistableValue can only be used with LUA_TFUNCTION, LUA_TTABLE, LUA_TUSERDATA, LUA_TTHREAD");
	tryInitOnceFor(luaType);
}

LuaRegistryPersistableValue::LuaRegistryPersistableValue(const LuaRegistryPersistableValue& other) : registryKey(other.registryKey), luaType(other.luaType)
{
	// since it's a copy constructor, we probably don't need to call tryInitOnceFor, but doing it just in case
	wxASSERT_MSG(util::container::existsInContainer(acceptableTypes, luaType), "LuaRegistryPersistableValue can only be used with LUA_TFUNCTION, LUA_TTABLE, LUA_TUSERDATA, LUA_TTHREAD");
	tryInitOnceFor(luaType);
}

LuaRegistryPersistableValue::~LuaRegistryPersistableValue()
{

}
