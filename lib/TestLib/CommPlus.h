//---------------------------------------------------------------------------

#ifndef CommPlusH
#define CommPlusH
//---------------------------------------------------------------------------
#include    <vcl.h>
#include    "CommFunc.h"


//#ifdef      ENABLE_THREAD_TRY
#define     THREAD_TRY_BEGIN       try{
#define     THREAD_TRY_END(msg)    }   \
                                    catch(Exception &e) \
                                    {   \
                                            GetLog()->Error("%s Exception = %s", \
                                                    msg, e.Message); \
                                        return ; \
                                    }
//#else
//#define     THREAD_TRY_BEGIN
//#define     THREAD_TRY_END(msg)
//#endif

AnsiString  StrHeadInsertBuf(AnsiString src, void  *buf, int bufLen);
AnsiString  StrHeadInsertBYTE(AnsiString src, BYTE head);
AnsiString  StrHeadInsertWORD(AnsiString src, WORD head);
AnsiString  StrHeadInsertDWORD(AnsiString src, DWORD head);
int GetFileDirList(const String &DirName,TStrings *ResultList,bool SubDir);


typedef HANDLE  (__closure * TFindWindowFunc)();
typedef	void   	(__closure * TInjectOK)();
class DllInjecter
{
private:
    TTimer  *       m_FindTimer;
	String          m_DllFullPath;
	HANDLE			m_hProcess;
	DWORD			m_ProcessID;
    void __fastcall         OnFindTimer(System::TObject* Sender);

    void                    ProcessInject();
public:
    DllInjecter();
    ~DllInjecter();
	TFindWindowFunc         fpFindWindowFunc;
	TInjectOK				fpInjectOK;

	void            InjectDll(String DllFullPath);
	HANDLE			GetProcessHandler(){return		m_hProcess;}
	void			SetActiveInject(bool active);
	bool			GetIsActiveInject();
	DWORD			GetInjectProcessID();
};

DllInjecter *       GetDllInjecter();
//---------------------------------------------------------------------------





#endif
