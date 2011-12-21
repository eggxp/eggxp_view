//---------------------------------------------------------------------------

#ifndef WOWPacketReviewerH
#define WOWPacketReviewerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <IniFiles.hpp>
#include <Forms.hpp>
#include "WOWProxy.h"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "AList.h"
//#include "Eay32DllLoader.h"
#include <Menus.hpp>
#include "PackageContainer.h"
#include "GameDataViewerFrm.h"
#include "cspin.h"
#include <ToolWin.hpp>
#include <ImgList.hpp>

//---------------------------------------------------------------------------


class TWOWReviewerMainFrm : public TForm
{
__published:	// IDE-managed Components
	TPageControl *pcMainControl;
	TTabSheet *tsSend;
	TTabSheet *tsRecv;
    TTabSheet *TabSheet3;
    TMemo *memOutput;
    TTimer *Timer1;
	TTabSheet *tsAll;
    TPopupMenu *pmAll;
    TMenuItem *miAllCopy;
    TTimer *TimeLogic;
    TSplitter *Splitter1;
    TPanel *Panel1;
    TCheckBox *cbShowHead;
    TComboBox *cbWatchType;
    TCheckBox *cbHandlerPacket;
    TPopupMenu *pmMemo;
    TMenuItem *miCommentCopyAll;
    TMenuItem *miCommentWatch;
    TTabSheet *TabSheet14;
    TButton *btTimeBitToString;
    TEdit *edtInputTimeBit;
    TEdit *edtTimeBitString;
    TEdit *edtUTF8BIN;
    TButton *btUTF8ToAnsi;
    TEdit *edtUTF8Output;
    TEdit *edtFloatToTime;
    TButton *btFloatToTime;
    TEdit *edtFloatToTimeResult;
    TCheckBox *cbShowOrgPack;
    TListView *lvSend;
    TListView *lvRecv;
    TListView *lvAll;
    TPageControl *PageControl2;
    TTabSheet *TabSheet4;
    TTabSheet *TabSheet5;
    TSplitter *Splitter2;
    TGroupBox *GroupBox2;
    TLabel *labSendMsg;
    TComboBox *cbPackHead;
    TButton *btSendToClient;
    TButton *btSendToServer;
    TButton *btParseRecv;
    TButton *btParseSend;
    TMemo *edtSendPack;
    TMemo *memComment;
    TPanel *Panel2;
    TListView *lvPackFilter;
    TCheckBox *cbFilter;
    TCheckBox *cbReverseFilter;
    TComboBox *cbAddFilter;
    TButton *btAddFilter;
    TMenuItem *miAllAddToFilter;
    TButton *btClearFilter;
    TPopupMenu *pmFilter;
    TMenuItem *miDeleteFilter;
    TCheckBox *cbNoRefresh;
    TButton *btShowMaps;
    TButton *btDataViewer;
    TTabSheet *TabSheet6;
    TMemo *memPosInfo;
    TTimer *TimeInfo;
    TTabSheet *TabSheet7;
    TListView *lvMemView;
	TEdit *edtServerMSTimeMuti;
    TButton *btStartAI;
	TButton *btSetServerMSTimeMuti;
    TCSpinEdit *edtVersion;
    TLabel *Label1;
	TButton *btOrgToUTF8;
	TEdit *edtAnsiStr;
	TButton *btAnsiToUTF8Bin;
	TEdit *edtAnsiToUTF8Bin;
	TLabel *labCnt;
	TTabSheet *TabSheet8;
	TListView *lvThread;
	TButton *btUpdateObject;
	TButton *btMapDrawer;
	TEdit *edtTick;
	TEdit *edtFilterGuid;
	TCheckBox *cbFilterAllCreature;
	TTimer *tmCloseFreeRefresh;
	TPopupMenu *pmStartMenu;
	TToolBar *ToolBar1;
	TToolButton *tbClearAll;
	TToolButton *tbBlock;
	TToolButton *tbStartGame;
	TImageList *ImageList1;
	TToolButton *btDock;
	TButton *btReloadResource;
	TTabSheet *TabSheet9;
	TButton *btFlySet;
	TButton *btGameObjectFind;
	TButton *btCreatureFind;
	TButton *btIncSpeed;
	TTabSheet *TabSheet11;
	TMemo *memThreat;
	TTabSheet *TabSheet12;
	TMemo *memMSTimeInfo;
	TButton *btDisconnect;
	TTabSheet *TabSheet13;
	TButton *btDirectModel;
	TEdit *edtFloatCalc;
	TEdit *edtFloatCalcResult;
	TMenuItem *CopyDetail1;
	TMenuItem *CopyLine1;
	TMenuItem *CopyCVS1;
	TButton *btWaterwalking;
	TLabel *labProxyCount;
    TButton *Button1;
    TMenuItem *miCopyToFile;
	TButton *btSaveSpellData;
    void __fastcall FormCreate(TObject *Sender);
    void __fastcall FormDestroy(TObject *Sender);
    void __fastcall Timer1Timer(TObject *Sender);
    void __fastcall lvSendData(TObject *Sender, TListItem *Item);
    void __fastcall lvRecvData(TObject *Sender, TListItem *Item);
    void __fastcall lvAllData(TObject *Sender, TListItem *Item);
    void __fastcall cbWatchTypeSelect(TObject *Sender);
    void __fastcall TimeLogicTimer(TObject *Sender);
    void __fastcall btSendToClientClick(TObject *Sender);
    void __fastcall btSendToServerClick(TObject *Sender);
    void __fastcall cbShowHeadClick(TObject *Sender);
    void __fastcall lvAllClick(TObject *Sender);
    void __fastcall btParseRecvClick(TObject *Sender);
    void __fastcall btParseSendClick(TObject *Sender);
    void __fastcall cbHandlerPacketClick(TObject *Sender);
    void __fastcall miCommentCopyAllClick(TObject *Sender);
    void __fastcall miCommentWatchClick(TObject *Sender);
    void __fastcall btTimeBitToStringClick(TObject *Sender);
    void __fastcall btUTF8ToAnsiClick(TObject *Sender);
    void __fastcall btFloatToTimeClick(TObject *Sender);
    void __fastcall cbShowOrgPackClick(TObject *Sender);
    void __fastcall edtSendPackDblClick(TObject *Sender);
    void __fastcall lvPackFilterData(TObject *Sender, TListItem *Item);
    void __fastcall cbFilterClick(TObject *Sender);
    void __fastcall btAddFilterClick(TObject *Sender);
    void __fastcall miAllAddToFilterClick(TObject *Sender);
    void __fastcall btClearFilterClick(TObject *Sender);
    void __fastcall miDeleteFilterClick(TObject *Sender);
    void __fastcall btShowMapsClick(TObject *Sender);
    void __fastcall btDataViewerClick(TObject *Sender);
    void __fastcall TimeInfoTimer(TObject *Sender);
    void __fastcall lvMemViewData(TObject *Sender, TListItem *Item);
    void __fastcall btStartAIClick(TObject *Sender);
	void __fastcall btOrgToUTF8Click(TObject *Sender);
	void __fastcall btAnsiToUTF8BinClick(TObject *Sender);
	void __fastcall lvThreadData(TObject *Sender, TListItem *Item);
	void __fastcall btUpdateObjectClick(TObject *Sender);
	void __fastcall btMapDrawerClick(TObject *Sender);
	void __fastcall tmCloseFreeRefreshTimer(TObject *Sender);
	void __fastcall tbClearAllClick(TObject *Sender);
	void __fastcall tbBlockClick(TObject *Sender);
	void __fastcall tbStartGameClick(TObject *Sender);
	void __fastcall btDockClick(TObject *Sender);
	void __fastcall btSetServerMSTimeMutiClick(TObject *Sender);
	void __fastcall btCreatureFindClick(TObject *Sender);
	void __fastcall btGameObjectFindClick(TObject *Sender);
	void __fastcall btReloadResourceClick(TObject *Sender);
	void __fastcall btFlySetClick(TObject *Sender);
	void __fastcall btIncSpeedClick(TObject *Sender);
	void __fastcall btDisconnectClick(TObject *Sender);
	void __fastcall btDirectModelClick(TObject *Sender);
	void __fastcall edtFloatCalcChange(TObject *Sender);
	void __fastcall CopyDetail1Click(TObject *Sender);
	void __fastcall CopyLine1Click(TObject *Sender);
	void __fastcall CopyCVS1Click(TObject *Sender);
	void __fastcall btWaterwalkingClick(TObject *Sender);
    void __fastcall Button1Click(TObject *Sender);
    void __fastcall miCopyToFileClick(TObject *Sender);
	void __fastcall btSaveSpellDataClick(TObject *Sender);
private:	// User declarations 

    void            AddParseStr(String mark);
    
    TMemIniFile *       m_MemIniFile;


    //窗体类功能函数
	void 	RestoreWindow();
	void 	MinimizeWindow();

    void                Refresh(int forceRefresh);

    virtual void __fastcall WndProcs(Messages::TMessage &Message);
    PackageContainer        *   GetWatchProxy();


    void                        GetSendPack(WOWPackage  *   pack, String mark);

	void                        AddViewSelectTextToFilter(TListView * lv, AList<WOWPackage> * listData);
	AnsiString                      GetInputData();
	HANDLE                      FindWindowFunc(String className);

	void __fastcall miStartMenuClick(TObject *Sender);
	TStringList *				m_ConnectIPList;
	double						m_ServerMSTimeMuti;

	map<int, double>						m_ServerMSTimeMutiSuggest;
	void WriteServerMSTime(int type, String titleName, TStrings *output);

	bool GetVisibleListView(TListView **lv, AList<WOWPackage> **listData);
	void AddMessageToPackage(String msg);
public:		// User declarations
	__fastcall TWOWReviewerMainFrm(TComponent* Owner);

	void	        LogMsg(const String &Msg);
	void            SetCommentText(String text);
};
//---------------------------------------------------------------------------
extern PACKAGE TWOWReviewerMainFrm *WOWReviewerMainFrm;
//---------------------------------------------------------------------------
#endif
