//---------------------------------------------------------------------------

#ifndef BlockWindowFrmH
#define BlockWindowFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include "AList.h"
#include "PackageCommon.h"
#include <Dialogs.hpp>
#include "cspin.h"
class WOWPackage;
//---------------------------------------------------------------------------
void                CopyListViewSelectText(TListView * lv, AList<WOWPackage> * listData, TGetInfoType getInfoType);
String              GetListViewCommentText(TListView * lv, AList<WOWPackage> * listData);
int                 GetShowHeadSize(WOWPackage * curPack);
//---------------------------------------------------------------------------

class TfrmBlock : public TForm
{
__published:	// IDE-managed Components
    TListView *lvAll;
    TTimer *Timer1;
    TPopupMenu *PopupMenu1;
    TMenuItem *miMoveHere;
    TPanel *Panel1;
    TSplitter *Splitter1;
    TButton *btNext;
    TMenuItem *miCopy;
    TButton *btJmp;
    TMenuItem *miProcessCurrent;
    TMenuItem *N1;
    TMenuItem *miJumpHere;
	TCheckBox *cbBlockOnly;
	TButton *btResetBlockOnly;
	TMenuItem *CopyDetail1;
	TMenuItem *CopyLine1;
	TMenuItem *CopyCVS1;
	TCSpinEdit *edtNextCount;
	TStaticText *StaticText1;
    void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall lvAllData(TObject *Sender, TListItem *Item);
    void __fastcall lvAllCustomDrawItem(TCustomListView *Sender,
          TListItem *Item, TCustomDrawState State, bool &DefaultDraw);
    void __fastcall lvAllCustomDrawSubItem(TCustomListView *Sender,
          TListItem *Item, int SubItem, TCustomDrawState State,
          bool &DefaultDraw);
    void __fastcall btNextClick(TObject *Sender);
    void __fastcall miMoveHereClick(TObject *Sender);
    void __fastcall btJmpClick(TObject *Sender);
    void __fastcall miProcessCurrentClick(TObject *Sender);
    void __fastcall miJumpHereClick(TObject *Sender);
	void __fastcall cbBlockOnlyClick(TObject *Sender);
	void __fastcall lvAllClick(TObject *Sender);
	void __fastcall btResetBlockOnlyClick(TObject *Sender);
	void __fastcall CopyDetail1Click(TObject *Sender);
	void __fastcall CopyLine1Click(TObject *Sender);
	void __fastcall CopyCVS1Click(TObject *Sender);
private:	// User declarations
	void            Refresh();
	int				m_BlockOnlyPackIndex;
    int             m_WatchConnectionIndex;
public:		// User declarations
    __fastcall TfrmBlock(TComponent* Owner);
    GEN_GET_SET(int, WatchConnectionIndex);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmBlock *frmBlock;
//---------------------------------------------------------------------------
#endif
