//---------------------------------------------------------------------------


#pragma hdrstop

#include "MessageContainer.h"
#include "Applang.h"
#include "Commfunc.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

String	GetChannelName(IChannelType ct)
{
    switch(ct)
	{
        case ctCmd:
                return _DT("命令行");
        case ctSys:
                return _DT("系统");
        case ctGameSys:
                return _DT("游戏");
        case ctBattle:
                return _DT("战斗");
        case ctPublic:
                return _DT("公");
        case ctCur:
                return _DT("轻");
        case ctGroup:
                return _DT("帮");
        case ctFriend:
                return _DT("友");
        case ctTeam:
                return _DT("队");
        case ctPlayer:
				return _DT("密");
		case ctGM:
				return _DT("GM问答");
		case ctSysAnswer:
				return _DT("问答");
        default :
                return "";
	}
}


MessageContainer::MessageContainer():
							m_Recs(true, MAX_LINE_COUNT)
{
	m_View = NULL;

    m_ChannelColor[0].channelColor = clMaroon;
	m_ChannelColor[1].channelColor = clBlack;
	m_ChannelColor[2].channelColor =clGreen;
	m_ChannelColor[3].channelColor =clPurple;
	m_ChannelColor[4].channelColor =clRed;
	m_ChannelColor[5].channelColor =clTeal;
	m_ChannelColor[6].channelColor =clFuchsia;
	m_ChannelColor[7].channelColor =clMaroon;
	m_ChannelColor[8].channelColor =clNavy;
	m_ChannelColor[9].channelColor =clLime;
}

MessageContainer::~MessageContainer()
{
}

tagChatConfig   *  MessageContainer::GetDefColor(int index)
{
    if(index >= 0 && index < MAX_CHANNEL)
        return  &m_ChannelColor[index];


    return  NULL;
}

void	MessageContainer::Init(int msgType)
{
	m_MsgType = msgType;
}

void	MessageContainer::BindControl(TListView * lvView)
{
	m_View = lvView;
    if(m_View)
    {
        m_View->OnCustomDrawItem = m_ViewCustomDrawItem;
        m_View->OnCustomDrawSubItem = m_ViewCustomDrawSubItem;
        m_View->OnData = m_ViewData;
        Refresh();
    }
}


void __fastcall MessageContainer::m_ViewCustomDrawItem(TCustomListView *Sender,
							TListItem *Item, TCustomDrawState State, bool &DefaultDraw)
{
    if(m_View == NULL)
        return;
	if(!State.Contains(cdsDisabled))
    {
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
            Flags = m_View->DrawTextBiDiModeFlags(Sender->Column[0]->Alignment);
            OffsetRect(&tDrawRect, 2, 2);
            DrawText(tCanvas->Handle, Item->Caption.c_str(), Item->Caption.Length(), &tDrawRect, Flags);
            for(int i = 0; i< ((TListView *)Sender)->Columns->Count; i++)
            {
                m_View->OnCustomDrawSubItem(Sender, Item, i, State, DefaultDraw);
            }

            DefaultDraw = false;
        }

        catch(...)
        {}
    }
}

void __fastcall MessageContainer::m_ViewCustomDrawSubItem(TCustomListView *Sender,
								TListItem *Item, int SubItem, TCustomDrawState State,
								bool &DefaultDraw)
{
	if (Item==NULL)
        return;
    if(m_View == NULL)
        return;
    TInfoRecord *InfoRecord = m_Recs.At(Item->Index);
    if (InfoRecord==NULL)
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
        char szSubItemText[4096];
        tCanvas = Sender->Canvas;
        try
        {
            crOldColor = GetTextColor(tCanvas->Handle);
            ZeroMemory(szSubItemText, sizeof(szSubItemText));
            ListView_GetItemText(Sender->Handle, Item->Index, SubItem, szSubItemText, sizeof(szSubItemText) - 1);
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
            GetTextExtentPoint32(tCanvas->Handle, szSubItemText, strlen(szSubItemText), &lpSize);
            if(lpSize.cx > tDrawRect.Width())
                lpSize.cx = tDrawRect.Width();
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
            //字段着色
			if(SubItem == 0)      //时间
            {
                if(!State.Contains(cdsSelected))
                {
                    SetTextColor(tCanvas->Handle,clBlue);
                }
            }
			else if(SubItem == 1)  //类型
            {
                if(!State.Contains(cdsSelected))
                {
                    SetTextColor(tCanvas->Handle,GetDefColor(InfoRecord->Channel)->channelColor);
                }
			}
			else if(SubItem == 2)  //发送者
            {
                if(!State.Contains(cdsSelected))
                {
                    SetTextColor(tCanvas->Handle,clBlack);
                }
            }
			else if(SubItem == 3)  //信息
            {
                if(!State.Contains(cdsSelected))
                {
                    SetTextColor(tCanvas->Handle, GetDefColor((int)InfoRecord->Channel)->channelColor);
                }
            }
            DrawText(tCanvas->Handle, szSubItemText, strlen(szSubItemText), &tDrawRect, 0);
            SetTextColor(tCanvas->Handle, crOldColor);
            DefaultDraw = false;
        }
        catch(...)
        {}
    }
}

void            MessageContainer::RefreshCurItemText(TListItem *Item, TInfoRecord *InfoRecord)
{
    if(InfoRecord == NULL || Item == NULL)
    {
        return;
	}
	if(m_MsgType == 0)
	{
		Item->Caption = InfoRecord->LogTime;
		Item->SubItems->Add(InfoRecord->ChannelName());
		Item->SubItems->Add(InfoRecord->Sender);
		Item->SubItems->Add(InfoRecord->Info);
	}
	else
	{
		Item->Caption = InfoRecord->LogTime;
		Item->SubItems->Add(InfoRecord->Info);
	}
}

void __fastcall MessageContainer::m_ViewData(TObject *Sender, TListItem *Item)
{
    if(Item == NULL)
        return;

    TInfoRecord *InfoRecord = m_Recs.At(Item->Index);
    RefreshCurItemText(Item, InfoRecord);
}

bool            MessageContainer::IsNeedAutoScroll()
{
    if(m_View == NULL)
		return false;
    if(m_Recs.Count() == 0)
        return  true;

    bool    result = false;
	tagSCROLLINFO	scrollInfo;
	scrollInfo.cbSize = sizeof(scrollInfo);
	scrollInfo.fMask = SIF_RANGE | SIF_POS | SIF_PAGE;
	GetScrollInfo(m_View->Handle, SB_VERT, &scrollInfo);
	if(scrollInfo.nPos == (int)(scrollInfo.nMax - scrollInfo.nPage + 1))
	{
		result = true;
	}
	else
		result = false;
    return  result;
}

bool		MessageContainer::Refresh()
{
    if(m_View == NULL)
        return true;
	if(IsNeedAutoScroll())
	{
		m_View->Items->Count = m_Recs.Count();
		if(m_View->Items->Count > 0)
		{
			m_View->ItemIndex = m_View->Items->Count-1;
			m_View->Selected->MakeVisible(true);
		}
       	m_View->Repaint();
        return  true;
	}
    return false;
}

void		MessageContainer::Add(int channel, String sender, String info)
{
	if(GetDefColor(channel)->show == false)
		return;

	TInfoRecord	*	addRec = new TInfoRecord;
	addRec->Channel = channel;
	addRec->Sender = sender;
	addRec->Info = info;
	addRec->LogTime = TimeToStr(Now());
	
	if(m_Recs.Count() >= MAX_LINE_COUNT)
	{
		m_Recs.Delete(0);
	}
	m_Recs.Add(addRec);
	bool result = Refresh();

    if(result == false)
    {
        TListItem * curItem = m_View->Items->Add();
        RefreshCurItemText(curItem, addRec);
    }
}

void		MessageContainer::Clear()
{
	m_Recs.Clear();
	Refresh();
}

void		MessageContainer::SaveToFile(String fileName)
{
	auto_ptr<TStringList> SaveList(new TStringList());
	String sender;
	for (int i=0;i<m_Recs.Count() ;i++)
	{
		sender = m_Recs[i]->Sender;
		if(sender == "")
			sender = " ";
        SaveList->Add(FormatStr("%s [%s]:%s  %s",m_Recs[i]->LogTime,
								m_Recs[i]->ChannelName(),
                                sender,
                                m_Recs[i]->Info));
    }
    SaveList->SaveToFile(fileName);
}
