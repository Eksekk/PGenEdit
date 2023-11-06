#include "pch.h"
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