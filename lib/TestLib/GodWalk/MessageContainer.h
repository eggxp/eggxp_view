//---------------------------------------------------------------------------

#ifndef MessageContainerH
#define MessageContainerH
#include "AList.h"
#include <VCL.h>
#include <ComCtrls.hpp>

//---------------------------------------------------------------------------

enum	IChannelType
{
ctCmd, ctSys, ctGameSys, ctBattle,
//公频, 轻频, 帮频, 友频, 队频, 密频,
ctPublic, ctCur, ctGroup, ctFriend, ctTeam, ctPlayer,
ctGM,ctSysAnswer//自动答题记录
};

String	GetChannelName(IChannelType ct);


struct TInfoRecord
{
  String LogTime;  //时间
  String Info;    //信息
  String Sender;  //发送者
  int    Channel; //信息频道
  String	ChannelName()
  {
  	return	GetChannelName((IChannelType)Channel);
  }
};

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

#define			MAX_CHANNEL			10
#define         MAX_LINE_COUNT      10000

class	MessageContainer
{
private:
	AList<TInfoRecord>		m_Recs;
	TListView		*m_View;
	int				m_MsgType;

    tagChatConfig   m_ChannelColor[MAX_CHANNEL];
    tagChatConfig  *GetDefColor(int index);

	bool			Refresh();
    bool            IsNeedAutoScroll();


	void __fastcall m_ViewCustomDrawItem(TCustomListView *Sender,
			TListItem *Item, TCustomDrawState State, bool &DefaultDraw);
	void __fastcall m_ViewCustomDrawSubItem(TCustomListView *Sender,
			TListItem *Item, int SubItem, TCustomDrawState State,
			bool &DefaultDraw);

	void __fastcall m_ViewData(TObject *Sender, TListItem *Item);

    void            RefreshCurItemText(TListItem *Item, TInfoRecord *InfoRecord);

public:
	MessageContainer();   //0:系统(4列) 1:其他(2列)
	~MessageContainer();
	void			Init(int msgType);
	void			BindControl(TListView * lvView);
	void			Add(int channel, String sender, String info);
	TInfoRecord	*	At(int index){return	m_Recs[index];}
	void			Clear();
	void			SaveToFile(String fileName);
};



#endif
