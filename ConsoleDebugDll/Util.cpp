#include "pch.h"
#include <iostream>


CMPOBJHANLDES CompareObjectHandlesPt = (CMPOBJHANLDES)GetProcAddress(GetModuleHandleW(TEXT("kernelbase.dll")), "CompareObjectHandles");

//#include <windows.h>
VOID logFile(char* str) {
  std::cerr << str << "\n";
}
VOID logFile(const char* str) {
  std::cerr << str << "\n";
}
VOID logFile(DWORD dword) {
  std::cerr << dword << "\n";
}
VOID logFile(HANDLE handle) {
  std::cerr << handle << "\n";
}
VOID logConsoleMode(DWORD* mode) {
  logFile("Input Modes:");
  if (*mode & ENABLE_PROCESSED_INPUT) {
    logFile("ENABLE_PROCESSED_INPUT");
  }
  if (*mode & ENABLE_ECHO_INPUT) {
    logFile("ENABLE_ECHO_INPUT");
  }
  if (*mode & ENABLE_INSERT_MODE) {
    logFile("ENABLE_INSERT_MODE");
  }
  if (*mode & ENABLE_LINE_INPUT) {
    logFile("ENABLE_LINE_INPUT");
  }
  if (*mode & ENABLE_MOUSE_INPUT) {
    logFile("ENABLE_MOUSE_INPUT");
  }
  if (*mode & ENABLE_QUICK_EDIT_MODE) {
    logFile("ENABLE_QUICK_EDIT_MODE");
  }
  if (*mode & ENABLE_WINDOW_INPUT) {
    logFile("ENABLE_WINDOW_INPUT");
  }
  if (*mode & ENABLE_VIRTUAL_TERMINAL_INPUT) {
    logFile("ENABLE_VIRTUAL_TERMINAL_INPUT");
  }
  logFile("\nOutput Modes:");
  if (*mode & ENABLE_PROCESSED_OUTPUT) {
    logFile("ENABLE_PROCESSED_OUTPUT");
  }
  if (*mode & ENABLE_WRAP_AT_EOL_OUTPUT) {
    logFile("ENABLE_WRAP_AT_EOL_OUTPUT");
  }
  if (*mode & DISABLE_NEWLINE_AUTO_RETURN) {
    logFile("DISABLE_NEWLINE_AUTO_RETURN");
  }
  if (*mode & ENABLE_LVB_GRID_WORLDWIDE) {
    logFile("ENABLE_LVB_GRID_WORLDWIDE");
  }
  if (*mode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) {
    logFile("ENABLE_VIRTUAL_TERMINAL_PROCESSING");
  }
  logFile("Raw DWORD: ");
  logFile(*mode);
  logFile("\n");
  std::cout.flush();
}