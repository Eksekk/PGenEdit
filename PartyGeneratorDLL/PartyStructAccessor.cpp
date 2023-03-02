#include "pch.h"
#include "PartyStructAccessor.h"

template<typename Game>
int TemplatedPartyStructAccessor<Game>::getGold()
{
	return party->gold;
}

template<typename Game>
void TemplatedPartyStructAccessor<Game>::setGold(int value)
{
	party->gold = value;
}

template<typename Game>
void TemplatedPartyStructAccessor<Game>::addGold(int value)
{
	party->gold += value;
}

template<typename Game>
void TemplatedPartyStructAccessor<Game>::subtractGold(int value)
{
	party->gold -= value;
}

template<typename Game>
int TemplatedPartyStructAccessor<Game>::getBankGold()
{
	return party->bankGold;
}

template<typename Game>
void TemplatedPartyStructAccessor<Game>::setBankGold(int value)
{
	party->bankGold = value;
}

template<typename Game>
int TemplatedPartyStructAccessor<Game>::getFood()
{
	return party->food;
}

template<typename Game>
void TemplatedPartyStructAccessor<Game>::setFood(int value)
{
	party->food = value;
}

template<typename Game>
void TemplatedPartyStructAccessor<Game>::addFood(int value)
{
	party->food += value;
}

template<typename Game>
void TemplatedPartyStructAccessor<Game>::subtractFood(int value)
{
	party->food = std::max(party->food - value, 0);
}

template<typename Game>
int TemplatedPartyStructAccessor<Game>::getFine()
{
	return party->fine;
}

template<typename Game>
void TemplatedPartyStructAccessor<Game>::setFine(int value)
{
	party->fine = value;
}

template class TemplatedPartyStructAccessor<mm6::Game>;
template class TemplatedPartyStructAccessor<mm7::Game>;
template class TemplatedPartyStructAccessor<mm8::Game>;