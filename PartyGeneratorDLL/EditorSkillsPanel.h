#pragma once
#include "pch.h"
#include "main.h"
#include <wx/statline.h>
#include <wx/spinctrl.h>
#include "EditorSkillValueChooser.h"
#include "PlayerStructAccessor.h"

class EditorSkillsPanel : public wxScrolledWindow
{
private:
	// divide constructor into few methods for readability
	void createSkillPointsOptionsPanel();
	void createSkillsPanel();
	void createActionsPanel();

	void onSkillPointsChange(wxCommandEvent& event);
	void onAffectSkillPointsCheck(wxCommandEvent& event);
	void onDontAllowSpendingMoreThanAvailableSpRadio(wxCommandEvent& event);
	void onAllowNegativeSkillPointsRadio(wxCommandEvent& event);
	void onAffectGoldCheck(wxCommandEvent& event);
	void onDontAllowSpendingMoreThanAvailableGoldRadio(wxCommandEvent& event);
	void onAllowNegativeGoldRadio(wxCommandEvent& event);
	void onRespectClassConstraintsNoRadio(wxCommandEvent& event);
	void onRespectClassConstraintsCurrentRadio(wxCommandEvent& event);
	void onRespectClassConstraintsPromotionRadio(wxCommandEvent& event);
	void onApplyClassConstraintsButton(wxCommandEvent& event);
	void onAffectWeaponsCheck(wxCommandEvent& event);
	void onAffectArmorCheck(wxCommandEvent& event);
	void onAffectMagicCheck(wxCommandEvent& event);
	void onAffectMiscCheck(wxCommandEvent& event);
	void onGodModeButton(wxCommandEvent& event);
	void onSetAllSkillsButton(wxCommandEvent& event);
	void onOnlyAlreadyLearnedCheck(wxCommandEvent& event);
	void onShowUnobtainableSkillsCheck(wxCommandEvent& event);

	void affectCheckboxHelper(bool on, SkillCategory cat);

	void onScrollStart(wxScrollWinEvent& event);
	PlayerStructAccessor::SkillOptions options;

	void onSkillValueChange(wxCommandEvent& event);

	std::unordered_map<PlayerSkill*, EditorSkillValueChooser*> widgetToSkillMap;
	std::unordered_map<EditorSkillValueChooser*, PlayerSkill*> skillToWidgetMap;
	std::unordered_map<int, EditorSkillValueChooser*> widgetToWidgetIdMap;

	const int playerIndex;

	void updateSkillBonuses();
	void skillConstraintErrorMsgBox(bool multiple);
protected:

public:
	wxStaticText* skillPointsAndOptionsHeader;
	wxStaticText* availableSkillPointsLabel;
	wxSpinCtrl* availableSkillPointsAmount;
	wxStaticText* spentSkillPointsLabel;
	wxTextCtrl* spentSkillPointsValue;
	wxCheckBox* affectAvailableSkillpointsCheckbox;
	wxRadioButton* dontAllowSpendingMoreThanAvailableSkillpointsRadio;
	wxRadioButton* allowNegativeSkillpointsRadio;
	wxCheckBox* affectGoldCheckbox;
	wxRadioButton* dontAllowSpendingMoreThanAvailableGoldRadio;
	wxRadioButton* allowNegativeGoldRadio;
	wxTextCtrl* goldDisplayText;
	wxStaticText* goldLabel;
	wxStaticLine* m_staticline29;
	wxStaticText* skillValuesLabel;
	wxStaticLine* m_staticline151;
	wxStaticLine* m_staticline121;
	wxStaticLine* m_staticline16;
	wxStaticLine* m_staticline28;
	wxStaticText* actionsLabel;
	wxRadioButton* classConstraintsNone;
	wxRadioButton* classConstraintsCurrentClass;
	wxRadioButton* classConstraintsPromotionClass;
	wxButton* applyClassConstraintsButton;
	wxStaticBitmap* respectClassConstraintsTooltip;
	wxCheckBox* affectWeaponsCheckbox;
	wxCheckBox* affectArmorCheckbox;
	wxCheckBox* affectMagicCheckbox;
	wxCheckBox* affectMiscCheckbox;
	wxButton* godModeButton;
	wxButton* setAllSkillsToButton;
	wxSpinCtrl* setAllSkillsToLevelSpinCtrl;
	wxChoice* setAllSkillsToMasteryChoice;
	wxStaticLine* m_staticline31;
	wxCheckBox* onlyAlreadyLearnedCheckbox;

	wxCheckBox* showUnobtainableSkillsCheckbox;

	wxBoxSizer* mainSizer;
	//std::function<void(void)> updateCallback;

	EditorSkillsPanel(wxWindow* parent, int playerIndex);

	void onScrollRelease(wxScrollWinEvent& event);
	~EditorSkillsPanel();

	bool AcceptsFocus() const override;
	void updateFromPlayerData();
};
