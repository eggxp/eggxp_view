//---------------------------------------------------------------------------

#ifndef NetStreamH
#define NetStreamH
//---------------------------------------------------------------------------

#include    "fl_blockclient.h"
#include    "fl_IServer.h"
#include    <VCL.h>
#include    "PackBuffer.h"

#define MAKE_ERROR(n) (n | 0x20000000) 
#define ERR_SEND_ZERO      MAKE_ERROR(0x1)


class   PackBufer;
class CNetStream
{
private:
    SOCKET          m_SocketID;

    PackBufer       m_PackBufer;
public:
    CNetStream(SOCKET    socketID);
    ~CNetStream();

    int         SendBuf(char *lpData, int len);
    int         RecvBuf(char *lpData, int len);

    //发送指定n字节的封包
    int         SendBuf_n(char *lpData, int len);
    //接收指定n字节的封包, 若还没有收到指定长度的封包, 则阻塞等待
//    int         RecvBuf_n(char *lpData, int len);

    //优化版, 将多个小包累计到一定的缓冲区大小, 再发送
    //如果len大于缓冲区, 直接发送
    //如果len小于缓冲区, 累计, 到达上限后再发送
    //如果len为0的话, 表示发送所有剩余缓冲区数据
    int         SendBuf_o(char *lpData, int len);
};



class CICOPNetStream
{
private:
    IServerClient   *   m_IServerClient;

    PackBufer       m_PackBufer;
public:
    CICOPNetStream(IServerClient * serverClient);
    ~CICOPNetStream();

    //接收指定n字节的封包, 若还没有收到指定长度的封包, 则阻塞等待
//    int         RecvBuf_n(char *lpData, int len);

    //优化版, 将多个小包累计到一定的缓冲区大小, 再发送
    //如果len大于缓冲区, 直接发送
    //如果len小于缓冲区, 累计, 到达上限后再发送
    //如果len为0的话, 表示发送所有剩余缓冲区数据
    int         SendBuf_o(char *lpData, int len);
};
#endif
