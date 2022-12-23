#include "pch.h"
#include "main.h"
#include "globals.h"
#include "MainWindow.h"
#include <unordered_map>
#include <string>
#include "Structs.h"
#include <variant>
#include "Generator.h"

Generator* generator = nullptr;

const int INVALID_ID = -1;

const int CMD_SHOW_WINDOW = wxNewId();
const int CMD_TERMINATE = wxNewId();

int MMVER = INVALID_ID;