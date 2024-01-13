#include "pch.h"
#include "LuaValue.h"
#include "LuaTable.h"
#include "LuaWrapper.h"

_Nil Nil;

using ::lua::utils::luaError;
using ::lua::utils::luaAssert;

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
	val.pushToLuaStack(wrapper);
}

LuaTypeInCpp lua::utils::convertStackIndexToLuaTypeInCpp(lua_State* L, int stackIndex)
{
	return LuaTypeInCpp(L, stackIndex);
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
	return const_cast<lua_Number&>(static_cast<const LuaValue&>(*this).getNumber());
}

const lua_Number& LuaValue::getNumber() const
{
	if (const lua_Number* num = std::get_if<lua_Number>(this))
	{
		return *num;
	}
	else
	{
		luaError("LuaValue is not a floating-point, it's {}", *this);
	}
}

sqword_t& LuaValue::getInteger()
{
	return const_cast<sqword_t&>(static_cast<const LuaValue&>(*this).getInteger());
}

const sqword_t& LuaValue::getInteger() const
{
	if (const sqword_t* num = std::get_if<sqword_t>(this))
	{
		return *num;
	}
	else
	{
		luaError("LuaValue is not an integer, it's {}", *this);
	}
}

lua_Number& LuaValue::getNumberAny()
{
	if (lua_Number* num = std::get_if<lua_Number>(this))
	{
		return *num;
	}
	else if (sqword_t* num = std::get_if<sqword_t>(this))
	{
		return emplace<lua_Number>(*num);
	}
	else
	{
		luaError("LuaValue is not a number, it's {}", *this);
	}
}

lua_Number LuaValue::getNumberAny() const
{
	// big problem: in non-const getNumberAny(), we converted the variant to integer if it was lua_Number, but we can't so this here, because "this" is const-qualified
	// could use const_cast, but it's not safe
	// so, I changed above to work around this problem, so numbers are not converted to integers anymore
	// but this is not a good solution, because it's not consistent with LuaTable, where we do convert to integers
	// so, I need to think about this more

	// DECIDED: since this is const version, this means that variant will be initialized only once. So, we can convert it to integer or floating-point in the constructor if needed, and return non-const-reference version as I chose here (because it won't get modified without UB, so no need for reference at all)
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
		luaError("LuaValue is not a number, it's {}", *this);
	}
}

std::string& LuaValue::getString()
{
	return const_cast<std::string&>(static_cast<const LuaValue&>(*this).getString());
}

const std::string& LuaValue::getString() const
{
	if (const std::string* str = std::get_if<std::string>(this))
	{
		return *str;
	}
	else
	{
		luaError("LuaValue is not a string, it's {}", *this);
	}
}

bool& LuaValue::getBool()
{
	return const_cast<bool&>(static_cast<const LuaValue&>(*this).getBool());
}

const bool& LuaValue::getBool() const
{
	if (const bool* b = std::get_if<bool>(this))
	{
		return *b;
	}
	else
	{
		luaError("LuaValue is not a boolean, it's {}", *this);
	}
}

LuaTable& LuaValue::getTable()
{
	return const_cast<LuaTable&>(static_cast<const LuaValue&>(*this).getTable());
}

const LuaTable& LuaValue::getTable() const
{
	if (const LuaTable* tbl = std::get_if<LuaTable>(this))
	{
		return *tbl;
	}
	else
	{
		luaError("LuaValue is not a table, it's {}", *this);
	}
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

sqword_t* LuaValue::getIntegerIf()
{
	return std::get_if<sqword_t>(this);
}

const sqword_t* LuaValue::getIntegerIf() const
{
	return std::get_if<sqword_t>(this);
}

lua_Number* LuaValue::getNumberIf()
{
	return std::get_if<lua_Number>(this);
}

const lua_Number* LuaValue::getNumberIf() const
{
	return std::get_if<lua_Number>(this);
}

lua_Number* LuaValue::getNumberAnyIf()
{
	if (lua_Number* num = std::get_if<lua_Number>(this))
	{
		return num;
	}
	else if (sqword_t* num = std::get_if<sqword_t>(this))
	{
		return &emplace<lua_Number>(*num);
	}
	else
	{
		return nullptr;
	}
}

const lua_Number* LuaValue::getNumberAnyIf() const
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
	LuaWrapper w(L);
	pushToLuaStack(w);
}

void LuaValue::pushToLuaStack(LuaWrapper& w) const
{
	if (const _Nil* nil = getNilIf())
	{
		w.pushnil();
	}
	else if (const sqword_t* num = getIntegerIf())
	{
		w.pushnumber(*num);
	}
	else if (const lua_Number* num = getNumberIf())
	{
		w.pushnumber(*num);
	}
	else if (const std::string* str = getStringIf())
	{
		w.pushstring(*str);
	}
	else if (const bool* b = getBoolIf())
	{
		w.pushboolean(*b);
	}
	else if (const LuaTable* tbl = getTableIf())
	{
		tbl->pushToLuaStack(w.getLuaState());
	}
	else
	{
		wxFAIL_MSG("Invalid LuaTypeInCpp type");
	}
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

LuaValue::LuaValue(lua_State* L, int index)
{
	LuaWrapper w(L);
	switch (w.type(index))
	{
	case LUA_TNIL:
		*this = Nil;
		break;
	case LUA_TBOOLEAN:
		*this = w.toboolean(index);
		break;
	case LUA_TSTRING:
		*this = w.tostring(index);
		break;
	case LUA_TNUMBER:
		*this = w.tonumber(index);
		break;
	case LUA_TTABLE:
		*this = LuaTable(L, index);
		break;
	default:
		luaError("Unsupported lua type '{}'", w.typename_(index));
		*this = Nil;
		break;
	}
}
