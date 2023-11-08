#pragma once
#include "main.h"

class wxSpinCtrl;
class PlayerResistance;
class wxGridBagSizer;

wxDECLARE_EVENT(RESISTANCE_BASE, wxCommandEvent);
wxDECLARE_EVENT(RESISTANCE_BONUS, wxCommandEvent);

class ResistanceWidget : public wxEvtHandler
{
	void onBaseChange(wxCommandEvent& event);
	void onBonusChange(wxCommandEvent& event);
public:
	PlayerResistance* const res;
	const int resId, playerIndex;
	wxStaticText* label;
	wxSpinCtrl* base, * bonus;
	wxStaticText* resistanceSpellEffect;

	ResistanceWidget(wxWindow* panel, wxGridBagSizer* sizer, int rowId, PlayerResistance* res, int playerIndex);
	~ResistanceWidget();
	ResistanceWidget() = delete;
	ResistanceWidget(const ResistanceWidget&) = delete;
	ResistanceWidget(ResistanceWidget&&) = delete;

	void updateResistanceSpellEffect(int value);
	void updateFromPlayerData();
};

