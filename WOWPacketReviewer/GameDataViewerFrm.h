//---------------------------------------------------------------------------

#ifndef GameDataViewerFrmH
#define GameDataViewerFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "GameWorld.h"
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFrmGameDataViewer : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TPanel *Panel2;
    TSplitter *Splitter1;
    TListView *lvAll;
    TTimer *Timer1;
    TPanel *Panel3;
    TButton *btReset;
    TButton *btUp;
    TButton *btGo;
    TListView *lvFiberState;
    TButton *btReload;
	TPopupMenu *pmMenu;
	TMenuItem *miCopy;
	TButton *btClearData;
    void __fastcall btGoClick(TObject *Sender);
    void __fastcall btResetClick(TObject *Sender);
    void __fastcall lvAllData(TObject *Sender, TListItem *Item);
    void __fastcall lvAllDblClick(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall btUpClick(TObject *Sender);
    void __fastcall lvFiberStateData(TObject *Sender, TListItem *Item);
    void __fastcall btReloadClick(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall miCopyClick(TObject *Sender);
	void __fastcall btClearDataClick(TObject *Sender);
private:	// User declarations
    shared_ptr<DataObject>      m_Root;

    void        Refresh();
public:		// User declarations
    __fastcall TFrmGameDataViewer(TComponent* Owner);
    void        ShowFrm();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmGameDataViewer *FrmGameDataViewer;
//---------------------------------------------------------------------------
#endif
