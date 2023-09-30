#include "pch.h"
#include "main.h"
#include "LowLevel.h"
#include <cassert>
#include <cstring>
#include "wx/debug.h"

std::unordered_map<int, Hook> hooks;
std::unordered_map<uint32_t, HookFunc> hookFuncMap;

void checkOverlap(uint32_t address, uint32_t size)
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
	if (!existsInVector(gameVersions, MMVER))
	{
		return;
	}
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
			hookCallRaw(address, reinterpret_cast<void*>(target), &restoreData, hookSize);
		}
		break;
		case HOOK_ELEM_TYPE_CALL:
		{
			hookCall(address, func, &restoreData, hookSize);
		}
		break;
		case HOOK_ELEM_TYPE_AUTOHOOK:
		{
			extraData = (void*)autohookCall(address, func, &restoreData, hookSize);
		}
		break;
		case HOOK_ELEM_TYPE_JUMP:
        {
			hookJumpRaw(address, reinterpret_cast<void*>(target), &restoreData, hookSize);
		}
		break;
		case HOOK_ELEM_TYPE_ERASE_CODE:
		{
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
        case HOOK_ELEM_TYPE_ASMHOOK_BEFORE:
        case HOOK_ELEM_TYPE_ASMHOOK_AFTER:
		{
			std::string code(patchDataStr, dataSize);
			if (!codeReplacementArgs.empty())
			{
				code = formatAsmCode(code, codeReplacementArgs);
			}
			if (type == HOOK_ELEM_TYPE_ASMHOOK_BEFORE)
            {
                extraData = asmhookBefore(address, code, &restoreData, hookSize);
			}
			else
			{
				extraData = asmhookAfter(address, code, &restoreData, hookSize);
			}
            break;
        }
		case HOOK_ELEM_TYPE_DISABLED:
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
		case HOOK_ELEM_TYPE_ASMHOOK_BEFORE:
		case HOOK_ELEM_TYPE_ASMHOOK_AFTER:
			unhookAsmhook(address, restoreData, extraData);
			break;
        case HOOK_ELEM_TYPE_DISABLED:
            break;
		default:
			wxFAIL_MSG(wxString::Format("Unknown hook type %d", (int)type));
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
	needUnprotect(false), description(""), patchUseNops(false), extraData(nullptr), gameVersions{6, 7, 8}
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
		//codeMemoryFree(extraData); // done inside unhook functions
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

HookElementBuilder& HookElementBuilder::gameVersions(const std::vector<int>& gameVersions)
{
	elem.gameVersions = gameVersions;
	return *this;
}

HookElementBuilder& HookElementBuilder::codeReplacementArgs(const CodeReplacementArgs& args)
{
	elem.codeReplacementArgs = args;
	return *this;
}

HookElement HookElementBuilder::build()
{
    // hook properties: type, address, dataSize, hookSize, target, func, needUnprotect, description, patchUseNops (only for patch data)
    // hook types: jump, call raw, call, patch data, erase code
    
	if (elem.gameVersions.empty())
	{
		wxLogWarning("Hook at 0x%X not applicable to any game", elem.address);
	}
    
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

Hook::Hook(const HookElement& element, const std::string& description) : elements({ element }), _active(false), description(description)
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

uint32_t findCode(uint32_t addr, const char* code, int len)
{
    ZydisDisassembledInstruction instr;
	int codeLen = len != -1 ? len : strlen(code); // FIXME: will fail with embedded zeros
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

uint32_t findCode(void* addr, const char* code, int len)
{
	return findCode((uint32_t)addr, code, len);
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
	checkOverlap(addr, size);
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
    checkOverlap(addr, size);
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
    checkOverlap(addr, size);

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
void unhookAutohookCall(uint32_t addr, std::vector<uint8_t>& restoreData, void*& allocatedCode)
{
	unhookCall(addr, restoreData);
	codeMemoryFree(allocatedCode);
	allocatedCode = nullptr;
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
    checkOverlap(addr, size);
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

uint32_t copyCode(uint32_t source, uint32_t size, bool writeJumpBack, uint32_t dest)
{
    std::vector<int> rel32Positions; // to fix calls/jumps
	int sizeReal = getRealHookSize(source, size, size); // TODO: skip this call and use below loop to compute effective size?
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
    uint32_t mem = dest ? dest : codeMemoryAlloc(newCodeSize);
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

void* asmhookCommon(uint32_t addr, const std::string& code, std::vector<uint8_t>* storeAt, int size, bool before)
{
    size = getRealHookSize(addr, size, 5);
    storeBytes(storeAt, addr, size);
    std::string_view codeBytes = compileAsm(code);
    uint32_t mem = codeMemoryAlloc(size + codeBytes.size() + 5); // 5 = jump size
	if (before)
	{
        copyCode((uint32_t)codeBytes.data(), codeBytes.size(), false, mem);
        copyCode(addr, size, true, mem + codeBytes.size());
	}
	else
    {
        copyCode(addr, size, false, mem);
        copyCode((uint32_t)codeBytes.data(), codeBytes.size(), false, mem + size);
		// manual jump hook, because if codeBytes one was true, it would generate jump to fasm code block, not original code
		hookJumpRaw(mem + size + codeBytes.size(), (void*)(addr + size), nullptr);
	}
	hookJumpRaw(addr, (void*)mem, nullptr);
    return (void*)mem;
}

void* asmhookBefore(uint32_t addr, const std::string& code, std::vector<uint8_t>* storeAt, int size /*= 5*/)
{
	return asmhookCommon(addr, code, storeAt, size, true);
}

void* asmhookAfter(uint32_t addr, const std::string& code, std::vector<uint8_t>* storeAt, int size /*= 5*/)
{
	return asmhookCommon(addr, code, storeAt, size, false);
}

void* asmhookBefore(uint32_t addr, const std::string& code, const CodeReplacementArgs& args, std::vector<uint8_t>* storeAt, int size = 5)
{
	return asmhookBefore(addr, formatAsmCode(code, args), storeAt, size);
}

void* asmhookAfter(uint32_t addr, const std::string& code, const CodeReplacementArgs& args, std::vector<uint8_t>* storeAt, int size = 5)
{
	return asmhookAfter(addr, formatAsmCode(code, args), storeAt, size);
}

void* asmpatch(uint32_t addr, const std::string& code, std::vector<uint8_t>* storeAt, int size, bool writeJumpBack)
{
	// asmpatch("inc eax");
	// asmpatch("add ebx, 5");
    // asmpatch("call dword [0x52525252]")
    std::string_view compiled = compileAsm(code);
    size = getRealHookSize(addr, size, size);
    storeBytes(storeAt, addr, size);
	if (compiled.size() <= size) // inline
	{
		copyCode((uint32_t)compiled.data(), compiled.size(), false, addr);
		uint32_t remaining = size - (int)compiled.size();
		if (remaining > 0)
        {
			eraseCode(addr + compiled.size(), remaining, nullptr);
		}
		return nullptr;
	}
	else // jump out
	{
		void* mem = (void*)codeMemoryAlloc(compiled.size() + (writeJumpBack ? 5 : 0));
		copyCode((uint32_t)compiled.data(), compiled.size(), false, (uint32_t)mem);
		if (writeJumpBack)
        {
            hookJumpRaw((uint32_t)mem + compiled.size(), (void*)(addr + size), nullptr);
		}
		eraseCode(addr, size, storeAt);
		hookJumpRaw(addr, mem, nullptr);
		return mem;
	}
}

void* asmpatch(uint32_t addr, const std::string& code, const CodeReplacementArgs& args, std::vector<uint8_t>* storeAt, int size, bool writeJumpBack)
{
	return asmpatch(addr, formatAsmCode(code, args), storeAt, size, writeJumpBack);
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

void unhookAsmhook(uint32_t addr, const std::vector<uint8_t>& restoreData, void*& copiedCode)
{
	codeMemoryFree(copiedCode);
	copiedCode = nullptr;
	patchBytes(addr, restoreData.data(), restoreData.size());
}

void removeHooks()
{
	for (auto& [id, hook]: hooks)
	{
		hook.disable();
	}
	// destructors (to free memory in some cases) will run automatically when map is destroyed on exit
}

static void __fastcall dispatchHook(uint32_t esp)
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
    uint32_t ret = dword(esp); // backup return address
    esp += stackNum * 4; // pop stack replacements
    dword(esp) = ret; // restore backed up return address
}

std::function<uint32_t(HookData* d, std::function<short(int, char*, bool)>, int, char*, bool)> f = reinterpret_cast<uint32_t(*)(HookData * d, std::function<short(int, char*, bool)>, int, char*, bool)>(0x55555555);

void g()
{
	hookReplaceCall<short, 1, int, char*, bool>(0xFEDECEBE, 2, f);
}

uint8_t fasmMemoryBlock[FASM_MEMORY_BLOCK_SIZE];
FASM_STATE* fasmState = reinterpret_cast<FASM_STATE*>(fasmMemoryBlock);
Fasm_Assemble fasm_Assemble; // initialized inside "init()" function in dllApi.cpp

FasmAssembleReturn fasm_Assemble_str(const std::string& src, uint8_t* memoryBlock, int memoryBlockSize, int passes, uint32_t displayPipeHandle)
{
	return fasm_Assemble(src.c_str(), memoryBlock, memoryBlockSize, passes, displayPipeHandle);
}

const std::map<FasmErrorCode, std::string> fasmErrorCodeToText =
{
	{FASMERR_FILE_NOT_FOUND, "file not found"},
	{FASMERR_ERROR_READING_FILE, "error reading file"},
	{FASMERR_INVALID_FILE_FORMAT, "invalid file format"},
	{FASMERR_INVALID_MACRO_ARGUMENTS, "invalid macro arguments"},
	{FASMERR_INCOMPLETE_MACRO, "incomplete macro"},
	{FASMERR_UNEXPECTED_CHARACTERS, "unexpected characters"},
	{FASMERR_INVALID_ARGUMENT, "invalid argument"},
	{FASMERR_ILLEGAL_INSTRUCTION, "illegal instruction"},
	{FASMERR_INVALID_OPERAND, "invalid operand"},
	{FASMERR_INVALID_OPERAND_SIZE, "invalid operand size"},
	{FASMERR_OPERAND_SIZE_NOT_SPECIFIED, "operand size not specified"},
	{FASMERR_OPERAND_SIZES_DO_NOT_MATCH, "operand sizes do not match"},
	{FASMERR_INVALID_ADDRESS_SIZE, "invalid address size"},
	{FASMERR_ADDRESS_SIZES_DO_NOT_AGREE, "address sizes do not agree"},
	{FASMERR_DISALLOWED_COMBINATION_OF_REGISTERS, "disallowed combination of registers"},
	{FASMERR_LONG_IMMEDIATE_NOT_ENCODABLE, "long immediate not encodable"},
	{FASMERR_RELATIVE_JUMP_OUT_OF_RANGE, "relative jump out of range"},
	{FASMERR_INVALID_EXPRESSION, "invalid expression"},
	{FASMERR_INVALID_ADDRESS, "invalid address"},
	{FASMERR_INVALID_VALUE, "invalid value"},
	{FASMERR_VALUE_OUT_OF_RANGE, "value out of range"},
	{FASMERR_UNDEFINED_SYMBOL, "undefined symbol"},
	{FASMERR_INVALID_USE_OF_SYMBOL, "invalid use of symbol"},
	{FASMERR_NAME_TOO_LONG, "name too long"},
	{FASMERR_INVALID_NAME, "invalid name"},
	{FASMERR_RESERVED_WORD_USED_AS_SYMBOL, "reserved word used as symbol"},
	{FASMERR_SYMBOL_ALREADY_DEFINED, "symbol already defined"},
	{FASMERR_MISSING_END_QUOTE, "missing end quote"},
	{FASMERR_MISSING_END_DIRECTIVE, "missing end directive"},
	{FASMERR_UNEXPECTED_INSTRUCTION, "unexpected instruction"},
	{FASMERR_EXTRA_CHARACTERS_ON_LINE, "extra characters on line"},
	{FASMERR_SECTION_NOT_ALIGNED_ENOUGH, "section not aligned enough"},
	{FASMERR_SETTING_ALREADY_SPECIFIED, "setting already specified"},
	{FASMERR_DATA_ALREADY_DEFINED, "data already defined"},
	{FASMERR_TOO_MANY_REPEATS, "too many repeats"},
	{FASMERR_SYMBOL_OUT_OF_SCOPE, "symbol out of scope"},
	{FASMERR_USER_ERROR, "user error"},
	{FASMERR_ASSERTION_FAILED, "assertion failed"},
};

std::string formatAsmCode(const std::string& code, const CodeReplacementArgs& replacements)
{
	static const std::regex regex("%.*?%");
	std::string newCode;
	auto iterAfterLastMatch = code.begin();
	std::sregex_iterator regexItr(code.begin(), code.end(), regex);
	std::sregex_iterator end;
	while (regexItr != end)
	{
		const std::smatch& match = *regexItr;
		const std::ssub_match& submatch = match[0];

		if (submatch.first - iterAfterLastMatch > 0)
		{
			newCode += std::string(iterAfterLastMatch, submatch.first);
		}
		// try to find parameter
		if (std::distance(submatch.first, submatch.second) <= 2) // %%
		{
			newCode += "%";
		}
		else
		{
			std::string ident = std::string(submatch.first + 1, submatch.second - 1);
            auto mapItr = replacements.find(ident);
            if (mapItr != replacements.end())
            {
                std::visit([&](auto& val)
                    {
                        if constexpr (SAME(std::string, decay_fully<decltype(val)>))
                        {
                            newCode += val;
                        }
                        else if constexpr (SAME(void, decay_fully<decltype(val)>))
                        {
                            newCode += std::to_string((uint32_t)val);
                        }
                        else
                        {
                            newCode += std::to_string(val);
                        }
                    }, mapItr->second);
            }
            else
            {
                wxLogError("Couldn't find replace placeholder for '%s' for code '%s'", ident, code);
                wxLog::FlushActive();
            }
        }
        iterAfterLastMatch = submatch.second;
		++regexItr;
	}
	newCode += std::string(iterAfterLastMatch, code.end());

	return newCode;
}

std::string_view compileAsm(const std::string& code)
{
	std::string useCode = "use32\n" + code; // 32-bit
	FasmAssembleReturn ret = fasm_Assemble(useCode.c_str(), fasmMemoryBlock, FASM_MEMORY_BLOCK_SIZE, 100, 0);
	switch (ret)
	{
	case FASM_OK:
	case FASM_WORKING:
		return std::string_view((const char*)fasmState->output_data, fasmState->output_length);
		break;
	case FASM_ERROR:
	case FASM_INVALID_PARAMETER:
	case FASM_OUT_OF_MEMORY:
	case FASM_STACK_OVERFLOW:
	case FASM_SOURCE_NOT_FOUND:
	case FASM_UNEXPECTED_END_OF_SOURCE:
	case FASM_CANNOT_GENERATE_CODE:
	case FASM_FORMAT_LIMITATIONS_EXCEDDED:
	case FASM_WRITE_FAILED:
	case FASM_INVALID_DEFINITION:
	{
		// assert to show stack traceback
		wxASSERT_MSG(false, wxString::Format("[ASM ERROR, line %d]: %s", fasmState->error_line->line_number & 0x7FFFFFFFU, fasmErrorCodeToText.at(fasmState->error_code))); // first bit is not line number, but flag
		return "";
	}
		break;
	default:
		wxLogError("Unknown FASM return code: %d", (int)ret);
        wxLog::FlushActive();
		return "";

	}
}