//---------------------------------------------------------------------------

#include <vcl.h>
#include <memory>
#include <map>
#include <vector>
#include <winsock2.h>
#include "ShareDef.h"
#include "SharedMemInfo.h"
#include "Log4Me.h"
#include    "CommFunc.h"

#pragma comment(lib,"ws2_32.lib")

using namespace std;

#pragma hdrstop
#pragma argsused






#define     HOOK_SIZE       6

#define     WATCH_PORT      0

static      map<SOCKET, int> gNonBlockingSocket;
static      int                 gConnectPort = 0;
//static      map<String, String> gRedirectIPList;
static      map<String, SOCKET> gUDPConnectList;

//自定义APIHOOK结构
struct  HOOKSTRUCT
{
    FARPROC funcaddr;  //RECV函数所在地址
    BYTE    olddata[HOOK_SIZE];      //RECV函数开头的8个字节原始数据
    BYTE    newdata[HOOK_SIZE];    //我们要写入的数据，汇编代码在下面，利用了EAX存储要跳转的地址，并且FF E0这个操作是绝对地址的
};

static    HINSTANCE  gHInstDLL = 0;
//static    vector<int>   gRedirectPort;
struct tagConnectInfo
{
    String IP;
    int Port;
    tagConnectInfo()
    {
        Port = 0;
    }
    tagConnectInfo(String ip, int port)
    {
        Port = port;
        IP = ip;
    }
    bool Equal(String ip, int port)
    {
        return IP == ip && Port == port;
    }
};
static    vector<tagConnectInfo>     gConnectPortList;
static    HANDLE     gHostWindowHandle = 0;
static    String     gFindWindowClassName;
static  WOWHookViewInfo *   gWOWHookViewInfo = NULL;

//备份sendto的地址
DWORD sendto_sin_port = 0;
DWORD sendto_sin_addr = 0;

DWORD wsasendto_sin_port = 0;
DWORD wsasendto_sin_addr = 0;


BOOL   CALLBACK   EnumFindViewerWindowsProc(HWND   hwnd,   LPARAM   lParam)
{
	TCHAR	pclassName[100];
	GetClassName(hwnd, pclassName, sizeof(pclassName) / sizeof(TCHAR));
	String className = pclassName;
//	GetLog()->Warn("(%s,%s),(%d,%d)", className, gFindWindowClassName, className.Length(), gFindWindowClassName.Length());
	if(className == gFindWindowClassName)
    {
        ASSERT(gWOWHookViewInfo)
        gHostWindowHandle = hwnd;
        return false;
	}
    return true;
}

void        InitDLL(HINSTANCE hinstDLL)
{
	if(gHInstDLL != 0)
		return;

	GetSharedMemInfo()->OpenMapping();
//	GetLog()->Warn("InitDLL");
    gHInstDLL = hinstDLL;

	gWOWHookViewInfo = GetSharedMemInfo()->FindSelf();
    if(!gWOWHookViewInfo)
    {
        ShowMessage("Unknown Failed");
		return;
	}

//	TCHAR	pfileName[255];
//	GetModuleFileName(gHInstDLL, pfileName, sizeof(pfileName) / sizeof(TCHAR));
//	String fileName = pfileName;
//	String path = ExtractFilePath(fileName) + "wowconfig.ini";
//	if(!FileExists(path))
//	{
//		ShowMessage(FormatStr("Config Not Exists?%s", path));
//		return;
//	}
//    gLoadIni = new TMemIniFile(path);

	gFindWindowClassName = gWOWHookViewInfo->MainWindowClassName;

	EnumWindows((WNDENUMPROC)EnumFindViewerWindowsProc, NULL);

	if(gHostWindowHandle == 0)
	{
		ShowMessage("Can't Find Host Window?");
	}

    gConnectPort = gWOWHookViewInfo->HostPortNumber;
}

void        LogMsg(String msg, int par = MSG_HINT)
{
    if(par == MSG_HINT)
    {
        msg = L">" + msg;
    }

//	String ansiMsg = msg;
	COPYDATASTRUCT copyData;
	copyData.cbData = msg.Length() * sizeof(TCHAR);
	copyData.lpData = msg.c_str();
    copyData.dwData = par;

//	GetLog()->Warn(msg);
	HANDLE pWindow = gHostWindowHandle;
//	GetLog()->Warn(msg);
    if (pWindow)
    {
        ::SendMessage(pWindow,WM_COPYDATA, NULL, (LPARAM)&copyData);
	}
	else
	{
		ShowMessage(msg);
	}
}

HOOKSTRUCT gRecvHookData; //ws2_32.dll HOOK结构
HOOKSTRUCT gConnectHookData; //ws2_32.dll HOOK结构
HOOKSTRUCT gSendHookData; //ws2_32.dll HOOK结构
HOOKSTRUCT gIoctlsocketHookData;
HOOKSTRUCT gSendToHookData;
HOOKSTRUCT gRecvFromHookData;
HOOKSTRUCT gWSASendToHookData;
HOOKSTRUCT gWSARecvFromHookData;
HOOKSTRUCT gWSARecvHookData; //ws2_32.dll HOOK结构
HOOKSTRUCT gWSAConnectHookData; //ws2_32.dll HOOK结构
HOOKSTRUCT gWSASendHookData; //ws2_32.dll HOOK结构


////////////////////////////////////////
//将原来的函数内容写回——关闭HOOK
void HookOffOne(HOOKSTRUCT *hookfunc)
{
    WriteProcessMemory(GetCurrentProcess(), hookfunc->funcaddr, hookfunc->olddata, HOOK_SIZE, 0);
}

//将我们构建的代码写入——打开HOOK
void HookOnOne(HOOKSTRUCT *hookfunc)
{          
    WriteProcessMemory(GetCurrentProcess(), hookfunc->funcaddr, hookfunc->newdata, HOOK_SIZE, 0);
}

bool HOOKAPI(DWORD Address,HOOKSTRUCT *hookfunc,DWORD mFncAddress)
{
    hookfunc->funcaddr = (FARPROC)Address;  //这个地方用了一个转换，把传入值转换成何结构当中声明的一样
    memcpy(hookfunc->olddata, hookfunc->funcaddr, HOOK_SIZE); //记录RECV函数前8字节原始数据


    //下面开始构建汇编代码
    hookfunc->newdata[0]=0x68;   //PUSH
    memcpy(&hookfunc->newdata[1], (char *)(&mFncAddress), 4);  //这里替换了上面提到的 00000000 为我们用来代替RECV的函数的地址
    hookfunc->newdata[5]=0xC3;   //RET

    HookOnOne(hookfunc);  //将RECV函数前8字节替换为我们构建的代码——开始HOOK RECV
    return true;
}

static  SOCKET     gLogSocket = 0;
////////////////////////////////////////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
WINSOCK_API_LINKAGE
int
WSAAPI
RecvHook(
    IN SOCKET s,
    __out_bcount_part(len, return) __out_data_source(NETWORK) char FAR * buf,
    IN int len,
    IN int flags
    )
{
    if(s == gLogSocket)
	{
		LogMsg(FormatStr("Call Recv"));
    }


    HookOffOne(&gRecvHookData); //先关闭HOOK，因为已经进入我们的函数了
    int nReturn = recv(s, buf, len, flags);  //先运行原来的RECV，否则我们不能得到或不能得到全部被复制的内容

    if(s == gLogSocket && nReturn > 0)
    {
        LogMsg(FormatStr("Recv: %s", BinToStr(buf, nReturn)));
    }
    HookOnOne(&gRecvHookData); //继续HOOK
    //sndmsg((DWORD)len,(DWORD)nReturn);
    return(nReturn);
}


WINSOCK_API_LINKAGE
        int
        WSAAPI
        ConnectHook(
            IN SOCKET s,
            __in_bcount(namelen) const struct sockaddr FAR * name,
            IN int namelen
            )
{
	ASSERT(gWOWHookViewInfo)
    int nReturn = 0;
	WORD hport = (BYTE)name->sa_data[0];
    WORD lport = (BYTE)name->sa_data[1];
    hport *= 0x100;
//    LogMsg(BinToStr((char *)name->sa_data, sizeof(name->sa_data)));
    WORD   port = hport + lport;
	String  ip=FormatStr("%d.%d.%d.%d", (BYTE)name->sa_data[2],
                                        (BYTE)name->sa_data[3],
                                        (BYTE)name->sa_data[4],
										(BYTE)name->sa_data[5]);

	int nonBlocking = 0;
    if(gNonBlockingSocket.find(s) != gNonBlockingSocket.end())
    {
        nonBlocking = 1;
    }
    LogMsg(FormatStr("Connect, IP=%s, Port=%d, nonBlocking = %d", ip, port, nonBlocking));
    HookOffOne(&gConnectHookData);

//    int needRedirect = 0;
	if(port == 80 || ip == "127.0.0.1")
    {
        LogMsg("no redirect");
		nReturn = connect(s, name, namelen);
		HookOnOne(&gConnectHookData);

		LogMsg(FormatStr("no redirect. nReturn = %d, LastError = %d", nReturn, WSAGetLastError()));
        return nReturn;
    }
	//redirect IP
	if(port == WATCH_PORT)
		gLogSocket = s;

	static int index = 0;

	gWOWHookViewInfo->ClientConnectIndex = index;
	LogMsg(FormatStr("tcp|%s|%d|%d", ip, port, gWOWHookViewInfo->ClientConnectIndex), MSG_CONNECT);
    sockaddr_in * their_addr = (sockaddr_in *)name;
	their_addr->sin_port = htons(gConnectPort);
	AnsiString ansiIP = HOST_IP;
    their_addr->sin_addr.s_addr=inet_addr(ansiIP.c_str());


	nReturn = connect(s, name, namelen);

	//注意: 不要摄入封包流逻辑, 不要在这里主动发包..
	HookOnOne(&gConnectHookData);

    index++;
	return nReturn;
}

WINSOCK_API_LINKAGE
int
WSAAPI
SendHook(
    IN SOCKET s,
    __in_bcount(len) const char FAR * buf,
    IN int len,
    IN int flags
    )
{
    if(s == gLogSocket)
    {
        LogMsg(FormatStr("Send: %s", BinToStr((char *)buf,len)));
    }
    
    HookOffOne(&gSendHookData);
    int nReturn = send(s, buf, len, flags);
    HookOnOne(&gSendHookData);
    return(nReturn);

}

WINSOCK_API_LINKAGE
int
WSAAPI
IoctlsocketHook(
    IN SOCKET s,
    IN long cmd,
    __inout u_long FAR * argp
    )
{
    HookOffOne(&gIoctlsocketHookData);

    if((DWORD)cmd == FIONBIO)
    {
        LogMsg(FormatStr("socket(%d) non-blocking : %d", s, *argp));
        gNonBlockingSocket[s] = 1;
    }

	int nReturn = ioctlsocket(s, cmd, argp);
    HookOnOne(&gIoctlsocketHookData);
    return(nReturn);
}

////////////////////////////////////////////////////////////////////////////////////////////////
// WSA TCP
WINSOCK_API_LINKAGE
int
WSAAPI
WSARecvHook(
    __in SOCKET s,
    __in_ecount(dwBufferCount) __out_data_source(NETWORK) LPWSABUF lpBuffers,
    __in DWORD dwBufferCount,
    __out_opt LPDWORD lpNumberOfBytesRecvd,
    __inout LPDWORD lpFlags,
    __inout_opt LPWSAOVERLAPPED lpOverlapped,
	__in_opt LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
	)
{
	HookOffOne(&gWSARecvHookData); //先关闭HOOK，因为已经进入我们的函数了
	int nReturn = WSARecv(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd, lpFlags, lpOverlapped, lpCompletionRoutine);  //先运行原来的RECV，否则我们不能得到或不能得到全部被复制的内容
    HookOnOne(&gWSARecvHookData); //继续HOOK
    //sndmsg((DWORD)len,(DWORD)nReturn);
    return(nReturn);
}


WINSOCK_API_LINKAGE
int
WSAAPI
WSAConnectHook(
    __in SOCKET s,
    __in_bcount(namelen) const struct sockaddr FAR * name,
    __in int namelen,
    __in_opt LPWSABUF lpCallerData,
    __out_opt LPWSABUF lpCalleeData,
    __in_opt LPQOS lpSQOS,
    __in_opt LPQOS lpGQOS
    )
{
	ASSERT(gWOWHookViewInfo)
    int nReturn = 0;
	WORD hport = (BYTE)name->sa_data[0];
    WORD lport = (BYTE)name->sa_data[1];
    hport *= 0x100;
//    LogMsg(BinToStr((char *)name->sa_data, sizeof(name->sa_data)));
    WORD   port = hport + lport;
	String  ip=FormatStr("%d.%d.%d.%d", (BYTE)name->sa_data[2],
                                        (BYTE)name->sa_data[3],
                                        (BYTE)name->sa_data[4],
										(BYTE)name->sa_data[5]);

	int nonBlocking = 0;
    if(gNonBlockingSocket.find(s) != gNonBlockingSocket.end())
    {
        nonBlocking = 1;
    }
    LogMsg(FormatStr("Connect, IP=%s, Port=%d, nonBlocking = %d", ip, port, nonBlocking));
	HookOffOne(&gWSAConnectHookData);

//    int needRedirect = 0;
	if(port == 80 || ip == "127.0.0.1")
    {
        LogMsg("no redirect");
		nReturn = WSAConnect(s, name, namelen, lpCallerData, lpCalleeData, lpSQOS, lpGQOS);
		HookOnOne(&gWSAConnectHookData);

		LogMsg(FormatStr("no redirect. nReturn = %d, LastError = %d", nReturn, WSAGetLastError()));
        return nReturn;
    }
	//redirect IP
	if(port == WATCH_PORT)
		gLogSocket = s;

	static int index = 0;

	gWOWHookViewInfo->ClientConnectIndex = index;
	LogMsg(FormatStr("tcp|%s|%d|%d", ip, port, gWOWHookViewInfo->ClientConnectIndex), MSG_CONNECT);
    sockaddr_in * their_addr = (sockaddr_in *)name;
	their_addr->sin_port = htons(gConnectPort);
	AnsiString ansiIP = HOST_IP;
    their_addr->sin_addr.s_addr=inet_addr(ansiIP.c_str());


	nReturn = WSAConnect(s, name, namelen, lpCallerData, lpCalleeData, lpSQOS, lpGQOS);

	//注意: 不要摄入封包流逻辑, 不要在这里主动发包..
	HookOnOne(&gWSAConnectHookData);

    index++;
	return nReturn;
}

WINSOCK_API_LINKAGE
int
WSAAPI
WSASendHook(
    __in SOCKET s,
    __in_ecount(dwBufferCount) LPWSABUF lpBuffers,
    __in DWORD dwBufferCount,
    __out_opt LPDWORD lpNumberOfBytesSent,
    __in DWORD dwFlags,
    __inout_opt LPWSAOVERLAPPED lpOverlapped,
    __in_opt LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
    )
{
	HookOffOne(&gWSASendHookData);
    int nReturn = WSASend(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent, dwFlags, lpOverlapped, lpCompletionRoutine);
    HookOnOne(&gWSASendHookData);
    return(nReturn);
}

////////////////////////////////////////////////////////////////////////////////////////////////
//  UDP Hook
void CheckConnectUDPToTCP(const struct sockaddr FAR * dest)
{
	AnsiString ansiIP = HOST_IP;
	WORD hport = (BYTE)dest->sa_data[0];
	WORD lport = (BYTE)dest->sa_data[1];
	hport *= 0x100;
	WORD   sendtoPort = hport + lport;
	String  sendtoIP=FormatStr("%d.%d.%d.%d", (BYTE)dest->sa_data[2],
										(BYTE)dest->sa_data[3],
										(BYTE)dest->sa_data[4],
										(BYTE)dest->sa_data[5]);
	if(sendtoIP == "1.0.0.0")
	{
		return;
	}
	String  sendtoKey=FormatStr("%s:%d", sendtoIP, sendtoPort);
	if (gUDPConnectList.find(sendtoKey) != gUDPConnectList.end())
		return;
	LogMsg(FormatStr("udp|%s|%d|%d", sendtoIP, sendtoPort, gWOWHookViewInfo->ClientConnectIndex), MSG_CONNECT);
	
	gUDPConnectList[sendtoKey] = 0;
	return;
}

WINSOCK_API_LINKAGE
int
WSAAPI
SendToHook(
    __in SOCKET s,
    __in_bcount(len) const char FAR * buf,
    __in int len,
    __in int flags,
    __in_bcount(tolen) const struct sockaddr FAR * to,
    __in int tolen
	)
{
//	if (to) {
//		WORD hport = (BYTE)to->sa_data[0];
//		WORD lport = (BYTE)to->sa_data[1];
//		hport *= 0x100;
//		WORD   port = hport + lport;
//		String  ip=FormatStr("%d.%d.%d.%d", (BYTE)to->sa_data[2],
//											(BYTE)to->sa_data[3],
//											(BYTE)to->sa_data[4],
//											(BYTE)to->sa_data[5]);
//		if (ip != "1.0.0.0")
//		{
//			LogMsg(FormatStr("sendto|%s|%d|%s", ip, port, BinToStr((char FAR * )buf, len)), MSG_ADD_PACKAGE);
//		}
//	}
	HookOffOne(&gSendToHookData);
//	int nReturn = sendto(s, buf, len, flags, to, tolen);
	CheckConnectUDPToTCP(to);
	AnsiString ansiIP = HOST_IP;
	sockaddr_in * their_addr = (sockaddr_in *)to;
	sendto_sin_port = their_addr->sin_port;
	sendto_sin_addr = their_addr->sin_addr.s_addr;
	their_addr->sin_port = htons(gConnectPort + UDP_PORT_START);
	their_addr->sin_addr.s_addr=inet_addr(ansiIP.c_str());
	int nReturn = sendto(s, buf, len, flags, to, tolen);
	HookOnOne(&gSendToHookData);

//	if(nReturn >= 0)
//	{
//		LogMsg(FormatStr("sendto| |0|%s", BinToStr((char FAR * )buf, len)), MSG_ADD_PACKAGE);
//	}
	return(nReturn);


//	HookOffOne(&gSendToHookData);
////	sockaddr_in * their_addr = (sockaddr_in *)to;
////	their_addr->sin_port = htons(gConnectPort);
//	SOCKET sendtoSocket = CheckConnectUDPToTCP(to);
//	int nReturn = send(sendtoSocket, buf, len, flags);
//    // their_addr->sin_addr.s_addr=inet_addr(ansiIP.c_str());
//	//int nReturn = sendto(s, buf, len, flags, to, tolen);
//    HookOnOne(&gSendToHookData);
//    return(nReturn);
}

__control_entrypoint(DllExport) WINSOCK_API_LINKAGE
int
WSAAPI
RecvFromHook(
    __in SOCKET s,
	__out_bcount_part(len, return) __out_data_source(NETWORK) char FAR * buf,
    __in int len,
    __in int flags,
    __out_bcount_part_opt(*fromlen, *fromlen) struct sockaddr FAR * from,
    __inout_opt int FAR * fromlen
	)
{
	HookOffOne(&gRecvFromHookData);
//	int nReturn = recvfrom(s, buf, len, flags, from, fromlen);
	AnsiString ansiIP = HOST_IP;
	sockaddr_in * their_addr = (sockaddr_in *)from;

	int nReturn = recvfrom(s, buf, len, flags, from, fromlen);

	// 127.0.0.1
	// 防止客户端检测这个封包来源是否合法
	if(their_addr->sin_port == htons(gConnectPort + UDP_PORT_START) && their_addr->sin_addr.s_addr == 0x0100007F)
	{
		their_addr->sin_port = sendto_sin_port;
		their_addr->sin_addr.s_addr = sendto_sin_addr;
	}
	HookOnOne(&gRecvFromHookData);

//	if(nReturn > 0)
//	{
//		LogMsg(FormatStr("recvfrom| |0|%s", BinToStr((char FAR * )buf, nReturn)), MSG_ADD_PACKAGE);
//	}
	return nReturn;

}

//////////////////////////////WSA///////////////////////////////
WINSOCK_API_LINKAGE
int
WSAAPI
WSASendToHook(
	__in SOCKET s,
	__in_ecount(dwBufferCount) LPWSABUF lpBuffers,
	__in DWORD dwBufferCount,
	__out_opt LPDWORD lpNumberOfBytesSent,
	__in DWORD dwFlags,
	__in_bcount_opt(iTolen) const struct sockaddr FAR * lpTo,
	__in int iTolen,
	__inout_opt LPWSAOVERLAPPED lpOverlapped,
	__in_opt LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
	)
{
	HookOffOne(&gWSASendToHookData);
//	{
//		// 调试
//		int nReturn = WSASendTo(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent,
//								dwFlags, lpTo, iTolen, lpOverlapped, lpCompletionRoutine);
//
//		String send_string;
//		for (DWORD i=0; i<dwBufferCount; i++)
//		{
//			send_string += BinToStr((char FAR * )lpBuffers[i].buf, lpBuffers[i].len);
//		}
//		LogMsg(FormatStr("sendto| |%d|%s", 0, send_string), MSG_ADD_PACKAGE);
//
//		HookOnOne(&gWSASendToHookData);
//
//		return nReturn;
//	}

	CheckConnectUDPToTCP(lpTo);
	AnsiString ansiIP = HOST_IP;
	sockaddr_in * their_addr = (sockaddr_in *)lpTo;
	wsasendto_sin_port = their_addr->sin_port;
	wsasendto_sin_addr = their_addr->sin_addr.s_addr;
	their_addr->sin_port = htons(gConnectPort + UDP_PORT_START);
	their_addr->sin_addr.s_addr=inet_addr(ansiIP.c_str());
	int nReturn = WSASendTo(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent,
							dwFlags, lpTo, iTolen, lpOverlapped, lpCompletionRoutine);
	HookOnOne(&gWSASendToHookData);

//	if(nReturn == 0)
//	{
//		String send_string;
//		for (DWORD i=0; i<dwBufferCount; i++)
//		{
//			send_string += BinToStr((char FAR * )lpBuffers[i].buf, lpBuffers[i].len);
//		}
//		LogMsg(FormatStr("sendto| |%d|%s", 0, send_string), MSG_ADD_PACKAGE);
//	}
	return nReturn;
}

WINSOCK_API_LINKAGE
int
WSAAPI
WSARecvFromHook(
	__in SOCKET s,
	__in_ecount(dwBufferCount) __out_data_source(NETWORK) LPWSABUF lpBuffers,
	__in DWORD dwBufferCount,
	__out_opt LPDWORD lpNumberOfBytesRecvd,
	__inout LPDWORD lpFlags,
	__out_bcount_part_opt(*lpFromlen,*lpFromlen) struct sockaddr FAR * lpFrom,
	__inout_opt LPINT lpFromlen,
	__inout_opt LPWSAOVERLAPPED lpOverlapped,
	__in_opt LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine
	)
{
	HookOffOne(&gWSARecvFromHookData);
//	{
//		// 调试
//		int nReturn = WSARecvFrom(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd,
//									lpFlags, lpFrom, lpFromlen, lpOverlapped, lpCompletionRoutine);
//		if(nReturn == 0)
//		{
////			LogMsg(FormatStr("lpNumberOfBytesRecvd = %d", *lpNumberOfBytesRecvd));
//			LogMsg(FormatStr("recvfrom| |0|%s", BinToStr((char FAR * )lpBuffers->buf, *lpNumberOfBytesRecvd)), MSG_ADD_PACKAGE);
//		}
//		HookOnOne(&gWSARecvFromHookData);
//		return nReturn;
//	}
	AnsiString ansiIP = HOST_IP;
	sockaddr_in * their_addr = (sockaddr_in *)lpFrom;


	int nReturn = WSARecvFrom(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd,
								lpFlags, lpFrom, lpFromlen, lpOverlapped, lpCompletionRoutine);

	HookOnOne(&gWSARecvFromHookData);

	// 127.0.0.1
	// 防止客户端检测这个封包来源是否合法
	if(their_addr->sin_port == htons(gConnectPort + UDP_PORT_START) && their_addr->sin_addr.s_addr == 0x0100007F)
	{
		their_addr->sin_port = wsasendto_sin_port;
		their_addr->sin_addr.s_addr = wsasendto_sin_addr;
	}
//	if(nReturn == 0)
//	{
//		LogMsg(FormatStr("recvfrom| |0|%s", BinToStr((char FAR * )lpBuffers[0].buf, *lpNumberOfBytesRecvd)), MSG_ADD_PACKAGE);
//	}
	return nReturn;
}
//////////////////////////////END///////////////////////////////

void        ProcessHook()
{
	String libStr = SOCK_DLL;


	HANDLE libHandle = GetModuleHandle(libStr.c_str());

	{
		DWORD connectAddr = (DWORD)GetProcAddress(libHandle, "connect");
		LogMsg(FormatStr("Hook Connect, Addr = 0x%x", connectAddr));
		HOOKAPI(connectAddr,&gConnectHookData,(DWORD)ConnectHook);
	}

	{
		DWORD recvAddr = (DWORD)GetProcAddress(libHandle, "recv");
		LogMsg(FormatStr("Hook Recv, Addr = 0x%x", recvAddr));
		HOOKAPI(recvAddr,&gRecvHookData,(DWORD)RecvHook);
	}

	{
		DWORD sendAddr = (DWORD)GetProcAddress(libHandle, "send");
		LogMsg(FormatStr("Hook Send, Addr = 0x%x", sendAddr));
		HOOKAPI(sendAddr,&gSendHookData,(DWORD)SendHook);
	}

	{
		// WSA TCP
		DWORD connectAddr = (DWORD)GetProcAddress(libHandle, "WSAConnect");
		LogMsg(FormatStr("Hook WSAConnect, Addr = 0x%x", connectAddr));
		HOOKAPI(connectAddr,&gWSAConnectHookData,(DWORD)WSAConnectHook);
	}

	{
		// WSA TCP
		DWORD recvAddr = (DWORD)GetProcAddress(libHandle, "WSARecv");
		LogMsg(FormatStr("Hook WSARecv, Addr = 0x%x", recvAddr));
		HOOKAPI(recvAddr,&gWSARecvHookData,(DWORD)WSARecvHook);
	}

	{
		// WSA TCP
		DWORD sendAddr = (DWORD)GetProcAddress(libHandle, "WSASend");
		LogMsg(FormatStr("Hook WSASend, Addr = 0x%x", sendAddr));
		HOOKAPI(sendAddr,&gWSASendHookData,(DWORD)WSASendHook);
	}

	{
		DWORD ioctlAddr = (DWORD)GetProcAddress(libHandle, "ioctlsocket");
		LogMsg(FormatStr("Hook Ioctl, Addr = 0x%x", ioctlAddr));
		HOOKAPI(ioctlAddr,&gIoctlsocketHookData,(DWORD)IoctlsocketHook);
	}

	// UDP
	{
		DWORD sendToAddr = (DWORD)GetProcAddress(libHandle, "sendto");
		LogMsg(FormatStr("Hook SendTo, Addr = 0x%x", sendToAddr));
		HOOKAPI(sendToAddr,&gSendToHookData,(DWORD)SendToHook);
	}

	{
		DWORD recvFromAddr = (DWORD)GetProcAddress(libHandle, "recvfrom");
		LogMsg(FormatStr("Hook RecvFrom, Addr = 0x%x", recvFromAddr));
		HOOKAPI(recvFromAddr,&gRecvFromHookData,(DWORD)RecvFromHook);
	}

	{
		DWORD wsaSendToAddr = (DWORD)GetProcAddress(libHandle, "WSASendTo");
		LogMsg(FormatStr("Hook WSASendTo, Addr = 0x%x", wsaSendToAddr));
		HOOKAPI(wsaSendToAddr,&gWSASendToHookData,(DWORD)WSASendToHook);
	}

	{
		DWORD wsaRecvFromAddr = (DWORD)GetProcAddress(libHandle, "WSARecvFrom");
		LogMsg(FormatStr("Hook WSARecvFrom, Addr = 0x%x", wsaRecvFromAddr));
		HOOKAPI(wsaRecvFromAddr,&gWSARecvFromHookData,(DWORD)WSARecvFromHook);
	}

    LogMsg("HiJack OK!");
}

int __stdcall DllMain(HINSTANCE hinstDLL, DWORD fwdreason, LPVOID lpvReserved)
{
    switch(fwdreason)
    {
        case DLL_PROCESS_ATTACH:
        {
            InitDLL(hinstDLL);
            LogMsg("ProcessHook");
            ProcessHook();
            break;
        }

        case DLL_PROCESS_DETACH:
           break;

    }

    return 1;
}
//---------------------------------------------------------------------------
