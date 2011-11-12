//---------------------------------------------------------------------------

#ifndef EventHandlerH
#define EventHandlerH
//---------------------------------------------------------------------------

#include "Opcodes.h"
#include "PackageCommon.h"

class GameWorld;
class EventHandler
{
private:
    GameWorld   *       m_GameWorld;
	void    Handler_SMSG_GOSSIP_MESSAGE(WOWPackage * packet);
	void    Handler_SMSG_NPC_TEXT_UPDATE(WOWPackage * packet);
	void    Handler_SMSG_GOSSIP_POI(WOWPackage * packet);

public:
    EventHandler(GameWorld * gameworld);
    ~EventHandler();
};

#endif
