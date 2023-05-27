function reload()
	dofile("Scripts/Global/GenerateStructInfo.lua")
end
r = reload
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
local convertToPointers = -- because updated during runtime etc.
{
	SpritesLod = {"SpritesSW"},
	GameStructure = {"NPCDataTxt", "MonstersTxt", "CharacterPortraits", "TransportLocations", "NPCGroup", "NPCText", "TransTxt", "ShopTheftExpireTime",
		"MapDoorSound", "GlobalEvtLines", "ItemsTxt", "NPC", "MixPotions", "ReagentSettings", "NPCNews", "MapFogChances",
		"ShopItems", "GuildItems", "NPCTopic", "ShopSpecialItems", "AutonoteTxt", "MapStats", "Houses", "ClassNames", "HostileTxt",
		"PlaceMonTxt", "AutonoteCategory", "QuestsTxt", "HousesExtra", "CharacterDollTypes", "HouseMovies", "NPCGreet", "TransportIndex",
		"GuildNextRefill2", "ShopNextRefill", "ClassNames" -- from merge
		, "PatchOptions" -- potentially relocated each run
		, "CustomLods", "MonsterKinds", "TitleTrackOffset", "MissileSetup", "AwardsSort" -- MMExt
	},
	GameClasses = {"HPBase", "SPBase", "HPFactor", "SPFactor", "StartingStats", "Skills" -- Merge
	, "SPStats"}, -- MMExt
	GameClassKinds = {"StartingSkills"}, -- Merge
	DialogLogic = {"List"} -- MMExt
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

local function getCustomFieldSizes(structName)
	local oldMember = types.CustomType
	local fieldSizes = {}
	function types.CustomType(name, size, f, ...)
		fieldSizes[name] = size
		return oldMember(name, size, f, ...)
	end
	mem.struct(structs.f[structName])
	types.CustomType = oldMember
	return fieldSizes
end

local function stripNamespaces(str)
	return str:gsub(".-::", "")
end

function getStructureMembersInfoData(structName)
	local oldStru = structs.f[structName]
	local output = {}
	structs.f[structName] = function(define, ...)
		local oldInfo, oldFunc, oldMethod = types.Info, types.func, types.method
		local prevDefined
		function types.Info(t, ...)
			local name = define.LastDefinedMemberName or "DefaultIndex"
			if not t.new -- not added by mmext
				and prevDefined ~= name then -- don't overwrite old data, for example if define.f.Something is defined, because it doesn't change "LastDefinedMemberName"
				prevDefined = name
				output[name] = t
			end
			return oldInfo(t, ...)
		end
		function types.func(def, ...)
			define.LastDefinedMemberName = def.name
			return oldFunc(def, ...)
		end
		function types.method(def, ...)
			define.LastDefinedMemberName = def.name
			return oldMethod(def, ...)
		end
		local ret = {oldStru(define, ...)}
		types.Info, types.func, types.method = oldInfo, oldFunc, oldMethod
		return unpack(ret)
	end
	mem.struct(structs.f[structName])
	structs.f[structName] = oldStru
	return output
end

-- decided to keep all three games' structures in one file, because I would have to include files for all games anyway
local structureByFile =
{
	MapModel = {"ModelVertex", "ModelFacet", "BSPNode", "MapModel"},

	MapMisc = {"TilesetDef", "MapOutline", "MapOutlines", "OdmHeader", "BlvHeader", "SpawnPoint", "BaseLight", "MapNote"},

	MapElements = {"FacetData", "MapLight", "MapRoom", "MapVertex", "MapFacet", "MapDoor", "MapSprite", "MapChest"},

	Common = {"SpellBuff", "SpellEffect", "Item", "StartStat", "ObjectRef2", "FloatVector", "ObjectRef"},

	Monster = {"MonsterSchedule", "MonsterAttackInfo", "MapMonster", "MonstersTxtItem", "MonsterKind"},

	GameMap = {"MapExtra", "MapObject", "GameMap"},

	Arcomage = {"ArcomageAction", "ArcomageActions", "ArcomageCard", "ArcomagePlayer", "Arcomage"},

	Lod = {"LodRecord", "CustomLods", "LodFile", "Lod", "LodSprite", "LodSpriteD3D", "SpritesLod", "LodBitmap", "BitmapsLod", "LodSpriteLine", "LodPcx"},

	Bin = {"DecListItem", "OverlayItem", "TileItem", "ObjListItem", "DChestItem", "SoundsItem", "TFTItem", "MonListItem", "PFTItem", "IFTItem", "SFTItem", "SFT", "CurrentTileBin"},
	
	TxtFileItems = {"HistoryTxtItem", "StdItemsTxtItem", "SpcItemsTxtItem", "SpellsTxtItem", "MapStatsItem", "ItemsTxtItem", "NPCProfTxtItem", "Events2DItem", },

	GameDataStructs = {"GameRaces", "GameClasses", "GameClassKinds", "DialogLogic", "Dlg", "GameScreen"},

	GameMisc = {"SpellInfo", "TravelInfo", "FogChances", "ShopItemKind", "GeneralStoreItemKind", "HouseMovie", "Weather", "MoveToMap", "MissileSetup", "TownPortalTownInfo", "EventLine", "ProgressBar", "ActionItem", "PatchOptions", "GameMouse", "MouseStruct", "Fnt"},

	Player = {"FaceAnimationInfo", "LloydBeaconSlot", "BaseBonus", "Player"},

	GameParty = {"GameParty", "NPC", "Button", "NPCNewsItem"},

	MergeSpecific = {"ArmorShopRule", "ShopRule", "WeaponShopRule", "ArcomageRule", "HouseRules", "HousesExtra", "CharacterDollType", "CharacterVoices", "CharacterPortrait", "PartyLight", "EquipCoordsCloak", "EquipCoordinates", "ArmorPicsCoords", "ReagentSettings"},

	GameStructure = {"GameStructure"}
}

local globalExcludes =
{
	Player = {"Attrs"}, -- attrs is from merge.
	GameStructure = {"Dialogs"}, -- mmext
	Item = {"ExtraData"}, -- my stuff for MAW mod
}

local function getStructFile(name)
	for k, v in pairs(structureByFile) do
		if table.find(v, name) then
			return k
		end
	end
	printf("No file specified for name %q", name)
	return "unknown"
end

-- helper functions
-- DEFINED IN A_EksekkFunctions.lua

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
- size - entire member size in memory, for arrays it's count * innerType.size
- bit - is bit
	- bitValue - used for named bits (like structs.Item.Stolen)
	- bitIndex - index of bit in little endian starting from 0 (bit 0x200 of container 0xFE84 would have index 14), used only with named bits
	- bigEndian - used with bit arrays
	- anti - is anti bit (if you access a bit (0-7) with index 2, anti bit index is (7 - 2) = 5), used only with unnamed bits
- comments - table of strings
- struct - is struct (or pointer to it if ptr is set)
- commentOut - self-explanatory, used for custom types with 0 size
- padding
- [added in processStruct] ptrValue - pointer with set value
- [added in getGroup] padStart
]]
local EditPChar_newindex, EditConstPChar_newindex = getmetatable(mem.EditPChar).__newindex, getmetatable(mem.EditConstPChar).__newindex
local getMemberData
function getMemberData(structName, memberName, member, offsets, members, class, rofields, customFieldSizes, inArray)
	rofields = rofields or {}
	member = member or members[memberName]
	local data = {name = memberName or "", offset = offsets[memberName or ""] or 0}
	local function addComment(s)
		data.comments = data.comments or {}
		table.insert(data.comments, s)
	end
	if type(memberName) == "number" then -- unions
		data.name = "_" .. memberName
	end
	local protFunc = getU(member, "f0")
	if protFunc then
		addComment("requires unprotect before change")
		member = protFunc
	end
	local up = debug.upvalues(member)
	local arrayHandler = up.f
	local boolsize = booleanHandlers[member] -- boolean
	local memArr = up.arr -- mem arrays etc.
	local sname = (type(arrayHandler) == "table" and arrayHandler or {})[internal.structs_name_t] -- structure
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
		-- if Merge and table.find({"HPBase", "SPBase", "HPFactor", "SPFactor", "SPStats"}, memberName) then
		-- 	data.offset = getU(getmetatable(Game.Classes[memberName]).__index, "o")
		-- end
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
		-- PADDING PROBLEMS, two solutions below:
		if data.innerType.size and up.size > data.innerType.size then
			data.innerType.padding = up.size - data.innerType.size
			-- 1st, count padding as type size
			--data.innerType.size = up.size
		end
		if data.innerType.bit then
			local bytes = data.count:div(8)
			data.count = bytes
			addComment("array of " .. (data.innerType.anti and "abits (real index = 7 - usual)" or "bits"))
			data.size = bytes
		else
			-- 2nd, padding is distinct and add it only when necessary
			data.size = (data.ptr or data.count == 0) and 4 or math.ceil(data.count * (data.innerType.size + (data.innerType.padding or 0)))
		end
		data.dataType = data.ptr and types.parray or types.array
		-- change array to pointer
		if convertToPointers[structName] and table.find(convertToPointers[structName], data.name) then
			tget(luaData, structName, data.name).ptrName = data.name
			setBaseTypeField(data, "convertToPointer", true) -- setting this to explicitly signal to processStruct that it needs to convert length field into pointer
			--setBaseTypeField(data, "padding", (getBaseTypeField(data, "padding") or 0) + getBaseTypeField(data, "size") - 4)
		end
	elseif stringLen then -- string (fixed size, not pointer)
		data.array = true
		data.count = stringLen
		data.low = 0
		data.size = data.count
		data.innerType = {typeName = "char", name = memberName, offset = 0, size = 1}
		addComment("fixed size string, " .. (up.NoZero and "doesn't require null terminator" or "requires null terminator"))
		data.dataType = types.string
	elseif bitValue then
		data.size = 1/8
		data.bitIndex = 7 - bitIndex[bitValue] or error("Not a valid bit", 1)
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
		addComment("EditPChar")
	elseif getUpvalueByValue(member, EditConstPChar_newindex) then
		data.size = 4
		data.typeName = "char"
		data.ptr = true
		addComment("EditConstPChar - unprotect before/protect after edit")
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
			addComment("PChar (read-only)")
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
	if convertToPointers[structName] and table.find(convertToPointers[structName], data.name) then
		tget(luaData, structName, data.name).ptrName = data.name
		data.convertToPointer = true
	end
	return data
end

function getArrayPointerString(arrays, last, addPointer) -- for testing: https://cdecl.org/
	local stdArray = "std::array<%s, %d>"
	local type, name = last.typeName .. (last.ptr and "*" or "") .. (last.constPtr and "const" or ""), last.name
	for i = #arrays, 1, -1 do
		local arr = arrays[i]
		if arr.count == 0 then
			type = type .. "*"
		else
			type = stdArray:format(type, arr.count) .. (arr.ptr and "*" or "")
			-- std::array<std::array<uint8_t, 128>*, 128> heightMap;
		end
	end
	return type .. (addPointer and "*" or "") .. " " .. name
end

local function toCamelCase(str)
	local twoUpper = str:len() >= 2 and str:sub(1, 2):upper() == str:sub(1, 2)
	str = twoUpper and str or (str:sub(1, 1):lower() .. (str:len() >= 2 and str:sub(2) or ""))
	str = globalReplacements[str] or str
	return str
end

local function getArraysCommentsAndBaseData(data)
	-- collect array info and get to base type
	local arrays, comments = {}, {}
	while data.array do
		comments = table.join(comments, data.comments or {})
		arrays[#arrays + 1] = data
		data = data.innerType
	end
	comments = table.join(comments, data.comments or {})
	return arrays, comments, data
end

local function processSingle(data, indentLevel, structName, namespaceStr, debugLines)
	indentLevel = indentLevel or 0
	local indentOuter, indentInner = string.rep(INDENT_CHARS, indentLevel), string.rep(INDENT_CHARS, indentLevel + 1)
	local dataCopy = data
	local s = indentOuter
	local arrays, comments, data = getArraysCommentsAndBaseData(data)
	if #arrays == 0 then arrays = nil end
	
	-- use camel case (I personally prefer it)
	data.name = toCamelCase(tostring(data.name))

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
				result = result .. getArrayPointerString(arrays, data)
			else
				result = result .. data.typeName .. (data.ptr and "*" or "") .. " " .. data.name
			end
		end
		local offset = arrays and arrays[1] and arrays[1].offset or data.offset or 0
		table.insert(comments, string.format("0x%X (%d decimal)", offset, offset))
		if data.bit and data.bitIndex then
			comments[#comments] = comments[#comments] .. ", bit index " .. data.bitIndex
		end
		if data.commentOut then
			result = "// " .. result
		end
		return result
	end
	if data.union then
		s = {}
		for i, v in ipairs(data.code) do
			s[i] = indentOuter .. v
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
	local commentsStr = #comments > 0 and (" // " .. table.concat(comments, " | ")) or ""
	if type(s) == "table" then
		s[#s] = s[#s] .. commentsStr
	else
		s = s .. ";" .. commentsStr
	end
	if _DEBUG and not data.static and not data.commentOut then
		local off = arrays and arrays[1] and arrays[1].offset or data.offset or 0
		local formatStr = "%sstatic_assert(offsetof(%s, %s) == %d);"
		if off ~= 0 and structName and not data.bit then
			table.insert(debugLines, formatStr:format(indentOuter, namespaceStr .. structName, data.name, off))
		end
	end
	data = dataCopy
	return s
end

-- using visual studio code with "lua booster" extension
-- need to dummy forward declare to not miss recursive call when using "find references"
local processGroup
function processGroup(group, indentLevel, structName, namespaceStr, debugLines)
	-- messing around
	--setmetatable(getfenv(1), {__index = function(t, k) if not xxx then print(k); return rawget(t, k) end end})
	indentLevel = indentLevel or 0
	if #group == 1 then
		local ret = processSingle(group[1], indentLevel, structName, namespaceStr, debugLines)
		return type(ret) == "table" and ret or {ret}
	end
	local indentOuter, indentInner = string.rep(INDENT_CHARS, indentLevel), string.rep(INDENT_CHARS, indentLevel + 1) -- 3, 4 for union
	-- do union wrap
	local code = {
		indentOuter .. "union",
		indentOuter .. "{"
	}
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
		if member.size ~= maxS then
			wrap[#wrap + 1] = member
		else
			-- for now taken care of by processSingle
			local padding = member.innerType and member.innerType.padding
			if padding and not skipFirst then
				code[#code + 1] = indentInner .. "struct"
				code[#code + 1] = indentInner .. "{"
				indentLevel = indentLevel + 1
				code[#code + 1] = string.rep(INDENT_CHARS, indentLevel + 1) .. skipBytesText:format(padding)
			end
			code[#code + 1] = processSingle(member, indentLevel + 1, structName, namespaceStr, debugLines)
			if padding and not skipFirst then
				indentLevel = indentLevel - 1
				code[#code + 1] = indentInner .. "};"
			end
			if padding then
				skipFirst = not skipFirst
			end
		end
		offset = member.offset + member.size + ((member.innerType or {}).padding or 0)
	end
	if #wrap > 0 then
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
				
				I chose second approach because first conflicts with my (attempted) decoupled functions structure (processGroup shouldn't care what type field has,
				while to fix it it would have to change types of bit fields), while getMemberData shouldn't care about type outside bitfield
				]]
				local previousBit = (lastOffset % 1) * 8
				local skip = math.min(skipBits, 8 - previousBit)
				-- don't print total if it's just single skipbits "instruction"
				local total = skipBits - skip > 0 and string.format(" // skipping %d bytes and %d bits, in total %d bits", skipBits:div(8), skipBits % 8, skipBits) or ""
				code[#code + 1] = indentInnerInner .. skipBitsText:format(skip) .. total
				skipBits = skipBits - skip
				local function doBits()
					if skipBits > 0 then
						skip = math.min(skipBits, 8) -- no more than 8 bits in one go
						code[#code + 1] = indentInnerInner .. skipBitsText:format(skip)
						skipBits = skipBits - skip
					end
				end
				doBits()
				local skipBytes = skipBits:div(8)
				if skipBytes > 0 then
					code[#code + 1] = indentInnerInner .. skipBytesText:format(skip)
					skipBits = skipBits - skipBytes * 8
				end
				doBits()
			end
			if #members == 1 then
				code[#code + 1] = processSingle(currentField, indentLevel + 2, structName, namespaceStr, debugLines)
			else
				code[#code + 1] = processGroup(members, indentLevel + 2, structName, namespaceStr, debugLines) -- nested unions
			end
			lastOffset = currentField.offset + currentField.size
			if i > #wrap then break end
		end
		code[#code + 1] = indentInner .. "};"
	end
	code[#code + 1] = indentOuter .. "};"
	return code
end

local function findDependencies(data, structureDependencies)
	local data2 = data
	while data2 do
		if data2.struct then
			if not table.find(structureDependencies, data2.typeName) then
				structureDependencies[#structureDependencies + 1] = data2.typeName
			end
		end
		data2 = data2.innerType
	end
end
 -- for doing unions
 -- returns group members, next index for full members array, and offset which marks group end (non-inclusive, member at this offset won't be in group)
function getGroup(fields, firstField, i)
	local members = {firstField}
	debugTable(firstField)
	
	local maxNextOffset = firstField.offset + firstField.size

	for j = i + 1, #fields do
		if fields[j].offset >= maxNextOffset then
			return members, j, maxNextOffset
		end
		maxNextOffset = math.max(maxNextOffset, fields[j].offset + fields[j].size)
		table.insert(members, fields[j])
	end
	return members, #fields + 1, maxNextOffset
end

local function addExtraFields(name, fields)
	-- fields hardcoded into this file, because they really need special processing (for example,
	-- light resistance doesn't have name and thus also offset)
	local extra = extra[name]
	if extra then
		for k, v in pairs(extra) do
			if table.find(v.games, offsets.MMVersion) then
				fields[#fields + 1] = table.copy(v.data)
			end
		end
	end
end

local function addNamespacePrefixes(data, namespaceStr)
	local data2 = data
	while data2 do
		if data2.struct then
			data2.typeName = namespaceStr .. data2.typeName
		end
		data2 = data2.innerType
	end
end

local function definitelyShouldSkipMember(structName, includeMembers, excludeMembers, memberName)
	if (type(includeMembers) == "table" and not table.find(includeMembers, memberName)) or (type(memberName) == "string" and memberName:len() == 0) then -- last check is for dummy names
		return true
	elseif type(excludeMembers) == "table" and table.find(excludeMembers, memberName) or globalExcludes[structName] and table.find(globalExcludes[structName], memberName) then
		return true
	end
	return false
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
local function invalidIndex(tbl, key)
	error(string.format("Unexpected struct table index %q", key), 2)
end

local processStruct
function processStruct(args)
	-- initialization

	-- default arguments
	args.offset = args.offset or 0
	args.structOrder = args.structOrder or {}
	args.indentLevel = args.indentLevel or 0
	args.processedStructs = args.processedStructs or {}

	-- locals
	local fields, structureDependencies = {}, {}
	local myNamespaceStr = args.prependNamespace and namespaceStr or ""
	local indentOuter, indentInner = string.rep(INDENT_CHARS, args.indentLevel), string.rep(INDENT_CHARS, args.indentLevel + 1)
	local customFieldSizes = not args.union and getCustomFieldSizes(args.name) or {}
	local staticPtrDeclarationCode, staticConvertToPointerDeclarationCode, staticDefinitionCode = {}, {}, {}
	local offsets, members = args.offsets or structs.o[args.name], args.members or structs.m[args.name]
	local class, rofields = args.class or structs.class(args.name), args.rofields or {}
	local size = not args.union and structs[args.name]["?size"] or 0
	
	-- after initialization
	if not next(members) or (not args.union and size == 0) then -- forward declaration only, idk if 0 size struct is possible in C++
		local data = {code = {string.format("%sstruct %s; // 0-size struct, declaration only", string.rep(INDENT_CHARS, args.indentLevel), args.name)}, dependencies = {}, size = 0}
		args.processedStructs[args.name] = data
		table.insert(tget(args, "structOrder"), 1, args.name)
		return data.code, data.dependencies, size, args.processedStructs
	end
	addExtraFields(args.name, fields)
	for mname, f in sortpairs(members) do
		if definitelyShouldSkipMember(args.name, args.includeMembers, args.excludeMembers, mname) then
			goto continue
		end
		local data = getMemberData(args.name, mname, f, offsets, members, class, rofields, customFieldSizes, false)
		local function addArraySizeField()
			if data.array and data.lenP then
				local t = {name = mname .. "_size", offset = data.lenP, size = data.lenA, typeName = commonTypeNamesToCpp["u" .. data.lenA]}
				table.insert(tget(data, "comments"), string.format("size field offset is 0x%X", data.lenP))
				table.insert(fields, t)
			end
		end
		if data then
			if args.union and tonumber(data.name) then
				-- array with some fields rearranged, so it can't be indexed with const.* in all cases
				-- TODO: proper handling, like static const translation table
				data.name = "_" .. tostring(data.name)
			end
			-- add pointers for structs which don't really reside at 0 address, TODO: take into account limits removal relocation
			if data.struct and data.offset == 0 then
				table.insert(staticPtrDeclarationCode,
					string.format("%sstatic inline %s%s* const %s = 0;",
					indentInner,
					myNamespaceStr,
					data.typeName,
					toCamelCase(data.name))
				)
				findDependencies(data, structureDependencies)
				goto continue
			elseif data.struct and data.size == 0 then -- Merge, PartyLight
				goto continue
			elseif (data.array and data.innerType.convertToPointer) or data.convertToPointer then
				findDependencies(data, structureDependencies)
				if not args.saveToGeneratorDirectory then
					local f = deepcopyMM(data)
					table.insert(fields, f)
				end
				local arrays, comments, baseData = getArraysCommentsAndBaseData(data)
				local arraysOrig = deepcopyMM(arrays)
				if #arrays > 0 then
					table.remove(arrays, 1)
				end
				local old1, old2 = baseData.typeName, baseData.name
				baseData.typeName = (baseData.struct and args.prependNamespace and namespaceStr or "") .. baseData.typeName
				baseData.name = toCamelCase(baseData.name)
				local resultTypeAndName = getArrayPointerString(arrays, baseData, true)
				local comment = "" -- "converted to pointer to not break with limits removal scripts"
				comment = comment .. string.format(--[[", ]]"original offset 0x%X (%d decimal)", data.offset, data.offset)
				if #arraysOrig > 0 then
					comment = comment .. string.format(--[[", ]]"element size: 0x%X (%d decimal)", data.innerType.size, data.innerType.size)
				end
				table.insert(staticConvertToPointerDeclarationCode,
					string.format(
						"%sstatic %s; // %s",
						indentInner,
						resultTypeAndName,
						comment
					)
				)
				baseData.name = myNamespaceStr .. args.name .. "::" .. baseData.name
				resultTypeAndName = getArrayPointerString(arrays, baseData, true)
				table.insert(staticDefinitionCode, string.format("%s = nullptr;", resultTypeAndName))
				if arraysOrig[1] then
					if not args.saveToGeneratorDirectory then addArraySizeField() end
					local isPointer = arraysOrig[1].lenA and true or false
					-- size field pointer, getting one (but not pointer) even if original array doesn't have it
					local typeNameWithPtr = isPointer and (commonTypeNamesToCpp["u" .. arraysOrig[1].lenA] .. "*") or commonTypeNamesToCpp.u4
					local fieldName = toCamelCase(mname .. "_size") .. (isPointer and "Ptr" or "")
					local comment = "Offset/size: " -- (isPointer and "pointer to size" or "size field") .. ", set during initialization. Original offset/size: "
					comment = comment .. (
						string.format("0x%X (%d decimal)",
							isPointer and arraysOrig[1].lenP or arraysOrig[1].count,
							isPointer and arraysOrig[1].lenP or arraysOrig[1].count
						)
					)
					table.insert(staticConvertToPointerDeclarationCode,
						string.format("%sstatic %s %s; // %s",
							indentInner,
							typeNameWithPtr,
							fieldName,
							comment
						)
					)
					table.insert(staticDefinitionCode,
						string.format("%s %s = %s;",
						-- prepend namespace here should always be implicitly true because wrapping in header stuff requires it, but whatever
						typeNameWithPtr,
						myNamespaceStr .. args.name .. "::" .. fieldName,
						isPointer and "nullptr" or "0"
						)
					)

					tget(luaData, args.name, baseData.name).sizePtrName = toCamelCase(mname .. "_size")
				end
				baseData.typeName, baseData.name = old1, old2
			elseif data.union then
				local res = processStruct{name = data.name:sub(1, 1):lower() .. data.name:sub(2), offsets = data.offsets, members = data.fields, rofields = data.rofields,
					union = true, indentLevel = 0, prependNamespace = args.prependNamespace, offset = data.offset, processedStructs = args.processedStructs, parent = args.name,
					processDependencies = args.processDependencies, structOrder = args.structOrder, shouldProcessdependency = args.shouldProcessdependency}
				data.code, data.size = res.code, res.size
					-- unions have 0 indent level and this breaks normal structs processed as dependencies
					-- this whole indent system should be probably redone anyways
				-- doesn't work with non-integer key tables
				--multipleInsert(fields, #fields + 1, data)
				table.insert(fields, data)
				mergeArraysShallowCopy(structureDependencies, res.dependencies, true)
			elseif data.replaceWith then
				multipleInsert(fields, #fields + 1, data.replaceWith)
			else
				findDependencies(data, structureDependencies)
				table.insert(fields, data)
				addArraySizeField()
			end
			addNamespacePrefixes(data, myNamespaceStr)
			if not getBaseTypeField(data, "static") and not ((data.array and data.innerType.convertToPointer) or data.convertToPointer) then
				size = math.max(size, math.ceil(data.offset + (data.size or 0)))
			end
		end
		::continue::
	end
	table.sort(fields, function(a, b)
		if a.offset ~= b.offset then
			return a.offset < b.offset
		end
		if a.size ~= b.size then
			return a.size > b.size
		end
		return a.name < b.name
	end)
	local code = {}
	code[#code + 1] = indentOuter .. "{"
	if #staticPtrDeclarationCode > 0 then
		table.insert(staticPtrDeclarationCode, "")
	end
	multipleInsert(code, #code + 1, staticPtrDeclarationCode)
	if #staticConvertToPointerDeclarationCode > 0 then
		table.insert(staticConvertToPointerDeclarationCode, "")
	end
	multipleInsert(code, #code + 1, staticConvertToPointerDeclarationCode)
	local currentOffset = -1
	local prevOffset = args.offset or 0 -- for skipping bytes
	local i = 1
	local maxNextOffset = 0
	local debugLines = {}
	while true do
		local currentField = fields[i]
		if not currentField then break end
		if not getBaseTypeField(currentField, "static") then
			currentOffset = currentField.offset
			local skip = currentOffset - prevOffset
			skip = skip > 0 and math.floor(skip) or 0 -- bits
			if skip > 0 then
				code[#code + 1] = indentInner .. skipBytesText:format(skip)
			end
		end
		local members
		members, i, maxNextOffset = getGroup(fields, currentField, i)
		local group = processGroup(members, args.indentLevel + 1, not args.union and args.name, not args.union and myNamespaceStr or "", debugLines)
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
	else
		table.insert(code, 1, string.format("%sstruct %s // size: 0x%X", indentOuter, args.name, size))
	end
	do
		local tmpname = (not args.union and namespaceStr or "") .. args.name -- unions are inline&anonymous struct, so need to check instance of it, not type
		local cppAssert = "%sstatic_assert(sizeof(%s) == 0x%X, \"Invalid \\\"%s\\\" structure size\");"
		code[#code + 1] = cppAssert:format(indentOuter, tmpname, size, tmpname)
	end
	for i, v in ipairs(debugLines) do
		-- even out indentation
		debugLines[i] = v:gsub(INDENT_CHARS:escapeRegex() .. "+", indentOuter)
	end
	multipleInsert(code, #code + 1, debugLines)
	-- unions are not considered structs in many aspects
	if not args.union then
		if args.processDependencies then
			local addDepNames = {}
			for i, name in ipairs(structureDependencies) do
				if not args.processedStructs[name] and (not args.shouldProcessdependency or args.shouldProcessdependency(name)) then
					local passArgs = table.copy(args)
					passArgs.name = name
					local res = processStruct(passArgs)
					--args.processedStructs[name] = {code = depCode, dependencies = depends, size = size} -- args.processedStructs is shared and written to a bit further
					mergeArraysShallowCopy(addDepNames, res.dependencies, true)
				end
			end
			mergeArraysShallowCopy(structureDependencies, addDepNames, true)
		end
		if not args.processedStructs[args.name] then -- unions are inline
			args.processedStructs[args.name] = setmetatable({code = code, dependencies = structureDependencies, size = size, staticDefinitionCode = staticDefinitionCode},
				{__index = invalidIndex})
		end
		-- structure needs to be after all of its dependencies
		local maxI = 0
		for i, name in ipairs(args.structOrder) do
			if table.find(structureDependencies, name) then
				maxI = i
			end
		end
		table.insert(args.structOrder, math.min(#args.structOrder + 1, maxI + 1), args.name)
	end
	return setmetatable({code = code, dependencies = structureDependencies, size = size, processedStructs = args.processedStructs}, {__index = invalidIndex})
end

-- saveToGeneratorDirectory - whether it's for my project (true) or for reverse engineering purposes (false)
-- isLast if it's last of 3 games processed
function printStruct(name, includeMembers, excludeMembers, indentLevel, saveToGeneratorDirectory, isLast, directoryPrefix) 
	luaData = {}
	local processed = {}
	indentLevel = wrapInHeaderStuff and 1 or indentLevel or 1 -- always 1 indentation level if wrapping
	local args = {name = name, includeMembers = includeMembers, indentLevel = indentLevel, processDependencies = true,
		prependNamespace = true, processedStructs = processed, excludeMembers = excludeMembers, structOrder = {},
		saveToGeneratorDirectory = saveToGeneratorDirectory}
	local t = processStruct(args)
	local old = args.name
	args.name = "Button" -- npc dialog item
	do local x = structs.Button end -- generate data (__index)
	t = processStruct(args)
	args.name = old
	_G.t, _G.processed, _G.args = t, processed, args
	local pathToLoad = "C:\\Users\\Eksekk\\code.bin"
	local oldCode
	local ok, fileContent = pcall(io.load, pathToLoad)
	if ok then
		ok, oldCode = pcall(internal.unpersist, fileContent)
	end
	local code = ok and oldCode or {}
	-- for i, name in ipairs(args.structOrder) do
	-- 	structureByFile[name] = {name} -- hack to help with doxygen
	-- end
	local usedFiles = {}
	for i, name in ipairs(args.structOrder) do
		local struct = processed[name]
		setmetatable(struct.code, nil) -- just in case
		local fileName = getStructFile(name)
		code[fileName] = code[fileName] or {header = {}, source = {}, includes = {}}
		local currentCode = code[fileName]
		if not table.find(usedFiles, fileName) then
			multipleInsert(currentCode.header, #currentCode.header + 1, {
				"namespace mm" .. Game.Version,
				"{"
			})
			table.insert(usedFiles, fileName)
		end
		currentCode.header = table.join(currentCode.header, struct.code)
		multipleInsert(currentCode.header, #currentCode.header + 1, {
			"",
			"",
			""
		})
		if struct.staticDefinitionCode and #struct.staticDefinitionCode > 0 then
			currentCode.source = table.join(currentCode.source, struct.staticDefinitionCode)
			table.insert(currentCode.source, "")
		end
		for i, v in ipairs(struct.dependencies) do
			local depFileName = getStructFile(v)
			if not table.find(currentCode.includes, depFileName) and depFileName ~= fileName then
				table.insert(currentCode.includes, depFileName)
			end
		end
	end
	for fname, _ in pairs(structureByFile) do
		if code[fname] then
			local header = code[fname].header
			for i = 1, 3 do
				table.remove(header, #header)
			end
		end
	end
	--code = table.join(code, processed[name].code)
	--io.save("structs.h", table.concat(code, "\n"))
	for i, fileName in ipairs(usedFiles) do
		local currentCode = code[fileName]
		multipleInsert(currentCode.header, #currentCode.header + 1, {
			"}"
		})
	end
	if not isLast then
		io.save(pathToLoad, internal.persist(code))
	else
		if saveToGeneratorDirectory then
			os.remove("C:\\Users\\Eksekk\\source\\repos\\PGenEdit\\PGenEditDLL\\headers\\structs")
			os.remove("C:\\Users\\Eksekk\\source\\repos\\PGenEdit\\PGenEditDLL\\sources\\structs")
		else
			for p in path.find("C:\\Users\\Eksekk\\structOffsets\\*") do
				if not mem.dll.shlwapi.PathIsDirectoryA(p) then
					os.remove(p)
				end
			end
		end
		os.remove("C:\\Users\\Eksekk\\code.bin")
		for fileName in pairs(code) do
			local currentCode = code[fileName]
			local includeCode = {}
			for i, v in ipairs(currentCode.includes) do
				table.insert(includeCode, string.format("#include \"%s.h\"", v))
			end
			local prefix = {
				"#pragma once",
				"#include \"pch.h\"",
				"#include \"main.h\"",
			}
			if not saveToGeneratorDirectory then -- all header includes are in pch.h
				multipleInsert(prefix, #prefix + 1, includeCode)
			end
			multipleInsert(prefix, #prefix + 1, {
				"",
				"#pragma pack(push, 1)",
				"",
			})
			multipleInsert(currentCode.header, 1, prefix)
			multipleInsert(currentCode.header, #currentCode.header + 1, {
				"",
				"#pragma pack(pop)"
			})
			local headerFileName, sourceFileName
			if saveToGeneratorDirectory then
				headerFileName = string.format("C:\\Users\\Eksekk\\source\\repos\\PGenEdit\\PGenEditDLL\\headers\\structs\\%s.h", fileName)
				sourceFileName = string.format("C:\\Users\\Eksekk\\source\\repos\\PGenEdit\\PGenEditDLL\\sources\\structs\\%s.cpp", fileName)
			else
				headerFileName = string.format("%s\\MM%d\\%s.h", directoryPrefix or "C:\\Users\\Eksekk\\structOffsets", Game.Version, fileName)
				sourceFileName = string.format("%s\\MM%d\\%s.cpp", directoryPrefix or "C:\\Users\\Eksekk\\structOffsets", Game.Version, fileName)
			end
			local luaDataFileName = "C:\\Users\\Eksekk\\source\\repos\\PGenEdit\\luaData.cpp"
			io.save(headerFileName, table.concat(currentCode.header, "\n"))
			if #currentCode.source > 0 and saveToGeneratorDirectory then
				local prefix = {
					"#pragma once",
					"#include \"pch.h\"",
					"#include \"main.h\"",
				}
				multipleInsert(prefix, #prefix + 1, includeCode)
				table.insert(prefix, "")
				multipleInsert(currentCode.source, 1, prefix)
				io.save(sourceFileName, table.concat(currentCode.source, "\n"))
			end
			-- ptrName
			--tget(luaData, args.name, baseData.name).sizePtrName
			if saveToGeneratorDirectory then
				local content = {}
				for sname, fields in pairs(luaData) do
					for fname, field in pairs(fields) do
						local s = ""
						if field.ptrName then
							s = s .. string.format(", pointer name: %q", stripNamespaces(field.ptrName))
						end
						if field.sizePtrName then
							s = s .. string.format(", size field/pointer name: %q", stripNamespaces(field.sizePtrName))
						end
						table.insert(content, string.format("// struct %q, field name %q%s", stripNamespaces(sname), stripNamespaces(fname), s))
					end
				end
				io.save(luaDataFileName, table.concat(content, "\n"))
			else
				io.save(headerFileName:replace(fileName, "pch"), table.concat({
					"#pragma once"
				}, "\r\n"))
				io.save(headerFileName:replace(fileName, "main"), table.concat({
					"#pragma once",
					"#define JOIN(a, b) a ## b",
					"#define JOIN2(a, b) JOIN(a, b)",
					"#define SKIP(bytes) uint8_t JOIN2(unknown_, __COUNTER__)[bytes]",
					'#define SKIPBITS(bits) static_assert(bits <= 8, "Bit amount cannot be higher than 8 because MSVC compiler will not pack bitfields properly"); \\',
					"bool : bits // name is optional",
					"#include <array>",
					"#include <cstdint>",
				}, "\r\n"))
			end
		end
	end
end

function pr(str)
	reload();printStruct(str, nil, nil, nil, false, true)
end

function pr2(str)
	printStruct("GameStructure", nil, nil, nil, false, true)
end

function pr3(isLast)
	printStruct("GameStructure", nil, nil, nil, false, isLast)
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