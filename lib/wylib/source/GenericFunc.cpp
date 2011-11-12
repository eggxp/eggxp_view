//---------------------------------------------------------------------------
#include <windows.h>
#include <shlobj.h>
#pragma hdrstop

#include "GenericFunc.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

DWORD iRandSeed;
//---------------------------------------------------------------------------
DWORD g_outkey[16][2] = {0}; /*输出的key*/
DWORD g_bufkey[2] = {0};     /*形成起始密钥*/
                             /*实现时多采用查表方式,下面是定义的供查找用的表*/
static BYTE wz_lefttable[16] = {1,1,2,2,2,2,2,2,1,2,2,2,2,2,2,1};
static DWORD wz_leftandtab[3] = {0x0, 0x80000000, 0xc0000000};
static BYTE wz_keyleft[28] =
{
  57,49,41,33,25,17,9,1,58,50,42,34,26,18,
  10,2,59,51,43,35,27,19,11,3,60,52,44,36
};
static BYTE wz_keyright[28] =
{
  63,55,47,39,31,23,15,7,62,54,46,38,30,22,
  14,6,61,53,45,37,29,21,13,5,28,20,12,4
};
static BYTE wz_keychoose[48] =
{
  14,17,11,24,1,5,3,28,15,6,21,10,
  23,19,12,4,26,8,16,7,27,20,13,2,
  41,52,31,37,47,55,30,40,51,45,33,48,
  44,49,39,56,34,53,46,42,50,36,29,32
};
static BYTE wz_pc4[64] =                    /*最后一次调整*/
{
  40,8,48,16,56,24,64,32, 39,7,47,15,55,23,63,31,
  38,6,46,14,54,22,62,30, 37,5,45,13,53,21,61,29,
  36,4,44,12,52,20,60,28, 35,3,43,11,51,19,59,27,
  34,2,42,10,50,18,58,26, 33,1,41,9,49,17,57,25
};
static BYTE  wz_pc1[64] =                   /*第一次转换时用*/
{
  58,50,42,34,26,18,10,2,60,52,44,36,28,20,12,4,
  62,54,46,38,30,22,14,6,64,56,48,40,32,24,16,8,
  57,49,41,33,25,17,9,1,59,51,43,35,27,19,11,3,
  61,53,45,37,29,21,13,5,63,55,47,39,31,23,15,7
};
static BYTE wz_pc3[32] =
{
  16,7,20,21, 29,12,28,17, 1,15,23,26,
  5,18,31,10, 2,8,24,14, 32,27,3,9,
  19,13,30,6, 22,11,4,25
} ;
static DWORD  wz_pc2[64] =
{
  0x80000000L,0x40000000L,0x20000000L,0x10000000L, 0x8000000L,
  0x4000000L, 0x2000000L, 0x1000000L, 0x800000L, 0x400000L,
  0x200000L, 0x100000L,  0x80000L, 0x40000L, 0x20000L,0x10000L,
  0x8000L, 0x4000L, 0x2000L, 0x1000L, 0x800L, 0x400L, 0x200L,
  0x100L, 0x80L,0x40L,0x20L, 0x10L, 0x8L, 0x4L, 0x2L, 0x1L,
  0x80000000L,0x40000000L,0x20000000L,0x10000000L, 0x8000000L,
  0x4000000L, 0x2000000L, 0x1000000L, 0x800000L, 0x400000L,
  0x200000L, 0x100000L,  0x80000L, 0x40000L, 0x20000L, 0x10000L,
  0x8000L, 0x4000L, 0x2000L, 0x1000L, 0x800L, 0x400L, 0x200L,
  0x100L, 0x80L, 0x40L,0x20L, 0x10L, 0x8L,  0x4L, 0x2L, 0x1L,
};
static BYTE exptab3[48] =
{
  32,1,2,3,4,5,4,5,6,7,8,9,8,9,10,11,12,13,
  12,13,14,15,16,17,16,17,18,19,20,21,
  20,21,22,23,24,25,24,25,26,27,28,29,
  28,29,30,31,32,1
};
static BYTE SP[8][64] =
{
  {
    0xe,0x0,0x4,0xf,0xd,0x7,0x1,0x4,0x2,0xe,0xf,0x2,0xb,
    0xd,0x8,0x1,0x3,0xa,0xa,0x6,0x6,0xc,0xc,0xb,0x5,0x9,
    0x9,0x5,0x0,0x3,0x7,0x8,0x4,0xf,0x1,0xc,0xe,0x8,0x8,
    0x2,0xd,0x4,0x6,0x9,0x2,0x1,0xb,0x7,0xf,0x5,0xc,0xb,
    0x9,0x3,0x7,0xe,0x3,0xa,0xa,0x0,0x5,0x6,0x0,0xd
  },

  {
    0xf,0x3,0x1,0xd,0x8,0x4,0xe,0x7,0x6,0xf,0xb,0x2,0x3,
    0x8,0x4,0xf,0x9,0xc,0x7,0x0,0x2,0x1,0xd,0xa,0xc,0x6,
    0x0,0x9,0x5,0xb,0xa,0x5,0x0,0xd,0xe,0x8,0x7,0xa,0xb,
    0x1,0xa,0x3,0x4,0xf,0xd,0x4,0x1,0x2,0x5,0xb,0x8,0x6,
    0xc,0x7,0x6,0xc,0x9,0x0,0x3,0x5,0x2,0xe,0xf,0x9
  },
  {
    0xa,0xd,0x0,0x7,0x9,0x0,0xe,0x9,0x6,0x3,0x3,0x4,0xf,
    0x6,0x5,0xa,0x1,0x2,0xd,0x8,0xc,0x5,0x7,0xe,0xb,0xc,
    0x4,0xb,0x2,0xf,0x8,0x1,0xd,0x1,0x6,0xa,0x4,0xd,0x9,
    0x0,0x8,0x6,0xf,0x9,0x3,0x8,0x0,0x7,0xb,0x4,0x1,0xf,
    0x2,0xe,0xc,0x3,0x5,0xb,0xa,0x5,0xe,0x2,0x7,0xc
  },
  {
    0x7,0xd,0xd,0x8,0xe,0xb,0x3,0x5,0x0,0x6,0x6,0xf,0x9,
    0x0,0xa,0x3,0x1,0x4,0x2,0x7,0x8,0x2,0x5,0xc,0xb,0x1,
    0xc,0xa,0x4,0xe,0xf,0x9,0xa,0x3,0x6,0xf,0x9,0x0,0x0,
    0x6,0xc,0xa,0xb,0xa,0x7,0xd,0xd,0x8,0xf,0x9,0x1,0x4,
    0x3,0x5,0xe,0xb,0x5,0xc,0x2,0x7,0x8,0x2,0x4,0xe
  },
  {
    0x2,0xe,0xc,0xb,0x4,0x2,0x1,0xc,0x7,0x4,0xa,0x7,0xb,
    0xd,0x6,0x1,0x8,0x5,0x5,0x0,0x3,0xf,0xf,0xa,0xd,0x3,
    0x0,0x9,0xe,0x8,0x9,0x6,0x4,0xb,0x2,0x8,0x1,0xc,0xb,
    0x7,0xa,0x1,0xd,0xe,0x7,0x2,0x8,0xd,0xf,0x6,0x9,0xf,
    0xc,0x0,0x5,0x9,0x6,0xa,0x3,0x4,0x0,0x5,0xe,0x3
  },
  {
    0xc,0xa,0x1,0xf,0xa,0x4,0xf,0x2,0x9,0x7,0x2,0xc,0x6,
    0x9,0x8,0x5,0x0,0x6,0xd,0x1,0x3,0xd,0x4,0xe,0xe,0x0,
    0x7,0xb,0x5,0x3,0xb,0x8,0x9,0x4,0xe,0x3,0xf,0x2,0x5,
    0xc,0x2,0x9,0x8,0x5,0xc,0xf,0x3,0xa,0x7,0xb,0x0,0xe,
    0x4,0x1,0xa,0x7,0x1,0x6,0xd,0x0,0xb,0x8,0x6,0xd
  },
  {
    0x4,0xd,0xb,0x0,0x2,0xb,0xe,0x7,0xf,0x4,0x0,0x9,0x8,
    0x1,0xd,0xa,0x3,0xe,0xc,0x3,0x9,0x5,0x7,0xc,0x5,0x2,
    0xa,0xf,0x6,0x8,0x1,0x6,0x1,0x6,0x4,0xb,0xb,0xd,0xd,
    0x8,0xc,0x1,0x3,0x4,0x7,0xa,0xe,0x7,0xa,0x9,0xf,0x5,
    0x6,0x0,0x8,0xf,0x0,0xe,0x5,0x2,0x9,0x3,0x2,0xc
  },
  {
    0xd,0x1,0x2,0xf,0x8,0xd,0x4,0x8,0x6,0xa,0xf,0x3,0xb,
    0x7,0x1,0x4,0xa,0xc,0x9,0x5,0x3,0x6,0xe,0xb,0x5,0x0,
    0x0,0xe,0xc,0x9,0x7,0x2,0x7,0x2,0xb,0x1,0x4,0xe,0x1,
    0x7,0x9,0x4,0xc,0xa,0xe,0x8,0x2,0xd,0x0,0xf,0x6,0xc,
    0xa,0x9,0xd,0x0,0xf,0x3,0x3,0x5,0x5,0x6,0x8,0xb
  }
};

int handle_data(DWORD *left , BYTE choice);
int makedata(DWORD  *left ,DWORD  *right ,DWORD number);
int makefirstkey( DWORD *keyP );
int makekey(  DWORD *keyleft,DWORD *keyright ,DWORD number);

/*函数实现*/
int DdesN(BYTE *data, BYTE **key, DWORD n_key,DWORD readlen)
{
  int i ;
  for ( i = n_key ; i > 0 ; i--)
  {
    Ddes(data,key[i-1],readlen);
  }
  return SUCCESS;
}

int desN(BYTE *data, BYTE **key, DWORD n_key,DWORD readlen)
{
  DWORD i;
  for ( i = 0 ; i < n_key ; i++)
  {
    des(data,key[i],readlen);
  }
  return SUCCESS;
}

int des3(BYTE *data, BYTE *key,DWORD n ,DWORD readlen)
{
  DWORD i, j;

  if(((readlen / 8) * 8) != readlen)
    return 0;
  makefirstkey((DWORD*)key) ;  /*产生密钥*/
  for ( i = 0 ; i < n ; i++)
  {
    for ( j = 0 ; j < readlen ; j += 8)
    {
      handle_data( (DWORD*)&data[j], DESENCRY );
    }
  }
  return SUCCESS;
}

int Ddes3(BYTE *data,BYTE *key,DWORD n ,DWORD readlen)
{
  DWORD i, j;

  if(((readlen / 8) * 8) != readlen)
    return 0;
  makefirstkey((DWORD*)key) ;  /*产生密钥*/
  for ( i = 0 ; i < n ; i++)
  {
    for ( j = 0 ; j < readlen ; j += 8)
    {
      handle_data( (DWORD*)&data[j], DESDECRY );
    }
  }
  return SUCCESS;
}

int des(BYTE *data, BYTE *key,int readlen)
{
  int i;

  if(((readlen / 8) * 8) != readlen)
    return 0;
  makefirstkey((DWORD*)key) ;  /*产生密钥*/
  for ( i = 0 ; i < readlen ; i += 8)
  {
    handle_data( (DWORD*)&data[i], DESENCRY );
  }
  return SUCCESS;
}

int Ddes(BYTE *data,BYTE *key,int readlen)
{
  int i;

  if(((readlen / 8) * 8) != readlen)
    return 0;
  makefirstkey((DWORD*)key) ;
  for ( i = 0 ; i < readlen ; i += 8)
  {
    handle_data( (DWORD*)&data[i] ,DESDECRY);
  }
  return SUCCESS;
}

int handle_data(DWORD *left , BYTE choice)
{
  int  number, j;
  DWORD *right = &left[1] ;
  DWORD tmp;
  DWORD tmpbuf[2] = { 0 };

  /*第一次调整wz_pc1[64]*/
  for ( j = 0 ; j < 64 ; j++)
  {
    if (j < 32 )
    {
      if ( wz_pc1[j] > 32)/*属于right*/
      {
        if ( *right&wz_pc2[wz_pc1[j]-1] )
        {
          tmpbuf[0] |= wz_pc2[j] ;
        }
      }
      else
      {
        if ( *left&wz_pc2[wz_pc1[j]-1] )
        {
          tmpbuf[0] |= wz_pc2[j] ;
        }
      }
    }
    else
    {
      if ( wz_pc1[j] > 32)/*属于right*/
      {
        if ( *right&wz_pc2[wz_pc1[j]-1] )
        {
          tmpbuf[1] |= wz_pc2[j] ;
        }
      }
      else
      {
        if ( *left&wz_pc2[wz_pc1[j]-1] )
        {
          tmpbuf[1] |= wz_pc2[j] ;
        }
      }
    }
  }
  *left  = tmpbuf[0] ;
  *right = tmpbuf[1];
  tmpbuf[0] = 0 ;
  tmpbuf[1] = 0 ;
  switch( choice )
  {
    case DESENCRY:
      for ( number = 0 ; number < 16 ; number++)
      {
        makedata( left , right , (DWORD)number) ;
      }
      break;
    case DESDECRY:
      for ( number = 15 ; number >= 0 ; number--)
      {
        makedata( left , right ,(DWORD)number) ;
      }
      break;
    default:
          break;
  }

  /*最后一轮操作不交换左右值*/
  tmp = *left ;
  *left = *right ;
  *right = tmp ;

  /*最后一次调整wz_pc4[64]*/
  for ( j = 0 ; j < 64 ; j++)
  {
    if (j < 32 )
    {
      if ( wz_pc4[j] > 32)/*属于right*/
      {
        if ( *right&wz_pc2[wz_pc4[j]-1] )
        {
          tmpbuf[0] |= wz_pc2[j] ;
        }
      }
      else
      {
        if ( *left&wz_pc2[wz_pc4[j]-1] )
        {
          tmpbuf[0] |= wz_pc2[j] ;
        }
      }
    }
    else
    {
      if ( wz_pc4[j] > 32)/*属于right*/
      {
        if ( *right&wz_pc2[wz_pc4[j]-1] )
        {
          tmpbuf[1] |= wz_pc2[j] ;
        }
      }
      else
      {
        if ( *left&wz_pc2[wz_pc4[j]-1] )
        {
          tmpbuf[1] |= wz_pc2[j] ;
        }
      }
    }
  }

  *left =  tmpbuf[0] ;
  *right = tmpbuf[1];

  return SUCCESS;
}

int makedata(DWORD  *left ,DWORD  *right ,DWORD number)
{
  int j;
  DWORD oldright = *right;
  BYTE rexpbuf[8] = {0};
  DWORD datatmp;
  DWORD exp[2] = {0};

  //由32扩充至48位
  for ( j = 0 ; j < 48 ; j++)
  {
    /*两个32位，每个存放24位*/
    if ( j < 24 )
    {
      if ( *right&wz_pc2[exptab3[j]-1] )
      {
        exp[0] |= wz_pc2[j] ;
      }
    }
    else
    {
      if ( *right&wz_pc2[exptab3[j]-1] )
      {
        exp[1] |= wz_pc2[j-24] ;
      }
    }
  }

  for ( j = 0 ; j < 2 ; j++)
  {
    exp[j] ^= g_outkey[number][j] ;
  }

  /*由48－>32*/

  exp[1] >>= 8 ;
  rexpbuf[7] = (BYTE) (exp[1]&0x0000003fL) ;
  exp[1] >>= 6 ;
  rexpbuf[6] = (BYTE) (exp[1]&0x0000003fL) ;
  exp[1] >>= 6 ;
  rexpbuf[5] = (BYTE) (exp[1]&0x0000003fL) ;
  exp[1] >>= 6 ;
  rexpbuf[4] = (BYTE) (exp[1]&0x0000003fL) ;
  exp[0]  >>=  8 ;
  rexpbuf[3] = (BYTE) (exp[0]&0x0000003fL) ;
  exp[0] >>= 6 ;
  rexpbuf[2] = (BYTE) (exp[0]&0x0000003fL) ;
  exp[0] >>= 6 ;
  rexpbuf[1] = (BYTE) (exp[0]&0x0000003fL) ;
  exp[0] >>= 6 ;
  rexpbuf[0] = (BYTE) (exp[0]&0x0000003fL) ;
  exp[0] = 0 ;
  exp[1] = 0 ;

  /*由48－> 32*/

  *right = 0 ;
  for ( j = 0 ; j < 7 ; j++)
  {
    *right |= SP[j][rexpbuf[j]] ;
    *right <<= 4 ;
  }
  *right |= SP[j][rexpbuf[j]] ;

  /*又要换位了*/
  datatmp = 0;
  for ( j = 0 ; j < 32 ; j++)
  {
    if ( *right&wz_pc2[wz_pc3[j]-1] )
    {
      datatmp |= wz_pc2[j] ;
    }
  }
  *right = datatmp ;

  /*一轮结束收尾操作*/
  *right ^= *left;
  *left = oldright;

  return SUCCESS;
}

int makefirstkey( DWORD *keyP )
{
  DWORD key[2] = {0};
  DWORD *Pkey ;
  DWORD *Pbufkey ;
  int j;
  Pbufkey = (DWORD*)g_bufkey ;
  Pkey = (DWORD*)key;

  memset((BYTE*)g_bufkey,0,sizeof(g_bufkey));
  memcpy((BYTE*)&key,(BYTE*)keyP ,8) ;
  memset((BYTE*)g_outkey,0,sizeof(g_outkey));
  for(  j = 0 ; j < 28 ; j++)
  {
    if ( wz_keyleft[j] > 32 )
    {
      if ( Pkey[1]&wz_pc2[wz_keyleft[j]-1] )
      {
        Pbufkey[0] |= wz_pc2[j] ;
      }
    }
    else
    {
      if ( Pkey[0]&wz_pc2[wz_keyleft[j]-1] )
      {
        Pbufkey[0] |= wz_pc2[j] ;
      }
    }

    if ( wz_keyright[j] > 32 )
    {
      if ( Pkey[1]&wz_pc2[wz_keyright[j]-1] )
      {
        Pbufkey[1] |= wz_pc2[j];
      }
    }
    else
    {
      if ( Pkey[0]&wz_pc2[wz_keyright[j]-1] )
      {
        Pbufkey[1] |= wz_pc2[j];
      }
    }
  }
  for (j = 0 ; j < 16 ; j++)
  {
    makekey(&Pbufkey[0],&Pbufkey[1] , j ) ;
  }
  return SUCCESS;
}

int makekey(  DWORD *keyleft,DWORD *keyright ,DWORD number)/*输入密钥的地址，一个32位的*/
{
  DWORD tmpkey[2] ={0};
  DWORD *Ptmpkey = (DWORD*)tmpkey;
  DWORD *Poutkey = (DWORD*)&g_outkey[number];
  int j;
  memset((BYTE*)tmpkey,0,sizeof(tmpkey));
  /*要最高的一位或两位*/
  *Ptmpkey = *keyleft&wz_leftandtab[wz_lefttable[number]] ;
  Ptmpkey[1] = *keyright&wz_leftandtab[wz_lefttable[number]] ;
  if ( wz_lefttable[number] == 1)
  {
    *Ptmpkey >>= 27;
    Ptmpkey[1] >>= 27;
  }
  else
  {
    *Ptmpkey >>= 26;
    Ptmpkey[1] >>= 26;
  }
  Ptmpkey[0] &= 0xfffffff0;
  Ptmpkey[1] &= 0xfffffff0;
  /*得到高位的值*/
  *keyleft <<= wz_lefttable[number] ;
  *keyright <<= wz_lefttable[number] ;
  *keyleft |= Ptmpkey[0] ;
  *keyright |= Ptmpkey[1] ;
  Ptmpkey[0] = 0;
  Ptmpkey[1] = 0;

  /*从56位中选出48位,3个16位*/
  for ( j = 0 ; j < 48 ; j++)
  {
    if ( j < 24 )
    {
      if ( *keyleft&wz_pc2[wz_keychoose[j]-1])
      {
        Poutkey[0] |= wz_pc2[j] ;
      }
    }

    else /*j>=24*/
    {
      if ( *keyright&wz_pc2[(wz_keychoose[j]-28)])
      {
        Poutkey[1] |= wz_pc2[j-24] ;
      }
    }
  }
  return SUCCESS;
}
//---------------------------------------------------------------------------
void Xor_Add(LPSTR szBuffer, int ulFileLen, LPSTR szPassword, int iPasswordLen)
{
  LPSTR szTempStr = szPassword;
  int uiSize;
  BYTE ucByte = 0, ucTemp;
  for(uiSize=0; uiSize<ulFileLen;)
  {
    ucTemp = *szBuffer;
    szBuffer[0] ^= szTempStr[0];
    szBuffer[0] ^= ucByte;
    ucByte += ucTemp;
    szBuffer[0] ^= uiSize;
    szBuffer[0] ^= 0x78;
    szBuffer[0] ^= 0x05;
    szBuffer[0] ^= 0x27;
    szTempStr ++;
    szBuffer ++;
    uiSize ++;
    if(!(uiSize % iPasswordLen))
      szTempStr = szPassword;
  }
}

void Xor_Sub(LPSTR szBuffer, int ulFileLen, LPSTR szPassword, int iPasswordLen)
{
  LPSTR szTempStr = szPassword;
  int uiSize;
  BYTE ucByte = 0, ucTemp = 0;
  for(uiSize=0;uiSize<ulFileLen;)
  {
    szBuffer[0] ^= 0x78;
    szBuffer[0] ^= 0x05;
    szBuffer[0] ^= 0x27;
    szBuffer[0] ^= uiSize;
    ucByte += ucTemp;
    szBuffer[0] ^= ucByte;
    szBuffer[0] ^= szTempStr[0];
    ucTemp = szBuffer[0];
    szTempStr ++;
    szBuffer ++;
    uiSize ++;
    if(!(uiSize % iPasswordLen))
      szTempStr = szPassword;
  }
}

//---------------------------------------------------------------------------
BOOL DirExists(LPSTR lpPath)
{
  int Code;
  Code = GetFileAttributes(lpPath);
  return (Code != -1) && (FILE_ATTRIBUTE_DIRECTORY && Code != 0);
}
//---------------------------------------------------------------------------
//SHBrowseForFolder控件在初始化或选择改变后的回调函数
//---------------------------------------------------------------------------
static int __stdcall BrowseCtrlCallback(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
  if(uMsg == BFFM_INITIALIZED)
    SendMessage(hwnd,BFFM_SETSELECTION, TRUE, lpData);
  return 0;
}
//---------------------------------------------------------------------------
BOOL BrowseFolder(HWND hParent, LPCTSTR lpTitle, LPTSTR DirName)
{
  LPMALLOC pMalloc;
  BOOL     bOk;
  char     RootDir[MAX_PATH + 1];
  if (SHGetMalloc (&pMalloc)!= NOERROR)
    return FALSE;

  BROWSEINFO bInfo;
  LPITEMIDLIST pidl;

  ZeroMemory ( (PVOID) &bInfo,sizeof (BROWSEINFO));

  bInfo.pidlRoot = NULL;      // in default, Using Desktop folder as Root folder

  RootDir[0] = 0;

  bInfo.hwndOwner = hParent;
  bInfo.pszDisplayName = RootDir;
  bInfo.lpszTitle = lpTitle == NULL || lpTitle[0]==0 ? "Open":lpTitle;
  bInfo.ulFlags = BIF_RETURNFSANCESTORS|BIF_RETURNONLYFSDIRS;
  if(DirExists(DirName))
    bInfo.lpfn = BrowseCtrlCallback;
  bInfo.lParam = (LPARAM)DirName;
  if ((pidl = ::SHBrowseForFolder(&bInfo)) == NULL)
     return FALSE;

  bOk = ::SHGetPathFromIDList(pidl, DirName);

  pMalloc ->Free(pidl);
  pMalloc ->Release();
  return bOk;
}

//---------------------------------------------------------------------------
//@System@@RandInt$qqrv:
//                imul    edx, ds:RandSeed, 8088405h
//                inc     edx
//                mov     ds:RandSeed, edx
//                mul     edx
//                mov     eax, edx
//                retn
//---------------------------------------------------------------------------
DWORD __fastcall MyRandInt(DWORD i)
{
  iRandSeed = iRandSeed * 0x8088405 + 1;
  return Int64ShrlMod32(i * UINT64(iRandSeed), 32);
}

