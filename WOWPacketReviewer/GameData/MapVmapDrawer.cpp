//---------------------------------------------------------------------------


#pragma hdrstop

#include "MapVmapDrawer.h"
#include "GameMap.h"
#include "GameWorld.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

#define MAX_SHOW_HEIGHT 500
#define MIN_SHOW_HEIGHT -100
// #define BYTE_MAX    255

bool        DBCMapToBitmap(GameWorld * gameworld, Graphics::TBitmap * OutBitmap, const MapEntry  *   entry, int startgx, int startgy, int scale, TCGauge * gauge)
{
    const MapEntry * curMapEntry = entry;
    if(!curMapEntry)
        return false;

    GameMap * curGameMap = gameworld->GetGameMapManager()->GetGameMap(curMapEntry->MapID);
    if(!curGameMap)
        return false;

    if(startgx == -1 || startgy == -1)
        return false;


    TColor color;
    int gx=0;
    int gy=0;
    int split = OutBitmap->Height / 50;
    if(split == 0)
        split = 1; 
    gauge->MaxValue = OutBitmap->Height / split;
    float scalesize = SIZE_OF_GRIDS / scale;
    for(int i = 0;i < OutBitmap->Height; i++)
    {
        if(i % split == 0)
        {
            gauge->Progress = i / split;
            Application->ProcessMessages();
        }
        for(int j = 0;j < OutBitmap->Width; j++)
        {
            gx = startgx + int(i / scalesize);
            gy = startgy + int(j / scalesize);
            GridMap * curGridMap = curGameMap->GetGridMap(gx, gy);
            if(!curGridMap)
            {
                int topos = min((int)(j+scalesize+1), OutBitmap->Width);
                OutBitmap->Canvas->Pen->Color = clWhite;
                OutBitmap->Canvas->MoveTo(j, i);
                OutBitmap->Canvas->LineTo(topos, i);
                j = topos - 1;
                continue;
            }
            if(curGridMap->isflat())
            {
                int topos = min((int)(j+scalesize+1), OutBitmap->Width);
                OutBitmap->Canvas->Pen->Color = HeightToRGB(curGridMap->getFlatHeight());
                OutBitmap->Canvas->MoveTo(j, i);
                OutBitmap->Canvas->LineTo(topos, i);
                j = topos - 1;
                continue;
            }
            float x = (32 - gx) * scalesize - (i / scalesize - int(i / scalesize)) * scalesize;
            float y = (32 - gy) * scalesize - (j / scalesize - int(j / scalesize)) * scalesize;
            x = x * scale;
            y = y * scale;
            float h = curGridMap->getHeight(x, y);
            OutBitmap->Canvas->Pixels[j][i] = HeightToRGB(h);
        }
    }
    gauge->Progress = gauge->MaxValue;
    return  true;
}

TColor    HeightToRGB(float h)
{
    if(h > MAX_SHOW_HEIGHT)
        h = MAX_SHOW_HEIGHT;
    if(h < MIN_SHOW_HEIGHT)
        h = MIN_SHOW_HEIGHT;
    int value = 0;
    TColor color;
    if(h > 0)
    {
        value = h / MAX_SHOW_HEIGHT * (BYTE_MAX * 2);
        if(value < BYTE_MAX)
        {
            color = RGB2Color(value, BYTE_MAX, 0);
        }
        else
        {
            color = RGB2Color(BYTE_MAX, BYTE_MAX * 2 - value, 0);
        }
    }
    else
    {
        value = h / MIN_SHOW_HEIGHT * (BYTE_MAX * 2);
        if(value < BYTE_MAX)
        {
            color = RGB2Color(0, BYTE_MAX, value);
        }
        else
        {
            color = RGB2Color(0, BYTE_MAX * 2 - value, BYTE_MAX);
        }
    }
    return  color;
}
