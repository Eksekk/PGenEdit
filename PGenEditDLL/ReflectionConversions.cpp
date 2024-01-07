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

// returns pointer to real object (not shared_ptr) represented by value at given stack index
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

bool ReflectionConversions::convertVariantToLuaTypeOnStack(lua_State* L, const rttr::variant& val)
{
	LuaWrapper w(L);
	type typ = val.get_type();
	type_id typeId = typ.get_id();
	if (typ.is_pointer())
	{
		type raw = typ.get_raw_type();
		// pointer to class type will be converted to instance of class (as a table with ptr)
		// pointer to primitive type will be converted to that type
		// pointer to void will be converted to number

		if (val.is_type<void*>())
		{
			w.pushnumber((dword_t)val.get_value<void*>());
		}
		else if (val.is_type<std::nullptr_t>())
		{
			w.pushnumber(0);
		}
		else if (raw.is_class())
		{
			std::string rawTypeName = typ.get_raw_type().get_name().to_string();
			w.getPath("pgenedit.cpp.class." + rawTypeName);
			if (!lua_istable(L, -1))
			{
				luaError("Couldn't get class table for class '{}'", rawTypeName);
				return false;
			}
			w.getfield(-1, "?existingObjectAt");
			if (!lua_isfunction(L, -1))
			{
				luaError("Couldn't get function '?existingObjectAt' from class table for class '{}'", rawTypeName);
				return false;
			}
			w.replace(-2); // replace class table with function
			wxASSERT_MSG(val.convert<void*>() && val.convert<dword_t>(), std::format("Can't convert pointer to class to number. Is type '{}' not registered?", raw));
			w.pushnumber(val.get_value<dword_t>());
			if (w.pcall(1, 1, 0) != LUA_OK)
			{
				luaError("Couldn't call function '?existingObjectAt' from class table for class '{}': '{}'", rawTypeName, w.tostring(-1));
				return false;
			}
			// leave result on stack
			return true;
		}
		else
		{
			luaError("Unsupported pointer type '{}' in convertVariantToLuaTypeOnStack", typ.get_name().to_string());
			return false;
		}
	}
	if (val.is_sequential_container())
	{
		// create table from sequential container
		rttr::variant_sequential_view seqView = val.create_sequential_view();
		// IMPORTANT: values are stored inside reference_wrapper, so we have to get wrapped type
		rttr::type wrappedType = seqView.get_value_type();
		LuaTable t;
		for (int i = 0; auto & value : seqView)
		{
			t[i++] = convertVariantToLuaTypeInCpp(value.extract_wrapped_value());
		}
		t.pushToLuaStack(L);
	}
	else if (val.is_associative_container())
	{
		// create table from associative container
		rttr::type wrappedType = val.get_type().get_wrapped_type();
		rttr::variant_associative_view assocView = val.create_associative_view();
		rttr::type wrappedKeyType = assocView.get_key_type();
		rttr::type wrappedValueType = assocView.get_value_type();
		LuaTable t;
		for (auto&& [key, value] : assocView)
		{
			t[convertVariantToLuaTypeInCpp(key.extract_wrapped_value())] = convertVariantToLuaTypeInCpp(value.extract_wrapped_value());
		}
		t.pushToLuaStack(L);
	}
	else if (typeId == TYPE_ID_NIL)
	{
		w.pushnil();
	}
	else if (typeId == TYPE_ID_LUA_TABLE)
	{
		if (!val.is_type<LuaTable>())
		{
			throw std::runtime_error("Can't convert lua table to lua table, because it's not of type LuaTable");
		}
		val.get_value<LuaTable>().pushToLuaStack(L);
	}
	else if (typeId == TYPE_ID_BOOL)
	{
		w.pushboolean(val.get_value<bool>());
	}
	else if (typeId == TYPE_ID_CHAR)
	{
		w.pushnumber(static_cast<lua_Number>(val.get_value<char>()));
	}
	else if (typeId == TYPE_ID_UNSIGNED_CHAR)
	{
		w.pushnumber(static_cast<lua_Number>(val.get_value<unsigned char>()));
	}
	else if (typeId == TYPE_ID_SHORT)
	{
		w.pushnumber(static_cast<lua_Number>(val.get_value<short>()));
	}
	else if (typeId == TYPE_ID_UNSIGNED_SHORT)
	{
		w.pushnumber(static_cast<lua_Number>(val.get_value<unsigned short>()));
	}
	else if (typeId == TYPE_ID_INT)
	{
		w.pushnumber(static_cast<lua_Number>(val.get_value<int>()));
	}
	else if (typeId == TYPE_ID_UNSIGNED_INT)
	{
		w.pushnumber(static_cast<lua_Number>(val.get_value<unsigned int>()));
	}
	else if (typeId == TYPE_ID_LONG)
	{
		w.pushnumber(static_cast<lua_Number>(val.get_value<long>()));
	}
	else if (typeId == TYPE_ID_UNSIGNED_LONG)
	{
		w.pushnumber(static_cast<lua_Number>(val.get_value<unsigned long>()));
	}
	else if (typeId == TYPE_ID_LONG_LONG)
	{
		w.pushnumber(static_cast<lua_Number>(val.get_value<long long>()));
	}
	else if (typeId == TYPE_ID_UNSIGNED_LONG_LONG)
	{
		w.pushnumber(static_cast<lua_Number>(val.get_value<unsigned long long>()));
	}
	else if (typeId == TYPE_ID_FLOAT)
	{
		w.pushnumber(static_cast<lua_Number>(val.get_value<float>()));
	}
	else if (typeId == TYPE_ID_DOUBLE)
	{
		w.pushnumber(static_cast<lua_Number>(val.get_value<double>()));
	}
	else if (typeId == TYPE_ID_LONG_DOUBLE)
	{
		w.pushnumber(static_cast<lua_Number>(val.get_value<long double>()));
	}
	else if (typeId == TYPE_ID_STRING)
	{
		w.pushstring(val.get_value<std::string>());
	}
	else if (typeId == TYPE_ID_STRING_VIEW)
	{
		w.pushstring(std::string(val.get_value<std::string_view>()));
	}
	else if (typeId == TYPE_ID_VOID)
	{
		// explicit lack of return value, ignore
	}
	else if (typeId == TYPE_ID_VOID_PTR)
	{
		w.pushlightuserdata(val.get_value<void*>());
	}
	else
	{
		luaError("Unsupported type '{}' in convertVariantToLuaTypeOnStack", val.get_type().get_name().to_string());
		return false;
		//wxFAIL_MSG(wxString::Format("Can't convert type '%s' to matching lua type", tbl.get_type().get_name().data()));
	}
	return true;
}
