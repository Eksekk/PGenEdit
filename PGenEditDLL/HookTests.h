#pragma once
#include "main.h"
#include "Utility.h"
#include "Asserter.h"

namespace util::lowLevel
{
	std::vector<uint8_t> memcpyVector(void* src, uint32_t size);
}

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

    static std::vector<wxString> testAsmHookFunctions();

    template<typename Player, typename Game>
    static std::vector<wxString> testMiscFunctions(); // findCode, getInstructionSize, 
};