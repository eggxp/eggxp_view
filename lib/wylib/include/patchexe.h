//---------------------------------------------------------------------------

#ifndef patchexeH
#define patchexeH
#include <vcl.h>
#include "alist.h"
//林弋
//2005.06.03 第一个版本
#define MAX_PATCH_LEN  16
#define DATA_HEAD_FLAG 0xaadc //保存数据的数据头标志
//------------------------------------------------------------------------------
//执行某个进程,并且在进程执行之前修改进程代码,然后恢复进程运行
#pragma pack(push, 1)

struct tagPatchAddrInfo
{
  DWORD Address; //原始地址
  int   Len;     //长度
  BYTE  OrgCodeData[MAX_PATCH_LEN]; //原始内容
  BYTE  NewCodeData[MAX_PATCH_LEN]; //修改后的内容
};
#pragma pack(pop)
//------------------------------------------------------------------------------
class TPatchProcess
{
private:
  AList<tagPatchAddrInfo> * m_PatchInfoList;
protected:
  void PatchCode(HANDLE ProcessHandle,DWORD ProcessID);
  bool PatchRecord(HANDLE ProcessHandle,DWORD ProcessID,tagPatchAddrInfo * lpPatchRecord);
  tagPatchAddrInfo *  ExistsAddress(DWORD Address);
public:
  String LastError;
  int    FailCount; //内存patch失败计数
public:
  __fastcall TPatchProcess();
  __fastcall ~TPatchProcess();
  DWORD RunExe(const String &Cmdline,String DirName,int Visibility = SW_SHOW);
//------------------------------------------------------------------------------
//添加一条修改记录
//参数: 目标地址,目标数据长度,原始数据,新数据
//返回值: 成功返回 True,失败返回false
//------------------------------------------------------------------------------
  bool AddPatchInfo(DWORD Addrees,int Len,LPBYTE lpOrgData,LPBYTE lpPatchData);

  //修改点管理函数
  bool  LoadFromMem(LPBYTE Data,int Len); //从一串缓冲区中读取修改数据
  int   SaveToMem(LPBYTE Data);           //写入修改数据到一串缓冲区中
  __inline void Delete(int Index){m_PatchInfoList->Delete(Index);}
  __inline void Clear(){m_PatchInfoList->Clear();}
  __inline tagPatchAddrInfo * At(int Index){return m_PatchInfoList->At(Index);}
  __inline int Count(){return m_PatchInfoList->Count();}
};

//---------------------------------------------------------------------------
#endif
