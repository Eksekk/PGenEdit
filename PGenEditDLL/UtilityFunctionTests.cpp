#include "pch.h"
#include "UtilityFunctionTests.h"
#include "Asserter.h"

std::vector<wxString> doStringFunctionTests()
{
	// string functions
	Asserter myasserter("String functions test");

	// stringToLower and stringToUpper
	wxLogMessage("stringToLower");
	static std::vector<std::pair<std::string, std::string>> stringToLowerTests =
	{
		{ "Hello", "hello" },
		{ "HELLO", "hello" },
		{ "he!!llo", "he!!llo" },
		{ "HeLLo WoRLD", "hello world" },
		{ "123", "123" },
		{ "123;abc", "123;abc" },
		{ "123ABC", "123abc" },
		{ "123abcABC", "123abcabc" },
		{ "123abcABC123", "123abcabc123" },
		{ "123abcABC123abcABC", "123abcabc123abcabc" },
		{ "GDf+#28394;;;3dEKoMNsh", "gdf+#28394;;;3dekomnsh" },
		//{ "• ∆£—”åèØ", "πÍÊ≥ÒÛúüø" }, // polish characters
	};

	wxLogMessage("stringToUpper");
	static std::vector<std::pair<std::string, std::string>> stringToUpperTests =
	{
		{ "Hello", "HELLO" },
		{ "HELLO", "HELLO" },
		{ "he!!llo", "HE!!LLO" },
		{ "HeLLo WoRLD", "HELLO WORLD" },
		{ "123", "123" },
		{ "123abc", "123ABC" },
		{ "123;ABC", "123;ABC" },
		{ "123abcABC", "123ABCABC" },
		{ "123abcABC123", "123ABCABC123" },
		{ "123abcABC123abcABC", "123ABCABC123ABCABC" },
		{ "GDf+#28394;;;3dEKoMNsh", "GDF+#28394;;;3DEKOMNSH" },
		//{ "πÍÊ≥ÒÛúüø", "• ∆£—”åèØ" }, // polish characters
	};

	for (const auto& test : stringToUpperTests)
	{
		myassertf(util::string::toUpper(test.first) == test.second, std::format("stringToUpper test failed: input: '{}', expected output: '{}', actual output: '{}'", test.first, test.second, util::string::toUpper(test.first)));
	}

	for (const auto& test : stringToLowerTests)
	{
		myassertf(util::string::toLower(test.first) == test.second, std::format("stringToLower test failed: input: '{}', expected output: '{}', actual output: '{}'", test.first, test.second, util::string::toLower(test.first)));
	}

	// stringSplit
	wxLogMessage("stringSplit");
	struct StringSplitTest
	{
		std::string text;
		std::string delimiter;
		bool regex;
		bool ignoreCase;
		std::vector<std::string> expected;
	};

	static const std::vector<StringSplitTest> stringSplitTests
	{
		{.text = "", .delimiter = ",", .regex = false, .ignoreCase = false, .expected = { "" } },
		{.text = "Hello,world", .delimiter = ",", .regex = false, .ignoreCase = false, .expected = { "Hello", "world" } },
		{.text = "Hello,world", .delimiter = "o", .regex = false, .ignoreCase = false, .expected = { "Hell", ",w", "rld" } },
		{.text = "Hello,world", .delimiter = "l", .regex = true, .ignoreCase = false, .expected = { "He", "", "o,wor", "d"} },
		{.text = "20 + 2 + 2 * (3 + 2)", .delimiter = "\\+ ", .regex = true, .ignoreCase = false, .expected = { "20 ", "2 ", "2 * (3 ", "2)"} },
		{.text = "mY strING mY text MY words", .delimiter = "mY", .regex = false, .ignoreCase = true, .expected = { "", " strING ", " text ", " words" } },
		{.text = "mY strING mY text mY words", .delimiter = "[a-z] [a-z]", .regex = true, .ignoreCase = false, .expected = { "mY strING mY tex", "Y words" } },
		{.text = "|||,|,,||,|||,,|,||", .delimiter = R"(\|\|)", .regex = true, .ignoreCase = true, .expected = { "", "|,|,,", ",", "|,,|,", "" } },
		{.text = "a,b;c.d.f:abc:abc", .delimiter = R"(,|;|\.|:)", .regex = true, .ignoreCase = true, .expected = { "a", "b", "c", "d", "f", "abc", "abc" } },
		{.text = "testingtestingtesting", .delimiter = R"(t|t|t|s)", .regex = true, .ignoreCase = true, .expected = { "", "e", "", "ing", "e", "ing", "e", "", "ing"}},
		// New test cases
		{.text = "CaseInsensitive,CASEINSENSITIVE,caseinsensitive", .delimiter = "caseinsensitive", .regex = false, .ignoreCase = true, .expected = { "", ",", ",", "" }},
		{.text = "Split by space", .delimiter = " ", .regex = false, .ignoreCase = false, .expected = { "Split", "by", "space" } },
		{.text = "Split  by multiple    spaces", .delimiter = " +", .regex = true, .ignoreCase = false, .expected = { "Split", "by", "multiple", "spaces" } },
		{.text = "Split by digits 123", .delimiter = R"(\d)", .regex = true, .ignoreCase = false, .expected = { "Split by digits ", "", "", "" } },
		{.text = "Special characters !@#$%^&*()", .delimiter = "[!@#$%^&*()]", .regex = true, .ignoreCase = false, .expected = { "Special characters ", "", "", "", "", "", "", "", "", "", "" }},
		{.text = "No delimiter match", .delimiter = "xyz", .regex = false, .ignoreCase = false, .expected = { "No delimiter match" } },
		{.text = "Multiple delimiters a,b;c.d", .delimiter = "[,;\\.]", .regex = true, .ignoreCase = false, .expected = { "Multiple delimiters a", "b", "c", "d" } },
		{.text = "CaseSensitiveTest,CASESENSITIVETEST,casesensitivetest", .delimiter = "CASESENSITIVETEST", .regex = false, .ignoreCase = false, .expected = { "CaseSensitiveTest,", ",casesensitivetest" } },
		{.text = "Split by newline\nSecond line\nThird line", .delimiter = "\n", .regex = false, .ignoreCase = false, .expected = { "Split by newline", "Second line", "Third line" } }
	};

	for (const auto& test : stringSplitTests)
	{
		std::vector<std::string> result;
		if (test.regex)
		{
			result = stringSplitRegex(test.text, test.delimiter, test.ignoreCase);
		}
		else
		{
			result = stringSplit(test.text, test.delimiter, test.ignoreCase);
		}
		myassert(result == test.expected, std::format("stringSplit test failed: input: '{}', delimiter: '{}', expected output: '{}', actual output: '{}'", test.text, test.delimiter, test.expected, result));
	}

	// stringRep
	wxLogMessage("stringRep");
	struct StringRepTest
	{
		std::string text;
		int reps;
		std::string expected;
	};

	std::vector<StringRepTest> stringRepTests
	{
		{.text = "Hello", .reps = 0, .expected = "" },
		{.text = "AaA", .reps = 2, .expected = "AaAAaA" },
		{.text = "1ooo", .reps = 5, .expected = "1ooo1ooo1ooo1ooo1ooo"},
		{.text = "+d", .reps = 1, .expected = "+d" },
		{.text = "πÍÊ≥ÒÛúüø", .reps = 3, .expected = "πÍÊ≥ÒÛúüøπÍÊ≥ÒÛúüøπÍÊ≥ÒÛúüø" }, // polish characters
		{.text = "123", .reps = 4, .expected = "123123123123" },
		{.text = " ", .reps = 0, .expected = "" },
		{.text = "ú    o2^", .reps = 2, .expected = "ú    o2^ú    o2^" },
		{.text = "a", .reps = 0, .expected = "" },
		{.text = "a", .reps = 1, .expected = "a" },
		{.text = "a", .reps = 2, .expected = "aa" },
		{.text = "a", .reps = 3, .expected = "aaa" },
		{.text = "a", .reps = 4, .expected = "aaaa" },
		{.text = "a", .reps = 5, .expected = "aaaaa" },
		{.text = "a", .reps = 6, .expected = "aaaaaa" },
		{.text = "a", .reps = 7, .expected = "aaaaaaa" },
	};

	for (const auto& test : stringRepTests)
	{
		myassertf(util::string::rep(test.text, test.reps) == test.expected, std::format("stringRep test failed: input: '{}', reps: '{}', expected output: '{}', actual output: '{}'", test.text, test.reps, test.expected, util::string::rep(test.text, test.reps)));
	}

	// stringReplace
	wxLogMessage("stringReplace");

	struct ReplaceInStringTest
	{
		std::string str, replaceWhat;
		bool regex = false;
		std::variant<std::string, StringReplaceFuncType> replacement;
		std::string expected;
	};

	const std::vector<ReplaceInStringTest> replaceInStringTests =
	{
		// TODO: more test cases
		{.str = "ababababa", .replaceWhat = "ab", .regex = false, .replacement = "b", .expected = "bbbba"},
		{.str = "aaaaaaaaaaaaaaaaaaa", .replaceWhat = "aaa", .regex = false, .replacement = "c", .expected = "cccccca"},
		{.str = "mytest1", .replaceWhat = "tes1", .regex = false, .replacement = "y", .expected = "mytest1"},
		{.str = "no_re3pla5ceme5nt_at_all+++++", .replaceWhat = R"([a-z]+(?!\d)|[a-z]_[g-o]|\+{3}(?=\-))", .regex = true, .replacement = "|$1|,", .expected = "no_re3pla5ceme5nt_at_all+++++"},
		{.str = "replace this and that", .replaceWhat = "this", .regex = false, .replacement = "that", .expected = "replace that and that"},
		{.str = "Hello World", .replaceWhat = "world", .regex = false, .replacement = "Universe", .expected = "Hello World"},
		{.str = "12345", .replaceWhat = "2", .regex = false, .replacement = "0", .expected = "10345"},
		{.str = "abcabcabc", .replaceWhat = "abc", .regex = false, .replacement = "xyz", .expected = "xyzxyzxyz"},
		{.str = "Test string with numbers 12345", .replaceWhat = R"(\d+)", .regex = true, .replacement = "NUM", .expected = "Test string with numbers NUM"},
		{.str = "Hello, Hello, Hello", .replaceWhat = "Hello", .regex = false, .replacement = "Hi", .expected = "Hi, Hi, Hi" },
		{.str = "No match here", .replaceWhat = "xyz", .regex = false, .replacement = "found", .expected = "No match here" },
		{.str = "Special characters !@#$%^&*()", .replaceWhat = "[!@#$%^&*()]", .regex = true, .replacement = "", .expected = "Special characters " },
		{.str = "abc123abc", .replaceWhat = "\\d+", .regex = true, .replacement = "456", .expected = "abc456abc" },
		{.str = "CaseSensitive", .replaceWhat = "casesensitive", .regex = false, .replacement = "new", .expected = "CaseSensitive" },
		{.str = "int i;\nint j;\nint k;\nint f;", .replaceWhat = "int (\\w);", .regex = true,


			.replacement = [](const std::smatch& match) -> std::string
			{
					return "int " + stringRep(match[1].str(), 3) + ";";
			},
			.expected = "int iii;\nint jjj;\nint kkk;\nint fff;" },

		{.str = "fedcba", .replaceWhat = "(\\w)", .regex = true,
			.replacement = [](const std::smatch& match) -> std::string
			{
				const auto& str = match[1].str();
				if (str != "f")
				{
					return std::string(1, 'a' + ('e' - str[0]));
				}
				else
				{
					return "";
				}
			},
			.expected = "abcde" },

			// complicated regex
		{.str = "0_1_2+aAaaBa+5<6+fdDDDDD_", .replaceWhat = R"((_|aB(a*)?|^\d+|[dD]{3})|\+)", .regex = true, .replacement = "($1),repl", .expected = "(0),repl(_),repl1(_),repl2(+),replaAa(aBa),repl(+),repl5<6(+),repl(dDD),repl(DDD),repl"
		},

		{
			// first number after is number of underscores in group
		.str = "_1__25___3___33_1____41___3fs__2_1_", .replaceWhat = R"(_{1,3}\d)", .regex = true, .replacement = "($1),repl", .expected = "(_1),repl(__2),repl5(___3),repl(___3),repl3(_1),repl____41(___3,repl)fs(__2),repl(_1),repl_"
		},
	};

	int i = 1;
	for (const auto& [str, replaceWhat, regex, replacement, expected] : replaceInStringTests)
	{
		std::string result;
		if (const std::string* repl = std::get_if<std::string>(&replacement))
		{
			result = stringReplace(str, replaceWhat, *repl, !regex);
		}
		else if (const StringReplaceFuncType* repl = std::get_if<StringReplaceFuncType>(&replacement))
		{
			result = stringReplace(str, replaceWhat, *repl);
		}
		myassertf(result == expected, "[stringReplace test #%d] incorrect output (expected '%s', got '%s')", i, expected, result);
		++i;
	}

	return myasserter.errors;
}

std::vector<wxString> UtilityFunctionTests::run()
{
	std::vector<wxString> results = doStringFunctionTests();
	return results;
}
