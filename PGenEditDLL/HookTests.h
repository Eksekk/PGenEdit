#pragma once
#include "pch.h"
#include "main.h"
#include "Utility.h"
#include "Asserter.h"

class HookTests
{
public:
    template<typename Player, typename Game>
    static std::vector<wxString> run();

    template<typename Player, typename Game>
    static std::vector<wxString> testHookPlacingAndSize();

    template<typename Player, typename Game>
    static std::vector<wxString> testBasicHookFunctionalityAndHookManager();

    template<typename Player, typename Game>
    static std::vector<wxString> testAdvancedHookFunctionality();

    template<typename Player, typename Game>
    static std::vector<wxString> testMiscFunctions(); // findCode, getInstructionSize, 
};