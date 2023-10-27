#include "pch.h"
#include "HookElement2.h"

void HookElement2::makeInitialized()
{
    initialized = true;
}

bool HookElement2::isInitialized() const
{
    return initialized;
}

bool HookElement2::usesExtraData() const
{
    return false;
}

void* HookElement2::getExtraData() const
{
    return nullptr;
}

std::vector<uint8_t> HookElement2::getRestorationData() const
{
    return restorationData;
}

HookElementType HookElement2::getType() const
{
    return type;
}

void HookElement2::enable(bool enable /*= true*/)
{
    if (!initialized)
    {
        wxLogFatalError("Hook was %s without being initialized first", enable ? "enabled" : "disabled");
    }
}

HookElement2::~HookElement2()
{
    disable();
    destroy();
}

void HookElement2::destroy()
{
    // dummy to allow destructor call
    disable();
}

void HookElement2::disable()
{
    enable(false);
}

void HookElement2::toggle()
{
    enable(!active);
}

bool HookElement2::isActive() const
{
    return active;
}

HookElement2::HookElement2(HookElementType type, bool initialized) : type(type), active(false), initialized(initialized)
{
}

// AUTOHOOK GENERIC

bool HookElementAutohookBase::usesExtraData() const
{
    return true;
}

void* HookElementAutohookBase::getExtraData() const
{
    return extraData;
}

void HookElementAutohookBase::destroy()
{
    disable();
    if (extraData)
    {
        codeMemoryFree(extraData);
        extraData = nullptr;
    }
}

HookElementAutohookBase::HookElementAutohookBase(HookElementType type): HookElement2(type, false),
    address(0), extraData(nullptr), func(nullptr), size(0)// : initialized(false) // not working here
{
    
}

HookElementAutohookBase::HookElementAutohookBase(HookElementType type, uint32_t address, HookFunc func, int size) : address(address), func(func), size(size),
    extraData(nullptr), HookElement2(type, true)
{
    
}

// AUTOHOOK BEFORE

void HookElementAutohookBefore::enable(bool enable)
{
    HookElement2::enable(enable);
    if (enable && !active)
    {
        active = true;
        extraData = (void*)autohookBefore(address, func, &restorationData, size);
    }
    else if (!enable && active)
    {
        active = false;
        unhookAutohook(address, restorationData, extraData);
    }
}

HookElementAutohookBefore::HookElementAutohookBefore() : HookElementAutohookBase(HOOK_ELEM_TYPE_AUTOHOOK_BEFORE)
{
}

HookElementAutohookBefore::HookElementAutohookBefore(uint32_t address, HookFunc&& func, int size)
    : HookElementAutohookBase(HOOK_ELEM_TYPE_AUTOHOOK_BEFORE, address, std::forward<HookFunc>(func), size)
{
}

// AUTOHOOK AFTER

void HookElementAutohookAfter::enable(bool enable)
{
    HookElement2::enable(enable);
    if (enable && !active)
    {
        active = true;
        extraData = (void*)autohookAfter(address, func, &restorationData, size);
    }
    else if (!enable && active)
    {
        active = false;
        unhookAutohook(address, restorationData, extraData);
    }
}

HookElementAutohookAfter::HookElementAutohookAfter() : HookElementAutohookBase(HOOK_ELEM_TYPE_AUTOHOOK_AFTER)
{
}

HookElementAutohookAfter::HookElementAutohookAfter(uint32_t address, HookFunc&& func, int size)
    : HookElementAutohookBase(HOOK_ELEM_TYPE_AUTOHOOK_AFTER, address, std::forward<HookFunc>(func), size)
{
}


// ASMHOOK BASE

bool HookElementAsmhookBytecodehookBase::usesExtraData() const
{
    return true;
}

void* HookElementAsmhookBytecodehookBase::getExtraData() const
{
    return extraData;
}

void HookElementAsmhookBase::ensureHasNoReplacementArgs()
{
    if (std::holds_alternative<SubstitutableAsmCode>(asmCode))
    {
        asmCode = std::get<SubstitutableAsmCode>(asmCode).code;
    }
}

void HookElementAsmhookBytecodehookBase::destroy()
{
    disable();
    if (extraData)
    {
        codeMemoryFree(extraData);
        extraData = nullptr;
    }
}

HookElementAsmhookBytecodehookBase::HookElementAsmhookBytecodehookBase(HookElementType type) : HookElement2(type, false)
{
}

HookElementAsmhookBytecodehookBase::HookElementAsmhookBytecodehookBase(HookElementType type, uint32_t address, int size)
    : HookElement2(type, true), address(address), size(size)
{
}

HookElementAsmhookBase::HookElementAsmhookBase(HookElementType type) : HookElementAsmhookBytecodehookBase(type)
{
}

HookElementAsmhookBase::HookElementAsmhookBase(HookElementType type, uint32_t address, const std::string& asmCode, int size)
    : HookElementAsmhookBytecodehookBase(type, address, size), asmCode(asmCode)
{
}

HookElementAsmhookBase::HookElementAsmhookBase(HookElementType type, uint32_t address, const std::string& asmCode, const CodeReplacementArgs& args, int size)
    : HookElementAsmhookBytecodehookBase(type, address, size), asmCode(SubstitutableAsmCode{asmCode, args})
{
}

void HookElementAsmhookBefore::enable(bool enable)
{
    HookElement2::enable(enable);
    if (enable && !active)
    {
        active = true;
        if (std::holds_alternative<SubstitutableAsmCode>(asmCode))
        {
            SubstitutableAsmCode& code = std::get<SubstitutableAsmCode>(asmCode);
            extraData = asmhookBefore(address, code.code, code.args, &restorationData, size);
        }
        else
        {
            extraData = asmhookBefore(address, std::get<std::string>(asmCode), &restorationData, size);
        }
    }
    else if (!enable && active)
    {
        active = false;
        unhookAsmhook(address, restorationData, extraData);
    }
}

// ASMHOOK BEFORE

HookElementAsmhookBefore::HookElementAsmhookBefore() : HookElementAsmhookBase(HOOK_ELEM_TYPE_ASMHOOK_BEFORE, 0, "", 5)
{
}

HookElementAsmhookBefore::HookElementAsmhookBefore(uint32_t address, const std::string& asmCode, int size)
    : HookElementAsmhookBase(HOOK_ELEM_TYPE_ASMHOOK_BEFORE, address, asmCode, size)
{
}

HookElementAsmhookBefore::HookElementAsmhookBefore(uint32_t address, const std::string& asmCode, const CodeReplacementArgs& args, int size)
    : HookElementAsmhookBase(HOOK_ELEM_TYPE_ASMHOOK_BEFORE, address, asmCode, args, size)
{
}

// ASMHOOK AFTER

void HookElementAsmhookAfter::enable(bool enable)
{
    HookElement2::enable(enable);
    if (enable && !active)
    {
        active = true;
        if (std::holds_alternative<SubstitutableAsmCode>(asmCode))
        {
            SubstitutableAsmCode& code = std::get<SubstitutableAsmCode>(asmCode);
            extraData = asmhookAfter(address, code.code, code.args, &restorationData, size);
        }
        else
        {
            extraData = asmhookAfter(address, std::get<std::string>(asmCode), &restorationData, size);
        }
    }
    else if (!enable && active)
    {
        active = false;
        unhookAsmhook(address, restorationData, extraData);
    }
}

HookElementAsmhookAfter::HookElementAsmhookAfter() : HookElementAsmhookBase(HOOK_ELEM_TYPE_ASMHOOK_AFTER, 0, "", 5)
{
}

HookElementAsmhookAfter::HookElementAsmhookAfter(uint32_t address, const std::string& asmCode, int size)
    : HookElementAsmhookBase(HOOK_ELEM_TYPE_ASMHOOK_AFTER, address, asmCode, size)
{
}

HookElementAsmhookAfter::HookElementAsmhookAfter(uint32_t address, const std::string& asmCode, const CodeReplacementArgs& args, int size)
    : HookElementAsmhookBase(HOOK_ELEM_TYPE_ASMHOOK_AFTER, address, asmCode, args, size)
{
}

// ASMPATCH

void HookElementAsmpatch::enable(bool enable)
{
    HookElement2::enable(enable);
    if (enable && !active)
    {
        active = true;
        if (std::holds_alternative<SubstitutableAsmCode>(asmCode))
        {
            SubstitutableAsmCode& code = std::get<SubstitutableAsmCode>(asmCode);
            extraData = asmpatch(address, code.code, code.args, &restorationData, size, writeJumpBack);
        }
        else
        {
            assert(asmCode.index() <= 1); // <= 2 variant args
            extraData = asmpatch(address, std::get<std::string>(asmCode), &restorationData, size, writeJumpBack);
        }
    }
    else if (!enable && active)
    {
        active = false;
        unhookAsmpatch(address, restorationData, extraData);
    }
}

HookElementAsmpatch::HookElementAsmpatch() : HookElementAsmhookBase(HOOK_ELEM_TYPE_ASMPATCH, 0, "", 5), writeJumpBack(true)
{
}

HookElementAsmpatch::HookElementAsmpatch(uint32_t address, const std::string& asmCode, int size, bool writeJumpBack)
    : writeJumpBack(writeJumpBack), HookElementAsmhookBase(HOOK_ELEM_TYPE_ASMPATCH, address, asmCode, size)
{
}

HookElementAsmpatch::HookElementAsmpatch(uint32_t address, const std::string& asmCode, const CodeReplacementArgs& args, int size, bool writeJumpBack)
    : writeJumpBack(writeJumpBack), HookElementAsmhookBase(HOOK_ELEM_TYPE_ASMPATCH, address, asmCode, args, size)
{
}

HookElementBytecodehookBase::HookElementBytecodehookBase(HookElementType type) : HookElementAsmhookBytecodehookBase(type)
{
}

HookElementBytecodehookBase::HookElementBytecodehookBase(HookElementType type, uint32_t address, const std::string& bytecode, int size)
    : HookElementAsmhookBytecodehookBase(type, address, size), bytecode(bytecode)
{
}

void HookElementBytecodehookBefore::enable(bool enable)
{
    HookElement2::enable(enable);
    if (enable && !active)
    {
        active = true;
        extraData = bytecodeHookBefore(address, bytecode, &restorationData, size);
    }
    else if (!enable && active)
    {
        active = false;
        unhookBytecodeHook(address, restorationData, extraData);
    }
}

HookElementBytecodehookBefore::HookElementBytecodehookBefore() : HookElementBytecodehookBase(HOOK_ELEM_TYPE_BYTECODEHOOK_BEFORE)
{
}

HookElementBytecodehookBefore::HookElementBytecodehookBefore(uint32_t address, const std::string& bytecode, int size)
    : HookElementBytecodehookBase(HOOK_ELEM_TYPE_BYTECODEHOOK_BEFORE, address, bytecode, size)
{
}

void HookElementBytecodehookAfter::enable(bool enable)
{
    HookElement2::enable(enable);
    if (enable && !active)
    {
        active = true;
        extraData = bytecodeHookAfter(address, bytecode, &restorationData, size);
    }
    else if (!enable && active)
    {
        active = false;
        unhookBytecodeHook(address, restorationData, extraData);
    }
}

HookElementBytecodehookAfter::HookElementBytecodehookAfter() : HookElementBytecodehookBase(HOOK_ELEM_TYPE_BYTECODEHOOK_AFTER)
{
}

HookElementBytecodehookAfter::HookElementBytecodehookAfter(uint32_t address, const std::string& bytecode, int size)
    : HookElementBytecodehookBase(HOOK_ELEM_TYPE_BYTECODEHOOK_AFTER, address, bytecode, size)
{
}

void HookElementBytecodepatch::enable(bool enable)
{
    HookElement2::enable(enable);
    if (enable && !active)
    {
        active = true;
        extraData = bytecodePatch(address, bytecode, &restorationData, size, writeJumpBack);
    }
    else if (!enable && active)
    {
        active = false;
        unhookBytecodePatch(address, restorationData, extraData);
    }
}

HookElementBytecodepatch::HookElementBytecodepatch() : HookElementBytecodehookBase(HOOK_ELEM_TYPE_BYTECODEPATCH)
{
}

HookElementBytecodepatch::HookElementBytecodepatch(uint32_t address, const std::string& bytecode, int size, bool writeJumpBack)
    : HookElementBytecodehookBase(HOOK_ELEM_TYPE_BYTECODEPATCH, address, bytecode, size), writeJumpBack(writeJumpBack)
{
}

bool HookElementAsmproc::usesExtraData() const
{
    return true;
}

void* HookElementAsmproc::getExtraData() const
{
    return extraData;
}

void HookElementAsmproc::enable(bool enable)
{
    HookElement2::enable(enable);
    if (enable && !active)
    {
        active = true;
        if (const std::string* str = std::get_if<std::string>(&asmCode))
        {
            extraData = (void*)asmproc(*str).data();
        }
        else if (const SubstitutableAsmCode* code = std::get_if<SubstitutableAsmCode>(&asmCode))
        {
            extraData = (void*)asmproc(code->code, code->args).data();
        }
    }
    else if (!enable && active)
    {
        active = false;
        codeMemoryFree(extraData);
    }
}

HookElementAsmproc::HookElementAsmproc() : HookElement2(HOOK_ELEM_TYPE_ASMPROC, false)
{
}

HookElementAsmproc::HookElementAsmproc(const std::string& asmCode) : HookElement2(HOOK_ELEM_TYPE_ASMPROC, true), asmCode(asmCode)
{
}

HookElementAsmproc::HookElementAsmproc(const std::string& asmCode, const CodeReplacementArgs& args)
    : HookElement2(HOOK_ELEM_TYPE_ASMPROC, true), asmCode(SubstitutableAsmCode{ asmCode, args })
{
}

bool HookElementBytecodeproc::usesExtraData() const
{
    return true;
}

void* HookElementBytecodeproc::getExtraData() const
{
    return extraData;
}

void HookElementBytecodeproc::enable(bool enable)
{
    HookElement2::enable(enable);
    if (enable && !active)
    {
        active = true;
        extraData = (void*)bytecodeproc(bytecode).data();
    }
    else if (!enable && active)
    {
        active = false;
        codeMemoryFree(extraData);
    }
}

HookElementBytecodeproc::HookElementBytecodeproc() : HookElement2(HOOK_ELEM_TYPE_BYTECODEPROC, false)
{
}

HookElementBytecodeproc::HookElementBytecodeproc(const std::string& bytecode) : HookElement2(HOOK_ELEM_TYPE_BYTECODEPROC, true), bytecode(bytecode)
{
}

// JUMP

void HookElementJump::enable(bool enable)
{
    HookElement2::enable(enable);
    if (enable && !active)
    {
        active = true;
        hookJumpRaw(address, jumpTarget, &restorationData, size);
    }
    else if (!enable && active)
    {
        active = false;
        unhookJumpRaw(address, restorationData);
    }
}

HookElementJump::HookElementJump() : HookElement2(HOOK_ELEM_TYPE_JUMP, false), address(0), jumpTarget(nullptr), size(5)
{
}

HookElementJump::HookElementJump(uint32_t address, void* jumpTarget, int size)
    : HookElement2(HOOK_ELEM_TYPE_JUMP, true), address(address), jumpTarget(jumpTarget), size(size)
{
}

HookElementJump::HookElementJump(uint32_t address, uint32_t jumpTarget, int size)
    : HookElementJump(address, (void*)jumpTarget, size)
{
}

// CALL RAW

void HookElementCallRaw::enable(bool enable)
{
    HookElement2::enable(enable);
    if (enable && !active)
    {
        active = true;
        hookCallRaw(address, callTarget, &restorationData, size);
    }
    else if (!enable && active)
    {
        active = false;
        unhookCallRaw(address, restorationData);
    }
}

HookElementCallRaw::HookElementCallRaw() : HookElement2(HOOK_ELEM_TYPE_CALL_RAW, false), address(0), callTarget(nullptr), size(5)
{
}

HookElementCallRaw::HookElementCallRaw(uint32_t address, void* callTarget, int size)
    : HookElement2(HOOK_ELEM_TYPE_CALL_RAW, true), address(address), callTarget(callTarget), size(size)
{
}

HookElementCallRaw::HookElementCallRaw(uint32_t address, uint32_t callTarget, int size)
    : HookElementCallRaw(address, (void*)callTarget, size)
{
}

// CALL

void HookElementCall::enable(bool enable)
{
    HookElement2::enable(enable);
    if (enable && !active)
    {
        active = true;
        hookCall(address, func, &restorationData, size);
    }
    else if (!enable && active)
    {
        active = false;
        unhookCall(address, restorationData);
    }
}

HookElementCall::HookElementCall() : HookElement2(HOOK_ELEM_TYPE_CALL, false), address(0), func(nullptr), size(5)
{
}

HookElementCall::HookElementCall(uint32_t address, HookFunc func, int size)
    : HookElement2(HOOK_ELEM_TYPE_CALL, true), address(address), func(func), size(size)
{
}

void HookElementEraseCode::enable(bool enable)
{
    HookElement2::enable(enable);
    if (enable && !active)
    {
        active = true;
        eraseCode(address, size, &restorationData);
    }
    else if (!enable && active)
    {
        active = false;
        patchBytes(address, restorationData.data(), restorationData.size(), nullptr, true);
    }
}

HookElementEraseCode::HookElementEraseCode() : HookElement2(HOOK_ELEM_TYPE_ERASE_CODE, false), address(0), size(1)
{
}

HookElementEraseCode::HookElementEraseCode(uint32_t address, int size)
    : HookElement2(HOOK_ELEM_TYPE_ERASE_CODE, true), address(address), size(size)
{
}

void HookElementPatchData::enable(bool enable)
{
    HookElement2::enable(enable);
    if (enable && !active)
    {
        active = true;
        ByteVector patchData;
        if (const ByteVector* vec = std::get_if<ByteVector>(&data))
        {
            patchData = *vec;
        }
        else if (const PatchDataGetBytesFunc* func = std::get_if<PatchDataGetBytesFunc>(&data))
        {
            patchData = (*func)(address); // probably overengineering
        }
        patchBytes(address, patchData, &restorationData, useNops);
    }
    else if (!enable && active)
    {
        active = false;
        patchBytes(address, restorationData, nullptr, false); // here patch data might not be code, just in case don't use nops
    }
}

HookElementPatchData::HookElementPatchData() : HookElement2(HOOK_ELEM_TYPE_PATCH_DATA, false), address(0), data(ByteVector{})
{
}

HookElementPatchData::HookElementPatchData(uint32_t address, const ByteVector& data, bool useNops)
    : HookElement2(HOOK_ELEM_TYPE_PATCH_DATA, true), address(address), data(data), useNops(useNops)
{
    
}

HookElementPatchData::HookElementPatchData(uint32_t address, PatchDataGetBytesFunc getBytesFunc, bool useNops)
    : HookElement2(HOOK_ELEM_TYPE_PATCH_DATA, true), address(address), data(getBytesFunc), useNops(useNops)
{
}

HookElementPatchData::HookElementPatchData(uint32_t address, const std::string& data, bool useNops)
    : HookElement2(HOOK_ELEM_TYPE_PATCH_DATA, true), address(address), useNops(useNops)
{
    ByteVector v;
    std::ranges::transform(data, std::back_insert_iterator(v), [](char c) { return std::bit_cast<uint8_t>(c); });
    this->data = std::move(v);
}

HookElementCallableFunction::HookElementCallableFunction(HookElementType type) : HookElement2(type, false), address(0), size(0)
{
}

HookElementCallableFunction::HookElementCallableFunction(HookElementType type, uint32_t address, int size) : HookElement2(type, true), address(address), size(size)
{
}

void HookElementCallableFunction::enable(bool enable)
{
    HookElement2::enable(enable);
    wxASSERT_MSG((bool)setCallableFunctionHook, "Callable function hook: set hook function not provided");
    if (enable && !active)
    {
        active = true;
        setCallableFunctionHook();
    }
    else if (!enable && active)
    {
        active = false;
        unsetCallableFunctionHook();
    }
}

HookElementReplaceCall::HookElementReplaceCall() : HookElementCallableFunction(HOOK_ELEM_TYPE_REPLACE_CALL)
{
}

bool HookElementHookFunction::usesExtraData() const
{
    return true;
}

void* HookElementHookFunction::getExtraData() const
{
    return extraData;
}

HookElementHookFunction::HookElementHookFunction() : HookElementCallableFunction(HOOK_ELEM_TYPE_HOOKFUNCTION, 0, 0)
{
}
