#pragma once
#include "pch.h"
#include "main.h"
#include <wx/spinctrl.h>
#include "PlayerSkill.h"

wxDECLARE_EVENT(SKILL_VALUE_CHANGE, wxCommandEvent);

class EditorSkillValueChooser : public wxPanel
{
	static const std::unordered_map<int, Mastery> masteryToIdMap;
	static const std::unordered_map<Mastery, int> idToMasteryMap;
	static const std::array<wxString, 5> masteryNames;
public:
	wxStaticText* skillNameLabel;
	wxSpinCtrl* skillLevel;
	wxStaticText* skillLevelBonusLabel;
	wxChoice* skillMastery;

	EditorSkillValueChooser(wxWindow* parent, const wxString& labelText);

	SkillValue getValue();
	int getLevel();
	Mastery getMastery();
	void setValue(const SkillValue& value);
	void setValue(int value);
	void setLevel(int level);
	void setMastery(Mastery mastery);
	void updateSkillBonus(int value);
	void onValueChange(wxCommandEvent& event);
	void setRowColor(const wxColour& colour);
	void onShow(wxShowEvent& event);
};

