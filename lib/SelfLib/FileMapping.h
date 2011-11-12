//---------------------------------------------------------------------------
#ifndef FileMappingH
#define FileMappingH
//---------------------------------------------------------------------------
class CFileMappingStream : public TCustomMemoryStream
{
    typedef TCustomMemoryStream inherited;
protected:
    HANDLE                      m_hFile;
    HANDLE                      m_hMapping;
    LPVOID                      m_pBasePointer;

protected:
	void __fastcall             CreateFileMap(const String &AFileName, Word Mode);

public:
	__fastcall                  CFileMappingStream();
	__fastcall                  CFileMappingStream(const String &AFileName, Word Mode)/* overload */;
	__fastcall                  CFileMappingStream(const String &AFileName, Word Mode, unsigned Rights)/* overload */;
	virtual __fastcall          ~CFileMappingStream(void);

	virtual int __fastcall      Write(const void *Buffer, int Count);

	virtual void __fastcall		Open(const String &AFileName, Word Mode);
	virtual void __fastcall		Close();
};
//---------------------------------------------------------------------------
#endif
