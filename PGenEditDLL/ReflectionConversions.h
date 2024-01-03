#pragma once
#include "LuaWrapper.h"
#include "Utility.h"
#include "LuaFunctions.h"

// aliases for lua utility functions
namespace // anonymous namespace makes it so that these aliases are only visible in this file
{
	using ::lua::utils::getLuaTableMetafieldOrError;
	using ::lua::utils::getLuaTypeOrError;
	using ::lua::utils::isLuaType;
	using ::lua::utils::luaError;
	using ::lua::utils::luaAssert;
	using ::lua::utils::luaExpectStackSize;
	using ::lua::utils::luaTableHasMetafield;
}

void* luaGetObjectPtr(lua_State* L, int index);

// handles conversions of all types for reflection, whether at cpp/lua boundary or within cpp
class ReflectionConversions
{
public:
	using type = rttr::type;
	using type_id = type::type_id;
	static const type_id TYPE_ID_CHAR;
	static const type_id TYPE_ID_UNSIGNED_CHAR;
	static const type_id TYPE_ID_SHORT;
	static const type_id TYPE_ID_UNSIGNED_SHORT;
	static const type_id TYPE_ID_INT;
	static const type_id TYPE_ID_UNSIGNED_INT;
	static const type_id TYPE_ID_LONG;
	static const type_id TYPE_ID_UNSIGNED_LONG;
	static const type_id TYPE_ID_LONG_LONG;
	static const type_id TYPE_ID_UNSIGNED_LONG_LONG;
	static const type_id TYPE_ID_FLOAT;
	static const type_id TYPE_ID_DOUBLE;
	static const type_id TYPE_ID_LONG_DOUBLE;
	static const type_id TYPE_ID_BOOL;
	static const type_id TYPE_ID_STRING;
	static const type_id TYPE_ID_STRING_VIEW;
	static const type_id TYPE_ID_VOID;
	static const type_id TYPE_ID_VOID_PTR;
	static const type_id TYPE_ID_LUA_TABLE;
	static const type_id TYPE_ID_NIL;

	// combinations of individual types
	static const std::vector<type_id> TYPE_IDS_INTEGERS; // excludes floating-point types
	static const std::vector<type_id> TYPE_IDS_NUMBERS; // includes floating-point types
	static const std::vector<type_id> TYPE_IDS_FLOATS;
	static const std::vector<type_id> TYPE_IDS_STRINGS;
	static const std::vector<type_id> TYPE_IDS_POINTERS;
	static const std::vector<type_id> TYPE_IDS_ALL_TYPES;

	// FIXME: make a method checking compatibility of two types, so that we can check if we can convert lua type to C++ type, which is parameter of the method
	// if any parameter doesn't match (remember about cv!), we can't call the method with this overload
	// remember about special handling for types in lua, which natively are not in C++ (like nil, table, function, userdata, thread)
	// and remember about integer/float distinction callableIndexPair in lua -> cpp conversion

	// lua can be converted to cpp like this [these brackets mean the conversion needs to be explicitly requested]:
	// number -> char, short, int, long, long long, float, double, long double, unsigned char, unsigned short, unsigned int, unsigned long, unsigned long long, [bool]
	// string -> std::string, std::string_view, char*, [bool]
	// boolean -> bool, [all integer formats like int]
	// table -> LuaTable, [bool]
	// nil -> _Nil, [bool]
	// function -> none
	// thread -> none
	// userdata -> void*
	// lightuserdata -> void*
	// any lua type representable in cpp -> LuaTypeInCpp, rttr::variant

	static bool isAnyContainerOrWrapper(const rttr::variant& var)
	{
		return var.is_sequential_container() || var.is_associative_container() || var.get_type().is_wrapper();
	}

	// if a variant designates a container or wrapper, returns example value to have instance of value type to modify, otherwise returns invalid variant
	static rttr::variant getNestedContainerExampleValue(rttr::variant& var)
	{
		if (isAnyContainerOrWrapper(var))
		{
			if (var.is_sequential_container())
			{
				auto view = var.create_sequential_view();
				if (view.get_size() == 0)
				{
					if (view.is_dynamic())
					{
						view.set_size(1);
					}
					else
					{
						wxFAIL_MSG("Static sequential container with size 0");
					}
				}
				return view.get_value(0);
			}
			else if (var.is_associative_container())
			{
				auto view = var.create_associative_view();
				if (view.get_size() == 0)
				{
					wxASSERT_MSG(view.insert(rttr::variant(), rttr::variant()).second, "Failed to insert empty key-value pair into associative container");
				}
				return (*view.begin()).second;
			}
			else if (var.get_type().is_wrapper())
			{
				return var.extract_wrapped_value();
			}
			else
			{
				wxFAIL_MSG("Unknown container type");
				return rttr::variant();
			}
		}
		else
		{
			return rttr::variant();
		}
	}


	// property, method, constructor can have metadata, which will allow to create new, empty container of desired type
	// type metadata won't work, because would need to register a ton of types, and I don't want to do that
	// method and constructor require index in addition to type, so I can use metadata

	// captures all information needed to properly create a parameter of method/field of class, or nested type inside a container
	// for constructors and methods it's pair of constructor/method and index of parameter, so you can get creation function from metadata,
	// for properties it's just property, also has function in metadata,
	// for nested containers it's a dummy instance (variant) of the container to use (fill with needed data/clear/etc.),
	// and for simple types nested in containers it's just the type
	using RttrClassMemberVariant = std::variant<rttr::variant, rttr::type, rttr::property, std::pair<rttr::constructor, size_t>, std::pair<rttr::method, size_t>>;
private:

	static rttr::variant createContainerFromClassMemberVariant(const RttrClassMemberVariant& member)
	{
		if (const rttr::variant* var = std::get_if<rttr::variant>(&member))
		{
			return *var;
		}
		else if (const rttr::type* typ = std::get_if<rttr::type>(&member))
		{
			return rttr::variant(typ->create());
		}
		else if (const rttr::variant* var = std::get_if<rttr::variant>(&member))
		{
			rttr::variant ret = *var; // make a copy
			if (ret.is_sequential_container() && ret.create_sequential_view().is_dynamic())
			{
				ret.create_sequential_view().set_size(0);
			}
			else if (ret.is_associative_container())
			{
				ret.create_associative_view().clear();
			}
			return ret;
		}
		else
		{
			rttr::variant f = getCreationFunction(member);
			wxASSERT_MSG(f.is_type<CreateContainerFunc>(), std::format("Member of type '{}' doesn't have metadata with creation function", getType(member)));
			try
			{
				rttr::variant var = f.get_value<CreateContainerFunc>()();
				wxASSERT_MSG(var.is_valid(), std::format("Creation function for member of type '{}' returned invalid variant", getType(member)));
				wxASSERT_MSG(var.is_sequential_container() || var.is_associative_container(), std::format("Creation function for member of type '{}' returned variant of type '{}', which is neither sequential nor associative container", getType(member), var.get_type()));
				wxASSERT_MSG(var.get_type() == getType(member), std::format("Creation function for member of type '{}' returned variant of type '{}'", getType(member), var.get_type()));
				return var;
			}
			catch (const std::exception& ex)
			{
				wxFAIL_MSG(std::format("Exception '{}' thrown when creating container for member of type '{}'", ex.what(), getType(member)));
				return rttr::variant();
			}
		}
	}

	/// <summary>
/// Tries to convert a number to the specified type.
/// </summary>
/// <param name="val">The value to be converted.</param>
/// <param name="typeId">The type to convert the value to.</param>
/// <param name="allowCrossTypeConversions">Flag to allow cross type conversions.</param>
/// <returns>
/// A variant containing the converted value, or an empty variant if conversion fails.
/// </returns>
	template<typename T>
	static rttr::variant tryConvertNumberToType(T val, type_id typeId, bool allowCrossTypeConversions = false)
	{
		if (typeId == TYPE_ID_CHAR)
		{
			return static_cast<char>(val);
		}
		else if (typeId == TYPE_ID_UNSIGNED_CHAR)
		{
			return static_cast<unsigned char>(val);
		}
		else if (typeId == TYPE_ID_SHORT)
		{
			return static_cast<short>(val);
		}
		else if (typeId == TYPE_ID_UNSIGNED_SHORT)
		{
			return static_cast<unsigned short>(val);
		}
		else if (typeId == TYPE_ID_INT)
		{
			return static_cast<int>(val);
		}
		else if (typeId == TYPE_ID_UNSIGNED_INT)
		{
			return static_cast<unsigned int>(val);
		}
		else if (typeId == TYPE_ID_LONG)
		{
			return static_cast<long>(val);
		}
		else if (typeId == TYPE_ID_UNSIGNED_LONG)
		{
			return static_cast<unsigned long>(val);
		}
		else if (typeId == TYPE_ID_LONG_LONG)
		{
			return static_cast<long long>(val);
		}
		else if (typeId == TYPE_ID_UNSIGNED_LONG_LONG)
		{
			return static_cast<unsigned long long>(val);
		}
		else if (typeId == TYPE_ID_FLOAT)
		{
			return static_cast<float>(val);
		}
		else if (typeId == TYPE_ID_DOUBLE)
		{
			return static_cast<double>(val);
		}
		else if (typeId == TYPE_ID_LONG_DOUBLE)
		{
			return static_cast<long double>(val);
		}
		else if (allowCrossTypeConversions)
		{
			if (typeId == TYPE_ID_BOOL)
			{
				return static_cast<bool>((long long)val); // second cast is for doubles, which can't be cast to bool directly
			}
			// strings
			else if (typeId == TYPE_ID_STRING)
			{
				return std::to_string(val);
			}
			else if (typeId == TYPE_ID_STRING_VIEW)
			{
				return std::string_view(std::to_string(val));
			}
		}
		return rttr::variant();
	}

	// gets type of property, method parameter or constructorm parameter
	// takes into account that constructor might be wrapped
	// receives also index of parameter in case of method or constructor (pair)
	static rttr::type getType(const RttrClassMemberVariant& var)
	{
		if (const rttr::type* typ = std::get_if<rttr::type>(&var))
		{
			return *typ;
		}
		else if (const rttr::property* prop = std::get_if<rttr::property>(&var))
		{
			return prop->get_type();
		}
		else if (const std::pair<rttr::constructor, size_t>* constr = std::get_if<std::pair<rttr::constructor, size_t>>(&var))
		{
			auto [ctor, _] = util::rttr::getMaybeWrappedConstructor(constr->first);
			return util::misc::getNthRangeElement(ctor.get_parameter_infos(), constr->second).get_type();
		}
		else if (const std::pair<rttr::method, size_t>* method = std::get_if<std::pair<rttr::method, size_t>>(&var))
		{
			return util::misc::getNthRangeElement(method->first.get_parameter_infos(), method->second).get_type();
		}
		else
		{
			wxFAIL_MSG("Unknown type of std::variant");
			return rttr::type::get<void*>(); // dummy return
		}
	}

	static rttr::variant getCreationFunction(const RttrClassMemberVariant& var)
	{
		using FuncVector = std::vector<CreateContainerFunc>;
		if (const rttr::type* typ = std::get_if<rttr::type>(&var))
		{
			wxFAIL_MSG("Creating container from type is not supported, because it would require registering (probably manually) all types that will be used as containers. Pass a property, method, constructor, or container instance instead.");
			return rttr::variant();
		}
		else if (const rttr::property* prop = std::get_if<rttr::property>(&var))
		{
			rttr::variant m = prop->get_metadata(g_CONTAINER_CREATION_FUNC_METADATA_NAME);
			wxASSERT_MSG(m.is_type<FuncVector>(), std::format("Property '{}' of type '{}' doesn't have metadata with creation function", prop->get_name(), prop->get_type()));
			return m.get_value<FuncVector>().at(0);
		}
		else if (const std::pair<rttr::constructor, size_t>* constrPair = std::get_if<std::pair<rttr::constructor, size_t>>(&var))
		{
			auto [ctor, unwrapped] = util::rttr::getMaybeWrappedConstructor(constrPair->first);
			rttr::variant m = ctor.get_metadata(g_CONTAINER_CREATION_FUNC_METADATA_NAME);
			wxASSERT_MSG(m.is_type<FuncVector>(), std::format("Constructor '{}' of type '{}'{} doesn't have metadata with creation function", ctor.get_signature(), unwrapped ? " [unwrapped]" : "", ctor.get_declaring_type()));
			return m.get_value<FuncVector>().at(constrPair->second);
		}
		else if (const std::pair<rttr::method, size_t>* methodPair = std::get_if<std::pair<rttr::method, size_t>>(&var))
		{
			rttr::variant m = methodPair->first.get_metadata(g_CONTAINER_CREATION_FUNC_METADATA_NAME);
			wxASSERT_MSG(m.is_type<FuncVector>(), std::format("Method '{}' of type '{}' doesn't have metadata with creation function", methodPair->first.get_signature(), methodPair->first.get_declaring_type()));
			return m.get_value<FuncVector>().at(methodPair->second);
		}
		else
		{
			wxFAIL_MSG("Unknown type of std::variant");
			return rttr::variant(); // dummy return
		}
	};
public:
	// converts lua parameter from stack to given type (using RTTR type_id)
	// allowCrossTypeCategoryConversions allows to convert lua types to C++ types, which are not exactly matching, but are compatible (like number to boolean)
	static rttr::variant convertStackIndexToType(lua_State* L, int stackIndex, const RttrClassMemberVariant& classPropertyVariant, bool allowCrossTypeCategoryConversions = false)
	{
		LuaWrapper wrapper(L);

		rttr::type typ = getType(classPropertyVariant);
		rttr::type::type_id typeId = typ.get_id();
		stackIndex = wrapper.makeAbsoluteStackIndex(stackIndex);
		switch (lua_type(L, stackIndex))
		{
		case LUA_TNUMBER:
		{
			lua_Number num = lua_tonumber(L, stackIndex);
			return tryConvertNumberToType(num, typeId, allowCrossTypeCategoryConversions);
		}
		case LUA_TSTRING:
		{
			size_t s;
			const char* str = lua_tolstring(L, stackIndex, &s);
			if (existsInVector(TYPE_IDS_STRINGS, typeId))
			{
				if (typeId == TYPE_ID_STRING)
				{
					return std::string(str, s);
				}
				else if (typeId == TYPE_ID_STRING_VIEW)
				{
					return std::string_view(str, s);
				}
				else
				{
					return rttr::variant();
				}
			}
			else if (allowCrossTypeCategoryConversions && typeId == TYPE_ID_BOOL)
			{
				// TODO: decide how I would want string to bool conversion to work
				return static_cast<bool>(str);
			}
			break;
		}
		case LUA_TBOOLEAN:
			if (typeId == TYPE_ID_BOOL)
			{
				return static_cast<bool>(lua_toboolean(L, stackIndex));
			}
			else if (allowCrossTypeCategoryConversions && existsInVector(TYPE_IDS_INTEGERS, typeId))
			{
				int b = lua_toboolean(L, stackIndex);
				if (typeId == TYPE_ID_CHAR)
				{
					return static_cast<char>(b);
				}
				else if (typeId == TYPE_ID_UNSIGNED_CHAR)
				{
					return static_cast<unsigned char>(b);
				}
				else if (typeId == TYPE_ID_SHORT)
				{
					return static_cast<short>(b);
				}
				else if (typeId == TYPE_ID_UNSIGNED_SHORT)
				{
					return static_cast<unsigned short>(b);
				}
				else if (typeId == TYPE_ID_INT)
				{
					return static_cast<int>(b);
				}
				else if (typeId == TYPE_ID_UNSIGNED_INT)
				{
					return static_cast<unsigned int>(b);
				}
				else if (typeId == TYPE_ID_LONG)
				{
					return static_cast<long>(b);
				}
				else if (typeId == TYPE_ID_UNSIGNED_LONG)
				{
					return static_cast<unsigned long>(b);
				}
				else if (typeId == TYPE_ID_LONG_LONG)
				{
					return static_cast<long long>(b);
				}
				else if (typeId == TYPE_ID_UNSIGNED_LONG_LONG)
				{
					return static_cast<unsigned long long>(b);
				}
				else
				{
					return rttr::variant();
				}
			}
			else if (allowCrossTypeCategoryConversions && existsInVector(TYPE_IDS_FLOATS, typeId))
			{
				int b = lua_toboolean(L, stackIndex);
				if (typeId == TYPE_ID_FLOAT)
				{
					return static_cast<float>(b);
				}
				else if (typeId == TYPE_ID_DOUBLE)
				{
					return static_cast<double>(b);
				}
				else if (typeId == TYPE_ID_LONG_DOUBLE)
				{
					return static_cast<long double>(b);
				}
				else
				{
					return rttr::variant();
				}
			}
			else if (allowCrossTypeCategoryConversions && existsInVector(TYPE_IDS_STRINGS, typeId))
			{
				// TODO: decide how I would want bool to string conversion to work
				int b = lua_toboolean(L, stackIndex);
				if (typeId == TYPE_ID_STRING)
				{
					return std::string(b ? "true" : "false");
				}
				else if (typeId == TYPE_ID_STRING_VIEW)
				{
					return std::string_view(b ? "true" : "false");
				}
				else
				{
					return rttr::variant();
				}
			}
			break;
		case LUA_TTABLE:
			if (typeId == TYPE_ID_LUA_TABLE)
			{
				return LuaTable::fromLuaTable(L, stackIndex);
			}
			else if (typ.is_sequential_container())
			{
				rttr::variant var = createContainerFromClassMemberVariant(classPropertyVariant);

				rttr::variant_sequential_view seqView = var.create_sequential_view();
				rttr::type wrappedType = seqView.get_value_type();
				LuaTable t = LuaTable::fromLuaTable(L, stackIndex);
				auto arr = t.getArrayPart();
				seqView.set_size(arr.size());
				// std::vector<std::vector<int>>: how to create inner container? (it doesn't have metadata)
				// resize if needed and get any value, then pass it?
				for (int i = 0; const LuaTypeInCpp & val : arr)
				{
					rttr::variant var = convertLuaTypeInCppToVariant(val, wrappedType);
					seqView.set_value(i++, var);
				}
				return var;
			}
			else if (typ.is_associative_container())
			{
				// have to extract information from lua table into rttr::variant containing desired container
				auto var = createContainerFromClassMemberVariant(classPropertyVariant);
				rttr::variant_associative_view assocView = var.create_associative_view();
				rttr::type keyType = assocView.get_key_type();
				rttr::type valueType = assocView.get_value_type();
				rttr::type wrappedKeyType = keyType;
				rttr::type wrappedValueType = valueType;

				LuaTable t = LuaTable::fromLuaTable(L, stackIndex);
				for (auto&& [key, value] : t)
				{
					rttr::variant keyVar = convertLuaTypeInCppToVariant(key, wrappedKeyType);
					rttr::variant valueVar = convertLuaTypeInCppToVariant(value, wrappedValueType);
					assocView.insert(keyVar, valueVar);
				}
				return var;
			}
			else if (allowCrossTypeCategoryConversions && typeId == TYPE_ID_BOOL)
			{
				return true;
			}
			else
			{
				return rttr::variant();
			}
			break;
		case LUA_TNIL:
			if (typeId == TYPE_ID_NIL)
			{
				return Nil;
			}
			else if (allowCrossTypeCategoryConversions && typeId == TYPE_ID_BOOL)
			{
				return false;
			}
			else
			{
				return rttr::variant();
			}
			break;
		default:
			// TODO: return nil?
			wxFAIL_MSG(wxString::Format("Unsupported lua type '%s'", lua_typename(L, stackIndex)));
		}
		return rttr::variant();
	}

	// will be used to allow reflected methods to return values in lua
	// takes constituent types of LuaTypeInCpp and converts them to lua types
	template<typename T>
	static void convertValueToLuaTypeOnStack(lua_State* L, const T& val)
	{
		LuaWrapper wrapper(L);
		using BaseType = std::remove_cvref_t<T>;
		rttr::type typ = rttr::type::get<BaseType>();
		if constexpr (SAME(BaseType, _Nil))
		{
			wrapper.pushnil();
		}
		else if constexpr (SAME(BaseType, LuaTable))
		{
			val->pushToLuaStack();
		}
		else if constexpr (SAME(BaseType, bool))
		{
			wrapper.pushboolean(val);
		}
		else if constexpr (std::is_integral_v<BaseType> || std::is_floating_point_v<BaseType>) // number
		{
			wrapper.pushnumber(static_cast<lua_Number>(val));
		}
		else if constexpr (SAME(BaseType, std::string) || SAME(BaseType, std::string_view))
		{
			wrapper.pushstring(val.c_str());
		}
		else if constexpr (SAME(BaseType, char*))
		{
			wrapper.pushstring(val);
		}
		else if constexpr (SAME(BaseType, void*))
		{
			wrapper.pushlightuserdata(val);
		}
		else
		{
			showDeducedType(val);
			COMPILE_TIME_CONSTEXPR_IF_ERROR();
		}
	}

	static LuaTypeInCpp convertVariantToLuaTypeInCpp(const rttr::variant& var)
	{
		type_id typ = var.get_type().get_id();
		if (var.is_sequential_container())
		{
			// create table from sequential container
			rttr::variant_sequential_view seqView = var.create_sequential_view();
			LuaTable t;
			for (int i = 0; auto & value : seqView)
			{
				t[i++] = convertVariantToLuaTypeInCpp(value);
			}
			return t;
		}
		else if (var.is_associative_container())
		{
			// create table from associative container
			rttr::variant_associative_view assocView = var.create_associative_view();
			LuaTable t;
			for (auto&& [key, value] : assocView)
			{
				t[convertVariantToLuaTypeInCpp(key)] = convertVariantToLuaTypeInCpp(value);
			}
			return t;
		}
		else if (typ == TYPE_ID_NIL)
		{
			return Nil;
		}
		else if (typ == TYPE_ID_LUA_TABLE)
		{
			return var.get_value<LuaTable>();
		}
		else if (typ == TYPE_ID_BOOL)
		{
			return var.get_value<bool>();
		}
		else if (typ == TYPE_ID_CHAR)
		{
			return var.get_value<char>();
		}
		else if (typ == TYPE_ID_UNSIGNED_CHAR)
		{
			return var.get_value<unsigned char>();
		}
		else if (typ == TYPE_ID_SHORT)
		{
			return var.get_value<short>();
		}
		else if (typ == TYPE_ID_UNSIGNED_SHORT)
		{
			return var.get_value<unsigned short>();
		}
		else if (typ == TYPE_ID_INT)
		{
			return var.get_value<int>();
		}
		else if (typ == TYPE_ID_UNSIGNED_INT)
		{
			return var.get_value<unsigned int>();
		}
		else if (typ == TYPE_ID_LONG)
		{
			return var.get_value<long>();
		}
		else if (typ == TYPE_ID_UNSIGNED_LONG)
		{
			return var.get_value<unsigned long>();
		}
		else if (typ == TYPE_ID_LONG_LONG)
		{
			return var.get_value<long long>();
		}
		else if (typ == TYPE_ID_UNSIGNED_LONG_LONG)
		{
			return static_cast<sqword_t>(var.get_value<unsigned long long>());
		}
		else if (typ == TYPE_ID_FLOAT)
		{
			return var.get_value<float>();
		}
		else if (typ == TYPE_ID_DOUBLE)
		{
			return var.get_value<double>();
		}
		else if (typ == TYPE_ID_LONG_DOUBLE)
		{
			return static_cast<double>(var.get_value<long double>());
		}
		else if (typ == TYPE_ID_STRING)
		{
			return var.get_value<std::string>();
		}
		else if (typ == TYPE_ID_STRING_VIEW)
		{
			return (std::string)var.get_value<std::string_view>();
		}
		else if (typ == TYPE_ID_VOID_PTR)
		{
			return (dword_t)var.get_value<void*>();
		}
		else
		{
			luaError("Unsupported type '{}' in convertVariantToLuaTypeInCpp", var.get_type().get_name().to_string());
			return 0; // dummy return
		}
	}

	static rttr::variant convertLuaTypeInCppToVariant(const LuaTypeInCpp& var, const RttrClassMemberVariant& member, bool allowCrossTypeConversions = false)
	{
		type typ = getType(member);
		type_id typeId = typ.get_id();
		// let's assume integers can be converted to floats and vice versa, even if allowCrossTypeConversions is false
		if (const sqword_t* val = std::get_if<sqword_t>(&var))
		{
			return tryConvertNumberToType(*val, typeId, allowCrossTypeConversions);
		}
		else if (const lua_Number* val = std::get_if<lua_Number>(&var))
		{
			return tryConvertNumberToType(*val, typeId, allowCrossTypeConversions);
		}
		else if (const std::string* val = std::get_if<std::string>(&var))
		{
			if (typeId == TYPE_ID_STRING)
			{
				return *val;
			}
			else if (typeId == TYPE_ID_STRING_VIEW)
			{
				return std::string_view(*val);
			}
			else if (allowCrossTypeConversions)
			{
				if (typeId == TYPE_ID_BOOL)
				{
					return !val->empty();
				}

				try
				{
					return tryConvertNumberToType(std::stod(*val), typeId, allowCrossTypeConversions);
				}
				catch (const std::exception&)
				{
					// ignore
				}

				try
				{
					return tryConvertNumberToType(std::stoll(*val), typeId, allowCrossTypeConversions);
				}
				catch (const std::exception&)
				{
					// ignore
				}
			}
		}
		else if (const bool* val = std::get_if<bool>(&var))
		{
			if (typeId == TYPE_ID_BOOL)
			{
				return *val;
			}
			else if (allowCrossTypeConversions)
			{
				if (typeId == TYPE_ID_CHAR)
				{
					return static_cast<char>(*val);
				}
				else if (typeId == TYPE_ID_UNSIGNED_CHAR)
				{
					return static_cast<unsigned char>(*val);
				}
				else if (typeId == TYPE_ID_SHORT)
				{
					return static_cast<short>(*val);
				}
				else if (typeId == TYPE_ID_UNSIGNED_SHORT)
				{
					return static_cast<unsigned short>(*val);
				}
				else if (typeId == TYPE_ID_INT)
				{
					return static_cast<int>(*val);
				}
				else if (typeId == TYPE_ID_UNSIGNED_INT)
				{
					return static_cast<unsigned int>(*val);
				}
				else if (typeId == TYPE_ID_LONG)
				{
					return static_cast<long>(*val);
				}
				else if (typeId == TYPE_ID_UNSIGNED_LONG)
				{
					return static_cast<unsigned long>(*val);
				}
				else if (typeId == TYPE_ID_LONG_LONG)
				{
					return static_cast<long long>(*val);
				}
				else if (typeId == TYPE_ID_UNSIGNED_LONG_LONG)
				{
					return static_cast<unsigned long long>(*val);
				}
				else if (typeId == TYPE_ID_FLOAT)
				{
					return static_cast<float>(*val);
				}
				else if (typeId == TYPE_ID_DOUBLE)
				{
					return static_cast<double>(*val);
				}
				else if (typeId == TYPE_ID_LONG_DOUBLE)
				{
					return static_cast<long double>(*val);
				}
				else if (typeId == TYPE_ID_STRING)
				{
					return std::string(*val ? "true" : "false");
				}
				else if (typeId == TYPE_ID_STRING_VIEW)
				{
					return std::string_view(*val ? "true" : "false");
				}
			}
		}
		else if (const LuaTable* tbl = std::get_if<LuaTable>(&var))
		{
			// member is "rttr::variant" if we need to convert table to container inside any other container
			if (typeId == TYPE_ID_LUA_TABLE)
			{
				return *tbl;
			}
			else if (typ.is_sequential_container())
			{
				// have to extract information from lua table into rttr::variant containing desired container

				// for containers, we need to be passed an instance of it (created earlier by (optionally resizing) and taking first element)
				rttr::variant var = createContainerFromClassMemberVariant(member);
				wxASSERT_MSG(var.is_valid(), "Creation function for member returned invalid variant");
				wxASSERT_MSG(var.is_sequential_container(), "Member is not sequential container, but sequential container is expected");
				rttr::variant_sequential_view seqView = var.create_sequential_view();
				rttr::type valType = seqView.get_value_type();

				rttr::type wrappedType = valType.get_wrapped_type();
				auto arr = tbl->getArrayPart();
				if (seqView.is_dynamic())
				{
					seqView.set_size(arr.size());
				}
				else
				{
					luaAssert(arr.size() == seqView.get_size(), "Lua table size ({}) doesn't match nonresizable sequential container size ({})", arr.size(), seqView.get_size());
					wxASSERT_MSG(seqView.get_size() > 0, "Nondynamic sequential container size is 0");
				}
				// if we have a container of containers/wrappers, we need to get example value to have instance of value type to modify
				rttr::variant example = getNestedContainerExampleValue(var);
				rttr::type firstType = rttr::type::get<void*>();
				for (int i = 0; const LuaTypeInCpp & val : arr)
				{
					rttr::variant var = convertLuaTypeInCppToVariant(val, example.is_valid() ? example : wrappedType);
					luaAssert(var.is_valid(), "Couldn't convert lua type '{}' to rttr::variant", val);
					if (!firstType.is_valid())
					{
						firstType = var.get_type();
					}
					else
					{
						luaAssert(var.get_type() == firstType, "All elements of sequential container must be of the same type. First type is {}, type at index #{} is {}", firstType, i, var.get_type());
					}
					if (!seqView.set_value(i, var))
					{
						luaError("Couldn't set value at index #{} of sequential container (first type: '{}', current type: '{}')", i, firstType, var.get_type());
					}
					++i;
				}
				return var;
			}
			else if (typ.is_associative_container())
			{
				// have to extract information from lua table into rttr::variant containing desired container
				rttr::variant var = createContainerFromClassMemberVariant(member);
				wxASSERT_MSG(var.is_valid(), "Creation function for member returned invalid variant");
				wxASSERT_MSG(var.is_associative_container(), "Member is not associative container, but associative container is expected");
				auto view = var.create_associative_view();
				rttr::type valType = view.get_value_type(), keyType = view.get_key_type();
				view.clear();
				rttr::type firstKeyType = rttr::type::get<void*>(), firstValueType = rttr::type::get<void*>();
				for (auto&& [key, val] : *tbl)
				{
					rttr::variant keyVar = convertLuaTypeInCppToVariant(key, firstKeyType ? firstKeyType : keyType);
					luaAssert(keyVar.is_valid(), "Couldn't convert lua type '{}' to rttr::variant", key);
					if (!firstKeyType)
					{
						firstKeyType = keyVar.get_type();
					}
					else
					{
						luaAssert(keyVar.get_type() == firstKeyType, "All keys of associative container must be of the same type. First type is {}, current type is {}", firstKeyType, keyVar.get_type());
					}
					if (view.is_key_only_type())
					{
						if (!view.insert(keyVar).second)
						{
							luaError("Couldn't insert key into associative container (first key type: '{}', current key type: '{}')", firstKeyType, keyVar.get_type());
						}
					}
					else
					{
						rttr::variant valVar = convertLuaTypeInCppToVariant(val, firstValueType ? firstValueType : valType);
						luaAssert(valVar.is_valid(), "Couldn't convert lua type '{}' to rttr::variant", val);
						if (!firstValueType)
						{
							firstValueType = valVar.get_type();
						}
						else
						{
							luaAssert(valVar.get_type() == firstValueType, "All values of associative container must be of the same type. First type is {}, current type is {}", firstValueType, valVar.get_type());
						}
						if (!view.insert(keyVar, valVar).second)
						{
							luaError("Couldn't insert key-value pair into associative container (first key type: '{}', current key type: '{}', first value type: '{}', current value type: '{}')", firstKeyType, keyVar.get_type(), firstValueType, valVar.get_type());
						}
					}
				}
			}
			else if (typ.is_class()) // must be registered
			{
				rttr::variant var = typ.create(); // !!! will return shared ptr
				wxASSERT_MSG(var, std::format("Couldn't create instance of class '{}'", typ));
				var = var.extract_wrapped_value(); // extract raw pointer
				// FIXME: return instance of class, not pointer?
				return var;
			}
			else if (allowCrossTypeConversions && typeId == TYPE_ID_BOOL)
			{
				return true;
			}
		}
		return rttr::variant();
	}

	// now similar function to above, but using runtime type_id of rttr::variant to perform the conversions
	static bool convertVariantToLuaTypeOnStack(lua_State* L, const rttr::variant& val);
};
