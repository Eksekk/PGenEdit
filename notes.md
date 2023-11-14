# [Inventory control - player] link
- player items are index-independent, only usage is probably equipped items and Inventory[] array
- this means that we can't determine exactly whether inventory control item is the same one as any player item:
	- any item can be changed (enchant item, identify it, harden it etc.)
	- the position of same item in Items[] can change (drop item on the ground and pick it up again)
	- item can be removed (drop it or sell it)
- possible solutions:
	- checking for the best of our ability if items are likely the same (item fields, player equipped items, position in inventory)
	- hooking all item-related functions and modifying the control on the fly - extreme amount of work, and wouldn't work for cases like do stuff -> disable editor (if dll is loaded we could still track it, but user could always physically move the .dll out) -> do stuff -> enable editor again (will use old state!)

!!! solution:
- when loading editor, items are reloaded from game (except stored items) and assigned their indexes in Items[]
- while editor window is open, player can't interact with the game, in particular can't move items around, so no change will happen except ours
- item index set in first point can be used to manipulate it
- when exiting the editor, inventory ingame is automatically updated
That way we don't need to deal with item index while ingame, and during one editor opening it will be constant.

# Inventory control design
- control should allow drag-and-dropping items from item table into control, from control into item table, and from control into other inventory position
    - item dropped into table should be stored there and removed from control
	- item dropped into inventory (both control-control and table-control) should be placed at exact spot dropped if possible, then at any closest spot, then if there still is no space, error message should appear and action undone
- control should highlight the item in inventory when choosing item row in item table
- optionally (checkbox?), control should focus and highlight table row corresponding to mouseover item in the control
- should have game-specific backgrounds and look in the control

# Quest bit / award bit switcher panel design
- class and race promotion quests should be prioritized, grouped (maybe optionally [checkbox]) and done in a more robust way (like, add required item to a chest if already taken, reset mapvar in clanker's lab, respawn already killed monster etc.)
- multiple qbit trees (switchable with radio buttons) - show those that affect only: promotions, certain map, main questline, side quests etc.
- coloring of entries based on something?