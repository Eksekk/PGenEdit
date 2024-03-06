#pragma once
#include "main.h"
#include "StructAccessor.h"
#include "Utility.h"
#include "accessorCommonCode.h"

class MapChestStructAccessor;
template<typename T>
class TemplatedMapChestStructAccessor;

extern MapChestStructAccessor* chestAccessor;

class MapChestStructAccessor : public StructAccessorGenericFor
{
protected:
	void* chest;
public:
	static const int CHEST_CELL_WIDTH = 12, CHEST_CELL_HEIGHT = 9; // FIXME: check actual numbers
	inline MapChestStructAccessor* forChest(void* ptr)
	{
		chest = ptr;
		return this;
	}
	inline void* getCurrentChestPtr()
	{
		return chest;
	}

	virtual std::optional<ItemInInventoryData> addItem(const mm7::Item& item) = 0;
	virtual std::vector<ItemInInventoryDataWithItem> getItems() = 0;

	virtual InventoryPosition getItemInventoryPosition(void* itemsArrayEntryPtr) = 0;
	virtual bool moveItemToInventoryPosition(void* itemsArrayEntryPtr, const InventoryPosition& position) = 0;
	virtual bool moveItemToInventoryPosition(void* itemsArrayEntryPtr, int x, int y) = 0;
	virtual std::optional<ItemInInventoryData> addItemToInventory(const mm7::Item& item) = 0;

	template<typename Function> auto forEachItemDo(Function&& func, int first = 0)
	{
		return versionBasedAccessorDispatch(
			TemplatedMapChestStructAccessor<mm6::MapChest>::forEachItemDo,
			TemplatedMapChestStructAccessor<mm7::MapChest>::forEachItemDo,
			TemplatedMapChestStructAccessor<mm8::MapChest>::forEachItemDo,
			std::forward<Function>(func),
			first
		);
	}

	virtual void addItemToChest(int chestIndex, mm7::Item& item) = 0;
};

template<typename ChestType>
class TemplatedMapChestStructAccessor : public MapChestStructAccessor, public StructAccessor<ChestType, mm6::MapChest, mm7::MapChest, mm8::MapChest>
{
	using ItemType = std::remove_pointer_t<std::decay_t<decltype(ChestType::items.at(0))>>;
	ChestType* getChestToAffect() 
	{ 
		return static_cast<ChestType*>(chest); 
	}

	ItemType* getItemToAffect(void* item) 
	{ 
		return static_cast<ItemType*>(item); 
	}

	template<typename Function>
	auto forEachItemDo(Function&& func, int first = 0)
	{
		auto chest = getChestToAffect();
		int size = (int)chest->items.size();
		for (int i = first; i < size; i++)
		{
			accessorDetail::callWithOptionalIndexParam(&chest->items[i], i, std::forward<Function>(func));
		}
	}
public:
	virtual InventoryPosition getItemInventoryPosition(void* itemsArrayEntryPtr) override
	{
		return accessorDetail::getItemInventoryPosition(getChestToAffect(), getItemToAffect(itemsArrayEntryPtr), CHEST_CELL_WIDTH, CHEST_CELL_HEIGHT);
	}
	// Inherited via MapChestStructAccessor
	std::optional<ItemInInventoryData> addItem(const mm7::Item& item) override
	{
		return accessorDetail::addItemToInventory(getChestToAffect(), item, CHEST_CELL_WIDTH, CHEST_CELL_HEIGHT);
	}
	std::vector<ItemInInventoryDataWithItem> getItems() override
	{
		std::vector<ItemInInventoryDataWithItem> items;
		size_t maxItems = getChestToAffect()->items.size();
		forEachItemDo([&](AnyItemStruct auto* item, int index)
			{
				items.push_back({ getItemInventoryPosition(item), index, itemAccessor->forItem(item)->convertToMM7Item() });
			}, maxItems);
		return items;
	}

	// Inherited via MapChestStructAccessor
	bool moveItemToInventoryPosition(void* itemsArrayEntryPtr, const InventoryPosition& position) override
	{
		return false;
	}
	bool moveItemToInventoryPosition(void* itemsArrayEntryPtr, int x, int y) override
	{
		return false;
	}
	std::optional<ItemInInventoryData> addItemToInventory(const mm7::Item& item) override
	{
		return std::optional<ItemInInventoryData>();
	}

	// Inherited via MapChestStructAccessor
	void addItemToChest(int chestIndex, mm7::Item& item) override
	{
	}
};

INSTANTIATE_ACCESSOR_TEMPLATES_MM_GAMES(MapChestStructAccessor, MapChest);
