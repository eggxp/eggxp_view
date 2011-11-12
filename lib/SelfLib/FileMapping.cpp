//---------------------------------------------------------------------------
#include <vcl.h>
#include <Rtlconsts.HPP>
#pragma hdrstop

#include "FileMapping.h"
//---------------------------------------------------------------------------
void __fastcall CFileMappingStream::CreateFileMap(const String &AFileName, Word Mode)
{
    DWORD dwMappingProtect, dwMapViewDesiredAccess;
    if ( Mode == fmOpenRead )
    {
        dwMappingProtect = PAGE_READONLY;
        dwMapViewDesiredAccess = FILE_MAP_READ;
    }
    else
    {
        dwMappingProtect = PAGE_READWRITE;
        dwMapViewDesiredAccess = FILE_MAP_READ | FILE_MAP_WRITE;
    }
    m_hMapping = CreateFileMapping(m_hFile, NULL, dwMappingProtect, 0, 0, NULL);
    if ( m_hMapping == NULL )
    {
        CloseHandle(m_hFile);
        m_hFile = NULL;
		throw EFCreateError("Cannot create file mapping " + ExpandFileName(AFileName) + ". " + SysErrorMessage(GetLastError()), -1);
    }
    m_pBasePointer = MapViewOfFile(m_hMapping, dwMapViewDesiredAccess, 0, 0, 0);
    if ( m_pBasePointer == NULL )
    {
        CloseHandle(m_hMapping);
        CloseHandle(m_hFile);
        m_hMapping = NULL;
        m_hFile = NULL;
		throw EFCreateError("Cannot map view of file " + ExpandFileName(AFileName) + ". " + SysErrorMessage(GetLastError()), -1);
    }
    SetPointer(m_pBasePointer, GetFileSize(m_hFile, NULL));
}
//---------------------------------------------------------------------------
__fastcall CFileMappingStream::CFileMappingStream()
{
	m_pBasePointer = NULL;
	m_hMapping = NULL;
	m_hFile = NULL;
}
//---------------------------------------------------------------------------
__fastcall CFileMappingStream::CFileMappingStream(const String &AFileName, Word Mode)
{
	m_pBasePointer = NULL;
	m_hMapping = NULL;
	m_hFile = NULL;
	Open(AFileName, Mode);
}
//---------------------------------------------------------------------------
__fastcall CFileMappingStream::CFileMappingStream(const String &AFileName, Word Mode, unsigned Rights)
{
	m_pBasePointer = NULL;
	m_hMapping = NULL;
	m_hFile = NULL;
	if ( Mode == fmCreate )
	{
		m_hFile = (HANDLE)FileCreate(AFileName, Rights);
		if ( m_hFile == INVALID_HANDLE_VALUE )
			throw EFCreateError("Cannot create file " + ExpandFileName(AFileName) + ". " + SysErrorMessage(GetLastError()), -1);
    }
    else
    {
        m_hFile = (HANDLE)FileOpen(AFileName, Mode);
        if ( m_hFile == INVALID_HANDLE_VALUE )
            throw EFCreateError("Cannot open file " + ExpandFileName(AFileName) + ". " + SysErrorMessage(GetLastError()), -1);
    }
    CreateFileMap(AFileName, Mode);
}
//---------------------------------------------------------------------------
__fastcall CFileMappingStream::~CFileMappingStream(void)
{
	Close();
}
//---------------------------------------------------------------------------
int __fastcall CFileMappingStream::Write(const void *Buffer, int Count)
{
    return 0;
}
//---------------------------------------------------------------------------
void __fastcall CFileMappingStream::Open(const String &AFileName, Word Mode)
{
	m_hFile = (HANDLE)FileOpen(AFileName, Mode);
	if ( m_hFile == INVALID_HANDLE_VALUE )
		throw EFCreateError("Cannot open file " + ExpandFileName(AFileName) + ". " + SysErrorMessage(GetLastError()), -1);
	CreateFileMap(AFileName, Mode);
}
//---------------------------------------------------------------------------
void __fastcall	CFileMappingStream::Close()
{
	if ( m_pBasePointer != NULL )
		UnmapViewOfFile(m_pBasePointer);
	if ( m_hMapping != NULL )
		CloseHandle(m_hMapping);
	if ( m_hFile != NULL )
		CloseHandle(m_hFile);
	m_pBasePointer = NULL;
	m_hMapping = NULL;
	m_hFile = NULL;
}
//---------------------------------------------------------------------------

