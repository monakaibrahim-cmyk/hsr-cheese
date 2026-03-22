#include "pch.h"
#include "main.h"
#include "Menu/menu.h"

BOOL WINAPI DllMain(
	HINSTANCE hinstDLL,
	DWORD fdwReason,
	LPVOID lpvReserved
)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		if (!Menu::Setup())
		{
			return FALSE;
		}
	}

	return TRUE;
}
