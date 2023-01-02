#include <windows.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>

int main()
{
	HMODULE dll = LoadLibraryA("C:\\Users\\Eksekk\\source\\repos\\PartyGenerator\\Debug\\PartyGenerator.dll");
	if (!dll)
	{
		DWORD error = GetLastError();
		char buf[200];
		FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM, 0, error, 0, buf, 200, nullptr);
		std::string s = "Couldn't load library. Error: " + std::string(buf);
		MessageBoxA(nullptr, s.c_str(), "Error", 0);
		return EXIT_FAILURE;
	}
	auto init = GetProcAddress(dll, "init");
	init();
	//char pwd[MAX_PATH];
	//GetCurrentDirectoryA(MAX_PATH, pwd);
	//MessageBoxA(NULL, pwd, "Working directory", 0);
	std::fstream file("classData.json");
	assert(file.good());
	std::stringstream ss;
	ss << file.rdbuf();
	auto setClassData = ( bool (__stdcall *)(const char*))GetProcAddress(dll, "setClassData");
	setClassData(ss.str().c_str());
	std::string cmd;
	while (std::cin >> cmd)
	{

	}
	FreeLibrary(dll);
	return EXIT_SUCCESS;
}