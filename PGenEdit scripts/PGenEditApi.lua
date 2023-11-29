local api = require("luaDebugApi")
local format = string.format

-- remaining to do:
-- 1. add support for enums
-- 2. add support for const methods
-- 3. add support for overloaded methods
-- 4. handle inheritance by performing lookup for fields in base classes
-- 5. provide a method to check if object is of a given class (or any of its derived classes)
-- 6. rich error messages for function wrapper (including parameter names and types)
-- 7. currently only userdata represents C++ objects. Since they are garbage-collected by Lua, it's possible to have objects with invalid state in C++ after some debug calls and gc execution. Need to add a way to create a "weak" object, which will not be garbage-collected by Lua, but will be destroyed only when object is destroyed from C++ side, and will be just as functional as a regular object (except for __gc metamethod, which will not be called).
-- Obviously need to use tables to represent such objects, since they too support metatables, and aren't garbage collected.
-- Such objects will be used, if user wants to keep a reference to an object, which is owned by C++ (global variable for example).
-- TODO: notify lua about object destruction from C++ side?

-- for functions need to handle:
-- 1. type checking for arguments and return types (including small value types range compatibility), C++ will also check this, but it's better to check it here too
-- 2. objects as arguments and return values
-- 3. error handling
-- 4. pass the number of arguments to C++ (for functions with default arguments or for checking if parameters are missing/extra)

-- minor style convention I adopted: functions in metatables should be qualified with __, for consistency with built-in metamethods, and also to disambiguate them from regular functions

pgenedit.debug.attemptTypeConversion = true -- if true, will attempt to convert parameters to correct type, if false, will throw an error

local cpp = tget(pgenedit, "cpp")

local makeClass
local class = {}
cpp.class = class
-- pgenedit.cpp.class
-- pgenedit.cpp.global
local classContainerMT = {}
function classContainerMT.__index(t, key) -- if __index fires, this means that class is not yet created
	local cls = makeClass(key)
	rawset(t, key, cls)
	return cls
end
function classContainerMT.__newindex(t, key, value)
	error(format("Attempt to set class %q", key), 2)
end
setmetatable(class, classContainerMT)
-- pgenedit.class.wxWindow.new("test", nil, 0, 0, 0, 0)

-- userdata are objects created by lua, tables are objects created by C++ (so no automatic garbage collection happens)
local function isClassObject(obj)
	return (type(obj) == "userdata" or type(obj) == "table") and getmetatable(obj) and getmetatable(obj).className
end

local function isObjectOfClassOrDerived(obj, checkName)
	if not isClassObject(obj) then
		return false
	end
	local objMT = getmetatable(obj)
	-- support both class name and class table
	checkName = type(checkName == "table") and getmetatable(checkName).name or checkName
	if objMT.className == checkName then -- same class
		return true
	elseif table.find(objMT.classMetatable.bases, checkName) then -- first-level base class
		return true
	elseif cpp.class[checkName] then -- check recursively for all base classes
		for i, name in ipairs(getmetatable(cpp.class[checkName]).bases) do
			if isObjectOfClassOrDerived(obj, name) then
				return true
			end
		end
	end
	return false
end

local function isCppObjectType(val)
	return (type(val) == "table" or type(val) == "userdata") and getmetatable(val) and getmetatable(val).className
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
		if type(value) ~= "userdata" orj not getmetatable(value) or not getmetatable(value).className then
			error(format(sNotAnObject, funcNameForMessage, paramIndex, value), 3)
		elseif getmetatable(cppTypeName).className ~= getmetatable(value).className and not isObjectOfClassOrDerived(value, cppTypeName) then
			error(format("'%s': Parameter %d (%q) is of invalid class (expected %q or any derived, got %q)", funcNameForMessage, paramIndex, expectedParamData.name, cppTypeName, getmetatable(value).className), 3)
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
local function funcWrapper(className, funcName, memberData)
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
			elseif type(this) ~= "userdata" and type(this) ~= "table" then
				error(format("Invalid object instance (first parameter), received %q", this), 2)
			elseif not getmetatable(this) then
				error(format("Object instance is not a valid object (no metatable)", this), 2)
			elseif getmetatable(this).className ~= className then
				error(format("Object instance is of invalid class (expected %q, got %q)", this, className, getmetatable(this).className), 2)
			end
		end
		return api.callMethod(className, funcName, #args, unpack(args))
	end
end

-- contrary to its name, for methods it uses rawset in addition to returning function, to cache the functions, because their creation might be expensive
-- as single table is used for all polymorphic objects, I can't use __index and __newindex metamethods to check for field existence, because I would have to call them manually from metatable (ugly)

-- FIXME: those functions don't actually check first class
local function currentOrInheritedMemberLookup(obj, key, className, treatAsClass, shouldBeStatic)
	-- since treatAsClass is passed only for first function call, we don't need to check the object hierarchy validity in subsequent calls, as it's already checked
	if not treatAsClass and getmetatable(obj).className ~= className and not isObjectOfClassOrDerived(obj, className) then
		error(format("Received object of type %q, expected %q", getmetatable(obj).className, className), 3)
	end
	local data = getmetatable(obj).getMemberData(key)
	if data.isField and data.isStatic == shouldBeStatic then -- current class has matching field
		return api.getFieldOfClass(obj, className, key)
	elseif data.isCallable and data.isStatic == shouldBeStatic then -- current class has matching method
		local f = funcWrapper(className, key, data)
		rawset(obj, key, f) -- cache future accesses to methods
		return f
	else
		 -- recursively check base classes
		local bases = getmetatable(treatAsClass and cpp.class[treatAsClass] or obj).bases
		for i, cls in ipairs(bases) do
			local val = currentOrInheritedMemberLookup(obj, key, className, cls, shouldBeStatic)
			if val ~= nil then -- if found, return the value
				return val
			end
		end
		-- otherwise continue to next base class
	end
end

-- now same as above, but for setting (__newindex), using behavior from below __newindex
-- returns if value was set somewhere in the hierarchy
local function currentOrInheritedMemberSet(obj, key, value, className, treatAsClass, shouldBeStatic)
	if not treatAsClass and getmetatable(obj).className ~= className and not isObjectOfClassOrDerived(obj, className) then
		error(format("Received object of type %q, expected %q", getmetatable(obj).className, className), 3)
	end
	local data = getmetatable(obj).getMemberData(key)
	if data.isField and data.isStatic == shouldBeStatic then -- base class has field
		api.setFieldOfClass(obj, className, key, value)
		return true
	elseif data.isMethod and data.isStatic == shouldBeStatic then -- base class has method
		error(format("Attempt to set method %q of class %q", key, className), 3)
	else
		-- recursively check base classes
		local bases = getmetatable(treatAsClass and cpp.class[treatAsClass] or obj).bases
		for i, cls in ipairs(bases) do
			if currentOrInheritedMemberSet(obj, key, value, className, cls, shouldBeStatic) then
				return true
			end
		end
		-- otherwise continue to next base class
	end
end

-- creates metatable, which will be used to give object ability to access its fields and methods
local function createObjectMetatable(classMT)
	local objMT = {}
	local className = classMT.name
	objMT.className = className
	objMT.classMetatable = classMT

	-- so, value can be either userdata or table
	-- with userdata passing the objects to C++ is easy, with table it's not
	-- probably best way is to have "?ptr" field which C++ will use

	-- C++ side to receive object should:
	-- put pointer to int (or anything else) inside variant, with value equal to table field "?ptr"
	-- convert the pointer internally to pointer to object (might need writing custom converter)
	-- somehow dereference the pointer

	function objMT.__index(obj, key)
		-- check for correct object type (inheritance won't change much, still original object is passed, just different metatable functions are called)
		local val = currentOrInheritedMemberLookup(obj, key)
		if val ~= nil then
			return val
		else
			error(format("Attempt to access unknown field %q of class %q", key, className), 2)
		end
	end

	function objMT.__newindex(obj, key, value)
		if not currentOrInheritedMemberSet(obj, key, value) then
			error(format("Attempt to set unknown field %q of class %q", key, className), 2)
		end
	end

	function objMT.__gc(obj)
		api.destroyObject(obj)
	end

	function objMT.__copy(this)
		local obj = api.copyObject(this)
		setmetatable(obj, objMT)
		return obj
	end
	-- TODO: dumpAllProperties (including functions shown clearly as such)
	-- TODO: readonly properties
	return objMT
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
	classMT.name = name
	classMT.bases = api.getClassBases(name) -- classes, which this class inherits from
	classMT.deriveds = api.getClassDeriveds(name) -- classes, which inherit from this class
	-- name, type, isConst, isReference, isPointer, isClass, isEnum, hasDefaultValue, defaultValue, isStatic
	-- isCallable (for example std::function, functions as fields), if so, then callableData field is function data like below, isField = true, isMethod = false
	local fields = api.getClassFieldInfo(name) -- array of field properties
	-- name, returnType, isConst, isVolatile, isStatic, isField = false, isMethod = true, isCallable = true
	local methods = api.getClassMethodInfo(name) -- array of method properties
	classMT.fields = fields -- important that it happens before createObjectMetatable, as it uses fields
	classMT.methods = methods -- this too
	local function getMemberData(name)
		return fields[name] or methods[name]
	end
	classMT.getMemberData = getMemberData

	local objMT = createObjectMetatable(classMT)
	classMT.objectMetatable = objMT
	local function new(...)
		-- TODO: find constructor matching parameters (count, types and possible conversions between types) and default arguments, if no matching constructor found, throw an error
		local obj = api.createObject(name, select("#", ...), ...)
		setmetatable(obj, objMT)
		return obj
	end
	classMT.__call = new
	classMT.new = new
	-- TODO: fields, methods in metatable - eliminate constant api calls?
	-- static variables
	function classMT.__index(t, str)
		local data = getMemberData(str)
		if data.isCallable and data.isStatic then
			local f = funcWrapper(name, str)
			rawset(t, str, f)
			return f
		elseif not data.isCallable and data.isStatic then
			return api.getStaticFieldOfClass(name, str)
		else
			error(format("Attempt to access unknown static field %q of class %q", str, name), 2)
		end
	end
	function classMT.__newindex(t, key, value)
		local data = getMemberData(key)
		-- changing callable members that aren't methods is not allowed, because they are not expecting possible lua errors/type differences from writing lua callback to be called from C++ via field
		assert(not data.isCallable, format("Attempt to set callable member %q of class %q", key, name), 2)
		if data.isStatic then
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