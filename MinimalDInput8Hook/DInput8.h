#pragma once
#include <unknwn.h>

typedef HRESULT(WINAPI*DirectInput8Create_t)(
	HINSTANCE hinst,
	DWORD dwVersion,
	REFIID riidltf,
	LPVOID * ppvOut,
	LPUNKNOWN punkOuter
	);

extern DirectInput8Create_t OriginalFunction;
extern HMODULE DInput8DLL;

extern "C"
{
	DINPUT8_API HRESULT WINAPI DirectInput8Create(
		HINSTANCE hinst,
		DWORD dwVersion,
		REFIID riidltf,
		LPVOID * ppvOut,
		LPUNKNOWN punkOuter
	);
}