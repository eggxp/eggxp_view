//---------------------------------------------------------------------------


#pragma hdrstop

#include "FiberContext.h"
#include "ThreadManager.h"
#include "Log4me.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

static  void    *   gMainFiber = NULL;


void WINAPI FiberProc(void *fiber_nbr)
{
    FiberProcesser  * processer = (FiberProcesser  *)fiber_nbr;
    while(1)
    {
        processer->OnProcess();
        SwitchToFiber(gMainFiber);
    }
}

////////////////////////////////////////////////////////////////////////////////
FiberProcesser::FiberProcesser()
{
    m_FiberIndex = 0;
    m_WaitCode = 0;
    m_ErrorCode = 0;
    m_FiberStat = 0;
    m_Active = 0;
    m_WaitTick = 0;
    m_WaitTimeout = 0;
    m_FiberContext = NULL;
}

FiberProcesser::~FiberProcesser()
{
}

bool            FiberProcesser::WaitFor(int code, String msg, int timeout)
{
    if(code == 0)
        return false;
    this->SetWaitMsg(msg);
    this->SetWaitCode(code);
    this->SetFiberStat(FS_WAITFOR);
    this->SetWaitTick(GetTickCount());
    this->SetWaitTimeout(timeout);
    SwitchToFiber(gMainFiber);
    if(m_ErrorCode == FEC_NULL)
        return true;
    return false;
}

bool            FiberProcesser::CheckTimeout()
{
    if(this->GetWaitTimeout() == 0)
        return false;

    if((int)GetTickCount() - this->GetWaitTick() >= this->GetWaitTimeout())
    {
        this->SetErrorCode(FEC_TIMEOUT);
		this->SetFiberStat(FS_RUNNING);
		this->SetWaitTimeout(0);
        return true;
	}
	return false;
}

void            FiberProcesser::FiberSleep(int timeout)
{
    this->WaitFor(FWC_SLEEP, "sleep", timeout);
}

void            FiberProcesser::ForceAwake()
{
    this->Awake(FWC_FORCE_AWAKE, FEC_FORCE_AWAKE);
}

void            FiberProcesser::Awake(int code, int errorcode)
{
    if(this->GetFiberStat() != FS_WAITFOR)
    {
        return;
    }

    if(this->GetWaitCode() != code && code != FWC_FORCE_AWAKE)
    {
        return;
    }

    this->SetErrorCode(errorcode);
    this->SetFiberStat(FS_RUNNING);
}
////////////////////////////////////////////////////////////////////////////////

FiberManager::FiberManager()
{
}

FiberManager::~FiberManager()
{
}

void        FiberManager::AddFiber(FiberProcesser * processer)
{
    processer->SetFiberIndex(m_FiberContext.Count());
    m_FiberContext.Add(processer);
}

bool        FiberManager::Start()
{
    gMainFiber = ConvertThreadToFiber(NULL);
    for(int i=0; i<m_FiberContext.Count(); i++)
    {
        void * context = CreateFiber(0, FiberProc, m_FiberContext[i]);
        if(context == NULL)
        {
            GetLog()->Error("FiberManager::Start, context == NULL. Info:%s", SysErrorMessage(GetLastError()));
            return  false;
        }
        m_FiberContext[i]->SetFiberContext(context);
    }
    return  true;
}

void        FiberManager::Process()
{                         
    for(int i=0; i<m_FiberContext.Count(); i++)
    {
        if(m_FiberContext[i]->GetFiberStat() != FS_RUNNING)
        {
			if(!m_FiberContext[i]->CheckTimeout())
			{
				continue;
			}
        }
        SwitchToFiber(m_FiberContext[i]->GetFiberContext());
    }
}

void        FiberManager::Awake(int code, int errorcode)
{
    if(code == 0)
        return;
    for(int i=0; i<m_FiberContext.Count(); i++)
    {
        m_FiberContext[i]->Awake(code, errorcode);
    }
}

static  FiberManager        gFiberManager;
FiberManager    *           GetFiberManager()
{
    return      &gFiberManager;
}
