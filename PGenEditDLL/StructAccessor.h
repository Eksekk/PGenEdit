#pragma once
#include "pch.h"
#include "main.h"

struct ArrayData // TODO: wrap all suitable dynamic arrays inside this class
{
private:
    std::variant<int, int*, uint32_t*> countVariant;
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
        else if (uint32_t* const* val = std::get_if<uint32_t*>(&countVariant))
        {
            return **val;
        }
    }

    inline void checkIndex(int index) const
    {
        const int size = this->size();
        wxASSERT_MSG(index >= 0 && index < size, wxString::Format("Out of bounds access with index '%d' (size is '%d')", index, size));
    }
};

template<typename MainTypeActual, typename MainType6, typename MainType7, typename MainType8>
class StructAccessor
{
protected:
    template<typename Type6, typename Type7, typename Type8>
    using MakeType = std::conditional_t<SAME(MainTypeActual, MainType6), Type6, std::conditional_t<SAME(MainTypeActual, MainType7), Type7, Type8>>;
public:
    // typedef?
    using GameType = std::conditional_t<SAME(MainTypeActual, MainType6), mm6::GameStructure, std::conditional_t<SAME(MainTypeActual, MainType7), mm7::GameStructure, mm8::GameStructure>>;
    static inline GameType* const game = reinterpret_cast<GameType*>(0);
    using MapType = std::conditional_t<SAME(MainTypeActual, MainType6), mm6::GameMap, std::conditional_t<SAME(MainTypeActual, MainType7), mm7::GameMap, mm8::GameMap>>;
    static inline MapType* const map = reinterpret_cast<MapType*>(0);
    using ScreenType = std::conditional_t<SAME(MainTypeActual, MainType6), mm6::GameScreen, std::conditional_t<SAME(MainTypeActual, MainType7), mm7::GameScreen, mm8::GameScreen>>;
    static inline ScreenType* const screen = reinterpret_cast<ScreenType*>(0);
    using PartyType = MakeType<mm6::GameParty, mm7::GameParty, mm8::GameParty>;
    static inline PartyType* const party = reinterpret_cast<PartyType*>(0);
    using MouseType = MakeType<mm6::GameMouse, mm7::GameMouse, mm8::GameMouse>;
    static inline MouseType* const mouse = reinterpret_cast<MouseType*>(0);
};

class StructAccessorGenericFor
{
public:
    template<typename Function, typename Type6, typename Type7, typename Type8, template<typename> typename Subclass>
    static auto genericForEachDo(void* ptr, int n, Function&& func)
    {
        if (MMVER == 6)
        {
            Subclass<Type6>::genericForEachDoSpecialized(reinterpret_cast<Type6*>(ptr), n, std::forward<Function>(func));
        }
        else if (MMVER == 7)
        {
            Subclass<Type7>::genericForEachDoSpecialized(reinterpret_cast<Type7*>(ptr), n, std::forward<Function>(func));
        }
        else if (MMVER == 8)
        {
            Subclass<Type8>::genericForEachDoSpecialized(reinterpret_cast<Type8*>(ptr), n, std::forward<Function>(func));
        }
        else
        {
            wxFAIL;
        }
    }

    template<typename Function, typename T>
    static auto genericForEachDoSpecialized(T* ptr, int n, Function&& func)
    {
        for (int i = 0; i < n; ++i)
        {
            func(ptr + i);
        }
    }

    template<typename Function, typename Type6, typename Type7, typename Type8, template<typename> typename Subclass>
    static auto genericForItemExecute(void* ptr, Function&& func)
    {
        if (MMVER == 6)
        {
            return Subclass<Type6>::genericForItemExecuteSpecialized(reinterpret_cast<Type6*>(ptr), std::forward<Function>(func));
        }
        else if (MMVER == 7)
        {
            return Subclass<Type7>::genericForItemExecuteSpecialized(reinterpret_cast<Type7*>(ptr), std::forward<Function>(func));
        }
        else if (MMVER == 8)
        {
            return Subclass<Type8>::genericForItemExecuteSpecialized(reinterpret_cast<Type8*>(ptr), std::forward<Function>(func));
        }
        else
        {
            wxFAIL;
        }
        return false;
    }

    template<typename Function, typename T>
    static auto genericForItemExecuteSpecialized(T* ptr, Function&& func)
    {
        return func(ptr);
    }

    // to be used for example with items.txt - where there is one array only, so if you need item id 5 data, you don't need to calculate pointer
    template<typename Function, typename Type6, typename Type7, typename Type8, template<typename> typename Subclass>
    static auto genericForSingleArrayIndexExecute(void* ptr, int index, Function&& func)
    {
        if (MMVER == 6)
        {
            return Subclass<Type6>::genericForItemExecuteSpecialized(reinterpret_cast<Type6*>(ptr) + index, std::forward<Function>(func));
        }
        else if (MMVER == 7)
        {
            return Subclass<Type7>::genericForItemExecuteSpecialized(reinterpret_cast<Type7*>(ptr) + index, std::forward<Function>(func));
        }
        else if (MMVER == 8)
        {
            return Subclass<Type8>::genericForItemExecuteSpecialized(reinterpret_cast<Type8*>(ptr) + index, std::forward<Function>(func));
        }
        else
        {
            wxFAIL;
        }
        return false;
    }
};