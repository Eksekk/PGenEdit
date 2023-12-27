#include "pch.h"
#include "LuaTests.h"
#include "LuaTable.h"
#include "Asserter.h"
#include "LuaWrapper.h"
#include "LuaFunctions.h"
#include "GameStructAccessor.h"

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

    // TODO: also extended Nil test, once I implement appropriate behavior
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
			return std::vformat(typeMismatchStr, std::make_format_args(w.typename_(desiredType), w.typename_(actualType)));
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
