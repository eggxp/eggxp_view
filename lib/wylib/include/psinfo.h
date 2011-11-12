//---------------------------------------------------------------------------

#ifndef psinfoH
#define psinfoH
//---------------------------------------------------------------------------
#endif
#include <vcl.h>
#include <tlhelp32.h>
#include "mlist.h"

namespace  PsINFO  
{  


typedef BOOL (WINAPI *ENUMPROCESSES)(DWORD *lpidProcess,     // array of process identifiers
                                     DWORD cb,            // size of array
                                     DWORD *cbNeeded);    // number of bytes returned
typedef BOOL (WINAPI *ENUMPROCESSMODULES)(HANDLE hProcess,   // handle to process
        HMODULE *lphModule,   // array of module handles
        DWORD cb,             // size of array
        LPDWORD lpcbNeeded);  // number of bytes required
typedef DWORD (WINAPI *GETMODULEBASENAME)(HANDLE hProcess, HMODULE hModule, LPTSTR BaseName, DWORD BaseNameSize);
typedef DWORD (WINAPI *GETMODULEFILENAMEEX)(HANDLE hProcess, // handle to process
        HMODULE hModule,    // handle to module
        LPTSTR lpFilename,  // path buffer
        DWORD nSize);       // maximum characters to retrieve

typedef struct tagPROCESSINFO
{
    String ProcessName;
    DWORD  ProcessId;
}
PROCESSINFO,*PPROCESSINFO;


typedef struct tagSearchWindowData
{
  DWORD  dwOwnerPID;
  LPCSTR strClassName;
  LPCSTR strWindowName;
  LPCSTR ProcessName;
  void   *Owner;
  HWND   hWnd;
}SEARCHWINDOWDATA, *LPSEARCHWINDOWDATA;


class TPsinfo
{
private:
    HINSTANCE             hDll;
    HANDLE                hPSAPI_dll;
    ENUMPROCESSES         aEnumProcesses;
    ENUMPROCESSMODULES    aEnumProcessModules;
    GETMODULEBASENAME     aGetModuleBaseName;
    GETMODULEFILENAMEEX   aGetModuleFileNameEx;
    DWORD                 iProcessId;
    bool                  GetFileName2000(DWORD ProcessId,LPSTR FileName,DWORD Size);
    bool                  GetFileName98(DWORD ProcessId,LPSTR FileName,DWORD Size);
public:
    TTypeList <PROCESSINFO> * ProcessList;
public:
    __fastcall TPsinfo();
    __fastcall ~TPsinfo();
    bool  IsWin2k();
    DWORD MyWinExeC(String Cmdline,int Visibility);
    bool  FindTagWindow(String sClassName,String sFormName);
    void  GetProcessNameAndID(DWORD processID);
    void  ListProcess9x(void); //遍历所有进程 for 9x
    void  ListProcessNt(void); //遍历所有进程 for nt,2k
    void  InitDll();
    DWORD  GetProcessIdByName(String ProcessName);
    bool  GetFileNameByProessId(DWORD ProcessId,LPSTR FileName,DWORD Size);
    static BOOL CALLBACK SearchWindowProc(HWND hWnd,LPSEARCHWINDOWDATA lpSearchData);
    static BOOL CALLBACK SearchWindowProcByName(HWND hWnd,LPSEARCHWINDOWDATA lpSearchData);
    HWND __fastcall SearchWindow(DWORD dwOwnerPID, LPCSTR strClassName, LPCSTR strWindowName);
    HWND __fastcall SearchWindowByName(LPSTR ProcessName, LPCSTR strClassName, LPCSTR strWindowName);
};
}



