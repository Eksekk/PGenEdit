#pragma once
#include "pch.h"
#include "main.h"
#include "LowLevel.h"
#include "HookElement2.h"

class Hook2
{
    bool active;
public:
    std::vector<std::unique_ptr<HookElement2>> elements;
    std::string description;
    void enable(bool enable = true);
    void disable();
    void toggle();
    void destroy();
    inline bool isActive() const;
    bool isFullyActive() const; // every element is active

    // cannot use move constructors with initializer_list
    Hook2(HookElement2* el);
    Hook2(std::initializer_list<HookElement2*> elems);
    Hook2(std::vector<HookElement2*>& elems);

    Hook2() = delete;
    //Hook(const Hook&) = delete; // breaks with initializer lists
    Hook2(Hook2&&) = default;
    ~Hook2();
    Hook2& operator=(const Hook2&) = delete;
    Hook2(const Hook2&) = delete;

    void addElement(HookElement2* element);
};

