#pragma once
#include "main.h"
#include "Utility.h"

#define myassert(cond, ...) (!!(cond) || myasserter(__FUNCTION__, __FILE__, __LINE__, "Assertion failed! (" #cond ")" __VA_OPT__(,) __VA_ARGS__))

// could also be simply macro invoking directly format function
#define myassertf(cond, fmt, ...) (!!(cond) || myasserter.assertFormat(__FUNCTION__, __FILE__, __LINE__, wxString("Assertion failed! (" #cond "): ") + fmt __VA_OPT__(,) __VA_ARGS__))

class Asserter
{
public:
	std::vector<wxString> errors;
	std::string category;
	template<typename... Args>
	bool operator()(const char* func, const char* file, int line, const wxString& rawErrorMsg, Args&&... args);
	template<typename... Args>
	bool assertFormat(const char* func, const char* file, int line, Args&&... args);
	static bool logAutomatically;
	void flush();

	Asserter(const std::string& category);

	Asserter(const Asserter&) = delete;
	Asserter(Asserter&&) = delete;
	Asserter& operator=(const Asserter&) = delete;
};

template<typename... Args>
bool Asserter::operator()(const char* func, const char* file, int line, const wxString& rawErrorMsg, Args&&... args)
{
	// condition checking done in macro - avoiding unnecessary string constructions
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
		errorMsg << ("\nExtra data:" + stringRep("\n%s", sizeof...(args)));
		errorMsg = wxString::Format(errorMsg, my_to_string(std::forward<Args>(args))...);
	}
	wxString str = wxString::Format(errorFormat, func, file2, line, errorMsg);
	if (logAutomatically)
	{
		wxLogError("[%s] %s", category, str);
	}
	errors.push_back(str);
	return false;
}

template<typename... Args>
bool Asserter::assertFormat(const char* func, const char* file, int line, Args&&... args)
{
	return operator()(func, file, line, wxString::Format(args...));
}