//---------------------------------------------------------------------------

#ifndef GameMapH
#define GameMapH
//---------------------------------------------------------------------------
#include <vcl.h>
#include "CommFunc.h"
#include "Log4Me.h"
#include "SharedDefine.h"
#include "AList.h"
#include "DBCFmt.h"
#include "DBCFileLoader.h"
#include "DBCStructure.h"

#pragma pack(push,1)
//******************************************
// Map file format defines
//******************************************
struct map_fileheader
{
    uint32 mapMagic;
    uint32 versionMagic;
//    uint32 buildMagic;                //new in 3.3.2
    uint32 areaMapOffset;
    uint32 areaMapSize;
    uint32 heightMapOffset;
    uint32 heightMapSize;
    uint32 liquidMapOffset;
    uint32 liquidMapSize;
};
struct map_areaHeader
{
    uint32 fourcc;
    uint16 flags;
    uint16 gridArea;
};
struct map_heightHeader
{
    uint32 fourcc;
    uint32 flags;
    float  gridHeight;
    float  gridMaxHeight;
};
struct map_liquidHeader
{
    uint32 fourcc;
    uint16 flags;
    uint16 liquidType;
    uint8  offsetX;
    uint8  offsetY;
    uint8  width;
    uint8  height;
    float  liquidLevel;
};
struct LiquidData
{
    uint32 type;
    float  level;
    float  depth_level;
};

class GridMap
{
    uint32  m_flags;
    // Area data
    uint16  m_gridArea;
    uint16 *m_area_map;
    // Height level data
    float   m_gridHeight;
    float   m_gridIntHeightMultiplier;
    union{
        float  *m_V9;
        uint16 *m_uint16_V9;
        uint8  *m_uint8_V9;
    };
    union{
        float  *m_V8;
        uint16 *m_uint16_V8;
        uint8  *m_uint8_V8;
    };
    // Liquid data
    uint16  m_liquidType;
    uint8   m_liquid_offX;
    uint8   m_liquid_offY;
    uint8   m_liquid_width;
    uint8   m_liquid_height;
    float   m_liquidLevel;
    uint8  *m_liquid_type;
    float  *m_liquid_map;

    bool  loadAreaData(FILE *in, uint32 offset, uint32 size);
    bool  loadHeightData(FILE *in, uint32 offset, uint32 size);
    bool  loadLiquidData(FILE *in, uint32 offset, uint32 size);

    // Get height functions and pointers
    typedef float (GridMap::*pGetHeightPtr) (float x, float y) const;
    pGetHeightPtr m_gridGetHeight;
    float  getHeightFromFloat(float x, float y) const;
    float  getHeightFromUint16(float x, float y) const;
    float  getHeightFromUint8(float x, float y) const;
    float  getHeightFromFlat(float x, float y) const;

public:
    GridMap();
    ~GridMap();
    bool  loadData(char *filaname);
    void  unloadData();

    uint16 getArea(float x, float y);
    inline float getHeight(float x, float y) {return (this->*m_gridGetHeight)(x, y);}
    float  getLiquidLevel(float x, float y);
    uint8  getTerrainType(float x, float y);
    ZLiquidStatus getLiquidStatus(float x, float y, float z, uint8 ReqLiquidType, LiquidData *data = 0);
    bool    isflat(){return m_gridGetHeight == &GridMap::getHeightFromFlat;}
    float   getFlatHeight(){return  m_gridHeight;}
};

#pragma pack(pop)



class GameMap
{
private:
    String          m_Path;
    int             m_MapID;
    const MapEntry *      m_MapEntry;
    typedef     vector<GridMap *>      MapGridListType;
    vector<MapGridListType>              m_MapGrids;

    void            LoadMapAndVMap(int gx, int gy);
    void            LoadMap(int gx, int gy);
    void            LoadVMap(int gx, int gy);
public:
    GameMap();
    ~GameMap();

    void        Init(int mapid, String path);
    GridMap *   GetGridMap(int gx, int gy);
};




#endif
