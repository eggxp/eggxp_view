//---------------------------------------------------------------------------

#ifndef GameMapManagerH
#define GameMapManagerH
//---------------------------------------------------------------------------
#include "GameMap.h"
#include "AMap.h"

class GameMapManager
{
private:
    String                      m_Path;
    AIndexList<GameMap>         m_GameMap;
         
public:
    GameMapManager();
    ~GameMapManager();
    void                Init(String path);
    GameMap *           GetGameMap(int mapid);
    int                 PosToGrix(float pos);
};

#endif
