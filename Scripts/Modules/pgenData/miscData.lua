local data = {}

data.primaryStats = {
    ["0"] = {name = Game.StatNames[0], blackPotionId = 270}, -- might
    ["1"] = {name = Game.StatNames[1], blackPotionId = 266}, -- intellect
    ["2"] = {name = Game.StatNames[2], blackPotionId = 268}, -- personality
    ["3"] = {name = Game.StatNames[3], blackPotionId = 267}, -- endurance
    ["4"] = {name = Game.StatNames[4], blackPotionId = 269}, -- accuracy
    ["5"] = {name = Game.StatNames[5], blackPotionId = 265}, -- speed
    ["6"] = {name = Game.StatNames[6], blackPotionId = 264}, -- luck
}

data.resistances = {}
local function doRes(name)
    data.resistances[tostring(const.Stats[name .. "Resistance"])] = {
        name = name, exclusive = false, resistanceSpell = const.Spells[name .. "Resistance"], groupResistanceSpell = const.Spells.DayOfProtection
    }
end
for i, v in ipairs{"Fire", "Air", "Water", "Earth", "Mind", "Body"} do
    doRes(v)
end

data.resistances[tostring(const.Stats.SpiritResistance])] = {
    name = name, exclusive = true
}
data.resistances["-2"] = { -- negative, because there's no builtin stat corresponding to it, so they need to be treated individually
    name = "Light", exclusive = true, builtinSpecial = "light" -- identify stat by builtinSpecial
}
data.resistances["-3"] = {
    name = "Dark", exclusive = true, builtinSpecial = "dark"
}

return data