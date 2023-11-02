#pragma once
#include "pch.h"
#include "main.h"

namespace
{
    template <typename T>
    using Ref = std::reference_wrapper<T>;
}
struct LuaTable;
using LuaTableUPtr = std::unique_ptr<LuaTable>;

struct _Nil {};

static_assert(sizeof(lua_Number) == 8, "Unexpected lua_Number size");

using LuaTypesInCpp = std::variant<
    _Nil,
    sqword_t,
    lua_Number,
    std::string,
    bool,
    LuaTable
>;

inline bool operator<(const _Nil& lhs, const _Nil& rhs)
{
    return false;
}

using LuaTableValues = std::map<LuaTypesInCpp, LuaTypesInCpp>;
using LuaTableValuesUPtr = std::unique_ptr<LuaTableValues>;
struct LuaTable
{
    // only values as unique_ptr doesn't work
    // values and table as unique_ptrs don't work with std::unordered_map
    // values and table as unique_ptrs work with std::map
    LuaTableValuesUPtr values;
    static LuaTable fromLuaTable(int index = -1); // converts table at specified stack index into this value
    static void toLuaTable(); // converts this structure into lua table on top of the stack
    // extracts keys from table at specified stack index and creates instance of this class, but for table calls itself recursively with created output LuaTable
    static LuaTable processSingleTableContents(int index = -1);
    LuaTableValues::iterator begin();
    LuaTableValues::iterator end();
    LuaTableValues::const_iterator begin() const;
    LuaTableValues::const_iterator end() const;
    LuaTable();
    LuaTable(const LuaTable& other) = default;
    LuaTable& operator=(const LuaTable& other) = default;
    LuaTable& operator=(LuaTable&& other) = default;
    LuaTable(LuaTable&& other) = default;

    //LuaTypesInCpp& operator[](const LuaTypesInCpp& type);
    void emplace(LuaTypesInCpp&& key, LuaTypesInCpp&& value);
    const LuaTypesInCpp& at(const LuaTypesInCpp& type) const;
    LuaTypesInCpp& at(const LuaTypesInCpp& type);
    bool contains(const LuaTypesInCpp& type) const;
private:
    static void luaConvertTypeCommon(LuaTypesInCpp& val, int stack);
};

using LuaValuePair = std::pair<LuaTypesInCpp, LuaTypesInCpp>;

inline bool operator==(const LuaValuePair& lhs, const LuaValuePair& rhs)
{
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

inline bool operator==(const _Nil& lhs, const _Nil& rhs)
{
    return true;
}

inline bool operator==(const LuaTable& lhs, const LuaTable& rhs)
{
    return lhs.values == rhs.values;
}

inline bool operator<(const LuaTable& lhs, const LuaTable& rhs)
{
    return lhs.values < rhs.values;
}

namespace std
{
    //     template<>
    //     struct hash<_Nil>
    //     {
    //         size_t operator()(const _Nil& Nil) const noexcept
    //         {
    //             return (size_t)1;
    //         }
    //     };
    //     template<>
    //     struct hash<LuaValuePair>
    //     {
    //         size_t operator()(const LuaValuePair& pair) const noexcept
    //         {
    //             return std::hash<LuaTypesInCpp>()(pair.first) ^ std::hash<LuaTypesInCpp>()(pair.second);
    //         }
    //     };
    //     template<>
    //     struct hash<LuaTable>
    //     {
    //         size_t operator()(const LuaTable& tbl) const noexcept
    //         {
    //             size_t res = 0;
    //             for (const auto& pair : tbl.values)
    //             {
    //                 res ^= std::hash<LuaValuePair>()(pair);
    //             }
    //             return res;
    //         }
    //     };
}

extern _Nil Nil;

