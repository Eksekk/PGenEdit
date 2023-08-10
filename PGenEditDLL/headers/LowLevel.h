#pragma once
#include "pch.h"
#include "main.h"
#include "Zydis/Zydis.h"

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
};
#pragma pack(pop)

typedef int(__stdcall* HookFuncPtr)(HookData*);
typedef std::function<int(HookData*)> HookFunc; // any function callable with HookData parameter and returning int is hook function

// BASE FUNCTIONS

int getInstructionSize(void* addr);
int getInstructionSize(uint32_t addr);

int getRealHookSize(uint32_t addr, uint32_t size);
void storeBytes(std::vector<uint8_t>* storeAt, uint32_t addr, uint32_t size);

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
void hookJumpRaw(uint32_t addr, void* func, std::vector<uint8_t>* storeAt, uint32_t size = 5);

void hookCall(uint32_t addr, HookFunc func, std::vector<uint8_t>* storeAt, uint32_t size = 5);
uint32_t autohookCall(uint32_t addr, HookFunc func, std::vector<uint8_t>* storeAt, uint32_t size = 5);

// data patching functions which unprotect before/protect after (essential for patching code etc.)
void patchByte(uint32_t addr, uint8_t val, std::vector<uint8_t>* storeAt);
void patchWord(uint32_t addr, uint16_t val, std::vector<uint8_t>* storeAt);
void patchDword(uint32_t addr, uint32_t val, std::vector<uint8_t>* storeAt);
void patchQword(uint32_t addr, uint64_t val, std::vector<uint8_t>* storeAt);

void patchSDword(uint32_t addr, int32_t val, std::vector<uint8_t>* storeAt);

// erases code (NOPs), writing jump forward if number of bytes erased is high enough
void eraseCode(uint32_t addr, uint32_t size, std::vector<uint8_t>* storeAt);

// patches sequence of bytes (unprotect/protect)
void patchBytes(uint32_t addr, void* bytes, uint32_t size, std::vector<uint8_t>* storeAt = nullptr, bool useNops = false);

// allocates memory for code
uint32_t codeMemoryAlloc(uint32_t size);

// copies code
uint32_t copyCode(uint32_t source, uint32_t size, bool writeJumpBack = true);

// type of object representing replaced function call
template<typename ReturnType, typename... Args>
using HookReplaceCallOrigFuncType = typename std::function<ReturnType(Args...)>;

// type representing hook function
template<typename ReturnType, typename... Args>
using HookReplaceCallFunc = typename std::function<uint32_t(HookData* d, HookReplaceCallOrigFuncType<ReturnType, Args...> func, Args... args)>;

template<typename ReturnType, int cc, typename... Args>
uint32_t hookReplaceCall(uint32_t addr, uint32_t stackNum, HookReplaceCallFunc<ReturnType, Args...> func, std::vector<uint8_t>* storeAt = nullptr, uint32_t size = 5)
{
	wxASSERT_MSG(byte(addr) == 0xE8, wxString::Format("Instruction at 0x%X is not call instruction", addr));
	uint32_t dest = addr + 1 + sdword(addr + 1) + 5;
	HookReplaceCallFunc<ReturnType, Args...> def = [addr, cc](HookData* d, Args... args) -> ReturnType {
		return callMemoryAddress<ReturnType>(addr, cc, args...);
	};
	size = getRealHookSize(addr, size);
    hookCall(addr, [func, cc, def](HookData* d) {
        std::tuple<Args...> args;
        constexpr int tupleIndex = 0;
        if constexpr (cc >= 1)
        {
			args.get<tupleIndex++> = static_cast<std::tuple_element_t<0, Args...>>(d->ecx);
		}
        if constexpr (cc >= 2)
        {
            args.get<tupleIndex++> = static_cast<std::tuple_element_t<1, Args...>>(d->edx);
        }
        constexpr int num = 0;
        while (num < stackNum)
        {
            args.get<tupleIndex++> = static_cast<std::tuple_element_t<tupleIndex + num, Args...>>(dword(d->esp + 4 + num * 4));
        }
		func(d, def, args...);
	}, storeAt, size);
}

template<typename ReturnType, typename Address, typename... Args>
ReturnType callMemoryAddress(Address address, int registerParamsNum, Args... args) // NO rvalue reference, because it passes arguments by address
{
    wxASSERT_MSG(registerParamsNum >= -1 && registerParamsNum <= 2, "Invalid number of register parameters");
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

// HOOK SYSTEM

enum HookElementType
{
	HOOK_ELEM_TYPE_CALL_RAW, // simple call hook
	HOOK_ELEM_TYPE_CALL, // mmext-like call hook
	HOOK_ELEM_TYPE_JUMP,
	HOOK_ELEM_TYPE_PATCH_DATA,
	HOOK_ELEM_TYPE_ERASE_CODE,
	HOOK_ELEM_TYPE_AUTOHOOK,
};

enum HookReturnCode
{
	HOOK_RETURN_SUCCESS,
	HOOK_RETURN_AUTOHOOK_NO_PUSH
};

// different games may need some extra elements for a particular hook, or less
// also can have same element, but just a bit different
// and can simply have same elements

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

	void enable(bool enable = true);
	void disable();
	void toggle();
	inline bool isActive() const;
	HookElement();
	~HookElement();
};

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
    HookElement build();
};

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
	Hook(HookElement element, const std::string& description = "");

	Hook() = delete;
	Hook(const Hook&) = delete;
	Hook(Hook&&) = default;
	~Hook();
	Hook& operator=(const Hook&) = delete;
};

extern std::unordered_map<int, Hook> hooks;
extern std::unordered_map<uint32_t, HookFunc> hookFuncMap;

void __fastcall dispatchHook(uint32_t esp);

void removeHooks();

void myHookProc();