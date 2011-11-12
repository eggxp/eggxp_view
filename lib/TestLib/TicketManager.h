//---------------------------------------------------------------------------

#ifndef TicketManagerH
#define TicketManagerH
//---------------------------------------------------------------------------

#include    "AList.h"
#include    <VCL.h>
#include    <Mmsystem.h>

//对于每一个对象, 会有一个TickManager实例
//tick的类型自己输入

class   TickManager;

class   TickObj
{
friend          TickManager;
private:
    DWORD       m_Tick;
    DWORD       m_Interval;

public:
    TickObj();
    ~TickObj();
    int         CanTick(DWORD   curTick);
    void        SetInterval(DWORD interval);
    void        RefreshTick();

    //调试用
    DWORD       GetInterval(){return    m_Interval;}
    DWORD       GetTick(){return    m_Tick;}
};

class   TickManager
{
private:
    AList<TickObj>      m_Ticks;
public:

    TickManager();
    ~TickManager();
    void                AddTick(int     ttType, DWORD interval);
    TickObj     *       GetTick(int     ttType);
    void                ResetAll();
};


#endif
