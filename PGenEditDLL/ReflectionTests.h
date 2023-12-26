#pragma once
#include "main.h"

class ReflectionTests
{
public:
    static std::vector<wxString> run();

    static std::vector<wxString> testProperties();

    // TODO: test constructor call methods that take lua params, because they need to take rttr::variant by value to bind both to pointers and class instances, and this might cause original values to be unmodified
};

