//---------------------------------------------------------------------------

#ifndef OpcodesH
#define OpcodesH
//---------------------------------------------------------------------------
#include <vcl.h>
#include "ReviewerCommon.h"
#include "FiberContext.h"
#include "FiberCode.h"


/// Player state
enum SessionStatus
{
    STATUS_AUTHED = 0,                                      ///< Player authenticated (_player==NULL, m_playerRecentlyLogout = false or will be reset before handler call, m_GUID have garbage)
    STATUS_LOGGEDIN,                                        ///< Player in game (_player!=NULL, m_GUID == _player->GetGUID(), inWorld())
    STATUS_TRANSFER,                                        ///< Player transferring to another map (_player!=NULL, m_GUID == _player->GetGUID(), !inWorld())
    STATUS_LOGGEDIN_OR_RECENTLY_LOGGEDOUT,                  ///< _player!= NULL or _player==NULL && m_playerRecentlyLogout, m_GUID store last _player guid)
    STATUS_NEVER,                                           ///< Opcode not accepted from client (deprecated or server side only)
    STATUS_UNHANDLED                                        ///< We don' handle this opcode yet
};

class WorldPacket;

//struct OpcodeHandler
//{
//    TCHAR const* name;
//    SessionStatus status;
//};


String LookupOpcodeName(uint16 id);

int LookupOpcodeID(String headStr);

void InitOpcode();

TStringList *GetAllOpcodeNameList();


#endif
