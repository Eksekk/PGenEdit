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

// BASE FUNCTIONS

int getInstructionSize(void* addr);
int getInstructionSize(uint32_t addr);

int getRealHookSize(uint32_t addr, uint32_t size);
void storeBytes(std::vector<uint8_t>* storeAt, uint32_t addr, uint32_t size);

uint32_t findCode(uint32_t addr, const char* code);
uint32_t findCode(uint32_t addr, const std::string& code);
uint32_t findCode(void* addr, const char* code);
uint32_t findCode(void* addr, const std::string& code);

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
uint32_t autohookCall(uint32_t addr, HookFunc func, std::vector<uint8_t>* storeAt, uint32_t size = 5);
void unhookAutohookCall(uint32_t addr, std::vector<uint8_t>& restoreData, void* allocatedCode);
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

void patchSDword(uint32_t addr, int32_t val, std::vector<uint8_t>* storeAt);

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

// copies code
uint32_t copyCode(uint32_t source, uint32_t size, bool writeJumpBack = true);

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
            std::get<index>(tup) = (ParamType)dword(index == 0 ? d->ecx : d->edx);
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
uint32_t callableHookCommon(uint32_t addr, uint32_t stackNum, CallableFunctionHookFunc<ReturnType, Args...> func, std::vector<uint8_t>* storeAt, uint32_t size, uint32_t code)
{
    using OrigType = CallableFunctionHookOrigFunc<ReturnType, Args...>;
    OrigType def = [=](Args... args) -> ReturnType { // CRASH HERE
        return callMemoryAddress<ReturnType>(code, cc, args...);
    };
    size = getRealHookSize(addr, size);
    hookCall(addr, [=](HookData* d) -> uint32_t {
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
	uint32_t dest = addr + 1 + sdword(addr + 1) + 5;
    callableHookCommon<ReturnType, cc, Args...>(addr, stackNum, func, storeAt, size, dest);
}

template<typename ReturnType, int cc, typename... Args>
uint32_t hookFunction(uint32_t addr, uint32_t stackNum, CallableFunctionHookFunc<ReturnType, Args...> func, std::vector<uint8_t>* storeAt = nullptr, uint32_t size = 5)
{
    static_assert(cc >= -1 && cc <= 2, "Invalid calling convention");
    static_assert(((std::is_standard_layout_v<Args>) && ...) && (std::is_standard_layout_v<ReturnType> || std::is_void_v<ReturnType>), "Arguments are non-POD");
    uint32_t dest = copyCode(addr, size, true);
    callableHookCommon<ReturnType, cc, Args...>(addr, stackNum, func, storeAt, size, dest);
    return dest;
}

void unhookReplaceCall(uint32_t addr, std::vector<uint8_t>& restoreData);
void unhookHookFunction(uint32_t addr, std::vector<uint8_t>& restoreData, void* copiedCode);

// HOOK SYSTEM

enum HookElementType
{
	HOOK_ELEM_TYPE_CALL_RAW, // simple call hook
	HOOK_ELEM_TYPE_CALL, // mmext-like call hook
	HOOK_ELEM_TYPE_JUMP,
	HOOK_ELEM_TYPE_PATCH_DATA,
	HOOK_ELEM_TYPE_ERASE_CODE,
	HOOK_ELEM_TYPE_AUTOHOOK,
    HOOK_ELEM_TYPE_REPLACE_CALL,
    HOOK_ELEM_TYPE_HOOKFUNCTION,
};

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
	const char* patchDataStr;
	uint32_t hookSize;
	uint32_t dataSize;
	std::vector<uint8_t> restoreData;
	HookFunc func;
	bool needUnprotect;
	std::string description;
	bool patchUseNops;
	void* extraData; // like copied code for autohook
    // int stackParamNum; // for callable function hooks; number is automatically deduced from argument count and calling convention

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
	HookElementBuilder& target(uint32_t target);
	HookElementBuilder& size(uint32_t size);
	HookElementBuilder& dataSize(uint32_t dataSize);
    HookElementBuilder& func(HookFunc func);
    HookElementBuilder& patchDataStr(const char* patchDataStr);
    HookElementBuilder& needUnprotect(bool needUnprotect);
	HookElementBuilder& description(const std::string& desc);
	HookElementBuilder& patchUseNops(bool on);
    template<typename ReturnType, int cc, typename... Args>
    HookElementBuilder& callableFunctionHookFunc(CallableFunctionHookFunc<ReturnType, Args...> func);
    HookElement build();
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

	Hook(std::initializer_list<HookElement> elements, const std::string& description = "");
    Hook(const std::vector<HookElement>& elements, const std::string description = "");
	Hook(HookElement element, const std::string& description = "");

	Hook() = delete;
	Hook(const Hook&) = delete;
	Hook(Hook&&) = default;
	~Hook();
	Hook& operator=(const Hook&) = delete;

    void addElement(HookElement element);
};

extern std::unordered_map<int, Hook> hooks;
extern std::unordered_map<uint32_t, HookFunc> hookFuncMap;

void __fastcall dispatchHook(uint32_t esp);

void removeHooks();

void myHookProc();