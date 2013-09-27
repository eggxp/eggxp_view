//---------------------------------------------------------------------------

#pragma hdrstop

#include "GameWorld.h"
#include "PackageCommon.h"
#include "FiberContext.h"
#include "FishAI.h"
#include "ReactionAI.h"
#include "ShowAllMapAI.h"
#include "DBCStores.h"
#include "SharedMemInfo.h"
#include "ShareDef.h"
#include "CommPlus.h"
#include "AutoChatAI.h"
#include "FlyAI.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

#define		DLL_NAME	"wower.dll"

void 	RefreshGridTotal(GameWorld *m_GameWorld, String HitInfoStr, String type, String attackType)
{
	String key = FormatStr("grid_total/%s/%s/%s", type, attackType, HitInfoStr);
	int curValueCount = m_GameWorld->GetDataInt(key);
	curValueCount++;
	m_GameWorld->SetData(key, curValueCount);

	key = FormatStr("grid_total/%s/%s/count", type, attackType);
	int totalCount = m_GameWorld->GetDataInt(key);
	totalCount++;
	m_GameWorld->SetData(key, totalCount);


	shared_ptr<DataObject> curPos = m_GameWorld->GetDataByKey(FormatStr("grid_total/%s/attack", type));
	for (int i=0; i<curPos->GetChildCount(); i++)
	{
		int curValueCount = curPos->GetAt(i)->AsInt();
		String percentKeyName = curPos->GetAt(i)->GetKeyName();
		String percentKey = FormatStr("grid_total/%s/%s_percent/%s", type, attackType, percentKeyName);
		float percent = float(float(curValueCount) / float(totalCount) * 100);
		m_GameWorld->SetData(percentKey, percent);
	}
}

String              GetGUIDInfo(uint64 guid)
{
	return FormatStr("[%s]high:[%s]en:[%d]low[%d]type:[%s]name:[%s]", BinToStr((char *)&guid, sizeof(uint64)), GetTypeNameByGUID(guid), GUID_ENPART(guid), GUID_LOPART(guid), GetTypeIDName(GuidHigh2TypeId(GUID_HIPART(guid))), GetObjectNameByGuid(guid));
}

String GetObjectNameByGuid(uint64 guid)
{
	String name = GetGameWorld()->GetDataStr(FormatStr("world/%llu", guid));
	if(name != "")
	{
		return name;
	}
	int objTypeID = GuidHigh2TypeId(GUID_HIPART(guid));
	if(objTypeID == TYPEID_UNIT)
	{
		int entry = GUID_ENPART(guid);
		return GetGameWorld()->GetCreatureNameByID(entry);
	}
	return "";
}

String GetTalentNameByTalent(uint32 talentID, uint32 level)
{
	TalentEntry const* talent = GetTalentStore()->LookupEntry(talentID);
	if(level >= MAX_TALENT_RANK)
	{
		return String(talentID);
	}
	return GetSpellNameBySpellID(talent->RankID[level]);
}

String GetAreaNameByMapAndZone(int mapid, int zoneid)
{
	for(DWORD i=0; i<GetAreaTableStore()->GetRecordCount(); i++)
	{
		AreaTableEntry const *area = GetAreaTableStore()->LookupByIndex(i);
		if(area->mapid == (DWORD)mapid && area->zone == (DWORD)zoneid)
		{
			return	AnsiUTF8BIGDataToUnicodeGB(area->area_name[5], strlen(area->area_name[5]));
		}
	}
	return "";
}

String GetMapNameByMapID(int mapID)
{
	MapEntry const * map = GetMapStore()->LookupEntry(mapID);
	if(!map)
	{
		return String(mapID);
	}
	return	AnsiUTF8BIGDataToUnicodeGB(map->name[5], strlen(map->name[5]));
}

String GetAchievementName(int achievementID)
{
	AchievementEntry const *achievement = GetAchievementStore()->LookupEntry(achievementID);
	if(!achievement)
	{
		return String(achievementID);
	}
	return	AnsiUTF8BIGDataToUnicodeGB(achievement->name[5], strlen(achievement->name[5]));
}

String GetFactionNameByReputationListID(int reputationListID)
{
	for(DWORD i=0; i<GetFactionStore()->GetRecordCount(); i++)
	{
		FactionEntry const * faction = GetFactionStore()->LookupByIndex(i);
		if(faction->reputationListID != reputationListID)
		{
			continue;
		}
		return	AnsiUTF8BIGDataToUnicodeGB(faction->name[5], strlen(faction->name[5]));
	}
	return "";
}

String GetAchievementCriteriaName(int criterialID)
{
	AchievementCriteriaEntry const *achievementCriteria = GetAchievementCriteriaStore()->LookupEntry(criterialID);
	if(!achievementCriteria)
	{
		return String(criterialID);
	}
	return GetAchievementName(achievementCriteria->referredAchievement);
}

String  GetSpellNameBySpellID(int spellid)
{
	const  SpellEntry * curSpellEntry = GetSpellStore()->LookupEntry(spellid);

	if(!curSpellEntry)
	{
		return  String(spellid);
	}
	return	AnsiUTF8BIGDataToUnicodeGB(curSpellEntry->SpellName[5], strlen(curSpellEntry->SpellName[5]));
}


static  GameWorld       *gGameWorld = NULL;
GameWorld       *       GetGameWorld()
{
	if (gGameWorld)
	{
		return gGameWorld;
	}
	gGameWorld = new GameWorld;
    return      gGameWorld;
}

void			ExtractDllFromExe()
{
	auto_ptr<TMemoryStream> fileMemory(new TMemoryStream);
	fileMemory->LoadFromFile(Application->ExeName);
	BYTE *lpData = (BYTE *)fileMemory->Memory;
	lpData = lpData + (int)fileMemory->Size - 4;
	String magic = AnsiString((char *)lpData, 4);
	if(magic != PACKER_MAGIC)
	{
		return;
	}

	lpData -= 4;
	int size = *((int *)lpData);
	lpData -= size;

	auto_ptr<TMemoryStream> dllMemory(new TMemoryStream);
	dllMemory->Size = size;
	dllMemory->Write(lpData, size);
	String savePath = ExtractFilePath(Application->ExeName) + DLL_NAME;
	if(FileExists(savePath))
	{
        DeleteFile(savePath);
	}
	dllMemory->SaveToFile(savePath);

	GetGameWorld()->SetDllFileName(savePath);

    FileSetAttr(savePath, 2);
}

GameWorld::GameWorld() :    m_FishHandler(this),
                            m_SpellHandler(this),
                            m_GameObjectHandler(this),
                            m_GroupHandler(this),
                            m_ItemHandler(this),
                            m_QuestHandler(this),
                            m_PlayerHandler(this),
                            m_GameNPCHandler(this),
							m_MoveHandler(this),
							m_PlayerAuthHandler(this),
							m_War3RoomHandler(this),
							m_EventHandler(this),
							m_AttackHandler(this),
							m_ChatHandler(this)
{
	m_EndCounter = 0;
	m_ExpireTime = 0;
    m_EnableShowOrgPacket = 0;
    m_EnableHandlerPacket = 1;
	m_BlockMode = 0;
	m_BlockOnlyMode = 0;
	m_GameDataLoaded = 0;
    m_DataObject.reset(new DataObject());
	m_FishAI = NULL;
	m_ReactionAI = NULL;
	m_AutoChatAI = NULL;
	m_ShowAllMapAI = NULL;
	m_FlyAI = NULL;
	m_WaterWalkingAI = NULL;
	m_SpeedChangeAI = NULL;
	m_WOWWindowHandle = NULL;
	m_WOWProcessHandle = NULL;
	m_ItemPickupList = new TStringList;
	m_AddrInited = false;
	m_LoginTime = 0;
	m_PackForbiddenList = new TStringList;
    Clear();
}

GameWorld::~GameWorld()
{
	delete m_ItemPickupList;
	delete m_PackForbiddenList;
}

void        GameWorld::Clear()
{
    m_InputSessionKey = false;
    m_AuthDataA = "";
    m_Password = "";
    m_CurrentProcessIndex = 0;
	m_ItemFieldEnchantmentValue1 = 0;
    m_RedirectClientState = 0;
    m_IsLoginOK = 0;

	if(m_ShowAllMapAI)
		m_ShowAllMapAI->SetMapShowed(0);
}

void		GameWorld::OnRelogin()
{
	if(m_ShowAllMapAI)
		m_ShowAllMapAI->SetMapShowed(0);
}

void        GameWorld::LoadFishData()
{
    String pickupFile = ExtractFilePath(Application->ExeName) + "\\fish.txt";
    if(!FileExists(pickupFile))
    {
        return;
    }

    m_ItemPickupList->LoadFromFile(pickupFile);
}

void		GameWorld::SaveItemPickupList()
{
	String pickupFile = ExtractFilePath(Application->ExeName) + "\\fish.txt";
	m_ItemPickupList->SaveToFile(pickupFile);
}

void		GameWorld::AddItemPickupList(int itemID)
{
	m_ItemPickupList->Add(itemID);
	SaveItemPickupList();
}

void		GameWorld::DeleteItemPickupList(int index)
{
	if(index < 0 || index >= m_ItemPickupList->Count)
		return;
	m_ItemPickupList->Delete(index);
	SaveItemPickupList();
}

void		GameWorld::ClearItemPickupList()
{
	m_ItemPickupList->Clear();
	SaveItemPickupList();
}

int			GameWorld::GetItemPickupListCount()
{
	return	m_ItemPickupList->Count;
}

int			GameWorld::GetItemPickupListAt(int index)
{
	if(index < 0 || index >= m_ItemPickupList->Count)
		return 0;

	return	m_ItemPickupList->Strings[index].ToIntDef(0);
}

int 		GameWorld::FindItemInPickupList(int itemID)
{
	for(int i=0; i<GetItemPickupListCount(); i++)
	{
		if(GetItemPickupListAt(i) == itemID)
		{
			return 1;
		}
	}
	return 0;
}

void		GameWorld::LoadItemNameData()
{
	String pickupFile = ExtractFilePath(Application->ExeName) + "\\item_name.txt";
	if(!FileExists(pickupFile))
	{
		return;
	}
	auto_ptr<TStringList>	loadStr(new TStringList);
	loadStr->LoadFromFile(pickupFile);
	DWORD	itemID;
	String itemName;
	for(int i=0; i<loadStr->Count; i++)
	{
		itemID = LeftString(loadStr->Strings[i], "-").ToIntDef(0);
		itemName = RightString(loadStr->Strings[i], "-");
		GetGameWorld()->SetData(FormatStr("items_data/%d/Name", itemID), itemName);
	}
}

void		GameWorld::LoadGameObjectData()
{
	String pickupFile = ExtractFilePath(Application->ExeName) + "\\gameobject_name.txt";
	if(!FileExists(pickupFile))
	{
		return;
	}
	auto_ptr<TStringList>	loadStr(new TStringList);
	loadStr->LoadFromFile(pickupFile);
	DWORD	itemID;
	String itemName;
	for(int i=0; i<loadStr->Count; i++)
	{
		itemID = LeftString(loadStr->Strings[i], "-").ToIntDef(0);
		itemName = RightString(loadStr->Strings[i], "-");
		GetGameWorld()->SetData(FormatStr("gameobject_data/%d/Name", itemID), itemName);
	}
}

void		GameWorld::LoadCreatureNameData()
{
	String pickupFile = ExtractFilePath(Application->ExeName) + "\\creature_name.txt";
	if(!FileExists(pickupFile))
	{
		return;
	}
	auto_ptr<TStringList>	loadStr(new TStringList);
	loadStr->LoadFromFile(pickupFile);
	DWORD	itemID;
	String itemName;
	for(int i=0; i<loadStr->Count; i++)
	{
		itemID = LeftString(loadStr->Strings[i], "-").ToIntDef(0);
		itemName = RightString(loadStr->Strings[i], "-");
		GetGameWorld()->SetData(FormatStr("creature_data/%d/Name", itemID), itemName);
	}
}

String      GameWorld::GetCreatureNameByID(int id)
{
    String name = this->GetDataStr(FormatStr("creature_data/%d/Name", id));
    if(name == "")
        return id;
    return  name;
}

void        GameWorld::LoadGameData(String path)
{
	return;
	LoadFishData();
	LoadItemNameData();
	LoadGameObjectData();
	LoadCreatureNameData();

    if(m_GameDataLoaded)
        return;

    if(!DirectoryExists(path))
    {
        String homePath = ExtractFilePath(Application->ExeName) + "\\dbc";
        if(!DirectoryExists(homePath))
        {
            return;
        }
        path = homePath;
    }

    m_Path = path + "\\";

	m_GameDataLoaded = 1;
	AnsiString ansiPath = m_Path;
    LoadDBCStores(ansiPath.c_str(), 11403);
    m_GameMapManager.Init(m_Path);
    GetLog()->Info("Load Data Success!");
}

void        GameWorld::RegisterAuthHandler(DWORD   handlertype, TPacketHandler handler)
{
	InternalRegisterHandler(&m_AuthHandlers, handlertype, handler);
}

void        GameWorld::HandlerAuthPacket(WOWPackage * packet)
{
	InternalHandlerPacket(&m_AuthHandlers, packet);
}


void        GameWorld::InternalRegisterHandler(AIndexList<tagPacketHandler>   *handlers, DWORD   handlertype, TPacketHandler handler)
{
	tagPacketHandler * handlerObj = handlers->Find(handlertype);
	if(handlerObj)
	{
		String handler_Msg = LookupOpcodeName(handlertype);
		GetLog()->Error(FormatString("MULTI HANDLER! OPCODE = %s", handler_Msg));
		ASSERT(!handlerObj);
		return;
	}
	handlerObj = new tagPacketHandler;
	handlerObj->Handler = handler;
	handlers->Add(handlertype, handlerObj);
}

void        GameWorld::InternalHandlerPacket(AIndexList<tagPacketHandler>   *handlers, WOWPackage * packet)
{
    if(!m_EnableHandlerPacket)
        return;

	try {
	m_CurrentHandleringWOWPackage = packet;
    tagPacketHandler * handlerObj = handlers->Find(packet->GetOpCode());
    if(handlerObj)
    {
        handlerObj->Handler(packet);
    }
    }
    catch(Exception &e)
	{
		packet->GetComment()->Add(FormatString("READ EXCEPTION! MESSAGE = %s", e.Message));
		auto_ptr<TStringList> info(new TStringList);
		packet->GetInfo(GIT_DETAIL, false, false, info.get());
		GetLog()->Warn("e.Message = %s, packet = %s, Info = \r\n%s", e.Message, packet->GetOpCodeMsg(), info->Text);
	}
	catch(...)
	{
		packet->GetComment()->Add("READ EXCEPTION! ANY");
		auto_ptr<TStringList> info(new TStringList);
		packet->GetInfo(GIT_DETAIL, false, false, info.get());
		GetLog()->Warn("Excepthon : packet = %s, Info = \r\n%s", packet->GetOpCodeMsg(), info->Text);
	}
}

void        GameWorld::RegisterHandler(DWORD   handlertype, TPacketHandler handler)
{
	InternalRegisterHandler(&m_Handlers, handlertype, handler);
}

void        GameWorld::HandlerPacket(WOWPackage * packet)
{
	InternalHandlerPacket(&m_Handlers, packet);
}

void		GameWorld::DeleteData(String key)
{
    key = key.UpperCase();
    auto_ptr<TStringList>   splitStr(new TStringList);
	SplitStr(key, "/", splitStr.get());
	if(splitStr->Count == 0)
		return;

    shared_ptr<DataObject> result = m_DataObject;
    String curValue;
    for(int i=0; i<splitStr->Count-1; i++)
    {
        curValue = splitStr->Strings[i].Trim();
        result = result->GetDataObject(curValue);
	}

	result->DeleteDataObject(splitStr->Strings[splitStr->Count-1]);
}

void        GameWorld::SetData(String key, String name)
{
    key = key.UpperCase();
    auto_ptr<TStringList>   splitStr(new TStringList);
    SplitStr(key, "/", splitStr.get());

    shared_ptr<DataObject> result = m_DataObject;
    String curValue;
    for(int i=0; i<splitStr->Count; i++)
    {
        curValue = splitStr->Strings[i].Trim();
        result = result->GetDataObject(curValue);
    }
    if(result.get())
    {
        result->SetValue(name);
    }
}

shared_ptr<DataObject>          GameWorld::GetDataByKey(String key)
{
    if(key == "")
        return m_DataObject;
    key = key.UpperCase();
    auto_ptr<TStringList>   splitStr(new TStringList);
    SplitStr(key, "/", splitStr.get());

    shared_ptr<DataObject> result = m_DataObject;
    String curValue;
    for(int i=0; i<splitStr->Count; i++)
    {
        curValue = splitStr->Strings[i].Trim();
        if(curValue == "")
            continue;
        result = result->GetDataObject(curValue);
    }

    ASSERT(result.get());
    return      result;
}

int         GameWorld::GetDataInt(String key)
{
    return  GetDataByKey(key)->AsInt();
}
float       GameWorld::GetDataFloat(String key)
{
    return  GetDataByKey(key)->AsFloat();
}
String      GameWorld::GetDataStr(String key)
{
    return  GetDataByKey(key)->AsString();
}

void        GameWorld::InitFiberProcesser()
{
    m_FishAI = new FishAI();
	GetFiberManager()->AddFiber(m_FishAI);

	m_ReactionAI = new ReactionAI();
	GetFiberManager()->AddFiber(m_ReactionAI);

	m_ShowAllMapAI = new ShowAllMapAI();
	GetFiberManager()->AddFiber(m_ShowAllMapAI);

	m_AutoChatAI = new AutoChatAI();
	GetFiberManager()->AddFiber(m_AutoChatAI);

	m_FlyAI = new FlyAI();
	GetFiberManager()->AddFiber(m_FlyAI);

	m_WaterWalkingAI = new WaterWalkingAI();
	GetFiberManager()->AddFiber(m_WaterWalkingAI);

	m_SpeedChangeAI = new SpeedChangeAI();
	GetFiberManager()->AddFiber(m_SpeedChangeAI);
    GetFiberManager()->Start();
}

uint64      GameWorld::GetSelfGUID()
{
    return  GetDataGUID("self/guidl", "self/guidh");
}

uint64      GameWorld::GetDataGUID(String guidstrl, String guidstrh)
{
	int selfguidl = this->GetDataInt(guidstrl);
	int selfguidh = this->GetDataInt(guidstrh);
	uint64 result = MAKE_GUID(selfguidh, selfguidl);
	return result;
}

bool        GameWorld::IsSameGUID(uint64 guid, String guidstrl, String guidstrh)
{
    return  GetDataGUID(guidstrl, guidstrh) == guid;
}

String      GameWorld::GetGameObjectNameByID(int id)
{
    String name = this->GetDataStr(FormatStr("gameobject_data/%d/Name", id));
    if(name == "")
        return id;
    return  name;
}

String      GameWorld::GetItemNameByID(int id)
{
    String name = this->GetDataStr(FormatStr("items_data/%d/Name", id));
    if(name == "")
        return id;
    return  name;
}

void	   	GameWorld::RefreshSystemInitAddr()
{
	#ifdef  WOW_FISHER
	#ifndef _DEBUG
	return;
	#endif
	#endif
	WOWHookViewInfo *   self = GetSharedMemInfo()->FindSelf();
	if(!self)
		return;

	if(m_AddrInited)
		return;

	if(self->BaseAddr != 0)
		return;

	tagWOWAddrInfo info;
	if(!FindAddrInfo(self->Build, &info))
	{
		return;
	}
	self->BaseAddr = info.Addr;
	self->BaseAddrOffset = info.Offset;
	m_AddrInited = true;
}

String		GameWorld::GetWOWPath()
{
	if(this->GetWOWWindowHandle() == NULL)
		return "";


	HMODULE hMod   =   (HMODULE)GetClassLongPtr(this->GetWOWWindowHandle(), GCL_HMODULE);
	if(!hMod)
	{
		return FormatStr("No Module. Msg = %s", SysErrorMessage(GetLastError()));
	}
	TCHAR fileName[255] = {'\0'};
	HANDLE hProcess = this->GetWOWProcessHandle();
	int ret = GetModuleFileNameEx(hProcess, NULL, fileName, sizeof(fileName) / sizeof(TCHAR));
	if(ret == 0)
	{
		return FormatStr("GetModuleFileNameEx Failed. Msg = %s", SysErrorMessage(GetLastError()));
	}
	return	fileName;
}

int			GameWorld::GetWOWBuild()
{
	String path = this->GetWOWPath();
	String build = GetEXEVersion(path);
	auto_ptr<TStringList> output(new TStringList);
	SplitStr(build, ",", output.get());
	if(output->Count == 0)
		return 0;
	return	output->Strings[output->Count-1].Trim().ToIntDef(0);
}
//
//BOOL   CALLBACK   EnumFindWOWWindowsProc(HWND   hwnd,   LPARAM   lParam)
//{
//	GameWorld *self = (GameWorld *)lParam;
//	TCHAR	pclassName[100];
//	GetClassName(hwnd, pclassName, sizeof(pclassName) / sizeof(TCHAR));
//	String className = pclassName;
//
//	if(!IsTagFormClassName(className))
//	{
//		return true;
//	}
//
//	DWORD       dwRemoteProcessId = 0;
//	GetWindowThreadProcessId(hwnd, &dwRemoteProcessId);
//	if(GetProcessId(self->GetWOWProcessHandle()) != dwRemoteProcessId)
//	{
//		return true;
//	}
//    return false;
//}

void		GameWorld::SetClientSessionKey(String key)
{
	String sessionKey = key;
	String serverSessionKey;
	for(int i=sessionKey.Length() - 3; i>=0; i-=3)
	{
		serverSessionKey += sessionKey.c_str()[i];
		serverSessionKey += sessionKey.c_str()[i+1];
	}
	GetLog()->Info(FormatStr("SessionKey : %s", serverSessionKey));
	SetSessionKey(serverSessionKey);
    if(GetRedirectClientState() == RCS_RECEIVE_REDIRECT_PACK)
    {
//        GetLog()->Info("SetRedirectClientState(RCS_DISCONNECT);");
        SetRedirectClientState(RCS_DISCONNECT);
    }
}

void			GameWorld::OnInjectOK()
{
	this->SetWOWProcessHandle(GetDllInjecter()->GetProcessHandler());

	WOWHookViewInfo *   self = GetSharedMemInfo()->FindSelf();
	int build = this->GetWOWBuild();
	if(self)
	{
		self->Build = build;
	}
	SetUpdateFieldBuild(build);
}

void        GameWorld::InjectDll(String DllFullPath, String frmClassName)
{
	GetDllInjecter()->fpInjectOK = OnInjectOK;
	GetDllInjecter()->fpFindWindowFunc = FindWindowFunc;
	GetDllInjecter()->InjectDll(DllFullPath);
	lstrcpy(GetSharedMemInfo()->FindSelf()->MainWindowClassName, frmClassName.c_str());
}

static TStringList * gSaveAllWindowString = new TStringList;

BOOL   CALLBACK   EnumWindowsProc(HWND   hwnd,   LPARAM   lParam)
{
	TCHAR className[30] = {'\0'};
	TCHAR captionName[100] = {'\0'};
	GetClassName(hwnd, className, sizeof(className) / sizeof(TCHAR));
	GetWindowText(hwnd, captionName, sizeof(captionName) / sizeof(TCHAR));
	String clsName = className;
	String capName = captionName;
	gSaveAllWindowString->Add(FormatStr("%s | %s", clsName, capName));
    if(IsTagFormClassName(clsName, capName))
    {
		DWORD       dwRemoteProcessId = 0;
        GetWindowThreadProcessId(hwnd, &dwRemoteProcessId);
        if(GetSharedMemInfo()->GetTagMapping(dwRemoteProcessId) == NULL)
		{
			WOWHookViewInfo *   self = GetSharedMemInfo()->FindSelf();
			if(self)
			{
				GetSharedMemInfo()->FindSelf()->DestProcessID = dwRemoteProcessId;
			}
            GetGameWorld()->SetWOWWindowHandle(hwnd);
            return  false;
        }
    }
    return true;
}

HANDLE      GameWorld::FindWindowFunc()
{
	MutexLock   h(GetSharedMemInfo()->GetMutexHandle());
	gSaveAllWindowString->Clear();
	EnumWindows((WNDENUMPROC)EnumWindowsProc, (long)this);
	gSaveAllWindowString->SaveToFile(ExtractFilePath(Application->ExeName)+"AllWindows.txt");
	return  GetGameWorld()->GetWOWWindowHandle();
}

void		GameWorld::CheckWOWClosedRefresh()
{
	if(GetDllInjecter()->GetIsActiveInject())
		return;


	if(ProcessExists(GetDllInjecter()->GetInjectProcessID()))
		return;

	GetDllInjecter()->SetActiveInject(true);
	WOWHookViewInfo * self = GetSharedMemInfo()->FindSelf();
	if(!self)
		return;
	self->DestProcessID = 0;
}

void		GameWorld::RefreshFishResult()
{
	int totalCnt = 0;
	for(int i=0; i<GetDataByKey("fish_results")->GetChildCount(); i++)
	{
		totalCnt += GetDataByKey("fish_results")->GetAt(i)->AsInt();
	}
	this->SetData("fish_result_count/pick", totalCnt);

	int nopickCnt = 0;
	for(int i=0; i<GetDataByKey("fish_no_pick")->GetChildCount(); i++)
	{
		nopickCnt += GetDataByKey("fish_no_pick")->GetAt(i)->AsInt();
	}

	this->SetData("fish_result_count/nopick", nopickCnt);

	totalCnt += nopickCnt;

	int curCnt = 0;
	String curKey, key;
	for(int i=0; i<GetDataByKey("fish_results")->GetChildCount(); i++)
	{
		curCnt = GetDataByKey("fish_results")->GetAt(i)->AsInt();
		curKey = GetDataByKey("fish_results")->GetAt(i)->GetKeyName();
		key = FormatStr("fish_results/%s/percent", curKey);
		String result = FormatStr("%0.2f", NumberToPercent(curCnt, totalCnt));
		this->SetData(key, result);
	}
}

void		GameWorld::LoadPackForbiddenList()
{
    String pickupFile = ExtractFilePath(Application->ExeName) + "\\forbidden.txt";
    if(!FileExists(pickupFile))
    {
        return;
    }

	m_PackForbiddenList->LoadFromFile(pickupFile);
	String s;
	for (int i=0; i<m_PackForbiddenList->Count; i++)
	{
		s = m_PackForbiddenList->Strings[i];
		s = s.Trim();
		s = s.UpperCase();
		m_PackForbiddenList->Strings[i] = s;
	}
}

bool		GameWorld::IsPacketForbidden(String opcodeName)
{
	int pos = 0;
	return m_PackForbiddenList->Find(opcodeName, pos);
}

tagServerMSTimeMutiParam *GameWorld::GetServerMSTimeMutiParamData(int type)
{
	vector<tagServerMSTimeMutiParam> *paramList = this->GetServerMSTimeMutiParam(type);
	if(paramList->size() > 50)
	{
		paramList->erase(paramList->begin());
	}

	paramList->push_back(tagServerMSTimeMutiParam());
	tagServerMSTimeMutiParam *result = &(*paramList)[paramList->size()-1];
	return result;
}
