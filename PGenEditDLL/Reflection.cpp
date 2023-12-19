#include "pch.h"
#include "Reflection.h"
#include "LuaWrapper.h"
#include "LuaFunctions.h"

using type = rttr::type;
using type_id = type::type_id;
const type_id Reflection::TYPE_ID_CHAR = type::get<char>().get_id();
const type_id Reflection::TYPE_ID_UNSIGNED_CHAR = type::get<unsigned char>().get_id();
const type_id Reflection::TYPE_ID_SHORT = type::get<short>().get_id();
const type_id Reflection::TYPE_ID_UNSIGNED_SHORT = type::get<unsigned short>().get_id();
const type_id Reflection::TYPE_ID_INT = type::get<int>().get_id();
const type_id Reflection::TYPE_ID_UNSIGNED_INT = type::get<unsigned int>().get_id();
const type_id Reflection::TYPE_ID_LONG = type::get<long>().get_id();
const type_id Reflection::TYPE_ID_UNSIGNED_LONG = type::get<unsigned long>().get_id();
const type_id Reflection::TYPE_ID_LONG_LONG = type::get<long long>().get_id();
const type_id Reflection::TYPE_ID_UNSIGNED_LONG_LONG = type::get<unsigned long long>().get_id();
const type_id Reflection::TYPE_ID_FLOAT = type::get<float>().get_id();
const type_id Reflection::TYPE_ID_DOUBLE = type::get<double>().get_id();
const type_id Reflection::TYPE_ID_LONG_DOUBLE = type::get<long double>().get_id();
const type_id Reflection::TYPE_ID_BOOL = type::get<bool>().get_id();
const type_id Reflection::TYPE_ID_STRING_VIEW = type::get<std::string_view>().get_id();
const type_id Reflection::TYPE_ID_STRING = type::get<std::string>().get_id();
const type_id Reflection::TYPE_ID_VOID = type::get<void>().get_id();
const type_id Reflection::TYPE_ID_VOID_PTR = type::get<void*>().get_id();
const type_id Reflection::TYPE_ID_LUA_TABLE = type::get<LuaTable>().get_id();
const type_id Reflection::TYPE_ID_NIL = type::get<_Nil>().get_id();

const std::vector<type_id> Reflection::TYPE_IDS_INTEGERS{ TYPE_ID_CHAR, TYPE_ID_UNSIGNED_CHAR, TYPE_ID_SHORT, TYPE_ID_UNSIGNED_SHORT, TYPE_ID_INT, TYPE_ID_UNSIGNED_INT, TYPE_ID_LONG, TYPE_ID_UNSIGNED_LONG, TYPE_ID_LONG_LONG, TYPE_ID_UNSIGNED_LONG_LONG };
const std::vector<type_id> Reflection::TYPE_IDS_FLOATS{ TYPE_ID_FLOAT, TYPE_ID_DOUBLE, TYPE_ID_LONG_DOUBLE };
const std::vector<type_id> Reflection::TYPE_IDS_STRINGS{ TYPE_ID_STRING_VIEW, TYPE_ID_STRING };
const std::vector<type_id> Reflection::TYPE_IDS_NUMBERS{ compileTimeMergeVectors({TYPE_IDS_INTEGERS, TYPE_IDS_FLOATS }) };
// this one doesn't use "pointer" vector to merge, because strings already contain char pointers
const std::vector<type_id> Reflection::TYPE_IDS_ALL_TYPES{ compileTimeMergeVectors({TYPE_IDS_NUMBERS, TYPE_IDS_STRINGS, {TYPE_ID_BOOL, TYPE_ID_VOID_PTR, TYPE_ID_NIL, TYPE_ID_VOID} }) };

// aliases for lua utility functions
using ::lua::utils::getLuaTableMetafieldOrError;
using ::lua::utils::getLuaTypeOrError;
using ::lua::utils::luaError;
using ::lua::utils::luaExpectStackSize;
using ::lua::utils::luaTableHasMetafield;
using ::lua::utils::isLuaType;

// returns variant containing pointer to object of given type, or invalid variant if failed
static rttr::variant convertToObjectPointer(void* ptr, const std::string& typeName)
{
    rttr::type t = rttr::type::get_by_name(typeName);
    rttr::type ptrT = rttr::type::get_by_name(typeName + "*"); // pointer to object
    if (!t.is_valid())
    {
        luaError("Couldn't get type '{}'", typeName);
        return rttr::variant();
    }
    else if (!t.is_class())
    {
        luaError("Couldn't get type '{}' - it's not a class", typeName);
        return rttr::variant();
    }
    else if (!ptrT.is_valid())
    {
        luaError("Couldn't get type '{}'", typeName + "*");
        return rttr::variant();
    }
    else if (!ptrT.is_pointer())
    {
        luaError("Couldn't get type '{}' - it's not a pointer", typeName + "*");
        return rttr::variant();
    }
    else if (ptrT.get_raw_type() != t)
    {
        luaError("Couldn't get type '{}' - it's not a pointer to '{}'", typeName + "*", typeName);
        return rttr::variant();
    }
    else
    {
        rttr::variant var(ptr);
        if (!var.convert(static_cast<const rttr::type&>(ptrT))) // static_cast used to choose correct overload
        {
            luaError("Couldn't convert void* pointer {:p} to type '{}'", ptr, typeName + "*");
            return rttr::variant();
        }
        else
        {
            return var;
        }
    }
}

// so, it seems the only way to handle creating new objects and destroying them correctly, is using std::shared_ptr<>, or using everywhere policy of raw ptr in constructor
// for userdata, we can probably reinterpret_cast the userdata into the variant (which will contain shared_ptr) and extract raw pointer from it EVERY TIME we want to use it
// for tables, we would need to store raw pointer, because creating shared_ptr to existing object is possible, but would destroy the original object when variant is destroyed

// handles both userdata and table
// userdata contains variant, which itself contains shared_ptr to object
// table contains raw pointer to object
static void* luaGetObjectPtr(lua_State* L, int index)
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

LuaTable getBasicTypeDataTable(const rttr::type& type)
{
    LuaTable typeInfo;
    if (type.is_sequential_container())
    {
        typeInfo["isSequentialContainer"] = true;
        typeInfo["valueType"] = getBasicTypeDataTable(*type.get_template_arguments().begin());
    }
    else if (type.is_associative_container())
    {
        typeInfo["isAssociativeContainer"] = true;
        auto args = type.get_template_arguments();
        typeInfo["keyType"] = getBasicTypeDataTable(*args.begin());
        typeInfo["valueType"] = getBasicTypeDataTable(*++args.begin());
    }
    else // containers aren't enums nor callable
    {
        typeInfo["isEnum"] = type.is_enumeration();
        typeInfo["isCallable"] = type.is_function_pointer() || type.is_member_function_pointer(); // FIXME: somehow handle std::function
    }
    const rttr::type::type_id typeId = type.get_id();
    typeInfo["name"] = type.get_name().to_string();
    //typeInfo["isConst"] = type.;
    //typeInfo["isReference"] = type.is_;
    typeInfo["isPointer"] = type.is_pointer();
    typeInfo["isClass"] = type.is_class();
    rttr::type rawType = type.get_raw_type();
    if (typeId != rawType.get_id()) // avoid infinite recursion
    {
        typeInfo["raw"] = getBasicTypeDataTable(rawType);
    }
    return typeInfo;
}

LuaTable getCallableParamInfo(const rttr::parameter_info& param)
{
    LuaTable paramInfo;
    paramInfo["type"] = getBasicTypeDataTable(param.get_type());
    paramInfo["hasDefaultValue"] = param.has_default_value();
    if (param.has_default_value())
    {
        paramInfo["defaultValue"] = param.get_default_value().to_string(); // FIXME: this is not a string, but a variant
    }
    return paramInfo;
}

LuaTable getCallableParamsTable(const rttr::array_range<rttr::parameter_info>& params)
{
    LuaTable paramsTable;
    int i = 1;
    for (auto& param : params)
    {
        paramsTable[i++] = getCallableParamInfo(param);
    }
    return paramsTable;
}

int getFieldCommon(lua_State* L)
{
    LuaWrapper w(L);
    if (w.gettop() == 1) // get global
    {
        // get global
        std::string name = w.tostring(2);
        auto t = rttr::type::get_by_name(name);
        if (!t.is_valid())
        {
            luaError("Couldn't get global '" + w.tostring(2) + "'");
            return 0;
        }
        else if (t.is_class())
        {
            luaError("Couldn't get global '" + w.tostring(2) + "' - it's a class");
            return 0;
        }
        else
        {
            Reflection::getGlobalVariableToLuaStack(L, name);
            return 1;
        }
    }
    else // get class field
    {
        std::string className = w.tostring(1);
        rttr::type t = rttr::type::get_by_name(className);
        if (!t.is_valid())
        {
            luaError("Couldn't get class '" + className + "'");
            return 0;
        }
        else if (!t.is_class())
        {
            luaError("Couldn't get class '" + className + "' - it's not a class");
            return 0;
        }
        else
        {
            rttr::variant var = convertToObjectPointer(luaGetObjectPtr(L, 3), className);
            if (!var.is_valid())
            {
                luaError("Couldn't get class '" + className + "' - couldn't convert to object pointer");
                return 0;
            }
            else
            {
                rttr::property prop = t.get_property(w.tostring(2));
                if (!prop.is_valid())
                {
                    luaError("Couldn't get property '" + w.tostring(2) + "' of class '" + className + "'");
                    return 0;
                }
                else
                {
                    Reflection::getClassObjectFieldToLuaStack(L, className, prop.get_name().to_string(), var);
                    return 1;
                }
            }
        }
    }
}

[[noreturn]] void throwLuaError(lua_State* L, const std::string& msg)
{
    luaL_error(L, msg.c_str());
}

// receives class name as string
int lua::debugApi::classExists(lua_State* L)
{
    try
    {
        LuaWrapper w(L);
        if (w.gettop() != 1)
        {
            w.pushboolean(false);
            return 1;
        }
        std::string s = getLuaTypeOrError<std::string>(L, 1);
        rttr::type t = rttr::type::get_by_name(s);
        w.pushboolean(t.is_class());
        return 1;
    }
    catch (const LuaErrorException& e)
    {
        luaL_error(L, e.what());
        return 0;
    }
}

// receives object pointer (userdata) of address equal to pointer to object
int lua::debugApi::copyObject(lua_State* L)
{
    try
    {
        LuaWrapper w(L);
        luaExpectStackSize(L, 1);
        void* ptr = luaGetObjectPtr(L, 1);
        if (!ptr)
        {
            luaError("Couldn't copy object - pointer is null");
            return 0;
        }
        rttr::variant var = convertToObjectPointer(ptr, getLuaTableMetafieldOrError<std::string>(L, 1, "className"));
        if (!var.is_valid())
        {
            luaError("Couldn't copy object - couldn't convert to object pointer");
            return 0;
        }
        rttr::variant obj = Reflection::findAndInvokeConstructorWithCppArgs(var.get_type(), { var });
        if (!obj.is_valid())
        {
            luaError("Couldn't copy object - couldn't find ctor");
            return 0;
        }
        else
        {
            if (!obj.convert(rttr::type::get<void*>()))
            {
                luaError("Couldn't copy object - couldn't convert to void pointer");
                return 0;
            }
            else
            {
                void* objPtr = obj.get_value<void*>();
                void* ud = lua_newuserdata(L, sizeof(rttr::variant)); // automatically pushed to stack
                new(ud) rttr::variant(objPtr);
                // TODO: set __gc here?
                return 1;
            }
        }
    }
    catch (const LuaErrorException& e)
    {
        luaL_error(L, e.what());
        return 0;
    }
    //...
}

// receives class name as string, number of arguments and optionally, arguments
int lua::debugApi::createObject(lua_State* L)
{
    try
    {
        LuaWrapper w(L);
        auto name = getLuaTypeOrError<std::string>(L, 1);
        int nargs;
        if (w.gettop() == 1) // assume no arguments
        {
            nargs = 0;
        }
        else
        {
            nargs = getLuaTypeOrError<int>(L, 2);
            int realArgCount = w.gettop() - 2;
            if (realArgCount != nargs)
            {
                luaError("Expected {} arguments, got {}", nargs, realArgCount);
                return 0;
            }
        }
        auto t = rttr::type::get_by_name(name);
        if (!t.is_valid())
        {
            luaError("Couldn't get class '{}'", name);
            return 0;
        }
        else if (!t.is_class())
        {
            luaError("Couldn't create object of type '{}', it's not a class", name);
            return 0;
        }
        else
        {
            rttr::variant obj = Reflection::findAndInvokeConstructorWithLuaArgs(L, t, nargs);
            if (!obj.is_valid())
            {
                luaError("Couldn't create object of type '{}'", name);
                return 0;
            }
            else
            {
                if (!obj.get_type().is_wrapper())
                {
                    luaError("Couldn't create object of type '{}' - variant is not a wrapper, which means it's not a shared_ptr", name);
                    return 0;
                }
                else
                {
                    void* ud = lua_newuserdata(L, sizeof(rttr::variant)); // automatically pushed to stack
                    new(ud) rttr::variant(obj); // hopefully copies shared_ptr
                    return 1;
                }
            }
        }
    }
    catch (const LuaErrorException& e)
    {
        luaL_error(L, e.what());
        return 0;
    }
}

int lua::debugApi::destroyObject(lua_State* L)
{
    try
    {
        LuaWrapper w(L);
        luaExpectStackSize(L, 1);
        if (w.isTable(1))
        {
            luaError("Couldn't destroy object - first argument is a table (C++ owned object), not userdata");
            return 0;
        }
        void* ptr = luaGetObjectPtr(L, 1);
        if (!ptr)
        {
            luaError("Couldn't destroy object - pointer is null");
            return 0;
        }
        rttr::variant* var = reinterpret_cast<rttr::variant*>(lua_touserdata(L, 1));
        // sanity check
        if (!var->get_type().is_wrapper())
        {
            luaError("Couldn't destroy object - variant is not a wrapper, which means it's not a shared_ptr");
            return 0;
        }
        var->get_type().destroy(*var);
//         rttr::variant var = convertToObjectPointer(ptr, getLuaTableMetafieldOrError<std::string>(L, 1, "className"));
//         if (!var.is_valid())
//         {
//             luaError("Couldn't destroy object - couldn't convert to object pointer");
//             return 0;
//         }
//         var.get_type().destroy(var);
        // FIXME: will this work with pointers too, and delete pointed-to object, not 4-byte pointer primitive?
        return 0;
    }
    catch (const LuaErrorException& e)
    {
        luaL_error(L, e.what());
        return 0;
    }
}

// receives: [object, class name, field name]
int lua::debugApi::getClassObjectField(lua_State* L)
{
    try
    {
        auto className = getLuaTypeOrError<std::string>(L, 2);
        if (!Reflection::getClassObjectFieldToLuaStack(L, className, getLuaTypeOrError<std::string>(L, 3), convertToObjectPointer(luaGetObjectPtr(L, 1), className)))
        {
            luaError("Couldn't get field '{}' of class '{}'", getLuaTypeOrError<std::string>(L, 3), className);
            return 0;
        }
    }
    catch (const LuaErrorException& e)
    {
        //currentExceptionStr = e.what();
        //e.~LuaErrorException();
        // FIXME: exception object might not be destroyed (applies to all exception handlers like this one)
        //luaL_error(L, currentExceptionStr.data());
        luaL_error(L, e.what());
        return 0;
    }
    return 1;
}

// receives class name, field name
int lua::debugApi::getClassField(lua_State* L)
{
    try
    {
        LuaWrapper w(L);
        luaExpectStackSize(L, 2);
        std::string className = getLuaTypeOrError<std::string>(L, 1);
        rttr::type t = rttr::type::get_by_name(className);
        if (!t.is_valid())
        {
            luaError("Type '{}' is not registered", className);
            return 0;
        }
        else if (!t.is_class())
        {
            luaError("Couldn't get class '{}', it's not a class", className);
            return 0;
        }
        else
        {
            Reflection::getClassFieldToLuaStack(L, className, getLuaTypeOrError<std::string>(L, 2));
            return 1;
        }
    }
    catch (const LuaErrorException& e)
    {
        luaL_error(L, e.what());
        return 0;
    }
}

// receives global name
int lua::debugApi::getGlobalField(lua_State* L)
{
    try 
    {
        if (!Reflection::getGlobalVariableToLuaStack(L, getLuaTypeOrError<std::string>(L, 1)))
        {
            luaError("Couldn't get global '{}'", getLuaTypeOrError<std::string>(L, 1));
            return 0;
        }
    }
    catch (const LuaErrorException& ex)
    {
    	luaL_error(L, ex.what());
        return 0;
    }
    return 1;
}

int lua::debugApi::getClassObjectFieldPtr(lua_State* L)
{
    return 0;
}

int lua::debugApi::getClassFieldPtr(lua_State* L)
{
    return 0;
}

int lua::debugApi::getGlobalFieldPtr(lua_State* L)
{
    return 0;
}

// receives global name and value
int lua::debugApi::setGlobalField(lua_State* L)
{
    try
    {
        LuaWrapper w(L);
        luaExpectStackSize(L, 2);
        std::string name = getLuaTypeOrError<std::string>(L, 1);
        rttr::type t = rttr::type::get_by_name(name);
        if (!t.is_valid())
        {
            luaError("Global '{}' doesn't exist", name);
            return 0;
        }
        else if (t.is_class())
        {
            luaError("Couldn't set global '{}' - it's a class", name);
            return 0;
        }
        else
        {
            Reflection::setGlobalVariableFromLuaStack(L, name, 2);
            return 0;
        }
    }
    catch (const LuaErrorException& e)
    {
        luaL_error(L, e.what());
        return 0;
    }
}

// receives class name, function name, number of arguments, and arguments
int lua::debugApi::invokeClassMethod(lua_State* L)
{
    try 
    {
        LuaWrapper w(L);
        std::string className = getLuaTypeOrError<std::string>(L, 1);
        rttr::type t = rttr::type::get_by_name(className);
        if (!t.is_valid())
        {
            luaError("Type '{}' is not registered", className);
            return 0;
        }
        else if (!t.is_class())
        {
            luaError("Couldn't get class '{}' - it's not a class", className);
            return 0;
        }
        else
        {
            auto result = Reflection::callClassMethodWithLuaParams(L, className, getLuaTypeOrError<std::string>(L, 2), getLuaTypeOrError<int>(L, 3));
            if (!result)
            {
                luaError("Couldn't call method '{}' of class '{}'", getLuaTypeOrError<std::string>(L, 2), className);
                return 0;
            }
            else
            {
                Reflection::convertToLuaTypeOnStackByTypeId(L, result);
                return 1;
            }
        }
    }
    catch (const LuaErrorException& e)
    {
        luaL_error(L, e.what());
        return 0;
    }
}

// receives class name, class object, function name, number of arguments, and arguments
int lua::debugApi::invokeClassObjectMethod(lua_State* L)
{
    try
    {
        LuaWrapper w(L);
        std::string className = getLuaTypeOrError<std::string>(L, 1);
        rttr::type t = rttr::type::get_by_name(className);
        if (!t.is_valid())
        {
            luaError("Type '{}' is not registered", className);
            return 0;
        }
        else if (!t.is_class())
        {
            luaError("Couldn't get class '{}' - it's not a class", className);
            return 0;
        }
        else
        {
            rttr::variant var = convertToObjectPointer(luaGetObjectPtr(L, 2), className);
            if (!var.is_valid())
            {
                luaError("Couldn't convert class '{}' to object pointer", className);
                return 0;
            }
            else
            {
                auto result = Reflection::callClassObjectMethodWithLuaParams(L, var, getLuaTypeOrError<std::string>(L, 3), getLuaTypeOrError<int>(L, 4));
                if (!result)
                {
                    luaError("Couldn't call method '{}' of class '{}'", getLuaTypeOrError<std::string>(L, 3), className);
                    return 0;
                }
                else
                {
                    Reflection::convertToLuaTypeOnStackByTypeId(L, result);
                    return 1;
                }
            }
        }
    }
    catch (const LuaErrorException& e)
    {
        luaL_error(L, e.what());
        return 0;
    }
    
}

// receives function name, number of arguments, and arguments
int lua::debugApi::invokeGlobalMethod(lua_State* L)
{

    try 
    {
        LuaWrapper w(L);
        auto result = Reflection::callGlobalFunctionWithLuaParams(L, getLuaTypeOrError<std::string>(L, 1), getLuaTypeOrError<int>(L, 2));
        if (!result)
        {
            luaError("Couldn't call global function '{}'", getLuaTypeOrError<std::string>(L, 1));
            return 0;
        }
        else
        {
            Reflection::convertToLuaTypeOnStackByTypeId(L, result);
            return 1;
        }
    }
    catch (const LuaErrorException& ex)
    {
        luaL_error(L, ex.what());
        return 0;
    }
}

// receives object, class name, property name, value
int lua::debugApi::setClassObjectField(lua_State* L)
{
    try 
    {
        LuaWrapper w(L);
        luaExpectStackSize(L, 4);
        std::string className = getLuaTypeOrError<std::string>(L, 2);
        rttr::type t = rttr::type::get_by_name(className);
        if (!t.is_valid())
        {
            luaError("Type '{}' is not registered", className);
            return 0;
        }
        else if (!t.is_class())
        {
            luaError("Couldn't get class '{}', it's not a class", className);
            return 0;
        }
        else
        {
            rttr::variant var = convertToObjectPointer(luaGetObjectPtr(L, 1), className);
            if (!var.is_valid())
            {
                luaError("Couldn't get class '{}', couldn't convert to object pointer", className);
                return 0;
            }
            else
            {
                if (!Reflection::setClassObjectFieldFromLuaStack(L, var, getLuaTypeOrError<std::string>(L, 3), 4))
                {
                    luaError("Couldn't set field '{}' of class '{}'", getLuaTypeOrError<std::string>(L, 3), className);
                }
                return 0;
            }
        }
    }
    catch (const LuaErrorException& ex)
    {
        luaL_error(L, ex.what());
        return 0;
    }
}

// receives class name, property name, value
int lua::debugApi::setClassField(lua_State* L)
{
    try 
    {
        LuaWrapper w(L);
        luaExpectStackSize(L, 3);
        std::string className = getLuaTypeOrError<std::string>(L, 1);
        rttr::type t = rttr::type::get_by_name(className);
        if (!t.is_valid())
        {
            luaError("Type '{}' is not registered", className);
            return 0;
        }
        else if (!t.is_class())
        {
            luaError("Couldn't set field of type '{}' - it's not a class", className);
            return 0;
        }
        else
        {
            Reflection::setClassFieldFromLuaStack(L, className, getLuaTypeOrError<std::string>(L, 2), 3);
            return 1;
        }
    }
    catch (const LuaErrorException& ex)
    {
        luaL_error(L, ex.what());
        return 0;
    }
}

void insertPropertyAndMethodData(const rttr::array_range<rttr::property>& properties, const rttr::array_range<rttr::method>& methods, LuaTable& info)
{
    for (auto& prop : properties)
    {
        LuaTable propInfo;
        //fillInBasicTypeData(propInfo, prop.get_type());
        propInfo["name"] = prop.get_name().to_string();
        propInfo["type"] = getBasicTypeDataTable(prop.get_type());
        propInfo["isStatic"] = prop.is_static();
        propInfo["isConst"] = prop.is_readonly();
        propInfo["isField"] = true;
        propInfo["isMethod"] = false;
        // FIXME: no method-specific info is added for std::function

        //info.getTableFieldOrCreate("fields")[prop.get_name().to_string()] = propInfo;
        info.getTableFieldOrCreate("members")[prop.get_name().to_string()] = propInfo;
    }

    for (auto& method : methods)
    {
        LuaTable propInfo;
        //fillInBasicTypeData(propInfo, method.get_return_type());
        propInfo["name"] = method.get_name().to_string();
        propInfo["returnType"] = getBasicTypeDataTable(method.get_return_type());
        propInfo["isStatic"] = method.is_static();
        propInfo["isField"] = false;
        propInfo["isMethod"] = true;
        propInfo["isCallable"] = true;

        propInfo["params"] = getCallableParamsTable(method.get_parameter_infos());
        propInfo["signature"] = method.get_signature().to_string();

        //info.getTableFieldOrCreate("methods")[method.get_name().to_string()] = propInfo;
        info.getTableFieldOrCreate("members")[method.get_name().to_string()] = propInfo;
    }
}

// receives: class name
int lua::debugApi::getClassInfo(lua_State* L)
{
    try 
    {
	    luaExpectStackSize(L, 1);
	    std::string name = getLuaTypeOrError<std::string>(L, 1);
	    rttr::type t{ type::get_by_name(name) };
	    if (!t.is_valid())
	    {
	        luaError("Couldn't get class '{}'", name);
	        return 0;
	    }
	    else if (!t.is_class())
	    {
	        luaError("Couldn't get class '{}', it's not a class", name);
	        return 0;
	    }
	    /*
	    -- name, type, isConst, isReference, isPointer, isClass, isEnum, isStatic, isField, isMethod, isCallable
	    -- isCallable (for example std::function, functions as fields)
	    -- if isCallable, then also returnType, params [array of basic properties above + two extra fields: hasDefaultValue, defaultValue]
	    */
	    LuaTable info;
	    insertPropertyAndMethodData(t.get_properties(), t.get_methods(), info);
	
	    for (auto& ctor : t.get_constructors())
	    {
	        LuaTable propInfo;
	        //fillInBasicTypeData(propInfo, ctor.get_return_type());
	        propInfo["returnType"] = getBasicTypeDataTable(ctor.get_declaring_type()); // always same return value
	        propInfo["isField"] = false;
	        propInfo["isMethod"] = true;
	        propInfo["isCallable"] = true;
	
	        propInfo["params"] = getCallableParamsTable(ctor.get_parameter_infos());
	        propInfo["signature"] = ctor.get_signature().to_string();
	
	        info.getTableFieldOrCreate("constructors").arrayInsert(propInfo);
	    }
	
	    // bases, derived
	    LuaTable bases;
	    for (auto& base : t.get_base_classes())
	    {
	        bases.arrayInsert(base.get_name().to_string());
	    }
	    info["bases"] = bases;
	    LuaTable derived;
	    for (auto& derivedClass : t.get_derived_classes())
	    {
	        derived.arrayInsert(derivedClass.get_name().to_string());
	    }
	    info["derived"] = derived;
	
	    info.pushToLuaStack(L);
	    return 1;
    }
    catch (const LuaErrorException& ex)
    {
	    luaL_error(L, ex.what());
        return 0;
    }
}

int lua::debugApi::getGlobalEnvironmentInfo(lua_State* L)
{
    try 
    {
        LuaTable info;
        insertPropertyAndMethodData(rttr::type::get_global_properties(), rttr::type::get_global_methods(), info);
        info.pushToLuaStack(L);
        return 1;
    }
    catch (const LuaErrorException& ex)
    {
    	luaL_error(L, ex.what());
        return 0;
    }
}

// receives classObject, fieldName and accessPath
int lua::debugApi::getContainerSize(lua_State* L)
{
    return 0;
}

int lua::debugApi::getContainerElement(lua_State* L)
{
    return 0;
}

int lua::debugApi::setContainerElement(lua_State* L)
{
    return 0;
}

int lua::debugApi::clearContainer(lua_State* L)
{
    return 0;
}

int lua::debugApi::getContainerKeys(lua_State* L)
{
    return 0;
}

int lua::debugApi::getContainerValues(lua_State* L)
{
    return 0;
}
