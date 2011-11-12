//---------------------------------------------------------------------------

#ifndef DataViewerFrmH
#define DataViewerFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "cgauges.h"
#include <Menus.hpp>
//---------------------------------------------------------------------------
class TFrmDBCViewer : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel3;
    TSplitter *Splitter1;
    TPanel *Panel1;
    TListView *lvDataNames;
    TPanel *Panel2;
    TListView *lvDatas;
    TCGauge *CGauge1;
    TPopupMenu *pmOutput;
    TMenuItem *miOutput;
    TLabel *labMsg;
    void __fastcall lvDataNamesClick(TObject *Sender);
    void __fastcall lvDatasData(TObject *Sender, TListItem *Item);
    void __fastcall miOutputClick(TObject *Sender);
private:	// User declarations
    bool        m_DataInited;
    String      m_SelectedTableName;
public:		// User declarations
    __fastcall TFrmDBCViewer(TComponent* Owner);

    void        ShowInitFrm();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmDBCViewer *FrmDBCViewer;
//---------------------------------------------------------------------------
#endif
