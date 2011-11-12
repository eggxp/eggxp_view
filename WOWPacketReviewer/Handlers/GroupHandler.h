//---------------------------------------------------------------------------

#ifndef GroupHandlerH
#define GroupHandlerH
//---------------------------------------------------------------------------


#include "Opcodes.h"
#include "PackageCommon.h"

class GameWorld;
class GroupHandler
{
private:
    GameWorld   *       m_GameWorld;
    void    Handler_SMSG_GROUP_LIST(WOWPackage * packet);
    void    Handler_SMSG_PARTY_MEMBER_STATS(WOWPackage * packet);
    void    Handler_SMSG_PARTY_MEMBER_STATS_FULL(WOWPackage * packet);
    
public:
    GroupHandler(GameWorld * gameworld);
    ~GroupHandler();
};
#endif
