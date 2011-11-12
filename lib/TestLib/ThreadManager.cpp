//---------------------------------------------------------------------------


#pragma hdrstop

#include "ThreadManager.h"
#include "Log4Me.h"
#include "CommPlus.h"
#include <objbase.h>

//---------------------------------------------------------------------------

#pragma package(smart_init)

static      ThreadManager       gThreadManager;

ThreadManager   *   GetThreadManager()
{
    return  &gThreadManager;
}

//***************************************************////////////
__fastcall WYThread::WYThread(bool    CreateSuspened, bool IsCOMObj) : TThread(false)
{
	fpInitFunc = NULL;
	fpUnInitFunc = NULL;
    fpThreadFunc = NULL;
	m_CreateSuspended = CreateSuspened;
	m_CreateEvent = GetThreadManager()->AddEvent(FormatStr("Create_%p", this));
    m_IsCOMObj = IsCOMObj;
    if(m_IsCOMObj)
    {
        CoInitializeEx(NULL, COINIT_MULTITHREADED);
    } 
}

__fastcall WYThread::~WYThread()
{
    if(m_IsCOMObj)
    {
        CoUninitialize();
    }
}

String     WYThread::GetStateName()
{
    switch(m_ThreadState)
    {
        case    tsSuspend:
            return  "Suspended";
        case    tsFree:
            return  "Not Busy :)";
        case    tsBusy:
            return  "Busy";
        case    tsTerminate:
            return  "Terminate!";
        case    tsError:
            return  "Exception Error";
        case    tsIniting:
            return  "Initing..";
        case    tsUnIniting:
			return  "UnIniting...";
		case	tsFinished:
			return 	"Finished";
    }
    return  "WYThread UnDefined State";
}
//***************************************************////////////
__fastcall  SingleThread::SingleThread(bool    CreateSuspened, String  name, TDefThreadFunc  func, bool createCOMObj): WYThread(CreateSuspened, createCOMObj)
{
	fpThreadFunc = func;
    m_Name = name;
    this->FreeOnTerminate = false;

//    m_CProfileManager.SetName(m_Name);
}

__fastcall SingleThread::SingleThread(bool    CreateSuspened, String  name): WYThread(CreateSuspened)
{
    m_Name = name;
    
//    m_CProfileManager.SetName(m_Name);
}

__fastcall  SingleThread::~SingleThread()
{
}

void        SingleThread::Initialize()
{
    GetLog()->Warn("%s  Sys start id = %d; Class Start ID = %d", m_Name, GetCurrentThreadId(), this->ThreadID);
}

void        SingleThread::UnInitialize()
{
    GetLog()->Warn("UnInitialize : %s  Sys start id = %d; Class Start ID = %d", m_Name, GetCurrentThreadId(), this->ThreadID);
}

void __fastcall     SingleThread::Execute() 
{
	THREAD_TRY_BEGIN
	if(m_CreateSuspended)
	{
		m_CreateEvent->WaitFor(INFINITE);
	}
    
	m_ThreadState = tsIniting;
	if(fpInitFunc)
		fpInitFunc(this);
    Initialize();
    while(this->Terminated == false)
    {
        #ifdef ENABLE_PROFILE
        this->Synchronize(m_CProfileManager.WatchInfo);
        m_CProfileManager.Reset();
        THREAD_PROFILE(&m_CProfileManager, m_Name.c_str());
        #endif
            
        if(fpThreadFunc)
        {
            int sleepTime = fpThreadFunc(this);
            if(sleepTime == 0)
            {
                //繁忙
                m_ThreadState = tsBusy;
                continue;
            }
            else    if(sleepTime > 0)
            {
                //空闲
                Sleep(sleepTime);
                m_ThreadState = tsFree;
                continue;
            }
            else if(sleepTime == -1)
            {
                m_ThreadState = tsTerminate;
                this->Terminate();
            }
            continue;
        }

        Sleep(1);
    }
	m_ThreadState = tsUnIniting;
	if(fpUnInitFunc)
		fpUnInitFunc(this);
    UnInitialize();
        
    THREAD_TRY_END(m_Name)

	GetLog()->Warn("%s Thread Exit", m_Name);
	m_ThreadState = tsFinished;
}

/////////////////////////////////////////////////////////////
//Event对象
WYThreadEvent::WYThreadEvent(Windows::PSecurityAttributes EventAttributes, bool ManualReset, bool InitialState, const AnsiString Name, bool UseCOMWait) :
                                    TEvent(EventAttributes, ManualReset, InitialState, Name, UseCOMWait)
{
    m_bEnabled = true;
}

TWaitResult __fastcall WYThreadEvent::WaitFor(unsigned Timeout)
{
    if(m_bEnabled)
        return  TEvent::WaitFor(Timeout);
    return  wrAbandoned;
}

void                WYThreadEvent::Enable()
{
    m_bEnabled = true;
}

void                WYThreadEvent::Disable()
{
    m_bEnabled = false;
}

//////////////////////////////////////////////////////////////////////////////
UserThread::UserThread()
{
    m_ThreadFunc = NULL;
    m_IsComObj = false;
    m_Thread = NULL;
}

void      UserThread::UserCreate(bool    CreateSuspened, String  name, TDefThreadFunc  func, bool createCOMObj)
{
    m_ThreadName = name;
    m_ThreadFunc = func;
    m_IsComObj = createCOMObj;
    m_Thread = new SingleThread(CreateSuspened, name, func, createCOMObj);
}

UserThread::~UserThread()
{
    SAFE_DELETE(m_Thread);
}

//////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////
ThreadManager::ThreadManager()
{
    m_bThreadStarted = false;
}

ThreadManager::~ThreadManager()
{
}

UserThread * 		ThreadManager::ManagerCreateThread(String  name, TDefThreadFunc  func, bool createCOMObj)
{
	UserThread * curSingleThread = new UserThread;
	bool createSuspended = !m_bThreadStarted;
    curSingleThread->UserCreate(createSuspended, name, func, createCOMObj);

	m_Threads.Add(curSingleThread);
	return			curSingleThread;

}

void            ThreadManager::StartAll()
{
    m_bThreadStarted = true;
    for(int i=0; i<m_Threads.Count(); i++)
    {
		m_Threads.At(i)->GetThread()->GetCreateEvent()->SetEvent();
    }
}

void            ThreadManager::AddThread(WYThread  * thread)
{
    UserThread * addThread = new UserThread;
    addThread->SetThread(thread);
    m_Threads.Add(addThread);
}

void			ThreadManager::ProcessDeletedThread()
{
	for(int i=m_Threads.Count()-1; i>=0; i--)
	{
		if(m_Threads[i]->GetThread()->GetThreadState() == tsFinished)
		{
			GetLog()->Warn("Delete Thread : %s", m_Threads[i]->GetThread()->GetName());
			m_Threads.Delete(i);
		}
	}
}

void            ThreadManager::StopAll()
{
    for(int i=0; i<m_Events.Count(); i++)
    {
        //让所有线程都不要等待
        m_Events[i]->SetEvent();
        m_Events[i]->Disable();
    }


    for(int i=0; i<m_Threads.Count(); i++)
    {
        m_Threads.At(i)->GetThread()->Terminate();
        GetLog()->Warn("%s Thread Prepare Exit", m_Threads.At(i)->GetThread()->GetName());
        m_Threads.At(i)->GetThread()->WaitFor();
    }
}

void            ThreadManager::FreeAll()
{
    m_bThreadStarted = false;
    StopAll();
    m_Threads.Clear();
}

WYThread    *   ThreadManager::At(int index)
{
	UserThread *thread = m_Threads.At(index);
	if(!thread)
		return NULL;
    return  thread->GetThread();
}

WYThreadEvent * ThreadManager::AddEvent(String name)
{
    WYThreadEvent  *   curEvent = new WYThreadEvent(NULL,true,true,name,false);
    m_Events.Add(curEvent);
    return      curEvent;
}

WYThread    *   ThreadManager::FindThreadByThreadID(int    threadID)
{
    UserThread  *   curThread = FindThreadContainerByID(threadID);
    if(curThread)
        return  curThread->GetThread();
    return  NULL;
}

WYThread    *   ThreadManager::FindThreadByName(String threadName)
{
    UserThread  *   curThread = FindThreadContainerByName(threadName);
    if(curThread)
        return  curThread->GetThread();
    return  NULL;
}

UserThread    *   ThreadManager::FindThreadContainerByID(DWORD threadID)
{
    for(int i=0; i<m_Threads.Count(); i++)
    {
        if(m_Threads[i]->GetThread()->ThreadID == threadID)
            return  m_Threads[i];
    }
    return  NULL;
}

UserThread    *   ThreadManager::FindThreadContainerByName(String threadName)
{
	for(int i=0; i<m_Threads.Count(); i++)
	{
		if(m_Threads[i]->GetThread()->GetName() == threadName)
			return  m_Threads[i];
	}
	return  NULL;
}

void			ThreadManager::AddGUIMessage(String msg)
{
	m_Messages.Push(msg);
}

bool			ThreadManager::PopGUIMessage(String *msg)
{
	return	m_Messages.Pop(msg);
}

int				ThreadManager::GetGUIMessageCount()
{
 	return		m_Messages.Count();
}
