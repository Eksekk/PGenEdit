#include "pch.h"
#include "LuaTests.h"
#include "LuaTable.h"
#include "Asserter.h"

std::vector<wxString> LuaTests::run()
{
    Asserter myasserter("Lua tests");
    // LuaTable
    auto luaTablePassthrough = [&](const LuaTable& t, int index)
        {
            t.toLuaTable();
            myassertf(LuaTable::fromLuaTable() == t, "[LuaTable] Test #%d failed", index);
        };

    LuaTable t = { {
        {"abc", 5LL},
        {5LL, 24LL},
        {true, true},
        } };
    luaTablePassthrough(t, 1);
    return myasserter.errors;
}