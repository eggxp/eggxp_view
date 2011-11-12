//---------------------------------------------------------------------------

#ifndef SecCounterH
#define SecCounterH
//---------------------------------------------------------------------------

#include "SingletonEx.h"

class       SecCounter
{
private:
    DWORD           m_StartTime;
    DWORD           m_Count;
    DWORD           m_CurCount;
    DWORD           m_Interval;
    DWORD           m_TotalCount;
public:
    SecCounter(int interval = 1000);
    ~SecCounter();
    void            Tick();
    DWORD           Count();
    void            Refresh();
    void            Clear();
    String          GetInfo();
};

///////////////////////////////////////////////////////////

class CFPSCounter
{
    DEFINE_SINGLETONEX(CFPSCounter)
private:
                                CFPSCounter() : m_fps(0),m_dwStartTime(0),m_dwFrameCnt(0)
                                {
                                }
    virtual                     ~CFPSCounter()                              { }

public:
    DWORD                       m_fps;
    DWORD                       m_dwStartTime;
    DWORD                       m_dwFrameCnt;

public:
    virtual DWORD               GetFPS();
    virtual void                RegisterFPS();
};


CFPSCounter         *           GetCFPSCounter();
#endif
