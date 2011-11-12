//---------------------------------------------------------------------------


#pragma hdrstop
#include "psinfo.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
using  namespace  PsINFO;  
//----TPsinfo Code Begin------------------------------------------------------------------
__fastcall TPsinfo::TPsinfo()
{
    iProcessId = 0xffffffff;
    ProcessList = new TTypeList<PROCESSINFO>(true);
    InitDll();
}
//------------------------------------------------------------------------------
__fastcall TPsinfo::~TPsinfo()
{
    delete ProcessList;
    if(hPSAPI_dll)
        FreeLibrary(hPSAPI_dll);
}
//------------------------------------------------------------------------------
bool TPsinfo::IsWin2k()
{
    OSVERSIONINFO lpOs;
    lpOs.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
    GetVersionEx(&lpOs);
    if (lpOs.dwPlatformId == VER_PLATFORM_WIN32_NT)
        return true;
    else
        return false;
}
//---------------------------------------------------------------------------
DWORD TPsinfo::MyWinExeC(String Cmdline,int Visibility)
{
    DWORD ProcessId;
    String DirName;
    STARTUPINFO StartupInfo;
    PROCESS_INFORMATION ProcessInfo;
    ZeroMemory(&StartupInfo, sizeof(STARTUPINFO));
    DirName = ExtractFileDir(Cmdline);
    StartupInfo.cb = sizeof(StartupInfo);
    StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
    StartupInfo.wShowWindow = Visibility;
    ProcessId = CreateProcess(NULL,(LPSTR)Cmdline.c_str(),NULL,NULL,false,0,NULL,(LPSTR)DirName.c_str(),&StartupInfo,&ProcessInfo);
    if (!ProcessId)
    {
        return 0;
    }
    else
    {
        return  ProcessInfo.dwProcessId;
    }
}

//---------------------------------------------------------------------------
bool  TPsinfo::FindTagWindow(String sClassName,String sFormName)
{
    HWND hTagWindow;
    hTagWindow = FindWindow(sClassName.c_str(),sFormName.c_str());
    return  hTagWindow !=NULL;
}
//---------------------------------------------------------------------------
void TPsinfo::ListProcess9x(void)
{
    PPROCESSINFO NewProcess;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if(hSnapshot != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 ProcessEntry;
        ProcessList->Clear();
        ZeroMemory(&ProcessEntry,sizeof(PROCESSENTRY32));
        ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
        BOOL bFlag = Process32First(hSnapshot,&ProcessEntry);
        while(bFlag)
        {
            if((GetCurrentProcessId() != ProcessEntry.th32ProcessID) && !StrPos(ProcessEntry.szExeFile, "KERNEL32.DLL"))
            {
                NewProcess = new PROCESSINFO;
                NewProcess->ProcessName = ExtractFileName(ProcessEntry.szExeFile);
                NewProcess->ProcessId   = ProcessEntry.th32ProcessID;
                ProcessList->Add(NewProcess);
            }
            ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
            bFlag = Process32Next(hSnapshot,&ProcessEntry);
        }
        CloseHandle(hSnapshot);
    }
}
//---------------------------------------------------------------------------
void TPsinfo::InitDll()
{
    hPSAPI_dll = GetModuleHandle("PSAPI.DLL");
    if(!hPSAPI_dll)
    {
        hPSAPI_dll = LoadLibrary("PSAPI.DLL");
        if(!hPSAPI_dll)
        {
            return;
        }
    }
    aEnumProcesses = (ENUMPROCESSES)GetProcAddress(hPSAPI_dll, "EnumProcesses");
    aEnumProcessModules = (ENUMPROCESSMODULES)GetProcAddress(hPSAPI_dll, "EnumProcessModules");
    aGetModuleBaseName = (GETMODULEBASENAME)GetProcAddress(hPSAPI_dll, "GetModuleBaseNameA");
    aGetModuleFileNameEx = (GETMODULEFILENAMEEX)GetProcAddress(hPSAPI_dll, "GetModuleFileNameExA");
}
//---------------------------------------------------------------------------
void TPsinfo::ListProcessNt(void)
{
    DWORD aProcesses[1024], cbNeeded, cProcesses, i;
    if(!aEnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
    {
        ListProcess9x();
        return;
    }
    ProcessList->Clear();
    cProcesses = cbNeeded / sizeof(DWORD);
    for(i=0;i<cProcesses;i++)
        GetProcessNameAndID(aProcesses[i]);
}
//---------------------------------------------------------------------------
void TPsinfo::GetProcessNameAndID(DWORD processID)
{
    char szProcessName[260] = "unknown";
    DWORD hMod[1024],cbNeeded;
    PPROCESSINFO NewProcess;
    if(GetCurrentProcessId() == processID)
        return;
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
                                  PROCESS_VM_READ,
                                  FALSE, processID);
    if(hProcess)
    {
        if(aEnumProcessModules(hProcess, (HMODULE *)hMod, sizeof(hMod), &cbNeeded))
        {
            aGetModuleBaseName(hProcess, (HMODULE)hMod[0], szProcessName, sizeof(szProcessName));
            NewProcess = new PROCESSINFO;
            NewProcess->ProcessName = ExtractFileName(szProcessName);
            NewProcess->ProcessId   = processID;
            ProcessList->Add(NewProcess);
        }
        CloseHandle(hProcess);
    }
}
//---------------------------------------------------------------------------
DWORD TPsinfo::GetProcessIdByName(String ProcessName)
{
    for (int i=0;i< ProcessList->Count;i++)
    {
        if (ProcessList->Items[i]->ProcessName == ProcessName)
        {
            return ProcessList->Items[i]->ProcessId;
        }
    }
    return 0;
}
//-------------------------------------------------------------------------------------
bool  TPsinfo::GetFileNameByProessId(DWORD ProcessId,LPSTR FileName,DWORD Size)
{
    if (IsWin2k())
    {
        return GetFileName2000(ProcessId,FileName,Size);
    }
    else
    {
        return GetFileName98(ProcessId,FileName,Size);
    }
}
//-------------------------------------------------------------------------------------
bool  TPsinfo::GetFileName2000(DWORD ProcessId,LPSTR FileName,DWORD Size)
{
    HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION |
                                  PROCESS_VM_READ,
                                  FALSE, ProcessId);
    if(hProcess)
    {
        aGetModuleFileNameEx(hProcess,NULL,FileName,Size);
        CloseHandle(hProcess);
        return true;
    }
    return false;
}
//-------------------------------------------------------------------------------------
bool   TPsinfo::GetFileName98(DWORD ProcessId,LPSTR FileName,DWORD Size)
{
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    bool Result=false;
    if(hSnapshot != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 ProcessEntry;
        ZeroMemory(&ProcessEntry,sizeof(PROCESSENTRY32));
        ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
        BOOL bFlag = Process32First(hSnapshot,&ProcessEntry);
        while(bFlag)
        {
            if(ProcessId == ProcessEntry.th32ProcessID)
            {
                if (strlen(ProcessEntry.szExeFile)<Size)
                {
                    strcpy(FileName,ProcessEntry.szExeFile);
                    Result = true;
                    break;
                }
                else
                {
                    Result =false;
                    break;
                }
            }
            ProcessEntry.dwSize = sizeof(PROCESSENTRY32);
            bFlag = Process32Next(hSnapshot,&ProcessEntry);
        }
        CloseHandle(hSnapshot);
    }
    return Result;
}
//---------------------------------------------------------------------------
BOOL CALLBACK TPsinfo::SearchWindowProcByName(HWND hWnd,LPSEARCHWINDOWDATA lpSearchData)
{
  DWORD       iWndProcessId;
  CHAR        lpClassName[256];
  char        ProcessName[256];
  GetClassName(hWnd, lpClassName, 255);
  if(!lpSearchData->strClassName ||
     !strcmp(lpClassName, lpSearchData->strClassName))
  {
    GetWindowText(hWnd, lpClassName, 255);
    if(!lpSearchData->strWindowName ||
       !strcmp(lpClassName, lpSearchData->strWindowName))
    {
      GetWindowThreadProcessId(hWnd, &iWndProcessId);
      ((TPsinfo *)lpSearchData->Owner)->GetFileNameByProessId(iWndProcessId,ProcessName,sizeof(ProcessName));
      if(UpperCase(ExtractFileName(ProcessName)) == UpperCase(lpSearchData->ProcessName))
      {
        lpSearchData->hWnd = hWnd;
        return false;
      }
    }
  }
  return true;
}
//---------------------------------------------------------------------------
BOOL CALLBACK TPsinfo::SearchWindowProc(HWND hWnd,LPSEARCHWINDOWDATA lpSearchData)
{
  DWORD       iWndProcessId;
  CHAR        lpClassName[256];
  GetClassName(hWnd, lpClassName, 255);
  if(!lpSearchData->strClassName ||
     !strcmp(lpClassName, lpSearchData->strClassName))
  {
    GetWindowText(hWnd, lpClassName, 255);
    if(!lpSearchData->strWindowName ||
       !strcmp(lpClassName, lpSearchData->strWindowName))
    {
      GetWindowThreadProcessId(hWnd, &iWndProcessId);
      if(iWndProcessId == lpSearchData->dwOwnerPID)
      {
        lpSearchData->hWnd = hWnd;
        return false;
      }
    }
  }
  return true;
}
//---------------------------------------------------------------------------
HWND __fastcall TPsinfo::SearchWindow(DWORD dwOwnerPID, LPCSTR strClassName, LPCSTR strWindowName)
{
  SEARCHWINDOWDATA lpSearchData;
  lpSearchData.dwOwnerPID = dwOwnerPID;
  lpSearchData.strClassName = strClassName;
  lpSearchData.strWindowName = strWindowName;
  lpSearchData.hWnd = NULL;
  EnumWindows((WNDENUMPROC)SearchWindowProc, (LPARAM)&lpSearchData);
  return lpSearchData.hWnd;
}
//---------------------------------------------------------------------------
HWND __fastcall TPsinfo::SearchWindowByName(LPSTR ProcessName, LPCSTR strClassName, LPCSTR strWindowName)
{
  SEARCHWINDOWDATA lpSearchData;
  lpSearchData.dwOwnerPID = 0;
  lpSearchData.ProcessName  = ProcessName;
  lpSearchData.strClassName = strClassName;
  lpSearchData.strWindowName = strWindowName;
  lpSearchData.Owner = this;
  lpSearchData.hWnd = NULL;
  EnumWindows((WNDENUMPROC)SearchWindowProcByName, (LPARAM)&lpSearchData);
  return lpSearchData.hWnd;
}


