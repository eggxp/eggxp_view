//---------------------------------------------------------------------------


#pragma hdrstop

#include "NetStream.h"
#include "Log4Me.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

CNetStream::CNetStream(SOCKET    socketID) : m_PackBufer()
{
    m_SocketID = socketID;
}

CNetStream::~CNetStream()
{
}

int         CNetStream::SendBuf(char *lpData, int len)
{
    return  send(m_SocketID, lpData, len, 0);
}

int         CNetStream::RecvBuf(char *lpData, int len)
{                     
    return  recv(m_SocketID, lpData, len, 0);
}

int         CNetStream::SendBuf_n(char *lpData, int len)
{
    //完整接收
    int iTotalLen=len;
    int iSendLen=0;
    int ret;
    do {
        ret=SendBuf(lpData+iSendLen, iTotalLen-iSendLen );

        //发送错误
        if (ret<=0)
        {
            return  ret;
        }
        else
        {
            iSendLen+=ret;
        }
    }while(iSendLen!=iTotalLen);
    return  len;
}
                     
int         CNetStream::SendBuf_o(char *lpData, int len)
{
    try
    {
        if(len == 0)
        {
            if(m_PackBufer.GetResultLength() <= 0)
            {
                //没有信息发送
                SetLastError(ERR_SEND_ZERO);
                return 0;
            }
            else
            {
                int ret = SendBuf_n(m_PackBufer.GetResult(), m_PackBufer.GetResultLength());
                m_PackBufer.Reset();
                return  ret;
            }

        }


        if(m_PackBufer.Put(lpData, len))
            return  len;

        //放不下, 应该send了
        if(m_PackBufer.GetResultLength())
        {
            int ret = SendBuf_n(m_PackBufer.GetResult(), m_PackBufer.GetResultLength());
            if(ret <= 0)
                return ret;
        }
        m_PackBufer.Reset();
        if(m_PackBufer.Put(lpData, len) == false)
        {
            //还是发送不了, 证明是超大封包, 直接发送
            return  SendBuf_n(lpData, len);
        }
        return len;
    }
    catch(Exception &e)
    {
        GetLog()->Fatal("CNetStream::SendBuf_o, lpData = %d, len = %d", lpData, len);
        return  0;
    }
}


/////////////////////////////////////////////////////////////////////////
//开启256k空间
CICOPNetStream::CICOPNetStream(IServerClient * serverClient) : m_PackBufer(256 * 1024)
{
    m_IServerClient = serverClient;
}

CICOPNetStream::~CICOPNetStream()
{
}
                     
int         CICOPNetStream::SendBuf_o(char *lpData, int len)
{
    try
    {
        if(len == 0)
        {                     
            if(m_PackBufer.GetResultLength() <= 0)
            {
                //没有信息发送
                SetLastError(ERR_SEND_ZERO);
                return 0;
            }
            else
            {             
                int ret = m_IServerClient->SendBuffer(m_PackBufer.GetResult(), m_PackBufer.GetResultLength());
                m_PackBufer.Reset();
                return  ret;
            }

        }


        if(m_PackBufer.Put(lpData, len))
            return  len;

        //放不下, 应该send了
        if(m_PackBufer.GetResultLength())
        {
            int ret = m_IServerClient->SendBuffer(m_PackBufer.GetResult(), m_PackBufer.GetResultLength());
            if(ret <= 0)
                return ret;
        }
        m_PackBufer.Reset();
        if(m_PackBufer.Put(lpData, len) == false)
        {
            //还是发送不了, 证明是超大封包, 直接发送
            return  m_IServerClient->SendBuffer(lpData, len);
        }
        return len;
    }
    catch(Exception &e)
    {
        GetLog()->Fatal("CICOPNetStream::SendBuf_o, lpData = %d, len = %d", lpData, len);
        return  0;
    }
}
