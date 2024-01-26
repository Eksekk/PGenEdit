#include "pch.h"
#include "LuaRegistryPersistableValue.h"
#include "Utility.h"

LuaRegistryPersistableValue::LuaRegistryPersistableValue(int luaType) : registryKey(util::guid::newGuidString()), luaType(luaType)
{
	static const std::initializer_list<int> acceptableTypes = { LUA_TFUNCTION, LUA_TTABLE, LUA_TUSERDATA, LUA_TTHREAD };
	wxASSERT_MSG(util::container::existsInContainer(acceptableTypes, luaType), "LuaRegistryPersistableValue can only be used with LUA_TFUNCTION, LUA_TTABLE, LUA_TUSERDATA, LUA_TTHREAD");
}

LuaRegistryPersistableValue::LuaRegistryPersistableValue(const LuaRegistryPersistableValue& other) : registryKey(other.registryKey), luaType(other.luaType)
{
}

LuaRegistryPersistableValue::~LuaRegistryPersistableValue()
{

}
