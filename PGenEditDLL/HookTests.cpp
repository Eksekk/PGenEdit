#include "pch.h"
#include "HookTests.h"
#include "LowLevel.h"

// dst, src, size
std::vector<uint8_t> memcpyVector(void* src, uint32_t size)
{
    std::vector<uint8_t> v(size);
    memcpy(v.data(), src, size);
    return v;
}

static __declspec(naked) int hook2Bytes()
{
    _asm
    {
        mov edi, edi
        push ebx
        dec eax
        push ds
        push ds
        push ds
        add ebx, eax
        ret
    }
}

static __declspec(naked) int hook5Bytes()
{
    _asm
    {
        mov ecx, 0xDEADBEEF
        push ebx
        dec eax
        push ds
        push ds
        push ds
        add ebx, eax
        ret
    }
}

static __declspec(naked) int hook10Bytes()
{
    _asm
    {
        mov DWORD PTR[ebp - 0x3640e], 0x42f300
        push ebx
        dec eax
        push ds
        push ds
        push ds
        add ebx, eax
        ret
    }
}

// converts string to hexadecimal character notation
std::string codeToSemiReadableString(const std::string& input)
{
    std::string out;
    out.resize(input.size() * 4);
    char buf[8];
    for (unsigned char c : input)
    {
        sprintf_s(buf, 8, "%X", c);
        out += "\\x";
        out += buf;
    }
    return out;
}

std::string readCodeAsString(uint32_t addr, int size)
{
    return std::string((char*)addr, (char*)(addr + size));
}

std::string getCodeString(uint32_t addr, int size)
{
    return codeToSemiReadableString(readCodeAsString(addr, size));
}

template<typename Player, typename Game>
static std::vector<wxString> HookTests::testHookPlacingAndSize()
{
    std::vector<std::vector<uint8_t>> codeBackup;
    // test hook size: patchData, callRaw, call, jump (for detours check if opcode and function address is correct, for all check that bytes beyond 5 are NOP-ed if they are in range of hook size)
    // for each type do at least three different size instructions at the beginning
    // on the occasion, also test if disabling a hook fully restores previous instructions/data
    // also testing both manual function calls and creating complex hook would be nice, but not required
    int funcSizes[3] = { 10, 13, 18 };
    codeBackup.push_back(memcpyVector(hook2Bytes, funcSizes[0]));
    codeBackup.push_back(memcpyVector(hook5Bytes, funcSizes[1]));
    codeBackup.push_back(memcpyVector(hook10Bytes, funcSizes[2]));

    auto hookTypeToString = [](HookElementType type)
    {
        switch (type)
        {
        case HOOK_ELEM_TYPE_CALL: return "call";
        case HOOK_ELEM_TYPE_CALL_RAW: return "call raw";
        case HOOK_ELEM_TYPE_JUMP: return "jump";
        case HOOK_ELEM_TYPE_PATCH_DATA: return "patch data";
        default: return "unknown hook type";
        }
    };

    void* funcs[3] = { (void*)hook2Bytes, (void*)hook5Bytes, (void*)hook10Bytes };
    int funcStartSizes[3] = { 2, 5, 10 };
    Asserter myasserter;

    auto doTest = [&](HookElementType type)
    {
        const wxString& backupCodeFailed = "[%s] Backed up code doesn't match code stored before (hook size: %d bytes)";
        const wxString& hookTypeStr = hookTypeToString(type);
        for (int hookSizeId = 0; hookSizeId < 3; ++hookSizeId)
        {
            char patchContent[] = "aabbccddeegghhii";
            for (int funcId = 0; funcId < 3; ++funcId)
            {
                void* func = funcs[funcId];
                uint32_t addr = reinterpret_cast<uint32_t>(func);
                int funcStartSize = funcStartSizes[funcId];
                int funcSize = funcSizes[funcId];
                int hookSize;
                std::vector<uint8_t> autoCodeCopy;
                switch (type)
                {
                case HOOK_ELEM_TYPE_CALL_RAW:
                    hookSize = 5 + hookSizeId * 2;
                    hookCallRaw(addr, (void*)0xFEFEFEFE, &autoCodeCopy, hookSize);
                    break;
                case HOOK_ELEM_TYPE_CALL:
                    hookSize = 5 + hookSizeId * 2;
                    hookCall(addr, (HookFunc)reinterpret_cast<HookFuncPtr>(0xFEFEFEFE), &autoCodeCopy, hookSize);
                    break;
                case HOOK_ELEM_TYPE_JUMP:
                    hookSize = 5 + hookSizeId * 2;
                    hookJumpRaw(addr, (void*)0xFEFEFEFE, &autoCodeCopy, hookSize);
                    break;
                case HOOK_ELEM_TYPE_PATCH_DATA:
                    hookSize = 3 + hookSizeId * 2;
                    patchBytes(addr, (unsigned char*)patchContent, hookSize, &autoCodeCopy, true); // useNops == true
                    // && sdword(hook2Bytes + 1) + hook2Bytes + 1 == 0xFEFEFEFE && byte(hook2Bytes + 5) != 0x90, 
                }
                wxString basicInfoStr = wxString::Format("[%s] [hookSizeId: %d, real: %d] [funcId: %d]: ", hookTypeStr, hookSizeId, hookSize, funcId);
                int cmpFirstByte = -1;
                wxString opcodeName;
                if (type == HookElementType::HOOK_ELEM_TYPE_CALL || type == HookElementType::HOOK_ELEM_TYPE_CALL_RAW)
                {
                    cmpFirstByte = 0xE8;
                    opcodeName = "call";
                }
                else if (type == HOOK_ELEM_TYPE_JUMP)
                {
                    cmpFirstByte = 0xE9;
                    opcodeName = "jump";
                }
                if (cmpFirstByte >= 0)
                {
                    myassert(byte(addr) == cmpFirstByte, wxString::Format("%sFirst byte is not %s opcode (it's '%s')",
                        basicInfoStr, opcodeName, getCodeString(addr, 1))
                    );
                }

                if (type == HookElementType::HOOK_ELEM_TYPE_CALL_RAW || type == HOOK_ELEM_TYPE_JUMP || type == HOOK_ELEM_TYPE_CALL)
                {
                    if (type == HOOK_ELEM_TYPE_CALL)
                    {
                        myassert(hookFuncMap.contains(addr), wxString::Format("%sComplex call hook wasn't set properly - 'hooks' map doesn't contain hooked address (0x%X)",
                            basicInfoStr, addr)
                        );
                    }
                    long long targetAddr = sdword(addr + 1) + addr + 5;
                    uint32_t expected = type == HOOK_ELEM_TYPE_CALL ? reinterpret_cast<uint32_t>(myHookProc) : 0xFEFEFEFEU;
                    myassert(targetAddr == expected, wxString::Format("%sCall hook has invalid address (0x%X, expected 0x%X)",
                        basicInfoStr, (uint32_t)targetAddr, expected));
                }
                else if (type == HOOK_ELEM_TYPE_PATCH_DATA)
                {
                    myassert(readCodeAsString(addr, hookSize) == std::string(patchContent).substr(0, hookSize),
                        wxString::Format("%sData after patching is different from intended", basicInfoStr)
                    );
                }
                auto& oldCodeVec = codeBackup.at(funcId);
                uint32_t oldCode = reinterpret_cast<uint32_t>(oldCodeVec.data());
                uint32_t newCode = addr;
                // check that all required bytes are NOP-ed
                int firstNopIndex = type == HOOK_ELEM_TYPE_PATCH_DATA ? hookSize : 5;
                int realSize = getRealHookSize(oldCode, hookSize);
                myassert(realSize == autoCodeCopy.size(), wxString::Format("%sReal hook size (%d) and auto code backup size (%d) don't match", realSize, autoCodeCopy.size()));
                myassert(memcmp((void*)oldCodeVec.data(), (void*)autoCodeCopy.data(), realSize) == 0,
                    wxString::Format("%sBackup memory and backup memory done by hook functions don't match: %s\t\t%s",
                        getCodeString((uint32_t)codeBackup[funcId].data(), realSize), getCodeString((uint32_t)autoCodeCopy.data(), realSize)
                    )
                );
                for (int i = firstNopIndex; i < realSize; ++i)
                {
                    myassert(byte(newCode + i) == 0x90, wxString::Format("%sRequired byte is not NOP-ed (address 0x%X, byte index %d)", basicInfoStr, addr, i));
                }
                // restore backup code
                patchBytes(addr, codeBackup[funcId].data(), funcSize);
                if (type == HOOK_ELEM_TYPE_CALL)
                {
                    assert(hookFuncMap.contains(addr));
                    hookFuncMap.erase(addr);
                }
            }

        }
    };
    // print errors from asserter
    wxString errorStr;
    std::array<HookElementType, 4> types = { HOOK_ELEM_TYPE_CALL_RAW, HOOK_ELEM_TYPE_CALL, HOOK_ELEM_TYPE_JUMP, HOOK_ELEM_TYPE_PATCH_DATA };
    for (auto type : types)
    {
        doTest(type);
    }
    return myasserter.errors;
}

template std::vector<wxString> HookTests::testHookPlacingAndSize<mm6::Player, mm6::Game>();
template std::vector<wxString> HookTests::testHookPlacingAndSize<mm7::Player, mm7::Game>();
template std::vector<wxString> HookTests::testHookPlacingAndSize<mm8::Player, mm8::Game>();

uint32_t $eax, $edx, $esi, $ebp;
bool autohookTestPassed = false;
static __declspec(naked) int __stdcall expectRegisterValues(bool autohook)
{
    _asm
    {
        push ebx
        push esi
        push edi
        sub esp, 4
        // stack pointer needs to not be moved
        mov ebx, esp
        xor eax, eax
        mov ah, 0x32
        mov dx, 0x3849
        mov $eax, eax
        mov $edx, edx
        xor esi, esi
        or si, 0x4
        mov $esi, esi
        mov ebp, 0x90909090
        mov $ebp, ebp
        // hook that does nothing, check that stuff is not changed
        nop
        nop
        nop
        nop
        nop
        cmp ebx, esp
        jne fail

        // registers need to not be touched
        cmp eax, dword ptr[$eax]
        jne fail
        cmp edx, dword ptr[$edx]
        jne fail
        cmp esi, dword ptr[$esi]
        jne fail
        cmp ebp, dword ptr[$ebp]
        jne fail

        // second hook, changes values
        push ds // 0x1E
        push ds
        push ds
        push ds
        push ds

        ; // need ecx == 0x54874343
        cmp ecx, 0x54874343
        jne fail
        
        sub ecx, esi; // need edx == (ecx - esi)
        cmp edx, ecx
        jne fail

        add ah, 0x34; // need ax == 0xA329
        cmp ax, 0xA329 + 0x3400
        jne fail

        // need (0x43764523 % 20) <= 7
        mov eax, 0x43764523
        mov ecx, 20
        cdq
        idiv ecx
        cmp edi, 7
        jae fail

        // need (0xA0000310 ^ 0x80100010) & dword(esp) != 0
        mov eax, 0xA0000310
        xor dword ptr[esp], 0x80100010
        test eax, dword PTR [esp]
        jne fail

        // need bx >= di + 0x1111
        sub bx, 0x1111
        cmp bx, di
        jl fail

        // need di % 4 == 3

        mov ax, di
        mov di, 4
        cwd
        idiv di
        cmp dx, 3
        jne fail

        xor eax, eax
        inc eax
        jmp end

        fail:
        xor eax, eax

        end:
        add esp, 4
        pop edi
        pop esi
        pop ebx
        ret
    }
}

static __declspec(naked) bool expectComputation()
{
    _asm
    {
        nop
        nop
        nop
        nop
        nop
        push esi
        push edi
        mov eax, ecx
        add eax, edx
        mov esi, eax
        
        ret
    }
}

template<typename Player, typename Game>
static std::vector<wxString> HookTests::testHookFunctionAndHookManager()
{
    return std::vector<wxString>();
}

template std::vector<wxString> HookTests::testHookFunctionAndHookManager<mm6::Player, mm6::Game>();
template std::vector<wxString> HookTests::testHookFunctionAndHookManager<mm7::Player, mm7::Game>();
template std::vector<wxString> HookTests::testHookFunctionAndHookManager<mm8::Player, mm8::Game>();

template<typename Player, typename Game>
static std::vector<wxString> HookTests::run()
{
    return mergeVectors({ testHookPlacingAndSize<Player, Game>(), testHookFunctionAndHookManager<Player, Game>() });
}

template std::vector<wxString> HookTests::run<mm6::Player, mm6::Game>();
template std::vector<wxString> HookTests::run<mm7::Player, mm7::Game>();
template std::vector<wxString> HookTests::run<mm8::Player, mm8::Game>();