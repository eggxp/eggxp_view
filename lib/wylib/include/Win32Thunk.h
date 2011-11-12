/***************************************************************************
 *  File name Win32Thunk.h                                                 *
 *  Version:  1.00.03a                                                     *
 *  Author:   yypcn                                                        *
 *  Target:   ATL/AUX -- COM/ATL Useful Helpers                            *
 *                                                                         *
 *  History                                                                *
 *  06-16-2003    21:54pm  Base on Andrew Nosenko's ATL/AUX Thunk.         *
 *  06-16-2003    23:07pm  Add 'CAuxCdeclThunk' class support '__cdecl'    *
 *                         methods.                                        *
 *                                                                         *
 ***************************************************************************/
#ifndef Win32ThunkH
  #define Win32ThunkH

////////////////////////////////////////////////////////////////////////////////

/* Win32 Callback thunking, the main idea was taken from ATL.

Thunks could be used to turn an object+method pair into a closure that could be
passed to Win32 API requiring a callback address. This is a clever idea of ATL
team, I've only tried to propagate it over a general case.
Thunks are very suitable and efficient way to avoid tiresome TLS/CritSecs/maps
(when providing apartment threading and reentrancy).

CAuxThunk<> is provided for __thiscall methods, CAuxStdThunk<> is for __stdcall.

Here is an example of how to set up Win32 hook the reentrant way, without a
use of global variable:

class CHook:
  public CAuxThunk<CHook>
{
public:
  CHook(): m_hhook(NULL)
  {
    InitThunk((TMFP)CBTHook, this);
  }

  LRESULT CBTHook(int nCode, WPARAM wParam, LPARAM lParam);
  BOOL Hook() {
    m_hook = SetWindowsHookEx(WH_CBT, (HOOKPROC)GetThunk(), NULL, GetCurrentThreadId());
    return (BOOL)m_hook;
  }

  HHOOK m_hhook;
...
};

LRESULT CHook::CBTHook(int nCode, WPARAM wParam, LPARAM lParam)
{
  if ( nCode == HCBT_CREATEWND ) {
    UnhookWindowsHookEx(m_hook);
    HWND hwnd = (HWND)wParam;
    // do whatever we want with HWND
    ...
  }
  return CallNextHookEx(m_hook, nCode, wParam, lParam);
}

Another example. I need to process an event in my IE4 simple object
(windowless) *asynchronously* and use SetTimer API for that.
Unfortunately, TIMERPROC doesn't take any context info.
Here is how it has been solved:

struct TIMEOUT: CAuxThunk<TIMEOUT> {
  UINT m_timerID;
  CONTEXT m_contex;

  TIMEOUT(CONTEXT& contex): m_contex(contex)
  {
    InitThunk((TMFP)TimerProc, this);
  }
  void TimerProc(HWND, UINT, UINT idEvent, DWORD dwTime);
  ...
};

void TIMEOUT::TimerProc(HWND, UINT, UINT idEvent, DWORD dwTime)
{
  KillTimer(NULL, m_timerID); // one-shot callback
  // do any processing task
  ...
  delete this;
}
HRESULT CSimpleObj::Post(CONTEXT& contex) {
  TIMEOUT* pTimeout = new TIMEOUT(context);
  pTimeout->m_timerID = ::SetTimer(NULL, 0, timeout, (TIMERPROC)pTimeout->GetThunk());
}
//////////////////////////////////////////////////////////////////////////////*/
  #ifndef _M_IX86
    #pragma message("CAuxThunk/CAuxStdThunk is implemented for X86 only!")
  #endif

  #ifndef _ASSERTE    // BCB non define _ASSERTE ...
    #define _ASSERTE
  #endif

//---------------------------------------------------------------------------
  #pragma pack(push, 1)
template<class T>
class CAuxThunk       // __thiscall(__fastcall) methods
{
  BYTE  m_mov;        // mov ecx, %pThis
  DWORD m_this;       //
  BYTE  m_jmp;        // jmp func
  DWORD m_relproc;    // relative jmp

public:
  typedef void (T:: *TMFP) ();
  void InitThunk(TMFP method, const T *pThis)
  {
    union
    {
      DWORD func;
      TMFP  method;
    } addr;
    addr.method = method;
  #ifdef __BORLANDC__
    m_mov = 0xB8;     // mov eax, %pThis
  #else
    m_mov = 0xB9;     // mov ecx, %pThis
  #endif
    m_this = (DWORD) pThis;
    m_jmp = 0xE9;     // jmp func
    m_relproc = addr.func - (DWORD) (this + 1);
    FlushInstructionCache(GetCurrentProcess(), this, sizeof(*this));
  }

  FARPROC GetThunk() const
  {
  #ifdef __BORLANDC__
    _ASSERTE(m_mov == 0xB8);
  #else
    _ASSERTE(m_mov == 0xB9);
  #endif
    return (FARPROC) this;
  }
};

template<class T>
class CAuxStdThunk    // __stdcall methods
{
  BYTE  m_mov;        // mov eax, %pThis
  DWORD m_this;       //
  DWORD m_xchg_push;  // xchg eax, [esp] : push eax
  BYTE  m_jmp;        // jmp func
  DWORD m_relproc;    // relative jmp

public:
  typedef void (__stdcall T:: *TMFP) ();
  void InitThunk(TMFP method, const T *pThis)
  {
    union
    {
      DWORD func;
      TMFP  method;
    } addr;
    addr.method = method;
    m_mov = 0xB8;
    m_this = (DWORD) pThis;
    m_xchg_push = 0x50240487;
    m_jmp = 0xE9;
    m_relproc = addr.func - (DWORD) (this + 1);
    FlushInstructionCache(GetCurrentProcess(), this, sizeof(*this));
  }

  FARPROC GetThunk() const
  {
    _ASSERTE(m_mov == 0xB8);
    return (FARPROC) this;
  }
};

template<class T>
class CAuxCdeclThunk  // __cdecl methods
{
  BYTE  m_push;       // push %pThis
  DWORD m_this;       //
  BYTE  m_call;       // call func
  DWORD m_relproc;    // relative call
  BYTE  m_pop;        // pop ecx
  BYTE  m_ret;        // ret

public:
  typedef void (__cdecl T:: *TMFP) ();
  void InitThunk(TMFP method, const T *pThis)
  {
    union
    {
      DWORD func;
      TMFP  method;
    } addr;
    addr.method = method;
    m_push = 0x68;    // push %pThis
    m_this = (DWORD) pThis;
    m_call = 0xE8;    // call func
    m_relproc = addr.func - (DWORD) (this) - 10;
    m_pop = 0x59;     // pop ecx
    m_ret = 0xC3;     // ret
    FlushInstructionCache(GetCurrentProcess(), this, sizeof(*this));
  }

  FARPROC GetThunk() const
  {
    _ASSERTE(m_push == 0x68);
    return (FARPROC) this;
  }
};
  #pragma pack(pop)   // CAuxThunk

//---------------------------------------------------------------------------
#endif