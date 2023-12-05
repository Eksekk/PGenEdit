local api = require("pgeneditDebugApi")
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
-- 8. BIG ONE: implement struct operators as metamethods if appropriate (for example, __add for operator+), and also implement __eq for all classes (for operator==)

-- for functions need to handle:
-- 1. type checking for arguments and return types (including small value types range compatibility), C++ will also check this, but it's better to check it here too
-- 2. objects as arguments and return values
-- 3. error handling
-- 4. pass the number of arguments to C++ (for functions with default arguments or for checking if parameters are missing/extra)

-- minor style convention I adopted: functions in metatables should be qualified with __, for consistency with built-in metamethods, and also to disambiguate them from regular functions

pgenedit = pgenedit or {}
--tget(pgenedit, "debug").attemptTypeConversion = true -- if true, will attempt to convert parameters to correct type, if false, will throw an error

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

-- TODO: this actually doesn't take into account derived classes!
local function isObjectOfClassOrDerived(obj, checkName)
	if not isClassObject(obj) then
		return false
	end
	local objMT = getmetatable(obj)
	-- support both class name and class table
	if checkName == nil then
		checkName = getmetatable(obj).className
	else
		checkName = type(checkName) == "table" and getmetatable(checkName).name or checkName
	end
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
	end
	if expectedParamData.isPointer then
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
		if type(value) ~= "userdata" or not getmetatable(value) or not getmetatable(value).className then
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
local function funcWrapper(className, memberName, memberData)
	local fullFuncName = className and format("%s::%s", className, memberName) or memberName
	local params = memberData.params
	assert(memberData.isCallable, format("'%s': Member %q is not callable", fullFuncName, memberData.name))

	local argCount, defCount = #params, getDefParamCount(params)
	assert(argCount >= defCount, format("'%s': Argument count (%d) is less than default argument count (%d)", fullFuncName, argCount, defCount))
	assert(#params == argCount, format("'%s': Argument type count (%d) is not equal to argument count (%d)", fullFuncName, #params, argCount))
	return function(...)
		local args = {...}
		if #args < argCount - defCount then
			error(format("'%s': Not enough arguments (expected at least %d, got %d)", fullFuncName, argCount - defCount, #args), 2)
		elseif #args > argCount then
			error(format("'%s': Too many arguments (expected at most %d, got %d)", fullFuncName, argCount, #args), 2)
		end
		if not memberData.isConstructor then
			for i = className and 2 or 1, #params do -- if class method, skip first argument, it's processed later
				local typ = params[i].type
				args[i] = validateOrConvertParameter(args[i], typ, i, fullFuncName)
			end
			-- if member is static or a field (std::function for example), then we don't need to process it
			if className and not memberData.isStatic and not memberData.isField then
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
		end
		-- convert objects to pointers if possible
		-- COMMENTED OUT, because C++ needs to know the exact type of passed object
		-- for i, arg in pairs(args) do
		-- 	args[i] = type(arg) == "table" and arg["?ptr"] or arg
		-- end
		if not className then -- global
			return api.invokeGlobalMethod(memberName, #args, unpack(args))
		elseif memberData.isStatic then -- static class method
			return api.invokeClassMethod(className, memberName, #args, unpack(args))
		else
			return api.invokeClassObjectMethod(args[1], className, memberName, #args, unpack(args))
		end
	end
end

-- TODO: Boost.PP for easy & nice definition of accessor getters/setters (and other macros)
-- contrary to its name, for methods it uses rawset in addition to returning function, to cache the functions, because their creation might be expensive
-- as single table is used for all polymorphic objects, I can't use __index and __newindex metamethods to check for field existence, because I would have to call them manually from metatable (ugly)

local function currentOrInheritedMemberLookup(obj, key, className, treatAsClassName, shouldBeStatic)
	-- since treatAsClass is passed only for first function call, we don't need to check the object hierarchy validity in subsequent calls, as it's already checked
	if not treatAsClassName and getmetatable(obj).className ~= className and not isObjectOfClassOrDerived(obj, className) then
		error(format("Received object of type %q, expected %q", getmetatable(obj).className, className), 3)
	end
	local data = getmetatable(obj).classMetatable.getMemberData(key)
	if data.isField and (shouldBeStatic == nil or data.isStatic == shouldBeStatic) then -- current class has matching field, or shouldBeStatic is not provided
		return api.getClassObjectField(obj, className, key)
	elseif data.isCallable and data.isStatic == shouldBeStatic then -- current class has matching method
		local f = funcWrapper(className, key, data)
		-- rawset(obj, key, f) -- cache future accesses to methods
		return f
	else
		 -- recursively check base classes
		local bases = treatAsClassName and getmetatable(cpp.class[treatAsClassName]) or getmetatable(obj).classMetatable.bases
		for i, cls in ipairs(bases) do
			local val = currentOrInheritedMemberLookup(obj, key, className, cls, shouldBeStatic)
			if val ~= nil then -- if found, return the value
				return val
			end
			-- otherwise continue to next base class
		end
	end
end

-- now same as above, but for setting (__newindex), using behavior from below __newindex
-- returns if value was set somewhere in the hierarchy
local function currentOrInheritedMemberSet(obj, key, value, className, treatAsClassName, shouldBeStatic)
	if not treatAsClassName and getmetatable(obj).className ~= className and not isObjectOfClassOrDerived(obj, className) then
		error(format("Received object of type %q, expected %q", getmetatable(obj).className, className), 3)
	end
	local data = getmetatable(obj).classMetatable.getMemberData(key)
	if data.isField and (shouldBeStatic == nil or data.isStatic == shouldBeStatic) then -- base class has field
		api.setClassObjectField(obj, className, key, value)
		return true
	elseif data.isMethod and data.isStatic == shouldBeStatic then -- base class has method
		error(format("Attempt to set method %q of class %q", key, className), 3)
	else
		-- recursively check base classes
		local bases = treatAsClassName and getmetatable(cpp.class[treatAsClassName]) or getmetatable(obj).classMetatable.bases
		for i, cls in ipairs(bases) do
			if currentOrInheritedMemberSet(obj, key, value, className, cls, shouldBeStatic) then
				return true
			end
			-- otherwise continue to next base class
		end
	end
end

-- creates metatable, which will be used to give object ability to access its fields and methods
local createObjectMetatable

-- call stack: user code -> pgenedit.class index -> makeClass -> createObjectMetatable
-- !!! if called from __index or __newindex of metatable, then stack is: user code -> our function (max 2 depth)

--[[local ]]function makeClass(className, ...)
	if className == nil then
		error("Class name is nil", 3)
	elseif not api.classExists(className) then
		error(format("Class %q does not exist", className), 3)
	end
	
	local classMT = {}
	classMT.name = className
	local info = api.getClassInfo(className)
	-- name, type, isConst, isReference, isPointer, isClass, isEnum, hasDefaultValue, defaultValue, isStatic, isField, isMethod, isCallable
	-- isCallable (for example std::function, functions as fields)
	-- returnType
	local members = info.members -- array of field properties
	classMT.bases = info.bases -- classes, which this class inherits from
	classMT.derived = info.derived -- classes, which inherit from this class
	classMT.members = members -- important that it happens before createObjectMetatable, as it uses members
	local function getMemberData(memberName)
		return members[memberName]
	end
	classMT.getMemberData = getMemberData

	local objMT = createObjectMetatable(classMT)
	classMT.objectMetatable = objMT
	local function new(...)
		-- TODO: find constructor matching parameters (count, types and possible conversions between types) and default arguments, if no matching constructor found, throw an error
		local obj = api.createObject(className, select("#", ...), ...)
		debug.setmetatable(obj, objMT) -- FIXME: you can't set a metatable of userdata without using debug library, so C++ needs to do it
		return obj
	end
	classMT.__call = function(t, ...)
		return new(...)
	end
	classMT.new = new
	-- static variables
	function classMT.__index(t, str)
		-- handling this here, because I don't want to make overwriting the field possible
		if str == "new" then
			return new
		end
		local data = getMemberData(str)
		if not data then
			error(format("Attempt to access unknown static field %q of class %q", str, className), 2)
		end
		if data.isCallable and data.isStatic then
			local f = funcWrapper(className, str, data)
			--rawset(t, str, f)
			return f
		elseif not data.isCallable and data.isStatic then
			return api.getClassField(className, str)
		else
			error(format("Attempt to access unknown static field %q of class %q", str, className), 2)
		end
	end
	function classMT.__newindex(t, key, value)
		local data = getMemberData(key)
		if not data then
			error(format("Attempt to set unknown static field %q of class %q", key, className), 2)
		end
		-- changing callable members that aren't methods is not allowed, because they are not expecting possible lua errors/type differences from writing lua callback to be called from C++ via field
		assert(not data.isCallable, format("Attempt to set callable member %q of class %q", key, className), 2)
		if data.isStatic then
			api.setClassField(className, key, value)
		else
			error(format("Attempt to set unknown static field %q of class %q", key, className), 2)
		end
	end
	return setmetatable({}, classMT)
end

--[[local ]]function createObjectMetatable(classMT)
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
		local val = currentOrInheritedMemberLookup(obj, key, className)
		if val ~= nil then
			return val
		else
			error(format("Attempt to access unknown field %q of class %q", key, className), 2)
		end
	end

	function objMT.__newindex(obj, key, value)
		if not currentOrInheritedMemberSet(obj, key, value, className) then
			error(format("Attempt to set unknown field %q of class %q", key, className), 2)
		end
	end

	function objMT.__gc(obj)
		-- destroy only objects created by lua
		if type(obj) == "userdata" then
			api.destroyObject(obj)
		end
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

-- now global functions/variables
local global = {}
cpp.global = global
local mt = {}
setmetatable(global, mt)
local members = api.getGlobalEnvironmentInfo()
mt.members = members
function mt.__index(t, key)
	local data = members[key]
	if not data then
		error(format("Attempt to access unknown global function/variable %q", key), 2)
	end
	if data.isCallable then
		local f = funcWrapper(nil, key, data)
		--rawset(t, key, f) -- commented out, because std::function fields might theoretically change their value
		return f
	elseif data.isField then
		return api.getGlobal(key)
	end
end

function mt.__newindex(t, key, value)
	local data = members[key]
	if not data then
		error(format("Attempt to set unknown global function/variable %q", key))
	end
	if data.isCallable then
		error(format("Attempt to set global callable %q", key), 2)
	end
	api.setGlobal(key, value)
end

-- tests
function tests()
	local stru = cpp.class.ReflectionSampleStruct.new()
	local errors = {}
	local function addError(level, fmt, ...)
		local info = debug.getinfo(level + 1, "l")
		local msg = format("[line %d]: ", info.currentline) .. format(fmt, ...)
		table.insert(errors, msg)
	end
	local function assert(cond, ...)
		if not cond then
			addError(2, ...)
		end
	end
	local function defCmp(a, b)
		return a == b
	end
	local function testGetProp(name, value, cmpFunc)
		local val = stru[name]
		cmpFunc = cmpFunc or defCmp
		if not cmpFunc(val, value) then
			addError(2, "stru.%s == %q, expected %q", name, val, value)
		end
	end
	local function testSetProp(name, value, cmpFunc)
		stru[name] = value
		cmpFunc = cmpFunc or defCmp
		local val = stru[name]
		if not cmpFunc(val, value) then
			addError(2, "stru.%s == %q, expected %q", name, val, value)
		end
	end

	local function cmpArrayVector(a, b)
		if #a ~= #b then
			return false
		end
		for i, v in ipairs(a) do
			if v ~= b[i] then
				return false
			end
		end
		return true
	end
	local function cmpAssociativeContainer(a, b)
		for k, v in pairs(a) do
			if v ~= b[k] then
				return false
			end
		end
		local countB = 0 -- "b" may have more or less keys than "a", of which all existing in "a" happen to compare equal
		for k, v in pairs(b) do
			countB = countB + 1
		end
		return countB == #a
	end
	local function mmv(a, b, c)
		local v = select(mmv - 5, a, b, c)
		_G.assert(v ~= nil)
		return v
	end

	-- get/set property tests
	testGetProp("i", 0)
	testGetProp("str", "default")
	testSetProp("i", 1)
	testSetProp("str", "test")
	testSetProp("i", 837248237)
	testSetProp("str", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaatest")
	testGetProp("vec", {1, 2, 3}, cmpArrayVector)
	testGetProp("arr", {1, 2, 3, 4, 5}, cmpArrayVector)
	testGetProp("map", {a = 1, b = 2, c = 3}, cmpAssociativeContainer)
	-- TODO: implement sets: testGetProp("set", {1, 2, 3}, cmpAssociativeContainer)
	testSetProp("vec", {4, 5, 6}, cmpArrayVector)
	testSetProp("arr", {6, 5, 4, 3, 2}, cmpArrayVector)
	testSetProp("map", {a = 3, b = 2, c = 1}, cmpAssociativeContainer)
	testSetProp("map", {akey = 4434, bkey = 5525, ckey = 66536}, cmpAssociativeContainer)
	-- TODO: map test with different key/value types

	-- test different instance
	local struOld = stru
	stru = cpp.class.ReflectionSampleStruct() -- use call syntax for object creation
	testGetProp("i", 0)
	testGetProp("str", "default")
	testGetProp("vec", {1, 2, 3}, cmpArrayVector)
	testGetProp("arr", {1, 2, 3, 4, 5}, cmpArrayVector)
	testGetProp("map", {a = 1, b = 2, c = 3}, cmpAssociativeContainer)
	stru = struOld

	-- function call tests

	stru.modifyMultiple(3, "cddd", {5, 6})
	testGetProp("i", 3)
	testGetProp("str", "cddd")
	testGetProp("vec", {5, 6})
	-- adds or inserts
	stru.modifyMultipleByOperation(88, "ap", {1})
	testGetProp("i", 91)
	testGetProp("str", "cdddap")
	testGetProp("vec", {5, 6, 1})

	assert(stru.get5() == 5, "[1st] stru.get5() == %d, expected 5", stru.get5())
	assert(stru.get5() == 5, "[2nd] stru.get5() == %d, expected 5", stru.get5())

	-- globals
	local global = cpp.global
	-- static int __declspec(naked) __fastcall fastcallGlobalFunctionTest(int argEcx, int argEdx, int argEsp)
	-- has to have values 0x77777777, 0x3333333, 0x88888888
	-- returns index of first nonmatching argument or 0 if all match
	local function fastcallGlobalFunctionTest(argEcx, argEdx, argEsp)
		return global.fastcallGlobalFunctionTest(argEcx, argEdx, argEsp)
	end
	assert(fastcallGlobalFunctionTest(0x77777777, 0x3333333, 0x88888888) == 0, "fastcallGlobalFunctionTest(0x77777777, 0x3333333, 0x88888888) == %d, expected 0", fastcallGlobalFunctionTest(0x77777777, 0x3333333, 0x88888888))
	assert(fastcallGlobalFunctionTest(0x0, 0x1, 0x2) == 1, "fastcallGlobalFunctionTest(0x0, 0x1, 0x2) == %d, expected 1", fastcallGlobalFunctionTest(0x0, 0x1, 0x2))
	assert(fastcallGlobalFunctionTest(0x77777777, 0x0, 0x2) == 2, "fastcallGlobalFunctionTest(0x77777777, 0x0, 0x2) == %d, expected 2", fastcallGlobalFunctionTest(0x77777777, 0x0, 0x2))
	assert(fastcallGlobalFunctionTest(0x77777777, 0x3333333, 0x0) == 3, "fastcallGlobalFunctionTest(0x77777777, 0x3333333, 0x0) == %d, expected 3", fastcallGlobalFunctionTest(0x77777777, 0x3333333, 0x0))
	local MMVER = global.MMVER
	assert(MMVER == Game.Version, "MMVER == %d, expected %d", MMVER, Game.Version)
	local inGame = global.inGame
	assert(inGame == internal.InGame, "inGame == %s, expected %s", tostring(inGame), tostring(internal.InGame))
	local playersFullArray = global.PlayersFullArray
	for i = 0, Game.PlayersArray.Count do
		assert(playersFullArray[i] == Game.PlayersArray[i], "playersFullArray[%d] == %s, expected %s", i, tostring(playersFullArray[i]), tostring(Game.PlayersArray[i]))
	end

	-- throw error tests
	local function shouldThrow(func, condStr, ...)
		local ok = pcall(func, ...)
		if ok then
			assert("%q did not throw an error", func, condStr)
		end
	end

	-- getting/setting nonexisting properties should throw error
	shouldThrow(function() local v = stru.nonexisting end, "stru.nonexisting")
	shouldThrow(function() stru.nonexisting = 1 end, "stru.nonexisting = 1")
	-- reassigning functions should throw error
	shouldThrow(function() stru.get5 = 1 end, "stru.get5 = 1")
	shouldThrow(function() stru.modifyMultiple = function() end end, "stru.modifyMultiple = function() end")

	-- assignment to array which changes amount of elements should throw lua error
	shouldThrow(function() stru.arr = {1, 2, 3, 4, 5, 6, 7, 8} end, "stru.arr = {1, 2, 3, 4, 5, 6, 7, 8}")
	-- can't define new globals
	shouldThrow(function() global.newGlobal = 1 end, "global.newGlobal = 1")
	-- or get values of nonexisting globals
	shouldThrow(function() local v = global.newGlobal end, "global.newGlobal")
	-- can't get classes as globals
	shouldThrow(function() local v = global.ReflectionSampleStruct end, "global.ReflectionSampleStruct")
	-- or set them
	shouldThrow(function() global.ReflectionSampleStruct = 1 end, "global.ReflectionSampleStruct = 1")
	inGame = internal.InGame
	-- setting invalid value types should throw error
	shouldThrow(function() global.inGame = 1 end, "global.inGame = 1")
	shouldThrow(function() global.inGame = "test" end, "global.inGame = \"test\"")
	global.inGame = inGame -- just in case, restore original value

	-- test inner classes
	-- indexing a class field which is another class should return a table type with "?ptr" set
	local innerStruct = stru.innerStruct
	assert(type(innerStruct) == "table", "type(innerStruct) == %q, expected %q", type(innerStruct), "table")
	assert(type(innerStruct["?ptr"]) == "number", "type(innerStruct[\"?ptr\"]) == %q, expected %q", type(innerStruct["?ptr"]), "number")
	assert(innerStruct["?ptr"] ~= 0, "innerStruct[\"?ptr\"] == %d, expected nonzero", innerStruct["?ptr"])
	assert(getmetatable(innerStruct).className == "InnerStruct", "getmetatable(innerStruct).className == %q, expected %q", getmetatable(innerStruct).className, "InnerStruct")

	--[[
		struct InnerStruct
{
    bool b, bb, bbb;
    std::string str;
    void allTrue()
    {
        b = true, bb = true, bbb = true;
    }
    void allFalse()
    {
        b = false, bb = false, bbb = false;
    }

    InnerStruct() : b(false), bb(false), bbb(false), str("default") {}
    // default copy ctor
    InnerStruct(const InnerStruct&) = default;
    InnerStruct(InnerStruct&&) = default;
    InnerStruct& operator=(const InnerStruct&) = default;
    InnerStruct& operator=(InnerStruct&&) = default;

    // virtual methods
    virtual int returnSizeof() const
    {
        return sizeof(InnerStruct);
    }

    // in derived class will return double the value
    virtual int addAllArguments(int a, int b, int c, int d) const
    {
        return a + b + c + d;
    }

    // an operator which modifies the struct based on int argument passed to it
    InnerStruct& operator+=(int val)
    {
        str += std::to_string(val);
        return *this;
    }

    InnerStruct operator+(int val) const
    {
        InnerStruct u2(*this);
        u2.str += std::to_string(val);
        return u2;
    }

    friend std::string to_string(const InnerStruct& u);

    // comparison operator for all fields
    bool operator==(const InnerStruct& other) const
    {
        return b == other.b && bb == other.bb && bbb == other.bbb && str == other.str;
    }

    RTTR_ENABLE()
};
	]]
	local struOld = stru
	stru = innerStruct
	testGetProp("b", false)
	testGetProp("bb", false)
	stru.allTrue()
	testGetProp("b", true)
	testGetProp("bb", true)
	testGetProp("bbb", true)
	testSetProp("b", false)
	stru.allFalse()
	testGetProp("b", false)
	testGetProp("bb", false)
	testGetProp("str", "default")
	testSetProp("str", "test")
	testGetProp("str", "test")
	assert(stru.addAllArguments(1, 2, 3, 4) == 10, "stru.addAllArguments(1, 2, 3, 4) == %d, expected 10", stru.addAllArguments(1, 2, 3, 4))

	--[[
		// few constructors with default arguments
ReflectionSampleStruct(bool b, int i = 20, char ch = 'a') : ReflectionSampleStruct() // this call also initializes other fields with default values
{
    this->i = i + b;
    str = std::string(1, ch);
    vec = { 1, 2, 3 };
    arr = { 1, 2, 3, 4, 5 };
    map = { {"a", 1}, {"b", 2}, {"c", 3} };
    u = { 0 };
}

ReflectionSampleStruct(int a, int b, int c = 5, int d = 20) : ReflectionSampleStruct()
{
    i = a + b + c + d;
    str = "default";
    vec = { 1, 2, 3 };
    arr = { 1, 2, 3, 4, 5 };
    map = { {"a", 1}, {"b", 2}, {"c", 3} };
    u = { 0 };
}
	]]
	stru = cpp.class.ReflectionSampleStruct.new(true)
	testGetProp("i", 21)
	testGetProp("str", "a")
	testGetProp("vec", {1, 2, 3}, cmpArrayVector)
	stru = cpp.class.ReflectionSampleStruct.new(false, 5)
	testGetProp("i", 5)
	testGetProp("str", "a")
	-- the other constructor
	stru = cpp.class.ReflectionSampleStruct.new(1, 2)
	testGetProp("i", 28)
	testGetProp("str", "default")

	stru = cpp.class.ReflectionSampleStruct.new(2, 3, 4)
	testGetProp("i", 29)
	stru = cpp.class.ReflectionSampleStruct.new(2, 3, 4, 5)
	testGetProp("i", 14)
	-- more arguments should throw
	shouldThrow(function() stru = cpp.class.ReflectionSampleStruct.new(2, 3, 4, 5, 6) end, "cpp.class.ReflectionSampleStruct.new(2, 3, 4, 5, 6)")

	stru = struOld

	-- void setArrayWithDefaultArgs(int a, int b, int c = 12, int d = 33, int e = -5)
	stru.setArrayWithDefaultArgs(1, 2)
	testGetProp("arr", {1, 2, 12, 33, -5}, cmpArrayVector)
	stru.setArrayWithDefaultArgs(1, 2, 3)
	testGetProp("arr", {1, 2, 3, 33, -5}, cmpArrayVector)

	local inner = cpp.class.InnerStruct.new()
	local inner2 = cpp.class.InnerStruct2.new()

	-- basic virtual function test, TODO: more complex tests
	assert(inner.returnSizeof() ~= inner2.returnSizeof(), "inner.returnSizeof() == %d, inner2.returnSizeof() == %d, expected different values", inner.returnSizeof(), inner2.returnSizeof())
	-- derived class "addAllArguments" should return double the value
	assert(inner.addAllArguments(1, 2, 3, 4) == 10, "inner.addAllArguments(1, 2, 3, 4) == %d, expected 10", inner.addAllArguments(1, 2, 3, 4))
	assert(inner2.addAllArguments(1, 2, 3, 4) == 20, "inner2.addAllArguments(1, 2, 3, 4) == %d, expected 20", inner2.addAllArguments(1, 2, 3, 4))

	-- basic inheritance test
	-- inner2 should have members and methods of inner
	struOld = stru
	stru = inner2
	testGetProp("b", false)
	testGetProp("bb", false)
	stru.allTrue()
	testGetProp("b", true)
	testGetProp("bb", true)
	testGetProp("bbb", true)
	stru = struOld
end