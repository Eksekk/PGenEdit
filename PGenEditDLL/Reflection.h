#pragma once
#include "main.h"
#include "CallEvents.h"
#include "LuaWrapper.h"
#include "Utility.h"

template<typename T>
concept IsCvUnqualifiedTopLevel = !(std::is_const_v<std::remove_reference_t<T>> || std::is_volatile_v<std::remove_reference_t<T>>);

// custom exception, which will be thrown as part one of generating lua error from C++
// using this, because it properly invokes destructors of objects
// this exception should be caught by C++ function directly called by lua, and it should execute its own stack objects' destructors and generate lua error
class LuaErrorException : public std::runtime_error
{
    // TODO: have more fields (like what type of error it is, and what are error parameters, so for type mismatch we can show expected type and actual type) to facilitate unit testing
public:
    LuaErrorException(const std::string& msg) : std::runtime_error(msg) {}

    ~LuaErrorException()
    {
        //wxMessageBox(wxString::Format("Lua error: %s", what()), "Lua error", wxICON_ERROR | wxOK);
    }
};

namespace std
{
    // note: you need to implement both functions, otherwise it won't work
    template<>
    struct formatter<rttr::string_view>
    {
        template<typename ParseContext>
        constexpr auto parse(ParseContext& ctx)
        {
            return ctx.begin();
        }

        template<typename FormatContext>
        auto format(const rttr::string_view& p, FormatContext& ctx) const
        {
            return format_to(ctx.out(), "{}", p.to_string());
        }
    };
}

// creates "safe" lua error, that is not skipping C++ destructors
// still need to write try-catch block **in first function on call stack called by lua** which calls luaL_error
// note: exception object is automatically destroyed, even though lua might skip C++ code by using longjmp to signal error
// [[noreturn]] doesn't need to be here BTW, exception object is still destroyed
template<typename... Args>
[[noreturn]] void luaError(const std::string& msg, Args&&... args)
{
    throw LuaErrorException(std::vformat(msg, std::make_format_args(std::forward<Args>(args)...)));
}

template<typename... Args>
void callDestructors(Args&&... args)
{
    (args.~Args(), ...);
}

// lua debug api
namespace luaDebug
{
    // TODO: I removed static from these functions, because I want to use them in LuaFunctions.cpp (to register them in lua), but I'm not sure if it's correct
    extern "C"
    {
        int classExists(lua_State* L);
        int copyObject(lua_State* L);
        int createObject(lua_State* L);
        int destroyObject(lua_State* L);
        int getClassObjectField(lua_State* L);
        int getClassField(lua_State* L);
        int getGlobalField(lua_State* L);
        int setClassObjectField(lua_State* L);
        int setClassField(lua_State* L);
        int setGlobalField(lua_State* L);
        int invokeClassMethod(lua_State* L);
        int invokeClassObjectMethod(lua_State* L);
        int invokeGlobalMethod(lua_State* L);
        int getClassInfo(lua_State* L);
        int getGlobalEnvironmentInfo(lua_State* L);
    }
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
        auto getNthParameterInfo = [](const rttr::array_range<rttr::parameter_info>& range, size_t n) -> rttr::parameter_info
        {
            auto it = range.begin();
            std::advance(it, n);
            return *it;
        };

        auto getType = [getNthParameterInfo](const RttrClassMemberVariant& var) -> rttr::type
            {
                if (const rttr::property* prop = std::get_if<rttr::property>(&var))
                {
                    return prop->get_type();
                }
                else if (const std::pair<rttr::constructor, size_t>* constr = std::get_if<std::pair<rttr::constructor, size_t>>(&var))
                {
                    return getNthParameterInfo(constr->first.get_parameter_infos(), constr->second).get_type();
                }
                else if (const std::pair<rttr::method, size_t>* method = std::get_if<std::pair<rttr::method, size_t>>(&var))
                {
                    return getNthParameterInfo(method->first.get_parameter_infos(), method->second).get_type();
                }
                else
                {
                    wxFAIL_MSG("Unknown type of std::variant");
                    return rttr::type::get<void*>(); // dummy return
                }

            };

        auto getCreationFunction = [getNthParameterInfo](const RttrClassMemberVariant& var) -> rttr::variant
            {
                using FuncVector = std::vector<CreateContainerFunc>;
                if (const rttr::property* prop = std::get_if<rttr::property>(&var))
                {
                    rttr::variant m = prop->get_metadata(g_CONTAINER_CREATION_FUNC_METADATA_NAME);
                    wxASSERT_MSG(m.is_type<FuncVector>(), wxString::Format("Property '%s' of type '%s' doesn't have metadata with creation function", prop->get_name().data(), prop->get_type().get_name().data()));
                    return m.get_value<FuncVector>()[0];
                }
                else if (const std::pair<rttr::constructor, size_t>* constr = std::get_if<std::pair<rttr::constructor, size_t>>(&var))
                {
                    rttr::variant m = constr->first.get_metadata(g_CONTAINER_CREATION_FUNC_METADATA_NAME);
                    wxASSERT_MSG(m.is_type<FuncVector>(), wxString::Format("Constructor '%s' of type '%s' doesn't have metadata with creation function", constr->first.get_signature().data(), constr->first.get_declaring_type().get_name().data()));
                    return m.get_value<FuncVector>()[constr->second];
                }
                else if (const std::pair<rttr::method, size_t>* method = std::get_if<std::pair<rttr::method, size_t>>(&var))
                {
                    rttr::variant m = method->first.get_metadata(g_CONTAINER_CREATION_FUNC_METADATA_NAME);
                    wxASSERT_MSG(m.is_type<FuncVector>(), wxString::Format("Method '%s' of type '%s' doesn't have metadata with creation function", method->first.get_signature().data(), method->first.get_declaring_type().get_name().data()));
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
                for (int i = 0; const LuaTypeInCpp& val : arr)
                {
                    rttr::variant var = convertLuaTypeInCppToVariantByTypeId(val, wrappedType);
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
                    rttr::variant keyVar = convertLuaTypeInCppToVariantByTypeId(key, wrappedKeyType);
                    rttr::variant valueVar = convertLuaTypeInCppToVariantByTypeId(value, wrappedValueType);
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
    static void convertToLuaTypeOnStack(lua_State* L, const T& val)
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
            for (int i = 0; auto& value : seqView)
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

    static rttr::variant convertLuaTypeInCppToVariantByTypeId(const LuaTypeInCpp& var, const rttr::type& typ, bool allowCrossTypeConversions = false)
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
                    rttr::variant var = convertLuaTypeInCppToVariantByTypeId(val, wrappedType);
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

    // now similar function to above, but using runtime type_id of rttr::variant perform the conversions
    static bool convertToLuaTypeOnStackByTypeId(lua_State* L, const rttr::variant& val)
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
            for (int i = 0; auto& value : seqView)
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
            luaError("Unsupported type '{}' in convertToLuaTypeOnStackByTypeId", val.get_type().get_name().to_string());
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
luaError("Can't convert parameter {} (stack index {}, name '{}') of lua type '{}' to C++ type '{}'", i + 1, stackIndex, /*required[i].get_name().data()*/"", lua_typename(L, stackIndex), required[i].get_type().get_name().data());
                return false;
            }
        }
        return true;
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

    // ensures class exists and property exists, returns the property. Doesn't check if property is static or not
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

    static rttr::property getAndCheckClassObjectPtrProperty(const rttr::variant& instance, const std::string& propertyName)
    {
        rttr::property prop = instance.get_type().get_raw_type().get_property(propertyName);
        if (!prop.is_valid())
        {
            luaError("Object of type {} doesn't have property {}", instance.get_type().get_raw_type().get_name(), propertyName);
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

    static rttr::property getAndCheckGlobalVariable(const std::string& varName)
    {
        rttr::property prop = rttr::type::get_global_property(varName);
        if (!prop.is_valid()) // global variable doesn't exist
        {
            globalVariableDoesNotExistLuaError(varName);
        }
        return prop;
    }



    static void checkGlobalVariableExists(const std::string& variableName, const rttr::property& prop)
    {
        if (!prop.is_valid()) // global variable doesn't exist
        {
            globalVariableDoesNotExistLuaError(variableName);
        }
    }

public: // property getters

    static bool getClassFieldToLuaStack(lua_State* L, const std::string& className, const std::string& fieldName)
    {
        rttr::property prop = getAndCheckClassProperty(className, fieldName);
        checkPropertyIsStatic(className, fieldName, prop);
        return convertToLuaTypeOnStackByTypeId(L, prop.get_value(rttr::instance()));
    }

    // variant must contain pointer to real object type, not void*
    static bool getClassObjectFieldToLuaStack(lua_State* L, const std::string& className, const std::string& fieldName, const rttr::variant& instance)
    {
        rttr::property prop = getAndCheckClassProperty(className, fieldName);
        checkPropertyIsNotStatic(className, fieldName, prop);
        return convertToLuaTypeOnStackByTypeId(L, prop.get_value(instance));
    }

    static bool getGlobalVariableToLuaStack(lua_State* L, const std::string& fieldName)
    {
        rttr::property prop = getAndCheckGlobalVariable(fieldName);
        return convertToLuaTypeOnStackByTypeId(L, prop.get_value(rttr::instance()));
    }

public: // property setters

    // uses variants
    static bool setClassObjectFieldFromLuaStack(lua_State* L, const rttr::variant& instance, const std::string& propertyName, int stackIndex = -1)
    {
        rttr::property prop = getAndCheckClassObjectPtrProperty(instance, propertyName);
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
        rttr::property prop = getAndCheckClassProperty(className, propertyName);
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
        rttr::property prop = getAndCheckGlobalVariable(variableName);
        rttr::variant value = convertStackIndexToType(L, stackIndex, prop);
        if (!value.is_valid())
        {
            luaError("Can't set global variable {} - can't convert lua stack index {} to type {}", variableName, stackIndex, prop.get_type().get_name());
            return false;
        }
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
};