/*************************************************************
 * Module name: InjLib.H
 * Notices: Copyright (c) 2002-2008 yypcn
  ************************************************************/

//---------------------------------------------------------------------------
#ifndef InjLibH
  #define InjLibH

  #include "Win32Thunk.h"

//---------------------------------------------------------------------------
  #ifdef __BORLANDC__
    #pragma option -a1
  #endif //__BORLANDC__
  #ifdef _MSC_VER
    #pragma pack(1)
  #endif //__MSC_VER

//---------------------------------------------------------------------------
  #define CalcJumpAddress(iBaseAddr, iNewAddr)  ((DWORD) iBaseAddr + (DWORD) iNewAddr + 5)

//---------------------------------------------------------------------------
typedef struct  tagHOOKDATA
{
  unsigned char     cJumpToCall[2];
  unsigned char     cName[24];
  unsigned char     bInitOk;
  unsigned char     cCodeLength;
  unsigned char far *OldFuncAddress;
  unsigned char far *NewFuncAddress;
  unsigned char     cNewCode[12];
  unsigned char     cOldCode[12];
  unsigned char     cCallApiCode[57];
}
HOOKDATA, *LPHOOKDATA;

//---------------------------------------------------------------------------
  #ifdef __BORLANDC__
    #pragma option -a.
  #endif //__BORLANDC__
  #ifdef _MSC_VER
    #pragma pack()
  #endif //_MSC_VER

//---------------------------------------------------------------------------
LPHOOKDATA  HookApi(LPBYTE cWinAPIFunc, LPBYTE cNewAPIFunc);
BOOL        UnHookApi(LPHOOKDATA lpHookStruct);

//---------------------------------------------------------------------------
class       CAPIHookXP
{

private:
  HINSTANCE   m_hDLL;
  LPHOOKDATA  m_pfnOrig;

public:
  CAPIHookXP();
  CAPIHookXP(PSTR pszCalleeModName, PSTR pszFuncName, PROC pfnHook);
  ~CAPIHookXP();

  bool      InitAPIHook(PSTR pszCalleeModName, PSTR pszFuncName, PROC pfnHook);
  operator  PROC()  { return ((PROC) m_pfnOrig); }
};

//---------------------------------------------------------------------------
// TAPIHook class
//---------------------------------------------------------------------------
template<class T>
class TAPIHook
{

private:
  typedef CAuxStdThunk<T> thisThunk;
  thisThunk               m_pAPIThunk;
  HINSTANCE               m_hDLL;
  LPHOOKDATA              m_pfnOrig;

public:
  typedef void (__stdcall T:: *TMFP) ();

  //---------------------------------------------------------------------------
  TAPIHook()  { m_hDLL = NULL; m_pfnOrig = NULL; }

  //---------------------------------------------------------------------------
  TAPIHook(PSTR pszCalleeModName, PSTR pszFuncName, TMFP method, const T *pThis)
  {
    m_hDLL = NULL;
    m_pfnOrig = NULL;
    InitAPIHook(pszCalleeModName, pszFuncName, method, pThis);
  }

  //---------------------------------------------------------------------------
  ~TAPIHook()
  {
    if (m_pfnOrig)
      UnHookApi(m_pfnOrig);
    if (m_hDLL)
      FreeLibrary(m_hDLL);
  }

  //---------------------------------------------------------------------------
  bool InitAPIHook(PSTR pszCalleeModName, PSTR pszFuncName, TMFP method, const T *pThis)
  {
    LPBYTE  lpfAPIFunc;

    m_hDLL = LoadLibrary(pszCalleeModName);
    lpfAPIFunc = (LPBYTE) GetProcAddress(m_hDLL, pszFuncName);
    if (lpfAPIFunc)
    {
      m_pAPIThunk.InitThunk(method, pThis);
      m_pfnOrig = HookApi(lpfAPIFunc, (LPBYTE) m_pAPIThunk.GetThunk());
      return true;
    }

    return false;
  }

  //---------------------------------------------------------------------------
  operator  PROC()  { return ((PROC) m_pfnOrig); }
};

//---------------------------------------------------------------------------
// TFuncHook class
//---------------------------------------------------------------------------
template<class T>
class TFuncHook
{

private:
  typedef CAuxStdThunk<T> thisThunk;
  thisThunk               m_pAPIThunk;
  LPHOOKDATA              m_pfnOrig;

public:
  typedef void (__stdcall T:: *TMFP) ();

  //---------------------------------------------------------------------------
  TFuncHook() { m_pfnOrig = NULL; }

  //---------------------------------------------------------------------------
  TFuncHook(PROC fnFuncProc, TMFP method, const T *pThis)
  {
    m_pfnOrig = NULL;
    InitFuncHook(fnFuncProc, method, pThis);
  }

  //---------------------------------------------------------------------------
  ~TFuncHook()
  {
    if (m_pfnOrig)
      UnHookApi(m_pfnOrig);
  }

  //---------------------------------------------------------------------------
  bool InitFuncHook(PROC fnFuncProc, TMFP method, const T *pThis)
  {
    m_pAPIThunk.InitThunk(method, pThis);
    m_pfnOrig = HookApi((LPBYTE) fnFuncProc, (LPBYTE) m_pAPIThunk.GetThunk());
    return true;
  }

  //---------------------------------------------------------------------------
  operator  PROC()  { return ((PROC) m_pfnOrig); }
};
#endif

//////////////////////// End Of File /////////////////////////