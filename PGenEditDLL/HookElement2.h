#pragma once
#include "pch.h"
#include "main.h"
#include "LowLevel.h"

class HookElement2
{
protected:
    HookElementType type;
    bool active;
    std::vector<uint8_t> restorationData;
public:
    virtual bool hasExtraData() const = 0;
    virtual void* getExtraData() const = 0;
    std::vector<uint8_t> getRestorationData() const;
    HookElementType getType() const;
    virtual void enable(bool enable = true) = 0;
    virtual void destroy() = 0; // requested to free all memory etc.
    void disable();
    void toggle();
    inline bool isActive() const;
    HookElement2();
    HookElement2(HookElementType type);
    HookElement2(const HookElement2&) = default; // TODO: check (extraData)
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

class HookElementAutohook : public HookElement2
{
protected:
    uint32_t address;
    bool isBefore;
    HookFunc func;
    void* extraData;
    int size;
public:
    // Inherited via HookElement2
    bool hasExtraData() const override;
    void* getExtraData() const override;
    void enable(bool enable) override;
    void destroy() override;

    HookElementAutohook(bool isBefore, uint32_t address, HookFunc func, int size);
};