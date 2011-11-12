//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <ExtCtrls.hpp>
#include <AppEvnts.hpp>
#include <Menus.hpp>
#include <ComCtrls.hpp>
#include "cspin.h"
//---------------------------------------------------------------------------
class SingleThread;
class TMainFrm : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TApplicationEvents *ApplicationEvents1;
	TTrayIcon *TrayIcon1;
	TPopupMenu *pmTray;
	TMenuItem *miCloseWnd;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TListView *lvThread;
	TLabel *labThreadState;
	TGroupBox *GroupBox1;
	TButton *btCreateCare;
	TLabel *Label1;
	TLabel *Label2;
	TComboBox *cbCardType;
	TCSpinEdit *edtCardCount;
	TTabSheet *TabSheet3;
	TLabel *Label3;
	TButton *btCharge;
	TTabSheet *TabSheet4;
	TMemo *memLog;
	TTabSheet *TabSheet5;
	TGroupBox *GroupBox2;
	TLabel *Label4;
	TLabel *Label5;
	TButton *btGetCard;
	TComboBox *cbGetCardType;
	TCSpinEdit *edtGetCardNum;
	TMemo *memGetResult;
	TButton *btQueryCard;
	TButton *btRefreshCardTypes;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall ApplicationEvents1Minimize(TObject *Sender);
	void __fastcall TrayIcon1DblClick(TObject *Sender);
	void __fastcall miCloseWndClick(TObject *Sender);
	void __fastcall TrayIcon1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
		  int X, int Y);
	void __fastcall lvThreadData(TObject *Sender, TListItem *Item);
	void __fastcall btCreateCareClick(TObject *Sender);
	void __fastcall btChargeClick(TObject *Sender);
	void __fastcall btGetCardClick(TObject *Sender);
	void __fastcall btQueryCardClick(TObject *Sender);
	void __fastcall btRefreshCardTypesClick(TObject *Sender);


private:	// User declarations
	virtual void __fastcall WndProcs(Messages::TMessage &Message);

	TADOConnection	*		m_ADOConnection;
	TADOQuery *				m_ADOQuery;

	void				AddLog(String msg);
	void				RefreshCardTypes();
//	int		TestThread(SingleThread * thread);
public:		// User declarations
    __fastcall TMainFrm(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMainFrm *MainFrm;
//---------------------------------------------------------------------------
#endif
