//---------------------------------------------------------------------------

#ifndef serverclientH
#define serverclientH
#include <vcl.h>
#include <winsock.h>
#include "CommFunc.h"
//服务器的客户端处理基类,对每个用户的处理,可以从此基类派生
class TServerClient;
typedef void __fastcall (__closure *TON_CLIENT_CLOSE)(SOCKET  SocketID);
typedef void __fastcall (__closure *TON_FREE)(TServerClient* ObjHandle);
class TServerClient
{
private:
  SOCKET       m_Socket;
protected:
  String       m_LastError;

public:
  TServerClient(SOCKET   Socket);
  virtual ~TServerClient();
  virtual int 	  SendBuf(char * Buffer,int Len);
  int	  SendString(String Data); //发送一个String中的数据
  virtual int     RecvBuf(char * DesBuffer,int BufferLen);  //recv数据到缓冲区中
  String  RecvString(); //recv数据到一个String中并返回
  int	  RecvLength(); //查看recv缓冲区当中的数据长度
  bool    Close(); //关闭和此客户端的连接
  String  LastError(){return m_LastError;} //最后的错误信息
  String  GetIP();
  SOCKET  SocketID(){return m_Socket;}
  void *  lpUserData; //用户自定义数据
  bool    IsConnect(){return !(m_Socket == INVALID_SOCKET);}
//事件通知
  TON_CLIENT_CLOSE    OnClientClose;   //客户端关闭
  TON_FREE            OnFree;          //对象释放的时候
};


//---------------------------------------------------------------------------
#endif
