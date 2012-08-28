//---------------------------------------------------------------------------

#ifndef LOLPackageDispatcherH
#define LOLPackageDispatcherH
//---------------------------------------------------------------------------

#include <vcl.h>
#include "ReviewerCommon.h"
#include "PackageCommon.h"
#include "BlowFish.h"


class LOLBlowFish
{
private:
	BlowFish	*	m_BlowFish;
public:
	LOLBlowFish();
	~LOLBlowFish();
	BlowFish	*	GetBlowFish();
	void	Init(AnsiString key);
};

LOLBlowFish * GetLOLBlowFish();

////////////////////////////////////////////////////////////////////////////////////

class	LOLPackageDispatcher : public PackageDispatcher
{
//内部使用变量
private:
	WOWPackage				m_SendBufferPacket;
    WOWPackage				m_RecvBufferPacket;
//内部使用回调
private:
	void					DecryptData(WOWPackage* pack);

//内部使用函数
public:
	String              GetOPcodeMsgByCMD(uint8 cmd);

	int                 DigestSendPacket();
	int                 DigestRecvPacket();
	int                 IsPacketNeedDecrypt(WOWPackage *packet);

public:
	LOLPackageDispatcher();
	~LOLPackageDispatcher();


	//调用方法
public:
	void				GetOrignSendPacket(WOWPackage *  packet);
    void				GetOrignRecvPacket(WOWPackage *  packet);
	//打包发送
	void				PackData(char * buf, int len);
	void				Clear();
};


#endif
