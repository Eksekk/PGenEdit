#ifndef __MAIN_H__
#define __MAIN_H__

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

#define SAME(unknownType, knownType) std::is_same_v<unknownType, knownType>
#define SAME_DECL(unknownType, knownType) SAME(decltype(unknownType), knownType)
#define BASE_TYPE(variable) decay_fully<decltype(variable)>
#define SAME_BASE_TYPE(variable, type) SAME(BASE_TYPE(variable), type)

#define JSON_DIAGNOSTICS 1
#include <json.hpp>
using Json = nlohmann::json;
using JsonException = Json::exception;

void MSGBOX(const char* text);

#define wxUSE_RC_MANIFEST 1 // make controls look much better

#define INSTANTIATE_TEMPLATES_SINGLE_GAME(game, ret, identifier) template ret identifier<mm##game::Player, mm##game::Game>()

#define INSTANTIATE_TEMPLATES_MM_GAMES(ret, identifier) \
INSTANTIATE_TEMPLATES_SINGLE_GAME(6, ret, identifier); \
INSTANTIATE_TEMPLATES_SINGLE_GAME(7, ret, identifier); \
INSTANTIATE_TEMPLATES_SINGLE_GAME(8, ret, identifier)

#define INSTANTIATE_CLASS_TEMPLATES_SINGLE_GAME(game, identifier, name) template class identifier<mm##game::name>

#define INSTANTIATE_CLASS_TEMPLATES_MM_GAMES(identifier, name) \
INSTANTIATE_CLASS_TEMPLATES_SINGLE_GAME(6, identifier, name); \
INSTANTIATE_CLASS_TEMPLATES_SINGLE_GAME(7, identifier, name); \
INSTANTIATE_CLASS_TEMPLATES_SINGLE_GAME(8, identifier, name)

#define INSTANTIATE_ACCESSOR_TEMPLATES_SINGLE_GAME(game, identifier, name) using identifier##_##game = Templated##identifier<mm##game::name>

#define INSTANTIATE_ACCESSOR_TEMPLATES_MM_GAMES(identifier, name) \
INSTANTIATE_ACCESSOR_TEMPLATES_SINGLE_GAME(6, identifier, name); \
INSTANTIATE_ACCESSOR_TEMPLATES_SINGLE_GAME(7, identifier, name); \
INSTANTIATE_ACCESSOR_TEMPLATES_SINGLE_GAME(8, identifier, name)

using byte_t = uint8_t;
using word_t = uint16_t;
using dword_t = uint32_t;
using qword_t = uint64_t;

using sbyte_t = int8_t;
using sword_t = int16_t;
using sdword_t = int32_t;
using sqword_t = int64_t;

using SimpleCallback = std::function<void()>;

/*#pragma comment( lib, "comctl32.lib")

#pragma comment( linker, "/manifestdependency:\"type='win32' \
        name='Microsoft.Windows.Common-Controls' version='5.82.19041.1110' \
        processorArchitecture='*' publicKeyToken='6595b64144ccf1df' \
        language='*'\"")*/


//using std::visit;

// undo system "instant edit + undo/redo" and "edit only on confirm + undo/redo" are equivalent -
// to implement second just rollback all edits in first if user didn't confirm

// I want to receive a table containg "?ptr" field and convert it to a pointer to a class, **based on rttr::type object**, not template parameter
// would need to support conversion of void* to all registered classes' object pointers, TODO: with checking the validity of the pointer? seems very hard to do
// for now lua will manage type checking and won't try to call a registered method of some class with other class name inside metatable
// it's required, because accessing existing C++ objects from lua can't work without it (rttr doesn't support something like reinterpret_cast<T*> based on rttr::type object)
template<typename T>
T* convertPtr(void* ptr, bool& ok)
{
    ok = true; // TODO: check if ptr is valid? seems very hard to do
    return static_cast<T*>(ptr);
}

template<typename T>
void registerPointerConversionFunc()
{
    rttr::type::register_converter_func(convertPtr<T>);
}

#endif // __MAIN_H__