#pragma once
#include "main.h"

class wxSpinCtrl;
class PlayerPrimaryStat;
class wxGridBagSizer;

wxDECLARE_EVENT(PRIMARY_STAT_BASE, wxCommandEvent);
wxDECLARE_EVENT(PRIMARY_STAT_BONUS, wxCommandEvent);
wxDECLARE_EVENT(PRIMARY_STAT_BLACK_POTION, wxCommandEvent);

class PrimaryStatWidget : public wxEvtHandler
{
	void onBaseChange(wxCommandEvent& event);
	void onBonusChange(wxCommandEvent& event);
	void onBlackPotionCheck(wxCommandEvent& event);
public:
	PlayerPrimaryStat* const stat;
	const int statId, playerIndex;
	wxStaticText* label;
	wxSpinCtrl* base, *bonus;
	wxCheckBox* blackPotionCheckbox;
	wxStaticText* conditionEffect;

	// take sizer as argument, because I can't make this a window derivative (wxPanel), because
	// I think grid bag sizer can't take panel and still be able to split it along different cells
	// (with aligning them nicely, so span of 5 columns won't do)
	PrimaryStatWidget(wxWindow* panel, wxGridBagSizer* sizer, int rowId, PlayerPrimaryStat* stat, int playerIndex);
	~PrimaryStatWidget();
	PrimaryStatWidget() = delete;
	PrimaryStatWidget(const PrimaryStatWidget&) = delete;
	PrimaryStatWidget(PrimaryStatWidget&&) = delete;

	void updateConditionEffect(int percentage);
	void updateFromPlayerData();
};