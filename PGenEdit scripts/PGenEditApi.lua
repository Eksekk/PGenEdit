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
	end
end

local function funcWrapper(f, argTypes, retTypes)
	return function(...)
		local args = {...}
		for i, typ in ipairs(argTypes) do
			if typ == "object" then
				if type(args[i]) ~= "table" or not getmetatable(args[i]) or not getmetatable(args[i]).__className then
					error(format("Argument %d is not an object", i), 2)
				end
			elseif 
			end
		end
		local ret = {f(unpack(args))}
		for i = 1, #ret do
			if type(ret[i]) == "userdata" then
				ret[i] = api.makeObject(ret[i])
			end
		end
		return unpack(ret)
	end
end

-- creates metatable, which will be used to give object ability to access its fields and methods
local function createObjectMetatable(className)
	local mt = {}
	mt.__className = className
	function mt.__index(obj, key)
		assert(getmetatable(obj).__className == className, format("Received object of type %q, expected %q", getmetatable(obj).__className, className))
		if api.isMethodOfClass(className, key) then
			local f = api.makeMethodOfClass(className, key)
			rawset(obj, key, f)
			return f
		elseif api.isFieldOfClass(className, key) then
			return api.getFieldOfClass(obj, className, key)
		else
			error(format("Attempt to access unknown field %q of class %q", key, className))
		end
	end
	function mt.__newindex(obj, key, value)
		assert(getmetatable(obj).__className == className, format("Received object of type %q, expected %q", getmetatable(obj).__className, className))
		assert(not api.isMethodOfClass(className, key), format("Attempt to set method %q of class %q", key, className))
		api.setFieldOfClass(obj, className, key, value)
	end
	function mt.__new(...)
		local obj = api.createObject(className, ...)
		setmetatable(obj, mt)
		return obj
	end
	function mt.__gc(obj)
		api.destroyObject(obj)
	end
	function mt.__copy(...)
		local obj = api.copyObject(...)
		setmetatable(obj, mt)
		return obj
	end
	return mt
end

local function makeClass(name, ...)
	assert(api.classExists(name), format("Class %q does not exist", name))
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
			local f = api.makeStaticMethodOfClass(name, str)
			rawset(t, str, f)
			return f
		elseif api.isStaticFieldOfClass(name, str) then
			return api.getStaticFieldOfClass(name, str)
		else
			error(format("Attempt to access unknown static field %q of class %q", str, name))
		end
	end
	function classMT.__newindex(t, key, value)
		assert(not api.isStaticMethodOfClass(name, key), format("Attempt to set static method %q of class %q", key, name))
		if api.isStaticFieldOfClass(name, key) then
			api.setStaticFieldOfClass(name, key, value)
		else
			error(format("Attempt to set unknown static field %q of class %q", key, name))
		end
	end
	return classMT
end

local class = {}
pgenedit.class = class
local mt = {}
function mt.__index(t, key) -- if __index fires, this means that class is not yet created
	local classMT = makeClass(key)
	rawset(t, key, classMT)
	return classMT
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
		local f = api.makeGlobalFunction(key)
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