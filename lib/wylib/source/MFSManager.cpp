/***************************************************************************
 *  File name MFSManager.cpp                                               *
 *  Version:  3.00.03a                                                     *
 *  Author:   yypcn                                                        *
 *  Target:   .mfs Packages Manager.                                       *
 *                                                                         *
 *  History                                                                *
 *  01-22-2003    12:03pm  New version, all new!                           *
 *                                                                         *
 ***************************************************************************/

#include <math.h>
#include <stdio.h>
//#include <alloc.h>

#pragma hdrstop

#include "MFSManager.h"
#include "CryptoLib.h"
#include "zlib.h"

//void BaseXorAdd(unsigned char *szBuffer, int ulFileLen, char *szPassword, int iPasswordLen){}
//void BaseXorSub(unsigned char *szBuffer, int ulFileLen, char *szPassword, int iPasswordLen){}
//---------------------------------------------------------------------------
int _stdcall ZLibCheck(int code)
{
  int iResult;
  iResult = code;
  if(code < 0)
    throw code;
  return iResult;
}
//---------------------------------------------------------------------------
int _stdcall ZDecompress(LPCVOID inBuffer, int inSize, LPVOID &outBuffer, int &outSize, int outEstimate)
{
  z_stream zstream;
  int iResult, delta;
  ZeroMemory(&zstream, sizeof(z_stream));

  delta = (inSize + 255) | (!255);

  if(outEstimate == 0)
    outSize = delta;
  else
    outSize = outEstimate;

  outBuffer = malloc(outSize);
  try
  {
    zstream.next_in   = (LPBYTE)inBuffer;
    zstream.avail_in  = inSize;
    zstream.next_out  = (LPBYTE)outBuffer;
    zstream.avail_out = outSize;

    ZLibCheck(inflateInit(&zstream));

    __try
    {
      while(ZLibCheck(inflate(&zstream, Z_NO_FLUSH)) != Z_STREAM_END)
      {
        outSize += delta;
        outBuffer = realloc(outBuffer, outSize);

        zstream.next_out = LPBYTE(outBuffer) + zstream.total_out;
        zstream.avail_out = delta;
      }
    }
    __finally
    {
      ZLibCheck(inflateEnd(&zstream));
    }

    outBuffer = realloc(outBuffer, zstream.total_out);
    outSize = zstream.total_out;
    iResult = Z_OK;
  }
  catch(int code)
  {
    free(outBuffer);
    iResult = code;
  }
  return iResult;
}
//---------------------------------------------------------------------------
int _stdcall ZCompress(LPCVOID inBuffer, int inSize, LPVOID &outBuffer, int &outSize, TZCompressionLevel level)
{
  z_stream zstream;
  int iResult, delta = 256;
  static int ZLevels[] = { Z_NO_COMPRESSION, Z_BEST_SPEED, Z_DEFAULT_COMPRESSION, Z_BEST_COMPRESSION };

  ZeroMemory(&zstream, sizeof(z_stream));

  outSize = ((inSize + (inSize / 10) + 12) + 255) | (!255);
  outBuffer = malloc(outSize);

  try
  {
    zstream.next_in   = (LPBYTE)inBuffer;
    zstream.avail_in  = inSize;
    zstream.next_out  = (LPBYTE)outBuffer;
    zstream.avail_out = outSize;

    ZLibCheck(deflateInit(&zstream, ZLevels[level]));

    __try
    {
      while(ZLibCheck(deflate(&zstream, Z_FINISH)) != Z_STREAM_END)
      {
        outSize += delta;
        outBuffer = realloc(outBuffer, outSize);

        zstream.next_out  = LPBYTE(outBuffer) + zstream.total_out;
        zstream.avail_out = delta;
      }
    }
    __finally
    {
      ZLibCheck(deflateEnd(&zstream));
    }

    outBuffer = realloc(outBuffer, zstream.total_out);
    outSize = zstream.total_out;
    iResult = Z_OK;
  }
  catch(int code)
  {
    free(outBuffer);
    iResult = code;
  }
  return iResult;
}
//---------------------------------------------------------------------------
void _stdcall ZFreeBuffer(LPVOID pBuffer)
{
  if(pBuffer)
    free(pBuffer);
}
//---------------------------------------------------------------------------
BOOL _stdcall ZFileExists(LPCSTR FileName)
{
  HANDLE hFile;
  hFile = CreateFile(FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
  if(hFile == INVALID_HANDLE_VALUE)
    return FALSE;
  CloseHandle(hFile);
  return TRUE;
}
//---------------------------------------------------------------------------
__inline double _stdcall ZSqr(double x)
{
  return x * x;
}
//---------------------------------------------------------------------------
double _stdcall ZLn(double x)
{
  __asm fld     x;
  __asm fldln2;
  __emit__(0xd9, 0xc9);             // fxch    st(1);
  __asm fyl2x;
  __asm fstp    x;
  __asm wait;
  return x;
}
//---------------------------------------------------------------------------
DWORD dwZRandSeed;
//---------------------------------------------------------------------------
void _stdcall ZRandomize(void)
{
  SYSTEMTIME stTime;
  GetSystemTime(&stTime);
  dwZRandSeed = ((stTime.wHour * 60 + stTime.wMinute) * 60 + stTime.wSecond) * 1000 + stTime.wMilliseconds;
}
/****************************************************************************
 * @System@@RandInt$qqrv:
 *                 imul    edx, ds:RandSeed, 8088405h
 *                 inc     edx
 *                 mov     ds:RandSeed, edx
 *                 mul     edx
 *                 mov     eax, edx
 *                 retn
 ***************************************************************************/
DWORD _stdcall ZRandInt(DWORD i)
{
  dwZRandSeed = dwZRandSeed * 0x8088405 + 1;
  return Int64ShrlMod32(i * UINT64(dwZRandSeed), 32);
}
/****************************************************************************
 * dbl_45102C      dq 2.328306436538696e-10
 * @System@@RandExt$qqrv:
 *                 imul    edx, ds:RandSeed, 8088405h
 *                 inc     edx
 *                 mov     ds:RandSeed, edx
 *                 fld     ds:dbl_45102C      ; 2.328306436538696e-10
 *                 push    0
 *                 push    edx
 *                 fild    qword ptr [esp]
 *                 add     esp, 8
 *                 fmulp   st(1), st
 *                 retn
 ***************************************************************************/
double ZRandExt(void)
{
  static double two2neg32 = ((1.0 / 0x10000) / 0x10000);  // 2^-32
  dwZRandSeed = dwZRandSeed * 0x8088405 + 1;
  return dwZRandSeed * two2neg32;
}
//---------------------------------------------------------------------------
double _stdcall ZRandG(double Mean, double StdDev)
{
  double U1, S2;
  do
  {
    U1 = 2 * ZRandExt() - 1;
    S2 = ZSqr(U1) + ZSqr(2 * ZRandExt() - 1);
  }while(S2 >= 1);
  return sqrt(-2 * ZLn(S2) / S2) * U1 * StdDev + Mean;
}
//---------------------------------------------------------------------------
int _stdcall ZGetRand(int x)
{
  return int(floor(fabs(ZRandG(0, 0x000fffff)))) % x;
}
//---------------------------------------------------------------------------
void _stdcall SetRandDWord(LPDWORD lpValue)
{
  *(LPBYTE(lpValue) + 0) = ZGetRand(255);
  *(LPBYTE(lpValue) + 1) = ZGetRand(255);
  *(LPBYTE(lpValue) + 2) = ZGetRand(255);
  *(LPBYTE(lpValue) + 3) = ZGetRand(255);
}
/* ========================================================================= */
#define DO1(buf)  crc = crc_table[((int)crc ^ (*buf++)) & 0xff] ^ (crc >> 8);
#define DO2(buf)  DO1(buf); DO1(buf);
#define DO4(buf)  DO2(buf); DO2(buf);
#define DO8(buf)  DO4(buf); DO4(buf);
//---------------------------------------------------------------------------
DWORD _stdcall TMFSManager::GetCrc32(DWORD crc, LPBYTE buf, UINT len)
{
  static DWORD crc_table[256] = {
    0x00000000L, 0x77073096L, 0xee0e612cL, 0x990951baL, 0x076dc419L,
    0x706af48fL, 0xe963a535L, 0x9e6495a3L, 0x0edb8832L, 0x79dcb8a4L,
    0xe0d5e91eL, 0x97d2d988L, 0x09b64c2bL, 0x7eb17cbdL, 0xe7b82d07L,
    0x90bf1d91L, 0x1db71064L, 0x6ab020f2L, 0xf3b97148L, 0x84be41deL,
    0x1adad47dL, 0x6ddde4ebL, 0xf4d4b551L, 0x83d385c7L, 0x136c9856L,
    0x646ba8c0L, 0xfd62f97aL, 0x8a65c9ecL, 0x14015c4fL, 0x63066cd9L,
    0xfa0f3d63L, 0x8d080df5L, 0x3b6e20c8L, 0x4c69105eL, 0xd56041e4L,
    0xa2677172L, 0x3c03e4d1L, 0x4b04d447L, 0xd20d85fdL, 0xa50ab56bL,
    0x35b5a8faL, 0x42b2986cL, 0xdbbbc9d6L, 0xacbcf940L, 0x32d86ce3L,
    0x45df5c75L, 0xdcd60dcfL, 0xabd13d59L, 0x26d930acL, 0x51de003aL,
    0xc8d75180L, 0xbfd06116L, 0x21b4f4b5L, 0x56b3c423L, 0xcfba9599L,
    0xb8bda50fL, 0x2802b89eL, 0x5f058808L, 0xc60cd9b2L, 0xb10be924L,
    0x2f6f7c87L, 0x58684c11L, 0xc1611dabL, 0xb6662d3dL, 0x76dc4190L,
    0x01db7106L, 0x98d220bcL, 0xefd5102aL, 0x71b18589L, 0x06b6b51fL,
    0x9fbfe4a5L, 0xe8b8d433L, 0x7807c9a2L, 0x0f00f934L, 0x9609a88eL,
    0xe10e9818L, 0x7f6a0dbbL, 0x086d3d2dL, 0x91646c97L, 0xe6635c01L,
    0x6b6b51f4L, 0x1c6c6162L, 0x856530d8L, 0xf262004eL, 0x6c0695edL,
    0x1b01a57bL, 0x8208f4c1L, 0xf50fc457L, 0x65b0d9c6L, 0x12b7e950L,
    0x8bbeb8eaL, 0xfcb9887cL, 0x62dd1ddfL, 0x15da2d49L, 0x8cd37cf3L,
    0xfbd44c65L, 0x4db26158L, 0x3ab551ceL, 0xa3bc0074L, 0xd4bb30e2L,
    0x4adfa541L, 0x3dd895d7L, 0xa4d1c46dL, 0xd3d6f4fbL, 0x4369e96aL,
    0x346ed9fcL, 0xad678846L, 0xda60b8d0L, 0x44042d73L, 0x33031de5L,
    0xaa0a4c5fL, 0xdd0d7cc9L, 0x5005713cL, 0x270241aaL, 0xbe0b1010L,
    0xc90c2086L, 0x5768b525L, 0x206f85b3L, 0xb966d409L, 0xce61e49fL,
    0x5edef90eL, 0x29d9c998L, 0xb0d09822L, 0xc7d7a8b4L, 0x59b33d17L,
    0x2eb40d81L, 0xb7bd5c3bL, 0xc0ba6cadL, 0xedb88320L, 0x9abfb3b6L,
    0x03b6e20cL, 0x74b1d29aL, 0xead54739L, 0x9dd277afL, 0x04db2615L,
    0x73dc1683L, 0xe3630b12L, 0x94643b84L, 0x0d6d6a3eL, 0x7a6a5aa8L,
    0xe40ecf0bL, 0x9309ff9dL, 0x0a00ae27L, 0x7d079eb1L, 0xf00f9344L,
    0x8708a3d2L, 0x1e01f268L, 0x6906c2feL, 0xf762575dL, 0x806567cbL,
    0x196c3671L, 0x6e6b06e7L, 0xfed41b76L, 0x89d32be0L, 0x10da7a5aL,
    0x67dd4accL, 0xf9b9df6fL, 0x8ebeeff9L, 0x17b7be43L, 0x60b08ed5L,
    0xd6d6a3e8L, 0xa1d1937eL, 0x38d8c2c4L, 0x4fdff252L, 0xd1bb67f1L,
    0xa6bc5767L, 0x3fb506ddL, 0x48b2364bL, 0xd80d2bdaL, 0xaf0a1b4cL,
    0x36034af6L, 0x41047a60L, 0xdf60efc3L, 0xa867df55L, 0x316e8eefL,
    0x4669be79L, 0xcb61b38cL, 0xbc66831aL, 0x256fd2a0L, 0x5268e236L,
    0xcc0c7795L, 0xbb0b4703L, 0x220216b9L, 0x5505262fL, 0xc5ba3bbeL,
    0xb2bd0b28L, 0x2bb45a92L, 0x5cb36a04L, 0xc2d7ffa7L, 0xb5d0cf31L,
    0x2cd99e8bL, 0x5bdeae1dL, 0x9b64c2b0L, 0xec63f226L, 0x756aa39cL,
    0x026d930aL, 0x9c0906a9L, 0xeb0e363fL, 0x72076785L, 0x05005713L,
    0x95bf4a82L, 0xe2b87a14L, 0x7bb12baeL, 0x0cb61b38L, 0x92d28e9bL,
    0xe5d5be0dL, 0x7cdcefb7L, 0x0bdbdf21L, 0x86d3d2d4L, 0xf1d4e242L,
    0x68ddb3f8L, 0x1fda836eL, 0x81be16cdL, 0xf6b9265bL, 0x6fb077e1L,
    0x18b74777L, 0x88085ae6L, 0xff0f6a70L, 0x66063bcaL, 0x11010b5cL,
    0x8f659effL, 0xf862ae69L, 0x616bffd3L, 0x166ccf45L, 0xa00ae278L,
    0xd70dd2eeL, 0x4e048354L, 0x3903b3c2L, 0xa7672661L, 0xd06016f7L,
    0x4969474dL, 0x3e6e77dbL, 0xaed16a4aL, 0xd9d65adcL, 0x40df0b66L,
    0x37d83bf0L, 0xa9bcae53L, 0xdebb9ec5L, 0x47b2cf7fL, 0x30b5ffe9L,
    0xbdbdf21cL, 0xcabac28aL, 0x53b39330L, 0x24b4a3a6L, 0xbad03605L,
    0xcdd70693L, 0x54de5729L, 0x23d967bfL, 0xb3667a2eL, 0xc4614ab8L,
    0x5d681b02L, 0x2a6f2b94L, 0xb40bbe37L, 0xc30c8ea1L, 0x5a05df1bL,
    0x2d02ef8dL};
  if (buf == NULL)
    return 0L;
  crc = crc ^ 0xffffffffL;
  while (len >= 8)
  {
    DO8(buf);
    len -= 8;
  }
  if (len)
  {
    do
    {
      DO1(buf);
    }while(--len);
  }
  return crc ^ 0xffffffffL;
}
//---------------------------------------------------------------------------
VOID TMFSManager::Init(VOID)
{
  m_bValid = FALSE;
  m_bNewFile = FALSE;
  m_bModified = FALSE;
  m_hMFSMapFile = NULL;
  m_pvBasePointer = NULL;
  m_dwTotalOfOperation = 0l;
  m_pMFSDataDirectory = NULL;
  m_dwLastError = MFS_NO_ERROR;
  m_hMFSFile = INVALID_HANDLE_VALUE;
  m_pBaseOperation = m_pCurOperation = NULL;
  ZeroMemory(&m_mMFSHeader, sizeof(m_mMFSHeader));
  m_dwVersionOfCompressor = COMPRESSOR_VERSION_ZLIB114;
  for(int i=0;i<m_aMFSDataDirectory.GetLength();i++)
    if(m_aMFSDataDirectory[i].DataOfCompressed)
      delete m_aMFSDataDirectory[i].DataOfCompressed;
  m_aMFSDataDirectory.SetLength(0);
}
//---------------------------------------------------------------------------
VOID TMFSManager::CreateMFSHeader(VOID)
{
  m_mMFSHeader.Signature = PACKAGE_MFS30_SIGNATURE;
  m_mMFSHeader.Numbering = PACKAGE_MFS30_NUMBERING;
  m_mMFSHeader.OSVersion = PACKAGE_MFS30_OSVERSION;
  SetRandDWord(m_mMFSHeader.PasswordOfAutoLock + 0);    // 生成128Bit KEY
  SetRandDWord(m_mMFSHeader.PasswordOfAutoLock + 1);
  SetRandDWord(m_mMFSHeader.PasswordOfAutoLock + 2);
  SetRandDWord(m_mMFSHeader.PasswordOfAutoLock + 3);
}
//---------------------------------------------------------------------------
DWORD _stdcall TMFSManager::WriteMFSSectionData(HANDLE hFile, PMFSDATADIRECTORY pMFSDataDir)
{
  DWORD k, iZipSize;
  HANDLE hZipHandle;
  MFSSECTIONHEADER mfsTempSection, mfsWriteSection;
  LPBYTE lpZipBuffer, lpCompressed, lpRemarks;
  if(!pMFSDataDir->DataOfCompressed)
    return MFS_FATAL_ERROR; 
  CopyMemory(&mfsTempSection, pMFSDataDir->DataOfCompressed, sizeof(MFSSECTIONHEADER));
  SetRandDWord((LPDWORD)mfsTempSection.cReserved);
  k = strlen(mfsTempSection.ImportDirectory) + 1;
  for(;k<MAX_PATH;k++)
    mfsTempSection.ImportDirectory[k] = ZGetRand(255);
  k = SetFilePointer(hFile, 0, NULL, FILE_CURRENT);
  pMFSDataDir->DataOfCompressed = (PMFSSECTIONHEADER)k;
  if(!mfsTempSection.Size)                // 新建文件
  {
    mfsTempSection.PointerToCompressedData = k + sizeof(MFSSECTIONHEADER);
    hZipHandle = CreateFile(mfsTempSection.ImportDirectory, GENERIC_READ,
                            FILE_SHARE_READ, NULL, OPEN_EXISTING,
                            FILE_ATTRIBUTE_NORMAL, NULL);
    if(hZipHandle == INVALID_HANDLE_VALUE)
      return MFS_OPEN_FILE_FAIL;
    iZipSize = GetFileSize(hZipHandle, NULL);
    lpZipBuffer = new BYTE[iZipSize];
    ReadFile(hZipHandle, lpZipBuffer, iZipSize, &iZipSize, NULL);
    GetFileTime(hZipHandle, &mfsTempSection.CreationTime, NULL, &mfsTempSection.LastWriteTime);
    mfsTempSection.CompressedOfSize = mfsTempSection.FileSizeLow = iZipSize;
    mfsTempSection.CrcOfFile = GetCrc32(0, lpZipBuffer, iZipSize);
    if(mfsTempSection.VersionOfCompressor == COMPRESSOR_VERSION_ZLIB114)
      ZCompress(lpZipBuffer, iZipSize, (LPVOID)lpCompressed, (int)mfsTempSection.CompressedOfSize);
    else
      lpCompressed = NULL;
    if(mfsTempSection.SizeOfRemarks)
    {
      lpRemarks = (LPBYTE)mfsTempSection.PointerToRemarks;
      mfsTempSection.PointerToRemarks = mfsTempSection.PointerToCompressedData + mfsTempSection.CompressedOfSize;
    }
    else
      lpRemarks = NULL;
    mfsTempSection.Size = sizeof(MFSSECTIONHEADER) + mfsTempSection.CompressedOfSize + mfsTempSection.SizeOfRemarks;
    if(m_cPassword[0])                        // 如果存在用户密码，设置密码的CRC
      pMFSDataDir->CrcOfPassword = GetCrc32(0, m_cPassword, strlen(m_cPassword));
    CopyMemory(&mfsWriteSection, &mfsTempSection, sizeof(MFSSECTIONHEADER));
                                              // 加密节点头数据
    EncryptBuffer(&mfsWriteSection, sizeof(MFSSECTIONHEADER), m_mMFSHeader.Characteristics & (~PACKAGE_MFS30_ENCRYPT_RSA));
    WriteFile(hFile, &mfsWriteSection, sizeof(MFSSECTIONHEADER), &k, NULL);
    if(lpCompressed)                          // 压缩格式
    {
      BaseXorAdd(lpCompressed, mfsTempSection.CompressedOfSize, (LPBYTE)m_mMFSHeader.PasswordOfAutoLock, 16); // 基本加密算法，把压缩完的数据加密
      if(m_cPassword[0])                      // 如果存在密码，使用用户密码再加密一编
        BaseXorAdd(lpCompressed, mfsTempSection.CompressedOfSize, m_cPassword, strlen(m_cPassword));
      WriteFile(hFile, lpCompressed, mfsTempSection.CompressedOfSize, &k, NULL);
      ZFreeBuffer(lpCompressed);
    }
    else
    {
      BaseXorAdd(lpZipBuffer, iZipSize, (LPBYTE)m_mMFSHeader.PasswordOfAutoLock, 16); // 基本加密算法，把压缩完的数据加密
      if(m_cPassword[0])                      // 如果存在密码，使用用户密码再加密一编
        BaseXorAdd(lpZipBuffer, iZipSize, m_cPassword, strlen(m_cPassword));
      WriteFile(hFile, lpZipBuffer, iZipSize, &k, NULL);
    }
    delete []lpZipBuffer;
    CloseHandle(hZipHandle);
  }
  else
  {
    if(mfsTempSection.SizeOfRemarks)
      lpRemarks = (LPBYTE)mfsTempSection.PointerToRemarks;
    else
      lpRemarks = NULL;
    lpZipBuffer = (LPBYTE)mfsTempSection.PointerToCompressedData;
    mfsTempSection.PointerToCompressedData = k + sizeof(MFSSECTIONHEADER);
    if(lpRemarks)
      mfsTempSection.PointerToRemarks = mfsTempSection.PointerToCompressedData + mfsTempSection.CompressedOfSize;
    mfsTempSection.Size = sizeof(MFSSECTIONHEADER) + mfsTempSection.CompressedOfSize + mfsTempSection.SizeOfRemarks;
    CopyMemory(&mfsWriteSection, &mfsTempSection, sizeof(MFSSECTIONHEADER));
    EncryptBuffer(&mfsWriteSection, sizeof(MFSSECTIONHEADER), m_mMFSHeader.Characteristics & (~PACKAGE_MFS30_ENCRYPT_RSA));
    WriteFile(hFile, &mfsWriteSection, sizeof(MFSSECTIONHEADER), &k, NULL);
    WriteFile(hFile, lpZipBuffer, mfsTempSection.CompressedOfSize, &k, NULL);
  }
  if(lpRemarks)
    WriteFile(hFile, lpRemarks, mfsTempSection.SizeOfRemarks, &k, NULL);
  return MFS_NO_ERROR;
}
//---------------------------------------------------------------------------
VOID _stdcall TMFSManager::mfsSetLastError(DWORD iError)
{
  m_dwLastError = iError;
}
//---------------------------------------------------------------------------
VOID _stdcall TMFSManager::AddOperation(PMFS_OPERATION pMFSOperation)
{
  PMFS_OPERATION pTemp;

  if(!m_bValid)
  {
    m_bValid = TRUE;
    m_bNewFile = TRUE;
  }
  m_bModified = TRUE;
  pTemp = new MFS_OPERATION;
  CopyMemory(pTemp, pMFSOperation, sizeof(MFS_OPERATION));
  pTemp->pPrev = m_pCurOperation;
  pTemp->pNext = NULL;
  pTemp->iVersionOfCompressor = m_dwVersionOfCompressor;
  if(!m_pCurOperation)
    m_pBaseOperation = m_pCurOperation = pTemp;
  else
  {
    m_pCurOperation->pNext = pTemp;
    m_pCurOperation = pTemp;
  }
  m_dwTotalOfOperation++;
}
//---------------------------------------------------------------------------
VOID _stdcall TMFSManager::DeleteOperation(LPCSTR lpFilename)
{
  PMFS_OPERATION pTemp;
  pTemp = m_pCurOperation;
  while(pTemp)
  {
    if(!strcmp(pTemp->cFileName, lpFilename))
    {
      if(pTemp->pNext)
        pTemp->pNext->pPrev = pTemp->pPrev;
      else
      {
        m_pCurOperation = pTemp->pPrev;
        if(m_pCurOperation)
          m_pCurOperation->pNext = NULL;
      }
      if(pTemp->pPrev)
        pTemp->pPrev->pNext = pTemp->pNext;
      else
      {
        m_pBaseOperation = pTemp->pNext;
        if(m_pBaseOperation)
          m_pBaseOperation->pPrev = NULL;
      }
      m_dwTotalOfOperation--;
      if(pTemp->lpData)
        delete []pTemp->lpData;
      delete pTemp;
      break;
    }
    pTemp = pTemp->pPrev;
  }
}
//---------------------------------------------------------------------------
PMFS_OPERATION _stdcall TMFSManager::IndexOfOperation(LPCSTR lpFilename)
{
  PMFS_OPERATION pTemp;
  pTemp = m_pCurOperation;
  while(pTemp)
  {
    if(!strcmp(pTemp->cFileName, lpFilename))
      return pTemp;
    pTemp = pTemp->pPrev;
  }
  return NULL;
}
//---------------------------------------------------------------------------
VOID TMFSManager::ClearOperation(VOID)
{
  PMFS_OPERATION pTemp;
  pTemp = m_pCurOperation;
  while(pTemp)
  {
    if(pTemp->pPrev)
    {
      m_dwTotalOfOperation--;
      pTemp = pTemp->pPrev;
      if(pTemp->pNext->lpData)
        delete []pTemp->pNext->lpData;
      delete pTemp->pNext;
    }
    else
    {
      m_dwTotalOfOperation--;
      if(pTemp->lpData)
        delete []pTemp->lpData;
      delete pTemp;
      break;
    }
  }
  if(m_dwTotalOfOperation)
    MessageBox(NULL, "Error: Clear Operation data failure!!", NULL, MB_OK);
  m_pBaseOperation     = NULL;
  m_pCurOperation      = NULL;
  m_dwTotalOfOperation = 0;
}
//---------------------------------------------------------------------------
int _stdcall TMFSManager::IndexOf(LPCSTR lpFilename)
{
  if(m_bValid)
    for(int i=0;i<m_aMFSDataDirectory.GetLength();i++)
      if(!strcmp(m_aMFSDataDirectory[i].FileName, lpFilename))
        return i;
  return -1;
}
//---------------------------------------------------------------------------
VOID _stdcall TMFSManager::SaveFileName(LPCSTR lpFilename)
{
  strncpy(m_cFilename, lpFilename, MAX_PATH - 1);
  m_cFilename[MAX_PATH - 1] = 0;
}
//---------------------------------------------------------------------------
BOOL _stdcall TMFSManager::DecryptBuffer(LPBYTE lpInBuffer, DWORD iInLen, LPBYTE lpOutBuffer, DWORD iOutLen, LPBYTE key, int keyLen, int iMode)
{
  DWORD k;
  unsigned char initVect[8];
  if(iInLen / 8 * 8 != iInLen)
    return FALSE;
  // last 8 bytes of key are used as base for initialization vector
  memcpy((char*)initVect, key + 8, 8);
  switch(iMode)
  {
    case PACKAGE_MFS30_ENCRYPT_DES:
      DES_CBC_CTX pDesCTX;
      DES_CBCInit(&pDesCTX, key, initVect, IDEA_DECRYPT);
      for(k=0; k<iInLen; k+=8 )
        DES_CBCUpdate(&pDesCTX, &lpOutBuffer[k],
                      (unsigned char*)&lpInBuffer[k], 8);
      break;
    case PACKAGE_MFS30_ENCRYPT_BLOWFISH:
      BLOWFISH_CTX pBlowfishCTX;
      CopyMemory(lpOutBuffer, lpInBuffer, iInLen);
      lpInBuffer = lpOutBuffer;
      Blowfish_Init(&pBlowfishCTX, key, keyLen);
      for(k=0;k<iInLen;k+=8)
        Blowfish_Decrypt(&pBlowfishCTX, (unsigned long *)&lpInBuffer[k],
                         (unsigned long *)&lpInBuffer[k + 4]);
      break;
    case PACKAGE_MFS30_ENCRYPT_IDEA:
      IDEA_KEY_SCHEDULE encrypt_ks, decrypt_ks;
      idea_set_encrypt_key(key, &encrypt_ks);
      idea_set_decrypt_key(&encrypt_ks, &decrypt_ks);
      idea_ecb_encrypt(lpInBuffer, lpOutBuffer, &decrypt_ks);
      idea_cbc_encrypt(lpInBuffer, lpOutBuffer, iInLen, &decrypt_ks, initVect, IDEA_DECRYPT);
      break;
    case PACKAGE_MFS30_ENCRYPT_BASE:
    default:
      CopyMemory(lpOutBuffer, lpInBuffer, iInLen);
      break;
  };
  BaseXorSub(lpOutBuffer, iInLen, key, keyLen);          // 统统做一编基础解密
  return TRUE;
}
//---------------------------------------------------------------------------
BOOL _stdcall TMFSManager::DecryptBuffer(LPVOID lpBuffer, DWORD iLen, int iMode)
{
  BOOL bResult;
  LPBYTE lpOutBuffer;
  lpOutBuffer = new BYTE[iLen];
  bResult = DecryptBuffer((LPBYTE)lpBuffer, iLen, lpOutBuffer, iLen, (LPBYTE)m_mMFSHeader.PasswordOfAutoLock, 16, iMode);
  CopyMemory(lpBuffer, lpOutBuffer, iLen);
  delete []lpOutBuffer;
  return bResult;
}
//---------------------------------------------------------------------------
BOOL _stdcall TMFSManager::EncryptBuffer(LPBYTE lpInBuffer, DWORD iInLen, LPBYTE lpOutBuffer, DWORD iOutLen, LPBYTE key, int keyLen, int iMode)
{
  DWORD k;
  unsigned char initVect[8];
  if(iInLen / 8 * 8 != iInLen)
    return FALSE;
  // last 8 bytes of key are used as base for initialization vector
  memcpy((char*)initVect, key + 8, 8);
  BaseXorAdd(lpInBuffer, iInLen, key, keyLen);          // 统统做一编基础加密
  switch(iMode)
  {
    case PACKAGE_MFS30_ENCRYPT_DES:
      DES_CBC_CTX pDesCTX;
      DES_CBCInit(&pDesCTX, key, initVect, IDEA_ENCRYPT);
      for(k=0; k<iInLen; k+=8 )
        DES_CBCUpdate(&pDesCTX, &lpOutBuffer[k],
                      (unsigned char*)&lpInBuffer[k], 8);
      break;
    case PACKAGE_MFS30_ENCRYPT_BLOWFISH:
      BLOWFISH_CTX pBlowfishCTX;
      CopyMemory(lpOutBuffer, lpInBuffer, iInLen);
      lpInBuffer = lpOutBuffer;
      Blowfish_Init(&pBlowfishCTX, key, keyLen);
      for(k=0;k<iInLen;k+=8)
        Blowfish_Encrypt(&pBlowfishCTX, (unsigned long *)&lpInBuffer[k],
                         (unsigned long *)&lpInBuffer[k + 4]);
      break;
    case PACKAGE_MFS30_ENCRYPT_IDEA:
      IDEA_KEY_SCHEDULE encrypt_ks, decrypt_ks;
      idea_set_encrypt_key(key, &encrypt_ks);
      idea_ecb_encrypt(lpInBuffer, lpOutBuffer, &encrypt_ks);
      idea_cbc_encrypt(lpInBuffer, lpOutBuffer, iInLen, &encrypt_ks, initVect, IDEA_ENCRYPT);
      break;
    case PACKAGE_MFS30_ENCRYPT_BASE:
    default:
      CopyMemory(lpOutBuffer, lpInBuffer, iInLen);
      break;
  };
  return TRUE;
}
//---------------------------------------------------------------------------
BOOL _stdcall TMFSManager::EncryptBuffer(LPVOID lpBuffer, DWORD iLen, int iMode)
{
  BOOL bResult;
  LPBYTE lpOutBuffer;
  lpOutBuffer = new BYTE[iLen];
  bResult = EncryptBuffer((LPBYTE)lpBuffer, iLen, lpOutBuffer, iLen, (LPBYTE)m_mMFSHeader.PasswordOfAutoLock, 16, iMode);
  CopyMemory(lpBuffer, lpOutBuffer, iLen);
  delete lpOutBuffer;
  return bResult;
}
//---------------------------------------------------------------------------
_stdcall TMFSManager::TMFSManager(LPSTR lpFilename, BOOL bCreated)
{
  Init();
  m_bPublicKey = m_bPrivateKey = FALSE;
  ZeroMemory(m_cFilename, sizeof(m_cFilename));
  ZeroMemory(m_cPassword, sizeof(m_cPassword));
  ZeroMemory(m_cPublicKey, sizeof(m_cPublicKey));
  ZeroMemory(m_cPrivateKey, sizeof(m_cPrivateKey));
  if(NULL != lpFilename)                      // 文件名非空，则打开文件
    OpenMFSFile(lpFilename, bCreated);
  if(0 != dwZRandSeed)                        // 初始化随机函数
    ZRandomize();
}
//---------------------------------------------------------------------------
TMFSManager::~TMFSManager()
{
  Close();
}
//---------------------------------------------------------------------------
BOOL _stdcall TMFSManager::OpenMFSFile(LPSTR lpFilename, BOOL bCreated)
{
  unsigned int iOutLen, i;
  BOOL bResult = FALSE;
  PMFSHEADER pMfsHeader;
  PMFSSECTIONHEADER pTmpMfsSection;
  Close();
  if(!ZFileExists(lpFilename) && bCreated)    // 文件不存在并且需要创建
  {
    bResult = TRUE;
    m_bValid = TRUE;
    m_bNewFile = TRUE;                        // 新文件标志
    SaveFileName(lpFilename);
  }
  else                                        // 否则检查文件格式是否正确
  {
    try
    {
      m_hMFSFile = CreateFile(lpFilename, GENERIC_READ | GENERIC_WRITE,
                              FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL, NULL);
      if(m_hMFSFile == INVALID_HANDLE_VALUE)
        throw MFS_OPEN_FILE_FAIL;
      m_hMFSMapFile = CreateFileMapping(m_hMFSFile, NULL, PAGE_READWRITE, 0, 0, NULL);
      if(m_hMFSMapFile == NULL)
        throw MFS_MAPFILE_FAIL;
      m_pvBasePointer = MapViewOfFile(m_hMFSMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
      if(m_pvBasePointer == NULL)
        throw MFS_MAPFILE_FAIL;
      pMfsHeader = (PMFSHEADER)m_pvBasePointer;
      if(pMfsHeader->Signature != PACKAGE_MFS30_SIGNATURE ||
         pMfsHeader->Numbering != PACKAGE_MFS30_NUMBERING ||
         pMfsHeader->OSVersion != PACKAGE_MFS30_OSVERSION)
        throw MFS_INVALID_MFS_FILE;
      SaveFileName(lpFilename);
      CopyMemory(&m_mMFSHeader, m_pvBasePointer, sizeof(MFSHEADER));
      BaseXorSub((LPBYTE)&m_mMFSHeader.Characteristics, 4, (LPBYTE)&m_mMFSHeader.OSVersion, 4);
      BaseXorSub(m_mMFSHeader.Copyright, 256, (LPBYTE)&m_mMFSHeader.Signature, sizeof(DWORD) * 4);
      if(m_mMFSHeader.Characteristics & PACKAGE_MFS30_ENCRYPT_RSA)
      {
        if(m_bPublicKey)
          RSAPublicDecrypt(m_mMFSHeader.Copyright, &iOutLen, m_mMFSHeader.Copyright, 256, (R_RSA_PUBLIC_KEY *)m_cPublicKey);
        else
          throw MFS_NEED_PUBLIC_KEY;
      }
      if(m_mMFSHeader.SizeOfHeader != m_mMFSHeader.NumberOfDataDirectory * sizeof(MFSDATADIRECTORY) + sizeof(MFSHEADER))
        throw MFS_INVALID_MFS_FILE;
      i = sizeof(MFSDATADIRECTORY) * m_mMFSHeader.NumberOfDataDirectory;
      m_pMFSDataDirectory = (PMFSDATADIRECTORY)new BYTE[i];
      CopyMemory(m_pMFSDataDirectory, LPBYTE(m_pvBasePointer) + sizeof(MFSHEADER), i);
      DecryptBuffer(m_pMFSDataDirectory, i, m_mMFSHeader.Characteristics & (~PACKAGE_MFS30_ENCRYPT_RSA));
      m_aMFSDataDirectory.SetLength(m_mMFSHeader.NumberOfDataDirectory);
      for(i=0;i<m_mMFSHeader.NumberOfDataDirectory;i++)
      {
        CopyMemory(&m_aMFSDataDirectory[i], &m_pMFSDataDirectory[i], sizeof(MFSDATADIRECTORY));
        pTmpMfsSection = new MFSSECTIONHEADER;
        CopyMemory(pTmpMfsSection, LPBYTE(m_pvBasePointer) + DWORD(m_aMFSDataDirectory[i].DataOfCompressed), sizeof(MFSSECTIONHEADER));
        DecryptBuffer(pTmpMfsSection, sizeof(MFSSECTIONHEADER), m_mMFSHeader.Characteristics & (~PACKAGE_MFS30_ENCRYPT_RSA));
        pTmpMfsSection->PointerToCompressedData += DWORD(m_pvBasePointer);
        if(pTmpMfsSection->SizeOfRemarks)
          pTmpMfsSection->PointerToRemarks += DWORD(m_pvBasePointer);
        m_aMFSDataDirectory[i].DataOfCompressed = pTmpMfsSection;
      }
      delete []m_pMFSDataDirectory;
      m_pMFSDataDirectory = NULL;
      m_bValid = TRUE;
      bResult = TRUE;
    }
    catch(DWORD x)
    {
      mfsSetLastError(x);
      if(m_hMFSFile != INVALID_HANDLE_VALUE)
        Close();
    }
    catch(...)
    {
      mfsSetLastError(MFS_FATAL_ERROR);
      if(m_hMFSFile != INVALID_HANDLE_VALUE)
        Close();
    }
  }
  return bResult;
}
//---------------------------------------------------------------------------
BOOL TMFSManager::Save()
{
  BOOL bResult = FALSE;
  char *lpFilePart = NULL;
  char cTempFile[MAX_PATH], cTempPath[MAX_PATH] = {0};
  if(!m_bNewFile)                             // 如果不是新建文件，先保存成临时
  {                                           // 文件，再复制回原有文件。
    GetFullPathName(m_cFilename, MAX_PATH, cTempPath, &lpFilePart);
    if(lpFilePart && lpFilePart > cTempFile)
      *--lpFilePart = 0;
    else if(lpFilePart)
      *lpFilePart = 0;
    if(cTempPath[0])                          // 取得文件的路径
    {
      GetTempFileName(cTempPath, "mfs", 0, cTempFile);
      if(SaveAs(cTempFile))                   // 保存成临时文件
      {
        Close();
        if(MoveFileEx(cTempFile, m_cFilename, MOVEFILE_REPLACE_EXISTING))
        {                                     // 改名成原文件
          bResult = TRUE;
          OpenMFSFile(m_cFilename, FALSE);    // 重新打开文件
        }
        else
          DeleteFile(cTempFile);              // 改名失败，删除临时文件
      }
    }
  }
  else
  {
    bResult = SaveAs(m_cFilename);
    if(bResult)
      OpenMFSFile(m_cFilename, FALSE);
  }
  return bResult;
}
//---------------------------------------------------------------------------
BOOL _stdcall TMFSManager::SaveAs(LPSTR lpNewFilename)
{                                             // 另存为... 不得破坏原有任何数据
  DWORD k;
  HANDLE houtHandle;
  BOOL bResult = FALSE;
  PMFS_OPERATION pTemp;
  MFSHEADER pTempHeader;
  int i, iIndex, iCountDataDir;
  PMFSSECTIONHEADER pTempSection;
  MFSDATADIRECTORY mfsTempData, *lpTempData;
  IDataArray<MFSDATADIRECTORY> aTempDataDir;

  iCountDataDir = m_aMFSDataDirectory.GetLength();
  aTempDataDir.SetLength(iCountDataDir);
  aTempDataDir.SetAutoAlloc(1);               // 自动分配内存方式
  for(i=0;i<iCountDataDir;i++)                // 复制原始文件的目录数据
    aTempDataDir[i] = m_aMFSDataDirectory[i];

  pTemp = m_pCurOperation;
  try
  {
    houtHandle = CreateFile(lpNewFilename, GENERIC_READ | GENERIC_WRITE,
                            FILE_SHARE_READ, NULL, CREATE_ALWAYS,
                            FILE_ATTRIBUTE_NORMAL, NULL);
    if(houtHandle == INVALID_HANDLE_VALUE)
      throw MFS_CREATE_FILE_FAIL;
    while(pTemp)                              // 先建立MFS数据路径表
    {
      iIndex = -1;
      iCountDataDir = aTempDataDir.GetLength();
      for(i=0;i<iCountDataDir;i++)
      {
        if(!strcmp(aTempDataDir[i].FileName, pTemp->cFileName))
        {
          iIndex = i;
          break;
        }
      }
      switch(pTemp->iOperationType)
      {
        case MFS_OPERATION_NONE:              // 空操作
          break;
        case MFS_OPERATION_ADD_FILE:          // 添加一个新文件到文件包
          ZeroMemory(&mfsTempData, sizeof(MFSDATADIRECTORY));
          strncpy(mfsTempData.FileName, pTemp->cFileName, MAX_PATH - 1);
          pTempSection = new MFSSECTIONHEADER;
          ZeroMemory(pTempSection, sizeof(MFSSECTIONHEADER));
          pTempSection->VersionOfSection = SECTION_VERSION_30;
          pTempSection->VersionOfCompressor = pTemp->iVersionOfCompressor;
          strncpy(pTempSection->ItemName, pTemp->cItemName, 63);
          strncpy(pTempSection->ImportDirectory, pTemp->cImportFileName, MAX_PATH - 1);
          GetSystemTimeAsFileTime(&pTempSection->ImportTime);
          mfsTempData.DataOfCompressed = pTempSection;
          aTempDataDir[iCountDataDir] = mfsTempData;
          break;
        case MFS_OPERATION_DELETE_FILE:       // 从文件包删除一个文件
          if(iIndex != -1)
          {
            if(aTempDataDir[iIndex].DataOfCompressed)
              delete aTempDataDir[iIndex].DataOfCompressed;
            aTempDataDir.Delete(iIndex);
          }
          else
            throw MFS_OPERATION_ERROR;
          break;
        case MFS_OPERATION_ADD_REMARK:        // 添加一个备注到文件包
        case MFS_OPERATION_DELETE_REMARK:     // 删除一个备注
          if(iIndex != -1)
          {
            pTempSection = aTempDataDir[iIndex].DataOfCompressed;
            if(pTemp->iOperationType == MFS_OPERATION_ADD_REMARK)
            {
              pTempSection->SizeOfRemarks = pTemp->iSizeOfData;
              pTempSection->PointerToRemarks = (DWORD)pTemp->lpData;
            }
            else
            {
              pTempSection->SizeOfRemarks = 0;
              pTempSection->PointerToRemarks = NULL;
            }
          }
          else
            throw MFS_OPERATION_ERROR;
          break;
        default:
          throw MFS_OPERATION_ERROR;
      }
      pTemp = pTemp->pPrev;
    }
    iCountDataDir = aTempDataDir.GetLength();
    if(m_bNewFile)
      CreateMFSHeader();
    m_mMFSHeader.NumberOfDataDirectory = iCountDataDir;
    m_mMFSHeader.SizeOfHeader = sizeof(MFSHEADER) + sizeof(MFSDATADIRECTORY) * iCountDataDir;
    CopyMemory(&pTempHeader, &m_mMFSHeader, sizeof(MFSHEADER));
    for(i=0;i<sizeof(pTempHeader.cReserved);i++)
      pTempHeader.cReserved[i] = ZGetRand(255);
    if(pTempHeader.Characteristics & PACKAGE_MFS30_ENCRYPT_RSA)
    {
      if(m_bPrivateKey)
        RSAPrivateEncrypt(pTempHeader.Copyright, (unsigned int *)&i, m_mMFSHeader.Copyright, 120, (R_RSA_PRIVATE_KEY *)m_cPrivateKey);
      else
        pTempHeader.Characteristics &= ~PACKAGE_MFS30_ENCRYPT_RSA;
    }                                         // 写入MFS文件头
    BaseXorAdd(pTempHeader.Copyright, 256, (LPBYTE)&pTempHeader.Signature, sizeof(DWORD) * 4);
    BaseXorAdd((LPBYTE)&pTempHeader.Characteristics, 4, (LPBYTE)&pTempHeader.OSVersion, 4);
    WriteFile(houtHandle, &pTempHeader, sizeof(MFSHEADER), &k, NULL);

    for(i=0;i<iCountDataDir;i++)              // 先空出数据目录表的位置
      WriteFile(houtHandle, &aTempDataDir[i], sizeof(MFSDATADIRECTORY), &k, NULL);

    for(i=0;i<iCountDataDir;i++)              // 逐个写入各个文件数据
    {
      k = WriteMFSSectionData(houtHandle, &aTempDataDir[i]);
      if(k != MFS_NO_ERROR)
        throw k;
    }

    SetFilePointer(houtHandle, sizeof(MFSHEADER), NULL, FILE_BEGIN);
    i = iCountDataDir * sizeof(MFSDATADIRECTORY);
    m_pMFSDataDirectory = (PMFSDATADIRECTORY)new BYTE[i];
    for(i=0;i<iCountDataDir;i++)              // 重写入完整数据目录表数据
    {
      CopyMemory(&mfsTempData, &aTempDataDir[i], sizeof(MFSDATADIRECTORY));
      k = strlen(mfsTempData.FileName) + 1;
      for(;k<MAX_PATH;k++)
        mfsTempData.FileName[k] = ZGetRand(255);
      SetRandDWord((LPDWORD)&mfsTempData.cReserved[0]);
      SetRandDWord((LPDWORD)&mfsTempData.cReserved[4]);
      CopyMemory(&m_pMFSDataDirectory[i], &mfsTempData, sizeof(MFSDATADIRECTORY));
    }
    i = iCountDataDir * sizeof(MFSDATADIRECTORY);
    EncryptBuffer(m_pMFSDataDirectory, i, m_mMFSHeader.Characteristics & (~PACKAGE_MFS30_ENCRYPT_RSA));
    WriteFile(houtHandle, m_pMFSDataDirectory, i, &k, NULL);
    delete []m_pMFSDataDirectory;
    m_pMFSDataDirectory = NULL;
    bResult = TRUE;
    mfsSetLastError(MFS_NO_ERROR);
  }
  catch(DWORD x)                              // 一般错误
  {
    mfsSetLastError(x);
  }
  catch(...)                                  // 出现不可预料错误
  {
    mfsSetLastError(MFS_FATAL_ERROR);
  }
  if(houtHandle != INVALID_HANDLE_VALUE)
    CloseHandle(houtHandle);
  return bResult;
}
//---------------------------------------------------------------------------
BOOL TMFSManager::Close()
{
  if(m_pvBasePointer)
    UnmapViewOfFile(m_pvBasePointer);
  if(m_hMFSMapFile)
    CloseHandle(m_hMFSMapFile);
  if(m_hMFSFile && m_hMFSFile != INVALID_HANDLE_VALUE)
    CloseHandle(m_hMFSFile);
  ClearOperation();
  Init();
  return TRUE;
}
//---------------------------------------------------------------------------
VOID _stdcall TMFSManager::SetVersionOfCompressor(DWORD iVersion)
{
  m_dwVersionOfCompressor = iVersion;
}
//---------------------------------------------------------------------------
BOOL _stdcall TMFSManager::AddDirectory(LPCSTR lpDirectory, LPCSTR lpItemName)
{
  return TRUE;
}
//---------------------------------------------------------------------------
BOOL _stdcall TMFSManager::AddFile(LPCSTR lpImportFilename, LPCSTR lpItemName, LPCSTR lpFilename)
{
  MFS_OPERATION mfsOperation;
  if(IndexOfOperation(lpFilename))
  {
    mfsSetLastError(MFS_FILE_EXISTS);
    return FALSE;
  }
  ZeroMemory(&mfsOperation, sizeof(MFS_OPERATION));
  mfsOperation.iOperationType = MFS_OPERATION_ADD_FILE;
  strncpy(mfsOperation.cFileName, lpFilename, MAX_PATH - 1);
  strncpy(mfsOperation.cImportFileName, lpImportFilename, MAX_PATH - 1);
  strncpy(mfsOperation.cItemName, lpItemName, 63);
  AddOperation(&mfsOperation);
  return TRUE;
}
//---------------------------------------------------------------------------
BOOL _stdcall TMFSManager::AddRemark(LPCSTR lpFilename, LPVOID lpRemarks, DWORD iSizeOfRemarks)
{
  MFS_OPERATION mfsOperation;
  ZeroMemory(&mfsOperation, sizeof(MFS_OPERATION));
  mfsOperation.iOperationType = MFS_OPERATION_ADD_REMARK;
  strncpy(mfsOperation.cFileName, lpFilename, MAX_PATH - 1);
  mfsOperation.lpData = new BYTE[iSizeOfRemarks];
  mfsOperation.iSizeOfData = iSizeOfRemarks;
  CopyMemory(mfsOperation.lpData, lpRemarks, iSizeOfRemarks);
  AddOperation(&mfsOperation);
  return TRUE;
}
//---------------------------------------------------------------------------
BOOL _stdcall TMFSManager::RemoveFile(LPCSTR lpFilename)
{
  MFS_OPERATION mfsOperation;
  ZeroMemory(&mfsOperation, sizeof(MFS_OPERATION));
  mfsOperation.iOperationType = MFS_OPERATION_DELETE_FILE;
  strncpy(mfsOperation.cFileName, lpFilename, MAX_PATH - 1);
  AddOperation(&mfsOperation);
  return TRUE;
}
//---------------------------------------------------------------------------
HANDLE _stdcall TMFSManager::mfsOpenFile(LPSTR lpFilename, BOOL bPreRead)
{
  int i;
  PMFSFILEHANDLE pMfsHandle = NULL;
  i = IndexOf(lpFilename);
  if(i != -1)
  {
    if(m_aMFSDataDirectory[i].CrcOfPassword && GetCrc32(0, m_cPassword, strlen(m_cPassword)) != m_aMFSDataDirectory[i].CrcOfPassword)
      mfsSetLastError(MFS_INVAILD_PASSWORD);
    else
    {
      pMfsHandle = new MFSFILEHANDLE;
      ZeroMemory(pMfsHandle, sizeof(MFSFILEHANDLE));
      CopyMemory(&pMfsHandle->mMFSSectionInfo, m_aMFSDataDirectory[i].DataOfCompressed, sizeof(MFSSECTIONHEADER));
      if(bPreRead)
      {
        LPBYTE lpDecompressed;
        DWORD iCompressedOfSize;
        iCompressedOfSize = pMfsHandle->mMFSSectionInfo.CompressedOfSize;
        pMfsHandle->iSizeOfData = pMfsHandle->mMFSSectionInfo.FileSizeLow;
        pMfsHandle->lpData = new BYTE[pMfsHandle->iSizeOfData];
        CopyMemory(pMfsHandle->lpData, (LPBYTE)pMfsHandle->mMFSSectionInfo.PointerToCompressedData, iCompressedOfSize);
        if(m_aMFSDataDirectory[i].CrcOfPassword)        // 如果文件是加密的，解密先...
        {
          pMfsHandle->bPassword = TRUE;
          BaseXorSub(pMfsHandle->lpData, iCompressedOfSize, m_cPassword, strlen(m_cPassword));
        }
        BaseXorSub(pMfsHandle->lpData, iCompressedOfSize, (LPBYTE)m_mMFSHeader.PasswordOfAutoLock, 16);
        if(pMfsHandle->mMFSSectionInfo.VersionOfCompressor == COMPRESSOR_VERSION_ZLIB114)
        {                                               // 如果文件是压缩的，解压NOW
          if(ZDecompress(pMfsHandle->lpData, iCompressedOfSize, (LPVOID)lpDecompressed, (int)iCompressedOfSize, 0) == Z_OK)
            CopyMemory(pMfsHandle->lpData, lpDecompressed, iCompressedOfSize);
          ZFreeBuffer(lpDecompressed);
        }
        if(GetCrc32(0, pMfsHandle->lpData, pMfsHandle->iSizeOfData) != pMfsHandle->mMFSSectionInfo.CrcOfFile)
        {
          mfsSetLastError(MFS_FILE_CRC_BAD);
          mfsCloseFile((HANDLE)pMfsHandle);
          pMfsHandle = NULL;
        }
      }
    }
  }
  return pMfsHandle;
}
//---------------------------------------------------------------------------
DWORD _stdcall TMFSManager::mfsSetFilePointer(HANDLE hFile, DWORD iDistanceToMove, DWORD dwMoveMethod)
{
  DWORD iFileSize, iResult = 0;
  if(hFile && PMFSFILEHANDLE(hFile)->lpData)
  {
    iFileSize = mfsGetFileSize(hFile, NULL);
    switch(dwMoveMethod)
    {
      case FILE_BEGIN:
        PMFSFILEHANDLE(hFile)->iOffset = iDistanceToMove;
        break;
      case FILE_CURRENT:
        PMFSFILEHANDLE(hFile)->iOffset += iDistanceToMove;
        break;
      case FILE_END:
        PMFSFILEHANDLE(hFile)->iOffset = iFileSize - iDistanceToMove;
        break;
    }
    if(PMFSFILEHANDLE(hFile)->iOffset > iFileSize)
      PMFSFILEHANDLE(hFile)->iOffset = iFileSize;
    iResult = PMFSFILEHANDLE(hFile)->iOffset;
  }
  return iResult;
}
//---------------------------------------------------------------------------
DWORD _stdcall TMFSManager::mfsReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead)
{
  DWORD iFileSize, iResult = 0;
  if(hFile)
  {
    if(PMFSFILEHANDLE(hFile)->lpData)
    {
      iFileSize = PMFSFILEHANDLE(hFile)->iSizeOfData;
      if(iFileSize - PMFSFILEHANDLE(hFile)->iOffset < nNumberOfBytesToRead)
        nNumberOfBytesToRead = iFileSize - PMFSFILEHANDLE(hFile)->iOffset;
      CopyMemory(lpBuffer, PMFSFILEHANDLE(hFile)->lpData + PMFSFILEHANDLE(hFile)->iOffset, nNumberOfBytesToRead);
    }
    else
    {
      LPBYTE lpDecompressed, lpData;
      DWORD iCompressedOfSize;
      iFileSize = mfsGetFileSize(hFile, NULL);
      if(iFileSize - PMFSFILEHANDLE(hFile)->iOffset < nNumberOfBytesToRead)
        nNumberOfBytesToRead = iFileSize - PMFSFILEHANDLE(hFile)->iOffset;
      iCompressedOfSize = PMFSFILEHANDLE(hFile)->mMFSSectionInfo.CompressedOfSize;
      lpData = new BYTE[iCompressedOfSize];
      CopyMemory(lpData, (LPBYTE)PMFSFILEHANDLE(hFile)->mMFSSectionInfo.PointerToCompressedData, iCompressedOfSize);
      if(PMFSFILEHANDLE(hFile)->bPassword)        // 如果文件是加密的，解密先...
        BaseXorSub(lpData, iCompressedOfSize, m_cPassword, strlen(m_cPassword));
      BaseXorSub(lpData, iCompressedOfSize, (LPBYTE)m_mMFSHeader.PasswordOfAutoLock, 16);
      if(PMFSFILEHANDLE(hFile)->mMFSSectionInfo.VersionOfCompressor == COMPRESSOR_VERSION_ZLIB114)
      {                                           // 如果文件是压缩的，解压NOW
        if(ZDecompress(lpData, iCompressedOfSize, (LPVOID)lpDecompressed, (int)iCompressedOfSize, 0) == Z_OK)
          CopyMemory(lpBuffer, lpDecompressed + PMFSFILEHANDLE(hFile)->iOffset, nNumberOfBytesToRead);
        ZFreeBuffer(lpDecompressed);
      }
      else
        CopyMemory(lpBuffer, lpData + PMFSFILEHANDLE(hFile)->iOffset, nNumberOfBytesToRead);
    }
    iResult = nNumberOfBytesToRead;
  }
  return iResult;
}
//---------------------------------------------------------------------------
DWORD _stdcall TMFSManager::mfsWriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite)
{
  int i;
  LPBYTE lpData;
  DWORD iResult = 0;
  if(hFile && (i = IndexOf(PMFSFILEHANDLE(hFile)->cFileName)) != -1)
  {                                           // 非压缩格式才允许修改内容
    if(m_aMFSDataDirectory[i].DataOfCompressed->VersionOfCompressor == COMPRESSOR_VERSION_NONE)
    {
      lpData = (LPBYTE)PMFSFILEHANDLE(hFile)->mMFSSectionInfo.PointerToCompressedData;
      if(lpData)
      {
        if(nNumberOfBytesToWrite > PMFSFILEHANDLE(hFile)->mMFSSectionInfo.FileSizeLow)
          nNumberOfBytesToWrite = PMFSFILEHANDLE(hFile)->mMFSSectionInfo.FileSizeLow;
        CopyMemory(lpData, lpBuffer, nNumberOfBytesToWrite);
        iResult = nNumberOfBytesToWrite;
      }
    }
  }
  return iResult;
}
//---------------------------------------------------------------------------
DWORD _stdcall TMFSManager::mfsGetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh)
{
  DWORD iResult = 0;
  if(hFile)
  {
    iResult = PMFSFILEHANDLE(hFile)->mMFSSectionInfo.FileSizeLow;
    if(lpFileSizeHigh)
      *lpFileSizeHigh = PMFSFILEHANDLE(hFile)->mMFSSectionInfo.FileSizeHigh;
  }
  else if(lpFileSizeHigh)
    *lpFileSizeHigh = 0;
  return iResult;
}
//---------------------------------------------------------------------------
BOOL _stdcall TMFSManager::mfsCloseFile(HANDLE hFile)
{
  if(hFile)
  {
    if(PMFSFILEHANDLE(hFile)->lpData)
      delete []PMFSFILEHANDLE(hFile)->lpData;
    delete hFile;
  }
  return TRUE;
}
//---------------------------------------------------------------------------
DWORD _stdcall TMFSManager::mfsGetFileBuffer(HANDLE hFile, LPBYTE *lpData)
{
  if(PMFSFILEHANDLE(hFile)->lpData)
    *lpData = PMFSFILEHANDLE(hFile)->lpData;
  else
    *lpData = NULL;
  return PMFSFILEHANDLE(hFile)->iSizeOfData;
}
//---------------------------------------------------------------------------
BOOL _stdcall TMFSManager::mfsFileExists(LPCSTR lpFilename)
{
  return mfsGetFileAttributes(lpFilename, NULL);
}
//---------------------------------------------------------------------------
BOOL TMFSManager::mfsGetFileAttributes(LPCSTR lpFilename, PMFSSECTIONHEADER pmfsSectionHeader)
{
  int i;
  i = IndexOf(lpFilename);
  if(pmfsSectionHeader)
  {
    CopyMemory(pmfsSectionHeader, m_aMFSDataDirectory[i].DataOfCompressed, sizeof(MFSSECTIONHEADER));
    pmfsSectionHeader->PointerToCompressedData = 0l;
    pmfsSectionHeader->PointerToRemarks =  0l;
  }
  return i != -1;
}
//---------------------------------------------------------------------------
int TMFSManager::GetFileCount(VOID)
{
  if(m_bValid)
    return m_aMFSDataDirectory.GetLength();
  return 0;
}
//---------------------------------------------------------------------------
PMFSDATADIRECTORY TMFSManager::GetDataDirectory(int Index)
{
  PMFSDATADIRECTORY pmfsDataDirectory = NULL;
  if(m_aMFSDataDirectory.GetLength() > Index)
    pmfsDataDirectory = &m_aMFSDataDirectory[Index];
  return pmfsDataDirectory;
}
//---------------------------------------------------------------------------
BOOL TMFSManager::IsValid(VOID)
{
  return m_bValid;
}
//---------------------------------------------------------------------------
BOOL TMFSManager::IsModified(VOID)
{
  return m_bModified;
}
//---------------------------------------------------------------------------
VOID _stdcall TMFSManager::SetPasswordOfFile(LPCSTR lpPassword)
{
  strncpy(m_cPassword, lpPassword, 63);
  m_cPassword[63] = 0;
}
//---------------------------------------------------------------------------
VOID _stdcall TMFSManager::SetPrivateKeyOfFile(LPBYTE lpPrivateKey, DWORD iKeyLen)
{
  if(iKeyLen > sizeof(m_cPrivateKey))
    iKeyLen = sizeof(m_cPrivateKey);
  CopyMemory(m_cPrivateKey, lpPrivateKey, iKeyLen);
  m_bPrivateKey = TRUE;
}
//---------------------------------------------------------------------------
VOID _stdcall TMFSManager::SetPublicKeyOfFile(LPBYTE lpPublicKey, DWORD iKeyLen)
{
  if(iKeyLen > sizeof(m_cPublicKey))
    iKeyLen = sizeof(m_cPublicKey);
  CopyMemory(m_cPublicKey, lpPublicKey, iKeyLen);
  m_bPublicKey = TRUE;
}
//---------------------------------------------------------------------------
VOID _stdcall TMFSManager::ClearPrivateKeyOfFile(VOID)
{
  ZeroMemory(m_cPrivateKey, sizeof(m_cPrivateKey));
  m_bPrivateKey = FALSE;
}
//---------------------------------------------------------------------------
VOID _stdcall TMFSManager::ClearPublicKeyOfFile(VOID)
{
  ZeroMemory(m_cPublicKey, sizeof(m_cPublicKey));
  m_bPublicKey = FALSE;
}
//---------------------------------------------------------------------------
VOID _stdcall TMFSManager::SetEncryptModeOfFile(DWORD iMode)
{
  m_mMFSHeader.Characteristics = iMode;
}
//---------------------------------------------------------------------------
VOID _stdcall TMFSManager::SetCopyright(LPCSTR lpCopyright)
{
  strncpy(m_mMFSHeader.Copyright, lpCopyright, 63);
  m_mMFSHeader.Copyright[63] = 0;
}
//---------------------------------------------------------------------------
DWORD TMFSManager::mfsGetLastError()
{
  return m_dwLastError;
}
//---------------------------------------------------------------------------
LPSTR TMFSManager::GetFilename(void)
{
  return m_cFilename;
}
//---------------------------------------------------------------------------
LPSTR TMFSManager::GetVersionString()
{
  return MFS_VERSION;
}
//---------------------------------------------------------------------------



