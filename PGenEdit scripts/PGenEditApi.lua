local api = require("luaDebugApi")
local format = string.format

-- remaining to do:
-- 1. add support for enums
-- 2. add support for const methods
-- 3. add support for overloaded methods
-- 4. handle inheritance by performing lookup for fields in base classes
-- 5. provide a method to check if object is of a given class (or any of its derived classes)
-- 6. rich error messages for function wrapper (including parameter names and types)

-- for functions need to handle:
-- 1. type checking for arguments and return types (including small value types range compatibility), C++ will also check this, but it's better to check it here too
-- 2. objects as arguments and return values
-- 3. error handling
-- 4. pass the number of arguments to C++ (for functions with default arguments or for checking if parameters are missing/extra)

pgenedit.debug.attemptTypeConversion = true -- if true, will attempt to convert parameters to correct type, if false, will throw an error

local cpp = tget(pgenedit, "cpp")

local makeClass
local class = {}
cpp.class = class
-- pgenedit.cpp.class
-- pgenedit.cpp.global
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

local function isClassOrDerived(this, checkName)
	local mt = getmetatable(this) or {}
	-- support both class name and class metatable
	checkName = type(checkName == "table") and checkName.__name or checkName
	if mt.__className == checkName then -- same class
		return true
	elseif table.find(mt.bases, checkName) then
		return true
	elseif cpp.class[checkName] then
		for i, name in ipairs(getmetatable(cpp.class[checkName]).bases) do
			if isClassOrDerived(this, name) then
				return true
			end
		end
	end
	return false
end

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
--error(format(sCantConvertToNumber, funcNameForMessage, paramIndex, value), 3)
local sIntOutOfRange = "'%s': Parameter #%d is out of range for type %q (value is %d)"
local genericParamFormatStr = "'%s': Parameter #%d (%q) of type %q and value %q can't be converted to C++ type %q"
local sNotAnObject = "Argument #%d (%q) is not an object [userdata]"
local function validateOrConvertParameter(value, cppType, paramIndex, funcNameForMessage)
	local expectedParamData = cppType
	local expectedCppTypeStr = expectedParamData.type
	if expectedParamData.isClass then
		expectedCppTypeStr = expectedParamData.type
	elseif expectedParamData.isPointer then
		expectedCppTypeStr = expectedCppTypeStr .. "*"
	elseif expectedParamData.isReference then
		expectedCppTypeStr = expectedCppTypeStr .. "&"
	elseif expectedParamData.isConst then
		expectedCppTypeStr = "const " .. expectedCppTypeStr
	end
	local conv = pgenedit.debug.attemptTypeConversion
	local cppTypeName = cppType.name
	if integerTypeRanges[cppTypeName] then
		if type(value) == "number" then
			if value < integerTypeRanges[cppTypeName].min or value > integerTypeRanges[cppTypeName].max then
				error(format(sIntOutOfRange, funcNameForMessage, paramIndex, cppTypeName, value), 3)
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
					if num < integerTypeRanges[cppTypeName].min or num > integerTypeRanges[cppTypeName].max then
						error(format(sIntOutOfRange, funcNameForMessage, paramIndex, cppTypeName, num), 3)
					end
					return num
				end
			end
		end
		--local genericParamFormatStr = "'%s': Parameter #%d (%q) of type %q and value %q can't be converted to C++ type %q"
		error(format(genericParamFormatStr, funcNameForMessage, paramIndex, expectedParamData.name, type(value), value, expectedCppTypeStr), 3)
	elseif cppTypeName == "float" or cppTypeName == "double" or cppTypeName == "long double" then
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
		error(format(genericParamFormatStr, funcNameForMessage, paramIndex, expectedParamData.name, type(value), value, expectedCppTypeStr), 3)
	elseif cppTypeName == "bool" then
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
		error(format(genericParamFormatStr, funcNameForMessage, paramIndex, expectedParamData.name, type(value), value, expectedCppTypeStr), 3)
	elseif cppTypeName == "string" then -- for std::string, const char* and std::string_view
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
		error(format(genericParamFormatStr, funcNameForMessage, paramIndex, expectedParamData.name, type(value), value, expectedCppTypeStr), 3)
	elseif cppTypeName == "table" then
		if type(value) == "table" then
			return value
		elseif conv then
			if value == nil then
				return {}
			end
		end
		error(format(genericParamFormatStr, funcNameForMessage, paramIndex, expectedParamData.name, type(value), value, expectedCppTypeStr), 3)
	elseif cppTypeName == "nil" then -- shouldn't ever happen
		error(format("'%s': Parameter #%d (%q) of type %q and value %q: requested C++ type is 'nil'", funcNameForMessage, paramIndex, expectedParamData.name, type(value), value), 3)
	elseif expectedParamData.isClass then
		if type(value) ~= "userdata" or not getmetatable(value) or not getmetatable(value).__className then
			error(format(sNotAnObject, funcNameForMessage, paramIndex, value), 3)
		elseif getmetatable(cppTypeName).__className ~= getmetatable(value).__className and not isClassOrDerived(value, cppTypeName) then
			error(format("'%s': Parameter %d (%q) is of invalid class (expected %q or any derived, got %q)", funcNameForMessage, paramIndex, expectedParamData.name, cppTypeName, getmetatable(value).__className), 3)
		else
			return value
		end
	end
end

local function getDefParamCount(params)
	local defCount = 0
	for i = #params, 1, -1 do
		if params[i].hasDefaultValue then
			defCount = defCount + 1
		else
			break
		end
	end
	return defCount
end

-- if className is nil, then it's treated as a global/static function
local function funcWrapper(className, funcName)
	local fullFuncName = className and format("%s::%s", className, funcName) or funcName
	local params = api.getMethodArgumentInfo(className, funcName)
	-- single parameter table can have following fields:
	-- name - as it appears in C++ code
	-- type - if isClass is true, then this is class name, otherwise it's type name
	-- hasDefaultValue - true if parameter has default value
	-- defaultValue - default value, if hasDefaultValue is true
	-- isClass
	-- isConst
	-- isReference
	-- isPointer

	-- in the future:
	-- isEnum
	local argTypes = api.getMethodArgumentTypes(className, funcName)
	local argCount, defCount = #params, getDefParamCount(params)
	assert(argCount >= defCount, format("'%s': Argument count (%d) is less than default argument count (%d)", fullFuncName, argCount, defCount))
	assert(#argTypes == argCount, format("'%s': Argument type count (%d) is not equal to argument count (%d)", fullFuncName, #argTypes, argCount))
	return function(...)
		local args = {...}
		if #args < argCount - defCount then
			error(format("'%s': Not enough arguments (expected at least %d, got %d)", fullFuncName, argCount - defCount, #args), 2)
		elseif #args > argCount then
			error(format("'%s': Too many arguments (expected at most %d, got %d)", fullFuncName, argCount, #args), 2)
		end
		for i = className and 2 or 1, #argTypes do -- if class method, skip first argument, it's processed later
			local typ = argTypes[i]
			args[i] = validateOrConvertParameter(args[i], typ, i, fullFuncName)
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
local function createObjectMetatable(classMT)
	local mt = {}
	local className = classMT.__name
	mt.__className = className
	mt.classMetatable = classMT
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

--[[local ]]function makeClass(name, ...)
	if name == nil then
		error("Class name is nil", 3)
	elseif not api.classExists(name) then
		error(format("Class %q does not exist", name), 3)
	end
	local classMT = {}
	classMT.__name = name
	local objMT = createObjectMetatable(classMT)
	classMT.objectMetatable = objMT
	classMT.__call = function(...)
		return objMT.__new(...)
	end
	classMT.new = function(...)
		return objMT.__new(...)
	end
	classMT.bases = api.getClassBases(name) -- classes, which this class inherits from
	classMT.deriveds = api.getClassDeriveds(name) -- classes, which inherit from this class
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

-- now global functions/variables
local global = {}
cpp.global = global
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