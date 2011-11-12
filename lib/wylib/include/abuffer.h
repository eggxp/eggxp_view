//---------------------------------------------------------------------------

#ifndef abufferH
#define abufferH
#include <vcl.h>
//TSmartBuffer封装了一个动态缓冲区对象,可以按类型读取和写入数据,简化了数据拷贝操作
class TSmartBuffer
{
private:
   String m_Data;
   int    m_NewSize; //每次缓冲区不够的时候重新分配的大小
protected:
   int CurPos;
public:
  __fastcall TSmartBuffer(int DefauleBufSize=64);
  __fastcall ~TSmartBuffer();
   void SetPos(int NewPos);
   int  GetPos(){return CurPos;};
   void SetSize(int NewSize);  //更改大小会导致原来的数据丢失
   void AppendSize(int NewSize);   //增加大小,不会导致数据丢失
   int  GetSize(){return m_Data.Length();};
   int  __fastcall Read(void * lpData,int Count);
   int  __fastcall Write(void * lpData,int Count);
   BYTE ReadBYTE();
   WORD ReadWORD();
   DWORD ReadDWORD();
   float  ReadFloat();
   double ReadDouble();
   String ReadCStr();  //读取c风格的字符串
   String ReadAnsiStr(); //读取pascal风格的字符串   DWORD Len,char *Str
   String ReadSmallAnsiStr(); //读取小pascal风格的字符串,BYTE Len,char *Str
   WideString  ReadWideCStr(); //读取c风格的双字节字符串
   WideString  ReadWideString(); //读取pascal风格的双字节字符串
   int  WriteBYTE(BYTE Value);
   int  WriteDWORD(DWORD Value);
   int  WriteWORD(WORD Value);
   int  WriteFloat(float Value);
   int  WriteDouble(double Value);
   int  WriteCStr(String &Str);  //按c风格的字符串 写入
   int  WriteAnsiStr(String &Str); //pascal风格的字符串写入
   int  WriteSmallAnsiStr(String &Str); //按小pascal风格的字符串,BYTE Len,char *Str
   int  WriteWideCStr(WideString &Value); //c风格的双字节字符串写入
   int  WriteWideString(WideString &Value); //pascal风格的双字节字符串写入
   const void * Data(){return m_Data.data();}
   char * c_str(){return m_Data.c_str();}
   void Clear();
   void SaveToFile(String FileName);
   bool LoadFromFile(String FileName);
   bool LoadFromStream(TStream *Stream);
   void LoadFromString(const String &Data);
};

//---------------------------------------------------------------------------
#endif
