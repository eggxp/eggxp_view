//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#ifndef cppparseH
#define cppparseH

//---------------------------------------------------------------------------
#include "AccToken.h"
class ICppToken :
    public IAccToken                                            // Pascal式词法分析器
{

protected:
    TStream     *is;                                            //脚本源代码输入流
    TStringList *KeyWord;                                       //关键字列表
    char        OPWord[20];                                     //操作符,运算符表
    char        ch;
    int         getnc();                                        //读取一个字节并将流指针下移

public:
    int         Line;                                           //当前行号
    TStringList *SysIdent;                                      //系统保留标识符列表
    TStringList *SysFunc;                                       //系统函数列表
    ICppToken();
    ~ICppToken();
    void    ReadBack();
    bool    IsOperator(char chr);                               //是否是操作符,运算符
    void Start(TStream *input)
    {
        is = input;
        ch = 0;
        Line = 1;
        Type = ENDL;
    }                                                           //初始化

    int Read();                                                 //读取并分析一个单词或符号
};

class ICppScript :
    public IParse                                               // 类Pascal脚本编译器类,从输入流编译类Pascal源程序
{

protected:
    ICppToken   Token;                                          //Pascal式词法分析器
    int         LABEL_ID;                                       //生成的标号ID;
    int         ParseExpression(String ElseLabel, String EndIfLabel,
                                String MainIfLabel);            // 生成分析表达式的代码
    int         ParseScript();                                  // 单条指令
    int         ParseLine();                                    // 单行指令
    int         ParseStatement();                               // 一段指令
    int         ParseProgram();                                 // 一个脚本程序
    int         MakeGoto();                                     /* 处理跳转部分	*/
    int         MakeIf();                                       /* 条件判断部分 */
    int         MakeWhile();                                    /* 循环模块实现 */
    int         MakeValue();                                    //处理系统表示符
    int         MakeSysFunc();                                  //处理系统函数
    String      MakeExpress(String OperatorType);
    String      MakeNotExpress(String OperatorType);
    String      Express2KeyWord(String ExpStr);
    int         OptimizeCode();                                 //优化生成的伪代码  未完成
    int         OptimizeLabel(String LabelStr);                 //未完成
    void        SplitStr(AnsiString SrcStr, AnsiString SplitChar,
                         TStringList *Str);
    String      GenLabelId();

public:
    ICppScript();
    ~ICppScript();
    TStrings    *OutPutList;                                    //编译后代码输出
    bool        IsSysFunc(String Opcode);
    bool        IsIdentWord(String Opcode);
    bool        IsDefaultSysFunc(String Opcode);                //是否是默认的系统函数
    bool        IsDefaultIdent(String Opcode);                  //是否是默认的系统关键字
    void        GetSysFuncList(TStrings *SysFuncList);          //获取系统函数列表
    void        GetSysIdentWordList(TStrings *IndentWordList);  //获取系统关键字列表
    void        GetUserFuncList(TStrings *SysFuncList);         //获取用户函数列表
    void        GetUserIdentWordList(TStrings *IndentWordList); //获取用户关键字列表
    void        SetSysFunc(TStrings *SysFuncList);              //设置系统函数列表
	void        SetIdentWord(TStrings *IdentWordList);          //设置系统关键字
	void        AddUserFunc(String FuncName);     //增加一个用户自定义函数
	void        AddUserIdentWord(String IdentWord); //增加一个用户自定义关键字
    int         GoScript(TStream *Input, TStrings *OutPut);     //开始编译
    int ErrorPos()
    {
        return Token.ReadLen;
    }
};
#endif

