#pragma once
#include "main.h"
#include "Utility.h"

#define myassert(cond, ...) ((!!(cond)) || myasserter(__FUNCTION__, __FILE__, __LINE__, "Assertion failed! (" #cond ")" __VA_OPT__(,) __VA_ARGS__))

#define myfail(msg) myasserter.fail(__FUNCTION__, __FILE__, __LINE__, wxString("Failure! " + msg))

// could also be simply macro invoking directly format function
#define myassertf(cond, fmt, ...) ((!!(cond)) || myasserter(__FUNCTION__, __FILE__, __LINE__, wxString::Format(wxString("Assertion failed! (" #cond "): ") + fmt __VA_OPT__(,) __VA_ARGS__)))

#define myfailf(fmt, ...) myasserter.failFormat(__FUNCTION__, __FILE__, __LINE__, wxString("Failure! ") + fmt __VA_OPT__(,) __VA_ARGS__)

// using this to not require exact name "myasserter" to be written every time
// still a primitive test system, but a bit better
#define CREATE_ASSERTER(description) Asserter myasserter(description)

class Asserter
{
	// wx log sink
	class LogSink : public wxLog
	{
        Asserter* asserter;
	public:
		LogSink(Asserter* asserter);
		~LogSink();
		void DoLogTextAtLevel(wxLogLevel level, const wxString& msg) override;
		void DoLogText(const wxString& msg) override;
		void DoLogRecord(wxLogLevel level, const wxString& msg, const wxLogRecordInfo& info) override;
	};
	std::unique_ptr<LogSink> logSink;
public:
	std::vector<wxString> errors;
    std::string category;
	// called when assert failure happens, handles logging and adding to errors vector
    template<typename... Args>
    bool operator()(const char* func, const char* file, int line, const wxString& rawErrorMsg, Args&&... args);
	template<typename... Args>
    bool assertFormat(const char* func, const char* file, int line, Args&&... args);
    template<typename... Args>
    bool fail(const char* func, const char* file, int line, const wxString& str);
    template<typename... Args>
	bool failFormat(const char* func, const char* file, int line, const wxString& format, Args&&... args);
	static bool logAutomatically;
	void flush();

	// generate code for assert() method, which takes same arguments as operator() and calls it with forwarded arguments
	template<typename... Args>
	bool assertTrue(const char* func, const char* file, int line, const wxString& rawErrorMsg, Args&&... args)
    {
        return operator()(func, file, line, rawErrorMsg, std::forward<Args>(args)...);
    }

	Asserter(const std::string& category);
	~Asserter();

	Asserter(const Asserter&) = delete;
	Asserter(Asserter&&) = delete;
	Asserter& operator=(const Asserter&) = delete;
};

template<typename... Args>
bool Asserter::operator()(const char* func, const char* file, int line, const wxString& rawErrorMsg, Args&&... args)
{
	// condition checking done in macro - avoiding unnecessary string constructions

	// extract only file name from full path
	std::string file2 = file;
	size_t index = file2.rfind('\\');
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
	if (IsDebuggerPresent())
	{
		//__debugbreak(); // if we're being debugged, break into debugger to inspect call stack and variables
	}
	errors.push_back(str);
	return false;
}

template<typename... Args>
bool Asserter::assertFormat(const char* func, const char* file, int line, Args&&... args)
{
	return operator()(func, file, line, wxString::Format(args...));
}

template<typename ...Args>
inline bool Asserter::fail(const char* func, const char* file, int line, const wxString& str)
{
	return operator()(func, file, line, str);
}

template<typename ...Args>
inline bool Asserter::failFormat(const char* func, const char* file, int line, const wxString& format, Args&& ...args)
{
	return operator()(func, file, line, wxString::Format(format, std::forward<Args>(args)...));
}
