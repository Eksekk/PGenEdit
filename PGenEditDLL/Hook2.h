#pragma once
#include "pch.h"
#include "main.h"
#include "LowLevel.h"
#include "HookElement2.h"

class Hook2
{
    bool active;
    std::vector<std::unique_ptr<HookElement2>> elements;
public:
    std::string description;
    std::vector<int> gameVersions;
    void enable(bool enable = true);
    void disable();
    void toggle();
    void destroy();
    inline bool isActive() const;
    bool isFullyActive() const; // every element is active

    // cannot use move constructors with initializer_list
    Hook2(HookElement2* el, const std::string& description = "", const std::vector<int> gameVersions = {});
    Hook2(std::initializer_list<HookElement2*> elems, const std::string& description = "", const std::vector<int> gameVersions = {});
    Hook2(std::vector<HookElement2*>& elems, const std::string& description = "", const std::vector<int> gameVersions = {});

    Hook2() = delete;
    //Hook(const Hook&) = delete; // breaks with initializer lists
    Hook2(Hook2&&) = default;
    ~Hook2();
    Hook2& operator=(const Hook2&) = delete;
    Hook2(const Hook2&) = delete;
    // mainly for testing
    // autoEnable synchronizes new element enabled state with current hook enabled state
    void addElement(HookElement2* element, bool autoEnable = true);
    void replaceElement(int i, HookElement2* element, bool autoEnable = true);
};

