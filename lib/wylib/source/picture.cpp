//---------------------------------------------------------------------------


#pragma hdrstop

#include "picture.h"


#include <math.h>
#include <algorithm>
using namespace std;

//---------------------------------------------------------------------------

#pragma package(smart_init)
//---------------------------------------------------------------------------
void S_PicXZ(Graphics::TBitmap *Source, Graphics::TBitmap *NewPic, int angle) //
{
  if(angle > 180)
    angle = 360 - angle;
  if(angle < -180)
    angle = 360 + angle;

  float radians = (2 * 3.1416 * angle) / 360;
  float cosine = (float)cos(radians);
  float sine = (float)sin(radians);
  float Point1x = (-Source->Height * sine);
  float Point1y = (Source->Height * cosine);
  float Point2x = (Source->Width * cosine - Source->Height * sine);
  float Point2y = (Source->Height * cosine + Source->Width * sine);
  float Point3x = (Source->Width * cosine);
  float Point3y = (Source->Width * sine);
  float minx = min((float)0, min(Point1x, min(Point2x, Point3x)));
  float miny = min((float)0, min(Point1y, min(Point2y, Point3y)));
  float maxx = max(Point1x, max(Point2x, Point3x));
  float maxy = max(Point1y, max(Point2y, Point3y));
  int   DestBitmapWidth, DestBitmapHeight;
  if(angle > 90 && angle < 180)
    DestBitmapWidth = (int)ceil(-minx);
  else
    DestBitmapWidth = (int)ceil(maxx - minx);
  if(angle > -180 && angle < -90)
    DestBitmapHeight = (int)ceil(-miny);
  else
    DestBitmapHeight = (int)ceil(maxy - miny);
  NewPic->Height = DestBitmapHeight;
  NewPic->Width = DestBitmapWidth;
  for(int x = 0; x < DestBitmapWidth; x++)
  {
    for(int y = 0; y < DestBitmapHeight; y++)
    {
      int SrcBitmapx = (int)((x + minx) * cosine + (y + miny) * sine);
      int SrcBitmapy = (int)((y + miny) * cosine - (x + minx) * sine);
      if(SrcBitmapx >= 0 && SrcBitmapx < Source->Width && SrcBitmapy >= 0 &&
         SrcBitmapy < Source->Height)
      {
        NewPic->Canvas->Pixels[x][y] = Source->Canvas->Pixels[SrcBitmapx][SrcBitmapy];
      }
    }
  }
}