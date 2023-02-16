#include "pch.h"
#include "Tests.h"
#include "PlayerSkill.h"
#include <cstdarg>
#include "GuiApplication.h"
#include <wx/notebook.h>
#include "GeneralPanel.h"
#include "Generator.h"
#include "DefaultPlayerPanel.h"
#include "PlayerPanel.h"
#include "globals.h"

extern Generator* generator;

Asserter::Asserter(std::vector<wxString>& errors, bool& failed) : errors(errors), failed(failed) {}

wxString rep(const wxString& str, int n)
{
	wxString ret = str;
	for (int i = 0; i < n - 1; ++i)
	{
		ret << str;
	}
	return ret;
}

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

	myassert(splitSkill(0b1000101) == SkillValue({ 5, 2 }));
	myassert(splitSkill(0b1001010) == SkillValue({ 10, 2 }));
	myassert(splitSkill(0b100000001) == SkillValue({ 1, 4 }));
	myassert(splitSkill(0b0) == SkillValue({ 0, 0 }));
	myassert(splitSkill(0b100111111) == SkillValue({ 63, 4 }));
	myassert(splitSkill(0b10001111) == SkillValue({ 15, 3 }));
	myassert(splitSkill(0b10000001) == SkillValue({ 1, 3 }));
	myassert(splitSkill(0b1) == SkillValue({ 1, 1 }));
	myassert(splitSkill(0b0) == SkillValue({ 0, 0 }));

	MASTERY_BITS = { -1, -1, 13, 14, 16 };
	SKILL_BITS = 10;
	myassert(splitSkill(0b11) == SkillValue({ 3, 1 }));
	myassert(splitSkill(0b10000000001010) == SkillValue({ 10, 2 }));
	myassert(splitSkill(0b10000001000000000) == SkillValue({ 512, 4 }));
	myassert(splitSkill(0b111111) == SkillValue({ 63, 1 }));
	myassert(splitSkill(0b100000000011001) == SkillValue({ 25, 3 }));
	myassert(splitSkill(0b1) == SkillValue({ 1, 1 }));
	myassert(splitSkill(0b10000000000110111) == SkillValue({ 55, 4 }));
	myassert(splitSkill(0b0) == SkillValue({ 0, 0 }));

	SKILL_COMBINE_MODE = PACKED;
	SKILL_BITS = 4;
	myassert(splitSkill(0b11) == SkillValue({ 3, 1 }));
	myassert(splitSkill(0b101100) == SkillValue({ 12, 3 }));
	myassert(splitSkill(0b1) == SkillValue({ 1, 1 }));
	myassert(splitSkill(0b111111) == SkillValue({ 15, 4 }));
	myassert(splitSkill(0b100010) == SkillValue({ 2, 3 }));
	myassert(splitSkill(0b0) == SkillValue({ 0, 0 }));
	myassert(splitSkill(0b100011) == SkillValue({ 3, 3 }));
	myassert(splitSkill(0b110010) == SkillValue({ 2, 4 }));

	SKILL_BITS = 6; // like in mm6
	myassert(splitSkill(0b11) == SkillValue({ 3, 1 }));
	myassert(splitSkill(0b10001100) == SkillValue({ 12, 3 }));
	myassert(splitSkill(0b1) == SkillValue({ 1, 1 }));
	myassert(splitSkill(0b100) == SkillValue({ 4, 1 }));
	myassert(splitSkill(0b111111) == SkillValue({ 63, 1 }));
	myassert(splitSkill(0b11111111) == SkillValue({ 63, 4 }));
	myassert(splitSkill(0b10001100) == SkillValue({ 12, 3 }));
	myassert(splitSkill(0b0) == SkillValue({ 0, 0 }));
	myassert(splitSkill(0b10000001) == SkillValue({ 1, 3 }));

	// restore old values
	std::tie(SKILL_COMBINE_MODE, MASTERY_BITS, SKILL_BITS) = std::make_tuple(old1, old2, old3);

	return errors;
}

std::vector<wxString> Tests::testAlignmentRadioBox()
{
	// need to pass nullptr!!! otherwise children of frame will be created as top level windows
	// and NtUserCreateWindowEx will fail with code 1406 (0x57E)
	wxFrame* w = new wxFrame(nullptr, wxID_ANY, "testFrame");
	std::vector<wxString> errors;
	bool failed = false;
	Asserter myasserter(errors, failed);
	AlignmentRadioBox* b1 = new AlignmentRadioBox(w, "a"), *b2 = new AlignmentRadioBox(w, "b");
	myassert(b1->getSelectedAlignment() == b2->getSelectedAlignment());
	b1->setSelection(ALIGNMENT_LIGHT);
	myassert(b1->getSelectedAlignment() != b2->getSelectedAlignment());
	b2->setSelection(ALIGNMENT_LIGHT);
	myassert(b1->getSelectedAlignment() == b2->getSelectedAlignment());
	b1->setSelection(ALIGNMENT_ANY);
	b2->setSelection(ALIGNMENT_DARK);
	myassert(b1->getSelectedAlignment() != b2->getSelectedAlignment());

	for (const auto& str : AlignmentRadioBox::texts)
	{
		b1->setSelection(str);
		b2->setSelection(str);
		myassert(b1->getSelectedAlignment() == b2->getSelectedAlignment(), str);
	}

	b1->SetSelection(AlignmentRadioBox::alignmentIndexes.find(ALIGNMENT_DARK)->second);
	b2->setSelection(ALIGNMENT_DARK);
	myassert(b1->getSelectedAlignment() == b2->getSelectedAlignment());
	myassert(b1->GetSelection() == b2->GetSelection());
	w->Destroy();
	//delete b1, b2, w;
	return errors;
}

std::vector<wxString> Tests::testJson()
{
	static const std::string TEST_FILE_NAME = "class data tests.txt", ERROR_FILE_NAME = "class data errors.txt", OLD_ERROR_FILE_NAME = "old class data errors.txt";
	static const int TEST_AMOUNT = 25;
	// std::ios::in fails if file doesn't exist, even if std::ios::out is specified
	std::fstream errorFile(ERROR_FILE_NAME, std::ios::in);
	if (errorFile.is_open())
	{
		std::fstream(OLD_ERROR_FILE_NAME, std::ios::out | std::ios::trunc) << errorFile.rdbuf();
		errorFile.close();
	}
	else
	{
		errorFile.clear(); // remove failed open flags
	}
	errorFile.open(ERROR_FILE_NAME, std::ios::out | std::ios::trunc);
	if (!jsonErrors.empty())
	{
		wxString str = wxString::Format("Time: %s\nEntering %s(), %d old errors still present:\n\n%s\n\n\n", getTimeStr(), __FUNCTION__, jsonErrors.size(), concatWxStrings(jsonErrors, "\n"));
		errorFile << str;
		if (jsonErrors.size() <= 5)
		{
			wxLogError(str);
		}
		else
		{
			wxLogError("%d json errors written to error file", jsonErrors.size());
		}
		wxLog::FlushActive();
	}
	jsonErrors.clear();
	std::vector<wxString> errors;
	bool failed = false;
	Asserter myasserter(errors, failed);
	std::fstream testFile;
	bool existed = true;
	Json testOut = Json::array(), existingJson;
	std::fstream oldTestsFile(TEST_FILE_NAME, std::ios::in);
	if (oldTestsFile.is_open() && std::filesystem::file_size(TEST_FILE_NAME) > 0)
	{
		try
		{
			existingJson = Json::parse(oldTestsFile);
		}
		catch (const nlohmann::json::exception& ex)
		{
			wxLogError("Error reading old tests file, generating new tests\nError description: %s", ex.what());
			wxLog::FlushActive();
			existed = false;
			testFile.open(TEST_FILE_NAME, std::ios::out | std::ios::trunc);
		}
	}
	else
	{
		existed = false;
		testFile.open(TEST_FILE_NAME, std::ios::out | std::ios::trunc);
	}
	unsigned int failedNum = 0;
	try
	{
		const size_t playerJsonSize = existingJson.size();
		for (int pl = 0; pl < MAX_PLAYERS; ++pl)
		{
			if (!existed || playerJsonSize <= pl)
			{
				testOut.push_back(Json::array());
			}
			auto& classes = generator->playerData[pl]->classes;
			Json copy;
			classes.writeToJson(copy);
			const size_t classJsonSize = playerJsonSize > pl ? existingJson[pl].size() : 0;
			for (int i = 0; i < TEST_AMOUNT; ++i)
			{
				Json j;
				if (existed && playerJsonSize > pl && classJsonSize > i)
				{
					classes.readFromJson(existingJson[pl][i]);
				}
				else
				{
					classes.randomize();
				}
				classes.writeToJson(j);
				if (!existed || classJsonSize <= i)
				{
					testOut[pl].push_back(j);
				}
				ClassGenerationData classes2(classes.index, classes.playerData);
				classes2.readFromJson(j);
				if (classes != classes2)
				{
					errorFile << wxString::Format("Test %d (player %d) failed\nResult json:\n%s\n\n", i, pl, j.dump(4) + "\n\n");
					++failedNum;
				}
			}
			classes.readFromJson(copy);
		}
		if (failedNum > 0)
		{
			wxLogInfo(wxString::Format("%d class json tests failed", failedNum));
			wxLog::FlushActive();
		}
		if (!existed)
		{
			testFile << testOut;
		}
	}
	catch (const std::exception& ex)
	{
		wxLogError(ex.what());
		wxLog::FlushActive();
	}
	if (!jsonErrors.empty())
	{
		wxString str = wxString::Format("Time: %s\nLeaving %s(), %d errors occurred:\n\n%s\n\n\n", getTimeStr(), __FUNCTION__, jsonErrors.size(), concatWxStrings(jsonErrors, "\n"));
		errorFile << str;
		if (jsonErrors.size() <= 5)
		{
			wxLogError(str);
		}
		else
		{
			wxLogError("%d json errors written to error file", jsonErrors.size());
		}
		wxLog::FlushActive();
		jsonErrors.clear();
	}
	return errors;
}

std::vector<wxString> Tests::testGui()
{
	std::vector<wxString> errors;
	bool failed = false;
	Asserter myasserter(errors, failed);
	auto tabs = wxGetApp().mainWindow->tabs;
	myassert(tabs->GetPageCount() == MainWindow::FIRST_PLAYER_PAGE + MAX_PLAYERS);
	myassert(dynamic_cast<GeneralPanel*>(tabs->GetPage(MainWindow::GENERAL_PANEL_PAGE)));
	auto p = dynamic_cast<DefaultPlayerPanel*>(tabs->GetPage(MainWindow::DEFAULT_PLAYER_PAGE));
	if (myassert(p))
	{
		myassert(dynamic_cast<PlayerData*>(p->linkedGenerationData));
	}
	for (int i = 0; i < MAX_PLAYERS; ++i)
	{
		auto p = dynamic_cast<PlayerPanel*>(tabs->GetPage(i + MainWindow::FIRST_PLAYER_PAGE));
		myassert(p, wxString::Format("iteration %d", i));
		if (p)
		{
			myassert(p->linkedGenerationData, wxString::Format("iteration %d", i));
		}
	}
	return mergeVectors({ errors, testAlignmentRadioBox() });
}
