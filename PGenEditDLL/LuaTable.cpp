#include "pch.h"
#include "LuaTable.h"
#include "LuaFunctions.h"
#include "LuaWrapper.h"
#include "LuaValue.h"

using lua::utils::luaTypeInCppToStack;

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
            argError("function", lua::utils::luaTypeToString(L, -2));
            break;
        case LUA_TTHREAD:
            argError("thread", lua::utils::luaTypeToString(L, -2));
            break;
        case LUA_TUSERDATA:
            argError("userdata", lua::utils::luaTypeToString(L, -2));
            break;
        case LUA_TLIGHTUSERDATA:
            argError("light userdata", lua::utils::luaTypeToString(L, -2));
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
            argError("function", lua::utils::luaTypeToString(L, -1));
            break;
        case LUA_TTHREAD:
            argError("thread", lua::utils::luaTypeToString(L, -1));
            break;
        case LUA_TUSERDATA:
            argError("userdata", lua::utils::luaTypeToString(L, -1));
            break;
        case LUA_TLIGHTUSERDATA:
            argError("light userdata", lua::utils::luaTypeToString(L, -1));
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

LuaTable::LuaTable(lua_State* L, int index)
{
    *this = fromLuaTable(L, index);
}

LuaTable::LuaTable(lua_State* L, const std::string& luaCode)
{
    LuaWrapper w(L);
    if (w.dostring("return " + luaCode) != LUA_OK)
    {
		lua::utils::luaError("Error in LuaTable::LuaTable() constructor from lua code: received error '{}'", w.tostring(-1));
	}
    else
    {
		*this = fromLuaTable(L);
        w.pop(1);
	}
}

void LuaTable::emplace(LuaTypeInCpp&& key, LuaTypeInCpp&& value)
{
    tryToIntegerRef(key);
    tryToIntegerRef(value);
    values.emplace(std::forward<LuaTypeInCpp>(key), std::forward<LuaTypeInCpp>(value));
}

const LuaTypeInCpp& LuaTable::at(const LuaTypeInCpp& type) const
{
    auto type2 = tryToIntegerRet(type);
    return values.at(type2);
}

LuaTable& LuaTable::att(const LuaTypeInCpp& type)
{
	return const_cast<LuaTable&>(static_cast<const LuaTable&>(*this).att(type));
}

const LuaTable& LuaTable::att(const LuaTypeInCpp& type) const
{
	const LuaTypeInCpp& val = at(type);
	if (const LuaTable* t = std::get_if<LuaTable>(&val))
	{
		return *t;
	}
	else
	{
		lua::utils::luaError("LuaTable::att() called with key which contains non-table value of type '{}'", typeid(val).name());
		return *this;
	}
}

LuaTable& LuaTable::attc(const LuaTypeInCpp& type)
{
    if (contains(type))
    {
		return att(type);
	}
    else
    {
		values[type] = LuaTable{};
		return std::get<LuaTable>(at(type));
	}
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

std::vector<LuaTypeInCpp> LuaTable::getArrayPart(int firstIndex) const
{
    std::vector<LuaTypeInCpp> arrayPart;
    for (int i = firstIndex; ; ++i)
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

std::string LuaTable::dump(int depth) const
{
    LuaWrapper w(Lua);
    w.getglobal("dump");
    pushToLuaStack(Lua);
    depth != -1 ? w.pushnumber(depth) : w.pushnil();
    if (w.pcall(2, 1, 0))
	{
		std::string str = std::format("Error in dump(): {}", w.tostring(-1));
		w.pop(1);
		return str;
	}
    else
	{
		std::string str = w.tostring(-1);
		w.pop(1);
		return str;
	}
}

LuaTable LuaTable::fromLuaCode(lua_State* L, const std::string& code)
{
    LuaTable t(L, code);
    return t;
}

void LuaTable::pushArrayPartToLuaStack(lua_State* L, int firstIndex) const
{
    auto&& arr = getArrayPart(firstIndex);
    LuaWrapper w(L);
    for (const auto& val : arr)
    {
		luaTypeInCppToStack(val, w);
    }
}

void LuaTable::updateFromLuaTableOnStack(lua_State* L, int index /*= -1*/)
{
    *this = LuaTable(L, index);
}

LuaTable operator""_luaTable(const char* text, size_t len)
{
	wxASSERT_MSG(Lua, "LuaTable operator""_luaTable() called before Lua is initialized");
	LuaStackAutoRestore stackRestore(Lua);
    return LuaTable(Lua, std::string(text, len));
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
.constructor<lua_State*, int>(registration::public_access)
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
.method("att", select_overload<const LuaTable&(const LuaTypeInCpp&) const>(&LuaTable::att), registration::public_access)
.method("att", select_overload<LuaTable&(const LuaTypeInCpp&)>(&LuaTable::att), registration::public_access)
.method("attc", &LuaTable::attc, registration::public_access)
.method("getArrayPart", &LuaTable::getArrayPart, registration::public_access)
.method("contains", &LuaTable::contains, registration::public_access)
.method("getTableFieldOrCreate", &LuaTable::getTableFieldOrCreate, registration::public_access)
.method("arrayInsert", &LuaTable::arrayInsert, registration::public_access)
.method("dump", &LuaTable::dump, registration::public_access)
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

bool operator==(const LuaValuePair& lhs, const LuaValuePair& rhs)
{
	return lhs.first == rhs.first && lhs.second == rhs.second;
}

bool operator==(const LuaTable& lhs, const LuaTable& rhs)
{
	return lhs.values == rhs.values;
}

bool operator<(const LuaTable& lhs, const LuaTable& rhs)
{
	return lhs.values < rhs.values;
}
