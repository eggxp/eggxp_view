//---------------------------------------------------------------------------


#pragma hdrstop

#include "CommPlus.h"
#include "Log4Me.h"
#include "ThreadManager.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

AnsiString  StrHeadInsertBuf(AnsiString src, void  *buf, int bufLen)
{
	AnsiString data;
    data.SetLength(src.Length() + bufLen);

    int pos = 0;
    WriteBuf(data.c_str(), pos, buf, bufLen);
    WriteBuf(data.c_str(), pos, src.c_str(), src.Length());

    return data;
}

AnsiString  StrHeadInsertBYTE(AnsiString src, BYTE head)
{
	AnsiString data;
    data.SetLength(src.Length() + sizeof(BYTE));

    int pos = 0;
    WriteBYTE(data.c_str(), pos, head);
    WriteBuf(data.c_str(), pos, src.c_str(), src.Length());

    return data;
}

AnsiString  StrHeadInsertWORD(AnsiString src, WORD head)
{
    AnsiString data;
    data.SetLength(src.Length() + sizeof(WORD));

    int pos = 0;
    WriteWORD(data.c_str(), pos, head);
    WriteBuf(data.c_str(), pos, src.c_str(), src.Length());

    return data;
}

AnsiString  StrHeadInsertDWORD(AnsiString src, DWORD head)
{
    AnsiString data;
    data.SetLength(src.Length() + sizeof(DWORD));

    int pos = 0;
    WriteDWORD(data.c_str(), pos, head);
    WriteBuf(data.c_str(), pos, src.c_str(), src.Length());

    return data;
}

int GetFileDirList(const String &DirName,TStrings *ResultList,bool SubDir)
{
    TSearchRec sr;
    String PathStr = DirName+"\\*.*";
    int  FileCount = 0;
    if (FindFirst(PathStr,faAnyFile,sr) == 0)
    {
        do
        {
            if (sr.Name=="." || sr.Name=="..")
            {
                continue;
            }
            if ((sr.Attr & faDirectory) == faDirectory)
            {
                FileCount++;
                ResultList->Add(DirName+"\\"+sr.Name);
                if (SubDir)
                {
                    GetFileDirList(DirName+"\\"+sr.Name,ResultList,true);
                }
            }
        } while (FindNext(sr) == 0);
        FindClose(sr);
    }
    return  FileCount;
}



int EnableDebugPriv(String name)
{
    HANDLE hToken;
    TOKEN_PRIVILEGES tp;
    LUID luid;
    //打开进程令牌环
    OpenProcessToken(GetCurrentProcess(),
        TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY,
        &hToken);
    //获得进程本地唯一ID
    LookupPrivilegeValue(NULL,name.c_str(),&luid) ;
    
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    tp.Privileges[0].Luid = luid;
    //调整权限
    AdjustTokenPrivileges(hToken,0,&tp,sizeof(TOKEN_PRIVILEGES),NULL,NULL);
    return 0;
}


//*****************************************************************************************************************************
static      DllInjecter         *  gDllInjecter = NULL;

DllInjecter *       GetDllInjecter()
{
    if(gDllInjecter == NULL)
    {
        gDllInjecter = new DllInjecter;
    }
    return  gDllInjecter;
}

DllInjecter::DllInjecter()
{
	fpFindWindowFunc = NULL;
	fpInjectOK = NULL;
    m_FindTimer = new TTimer(NULL);
    m_FindTimer->OnTimer = OnFindTimer;
	m_FindTimer->Interval = 1000;
	m_ProcessID = 0;
	m_hProcess = NULL;
}

DllInjecter::~DllInjecter()
{
    delete m_FindTimer;
}

void __fastcall         DllInjecter::OnFindTimer(System::TObject* Sender)
{
    ProcessInject();
}

void					DllInjecter::SetActiveInject(bool active)
{
	m_FindTimer->Enabled = active;
}

bool				   	DllInjecter::GetIsActiveInject()
{
	return	m_FindTimer->Enabled;
}

DWORD					DllInjecter::GetInjectProcessID()
{
	return	m_ProcessID;
}

void                    DllInjecter::ProcessInject()
{
	HANDLE  hWnd = NULL;
	ASSERT(fpFindWindowFunc)
	hWnd = fpFindWindowFunc();
    if(hWnd == NULL)
    {
        return;
    }

    GetWindowThreadProcessId(hWnd, &m_ProcessID);

	if(m_ProcessID == 0)
	{
		return;
	}

	if(!ProcessExists(m_ProcessID))
		return;

	BOOL result;

    EnableDebugPriv(SE_DEBUG_NAME);
	//打开远程线程
	m_hProcess = OpenProcess( PROCESS_ALL_ACCESS, FALSE, m_ProcessID );
	if(!m_hProcess)
	{
		GetLog()->Info("OpenProcess Failed. %s", SysErrorMessage(GetLastError()));
		return;
	}
    
    char *pszLibFileRemote;
    
	//使用VirtualAllocEx函数在远程进程的内存地址空间分配DLL文件名空间
	AnsiString pathName = m_DllFullPath;
	GetLog()->Info("Inject Dll Path = %s", m_DllFullPath.c_str());
	pszLibFileRemote = (char *) VirtualAllocEx( m_hProcess, NULL, pathName.Length(),
		MEM_COMMIT, PAGE_READWRITE);

	if(!pszLibFileRemote)
	{
		GetLog()->Info("VirtualAllocEx Failed. %s", SysErrorMessage(GetLastError()));
		return;
	}

	//使用WriteProcessMemory函数将DLL的路径名写入到远程进程的内存空间
    result = WriteProcessMemory(m_hProcess,
		pszLibFileRemote, (void *) pathName.c_str(), pathName.Length(), NULL);
	if(!result)
	{
		GetLog()->Info("WriteProcessMemory Failed. %s", SysErrorMessage(GetLastError()));
		return;
	}
    
    //##############################################################################
    //计算LoadLibraryA的入口地址
    PTHREAD_START_ROUTINE pfnStartAddr = (PTHREAD_START_ROUTINE)
		GetProcAddress(GetModuleHandle(TEXT("Kernel32")), "LoadLibraryA");
	if(!pfnStartAddr)
	{
		GetLog()->Info("Load Library Failed!. %s", SysErrorMessage(GetLastError()));
		return;
	}
    //(关于GetModuleHandle函数和GetProcAddress函数)
    
    //启动远程线程LoadLibraryA，通过远程线程调用创建新的线程
    HANDLE hRemoteThread = CreateRemoteThread( m_hProcess, NULL, 0, pfnStartAddr, pszLibFileRemote, 0, NULL);
	if( hRemoteThread != NULL)
    {
		GetLog()->Info("inject OK!");
	}
	else
	{
        GetLog()->Info("inject Fail! %s", SysErrorMessage(GetLastError()));
    }
    
    
    //##############################################################################
    
    /*
    // 在//###.....//###里的语句也可以用如下的语句代替:
    DWORD dwID;
    LPVOID pFunc = LoadLibraryA;
    HANDLE hRemoteThread = CreateRemoteThread(m_hProcess, NULL, 0, (LPTHREAD_START_ROUTINE)pFunc, pszLibFileRemote, 0, &dwID );
    //是不是感觉简单了很多
    */
    
    // 释放句柄
    
//	CloseHandle(m_hProcess);
	CloseHandle(hRemoteThread);

	if(fpInjectOK)
	{
		fpInjectOK();
	}

	GetThreadManager()->AddGUIMessage("Process Init OK!");
    m_FindTimer->Enabled = false;
}

void                    DllInjecter::InjectDll(String       DllFullPath)
{
    m_DllFullPath = DllFullPath;
    m_FindTimer->Enabled = true; 

}
