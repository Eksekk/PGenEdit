function reload()
	dofile("Scripts/Global/GenerateStructInfo.lua")
end
local mmver = offsets.MMVersion
local function mm78(...)
	local r = select(mmver - 6, ...)
	assert(r ~= nil)
	return r
end
local _DEBUG = true
--[[
	> dump(structs, 1)
	-- interesting stuff:
   	class = function: 0x0329b2d8,\ -- class with custom methods and "new" method
	enum = function: 0x0329b338,\ -- for iterating over struct instance's properties
	f = table: 0x03259168,\ -- definition functions
	m = table: 0x032591f0,\ -- member handler functions (handle every access and write to it)
	name = function: 0x0329b450,\ -- gets struct name from its class
	o = table: 0x032591c8\ -- offsets of all members
	
	-- also:
	
	mem.structs.types
	mem.structs.types.u4
	mem.structs.types.array -- etc.
	
	-- a lot of info is stored in upvalues
	-- debug.getinfo also was useful in one case
]]

-- constants
local skipBitsText = "SKIPBITS(%d);"
local skipBytesText = "SKIP(%d);"
local INDENT_CHARS = "\t"
local types = mem.structs.types
local namespaceStr = "mm" .. _G.offsets.MMVersion .. "::"
local commonTypeNamesToCpp = 
{
	u1 = "uint8_t",
	u2 = "uint16_t",
	u4 = "uint32_t",
	u8 = "uint64_t",
	i1 = "int8_t",
	i2 = "int16_t",
	i4 = "int32_t",
	i8 = "int64_t",
	r4 = "float",
	r8 = "double",
	r10 = "long double",
	b1 = "bool",
}
local extra = -- extra fields in structs
{
	Player =
	{
		{games = {7, 8}, data = {offset = structs.o.Player.FireResistanceBase + 18, name = "LightResistanceBase", typeName = commonTypeNamesToCpp.i2, size = 2} },
		{games = {7, 8}, data = {offset = structs.o.Player.FireResistanceBase + 20, name = "DarkResistanceBase", typeName = commonTypeNamesToCpp.i2, size = 2} },
		{games = {7, 8}, data = {offset = structs.o.Player.FireResistanceBase + 22 + 18, name = "LightResistanceBonus", typeName = commonTypeNamesToCpp.i2, size = 2} },
		{games = {7, 8}, data = {offset = structs.o.Player.FireResistanceBase + 22 + 20, name = "DarkResistanceBonus", typeName = commonTypeNamesToCpp.i2, size = 2} },
	}
}
local globalReplacements = {class = "clas", ["if"] = "if_", ["else"] = "else_"}
local arraysToPointers =
{
	[7] =
	{
		SpritesLod = {"SpritesSW"}
	}
}
local arraysToPointersCurrentGame = arraysToPointers[Game.Version]
local booleanHandlers = {
	[getUpvalue(mem.structs.types.b1, "handler")] = 1,
	[getUpvalue(mem.structs.types.b2, "handler")] = 2,
	[getUpvalue(mem.structs.types.b4, "handler")] = 4,
}
local bitIndex = {}
local bit = 1
for i = 0, 7 do
	bitIndex[bit] = i
	bit = bit * 2
end
local AnyABitHandler = getU(getU(types.abit, "doBit"), "AnyABitHandler")

local luaData = {}
local function setBaseTypeField(data, field, value) -- if there are arrays, skips them
	local data2 = data
	while data2.array do
		data2 = data2.innerType
	end
	data2[field] = value
end
local function getBaseTypeField(data, field)
	local data2 = data
	while data2.array do
		data2 = data2.innerType
	end
	return data2[field]
end
local getGroup

-- helper functions
-- DEFINED IN EksekkStuff.lua
--[[
all possible attributes:
- array - is array
	- beyondLen - access beyond length (???)
	- count - number of elements
	- size - full array size (product of count and all child array counts and base type size)
	- low - first element index (usually 0 or 1)
	- innerType - return value from recursive call
- typeName - data type name
- constValue - value of this member can't be changed
- formatTypeName - %s is embedded in string and represents member name and thus must be formatted
- ptr - is ptr to something (array, character string, structure etc.)
- constPtr - pointer can't be changed
- size
- bit - is bit
	- bitValue - used for named bits (like structs.Item.Stolen)
	- bitIndex - index of bit in little endian starting from 0 (bit 0x200 of container 0xFE84 would have index 14), used only with named bits
	- bigEndian - used with bit arrays
	- anti - is anti bit (if you access a bit (0-7) with index 2, anti bit index is (7 - 2) = 5), used only with unnamed bits
- comments - table of strings
- struct - is struct (or pointer to it if ptr is set)
- commentOut - self-explanatory, used for custom types with 0 size
- [added in processStruct] ptrValue - pointer with set value
]]
local function getMemberData(structName, memberName, member, offsets, members, class, rofields, customFieldSizes, inArray)
	rofields = rofields or {}
	member = member or members[memberName]
	local data = {name = memberName or "", offset = offsets[memberName or ""] or 0}
	local function addComment(s)
		data.comments = data.comments or {}
		table.insert(data.comments, s)
	end
	if type(memberName) == "number" then
		data.name = "_" .. memberName
	end
	local protFunc = getU(member, "f0")
	if protFunc then
		addComment("Requires unprotect before change")
		member = protFunc
	end
	local up = debug.upvalues(member)
	local arrayHandler = up.f
	local boolsize = booleanHandlers[member] -- boolean
	local memArr = up.arr -- mem arrays etc.
	local sname = (type(arrayHandler) == "table" and arrayHandler or {})[internal.structs_name_t] -- structure
	local EditPChar_newindex, EditConstPChar_newindex = getmetatable(mem.EditPChar).__newindex, getmetatable(mem.EditConstPChar).__newindex
	local bitValue = up.b
	local isAutoValueBit = up.bitHandlers and true or false -- bit without specifying value (contiguous), used in arrays
	local stringLen = up.len
	local unionOffsets = up.offs
	data.constValue = memberName and (tostring(memberName):len() > 0) and (table.find(rofields, memberName) ~= nil)
	if unionOffsets then
		data.union, data.offsets, data.fields, data.rofields = true, unionOffsets, up.fields, up.rofields
		
		-- assume union offset is minimum offset among its fields
		local offset = 0xFFFFFFFF
		for k, v in pairs(data.offsets) do
			offset = math.min(offset, v)
		end
		data.offset = offset
		data.dataType = types.union
	elseif up.count then -- array
		data.array = true
		data.innerType = getMemberData(structName, memberName, arrayHandler, offsets, members, class, rofields, customFieldSizes, true)
		if data.innerType.replaceWith then
			data.replaceWith = data.innerType.replaceWith
			return data
		end
		data.ptr = up.ptr
		data.lenP = up.lenP
		data.lenA = data.lenP and getU(MT(up.lenA).__index, "size")
		data.beyondLen = up.beyondLen
		data.count = up.count == 0xFFFFFFFF and 0 or up.count
		if data.beyondLen then
			addComment("AccessBeyondLength is active (???)")
		end
		data.low = up.low
		if data.low and data.low > 0 then
			addComment(string.format("MMExt: %d..%d, here %d..%d", data.low, data.low + data.count - 1, 0, data.count - 1))
		end
		data.size = ((data.ptr or data.count == 0) and 4 or data.count * up.size)
		if data.innerType.size and up.size > data.innerType.size then
			data.innerType.padding = up.size - data.innerType.size
		end
		if data.innerType.bit then
			local bytes = data.count:div(8)
			data.count = bytes
			addComment("array of " .. (data.innerType.anti and "abits (real index = 7 - usual)" or "bits"))
			data.size = bytes
		else
			data.size = (data.ptr or data.count == 0) and 4 or math.ceil(data.count * data.innerType.size)
		end
		data.dataType = data.ptr and types.parray or types.array
		-- change array to pointer
		if arraysToPointersCurrentGame and arraysToPointersCurrentGame[structName] and table.find(arraysToPointersCurrentGame[structName], data.name) then
			table.insert(tget(luaData, structName, arraysToPointersCurrentGame[structName]), data.name)
			setBaseTypeField(data, "addPointer", true)
			setBaseTypeField(data, "static", true)
			return data.innerType -- replace current array with pointer
		end
			
		--if data.innerType.bit then debug.Message(dump(data.innerType)) end
	elseif stringLen then -- string (fixed size, not pointer)
		data.array = true
		data.count = stringLen
		data.low = 0
		data.size = data.count
		data.innerType = {typeName = "char", name = memberName, offset = 0, size = 1}
		addComment(up.NoZero and "doesn't require null terminator" or "requires null terminator")
		data.dataType = types.string
	elseif bitValue then
		data.size = 1/8
		local b, o = bitValue, 0
		while b >= 256 do
			b = b / 256
			o = o + 1
		end
		data.bitIndex = o * 8 + (7 - bitIndex[b] or error("Not a valid bit", 1))
		data.typeName = "bool %s : 1"
		data.formatTypeName = true
		data.bit = true
		data.dataType = types.bit
	elseif isAutoValueBit then
		data.size = 1/8
		data.bit = true
		if inArray then
			data.bigEndian = true
			data.typeName = "uint8_t"
		else
			data.typeName = "bool %s : 1"
			data.formatTypeName = true
		end
		data.anti = member == AnyABitHandler -- is anti bit (if you access a bit (0-7) with index 2, anti bit index is (7 - 2) = 5)
		data.dataType = data.anti and types.abit or types.bit
	elseif getUpvalueByValue(member, EditPChar_newindex) then
		data.size = 4
		data.typeName = "char"
		data.ptr = true
		data.dataType = types.editpchar
	elseif getUpvalueByValue(member, EditConstPChar_newindex) then
		data.size = 4
		data.typeName = "char"
		data.ptr = true
		addComment("unprotect before/protect after edit")
		data.dataType = types.editconstpchar
	elseif boolsize then
		if boolsize == 1 then
			data.typeName = "bool"
		else
			data.typeName = boolsize == 2 and commonTypeNamesToCpp.u2 or commonTypeNamesToCpp.u4
			addComment(boolsize .. "-byte boolean")
		end
		data.size = boolsize
		data.dataType = types["b" .. boolsize]
	elseif memArr then
		local found
		for _, name in ipairs{"u1", "u2", "u4", "u8", "i1", "i2", "i4", "i8", "r4", "r8", "r10"} do
			if memArr == mem[name] then
				data.typeName = commonTypeNamesToCpp[name]
				data.size = tonumber(name:sub(2))
				found = true
				data.dataType = types[name]
				break
			end
		end
		if memArr == mem.pchar then
			data.size = 4
			data.typeName = "char"
			data.ptr = true
			data.constPtr = true
			data.constValue = true
			data.dataType = types.pchar
			found = true
		end
		found = found or error("Unknown mem array type")
	elseif sname then -- struct or pstruct
		if sname == "PlayerResistanceBaseBonus" then
			local ro = table.find(rofields, memberName)
			local newBase, newBonus = "ResistanceBase", "ResistanceBonus"
			data.replaceWith =
			{
				{
					offset = data.offset, array = true, count = 11, low = 0, size = 22, name = newBase, constValue = ro, dataType = types.array, innerType =
					{
						typeName = commonTypeNamesToCpp.i2, offset = data.offset, size = 2, name = newBase, constValue = ro, dataType = types.i2
					},
				},
				{
					offset = data.offset + 22, array = true, count = 11, low = 0, size = 22, name = newBonus, constValue = ro, dataType = types.array, innerType =
					{
						typeName = commonTypeNamesToCpp.i2, offset = data.offset + 22, size = 2, name = newBonus, constValue = ro, dataType = types.i2
					},
				},
			}
			return data
			--data.size = 4
		end
		local isPtr = up.pstruct
		data.typeName = sname
		data.ptr = isPtr
		data.struct = true
		data.size = isPtr and 4 or structs[sname]["?size"]
		data.dataType = isPtr and types.pstruct or types.struct
	else
		print(string.format("Warning: unknown type structs.%s.%s encountered!", structName, memberName))
		data.array = true
		data.innerType = {size = 1, typeName = commonTypeNamesToCpp.u1, name = memberName}
		data.count = customFieldSizes[memberName] or error("Unknown custom type name: " .. memberName, 2)
		if data.count == 0 then
			--data.count = 1
			data.commentOut = true
			data.innerType.commentOut = true
			addComment("real size is 0")
		end
		data.low = 0
		data.size = data.count
		addComment("Unknown type")
	end
	return data
end

--[[
remaining to do:
f = {  -- table: 0x02e88ff0\
},\
func = function: 0x02e19fb8,\
goto = function: 0x02ea5550,\

i8x = function: 0x02e91a80,\
iany = function: 0x02e91728,\
indexmember = function: 0x02e19948,\
m = table: 0x02e88ff0,\
method = function: 0x02e19f90,\
newindexmember = function: 0x02e19968,\
u8x = function: 0x02e91b30,\
uany = function: 0x02e916e8,\
vmethod = function: 0x02e19fe0\
--]]

function getArrayPointerString(arrays, last, addPointer) -- for testing: https://cdecl.org/
	local stdArray = "std::array<%s, %d>"
	--if last.bit then debug.Message(dump(arrays), dump(last)) end
	local type, name = last.typeName .. (last.ptr and "*" or "") .. (addPointer and "*" or "") .. (last.constPtr and "const" or ""), last.name
	for i = #arrays, 1, -1 do
		local arr = arrays[i]
		if arr.count == 0 then
			if arr.ptr then
				type = type .. "*"
			else
				--str = "(" .. str .. ")" .. "[]" -- commented out because it clutters up code in overwhelming majority of the cases
				type = type .. "*"
			end
		else
			type = stdArray:format(type, arr.count) .. (arr.ptr and "*" or "")
			-- std::array<std::array<uint8_t, 128>*, 128> heightMap;
		end
	end
	return type .. " " .. name
end
local function toCamelCase(str)
	local twoUpper = str:len() >= 2 and str:sub(1, 2):upper() == str:sub(1, 2)
	str = twoUpper and str or (str:sub(1, 1):lower() .. (str:len() >= 2 and str:sub(2) or ""))
	str = globalReplacements[str] or str
	return str
end

local firstPaddingProcessed
local function processSingle(data, indentLevel, structName, namespaceStr)
	debugTable(data)
	indentLevel = indentLevel or 0
	local indentOuter, indentInner = string.rep(INDENT_CHARS, indentLevel), string.rep(INDENT_CHARS, indentLevel + 1)
	local dataCopy = data
	
	local s = indentOuter
	
	-- collect array info and get to base type
	local arrays, comments = {}, {}
	while data.array do
		comments = table.join(comments, data.comments or {})
		arrays[#arrays + 1] = {ptr = data.ptr, count = data.count, low = data.low}
		data = data.innerType
	end
	local addPointer = data.addPointer
	if #arrays == 0 then arrays = nil end
	
	data.name = tostring(data.name)
	-- use camel case (I personally prefer it)
	local name = toCamelCase(data.name)
	data.name = name
	-- arrays taken care of

	local function doBaseType(doArrays)
		local result = data.static and "static " or ""
		-- structure, mem array, edit pchars, bools, bits
		if data.constValue then
			result = result .. "const "
		end
		if data.formatTypeName then
			result = result .. data.typeName:format(data.name)
		else
			if arrays and doArrays then
				result = result .. getArrayPointerString(arrays, data, addPointer)
				if data.ptrValue then
					result = result .. string.format(" = 0x%X", data.ptrValue)
				end
			else
				result = result .. data.typeName .. (data.ptr and "*" or "") .. (addPointer and "*" or "") .. " " .. data.name
				if data.ptrValue then
					result = result .. string.format(" = 0x%X", data.ptrValue)
				end
			end
		end
		local offset = arrays and arrays[1] and arrays[1].offset or data.offset or 0
		table.insert(tget(data, "comments"), string.format(".%d, 0x%X", offset, offset))
		if data.commentOut then
			result = "// " .. result
		end
		return result
	end
	if data.union then
		local code = data.code
		s = {}
		for i, v in ipairs(code) do
			s[i] = indentOuter .. code[i]
		end
	elseif arrays and #arrays == 1 and data.padding then -- NPCTopic, NPCText - element size 4, "real" size 8, overlapping
		local structName = "__" .. data.name
		local old1 = data.name
		data.name = "value"
		s = {
			indentOuter .. "struct " .. structName,
			indentOuter .. "{",
			indentInner .. 		doBaseType(false) .. ";",
			indentInner .. 		skipBytesText:format(data.padding),
			indentOuter .. "};"
		}
		if firstPaddingProcessed then
			firstPaddingProcessed = false
			s[3], s[4] = s[4], s[3]
		else
			firstPaddingProcessed = true
		end
		local offset = arrays and arrays[1] and arrays[1].offset or data.offset or 0
		data.name = old1
		local old2, old3 = data.typeName, data.ptr -- hacky hacky
		data.typeName = structName
		data.ptr = nil
		s[#s + 1] = indentOuter .. doBaseType(true) .. ";"
		data.typeName, data.ptr = old2, old3
	else
		if data.padStart then
			s = {
				indentOuter .. "struct " .. structName,
				indentOuter .. "{",
				indentInner .. 		skipBytesText:format(data.padStart),
				indentInner .. 		doBaseType(true) .. ";",
				indentOuter .. "};"
			}
		else
			s = s .. doBaseType(true)
		end
	end
	if not data.padding then firstPaddingProcessed = false end
	comments = table.join(comments, data.comments or {})
	local commentsStr = #comments > 0 and (" // " .. table.concat(comments, " | ")) or ""
	if type(s) == "table" then
		s[#s] = s[#s] .. commentsStr
	else
		s = s .. ";" .. commentsStr
	end
	if _DEBUG and not data.static then
		local off = arrays and arrays[1] and arrays[1].offset or data.offset or 0
		local formatStr = "%sstatic_assert(offsetof(%s, %s) == %d);"
		if off ~= 0 and structName and not data.bit then
			if type(s) == "table" then
				s[#s + 1] = formatStr:format(indentOuter, namespaceStr .. structName, data.name, off)
			else
				s = s .. "\n" .. formatStr:format(indentOuter, namespaceStr .. structName, data.name, off)
			end
		end
	end
	data = dataCopy
	return s
end

local function processGroup(group, indentLevel, structName, namespaceStr)
	-- messing around
	--setmetatable(getfenv(1), {__index = function(t, k) if not xxx then print(k); return rawget(t, k) end end})
	indentLevel = indentLevel or 0
	if #group == 1 then
		return {processSingle(group[1], indentLevel, structName, namespaceStr)}
	end
	local indentOuter, indentInner = string.rep(INDENT_CHARS, indentLevel), string.rep(INDENT_CHARS, indentLevel + 1) -- 3, 4 for union
	-- do union wrap
	local code = {indentOuter .. "union", indentOuter .. "{"}
	setmetatable(code, {__newindex = function(t, k, v) -- used in processSingle(), for convenience value can be table
		if type(v) == "table" then
			multipleInsert(t, k, v)
		else
			rawset(t, k, v)
		end
	end})
	-- if any two members have different sizes, need to wrap in struct
	-- members with size equal to biggest among group will be outside, other inside
	local maxS = 0
	for i, v in ipairs(group) do
		maxS = math.max(maxS, v.size)
	end
	local wrap = {}
	local offset = group[1].offset
	local skipFirst = true -- first is at right offset, second needs adjustment (usually by 4)
	for i, member in ipairs(group) do
		debugTable(member)
		if member.size ~= maxS then
			wrap[#wrap + 1] = member
		else
			-- for now taken care of by processSingle
			local padding = member.innerType and member.innerType.padding and member.innerType.padding
			if padding and not skipFirst and false then
				code[#code + 1] = indentInner .. "struct"
				code[#code + 1] = indentInner .. "{"
				indentLevel = indentLevel + 1
				code[#code + 1] = string.rep(INDENT_CHARS, indentLevel + 1) .. skipBytesText:format(padding)
			end
			code[#code + 1] = processSingle(member, indentLevel + 1, structName, namespaceStr)
			if padding and not skipFirst and false then
				indentLevel = indentLevel - 1
				code[#code + 1] = indentInner .. "};"
				dontSkipFirst = false
			end
			if padding and false then
				skipFirst = not skipFirst
			end
		end
		offset = member.offset + member.size + ((member.innerType or {}).padding or 0)
	end
	--[[if #wrap == 1 then -- one other size member can be inside union
		code[#code + 1] = processSingle(wrap[1], indentLevel + 1)
	else]]if #wrap > 0 then
		-- do struct wrap
		table.sort(wrap, function(a, b) return a.offset < b.offset end)
		code[#code + 1] = indentInner .. "struct"
		code[#code + 1] = indentInner .. "{"
		local indentInnerInner = string.rep(INDENT_CHARS, indentLevel + 2)
		local lastOffset = group[1].offset
		local i = 1
		while true do
			local currentField = wrap[i]
			local members
			members, i = getGroup(wrap, currentField, i)
			local skipBits = (currentField.offset - lastOffset) * 8
			if skipBits > 0 and skipBits % 8 == 0 then
				local bytes = skipBits:div(8)
				code[#code + 1] = indentInnerInner .. skipBytesText:format(bytes)
			elseif skipBits > 0 then
				--[[
				SATISFY MSVC
				packing bitfields there is wonky
				
				either have each bitfield item the size of item outside of bitfield (unsigned also strongly recommended), otherwise there will be wasted space
				
				or use 1-byte fields and carefully adjust size of skipped bits so that 8-bit boundary is not crossed in one declaration (if so, other bits will be skipped,
				so not only wasted space, but also subsequent bit positions will be wrong and union size may be wrong)
				(thank god to my idea to put static_assert! I would not catch this that soon otherwise)
				
				I chose second approach because first conflicts with my decoupled functions structure (processGroup shouldn't care what type field has,
				while to fix it it would have to change types of bit fields), while getMemberData shouldn't care about type outside bitfield
				]]
				local previousBit = (lastOffset % 1) * 8
				local skip = math.min(skipBits, 8 - previousBit)
				-- don't print total if it's just single skipbits "instruction"
				local total = skipBits - skip > 0 and string.format(" // skipping %d bytes and %d bits, in total %d bits", skipBits:div(8), skipBits % 8, skipBits) or ""
				code[#code + 1] = indentInnerInner .. skipBitsText:format(skip) .. total
				skipBits = skipBits - skip
				if skipBits > 0 then
					skip = math.min(skipBits, 8) -- no more than 8 bits in one go
					code[#code + 1] = indentInnerInner .. skipBitsText:format(skip)
					skipBits = skipBits - skip
				end
				local skipBytes = skipBits:div(8)
				if skipBytes > 0 then
					code[#code + 1] = indentInnerInner .. skipBytesText:format(skip)
					skipBits = skipBits - skipBytes * 8
				end
				if skipBits > 0 then
					skip = math.min(skipBits, 8) -- no more than 8 bits in one go
					code[#code + 1] = indentInnerInner .. skipBitsText:format(skip)
					skipBits = skipBits - skip
				end
				--[[while skipBits > 0 do
					skip = math.min(skipBits, 8) -- no more than 8 bits in one go
					code[#code + 1] = indentInnerInner .. skipBitsText:format(skip)
					skipBits = skipBits - skip
				end]]
			end
			if #members == 1 then
				code[#code + 1] = processSingle(currentField, indentLevel + 2, structName, namespaceStr)
			else
				code[#code + 1] = processGroup(members, indentLevel + 2, structName, namespaceStr) -- nested unions
			end
			lastOffset = currentField.offset + currentField.size
			if i > #wrap then break end
		end
		code[#code + 1] = indentInner .. "};"
	end
	code[#code + 1] = indentOuter .. "};"
	return code
end

local function getCustomFieldSizes(structName)
	local oldMember = mem.structs.types.CustomType
	local fieldSizes = {}
	function mem.structs.types.CustomType(name, size, f, ...)
		fieldSizes[name] = size
		return oldMember(name, size, f, ...)
	end
	mem.struct(structs.f[structName])
	mem.structs.types.CustomType = oldMember
	return fieldSizes
end

local function findDependencies(args, data, structureDependencies)
	debugTable(args)
	local data2 = data
	local n = #structureDependencies
	while data2 do
		if data2.struct then
			--print(data2.typeName, table.find(structureDependencies, data2.typeName) and true or false)
			if not table.find(structureDependencies, data2.typeName) then
				--print(args.name, data2.typeName, #structureDependencies)
				structureDependencies[#structureDependencies + 1] = data2.typeName
			end
			data2.typeName = (args.prependNamespace and namespaceStr or "") .. data2.typeName
		end
		data2 = data2.innerType
	end
end

function getGroup(fields, firstField, i)
	local members = {firstField} -- for doing unions
	debugTable(firstField)
	maxNextOffset = firstField.offset + firstField.size
	local firstOffset = firstField.offset
	local prevOffset = maxNextOffset
	for j = i + 1, #fields do
		if fields[j].offset >= maxNextOffset then
			return members, j, maxNextOffset
		end
		if fields[j].offset > prevOffset and fields[j].offset ~= firstOffset then
			--local diff = fields[j].offset - firstOffset
			--assert(diff > 0 and not fields[j].bit, string.format("Field %s, firstOffset %f, fieldOffset %f, fieldSize %f, diff %f, maxNextOffset: %f, prevOffset: %f",
			--	fields[j].name, firstOffset, fields[j].offset, fields[j].size, diff, maxNextOffset, prevOffset))
			--fields[j].padStart = diff
			--fields[j].offset = firstOffset
		end
		prevOffset = fields[j].offset + fields[j].size
		maxNextOffset = math.max(maxNextOffset, prevOffset)
		table.insert(members, fields[j])
	end
	return members, #fields + 1, maxNextOffset
	--[[local nextI
	-- "local j" wouldn't work here, loop variable shadows it instead of modifying
	for j = i, #fields do
		members[#members + 1] = fields[j]
		if j == #fields or fields[j + 1] and fields[j + 1].offset >= maxNextOffset then
			nextI = j + 1
			break
		end
	end
	i = nextI
	return members, i, maxNextOffset]]
end

--[[
args = table with:
	name - structure/union name
	indentLevel - if omitted, is assumed to be 0
	includeMembers - if is table, only members with names existing in table will be added
	offsets - member offsets (if omitted, will be taken from structs.o.*)
	members - member functions (if omitted, will be taken from structs.m.*)
	class - structure class (if omitted, will be the result of structs.class function call)
	union - structure is union (in MMExt sense)
	prependNamespace - prepend game-specific namespace to member structure names (for example mm8::Item)
	offset - if union, then its calculated offset, else unset (and assumed 0)
	processDependencies - whether to recursively process non-anonymous member structures
	processedStructs - table where all function results will be saved (best to pass same table for each call, that
		way same struct won't be processed more than once)
	structOrder - used for printing structure and dependencies code in correct order - to declare dependency before struct requiring it
	
function returns table with definition lines, array of names of structures it depends on (they also need to be defined),
	calculated size (most useful for mmext unions) and "processedStructs" table (if you were too lazy to pass your own)
]]
lastM = {}
local function processStruct(args)
	debugTable(args)
	args.processedStructs = args.processedStructs or {}
	args.indentLevel = args.indentLevel or 0
	args.offset = args.offset or 0
	local offsets, members = args.offsets or structs.o[args.name], args.members or structs.m[args.name]
	local class, rofields = args.class or structs.class(args.name), args.rofields or {}
	if not next(members) then -- forward declaration only, idk if 0 size struct is possible in C++
		local data = {code = {string.format("%sstruct %s; // 0-size struct, declaration only", string.rep(INDENT_CHARS, args.indentLevel), args.name)}, dependencies = {}, size = 0}
		args.processedStructs[args.name] = data
		table.insert(tget(args, "structOrder"), 1, args.name)
		return data.code, data.dependencies, size, args.processedStructs
	end
	args.structOrder = args.structOrder or {}
	local fields, structureDependencies = {}, {}
	-- fields hardcoded into this file, because they really need special processing (for example,
	-- light resistance doesn't have name and thus also offset)
	local extra = extra[args.name]
	if extra then
		for k, v in pairs(extra) do
			if table.find(v.games, _G.offsets.MMVersion) then
				fields[#fields + 1] = table.copy(v.data)
			end
		end
	end
	local indentOuter, indentInner = string.rep(INDENT_CHARS, args.indentLevel), string.rep(INDENT_CHARS, args.indentLevel + 1)
	local customFieldSizes = not args.union and getCustomFieldSizes(args.name) or {}
	local staticPtrCode = {}
	local size = not args.union and structs[args.name]["?size"] or 0
	local function addExtraField(t)
		fields[#fields + 1] = t
	end
	for mname, f in pairs(members) do
		table.insert(lastM, mname)
		if (type(args.includeMembers) == "table" and not table.find(args.includeMembers, mname)) or (type(mname) == "string" and mname:len() == 0) then -- last check is for dummy names
			goto continue
		elseif type(args.excludeMembers) == "table" and table.find(args.excludeMembers, mname) then
			goto continue
		end
		local data = getMemberData(args.name, mname, f, offsets, members, class, rofields, customFieldSizes, false, addExtraField)
		--if args.name == "GameStructure" then print(data.name, data.size:tohex()) end
		if data then
			if args.union and tonumber(data.name) then
				-- array with some fields rearranged, so it can't be indexed with const.* in all cases
				-- TODO: proper handling, like static const translation table
				data.name = "_" .. tostring(data.name)
			end
			-- add pointers for structs which don't really reside at 0 address, TODO: take into account limits removal relocation
			if args.name == "GameStructure" and data.struct and data.offset == 0 then
				--print(dump(data))
				table.insert(staticPtrCode, string.format("%sstatic inline %s%s* const %s = 0;", indentInner,
					args.prependNamespace and namespaceStr or "", data.typeName, toCamelCase(data.name)))
				findDependencies(args, data, structureDependencies)
				goto continue
			elseif data.union then
				local depends
				data.code, depends, data.size = processStruct{name = data.name:sub(1, 1):lower() .. data.name:sub(2), offsets = data.offsets, members = data.fields, rofields = data.rofields,
					union = true, indentLevel = 0, prependNamespace = args.prependNamespace, offset = data.offset, processedStructs = args.processedStructs, parent = args.name,
					processDependencies = args.processDependencies, structOrder = args.structOrder}
				multipleInsert(fields, #fields + 1, data)
				mergeArraysShallowCopy(structureDependencies, depends, true)
			elseif data.replaceWith then
				multipleInsert(fields, #fields + 1, data.replaceWith)
			else
				findDependencies(args, data, structureDependencies)
				table.insert(fields, data)
				if data.array and data.lenP then
					local t = {name = mname .. "_size", offset = data.lenP, size = data.lenA, typeName = commonTypeNamesToCpp["u" .. data.lenA]}
					table.insert(tget(data, "comments"), string.format("size offset is 0x%X", data.lenP))
					table.insert(fields, t)
				end
			end
			size = math.max(size, not getBaseTypeField(data, "static") and math.ceil(data.offset + (data.size or 0)) or 0)
		end
		::continue::
	end
	table.sort(fields, function(a, b)
		if a.offset ~= b.offset then
			return a.offset < b.offset
		end
		return a.size > b.size
	end)
	local cppAssert = "%sstatic_assert(sizeof(%s) == 0x%X, \"Invalid \\\"%s\\\" structure size\");"
	local code = {}
	if not args.union then-- insert later, because size not known yet
		code[#code + 1] = string.format("%sstruct %s // size: 0x%X", indentOuter, args.name, size)
	end
	code[#code + 1] = indentOuter .. "{"
	if #staticPtrCode > 0 then
		table.insert(staticPtrCode, "")
	end
	multipleInsert(code, #code + 1, staticPtrCode)
	local currentOffset = -1
	local prevOffset = args.offset or 0 -- for skipping bytes
	local i = 1
	local maxNextOffset = 0
	while true do
		if not fields[i] then break end
		local currentField = fields[i]
		if not getBaseTypeField(currentField, "static") then
			currentOffset = currentField.offset
		end
		local skip = currentOffset - prevOffset
		if skip > 0 then
			code[#code + 1] = indentInner .. skipBytesText:format(skip)
		end
		local members
		members, i, maxNextOffset = getGroup(fields, currentField, i)
		local group = processGroup(members, args.indentLevel + 1, not args.union and args.name, not args.union and args.prependNamespace and namespaceStr or "")
		multipleInsert(code, #code + 1, group)
		prevOffset = maxNextOffset
	end
	size = args.union and math.ceil(maxNextOffset - args.offset) or size -- ceil is for bits
	local endPadding = size - prevOffset
	if endPadding >= 1 then
		code[#code + 1] = indentInner .. skipBytesText:format(endPadding)
	end
	code[#code + 1] = args.union and string.format("%s} %s;", indentOuter, args.name) or (indentOuter .. "};")
	if args.union then
		table.insert(code, 1, string.format("%sstruct // size: 0x%X, MMExt union", indentOuter, size))
	end
	--local tmpname = prep .. (args.parent and (args.parent .. "::") or "") .. args.name
	local tmpname = (not args.union and namespaceStr or "") .. args.name -- unions are inline&anonymous struct, so need to check instance of it, not type
	code[#code + 1] = cppAssert:format(indentOuter, tmpname, size, tmpname)
	if args.processDependencies and not args.union then -- unions have 0 indent level and this breaks normal structs processed as dependencies
	-- this whole indent system should be probably redone anyways
		local addDepNames = {}
		for i, name in ipairs(structureDependencies) do
			if not args.processedStructs[name] then
				local depCode, depends, size = processStruct{name = name, indentLevel = args.indentLevel, prependNamespace = args.prependNamespace,
				processedStructs = args.processedStructs, processDependencies = args.processDependencies, structOrder = args.structOrder}
				--args.processedStructs[name] = {code = depCode, dependencies = depends, size = size} -- args.processedStructs is shared and written to a bit further
				mergeArraysShallowCopy(addDepNames, depends, true)
			end
		end
		mergeArraysShallowCopy(structureDependencies, addDepNames, true)
	end
	if not args.union and not args.processedStructs[args.name] then -- unions are inline
		args.processedStructs[args.name] = {code = code, dependencies = structureDependencies, size = size}
	end
	args.structOrder = args.structOrder or {}
	if not args.union then -- unions are not considered structs in many aspects
		-- structure needs to be after all of its dependencies
		local maxI = 1
		for i, name in ipairs(args.structOrder) do
			if table.find(structureDependencies, name) then
				maxI = i
			end
		end
		table.insert(args.structOrder, math.min(#args.structOrder + 1, maxI + 1), args.name)
	end
	return code, structureDependencies, size, args.processedStructs
end

function printStruct(name, includeMembers, excludeMembers, indentLevel, wrapInHeaderStuff)
	local processed = {}
	indentLevel = wrapInHeaderStuff and 1 or indentLevel or 1 -- always 1 indentation level if wrapping
	local args = {name = name, includeMembers = includeMembers, indentLevel = indentLevel, processDependencies = true,
		prependNamespace = true, processedStructs = processed, excludeMembers = excludeMembers, structOrder = {}}
	local t, dep = processStruct(args)
	--print(table.concat(t, "\n") .. "\n\nDependencies: " .. table.concat(dep, "\t"))
	_G.t, _G.dep, _G.processed, _G.args = t, dep, processed, args
	local code = {}
	--print(dump(args.structOrder))
	for i, name in ipairs(args.structOrder) do
		local struct = processed[name]
		setmetatable(struct.code, nil)
		code = table.join(code, struct.code)
		code[#code + 1] = "" -- newline
	end
	--code = table.join(code, processed[name].code)
	--io.save("structs.h", table.concat(code, "\n"))
	if wrapInHeaderStuff then
		multipleInsert(code, 1, {
			"#pragma once",
			"#include \"pch.h\"",
			"#include \"main.h\"",
			"",
			"#pragma pack(push, 1)",
			"",
			"namespace mm" .. Game.Version,
			"{"
		})

		multipleInsert(code, #code + 1, {
			"}",
			"#pragma pack(pop)"
		})
	end
	io.save("C:\\Users\\Eksekk\\source\\repos\\PartyGenerator\\PartyGeneratorDLL\\headers\\structsTest.h", table.concat(code, "\n"))
end

function pr(str)
	reload();printStruct(str, nil, str == "Player" and {"Attrs"} or nil, nil, true) -- attrs is from merge
end

function pr2(str)
	printStruct("GameStructure", nil, nil, nil, true)
end

-- fuck msvc
-- outside struct type has size x
-- then each bitfield member has size x (even if just one bit!), unsigned (so uint(n)_t)
-- this includes skipbits
-- OR
-- split skipbits into groups of 8 (need same type as members - bool - 1 byte; can't have more skipped than field size even if it's just for skipping...)



-- "ENUM" GENERATOR
local namePrefixes = {["Stats"] = "STAT", ["Skills"] = "SKILL", ["Damage"] = "DMG"}
local consts, header, source = {}, {}, {}
function processConst(name)
	if not consts[6] then
		consts[Game.Version] = const
		for _, i in ipairs{6, 7 ,8} do
			if i ~= Game.Version then
				local f, err = loadfile((DevPath or AppPath) .. "Scripts/Core/ConstAndBits.lua")
				if not f then
					print(err)
					goto continue
				end
				local o = table.copy(offsets)
				o.MMVersion = i
				local env = {
					offsets = o,
					select = select,
					mem = mem,
					pairs = pairs,
					internal = {MMVersion = Game.Version},
					string = string,
					setmetatable = setmetatable,
					table = table
				}
				setfenv(f, env)
				f()
				consts[i] = env.const
				::continue::
			end
		end
	end
	local prefix = namePrefixes[name]
	
	-- header
	
	local allKeys = {}
	for i, const in pairs(consts) do
		for v, k in sortpairs(table.invert(const[name])) do
			if not table.find(allKeys, k) then
				allKeys[#allKeys + 1] = k
			end
		end
	end
	local function formatName(name)
		name = name:gsub("([a-z])([A-Z0-9])", "%1_%2")
		name = prefix .. "_" .. name:upper()
		return name
	end
	local forwardDecl = {"extern int"}
	for i, k in ipairs(allKeys) do
		table.insert(forwardDecl, "\t" .. formatName(k) .. (i == #allKeys and ";" or ","))
	end
	table.insert(forwardDecl, "") -- becomes newline after concat
	for _, i in ipairs{6, 7, 8} do
		table.insert(forwardDecl, string.format("extern void makeEnum%s_%d();", name, i))
	end
	multipleInsert(header, #header + 1, forwardDecl)
	table.insert(header, "")
	
	-- source
	
	source[#source + 1] = "int "
	local last = allKeys[#allKeys]
	for _, k in ipairs(allKeys) do
		table.insert(source, string.format("\t%s = INVALID_ID%s", formatName(k), k == last and ";" or ","))
	end
	table.insert(source, "")
	
	for _, i in ipairs{6, 7, 8} do
		table.insert(source, string.format("void makeEnum%s_%d()", name, i))
		table.insert(source, "{")
		for v, k in sortpairs(table.invert(consts[i][name])) do
			table.insert(source, string.format("\t%s = %d;", formatName(k), v))
		end
		
		table.insert(source, "}")
		table.insert(source, "")
	end
	table.insert(source, "")
end

local constsToProcess = {"Damage"}
function writeConsts()
	for _, const in ipairs(constsToProcess) do
		processConst(const)
	end
	io.save("constHeader.h", table.concat(header, "\n"))
	io.save("constSource.cpp", table.concat(source, "\n"))
	header, source = {}, {}
end

--[[
	[mmv(0x6A7680, 0x7214E8, 0x75E450)].array{1, mmv(517, 789, 1000), ItemSize = 8}.EditPChar  'NPCTopic'
	[mmv(0x6A7684, 0x7214EC, 0x75E454)].array{1, mmv(517, 789, 1000), ItemSize = 8}.EditPChar  'NPCText'
	
	[mmv(0x6A8804, 0x722D90, 0x760390)].array(0, 512).EditPChar  'QuestsTxt'
]]