#include "pch.h"
#include "Hook.h"

void Hook::enable(bool enable)
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

void Hook::disable()
{
    enable(false);
}

void Hook::toggle()
{
    enable(!active);
}

void Hook::destroy()
{
    for (auto& elem : elements)
    {
        elem->destroy();
    }
}

inline bool Hook::isActive() const
{
    return active;
}

bool Hook::isFullyActive() const
{
    bool yes = active;
    for (const auto& elem : elements)
    {
        yes = !elem->isActive() ? false : yes;
    }
    return yes;
}

Hook::Hook(HookElement* el, const std::string& description, const std::vector<int> gameVersions)
    : description(description), gameVersions(gameVersions), active(false)
{
    if (gameVersions.empty())
    {
        this->gameVersions = { 6, 7, 8 };
    }
    // initializer_list in member initializer with unique_ptr breaks - tries to copy it
    elements.push_back(std::move(std::unique_ptr<HookElement>(el)));
}

Hook::Hook(std::initializer_list<HookElement*> elems, const std::string& description, const std::vector<int> gameVersions)
    : description(description), gameVersions(gameVersions), active(false)
{
    if (gameVersions.empty())
    {
        this->gameVersions = { 6, 7, 8 };
    }
    for (const auto& elem : elems)
    {
        elements.push_back(std::move(std::unique_ptr<HookElement>(elem)));
    }
}

Hook::Hook(std::vector<HookElement*>& elems, const std::string& description, const std::vector<int> gameVersions)
    : description(description), gameVersions(gameVersions), active(false)
{
    if (gameVersions.empty())
    {
        this->gameVersions = { 6, 7, 8 };
    }
    for (auto& elem : elems)
    {
        elements.push_back(std::move(std::unique_ptr<HookElement>(elem)));
    }
}

Hook::~Hook()
{
    if (active)
    {
        disable();
    }
    destroy();
}

void Hook::addElement(HookElement* element, bool autoEnable)
{
    auto p = std::unique_ptr<HookElement>(element);
    if (autoEnable)
    {
        p->enable(active);
    }
    elements.push_back(std::move(p));
}

void Hook::replaceElement(int i, HookElement* element, bool autoEnable)
{
    auto p = std::unique_ptr<HookElement>(element);
    if (autoEnable)
    {
        p->enable(active);
    }
    elements.at(i) = std::move(p);
}