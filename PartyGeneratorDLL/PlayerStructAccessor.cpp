#include "pch.h"
#include "PlayerStructAccessor.h"
#include "LowLevel.h"

const bool MALE = true, FEMALE = false; // TODO: check
const int PLAYER_ACTIVE = 6, PLAYER_RANDOM = 7;

PlayerStructAccessor* playerAccessor = nullptr;
//PlayerStructAccessor::FieldSizes PlayerStructAccessor::FIELD_SIZES;
int PlayerStructAccessor::FieldSizes::biography = 0; // 0/0/256, set in dllApi.cpp
int PlayerStructAccessor::FieldSizes::skill = -2; // 1/-2/-2

PlayerStructAccessor::~PlayerStructAccessor() {}

int PlayerStructAccessor::getPlayerIndex()
{
	static std::mt19937 gen(std::random_device{}());
	if (playerIndex == PLAYER_RANDOM)
	{
		return std::uniform_int_distribution(0, CURRENT_PARTY_SIZE - 1)(gen);
	}
	else if (playerIndex == PLAYER_ACTIVE)
	{
		int index = std::max(0, (int32_t)dword(mmv(0x4D50E8, 0x507A6C, 0x519350)) - 1);
		return index;
	}
	else
	{
		wxASSERT_MSG(playerIndex < CURRENT_PARTY_SIZE, wxString::Format("Invalid player index %d", playerIndex));
		return std::clamp(playerIndex, 0, CURRENT_PARTY_SIZE - 1);
	}
}
