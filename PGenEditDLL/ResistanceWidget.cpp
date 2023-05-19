#include "pch.h"
#include "ResistanceWidget.h"
#include "PlayerResistance.h"
#include "Utility.h"
#include <wx/gbsizer.h>
#include <wx/spinctrl.h>
#include "PlayerStructAccessor.h"

wxDEFINE_EVENT(RESISTANCE_BASE, wxCommandEvent);
wxDEFINE_EVENT(RESISTANCE_BONUS, wxCommandEvent);

ResistanceWidget::ResistanceWidget(wxWindow* panel, wxGridBagSizer* sizer, int rowId, PlayerResistance* res, int playerIndex)
	: resId(res->id), res(res), playerIndex(playerIndex), wxEvtHandler()
{
	label = new wxStaticText(panel, wxID_ANY, res->name);
	sizer->Add(label, wxGBPosition(rowId, 0), wxGBSpan(1, 1));
	auto [low, high] = boundsByType<int16_t>;
	base = new wxSpinCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, low, high);
	sizer->Add(base, wxGBPosition(rowId, 1), wxGBSpan(1, 1));
	bonus = new wxSpinCtrl(panel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0, low, high);
	sizer->Add(bonus, wxGBPosition(rowId, 2), wxGBSpan(1, 1));
	resistanceSpellEffect = new wxStaticText(panel, wxID_ANY, "0");
	sizer->Add(resistanceSpellEffect, wxGBPosition(rowId, 3), wxGBSpan(1, 1), wxALIGN_CENTER_HORIZONTAL);

	base->Bind(wxEVT_SPINCTRL, &ResistanceWidget::onBaseChange, this);
	bonus->Bind(wxEVT_SPINCTRL, &ResistanceWidget::onBonusChange, this);
}

void ResistanceWidget::onBaseChange(wxCommandEvent& event)
{
	playerAccessor->forPlayer(playerIndex)->setStatBase(resId, base->GetValue());
	wxCommandEvent event2(RESISTANCE_BASE, base->GetId());
	event2.SetEventObject(this);
	ProcessEvent(event2);
}

void ResistanceWidget::onBonusChange(wxCommandEvent& event)
{
	playerAccessor->forPlayer(playerIndex)->setStatBonus(resId, bonus->GetValue());
	wxCommandEvent event2(RESISTANCE_BONUS, bonus->GetId());
	event2.SetEventObject(this);
	ProcessEvent(event2);
}

ResistanceWidget::~ResistanceWidget()
{
	// controls will be child of panel, so deleted automatically
}

void ResistanceWidget::updateResistanceSpellEffect(int value)
{
	redBlackGreenTextThreshold(resistanceSpellEffect, value, 0);
	wxString text;
	if (value < 0)
	{
		text = "-" + wxString::Format("%d%%", 100 - value);
	}
	else if (value > 0)
	{
		text = "+" + wxString::Format("%d%%", value - 100);
	}
	else
	{
		text = "0";
	}
	resistanceSpellEffect->SetLabel(text);
}

void ResistanceWidget::updateFromPlayerData()
{
	(void)playerAccessor->forPlayer(playerIndex);
	BaseBonus bb = playerAccessor->getStatBaseBonus(resId);
	base->SetValue(bb.base);
	redBlackGreenTextThreshold(bonus, bb.bonus, 0);
	bonus->SetValue(bb.bonus);
	updateResistanceSpellEffect(playerAccessor->getResistanceSpellEffect(resId));
}
