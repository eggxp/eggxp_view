//---------------------------------------------------------------------------


#pragma hdrstop

#include "PackageCommon.h"
#include "AuthLoader.h"
#include "CommFunc.h"
#include "Opcodes.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)




void              PackageDispatcher::MoveBuffer(WOWPackage * input, int pos)
{
    input->SetData("");
    AnsiString orgData = input->GetOrgData();
    input->SetOrgData(AnsiString(orgData.c_str() + pos, orgData.Length() - pos));
    input->SetBigPacketDecrypted(0);
    return;
}



WOWPackage::WOWPackage() : m_Comment(new TStringList)
{
	Clear();
	m_Time = DateTimeToStr(Now());
	TReplaceFlags   flag;
	flag << rfReplaceAll;
	m_Time = StringReplace(m_Time, "/", "-", flag);
	OnInit();
}

void		WOWPackage::OnInit()
{
	m_IsFreed = 0;
//	GetLog()->Warn("New WOWPackage, this = 0x%p", this);
}

WOWPackage::WOWPackage(AnsiString orgData, int index) : m_Comment(new TStringList)
{
	Clear();
	m_OrgData = orgData;
	m_Index = index;
	OnInit();
}

WOWPackage::~WOWPackage()
{
	if(m_IsFreed)
	{
		GetLog()->Fatal("Multi Free WOWPackage, this = 0x%p", this);
	}
	m_IsFreed = 1;
//	GetLog()->Warn("Free WOWPackage, this = 0x%p", this);
}

void            WOWPackage::Assign(WOWPackage * package)
{
    m_Data = package->m_Data;
    m_OpCodeMsg = package->m_OpCodeMsg;
    m_Index = package->m_Index;
    m_Mark = package->m_Mark;
	m_OrgData = package->m_OrgData;
	m_OrgPrefixData = package->m_OrgPrefixData;
	m_Decrypted = package->m_Decrypted;
	m_BigPacketDecrypted = package->m_BigPacketDecrypted;
    m_Processed = 0;
    m_Time = package->m_Time;
	m_OpCode = package->m_OpCode;
	m_PackType = package->m_PackType;
    m_Comment->Clear();
    m_Comment->AddStrings(package->m_Comment.get());
	m_Decompress = package->m_Decompress;
	m_ForceSend = package->m_ForceSend;
	m_PacketProxyType = package->m_PacketProxyType;
    m_PacketProxyIndex = package->m_PacketProxyIndex;
    m_DestIP = package->m_DestIP;
	m_DestPort = package->m_DestPort;
	m_NotShowInGui = package->m_NotShowInGui;
	m_HeadSize = package->m_HeadSize;
}

void            WOWPackage::Clear()
{
	m_NotShowInGui = false;
    m_Data = "";
	m_OrgData = "";
	m_HeadSize = 8;
	m_OrgPrefixData = "";
    m_OpCodeMsg = "";
    m_Index = 0;
    m_Mark = "";
	m_Decrypted = 0;
	m_BigPacketDecrypted = 0;
    m_Processed = 0;
	m_OpCode = 0;
	m_PackType = 0;
    m_Decompress = "";
	m_Comment->Clear();
	m_Guid = 0;
	m_ForceSend = 0;
	m_PacketProxyType = 0;
    m_DestIP = "";
    m_DestPort = 0;
    m_PacketProxyIndex = 0;
}

void            WOWPackage::AddComment(String key, String value)
{
    if(value == "")
        m_Comment->Add(FormatString("%s : ", key));
    else
        m_Comment->Add(FormatString("%s : %s", key, value));
}

void            WOWPackage::ClientToServerDecrypt()
{
    if(m_Decrypted)
        return;
    m_Data = m_OrgData;
    m_Data = m_Data.Unique();
    DecryptClientToServer(this->GetPacketProxyIndex(), m_Data.c_str(), this->GetHeadSize());
    m_Decrypted = 1;
}

void            WOWPackage::ServerToClientDecrypt()
{
    if(m_Decrypted)
        return;
    m_Data = m_OrgData;
    m_Data = m_Data.Unique();
    DecryptServerToClient(this->GetPacketProxyIndex(), m_Data.c_str(), 4);
    m_Decrypted = 1;
}

void            WOWPackage::ServerToClientDecryptOver()
{
    if(m_Decrypted)
        return;
	DecryptServerToClientEnd(this->GetPacketProxyIndex());
}

void			WOWPackage::ServerToClientDecryptForBigPacket()
{
    if(m_BigPacketDecrypted)
        return;
    DecryptServerToClient(this->GetPacketProxyIndex(), m_Data.c_str() + 4, 1);
    m_BigPacketDecrypted = 1;
}

void            WOWPackage::ClientToServerEncrypt()
{
	m_OrgPrefixData = m_Data;
    m_OrgPrefixData = m_OrgPrefixData.Unique();
    EncryptClientToServer(this->GetPacketProxyIndex(), m_OrgPrefixData.c_str(), this->GetHeadSize());
}

void            WOWPackage::ServerToClientEncrypt()
{
	m_OrgPrefixData = m_Data;
	m_OrgPrefixData = m_OrgPrefixData.Unique();
	EncryptServerToClient(this->GetPacketProxyIndex(), m_OrgPrefixData.c_str(), this->GetHeadSize());
}

char    *       WOWPackage::GetHead()
{
	return	this->GetData().c_str();
}

char    *       WOWPackage::GetContent()
{
    if(this->GetDecompress().Length())
    {
        return  this->GetDecompress().c_str();
	}

	return  this->GetData().c_str() + this->GetHeadSize();
}

int             WOWPackage::GetContentLen()
{
    if(this->GetDecompress().Length())
    {
        return  this->GetDecompress().Length();
    }

	return	this->GetData().Length() - this->GetHeadSize();
}

uint64          WOWPackage::ReadPackGUID(int &pos)
{
    uint64 guid = 0;
    uint8 guidmark = ReadBYTE(this->GetContent(), pos);

    for(int i = 0; i < 8; ++i)
    {
        if(guidmark & (uint8(1) << i))
        {
            uint8 bit = ReadBYTE(this->GetContent(), pos);
            guid |= (uint64(bit) << (i * 8));
        }
    }

    return guid;
}

AnsiString          WOWPackage::ReadString(int &pos)
{
    char *lpData = this->GetContent() + pos;
    int readLen = strlen(lpData);
    pos += (readLen + 1);
    if(readLen == 0)
        return  "";
    return AnsiString(lpData, readLen);
}

void            WOWPackage::WritePackGUID(int &pos, uint64 guid)
{
    int writePos = pos;
    WriteBYTE(this->GetContent(), pos, 0);
    for(uint8 i = 0; i < 8; ++i)
    {
        if(guid & 0xFF)
        {
            this->GetContent()[writePos] |= uint8(1 << i);
            WriteBYTE(this->GetContent(), pos, guid & 0xFF);
        }

        guid >>= 8;
    }
}

void            WOWPackage::GetInfo(TGetInfoType getInfoType, bool showPackHead, bool showOrgPack, TStrings * output)
{
    ASSERT(output)
    output->BeginUpdate();

	try{

    int headsize = 0;
    if(showPackHead == false)
    {
        headsize = GetHeadSize();
	}
	AnsiString getData;
	if (showOrgPack)
	{
		getData = this->GetOrgData();
	}
	else
	{
		getData = this->GetData();
	}
    AnsiString bindata = AnsiString(getData.c_str()+headsize, getData.Length()-headsize);
	if(getInfoType == GIT_LINE)
	{
		output->Add(BinToStr(bindata.c_str(), bindata.Length()));
		return;
	}

	if(getInfoType == GIT_DETAIL || getInfoType == GIT_FILE)
	{
		output->Add(this->GetTime());
		output->Add(FormatString("DIR   : %s", this->GetMark()));
		output->Add(FormatString("LENGTH: %d", getData.Length()));
		output->Add(FormatString("OPCODE: %s (0x%X)", this->GetOpCodeMsg(), this->GetOpCode()));
		output->Add("DATA:");
		BeautifulHex(bindata, output);
		output->Add("");
		if(this->GetDecompress().Length())
		{
			output->Add("DECOMPRESS:");
			BeautifulHex(this->GetDecompress(), output);
			output->Add("");
		}
		output->Add("");
		output->Add("");
		output->AddStrings(this->GetComment());
		output->Add("");
		return;
	}

	if(getInfoType == GIT_CVS)
	{
		String result;
		result = IntToStr(this->GetIndex()) + "\t";
		result += this->GetTime() + "\t";
		result += this->GetMark() + "\t";
		result += IntToStr(getData.Length()) + "\t";
		result += this->GetOpCodeMsg() + "\t";
		result += BinToStr(bindata.c_str(), bindata.Length());
		output->Add(result);
		return;
	}

	} __finally {
		output->EndUpdate();
	}
}

void			WOWPackage::ChangeOPCode(int opcode)
{
	if(m_PackType == 1)
		return;

	String opcodeName = LookupOpcodeName(opcode);
	int dataPos = 0;
    if(this->GetMark() == SEND_MARK)
    {
		dataPos = 2;
		this->SetOpCode(opcode);
		this->SetOpCodeMsg(opcodeName);
		WriteDWORD(this->GetHead(), dataPos, opcode);
		return;
    }

	dataPos = 2;
	if(this->GetData().Length() + 2 > 0x7FFF)
	{
		dataPos = 3;
	}
	this->SetOpCode(opcode);
	this->SetOpCodeMsg(opcodeName);
	WriteWORD(this->GetHead(), dataPos, opcode);
}

void  			WOWPackage::RemoveContent(int pos, int size)
{
	int headSize = this->GetHeadSize();
	m_Data.Delete(headSize + pos + 1, size);
	int sizePos = 1;
	int len = ReadBYTE(m_Data.c_str(), sizePos);
	sizePos = 1;
	WriteBYTE(m_Data.c_str(), sizePos, len-size);
}
