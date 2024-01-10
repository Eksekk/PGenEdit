#include "pch.h"
#include "LuaValue.h"
#include "LuaTable.h"
#include "LuaWrapper.h"

_Nil Nil;

std::string lua::utils::convertLuaTypeInCppTypeToString(const LuaTypeInCpp& type)
{
	return type.typeToString();
}

std::string lua::utils::convertLuaTypeInCppToString(const LuaTypeInCpp& type)
{
	return type.valueToString();
}

// converts value to lua value and pushes it on the stack
void lua::utils::luaTypeInCppToStack(const LuaTypeInCpp& val, LuaWrapper& wrapper)
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
	else
	{
		wxFAIL_MSG("Invalid LuaTypeInCpp type");
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

bool LuaValue::isNil() const
{
	return std::holds_alternative<_Nil>(*this);
}

bool LuaValue::isNumber() const
{
	return std::holds_alternative<lua_Number>(*this) || std::holds_alternative<sqword_t>(*this);
}

bool LuaValue::isString() const
{
	return std::holds_alternative<std::string>(*this);
}

bool LuaValue::isBool() const
{
	return std::holds_alternative<bool>(*this);
}

bool LuaValue::isTable() const
{
	return std::holds_alternative<LuaTable>(*this);
}

lua_Number& LuaValue::getNumber()
{
	// TODO: insert return statement here
}

const lua_Number& LuaValue::getNumber() const
{
	// TODO: insert return statement here
}

std::string& LuaValue::getString()
{
	// TODO: insert return statement here
}

const std::string& LuaValue::getString() const
{
	// TODO: insert return statement here
}

bool& LuaValue::getBool()
{
	// TODO: insert return statement here
}

const bool& LuaValue::getBool() const
{
	// TODO: insert return statement here
}

LuaTable& LuaValue::getTable()
{
	// TODO: insert return statement here
}

const LuaTable& LuaValue::getTable() const
{
	// TODO: insert return statement here
}

lua_Number LuaValue::getNumberOr(lua_Number alt) const
{
	if (const lua_Number* num = std::get_if<lua_Number>(this))
	{
		return *num;
	}
	else if (const sqword_t* num = std::get_if<sqword_t>(this))
	{
		return *num;
	}
	else
	{
		return alt;
	}
}

std::string LuaValue::getStringOr(std::string_view alt) const
{
	if (const std::string* str = std::get_if<std::string>(this))
	{
		return *str;
	}
	else
	{
		return std::string(alt);
	}
}

bool LuaValue::getBoolOr(bool alt) const
{
	if (const bool* b = std::get_if<bool>(this))
	{
		return *b;
	}
	else
	{
		return alt;
	}
}

LuaTable LuaValue::getTableOr(const LuaTable& alt) const
{
	if (const LuaTable* tbl = std::get_if<LuaTable>(this))
	{
		return *tbl;
	}
	else
	{
		return alt;
	}
}

_Nil* LuaValue::getNilIf()
{
	return std::get_if<_Nil>(this);
}

const _Nil* LuaValue::getNilIf() const
{
	return std::get_if<_Nil>(this);
}

lua_Number* LuaValue::getNumberIf()
{
	return std::get_if<lua_Number>(this);
}

const lua_Number* LuaValue::getNumberIf() const
{
	return std::get_if<lua_Number>(this);
}

std::string* LuaValue::getStringIf()
{
	return std::get_if<std::string>(this);
}

const std::string* LuaValue::getStringIf() const
{
	return std::get_if<std::string>(this);
}

bool* LuaValue::getBoolIf()
{
	return std::get_if<bool>(this);
}

const bool* LuaValue::getBoolIf() const
{
	return std::get_if<bool>(this);
}

LuaTable* LuaValue::getTableIf()
{
	return std::get_if<LuaTable>(this);
}

const LuaTable* LuaValue::getTableIf() const
{
	return std::get_if<LuaTable>(this);
}

rttr::variant LuaValue::toRttrVariant(rttr::type type) const
{
	return rttr::variant();
}

bool LuaValue::isType(int type) const
{
	switch (type)
	{
	case LUA_TNUMBER:
			return isNumber();
	case LUA_TSTRING:
		return isString();
	case LUA_TBOOLEAN:
		return isBool();
	case LUA_TTABLE:
		return isTable();
	case LUA_TNIL:
		return isNil();
	default:
		return false;

	}
}

int LuaValue::getType() const
{
	if (isNil())
	{
		return LUA_TNIL;
	}
	else if (isNumber())
	{
		return LUA_TNUMBER;
	}
	else if (isString())
	{
		return LUA_TSTRING;
	}
	else if (isBool())
	{
		return LUA_TBOOLEAN;
	}
	else if (isTable())
	{
		return LUA_TTABLE;
	}
	else
	{
		wxFAIL_MSG("Invalid LuaValue type");
		return LUA_TNONE;
	}
}

std::string LuaValue::typeToString() const
{
	if (isNil())
	{
		return "nil";
	}
	else if (isNumber())
	{
		return "number";
	}
	else if (isString())
	{
		return "string";
	}
	else if (isBool())
	{
		return "boolean";
	}
	else if (isTable())
	{
		return "table";
	}
	else
	{
		wxFAIL_MSG("Invalid LuaValue type");
		return "invalid";
	}
}

std::string LuaValue::valueToString() const
{
	return std::visit([](const auto& arg) -> std::string
		{
			return std::format("{}", arg);
		}, *this);
}

std::string LuaValue::toString() const
{
	return std::format("{}: {}", typeToString(), valueToString());
}

void LuaValue::pushToLuaStack(lua_State* L) const
{
}

void LuaValue::pushToLuaStack(LuaWrapper& w) const
{
}

lua_Number LuaValue::toNumber(bool& ok) const
{
	return lua_Number();
}

std::string LuaValue::toString(bool& ok) const
{
	return std::string();
}

bool LuaValue::toBool(bool& ok) const
{
	return false;
}

LuaTable LuaValue::toTable(bool& ok) const
{
	return LuaTable();
}

bool LuaValue::toNumberInplace()
{
	return false;
}

bool LuaValue::toStringInplace()
{
	return false;
}

bool LuaValue::toBoolInplace()
{
	return false;
}

bool LuaValue::toTableInplace()
{
	return false;
}

LuaValue::LuaValue(const rttr::variant& var)
{
}
