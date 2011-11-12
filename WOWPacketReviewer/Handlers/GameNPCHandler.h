//---------------------------------------------------------------------------

#ifndef GameNPCHandlerH
#define GameNPCHandlerH
//---------------------------------------------------------------------------

#include "Opcodes.h"
#include "PackageCommon.h"

class GameWorld;
class GameNPCHandler
{
private:
    GameWorld   *       m_GameWorld;
	void    Handler_SMSG_MONSTER_MOVE(WOWPackage * packet);
	void    Handler_SMSG_CREATURE_QUERY_RESPONSE(WOWPackage * packet);
	void    Handler_SMSG_THREAT_UPDATE(WOWPackage * packet);
	void    Handler_SMSG_HIGHEST_THREAT_UPDATE(WOWPackage * packet);
	void    Handler_SMSG_THREAT_CLEAR(WOWPackage * packet);
    void    Handler_SMSG_PET_SPELLS(WOWPackage * packet);
    void    Handler_SMSG_MIRRORIMAGE_DATA(WOWPackage * packet);
    void    ReadPetActionBarData(WOWPackage * packet, int &pos);
public:
    GameNPCHandler(GameWorld * gameworld);
    ~GameNPCHandler();
};


#endif
