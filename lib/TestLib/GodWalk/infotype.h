//---------------------------------------------------------------------------
#ifndef infotypeH
#define infotypeH

#include "alist.h"
#include "BaseEngine.h"
//---------------------------------------------------------------------------
class TPropertiesRecord
{
public:
    String                      Name;
    String                      Value;

public:
    __fastcall                  TPropertiesRecord(){Name=""; Value="";}
    __fastcall                  ~TPropertiesRecord(){}
};
//---------------------------------------------------------------------------
typedef struct tagPROPERTIESCOLUMN
{
    String                      Name;
    INT                         Width;
}PROPERTIESCOLUMN, *PPROPERTIESCOLUMN;
//---------------------------------------------------------------------------
class CPropertiesList
{
private:
    IEngine    		           *m_xEngine;
	AList<TPropertiesRecord>   *m_xRecord;
	AList<PROPERTIESCOLUMN>    *m_xColumns;
   	AList<TBasicAction>		   *m_xActions;

    String                      m_aValueCount;
    TStringList                *m_xValuePrefixList;
	BOOL                        m_bDynamicQuery;

	int							m_Tag;

public:
	CPropertiesList(IEngine *xEngine);
	CPropertiesList(IEngine *xEngine, const String &aValueCount);
	virtual                     ~CPropertiesList();
//  	virtual	void				OnMouseDown(TListView * list);
	virtual INT __fastcall      GetCount();
	void						SetTag(int tag);
	int							GetTag(){return m_Tag;}
	virtual bool __fastcall     AddValuePrefix(const String &aValuePrefix);
	virtual bool __fastcall     AddProperties(const String &Name, const String &Value);
	virtual bool __fastcall     AddColumn(const String &Name, INT Width);
	virtual void __fastcall		AddAction(TBasicAction * action);

	virtual void __fastcall     SetColumn(TListView *lvwProperties);
	virtual void __fastcall     Refresh(TListView *lvwProperties, INT FirstIndex = -1, INT LastIndex = -1);
	virtual void __fastcall     OnData(TObject *Sender, TListItem *Item, int forceIndex = -1);
	virtual IEngine * WINAPI GetEnginePtr()                              { return m_xEngine; }

	virtual	void __fastcall 	PopMenuPopup(TPopupMenu * popupMenu, int	selItem);//ÓÒ¼üµ¯³öÏûÏ¢

};


/////////////////////////////////////////////////

//================================================================================
class	CMultiPropertiesList;

class	SingleProperty
{
private:
	IEngine					*m_Engine;
public:
	String					m_Header;
	int						m_HeaderIndex;
	String					m_HeaderValue;
	CPropertiesList			m_Property;
	AList<TBasicAction>		m_xActions;

friend	CMultiPropertiesList;
protected:
	SingleProperty(IEngine	*	Engine, const String &aValueCount);
	SingleProperty(IEngine	*	Engine);
public:
	~SingleProperty(){}
	void			OnData(TObject *Sender, TListItem *Item, int forceIndex);
	void			PopMenuPopup(TPopupMenu * popupMenu);
	int				GetCount();
};
//================================================================================

enum	tagViewStyle
{
	vsSingle, vsMulti
};

class	CMultiPropertiesList : public	CPropertiesList
{
private:
	AList<SingleProperty>			*m_Properties;
	tagViewStyle					m_ViewStyle;
	IEngine							*m_Engine;

	SingleProperty		*			GetCurSelSec(int index, int& secIndex);
public:                                    
	virtual void __fastcall     OnData(TObject *Sender, TListItem *Item, int forceIndex = -1);


	CMultiPropertiesList(IEngine *xEngine);
	~CMultiPropertiesList();

	SingleProperty	*				AddProperty(const String &aValueCount);
	SingleProperty	*				AddProperty();

	virtual INT __fastcall      GetCount();

	virtual	void __fastcall PopMenuPopup(TPopupMenu * popupMenu, int	selItem);

	int						GetCurSelIndex(int index);
    int                     GetCurSelSecIndex(int index);
	bool					GetHeaderAndSelIndex(int &Headerindex, int &SecIndex, int index);
};



//---------------------------------------------------------------------------
#endif
