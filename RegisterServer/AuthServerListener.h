//---------------------------------------------------------------------------

#ifndef AuthServerListenerH
#define AuthServerListenerH
//---------------------------------------------------------------------------
#include <vcl.h>
#include <WINSOCK2.H>
#include <ADODB.hpp>
#include <DB.hpp>
#include "Log4Me.h"
#include "AList.h"
#include "AMap.h"
#include "ThreadManager.h"
#include "SocketClientUser.h"
#include "SRP6Auth.h"
#include "AuthCrypt.h"
 #include   <algorithm>

#define		SQL_TIMEOUT		  	60 * 1000 * 5

int			GetAllFreeCardCount(TADOQuery *query);

String		GetFileNameByDate(String name, String ext);
bool		GenerateCard(TADOQuery *query, String cardType, int cnt);

String		GetCardNameByCardType(String cardType);
int			GetDaysByCardType(String cardType);
int			GetMoneyByCardType(String cardType);
bool		GetExpireTime(TADOQuery *query, String username, vector<String> *outputMsg, TDateTime *result);

String		CreateCardNo(String cardType);
String		GetCardEndDataFromNow(String cardType);
bool					ExecSQL(TADOQuery *query);
bool					OpenSQL(TADOQuery *query);

bool		Charge(TADOQuery *query, String username, String card_no, vector<String> *outputMsg);
bool        GetCard(TADOQuery *query, String cardType, String *outputCardNo, vector<String> *outputMsg);

class AuthClientUser : public SocketClientUser
{
private:
	TADOConnection	*		m_ADOConnection;
	TADOQuery *				m_ADOQuery;
	virtual	int         	ClientProcessThread(SingleThread * self);
	SRP6Server				m_SRP6Server;
  	AuthCrypt	    		m_AuthCrypt;
	String					m_UserName;
	int						m_Build;
	String					m_RefuseLoginReason;
	BYTE					m_IsChargeProcess;

	void 					SocketReadError(String msg);
	void					OnLoginSuccess();
	bool					CheckUserCanLogin(vector<String> *outputMsg);
	bool					SendAuthMessage(BYTE *lpdate, int len);
	bool					SendLogMessage(AnsiString msg);
	bool					SendRegMessage();

	virtual	void	DecryptRecv(BYTE *lpdata, int len);
	virtual void  	EncryptSend(BYTE *lpdata, int len);


	bool					OnUserFirstLogin(vector<String> *outputMsg);
public:
	AuthClientUser();
	~AuthClientUser();

	virtual		void            Start(SOCKET client, SOCKADDR_IN clientAddr);
};

//-----------------------------------------------------------------------------

struct	tagCardInfo
{
	String 	CardType;
	int     CardDay;
	int		CardMoney;
	String  CardName;
	tagCardInfo()
	{
		CardDay = 0;
		CardMoney = 0;
	}
	bool operator < (const tagCardInfo & rhs)const // ÉýÐòÅÅÐòÊ±±ØÐëÐ´µÄº¯Êý
	{
		return CardDay < rhs.CardDay;
	}
	bool operator > (const tagCardInfo & rhs)const // ½µÐòÅÅÐòÊ±±ØÐëÐ´µÄº¯Êý
	{
		return CardDay > rhs.CardDay;
	}
};

class AuthServerListener
{
private:
	AIndexList<AuthClientUser>       m_Users;
	map<String, tagCardInfo>		 m_CardTypes;
	CRITICAL_SECTION m_csLock;

	int             m_ListenPort;
	SOCKET          m_ListenSocket;
	int             m_ListenThreadCount;
	String			m_DatabaseUserID;
	String          m_DatabaseUserPsw;
	String          m_DatabaseIP;
	int				m_DatabasePort;

	int                     ListenThread(SingleThread * self);
public:
    AuthServerListener();
    ~AuthServerListener();

    bool            Start(int listenPort, int listenThreadCount = 1000);
    void            Close();
	void			ProcessCloseClients();
	void            CloseConnect(SOCKET socket);
	GEN_GET_SET(String, DatabaseUserID)
	GEN_GET_SET(String, DatabaseUserPsw)
	GEN_GET_SET(String, DatabaseIP)
	GEN_GET_SET(int,	DatabasePort);
	int				GetUserCount(){return	m_Users.Count();}

	tagCardInfo	*	GetCardInfo(String key);
	void			AddCardInfo(String key, int day, int money, String name);
	tagCardInfo	*   GetCardInfoByIndex(int index);
	int				GetCardInfoCount();
};

AuthServerListener      *       GetAuthServerListener();
#endif
