#include "pch.h"
#include <utility>
#include <vector>
#include "Util.h"
#include "Handles.h"

static BOOL(WINAPI* SetConsoleModeWin)(
  HANDLE CHandle,
  DWORD mode
  )
  = SetConsoleMode;

BOOL WINAPI SetConsoleModeDet(HANDLE Console, DWORD mode) {
  logFile("Call to SetConsoleMode on Handle:");
  if (CompareObjectHandlesPt(Console, hConIn)) {
    logFile("ConIn");
  }
  else if (CompareObjectHandlesPt(Console, hConOut)) {
    logFile("ConOut");
  }
  else if (CompareObjectHandlesPt(Console, hStdIn)) {
    logFile("std::In");
  }
  else if (CompareObjectHandlesPt(Console, hStdOut)) {
    logFile("std::Out");
  }
  else if (CompareObjectHandlesPt(Console, hStdErr)) {
    logFile("std::Err");
  }
  else if (CompareObjectHandlesPt(Console, hIn)) {
    logFile("custom::In");
  }
  else if (CompareObjectHandlesPt(Console, hOut)) {
    logFile("custom::Out");
  }
  else if (CompareObjectHandlesPt(Console, hErr)) {
    logFile("custom::Err");
  }
  else {
    logFile("Unknown:");
    logFile("Address:");
    logFile(Console);
  }
  logConsoleMode(&mode);
  return SetConsoleModeWin(Console, mode);
}



static BOOL(WINAPI* GetConsoleModeWin)(
  HANDLE CHandle,
  LPDWORD mode
  )
  = GetConsoleMode;

BOOL WINAPI GetConsoleModeDet(_In_  HANDLE  hConsoleHandle, _Out_ LPDWORD lpMode) {
  logFile("Call to GetConsoleMode on Handle:");
  if (CompareObjectHandlesPt(hConsoleHandle, hConIn)) {
    logFile("ConIn");
  }
  else if (CompareObjectHandlesPt(hConsoleHandle, hConOut)) {
    logFile("ConOut");
  }
  else if (CompareObjectHandlesPt(hConsoleHandle, hStdIn)) {
    logFile("std::In");
  }
  else if (CompareObjectHandlesPt(hConsoleHandle, hStdOut)) {
    logFile("std::Out");
  }
  else if (CompareObjectHandlesPt(hConsoleHandle, hStdErr)) {
    logFile("std::Err");
  }
  else if (CompareObjectHandlesPt(hConsoleHandle, hIn)) {
    logFile("custom::In");
  }
  else if (CompareObjectHandlesPt(hConsoleHandle, hOut)) {
    logFile("custom::Out");
  }
  else if (CompareObjectHandlesPt(hConsoleHandle, hErr)) {
    logFile("custom::Err");
  }
  else {
    logFile("Unknown");
    logFile("Address:");
    logFile(hConsoleHandle);
  }
  bool ret = GetConsoleModeWin(hConsoleHandle, lpMode);
  logConsoleMode(lpMode);
  return ret;
}



static BOOL(WINAPI* GetConsoleScreenBufferInfoWin)(
  _In_  HANDLE                      hConsoleOutput,
  _Out_ PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo
  )
  = GetConsoleScreenBufferInfo;

BOOL WINAPI GetConsoleScreenBufferInfoDet(_In_  HANDLE hConsoleOutput, _Out_ PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo)
{
  logFile("Call to GetConsoleScreenBufferInfo on Handle");
  if (CompareObjectHandlesPt(hConOut, hConsoleOutput)) {
    logFile("ConOut\n\n");
  }
  else {
    logFile("Unknown:");
    logFile("Address:");
    logFile(hConsoleOutput);
    logFile("\n");
  }
  return GetConsoleScreenBufferInfoWin(hConsoleOutput, lpConsoleScreenBufferInfo);
}



static BOOL(WINAPI* SetConsoleScreenBufferInfoExWin)(
  _In_ HANDLE                        hConsoleOutput,
  _In_ PCONSOLE_SCREEN_BUFFER_INFOEX lpConsoleScreenBufferInfoEx
  )
  = SetConsoleScreenBufferInfoEx;

BOOL WINAPI SetConsoleScreenBufferInfoExDet(_In_ HANDLE hConsoleOutput, _In_ PCONSOLE_SCREEN_BUFFER_INFOEX lpConsoleScreenBufferInfoEx) {

  logFile("Call to SetConsoleScreenBufferInfoEx on Handle");
  if (CompareObjectHandlesPt(hConOut, hConsoleOutput)) {
    logFile("ConOut\n\n");
  }
  else {
    logFile("Unknown:");
    logFile("Address:");
    logFile(hConsoleOutput);
    logFile("\n");
  }
  return SetConsoleScreenBufferInfoExWin(hConsoleOutput, lpConsoleScreenBufferInfoEx);
}



static BOOL(WINAPI* GetConsoleScreenBufferInfoExWin)(
  _In_ HANDLE                        hConsoleOutput,
  _Out_ PCONSOLE_SCREEN_BUFFER_INFOEX lpConsoleScreenBufferInfoEx
  )
  = GetConsoleScreenBufferInfoEx;

BOOL WINAPI GetConsoleScreenBufferInfoExDet(_In_ HANDLE hConsoleOutput, _Out_ PCONSOLE_SCREEN_BUFFER_INFOEX lpConsoleScreenBufferInfoEx) {
  logFile("Call to GetConsoleScreenBufferInfoEx on Handle");
  if (CompareObjectHandlesPt(hConOut, hConsoleOutput)) {
    logFile("ConOut\n\n");
  }
  else {
    logFile("Unknown:");
    logFile("Address:");
    logFile(hConsoleOutput);
    logFile("\n");
  }
  return GetConsoleScreenBufferInfoExWin(hConsoleOutput, lpConsoleScreenBufferInfoEx);
}



static DWORD(WINAPI* GetLastErrorWin)() = GetLastError;


DWORD WINAPI GetLastErrorDet() {
  logFile("Call to GetLastError:");
  DWORD ret = GetLastErrorWin();
  char strDWORD[10];
  sprintf_s(strDWORD, "%d", ret);
  logFile(strDWORD);
  return ret;
}



BOOL(WINAPI* SetConsoleTextAttributeWin)(
  _In_ HANDLE hConsoleOutput,
  _In_ WORD   wAttributes
  )
  = SetConsoleTextAttribute;

BOOL WINAPI SetConsoleTextAttributeDet(_In_ HANDLE hConsoleOutput, _In_ WORD wAttributes) {
  logFile("Call to SetConsoleTextAttribute");
  return SetConsoleTextAttributeWin(hConsoleOutput, wAttributes);
}



static BOOL(WINAPI* SetStdHandleWin)(
  _In_ DWORD  nStdHandle,
  _In_ HANDLE hHandle
  ) = SetStdHandle;

BOOL WINAPI SetStdHandleDet(_In_ DWORD  nStdHandle, _In_ HANDLE hHandle) {
  logFile("Call to SetStdHandle");
  BOOL ret = SetStdHandleWin(nStdHandle, hHandle);
  if (ret) {
    if (nStdHandle == STD_INPUT_HANDLE) {
      logFile("Set Handle std::In");
      hIn = hHandle;
    }
    else if (nStdHandle == STD_OUTPUT_HANDLE) {
      logFile("Set Handle std::Out");
      hOut = hHandle;
    }
    else if (nStdHandle == STD_ERROR_HANDLE) {
      logFile("Set Handle std::Err");
      hErr = hHandle;
    }
    else {
      logFile("Unknown Handle Deskriptor");
    }
  }
  else {
    logFile("Error Occured");
    logFile(GetLastError());
  }
  logFile("\n");
  return ret;
}




static HANDLE(WINAPI* GetStdHandleWin)(
  _In_ DWORD  nStdHandle
  ) = GetStdHandle;

HANDLE WINAPI GetStdHandleDet(_In_ DWORD nStdHandle) {
  logFile("Call to GetStdHandle");
  HANDLE ret = GetStdHandleWin(nStdHandle);
  if (ret != INVALID_HANDLE_VALUE) {
    if (nStdHandle == STD_INPUT_HANDLE) {
      logFile("Get Handle std::In");
      if (ret != hIn) {
        logFile("hIn got changed outside of the Application?");
        hIn = ret;
      }
    }
    else if (nStdHandle == STD_OUTPUT_HANDLE) {
      logFile("Get Handle std::Out");
      if (ret != hOut) {
        logFile("hOut got changed outside of the Application?");
        hOut = ret;
      }
    }
    else if (nStdHandle == STD_ERROR_HANDLE) {
      logFile("Get Handle std::Err");
      if (ret != hErr) {
        logFile("hErr got changed outside of the Application?");
        hErr = ret;
      }
    }
    else {
      logFile("Unknown Handle Deskriptor");
    }
  }
  else {
    logFile("Error Occured");
    logFile(GetLastError());
  }
  logFile("\n");
  return ret;
}




BOOL(WINAPI* SetConsoleActiveScreenBufferWin)(
  _In_ HANDLE hConsoleOutput
  ) = SetConsoleActiveScreenBuffer;

BOOL WINAPI SetConsoleActiveScreenBufferDet(_In_ HANDLE hConsoleOutput) {
  logFile("Call to SetConsoleActiveScreenBuffer");
  BOOL ret = SetConsoleActiveScreenBufferWin(hConsoleOutput);
  if (ret != 0) {
    logFile("Error during call:");
    logFile(ret);
  }
  else hConOut = hConsoleOutput;
  return ret;
}


namespace ConsoleAPI {

  std::vector<std::pair<PVOID*, PVOID>> detours = {
     std::make_pair(&(PVOID&)SetConsoleModeWin, SetConsoleModeDet),
     std::make_pair(&(PVOID&)GetConsoleModeWin, GetConsoleModeDet),
     std::make_pair(&(PVOID&)GetConsoleScreenBufferInfoWin, GetConsoleScreenBufferInfoDet),
     std::make_pair(&(PVOID&)SetConsoleScreenBufferInfoExWin, SetConsoleScreenBufferInfoExDet),
     std::make_pair(&(PVOID&)GetConsoleScreenBufferInfoExWin, GetConsoleScreenBufferInfoExDet),
     std::make_pair(&(PVOID&)SetConsoleTextAttributeWin, SetConsoleTextAttributeDet),
     std::make_pair(&(PVOID&)GetStdHandleWin, GetStdHandleDet),
     std::make_pair(&(PVOID&)SetStdHandleWin, SetStdHandleDet),
     std::make_pair(&(PVOID&)SetConsoleActiveScreenBufferWin, SetConsoleActiveScreenBufferDet)
  };
}