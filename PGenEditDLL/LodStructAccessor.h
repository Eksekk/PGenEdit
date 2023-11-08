#pragma once
#include "main.h"
#include "Utility.h"
#include <LowLevel.h>
#include "StructAccessor.h"

template<typename Lod>
class TemplatedLodStructAccessor;
class LodStructAccessor;
extern LodStructAccessor* lodAccessor;

enum BitmapsLodType
{
    BITMAPS_LOD_BITMAPS,
    BITMAPS_LOD_ICONS
};

class LodStructAccessor : public StructAccessorGenericFor
{
public:
    //virtual void forEachIconsLodBitmapDo(void* ptr, int n, std::function<void(AnyLodBitmapVariant var)> func) = 0;

    template<typename Function>
    static void forEachLodDo(void* ptr, int n, Function&& func)
    {
        StructAccessorGenericFor::genericForEachDo<Function, mm6::Lod, mm7::Lod, mm8::Lod>(ptr, n, std::forward<Function>(func));
    }

    template<typename Function>
    static void forEachLodBitmapDo(Function func, BitmapsLodType type)
    {
        StructAccessorGenericFor::versionBasedAccessorDispatch(
            // just "TemplatedLodStructAccessor<mm6::Lod>::forEachLodBitmapDo" doesn't work
            // I now know why - it's template function, so just function name doesn't exist
            TemplatedLodStructAccessor<mm6::Lod>::template forEachLodBitmapDo<Function>,
            TemplatedLodStructAccessor<mm7::Lod>::template forEachLodBitmapDo<Function>,
            TemplatedLodStructAccessor<mm8::Lod>::template forEachLodBitmapDo<Function>,
            func, type);
    }
    
    template<typename Function>
    static auto forLodBitmapRangeDo(Function func, BitmapsLodType type)
    {
        StructAccessorGenericFor::versionBasedAccessorDispatch(
            TemplatedLodStructAccessor<mm6::Lod>::template forLodBitmapRangeDo<Function>,
            TemplatedLodStructAccessor<mm7::Lod>::template forLodBitmapRangeDo<Function>,
            TemplatedLodStructAccessor<mm8::Lod>::template forLodBitmapRangeDo<Function>,
            func, type);
    }
    
    template<typename Function>
    static auto forLodBitmapIndexesDo(Function func, BitmapsLodType type, const std::vector<int>& indexes, bool sort = false)
    {
        StructAccessorGenericFor::versionBasedAccessorDispatch(
            TemplatedLodStructAccessor<mm6::Lod>::template forLodBitmapIndexesDo<Function>,
            TemplatedLodStructAccessor<mm7::Lod>::template forLodBitmapIndexesDo<Function>,
            TemplatedLodStructAccessor<mm8::Lod>::template forLodBitmapIndexesDo<Function>,
            func, type, indexes, sort);
    }
    
    virtual int loadBitmap(const char* name, BitmapsLodType type) = 0;
    virtual void destroyBitmap(void* ptr) = 0;
    virtual void cleanupBitmaps(BitmapsLodType type) = 0;

    virtual ~LodStructAccessor();
};

namespace
{
    template<typename Lod>
    using StructAccessorAlias = StructAccessor<Lod, mm6::Lod, mm7::Lod, mm8::Lod>;
}

template<typename Lod>
class TemplatedLodStructAccessor : public LodStructAccessor, public StructAccessorAlias<Lod>
{
public:
    using LodBitmap = typename StructAccessorAlias<Lod>::template MakeType<mm6::LodBitmap, mm7::LodBitmap, mm8::LodBitmap>;
    using BitmapsLod = typename StructAccessorAlias<Lod>::template MakeType<mm6::BitmapsLod, mm7::BitmapsLod, mm8::BitmapsLod>;
    using StructAccessorAlias<Lod>::game;
    using IconsLod = BitmapsLod;
private:
    static BitmapsLod* getBitmaps(BitmapsLodType type)
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
        return lod;
    }
public:
    template<typename Function>
    static void forEachLodBitmapDo(Function func, BitmapsLodType type)
    {
        BitmapsLod* lod = getBitmaps(type);
        LodBitmap* bmp = reinterpret_cast<LodBitmap*>(lod->bitmaps.data());
        for (size_t i = 0; i < lod->bitmaps_size; ++i)
        {
            func(bmp + i);
        }
    }

    template<typename Function>
    static auto forLodBitmapRangeDo(Function func, BitmapsLodType type)
    {
        BitmapsLod* lod = getBitmaps(type);
        LodBitmap* bmp = reinterpret_cast<LodBitmap*>(lod->bitmaps.data());
        StructAccessorGenericFor::genericForRangeDoSpecialized(bmp, lod->bitmaps_size, func);
    }

    template<typename Function>
    static auto forLodBitmapIndexesDo(Function func, BitmapsLodType type, const std::vector<int>& indexes, bool sort = false)
    {
        BitmapsLod* lod = getBitmaps(type);
        LodBitmap* bmp = reinterpret_cast<LodBitmap*>(lod->bitmaps.data());
        StructAccessorGenericFor::genericForSpecificArrayIndexesExecuteSpecialized(bmp, func, indexes, sort, 0);
    }

    virtual int loadBitmap(const char* name, BitmapsLodType type) override
    {
        // TODO: argument count may be wrong in mm6
        void* p = type == BITMAPS_LOD_BITMAPS ? &game->bitmapsLod : &game->iconsLod;
        int typ = type == BITMAPS_LOD_BITMAPS ? 0 : 2;

        int ret = -1;
        if (MMVER == 6)
        {
            wxFAIL;
        }
        else if (MMVER == 7)
        {
            ret = callMemoryAddress<int>(mmv(0x40B430, 0x40FB2C, 0x410D70), 1,
                p,
                name,
                typ);
        }
        else if (MMVER == 8)
        {
            ret = callMemoryAddress<int>(mmv(0x40B430, 0x40FB2C, 0x410D70), 1,
                p,
                name,
                typ,
                0, 0);
        }
        return ret;
    }

    virtual void destroyBitmap(void* ptr) override
    {
        callMemoryAddress(mmv(0x40A0C0, 0x40F788, 0x410A10), 1, ptr);
    }

    virtual void cleanupBitmaps(BitmapsLodType type)
    {
        void* p = type == BITMAPS_LOD_BITMAPS ? &game->bitmapsLod : &game->iconsLod;
        callMemoryAddress(mmv(0x40B2F0, 0x40F9D1, 0x410C09), 1, p);
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