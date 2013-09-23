//---------------------------------------------------------------------------

#ifndef PackageContainerH
#define PackageContainerH
//---------------------------------------------------------------------------
#include <VCL.h>
#include "CommFunc.h"
#include "PackageCommon.h"
#include "AuthPackageDispatcher.h"
#include "WorldPackageDispatcher.h"
#include "MSanguoPackageDispatcher.h"
#include "DefaultPackageDispatcher.h"
#include "DiabloIIIPackageDispatcher.h"
#include "War3PackageDispatcher.h"
#include "LOLPackageDispatcher.h"
#include "AQueue.h"

#define USE_PACKAGE_DISPATCHER War3PackageDispatcher

int GetLogicPackIndex();
void SetLogicPackIndex(int index);
void AddLogicPackIndex();

struct FilterType {
	int Opcode;
	uint64 Guid;
    FilterType()
    {
		Opcode = 0;
		Guid = 0;
    }
};

class PackageContainer
{
private:
    String                  m_Name;
    AList<WOWPackage>       m_Recv;
    AList<WOWPackage>       m_Send;
    AList<WOWPackage>       m_All;
    PackageDispatcher   *   m_SendPackageDispatcher;
    PackageDispatcher   *   m_RecvPackageDispatcher;
    int                     m_PackageContainerIndex;

    AList<WOWPackage>       m_RecvFilter;
    AList<WOWPackage>       m_SendFilter;
    AList<WOWPackage>       m_AllFilter;
    AList<FilterType>       m_FilterOpcode;
    bool                    m_EnableFilter;
	bool                    m_ReverseFilter;
	bool					m_CreatureFilter;
	bool					m_ForbiddenSend;

	void                    AddPackToFilter(AList<WOWPackage> * source, AList<WOWPackage> * dest);

	bool                    FindFilterOpcode(int opcode, uint64 guid);

public:
	PackageContainer(PackageDispatcher   * sendDispatcher, PackageDispatcher   * recvDispatcher, int packetContainerIndex);
	~PackageContainer();

	void                    GetPack(WOWPackage * packet);
	void					SaveFilter();
	void					LoadFilter();
	String					GetSaveFilterName();
	bool					HideFilterOpcode(int opcode, uint64 guid);
	bool					NeedHidePackage(WOWPackage *	packet);

    void                    OnGetSendWOWPack(WOWPackage *	packet);
    void                    OnGetRecvWOWPack(WOWPackage *	packet);
    
    void                    ClearPackageContainer();
	AList<WOWPackage>    *  GetRecv(){return    &m_Recv;};
    AList<WOWPackage>    *  GetSend(){return    &m_Send;};
    AList<WOWPackage>    *  GetAll(){return    &m_All;};

    void                    SetName(String name){m_Name = name;}
    String                  GetName(){return        m_Name;}

    AList<WOWPackage>   *   GetFilterRecv(){return  &m_RecvFilter;}
    AList<WOWPackage>   *   GetFilterSend(){return  &m_SendFilter;}
    AList<WOWPackage>   *   GetFilterAll(){return   &m_AllFilter;}
    AList<FilterType>   *   GetFilterOpcode(){return    &m_FilterOpcode;}
    GEN_GET_SET(bool, EnableFilter)
	GEN_GET_SET(bool, ReverseFilter)
	GEN_GET_SET(bool, CreatureFilter)
	GEN_GET_SET(bool, ForbiddenSend)
    GEN_GET_SET(int, PackageContainerIndex)
    void                    RefreshFilter();
    void                    AddFilterOpcode(int opcode, uint64 guid);
};


////////////////////////////////////////////////////////////////////////////////////
class WOWProxy;
class PackageContainerManager
{
private:
//	LOLPackageDispatcher       m_SendAuthPackageDispatcher;
//	LOLPackageDispatcher       m_RecvAuthPackageDispatcher;
	USE_PACKAGE_DISPATCHER   m_SendAuthPackageDispatcher;
	USE_PACKAGE_DISPATCHER   m_RecvAuthPackageDispatcher;
    PackageContainer            m_AuthPackageContainer;

	AList<PackageDispatcher>      m_SendWorldPackageDispatcher;
	AList<PackageDispatcher>      m_RecvWorldPackageDispatcher;
	AList<PackageContainer>     m_WorldPackageContainer;

	int							m_ForceOneContainer;

	AList<WOWPackage>			m_AllPackage;
public:
	PackageContainerManager();
	~PackageContainerManager();
	PackageContainer    *       GetAuthPackageContainer(){return        &m_AuthPackageContainer;}
	PackageContainer    *       GetWorldPackageContainer(int index);
    int                         GetWorldPackageContainerCount();
    PackageContainer    *       GetDefaultWorldPackageContainer();
    void                        AddWorldPackageContainer();

	void                        ProcessClientMessage(int forcemove = 0, int processCnt = -1, int toIndex = -1);
	bool                        ProcessOneClientMessage(WOWPackage * curWOWPackage);
	void                    	PopQueue(ASharedPtrQueue<WOWPackage> * packetQueue);
	void						AddAllWOWPackage(WOWPackage *package);
	AList<WOWPackage>		   *GetAllPackage(){return &m_AllPackage;}
	void						ClearAllPackage();
	void                        FreeWorldPackageContainer();
	GEN_GET_SET(int, ForceOneContainer)
};


PackageContainerManager     *       GetPackageContainerManager();
#endif
