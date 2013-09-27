//---------------------------------------------------------------------------
#pragma hdrstop


#ifdef      USE_EUREKA_DUMP
#include "ExceptionLog.hpp"
#endif

#include "Log4Me.h"


//---------------------------------------------------------------------------

#pragma package(smart_init)

//----------------------------------------------------------------------
IMPLEMENT_SINGLETON(Log4Me)
//----------------------------------------------------------------------

Log4Me	*	GetLog()
{
    return Log4Me::GetInstance();
}


/////////////////////////////////////////////////////////////
#define     DO_LOG(func)        if(!m_bEnableLog)                        \
                            		return;                              \
                                                                         \
                                EnterCriticalSection(&m_csLock);       \
                                String  StrInfo;                         \
                                va_list vaArgs;                          \
                                va_start(vaArgs, log);                   \
                                if (log.c_str())                         \
                                {                                        \
                                    StrInfo.vprintf(log.c_str(), vaArgs);\
                                    m_bWritenLog = true;                 \
                                    func(StrInfo.c_str());               \
                                }                                        \
                                va_end(vaArgs);                          \
                                LeaveCriticalSection(&m_csLock);

#define     OUTPUT_STACK        try{                                                      \
                                TEurekaStackList * curStack = GetCurrentCallStack();	\
                                auto_ptr<TStringList>      outputList(new TStringList);\
								CallStackToStrings(curStack, outputList.get());        \
								curStack->Free();										\
                                for(int i=0; i<outputList->Count; i++)                 \
                                {                                                      \
									WriteFile(outputList->Strings[i]);					\
									WriteFile("\r\n");							        \
                                }                                                      \
                                }                                                      \
                                catch(Exception &e)                                    \
                                {                                                      \
                                }
/////////////////////////////////////////////////////////////


Log4Me::Log4Me()
{
	m_LogLev<<llvDebug<<llvInfo<<llvWarn<<llvError<<llvFatal;

    m_HostWindow = NULL;
    InitializeCriticalSection(&m_csLock);
	m_bWritenLog = false;

    #ifdef _DEBUG
        m_bEnableLog = true;
    #else
        m_bEnableLog = false;
    #endif

    if(m_bEnableLog)
    {
        //人物登录
		String fullName = GetFileName();
		OpenFile(fullName);
	}
}

void Log4Me::OpenFile(String fullName)
{
//	if(!FileExists(fullName))
//	{
//		return;
//	}
	fout.open(fullName.c_str(), ios_base::trunc | ios_base::out | ios_base::binary);

	#if defined(_DELPHI_STRING_UNICODE)
	wchar_t BOM = 0xFEFF;//Byte Order Mark character
	fout.write((char *)&BOM, 2);		//unicode
	#endif

	fout.flush();
}

void				Log4Me::WriteFile(String str)
{
	#if defined(_DELPHI_STRING_UNICODE)
	fout.write((char *)str.c_str(), str.Length() * 2);
	#else
	fout.write(str.c_str(), str.Length());
	#endif

	fout.flush();
}

Log4Me::~Log4Me(void)
{
    EnterCriticalSection(&m_csLock);
	if(m_bEnableLog)
	{
        if(fout.is_open())
    		fout.close();
	}
    LeaveCriticalSection(&m_csLock);
    DeleteCriticalSection(&m_csLock);
}

String      Log4Me::GetFileName()
{
    if(m_Path == "")
		m_Path = ExtractFilePath(Application->ExeName);

	if(m_FileName == "")
		return  m_Path + ExtractFileName(Application->ExeName) + "_Log.txt";
    else
        return  m_Path + m_FileName;
}

//----------------------------------------------------------------------

void Log4Me::SetFileName(String fileName)
{
    m_FileName = fileName;
    if(m_bEnableLog)
    {
        fout.close();
		OpenFile(m_FileName);
    }
}

//----------------------------------------------------------------------

void Log4Me::DebugOutput(String log, ...)
{
    DO_LOG(DebugOutput);
}

void Log4Me::WarnLog(String log)
{
	WriteFile("warn:");
	WriteNormal(log.c_str());
}

void Log4Me::ErrorLog(String log)
{
	WriteFile("ERROR :");
	WriteNormal(log);
}

void Log4Me::SetPath(String path)
{
	if(!DirectoryExists(path))
	{
        ForceDirectories(path);
	}
	m_Path = path;
}

void Log4Me::WriteNormal(String log)
{
	String time = DateTimeToStr(Now());
	String outStr;
	String formatStr = "(%s)\t%d\t:";         // Unicode
	outStr = outStr.sprintf(formatStr.c_str(), time, GetCurrentThreadId());
	WriteFile(outStr);
	WriteFile(log);
	WriteFile("\r\n");
}

//----------------------------------------------------------------------

void Log4Me::SetEnableLog(bool enAbleLog)
{
	m_bEnableLog = enAbleLog;
}

void Log4Me::DebugLog(String log)
{
    WriteFile("Debug:");
	WriteNormal(log.c_str());
}

void Log4Me::InfoLog(String log)
{
    MessageWarn(1, log);
    WriteFile("Info:");
	WriteNormal(log.c_str());
}

void Log4Me::FatalLog(String log)
{
    WriteFile("Fatal:");
	WriteNormal(log.c_str());
}

//DEBUG Level指出细粒度信息事件对调试应用程序是非常有帮助的
void Log4Me::Debug(String log, ...)
{
    if(!m_LogLev.Contains(llvDebug))
        return;
    DO_LOG(DebugLog);

//    #ifdef      USE_EUREKA_DUMP
//    OUTPUT_STACK
//    #endif
}

//INFO level表明 消息在粗粒度级别上突出强调应用程序的运行过程。
void Log4Me::Info(String log, ...)
{
    if(!m_LogLev.Contains(llvInfo))
        return;
    DO_LOG(InfoLog);
}

//WARN level表明会出现潜在错误的情形。
void Log4Me::Warn(String log, ...)
{
    if(!m_LogLev.Contains(llvWarn))
        return;
    
    DO_LOG(WarnLog);
}

//ERROR level指出虽然发生错误事件，但仍然不影响系统的继续运行。
void Log4Me::Error(String log, ...)
{
    //导出堆栈
    if(!m_LogLev.Contains(llvError))
        return;

    DO_LOG(ErrorLog);

//    #ifdef      USE_EUREKA_DUMP
//    OUTPUT_STACK
//    #endif
}

//FATAL level指出每个严重的错误事件将会导致应用程序的退出。
void Log4Me::Fatal(String log, ...)
{
    if(!m_LogLev.Contains(llvFatal))
        return;

    DO_LOG(FatalLog);
//    #ifdef      USE_EUREKA_DUMP
//    OUTPUT_STACK
//    #endif
}

void Log4Me::SetLogLev(TLogLvState  lvState)
{
    m_LogLev = lvState;
}


//////////////////////////////////用Windows Message的方式写日志
void                Log4Me::SetGUIWindow(HWND   hwnd)
{
	TCHAR pwindowClassName[255];
    int result = GetClassName(hwnd, pwindowClassName, sizeof(pwindowClassName) / sizeof(TCHAR));
    if(!result)
    {
        Warn("Log4Me::SetGUIWindow, GetClassName error = %s",
                        SysErrorMessage(GetLastError()));
        return;
    }

    m_HostWindow = FindWindow(pwindowClassName,NULL);
}

void                Log4Me::MessageWarnLog(int channel, String log)
{
    String time = DateTimeToStr(Now());
	String outStr;
	String formatStr = "( %s ) : %s";
	outStr = outStr.sprintf(formatStr.c_str(), time, log);

    if(m_HostWindow)
	{
		String cpStr = outStr;
        COPYDATASTRUCT SendData;
        SendData.dwData = channel;
		SendData.cbData = cpStr.Length() * sizeof(TCHAR);
        SendData.lpData = cpStr.c_str();
        SendMessage(m_HostWindow,WM_COPYDATA,0,LPARAM(&SendData));
    }

}

//输出
void                Log4Me::MessageWarn(int channel, String log, ...)
{
    EnterCriticalSection(&m_csLock);
	String  StrInfo;
	va_list vaArgs;
	va_start(vaArgs, log);
	if (log.c_str())
	{
		StrInfo.vprintf(log.c_str(), vaArgs);
		MessageWarnLog(channel, StrInfo);
	}
	va_end(vaArgs);
    LeaveCriticalSection(&m_csLock);
}
