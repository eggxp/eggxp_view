//---------------------------------------------------------------------------

#ifndef WorldPackageDispatcherH
#define WorldPackageDispatcherH
//---------------------------------------------------------------------------
#include <vcl.h>
#include "ReviewerCommon.h"
#include "PackageCommon.h"

class	WorldPackageDispatcher : public PackageDispatcher
{
//内部使用变量
private:
	WOWPackage				m_SendBufferPacket;
    WOWPackage				m_RecvBufferPacket;
//内部使用回调
private:
    

//内部使用函数
public:
    String              GetOPcodeMsgByCMD(uint8 cmd);

    int                 DigestSendPacket();
    int                 DigestRecvPacket();
    int                 IsPacketNeedDecrypt(WOWPackage *packet);

public:
	WorldPackageDispatcher();
	~WorldPackageDispatcher();


	//调用方法
public:
	void				GetOrignSendPacket(WOWPackage *  packet);
    void				GetOrignRecvPacket(WOWPackage *  packet);
	//打包发送
	void				PackData(char * buf, int len);
	void				Clear();
};


#endif
