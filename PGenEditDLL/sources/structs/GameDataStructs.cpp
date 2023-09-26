#pragma once
#include "pch.h"
#include "main.h"
#include "Monster.h"
#include "Common.h"

int mm6::GameScreen::saveToPcx(/*name, x = 0, y = 0, width = 640, height = 480*/)
{
	return 0;
}


int mm6::Dlg::setKeyboardNavigation(/*KeyboardItemsCount, KeyboardNavigationTrackMouse, KeyboardLeftRightStep, KeyboardItemsStart*/)
{
	return 0;
}

int mm6::Dlg::getItemPtrByIndex(/*Index*/)
{
	return 0;
}


int32_t* mm6::DialogLogic::list = nullptr;
uint32_t* mm6::DialogLogic::list_sizePtr = nullptr;

uint8_t* mm6::GameClasses::HPFactor = nullptr;
uint32_t mm6::GameClasses::HPFactor_size = 0;
uint8_t* mm6::GameClasses::SPFactor = nullptr;
uint32_t mm6::GameClasses::SPFactor_size = 0;
uint8_t* mm6::GameClasses::SPStats = nullptr;
uint32_t mm6::GameClasses::SPStats_size = 0;

std::array<uint8_t, 31>* mm6::GameClassKinds::startingSkills = nullptr;
uint32_t mm6::GameClassKinds::startingSkills_size = 0;

int mm7::GameScreen::saveToPcx(/*name, x = 0, y = 0, width = 640, height = 480*/)
{
	return 0;
}

int mm7::GameScreen::setClipRect(/*left = 0, top = 0, right = 640, bottom = 480*/)
{
	return 0;
}

int mm7::GameScreen::saveBufferToPcx(/*name, buf, width = 640, height = 480*/)
{
	return 0;
}


int mm7::Dlg::getItemPtrByIndex(/*Index*/)
{
	return 0;
}

int mm7::Dlg::setKeyboardNavigation(/*KeyboardItemsCount, KeyboardNavigationTrackMouse, KeyboardLeftRightStep, KeyboardItemsStart*/)
{
	return 0;
}


int32_t* mm7::DialogLogic::list = nullptr;
uint32_t* mm7::DialogLogic::list_sizePtr = nullptr;

uint8_t* mm7::GameClasses::HPFactor = nullptr;
uint32_t mm7::GameClasses::HPFactor_size = 0;
uint8_t* mm7::GameClasses::SPFactor = nullptr;
uint32_t mm7::GameClasses::SPFactor_size = 0;
uint8_t* mm7::GameClasses::SPStats = nullptr;
uint32_t mm7::GameClasses::SPStats_size = 0;
std::array<uint8_t, 37>* mm7::GameClasses::skills = nullptr;
uint32_t mm7::GameClasses::skills_size = 0;

std::array<uint8_t, 37>* mm7::GameClassKinds::startingSkills = nullptr;
uint32_t mm7::GameClassKinds::startingSkills_size = 0;

int mm8::GameScreen::saveBufferToPcx(/*name, buf, width = 640, height = 480*/)
{
	return 0;
}

int mm8::GameScreen::saveToPcx(/*name, x = 0, y = 0, width = 640, height = 480*/)
{
	return 0;
}


int32_t* mm8::DialogLogic::list = nullptr;
uint32_t* mm8::DialogLogic::list_sizePtr = nullptr;

int mm8::Dlg::getItemPtrByIndex(/*Index*/)
{
	return 0;
}

int mm8::Dlg::addButton(/*X, Y, Width, Height, Shape = 1, HintAction, ActionType, ActionInfo, Key, Hint, Sprites..., 0*/)
{
	return 0;
}

int mm8::Dlg::setKeyboardNavigation(/*KeyboardItemsCount, KeyboardNavigationTrackMouse, KeyboardLeftRightStep, KeyboardItemsStart*/)
{
	return 0;
}


uint8_t* mm8::GameClasses::HPBase = nullptr;
uint32_t mm8::GameClasses::HPBase_size = 0;
uint8_t* mm8::GameClasses::HPFactor = nullptr;
uint32_t mm8::GameClasses::HPFactor_size = 0;
uint8_t* mm8::GameClasses::SPBase = nullptr;
uint32_t mm8::GameClasses::SPBase_size = 0;
uint8_t* mm8::GameClasses::SPFactor = nullptr;
uint32_t mm8::GameClasses::SPFactor_size = 0;
uint8_t* mm8::GameClasses::SPStats = nullptr;
uint32_t mm8::GameClasses::SPStats_size = 0;
std::array<uint8_t, 39>* mm8::GameClasses::skills = nullptr;
uint32_t mm8::GameClasses::skills_size = 0;
std::array<mm8::StartStat, 7>* mm8::GameClasses::startingStats = nullptr;
uint32_t mm8::GameClasses::startingStats_size = 0;

std::array<uint8_t, 39>* mm8::GameClassKinds::startingSkills = nullptr;
uint32_t mm8::GameClassKinds::startingSkills_size = 0;
