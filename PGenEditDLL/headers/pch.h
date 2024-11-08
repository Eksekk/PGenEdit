﻿// pch.h: wstępnie skompilowany plik nagłówka.
// Wymienione poniżej pliki są kompilowane tylko raz, co poprawia wydajność kompilacji dla przyszłych kompilacji.
// Ma to także wpływ na wydajność funkcji IntelliSense, w tym uzupełnianie kodu i wiele funkcji przeglądania kodu.
// Jednak WSZYSTKIE wymienione tutaj pliki będą ponownie kompilowane, jeśli którykolwiek z nich zostanie zaktualizowany między kompilacjami.
// Nie dodawaj tutaj plików, które będziesz często aktualizować (obniża to korzystny wpływ na wydajność).

#ifndef PCH_H
#define PCH_H

// w tym miejscu dodaj nagłówki, które mają być wstępnie kompilowane

// need to include wx before <cstring>, otherwise there'll be a ton of warnings
// For compilers that support precompilation, includes "wx.h".

#define wxUSE_TOOLTIPS 1 // required or tooltips simply don't show up - STILL DON'T WORK
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif

#include <cstdint>
#include <cstring>
#include <cassert>
#include <ctime>

//#include <WinSock2.h>
#define WIN32_LEAN_AND_MEAN // prevents above winsock problem (error if windows.h is included before winsock)
#include <windows.h>

#include <string>
#include <unordered_map>
#include <vector>
#include <format>
#include <type_traits>
#include <random>
#include <fstream>
#include <filesystem>
#include <chrono>
#include <limits>
#include <ranges>
#include <functional>
#include <variant>
#include <regex>
#include <set>
#include <unordered_set>
#include <source_location>

#include <boost/pfr.hpp>
namespace pfr = boost::pfr;
#include <boost/preprocessor.hpp>
#include "CreateObjectVisitor.h"
#include <rttr/registration>
#include <rttr/registration_friend.h>

extern "C"
{
#include <lua.h>
#include <lauxlib.h>

// make stuff like lua_State* work with RTTR (be defined, not only declared)
#include <lj_obj.h>
}

// game structs
// include order is important
#include "Common.h"
#include "Lod.h"
#include "GameMisc.h"
#include "Monster.h"
#include "GameDataStructs.h"
#include "Player.h"
#include "GameParty.h"
#include "MapElements.h"
#include "MapModel.h"
#include "MapMisc.h"
#include "TxtFileItems.h"
#include "GameMap.h"
#include "Bin.h"
#include "Arcomage.h"
#include "MergeSpecific.h"
#include "GameStructure.h"
#include "Structs.h"

#endif //PCH_H