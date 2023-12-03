#include "pch.h"
#include "LuaTable.h"
#include "LuaFunctions.h"
#include "LuaWrapper.h"

_Nil Nil;

// converts value to lua value and pushes it on the stack
void luaTypeInCppToStack(const LuaTypeInCpp& val, LuaWrapper& wrapper)
{
    if (const _Nil* nil = std::get_if<_Nil>(&val))
    {
        wrapper.pushnil();
    }
    else if (const sqword_t* num = std::get_if<sqword_t>(&val))
    {
        wrapper.pushnumber(*num);
    }
    else if (const lua_Number* num = std::get_if<lua_Number>(&val))
    {
        wrapper.pushnumber(*num);
    }
    else if (const std::string* str = std::get_if<std::string>(&val))
    {
        wrapper.pushstring(*str);
    }
    else if (const bool* b = std::get_if<bool>(&val))
    {
        wrapper.pushboolean(*b);
    }
    else if (const LuaTable* tbl = std::get_if<LuaTable>(&val))
    {
        tbl->pushToLuaStack(wrapper.getLuaState());
    }
}

void LuaTable::pushToLuaStack(lua_State* L) const
{
    LuaWrapper wrapper(L);
    wrapper.newtable();
    for (const auto& [key, value] : values)
    {
        if (!std::holds_alternative<_Nil>(key) && !std::holds_alternative<_Nil>(value))
        {
            luaTypeInCppToStack(key, wrapper);
            luaTypeInCppToStack(value, wrapper);
            wrapper.settable(-3);
        }
    }
}

void argError(const std::string& expected, const std::string& actual)
{
    wxLogError("Expected type '%s', got '%s'", expected, actual);
}

void LuaTable::luaConvertTypeCommon(lua_State* L, LuaTypeInCpp& val, int stack)
{
    LuaWrapper wrapper(L);
    stack = wrapper.makeAbsoluteStackIndex(stack);
    switch (lua_type(L, stack))
    {
    case LUA_TNIL:
        val = Nil;
        break;
    case LUA_TTABLE:
        val = LuaTable::fromLuaTable(L, stack);
        break;
    case LUA_TNUMBER:
    {
        lua_Number num = lua_tonumber(L, stack);
        lua_Number asInteger = (lua_Number)static_cast<sqword_t>(num);
        if (asInteger == num)
        {
            val = static_cast<sqword_t>(num);
        }
        else
        {
            val = num;
        }
    }
    break;
    case LUA_TBOOLEAN:
        val = (bool)lua_toboolean(L, stack);
        break;
    case LUA_TSTRING:
    {
        const char* p;
        size_t s;
        p = lua_tolstring(L, stack, &s);
        val = std::string(p, s);
    }
    break;
    }
}

LuaTable LuaTable::fromLuaTable(lua_State* L, int index)
{
    LuaWrapper wrapper(L);
    wxASSERT_MSG(wrapper.isTable(index), wxString::Format("Value at index #%d is not a table", index));
    static sqword_t dword_max = std::numeric_limits<dword_t>::max(), sdword_min = std::numeric_limits<sdword_t>::min(), sdword_max = std::numeric_limits<sdword_t>::max();
    index = wrapper.makeAbsoluteStackIndex(index);
    int prevStack = lua_gettop(L);
    LuaTable t;
    lua_pushnil(L); // first key
    while (lua_next(L, index) != 0) // key is at -2, value is at -1
    
    {
        LuaTypeInCpp key;
        LuaTypeInCpp value;
        switch (lua_type(L, -2)) // key
        {
        case LUA_TNIL:
        case LUA_TTABLE:
        case LUA_TNUMBER:
        case LUA_TBOOLEAN:
        case LUA_TSTRING:
            LuaTable::luaConvertTypeCommon(L, key, -2);
            break;
            // those below are unsupported
        case LUA_TFUNCTION:
            argError("function", luaTypeToString(L, -2));
            break;
        case LUA_TTHREAD:
            argError("thread", luaTypeToString(L, -2));
            break;
        case LUA_TUSERDATA:
            argError("userdata", luaTypeToString(L, -2));
            break;
        case LUA_TLIGHTUSERDATA:
            argError("light userdata", luaTypeToString(L, -2));
            break;
        }

        switch (lua_type(L, -1)) // value
        {
        case LUA_TNIL:
        case LUA_TTABLE:
        case LUA_TNUMBER:
        case LUA_TBOOLEAN:
        case LUA_TSTRING:
            LuaTable::luaConvertTypeCommon(L, value, -1);
            break;
            // those below are unsupported
        case LUA_TFUNCTION:
            argError("function", luaTypeToString(L, -1));
            break;
        case LUA_TTHREAD:
            argError("thread", luaTypeToString(L, -1));
            break;
        case LUA_TUSERDATA:
            argError("userdata", luaTypeToString(L, -1));
            break;
        case LUA_TLIGHTUSERDATA:
            argError("light userdata", luaTypeToString(L, -1));
            break;
        }
        t.emplace(std::move(key), std::move(value));
        lua_pop(L, 1); // pop value, leave key
    }
    lua_settop(L, prevStack);
    return t;
}

LuaTableValues::iterator LuaTable::begin()
{
    return values.begin();
}

LuaTableValues::iterator LuaTable::end()
{
    return values.end();
}

LuaTableValues::const_iterator LuaTable::begin() const
{
    return values.begin();
}

LuaTableValues::const_iterator LuaTable::end() const
{
    return values.end();
}

LuaTableValues::const_iterator LuaTable::cbegin() const
{
    return values.cbegin();
}

LuaTableValues::const_iterator LuaTable::cend() const
{
    return values.cend();
}

LuaTable::LuaTable(const LuaTableValues& values) : values(tryToIntegerFull(values))
{

}

LuaTable::LuaTable(LuaTableValues&& values) : values(tryToIntegerFull(std::forward<LuaTableValues>(values)))
{
}

void LuaTable::emplace(LuaTypeInCpp&& key, LuaTypeInCpp&& value)
{
    tryToIntegerRef(key);
    tryToIntegerRef(value);
    values.emplace(std::forward<LuaTypeInCpp>(key), std::forward<LuaTypeInCpp>(value));
}

const LuaTypeInCpp& LuaTable::at(const LuaTypeInCpp& type) const
{
    return values.at(type);
}

LuaTypeInCpp& LuaTable::at(const LuaTypeInCpp& type)
{
    return values.at(type);
}

bool LuaTable::contains(const LuaTypeInCpp& type) const
{
    return values.contains(type);
}

void LuaTable::tryToIntegerRef(LuaTypeInCpp& type)
{
    if (canBeInteger(type))
    {
        type = (sqword_t)std::get<lua_Number>(type);
    }
}

bool LuaTable::canBeInteger(const LuaTypeInCpp& type)
{
    if (const lua_Number* num = std::get_if<lua_Number>(&type))
    {
        return *num == (sqword_t)*num;
    }
    return false;
}
LuaTypeInCpp LuaTable::tryToIntegerRet(const LuaTypeInCpp& type)
{
    if (canBeInteger(type))
    {
        return (sqword_t)std::get<lua_Number>(type);
    }
    return type;
}

LuaTableValues LuaTable::tryToIntegerFull(const LuaTableValues& values)
{
    LuaTableValues vals = values;
    return tryToIntegerFull(std::move(vals));
}

LuaTableValues LuaTable::tryToIntegerFull(LuaTableValues&& values)
{
    std::vector<LuaTableValues::value_type> deferInsert;
    for (auto itr = values.begin(); itr != values.end(); )
    {
        auto& [key, value] = *itr;
        if (canBeInteger(key)) // key is const, need to remove map entry and insert new one later (to not break iteration)
        {
            LuaTableValues::value_type pair(tryToIntegerRet(key), tryToIntegerRet(value));
            itr = values.erase(itr);
            deferInsert.push_back(std::move(pair));
        }
        else // value is not const, can be modified in place
        {
            tryToIntegerRef(value);
            ++itr;
        }
    }
    for (auto& pair : deferInsert)
    {
        values.insert(std::move(pair));
    }
    return values;
}

LuaTypeInCpp& LuaTable::operator[](const LuaTypeInCpp& type)
{
    return values[type];
}

LuaTable LuaTable::constructFromValuesWithArray(LuaTableValuesWithArray&& values)
{
    LuaTableValues converted;
    int lastArrayIndex = 1;
    for (const auto& value : values)
    {
        if (const LuaValuePair* pair = std::get_if<LuaValuePair>(&value))
        {
            converted.emplace(tryToIntegerRet(pair->first), tryToIntegerRet(pair->second));
        }
        else if (const LuaTypeInCpp* val = std::get_if<LuaTypeInCpp>(&value))
        {
            converted.emplace(lastArrayIndex++, *val);
        }
    }

    LuaTable t;
    t.values = std::move(converted);
    return t;
}

LuaTable LuaTable::constructFromValuesWithArray(const LuaTableValuesWithArray& values)
{
    auto values2 = values;
    return constructFromValuesWithArray(std::move(values2));
}

std::vector<LuaTypeInCpp> LuaTable::getArrayPart() const
{
    std::vector<LuaTypeInCpp> arrayPart;
    for (int i = 1; ; ++i)
    {
        LuaTypeInCpp key = i;
        if (values.contains(key))
        {
            arrayPart.push_back(values.at(key));
        }
        else
        {
            break;
        }
    }
    return arrayPart;
}

LuaTable& LuaTable::getTableFieldOrCreate(const LuaTypeInCpp& type)
{

    if (values.contains(type))
    {
        if (LuaTable* t = std::get_if<LuaTable>(&values.at(type))) // already a table
        {
            return *t;
        }
        else // not a table, create one
        {
            values[type] = LuaTable{};
            return std::get<LuaTable>(values.at(type));
        }
    }
    else // doesn't have field, create one
    {
        values[type] = LuaTable{};
        return std::get<LuaTable>(values.at(type));
    }
}

void LuaTable::arrayInsert(const LuaTypeInCpp& value)
{
    for (int i = 1; ; ++i)
    {
        LuaTypeInCpp key = i;
        if (!values.contains(key))
        {
            values.emplace(std::move(key), value);
            break;
        }
    }
}

bool operator==(const LuaTypeInCpp& a, const LuaTypeInCpp& b)
{
    // cleanest way to have default operator for most types and custom behavior for some, without endless recursion, is this lambda way, I think
    return std::visit([](const auto& a, const auto& b) -> bool
    {
        using TypeA = std::decay_t<decltype(a)>;
        using TypeB = std::decay_t<decltype(b)>;
        if constexpr (SAME(TypeA, lua_Number) && SAME(TypeB, lua_Number))
        {
            return essentiallyEqualFloats(a, b);
        }
        else if constexpr ((SAME(TypeA, sqword_t) && SAME(TypeB, lua_Number)) || (SAME(TypeA, lua_Number) && SAME(TypeB, sqword_t)))
        {
            return a == b;
        }
        else if constexpr (SAME(TypeA, TypeB))
        {
            return a == b;
        }
        else
        {
            return false;
        }
    }, a, b); // generates lambda handler for each combination of types from variants, that is, usually size(a) * size(b) handlers
}

RTTR_REGISTRATION
{
    using namespace rttr;
    registration::class_<LuaTable>("LuaTable")
.property("LuaTableValues", &LuaTable::values)
.constructor<const LuaTableValues&>(registration::public_access)
.constructor<LuaTableValues&&>(registration::public_access)
.constructor<const LuaTable&>(registration::public_access)
.constructor<LuaTable&&>(registration::public_access)
.constructor<>()
.method("constructFromValuesWithArray", select_overload<LuaTable(const LuaTableValuesWithArray&)>(&LuaTable::constructFromValuesWithArray), registration::public_access)
.method("constructFromValuesWithArray", select_overload<LuaTable(LuaTableValuesWithArray&&)>(&LuaTable::constructFromValuesWithArray), registration::public_access)
.method("operator=", select_overload<LuaTable&(const LuaTable&)>(&LuaTable::operator=))
.method("operator=", select_overload<LuaTable&(LuaTable&&)>(&LuaTable::operator=))
.method("operator[]", &LuaTable::operator[])
.method("pushToLuaStack", &LuaTable::pushToLuaStack, registration::public_access)
.method("begin", select_overload<LuaTableValues::iterator()>(&LuaTable::begin), registration::public_access)//reinterpret_cast<typename LuaTableValues::iterator(__thiscall *)()>(&LuaTable::begin)
.method("end", select_overload<LuaTableValues::iterator()>(&LuaTable::end), registration::public_access)
.method("begin", select_overload<LuaTableValues::const_iterator() const>(&LuaTable::begin), registration::public_access)
.method("end", select_overload<LuaTableValues::const_iterator() const>(&LuaTable::end), registration::public_access)
.method("emplace", &LuaTable::emplace, registration::public_access)
.method("at", select_overload<const LuaTypeInCpp&(const LuaTypeInCpp&) const>(&LuaTable::at), registration::public_access)
.method("at", select_overload<LuaTypeInCpp&(const LuaTypeInCpp&)>(&LuaTable::at), registration::public_access)
.method("getArrayPart", &LuaTable::getArrayPart, registration::public_access)
.method("contains", &LuaTable::contains, registration::public_access)
.method("fromLuaTable", &LuaTable::fromLuaTable)
.method("luaConvertTypeCommon", &LuaTable::luaConvertTypeCommon, registration::private_access)
.method("tryToIntegerRef", &LuaTable::tryToIntegerRef, registration::private_access)
.method("tryToIntegerRet", &LuaTable::tryToIntegerRet, registration::private_access)
.method("canBeInteger", &LuaTable::canBeInteger, registration::private_access)
.method("tryToIntegerFull", select_overload<LuaTableValues(const LuaTableValues&)>(&LuaTable::tryToIntegerFull), registration::private_access)
.method("tryToIntegerFull", select_overload<LuaTableValues(LuaTableValues&&)>(&LuaTable::tryToIntegerFull), registration::private_access)
       ;
    registerExtra<LuaTable>();
}