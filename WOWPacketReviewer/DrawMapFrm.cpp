//---------------------------------------------------------------------------

#include <vcl.h>
#include <math.h>
#include <Clipbrd.hpp>
#pragma hdrstop

#include "DrawMapFrm.h"
#include "MapDrawer.h"
#include "SharedMemInfo.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrmDrawMap *FrmDrawMap;
//---------------------------------------------------------------------------

void        TFrmDrawMap::DrawPosToWOWPos(int x, int y, int &outputX, int &outputY)
{
	outputX = -(y + m_Top);
	outputY = -(x + m_Left);
}

void        TFrmDrawMap::WOWPosToDrawPos(int x, int y, int &outputX, int &outputY)
{
	//XY ÊÇ·´µÄ!
	outputX = -y - m_Left;
	outputY = -x - m_Top;
}

float		WOWOToDrawO(float o)
{
	return	-o;
}

void        WOWForward(float x, float y, float o, float size, float &outputX, float &outputY)
{
	outputX = x + size * cos(o);
	outputY = y + size * sin(o);
}

__fastcall TFrmDrawMap::TFrmDrawMap(TComponent* Owner)
	: TForm(Owner)
{
	m_CursorPosX = 0;
	m_CursorPosY = 0;
}
//---------------------------------------------------------------------------

void        TFrmDrawMap::ShowFrm()
{
	this->Show();
	pbMapObj->Repaint();
}

void		TFrmDrawMap::InitMap()
{
	pbMapObj->Width = SIZE_OF_GRIDS;
	pbMapObj->Height = SIZE_OF_GRIDS;
	m_Left = 0;
	m_Top = 0;
}

void		TFrmDrawMap::SetCenterXY(int x, int y)
{
	m_Left = -y - pbMapObj->Width / 2;
	m_Top = -x - pbMapObj->Width / 2;
}

void        TFrmDrawMap::DrawWOWMapObj(String guid, TColor DrawColor, int X, int Y)
{
	int drawX = 0, drawY = 0;
	int size = 3;
	WOWPosToDrawPos(X, Y, drawX, drawY);
	DrawMapObj(pbMapObj->Canvas, DrawColor, drawX, drawY, size, 1);

	tagDrawObjInfo info;
	info.PosX = drawX;
	info.PosY = drawY;
	info.Size = size;
	info.Guid = guid;
	m_DrawObj.push_back(info);
}

void		TFrmDrawMap::DrawSelfPos()
{
	float x = GetGameWorld()->GetDataFloat("self/posx");
	float y = GetGameWorld()->GetDataFloat("self/posy");
	float o = GetGameWorld()->GetDataFloat("self/poso");
	this->SetCenterXY(x, y);
	DrawWOWMapObj(GetGameWorld()->GetSelfGUID(), clYellow, x, y);

	TColor penOldColor = pbMapObj->Canvas->Pen->Color;
	int lineOld = pbMapObj->Canvas->Pen->Width;
	int drawX, drawY;
	WOWPosToDrawPos(x, y, drawX, drawY);
	pbMapObj->Canvas->MoveTo(drawX, drawY);

	o = WOWOToDrawO(o);

	pbMapObj->Canvas->Pen->Color = clRed;
	pbMapObj->Canvas->Pen->Width = 3;
	int size = 8;

	int drawOX, drawOY;
	WOWPosToDrawPos(x, y, drawOX, drawOY);
	drawOX = drawOX + size * sin(o);
	drawOY = drawOY - size * cos(o);

	pbMapObj->Canvas->LineTo(drawOX, drawOY);
	pbMapObj->Canvas->Pen->Color = penOldColor;
	pbMapObj->Canvas->Pen->Width = lineOld;
}

void		TFrmDrawMap::DrawGameObj(shared_ptr<DataObject> obj)
{
	if(obj->GetKeyName() == String(GetGameWorld()->GetSelfGUID()))
		return;
	if(!obj->HaveDataObject("x"))
		return;
	int obj_type_id = obj->GetDataObject("type_id")->AsInt();
	float x = obj->GetDataObject("x")->AsFloat();
	float y = obj->GetDataObject("y")->AsFloat();
	TColor cl = clWhite;
	switch (obj_type_id)
	{
		case TYPEID_UNIT:
			cl = clGray;
			break;
		case TYPEID_GAMEOBJECT:
			cl = clGreen;
			break;
		case TYPEID_PLAYER:
			cl = clGreen;
			break;
	}
	DrawWOWMapObj(obj->GetKeyName(), cl, x, y);
}

void    	TFrmDrawMap::RefreshMap()
{
	m_DrawObj.clear();
	DrawSelfPos();
	shared_ptr<DataObject> world = GetGameWorld()->GetDataByKey("world");
	for(int i=0; i<world->GetChildCount(); i++)
	{
		DrawGameObj(world->GetAt(i));
	}
}

void __fastcall TFrmDrawMap::RefreshTimerTimer(TObject *Sender)
{
	pbMapObj->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TFrmDrawMap::FormCreate(TObject *Sender)
{
//	#ifndef	WOW_FISHER
//	miMove->Visible = false;
//	#endif
	InitMap();
}
//---------------------------------------------------------------------------

void __fastcall TFrmDrawMap::pbMapObjPaint(TObject *Sender)
{
 	RefreshMap();
}
//---------------------------------------------------------------------------
String		TFrmDrawMap::GetPointXYText(int X, int Y, int &maxSize)
{
	maxSize = 0;
	vector<tagDrawObjInfo> hitObj;
	for (DWORD i=0; i<m_DrawObj.size(); i++)
	{
		tagDrawObjInfo *info = &m_DrawObj[i];
		if(X >= info->PosX - info->Size && X <= info->PosX + info->Size &&
			Y >= info->PosY - info->Size && Y <= info->PosY + info->Size)
		{
			hitObj.push_back(m_DrawObj[i]);
		}
	}

	int outputX, outputY;
	DrawPosToWOWPos(X, Y, outputX, outputY);
	String caption = FormatStr("%d,%d", outputX, outputY);
	maxSize = caption.Length();
	for(DWORD i=0; i<hitObj.size(); i++)
	{
		String name = GetGameWorld()->GetDataStr(FormatStr("world/%s/name", hitObj[i].Guid));
		String text = FormatStr("\r\n%s:%s", name, hitObj[i].Guid);
		caption += text;
		if(maxSize < text.Length())
		{
			maxSize = text.Length();
		}
	}
	return caption;
}

void __fastcall TFrmDrawMap::pbMapObjMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
	m_CursorPosX = X;
	m_CursorPosY = Y;

	int TY = Y- sbMap->VertScrollBar->Position;
	int	TX = X - sbMap->HorzScrollBar->Position;

	int textLength = 0;
	m_CurShowText = GetPointXYText(X, Y, textLength);
	textLength = 8 * textLength;
	labMapHint->Caption = m_CurShowText;

	if (TX < sbMap->ClientWidth-textLength)
	{
	  labMapHint->Left  = TX;
	}
	else
	{
	  labMapHint->Left  = TX-textLength;
	}

	if (TY < sbMap->ClientHeight-50)
	{
	  labMapHint->Top  = TY + 20;
	}
	else
	{
	  labMapHint->Top  = TY-20;
	}
}
//---------------------------------------------------------------------------

void __fastcall TFrmDrawMap::pbMapObjMouseEnter(TObject *Sender)
{
	labMapHint->Visible = true;
	labMapHint->Font->Color = clBlack;
}
//---------------------------------------------------------------------------


void __fastcall TFrmDrawMap::pbMapObjMouseLeave(TObject *Sender)
{
	labMapHint->Visible = false;
	labMapHint->Font->Color = clWhite;
}
//---------------------------------------------------------------------------

void __fastcall TFrmDrawMap::miCopyClick(TObject *Sender)
{
	Clipboard()->AsText = m_CurShowText;
}
//---------------------------------------------------------------------------

void __fastcall TFrmDrawMap::miMoveClick(TObject *Sender)
{
//	float x = GetGameWorld()->GetDataFloat("self/posx");
//	float y = GetGameWorld()->GetDataFloat("self/posy");
//	float z = GetGameWorld()->GetDataFloat("self/posz");
//	float o = GetGameWorld()->GetDataFloat("self/poso");
//
//	GetGameWorld()->GetPackSender()->SendMovementBoth(MSG_MOVE_START_FORWARD,
//		GetGameWorld()->GetSelfGUID(), MOVEFLAG_FORWARD, 0, GetWowTick(),
//		x, y, z, o, 0);
//
//	float outputX, outputY;
//	WOWForward(x, y, o, 2, outputX, outputY);
//	GetGameWorld()->GetPackSender()->SendMovementBoth(MSG_MOVE_STOP,
//		GetGameWorld()->GetSelfGUID(), 0, 0, GetWowTick() + 200,
//		outputX, outputY, z+20, o, 0);
}
//---------------------------------------------------------------------------

