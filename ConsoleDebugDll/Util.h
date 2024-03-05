#pragma once
#include <Windows.h>
VOID logFile(const char* str);
VOID logFile(char* str);
VOID logFile(DWORD dword);
VOID logFile(HANDLE handle);
VOID logConsoleMode(DWORD* mode);