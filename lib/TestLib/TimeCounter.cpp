//---------------------------------------------------------------------------


#pragma hdrstop

#include "TimeCounter.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

static      TimeCounter         gTimeCounter;

TimeCounter     *   GetTimeCounter()
{
    return      &gTimeCounter;
}
