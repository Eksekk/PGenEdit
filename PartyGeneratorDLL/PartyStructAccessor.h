#pragma once
#include "pch.h"
#include "main.h"

class PartyStructAccessor;
extern PartyStructAccessor* partyAccessor;

class PartyStructAccessor
{
public:
	virtual int getGold() = 0;
	virtual void setGold(int value) = 0;
	virtual void addGold(int value) = 0;
	virtual void subtractGold(int value) = 0;

	virtual int getBankGold() = 0;
	virtual void setBankGold(int value) = 0;

	virtual int getFood() = 0;
	virtual void setFood(int value) = 0;
	virtual void addFood(int value) = 0;
	virtual void subtractFood(int value) = 0;

	virtual int getFine() = 0;
	virtual void setFine(int value) = 0;

	virtual ~PartyStructAccessor();
};

template<typename Game>
class TemplatedPartyStructAccessor : public PartyStructAccessor
{
	using GameType = Game;
	static inline GameType* const game = reinterpret_cast<GameType*>(0);
	using PartyType = std::remove_pointer_t<std::decay_t<decltype(Game::party)>>;
	static inline PartyType* const party = reinterpret_cast<PartyType*>(0);

	// Inherited via PartyStructAccessor
	virtual int getGold() override;
	virtual void setGold(int value) override;
	virtual void addGold(int value) override;
	virtual void subtractGold(int value) override;
	virtual int getBankGold() override;
	virtual void setBankGold(int value) override;
	virtual int getFood() override;
	virtual void setFood(int value) override;
	virtual void addFood(int value) override;
	virtual void subtractFood(int value) override;
	virtual int getFine() override;
	virtual void setFine(int value) override;
};

using PartyStructAccessor_6 = TemplatedPartyStructAccessor<mm6::Game>;
using PartyStructAccessor_7 = TemplatedPartyStructAccessor<mm7::Game>;
using PartyStructAccessor_8 = TemplatedPartyStructAccessor<mm8::Game>;