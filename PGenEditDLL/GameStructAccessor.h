#pragma once
#include "main.h"
#include "StructAccessor.h"

// boost.pp for accessor methods generation needs widest types of all game fields, and return/set them
// also need to somehow make first field letter capital (so it's getGold, not getgold)
// to consider: issue a warning if assigning to or returning narrower type outside its range?
// params to pass on example of gold: gold, Gold, int64_t

// declaration will contain virtual and = 0, definition will contain override

#define GETTER_DECL(type, fieldName, getterNamePart) \
	virtual type get##getterNamePart() = 0;
#define GETTER_DEF(type, fieldName, getterNamePart) \
	type get##getterNamePart() override { return game->fieldName; }
#define SETTER_DECL(type, fieldName, setterNamePart) \
	virtual void set##setterNamePart(type value) = 0;
#define SETTER_DEF(type, fieldName, setterNamePart) \
	void set##setterNamePart(type value) override { game->fieldName = value; }

#define GETTER_SETTER_DECL(type, fieldName, accessorNamePart) \
	GETTER_DECL(type, fieldName, accessorNamePart) \
	SETTER_DECL(type, fieldName, accessorNamePart)

#define GETTER_SETTER_DEF(type, fieldName, accessorNamePart) \
	GETTER_DEF(type, fieldName, accessorNamePart) \
	SETTER_DEF(type, fieldName, accessorNamePart)

// pass a list of tuples containing 3 elements each: type, field name, accessor name part to some macro, which will iterate over them and generate getter/setter methods
// example: GETTER_SETTER_METHODS((int, gold, Gold), (int, food, Food))
#define GETTER_SETTER_METHODS_DEF(...) \
	BOOST_PP_SEQ_FOR_EACH(GETTER_SETTER_METHODS_MACRO_DEF, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))
#define GETTER_SETTER_METHODS_MACRO_DEF(r, data, seq) \
	GETTER_SETTER_DEF(BOOST_PP_TUPLE_ELEM(0, seq), BOOST_PP_TUPLE_ELEM(1, seq), BOOST_PP_TUPLE_ELEM(2, seq))

#define GETTER_SETTER_METHODS_DECL(...) \
	BOOST_PP_SEQ_FOR_EACH(GETTER_SETTER_METHODS_MACRO_DECL, _, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))
#define GETTER_SETTER_METHODS_MACRO_DECL(r, data, seq) \
	GETTER_SETTER_DECL(BOOST_PP_TUPLE_ELEM(0, seq), BOOST_PP_TUPLE_ELEM(1, seq), BOOST_PP_TUPLE_ELEM(2, seq))

//BOOST_PP_VARIADIC_TO_SEQ((int, gold, Gold), (int, food, Food))

class GameStructAccessor;
extern GameStructAccessor* gameAccessor;
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
	GETTER_SETTER_METHODS_DECL((int, gold, Gold), (int, food, Food))

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
};
using GameStructAccessor_6 = TemplatedGameStructAccessor<mm6::Game>;
using GameStructAccessor_7 = TemplatedGameStructAccessor<mm7::Game>;
using GameStructAccessor_8 = TemplatedGameStructAccessor<mm8::Game>;