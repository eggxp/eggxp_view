//---------------------------------------------------------------------------

#ifndef DockFrmH
#define DockFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmDock : public TForm
{
__published:	// IDE-managed Components
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormResize(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmDock(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmDock *frmDock;
//---------------------------------------------------------------------------
#endif
