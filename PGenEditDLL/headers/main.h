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

#include "CreateObjectVisitor.h"
#include <rttr/registration.h>

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
void* convertPtrToVoid(T* ptr, bool& ok)
{
    ok = true; // TODO: check if ptr is valid? seems very hard to do
    return reinterpret_cast<void*>(ptr);
}

template<typename T>
void registerPointerConversionFunc()
{
    rttr::type::register_converter_func(convertPtr<T>);
    rttr::type::register_converter_func(convertPtrToVoid<T>);
}

struct TypeIds
{
    // basic types
    rttr::type::type_id base, pointer, reference;
    // const types
    rttr::type::type_id const_, const_pointer, const_reference, pointer_to_const;
    // volatile types
    rttr::type::type_id volatile_, volatile_pointer, volatile_reference, pointer_to_volatile;
    // const volatile types
    rttr::type::type_id const_volatile, const_volatile_pointer, const_volatile_reference, pointer_to_const_volatile;

    static TypeIds findByType(rttr::type::type_id id);
    static bool isTypeAnyOf(rttr::type::type_id id, const TypeIds& typeIds);
    bool isTypeAnyOf(rttr::type::type_id id) const;
    // pointers and references
    static bool isTypeAnyIndirection(rttr::type::type_id id);
    static bool isTypeAnyConst(rttr::type::type_id id);
    static bool isTypeAnyVolatile(rttr::type::type_id id);
    static bool isTypeAnyPointer(rttr::type::type_id id);
    static bool isTypeAnyReference(rttr::type::type_id id);
};

// causes "static order initialization fiasco" problem, because reflection registration functions, which should also insert type ids, might run before this variable is initialized
// extern std::map<std::string, TypeIds> g_typeIdsByTypeName;
// wrap in function to avoid the problem
std::map<std::string, TypeIds>& g_getTypeIdsByTypeName();

template<typename T>
TypeIds& getTypeIds()
{
    return g_getTypeIdsByTypeName().at(rttr::type::get<T>().get_name().to_string());
}

TypeIds& getTypeIds(const std::string& str)
{
    return g_getTypeIdsByTypeName().at(str);
}

TypeIds& getTypeIds(const rttr::type& t)
{
    return g_getTypeIdsByTypeName().at(t.get_name().data());
}

template<typename T>
void generateTypeIdData()
{
    TypeIds typeIds;
    using rttr::type;
    if constexpr (!SAME(T, void)) // can't get reference to "void" type
    {
        typeIds.base = type::get<T>().get_id();
        typeIds.const_ = type::get<const T>().get_id();
        typeIds.volatile_ = type::get<volatile T>().get_id();
        typeIds.const_volatile = type::get<const volatile T>().get_id();
        typeIds.reference = type::get<T&>().get_id();
        typeIds.volatile_reference = type::get<volatile T&>().get_id();
        typeIds.const_volatile_reference = type::get<const volatile T&>().get_id();
        typeIds.const_reference = type::get<const T&>().get_id();
    }
    typeIds.pointer = type::get<T*>().get_id(), typeIds.pointer_to_const = type::get<const T*>().get_id(), typeIds.const_pointer = type::get<T* const>().get_id();
typeIds.pointer_to_volatile = type::get<volatile T*>().get_id(), typeIds.volatile_pointer = type::get<T* volatile>().get_id();
typeIds.pointer_to_const_volatile = type::get<const volatile T*>().get_id(), typeIds.const_volatile_pointer = type::get<T* const volatile>().get_id();
    g_getTypeIdsByTypeName()[type::get<T>().get_name().to_string()] = typeIds;
}

template<typename T>
concept canConvertToContainer = requires // can't register conversion functions for abstract classes / those that invoke deleted function in constructor etc.
{
    T();
    T(static_cast<const T&>(std::declval<T>()));
};

namespace toContainer
{
    // this struct's only purpose is to be passed to conversion function to indicate that it should return empty vector (make it somewhat type-safe)
    struct vector {};
    struct array {};
}

template<typename ValType, size_t s>
void registerArrayConversionFunctions()
{
    using namespace toContainer;
    auto f = [](const array& val, bool& ok)->std::array<ValType, s>
    {
        ok = true;
        return std::array<ValType, s>{ };
    };
    rttr::type::register_converter_func(f);
    if constexpr (s < 50)
    {
        registerArrayConversionFunctions<ValType, s + 1>();
    }
}

template<typename T>
void registerContainerConversionFunctions()
{
    using namespace toContainer;
//     auto f = [](const T& val, bool& ok) -> std::vector<T>
//         {
//             ok = true;
//             return std::vector<T>{ };
//         };
//     rttr::type::register_converter_func(f);
//     rttr::type::register_converter_func([](const auto& val, bool& ok) -> std::vector<std::decay_t<decltype(val)>>
//         {
//             ok = true;
//             return std::vector{ val };
//         });
    //registerArrayConversionFunctions<T, 0>();
    //rttr::registration::class_<std::vector<T>>().constructor<>();
}

template<typename T>
void registerExtra()
{
    generateTypeIdData<T>();
    registerPointerConversionFunc<T>();
    if constexpr (canConvertToContainer<T>)
    {
        registerContainerConversionFunctions<T>();
    }
}

using CreateContainerFunc = rttr::variant(*)();

template<typename T>
rttr::variant getEmptyVector()
{
    return std::vector<T>{ };
}

const std::string g_CONTAINER_CREATION_FUNC_METADATA_NAME = "creationFunctions";
template<typename... Types>
auto getParameterMetadata()
{
    std::vector<CreateContainerFunc> funcs{ []() -> rttr::variant { return Types(); }... };
    return rttr::metadata(g_CONTAINER_CREATION_FUNC_METADATA_NAME, funcs);
}

void g_initCommonTypeIds();

// allow using global functions with different calling convention than project default
// (RTTR defines only those without explicit calling convention, which then use project default)
namespace rttr::detail
{
#define DEFINE_CALLING_CONV_NOEXCEPT(conv) \
    template<typename R, typename... Args> \
    struct is_functor<R(conv*)(Args...) noexcept> : std::true_type {}; \
\
    template<typename R, typename... Args>\
    struct is_functor<R(conv&)(Args...) noexcept> : std::true_type {}; \
\
    template<typename R, typename... Args>\
    struct function_traits<R(conv*)(Args...) noexcept> : function_traits<R(Args...)> {};\
\
    template<typename R, typename... Args>\
    struct function_traits<R(conv&)(Args...) noexcept> : function_traits<R(Args...)> {}
    
#define DEFINE_CALLING_CONV(conv) \
    template<typename R, typename... Args> \
    struct is_functor<R(conv*)(Args...)> : std::true_type {}; \
\
    template<typename R, typename... Args> \
    struct is_functor<R(conv&)(Args...)> : std::true_type {}; \
\
    template<typename R, typename... Args>\
    struct function_traits<R(conv*)(Args...)> : function_traits<R(Args...)> {};\
\
    template<typename R, typename... Args>\
    struct function_traits<R(conv&)(Args...)> : function_traits<R(Args...)> {}

    // TODO: these give "class template has already been defined" error if used with project default calling convention
    // proper solution will have to wait, for now just commenting it out

    //DEFINE_CALLING_CONV(__cdecl);
    DEFINE_CALLING_CONV(__stdcall);
    DEFINE_CALLING_CONV(__thiscall);
    DEFINE_CALLING_CONV(__fastcall);

#ifndef RTTR_NO_CXX17_NOEXCEPT_FUNC_TYPE
    //DEFINE_CALLING_CONV_NOEXCEPT(__cdecl);
    DEFINE_CALLING_CONV_NOEXCEPT(__stdcall);
    DEFINE_CALLING_CONV_NOEXCEPT(__thiscall);
    DEFINE_CALLING_CONV_NOEXCEPT(__fastcall);
#endif

#undef DEFINE_CALLING_CONV_NOEXCEPT
#undef DEFINE_CALLING_CONV
}

// formatter specializations for rttr types and more
namespace std
{
    // note: you need to implement both functions, otherwise it won't work
    template<>
    struct formatter<rttr::string_view>
    {
        template<typename ParseContext>
        constexpr auto parse(ParseContext& ctx)
        {
            return ctx.begin();
        }

        template<typename FormatContext>
        auto format(const rttr::string_view& p, FormatContext& ctx) const
        {
            return format_to(ctx.out(), "{}", p.to_string());
        }
    };

    // for rttr::type, returns name of the type
	template<>
	struct formatter<rttr::type>
	{
		template<typename ParseContext>
		constexpr auto parse(ParseContext& ctx)
		{
			return ctx.begin();
		}

		template<typename FormatContext>
		auto format(const rttr::type& p, FormatContext& ctx) const
		{
			return format_to(ctx.out(), "<RTTR type '{}'>", p.get_name().to_string());
		}
	};

    // for rttr::variant, returns name of the type (because converting arbitrary variant value to string probably is impossible)
    template<>
    struct formatter<rttr::variant>
	{
		template<typename ParseContext>
		constexpr auto parse(ParseContext& ctx)
		{
			return ctx.begin();
		}

		template<typename FormatContext>
		auto format(const rttr::variant& p, FormatContext& ctx) const
		{
			return format_to(ctx.out(), "<RTTR variant of type '{}'>", p.get_type());
		}
	};

    // for std::vector
	template<typename T, typename... Extra>
	struct formatter<std::vector<T, Extra...>>
	{
		template<typename ParseContext>
		constexpr auto parse(ParseContext& ctx)
		{
			return ctx.begin();
		}

		template<typename FormatContext>
		auto format(const std::vector<T, Extra...>& p, FormatContext& ctx) const
		{
            std::string s = "<std::vector> ";
            for (int i = 0; i < (int)p.size(); ++i)
            {
                std::format_to(std::back_inserter(s), "{}", p[i]);
				if (i != p.size() - 1)
				{
					s += ", ";
				}
			}
			return format_to(ctx.out(), "{}", s);
		}
	};

	// for std::array
}

#endif // __MAIN_H__