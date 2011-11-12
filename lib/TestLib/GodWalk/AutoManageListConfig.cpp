//---------------------------------------------------------------------------


#pragma hdrstop

#include "AutoManageListConfig.h"
#include "ShareData.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

//ini存储格式：xxxxxxxx-xxxxxx-xxxxxx
//             物品    -给玩家-预留组
void	OneListData::LoadSaveString(String iniStr)
{
	auto_ptr<TStringList> ValueList(new TStringList());
	SplitStr(iniStr,"-",ValueList.get());


	if(ValueList->Count != 3)
		return;
		
	m_ManageItem = ValueList->Strings[0];
	m_Tag	=	ValueList->Strings[1];
	m_ManageMinCount	=	ValueList->Strings[2];
}

String 	OneListData::OutPutString()
{
	return FormatStr("%s-%s-%s", m_ManageItem, m_Tag, m_ManageMinCount);
}

void	OneListData::Init(String item, int tag, int count)
{
	m_ManageItem = item;
	m_Tag = IntToStr(tag);
	m_ManageMinCount = IntToStr(count);
}

void		OneListData::InitStr(String item, String tag, String count)
{
	m_ManageItem = item;
	m_Tag = tag;
	m_ManageMinCount = count;
}

void		OneListData::ReadData(OneListData * other)
{
	m_ManageItem = other->m_ManageItem;
	m_Tag = other->m_Tag;
	m_ManageMinCount = other->m_ManageMinCount;
}

union		TUnionData
{
	int		Data;
	WORD	Part[2];
};

int			OneListData::GetManageMinCountHi()
{
	int data = m_ManageMinCount.ToInt();
	TUnionData	unionData;
	unionData.Data = data;
	return	unionData.Part[0];
}

int		OneListData::GetManageMinCountLo()
{
	int data = m_ManageMinCount.ToIntDef(0);
	TUnionData	unionData;
	unionData.Data = data;
	return	unionData.Part[1];
}

int			OneListData::GetTagHi()
{
	int data = m_Tag.ToIntDef(0);
	TUnionData	unionData;
	unionData.Data = data;
	return	unionData.Part[0];
}

int			OneListData::GetTagLo()
{
	int data = m_Tag.ToIntDef(0);
	TUnionData	unionData;
	unionData.Data = data;
	return	unionData.Part[1];
}

//==================================================================================

//--------------------------------------------------------------------------------
AutoManageList::AutoManageList(String indexName, TAutoManage am, int refreshType)
{
	m_StringList = new TStringList;
	m_ListGui = NULL;
	m_ValueListGUI = NULL;
	m_IndexName = indexName;
	m_Index = am;
	m_RefreshType = refreshType;

	m_bItemLoaded = false;
}

//--------------------------------------------------------------------------------
AutoManageList::~AutoManageList()
{
	delete m_StringList;
}

//-------------------------------------------------------------------------

//--------------------------------------------------------------------------------
String		AutoManageList::GetTagString(String tag)
{
	String result = tag;
	return result;
}

//--------------------------------------------------------------------------------
String		AutoManageList::GetCountString(int count)
{
	return FormatStr(_DT("预留%d组").c_str(), count);
}

//--------------------------------------------------------------------------------
String		AutoManageList::GetDataGuiCaption(OneListData * data)
{
	int		 id = data->m_ManageItem.ToIntDef(0);

	if(m_Index == amAutoKongfu || m_Index == amFastSkill || m_Index == amLearnKongfuList)
	{
		IWogonRecInterface * curKongfu = GameData()->GetWogonRec(id);
		if(curKongfu == NULL)
			return data->m_ManageItem;

		return TEXT_BIG5(curKongfu->GetName());
	}
	else if(m_Index == amChangeLine)
	{
		return	data->m_ManageItem;
	}
	else if(IsItem())
	{
		IItemObjInterface * itemInterface = GameData()->GetItem(id);
		if(itemInterface == NULL)
			return "";

		return	FormatStr("%s (%d)", TEXT_BIG5(itemInterface->GetName()), id);
	}
	else if(m_Index == amUnAttackNPCType)
	{
		//根据NPC的类型得到NPC的名字
		tagNPCDetail detail;
		if(GameData()->GetNPCDetailByTypeID(id, detail))
		{
			return	FormatStr("%s (%d)", TEXT_BIG5(detail.Name), id);
		}

		return "";
	}
	else if(m_Index == amAutoRepair)
	{
		return	GetEquipNameByIndex(id) + _DT("损坏(耐久小于1)");
	}
	else if(m_Index == amAskTeamPlayer || m_Index == amAccTeamLeader)
	{
		return	data->m_ManageItem;
	}
    else if(m_Index == amAutoPaoTui)
    {
        int itemID = GetPetPaoTuiItemIDByIndex(id);
        IItemObjInterface * itemInterface = GameData()->GetItem(itemID);
		if(itemInterface == NULL)
			return "";

		return	FormatStr("%s (%d)", TEXT_BIG5(itemInterface->GetName()), itemID);
    }

	return	data->m_ManageItem;
}

bool		AutoManageList::IsItem()
{
	if(m_Index == amAutoDropItem || m_Index == amAutoUploadItem || m_Index == amAutoOpenBox ||
		m_Index == amAutoSell || m_Index == amAutoBuy || m_Index == amAutoSaveMoneyHouse ||
		m_Index == amAutoDelivery || m_Index == amAutoGetDelivery || m_Index == amAutoBuyShopItem ||
		m_Index == amAutoSellShopItem || m_Index == amAutoMerge || m_Index == amAutoSearch)
		return true;
	return false;
}

String		AutoManageList::GetDataGuiText(OneListData * data)
{
	if(m_Index == amAutoKongfu)
	{
		return	FormatString(_DT("%d 秒"), data->GetTag());
	}
	else if(m_Index == amAutoRepair)
	{
		IItemObjInterface * itemInterface = GameData()->GetItem(data->GetTag());
		if(itemInterface == NULL)
			return "";

		return	FormatStr("%s (%d)", TEXT_BIG5(itemInterface->GetName()), data->GetTag());
	}
	else	if(m_Index == amAutoSellShopItem || m_Index == amAutoSearch)
	{
		return	GetPriceText(data->GetTag());
	}
	else	if(m_Index == amDaiLianAsk || m_Index == amAccDaiLian)
	{
		int tag = data->GetTag();
		if(tag == 0)
		{
			return	_DT("龙戒和凤戒");
		}
		else	if(tag == 1)
		{
			return	_DT("龙戒");
		}
		else	if(tag == 2)
		{
			return	_DT("凤戒");	
		}
	}

	return	data->GetTagStr();
}

String		AutoManageList::GetDataGuiText2(OneListData * data)
{
	if(m_Index == amAutoKongfu)
	{
		if(data->GetManageMinCount() == 0)
		{
			return _DT("一直保持");
		}
		else if(data->GetManageMinCount() == 1)
		{
			return _DT("走路时保持");
		}
		else if(data->GetManageMinCount() == 2)
		{
			return _DT("战斗时保持");
		}
	}
	if(m_Index == amLearnKongfuList)
	{
		if(data->GetManageMinCount() != 0)
			return _DT("是");
		else
			return _DT("否");
	}
	if(m_Index == amAutoBuyShopItem)
	{
		return	GetPriceText(data->GetManageMinCount());
	}
	return	data->GetManageMinCountStr();
}

void	AutoManageList::AddGuiItem(OneListData * data)
{
	if(m_ListGui)
	{
		if(m_RefreshType == 0)
		{
			TListItem * addItem = m_ListGui->Add();
			addItem->Caption = GetDataGuiCaption(data);
			addItem->SubItems->Add(GetDataGuiText(data));
			addItem->SubItems->Add(GetDataGuiText2(data));
		}
		else if(m_RefreshType == 1)
		{
			TListItem * addItem = m_ListGui->Add();
			addItem->Caption = GetDataGuiCaption(data);
			addItem->SubItems->Add(data->GetTagHi());
			addItem->SubItems->Add(data->GetTagLo());
			addItem->SubItems->Add(GetDataGuiText2(data));
		}
	}
}

//--------------------------------------------------------------------------------
//读取ini
void	AutoManageList::LoadFromIni(TMemIniFile * IniFile,const String &SecName)
{
	m_ListData.Clear();
	SplitStrOld(IniFile->ReadString(SecName,m_IndexName, "") ,",",m_StringList);

	//修补
	for(int i=0; i<m_StringList->Count; i++)
	{
		if(m_StringList->Strings[i] == " " || m_StringList->Strings[i] == "" ||
				m_StringList->Strings[i] == NULL)
			m_StringList->Delete(i);
	}

	//转化为结构体
	OneListData * addData;
	for(int i=0; i<m_StringList->Count; i++)
	{
		addData = new OneListData;
		addData->LoadSaveString(m_StringList->Strings[i]);
		m_ListData.Add(addData);
	}

	if(m_Index == amAutoRepair)
	{
		if(Count() != MAX_EQUIP_COUNT)
		{
            //如果装备最大数据更新了(造型衣服)这里不能Clear, 防止黄金槌变成铁锤
            while(Count() < MAX_EQUIP_COUNT)
            {
                Add(Count(), 36001);		//36001是铁锤, 默认用铁锤修理
            }
            
            if(Count() > MAX_EQUIP_COUNT)
            {
                Clear();
                for(int i=0; i<MAX_EQUIP_COUNT; i++)
                {
                    Add(i, 36001);		//36001是铁锤, 默认用铁锤修理
                }
            }
		}
	}
	else	if(m_Index == amAutoBuy)
	{
//		Add(38007, 1);		//一定要买回城卷		取消此选项
	}

	m_bItemLoaded = true;
}

//-------------------------------------------------------------------------
String  AutoManageList::MakeListToString(TStringList * destList)
{
	String TeamList;
	for (int i = 0; i < destList->Count; i++)
	{
	   if(i ==0)
	   {
		 TeamList =  destList->Strings[i];
	   }
	   else
	   {
		 TeamList =  TeamList + "," +destList->Strings[i];
	   }
	}
	return TeamList;
}

//--------------------------------------------------------------------------------
//保存ini
void	AutoManageList::SaveToIni(TMemIniFile * IniFile, String RecordName)
{
	//输出到列表
	m_StringList->Clear();
	for(int i=0; i<m_ListData.Count(); i++)
	{
		m_StringList->Add(m_ListData[i]->OutPutString());
	}
	IniFile->WriteString(RecordName, m_IndexName,MakeListToString(m_StringList));
}

//--------------------------------------------------------------------------------
//绑定界面
void	AutoManageList::Bind(TListItems * GuiList)
{
		
	m_ListGui = GuiList;

	RefreshGUI();
}

void	AutoManageList::Bind(TValueListEditor * valueListEditor)
{
	m_ValueListGUI = valueListEditor;
	valueListEditor->Strings->Clear();
	String curValue;
	for(int i=0; i<Count(); i++)
	{
		curValue = FormatStr("%s=%s", GetDataGuiCaption(m_ListData[i]),
										GetDataGuiText(m_ListData[i]));
		valueListEditor->Strings->Add(curValue);
		valueListEditor->ItemProps[i]->EditStyle = esEllipsis;
	}
}

void	AutoManageList::RefreshGUI()
{
	if(m_ListGui == NULL)
		return;
	m_ListGui->Clear();

	for(int i = 0; i < m_ListData.Count(); i++)
	{
		AddGuiItem(m_ListData[i]);
	}
}

void	AutoManageList::Delete(int index)
{
    if(index < 0)
        return;
	m_ListData.Delete(index);
	if(m_ListGui)
	{
		m_ListGui->Delete(index);
	}

	if(m_Index == amPatrol)
	{
		//定义巡逻点的时候, 要改变索引
		for(int i=0; i<m_ListData.Count(); i++)
		{
			m_ListData[i]->m_ManageItem = IntToStr(i);
		}
		RefreshGUI();
	}
}

void	AutoManageList::Clear()
{
	m_ListData.Clear();
	if(m_ListGui)
	{
		m_ListGui->Clear();
	}
}

void	AutoManageList::Add(String item, int tag, int count)
{
	if(IsExist(item))
		return;
	OneListData	* addData = new OneListData;
	addData->Init(item, tag, count);
	
	m_ListData.Add(addData);
	AddGuiItem(addData);
}

void	 AutoManageList::Add(String item, WORD tagHi, WORD tagLo, int count)
{
	TUnionData	unData;
	unData.Part[0] = tagHi;
	unData.Part[1] = tagLo;

	Add(item, unData.Data, count);
}

void	AutoManageList::AddStr(String item, String tag, String count)
{
	if(IsExist(item))
		return;
	OneListData	* addData = new OneListData;
	addData->InitStr(item, tag, count);
	
	m_ListData.Add(addData);
	AddGuiItem(addData);
}

void	AutoManageList::EditStr(int index, String item, String tag, String count)
{
	OneListData	* curData = At(index);
	if(curData)
	{
		curData->InitStr(item, tag, count);
	}
	EditModifyView(index, curData);
}

void	AutoManageList::EditModifyView(int index, OneListData * curData)
{
	if(m_ListGui)
	{
		if(index >= 0 && index < m_ListGui->Count)
		{
			TListItem * curItem = m_ListGui->Item[index];
			curItem->Caption = GetDataGuiCaption(curData);
			if(curItem->SubItems->Count == 0)
			{
				curItem->SubItems->Add(GetDataGuiText(curData));
				curItem->SubItems->Add(GetDataGuiText2(curData));
			}
			else if(curItem->SubItems->Count == 1)
			{
				curItem->SubItems->Strings[0] = GetDataGuiText(curData);
				curItem->SubItems->Add(GetDataGuiText2(curData));
			}
            else if(curItem->SubItems->Count == 3)
			{
				curItem->SubItems->Strings[0] = curData->GetTagHi();
				curItem->SubItems->Strings[1] = curData->GetTagLo();
                curItem->SubItems->Strings[2] = GetDataGuiText2(curData);
			}
            else
			{
				curItem->SubItems->Strings[0] = GetDataGuiText(curData);
				curItem->SubItems->Strings[1] = GetDataGuiText2(curData);
			}
		}
	}

	if(m_ValueListGUI)
	{
		if(index >= 0 && index < m_ValueListGUI->Strings->Count)
			m_ValueListGUI->Strings->Strings[index] = FormatStr("%s=%s", GetDataGuiCaption(m_ListData[index]),
										GetDataGuiText(m_ListData[index]));
	}
}

void	AutoManageList::Edit(int index, String item, int tag, int count)
{
	OneListData	* curData = At(index);
	if(curData)
	{
		curData->Init(item, tag, count);
	}
  	EditModifyView(index, curData);
}

void	AutoManageList::Edit(int index, String item, WORD tagHi, WORD tagLo, int count)
{
    OneListData	* curData = At(index);
	if(curData)
	{
        TUnionData	unData;
        unData.Part[0] = tagHi;
        unData.Part[1] = tagLo;
		curData->Init(item, unData.Data, count);
	}
  	EditModifyView(index, curData);
}

int		AutoManageList::IndexOf(String item)
{
	for(int i=0; i<m_ListData.Count(); i++)
	{
		if(m_ListData[i]->m_ManageItem == item)
			return i;
	}
	return -1;
}

bool	AutoManageList::IsExist(String item)
{
	for(int i=0; i<m_ListData.Count(); i++)
	{
		if(m_ListData[i]->m_ManageItem == item)
			return true;
	}

	//特殊处理, 如果是物品的话, 如果这2个物品的名字相同, 那么认为是同一种物品
	if(IsItem())
	{
		IItemObjInterface	*  curItem;
		IItemObjInterface	*  destItem = GameData()->GetItem(item.ToIntDef(0));
		if(destItem == NULL)
			return false;
		for(int i=0; i<m_ListData.Count(); i++)
		{
			curItem = GameData()->GetItem(m_ListData[i]->m_ManageItem.ToIntDef(0));
			if(curItem)
			{
				if(curItem->GetName() == destItem->GetName())
					return true;
			}
		}
	}
	return false;
}

OneListData	*	AutoManageList::At(int index)
{
	return m_ListData[index];
}

OneListData	*	AutoManageList::Find(String item)
{
	for(int i=0; i<m_ListData.Count(); i++)
	{
		if(m_ListData[i]->m_ManageItem == item)
			return m_ListData[i];
	}
	return NULL;
}

void			AutoManageList::LoadSetting(AutoManageList * other)
{
	Clear();
	for(int i=0; i<other->Count(); i++)
	{
		Add(other->At(i)->GetManageItem(), other->At(i)->GetTag(), other->At(i)->GetManageMinCount());
	}
}


void			AutoManageList::MoveUp(int index)
{
	if(index <= 0 || index >= Count())
		return;

	OneListData temp;
	temp.ReadData(At(index-1));
	At(index-1)->ReadData(At(index));
	At(index)->ReadData(&temp);

	RefreshGUI();
}

void			AutoManageList::MoveDown(int index)
{
	if(index < 0 || index >= Count()-1)
		return;

	OneListData temp;
	temp.ReadData(At(index+1));
	At(index+1)->ReadData(At(index));
	At(index)->ReadData(&temp);

	RefreshGUI();
}

//********************************************************************************
//================================================================================


AutoManageListConfig::AutoManageListConfig()
{
	//自动加持
	AutoManageList * list = new AutoManageList("AutoKongfu", amAutoKongfu);
	m_ManageList.Add(list);

	//自动选择分流
	list = new AutoManageList("Patrol", amPatrol);
	m_ManageList.Add(list);

	//自动换线
	list = new AutoManageList("AutoChangeLine2", amChangeLine);
	m_ManageList.Add(list);

	//自动丢弃
	list = new AutoManageList("AutoDrop", amAutoDropItem);
	m_ManageList.Add(list);

	//自动贡献
	list = new AutoManageList("AutoUpload", amAutoUploadItem);
	m_ManageList.Add(list);

	//自动打开/使用
	list = new AutoManageList("AutoOpenOrUse", amAutoOpenBox);
	m_ManageList.Add(list);

	//不主动攻击的怪
	list = new AutoManageList("UnAttackNPC", amUnAttackNPCType);
	m_ManageList.Add(list);

	//自动卖
	list = new AutoManageList("AutoSellItem", amAutoSell);
	m_ManageList.Add(list);
	
	//自动买
	list = new AutoManageList("AutoBuyItem", amAutoBuy);
	m_ManageList.Add(list);

	//自动修理
	list = new AutoManageList("AutoRepairItem", amAutoRepair);
	m_ManageList.Add(list);

	//技能快捷栏
	list = new AutoManageList("FastSkill", amFastSkill);
	m_ManageList.Add(list);

	//自动存钱庄
	list = new AutoManageList("AutoSaveMoneyHouse", amAutoSaveMoneyHouse);
	m_ManageList.Add(list);

	//自动快递给XXX
	list = new AutoManageList("AutoDelivery", amAutoDelivery);
	m_ManageList.Add(list);

	//邀请加入人的列表
	list = new AutoManageList("AskTeamPlayer", amAskTeamPlayer);
	m_ManageList.Add(list);

	//接受加入人的列表
	list = new AutoManageList("AccTeamLeader", amAccTeamLeader);
	m_ManageList.Add(list);

	//自动取物品
	list = new AutoManageList("AutoGetDelivery", amAutoGetDelivery);
	m_ManageList.Add(list);

	//遇到后自动换线的玩家
	list = new AutoManageList("PlayerBlackList", amPlayerBlackList);
	m_ManageList.Add(list);

	//自动习武的习武列表
	list = new AutoManageList("LearnKongfuList", amLearnKongfuList);
	m_ManageList.Add(list);

	//自动买商店物品
	list = new AutoManageList("AutoBuyShopList", amAutoBuyShopItem, 1);
	m_ManageList.Add(list);

	//自动挂商店的列表
	list = new AutoManageList("AutoSellShopItemList", amAutoSellShopItem);
	m_ManageList.Add(list);

	//自动组人
	list = new AutoManageList("AutoTeamStr", amAutoTeamStr);
	m_ManageList.Add(list);

	//自动合成
	list = new AutoManageList("AutoMerge", amAutoMerge);
	m_ManageList.Add(list);

	//黑名单
	list = new AutoManageList("BlackList", amBlackList);
	m_ManageList.Add(list);

	//自定义屏蔽
	list = new AutoManageList("BlockString", amBlockString);
	m_ManageList.Add(list);

	//要求代练的人
	list = new AutoManageList("DaiLianAsk", amDaiLianAsk);
	m_ManageList.Add(list);

	//接受代练的人
	list = new AutoManageList("AccDaiLian", amAccDaiLian);
	m_ManageList.Add(list);

    //宠物跑腿
    list = new AutoManageList("AutoPaoTui", amAutoPaoTui);
	m_ManageList.Add(list);

    //神行淘宝
    list = new AutoManageList("AutoSearch", amAutoSearch);
	m_ManageList.Add(list);

    //不自动组队的成员列表
    list = new AutoManageList("DoNotJoinTeam", amDoNotJoinTeam);
    m_ManageList.Add(list);
}

AutoManageListConfig::~AutoManageListConfig()
{
}

//-------------------------------------------------------------------------
AutoManageList *	AutoManageListConfig::GetDefStringList(TAutoManage am)
{
	for(int i=0; i<m_ManageList.Count(); i++)
	{
		if(m_ManageList[i]->GetIndex() == am)
			return m_ManageList[i];
	}

	return NULL;
}

//-------------------------------------------------------------------------
//读取ini
void	AutoManageListConfig::LoadFromIni(TMemIniFile * IniFile,const String &SecName)
{

	for(int i=0; i<m_ManageList.Count(); i++)
	{
		m_ManageList[i]->LoadFromIni(IniFile, SecName);
	}

}

//---------------------------------------------------------------------------
//得到列表中的文字，用于保存ini
void	AutoManageListConfig::SaveToIni(TMemIniFile * IniFile, String RecordName)
{
	for(int i=0; i<m_ManageList.Count(); i++)
	{
		m_ManageList[i]->SaveToIni(IniFile, RecordName);
	}

}

//---------------------------------------------------------------------------

//============================================================================
__fastcall HEConfig::HEConfig()
{
	ChannelColor[0].channelColor = clMaroon;
	ChannelColor[1].channelColor = clBlack;
	ChannelColor[2].channelColor =clGreen;
	ChannelColor[3].channelColor =clPurple;
	ChannelColor[4].channelColor =clRed;
	ChannelColor[5].channelColor =clTeal;
	ChannelColor[6].channelColor =clFuchsia;
	ChannelColor[7].channelColor =clMaroon;
	ChannelColor[8].channelColor =clNavy;
	ChannelColor[9].channelColor =clLime;
}
//---------------------------------------------------------------------------
__fastcall HEConfig::~HEConfig()
{
}
//---------------------------------------------------------------------------
bool    HEConfig::LoadFromIni(TMemIniFile * IniFile,const String &SecName)
{
	TConfig::LoadFromIni(IniFile,SecName);

	for (int i = 0; i <  MAX_CHANNEL; i++)
	{
		ChannelColor[i].channelColor = (TColor)IniFile->ReadInteger(SecName,FormatStr("Channel_%d",i),ChannelColor[i].channelColor);
	}

	for (int i = 0; i <  MAX_CHANNEL; i++)
	{
		ChannelColor[i].show = (bool)IniFile->ReadInteger(SecName,FormatStr("ShowChannel_%d",i),ChannelColor[i].show);
	}
	
	m_AutoManageListConfig.LoadFromIni(IniFile, SecName);
	return true;
}

//---------------------------------------------------------------------------
bool    HEConfig::LoadFromFile(const String &FileName,const String &SecName)
{
	if (!FileExists(FileName))
	{
		return false;
	}

   auto_ptr<TMemIniFile> IniFile(new TMemIniFile(FileName));
   return LoadFromIni(IniFile.get(),SecName);
}

//---------------------------------------------------------------------------
void    HEConfig::SaveToFile(const String &FileName)
{
	auto_ptr<TMemIniFile> IniFile(new TMemIniFile(FileName));
	SaveToIni(IniFile.get());
}
//---------------------------------------------------------------------------
void    HEConfig::SaveToIni(TMemIniFile * IniFile)
{
	TConfig::SaveToIni(IniFile);

	for (int i = 0; i <  MAX_CHANNEL; i++)
	{
	   IniFile->WriteInteger(this->GetRecordName(),FormatStr("Channel_%d",i),(int)ChannelColor[i].channelColor);
	}
	for (int i = 0; i <  MAX_CHANNEL; i++)
	{
	   IniFile->WriteInteger(this->GetRecordName(),FormatStr("ShowChannel_%d",i),(int)ChannelColor[i].show);
	}
	
	m_AutoManageListConfig.SaveToIni(IniFile, this->GetRecordName());
	IniFile->UpdateFile();

}



AutoManageList *	HEConfig::GetDefStringList(TAutoManage am)
{
	return m_AutoManageListConfig.GetDefStringList(am);
}
//
//---------------------------------------------------------------------------
bool    HEConfig::IsListExist(TAutoManage am, DWORD ID)
{
	AutoManageList * autoList = m_AutoManageListConfig.GetDefStringList(am); 
	return autoList->IsExist(ID);
}

tagChatConfig	HEConfig::GetDefColor(int	ct)
{
	if(ct > 1 && ct < MAX_CHANNEL)
		return	ChannelColor[ct-1];
	tagChatConfig defConfig;
	return	defConfig;
}

void	HEConfig::SetDefColor(int ct, tagChatConfig config)
{
	if(ct > 1 && ct < MAX_CHANNEL)
		ChannelColor[ct-1] = config;
}

void	HEConfig::SetDefColor(int ct, TColor color, bool show)
{
	tagChatConfig curColor;
	curColor.channelColor = color;
	curColor.show = show;

	SetDefColor(ct, curColor);
}
