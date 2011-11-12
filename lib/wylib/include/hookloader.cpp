//---------------------------------------------------------------------------


#pragma hdrstop

#include "CommFunc.h"
#define AppDllName   "hs.dll"

//---------------------------------------------------------------------------
#pragma package(smart_init)
//---------------------------------------------------------------------------
__fastcall THookLoader::THookLoader(TForm *Parent,TOnHOOKMsg MsgOutputProc,Classes::TWndMethod ParentDefWndProc)
{
    //初始化宿主窗口
    m_Parent = Parent;

    m_fpOnHookMsg = MsgOutputProc;
    //替换宿主窗口的消息处理函数
    m_fpParentDefWndProc = ParentDefWndProc; //保存宿主窗口默认的消息处理函数
    m_fpOrgWndProc = m_Parent->WindowProc;   //保存宿主窗口用户定义的消息处理函数
    m_Parent->WindowProc = ParentFormWndProc;   //替换
    //初始化HOOK DLL
    m_fpMsgHookfunc      = NULL;
    m_fpCBTHookfunc      = NULL;
    pfOnTagConnect    = NULL;
	pfOnTagDisconnect = NULL;
    pfOnTagKeydown    = NULL;
    pfOnNetDataOP= NULL;
    String  DllPath = ExtractFilePath(Application->ExeName) + "dLoader.dll";
	m_InjectDll = LoadLibrary(DllPath.c_str());
    if(m_InjectDll)
    {              
        m_fpMsgHookfunc = (SET_MSG_HOOK) GetProcAddress(m_InjectDll, "SetMsgHook");
        m_fpCBTHookfunc = (SET_CBT_HOOK) GetProcAddress(m_InjectDll, "SetCBTHook");
		LogMsg(FormatStr("Load dLoader.dll Success!MsgHookFunc Addr:%x,CBTHookFunc:%x",m_fpMsgHookfunc,m_fpCBTHookfunc));
    }
    else
    {
		LogMsg("Load dLoader.dll Fail!");
        m_fpMsgHookfunc = NULL;
        m_fpCBTHookfunc = NULL;
	}
	//初始化成员变量
	m_FindWindowMode = fwmCLASS;
    m_AppDllRunning = false;
    timHookDetector = new TTimer(NULL);
    timHookDetector->Interval = 300;
    timHookDetector->Enabled = false;
    timHookDetector->OnTimer = OnHookDetectorTimer;
    m_State = hsNOTACTIVE;
    m_HookType = htMSGHOOK;
}
//---------------------------------------------------------------------------
__fastcall THookLoader::~THookLoader()
{
    timHookDetector->Enabled = false; 
    if(m_InjectDll)
    {
        m_fpMsgHookfunc = NULL;
        m_fpCBTHookfunc = NULL;
        FreeLibrary(m_InjectDll);
    }

    delete timHookDetector;
}
//---------------------------------------------------------------------------
int __fastcall THookLoader::LoadDLL(String AppDllPath)
{
  HWND  TagWindow;
  DWORD TagThreadId = 0;
  if(m_fpMsgHookfunc)
  {
    TagWindow = FindTagWindow();
    if(TagWindow == NULL)
      return 2; //目标窗口未找到
    TagThreadId = GetWindowThreadProcessId(TagWindow, NULL);
    if(TagThreadId == 0)
      return 3; //获取目标线程ID失败
    if(m_fpMsgHookfunc(TagThreadId, m_Parent->Handle, AppDllPath.c_str()))
    {
      //取消金庸窗口总在最前面的属性
      SetWindowPos(TagWindow,HWND_NOTOPMOST,0,0,0,0,SWP_NOACTIVATE | SWP_SHOWWINDOW | SWP_NOMOVE | SWP_NOSIZE);
      return 0; //成功挂钩
    }
    else
      return 4; //挂钩函数失败
  }

  return 1;     //加载注入DLL失败
}
//---------------------------------------------------------------------------
void THookLoader::LogMsg(const String &Msg)
{
    if (m_fpOnHookMsg)
	{
       m_fpOnHookMsg(Msg);
    }
}
//---------------------------------------------------------------------------
void __fastcall THookLoader::ParentFormWndProc(Messages::TMessage &Message)
{
	if(Message.Msg == LOAD_DLL_SUCCED)              //应用DLL加载完成,卸载推送挂钩dll
    {
		if(m_HookType == htMSGHOOK)
		{
			if(m_fpMsgHookfunc)
            {
				m_fpMsgHookfunc(0, m_Parent->Handle, 0);
            }
        }
        else
        {
			if(m_fpCBTHookfunc)
            {
                m_fpCBTHookfunc(false, NULL, m_Parent->Handle, 0);
			}
        }
        m_AppDllRunning = true;
		LogMsg("LOAD_DLL_SUCCED!");
    }
	else if(Message.Msg == INSTALL_HOOK_SUCCED)     //挂钩完成
    {
		LogMsg("INSTALL_HOOK_SUCCED!");
    }
	else if(Message.Msg == UNINSTALL_HOOK_SUCCED)   //解挂钩完成
    {
		LogMsg("UNINSTALL_HOOK_SUCCED!");
	}
	else if(Message.Msg == LOAD_DLL_FAIL)
	{
	    //错误编号含义
		//#define ERROR_OPENSHAREOBJ_FAIL  8811     //1=无法打开内存文件映射,2=MapViewOfFile失败
		//#define ERROR_LOAD_USERDLL_FAIL  8812     //param值为LoadLibrary错误返回码
		//#define ERROR_CREATESHAREOBJ_FAIL  8813 //创建内存文件映射失败,1=无法创建,2=映射已经存在,3=调用MapViewOfFile失败
		LogMsg(FormatStr("LOAD_DLL_FAIL,error=%d,errorInfo=%d",Message.WParam,Message.LParam));
    }
    else if(Message.Msg == WM_COPYDATA)             //热键消息处理
    {
        int             DataLen;
        PCOPYDATASTRUCT lpData;
        lpData = PCOPYDATASTRUCT(Message.LParam);
        ProcMsgData(lpData->dwData, lpData->lpData, lpData->cbData);
    }
    else
    {
        if(m_fpOrgWndProc)
        {
            m_fpOrgWndProc(Message);
        }
        else
        {
            m_fpParentDefWndProc(Message);
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall THookLoader::ProcMsgData(int Flag, void *lpData, int Len)
{
    if(Len <= 0)
        return;
    if(Flag == MSG_KEY_UP)
    {
        DWORD   KeyDown = *(LPDWORD(lpData));
        if(pfOnTagKeydown)
        {
            pfOnTagKeydown(KeyDown);
        }

        return;
    }
    else if(Flag == MSG_HINT)
    {
        LogMsg(String((char *)lpData, Len));
    }
    else if(Flag == MSG_SEND)
    {
        if (pfOnNetDataOP)
        {
          pfOnNetDataOP(noSEND,(char *)lpData,Len);
        }

        //LogMsg(String((char *)lpData, Len));
    }
    else if(Flag == MSG_RECV)
    {
        if (pfOnNetDataOP)
        {
          pfOnNetDataOP(noRECV,(char *)lpData,Len);
        }
    }
    else if(Flag == MSG_CONNECT)
    {
        tagSERVERINFO   *lpServerInfo;
        lpServerInfo = (tagSERVERINFO *)lpData;
        if(pfOnTagConnect)
        {
            pfOnTagConnect(lpServerInfo);
        }
    }
    else if(Flag == MSG_DISCONNECT)
    {
        if(pfOnTagDisconnect)
        {
            pfOnTagDisconnect(*(SOCKET *)lpData);
        }
    }
    else
    {
		LogMsg(FormatStr("unknow copydata :%d",Flag));
    }

}
//---------------------------------------------------------------------------
HWND	THookLoader::FindTagWindow()
{
   if (m_FindWindowMode == fwmCLASS)
   {
	 return FindWindow(TagFormClass.c_str(), NULL);
   }
   else if(m_FindWindowMode == fwmNAME)
   {
	 return FindWindow(NULL, TagFormName.c_str());
   }
   else
   {
	 return FindWindow(TagFormClass.c_str(), TagFormName.c_str());
   }
}
//---------------------------------------------------------------------------
void __fastcall THookLoader::OnHookDetectorTimer(TObject *Sender)
{
	HWND    TagWindow = FindTagWindow();
    if(TagWindow == NULL)
    {
        m_AppDllRunning = false;
        m_State = hsDETECTOR_TAG;
    }
    else
    {
        if(m_AppDllRunning)
        {
            m_State = hsTAGRUNNING;
            return;
        }

        String  AppDllPath;
        int     ErrorCode;
        AppDllPath = ExtractFilePath(Application->ExeName) + AppDllName;
        ErrorCode = LoadDLL(AppDllPath);
        if(ErrorCode != 0)
			LogMsg(FormatStr("load dll %s fail,error=%d ",AppDllPath,ErrorCode));
    }
}
//---------------------------------------------------------------------------
void THookLoader::SetActive(bool IsActive)
{
   if (htMSGHOOK == m_HookType)
   {
      timHookDetector->Enabled =IsActive;
   }
   else
   {
      //取消Hook timer,CBT HOOK不需要Hook Timer
      timHookDetector->Enabled = false;
      if (m_fpCBTHookfunc)
      {
          String AppDllPath = ExtractFilePath(Application->ExeName) + AppDllName;
          if (FileExists(AppDllPath))
          {
             m_State = hsDETECTOR_TAG;
             m_fpCBTHookfunc(true,TagExeName.c_str(),m_Parent->Handle, AppDllPath.c_str());
          }
      }
   }
}

