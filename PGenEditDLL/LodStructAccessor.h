#pragma once
#include "pch.h"
#include "main.h"

template<typename Lod>
class TemplatedLodStructAccessor;

class LodStructAccessor
{
public:
    //virtual void forEachLodBitmapDo(void* ptr, int n, std::function<void(AnyLodBitmapVariant var)> func) = 0;

    template<typename Function>
    static void forEachLodDo(void* ptr, int n, Function func)
    {
        if (MMVER == 6)
        {
            TemplatedLodStructAccessor<mm6::Lod>::forEachLodDo(ptr, n, func);
        }
        else if (MMVER == 7)
        {
            TemplatedLodStructAccessor<mm7::Lod>::forEachLodDo(ptr, n, func);
        }
        else if (MMVER == 8)
        {
            TemplatedLodStructAccessor<mm8::Lod>::forEachLodDo(ptr, n, func);
        }
    }

    template<typename Function>
    static void forEachLodBitmapDo(Function func)
    {
        if (MMVER == 6)
        {
            TemplatedLodStructAccessor<mm6::Lod>::forEachLodBitmapDo(func);
        }
        else if (MMVER == 7)
        {
            TemplatedLodStructAccessor<mm7::Lod>::forEachLodBitmapDo(func);
        }
        else if (MMVER == 8)
        {
            TemplatedLodStructAccessor<mm8::Lod>::forEachLodBitmapDo(func);
        }
    }
};

template<typename Lod>
class TemplatedLodStructAccessor : LodStructAccessor
{
public:
    // Inherited via LodStructAccessor
    /*virtual void forEachLodBitmapDo(void* ptr, int n, std::function<void(AnyLodBitmapVariant var)> func) override
    {
        mm6::LodBitmap* lodBmps = reinterpret_cast<mm6::LodBitmap*>(ptr);

        for (int i = 0; i < n; ++i)
        {
            func(lodBmps + i);
        }
    }*/

    template<typename Function>
    static void forEachLodDo(void* ptr, int n, Function func)
    {
        Lod* lod = reinterpret_cast<Lod*>(ptr);

        for (int i = 0; i < n; ++i)
        {
            func(lod + i);
        }
    }

    using LodBitmap = std::conditional_t<SAME(Lod, mm6::Lod), mm6::LodBitmap, std::conditional_t<SAME(Lod, mm7::Lod), mm7::LodBitmap, mm8::LodBitmap>>;
    using BitmapsLod = std::conditional_t<SAME(Lod, mm6::Lod), mm6::BitmapsLod, std::conditional_t<SAME(Lod, mm7::Lod), mm7::BitmapsLod, mm8::BitmapsLod>>;
    using GameType = std::conditional_t<SAME(Lod, mm6::Lod), mm6::GameStructure, std::conditional_t<SAME(Lod, mm7::Lod), mm7::GameStructure, mm8::GameStructure>>;
    static inline GameType* const game = reinterpret_cast<GameType*>(0);
    using IconsLod = BitmapsLod;

    template<typename Function>
    static void forEachLodBitmapDo(Function func)
    {
        IconsLod* lod = (IconsLod*)&game->iconsLod;
        LodBitmap* bmp = reinterpret_cast<LodBitmap*>(lod->bitmaps);
        for (int i = 0; i < lod->bitmaps_size; ++i)
        {
            func(bmp + i);
        }
    }
};

INSTANTIATE_CLASS_TEMPLATES_MM_GAMES(TemplatedLodStructAccessor, Lod);

inline int test()
{
    LodStructAccessor::forEachLodDo((void*)0xFEFEFEFE, 2, [](auto lodPtr)
        {
            if constexpr (SAMEDECL(lodPtr, mm6::Lod*))
            {
                wxMessageBox("MM6");
                int x = lodPtr->chapterHandle;
            }
            else
            {
                int y = lodPtr->archivesCount;
            }
        });
    return 0;
}

//const int x = test();