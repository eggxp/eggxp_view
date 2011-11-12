//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "infotype.h"

String 		 InfoReadToken(String &SrcString, String TokenStr)
{
    String ResultStr;
    int TokenIndex = SrcString.Pos(TokenStr);
    if (TokenIndex == 0)
    {
        ResultStr = SrcString;
        SrcString = "";
        return ResultStr;
    }
    ResultStr = SrcString.SubString(1, TokenIndex - 1);
    SrcString =  SrcString.SubString(TokenIndex + TokenStr.Length(),SrcString.Length());
    return ResultStr;
}
//---------------------------------------------------------------------------
// CPropertiesList class

void			AddPopMenuPopup(TPopupMenu * popupMenu, AList<TBasicAction> * actions)
{
	popupMenu->Items->Clear();

	TMenuItem * curItem;
	for(int i=0; i<actions->Count(); i++)
	{
		curItem = new TMenuItem(popupMenu);
		if(actions->At(i) == NULL)
		{
			//分隔符
			curItem->Caption = "-";
		}
		else
			curItem->Action = actions->At(i);
		popupMenu->Items->Add(curItem);
	}
}

//---------------------------------------------------------------------
String __fastcall InterpretValue(const String &Value, IEngine * Engine)
{
	String aResult, SrcString, QueryValue;
	aResult = "", SrcString = Value;
	while(SrcString.Length())
	{
        aResult += InfoReadToken(SrcString, "<%");
        QueryValue = InfoReadToken(SrcString, "%>");
        if ( QueryValue.Length() )
        {
            if ( QueryValue.Pos(" ") )
				aResult += Engine->DoCommand(QueryValue);
			else
				aResult += Engine->DoCommand(QueryValue);
        }
    }
    return aResult;
}


//---------------------------------------------------------------------
CPropertiesList::CPropertiesList(IEngine *xEngine)
{
    m_xEngine = xEngine;
    m_bDynamicQuery = false;
    m_xRecord = new AList<TPropertiesRecord>(true);
	m_xColumns = new AList<PROPERTIESCOLUMN>(true);
	m_xActions = new AList<TBasicAction>(false);
	m_xValuePrefixList = new TStringList();

	m_Tag = -1;
}
//---------------------------------------------------------------------------
CPropertiesList::CPropertiesList(IEngine *xEngine, const String &aValueCount)
{
    m_xEngine = xEngine;
    m_bDynamicQuery = true;
    m_aValueCount = aValueCount;
    m_xRecord = new AList<TPropertiesRecord>(true);
	m_xColumns = new AList<PROPERTIESCOLUMN>(true);
	m_xActions = new AList<TBasicAction>(false);
	m_xValuePrefixList = new TStringList();

	m_Tag = -1;
}
//---------------------------------------------------------------------------
CPropertiesList::~CPropertiesList()
{
    SAFE_DELETE(m_xRecord);
    SAFE_DELETE(m_xColumns);
	SAFE_DELETE(m_xValuePrefixList);
	SAFE_DELETE(m_xActions);
}
//---------------------------------------------------------------------
void __fastcall		CPropertiesList::AddAction(TBasicAction * action)
{
	m_xActions->Add(action);
}
//---------------------------------------------------------------------

INT __fastcall CPropertiesList::GetCount()
{
	if ( m_bDynamicQuery )
	{
		if(m_aValueCount.ToIntDef(0) == 0)
			return (INT)GetEnginePtr()->DoCommand(m_aValueCount);
		else
			return	m_aValueCount.ToIntDef(0);
	}
    return m_xRecord->Count();
}
//---------------------------------------------------------------------
bool __fastcall CPropertiesList::AddValuePrefix(const String &aValuePrefix)
{
    if ( m_xValuePrefixList )
    {
        m_xValuePrefixList->Add(aValuePrefix);
        return true;
    }
    return false;
}
//---------------------------------------------------------------------
bool __fastcall CPropertiesList::AddProperties(const String &Name, const String &Value)
{
    if ( m_xRecord )
    {
        TPropertiesRecord *pProperties;
        pProperties = new TPropertiesRecord();
        pProperties->Name = Name;
        pProperties->Value = Value;
        m_xRecord->Add(pProperties);
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
bool __fastcall CPropertiesList::AddColumn(const String &Name, INT Width)
{
    if ( m_xColumns )
    {
        PPROPERTIESCOLUMN pPropertiesColumn;
        pPropertiesColumn = new PROPERTIESCOLUMN;
        pPropertiesColumn->Name = Name;
        pPropertiesColumn->Width = Width;
        m_xColumns->Add(pPropertiesColumn);
        return true;
    }
    return false;
}
//---------------------------------------------------------------------------
void __fastcall CPropertiesList::SetColumn(TListView *lvwProperties)
{
    lvwProperties->Columns->Clear();
    for(INT nCnt = 0;nCnt < m_xColumns->Count();nCnt ++)
    {
        TListColumn *pColumn = lvwProperties->Columns->Add();
		PPROPERTIESCOLUMN pPropertiesColumn = m_xColumns->At(nCnt);
        pColumn->Caption = pPropertiesColumn->Name;
        pColumn->Width   = pPropertiesColumn->Width;
    }
}
//---------------------------------------------------------------------------
void __fastcall CPropertiesList::Refresh(TListView *lvwProperties, INT FirstIndex, INT LastIndex)
{
    ListView_SetItemCountEx(lvwProperties->Handle, GetCount(), LVSICF_NOINVALIDATEALL | LVSICF_NOSCROLL);
    if ( FirstIndex == -1 )
        lvwProperties->Repaint();
    else if ( FirstIndex == -2 )
    {
        FirstIndex = lvwProperties->TopItem->Index;
        LastIndex  = FirstIndex + lvwProperties->VisibleRowCount;
    }
    if ( FirstIndex != -1 )
    {
        if ( FirstIndex > lvwProperties->Items->Count - 1 )
            FirstIndex = lvwProperties->Items->Count - 1;
        if ( LastIndex == -1 )
            LastIndex = FirstIndex + 1;
        lvwProperties->UpdateItems(FirstIndex, LastIndex);
    }
}

//---------------------------------------------------------------------------
void __fastcall CPropertiesList::PopMenuPopup(TPopupMenu * popupMenu, int	selItem)
{
	AddPopMenuPopup(popupMenu, m_xActions);
}

//---------------------------------------------------------------------------
void __fastcall CPropertiesList::OnData(TObject *Sender, TListItem *Item, int forceIndex)
{
	int index;
	if(forceIndex != -1)
	{
		index = forceIndex;
	}
	else
		index = Item->Index;

    if ( m_bDynamicQuery )
    {
        String aResult;
		for(INT nCnt = 0;nCnt < m_xValuePrefixList->Count;nCnt ++)
		{
			aResult = GetEnginePtr()->DoCommand("%s %d", m_xValuePrefixList->Strings[nCnt], index);
			if ( nCnt == 0 )
				Item->Caption = aResult;
			else
				Item->SubItems->Add(aResult);
		}
	}
	else
	{
		TPropertiesRecord *pProperties = m_xRecord->At(index);
		if ( pProperties )
		{
			Item->Caption = pProperties->Name;
			String	result = InterpretValue(pProperties->Value, GetEnginePtr());
			Item->SubItems->Add(result);
		}
	}
}
//---------------------------------------------------------------------------

void			CPropertiesList::SetTag(int tag)
{
	m_Tag = tag;
}

//================================================================================

SingleProperty::SingleProperty(IEngine	*	Engine, const String &aValueCount) :	m_Property(Engine, aValueCount),
									m_xActions(false)			
{
	m_Engine = Engine;
	m_HeaderIndex = 1;
}

SingleProperty::SingleProperty(IEngine	*	Engine) :	m_Property(Engine), m_xActions(false)
{
	m_Engine = Engine;
	m_HeaderIndex = 1;
}

void	SingleProperty::OnData(TObject *Sender, TListItem *Item, int forceIndex)
{
	if(m_Header != "")
	{
		//有标题
		if(forceIndex == 0)
		{
			//标题
			if(m_HeaderIndex != 0)
			{
				Item->Caption = "";		//这个字段为ID字段
				Item->SubItems->Add(m_Header);
				if(m_HeaderValue == "")
					Item->SubItems->Add("-");
				else
					Item->SubItems->Add(InterpretValue(m_HeaderValue, m_Engine));
				return;
			}
			else
			{
				Item->Caption = m_Header;		//这个字段为ID字段

				if(m_HeaderValue == "")
					Item->SubItems->Add("-");
				else
					Item->SubItems->Add(InterpretValue(m_HeaderValue, m_Engine));
				return;
			}
		}
		else
		{
			m_Property.OnData(Sender, Item, forceIndex-1);
		}
	}
	else
	{
		//无标题
		m_Property.OnData(Sender, Item, forceIndex);
	}
}

int		SingleProperty::GetCount()
{
	if(m_Header != "")
	{
		return	m_Property.GetCount()+1;
	}
	return	m_Property.GetCount();
}

void	SingleProperty::PopMenuPopup(TPopupMenu * popupMenu)
{
	AddPopMenuPopup(popupMenu, &m_xActions);

}

//================================================================================

CMultiPropertiesList::CMultiPropertiesList(IEngine *xEngine) :
										CPropertiesList(xEngine)
{
	m_ViewStyle = vsSingle;
	m_Engine = xEngine;
	m_Properties = new AList<SingleProperty>;
}

CMultiPropertiesList::~CMultiPropertiesList()
{
	delete	m_Properties;
}

SingleProperty	*	CMultiPropertiesList::AddProperty(const String &aValueCount)
{
	m_ViewStyle = vsMulti;
	SingleProperty	*	curProperty = new SingleProperty(m_Engine, aValueCount);
	m_Properties->Add(curProperty);

	return	curProperty;
}

SingleProperty	*	CMultiPropertiesList::AddProperty()
{
	m_ViewStyle = vsMulti;
	SingleProperty	*	curProperty = new SingleProperty(m_Engine);
	m_Properties->Add(curProperty);

	return	curProperty;
}

SingleProperty		*	CMultiPropertiesList::GetCurSelSec(int index, int& secIndex)
{
	int totalCount=0;
	for(int i=0; i<m_Properties->Count(); i++)
	{
		if(index - totalCount < m_Properties->At(i)->GetCount())
		{
			//找到区间
			secIndex = index-totalCount;
			return	m_Properties->At(i);
		}
		totalCount += m_Properties->At(i)->GetCount();
	}
	return	NULL;
}

void	__fastcall		CMultiPropertiesList::OnData(TObject *Sender, TListItem *Item, int forceIndex)
{
	if(m_ViewStyle == vsSingle)
	{
		CPropertiesList::OnData(Sender, Item, forceIndex);
		return;
	}
	else if(m_ViewStyle == vsMulti)
	{
		int secIndex = 0;
		SingleProperty	*	curProperty = GetCurSelSec(Item->Index, secIndex);
		if(curProperty == NULL)
			return;

		curProperty->OnData(Sender, Item, secIndex);
	}
}

INT __fastcall     CMultiPropertiesList::GetCount()
{
	if(m_ViewStyle == vsSingle)
	{
		return	CPropertiesList::GetCount();
	}
	else
	{
		int TotalCount = 0;
		for(int i=0; i<m_Properties->Count(); i++)
		{
			TotalCount += m_Properties->At(i)->GetCount();
		}
		return	TotalCount;
	}
}

void __fastcall CMultiPropertiesList::PopMenuPopup(TPopupMenu * popupMenu, int	selItem)
{
	if(m_ViewStyle == vsSingle)
	{
		CPropertiesList::PopMenuPopup(popupMenu, selItem);
		return;
	}
	else if(m_ViewStyle == vsMulti)
	{
//		PopMenuPopup;
		int secIndex = 0;
		SingleProperty	*	curProperty = GetCurSelSec(selItem, secIndex);
		if(curProperty == NULL)
			return;

		if(curProperty->m_Header != "" && secIndex == 0)
		{
			//如果选中的是标题头, 那么不绑定
			popupMenu->Items->Clear();
		}
		else
			curProperty->PopMenuPopup(popupMenu);
	}
}

int			CMultiPropertiesList::GetCurSelIndex(int index)
{
	int secIndex = 0;
	SingleProperty	*	curProperty = GetCurSelSec(index, secIndex);
    if(curProperty == NULL)
        return -1;
	if(curProperty->m_Header == "")
		return secIndex;

	return	secIndex-1;
}

int         CMultiPropertiesList::GetCurSelSecIndex(int index)
{
    int totalCount=0;
	for(int i=0; i<m_Properties->Count(); i++)
	{
		if(index - totalCount < m_Properties->At(i)->GetCount())
		{
			//找到区间
			return	i;
		}
		totalCount += m_Properties->At(i)->GetCount();
	}
	return	-1;
}

bool		CMultiPropertiesList::GetHeaderAndSelIndex(int &Headerindex, int &SecIndex, int index)
{
	SingleProperty	*	curProperty = GetCurSelSec(index, SecIndex);
	if(curProperty == NULL)
		return false;
	if(curProperty->m_Header != "")
		SecIndex--;

	for(int i=0; i<m_Properties->Count(); i++)
	{
		if(m_Properties->At(i) == curProperty)
		{
			Headerindex = i;
		}
	}
	return true;
}

