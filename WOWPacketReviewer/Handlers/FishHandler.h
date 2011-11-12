//---------------------------------------------------------------------------

#ifndef FishHandlerH
#define FishHandlerH
//---------------------------------------------------------------------------

#include "Opcodes.h"
#include "PackageCommon.h"

class GameWorld;
class FishHandler
{
private:
    GameWorld   *       m_GameWorld;
    void    Handler_SMSG_FISH_NOT_HOOKED(WOWPackage * packet);
public:
    FishHandler(GameWorld * gameworld);
    ~FishHandler();
};

#endif
