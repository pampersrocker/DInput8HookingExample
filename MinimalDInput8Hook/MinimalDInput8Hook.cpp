// MinimalDInput8Hook.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "DInput8.h"
#include "CustomHooks.h"
DirectInput8Create_t OriginalFunction = nullptr;
HMODULE DInput8DLL = nullptr;



DINPUT8_API HRESULT WINAPI DirectInput8Create(HINSTANCE hinst, DWORD dwVersion, REFIID riidltf, LPVOID * ppvOut, LPUNKNOWN punkOuter)
{
	// MSVC will mangle the name of __stdcall functions, even in C
	// Workaround to avoid needing a .def file from https://stackoverflow.com/a/2805560
	#pragma comment(linker, "/EXPORT:" __FUNCTION__ "=" __FUNCDNAME__)
	if (OriginalFunction)
	{
		return OriginalFunction(hinst, dwVersion, riidltf, ppvOut, punkOuter);
	}
	return S_FALSE;
}
