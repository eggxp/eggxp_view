//---------------------------------------------------------------------------

#ifndef GameObjectHandlerH
#define GameObjectHandlerH
//---------------------------------------------------------------------------
#include "Opcodes.h"
#include "PackageCommon.h"

struct tagUpdateObjectValueResult
{
	int Type;
	DWORD Value;
	int Pos;
	tagUpdateObjectValueResult()
	{
		memset(this, 0, sizeof(*this));
	}
	operator < (tagUpdateObjectValueResult &other)
	{
		return Type < other.Type;
	}
	operator > (tagUpdateObjectValueResult &other)
	{
		return Type > other.Type;
	}
};

String  GetDWORDInfo(int objtypeid, int index, BYTE * content);
String  FindFieldName(int objtypeid, int index);

struct tagUpdateObjectValuesResult
{
	String	BlockName;
	int ValuePosStart;
	int ValuePosEnd;
	int ObjTypeID;
	int MaskSize;
	int MaskPos;
	vector<tagUpdateObjectValueResult>  Values;
	tagUpdateObjectValuesResult()
	{
		Clear();
	}
	void Clear()
	{
		BlockName = "";
		ValuePosStart = 0;
		ValuePosEnd = 0;
		ObjTypeID = 0;
		MaskSize = 0;
		MaskPos = 0;
		Values.clear();
	}
};

class GameWorld;
class GameObjectHandler
{
private:
    GameWorld   *       m_GameWorld;
    void                Handler_SMSG_COMPRESSED_UPDATE_OBJECT(WOWPackage * packet);
    void                Handler_SMSG_UPDATE_OBJECT(WOWPackage * packet);
    void                Handler_SMSG_NAME_QUERY_RESPONSE(WOWPackage * packet);
    void                Handler_SMSG_GAMEOBJECT_SPAWN_ANIM_OBSOLETE(WOWPackage * packet);
    void                Handler_SMSG_GAMEOBJECT_DESPAWN_ANIM(WOWPackage * packet);
    void                Handler_SMSG_GAMEOBJECT_CUSTOM_ANIM(WOWPackage * packet);
    void                Handler_SMSG_CRITERIA_UPDATE(WOWPackage * packet);
    void                Handler_SMSG_ALL_ACHIEVEMENT_DATA(WOWPackage * packet);
	void                Handler_SMSG_RESPOND_INSPECT_ACHIEVEMENTS(WOWPackage * packet);
	void                Handler_SMSG_DESTROY_OBJECT(WOWPackage * packet);

    void                ProcessUpdateObject(WOWPackage * packet);
    void                ReadMovementUpdate(uint64 guid, WOWPackage * packet, int &pos);
    void                ReadValuesUpdate(int objtypeid, uint64 guid, WOWPackage * packet, int &pos, tagUpdateObjectValuesResult *curResult);
	void                ReadAllDataPacket(WOWPackage * packet, int &pos);

	vector<tagUpdateObjectValuesResult> m_UpdateValueResults;
public:
	GameObjectHandler(GameWorld * gameworld);
	~GameObjectHandler();
	vector<tagUpdateObjectValuesResult> GetUpdateValueResults(){return m_UpdateValueResults;}
};

#endif
