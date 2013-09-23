//---------------------------------------------------------------------------

#ifndef PackageCommonH
#define PackageCommonH
//---------------------------------------------------------------------------
#include    <VCL.h>
#include 	<vector>
#include    "CommFunc.h"
#include    "ReviewerCommon.h"
using namespace std;

enum TProxyType
{
	PROXY_TYPE_REALM = 0,
	PROXY_TYPE_WORLD = 1
};

class WOWPackage;
typedef	 void	(__closure	* TOnGetPacket)(WOWPackage *	packet);

enum TGetInfoType
{
	GIT_LINE = 0,
	GIT_CVS,
	GIT_DETAIL,
    GIT_FILE
};

#pragma pack(push,1)
struct ClientPktHeader
{
	uint16 cmd;
	uint16 size;
};

#pragma pack(pop)


class	PackageDispatcher
{
protected:
    virtual     void              MoveBuffer(WOWPackage *input, int pos);
    int         m_PackageContainerIndex;
public:
    TOnGetPacket		fpOnGetPacket;
    PackageDispatcher(){fpOnGetPacket=NULL;m_PackageContainerIndex = 0;}
    virtual ~PackageDispatcher(){}

    virtual     void				GetOrignSendPacket(WOWPackage *  packet) = 0;
    virtual     void				GetOrignRecvPacket(WOWPackage *  packet) = 0;
    virtual     void				Clear() = 0;
    virtual     void				SetPackageContainerIndex(int index){m_PackageContainerIndex = index;}
    virtual     int                 GetPackageContainerIndex(){return m_PackageContainerIndex;}
};



class WOWPackage
{
private:
    AnsiString          m_Data;
	AnsiString          m_OrgData;
	AnsiString          m_OrgPrefixData;
    String          m_OpCodeMsg;
    int             m_Index;
    String          m_Mark;
	int             m_Decrypted;
	int             m_BigPacketDecrypted;
	int             m_Processed;
	String          m_Time;
	int             m_OpCode;
	AnsiString          m_Decompress;
	auto_ptr<TStringList>     m_Comment;
	int				m_PackType;			//1. Auth 0.World
	void			OnInit();
	int				m_IsFreed;
	uint64			m_Guid;
	int				m_ForceSend;
	int				m_PacketProxyType;
	int				m_PacketProxyIndex;

	String          m_DestIP;
	int             m_DestPort;
	bool			m_NotShowInGui;		//是否显示出来
	int				m_HeadSize;

public:
    WOWPackage();
    ~WOWPackage();
    explicit WOWPackage(AnsiString orgData, int index);

    void            Assign(WOWPackage * package);
    void            Clear();

    void            ClientToServerDecrypt();
	void            ServerToClientDecrypt();
	void			ServerToClientDecryptForBigPacket();
	void            ServerToClientDecryptOver();

    void            ClientToServerEncrypt();
	void            ServerToClientEncrypt();

	int				GetIsFreed(){return	m_IsFreed;}

	GEN_GET_SET(AnsiString, Data)
	GEN_GET_SET(uint64, Guid)
    GEN_GET_SET(String, OpCodeMsg)
    GEN_GET_SET(String, Mark)
    GEN_GET_SET(int, Index)
    GEN_GET_SET(int, Decrypted);
	GEN_GET_SET(AnsiString, OrgData);
	GEN_GET_SET(AnsiString, OrgPrefixData);
    GEN_GET_SET(int, Processed);
    GEN_GET_SET(String, Time);
	GEN_GET_SET(int, OpCode);
	GEN_GET_SET(int, PackType);
	GEN_GET_SET(int, ForceSend);
	GEN_GET_SET(AnsiString, Decompress);
	GEN_GET_SET(int, PacketProxyType);
    GEN_GET_SET(int, PacketProxyIndex);
    GEN_GET_SET(String, DestIP);
    GEN_GET_SET(int, DestPort);
	GEN_GET_SET(int, BigPacketDecrypted);
	GEN_GET_SET(bool, NotShowInGui);
	GEN_GET_SET(int, HeadSize);
    TStringList *   GetComment() {return    m_Comment.get();}
    void            AddComment(String key, String value);

    char    *       GetContent();
    int             GetContentLen();

    uint64          ReadPackGUID(int &pos);
    void            WritePackGUID(int &pos, uint64 guid);
	AnsiString          ReadString(int &pos);
	vector<unsigned char> ReadZData(int &pos);

	char    *       GetHead();
	void            GetInfo(TGetInfoType getInfoType, bool showPackHead, bool showOrgPack, TStrings * output);
	void			ChangeOPCode(int opcode);
	void  			RemoveContent(int pos, int size);
};


typedef void    (__closure * TPacketHandler)(WOWPackage * packet);


#endif
