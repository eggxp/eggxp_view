//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MapFrm.h"
#include "GameWorld.h"
#include "MapDrawer.h"
#include "DBCStructureInfo.h"
#include "MapVmapDrawer.h"
#include "GameWorld.h"
#include "DBCStores.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cgauges"
#pragma resource "*.dfm"
TFrmMap *FrmMap;
//---------------------------------------------------------------------------
__fastcall TFrmMap::TFrmMap(TComponent* Owner)
    : TForm(Owner)
{
    m_Inited = false;
    m_SelectedEntry = NULL;
    m_StartGx = 0;
    m_StartGy = 0;
    m_SelectedTableName = "Map";
    ClearMapRegionRec();
    m_Scale = 2;
}
//---------------------------------------------------------------------------
void        TFrmMap::ClearMapRegionRec()
{
    m_MapRect.left = -1;
    m_MapRect.top = -1;
    m_MapRect.right = -1;
    m_MapRect.bottom = -1;
}
//---------------------------------------------------------------------------
void    TFrmMap::ShowMap()
{
    lvMaps->Columns->Clear();
    for(DWORD i=0; i<(*GetTableColumns())[m_SelectedTableName].Columns.size(); i++)
    {
        TListColumn * column = lvMaps->Columns->Add();
        column->Caption = (*GetTableColumns())[m_SelectedTableName].Columns[i];
        column->Width = 100;
    }

    int rowCount = GetStoresCountByName(m_SelectedTableName);
    ListView_SetItemCountEx(lvMaps->Handle, rowCount, LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
    lvMaps->Refresh();
    this->Show();
}
void __fastcall TFrmMap::PaintBox1Paint(TObject *Sender)
{
    //pbMapObj->Canvas    
}
//---------------------------------------------------------------------------
void        TFrmMap::DrawMapGrid()
{
    ClearMapRegionRec();
    dgMap->Refresh();
    dgVMap->Refresh();
}

void __fastcall TFrmMap::lvMapsClick(TObject *Sender)
{
    m_SelectedEntry = GetMapStore()->LookupByIndex(lvMaps->ItemIndex);
    DrawMapGrid();
}
//---------------------------------------------------------------------------

void __fastcall TFrmMap::lvMapsData(TObject *Sender, TListItem *Item)
{
    AddDBCToListItem(m_SelectedTableName, Item->Index, Item);
}
//---------------------------------------------------------------------------


void __fastcall TFrmMap::dgMapDrawCell(TObject *Sender, int ACol, int ARow,
      TRect &Rect, TGridDrawState State)
{
    dgMap->Canvas->Brush->Color = clWhite;
    dgMap->Canvas->FillRect(Rect);
    const MapEntry * curMapEntry = m_SelectedEntry;
    if(!curMapEntry)
        return;

    String fileName = FormatStr("%03u%02u%02u", curMapEntry->MapID, ACol, ARow);
    String fullName = GetGameWorld()->GetPath() + "maps\\" + fileName + ".map";
    if(!FileExists(fullName))
        return;

    dgMap->Canvas->Brush->Color = clMaroon;
    dgMap->Canvas->FillRect(Rect);

    if(m_MapRect.left == -1)
    {
        m_MapRect.left = ACol;
    }
    if(m_MapRect.right == -1)
    {
        m_MapRect.right = ACol;
    }
    if(m_MapRect.top == -1)
    {
        m_MapRect.top = ARow;
    }
    if(m_MapRect.bottom == -1)
    {
        m_MapRect.bottom = ARow;
    }

    if(ACol < m_MapRect.left)
    {
        m_MapRect.left = ACol;
    }
    if(ACol > m_MapRect.right)
    {
        m_MapRect.right = ACol;
    }
    if(ARow < m_MapRect.top)
    {
        m_MapRect.top = ARow;
    }
    if(ARow > m_MapRect.bottom)
    {
        m_MapRect.bottom = ARow;
    }
}
//---------------------------------------------------------------------------

void __fastcall TFrmMap::dgVMapDrawCell(TObject *Sender, int ACol, int ARow,
      TRect &Rect, TGridDrawState State)
{
//    dgVMap->Canvas->Brush->Color = clWhite;
//    dgVMap->Canvas->FillRect(Rect);
//    const MapEntry * curMapEntry = GetMapStore()->LookupByIndex(lvMaps->ItemIndex);
//    if(!curMapEntry)
//        return;
//
//    String fileName = FormatStr("%03u_%02u_%02u", curMapEntry->MapID, ACol, ARow);
//    String fullName = GetGameWorld()->GetPath() + "vmaps\\" + fileName + ".vmap";
//    if(!FileExists(fullName))
//        return;
//
//    dgVMap->Canvas->Brush->Color = clMaroon;
//    dgVMap->Canvas->FillRect(Rect);
}
//---------------------------------------------------------------------------

void __fastcall TFrmMap::dgMapSelectCell(TObject *Sender, int ACol, int ARow,
      bool &CanSelect)
{
    m_StartGx = ACol;
    m_StartGy = ARow;
    this->Caption = FormatStr("Map(%d,%d)", ACol, ARow);
    if(!PaintMap(imgObsMap->Picture->Bitmap, m_SelectedEntry, ACol, ARow, m_Scale))
    {
        Graphics::TBitmap * OutBitmap = imgObsMap->Picture->Bitmap;
        OutBitmap->Canvas->Brush->Color = clWhite;
        OutBitmap->Canvas->FillRect(Rect(0, 0, OutBitmap->Width, OutBitmap->Height));
    }
}
//---------------------------------------------------------------------------

bool        TFrmMap::PaintMap(Graphics::TBitmap * OutBitmap, const MapEntry  *   entry, int startgx, int startgy, int scale)
{
    return  DBCMapToBitmap(GetGameWorld(), OutBitmap, entry, startgx, startgy, scale, CGauge1);
}
void __fastcall TFrmMap::FormCreate(TObject *Sender)
{
    PageControl1->ActivePageIndex = 0;
    Graphics::TBitmap * OutBitmap = imgObsMap->Picture->Bitmap;
    OutBitmap->Width = SIZE_OF_GRIDS * 2 / m_Scale;
    OutBitmap->Height = SIZE_OF_GRIDS * 2 / m_Scale;
}
//---------------------------------------------------------------------------

void __fastcall TFrmMap::btCalcClick(TObject *Sender)
{
    memOutput->Lines->Clear();

    int gx = GetGameWorld()->GetGameMapManager()->PosToGrix(edtPosx->Text.ToDouble());
    int gy = GetGameWorld()->GetGameMapManager()->PosToGrix(edtPosy->Text.ToDouble());
    memOutput->Lines->Add(FormatStr("Grid:(%d,%d)", gx, gy));
    dgMap->Col = gx;
    dgMap->Row = gy;
}
//---------------------------------------------------------------------------

void __fastcall TFrmMap::btGotoClick(TObject *Sender)
{
    dgMap->Col = edtgx->Text.ToIntDef(0) + 1;
    dgMap->Row = edtgy->Text.ToIntDef(0) + 1;
}
//---------------------------------------------------------------------------

void __fastcall TFrmMap::imgObsMapMouseMove(TObject *Sender, TShiftState Shift,
      int X, int Y)
{
    int i = X;
    int j = Y;
    float scale = SIZE_OF_GRIDS / m_Scale;
    int gx = m_StartGx + int(i / scale);
    int gy = m_StartGy + int(j / scale);
    float x = (32 - gx) * scale - (i / scale - int(i / scale)) * scale;
    float y = (32 - gy) * scale - (j / scale - int(j / scale)) * scale;
    x = x * m_Scale;
    y = y * m_Scale;
    labCurXY->Caption = FormatStr("(%d, %d)(%f, %f)(%d, %d)", X, Y, x, y, gx, gy);    
}
//---------------------------------------------------------------------------

int         TFrmMap::GetOutputMapSize()
{
    uint64 curSize = SIZE_OF_GRIDS * (m_MapRect.Width()+1) * SIZE_OF_GRIDS * (m_MapRect.Height() + 1) * 4;
    return  curSize / 1024 / 1024;      
}
//---------------------------------------------------------------------------

void __fastcall TFrmMap::Timer1Timer(TObject *Sender)
{

    labRegionInfo->Caption = FormatStr("left:%d.right:%d.top:%d.bottom:%d. mem:%dmb", m_MapRect.left, m_MapRect.right,
                m_MapRect.top, m_MapRect.bottom,
                GetOutputMapSize()
                );
}
//---------------------------------------------------------------------------

void        TFrmMap::OutputMap()
{
    String scaleStr = "1";
    if(!InputQuery("input scale", "input scale", scaleStr))
        return;
    int scale = scaleStr.ToIntDef(1);
    auto_ptr<Graphics::TBitmap> OutBitmap(new Graphics::TBitmap);

    OutBitmap->Width = SIZE_OF_GRIDS * (m_MapRect.Height() + 1) / scale;
    OutBitmap->Height = SIZE_OF_GRIDS * (m_MapRect.Width() + 1) / scale;

    PaintMap(OutBitmap.get(), m_SelectedEntry, m_MapRect.left, m_MapRect.top, scale);

    String path = ExtractFilePath(Application->ExeName) + "\\MapsBmp\\";
    ForceDirectories(path);
    String savePath = path + FormatStr("%d.bmp", m_SelectedEntry->MapID);
    OutBitmap->SaveToFile(savePath);
    GetLog()->Info(FormatStr("Output OK. path = %s", savePath));

    
}
void __fastcall TFrmMap::miOutputClick(TObject *Sender)
{
    OutputMap();    
}
//---------------------------------------------------------------------------


