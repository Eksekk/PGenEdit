#pragma once
#include "pch.h"
#include "main.h"
#include "Enum_const.h"
class AlignmentRadioBox : public wxRadioBox
{
private:
	static const wxString texts[4];
	static const std::map<Alignment, int> alignmentIndexes;
public:
	AlignmentRadioBox(wxWindow* parent, wxString&& label);
	AlignmentRadioBox(wxWindow* parent, const wxString& label);

	Alignment getSelectedAlignment();
	bool setSelection(Alignment alignment);
	bool setSelection(const wxString& str);
};