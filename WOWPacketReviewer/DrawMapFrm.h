//---------------------------------------------------------------------------

#ifndef DrawMapFrmH
#define DrawMapFrmH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "GameWorld.h"
#include <Menus.hpp>
//---------------------------------------------------------------------------
struct tagDrawObjInfo
{
	int PosX;
	int PosY;
	int Size;
	String Guid;
	tagDrawObjInfo()
	{
		PosX = 0;
		PosY = 0;
		Size = 0;
	}
};

class TFrmDrawMap : public TForm
{
__published:	// IDE-managed Components
	TPanel *Panel1;
	TPanel *Panel2;
	TScrollBox *sbMap;
	TImage *imgPicMap;
	TImage *imgObsMap;
	TPaintBox *pbMapObj;
	TLabel *labMapHint;
	TTimer *RefreshTimer;
	TPopupMenu *PopupMenu1;
	TMenuItem *miCopy;
	TMenuItem *miMove;
	void __fastcall RefreshTimerTimer(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall pbMapObjPaint(TObject *Sender);
	void __fastcall pbMapObjMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall pbMapObjMouseEnter(TObject *Sender);
	void __fastcall pbMapObjMouseLeave(TObject *Sender);
	void __fastcall miCopyClick(TObject *Sender);
	void __fastcall miMoveClick(TObject *Sender);

private:	// User declarations
	int			m_Left;
	int			m_Top;

	void		RefreshMap();
	void		InitMap();
	void        WOWPosToDrawPos(int x, int y, int &outputX, int &outputY);
	void        DrawPosToWOWPos(int x, int y, int &outputX, int &outputY);
	void		SetCenterXY(int x, int y);

	void		DrawSelfPos();
	void		DrawGameObj(shared_ptr<DataObject> obj);

	void        DrawWOWMapObj(String guid, TColor DrawColor, int X, int Y);
	vector<tagDrawObjInfo>	m_DrawObj;
	String		GetPointXYText(int X, int Y, int &maxSize);
	String		m_CurShowText;
	int			m_CursorPosX;
	int			m_CursorPosY;
public:		// User declarations
	__fastcall TFrmDrawMap(TComponent* Owner);
	void        ShowFrm();
};
//---------------------------------------------------------------------------
extern PACKAGE TFrmDrawMap *FrmDrawMap;
//---------------------------------------------------------------------------
#endif
