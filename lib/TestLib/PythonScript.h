//---------------------------------------------------------------------------

#ifndef PythonScriptH
#define PythonScriptH
//---------------------------------------------------------------------------
#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

#include <vcl.h>
#include "CommFunc.h"
#include <vector>
#include "AList.h"
#include "AMap.h"
#include "Win32Thunk.h"

using namespace std;

//注意:
//1.一定要定义 : NDEBUG, 不能定义 _DEBUG !  否则编译不过
//2.[重要] 目录名称不能和文件名称相同, 否则Python不会编译(但是在重新编译的时候会编译, 不知道为什么)

//解析方法:
//  const char *msg, * tit;
//  PyArg_ParseTuple(Args, "ss", &tit,&msg);
typedef void    (__closure * TPythonError)(String   Error);

struct      tagModuleDict
{
    PyObject    *   pModule;
    PyObject    *   pDict;
    tagModuleDict()
    {
        pModule = NULL;
        pDict = NULL;
    }
    ~tagModuleDict()
    {
    }
};

size_t	GetStrCRC32(const char * StrKey);

class   CPythonScript
{
private:
    String                  m_ScriptText;
    String                  m_ScriptPath;
    TStringList         *   m_ErrorInfo;
    void                    LogError(String fileName, String err);
    int                     m_iCount;

    bool                    m_EnableRecordStackOnRun;

    typedef     vector<PyMethodDef> TMethodDefList;
    AList<TMethodDefList>           m_FuncMethods;
    TMethodDefList                  *m_CurFuncMethod;

    bool                            CanLoadFromFile(String fileName);

    //注册msg函数
    typedef CAuxCdeclThunk<CPythonScript>  thisThunk;
    thisThunk	m_Thunk;
    typedef PyObject* (* PYTHONFUNC)(PyObject *self, PyObject *args);
    PyObject* __cdecl Python_Alert(DWORD,PyObject *self, PyObject *args);

    AIndexList<tagModuleDict>            m_Dicts;

    //日志记录                                                 
    TStringList         *   m_StackMessage;
    PyObject            *   m_CurTracingFunc;
    PyObject            *   m_CurRunFunc;
    TStringList         *   m_FilterFileName;       //记录日志的时候, 需要过滤的文件
    TStringList         *   m_RunStack;               //脚本运行时记录最近5条消息

    TStringList         *   m_UserOutputLog;        //用户输出日志记录的地点
    bool                    m_bUserOutput;           //是否要输出到用户自定义输出地点

    bool        LoadFromFile(String FileName);
    bool        ReloadFromFile(String FileName);
public:
    CPythonScript();
    ~CPythonScript();

    void                    AddStackMessage(String msg);
    TStringList         *   GetErrorStrings(){return    m_ErrorInfo;}
    TPythonError            fpPythonError;

    void        Init();
    void        SetScriptPath(String    path);
    void        ReloadAll();
    bool        HaveLoadedFile(String FileName);

    TStringList *GetUserOutputLog(){return  m_UserOutputLog;}

    bool        RunString(const String  &srcName, bool enableUserLog = false);

    //注册自定义函数
    void __fastcall AddMethod(const char * lpName, PyCFunction CallEvent, const char * lpDescription = "");
    void        AddNameSpace(const  String &lpNameSpace);

    //运行脚本的一个函数, funcName是脚本的函数名, args 是函数参数列表
    //高效, 推荐使用
    //参数用法:
    //  PyObject *pArgs, *list;
    //  pArgs = Py_BuildValue("(iis)", 1, 2, "three");
    //  list = Py_BuildValue("[iis]", 1, 2, "three");
    //  Py_BuildValue("{s:i,s:i}", "abc", 123, "def", 456)   ------> {'abc': 123, 'def': 456}

    PyObject*   RunFunc(const String &fileName, const String &funcName, PyObject *pArgs = NULL);
    String      GetScriptError();

    //////////////////////////////////////////////////////
    //记录日志
    void        SetTrace(const String &fileName, const String &funcName);
    void        DisableTrace();
    PyObject*   GetCurTraceFunc(){return    m_CurTracingFunc;}
    PyObject*   GetCurRunFunc(){return  m_CurRunFunc;}
    TStringList*GetStackMessage(){return    m_StackMessage;}
    void        AddFilterFileName(String    fileName);
    TStringList *GetFilterFileName(){return  m_FilterFileName;}
    void        AddRunMsg(String    msg);
    TStringList*GetRunStack();
    //Python 调试模式, 打开后, 速度很慢
    void        SetEnableRecordStackOnRun();
    bool        GetEnableRecordStackOnRun(){return      m_EnableRecordStackOnRun;}
    /////////////////////////////////////////////////////
};


CPythonScript       *       GetPythonScript();

#endif
