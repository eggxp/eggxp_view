//---------------------------------------------------------------------------


#pragma hdrstop

#include "SharedMemInfo.h"
#include "CommFunc.h"
#include "Log4Me.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

#define MAX_WOW_WND_COUNT       100
#define FILE_MAP_NAME   __TEXT("WOWInfo")

static  SharedMemInfo   gSharedMemInfo;




SharedMemInfo   *   GetSharedMemInfo()
{
    return  &gSharedMemInfo;
}

SharedMemInfo::SharedMemInfo()
{
	m_InitOK = false;
    m_hMutex = CreateMutex(NULL, FALSE, __TEXT("WOWMutex"));
    if(!m_hMutex)
    {
        ShowMessage(FormatStr("Mutex Error:%s", SysErrorMessage(GetLastError())));
    }
    m_hFile = NULL;
    m_lpData = NULL;
}

bool            SharedMemInfo::CreateMapping()
{
    MutexLock h(m_hMutex);
    m_hFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(WOWHookViewInfo) * MAX_WOW_WND_COUNT, FILE_MAP_NAME);
    if(!m_hFile)
    {
        ShowMessage(FormatStr("CreateMapping Error:%s", SysErrorMessage(GetLastError())));
        return false;
    }

    m_lpData = MapViewOfFile(m_hFile, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
    if(!m_lpData)
    {
        ShowMessage(FormatStr("MapViewOfFile Error:%s", SysErrorMessage(GetLastError())));
        return false;
    }

	m_InitOK = true;
    return  true;
}

bool            SharedMemInfo::OpenMapping()
{
    MutexLock h(m_hMutex);
    m_hFile = OpenFileMapping(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, FILE_MAP_NAME);
    if(!m_hFile)
    {
        ShowMessage(FormatStr("OpenMapping Error:%s", SysErrorMessage(GetLastError())));
        return false;
    }

    m_lpData = MapViewOfFile(m_hFile, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, 0);
    if(!m_lpData)
    {
        ShowMessage(FormatStr("MapViewOfFile Error:%s", SysErrorMessage(GetLastError())));
        return false;
    }

	m_InitOK = true;
    return  true;
}

SharedMemInfo::~SharedMemInfo()
{
    if(m_hMutex)
    {
        CloseHandle(m_hMutex);
    }
    if(m_lpData)
    {
        UnmapViewOfFile(m_lpData);
    }
    if(m_hFile)
    {
        CloseHandle(m_hFile);
    }
}

WOWHookViewInfo *   SharedMemInfo::GetAt(int index)
{
    MutexLock h(m_hMutex);
    return  (WOWHookViewInfo *)((char *)m_lpData + sizeof(WOWHookViewInfo) * index);
}

int             SharedMemInfo::GetCount()
{
    return  MAX_WOW_WND_COUNT;
}

WOWHookViewInfo *   SharedMemInfo::FindSelf()
{
    MutexLock h(m_hMutex);
    WOWHookViewInfo * data;
	for(int i=0; i<this->GetCount(); i++)
	{
		data = this->GetAt(i);
		if(!data)
			continue;
		if((data->HostProcessID == GetCurrentProcessId()) ||
			(data->DestProcessID == GetCurrentProcessId()))
		{
			return data;
		}
	}

	GetLog()->Warn("GetCurrentProcessId() = %d", GetCurrentProcessId());
    for(int i=0; i<this->GetCount(); i++)
	{
		data = this->GetAt(i);
		if(data->HostProcessID)
		{
			GetLog()->Warn("%d, HostProcessID:%d, DestProcessID:%d", i, data->HostProcessID, data->DestProcessID);
		}
	}
    return  NULL;
}

WOWHookViewInfo *   SharedMemInfo::CreateEmpty(int baseListenPort)
{
    MutexLock h(m_hMutex);
    WOWHookViewInfo * data;

    int maxPort = baseListenPort;
    for(int i=0; i<this->GetCount(); i++)
    {
        data = this->GetAt(i);
        if((int)data->HostPortNumber >= maxPort)
        {
            maxPort = data->HostPortNumber+1;
        }
    }

    for(int i=0; i<this->GetCount(); i++)
    {
        data = this->GetAt(i);
        if(data->IsEmpty())
        {
            data->HostProcessID = GetCurrentProcessId();
            data->HostPortNumber = maxPort;
            return data;
        }
    }
    return NULL;
}

WOWHookViewInfo *   SharedMemInfo::GetTagMapping(int destProcessID)
{
    WOWHookViewInfo * data;
    for(int i=0; i<this->GetCount(); i++)
    {
        data = this->GetAt(i);
        if((int)data->DestProcessID == destProcessID)
        {
            return data;
        }
    }
    return NULL;
}

