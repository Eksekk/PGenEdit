#pragma once
#include "pch.h"
#include "main.h"
#include "LowLevel.h"
#include "HookElement.h"

class Hook
{
    bool active;
    std::vector<std::unique_ptr<HookElement>> elements;
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
    Hook(HookElement* el, const std::string& description = "", const std::vector<int> gameVersions = {});
    Hook(std::initializer_list<HookElement*> elems, const std::string& description = "", const std::vector<int> gameVersions = {});
    Hook(std::vector<HookElement*>& elems, const std::string& description = "", const std::vector<int> gameVersions = {});

    Hook() = delete;
    //Hook(const Hook&) = delete; // breaks with initializer lists
    Hook(Hook&&) = default;
    ~Hook();
    Hook& operator=(const Hook&) = delete;
    Hook(const Hook&) = delete;
    // mainly for testing
    // autoEnable synchronizes new element enabled state with current hook enabled state
    void addElement(HookElement* element, bool autoEnable = true);
    void replaceElement(int i, HookElement* element, bool autoEnable = true);
};

