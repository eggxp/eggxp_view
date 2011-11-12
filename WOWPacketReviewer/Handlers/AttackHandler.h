//---------------------------------------------------------------------------

#ifndef AttackHandlerH
#define AttackHandlerH
//---------------------------------------------------------------------------

#include "Opcodes.h"
#include "PackageCommon.h"


class GameWorld;
class AttackHandler
{
private:
    GameWorld           *   m_GameWorld;
    void    Handler_SMSG_ATTACKERSTATEUPDATE(WOWPackage * packet);

public:
    AttackHandler(GameWorld * gameworld);
    ~AttackHandler();

};


#endif
