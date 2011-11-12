//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TButton *btTest;
	TGroupBox *GroupBox1;
	TLabeledEdit *labUserName;
	TLabeledEdit *labPsw;
	TLabeledEdit *edtClients;
	TLabeledEdit *edtClientB;
	TLabeledEdit *edtClientCalcResult;
	TButton *btClientCalc;
	TButton *Button1;
	void __fastcall btTestClick(TObject *Sender);
	void __fastcall btClientCalcClick(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
