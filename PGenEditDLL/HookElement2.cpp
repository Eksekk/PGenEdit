#include "pch.h"
#include "HookElement2.h"

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

HookElement2::HookElement2(HookElementType type) : type(type), active(false), initialized(true)
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
}

HookElementJump::HookElementJump()
{
}

HookElementJump::HookElementJump(uint32_t address, void* jumpTarget, int size)
{
}

HookElementJump::HookElementJump(uint32_t address, uint32_t jumpTarget, int size)
{
}

// CALL RAW

void HookElementCallRaw::enable(bool enable)
{
}

HookElementCallRaw::HookElementCallRaw()
{
}

HookElementCallRaw::HookElementCallRaw(uint32_t address, void* callTarget, int size)
{
}

HookElementCallRaw::HookElementCallRaw(uint32_t address, uint32_t callTarget, int size)
{
}

// CALL

void HookElementCall::enable(bool enable)
{
}

HookElementCall::HookElementCall()
{
}

HookElementCall::HookElementCall(uint32_t address, HookFunc func, int size)
{
}