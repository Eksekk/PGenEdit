#pragma once
#include "pch.h"
#include "main.h"

// REMAINING TO IMITATE MMEXT
// - disassembler engine
// - assembler (fasm? it's already loaded)
// - integration with lua
// 

struct HookData;

extern std::unordered_map<uint32_t, std::vector<uint8_t> > hookRestoreList;
typedef void(__stdcall *HookFunc)(HookData*);
extern std::unordered_map<uint32_t, HookFunc> hookFuncMap;

void __fastcall dispatchHook(uint32_t esp);

void storeBytes(uint32_t addr, uint32_t size);

// credits to Tomsod for his elemental mod sources (and of course to Grayface), they made it much easier
// for me to understand such low level stuff
// many functions taken/adapted from Tomsod's elemental mod

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
void hookCall(uint32_t addr, void* func, uint32_t size = 5);
void hookJump(uint32_t addr, void* func, uint32_t size = 5);

// data patching functions which unprotect before/protect after (essential for patching code etc.)
void patchByte(uint32_t addr, uint8_t val, bool store);
void patchWord(uint32_t addr, uint16_t val, bool store);
void patchDword(uint32_t addr, uint32_t val, bool store);
void patchQword(uint32_t addr, uint64_t val, bool store);

// erases code (NOPs), writing jump forward if number of bytes erased is high enough
void eraseCode(uint32_t addr, uint32_t size);

// patches sequence of bytes (unprotect/protect)
void patchBytes(uint32_t addr, void* bytes, uint32_t size, bool store);

void removeHooks();
void removeHook(uint32_t addr);

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
		typedef ReturnType(__stdcall *Function)(Args...);
		return reinterpret_cast<Function>(ptr)(args...);
	}
	else if (registerParamsNum == 1)
	{
		typedef ReturnType(__thiscall *Function)(Args...);
		return reinterpret_cast<Function>(ptr)(args...);
	}
	else
	{
		typedef ReturnType(__fastcall* Function)(Args...);
		return reinterpret_cast<Function>(ptr)(args...);
	}
}

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
};

#pragma pack(pop)

void myHookProc();