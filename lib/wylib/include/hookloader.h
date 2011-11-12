//---------------------------------------------------------------------------

#ifndef hookloaderH
#define hookloaderH
#include <vcl.h>
#include <ScktComp.hpp>
#define  LOAD_DLL_SUCCED WM_USER+0x9111
#define  LOAD_DLL_FAIL   WM_USER+0x9112
#define  INSTALL_HOOK_SUCCED  WM_USER+0x9121  //自定义消息,通知主程序钩子加载成功
#define  UNINSTALL_HOOK_SUCCED  WM_USER+0x9122  //自定义消息,通知主程序钩子加载成功
#define MSG_CONNECT      WM_USER+0x1129
#define MSG_DISCONNECT   WM_USER+0x1130
#define MSG_HINT         WM_USER+0x1131
#define MSG_SEND         WM_USER+0x1132
#define MSG_RECV         WM_USER+0x1133
#define MSG_KEY_UP       WM_USER+0x1134


struct tagSERVERINFO
{
  char      IP[20];
  WORD      Port;
  SOCKET    SocketId;
};
typedef BOOL WINAPI (*SET_MSG_HOOK) (DWORD, HWND, char *);
typedef BOOL WINAPI (*SET_CBT_HOOK)(bool IsActive,char *TagExeName,HWND HostWindow,char *AppDllName);
typedef void __fastcall (__closure *TOnHOOKMsg)(const String &Msg);
typedef void __fastcall (__closure *TOnTagConnect)(tagSERVERINFO *lpServerInfo);
typedef void __fastcall (__closure *TOnTagDisconnect)(SOCKET    SocketId);
typedef void __fastcall (__closure *TOnTagHotKey)(DWORD KeyValue);
typedef void __fastcall (__closure *TOnDataOP)(int OPType,char *Data,int DataLen);
enum{hsNOTACTIVE=0,hsDETECTOR_TAG,hsTAGRUNNING};

enum HOOKType{htMSGHOOK=0,htCBTHOOK};

enum NETOPType{noSEND=0,noRECV};
enum FIND_WINDOW_MODE{fwmCLASS,fwmNAME,fwmBOTH};
//此模块用来加载HOOK dll
//---------------------------------------------------------------------------
class THookLoader
{

private:
  TForm      *  m_Parent;
  HINSTANCE     m_InjectDll;
  bool          m_AppDllRunning;
  TTimer        * timHookDetector;
  int           m_State; //当前工作状态
  HOOKType      m_HookType; //挂钩方式
protected:
  SET_MSG_HOOK           m_fpMsgHookfunc;
  SET_CBT_HOOK           m_fpCBTHookfunc;
  Classes::TWndMethod  m_fpOrgWndProc;
  Classes::TWndMethod  m_fpParentDefWndProc;
  TOnHOOKMsg           m_fpOnHookMsg;
  FIND_WINDOW_MODE	   m_FindWindowMode;
  void __fastcall      ParentFormWndProc(Messages::TMessage &Message);
  void __fastcall      ProcMsgData(int Flag,void *lpData,int Len);
  void __fastcall      OnHookDetectorTimer(TObject *Sender);
  int __fastcall       LoadDLL(String AppDllPath);
  void                 LogMsg(const String &Msg);
  HWND				   FindTagWindow();

public:
  TOnTagConnect        pfOnTagConnect;          //目标程序连接成功 事件
  TOnTagDisconnect     pfOnTagDisconnect;       //目标程序断开连接 事件
  TOnTagHotKey         pfOnTagKeydown;          //目标程序按下热键 事件
  TOnDataOP            pfOnNetDataOP;           //网络数据传输操作
  String               TagFormClass;
  String			   TagFormName;		//目标窗口名
  String               TagExeName;
public:
  __fastcall THookLoader(TForm * Parent,TOnHOOKMsg MsgOutputProc,Classes::TWndMethod ParentDefWndProc);
  __fastcall ~THookLoader();
  void SetActive(bool IsActive);
  __inline int  State(){return m_State;}
  __inline HOOKType GetHookType(){return m_HookType;}
  __inline void SetHookType(HOOKType HookType){m_HookType=HookType;}
  __inline void SetFindWindowMode(FIND_WINDOW_MODE Mode){m_FindWindowMode = Mode;}
};

#endif
