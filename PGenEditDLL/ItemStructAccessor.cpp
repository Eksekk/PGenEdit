#include "pch.h"
#include "ItemStructAccessor.h"

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