//---------------------------------------------------------------------------
//基于fastscript的脚本引擎包装
//可按微线程方式或普通方式运行
//
#ifndef scriptengH
#define scriptengH
#include "microthread.h"
#include "fs_iinterpreter.hpp"
#include "fs_icpp.hpp"
typedef Variant __fastcall (__closure * TCallMethodEvent)(System::TObject* Instance, TMetaClass* ClassType, const AnsiString MethodName, Variant &Params);
typedef void    __fastcall (__closure * TOnRunLine)(String UnitName,TPoint * LinePos);
class CScriptEngine
{
private:
  TfsScript *fsScript;
  TfsCPP    *CPPLang;
  bool       m_ThreadMode;
  bool		 m_ThreadSuspend; //线程是否处于挂起状态
  MicroThread::MicroThreadInfo * m_MicroThread;
protected:
  String     m_LastErrorInfo;
  static     void WorkerThread(void *  ScriptEngine);
  void __fastcall OnLine(TfsScript* Sender,const AnsiString UnitName, const AnsiString SourcePos);
public:
  __fastcall CScriptEngine(TComponent * AOwner);
  __fastcall ~CScriptEngine();
  bool       IsRunning();
  bool       IsThreadMode(){return m_ThreadMode;}  //当前是否以线程方式执行
  bool       Start(bool ThreadMode=false); //开始运行脚本,参数指定: 是否以线程方式执行
  void       Stop(); //结束脚本
  void		 ResumeThread();//恢复挂起的脚本线程
  void		 SleepThread(); //交出脚本的cpu控制权
  bool	 	 ThreadIsSuspend(){return m_ThreadSuspend;} //线程是否挂起中
  //添加一个函数供脚本调用
  //举例: AddMethod("function  Walk(PosX:int;PosY:int):boolean",OnScriptWalk);
  // 函数原型, OnScriptWalk为处理此函数的过程,定义Variant __fastcall  OnScriptWalk(System::TObject* Instance, TMetaClass* ClassType, const AnsiString MethodName, Variant &Params);
  void __fastcall AddMethod(const AnsiString Syntax, TCallMethodEvent CallEvent, const AnsiString Category = "", const AnsiString Description = "");
  //------------------------------------------------------------------------------
  String     GetLastErrorInfo(){return m_LastErrorInfo;}  //获取错误信息
  void       LoadScript(TStrings * ScriptText); //从TStrings读取脚本
  bool       LoadFromFile(String FileName);
  void		 SaveToOPCode(String FileName); //保持到中间代码
  void		 LoadOPCode(String FileName); //加载中间代码
  void       LoadOPCode(TStrings * OPCodes); //加载中间代码
  Variant __fastcall Evaluate(const AnsiString Expression); //表达式求值
  //-----------------------------------------------------------------------------
  //单步执行
  TOnRunLine  OnRunLine;
};

//---------------------------------------------------------------------------
#endif
