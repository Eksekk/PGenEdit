#pragma once
#include "pch.h"
#include "main.h"

class GameStructAccessor;
extern GameStructAccessor* gameAccessor;
class GameStructAccessor
{
public:
	virtual HWND getWindowHandle() = 0;
	virtual int getCurrentPlayer() = 0;

	virtual void* getIconsLodPtr() = 0;
	virtual int64_t getTime() = 0;
	virtual void setTime(int64_t time) = 0;

	virtual ~GameStructAccessor();
};

template<typename Game>
class TemplatedGameStructAccessor : public GameStructAccessor
{
	using GameType = std::decay_t<Game>;
	static inline GameType* const game = reinterpret_cast<GameType*>(0);
public:
	HWND getWindowHandle() override;
	int getCurrentPlayer() override;
	// Inherited via GameStructAccessor
	virtual void* getIconsLodPtr() override
	{
		return &game->iconsLod;
	}

	// Inherited via GameStructAccessor
	virtual int64_t getTime() override;

	virtual void setTime(int64_t time) override;
};
using GameStructAccessor_6 = TemplatedGameStructAccessor<mm6::Game>;
using GameStructAccessor_7 = TemplatedGameStructAccessor<mm7::Game>;
using GameStructAccessor_8 = TemplatedGameStructAccessor<mm8::Game>;