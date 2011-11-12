//---------------------------------------------------------------------------


#pragma hdrstop

#include "WayPointManager.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


WayPointManager::WayPointManager()
{
    AddMaxSize(200);
    m_PointIndex = 0;
    fpCanMove = NULL;
}

WayPointManager::~WayPointManager()
{
}

void                WayPointManager::AddMaxSize(int size)
{
    //设置数组的最大大小
    for(int i=0; i<size; i++)
    {
        TPoint  curPoint;
        curPoint.x = 0;
        curPoint.y = 0;
        m_WayPoints.push_back(curPoint);
    }
}

void                WayPointManager::AddPoint(int x, int y)
{
    if(fpCanMove)
    {
        if(!fpCanMove(x, y))
            return;
    }
    
    if(m_PointIndex == (int)m_WayPoints.size())
    {
        //节点不够, 增加节点
        AddMaxSize(50);
    }

    m_WayPoints[m_PointIndex].x = x;
    m_WayPoints[m_PointIndex].y = y;
    m_PointIndex++;
}

TPoint      *       WayPointManager::At(int index)
{
    if(index >= 0 && index < (int)m_WayPoints.size())
        return  &m_WayPoints[index];
    return NULL;
}

void                WayPointManager::Clear()
{
    ZeroMemory(&m_WayPoints[0], WayPointCount() * sizeof(TPoint));
    m_PointIndex = 0;
}

int                 WayPointManager::WayPointCount()
{
    return  m_PointIndex;
}

void                WayPointManager::StartMove(int srcX, int srcY, int destX, int destY)
{
    Clear();
    LineDDA(srcX, srcY, destX, destY,
		  (LINEDDAPROC) & LineDDAProc,
		  (LPARAM) this);
    AddPoint(destX, destY);
}

void CALLBACK       WayPointManager::LineDDAProc(int X, int Y, LPARAM lpData)
{
    WayPointManager  * this_Ptr = (WayPointManager *)lpData;
    this_Ptr->AddPoint(X, Y);
}
