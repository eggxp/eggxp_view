//---------------------------------------------------------------------------
#include <windows.h>
#pragma hdrstop

#include "UnicodeSupport.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
WIDECHARTOMULTIBYTE fn_OldWideCharToMultiByte;
//---------------------------------------------------------------------------
int WINAPI NewWideCharToMultiByte(UINT CodePage,	        // code page
                                  DWORD dwFlags,	        // performance and mapping flags
                                  LPCWSTR lpWideCharStr,	// address of wide-character string
                                  int cchWideChar,	        // number of characters in string
                                  LPSTR lpMultiByteStr,	        // address of buffer for new string
                                  int cchMultiByte,	        // size of buffer
                                  LPCSTR lpDefaultChar,	        // address of default for unmappable characters
                                  LPBOOL lpUsedDefaultChar)	// address of flag set when default char. used
{
 // if(CP_ACP == CodePage)
 //   CodePage = 936;
  CodePage = 936;
  return fn_OldWideCharToMultiByte(CodePage, dwFlags,
                                   lpWideCharStr, cchWideChar,
                                   lpMultiByteStr, cchMultiByte,
                                   lpDefaultChar, lpUsedDefaultChar);
}
//---------------------------------------------------------------------------
bool InitSimplifiedChinese(void)
{
  DWORD iAddr, iNewAddr;
  DWORD lpflOldProtect;
  LPBYTE lp_WideCharToMultiByte;
  MEMORY_BASIC_INFORMATION mbi_Memory;

  lp_WideCharToMultiByte = (LPBYTE)&WideCharToMultiByte;
  if(0x25FF == *LPWORD(lp_WideCharToMultiByte))
  {
    try
    {
      iAddr = *LPDWORD(lp_WideCharToMultiByte + 2);
      iNewAddr = (DWORD)&NewWideCharToMultiByte;
      fn_OldWideCharToMultiByte = (WIDECHARTOMULTIBYTE)*LPDWORD(iAddr);
      VirtualQuery((LPVOID)iAddr, &mbi_Memory, sizeof(MEMORY_BASIC_INFORMATION));
      VirtualProtect(mbi_Memory.BaseAddress, mbi_Memory.RegionSize, PAGE_EXECUTE_READWRITE, &lpflOldProtect);
      *LPDWORD(iAddr) = iNewAddr;
    }
    catch(...)
    {
    }
    return true;
  }
  return false;
}

//---------------------------------------------------------------------------
bool DeInitSimplifiedChinese(void){  DWORD iAddr, iNewAddr;  DWORD lpflOldProtect;  LPBYTE lp_WideCharToMultiByte;  MEMORY_BASIC_INFORMATION mbi_Memory;  lp_WideCharToMultiByte = (LPBYTE)&WideCharToMultiByte;  if(0x25FF == *LPWORD(lp_WideCharToMultiByte))  {    try    {      iAddr = *LPDWORD(lp_WideCharToMultiByte + 2);      iNewAddr = (DWORD)&NewWideCharToMultiByte;      if ( iNewAddr == *LPDWORD(iAddr) )      {        VirtualQuery((LPVOID)iAddr, &mbi_Memory, sizeof(MEMORY_BASIC_INFORMATION));        VirtualProtect(mbi_Memory.BaseAddress, mbi_Memory.RegionSize, PAGE_EXECUTE_READWRITE, &lpflOldProtect);        *LPDWORD(iAddr) = (DWORD)fn_OldWideCharToMultiByte;      }    }    catch(...)    {    }    return true;  }  return false;}
