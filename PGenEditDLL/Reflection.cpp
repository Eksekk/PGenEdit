#include "pch.h"
#include "Reflection.h"

using type = rttr::type;
using type_id = type::type_id;
const type_id Reflection::TYPE_ID_CHAR = type::get<char>().get_id();
const type_id Reflection::TYPE_ID_UNSIGNED_CHAR = type::get<unsigned char>().get_id();
const type_id Reflection::TYPE_ID_SHORT = type::get<short>().get_id();
const type_id Reflection::TYPE_ID_UNSIGNED_SHORT = type::get<unsigned short>().get_id();
const type_id Reflection::TYPE_ID_INT = type::get<int>().get_id();
const type_id Reflection::TYPE_ID_UNSIGNED_INT = type::get<unsigned int>().get_id();
const type_id Reflection::TYPE_ID_LONG = type::get<long>().get_id();
const type_id Reflection::TYPE_ID_UNSIGNED_LONG = type::get<unsigned long>().get_id();
const type_id Reflection::TYPE_ID_LONG_LONG = type::get<long long>().get_id();
const type_id Reflection::TYPE_ID_UNSIGNED_LONG_LONG = type::get<unsigned long long>().get_id();
const type_id Reflection::TYPE_ID_FLOAT = type::get<float>().get_id();
const type_id Reflection::TYPE_ID_DOUBLE = type::get<double>().get_id();
const type_id Reflection::TYPE_ID_LONG_DOUBLE = type::get<long double>().get_id();
const type_id Reflection::TYPE_ID_BOOL = type::get<bool>().get_id();
const type_id Reflection::TYPE_ID_STRING_VIEW = type::get<std::string_view>().get_id();
const type_id Reflection::TYPE_ID_STRING = type::get<std::string>().get_id();
const type_id Reflection::TYPE_ID_VOID_PTR = type::get<void*>().get_id();
const type_id Reflection::TYPE_ID_LUA_TABLE = type::get<LuaTable>().get_id();
const type_id Reflection::TYPE_ID_NIL = type::get<_Nil>().get_id();

const std::vector<type_id> Reflection::TYPE_IDS_INTEGERS{ TYPE_ID_CHAR, TYPE_ID_UNSIGNED_CHAR, TYPE_ID_SHORT, TYPE_ID_UNSIGNED_SHORT, TYPE_ID_INT, TYPE_ID_UNSIGNED_INT, TYPE_ID_LONG, TYPE_ID_UNSIGNED_LONG, TYPE_ID_LONG_LONG, TYPE_ID_UNSIGNED_LONG_LONG };
const std::vector<type_id> Reflection::TYPE_IDS_FLOATS{ TYPE_ID_FLOAT, TYPE_ID_DOUBLE, TYPE_ID_LONG_DOUBLE };
const std::vector<type_id> Reflection::TYPE_IDS_STRINGS{ TYPE_ID_STRING_VIEW, TYPE_ID_STRING };
const std::vector<type_id> Reflection::TYPE_IDS_NUMBERS{ compileTimeMergeVectors({TYPE_IDS_INTEGERS, TYPE_IDS_FLOATS }) };
// this one doesn't use "pointer" vector to merge, because strings already contain char pointers
const std::vector<type_id> Reflection::TYPE_IDS_ALL_TYPES{ compileTimeMergeVectors({TYPE_IDS_NUMBERS, TYPE_IDS_STRINGS, {TYPE_ID_BOOL, TYPE_ID_VOID_PTR, TYPE_ID_NIL} }) };