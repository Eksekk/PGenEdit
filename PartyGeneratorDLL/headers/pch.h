// pch.h: wstępnie skompilowany plik nagłówka.
// Wymienione poniżej pliki są kompilowane tylko raz, co poprawia wydajność kompilacji dla przyszłych kompilacji.
// Ma to także wpływ na wydajność funkcji IntelliSense, w tym uzupełnianie kodu i wiele funkcji przeglądania kodu.
// Jednak WSZYSTKIE wymienione tutaj pliki będą ponownie kompilowane, jeśli którykolwiek z nich zostanie zaktualizowany między kompilacjami.
// Nie dodawaj tutaj plików, które będziesz często aktualizować (obniża to korzystny wpływ na wydajność).

#ifndef PCH_H
#define PCH_H

// w tym miejscu dodaj nagłówki, które mają być wstępnie kompilowane

// need to include wx before <cstring>, otherwise there'll be a ton of warnings
// For compilers that support precompilation, includes "wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
	#include <wx/wx.h>
#endif
#include <cstdint>
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>
//#include <WinSock2.h>
#define WIN32_LEAN_AND_MEAN // prevents above winsock problem (error if windows.h is included before winsock)
#include <windows.h>
#include <format>
#include <type_traits>

#endif //PCH_H
