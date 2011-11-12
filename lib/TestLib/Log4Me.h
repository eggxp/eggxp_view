//---------------------------------------------------------------------------

#ifndef Log4MeH
#define Log4MeH
//---------------------------------------------------------------------------
#include    <vcl.h>
#include <iostream>
#include <fstream>
#include <vcl.h>
#include "CommFunc.h"
#include "SingletonEx.h"
#include "Messager.h"
using namespace std;

#define     GEN_GET_SET(TYPE, PAR)         \
    TYPE      Get##PAR()                \
    {                                       \
        return  m_##PAR;                       \
    }                                           \
    void        Set##PAR(TYPE par)   \
    {                                \
        m_##PAR = par;               \
    }

#define     GEN_POINTER_GET(PAR)  \
    PAR    *   Get##PAR()  \
    {   \
        return  &m_##PAR;    \
    }
    

#ifdef _DEBUG
#define ASSERT(x)   WY_ASSERT(x)

#define WY_ASSERT(x)        \
if (!(x))						\
{                               \
	String Info;                \
	Info.sprintf(_TEXT("assert fail: (%s). %s:%s"),#x,__LINE__,__FUNC__); \
    GetLog()->Fatal(Info);              \
	throw Exception(Info,123456);       \
}
#else
#define ASSERT(x)   WY_ASSERT(x)
#define WY_ASSERT(x)
#endif

//****************************************************
//支持Dump调用堆栈
//项目定义宏:  USE_EUREKA_DUMP
//****************************************************

//作用: 写日志文件
//实现方式:singleton模式
//输入:lev--子类级别  log--内容  logLen--内容的长度
//多线程情况下请在项目的头尾增加GetLog和Free

enum        TLogLev
{
    llvDebug = 1, llvInfo, llvWarn, llvError, llvFatal
};

typedef Set<TLogLev, llvDebug, llvFatal>  TLogLvState;


#define     SOURCE_INFO         FormatStr("%s : %d", __FILE__, __LINE__)
#define     LOG_ERROR(s)        GetLog()->Error(FormatStr("%s , info : %s", SOURCE_INFO, s))

class Log4Me
{
    DEFINE_SINGLETONEX(Log4Me)
private:
    CRITICAL_SECTION m_csLock;

    HWND                m_HostWindow;
	String	m_Path;
    String  m_FileName;
	String  GetFileName();
	bool m_bEnableLog;
	ofstream fout;
	void				WriteFile(String str);

	void WriteNormal(String log);
	void OpenFile(String fullName);

	void WarnLog(String log);
	void ErrorLog(String log);

    void DebugLog(String log);
	void InfoLog(String log);
    void FatalLog(String log);

    void MessageWarnLog(int channel, String log);

	bool m_bWritenLog;

    TLogLvState m_LogLev;

    Log4Me();
	~Log4Me();
public:
    void SetFileName(String fileName);
    void DebugOutput(String log, ...);

	void SetEnableLog(bool enAbleLog);
	void SetPath(String path);
	bool HaveLoged(){return m_bWritenLog;}

    /*
    日志记录器（Logger）的行为是分等级的。如下表所示：
    分为
    OFF、FATAL、ERROR、WARN、INFO、DEBUG、ALL 或者您定义的级别。
    Log4j建议只使用四个级别，优先级从高到低分别是ERROR、WARN、INFO、DEBUG。
    通过在这里定义的级别，您可以控制到应用程序中相应级别的日志信息的开关。
    比如在这里定义了INFO级别，则应用程序中所有DEBUG级别的日志信息将不被打印出来
    */
    //DEBUG Level指出细粒度信息事件对调试应用程序是非常有帮助的
    void Debug(String log, ...);
    //INFO level表明 直接输出到GUI。
    void Info(String log, ...);
    //WARN level表明会出现潜在错误的情形。
    void Warn(String log, ...);
    //ERROR level指出虽然发生错误事件，但仍然不影响系统的继续运行。
    void Error(String log, ...);
    //FATAL level指出每个严重的错误事件将会导致应用程序的退出。
    void Fatal(String log, ...);

    void SetLogLev(TLogLvState  lvState);

    //////////////////////////////////用Windows Message的方式写日志
    void                SetGUIWindow(HWND   hwnd);
    //输出
    void                MessageWarn(int channel, String log, ...);
};

Log4Me	*	GetLog();

#endif
