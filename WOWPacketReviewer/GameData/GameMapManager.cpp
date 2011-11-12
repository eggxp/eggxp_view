//---------------------------------------------------------------------------


#pragma hdrstop

#include "GameMapManager.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

GameMapManager::GameMapManager()
{
}

GameMapManager::~GameMapManager()
{
}

void                GameMapManager::Init(String path)
{
    m_Path = path;
}

GameMap *           GameMapManager::GetGameMap(int mapid)
{
    GameMap *    result = m_GameMap.Find(mapid);
    if(result)
        return result;

    result = new GameMap();
    result->Init(mapid, m_Path);
    m_GameMap.Add(mapid, result);
    return  result;
}

int                 GameMapManager::PosToGrix(float pos)
{
    return  32 - pos / SIZE_OF_GRIDS;
}
