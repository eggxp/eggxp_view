//---------------------------------------------------------------------------

#include <windows.h>
#pragma hdrstop

#include "ReviewerCommon.h"
#include "GameWorld.h"
//---------------------------------------------------------------------------

#pragma package(smart_init)


static uint32 gWOWInitTick = 0;
static uint32 gSelfInitTick = 0;

String GetListEnumName(const char * name_list[], int code, int max)
{
    if(code > max)
        return  "Error";
    return      name_list[code];
}

void            BeautifulHex(AnsiString binData, TStrings * output)
{
    String result = BinToStr(binData.c_str(), binData.Length());
    int pos = 0;
    while(result.Length() - pos >= SPLIT_LEN)
	{
		output->Add(FormatString("\"%s\"", String(result.c_str() + pos, SPLIT_LEN).c_str()));
        pos += SPLIT_LEN;
    }
    if(result.Length() - pos > 0)
    {
        output->Add(FormatString("\"%s\"", String(result.c_str() + pos, result.Length() - pos)));
    }
}

TDateTime  TimeBitToDateTime(DWORD   timebit)
{
    DWORD year_mask = 0xFF000000;
    DWORD mon_mask  = 0x00F00000;
    DWORD mday_mask = 0x000FC000;
    DWORD wday_mask = 0x00003800;
    DWORD hour_mask = 0x000007C0;
    DWORD min_mask  = 0x0000003F;

    int year = ((timebit & year_mask) >> 24) + 2000;
    int mon = ((timebit & mon_mask) >> 20) + 1;
    int mday = ((timebit & mday_mask) >> 14) + 1;
    int wday = (timebit & wday_mask) >> 11;
    int hour = (timebit & hour_mask) >> 6;
	int min  = (timebit & min_mask);

	TDateTime rv;
	rv = TDateTime(year, mon, mday);
	rv += TDateTime(hour, min, 0, 0);

    return  rv;
}

String  TimeBitToString(DWORD   timebit)
{
    DWORD year_mask = 0xFF000000;
    DWORD mon_mask  = 0x00F00000;
    DWORD mday_mask = 0x000FC000;
    DWORD wday_mask = 0x00003800;
    DWORD hour_mask = 0x000007C0;
    DWORD min_mask  = 0x0000003F;

    int year = ((timebit & year_mask) >> 24) + 2000;
    int mon = ((timebit & mon_mask) >> 20) + 1;
    int mday = ((timebit & mday_mask) >> 14) + 1;
    int wday = (timebit & wday_mask) >> 11;
    int hour = (timebit & hour_mask) >> 6;
	int min  = (timebit & min_mask);

    return  FormatString("%d-%d-%d(week:%d)%d:%d", year, mon, mday, wday, hour, min);
}

uint32			GetWowTick()
{
	if(gWOWInitTick == 0)
	{
		return	timeGetTime() * 1.002f;
	}

	return	(timeGetTime() - gSelfInitTick + gWOWInitTick) * 1.002f;
}

void			SetWowInitTick(uint32 tick)
{
	gWOWInitTick = tick;
	gSelfInitTick = timeGetTime();
}

uint32			GetWowInitTick()
{
	return	gWOWInitTick;
}
