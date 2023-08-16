#include "pch.h"
#include "Asserter.h"

Asserter::Asserter(const std::string& category)
{
    this->category = category;
}

bool Asserter::logAutomatically = true;