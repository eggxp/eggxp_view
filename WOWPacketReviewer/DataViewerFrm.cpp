//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "DataViewerFrm.h"
#include "GameWorld.h"
#include "DBCStructureInfo.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cgauges"
#pragma resource "*.dfm"
TFrmDBCViewer *FrmDBCViewer;
//---------------------------------------------------------------------------
__fastcall TFrmDBCViewer::TFrmDBCViewer(TComponent* Owner)
    : TForm(Owner)
{
    m_DataInited = false;
}
//---------------------------------------------------------------------------

void        TFrmDBCViewer::ShowInitFrm()
{
    if(m_DataInited == false)
    {
        m_DataInited = true;

        auto_ptr<TStringList>  dataNames(new TStringList);
        GetTableColumnNames(dataNames.get());
        for(int i=0; i<dataNames->Count; i++)
        {
            TListItem * curItem = lvDataNames->Items->Add();
            curItem->Caption = dataNames->Strings[i];
            curItem->SubItems->Add(GetStoresCountByName(curItem->Caption));
        }
    }

    this->Show();
}

void __fastcall TFrmDBCViewer::lvDataNamesClick(TObject *Sender)
{
    if(lvDataNames->ItemIndex < 0 || lvDataNames->ItemIndex >= lvDataNames->Items->Count)
        return;

    m_SelectedTableName = lvDataNames->Items->Item[lvDataNames->ItemIndex]->Caption;
    lvDatas->Columns->BeginUpdate();
    lvDatas->Columns->Clear();
    for(DWORD i=0; i<(*GetTableColumns())[m_SelectedTableName].Columns.size(); i++)
    {
        TListColumn * column = lvDatas->Columns->Add();
        column->Caption = (*GetTableColumns())[m_SelectedTableName].Columns[i];
        column->Width = 100;
    }
    lvDatas->Columns->EndUpdate();
    
    int rowCount = GetStoresCountByName(m_SelectedTableName);
    ListView_SetItemCountEx(lvDatas->Handle, rowCount, LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
    lvDatas->Refresh();

}
//---------------------------------------------------------------------------

void __fastcall TFrmDBCViewer::lvDatasData(TObject *Sender, TListItem *Item)
{
    AddDBCToListItem(m_SelectedTableName, Item->Index, Item);    
}
//---------------------------------------------------------------------------

void __fastcall TFrmDBCViewer::miOutputClick(TObject *Sender)
{
    String savePath = FormatStr("%s\\DBCOutput\\", ExtractFilePath(Application->ExeName));
    ForceDirectories(savePath);
    String saveName = savePath + m_SelectedTableName + ".txt";
    auto_ptr<TStringList> saveString(new TStringList);

    String line = "";
    for(DWORD i=0; i<(*GetTableColumns())[m_SelectedTableName].Columns.size(); i++)
    {
        if(i == (*GetTableColumns())[m_SelectedTableName].Columns.size()-1)
        {
            line = line + (*GetTableColumns())[m_SelectedTableName].Columns[i];
        }
        else
        {
            line = line + (*GetTableColumns())[m_SelectedTableName].Columns[i] + "\t";
        }
    }
    saveString->Add(line);

    line = "";

    auto_ptr<TStringList> outputLine(new TStringList);
    int rowCount = GetStoresCountByName(m_SelectedTableName);

    int scale = rowCount / 100;
    if(scale == 0)
        scale = 1;
    CGauge1->MaxValue = rowCount / scale;
    for(int i=0; i<rowCount; i++)
    {
        line = "";
        outputLine->Clear();
        AddDBCToStringList(m_SelectedTableName, i, outputLine.get());

        for(int index=0; index<outputLine->Count; index++)
        {
            if(index == outputLine->Count-1)
            {
                line = line + outputLine->Strings[index];
            }
            else
            {
                line = line + outputLine->Strings[index] + "\t";
            }
        }
        saveString->Add(line);

        if(i % scale == 0)
        {
            CGauge1->Progress = i / scale;
        }
    }
    
    CGauge1->Progress = CGauge1->MaxValue;
    labMsg->Caption = "Saving...";
    saveString->SaveToFile(saveName);
    ShowMessage(FormatStr("Save To File OK! Name : %s", saveName));
    labMsg->Caption = "-";
    CGauge1->Progress = 0;
}
//---------------------------------------------------------------------------
