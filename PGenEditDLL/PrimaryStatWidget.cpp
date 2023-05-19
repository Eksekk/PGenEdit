#include "pch.h"
#include "PrimaryStatWidget.h"
#include "PlayerPrimaryStat.h"
#include "Utility.h"
#include <wx/gbsizer.h>
#include <wx/spinctrl.h>
#include "PlayerStructAccessor.h"

wxDEFINE_EVENT(PRIMARY_STAT_BASE, wxCommandEvent);
wxDEFINE_EVENT(PRIMARY_STAT_BONUS, wxCommandEvent);
wxDEFINE_EVENT(PRIMARY_STAT_BLACK_POTION, wxCommandEvent);

PrimaryStatWidget::PrimaryStatWidget(wxWindow* panel, wxGridBagSizer* sizer, int rowId, PlayerPrimaryStat* stat, int playerIndex)
	: statId(stat->id), stat(stat), playerIndex(playerIndex), wxEvtHandler()
{
	label = new wxStaticText(panel, wxID_ANY, stat->name);
	sizer->Add(label, wxGBPosition(rowId, 0), wxGBSpan(1, 1));
	auto [low, high] = boundsByType<int16_t>;
	base = new wxSpinCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, low, high);
	sizer->Add(base, wxGBPosition(rowId, 1), wxGBSpan(1, 1));
	bonus = new wxSpinCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, low, high);
	sizer->Add(bonus, wxGBPosition(rowId, 2), wxGBSpan(1, 1));
	blackPotionCheckbox = new wxCheckBox(panel, wxID_ANY, "");
	sizer->Add(blackPotionCheckbox, wxGBPosition(rowId, 3), wxGBSpan(1, 1), wxALIGN_CENTER_HORIZONTAL);
    conditionEffect = new wxStaticText(panel, wxID_ANY, "0");
    sizer->Add(conditionEffect, wxGBPosition(rowId, 4), wxGBSpan(1, 1), wxALIGN_CENTER_HORIZONTAL);

	base->Bind(wxEVT_SPINCTRL, &PrimaryStatWidget::onBaseChange, this);
	bonus->Bind(wxEVT_SPINCTRL, &PrimaryStatWidget::onBonusChange, this);
	blackPotionCheckbox->Bind(wxEVT_CHECKBOX, &PrimaryStatWidget::onBlackPotionCheck, this);
}

void PrimaryStatWidget::onBaseChange(wxCommandEvent& event)
{
	playerAccessor->forPlayer(playerIndex)->setStatBase(statId, base->GetValue());
	wxCommandEvent event2(PRIMARY_STAT_BASE, base->GetId());
	event2.SetEventObject(this);
	ProcessEvent(event2);
}

void PrimaryStatWidget::onBonusChange(wxCommandEvent& event)
{
	playerAccessor->forPlayer(playerIndex)->setStatBonus(statId, bonus->GetValue());
	wxCommandEvent event2(PRIMARY_STAT_BONUS, bonus->GetId());
	event2.SetEventObject(this);
	ProcessEvent(event2);
}

void PrimaryStatWidget::onBlackPotionCheck(wxCommandEvent& event)
{
	playerAccessor->forPlayer(playerIndex)->setBlackPotionUsed(statId, event.IsChecked());
	wxCommandEvent event2(PRIMARY_STAT_BASE, base->GetId());
	event2.SetEventObject(this);
	ProcessEvent(event2);
}

PrimaryStatWidget::~PrimaryStatWidget()
{
	// controls will be child of panel, so deleted automatically
	// delete base, bonus, label, blackPotionCheckbox, conditionEffect;
}

void PrimaryStatWidget::updateConditionEffect(int percentage)
{
	wxString text;
	if (percentage < 100)
	{
		conditionEffect->SetOwnForegroundColour(*wxRED);
		text = "-" + wxString::Format("%d%%", 100 - percentage);
	}
	else if (percentage > 100)
	{
		conditionEffect->SetOwnForegroundColour(*wxGREEN);
		text = "+" + wxString::Format("%d%%", percentage - 100);
	}
	else
	{
		conditionEffect->SetOwnForegroundColour(*wxBLACK);
		text = "0";
	}
	conditionEffect->SetLabel(text);
}

void PrimaryStatWidget::updateFromPlayerData()
{
	(void)playerAccessor->forPlayer(playerIndex);
	BaseBonus bb = playerAccessor->getStatBaseBonus(statId);
	base->SetValue(bb.base);
	redBlackGreenTextThreshold(bonus, bb.bonus, 0);
	bonus->SetValue(bb.bonus);
	updateConditionEffect(playerAccessor->getConditionEffectOnStat(statId));
	blackPotionCheckbox->SetValue(playerAccessor->isBlackPotionUsed(statId));
}
