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

Hook2::Hook2(HookElement2* el, const std::string& description, const std::vector<int> gameVersions)
    : description(description), gameVersions(gameVersions), active(false)
{
    if (gameVersions.empty())
    {
        this->gameVersions = { 6, 7, 8 };
    }
    // initializer_list in member initializer with unique_ptr breaks - tries to copy it
    elements.push_back(std::move(std::unique_ptr<HookElement2>(el)));
}

Hook2::Hook2(std::initializer_list<HookElement2*> elems, const std::string& description, const std::vector<int> gameVersions)
    : description(description), gameVersions(gameVersions), active(false)
{
    if (gameVersions.empty())
    {
        this->gameVersions = { 6, 7, 8 };
    }
    for (const auto& elem : elems)
    {
        elements.push_back(std::move(std::unique_ptr<HookElement2>(elem)));
    }
}

Hook2::Hook2(std::vector<HookElement2*>& elems, const std::string& description, const std::vector<int> gameVersions)
    : description(description), gameVersions(gameVersions), active(false)
{
    if (gameVersions.empty())
    {
        this->gameVersions = { 6, 7, 8 };
    }
    for (auto& elem : elems)
    {
        elements.push_back(std::move(std::unique_ptr<HookElement2>(elem)));
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

void Hook2::addElement(HookElement2* element, bool autoEnable)
{
    auto p = std::unique_ptr<HookElement2>(element);
    if (autoEnable)
    {
        p->enable(active);
    }
    elements.push_back(std::move(p));
}

void Hook2::replaceElement(int i, HookElement2* element, bool autoEnable)
{
    auto p = std::unique_ptr<HookElement2>(element);
    if (autoEnable)
    {
        p->enable(active);
    }
    elements.at(i) = std::move(p);
}