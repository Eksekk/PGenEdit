#pragma once
#include "pch.h"
#include "main.h"

extern std::unordered_map<uint32_t, std::vector<uint8_t> > hookRestoreList;

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