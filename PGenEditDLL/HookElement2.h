#pragma once
#include "pch.h"
#include "main.h"
#include "LowLevel.h"

#define makeAliases(name)\
using name = HookElement ## name;\
using HKE_ ## name = HookElement ## name;\
namespace hooks\
{\
    using name = HookElement ## name;\
    using HKE_ ## name = HookElement ## name;\
}

class HookElement2
{
protected:
    HookElementType type;
    bool active;
    std::vector<uint8_t> restorationData;
    bool initialized; // for debugging, probably need no arg constructor, but then the element is not initialized fully
    // make sure than when enabling it is initialized
public:
    void isInitialized() const;
    virtual bool hasExtraData() const = 0;
    virtual void* getExtraData() const = 0;
    std::vector<uint8_t> getRestorationData() const; // intentionally returns a copy
    HookElementType getType() const;
    virtual void enable(bool enable = true) = 0;
    virtual void destroy() = 0; // requested to free all memory etc.
    void disable();
    void toggle();
    bool isActive() const;
    HookElement2(HookElementType type, bool initialized);
    HookElement2(const HookElement2&) = delete; // TODO: implement proper copy ctor
    HookElement2(HookElement2&&) = default;
    HookElement2& operator=(const HookElement2& elem) = default;
    HookElement2& operator=(HookElement2&& elem) = default;
    virtual ~HookElement2();
    // constructor parameters (type will be set automatically):
    // call raw: address, func, size
    // call: address, func, size
    // jump: address, jumpAddress, size
    // patch data: (address, dataPtr, dataSize, patchSize, patchUseNopInstructions [optional]) OR (address, std::string/std::string_view data, patchSize, patchUseNopInstructions [optional])
    // erase code: address, size
    // autohook: address, func, size
    // asmhooks/asmpatch: (address, asmCode, size) OR (address, asmCode, codeReplacementArgs, size)
    // ! in above, a method to change code replacement args!
    // bytecodehooks/bytecodepatch: (address, bytecodePtr, bytecodeSize, hookSize) OR (address, std::string/std::string_view bytecode, hookSize)
    // hookfunction/hookReplaceCall: address, func, size
    // asmproc: code OR (code, codeReplacementArgs), provide method to get generated code address (also in all other asmhooks/asmpatches)
};

// all: description

// each stores restoration data (defined in base class) and optional extra data field

class HookElementAutohookBase : public HookElement2
{
protected:
    uint32_t address;
    HookFunc func;
    void* extraData;
    int size;
    using HookElement2::initialized; // allow using protected member of superclass (HookElement2) in subclass (HookElementAutohookBefore)?? TODO: test it
public:
    // Inherited via HookElement2
    bool hasExtraData() const override;
    void* getExtraData() const override;
    void destroy() override;
protected:
    // constructors protected to disallow creating instances of this class
    HookElementAutohookBase(HookElementType type);
    HookElementAutohookBase(HookElementType type, uint32_t address, HookFunc func, int size = 5);
};

class HookElementAutohookBefore : public HookElementAutohookBase
{
public:
    void enable(bool enable) override;
    HookElementAutohookBefore();
    HookElementAutohookBefore(uint32_t address, HookFunc func, int size = 5);
};

makeAliases(AutohookBefore);

class HookElementAutohookAfter : public HookElementAutohookBase
{
public:
    void enable(bool enable) override;
    HookElementAutohookAfter();
    HookElementAutohookAfter(uint32_t address, HookFunc func, int size = 5);
};

makeAliases(AutohookAfter);

struct SubstitutableAsmCode
{
    std::string code;
    CodeReplacementArgs args;
};

using AsmCodeVariant = std::variant<std::string, SubstitutableAsmCode>;

class HookElementAsmhookBase : public HookElement2
{
protected:
    uint32_t address;
    AsmCodeVariant asmCode;
    void* extraData;
    int size;
public:
    // Inherited via HookElement2
    bool hasExtraData() const override;
    void* getExtraData() const override;
    void destroy() override;
    void ensureHasNoReplacementArgs();
protected:
    // constructors protected to disallow creating instances of this class
    HookElementAsmhookBase(HookElementType type);
    HookElementAsmhookBase(HookElementType type, uint32_t address, const std::string& asmCode, int size = 5);
    HookElementAsmhookBase(HookElementType type, uint32_t address, const std::string& asmCode, const CodeReplacementArgs& args, int size = 5);
};

class HookElementAsmhookBefore : public HookElementAsmhookBase
{
public:
    // Inherited via HookElementAsmhookBase
    void enable(bool enable) override;

    HookElementAsmhookBefore();
    HookElementAsmhookBefore(uint32_t address, const std::string& asmCode, int size = 5);
    HookElementAsmhookBefore(uint32_t address, const std::string& asmCode, const CodeReplacementArgs& args, int size = 5);
};

makeAliases(AsmhookBefore);

class HookElementAsmhookAfter : public HookElementAsmhookBase
{
public:
    // Inherited via HookElementAsmhookBase
    void enable(bool enable) override;

    HookElementAsmhookAfter();
    HookElementAsmhookAfter(uint32_t address, const std::string& asmCode, int size = 5);
    HookElementAsmhookAfter(uint32_t address, const std::string& asmCode, const CodeReplacementArgs& args, int size = 5);
};

makeAliases(AsmhookAfter);

class HookElementAsmpatch : public HookElementAsmhookBase
{
protected:
    bool writeJumpBack;
public:
    // Inherited via HookElementAsmhookBase
    void enable(bool enable) override;

    HookElementAsmpatch();
    HookElementAsmpatch(uint32_t address, const std::string& asmCode, int size = 5, bool writeJumpBack = true);
    HookElementAsmpatch(uint32_t address, const std::string& asmCode, const CodeReplacementArgs& args, int size = 5, bool writeJumpBack = true);
};

makeAliases(Asmpatch);

class HookElementAsmproc : public HookElement2
{
    void* extraData;
    AsmCodeVariant asmCode;
public:
    bool hasExtraData() const override;
    void* getExtraData() const override;
    void enable(bool enable) override;

    HookElementAsmproc();
    HookElementAsmproc(const std::string& asmCode);
    HookElementAsmproc(const std::string& asmCode, const CodeReplacementArgs& args);
};

makeAliases(Asmproc);

class HookElementCall : public HookElement2
{
protected:
    uint32_t address;
    HookFunc func;
    int size;
public:
    void enable(bool enable) override;

    HookElementCall();
    HookElementCall(uint32_t address, HookFunc func, int size = 5);
};

makeAliases(Call);

class HookElementCallRaw : public HookElement2
{
protected:
    uint32_t address;
    void* callTarget;
    int size;
public:
    void enable(bool enable) override;

    HookElementCallRaw();
    HookElementCallRaw(uint32_t address, void* callTarget, int size = 5);
    HookElementCallRaw(uint32_t address, uint32_t callTarget, int size = 5);
};

makeAliases(CallRaw);

class HookElementJump : public HookElement2
{
protected:
    uint32_t address;
    void* jumpTarget;
    int size;
public:
    void enable(bool enable) override;

    HookElementJump();
    HookElementJump(uint32_t address, void* jumpTarget, int size = 5);
    HookElementJump(uint32_t address, uint32_t jumpTarget, int size = 5);
};

makeAliases(Jump);

class HookElementEraseCode : public HookElement2
{
protected:
    uint32_t address;
    int size;
public:
    void enable(bool enable) override;

    HookElementEraseCode();
    HookElementEraseCode(uint32_t address, int size = 1); // without size argument replaces single instruction, as in MMExt
};

makeAliases(EraseCode);

using PatchDataGetBytesFunc = std::function<ByteVector(uint32_t address)>;

class HookElementPatchData : public HookElement2
{
protected:
    uint32_t address;
    int size;
    std::variant<ByteVector, PatchDataGetBytesFunc> data;
public:
    void enable(bool enable) override;

    HookElementPatchData();
    HookElementPatchData(uint32_t address, const ByteVector& data, int size);
    HookElementPatchData(uint32_t address, PatchDataGetBytesFunc getBytesFunc, int size);
};

makeAliases(PatchData);

class HookElementCallableFunction : HookElement2
{
protected:
    uint32_t address;
    int size;
    std::function<void()> setCallableFunctionHook = nullptr, unsetCallableFunctionHook = nullptr;
    // constructors protected to disallow creating instances of this class
    HookElementCallableFunction(HookElementType type);
    HookElementCallableFunction(HookElementType type, uint32_t address, int size = 5);
    void enable(bool enable) override;
};

class HookElementReplaceCall : HookElementCallableFunction
{
public:
    HookElementReplaceCall();
    template<typename ReturnType, int cc, typename... Args>
    void setCallableFunctionHookFunc(CallableFunctionHookFunc<ReturnType, Args...> func)
    {
        constexpr int stackNum = sizeof...(Args) - std::clamp(cc, 0, 2);
        setCallableFunctionHook = [=]()
            {
                hookReplaceCall<ReturnType, cc>(address, stackNum, func, &restorationData, 5);
            };
        unsetCallableFunctionHook = [=]()
            {
                unhookReplaceCall(address, restorationData);
            };
    }
    template<typename ReturnType, int cc, typename... Args>
    HookElementReplaceCall(uint32_t address, CallableFunctionHookFunc<ReturnType, Args...> func) : HookElementCallableFunction(HOOK_ELEM_TYPE_REPLACE_CALL, address, 5)
    {
        setCallableFunctionHookFunc<ReturnType, cc>(func);
    }
};

makeAliases(ReplaceCall);

class HookElementHookFunction : HookElementCallableFunction
{
    void* extraData;
public:
    bool hasExtraData() const override;
    void* getExtraData() const override;
    HookElementHookFunction();
    template<typename ReturnType, int cc, typename... Args>
    void setCallableFunctionHookFunc(CallableFunctionHookFunc<ReturnType, Args...> func)
    {
        constexpr int stackNum = sizeof...(Args) - std::clamp(cc, 0, 2);
        setCallableFunctionHook = [=]()
            {
                extraData = hookFunction<ReturnType, cc>(address, stackNum, func, &restorationData, 5);
            };
        unsetCallableFunctionHook = [=]()
            {
                unhookHookFunction(address, restorationData, extraData);
            };
    }
    template<typename ReturnType, int cc, typename... Args>
    HookElementHookFunction(uint32_t address, CallableFunctionHookFunc<ReturnType, Args...> func, int size = 5)
        : HookElementCallableFunction(HOOK_ELEM_TYPE_HOOKFUNCTION, address, size)
    {
        setCallableFunctionHookFunc<ReturnType, cc>(func);
    }
};

makeAliases(HookFunction);

#undef makeAliases