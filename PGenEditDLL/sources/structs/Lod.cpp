#pragma once
#include "pch.h"
#include "main.h"

mm6::LodSprite* mm6::SpritesLod::spritesSW = nullptr;
uint32_t* mm6::SpritesLod::spritesSW_sizePtr = nullptr;

bool mm6::SpritesLod::hasFile(/*name*/)
{
	return false;
}

char* mm6::SpritesLod::findFile(/*name, unsorted = false*/)
{
	return nullptr;
}


bool mm6::Lod::hasFile(/*name*/)
{
	return false;
}

char* mm6::Lod::findFile(/*name, unsorted = false*/)
{
	return nullptr;
}


int mm6::LodBitmap::destroy()
{
	return 0;
}


int mm6::BitmapsLod::cleanup()
{
	return 0;
}

char* mm6::BitmapsLod::findFile(/*name, unsorted = false*/)
{
	return nullptr;
}

bool mm6::BitmapsLod::hasFile(/*name*/)
{
	return false;
}

int mm6::BitmapsLod::loadBitmapInPlace(/*bmp:structs.LodBitmap, name, unused_must_be_2 = 2*/)
{
	return 0;
}


mm7::LodSprite* mm7::SpritesLod::spritesSW = nullptr;
uint32_t* mm7::SpritesLod::spritesSW_sizePtr = nullptr;

bool mm7::SpritesLod::hasFile(/*name*/)
{
	return false;
}

char* mm7::SpritesLod::findFile(/*name, unsorted = false*/)
{
	return nullptr;
}


bool mm7::Lod::hasFile(/*name*/)
{
	return false;
}

char* mm7::Lod::findFile(/*name, unsorted = false*/)
{
	return nullptr;
}


int mm7::LodBitmap::destroy()
{
	return 0;
}


int mm7::BitmapsLod::endTmp()
{
	return 0;
}

int mm7::BitmapsLod::cleanup()
{
	return 0;
}

bool mm7::BitmapsLod::hasFile(/*name*/)
{
	return false;
}

int mm7::BitmapsLod::loadBitmapInPlace(/*bmp:structs.LodBitmap, name, unused_must_be_2 = 2*/)
{
	return 0;
}

char* mm7::BitmapsLod::findFile(/*name, unsorted = false*/)
{
	return nullptr;
}

int mm7::BitmapsLod::replaceBitmap(/*bmp:structs.LodBitmap, name, unused_must_be_2 = 2*/)
{
	return 0;
}


mm8::LodSprite* mm8::SpritesLod::spritesSW = nullptr;
uint32_t* mm8::SpritesLod::spritesSW_sizePtr = nullptr;

bool mm8::SpritesLod::hasFile()
{
	return false;
}


bool mm8::Lod::hasFile()
{
	return false;
}


bool mm8::BitmapsLod::hasFile()
{
	return false;
}

