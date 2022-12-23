#ifndef __MAIN_H__
#define __MAIN_H__
#include "pch.h"
#include "Logger.h"


#define BUILD_DLL
#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

// C++ requires a string literal for static_assert, even with constexpr...

// checks that type has required size and generates compiler error if not
#define ASSERT_SIZE(type, size) static_assert(sizeof(type) == size, "\"" #type "\" has not supported size (" #size " expected)")

#define DLL_EXPORT __declspec(dllexport)
#define JOIN(a, b) a ## b
#define JOIN2(a, b) JOIN(a, b)
#define SKIP(bytes) uint8_t JOIN2(unknown_, __COUNTER__)[bytes]
#define SKIPBITS(bits) int : bits // name is optional
#define NEXTBYTE() int : 0 // allocates at next byte

#define SAME(unknownType, knownType) std::is_same_v<std::decay_t<decltype(unknownType)>, knownType>

struct Json;

void MSGBOX(const char* text);

//using std::visit;

#endif // __MAIN_H__