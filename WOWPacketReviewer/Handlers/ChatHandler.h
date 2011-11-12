//---------------------------------------------------------------------------

#ifndef ChatHandlerH
#define ChatHandlerH
//---------------------------------------------------------------------------

#include "Opcodes.h"
#include "PackageCommon.h"

class GameWorld;
class ChatHandler
{
private:
    GameWorld   *       m_GameWorld;
	void    Handler_CMSG_MESSAGECHAT(WOWPackage * packet);
	void    Handler_SMSG_MESSAGECHAT(WOWPackage * packet);
public:
    ChatHandler(GameWorld * gameworld);
    ~ChatHandler();
};


#endif
