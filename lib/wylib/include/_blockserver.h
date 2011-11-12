//---------------------------------------------------------------------------
//2006.06.06 by bluely  : 修正了Thread同时创建过多出现无法创建线程的问题
#ifndef blockserverH
#define blockserverH
#include <vcl.h>
#include <SyncObjs.hpp>
#include <ScktComp.hpp>
#include "alist.h"

class CServerThread;
typedef void __fastcall (__closure * OnThreadMethods)(CServerThread * Thread);
typedef void __fastcall (__closure * OnLogMethods)(String Log);
struct ThreadInfo
{
  DWORD   ThreadID;
  int     State;
  SOCKET  ClientSocket;
  String  ClientIP;
  void *  UserData;
};

//阻塞线程池方式的Socket Server
class CServerSocket
{
private:
   AList<CServerThread> * m_ThreadPool; //线程池
   TCriticalSection     * m_GlobalLock; //互斥锁
   TStringList          * m_LogList;
protected:
  SOCKET     m_ListenSocket;
  bool       m_IsActive;
  void       SetThreadPool(int ThreadNumber); //构造线程池
  void       FreeThreadPool();   //释放线程池里面的线程
public:
  int       RecvTimeOut;    //接收超时
  bool      CanShowLog;     //是否显示日志记录
  WORD      Port;
  OnLogMethods  OnOutputLog;
  OnLogMethods  OnOutputErrorLog;
  String     m_LastErrorStr;       //最后的错误信息
  OnThreadMethods  OnThreadBegin;     //在此函数初始化线程变量
  OnThreadMethods  OnThreadClientAccept;  //在此函数进行用户自定义处理
  OnThreadMethods  OnThreadEnd;
public:
  __fastcall CServerSocket();
  __fastcall ~CServerSocket();
  bool       Start(int PoolSize);            //开始服务
  bool       Stop();             //结束服务
  SOCKET     SafeAccept(struct sockaddr FAR* addr,int FAR* addrlen);
  int        ThreadPoolSize(){return m_ThreadPool->Count();}
  bool       IsActive(){return m_IsActive;}
  bool       GetThreadInfo(int ThreadIndex,ThreadInfo * ThreadInfoOut);
  void       ShowLog(String Log);
  void       ShowErrorLog(String Log);
};

//---------------------------------------------------------------------------
#endif
