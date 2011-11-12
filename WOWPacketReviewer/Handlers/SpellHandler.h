//---------------------------------------------------------------------------

#ifndef SpellHandlerH
#define SpellHandlerH
//---------------------------------------------------------------------------
#include "Opcodes.h"
#include "PackageCommon.h"


class GameWorld;
class SpellHandler
{
private:
    GameWorld           *   m_GameWorld;
    void    Handler_CMSG_CAST_SPELL(WOWPackage * packet);
	void    Handler_SMSG_SPELL_START(WOWPackage * packet);
	void    Handler_SMSG_SPELL_GO(WOWPackage * packet);
	void    Handler_MSG_CHANNEL_START(WOWPackage * packet);
	void    Handler_SMSG_SPELLLOGEXECUTE(WOWPackage * packet);
	void    Handler_SMSG_INITIAL_SPELLS(WOWPackage * packet);
	void    Handler_SMSG_LEARNED_SPELL(WOWPackage * packet);
	void    Handler_SMSG_SUPERCEDED_SPELL(WOWPackage * packet);
	void    Handler_SMSG_CAST_FAILED(WOWPackage * packet);
	void    Handler_SMSG_AURA_UPDATE(WOWPackage * packet);
	void    Handler_SMSG_SPELLNONMELEEDAMAGELOG(WOWPackage * packet);
	void    Handler_SMSG_SPELLHEALLOG(WOWPackage * packet);
	void    Handler_SMSG_TRAINER_LIST(WOWPackage * packet);
	void    Handler_SMSG_SET_FLAT_SPELL_MODIFIER(WOWPackage * packet);
	void    Handler_SMSG_SET_PCT_SPELL_MODIFIER(WOWPackage * packet);

	void    Handler_SMSG_SET_SPELL_Normal(WOWPackage * packet);

	void   	ReadSpellGoTargets(WOWPackage * packet, int &pos, uint64 caster_guid);
	void	ReadSpellTargets(WOWPackage * packet, int &pos, DWORD &targetMask);
	void	ReadAmmoToPacket(WOWPackage * packet, int &pos);
    bool    IsSpellIDCanApplyEffIndex(DWORD spellID, DWORD effidx);

public:
    SpellHandler(GameWorld * gameworld);
    ~SpellHandler();
    
};
#endif
