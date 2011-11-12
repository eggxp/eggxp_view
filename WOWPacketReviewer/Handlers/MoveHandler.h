//---------------------------------------------------------------------------

#ifndef MoveHandlerH
#define MoveHandlerH
//---------------------------------------------------------------------------
#include <map>
#include "Opcodes.h"
#include "PackageCommon.h"
using namespace std;

class GameWorld;
class MoveHandler
{
private:
    GameWorld   *       m_GameWorld;
    void    Handler_MSG_MOVE_START_FORWARD(WOWPackage * packet);
    void    Handler_MSG_MOVE_START_BACKWARD(WOWPackage * packet);
    void    Handler_MSG_MOVE_STOP(WOWPackage * packet);
    void    Handler_MSG_MOVE_START_STRAFE_LEFT(WOWPackage * packet);
    void    Handler_MSG_MOVE_START_STRAFE_RIGHT(WOWPackage * packet);
    void    Handler_MSG_MOVE_STOP_STRAFE(WOWPackage * packet);
    void    Handler_MSG_MOVE_JUMP(WOWPackage * packet);
    void    Handler_MSG_MOVE_START_TURN_LEFT(WOWPackage * packet);
    void    Handler_MSG_MOVE_START_TURN_RIGHT(WOWPackage * packet);
    void    Handler_MSG_MOVE_STOP_TURN(WOWPackage * packet);
    void    Handler_MSG_MOVE_START_PITCH_UP(WOWPackage * packet);
    void    Handler_MSG_MOVE_START_PITCH_DOWN(WOWPackage * packet);
    void    Handler_MSG_MOVE_STOP_PITCH(WOWPackage * packet);
    void    Handler_MSG_MOVE_SET_RUN_MODE(WOWPackage * packet);
    void    Handler_MSG_MOVE_SET_WALK_MODE(WOWPackage * packet);
    void    Handler_MSG_MOVE_SET_FACING(WOWPackage * packet);
    void    Handler_MSG_MOVE_SET_PITCH(WOWPackage * packet);
    void    Handler_CMSG_MOVE_FALL_RESET(WOWPackage * packet);
    void    Handler_CMSG_MOVE_SET_FLY(WOWPackage * packet);
    void    Handler_MSG_MOVE_START_ASCEND(WOWPackage * packet);
    void    Handler_MSG_MOVE_STOP_ASCEND(WOWPackage * packet);
    void    Handler_CMSG_MOVE_CHNG_TRANSPORT(WOWPackage * packet);
    void    Handler_MSG_MOVE_START_DESCEND(WOWPackage * packet);
    void    Handler_MSG_MOVE_HEARTBEAT(WOWPackage * packet);
    void    Handler_MSG_MOVE_FALL_LAND(WOWPackage * packet);
    void    Handler_MSG_MOVE_START_SWIM(WOWPackage * packet);
    void    Handler_MSG_MOVE_STOP_SWIM(WOWPackage * packet);
    void    Handler_SMSG_ENVIRONMENTALDAMAGELOG(WOWPackage * packet);
	void    Handler_SMSG_FORCE_RUN_SPEED_CHANGE(WOWPackage * packet);
	void    Handler_SMSG_FORCE_SWIM_SPEED_CHANGE(WOWPackage * packet);
	void    Handler_CMSG_FORCE_RUN_SPEED_CHANGE_ACK(WOWPackage * packet);
	void    Handler_SMSG_FORCE_FLIGHT_SPEED_CHANGE(WOWPackage * packet);

	void    Handler_MSG_MOVE_SET_WALK_SPEED(WOWPackage *packet);
	void    Handler_MSG_MOVE_SET_RUN_SPEED(WOWPackage *packet);
	void    Handler_MSG_MOVE_SET_RUN_BACK_SPEED(WOWPackage *packet);
	void    Handler_MSG_MOVE_SET_SWIM_SPEED(WOWPackage *packet);
	void    Handler_MSG_MOVE_SET_SWIM_BACK_SPEED(WOWPackage *packet);
	void    Handler_MSG_MOVE_SET_TURN_RATE(WOWPackage *packet);
	void    Handler_MSG_MOVE_SET_FLIGHT_SPEED(WOWPackage *packet);
	void    Handler_MSG_MOVE_SET_FLIGHT_BACK_SPEED(WOWPackage *packet);
	void    Handler_MSG_MOVE_SET_PITCH_RATE(WOWPackage *packet);
    void    Handler_SMSG_MOVE_KNOCK_BACK(WOWPackage *packet);
    void    Handler_MSG_MOVE_KNOCK_BACK(WOWPackage *packet);

	void    Handler_MSG_MOVE_Change(WOWPackage *packet);

	void    HandlerMovementOpcodes(WOWPackage * packet);
	void	RemakeMovementInfo(uint64 guid, WOWPackage * packet, int pos, DWORD move_flags);

	DWORD	m_HeartBeatTick;
	DWORD	m_OrgDiffTick;
	DWORD	m_LastMovementPackOptype;

public:
    MoveHandler(GameWorld * gameworld);
    ~MoveHandler();

	void    ReadMovementInfo(uint64 guid, WOWPackage * packet, int &pos, DWORD * move_flags_output);
	void	SetPos(uint64 guid, float x, float y, float z, float o);
};


#endif

