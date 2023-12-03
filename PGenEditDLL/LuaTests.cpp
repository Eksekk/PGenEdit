#include "pch.h"
#include "LuaTests.h"
#include "LuaTable.h"
#include "Asserter.h"
#include "LuaWrapper.h"
#include "LuaFunctions.h"

std::vector<wxString> LuaTests::run()
{
    Asserter myasserter("Lua tests");
    // LuaTable
    auto luaTablePassthrough = [&](const LuaTable& orig, int index)
        {
            orig.pushToLuaStack(Lua);
            LuaTable created = LuaTable::fromLuaTable();
            if (created != orig)
            {
                myassertf(false, "[LuaTable] Test #%d failed", index);
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

    // TODO: also extended Nil test, once I implement appropriate behavior
    return myasserter.errors;
}