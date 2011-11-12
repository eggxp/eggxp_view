//---------------------------------------------------------------------------

#ifndef MapFrmH
#define MapFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include <Grids.hpp>
#include "cgauges.h"
#include <Menus.hpp>
//---------------------------------------------------------------------------
class MapEntry;
class TFrmMap : public TForm
{
__published:	// IDE-managed Components
    TPanel *Panel1;
    TSplitter *Splitter1;
    TPanel *Panel2;
    TScrollBox *ScrollBox2;
    TImage *imgObsMap;
    TPanel *Panel3;
    TSplitter *Splitter2;
    TDrawGrid *dgVMap;
    TDrawGrid *dgMap;
    TPageControl *PageControl1;
    TTabSheet *TabSheet1;
    TTabSheet *TabSheet2;
    TListView *lvMaps;
    TEdit *edtPosx;
    TEdit *edtPosy;
    TButton *btCalc;
    TMemo *memOutput;
    TEdit *edtgx;
    TEdit *edtgy;
    TButton *btGoto;
    TLabel *labCurXY;
    TCGauge *CGauge1;
    TPopupMenu *pmMaps;
    TMenuItem *miOutput;
    TTimer *Timer1;
    TLabel *labRegionInfo;

    void __fastcall PaintBox1Paint(TObject *Sender);
    void __fastcall lvMapsClick(TObject *Sender);
    void __fastcall lvMapsData(TObject *Sender, TListItem *Item);
    void __fastcall dgMapDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
    void __fastcall dgVMapDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
    void __fastcall dgMapSelectCell(TObject *Sender, int ACol, int ARow,
          bool &CanSelect);
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btCalcClick(TObject *Sender);
    void __fastcall btGotoClick(TObject *Sender);
    void __fastcall imgObsMapMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall miOutputClick(TObject *Sender);
private:	// User declarations
    bool        m_Inited;
    String      m_SelectedTableName;
    int         m_StartGx;
    int         m_StartGy;
    TRect       m_MapRect;
    int         m_Scale;
    void        ClearMapRegionRec();
    const MapEntry  *   m_SelectedEntry;
    void        DrawMapGrid();
    bool        PaintMap(Graphics::TBitmap * OutBitmap, const MapEntry  *   entry, int gx, int gy, int scale);
    int         GetOutputMapSize();
    void        OutputMap();
public:		// User declarations
    __fastcall TFrmMap(TComponent* Owner);
    void    ShowMap();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmMap *FrmMap;
//---------------------------------------------------------------------------
#endif
