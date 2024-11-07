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
    static std::vector<wxString> run();

    static std::vector<wxString> testHookPlacingAndSize();

    static std::vector<wxString> testBasicHookFunctionalityAndHookManager();

    static std::vector<wxString> testAdvancedHookFunctionality();

    static std::vector<wxString> testAsmHookFunctions();

    static std::vector<wxString> testMiscFunctions(); // findCode, getInstructionSize, 
};