//---------------------------------------------------------------------------
#ifndef ScriptstackH
#define ScriptstackH
#include <Classes.hpp>
#include <Windows.h>
//---------------------------------------------------------------------------
typedef struct tagSCRIPTSTACK
{
  TStringList *ScrCmd;
  String Name;
  String File;
  String Info;
  int  EIP;
}
SCRIPTSTACK,*PSCRIPTSTACK;
//脚本调用堆栈类
class CScriptStack
{
private:
  TList *ScriptList;
public:
  __fastcall CScriptStack();
  __fastcall ~CScriptStack();
  int GetLevel();
  void Clear();
  void Push(SCRIPTSTACK &ScriptStock);
  void Pop(SCRIPTSTACK &ScriptStock);

};
#endif
