//---------------------------------------------------------------------------

#ifndef War3RoomHandlerH
#define War3RoomHandlerH
//---------------------------------------------------------------------------
#include "Opcodes.h"
#include "PackageCommon.h"
#include <map>
using namespace std;




class GameWorld;
class War3RoomHandler
{
private:
	GameWorld   *       m_GameWorld;
	void			DecodeStatPacket(WOWPackage *packet);

public:
	War3RoomHandler(GameWorld * gameworld);
	~War3RoomHandler();
	void    Handler_W3GS_GAMEINFO(WOWPackage * packet);
	void    Handler_W3GS_SEARCHGAME(WOWPackage * packet);
	void    Handler_W3GS_REQJOIN(WOWPackage * packet);
	void    Handler_W3GS_SLOTINFOJOIN(WOWPackage * packet);
	void    Handler_W3GS_PLAYERINFO(WOWPackage * packet);
	void    Handler_W3GS_MAPCHECK(WOWPackage * packet);
	void    Handler_W3GS_SLOTINFO(WOWPackage * packet);
	void    Handler_W3GS_MAPSIZE(WOWPackage * packet);
	void    Handler_W3GS_CHAT_FROM_HOST(WOWPackage * packet);
	void    Handler_W3GS_INCOMING_ACTION(WOWPackage * packet);
	void    Handler_W3GS_OUTGOING_ACTION(WOWPackage * packet);
};


#endif
