#include "pch.h"
#include "LuaTests.h"
#include "LuaTable.h"
#include "Asserter.h"
#include "LuaWrapper.h"
#include "LuaFunctions.h"
#include "GameStructAccessor.h"
#include "LuaValue.h"
#include "PersistableLuaTable.h"

std::vector<wxString> LuaTests::run()
{
    wxASSERT_MSG(Lua, "LuaTests::run() called before Lua is initialized");
    Asserter myasserter("Lua tests");
    // LuaTable
    auto luaTablePassthrough = [&](const LuaTable& orig, int index)
        {
            orig.pushToLuaStack(Lua);
            LuaTable created = LuaTable::fromLuaTable(Lua);
            if (created != orig)
            {
                myassertf(false, "[LuaTable] Passthrough test #%d failed", index);
                lua_getglobal(Lua, "dump");
                created.pushToLuaStack(Lua);
                if (lua_pcall(Lua, 1, 1, 0))
                {
                    wxLogError("pcall to dump table failed: '%s'", luaWrapper.tostring(-1));
                }
                else
                {
                    wxLogError("[LuaTable] Test #%d: dumped converted table is: '%s'", index, luaWrapper.tostring(-1));
                }
                luaWrapper.pop(1); // pop error msg or dump result
            }
            luaWrapper.pop(1); // pop actual table from stack
        };

    using namespace std::string_literals; // makes '"aaa"s' work
    LuaTable t1{ { // first LuaTable init, second map init, third pair init
        {"abc", 5LL},
        {5LL, 24LL},
        {true,
            LuaTable{ {
                {"f", "f"},
                {51111, false},
                {1, 3},
                {"abcd",
                    LuaTable{ {
                        {"f", "b"},
                        {3.4, "A"}
                    } }
                }
            } }
        },
    } };
    luaTablePassthrough(t1, 1);
    LuaTable t2{ {
        {false, false},
        {true, true}
    } };
    luaTablePassthrough(t1, 2);
    LuaTable t3{ {
    } };
    luaTablePassthrough(t3, 3);
    LuaTable t4{ {
        {5.0, 3.0},
        {8, 8.0},
        {3, true}
    } };
    luaTablePassthrough(t4, 4);

    LuaTable t5{ {
        {5.0, t1},
        {"ddd", t2},
        {t3, t4},
        {t2, LuaTable{{
                // {Nil, t3}, // in reality key can't be nil in lua, but this will be used to remove keys/values in C++ and transfer this to lua
                {t2, 333333333333LL},
                {false, LuaTable{{}}}
            }}
        }
    } };
    luaTablePassthrough(t5, 5);
    // ONE MORE integer-floating-point test
    LuaTable t6{ {
        {2.0, 2.0},
        {0xFFFFFFFFFFFFLL, -0x5LL},
        {3, 3333333},
        {4, 50000000000000.0}
    } };
    luaTablePassthrough(t6, 6);

    auto table = [](const LuaTypeInCpp& val)
        {
            wxASSERT_MSG(std::holds_alternative<LuaTable>(val), "LuaTable::at() test: value is not a table");
            return std::get<LuaTable>(val);
        };

    // TODO: also extended Nil test, once I implement appropriate behavior

    // "at" method tests
    int atIndex = 1;
    static const wxString atStr = "[LuaTable::at()] Test #%d failed";
    myassertf(t1.at("abc") == 5LL, atStr, atIndex++);
    myassertf(t1.att(true).at("f") == "f"s, atStr, atIndex++);

    myassertf(t1.at(5LL) == 24LL, atStr, atIndex++);
    myassertf(t1.att(true).at(51111) == false, atStr, atIndex++);
    myassertf(t1.att(true).at(1) == 3LL, atStr, atIndex++);
    myassertf(t1.att(true).att("abcd").at("f") == "b"s, atStr, atIndex++);

    myassertf(t5.att(5.0).at("abc") == 5LL, atStr, atIndex++);
    myassertf(t5.att("ddd").at(false) == false, atStr, atIndex++);
    myassertf(t5.att(t3).at(3) == true, atStr, atIndex++);

    myassertf(t5.att(t2).at(t2) == 333333333333LL, atStr, atIndex++);

    // contains() method tests
    int containsIndex = 1;
    static const wxString containsStr = "[LuaTable::contains()] Test #%d failed";
    myassertf(t1.contains("abc"), containsStr, containsIndex++);
    myassertf(t1.att(true).contains("f"), containsStr, containsIndex++);
    myassertf(t1.contains(5LL), containsStr, containsIndex++);
    myassertf(t1.att(true).contains(51111), containsStr, containsIndex++);
    myassertf(t1.att(true).contains(1), containsStr, containsIndex++);
    myassertf(t1.att(true).att("abcd").contains("f"), containsStr, containsIndex++);
    myassertf(t5.att(5.0).contains("abc"), containsStr, containsIndex++);
    myassertf(t5.att("ddd").contains(false), containsStr, containsIndex++);
    myassertf(t5.att(t3).contains(3), containsStr, containsIndex++);

    // negative tests
    myassertf(!t1.contains("abcd"), containsStr, containsIndex++);
    myassertf(!t1.contains(51112), containsStr, containsIndex++);
    myassertf(!t1.att(true).contains("abcdfg"), containsStr, containsIndex++);
    myassertf(!t1.att(true).contains(51112), containsStr, containsIndex++);
    myassertf(!t5.att(5.0).contains("abcd"), containsStr, containsIndex++);
    myassertf(!t5.att(t3).contains(4), containsStr, containsIndex++);
    myassertf(!t5.att(t2).contains(t3), containsStr, containsIndex++);
    myassertf(!t5.att(t2).contains(t5), containsStr, containsIndex++);

    // fromLuaCode tests
    int fromLuaCodeTestIndex = 1;
    LuaTable t7 = LuaTable::fromLuaCode(Lua, "{a = 5, b = 6}");
    myassertf(t7.at("a") == 5LL, "[LuaTable::fromLuaCode()] Test #%d failed, field 'a' is not equal to 5", fromLuaCodeTestIndex++);
    myassertf(t7.at("b") == 6LL, "[LuaTable::fromLuaCode()] Test #%d failed, field 'b' is not equal to 6", fromLuaCodeTestIndex++);
    LuaTable t8 = "{a = 5, b = 6}"_luaTable;
    myassertf(t8.at("a") == 5LL, "[LuaTable::fromLuaCode()] Test #%d failed, field 'a' is not equal to 5", fromLuaCodeTestIndex++);
    myassertf(t8.at("b") == 6LL, "[LuaTable::fromLuaCode()] Test #%d failed, field 'b' is not equal to 6", fromLuaCodeTestIndex++);

    LuaWrapper w(Lua);
    w.dostring(R"(
		function dbl(x)
            return x * 2
		end

        function appendStr(str)
	        return str .. "abc"
        end

        exampleTable = {["t"] = 23, a = 4, [false] = 5}
	)");
    LuaTable t9 = R"(
		{
			["t"] = exampleTable.t,
			a = exampleTable.a,
			[false] = exampleTable[false],
            d = dbl(15),
            s = appendStr("def")
		}
)"_luaTable;
    myassertf(t9.at("t") == 23LL, "[LuaTable::fromLuaCode()] Test #%d failed, field 't' is not equal to 23", fromLuaCodeTestIndex++);
    myassertf(t9.at("a") == 4LL, "[LuaTable::fromLuaCode()] Test #%d failed, field 'a' is not equal to 4", fromLuaCodeTestIndex++);
    myassertf(t9.at(false) == 5LL, "[LuaTable::fromLuaCode()] Test #%d failed, field 'false' is not equal to 5", fromLuaCodeTestIndex++);
    myassertf(t9.at("d") == 30LL, "[LuaTable::fromLuaCode()] Test #%d failed, field 'd' is not equal to 30", fromLuaCodeTestIndex++);
    myassertf(t9.at("s") == "defabc"s, "[LuaTable::fromLuaCode()] Test #%d failed, field 's' is not equal to 'defabc'", fromLuaCodeTestIndex++);

    w.unsetGlobals({ "dbl", "appendStr", "exampleTable"}, true);

    // constructFromValuesWithArray tests
    int constructFromValuesWithArrayIndex = 1;
    auto testMultipleFields = [&](const LuaTable& t, const std::vector<LuaValuePair>& vals)
        {
            for (const auto& [index, value] : vals)
            {
                if (!t.contains(index))
                {
                    myfailf("[LuaTable::constructFromValuesWithArray()] Test #%d failed, field %s is not present", constructFromValuesWithArrayIndex, index.valueToString());
                }
                else if (t.at(index) != value)
                {
                    myfailf("[LuaTable::constructFromValuesWithArray()] Test #%d failed, field %s is not equal to %s", constructFromValuesWithArrayIndex, index.valueToString(), value.toString());
                }
            }
            ++constructFromValuesWithArrayIndex;
        };
    LuaTable t10 = LuaTable::constructFromValuesWithArray({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    testMultipleFields(t10, { {1, 1LL}, {10, 10LL} });
    LuaTable t11 = LuaTable::constructFromValuesWithArray({ 5, 4, 3, 2, 1 });
    testMultipleFields(t11, { {1, 5LL}, {5, 1LL} });
    LuaTable t12 = LuaTable::constructFromValuesWithArray({ 2, "abc", 3, "def", false });
    testMultipleFields(t12, { {1, 2LL}, {2, "abc"s}, {3, 3LL}, {4, "def"s}, {5, false} });
    // few tables with scattered key-value pairs
    LuaTable t13 = LuaTable::constructFromValuesWithArray({ false, false, LuaValuePair{"a"s, true}, LuaValuePair{25LL, 3LL}, "string"s, LuaValuePair{false, LuaTable()}, 5, 2, LuaValuePair{111, 1}, 5, LuaValuePair{"cdg"s, "aaaaa"s}});
    testMultipleFields(t13, { {1, false}, {2, false}, {"a"s, true}, {25LL, 3LL}, {3, "string"s}, {false, LuaTable()}, {4, 5LL}, {5, 2LL}, {111, 1LL}, {6, 5LL}, {"cdg"s, "aaaaa"s}});
    LuaTable t14 = LuaTable::constructFromValuesWithArray({ false, false, false, LuaValuePair{false, false}, "a"s, "a"s, LuaValuePair{"a"s, "a"}, 5, 5, LuaValuePair{55, 5} });
    testMultipleFields(t14, { {1, false}, {2, false}, {3, false}, {false, false}, {4, "a"s}, {5, "a"s}, {"a"s, "a"s}, {6, 5LL}, {7, 5LL}, {55, 5LL} });


    // getArrayPart tests
    int getArrayPartIndex = 1;
    auto getArrayPartTest = [&](const LuaTableValuesWithArray& values)
        {
            LuaTable arr = LuaTable::constructFromValuesWithArray(values);
            std::vector<LuaTypeInCpp> myArrayPart;
            std::ranges::for_each(values, [&](const auto& var)
                {
                    if (std::holds_alternative<LuaValue>(var))
                    {
                        myArrayPart.push_back(std::get<LuaValue>(var));
                    }
                });
            myassertf(arr.getArrayPart() == myArrayPart, "[LuaTable::getArrayPart()] Test #%d failed", getArrayPartIndex++);
        };

    getArrayPartTest({ 1, 2, 5, false });
    getArrayPartTest({ "a"s, "b"s, "c"s, "d"s });
    getArrayPartTest({ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 });
    getArrayPartTest({ LuaValuePair{"a"s, "b"s}, 4, false, LuaTable(), LuaValuePair{LuaTable(), LuaTable()}, "striiiiiiiing"s, LuaValuePair{333333333, "sssss"s} });
    getArrayPartTest({ 10, LuaValuePair{-1, -2}, 5, 2, "jhsdbfjsdhf"s, LuaValuePair{false, false} });
    
    // FIXME: decide how PersistableLuaTable should work and fix these tests

    /*
    // PersistableLuaTable tests, in particular identity-preserving feature
    int persistableLuaTableIndex = 1;
    auto persistableLuaTableTest = [&](const LuaTable& t)
		{
            LuaStackAutoRestore sr(Lua);
            LuaWrapper w(Lua);
			PersistableLuaTable plu(t);
			// some stack manipulations
            plu.pushToLuaStack(Lua);
            plu.updateInRegistry(Lua);
            PersistableLuaTable plu2(t);
            // different PLTs created from same table still shouldn't be shared, unless PLT's copy constructor is involved, and only then
            myassertf(!w.rawequal(-1, -2), "[PersistableLuaTable] Test #%d failed, two tables with different identities are fully equal", persistableLuaTableIndex);
            PersistableLuaTable plu3(t), plu4(plu3);
            plu3.pushToLuaStack(Lua);
            plu4.pushToLuaStack(Lua);
            myassertf(w.rawequal(-1, -2), "[PersistableLuaTable] Test #%d failed, two tables with same identities are not fully equal", persistableLuaTableIndex);
            wxASSERT(!t.contains(555)); // so I don't accidentally overwrite with test value
            plu[555] = 21212LL;
            plu.updateFromRegistry(Lua);
            myassertf(!t.contains(555), "[PersistableLuaTable] Test #%d failed, table modifications are visible after restoration from registry", persistableLuaTableIndex);

			++persistableLuaTableIndex;
		};

    persistableLuaTableTest(t1);
    persistableLuaTableTest(t2);
    persistableLuaTableTest(t3);
    persistableLuaTableTest({});
    */

    return util::container::mergeVectors({ myasserter.errors, testLuaWrapper() });
}

std::vector<wxString> LuaTests::testLuaWrapper()
{
    Asserter myasserter("LuaWrapper tests");
    LuaWrapper w(Lua);

    int stackIndex = w.gettop();
    // get path tests
    int getPathIndex = 1;
    static const wxString failureStr = "[LuaWrapper::getPath(), path '%s'] Test #%d failed: %s";
    static const std::string typeMismatchStr = "Type mismatch: expected {}, got {}";
    static const std::string valueMismatchStr = "Value mismatch: expected {}, got {}";
    auto formatTypeMismatchStr = [&](int desiredType, int actualType) -> std::string
        {
			return std::vformat(typeMismatchStr, std::make_format_args(static_cast<const std::string&>(w.typename_(desiredType)), static_cast<const std::string&>(w.typename_(actualType))));
		};
    auto formatValueMismatchStr = [&](const auto& desiredValue, const auto& actualValue) -> std::string
        {
            return std::vformat(valueMismatchStr, std::make_format_args(desiredValue, actualValue));
        };
    auto getPathTest = [&](const std::string& path, int firstElemIndex, const auto& desiredValue)
        {
            if (!w.getPath(path, firstElemIndex))
            {
                myfailf(failureStr, getPathIndex++, std::format("couldn't get path '{}'", path));
                return;
            }
            using T = std::remove_cvref_t<decltype(desiredValue)>; // T is type of desiredValue
            if constexpr (std::is_same_v<T, LuaTable>)
            {
                if (!w.isTable(-1))
                {
                    myfailf(failureStr, path, getPathIndex, formatTypeMismatchStr(LUA_TTABLE, w.type(-1)));
                }
                else
                {
					myassertf(w.totable(-1) == desiredValue, failureStr, path, getPathIndex, formatValueMismatchStr(desiredValue, w.totable(-1)));
                }
			}
            else if constexpr (std::is_same_v<T, bool>)
            {
                if (!w.isBoolean(-1))
                {
					myfailf(failureStr, path, getPathIndex, formatTypeMismatchStr(LUA_TBOOLEAN, w.type(-1)));
				}
                else
                {
					myassertf(w.toboolean(-1) == desiredValue, failureStr, path, getPathIndex, formatValueMismatchStr(desiredValue, w.toboolean(-1)));
				}
			}
            else if constexpr (std::integral<T> && !std::is_same_v<T, bool>) // second condition just in case
            {
                if (!w.isNumber(-1))
                {
					myfailf(failureStr, path, getPathIndex, formatTypeMismatchStr(LUA_TNUMBER, w.type(-1)));
				}
                else
                {
					myassertf(w.tonumber(-1) == desiredValue, failureStr, path, getPathIndex, formatValueMismatchStr(desiredValue, w.tonumber(-1)));
				}
			}
            else if constexpr (std::is_same_v<T, double>)
            {
                if (!w.isNumber(-1))
                {
					myfailf(failureStr, path, getPathIndex, formatTypeMismatchStr(LUA_TNUMBER, w.type(-1)));
				}
                else
                {
					myassertf(w.tonumber(-1) == desiredValue, failureStr, path, getPathIndex, formatValueMismatchStr(desiredValue, w.tonumber(-1)));
				}
			}
            else if constexpr (std::is_same_v<T, std::string>)
            {
                if (!w.isString(-1))
                {
					myfailf(failureStr, path, getPathIndex, formatTypeMismatchStr(LUA_TSTRING, w.type(-1)));
				}
                else
                {
					myassertf(w.tostring(-1) == desiredValue, failureStr, path, getPathIndex, formatValueMismatchStr(desiredValue, w.tostring(-1)));
				}
			}
            else if constexpr (std::is_same_v<T, void*>)
            {
                if (!w.isUserdata(-1))
                {
                    myfailf(failureStr, path, getPathIndex, formatTypeMismatchStr(LUA_TUSERDATA, w.type(-1)));
                }
                else
                {
					myassertf(w.touserdata(-1) == desiredValue, failureStr, path, getPathIndex, formatValueMismatchStr(desiredValue, w.touserdata(-1)));
				}
            }
            else if constexpr (std::is_same_v<T, _Nil>)
            {
                if (!w.isNil(-1))
                {
					myfailf(failureStr, path, getPathIndex, formatTypeMismatchStr(LUA_TNIL, w.type(-1)));
				}
			}
            else
            {
				COMPILE_TIME_CONSTEXPR_IF_ERROR();
			}
            ++getPathIndex;
            w.pop(1);
        };

    using namespace std::string_literals; // makes '"aaa"s' work

    w.dostring("adc = { b = { c = 5 } }");
    w.getglobal("adc");
    getPathTest("b.c", -1, 5LL);
    getPathTest("b", -1, LuaTable{ {{ "c", 5LL }} });
    getPathTest("b.d", -1, Nil);
    w.unsetGlobal("adc");

    w.dostring(R"(
        function f() return { a = false, b = { c = 5 } } end
        _G.fff = { ttt = "aaa", b = { b = {b = {c = "a"} }, d = true, h = 3 } }
    )");

    w.getglobal("f");
    w.call(0, 1);
    getPathTest("a", -1, false);
    getPathTest("b.c", -1, 5LL);
	getPathTest("b", -1, LuaTable{ {{ "c", 5LL }} });
	w.unsetGlobal("f");

    w.getglobal("fff");
    getPathTest("ttt", -1, "aaa"s);
    getPathTest("b.b.b.c", -1, "a"s);
    getPathTest("b.b.b", -1, LuaTable{ {{ "c", "a"s }} });
    getPathTest("b.b", -1, LuaTable{ {{ "b", LuaTable{ {{ "c", "a"s }} }} }});
    getPathTest("b", -1, LuaTable{ {{ "b", LuaTable{ {{ "b", LuaTable{ {{ "c", "a"s }} } }} } }, {"d", true}, {"h", 3}} });
    getPathTest("b.d", -1, true);
    getPathTest("b.h", -1, 3LL);

    getPathTest("b.idhj", -1, Nil);
    getPathTest("b.b.b.idhj", -1, Nil);
    getPathTest("b.b.m", -1, Nil);
    getPathTest("ttttttttttttt", -1, Nil);
    w.unsetGlobal("fff");

    w.settop(stackIndex);
    return myasserter.errors;
}
