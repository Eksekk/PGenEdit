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

void testMemberFunctions()
{
	struct Player
	{
		bool wearsItem(int id, int slot)
		{
			if (MMVER == 7)
			{
				return callMemoryAddress<bool>(0x48D6EF, 1, this, id, slot);
			}
		}
	};
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
			const void* target = patchDataStr ? (const void*)patchDataStr : (void*)this->target;
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
		case HOOK_ELEM_TYPE_REPLACE_CALL:
		case HOOK_ELEM_TYPE_HOOKFUNCTION:
		{
			wxASSERT_MSG(setCallableFunctionHook, "Function to set hook is unavailable");
			setCallableFunctionHook();
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
		switch (type)
		{
		case HOOK_ELEM_TYPE_CALL_RAW: unhookCallRaw(address, restoreData);
			break;
		case HOOK_ELEM_TYPE_CALL: unhookCall(address, restoreData);
			break;
		case HOOK_ELEM_TYPE_JUMP: unhookJumpRaw(address, restoreData);
			break;
		case HOOK_ELEM_TYPE_ERASE_CODE:
		case HOOK_ELEM_TYPE_PATCH_DATA:
			patchBytes(address, restoreData.data(), restoreData.size(), nullptr, this->patchUseNops);
			break;
		case HOOK_ELEM_TYPE_AUTOHOOK: unhookAutohookCall(address, restoreData, extraData);
			break;
		case HOOK_ELEM_TYPE_REPLACE_CALL:
		case HOOK_ELEM_TYPE_HOOKFUNCTION:
			unsetCallableFunctionHook();
			break;
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
	if (extraData)
	{
		codeMemoryFree(extraData);
		extraData = nullptr;
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
    // call/call raw/jump/autohook/callable function hooks need hook size >= 5
	static const std::vector<HookElementType> minimumSize5 = { HOOK_ELEM_TYPE_JUMP, HOOK_ELEM_TYPE_CALL, HOOK_ELEM_TYPE_CALL_RAW, HOOK_ELEM_TYPE_AUTOHOOK, HOOK_ELEM_TYPE_REPLACE_CALL, HOOK_ELEM_TYPE_HOOKFUNCTION };
    if (existsInVector(minimumSize5, elem.type) && elem.hookSize < 5)
    {
        wxFAIL_MSG("Hook size can't be less than 5");
    }
    // jump/call raw need target (intended to jump/call simple asm functions)
    if ((elem.type == HOOK_ELEM_TYPE_JUMP || elem.type == HOOK_ELEM_TYPE_CALL_RAW) && elem.target <= 0)
    {
        wxFAIL_MSG("Jump/call raw hook: target to jump to not set or <= 0");
    }
	// callable function hooks need function
	if ((elem.type == HOOK_ELEM_TYPE_HOOKFUNCTION || elem.type == HOOK_ELEM_TYPE_REPLACE_CALL) && !elem.setCallableFunctionHook)
	{
		wxFAIL_MSG("Callable function hook: hook function not provided");
	}

    return elem;
}

void Hook::enable(bool enable)
{
	if (elements.empty())
	{
		wxLogWarning("Enabled hook '%s' with no elements", description);
	}

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

Hook::Hook(const std::vector<HookElement>& elements, const std::string description /*= ""*/) : elements(elements), _active(false), description(description)
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

void Hook::addElement(HookElement element)
{
	elements.push_back(element);
}

int getRealHookSize(uint32_t addr, uint32_t size, uint32_t minSize)
{
	uint32_t n = 0;
	uint32_t max = std::max(size, minSize);
	while (n < max)
	{
		n = n + getInstructionSize(addr + n);
	}
	assert(n >= minSize);
	return n;
}

void storeBytes(std::vector<uint8_t>* storeAt, uint32_t addr, uint32_t size)
{
	if (storeAt)
	{
		*storeAt = std::vector<uint8_t>((uint8_t*)addr, (uint8_t*)(addr + size));
	}
}

uint32_t findCode(uint32_t addr, const char* code)
{
    ZydisDisassembledInstruction instr;
	int codeLen = strlen(code); // FIXME: will fail with embedded zeros
	while (true)
	{
		if (!ZYAN_SUCCESS(ZydisDisassembleIntel(ZYDIS_MACHINE_MODE_LEGACY_32, addr, (void*)addr, 20, &instr))) // invalid code
		{
			__debugbreak();
			++addr;
			continue;
		}

		if (instr.info.length != codeLen)
        {
            addr += instr.info.length;
			continue;
		}

		if (memcmp((void*)addr, code, codeLen) == 0)
		{
			break;
		}
		addr += instr.info.length;
	}
	return addr;
}

uint32_t findCode(uint32_t addr, const std::string& code)
{
	return findCode(addr, code.c_str());
}

uint32_t findCode(void* addr, const char* code)
{
	return findCode((uint32_t)addr, code);
}

uint32_t findCode(void* addr, const std::string& code)
{
	return findCode((uint32_t)addr, code);
}

uint32_t intMax = std::numeric_limits<int>::max();
int bitwiseUnsignedToInt(uint32_t val)
{
	int res = val;
	if (val > intMax)
	{
		res = intMax - val;
	}
	return res;
}

void hookCallRaw(uint32_t addr, void* func, std::vector<uint8_t>* storeAt, uint32_t size)
{
	size = getRealHookSize(addr, size, 5);
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

void unhookCallRaw(uint32_t addr, std::vector<uint8_t>& restoreData)
{
    patchBytes(addr, restoreData.data(), restoreData.size(), nullptr);
    restoreData.clear();
}

void hookJumpRaw(uint32_t addr, void* func, std::vector<uint8_t>* storeAt, uint32_t size)
{
	size = getRealHookSize(addr, size, 5);
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

void unhookJumpRaw(uint32_t addr, std::vector<uint8_t>& restoreData)
{
	patchBytes(addr, restoreData.data(), restoreData.size(), nullptr);
}

void hookCall(uint32_t addr, HookFunc func, std::vector<uint8_t>* storeAt, uint32_t size /*= 5*/)
{
	size = getRealHookSize(addr, size, 5);
    checkOverlap(addr, size);
    hookCallRaw(addr, reinterpret_cast<void*>(myHookProc), storeAt, size);
    hookFuncMap[addr] = func;
}

void unhookCall(uint32_t addr, std::vector<uint8_t>& restoreData)
{
	unhookCallRaw(addr, restoreData);
    wxASSERT(hookFuncMap.contains(addr));
    hookFuncMap.erase(addr);
}

uint32_t autohookCall(uint32_t addr, HookFunc func, std::vector<uint8_t>* storeAt, uint32_t size)
{
	// copy code with jump back
	// setup call hook
	// pass our own function which will change return address to copied code
	
	size = getRealHookSize(addr, size, 5);

	uint32_t code = copyCode(addr, size, true);
	auto wrapperFunc = [code, func](HookData* d) -> int {
		d->esp = d->esp + 4;
		if (func(d) != HOOK_RETURN_AUTOHOOK_NO_PUSH)
		{
			d->push(code);
		}
		return HOOK_RETURN_SUCCESS;
	};
	hookCall(addr, wrapperFunc, storeAt, size);
	return code;
}

// TODO: all unhooks could also store all required data by themselves, to not require passing unnecessary arguments
void unhookAutohookCall(uint32_t addr, std::vector<uint8_t>& restoreData, void* allocatedCode)
{
	unhookCall(addr, restoreData);
	codeMemoryFree(allocatedCode);
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
	size = getRealHookSize(addr, size, 1);
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

void patchBytes(uint32_t addr, const void* bytes, uint32_t size, std::vector<uint8_t>* storeAt, bool useNops)
{
	int realSize = size, dataSize = size;
	if (useNops)
	{
		realSize = getRealHookSize(addr, dataSize, 1);
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

uint32_t allocatedBlockSize = 0;
void* allocatedBlock = nullptr;
std::map<uint32_t, std::vector<void*>> freeAddressesBySize;
std::map<void*, uint32_t> sizesByAddress; // all allocated "micro-blocks" (parts of single VirtualAlloc call reserved in multiple codeMemoryAlloc calls)
std::map<void*, uint32_t> allAllocatedBlocks; // <address, size>
SYSTEM_INFO systemInfo;

uint32_t codeMemoryAlloc(uint32_t size)
{
	auto itr = freeAddressesBySize.find(size);
	if (itr != freeAddressesBySize.end() && itr->second.size() > 0)
	{
		void* addr = itr->second.front();
		itr->second.erase(itr->second.begin());
		memset(addr, 0x90, size);
		return (uint32_t)addr;
	}
	if (!allocatedBlock || allocatedBlockSize < size)
	{
		if (allocatedBlock)
        {
            // remaining free space - put inside appropriate "available addresses" vector
			freeAddressesBySize[allocatedBlockSize].push_back(allocatedBlock);
		}
        allocatedBlockSize = (size + systemInfo.dwPageSize) & (systemInfo.dwPageSize - 1); // rounded up to page size
        wxASSERT(allocatedBlockSize >= size);
		allocatedBlock = VirtualAlloc(nullptr, allocatedBlockSize, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
		if (!allocatedBlock)
		{
			wxLogFatalError("Couldn't allocate memory for code");
			return 0;
		}
		allAllocatedBlocks[allocatedBlock] = allocatedBlockSize;
	}
	allocatedBlockSize -= size;
	void* ret = allocatedBlock;
	sizesByAddress[ret] = size;
	allocatedBlock = (void*)((uint32_t)allocatedBlock + size);
    memset(ret, 0x90, size);
	return reinterpret_cast<uint32_t>(ret);
}

void codeMemoryFree(void* addr)
{
	wxASSERT_MSG(sizesByAddress.contains(addr), wxString::Format("Allocated for code address 0x%X doesn't have defined size"));
	freeAddressesBySize[sizesByAddress.at(addr)].push_back(addr);
}

void codeMemoryFullFree()
{
	for (auto& [addr, size] : allAllocatedBlocks)
	{
		wxASSERT_MSG(VirtualFree(addr, 0, MEM_RELEASE), wxString::Format("Couldn't free memory at 0x%X", addr));
	}
}

uint32_t copyCode(uint32_t source, uint32_t size, bool writeJumpBack)
{
    std::vector<int> rel32Positions; // to fix calls/jumps
	int sizeReal = getRealHookSize(source, size); // TODO: skip this call and use below loop to compute effective size?
	if (sizeReal != size)
    {
		wxLogWarning("Tried to copy 0x%X code bytes at 0x%X, breaking an instruction due to too small code size (computed minimum is 0x%X)", size, source, sizeReal);
		//wxLog::FlushActive();
		size = sizeReal;
	}
	// check short jumps
    ZyanU64 runtimeAddr = (ZyanU64)source;
    ZydisDisassembledInstruction instr;
	size_t n = 0;
    bool hasShort = false;
	while (n < size && ZYAN_SUCCESS(ZydisDisassembleIntel(ZYDIS_MACHINE_MODE_LEGACY_32, source + n, reinterpret_cast<void*>(source + n), 20, &instr)))
	{
        if (instr.info.meta.branch_type == ZYDIS_BRANCH_TYPE_SHORT)
        {
			uint32_t dest = n + 2 + byte(source + n + 1);
			if (dest > source + size || dest < source) // jump outside code
			{
				hasShort = true;
			}
        }
		else if ((instr.info.meta.branch_type == ZYDIS_BRANCH_TYPE_NEAR || instr.info.meta.category == ZYDIS_CATEGORY_CALL) && (instr.info.attributes & ZYDIS_ATTRIB_IS_RELATIVE))
		{
			// to check if call is included in "branch type"
			
			// FIRES
			//wxASSERT_MSG((instr.info.meta.branch_type == ZYDIS_BRANCH_TYPE_NEAR) ^ (instr.info.meta.category == ZYDIS_CATEGORY_CALL), "Call instruction is considered as 'branch type'");
			
            auto& imm = instr.info.raw.imm;
            wxASSERT_MSG(imm[0].size == 4 * 8, wxString::Format("Expected size 4 (DWORD) immediate, got %d", imm[0].size));
            rel32Positions.push_back(n + imm[0].offset);
		}
        n += instr.info.length;
	}

	if (n < size) // Zydis error
	{
		wxLogError("Couldn't copy code from address 0x%X + 0x%X - zydis error", source, n);
		wxLog::FlushActive();
		throw std::logic_error("Zydis error");
	}
	else if (hasShort)
	{
		wxLogError("Code at 0x%X of size 0x%X has short jump leading outside", source, size);
		wxLog::FlushActive();
		throw std::logic_error("Short jump outside in code");
	}
	uint32_t newCodeSize = size + (writeJumpBack ? 5 : 0);
    uint32_t mem = codeMemoryAlloc(newCodeSize);
    // copy code to newly allocated memory
    DWORD tmp;
    VirtualProtect((void*)mem, newCodeSize, PAGE_EXECUTE_READWRITE, &tmp);
	memcpy((void*)mem, (void*)source, size);
	// write jump back
	if (writeJumpBack)
	{
        hookJumpRaw(mem + size, reinterpret_cast<void*>(source + size), nullptr);
	}
	// fix calls/jumps
    for (size_t i = 0; i < rel32Positions.size(); ++i)
    {
        sdword(mem + rel32Positions[i]) -= (mem - source);
    }
    VirtualProtect((void*)mem, newCodeSize, tmp, &tmp);
	return mem;
}

void unhookReplaceCall(uint32_t addr, std::vector<uint8_t>& restoreData)
{
	unhookCall(addr, restoreData);
}

void unhookHookFunction(uint32_t addr, std::vector<uint8_t>& restoreData, void* copiedCode)
{
	unhookCall(addr, restoreData);
	codeMemoryFree(copiedCode);
}

void removeHooks()
{
	for (auto& [id, hook]: hooks)
	{
		hook.disable();
	}
	// destructors (to free memory in some cases) will run automatically when map is destroyed on exit
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
			int ret = f(d);
			if (ret == HOOK_RETURN_FAIL)
			{
				wxLogError("Hook at 0x%X failed", hookAddr);
				wxLog::FlushActive();
			}
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

void HookData::ret(int stackNum)
{
	esp += 4; // pop return address from hookCall
    uint32_t ret = dword(esp); // backup return address
    esp += stackNum * 4; // pop stack args
    dword(esp) = ret; // restore backed up return address
}

std::function<uint32_t(HookData* d, std::function<short(int, char*, bool)>, int, char*, bool)> f = reinterpret_cast<uint32_t(*)(HookData * d, std::function<short(int, char*, bool)>, int, char*, bool)>(0x55555555);

void g()
{
	hookReplaceCall<short, 1, int, char*, bool>(0xFEDECEBE, 2, f);
}