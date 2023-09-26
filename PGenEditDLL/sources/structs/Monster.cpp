#pragma once
#include "pch.h"
#include "main.h"
#include "Common.h"

int mm6::MapMonster::loadFrames(/*SoundLoaded = false*/)
{
	return 0;
}

char* mm6::MapMonster::updateGraphicState()
{
	return nullptr;
}

int mm6::MapMonster::calcTakenDamage(/*DamageKind, Damage*/)
{
	return 0;
}

bool mm6::MapMonster::calcHitOrMiss(/*Player:structs.Player*/)
{
	return false;
}

int mm6::MapMonster::chooseTargetPlayer()
{
	return 0;
}

bool mm6::MapMonster::calcHitByEffect(/*DamageKind*/)
{
	return false;
}


char* mm7::MapMonster::updateGraphicState()
{
	return nullptr;
}

char* mm7::MapMonster::showSpellEffect(/*Color24 = 0*/)
{
	return nullptr;
}

int mm7::MapMonster::calcTakenDamage(/*DamageKind, Damage*/)
{
	return 0;
}

int mm7::MapMonster::isAgainst(/*Mon2:structs.MapMonster*/)
{
	return 0;
}

bool mm7::MapMonster::calcHitOrMiss(/*Player:structs.Player*/)
{
	return false;
}

bool mm7::MapMonster::calcHitByEffect(/*DamageKind*/)
{
	return false;
}

int mm7::MapMonster::loadFrames(/*SoundLoaded = false*/)
{
	return 0;
}

int mm7::MapMonster::chooseTargetPlayer()
{
	return 0;
}


int mm8::MapMonster::isAgainst(/*Mon2:structs.MapMonster*/)
{
	return 0;
}

int mm8::MapMonster::loadFrames(/*SoundLoaded = false*/)
{
	return 0;
}

int mm8::MapMonster::chooseTargetPlayer()
{
	return 0;
}

bool mm8::MapMonster::calcHitByEffect(/*DamageKind*/)
{
	return false;
}

char* mm8::MapMonster::showSpellEffect(/*Color24 = 0*/)
{
	return nullptr;
}

bool mm8::MapMonster::calcTakenDamage(/*DamageKind, Damage*/)
{
	return false;
}

char* mm8::MapMonster::updateGraphicState()
{
	return nullptr;
}

bool mm8::MapMonster::calcHitOrMiss(/*Player:structs.Player*/)
{
	return false;
}

