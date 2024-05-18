#include "pch.h"
#include "WindowsMessageBrowser.h"

WindowsMessageBrowser windowsMessageBrowser;

std::vector<WindowsMessageBrowser::MessageData> WindowsMessageBrowser::getMessagesForCurrentThread()
{
    return getMessagesForWindowOfCurrentThread(nullptr);
}

std::vector<WindowsMessageBrowser::MessageData> WindowsMessageBrowser::getMessagesForWindowOfCurrentThread(HWND windowHandle)
{
    std::vector<MessageData> output;
    MSG msg;
	while (PeekMessageA(&msg, windowHandle, 0, 0, PM_NOREMOVE))
    {
		MessageData data{ .windowHandle = msg.hwnd, .msg = msg.message, .lParam = msg.lParam, .wParam = msg.wParam };
		output.push_back(data);
	}
	return output;
}
