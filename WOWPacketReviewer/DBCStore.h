//---------------------------------------------------------------------------

#ifndef DBCStoreH
#define DBCStoreH
//---------------------------------------------------------------------------
#include <list>
#include "DBCFileLoader.h"

template<class T>
class DBCStorage
{
    typedef std::list<char*> StringPoolList;
    public:
        explicit DBCStorage(const char *f) : nCount(0), nRecordCount(0), fieldCount(0), fmt(f), indexTable(NULL), listTable(NULL), m_dataTable(NULL) { }
        ~DBCStorage() { Clear(); }

        T const* LookupEntry(uint32 id) const { return (id>=nCount)?NULL:indexTable[id]; }
        T const* LookupByIndex(uint32 index) const { return (index>=nRecordCount)?NULL:listTable[index]; }
        uint32  GetNumRows() const { return nCount; }
        uint32  GetRecordCount() const { return nRecordCount; }
        char const* GetFormat() const { return fmt; }
        uint32 GetFieldCount() const { return fieldCount; }

        bool Load(char const* fn)
        {
            DBCFileLoader dbc;
            // Check if load was sucessful, only then continue
            if(!dbc.Load(fn, fmt))
                return false;

            fieldCount = dbc.GetCols();
            m_dataTable = (T*)dbc.AutoProduceData(fmt,nCount, (char**&)indexTable, (char**&)listTable);
            nRecordCount = dbc.GetNumRows();
            m_stringPoolList.push_back(dbc.AutoProduceStrings(fmt,(char*)m_dataTable));

            // error in dbc file at loading if NULL
            return indexTable!=NULL;
        }

        bool LoadStringsFrom(char const* fn)
        {
            // DBC must be already loaded using Load
            if(!indexTable)
                return false;

            DBCFileLoader dbc;
            // Check if load was successful, only then continue
            if(!dbc.Load(fn, fmt))
                return false;

            m_stringPoolList.push_back(dbc.AutoProduceStrings(fmt,(char*)m_dataTable));

            return true;
        }

        void Clear()
        {
            if (!indexTable)
                return;

            delete[] ((char*)indexTable);
            indexTable = NULL;
            delete[] ((char*)listTable);
            listTable = NULL;
            delete[] ((char*)m_dataTable);
            m_dataTable = NULL;

            while(!m_stringPoolList.empty())
            {
                delete[] m_stringPoolList.front();
                m_stringPoolList.pop_front();
            }
            nCount = 0;
            nRecordCount = 0;
        }

    private:
        uint32 nCount;
        uint32 nRecordCount;
        uint32 fieldCount;
        char const* fmt;
        T** indexTable;
        T** listTable;
        T* m_dataTable;
        StringPoolList m_stringPoolList;
};

#endif
