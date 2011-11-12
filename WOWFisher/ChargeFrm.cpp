//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ChargeFrm.h"
#include "ClientAuther.h"
#include "ShareDef.h"
#include "ClientServerShared.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmChargeFrm *frmChargeFrm;
//---------------------------------------------------------------------------
__fastcall TfrmChargeFrm::TfrmChargeFrm(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmChargeFrm::FormCreate(TObject *Sender)
{
//	PageControl1->ActivePageIndex = 0;
}
//---------------------------------------------------------------------------
void __fastcall TfrmChargeFrm::btChargeClick(TObject *Sender)
{
	AnsiString cardNo = edtChargeText->Text;
	AnsiString acc = edtAcc->Text;
	if(cardNo.Length() < CHARGE_CARD_SIZE_MIN || cardNo.Length() > CHARGE_CARD_SIZE_MAX)
	{
		ShowMessage(GBText("充值卡格式错误"));
		return;
	}
	for(int i=0; i<acc.Length(); i++)
	{
		if(acc.c_str()[i] < 0)
		{
			ShowMessage(GBText("你输入的游戏帐号有误, 请确认你输入的是游戏帐号, 不是角色名称!"));
			return;
		}
	}
	String msg = FormatStr(GBText("你准备给账号[%s]充值, 是否确定?"), String(acc));
	if (Application->MessageBox(msg.c_str(),L"Charge",MB_OKCANCEL)!=IDOK)
	{
		return;
	}

//	PageControl1->ActivePageIndex = 1;
	memChargeMsg->Lines->Clear();
	GetClientAuth()->BeginCharge(acc, cardNo);
}
//---------------------------------------------------------------------------
void	TfrmChargeFrm::AddLog(String log)
{
	if(memChargeMsg->Lines->Count > 1000)
	{
		memChargeMsg->Lines->Clear();
	}
	memChargeMsg->Lines->Add(log);
}

void	TfrmChargeFrm::ShowFrm()
{
	if(this->Showing)
		return;
	memChargeMsg->Lines->Clear();
	this->Show();
}
