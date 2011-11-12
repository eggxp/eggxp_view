//---------------------------------------------------------------------------


#pragma hdrstop

#include "patchexe.h"
#include "CommFunc.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
__fastcall TPatchProcess::TPatchProcess()
{
   m_PatchInfoList = new AList<tagPatchAddrInfo>(true,100);
}
//------------------------------------------------------------------------------
__fastcall TPatchProcess::~TPatchProcess()
{
   delete m_PatchInfoList;
}
//------------------------------------------------------------------------------
bool TPatchProcess::PatchRecord(HANDLE              ProcessHandle,
                                DWORD               ProcessID,
                                tagPatchAddrInfo    *lpPatchRecord)
{
    BYTE    OrgCodeData[MAX_PATCH_LEN]; //目前进程的原始内容
    memset(&OrgCodeData, 0, MAX_PATCH_LEN);
    if(!D_ReadMemory(ProcessID,
                     lpPatchRecord->Address,
                     lpPatchRecord->Len,
                     (LPBYTE) & OrgCodeData))
    {

        //进程内存读取失败了
        LastError.sprintf("Read memory fail,addr = 0x%x",
                          lpPatchRecord->Address);
        return false;
    }

    if(memcmp(&OrgCodeData,
              &lpPatchRecord->NewCodeData,
              lpPatchRecord->Len) == 0)
    {

        //当前进程的内存数据已经是和修改内存相同了
        return true;
    }

    if(memcmp(&OrgCodeData,
              &lpPatchRecord->OrgCodeData,
              lpPatchRecord->Len) != 0)
    {

        //当前进程的内存数据和设定的原始数据不同(版本不符)
        LastError.sprintf("Memory date differ,addr = 0x%x,process_data =%s,data =%s",
                          lpPatchRecord->Address,
                          BinToStr((LPSTR) & OrgCodeData, lpPatchRecord->Len),
                          BinToStr((LPSTR) & lpPatchRecord->OrgCodeData,
                                   lpPatchRecord->Len));
        return false;
    }

    DWORD   OldProtectValue;
    VirtualProtectEx(ProcessHandle,
                     (LPVOID)lpPatchRecord->Address,
                     lpPatchRecord->Len,
                     PAGE_EXECUTE_READWRITE,
                     &OldProtectValue);
    if(!D_WriteMemory(ProcessID,
                      lpPatchRecord->Address,
                      lpPatchRecord->Len,
                      (LPBYTE) & lpPatchRecord->NewCodeData))
    {

        //进程内存写入失败了
        LastError.sprintf("Write memory fail,addr = 0x%x",
                          lpPatchRecord->Address);
        return false;
    }

    return true;
}
//------------------------------------------------------------------------------
void TPatchProcess::PatchCode(HANDLE ProcessHandle,DWORD ProcessID)
{
    tagPatchAddrInfo *  lpPatchRecord;
    FailCount = 0;
    for(int i=0;i<m_PatchInfoList->Count();i++)
    {
        lpPatchRecord =  m_PatchInfoList->At(i);
        if (!PatchRecord(ProcessHandle,ProcessID,lpPatchRecord))
        {
           FailCount++;
        }
    }
}
//------------------------------------------------------------------------------
tagPatchAddrInfo *  TPatchProcess::ExistsAddress(DWORD Address)
{
   tagPatchAddrInfo * lpPatchRecord = NULL;
   for(int i=0;i<m_PatchInfoList->Count();i++)
   {
        lpPatchRecord =  m_PatchInfoList->At(i);
        if (lpPatchRecord->Address ==  Address)
        {
          return  lpPatchRecord;
        }
   }
   return NULL;
}
//------------------------------------------------------------------------------
bool TPatchProcess::AddPatchInfo(DWORD Addrees,int Len,LPBYTE lpOrgData,LPBYTE lpPatchData)
{
     if (Len >= MAX_PATCH_LEN)
     {
        LastError = "Patch len too long";
        return false;
     }
     tagPatchAddrInfo * NewPatchRecord = NULL;
     NewPatchRecord = ExistsAddress(Addrees);
     if (NewPatchRecord == NULL)
       NewPatchRecord = new  tagPatchAddrInfo;
     memset(NewPatchRecord,0,sizeof(tagPatchAddrInfo));
     NewPatchRecord->Address =  Addrees;
     NewPatchRecord->Len     =  Len;
     memcpy(&NewPatchRecord->OrgCodeData,lpOrgData,Len);
     memcpy(&NewPatchRecord->NewCodeData,lpPatchData,Len);
     m_PatchInfoList->Add(NewPatchRecord);
     return true;
}
//------------------------------------------------------------------------------
DWORD TPatchProcess::RunExe(const String &Cmdline,String DirName,int Visibility)
{

   DWORD ProcessId;
   STARTUPINFO StartupInfo;
   PROCESS_INFORMATION ProcessInfo;
   ZeroMemory(&StartupInfo, sizeof(STARTUPINFO));
   //DirName = ExtractFileDir(Cmdline);
   StartupInfo.cb = sizeof(StartupInfo);
   StartupInfo.dwFlags = STARTF_USESHOWWINDOW;
   StartupInfo.wShowWindow = Visibility;
   ProcessId = CreateProcess(NULL,(LPSTR)Cmdline.c_str(),NULL,NULL,false,CREATE_SUSPENDED,NULL,(LPSTR)DirName.c_str(),&StartupInfo,&ProcessInfo);
   if (!ProcessId)
   {
     LastError = "CreateProcess Fail";
     return 0;
   }
   else
   {
     PatchCode(ProcessInfo.hProcess,ProcessInfo.dwProcessId);              //修改代码
     ResumeThread(ProcessInfo.hThread); //恢复游戏进程
     return  ProcessInfo.dwProcessId;
   }
}
//------------------------------------------------------------------------------
bool TPatchProcess::LoadFromMem(LPBYTE  Data,
                                int     Len)
{

    //从一串缓冲区中读取修改数据
    if(Len < 8 + sizeof(tagPatchAddrInfo))
    {
        LastError.sprintf("Datalen not not enough = %d", Len);
        return false;
    }

    int     Pos = 0;
    DWORD   Flag = ReadDWORD(Data, Pos);
    if(Flag != DATA_HEAD_FLAG)
    {
        LastError.sprintf("Data flag not matching, 0x%x != 0x%x",
                          Flag,
                          DATA_HEAD_FLAG);
        return false;
    }

    int Count = ReadDWORD(Data, Pos);
    if(Count <= 0)
    {
        LastError.sprintf("Data Count not matching, %d", Count);
        return false;
    }

    //检查数据长度
    if((int)(Count * sizeof(tagPatchAddrInfo) + 8) > Len)
    {
        LastError.sprintf("Datalen not not enough 2, %d", Len);
        return false;
    }

    tagPatchAddrInfo    *lpPatchRecord;
    for(int i = 0; i < Count; i++)
    {
        lpPatchRecord = new tagPatchAddrInfo;
        ReadBuf(Data, Pos, lpPatchRecord, sizeof(tagPatchAddrInfo));
        m_PatchInfoList->Add(lpPatchRecord);
    }

    return true;
}
//------------------------------------------------------------------------------
int   TPatchProcess::SaveToMem(LPBYTE Data)
{
    //写入修改数据到一串缓冲区中
    if (m_PatchInfoList->Count() <=0)
     return 0;
    tagPatchAddrInfo *  lpPatchRecord;
    int Pos=0;
    WriteDWORD(Data,Pos,DATA_HEAD_FLAG);
    WriteDWORD(Data,Pos,m_PatchInfoList->Count());
    for(int i=0;i<m_PatchInfoList->Count();i++)
    {
        lpPatchRecord =  m_PatchInfoList->At(i);
        WriteBuf(Data,Pos,&lpPatchRecord,sizeof(tagPatchAddrInfo));
    }
    return Pos;
}
