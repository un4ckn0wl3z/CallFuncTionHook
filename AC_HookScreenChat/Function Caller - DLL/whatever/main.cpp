#include "Memory.h"

typedef char*(__cdecl * _ACPrintScreenChat)(char * sFormat, ...);
_ACPrintScreenChat ACPrintScreenChat;

DWORD WINAPI MainThread(LPVOID param)
{
	uintptr_t modBase = (uintptr_t)GetModuleHandle(NULL);
	ACPrintScreenChat = (_ACPrintScreenChat)(modBase + 0x6B060);
	char* sFormat = "%s:\f%d %s";
	//Set up
	ACPrintScreenChat(sFormat, "ACHACK", 1, "Loading.....");
	while (!GetAsyncKeyState(VK_END))
	{
		if(GetAsyncKeyState(VK_NUMPAD1) & 1)
		{
			ACPrintScreenChat(sFormat, "Str1", 1, "str2");
		}
		
	}
	ACPrintScreenChat(sFormat, "ACHACK", 1, "Unloading.....");

	FreeLibraryAndExitThread((HMODULE)param, 0);
	return 0;
}

BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(0, 0, MainThread, hModule, 0, 0);
		break;
	default:
		break;
	}
	return TRUE;
}