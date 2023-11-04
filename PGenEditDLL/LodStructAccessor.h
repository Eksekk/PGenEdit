#pragma once
#include "pch.h"
#include "main.h"

template<typename Lod>
class TemplatedLodStructAccessor;
class LodStructAccessor;
extern LodStructAccessor* lodAccessor;

enum BitmapsLodType
{
    BITMAPS_LOD_BITMAPS,
    BITMAPS_LOD_ICONS
};

class LodStructAccessor
{
public:
    //virtual void forEachIconsLodBitmapDo(void* ptr, int n, std::function<void(AnyLodBitmapVariant var)> func) = 0;

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
    static void forEachLodBitmapDo(Function func, BitmapsLodType type)
    {
        if (MMVER == 6)
        {
            TemplatedLodStructAccessor<mm6::Lod>::forEachLodBitmapDo(func, type);
        }
        else if (MMVER == 7)
        {
            TemplatedLodStructAccessor<mm7::Lod>::forEachLodBitmapDo(func, type);
        }
        else if (MMVER == 8)
        {
            TemplatedLodStructAccessor<mm8::Lod>::forEachLodBitmapDo(func, type);
        }
    }

    virtual ~LodStructAccessor();
};

template<typename Lod>
class TemplatedLodStructAccessor : public LodStructAccessor
{
public:
    // Inherited via LodStructAccessor
    /*virtual void forEachIconsLodBitmapDo(void* ptr, int n, std::function<void(AnyLodBitmapVariant var)> func) override
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
    static void forEachLodBitmapDo(Function func, BitmapsLodType type)
    {
        BitmapsLod* lod = nullptr;
        if (type == BITMAPS_LOD_BITMAPS)
        {
            lod = (BitmapsLod*)&game->bitmapsLod;
        }
        else if (type == BITMAPS_LOD_ICONS)
        {
            lod = (BitmapsLod*)&game->iconsLod;
        }
        else
        {
            assert(false);
        }
        LodBitmap* bmp = reinterpret_cast<LodBitmap*>(lod->bitmaps.data());
        for (size_t i = 0; i < lod->bitmaps_size; ++i)
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
            if constexpr (SAME_DECL(lodPtr, mm6::Lod*))
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

INSTANTIATE_ACCESSOR_TEMPLATES_MM_GAMES(LodStructAccessor, Lod);