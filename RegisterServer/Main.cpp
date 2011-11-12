//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Main.h"
#include "AuthServerListener.h"
#include "ClientServerShared.h"
#include "ShareDef.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cspin"
#pragma resource "*.dfm"
#pragma link "ws2_32.lib"
TMainFrm *MainFrm;
//---------------------------------------------------------------------------
__fastcall TMainFrm::TMainFrm(TComponent* Owner)
    : TForm(Owner)
{
	this->WindowProc = WndProcs;
}
//---------------------------------------------------------------------------


void __fastcall TMainFrm::FormCreate(TObject *Sender)
{
	String filePath = ExtractFilePath(Application->ExeName) + "Log\\";
	GetLog()->SetPath(filePath);
	GetLog()->SetFileName(filePath + "RegisterServer.log");
	PageControl1->ActivePageIndex = 0;
	GetAuthServerListener()->SetDatabaseIP("127.0.0.1");
	GetAuthServerListener()->SetDatabaseUserID("wow");
	GetAuthServerListener()->SetDatabaseUserPsw("1qaz2wsx");
	GetAuthServerListener()->SetDatabasePort(17589);
	if(!GetAuthServerListener()->Start(AUTH_SERVER_LIST_PORT))
	{
		ShowMessage(GBText("无法开启, 端口已被占用? 请检查是否开了多个注册服务!"));
        Application->Terminate();
		return;
	}

	m_ADOConnection = new TADOConnection(NULL);
	m_ADOQuery = new TADOQuery(NULL);
	m_ADOQuery->Connection = m_ADOConnection;

	m_ADOConnection->LoginPrompt = false;
	m_ADOConnection->KeepConnection = true;
	m_ADOConnection->ConnectionTimeout = SQL_TIMEOUT;
	m_ADOConnection->ConnectionString= FormatStr("Provider=SQLOLEDB.1;Persist Security Info=True;User ID=%s;Password=%s;Initial Catalog=wowwg;Data Source=%s,%d",
		GetAuthServerListener()->GetDatabaseUserID(), GetAuthServerListener()->GetDatabaseUserPsw(), GetAuthServerListener()->GetDatabaseIP(), GetAuthServerListener()->GetDatabasePort());
	m_ADOConnection->Connected=true;
	GetThreadManager()->StartAll();

	RefreshCardTypes();
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::FormDestroy(TObject *Sender)
{
	GetAuthServerListener()->Close();
	GetThreadManager()->FreeAll();
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::Timer1Timer(TObject *Sender)
{
	ListView_SetItemCountEx(lvThread->Handle, GetThreadManager()->Count(), LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
	lvThread->Refresh();

	labThreadState->Caption = FormatStr("ThreadCnt:%d, ClientCnt:%d", GetThreadManager()->Count(), GetAuthServerListener()->GetUserCount());

	GetAuthServerListener()->ProcessCloseClients();
	GetThreadManager()->ProcessDeletedThread();

	while(GetThreadManager()->GetGUIMessageCount())
	{
		String result;
		if(!GetThreadManager()->PopGUIMessage(&result))
		{
			break;
		}
		AddLog(result);
	}
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::ApplicationEvents1Minimize(TObject *Sender)
{
	Application->Minimize();
	ShowWindow(Application->Handle, SW_HIDE);
	this->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::TrayIcon1DblClick(TObject *Sender)
{
	Application->Restore();
	ShowWindow(Application->Handle, SW_RESTORE);
	SetForegroundWindow(Application->Handle);
	this->Visible = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::WndProcs(Messages::TMessage &Message)
{
	if(Message.Msg == WM_CLOSE)
	{
		ApplicationEvents1Minimize(this);
		return;
	}
    this->WndProc(Message);
}
void __fastcall TMainFrm::miCloseWndClick(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::TrayIcon1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y)
{
	if(Button != mbRight)
	{
		return;
	}
	pmTray->Popup(X, Y);
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::lvThreadData(TObject *Sender, TListItem *Item)
{
	WYThread * curWYThread = GetThreadManager()->At(Item->Index);
	if(!curWYThread)
		return;

	Item->Caption = curWYThread->ThreadID;
	Item->SubItems->Add(curWYThread->GetName());
	Item->SubItems->Add(curWYThread->GetStateName());
}
//---------------------------------------------------------------------------
//int					TMainFrm::TestThread(SingleThread * thread)
//{
//	TADOConnection	*		m_ADOConnection;
//	TADOQuery *				m_ADOQuery;
// 	m_ADOConnection = new TADOConnection(NULL);
//	m_ADOQuery = new TADOQuery(NULL);
//	m_ADOQuery->Connection = m_ADOConnection;
//
//	m_ADOConnection->LoginPrompt = false;
//	m_ADOConnection->KeepConnection = true;
//	m_ADOConnection->ConnectionTimeout = SQL_TIMEOUT;
//	m_ADOConnection->ConnectionString= FormatStr("Provider=SQLOLEDB.1;Persist Security Info=True;User ID=%s;Password=%s;Initial Catalog=wowwg;Data Source=%s,%d",
//		GetAuthServerListener()->GetDatabaseUserID(), GetAuthServerListener()->GetDatabaseUserPsw(), GetAuthServerListener()->GetDatabaseIP(), GetAuthServerListener()->GetDatabasePort());
//	m_ADOConnection->Connected=true;
//
//	m_ADOQuery->SQL->Clear();
//	m_ADOQuery->SQL->Add(FormatStr("UPDATE top (1) wow_card SET is_card_send = 1 , send_time = '%s' output  INSERTED.card_no WHERE card_type = %d and is_card_send = 0",
//			DateTimeToStr(Now()), 1));
//	try
//	{
//		m_ADOQuery->Open();
//	} catch (Exception &e)
//	{
//		GetLog()->Warn("Error : %s", e.Message);
//	}
//
//	if(m_ADOQuery->RecordCount == 0)
//	{
//		GetLog()->Warn("ERROR");
//	}
//	GetLog()->Warn("OK~");
//	return -1;
//}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::btCreateCareClick(TObject *Sender)
{
	String cardType;
	for(int i=0; i<GetAuthServerListener()->GetCardInfoCount(); i++)
	{
		tagCardInfo *info = GetAuthServerListener()->GetCardInfoByIndex(i);
		if(info->CardName == cbCardType->Text)
		{
			cardType = info->CardType;
		}
	}
	if(cardType == "")
	{
		ShowMessage(GBText("未知卡类型"));
		return;
	}

	int cardCount = edtCardCount->Value;
	String msg = FormatStr(GBText("准备生成 %s %d 张, 是否确定?"), GetCardNameByCardType(cardType), cardCount);
	if (Application->MessageBox(msg.c_str(),L"Create Card",MB_OKCANCEL)!=IDOK)
	{
		return;
	}

	GenerateCard(m_ADOQuery, cardType, cardCount);

	int total = GetAllFreeCardCount(m_ADOQuery);
	ShowMessage(FormatStr(GBText("生成成功, 现在数据库里面有%d张卡!"), total));
}
//---------------------------------------------------------------------------
void __fastcall TMainFrm::btChargeClick(TObject *Sender)
{
	String fileName = ExtractFilePath(Application->ExeName) + "ChargeList.csv";
	if(!FileExists(fileName))
	{
		ShowMessage(FormatStr(GBText("找不到文件:%s"), fileName));
		return;
	}
	auto_ptr<TStringList>   charge(new TStringList);
	try{
		charge->LoadFromFile(fileName);
	}catch(Exception &e)
	{
		ShowMessage(FormatStr(GBText("%s(关闭excel?)"), e.Message));
		return;
	}
	vector<vector<String> > results;

	auto_ptr<TStringList> 	splitResult(new TStringList);
	for(int i=0; i<charge->Count; i++)
	{
		vector<String> curLine;
		SplitStr(charge->Strings[i], ",", splitResult.get());
		if(splitResult->Count != 2)
		{
			ShowMessage(FormatStr(GBText("[%s] 这一行格式错误"), charge->Strings[i]));
			return;
		}
		for(int j=0; j<splitResult->Count; j++)
		{
			curLine.push_back(splitResult->Strings[j]);
		}
		results.push_back(curLine);
	}

	map<String, int> cardTypes;
	for(DWORD i=0; i<results.size(); i++)
	{
		String cardType = results[i][1];
		if(cardTypes.find(cardType) == cardTypes.end())
		{
			cardTypes[cardType] = 1;
		}
		else
		{
			cardTypes[cardType] += 1;
		}
	}

	for(map<String, int>::iterator it = cardTypes.begin();
		it != cardTypes.end(); it++)
	{
		m_ADOQuery->SQL->Text = FormatStr("SELECT count(*) as cnt FROM wow_card WHERE is_card_send = 0 and card_type = '%s'", it->first);
		m_ADOQuery->Open();
		int curCnt = m_ADOQuery->FieldByName("cnt")->AsInteger;
		if(it->second >= curCnt)
		{
			ShowMessage(FormatStr(GBText("充值卡类型:(%s)过少, 需要%d张, 但是只有%d张, 请先生成卡!"), it->first, it->second, curCnt));
			return;
		}
	}

	vector<String> outputMsg;
	for(DWORD i=0; i<results.size(); i++)
	{
		String cardType = results[i][1];
		String cardNoOutput;
		if(!GetCard(m_ADOQuery, cardType, &cardNoOutput, &outputMsg))
		{
			ShowMessage(FormatStr(GBText("批量领卡失败!已经领取了%d张卡, 这些卡已作废, 请重新生成卡!"), i));
			return;
		}
		results[i].push_back(cardNoOutput);
	}

	for(DWORD i=0; i<results.size(); i++)
	{
		outputMsg.push_back(FormatStr(GBText("给玩家(%s)冲卡, 类型(%s), 卡号(%s)"), results[i][0], results[i][1], results[i][2]));
		if(!Charge(m_ADOQuery, results[i][0], results[i][2], &outputMsg))
		{
			outputMsg.push_back(FormatStr(GBText("用户(%s)充值失败!充值类型:(%s)充值卡号:(%s)"), results[i][0], results[i][1], results[i][2]));
		}
	}

	String savePath = ExtractFilePath(Application->ExeName) + "ChargeLog\\";
	if(!DirectoryExists(savePath))
	{
        ForceDirectories(savePath);
	}

	String chargeHistory = savePath + GetFileNameByDate("ChargeList", "csv");
	String chargeLog = savePath + GetFileNameByDate("ChargeList", "txt");
	auto_ptr<TStringList> saveStr(new TStringList);
	saveStr->Clear();
	for(DWORD i=0; i<results.size(); i++)
	{
		saveStr->Add(FormatStr("%s,%s,%s", results[i][0], results[i][1], results[i][2]));
	}
	saveStr->SaveToFile(chargeHistory);

	saveStr->Clear();
	for(DWORD i=0; i<outputMsg.size(); i++)
	{
		saveStr->Add(outputMsg[i]);
	}
	saveStr->SaveToFile(chargeLog);
	DeleteFile(fileName);
	ShowMessage(FormatStr(GBText("冲卡成功!冲入了(%d)个玩家!"), results.size()));
}
//---------------------------------------------------------------------------

void				TMainFrm::AddLog(String msg)
{
	if(memLog->Lines->Count > 10000)
		memLog->Lines->Clear();

	memLog->Lines->Add(DateTimeToStr(Now()) + ":");
	memLog->Lines->Add(msg);
}
void __fastcall TMainFrm::btGetCardClick(TObject *Sender)
{
	String cardType;
	for(int i=0; i<GetAuthServerListener()->GetCardInfoCount(); i++)
	{
		tagCardInfo *info = GetAuthServerListener()->GetCardInfoByIndex(i);
		if(info->CardName == cbGetCardType->Text)
		{
			cardType = info->CardType;
		}
	}
	if(cardType == "")
	{
		ShowMessage(GBText("未知卡类型"));
		return;
	}

	int cardCount = edtGetCardNum->Value;

	m_ADOQuery->SQL->Clear();
	m_ADOQuery->SQL->Text = FormatStr("SELECT count(*) as cnt FROM wow_card WHERE is_card_send = 0 and card_type = '%s'", cardType);
	m_ADOQuery->Open();
	int total = m_ADOQuery->FieldByName("cnt")->AsInteger;
	if(total <= cardCount)
	{
		ShowMessage(FormatStr(GBText("数据库中%s过少, 现有%d张, 需要%d张, 需要至少再生成%d张!"), GetCardNameByCardType(cardType),
				total, cardCount, cardCount - total + 1));
		return;
	}

	String msg = FormatStr(GBText("准备取出 %s %d 张, 是否确定?"), GetCardNameByCardType(cardType), cardCount);
	if (Application->MessageBox(msg.c_str(),L"Create Card",MB_OKCANCEL)!=IDOK)
	{
		return;
	}

	vector<String> outputMsg;
	auto_ptr<TStringList> cardOutput(new TStringList);
	for(int i=0; i<cardCount; i++)
	{
		String cardNoOutput;
		if(!GetCard(m_ADOQuery, cardType, &cardNoOutput, &outputMsg))
		{
			ShowMessage(FormatStr(GBText("生成失败了, 目前生成了%d张!"), cardOutput->Count));
			break;
		}
		cardOutput->Add(cardNoOutput);
	}

	String getCardPath = ExtractFilePath(Application->ExeName) + "GetCard\\";
	if(!DirectoryExists(getCardPath))
	{
        ForceDirectories(getCardPath);
	}
	String saveName = getCardPath + GetFileNameByDate(cardType, "txt");
	cardOutput->SaveToFile(saveName);

	memGetResult->Lines->Clear();
	memGetResult->Lines->AddStrings(cardOutput.get());

	total = GetAllFreeCardCount(m_ADOQuery);
	ShowMessage(FormatStr(GBText("取出成功, 现在数据库里面有%d张卡! 记录保存于:%s"), total, saveName));
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::btQueryCardClick(TObject *Sender)
{
	int total = GetAllFreeCardCount(m_ADOQuery);
	ShowMessage(FormatStr(GBText("现在数据库里面有%d张卡!"), total));
}
//---------------------------------------------------------------------------

void __fastcall TMainFrm::btRefreshCardTypesClick(TObject *Sender)
{
	RefreshCardTypes();
}
//---------------------------------------------------------------------------

void				TMainFrm::RefreshCardTypes()
{
	m_ADOQuery->SQL->Text = "SELECT * FROM card_info";
	m_ADOQuery->Open();
	m_ADOQuery->First();
	cbCardType->Items->Clear();
	cbGetCardType->Items->Clear();
	while(!m_ADOQuery->Eof)
	{
		String cardName = m_ADOQuery->FieldByName("card_name")->AsString;
		String cardType = m_ADOQuery->FieldByName("card_type")->AsString;
		int cardDay = m_ADOQuery->FieldByName("day")->AsInteger;
		int cardMoney = m_ADOQuery->FieldByName("money")->AsInteger;
		GetAuthServerListener()->AddCardInfo(cardType, cardDay, cardMoney, cardName);
		cbCardType->Items->Add(cardName);
		cbGetCardType->Items->Add(cardName);
		m_ADOQuery->Next();
	}

}
