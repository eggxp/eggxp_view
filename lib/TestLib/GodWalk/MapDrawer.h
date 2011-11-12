//---------------------------------------------------------------------------

#ifndef MapDrawerH
#define MapDrawerH
//---------------------------------------------------------------------------

#include    <VCL.h>

void        DrawMapObj(TCanvas * OutPut, TColor DrawColor, int MapX, int MapY, int size, int drawBorder);
void        DrawArea(TCanvas * OutPut, TColor DrawColor, int MapX, int MapY, int Area);

#endif
