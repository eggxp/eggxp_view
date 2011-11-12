//---------------------------------------------------------------------------


#pragma hdrstop

#include "PackBuffer.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

PackBufer::PackBufer(int maxBuf)
{
    m_Buffer.SetLength(maxBuf);
    Reset();
}

PackBufer::~PackBufer()
{
}

char        *   PackBufer::GetResult()
{
    return  m_Buffer.c_str();
}

int             PackBufer::GetResultLength()
{
    return  m_CurBuferPos;
}

void            PackBufer::Reset()
{
    ZeroMemory(m_Buffer.c_str(), m_Buffer.Length());
    m_CurBuferPos = 0;
}

bool            PackBufer::Put(char *lpData, int len)
{
    if(m_CurBuferPos + len >= m_Buffer.Length()-1)
        return false;

    WriteBuf(m_Buffer.c_str(), m_CurBuferPos, lpData, len);
    return  true;
}
