#pragma once
#include "pch.h"
#include "main.h"
#include "PlayerClass.h"
#include "PlayerSkill.h"
#include <vector>

class GameData
{
public:
	static std::vector<PlayerClass> classes; // lua
	static std::vector<PlayerSkill> skills; // lua
};

