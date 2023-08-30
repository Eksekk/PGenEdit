#include "pch.h"
#include "main.h"
#include "globals.h"
#include "MainWindow.h"
#include "Generator.h"

Generator* generator = nullptr;

const int INVALID_ID = -1;
const int DEFAULT_SETTINGS_INDEX = -2;

int MMVER = INVALID_ID;

void* game = 0;
std::array<void*, 50> players{ 0 };
std::array<void*, 5> playersInParty{ 0 }; // TODO: might need regular update
bool inGame = false;
wxTimer* mainUpdateTimer = nullptr;
std::vector<std::function<void(void)>> callbackList;
void runUpdateTimerCallbacks(wxTimerEvent&)
{
	for (const auto& callback : callbackList)
	{
		callback();
	}
}

void addUpdateTimerCallback(std::function<void(void)> callback)
{
	callbackList.push_back(std::move(callback));
}

isTwoHanded_ptr isTwoHanded = (isTwoHanded_ptr)0;
isEquippableInOffhand_ptr isEquippableInOffhand = (isEquippableInOffhand_ptr)0;

bool inMM = false;

std::vector<wxString> jsonErrors;