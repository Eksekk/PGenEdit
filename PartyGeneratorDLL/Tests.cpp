#include "pch.h"
#include "Tests.h"
#include "PlayerSkill.h"
#include <cstdarg>
#include "Application.h"
#include <wx/notebook.h>
#include "GeneralPanel.h"
#include "Generator.h"

extern Generator* generator;

Asserter::Asserter(std::vector<wxString>& errors, bool& failed) : errors(errors), failed(failed) {}

void Asserter::operator()(const char* func, const char* file, int line, bool cond, wxString errorMsg, ...)
{
	if (!cond)
	{
		if (!errorMsg.empty())
		{
			va_list args;
			va_start(args, errorMsg); // second argument cannot be a reference
			std::string file2 = file;
			size_t index = file2.rfind('/');
			if (index != std::string::npos)
			{
				file2 = file2.substr(index + 1);
			}
			errors.push_back(wxString::Format(wxString("%s(%s:%d) %s" + errorMsg), func, file2, line, args));
			va_end(args);
		}
		failed = true;
	}
};

std::vector<wxString> Tests::testSkillFunctions()
{
	std::vector<wxString> errors;
	bool failed = false;
	Asserter myasserter(errors, failed);
	auto old1 = SKILL_COMBINE_MODE;
	auto old2 = MASTERY_BITS;
	auto old3 = SKILL_BITS;

	// rules as in mm7+
	SKILL_COMBINE_MODE = BIT_PER_MASTERY;
	MASTERY_BITS = {-1, -1, 6, 7, 8 };
	SKILL_BITS = 6;
	
	myassert(joinSkill({ 5, 2 }) == 0b1000101);
	myassert(joinSkill({ 10, 2 }) == 0b1001010);
	myassert(joinSkill({ 1, 4 }) == 0b100000001);
	myassert(joinSkill({ 0, 4 }) == 0b0);
	myassert(joinSkill({ 63, 4 }) == 0b100111111);
	myassert(joinSkill({ 15, 3 }) == 0b10001111);
	myassert(joinSkill({ 1, 3 }) == 0b10000001);
	myassert(joinSkill({ 1, 1 }) == 0b1);
	myassert(joinSkill({ 0, 2 }) == 0b0);

	MASTERY_BITS = { -1, -1, 13, 14, 16 };
	SKILL_BITS = 10;
	myassert(joinSkill({ 3, 1 }) == 0b11);
	myassert(joinSkill({ 10, 2 }) == 0b10000000001010);
	myassert(joinSkill({ 512, 4 }) == 0b10000001000000000);
	myassert(joinSkill({ 63, 1 }) == 0b111111);
	myassert(joinSkill({ 25, 3 }) == 0b100000000011001);
	myassert(joinSkill({ 1, 1 }) == 0b1);
	myassert(joinSkill({ 55, 4 }) == 0b10000000000110111);
	myassert(joinSkill({ 0, 4 }) == 0b0);

	SKILL_COMBINE_MODE = PACKED;
	SKILL_BITS = 4;
	myassert(joinSkill({ 3, 1 }) == 0b11);
	myassert(joinSkill({ 12, 3 }) == 0b101100);
	myassert(joinSkill({ 1, 1 }) == 0b1);
	myassert(joinSkill({ 15, 4 }) == 0b111111);
	myassert(joinSkill({ 2, 3 }) == 0b100010);
	myassert(joinSkill({ 0, 4 }) == 0b0);
	myassert(joinSkill({ 3, 3 }) == 0b100011);
	myassert(joinSkill({ 2, 4 }) == 0b110010);

	SKILL_BITS = 6; // like in mm6
	myassert(joinSkill({ 3, 1 }) == 0b11);
	myassert(joinSkill({ 12, 3 }) == 0b10001100);
	myassert(joinSkill({ 1, 1 }) == 0b1);
	myassert(joinSkill({ 4, 1 }) == 0b100);
	myassert(joinSkill({ 63, 1 }) == 0b111111);
	myassert(joinSkill({ 63, 4 }) == 0b11111111);
	myassert(joinSkill({ 12, 3 }) == 0b10001100);
	myassert(joinSkill({ 0, 3 }) == 0b0);
	myassert(joinSkill({ 1, 3 }) == 0b10000001);

	SKILL_COMBINE_MODE = BIT_PER_MASTERY;
	MASTERY_BITS = { -1, -1, 6, 7, 8 };
	SKILL_BITS = 6;
	// rules as in mm7+

	myassert(splitSkill(0b1000101) == Skill({ 5, 2 }));
	myassert(splitSkill(0b1001010) == Skill({ 10, 2 }));
	myassert(splitSkill(0b100000001) == Skill({ 1, 4 }));
	myassert(splitSkill(0b0) == Skill({ 0, 0 }));
	myassert(splitSkill(0b100111111) == Skill({ 63, 4 }));
	myassert(splitSkill(0b10001111) == Skill({ 15, 3 }));
	myassert(splitSkill(0b10000001) == Skill({ 1, 3 }));
	myassert(splitSkill(0b1) == Skill({ 1, 1 }));
	myassert(splitSkill(0b0) == Skill({ 0, 0 }));

	MASTERY_BITS = { -1, -1, 13, 14, 16 };
	SKILL_BITS = 10;
	myassert(splitSkill(0b11) == Skill({ 3, 1 }));
	myassert(splitSkill(0b10000000001010) == Skill({ 10, 2 }));
	myassert(splitSkill(0b10000001000000000) == Skill({ 512, 4 }));
	myassert(splitSkill(0b111111) == Skill({ 63, 1 }));
	myassert(splitSkill(0b100000000011001) == Skill({ 25, 3 }));
	myassert(splitSkill(0b1) == Skill({ 1, 1 }));
	myassert(splitSkill(0b10000000000110111) == Skill({ 55, 4 }));
	myassert(splitSkill(0b0) == Skill({ 0, 0 }));

	SKILL_COMBINE_MODE = PACKED;
	SKILL_BITS = 4;
	myassert(splitSkill(0b11) == Skill({ 3, 1 }));
	myassert(splitSkill(0b101100) == Skill({ 12, 3 }));
	myassert(splitSkill(0b1) == Skill({ 1, 1 }));
	myassert(splitSkill(0b111111) == Skill({ 15, 4 }));
	myassert(splitSkill(0b100010) == Skill({ 2, 3 }));
	myassert(splitSkill(0b0) == Skill({ 0, 0 }));
	myassert(splitSkill(0b100011) == Skill({ 3, 3 }));
	myassert(splitSkill(0b110010) == Skill({ 2, 4 }));

	SKILL_BITS = 6; // like in mm6
	myassert(splitSkill(0b11) == Skill({ 3, 1 }));
	myassert(splitSkill(0b10001100) == Skill({ 12, 3 }));
	myassert(splitSkill(0b1) == Skill({ 1, 1 }));
	myassert(splitSkill(0b100) == Skill({ 4, 1 }));
	myassert(splitSkill(0b111111) == Skill({ 63, 1 }));
	myassert(splitSkill(0b11111111) == Skill({ 63, 4 }));
	myassert(splitSkill(0b10001100) == Skill({ 12, 3 }));
	myassert(splitSkill(0b0) == Skill({ 0, 0 }));
	myassert(splitSkill(0b10000001) == Skill({ 1, 3 }));

	// restore old values
	std::tie(SKILL_COMBINE_MODE, MASTERY_BITS, SKILL_BITS) = std::make_tuple(old1, old2, old3);

	return errors;
}

std::vector<wxString> Tests::testJson()
{
	return std::vector<wxString>();
}

std::vector<wxString> Tests::testGui()
{
	std::vector<wxString> errors;
	bool failed;
	Asserter myasserter(errors, failed);
	auto tabs = wxGetApp().mainWindow->tabs;
	myassert(tabs->GetPageCount() >= 2 + 4);
	myassert(dynamic_cast<GeneralPanel*>(tabs->GetPage(0)));
	return errors;;
}