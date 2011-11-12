//---------------------------------------------------------------------------


#pragma hdrstop

#include "MapDrawer.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


void        DrawMapObj(TCanvas * OutPut, TColor DrawColor, int MapX, int MapY, int size, int drawBorder)
{
	int   DrawX, DrawY;

	DrawX = MapX;
	DrawY = MapY;
	int ObjSize = size;
	OutPut->Brush->Style = bsSolid;
	OutPut->Brush->Color = DrawColor;
	TColor penOldColor;
	penOldColor = OutPut->Pen->Color;
	if(!drawBorder)
	{
		OutPut->Pen->Color = DrawColor;
	}

	OutPut->Ellipse(DrawX - ObjSize, DrawY - ObjSize, DrawX + ObjSize, DrawY + ObjSize);
	OutPut->Pen->Color = penOldColor;
}


void            DrawArea(TCanvas * OutPut, TColor DrawColor, int MapX, int MapY, int Area)
{
    TPoint RandPosStart;
    TPoint RandPosEnd;
    RandPosStart.x  =  MapX - Area;
    RandPosStart.y  =  MapY - Area;
    RandPosEnd.x 	=  MapX + Area;
    RandPosEnd.y 	=  MapY + Area;

    OutPut->Brush->Style = bsFDiagonal;
    OutPut->Brush->Color = DrawColor;
    OutPut->Ellipse(RandPosStart.x, RandPosStart.y, RandPosEnd.x, RandPosEnd.y);
}