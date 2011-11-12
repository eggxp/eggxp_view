//---------------------------------------------------------------------------

#ifndef servermgrH
#define servermgrH
#include "serversocket.h"
#include "serverclient.h"
#include "amap.h"
//---------------------------------------------------------------------------
//增加管理和维护客户端列表的 ServerSocket
typedef TServerClient*  __fastcall (__closure *TUSER_NEW_CLIENTOBJ)(SOCKET Socket);
class CASynServerMgr : public CAsyncServerSocket
{
private:
  AIndexList<TServerClient> * m_ClientList;
protected:
  virtual void  OnSocketEvent(CESocketEvent Event,SOCKET SocketID);
  void __fastcall OnClientClose(SOCKET  SocketID);
  TServerClient * AddClient(SOCKET SocketID);
  void			  DelClient(SOCKET SocketID);
public:
  __fastcall 		  CASynServerMgr(HINSTANCE Instance);
  virtual __fastcall ~CASynServerMgr();
  int				Count(){return m_ClientList->Count();}
  TServerClient * 	At(int Index){return  m_ClientList->At(Index);}
  TServerClient *   Find(SOCKET SocketID);
  virtual bool      Stop();
  TUSER_NEW_CLIENTOBJ   OnUserNewClient; //由用户创建TServerClient的继承类的通知函数
};
#endif
