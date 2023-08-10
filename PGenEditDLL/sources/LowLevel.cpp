#include "pch.h"
#include "main.h"
#include "LowLevel.h"
#include <cassert>
#include <cstring>
#include "wx/debug.h"

std::unordered_map<int, Hook> hooks;
std::unordered_map<uint32_t, HookFunc> hookFuncMap;

void checkOverlap(uint32_t address, uint32_t size = 5)
{
	if (hookFuncMap.contains(address))
	{
		wxFAIL_MSG(wxString::Format("Hook at address 0x%X is already set", address));
	}
	else
	{
		for (uint32_t checkAddr = address - size + 1; checkAddr <= address + size - 1; ++checkAddr)
		{
			if (hookFuncMap.contains(checkAddr))
			{
				wxFAIL_MSG(wxString::Format("Hook at 0x%X overlaps with existing hook at 0x%X", address, checkAddr));
			}
		}
	}
}

void HookElement::enable(bool enable)
{
	if (enable && !_active)
	{
		_active = true;
		switch (type)
		{

		case HOOK_ELEM_TYPE_PATCH_DATA:
		{
			void* target = patchDataStr ? (void*)patchDataStr : (void*)this->target;
			int dataSize = patchDataStr ? strlen(patchDataStr) : this->dataSize;
			patchBytes(address, target, dataSize, &restoreData, this->patchUseNops);
		}
		break;
		case HOOK_ELEM_TYPE_CALL_RAW:
		{
			checkOverlap(address, hookSize);
			hookCallRaw(address, reinterpret_cast<void*>(target), &restoreData, hookSize);
		}
		break;
		case HOOK_ELEM_TYPE_CALL:
		{
			// here overlap is checked automatically, TODO: add to all other hook functions
			hookCall(address, func, &restoreData, hookSize);
		}
		break;
		case HOOK_ELEM_TYPE_AUTOHOOK:
		{
			checkOverlap(address, hookSize);
			// TODO: probably inefficient? somehow pass copied code to autohookCall?
			extraData = (void*)autohookCall(address, func, &restoreData, hookSize);
		}
		break;
		case HOOK_ELEM_TYPE_JUMP:
        {
            checkOverlap(address, hookSize);
			hookJumpRaw(address, reinterpret_cast<void*>(target), &restoreData, hookSize);
		}
		break;
		case HOOK_ELEM_TYPE_ERASE_CODE:
		{
			// TODO: check overlap
			eraseCode(address, hookSize, &restoreData);
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
		if (type == HOOK_ELEM_TYPE_CALL || type == HOOK_ELEM_TYPE_AUTOHOOK)
		{
			hookFuncMap.erase(address);
		}
		if (type == HOOK_ELEM_TYPE_AUTOHOOK)
		{
			wxASSERT(extraData);
			free(extraData);
		}
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

HookElement::HookElement() : _active(false), type(HOOK_ELEM_TYPE_CALL_RAW), address(0), target(0), hookSize(5), dataSize(0), func(0), patchDataStr(0),
	needUnprotect(false), description(""), patchUseNops(false), extraData(nullptr)
{
}

HookElement::~HookElement()
{
	if (_active)
	{
		disable();
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

HookElementBuilder& HookElementBuilder::func(HookFunc func)
{
    elem.func = func;
    return *this;
}

HookElementBuilder& HookElementBuilder::patchDataStr(const char* patchDataStr)
{
	elem.patchDataStr = patchDataStr;
	return *this;
}

HookElementBuilder& HookElementBuilder::needUnprotect(bool needUnprotect)
{
    elem.needUnprotect = needUnprotect;
    return *this;
}

HookElementBuilder& HookElementBuilder::description(const std::string& desc)
{
	elem.description = desc;
	return *this;
}

HookElementBuilder& HookElementBuilder::patchUseNops(bool on)
{
	elem.patchUseNops = on;
	return *this;
}

HookElement HookElementBuilder::build()
{
    // hook properties: type, address, dataSize, hookSize, target, func, needUnprotect, description, patchUseNops (only for patch data)
    // hook types: jump, call raw, call, patch data, erase code
    
    // all need address
    if (elem.address == 0)
    {
        wxFAIL_MSG("Hook address not set");
    }
    // patch data needs data ptr, data size and target
	if (elem.type == HOOK_ELEM_TYPE_PATCH_DATA)
	{
        if (elem.dataSize <= 0 && elem.patchDataStr == nullptr)
        {
            wxFAIL_MSG("Patch data hook: not using string and data size not set or <= 0");
        }
        else if (elem.target <= 0 && elem.patchDataStr == nullptr)
        {
            wxFAIL_MSG("Patch data hook: neither of target bytes ptr or patch data string is set");
        }
        else if (elem.target > 0 && elem.patchDataStr != nullptr)
        {
            wxFAIL_MSG("Patch data hook: target and patch str can't both be set");
        }
	}
	// erase code needs size
	if (elem.type == HOOK_ELEM_TYPE_ERASE_CODE)
	{
        if (elem.hookSize <= 0)
        {
            wxFAIL_MSG("Erase code hook: size not set or <= 0");
        }
	}
    // call and autohook needs func (call raw jumps to any code, not using hook proc)
    if ((elem.type == HOOK_ELEM_TYPE_CALL || elem.type == HOOK_ELEM_TYPE_AUTOHOOK) && elem.func == 0)
    {
        wxFAIL_MSG("Call hook/autohook: function not set");
    }
    // call/call raw/jump/autohook need hook size >= 5
    if ((elem.type == HOOK_ELEM_TYPE_JUMP || elem.type == HOOK_ELEM_TYPE_CALL || elem.type == HOOK_ELEM_TYPE_CALL_RAW || elem.type == HOOK_ELEM_TYPE_AUTOHOOK) && elem.hookSize < 5)
    {
        wxFAIL_MSG("Call/jump hook/autohook size can't be less than 5");
    }
    // jump/call raw need target (intended to jump/call simple asm functions)
    if ((elem.type == HOOK_ELEM_TYPE_JUMP || elem.type == HOOK_ELEM_TYPE_CALL_RAW) && elem.target <= 0)
    {
        wxFAIL_MSG("Jump/call raw hook: target to jump to not set or <= 0");
    }
    return elem;
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

Hook::Hook(std::initializer_list<HookElement> elements, const std::string& description) : elements(elements), _active(false), description(description)
{

}

Hook::Hook(HookElement element, const std::string& description) : elements({element}), _active(false), description(description)
{

}

Hook::~Hook()
{
	if (_active)
	{
		disable();
	}
}

// returns address of next instruction after [size] bytes
int getRealHookSize(uint32_t addr, uint32_t size)
{
	uint32_t n = 0;
	while (n < size)
	{
		n = n + getInstructionSize(addr + n);
	}
	// assert(n >= 5); // now also supports NOP-ing when patching data, so this assert can't execute
	return n;
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
	size = getRealHookSize(addr, size);
	storeBytes(storeAt, addr, size);
	DWORD tmp;
	VirtualProtect((void*)addr, size, PAGE_EXECUTE_READWRITE, &tmp);
	byte(addr) = 0xE8; // call rel32
	sdword(addr + 1) = (int32_t)func - addr - 5;
	if (size > 5)
	{
		memset((void*)(addr + 5), 0x90, size - 5); // 0x90 = NOP
	}
	VirtualProtect((void*)addr, size, tmp, &tmp);
}

void hookJumpRaw(uint32_t addr, void* func, std::vector<uint8_t>* storeAt, uint32_t size)
{
	size = getRealHookSize(addr, size);
	storeBytes(storeAt, addr, size);
	DWORD tmp;
	VirtualProtect((void*)addr, size, PAGE_EXECUTE_READWRITE, &tmp);
	byte(addr) = 0xE9; // jmp rel32
	sdword(addr + 1) = (int32_t)func - addr - 5;
	if (size > 5)
	{
		memset((void*)(addr + 5), 0x90, size - 5);
	}
	VirtualProtect((void*)addr, size, tmp, &tmp);
}

void hookCall(uint32_t addr, HookFunc func, std::vector<uint8_t>* storeAt, uint32_t size /*= 5*/)
{
	size = getRealHookSize(addr, size);
    checkOverlap(addr, size);
    hookCallRaw(addr, reinterpret_cast<void*>(myHookProc), storeAt, size);
    hookFuncMap[addr] = func;
}

uint32_t autohookCall(uint32_t addr, HookFunc func, std::vector<uint8_t>* storeAt, uint32_t size)
{
	// copy code with jump back
	// setup call hook
	// pass our own function which will change return address to copied code
	
	// PROBLEMS WITH FREEING ALLOCATED MEMORY?
	size = getRealHookSize(addr, size);

	uint32_t code = copyCode(addr, size, true);
	auto wrapperFunc = [addr, size, func](HookData* d) -> int {
		d->esp = d->esp + 4;
		if (func(d) != HOOK_RETURN_AUTOHOOK_NO_PUSH)
		{
			d->push(addr + size);
		}
		return HOOK_RETURN_SUCCESS;
	};
	hookCall(addr, wrapperFunc, storeAt, size);
	return code;
}

// TODO: generic function to generate all four without repeating code?
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

void patchSDword(uint32_t addr, int32_t val, std::vector<uint8_t>* storeAt)
{
    storeBytes(storeAt, addr, 4);
    DWORD tmp;
    VirtualProtect((void*)addr, 4, PAGE_EXECUTE_READWRITE, &tmp);
    sdword(addr) = val;
    VirtualProtect((void*)addr, 4, tmp, &tmp);
}

void eraseCode(uint32_t addr, uint32_t size, std::vector<uint8_t>* storeAt)
{
	size = getRealHookSize(addr, size);
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

void patchBytes(uint32_t addr, void* bytes, uint32_t size, std::vector<uint8_t>* storeAt, bool useNops)
{
	int realSize = size, dataSize = size;
	if (useNops)
	{
		realSize = getRealHookSize(addr, dataSize);
	}
	storeBytes(storeAt, addr, realSize);
	DWORD tmp;
	VirtualProtect((void*)addr, realSize, PAGE_EXECUTE_READWRITE, &tmp);
	memcpy((void*)addr, bytes, dataSize);
	if (useNops && realSize - dataSize > 0)
	{
		memset(reinterpret_cast<void*>(addr + dataSize), 0x90, realSize - dataSize);
	}
	VirtualProtect((void*)addr, realSize, tmp, &tmp);
}

uint32_t codeMemoryAlloc(uint32_t size)
{
	// TODO: memory leak when reloading dll?
	void* mem = malloc(size);
	assert(mem);
	DWORD tmp;
	VirtualProtect(mem, size, PAGE_EXECUTE_READ, &tmp);
	memset(mem, 0x90, size);
	return reinterpret_cast<uint32_t>(mem);
}

uint32_t copyCode(uint32_t source, uint32_t size, bool writeJumpBack)
{
	size = getRealHookSize(source, size);
	// check short jumps
    ZyanU64 runtimeAddr = (ZyanU64)source;
    ZydisDisassembledInstruction instr;
	std::vector<int> rel32Positions; // to fix calls/jumps
	int n = 0;
    bool hasShort = false;
	while (n < size && ZYAN_SUCCESS(ZydisDisassembleIntel(ZYDIS_MACHINE_MODE_LEGACY_32, source + n, reinterpret_cast<void*>(source + n), 20, &instr)))
	{
        if (instr.info.meta.branch_type == ZYDIS_BRANCH_TYPE_SHORT)
        {
			uint32_t dest = n + 2 + byte(source + n + 1);
			if (dest > source + size) // jump outside code
			{
				hasShort = true;
			}
        }
		else if ((instr.info.meta.branch_type == ZYDIS_BRANCH_TYPE_NEAR || instr.info.meta.category == ZYDIS_CATEGORY_CALL) && (instr.info.attributes & ZYDIS_ATTRIB_IS_RELATIVE))
		{
			// to check if call is included in "branch type"
			wxASSERT_MSG((instr.info.meta.branch_type == ZYDIS_BRANCH_TYPE_NEAR) ^ (instr.info.meta.category == ZYDIS_CATEGORY_CALL), "Call instruction is considered as 'branch type'");
			auto& disp = instr.info.raw.disp;
			wxASSERT_MSG(disp.size == 4, wxString::Format("Expected size 4 (DWORD) immediate, got %d", disp.size));
			rel32Positions.push_back(n + disp.offset);
		}
        n += instr.info.length;
	}

	if (n < size) // Zydis error
	{
		wxLogError("Couldn't copy code from address 0x%X + 0x%X - zydis error", source, n);
		wxLog::FlushActive();
		return 0;
	}
	else if (hasShort)
	{
		wxLogError("Code at 0x%X of size 0x%X has short jump leading outside", source, size);
		wxLog::FlushActive();
		return 0;
	}

	uint32_t newCodeSize = size + (writeJumpBack ? 5 : 0);
    uint32_t mem = codeMemoryAlloc(newCodeSize);
    // copy code to newly allocated memory
	memcpy((void*)mem, (void*)source, size);
	// write jump back
	if (writeJumpBack)
	{
        hookJumpRaw(mem + size, reinterpret_cast<void*>(source + size), nullptr);
	}
	// fix calls/jumps
	if (rel32Positions.size() > 0)
    {
		DWORD tmp;
		VirtualProtect((void*)mem, newCodeSize, PAGE_EXECUTE_READWRITE, &tmp);
        for (int fix : rel32Positions)
        {
            sdword(mem + fix) += (mem - source);
        }
		VirtualProtect((void*)mem, newCodeSize, tmp, &tmp);
	}
	return mem;
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
	// code taken from MMExtension RSMem.cpp and adapted
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

int getInstructionSize(void* addr)
{
	ZyanU64 runtimeAddr = (ZyanU64)addr;
    ZydisDisassembledInstruction instr;
	if (!ZYAN_SUCCESS(ZydisDisassembleIntel(ZydisMachineMode::ZYDIS_MACHINE_MODE_LEGACY_32, runtimeAddr, addr, 20, &instr)))
	{
		wxMessageBox(wxString::Format("Couldn't get instruction length at address 0x%X", (uint32_t)addr), "Error", wxCENTER | wxOK | wxICON_ERROR);
		return 1; // so no infinite loops happen
	}
	else
	{
		//wxLogInfo("Instruction at address 0x%X has length of %d", (uint32_t)addr, (uint32_t)instr.info.length);
		return instr.info.length;
	}
}

int getInstructionSize(uint32_t addr)
{
	return getInstructionSize((void*)addr);
}

void HookData::push(uint32_t val)
{
	esp = esp - 4;
	dword(esp) = val;
}

std::function<uint32_t(HookData* d, std::function<short(int, char*, bool)>, int, char*, bool)> f = reinterpret_cast<uint32_t(*)(HookData * d, std::function<short(int, char*, bool)>, int, char*, bool)>(0x55555555);

void g()
{
	hookReplaceCall<short, 1, int, char*, bool>(0xFEDECEBE, 2, f);
}