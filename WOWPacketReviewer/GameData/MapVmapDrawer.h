//---------------------------------------------------------------------------

#ifndef MapVmapDrawerH
#define MapVmapDrawerH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "DBCStructure.h"
#include "DBCStores.h"
#include "cgauges.h"

class     GameWorld;

TColor    HeightToRGB(float height);
bool      DBCMapToBitmap(GameWorld * gameworld, Graphics::TBitmap * OutBitmap, const MapEntry  *   entry, int startgx, int startgy, int scale, TCGauge * gauge);

#endif
