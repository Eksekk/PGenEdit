#pragma once
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
    // TODO: I wanted to allow to duplicate lua_Number as sqword_t (and maybe qword_t) to have full 64-bit range of numbers,
    // but this will cause equality checking errors (different types, same real value) and will require some code to mitigate
    // !!! also usual floating-point equality checking problems!
    sqword_t,
    lua_Number,
    std::string,
    bool,
    LuaTable
>;

// from stack overflow
template<typename Float>
bool essentiallyEqualFloats(Float a, Float b)
{
    // checking for pointer, because I use variants with std::get_if
    static_assert(!std::is_pointer_v<Float>, "This function doesn't accept pointers to floating-point values");
    using std::abs;
    Float epsilon = std::numeric_limits<Float>::epsilon();
    return abs(a - b) <= ((abs(a) > abs(b) ? abs(b) : abs(a)) * epsilon);
}

// to correctly handle floating-point keys with integer value transformed into integers
bool operator==(const LuaTypeInCpp& a, const LuaTypeInCpp& b);
bool operator!=(const LuaTypeInCpp& a, const LuaTypeInCpp& b);

using LuaValuePair = std::pair<LuaTypeInCpp, LuaTypeInCpp>;

using LuaTableValues = std::map<LuaTypeInCpp, LuaTypeInCpp>;
using LuaTableValuesWithArray = std::set<std::variant<LuaTypeInCpp, LuaValuePair>>;
using LuaTableValuesUPtr = std::unique_ptr<LuaTableValues>;
struct LuaTable // TODO: storing array part and hashed part separately - will improve table to lua conversion time, but will require tricky code
{
    // only values as unique_ptr doesn't work
    // values and table as unique_ptrs don't work with std::unordered_map
    // values and table as unique_ptrs work with std::map
    LuaTableValues values;
    void pushToLuaStack() const; // converts this structure into lua table on top of the stack
    // TODO: a version updating lua table at specified index
    // converts table at specified stack index into this value
    static LuaTable fromLuaTable(int index = -1);

    LuaTableValues::iterator begin();
    LuaTableValues::iterator end();
    LuaTableValues::const_iterator begin() const;
    LuaTableValues::const_iterator end() const;
    LuaTableValues::const_iterator cbegin() const;
    LuaTableValues::const_iterator cend() const;
    LuaTable(const LuaTableValues& values);
    LuaTable(LuaTableValues&& values);

    // unfortunately, can't make this a constructor, because it will be ambiguous with LuaTableValues when passed initializer_list
    // also accepts normal key-value pairs in addition to individual array elements
    static LuaTable constructFromValuesWithArray(LuaTableValuesWithArray&& values);
    // also accepts normal key-value pairs in addition to individual array elements
    static LuaTable constructFromValuesWithArray(const LuaTableValuesWithArray& values);
    LuaTable() = default;
    LuaTable(const LuaTable& other) = default;
    LuaTable& operator=(const LuaTable& other) = default;//FIX
    LuaTable& operator=(LuaTable&& other) = default;//FIX
    LuaTable(LuaTable&& other) = default;//FIX

    LuaTypeInCpp& operator[](const LuaTypeInCpp& type);
    void emplace(LuaTypeInCpp&& key, LuaTypeInCpp&& value);
    void arrayInsert(const LuaTypeInCpp& value);
    // gets table field or creates it if it doesn't exist
    // WARNING: this will overwrite existing value if it's not a table
    LuaTable& getTableFieldOrCreate(const LuaTypeInCpp& type);
    const LuaTypeInCpp& at(const LuaTypeInCpp& type) const;
    LuaTypeInCpp& at(const LuaTypeInCpp& type);
    bool contains(const LuaTypeInCpp& type) const;
    // gets consecutive integer keys' values as a vector
    // stops on first missing index
    std::vector<LuaTypeInCpp> getArrayPart() const;
private:
    static void luaConvertTypeCommon(LuaTypeInCpp& val, int stack);
    static void tryToIntegerRef(LuaTypeInCpp& type);
    static LuaTypeInCpp tryToIntegerRet(const LuaTypeInCpp& type);
    static bool canBeInteger(const LuaTypeInCpp& type);
    static LuaTableValues tryToIntegerFull(const LuaTableValues& values);
    static LuaTableValues tryToIntegerFull(LuaTableValues&& values);

    RTTR_REGISTRATION_FRIEND
};

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

