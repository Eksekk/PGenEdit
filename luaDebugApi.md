# Design of lua debug api
It's gonna be a set of tables with metatables for inspecting C++ types, invoking functions, getting/setting fields etc. I will also try to make it able to do basically everything that is registered through RTTR.
- there will be ability to get values of global variables, as well as set them
- similar to above, there will be ability to call global/static functions
- for the above and classes, metamethods will intercept read/write attempts and call C++ code to do the actual work, or throw error if it's not possible
- for the above, C++ code will receive, optionally, the object on which the operation is performed, as well as the string key (for fields, this includes functions) or arguments (for functions any number, for get 0, for set 1)

## class interface
- creating dynamic class objects will work, they will be implemented as userdata with metatable
- calling methods on class objects will be supported, they will modify their appropriate object if needed
- getting/setting fields will be supported, setting will modify its object
- __gc metamethod will be used to destroy objects when they are no longer needed

simple sketch of the implementation:
```lua
local api = require("luaDebugApi")
local format = string.format

local classObjectMT = {name = "<unknown>"}

local function createObjectMetatable(name, ...)
	local mt = {}
	mt.__index = mt
	mt.__name = name
	mt.__new = function(...)
		local obj = api.createObjectOfClass(name, ...)
		setmetatable(obj, mt)
		return obj
	end
	mt.__gc = function(obj)
		api.destroyObject(obj)
	end
	return mt
end

local function makeClass(name, ...)
	local mt = createObjectMetatable(name, ...)
	mt.__call = function(...)
		return mt.__new(...)
	end
	return mt
end

local class = {}
pgenedit.class = class
-- pgenedit.class.wxWindow.new("test", nil, 0, 0, 0, 0)
function classMT.new(...)
	local obj = api.createObjectOfClass(classMT.name, ...)
	setmetatable(obj, classObjectMT)
	return obj
end

function classObjectMT.__index(obj, key)
	assert(getmetatable(obj) == classObjectMT, format("Received object of type %s, expected %s", getmetatable(obj).name, classMT.name))
	return api.getFieldOfClass(obj, classMT.name, key)
end
```

## Misc
- need to support explicit error types on the C++ side, so that first C++ function called by lua either catches C++ exception or gets error code, and then throws lua error with appropriate message
- to avoid undefined behavior with longjmp, each lua call must be pcall **directly in the function that calls lua code** (so that longjmp won't have potential to skip destructors of stack objects of functions on the call stack, causing UB)
- this function will then either return error code or throw C++ exception, which will be caught by the first C++ function called by lua, and this function will then throw lua error with appropriate message back to the lua code (need to take care of stack objects of first functions, call destructors manually or don't use nontrivial objects or do all real work in second called function?)

## Later
- I want it to be as easy to use as possible, so I will try to make it as close to lua as possible (that means ability to pass arguments as table, get return values as table etc.)