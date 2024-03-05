// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "pch.h"
#include "iostream"
#include "Util.h"
#include "Handles.h"
#include "ConsoleAPI.h"

//CMPOBJHANLDES CompareObjectHandlesPt = (CMPOBJHANLDES) GetProcAddress(GetModuleHandleW(TEXT("kernelbase.dll")), "CompareObjectHandles");




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

BOOL WINAPI CreateProcessWDet(LPCWSTR name, LPWSTR cl, LPSECURITY_ATTRIBUTES attr, LPSECURITY_ATTRIBUTES thread_attr, BOOL inherit_attr, DWORD flags, LPVOID env, LPCWSTR dir, LPSTARTUPINFOW info, LPPROCESS_INFORMATION p_info) {
  logFile("call to CreateProcessW");
  return CreateProcessWWin(name, cl, attr, thread_attr, inherit_attr, flags, env, dir, info, p_info);
}BOOL WINAPI CreateProcessADet(LPCSTR name, LPSTR cl, LPSECURITY_ATTRIBUTES attr, LPSECURITY_ATTRIBUTES thread_attr, BOOL inherit_attr, DWORD flags, LPVOID env, LPCSTR dir, LPSTARTUPINFOA info, LPPROCESS_INFORMATION p_info) {
  logFile("call to CreateProcessA");
  return CreateProcessAWin(name, cl, attr, thread_attr, inherit_attr, flags, env, dir, info, p_info);
}



// Attach & Detach
VOID Attach()
{
  DetourTransactionBegin();
  DetourUpdateThread(GetCurrentThread());
  logFile("Attaching...");
  for (int i = 0; i < ConsoleAPI::detours.size(); i++) {
    DetourAttach(ConsoleAPI::detours[i].first, ConsoleAPI::detours[i].second);
  }

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
  for (int i = 0; i < ConsoleAPI::detours.size(); i++) {
    DetourDetach(ConsoleAPI::detours[i].first, ConsoleAPI::detours[i].second);
  }
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

