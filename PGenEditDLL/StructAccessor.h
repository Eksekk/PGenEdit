#pragma once
#include "main.h"

// holds dynamic array data
// TODO: wrap all suitable dynamic arrays inside this class
struct ArrayData
{
private:
    std::variant<int, int*, uint32_t, uint32_t*> countVariant;
    void* myPtr;
public:

    ArrayData() = delete;

    template<typename T, size_t Count>
    ArrayData(std::array<T, Count>& arr)
    {
        myPtr = arr.data();
        countVariant = (int)Count;
    }

    template<typename T>
    ArrayData(T* data, int count)
    {
        myPtr = data;
        countVariant = count;
    }

    template<typename T>
    ArrayData(T* data, int* count)
    {
        myPtr = data;
        countVariant = count;
    }

    template<typename T>
    ArrayData(T* data, uint32_t count)
    {
        myPtr = data;
        countVariant = count;
    }

    template<typename T>
    ArrayData(T* data, uint32_t* count)
    {
        myPtr = data;
        countVariant = count;
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

    template<typename Function, typename T>
    static auto genericForEachDoSpecialized(T* ptr, int count, Function&& func, int first = 0)
    {
        for (int i = 0; i < count; ++i)
        {
            accessorDetail::callWithOptionalIndexParam(ptr, first + i, std::forward<Function>(func));
        }
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

    template<typename Function6, typename Function7, typename Function8, typename... Args>
    static auto versionBasedAccessorDispatch(Function6&& func6, Function7&& func7, Function8&& func8, Args&&... args)
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
};