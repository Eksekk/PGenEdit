#pragma once
#include "pch.h"
#include "main.h"

template<typename MainTypeActual, typename MainType6, typename MainType7, typename MainType8>
class StructAccessor
{
    template<typename Type6, typename Type7, typename Type8>
    using MakeType = std::conditional_t<SAME(MainTypeActual, MainType6), Type6, std::conditional_t<SAME(MainTypeActual, MainType7), Type7, Type8>>;
public:
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

