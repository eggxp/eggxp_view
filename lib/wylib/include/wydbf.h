//---------------------------------------------------------------------------
//网游公司自定义数据格式
//实现一个自定义的小型数据库
//初始版本: 2005.10.25 by 林弋
//纯内存表,所有数据读取到内存当中
//------------------------------------------------------------------------------
#ifndef wydbfH
#define wydbfH
#include <vcl.h>
#include "alist.h"
#define FLAG     0x5566  //文件头标志
#define VER_FLAG 0x1000  //版本信息

#define MAX_FIELD_NAME_LEN 12           //字段名最大长度
#define MAX_DBNAME_LEN 20 //表说明最大长度
#define FIELD_LEN    sizeof(WY_Field)   //字段结构长度
enum FIELD_TYPE {ftBYTE = 0,ftWORD,ftDWORD,ftBUFFER,ftSTRING};
struct tagDB_Head
{
   WORD  Flag;
   WORD  VerFlag;
   char  DB_Name[MAX_DBNAME_LEN];
   DWORD FieldCount;
   DWORD RecordCount;
};

//字段类
class WY_Field
{
   private:
   char   m_Name[MAX_FIELD_NAME_LEN];   //字段名
   int    m_Type;    //字段类型
   int    m_Length;   //字段长度
   protected:

   public:
     WY_Field(){memset(m_Name,0,MAX_FIELD_NAME_LEN);m_Type=0;m_Length=0;}
     ~WY_Field(){;}
     void SetType(int Type);
     void SetName(String Name);
     void SetLength(int Length);   //设置字段长度,非ftBUFFER和ftSTRING类型调用此函数无效
     FIELD_TYPE  GetType(){return FIELD_TYPE(m_Type);}        //获取字段类型
     int         GetLength(){return m_Length;}      //获取字段长度
     String      GetName(){return String(m_Name);}        //获取字段名字
     int         WriteToBuffer(char * lpDesData); //将整个结构写入缓冲区
     void        WriteToStream(TMemoryStream * Stream);
     int         ReadFromBuffer(char * lpDesData);
     int         GetSize(){return MAX_FIELD_NAME_LEN+sizeof(int)+sizeof(int);}  //获取Field类型的实际大小
};



class WYDB_File
{
private:
   AList<WY_Field> * lpFieldList; //字段定义列表
   TStringList *   lpDataRecord; //保存记录数据
   TMemoryStream * lpDataStream; //保存数据的数据流
   int             IndexOfFieldName(String FieldName);
   int             GetFieldBufferStartPos(int FieldIndex);
protected:
   tagDB_Head Head;
   void  ReadDataToMem();     //从流中读取字段信息到lpFieldList,lpDataRecord
   void  SaveMemToStream();     // 将数据写回到流中
   int   GetRecordLength();     //
   bool  m_IsOpened; //打开中
   int   m_CurrentRecordNO;
public:
  String LastError;
public:
  __fastcall WYDB_File();
  __fastcall ~WYDB_File();
  bool __fastcall LoadFromFile(String FileName);
  bool __fastcall SaveToFile(String FileName);
  bool __fastcall LoadFromStream(TMemoryStream * DataStream);
  bool __fastcall SaveToStream(TMemoryStream * DataStream);
  int     GetFieldCount(){return lpFieldList->Count();}
  int     GetRecordCount(){return lpDataRecord->Count;}
  String  GetRecordAsString(String FieldName,int NO=-1);  //获取当前记录某个字段的内容,按String方式
  String  GetRecordAsString(int FieldIndex,int NO=-1);  //获取当前记录某个字段的内容,按String方式
  int     GetRecordAsInteger(String FieldName,int NO=-1); //获取当前记录某个字段的内容,按int方式
  int     GetRecordAsInteger(int FieldIndex,int NO=-1);
  int     GetRecordAsBuffer(String FieldName,char * lpOutBuffer,int NO=-1);  //按缓冲区方式读取当前记录某个字段的数据
  int     GetRecordAsBuffer(int FieldIndex,char * lpOutBuffer,int NO=-1);
  bool    SetRecordAsString(String FieldName,String Data,int NO=-1);  //刷新当前记录某个字段的内容,按String方式
  bool    SetRecordAsInteger(String FieldName,int Data,int NO=-1); //刷新当前记录某个字段的内容,按int方式
  bool    SetRecordAsBuffer(String FieldName,char * lpInBuffer,int Len,int NO=-1);//刷新某个记录字段按buffer方式
  void    SetRecordNO(int NO){m_CurrentRecordNO =NO;} //设置当前记录号
  int     GetRecordNO(){return m_CurrentRecordNO;} // 获取当前记录号
  bool    AddField(String Name,int Type,int Length); //添加一个字段
  String  GetDBName(){return Head.DB_Name;}
  void    SetDBName(String DBName);
  WY_Field * GetField(int Index){return lpFieldList->At(Index);}
  void    Close(){lpDataStream->Clear();lpFieldList->Clear();lpDataRecord->Clear();memset(&Head,0,sizeof(Head));}
  bool    IsOpen(){return m_IsOpened;}
  void    Append();   //添加一条空记录
  void    Last(); //跳到最后一个记录
  void    Next(); //跳到下一个记录
  void    Prev(); //跳到上一个记录
  void    First(); //跳到第一个记录
};

//---------------------------------------------------------------------------
#endif
