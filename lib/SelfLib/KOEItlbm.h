//---------------------------------------------------------------------------
#ifndef KOEItlbmH
#define KOEItlbmH

#include <vcl.h>
//---------------------------------------------------------------------------
#ifdef  __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------
INT    __cdecl tlbm_UTF8ToUnicode(LPWSTR pwOutStr, INT nMaxOutStr, char * pInStr,INT nInLen);

String __cdecl tlbm_UTF8ToAnsi(char * pInStr, INT nInLen);
String __cdecl tlbm_StrUTF8ToAnsi(const AnsiString  &aStr);
//---------------------------------------------------------------------------


String AnsiUTF8BIGDataToUnicodeGB(char *lpdata, int len);

#ifdef  __cplusplus
}
#endif
//---------------------------------------------------------------------------
#endif
