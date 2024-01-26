#pragma once
#include "main.h"
#include "LuaRegistryPersistableValue.h"

// make lua functions callable directly by C++ and able to be stored in variables, and make C++ functions callable by lua and able to be stored in variables

// basic strategy for C++ calling lua:
// 
// store each real function in registry subtable, and store some sort of access path to that function in this class
// keys need to be unique, use lua_topointer for it? (might cause problems if function is garbage collected and then another function is created with same address)
// store some useful function metadata in this class (debug.getinfo if capturing lua function, or just function name/optional parameter types/etc. if capturing C++ function)
// C++ functions pushed to stack should be callable from lua, assuming that parameters passed happen to match function signature, but that will take way too much time, so only do this if required
// calling from C++ side will probably require vector of LuaValue, and return vector of LuaValue (possibly with a boolean indicating whether function call succeeded) - use LuaWrapper for that
// class should be reference-counted, and copy constructor and copy assignment operator should return object containing the same underlying data

// basic strategy for lua calling C++:
// provide callable extern "C" wrapper for lua with upvalue, which:
// setups try-catch block to catch lua errors and propagate them from top level of C++ code
// automatically gets function from registry, validates/converts parameters, calls function, and converts return value to lua

// will be used to extract return type and parameter types from C++ callables
// first definition prevents "template argument list is not allowed in declaration of primary template" error
template<typename ReturnType, typename... Args>
struct FunctionSignature;

template<typename Ret, typename... Args>
struct FunctionSignature<std::function<Ret(Args...)>>
{
	using ReturnType = Ret;
	using ArgsTuple = std::tuple<Args...>;
};

template<typename Callable>
struct FunctionMetadata
{
	static constexpr bool isMemberFunction = std::is_member_function_pointer_v<Callable>;
};

template<typename Callable>
using GetFunctionSignature = FunctionSignature<decltype(std::function{ std::declval<Callable>() })>;

class LuaValue;
using LuaFunctionReturn = std::pair<bool, std::vector<LuaValue>>; // first is whether function call succeeded, second is return value
using LuaFunctionArgs = std::vector<LuaValue>; // arguments to pass to lua function
class LuaFunction : public LuaRegistryPersistableValue
{
	lua_State* L;
	std::string name; // optional
public:
	LuaFunctionReturn operator()(const LuaFunctionArgs& args) const; // uses pcall by default
	std::vector<LuaValue> callUnprotected(const LuaFunctionArgs& args) const; // uses call by default

	// TODO: capture any C++ callable (function pointer, std::function, lambda, etc.)

	lua_Debug getDebugInfo() const;

	// ALTERNATIVE TO declaring functions with extern "C" to register them in lua, which can't be done with lambdas and anything other than raw function pointers, so it would be unsuitable for this class:
	// use pushcclosure to push a single static C function multiple times, giving it a different upvalue each time (serving as marker of what to call), and then store that upvalue in this class and use that single function with upvalue to dispatch dynamically?

	LuaFunction(lua_State* L, int index, const std::string& name = "<unknown>");
	LuaFunction(const std::vector<LuaValue>& accessPath, int firstElemIndex = LUA_GLOBALSINDEX, const std::string& name = "<unknown>");
	LuaFunction(const LuaFunction& other);

	template<typename Callable>
	LuaFunction(lua_State* L, Callable&& callable, const std::string& name = "<unknown>")
	{
		using Signature = GetFunctionSignature<Callable>;
		static_assert(requires { typename Signature::ReturnType; typename Signature::ArgsTuple; });
		using Metadata = FunctionMetadata<Callable>;
	}

	void luaFunctionInit();

	void fetchFromRegistry();
	void persistInRegistry() const;
};