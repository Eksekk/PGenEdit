#include "pch.h"
#include "main.h"
#include "LowLevel.h"
#include <cassert>
#include <cstring>
#include "wx/debug.h"

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
	hookRestoreList.erase(addr);
}

std::unordered_map<uint32_t, HookFunc> hookFuncMap;

void __fastcall dispatchHook(uint32_t esp)
{
	HookData* d = reinterpret_cast<HookData*>(esp);
	DWORD hookAddr = dword(d->esp) - 5;
	auto itr = hookFuncMap.find(hookAddr);
	if (itr != hookFuncMap.end())
	{
		HookFunc f = itr->second;
		try
		{
			f(d);
		}
		catch (const std::exception& ex)
		{
			wxLogError(ex.what());
			wxLog::FlushActive();
		}
	}
	else
	{
		wxLogError("Unknown hook address 0x%X", hookAddr);
		wxLog::FlushActive();
	}
}

void __declspec(naked) myHookProc()
{
	// code taken from MMExtension RSMem.cpp
	_asm
	{
		pushfd // push eflags first, because below sub would corrupt them, and we want to preserve them
		// don't know yet why that is required (I think some free space for another functions to allocate, or return data to vanilla functions),
		// but I can't confirm that so I simply commented this out and will find out what it's for when something breaks :)
		// sub esp, 0xFFC
		push eax // push eax so that we can overwrite it with old esp value
		// lea eax, dword ptr[esp + 0x1004] // points to return address to vanilla code (esp + 4 is first address before hook call)
		lea eax, dword ptr[esp + 8]
		// push registers
		push ebx
		push ecx
		push edx
		push eax // old value of esp
		push ebp
		push esi
		push edi
		push dword ptr[eax - 4] // push flags again to have contiguous access to old register values
		mov ecx, esp // pass current esp to hook function to let it access values
		call dispatchHook
		popfd // pop flags
		// pop registers
		pop edi
		pop esi
		pop ebp
		// now here's the thing, if we popped esp right now we wouldn't have easy access to old values and had to do monstrosities like [esp + 0x1008]
		// so move values manually
		mov edx, [esp + 4]
		mov ecx, [esp + 8]
		mov ebx, [esp + 12]
		mov eax, [esp + 16]
		// restore old esp to clean up the stack - points to return address now
		mov esp, [esp]
		ret
	}
}
