#include "pch.h"
#include "Asserter.h"

Asserter::Asserter(std::vector<wxString>& errors, bool& failed) : errors(errors), failed(failed) {}