//---------------------------------------------------------------------------

#ifndef TimeCounterH
#define TimeCounterH
//---------------------------------------------------------------------------

#include    "CountTime.h"
#include    "Log4Me.h"

class       TimeCounter
{
private:
    CTimeCount          m_TimeCount;
public:
    TimeCounter(){}
    ~TimeCounter(){}

    void                BeginCount(){m_TimeCount.BeginCount();}
    double              EndCount(){return   m_TimeCount.EndCount();}
};

TimeCounter     *   GetTimeCounter();

#endif
