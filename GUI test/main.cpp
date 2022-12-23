#include <windows.h>
#include <iostream>
#include <string>

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
	std::string cmd;
	while (std::cin >> cmd)
	{

	}
	FreeLibrary(dll);
	return EXIT_SUCCESS;
}