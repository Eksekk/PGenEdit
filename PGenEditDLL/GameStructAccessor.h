#pragma once
#include "main.h"
#include "StructAccessor.h"

class GameStructAccessor;
extern GameStructAccessor* gameAccessor;
#define PGENEDIT_GETTERS_SETTERS (int32_t, NPCCommand, NPCCommand), (bool, paused, Paused)
class GameStructAccessor : StructAccessorGenericFor
{
public:
	virtual HWND getWindowHandle() = 0;
	virtual int getCurrentPlayer() = 0;

	virtual void* getIconsLodPtr() = 0;
	virtual ArrayData getItemsTxtArrayData() = 0;
	virtual ArrayData getStdItemsTxtArrayData() = 0;
	virtual ArrayData getSpcItemsTxtArrayData() = 0;
	virtual int64_t getTime() = 0;
	virtual void setTime(int64_t time) = 0;

	template<typename Function>
	static auto forAnyGameStructExecute(Function&& func)
	{
		return StructAccessorGenericFor::genericForSingleStructExecute<Function, mm6::Game, mm7::Game, mm8::Game>(nullptr, std::forward<Function>(func));
	}
	PGENEDIT_GETTER_SETTER_METHODS_DECL(PGENEDIT_GETTERS_SETTERS)

	PGENEDIT_ARRAY_GETTER_SETTER_METHODS_DECL((int16_t, spellSounds, SpellSounds, 99, 99, 132))

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
	virtual int64_t getTime() override;

	virtual void setTime(int64_t time) override;

	// Inherited via GameStructAccessor
	virtual void* getIconsLodPtr() override
	{
		return &game->iconsLod;
	}
	virtual ArrayData getItemsTxtArrayData() override
	{
		return ArrayData(game->itemsTxt, game->itemsTxt_sizePtr);
	}
	virtual ArrayData getStdItemsTxtArrayData() override
	{
		return ArrayData(game->stdItemsTxt, game->stdItemsTxt_size);
    }
    virtual ArrayData getSpcItemsTxtArrayData() override
    {
        return ArrayData(game->spcItemsTxt, game->spcItemsTxt_size);
    }

	PGENEDIT_GETTER_SETTER_METHODS_DEF(game->, PGENEDIT_GETTERS_SETTERS)

	PGENEDIT_ARRAY_GETTER_SETTER_METHODS_DEF(game->, (int16_t, spellSounds, SpellSounds))
};
using GameStructAccessor_6 = TemplatedGameStructAccessor<mm6::Game>;
using GameStructAccessor_7 = TemplatedGameStructAccessor<mm7::Game>;
using GameStructAccessor_8 = TemplatedGameStructAccessor<mm8::Game>;