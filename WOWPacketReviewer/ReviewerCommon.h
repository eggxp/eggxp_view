//---------------------------------------------------------------------------

#ifndef ReviewerCommonH
#define ReviewerCommonH
//---------------------------------------------------------------------------
#include <time.h>
#include <vcl.h>
#include "CommFunc.h"
#include "Log4Me.h"
#include "KOEItlbm.h"
#include <boost/shared_ptr.hpp>
using boost::shared_ptr;


TDateTime  TimeBitToDateTime(DWORD   timebit);


#define         SEND_MARK       "Snd"
#define         RECV_MARK       "Rcv"
#define         CLOSE_MARK      "Close"


String GetListEnumName(const char * name_list[], int code, int max);
#define         READ_TRY_BEGINE try{
#define         READ_TRY_END    }catch(Exception &e){packet->GetComment()->Add(FormatStr("ReadException!:%s", e.Message));return;}

#define         READ_TYPE(TYPE, NAME, READ_FUNC)        \
                if(pos >= packet->GetContentLen())  {packet->GetComment()->Add("-------------READ ERROR!------------");return;} \
                pos_info = FormatStr("[#%d]", pos);     \
                TYPE    NAME = READ_FUNC(packet->GetContent(), pos);    \
                if(String(#READ_FUNC) == "ReadUINT64") packet->AddComment(FormatStr("%s%s_%s(%s)", pos_info, __TEXT(#NAME), _TEXT(#READ_FUNC), GetGUIDInfo(NAME)), NAME);    \
                else if(String(#READ_FUNC) == "ReadFloat") packet->AddComment(FormatStr("%s%s_%s", pos_info, __TEXT(#NAME), _TEXT(#READ_FUNC)), FloatToStr(NAME));\
                else packet->AddComment(FormatStr("%s%s_%s", pos_info, __TEXT(#NAME), _TEXT(#READ_FUNC)), NAME);   \

#define         READ_GUID(NAME)        \
                if(pos >= packet->GetContentLen())  {packet->GetComment()->Add("-------------READ ERROR!------------");return;} \
                pos_info = FormatStr("[#%d]", pos);     \
                uint64    NAME = packet->ReadPackGUID(pos);    \
                packet->AddComment(FormatStr("%s%s_ReadGUID(%s)", pos_info, __TEXT(#NAME), GetGUIDInfo(NAME)), NAME);   \

#define         READ_TIME(NAME)        \
                if(pos >= packet->GetContentLen())  {packet->GetComment()->Add("-------------READ ERROR!------------");return;} \
                pos_info = FormatStr("[#%d]", pos);     \
                long    NAME = ReadDWORD(packet->GetContent(), pos);    \
                packet->AddComment(FormatStr("%s%s(%d)", pos_info, __TEXT(#NAME), NAME), ctime(&NAME));     \

#define         READ_TIMEBIT(NAME)        \
                if(pos >= packet->GetContentLen())  {packet->GetComment()->Add("-------------READ ERROR!------------");return;} \
                pos_info = FormatStr("[#%d]", pos);     \
                DWORD    NAME = ReadDWORD(packet->GetContent(), pos);    \
                packet->AddComment(FormatStr("%s%s(%d)", pos_info, __TEXT(#NAME), NAME), TimeBitToString(NAME));    \

#define         READ_STRING(NAME)		READ_UTF8_STRING(NAME)

#define         READ_UTF8_STRING(NAME)        \
                if(pos >= packet->GetContentLen())  {packet->GetComment()->Add("-------------READ ERROR!------------");return;} \
                pos_info = FormatStr("[#%d]", pos);     \
                String NAME = tlbm_StrUTF8ToAnsi(packet->ReadString(pos));    \
                packet->AddComment(FormatStr("%s%s_ReadString", pos_info, __TEXT(#NAME)), NAME);    \

#define         READ_FOR_TYPE(IT, TYPE, NAME, READ_FUNC)        \
                if(pos >= packet->GetContentLen())  {packet->GetComment()->Add("-------------READ ERROR!------------");return;} \
                pos_info = FormatStr("[#%d]", pos);     \
                TYPE    NAME = READ_FUNC(packet->GetContent(), pos);    \
                packet->AddComment(FormatStr("%s%d_%s_%s", pos_info, IT, __TEXT(#NAME), __TEXT(#READ_FUNC)), NAME); \


#define         READ_BUFF(NAME, LEN)    \
				AnsiString NAME;    \
                if((DWORD)(pos+LEN) > (DWORD)packet->GetContentLen())  {packet->GetComment()->Add("-------------READ ERROR!------------");return;} \
                NAME.SetLength(LEN);    \
                pos_info = FormatStr("[#%d]", pos);     \
                ReadBuf(packet->GetContent(), pos, NAME.c_str(), LEN);  \
                packet->AddComment(FormatStr("%s%s", pos_info, __TEXT(#NAME)), BinToStr(NAME.c_str(), NAME.Length()));   \

#define         READ_FINISH \
                packet->GetComment()->Add("");  \
                packet->GetComment()->Add(FormatStr("-------------FINISH RESULT : pos = %d, len = %d", pos, packet->GetContentLen()));

#define         READ_BYTE(NAME)         READ_TYPE(BYTE, NAME, ReadBYTE)
#define         READ_WORD(NAME)         READ_TYPE(WORD, NAME, ReadWORD)
#define         READ_DWORD(NAME)        READ_TYPE(DWORD, NAME, ReadDWORD)
#define         READ_FLOAT(NAME)        READ_TYPE(float, NAME, ReadFloat)
#define         READ_UINT64(NAME)       READ_TYPE(uint64, NAME, ReadUINT64)



#define     SPLIT_LEN       16*3
void            BeautifulHex(AnsiString binData, TStrings * output);
String          TimeBitToString(DWORD   timebit);

bool            IsAcceptableClientBuild(uint32 build){return true;}

uint32			GetWowTick();
void			SetWowInitTick(uint32 tick);
uint32			GetWowInitTick();
#endif
