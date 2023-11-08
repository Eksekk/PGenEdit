#pragma once
#include "main.h"
#include "InventoryCtrl.h"
#include "GameData.h"

// this doesn't belong to inventoryControl, because the inventory control uses identical wrapper classes for items,
// while this deals in pointers and various templated types
template<typename EntityTypeT, typename ItemTypeT>
    requires (AnyPlayerStruct<EntityTypeT> || AnyMapChestStruct<EntityTypeT>) && AnyItemStruct<ItemTypeT>
             && (GameSpecificStructs<EntityTypeT>::gameVersion == GameSpecificStructs<ItemTypeT>::gameVersion)
InventoryPosition getItemInventoryPosition(EntityTypeT* entity, ItemTypeT* item, int inventoryWidth, int inventoryHeight)
{
    // (Items index) for main item cell,  -(1 + main Inventory cell index) for other cells
    double dblIndex = ((dword_t)item - (dword_t)&entity->items) / (double)sizeof(ItemType);
    size_t index = (dword_t)dblIndex;
    wxASSERT_MSG(dblIndex == index,
        wxString::Format("Got invalid index (%.3f) for item at 0x%X (entity types: '%s', '%s'",
            dblIndex, (dword_t)item, typeid(EntityTypeT).name(), typeid(ItemTypeT).name()
        )
    );
    auto& playerItem = GameData::items.at(item->number);
    int i = 0;
    for (const auto& whatCellContains : entity->inventory)
    {
        if (whatCellContains == index)
        {
            int x = i % inventoryWidth;
            int y = i / inventoryWidth;
            wxASSERT_MSG(x + playerItem->inventoryWidth < inventoryWidth && y + playerItem->inventoryHeight < inventoryHeight,
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

template<typename EntityType, typename ItemType>
    requires (AnyPlayerStruct<EntityType> || AnyMapChestStruct<EntityType>) && AnyItemStruct<ItemType>
             && (GameSpecificStructs<EntityType>::gameVersion == GameSpecificStructs<ItemType>::gameVersion)
bool setItemInventoryPosition(EntityType* entity, ItemType* item, int inventoryWidth, int inventoryHeight, int newX, int newY)
{
    // (Items index) for main item cell,  -(1 + main Inventory cell index) for other cells
    double dblIndex = ((dword_t)item - (dword_t)&entity->items) / (double)sizeof(ItemType);
    size_t index = (dword_t)dblIndex;
    wxASSERT_MSG(dblIndex == index,
        wxString::Format("Got invalid index (%.3f) for item at 0x%X (entity types: '%s', '%s'",
            dblIndex, (dword_t)item, typeid(EntityType).name(), typeid(ItemType).name()
        )
    );
    // check if item at destination slot wouldn't cross inventory bounds
    auto& playerItem = GameData::items.at(item->number);
    wxASSERT_MSG(newX + playerItem->inventoryWidth < inventoryWidth && newY + playerItem->inventoryHeight < inventoryHeight,
        wxString::Format("Cannot place item at the requested inventory position (x: %d, y: %d), because item size at that spot exceeds inventory size"
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
                int itemIndex = whatCellContains > 0 ? whatCellContains : -(whatCellContains + 1);
                wxFAIL_MSG(wxString::Format(
                    "Inventory cell (x: %d, y: %d) is occupied by another item (index in 'Items' array: %d)",
                    x, y, itemIndex
                ));
                return false;
            }
        }
    }
    // move item
    int i = 0;
    for (auto& whatCellContains : entity->inventory)
    {
        if (whatCellContains == index)
        {
            // since we're going left-right and top-bottom, first cell with item will always be top-left
            int w = playerItem->inventoryWidth, h = playerItem->inventoryHeight;
            int oldX = i % inventoryWidth, oldY = i / inventoryWidth;
            for (int yOffset = 0; yOffset < h; ++yOffset)
            {
                for (int xOffset = 0; xOffset < w; ++xOffset)
                {
                    int currentOldX = oldX + xOffset, currentOldY = oldY + yOffset;
                    int currentNewX = newX + xOffset, currentNewY = newY + yOffset;
                    auto& oldVal = entity->inventory[currentOldX + currentOldY * inventoryWidth];
                    entity->inventory[currentNewX + currentNewY * inventoryWidth] = oldVal;
                    oldVal = 0;
                }
            }
            return true;
        }
        ++i;
    }
    return false;
}