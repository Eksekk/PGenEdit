#pragma once
#include "pch.h"
#include "main.h"
#include "Player.h"
#include "Structs.h"

class Generator;
extern Generator* generator;

extern int MMVER;

extern const int INVALID_ID;
extern const int DEFAULT_SETTINGS_INDEX;

extern void* game;
extern std::array<void*, 50> players;
extern std::array<void*, 5> playersInParty;
extern bool inGame;
extern wxTimer* mainUpdateTimer;
void runUpdateTimerCallbacks(wxTimerEvent&);
void addUpdateTimerCallback(std::function<void(void)> callback);
extern std::vector<std::function<void(void)>> callbackList;

// functions from lua
typedef bool (*isTwoHanded_ptr)(void*, int); // player ptr, item id
extern isTwoHanded_ptr isTwoHanded;
typedef bool (*isEquippableInOffhand_ptr)(void*, int);
extern isEquippableInOffhand_ptr isEquippableInOffhand;

extern std::vector<wxString> jsonErrors;

extern bool inMM;