#pragma once
#include "main.h"
#include <wx/spinctrl.h>
#include "PlayerSkill.h"
#include "PlayerStructAccessor.h"

wxDECLARE_EVENT(SKILL_VALUE_CHANGE_BY_USER, wxCommandEvent);

class EditorSkillValueChooser : public wxPanel
{
	static const std::unordered_map<int, Mastery> masteryToIdMap;
	static const std::unordered_map<Mastery, int> idToMasteryMap;
	static const std::array<wxString, 5> masteryNames;
public:
	const int playerIndex;
	PlayerSkill* const skill;
	PlayerStructAccessor::SkillOptions& options;

	wxStaticText* skillNameLabel;
	wxSpinCtrl* skillLevel;
	wxStaticText* skillLevelBonusLabel;
	wxChoice* skillMastery;

	EditorSkillValueChooser(wxWindow* parent, const wxString& labelText, int playerIndex, PlayerSkill* skill, PlayerStructAccessor::SkillOptions& options);

	SkillValue getValue();
	int getLevel();
	Mastery getMastery();
	// doesn't perform skill points / gold checks
	void setValue(const SkillValue& value);
	// doesn't perform skill points / gold checks
	void setValue(int value);
	// doesn't perform skill points / gold checks
	void setLevel(int level);
	// doesn't perform skill points / gold checks
	void setMastery(Mastery mastery);
	void updateSkillBonus(int value);
	void onValueChange(wxCommandEvent& event);
	bool processValueChangeByUser();
	static void adjustNewSkillValue(const SkillValue& oldValue, SkillValue& newValue);

	void updateFromPlayerData();
	friend class Tests;
	friend class GUI_tests;
};

