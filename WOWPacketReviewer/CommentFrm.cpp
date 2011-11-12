//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "CommentFrm.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmComment *FrmComment;
//---------------------------------------------------------------------------
__fastcall TFrmComment::TFrmComment(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void        TFrmComment::SetShowText(TStrings * str)
{
    memComment->Lines->Clear();
    memComment->Lines->AddStrings(str);
}
