#pragma once
#include "main.h"
#include "CallEvents.h"
#include "LuaWrapper.h"
#include "Utility.h"

template<typename T>
concept IsCvUnqualifiedTopLevel = !(std::is_const_v<std::remove_reference_t<T>> || std::is_volatile_v<std::remove_reference_t<T>>);

template<typename... Args>
void callDestructors(Args&&... args)
{
	(args.~Args(), ...);
}

// lua debug api
namespace lua::debugApi
{
	extern "C"
	{
		int classExists(lua_State* L);
		int copyObject(lua_State* L);
		int createObject(lua_State* L);
		int destroyObject(lua_State* L);
		int getClassObjectField(lua_State* L);
		int getClassField(lua_State* L);
		int getGlobalField(lua_State* L);
		int getClassObjectFieldPtr(lua_State* L);
		int getClassFieldPtr(lua_State* L);
		int getGlobalFieldPtr(lua_State* L);
		int setClassObjectField(lua_State* L);
		int setClassField(lua_State* L);
		int setGlobalField(lua_State* L);
		int invokeClassMethod(lua_State* L);
		int invokeClassObjectMethod(lua_State* L);
		int invokeGlobalMethod(lua_State* L);
		int getClassInfo(lua_State* L);
		int getGlobalEnvironmentInfo(lua_State* L);
		// containers
		int getContainerSize(lua_State* L);
		int getContainerElement(lua_State* L);
		int setContainerElement(lua_State* L);
		int clearContainer(lua_State* L);
		int getContainerKeys(lua_State* L);
		int getContainerValues(lua_State* L);
	}
}

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

// member methods, static methods, global methods, global callables, member callables, static callables
// those that are object properties: member methods, member callables
// those that are class properties: static methods, static callables
// those that are global properties: global methods, global callables

// will contain utils for dealing with RTTR reflection system, like a template method for calling any method by name, converting lua types to callableIndexPair C++ types etc.
class Reflection
{
	// so, I need to be able to call any method by name, and I need to be able to convert lua types to C++ types
	// however, we don't know the exact signature (types) of the method, and converting lua types to
	// **exactly matching** C++ types (RTTR requires it) is not trivial
	// (for example, there are two types for numbers: integer and float, and lua (5.1) doesn't distinguish between them, so 7 could be just 7 or 7.0 [double])
	// so I will store the type_id of those types, they will change with each different game launch, but will be the same, once I set them dynamically in .cpp file of this class
	// this allows to "get exact type" of method parameter, still will require a ton of ifs, but should work
	// NOTE: when creating those ifs, we need to strip any const or volatile qualifiers
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

private:

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
public:
	// converts lua parameter from stack to given type (using RTTR type_id)
	// allowCrossTypeCategoryConversions allows to convert lua types to C++ types, which are not exactly matching, but are compatible (like number to boolean)
	using RttrClassMemberVariant = std::variant<rttr::property, std::pair<rttr::constructor, size_t>, std::pair<rttr::method, size_t>>;
	static rttr::variant convertStackIndexToType(lua_State* L, int stackIndex, const RttrClassMemberVariant& classPropertyVariant, bool allowCrossTypeCategoryConversions = false)
	{
		// property, method, constructor can have metadata, which will allow to create new, empty container of desired type
		// type metadata won't work, because would need to register a ton of types, and I don't want to do that
		// method and constructor require index in addition to type, so I can use metadata
		LuaWrapper wrapper(L);

		// gets type of property, method parameter or constructorm parameter
		// takes into account that constructor might be wrapped
		// receives also index of parameter in case of method or constructor (pair)
		auto getType = [&](const RttrClassMemberVariant& var) -> rttr::type
			{
				if (const rttr::property* prop = std::get_if<rttr::property>(&var))
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

			};

		auto getCreationFunction = [&](const RttrClassMemberVariant& var) -> rttr::variant
			{
				using FuncVector = std::vector<CreateContainerFunc>;
				if (const rttr::property* prop = std::get_if<rttr::property>(&var))
				{
					rttr::variant m = prop->get_metadata(g_CONTAINER_CREATION_FUNC_METADATA_NAME);
					wxASSERT_MSG(m.is_type<FuncVector>(), std::format("Property '{}' of type '{}' doesn't have metadata with creation function", prop->get_name(), prop->get_type()));
					return m.get_value<FuncVector>()[0];
				}
				else if (const std::pair<rttr::constructor, size_t>* constr = std::get_if<std::pair<rttr::constructor, size_t>>(&var))
				{
					auto [ctor, unwrapped] = util::rttr::getMaybeWrappedConstructor(constr->first);
					rttr::variant m = ctor.get_metadata(g_CONTAINER_CREATION_FUNC_METADATA_NAME);
					wxASSERT_MSG(m.is_type<FuncVector>(), std::format("Constructor '{}' of type '{}'{} doesn't have metadata with creation function", ctor.get_signature(), unwrapped ? " [unwrapped]" : "", ctor.get_declaring_type()));
					return m.get_value<FuncVector>()[constr->second];
				}
				else if (const std::pair<rttr::method, size_t>* method = std::get_if<std::pair<rttr::method, size_t>>(&var))
				{
					rttr::variant m = method->first.get_metadata(g_CONTAINER_CREATION_FUNC_METADATA_NAME);
					wxASSERT_MSG(m.is_type<FuncVector>(), std::format("Method '{}' of type '{}' doesn't have metadata with creation function", method->first.get_signature(), method->first.get_declaring_type()));
					return m.get_value<FuncVector>()[method->second];
				}
				else
				{
					wxFAIL_MSG("Unknown type of std::variant");
					return rttr::variant(); // dummy return
				}
			};

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
				// have to extract information from lua table into rttr::variant containing desired container
				// VECTOR IS NOT REGISTERED
				//rttr::variant var = toContainer::vector{}; // shared_ptr
				//assert(var.convert(classPropertyVariant)); // hopefully convert element to vector
				//assert(classPropertyVariant.get_metadata("createFunc").is_type<CreateContainerFunc>()); // getting metadata from PROPERTY might allow it to work
				//rttr::variant var = classPropertyVariant.get_metadata("createFunc").get_value<CreateContainerFunc>()();
				rttr::variant f = getCreationFunction(classPropertyVariant);
				assert(f.is_type<CreateContainerFunc>());
				rttr::variant var = f.get_value<CreateContainerFunc>()();
				//CreateObjectVisitor visitor(var);
				//visitor.visit(classPropertyVariant);
				assert(var.is_valid());
				assert(var.is_sequential_container());

				rttr::variant_sequential_view seqView = var.create_sequential_view();
				//rttr::variant_sequential_view seqView = var.extract_wrapped_value().create_sequential_view();
//                 rttr::type valType = seqView.get_value_type();
//                 if (!valType.is_wrapper())
//                 {
//                     throw std::runtime_error("Can't convert lua table to sequential container, because it contains elements of non-wrapped type");
//                 }
//                 rttr::type wrappedType = valType.get_wrapped_type();
				rttr::type wrappedType = seqView.get_value_type();
				LuaTable t = LuaTable::fromLuaTable(L, stackIndex);
				auto arr = t.getArrayPart();
				seqView.set_size(arr.size());
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
				auto f = getCreationFunction(classPropertyVariant);
				assert(f.is_type<CreateContainerFunc>());
				rttr::variant var = f.get_value<CreateContainerFunc>()();
				assert(var.is_valid());
				rttr::variant_associative_view assocView = var.create_associative_view();
				rttr::type keyType = assocView.get_key_type();
				rttr::type valueType = assocView.get_value_type();
				//                 if (!keyType.is_wrapper())
				//                 {
				//                     throw std::runtime_error("Can't convert lua table to associative container, because it contains keys of non-wrapped type");
				//                 }
				//                 if (!valueType.is_wrapper())
				//                 {
				//                     throw std::runtime_error("Can't convert lua table to associative container, because it contains values of non-wrapped type");
				//                 }
				//                 rttr::type wrappedKeyType = keyType.get_wrapped_type();
				//                 rttr::type wrappedValueType = valueType.get_wrapped_type();
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

	static rttr::variant convertLuaTypeInCppToVariant(const LuaTypeInCpp& var, const rttr::type& typ, bool allowCrossTypeConversions = false)
	{
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
		else if (const LuaTable* val = std::get_if<LuaTable>(&var))
		{
			if (typeId == TYPE_ID_LUA_TABLE)
			{
				return *val;
			}
			else if (typ.is_sequential_container())
			{
				// have to extract information from lua table into rttr::variant containing desired container
				rttr::variant var = typ.create();
				rttr::variant_sequential_view seqView = var.create_sequential_view();
				rttr::type valType = seqView.get_value_type();
				if (!valType.is_wrapper())
				{
					throw std::runtime_error("Can't convert lua table to sequential container, because it contains elements of non-wrapped type");
				}
				rttr::type wrappedType = valType.get_wrapped_type();
				auto arr = val->getArrayPart();
				seqView.set_size(arr.size());
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
				rttr::type wrappedType = typ.get_wrapped_type();/// FIX
				rttr::variant var = typ.create();
				rttr::variant_associative_view assocView = var.create_associative_view();
				for (auto&& [key, value] : *val)
				{
					assocView.insert(key, value);
				}
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
	static bool convertVariantToLuaTypeOnStack(lua_State* L, const rttr::variant& val)
	{
		LuaWrapper wrapper(L);
		type_id typ = val.get_type().get_id();
		if (val.is_sequential_container())
		{
			// create table from sequential container
			rttr::variant_sequential_view seqView = val.create_sequential_view();
			// IMPORTANT: values are stored inside reference_wrapper, so we have to get wrapped type
			rttr::type wrappedType = seqView.get_value_type();
			LuaTable t;
			for (int i = 0; auto & value : seqView)
			{
				//                 if (value.get_type().get_id() != wrappedType.get_id())
				//                 {
				//                     throw std::runtime_error("Can't convert sequential container to lua table, because it contains elements of different types");
				//                 }
								// TODO: a way to avoid copy here?
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
				//                 if (key.get_type().get_id() != keyType.get_id())
				//                 {
				//                     throw std::runtime_error("Can't convert associative container to lua table, because it contains keys of different types");
				//                 }
				//                 if (value.get_type().get_id() != valueType.get_id())
				//                 {
				//                     throw std::runtime_error("Can't convert associative container to lua table, because it contains values of different types");
				//                 }
				t[convertVariantToLuaTypeInCpp(key.extract_wrapped_value())] = convertVariantToLuaTypeInCpp(value.extract_wrapped_value());
			}
			t.pushToLuaStack(L);
		}
		else if (typ == TYPE_ID_NIL)
		{
			wrapper.pushnil();
		}
		else if (typ == TYPE_ID_LUA_TABLE)
		{
			if (!val.is_type<LuaTable>())
			{
				throw std::runtime_error("Can't convert lua table to lua table, because it's not of type LuaTable");
			}
			val.get_value<LuaTable>().pushToLuaStack(L);
		}
		else if (typ == TYPE_ID_BOOL)
		{
			wrapper.pushboolean(val.get_value<bool>());
		}
		else if (typ == TYPE_ID_CHAR)
		{
			wrapper.pushnumber(static_cast<lua_Number>(val.get_value<char>()));
		}
		else if (typ == TYPE_ID_UNSIGNED_CHAR)
		{
			wrapper.pushnumber(static_cast<lua_Number>(val.get_value<unsigned char>()));
		}
		else if (typ == TYPE_ID_SHORT)
		{
			wrapper.pushnumber(static_cast<lua_Number>(val.get_value<short>()));
		}
		else if (typ == TYPE_ID_UNSIGNED_SHORT)
		{
			wrapper.pushnumber(static_cast<lua_Number>(val.get_value<unsigned short>()));
		}
		else if (typ == TYPE_ID_INT)
		{
			wrapper.pushnumber(static_cast<lua_Number>(val.get_value<int>()));
		}
		else if (typ == TYPE_ID_UNSIGNED_INT)
		{
			wrapper.pushnumber(static_cast<lua_Number>(val.get_value<unsigned int>()));
		}
		else if (typ == TYPE_ID_LONG)
		{
			wrapper.pushnumber(static_cast<lua_Number>(val.get_value<long>()));
		}
		else if (typ == TYPE_ID_UNSIGNED_LONG)
		{
			wrapper.pushnumber(static_cast<lua_Number>(val.get_value<unsigned long>()));
		}
		else if (typ == TYPE_ID_LONG_LONG)
		{
			wrapper.pushnumber(static_cast<lua_Number>(val.get_value<long long>()));
		}
		else if (typ == TYPE_ID_UNSIGNED_LONG_LONG)
		{
			wrapper.pushnumber(static_cast<lua_Number>(val.get_value<unsigned long long>()));
		}
		else if (typ == TYPE_ID_FLOAT)
		{
			wrapper.pushnumber(static_cast<lua_Number>(val.get_value<float>()));
		}
		else if (typ == TYPE_ID_DOUBLE)
		{
			wrapper.pushnumber(static_cast<lua_Number>(val.get_value<double>()));
		}
		else if (typ == TYPE_ID_LONG_DOUBLE)
		{
			wrapper.pushnumber(static_cast<lua_Number>(val.get_value<long double>()));
		}
		else if (typ == TYPE_ID_STRING)
		{
			wrapper.pushstring(val.get_value<std::string>());
		}
		else if (typ == TYPE_ID_STRING_VIEW)
		{
			wrapper.pushstring(std::string(val.get_value<std::string_view>()));
		}
		else if (typ == TYPE_ID_VOID)
		{
			// explicit lack of return value, ignore
		}
		else if (typ == TYPE_ID_VOID_PTR)
		{
			wrapper.pushlightuserdata(val.get_value<void*>());
		}
		else
		{
			luaError("Unsupported type '{}' in convertVariantToLuaTypeOnStack", val.get_type().get_name().to_string());
			return false;
			//wxFAIL_MSG(wxString::Format("Can't convert type '%s' to matching lua type", val.get_type().get_name().data()));
		}
		return true;
	}

	// receives a vector of callableIndexPair types, and converts lua parameters to C++ types, which are callableIndexPair by the method
	// throws exception with additional info if conversion of any parameter fails
	// by default pops converted parameters from lua stack, but can be disabled
	// nArgs is intended to be set by lua side to show how many arguments were passed to the function (to allow to use default values)
	using CallableVariant = std::variant<rttr::method, rttr::constructor>;
	static std::vector<rttr::variant> convertLuaParametersToCppForReflection(lua_State* L, const CallableVariant& callable, int nArgs, bool pop = true)
	{
		LuaWrapper wrapper(L);
		std::vector<wxString> errorParts;
		std::vector<rttr::parameter_info> requiredParameters;
		std::visit([&](auto& val)
			{
				auto infos = val.get_parameter_infos();
				requiredParameters.reserve(infos.size());
				std::ranges::copy(infos, std::back_inserter(requiredParameters));
			}, callable);
		if (nArgs == -1)
		{
			nArgs = requiredParameters.size();
		}
		else if (nArgs > (int)requiredParameters.size())
		{
			errorParts.push_back(wxString::Format("Too many parameters passed by lua function (expected %d, got %d)", requiredParameters.size(), nArgs));
		}
		else if (nArgs < (int)requiredParameters.size())
		{
			bool haveDefault = true;
			for (int i = nArgs; i < (int)requiredParameters.size(); ++i)
			{
				if (!requiredParameters[i].has_default_value())
				{
					haveDefault = false;
					break;
				}
			}
			if (!haveDefault)
			{
				errorParts.push_back(wxString::Format("Not enough parameters passed by lua function (expected %d, got %d), can't recover using default values", requiredParameters.size(), nArgs));
			}
		}
		int defaultCount = requiredParameters.size() - nArgs;
		wxASSERT_MSG(wrapper.gettop() >= nArgs, "Not enough parameters on lua stack to convert to C++ types");
		std::vector<rttr::variant> result(requiredParameters.size());
		int stackTop = wrapper.gettop();
		int firstStackIndex = stackTop - nArgs + 1; // have to go to the top of the stack for proper argument order
		for (int i = 0; i < (int)requiredParameters.size(); ++i)
		{
			if (i < nArgs) // use passed parameter
			{
				int currentStackIndex = firstStackIndex + i;
				auto&& param = requiredParameters[i];
				if (const rttr::method* meth = std::get_if<rttr::method>(&callable))
				{
					result[i] = convertStackIndexToType(L, currentStackIndex, std::make_pair(*meth, i), true);
				}
				else if (const rttr::constructor* constr = std::get_if<rttr::constructor>(&callable))
				{
					result[i] = convertStackIndexToType(L, currentStackIndex, std::make_pair(*constr, i), true);
				}
				else
				{
					wxFAIL_MSG("Unknown type of std::variant");
				}
				// failsafe to check that lua stack top has not changed (shouldn't happen, but just in case)
				if (wrapper.gettop() != stackTop)
				{
					int top = wrapper.gettop();
					if (pop) // restore stack to original state
					{
						wrapper.settop(stackTop - nArgs);
					}
					throw std::runtime_error(wxString::Format("Lua stack top changed during conversion of lua parameters to C++ types (from %d to %d)", stackTop, top));
				}
				if (!result[i].is_valid()) // got invalid (not supported) type
				{
					errorParts.push_back(wxString::Format("Parameter %d (stack index %d, name '%s') of lua type '%s' to C++ type '%s'", i + 1, currentStackIndex, param.get_name().data(), lua_typename(L, currentStackIndex), param.get_type().get_name().data()));
				}
			}
			else // use default value
			{
				result[i] = requiredParameters[i].get_default_value();
			}
		}
		if (pop)
		{
			wrapper.settop(stackTop - nArgs);
		}
		if (!errorParts.empty())
		{
			throw std::runtime_error("Failed to convert some parameters. Exact failures:\n" + stringConcat(errorParts, "\n"));
		}
		return result;
	}

private:


	// not using convertLuaParametersToCppForReflection here, because it throws exception on failure, and we want to return false instead

	using CallableIndexPair = std::pair<CallableVariant, size_t>;
	static bool canConvertLuaParameter(lua_State* L, int stackIndex, const CallableIndexPair& callableIndexPair)
	{
		LuaWrapper wrapper(L);
		// check validity of stack index
		if (stackIndex < 1 || stackIndex > wrapper.gettop())
		{
			luaError("Invalid stack index {} (current size is {})", stackIndex, wrapper.gettop());
			return false;
		}
		if (const rttr::method* meth = std::get_if<rttr::method>(&callableIndexPair.first))
		{
			return convertStackIndexToType(L, stackIndex, std::make_pair(*meth, callableIndexPair.second)).is_valid();
		}
		else if (const rttr::constructor* constr = std::get_if<rttr::constructor>(&callableIndexPair.first))
		{
			return convertStackIndexToType(L, stackIndex, std::make_pair(*constr, callableIndexPair.second)).is_valid();
		}
		else
		{
			luaError("Unknown type of std::variant");
			return false;
		}
	}

	static bool canConvertLuaParameters(lua_State* L, const CallableVariant& callable, int nArgs = -1)
	{
		std::vector<rttr::parameter_info> required;
		std::visit([&](auto& val)
			{
				auto infos = val.get_parameter_infos();
				required.reserve(infos.size());
				std::ranges::copy(infos, std::back_inserter(required));
			}, callable);

		LuaWrapper wrapper(L);
		if (nArgs == -1)
		{
			nArgs = required.size();
		}
		else if (nArgs > (int)required.size())
		{
			luaError("Too many parameters passed by lua function (expected {}, got {})", required.size(), nArgs);
			return false;
		}
		else if (nArgs < (int)required.size())
		{
			bool haveDefault = true;
			for (int i = nArgs; i < (int)required.size(); ++i)
			{
				if (!required[i].has_default_value())
				{
					haveDefault = false;
					break;
				}
			}
			if (!haveDefault)
			{
				luaError("Not enough parameters passed by lua function (expected {}, got {}), can't recover using default values", required.size(), nArgs);
				return false;
			}
		}
		for (int i = 0; i < nArgs; ++i)
		{
			int stackIndex = wrapper.makeAbsoluteStackIndex(wrapper.gettop() - nArgs + i + 1);
			if (!canConvertLuaParameter(L, stackIndex, std::make_pair(callable, i)))
			{
				// FIXME: unfortunately, function parameter names need to be provided by user, so we can't show them here
				// that was to be expected though
				// luaError("Can't convert parameter {} (stack index {}, name '{}') of lua type '{}' to C++ type '{}'", i + 1, stackIndex, /*required[i].get_name().data()*/"", lua_typename(L, stackIndex), required[i].get_type().get_name().data());
				return false;
			}
		}
		return true;
	}

	static int defaultArgumentCount(const std::vector<rttr::parameter_info>& paramInfo)
	{
		int result = 0;
		int i = 0;
		for (auto itr = paramInfo.rbegin(); itr != paramInfo.rend(); ++itr, ++i)
		{
			if (!itr->has_default_value())
			{
				return i;
			}
		}
		// all default
		return paramInfo.size();
	}

	static rttr::variant callWithLuaParamsCommon(lua_State* L, const rttr::method& meth, rttr::instance inst, int nArgs)
	{
		if (!meth.is_valid())
		{
			return rttr::variant();
		}
		auto paramsArray = meth.get_parameter_infos();
		std::vector<rttr::parameter_info> params(paramsArray.begin(), paramsArray.end());
		if (!canConvertLuaParameters(L, meth, nArgs))
		{
			return rttr::variant();
		}
		std::vector<rttr::variant> variants = convertLuaParametersToCppForReflection(L, meth, nArgs);
		std::vector<rttr::argument> args;
		for (rttr::variant& arg : variants)
		{
			args.push_back(arg);
		}
		rttr::variant result = meth.invoke_variadic(inst.is_valid() ? inst : rttr::instance(), args);
		return result;
	}

	template<typename T>
	static rttr::variant callWithLuaParamsCommonTemplated(lua_State* L, const std::string& name, T* instancePtr, int nArgs = -1)
	{
		bool isMemberFunc = instancePtr != nullptr;
		rttr::method meth = isMemberFunc ? rttr::type::get<T>().get_method(name) : rttr::type::get_global_method(name);
		return callWithLuaParamsCommon(L, meth, isMemberFunc ? rttr::instance(instancePtr) : rttr::instance(), nArgs);
	}

	// to allow calling above function with nullptr (in reality it's not a pointer type, so can't bind to T*, we need to overload it)
	static rttr::variant callWithLuaParamsCommonTemplated(lua_State* L, const std::string& name, std::nullptr_t instancePtr, int nArgs = -1)
	{
		return callWithLuaParamsCommonTemplated(L, name, static_cast<void*>(nullptr), nArgs);
	}
	
	static rttr::variant callWithCppParamsCommon(const rttr::method& meth, rttr::instance inst, const std::vector<rttr::variant>& args)
	{
		if (!meth.is_valid())
		{
			return rttr::variant();
		}
		auto paramsArray = meth.get_parameter_infos();
		std::vector<rttr::parameter_info> params(paramsArray.begin(), paramsArray.end());
		int defaultCount = defaultArgumentCount(params);
		const bool isGlobal = !meth.get_declaring_type().is_valid(); // global methods don't have declaring type
		const std::string formatString = inst.is_valid() ? "instance method '{}'"
			: (isGlobal ? "global function '{}'" : "static class method '{}'");
		const std::string funcName = std::vformat(formatString, std::make_format_args(meth.get_name()));
		if (args.size() > params.size())
		{
			luaError("Too many parameters passed to {} (expected at most {}, got {})", funcName, params.size(), args.size());
			return rttr::variant();
		}
		else if (args.size() + defaultCount < params.size())
		{
			luaError("Not enough parameters passed to {} (expected at least {}, got {})", funcName, params.size() - defaultCount, args.size());
			return rttr::variant();
		}
		auto argsCopy = args;

		// fill in default values
		for (int i = args.size(); i < (int)params.size(); ++i)
		{
			argsCopy.push_back(params[i].get_default_value());
		}
		for (int i = 0; i < (int)argsCopy.size(); ++i)
		{
			// check if types match
			if (argsCopy[i].get_type() != params[i].get_type())
			{
				// if not, try to convert

				// convert works on existing variant, it doesn't create a new one
				if (!argsCopy[i].convert(params[i].get_type()))
				{
					luaError("Parameter {} of {} is of type '{}', but expected type '{}'", i + 1, funcName, argsCopy[i].get_type(), params[i].get_type());
					return rttr::variant();
				}
			}
		}
		std::vector<rttr::argument> v(argsCopy.begin(), argsCopy.end());
		rttr::variant result = meth.invoke_variadic(inst.is_valid() ? inst : rttr::instance(), v);
		return result;
	}

	static rttr::variant callGlobalFunctionCpp(const std::string& name, const std::vector<rttr::variant>& args)
	{
		rttr::method meth = rttr::type::get_global_method(name);
		return callWithCppParamsCommon(meth, rttr::instance(), args);
	}

	static rttr::variant callClassObjectMethodCpp(rttr::variant& instancePtr, const std::string& className, const std::string& methodName, const std::vector<rttr::variant>& args)
	{
		rttr::method meth = rttr::type::get_by_name(className).get_method(methodName);
		return callWithCppParamsCommon(meth, rttr::instance(instancePtr), args);
	}

	static rttr::variant callClassStaticMethodCpp(const std::string& className, const std::string& methodName, const std::vector<rttr::variant>& args)
	{
		rttr::method meth = rttr::type::get_by_name(className).get_method(methodName);
		return callWithCppParamsCommon(meth, rttr::instance(), args);
	}

	static void classDoesNotExistLuaError(const std::string& className)
	{
		luaError("Class {} doesn't exist (invalid type)", className);
	}
	static void propertyDoesNotExistLuaError(const std::string& className, const std::string& propertyName)
	{
		luaError("Property {} doesn't exist in class {}", propertyName, className);
	}

	static void propertyNotStaticLuaError(const std::string& className, const std::string& propertyName)
	{
		luaError("Property {} in class {} is not static", propertyName, className);
	}

	static void propertyStaticLuaError(const std::string& className, const std::string& propertyName)
	{
		luaError("Property {} in class {} is static", propertyName, className);
	}

	static void objectDoesNotHavePropertyLuaError(const std::string& className, const std::string& propertyName)
	{
		luaError("Object of type {} doesn't have property {}", className, propertyName);
	}

	static void globalVariableDoesNotExistLuaError(const std::string& variableName)
	{
		luaError("Global variable {} doesn't exist", variableName);
	}

	static void cannotSetObjectPropertyLuaError(const std::string& className, const std::string& propertyName, int stackIndex, const rttr::property& prop)
	{
		luaError("Can't set property {} of object of type {} - can't convert lua stack index {} to type {}", propertyName, className, stackIndex, prop.get_type().get_name());
	}

	static void cannotGetGlobalVariableLuaError(const std::string& variableName, int stackIndex, const rttr::property& prop)
	{
		luaError("Can't set global variable {} - can't convert lua stack index {} to type {}", variableName, stackIndex, prop.get_type().get_name());
	}

	static rttr::type getAndCheckClassType(const std::string& className)
	{
		rttr::type type = rttr::type::get_by_name(className);
		if (!type.is_valid())
		{
			classDoesNotExistLuaError(className);
		}
		return type;
	}

	static rttr::property getAndCheckClassProperty(const std::string& className, const std::string& propertyName)
	{
		rttr::type type = getAndCheckClassType(className);
		rttr::property prop = type.get_property(propertyName);
		if (!prop.is_valid())
		{
			propertyDoesNotExistLuaError(className, propertyName);
		}
		return prop;
	}

	static rttr::property getAndCheckClassObjectProperty(const rttr::variant& instance, const std::string& propertyName)
	{
		rttr::property prop = instance.get_type().get_raw_type().get_property(propertyName);
		if (!prop.is_valid())
		{
			objectDoesNotHavePropertyLuaError(instance.get_type().get_raw_type().get_name().to_string(), propertyName);
			return prop; // dummy return
		}
		return prop;
	}

	static void checkPropertyIsStatic(const std::string& className, const std::string& propertyName, const rttr::property& prop)
	{
		if (!prop.is_static()) // object field, expected class field
		{
			propertyNotStaticLuaError(className, propertyName);
		}
	}

	static void checkPropertyIsNotStatic(const std::string& className, const std::string& propertyName, const rttr::property& prop)
	{
		if (prop.is_static()) // class field, expected object field
		{
			propertyStaticLuaError(className, propertyName);
		}
	}

public: // property getters

	// takes not an instance, but raw pointer to instance
	static rttr::property getClassObjectPtrField(const rttr::variant& instance, const std::string& propertyName)
	{
		auto type = instance.get_type();
		if (!type.is_pointer())
		{
			luaError("Can't get class object field '{}' - type {} is not a raw pointer to object", propertyName, type.get_raw_type().get_name());
		}
		rttr::property prop = type.get_raw_type().get_property(propertyName);

		if (!prop.is_valid())
		{
			objectDoesNotHavePropertyLuaError(type.get_raw_type().get_name().to_string(), propertyName);
		}
		return prop;
	}

	// takes an instance, not raw pointer to instance
	static rttr::property getClassObjectProperty(const rttr::variant& instance, const std::string& propertyName)
	{
		rttr::property prop = instance.get_type().get_raw_type().get_property(propertyName);
		if (!prop.is_valid())
		{
			objectDoesNotHavePropertyLuaError(instance.get_type().get_raw_type().get_name().to_string(), propertyName);
		}
		return prop;
	}

	static rttr::property getGlobalPropertyCpp(const std::string& varName)
	{
		rttr::property prop = rttr::type::get_global_property(varName);
		if (!prop.is_valid()) // global variable doesn't exist
		{
			globalVariableDoesNotExistLuaError(varName);
		}
		return prop;
	}

	static rttr::variant getGlobalFieldCpp(const std::string& varName)
	{
		rttr::property prop = getGlobalPropertyCpp(varName);
		return prop.get_value(rttr::instance());
	}

	// ensures class exists and property exists, returns the property. Doesn't check if property is static or not
	static rttr::property getClassPropertyCpp(const std::string& className, const std::string& propertyName)
	{
		rttr::type type = getAndCheckClassType(className);
		rttr::property prop = type.get_property(propertyName);
		if (!prop.is_valid())
		{
			propertyDoesNotExistLuaError(className, propertyName);
		}
		return prop;
	}

	static rttr::variant getClassFieldCpp(const std::string& className, const std::string& fieldName)
	{
		rttr::property prop = getClassPropertyCpp(className, fieldName);
		checkPropertyIsStatic(className, fieldName, prop);
		return prop.get_value(rttr::instance());
	}

	static bool getClassFieldToLuaStack(lua_State* L, const std::string& className, const std::string& fieldName)
	{
		rttr::property prop = getClassPropertyCpp(className, fieldName);
		checkPropertyIsStatic(className, fieldName, prop);
		return convertVariantToLuaTypeOnStack(L, prop.get_value(rttr::instance()));
	}

	static bool getGlobalVariableToLuaStack(lua_State* L, const std::string& fieldName)
	{
		rttr::property prop = getGlobalPropertyCpp(fieldName);
		return convertVariantToLuaTypeOnStack(L, prop.get_value(rttr::instance()));
	}

	// variant must contain pointer to real object type, not void* or instance
	static bool getClassObjectFieldToLuaStack(lua_State* L, const std::string& className, const std::string& fieldName, const rttr::variant& instance)
	{
		rttr::property prop = getClassPropertyCpp(className, fieldName);
		checkPropertyIsNotStatic(className, fieldName, prop);
		return convertVariantToLuaTypeOnStack(L, prop.get_value(instance));
	}

	static rttr::property getClassObjectFieldCpp(const rttr::variant& instance, const std::string& fieldName)
	{
		return getAndCheckClassObjectProperty(instance, fieldName);
	}

public: // property setters

	// uses variants
	static bool setClassObjectFieldFromLuaStack(lua_State* L, const rttr::variant& instance, const std::string& propertyName, int stackIndex = -1)
	{
		rttr::property prop = getClassObjectPtrField(instance, propertyName);
		//static
		rttr::variant value = convertStackIndexToType(L, stackIndex, prop);
		if (!value.is_valid())
		{
			luaError("Can't set property {} of object of type {} - can't convert lua stack index {} to type {}", propertyName, instance.get_type().get_raw_type().get_name(), stackIndex, prop.get_type().get_name());
			return false;
		}
		return prop.set_value(instance, value);
	}

	static bool setClassFieldFromLuaStack(lua_State* L, const std::string& className, const std::string& propertyName, int stackIndex = -1)
	{
		rttr::property prop = getClassPropertyCpp(className, propertyName);
		checkPropertyIsStatic(className, propertyName, prop);
		rttr::variant value = convertStackIndexToType(L, stackIndex, prop);
		if (!value.is_valid())
		{
			luaError("Can't set property {} of class {} - can't convert lua stack index {} to type {}", propertyName, className, stackIndex, prop.get_type().get_name());
			return false;
		}
		return prop.set_value(rttr::instance(), value);
	}

	static bool setGlobalVariableFromLuaStack(lua_State* L, const std::string& variableName, int stackIndex = -1)
	{
		rttr::property prop = getGlobalPropertyCpp(variableName);
		rttr::variant value = convertStackIndexToType(L, stackIndex, prop);
		if (!value.is_valid())
		{
			luaError("Can't set global variable {} - can't convert lua stack index {} to type {}", variableName, stackIndex, prop.get_type().get_name());
			return false;
		}
		return prop.set_value(rttr::instance(), value);
	}

	static bool setClassObjectPtrFieldCpp(const rttr::variant& instance, const std::string& propertyName, const rttr::variant& value)
	{
		rttr::property prop = getClassObjectPtrField(instance, propertyName);
		checkPropertyIsNotStatic(instance.get_type().get_raw_type().get_name().to_string(), propertyName, prop);
		return prop.set_value(instance, value);
	}

	static bool setClassObjectFieldCpp(const rttr::variant& instance, const std::string& propertyName, const rttr::variant& value)
	{
		rttr::property prop = getClassObjectPtrField(instance, propertyName);
		checkPropertyIsNotStatic(instance.get_type().get_raw_type().get_name().to_string(), propertyName, prop);
		return prop.set_value(instance, value);
	}

	static bool setClassFieldCpp(const std::string& className, const std::string& propertyName, const rttr::variant& value)
	{
		rttr::property prop = getClassPropertyCpp(className, propertyName);
		checkPropertyIsStatic(className, propertyName, prop);
		return prop.set_value(rttr::instance(), value);
	}

	static bool setGlobalVariableCpp(const std::string& variableName, const rttr::variant& value)
	{
		rttr::property prop = getGlobalPropertyCpp(variableName);
		return prop.set_value(rttr::instance(), value);
	}

public: // function calls

	static rttr::variant callGlobalFunctionWithLuaParams(lua_State* L, const std::string& name, int nArgs = -1)
	{
		rttr::method meth = rttr::type::get_global_method(name);

		return callWithLuaParamsCommon(L, meth, rttr::instance(), nArgs);
	}

	static rttr::variant callClassObjectMethodWithLuaParams(lua_State* L, rttr::variant instance, const std::string& methodName, int nArgs = -1)
	{
		rttr::type t = instance.get_type().get_raw_type();
		if (!t.is_class())
		{
			return rttr::variant();
		}
		else if (!instance.get_type().is_pointer())
		{
			return rttr::variant();
		}
		rttr::method meth = t.get_method(methodName);

		return callWithLuaParamsCommon(L, meth, instance, nArgs);
	}

	static rttr::variant callClassMethodWithLuaParams(lua_State* L, const std::string& className, const std::string& methodName, int nArgs = -1)
	{
		rttr::type t = rttr::type::get_by_name(className);
		if (!t.is_class())
		{
			return rttr::variant();
		}
		rttr::method meth = t.get_method(methodName);

		return callWithLuaParamsCommon(L, meth, rttr::instance(), nArgs);
	}

public: // constructor call helpers

	// so, I need to be able to put object, variant containing object or something like that into userdata allocated by lua
	// idk if rttr variants are moveable (if there is a way to avoid copying), but I will assume they are not
	// possible options:
	// 1) pass a pointer to variant containing [object or pointer to object] to lua, and then create userdata of it
	// 2) pass variant containing [object or pointer to object] to lua, and then create userdata of it - probably will be hard to avoid unnecessary copying
	// we can't use raw pointers to class, because I don't know, which type it is, and I don't want to use void* (because it's not type safe)
	// for now I will use variant passed by copy, which contains a pointer to object (userdata will contain variant class)

	// also takes a nArgs parameter, which specifies, how many arguments from lua stack should be passed to constructor (if -1, then any number of arguments is allowed). It needs to be greater or equal to the number of non-default parameters
	// returns variant containing shared_ptr to created object, or invalid variant if no matching constructor was found
	static rttr::variant findAndInvokeConstructorWithLuaArgs(lua_State* L, const rttr::type& type, int nArgs = -1)
	{
		for (rttr::constructor ctor : type.get_constructors())
		{
			auto info = ctor.get_parameter_infos();

			std::vector<rttr::parameter_info> vec(info.begin(), info.end());
			if (canConvertLuaParameters(L, ctor, nArgs))
			{
				std::vector<rttr::variant> variants = convertLuaParametersToCppForReflection(L, ctor, nArgs);
				std::vector<rttr::argument> params;
				for (rttr::variant& arg : variants)
				{
					params.push_back(arg);
				}
				rttr::variant result = ctor.invoke_variadic(params);
				// object is std::shared_ptr<Class>, so we need to extract it
				// PROBLEM: 1) shared_ptr has no release() method, 2) shared_ptr methods are not known to RTTR, so we can't invoke them reflectively
				//result.get_type().get_method("release").invoke(result); // release ownership of object
				return result;//.extract_wrapped_value();
			}
		}
		return rttr::variant();
	}

	// returns variant containing shared_ptr to created object, or invalid variant if no matching constructor was found
	static rttr::variant findAndInvokeConstructorWithCppArgs(const rttr::type& type, const std::vector<rttr::variant>& args)
	{
		for (rttr::constructor ctor : type.get_constructors())
		{
			auto info = ctor.get_parameter_infos();

			std::vector<rttr::parameter_info> vec(info.begin(), info.end());
			int defCount = defaultArgumentCount(vec);
			if (args.size() >= info.size() - defCount && args.size() <= vec.size()) // have to check that we have enough arguments, but not too many
			{
				bool canConvert = true;
				for (int i = 0; i < (int)vec.size(); ++i)
				{
					if (args[i].get_type().get_id() != vec[i].get_type().get_id())
					{
						wxLogError("Can't convert argument %d from type '%s' to type '%s'", i + 1, args[i].get_type().get_name().data(), vec[i].get_type().get_name().data());
						wxLog::FlushActive();
						canConvert = false;
						break;
					}
				}
				if (canConvert)
				{
					auto r = args | std::views::transform([](const rttr::variant& var) { return static_cast<rttr::argument>(var); });
					std::vector<rttr::argument> params(r.begin(), r.end());
					rttr::variant result = ctor.invoke_variadic(params);
					//result.get_type().get_method("release").invoke(result); // release ownership of object
					return result;// .extract_wrapped_value();
				}
			}
		}
		return rttr::variant();
	}

public: // constructor calls

	// creates instance of given class by calling constructor with matching parameters
	// returns shared_ptr to created instance, or nullptr if no matching constructor was found
	// this one returns shared_ptr, because it's provided with a class type, so it can have nicer form of usage
	template<typename Class>
	static std::shared_ptr<Class> createInstanceByConstructorFromLuaStack(lua_State* L, int nArgs = -1)
	{
		auto result = findAndInvokeConstructorWithLuaArgs(L, rttr::type::get<Class>(), nArgs);
		// we need to do copy construction, because there are three options for constructor policies regarding object creation:
		// 1) create a new object with automatic storage duration
		// 2) create a new object and return std::shared_ptr<Class> (default)
		// 3) create a new object with dynamic storage duration (Class*), which needs to be properly .destroy()-ed later
		// third option is best for this use case IMO, but it requires explicitly changing policy in each class constructor registration, and I would obviously forget about it many times, ~~so I will just create a dynamic copy of automatic storage object~~ (decided to use shared_ptr's instead)
		static_assert(std::is_copy_constructible_v<Class>, "Class must be copy constructible (for now)");

		// TODO: require that "dynamic creation" policy is set if class is not copy constructible
		return result.is_valid() ? result.get_value<std::shared_ptr<Class>>() : nullptr;
	}

	// creates instance of given class by calling constructor with matching parameters
	// returns a variant with std::shared_ptr to dynamically-allocated variant containing instance. Variant is invalid if no matching constructor was found
	// returns variant containing shared_ptr to created object, or invalid variant if no matching constructor was found
	static rttr::variant createInstanceByConstructorFromLuaStack(lua_State* L, const std::string& className, int nArgs = -1)
	{
		rttr::type type = getAndCheckClassType(className);
		auto result = findAndInvokeConstructorWithLuaArgs(L, type, nArgs);
		// now hopefully has shared_ptr inside, pointing to new instance of class
		// can methods be invoked reflectively on raw pointers to class?
		return result;
	}

	//     static std::string toString(const rttr::variant& var)
	//     {
	//         for (const auto& prop : var.get_type().get_properties())
	//         {
	//             prop.get_name();
	//             prop.
	//         }
	//     }

		// store reflectively created class instances as userdata/light userdata inside lua? (so that we can get them back later)

	// CONTAINERS
	// since containers can be nested, for example std::vector<std::vectors<std::vector<int>>>, and they don'cls have names nor are reflected in RTTR, we need to pass "access path" to the indexed container, as well as field name, to get specific one
	// so for example above and assignment index[0][2][5] = 88, we would pass {0, 2} as access path, 5 as index, and 88 as value

private:

	rttr::variant getContainerFieldSequence(lua_State* L, const std::vector<LuaTypeInCpp>& parts, rttr::variant& entity)
	{
		for (int i = 0; i < (int)parts.size(); ++i)
		{

		}
		return rttr::variant();
	}

	// value at "entityIndex" can actually be global variable or function, class static field or method, or class object field or method
	rttr::variant getContainerByPath(lua_State* L, int accessPathIndex, int entityIndex, int fieldNameIndex)
	{
		LuaWrapper w(L);
		accessPathIndex = w.makeAbsoluteStackIndex(accessPathIndex);
		entityIndex = w.makeAbsoluteStackIndex(entityIndex);
		fieldNameIndex = w.makeAbsoluteStackIndex(fieldNameIndex);

		auto getField = [&](rttr::variant& entity, const std::string& errorMsgInvalidProp, const std::string& errorMsgCannotGetValue) -> rttr::variant
			{
				std::string name = getLuaTypeOrError<std::string>(L, fieldNameIndex);
				rttr::type type = entity.get_type();
				rttr::property prop = type.get_property(name);
				if (!prop.is_valid())
				{
					luaError(errorMsgInvalidProp, name);
					return rttr::variant();
				}
				else
				{
					auto var = prop.get_value(entity);
					if (!var.is_valid())
					{
						luaError(errorMsgCannotGetValue, name);
						return rttr::variant();
					}
					else
					{
						return var;
					}
				}
			};
		// test what it actually is
		w.getPath("pgenedit.cpp.isClass");
		w.pushvalue(entityIndex);
		if (lua_pcall(L, 1, 1, 0) != LUA_OK)
		{
			luaError("Couldn't get container - error while calling isClass: '%s'", w.tostring(-1));
			return rttr::variant();
		}
		else
		{
			if (static_cast<bool>(w.toboolean(-1))) // is class
			{
				std::string className = getLuaTableMetafieldOrError<std::string>(L, entityIndex, "name");
				rttr::type cls = rttr::type::get_by_name(className);
				if (!cls.is_valid())
				{
					luaError("Couldn't get container - class '{}' is not registered", className);
				}
				else if (!cls.is_class())
				{
					luaError("Couldn't get container - '{}' is not a class", className);
				}
				else
				{
					if (!Reflection::getClassFieldToLuaStack(L, className, getLuaTypeOrError<std::string>(L, fieldNameIndex)))
					{
						luaError("Couldn't get container - couldn't get field '{}' of class '{}'", getLuaTypeOrError<std::string>(L, fieldNameIndex), className);
						return rttr::variant();
					}
				}
			}
			else // object or global
			{
				w.getPath("pgenedit.cpp.isClassObject");
				w.pushvalue(entityIndex);
				if (lua_pcall(L, 1, 1, 0) != LUA_OK)
				{
					luaError("Couldn't get container - error while calling isClassObject: '%s'", w.tostring(-1));
					return rttr::variant();
				}
				else if (static_cast<bool>(w.toboolean(-1))) // object
				{
					std::string className = getLuaTableMetafieldOrError<std::string>(L, entityIndex, "className");
					rttr::type cls = rttr::type::get_by_name(className);
					if (!cls.is_valid())
					{
						luaError("Couldn't get container - class '{}' is not registered", className);
					}

				}
				else // global
				{

				}
			}
		}
		if (w.isTable(accessPathIndex))
		{
			LuaTable accessPath = LuaTable::fromLuaTable(L, accessPathIndex);
			rttr::variant ret;
			//for (L)
		}
		else
		{
			luaError("Couldn't get container - access path is not a table");
			return rttr::variant();
		}
		return rttr::variant();
	}

public:
	struct container
	{
		container() = delete;
	private:
		// function is needed, because multiple types may be used to index associative and sequential containers
		static rttr::variant indexAssociative(rttr::variant& container, const LuaTypeInCpp& arg, int paramIndex)
		{
			if (!container.is_valid())
			{
				luaError("Can't index associative container by {} (parameter #{}) - container is invalid", ::lua::utils::convertLuaTypeInCppTypeToString(arg), paramIndex);
				return rttr::variant();
			}
			rttr::variant_associative_view view = container.create_associative_view();
			// need to convert lua type to rttr::variant
			rttr::type keyType = view.get_key_type();
			rttr::variant index = convertLuaTypeInCppToVariant(arg, keyType);
			auto iter = view.find(index);
			if (iter == view.end())
			{
				luaError("Can't index associative container by {} (parameter #{}) - key not found", ::lua::utils::convertLuaTypeInCppTypeToString(arg), paramIndex);
				return rttr::variant();
			}
			else
			{
				rttr::variant val = iter.get_value().extract_wrapped_value();
				if (!val.is_valid())
				{
					luaError("Can't index associative container by {} (parameter #{}) - value is invalid", ::lua::utils::convertLuaTypeInCppTypeToString(arg), paramIndex);
				}
				else
				{
					return val;
				}
			}
			return rttr::variant();
		};

		static rttr::variant indexSequential(rttr::variant& container, const LuaTypeInCpp& arg, int paramIndex)
		{
			rttr::variant_sequential_view view = container.create_sequential_view();
			// need to convert lua type to rttr::variant
			size_t index;
			if (const sqword_t* num = std::get_if<sqword_t>(&arg))
			{
				index = *num;
			}
			else if (const lua_Number* num = std::get_if<lua_Number>(&arg))
			{
				// check that number is integer
				if (std::floor(*num) != *num)
				{
					luaError("Can't index sequential container by {} (parameter #{}) - number {} is not an integer", arg, paramIndex, *num);
					return rttr::variant();
				}
				else
				{
					index = *num;
				}
			}
			else
			{
				luaError("Can't index sequential container by {} (parameter #{}) - can't convert to integer", arg, paramIndex);
				return rttr::variant();
			}
			size_t s = view.get_size();
			if (index >= s)
			{
				luaError("Can't index sequential container by parameter #{} - index {} is out of bounds (size is {})", paramIndex, index, s);
			}
			else
			{
				rttr::variant val = view.get_value(index).extract_wrapped_value();
				if (!val.is_valid())
				{
					luaError("Can't index sequential container by {} (parameter #{}) - value is invalid", arg, paramIndex);
				}
				else
				{
					return val;
				}
			}
			return rttr::variant();
		};
	public:
		static rttr::variant getContainerField(rttr::variant& container, const LuaTypeInCpp& index, int paramIndex)
		{
			if (const LuaTable* t = std::get_if<LuaTable>(&index))
			{
				luaError("Indexing by table (parameter #{}) is not supported right now - would need to keep track of the exact table, since even those with exact contents and metatable are not treated as equal, unless they refer to same object in memory", paramIndex + 1);
			}
			else if (const std::string* str = std::get_if<std::string>(&index))
			{
				if (container.is_sequential_container())
				{
					luaError("Indexing sequential container by string (parameter #{}) is not supported", paramIndex + 1);
				}
				else if (container.is_associative_container())
				{
					return indexAssociative(container, *str, paramIndex + 1);
				}
				else
				{
					luaError("Can't index container by string (parameter #{}) - container is neither sequential nor associative", paramIndex + 1);
				}
			}
			else if (const lua_Number* num = std::get_if<lua_Number>(&index))
			{
				if (container.is_sequential_container())
				{
					return indexSequential(container, index, paramIndex + 1);
				}
				else if (container.is_associative_container())
				{
					return indexAssociative(container, index, paramIndex + 1);
				}
				else
				{
					luaError("Can't index container by number (parameter #{}) - container is neither sequential nor associative", paramIndex + 1);
				}
			}
			else if (const bool* b = std::get_if<bool>(&index))
			{
				if (container.is_sequential_container())
				{
					luaError("Indexing sequential container by bool (parameter #{}) is not supported", paramIndex + 1);
				}
				else if (container.is_associative_container())
				{
					return indexAssociative(container, index, paramIndex + 1);
				}
				else
				{
					luaError("Can't index container by bool (parameter #{}) - container is neither sequential nor associative", paramIndex + 1);
				}
			}
			else if (const sqword_t* arg = std::get_if<sqword_t>(&index))
			{
				if (container.is_sequential_container())
				{
					return indexSequential(container, index, paramIndex + 1);
				}
				else if (container.is_associative_container())
				{
					return indexAssociative(container, index, paramIndex + 1);
				}
				else
				{
					luaError("Can't index container by {} (parameter #{}) - container is neither sequential nor associative", *arg, paramIndex + 1);
				}
			}
			else
			{
				luaError("Can't index container by unknown type (parameter #{})", paramIndex + 1);
			}
			return rttr::variant();
		}

		static rttr::variant getContainerFieldSequence(rttr::variant& container, const std::vector<LuaTypeInCpp>& indexes)
		{
			// FIXME: idk how to cause RTTR to not make copies of data at each level (if there is even a way to do so)
			rttr::variant current = container;

			for (int i = 0; const auto & index : indexes)
			{
				if (!(current.is_associative_container() || current.is_sequential_container() || current.get_type().is_wrapper()))
				{
					// it's object, get object field
					luaAssert(std::holds_alternative<std::string>(index), "Can't index object field - index #{} is not a string", i + 1);
					current = getClassObjectFieldCpp(current, std::get<std::string>(index)).get_value(current);
				}
				else
				{
					current = getContainerField(current, index, i++);
				}
			}
			return current;
		}
	private:
		// sets container/object field, which also is a container (assigns container to container)
		static void setContainerContainerField(rttr::variant& container, const rttr::variant& key, const rttr::variant& value, int paramIndex)
		{
			if (container.is_sequential_container())
			{
				rttr::variant_sequential_view viewCurrent = container.create_sequential_view();
				viewCurrent.clear();
				if (value.is_sequential_container())
				{
					rttr::variant_sequential_view viewNew = value.create_sequential_view();
					luaAssert(viewCurrent.get_value_type() == viewNew.get_value_type(), "Can't set sequential container field (param #{}) - container element ({}) and new container element ({}) have different types", paramIndex, viewCurrent.get_value_type(), viewNew.get_value_type());
					if (viewCurrent.is_dynamic())
					{
						viewCurrent.set_size(viewNew.get_size());
					}
					for (int i = 0; auto & value : viewNew)
					{
						viewCurrent.set_value(i++, value);
					}
				}
				else if (value.is_associative_container())
				{
					luaError("Can't set sequential container field (param #{}) - can't assign associative container to sequential container", paramIndex);
				}
				else
				{
					luaAssert(false, "Can't set sequential container field (param #{}) - value '{}' is neither sequential nor associative container", paramIndex, value);
				}
			}
			else if (container.is_associative_container())
			{
				rttr::variant_associative_view viewCurrent = container.create_associative_view();
				viewCurrent.clear();
				if (value.is_associative_container())
				{
					rttr::variant_associative_view viewNew = value.create_associative_view();
					luaAssert(viewCurrent.get_key_type() == viewNew.get_key_type(), "Can't set associative container field (param #{}) - container key ({}) and new container key ({}) have different types", paramIndex, viewCurrent.get_key_type(), viewNew.get_key_type());
					if (viewCurrent.is_key_only_type())
					{
						for (auto& key : viewNew)
						{
							viewCurrent.insert(key);
						}
					}
					else
					{
						luaAssert(viewCurrent.get_value_type() == viewNew.get_value_type(), "Can't set associative container field (param #{}) - container value ({}) and new container value ({}) have different types", paramIndex, viewCurrent.get_value_type(), viewNew.get_value_type());
						for (auto& [key, value] : viewNew)
						{
							viewCurrent.insert(key, value);
						}
					}
				}
			}
			else
			{
				luaError("Can't set original field (param #{}) - original field is neither sequential nor associative container", paramIndex);
			}
		}
	public:
		static void setContainerField(rttr::variant& container, const LuaTypeInCpp& key, const LuaTypeInCpp& value, int paramIndex)
		{
			luaAssert(container.is_valid(), "Can't set container field - container is invalid");
			if (container.is_sequential_container())
			{
				rttr::variant_sequential_view view = container.create_sequential_view();
				rttr::type keyType = rttr::type::get<size_t>();
				rttr::type valueType = view.get_value_type();
				rttr::variant keyVar = convertLuaTypeInCppToVariant(key, keyType);
				luaAssert(keyVar.is_type<size_t>(), "Can't set sequential container field - can't convert key {} to type 'size_t'", key);
				size_t idx = keyVar.get_value<size_t>();

				rttr::variant valueVar = convertLuaTypeInCppToVariant(value, valueType);
				luaAssert(valueVar.is_valid(), "Can't set sequential container field - value '{}' is invalid after conversion to rttr::variant", value);
				if (valueVar.is_type<LuaTable>())
				{
					assert(false); // FIXME: not implemented
				}
				else if (valueVar.is_associative_container() || valueVar.is_sequential_container())
				{
					setContainerContainerField(container, keyVar, valueVar, paramIndex);
				}
				else
				{
					luaAssert(view.set_value(idx, valueVar), "Can't set sequential container field - couldn't set value '{}' at index {}", value, idx);
				}
			}
			else if (container.is_associative_container())
			{
				rttr::variant_associative_view view = container.create_associative_view();
				if (view.is_key_only_type()) // std::set and the like
				{
					rttr::type keyType = view.get_key_type();
					rttr::variant keyVar = convertLuaTypeInCppToVariant(key, keyType);
					luaAssert(keyVar.is_valid(), "Can't set key-only associative container field - key '{}' is invalid after conversion to rttr::variant", key);
					auto [elem, inserted] = view.insert(keyVar);
					if (!inserted)
					{
						luaError("Can't insert element of type '{}' into key-only associative container", keyVar.get_type().get_name());
						return;
					}
				}
				else
				{
					rttr::type keyType = view.get_key_type();
					rttr::type valueType = view.get_value_type();

					rttr::variant keyVar = convertLuaTypeInCppToVariant(key, keyType);
					luaAssert(keyVar.is_valid(), "Can't set container field - key '{}' is invalid after conversion to rttr::variant", key);
					rttr::variant valueVar = convertLuaTypeInCppToVariant(value, valueType);
					auto [elem, inserted] = view.insert(keyVar, valueVar);
					if (!inserted)
					{
						luaError("Can't set container field - couldn't insert key of type '{}' with value of type '{}'", keyVar.get_type().get_name(), valueVar.get_type().get_name());
						return;
					}
				}
			}
			else
			{
				luaError("Can't set container field - container is neither sequential nor associative");
				return;
			}
		}

	private:
		static bool isNonContainerNonWrapperObject(const rttr::variant& var)
		{
			return !(var.is_associative_container() || var.is_sequential_container() || var.get_type().is_wrapper());
		}
	public:

		static void setContainerFieldSequence(rttr::variant& container, const std::vector<LuaTypeInCpp>& indexes, const LuaTypeInCpp& value)
		{
			rttr::variant current = container;
			std::vector<rttr::variant> needToUpdate; // will contain values, which need to be updated when last value changes
			// due to copy semantics of RTTR, we need to get the value at each level, change it recursively, and then set it
			for (int i = 0; i < (int)indexes.size() - 1; ++i)
			{
				needToUpdate.push_back(current);
				if (isNonContainerNonWrapperObject(current))
				{
					// it's object, get object field
					luaAssert(std::holds_alternative<std::string>(indexes[i]), "Can't index object field - index #{} is not a string", i + 1);
					current = getClassObjectFieldCpp(current, std::get<std::string>(indexes[i])).get_value(current);
				}
				else
				{
					current = getContainerField(current, indexes[i], i++);
				}
			}
			// set it
			if (isNonContainerNonWrapperObject(current))
			{
				luaAssert(std::holds_alternative<std::string>(indexes.back()), "Can't index object field - index #{} is not a string", indexes.size());
				rttr::property prop = getClassObjectFieldCpp(current, std::get<std::string>(indexes.back()));
				rttr::variant valueVar = convertLuaTypeInCppToVariant(value, prop.get_type());
				luaAssert(valueVar.is_valid(), "Can't set object field - value '{}' is invalid after conversion to rttr::variant", value);
				if (!prop.set_value(current, valueVar))
				{
					luaError("Can't set object field - couldn't set value '{}' at index {}", value, indexes.size());
				}
			}
			else
			{
				setContainerField(current, indexes.back(), value, indexes.size());
			}
			assert(indexes.size() - 2 == needToUpdate.size());
			// now go backwards, setting value at each level
			std::reference_wrapper<rttr::variant> currentRef = current;
			for (int i = indexes.size() - 2; i >= 1; --i)
			{
				auto&& field = needToUpdate[i];
				if (isNonContainerNonWrapperObject(field))
				{
					luaAssert(std::holds_alternative<std::string>(indexes[i]), "Can't index object field - index #{} is not a string", i + 1);
					setClassObjectFieldCpp(field, std::get<std::string>(indexes[i]), currentRef);
				}
				else
				{
					setContainerField(field, indexes[i], convertVariantToLuaTypeInCpp(currentRef), i + 1);
				}
				currentRef = field;
			}
		}

		size_t getContainerSize(const rttr::variant& container)
		{
			if (container.is_sequential_container())
			{
				rttr::variant_sequential_view view = container.create_sequential_view();
				return view.get_size();
			}
			else if (container.is_associative_container())
			{
				rttr::variant_associative_view view = container.create_associative_view();
				return view.get_size();
			}
			else
			{
				luaError("Can't get container size - container is neither sequential nor associative");
				return 0;
			}
		}

		void clearContainer(rttr::variant& container)
		{
			if (container.is_sequential_container())
			{
				rttr::variant_sequential_view view = container.create_sequential_view();
				view.clear();
			}
			else if (container.is_associative_container())
			{
				rttr::variant_associative_view view = container.create_associative_view();
				view.clear();
			}
			else
			{
				luaError("Can't clear container - container is neither sequential nor associative");
			}
		}

		// returns vector of indexes
		std::vector<rttr::variant> getContainerKeys(const rttr::variant& container)
		{
			if (container.is_sequential_container())
			{
				std::vector<rttr::variant> v;
				v.resize(container.create_sequential_view().get_size());
				std::iota(v.begin(), v.end(), 0);
				return v;
			}
			else if (container.is_associative_container())
			{
				std::vector<rttr::variant> v;
				rttr::variant_associative_view view = container.create_associative_view();
				v.reserve(view.get_size());
				for (auto& [key, value] : view)
				{
					v.push_back(key);
				}
				return v;
			}
			else
			{
				luaError("Can't get container keys - container is neither sequential nor associative");
				return std::vector<rttr::variant>();
			}
		}

		// returns vector of values
		std::vector<rttr::variant> getContainerValues(const rttr::variant& container)
		{
			if (container.is_sequential_container())
			{
				std::vector<rttr::variant> v;
				rttr::variant_sequential_view view = container.create_sequential_view();
				v.reserve(view.get_size());
				for (auto& value : view)
				{
					v.push_back(value);
				}
				return v;
			}
			else if (container.is_associative_container())
			{
				std::vector<rttr::variant> v;
				rttr::variant_associative_view view = container.create_associative_view();
				v.reserve(view.get_size());
				for (auto& [key, value] : view)
				{
					v.push_back(value);
				}
				return v;
			}
			else
			{
				luaError("Can't get container values - container is neither sequential nor associative");
				return std::vector<rttr::variant>();
			}
		}
	};

	// function aliases
	// using namespaces for clarity and not having to remember 20 names of functions

	// these are the functions, which directly access lua stack, whether it's for getting or setting values
	struct lua
	{
		lua() = delete;

		struct get
		{
			get() = delete;
			static constexpr auto globalField = &getGlobalVariableToLuaStack;
			static constexpr auto classField = &getClassFieldToLuaStack;
			static constexpr auto classObjectField = &getClassObjectFieldToLuaStack;
		};

		struct set
		{
			set() = delete;
			static constexpr auto globalField = &setGlobalVariableFromLuaStack;
			static constexpr auto classField = &setClassFieldFromLuaStack;
			static constexpr auto classObjectField = &setClassObjectFieldFromLuaStack;
		};

		struct call
		{
			call() = delete;
			static constexpr auto globalFunction = &callGlobalFunctionWithLuaParams;
			static constexpr auto classFunction = &callClassMethodWithLuaParams;
			static constexpr auto classObjectFunction = &callClassObjectMethodWithLuaParams;
		};

		struct create
		{
			create() = delete;
			static constexpr rttr::variant(*classObjectVariant)(lua_State*, const std::string&, int) = &createInstanceByConstructorFromLuaStack; // need to specify signature, because otherwise it's ambiguous (overloaded function)
			template<typename Class>
			static constexpr std::shared_ptr<Class>(*classObjectSharedPtr)(lua_State*, int) = &createInstanceByConstructorFromLuaStack<Class>;
		};

		struct convert
		{
			convert() = delete;
			template<typename T>
			static constexpr auto valueToLuaTypeOnStack = &convertValueToLuaTypeOnStack<T>;
			static constexpr auto variantToLuaTypeOnStack = &convertVariantToLuaTypeOnStack;
		};
	};

	// these are the functions, which don't use lua stack, but may use C++ representations of lua types (LuaTypeInCpp)
	struct cpp
	{
		cpp() = delete;
		struct get
		{
			get() = delete;
			static constexpr auto globalProperty = &getGlobalPropertyCpp;
			static constexpr auto classProperty = &getClassPropertyCpp;
			static constexpr auto classObjectProperty = &getClassObjectProperty;

			static constexpr auto globalField = &getGlobalFieldCpp;
			static constexpr auto classField = &getClassFieldCpp;
			static constexpr auto classObjectField = &getClassObjectFieldCpp;
			static constexpr auto classObjectPtrField = &getClassObjectPtrField;

			static constexpr auto containerField = &container::getContainerField;
			static constexpr auto containerFieldSequence = &container::getContainerFieldSequence;
			static constexpr auto containerSize = &container::getContainerSize;
			static constexpr auto containerKeys = &container::getContainerKeys;
			static constexpr auto containerValues = &container::getContainerValues;
		};

		struct set
		{
			set() = delete;
			static constexpr auto globalField = &setGlobalVariableCpp;
			static constexpr auto classField = &setClassFieldCpp;
			static constexpr auto classObjectField = &setClassObjectFieldCpp;
			static constexpr auto classObjectPtrField = &setClassObjectPtrFieldCpp;

			static constexpr auto containerField = &container::setContainerField;
			static constexpr auto containerFieldSequence = &container::setContainerFieldSequence;
		};

		struct create
		{
			create() = delete;
			static constexpr auto classObject = &findAndInvokeConstructorWithCppArgs;
		};

		struct convert
		{
			convert() = delete;
			static constexpr auto variantToLuaTypeInCpp = &convertVariantToLuaTypeInCpp;
			static constexpr auto luaTypeInCppToVariant = &convertLuaTypeInCppToVariant;
		};
	};

	// set, nonptr, etc.
};

namespace lua
{
	using reflect = ::Reflection::lua;
}
