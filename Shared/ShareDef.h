//---------------------------------------------------------------------------

#ifndef ShareDefH
#define ShareDefH
//---------------------------------------------------------------------------
#include <VCL.h>

#define MSG_CONNECT      WM_USER+0x1129
#define MSG_DISCONNECT   WM_USER+0x1130
#define MSG_HINT         WM_USER+0x1131
#define MSG_SEND         WM_USER+0x1132
#define MSG_RECV         WM_USER+0x1133
#define MSG_KEY_UP       WM_USER+0x1134
#define MSG_TOP_WINDOW   WM_USER+0x1135
#define MSG_SESSIONKEY   WM_USER+0x1136
#define MSG_ADD_PACKAGE  WM_USER+0x1137
#define MSG_COMMANDLINE  WM_USER+0x1138

#define	PACKER_MAGIC "wowf"


enum    WOW_VERSION
{
	VERSION_GB = 1,
	VERSION_TW
};

void  SetTagFormClassName(String clsName);
bool	IsTagFormClassName(String clsName);

#define     SOCK_DLL				"ws2_32.dll"

#pragma pack(push, 1)
struct	tagWOWAddrInfo
{
	DWORD	Build;
	DWORD   Addr;
	DWORD   Offset;
	tagWOWAddrInfo(DWORD build, DWORD addr, DWORD offset)
	{
		Build = build;
		Addr = addr;
		Offset = offset;
	}
	tagWOWAddrInfo()
	{
		memset(this, 0, sizeof(*this));
	}
};
#pragma pack(pop)


#if defined(WOW_FISHER) && !defined(_DEBUG)
#else
static	const	int	gAddr_Table[][3] = {
	{10146, 0x01139F8C, 0xA14},
	{11159, 0xC923CC, 0xF14},
	{11723, 0xBB43FC, 0xF14},
	{12340, 0xC79CEC, 0xF14},
	{12484, 0x12705BC, 0xA14},
	{13507, 0xC79CEC, 0xF14},
	{13685, 0xC79CEC, 0xF14},
	{13930, 0xC79CEC, 0xF14},
	};
bool FindAddrInfo(int build, tagWOWAddrInfo *result);
#endif


String		GBText(String text);

#define		SESSIONKEY_SIZE			40
#define		HOST_IP					"127.0.0.1"

#ifdef WOW_FISHER
#define		HOST_PORT				33888
#else
#define		HOST_PORT				34888
#endif

#define		UDP_PORT_START			1000

#endif
