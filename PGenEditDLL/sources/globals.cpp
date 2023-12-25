#include "pch.h"
#include "main.h"
#include "globals.h"
#include "MainWindow.h"
#include "Generator.h"

Generator* generator = nullptr;

const int INVALID_ID = -1;
const int DEFAULT_SETTINGS_INDEX = -2;
bool unloadCleanupStarted = false;

int MMVER = INVALID_ID;

void* game = 0;
std::array<void*, 50> playersFullArray{ 0 };
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

RTTR_REGISTRATION
{
	// register all global properties in this file
	using namespace rttr;
rttr::registration::property("game", &game)
	.property("playersFullArray", &playersFullArray)
	.property("playersInParty", &playersInParty)
	.property("inGame", &inGame)
	.property("mainUpdateTimer", &mainUpdateTimer)
	.property("MMVER", &MMVER)
	.property("inMM", &inMM)
	.property("jsonErrors", &jsonErrors)
	.property("isTwoHanded", &isTwoHanded)
	.property("isEquippableInOffhand", &isEquippableInOffhand)
	.property("generator", &generator)
	.property("unloadCleanupStarted", &unloadCleanupStarted)
	.property_readonly("INVALID_ID", &INVALID_ID)
	.property_readonly("DEFAULT_SETTINGS_INDEX", &DEFAULT_SETTINGS_INDEX);
}
