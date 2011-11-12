//---------------------------------------------------------------------------

#ifndef hookfuncH
#define hookfuncH
#include <windows.h>
#include <winsock.h>
#include <string>
#include "injlib.h"
#ifdef VCVERSION
#include "comm_stl.h"
#else
#include "CommFunc.h"
#endif
#include "alist.h"
using namespace std;
class CHookData
{
   public:
    string FuncName;        //函数名
    LPBYTE OrgFuncAddr;    //原来的函数指针地址
    LPBYTE NewFuncAddr;    //替换后的函数指针地址
   public:
  __fastcall CHookData();
  __fastcall ~CHookData();
};
//---------------------------------------------------------------------------
//拦截api函数的管理类
class CHooker
{
private:
  HMODULE   m_Module;  //动态链接库句柄
  string    m_DllName; //动态链接库名字
  AList<CHookData> *HookFuncList;  //需要hook的函数列表
protected:
public:
public:
  __fastcall CHooker(char * DllName);
  __fastcall ~CHooker();
  void  BeginHookFunc();
  void  EndHookFunc();
  bool  RegisterFunc(char * FuncName,LPBYTE ReplaceFuncAddr); //注册替换函数,
  bool  IsHooked(){return  m_Module != NULL;}
  LPBYTE GetOrgFuncAddr(char * FuncName);
};

#endif
