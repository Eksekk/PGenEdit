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

namespace detail
{
	template<typename T>
	constexpr std::string registryKeyType;
}

// need to do initialization for all four types of persistable values only once, before their first use
// initialization belongs to class, not object, so using static function here is probably better
// but you can't override static functions, and we need access to registry subtable key ("functions" etc.), which currently is kept in object, not class (member field)
// ideally, you'd not need to pass an object of class to static function, but you can't access non-static members from static function

// this file can't reference the derived types directly, because of a potential circular dependency

class LuaRegistryPersistableValue
{
private:
	static void initFor(int type);
	static std::map<int, bool> initPerformedFor;
	static void tryInitOnceFor(int type);
protected:
	// registry key is GUID represented as string
	const std::string registryKey;

public:
	// names of registry subtable field (for functions "functions", for tables "tables", etc.)
	static const std::string registrySubtableKeyFunctions;
	static const std::string registrySubtableKeyTables;
	static const std::string registrySubtableKeyUserdata;
	static const std::string registrySubtableKeyThreads;
	static const std::map<int, const std::string> registrySubtableKeyByLuaType;

	const int luaType; // LUA_TFUNCTION, LUA_TTABLE, LUA_TUSERDATA, LUA_TTHREAD
	// always called, generates a new GUID to use as a registry key
	LuaRegistryPersistableValue(int luaType);
	// derived classes NEED to call this copy constructor in their copy constructors
	LuaRegistryPersistableValue(const LuaRegistryPersistableValue& other);
	virtual ~LuaRegistryPersistableValue();

	virtual void updateFromRegistry(lua_State* L) = 0;
	virtual bool updateInRegistry(lua_State* L) const = 0;
	virtual void pushFromRegistryToLuaStack(lua_State* L) const = 0;
};

