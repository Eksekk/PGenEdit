#pragma once
#include "main.h"

// basic strategy:
// 
// store each real function in registry subtable, and store some sort of access path to that function in this class
// keys need to be unique, use lua_topointer for it? (might cause problems if function is garbage collected and then another function is created with same address)
// store some useful function metadata in this class (debug.getinfo if capturing lua function, or just function name/optional parameter types/etc. if capturing C++ function)
// C++ functions pushed to stack should be callable from lua, assuming that parameters passed happen to match function signature, but that will take way too much time, so only do this if required
// calling from C++ side will probably require vector of LuaValue, and return vector of LuaValue (possibly with a boolean indicating whether function call succeeded) - use LuaWrapper for that
// class should be reference-counted, and copy constructor and copy assignment operator should return object containing the same underlying data

// registry -> pgenedit -> functions -> [some sort of unique key] -> function [together with metadata]

class LuaValue;
using LuaFunctionReturn = std::pair<bool, std::vector<LuaValue>>;
using LuaFunctionArgs = std::vector<LuaValue>;
class LuaFunction
{
	lua_State* L;
public:
	LuaFunctionReturn operator()(const LuaFunctionArgs& args) const;
	
	// TODO: capture any C++ callable (function pointer, std::function, lambda, etc.)

	lua_Debug debugInfo;

	// ALTERNATIVE TO declaring functions with extern "C" to register them in lua, which can't be done with lambdas and anything other than raw function pointers, so it would be unsuitable for this class:
	// use pushcclosure to push a single static C function multiple times, giving it a different upvalue each time (serving as marker of what to call), and then store that upvalue in this class and use that single function with upvalue to dispatch dynamically?
};

