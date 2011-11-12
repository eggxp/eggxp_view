//---------------------------------------------------------------------------

#ifndef PackBuferH
#define PackBuferH
//---------------------------------------------------------------------------

#include    <vcl.h>
#include    "CommFunc.h"

class   PackBufer
{
private:
    String          m_Buffer;
    int             m_CurBuferPos;
public:
    PackBufer(int maxBuf = 8192);
    ~PackBufer();
    
    char        *   GetResult();
    int             GetResultLength();

    void            Reset();

    bool            Put(char *lpData, int len);    
};

#endif
