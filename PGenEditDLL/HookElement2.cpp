#include "pch.h"
#include "HookElement2.h"

bool HookElement2::hasExtraData() const
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

HookElement2::~HookElement2()
{
    disable();
    destroy();
}

void HookElement2::destroy()
{
    // dummy to allow destructor call
}

void HookElement2::disable()
{
    enable(false);
}

void HookElement2::toggle()
{
    enable(!active);
}

inline bool HookElement2::isActive() const
{
    return active;
}

HookElement2::HookElement2() : type(HOOK_ELEM_TYPE_DISABLED), active(false), initialized(false)
{
}

HookElement2::HookElement2(HookElementType type) : type(type), active(false), initialized(true) // TODO: add extra "initialized" arg, this ctor is called always
{
}

// AUTOHOOK GENERIC

bool HookElementAutohook::hasExtraData() const
{
    return true;
}

void* HookElementAutohook::getExtraData() const
{
    return extraData;
}

void HookElementAutohook::enable(bool enable)
{
    if (enable && !active)
    {
        active = true;
        if (isBefore)
        {
            extraData = (void*)autohookBefore(address, func, &restorationData, size);
        }
        else
        {
            extraData = (void*)autohookAfter(address, func, &restorationData, size);
        }
    }
    else if (!enable && active)
    {
        active = false;
        unhookAutohook(address, restorationData, extraData);
    }
}

void HookElementAutohook::destroy()
{
    disable();
    if (extraData)
    {
        codeMemoryFree(extraData);
        extraData = nullptr;
    }
}

HookElementAutohook::HookElementAutohook() : address(0), extraData(nullptr), func(nullptr), size(0)// : initialized(false) // not working here
{
    initialized = false;
}

HookElementAutohook::HookElementAutohook(bool isBefore, uint32_t address, HookFunc func, int size) : isBefore(isBefore), address(address), func(func), size(size),
    extraData(nullptr), HookElement2(isBefore ? HOOK_ELEM_TYPE_AUTOHOOK_BEFORE : HOOK_ELEM_TYPE_AUTOHOOK_AFTER)
{
    initialized = true;
}

// AUTOHOOK BEFORE

HookElementAutohookBefore::HookElementAutohookBefore() : HookElementAutohook()
{
}

HookElementAutohookBefore::HookElementAutohookBefore(uint32_t address, HookFunc func, int size) : HookElementAutohook(true, address, func, size)
{
}

// AUTOHOOK AFTER

HookElementAutohookAfter::HookElementAutohookAfter()
{
}

HookElementAutohookAfter::HookElementAutohookAfter(uint32_t address, HookFunc func, int size) : HookElementAutohook(false, address, func, size)
{
}


// ASMHOOK BASE

bool HookElementAsmhookBase::hasExtraData() const
{
    return true;
}

void* HookElementAsmhookBase::getExtraData() const
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

void HookElementAsmhookBase::destroy()
{
    disable();
    if (extraData)
    {
        codeMemoryFree(extraData);
        extraData = nullptr;
    }
}

HookElementAsmhookBase::HookElementAsmhookBase()
{
}

HookElementAsmhookBase::HookElementAsmhookBase(HookElementType type, uint32_t address, const std::string& asmCode, int size)
    : HookElement2(type), address(address), asmCode(asmCode), size(size)
{
}

HookElementAsmhookBase::HookElementAsmhookBase(HookElementType type, uint32_t address, const std::string& asmCode, const CodeReplacementArgs& args, int size)
    : HookElement2(type), address(address), asmCode(SubstitutableAsmCode{asmCode, args}), size(size)
{
}

void HookElementAsmhookBefore::enable(bool enable)
{
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

// JUMP

void HookElementJump::enable(bool enable)
{
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

HookElementJump::HookElementJump() : HookElement2(HOOK_ELEM_TYPE_JUMP), address(0), jumpTarget(nullptr), size(5)
{
}

HookElementJump::HookElementJump(uint32_t address, void* jumpTarget, int size) : HookElement2(HOOK_ELEM_TYPE_JUMP), address(0), jumpTarget(jumpTarget), size(5)
{
}

HookElementJump::HookElementJump(uint32_t address, uint32_t jumpTarget, int size) : HookElement2(HOOK_ELEM_TYPE_JUMP), address(0), jumpTarget((void*)jumpTarget), size(5)
{
}

// CALL RAW

void HookElementCallRaw::enable(bool enable)
{
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

HookElementCallRaw::HookElementCallRaw() : HookElement2(HOOK_ELEM_TYPE_CALL_RAW), address(0), callTarget(nullptr), size(5)
{
}

HookElementCallRaw::HookElementCallRaw(uint32_t address, void* callTarget, int size)
    : HookElement2(HOOK_ELEM_TYPE_CALL_RAW), address(address), callTarget(callTarget), size(size)
{
}

HookElementCallRaw::HookElementCallRaw(uint32_t address, uint32_t callTarget, int size)
    : HookElement2(HOOK_ELEM_TYPE_CALL_RAW), address(address), callTarget((void*)callTarget), size(size)
{
}

// CALL

void HookElementCall::enable(bool enable)
{
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

HookElementCall::HookElementCall() : HookElement2(HOOK_ELEM_TYPE_CALL), address(0), func(nullptr), size(5)
{
}

HookElementCall::HookElementCall(uint32_t address, HookFunc func, int size)
    : HookElement2(HOOK_ELEM_TYPE_CALL), address(address), func(func), size(size)
{
}

void HookElementEraseCode::enable(bool enable)
{
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

HookElementEraseCode::HookElementEraseCode() : HookElement2(HOOK_ELEM_TYPE_ERASE_CODE), address(0), size(1)
{
}

HookElementEraseCode::HookElementEraseCode(uint32_t address, int size)
    : HookElement2(HOOK_ELEM_TYPE_ERASE_CODE), address(address), size(size)
{
}

void HookElementPatchData::enable(bool enable)
{
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
        patchBytes(address, patchData, &restorationData, false);
    }
    else if (!enable && active)
    {
        active = false;
        patchBytes(address, restorationData, nullptr, true);
    }
}

HookElementPatchData::HookElementPatchData() : HookElement2(HOOK_ELEM_TYPE_PATCH_DATA), address(0), data(ByteVector{}), size(0)
{
}

HookElementPatchData::HookElementPatchData(uint32_t address, const ByteVector& data, int size)
    : HookElement2(HOOK_ELEM_TYPE_PATCH_DATA), address(address), data(data), size(size)
{
}

HookElementPatchData::HookElementPatchData(uint32_t address, PatchDataGetBytesFunc getBytesFunc, int size)
    : HookElement2(HOOK_ELEM_TYPE_PATCH_DATA), address(address), data(getBytesFunc), size(size)
{
}

HookElementCallableFunction::HookElementCallableFunction(HookElementType type) : HookElement2(type), address(0), size(0)
{
}

HookElementCallableFunction::HookElementCallableFunction(HookElementType type, uint32_t address, int size) : HookElement2(type), address(address), size(size)
{
}

void HookElementCallableFunction::enable(bool enable)
{
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
