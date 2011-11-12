//---------------------------------------------------------------------------

#include <vcl.h>
#include <Clipbrd.hpp>
#pragma hdrstop

#include "BlockWindowFrm.h"
#include "PackageContainer.h"
#include "GameWorld.h"
#include "WOWPacketReviewer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmBlock *frmBlock;

int                 GetShowHeadSize(WOWPackage * curPack)
{
    if(WOWReviewerMainFrm->cbShowHead->Checked)
	{
		return	curPack->GetHeadSize();
    }

    return      0;
}

String              GetListViewCommentTextByIndex(int index, AList<WOWPackage> * listData)
{
	WOWPackage  * curPack = listData->At(index);
	if(!curPack)
		return  "";

	return          curPack->GetComment()->Text;
}

String              GetListViewCommentText(TListView * lv, AList<WOWPackage> * listData)
{
	return GetListViewCommentTextByIndex(lv->ItemIndex, listData);
}

void                CopyListViewSelectText(TListView * lv, AList<WOWPackage> * listData, TGetInfoType getInfoType)
{
    auto_ptr<TStringList>   copyStr(new TStringList);
    for(int i=0; i<lv->Items->Count; i++)
    {
        if(lv->Items->Item[i]->Selected)
        {
            WOWPackage  * curPack = listData->At(i);
            if(!curPack)
                continue;

			curPack->GetInfo(getInfoType, !WOWReviewerMainFrm->cbShowHead->Checked, copyStr.get());
        }
    }

    if(getInfoType == GIT_FILE)
    {
        String savePath = FormatStr("%s\\PacketSave\\", ExtractFilePath(Application->ExeName));
        ForceDirectories(savePath);
        String fileName = DateTimeToStr(Now());
        fileName = ReplaceStr(fileName, "-", "_");
        fileName = ReplaceStr(fileName, " ", "_");
        fileName = ReplaceStr(fileName, ":", "_");
        String saveName = savePath + fileName + ".txt";
        copyStr->SaveToFile(saveName);
        ShowMessage(FormatStr("Copy OK, path = %s", saveName));
        return;
    }
    Clipboard()->AsText = copyStr->Text;
}


//---------------------------------------------------------------------------
__fastcall TfrmBlock::TfrmBlock(TComponent* Owner)
    : TForm(Owner)
{
    m_WatchConnectionIndex = 0;
	m_BlockOnlyPackIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmBlock::FormClose(TObject *Sender, TCloseAction &Action)
{
	GetGameWorld()->SetBlockMode(0);
	GetGameWorld()->SetCurrentProcessIndex(0);
}
//---------------------------------------------------------------------------
void            TfrmBlock::Refresh()
{
	PackageContainer * curPackageContainer = GetPackageContainerManager()->GetWorldPackageContainer(m_WatchConnectionIndex);
	if(!curPackageContainer)
		return;

	int  cnt = curPackageContainer->GetFilterAll()->Count();
	ListView_SetItemCountEx(lvAll->Handle, cnt, LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
	lvAll->Repaint();

	cbBlockOnly->Caption = FormatStr("Block Only. Index = %d", m_BlockOnlyPackIndex);
}
//---------------------------------------------------------------------------
void __fastcall TfrmBlock::Timer1Timer(TObject *Sender)
{
	Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfrmBlock::lvAllData(TObject *Sender, TListItem *Item)
{
    PackageContainer * curPackageContainer =  GetPackageContainerManager()->GetWorldPackageContainer(m_WatchConnectionIndex);
    if(!curPackageContainer)
        return;
    WOWPackage * curPack = curPackageContainer->GetFilterAll()->At(Item->Index);
    if(!curPack)
    {
        return;
    }
	Item->Caption = IntToStr(curPack->GetIndex());
	Item->SubItems->Add(curPack->GetTime());
	Item->SubItems->Add(curPack->GetMark());
	Item->SubItems->Add(curPack->GetData().Length());
	Item->SubItems->Add(curPack->GetOpCodeMsg());
	Item->SubItems->Add(BinToStr(curPack->GetData().c_str()+GetShowHeadSize(curPack), curPack->GetData().Length()-GetShowHeadSize(curPack)));
}
//---------------------------------------------------------------------------
void __fastcall TfrmBlock::lvAllCustomDrawItem(TCustomListView *Sender,
      TListItem *Item, TCustomDrawState State, bool &DefaultDraw)
{
    PackageContainer * curPackageContainer = GetPackageContainerManager()->GetWorldPackageContainer(m_WatchConnectionIndex);
    if(!curPackageContainer)
        return;
    WOWPackage * curPack = curPackageContainer->GetFilterAll()->At(Item->Index);
    if(!curPack)
    {
        return;
    }

    UINT        Flags;
    TRect       tDrawRect;
    TCanvas     *tCanvas;
    HIMAGELIST  hStateImages;
    IMAGEINFO   hStateImageInfo;
    tCanvas = Sender->Canvas;
    hStateImages = ListView_GetImageList(Sender->Handle, LVSIL_STATE);
    ZeroMemory(&hStateImageInfo, sizeof(hStateImageInfo));
    try
    {
        ListView_GetSubItemRect(Sender->Handle, Item->Index, 0, LVIR_BOUNDS, &tDrawRect);
        tDrawRect.right = tDrawRect.left + Sender->Column[0]->Width;
        if(State.Contains(cdsSelected))
        {
            tCanvas->Font->Color = clHighlightText;
            tCanvas->Brush->Color = clHighlight;
        }
        else
        {
            tCanvas->Font->Color = (TColor) ListView_GetTextColor(Sender->Handle);
            tCanvas->Brush->Color = ((TListView *)Sender)->Color;
        }

        if(Sender->Checkboxes)
        {
            ImageList_GetImageInfo(hStateImages, (Item->Checked ? 1 : 0), &hStateImageInfo);
            ImageList_Draw(hStateImages, (Item->Checked ? 1 : 0), tCanvas->Handle, tDrawRect.left + 1, tDrawRect.top, ILD_TRANSPARENT);
            OffsetRect(&tDrawRect, TRect(hStateImageInfo.rcImage).Width() + 2, 0);
        }

        tCanvas->FillRect(tDrawRect);
        Flags = lvAll->DrawTextBiDiModeFlags(Sender->Column[0]->Alignment);
        OffsetRect(&tDrawRect, 2, 2);
        DrawText(tCanvas->Handle, Item->Caption.c_str(), Item->Caption.Length(), &tDrawRect, Flags);
        for(int i = 0; i< ((TListView *)Sender)->Columns->Count; i++)
        {
            lvAll->OnCustomDrawSubItem(Sender, Item, i, State, DefaultDraw);
        }

        DefaultDraw = false;
    }

    catch(...)
    {}
}
//---------------------------------------------------------------------------
void __fastcall TfrmBlock::lvAllCustomDrawSubItem(TCustomListView *Sender,
      TListItem *Item, int SubItem, TCustomDrawState State, bool &DefaultDraw)
{
    PackageContainer * curPackageContainer = GetPackageContainerManager()->GetWorldPackageContainer(m_WatchConnectionIndex);
    if(!curPackageContainer)
        return;
    WOWPackage * curPack = curPackageContainer->GetFilterAll()->At(Item->Index);
    if(!curPack)
    {
        return;
    }


    if(SubItem>=0 && !State.Contains(cdsDisabled))
    {
        SIZE lpSize;
        TRect tDrawRect;
        TCanvas *tCanvas;
        LPSTR lpBackslash;
        COLORREF crOldColor;
		TCHAR szSubItemText[4096*2];
        tCanvas = Sender->Canvas;
        try
        {
            crOldColor = GetTextColor(tCanvas->Handle);
			ListView_GetItemText(Sender->Handle, Item->Index, SubItem, szSubItemText, sizeof(szSubItemText) / sizeof(TCHAR));
			String itemText = szSubItemText;
            ListView_GetSubItemRect(Sender->Handle, Item->Index, SubItem, LVIR_BOUNDS, &tDrawRect);
            if(State.Contains(cdsSelected))
            {
                tCanvas->Font->Color = clHighlightText;
                tCanvas->Brush->Color = clHighlight;
            }
            else
            {
                tCanvas->Font->Color = (TColor)ListView_GetTextColor(Sender->Handle);
                tCanvas->Brush->Color = ((TListView *)Sender)->Color;
            }
            tCanvas->FillRect(tDrawRect);
            OffsetRect(&tDrawRect, 2, 2);
            tCanvas->Font->Size = lvAll->Font->Size - 2;
            GetTextExtentPoint32(tCanvas->Handle, itemText.c_str(), itemText.Length(), &lpSize);
            if(lpSize.cx > tDrawRect.Width())
                lpSize.cx = tDrawRect.Width()-2;
            switch(Sender->Column[SubItem]->Alignment)
            {
            case taLeftJustify:
                break;
            case taCenter:
                OffsetRect(&tDrawRect, (tDrawRect.Width() - lpSize.cx) / 2, 0);
                break;
            case taRightJustify:
                OffsetRect(&tDrawRect, tDrawRect.Width() - lpSize.cx - 8, 0);
                break;
            }

            if(curPack->GetIndex() == GetGameWorld()->GetCurrentProcessIndex())
            {
                SetTextColor(tCanvas->Handle, clBlue);                
			}
			else 	if (cbBlockOnly->Checked && m_BlockOnlyPackIndex == Item->Index)
			{
				SetTextColor(tCanvas->Handle, clBlue);
			}
            else    if(curPack->GetProcessed() == 1)
            {
                SetTextColor(tCanvas->Handle, clGray);
			}
            else    if(curPack->GetProcessed() == -1)
            {
                SetTextColor(tCanvas->Handle, clYellow);
            }
            else
            {
                SetTextColor(tCanvas->Handle, clMaroon);
            }

            DrawText(tCanvas->Handle, itemText.c_str(), itemText.Length(), &tDrawRect, 0);
            SetTextColor(tCanvas->Handle, crOldColor);
            DefaultDraw = false;
        }
        catch(...)
        {}
    }
}
//---------------------------------------------------------------------------
void __fastcall TfrmBlock::btNextClick(TObject *Sender)
{
	if(!cbBlockOnly->Checked)
	{
		GetPackageContainerManager()->ProcessClientMessage(1, 1, -1);
	}
	else
	{
		PackageContainer * curPackageContainer = GetPackageContainerManager()->GetWorldPackageContainer(m_WatchConnectionIndex);
		if(!curPackageContainer)
			return;
		for(; m_BlockOnlyPackIndex < curPackageContainer->GetFilterAll()->Count(); m_BlockOnlyPackIndex++)
		{
			WOWPackage * curPack = curPackageContainer->GetFilterAll()->At(m_BlockOnlyPackIndex);
			if(!curPack)
			{
				return;
			}
			if (curPack->GetProcessed())
			{
				continue;
			}
			GetPackageContainerManager()->ProcessOneClientMessage(curPack);
			WOWReviewerMainFrm->SetCommentText(GetListViewCommentTextByIndex(m_BlockOnlyPackIndex, curPackageContainer->GetFilterAll()));
			break;
		}
	}
    this->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TfrmBlock::miMoveHereClick(TObject *Sender)
{
    PackageContainer * curPackageContainer = GetPackageContainerManager()->GetWorldPackageContainer(m_WatchConnectionIndex);
    if(!curPackageContainer)
        return;
    WOWPackage * curPack = curPackageContainer->GetFilterAll()->At(lvAll->ItemIndex);
    if(!curPack)
    {
        return;
    }
    GetPackageContainerManager()->ProcessClientMessage(1, -1, curPack->GetIndex());

    this->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBlock::btJmpClick(TObject *Sender)
{
    GetGameWorld()->SetCurrentProcessIndex(GetGameWorld()->GetCurrentProcessIndex() + 2);
    GetPackageContainerManager()->ProcessClientMessage(1, 1, -1);
    this->Refresh();    
}
//---------------------------------------------------------------------------

void __fastcall TfrmBlock::miProcessCurrentClick(TObject *Sender)
{
	PackageContainer * curPackageContainer = GetPackageContainerManager()->GetWorldPackageContainer(m_WatchConnectionIndex);
    if(!curPackageContainer)
        return;
    WOWPackage * curPack = curPackageContainer->GetFilterAll()->At(lvAll->ItemIndex);
    if(!curPack)
    {
        return;
    }
    GetPackageContainerManager()->ProcessOneClientMessage(curPack);
}
//---------------------------------------------------------------------------

void __fastcall TfrmBlock::miJumpHereClick(TObject *Sender)
{
	PackageContainer * curPackageContainer = GetPackageContainerManager()->GetWorldPackageContainer(m_WatchConnectionIndex);
    if(!curPackageContainer)
        return;
    WOWPackage * curPack = curPackageContainer->GetFilterAll()->At(lvAll->ItemIndex);
    if(!curPack)
    {
        return;
    }
    GetGameWorld()->SetCurrentProcessIndex(curPack->GetIndex());
    GetPackageContainerManager()->ProcessClientMessage(1, 1, -1);
    this->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmBlock::cbBlockOnlyClick(TObject *Sender)
{
	GetGameWorld()->SetBlockOnlyMode(cbBlockOnly->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TfrmBlock::lvAllClick(TObject *Sender)
{
	PackageContainer * curPackageContainer = GetPackageContainerManager()->GetWorldPackageContainer(m_WatchConnectionIndex);
	if(!curPackageContainer)
		return;
	WOWReviewerMainFrm->SetCommentText(GetListViewCommentText(lvAll, curPackageContainer->GetFilterAll()));
}
//---------------------------------------------------------------------------

void __fastcall TfrmBlock::btResetBlockOnlyClick(TObject *Sender)
{
	m_BlockOnlyPackIndex = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmBlock::CopyDetail1Click(TObject *Sender)
{
	PackageContainer * curPackageContainer = GetPackageContainerManager()->GetWorldPackageContainer(m_WatchConnectionIndex);
	if(!curPackageContainer)
		return;
	CopyListViewSelectText(lvAll, curPackageContainer->GetFilterAll(), GIT_DETAIL);
}
//---------------------------------------------------------------------------

void __fastcall TfrmBlock::CopyLine1Click(TObject *Sender)
{
	PackageContainer * curPackageContainer = GetPackageContainerManager()->GetWorldPackageContainer(m_WatchConnectionIndex);
	if(!curPackageContainer)
		return;
	CopyListViewSelectText(lvAll, curPackageContainer->GetFilterAll(), GIT_LINE);
}
//---------------------------------------------------------------------------

void __fastcall TfrmBlock::CopyCVS1Click(TObject *Sender)
{
	PackageContainer * curPackageContainer = GetPackageContainerManager()->GetWorldPackageContainer(m_WatchConnectionIndex);
	if(!curPackageContainer)
		return;
	CopyListViewSelectText(lvAll, curPackageContainer->GetFilterAll(), GIT_CVS);
}
//---------------------------------------------------------------------------

