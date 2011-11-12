//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "AutoChatFrm.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmAutoChat *FrmAutoChat;
//---------------------------------------------------------------------------
__fastcall TFrmAutoChat::TFrmAutoChat(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void		TFrmAutoChat::ShowFrm()
{
	this->Show();
}

void __fastcall TFrmAutoChat::btActiveClick(TObject *Sender)
{
	if(GetGameWorld()->GetAutoChatAI()->GetActive())
    {
		GetGameWorld()->GetAutoChatAI()->SetActive(0);
        GetGameWorld()->GetAutoChatAI()->ForceAwake();
    }
    else
    {
        GetFiberManager()->Awake(FWC_WAIT_AUTO_CHAT_START);
    }
}
//---------------------------------------------------------------------------
void			TFrmAutoChat::Refresh()
{
	m_WhoPlayerInfo.clear();
	m_AreaChatAIResult.clear();

	map<String, tagWhoPlayerInfo>	*info = GetGameWorld()->GetAutoChatAI()->GetAreaPlayerWhoInfo();
	map<String, tagAreaChatAIResult>	*result = GetGameWorld()->GetAutoChatAI()->GetAreaChatAIResult();

	for(map<String, tagWhoPlayerInfo>::iterator it = info->begin(); it != info->end(); it++)
	{
		m_WhoPlayerInfo.push_back(it->second);
	}

	for(map<String, tagAreaChatAIResult>::iterator it = result->begin(); it != result->end(); it++)
	{
		m_AreaChatAIResult.push_back(it->second);
	}

	gbProcessing->Caption = FormatStr("cnt = %d", m_AreaChatAIResult.size());
	ListView_SetItemCountEx(lvProcess->Handle, m_AreaChatAIResult.size(), LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
	lvProcess->Refresh();

	gbAll->Caption = FormatStr("cnt = %d", m_WhoPlayerInfo.size());
	ListView_SetItemCountEx(lvAll->Handle, m_WhoPlayerInfo.size(), LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
	lvAll->Refresh();

}

void __fastcall TFrmAutoChat::Timer1Timer(TObject *Sender)
{
	Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TFrmAutoChat::lvProcessData(TObject *Sender, TListItem *Item)
{
	if(Item->Index < 0 || Item->Index >= (int)m_AreaChatAIResult.size())
		return;
	tagAreaChatAIResult *result = &m_AreaChatAIResult[Item->Index];
	Item->Caption = Item->Index;
	Item->SubItems->Add(result->AreaName);
	Item->SubItems->Add(result->PlayerCount);
	Item->SubItems->Add(result->ProcessCount);
	Item->SubItems->Add(result->Expired);
}
//---------------------------------------------------------------------------

void __fastcall TFrmAutoChat::lvAllData(TObject *Sender, TListItem *Item)
{
	if(Item->Index < 0 || Item->Index >= (int)m_WhoPlayerInfo.size())
		return;
	tagWhoPlayerInfo *result = &m_WhoPlayerInfo[Item->Index];
	Item->Caption = Item->Index;
	Item->SubItems->Add(result->Player_Name);
	Item->SubItems->Add(result->Guild_Name);
	Item->SubItems->Add(result->level);
	Item->SubItems->Add(result->Class);
	Item->SubItems->Add(result->Race);
	Item->SubItems->Add(result->ZoneID);
}
//---------------------------------------------------------------------------

void __fastcall TFrmAutoChat::btSetClick(TObject *Sender)
{
	GetGameWorld()->GetAutoChatAI()->SetSendText(edtText->Text);
}
//---------------------------------------------------------------------------

