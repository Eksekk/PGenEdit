#include "pch.h"
#include "LuaValue.h"
#include "LuaTable.h"
#include "LuaWrapper.h"

_Nil Nil;

std::string lua::utils::convertLuaTypeInCppTypeToString(const LuaTypeInCpp& type)
{
	if (const std::string* str = std::get_if<std::string>(&type))
	{
		return "string";
	}
	else if (const sqword_t* num = std::get_if<sqword_t>(&type))
	{
		return "number";
	}
	else if (const lua_Number* num = std::get_if<lua_Number>(&type))
	{
		return "number";
	}
	else if (const bool* b = std::get_if<bool>(&type))
	{
		return "boolean";
	}
	else if (const LuaTable* tbl = std::get_if<LuaTable>(&type))
	{
		return "table";
	}
	else if (const _Nil* nil = std::get_if<_Nil>(&type))
	{
		return "nil";
	}
	else
	{
		wxFAIL_MSG("Invalid LuaTypeInCpp type");
		return "unknown";
	}
}

std::string lua::utils::convertLuaTypeInCppToString(const LuaTypeInCpp& type)
{
	using std::to_string;
	return std::visit([](const auto& arg) -> std::string
		{
			return std::format("{}", arg);
		}, type);
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