//---------------------------------------------------------------------------

#ifndef stringqueueH
#define stringqueueH
#include <Classes.hpp>
/* 基于TStringList封装的队列和栈 */

class TStringQueue
{
private:
   TStringList *DataList;
protected:

public:
  __fastcall TStringQueue();
  __fastcall ~TStringQueue();
  void __fastcall Push(String Data);
  String __fastcall Pop();
  bool   __fastcall Pop(String &Data);
  __inline int   __fastcall  Count(){return DataList->Count;}
  __inline void  __fastcall  Clear(){DataList->Clear();}

};
//---------------------------------------------------------------------------
class TStringStack
{
private:
   TStringList *DataList;
protected:

public:
  __fastcall TStringStack();
  __fastcall ~TStringStack();
  void __fastcall Push(String Data);
  String __fastcall Pop(String Data);
  bool   __fastcall Pop(String &Data);
  __inline int   __fastcall  Count(){return DataList->Count;}
  __inline void  __fastcall  Clear(){DataList->Clear();}

};
//---------------------------------------------------------------------------
#endif
