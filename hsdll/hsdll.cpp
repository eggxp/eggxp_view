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

//
//
//	if(port == 80)
//	{
//		needRedirect = 0;
//	}
//	else
//	{
//		needRedirect = 1;
//	}
////	for(DWORD i=0; i<gRedirectPort.size(); i++)
////	{
////		if(gRedirectPort[i] == port)
////		{
////			needRedirect = 1;
////            break;
////        }
////    }
//
//    if(!needRedirect)
//    {
//        LogMsg("no redirect");
//        nReturn = connect(s, name, namelen);
//        HookOnOne(&gConnectHookData);
//
//		LogMsg(FormatStr("no redirect. nReturn = %d, LastError = %d", nReturn, WSAGetLastError()));
//        return nReturn;
//    }
//
//    if((gConnectPortList.size() > 1 && gConnectPortList[0].Equal(ip, port)))
//    {
//        // 连接realm, 第一个连接
//        gConnectPortList.clear();
//        gWOWHookViewInfo->ForbiddenAnyMortConnection = 0;
//    }
//
//    if(gWOWHookViewInfo->ClientConnectIndex == -10)
//    {
//        LogMsg("gConnectPortList.clear()");
//        gConnectPortList.clear();
//    }
//	gWOWHookViewInfo->ClientConnectIndex = -1;
//    for(DWORD i=0; i<gConnectPortList.size(); i++)
//    {
//        if(gConnectPortList[i].Equal(ip, port))
//        {
//            gWOWHookViewInfo->ClientConnectIndex = i;
//        }
//    }
//    if(gWOWHookViewInfo->ClientConnectIndex == -1)
//    {
//        gConnectPortList.push_back(tagConnectInfo(ip, port));
//        gWOWHookViewInfo->ClientConnectIndex = gConnectPortList.size() - 1;
//    }
//
//    int connectPort = gConnectPort;
//    if(gWOWHookViewInfo->ClientConnectIndex > 0)
//	{
//        //现在连接WorldServer了
//        AnsiString sessionKey;
//        int keyLen = SESSIONKEY_SIZE;
//        sessionKey.SetLength(keyLen);
//        void    *   baseAddr = NULL;
//        int         offset = 0;
//
//		baseAddr = (void *)gWOWHookViewInfo->BaseAddr;
//		offset = gWOWHookViewInfo->BaseAddrOffset;
//
//        if(baseAddr != 0 && offset != 0)
//        {
//            BYTE    readBuf[4] = {0};
//            ReadProcessMemory(GetCurrentProcess(), baseAddr, readBuf, sizeof(readBuf), 0);
//            int pos = 0;
//            void *   memoryAddr = (void *)ReadDWORD(readBuf, pos);
//            void * keyAddr = (BYTE *)memoryAddr + offset;
//            ReadProcessMemory(GetCurrentProcess(), keyAddr, sessionKey.c_str(), sessionKey.Length(), 0);
//            if (sessionKey.c_str()[0] == 0 && sessionKey.c_str()[1] == 0)
//            {
//                LogMsg("Null Session Key!");
//                LogMsg(BinToStr(sessionKey.c_str(), sessionKey.Length()));
//                gWOWHookViewInfo->ClientConnectIndex = 0;
//            }
//            else
//            {
//                LogMsg(BinToStr(sessionKey.c_str(), sessionKey.Length()), MSG_SESSIONKEY);
//            }
//        }
//        else
//        {
//            LogMsg("Input Session Key!");
//        }
//    }
//
//    String connectIP = HOST_IP;
//
//    // 这句控制是否允许新增连接
//    gWOWHookViewInfo->ForbiddenAnyMortConnection = 1;
//    if(gWOWHookViewInfo->ClientConnectIndex > 1 && gWOWHookViewInfo->ForbiddenAnyMortConnection)
//    {
//        connectPort = 0;
//        LogMsg(FormatStr("<FORCE_NO_REDIRECT>IP=%s,Port=%d,nonblocking=%d!connectIndex = %d", ip, port, nonBlocking, gWOWHookViewInfo->ClientConnectIndex));
//    }
//    else
//    {
//        LogMsg(FormatStr("<REDIRECT>IP=%s,Port=%d,nonblocking=%d!", connectIP, connectPort, nonBlocking));
//        //通知proxy设置目标的地点
//        LogMsg(FormatStr("%s|%d|%d", ip, port, gWOWHookViewInfo->ClientConnectIndex), MSG_CONNECT);
//    }
//
//    sockaddr_in * their_addr = (sockaddr_in *)name;
//	their_addr->sin_port = htons(connectPort);
//	AnsiString ansiIP = connectIP;
//    their_addr->sin_addr.s_addr=inet_addr(ansiIP.c_str());
//
//
//    nReturn = connect(s, name, namelen);
//
//
//	//注意: 不要摄入封包流逻辑, 不要在这里主动发包..
//	HookOnOne(&gConnectHookData);
//
//
//	return nReturn;
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
//  UDP Hook
void CheckConnectUDPToTCP(const struct sockaddr FAR * dest, bool is_wsa)
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
	if(is_wsa == false)
	{
		LogMsg(FormatStr("udp|%s|%d|%d", sendtoIP, sendtoPort, gWOWHookViewInfo->ClientConnectIndex), MSG_CONNECT);
	}
	else
	{
		LogMsg(FormatStr("wsaudp|%s|%d|%d", sendtoIP, sendtoPort, gWOWHookViewInfo->ClientConnectIndex), MSG_CONNECT);
	}
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
	CheckConnectUDPToTCP(to, false);
	AnsiString ansiIP = HOST_IP;
	sockaddr_in * their_addr = (sockaddr_in *)to;
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
	their_addr->sin_port = htons(gConnectPort + UDP_PORT_START);
	their_addr->sin_addr.s_addr=inet_addr(ansiIP.c_str());
	int nReturn = recvfrom(s, buf, len, flags, from, fromlen);
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
//	if (lpTo) {
//		WORD hport = (BYTE)lpTo->sa_data[0];
//		WORD lport = (BYTE)lpTo->sa_data[1];
//		hport *= 0x100;
//		WORD   port = hport + lport;
//		String  ip=FormatStr("%d.%d.%d.%d", (BYTE)lpTo->sa_data[2],
//											(BYTE)lpTo->sa_data[3],
//											(BYTE)lpTo->sa_data[4],
//											(BYTE)lpTo->sa_data[5]);
//		if (ip != "1.0.0.0")
//		{
//			LogMsg(FormatStr("sendto|%s|%d|%s", ip, port, BinToStr((char FAR * )lpBuffers, dwBufferCount)), MSG_ADD_PACKAGE);
//		}
//	}
	HookOffOne(&gWSASendToHookData);
//	{
//	    // 调试
//		int nReturn = WSASendTo(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent,
//								dwFlags, lpTo, iTolen, lpOverlapped, lpCompletionRoutine);
//		if(nReturn == 0)
//		{
////			LogMsg(FormatStr("send:%d, %d", *lpNumberOfBytesSent, lpBuffers->len));
//			LogMsg(FormatStr("sendto| |0|%s", BinToStr((char FAR * )lpBuffers->buf, *lpNumberOfBytesSent)), MSG_ADD_PACKAGE);
//		}
//		HookOnOne(&gWSASendToHookData);
//
//		return nReturn;
//	}

	CheckConnectUDPToTCP(lpTo, false);
	AnsiString ansiIP = HOST_IP;
	sockaddr_in * their_addr = (sockaddr_in *)lpTo;

	their_addr->sin_port = htons(gConnectPort + UDP_PORT_START);
	their_addr->sin_addr.s_addr=inet_addr(ansiIP.c_str());
	int nReturn = WSASendTo(s, lpBuffers, dwBufferCount, lpNumberOfBytesSent,
							dwFlags, lpTo, iTolen, lpOverlapped, lpCompletionRoutine);
	HookOnOne(&gWSASendToHookData);

	if(nReturn == 0)
	{
		if(dwBufferCount > 1)
		{
			LogMsg(FormatStr("sendto, dwBufferCount = %d", dwBufferCount));
		}
		for (DWORD i=0; i<dwBufferCount; i++)
		{
			LogMsg(FormatStr("sendto| |%d|%s", i, BinToStr((char FAR * )lpBuffers[i].buf, lpBuffers[i].len)), MSG_ADD_PACKAGE);
		}
//		LogMsg(FormatStr("sendto dwFlags = %d", dwFlags));
//		LogMsg(FormatStr("sendto lpTo = %d", lpTo));
//		LogMsg(FormatStr("sendto iTolen = %d", iTolen));
//		LogMsg(FormatStr("sendto lpOverlapped = %d", lpOverlapped));
//		LogMsg(FormatStr("sendto lpCompletionRoutine = %d", lpCompletionRoutine));
	}
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
////			LogMsg(FormatStr("recv:%d, %d", *lpNumberOfBytesRecvd, lpBuffers->len));
//			LogMsg(FormatStr("recvfrom| |0|%s", BinToStr((char FAR * )lpBuffers->buf, *lpNumberOfBytesRecvd)), MSG_ADD_PACKAGE);
//		}
//		HookOnOne(&gWSARecvFromHookData);
//		return nReturn;
//	}
	AnsiString ansiIP = HOST_IP;
	sockaddr_in * their_addr = (sockaddr_in *)lpFrom;

	their_addr->sin_port = htons(gConnectPort + UDP_PORT_START);
	their_addr->sin_addr.s_addr=inet_addr(ansiIP.c_str());
	int nReturn = WSARecvFrom(s, lpBuffers, dwBufferCount, lpNumberOfBytesRecvd,
								lpFlags, lpFrom, lpFromlen, lpOverlapped, lpCompletionRoutine);
	HookOnOne(&gWSARecvFromHookData);

	if(nReturn == 0)
	{
		if(dwBufferCount > 1)
		{
			LogMsg(FormatStr("recvfrom, dwBufferCount = %d", dwBufferCount));
		}
		LogMsg(FormatStr("recvfrom| |0|%s", BinToStr((char FAR * )lpBuffers[0].buf, *lpNumberOfBytesRecvd)), MSG_ADD_PACKAGE);
//		LogMsg(FormatStr("recvfrom lpFlags = %d", *lpFlags));
//		LogMsg(FormatStr("recvfrom lpFrom = %d", lpFrom));
//		LogMsg(FormatStr("recvfrom lpFromlen = %d", lpFromlen));
//		LogMsg(FormatStr("recvfrom lpOverlapped = %d", lpOverlapped));
//		LogMsg(FormatStr("recvfrom lpCompletionRoutine = %d", lpCompletionRoutine));
	}
	return nReturn;
}
//////////////////////////////END///////////////////////////////

void        ProcessHook()
{
	String libStr = SOCK_DLL;
//    HANDLE libHandle = LoadLibrary(libStr.c_str());
//    if(libHandle == NULL)
//    {
//        LogMsg("Hook Failed, libHandle == NULL");
//        return;
//    }
//    String fPort = gLoadIni->ReadString("SET", "HackPort", "");
//    auto_ptr<TStringList> splitStr(new TStringList);
//    SplitStr(fPort, ",", splitStr.get());

//    int rPort = 0;
//    for(int i=0; i<splitStr->Count; i++)
//    {
//        rPort = splitStr->Strings[i].Trim().ToIntDef(0);
//        if(rPort == 0)
//            continue;
//        LogMsg(FormatStr("Add Redirect : %d", rPort));
//        gRedirectPort.push_back(rPort);
//    }
               

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
