#pragma once
#include "pch.h"
#include "main.h"
#include <wx/spinctrl.h>
#include "PlayerSkill.h"

class EditorSkillValueChooser : public wxPanel
{
	static const std::unordered_map<int, Mastery> masteryToIdMap;
	static const std::unordered_map<Mastery, int> idToMasteryMap;
	static const std::array<wxString, 5> masteryNames;
public:
	wxStaticText* skillNameLabel;
	wxSpinCtrl* skillLevel;
	wxChoice* skillMastery;

	EditorSkillValueChooser(wxWindow* parent, const wxString& labelText);

	SkillValue getValue();
	int getLevel();
	Mastery getMastery();
	void setValue(const SkillValue& value);
	void setValue(int value);
	void setLevel(int level);
	void setMastery(Mastery mastery);
};

