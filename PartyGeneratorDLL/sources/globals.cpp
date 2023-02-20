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

isTwoHanded_ptr isTwoHanded = (isTwoHanded_ptr)0;
isEquippableInOffhand_ptr isEquippableInOffhand = (isEquippableInOffhand_ptr)0;

bool inMM = false;

std::vector<wxString> jsonErrors;