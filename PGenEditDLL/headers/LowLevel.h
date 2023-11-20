#pragma once
#include "main.h"
#include "Zydis/Zydis.h"
#include "Utility.h"

// REMAINING TO IMITATE MMEXT
// - assembler (fasm? it's already loaded)
// - integration with lua
// 

// credits to Tomsod for his elemental mod sources (and of course to Grayface), they made it much easier
// for me to understand such low level stuff
// many functions taken/adapted from Tomsod's elemental mod

using ByteVector = std::vector<uint8_t>;

#pragma pack(push, 1)
struct HookData
{
    union
    {
        uint32_t eflags;
        uint16_t flags;
        struct
        {
            bool CF : 1; // carry
            SKIPBITS(1);
            bool PF : 1; // parity
            SKIPBITS(3);
            bool ZF : 1; // zero
            bool SF : 1; // sign
            bool TF : 1; // trap
            bool IF : 1; // interrupt
            bool DF : 1; // direction
            bool OF : 1; // overflow
        };
    };
    union
    {
        uint32_t edi;
        uint16_t di;
    };
    union
    {
        uint32_t esi;
        uint16_t si;
    };
    union
    {
        uint32_t ebp;
        uint16_t bp;
    };
    union
    {
        uint32_t esp; // change this to change return address from hook proc
        uint16_t sp;
    };
    union
    {
        uint32_t edx;
        uint16_t dx;
        struct
        {
            uint8_t dl;
            uint8_t dh;
        };
    };
    union
    {
        uint32_t ecx;
        uint16_t cx;
        struct
        {
            uint8_t cl;
            uint8_t ch;
        };
    };
    union
    {
        uint32_t ebx;
        uint16_t bx;
        struct
        {
            uint8_t bl;
            uint8_t bh;
        };
    };
    union
    {
        uint32_t eax;
        uint16_t ax;
        struct
        {
            uint8_t al;
            uint8_t ah;
        };
    };

    void push(uint32_t val);
    void ret(int stackNum);

    // forward declaration, because this function depends on PackParams definition, while PackParams depends on HookData definition
    template<int cc, typename... Args>
    void getParams(std::tuple<Args...>& output);
    // a version, which returns tuple instead of modifying existing one
    template<int cc, typename... Args>
    std::tuple<Args...> getParams();
};

// retrieves parameters from HookData object, casts them to appropriate types and stores result in tuple
template<int index, int cc, typename... Args>
struct PackParams
{
    static constexpr int ArgCount = (int)sizeof...(Args);
    static constexpr int StackNum = std::max(0, ArgCount - std::max(cc, 0));
    static constexpr int RegNum = ArgCount - StackNum;
    static constexpr int StackIndex = index - RegNum;
    using ParamType = std::tuple_element_t<index, std::tuple<Args...>>;
    static void pack(std::tuple<Args...>& tup, HookData* d)
    {
        if constexpr (StackIndex < 0) // register parameter
        {
            std::get<index>(tup) = (ParamType)(index == 0 ? d->ecx : d->edx);
        }
        else
        {
            std::get<index>(tup) = (ParamType)dword(d->esp + 4 + StackIndex * 4);
        }
        if constexpr (index < ArgCount - 1) // not last one
        {
            PackParams<index + 1, cc, Args...>::pack(tup, d);
        }
    }
};

template<int cc, typename... Args>
void HookData::getParams(std::tuple<Args...>& output)
{
    static_assert(cc >= -1 && cc <= 2, "Invalid calling convention");
    if constexpr (sizeof...(Args) > 0)
    {
        PackParams<0, cc, Args...>::pack(output, this);
    }
}

template<int cc, typename... Args>
std::tuple<Args...> HookData::getParams()
{
    std::tuple<Args...> ret;
    getParams<cc, Args...>(ret);
    return ret;
}
#pragma pack(pop)

typedef int(__stdcall* HookFuncPtr)(HookData*);
typedef std::function<int(HookData*)> HookFunc; // any function callable with HookData parameter and returning int is hook function

enum HookReturnCode
{
    HOOK_RETURN_SUCCESS,
    HOOK_RETURN_FAIL,
    HOOK_RETURN_AUTOHOOK_NO_PUSH
};

struct HookRestoreData
{
    std::vector<uint8_t> bytes;
    void* extraData = nullptr;
};

extern std::map<uint32_t, HookRestoreData> hookRestoreDataMap;

// BASE FUNCTIONS

int getInstructionSize(void* addr);
int getInstructionSize(uint32_t addr);

template<typename T>
concept Address = std::is_same_v<T, uint32_t> || std::is_same_v<T, void*>;

// returns address of next instruction after max(size, minSize) bytes
// minSize parameter intended to allow correct behavior for call hooks (min 5) and something like erase code (min 1)
int getRealHookSize(uint32_t addr, uint32_t size, uint32_t minSize = 5);
void checkOverlap(uint32_t address, uint32_t size = 5);
void storeBytes(std::vector<uint8_t>* storeAt, uint32_t addr, uint32_t size);

uint32_t findCode(uint32_t addr, const char* code, int len = -1);
uint32_t findCode(void* addr, const char* code, int len = -1);

// finds nearest call to address findAddr beginning at beginAddr
// if address is 0, finds any nearest call
template<typename Address, typename Address2 = uint32_t>
uint32_t findCall(Address beginAddr, Address2 findAddr = 0)
{
    // TODO: reinterpret cast + constexpr
    uint32_t addr = (uint32_t)beginAddr, find = (uint32_t)findAddr;
    ZydisDisassembledInstruction instr;
    while (true)
    {
        ZyanStatus status = ZydisDisassembleIntel(ZYDIS_MACHINE_MODE_LEGACY_32, addr, (void*)addr, 20, &instr);
        if (!ZYAN_SUCCESS(status))
        {
            ++addr;
            continue;
        }
        if (instr.info.meta.branch_type == ZYDIS_BRANCH_TYPE_NEAR && instr.info.meta.category == ZYDIS_CATEGORY_CALL)
        {
            uint32_t dest = (int64_t)addr + (int64_t)instr.info.length + (int64_t)instr.info.raw.imm[0].value.s;
            if (!findAddr || dest == find)
            {
                return addr;
            }
        }
        addr += instr.info.length;
    }
    return 0;
}

// get or set either byte/word/dword/qword (unsigned 1/2/4/8 byte integer)
#define byte(addr) (*(uint8_t*)(addr))
#define word(addr) (*(uint16_t*)(addr))
#define dword(addr) (*(uint32_t*)(addr))
#define qword(addr) (*(uint64_t*)(addr))

// signed
#define sbyte(addr) (*(int8_t*)(addr))
#define sword(addr) (*(int16_t*)(addr))
#define sdword(addr) (*(int32_t*)(addr))
#define sqword(addr) (*(int64_t*)(addr))

uint32_t relJumpCallTarget(uint32_t addr);

int bitwiseUnsignedToInt(uint32_t val);
template<std::integral T>
T byteswap(const T& val)
{
    T ret;
    char* retP = (char*)&ret, * valP = (const char*)&val;
    for (int i = 0; i < sizeof(T); ++i)
    {
        byte(retP + sizeof(T) - i - 1) = byte(valP + i);
    }
    return ret;
}

// sets a call/jump hook (5-byte instruction) at given address transferring
// control into given func, hook size can be given or omitted (5 assumed)
void hookCallRaw(uint32_t addr, void* func, std::vector<uint8_t>* storeAt, uint32_t size = 5);
void unhookCallRaw(uint32_t addr, std::vector<uint8_t>& restoreData);

void hookJump(uint32_t addr, void* func, std::vector<uint8_t>* storeAt, uint32_t size = 5);
void unhookJump(uint32_t addr, std::vector<uint8_t>& restoreData);

// mmext-like call hook (dispatch, HookData param etc.)
void hookCall(uint32_t addr, HookFunc func, std::vector<uint8_t>* storeAt, uint32_t size = 5);
void unhookCall(uint32_t addr, std::vector<uint8_t>& restoreData);

// mmext-like autohook
uint32_t autohookBefore(uint32_t addr, HookFunc func, std::vector<uint8_t>* storeAt, uint32_t size = 5);
uint32_t autohookAfter(uint32_t addr, HookFunc func, std::vector<uint8_t>* storeAt, uint32_t size = 5);
// unhook, also sets passed extra data pointer to nullptr
void unhookAutohook(uint32_t addr, std::vector<uint8_t>& restoreData, void*& allocatedCode);
/*
struct f
{
    static int(*test)(bool, char*);
};
void t()
{
f::test = reinterpret_cast<decltype(f::test)>(0x45458943);
}
}*/

// data patching functions which unprotect before/protect after (essential for patching code etc.)

template<typename valType>
void genericPatch(uint32_t addr, valType val, std::vector<uint8_t>* storeAt)
{
    storeBytes(storeAt, addr, sizeof(valType));
    DWORD tmp;
    VirtualProtect((void*)addr, sizeof(valType), PAGE_EXECUTE_READWRITE, &tmp);
    *(valType*)addr = val;
    VirtualProtect((void*)addr, sizeof(valType), tmp, &tmp);
}

void patchByte(uint32_t addr, uint8_t val, std::vector<uint8_t>* storeAt);
void patchWord(uint32_t addr, uint16_t val, std::vector<uint8_t>* storeAt);
void patchDword(uint32_t addr, uint32_t val, std::vector<uint8_t>* storeAt);
void patchQword(uint32_t addr, uint64_t val, std::vector<uint8_t>* storeAt);

void patchSByte(uint32_t addr, int8_t val, std::vector<uint8_t>* storeAt);
void patchSWord(uint32_t addr, int16_t val, std::vector<uint8_t>* storeAt);
void patchSDword(uint32_t addr, int32_t val, std::vector<uint8_t>* storeAt);
void patchSQword(uint32_t addr, int64_t val, std::vector<uint8_t>* storeAt);

// erases code (NOPs), writing jump forward if number of bytes erased is high enough
void eraseCode(uint32_t addr, uint32_t size, std::vector<uint8_t>* storeAt);

// patches sequence of bytes (unprotect/protect)
void patchBytes(uint32_t addr, const void* bytes, uint32_t size, std::vector<uint8_t>* storeAt = nullptr, bool useNops = false);
void patchBytes(uint32_t addr, const ByteVector& bytes, std::vector<uint8_t>* storeAt = nullptr, bool useNops = false);

extern SYSTEM_INFO systemInfo;

// works like in MMExt
std::string readStringFromMemory(const void* buf, uint32_t maxLength = 0, bool readNull = false);

// allocates memory for code
uint32_t codeMemoryAlloc(uint32_t size);
// frees memory allocated with codeMemoryAlloc
void codeMemoryFree(void* addr);

// unallocates all memory allocated for code
void codeMemoryFullFree();

// copies code, fixing calls and jumps
uint32_t copyCode(uint32_t source, uint32_t size, bool writeJumpBack = true, uint32_t dest = 0, uint32_t canJumpAfterCodeBytes = 0);

using CodeReplacementArg = std::variant<uint32_t, int32_t, std::string, void*>;
using CodeReplacementArgs = std::unordered_map<std::string, CodeReplacementArg>;

// need own function, because std::format and wxString::Format use position-based arguments, not name-based
std::string formatAsmCode(const std::string& code, const CodeReplacementArgs& replacements);

// replaces instructions, jumping out if needed
void* bytecodePatch(uint32_t addr, std::string_view bytecode, std::vector<uint8_t>* storeAt, int size, bool writeJumpBack = true);
void unhookBytecodePatch(uint32_t addr, const std::vector<uint8_t>& restoreData, void*& copiedCode);

// new code is called before overwritten code
void* bytecodeHookBefore(uint32_t addr, std::string_view code, std::vector<uint8_t>* storeAt, int size);

// new code is called after overwritten code
void* bytecodeHookAfter(uint32_t addr, std::string_view code, std::vector<uint8_t>* storeAt, int size);
void unhookBytecodeHook(uint32_t addr, const std::vector<uint8_t>& restoreData, void*& copiedCode);

// TODO: versions of asm functions taking a function to generate code/copy it (mainly support different game versions)
// new code is called before overwritten code
void* asmhookBefore(uint32_t addr, const std::string& code, std::vector<uint8_t>* storeAt, int size = 5);
// this version formats code
void* asmhookBefore(uint32_t addr, const std::string& code, const CodeReplacementArgs& args, std::vector<uint8_t>* storeAt, int size = 5);

// new code is called after overwritten code
void* asmhookAfter(uint32_t addr, const std::string& code, std::vector<uint8_t>* storeAt, int size = 5);
// this version formats code
void* asmhookAfter(uint32_t addr, const std::string& code, const CodeReplacementArgs& args, std::vector<uint8_t>* storeAt, int size = 5);

void unhookAsmhook(uint32_t addr, const std::vector<uint8_t>& restoreData, void*& copiedCode);

// replaces instructions, jumping out if needed
void* asmpatch(uint32_t addr, const std::string& code, std::vector<uint8_t>* storeAt, int size, bool writeJumpBack = true);
// this version formats code
void* asmpatch(uint32_t addr, const std::string& code, const CodeReplacementArgs& args, std::vector<uint8_t>* storeAt, int size, bool writeJumpBack = true);

// creates asm bytecode block (without "ret" instruction)
std::string_view bytecodeproc(const std::string& bytecode);

// creates asm code block (without "ret" instruction)
std::string_view asmproc(const std::string& code);
// this version formats code
std::string_view asmproc(const std::string& code, const CodeReplacementArgs& args);

void unhookAsmpatch(uint32_t addr, const std::vector<uint8_t>& restoreData, void*& copiedCode);

/*
template<typename T, typename std::enable_if_t<>
struct classToAddress
{

};*/

template<typename T>
auto getAddress(T&& t)
{
    if constexpr (std::is_class_v<T>)
    {
        return &t;
    }
    else
    {
        return t;
    }
}

template<typename ReturnType = void, typename Address, typename... Args>
ReturnType callMemoryAddress(Address address, int registerParamsNum = 0, Args... args) // NO rvalue reference, because it passes arguments by address
{
    wxASSERT_MSG(registerParamsNum >= -1 && registerParamsNum <= 2, "Invalid number of register parameters");
    // fold expression??? kinda weird syntax
    static_assert(((std::is_scalar_v<Args>) && ...) && (std::is_scalar_v<ReturnType> || std::is_void_v<ReturnType>), "Argument types or return type are invalid");
    void* ptr;
    if constexpr (std::is_pointer_v<Address>)
    {
        ptr = (void*)address;
    }
    else
    {
        static_assert(std::is_integral_v<Address>, "Neither pointer nor integer type passed to callMemoryAddress");
        ptr = (void*)address;
    }
    if (registerParamsNum == -1)
    {
        typedef ReturnType(__cdecl* Function)(Args...);
        //typedef ReturnType(__cdecl* Function)(decltype(getAddress(replacements))...);
        return reinterpret_cast<Function>(ptr)(args...);
    }
    else if (registerParamsNum == 0)
    {
        typedef ReturnType(__stdcall* Function)(Args...);
        return reinterpret_cast<Function>(ptr)(args...);
    }
    else if (registerParamsNum == 1)
    {
        typedef ReturnType(__thiscall* Function)(Args...);
        return reinterpret_cast<Function>(ptr)(args...);
    }
    else
    {
        typedef ReturnType(__fastcall* Function)(Args...);
        return reinterpret_cast<Function>(ptr)(args...);
    }
}

#pragma warning(push)
#pragma warning(disable: 4731) // frame pointer register 'ebp' modified by inline assembly code

// another version of "call arbitrary address" function
// this one uses registers from provided HookData for call (except esp [TODO: push before changing registers and do jump instead of call, as in hook tests?]),
// and returns HookData which contains the registers just after called function returns
static dword_t callRegisters[9], callAddress, callOldEsp, callEspAfterCall; // registers, address, old esp, esp after call
//static dword_t* callRegisters = callRegisters2; // for some reason this is needed, "mov edi, callRegisters2" would result in edi == 0
// using this for registers, because compiler probably would use ebp-based addressing for accessing retData, which wouldn't work
template<typename Address, typename... Args>
HookData callMemoryAddressRegisters(Address address, int registerParamsNum, const HookData& useData, Args... args)
{
    HookData retData;
    constexpr int arg = sizeof...(Args);
    std::vector<dword_t> argsVec{args...};
    dword_t* vecDwords = argsVec.data();
    _asm
    {
        pushad
        pushfd
        push ebp // to allow using ebp-based params later

        // copy registers to use
        mov esi, useData // we want to use value as pointer -> can't use "lea", or we would get pointer to a pointer to value
        lea edi, callRegisters
        mov ecx, 9
        rep movsd
        mov eax, address
        mov callAddress, eax
        // for now ignore register params num

        // backup stack and registers
        // move register values
        // call static address
        // push registers in order
        // memcpy
        // cleanup

        mov callOldEsp, esp
        // push args
        xor esi, esi
        mov eax, vecDwords
        mov ecx, arg
        test ecx, ecx
        je $pushed
        $push:
        push dword ptr [eax + esi * 4]
        inc esi
            cmp esi, ecx
        jb $push
        $pushed:

        push dword ptr[callRegisters]
        popfd
        mov edi, dword ptr[callRegisters + 4]
        mov esi, dword ptr[callRegisters + 8]
        mov ebp, dword ptr[callRegisters + 12]
        //mov esp, dword ptr[callRegisters + 16]
        mov edx, dword ptr[callRegisters + 20]
        mov ecx, dword ptr[callRegisters + 24]
        mov ebx, dword ptr[callRegisters + 28]
        mov eax, dword ptr[callRegisters + 32]
        call callAddress
        mov callEspAfterCall, esp
        mov esp, callOldEsp
        // push in inverse order and start from stack top going towards increasing addresses
        // starting from first pushed arg wouldn't work, would be going inverse of where params are in memory,
        // and we can't toggle direction flag, because otherwise edi would decrease too;
        // normal order and starting from stack top would not require flag, but would move memory in inverse order,
        // while normal order and starting from first arg would require toggling the flag too
        push eax
            mov eax, callEspAfterCall
        push ebx
        push ecx
        push edx
        push eax // esp
        push ebp
        push esi
        push edi
        pushfd

        mov ebp, dword ptr [esp + 9*4] // restore to allow to take address of retData

        mov esi, esp
        lea edi, retData
        mov ecx, 9
        rep movsd
        
        add esp, 10*4

        popfd
        popad
    }
    return retData;
}

#pragma warning(pop)

// fills out hookData struct with current register values (at the moment of this function call)
static void __declspec(naked) __stdcall fillOutHookData(HookData* d)
{
    _asm
    {
        push eax
        push ebx
        push ecx
        push edx
        lea eax, dword ptr [esp + 6 * 4]
        push eax
        push ebp
        push esi
        push edi
        pushfd

        mov esi, esp
        mov edi, dword ptr [esp + 10 * 4]
        mov ecx, 9
        rep movsd
        mov edi, dword ptr [esp + 4]
        mov esi, dword ptr [esp + 8]
        add esp, 9 * 4
        ret 4
    }
}

// trick to allow asm jump from different function into this name-mangled one
static void(__stdcall* myFuncPtr)(HookData*) = fillOutHookData;

static void __declspec(naked) __stdcall fillOutHookData(HookData& d)
{
    _asm
    {
        jmp myFuncPtr
    }
}

// type of object representing replaced function call
template<typename ReturnType, typename... Args>
using CallableFunctionHookOrigFunc = typename std::function<ReturnType(Args...)>;

// type representing hook function
template<typename ReturnType, typename... Args>
using CallableFunctionHookFunc = typename std::function<uint32_t(HookData* d, CallableFunctionHookOrigFunc<ReturnType, Args...> func, Args... args)>;

// template<int cc, typename Arg, int... Indexes, int i>
// auto getParam(HookData* d)
// {
//     constexpr int regNum = std::clamp(i, 0, 2);
//     constexpr int stackIndex = i - regNum;
//     if constexpr (stackIndex < 0)
//     {
//         return static_cast<Arg>(i == 0 ? d->ecx : d->edx);
//     }
//     else
//     {
//         return static_cast<Arg>(dword(d->esp + 4 + stackIndex * 4));
//     }
// }

template<typename ReturnType, int cc, typename... Args>
uint32_t callableHookCommon(uint32_t addr, uint32_t stackNum, CallableFunctionHookFunc<ReturnType, Args...> func, std::vector<uint8_t>* storeAt, uint32_t size, uint32_t code, bool hookfunction)
{
    using OrigType = CallableFunctionHookOrigFunc<ReturnType, Args...>;
    OrigType def = [=](Args... args) -> ReturnType { // CRASH HERE
        return callMemoryAddress<ReturnType>(code, cc, args...);
    };
    size = getRealHookSize(addr, size);
    hookCall(addr, [=](HookData* d) -> uint32_t {
        if (hookfunction)
        {
            d->esp += 4; // pop return address from hookCall (esp now points to return address to the code that called hooked function)
            // note that if it's not hookfunction, but replaceCall, no adjustment is needed, because function isn't entered by default code
        }
        std::tuple<HookData*, OrigType> basicParams;
        std::get<0>(basicParams) = d;
        std::get<1>(basicParams) = def;
        std::tuple<HookData*, OrigType, Args...> fullArgs;
        if constexpr (sizeof...(Args) > 0)
        {
            std::tuple<Args...> args;
            // pack all arguments into tuple with conversion: optional from ecx, optional from edx, then all from stack
            PackParams<0, cc, Args...>::pack(args, d);
            fullArgs = std::tuple_cat(basicParams, args);
        }
        else
        {
            fullArgs = basicParams;
        }
        // int result = bitwiseUnsignedToInt(std::apply(func, basicParams));
        uint32_t result = std::apply(func, fullArgs);
        //constexpr int i = 0;
        //std::integer_sequence<int, sizeof...(Args)> seq = std::make_integer_sequence<int, sizeof...(Args)>;
        //uint32_t result1 = func(d, def, getParam<cc, Args, seq>(d)...);
        //std::inde
        // return from function (pop basicParams and move return address)
        d->ret(stackNum);
        d->eax = result;
        return HOOK_RETURN_SUCCESS;
    }, storeAt, size);
    return HOOK_RETURN_SUCCESS;
}

template<typename ReturnType, int cc, typename... Args>
void hookReplaceCall(uint32_t addr, uint32_t stackNum, CallableFunctionHookFunc<ReturnType, Args...> func, std::vector<uint8_t>* storeAt = nullptr, uint32_t size = 5)
{
    static_assert(cc >= -1 && cc <= 2, "Invalid calling convention");
    static_assert(((std::is_standard_layout_v<Args>) && ...) && (std::is_standard_layout_v<ReturnType> || std::is_void_v<ReturnType>), "Arguments are non-POD");
	wxASSERT_MSG(byte(addr) == 0xE8, wxString::Format("Instruction at 0x%X is not call instruction", addr));
    size = getRealHookSize(addr, size);
    checkOverlap(addr, size);
    uint32_t dest = addr + sdword(addr + 1) + 5;
    callableHookCommon<ReturnType, cc, Args...>(addr, stackNum, func, storeAt, size, dest, false);
}

template<typename ReturnType, int cc, typename... Args>
uint32_t hookFunction(uint32_t addr, uint32_t stackNum, CallableFunctionHookFunc<ReturnType, Args...> func, std::vector<uint8_t>* storeAt = nullptr, uint32_t size = 5)
{
    static_assert(cc >= -1 && cc <= 2, "Invalid calling convention");
    static_assert(((std::is_standard_layout_v<Args>) && ...) && (std::is_standard_layout_v<ReturnType> || std::is_void_v<ReturnType>), "Arguments are non-POD");
    size = getRealHookSize(addr, size);
    checkOverlap(addr, size);
    uint32_t dest = copyCode(addr, size, true, 0, 1);
    callableHookCommon<ReturnType, cc, Args...>(addr, stackNum, func, storeAt, size, dest, true);
    return dest;
}

void unhookReplaceCall(uint32_t addr, std::vector<uint8_t>& restoreData);
void unhookHookFunction(uint32_t addr, std::vector<uint8_t>& restoreData, void* copiedCode);

// HOOK SYSTEM

enum HookElementType
{
    HOOK_ELEM_TYPE_DISABLED, // for example for hooks which are only in mm7+, so in mm6 they need not be used
	HOOK_ELEM_TYPE_CALL_RAW, // simple call hook
	HOOK_ELEM_TYPE_CALL, // mmext-like call hook
	HOOK_ELEM_TYPE_JUMP,
	HOOK_ELEM_TYPE_PATCH_DATA,
	HOOK_ELEM_TYPE_ERASE_CODE,
	HOOK_ELEM_TYPE_AUTOHOOK_BEFORE,
    HOOK_ELEM_TYPE_AUTOHOOK_AFTER,
    HOOK_ELEM_TYPE_REPLACE_CALL,
    HOOK_ELEM_TYPE_HOOKFUNCTION,
    HOOK_ELEM_TYPE_ASMHOOK_BEFORE,
    HOOK_ELEM_TYPE_ASMHOOK_AFTER,
    HOOK_ELEM_TYPE_ASMPATCH,
    HOOK_ELEM_TYPE_ASMPROC,
    HOOK_ELEM_TYPE_BYTECODEHOOK_BEFORE,
    HOOK_ELEM_TYPE_BYTECODEHOOK_AFTER,
    HOOK_ELEM_TYPE_BYTECODEPATCH,
    HOOK_ELEM_TYPE_BYTECODEPROC,
};
// constructor parameters (type will be set automatically):
// call raw: address, func, size
// call: address, func, size
// jump: address, jumpAddress, size
// patch data: (address, dataPtr, dataSize, patchSize, patchUseNopInstructions [optional]) OR (address, std::string/std::string_view data, patchSize, patchUseNopInstructions [optional])
// erase code: address, size
// autohook: address, func, size
// asmhooks/asmpatch: (address, asmCode, size) OR (address, asmCode, codeReplacementArgs, size)
// ! in above, a method to change code replacement args!
// bytecodehooks/bytecodepatch: (address, bytecodePtr, bytecodeSize, hookSize) OR (address, std::string/std::string_view bytecode, hookSize)
// hookfunction/hookReplaceCall: address, func, size
// asmproc: code OR (code, codeReplacementArgs), provide method to get generated code address (also in all other asmhooks/asmpatches)

// all: description

// each stores restoration data (defined in base class) and optional extra data field

// different games may need some extra elements for a particular hook, or less
// also can have same element, but just a bit different
// and can simply have same elements

/*
    template<typename T>
    auto transform_param(T&& t)
    {
        if constexpr (std::is_class_v<T>)
        {
            return (uint32_t) & t;
        }
        else
        {
            return t;
        }
    }

    template<typename T, std::enable_if_t<std::is_class_v<T>, bool> = true>
    struct transform_param_type
    {
        typedef uint32_t type;
    };

    template<typename T, std::enable_if_t<!std::is_class_v<T>, bool> = true>
    struct transform_param_type
    {
        typedef T type;
    };

    template<typename T>
    using transform_param_type_t = typename transform_param_type<T>::type;
*/

class Hook;
extern std::unordered_map<int, Hook> hooks;
extern std::unordered_map<uint32_t, HookFunc> hookFuncMap;

static void __fastcall dispatchHook(uint32_t esp);

void removeHooks();

void myHookProc();

// FASM

// General errors and conditions
enum FasmAssembleReturn
{
    FASM_OK = 0, // FASM_STATE points to output
    FASM_WORKING = 1,
    FASM_ERROR = 2, // FASM_STATE contains error code
    FASM_INVALID_PARAMETER = -1,
    FASM_OUT_OF_MEMORY = -2,
    FASM_STACK_OVERFLOW = -3,
    FASM_SOURCE_NOT_FOUND = -4,
    FASM_UNEXPECTED_END_OF_SOURCE = -5,
    FASM_CANNOT_GENERATE_CODE = -6,
    FASM_FORMAT_LIMITATIONS_EXCEDDED = -7,
    FASM_WRITE_FAILED = -8,
    FASM_INVALID_DEFINITION = -9,
};

// Error codes for FASM_ERROR condition
enum FasmErrorCode
{
    FASMERR_FILE_NOT_FOUND = -101,
    FASMERR_ERROR_READING_FILE = -102,
    FASMERR_INVALID_FILE_FORMAT = -103,
    FASMERR_INVALID_MACRO_ARGUMENTS = -104,
    FASMERR_INCOMPLETE_MACRO = -105,
    FASMERR_UNEXPECTED_CHARACTERS = -106,
    FASMERR_INVALID_ARGUMENT = -107,
    FASMERR_ILLEGAL_INSTRUCTION = -108,
    FASMERR_INVALID_OPERAND = -109,
    FASMERR_INVALID_OPERAND_SIZE = -110,
    FASMERR_OPERAND_SIZE_NOT_SPECIFIED = -111,
    FASMERR_OPERAND_SIZES_DO_NOT_MATCH = -112,
    FASMERR_INVALID_ADDRESS_SIZE = -113,
    FASMERR_ADDRESS_SIZES_DO_NOT_AGREE = -114,
    FASMERR_DISALLOWED_COMBINATION_OF_REGISTERS = -115,
    FASMERR_LONG_IMMEDIATE_NOT_ENCODABLE = -116,
    FASMERR_RELATIVE_JUMP_OUT_OF_RANGE = -117,
    FASMERR_INVALID_EXPRESSION = -118,
    FASMERR_INVALID_ADDRESS = -119,
    FASMERR_INVALID_VALUE = -120,
    FASMERR_VALUE_OUT_OF_RANGE = -121,
    FASMERR_UNDEFINED_SYMBOL = -122,
    FASMERR_INVALID_USE_OF_SYMBOL = -123,
    FASMERR_NAME_TOO_LONG = -124,
    FASMERR_INVALID_NAME = -125,
    FASMERR_RESERVED_WORD_USED_AS_SYMBOL = -126,
    FASMERR_SYMBOL_ALREADY_DEFINED = -127,
    FASMERR_MISSING_END_QUOTE = -128,
    FASMERR_MISSING_END_DIRECTIVE = -129,
    FASMERR_UNEXPECTED_INSTRUCTION = -130,
    FASMERR_EXTRA_CHARACTERS_ON_LINE = -131,
    FASMERR_SECTION_NOT_ALIGNED_ENOUGH = -132,
    FASMERR_SETTING_ALREADY_SPECIFIED = -133,
    FASMERR_DATA_ALREADY_DEFINED = -134,
    FASMERR_TOO_MANY_REPEATS = -135,
    FASMERR_SYMBOL_OUT_OF_SCOPE = -136,
    FASMERR_USER_ERROR = -140,
    FASMERR_ASSERTION_FAILED = -141,
};

extern const std::map<FasmErrorCode, std::string> fasmErrorCodeToText;

const int FASM_MEMORY_BLOCK_SIZE = 50000;
extern uint8_t fasmMemoryBlock[FASM_MEMORY_BLOCK_SIZE];

extern "C" typedef FasmAssembleReturn(__stdcall *Fasm_Assemble)(const char* src, uint8_t* memoryBlock, int memoryBlockSize, int passes, uint32_t displayPipeHandle);

extern Fasm_Assemble fasm_Assemble;
FasmAssembleReturn fasm_Assemble_str(const std::string& src, uint8_t* memoryBlock, int memoryBlockSize, int passes, uint32_t displayPipeHandle);

// The following structure resides at the beginning of memory block provided
// to the fasm_Assemble function.The condition field contains the same value
// as the one returned by function.
//   When function returns FASM_OK condition, the output_length and
// output_data fields are filled - with pointer to generated output
// (somewhere within the provided memory block) and the count of bytes stored
// there.
//   When function returns FASM_ERROR, the error_code is filled with the
// code of specific error that happened and error_line is a pointer to the
// LINE_HEADER structure, providing information about the line that caused
// the error.

struct LINE_HEADER;
struct FASM_STATE
{
    uint32_t condition;
    union
    {
        uint32_t output_length;
        FasmErrorCode error_code;
    };
    union
    {
        const char* output_data;
        LINE_HEADER* error_line;
    };
};

extern FASM_STATE* fasmState;

// The following structure has two variants - it either defines the line
// that was loaded directly from source, or the line that was generated by
// macroinstruction.First case has the highest bit of line_number set to 0,
// while the second case has this bit set.
//   In the first case, the file_path field contains pointer to the path of
// source file(empty string if it's the source that was provided directly to
// fasm_Assemble function), the line_number is the number of line within
// that file(starting from 1) and the file_offset field contains the offset
// within the file where the line starts.
//   In the second case the macro_calling_line field contains the pointer to
// LINE_HEADER structure for the line which called the macroinstruction, and
// the macro_line field contains the pointer to LINE_HEADER structure for the
// line within the definition of macroinstruction, which generated this one.

struct LINE_HEADER
{
    char* file_path;
    uint32_t line_number;
    union
    {
        uint32_t file_offset;
        uint32_t macro_calling_line;
    };
    uint32_t macro_line;
};

// returns generated code with origin point (for relative calls/jumps) at provided runtime address, or if it's not provided, at fasm memory block (used to get size)
std::string_view compileAsm(const std::string& code, uint32_t runtimeAddress = 0);