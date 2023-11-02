#pragma once
#include "pch.h"
#include "main.h"

struct _Nil {};
extern _Nil Nil;

inline bool operator==(const _Nil& lhs, const _Nil& rhs) // for std::unordered_map and other stuff, implements "there is only one Nil value"
{
    return true;
}

inline bool operator<(const _Nil& lhs, const _Nil& rhs) // for std::map
{
    return false;
}

static_assert(sizeof(lua_Number) == 8, "Unexpected lua_Number size");

struct LuaTable;
using LuaTableUPtr = std::unique_ptr<LuaTable>;
using LuaTypeInCpp = std::variant<
    _Nil,
    sqword_t,
    lua_Number,
    std::string,
    bool,
    LuaTable
>;

using LuaTableValues = std::map<LuaTypeInCpp, LuaTypeInCpp>;
using LuaTableValuesUPtr = std::unique_ptr<LuaTableValues>;
struct LuaTable // TODO: storing array part and hashed part separately - will improve table to lua conversion time, but will require tricky code
{
    // only values as unique_ptr doesn't work
    // values and table as unique_ptrs don't work with std::unordered_map
    // values and table as unique_ptrs work with std::map
    LuaTableValues values;
    void toLuaTable() const; // converts this structure into lua table on top of the stack
    // converts table at specified stack index into this value
    static LuaTable fromLuaTable(int index = -1);

    LuaTableValues::iterator begin();
    LuaTableValues::iterator end();
    LuaTableValues::const_iterator begin() const;
    LuaTableValues::const_iterator end() const;
    LuaTable(const LuaTableValues& values);
    LuaTable(LuaTableValues&& values);
    LuaTable(const LuaTable& other) = default;
    LuaTable& operator=(const LuaTable& other) = default;
    LuaTable& operator=(LuaTable&& other) = default;
    LuaTable(LuaTable&& other) = default;

    //LuaTypeInCpp& operator[](const LuaTypeInCpp& type);
    void emplace(LuaTypeInCpp&& key, LuaTypeInCpp&& value);
    const LuaTypeInCpp& at(const LuaTypeInCpp& type) const;
    LuaTypeInCpp& at(const LuaTypeInCpp& type);
    bool contains(const LuaTypeInCpp& type) const;
private:
    LuaTable() = default; // this is private, so lua tables without provided values won't be created
    static void luaConvertTypeCommon(LuaTypeInCpp& val, int stack);
};

using LuaValuePair = std::pair<LuaTypeInCpp, LuaTypeInCpp>;

inline bool operator==(const LuaValuePair& lhs, const LuaValuePair& rhs)
{
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

inline bool operator==(const LuaTable& lhs, const LuaTable& rhs)
{
    return lhs.values == rhs.values;
}

inline bool operator<(const LuaTable& lhs, const LuaTable& rhs)
{
    return lhs.values < rhs.values;
}

