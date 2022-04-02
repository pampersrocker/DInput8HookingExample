#include "stdafx.h"
#include "CustomHooks.h"

typedef HANDLE(WINAPI*CreateFileA_t)(
	LPCSTR                lpFileName,
	DWORD                 dwDesiredAccess,
	DWORD                 dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD                 dwCreationDisposition,
	DWORD                 dwFlagsAndAttributes,
	HANDLE                hTemplateFile);

typedef HANDLE(WINAPI*CreateFileW_t)(
	LPCWSTR                lpFileName,
	DWORD                 dwDesiredAccess,
	DWORD                 dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD                 dwCreationDisposition,
	DWORD                 dwFlagsAndAttributes,
	HANDLE                hTemplateFile);

CreateFileA_t OriginalCreateFileA;
CreateFileW_t OriginalCreateFileW;

HANDLE WINAPI CreateFileA_Wrapper(
	LPCSTR                lpFileName,
	DWORD                 dwDesiredAccess,
	DWORD                 dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD                 dwCreationDisposition,
	DWORD                 dwFlagsAndAttributes,
	HANDLE                hTemplateFile
)
{
	// Do our custom stuff and parameter rewriting
	WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), lpFileName, (DWORD)strlen(lpFileName), nullptr, nullptr);
	WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), "\n", 1, nullptr, nullptr);

	// Call the original CreateFileA function
	return OriginalCreateFileA(
		lpFileName,
		dwDesiredAccess,
		dwShareMode,
		lpSecurityAttributes,
		dwCreationDisposition,
		dwFlagsAndAttributes,
		hTemplateFile);
}

HANDLE WINAPI CreateFileW_Wrapper(
	LPCWSTR                lpFileName,
	DWORD                 dwDesiredAccess,
	DWORD                 dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD                 dwCreationDisposition,
	DWORD                 dwFlagsAndAttributes,
	HANDLE                hTemplateFile
)
{
	// Do our custom stuff and parameter rewriting
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), lpFileName, (DWORD)wcslen(lpFileName), nullptr, nullptr);
	WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), L"\n", 1, nullptr, nullptr);

	// Call the original CreateFileW function
	return OriginalCreateFileW(
		lpFileName,
		dwDesiredAccess,
		dwShareMode,
		lpSecurityAttributes,
		dwCreationDisposition,
		dwFlagsAndAttributes,
		hTemplateFile);
}

void SetupHooks()
{
	// Create a console for Debug output
	AllocConsole();

	// Setup hooks here, see examples below
	
	OriginalCreateFileA = HookFunction("KERNEL32.dll", "CreateFileA", &CreateFileA_Wrapper);
	OriginalCreateFileW = HookFunction("KERNEL32.dll", "CreateFileW", &CreateFileW_Wrapper);
}

