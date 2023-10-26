#include "pch.h"
#include "Hook2.h"

void Hook2::enable(bool enable)
{
    if (elements.empty())
    {
        wxLogWarning("Enabled hook '%s' with no elements", description);
    }

    for (auto& elem : elements)
    {
        elem->enable(enable);
    }
}

void Hook2::disable()
{
    enable(false);
}

void Hook2::toggle()
{
    enable(!active);
}

void Hook2::destroy()
{
    for (auto& elem : elements)
    {
        elem->destroy();
    }
}

inline bool Hook2::isActive() const
{
    return active;
}

bool Hook2::isFullyActive() const
{
    bool yes = active;
    for (const auto& elem : elements)
    {
        yes = !elem->isActive() ? false : yes;
    }
    return yes;
}

Hook2::Hook2(const HookElement2& el) : elements{ std::make_unique<HookElement2>(el) }
{
}

Hook2::Hook2(std::initializer_list<HookElement2> elems)
{
    for (const auto& elem : elems)
    {
        elements.push_back(std::make_unique<HookElement2>(elem));
    }
}

Hook2::Hook2(const std::vector<HookElement2>& elems)
{
    for (const auto& elem : elems)
    {
        elements.push_back(std::make_unique<HookElement2>(elem));
    }
}

Hook2::Hook2(HookElement2* el) : elements{ std::unique_ptr<HookElement2>(el) }
{
}

Hook2::Hook2(std::initializer_list<HookElement2*> elems)
{
    for (const auto& elem : elems)
    {
        elements.push_back(std::unique_ptr<HookElement2>(elem));
    }
}

Hook2::Hook2(const std::vector<HookElement2*>& elems)
{
    for (const auto& elem : elems)
    {
        elements.push_back(std::unique_ptr<HookElement2>(elem));
    }
}

Hook2::~Hook2()
{
    if (active)
    {
        disable();
    }
    destroy();
}

void Hook2::addElement(const HookElement2& element)
{
    elements.push_back(std::make_unique<HookElement2>(element));
}

void Hook2::addElement(HookElement2* element)
{
    elements.push_back(std::unique_ptr<HookElement2>(element));
}
