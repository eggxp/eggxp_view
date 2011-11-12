//---------------------------------------------------------------------------

#ifndef linepathH
#define linepathH
#include <vcl.h>
#include "alist.h"
class  ALinePath
{
private:
  AList<TPoint> * WayPointList;
  int CurStepLong;
  int LineMoveStep;
protected:
  static VOID CALLBACK DirectProc(int X,int Y,LPARAM lpData);
public:
   ALinePath();
   ~ALinePath();
	//直线处理,StepLong为每点之间的间隔长度,返回值为生成的路点数量
   int Process(DWORD StartX,DWORD StartY,DWORD EndX,DWORD EndY,int StepLong=20);
   int Count(){return WayPointList->Count();} //返回生成的路点数量
   TPoint *  At(int Index){return WayPointList->At(Index);} //取一个路点

};
//---------------------------------------------------------------------------
#endif
