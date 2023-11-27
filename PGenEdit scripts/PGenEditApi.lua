local api = require("luaDebugApi")
local format = string.format

-- for functions need to handle:
-- 1. type checking for arguments and return types (including small value types range compatibility), C++ will also check this, but it's better to check it here too
-- 2. objects as arguments and return values
-- 3. error handling
-- 4. pass the number of arguments to C++ (for functions with default arguments or for checking if parameters are missing/extra)

pgenedit.debug.attemptTypeConversion = true -- if true, will attempt to convert parameters to correct type, if false, will throw an error

local integerTypeRanges = 
{
	["char"] = {min = -128, max = 127},
	["unsigned char"] = {min = 0, max = 255},
	["short"] = {min = -32768, max = 32767},
	["unsigned short"] = {min = 0, max = 65535},
	["int"] = {min = -2147483648, max = 2147483647},
	["unsigned int"] = {min = 0, max = 4294967295},
	["long"] = {min = -2147483648, max = 2147483647},
	["unsigned long"] = {min = 0, max = 4294967295},
	["long long"] = {min = -9223372036854775808, max = 9223372036854775807},
	["unsigned long long"] = {min = 0, max = 18446744073709551615},
}

local sIntOutOfRange = "'%s': Parameter %d is out of range for type %q (value is %d)"
local sCantConvertToNumber = "'%s': Parameter %d (%q) is not a number and can't be converted to it"
local sCantConvertToBoolean = "'%s': Parameter %d (%q) is not a boolean and can't be converted to it"
local sCantConvertToString = "'%s': Parameter %d (%q) is not a string and can't be converted to it"
local sCantConvertToTable = "'%s': Parameter %d (%q) is not a table and can't be converted to it"
local sNotAnObject = "Argument %d (%q) is not an object [userdata]"
local function validateOrConvertParameter(value, typ, paramIndex, funcName)
	local conv = pgenedit.debug.attemptTypeConversion
	if integerTypeRanges[typ] then
		if type(value) == "number" then
			if value < integerTypeRanges[typ].min or value > integerTypeRanges[typ].max then
				error(format(sIntOutOfRange, funcName, paramIndex, typ, value), 3)
			end
			return value
		elseif conv then
			if type(value) == "boolean" then
				return value and 1 or 0
			elseif value == nil then
				return 0
			elseif type(value) == "string" then
				local num = tonumber(value)
				if num then
					if num < integerTypeRanges[typ].min or num > integerTypeRanges[typ].max then
						error(format(sIntOutOfRange, funcName, paramIndex, typ, num), 3)
					end
					return num
				end
			end
		end
		error(format(sCantConvertToNumber, funcName, paramIndex, value), 3)
	elseif typ == "float" or typ == "double" or typ == "long double" then
		if type(value) == "number" then
			return value
		elseif conv then
			if type(value) == "boolean" then
				return value and 1 or 0
			elseif value == nil then
				return 0
			elseif type(value) == "string" then
				local num = tonumber(value)
				if num then
					return num
				end
			end
		end
		error(format(sCantConvertToNumber, funcName, paramIndex, value), 3)
	elseif typ == "bool" then
		if type(value) == "boolean" then
			return value
		-- TODO: consider if always doing nil -> false conversion, regardless of conv, is a good idea
		elseif conv then
			if type(value) == "number" then
				return value ~= 0
			elseif value == nil then
				return false
			elseif type(value) == "string" then
				if value == "true" then
					return true
				elseif value == "false" then
					return false
				end
			end
		end
		error(format(sCantConvertToBoolean, funcName, paramIndex, value), 3)
	elseif typ == "string" then -- for std::string, const char* and std::string_view
		if type(value) == "string" then
			return value
		elseif conv then
			if value == nil then
				return ""
			elseif type(value) == "boolean" then
				return value and "true" or "false"
			elseif type(value) == "number" then
				return tostring(value)
			end
		end
		error(format(sCantConvertToString, funcName, paramIndex, value), 3)
	elseif typ == "table" then
		if type(value) == "table" then
			return value
		elseif conv then
			if value == nil then
				return {}
			end
		end
		error(format(sCantConvertToTable, funcName, paramIndex, value), 3)
	elseif typ == "nil" then -- shouldn't ever happen
		error(format("'%s': Parameter %d requested type is 'nil'", funcName, paramIndex), 3)
	elseif typ == "object" then
		if type(value) ~= "userdata" or not getmetatable(value) or not getmetatable(value).__className then
			error(format(sNotAnObject, funcName, paramIndex, value), 3)
		end
	end
end

-- if className is nil, then it's treated as a global/static function
local function funcWrapper(className, funcName)
	local paramInfos = api.getMethodArgumentInfos(className, funcName)
	-- single parameter table has following fields:
	-- name - as it appears in C++ code
	-- type - for objects of any kind it's "object", specific type name will be stored in className
	-- className - only for class objects, name of the class
	-- hasDefaultValue - true if parameter has default value
	-- defaultValue - default value, if hasDefaultValue is true
	-- isConst
	-- isReference
	-- isPointer

	-- isStatic
	-- isEnum
	-- isClass
	-- isFunction
	-- isMethod
	-- isField
	-- isVariable
	-- isGlobal
	-- isStaticMethod
	-- isStaticField
	local argTypes = api.getMethodArgumentTypes(className, funcName)
	local argCount, defCount = api.getMethodArgumentCount(className, funcName), api.getDefaultArgumentCount(className, funcName)
	assert(argCount >= defCount, format("'%s': Argument count (%d) is less than default argument count (%d)", funcName, argCount, defCount))
	assert(#argTypes == argCount, format("'%s': Argument type count (%d) is not equal to argument count (%d)", funcName, #argTypes, argCount))
	return function(...)
		local args = {...}
		if #args < argCount - defCount then
			error(format("'%s': Not enough arguments (expected at least %d, got %d)", funcName, argCount - defCount, #args), 2)
		elseif #args > argCount then
			error(format("'%s': Too many arguments (expected at most %d, got %d)", funcName, argCount, #args), 2)
		end
		for i = className and 2 or 1, #argTypes do -- if class method, skip first argument, it's processed later
			local typ = argTypes[i]
			args[i] = validateOrConvertParameter(args[i], typ, i, funcName)
		end
		if className then
			local this = args[1]
			if not api.classExists(className) then
				error(format("Class %q does not exist", className), 2)
			elseif type(this) ~= "userdata" then
				error(format("Invalid object instance (first parameter), received %q", this), 2)
			elseif not getmetatable(this) then
				error(format("Object instance is not a valid object (no metatable)", this), 2)
			elseif getmetatable(this).__className ~= className then
				error(format("Object instance is of invalid class (expected %q, got %q)", this, className, getmetatable(this).__className), 2)
			end
		end
		return api.callMethod(className, funcName, #args, unpack(args))
	end
end

-- creates metatable, which will be used to give object ability to access its fields and methods
local function createObjectMetatable(className)
	local mt = {}
	mt.__className = className
	function mt.__index(obj, key)
		if getmetatable(obj).__className ~= className then
			error(format("Received object of type %q, expected %q", getmetatable(obj).__className, className), 2)
		end
		if api.isMethodOfClass(className, key) then
			local f = funcWrapper(className, key)
			rawset(obj, key, f)
			return f
		elseif api.isFieldOfClass(className, key) then
			return api.getFieldOfClass(obj, className, key)
		else
			error(format("Attempt to access unknown field %q of class %q", key, className), 2)
		end
	end
	function mt.__newindex(obj, key, value)
		if getmetatable(obj).__className ~= className then
			error(format("Received object of type %q, expected %q", getmetatable(obj).__className, className), 2)
		end
		if api.isMethodOfClass(className, key) then
			error(format("Attempt to set method %q of class %q", key, className), 2)
		elseif not api.isFieldOfClass(className, key) then
			error(format("Attempt to set unknown field %q of class %q", key, className), 2)
		end
		api.setFieldOfClass(obj, className, key, value)
	end
	function mt.__new(...)
		-- TODO: find constructor matching parameters (count, types and possible conversions between types) and default arguments, if no matching constructor found, throw an error
		local obj = api.createObject(className, ...)
		setmetatable(obj, mt)
		return obj
	end
	function mt.__gc(obj)
		api.destroyObject(obj)
	end
	function mt.__copy(this)
		local obj = api.copyObject(this)
		setmetatable(obj, mt)
		return obj
	end
	-- TODO: dumpAllProperties (including functions shown clearly as such)
	-- TODO: readonly properties
	return mt
end

-- call stack: user code -> pgenedit.class index -> makeClass -> createObjectMetatable
-- !!! if called from __index or __newindex of metatable, then stack is: user code -> our function (max 2 depth)

local function makeClass(name, ...)
	if name == nil then
		error("Class name is nil", 3)
	elseif not api.classExists(name) then
		error(format("Class %q does not exist", name), 3)
	end
	local classMT = {}
	local objMT = createObjectMetatable(name)
	classMT.objectMetatable = objMT
	classMT.__call = function(...)
		return objMT.__new(...)
	end
	classMT.new = function(...)
		return objMT.__new(...)
	end
	-- static variables
	function classMT.__index(t, str)
		if api.isStaticMethodOfClass(name, str) then
			local f = funcWrapper(name, str)
			rawset(t, str, f)
			return f
		elseif api.isStaticFieldOfClass(name, str) then
			return api.getStaticFieldOfClass(name, str)
		else
			error(format("Attempt to access unknown static field %q of class %q", str, name), 2)
		end
	end
	function classMT.__newindex(t, key, value)
		assert(not api.isStaticMethodOfClass(name, key), format("Attempt to set static method %q of class %q", key, name), 2)
		if api.isStaticFieldOfClass(name, key) then
			api.setStaticFieldOfClass(name, key, value)
		else
			error(format("Attempt to set unknown static field %q of class %q", key, name), 2)
		end
	end
	return setmetatable({}, classMT)
end

local class = {}
pgenedit.class = class
local mt = {}
function mt.__index(t, key) -- if __index fires, this means that class is not yet created
	local cls = makeClass(key)
	rawset(t, key, cls)
	return cls
end
function mt.__newindex(t, key, value)
	error(format("Attempt to set class %q", key), 2)
end
setmetatable(class, mt)
-- pgenedit.class.wxWindow.new("test", nil, 0, 0, 0, 0)

-- now global functions/variables
local global = {}
pgenedit.global = global
local mt = {}
setmetatable(global, mt)
function mt.__index(t, key)
	if api.isGlobalFunction(key) then
		local f = funcWrapper(nil, key)
		rawset(t, key, f)
		return f
	elseif api.isGlobalVariable(key) then
		return api.getGlobalVariable(key)
	else
		error(format("Attempt to access unknown global function/variable %q", key))
	end
end

function mt.__newindex(t, key, value)
	assert(not api.isGlobalFunction(key), format("Attempt to set global function %q", key))
	if api.isGlobalVariable(key) then
		api.setGlobalVariable(key, value)
	else
		error(format("Attempt to set unknown global variable %q", key))
	end
end

-- these calls are just to make code above not grayed out
createObjectMetatable()
makeClass()
validateOrConvertParameter()