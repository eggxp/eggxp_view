//---------------------------------------------------------------------------

#ifndef DBCStructureInfoH
#define DBCStructureInfoH
//---------------------------------------------------------------------------
#include "DBCStructure.h"
#include "DBCStores.h"
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "cgauges.h"


struct tagDBCTableContent {
    vector<String>  Columns;
    String          Fmt;
};

void    InitTableColumns();
void    GetTableColumns(String tableName, TStrings * output);
void    GetTableColumnNames(TStrings * output);
void    OutputValuesToList(String tableName, TListView * curList, TCGauge *progress);
int     GetStoresCountByName(String tableName);
void    AddDBCToStringList(String tableName, int index, TStrings * output);
void    AddDBCToListItem(String tableName, int index, TListItem * curItem);
map<String, tagDBCTableContent >    *GetTableColumns();

#endif
