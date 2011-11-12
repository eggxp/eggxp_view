//---------------------------------------------------------------------------

#ifndef packreadH
#define packreadH
#include <vcl.h>
#include "MFSManager.h"
//---------------------------------------------------------------------------
class TMfsReader
{
private:
   TMFSManager MfsManage;
protected:

public:
  __fastcall TMfsReader();
  __fastcall ~TMfsReader();
  bool       LoadFromFile(String FileName,String Password);
  int        FileCount();
  bool       GetFileData(String FileName,TMemoryStream * DesBuf);
  bool       HavePassword();
};

#endif
