#include "pch.h"
#include "HookTests.h"
#include "LowLevel.h"

#define INSTANTIATE_TEMPLATES_SINGLE_GAME(game, ret, identifier) template ret identifier<mm##game::Player, mm##game::Game>()

#define INSTANTIATE_TEMPLATES_MM_GAMES(ret, identifier) \
INSTANTIATE_TEMPLATES_SINGLE_GAME(6, ret, identifier); \
INSTANTIATE_TEMPLATES_SINGLE_GAME(7, ret, identifier); \
INSTANTIATE_TEMPLATES_SINGLE_GAME(8, ret, identifier)

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
static std::vector<wxString> HookTests::testHookFunctionAndHookManager()
{
    Asserter myasserter;
    static std::mt19937 gen(std::random_device{}());
    static std::uniform_int_distribution genEsi(100, 10000);
    std::vector<uint8_t> copy((uint8_t*)expectRegisterValues, (uint8_t*)expectRegisterValues + 0x140);

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
                d->edi += std::uniform_int_distribution(20 - r, 20 - r + 7)(gen);
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

INSTANTIATE_TEMPLATES_MM_GAMES(std::vector<wxString>, HookTests::testHookFunctionAndHookManager);

template<typename Player, typename Game>
static std::vector<wxString>
HookTests::testMiscFunctions()
{
    // getinstructionsize, copyCode
    
    return std::vector<wxString>();
}

INSTANTIATE_TEMPLATES_MM_GAMES(std::vector<wxString>, HookTests::testMiscFunctions);

/*
template std::vector<wxString> HookTests::testHookFunctionAndHookManager<mm6::Player, mm6::Game>();
template std::vector<wxString> HookTests::testHookFunctionAndHookManager<mm7::Player, mm7::Game>();
template std::vector<wxString> HookTests::testHookFunctionAndHookManager<mm8::Player, mm8::Game>();*/

template<typename Player, typename Game>
static std::vector<wxString> HookTests::run()
{
    return mergeVectors({ testHookPlacingAndSize<Player, Game>(), testHookFunctionAndHookManager<Player, Game>() });
}

template std::vector<wxString> HookTests::run<mm6::Player, mm6::Game>();
template std::vector<wxString> HookTests::run<mm7::Player, mm7::Game>();
template std::vector<wxString> HookTests::run<mm8::Player, mm8::Game>();