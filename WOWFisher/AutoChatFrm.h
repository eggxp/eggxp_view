//---------------------------------------------------------------------------

#ifndef AutoChatFrmH
#define AutoChatFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "GameWorld.h"
#include "AutoChatAI.h"
//---------------------------------------------------------------------------
class TFrmAutoChat : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer1;
	TPanel *Panel1;
	TPanel *Panel2;
	TGroupBox *gbAll;
	TSplitter *Splitter1;
	TGroupBox *gbProcessing;
	TListView *lvProcess;
	TListView *lvAll;
	TButton *btActive;
	TEdit *edtText;
	TButton *btSet;
	void __fastcall btActiveClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall lvProcessData(TObject *Sender, TListItem *Item);
	void __fastcall lvAllData(TObject *Sender, TListItem *Item);
	void __fastcall btSetClick(TObject *Sender);
private:	// User declarations
	vector<tagAreaChatAIResult>		m_AreaChatAIResult;
	vector<tagWhoPlayerInfo>		m_WhoPlayerInfo;

	void			Refresh();
public:		// User declarations
	__fastcall TFrmAutoChat(TComponent* Owner);
	void		ShowFrm();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmAutoChat *FrmAutoChat;
//---------------------------------------------------------------------------
#endif
