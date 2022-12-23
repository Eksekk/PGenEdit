#pragma once
#include "pch.h"
#include "main.h"
#include <windows.h>

template<typename... Args>
void logMsgBox(std::string_view fmt, Args... args)
{
	MessageBoxA(nullptr, std::format(fmt, args...).c_str(), "Log message", 0);
}