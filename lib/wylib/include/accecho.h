//---------------------------------------------------------------------------

#ifndef accechoH
#define accechoH
#include <vcl.h>
#include "blockclient.h"


typedef void __fastcall (__closure *TON_REFRESH_SUCCESS)(void);
class CAccPing
{
private:
  TStringList * ServerList;
  TStringList * ServerInfo;
  int			BestServerIndex;
  bool			bNotActiveServer;
protected:
  CBlockSocket BlockSocket; 
  static DWORD WINAPI RecvThreadFunc(LPVOID Parameter);
  String GetDelayString(DWORD DelayTime);
public:
  __fastcall CAccPing();
  __fastcall ~CAccPing();
  void SetServerList(TStrings * ServerIPList);
  String	GetServerInfo(int Index);
  int		Count(){return ServerList->Count;}
  void		RefreshServerInfo(); //刷新服务器状态
  TON_REFRESH_SUCCESS  OnRefreshSuccess;
  int		GetBestServer(){return BestServerIndex;}   //获取速度最佳的服务器
  bool		NotActiveServer(){return bNotActiveServer;}//所有服务器均无法链接
};


//---------------------------------------------------------------------------
#endif
