//---------------------------------------------------------------------------

#ifndef messagerH
#define messagerH
#include <windows.h>
#include <string>
using namespace std;
//利用COPY_DATA消息传输数据的类

class  CMessager
{
private:
   HWND      m_HostWindow; //远程窗口句柄
protected:
public:
   string    m_HostWindowClassName; //远程窗口类名
public:
  __fastcall CMessager();
  __fastcall ~CMessager();
  bool       Connect();   //连接到目标窗口
  bool       Connected(){return (m_HostWindow!=0);}
  bool       Send(DWORD Flag,void *DataBuf,int DataLen);
};

//---------------------------------------------------------------------------
#endif
