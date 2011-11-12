//---------------------------------------------------------------------------

#ifndef WayPointManagerH
#define WayPointManagerH
//---------------------------------------------------------------------------

#include    <vcl.h>
#include    "AList.h"

typedef         bool        (__closure  *   TOnCanMove)(int posX, int posY);

class           WayPointManager
{
private:
    vector<TPoint>      m_WayPoints;
    int                 m_PointIndex;
    
    void                AddMaxSize(int size);
    void                AddPoint(int x, int y);
public:
    WayPointManager();
    ~WayPointManager();
   
    TOnCanMove          fpCanMove;
    //特殊处理, 超出范围会返回NULL
    TPoint      *       At(int index);
    void                Clear();
    int                 WayPointCount();

    //走路
    void                StartMove(int srcX, int srcY, int destX, int destY);

    //生成路点函数
    static      void CALLBACK    LineDDAProc(int X, int Y, LPARAM lpData);
};


#endif
