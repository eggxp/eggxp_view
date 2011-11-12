//---------------------------------------------------------------------------
#pragma hdrstop

#include "cppparse.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
static char *SysIdentWord[] = { "NULL", "TRUE", "FALSE", 0 };
static char *SysFuncWord[] = { "EXIT", "RESTART", "CALL", "RET", 0 };
ICppToken::ICppToken()
{
    static char *keyword[] =
        {
            "GOTO",
            "IF",
            "THEN",
            "ELSE",
            "MOD",
            "DO",
            "FUNCTION",
            "PROCEDURE",
            "WHILE",
            0
        };
    static char opword[] =
        {
            '+',
            '-',
            '*',
            '/',
            '>',
            '=',
            '<',
            '(',
            ')',
            ',',
            '!',
            '{',
            '}',
            '&',
            '|',
            0
        };
    KeyWord = new TStringList();
    SysIdent = new TStringList();
    SysFunc = new TStringList();

    int i;
    for(i = 0; keyword[i]; i++)
    {
        KeyWord->Add(keyword[i]);
    }

    for(i = 0; SysIdentWord[i]; i++)
    {
        SysIdent->Add(SysIdentWord[i]);
    }

    for(i = 0; SysFuncWord[i]; i++)
    {
        SysFunc->Add(SysFuncWord[i]);
    }

    for(i = 0; opword[i]; i++)
    {
        OPWord[i] = opword[i];
    }

    OPWord[i] = 0;
    is = NULL;
}

//---------------------------------------------------------------------------
ICppToken::~ICppToken()
{
    delete KeyWord;
    delete SysIdent;
    delete SysFunc;
}

//---------------------------------------------------------------------------
bool ICppToken::IsOperator(char chr)
{
    for(int i = 0; OPWord[i]; i++)
    {
        if(chr == OPWord[i] && chr != 0)
            return true;
    }

    return false;
}

//---------------------------------------------------------------------------
int ICppToken::getnc()  //读取一个字节并将流指针下移
{
    if(!is)
    {
        ch = -1;
        return 0;
    }

    if(is->Position >= is->Size)
    {
        ch = -1;
        return 0;
    }

    is->Read(&ch, sizeof(ch));
    ch = toupper(ch);
    ReadLen++;
    if(ch < -1 && ch > -128)
        ch = 256 + ch;
    return 1;
}

//---------------------------------------------------------------------------
void ICppToken::ReadBack()
{
    is->Position -= (ReadLen + 1);
    getnc();
}

//----------------------------------------------------------------------------
int ICppToken::Read()   //读取，并分析语法
{
    Text = "";
    ReadLen = 0;
    while((ch == ' ' || ch == '\t' || ch == 0) && ch >= 0)
    {
        getnc();                                // 除去空格
    }

    if(ch == '/' || ch == '\\')                 //注释
    {                                           // 除去注释
        getnc();
        while(ch != '\n' && ch != '\r')
        {
            getnc();
        }
    }

    if(ch == '\n' || ch == '\r' || ch == ';')   //处理回车换行符
    {
        while(ch == '\n' || ch == '\r' || ch == ';')
        {
            getnc();
        }

        Type = ENDL;
        Value = 0;
        Line++;
        return 1;
    }

    if(ch == -1)                                //程序段结束
    {                                           // 流结束
        Type = ENDF;
        Value = -1;
        Text = "--EOF--";
        return 0;
    }

    //  if ( ch=='{' || ch=='}')
    //  {
    //        Type = KEYWORD;
    //        Text = ch;
    //        getnc();
    //        return 1;
    //  }
    //  if (ch == '&' || ch == '|')
    //  {
    //        Type = KEYWORD;
    //        Text = ch;
    //        getnc();
    //        Text = Text+ch;
    //         getnc();
    //        return 1;
    //  }
    if(ch == '_' || isalpha(ch))                // 识别符和关键字
    {
        while(ch == '_' || isalpha(ch) || isalnum(ch))
        {
            Text += ch;
            getnc();
        }

        //关键字
        Text = UpperCase(Text);
        for(int j = 0; j < KeyWord->Count; j++)
        {
            if(Text == KeyWord->Strings[j])
            {
                Type = KEYWORD;
                Value = j;
                return 1;
            }
        }

        //系统标识符
        for(int j = 0; j < SysIdent->Count; j++)
        {
            if(Text == SysIdent->Strings[j])
            {
                Type = IDENT;
                Value = j;
                return 1;
            }
        }

        //系统接口函数
        for(int j = 0; j < SysFunc->Count; j++)
        {
            if(Text == SysFunc->Strings[j])
            {
                Type = SYSFUNC;
                Value = j;
                return 1;
            }
        }

        //无法识别的字符串
        Type = IERROR;
        Value = 0;
        return 1;
    }

    if(isalnum(ch))
    {                                           // 整数，浮点
        while(isalnum(ch))
        {
            Text += ch;
            getnc();
        }

        Value = StrToInt(Text);
        Type = INTEGER;
        return 1;
    }

    if(ch == '"')
    {                                           // 如果是字串
        getnc();
        while(ch != '\n' && ch != '\r' && ch != '"')
        {
            Text += ch;
            getnc();
        }

        if(ch == '"')
            getnc();
        Type = STRING;
        Value = 0;
        return 1;
    }

    if(IsOperator(ch))                          //操作符
    {
        while(IsOperator(ch))
        {
            Text += ch;
            getnc();
        }

        Type = OPERATOR;
        Value = 0;
        return 1;
    }

    //无法识别的字符
    Type = IERROR;
    Value = 0;
    getnc();
    return 1;
}

//---------------------------------------------------------------------------
ICppScript::ICppScript()
{}

//---------------------------------------------------------------------------
ICppScript::~ICppScript()
{}

//---------------------------------------------------------------------------
int ICppScript::GoScript(TStream *Input, TStrings *OutPut)
{
    if(!Input)
        return -1;
    is = Input;
    is->Position = 0;
    if(!OutPut)
        return -1;
    OutPutList = OutPut;
    Token.Start(is);
    OutPutList->Clear();
    LABEL_ID = 0;
    Token.Read();
    return ParseProgram();
}

//---------------------------------------------------------------------------
int ICppScript::ParseProgram()
{
    int i;
    BeginLabel = "ScriptStart";
    EndLabel = "ScriptEnd";
    OutPutList->Add(BeginLabel + ":");
    i = ParseStatement();
    if(i == scrERROR)
        return 0;
    OutPutList->Add(EndLabel + ":");
    return 1;
}

//---------------------------------------------------------------------------
int ICppScript::ParseStatement()
{
    if(Token.Type == IAccToken::ENDF)
        return scrPROGEND;

    int ReturnCode = ParseLine();
    if(ReturnCode == scrMODEND)
    {
        return scrMODEND;   // 如果模块结束
    }

    if(ReturnCode == scrPROGEND)
        return scrPROGEND;  // 如果程序结束
    if(ReturnCode == scrERROR)
    {                       //如果模块有错
        ErrorInfo.sprintf("ERROR FIND IN LINE %d ,Pos %d \n",
                          Token.Line,
                          Token.ReadLen);
        return scrERROR;
    }

    if(Token.Type == IAccToken::ENDL)
    {
        Token.Read();
        return ParseStatement();
    }

    return scrERROR;
}

//---------------------------------------------------------------------------
int ICppScript::ParseLine()
{
    if(Token.Type == IAccToken::ENDF)
        return scrPROGEND;
    if(Token.Type == IAccToken::ENDL)
        return scrLINEEND;

    int r = ParseScript();
    if(r == scrMODEND)
    {
        return scrMODEND;   // 模块结束
    }

    if(r == scrERROR)
        return scrERROR;    // 错误
    if(r == scrLINEEND)
    {
        Token.Read();
        return ParseLine();
    }

    if(r == scrMODEND)
        return scrPROGEND;
    ErrorInfo.sprintf("Operator : not find but find Line: %d Text:%s Pos:%d \n",
                      Token.Line,
                      Token.Text,
                      Token.ReadLen);
    return scrERROR;
}

//---------------------------------------------------------------------------
int ICppScript::ParseScript()
{
    if(Token.Type == IAccToken::OPERATOR)
    {
        if(Token.Text == UpperCase("}"))
        {
            return scrMODEND;
        }
        else if(Token.Text == UpperCase("{"))
        {
            Token.Read();
            return ParseStatement();
        }
    }

    if(Token.Type == IAccToken::KEYWORD)    // 第一个字符为关键字
    {
        if(Token.Text == UpperCase("goto"))
        {
            if(!MakeGoto())
                return scrERROR;
        }
        else if(Token.Text == UpperCase("if"))
        {
            if(!MakeIf())
                return scrERROR;
        }
        else if(Token.Text == UpperCase("while"))
        {
            if(!MakeWhile())
                return scrMODEND;
        }
        else if(Token.Text == UpperCase("else"))
        {
            return scrMODEND;
        }
    }
    else if(Token.Type == IAccToken::IDENT) // 第一个字符为识别符
    {
        if(!MakeValue())
            return scrERROR;
    }
    else if(Token.Type == IAccToken::SYSFUNC)
    {
        if(!MakeSysFunc())
            return scrERROR;
    }
    else if(Token.Type == IAccToken::ENDL)
    {
        return scrLINEEND;
    }
    else
    {
        ErrorInfo.sprintf("Unknow command %s ,Line: %d,Pos %d \n",
                          Token.Text,
                          Token.Line,
                          Token.ReadLen);
        return scrERROR;
    }

    return scrLINEEND;
}

//---------------------------------------------------------------------------
bool ICppScript::IsSysFunc(String Opcode)
{
    return (Token.SysFunc->IndexOf(Opcode.UpperCase()) != -1);
}

//---------------------------------------------------------------------------
bool ICppScript::IsIdentWord(String Opcode)
{
    return (Token.SysIdent->IndexOf(Opcode.UpperCase()) != -1);
}

//---------------------------------------------------------------------------
bool ICppScript::IsDefaultSysFunc(String Opcode)
{
    for(int i = 0; SysFuncWord[i]; i++)
    {
        if(Opcode == SysFuncWord[i])
            return true;
    }

    return false;
}

//---------------------------------------------------------------------------
bool ICppScript::IsDefaultIdent(String Opcode)
{
    for(int i = 0; SysIdentWord[i]; i++)
    {
        if(Opcode == SysIdentWord[i])
            return true;
    }

    return false;
}

//---------------------------------------------------------------------------
void ICppScript::GetSysFuncList(TStrings *SysFuncList)
{
    SysFuncList->Clear();
    for(int i = 0; SysFuncWord[i]; i++)
    {
        SysFuncList->Add(SysFuncWord[i]);
    }
}

//---------------------------------------------------------------------------
void ICppScript::GetSysIdentWordList(TStrings *IndentWordList)
{
    IndentWordList->Clear();
    for(int i = 0; SysIdentWord[i]; i++)
    {
        IndentWordList->Add(SysIdentWord[i]);
    }
}

//---------------------------------------------------------------------------
void ICppScript::GetUserFuncList(TStrings *SysFuncList)
{
    SysFuncList->Clear();
    for(int i = 0; i < Token.SysFunc->Count; i++)
    {
        if(!IsDefaultSysFunc(Token.SysFunc->Strings[i]))
            SysFuncList->Add(Token.SysFunc->Strings[i]);
    }
}

//---------------------------------------------------------------------------
void ICppScript::GetUserIdentWordList(TStrings *IndentWordList)
{
    IndentWordList->Clear();
    for(int i = 0; i < Token.SysIdent->Count; i++)
    {
        if(!IsDefaultIdent(Token.SysIdent->Strings[i]))
            IndentWordList->Add(Token.SysIdent->Strings[i]);
    }
}

//---------------------------------------------------------------------------
void ICppScript::SetSysFunc(TStrings *SysFuncList)
{

    //设置系统函数列表
    for(int i = 0; i < SysFuncList->Count; i++)
    {
        if(Token.SysFunc->IndexOf(SysFuncList->Strings[i]) < 0)
            Token.SysFunc->Add(SysFuncList->Strings[i]);
    }
}

//---------------------------------------------------------------------------
void ICppScript::SetIdentWord(TStrings *IdentWordList)
{
    for(int i = 0; i < IdentWordList->Count; i++)
    {
        if(Token.SysIdent->IndexOf(IdentWordList->Strings[i]) < 0)
            Token.SysIdent->Add(IdentWordList->Strings[i]);
    }

    //添加用户自定义系统关键字,变量
}

//---------------------------------------------------------------------------
int ICppScript::MakeSysFunc()
{
    String  MakeText = "";
    MakeText = Token.Text + " ";
    Token.Read();
    if(Token.Type != IAccToken::OPERATOR || Token.Text != "(")
    {
        ErrorInfo.sprintf("错误的函数调用格式:%s,Ln=%d,Pos=%d",
                          Token.Text,
                          Token.Line,
                          Token.ReadLen);
        return scrERROR;
    }

    while(Token.Text != ")")
    {
        Token.Read();
        if(Token.Type == IAccToken::STRING)
        {
            MakeText = MakeText + "\"" + Token.Text + "\"";
        }
        else if(Token.Type == IAccToken::INTEGER)
        {
            MakeText += Token.Text;
        }
        else
        {
            ErrorInfo.sprintf("错误的函数调用格式:%s,Ln=%d,Pos=%d",
                              Token.Text,
                              Token.Line,
                              Token.ReadLen);
            return scrERROR;
        }

        Token.Read();
        if(Token.Type == IAccToken::OPERATOR)
        {
            if(Token.Text == ",")
                MakeText += ",";
            else if(Token.Text == ")")
                break;
            else
            {
                ErrorInfo.sprintf("错误的函数调用格式:%s,Ln=%d,Pos=%d",
                                  Token.Text,
                                  Token.Line,
                                  Token.ReadLen);
                return scrERROR;
            }
        }
        else
        {
            ErrorInfo.sprintf("错误的函数调用格式:%s,Ln=%d,Pos=%d",
                              Token.Text,
                              Token.Line,
                              Token.ReadLen);
            return scrERROR;
        }

    }

    OutPutList->Add(MakeText);
    return scrLINEEND;
}

//---------------------------------------------------------------------------
String ICppScript::MakeExpress(String OperatorType)
{
    if(OperatorType == "==")
    {
        return "JE";
    }
    else if(OperatorType == ">")
    {
        return "JA";
    }
    else if(OperatorType == "<")
    {
        return "JB";
    }
    else if(OperatorType == ">=")
    {
        return "JAE";
    }
    else if(OperatorType == "<=")
    {
        return "JBE";
    }
    else if(OperatorType == "!=")
    {
        return "JNE";
    }
    else
    {
        return "";
    }
}

//-----------------------------------------------------------------------------
String ICppScript::MakeNotExpress(String OperatorType)
{
    if(OperatorType == "==")
    {
        return "JNE";
    }
    else if(OperatorType == ">")
    {
        return "JBE";
    }
    else if(OperatorType == "<")
    {
        return "JAE";
    }
    else if(OperatorType == ">=")
    {
        return "JB";
    }
    else if(OperatorType == "<=")
    {
        return "JA";
    }
    else if(OperatorType == "!=")
    {
        return "JE";
    }
    else
    {
        return "";
    }
}

//------------------------------------------------------------------------------
String ICppScript::Express2KeyWord(String ExpStr)
{
    if(ExpStr == "JE")
    {
        return "==";
    }
    else if(ExpStr == "JA")
    {
        return ">";
    }
    else if(ExpStr == "JB")
    {
        return "<";
    }
    else if(ExpStr == "JAE")
    {
        return ">=";
    }
    else if(ExpStr == "JBE")
    {
        return "<=";
    }
    else if(ExpStr == "JNE")
    {
        return "!=";
    }
    else
    {
        return "";
    }
}

//---------------------------------------------------------------------------
int ICppScript::MakeGoto()
{
    return scrLINEEND;
}

//---------------------------------------------------------------------------
int ICppScript::MakeIf()
{
    String  ElseLabel, EndIfLabel, MainIfLabel;
    ElseLabel = GenLabelId();
    MainIfLabel = GenLabelId();
    EndIfLabel = GenLabelId();
    Token.Read();
    if(Token.Text != "(")
    {
        ErrorInfo = "if 语句缺少 (";
        return scrERROR;
    }

    Token.Read();
    if(ParseExpression(ElseLabel, EndIfLabel, MainIfLabel) == 0)
    {
        return 0;
    }

    Token.Read();
    if(Token.Type == IAccToken::ENDL)
    {
        if(ParseStatement() == scrERROR)
            return scrERROR;
        Token.Read();
    }
    else
    {
        if(ParseLine() == scrERROR)
            return scrERROR;
    }

    Token.Read();
    OutPutList->Add("JMP " + EndIfLabel);
    OutPutList->Add(ElseLabel + ":   ;ELSE");
    if(Token.Type == IAccToken::KEYWORD && Token.Text == "ELSE")
    {
        Token.Read();
        if(Token.Type == IAccToken::ENDL)
        {
            if(ParseStatement() == scrERROR)
                return scrERROR;
        }
        else
        {
            if(ParseLine() == scrERROR)
                return scrERROR;
        }

        OutPutList->Add(EndIfLabel + ":   ;ENDIF");
    }
    else
    {
        OutPutList->Add(EndIfLabel + ":   ;ENDIF");
        Token.ReadBack();
    }

    return 1;
}

//---------------------------------------------------------------------------
int ICppScript::MakeWhile()
{
    String  WhileStart, ElseLabel, EndIfLabel, MainIfLabel;
    WhileStart = GenLabelId();
    MainIfLabel = GenLabelId();
    EndIfLabel = GenLabelId();
    ElseLabel = EndIfLabel;
    Token.Read();
    if(Token.Text != "(")
    {
        ErrorInfo = "while 语句缺少 (";
        return scrERROR;
    }

    Token.Read();
    OutPutList->Add(WhileStart + ":   ;Start While");
    if(ParseExpression(ElseLabel, EndIfLabel, MainIfLabel) == 0)
    {
        return 0;
    }

    Token.Read();
    if(Token.Type == IAccToken::ENDL)
    {
        if(ParseStatement() == scrERROR)
            return scrERROR;
        Token.Read();
    }
    else
    {
        if(ParseLine() == scrERROR)
            return scrERROR;
    }

    OutPutList->Add("JMP " + WhileStart);
    OutPutList->Add(EndIfLabel + ":   ;END WHILE");
    return 1;
}

//---------------------------------------------------------------------------
int ICppScript::MakeValue()
{
    return scrLINEEND;
}

//---------------------------------------------------------------------------
int ICppScript::ParseExpression(String ElseLabel, String EndIfLabel,
                                String MainIfLabel)
{
    String  TmpOp, LeftValue, RightValue;
    while(1)
    {
        if(Token.Type == IAccToken::ENDL)
        {
            ErrorInfo = "条件语句缺少 )";
            return 0;
        }

        if(Token.Type != IAccToken::STRING && Token.Type != IAccToken::INTEGER &&
                Token.Type != IAccToken::IDENT)
        {
            ErrorInfo.sprintf("条件语句解析错误!条件表达式左值非法, %s",
                              Token.Text);
            return 0;
        }

        LeftValue = Token.Text;
        Token.Read();
        if(Token.Type != IAccToken::OPERATOR)
        {
            ErrorInfo = "条件语句解析错误!条件表达式比较操作符非法";
            return 0;
        }

        TmpOp = Token.Text;
        if(TmpOp.Length() < 1 || TmpOp == "")
        {
            ErrorInfo = "条件语句解析错误!条件表达式比较操作符符号未知";
            return 0;
        }

        Token.Read();
        if(Token.Type != IAccToken::STRING && Token.Type != IAccToken::INTEGER &&
                Token.Type != IAccToken::IDENT)
        {
            ErrorInfo = "条件语句解析错误!条件表达式右值非法";
            return 0;
        }

        RightValue = Token.Text;
        OutPutList->Add("CMP " + LeftValue + "," + RightValue);
        Token.Read();
        if(Token.Text == ")")
        {
            TmpOp = MakeNotExpress(TmpOp);
            OutPutList->Add(TmpOp +
                            " " +
                            ElseLabel +
                            "   ;Goto Else IF " +
                            Express2KeyWord(TmpOp));
            OutPutList->Add(MainIfLabel + ":   ;IFMAIN");
            return 1;
        }

        if(Token.Type == IAccToken::OPERATOR)
        {
            if(Token.Text == "&&")
            {
                TmpOp = MakeNotExpress(TmpOp);
                OutPutList->Add(TmpOp +
                                " " +
                                ElseLabel +
                                "   ;Goto Else IF " +
                                Express2KeyWord(TmpOp));
                Token.Read();
            }
            else if(Token.Text == "||")
            {
                TmpOp = MakeExpress(TmpOp);
                OutPutList->Add(TmpOp +
                                " " +
                                MainIfLabel +
                                "   ;Goto Else IF " +
                                Express2KeyWord(TmpOp));
                Token.Read();
            }
            else if(Token.Text == "!")
            {
                TmpOp = MakeExpress(TmpOp);
                OutPutList->Add(TmpOp +
                                " " +
                                ElseLabel +
                                "   ;Goto Else IF " +
                                Express2KeyWord(TmpOp));
                Token.Read();
            }
        }
    }
}

//------------------------------------------------------------------------------
int ICppScript::OptimizeCode()
{
    int i;
    for(i = 0; i < LABEL_ID; i++)
    {
        OptimizeLabel(Format("LABEL_%d", ARRAYOFCONST((i))));
    }

    return 1;
}

//-------------↓↓↓↓分割字符串↓↓↓↓----------------------------------
void ICppScript::SplitStr(AnsiString SrcStr, AnsiString SplitChar,
                          TStringList *Str)
{
    int i, j;
    Str->Clear();
    j = SplitChar.Length();
    i = SrcStr.Pos(SplitChar);
    while(i > 0)
    {
        Str->Add(SrcStr.SubString(1, i - 1));
        SrcStr.Delete(1, i + j - 1);
        i = SrcStr.Pos(SplitChar);
    }

    Str->Add(SrcStr);
}

//------------------------------------------------------------------------------
String ICppScript::GenLabelId()
{
    String  ReturnStr;
    ReturnStr = Format("LABEL_%d", ARRAYOFCONST((LABEL_ID)));
    LABEL_ID++;
    return ReturnStr;
}

//------------------------------------------------------------------------------
int ICppScript::OptimizeLabel(String LabelStr)
{
    int     LabelPos;
    String  tmpStr;
    LabelPos = -1;
    for(int i = 0; i < OutPutList->Count; i++)
    {
        tmpStr = OutPutList->Strings[i];
        if(tmpStr.Pos(LabelStr + ":") > 0)
            LabelPos = i;
    }

    return LabelPos;
}
//---------------------------------------------------------------------------
void ICppScript::AddUserFunc(String FuncName)
{

    //设置系统函数列表
    if(Token.SysFunc->IndexOf(FuncName) < 0)
        Token.SysFunc->Add(FuncName);
}
//---------------------------------------------------------------------------
void ICppScript::AddUserIdentWord(String IdentWord)
{
    if(Token.SysIdent->IndexOf(IdentWord) < 0)
        Token.SysIdent->Add(IdentWord);
}
