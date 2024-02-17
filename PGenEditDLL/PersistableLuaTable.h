#pragma once
#include "main.h"
#include "LuaTable.h"
#include "LuaRegistryPersistableValue.h"

// a subclass of LuaTable, which provides additional ability to be stored in registry (keeps table identity [memory address] during runtime)
// note: value changes do not automatically propagate to/from registry, you need to call updateFromRegistry or updateInRegistry
class PersistableLuaTable : public LuaTable, public LuaRegistryPersistableValue
{
public:
	// to be considered: should this method automatically update table in registry with correct values? "identity" and "current values" are mutually exclusive things
	// for now it doesn't, to keep consistency with other methods
	// WARNING: this pushes a copy of the table to the stack, not the table itself (for both contents and identity, use pushFromRegistryToLuaStack)
	void pushToLuaStack(lua_State* L) const override;
	// Inherited via LuaRegistryPersistableValue
	void updateFromRegistry(lua_State* L) override;
	bool updateInRegistry(lua_State* L) const override;

	// Inherited via LuaRegistryPersistableValue
	void pushFromRegistryToLuaStack(lua_State* L) const override;

	bool compareContentsAndIdentity(lua_State* L, const PersistableLuaTable& other) const;

	RTTR_REGISTRATION_FRIEND
};

