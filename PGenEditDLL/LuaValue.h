#pragma once
#include "main.h"
#include "LuaTable.h"

struct _Nil {}; // this is a special type that represents nil in lua
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

using LuaTableUPtr = std::unique_ptr<LuaTable>;

class LuaValue;
using LuaTypeInCpp = LuaValue;
// to correctly handle floating-point keys with integer value transformed into integers
bool operator==(const LuaTypeInCpp& a, const LuaTypeInCpp& b);
bool operator!=(const LuaTypeInCpp& a, const LuaTypeInCpp& b);

class LuaWrapper;

// FIXME: change sqword_t to lua_Integer and go over all code using it etc. (lua has api functions for integers as well)
class LuaValue : public std::variant<
	_Nil,
	// TODO: I wanted to allow to duplicate lua_Number as sqword_t (and maybe qword_t) to have full 64-bit range of numbers,
	// but this will cause equality checking errors (different types, same real value) and will require some code to mitigate
	// !!! also usual floating-point equality checking problems!
	sqword_t,
	lua_Number,
	std::string,
	bool,
	LuaTable
>
{
public:
	using base = std::variant<_Nil, sqword_t, lua_Number, std::string, bool, LuaTable>;
	using base::variant;
	using base::operator=;

	bool isNil() const;
	bool isNumber() const; // both for floating-point and integer
	bool isString() const;
	bool isBool() const;
	bool isTable() const;

	// these methods throw if type is not correct

	// throws if type is not floating-point, even if it's an integer and can be converted to it
	lua_Number& getNumber();
	// throws if type is not floating-point, even if it's an integer and can be converted to it
	const lua_Number& getNumber() const;
	// throws if type is not integer, even if it's integer in floating-point form and can be converted to it
	sqword_t& getInteger();
	// throws if type is not integer, even if it's integer in floating-point form and can be converted to it
	const sqword_t& getInteger() const;

	// converts the value internally to floating-point if needed
	lua_Number& getNumberAny();
	// this one is different: it doesn't return const-reference, because I couldn't convert integer to number in const-qualified variant, and it's not needed anyways, because you can't modify const object, so no need for reference. Also, the number is a primitive type, and thus cheap to copy
	lua_Number getNumberAny() const;
	std::string& getString();
	const std::string& getString() const;
	bool& getBool();
	const bool& getBool() const;
	LuaTable& getTable();
	const LuaTable& getTable() const;

	// these methods return default value (NOT reference) if type is not correct
	lua_Number getNumberOr(lua_Number alt) const;
	std::string getStringOr(std::string_view alt) const;
	bool getBoolOr(bool alt) const;
	LuaTable getTableOr(const LuaTable& alt) const;

	// these methods return pointer to value if type is correct, or nullptr otherwise
	_Nil* getNilIf();
	const _Nil* getNilIf() const;
	sqword_t* getIntegerIf();
	const sqword_t* getIntegerIf() const;
	lua_Number* getNumberIf();
	const lua_Number* getNumberIf() const;
	lua_Number* getNumberAnyIf();
	// NOTE: this DOESN'T work if number is integer
	const lua_Number* getNumberAnyIf() const;
	std::string* getStringIf();
	const std::string* getStringIf() const;
	bool* getBoolIf();
	const bool* getBoolIf() const;
	LuaTable* getTableIf();
	const LuaTable* getTableIf() const;

	// returns rttr::variant with value converted to specified type, or if it's not specified, any matching type
	rttr::variant toRttrVariant(rttr::type type = rttr::type::get<void>()) const;

	// returns true if this value is of specified type (LUA_TFUNCTION, LUA_TUSERDATA, etc.)
	bool isType(int type) const;

	// returns type of this value (LUA_TFUNCTION, LUA_TUSERDATA, etc.)
	int getType() const;

	// returns string representation of type (nil, number, string, etc.)
	std::string typeToString() const;
	// returns string representation of value
	std::string valueToString() const;
	// returns string representation of value and type
	std::string toString() const;

	// pushes value to lua stack
	void pushToLuaStack(lua_State* L) const;
	// pushes value to lua stack using provided wrapper
	void pushToLuaStack(LuaWrapper& w) const;

	// these methods try to convert value to specified type, set provided boolean variable to true if successful, otherwise false and object is not modified
	lua_Number toNumber(bool& ok) const;
	std::string toString(bool& ok) const;
	bool toBool(bool& ok) const;

	// same as above, but converts the variant in-place, returning boolean indicating success
	bool toNumberInplace();
	bool toStringInplace();
	bool toBoolInplace();

	explicit LuaValue(const rttr::variant& var);
	// constructor from lua stack
	LuaValue(lua_State* L, int index);
};

namespace lua::utils
{
	// this function just forwards the function call to LuaValue object, it exists for compatiblity reasons
	std::string convertLuaTypeInCppTypeToString(const LuaTypeInCpp& type);
	// this function just forwards the function call to LuaValue object, it exists for compatiblity reasons
	std::string convertLuaTypeInCppToString(const LuaTypeInCpp& type);
	void luaTypeInCppToStack(const LuaTypeInCpp& val, LuaWrapper& wrapper);



	/// <summary>
	/// Converts a Lua stack index to a corresponding C++ LuaTypeInCpp value.
	/// </summary>
	/// <param name="L">The Lua state pointer.</param>
	/// <param name="stackIndex">The index of the stack to convert.</param>
	/// <returns>
	/// The corresponding C++ LuaTypeInCpp value based on the Lua type at the specified stack index.
	/// </returns>
	LuaTypeInCpp convertStackIndexToLuaTypeInCpp(lua_State* L, int stackIndex);
}

namespace std
{
	// text formatters for nil and LuaValue
	template<>
	struct formatter<_Nil> : formatter<string_view>
	{
		template<typename FormatContext>
		auto format(const _Nil& nil, FormatContext& ctx) const
		{
			return formatter<string_view>::format("<nil>", ctx);
		}
	};

	template<>
	struct formatter<LuaTypeInCpp> : formatter<string_view>
	{
		template<typename FormatContext>
		auto format(const LuaTypeInCpp& type, FormatContext& ctx) const
		{
			return format_to(ctx.out(), "{}", type.toString());
		}
	};
}