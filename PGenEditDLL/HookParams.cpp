#include "pch.h"
#include "HookParams.h"

namespace HookParams
{
    std::array<bool, 50> noRecoveryEnabled{};
    std::array<double, 50> recoveryMultiplier{ 1 };
    std::array<bool, 50> buffSpellRecoveryReduced{};
    std::array<bool, 50> buffSpellRecoveryReducedOnlyOutOfCombat{1};

    bool persist(Json& json)
    {
        try
        {
            json["noRecoveryEnabled"] = noRecoveryEnabled;
            json["recoveryMultiplier"] = recoveryMultiplier;
            json["buffSpellRecoveryReduced"] = buffSpellRecoveryReduced;
            json["buffSpellRecoveryReducedOnlyOutOfCombat"] = buffSpellRecoveryReducedOnlyOutOfCombat;
            return true;
        }
        catch (const JsonException& ex)
        {
            wxLogError("HookParams persist error: %s", ex.what());
            wxLog::FlushActive();
            return false;
        }
    }

    bool unpersist(const Json& json)
    {
        try
        {
            noRecoveryEnabled = json["noRecoveryEnabled"];
            recoveryMultiplier = json["recoveryMultiplier"];
            buffSpellRecoveryReduced = json["buffSpellRecoveryReduced"];
            buffSpellRecoveryReducedOnlyOutOfCombat = json["buffSpellRecoveryReducedOnlyOutOfCombat"];
            return true;
        }
        catch (const JsonException& ex)
        {
            wxLogError("HookParams unpersist error: %s", ex.what());
            wxLog::FlushActive();
            return false;
        }
    }
}

// INVERT JSON:
// (json\["\w+\"\]) = (\w+)
// $2 = $1