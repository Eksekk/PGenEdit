#pragma once
#include "pch.h"
#include "main.h"
class Logger
{
public:
	template<typename... Args>
	void log(std::string_view fmt, Args...) = 0;
};

class LoggerMsgBox : public Logger
{
	template<typename... Args>
	void log(std::string_view fmt, Args...)
	{
		MessageBoxA(nullptr, std::format(fmt, Args...).c_str(), "Debug message", 0);
	}
};

LoggerMsgBox log;