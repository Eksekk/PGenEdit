#pragma once
#include "pch.h"
#include "main.h"

enum HookKind // map index
{
	HK_RECOVERY_MULTIPLIER,
	HK_NO_RECOVERY
};

void setupHooks();