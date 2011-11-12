//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DockFrm.h"
#include "GameWorld.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmDock *frmDock;
//---------------------------------------------------------------------------
__fastcall TfrmDock::TfrmDock(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TfrmDock::FormClose(TObject *Sender, TCloseAction &Action)
{
	if(!GetGameWorld()->GetWOWWindowHandle())
	{
		return;
	}
	::SetParent(GetGameWorld()->GetWOWWindowHandle(), NULL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmDock::FormResize(TObject *Sender)
{
	if(!GetGameWorld()->GetWOWWindowHandle())
	{
		return;
	}
	::MoveWindow(GetGameWorld()->GetWOWWindowHandle(), 0, 0, this->Width, this->Height - 30, false);
	::ShowWindow(GetGameWorld()->GetWOWWindowHandle(), SW_MAXIMIZE);
}
//---------------------------------------------------------------------------

