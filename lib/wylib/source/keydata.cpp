//---------------------------------------------------------------------------
#pragma hdrstop
#include "keydata.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
__fastcall AIndexManage::AIndexManage(int MaxRecord)
{
  DataList = new AIndexList<AKeyData>(true);
}

//---------------------------------------------------------------------------
__fastcall AIndexManage::~AIndexManage()
{
  delete DataList;
}
//---------------------------------------------------------------------------
int      AIndexManage::IndexOf(DWORD KeyID)
{
    return DataList->IndexOf(IntToStr(KeyID).c_str());
//	for (int i=0;i<DataList->Count();i++)
//    {
//        if (DataList->At(i)->GetKey() == KeyID)
//        {
//           return i;
//        }
//    }
//    return -1;
}
//---------------------------------------------------------------------------
int    AIndexManage::IndexOfName(String Name)
{
    for (int i=0;i<DataList->Count();i++)
    {
        if (DataList->At(i)->GetName() == Name)
        {
           return i;
        }
    }
    return -1;
}
//---------------------------------------------------------------------------
AKeyData * AIndexManage::Get(DWORD KeyID)
{
     int Index =    IndexOf(KeyID);
     return At(Index);
}
//---------------------------------------------------------------------------
AKeyData * AIndexManage::GetByName(String Name)
{
     int Index =    IndexOfName(Name);
     return At(Index);
}
//---------------------------------------------------------------------------
bool  AIndexManage::Add(AKeyData * KeyData)
{
    int OldIndex = IndexOf(KeyData->GetKey());
    AKeyData * OldObj = At(OldIndex);
    if (OldObj !=NULL)  //原来已经有了
    {
        if (OldObj == KeyData)   //添加的对象已经存在
        {
           return false;
        }
        OldObj->Assign(KeyData);
        delete KeyData;
        return false;
    }
    else
    {
		DataList->Add(IntToStr(KeyData->GetKey()).c_str(),KeyData);
        return true;
    }
}
//---------------------------------------------------------------------------
String   AIndexManage::GetName(DWORD ID)
{
  AKeyData * OldObj = At(IndexOf(ID));
  if (OldObj)
  {
    return OldObj->GetName();
  }
  return IntToStr(ID);
}


