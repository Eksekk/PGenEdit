#pragma once
#include "main.h"

class LuaValue;
using LuaTypeInCpp = LuaValue;

using LuaValuePair = std::pair<LuaTypeInCpp, LuaTypeInCpp>;

using LuaTableValues = std::map<LuaTypeInCpp, LuaTypeInCpp>;
using LuaTableValuesWithArray = std::set<std::variant<LuaTypeInCpp, LuaValuePair>>; // it's important that this is not unordered, because I want to iterate array part arguments in order
using LuaTableValuesUPtr = std::unique_ptr<LuaTableValues>;
struct LuaTable // TODO: storing array part and hashed part separately - will improve table to lua conversion time, but will require tricky code
{
	// only values as unique_ptr doesn't work
	// values and table as unique_ptrs don't work with std::unordered_map
	// values and table as unique_ptrs work with std::map
	LuaTableValues values;
	// !!!!! IMPORTANT
	// when C function registered in lua is called, it receives lua_State* as first argument, and it's apparently state with entirely different stack
	// which means, pushes to global "Lua" state won't change the state that the function received, so it's as if nothing was pushed
	// solution: always take state as argument
	// not using default argument here with value of "Lua" global, because I would obviously forget to pass the correct state when using inside C functions registered in lua
	void pushToLuaStack(lua_State* L) const; // converts this structure into lua table on top of the stack
	// TODO: a version updating lua table at specified index
	// converts table at specified stack index into this value
	static LuaTable fromLuaTable(lua_State* L, int index = -1);

	using iterator = typename LuaTableValues::iterator;
	using const_iterator = typename LuaTableValues::const_iterator;

	LuaTableValues::iterator begin();
	LuaTableValues::iterator end();
	LuaTableValues::const_iterator begin() const;
	LuaTableValues::const_iterator end() const;
	LuaTableValues::const_iterator cbegin() const;
	LuaTableValues::const_iterator cend() const;
	LuaTable(const LuaTableValues& values);
	LuaTable(LuaTableValues&& values);
	LuaTable(lua_State* L, int index);
	// creates table from lua code, like "{a = 1, b = 2}"
	LuaTable(lua_State* L, const std::string& luaCode);

	// generic factory function from any contiguous range (vector, array, etc.)
	// this can't be constructor, because otherwise it would be preferred for initializer_list constructors like in LuaTests.cpp
	template<std::ranges::contiguous_range Range>
	static LuaTable fromRange(Range&& range, int firstOutputIndex = 1)
	{
		LuaTable t;
		for (int i = firstOutputIndex; auto && val : range)
		{
			t[i++] = val;
		}
		return t;
	}

	// unfortunately, can't make this a constructor, because it will be ambiguous with LuaTableValues when passed initializer_list
	// also accepts normal key-value pairs in addition to individual array elements
	static LuaTable constructFromValuesWithArray(LuaTableValuesWithArray&& values);
	// also accepts normal key-value pairs in addition to individual array elements
	static LuaTable constructFromValuesWithArray(const LuaTableValuesWithArray& values);

	// 
	static LuaTable fromLuaCode(lua_State* L, const std::string& code);
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
	// version of "at" that returns reference to table value, throwing error if it's not a table
	LuaTable& att(const LuaTypeInCpp& type);
	const LuaTable& att(const LuaTypeInCpp& type) const;
	// version of "att" that creates table if it doesn't exist
	LuaTable& attc(const LuaTypeInCpp& type);
	LuaTypeInCpp& at(const LuaTypeInCpp& type);
	bool contains(const LuaTypeInCpp& type) const;
	// gets consecutive integer keys' values as a vector
	// stops on first missing index
	// firstIndex is first numeric index to use
	std::vector<LuaTypeInCpp> getArrayPart(int firstIndex = 1) const;

	// pushes values in array part to lua stack, in order, firstIndex is first index of array part to use
	void pushArrayPartToLuaStack(lua_State* L, int firstIndex = 1) const;
	std::string dump(int depth = -1) const;
private:
	static void luaConvertTypeCommon(lua_State* L, LuaTypeInCpp& val, int stack);
	static void tryToIntegerRef(LuaTypeInCpp& type);
	static LuaTypeInCpp tryToIntegerRet(const LuaTypeInCpp& type);
	static bool canBeInteger(const LuaTypeInCpp& type);
	static LuaTableValues tryToIntegerFull(const LuaTableValues& values);
	static LuaTableValues tryToIntegerFull(LuaTableValues&& values);

	RTTR_REGISTRATION_FRIEND
};

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

// creates a lua table from lua code string as string literal, uses global "Lua" state to run code
LuaTable operator ""_luaTable(const char* text, size_t len);

namespace std
{
    template<>
    struct formatter<LuaTable> : formatter<string_view>
    {
        template<typename FormatContext>
        auto format(const LuaTable& table, FormatContext& ctx) const
        {
            return formatter<string_view>::format(table.dump(), ctx);
        }
    };
}

// this can't be inline, because LuaTypeInCpp is incomplete type at this point
bool operator==(const LuaValuePair& lhs, const LuaValuePair& rhs);
bool operator==(const LuaTable& lhs, const LuaTable& rhs);
bool operator<(const LuaTable& lhs, const LuaTable& rhs);

