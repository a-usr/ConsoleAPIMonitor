#pragma once
#include "pch.h"

VOID logFile(const char* str);
VOID logFile(char* str);
VOID logFile(DWORD dword);
VOID logFile(HANDLE handle);
VOID logConsoleMode(DWORD* mode);

extern CMPOBJHANLDES CompareObjectHandlesPt;