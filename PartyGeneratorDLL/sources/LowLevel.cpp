#include "pch.h"
#include "main.h"
#include "LowLevel.h"
#include <cassert>
#include <cstring>

std::unordered_map<uint32_t, std::vector<uint8_t> > hookRestoreList;

void storeBytes(uint32_t addr, uint32_t size)
{
	hookRestoreList[addr] = std::vector<uint8_t>((uint8_t*)addr, (uint8_t*)(addr + size));
}

void hookCall(uint32_t addr, void* func, uint32_t size)
{
	assert(size >= 5);
	storeBytes(addr, size);
	DWORD tmp;
	VirtualProtect((void*)addr, size, PAGE_EXECUTE_READWRITE, &tmp);
	byte(addr) = 0xE8; // call rel32
	sdword(addr + 1) = (int32_t)func - addr - 5;
	if (size > 5)
	{
		memset((void*)(addr + 5), 0x90, size - 5);
	}
	VirtualProtect((void*)addr, size, tmp, &tmp);
}

void hookJump(uint32_t addr, void* func, uint32_t size)
{
	assert(size >= 5);
	storeBytes(addr, size);
	DWORD tmp;
	VirtualProtect((void*)addr, size, PAGE_EXECUTE_READWRITE, &tmp);
	byte(addr) = 0xE9; // jmp rel32
	sdword(addr + 1) = (int32_t)func - addr - 5;
	if (size > 5)
	{
		memset((void*)(addr + 5), 0x90, size - 5); // 0x90 = NOP
	}
	VirtualProtect((void*)addr, size, tmp, &tmp);
}

void patchByte(uint32_t addr, uint8_t val, bool store = false)
{
	if (store)
	{
		storeBytes(addr, 1);
	}
	DWORD tmp;
	VirtualProtect((void*)addr, 1, PAGE_EXECUTE_READWRITE, &tmp);
	byte(addr) = val;
	VirtualProtect((void*)addr, 1, tmp, &tmp);
}

void patchWord(uint32_t addr, uint16_t val, bool store = false)
{
	if (store)
	{
		storeBytes(addr, 2);
	}
	DWORD tmp;
	VirtualProtect((void*)addr, 2, PAGE_EXECUTE_READWRITE, &tmp);
	word(addr) = val;
	VirtualProtect((void*)addr, 2, tmp, &tmp);
}

void patchDword(uint32_t addr, uint32_t val, bool store = false)
{
	if (store)
	{
		storeBytes(addr, 4);
	}
	DWORD tmp;
	VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE, &tmp);
	dword(addr) = val;
	VirtualProtect((void*)addr, 4, tmp, &tmp);
}

void patchQword(uint32_t addr, uint64_t val, bool store = false)
{
	if (store)
	{
		storeBytes(addr, 8);
	}
	DWORD tmp;
	VirtualProtect((void*)addr, 8, PAGE_EXECUTE_READWRITE, &tmp);
	qword(addr) = val;
	VirtualProtect((void*)addr, 8, tmp, &tmp);
}

void eraseCode(uint32_t addr, uint32_t size)
{
	storeBytes(addr, size);
	DWORD tmp;
	VirtualProtect((void*)addr, size, PAGE_EXECUTE_READWRITE, &tmp);
	memset((void*)addr, 0x90, size);
	if (size >= 10)
	{
		byte(addr) = 0xEB; // short jmp
		byte(addr + 1) = size - 2;
	}
	VirtualProtect((void*)addr, size, tmp, &tmp);
}

void patchBytes(uint32_t addr, void* bytes, uint32_t size, bool store = true)
{
	if (store)
	{
		storeBytes(addr, size);
	}
	DWORD tmp;
	VirtualProtect((void*)addr, size, PAGE_EXECUTE_READWRITE, &tmp);
	memcpy((void*)addr, bytes, size);
	VirtualProtect((void*)addr, size, tmp, &tmp);
}

void removeHooks()
{
	for (auto& [address, data] : hookRestoreList)
	{
		patchBytes(address, data.data(), data.size(), false);
	}
	hookRestoreList.clear();
}

void removeHook(uint32_t addr)
{
	if (!hookRestoreList.contains(addr))
	{
		wxLogFatalError("Attempt to remove nonexisting hook at %X", addr);
	}
	auto& data = hookRestoreList[addr];
	patchBytes(addr, data.data(), data.size(), false);
}