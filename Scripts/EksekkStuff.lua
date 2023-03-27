PGenEditData = PGenEditData or {}

local M = {dll = _G.oldDll}
mem.dll.kernel32.SetDllDirectoryA("C:\\Users\\Eksekk\\source\\repos\\PGenEdit\\Debug\\")
function events.GameInitialized1()
	-- speed up loading and unloading my dll by not unloading dependencies which don't change
	-- (they won't unload because this increments reference count)
	mem.LoadDll "wxmsw321ud_core_vc_custom.dll"
	mem.LoadDll "wxbase321ud_vc_custom.dll"
end
local runEventLoopOnce
local getLuaState
function M.unloadDll()
	--wtf = M.dll -- stack overflow
	--debug.Message"a"
	if M.dll then
		local ptr = M.dll["?ptr"]
		M.dll.unloadCleanup()
		mem.UnloadDll(M.dll)
		M.dll = nil
		_G.oldDll = nil
		d = nil
		-- loads twice for some reason
		if mem.dll.kernel32.GetModuleHandleA("PGenEdit.dll") ~= 0 then
			mem.dll.kernel32.FreeLibrary(ptr)
		end
		events.Tick.Remove(runEventLoopOnce)
		runEventLoopOnce = nil
	end
end
-- M.dll.setClassData(json.encode(M.C()))

local FORMAT_MESSAGE_FROM_SYSTEM = 0x00001000
function M.loadDll()
	if offsets.MMVersion ~= 7 then return end
	if not M.dll then
		M.dll = mem.LoadDll("PGenEdit.dll")
		if not M.dll then
			local err = mem.dll.kernel32.GetLastError()
			local buffer = mem.allocMM(500)
            mem.dll.kernel32.FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, 0, err, 0, buffer, 500, 0);
			local str = mem.string(buffer)
			mem.freeMM(buffer)
			error(string.format("Couldn't load party generator dll! Error %d (message: \"%s\")", err, str))
			return
		end
		d = M.dll
		_G.oldDll = M.dll
		M.dll.setLuaState(getLuaState())
		M.dll.setClassData(json.encode(M.C())) -- SET DATA BEFORE INIT
		M.dll.setSkillData(json.encode(M.Sk()))
		--M.dll.setMiscData(json.encode(M.getMiscData()))
		M.dll.init()
		runEventLoopOnce = function() M.dll.runEventLoopOnce() end
		events.Tick = runEventLoopOnce
		M.dll.runTests()
		rawset(M.dll, "runLua", M.dll.runLuaScriptFromDLL)
	end
end

function getLuaState()
	for k, v in pairs(debug.getregistry()) do
		if type(k) == "userdata" and getU(v, "HookData") then
			return
			mem.u4[
				tonumber(
					tostring(k):match("x([%dA-Fa-f]+)")
					, 16
				)
			]
		end
	end
end

if PGenEditData.ptrs then
	events.LoadMap.Remove(PGenEditData.ptrs)
	PGenEditData.ptrs = nil
end
function M.ptrs()
	if M.dll then
		local ptrs = mem.allocMM(4 * Party.Count)
		for i = 0, Party.Count - 1 do
			mem.u4[i * 4 + ptrs] = Party[i]["?ptr"]
		end
		M.dll.setPlayerPointers(ptrs)
		mem.freeMM(ptrs)
	end
end
--PGenEditData.ptrs = M.ptrs

--events.LoadMap = PGenEditData.ptrs

function M.reloadDll()
	M.unloadDll()
	M.loadDll()
end

function M.C()
	local ok
	ok, M.classData = pcall(require, "PGenEditData\\classData");
	package.loaded["PGenEditData\\classData"] = nil -- allow always reloading module
	return M.classData
end

function M.Sk()
	local ok
	ok, M.skillData = pcall(require, "PGenEditData\\skillData");
	package.loaded["PGenEditData\\skillData"] = nil
	return M.skillData
end

function M.getMiscData()
	local ok
	ok, M.miscData = pcall(require, "PGenEditData\\miscData");
	package.loaded["PGenEditData\\miscData"] = nil
	return M.miscData
end

M.playerTypes = {caster = "caster", melee = "melee", ranged = "ranged", defensive = "defensive", utility = "utility"}

PGenEditData = PGenEditData or {}
function M.installKeyboardHandlers()
	M.removeKeyboardHandlers()
	PGenEditData.handlers = {}
	local function loadUnload(t)
		if t.Key == const.Keys.F3 and Game.CtrlPressed then
			t.Handled = true
			M.dll.displayEditorMainWindow(true)
		elseif t.Key == const.Keys.F4 and Game.CtrlPressed then
			t.Handled = true
			if M.dll then
				M.unloadDll()
			else
				M.loadDll()
			end
		elseif t.Key == const.Keys.F5 and Game.CtrlPressed then
			t.Handled = true
			if M.dll.setClassData(json.encode(M.C())) then
				--MessageBox("Success!")
			end
		elseif t.Key == const.Keys.F6 and Game.CtrlPressed then
			t.Handled = true
			if M.dll.setSkillData(json.encode(M.Sk())) then
				--MessageBox("Success!")
			end
		end
	end
	table.insert(PGenEditData.handlers, loadUnload)
	events.AddFirst("KeyDown", loadUnload)
end

function M.removeKeyboardHandlers()
	if PGenEditData.handlers then
		for i, v in ipairs(PGenEditData.handlers) do
			events.Remove(v)
		end
	end
end
M.installKeyboardHandlers()

function universalEnum(t, array, unlimitedElementAmount)
	local meta = type(t) == "table" and getmetatable(t)
	local c = {}
	local i = 0
	for k, v in unpack(not meta and {(array and ipairs or pairs)(t or {})} or meta.members and {structs.enum(t)} or
		meta.__call and type(meta.__call) == "function" and {t} or {(array and ipairs or pairs)(t or {})}) do
		c[k] = v
		i = i + 1
		if i == 100000 and not unlimitedElementAmount then
			error("Infinite loop or more than 100000 elements (pass true as third argument to override)", 2)
		end
	end
	local key = array and (c[0] ~= nil and 0 or 1) or (next(c))
	return function()
		local v = c[key]
		if v ~= nil then
			local r1, r2 = key, v
			key = array and key + 1 or (next(c, key))
			return r1, r2
		end
	end
end

-- for k, v in universalEnum(Map.Facets) do print(k, v) end

function equalArrays(t1, t2)
	if #t1 ~= #t2 then return false end
	for i, v in universalEnum(t1, true) do
		if t2[i] ~= v then
			return false
		end
	end
	return true
end

table.findarray = function(t, a)
	for i, v in ipairs(t) do
		if type(v) == "table" and equalArrays(v, a) then
			return i
		end
	end
end

function selLen()
	local i = 0
	for k, v in pairs(Editor.Selection) do
		i = i + 1
	end
	return i
end

function selectAdjacentTextures(textures)
	if not Editor or not Editor.WorkMode then
		return error("Not in editor!")
	end
	local facetStack, processedFacets = {}, {}
	for k in pairs(Editor.Selection) do
		table.insert(facetStack, k)
	end
	if #facetStack == 0 then
		return error("Nothing selected!")
	end
	local textureIds = {}
	local _, x = next(textures)
	if type(x) == "string" then
		for i, b in Game.BitmapsLod.Bitmaps do
			if table.find(textures, b.Name:lower()) and not table.find(textureIds, i) then
				table.insert(textureIds, i)
			end
		end
	else
		textureIds = textures or {}
	end
	local vertexFacets = {}
	for fid, f in Map.Facets do
		for vid, v in f.VertexIds do
			v = Map.Vertexes[v]
			table.insert(tget(vertexFacets, v[1], v[2], v[3]), fid)
		end
	end
	local i = 0
	local facetStackLen = #facetStack
	while facetStackLen > 0 do
		i = i + 1
		local facetId = facetStack[facetStackLen] -- get last element
		facetStack[facetStackLen] = nil
		facetStackLen = facetStackLen - 1
		table.insert(processedFacets, facetId)
		local adjacentVertexes = {}
		for i, vertexId in Map.Facets[facetId].VertexIds do
			local v = Map.Vertexes[vertexId]
			local facetIds = vertexFacets[v[1] ][v[2] ][v[3] ] or {}
			for i, fid in ipairs(facetIds) do
				if not table.find(facetStack, fid) and not table.find(processedFacets, fid)
					and table.find(textureIds, Map.Facets[fid].BitmapId) then
					table.insert(facetStack, fid)
				end
			end
			vertexFacets[v[1] ][v[2] ][v[3] ] = nil -- vertex already processed
		end
	end
	for _, i in ipairs(processedFacets) do
		Editor.SelectSingleFacet(i)
	end
	Editor.UpdateSelectionState()
	return selLen()
end

sel = selectAdjacentTextures

local chT = {}
for i, b in Game.BitmapsLod.Bitmaps do
	if b.Name:lower():match("^gt") then
		table.insert(chT, b.Name:lower())
	end
end

function selectChest()
	--debug.Message(dump(t))
	return selectAdjacentTextures(table.copy(chT))
end

ch = selectChest

function F()
	local o = Mouse:GetTarget()
	if o.Kind == const.ObjectRefKind.Facet then
		return Map.Facets[o.Index]
	end
end

function bmpSize()
	local f = F()
	if f then
		local bmp = Game.BitmapsLod.Bitmaps[f.BitmapId]
		print(string.format("width: %d, height: %d", bmp.Width, bmp.Height))
	else
		print "No facet selected!"
	end
end

local function GetPlayer(ptr)
	local i = (ptr - Party.PlayersArray["?ptr"]) / Party.PlayersArray[0]["?size"]
	return i, Party.PlayersArray[i]
end

mmvAssert = function(ver)
	assert(Game.Version == ver, string.format("Wrong MM version, this script is for MM%d", ver))
end

local mapFileNamesToNames = {}
local fileNames = {}
function events.GameInitialized2()
	for _, msi in Game.MapStats do
		mapFileNamesToNames[msi.Name:lower()] = msi.FileName:lower()
		table.insert(fileNames, msi.FileName:lower())
	end
end

function mtm(str)
	-- show error instead of crashing game
	assert(mapFileNamesToNames[str:lower()] or table.find(fileNames, str:lower()), "Invalid map name")
	return evt.MoveToMap{Name = mapFileNamesToNames[str:lower()] or str}
end

M.mtm = mtm

function kill()
	for k, v in Map.Monsters do
		if v.Hostile then
			v.HP = 0
		end
	end
end

M.kill = kill

local mapIdsToItemNames = {}

function events.GameInitialized2()
	for i, entry in Game.ItemsTxt do
		mapIdsToItemNames[entry.Name:lower()] = i
	end
end

function item(id)
	evt.GiveItem{Id = mapIdsToItemNames[id] or id}
end

M.item = item

function increaseSpawnsInMapstats(infile, outfile, s, e, howMuch)
	local t = LoadBasicTextTable(infile, 0)
	for i = s, e do
		local index = i + 3
		local row = t[index]
		for j = 20, 28, 4 do
			local min, max = row[j]:match("(%d+)%-(%d+)")
			min = tonumber(min) or 0
			max = tonumber(max) or 0
			if max - min <= 0 then goto continue end
			min = min + howMuch
			max = max + howMuch
			row[j] = " " .. min .. "-" .. max
			::continue::
		end
	end
	WriteBasicTextTable(t, outfile)
end

function idm(pl, level, mastery)
	Party[pl].Skills[const.Skills.IdentifyMonster] = JoinSkill(level, mastery)
end
M.idm = idm

function deepcopyMM(t)
	local copy = {}
	if type(t) == "table" then -- only tables are passed by reference, and thus need copying
		local meta = getmetatable(t)
		local function copyRow(k, v)
			if type(v) == "table" then
				local meta = getmetatable(v)
				copy[k] = {}
				if meta and meta.members then
					for k2, v2 in structs.enum(v) do
						copy[k][k2] = (type(v2) == "table" and deepcopyMM(v2) or v2)
					end
				elseif meta and meta.__call and type(meta.__call) == "function" then
					for k2, v2 in v do
						copy[k][k2] = (type(v2) == "table" and deepcopyMM(v2) or v2)
					end
				else
					for k2, v2 in pairs(v) do
						copy[k][k2] = (type(v2) == "table" and deepcopyMM(v2) or v2)
					end
				end
			else
				copy[k] = v
			end
		end
		if meta and meta.members then
			for k2, v2 in structs.enum(t) do
				copy[k2] = (type(v2) == "table" and deepcopyMM(v2) or v2)
			end
		elseif meta and meta.__call and type(meta.__call) == "function" then
			for k, v in t do
				copyRow(k, v)
			end
		else
			for k, v in pairs(t) do
				copyRow(k, v)
			end
		end
		return copy
	else
		return t
	end
end

M.deepcopyMM = deepcopyMM

function multipleInsert(t, index, ...)
	local v = {...}
	if #v == 1 and type(v[1]) == "table" then
		v = v[1]
	end
	local shift = #v
	for i = #t, index, -1 do
		t[i + shift] = t[i]
	end
	for i = 1, #v do
		t[index + i - 1] = v[i]
	end
	return t
end

function getLocals(lev)
	lev = lev + 1 -- because current function call effectively reduces supplied stack level by 1
	local i = 1
	assert(debug.getinfo(lev, "f"), "Invalid stack level")
	local t = {}
	while true do
		local name, value = debug.getlocal(lev, i)
		if not name then break end
		t[name] = value
		i = i + 1
	end
	return t
end

getLs = getLocals

function dumpLocals(lev)
	lev = lev + 1
	for k, v in pairs(getLocals(lev)) do
		print(k, v)
	end
end

dumpL = dumpLocals

function findLocal(lev, name)
	lev = lev + 1
	local locals = getLocals(lev)
	if locals[name] ~= nil then
		return name, value
	end
end

findL = findLocal

function setLocal(lev, name, value)
	lev = lev + 1
	local i = 1
	local updateIndex -- set local with highest index (the "most local" one), since we return it in get and dump functions
	assert(debug.getinfo(lev, "f"), "Invalid stack level")
	while true do
		local localName = debug.getlocal(lev, i)
		if not localName then break end
		if localName == name then
			updateIndex = i
		end
		i = i + 1
	end
	if updateIndex then
		debug.setlocal(lev, updateIndex, value)
		return true
	end
	return false
end

setL = setLocal

function setLocalsTable(lev)
	LOCALS = M.deepcopyMM(getLocals(lev + 1))
end

setLT = setLocalsTable

function setLocalsTableAndDump(lev)
	lev = lev + 1
	locals = getLocals(lev)
	LOCALS = M.deepcopyMM(locals)
	for k, v in pairs(locals) do
		print(k, v)
	end
end

function table.findIf(t, func)
	for k, v in pairs(t) do
		if func(v, k) then
			return k, v
		end
	end
end

function table.map(t, func)
	local out = {}
	for k, v in pairs(t) do
		out[k] = func(v, k)
	end
	return out
end

function table.foreach(t, func)
	for k, v in pairs(t) do
		func(v, k)
	end
end

function table.filterFunc(t, func) -- filter is taken by merge
	local out = {}
	for k, v in pairs(t) do
		if func(v, k) then
			out[k] = v
		end
	end
	return out
end

function table.slice(tbl, first, last)
	local n = #tbl
	local tableFirstIndex = tbl[0] ~= nil and 0 or 1
	first = first or tableFirstIndex
	last = last or n
	local orig1, orig2 = first, last
	if first < 0 then
		first = n + first + 1
	end
	if last < 0 then
		last = n + last + 1
	end
	last = math.min(last, n)
	if first < tableFirstIndex or first > last then
		error(string.format("bad index values [%d, %d] (table size: %d)", orig1, orig2, n), 2)
	end
	local t = {}
	for i = first, last do
		t[i - first + 1] = tbl[i]
	end
	return t
end

function mergeArraysShallowCopy(t1, t2, inplace) -- handles duplicate keys
	local tt = inplace and t1 or table.copy(t1)
	for i, v in ipairs(t2) do
		if not table.find(tt, v) then
			tt[#tt + 1] = v
		end
	end
	return tt
end

function getUpvalue(f, name)
	local n, v = debug.findupvalue(f, name)
	return v
end

function upvalueDump(f) -- dump() doesn't work
	for k, v in debug.upvalues(f) do
		print(k, v)
	end
end

function getUpvalueByValue(f, val)
	for k, v in debug.upvalues(f) do
		if v == val then
			return k, v
		end
	end
end

dumpUpvalues = upvalueDump
getU = getUpvalue
getUbyV = getUpvalueByValue
dumpU = dumpUpvalues
MT = debug.getmetatable or getmetatable

function printSortedConst(c)
	for v, k in sortpairs(table.invert(c)) do
		print(k, v)
	end
end

function M.reloadApi()
	dofile "C:\\Users\\Eksekk\\source\\repos\\PGenEdit\\Scripts\\General\\PGenEditApi.lua"
end
M.reloadApi()

function debugTable(tbl) -- makes table print its contents in stacktrace instead of "(table: 0x0ff488f8)"
	local mt = getmetatable(tbl) or {}
	if not mt.__tostring then
		function mt.__tostring(t)
			rawset(getmetatable(t), "__tostring", nil)
			return dump(t)
		end
	end
	setmetatable(tbl, mt)
end

--[[
	MAW resurrection tests:
	> Party[3].Eradicated = -500000
	> Party[3].Eradicated = -50000000
	> Party[3].Eradicated = -50000000; Party[3].Dead = Game.Time
	> Party[3].Eradicated = Game.Time; Party[3].Dead = -9999999999
	> Party[3].Dead = -99999999
	> Party[3].Dead = -99999999
	> Party[3].Dead = -99999999; Party[3].Eradicated = 0
]]

-- MM6
-- 00417FD5
function keybindStruct(define)
	define[0x20].u4("action").u4("actionParam")
	[0x2C].u4("prevPtr").u4("nextPtr")
	[0x50].u1("virtualKeyCode")
end

return M