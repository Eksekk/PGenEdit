#pragma once
#include "windowsx.h"
#include <winuser.h>
#define MSG_DEF(msg) {msg, {msg, #msg}}
struct WindowsMessage
{
	DWORD msg;
	const char* name;
};

// list taken from wineHQ's page
// commented out are those that give IDE error due to not being defined, TODO: investigate if they are defined at all and if so, where
extern const std::multimap<DWORD, WindowsMessage> windowsMessagesData;

std::string getMatchingMessageNames(DWORD msgId);
