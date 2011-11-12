//---------------------------------------------------------------------------

#ifndef ThreadManagerH
#define ThreadManagerH
//---------------------------------------------------------------------------
#include    <vcl.h>
#include    <Classes.hpp>
#include    "AList.h"
#include    <SyncObjs.hpp>
#include 	"aqueue.h"

//#include    "WYProfile.h"
//#include    "WYProfileView.h"

enum        TWYThreadState
{
    tsSuspend, tsFree, tsBusy, tsIniting, tsUnIniting, tsTerminate, tsError, tsFinished
};

//线程管理器
//如果 TDefThreadFunc 的返回值为SleepTime
//如果返回0, 会不断转
//如果返回-1, 则关闭这个线程

class SingleThread;
typedef int       (__closure     * TDefThreadFunc)(SingleThread * self);
class   WYThreadEvent;

class   WYThread  : public TThread
{
private:
	bool                            m_IsCOMObj;
protected:
	String                          m_Name;
	TWYThreadState                  m_ThreadState;
	bool							m_CreateSuspended;
	WYThreadEvent	*				m_CreateEvent;
    virtual   void __fastcall Execute(){}

    virtual   void                  Initialize(){}
    virtual   void                  UnInitialize(){}

    //性能统计
//    CThreadProfileManager           m_CProfileManager;

public:
    __fastcall WYThread(bool    CreateSuspened, bool IsCOMObj = false);
	virtual __fastcall ~WYThread();

	TDefThreadFunc      			fpThreadFunc;
	TDefThreadFunc					fpInitFunc;
	TDefThreadFunc					fpUnInitFunc;

    virtual bool                    GetIsCOMObj(){return        m_IsCOMObj;}
    virtual String                  GetName(){return    m_Name;}
    virtual String                  GetStateName();
	virtual TDefThreadFunc          GetThreadFunc(){return  NULL;}
	WYThreadEvent	*               GetCreateEvent(){return m_CreateEvent;}
	TWYThreadState                  GetThreadState(){return	m_ThreadState;}

    //性能统计
//    CThreadProfileManager     *           GetProfileManager(){return  &m_CProfileManager;}
};

//单个线程的类
//使用上要注意 :  TDefThreadFunc 返回值为Sleep的时间
//-1表示退出,  而不是Sleep的 无限等待
class   SingleThread : public WYThread
{
private:

protected:
    virtual   void __fastcall Execute();


public:
	__fastcall SingleThread(bool    CreateSuspened, String  name, TDefThreadFunc  func, bool createCOMObj);
    __fastcall SingleThread(bool    CreateSuspened, String  name);
	__fastcall virtual ~SingleThread();



    virtual   void                  Initialize();
    virtual   void                  UnInitialize();
    virtual   TDefThreadFunc        GetThreadFunc(){return      fpThreadFunc;}
};

//Event对象
class   WYThreadEvent : public TEvent
{
private:
    bool                m_bEnabled;
public:
    WYThreadEvent(Windows::PSecurityAttributes EventAttributes, bool ManualReset, bool InitialState, const AnsiString Name, bool UseCOMWait);
    virtual TWaitResult __fastcall WaitFor(unsigned Timeout);
    void                Enable();
    void                Disable();
    bool                IsEnabled(){return  m_bEnabled;}
};

////////////////////////////////////////////////////////////////
class   UserThread
{
private:
    WYThread    *       m_Thread;
    String              m_ThreadName;
    TDefThreadFunc      m_ThreadFunc;
    bool                m_IsComObj;
public:
    UserThread();
    ~UserThread();

    void                UserCreate(bool    CreateSuspened, String  name, TDefThreadFunc  func, bool createCOMObj = false);
    WYThread    *       GetThread(){return  m_Thread;}
    void                SetThread(WYThread    *thread){m_Thread = thread;}

};

////////////////////////////////////////////////////////////////

//线程管理器
class   ThreadManager
{
private:
	AList<UserThread>        m_Threads;
	AList<WYThreadEvent>     m_Events;
	AThreadNormalQueue<String>	m_Messages;
	bool                     m_bThreadStarted;

	UserThread    *   FindThreadContainerByName(String threadName);
	UserThread    *   FindThreadContainerByID(DWORD threadID);
public:
	ThreadManager();
	~ThreadManager();

	UserThread * 	ManagerCreateThread(String  name, TDefThreadFunc  func, bool createCOMObj = false);

	void            AddThread(WYThread  * thread);

	void            StartAll();
	void            StopAll();
	void            FreeAll();

	WYThread    *   At(int index);
	int             Count(){return  m_Threads.Count();}

	WYThreadEvent*  AddEvent(String name);

	WYThread    *   FindThreadByThreadID(int    threadID);
	WYThread    *   FindThreadByName(String threadName);
	void			ProcessDeletedThread();

	void			AddGUIMessage(String msg);
	bool			PopGUIMessage(String *msg);
    int				GetGUIMessageCount();
};

ThreadManager       *       GetThreadManager();

#ifdef      ENABLE_PROFILE
#define     THREADMANAGER_PROFILE(threadIndex, name) THREAD_PROFILE(GetThreadManager()->At(threadIndex)->GetProfileManager(), name);
#define     SIMPLE_THREADMANAGER_PROFILE(name)  THREAD_PROFILE(GetThreadManager()->FindThreadByThreadID(GetCurrentThreadId())->GetProfileManager(), name);
#else
#define     THREADMANAGER_PROFILE(threadIndex, name)
#define     SIMPLE_THREADMANAGER_PROFILE(name)
#endif      

#endif
