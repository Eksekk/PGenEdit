#pragma once
#include "pch.h"
#include "main.h"
#include "LowLevel.h"

#define makeAliases(name)\
using name = HookElement ## name;\
using HKE_ ## name = HookElement ## name;\
namespace hk\
{\
    using name = name;\
}

#define makeAliasesCallableFuncHook(name)\
using name = HookElement ## name;\
using HKE_ ## name = HookElement ## name;\
namespace hk\
{\
    using name = name;\
}

class HookElement
{
protected:
    HookElementType type;
    bool active;
    std::vector<uint8_t> restorationData;
    bool initialized; // for debugging, probably need no arg constructor, but then the element is not initialized fully
    // make sure than when enabling it is initialized
    void makeInitialized();
public:
    bool isInitialized() const;
    virtual bool usesExtraData() const;
    virtual void* getExtraData() const;
    std::vector<uint8_t> getRestorationData() const; // intentionally returns a copy
    HookElementType getType() const;
    virtual void enable(bool enable = true) = 0;
    virtual void destroy(); // requested to free all memory etc.
    void disable();
    void toggle();
    bool isActive() const;
    HookElement(HookElementType type, bool initialized);
    HookElement(const HookElement&) = delete; // TODO: implement proper copy ctor
    HookElement(HookElement&&) = default;
    HookElement& operator=(const HookElement& elem) = delete;
    HookElement& operator=(HookElement&& elem) = default;
    virtual ~HookElement();
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

class HookElementAutohookBase : public HookElement
{
protected:
    uint32_t address;
    HookFunc func;
    void* extraData;
    int size;
    using HookElement::initialized; // allow using protected member of superclass (HookElement) in subclass (HookElementAutohookBefore)?? TODO: test it
public:
    // Inherited via HookElement
    bool usesExtraData() const override;
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
    // using rvalue reference here, because copy will be made in superclass constructor
    HookElementAutohookBefore(uint32_t address, HookFunc&& func, int size = 5);
};

makeAliases(AutohookBefore);

class HookElementAutohookAfter : public HookElementAutohookBase
{
public:
    void enable(bool enable) override;
    HookElementAutohookAfter();
    // using rvalue reference here, because copy will be made in superclass constructor
    HookElementAutohookAfter(uint32_t address, HookFunc&& func, int size = 5);
};

makeAliases(AutohookAfter);

struct SubstitutableAsmCode
{
    std::string code;
    CodeReplacementArgs args;
};

using AsmCodeVariant = std::variant<std::string, SubstitutableAsmCode>;

class HookElementAsmhookBytecodehookBase : public HookElement
{
protected:
    uint32_t address;
    void* extraData;
    int size;
public:
    // Inherited via HookElement
    bool usesExtraData() const override;
    void* getExtraData() const override;
    void destroy() override;

    HookElementAsmhookBytecodehookBase(HookElementType type);
    HookElementAsmhookBytecodehookBase(HookElementType type, uint32_t address, int size = 5);
};

class HookElementAsmhookBase : public HookElementAsmhookBytecodehookBase
{
protected:
    AsmCodeVariant asmCode;
public:
    void ensureHasNoReplacementArgs();
    // void enable(bool enable) override = 0; // make this class abstract; not needed?

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
    HookElementAsmpatch(uint32_t address, const std::string& asmCode, int size = 1, bool writeJumpBack = true);
    HookElementAsmpatch(uint32_t address, const std::string& asmCode, const CodeReplacementArgs& args, int size = 1, bool writeJumpBack = true);
};

makeAliases(Asmpatch);

class HookElementBytecodeHookBase : public HookElementAsmhookBytecodehookBase
{
protected:
    std::string bytecode;
    // constructors protected to disallow creating instances of this class
    HookElementBytecodeHookBase(HookElementType type);
    HookElementBytecodeHookBase(HookElementType type, uint32_t address, const std::string& bytecode, int size = 5);
};

class HookElementBytecodeHookBefore : public HookElementBytecodeHookBase
{
public:
    // Inherited via HookElementBytecodeHookBase
    void enable(bool enable) override;

    HookElementBytecodeHookBefore();
    HookElementBytecodeHookBefore(uint32_t address, const std::string& bytecode, int size = 5);
};

makeAliases(BytecodeHookBefore);

class HookElementBytecodeHookAfter : public HookElementBytecodeHookBase
{
public:
    // Inherited via HookElementBytecodeHookBase
    void enable(bool enable) override;

    HookElementBytecodeHookAfter();
    HookElementBytecodeHookAfter(uint32_t address, const std::string& bytecode, int size = 5);
};

makeAliases(BytecodeHookAfter);

class HookElementBytecodePatch : public HookElementBytecodeHookBase
{
protected:
    bool writeJumpBack;
public:
    // Inherited via HookElementBytecodeHookBase
    void enable(bool enable) override;

    HookElementBytecodePatch();
    HookElementBytecodePatch(uint32_t address, const std::string& bytecode, int size = 5, bool writeJumpBack = true);
};

makeAliases(BytecodePatch);

class HookElementAsmproc : public HookElement
{
    void* extraData;
    AsmCodeVariant asmCode;
public:
    bool usesExtraData() const override;
    void* getExtraData() const override;
    void enable(bool enable) override;

    HookElementAsmproc();
    HookElementAsmproc(const std::string& asmCode);
    HookElementAsmproc(const std::string& asmCode, const CodeReplacementArgs& args);
};

makeAliases(Asmproc);

class HookElementBytecodeProc : public HookElement
{
    void* extraData;
    std::string bytecode;
public:
    bool usesExtraData() const override;
    void* getExtraData() const override;
    void enable(bool enable) override;

    HookElementBytecodeProc();
    HookElementBytecodeProc(const std::string& bytecode);
};

makeAliases(BytecodeProc);

class HookElementCall : public HookElement
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

class HookElementCallRaw : public HookElement
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

class HookElementJump : public HookElement
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

class HookElementEraseCode : public HookElement
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

class HookElementPatchData : public HookElement
{
protected:
    uint32_t address;
    std::variant<ByteVector, PatchDataGetBytesFunc> data;
    bool useNops; // patching code
public:
    void enable(bool enable) override;

    HookElementPatchData();
    HookElementPatchData(uint32_t address, const ByteVector& data, bool useNops = false);
    HookElementPatchData(uint32_t address, const std::string& data, bool useNops = false);
    HookElementPatchData(uint32_t address, PatchDataGetBytesFunc getBytesFunc, bool useNops = false);
};

makeAliases(PatchData);

class HookElementCallableFunction : public HookElement
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

class HookElementReplaceCall : public HookElementCallableFunction
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
    static HookElementReplaceCall* create(uint32_t address, CallableFunctionHookFunc<ReturnType, Args...> func)
    {
        HookElementReplaceCall* elem = new HookElementReplaceCall();
        elem->address = address;
        elem->size = 5;
        elem->setCallableFunctionHookFunc<ReturnType, cc, Args...>(func);
        elem->makeInitialized();
        // create default-constructed instance
        // set hook function and other params
        // set initialized: HookElement::setInitialized(bool initialized)
        // return the instance
        return elem;
    }
private: // private to enforce no accidental "new" operator usage

    // COMMENTED OUT, because this constructor is preferred to "no args" constructor

    /*template<typename ReturnType, int cc, typename... Args>
    HookElementReplaceCall(uint32_t address, CallableFunctionHookFunc<ReturnType, Args...> func) : HookElementCallableFunction(HOOK_ELEM_TYPE_REPLACE_CALL, address, 5)
    {
        setCallableFunctionHookFunc<ReturnType, cc, Args...>(func);
    }*/
};

makeAliases(ReplaceCall);

namespace hk
{
    template<typename ReturnType, typename... Args>
    using ReplaceCallHookOrigFunc = ::CallableFunctionHookOrigFunc<ReturnType, Args...>;
    template<typename ReturnType, typename... Args>
    using ReplaceCallHookFunc = ::CallableFunctionHookFunc<ReturnType, Args...>;
}

class HookElementHookFunction : public HookElementCallableFunction
{
    void* extraData;
public:
    bool usesExtraData() const override;
    void* getExtraData() const override;
    HookElementHookFunction();
    template<typename ReturnType, int cc, typename... Args>
    void setCallableFunctionHookFunc(CallableFunctionHookFunc<ReturnType, Args...> func)
    {
        constexpr int stackNum = sizeof...(Args) - std::clamp(cc, 0, 2);
        setCallableFunctionHook = [=]()
            {
                extraData = (void*)hookFunction<ReturnType, cc>(address, stackNum, func, &restorationData, 5);
            };
        unsetCallableFunctionHook = [=]()
            {
                unhookHookFunction(address, restorationData, extraData);
            };
    }

    // static function to work around templated constructor problems (can't specify template args)
    template<typename ReturnType, int cc, typename... Args>
    static HookElementHookFunction* create(uint32_t address, CallableFunctionHookFunc<ReturnType, Args...> func, int size = 5)
    {
        HookElementHookFunction* elem = new HookElementHookFunction();
        elem->address = address;
        elem->size = size;
        elem->setCallableFunctionHookFunc<ReturnType, cc, Args...>(func);
        elem->makeInitialized();
        // create default-constructed instance
        // set hook function and other params
        // set initialized: HookElement::setInitialized(bool initialized)
        // return the instance
        return elem;
    }
private: // private to enforce no accidental "new" operator usage

    // COMMENTED OUT, because this constructor is preferred to "no args" constructor

    /*template<typename ReturnType, int cc, typename... Args>
    HookElementHookFunction(uint32_t address, CallableFunctionHookFunc<ReturnType, Args...> func, int size = 5)
        : HookElementCallableFunction(HOOK_ELEM_TYPE_HOOKFUNCTION, address, size)
    {
        setCallableFunctionHookFunc<ReturnType, cc>(func);
    }*/
};

namespace hk
{
    template<typename ReturnType, typename... Args>
    using HookFunctionHookOrigFunc = ::CallableFunctionHookOrigFunc<ReturnType, Args...>;
    template<typename ReturnType, typename... Args>
    using HookFunctionHookFunc = ::CallableFunctionHookFunc<ReturnType, Args...>;
}

makeAliases(HookFunction);

#undef makeAliases