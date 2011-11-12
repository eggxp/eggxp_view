//---------------------------------------------------------------------------

#ifndef ChargeFrmH
#define ChargeFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmChargeFrm : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *edtChargeText;
	TLabel *Label2;
	TEdit *edtAcc;
	TButton *btCharge;
	TPageControl *PageControl1;
	TTabSheet *TabSheet2;
	TMemo *memChargeMsg;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btChargeClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmChargeFrm(TComponent* Owner);
	void	AddLog(String log);
	void	ShowFrm();
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmChargeFrm *frmChargeFrm;
//---------------------------------------------------------------------------
#endif
