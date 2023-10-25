#pragma once
#include "pch.h"
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
};
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

int bitwiseUnsignedToInt(uint32_t val);

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

// sets a call/jump hook (5-byte instruction) at given address transferring
// control into given func, hook size can be given or omitted (5 assumed)
void hookCallRaw(uint32_t addr, void* func, std::vector<uint8_t>* storeAt, uint32_t size = 5);
void unhookCallRaw(uint32_t addr, std::vector<uint8_t>& restoreData);

void hookJumpRaw(uint32_t addr, void* func, std::vector<uint8_t>* storeAt, uint32_t size = 5);
void unhookJumpRaw(uint32_t addr, std::vector<uint8_t>& restoreData);

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
void patchByte(uint32_t addr, uint8_t val, std::vector<uint8_t>* storeAt);
void patchWord(uint32_t addr, uint16_t val, std::vector<uint8_t>* storeAt);
void patchDword(uint32_t addr, uint32_t val, std::vector<uint8_t>* storeAt);
void patchQword(uint32_t addr, uint64_t val, std::vector<uint8_t>* storeAt);

template<typename valType>
void genericPatch(uint32_t addr, valType val, std::vector<uint8_t>* storeAt)
{
    storeBytes(storeAt, addr, sizeof (valType));
    DWORD tmp;
    VirtualProtect((void*)addr, sizeof (valType), PAGE_EXECUTE_READWRITE, &tmp);
    *(valType*)addr = val;
    VirtualProtect((void*)addr, sizeof (valType), tmp, &tmp);
}

void patchSByte(uint32_t addr, int8_t val, std::vector<uint8_t>* storeAt);
void patchSWord(uint32_t addr, int16_t val, std::vector<uint8_t>* storeAt);
void patchSDword(uint32_t addr, int32_t val, std::vector<uint8_t>* storeAt);
void patchSQword(uint32_t addr, int64_t val, std::vector<uint8_t>* storeAt);

// erases code (NOPs), writing jump forward if number of bytes erased is high enough
void eraseCode(uint32_t addr, uint32_t size, std::vector<uint8_t>* storeAt);

// patches sequence of bytes (unprotect/protect)
void patchBytes(uint32_t addr, const void* bytes, uint32_t size, std::vector<uint8_t>* storeAt = nullptr, bool useNops = false);

extern SYSTEM_INFO systemInfo;

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
void* asmpatch(uint32_t addr, const std::string& code, std::vector<uint8_t>* storeAt, int size, bool writeJumpBack);
// this version formats code
void* asmpatch(uint32_t addr, const std::string& code, const CodeReplacementArgs& args, std::vector<uint8_t>* storeAt, int size, bool writeJumpBack = true);

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

// TODO: a version that uses registers from stack (for use in hookfunction or hookcall, to call a function with particular set of register values)
template<typename ReturnType, typename Address, typename... Args>
ReturnType callMemoryAddress(Address address, int registerParamsNum, Args... args) // NO rvalue reference, because it passes arguments by address
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

// type of object representing replaced function call
template<typename ReturnType, typename... Args>
using CallableFunctionHookOrigFunc = typename std::function<ReturnType(Args...)>;

// type representing hook function
template<typename ReturnType, typename... Args>
using CallableFunctionHookFunc = typename std::function<uint32_t(HookData* d, CallableFunctionHookOrigFunc<ReturnType, Args...> func, Args... args)>;

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
            std::get<index>(tup) = (ParamType) (index == 0 ? d->ecx : d->edx);
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

// TODO: redo into virtual inheritance to have each hook type store only data it needs
class HookElement
{
	bool _active;
public:
	HookElementType type;
	uint32_t address;
	uint32_t target;
	const char* patchDataStr; // TODO: string_view instead of separate data/size fields
    std::string asmText;
    CodeReplacementArgs codeReplacementArgs;
	uint32_t hookSize;
	uint32_t dataSize;
	std::vector<uint8_t> restoreData;
	HookFunc func;
	std::string description;
	bool patchUseNops;
	void* extraData; // like copied code for autohook
    // int stackParamNum; // for callable function hooks; number is automatically deduced from argument count and calling convention
    std::vector<int> gameVersions;

    // required for hooks where function receives multiple arguments with various types, can't store templated data member
    std::function<void()> setCallableFunctionHook = nullptr, unsetCallableFunctionHook = nullptr;
    // store types in tuple and function addr in void* field, then when placing hook extract them (tuple_element_t??), cast function to correct type and hook?
    template<typename ReturnType, int cc, typename... Args>
    void setAdvancedHookFunction(CallableFunctionHookFunc<ReturnType, Args...> func);

	void enable(bool enable = true);
	void disable();
	void toggle();
	inline bool isActive() const;
	HookElement();
    HookElement(const HookElement&) = default; // TODO: check (extraData)
    HookElement(HookElement&&) = default;
    HookElement& operator=(const HookElement& elem) = default;
    HookElement& operator=(HookElement&& elem) = default;
	~HookElement();
};

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

template<typename ReturnType, int cc, typename... Args>
void HookElement::setAdvancedHookFunction(CallableFunctionHookFunc<ReturnType, Args...> func)
{
    wxASSERT_MSG(!setCallableFunctionHook, "Advanced hook function is already stored");
    constexpr int stackArgs = std::max(0, (int)sizeof...(Args) - std::max(cc, 0));
    setCallableFunctionHook = [=]() {
        // to consider: supplying number of stack parameters manually?
        if (type == HOOK_ELEM_TYPE_REPLACE_CALL)
        {
            hookReplaceCall<ReturnType, cc, Args...>(address, stackArgs, func, &restoreData, hookSize);
        }
        else if (type == HOOK_ELEM_TYPE_HOOKFUNCTION)
        {
            extraData = (void*)hookFunction<ReturnType, cc, Args...>(address, stackArgs, func, &restoreData, hookSize);
        }
        else
        {
            wxFAIL_MSG(wxString::Format("Setting advanced hook function with invalid hook type (%d)", type));
        }
    };

    unsetCallableFunctionHook = [=]() {
        if (type == HOOK_ELEM_TYPE_REPLACE_CALL)
        {
            unhookReplaceCall(address, restoreData);
        }
        else if (type == HOOK_ELEM_TYPE_HOOKFUNCTION)
        {
            unhookHookFunction(address, restoreData, extraData);
        }
        else
        {
            wxFAIL_MSG(wxString::Format("Unsetting advanced hook function with invalid hook type (%d)", type));
        }
    };
}

// using this class, because constructors with values only would be somewhat unclear which argument does what
class HookElementBuilder
{
	HookElement elem;
public:
	HookElementBuilder& type(HookElementType type);
	HookElementBuilder& address(uint32_t address);
	HookElementBuilder& address(void* address);
	HookElementBuilder& target(uint32_t target);
	HookElementBuilder& size(uint32_t size);
	HookElementBuilder& dataSize(uint32_t dataSize);
    HookElementBuilder& func(HookFunc func);
    HookElementBuilder& patchDataStr(const char* patchDataStr);
    HookElementBuilder& asmText(const std::string& asmText);
	HookElementBuilder& description(const std::string& desc);
	HookElementBuilder& patchUseNops(bool on);
	HookElementBuilder& gameVersions(const std::vector<int>& gameVersions);
	HookElementBuilder& codeReplacementArgs(const CodeReplacementArgs& args);
    template<typename ReturnType, int cc, typename... Args>
    HookElementBuilder& callableFunctionHookFunc(CallableFunctionHookFunc<ReturnType, Args...> func);
    HookElement&& build();
};

template<typename ReturnType, int cc, typename... Args>
HookElementBuilder& HookElementBuilder::callableFunctionHookFunc(CallableFunctionHookFunc<ReturnType, Args...> func)
{
    wxASSERT_MSG(func, "No function passed");
    // wxASSERT_MSG(!elem.funcReplaceCall, "Call replace hook function is already set"); // hook element itself will test it
    elem.setAdvancedHookFunction<ReturnType, cc, Args...>(func);
    return *this;
}

class Hook
{
	bool _active;
public:
	std::vector<HookElement> elements;
	std::string description;
	void enable(bool enable = true);
	void disable();
	void toggle();
	inline bool isActive() const;
	bool isFullyActive() const; // every element is _active

    // cannot use move constructors with initializer_list
	Hook(std::initializer_list<HookElement> elements, const std::string& description = "");
    Hook(const std::vector<HookElement>& elements, const std::string description = "");
	Hook(const HookElement& element, const std::string& description = "");

	Hook() = delete;
	//Hook(const Hook&) = delete; // breaks with initializer lists
	Hook(Hook&&) = default;
	~Hook();
	Hook& operator=(const Hook&) = delete;

    void addElement(HookElement element);
};

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