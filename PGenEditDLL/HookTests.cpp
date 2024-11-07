#include "pch.h"
#include "HookTests.h"
#include "LowLevel.h"
#include "Hook.h"

static const char NOP[] = "\x90";

using BasicFuncType = void(*)(); // function returning void and without arguments

// dst, src, size
std::vector<uint8_t> util::lowLevel::memcpyVector(void* src, uint32_t size)
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

std::vector<wxString> HookTests::testHookPlacingAndSize()
{
    std::vector<std::vector<uint8_t>> codeBackup;
    // test hook size: patchData, callRaw, call, jump (for detours check if opcode and function address is correct, for all check that bytes beyond 5 are NOP-ed if they are in range of hook size)
    // for each type do at least three different size instructions at the beginning
    // on the occasion, also test if disabling a hook fully restores previous instructions/data
    // also testing both manual function calls and creating complex hook would be nice, but not required
    int funcSizes[3] = { 10, 13, 18 };
    using util::lowLevel::memcpyVector;
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
                    hookJump(addr, (void*)0xFEFEFEFE, &autoCodeCopy, hookSize);
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
                myassert(realSize == autoCodeCopy.size(), wxString::Format("%sReal hook size (%d) and auto code asmpatchBackup size (%d) don't match", basicInfoStr, realSize, autoCodeCopy.size()));
                myassert(memcmp((void*)oldCodeVec.data(), (void*)autoCodeCopy.data(), realSize) == 0,
                    wxString::Format("%sBackup memory and asmpatchBackup memory done by hook functions don't match: %s\t\t%s",
                        basicInfoStr, getCodeString((uint32_t)codeBackup[funcId].data(), realSize), getCodeString((uint32_t)autoCodeCopy.data(), realSize)
                    )
                );
                for (int i = firstNopIndex; i < realSize; ++i)
                {
                    myassert(byte(newCode + i) == 0x90, wxString::Format("%sRequired byte is not NOP-ed (address 0x%X, byte index %d)", basicInfoStr, addr, i));
                }
                // restore asmpatchBackup code
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

std::vector<wxString> HookTests::testBasicHookFunctionalityAndHookManager()
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
    std::vector<HookElement*> elems;
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

            elems.push_back(new hk::CallRaw(firstHookPos, (uint32_t)callDoNothing)),
            elems.push_back(new hk::EraseCode(secondHookPos, 5));
            break;
        case HOOK_ELEM_TYPE_CALL:
            elems.push_back(new hk::Call(firstHookPos, doNothing));
            elems.push_back(new hk::Call(secondHookPos, myHookFunc));
            break;
        case HOOK_ELEM_TYPE_AUTOHOOK_BEFORE:
            elems.push_back(new hk::AutohookBefore(firstHookPos, doNothing));
            elems.push_back(new hk::AutohookBefore(secondHookPos, myHookFuncAutohook));
            break;
        case HOOK_ELEM_TYPE_AUTOHOOK_AFTER:
            elems.push_back(new hk::AutohookAfter(firstHookPos, doNothing));
            elems.push_back(new hk::AutohookAfter(secondHookPos, myHookFuncAutohook));
            break;
        case HOOK_ELEM_TYPE_JUMP:
            elems.push_back(new hk::Jump(firstHookPos, (uint32_t)jumpDoNothing));
            elems.push_back(new hk::EraseCode(secondHookPos, 5));
            break;
        case HOOK_ELEM_TYPE_PATCH_DATA:
            elems.push_back(new hk::PatchData(firstHookPos, std::string(patch1, 5)));
            elems.push_back(new hk::PatchData(secondHookPos, std::string(patch2, 5)));
            break;
        case HOOK_ELEM_TYPE_ERASE_CODE:
            elems.push_back(new hk::EraseCode(firstHookPos, 5));
            elems.push_back(new hk::EraseCode(secondHookPos, 5));
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
        case HOOK_ELEM_TYPE_AUTOHOOK_BEFORE:
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

    for (auto type : { HOOK_ELEM_TYPE_CALL_RAW, HOOK_ELEM_TYPE_CALL, HOOK_ELEM_TYPE_AUTOHOOK_BEFORE, HOOK_ELEM_TYPE_JUMP, HOOK_ELEM_TYPE_PATCH_DATA, HOOK_ELEM_TYPE_ERASE_CODE, HOOK_ELEM_TYPE_HOOKFUNCTION })
    {
        doTest(type);
    }
    return myasserter.errors;
}

namespace // make vars file scoped
{
    namespace advancedHooksTestData // make vars non-conflicting with later code in this file
    {
        int setInt1, setInt2;
        int hookFunctionTestFailReasonId, replaceCallFailReasonInner, replaceCallFailReasonOuter, autohookFailReason;
        bool setBoolAutohook;
        int64_t setIntAutohook;
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

static uint32_t returnAValueFunc(unsigned char arg1, int arg2)
{
    return arg1 + arg2;
}

static int __declspec(naked) autohookTest()
{
    using namespace advancedHooksTestData;
    _asm
    {
        // 1. ax has to be 0x5678
        xor eax, eax
        mov autohookFailReason, 1
        // relocated start
        nop
        cmp ax, 0x5678
        mov eax, 0x22222222
        // relocated end
        jne fail
        mov autohookFailReason, 2
        // 2. eax has to be changed by relocated code
        cmp eax, 0x22222222
        jne fail
        // 3. edx has to be 0x10101010
        mov autohookFailReason, 3
        cmp edx, 0x10101010
        jne fail

        mov autohookFailReason, 4
        // relocated start 2
        // nop word ptr ds:[eax], ax // 0x660F1F00
        _emit 0x66
        _emit 0x0F
        _emit 0x1F
        _emit 0
        // 4. edx has to be 15
        add edx, 5
        // relocated end 2

        cmp edx, 20
        jne fail


        xor eax, eax
        jmp end
        fail:
        mov eax, autohookFailReason
        end:
        ret
    }
}

std::vector<wxString> HookTests::testAdvancedHookFunctionality()
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

    /*
     *  // 1. ax has to be 0x5678
        xor eax, eax
        mov autohookFailReason, 1
        // relocated start
        cmp ax, 0x5678
        mov eax, 0x12345678
        // relocated end
        jne fail
        // 2. edx has to be 0x10101010
        mov autohookFailReason, 2
        cmp edx, 0x10101010
        jne fail

        mov autohookFailReason, 3
        // relocated start 2
        nop word [eax] // 0x660F1F00
        // 3. edx has to be 15*/

    auto autohookFunc1 = [](HookData* d) -> int
    {
        d->ax = 0x5678;
        d->edx = 0x10101010;
        return HOOK_RETURN_SUCCESS;
    };

    auto autohookFunc2 = [](HookData* d) -> int
    {
        d->edx = 15;
        return HOOK_RETURN_SUCCESS;
    };

    Hook hook
	{ {
		hk::HookFunction::create<int, 2, int, int, unsigned char>((uint32_t)hookFunctionTest1, hookFunctionFunc, 5),
		hk::ReplaceCall::create<int, 0, unsigned char>(findCall(replaceCallHookTestOuter, replaceCallHookTestInner), replaceCallFunc),
        new hk::AutohookBefore((uint32_t)findCode(autohookTest, NOP), autohookFunc1, 6),
        new hk::AutohookBefore((uint32_t)findCode(autohookTest, "\x66\x0F\x1F\x00", 4), autohookFunc2, 5),
    } };
    hook.enable();
    int r = hookFunctionTest1(0x5555, 0x2, 0x44);
    myassert(r == HOOK_RETURN_SUCCESS, wxString::Format("Function call returned %d", r));

    r = replaceCallHookTestOuter();
    myassertf(r == 0, "[replace call, outer] received error id %d", r);

    r = autohookTest();
    myassertf(r == 0, "[autohook] received error id %d", r);

    return myasserter.errors;
}

namespace
{
    namespace asmhookTests
    {
        int returnCode;
    }
}

__declspec(naked) static bool asmhookTest1(bool before)
{
    using namespace asmhookTests;
    _asm
    {
        and returnCode, 0
        xor eax, eax
        // hook here (adds 5 to eax)
        nop
        shr eax, 1
        nop
        nop
        // hook end
        test byte ptr[esp + 4], 0xFF
        je $after
            // should have 2 in eax
            cmp eax, 2
            jmp $tested
        $after:
        cmp eax, 5

        $tested:
        sete al
        movzx eax, al

        ret
    }
}

__declspec(naked) static bool asmpatchTest1()
{
    _asm
    {
        repne cmpsb
        add edx, dword ptr[ebp + 4]
        clc
        imul eax, 15
        std
        fld dword ptr [esp]
        ret
    }

    /*
    0:  f2 a6                   repnz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
    2:  03 55 04                add    edx,DWORD PTR [ebp+0x4]
    5:  f8                      clc
    6:  6b c0 0f                imul   eax,eax,0xf
    9:  fd                      std
    a:  d9 04 24                fld    DWORD PTR [esp]
    d:  c3                      ret
*/
}

__declspec(naked) static bool asmpatchTest2()
{
    _asm
    {
        xor ah, dl
        setne byte ptr [esp + 0x20]
        call $+0
        sub eax, eax
        sbb edx, edx
        btr eax, edx
    }

    /*
    0:  30 d4                   xor    ah,dl
    2:  0f 95 44 24 20          setne  BYTE PTR [esp+0x20]
    7:  e8 fb ff ff ff          call   7 <_main+0x7>
    c:  29 c0                   sub    eax,eax
    e:  19 d2                   sbb    edx,edx
    10: 0f b3 d0                btr    eax,edx
*/
}

// real example, will be called
__declspec(naked) static bool asmpatchTest3()
{
    _asm
    {
        push ebp
        xor ebp, ebp
        // patch here, sets bp to 0x1000
        mov ebp, 0x13131313
        cmp ebp, 0x1000
        sete al
        movzx eax, al
        pop ebp
        ret
    }
}

struct MemoryCompareItem
{
    uint32_t address;
    std::string expected;
};

struct AsmHookTest
{
    // either
    // compare memory so it is unchanged before and after
    // compare new code to that it is patched inline or a jump is emitted
    // check new code destination and its equality to provided code
    
    uint32_t address, size;
    std::string code;
};

struct AsmpatchTestItem
{
    uint32_t offset, size;
    uint32_t expectedSize; // expected inline, so for a jump out will be not less than 5
    std::string code;
    bool shouldBeInline;
};

struct AsmpatchTest
{
    int funcSize;
    std::vector<AsmpatchTestItem> tests;
};

std::map<BasicFuncType, AsmpatchTest> asmpatchTestsBasic =
{
    {
        /*
            0:  f2 a6                   repnz cmps BYTE PTR ds:[esi],BYTE PTR es:[edi]
            2:  03 55 04                add    edx,DWORD PTR [ebp+0x4]
            5:  f8                      clc
            6:  6b c0 0f                imul   eax,eax,0xf
            9:  fd                      std
            a:  d9 04 24                fld    DWORD PTR [esp]
            d:  c3                      ret
        */
        (BasicFuncType)asmpatchTest1,
        {
            .funcSize = 0xE,
            .tests = 
            { // vector
                { /* vector item */ .offset = 0, .size = 1, .expectedSize = 2, .code = "nop", .shouldBeInline = true },
                {.offset = 0, .size = 6, .expectedSize = 6, .code = "mov eax, 0x40404040\npush esi", .shouldBeInline = true },
                /*
                0:  39 d6                   cmp    esi,edx
                2:  fe c0                   inc    al
                4:  00 c4                   add    ah,al
                6:  0f 94 c3                sete   bl
                */
                {.offset = 0, .size = 1, .expectedSize = 5, .code = R"(
                    cmp esi, edx
                    inc al
                    add ah, al
                    sete bl)",
                    .shouldBeInline = false
                },
                {.offset = 0, .size = 6, .expectedSize = 6, .code = R"(
                    cmp esi, edx
                    inc al
                    add ah, al
                    sete bl
                    fld dword [ebp + 20])", // 9:  d9 45 14                fld    DWORD PTR [ebp+0x14]
                    .shouldBeInline = false
                },
                {.offset = 0, .size = 4, .expectedSize = 5, .code = (std::string)stringRep("nop\n", 14), .shouldBeInline = false },
        /*
        0:  66 af                   scas   ax,WORD PTR es:[edi]
        2:  66 11 d8                adc    ax,bx
        */
        {.offset = 5, .size = 5, .expectedSize = 5, .code = R"(
                    scasw
                    adc ax, bx)",
                    .shouldBeInline = true
                },
            }
        }
    }
};

std::vector<wxString> HookTests::testAsmHookFunctions()
{
    // asmhook
    Asserter myasserter("Asm hook tests");
    std::string code = "add eax, 5";
    Hook hook(new hk::AsmhookBefore(findCode(asmhookTest1, "\x90", 1), code.c_str(), 5));
    hook.enable();
    myassertf(asmhookTest1(true), "[before asmhook] test failed");
    hook.disable();
    hook.replaceElement(0, new hk::AsmhookAfter(findCode(asmhookTest1, "\x90", 1), code.c_str(), 5));
    hook.enable();
    myassertf(asmhookTest1(false), "[after asmhook] test failed");

    // asmpatch

    /*
    0:  39 d1                   cmp    ecx,edx
    2:  0f 95 c0                setne  al
    5:  66 85 d0                test   ax,dx
    8:  74 07                   je     11 <jmp>
    a:  48                      dec    eax
    b:  69 c0 e8 03 00 00       imul   eax,eax,0x3e8
     */
    std::string_view compiledAsmpatchCode = asmproc(R"(
    cmp ecx, edx
    setne al
    test ax, dx
    je @jmp
    dec eax
    imul eax, eax, 1000
    @jmp:
    jmp near 0x50505050
)");

    /*
    0:  aa                      stos   BYTE PTR es:[edi],al
    1:  87 ca                   xchg   edx,ecx
     **/
    std::string_view patch1 = R"(
    stosb
    xchg edx, ecx
)";

    std::string_view patch1Compiled = compileAsm(std::string(patch1));

    /*
    0:  bb 50 50 50 50          mov    ebx,0x50505050
    5:  f7 fe                   idiv   esi
    7:  83 c0 1e                add    eax,0x1e
    a:  c3                      ret
     **/
    std::string_view patch2 = R"(
    mov ebx, 0x50505050
    idiv esi
    add eax, 30
    ret
)";

    std::string_view patch2Compiled = compileAsm(std::string(patch2));

    hook.disable();
    hook.replaceElement(0, new hk::Asmpatch((uint32_t)compiledAsmpatchCode.data() + 2, (std::string)patch1), patch1Compiled.size());
    hook.enable();
    myassertf(memcmp(compiledAsmpatchCode.data() + 2, patch1Compiled.data(), patch1Compiled.size()) == 0, "Asmpatch test #1 memory compare #1 failed");
    myassertf(memcmp(compiledAsmpatchCode.data() + 5, "\x66\x85", 2) == 0, "Asmpatch test #1 memory compare #2 failed");

    hook.disable();
    hook.replaceElement(0, new hk::Asmpatch((uint32_t)compiledAsmpatchCode.data() + 5, "nop", 1));
    hook.enable();
    myassertf(memcmp(compiledAsmpatchCode.data() + 5, "\x90\x90\x90", 1) == 0, "Asmpatch test #2 memory compare #1 failed");
    myassertf(memcmp(compiledAsmpatchCode.data() + 8, "\x74\x07\x48", 3) == 0, "Asmpatch test #2 memory compare #2 failed");

    hook.disable();
    hook.replaceElement(0, new hk::Asmpatch((uint32_t)compiledAsmpatchCode.data(), (std::string)patch2, 5));
    hook.enable();
    myassertf(byte((uint32_t)compiledAsmpatchCode.data()) == 0xE9, "Asmpatch test #3 memory compare #1 failed - first byte is not near jump opcode");
    myassertf(memcmp(compiledAsmpatchCode.data() + 5, "\x66\x85\xD0\x74\x07\x48", 6) == 0, "Asmpatch test #3 memory compare #2 failed - instructions after jump are changed");
    uint32_t dest = relJumpCallTarget((uint32_t)compiledAsmpatchCode.data());
    myassertf(memcmp((void*)dest, patch2Compiled.data(), patch2Compiled.size()) == 0, "Asmpatch test #3 memory compare #3 failed - jump destination is invalid");

    hook.disable();
    hook.replaceElement(0, new hk::Asmpatch((uint32_t)compiledAsmpatchCode.data(), stringRep("nop\n", 7) + "push ebx", 7));
    hook.enable();
    //dest = relJumpCallTarget((uint32_t)compiledAsmpatchCode.data());
    auto codeString = stringRep("\x90", 7) + "\x53";
    myassertf(memcmp((void*)compiledAsmpatchCode.data(), codeString.data(), 8) == 0, "Asmpatch test #4 memory compare #1 failed - generated bytecode is invalid");
    // no jump back
    // myassertf(relJumpCallTarget(dest + 8) == (uint32_t)compiledAsmpatchCode.data(), "Asmpatch test #4 memory compare #2 failed - generated jump back jumps to wrong address");

    using util::lowLevel::memcpyVector;
    // predefined tests
    int i = 1;
    for (auto& [func, data] : asmpatchTestsBasic)
    {
        for (const AsmpatchTestItem& test : data.tests)
        {
            const auto& [offset, size, expectedSize, code, shouldBeInline] = test;
            std::vector<uint8_t> asmpatchBackup, fullBackup(memcpyVector(func, data.funcSize));
            uint32_t addr = (uint32_t)func + offset;
            void* newCode = asmpatch(addr, code, &asmpatchBackup, size, true);
            bool isInline = byte(addr) != 0xE9 || relJumpCallTarget(addr) != (uint32_t)newCode;
            if (shouldBeInline)
            {
                // theoretically, first byte could be jump opcode in other valid code, so also checking jump target
                myassertf(isInline, "[Asmpatch predefined test #%d] patch marked as inline was converted to jump out", i);
            }
            else
            {
                myassertf(!isInline, "[Asmpatch predefined test #%d] patch marked as jump out is inline", i);
            }
            int patchEnd = offset + expectedSize;
            if (offset > 0)
            {
                myassertf(memcmp(func, fullBackup.data(), offset) == 0, "[Asmpatch predefined test #%d] bytes before patch are changed", i);
            }
            if (patchEnd < data.funcSize)
            {
                void* first = (void*)((uint32_t)func + patchEnd);
                myassertf(memcmp(first, &fullBackup[patchEnd], data.funcSize - patchEnd) == 0, "[Asmpatch predefined test #%d] bytes after patch are changed", i);
            }
            // test that only provided bytes are changed
            unhookAsmpatch(addr, asmpatchBackup, newCode);
            // more...
            ++i;
        }
    }

    return myasserter.errors;
}

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

struct FormatAsmCodeTest
{
    std::string code, expected;
    CodeReplacementArgs params;
};

std::vector<FormatAsmCodeTest> formatAsmCodeTests =
{
    {
        .code = "mov eax, %eax%; add ecx, %d%; %s%;%%", .expected = "mov eax, 5; add ecx, 100000; cmp al, dh;%", .params = { {"eax", 5U}, {"d", 100000U}, {"s", "cmp al, dh"} },
    },
    {
        .code = "imul %1%, %2%, %3%", .expected = "imul eax, ebx, 5", .params = {{"1", "eax"}, {"2", "ebx"}, {"3", 5U}}
    },
    {
        .code = R"(cmp ecx, edx
            jne %dest%
            %op% edx, ecx ; %%%%%%%
            push %d%
        @here:
        )", .expected = R"(cmp ecx, edx
            jne @here
            sbb edx, ecx ; %%%%
            push 255
        @here:
        )", .params = {{"dest", "@here"}, {"op", "sbb"}, {"d", 255U}}
    },
    {
        .code = "%a%%b%", .expected = "23", .params = {{"a", 2U}, {"b", 3U}},
    },
    {
        .code = "%", .expected = "%", .params = {},
    },
    {
        .code = R"(%x%
        %gg% %f% %t%
        %averylongidentifier%%
        mov edx, ecx
        %x% %f%
)", .expected = R"(%%
        %gg% 555555555 eax ax ah al
        abc%
        mov edx, ecx
        %% 555555555
)", .params = {{"x", "%%"}, {"gg", "%gg%"}, {"f", 555555555U}, {"t", "eax ax ah al"}, {"averylongidentifier", "abc"}},
    }
};

struct CompileAsmTest
{
    std::string code, expected;
    std::optional<CodeReplacementArgs> args;
};

std::vector<CompileAsmTest> compileAsmTests =
{
    {
        .code = R"(
        nop
        shl eax, 1
        nop
        )", .expected = "\x90\xD1\xE0\x90", .args = {std::nullopt}
    },
    {
        .code = R"(
        cmp ebp, edx
        add esp, 5
        aaa
        )", .expected = "\x39\xD5\x83\xC4\x05\x37", .args = {std::nullopt}
    },
    {
        .code = R"(
        add %s%, 4
        add ebx, 4
        add ecx, %num%
        jmp short @%l%
        test dx, ax
        @label:
        popcnt eax, ebx
        )", .expected = "\x83\xC0\x04\x83\xC3\x04\x83\xC1\x05\xEB\x03\x66\x85\xC2\xF3\x0F\xB8\xC3",
        .args = {{{"s", "eax"}, {"l", "label"}, {"num", 5}}}
    },
};

/*
    uint32_t eflags;
    uint32_t edi;
    uint32_t esi;
    uint32_t ebp;
    uint32_t esp; // change this to change return address from hook proc
    uint32_t edx;
    uint32_t ecx;
    uint32_t ebx;
    uint32_t eax;
*/
static dword_t regs[9]; // set by testing function
static int checkRegistersFailReasonId;
static dword_t eaxBackup; // needed for checking eflags
static dword_t returnJump; // to allow having custom esp value, while also correctly "returning" to caller
static __declspec(naked) int __stdcall checkRegisters()
{
    _asm
    {
        mov checkRegistersFailReasonId, 1
        mov eaxBackup, eax
        pushfd
        pop eax
        cmp eax, dword ptr [regs]
        // do it here to not pollute eflags and have one free register to not have "memory-to-memory move" problem
        mov eax, dword ptr[esp]
        mov returnJump, eax
        jne $exitFail
        mov eax, eaxBackup

        inc checkRegistersFailReasonId
        cmp edi, dword ptr[regs + 4 * 1] // "cmp edi, regs[1]" would get translated into "cmp edi, dword ptr [regs + 1]" (1 byte, not 4)
        jne $exitFail

        inc checkRegistersFailReasonId
        cmp esi, dword ptr[regs + 4 * 2]
        jne $exitFail

        inc checkRegistersFailReasonId
        cmp ebp, dword ptr[regs + 4 * 3]
        jne $exitFail

        inc checkRegistersFailReasonId
        //cmp esp, dword ptr [regs + 4 * 4]
        //jne $exitFail

        inc checkRegistersFailReasonId
        cmp edx, dword ptr[regs + 4 * 5]
        jne $exitFail

        inc checkRegistersFailReasonId
        cmp ecx, dword ptr[regs + 4 * 6]
        jne $exitFail

        inc checkRegistersFailReasonId
        cmp ebx, dword ptr[regs + 4 * 7]
        jne $exitFail

        inc checkRegistersFailReasonId
        cmp eax, dword ptr[regs + 4 * 8]
        jne $exitFail

        mov checkRegistersFailReasonId, 0
        jmp $setValues

        $exitFail:
        ret

        $setValues :
        add esp, 4 // pop return address
        push 0x200203 // carefully chosen, see c++ part
            popfd
            mov edi, 0
            mov esi, 0x32221
            mov ebp, 0x40040404
            // here we can test esp, due to ret changed to jump and restoring correct esp asap inside caller
            mov esp, 0x55555555
            mov edx, 0x1234
            mov ecx, 0x47287324
            mov ebx, 0x10000001
        mov eax, 0x33333
        jmp returnJump
    }//0x200203U, 0U, 0x32221U, 0x40040404U, 0x55555555U, 0x1234U, 0x47287324U, 0x10000001U, 0x33333U

}

namespace
{
    namespace callTests
    {
        static int callFailReasonId;
        static __declspec(naked) char __stdcall callTest1(int f, char c, bool b, const char* str)
        {
            static const char* cmpStr = "abbde";
            static const int len = strlen(cmpStr);
            _asm
            {
                mov callFailReasonId, 1
                cmp dword ptr[esp + 4], 0x12345678 // int f
                jne $fail
                mov callFailReasonId, 2
                cmp byte ptr[esp + 8], 0x12 // char c
                jne $fail
                mov callFailReasonId, 3
                cmp byte ptr[esp + 12], 0x0 // bool b
                jne $fail
                mov callFailReasonId, 4

                // compare the string pointed to by str with "abbde"
                push edi
                push esi

                mov esi, dword ptr[esp + 16 + 8] // const char* str, 8 added because of pushed registers
                mov edi, cmpStr
                mov ecx, len
                repe cmpsb
                test ecx, ecx
                pop esi
                pop edi
                jne $fail // not all characters equal

                mov callFailReasonId, 0
                jmp $exit

                //
                $fail:
                mov al, 0
                    $exit:
                    ret 4*4
            }
        }

        static __declspec(naked) int __stdcall callTest2(int a, int b, int c, int d, int e, int f, int g, int h, int i, int j)
        {
            _asm
            {
                mov eax, dword ptr[esp + 4]
                add eax, dword ptr[esp + 8]
                add eax, dword ptr[esp + 12]
                add eax, dword ptr[esp + 16]
                add eax, dword ptr[esp + 20]
                add eax, dword ptr[esp + 24]
                add eax, dword ptr[esp + 28]
                add eax, dword ptr[esp + 32]
                add eax, dword ptr[esp + 36]
                add eax, dword ptr[esp + 40]
                ret 10 * 4
            }
        }

        static __declspec(naked) void __stdcall __callTest3(bool b, bool bb, dword_t d)
        {
            _asm
            {
                mov callFailReasonId, 1
                test cl, cl
                jne $fail

                mov callFailReasonId, 2
                test byte ptr [esp + 4], 0
                jne $fail

                mov callFailReasonId, 3
                cmp dword ptr [esp + 8], 0x33994499
                jne $fail

                mov callFailReasonId, 0

                $fail:
                ret 2*4
            }
        }

        // cast __callTest3 to function which uses thiscall calling convention
        // function pointer cast hack is needed, because you can't directly declare __thiscall function in c++ code (at least in MSVC)
        typedef void(__thiscall* __callTest3_thiscall)(bool b, bool bb, dword_t d);
        static const __callTest3_thiscall callTest3 = (__callTest3_thiscall)__callTest3;

        // design a function using __fastcall calling convention, which tests whether parameters passed to it have certain values, using callTest3 as a reference
        static __declspec(naked) void __fastcall callTest4(bool b, byte_t needsToBe5, dword_t d)
        {
            _asm
            {
                mov callFailReasonId, 1
                test cl, cl
                jne $fail

                mov callFailReasonId, 2
                cmp dl, 5
                jne $fail

                mov callFailReasonId, 3
                cmp dword ptr [esp + 4], 0x33994499
                jne $fail

                mov callFailReasonId, 0

                $fail:
                ret 1 * 4
            }
        }

        static __declspec(naked) void __cdecl callTest5(void* p, float f, sdword_t sdw)
        {
            static const float cmpf = 3.12f;
            static const int divVal = 5;
            __asm
            {
                mov callFailReasonId, 1
                cmp dword ptr [esp + 4], 0x12345678
                jne $fail

                mov callFailReasonId, 2
                // check if loaded floating-point value is greater than 3.12
                fld cmpf
                fld dword ptr [esp + 8]
                fcomip st(0), st(1)
                fnstsw ax
                // test ax, ax // this is not correct here, because "fcomip" sets flags by itself, version which wouldn't set them is "fcomp"
                // any of CF, PF, ZF must not be set
                jz $fail
                jp $fail
                jc $fail
                mov callFailReasonId, 3
                // check if sdw divided by divVal is greater than or equal to 8
                mov eax, dword ptr [esp + 12]
                cdq
                idiv divVal
                cmp eax, 8
                jl $fail


                mov callFailReasonId, 0

                $fail:
                ret
            }
        }
    }
}

std::vector<wxString> HookTests::testMiscFunctions()
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
            const uint32_t fullFoundOffset = findCode(fullTestOffset, test.code.c_str(), test.code.size());
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

    // formatAsmCode
    int i = 0;
    for (const FormatAsmCodeTest& test : formatAsmCodeTests)
    {
        auto result = formatAsmCode(test.code, test.params);
        myassertf(result == test.expected, "[format asm compiled] test #%d failed (actual result: %s)", i, result);
        ++i;
    }

    // compileAsm
    i = 0;
    for (const auto& [compiled, expected, args] : compileAsmTests)
    {
        std::string codeNew = compiled;
        if (args)
        {
            codeNew = formatAsmCode(compiled, args.value());
        }
        std::string_view compiled = compileAsm(codeNew);
        if (compiled.size() != expected.size())
        {
            myassertf(false, "[compile asm, test #%d] binary compiled sizes (compiled: %d, expected: %d) do not match", i, compiled.size(), expected.size());
        }
        else
        {
            myassertf(memcmp(compiled.data(), expected.data(), compiled.size()) == 0,
                "[compile asm, test #%d] generated code is not the same (actual: '%s', expected: '%s')",
                i, codeToSemiReadableString((std::string)compiled), codeToSemiReadableString(expected)
            );
        }
        ++i;
    }

    // callMemoryAddress
    using namespace callTests;
    // check that after callTest1(...parameters defined in asm code above...), callFailReasonId is equal to 0
    callMemoryAddress(callTest1, 0, 0x12345678, 0x12, false, "abbde");
    myassertf(callFailReasonId == 0, "[callMemoryAddress] callTest1 caused error code %d", callFailReasonId);
    // callTest2 must return 77
    int ret = callMemoryAddress<int>(callTest2, 0, 2, 4, 6, 8, 1, 3, 5, 7, 22, 19);
    myassertf(ret == 77, "[callMemoryAddress] callTest2 returned %d, expected 77", ret);
    // check that after callTest3(...parameters defined in asm code above...), callFailReasonId is equal to 0
    callMemoryAddress(callTest3, 1, false, false, 0x33994499);
    myassertf(callFailReasonId == 0, "[callMemoryAddress] callTest3 caused error code %d", callFailReasonId);
    // do like above for callTest4
    callMemoryAddress(callTest4, 2, false, 5, 0x33994499);
    myassertf(callFailReasonId == 0, "[callMemoryAddress] callTest4 caused error code %d", callFailReasonId);
    // do like above for callTest5
    callMemoryAddress(callTest5, -1, (void*)0x12345678, 3.13f, 40);
    myassertf(callFailReasonId == 0, "[callMemoryAddress] callTest5 caused error code %d", callFailReasonId);

    // if there's no crash until this point, this means calling convention behavior is correct

    // callMemoryAddressRegisters
    HookData testData;
    // EFLAGS value carefully chosen to:
    // 1) not enable trap flag, which is annoying
    // 2) not cause processor to drop some bits (reserved?), thus breaking the comparison
    static const dword_t testValues[9] = { 0x200A12, 0x54433221U, 0U, 0x48200000U, 0x33333333U, 0x19283746U, 0x44445555U,
        0x11122233U, 0x10011001U };
    static const dword_t expectValues[9] = { 0x200203U, 0U, 0x32221U, 0x40040404U, 0x55555555U, 0x1234U, 0x47287324U, 0x10000001U, 0x33333U };
    /*
    push 0x21212121
            popfd
            mov edi, 0
            mov esi, 0x32221
            mov ebp, 0x40040404
            mov esp, 0x55555555
            mov edx, 0x1234
            mov ecx, 0x47287324
            mov ebx, 0x10000001
        mov eax, 0x33333*/
    memcpy(&testData, testValues, 9 * 4);
    memcpy(regs, testValues, 9 * 4);
    HookData retData = callMemoryAddressRegisters(checkRegisters, 0, testData);
    if (checkRegistersFailReasonId)
    {
        myassertf(false, "[callMemoryAddressRegisters] received fail reason id #", checkRegistersFailReasonId);
    }
    std::vector<int> failPositions;
    for (int i = 0; i < 9; ++i)
    {
        if (dword(reinterpret_cast<char*>(&retData) + i * 4) != expectValues[i])
        {
            failPositions.push_back(i);
        }
    }
    if (!failPositions.empty())
    {
        std::vector<std::string> v;
        std::ranges::transform(failPositions, std::back_inserter(v), [](int i) { return std::to_string(i); });
        myassertf(false, "[callMemoryAddressRegisters] expected register values differ (indexes of fails: %s)", stringConcat(v, ", "));
    }
    
    return myasserter.errors;
}

std::vector<wxString> HookTests::run()
{
    return mergeVectors({ testHookPlacingAndSize(), testMiscFunctions(), testBasicHookFunctionalityAndHookManager(), testAdvancedHookFunctionality(), testAsmHookFunctions()});
}