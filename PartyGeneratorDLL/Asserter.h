#pragma once
#include "pch.h"
#include "main.h"

#define myassert(cond, ...) (!!(cond) || myasserter(__FUNCTION__, __FILE__, __LINE__, "Assertion failed! (" #cond ")" __VA_OPT__(,) __VA_ARGS__))

class Asserter
{
public:
	std::vector<wxString>& errors;
	bool& failed;
	template<typename... Args>
	bool operator()(const char* func, const char* file, int line, const wxString& rawErrorMsg, Args&&... args);

	Asserter(std::vector<wxString>& errors, bool& failed);

	Asserter() = delete;
	Asserter(const Asserter&) = delete;
	Asserter(Asserter&&) = delete;
	Asserter& operator=(const Asserter&) = delete;
};

template<typename... Args>
bool Asserter::operator()(const char* func, const char* file, int line, const wxString& rawErrorMsg, Args&&... args)
{
	// condition checking done in macro - avoiding unnecessary string constructions?
	std::string file2 = file;
	size_t index = file2.rfind('/');
	if (index != std::string::npos)
	{
		file2 = file2.substr(index + 1);
	}
	static const wxString errorFormat("%s(%s:%d) %s");
	wxString errorMsg = rawErrorMsg;
	if constexpr (sizeof...(args) > 0)
	{
		errorMsg << ("\nExtra data:" + rep("\n%s", sizeof...(args)));
		errorMsg = wxString::Format(errorMsg, my_to_string(std::forward<Args>(args))...);
	}
	errors.push_back(wxString::Format(errorFormat, func, file2, line, errorMsg));
	failed = true;
	return false;
}