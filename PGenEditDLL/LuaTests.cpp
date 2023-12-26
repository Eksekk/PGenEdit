#include "pch.h"
#include "LuaTests.h"
#include "LuaTable.h"
#include "Asserter.h"
#include "LuaWrapper.h"
#include "LuaFunctions.h"
#include "GameStructAccessor.h"

std::vector<wxString> LuaTests::run()
{
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
        {false, true},
        {true, false},
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
    myassertf(t5.att("ddd").att(false) == true, atStr, atIndex++);
    myassertf(t5.att(t3).att(3) == true, atStr, atIndex++);

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
    myassertf(!t1.att(true).contains("abcd"), containsStr, containsIndex++);
    myassertf(!t1.att(true).contains(51112), containsStr, containsIndex++);
    myassertf(!t5.att(5.0).contains("abcd"), containsStr, containsIndex++);
    myassertf(!t5.att("ddd").contains(true), containsStr, containsIndex++);
    myassertf(!t5.att(t3).contains(4), containsStr, containsIndex++);
    myassertf(!t5.att(t2).contains(t3), containsStr, containsIndex++);
    myassertf(!t5.att(t2).contains(t2), containsStr, containsIndex++);

    // TODO: also extended Nil test, once I implement appropriate behavior
    return myasserter.errors;
}