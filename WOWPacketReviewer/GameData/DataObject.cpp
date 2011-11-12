//---------------------------------------------------------------------------


#pragma hdrstop

#include "DataObject.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)


DataObject::DataObject()
{
}

DataObject::~DataObject()
{
}

int     DataObject::AsInt()
{
    return      m_DataStringMap.AsInt();
}

float   DataObject::AsFloat()
{
    return      m_DataStringMap.AsFloat();
}

void    DataObject::SetValue(String value)
{
    m_DataStringMap.SetData(value);
}

String  DataObject::AsString()
{
    return  m_DataStringMap.AsString();    
}

void    DataObject::Clear()
{
    m_DataStringMap.Clear();
    m_NextDataObj.clear();
}

shared_ptr<DataObject>  DataObject::GetDataObject(String key)
{
    key = key.UpperCase();
    map<String, shared_ptr<DataObject> >::iterator it = m_NextDataObj.find(key);
    if(it == m_NextDataObj.end())
    {
        shared_ptr<DataObject> obj(new DataObject);
        m_NextDataObj[key] = obj;
        m_NextDataObj[key]->SetKeyName(key);
        m_NextDataObj[key]->SetFullPath(m_FullPath + "/" + key );
        return      m_NextDataObj[key];
    }

    return  it->second;
}

void    DataObject::SetDataObject(String key, shared_ptr<DataObject> value)
{
    key = key.UpperCase();
    m_NextDataObj[key] = value;
}

bool    DataObject::HaveDataObject(String key)
{
    key = key.UpperCase();
    map<String, shared_ptr<DataObject> >::iterator it = m_NextDataObj.find(key);
    if(it == m_NextDataObj.end())
    {
        return  false;
    }

    return  true;
}

void	DataObject::DeleteDataObject(String key)
{
	m_NextDataObj.erase(key);
}

int     DataObject::GetChildCount()
{
    return  m_NextDataObj.size();
}

shared_ptr<DataObject>  DataObject::GetAt(int index)
{
    int curIndex = 0;
    for(map<String, shared_ptr<DataObject> >::iterator it = m_NextDataObj.begin();
            it != m_NextDataObj.end();
            it++, curIndex++)
    {
        if(curIndex == index)
        {
            return  it->second;
        }
    }

    return  shared_ptr<DataObject>();
}
