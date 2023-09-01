#pragma once
#include "pch.h"
#include "main.h"

namespace HookParams
{
    extern std::array<bool, 50> noRecoveryEnabled;
    extern std::array<double, 50> recoveryMultiplier;
    extern std::array<bool, 50> buffSpellRecoveryReduced;
    extern std::array<bool, 50> buffSpellRecoveryReducedOnlyOutOfCombat;

    bool persist(Json& json);
    bool unpersist(const Json& json);
}