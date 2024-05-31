#pragma once
#include "main.h"

// macro definitions for easy generation of getter/setter methods for struct fields

// boost.pp for accessor methods generation needs widest types of all game fields, and return/set them
// also need to somehow make first field letter capital (so it's getGold, not getgold)
// to consider: issue a warning if assigning to or returning narrower type outside its range?
// params to pass on example of gold: gold, Gold, int64_t

// declaration will contain virtual and = 0, definition will contain override

// macro used as argument to BOOST_PP_SEQ_FOR_EACH, generates single "if constexpr" matching specific game based on passed struct type
// data is (code, templateParam)

#define PGENEDIT_TOO_MANY_ARGS_CHECK(...) \
BOOST_PP_ASSERT_MSG(BOOST_PP_EQUAL(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__), 0), "Too many arguments: " BOOST_PP_STRINGIZE(BOOST_PP_VARIADIC_SIZE(__VA_ARGS__))) \

#define PG_test(x) x

// data = (code)(templateParam), elem = game version
#define PGENEDIT_CONSTEXPR2(r, data, elem) \
if constexpr (SAME(mm##elem::BOOST_PP_SEQ_ELEM(1, data), BOOST_PP_SEQ_ELEM(1, data))) \
{ \
    BOOST_PP_SEQ_ELEM(0, data) \
}

// indirection needed to allow "data" (which is boost macro invocation) to expand before pasting
#define PGENEDIT_CONSTEXPR(r, data, elem) PGENEDIT_CONSTEXPR2(r, data, elem)

#define PGENEDIT_EXPAND(...) __VA_ARGS__


// NOTE: it's VERY IMPORTANT to iterate directly over list here, because upper in "macro call stack" I use BOOST_PP_SEQ_FOR_EACH, and apparently same macro can't be used twice in "expansion sequence"
#define PGENEDIT_GEN_CONSTEXPR2(code, games, templateParam, ...) \
	BOOST_PP_LIST_FOR_EACH(PGENEDIT_CONSTEXPR, (code)(templateParam), BOOST_PP_TUPLE_TO_LIST(games))

#define PGENEDIT_GEN_CONSTEXPR(code, games, templateParam, ...) \
    PGENEDIT_GEN_CONSTEXPR2(code, games, templateParam)

// generates inside of getter/setter function, which exists only in specific games
// "code" is code placed inside each if constexpr, games is tuple of game versions this code works in, templateParam is template parameter for class to use as if constexpr test
#define PGENEDIT_CONSTEXPR_BY_GAME(code, games, templateParam) \
    PGENEDIT_GEN_CONSTEXPR(code, games, templateParam) \
    wxLogFatalError("[%s] Invalid game version", __FUNCTION__);\
    throw std::exception("dummy"); // to make compiler allow not all paths returning value, won't be thrown anyway, because of wxLogFatalError

// test
//using Player = mm6::Player;
void f()
{
    //BOOST_PP_TUPLE_TO_LIST(BOOST_PP_SEQ_TO_TUPLE((6)(7)(8)))
    //PGENEDIT_CONSTEXPR_BY_GAME(return prefix fieldName; , (6)(7)(8), Player)
}
using Player = mm7::Player;

#define PGENEDIT_GETTER_DECL(type, fieldName, getterNamePart, templateParam) \
	[[nodiscard]] virtual type get##getterNamePart() = 0;\
	[[nodiscard]] virtual void* get##getterNamePart##Ptr () = 0;
/*
#define PGENEDIT_GETTER_DEF(prefix, type, fieldName, getterNamePart) \
	[[nodiscard]] type get##getterNamePart() override { return prefix fieldName; } \
	\
	[[nodiscard]] void* get##getterNamePart##Ptr () override { return & prefix fieldName; }*/

// returns correct getter/setter definition macro based on number of arguments (the one with less calls the one with more, passing all games)
#define PGENEDIT_GET_MACRO_GETTER_SETTER_DEF(_1, _2, _3, _4, _5, NAME, ...) NAME
#define PGENEDIT_GET_MACRO_GETTER_SETTER_DEF_6(_1, _2, _3, _4, _5, _6, NAME, ...) NAME

#define PGENEDIT_GETTER_DEF_SOME(prefix, type, fieldName, getterNamePart, templateParam, games) \
	[[nodiscard]] type get##getterNamePart() override { PGENEDIT_CONSTEXPR_BY_GAME(return prefix fieldName;, games, templateParam) } \
	\
	[[nodiscard]] void* get##getterNamePart##Ptr () override { return & prefix fieldName; }
#define PGENEDIT_GETTER_DEF_ALL(prefix, type, fieldName, getterNamePart, templateParam) PGENEDIT_GETTER_DEF_SOME(prefix, type, fieldName, getterNamePart, templateParam, (6, 7, 8))

//PGENEDIT_GETTER_DEF_SOME(, int, gold, Gold, Player, (6)(7)(8))

// prefix, type, fieldName, accessorNamePart, templateParam, games
#define PGENEDIT_GETTER_DEF(...) PGENEDIT_GET_MACRO_GETTER_SETTER_DEF_6(__VA_ARGS__, PGENEDIT_GETTER_DEF_SOME, PGENEDIT_GETTER_DEF_ALL)(__VA_ARGS__)
//using Player = mm6::Player;
class c
{
	//PGENEDIT_GETTER_DEF(pref, Player, fi, get, Player, (6))
};

//PGENEDIT_GET_MACRO_GETTER_SETTER_DEF(pr, tp, fi, gam, g, PGENEDIT_GETTER_DEF_ALL, PGENEDIT_GETTER_DEF_SOME)

// setters

#define PGENEDIT_SETTER_DECL(type, fieldName, setterNamePart, templateParam) \
	virtual void set##setterNamePart(type value) = 0;

#define PGENEDIT_SETTER_DEF_SOME(prefix, type, fieldName, setterNamePart, templateParam, games) \
	void set##setterNamePart(type value) override { PGENEDIT_CONSTEXPR_BY_GAME(prefix fieldName = value;, games, templateParam) }

#define PGENEDIT_SETTER_DEF_ALL(prefix, type, fieldName, setterNamePart, templateParam) PGENEDIT_SETTER_DEF_SOME(prefix, type, fieldName, setterNamePart, templateParam, (6, 7, 8))

// prefix, type, fieldName, accessorNamePart, templateParam, [games]
#define PGENEDIT_SETTER_DEF(...) PGENEDIT_GET_MACRO_GETTER_SETTER_DEF_6(__VA_ARGS__, PGENEDIT_SETTER_DEF_SOME, PGENEDIT_SETTER_DEF_ALL)(__VA_ARGS__)

// this macro and all "beneath it" take dummy templateParam parameter, which isn't really used in declaration, but it simplifies macro usage
#define PGENEDIT_GETTER_SETTER_DECL(type, fieldName, accessorNamePart, templateParam) \
	PGENEDIT_GETTER_DECL(type, fieldName, accessorNamePart, templateParam) \
	PGENEDIT_SETTER_DECL(type, fieldName, accessorNamePart, templateParam)

#define PGENEDIT_GETTER_SETTER_DEF_SOME(prefix, type, fieldName, accessorNamePart, templateParam, games, ...) \
	PGENEDIT_GETTER_DEF(prefix, type, fieldName, accessorNamePart, templateParam, games) \
	PGENEDIT_SETTER_DEF(prefix, type, fieldName, accessorNamePart, templateParam, games)

#define PGENEDIT_GETTER_SETTER_DEF_ALL(prefix, type, fieldName, accessorNamePart, templateParam) PGENEDIT_GETTER_SETTER_DEF_SOME(prefix, type, fieldName, accessorNamePart, templateParam, (6, 7, 8))

//PGENEDIT_SETTER_DEF_SOME(, int, gold, Gold, Player, (6)(7)(8))

/*
using Player = mm6::Player;
class G
{
    Player player;
	PGENEDIT_GETTER_SETTER_DEF_SOME( , Player, player, Player, (5)(6))
};*/

// 6 = some, 5 = all
// prefix, type, fieldName, accessorNamePart, templateParam, [tuple of games]
#define PGENEDIT_GETTER_SETTER_DEF(...) PGENEDIT_GET_MACRO_GETTER_SETTER_DEF_6(__VA_ARGS__, PGENEDIT_GETTER_SETTER_DEF_SOME, PGENEDIT_GETTER_SETTER_DEF_ALL)(__VA_ARGS__)

// args: prefix, tuple(type, field name, accessor name part, template argument, [tuple of games])
#define PGENEDIT_GETTER_SETTER_METHODS_DEF(prefix, ...) \
    /*PGENEDIT_TOO_MANY_ARGS_CHECK(__VA_ARGS__)*/ \
    BOOST_PP_ASSERT_MSG(BOOST_PP_NOT(BOOST_PP_IS_BEGIN_PARENS(prefix)), "First argument for accessor definitions should be prefix to access the field, not tuple")\
	BOOST_PP_SEQ_FOR_EACH(PGENEDIT_GETTER_SETTER_METHODS_MACRO_DEF, prefix, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__)) // makes a sequence of tuples

// data = prefix, tup = tuple(type, field name, accessor name part, template argument, [tuple of games])
#define PGENEDIT_GETTER_SETTER_METHODS_MACRO_DEF(r, data, tup, ...) \
	PGENEDIT_GETTER_SETTER_DEF(data, BOOST_PP_TUPLE_ENUM(BOOST_PP_TUPLE_SIZE(tup), tup))

#define PGENEDIT_GETTER_SETTER_METHODS_DECL(...) \
	BOOST_PP_LIST_FOR_EACH(PGENEDIT_GETTER_SETTER_METHODS_MACRO_DECL, 0, BOOST_PP_VARIADIC_TO_LIST(__VA_ARGS__))
#define PGENEDIT_GETTER_SETTER_METHODS_MACRO_DECL(r, data, tup) \ \
    BOOST_PP_ASSERT_MSG(0, BOOST_PP_TUPLE_ENUM(BOOST_PP_TUPLE_SIZE(tup), tup)) \
	PGENEDIT_GETTER_SETTER_DECL(BOOST_PP_TUPLE_ENUM(BOOST_PP_TUPLE_SIZE(tup), tup))

// arrays

#define PGENEDIT_ARRAY_GETTER_SETTER_METHODS_DEF(prefix, ...) \
	BOOST_PP_ASSERT_MSG(BOOST_PP_NOT(BOOST_PP_IS_BEGIN_PARENS(prefix)), "First argument for accessor definitions should be prefix to access the field, not tuple")\
	BOOST_PP_SEQ_FOR_EACH(PGENEDIT_ARRAY_GETTER_SETTER_METHODS_MACRO_DEF, prefix, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

class base
{
    virtual int getGold() = 0;
    virtual void* getGoldPtr() = 0;
	virtual void setGold(int value) = 0;
    virtual int getFood() = 0;
	virtual void* getFoodPtr() = 0;
	virtual void setFood(int value) = 0;
};

class x : base
{
    mm7::GameParty* getParty();
    void* p;
	PGENEDIT_GETTER_SETTER_METHODS_DEF(getParty()->, (int, gold, Gold, Player), (int, food, Food, Player, (7, 8)))
};



// arrays need special handling
// since amount of array items is not known at compile time, we need to pass it as a parameter
// to handle various sizes, we will use std::vector with assertion that its size is equal to the size of array
// PGENEDIT_ARRAY_GETTER_SETTER_DECL((std::array<int, 6>), test, Test, 6, 7, 8) // pass amount of elements for each game version

// only supports primitive types for now

#define PGENEDIT_ARRAY_GETTER_DECL(type, fieldName, accessorNamePart) \
	[[nodiscard]] virtual std::vector<type> get##accessorNamePart() = 0;\
    [[nodiscard]] virtual void* get##accessorNamePart##Ptr () = 0;\
	[[nodiscard]] virtual int get##accessorNamePart##Size() = 0;
#define PGENEDIT_ARRAY_GETTER_DEF(prefix, type, fieldName, accessorNamePart) \
	[[nodiscard]] std::vector<type> get##accessorNamePart() override { \
		std::vector<type> result; \
		result.reserve(prefix fieldName.size()); \
		std::copy(prefix fieldName.begin(), prefix fieldName.end(), std::back_inserter(result));\
		return result; \
	}\
    \
    [[nodiscard]] void* get##accessorNamePart##Ptr () override { \
		return reinterpret_cast<void*>(prefix fieldName.data()); \
	}\
    \
    [[nodiscard]] int get##accessorNamePart##Size() override { \
		return prefix fieldName.size(); \
	}
#define PGENEDIT_ARRAY_SETTER_DECL(type, fieldName, accessorNamePart) \
	virtual void set##accessorNamePart(const std::vector<type>& value) = 0;
#define PGENEDIT_ARRAY_SETTER_DEF(prefix, type, fieldName, accessorNamePart) \
	void set##accessorNamePart(const std::vector<type>& value) override { \
		wxASSERT_MSG(value.size() == prefix fieldName.size(), wxString::Format(\
            "Invalid number of array elements for %s %s (expected %d, got %d)", #type, #fieldName,\
			prefix fieldName.size(), value.size())); \
		std::copy(value.begin(), value.end(), prefix fieldName.begin()); \
	}
#define PGENEDIT_ARRAY_GETTER_SETTER_DECL(type, fieldName, accessorNamePart) \
	PGENEDIT_ARRAY_GETTER_DECL(type, fieldName, accessorNamePart) \
	PGENEDIT_ARRAY_SETTER_DECL(type, fieldName, accessorNamePart)

#define PGENEDIT_ARRAY_GETTER_SETTER_DEF(prefix, type, fieldName, accessorNamePart) \
	PGENEDIT_ARRAY_GETTER_DEF(prefix, type, fieldName, accessorNamePart) \
	PGENEDIT_ARRAY_SETTER_DEF(prefix, type, fieldName, accessorNamePart)

// prefix, type, field name, accessor name part
#define PGENEDIT_ARRAY_GETTER_SETTER_METHODS_DEF(prefix, ...) \
	BOOST_PP_ASSERT_MSG(BOOST_PP_NOT(BOOST_PP_IS_BEGIN_PARENS(prefix)), "First argument for accessor definitions should be prefix to access the field, not tuple")\
	BOOST_PP_SEQ_FOR_EACH(PGENEDIT_ARRAY_GETTER_SETTER_METHODS_MACRO_DEF, prefix, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))
#define PGENEDIT_ARRAY_GETTER_SETTER_METHODS_MACRO_DEF(r, data, seq) \
	PGENEDIT_ARRAY_GETTER_SETTER_DEF(data, BOOST_PP_TUPLE_ELEM(0, seq), BOOST_PP_TUPLE_ELEM(1, seq), BOOST_PP_TUPLE_ELEM(2, seq))

// type, field name, accessor name part
#define PGENEDIT_ARRAY_GETTER_SETTER_METHODS_DECL(...) \
	BOOST_PP_SEQ_FOR_EACH(PGENEDIT_ARRAY_GETTER_SETTER_METHODS_MACRO_DECL, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))
#define PGENEDIT_ARRAY_GETTER_SETTER_METHODS_MACRO_DECL(r, data, seq) \
	PGENEDIT_ARRAY_GETTER_SETTER_DECL(BOOST_PP_TUPLE_ELEM(0, seq), BOOST_PP_TUPLE_ELEM(1, seq), BOOST_PP_TUPLE_ELEM(2, seq))

//BOOST_PP_VARIADIC_TO_SEQ((int, gold, Gold), (int, food, Food))

// holds dynamic array data
// TODO: wrap all suitable dynamic arrays inside this class
struct ArrayData
{
private:
    std::variant<int, int*, uint32_t, uint32_t*> countVariant;
    void* myPtr;
    size_t myItemSize;
public:

    ArrayData() = delete;

    template<typename T, size_t Count>
    ArrayData(std::array<T, Count>& arr)
    {
        myPtr = arr.data();
        countVariant = (int)Count;
        myItemSize = sizeof(T);
    }

    template<typename T>
    ArrayData(T* data, int count)
    {
        myPtr = data;
        countVariant = count;
        myItemSize = sizeof(T);
    }

    template<typename T>
    ArrayData(T* data, int* count)
    {
        myPtr = data;
        countVariant = count;
        myItemSize = sizeof(T);
    }

    template<typename T>
    ArrayData(T* data, uint32_t count)
    {
        myPtr = data;
        countVariant = count;
        myItemSize = sizeof(T);
	}

    template<typename T>
    ArrayData(T* data, uint32_t* count)
    {
        myPtr = data;
        countVariant = count;
        myItemSize = sizeof(T);
	}

    inline void* ptr() const
    {
        return myPtr;
    }

    int size() const
    {
        if (const int* val = std::get_if<int>(&countVariant))
        {
            return *val;
        }
        else if (int* const * val = std::get_if<int*>(&countVariant))
        {
            return **val;
        }
        else if (const uint32_t* val = std::get_if<uint32_t>(&countVariant))
        {
            return *val;
        }
        else if (uint32_t* const* val = std::get_if<uint32_t*>(&countVariant))
        {
            return **val;
        }
        else
        {
            wxFAIL;
            return 1;
        }
    }

    size_t itemSize() const
	{
		return myItemSize;
	}

    void* nthElementPtr(int index) const
	{
        checkIndex(index);
		return static_cast<char*>(myPtr) + index * myItemSize;
	}

    inline void checkIndex(int index) const
    {
        const int size = this->size();
        wxASSERT_MSG(index >= 0 && index < size, wxString::Format("Out of bounds access with index '%d' (size is '%d')", index, size));
    }
};

namespace accessorDetail
{

    template<typename Function, typename T>
    concept CalledWithPointerOnly = requires (T * t)
    {
        (void)std::declval<Function>()(t);
    };

    template<typename Function, typename T>
    concept CalledWithPointerAndIndex = requires (T * t)
    {
        (void)std::declval<Function>()(t, (int)1);
    };

    template<typename Function, typename T>
    constexpr auto callWithOptionalIndexParam(T* ptr, int index, Function&& func)
    {
        if constexpr (CalledWithPointerOnly<Function, T>)
        {
            return func(ptr + index);
        }
        else if constexpr (CalledWithPointerAndIndex<Function, T>)
        {
            return func(ptr + index, index);
        }
        else
        {
            func(1, (char)3, true, "a"); // to cause compile-time error, static_assert always fails
        }
    }

    template<typename Function, typename T>
    concept CalledWithVectorOfPointersOnly = requires (T * t)
    {
        (void)std::declval<Function>()(std::declval<std::vector<T*>>());
    };

    template<typename Function, typename T>
    concept CalledWithVectorOfPointersAndIndexes = requires (T * t)
    {
        (void)std::declval<Function>()(std::declval<std::vector<std::pair<T*, int>>>());
    };

    // here "first" param makes sense, unlike above, because iterating over vector of indexes just to add 1 or so to each one would be probably code duplication in higher abstraction level
    template<typename Function, typename T>
    constexpr auto callWithOptionalIndexParamVector(T* ptr, int count, Function&& func, int first = 0)
    {
        if constexpr (CalledWithVectorOfPointersOnly<Function, T>)
        {
            std::vector<T*> v(count);
            for (int i = 0; i < count; ++i)
            {
                v[i] = ptr + first + i;
            }
            return func(v);
        }
        else if constexpr (CalledWithVectorOfPointersAndIndexes<Function, T>)
        {
            std::vector<std::pair<T*, int>> v(count);
            for (int i = 0; i < count; ++i)
            {
                v[i] = std::make_pair(ptr + first + i, first + i);
            }
            return func(v);
        }
        else
        {
            func(1, (char)3, true, "a"); // to cause compile-time error, static_assert always fails
        }
    }
}

// base type for all struct accessors, contains some predefined game-specific struct pointers
template<typename MainTypeActual, typename MainType6, typename MainType7, typename MainType8>
class StructAccessor
{
public:
    template<typename Type6, typename Type7, typename Type8>
    using MakeType = std::conditional_t<SAME(MainTypeActual, MainType6), Type6, std::conditional_t<SAME(MainTypeActual, MainType7), Type7, Type8>>;

    // typedef?
    using GameType = MakeType<mm6::Game, mm7::Game, mm8::Game>;
    static inline GameType* const game = reinterpret_cast<GameType*>(0);
    using MapType = MakeType<mm6::GameMap, mm7::GameMap, mm8::GameMap>;
    static inline MapType* const map = reinterpret_cast<MapType*>(0);
    using ScreenType = MakeType<mm6::GameScreen, mm7::GameScreen, mm8::GameScreen>;
    static inline ScreenType* const screen = reinterpret_cast<ScreenType*>(0);
    using PartyType = MakeType<mm6::GameParty, mm7::GameParty, mm8::GameParty>;
    static inline PartyType* const party = reinterpret_cast<PartyType*>(0);
    using MouseType = MakeType<mm6::GameMouse, mm7::GameMouse, mm8::GameMouse>;
    static inline MouseType* const mouse = reinterpret_cast<MouseType*>(0);
    using DialogLogicType = MakeType<mm6::DialogLogic, mm7::DialogLogic, mm8::DialogLogic>;
    static inline DialogLogicType* const dialogLogic = game->dialogLogic;
};

// utility class, contains generic functions for executing a function for any game version's struct over each array item,
// for single item, single index of array, execute once function receiving std::vector<T*>, or execute a function over one instance of static struct (like Game or Party)
class StructAccessorGenericFor
{
protected:
	// dispatches function based on MMVER
    // this needs to be used in cases where we want to allow function to be used from superclass and overridden in derived, and have it take parameters from derived class
    // since all "forEach" functions take callback as a parameter, they are template functions and thus cannot be virtual
    // so, this just dynamically dispatches to derived class
	template<typename Function6, typename Function7, typename Function8, typename... Args>
	static auto versionBasedStaticAccessorDispatch(Function6&& func6, Function7&& func7, Function8&& func8, Args&&... args)
	{
		if (MMVER == 6)
		{
			return func6(std::forward<Args>(args)...);
		}
		else if (MMVER == 7)
		{
			return func7(std::forward<Args>(args)...);
		}
		else if (MMVER == 8)
		{
			return func8(std::forward<Args>(args)...);
		}
		else
		{
			wxFAIL_MSG(wxString::Format("Invalid MM version (%d)", MMVER));
		}
		return decltype(func6(std::forward<Args>(args)...))(); // default-constructed return value, compiler will make sure all three returned types match
	}

    template<typename... Args, typename Class6, typename Class7, typename Class8, typename ReturnType>
    static auto versionBasedAccessorDispatch(ReturnType Class6::*func6, ReturnType Class7::* func7, ReturnType Class8::* func8, Args&&... args)
	{
		if (MMVER == 6)
		{
			return (static_cast<Class6*>(this)->*func6)(std::forward<Args>(args)...);
		}
		else if (MMVER == 7)
		{
			return (static_cast<Class7*>(this)->*func6)(std::forward<Args>(args)...);;
		}
		else if (MMVER == 8)
		{
			return (static_cast<Class8*>(this)->*func6)(std::forward<Args>(args)...);;
		}
		else
		{
			wxFAIL_MSG(wxString::Format("Invalid MM version (%d)", MMVER));
		}
		return decltype((static_cast<Class6*>(this)->*func6)(std::forward<Args>(args)...))(); // default-constructed return value, compiler will make sure all three returned types match
	}

    // executes a function for any game version's struct over each array item
    template<typename Function, typename Type6, typename Type7, typename Type8>
    static auto genericForEachDo(void* ptr, int count, Function&& func, int first = 0)
    {
        if (MMVER == 6)
        {
            return genericForEachDoSpecialized(reinterpret_cast<Type6*>(ptr), count, std::forward<Function>(func), first);
        }
        else if (MMVER == 7)
        {
            return genericForEachDoSpecialized(reinterpret_cast<Type7*>(ptr), count, std::forward<Function>(func), first);
        }
        else if (MMVER == 8)
        {
            return genericForEachDoSpecialized(reinterpret_cast<Type8*>(ptr), count, std::forward<Function>(func), first);
        }
        else
        {
            wxFAIL;
            return decltype(genericForEachDoSpecialized(reinterpret_cast<Type6*>(ptr), count, std::forward<Function>(func), first))(); // default-constructed return value
        }
    }

#define PGENEDIT_FOR_EACH_DEF(type) \
	template<typename Function> \
	static auto forEach ## type ## Do(void* ptr, int count, Function&& func, int first = 0) \
	{ \
        return genericForEachDo<Function, mm6::type, mm7::type, mm8::type>(ptr, count, std::forward<Function>(func), first); \
	}

	template<typename Function, typename T>
	static auto genericForEachDoSpecialized(T* ptr, int count, Function&& func, int first = 0)
	{
		for (int i = 0; i < count; ++i)
		{
			accessorDetail::callWithOptionalIndexParam(ptr, first + i, std::forward<Function>(func));
		}
	}

#define PGENEDIT_FOR_EACH_STATIC_ARRAY_DECL(type, accessor) \
	template<typename Function> \
	static auto forEach ## type ## ArrayIndexDo(Function&& func, int first = 0) \
	{ \
		if (MMVER == 6) \
		{ \
			return accessor<mm6::type>::template forEach ## type ## ArrayIndexDoSpecialized<Function, mm6::type>(std::forward<Function>(func), first); \
		} \
		else if (MMVER == 7) \
		{ \
			return accessor<mm7::type>::template forEach ## type ## ArrayIndexDoSpecialized<Function, mm7::type>(std::forward<Function>(func), first); \
		} \
		else if (MMVER == 8) \
		{ \
			return accessor<mm8::type>::template forEach ## type ## ArrayIndexDoSpecialized<Function, mm8::type>(std::forward<Function>(func), first); \
		} \
		else \
		{ \
			wxFAIL; \
			return decltype(accessor<mm6::type>::template forEach ## type ## ArrayIndexDoSpecialized<Function, mm6::type>(std::forward<Function>(func), first))(); /* default-constructed return value */ \
		} \
	}
// this needs to be in derived class to ease writing getArrCode and getCountCode
#define PGENEDIT_FOR_EACH_STATIC_ARRAY_DEF(type, getArrCode, getCountCode) \
	template<typename Function, typename T> \
		static auto forEach ## type ## ArrayIndexDoSpecialized(Function&& func, int first = 0) \
	{ \
        int count = getCountCode; \
		for (int i = 0; i < count; ++i) \
		{ \
			accessorDetail::callWithOptionalIndexParam<Function, T>(reinterpret_cast<T*>(getArrCode), first + i, std::forward<Function>(func)); \
		} \
	}


    // executes once a function receiving std::vector of pointers to structure entries
    template<typename Function, typename Type6, typename Type7, typename Type8>
    static auto genericForRangeDo(void* ptr, int count, Function&& func, int first = 0)
    {
        if (MMVER == 6)
        {
            return accessorDetail::callWithOptionalIndexParamVector(reinterpret_cast<Type6*>(ptr), count, std::forward<Function>(func), first);
        }
        else if (MMVER == 7)
        {
            return accessorDetail::callWithOptionalIndexParamVector(reinterpret_cast<Type7*>(ptr), count, std::forward<Function>(func), first);
        }
        else if (MMVER == 8)
        {
            return accessorDetail::callWithOptionalIndexParamVector(reinterpret_cast<Type8*>(ptr), count, std::forward<Function>(func), first);
        }
        else
        {
            wxFAIL;
            return decltype(accessorDetail::callWithOptionalIndexParamVector(reinterpret_cast<Type6*>(ptr), count, std::forward<Function>(func), first))(); // default-constructed return value
        }
    }
    // define macros similar to above, but for std::vector of pointers
#define PGENEDIT_FOR_RANGE_DEF(type) \
	template<typename Function> \
	static auto for ## type ## RangeDo(void* ptr, int count, Function&& func, int first = 0) \
	{ \
		return genericForRangeDo<Function, mm6::type, mm7::type, mm8::type>(ptr, count, std::forward<Function>(func), first); \
	}

    template<typename Function, typename... Args>
    static auto gameVersionFunctionDispatch(Function&& func, Args&&... args)
    {
        if (MMVER == 6)
        {
            return func(std::forward<Args>(args)...);
        }
        else if (MMVER == 7)
        {
            return func(std::forward<Args>(args)...);
        }
        else if (MMVER == 8)
        {
            return func(std::forward<Args>(args)...);
        }
        else
        {
            wxFAIL;
            return decltype(func(std::forward<Args>(args)...))(); // default-constructed return value
        }
    }

    // executes a function for single struct entry
    template<typename Function, typename Type6, typename Type7, typename Type8>
    static auto genericForItemExecute(void* ptr, Function&& func)
    {
        if (MMVER == 6)
        {
            return func(reinterpret_cast<Type6*>(ptr));
        }
        else if (MMVER == 7)
        {
            return func(reinterpret_cast<Type7*>(ptr));
        }
        else if (MMVER == 8)
        {
            return func(reinterpret_cast<Type8*>(ptr));
        }
        else
        {
            wxFAIL;
            return decltype(func(reinterpret_cast<Type6*>(ptr)))(); // default-constructed return value
        }
    }

#define PGENEDIT_FOR_ITEM_EXECUTE_DEF(type) \
	template<typename Function> \
	static auto for ## type ## Execute(void* ptr, Function&& func) \
	{ \
		return genericForItemExecute<Function, mm6::type, mm7::type, mm8::type>(ptr, std::forward<Function>(func)); \
	}

    // executes a function for single index of array
    // to be used for example with items.txt - where there is one array only, so if you need item id 5 data, you don't need to provide pointer outside of accessor internals
    template<typename Function, typename Type6, typename Type7, typename Type8>
    static auto genericForSingleArrayIndexExecute(void* ptr, int index, Function&& func, int first = 0)
    {
        if (MMVER == 6)
        {
            return accessorDetail::callWithOptionalIndexParam(reinterpret_cast<Type6*>(ptr), index + first, std::forward<Function>(func));
        }
        else if (MMVER == 7)
        {
            return accessorDetail::callWithOptionalIndexParam(reinterpret_cast<Type7*>(ptr), index + first, std::forward<Function>(func));
        }
        else if (MMVER == 8)
        {
            return accessorDetail::callWithOptionalIndexParam(reinterpret_cast<Type8*>(ptr), index + first, std::forward<Function>(func));
        }
        else
        {
            wxFAIL;
            return decltype(accessorDetail::callWithOptionalIndexParam(reinterpret_cast<Type6*>(ptr), index + first, std::forward<Function>(func)))(); // default-constructed return value
        }
    }

#define PGENEDIT_FOR_SINGLE_ARRAY_INDEX_EXECUTE_DEF(type) \
	template<typename Function> \
	static auto for ## type ## ArrayIndexExecute(void* ptr, int index, Function&& func, int first = 0) \
	{ \
		return genericForSingleArrayIndexExecute<Function, mm6::type, mm7::type, mm8::type>(ptr, index, std::forward<Function>(func), first); \
	}

    // executes for single-instance struct at static address, like Game or Party
    template<typename Function, typename Type6, typename Type7, typename Type8>
    static auto genericForSingleStructExecute(void* ptr, Function&& func)
    {
        if (MMVER == 6)
        {
            return func(reinterpret_cast<Type6*>(ptr));
        }
        else if (MMVER == 7)
        {
            return func(reinterpret_cast<Type7*>(ptr));
        }
        else if (MMVER == 8)
        {
            return func(reinterpret_cast<Type8*>(ptr));
        }
        else
        {
            wxFAIL;
            return decltype(func(reinterpret_cast<Type6*>(ptr)))(); // default-constructed return value
        }
    }

    // executes a function for specific indexes of array
    template<typename Function, typename Type6, typename Type7, typename Type8>
    static auto genericForSpecificArrayIndexesExecute(void* ptr, Function&& func, const std::vector<int>& baseIndexes, bool sort = false, int first = 0)
    {
        if (MMVER == 6)
        {
            return genericForSpecificArrayIndexesExecuteSpecialized(reinterpret_cast<Type6*>(ptr), std::forward<Function>(func), baseIndexes, sort, first);
        }
        else if (MMVER == 7)
        {
            return genericForSpecificArrayIndexesExecuteSpecialized(reinterpret_cast<Type7*>(ptr), std::forward<Function>(func), baseIndexes, sort, first);
        }
        else if (MMVER == 8)
        {
            return genericForSpecificArrayIndexesExecuteSpecialized(reinterpret_cast<Type8*>(ptr), std::forward<Function>(func), baseIndexes, sort, first);
        }
        else
        {
            wxFAIL;
            return decltype(genericForSpecificArrayIndexesExecuteSpecialized(reinterpret_cast<Type6*>(ptr),
                std::forward<Function>(func), baseIndexes, sort, first))(); // default-constructed return value
        }
    }

    // executes a function for specific indexes of array
    template<typename Function, typename T>
    static auto genericForSpecificArrayIndexesExecuteSpecialized(T* ptr, Function&& func, const std::vector<int>& baseIndexes, bool sort = false, int first = 0)
    {
        auto actualIndexes = baseIndexes;
        if (sort)
        {
            std::ranges::sort(actualIndexes);
        }
        for (int index : actualIndexes)
        {
            assert(index >= 0);
            accessorDetail::callWithOptionalIndexParam(ptr, index + first, std::forward<Function>(func));
        }
    }
    // macro which dispatches on MMVER and chooses appropriate structure type, then calls genericForSpecificArrayIndexesExecuteSpecialized
#define PGENEDIT_FOR_SPECIFIC_ARRAY_INDEXES_EXECUTE_DEF(type) \
	template<typename Function> \
	static auto for ## type ## ArrayIndexesExecute(void* ptr, Function&& func, const std::vector<int>& baseIndexes, bool sort = false, int first = 0) \
	{ \
		return genericForSpecificArrayIndexesExecute<Function, mm6::type, mm7::type, mm8::type>(ptr, std::forward<Function>(func), baseIndexes, sort, first); \
    }
};

#define PGENEDIT_GENERIC_METHODS_DECL(type) \
    PGENEDIT_FOR_EACH_STATIC_ARRAY_DECL(type) \

// excludes static array method
#define PGENEDIT_GENERIC_METHODS_DEF(type) \
    PGENEDIT_FOR_ITEM_EXECUTE_DEF(type) \
    PGENEDIT_FOR_EACH_DEF(type) \
	PGENEDIT_FOR_SINGLE_ARRAY_INDEX_EXECUTE_DEF(type) \
	PGENEDIT_FOR_SPECIFIC_ARRAY_INDEXES_EXECUTE_DEF(type) \
	PGENEDIT_FOR_RANGE_DEF(type) \
