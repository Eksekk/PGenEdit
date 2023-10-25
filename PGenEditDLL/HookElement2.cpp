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

HookElement2::HookElement2() : type(HOOK_ELEM_TYPE_DISABLED), active(false)
{
}

HookElement2::HookElement2(HookElementType type) : type(type), active(false)
{
}

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
/*
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
        case HOOK_ELEM_TYPE_AUTOHOOK_BEFORE:
        {
            extraData = (void*)autohookBefore(address, func, &restoreData, hookSize);
        }
        break;
        case HOOK_ELEM_TYPE_AUTOHOOK_AFTER:
        {
            extraData = (void*)autohookAfter(address, func, &restoreData, hookSize);
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
        case HOOK_ELEM_TYPE_ASMPATCH:
        {
            if (type == HOOK_ELEM_TYPE_ASMHOOK_BEFORE)
            {
                extraData = asmhookBefore(address, asmText, codeReplacementArgs, &restoreData, hookSize);
            }
            else if (type == HOOK_ELEM_TYPE_ASMHOOK_AFTER)
            {
                extraData = asmhookAfter(address, asmText, codeReplacementArgs, &restoreData, hookSize);
            }
            else
            {
                extraData = asmpatch(address, asmText, codeReplacementArgs, &restoreData, hookSize);
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
        case HOOK_ELEM_TYPE_AUTOHOOK_BEFORE:
        case HOOK_ELEM_TYPE_AUTOHOOK_AFTER:
            unhookAutohook(address, restoreData, extraData);
            break;
        case HOOK_ELEM_TYPE_REPLACE_CALL:
        case HOOK_ELEM_TYPE_HOOKFUNCTION:
            unsetCallableFunctionHook();
            break;
        case HOOK_ELEM_TYPE_ASMHOOK_BEFORE:
        case HOOK_ELEM_TYPE_ASMHOOK_AFTER:
            unhookAsmhook(address, restoreData, extraData);
            break;
        case HOOK_ELEM_TYPE_ASMPATCH:
            unhookBytecodePatch(address, restoreData, extraData);
            break;
        case HOOK_ELEM_TYPE_DISABLED:
            break;
        default:
            wxFAIL_MSG(wxString::Format("Unknown hook type %d", (int)type));
        }
    }
*/

bool HookElementAsmhookBase::hasExtraData() const
{
    return true;
}

void* HookElementAsmhookBase::getExtraData() const
{
    return extraData;
}

/*
void HookElementAsmhookBase::enable(bool enable)
{
    if (enable && !active)
    {
        active = true;
        switch (type)
        {
        case AHT_HOOK_BEFORE:
            if (std::holds_alternative<SubstitutableAsmCode>(asmCode))
            {
                SubstitutableAsmCode& sub = std::get<SubstitutableAsmCode>(asmCode);
                extraData = asmhookBefore(address, sub.code, sub.args, &restorationData, size);
            }
            else
            {
                extraData = asmhookBefore(address, std::get<std::string>(asmCode), &restorationData, size);
            }
            break;
        case AHT_HOOK_AFTER:
            if (std::holds_alternative<SubstitutableAsmCode>(asmCode))
            {
                SubstitutableAsmCode& sub = std::get<SubstitutableAsmCode>(asmCode);
                extraData = asmhookAfter(address, sub.code, sub.args, &restorationData, size);
            }
            else
            {
                extraData = asmhookAfter(address, std::get<std::string>(asmCode), &restorationData, size);
            }
            break;
        case AHT_ASMPATCH:
            if (std::holds_alternative<SubstitutableAsmCode>(asmCode))
            {
                SubstitutableAsmCode& sub = std::get<SubstitutableAsmCode>(asmCode);
                extraData = asmhookBefore(address, sub.code, sub.args, &restorationData, size);
            }
            else
            {
                extraData = asmhookBefore(address, std::get<std::string>(asmCode), &restorationData, size);
            }
            break;
        default:
            break;

        }
    }
}*/

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
