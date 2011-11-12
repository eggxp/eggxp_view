//---------------------------------------------------------------------------
/*可适合非同步连接的sock5代理服务器连接封装类
作者: Bluely
日期:2003.09.27
说明: 遵循 RFC 1982 标准,目前只实现sock5协议代码,UDP模式下没有测试过.
/*
步骤: smNEGOTIATION   协商版本和方法
客户端连到服务器后，然后就发送请求来协商版本和认证方法：

VER        版本: 0x5 (sock5)
NMETHODS   NMETHODS字段包含了在METHODS字段中出现的方法标示的数目（以字节为单位）。
METHODS    方法:	0x00		不需要认证
                  	0x01   		GSSAPI
                  	0x02   		用户名/密码
                  	0x03 -- 0x7F  	由IANA分配
                  	0x80 -- 0xFE 	为私人方法所保留的
                  	0xFF   	 	没有可以接受的方法

服务器返回:
服务器从这些给定的方法中选择一个并发送一个方法选中的消息回客户端：
VER       版本: 0x5 (sock5)
METHOD    应等于SEND 的METHODS,如果为0xFF表示没有可以接受的方法

步骤: emAUTHENTICATION  校验用户
VER           version of subnegotiation
USERNAME LEN  用户名长度
USERNAME      用户名
PassWord Len  密码长度
PASSWORD      密码

服务器返回:

0x0表示验证成功,否则为失败

步骤:smCONNECTION         发送代理连接信息
SockVER        // socks version
ConnectMethod  // connect method
Reserved       // reserved
AddrType        //address type:   IP V4 address: X'01',
                                  DOMAINNAME:    X'03'
                                  IP V6 address: X'04'
HOSTNAME_LEN   //目标主机名长度
HOSTNAME       //目标主机名
PORT           //目标主机端口



*/
#ifndef sock5H
#define sock5H
#include <Classes.hpp>
enum TSockStepMode {smNEGOTIATION=0,smAUTHENTICATION,smCONNECTION,smFINISH};
enum TAuthenticationMode {amNoAuthentication,amUsernamePassword};
class TSockProxyClient
{
private:
   String mUserName;
   String mPassWord;
   DWORD  mHostIP;
   WORD   mPort;
   TSockStepMode mCurrentStep;
   int    mLastError;
private:
   String DoNegotiation();    //处理协商步骤
   String DoAuthentication(); //处理验证步骤
   String DoConnection();     //处理连接步骤
   bool RecvNegotiation(LPBYTE buf,int Len);    //处理协商步骤返回封包
   bool RecvAuthentication(LPBYTE buf,int Len); //处理验证步骤返回封包
   bool RecvConnection(LPBYTE buf,int Len);     //处理连接步骤返回封包

public:
   TAuthenticationMode AuthenticationMode;
public:
  __fastcall TSockProxyClient();
  __fastcall ~TSockProxyClient();
  void       SetHostInfo(const String &Host,WORD Port); //设置目标服务器信息(不是代理服务器地址)
  void       SetUserInfo(const String &UserName,const String &PassWord);   //设置用户名和密码
  String     ProcessNext();         //处理下一步
  bool       ProcessRecvData(LPBYTE buf,int Len); //处理服务器返回信息
  int        GetCurrentStep();  //获取当前和代理服务器的通信完成步骤
  String     GetCurrentStepInfo();   //获取当前和代理服务器的通信完成步骤描述
  bool       IsFinish(); //是否已经全部验证完毕
  int        GetLastError();
  String     GetLastErrorStr();
  void       Reset();

};

//---------------------------------------------------------------------------
#endif
