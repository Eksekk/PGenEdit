#pragma once
#include "WindowMessageNumberNameMappings.h"
// a class which runs through all messages for given thread and prints useful debugging information, such as window name, message name, parameters etc.
// will be used to fix a problem where closing my windows causes game to minimize itself, even if minimize button was not clicked
// NOTE: it might be enough to use MMExtension's functions which are called before showing any non-game window and after hiding all of them
class WindowsMessageBrowser
{
	struct MessageData
	{
		HWND windowHandle;
		DWORD msg;
		DWORD lParam, wParam;
		inline std::string getWindowClassName() const
		{
			char buffer[256];
			GetClassNameA(windowHandle, buffer, 256);
			return std::string(buffer);
		}
		inline std::string getMessageName() const
		{
			return getMatchingMessageNames(msg);
		}
	};
};

