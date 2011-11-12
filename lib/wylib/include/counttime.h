//---------------------------------------------------------------------------
//精确时间间隔统计类，用于程序性能分析
//By LinYi 2004.3.31
//用法:
//CTimeCount TimeCount;
//TimeCount.BeginCount();
// 程序处理过程....
//double Havetimes = TimeCount.EndCount();
//Havetimes就是程序处理过程所消耗的时间，单位毫秒(ms)

#ifndef counttimeH
#define counttimeH
#include <windows.h>

class CTimeCount
{
private:
   LARGE_INTEGER StartCountValue,EndCountValue;
   double Freq,Minus;
protected:
   bool IsBegin;
public:
  __fastcall CTimeCount();
  __fastcall ~CTimeCount();
  void __fastcall BeginCount();
  double __fastcall EndCount();

};

//---------------------------------------------------------------------------
#endif
