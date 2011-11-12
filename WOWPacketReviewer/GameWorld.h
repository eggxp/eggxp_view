//---------------------------------------------------------------------------

#ifndef GameWorldH
#define GameWorldH
//---------------------------------------------------------------------------
#include    <VCL.h>
#include 	<Psapi.h>
#include    "commfunc.h"
#include    "ReviewerCommon.h"
#include    "Opcodes.h"
#include    "AMap.h"
#include    "DataObject.h"
#include    <map>
#include    "SpellHandler.h"
#include    "FishHandler.h"
#include    "GameObjectHandler.h"
#include    "GroupHandler.h"
#include    "ItemHandler.h"
#include    "QuestHandler.h"
#include    "PlayerHandler.h"
#include    "GameNPCHandler.h"
#include    "ChatHandler.h"
#include    "MoveHandler.h"
#include    "PackSender.h"
#include    "GameMapManager.h"
#include 	"PlayerAuthHandler.h"
#include 	"EventHandler.h"
#include 	"AttackHandler.h"
#include 	"AQueue.h"


static  String  pos_info;

using namespace std;

struct tagPacketHandler {
    TPacketHandler  Handler;
    tagPacketHandler()
    {
        Handler = NULL;
    }
};

enum RedirectClientState
{
    RCS_NULL = 0,
    RCS_RECEIVE_REDIRECT_PACK,
    RCS_DISCONNECT,
    RCS_RECEIVE_AUTH_CHANLLAGE,
    RCS_REDIRECT_OK
};


void			ExtractDllFromExe();
String  GetSpellNameBySpellID(int spellid);
void 	RefreshGridTotal(GameWorld *m_GameWorld, String HitInfoStr, String type, String attackType);
String GetGUIDInfo(uint64 guid);
String GetObjectNameByGuid(uint64 guid);
String GetTalentNameByTalent(uint32 talentID, uint32 level);
String GetAchievementCriteriaName(int criterialID);
String GetAchievementName(int achievementID);
String GetFactionNameByReputationListID(int reputationListID);
String GetMapNameByMapID(int mapID);
String GetAreaNameByMapAndZone(int mapid, int zoneid);

struct tagServerMSTimeMutiParam
{
	double NowTick;
	double ServerMSTime;
	String MoveNPCName;
	double NowTime;
	tagServerMSTimeMutiParam()
	{
		NowTick = 0;
		ServerMSTime = 0;
		NowTick = GetNowTick();
		NowTime = Now();
	}
};


class FishAI;
class ReactionAI;
class ShowAllMapAI;
class AutoChatAI;
class FlyAI;
class SpeedChangeAI;
class WaterWalkingAI;
class GameWorld
{
private:
    String      m_AuthDataA;
    String      m_Password;
    bool        m_InputSessionKey;
    String      m_SessionKey;
    int         m_CurrentProcessIndex;
    int         m_CurrentRecvIndex;
	int         m_BlockMode;
	int         m_BlockOnlyMode;
    int         m_EnableHandlerPacket;
    int         m_EnableShowOrgPacket;
    int         m_GameDataLoaded;
    int         m_RedirectClientState;
    int         m_IsLoginOK;
	HANDLE      m_WOWWindowHandle;
	TDateTime	m_ExpireTime;
	HANDLE		m_WOWProcessHandle;
    String      m_Path;
	AIndexList<tagPacketHandler>    m_Handlers;
	AIndexList<tagPacketHandler>    m_AuthHandlers;
    shared_ptr<DataObject>  m_DataObject;
    PackSender      m_PackSender;
	GameMapManager     m_GameMapManager;
	TDateTime	m_LoginTime;

    SpellHandler    m_SpellHandler;
    FishHandler     m_FishHandler;
    GroupHandler    m_GroupHandler;
    GameObjectHandler m_GameObjectHandler;
    ItemHandler     m_ItemHandler;
    QuestHandler    m_QuestHandler;
	PlayerHandler   m_PlayerHandler;
	AttackHandler	m_AttackHandler;
	GameNPCHandler  m_GameNPCHandler;
	ChatHandler		m_ChatHandler;
	MoveHandler     m_MoveHandler;
	PlayerAuthHandler		m_PlayerAuthHandler;
	EventHandler   	m_EventHandler;
	DWORD			m_EndCounter;

	FishAI  *       m_FishAI;
	ReactionAI	*	m_ReactionAI;
	ShowAllMapAI * 	m_ShowAllMapAI;
	AutoChatAI	*	m_AutoChatAI;
	FlyAI		 *	m_FlyAI;
	SpeedChangeAI * m_SpeedChangeAI;
	WOWPackage	*	m_CurrentHandleringWOWPackage;
	WaterWalkingAI *m_WaterWalkingAI;

	TStringList *   m_ItemPickupList;
	bool			m_AddrInited;
	TStringList *   m_PackForbiddenList;

	void			OnInjectOK();
	HANDLE      	FindWindowFunc();
	String			m_DllFileName;
	int				m_ItemFieldEnchantmentValue1;		//神奇的数值， 拿出来研究

	map<int, vector<tagServerMSTimeMutiParam> >	m_ServerMSTimeMutiParam;
public:
	GameWorld();
	~GameWorld();
	void        Clear();

	shared_ptr<DataObject>          GetDataByKey(String key);

	ShowAllMapAI	*GetShowAllMapAI(){return	m_ShowAllMapAI;}
	FlyAI			*GetFlyAI(){return m_FlyAI;}
	WaterWalkingAI	*GetWaterWalkingAI(){return m_WaterWalkingAI;}
	SpeedChangeAI   *GetSpeedChangeAI(){return m_SpeedChangeAI;}

	vector<tagServerMSTimeMutiParam> *GetServerMSTimeMutiParam(int type) {return &m_ServerMSTimeMutiParam[type];}
	tagServerMSTimeMutiParam *GetServerMSTimeMutiParamData(int type);

	GEN_GET_SET(TDateTime, LoginTime);
	GEN_GET_SET(String, AuthDataA)
    GEN_GET_SET(String, Password)
    GEN_GET_SET(bool, InputSessionKey);
    GEN_GET_SET(String, SessionKey);
    GEN_GET_SET(int, CurrentProcessIndex);
	GEN_GET_SET(int, BlockMode);
	GEN_GET_SET(int, BlockOnlyMode);
    GEN_GET_SET(int, EnableHandlerPacket);
	GEN_GET_SET(int, EnableShowOrgPacket);
	GEN_GET_SET(DWORD, EndCounter);
	GEN_GET_SET(String, Path);
	GEN_GET_SET(HANDLE, WOWWindowHandle);
	GEN_GET_SET(HANDLE, WOWProcessHandle);
	GEN_GET_SET(TDateTime, ExpireTime);
	GEN_GET_SET(String, DllFileName);
	GEN_GET_SET(int, ItemFieldEnchantmentValue1);
    GEN_GET_SET(int, RedirectClientState);
    GEN_GET_SET(int, IsLoginOK);

    GEN_POINTER_GET(SpellHandler)
    GEN_POINTER_GET(FishHandler)
    GEN_POINTER_GET(GroupHandler)
    GEN_POINTER_GET(GameObjectHandler)
    GEN_POINTER_GET(ItemHandler)
    GEN_POINTER_GET(QuestHandler)
	GEN_POINTER_GET(PlayerHandler)
	GEN_POINTER_GET(AttackHandler)
	GEN_POINTER_GET(GameNPCHandler)
	GEN_POINTER_GET(ChatHandler)
    GEN_POINTER_GET(MoveHandler)
    GEN_POINTER_GET(PackSender)
	GEN_POINTER_GET(GameMapManager)
	GEN_POINTER_GET(PlayerAuthHandler)
	GEN_POINTER_GET(EventHandler)
	FishAI  *       GetFishAI(){return m_FishAI;}
	AutoChatAI *	GetAutoChatAI(){return m_AutoChatAI;}
	WOWPackage	*	GetCurrentHandleringWOWPackage(){return m_CurrentHandleringWOWPackage;}

	void        RegisterHandler(DWORD   handlertype, TPacketHandler handler);
	void        HandlerPacket(WOWPackage * packet);

    void        RegisterAuthHandler(DWORD   handlertype, TPacketHandler handler);
	void        HandlerAuthPacket(WOWPackage * packet);

	void        InternalRegisterHandler(AIndexList<tagPacketHandler>   *handlers, DWORD   handlertype, TPacketHandler handler);
	void        InternalHandlerPacket(AIndexList<tagPacketHandler>   *handlers, WOWPackage * packet);


	void        SetData(String key, String name);
	void		DeleteData(String key);
    int         GetDataInt(String key);
    String      GetDataStr(String key);
    float       GetDataFloat(String key);

    void        InitFiberProcesser();
    void        LoadGameData(String path);
	void        LoadFishData();
	void		LoadItemNameData();
	void		LoadGameObjectData();
	void		LoadCreatureNameData();

    uint64      GetSelfGUID();
    uint64      GetDataGUID(String guidstrl, String guidstrh);
    bool        IsSameGUID(uint64 guid, String guidstrl, String guidstrh);
    shared_ptr<DataObject>  GetRootData(){return    m_DataObject;}

	String      GetItemNameByID(int id);
	String      GetGameObjectNameByID(int id);
	String      GetCreatureNameByID(int id);
	int			GetItemPickupListCount();
	int			GetItemPickupListAt(int index);
	int			FindItemInPickupList(int itemID);
	void		AddItemPickupList(int itemID);
	void		DeleteItemPickupList(int index);
	void		ClearItemPickupList();
	void		SaveItemPickupList();

	void	   	RefreshSystemInitAddr();
	String		GetWOWPath();
	int			GetWOWBuild();
	int 		FindWOWVersion();

	void		SetClientSessionKey(String key);
	void        InjectDll(String DllFullPath, String frmClassName);

	void		CheckWOWClosedRefresh();
	void		RefreshFishResult();

	void		OnRelogin();
	void		LoadPackForbiddenList();
	bool		IsPacketForbidden(String opcodeName);
};


GameWorld       *       GetGameWorld();


#define     REG_HANDLER(TYPE)   m_GameWorld->RegisterHandler(TYPE, Handler_##TYPE);
#define     REG_AUTH_HANDLER(TYPE)   m_GameWorld->RegisterAuthHandler(TYPE, Handler_##TYPE);
#endif
