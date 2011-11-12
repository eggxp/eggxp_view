//---------------------------------------------------------------------------

#ifndef waitobjH
#define waitobjH
#include <vcl.h>
//------------------------------------------------------------------------------
class TWaitForObj
{
private:
    DWORD m_LastWaitTime;
    int   m_TimeOut;
protected:
    String m_WaitInfo;

public:
  __fastcall TWaitForObj();
  __fastcall ~TWaitForObj();
  DWORD      WaitFor(DWORD TimeOut,const String &WaitInfo);  //开始等待
  __inline int        GetElapseTime(){return (GetTickCount()-m_LastWaitTime);} //获取已经等待的时间
  __inline int        RemainTime(){return (m_TimeOut-GetElapseTime());} //剩余等待时间
  void       Reset(){m_LastWaitTime=0;}           //重置,停止等待
  bool       IsWaiting(){return (m_LastWaitTime!=0 && GetElapseTime() < m_TimeOut);} //测试是否还处于等待状态
};

//---------------------------------------------------------------------------
#endif
