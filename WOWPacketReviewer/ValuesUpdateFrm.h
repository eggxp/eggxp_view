//---------------------------------------------------------------------------

#ifndef ValuesUpdateFrmH
#define ValuesUpdateFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "Opcodes.h"
#include "PackageCommon.h"
#include "GameWorld.h"
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFrmValuesUpdate : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TSplitter *Splitter1;
	TPanel *Panel2;
	TGroupBox *GroupBox1;
	TMemo *memComment;
	TMemo *edtPack;
	TPanel *Panel3;
	TPanel *Panel4;
	TPanel *Panel5;
	TPanel *Panel7;
	TListView *lvBlocks;
	TListView *lvValues;
	TPanel *Panel6;
	TComboBox *cbPackHead;
	TButton *btPackOutput;
	TButton *btPackInput;
	TPopupMenu *pmWrite;
	TMenuItem *miWriteInt;
	TMenuItem *miWriteFloat;
	TMenuItem *miDelete;
	TMenuItem *miAddValue;
	TMenuItem *N1;
	TMenuItem *miChangeIndex;
	TMenuItem *miWriteByte;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall btPackInputClick(TObject *Sender);
	void __fastcall btPackOutputClick(TObject *Sender);
	void __fastcall lvBlocksClick(TObject *Sender);
	void __fastcall lvBlocksData(TObject *Sender, TListItem *Item);
	void __fastcall lvValuesData(TObject *Sender, TListItem *Item);
	void __fastcall miWriteIntClick(TObject *Sender);
	void __fastcall miWriteFloatClick(TObject *Sender);
	void __fastcall miDeleteClick(TObject *Sender);
	void __fastcall miAddValueClick(TObject *Sender);
	void __fastcall miChangeIndexClick(TObject *Sender);
	void __fastcall edtPackDblClick(TObject *Sender);
	void __fastcall miWriteByteClick(TObject *Sender);
private:	// User declarations
	WOWPackage			m_WOWPackage;
	vector<tagUpdateObjectValuesResult>	m_ValueResult;
	int					m_CurBlockIndex;

	void				BuidlValues(tagUpdateObjectValuesResult *input);
	void				RefreshUI();
	void				RefreshBlocks();
	void				Parse();
public:		// User declarations
	__fastcall TFrmValuesUpdate(TComponent* Owner);
	void				ParseStart(WOWPackage *input);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmValuesUpdate *FrmValuesUpdate;
//---------------------------------------------------------------------------
#endif
