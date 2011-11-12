//---------------------------------------------------------------------------

#ifndef MainH
#define MainH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <AppEvnts.hpp>
#include <XPMan.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <Menus.hpp>
#include <ImgList.hpp>
//---------------------------------------------------------------------------
class WOWPackage;
class WOWProxy;
class SingleThread;
class TWOWFisherMain : public TForm
{
__published:	// IDE-managed Components
	TApplicationEvents *ApplicationEvents1;
	TPanel *Panel1;
	TSplitter *Splitter1;
	TPageControl *PageControl1;
	TTabSheet *TabSheet1;
	TTabSheet *TabSheet2;
	TMemo *memLog;
	TTabSheet *TabSheet3;
	TTimer *Timer1;
	TTrayIcon *TrayIcon1;
	TPopupMenu *pmTray;
	TMenuItem *miCloseWnd;
	TTabSheet *tsDebug;
	TButton *btDebug;
	TButton *btAuth;
	TTimer *RefreshTimer;
	TPopupMenu *pmFishLog;
	TMenuItem *miNoAutoPickup;
	TPopupMenu *pmFishFilter;
	TMenuItem *miDeleteFishFiter;
	TMenuItem *miClearFishFilter;
	TMenuItem *N1;
	TMenuItem *miCopyFishResult;
	TImageList *ImageList1;
	TGroupBox *GroupBox1;
	TListView *lvFishFilter;
	TGroupBox *gbFishResult;
	TListView *lvFishResult;
	TGroupBox *GroupBox3;
	TMemo *Memo1;
	TButton *btVisualCreature;
	TButton *btVisibleObject;
	TButton *btRegister;
	TLabel *labHomeAD;
	TLabel *labTaoBaoBuy;
	TButton *btChat;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormDestroy(TObject *Sender);
	void __fastcall btDebugClick(TObject *Sender);
	void __fastcall Timer1Timer(TObject *Sender);
	void __fastcall ApplicationEvents1Minimize(TObject *Sender);
	void __fastcall TrayIcon1DblClick(TObject *Sender);
	void __fastcall TrayIcon1MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall miCloseWndClick(TObject *Sender);
	void __fastcall btAuthClick(TObject *Sender);
	void __fastcall btRegisterClick(TObject *Sender);
	void __fastcall lvFishResultData(TObject *Sender, TListItem *Item);
	void __fastcall lvFishFilterData(TObject *Sender, TListItem *Item);
	void __fastcall RefreshTimerTimer(TObject *Sender);
	void __fastcall miNoAutoPickupClick(TObject *Sender);
	void __fastcall miDeleteFishFiterClick(TObject *Sender);
	void __fastcall miClearFishFilterClick(TObject *Sender);
	void __fastcall miCopyFishResultClick(TObject *Sender);
	void __fastcall btVisualCreatureClick(TObject *Sender);
	void __fastcall btVisibleObjectClick(TObject *Sender);
	void __fastcall labHomeADClick(TObject *Sender);
	void __fastcall labTaoBaoBuyClick(TObject *Sender);
	void __fastcall btChatClick(TObject *Sender);
private:	// User declarations
	bool			m_FrmInited;
	virtual void __fastcall WndProcs(Messages::TMessage &Message);
	void			Refresh();

	void			OnUserAuthPacket(WOWProxy *proxy, WOWPackage *packet);
	void			LogMsg(String msg);
	void			InitDebugFrms();

//	int				TestThread(SingleThread *self);
public:		// User declarations
	__fastcall TWOWFisherMain(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TWOWFisherMain *WOWFisherMain;
//---------------------------------------------------------------------------
#endif
