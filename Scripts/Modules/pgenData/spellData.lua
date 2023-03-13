data = {}

for id, spell in Game.Spells do
    data[id] = {}
    local sp, txt = Game.SpellsTxt[id]
    data.recoveryDelayByMastery = table.copy(spell.Delay)
    data.damageAddByMastery = {spell.DamageAdd, spell.DamageAdd, spell.DamageAdd, spell.DamageAdd}
    data.damageDiceSides = spell.DamageDiceSides

    data.name = txt.Name
    data.shortName = txt.shortName
    data.description = txt.Description
    data.rankDescriptions = {txt.Normal, txt.Expert, txt.Master, txt.GM}
    data.damageTypes = {txt.DamageType}
    data.manaCostByMastery = table.copy(txt.SpellPoints)
end