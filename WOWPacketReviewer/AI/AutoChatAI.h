//---------------------------------------------------------------------------

#ifndef AutoChatAIH
#define AutoChatAIH
//---------------------------------------------------------------------------

#include <VCL.h>
#include <map>
#include "GameWorld.h"
#include "FiberContext.h"

using namespace std;

struct	tagAreaChatAIResult
{
	String AreaName;
	int	PlayerCount;
	int ProcessCount;
	int	Expired;
	tagAreaChatAIResult()
	{
		PlayerCount = 0;
		ProcessCount = 0;
		Expired = 0;
	}
};

class AutoChatAI : public FiberProcesser
{
private:
    void        SendDZZhaoJia();
	DWORD       m_ActiveTick;

	map<String, tagWhoPlayerInfo>	m_AreaPlayerWhoInfo;
	map<String, tagAreaChatAIResult>	m_AreaChatAIResult;
	void		InitAreas();
	String		m_SendText;
public:
	AutoChatAI();
	~AutoChatAI();

	void        OnProcess();
	map<String, tagWhoPlayerInfo>	*GetAreaPlayerWhoInfo(){return &m_AreaPlayerWhoInfo;}
	map<String, tagAreaChatAIResult>	*GetAreaChatAIResult(){return &m_AreaChatAIResult;}
	GEN_GET_SET(String, SendText)
};


#endif
