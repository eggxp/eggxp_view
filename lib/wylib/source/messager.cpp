//---------------------------------------------------------------------------

#pragma hdrstop

#include "messager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall CMessager::CMessager()
{
   m_HostWindow=0;
   m_HostWindowClassName="";
}
//---------------------------------------------------------------------------
__fastcall CMessager::~CMessager()
{
   ;
}
//---------------------------------------------------------------------------
bool  CMessager::Connect()
{
   if (m_HostWindowClassName=="")
    return false;
    m_HostWindow =FindWindow(m_HostWindowClassName.c_str(),NULL);
    return  Connected();
}
//---------------------------------------------------------------------------
bool CMessager::Send(DWORD Flag,void *DataBuf,int DataLen)
{
    COPYDATASTRUCT SendData;
    if (!Connected())  //还没连接
    {
      if (!Connect())  //连接失败
        return false;
    }
    SendData.dwData = Flag;
    SendData.cbData = DataLen;
    SendData.lpData = DataBuf;
    SendMessage(m_HostWindow,WM_COPYDATA,0,LPARAM(&SendData));
    return true;
}
