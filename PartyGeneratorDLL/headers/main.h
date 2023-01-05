#ifndef __MAIN_H__
#define __MAIN_H__
#include "pch.h"

struct lua_State;

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
#define SKIPBITS(bits) static_assert(bits <= 8, "Bit amount cannot be higher than 8 because MSVC compiler will not pack bitfields properly");\
    bool : bits // name is optional
//#define NEXTBYTE() int : 0 // allocates at next byte, can use skipbits instead

#define SAME(unknownType, knownType) std::is_same_v<std::decay_t<decltype(unknownType)>, knownType>
#define TYPE(x) std::decay_t<decltype(x)>

#define JSON_DIAGNOSTICS 1
#include <json.hpp>
using Json = nlohmann::json;

void MSGBOX(const char* text);

//using std::visit;

#endif // __MAIN_H__