//---------------------------------------------------------------------------
#include <vcl.h>
#include <Psapi.h>
#include <winsock2.h>
#include <math.hpp>
#include <math.h>
#include <vector>
#pragma hdrstop
#include "CommFunc.h"
using namespace std;

//---------------------------------------------------------------------------
#pragma package(smart_init)
int WalkStep,WalkCount;
TList *WalkData;

static unsigned char Decode6BitMask[5] = { 0xfc, 0xf8, 0xf0, 0xe0, 0xc0 };


/* ========================================================================= */
//define for Crc32
#define DO1(buf)  crc = crc_table[((int)crc ^ (*buf++)) & 0xff] ^ (crc >> 8);
#define DO2(buf)  DO1(buf); DO1(buf);
#define DO4(buf)  DO2(buf); DO2(buf);
#define DO8(buf)  DO4(buf); DO4(buf);
/* ========================================================================= */
//参数: DWORD crc 上一次crc计算结果,初始为0
//      LPBYTE buf  输入缓冲
//      UINT len    输入缓冲长度
//---------------------------------------------------------------------------
DWORD _stdcall GetCrc32(DWORD crc, LPBYTE buf, UINT len)
{
  static DWORD crc_table[256] = {
    0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L,
    0x706af48fL, 0xe963a535L, 0x9e6495a3L, 0x0edb8832L, 0x79dcb8a4L,
    0xe0d5e91eL, 0x97d2d988L, 0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L,
    0x90bf1d91L, 0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL,
    0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L, 0x136c9856L,
    0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL, 0x14015c4fL, 0x63066cd9L,
    0xfa0f3d63L, 0x8d080df5L, 0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L,
    0xa2677172L, 0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
    0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L, 0x32d86ce3L,
    0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L, 0x26d930acL, 0x51de003aL,
    0xc8d75180L, 0xbfd06116L, 0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L,
    0xb8bda50fL, 0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L,
    0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL, 0x76dc4190L,
    0x01db7106L, 0x98d220bcL, 0xefd5102aL, 0x71b18589L, 0x06b6b51fL,
    0x9fbfe4a5L, 0xe8b8d433L, 0x7807c9a2L, 0x0f00f934L, 0x9609a88eL,
    0xe10e9818L, 0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
    0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL, 0x6c0695edL,
    0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L, 0x65b0d9c6L, 0x12b7e950L,
    0x8bbeb8eaL, 0xfcb9887cL, 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L,
    0xfbd44c65L, 0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L,
    0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL, 0x4369e96aL,
    0x346ed9fcL, 0xad678846L, 0xda60b8d0L, 0x44042d73L, 0x33031de5L,
    0xaa0a4c5fL, 0xdd0d7cc9L, 0x5005713cL, 0x270241aaL, 0xbe0b1010L,
    0xc90c2086L, 0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
    0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L, 0x59b33d17L,
    0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL, 0xedb88320L, 0x9abfb3b6L,
    0x03b6e20cL, 0x74b1d29aL, 0xead54739L, 0x9dd277afL, 0x04db2615L,
    0x73dc1683L, 0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L,
    0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L, 0xf00f9344L,
    0x8708a3d2L, 0x1e01f268L, 0x6906c2feL, 0xf762575dL, 0x806567cbL,
    0x196c3671L, 0x6e6b06e7L, 0xfed41b76L, 0x89d32be0L, 0x10da7a5aL,
    0x67dd4accL, 0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
    0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L, 0xd1bb67f1L,
    0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL, 0xd80d2bdaL, 0xaf0a1b4cL,
    0x36034af6L, 0x41047a60L, 0xdf60efc3L, 0xa867df55L, 0x316e8eefL,
    0x4669be79L, 0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L,
    0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL, 0xc5ba3bbeL,
    0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L, 0xc2d7ffa7L, 0xb5d0cf31L,
    0x2cd99e8bL, 0x5bdeae1dL, 0x9b64c2b0L, 0xec63f226L, 0x756aa39cL,
    0x026d930aL, 0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
    0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L, 0x92d28e9bL,
    0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L, 0x86d3d2d4L, 0xf1d4e242L,
    0x68ddb3f8L, 0x1fda836eL, 0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L,
    0x18b74777L, 0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL,
    0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L, 0xa00ae278L,
    0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L, 0xa7672661L, 0xd06016f7L,
    0x4969474dL, 0x3e6e77dbL, 0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L,
    0x37d83bf0L, 0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
    0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L, 0xbad03605L,
    0xcdd70693L, 0x54de5729L, 0x23d967bfL, 0xb3667a2eL, 0xc4614ab8L,
    0x5d681b02L, 0x2a6f2b94L, 0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL,
    0x2d02ef8dL};
  if (buf == NULL)
    return 0L;
  crc = crc ^ 0xffffffffL;
  while (len >= 8)
  {
    DO8(buf);
    len -= 8;
  }
  if (len)
  {
    do
    {
      DO1(buf);
    }while(--len);
  }
  return crc ^ 0xffffffffL;
}
//---------------------------------------------------------------------------
DWORD GetFileCRC(String FileName)
{
    if (!FileExists(FileName))
     return 0;
    TMemoryStream * FileStream= new    TMemoryStream;
    FileStream->LoadFromFile(FileName);
    DWORD CRC = GetCrc32(0,(char *)FileStream->Memory,FileStream->Size);
    delete FileStream;
    return CRC;
}
//---------------------------------------------------------------------------
int GetLogicalDrive(TStrings *Drivers)
{
	TCHAR buf[8192];
    int Len =  GetLogicalDriveStrings(sizeof(buf) / sizeof(TCHAR)-1, buf);
    Drivers->Clear();
    int Pos=0;
    String CurDriver;
    while (Pos<Len)
    {
       CurDriver = String(buf+Pos);
       Pos+= CurDriver.Length()+1;
       Drivers->Add(CurDriver);
    }
    return Drivers->Count;
}
//---------------------------------------------------------------------------
int GetCharPos(String Data,char SplitChar)
{
  TCHAR ch;
  TCHAR *pch;
  bool IsFind=false;
  int i=0;
  String InStr;
  if (!Data.Length())
    return 0;
  InStr = Data;
  pch = InStr.c_str();
  do
  {
    ch  =*pch;
    if (ch == SplitChar)
    {
      i++;
      IsFind = true;
      break;
    }
    i++;
    if(IsDBCSLeadByte(ch))
    {
      i++;
      ch = pch[1];
      ch  =*pch;
    }
    pch =CharNext(pch);
  }
  while (ch != '\n' && ch != '\0');
  if (!IsFind)
    return 0;
  else
    return i;
}

void SplitStr(AnsiString SrcStr,AnsiString SplitChar,TStrings *Str)
{
  int i,j;
  String tmpStr;
  Str->Clear();
  j=SplitChar.Length();
  i=GetCharPos(SrcStr,*SplitChar.c_str());
  while (i > 0)
  {
    tmpStr = SrcStr.SubString(1,i-1);
    //if (tmpStr != "")
    Str->Add(tmpStr);
    SrcStr.Delete(1,i+j-1);
    i=GetCharPos(SrcStr,*SplitChar.c_str());
  }
  Str->Add(SrcStr);
}
//-------------------------------------------------------------------------
 //取出字符串中所有字母   isalpha(c)
String GetAlpha(String InStr)
{
   if (InStr.Length()<=0)
     return "";
   TCHAR * Buf = new TCHAR[InStr.Length()];
   String ResultStr="";
   try
   {
       int  ResultLen = 0;
       memset(Buf,0,InStr.Length() * sizeof(TCHAR));
       for (int i=0;i<InStr.Length();i++)
       {
          if (isalpha(InStr.c_str()[i])) //是字母
          {
            Buf[ResultLen] =  InStr.c_str()[i];
            ResultLen++;
          }
       }
       if (ResultLen>0)
       {
          ResultStr=  String(Buf,ResultLen);
       }
   }
   __finally
   {
     delete []Buf;
   }
   return ResultStr;
}
//-------------------------------------------------------------------------
//取出字符串中所有数字  isdigit(c)
String GetDigit(String InStr)
{
   if (InStr.Length()<=0)
     return "";
   TCHAR *Buf = new TCHAR[InStr.Length()];
   String ResultStr="";
   try
   {
       int  ResultLen = 0;
       memset(Buf,0,InStr.Length() * sizeof(TCHAR));
       for (int i=0;i<InStr.Length();i++)
       {
          if (isdigit(InStr.c_str()[i])) //是字母
          {
            Buf[ResultLen] =  InStr.c_str()[i];
            ResultLen++;
          }
       }
       if (ResultLen>0)
       {
          ResultStr=  String(Buf,ResultLen);
       }
   }
   __finally
   {
     delete []Buf;
   }
   return ResultStr;

}
//-------------------------------------------------------------------------
bool CheckOS_Font()
{
  String S1,S2;
  S1="中国";
  S2="台湾";
  if (CompareString(0x00000804,NORM_IGNORECASE,S1.c_str(),S1.Length(),S2.c_str(),S2.Length()) == 0)
  {
    return false;
  }
  else
    return true;
}
//-------------------------------------------------------------------------
String GetTrueNumber(String InStr)
{
     String NumberStr = GetDigit(InStr);
     return IntToStr(NumberStr.ToIntDef(0));
}
//-------------------------------------------------------------------------
String ReadToken(String &SrcString,String TokenChar)
{
    int TokenIndex = SrcString.Pos(TokenChar);
    if (TokenIndex==0)
    {
      return "";
    }
    String ResultStr =  SrcString.SubString(1,TokenIndex-1);
    SrcString =  SrcString.SubString(TokenIndex+1,SrcString.Length());
    return ResultStr;
}
//------------------------------------------------------------------------------
String LeftString(const String &SrcString,String TokenStr)
{
  //取出一个字符串在某个字符左边的字符串
  //举例:  String BB = "123,456";
  //       String AA =  LeftString(BB,",");
  //结果   AA = "123"
  int TokenIndex = SrcString.Pos(TokenStr);
  if (TokenIndex==0)
  {
    return "";
  }
  return  SrcString.SubString(1,TokenIndex-1);
}
//------------------------------------------------------------------------------
String RightString(const String &SrcString,String TokenStr)
{
 //取出一个字符串在某个字符右边的字符串
  //举例:  String BB = "123,456";
  //       String AA =  LeftString(BB,",");
  //结果   AA = "456"
  int TokenIndex = SrcString.Pos(TokenStr);
  if (TokenIndex==0)
  {
    return "";
  }
  return  SrcString.SubString(TokenIndex+1,SrcString.Length());
}
//-------------------------------------------------------------------------
//函数说明:
//从字符串 "1111,222" 提取出一对数值,成功则 Index=1111,Value=222
//返回值表示操作是否成功,如果为false,则Index和Value里面的值没有意义
//-------------------------------------------------------------------------
bool GetPairWWByStr(String SrcStr,int &LeftValue,int &RightValue)
{
    TStringList *tmpStr = new TStringList;
    SplitStr(SrcStr,",",tmpStr);
    if (tmpStr->Count!=2)
    {
      delete tmpStr;
      return false;
    }
    LeftValue = StrToIntDef(tmpStr->Strings[0],0);
    RightValue = StrToIntDef(tmpStr->Strings[1],0);
    delete tmpStr;
    return true;
}
//-------------------------------------------------------------------------
//函数说明:
//从字符串 "1111,abcde" 提取出一个数值和一个字符串值,成功则 Index=1111,Value="abcde"
//返回值表示操作是否成功,如果为false,则Index和Value里面的值没有意义
//-------------------------------------------------------------------------
bool GetPairWSByStr(String SrcStr,int &LeftValue,String &RightValue)
{
    TStringList *tmpStr = new TStringList;
    SplitStr(SrcStr,",",tmpStr);
    if (tmpStr->Count!=2)
    {
      delete tmpStr;
      return false;
    }
    LeftValue = StrToIntDef(tmpStr->Strings[0],0);
    RightValue = tmpStr->Strings[1];
    delete tmpStr;
    return true;
}

bool Get3ValueByStr(String SrcStr,int &Index,int &Value1,int &Value2)
{
    TStringList *tmpStr = new TStringList;
    SplitStr(SrcStr,",",tmpStr);
    if (tmpStr->Count!=3)
    {
      delete tmpStr;
      return false;
    }
    Index = StrToIntDef(tmpStr->Strings[0],0);
    Value1 = StrToIntDef(tmpStr->Strings[1],0);
    Value2 = StrToIntDef(tmpStr->Strings[2],0);
    delete tmpStr;
    return true;
}


void SplitStrOld(AnsiString SrcStr,AnsiString SplitChar,TStrings *Str)
{
  int i,j;
  String tmpStr;
  Str->Clear();
  j=SplitChar.Length();
  i=SrcStr.Pos(SplitChar);
  while (i > 0)
  {
    tmpStr = SrcStr.SubString(1,i-1);
    Str->Add(tmpStr);
    SrcStr.Delete(1,i+j-1);
    i=SrcStr.Pos(SplitChar);
  }
  Str->Add(SrcStr);
}
//---------------------------------------------------------------------------
bool ReadMemory(String aClassName, DWORD BaseAddr, DWORD Len, LPBYTE lpBuf)
{
  HWND DesWnd;
  HANDLE ProcessHandle;
  DWORD ProcessID,dwSize,ThreadProcessId;
  DWORD NumberOfBytesWrite;
  DesWnd  = FindWindow(NULL,(LPCTSTR)aClassName.c_str());
  if (DesWnd == NULL)
  {
    return false;
  }
  ThreadProcessId =  GetWindowThreadProcessId(DesWnd,&ProcessID);
  if (!ThreadProcessId)
    return false;
  ProcessHandle =  OpenProcess(PROCESS_ALL_ACCESS, false,ProcessID);
  if (ReadProcessMemory(
        ProcessHandle,
        (LPCVOID)BaseAddr,
        lpBuf,
        Len,
        &NumberOfBytesWrite)!=0)
  {
    CloseHandle(ProcessHandle);
    return true;
  }
  else
  {
    CloseHandle(ProcessHandle);
    return false;
  }
}
//-----------------------------------------------------------------------------
bool WriteMemory(String ClassName,DWORD BaseAddr, DWORD Len, LPBYTE Buf)
{
   HWND DesWnd;
   HANDLE ProcessHandle;
   DWORD ProcessID,dwSize,ThreadProcessId;
   DesWnd  = FindWindow((LPCTSTR)ClassName.c_str(),NULL);
   if (DesWnd == NULL)
   {
     return false;
   }
   //ThreadProcessId =  GetWindowThreadProcessId(DesWnd,&ProcessID);
   ProcessHandle =  OpenProcess(PROCESS_ALL_ACCESS, false,ProcessID);
   if (WriteProcessMemory(ProcessHandle,(LPVOID)BaseAddr,Buf,Len,NULL)!=0)
   {
     CloseHandle(ProcessHandle);
     return true;
   }
   else
   {
      CloseHandle(ProcessHandle);
     return false;
   }

}
//---------------------------------------------------------------------------
bool D_ReadMemory(DWORD ProcessID,DWORD BaseAddr,DWORD Len,LPBYTE lpBuf)
{
  HANDLE ProcessHandle;
  DWORD dwSize;
  DWORD NumberOfBytesWrite;
  ProcessHandle =  OpenProcess(PROCESS_ALL_ACCESS, false,ProcessID);
  if (ReadProcessMemory(
        ProcessHandle,
        (LPCVOID)BaseAddr,
        lpBuf,
        Len,
        &NumberOfBytesWrite)!=0)
  {
    CloseHandle(ProcessHandle);
    return true;
  }
  else
  {
    CloseHandle(ProcessHandle);
    return false;
  }
}
//-----------------------------------------------------------------------------
bool D_WriteMemory(DWORD ProcessID,DWORD BaseAddr, DWORD Len,LPBYTE Buf)
{
   HANDLE ProcessHandle;
   DWORD dwSize;
   DWORD NumberOfBytesWrite;
   ProcessHandle =  OpenProcess(PROCESS_ALL_ACCESS, false,ProcessID);
   if (WriteProcessMemory(ProcessHandle,(LPVOID)BaseAddr,Buf,Len,NULL)!=0)
   {
     CloseHandle(ProcessHandle);
     return true;
   }
   else
   {
      CloseHandle(ProcessHandle);
     return false;
   }

}

//---------------------------------------------------------------------------
String FormatStrA(char *Info, ...)
{
  AnsiString  StrInfo;
  va_list vaArgs;
  va_start(vaArgs, Info);
  if (Info)
  {
    StrInfo.vprintf(Info, vaArgs);
    va_end(vaArgs);
    return StrInfo;
  }

  va_end(vaArgs);
  return "";
}

String FormatStrW(wchar_t *Info, ...)
{
  UnicodeString  StrInfo;
  va_list vaArgs;
  va_start(vaArgs, Info);
  if (Info)
  {
    StrInfo.vprintf(Info, vaArgs);
    va_end(vaArgs);
    return StrInfo;
  }

  va_end(vaArgs);
  return "";
}

//---------------------------------------------------------------------------
String FormatString(String Info, ...)
{
	String  StrInfo;
	va_list vaArgs;
	va_start(vaArgs, Info);
	StrInfo.vprintf(Info.c_str(), vaArgs);
	va_end(vaArgs);
	return StrInfo;
}
//---------------------------------------------------------------------------
AnsiString      HexStrToBinStr(String SrcData)
{
    AnsiString output;
	output.SetLength(SrcData.Length());
	AnsiString ansiSrc = SrcData;
    int len = WY_HexToBin(ansiSrc.c_str(), output.c_str(), output.Length(), true);
    return  AnsiString(output.c_str(), len);
}

int __fastcall WY_HexToBin(char * SrcText, char * DesBuffer, int DesBufSize,bool HasSplitChar)
{
  //asm优化版
 //Bluely 完成于 2005.12.29
    static char Convert[55] =
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,-1,-1,-1,-1,-1,-1,
     -1,10,11,12,13,14,15,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
     -1,10,11,12,13,14,15};
  	SrcText = StrLower(SrcText);
  	int Result=0;
    __asm
    {
                    mov     esi, DesBuffer
                    mov     bl, HasSplitChar
                    mov     edi, DesBufSize
                    mov     eax, SrcText
                    test    edi, edi
                    jle     short END_WHILE

    BEGIN_WHILE:
                    movsx   edx, byte ptr [eax]
                    cmp     edx, '0'
                    jl      short END_WHILE
                    cmp     edx, 'f'
                    jg      short END_WHILE
                    movsx   edx, byte ptr [eax+1]
                    cmp     edx, '0'
                    jl      short END_WHILE
                    cmp     edx, 'f'
                    jle     short CONVERT_CHAR
                    jmp     short END_WHILE

    CONVERT_CHAR:
                    movsx   ecx, byte ptr [eax]
                    sub     ecx,'0'
                    mov     dl, Convert[ecx]
                    movsx   ecx, byte ptr [eax+1]
                    sub     ecx,'0'
                    shl     edx, 4
                    add     dl, Convert[ecx]
                    test    bl, bl
                    mov     [esi], dl
                    jz      short NOT_HAS_SPLIT_CHAR  //没有分隔符
                    add     eax, 3
                    jmp     short NEW_WHILE

    NOT_HAS_SPLIT_CHAR:
                    add     eax, 2

    NEW_WHILE:
                    inc     esi
                    dec     edi
                    test    edi, edi
                    jg      short BEGIN_WHILE

    END_WHILE:

                    mov     eax, DesBufSize
                    sub     eax, edi
                    mov		Result,eax
    }
return Result;
}
//---------------------------------------------------------------------------
void __fastcall WY_BinToHex(char * DesText,const char * SrcBuffer,int SrcBufSize,const char SplitChar)
{
 //asm优化版
 //Bluely 完成于 2005.12.29

  static char  Convert[16] = "0123456789ABCDEF";
__asm
{
                    mov     edi, SrcBufSize
                    mov     esi, DesText
                    mov     bl, SplitChar
                    xor     edx, edx
                    mov     eax, SrcBuffer
                    cmp     edi, edx
                    jle     short FUNC_END

    LOOP_BEGIN:
                    xor     ecx, ecx
                    mov     cl, [eax]
                    sar     ecx, 4
                    mov     cl, Convert[ecx]
                    mov     [esi], cl
                    xor     ecx, ecx
                    mov     cl, [eax]
                    and     ecx, 0Fh
                    test    bl, bl
                    mov     cl, Convert[ecx]
                    mov     [esi+1], cl
                    jnz     short HAS_SPLIT_CHAR
                    add     esi, 2
                    jmp     short ONE_LOOP

    HAS_SPLIT_CHAR:
                    mov     [esi+2], bl
                    add     esi, 3

    ONE_LOOP:
                    inc     edx
                    inc     eax
                    cmp     edi, edx
                    jg      short LOOP_BEGIN

    FUNC_END:
                    mov     byte ptr [esi], 0 //返回缓冲区以0为结尾
}

}
//-----------------------------------------------------------------------------
String  BinToStr(char* SrcBuffer, int SrcLen)
{
  AnsiString StrResult;
  StrResult.SetLength(SrcLen*3);
  WY_BinToHex(StrResult.c_str(),SrcBuffer,SrcLen,' ');
  return StrResult;
}
//-----------------------------------------------------------------------------

int HexStrToBin(LPBYTE OutputBuf,String SrcData)
{
  //效率低下,弃用,仅仅为兼容旧代码而保留
  int iLen;
  TStringList   *DataList;
  SrcData = SrcData.Trim();
  if (SrcData.Length()<1)
  {
    return 0;
  }
  DataList =new TStringList;
  try
  {
    SplitStr(SrcData," ",DataList);
    iLen = DataList->Count;
    for (int i=0;i<iLen;i++)
    {
      OutputBuf[i] = StrToIntDef("0x"+DataList->Strings[i],0);
    }
  }
  __finally
  {
    delete DataList;
  }
  return iLen;
}


//-----------------------------------------------------------------------------
//统计字符串中某子串的个数
int CountChar(String InStr,String SubStr)
{
   int CurPos=0,Count=0;
   while ((CurPos = InStr.Pos(SubStr)) !=0)
   {
      Count++;
      InStr  = InStr.SubString(CurPos+1,InStr.Length()-CurPos);
   }
   return Count;
}

//-------------↓↓↓↓将一个String类的二进制内容保存到文件↓↓↓↓---------------------------------
// 参数: 数据,文件名
// 返回: 无
//////////////////////////////////////////////////////////////////////////////////////////
void  DumpString(String Data,String FileName)
{
  TMemoryStream *mmData = new TMemoryStream();
  try
  {
    mmData->Write(Data.data(),Data.Length());
    mmData->SaveToFile(FileName);
  }
  __finally
  {
    delete mmData;
  }
}

//-------------↓↓↓↓10进制转换到62进制↓↓↓↓---------------------------------
// 参数: 10进制数
// 返回: 62进制字符串
//////////////////////////////////////////////////////////////////////////////////////////
static char AscTable[62]= {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
					'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
					'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
					'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
					'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
					'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
					'Y', 'Z'};
//---------------------------------------------------------------------------
int GetNumber(char s)
{
  int i;
  for (i = 0;i<62;i++)
  {
	if (AscTable[i]== s)
	{
	  return i;
	}
  }
  return 0;
}
String c_10To62(int Value)
{
  int i,n;
  String ResultValue,tmpStr;
  i = Value;
  if (i <= 61)
  {
    return  AscTable[i];
  }
  ResultValue = "";
  while (i >= 62)
  {
    n = i % 62;
    tmpStr =  AscTable[n];
    ResultValue = tmpStr+ResultValue;
    i = i / 62;
  }
  tmpStr =  AscTable[i];
  ResultValue = tmpStr+ResultValue;
  return ResultValue;
}
//-------------↓↓↓↓62进制转换到10进制↓↓↓↓---------------------------------
// 参数: 62进制字符串
// 返回: 10进制数
//////////////////////////////////////////////////////////////////////////////////////////
int c_62To10(String s)
{
  int i,ResultValue;
  double Num;
  ResultValue = 0;
  for (i = 1;i<=s.Length();i++)
  {
	Num = Power((double)62,(double)(s.Length() - i));
    Num = GetNumber(s[i]) * Num;
    ResultValue = ResultValue + RoundTo(Num,0);
  }
  return ResultValue;
}
//------------------------------------------------------------------------------


//---------------------------------------------------------------------------
int GetReverseAngle(int OrgAngle)
{
   //获取某个角度的相反角度
        int DesAngle=0;
        if (OrgAngle== 0 || OrgAngle== 360)
        {
           DesAngle = 180;
        }
        else if(OrgAngle>0 && OrgAngle<180)
        {
           DesAngle=OrgAngle+180;
        }
        else if(OrgAngle>180 && OrgAngle<360)
        {
           DesAngle=OrgAngle-180;
        }
        else if(OrgAngle == 180)
        {
           DesAngle = 0;
        }
        else
        {
           DesAngle = 0;
        }
        return DesAngle;
}
//getAngle获取两个坐标之间的角度0-360度
//------------------------------------------------------------------------------
int GetAngle( int x1 , int  y1 , int x2 , int y2 )
{
    if (x1==x2 && y1==y2)
     return 0;
    double  rad = atan2(x1-x2,y1-y2 );
    int  th = -rad*180/M_PI;
    if (th<0)
      th+=360;
    return th;
}

//RotatePos 以ZeroX,ZeroY为原点，根据Angle角度值(0-360度)旋转SrcX,SrcY坐标，输出到DesPos,
//------------------------------------------------------------------------------
void RotatePos(int ZeroX,int ZeroY,int SrcX, int SrcY, TPoint *DesPos, float Angle)
{
  float ang = Angle * M_PI / 180.0;
  DesPos->x =ZeroX+(SrcX-ZeroX)*cos(ang)-(SrcY-ZeroY)*sin(ang);
  DesPos->y =ZeroY+(SrcX-ZeroX)*sin(ang)+(SrcY-ZeroY)*cos(ang);
}

//RotatePos 根据Angle角度值(0-360度)旋转SrcX,SrcY坐标，长度Dis,输出到DesPos,
//------------------------------------------------------------------------------
void RotatePosByDis(int SrcX, int SrcY,int Dis,TPoint *DesPos, float Angle)
{
  float ang = Angle * M_PI / 180.0;
  int  ZeroX =   SrcX;
  int  ZeroY =   SrcY;
  int  Lx    =   SrcX;
  int  Ly    =   SrcY-Dis;
  DesPos->x =ZeroX+(Lx-ZeroX)*cos(ang)-(Ly-ZeroY)*sin(ang);
  DesPos->y =ZeroY+(Lx-ZeroX)*sin(ang)+(Ly-ZeroY)*cos(ang);
}
//-------------↓↓↓↓斜线算法CALLBACK处理函数↓↓↓↓---------------------------------
// 参数: 目标X,目标Y,附加参数
// 返回: void
// 附加: 回调函数
//////////////////////////////////////////////////////////////////////////////////////////
VOID CALLBACK LineDDAProc(int X,int Y,LPARAM lpData)
{
  WalkCount++;
  if (WalkCount%WalkStep==0)
  {
    PPOSINFO PosInfo = new POSINFO;
    PosInfo->X = X;
    PosInfo->Y = Y;
    PosInfo->ReMapCode = 0;
    WalkData->Add(PosInfo);
  }
}
//-------------↓↓↓↓根据斜线算法生成路径↓↓↓↓---------------------------------
// 参数: 源X,源Y,目的X,目的Y,步长,结果保存列表
// 返回: 总步数
// 附加:
//////////////////////////////////////////////////////////////////////////////////////////
int MakeLineStep(int CurX,int CurY,int DesX,int DesY,int Step,TList *WalkList)
{
  PPOSINFO PosInfo = new POSINFO;
  WalkCount = 0;
  WalkStep =  Step;
  PosInfo->X = DesX;
  PosInfo->Y = DesY;
  PosInfo->ReMapCode = 0;
  WalkData = WalkList;
  LineDDA(CurX,CurY,DesX,DesY,(LINEDDAPROC)&LineDDAProc,NULL);
  WalkData->Add(PosInfo);
  return  WalkData->Count;
}
//-------------↓↓↓↓time_t转换成TDateTime格式↓↓↓↓---------------------------------
// 参数: time_t ,是否输出格林时间
// 返回: TDateTime格式的时间
// 附加:
//////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
TDateTime Unix_timeToPc_time(time_t t,bool UTC)
{
  TDateTime tmpDate;
  TSystemTime SysTime,TmpSysTime;
  FILETIME FTime,LTime;
  tmpDate =  ((double)t)/86400+25569;
  if (UTC)
  {
    return tmpDate;
  }
  else
  {
    DateTimeToSystemTime(tmpDate,TmpSysTime);
    SystemTimeToFileTime(&TmpSysTime,&FTime);
    FileTimeToLocalFileTime(&FTime,&LTime);
    FileTimeToSystemTime(&LTime,&SysTime);
    return  SystemTimeToDateTime(SysTime);
  }
}


//-------------↓↓↓↓获取某个目录下某种后缀名的所有文件名列表↓↓↓↓---------------------------------
// 参数: 目录名,后缀名,保存结果的字符串列表
// 返回: 符合条件的文件总数
// 附加:
//////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
int GetFileList(const String &DirName,const String &Ext,TStrings *ResultList,bool SubDir)
{
  TSearchRec sr;
  String PathStr = DirName+"\\*.*";
  int  FileCount = 0;
  if (FindFirst(PathStr,faAnyFile,sr) == 0)
  {
    do
    {
      if (sr.Name=="." || sr.Name=="..")
      {
        continue;
      }
      if ((sr.Attr & faDirectory) == faDirectory)
      {
        if (SubDir)
        {
          GetFileList(DirName+"\\"+sr.Name,Ext,ResultList,true);
        }
      }
      else
      {
        if (Ext != "*.*")
        {
          if (Ext.Pos(ExtractFileExt(sr.Name)) >0)
          {
              FileCount++;
              ResultList->Add(DirName+"\\"+sr.Name);
          }
        }
        else
        {
              FileCount++;
              ResultList->Add(DirName+"\\"+sr.Name);
        }
      }
    } while (FindNext(sr) == 0);
    FindClose(sr);
  }
  return  FileCount;

}
//---------------------------------------------------------------------------
int GetFileList(const String &DirName,const String &Ext,const String &TrueExt,TStrings *ResultList,bool SubDir)
{
  TSearchRec sr;
  String PathStr = DirName + "\\"+Ext;
  int  FileCount = 0;
  if (FindFirst(PathStr,faAnyFile,sr) == 0)
  {
    do
    {
      if (sr.Name=="." || sr.Name=="..")
      {
        continue;
      }
      if ((sr.Attr & faDirectory) == faDirectory)
      {
        if (SubDir)
        {
          GetFileList(DirName+"\\"+sr.Name,Ext,TrueExt,ResultList,true);
        }
      }
      else
      {
        if (ExtractFileExt(sr.Name) == TrueExt)
        {
          FileCount++;
          ResultList->Add(DirName+"\\"+sr.Name);
        }
      }
    } while (FindNext(sr) == 0);
    FindClose(sr);
  }
  return  FileCount;
}
//---------------------------------------------------------------------------
void  ZeroTextFile(String FileName)
{
     TStringList * tmpFile = new  TStringList;
     try
     {
       tmpFile->SaveToFile(FileName);  //清空文件
     }
     __finally
     {
       delete  tmpFile;
     }
}
//---------------------------------------------------------------------------
int GetFileList(const String &Path,const String &Ext,TStrings *ResultList)
{
  TSearchRec sr;
  String PathStr;
  int FileCount=0;
  PathStr = Path + "\\"+Ext;
  if (FindFirst(PathStr,faAnyFile,sr)==0)
  {
    FileCount++;
    ResultList->Add(sr.Name);
    while (FindNext(sr) ==0)
    {
      FileCount++;
      ResultList->Add(sr.Name);
    }
    FindClose(sr);
  }
  return FileCount;
}
//---------------------------------------------------------------------------
int GetFileSize(String sFileName)
{
  TSearchRec sr;
  int i;
  if (FindFirst(sFileName,faAnyFile,sr)==0)
  {
     return  sr.Size;
  }
  FindClose(sr);
  return 0;
}
//------------------------------------------------------------------------------
float  NumberToPercent(int Number1,int Number2)
{
  if (Number2<=0)
    return 0;
  //计算两个数值的百分比
  return (float)(((float)Number1/(float)Number2)*100);
}
//------------------------------------------------------------------------------
int CalcPosDis(int CurX,int CurY,int DesX,int DesY)
{

  if (CurX == DesX && CurY== DesY)
     return 0;
  long dx = abs(DesX-CurX);
  long dy = abs(DesY-CurY);
  double distance = sqrt(abs(dx*dx + dy*dy));
  return distance;

  /*double ii;
  if (CurX == DesX && CurY== DesY)
   return 0;
  try
  {
    DesX = abs(DesX-CurX);
    DesY = abs(DesY-CurY);
    ii   = DesX*DesX+DesY*DesY;
    if (ii<1)
      return -1;
    return abs(sqrtl(ii));
  }
  catch(...)
  {
    return -1;
  }    */
}
//---------------------------------------------------------------------------
String GetSysDir()
{
  TCHAR pSysPath[MAX_PATH];
  String ResultStr;
  GetSystemDirectory(pSysPath, sizeof(pSysPath) / sizeof(TCHAR));
  String SysPath = pSysPath;
  ResultStr = SysPath;
  return ResultStr;
}
//---------转换路径-----------------------------------------------------
String EnvironmentPath(String PathName)
{
  TCHAR pcPathName[MAX_PATH];
  String ResultStr;
  ExpandEnvironmentStrings(PathName.c_str(),pcPathName,sizeof(pcPathName) / sizeof(TCHAR));
  String cPathName = pcPathName;
  ResultStr = cPathName;
  return ResultStr;
}
//---------获取当前进程全路径--------------------------------------------------
String GetProcessName()
{
  String Info;
  TCHAR psProcessName[MAX_PATH];
  GetModuleFileName(NULL, psProcessName, sizeof(psProcessName) / sizeof(TCHAR));
  String sProcessName = psProcessName;
  Info = sProcessName;
  return Info;
}
//---------运行外部程序--------------------------------------------------
DWORD MyWinExeC(const String &Cmdline,String DirName,int Visibility )
{
   DWORD ProcessId;
   STARTUPINFO StartupInfo;
   PROCESS_INFORMATION ProcessInfo;
   ZeroMemory(&StartupInfo, sizeof(STARTUPINFO));
   //DirName = ExtractFileDir(Cmdline);
   StartupInfo.cb = sizeof(StartupInfo);
   StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
   StartupInfo.wShowWindow = Visibility;
   ProcessId = CreateProcess(NULL,Cmdline.c_str(),NULL,NULL,false,0,NULL,DirName.c_str(),&StartupInfo,&ProcessInfo);
   if (!ProcessId)
   {
     return 0;
   }
   else
   {
     return  ProcessInfo.dwProcessId;
   }
}
//---------获取当前进程全路径--------------------------------------------------
String GetCurDir()
{
   return ExtractFilePath(GetProcessName());
}
//---------输出调试信息-----------------------------------------
void ShowDebugInfo(String Info)
{
  OutputDebugString(Info.c_str());
}
//---------------------------------------------------------------------------
bool CALLBACK SearchWindowProc(HWND hWnd, LPSEARCHWINDOWDATA lpSearchData)
{
  DWORD       iWndProcessId;
  TCHAR plpClassName[256];

  GetClassName(hWnd, plpClassName, sizeof(plpClassName) / sizeof(TCHAR));
  String lpClassName = plpClassName;
  if(!lpSearchData->strClassName ||
     (lpClassName == lpSearchData->strClassName))
  {
    GetWindowText(hWnd, lpClassName.c_str(), lpClassName.Length());
    if(!lpSearchData->strWindowName ||
       lpClassName == lpSearchData->strWindowName)
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
HWND __fastcall SearchWindow(DWORD ProcessId, LPCSTR strClassName, LPCSTR strWindowName)
{
  SEARCHWINDOWDATA lpSearchData;
  lpSearchData.dwOwnerPID = ProcessId;
  lpSearchData.strClassName = strClassName;
  lpSearchData.strWindowName = strWindowName;
  lpSearchData.hWnd = NULL;
  EnumWindows((WNDENUMPROC)SearchWindowProc, (LPARAM)&lpSearchData);
  return lpSearchData.hWnd;
}
//------------------------------------------------------------------------------
BYTE ReadBYTE(LPBYTE Buf,int &DataPos)
{
   BYTE Result =  Buf[DataPos];
   DataPos+=sizeof(BYTE);
   return Result;
}
//------------------------------------------------------------------------------
BYTE ReadBit(BYTE * data, int maxLength, int index)
{
	if(maxLength <= (index >> 3))
	{
        throw Exception("ReadBit Length Error!");
	}
    return ( data[ index >> 3 ] & ( 1 << ( index & 0x7 ) )) != 0;
}
//------------------------------------------------------------------------------
void WriteBit(BYTE * data, int maxLength, int index, int value)
{
	if(maxLength <= (index >> 3))
	{
		throw Exception("WriteBit Length Error!");
	}
	if(value)
	{
		data[ index >> 3 ] = ( data[ index >> 3 ] | ( 1 << ( index & 0x7 ) ));
	}
	else
	{
		if(ReadBit(data, maxLength, index))
		{
			data[ index >> 3 ] = ( data[ index >> 3 ] ^ ( 1 << ( index & 0x7 ) ));
		}
	}
}
//------------------------------------------------------------------------------
WORD ReadWORD(LPBYTE Buf,int &DataPos)
{
   WORD Result =  *LPWORD(&Buf[DataPos]);
   DataPos+=sizeof(WORD);
   return Result;
}
//------------------------------------------------------------------------------
DWORD ReadDWORD(LPBYTE Buf,int &DataPos)
{
   DWORD Result =  *LPDWORD(&Buf[DataPos]);
   DataPos+=sizeof(DWORD);
   return Result;
}
uint64 ReadUINT64(LPBYTE Buf,int &DataPos)
{
   uint64 Result =  *LPUINT64(&Buf[DataPos]);
   DataPos+=sizeof(uint64);
   return Result;
}
//------------------------------------------------------------------------------
#include <vcl.h>
float ReadFloat(LPBYTE Buf,int &DataPos)
{
    float Result =  *(float *)(&Buf[DataPos]);
    DataPos+=sizeof(float);
    return Result;
}
//------------------------------------------------------------------------------
double ReadDouble(LPBYTE Buf,int &DataPos)
{
   double Result =  *(double *)(&Buf[DataPos]);
   DataPos+=sizeof(double);
   return Result;
}

//------------------------------------------------------------------------------
void ReadBuf(LPVOID Buf,int &DataPos,LPVOID DesBuf,int Len)
{
   CopyMemory(DesBuf,(char *)Buf+DataPos,Len);
   DataPos+=Len;
}
//------------------------------------------------------------------------------
void WriteBuf(LPVOID Buf,int &DataPos,LPVOID SrcBuf,int Len)
{
   CopyMemory((char *)Buf+DataPos,SrcBuf,Len);
   DataPos+=Len;
}
//------------------------------------------------------------------------------
void WriteBYTE(LPBYTE Buf,int &DataPos,BYTE Value)
{
   Buf[DataPos] = Value;
   DataPos+=sizeof(BYTE);
}
//------------------------------------------------------------------------------
void WriteWORD(LPBYTE Buf,int &DataPos,WORD Value)
{
   *LPWORD(&Buf[DataPos]) =  Value;
   DataPos+=sizeof(WORD);
}
//------------------------------------------------------------------------------
void WriteDWORD(LPBYTE Buf,int &DataPos,DWORD Value)
{
   *LPDWORD(&Buf[DataPos]) =  Value;
   DataPos+=sizeof(DWORD);
}
void WriteUINT64(LPBYTE Buf,int &DataPos,uint64 Value)
{
   *LPUINT64(&Buf[DataPos]) =  Value;
   DataPos+=sizeof(uint64);
}
//------------------------------------------------------------------------------
void WriteFloat(LPBYTE Buf,int &DataPos,float Value)
{
  *(float *)(&Buf[DataPos]) = Value;
  DataPos+= sizeof(float);
}
//------------------------------------------------------------------------------
void WriteDouble(LPBYTE Buf,int &DataPos,double Value)
{
  *(double *)(&Buf[DataPos]) = Value;
  DataPos+= sizeof(double);
}
//------------------------------------------------------------------------------
void WriteWideString(char *buf,int &DataPos,String &Text)
{
    WideString WSayText =  WideString(Text);
    CopyMemory(&buf[DataPos],WSayText.c_bstr(), WSayText.Length()*2);
    DataPos+= WSayText.Length()*2+2;
}
//------------------------------------------------------------------------------
int FindWORD(LPBYTE cData, int MaxLen, WORD Value)
{
  for (int i = 0; i < MaxLen; i++)
  {
    if (MaxLen - i >= (int)sizeof(WORD))
    {
      if (*LPWORD(&cData[i]) == Value)
      {
        return i;
      }
    }
  }

  return -1;
}
//------------------------------------------------------------------------------
int  FindDWORD(LPBYTE cData,int MaxLen,DWORD Value)
{
  for (int i = 0; i < MaxLen; i++)
  {
    if (MaxLen - i >= (int)sizeof(DWORD))
    {
      if (*LPDWORD(&cData[i]) == Value)
      {
        return i;
      }
    }
  }

  return -1;
}
//------------------------------------------------------------------------------
int  GetLocalIP(TStrings * IPList)
{
  char cName[255];
  WSADATA wsaData;
  PHOSTENT hostinfo;
  WORD wVersionRequested;
  struct in_addr iLastIP;
  String aLocalIP="127.0.0.1";
  wVersionRequested = MAKEWORD( 2, 0);
  if(WSAStartup(wVersionRequested, &wsaData ) == 0)
  {
    if(gethostname(cName, sizeof(cName)) == 0)
    {
      if((hostinfo = gethostbyname(cName)) != NULL)
      {
        do                                  // 以下就是本机IP列表
        {
          iLastIP = *(struct in_addr*)*hostinfo->h_addr_list;
          hostinfo->h_addr_list ++;
          IPList->Add((String)inet_ntoa(iLastIP));
        }while(*hostinfo->h_addr_list != NULL);

      }
    }
    WSACleanup();
  }
  return IPList->Count;
}

//------------------------------------------------------------------------------
bool  IsLocalIP(String IP)
{
  bool   IsSelfIP = false;
  String First = IP.SubString(1,IP.Pos(".")-1);
  TStringList * IPList = new TStringList;
  try
  {
    GetLocalIP(IPList);
    IsSelfIP = (IPList->IndexOf(IP)>=0);
  }
  __finally
  {
    delete  IPList;
  }
  return (IsSelfIP || First == "127" || First=="192" || First == "172" || First == "10");
}
//------------------------------------------------------------------------------
int WINAPI fnEncode6BitBufA(unsigned char *pszSrc, char *pszDest, int nSrcLen, int nDestLen)
{
	int				nDestPos	= 0;
	int				nRestCount	= 0;
	unsigned char	chMade = 0, chRest = 0;

	for (int i = 0; i < nSrcLen; i++)
	{
		if (nDestPos >= nDestLen) break;
		
		chMade = ((chRest | (pszSrc[i] >> (2 + nRestCount))) & 0x3f);
		chRest = (((pszSrc[i] << (8 - (2 + nRestCount))) >> 2) & 0x3f);

		nRestCount += 2;

		if (nRestCount < 6)
			pszDest[nDestPos++] = chMade + 0x3c;
		else
		{
			if (nDestPos < nDestLen - 1)
			{
				pszDest[nDestPos++]	= chMade + 0x3c;
				pszDest[nDestPos++]	= chRest + 0x3c;
			}
			else
				pszDest[nDestPos++] = chMade + 0x3c;

			nRestCount	= 0;
			chRest		= 0;
		}
	}

	if (nRestCount > 0)
		pszDest[nDestPos++] = chRest + 0x3c;

//	pszDest[nDestPos] = '\0';

	return nDestPos;
}
//------------------------------------------------------------------------------
int  WINAPI fnDecode6BitBufA(char *pszSrc, char *pszDest, int nDestLen)
{
	int   nLen = strlen((const char *)pszSrc);
	int   nDestPos = 0, nBitPos = 2;
	int   nMadeBit = 0;
	unsigned char	ch, chCode, tmp;
	for (int i = 0; i < nLen; i++)
	{
		if ((pszSrc[i] - 0x3c) >= 0)
			ch = pszSrc[i] - 0x3c;
		else
		{
			nDestPos = 0;
			break;
		}

		if (nDestPos >= nDestLen) break;

		if ((nMadeBit + 6) >= 8)
		{
			chCode = (tmp | ((ch & 0x3f) >> (6 - nBitPos)));
			pszDest[nDestPos++] = chCode;

			nMadeBit = 0;

			if (nBitPos < 6)
				nBitPos += 2;
			else
			{
				nBitPos = 2;
				continue;
			}
		}

		tmp = ((ch << nBitPos) & Decode6BitMask[nBitPos - 2]);

		nMadeBit += (8 - nBitPos);
	}

//	pszDest[nDestPos] = '\0';

	return nDestPos;
}
//------------------------------------------------------------------------------
AnsiString EncodeStr(AnsiString Src)
{
    char DesStr[8192];
    int  EnLen = fnEncode6BitBufA(Src.c_str(),DesStr,Src.Length(),sizeof(DesStr));
    if (EnLen >0)
	 return  AnsiString(DesStr,EnLen);
    else
     return "";
}
//------------------------------------------------------------------------------
AnsiString DecodeStr(AnsiString Src)
{
    char DesStr[8192];
    int  EnLen = fnDecode6BitBufA(Src.c_str(),DesStr,sizeof(DesStr));
    if (EnLen >0)
     return  AnsiString(DesStr,EnLen);
    else
     return "";
}

//------------------------------------------------------------------------------
bool IsWin2k()
{
  OSVERSIONINFO lpOs;
  lpOs.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
  GetVersionEx(&lpOs);
  if (lpOs.dwPlatformId == VER_PLATFORM_WIN32_NT)
   return true;
  else
   return false;
}
//------------------------------------------------------------------------------
void ReBoot()
{
  if (IsWin2k())
  {
    ShutDown2K(EWX_REBOOT);
  }
  else
  {
    ExitWindowsEx(EWX_REBOOT,0);
  }
}
//------------------------------------------------------------------------------
void ShutDown()
{
  if(IsWin2k())
  {
    ShutDown2K(EWX_POWEROFF);
  }
  else
  {
    ExitWindowsEx(EWX_SHUTDOWN, 0); // 关机
  }
}
//------------------------------------------------------------------------------
bool ShutDown2K(UINT Flag)
{
  HANDLE            hToken;
  TOKEN_PRIVILEGES  tkp;
  UINT              FFlag;
  FFlag = Flag | EWX_FORCE;
  if(IsWin2k())
  {
    // Windows NT 3.51, Windows NT 4.0, Windows 2000,
    // Windows XP, or Windows .NET Server
    if(!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken))
      return false;
    LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
    tkp.PrivilegeCount = 1; // one privilege to set
    tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES) NULL, 0);
    ExitWindowsEx(FFlag, 0);
    return true;
  }
  else
    return false;
}
//------------------------------------------------------------------------------
void PopUpWindow(HWND WinHwnd)
{
  HWND  hFocusWin, hOtherWin;
  DWORD OtherThreadID;
  hOtherWin = GetForegroundWindow();
  OtherThreadID = GetWindowThreadProcessId(hOtherWin, NULL);
  if(AttachThreadInput(GetCurrentThreadId(), OtherThreadID, TRUE))
  {
    hFocusWin = GetFocus();
    SetFocus(WinHwnd);
    if(hFocusWin != 0)
    {
      AttachThreadInput(GetCurrentThreadId(), OtherThreadID, FALSE);
    }
  }
  else
  {
    SetFocus(WinHwnd);
  }
}

//------------------------------------------------------------------------------
String GetEXEVersion(const String &path)
{
	DWORD infoSize = GetFileVersionInfoSize(path.c_str(), NULL);
	if(infoSize == 0)
	{
		return	FormatStr("GetEXEVersion Error : %s", SysErrorMessage(GetLastError()));
	}
	vector<BYTE>	infoData;
	infoData.resize(infoSize);
	LPVOID pBlock = &infoData[0];
	GetFileVersionInfo(path.c_str(), 0, infoData.size(), pBlock);

	// Read the list of languages and code pages.
	UINT32 cbTranslate = 0;
  	struct LANGANDCODEPAGE {
	  WORD wLanguage;
	  WORD wCodePage;
	} *lpTranslate;
	VerQueryValue(pBlock,
				  TEXT("\\VarFileInfo\\Translation"),
				  (LPVOID*)&lpTranslate,
				  &cbTranslate);

	if(lpTranslate == NULL || cbTranslate == 0)
	{
		return	FormatStr("GetEXEVersion Error2 : %s", SysErrorMessage(GetLastError()));
	}

	String strTranslation = FormatStr("%04x%04x", lpTranslate->wLanguage, lpTranslate->wCodePage);

	String strSubBlock;
	strSubBlock = FormatStr("\\StringFileInfo\\%s\\FileVersion",strTranslation);
	wchar_t *result = NULL;
	UINT32 resultLen = 0;
	VerQueryValue(pBlock,strSubBlock.c_str(),(LPVOID*)&result,&resultLen);
	return	result;
}
//------------------------------------------------------------------------------
TColor RGB2Color(BYTE R,BYTE G,BYTE B)
{
   return TColor((B << 16) | (G << 8) | R);
}
//------------------------------------------------------------------------------
void   DrawShadeBar(TCanvas * DrawCanvas,int ClientWidth,int ClientHeight)
{
    TRect rectangle;
    int   ColorValue;
    for(int i = 0; i < ClientWidth; i++)
    {
       rectangle =   TRect(i, 0, i + 1, ClientHeight);
       ColorValue = MulDiv(i, 255,ClientWidth);
       DrawCanvas->Brush->Color = RGB2Color(ColorValue,ColorValue,ColorValue);
       DrawCanvas->FillRect(rectangle);
    }
}

bool	ProcessExists(DWORD processID)
{
	DWORD aProcesses[1024], cbNeeded;
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded))
	{
		return false;
	}
	for (DWORD i = 0; i < cbNeeded; i++)
	{
		if(aProcesses[i] == processID)
			return true;
	}
	return false;
}

TDateTime TTimeToDateTime(const time_t t)
{
	TDateTime rv;
	struct tm *stm = localtime(&t);
	if (stm)
	{
		rv = TDateTime(stm->tm_year + 1900, stm->tm_mon + 1, stm->tm_mday);
		rv += TDateTime(stm->tm_hour, stm->tm_min, stm->tm_sec, 0);
	}
	return(rv);
}

uint64 Uint64Pow(uint64 num, int val)
{
	uint64 result = 1;
	for(int i=0; i<val; i++)
	{
		result *= num;
	}
	return result;
}

uint64 StrToUint64Def(String str, int def)
{
	uint64 val = 0;
	for(int i=str.Length()-1; i>=0; i--)
	{
		if(str.c_str()[i] > '9' || str.c_str()[i] < '0')
			return def;
		val += (str.c_str()[i] - '0') * (Uint64Pow(10, str.Length()-i-1));
	}
	return val;
}

String ReplaceStr(String input, String from, String to)
{
	TReplaceFlags   flag;
	flag << rfReplaceAll;
	return StringReplace(input, from, to, flag);
}

bool ForceRemoveDir(String SourceDir)
{
	TSHFileOpStruct   FileOp;
	ZeroMemory(&FileOp, sizeof(FileOp));
	FileOp.hwnd=NULL;
	FileOp.wFunc=FO_DELETE;
	FileOp.pFrom=SourceDir.c_str();
	FileOp.fFlags=FOF_NOCONFIRMMKDIR|FOF_CONFIRMMOUSE|FOF_NOCONFIRMATION;
	FileOp.fAnyOperationsAborted=false;
	FileOp.hNameMappings=NULL;
	if(SHFileOperation(&FileOp))
	{
		return false;
	}
	String dir = ExtractFilePath(SourceDir);
	if(!RemoveDir(dir))
	{
		return false;
	}
	return true;
}

double GetNowTick()
{
	LARGE_INTEGER OneCount, EndCountValue;
	QueryPerformanceFrequency(&OneCount);
	double Freq =  (double)OneCount.QuadPart;  //频率倍数
	QueryPerformanceCounter(&EndCountValue);
	double Minus =  (double)(EndCountValue.QuadPart);
	return  (Minus/Freq)*1000;
}
