#pragma once
#include "pch.h"
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
};

// utility class, contains generic functions for executing a function for any game version's struct over each array item,
// for single item, single index of array, execute once function receiving std::vector<T*>, or execute a function over one instance of static struct (like Game or Party)
class StructAccessorGenericFor
{
public:
    // executes a function for any game version's struct over each array item
    template<typename Function, typename Type6, typename Type7, typename Type8>
    static auto genericForEachDo(void* ptr, int limit, Function&& func, int first = 0)
    {
        if (MMVER == 6)
        {
            return genericForEachDoSpecialized(reinterpret_cast<Type6*>(ptr), limit, std::forward<Function>(func), first);
        }
        else if (MMVER == 7)
        {
            return genericForEachDoSpecialized(reinterpret_cast<Type7*>(ptr), limit, std::forward<Function>(func), first);
        }
        else if (MMVER == 8)
        {
            return genericForEachDoSpecialized(reinterpret_cast<Type8*>(ptr), limit, std::forward<Function>(func), first);
        }
        else
        {
            wxFAIL;
            return decltype(func(reinterpret_cast<Type6*>(ptr)))(); // default-constructed return value
        }
    }

    // executes once a function receiving std::vector of pointers to structure entries
    template<typename Function, typename Type6, typename Type7, typename Type8>
    static auto genericForRangeDo(void* ptr, int limit, Function&& func, int first = 0)
    {
        if (MMVER == 6)
        {
            return genericForRangeDoSpecialized(reinterpret_cast<Type6*>(ptr), limit, std::forward<Function>(func), first);
        }
        else if (MMVER == 7)
        {
            return genericForRangeDoSpecialized(reinterpret_cast<Type7*>(ptr), limit, std::forward<Function>(func), first);
        }
        else if (MMVER == 8)
        {
            return genericForRangeDoSpecialized(reinterpret_cast<Type8*>(ptr), limit, std::forward<Function>(func), first);
        }
        else
        {
            wxFAIL;
            return decltype(genericForRangeDoSpecialized(reinterpret_cast<Type6*>(ptr), limit, std::forward<Function>(func), first))(); // default-constructed return value
        }
    }

    template<typename Function, typename T>
    static auto genericForEachDoSpecialized(T* ptr, int limit, Function&& func, int first = 0)
    {
        for (int i = first; i < limit; ++i)
        {
            func(ptr + i);
        }
    }

    template<typename Function, typename T>
    static auto genericForRangeDoSpecialized(T* ptr, int limit, Function&& func, int first = 0)
    {
        std::vector<T*> ptrs(limit - first);
        for (int i = first, j = 0; i < limit; ++i, ++j)
        {
            ptrs[j] = ptr + i;
        }
        return func(ptrs);
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
    // to be used for example with items.txt - where there is one array only, so if you need item id 5 data, you don't need to calculate pointer
    template<typename Function, typename Type6, typename Type7, typename Type8>
    static auto genericForSingleArrayIndexExecute(void* ptr, int index, Function&& func)
    {
        if (MMVER == 6)
        {
            return func(reinterpret_cast<Type6*>(ptr) + index);
        }
        else if (MMVER == 7)
        {
            return func(reinterpret_cast<Type7*>(ptr) + index);
        }
        else if (MMVER == 8)
        {
            return func(reinterpret_cast<Type8*>(ptr) + index);
        }
        else
        {
            wxFAIL;
            return decltype(func(reinterpret_cast<Type6*>(ptr)))(); // default-constructed return value
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