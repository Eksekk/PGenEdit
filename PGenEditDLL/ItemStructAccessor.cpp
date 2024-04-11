#include "pch.h"
#include "ItemStructAccessor.h"
#include "LowLevel.h"

ItemStructAccessor* itemAccessor;

ItemStructAccessor* ItemStructAccessor::forItem(void* item)
{
    itemPtr = item;
    index = 0;
    return this;
}

ItemStructAccessor* ItemStructAccessor::nextItem()
{
    ++index;
    return this;
}

ItemStructAccessor::~ItemStructAccessor()
{

}

mm7::Item ItemStructAccessor::generateRandomItem(int strength, int type, bool alwaysEnchant /*= false*/)
{
    // return call(mmv(0x448790, 0x45664C, 0x453ECC), 1, pItems, assertnum(strength, 2), assertnum(type or 0, 2), self, alwaysEnchant and 1 or 0)
    void* itemsBlockStart = (char*)gameAccessor->getItemsTxtArrayData().ptr() - 4; // 4 less than real items txt address
    if (MMVER == 6)
    {
        mm6::Item item;
        memset(&item, 0, sizeof(item));
        callMemoryAddress(0x448790, 1, itemsBlockStart, strength, type, &item);
        return itemAccessor->forItem(&item)->convertToMM7Item();
    }
    else if (MMVER == 7)
	{
		mm7::Item item;
		memset(&item, 0, sizeof(item));
		callMemoryAddress(0x45664C, 1, itemsBlockStart, strength, type, &item);
		return item;
	}
	else if (MMVER == 8)
	{
		mm8::Item item;
		memset(&item, 0, sizeof(item));
		callMemoryAddress(0x453ECC, 1, itemsBlockStart, strength, type, &item, alwaysEnchant ? 1 : 0);
		return itemAccessor->forItem(&item)->convertToMM7Item();
	}
	else
	{
		throw std::runtime_error("Unsupported MM version");
	}
}

void ff()
{
    int x = 0;
    itemAccessor->forEachItemDo2(nullptr, 5, [&](auto var)
        {
            std::visit([&](auto ptr) {
                x = ptr->number;
                }, var);
        });
}

INSTANTIATE_CLASS_TEMPLATES_MM_GAMES(TemplatedItemStructAccessor, Item);