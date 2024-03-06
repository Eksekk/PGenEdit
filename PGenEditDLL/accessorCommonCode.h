#pragma once
#include "main.h"
#include "GameData.h"
#include "Utility.h"

namespace accessorDetail
{
    template<typename EntityTypeT, typename ItemTypeT>
    concept EntityItemTypesMatch = (AnyPlayerStruct<EntityTypeT> || AnyMapChestStruct<EntityTypeT>) && AnyItemStruct<ItemTypeT>
        && (GameSpecificStructs<EntityTypeT>::gameVersion == GameSpecificStructs<ItemTypeT>::gameVersion);

    extern std::stringstream ss;
    void printInventory(int itemSize, const void* p, int width, int height);

    template<typename EntityTypeT>
        requires AnyPlayerStruct<EntityTypeT> || AnyMapChestStruct<EntityTypeT>
    void printInventory(EntityTypeT* entity, int width, int height)
    {
        printInventory(sizeof(entity->inventory.value_type), &entity->inventory, width, height);
    }

    // this doesn't belong to inventoryControl, because the inventory control uses identical wrapper classes for items,
    // while this deals in pointers and various templated types
    template<typename EntityTypeT, typename ItemTypeT>
        requires EntityItemTypesMatch<EntityTypeT, ItemTypeT>
    InventoryPosition getItemInventoryPosition(const EntityTypeT* entity, const ItemTypeT* item, int inventoryWidth, int inventoryHeight)
    {
        // (Items index) for main item cell,  -(1 + main Inventory cell index) for other cells
        double itemsArrayIndexDbl = ((dword_t)item - (dword_t)&entity->items) / (double)sizeof(ItemTypeT);
        size_t itemsArrayIndex = (dword_t)itemsArrayIndexDbl;
        wxASSERT_MSG(itemsArrayIndexDbl == itemsArrayIndex,
            wxString::Format("Got invalid index (%.3f) for item at 0x%X (entity types: '%s', '%s'",
                itemsArrayIndexDbl, (dword_t)item, typeid(EntityTypeT).name(), typeid(ItemTypeT).name()
            )
        );
        ++itemsArrayIndex; // 0-based to 1-based
        auto& playerItem = GameData::items.at(item->number);
        int i = 0;
        for (const auto& whatCellContains : entity->inventory)
        {
            if (whatCellContains == itemsArrayIndex)
            {
                int x = i % inventoryWidth;
                int y = i / inventoryWidth;
                wxASSERT_MSG(x + playerItem->inventoryWidth <= inventoryWidth && y + playerItem->inventoryHeight <= inventoryHeight,
                    wxString::Format("Found invalid item position in inventory (x: %d, y: %d) - inventory size is x: %d, y: %d, item size (width: %d, height: %d)",
                        x, y, inventoryWidth, inventoryHeight, playerItem->inventoryWidth, playerItem->inventoryHeight
                    )
                );
                return InventoryPosition{ x, y };
            }
            ++i;
        }
        return InventoryPosition::invalid();
    }

    // this one doesn't need entity or item types to match, because it uses only "number" field of item and doesn't depend on its specific format/size
    template<typename EntityTypeT, typename ItemTypeT>
        //requires EntityItemTypesMatch<EntityTypeT, ItemTypeT>
    bool canItemBePlacedAtInventoryPosition(const EntityTypeT* entity, const ItemTypeT* item, int inventoryWidth, int inventoryHeight, int newX, int newY)
    {
        auto& playerItem = GameData::items.at(item->number);
        wxASSERT_MSG(newX + playerItem->inventoryWidth <= inventoryWidth && newY + playerItem->inventoryHeight <= inventoryHeight,
            wxString::Format("Invalid potential item position (x: %d, y: %d), because item size at that spot exceeds inventory size"
                "(width: %d, height: %d), item dimensions are (width: %d, height: %d)",
                newX, newY, inventoryWidth, inventoryHeight, playerItem->inventoryWidth, playerItem->inventoryHeight
            )
        );
        // check if all destination slots are free
        for (int yAdd = 0; yAdd < playerItem->inventoryHeight; ++yAdd)
        {
            for (int xAdd = 0; xAdd < playerItem->inventoryWidth; ++xAdd)
            {
                int x = newX + xAdd, y = newY + yAdd;
                int inventoryIndex = y * inventoryWidth + x;
                auto& whatCellContains = entity->inventory[inventoryIndex];
                if (whatCellContains != 0)
                {
                    int itemIndex = whatCellContains > 0 ? whatCellContains : entity->inventory[-(whatCellContains + 1)];
                    wxFAIL_MSG(wxString::Format(
                        "Inventory cell (x: %d, y: %d) is occupied by another item (index in 'Items' array: %d)",
                        x, y, itemIndex
                    ));
                    return false;
                }
            }
        }
        return true;
    }

    template<typename EntityTypeT, typename ItemTypeT>
        requires EntityItemTypesMatch<EntityTypeT, ItemTypeT>
    bool setItemInventoryPosition(EntityTypeT* entity, const ItemTypeT* item, int inventoryWidth, int inventoryHeight, int newX, int newY)
    {
        // (Items index) for main item cell,  -(1 + main Inventory cell index) for other cells
        double dblIndex = ((dword_t)item - (dword_t)&entity->items) / (double)sizeof(ItemTypeT);
        size_t itemsArrayIndex = (dword_t)dblIndex;
        wxASSERT_MSG(dblIndex == itemsArrayIndex,
            wxString::Format("Got invalid index (%.3f) for item at 0x%X (entity types: '%s', '%s'",
                dblIndex, (dword_t)item, typeid(EntityTypeT).name(), typeid(ItemTypeT).name()
            )
        );
        ++itemsArrayIndex; // 0-based to 1-based
        // check if item at destination slot wouldn't cross inventory bounds
        auto& playerItem = GameData::items.at(item->number);
        wxASSERT_MSG(newX + playerItem->inventoryWidth <= inventoryWidth && newY + playerItem->inventoryHeight <= inventoryHeight,
            wxString::Format("Cannot place item at the requested inventory position (x: %d, y: %d), because item size at that spot exceeds inventory size"
                "(itemSizeHorizontal: %d, height: %d), item dimensions are (itemSizeHorizontal: %d, height: %d)",
                newX, newY, inventoryWidth, inventoryHeight, playerItem->inventoryWidth, playerItem->inventoryHeight
            )
        );
        if (!canItemBePlacedAtInventoryPosition(entity, item, inventoryWidth, inventoryHeight, newX, newY))
        {
            return false;
        }
        // move item
        int currentInventoryCellIndex = 0;
        for (auto& whatCellContains : entity->inventory)
        {
            if (whatCellContains == itemsArrayIndex) // found main Inventory[] cell of item
            {
                // since we're going left-right and top-bottom, first cell with item will always be top-left
                int itemSizeHorizontal = playerItem->inventoryWidth, itemSizeVertical = playerItem->inventoryHeight;
                int oldX = currentInventoryCellIndex % inventoryWidth, oldY = currentInventoryCellIndex / inventoryWidth;
                entity->inventory[currentInventoryCellIndex] = 0; // clear first cell of old position
                int inventoryArrayIndexToUse = newY * inventoryWidth + newX;
                entity->inventory[inventoryArrayIndexToUse] = itemsArrayIndex; // set first cell (Items[] index) of new position
                for (int yOffset = 0; yOffset < itemSizeVertical; ++yOffset)
                {
                    for (int xOffset = 0; xOffset < itemSizeHorizontal; ++xOffset)
                    {
                        if (!xOffset && !yOffset)
                        {
                            continue; // first cell
                        }
                        int currentOldX = oldX + xOffset, currentOldY = oldY + yOffset;
                        int currentNewX = newX + xOffset, currentNewY = newY + yOffset;
                        entity->inventory[currentOldX + currentOldY * inventoryWidth] = 0; // clear old cell
                        entity->inventory[currentNewX + currentNewY * inventoryWidth] = -(inventoryArrayIndexToUse + 1); // set new cell (uses Inventory[] index)
                    }
                }
                return true;
            }
            ++currentInventoryCellIndex;
        }
        return false;
    }

    // returns whether item was successfully inserted or not (due to lack of space)
    template<typename EntityTypeT>
    std::optional<ItemInInventoryData> addItemToInventory(EntityTypeT* entity, const mm7::Item& item, int inventoryWidth, int inventoryHeight)
	{
		auto& playerItem = GameData::items.at(item.number);
		for (int y = 0; y <= inventoryHeight - playerItem->inventoryHeight; ++y)
		{
			for (int x = 0; x <= inventoryWidth - playerItem->inventoryWidth; ++x)
			{
				if (canItemBePlacedAtInventoryPosition(entity, &item, inventoryWidth, inventoryHeight, x, y))
				{
                    // find free slot in Items[] array
                    int itemsArrayIndex = 1;
                    while (entity->items[itemsArrayIndex].number != 0)
                    {
                        ++itemsArrayIndex;
                    }
					int inventoryArrayIndexToUse = y * inventoryWidth + x;
					entity->inventory[inventoryArrayIndexToUse] = itemsArrayIndex; // set first cell (Items[] index) of new position
					for (int yOffset = 0; yOffset < playerItem->inventoryHeight; ++yOffset)
					{
						for (int xOffset = 0; xOffset < playerItem->inventoryWidth; ++xOffset)
						{
							if (!xOffset && !yOffset)
							{
								continue; // first cell
							}
							entity->inventory[x + xOffset + (y + yOffset) * inventoryWidth] = -(inventoryArrayIndexToUse + 1); // set new cell (uses Inventory[] index)
						}
					}
                    return ItemInInventoryData({ x, y }, itemsArrayIndex);
				}
			}
		}
		return std::nullopt;
	}

} // namespace accessorDetail