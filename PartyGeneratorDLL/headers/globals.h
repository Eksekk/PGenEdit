#pragma once
#include "pch.h"
#include "main.h"
#include "Player.h"
#include "Structs.h"
#include "Generator.h"

extern Generator* generator;

extern int MMVER;

extern const int INVALID_ID;

extern const int CMD_SHOW_WINDOW;
extern const int CMD_TERMINATE;

extern lua_State* Lua;

extern void* game;

// functions from lua
typedef bool (*isTwoHanded_ptr)(void*, int); // player ptr, item id
extern isTwoHanded_ptr isTwoHanded;
typedef bool (*isEquippableInOffhand_ptr)(void*, int);
extern isEquippableInOffhand_ptr isEquippableInOffhand;

bool inMM;