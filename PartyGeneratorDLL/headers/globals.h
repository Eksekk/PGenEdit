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

// functions from lua
typedef bool (*isTwoHanded_ptr)(void*, int); // player ptr, item id
extern isTwoHanded_ptr isTwoHanded;
typedef bool (*isEquippableInOffhand_ptr)(void*, int);
extern isEquippableInOffhand_ptr isEquippableInOffhand;

extern std::vector<wxString> jsonErrors;

extern bool inMM;