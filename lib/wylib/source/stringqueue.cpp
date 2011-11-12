//---------------------------------------------------------------------------


#pragma hdrstop

#include "stringqueue.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//TStringStack ¶ÓÁĞ
__fastcall TStringQueue::TStringQueue()
{
    DataList = new TStringList;
}
//---------------------------------------------------------------------------
__fastcall TStringQueue::~TStringQueue()
{
    delete  DataList;
}
//---------------------------------------------------------------------------
void __fastcall TStringQueue::Push(String Data)
{
    DataList->Add(Data);
}
//---------------------------------------------------------------------------
String __fastcall TStringQueue::Pop()
{
   if (DataList->Count<=0)
    return "";
    String Result = DataList->Strings[0];
    DataList->Delete(0);
    return  Result;
}
//---------------------------------------------------------------------------
bool __fastcall TStringQueue::Pop(String &Data)
{
   if (DataList->Count<=0)
    return false;
    Data = DataList->Strings[0];
    DataList->Delete(0);
    return true;
}
//---------------------------------------------------------------------------

//TStringStack Õ»
//---------------------------------------------------------------------------
__fastcall TStringStack::TStringStack()
{
    DataList = new TStringList;
}
//---------------------------------------------------------------------------
__fastcall TStringStack::~TStringStack()
{
    delete  DataList;
}
//---------------------------------------------------------------------------
void __fastcall TStringStack::Push(String Data)
{
    DataList->Add(Data);
}
//---------------------------------------------------------------------------
String __fastcall TStringStack::Pop(String Data)
{
   if (DataList->Count<=0)
    return "";
    String Result = DataList->Strings[DataList->Count-1];
    DataList->Delete(DataList->Count-1);
    return Result;
}
//---------------------------------------------------------------------------
bool __fastcall TStringStack::Pop(String &Data)
{
   if (DataList->Count<=0)
    return false;
    Data = DataList->Strings[DataList->Count-1];
    DataList->Delete(DataList->Count-1);
    return true;
}
