//---------------------------------------------------------------------------

#include <vcl.h>
#include <Clipbrd.hpp>
#include <SysUtils.hpp>
#pragma hdrstop

#include "WOWPacketReviewer.h"
#include "CommentFrm.h"
#include "AuthLoader.h"
#include "CommFunc.h"
#include "Log4Me.h"
#include "CommPlus.h"
#include "ShareDef.h"
#include "gameworld.h"
#include "BlockWindowFrm.h"
#include "Opcodes.h"
#include "LOLPackageDispatcher.h"
#include "FiberContext.h"
#include "KOEItlbm.h"
#include "FiberCode.h"
#include "MapFrm.h"
#include "DBCStructureInfo.h"
#include "DataViewerFrm.h"
#include "SharedMemInfo.h"
#include "ValuesUpdateFrm.h"
#include "DrawMapFrm.h"
#include "DockFrm.h"
#include "FlyAI.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cspin"
#pragma link "ws2_32.lib"
#pragma link "Psapi.lib"
#pragma resource "*.dfm"
TWOWReviewerMainFrm *WOWReviewerMainFrm;

#define MAX_DEBUG_LINE_COUNT		100000

static String GetInputDataStr(String inputStr)
{
    TReplaceFlags   flag;
    flag << rfReplaceAll;
    String data = StringReplace(inputStr, "\r", " ", flag);
    data = StringReplace(data, "\n", " ", flag);
    data = StringReplace(data, "\"", "", flag);
	data = StringReplace(data, "   ", " ", flag);
	data = StringReplace(data, "  ", " ", flag);
    return  data;
}

struct tagInputPacketInfo
{
	int Head;
	AnsiString Packet;
	tagInputPacketInfo()
	{
		Head = 0;
	}
};

static void ParseInputPackToPacket(String markFilter, TStrings *input, vector<tagInputPacketInfo> *packet)
{
	bool readContent = false;
	String head;
	int opcode = 0;
	int mark = 0;
	String content;
	String markStr;
	int writeResult = 0;
	for(int i=1; i<input->Count; i++)
	{
		String curLine = input->Strings[i];
		if(!readContent)
		{
			if(curLine.Pos("DIR   :") != 0)
			{
				markStr = RightString(curLine, ":");
				markStr = markStr.Trim();
				if (markStr == "Snd" &&  markFilter == SEND_MARK)
				{
					writeResult = 1;
				}
				else if(markStr == "Rcv" &&  markFilter == RECV_MARK)
				{
					writeResult = 1;
				}
				else
				{
					writeResult = 0;
				}
			}
			if(curLine.Pos("OPCODE") == 0)
			{
				continue;
			}
			head = LeftString(curLine, "(");
			head = RightString(head, ":");
			head = head.Trim();
			opcode = LookupOpcodeID(head);
			if (opcode == 0)
			{
				continue;
			}
			readContent = true;
			i++;
		}
		else
		{
			if(curLine.Pos("\"") == 0)
			{
				if(writeResult)
				{
					tagInputPacketInfo info;
					info.Head = opcode;
					content = GetInputDataStr(content);
					info.Packet = HexStrToBinStr(content);
					packet->push_back(info);
				}
				readContent = false;
				writeResult = 0;
				content = "";
				continue;
			}
			else
			{
				content += curLine;
			}
		}
	}

	if(content != "" && writeResult)
	{
		tagInputPacketInfo info;
		info.Head = opcode;
		content = GetInputDataStr(content);
		info.Packet = HexStrToBinStr(content);
		packet->push_back(info);
	}
}

//---------------------------------------------------------------------------
__fastcall TWOWReviewerMainFrm::TWOWReviewerMainFrm(TComponent* Owner)
	: TForm(Owner)
{
	this->WindowProc = WndProcs;
}
//---------------------------------------------------------------------------
void __fastcall TWOWReviewerMainFrm::FormDestroy(TObject *Sender)
{
    GetLog()->Warn("TWOWReviewerMainFrm::FormDestroy");
	GetLog()->SetEnableLog(false);

    WOWHookViewInfo * curWOWHookViewInfo = GetSharedMemInfo()->FindSelf();
    if(curWOWHookViewInfo)
    {
        curWOWHookViewInfo->Clear();
    }

    for(int i=0; i<GetWOWProxyPool()->GetProxyCount(); i++)
    {
        GetWOWProxyPool()->GetProxy(i)->Close();
    }

    GetThreadManager()->FreeAll();
	delete m_ConnectIPList;
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::FormCreate(TObject *Sender)
{
	InitOpcode();
	m_ConnectIPList = new TStringList;
	if(!IsWin2k())
	{
		ShowMessage(GBText("你的操作系统版本过低, 需要win2000及以后的操作系统"));
		Application->Terminate();
		return;
	}
    pcMainControl->ActivePageIndex = 3;
	PageControl2->ActivePageIndex = 0;
	#ifndef WOW_FISHER
	GetSharedMemInfo()->CreateMapping();
	String filePath = ExtractFilePath(Application->ExeName) + "Log\\";
	GetLog()->SetEnableLog(true);
	GetLog()->SetPath(filePath);
	GetLog()->SetFileName(filePath + "WOWReviewer.log");
	GetLog()->Warn("Proc Init");
	GetLog()->Info("Current ThreadID = %d", GetCurrentThreadId());
	#endif

	SetUpdateFieldBuild(11723);
	InitTableColumns();

	for(int i=0; i<GetAllOpcodeNameList()->Count; i++)
	{
		cbPackHead->Items->Add(GetAllOpcodeNameList()->Strings[i]);
		cbAddFilter->Items->Add(GetAllOpcodeNameList()->Strings[i]);
	}

	GetLog()->SetGUIWindow(this->Handle);


//    GetEay32DllLoader()->Init();
	String iniName = ExtractFilePath(Application->ExeName)+"wowconfig.ini";
	if(!FileExists(iniName))
	{
        FileCreate(iniName);
	}
	m_MemIniFile = new  TMemIniFile(ExtractFilePath(Application->ExeName)+"wowconfig.ini");


	#ifndef WOW_FISHER
	int  listenPort = HOST_PORT;
	WOWHookViewInfo * view = GetSharedMemInfo()->CreateEmpty(listenPort);
	if(!view)
	{
		ShowMessage("FULL!");
		return;
	}
	listenPort = view->HostPortNumber;

	int baseaddr = m_MemIniFile->ReadString("SET", "BaseAddr", "").ToIntDef(0);
	int baseaddroffset = m_MemIniFile->ReadString("SET", "BaseAddrOffset", "").ToIntDef(0);
	int isHookHTTP = m_MemIniFile->ReadString("SET", "IsHookHTTP", "").ToIntDef(0);
	int WatchPort = m_MemIniFile->ReadString("SET", "WatchPort", "").ToIntDef(0);
	int OnlyHookTCP = m_MemIniFile->ReadString("SET", "OnlyHookTCP", "").ToIntDef(0);
	int ForceUseOneConnection = m_MemIniFile->ReadString("SET", "ForceUseOneConnection", "").ToIntDef(0);
	String ForceIP = m_MemIniFile->ReadString("SET", "ForceIP", "");
	int ForcePort = m_MemIniFile->ReadString("SET", "ForcePort", "").ToIntDef(0);
	int UDPToTCP = m_MemIniFile->ReadString("SET", "UDPToTCP", "").ToIntDef(0);
	GetWOWProxyManager()->SetUDPToTCP(UDPToTCP);
	GetWOWProxyManager()->SetForceDestIPAddr(ForceIP, ForcePort);
	GetSharedMemInfo()->FindSelf()->IsHookHTTP = isHookHTTP;
	GetSharedMemInfo()->FindSelf()->OnlyHookTCP = OnlyHookTCP;
	GetSharedMemInfo()->FindSelf()->WatchPort = WatchPort;
	GetSharedMemInfo()->FindSelf()->ForceUseOneConnection = ForceUseOneConnection;
	if (ForceUseOneConnection)
	{
		GetPackageContainerManager()->SetForceOneContainer(1);
	}
	if(baseaddr)
	{
		GetSharedMemInfo()->FindSelf()->BaseAddr = baseaddr;
		GetSharedMemInfo()->FindSelf()->BaseAddrOffset = baseaddroffset;
	}

	String dllName = GetGameWorld()->GetDllFileName();
	if(dllName == "")
	{
		dllName = ExtractFilePath(Application->ExeName) + "wowgo.dll";
	}
	GetGameWorld()->InjectDll(dllName, typeid(*this).name());

	GetWOWProxyManager()->Start(listenPort);

	GetThreadManager()->StartAll();


	GetGameWorld()->InitFiberProcesser();
	#endif

	String userDefineClassName = m_MemIniFile->ReadString("SET", "UserDefineClassName", "");
	String userDefineCaptionName = m_MemIniFile->ReadString("SET", "UserDefineCaptionName", "");
	SetTagFormClassName(userDefineClassName, userDefineCaptionName);

	GetGameWorld()->LoadGameData(m_MemIniFile->ReadString("SET", "DataPath", ""));
	GetPackageContainerManager()->GetWorldPackageContainer(cbWatchType->ItemIndex - 1)->LoadFilter();

	GetFiberManager()->Process();

	String ipList = m_MemIniFile->ReadString("SET", "iplist", "");
	SplitStr(ipList, ",", m_ConnectIPList);
	for(int i=0; i<m_ConnectIPList->Count; i++)
	{
		TMenuItem *item = new TMenuItem(pmStartMenu);
		item->Caption = m_ConnectIPList->Strings[i];
		item->OnClick = miStartMenuClick;
		pmStartMenu->Items->Add(item);
	}
	btSetServerMSTimeMutiClick(Sender);
}

void __fastcall TWOWReviewerMainFrm::miStartMenuClick(TObject *Sender)
{
	TMenuItem *item = (TMenuItem *)Sender;
	if(item->Checked)
	{
		GetWOWProxyManager()->SetForceRealmdIP("", 0);
		item->Checked = false;
		return;
	}

	for(int i=0; i<pmStartMenu->Items->Count; i++)
	{
		pmStartMenu->Items->Items[i]->Checked = false;
	}
	item->Checked = true;
	String connectIP = m_ConnectIPList->Strings[item->MenuIndex];
	auto_ptr<TStringList> splitStr(new TStringList);
	SplitStr(connectIP, ":", splitStr.get());
	if(splitStr->Count != 2)
	{
		ShowMessage("FormatError. ShouldBe  127.0.0.1:3724");
		return;
	}
	GetWOWProxyManager()->SetForceRealmdIP(splitStr->Strings[0], splitStr->Strings[1].ToIntDef(0));
	tbStartGameClick(Sender);
}
void TWOWReviewerMainFrm::AddMessageToPackage(String msg)
{
    PackageContainer * curPackageContainer = GetPackageContainerManager()->GetAuthPackageContainer();
    if(!curPackageContainer)
		return;
	auto_ptr<TStringList>   splitStr(new TStringList);
    SplitStr(msg, "|", splitStr.get());
	if(splitStr->Count != 4)
	{
		return;
	}
	// LogMsg(FormatStr("sendto|%s|%d|%s", ip, port, BinToStr((char FAR * )buf, len)), MSG_ADD_PACKAGE);

	WOWPackage fillPackage;
	fillPackage.SetProcessed(1);
	fillPackage.SetData(HexStrToBinStr(splitStr->Strings[3]));
	fillPackage.SetOpCodeMsg(FormatStr("%s:%s", splitStr->Strings[1], splitStr->Strings[2]));
	if (splitStr->Strings[0] == "sendto")
	{
		fillPackage.SetMark(SEND_MARK);
		curPackageContainer->OnGetSendWOWPack(&fillPackage);
	}
	else
	{
		fillPackage.SetMark(RECV_MARK);
		curPackageContainer->OnGetRecvWOWPack(&fillPackage);
	}
}
//---------------------------------------------------------------------------
void __fastcall TWOWReviewerMainFrm::WndProcs(Messages::TMessage &Message)
{
    if(Message.Msg == WM_COPYDATA)
    {
        COPYDATASTRUCT * sendData = (COPYDATASTRUCT *)Message.LParam;
		String msg = String((TCHAR *)sendData->lpData, sendData->cbData / sizeof(TCHAR));
		if(sendData->dwData == MSG_ADD_PACKAGE)
		{
			AddMessageToPackage(msg);
		}
		else
		{
			this->LogMsg(msg);
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
			else if(sendData->dwData == MSG_COMMANDLINE)
			{
				//LOL:得到了LOL的命令行, 开始获取base64数值
				//"F:/LOL_EN_GAME/League of Legends/RADS/solutions/lol_game_client_sln/releases/0.0.0.179/deploy/League of Legends.exe" "8394" "LoLLauncher.exe" "F:/LOL_EN_GAME/League of Legends/RADS/projects/lol_air_client/releases/0.0.0.193/deploy/LolClient.exe" "216.133.234.60 5211 SKkFXb9Hz8x/1+o5reAOyg== 29529788"
                auto_ptr<TStringList> split_strs(new TStringList);
				SplitStr(msg, " ", split_strs.get());
				if (split_strs->Count < 2)
				{
					return;
				}
				String lol_key_base64 = split_strs->Strings[split_strs->Count - 2];
				if (lol_key_base64 == "")
				{
					return;
				}
				GetLOLBlowFish()->Init(lol_key_base64);
				this->LogMsg(FormatStr("LOL Key = %s",lol_key_base64));
			}
		}
	}
	else if(Message.Msg == WM_MOVE)
	{
		if(frmDock->Showing)
		{
			frmDock->Left = this->Left + this->Width;
			frmDock->Top = this->Top;
		}
	}
    this->WndProc(Message);
}
//---------------------------------------------------------------------------
void	TWOWReviewerMainFrm::LogMsg(const String &Msg)
{
	if(memOutput->Lines->Count >= MAX_DEBUG_LINE_COUNT)
	{
        memOutput->Clear();
    }

    memOutput->Lines->Add(Msg);
}

//---------------------------------------------------------------------------
void TWOWReviewerMainFrm::RestoreWindow()
{
   Application->Restore();
   ShowWindow(Application->Handle, SW_RESTORE);
   SetForegroundWindow(Application->Handle);
}
//---------------------------------------------------------------------------
void TWOWReviewerMainFrm::MinimizeWindow()
{
	Application->Minimize();
	ShowWindow(Application->Handle, SW_HIDE);
}
//---------------------------------------------------------------------------

PackageContainer        *   TWOWReviewerMainFrm::GetWatchProxy()
{
    if(cbWatchType->ItemIndex == 0)
    {
        return      GetPackageContainerManager()->GetAuthPackageContainer();
    }
    else
    {
        return      GetPackageContainerManager()->GetWorldPackageContainer(cbWatchType->ItemIndex - 1);
    }
}

void            TWOWReviewerMainFrm::Refresh(int forceRefresh)
{
    if(forceRefresh == 0 && cbNoRefresh->Checked)
        return;

	edtTick->Text = FormatStr("%d, %f", GetWowTick(), GetNowTick());
    PackageContainer * curPackageContainer = GetWatchProxy();
    if(curPackageContainer)
    {
        curPackageContainer->RefreshFilter();
        int cnt = curPackageContainer->GetFilterRecv()->Count();
//        lvRecv->Items->Count = cnt;
        ListView_SetItemCountEx(lvRecv->Handle, cnt, LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
        lvRecv->Refresh();

        cnt = curPackageContainer->GetFilterSend()->Count();
//        lvSend->Items->Count = cnt;
        ListView_SetItemCountEx(lvSend->Handle, cnt, LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
        lvSend->Refresh();

        cnt = curPackageContainer->GetFilterAll()->Count();
//        lvAll->Items->Count = cnt;
        ListView_SetItemCountEx(lvAll->Handle, cnt, LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
        lvAll->Refresh();


        cnt = curPackageContainer->GetFilterOpcode()->Count();
        ListView_SetItemCountEx(lvPackFilter->Handle, cnt, LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
        lvPackFilter->Refresh();
    }

    ListView_SetItemCountEx(lvMemView->Handle, GetSharedMemInfo()->GetCount(), LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
	lvMemView->Refresh();


   	ListView_SetItemCountEx(lvThread->Handle, GetThreadManager()->Count(), LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
	lvThread->Refresh();
}


void __fastcall TWOWReviewerMainFrm::Timer1Timer(TObject *Sender)
{
	if(!GetSharedMemInfo()->GetInitOK())
		return;
    Refresh(0);
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::lvSendData(TObject *Sender,
      TListItem *Item)
{
    PackageContainer * curPackageContainer = GetWatchProxy();
    if(!curPackageContainer)
        return;
    WOWPackage * curPack = curPackageContainer->GetFilterSend()->At(Item->Index);
    if(!curPack)
    {
        return;
	}

	AnsiString curData;
	if (cbShowOrgPack->Checked)
	{
		curData = curPack->GetOrgData();
	}
	else
	{
		curData = curPack->GetData();
	}
    Item->Caption = IntToStr(curPack->GetIndex());
    Item->SubItems->Add(curPack->GetTime());
    Item->SubItems->Add(curData.Length());
    Item->SubItems->Add(curPack->GetOpCodeMsg());
    if(cbWatchType->ItemIndex == 0)
    {
        Item->SubItems->Add(BinToStr(curData.c_str(), curData.Length()));
    }
    else
    {
        Item->SubItems->Add(BinToStr(curData.c_str()+GetShowHeadSize(curPack), curData.Length()-GetShowHeadSize(curPack)));
    }
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::lvRecvData(TObject *Sender,
      TListItem *Item)
{
    PackageContainer * curPackageContainer = GetWatchProxy();
    if(!curPackageContainer)
        return;
    WOWPackage * curPack = curPackageContainer->GetFilterRecv()->At(Item->Index);
    if(!curPack)
    {
        return;
    }

	AnsiString curData;
	if (cbShowOrgPack->Checked)
	{
		curData = curPack->GetOrgData();
	}
	else
	{
		curData = curPack->GetData();
	}
    Item->Caption = IntToStr(curPack->GetIndex());
    Item->SubItems->Add(curPack->GetTime());
    Item->SubItems->Add(curData.Length());
    Item->SubItems->Add(curPack->GetOpCodeMsg());

    if(cbWatchType->ItemIndex == 0)
    {
        Item->SubItems->Add(BinToStr(curData.c_str(), curData.Length()));
    }
    else
    {
        Item->SubItems->Add(BinToStr(curData.c_str()+GetShowHeadSize(curPack), curData.Length()-GetShowHeadSize(curPack)));
    }
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::lvAllData(TObject *Sender, TListItem *Item)
{
    PackageContainer * curPackageContainer = GetWatchProxy();
    if(!curPackageContainer)
        return;
    WOWPackage * curPack = curPackageContainer->GetFilterAll()->At(Item->Index);
    if(!curPack)
    {
        return;
    }

	AnsiString curData;
	if (cbShowOrgPack->Checked)
	{
		curData = curPack->GetOrgData();
	}
	else
	{
		curData = curPack->GetData();
	}
	Item->Caption = IntToStr(curPack->GetIndex());
	Item->SubItems->Add(curPack->GetTime());
	Item->SubItems->Add(curPack->GetMark());
	Item->SubItems->Add(curData.Length());
	Item->SubItems->Add(curPack->GetOpCodeMsg());
	if(cbWatchType->ItemIndex == 0)
	{
		Item->SubItems->Add(BinToStr(curData.c_str(), curData.Length()));
    }
    else
    {
        Item->SubItems->Add(BinToStr(curData.c_str()+GetShowHeadSize(curPack), curData.Length()-GetShowHeadSize(curPack)));
    }
}
//---------------------------------------------------------------------------
bool TWOWReviewerMainFrm::GetVisibleListView(TListView **lv, AList<WOWPackage> **listData)
{
	WY_ASSERT(lv)
	WY_ASSERT(listData)
    PackageContainer * curPackageContainer = GetWatchProxy();
    if(!curPackageContainer)
		return false;
	if(pcMainControl->ActivePageIndex == tsSend->PageIndex)
	{
		*lv = lvSend;
		*listData = curPackageContainer->GetFilterSend();
		return true;
	}
	else if(pcMainControl->ActivePageIndex == tsRecv->PageIndex)
	{
		*lv = lvRecv;
		*listData = curPackageContainer->GetFilterRecv();
		return true;
	}
	else if(pcMainControl->ActivePageIndex == tsAll->PageIndex)
	{
		*lv = lvAll;
		*listData = curPackageContainer->GetFilterAll();
		return true;
	}
	return false;
}




void __fastcall TWOWReviewerMainFrm::cbWatchTypeSelect(TObject *Sender)
{
    this->Refresh(1);
    if(cbWatchType->ItemIndex > 0)
    {
        frmBlock->SetWatchConnectionIndex(cbWatchType->ItemIndex-1);
    }
}
//---------------------------------------------------------------------------


void __fastcall TWOWReviewerMainFrm::TimeLogicTimer(TObject *Sender)
{
    if(GetGameWorld()->GetInputSessionKey())
		return;

	if(!GetSharedMemInfo()->GetInitOK())
		return;

	GetGameWorld()->RefreshSystemInitAddr();

	GetPackageContainerManager()->PopQueue(GetWOWProxyManager()->GetAllQueue());

    GetPackageContainerManager()->ProcessClientMessage();

	GetFiberManager()->Process();
    if (cbNoRefresh->Checked && GetPackageContainerManager()->GetAllPackage()->Count() > 100000)
    {
        GetPackageContainerManager()->ClearAllPackage();
    }
}
//---------------------------------------------------------------------------

AnsiString          TWOWReviewerMainFrm::GetInputData()
{
	String data = GetInputDataStr(edtSendPack->Lines->Text);
	edtSendPack->Lines->Text = data;
    return  HexStrToBinStr(data);
}
//---------------------------------------------------------------------------

void            TWOWReviewerMainFrm::GetSendPack(WOWPackage  *   pack, String mark)
{
	cbPackHead->Text = cbPackHead->Text.Trim();
	GetPackageFromDataPack(pack, cbPackHead->Text, mark, GetInputData());
	SetLogicPackIndex(GetLogicPackIndex() + 1);
}

void __fastcall TWOWReviewerMainFrm::btSendToClientClick(TObject *Sender)
{
    PackageContainer * worldPackageContainer = GetPackageContainerManager()->GetWorldPackageContainer(cbWatchType->ItemIndex - 1);
    if(!worldPackageContainer)
		return;
	vector<tagInputPacketInfo> parseResult;
	ParseInputPackToPacket(RECV_MARK, edtSendPack->Lines, &parseResult);
	if(parseResult.size())
	{
		labSendMsg->Caption = FormatStr("Send To Client Pack Count = %d", parseResult.size());
		tagInputPacketInfo *info = NULL;
		for(uint32 i=0; i<parseResult.size(); i++)
		{
			info = &parseResult[i];
			GetGameWorld()->GetPackSender()->ForceSendPacket(RECV_MARK, info->Head, info->Packet, cbWatchType->ItemIndex - 1);
		}
		return;
	}

	int head = LookupOpcodeID(cbPackHead->Text);
	if(!head)
	{
		ShowMessage("Head == 0");
	}

    GetGameWorld()->GetPackSender()->ForceSendPacket(RECV_MARK, head, GetInputData(), cbWatchType->ItemIndex - 1);

}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::btSendToServerClick(TObject *Sender)
{
    PackageContainer * worldPackageContainer = GetPackageContainerManager()->GetWorldPackageContainer(cbWatchType->ItemIndex - 1);
    if(!worldPackageContainer)
        return;

	vector<tagInputPacketInfo> parseResult;
	ParseInputPackToPacket(SEND_MARK, edtSendPack->Lines, &parseResult);
	if(parseResult.size())
	{
		labSendMsg->Caption = FormatStr("Send To Server Pack Count = %d", parseResult.size());
		tagInputPacketInfo *info = NULL;
		for(uint32 i=0; i<parseResult.size(); i++)
		{
			info = &parseResult[i];
			GetGameWorld()->GetPackSender()->ForceSendPacket(SEND_MARK, info->Head, info->Packet, cbWatchType->ItemIndex - 1);
		}
		return;
	}

	int head = LookupOpcodeID(cbPackHead->Text);
	if(!head)
	{
		ShowMessage("Head == 0");
	}
    GetGameWorld()->GetPackSender()->ForceSendPacket(SEND_MARK, head, GetInputData(), cbWatchType->ItemIndex - 1);
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::cbShowHeadClick(TObject *Sender)
{
    this->Refresh(1);    
}
//---------------------------------------------------------------------------




void __fastcall TWOWReviewerMainFrm::lvAllClick(TObject *Sender)
{
	TListView *lv = NULL;
	AList<WOWPackage> *listData = NULL;
	if(!GetVisibleListView(&lv, &listData))
	{
		return;
	}
	SetCommentText(GetListViewCommentText(lv, listData));
}
//---------------------------------------------------------------------------


void            TWOWReviewerMainFrm::AddParseStr(String mark)
{
    WOWPackage   curPack;
	GetSendPack(&curPack, mark);
	GetGameWorld()->HandlerPacket(&curPack);
    curPack.GetInfo(GIT_DETAIL, !WOWReviewerMainFrm->cbShowHead->Checked, WOWReviewerMainFrm->cbShowOrgPack->Checked, memComment->Lines);
    SetCommentText(curPack.GetComment()->Text);
}
//---------------------------------------------------------------------------
void __fastcall TWOWReviewerMainFrm::btParseRecvClick(TObject *Sender)
{
    AddParseStr(RECV_MARK);
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::btParseSendClick(TObject *Sender)
{
    AddParseStr(SEND_MARK);
}
//---------------------------------------------------------------------------
void __fastcall TWOWReviewerMainFrm::cbHandlerPacketClick(TObject *Sender)
{
    GetGameWorld()->SetEnableHandlerPacket(cbHandlerPacket->Checked);
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::miCommentCopyAllClick(TObject *Sender)
{
    Clipboard()->AsText = memComment->Text;    
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::miCommentWatchClick(TObject *Sender)
{
    FrmComment->Show();
    FrmComment->SetShowText(memComment->Lines);
}
//---------------------------------------------------------------------------
void                        TWOWReviewerMainFrm::SetCommentText(String text)
{
    memComment->Text = text;
    if(FrmComment->Showing)
    {
        FrmComment->SetShowText(memComment->Lines);
    }
}
void __fastcall TWOWReviewerMainFrm::btTimeBitToStringClick(TObject *Sender)
{
    edtTimeBitString->Text = TimeBitToString(edtInputTimeBit->Text.ToIntDef(0));    
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::btUTF8ToAnsiClick(TObject *Sender)
{
    AnsiString result = HexStrToBinStr(edtUTF8BIN->Text);
    edtUTF8Output->Text = tlbm_StrUTF8ToAnsi(result);
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::btFloatToTimeClick(TObject *Sender)
{
    long value = edtFloatToTime->Text.ToIntDef(0);
    edtFloatToTimeResult->Text = ctime(&value);    
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::cbShowOrgPackClick(TObject *Sender)
{
	GetGameWorld()->SetEnableShowOrgPacket(cbShowOrgPack->Checked);
	this->Refresh(1);
}
//---------------------------------------------------------------------------


void __fastcall TWOWReviewerMainFrm::edtSendPackDblClick(TObject *Sender)
{
    edtSendPack->SelectAll();
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::lvPackFilterData(TObject *Sender,
      TListItem *Item)
{
    PackageContainer * curPackageContainer = GetWatchProxy();
    if(!curPackageContainer)
        return;
    FilterType * curFilterType = curPackageContainer->GetFilterOpcode()->At(Item->Index);
    if(!curFilterType)
        return;

	Item->Caption = LookupOpcodeName(curFilterType->Opcode);
	Item->SubItems->Add(curFilterType->Guid);
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::cbFilterClick(TObject *Sender)
{
	PackageContainer * curPackageContainer = GetWatchProxy();
	if(!curPackageContainer)
		return;

    curPackageContainer->SetEnableFilter(cbFilter->Checked);
	curPackageContainer->SetReverseFilter(cbReverseFilter->Checked);
	curPackageContainer->SetCreatureFilter(cbFilterAllCreature->Checked);
    this->Refresh(1);
}
//---------------------------------------------------------------------------


void __fastcall TWOWReviewerMainFrm::btAddFilterClick(TObject *Sender)
{
    PackageContainer * curPackageContainer = GetWatchProxy();
    if(!curPackageContainer)
        return;

	int head = 0;
	try
	{
		head = StrToInt("$"+cbAddFilter->Text);
	}
	catch (Exception &e)
	{
		head = LookupOpcodeID(cbAddFilter->Text);
	}

	uint64 guid = StrToUint64Def(edtFilterGuid->Text, 0);


	curPackageContainer->AddFilterOpcode(head, guid);
    this->Refresh(1);
}
//---------------------------------------------------------------------------

void            TWOWReviewerMainFrm::AddViewSelectTextToFilter(TListView * lv, AList<WOWPackage> * listData)
{
    PackageContainer * curPackageContainer = GetWatchProxy();
    if(!curPackageContainer)
        return;
    auto_ptr<TStringList>   copyStr(new TStringList);
    for(int i=0; i<lv->Items->Count; i++)
    {
        if(lv->Items->Item[i]->Selected)
        {
            WOWPackage  * curPack = listData->At(i);
            if(!curPack)
                continue;

            curPackageContainer->AddFilterOpcode(curPack->GetOpCode(), _wtoi(edtFilterGuid->Text.c_str()));
        }
    }

    this->Refresh(1);
}

void __fastcall TWOWReviewerMainFrm::miAllAddToFilterClick(TObject *Sender)
{
	TListView *lv = NULL;
	AList<WOWPackage> *listData = NULL;
	if(!GetVisibleListView(&lv, &listData))
	{
		return;
	}
    AddViewSelectTextToFilter(lv, listData);
}
//---------------------------------------------------------------------------



void __fastcall TWOWReviewerMainFrm::btClearFilterClick(TObject *Sender)
{
    PackageContainer * curPackageContainer = GetWatchProxy();
    if(!curPackageContainer)
        return;

	curPackageContainer->GetFilterOpcode()->Clear();
	curPackageContainer->SaveFilter();
    this->Refresh(1);
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::miDeleteFilterClick(TObject *Sender)
{
    PackageContainer * curPackageContainer = GetWatchProxy();
    if(!curPackageContainer)
        return;
	curPackageContainer->GetFilterOpcode()->Delete(lvPackFilter->ItemIndex);
	curPackageContainer->SaveFilter();
    this->Refresh(1);
}
//---------------------------------------------------------------------------


void __fastcall TWOWReviewerMainFrm::btShowMapsClick(TObject *Sender)
{
    FrmMap->ShowMap();
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::btDataViewerClick(TObject *Sender)
{
    FrmDBCViewer->ShowInitFrm();
}
//---------------------------------------------------------------------------

void TWOWReviewerMainFrm::WriteServerMSTime(int type, String titleName, TStrings *output)
{
    // 这个功能已经被2011.03.05日更改.
    // 原因: 多gate机制?
    return;
	vector<tagServerMSTimeMutiParam> *serverMSTimeMutiParam = GetGameWorld()->GetServerMSTimeMutiParam(type);
	if(serverMSTimeMutiParam->size() == 0)
	{
		return;
	}
	tagServerMSTimeMutiParam *currentData = &(*serverMSTimeMutiParam)[serverMSTimeMutiParam->size() - 1];
	double serverMSTime = double(currentData->ServerMSTime) * m_ServerMSTimeMuti;
	if (serverMSTimeMutiParam->size() >= 2)
	{
		int startIndex = serverMSTimeMutiParam->size() - 2;
		int endIndex = serverMSTimeMutiParam->size() - 1;
		// x = (Now2 - Now1) * (1000*3600*24) / (S2 - S1)
		if (serverMSTimeMutiParam->at(endIndex).ServerMSTime != serverMSTimeMutiParam->at(startIndex).ServerMSTime)
		{
			m_ServerMSTimeMutiSuggest[type] = ((double)(serverMSTimeMutiParam->at(endIndex).NowTick) - (double)(serverMSTimeMutiParam->at(startIndex).NowTick)) /
											(serverMSTimeMutiParam->at(endIndex).ServerMSTime - serverMSTimeMutiParam->at(startIndex).ServerMSTime);
		}
	}
	TDateTime suggestValue = 0;
	if (serverMSTimeMutiParam->size() != 0)
	{
		suggestValue = currentData->NowTime - currentData->ServerMSTime * m_ServerMSTimeMutiSuggest[type] / (1000*3600*24);
	}
	double serverStartTime = (double)currentData->NowTime - double(serverMSTime) / (1000*3600*24);
    String startTimeStr = "";
    if (serverStartTime >= 0)
    {
        try
        {
            startTimeStr = DateTimeToStr(serverStartTime);
        }
        catch(Exception &e)
        {
            startTimeStr = "unknown error";
        }
    }
    else
    {
        startTimeStr = "error";
    }
	output->Add(titleName);
	output->Add(FormatStr("ServerMSTime:[%f]. UpTimeHour:[%0.2f]. StartTime:[%s]. Mutifiler:[%f]. MoveNpc:[%s]. size[%d]",
			currentData->ServerMSTime, float(serverMSTime) / 3600000,
			startTimeStr,
			m_ServerMSTimeMuti,
			currentData->MoveNPCName,
			serverMSTimeMutiParam->size()));
	output->Add(FormatStr("SuggestMuti:[%f], SuggestTime:[%s]. ", m_ServerMSTimeMutiSuggest[type], DateTimeToStr(suggestValue)));
}

void __fastcall TWOWReviewerMainFrm::TimeInfoTimer(TObject *Sender)
{
	memPosInfo->Lines->Clear();
	memPosInfo->Lines->Add(FormatStr("Total Recv: %.2fkb", float(GetWOWProxyManager()->GetTotalRecvBytes()) / 1024));
	memPosInfo->Lines->Add(FormatStr("Total Send: %.2fkb", float(GetWOWProxyManager()->GetTotalSendBytes()) / 1024));
    float x,y,z;
    x = GetGameWorld()->GetDataFloat("self/posx");
    y = GetGameWorld()->GetDataFloat("self/posy");
    memPosInfo->Lines->Add(FormatStr("GUID  :[low %s, high %s]", GetGameWorld()->GetDataStr("self/guidl"),
											GetGameWorld()->GetDataStr("self/guidh")));
    memPosInfo->Lines->Add(FormatStr("mapid :%s", GetGameWorld()->GetDataStr("mapid")));
    memPosInfo->Lines->Add(FormatStr("zoneid:%s", GetGameWorld()->GetDataStr("zoneid")));
	memPosInfo->Lines->Add(FormatStr("areaid:%s", GetGameWorld()->GetDataStr("areaid")));
	memPosInfo->Lines->Add(FormatStr("NumberOfFields:%s", GetGameWorld()->GetDataStr("NumberOfFields")));
	memPosInfo->Lines->Add(FormatStr("pos   :[%s, %s, %s, %s]", GetGameWorld()->GetDataStr("self/posx"),
												GetGameWorld()->GetDataStr("self/posy"),
												GetGameWorld()->GetDataStr("self/posz"),
												GetGameWorld()->GetDataStr("self/poso")));
	memPosInfo->Lines->Add(FormatStr("speed :[%s", GetGameWorld()->GetDataStr("self/speed")));
	memPosInfo->Lines->Add(FormatStr("grid  :[%d, %d]", GetGameWorld()->GetGameMapManager()->PosToGrix(x),
												GetGameWorld()->GetGameMapManager()->PosToGrix(y)));
	memPosInfo->Lines->Add(FormatStr("ItemFieldEnchantmentValue1:%d", GetGameWorld()->GetItemFieldEnchantmentValue1()));

	memMSTimeInfo->Lines->BeginUpdate();
	memMSTimeInfo->Lines->Clear();
	for(int i=0; i<STM_MAX_MS_TIME_TYPE;i++)
	{
		WriteServerMSTime(i, GetServerMSTimeMutiParamTypeName(i), memMSTimeInfo->Lines);
	}
	memMSTimeInfo->Lines->EndUpdate();

	this->Caption = FormatStr("Eggxp - %s guidl:%s", GetGameWorld()->GetDataStr("self/name"), GetGameWorld()->GetDataStr("self/guidl"));

	labCnt->Caption = FormatStr("Thread Cnt:%d. Proxy Cnt:%d", GetThreadManager()->Count(), GetWOWProxyManager()->GetWOWProxyCount());

	String selectGuid = GetGameWorld()->GetDataStr("self/selection");
	memThreat->Text = GetGameWorld()->GetDataStr(FormatStr("threat/%s", selectGuid));
	labProxyCount->Caption = FormatStr("ProxyCount: %d", GetWOWProxyManager()->GetWOWProxyCount());

    int maxWatchItemCount = GetPackageContainerManager()->GetWorldPackageContainerCount() + 1;
    if(cbWatchType->Items->Count < maxWatchItemCount)
    {
        for(int i=cbWatchType->Items->Count; i<maxWatchItemCount; i++)
        {
            cbWatchType->Items->Add(FormatStr("Word%d", i));
        }
    }
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::lvMemViewData(TObject *Sender,
      TListItem *Item)
{
    WOWHookViewInfo * curItem = GetSharedMemInfo()->GetAt(Item->Index);
    Item->Caption = curItem->HostProcessID;
    Item->SubItems->Add(curItem->DestProcessID);
	Item->SubItems->Add(curItem->HostPortNumber);
	Item->SubItems->Add(curItem->WatchPort);
	Item->SubItems->Add(FormatStr("0x%x", curItem->BaseAddr));
	Item->SubItems->Add(FormatStr("0x%x", curItem->BaseAddrOffset));
	Item->SubItems->Add(curItem->MainWindowClassName);
    Item->SubItems->Add(curItem->ForbiddenAnyMortConnection);
	Item->SubItems->Add(curItem->ClientConnectIndex);
}

void __fastcall TWOWReviewerMainFrm::btStartAIClick(TObject *Sender)
{
    FrmGameDataViewer->ShowFrm();
}
//---------------------------------------------------------------------------


void __fastcall TWOWReviewerMainFrm::btOrgToUTF8Click(TObject *Sender)
{
	AnsiString result = edtUTF8BIN->Text;
	edtUTF8Output->Text = tlbm_StrUTF8ToAnsi(result);
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::btAnsiToUTF8BinClick(TObject *Sender)
{
	String ansi = edtAnsiStr->Text;
	vector<char> output;
	int len = UnicodeToUtf8(NULL, 0, ansi.c_str(), ansi.Length());
	output.resize(len+1);
	len = UnicodeToUtf8(&output[0], output.size(), ansi.c_str(), ansi.Length());
	edtAnsiToUTF8Bin->Text = BinToStr(&output[0], len);
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::lvThreadData(TObject *Sender, TListItem *Item)
{
	WYThread * curWYThread = GetThreadManager()->At(Item->Index);
	if(!curWYThread)
		return;

	Item->Caption = curWYThread->ThreadID;
	Item->SubItems->Add(curWYThread->GetName());
	Item->SubItems->Add(curWYThread->GetStateName());
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::btUpdateObjectClick(TObject *Sender)
{
	FrmValuesUpdate->Show();
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::btMapDrawerClick(TObject *Sender)
{
	FrmDrawMap->ShowFrm();
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::tmCloseFreeRefreshTimer(TObject *Sender)
{
    GetWOWProxyManager()->ProcessRemoveProxyList();
	GetThreadManager()->ProcessDeletedThread();

	GetGameWorld()->CheckWOWClosedRefresh();

    if(GetWOWProxyManager()->GetIsFirstStartWorking())
    {
        GetGameWorld()->Clear();
        GetWOWProxyManager()->SetIsFirstStartWorking(0);
        GetGameWorld()->DeleteData("world");
        GetGameWorld()->DeleteData("self");
    }
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::tbClearAllClick(TObject *Sender)
{
	TimeLogicTimer(Sender);
    GetPackageContainerManager()->ClearAllPackage();
    Refresh(1);
    memOutput->Lines->Clear();
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::tbBlockClick(TObject *Sender)
{
    GetGameWorld()->SetBlockMode(1);
    frmBlock->Show();
    if(cbWatchType->ItemIndex > 0)
    {
        frmBlock->SetWatchConnectionIndex(cbWatchType->ItemIndex-1);
    }
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::tbStartGameClick(TObject *Sender)
{
    if(GetSharedMemInfo()->FindSelf()->DestProcessID != 0)
    {
        return;
    }

	String wowPath = m_MemIniFile->ReadString("SET", "WOWPath", "");
	if(!FileExists(wowPath))
	{
		ShowMessage(FormatStr("Path Not Exist!(%s)", wowPath));
        return;
	}

	String tmpPath = ExtractFilePath(wowPath) + "Cache\\*";

	if(DirectoryExists(tmpPath))
	{
		if(!ForceRemoveDir(tmpPath))
		{
			ShowMessage(SysErrorMessage(GetLastError()));
		}
	}
    ShellExecute(NULL, _TEXT("open"), wowPath.c_str(), NULL, NULL, SW_SHOW);
	pcMainControl->ActivePageIndex = 2;
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::btDockClick(TObject *Sender)
{
	if(!GetGameWorld()->GetWOWWindowHandle())
	{
		return;
	}
	::SetParent(GetGameWorld()->GetWOWWindowHandle(), frmDock->Handle);
	frmDock->Left = this->Left + this->Width;
	frmDock->Top = this->Top;
	frmDock->Height = this->Height;
	frmDock->Width = frmDock->Height;
	frmDock->Show();
}
//---------------------------------------------------------------------------


void __fastcall TWOWReviewerMainFrm::btSetServerMSTimeMutiClick(TObject *Sender)
{
	try
	{
		m_ServerMSTimeMuti = edtServerMSTimeMuti->Text.ToDouble();
	}
	catch(Exception &e)
	{
		ShowMessage(FormatStr("设置错误: %s", e.Message));
	}
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::btCreatureFindClick(TObject *Sender)
{
	uint64 guid = GetGameWorld()->GetSelfGUID();
	if(guid == 0)
		return;
	GetGameWorld()->GetPackSender()->SendVisible(guid, PLAYER_TRACK_CREATURES, 1);
	GetGameWorld()->GetPackSender()->SendVisible(guid, PLAYER_TRACK_RESOURCES, 0);
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::btGameObjectFindClick(TObject *Sender)
{
	uint64 guid = GetGameWorld()->GetSelfGUID();
	if(guid == 0)
		return;
	GetGameWorld()->GetPackSender()->SendVisible(guid, PLAYER_TRACK_CREATURES, 0);
	GetGameWorld()->GetPackSender()->SendVisible(guid, PLAYER_TRACK_RESOURCES, 1);
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::btReloadResourceClick(TObject *Sender)
{
	GetGameWorld()->LoadFishData();
	GetGameWorld()->LoadPackForbiddenList();
}
//---------------------------------------------------------------------------


void __fastcall TWOWReviewerMainFrm::btFlySetClick(TObject *Sender)
{
	GetGameWorld()->GetFlyAI()->Awake(FWC_WAIT_FLY_AI_START);
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::btIncSpeedClick(TObject *Sender)
{
	GetGameWorld()->GetSpeedChangeAI()->SetActiveSetting(!GetGameWorld()->GetSpeedChangeAI()->GetActiveSetting());
	GetGameWorld()->GetSpeedChangeAI()->Awake(FWC_WAIT_RUN_SPEED_CHANGE_AI_START);
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::btDisconnectClick(TObject *Sender)
{
	GetWOWProxyManager()->ResetConnections();
    GetSharedMemInfo()->FindSelf()->ClientConnectIndex = -10;
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::btDirectModelClick(TObject *Sender)
{
	GetLog()->Warn("------------------------------------------SetDirectModel");
	GetWOWProxyManager()->SetDirectModel(!GetWOWProxyManager()->GetDirectModel());
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::edtFloatCalcChange(TObject *Sender)
{
	float result = 0.0f;
	try{
		result = edtFloatCalc->Text.ToDouble();
	}
	catch(Exception &e)
	{
		result = 0.0f;
	}
	char *lpdata = (char *)&result;
	int len = sizeof(result);
	edtFloatCalcResult->Text = BinToStr(lpdata, len);
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::CopyDetail1Click(TObject *Sender)
{
	TListView *lv = NULL;
	AList<WOWPackage> *listData = NULL;
	if(!GetVisibleListView(&lv, &listData))
	{
		return;
	}
	CopyListViewSelectText(lv, listData, GIT_DETAIL);
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::CopyLine1Click(TObject *Sender)
{
	TListView *lv = NULL;
	AList<WOWPackage> *listData = NULL;
	if(!GetVisibleListView(&lv, &listData))
	{
		return;
	}
	CopyListViewSelectText(lv, listData, GIT_LINE);
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::CopyCVS1Click(TObject *Sender)
{
	TListView *lv = NULL;
	AList<WOWPackage> *listData = NULL;
	if(!GetVisibleListView(&lv, &listData))
	{
		return;
	}
	CopyListViewSelectText(lv, listData, GIT_CVS);
}
//---------------------------------------------------------------------------



void __fastcall TWOWReviewerMainFrm::btWaterwalkingClick(TObject *Sender)
{
	GetGameWorld()->GetWaterWalkingAI()->Awake(FWC_WAIT_WATER_WALKING_AI_START);
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::Button1Click(TObject *Sender)
{
//    WorldPackageDispatcher d;
//    d.DigestRecvPacket();
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::miCopyToFileClick(TObject *Sender)
{
	TListView *lv = NULL;
	AList<WOWPackage> *listData = NULL;
	if(!GetVisibleListView(&lv, &listData))
	{
		return;
	}
	CopyListViewSelectText(lv, listData, GIT_FILE);
}
//---------------------------------------------------------------------------

void SaveCell(String fileDir, map<String, String> &cellData)
{
	DWORD id = cellData["id"].ToIntDef(0);
	auto_ptr<TStringList> saveCell(new TStringList);
	saveCell->Add("//!ITEM_SEPARATOR");

	saveCell->Add(FormatStr("id: %s", cellData["id"]));
	saveCell->Add(FormatStr("category: %s", cellData["category"]));
	saveCell->Add(FormatStr("dispel: %s", cellData["dispel"]));
	saveCell->Add(FormatStr("mechanic: %s", cellData["mechanic"]));
	saveCell->Add(FormatStr("attributes: %s", cellData["attributes"]));
	saveCell->Add(FormatStr("attributesex: %s", cellData["attributesex"]));
	saveCell->Add(FormatStr("attributesex2: %s", cellData["attributesex2"]));
	saveCell->Add(FormatStr("attributesex3: %s", cellData["attributesex3"]));
	saveCell->Add(FormatStr("attributesex4: %s", cellData["attributesex4"]));
	saveCell->Add(FormatStr("attributesex5: %s", cellData["attributesex5"]));
	saveCell->Add(FormatStr("attributesex6: %s", cellData["attributesex6"]));
	saveCell->Add(FormatStr("stances: %s", cellData["stances"]));
	saveCell->Add(FormatStr("stancesnot: %s", cellData["stancesnot"]));
	saveCell->Add(FormatStr("targets: %s", cellData["targets"]));
	saveCell->Add(FormatStr("targetcreaturetype: %s", cellData["targetcreaturetype"]));
	saveCell->Add(FormatStr("requiresspellfocus: %s", cellData["requiresspellfocus"]));
	saveCell->Add(FormatStr("facingcasterflags: %s", cellData["facingcasterflags"]));
	saveCell->Add(FormatStr("casteraurastate: %s", cellData["casteraurastate"]));
	saveCell->Add(FormatStr("targetaurastate: %s", cellData["targetaurastate"]));
	saveCell->Add(FormatStr("casteraurastatenot: %s", cellData["casteraurastatenot"]));
	saveCell->Add(FormatStr("targetaurastatenot: %s", cellData["targetaurastatenot"]));
	saveCell->Add(FormatStr("casterauraspell: %s", cellData["casterauraspell"]));
	saveCell->Add(FormatStr("targetauraspell: %s", cellData["targetauraspell"]));
	saveCell->Add(FormatStr("excludecasterauraspell: %s", cellData["excludecasterauraspell"]));
	saveCell->Add(FormatStr("excludetargetauraspell: %s", cellData["excludetargetauraspell"]));
	saveCell->Add(FormatStr("castingtimeindex: %s", cellData["castingtimeindex"]));
	saveCell->Add(FormatStr("recoverytime: %s", cellData["recoverytime"]));
	saveCell->Add(FormatStr("categoryrecoverytime: %s", cellData["categoryrecoverytime"]));
	saveCell->Add(FormatStr("interruptflags: %s", cellData["interruptflags"]));
	saveCell->Add(FormatStr("aurainterruptflags: %s", cellData["aurainterruptflags"]));
	saveCell->Add(FormatStr("channelinterruptflags: %s", cellData["channelinterruptflags"]));
	saveCell->Add(FormatStr("procflags: %s", cellData["procflags"]));
	saveCell->Add(FormatStr("procchance: %s", cellData["procchance"]));
	saveCell->Add(FormatStr("proccharges: %s", cellData["proccharges"]));
	saveCell->Add(FormatStr("maxlevel: %s", cellData["maxlevel"]));
	saveCell->Add(FormatStr("baselevel: %s", cellData["baselevel"]));
	saveCell->Add(FormatStr("spelllevel: %s", cellData["spelllevel"]));
	saveCell->Add(FormatStr("durationindex: %s", cellData["durationindex"]));
	saveCell->Add(FormatStr("powertype: %s", cellData["powertype"]));
	saveCell->Add(FormatStr("manacost: %s", cellData["manacost"]));
	saveCell->Add(FormatStr("manacostperlevel: %s", cellData["manacostperlevel"]));
	saveCell->Add(FormatStr("manapersecond: %s", cellData["manapersecond"]));
	saveCell->Add(FormatStr("manapersecondperlevel: %s", cellData["manapersecondperlevel"]));
	saveCell->Add(FormatStr("rangeindex: %s", cellData["rangeindex"]));
	saveCell->Add(FormatStr("speed: %s", cellData["speed"]));
	saveCell->Add(FormatStr("stackamount: %s", cellData["stackamount"]));
	saveCell->Add(FormatStr("totem0: %s", cellData["totem0"]));
	saveCell->Add(FormatStr("totem1: %s", cellData["totem1"]));
	saveCell->Add(FormatStr("reagent0: %s", cellData["reagent0"]));
	saveCell->Add(FormatStr("reagent1: %s", cellData["reagent1"]));
	saveCell->Add(FormatStr("reagent2: %s", cellData["reagent2"]));
	saveCell->Add(FormatStr("reagent3: %s", cellData["reagent3"]));
	saveCell->Add(FormatStr("reagent4: %s", cellData["reagent4"]));
	saveCell->Add(FormatStr("reagent5: %s", cellData["reagent5"]));
	saveCell->Add(FormatStr("reagent6: %s", cellData["reagent6"]));
	saveCell->Add(FormatStr("reagent7: %s", cellData["reagent7"]));
	saveCell->Add(FormatStr("reagentcount0: %s", cellData["reagentcount0"]));
	saveCell->Add(FormatStr("reagentcount1: %s", cellData["reagentcount1"]));
	saveCell->Add(FormatStr("reagentcount2: %s", cellData["reagentcount2"]));
	saveCell->Add(FormatStr("reagentcount3: %s", cellData["reagentcount3"]));
	saveCell->Add(FormatStr("reagentcount4: %s", cellData["reagentcount4"]));
	saveCell->Add(FormatStr("reagentcount5: %s", cellData["reagentcount5"]));
	saveCell->Add(FormatStr("reagentcount6: %s", cellData["reagentcount6"]));
	saveCell->Add(FormatStr("reagentcount7: %s", cellData["reagentcount7"]));
	saveCell->Add(FormatStr("equippeditemclass: %s", cellData["equippeditemclass"]));
	saveCell->Add(FormatStr("equippeditemsubclassmask: %s", cellData["equippeditemsubclassmask"]));
	saveCell->Add(FormatStr("equippediteminventorytypemask: %s", cellData["equippediteminventorytypemask"]));
	saveCell->Add(FormatStr("effect0: %s", cellData["effect0"]));
	saveCell->Add(FormatStr("effect1: %s", cellData["effect1"]));
	saveCell->Add(FormatStr("effect2: %s", cellData["effect2"]));
	saveCell->Add(FormatStr("effectdiesides0: %s", cellData["effectdiesides0"]));
	saveCell->Add(FormatStr("effectdiesides1: %s", cellData["effectdiesides1"]));
	saveCell->Add(FormatStr("effectdiesides2: %s", cellData["effectdiesides2"]));
	saveCell->Add(FormatStr("effectrealpointsperlevel0: %s", cellData["effectrealpointsperlevel0"]));
	saveCell->Add(FormatStr("effectrealpointsperlevel1: %s", cellData["effectrealpointsperlevel1"]));
	saveCell->Add(FormatStr("effectrealpointsperlevel2: %s", cellData["effectrealpointsperlevel2"]));
	saveCell->Add(FormatStr("effectbasepoints0: %s", cellData["effectbasepoints0"]));
	saveCell->Add(FormatStr("effectbasepoints1: %s", cellData["effectbasepoints1"]));
	saveCell->Add(FormatStr("effectbasepoints2: %s", cellData["effectbasepoints2"]));
	saveCell->Add(FormatStr("effectmechanic0: %s", cellData["effectmechanic0"]));
	saveCell->Add(FormatStr("effectmechanic1: %s", cellData["effectmechanic1"]));
	saveCell->Add(FormatStr("effectmechanic2: %s", cellData["effectmechanic2"]));
	saveCell->Add(FormatStr("effectimplicittargeta0: %s", cellData["effectimplicittargeta0"]));
	saveCell->Add(FormatStr("effectimplicittargeta1: %s", cellData["effectimplicittargeta1"]));
	saveCell->Add(FormatStr("effectimplicittargeta2: %s", cellData["effectimplicittargeta2"]));
	saveCell->Add(FormatStr("effectimplicittargetb0: %s", cellData["effectimplicittargetb0"]));
	saveCell->Add(FormatStr("effectimplicittargetb1: %s", cellData["effectimplicittargetb1"]));
	saveCell->Add(FormatStr("effectimplicittargetb2: %s", cellData["effectimplicittargetb2"]));
	saveCell->Add(FormatStr("effectradiusindex0: %s", cellData["effectradiusindex0"]));
	saveCell->Add(FormatStr("effectradiusindex1: %s", cellData["effectradiusindex1"]));
	saveCell->Add(FormatStr("effectradiusindex2: %s", cellData["effectradiusindex2"]));
	saveCell->Add(FormatStr("effectapplyauraname0: %s", cellData["effectapplyauraname0"]));
	saveCell->Add(FormatStr("effectapplyauraname1: %s", cellData["effectapplyauraname1"]));
	saveCell->Add(FormatStr("effectapplyauraname2: %s", cellData["effectapplyauraname2"]));
	saveCell->Add(FormatStr("effectamplitude0: %s", cellData["effectamplitude0"]));
	saveCell->Add(FormatStr("effectamplitude1: %s", cellData["effectamplitude1"]));
	saveCell->Add(FormatStr("effectamplitude2: %s", cellData["effectamplitude2"]));
	saveCell->Add(FormatStr("effectmultiplevalue0: %s", cellData["effectmultiplevalue0"]));
	saveCell->Add(FormatStr("effectmultiplevalue1: %s", cellData["effectmultiplevalue1"]));
	saveCell->Add(FormatStr("effectmultiplevalue2: %s", cellData["effectmultiplevalue2"]));
	saveCell->Add(FormatStr("effectchaintarget0: %s", cellData["effectchaintarget0"]));
	saveCell->Add(FormatStr("effectchaintarget1: %s", cellData["effectchaintarget1"]));
	saveCell->Add(FormatStr("effectchaintarget2: %s", cellData["effectchaintarget2"]));
	saveCell->Add(FormatStr("effectitemtype0: %s", cellData["effectitemtype0"]));
	saveCell->Add(FormatStr("effectitemtype1: %s", cellData["effectitemtype1"]));
	saveCell->Add(FormatStr("effectitemtype2: %s", cellData["effectitemtype2"]));
	saveCell->Add(FormatStr("effectmiscvalue0: %s", cellData["effectmiscvalue0"]));
	saveCell->Add(FormatStr("effectmiscvalue1: %s", cellData["effectmiscvalue1"]));
	saveCell->Add(FormatStr("effectmiscvalue2: %s", cellData["effectmiscvalue2"]));
	saveCell->Add(FormatStr("effectmiscvalueb0: %s", cellData["effectmiscvalueb0"]));
	saveCell->Add(FormatStr("effectmiscvalueb1: %s", cellData["effectmiscvalueb1"]));
	saveCell->Add(FormatStr("effectmiscvalueb2: %s", cellData["effectmiscvalueb2"]));
	saveCell->Add(FormatStr("effecttriggerspell0: %s", cellData["effecttriggerspell0"]));
	saveCell->Add(FormatStr("effecttriggerspell1: %s", cellData["effecttriggerspell1"]));
	saveCell->Add(FormatStr("effecttriggerspell2: %s", cellData["effecttriggerspell2"]));
	saveCell->Add(FormatStr("effectpointspercombopoint0: %s", cellData["effectpointspercombopoint0"]));
	saveCell->Add(FormatStr("effectpointspercombopoint1: %s", cellData["effectpointspercombopoint1"]));
	saveCell->Add(FormatStr("effectpointspercombopoint2: %s", cellData["effectpointspercombopoint2"]));
	saveCell->Add(FormatStr("effectspellclassmaska0: %s", cellData["effectspellclassmaska0"]));
	saveCell->Add(FormatStr("effectspellclassmaska1: %s", cellData["effectspellclassmaska1"]));
	saveCell->Add(FormatStr("effectspellclassmaska2: %s", cellData["effectspellclassmaska2"]));
	saveCell->Add(FormatStr("effectspellclassmaskb0: %s", cellData["effectspellclassmaskb0"]));
	saveCell->Add(FormatStr("effectspellclassmaskb1: %s", cellData["effectspellclassmaskb1"]));
	saveCell->Add(FormatStr("effectspellclassmaskb2: %s", cellData["effectspellclassmaskb2"]));
	saveCell->Add(FormatStr("effectspellclassmaskc0: %s", cellData["effectspellclassmaskc0"]));
	saveCell->Add(FormatStr("effectspellclassmaskc1: %s", cellData["effectspellclassmaskc1"]));
	saveCell->Add(FormatStr("effectspellclassmaskc2: %s", cellData["effectspellclassmaskc2"]));
	saveCell->Add(FormatStr("spellvisual0: %s", cellData["spellvisual0"]));
	saveCell->Add(FormatStr("spellvisual1: %s", cellData["spellvisual1"]));
	saveCell->Add(FormatStr("spelliconid: %s", cellData["spelliconid"]));
	saveCell->Add(FormatStr("activeiconid: %s", cellData["activeiconid"]));
	saveCell->Add(FormatStr("spellname0: %s", cellData["spellname0"]));
	saveCell->Add(FormatStr("spellname1: %s", cellData["spellname1"]));
	saveCell->Add(FormatStr("spellname2: %s", cellData["spellname2"]));
	saveCell->Add(FormatStr("spellname3: %s", cellData["spellname3"]));
	saveCell->Add(FormatStr("spellname4: %s", cellData["spellname4"]));
	saveCell->Add(FormatStr("spellname5: %s", cellData["spellname5"]));
	saveCell->Add(FormatStr("spellname6: %s", cellData["spellname6"]));
	saveCell->Add(FormatStr("spellname7: %s", cellData["spellname7"]));
	saveCell->Add(FormatStr("spellname8: %s", cellData["spellname8"]));
	saveCell->Add(FormatStr("spellname9: %s", cellData["spellname9"]));
	saveCell->Add(FormatStr("spellname10: %s", cellData["spellname10"]));
	saveCell->Add(FormatStr("spellname11: %s", cellData["spellname11"]));
	saveCell->Add(FormatStr("spellname12: %s", cellData["spellname12"]));
	saveCell->Add(FormatStr("spellname13: %s", cellData["spellname13"]));
	saveCell->Add(FormatStr("spellname14: %s", cellData["spellname14"]));
	saveCell->Add(FormatStr("spellname15: %s", cellData["spellname15"]));
	saveCell->Add(FormatStr("rank0: %s", cellData["rank0"]));
	saveCell->Add(FormatStr("rank1: %s", cellData["rank1"]));
	saveCell->Add(FormatStr("rank2: %s", cellData["rank2"]));
	saveCell->Add(FormatStr("rank3: %s", cellData["rank3"]));
	saveCell->Add(FormatStr("rank4: %s", cellData["rank4"]));
	saveCell->Add(FormatStr("rank5: %s", cellData["rank5"]));
	saveCell->Add(FormatStr("rank6: %s", cellData["rank6"]));
	saveCell->Add(FormatStr("rank7: %s", cellData["rank7"]));
	saveCell->Add(FormatStr("rank8: %s", cellData["rank8"]));
	saveCell->Add(FormatStr("rank9: %s", cellData["rank9"]));
	saveCell->Add(FormatStr("rank10: %s", cellData["rank10"]));
	saveCell->Add(FormatStr("rank11: %s", cellData["rank11"]));
	saveCell->Add(FormatStr("rank12: %s", cellData["rank12"]));
	saveCell->Add(FormatStr("rank13: %s", cellData["rank13"]));
	saveCell->Add(FormatStr("rank14: %s", cellData["rank14"]));
	saveCell->Add(FormatStr("rank15: %s", cellData["rank15"]));
	saveCell->Add(FormatStr("description0: %s", cellData["description0"]));
	saveCell->Add(FormatStr("description1: %s", cellData["description1"]));
	saveCell->Add(FormatStr("description2: %s", cellData["description2"]));
	saveCell->Add(FormatStr("description3: %s", cellData["description3"]));
	saveCell->Add(FormatStr("description4: %s", cellData["description4"]));
	saveCell->Add(FormatStr("description5: %s", cellData["description5"]));
	saveCell->Add(FormatStr("description6: %s", cellData["description6"]));
	saveCell->Add(FormatStr("description7: %s", cellData["description7"]));
	saveCell->Add(FormatStr("description8: %s", cellData["description8"]));
	saveCell->Add(FormatStr("description9: %s", cellData["description9"]));
	saveCell->Add(FormatStr("description10: %s", cellData["description10"]));
	saveCell->Add(FormatStr("description11: %s", cellData["description11"]));
	saveCell->Add(FormatStr("description12: %s", cellData["description12"]));
	saveCell->Add(FormatStr("description13: %s", cellData["description13"]));
	saveCell->Add(FormatStr("description14: %s", cellData["description14"]));
	saveCell->Add(FormatStr("description15: %s", cellData["description15"]));
	saveCell->Add(FormatStr("tooltip0: %s", cellData["tooltip0"]));
	saveCell->Add(FormatStr("tooltip1: %s", cellData["tooltip1"]));
	saveCell->Add(FormatStr("tooltip2: %s", cellData["tooltip2"]));
	saveCell->Add(FormatStr("tooltip3: %s", cellData["tooltip3"]));
	saveCell->Add(FormatStr("tooltip4: %s", cellData["tooltip4"]));
	saveCell->Add(FormatStr("tooltip5: %s", cellData["tooltip5"]));
	saveCell->Add(FormatStr("tooltip6: %s", cellData["tooltip6"]));
	saveCell->Add(FormatStr("tooltip7: %s", cellData["tooltip7"]));
	saveCell->Add(FormatStr("tooltip8: %s", cellData["tooltip8"]));
	saveCell->Add(FormatStr("tooltip9: %s", cellData["tooltip9"]));
	saveCell->Add(FormatStr("tooltip10: %s", cellData["tooltip10"]));
	saveCell->Add(FormatStr("tooltip11: %s", cellData["tooltip11"]));
	saveCell->Add(FormatStr("tooltip12: %s", cellData["tooltip12"]));
	saveCell->Add(FormatStr("tooltip13: %s", cellData["tooltip13"]));
	saveCell->Add(FormatStr("tooltip14: %s", cellData["tooltip14"]));
	saveCell->Add(FormatStr("tooltip15: %s", cellData["tooltip15"]));
	saveCell->Add(FormatStr("manacostpercentage: %s", cellData["manacostpercentage"]));
	saveCell->Add(FormatStr("startrecoverycategory: %s", cellData["startrecoverycategory"]));
	saveCell->Add(FormatStr("startrecoverytime: %s", cellData["startrecoverytime"]));
	saveCell->Add(FormatStr("maxtargetlevel: %s", cellData["maxtargetlevel"]));
	saveCell->Add(FormatStr("spellfamilyname: %s", cellData["spellfamilyname"]));
	saveCell->Add(FormatStr("spellfamilyflags: %s", cellData["spellfamilyflags"]));
	saveCell->Add(FormatStr("spellfamilyflags2: %s", cellData["spellfamilyflags2"]));
	saveCell->Add(FormatStr("maxaffectedtargets: %s", cellData["maxaffectedtargets"]));
	saveCell->Add(FormatStr("dmgclass: %s", cellData["dmgclass"]));
	saveCell->Add(FormatStr("preventiontype: %s", cellData["preventiontype"]));
	saveCell->Add(FormatStr("dmgmultiplier0: %s", cellData["dmgmultiplier0"]));
	saveCell->Add(FormatStr("dmgmultiplier1: %s", cellData["dmgmultiplier1"]));
	saveCell->Add(FormatStr("dmgmultiplier2 : %s", cellData["dmgmultiplier2"]));
	saveCell->Add(FormatStr("totemcategory0: %s", cellData["totemcategory0"]));
	saveCell->Add(FormatStr("totemcategory1: %s", cellData["totemcategory1"]));
	saveCell->Add(FormatStr("areagroupid: %s", cellData["areagroupid"]));
	saveCell->Add(FormatStr("schoolmask: %s", cellData["schoolmask"]));
	saveCell->Add(FormatStr("runecostid: %s", cellData["runecostid"]));



	int maxCount = 1000;
	int idPos = id / maxCount * maxCount;
	String dir = FormatStr("%s%d_%d\\", fileDir, idPos, idPos+maxCount);
	ForceDirectories(dir);
	String filePath = dir + cellData["id"] + ".txt";
	saveCell->SaveToFile(filePath);
}

void __fastcall TWOWReviewerMainFrm::btSaveSpellDataClick(TObject *Sender)
{
	String fileDir = ExtractFileDir(Application->ExeName) + "\\";
	String tableName = "Spell";
	fileDir += tableName + "\\";
	ForceDirectories(fileDir);
	auto_ptr<TStringList> outputLine(new TStringList);
	int rowCount = GetStoresCountByName(tableName);

	String header, value;
	for(int i=0; i<rowCount; i++)
	{
		AddDBCToStringList(tableName, i, outputLine.get());
		map<String, String> cell;
		for(int index=0; index<outputLine->Count; index++)
		{
			header = (*GetTableColumns())[tableName].Columns[index];
			value = outputLine->Strings[index];
			header = header.LowerCase();
			header = ReplaceStr(header, "_", "");
			cell[header.LowerCase()] = value;
		}
		SaveCell(fileDir, cell);
		return;
	}
}
//---------------------------------------------------------------------------

void __fastcall TWOWReviewerMainFrm::cbFilterPacketSizeClick(TObject *Sender)
{
	PackageContainer * curPackageContainer = GetWatchProxy();
	if(!curPackageContainer)
		return;
	if (cbFilterPacketSize->Checked)
	{
		curPackageContainer->SetFilterPacketSize(edtFilterPacketSize->Value);
	}
	else
	{
		curPackageContainer->SetFilterPacketSize(0);
	}
}
//---------------------------------------------------------------------------

