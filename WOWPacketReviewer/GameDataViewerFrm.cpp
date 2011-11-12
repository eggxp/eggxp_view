//---------------------------------------------------------------------------

#include <vcl.h>
#include <Clipbrd.hpp>
#pragma hdrstop

#include "GameDataViewerFrm.h"
#include "FishAI.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmGameDataViewer *FrmGameDataViewer;
//---------------------------------------------------------------------------
__fastcall TFrmGameDataViewer::TFrmGameDataViewer(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFrmGameDataViewer::btGoClick(TObject *Sender)
{
    if(GetGameWorld()->GetFishAI()->GetActive())
    {
        GetGameWorld()->GetFishAI()->SetActive(0);
        GetGameWorld()->GetFishAI()->ForceAwake();
    }
    else
    {
        GetFiberManager()->Awake(FWC_FISH_AI_START);
    }
}
void        TFrmGameDataViewer::ShowFrm()
{
    m_Root = GetGameWorld()->GetRootData();
    this->Refresh();
    this->Show();
}
//---------------------------------------------------------------------------
void __fastcall TFrmGameDataViewer::btResetClick(TObject *Sender)
{
    m_Root = GetGameWorld()->GetRootData();
    this->Refresh();
}
//---------------------------------------------------------------------------
void        TFrmGameDataViewer::Refresh()
{
    ListView_SetItemCountEx(lvFiberState->Handle, GetFiberManager()->GetFiberCount(), LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
    lvFiberState->Refresh();
    
    if(m_Root.get() == NULL)
        return;

    this->Caption = m_Root->GetFullPath();
    ListView_SetItemCountEx(lvAll->Handle, m_Root->GetChildCount(), LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
    lvAll->Refresh();
}
void __fastcall TFrmGameDataViewer::lvAllData(TObject *Sender, TListItem *Item)
{
    shared_ptr<DataObject>      value = m_Root->GetAt(Item->Index);
    if(value.get() == NULL)
        return;
    Item->Caption = value->GetKeyName();
    Item->SubItems->Add(value->AsString());
    Item->SubItems->Add(value->GetChildCount());
    Item->SubItems->Add(value->GetFullPath());
}
//---------------------------------------------------------------------------

void __fastcall TFrmGameDataViewer::lvAllDblClick(TObject *Sender)
{
    if(m_Root.get() == NULL)
        return;
    shared_ptr<DataObject>      value = m_Root->GetAt(lvAll->ItemIndex);
    if(value.get() == NULL)
        return;
    m_Root = value;
    this->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TFrmGameDataViewer::Timer1Timer(TObject *Sender)
{
    this->Refresh();    
}
//---------------------------------------------------------------------------


void __fastcall TFrmGameDataViewer::btUpClick(TObject *Sender)
{
    if(m_Root.get() == NULL)
        return;
    auto_ptr<TStringList> splitStr(new TStringList);
    SplitStr(m_Root->GetFullPath(), "/", splitStr.get());
    String upPath;
    for(int i=0; i<splitStr->Count-1; i++)
    {
        if(i != splitStr->Count-2)
            upPath = upPath + splitStr->Strings[i] + "/";
        else
            upPath = upPath + splitStr->Strings[i];
    }
    m_Root = GetGameWorld()->GetDataByKey(upPath);
    this->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TFrmGameDataViewer::lvFiberStateData(TObject *Sender,
      TListItem *Item)
{
    FiberProcesser * processer = GetFiberManager()->GetFiberProcesser(Item->Index);
    Item->Caption = processer->GetName();
    Item->SubItems->Add(processer->GetWaitMsg());
	Item->SubItems->Add(GetTickCount() - processer->GetWaitTick());
	Item->SubItems->Add(processer->GetActive());
}
//---------------------------------------------------------------------------

void __fastcall TFrmGameDataViewer::btReloadClick(TObject *Sender)
{
    GetGameWorld()->LoadFishData();
}
//---------------------------------------------------------------------------

void __fastcall TFrmGameDataViewer::FormCreate(TObject *Sender)
{
//#ifndef	WOW_FISHER
	btGo->Visible = false;
	lvFiberState->Visible = false;
//#endif
}
//---------------------------------------------------------------------------

void __fastcall TFrmGameDataViewer::miCopyClick(TObject *Sender)
{
	String result;
	for (int i=0; i<lvAll->Items->Count; i++)
	{
		if (lvAll->Items->Item[i]->Selected)
		{
		    shared_ptr<DataObject>      value = m_Root->GetAt(lvAll->Items->Item[i]->Index);
			if(value.get() == NULL)
				continue;
			result += FormatStr("%s\r\n%s\r\n%d\r\n%s\r\n\r\n", value->GetKeyName(), value->AsString(), value->GetChildCount(), value->GetFullPath());
		}
	}

	Clipboard()->AsText = result;
}
//---------------------------------------------------------------------------

void __fastcall TFrmGameDataViewer::btClearDataClick(TObject *Sender)
{
	String msg = "Clear ALl Data?";
	if (Application->MessageBox(msg.c_str(),L"Clear",MB_OKCANCEL)!=IDOK)
	{
		return;
	}
	for (int i=0; i<lvAll->Items->Count; i++)
	{
		shared_ptr<DataObject>      value = m_Root->GetAt(lvAll->Items->Item[i]->Index);
		if(value.get() == NULL)
			continue;
		value->SetValue("");
	}
	this->Refresh();
}
//---------------------------------------------------------------------------

