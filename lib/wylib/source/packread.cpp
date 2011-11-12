//---------------------------------------------------------------------------


#pragma hdrstop

#include "packread.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
__fastcall TMfsReader::TMfsReader()
{

}
//---------------------------------------------------------------------------
__fastcall TMfsReader::~TMfsReader()
{

}
//---------------------------------------------------------------------------
bool   TMfsReader::LoadFromFile(String FileName)
{
   return MfsManage.OpenMFSFile(FileName.c_str(),false);
}
//---------------------------------------------------------------------------
int   TMfsReader::FileCount()
{
   return MfsManage.GetFileCount();
}
//---------------------------------------------------------------------------
bool  TMfsReader::GetFileData(String FileName,TMemoryStream * DesBuf)
{
  HANDLE hFile = MfsManage.mfsOpenFile(FileName.LowerCase().c_str(), true);
  DWORD  Size;
  LPBYTE lpBuffer;
  if(hFile!=NULL)
  {
    Size = MfsManage.mfsGetFileBuffer(hFile, &lpBuffer);
    if(Size>0)
    {
      DesBuf->Clear();
      DesBuf->Write(lpBuffer,Size);
      MfsManage.mfsCloseFile(hFile);
      DesBuf->Position = 0;
      return true;
    }
  }
  MfsManage.mfsCloseFile(hFile);
  return false;
}


