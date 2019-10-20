#include "Memory.h"


typedef  void(__stdcall *_FuncA)();
_FuncA FuncA;

typedef  void(__cdecl *_FuncB)(char * string);
_FuncB FuncB;


DWORD WINAPI MainThread(LPVOID param)
{
	uintptr_t modBase = (uintptr_t)GetModuleHandle(NULL);
	FuncA = (_FuncA)(modBase+0x122C0);
	FuncB = (_FuncB)(modBase + 0x12340);

	//Set up
	
	while (!GetAsyncKeyState(VK_END))
	{
		if(GetAsyncKeyState(VK_NUMPAD2) & 1)
		{
			FuncA();
		}
		if (GetAsyncKeyState(VK_NUMPAD3) & 1)
		{
			FuncB("HOOOOKKED_MSG");
		}
	}
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