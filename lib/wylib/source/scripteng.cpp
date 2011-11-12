//---------------------------------------------------------------------------


#pragma hdrstop

#include "scripteng.h"
#include "CommFunc.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)
//------------------------------------------------------------------------------
__fastcall CScriptEngine::CScriptEngine(TComponent * AOwner)
{
   fsScript = new TfsScript(AOwner);
   CPPLang  = new TfsCPP(AOwner);
   TfsScript* GlobalScriptObj =  fsGlobalUnit();
   fsScript->SyntaxType = "C++Script";
   fsScript->Parent  =  GlobalScriptObj;
}
//------------------------------------------------------------------------------
__fastcall CScriptEngine::~CScriptEngine()
{
   if (fsScript->IsRunning)
   {
      fsScript->Stop();
   }
   SAFE_DELETE(CPPLang);
   SAFE_DELETE(fsScript);
}
//------------------------------------------------------------------------------
DWORD WINAPI CScriptEngine::WorkerThread(LPVOID  ScriptEngine)
{
    CScriptEngine * CurrentScriptEngine =   (CScriptEngine *)ScriptEngine;
    try
    {
       CurrentScriptEngine->fsScript->Execute();
    }
    catch(...)
    {
       return 1;
    }
    return 0;
}
//------------------------------------------------------------------------------
bool   CScriptEngine::Start(bool ThreadMode)
{
   if (IsRunning())
   {
     m_LastErrorInfo = "script already running";
     return false;
   }
   fsScript->ClearAll();
   m_ThreadMode    = ThreadMode;
   if (!fsScript->Compile())
   {
      m_LastErrorInfo = FormatStr("Error Pos[%s]:%s",fsScript->ErrorPos,fsScript->ErrorMsg);
      return false;
   }
   if (m_ThreadMode)
   {
       m_ThreadId = 0;
       HANDLE ThreadHandle = CreateThread(NULL,0,WorkerThread,this,0,&m_ThreadId);
       CloseHandle(ThreadHandle);
       return true;
   }
   else
   {
       fsScript->Execute();
       return true;
   }
}
//------------------------------------------------------------------------------
void   CScriptEngine::Stop()
{
    if (m_ThreadMode)
    {
       m_ThreadId = 0;
    }
    fsScript->Stop();
}
