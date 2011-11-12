//---------------------------------------------------------------------------

#include <vcl.h>
#include <Clipbrd.hpp>
#pragma hdrstop

#include "Main.h"
#include "AuthLoader.h"
#include "CommFunc.h"
#include "Log4Me.h"
#include "CommPlus.h"
#include "ShareDef.h"
#include "gameworld.h"
#include "Opcodes.h"
#include "FiberContext.h"
#include "KOEItlbm.h"
#include "FiberCode.h"
#include "DBCStructureInfo.h"
#include "WOWProxy.h"
#include "SharedMemInfo.h"
#include "FishAI.h"
#include "ClientAuther.h"
#include "ChargeFrm.h"
#include "themidasdk.h"
#include "AuthPackageDispatcher.h"
#include "PackageContainer.h"

#ifdef _DEBUG
#include "BlockWindowFrm.h"
#include "CommentFrm.h"
#include "DataViewerFrm.h"
#include "GameDataViewerFrm.h"
#include "WOWPacketReviewer.h"
#include "MapFrm.h"
#include "ValuesUpdateFrm.h"
#include "AutoChatFrm.h"
#include "DrawMapFrm.h"
#include "DockFrm.h"
#endif
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
#pragma link "ws2_32.lib"
#pragma link "Psapi.lib"
TWOWFisherMain *WOWFisherMain;
//---------------------------------------------------------------------------
__fastcall TWOWFisherMain::TWOWFisherMain(TComponent* Owner)
	: TForm(Owner)
{
	this->WindowProc = WndProcs;
	m_FrmInited = false;
}
//---------------------------------------------------------------------------
void __fastcall TWOWFisherMain::FormCreate(TObject *Sender)
{
	if(!IsWin2k())
	{
		ShowMessage(GBText("你的操作系统版本过低, 需要win2000及以后的操作系统"));
		Application->Terminate();
		return;
	}
	PageControl1->ActivePageIndex = 0;
	ExtractDllFromExe();
	#ifndef _DEBUG
	tsDebug->TabVisible = false;
	#endif
	GetLog()->SetEnableLog(true);
	GetSharedMemInfo()->CreateMapping();
	String filePath = ExtractFilePath(Application->ExeName) + "Log\\";
    GetLog()->SetPath(filePath);
	GetLog()->SetFileName(filePath + "WOWFisher.log");
    GetLog()->SetGUIWindow(this->Handle);
    GetLog()->Warn("Proc Init");
	GetLog()->Info("Current ThreadID = %d", GetCurrentThreadId());
	int  listenPort = HOST_PORT;
	WOWHookViewInfo * view = GetSharedMemInfo()->CreateEmpty(listenPort);
	if(!view)
	{
		ShowMessage("FULL!");
		return;
	}
	listenPort = view->HostPortNumber;
	String dllName = GetGameWorld()->GetDllFileName();
	if(dllName == "")
	{
		dllName = ExtractFilePath(Application->ExeName) + "wowgo.dll";
	}
	GetGameWorld()->InjectDll(dllName, typeid(*this).name());
	if(!GetWOWProxyManager()->Start(listenPort))
	{
		return;
	}

	GetWOWProxyManager()->fpOnUserAuthPacket = OnUserAuthPacket;
	GetThreadManager()->StartAll();
	GetGameWorld()->InitFiberProcesser();
	GetGameWorld()->LoadItemNameData();
	GetGameWorld()->LoadFishData();

	GetFiberManager()->Process();
	#ifdef _DEBUG
	GetFiberManager()->Awake(FWC_REACTION_START);
	InitDebugFrms();
	#endif
}
//---------------------------------------------------------------------------
void __fastcall TWOWFisherMain::FormDestroy(TObject *Sender)
{
    GetLog()->Warn("TWOWFisherMain::FormDestroy");
    GetLog()->SetEnableLog(false);

    for(int i=0; i<GetWOWProxyPool()->GetProxyCount(); i++)
    {
        GetWOWProxyPool()->GetProxy(i)->Close();
    }

	GetThreadManager()->FreeAll();
}
//---------------------------------------------------------------------------

void __fastcall TWOWFisherMain::WndProcs(Messages::TMessage &Message)
{
    if(Message.Msg == WM_COPYDATA)
    {
        COPYDATASTRUCT * sendData = (COPYDATASTRUCT *)Message.LParam;
		String msg = String((TCHAR *)sendData->lpData, sendData->cbData / sizeof(TCHAR));

		#ifdef _DEBUG
		if(WOWReviewerMainFrm)
			WOWReviewerMainFrm->LogMsg(msg);
		#endif
        if(sendData->dwData == MSG_CONNECT)
        {
            GetWOWProxyManager()->SetDestAddress(msg);
        }
        else if(sendData->dwData == MSG_TOP_WINDOW)
        {
            this->SetFocus();
            this->BringToFront();
            this->Show();
            Application->BringToFront();
        }
        else if(sendData->dwData == MSG_SESSIONKEY)
        {
            //得到了SessionKey
			//颠倒一下
			GetGameWorld()->SetClientSessionKey(msg);
        }
	}
	else if(Message.Msg == WM_CLOSE)
	{
		ApplicationEvents1Minimize(this);
		return;
	}
    this->WndProc(Message);
}

void			TWOWFisherMain::InitDebugFrms()
{
	#ifdef _DEBUG
	if(m_FrmInited)
		return;

	WOWReviewerMainFrm = new TWOWReviewerMainFrm(this);
	frmBlock = new TfrmBlock(this);
	FrmComment = new TFrmComment(this);
	FrmMap = new TFrmMap(this);
	FrmDBCViewer = new TFrmDBCViewer(this);
	FrmGameDataViewer = new TFrmGameDataViewer(this);
	FrmValuesUpdate = new TFrmValuesUpdate(this);
	FrmAutoChat = new TFrmAutoChat(this);
	FrmDrawMap = new TFrmDrawMap(this);
	frmDock = new TfrmDock(this);
	m_FrmInited = true;
	#endif
}

void __fastcall TWOWFisherMain::btDebugClick(TObject *Sender)
{
	#ifdef _DEBUG
	WOWReviewerMainFrm->Show();
	WOWReviewerMainFrm->Left = 0;
	WOWReviewerMainFrm->Top = 0;
	#endif
}
//---------------------------------------------------------------------------


void			TWOWFisherMain::LogMsg(String msg)
{
	GetLog()->Warn(msg);
	if(memLog->Lines->Count > 10000)
	{
		memLog->Lines->Clear();
	}
//	memLog->Lines->Add(FormatStr("[%s]:", DateTimeToStr(Now())));
	memLog->Lines->Add(msg);
}

void			TWOWFisherMain::OnUserAuthPacket(WOWProxy *proxy, WOWPackage *packet)
{
	#ifdef _DEBUG
	return;
	#endif
	if(proxy != GetWOWProxyManager()->GetActiveRealmd())
		return;
	char *lpdata = packet->GetOrgData().c_str();
	int len = packet->GetOrgData().Length();
	String username;
	if(lpdata[0] == 0)
	{
		AUTH_LOGON_CHALLENGE_C *pack = (AUTH_LOGON_CHALLENGE_C *)lpdata;
		username = AnsiString((char *)pack->I, pack->I_len);
	}
	else
	{
		int pos = len-1;
		while(pos >= 0 && lpdata[pos])
		{
			pos--;
		}
		pos += 5;
		if(len - pos > 0)
		{
			username = AnsiString(lpdata + pos, len - pos);
		}
		else
		{
		}
	}

//	LogMsg(FormatStr("ThreadID:%d", GetCurrentThreadId()));
//	LogMsg(username);
//	LogMsg(BinToStr(lpdata, len));
	DWORD addr = 0;
	DWORD offset = 0;
//	LogMsg(FormatStr("验证:用户名(%s)", username));
	if(!GetClientAuth()->BeginAuth(username, GetSharedMemInfo()->FindSelf()->Build, &addr, &offset))
	{
//		LogMsg("验证失败了");
		return;
	}

	GetSharedMemInfo()->FindSelf()->BaseAddr = addr;
	GetSharedMemInfo()->FindSelf()->BaseAddrOffset = offset;
	proxy->ServerAuthOKBeginProxy();
//	LogMsg("验证成功");
}
void __fastcall TWOWFisherMain::Timer1Timer(TObject *Sender)
{

	GetPackageContainerManager()->PopQueue(GetWOWProxyManager()->GetAllQueue());

    GetPackageContainerManager()->ProcessClientMessage();

	GetFiberManager()->Process();

	PackageContainer * curPackageContainer = GetPackageContainerManager()->GetWorldPackageContainer();
	if(curPackageContainer)
	{
		#ifdef _DEBUG
		int removeNum = 10000;
		#else
		int removeNum = 100;
		#endif
		if(removeNum != 0 && curPackageContainer->GetAll()->Count() > removeNum)
		{
			GetPackageContainerManager()->ClearAllPackage();
		}
	}

	GetWOWProxyManager()->ProcessRemoveProxyList();
	GetThreadManager()->ProcessDeletedThread();
	GetGameWorld()->CheckWOWClosedRefresh();

	String result;
	while(GetThreadManager()->GetGUIMessageCount())
	{
		if(!GetThreadManager()->PopGUIMessage(&result))
		{
			continue;
		}
		if(result == "REQ_CHARGE")
		{
			//弹出注册页面
			frmChargeFrm->ShowFrm();
			continue;
		}
		LogMsg(result);
		frmChargeFrm->AddLog(result);
	}
}
void			TWOWFisherMain::Refresh()
{
	ListView_SetItemCountEx(lvFishResult->Handle, GetGameWorld()->GetDataByKey("fish_results")->GetChildCount(), LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
	lvFishResult->Refresh();

	ListView_SetItemCountEx(lvFishFilter->Handle, GetGameWorld()->GetItemPickupListCount(), LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
	lvFishFilter->Refresh();

	int pickCnt = GetGameWorld()->GetDataInt("fish_result_count/pick");
	int nopickCnt = GetGameWorld()->GetDataInt("fish_result_count/nopick");
	gbFishResult->Caption = FormatStr(GBText("钓鱼记录.拾取数(%d).丢弃数(%d).总数(%d)"), pickCnt, nopickCnt, pickCnt + nopickCnt);
}
//---------------------------------------------------------------------------

void __fastcall TWOWFisherMain::ApplicationEvents1Minimize(TObject *Sender)
{
	Application->Minimize();
	ShowWindow(Application->Handle, SW_HIDE);
	this->Visible = false;
}
//---------------------------------------------------------------------------

void __fastcall TWOWFisherMain::TrayIcon1DblClick(TObject *Sender)
{
	Application->Restore();
	ShowWindow(Application->Handle, SW_RESTORE);
	SetForegroundWindow(Application->Handle);
	this->Visible = true;
}
//---------------------------------------------------------------------------


void __fastcall TWOWFisherMain::TrayIcon1MouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	if(Button != mbRight)
	{
		return;
	}
	pmTray->Popup(X, Y);
}
//---------------------------------------------------------------------------

void __fastcall TWOWFisherMain::miCloseWndClick(TObject *Sender)
{
	this->Close();
}
//---------------------------------------------------------------------------

void __fastcall TWOWFisherMain::btAuthClick(TObject *Sender)
{
	memLog->Lines->Clear();
	DWORD addr = 0;
	DWORD offset = 0;
	String username = "eggxp";
	LogMsg(FormatStr("验证:用户名(%s)", username));
	if(!GetClientAuth()->BeginAuth(username, 11159, &addr, &offset))
	{
		LogMsg("验证失败了");
		return;
	}

	GetSharedMemInfo()->FindSelf()->BaseAddr = addr;
	GetSharedMemInfo()->FindSelf()->BaseAddrOffset = offset;
//	proxy->ServerAuthOKBeginProxy();
	LogMsg(FormatStr("验证成功addr:0x%x, offset:0x%x", addr, offset));
}
//---------------------------------------------------------------------------
void __fastcall TWOWFisherMain::btRegisterClick(TObject *Sender)
{
 	frmChargeFrm->ShowFrm();
}
//---------------------------------------------------------------------------

void __fastcall TWOWFisherMain::lvFishResultData(TObject *Sender, TListItem *Item)
{
	shared_ptr<DataObject> curObj = GetGameWorld()->GetDataByKey("fish_results")->GetAt(Item->Index);
	DWORD itemID = curObj->GetKeyName().ToIntDef(0);
	DWORD cnt = curObj->AsInt();
	Item->Caption = GetGameWorld()->GetItemNameByID(itemID);
	Item->SubItems->Add(cnt);
	Item->SubItems->Add(FormatStr("%s%%", curObj->GetDataObject("percent")->AsString()));
}
//---------------------------------------------------------------------------

void __fastcall TWOWFisherMain::lvFishFilterData(TObject *Sender, TListItem *Item)
{
	DWORD itemID = GetGameWorld()->GetItemPickupListAt(Item->Index);
	Item->Caption = GetGameWorld()->GetItemNameByID(itemID);
}
//---------------------------------------------------------------------------

void __fastcall TWOWFisherMain::RefreshTimerTimer(TObject *Sender)
{
	Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TWOWFisherMain::miNoAutoPickupClick(TObject *Sender)
{
	shared_ptr<DataObject> curObj = GetGameWorld()->GetDataByKey("fish_results")->GetAt(lvFishResult->ItemIndex);
	if(curObj.get() == NULL)
		return;

	DWORD itemID = curObj->GetKeyName().ToIntDef(0);
	GetGameWorld()->AddItemPickupList(itemID);
	this->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TWOWFisherMain::miDeleteFishFiterClick(TObject *Sender)
{
	GetGameWorld()->DeleteItemPickupList(lvFishFilter->ItemIndex);
	this->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TWOWFisherMain::miClearFishFilterClick(TObject *Sender)
{
	GetGameWorld()->ClearItemPickupList();
	this->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TWOWFisherMain::miCopyFishResultClick(TObject *Sender)
{
	auto_ptr<TStringList>	copyStr(new TStringList);
	String str = "-";
	String resultStr;
	for(int i=0; i<61; i++)
	{
		resultStr += str;
	}
	copyStr->Add(resultStr);
	for(int i=0; i<GetGameWorld()->GetDataByKey("fish_results")->GetChildCount(); i++)
	{
		shared_ptr<DataObject> curObj = GetGameWorld()->GetDataByKey("fish_results")->GetAt(i);
		DWORD itemID = curObj->GetKeyName().ToIntDef(0);
		AnsiString itemName = GetGameWorld()->GetItemNameByID(itemID);
		AnsiString cnt = curObj->AsString();
		AnsiString percent = FormatStr("%s%%", curObj->GetDataObject("percent")->AsString());
		AnsiString itemResult;
		itemResult.sprintf("*%-30s%-15s%-15s*", itemName.c_str(), cnt.c_str(), percent.c_str());
		copyStr->Add(itemResult);
	}
	copyStr->Add(resultStr);
	Clipboard()->AsText = copyStr->Text;
}
//---------------------------------------------------------------------------

void __fastcall TWOWFisherMain::btVisualCreatureClick(TObject *Sender)
{
	uint64 guid = GetGameWorld()->GetSelfGUID();
	if(guid == 0)
		return;

	#ifndef _DEBUG
	VM_START
	if(GetGameWorld()->GetFishAI()->GetIsStop())
	{
		ShowMessage(GBText("你的使用期限已过, 请续费!"));
		frmChargeFrm->ShowFrm();
		return;
	}
	VM_END
	#endif
	GetGameWorld()->GetPackSender()->SendVisible(guid, PLAYER_TRACK_CREATURES, 1);
	GetGameWorld()->GetPackSender()->SendVisible(guid, PLAYER_TRACK_RESOURCES, 0);
}
//---------------------------------------------------------------------------

void __fastcall TWOWFisherMain::btVisibleObjectClick(TObject *Sender)
{
	uint64 guid = GetGameWorld()->GetSelfGUID();
	if(guid == 0)
	{
		return;
	}
	#ifndef _DEBUG
	VM_START
	if(GetGameWorld()->GetFishAI()->GetIsStop())
	{
		ShowMessage(GBText("你的使用期限已过, 请续费!"));
		frmChargeFrm->ShowFrm();
		return;
	}
	VM_END
	#endif
	GetGameWorld()->GetPackSender()->SendVisible(guid, PLAYER_TRACK_CREATURES, 0);
	GetGameWorld()->GetPackSender()->SendVisible(guid, PLAYER_TRACK_RESOURCES, 1);
}
//---------------------------------------------------------------------------

void __fastcall TWOWFisherMain::labHomeADClick(TObject *Sender)
{
	#ifdef	_DEBUG
	String connName = "127.0.0.1";
	#else
	String connName = "www.wowggg.com";
	#endif
	ShellExecute(NULL,L"open",connName.c_str(),NULL, NULL, SW_MAXIMIZE);
}
//---------------------------------------------------------------------------

void __fastcall TWOWFisherMain::labTaoBaoBuyClick(TObject *Sender)
{
	ShellExecute(NULL,L"open",L"http://item.taobao.com/item.htm?id=5763290298",NULL, NULL, SW_MAXIMIZE);
}
//---------------------------------------------------------------------------

void __fastcall TWOWFisherMain::btChatClick(TObject *Sender)
{
	#ifdef _DEBUG
	FrmAutoChat->ShowFrm();
	#endif
}
//---------------------------------------------------------------------------

