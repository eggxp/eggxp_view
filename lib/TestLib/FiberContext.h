//---------------------------------------------------------------------------

#ifndef FiberContextH
#define FiberContextH
//---------------------------------------------------------------------------
#include <vector>
#include "commfunc.h"
#include <vcl.h>
#include "AList.h"
#include "Log4Me.h"

using namespace std;

enum    FiberState
{
    FS_RUNNING = 0,
    FS_WAITFOR
};

enum    TSysFiberErrorCode
{
    FEC_NULL = 0,
    FEC_TIMEOUT,
	FEC_FORCE_AWAKE,
	FEC_USER = 100
};

enum    TSysFiberWaitCode
{
    FWC_NULL = 0,
    FWC_SLEEP,
    FWC_FORCE_AWAKE,
    FWC_USER = 100
};

class FiberProcesser
{
private:
    int             m_FiberIndex;
    void    *       m_FiberContext;
    int             m_WaitCode;
    int             m_ErrorCode;
    int             m_FiberStat;
    int             m_Active;
    int             m_WaitTick;
    int             m_WaitTimeout;
    String          m_WaitMsg;
    String          m_Name;

public:
    FiberProcesser();
    ~FiberProcesser();

    virtual     void        OnProcess() = 0;
    GEN_GET_SET(int, FiberIndex)
    GEN_GET_SET(void *, FiberContext)

    GEN_GET_SET(int, WaitCode)
    GEN_GET_SET(int, ErrorCode)
    GEN_GET_SET(int, FiberStat)
    GEN_GET_SET(int, Active)
    GEN_GET_SET(String, WaitMsg)
    GEN_GET_SET(String, Name)
    GEN_GET_SET(int, WaitTick)
    GEN_GET_SET(int, WaitTimeout);

    bool            WaitFor(int code, String msg, int timeout = 20000);
    bool            CheckTimeout();
    void            FiberSleep(int timeout);
    void            Awake(int code, int errorcode=0);
    void            ForceAwake();
};

class FiberManager
{
private:
    AList<FiberProcesser>                   m_FiberContext;
public:
    FiberManager();
    ~FiberManager();

    void        AddFiber(FiberProcesser * processer);
    bool        Start();
    void        Process();

    int         GetFiberCount(){return      m_FiberContext.Count();}
    FiberProcesser * GetFiberProcesser(int index){return    m_FiberContext[index];}

    void        Awake(int code, int errorcode=0);
};

FiberManager    *           GetFiberManager();

#endif
