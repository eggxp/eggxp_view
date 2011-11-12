/***************************************************************************
 *  File name SearchTool.cpp                                               *
 *  Version:  1.01.03a                                                     *
 *  Author:   yypcn                                                        *
 *  Target:   Normal binary search and wildcard binary search engine.      *
 *                                                                         *
 *  History                                                                *
 *  12-10-2003    20:20pm  First version.                                  *
 *  11-17-2005    17:48pm  Fix: BinarySearch return absolute address, but  *
 *                              need relative address!                     *
 *                                                                         *
 ***************************************************************************/
#include <ctype.h>
#include <string.h>
#include <windows.h>
#pragma hdrstop

#include "SearchTool.h"
//---------------------------------------------------------------------------
WORD WINAPI CSearchEngine::HexToInt(WORD wCh)
{
  WORD wRet;
  wRet = wCh - 0x3030;
  if(wRet & 0xF000)
    wRet -= 0x0700;
  if(wRet & 0x00F0)
    wRet -= 0x0007;
  if(wRet & 0xF0F0)
    return 0xFFFF;
  else
    return (wRet >> 4) | (wRet & 0x000F);
}
//---------------------------------------------------------------------------
DWORD WINAPI CSearchEngine::WildcardSearch(LPVOID pBuffer, DWORD nLength, LPWORD pwWildcardPattern, DWORD nPatternLength, DWORD &nResultLength)
{
  LPVOID pOrgBuffer = pBuffer;
  DWORD nResult = -1, nComplexBytes;

Wildcard_AgainSearch:
  __asm mov     edi, [pBuffer];
  __asm mov     ecx, [nLength];
  __asm mov     esi, [pwWildcardPattern];
  __asm mov     edx, [nPatternLength];
  __asm test    edx, edx;
  __asm jz      Wildcard_Exit;
  __asm test    ecx, ecx;
  __asm jz      Wildcard_ErrorExit;
  __asm lodsw;
  __asm dec     edx;
  __asm test    ah, ah;                       // wildcard ???
  __asm jnz     Wildcard_NextSearch1;
  __asm repne   scasb;                        // first byte search ...
  __asm jne     Wildcard_ErrorExit;
  __asm mov     [pBuffer], edi;               // refresh buffer and length
  __asm dec     [pBuffer];
  __asm mov     [nLength], ecx;
  __asm inc     [nLength];

Wildcard_NextSearch:
  __asm test    edx, edx;
  __asm jz      Wildcard_Exit;
  __asm test    ecx, ecx;
  __asm jz      Wildcard_ErrorExit;
  __asm lodsw;
  __asm dec     edx;

Wildcard_NextSearch1:
  __asm cmp     ax, SINGLE_WILDCARD;          // '??' sign
  __asm jz      Wildcard_Single;
  __asm cmp     ax, COMPLEX_WILDCARD;         // '%%' sign
  __asm jz      Wildcard_Complex;
  __asm cmp     ax, 0xFFFF;                   // EOF sign
  __asm jz      Wildcard_Exit;
  __asm dec     ecx;
  __asm inc     edi;
  __asm cmp     al, byte ptr [edi - 1];
  __asm jz      Wildcard_NextSearch;

Wildcard_NextSearch2:
  __asm inc     [pBuffer];
  __asm dec     [nLength];
  __asm jmp     Wildcard_AgainSearch;

Wildcard_Single:
  __asm inc     edi;                          // '??' sign, skip one byte.
  __asm dec     ecx;
  __asm jmp     Wildcard_NextSearch;

Wildcard_Complex:                             // '%%' sign, wildcard search.
  __asm mov     [nComplexBytes], 32;

Wildcard_Complex2:
  __asm cmp     word ptr [esi], COMPLEX_WILDCARD
  __asm jnz     Wildcard_Compare;
  __asm add     [nComplexBytes], 32;
  __asm inc     esi;
  __asm inc     esi;
  __asm test    edx, edx;
  __asm jz      Wildcard_Exit;
  __asm dec     edx;
  __asm jmp     Wildcard_Complex2;

Wildcard_Compare:
  __asm mov     ebx, [nComplexBytes];         // safe check.
  __asm cmp     ebx, ecx;
  __asm jb      Wildcard_Compare2;
  __asm mov     ebx, ecx;

Wildcard_Compare2:
  __asm mov     [nComplexBytes], ebx;
  __asm test    edx, edx;
  __asm jz      Wildcard_Exit;
  __asm lodsw;
  __asm dec     edx;
  __asm test    ah, ah;
  __asm jnz     Wildcard_ErrorExit;
  __asm xchg    ecx, ebx
  __asm repne   scasb;                        // complex wildcard serach
  __asm xchg    ecx, ebx
  __asm je      Wildcard_Compare3;
  __asm inc     [pBuffer];
  __asm dec     [nLength];
  __asm jmp     Wildcard_AgainSearch;

Wildcard_Compare3:
  __asm sub     ecx, [nComplexBytes];
  __asm add     ecx, ebx;
  __asm jmp     Wildcard_NextSearch;

Wildcard_Exit:
  __asm mov     eax, [pBuffer];
  __asm sub     edi, eax
  __asm sub     eax, [pOrgBuffer];
  __asm mov     [nResult], eax;
  __asm mov     eax, [nResultLength];
  __asm mov     [eax], edi;

Wildcard_ErrorExit:
  return nResult;
}
//---------------------------------------------------------------------------
DWORD WINAPI CSearchEngine::BinarySearch(LPVOID pBuffer, DWORD nLength, LPVOID pPattern, DWORD nPatternLength)
{
  DWORD nResult = -1;
  LPVOID pOrgBuffer = pBuffer;

  __asm mov     esi, [pPattern];
  __asm mov     edi, [pBuffer];
  __asm mov     ecx, [nLength];
  __asm dec     ecx;
  __asm js      Binary_NotFound;
  __asm mov     edx, [nPatternLength];
  __asm dec     edx;
  __asm js      Binary_NotFound;
  __asm mov     al, byte ptr [esi];
  __asm inc     esi;
  __asm sub     ecx, edx;
  __asm jle     Binary_NotFound;

Binary_FindNext:
  __asm repne   scasb;
  __asm jne     Binary_NotFound;
  __asm mov     ebx, ecx;
  __asm push    esi;
  __asm push    edi;
  __asm mov     ecx, edx;
  __asm repe    cmpsb;
  __asm pop     edi;
  __asm pop     esi;
  __asm je      Binary_Found;
  __asm mov     ecx, ebx;
  __asm jmp     Binary_FindNext;

Binary_Found:
  __asm mov     eax, edi;
  __asm dec     eax;
  __asm sub     eax, [pOrgBuffer];
  __asm mov     [nResult], eax;

Binary_NotFound:
  return nResult;
}
//---------------------------------------------------------------------------
BOOL WINAPI CSearchEngine::WildcardPatternPreprocess(LPSTR  pWildcardPattern)
{
  CHAR cCh0, cCh1;
  BOOL bResult = TRUE;
  m_nPatternLength = 0;
  while((cCh0 = pWildcardPattern[0]) != '\0')
  {
    if(cCh0 == ' ')
    {
      pWildcardPattern++;
      continue;
    }
    if((cCh1 = pWildcardPattern[1]) == '\0')
      break;
    WORD wCh = (toupper(cCh0) << 8) | toupper(cCh1);
    if(wCh == 0x3F3F)                         // '??' Sign
      m_wWildcardPattern[m_nPatternLength] = SINGLE_WILDCARD;
    else if(wCh == 0x2525)                    // '%%' Sign
      m_wWildcardPattern[m_nPatternLength] = COMPLEX_WILDCARD;
    else if((m_wWildcardPattern[m_nPatternLength] = HexToInt(wCh)) == 0xFFFF)
    {
      bResult = FALSE;
      break;
    }
    m_nPatternLength++;
    pWildcardPattern += 2;
    if(m_nPatternLength >= (sizeof(m_wWildcardPattern) / 2) - 1)
      break;
  };
  m_wWildcardPattern[m_nPatternLength] = 0xFFFF;
  return bResult;
}
//---------------------------------------------------------------------------
BOOL WINAPI CSearchEngine::NormalPatternPreprocess(LPSTR pPattern)
{
  CHAR cCh0, cCh1;
  BOOL bResult = TRUE;
  m_nPatternLength = 0;
  while((cCh0 = pPattern[0]) != '\0')
  {
    if(cCh0 == ' ')
    {
      pPattern++;
      continue;
    }
    if((cCh1 = pPattern[1]) == '\0')
      break;
    WORD wCh = (toupper(cCh0) << 8) | toupper(cCh1);
    if((wCh = HexToInt(wCh)) == 0xFFFF)
    {
      bResult = FALSE;
      break;
    }
    m_cNormalPattern[m_nPatternLength] = wCh;
    m_nPatternLength++;
    pPattern += 2;
    if(m_nPatternLength >= sizeof(m_cNormalPattern) - 1)
      break;
  };
  return bResult;
}
//---------------------------------------------------------------------------
CSearchEngine::CSearchEngine(VOID)
{

}
//---------------------------------------------------------------------------
CSearchEngine::~CSearchEngine(VOID)
{

}
//---------------------------------------------------------------------------
LPVOID WINAPI CSearchEngine::WildcardSearch(LPVOID pBuffer, DWORD nLength, LPSTR pWildcardPattern, LPDWORD pResultLength)
{
  LPVOID pRet = NULL;
  try
  {
    if(WildcardPatternPreprocess(pWildcardPattern))
    {
      DWORD nResultLength;
      DWORD nPos = WildcardSearch(pBuffer, nLength, m_wWildcardPattern, m_nPatternLength, nResultLength);
      if(nPos != 0xffffffff)
      {
        if(pResultLength)
          pResultLength[0] = nResultLength;
        pRet = LPBYTE(pBuffer) + nPos;
      }
    }
  }
  catch(...)
  {
  }
  return pRet;
}
//---------------------------------------------------------------------------
LPVOID WINAPI CSearchEngine::NormalSearch(LPVOID pBuffer, DWORD nLength, LPVOID pPattern, DWORD nPatternLength)
{
  LPVOID pRet = NULL;
  try
  {
    DWORD nPos = BinarySearch(pBuffer, nLength, pPattern, nPatternLength);
    if(nPos != 0xffffffff)
      pRet = LPBYTE(pBuffer) + nPos;
  }
  catch(...)
  {
  }
  return pRet;
}
//---------------------------------------------------------------------------
LPVOID WINAPI CSearchEngine::NormalSearch(LPVOID pBuffer, DWORD nLength, LPSTR pPattern)
{
  LPVOID pRet = NULL;
  if(NormalPatternPreprocess(pPattern))
    pRet = NormalSearch(pBuffer, nLength, m_cNormalPattern, m_nPatternLength);
  return pRet;
}
//---------------------------------------------------------------------------

