//---------------------------------------------------------------------------
#include <stdlib.h>
#include <windows.h>
#include <mbstring.h>
#pragma hdrstop

#include "KOEItlbm.h"
//---------------------------------------------------------------------------
#pragma warn -8070
#pragma option push
#pragma option -vG- -vG0- -vG1- -vG2- -vG3- -vGc- -vGd- -vGt-
//---------------------------------------------------------------------------
__declspec( naked ) INT __cdecl tlbm_UTF8ToUnicode(LPWSTR pwOutStr, INT nMaxOutStr, char * pInStr,INT nInLen)
{
    static WORD UnicodeDecodeTable[] = {0x301C, 0xFF5E,
										0x2212, 0xFF0D};
    __asm
    {
                push    ecx
				mov     eax, [esp+14h]
                push    ebx
                push    ebp
                push    esi
                push    edi
                mov     edi, [esp+20h]
                xor     ebp, ebp
                test    edi, edi
                mov     [esp+10h], eax
                mov     eax, [esp+18h]
                jz      loc_818B11

loc_818A50:
                mov     dl, [edi]
                test    dl, dl
                jz      loc_818B11
                cmp     dl, 7Fh
                mov     ebx, 1
                jbe     short loc_818ABD
				mov     cl, dl
				and     cl, 0E0h
				cmp     cl, 0E0h
                jnz     short loc_818A97
				mov     cl, [edi+1]
                xor     cl, 80h
                movzx   dx, dl
                movzx   cx, cl
				mov     ebx, 3
                shl     edx, 6
                or      ecx, edx
                mov     dl, [edi+2]
                xor     dl, 80h
                movzx   dx, dl
                shl     ecx, 6
                or      ecx, edx
                jmp     short loc_818AC1

loc_818A97:
                mov     cl, dl
                and     cl, 0C0h
                cmp     cl, 0C0h
                jnz     short loc_818ABD
                xor     dl, cl
                movzx   cx, dl
                mov     dl, [edi+1]
                xor     dl, 80h
				movzx   dx, dl
				mov     ebx, 2
				shl     ecx, 6
                or      ecx, edx
				jmp     short loc_818AC1

loc_818ABD:
                movzx   cx, dl

loc_818AC1:
                mov     esi, offset UnicodeDecodeTable
                xor     edx, edx

loc_818AC8:
                cmp     [esi], cx
                jz      short loc_818AD8
                inc     edx
                add     esi, 4
                cmp     edx, 2
                jl      short loc_818AC8
                jmp     short loc_818ADC

loc_818AD8:
                mov     cx, [esi+2]

loc_818ADC:
                mov     edx, [esp+24h]
                test    edx, edx
				jl      short loc_818AEC
				mov     edx, [esp+10h]
                test    edx, edx
				jle     short loc_818B11

loc_818AEC:
                test    eax, eax
				jz      short loc_818AFC
                cmp     [esp+1Ch], ebp
                jle     short loc_818B1C
                mov     [eax], cx
                add     eax, 2

loc_818AFC:
                mov     esi, [esp+10h]
                sub     esi, ebx
                add     edi, ebx
                inc     ebp
                test    edi, edi
                mov     [esp+10h], esi
                jnz     loc_818A50

loc_818B11:
                cmp     ebp, [esp+1Ch]
                jge     short loc_818B1C
                mov     word ptr [eax], 0

loc_818B1C:
				pop     edi
				pop     esi
				mov     eax, ebp
				pop     ebp
				pop     ebx
				pop     ecx
				retn
	}
}
//---------------------------------------------------------------------------
#pragma option pop
#pragma warn +8070
//---------------------------------------------------------------------------
String __cdecl tlbm_UTF8ToAnsi(char * pInStr, INT nInLen)
{
	return Utf8ToAnsi(pInStr);
}
//---------------------------------------------------------------------------
String __cdecl tlbm_StrUTF8ToAnsi(const AnsiString  &aStr)
{
	return Utf8ToAnsi(aStr);
}
//---------------------------------------------------------------------------


String AnsiUTF8BIGDataToUnicodeGB(char *lpdata, int len)
{
	if(len == 0)
	{
		return "";
	}
	String resultt = tlbm_UTF8ToAnsi(lpdata, len);
	String results;
	results.SetLength(resultt.Length() * 2);
	int covLen = LCMapString(0x0804,LCMAP_SIMPLIFIED_CHINESE, resultt.c_str(), resultt.Length(), results.c_str(), results.Length());
	return String(results.c_str(), covLen);
}
