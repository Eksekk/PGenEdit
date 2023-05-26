#include "pch.h"
#include "main.h"
#include "LowLevel.h"
#include <cassert>
#include <cstring>
#include "wx/debug.h"

std::unordered_map<int, Hook> hooks;
std::unordered_map<uint32_t, HookFunc> hookFuncMap;
std::unordered_map<uint32_t, std::vector<uint8_t>> hookRestoreList;

void HookElement::enable(bool enable)
{
	if (enable && !_active)
	{
		_active = true;
		switch (type)
		{

		case HOOK_ELEM_TYPE_PATCH_DATA:
		{
			patchBytes(address, reinterpret_cast<void*>(target), dataSize, &restoreData);
		}
		break;
		case HOOK_ELEM_TYPE_CALL_RAW:
		{
			hookCallRaw(address, reinterpret_cast<void*>(target), &restoreData, hookSize);
		}
		break;
		case HOOK_ELEM_TYPE_CALL:
		{
			wxFAIL_MSG("Not implemented yet");
		}
		break;
		case HOOK_ELEM_TYPE_JUMP:
		{
			hookJumpRaw(address, reinterpret_cast<void*>(target), &restoreData, hookSize);
		}
		break;
		default:
		{
			wxFAIL_MSG(wxString::Format("Unknown hook type %d", (int)type));
		}

		}
	}
	else if (!enable && _active)
	{
		_active = false;
		patchBytes(address, restoreData.data(), restoreData.size(), nullptr);
		restoreData.clear();
	}
}

void HookElement::disable()
{
	enable(false);
}

void HookElement::toggle()
{
	enable(!_active);
}

inline bool HookElement::isActive() const
{
	return _active;
}

HookElement::HookElement() : _active(false), type(HOOK_ELEM_TYPE_CALL_RAW), address(0), target(0), hookSize(5), dataSize(5)
{
}

void Hook::enable(bool enable)
{
	for (auto& elem : elements)
	{
		elem.enable(enable);
	}
}

void Hook::disable()
{
	enable(false);
}

void Hook::toggle()
{
	enable(!_active);
}

inline bool Hook::isActive() const
{
	return _active;
}

bool Hook::isFullyActive() const
{
	bool yes = _active;
	for (const auto& elem : elements)
	{
		yes = !elem.isActive() ? false : yes;
	}
	return yes;
}

Hook::Hook(std::initializer_list<HookElement> elements) : elements(elements), _active(false)
{
	
}

void storeBytes(std::vector<uint8_t>* storeAt, uint32_t addr, uint32_t size)
{
	if (storeAt)
	{
		*storeAt = std::vector<uint8_t>((uint8_t*)addr, (uint8_t*)(addr + size));
	}
}

void hookCallRaw(uint32_t addr, void* func, std::vector<uint8_t>* storeAt, uint32_t size)
{
	assert(size >= 5);
	storeBytes(storeAt, addr, size);
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

void hookJumpRaw(uint32_t addr, void* func, std::vector<uint8_t>* storeAt, uint32_t size)
{
	assert(size >= 5);
	storeBytes(storeAt, addr, size);
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

void patchByte(uint32_t addr, uint8_t val, std::vector<uint8_t>* storeAt)
{
	storeBytes(storeAt, addr, 1);
	DWORD tmp;
	VirtualProtect((void*)addr, 1, PAGE_EXECUTE_READWRITE, &tmp);
	byte(addr) = val;
	VirtualProtect((void*)addr, 1, tmp, &tmp);
}

void patchWord(uint32_t addr, uint16_t val, std::vector<uint8_t>* storeAt)
{
	storeBytes(storeAt, addr, 2);
	DWORD tmp;
	VirtualProtect((void*)addr, 2, PAGE_EXECUTE_READWRITE, &tmp);
	word(addr) = val;
	VirtualProtect((void*)addr, 2, tmp, &tmp);
}

void patchDword(uint32_t addr, uint32_t val, std::vector<uint8_t>* storeAt)
{
	storeBytes(storeAt, addr, 4);
	DWORD tmp;
	VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE, &tmp);
	dword(addr) = val;
	VirtualProtect((void*)addr, 4, tmp, &tmp);
}

void patchQword(uint32_t addr, uint64_t val, std::vector<uint8_t>* storeAt)
{
	storeBytes(storeAt, addr, 8);
	DWORD tmp;
	VirtualProtect((void*)addr, 8, PAGE_EXECUTE_READWRITE, &tmp);
	qword(addr) = val;
	VirtualProtect((void*)addr, 8, tmp, &tmp);
}

void eraseCode(uint32_t addr, uint32_t size, std::vector<uint8_t>* storeAt)
{
	storeBytes(storeAt, addr, size);
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

void patchBytes(uint32_t addr, void* bytes, uint32_t size, std::vector<uint8_t>* storeAt)
{
	storeBytes(storeAt, addr, size);
	DWORD tmp;
	VirtualProtect((void*)addr, size, PAGE_EXECUTE_READWRITE, &tmp);
	memcpy((void*)addr, bytes, size);
	VirtualProtect((void*)addr, size, tmp, &tmp);
}

void removeHooks()
{
	for (auto& [id, hook]: hooks)
	{
		hook.disable();
	}
}

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

HookElementBuilder& HookElementBuilder::type(HookElementType type)
{
	elem.type = type;
	return *this;
}

HookElementBuilder& HookElementBuilder::address(uint32_t address)
{
	elem.address = address;
	return *this;
}

HookElementBuilder& HookElementBuilder::target(uint32_t target)
{
	elem.target = target;
	return *this;
}

HookElementBuilder& HookElementBuilder::size(uint32_t size)
{
	elem.hookSize = size;
	return *this;
}

HookElementBuilder& HookElementBuilder::dataSize(uint32_t dataSize)
{
	elem.dataSize = dataSize;
	return *this;
}

HookElement HookElementBuilder::build()
{
	if (elem.address == 0)
	{
		wxFAIL_MSG("Hook address not set");
	}
	if (elem.target == 0)
	{
		wxFAIL_MSG("Target not set");
	}
	return elem;
}
