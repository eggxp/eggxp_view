//---------------------------------------------------------------------------

#ifndef AutoManageListConfigH
#define AutoManageListConfigH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <ValEdit.hpp>
#include "HEcommon.h"
#include "ShareDefine.h"
//改这个列表之后要改： AutoManageListConfig构造函数，  setup窗口中的 tag 
enum	TAutoManage {amAutoKongfu, amPatrol, amChangeLine, amAutoDropItem, amAutoUploadItem, amAutoOpenBox,
					amUnAttackNPCType, amAutoSell, amAutoBuy, amAutoRepair, amFastSkill, amAutoSaveMoneyHouse,
					amAutoDelivery, amAskTeamPlayer, amAccTeamLeader, amAutoGetDelivery, amPlayerBlackList,
					amLearnKongfuList, amAutoBuyShopItem, amAutoSellShopItem, amAutoTeamStr, amAutoMerge,
					amBlackList, amBlockString, amDaiLianAsk, amAccDaiLian, amAutoPaoTui,
                    amAutoSearch, amDoNotJoinTeam
					};

class AutoManageListConfig;


//一条列表数据
class AutoManageList;
class	OneListData
{
private:
	String		m_ManageItem;
	String	   	m_Tag;
	//对于自动保持列表来讲: 0-一直保持 1-走路时保持 2-战斗时保持
	String		m_ManageMinCount;			//预留N组
	
friend AutoManageList;
protected:
	void		LoadSaveString(String iniStr);
	String 		OutPutString();
	void		Init(String item, int tag, int count);
	void		InitStr(String item, String tag, String count);
	void		ReadData(OneListData * other);	

public:
	//对于自动保持列表来讲
	//m_ManageItem: 使用技能      m_Tag:间隔       m_ManageMinCount:使用方式
	String		GetManageItem(){return	m_ManageItem;}
	int			GetManageItemInt(){return	m_ManageItem.ToIntDef(0);}
	int			GetTag(){return	m_Tag.ToIntDef(0);}
	int			GetManageMinCount(){return	m_ManageMinCount.ToIntDef(0);}
	String		GetTagStr(){return	m_Tag;}
	String	  	GetManageMinCountStr(){return	m_ManageMinCount;}

	int			GetManageMinCountHi();
	int			GetManageMinCountLo();

	int			GetTagHi();
	int			GetTagLo();

public:
	OneListData()
	{
	}
	~OneListData(){}

};

class	AutoManageList
{
private:
	TStringList * 			m_StringList;
	AList<OneListData>		m_ListData;
	TListItems * 			m_ListGui;
	TValueListEditor * 		m_ValueListGUI;
	String					m_IndexName;
	TAutoManage				m_Index;

	String					MakeListToString(TStringList * destList);

	friend 					AutoManageListConfig;

	String					GetTagString(String tag);
	String					GetCountString(int count);
	
	bool					m_bItemLoaded;
	int						m_RefreshType;

	String					GetDataGuiCaption(OneListData * data);
	String					GetDataGuiText(OneListData * data);
	String					GetDataGuiText2(OneListData * data);
	void					AddGuiItem(OneListData * data);
	bool					IsItem();		//检查这个列表处理的是不是物品
	
protected:
	//读取ini
	void			LoadFromIni(TMemIniFile * IniFile,const String &SecName);

	//保存ini
	void			SaveToIni(TMemIniFile * IniFile, String RecordName);

	void			EditModifyView(int index, OneListData * curData);
public:
	//refreshType : 0 普通  1 4列,需要用联合体
	AutoManageList(String indexName, TAutoManage am, int refreshType=0);
	~AutoManageList();
	//绑定界面
	void			Bind(TListItems * GuiList);
	void			Bind(TValueListEditor * valueListEditor);
	void			RefreshGUI();
	void			Delete(int index);
	void			Clear();
	void			Add(String item, int tag=0, int count=0);
	void			Add(String item, WORD tagHi, WORD tagLo, int count);
	void			AddStr(String item, String tag="", String count="");
	void			Edit(int index, String item, int tag=0, int count=0);
    void			Edit(int index, String item, WORD tagHi, WORD tagLo, int count);
	void			EditStr(int index, String item, String tag="", String count="");
	bool			IsExist(String item);
	OneListData	*	At(int index);
	OneListData	*	Find(String item);
	int				IndexOf(String item);
	int				Count(){return m_ListData.Count();}
	TAutoManage		GetIndex(){return m_Index;}
	void			LoadSetting(AutoManageList * other);

	void			MoveUp(int index);
	void			MoveDown(int index);
};

class AutoManageListConfig
{
private:
	AList<AutoManageList>	m_ManageList;

public:
	AutoManageListConfig();
	~AutoManageListConfig();

	//读取ini
	void			LoadFromIni(TMemIniFile * IniFile,const String &SecName);
	//保存ini
	void			SaveToIni(TMemIniFile * IniFile, String RecordName);

	AutoManageList *	GetDefStringList(TAutoManage am);
};

//================================================================================
#define			MAX_CHANNEL			10

struct	tagChatConfig
{
	TColor	channelColor;
	bool	show;
	tagChatConfig()
	{
		channelColor = clBlack;
		show = true;
	}
};

class HEConfig : public TConfig
{
private:
	AutoManageListConfig		m_AutoManageListConfig;
	tagChatConfig  ChannelColor[MAX_CHANNEL];
	vector<tagPosition>			m_PatrolList;
public:
	__fastcall  HEConfig();
	__fastcall  ~HEConfig();
	bool    LoadFromIni(TMemIniFile * IniFile,const String &SecName);
	bool    LoadFromFile(const String &FileName,const String &SecName);
	
	void    SaveToIni(TMemIniFile * IniFile);
	void    SaveToFile(const String &FileName);


	AutoManageList *	GetDefStringList(TAutoManage am);
	tagChatConfig	GetDefColor(int	ct);
	void			SetDefColor(int ct, tagChatConfig config);
	void			SetDefColor(int ct, TColor color, bool show);
	
	bool    IsListExist(TAutoManage am, DWORD ID);
};

#endif
