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