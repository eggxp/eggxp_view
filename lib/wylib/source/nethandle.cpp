//---------------------------------------------------------------------------


#pragma hdrstop
                              
#include "nethandle.h"
#include "CommFunc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)


//---------------------------------------------------------------------------
__fastcall TNetHandle::TNetHandle(TForm * AOwner)
{
    _Client = new CClientSocket(HInstance);
    _Client->OnConnect = OnClientConnect;
    _Client->OnDisconnect = OnClientDisconnect;
    _Client->OnError = OnClientError;
    _Client->OnRecv = OnClientRead;
    OnSocketMessage = NULL;
    OutputLog  = NULL;

    SetErrorProc(&OnSocketError);
}
//---------------------------------------------------------------------------
__fastcall TNetHandle::~TNetHandle()
{
   delete _Client;
}
//---------------------------------------------------------------------------
void TNetHandle::SetRemoteAddr(const String &IP,WORD Port)
{
   _Client->SetServerIP(IP.c_str());
   _Client->SetServerPort(Port);
}
//---------------------------------------------------------------------------
bool TNetHandle::Connect()
{
   if (IsActive())
     return false;
   _Client->Connect();
   return true;
}
//---------------------------------------------------------------------------
void TNetHandle::DisConnect()
{
   _Client->Disconnect();
}
//---------------------------------------------------------------------------
int  TNetHandle::SendData(String Data)
{
   if (!IsActive())
     return false;
   OnSocketEvent(nmSEND);
   return _Client->SendBuf(Data.c_str(),Data.Length());
}
//---------------------------------------------------------------------------
int  TNetHandle::SendBuf(char *buf,int len)
{
   if (!IsActive())
     return false;
   OnSocketEvent(nmSEND);
   return _Client->SendBuf(buf,len);
}
//---------------------------------------------------------------------------
void TNetHandle::OutputInfo(const String &Info)
{
    if(OutputLog!=NULL)
    {
      OutputLog(Info);
    }
}
//---------------------------------------------------------------------------
void __fastcall TNetHandle::OnClientConnect(CClientSocket  *ClientSocket)
{
    if (OnSocketMessage!=NULL)
    {
      OnSocketMessage(nmCONNECT,(void *)ClientSocket->SocketID(),0);
    }
    OnSocketEvent(nmCONNECT);
    RecvCacheData = "";
    SendByteTotal = 0;
    RecvByteTotal = 0;
}
//---------------------------------------------------------------------------
void __fastcall TNetHandle::OnClientDisconnect(CClientSocket  *ClientSocket,bool ServerDisconnect)
{
    if (OnSocketMessage!=NULL)
    {
      OnSocketMessage(nmDISCONNECT,(void *)ClientSocket->SocketID(),0);
    }
    OnSocketEvent(nmDISCONNECT);
}
//---------------------------------------------------------------------------
void __fastcall TNetHandle::OnClientError(CClientSocket  *ClientSocket,int ErrorCode,char *ErrorInfo)
{
    String sErrorInfo = FormatStr("socket error:%s,%s",SysErrorMessage(ErrorCode),ErrorInfo);
    if (OnSocketMessage!=NULL)
    {
      OnSocketMessage(nmError,sErrorInfo.c_str(),sErrorInfo.Length());
    }
    OnSocketEvent(nmError);
    ErrorCode=0;
}
//---------------------------------------------------------------------------
void __fastcall TNetHandle::OnClientRead(CClientSocket  *ClientSocket,SOCKET SocketID)
{
   int RecvLen = ClientSocket->ReceiveLength();
   if (RecvLen<=0)
    return;
   String RecvData;
   RecvData.SetLength(RecvLen);
   RecvLen = ClientSocket->RecvBuf(RecvData.c_str(),RecvData.Length());
   if (RecvData.Length()>0)
   {
      if (OnSocketMessage!=NULL)
      {
		OnSocketMessage(nmRECV,RecvData.c_str(),RecvLen);
      }
	  OnSocketEvent(nmRECV);
	  if (DispatchSocketWindowMsg(String(RecvData.c_str(),RecvLen))>0)
      {
          OutputInfo(LastErrInfo);
      }
   }
}
//---------------------------------------------------------------------------
String TNetHandle::GetHostAddr()
{
   return _Client->GetServerIP();
}
//---------------------------------------------------------------------------
void __fastcall TNetHandle::OnSocketError(int ErrorCode)
{
   ShowDebugInfo("Unknow Socket Error:" + IntToStr(ErrorCode));
}
//---------------------------------------------------------------------------
__fastcall TProxyServer::TProxyServer()
{
   m_lpClientNetHandle = NULL;
   ServerSocket = new TServerSocket(NULL);
   ServerSocket->OnClientConnect = ServerSocketClientConnect;
   ServerSocket->OnClientDisconnect =  ServerSocketClientDisconnect;
   ServerSocket->OnClientError      =  ServerSocketClientError;
   ServerSocket->OnClientRead       =  ServerSocketClientRead;
   m_lpClientWaitDataBuf = new TStringList;
   m_LocalActiveServerSocket = NULL;
}
//---------------------------------------------------------------------------
__fastcall TProxyServer::~TProxyServer()
{
   ServerSocket->Close();
   delete m_lpClientWaitDataBuf;
   delete ServerSocket;
}
//---------------------------------------------------------------------------
void __fastcall TProxyServer::ServerSocketClientConnect(TObject *Sender, TCustomWinSocket *Socket)
{
      m_LocalActiveServerSocket = Socket;
      m_lpClientNetHandle->Connect();
      if (OnServerSocketMessage)
      {
         String Info = FormatStr("Socket:%d",Socket->Handle);
         OnServerSocketMessage(nmCONNECT,Info);
      }
}
//---------------------------------------------------------------------------
void __fastcall TProxyServer::ServerSocketClientError(TObject *Sender,
                                                      TCustomWinSocket *Socket,
                                                      TErrorEvent ErrorEvent, int &ErrorCode)
{
    ErrorCode = 0;
    m_lpClientNetHandle->DisConnect();
    if(OnServerSocketMessage)
    {
        String Info = FormatStr("Error:%d",ErrorCode);
        OnServerSocketMessage(nmError,Info);
    }
}
//---------------------------------------------------------------------------
void __fastcall TProxyServer::ServerSocketClientDisconnect(TObject *Sender,
                                                           TCustomWinSocket *Socket)
{
    m_lpClientNetHandle->DisConnect();
    m_LocalActiveServerSocket = NULL;
    if(OnServerSocketMessage)
    {
        String Info = FormatStr("Socket:%d",Socket->Handle);
        OnServerSocketMessage(nmDISCONNECT,Info);
    }
}
//---------------------------------------------------------------------------
void __fastcall TProxyServer::ServerSocketClientRead(TObject *Sender,
                                                     TCustomWinSocket *Socket)
{
    String  RecvData = Socket->ReceiveText();
    if(RecvData.Length() > 0)
    {
        if(OnServerSocketMessage)
        {
			OnServerSocketMessage(nmRECV,RecvData);
		}
        if(!m_lpClientNetHandle->IsActive())
        {
            m_lpClientWaitDataBuf->Add(RecvData);
        }
        else
        {
            m_lpClientNetHandle->SendData(RecvData);
        }
    } 
}
//---------------------------------------------------------------------------
void __fastcall TProxyServer::OnClientSocketMsg(NET_MSG_TYPE Type, void *Data,
                                                int DataLen)
{
    if(!m_LocalActiveServerSocket)  //客户端还没激活
    return;
    if(Type == nmDISCONNECT || Type == nmError) //客户端连接出错或断开,断开和本地游戏连接
    {
           m_LocalActiveServerSocket->Close();
    }
    else if(Type == nmCONNECT)                  //客户端连接成功,检查待发送缓冲区,将待发送数据发出去
    {
        for(int i = 0; i < m_lpClientWaitDataBuf->Count; i++)
        {
            m_lpClientNetHandle->SendData(m_lpClientWaitDataBuf->Strings[i]);
        }

        m_lpClientWaitDataBuf->Clear();
    }
    else if(Type == nmRECV)   //转发
    {
         m_LocalActiveServerSocket->SendBuf(Data,DataLen);
    }

    if(m_pfOrgClientMessage)
    {
        m_pfOrgClientMessage(Type, Data, DataLen);
    }
}
//---------------------------------------------------------------------------
void __fastcall TProxyServer::SetClientNetHandle(TNetHandle *ClientNetHandle)
{
   m_lpClientNetHandle  = ClientNetHandle;
   m_pfOrgClientMessage = m_lpClientNetHandle->OnSocketMessage;
   m_lpClientNetHandle->OnSocketMessage = OnClientSocketMsg;
}
//------------------------------------------------------------------------------
int   TProxyServer::SendData(char *Data,int Len)
{
    if(!m_LocalActiveServerSocket)  //客户端还没激活
       return -1;
    return     m_LocalActiveServerSocket->SendBuf(Data,Len);
}

