function reload()
	dofile("Scripts/Global/GenerateStructInfo.lua")
end
local mmver = offsets.MMVersion
local function mm78(...)
	local r = select(mmver - 6, ...)
	assert(r ~= nil)
	return r
end
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

-- helper functions
-- DEFINED IN EksekkStuff.lua

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
local extra =
{
	Player =
	{
		{games = {7, 8}, data = {offset = structs.o.Player.FireResistanceBase + 18, name = "LightResistanceBase", typeName = commonTypeNamesToCpp.i2, size = 2} },
		{games = {7, 8}, data = {offset = structs.o.Player.FireResistanceBase + 20, name = "DarkResistanceBase", typeName = commonTypeNamesToCpp.i2, size = 2} },
		{games = {7, 8}, data = {offset = structs.o.Player.FireResistanceBase + 22 + 18, name = "LightResistanceBonus", typeName = commonTypeNamesToCpp.i2, size = 2} },
		{games = {7, 8}, data = {offset = structs.o.Player.FireResistanceBase + 22 + 20, name = "DarkResistanceBonus", typeName = commonTypeNamesToCpp.i2, size = 2} },
	}
}

-- I had no other choice than calculate from offsets which might be wrong, so decided to hardcode
local customTypeSizes =
{
	GameStructure =
	{
		SpellObjId = 4,
		TitleTrack = 1,
		TitleTrackOffset = 4,
		NarratorTrack = 1,
		FlyCeiling = 5
	},
	LloydBeaconSlot =
	{
		Map = 2
	}
}
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
]]
local function getMemberData(structName, memberName, member, offsets, members, class, rofields)
	rofields = rofields or {}
	member = member or members[memberName]
	local data = {name = memberName or "", offset = offsets[memberName or ""] or 0}
	local up = debug.upvalues(member)
	local handler = up.f
	local boolsize = booleanHandlers[member] -- boolean
	local arr = up.arr -- mem arrays etc.
	local sname = (type(handler) == "table" and handler or {})[internal.structs_name_t] -- structure
	local EditPChar_newindex, EditConstPChar_newindex = getmetatable(mem.EditPChar).__newindex, getmetatable(mem.EditConstPChar).__newindex
	local bitValue = up.b
	local isUnnamedBit = up.bitHandlers and true or false -- bit without specifying value (contiguous), used in arrays
	local stringLen = up.len
	local unionOffsets = up.offs
	
	data.constValue = memberName and (tostring(memberName):len() > 0) and (table.find(rofields, memberName) ~= nil)
	
	local function addComment(s)
		data.comments = data.comments or {}
		table.insert(data.comments, s)
	end
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
		data.innerType = getMemberData(structName, memberName, handler, offsets, members, class)
		if data.innerType.replaceWith then
			data.replaceWith = data.innerType.replaceWith
			return data
		end
		data.ptr = up.ptr
		data.lenP = up.lenP
		data.lenA = data.ptr and getU(MT(up.lenA).__index, "size")
		data.beyondLen = up.beyondLen
		data.count = up.count == 0xFFFFFFFF and 0 or up.count
		if data.beyondLen then
			addComment("AccessBeyondLength is active (???)")
		end
		data.low = up.low
		if data.low and data.low > 0 then
			addComment(string.format("MMExt: %d..%d, here %d..%d", data.low, data.low + data.count - 1, 0, data.count - 1))
		end
		--data.size = ((data.ptr or data.count == 0) and 4 or data.count * up.size)
		if data.innerType.array and data.innerType.innerType.bit then
			local bytes = data.innerType.count:div(8)
			if bytes * 8 ~= data.innerType.count then
				error("Number of bits in nested array isn't divisible by 8", 1)
			end
			error "" -- TODO
			data.size = bytes * count
		elseif data.innerType.bit then
			local bytes = data.count:div(8)
			data.count = bytes
			addComment("array of " .. (data.innerType.anti and "abits (real index = 7 - usual)" or "bits"))
			data.size = bytes
		else
			data.size = (data.ptr or data.count == 0) and 4 or math.ceil(data.count * data.innerType.size)
		end
		data.dataType = data.ptr and types.parray or types.array
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
	elseif isUnnamedBit then
		data.size = 1/8
		data.bit = true
		data.bigEndian = true
		data.anti = member == AnyABitHandler -- is anti bit (if you access a bit (0-7) with index 2, anti bit index is (7 - 2) = 5)
		data.typeName = "uint8_t"
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
	elseif arr then
		local found
		for _, name in ipairs{"u1", "u2", "u4", "u8", "i1", "i2", "i4", "i8", "r4", "r8", "r10"} do
			if arr == mem[name] then
				data.typeName = commonTypeNamesToCpp[name]
				data.size = tonumber(name:sub(2))
				found = true
				data.dataType = types[name]
				break
			end
		end
		if arr == mem.pchar then
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
		data.size = isPtr and 4 or structs[sname].?size
		data.dataType = isPtr and types.pstruct or types.struct
	else
		print(string.format("Warning: unknown type structs.%s.%s encountered!", structName, memberName))
		data.array = true
		data.innerType = {size = 1, typeName = commonTypeNamesToCpp.u1}
		data.count = (customTypeSizes[structName] or {})[memberName] or error("Unknown custom type name: " .. memberName, 2)
		data.low = 0
		data.size = data.count
		data.name = memberName
		addComment("Unknown type")
	end
	return data
end

--[[
remaining to do:
CustomType = function: 0x02eb18c0,\
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
union = function: 0x02e919a0,\
vmethod = function: 0x02e19fe0\
--]]

function getArrayPointerString(arrays, last) -- for testing: https://cdecl.org/
	local explicitPointer = "(*%s)"
	local explicitArray = "[%d]"
	local arrayOfPointers = "(*[%d])"
	local pointerToArray = explicitPointer .. explicitArray
	local stdArray = "std::array<%s, %d>"
	--if last.bit then debug.Message(dump(arrays), dump(last)) end
	local type, name = last.typeName .. (last.ptr and "*" or "") .. (last.constPtr and "const" or ""), last.name
	for i, arr in ipairs(arrays) do
		if arr.count == 0 then
			if arr.ptr then
				type = "(*" .. type .. ")[]"
			else
				--str = "(" .. str .. ")" .. "[]" -- commented out because it clutters up code in overwhelming majority of the cases
				type = type .. "[]" -- TODOOOOOOOOOO: STD::ARRAY (has .size())
			end
		else
			type = stdArray:format(type, arr.count) .. (arr.ptr and "*" or "")
		end
	end
	return type .. " " .. name
end

local globalReplacements = {class = "clas"}
local function processSingle(data, indentLevel)
	indentLevel = indentLevel or 0
	local indentOuter, indentInner = string.rep(INDENT_CHARS, indentLevel), string.rep(INDENT_CHARS, indentLevel + 1)
	local dataCopy = data
	local s = indentOuter
	
	-- collect array info and get to base type
	local arrays, comments = nil, {}
	if data.array then
		arrays = {}
		while data.array do
			comments = table.join(comments, data.comments or {})
			arrays[#arrays + 1] = {ptr = data.ptr, count = data.count, low = data.low}
			data = data.innerType
		end
	end
	
	data.name = tostring(data.name)
	-- use camel case (I personally prefer it)
	local twoUpper = data.name:len() >= 2 and data.name:sub(1, 2):upper() == data.name:sub(1, 2)
	local name = twoUpper and data.name or (data.name:sub(1, 1):lower() .. (data.name:len() >= 2 and data.name:sub(2) or ""))
	name = globalReplacements[name] or name
	data.name = name
	-- arrays taken care of
	if data.union then
		local code = data.code
		s = {}
		for i, v in ipairs(code) do
			s[i] = indentOuter .. code[i]
		end
	elseif data.typeName then
		-- structure, mem array, edit pchars, bools, bits
		if data.constValue then
			s = s .. "const "
		end
		if data.formatTypeName then
			s = s .. data.typeName:format(name)
		else
			-- std::array<std::array<int, 5>, 20> arr;
			if arrays then
				s = s .. getArrayPointerString(arrays, data)
			else
				s = s .. data.typeName .. (data.ptr and "*" or "") .. " " .. name
			end
		end
	end
	comments = table.join(comments, data.comments or {})
	local commentsStr = #comments > 0 and (" // " .. table.concat(comments, " | ")) or ""
	if data.union then
		s[#s] = s[#s] .. commentsStr
	else
		s = s .. ";" .. commentsStr
	end
	data = dataCopy
	return s
end

local function processGroup(group, indentLevel)
	indentLevel = indentLevel or 0
	if #group == 1 then
		return {processSingle(group[1], indentLevel)}
	end
	local indentOuter, indentInner = string.rep(INDENT_CHARS, indentLevel), string.rep(INDENT_CHARS, indentLevel + 1) -- 3, 4 for union
	-- do union wrap
	local code = {indentOuter .. "union", indentOuter .. "{"}
	setmetatable(code, {__newindex = function(t, k, v)
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
	for i, member in ipairs(group) do
		if member.size ~= maxS then
			wrap[#wrap + 1] = member
		else
			code[#code + 1] = processSingle(member, indentLevel + 1)
		end
	end
	if #wrap > 0 then
		-- do struct wrap
		table.sort(wrap, function(a, b) return a.offset < b.offset end)
		code[#code + 1] = indentInner .. "struct"
		code[#code + 1] = indentInner .. "{"
		local indentInnerInner = string.rep(INDENT_CHARS, indentLevel + 2)
		local lastOffset = group[1].offset
		for i, member in ipairs(wrap) do
			local skipBits = (member.offset - lastOffset) * 8
			if skipBits > 0 then
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
				while skipBits > 0 do
					skip = math.min(skipBits, 8) -- no more than 8 bits in one go
					code[#code + 1] = indentInnerInner .. skipBitsText:format(skip)
					skipBits = skipBits - skip
				end
			end
			code[#code + 1] = processSingle(member, indentLevel + 2)
			lastOffset = member.offset + member.size
		end
		code[#code + 1] = indentInner .. "};"
	end
	code[#code + 1] = indentOuter .. "};"
	return code
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
	
function returns table with definition lines, array of names of structures it depends on (they also need to be defined),
	calculated size (most useful for mmext unions) and "processedStructs" table (if you were too lazy to pass your own)
]]
local function processStruct(args)
	args.processedStructs = args.processedStructs or {}
	args.indentLevel = args.indentLevel or 0
	args.offset = args.offset or 0
	local offsets, members, class, rofields = args.offsets or structs.o[args.name], args.members or structs.m[args.name], args.class or structs.class(args.name), args.rofields or {}
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
	for mname, f in pairs(members) do
		if (type(args.includeMembers) == "table" and not table.find(args.includeMembers, mname)) or (type(mname) == "string" and mname:len() == 0) then -- last check is for dummy names
			goto continue
		elseif type(args.excludeMembers) == "table" and table.find(args.excludeMembers, mname) then
			goto continue
		end
		local data = getMemberData(args.name, mname, f, offsets, members, class, rofields)
		if data then
			if args.union and tonumber(data.name) then
				-- array with some fields rearranged, so it can't be indexed with const.* in all cases
				-- TODO: proper handling, like static const translation table
				data.name = "_" .. tostring(data.name)
			end
			if data.union then
				local depends
				data.code, depends, data.size = processStruct{name = data.name:sub(1, 1):lower() .. data.name:sub(2), offsets = data.offsets, members = data.fields, rofields = data.rofields,
					union = true, indentLevel = 0, prependNamespace = args.prependNamespace, offset = data.offset, processedStructs = args.processedStructs, parent = args.name}
				table.insert(fields, data)
				for i, v in ipairs(depends) do
					if not table.find(structureDependencies, v) then
						table.insert(structureDependencies, v)
					end
				end
			elseif data.replaceWith then
				multipleInsert(fields, #fields + 1, data.replaceWith)
			else
				local data2 = data
				local n = #structureDependencies
				while data2 do
					if data2.struct then
						if not table.find(structureDependencies, data2.typeName) then
							structureDependencies[#structureDependencies + 1] = data2.typeName
						end
						data2.typeName = (args.prependNamespace and ("mm" .. tostring(Game.Version) .. "::") or "") .. data2.typeName
					end
					data2 = data2.innerType
				end
				table.insert(fields, data)
				if data.array and data.ptr then
					local t = {name = mname .. "_size", offset = data.lenP, size = data.lenA, typeName = commonTypeNamesToCpp["u" .. data.lenA]}
					table.insert(tget(data, "comments"), string.format("size offset is 0x%X", data.lenP))
					table.insert(fields, t)
				end
			end
		end
		::continue::
	end
	if args.union then
		--[[-- check for array
		local array, remove = {}, {}
		for i, field in ipairs(fields) do
			if tonumber(field.name) then
				array[#array + 1] = {offset = field.offset, index = tonumber(field.name)}
				table.insert(remove, i)
			end
		end
		if #array > 0 then
			table.sort(array, function(a, b) return a.offset < b.offset end)
			local i = 0
			local replace = {array = true, count = #array, size = 
			while true do
				if not array[i + 1] then break end
					
				i = i + 1
			end
		end]]
	end
	table.sort(fields, function(a, b) return a.offset < b.offset end)
	local cppAssert = "%sstatic_assert(sizeof(%s) == 0x%X, \"Invalid \\\"%s\\\" structure size\");"
	local code = {}
	local unionInsertIndex = args.union and 1 -- insert later, because size not known yet
	if not args.union then
		code[#code + 1] = string.format("%sstruct %s // size: 0x%X", indentOuter, args.name, structs[args.name].?size)
	end
	code[#code + 1] = indentOuter .. "{"
	local currentOffset = -1
	local prevOffset = args.offset or 0 -- for skipping bytes
	local i = 1
	local maxNextOffset, maxOffset = 0, 0
	while true do
		local currentField = fields[i]
		currentOffset = currentField.offset
		local skip = currentOffset - prevOffset
		if skip > 0 then
			code[#code + 1] = indentInner .. skipBytesText:format(skip)
		end
		local maxSize = currentField.size
		maxNextOffset = currentField.offset + maxSize
		for j = i + 1, #fields do
			if fields[j].offset ~= currentOffset then break end
			maxSize = math.max(maxSize, fields[j].size)
			maxNextOffset = math.max(maxNextOffset, fields[j].offset + fields[j].size)
		end
		maxOffset = math.max(maxOffset, maxNextOffset)
		local members = {} -- for doing unions
		local nextI
		-- "local j" wouldn't work, loop variable shadows it instead of modifying
		for j = i, #fields do
			members[#members + 1] = fields[j]
			if j == #fields or fields[j + 1].offset >= maxNextOffset then
				nextI = j + 1
				break
			end
		end
		i = nextI
		local group = processGroup(members, args.indentLevel + 1)
		multipleInsert(code, #code + 1, group)
		prevOffset = maxNextOffset
		if i > #fields then break end
	end
	local size = args.union and maxOffset - args.offset or structs[args.name].?size
	local endPadding = size - prevOffset
	if endPadding > 0 then
		code[#code + 1] = indentInner .. skipBytesText:format(endPadding)
	end
	code[#code + 1] = args.union and string.format("%s} %s;", indentOuter, args.name) or (indentOuter .. "};")
	if args.union then
		table.insert(code, unionInsertIndex, string.format("%sstruct // size: 0x%X, MMExt union", indentOuter, size))
	end
	local prep = args.prependNamespace and ("mm" .. _G.offsets.MMVersion .. "::") or ""
	--local tmpname = prep .. (args.parent and (args.parent .. "::") or "") .. args.name
	local tmpname = (not args.union and prep or "") .. args.name -- unions are inline&anonymous struct, so need to check instance of it, not type
	code[#code + 1] = cppAssert:format(indentOuter, tmpname, size, tmpname)
	if args.processDependencies then
		local combinedDepCode = {}
		local addDepNames = {}
		for i, name in ipairs(structureDependencies) do
			if not args.processedStructs[name] then
				local depCode, depends, size = processStruct{name = name, indentLevel = args.indentLevel, prependNamespace = args.prependNamespace, processedStructs = args.processedStructs}
				--table.insert(depCode, "\n")
				--multipleInsert(combinedDepCode, 1, depCode)
				args.processedStructs[name] = {code = depCode, dependencies = depends, size = size}
				mergeArraysShallowCopy(addDepNames, depends, true)
			end
		end
		multipleInsert(code, 1, combinedDepCode)
		mergeArraysShallowCopy(structureDependencies, addDepNames, true)
	end
	if not args.union and not args.processedStructs[args.name] then -- unions are inline
		args.processedStructs[args.name] = {code = code, dependencies = structureDependencies, size = size}
	end
	return code, structureDependencies, size, args.processedStructs
end

function printStruct(name, includeMembers, excludeMembers, indentLevel)
	local processed = {}
	indentLevel = indentLevel or 1
	local t, dep = processStruct{name = name, includeMembers = includeMembers, indentLevel = indentLevel, processDependencies = true, prependNamespace = true, processedStructs = processed, excludeMembers = excludeMembers}
	--print(table.concat(t, "\n") .. "\n\nDependencies: " .. table.concat(dep, "\t"))
	_G.t, _G.dep, _G.processed = t, dep, processed
	local code = {}
	for sname, v in pairs(processed) do
		if sname ~= name then
			setmetatable(v.code, nil)
			code = table.join(code, v.code)
			code[#code + 1] = "" -- newline
		end
	end
	code = table.join(code, processed[name].code)
	io.save("structs.h", table.concat(code, "\n"))
end

function pr(str)
	reload();printStruct(str, nil, str == "Player" and {"Attrs"} or nil) -- attrs is from merge
end

--[[
mem_internal = getU(mem.free, "internal")
old_callback = mem_internal.member_callback
function mem_internal.member_callback(n, ...) old_callback(n, ...); print(n) end
mem_internal.UpdateCallbacks()
mem.struct(structs.f.GameMap)
]]

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