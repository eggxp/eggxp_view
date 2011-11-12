//---------------------------------------------------------------------------
#pragma hdrstop

#include "Scriptstack.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//------------------------------------------------------------------------------
__fastcall CScriptStack::CScriptStack()
{
    ScriptList = new TList;
}
//------------------------------------------------------------------------------
__fastcall CScriptStack::~CScriptStack()
{
    Clear();
    delete ScriptList;
}
//------------------------------------------------------------------------------
void CScriptStack::Push(SCRIPTSTACK &ScriptStock)//TStringList *CmdList,int EIP)
{
    PSCRIPTSTACK CurScript = new SCRIPTSTACK;
    CurScript->ScrCmd = new TStringList;
    CurScript->ScrCmd->Assign(ScriptStock.ScrCmd);
    CurScript->EIP    = ScriptStock.EIP;
    CurScript->Name   = ScriptStock.Name;
    CurScript->Info   = ScriptStock.Info;
    CurScript->File   = ScriptStock.File;
    ScriptList->Add(CurScript);
}
//------------------------------------------------------------------------------
void CScriptStack::Pop(SCRIPTSTACK &ScriptStock)
{
    if (GetLevel()<1)
        return;
    PSCRIPTSTACK TopScript;
    int EIp;
    TopScript = PSCRIPTSTACK(ScriptList->Items[ScriptList->Count-1]);
    ScriptStock.ScrCmd->Assign(TopScript->ScrCmd);
    ScriptStock.Name = TopScript->Name;
    ScriptStock.Info = TopScript->Info;
    ScriptStock.EIP =  TopScript->EIP;
    ScriptStock.File = TopScript->File;
    delete  TopScript->ScrCmd;
    delete  TopScript;
    ScriptList->Delete(ScriptList->Count-1);
}
//------------------------------------------------------------------------------
void CScriptStack::Clear()
{
    PSCRIPTSTACK TopScript;
    for (int i=0;i<ScriptList->Count;i++)
    {
        TopScript = (PSCRIPTSTACK)ScriptList->Items[i];
        delete TopScript->ScrCmd;
        delete TopScript;
    }
    ScriptList->Clear();
}
//------------------------------------------------------------------------------
int CScriptStack::GetLevel()
{
    return ScriptList->Count;
}
