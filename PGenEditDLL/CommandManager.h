#pragma once
#include "main.h"
#include "Utility.h"
#include "Command.h"

class CommandManager
{
    std::vector<std::unique_ptr<Command>> commands;
};