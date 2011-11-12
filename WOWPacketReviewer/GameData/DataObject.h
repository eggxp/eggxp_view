//---------------------------------------------------------------------------

#ifndef DataObjectH
#define DataObjectH
//---------------------------------------------------------------------------
#include <boost/shared_ptr.hpp>
#include <VCL.h>
#include <map>

#include "Log4Me.h"
using namespace std;
using boost::shared_ptr;

#define     BASE_INT_INIT       0x0ABBCCDD

class  DataSaveType
{
private:
	String  m_BaseData;
    int64  m_ToInt;
    float   m_ToFloat;
    void    ResetToInitState()
    {
        m_ToInt = BASE_INT_INIT;
        m_ToFloat = 0;
    }
public:
    DataSaveType()
    {
        ResetToInitState();
    }

    int64  AsInt()
    {
        if(m_ToInt == BASE_INT_INIT)
        {
			m_ToInt = StrToUint64Def(m_BaseData, 0);
        }
        return  m_ToInt;
    }
    void    SetData(String value)
    {
        m_BaseData = value;
        ResetToInitState();
    };
    String  AsString()
    {
        return  m_BaseData;
    }
    float   AsFloat()
    {
        if(m_BaseData == "")
            return 0;
        if(m_ToFloat == 0)
        {
            m_ToFloat = m_BaseData.ToDouble();
        }
        return      m_ToFloat;
    }
    void    Clear()
    {
        m_BaseData = "";
        ResetToInitState();
    }
};

class DataObject
{
private:
    DataSaveType                               m_DataStringMap;
    map<String, shared_ptr<DataObject> >       m_NextDataObj;
    String                                     m_KeyName;
    String                                     m_FullPath;
public:
    DataObject();
    ~DataObject();

    int     AsInt();
    float   AsFloat();

    void    SetValue(String value);
    String  AsString();

    void    Clear();

    shared_ptr<DataObject>  GetDataObject(String key);
    bool                    HaveDataObject(String key);
	void    SetDataObject(String key, shared_ptr<DataObject> value);
	void	DeleteDataObject(String key);

    int     GetChildCount();
    shared_ptr<DataObject>  GetAt(int index);
    GEN_GET_SET(String, KeyName)
    GEN_GET_SET(String, FullPath)
};



#endif
