// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "pch.h"
#include "iostream"
#include "Util.h"

typedef BOOL(WINAPI* CMPOBJHANLDES)(HANDLE h1, HANDLE h2);
CMPOBJHANLDES CompareObjectHandlesPt = (CMPOBJHANLDES) GetProcAddress(GetModuleHandleW(TEXT("kernelbase.dll")), "CompareObjectHandles");

static HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
static HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
static HANDLE hStdErr = GetStdHandle(STD_ERROR_HANDLE);

static HANDLE hIn = hStdIn;
static HANDLE hOut = hStdOut;
static HANDLE hErr = hStdErr;

static HANDLE hConIn = CreateFileW(TEXT("$CONIN\n"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
static HANDLE hConOut = CreateFileW(TEXT("$CONOUT\n"), GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);

// Function Pointers
static BOOL(WINAPI* SetConsoleModeWin)(
  HANDLE CHandle,
  DWORD mode
  )
  = SetConsoleMode;


static BOOL(WINAPI* GetConsoleModeWin)(
  HANDLE CHandle,
  LPDWORD mode
  )
  = GetConsoleMode;


static BOOL(WINAPI* CreateProcessWWin)(
  LPCWSTR name,
  LPWSTR cl,
  LPSECURITY_ATTRIBUTES attr,
  LPSECURITY_ATTRIBUTES thread_attr,
  BOOL inherit_attr,
  DWORD flags,
  LPVOID env,
  LPCWSTR dir,
  LPSTARTUPINFOW info,
  LPPROCESS_INFORMATION p_info
  )
  = CreateProcessW;


static BOOL(WINAPI* CreateProcessAWin)(
  LPCSTR name,
  LPSTR cl, LPSECURITY_ATTRIBUTES attr,
  LPSECURITY_ATTRIBUTES thread_attr,
  BOOL inherit_attr, DWORD flags,
  LPVOID env,
  LPCSTR dir,
  LPSTARTUPINFOA info,
  LPPROCESS_INFORMATION p_info
  )
  = CreateProcessA;


static BOOL(WINAPI* GetConsoleScreenBufferInfoWin)(
  _In_  HANDLE                      hConsoleOutput,
  _Out_ PCONSOLE_SCREEN_BUFFER_INFO lpConsoleScreenBufferInfo
  )
  = GetConsoleScreenBufferInfo;

static BOOL(WINAPI* SetConsoleScreenBufferInfoExWin)(
  _In_ HANDLE                        hConsoleOutput,
  _In_ PCONSOLE_SCREEN_BUFFER_INFOEX lpConsoleScreenBufferInfoEx
  )
  = SetConsoleScreenBufferInfoEx;


static BOOL(WINAPI* GetConsoleScreenBufferInfoExWin)(
  _In_ HANDLE                        hConsoleOutput,
  _Out_ PCONSOLE_SCREEN_BUFFER_INFOEX lpConsoleScreenBufferInfoEx
  )
  = GetConsoleScreenBufferInfoEx;


static DWORD(WINAPI* GetLastErrorWin)() = GetLastError;

BOOL(WINAPI* SetConsoleTextAttributeWin)(
  _In_ HANDLE hConsoleOutput,
  _In_ WORD   wAttributes
  )
  = SetConsoleTextAttribute;


static BOOL(WINAPI* SetStdHandleWin)(
  _In_ DWORD  nStdHandle,
  _In_ HANDLE hHandle
) = SetStdHandle;


static HANDLE(WINAPI* GetStdHandleWin)(
  _In_ DWORD  nStdHandle
) = GetStdHandle;


BOOL(WINAPI* SetConsoleActiveScreenBufferWin)(
  _In_ HANDLE hConsoleOutput
  ) = SetConsoleActiveScreenBuffer;

// Detour Functions
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

BOOL WINAPI CreateProcessWDet(LPCWSTR name, LPWSTR cl, LPSECURITY_ATTRIBUTES attr, LPSECURITY_ATTRIBUTES thread_attr, BOOL inherit_attr, DWORD flags, LPVOID env, LPCWSTR dir, LPSTARTUPINFOW info, LPPROCESS_INFORMATION p_info) {
  logFile("call to CreateProcessW");
  return CreateProcessWWin(name, cl, attr, thread_attr, inherit_attr, flags, env, dir, info, p_info);
}BOOL WINAPI CreateProcessADet(LPCSTR name, LPSTR cl, LPSECURITY_ATTRIBUTES attr, LPSECURITY_ATTRIBUTES thread_attr, BOOL inherit_attr, DWORD flags, LPVOID env, LPCSTR dir, LPSTARTUPINFOA info, LPPROCESS_INFORMATION p_info) {
  logFile("call to CreateProcessA");
  return CreateProcessAWin(name, cl, attr, thread_attr, inherit_attr, flags, env, dir, info, p_info);
}

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

DWORD WINAPI GetLastErrorDet() {
  logFile("Call to GetLastError:");
  DWORD ret = GetLastErrorWin();
  char strDWORD[10];
  sprintf_s(strDWORD, "%d", ret);
  logFile(strDWORD);
  return ret;
}

BOOL WINAPI SetConsoleTextAttributeDet(_In_ HANDLE hConsoleOutput, _In_ WORD wAttributes) {
  logFile("Call to SetConsoleTextAttribute");
  return SetConsoleTextAttributeWin(hConsoleOutput, wAttributes);
}

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

// Attach & Detach
VOID Attach()
{
  DetourTransactionBegin();
  DetourUpdateThread(GetCurrentThread());
  logFile("Attaching...");
  DetourAttach(&(PVOID&)SetConsoleModeWin, SetConsoleModeDet);
  DetourAttach(&(PVOID&)GetConsoleModeWin, GetConsoleModeDet);
  DetourAttach(&(PVOID&)GetConsoleScreenBufferInfoWin, GetConsoleScreenBufferInfoDet);
  DetourAttach(&(PVOID&)SetConsoleScreenBufferInfoExWin, SetConsoleScreenBufferInfoExDet);
  DetourAttach(&(PVOID&)GetConsoleScreenBufferInfoExWin, GetConsoleScreenBufferInfoExDet);
  DetourAttach(&(PVOID&)SetConsoleTextAttributeWin, SetConsoleTextAttributeDet);
  DetourAttach(&(PVOID&)GetStdHandleWin, GetStdHandleDet);
  DetourAttach(&(PVOID&)SetStdHandleWin, SetStdHandleDet);
  DetourAttach(&(PVOID&)SetConsoleActiveScreenBufferWin, SetConsoleActiveScreenBufferDet);

  logFile("Attached to Console API!");
  DetourAttach(&(PVOID&)CreateProcessWWin, CreateProcessWDet);
  DetourAttach(&(PVOID&)CreateProcessAWin, CreateProcessADet);
  logFile("Hooked CreateProcess!");
  //DetourAttach(&(PVOID&)GetLastErrorWin, GetLastErrorDet);
  DetourTransactionCommit();
  logFile("Attatched to Process!");
}

VOID Detach() {
  DetourTransactionBegin();
  DetourUpdateThread(GetCurrentThread());
  DetourDetach(&(PVOID&)SetConsoleModeWin, SetConsoleModeDet);
  DetourDetach(&(PVOID&)GetConsoleModeWin, GetConsoleModeDet);
  DetourDetach(&(PVOID&)GetConsoleScreenBufferInfoWin, GetConsoleScreenBufferInfoDet);
  DetourDetach(&(PVOID&)SetConsoleScreenBufferInfoExWin, SetConsoleScreenBufferInfoExDet);
  DetourDetach(&(PVOID&)GetConsoleScreenBufferInfoExWin, GetConsoleScreenBufferInfoExDet);
  DetourDetach(&(PVOID&)SetConsoleTextAttributeWin, SetConsoleTextAttributeDet);
  DetourDetach(&(PVOID&)GetStdHandleWin, GetStdHandleDet);
  DetourDetach(&(PVOID&)SetStdHandleWin, SetStdHandleDet);
  DetourDetach(&(PVOID&)SetConsoleActiveScreenBufferWin, SetConsoleActiveScreenBufferDet);
  //DetourDetach(&(PVOID&)GetLastErrorWin, GetLastErrorDet);
  DetourDetach(&(PVOID&)CreateProcessWWin, CreateProcessWDet);
  DetourDetach(&(PVOID&)CreateProcessAWin, CreateProcessADet);
  DetourTransactionCommit();
  logFile("Detatched from Process!");
}

// DLLMAIN
BOOL APIENTRY DllMain(HMODULE hModule,
  DWORD  ul_reason_for_call,
  LPVOID lpReserved
)
{
  if (CompareObjectHandlesPt == NULL) {
    return HRESULT_FROM_WIN32(GetLastError());
  }
  if (DetourIsHelperProcess()) {
    return TRUE;
  }

  switch (ul_reason_for_call)
  {
  case DLL_PROCESS_ATTACH:
    DetourRestoreAfterWith();
    logFile("Init!");
    Attach();
    break;
  case DLL_THREAD_ATTACH:
  case DLL_THREAD_DETACH:
    break;
  case DLL_PROCESS_DETACH:
    Detach();
    break;
  }
  return TRUE;
}

