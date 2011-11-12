//---------------------------------------------------------------------------


#pragma hdrstop

#include "waitobj.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)
__fastcall TWaitForObj::TWaitForObj()
{
   m_TimeOut = 10000;
   Reset();
   m_WaitInfo ="ÎÞµÈ´ý";
}
//------------------------------------------------------------------------------
__fastcall TWaitForObj::~TWaitForObj()
{
   Reset();
}
//------------------------------------------------------------------------------
DWORD        TWaitForObj::WaitFor(DWORD TimeOut,const String &WaitInfo)
{
    m_TimeOut = TimeOut;
    m_WaitInfo = WaitInfo;
    m_LastWaitTime = GetTickCount();
    return   m_LastWaitTime;

}
