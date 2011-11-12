//---------------------------------------------------------------------------

#ifndef CommentFrmH
#define CommentFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFrmComment : public TForm
{
__published:	// IDE-managed Components
    TMemo *memComment;
private:	// User declarations
public:		// User declarations
    __fastcall TFrmComment(TComponent* Owner);
    void        SetShowText(TStrings * str);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmComment *FrmComment;
//---------------------------------------------------------------------------
#endif
