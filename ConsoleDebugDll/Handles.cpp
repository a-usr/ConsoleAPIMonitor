#include "pch.h"

HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hStdErr = GetStdHandle(STD_ERROR_HANDLE);

HANDLE hIn = hStdIn;
HANDLE hOut = hStdOut;
HANDLE hErr = hStdErr;

HANDLE hConIn = CreateFileW(TEXT("$CONIN\n"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
HANDLE hConOut = CreateFileW(TEXT("$CONOUT\n"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
