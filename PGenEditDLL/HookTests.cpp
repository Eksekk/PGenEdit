#include "pch.h"
#include "HookTests.h"
#include "LowLevel.h"

static const char NOP[] = "\x90";

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
    out.reserve(input.size() * 4);
    char buf[8];
    for (char c : input)
    {
        sprintf_s(buf, 8, "%X", (unsigned char)c);
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
    Asserter myasserter("Hook placing and size");

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
                // FIXME: add more
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
                int minSize = firstNopIndex;
                int realSize = getRealHookSize(oldCode, hookSize, minSize);
                myassert(realSize == autoCodeCopy.size(), wxString::Format("%sReal hook size (%d) and auto code backup size (%d) don't match", basicInfoStr, realSize, autoCodeCopy.size()));
                myassert(memcmp((void*)oldCodeVec.data(), (void*)autoCodeCopy.data(), realSize) == 0,
                    wxString::Format("%sBackup memory and backup memory done by hook functions don't match: %s\t\t%s",
                        basicInfoStr, getCodeString((uint32_t)codeBackup[funcId].data(), realSize), getCodeString((uint32_t)autoCodeCopy.data(), realSize)
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

static __declspec(naked) void jumpDoNothing()
{
    _asm
    {
        push 0x12345678 // to be replaced
        ret
    }
}

static __declspec(naked) void callDoNothing()
{
    _asm
    {
        ret
    }
}

// TODO: versions of above functions actually generating required data?

uint32_t $eax, $edx, $esi, $ebp;
bool autohookTestPassed = false;
int failReasonId;
// RETURNS FALSE (0) IF NO ERROR, otherwise 1-based index of check that failed
static __declspec(naked) int __stdcall expectRegisterValues()
{
    _asm
    {
        /*jmp start
        call $+5
        pop ecx
        jmp getSize
        start:*/
        mov dword ptr [failReasonId], 0
        push ebx
        push ebp
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
        mov dword ptr[failReasonId], 1
        // hook that does nothing, check that stuff is not changed
        nop
        nop
        nop
        nop
        nop
        cmp ebx, esp
        jne fail

        // registers need to not be touched
        mov dword ptr[failReasonId], 2
        cmp eax, dword ptr[$eax]
        jne fail
        mov dword ptr[failReasonId], 3
        cmp edx, dword ptr[$edx]
        jne fail
        mov dword ptr[failReasonId], 4
        cmp esi, dword ptr[$esi]
        jne fail
        mov dword ptr[failReasonId], 5
        cmp ebp, dword ptr[$ebp]
        jne fail

        // second hook, changes values
        push ds // 0x1E
        push ds
        add esp, 0x8

        mov dword ptr[failReasonId], 6
        ; // need ecx == 0x54874343
        cmp ecx, 0x54874343
        jne fail
        
        mov dword ptr[failReasonId], 7
        sub ecx, esi; // need edx == (ecx - esi)
        cmp edx, ecx
        jne fail

        mov dword ptr[failReasonId], 8
        add ah, 0x34; // need ax == 0xA329
        cmp ax, 0xA329 + 0x3400
        jne fail

        mov dword ptr[failReasonId], 9
        // need (edi % 20) < 7
        mov eax, edi
        mov ecx, 20
        cdq
        idiv ecx
        cmp edx, 7
        jae fail

        mov dword ptr[failReasonId], 10
        // need (0xA0000310 ^ 0x80100010) & dword(esp) != 0
        mov eax, 0xA0000310
        xor dword ptr[esp], 0x80100010
        test eax, dword PTR [esp]
        je fail
        
        mov dword ptr[failReasonId], 11
        // need bx >= di + 0x1111
        sub bx, 0x1111
        cmp bx, di
        jl fail

        mov dword ptr[failReasonId], 12
        // need si % 4 == 3
        mov ax, si
        mov di, 4
        cwd
        idiv di
        cmp dx, 3
        jne fail

        xor eax, eax
        jmp end

    fail:
        mov eax, dword ptr [failReasonId]

    end:
        add esp, 4
        pop edi
        pop esi
        pop ebp
        pop ebx
        ret

        /*getSize:
        call $+5
        pop eax
        sub eax, ecx
        ret*/
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
static std::vector<wxString> HookTests::testBasicHookFunctionalityAndHookManager()
{
    Asserter myasserter("Basic hook functionality");
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_int_distribution genEsi(100, 10000);
    std::vector<uint8_t> copy((uint8_t*)expectRegisterValues, (uint8_t*)expectRegisterValues + 0x140); // range end randomly chosen, no way to reliably check generated function size iirc

    auto getHookFunc = [](uint32_t stackOffset)
    {
        return [=](HookData* d) -> int
        {
            // need ecx == 0x54874343
            d->ecx = 0x54874343;

            // need edx == (ecx - esi)
            // need si % 4 == 3
            d->esi = genEsi(gen);
            int r = d->esi % 4;
            d->esi += 3 - r;
            d->edx = d->ecx - d->esi;

            // need ax == 0xA329
            d->al = 0x29;
            d->ah = 0xA3;

            // need (edi % 20) < 7
            d->edi = std::uniform_int_distribution(0x37, 0x4023)(gen);
            r = d->edi % 20;
            if (r >= 7)
            {
                d->edi += std::uniform_int_distribution(20 - r, 20 - r + 7 - 1)(gen);
            }

            // need (0xA0000310 ^ 0x80100010) & dword(esp) != 0
            unsigned int andWhat = 0x20100300;
            std::vector<int> randPositions = { 9, 10, 21, 29 };
            dword(d->esp + stackOffset) = randPositions.at(std::uniform_int_distribution(0, (int)randPositions.size() - 1)(gen));

            // need bx >= di + 0x1111
            d->bx = d->di + std::uniform_int_distribution(0x1111, 0x4444)(gen);
            return HOOK_RETURN_SUCCESS;
        };
    };

    auto myHookFunc = getHookFunc(4);
    auto myHookFuncAutohook = getHookFunc(0);

    auto doNothing = [](HookData* d) -> int {return HOOK_RETURN_SUCCESS; };

    //__debugbreak();
    uint32_t firstHookPos = findCode(expectRegisterValues, "\x90"), secondHookPos = findCode(expectRegisterValues, "\x1E"); // nop, push ds
    char patch1[] = "\x03\xC3\x2B\xC3\x90"; // add eax, ebx; sub eax, ebx; nop
    char patch2[] = "\x0F\x18\x20\x90\x90"; // nop dword ptr [eax]; nop; nop
    std::vector<HookElement> elems;
    CallableFunctionHookFunc<void> hookfunctionFunc = [=](HookData* d, CallableFunctionHookOrigFunc<void> def) -> uint32_t
    {
        myHookFunc(d);
        def();
        return d->eax;
    };
    CallableFunctionHookFunc<void> hookfunctionFuncDoNothing = [=](HookData* d, CallableFunctionHookOrigFunc<void> def) -> uint32_t
    {
        def();
        return d->eax;
    };
    auto doTest = [&](HookElementType type) {
        elems.clear();
        uint8_t firstHookByteBefore = byte(firstHookPos - 1), firstHookByteAfter = byte(firstHookPos + 5);
        uint8_t secondHookByteBefore = byte(secondHookPos - 1), secondHookByteAfter = byte(secondHookPos + 5);
        switch (type)
        {
        case HOOK_ELEM_TYPE_CALL_RAW:
            elems.push_back(HookElementBuilder().address(firstHookPos).type(HOOK_ELEM_TYPE_CALL_RAW).target((uint32_t)callDoNothing).build());
            elems.push_back(HookElementBuilder().address(secondHookPos).type(HOOK_ELEM_TYPE_ERASE_CODE).size(5).build());
            break;
        case HOOK_ELEM_TYPE_CALL:
            elems.push_back(HookElementBuilder().address(firstHookPos).type(HOOK_ELEM_TYPE_CALL).func(doNothing).build());
            elems.push_back(HookElementBuilder().address(secondHookPos).type(HOOK_ELEM_TYPE_CALL).func(myHookFunc).build());
            break;
        case HOOK_ELEM_TYPE_AUTOHOOK:
            elems.push_back(HookElementBuilder().address(firstHookPos).type(HOOK_ELEM_TYPE_AUTOHOOK).func(doNothing).build());
            elems.push_back(HookElementBuilder().address(secondHookPos).type(HOOK_ELEM_TYPE_AUTOHOOK).func(myHookFuncAutohook).build());
            //hookCall(firstHookPos, doNothing);
            //hookCall(secondHookPos, myHookFunc);
            break;
        case HOOK_ELEM_TYPE_JUMP:
            elems.push_back(HookElementBuilder().address(firstHookPos).type(HOOK_ELEM_TYPE_JUMP).target((uint32_t)jumpDoNothing).build());
            elems.push_back(HookElementBuilder().address(secondHookPos).type(HOOK_ELEM_TYPE_ERASE_CODE).size(5).build());
            break;
        case HOOK_ELEM_TYPE_PATCH_DATA:
            elems.push_back(HookElementBuilder().address(firstHookPos).type(HOOK_ELEM_TYPE_PATCH_DATA).target((uint32_t)patch1).dataSize(5).build());
            elems.push_back(HookElementBuilder().address(secondHookPos).type(HOOK_ELEM_TYPE_PATCH_DATA).target((uint32_t)patch2).dataSize(5).build());
            break;
        case HOOK_ELEM_TYPE_ERASE_CODE:
            elems.push_back(HookElementBuilder().address(firstHookPos).type(HOOK_ELEM_TYPE_ERASE_CODE).size(5).build());
            elems.push_back(HookElementBuilder().address(secondHookPos).type(HOOK_ELEM_TYPE_ERASE_CODE).size(5).build());
            break;
        case HOOK_ELEM_TYPE_REPLACE_CALL:
            // ignore
            break;
        case HOOK_ELEM_TYPE_HOOKFUNCTION:
            // CRASHES DUE TO setting hook in middle of function (after registers are backed up on stack, esp is changed due to entering hook, then registers are popped, trashing return address)
            // elems.push_back(HookElementBuilder().address(firstHookPos).type(HOOK_ELEM_TYPE_HOOKFUNCTION).callableFunctionHookFunc<void, 0>(hookfunctionFuncDoNothing).build());
            // elems.push_back(HookElementBuilder().address(secondHookPos).type(HOOK_ELEM_TYPE_HOOKFUNCTION).callableFunctionHookFunc<void, 0>(hookfunctionFunc).build());
            break;
        default:
            break;
        }

        Hook hook(elems);
        hook.enable();
        if (type == HOOK_ELEM_TYPE_JUMP)
        {
            // need to correct "return address" for jump
            patchSDword((uint32_t)jumpDoNothing + 1, firstHookPos + 5, nullptr);
        }

        int result;
        switch (type)
        {
        case HOOK_ELEM_TYPE_CALL_RAW:
            result = expectRegisterValues();
            // no code to set register values - must fail, but after "nothing changed" check
            myassert(result >= 6, wxString::Format("[call raw hook] received invalid fail reason %d", result));
            break;
        case HOOK_ELEM_TYPE_AUTOHOOK:
            result = expectRegisterValues();
            myassert(result == 0, wxString::Format("[autohook] received fail reason %d", result));
            break;
        case HOOK_ELEM_TYPE_CALL:
            result = expectRegisterValues();
            myassert(result == 0, wxString::Format("[call] received fail reason %d", result));
            break;
        case HOOK_ELEM_TYPE_JUMP:
            result = expectRegisterValues();
            // like raw call hook
            myassert(result >= 6, wxString::Format("[jump hook] received invalid fail reason %d", result));
            break;
        case HOOK_ELEM_TYPE_PATCH_DATA:
            myassert(memcmp((void*)firstHookPos, patch1, 5) == 0,
                wxString::Format("[patch data] first memory compare failed (expected: '%s', actual: '%s')", getCodeString((uint32_t)patch1, 5), getCodeString(firstHookPos, 5)));
            myassert(memcmp((void*)secondHookPos, patch2, 5) == 0,
                wxString::Format("[patch data] second memory compare failed (expected: '%s', actual: '%s')", getCodeString((uint32_t)patch2, 5), getCodeString(secondHookPos, 5)));
            break;
        case HOOK_ELEM_TYPE_ERASE_CODE:
            for (auto data = { std::make_pair(firstHookPos, "erase code; first hook"), std::make_pair(secondHookPos, "erase code; second hook") };
                auto [addr, str] : data)
            {
                myassert(readCodeAsString(addr, 5) == "\x90\x90\x90\x90\x90", wxString::Format("[%s] erased code ('%s') contains other bytes than NOPs", str, getCodeString(addr, 5)));
            }
            break;
        case HOOK_ELEM_TYPE_REPLACE_CALL:
            break;
        default:
            break;
        }
        
        hook.disable();
        myassert(memcmp(expectRegisterValues, copy.data(), copy.size()) == 0, "Memory comparison after disabling hook failed");
    };

    for (auto type : { HOOK_ELEM_TYPE_CALL_RAW, HOOK_ELEM_TYPE_CALL, HOOK_ELEM_TYPE_AUTOHOOK, HOOK_ELEM_TYPE_JUMP, HOOK_ELEM_TYPE_PATCH_DATA, HOOK_ELEM_TYPE_ERASE_CODE, HOOK_ELEM_TYPE_HOOKFUNCTION })
    {
        doTest(type);
    }
    return myasserter.errors;
}

INSTANTIATE_TEMPLATES_MM_GAMES(std::vector<wxString>, HookTests::testBasicHookFunctionalityAndHookManager);

namespace // make vars file scoped
{
    namespace advancedHooksTestData // make vars non-conflicting with later code in this file
    {
        int setInt1, setInt2;
        int hookFunctionTestFailReasonId, replaceCallFailReasonInner, replaceCallFailReasonOuter;
    }
}

static int __declspec(naked) __fastcall hookFunctionTest1(int val1, int val2, unsigned char val3)
{
    using namespace advancedHooksTestData;
    _asm
    {
        push ebp
        mov ebp, esp
        sub esp, 8
        push ebx
        // from now on code probably won't be moved
        push esi
        push edi
        mov dword ptr [ebp - 4], ecx
        mov dword ptr [ebp - 8], edx
        // 1. first argument needs to be greater than 0x9348
        mov eax, dword ptr[ebp - 4]
        cmp eax, 0x9348
        mov hookFunctionTestFailReasonId, 1
        jbe fail
        
        mov hookFunctionTestFailReasonId, 2
        // 2. second argument needs to have 56 remainder in division by 123
        mov eax, dword ptr[ebp - 8]
        cdq
        mov ecx, 123
        idiv ecx
        cmp edx, 56
    jne fail
        mov hookFunctionTestFailReasonId, 3
        // 3. third argument needs to be zero-extended and bigger than 170
        mov eax, dword ptr[ebp + 8]
        cmp eax, 170
    jbe fail

        // returns first arg + second arg
        mov hookFunctionTestFailReasonId, 0
        fail:
        mov eax, dword ptr[ebp - 4]
        add eax, dword ptr[ebp - 8]
        pop edi
        pop esi
        pop ebx
        leave
        ret 4
    }
}

static int __declspec(naked) __stdcall replaceCallHookTestInner(unsigned char arg)
{
    using namespace advancedHooksTestData;
    _asm
    {
        // expect some values to be set
        // 1. need SF ~= OF
       /* mov replaceCallFailReasonInner, 1
        jl fail

        // 2. ax has to be 0x3333
        mov replaceCallFailReasonInner, 2
        cmp ax, 0x3333
        jne fail

        // 3. esi has to be 0x1234
        mov replaceCallFailReasonInner, 3
        cmp esi, 0x1234
        jne fail
        */

        // byte [esp + 4] has to be 0x13

        mov replaceCallFailReasonInner, 1
        cmp byte ptr[esp + 4], 0x13
        jne fail

        mov setInt1, 0x33

        mov setInt2, 0xFFFFFFFF

        xor eax, eax
        jmp doExit
    fail:
        mov eax, replaceCallFailReasonInner
    doExit:
        ret 4
    }
}

static int __declspec(naked) __stdcall replaceCallHookTestOuter()
{
    using namespace advancedHooksTestData;
    _asm
    {
        mov setInt1, 13
        mov setInt2, 0
        push 0x88888888
        call replaceCallHookTestInner

        // 1. need SF ~= OF
        mov replaceCallFailReasonOuter, 1
        jl fail

        // 2. ax has to be 0x3333
        mov replaceCallFailReasonOuter, 2
        cmp ax, 0x3333
        jne fail

        // 3. esi has to be 0x1234
        mov replaceCallFailReasonOuter, 3
        cmp esi, 0x1234
        jne fail

        mov replaceCallFailReasonOuter, 5
        cmp setInt1, 0x33
        jne fail
        mov replaceCallFailReasonOuter, 6
        cmp setInt2, 0xFFFFFFFF
        jne fail

        xor eax, eax
        jmp success

    fail:
        mov eax, replaceCallFailReasonOuter

    success:
        ret
    }
}

template<typename Player, typename Game>
static std::vector<wxString> HookTests::testAdvancedHookFunctionality()
{
    Asserter myasserter("Advanced hook functionality");
    using HookFunctionType = CallableFunctionHookOrigFunc<int, int, int, unsigned char>;
    static std::mt19937 gen(std::random_device{}());
    auto hookFunctionFunc = [&](HookData* d, HookFunctionType def, int val1, int val2, unsigned char val3) -> int
    {
        myassert(val1 == 0x5555, wxString::Format("val1 has value of 0x%X", val1));
        myassert(val2 == 0x2, wxString::Format("val2 has value of 0x%X", val2));
        myassert(val3 == 0x44, wxString::Format("val3 has value of 0x%X", val3));
        // 1. first argument needs to be greater than 0x9348
        // 2. second argument needs to have 56 remainder in division by 123
        // 3. third argument needs to be zero-extended and bigger than 170
        // 4. return value must be sum of first two args
        
        int first = std::uniform_int_distribution(0x9349, 0x23854)(gen);
        int second = std::uniform_int_distribution(345, 43238)(gen);
        int r = second % 123;
        second += 123 + 56 - r; // 123 to avoid potential negative int unexpected behavior
        unsigned char third = std::uniform_int_distribution(180, 220)(gen);
        int result = def(first, second, third);
        myassert(result == first + second, wxString::Format("[hookfunction test] result value is invalid (expected 0x%X, got 0x%X)", first + second, result));
        r = advancedHooksTestData::hookFunctionTestFailReasonId;
        myassert(r == 0, wxString::Format("[hookfunction test] got invalid fail reason %d", r));
        return HOOK_RETURN_SUCCESS;
    };



    using ReplaceCallType = CallableFunctionHookOrigFunc<int, unsigned char>;
    auto replaceCallFunc = [&](HookData* d, ReplaceCallType def, unsigned char arg) -> int
    {
        // SIGNED CHAR is sign-extended here, failing this check
        myassertf(arg == 0x88, "[replace call, inner] received arg 0x%X instead of expected 0x88",  arg);
        // 1. need SF ~= OF
        // 2. ax has to be 0x3333
        // 3. esi has to be 0x1234
        // 4. byte [esp + 4] has to be 0x13
        d->SF = d->OF;
        //d->ax = 0x3333; // eax is assigned result of this function call
        d->esi = 0x1234;
        //byte(d->esp + 4) = 0x13;
        int errorId = def(0x13);
        myassertf(errorId == 0, "[replace call, inner] Received error id %d", errorId);
        return 0x00003333;
    };

    Hook hook
    ({
        HookElementBuilder().address((uint32_t)hookFunctionTest1).size(5).type(HOOK_ELEM_TYPE_HOOKFUNCTION).callableFunctionHookFunc<int, 2, int, int, unsigned char>(hookFunctionFunc).build(),
        HookElementBuilder().address(findCall(replaceCallHookTestOuter, replaceCallHookTestInner)).size(5).type(HOOK_ELEM_TYPE_REPLACE_CALL).callableFunctionHookFunc<int, 0, unsigned char>(replaceCallFunc).build()
    });
    hook.enable();
    int r = hookFunctionTest1(0x5555, 0x2, 0x44);
    myassert(r == HOOK_RETURN_SUCCESS, wxString::Format("Function call returned %d", r));

    r = replaceCallHookTestOuter();
    myassertf(r == 0, "[replace call, outer] received error id %d", r);

    // TODO: autohook

    return myasserter.errors;
}

INSTANTIATE_TEMPLATES_MM_GAMES(std::vector<wxString>, HookTests::testAdvancedHookFunctionality);

struct HookSizeTest
{
    int startOffset, hookSize, desiredResultSize;
    int minHookSize = 5;
};

struct FunctionInfo
{
    std::string name;
    std::vector<int> instructionSizes;
    std::vector<HookSizeTest> hookSizeTests;
};

// IF STATIC KEYWORD IS OMITTED, function "addresses" will be of a jump to it instead of its address

static void __declspec(naked) getRealHookSizeTest1()
{
    _asm
    {
        add edx, 4
        cmp esp, eax
        fild dword ptr[eax]
        bswap eax
        inc dword ptr ds:[0x43432583]
    }
}

static void __declspec(naked) getRealHookSizeTest2()
{
    _asm
    {
        imul edi, eax
        imul esp, esp, 0x348
        test dword ptr[eax + 0x50], 3
        call cs : 0x5984753
        movzx eax, byte ptr[esp + 8]

        // far jump
        // jmp 0x33:54938594
        _emit 0xEA
        _emit 0xE2
        _emit 0x4B
        _emit 0x46
        _emit 0x03
        _emit 0x33
        _emit 0x0

        sti
        stosd
        rep movsb
    }
}

static void __declspec(naked) getRealHookSizeTest3()
{
    _asm
    {
        sete byte ptr ds:[0x54358]
        lock cmpxchg dword ptr ds:[0x45354], eax
        repne scasb
        cpuid
        add cl, dh
        movsx dx, byte ptr[eax + ecx * 8 + 0x5438754]
        hlt
        int 3
        fld1
        sbb ax, dx
    }
}

static void __declspec(naked) getRealHookSizeTest4()
{
    _asm
    {
        cmp DWORD PTR[eax * 8 + 0x0], ecx
        aaa
        cmovge ax, bx
        je $+0x10
        test BYTE PTR[esp + 0x50], ah
        test WORD PTR[eax + ecx * 8], 0x3030
        btr eax, 0x4
        movzx dx, BYTE PTR[eax + 0x50]
        cbw
    }
}

const std::map<void(*)(), FunctionInfo> testData({
    {
        getRealHookSizeTest1,
        {.name = "getRealHookSizeTest1", .instructionSizes = {3, 2, 2, 2, 7}, .hookSizeTests = 
            {
                {.startOffset = 0, .hookSize = 5, .desiredResultSize = 5},
                {.startOffset = 0, .hookSize = 6, .desiredResultSize = 7},
                {.startOffset = 0, .hookSize = 7, .desiredResultSize = 7},
                {.startOffset = 0, .hookSize = 12, .desiredResultSize = 16},
                {.startOffset = 3, .hookSize = 6, .desiredResultSize = 6},
                {.startOffset = 5, .hookSize = 6, .desiredResultSize = 11},
            }
        }
    },
    {
        getRealHookSizeTest2,
        {.name = "getRealHookSizeTest2", .instructionSizes = {3, 6, 7, 7, 5, 7, 1, 1, 2}, .hookSizeTests =
            {
                {.startOffset = 0, .hookSize = 5, .desiredResultSize = 9},
                {.startOffset = 0, .hookSize = 10, .desiredResultSize = 16},
                {.startOffset = 0, .hookSize = 20, .desiredResultSize = 23},
                {.startOffset = 3, .hookSize = 13, .desiredResultSize = 13},
                {.startOffset = 10, .hookSize = 10, .desiredResultSize = 13},
                {.startOffset = 16, .hookSize = 5, .desiredResultSize = 7},
            }
        }
    },
    {
        getRealHookSizeTest3,
        {.name = "getRealHookSizeTest3", .instructionSizes = {8, 9, 2, 2, 2, 9, 1, 1, 2, 3}, .hookSizeTests =
            {
                {.startOffset = 0, .hookSize = 5, .desiredResultSize = 8},
                {.startOffset = 0, .hookSize = 15, .desiredResultSize = 17},
                {.startOffset = 17, .hookSize = 3, .desiredResultSize = 4, .minHookSize = 3},
                {.startOffset = 8, .hookSize = 1, .desiredResultSize = 9, .minHookSize = 1},
                {.startOffset = 19, .hookSize = 6, .desiredResultSize = 13},
            }
        }
    },
    {
        getRealHookSizeTest4,
        {.name = "getRealHookSizeTest4", .instructionSizes = {7, 1, 4, 6, 4, 6, 4, 5, 2}, .hookSizeTests =
            {
                {.startOffset = 0, .hookSize = 9, .desiredResultSize = 12},
                {.startOffset = 0, .hookSize = 5, .desiredResultSize = 7},
                {.startOffset = 7, .hookSize = 6, .desiredResultSize = 11},
                {.startOffset = 12, .hookSize = 1, .desiredResultSize = 6, .minHookSize = 1},
                {.startOffset = 22, .hookSize = 10, .desiredResultSize = 10},
            }
        }
    },
 });

struct CopyCodeTestDataItem
{
    int startOffset, instrOffset, copySize;
    std::vector<int> rel32ToFix;
};

struct CopyCodeTestData
{
    std::string name;
    std::vector<int> instructionSizes;
    std::vector<CopyCodeTestDataItem> tests;
    bool writeJumpBack = true;
};

static __declspec(naked) void copyCodeTest1()
{
    _asm
    {
        call $ + 0x438732 // to force rel32
        cmp eax, ebx
        add ecx, eax
        je $ + 0x3854
        ret
    }
}

static __declspec(naked) void copyCodeTest2()
{
    _asm
    {
        ret 0x4555
        bt ax, 2
        jc $+0xAAAAAAAA
        call $+0xFFFF
        test byte ptr[esp + 0x40], cl
        jne $+0x43258439
    }
}

static __declspec(naked) void copyCodeTest3()
{
    _asm
    {
        cmovnc eax, dword ptr[ebx + ecx + 0x50]
        setne al
        jmp $+0x123
        aas
        movzx ecx, bx
        call $+0x5555
        cmp ecx, dword ptr[esp]
        jne $+0x88888888
    }
}

const std::map<void(*)(), CopyCodeTestData> copyCodeTests = 
{ // initializer list call
    { // initializer list element
        copyCodeTest1,
        { // test struct
            .name = "CopyCodeTest1", .instructionSizes = {5, 2, 2, 6, 1}, .tests = 
            {
                {.startOffset = 0, .instrOffset = 0, .copySize = 5, .rel32ToFix = {1}},
                {.startOffset = 0, .instrOffset = 0, .copySize = 15, .rel32ToFix = {1, 11}},
                {.startOffset = 7, .instrOffset = 2, .copySize = 8, .rel32ToFix = {11}}, // rel32ToFix is relative to data begin, not startOffset
            },
        }
    },
    {
        copyCodeTest2,
        {
            .name = "CopyCodeTest2", .instructionSizes = {3, 5, 6, 5, 4, 6}, .tests = 
            {
                {.startOffset = 0, .instrOffset = 0, .copySize = 29, .rel32ToFix = {10, 15, 25}},
                {.startOffset = 0, .instrOffset = 0, .copySize = 19, .rel32ToFix = {10, 15}},
                {.startOffset = 0, .instrOffset = 0, .copySize = 14, .rel32ToFix = {}},
                {.startOffset = 3, .instrOffset = 1, .copySize = 11, .rel32ToFix = {10}},
                {.startOffset = 8, .instrOffset = 2, .copySize = 21, .rel32ToFix = {10, 15, 25}},
            },
        },
    },
    {
        copyCodeTest3,
        {
            .name = "CopyCodeTest3", .instructionSizes = {5, 3, 5, 1, 3, 5, 3, 6}, .tests =
            {
                {.startOffset = 0, .instrOffset = 0, .copySize = 31, .rel32ToFix = {9, 18, 27}},
                {.startOffset = 0, .instrOffset = 0, .copySize = 13, .rel32ToFix = {9}},
                {.startOffset = 0, .instrOffset = 0, .copySize = 5, .rel32ToFix = {}},
                {.startOffset = 5, .instrOffset = 1, .copySize = 0x1A, .rel32ToFix = {9, 18}},
                {.startOffset = 17, .instrOffset = 5, .copySize = 14, .rel32ToFix = {18, 27}},
            },
        },
    },
};

struct FindCodeTestItem
{
    int offset;
    std::string code;
    int desiredOffset;
};

struct FindCodeTestStruct
{
    std::string name;
    std::vector<FindCodeTestItem> tests;
};

// reuse previous functions
const std::map<void(*)(), FindCodeTestStruct> findCodeTests =
{ // initializer list
    { // list element
        getRealHookSizeTest1,
        { // struct
            .name = "getRealHookSizeTest1", .tests = 
            {
                // vector list elements
                {.offset = 0, .code = "\x83\xC2\x04", .desiredOffset = 0 }, // add
                {.offset = 0, .code = "\x0F\xC8", .desiredOffset = 7 }, // bswap
                {.offset = 5, .code = "\x0F\xC8", .desiredOffset = 7 }, // bswap
                {.offset = 0, .code = ">\xFF\x05\x83%CC", .desiredOffset = 9 }, // inc
            }
        },
    },
    {
        getRealHookSizeTest4,
        { // vector initializer list
             // vector list elements
            .name = "getRealHookSizeTest4", .tests =
            {
                {.offset = 0, .code = "f\x0FM\xC3", .desiredOffset = 8 }, // cmovge
                {.offset = 0, .code = "f\xF7\x04\xC8" "00", .desiredOffset = 0x16 }, // test (second)
                {.offset = 8, .code = "f\xF7\x04\xC8" "00", .desiredOffset = 0x16 }, // test (second)
                {.offset = 0, .code = "\x0F\xBA\xF0\x04", .desiredOffset = 0x1C }, // btr
                {.offset = 0, .code = "f\x98", .desiredOffset = 0x25 }, // cbw
                {.offset = 0x12, .code = "f\x98", .desiredOffset = 0x25 }, // cbw
            }
        },
    }
};

static void __declspec(naked) findCallFunc1()
{

}

static void __declspec(naked) findCallFunc2()
{

}

static void __declspec(naked) findCallFunc3()
{

}

static void __declspec(naked) findCallTest1()
{
    _asm
    {
        cmp ebx, ecx
        call findCallFunc1
        call findCallFunc2
        call findCallFunc3
        jmp $+0xFFFF
        sete byte PTR [esp + 20]
        imul ecx, ebx, 20
        call findCallFunc3
        add eax, ebx
        call $+0xFFFF
        ret
    }
}

static void __declspec(naked) findCallTest2()
{
    _asm
    {
        fld qword ptr[esp]
        inc al
        call $+0x4325
        call $+0x28452
        jmp $+0x85437
        sbb dx, bx
        aaa
        popcnt eax, ebx
        outsd
        call findCallFunc2
        repne cmpsw
        add dword ptr [eax + 0x40], edx
        call findCallFunc3
        call $+0x323832
        idiv dx
        rep movsd
        call findCallFunc1
    }
}

struct FindCallTestItem
{
    uint32_t findOffset;
    void* address;
    uint32_t desiredOffset;
};

struct FindCallTest
{
    std::string name;
    std::vector<FindCallTestItem> tests;
};

// STDCALL function has incompatible type
const std::map<void(*)(), FindCallTest> findCallTests =
{ // init list
    { // init list item
        findCallTest1,
        { // struct
            .name = "findCallTest1", .tests = 
            {
                {.findOffset = 0, .address = findCallFunc1, .desiredOffset = 2},
                {.findOffset = 0, .address = findCallFunc2, .desiredOffset = 7},
                {.findOffset = 0, .address = findCallFunc3, .desiredOffset = 0xC},
                {.findOffset = 0x11, .address = findCallFunc3, .desiredOffset = 0x1E},
                {.findOffset = 0, .address = nullptr, .desiredOffset = 2},
                {.findOffset = 0x16, .address = nullptr, .desiredOffset = 0x1E},
                {.findOffset = 0x23, .address = nullptr, .desiredOffset = 0x25},
            }
        }
    },
    { // init list item
        findCallTest2,
        { // struct
            .name = "findCallTest2", .tests = 
            {
                {.findOffset = 0, .address = nullptr, .desiredOffset = 5},
                {.findOffset = 0, .address = findCallFunc2, .desiredOffset = 0x1D},
                {.findOffset = 0, .address = findCallFunc1, .desiredOffset = 0x37},
                {.findOffset = 0xF, .address = nullptr, .desiredOffset = 0x1D},
                {.findOffset = 0x22, .address = nullptr, .desiredOffset = 0x28},
                {.findOffset = 0x28, .address = findCallFunc3, .desiredOffset = 0x28},
                {.findOffset = 0x2D, .address = nullptr, .desiredOffset = 0x2D},
            }
        }
    },
};

template<typename Player, typename Game>
static std::vector<wxString>
HookTests::testMiscFunctions()
{
    
    Asserter myasserter("Misc low level functions");
    auto checkInstructionSizes = [&](uint32_t addr, const std::string& name, const std::vector<int>& instructionSizes, int instrOffset = 0, int copySize = 0)
    {
        int off = 0, i = 0;
        for (size_t instrId = instrOffset; instrId < instructionSizes.size(); ++instrId)
        {
            int instrSize = instructionSizes[instrId];
            int s = getInstructionSize(addr + off);
            myassert(s == instrSize,
                wxString::Format("[%s] instruction index %d (offset: %d) has invalid size (current: %d, expected: %d)", name, i, instrOffset, s, instrSize)
            );
            ++i;
            off += s;
            if (copySize > 0 && off == copySize)
            {
                break;
            }
        }
    };

    // getInstructionSize, getRealHookSize
    for (const auto& [func, data] : testData)
    {
        uint32_t funcPtr = (uint32_t)func;
        checkInstructionSizes(funcPtr, data.name, data.instructionSizes);

        int i = 0;
        for (const HookSizeTest& test : data.hookSizeTests)
        {
            int size = getRealHookSize(funcPtr + test.startOffset, test.hookSize, test.minHookSize);
            myassert(size == test.desiredResultSize,
                wxString::Format("[%s] hook size test %d failed (offset: %d, initial size: %d, expected size: %d, current size: %d",
                    data.name, i, test.startOffset, test.hookSize, test.desiredResultSize, size
                )
            );
            ++i;
        }
    }

    // copyCode
    for (const auto& [func, data] : copyCodeTests)
    {
        uint32_t funcPtr = (uint32_t)func;
        checkInstructionSizes(funcPtr, data.name + " (old)", data.instructionSizes);
        for (const auto& test : data.tests)
        {
            uint32_t newCode = copyCode(funcPtr + test.startOffset, test.copySize, data.writeJumpBack);
            uint32_t change = newCode - funcPtr;

            checkInstructionSizes(newCode, data.name + " (new)", data.instructionSizes, test.instrOffset, test.copySize);
            std::vector<int> instructionSizeByOffset(test.copySize + test.startOffset);
            std::vector<int> instructionFirstByteOffset(test.copySize + test.startOffset);

            {
                int index = 0;
                for (int size : data.instructionSizes)
                {
                    for (int i = 0; i < size; ++i)
                    {
                        instructionSizeByOffset.at(index + i) = size;
                        instructionFirstByteOffset.at(index + i) = index;
                    }
                    index += size;
                    if (index >= test.copySize)
                    {
                        break;
                    }
                }
            }

            for (int off : test.rel32ToFix)
            {
                // off is relative to function begin, not start of copying
                uint32_t oldNumOff = funcPtr + off;
                uint32_t newNumOff = newCode + off - test.startOffset;
                // we need: instruction end (instruction address and size), instruction  and immediate value
                
                int first = instructionFirstByteOffset.at(off), size = instructionSizeByOffset.at(off);
                uint32_t oldDest = sdword(oldNumOff) + first + funcPtr + size;
                uint32_t newDest = sdword(newNumOff) + first - test.startOffset + newCode + size;
                myassert(oldDest == newDest,
                    wxString::Format("[copy code test '%s'] code at 0x%X (copied from 0x%X) has invalid rel32 destination at position %d (old: 0x%X, new: 0x%X)",
                        data.name, newCode, funcPtr, off, oldDest, newDest
                    )
                );
            }

            codeMemoryFree((void*)newCode);
        }
    }

    // findCode
    for (const auto& [func, data] : findCodeTests)
    {
        const uint32_t funcPtr = (const uint32_t)func;
        for (const FindCodeTestItem& test : data.tests)
        {
            const uint32_t fullTestOffset = funcPtr + test.offset, fullDesiredOffset = funcPtr + test.desiredOffset;
            const uint32_t fullFoundOffset = findCode(fullTestOffset, test.code);
            myassert(fullFoundOffset == fullDesiredOffset,
                wxString::Format("[findCode test '%s'] Tried to find code '%s' at 0x%X, desired offset is 0x%X, got 0x%X",
                    data.name, codeToSemiReadableString(test.code), fullTestOffset, fullDesiredOffset, fullFoundOffset
                )
            );
        }
    }

    // findCall
    for (const auto& [func, data] : findCallTests)
    {
        uint32_t funcPtr = (uint32_t)func;
        int i = 0;
        for (const FindCallTestItem& test : data.tests)
        {
            uint32_t findFull = test.findOffset + funcPtr, desiredFull = test.desiredOffset + funcPtr;
            uint32_t result = findCall(findFull, test.address);
            myassertf(result == desiredFull, "[find call, %s, test id %d] Tried to find address 0x%X at 0x%X, received 0x%X", data.name, i, findFull, test.address, desiredFull);
            ++i;
        }
    }
    
    return myasserter.errors;
}

INSTANTIATE_TEMPLATES_MM_GAMES(std::vector<wxString>, HookTests::testMiscFunctions);

/*
template std::vector<wxString> HookTests::testBasicHookFunctionalityAndHookManager<mm6::Player, mm6::Game>();
template std::vector<wxString> HookTests::testBasicHookFunctionalityAndHookManager<mm7::Player, mm7::Game>();
template std::vector<wxString> HookTests::testBasicHookFunctionalityAndHookManager<mm8::Player, mm8::Game>();*/

template<typename Player, typename Game>
static std::vector<wxString> HookTests::run()
{
    return mergeVectors({ testHookPlacingAndSize<Player, Game>(), testMiscFunctions<Player, Game>(), testBasicHookFunctionalityAndHookManager<Player, Game>(), testAdvancedHookFunctionality<Player, Game>()});
}

template std::vector<wxString> HookTests::run<mm6::Player, mm6::Game>();
template std::vector<wxString> HookTests::run<mm7::Player, mm7::Game>();
template std::vector<wxString> HookTests::run<mm8::Player, mm8::Game>();