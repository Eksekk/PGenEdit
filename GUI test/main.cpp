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
	/*std::fstream file("classData.json");
	assert(file.good());
	std::stringstream ss;
	ss << file.rdbuf();
	auto setClassData = ( bool (__stdcall *)(const char*))GetProcAddress(dll, "setClassData");
	setClassData(ss.str().c_str());
	file.close();
	file = std::fstream("skillData.json");
	assert(file.good());
	std::stringstream ss;
	ss << file.rdbuf();
	auto setClassData = (bool(__stdcall*)(const char*))GetProcAddress(dll, "setClassData");
	setClassData(ss.str().c_str());
	file.close();*/
	auto setClassData = (bool(__stdcall*)(const char*))GetProcAddress(dll, "setClassData");
	setClassData("classData.json");
	auto setSkillData = (bool(__stdcall*)(const char*))GetProcAddress(dll, "setSkillData");
	setSkillData("skillData.json");
	auto displayMainWindow = (void(__stdcall*)(bool))GetProcAddress(dll, "displayMainWindow");
	auto runEventLoopOnce = (void(__stdcall*)(void))GetProcAddress(dll, "runEventLoopOnce");
	std::string cmd;
	displayMainWindow(true);
	while (true)
	{
		runEventLoopOnce();
	}
	FreeLibrary(dll);
	return EXIT_SUCCESS;
}