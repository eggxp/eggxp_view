#ifndef scriptrunH
#define scriptrunH
#include <Classes.hpp>
#include "amap.h"
#include "scriptparam.h"
enum TScriptState { scrNotRun=0, scrRun, scrPause, scrRestart };

//运行一行脚本的适合通知使用者
//运行一行脚本之前通知使用者,参数表示是否可以运行下一行
typedef int __fastcall (__closure *TScrBeforeRunLine) (bool &CanRunNextLine);

//需要获取数值的时候通知使用者
typedef int __fastcall (__closure *TScrOnGetVarEvent) (const String &ValueStr);

//用户指定的脚本函数对应的处理函数指针
typedef int __fastcall (__closure *TUserFunction) (const String &FuncName,WY_Params &Params);
//函数对象
struct WY_Function
{
	 WY_Params  	Params;  //此函数的参数列表
	 String   		Name;    //此函数的名字
	 String   		Info;    //此函数的说明
	 TUserFunction  UserFunctionPtr;  //用户指定的处理此脚本函数的指针
	 WY_Function()
	 {
		 UserFunctionPtr = NULL;
	 }
	 int Run()
	 {
		if (UserFunctionPtr)
		{
		   return UserFunctionPtr(Name,Params);
		}
		else
		{
			return -1;
        }
     }
};

class IPascalScript;
class ICppScript;
class IParse;
class CScriptStack;
class   WY_ScriptEngine
{

private:
	TTimer			*RunTimer;	//执行时钟
    TStringList     *User_OPStr;                                    //当前命令行解析
    CScriptStack    *ScrStack;                                      //脚本运行堆栈管理类
    TMemoryStream   *ScriptSrc;                                     //脚本源代码文件流
	IPascalScript   *PascalScript;                                  //脚本语法分析器和解释器
	ICppScript      *CppScript;
	IParse          *ActiveParser;                                  //当前激活的语言解析器
    TStringList     *User_ScriptCmd;                                //脚本伪汇编命令列表
    bool            Flag_C, Flag_Z;                                 //比较判断标志位
    String          ScriptRootPath;                                 //脚本文件根目录
	TScriptState    ScriptState;                                    //当前脚本运行状态
	int             ScriptEIP;                                      //脚本当前EIP
	AList<WY_Function>	*  UserFunction; //用户自定义函数列表
	String          ScriptName;                                     //当前脚本名
	String          ScriptInfo;                                     //当前脚本信息
	String          ScriptFile;                                     //当前脚本文件
	TStringList    * ScriptPathDefs;									//默认脚本路径
private:
    String __fastcall   GetScriptPath(int ScriptType);
    bool __fastcall     IsJumpOP(String OPCode);
    String __fastcall   GetOpCmd(String CmdLine);
    int __fastcall      GetParValue(const String &Value);           //根据变量名得到变量的实际数值
    int __fastcall      FindLabel(const String &LabelName);
    bool __fastcall     GetScriptInfo(TMemoryStream *SrcCodeData, String &Name,
                                      String &Info, bool CanDelInfo);
	void __fastcall     Scr_CMP();
    void __fastcall     Scr_JMP(String JmpCmd);
	void __fastcall     Scr_Call();
	void __fastcall 	Scr_SubCall();
	int 		  GetUserFunctionIndex(const String &FuncName);
	WY_Function * GetUserFunctionByName(const String &FuncName)
	{
	   return      GetUserFunction(GetUserFunctionIndex(FuncName));
	}
	WY_Function * GetUserFunction(int Index);
	void __fastcall OnTimer(System::TObject* Sender);
	String __fastcall ParseFunctionStr(const String &FunctionDef,WY_Params * Params);
public:
	String          LastError;                                      //最后的出错信息
public:
	__fastcall          WY_ScriptEngine(String RootPath);
	__fastcall          ~WY_ScriptEngine();
	//脚本状态获取函数
	String				Name(){return ScriptName;} //获取当前脚本名
	String              Info(){return ScriptInfo;} //获取当前脚本说明                                     //当前脚本信息
	String          	File(){return ScriptFile;} //获取当前脚本文件完整路径
	int __fastcall      GetStackLv();                               //子程序堆栈层数
	String __fastcall   GetCurCmdLine();                            //当前命令行
	__inline            TScriptState GetState(){return ScriptState;}
	String				GetStataInfo();
	__inline            int          GetEIP(){return ScriptEIP;}
	int 				ErrorPos();
	void                GetSysFuncList(TStrings *SysFunc);          //获取系统函数列表
	void                GetSysIdentWordList(TStrings *IdentWord);   //获取系统关键字列表
	void                GetUserFuncList(TStrings *SysFunc);         //获取用户函数列表
	void                GetUserIdentWordList(TStrings *IdentWord);  //获取用户关键字列表
	bool                GetCmdCodeList(TStrings *DesCmdList);       //获取已编译的伪汇编代码
	__inline            bool         IsRunning(){return (ScriptState == scrRun || ScriptState == scrPause);}
	//脚本运行控制函数
	bool __fastcall     RunScript(String ScriptFileName);           //从文件运行脚本
	bool __fastcall		RunScript(TMemoryStream * SrcStream);			//从流运行脚本
	bool __fastcall		RunScript(TStrings * SrcStrings);			//从字符串列表运行脚本


	void __fastcall     StopScript();                               //停止脚本
	__inline void __fastcall     Pause(){ScriptState = scrPause;}  //暂停脚本
	__inline void __fastcall     Resume(){if (ScriptState == scrPause)ScriptState=scrRun;}  //恢复脚本运行
	bool __fastcall     DisposeCmdLine();                           //处理一行脚本
	//脚本变量设置函数
	void    SetRunInterval(int Interval){RunTimer->Interval = Interval;} //设置脚本时钟间隔
	void    SetScriptDefPath(TStrings * PathList){ScriptPathDefs->Assign(PathList);} //设置脚本默认路径表
	bool    AddUserFunc(String FuncName,String Info,WY_Params * Params,TUserFunction UserFuncPtr);     //增加一个用户自定义函数
	bool    AddUserFunc(String FuncDef,String Info,TUserFunction UserFuncPtr);     //增加一个用户自定义函数
	void    AddUserIdentWord(String IdentWord); //增加一个用户自定义关键字
	void    SetParserType(int Type);            //0= pascal ,1 = c++
	//事件
	TScrBeforeRunLine     OnBeforeRunLine;  //执行一行脚本命令之前通知
	TScrOnGetVarEvent     OnGetParValue;                              //处理变量实际值时间接口
};

//---------------------------------------------------------------------------
#endif
