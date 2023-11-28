﻿#include "pch.h"
#include "main.h"
ASSERT_SIZE(bool, 1);
ASSERT_SIZE(char, 1);
ASSERT_SIZE(short, 2);
ASSERT_SIZE(int, 4);
ASSERT_SIZE(long long, 8);
ASSERT_SIZE(float, 4);
ASSERT_SIZE(double, 8);
// long double omitted because it would be nice to allow either 8 (msvc) or 10 bytes, idk how to do that
ASSERT_SIZE(void*, 4);

void MSGBOX(const char* text)
{
	MessageBoxA(nullptr, text, nullptr, 0);
}

// link errors happen if these are not defined by me (shouldn't, there is RTTR's .cpp file which defines them)
// TODO: investigate more
const rttr::detail::public_access rttr::registration::public_access;
const rttr::detail::protected_access rttr::registration::protected_access;
const rttr::detail::private_access rttr::registration::private_access;

const TypeIds& TypeIds::findByType(rttr::type::type_id id)
{
    // TODO: better way to do this? this will be horrendously slow
    for (auto& [name, typeIds] : g_typeIdsByTypeName)
    {
        if (isTypeAnyOf(id, typeIds))
        {
            return typeIds;
        }
    }
    wxFAIL;
    return {};
}

bool TypeIds::isTypeAnyOf(rttr::type::type_id id, const TypeIds& typeIds)
{
    return typeIds.base == id || typeIds.pointer == id || typeIds.reference == id ||
        typeIds.const_ == id || typeIds.const_pointer == id || typeIds.const_reference == id ||
        typeIds.volatile_ == id || typeIds.volatile_pointer == id || typeIds.volatile_reference == id ||
        typeIds.const_volatile == id || typeIds.const_volatile_pointer == id || typeIds.const_volatile_reference == id;
}

bool TypeIds::isTypeAnyIndirection(rttr::type::type_id id)
{
    const TypeIds& typeIds = findByType(id);
    return typeIds.pointer == id || typeIds.reference == id ||
        typeIds.const_pointer == id || typeIds.const_reference == id ||
        typeIds.volatile_pointer == id || typeIds.volatile_reference == id ||
        typeIds.const_volatile_pointer == id || typeIds.const_volatile_reference == id;
}

bool TypeIds::isTypeAnyConst(rttr::type::type_id id)
{
    const TypeIds& typeIds = findByType(id);
    return typeIds.const_ == id || typeIds.const_pointer == id || typeIds.const_reference == id ||
        typeIds.const_volatile == id || typeIds.const_volatile_pointer == id || typeIds.const_volatile_reference == id;
}

bool TypeIds::isTypeAnyVolatile(rttr::type::type_id id)
{
const TypeIds& typeIds = findByType(id);
    return typeIds.volatile_ == id || typeIds.volatile_pointer == id || typeIds.volatile_reference == id ||
        typeIds.const_volatile == id || typeIds.const_volatile_pointer == id || typeIds.const_volatile_reference == id;
}

bool TypeIds::isTypeAnyPointer(rttr::type::type_id id)
{
    const TypeIds& typeIds = findByType(id);
    return typeIds.pointer == id || typeIds.const_pointer == id || typeIds.volatile_pointer == id || typeIds.const_volatile_pointer == id;
}

bool TypeIds::isTypeAnyReference(rttr::type::type_id id)
{
    const TypeIds& typeIds = findByType(id);
    return typeIds.reference == id || typeIds.const_reference == id || typeIds.volatile_reference == id || typeIds.const_volatile_reference == id;
}
