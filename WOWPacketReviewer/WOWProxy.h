//---------------------------------------------------------------------------

#ifndef WOWProxyH
#define WOWProxyH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <WINSOCK2.H>
#include "ThreadManager.h"
#include "CommFunc.h"
#include "AList.h"
#include "AMap.h"
#include "PackageCommon.h"



class WOWProxy;
typedef	 void	(__closure * TOnUserAuthPacket)(WOWProxy *self, WOWPackage *packet);

class WOWProxy
{
private:
	CRITICAL_SECTION m_csLock;
	int					m_StopProxy;
    int                 m_IsDesabled;

    TProxyType          m_ProxyType;

	ASharedPtrQueue<WOWPackage>  m_ClientToServerQueue;
    ASharedPtrQueue<WOWPackage>  m_ServerToClientQueue;
	int                 m_Active;
	map<DWORD, DWORD>	m_ThreadState;

    String          m_DesIP;
    int             m_DesPort;
    SOCKADDR_IN     m_ClientAddr;

    SOCKET          m_ClientSocket;
    SOCKET          m_HostSocket;

    int             m_DestIndex;
    int             m_RealmIndex;       // 20110328 多realm机制

	bool            SendBuf_O(SOCKET  s, char * buf, int len);
	bool            SendToBuf_O(SOCKET  s, char * buf, int len, const struct sockaddr FAR * to, int tolen);

	//接收需走逻辑，不直接发给客户端
	int             RecvProxy(SOCKET  from);
	int             SendProxy(SOCKET  to, ASharedPtrQueue<WOWPackage>  *pool);

	int             RecvNormalProxy(SOCKET  from, char *recvBuf, int recvLen);
	//UDP模式
	int             RecvFromProxy(SOCKET  from, struct sockaddr FAR * addrto, int tolen);
	int             SendToProxy(SOCKET  to, ASharedPtrQueue<WOWPackage>  *pool, const struct sockaddr FAR * addrto, int tolen);

	int             HostRecvThread(SingleThread * self);
	int             HostSendThread(SingleThread * self);
	int             ClientRecvThread(SingleThread * self);
	int             ClientSendThread(SingleThread * self);

	int             HostRecvFromThread(SingleThread * self);
	int             HostSendToThread(SingleThread * self);
	int             ClientRecvFromThread(SingleThread * self);
	int             ClientSendToThread(SingleThread * self);

	int				ThreadInitFunc(SingleThread * self);
	int				ThreadUnInitFunc(SingleThread * self);
    
public:
    WOWProxy();
	~WOWProxy();
   	TOnUserAuthPacket	fpOnUserAuthPacket;
	bool            Start(SOCKET client, SOCKADDR_IN clientAddr, String ip, int port);
	bool            StartUDP(SOCKET client, String ip, int port);
    void            Close();

	ASharedPtrQueue<WOWPackage>   * GetClientToServerQueue(){return  &m_ClientToServerQueue;}
    ASharedPtrQueue<WOWPackage>   * GetServerToClientQueue(){return  &m_ServerToClientQueue;}
    int             GetDestIndex(){return       m_DestIndex;}
    void            SetDestIndex(int index){m_DestIndex = index;}
    GEN_GET_SET(int, RealmIndex)
	int             GetActive(){return      m_Active;}
	int             GetClosed();

    void            SetProxyType(int type){m_ProxyType = (TProxyType)type;}
	int             GetProxyType(){return      (int)m_ProxyType;}

	void			ServerAuthOKBeginProxy();
	void			ServerAuthOKBeginProxyUDP();

    int             GetDesPort(){return m_DesPort;}
    String          GetDesIP(){return m_DesIP;}
    GEN_GET_SET(int, IsDesabled)
};

/////////////////////////////////////////////////////////////////////////////
class WOWProxyManager
{
private:
	CRITICAL_SECTION m_csLock;
	ASharedPtrQueue<WOWPackage>  m_AllQueue;
    AList<WOWProxy> m_WOWProxys;
    int             m_DestPort;
	String          m_DestIP;
    int             m_UDPDestPort;
	String          m_UDPDestIP;
	int				m_GateIndex;
    int             m_RealmIndex;
	TProxyType      m_ProxyType;
	String			m_ConnectStyle;

    int             m_ListenPort;
	SOCKET          m_ListenSocket;
	SOCKET          m_ListenSocketUDP;
	int             m_ListenThreadCount;
	String			m_RealmdIP;
	int				m_RealmdPort;
	int             m_IsFirstStartWorking;

	DWORD			m_TotalSendBytes;
	DWORD			m_TotalRecvBytes;

	//简单代理直接模式， 转发任何封包, 不解密
	bool			m_DirectModel;

	int             ListenThread(SingleThread * self);
	bool 			StartListenPort(int listenPort, int listenThreadCount = 100);
	bool 			StartListenPortUDP(int listenPort);
public:
	WOWProxyManager();
	~WOWProxyManager();

    void            SetProxyType(int type){m_ProxyType = (TProxyType)type;}
	int             GetProxyType(){return      (int)m_ProxyType;}
	bool            Start(int listenPort, int listenThreadCount = 100);
	void            Close();
	void			ResetConnections();
	TOnUserAuthPacket	fpOnUserAuthPacket;

	WOWProxy    *   GetWOWProxy(int index);
	int             GetWOWProxyCount();
	void            SetDestAddress(String addr);
	void			ProcessRemoveProxyList();
	void			SetForceRealmdIP(String realmdip, int port);
    GEN_GET_SET(int, IsFirstStartWorking)

	GEN_GET_SET(bool, DirectModel)

    WOWProxy    *   GetActiveRealmd(int realmIndex);
	WOWProxy    *   GetActiveWorld(int worldIndex);

	//注意： 魔兽世界发给realm和发给world的封包顺序有要求，必须保证顺序！所以allqueue放到公用类来
	//[达拉然不能登入问题]
	ASharedPtrQueue<WOWPackage>   * GetAllQueue(){return    &m_AllQueue;}

	DWORD			GetTotalSendBytes() {return m_TotalSendBytes;}
	DWORD			GetTotalRecvBytes() {return m_TotalRecvBytes;}
	void			AddTotalSendBytes(DWORD bytes);
	void			AddTotalRecvBytes(DWORD bytes);
};

class WOWProxyPool
{
private:
    AList<WOWProxyManager>      m_WOWProxyManagers;
public:
    WOWProxyPool();
    ~WOWProxyPool();

    void                    AddProxy();
    WOWProxyManager *       GetProxy(int index);
    int                     GetProxyCount();

};

WOWProxyManager  *       GetWOWProxyManager();
WOWProxyPool     *       GetWOWProxyPool();

#endif
