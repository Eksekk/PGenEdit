#include "pch.h"
#include "ReflectionConversions.h"

using type = rttr::type;
using type_id = type::type_id;
const type_id ReflectionConversions::TYPE_ID_CHAR = type::get<char>().get_id();
const type_id ReflectionConversions::TYPE_ID_UNSIGNED_CHAR = type::get<unsigned char>().get_id();
const type_id ReflectionConversions::TYPE_ID_SHORT = type::get<short>().get_id();
const type_id ReflectionConversions::TYPE_ID_UNSIGNED_SHORT = type::get<unsigned short>().get_id();
const type_id ReflectionConversions::TYPE_ID_INT = type::get<int>().get_id();
const type_id ReflectionConversions::TYPE_ID_UNSIGNED_INT = type::get<unsigned int>().get_id();
const type_id ReflectionConversions::TYPE_ID_LONG = type::get<long>().get_id();
const type_id ReflectionConversions::TYPE_ID_UNSIGNED_LONG = type::get<unsigned long>().get_id();
const type_id ReflectionConversions::TYPE_ID_LONG_LONG = type::get<long long>().get_id();
const type_id ReflectionConversions::TYPE_ID_UNSIGNED_LONG_LONG = type::get<unsigned long long>().get_id();
const type_id ReflectionConversions::TYPE_ID_FLOAT = type::get<float>().get_id();
const type_id ReflectionConversions::TYPE_ID_DOUBLE = type::get<double>().get_id();
const type_id ReflectionConversions::TYPE_ID_LONG_DOUBLE = type::get<long double>().get_id();
const type_id ReflectionConversions::TYPE_ID_BOOL = type::get<bool>().get_id();
const type_id ReflectionConversions::TYPE_ID_STRING_VIEW = type::get<std::string_view>().get_id();
const type_id ReflectionConversions::TYPE_ID_STRING = type::get<std::string>().get_id();
const type_id ReflectionConversions::TYPE_ID_VOID = type::get<void>().get_id();
const type_id ReflectionConversions::TYPE_ID_VOID_PTR = type::get<void*>().get_id();
const type_id ReflectionConversions::TYPE_ID_LUA_TABLE = type::get<LuaTable>().get_id();
const type_id ReflectionConversions::TYPE_ID_NIL = type::get<_Nil>().get_id();

const std::vector<type_id> ReflectionConversions::TYPE_IDS_INTEGERS{ TYPE_ID_CHAR, TYPE_ID_UNSIGNED_CHAR, TYPE_ID_SHORT, TYPE_ID_UNSIGNED_SHORT, TYPE_ID_INT, TYPE_ID_UNSIGNED_INT, TYPE_ID_LONG, TYPE_ID_UNSIGNED_LONG, TYPE_ID_LONG_LONG, TYPE_ID_UNSIGNED_LONG_LONG };
const std::vector<type_id> ReflectionConversions::TYPE_IDS_FLOATS{ TYPE_ID_FLOAT, TYPE_ID_DOUBLE, TYPE_ID_LONG_DOUBLE };
const std::vector<type_id> ReflectionConversions::TYPE_IDS_STRINGS{ TYPE_ID_STRING_VIEW, TYPE_ID_STRING };
const std::vector<type_id> ReflectionConversions::TYPE_IDS_NUMBERS{ compileTimeMergeVectors({TYPE_IDS_INTEGERS, TYPE_IDS_FLOATS }) };
// this one doesn't use "pointer" vector to merge, because strings already contain char pointers
const std::vector<type_id> ReflectionConversions::TYPE_IDS_ALL_TYPES{ compileTimeMergeVectors({TYPE_IDS_NUMBERS, TYPE_IDS_STRINGS, {TYPE_ID_BOOL, TYPE_ID_VOID_PTR, TYPE_ID_NIL, TYPE_ID_VOID} }) };

// aliases for lua utility functions
using ::lua::utils::getLuaTableMetafieldOrError;
using ::lua::utils::getLuaTypeOrError;
using ::lua::utils::luaError;
using ::lua::utils::luaExpectStackSize;
using ::lua::utils::luaTableHasMetafield;
using ::lua::utils::isLuaType;



// so, it seems the only way to handle creating new objects and destroying them correctly, is using std::shared_ptr<>, or using everywhere policy of raw ptr in constructor
// for userdata, we can probably reinterpret_cast the userdata into the variant (which will contain shared_ptr) and extract raw pointer from it EVERY TIME we want to use it
// for tables, we would need to store raw pointer, because creating shared_ptr to existing object is possible, but would destroy the original object when variant is destroyed

// handles both userdata and table
// userdata contains variant, which itself contains shared_ptr to object
// table contains raw pointer to object
void* luaGetObjectPtr(lua_State* L, int index)
{
	void* ptr = nullptr;
	if (lua_isuserdata(L, index))
	{
		ptr = lua_touserdata(L, index);
		if (!ptr)
		{
			luaError("Couldn't get object - userdata is null");
		}
		rttr::variant* sharedPtrVar = reinterpret_cast<rttr::variant*>(ptr); // contains shared_ptr
		rttr::variant rawPtrVar = sharedPtrVar->extract_wrapped_value(); // contains raw pointer
		if (!rawPtrVar.convert(rttr::type::get<void*>()) || !rawPtrVar.is_type<void*>())
		{
			luaError("Couldn't get object - variant obtained from userdata can't be converted to pointer");
			return nullptr;
		}
		return rawPtrVar.get_value<void*>();
		//className = getLuaTableMetafieldOrError<std::string>(index, "className");
	}
	else if (lua_istable(L, index))
	{
		lua_getfield(L, index, "?ptr"); // class object table field
		if (!lua_isnumber(L, -1))
		{
			luaError("Couldn't get object - table doesn't have a pointer");
			lua_pop(L, 1);
			return nullptr;
		}
		ptr = (void*)(dword_t)lua_tonumber(L, -1);
		lua_pop(L, 1);
		return ptr;
		//className = getLuaTableMetafieldOrError<std::string>(index, "className");
	}
	else
	{
		luaError("Couldn't get object - first argument is neither userdata nor table");
		return nullptr;
	}
}
