//---------------------------------------------------------------------------


#pragma hdrstop

#include "counttime.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
__fastcall CTimeCount::CTimeCount()
{
   LARGE_INTEGER OneCount;
   QueryPerformanceFrequency(&OneCount);
   Freq =  (double)OneCount.QuadPart;  //ÆµÂÊ±¶Êý
   IsBegin = false;
}
//---------------------------------------------------------------------------
__fastcall CTimeCount::~CTimeCount()
{

}
//---------------------------------------------------------------------------
void __fastcall CTimeCount::BeginCount()
{
    QueryPerformanceCounter(&StartCountValue);
    IsBegin = true;
}
//---------------------------------------------------------------------------
double __fastcall CTimeCount::EndCount()
{
    if (!IsBegin)
      return 0;
    QueryPerformanceCounter(&EndCountValue);
    Minus =  (double)(EndCountValue.QuadPart - StartCountValue.QuadPart);
    return  (Minus/Freq)*1000;
}
