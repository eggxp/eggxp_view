//---------------------------------------------------------------------------
//更新记录
//2006.06.06 BY bluely
//为nethandle.h的TNetHandle类添加了sock5代理协议支持,所有基于nethandle的网络客户端通讯都可以直接支持sock5代理了

#ifndef nethandleH
#define nethandleH
#include <Classes.hpp>
#include <ScktComp.hpp>
#include "clientsocket.h"
class TSockProxyClient;
typedef struct tagNetMSG
{   // msg
    int    MessageID;
    int    SubCmdID;
	WPARAM wParam;
    LPARAM lParam;
} NET_MSG,*lpNET_MSG;

enum NET_MSG_TYPE{nmCONNECT=0,nmDISCONNECT,nmError,nmRECV,nmSEND,nmCanSEND,nmDECRECV,nmDECSEND,nmSelfSEND,nmSock5Finish};
typedef void  __fastcall (__closure *NetOnOutputLog)(const String &ValueStr);
typedef void  __fastcall (__closure *NetOnNetMessage)(NET_MSG_TYPE Type,void *Data,int DataLen);
typedef void  __fastcall (__closure *ProxyServerMessage)(NET_MSG_TYPE Type,String &RecvData);
//网络消息处理管理,接口类
class TNetHandle
{
private:
   CClientSocket   *  _Client; //异步消息Socket对象
   TSockProxyClient	 *  _Sock5Protocol; //Sock5协议处理对象
   String			 _Sock5ServerIP;   //Sock5 服务器IP
   WORD				 _Sock5Port;      //Sock5服务器端口
   DWORD			 LastRecvTime;
protected:
  void __fastcall OnClientConnect(CClientSocket  *ClientSocket);
  void __fastcall OnClientDisconnect(CClientSocket  *ClientSocket,bool ServerDisconnect);
  void __fastcall OnClientError(CClientSocket  *ClientSocket,int ErrorCode,char *ErrorInfo);
  void __fastcall OnClientRead(CClientSocket  *ClientSocket,SOCKET SocketID);
  void __fastcall OnClientSend(CClientSocket  *ClientSocket,SOCKET SocketID);
  virtual int __fastcall DispatchSocketWindowMsg(String &RecvData)=0;   //处理远处网络封包信息(拆分,解密封包后加入队列),纯虚函数,继承类实现
  virtual void __fastcall DispatchNetworkQueue()=0;                  //处理网络封包队列,纯虚函数,继承类实现
  virtual void __fastcall DispatchNetworkMsg(NET_MSG &NetMsg)=0;    //处理网络封包消息,纯虚函数,继承类实现
  virtual void __fastcall PackSend(String &OrgData)=0;              //打包加密待发送数据,纯虚函数,继承类实现
  virtual void __fastcall PackSend(char * Data,int Len)=0;          //打包加密待发送数据,纯虚函数,继承类实现
  virtual void __fastcall OnSocketEvent(NET_MSG_TYPE NetMsg)=0;    //用于通知继承类发生了何种网络socket事件
  void __fastcall PostSocketMessage(NET_MSG_TYPE Type,void *Data,int DataLen);
protected:
   String          LastErrInfo;  //错误消息
   String          RecvCacheData;  //Recv未完整封包缓冲区
   static          __fastcall void OnSocketError(int ErrorCode);
   void 		   LoginToProxy();
   bool 		   Recv_ProxyReturn(const String &RecvData);
public:
	NetOnOutputLog  OutputLog;          //实时输出类提示信息的回调函数
	NetOnNetMessage OnSocketMessage;   //通知使用者网络消息的回调函数
	int  SendByteTotal; //累计接受封包数
	int  RecvByteTotal; //累计发送封包数
	bool    UseSock5Proxy; //是否使用Sock5代理

public:
  __fastcall TNetHandle(TForm * AOwner=NULL);
  virtual __fastcall ~TNetHandle();
  void SetRemoteAddr(const String &IP,WORD Port); //设置远程服务器的IP和端口
  int  SendData(String Data);                     //提供发送数据的接口
  int  SendBuf(char *buf,int len);
  __inline bool IsActive(){return _Client->IsConnected();}       //是否处于连接状态
  void OutputInfo(const String &Info);            //输出提示信息
  bool Connect();                                 //开启连接
  void DisConnect();                              //断开连接
  String GetHostAddr();
  DWORD	 IdleTime();		//网络RECV空闲时间,单位毫秒
  void SetSock5(String  Sock5ServerIP,  //Sock5 服务器IP
				WORD    Sock5ServerPort, //Sock5服务器端口
				bool    UseAuthentication, //是否需要验证用户名
				String  UserName,       //Sock5服务器用户名
				String  PassWord);       //Sock5服务器密码
  SOCKET  SocketID(){return _Client->SocketID();} //返回socketid
};

//---------------------------------------------------------------------------
//代理服务器类
class TProxyServer
{
private:
   TNetHandle       * m_lpClientNetHandle;
   TServerSocket    * ServerSocket;
   TCustomWinSocket * m_LocalActiveServerSocket;
   NetOnNetMessage    m_pfOrgClientMessage;
   TStringList      * m_lpClientWaitDataBuf;   //Client连接未成功的时候暂存的数据缓冲区
protected:
  void __fastcall ServerSocketClientConnect(TObject *Sender, TCustomWinSocket *Socket);
  void __fastcall ServerSocketClientDisconnect(TObject *Sender, TCustomWinSocket *Socket);
  void __fastcall ServerSocketClientError(TObject *Sender, TCustomWinSocket *Socket, TErrorEvent ErrorEvent,int &ErrorCode);
  void __fastcall ServerSocketClientRead(TObject *Sender, TCustomWinSocket *Socket);
  void __fastcall OnClientSocketMsg(NET_MSG_TYPE Type,void *Data,int DataLen);
public:
  ProxyServerMessage OnServerSocketMessage;
public:
  __fastcall TProxyServer();
  __fastcall ~TProxyServer();
  void __fastcall SetClientNetHandle(TNetHandle *ClientNetHandle);
  __inline void __fastcall SetServerPort(WORD Port){ServerSocket->Port = Port;}
  __inline WORD __fastcall GetPort(){return ServerSocket->Port;}
  __inline void __fastcall SetActive(bool IsActive){ServerSocket->Active = IsActive;}
  __inline bool __fastcall IsActive(){return ServerSocket->Active;}
  int      SendData(char *Data,int Len);

};

#endif
