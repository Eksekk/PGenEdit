pgenData = pgenData or {}

local M = {dll = _G.oldDll}
mem.dll.kernel32.SetDllDirectoryA("C:\\Users\\Eksekk\\source\\repos\\PartyGenerator\\Debug\\")
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
		if mem.dll.kernel32.GetModuleHandleA("PartyGenerator.dll") ~= 0 then
			mem.dll.kernel32.FreeLibrary(ptr)
		end
		events.Tick.Remove(runEventLoopOnce)
		runEventLoopOnce = nil
	end
end
-- M.dll.setClassData(json.encode(M.C()))

local FORMAT_MESSAGE_FROM_SYSTEM = 0x00001000
function M.loadDll()
	if not M.dll then
		M.dll = mem.LoadDll("PartyGenerator.dll")
		if not M.dll then
			local err = mem.dll.kernel32.GetLastError()
			local buffer = mem.allocMM(500)
            mem.dll.kernel32.FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, 0, err, 0, buffer, 500, 0);
			error(string.format("Couldn't load party generator dll! Error %d (message: \"%s\")", err, mem.string(buffer)))
			mem.freeMM(buffer)
			return
		end
		d = M.dll
		_G.oldDll = M.dll
		M.dll.setLuaState(getLuaState())
		M.dll.init()
		runEventLoopOnce = function() M.dll.runEventLoopOnce() end
		events.Tick = runEventLoopOnce
		M.dll.setClassData(json.encode(M.C()))
		M.dll.setSkillData(json.encode(M.Sk()))
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

if pgenData.ptrs then
	events.LoadMap.Remove(pgenData.ptrs)
	pgenData.ptrs = nil
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
--pgenData.ptrs = M.ptrs

--events.LoadMap = pgenData.ptrs

function M.reloadDll()
	M.unloadDll()
	M.loadDll()
end

function M.C()
	local ok
	ok, M.classData = pcall(require, "pgenData\\classData");
	package.loaded["pgenData\\classData"] = nil -- allow always reloading module
	return M.classData
end

function M.Sk()
	local ok
	ok, M.skillData = pcall(require, "pgenData\\skillData");
	package.loaded["pgenData\\skillData"] = nil
	return M.skillData
end

M.playerTypes = {caster = "caster", melee = "melee", ranged = "ranged", defensive = "defensive", utility = "utility"}

pgenData = pgenData or {}
function M.installKeyboardHandlers()
	M.removeKeyboardHandlers()
	pgenData.handlers = {}
	local function loadUnload(t)
		if t.Key == const.Keys.F3 and Game.CtrlPressed then
			t.Handled = true
			M.dll.displayControlPanel(true)
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
	table.insert(pgenData.handlers, loadUnload)
	events.AddFirst("KeyDown", loadUnload)
end

function M.removeKeyboardHandlers()
	if pgenData.handlers then
		for i, v in ipairs(pgenData.handlers) do
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

function mergeArraysShallowCopy(t1, t2, inplace) -- handles duplicate keys
	local tt = inplace and t1 or table.copy(t1)
	for i, v in ipairs(t2) do
		if not table.find(tt, v) then
			tt[#tt] = v
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

function M.reloadApi()
	dofile "C:\\Users\\Eksekk\\source\\repos\\PartyGenerator\\Scripts\\General\\PartyGeneratorApi.lua"
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

_G.oldDll = M.dll
return M