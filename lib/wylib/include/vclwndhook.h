//---------------------------------------------------------------------------

#ifndef vclwndhookH
#define vclwndhookH
//作者:小强
#include <vcl.h>

class CWindowWndHook
{
private:
    TWinControl                *m_pWinControl;
    Classes::TWndMethod         m_pPrevWndFunc;
    Classes::TWndMethod         m_xWindowProc;

private:
	void __fastcall             MainWndProc(Messages::TMessage &Message);
    virtual BOOL WINAPI         HookWndProc();
    virtual BOOL WINAPI         UnhookWndProc();
	virtual void __fastcall     WndProc(Messages::TMessage &Message);
public:
								CWindowWndHook(TWinControl *pWinControl, Classes::TWndMethod pNewProc = NULL);
								CWindowWndHook();
								~CWindowWndHook();
	virtual VOID WINAPI         Bind(TWinControl *pWinControl, Classes::TWndMethod pNewProc = NULL);
	virtual TWinControl *       GetWinControl()                                 { return m_pWinControl; }
	virtual Classes::TWndMethod GetWindowProc()                                 { return m_xWindowProc; }
    virtual VOID                SetWindowProc(Classes::TWndMethod pWindowProc)  { m_xWindowProc = pWindowProc; }

public:
    __property Classes::TWndMethod  WindowProc =        {read = m_xWindowProc, write = m_xWindowProc};
    __property TWinControl *        WinControl =        {read = m_pWinControl};

};


//---------------------------------------------------------------------------
#endif
