#ifndef AccTokenH
#define AccTokenH

//---------------------------------------------------------------------------
#include <Classes.hpp>
class   IAccToken                                           // 标准词法分析器(流式)
{

public:
    int     Type;                                           //分析类型
    long    Value;                                          //值,仅对数值有效
    int     ReadLen;
    String  Text;                                           //符号

public:
    enum
    {
        ENDF    = 0,
        ENDL    = 1,
        KEYWORD = 2,
        IDENT   = 3,
        INTEGER = 4,
        FLOAT   = 5,
        OPERATOR= 6,
        STRING  = 7,
        IERROR  = 8,
        SYSFUNC = 9
    };
    virtual int Read() = 0;
};

class   IParse
{

protected:
    TStream *is;

public:
    TStrings    *OutPutList;                                //编译后代码输出
    String      BeginLabel, EndLabel;
    enum { scrPROGEND = 0, scrLINEEND = 1, scrMODEND = 2, scrERROR = 4 };
    String ErrorInfo;

public:
    IParse()
    {
        is = NULL;
        OutPutList = NULL;
    }

    virtual~IParse()
    { ;
    }

    virtual bool    IsSysFunc(String Opcode) = 0;
    virtual bool    IsIdentWord(String Opcode) = 0;
    virtual bool    IsDefaultSysFunc(String Opcode) = 0;    //是否是默认的系统函数
    virtual bool    IsDefaultIdent(String Opcode) = 0;      //是否是默认的系统关键字
    virtual void    GetSysFuncList(TStrings *SysFuncList) = 0;          //获取系统函数列表
    virtual void    GetSysIdentWordList(TStrings *IndentWordList) = 0;  //获取系统关键字列表
    virtual void    GetUserFuncList(TStrings *SysFuncList) = 0;         //获取用户函数列表
    virtual void    GetUserIdentWordList(TStrings *IndentWordList) = 0; //获取用户关键字列表
    virtual void    SetSysFunc(TStrings *SysFuncList) = 0;              //设置系统函数列表
    virtual void    SetIdentWord(TStrings *IdentWordList) = 0;          //设置系统关键字
    virtual int     GoScript(TStream *Input, TStrings *OutPut) = 0;     //开始编译
    virtual int     ErrorPos() = 0;
};
#endif
