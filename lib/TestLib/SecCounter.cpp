//---------------------------------------------------------------------------
#include    <VCL.h>
#include <mmsystem.h>
#pragma hdrstop

#include "SecCounter.h"
#include "CommFunc.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


SecCounter::SecCounter(int interval)
{
    Clear();
    m_Interval = interval;
}

SecCounter::~SecCounter()
{
}

void            SecCounter::Tick()
{
    m_TotalCount++;
    m_CurCount++;
    Refresh();
}

DWORD           SecCounter::Count()
{
    Refresh();
    return  m_Count;
}

void            SecCounter::Clear()
{
    m_StartTime = 0;
    m_Count = 0;
    m_CurCount = 0;
    m_TotalCount = 0;
}

void            SecCounter::Refresh()
{
    if(m_StartTime == 0)
    {
        m_StartTime = GetTickCount();
        m_CurCount = 0;
    }

    
    if(GetTickCount() - m_StartTime >= m_Interval)
    {
        m_StartTime = GetTickCount();
        m_Count = m_CurCount;
        m_CurCount = 0;
    }
}

String          SecCounter::GetInfo()
{
    return      FormatStr("%d(%d/s)", m_TotalCount, Count());
}

///////////////////////////////////////////////////////////////////////////////////

CFPSCounter         *           GetCFPSCounter()
{
    return          CFPSCounter::GetInstance();
}
//---------------------------------------------------------------------------
IMPLEMENT_SINGLETON(CFPSCounter)
//---------------------------------------------------------------------------
void CFPSCounter::RegisterFPS()
{
    static DWORD m_dwStartTime = 0;
    DWORD dwTime = timeGetTime();
    m_dwFrameCnt++;

    if ( dwTime - m_dwStartTime > 1000 )
    {
        m_fps = m_dwFrameCnt / ( (dwTime - m_dwStartTime) / 1000 );
        m_dwStartTime = dwTime;
        m_dwFrameCnt = 0;
    }
}
//---------------------------------------------------------------------------
DWORD   CFPSCounter::GetFPS()
{
    return (m_fps);
}
//---------------------------------------------------------------------------

