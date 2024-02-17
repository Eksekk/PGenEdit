#include "pch.h"
#include "PersistableLuaTable.h"
#include "LuaWrapper.h"

void PersistableLuaTable::pushToLuaStack(lua_State* L) const
{
    // WARNING: if updateInRegistry method is called, this will cause infinite recursion
    return LuaTable::pushToLuaStack(L);
}

void PersistableLuaTable::updateFromRegistry(lua_State* L)
{
	LuaStackAutoRestore sr(L);
	pushFromRegistryToLuaStack(L);
    updateFromLuaTableOnStack(L);
}

bool PersistableLuaTable::updateInRegistry(lua_State* L) const
{
    LuaStackAutoRestore sr(L);
    pushToLuaStack(L); // WARNING: if pushToLuaStack calls this method, this will cause infinite recursion
    return LuaWrapper(L).setPath({LuaRegistryPersistableValue::registrySubtableKeyTables, *registryKey}, LUA_REGISTRYINDEX);
}

void PersistableLuaTable::pushFromRegistryToLuaStack(lua_State* L) const
{
	LuaStackAutoRestore sr(L);
	LuaWrapper(L).getPath({LuaRegistryPersistableValue::registrySubtableKeyTables, *registryKey}, LUA_REGISTRYINDEX);
}

bool PersistableLuaTable::compareContentsAndIdentity(lua_State* L, const PersistableLuaTable& other) const
{
    LuaStackAutoRestore sr(L);
    pushFromRegistryToLuaStack(L);
    other.pushFromRegistryToLuaStack(L);
    LuaWrapper w(L);
    if (!w.rawequal(-1, -2)) // identity check
	{
		return false;
    }
    return *this == other; // contents check
}

PersistableLuaTable::PersistableLuaTable(const LuaTable& t) : LuaTable(t), LuaRegistryPersistableValue(LUA_TTABLE)
{

}

PersistableLuaTable::PersistableLuaTable(const PersistableLuaTable& other) : LuaRegistryPersistableValue(other)
{
}

PersistableLuaTable::PersistableLuaTable(PersistableLuaTable&& other) : LuaRegistryPersistableValue(std::forward<LuaRegistryPersistableValue>(other))
{
}

PersistableLuaTable::PersistableLuaTable() : LuaRegistryPersistableValue(LUA_TTABLE)
{

}
