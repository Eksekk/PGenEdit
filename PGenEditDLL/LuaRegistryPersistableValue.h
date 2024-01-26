#pragma once

// registry -> pgenedit -> functions -> [some sort of unique key] -> function [together with metadata]

// VALUES THAT [NEED TO] / [CAN] BE PERSISTABLE (i.e. stored in registry):
// function
// table
// userdata (only full one, not light one)
// thread

// persistable value traits:
// - can be both stored in registry and stored directly in C++ (table), or only in registry (function, userdata, thread)
// - all values must be reference-counted, to "free" value in registry for garbage collection only when all C++ references to it are gone

// !!! "PersistableLuaTable" class which inherits from LuaTable and LuaRegistryPersistableValue?

class LuaValue;

class LuaRegistryPersistableValue
{
	// registry key is GUID represented as string
	const std::string registryKey;

protected:
	// returns the key that will be name of registry subtable field (for functions "functions", for tables "tables", etc.)
	virtual std::string getRegistrySubtableKey() const = 0;

public:
	const int luaType; // LUA_TFUNCTION, LUA_TTABLE, LUA_TUSERDATA, LUA_TTHREAD
	// always called, generates a new GUID to use as a registry key
	LuaRegistryPersistableValue(int luaType);
	// derived classes NEED to call this copy constructor in their copy constructors
	LuaRegistryPersistableValue(const LuaRegistryPersistableValue& other);
	virtual ~LuaRegistryPersistableValue();

	virtual void updateFromRegistry(lua_State* L) = 0;
	virtual bool updateInRegistry(lua_State* L) const = 0;
};

