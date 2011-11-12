//---------------------------------------------------------------------------
#ifndef MFSManagerH
#define MFSManagerH

// bugfix 2006-06-15 未考虑 压缩后的文件 CompressedOfSize 比 未压缩的 FileSizeLow 还大，发生复制越界
// 1029行:
// 原始:        pMfsHandle->lpData = new BYTE[pMfsHandle->iSizeOfData];
//
// 修改:        pMfsHandle->lpData = new BYTE[pMfsHandle->iSizeOfData < iCompressedOfSize ? iCompressedOfSize : pMfsHandle->iSizeOfData];

#include <windows.h>
#include "itemplat.h"                         // 通用动态数据模板
//---------------------------------------------------------------------------
#ifdef __BORLANDC__
#pragma option -a1			      // 对齐方式为1字节
#endif //__BORLANDC__

#ifdef _MSC_VER
#pragma pack(1)				      // 对齐方式为1字节
#endif //__MSC_VER
/****************************************************************************
 * MFS文件格式示意图
 * +------------------+
 * |    文件头(255)   |
 * +------------------+
 * |   数据目录列表   |
 * |含有各数据包的连接|
 * |信息,以及位置.    |
 * +------------------+
 * |各个数据包存放的位|
 * |置.               |
 * +------------------+
 ***************************************************************************/
typedef struct tagMfsHeader                            // 标志头
{
  DWORD                       Signature;               // 标志
  DWORD                       Numbering;               // 编号
  DWORD                       OSVersion;               // 版本
  DWORD                       Characteristics;         // 属性，所用的加密算法等属性
  BYTE                        Copyright[64];           // 版权，从这里开始加密计256字节
  DWORD                       SizeOfHeader;            // 文件头大小(含项目列表)
  DWORD                       NumberOfDataDirectory;   // 总项目列表数目(目录列表用)
  DWORD                       PasswordOfAutoLock[4];   // 自动加密口令(文件创建时便存在直至销毁,
                                                       // 是一随机数，文件除文件标志头以外均用该
                                                       // 密码加密，密码长度128 Bit.)
  BYTE                        cReserved[168];          // 保留为以后版本
}MFSHEADER, *PMFSHEADER;                               // 大小272字节

typedef struct tagMFSSectionHeader
{
  DWORD                       Size;                     // 本块大小,含结构和附属数据(如名字,文件名,导入目录,压缩数据等)
  DWORD                       VersionOfSection;         // 属性
  DWORD                       VersionOfCompressor;      // 压缩程序的版本
  char                        ItemName[64];             // 项名称
  char                        ImportDirectory[MAX_PATH];// 导入目录
  FILETIME                    CreationTime;             // 创建时间
  FILETIME                    LastWriteTime;            // 最后修改时间
  FILETIME                    ImportTime;               // 导入时间
  DWORD                       FileSizeHigh;             // 文件大小高位
  DWORD                       FileSizeLow;              // 文件大小低位
  DWORD                       CompressedOfSize;         // 压缩后的文件大小
  DWORD                       PointerToCompressedData;  // 指向压缩后的数据
  DWORD                       CrcOfFile;                // 原始文件的CRC (Cyclic Redundancy Check)
  DWORD                       SizeOfRemarks;            // 备注段大小(0L为无备注)
  DWORD                       PointerToRemarks;         // 指向备注段
  BYTE                        cReserved[4];             // 保留为保持8的倍数，加密方便
}MFSSECTIONHEADER, *PMFSSECTIONHEADER;                  // 392字节

typedef struct tagMFSDataDirectory
{
  char                        FileName[MAX_PATH];       // 文件名
  PMFSSECTIONHEADER           DataOfCompressed;         // 指向压缩数据的指针
  DWORD                       CrcOfPassword;            // 口令校正数据(0L为无口令)
  DWORD                       Characteristics;          // 块标志
  BYTE                        cReserved[8];             // 保留为保持8的倍数，加密方便
}MFSDATADIRECTORY, *PMFSDATADIRECTORY;                  // 280字节

typedef struct tagMFSOperation
{
  struct tagMFSOperation     *pPrev;                    // 指向上一块的指针
  struct tagMFSOperation     *pNext;                    // 指向下一块的指针
  DWORD                       iOperationType;           // 操作的类型
  char                        cFileName[MAX_PATH];      // 文件名
  char                        cItemName[64];            // 项名称
  char                        cImportFileName[MAX_PATH];// 导入的文件名
  DWORD                       iVersionOfCompressor;     // 压缩格式
  DWORD                       iSizeOfData;              // 数据的大小
  LPBYTE                      lpData;                   // 操作的数据
}MFS_OPERATION, *PMFS_OPERATION;

typedef struct tagMFSFileHandle
{
  DWORD                       iOffset;                  // 当前偏移, 非压缩Only
  MFSSECTIONHEADER            mMFSSectionInfo;          // 一些节点信息
  DWORD                       iSizeOfData;              // 数据的大小, 非压缩Only
  LPBYTE                      lpData;                   // 操作的数据
  BOOL                        bPassword;                // 是否有加密码
  char                        cFileName[MAX_PATH];      // 文件名
}MFSFILEHANDLE, *PMFSFILEHANDLE;

#define PACKAGE_MFS30_SIGNATURE               0x0000484C  // LH00(压缩包标志)
#define PACKAGE_MFS30_NUMBERING               0x20030107  // 编号
#define PACKAGE_MFS30_OSVERSION               0x3373666D  // 版本 'mfs3'

// Encrypt Arithmetic
#define PACKAGE_MFS30_ENCRYPT_BASE            0x00000000  // 加密用算法，基础加密算法
#define PACKAGE_MFS30_ENCRYPT_DES             0x00000001  // 加密用算法，des算法
#define PACKAGE_MFS30_ENCRYPT_BLOWFISH        0x00000002  // 加密用算法，blowfish算法
#define PACKAGE_MFS30_ENCRYPT_IDEA            0x00000003  // 加密用算法，idea算法
#define PACKAGE_MFS30_ENCRYPT_RSA             0x80000000  // 加密用算法，rsa算法(跟其他对称算法配合)，仅支持512, 1024, 2048bit Key

// Section Version
#define SECTION_VERSION_30                    0x00000030  // 目前节点版本为3.0

// Section Compressor Version
#define COMPRESSOR_VERSION_NONE               0x00000000  // 无压缩
#define COMPRESSOR_VERSION_ZLIB114            0x3431317A  // 压缩程序版本 zlib 1.1.4

// Section Characteristics
#define SECTION_IS_NONE                       0x00000000  // 压缩包不含数据
#define SECTION_IS_DATA                       0x00000001  // 压缩包含有数据
#define SECTION_IS_REMARKS                    0x00000002  // 压缩包含有备注数据

// Dynamic Operation Characteristics
#define MFS_OPERATION_NONE                    0x00000000  // 无操作
#define MFS_OPERATION_ADD_FILE                0x00000001  // 添加一个新文件到文件包
#define MFS_OPERATION_DELETE_FILE             0x00000002  // 从文件包删除一个文件
#define MFS_OPERATION_ADD_REMARK              0x00000003  // 添加一个备注到文件包
#define MFS_OPERATION_DELETE_REMARK           0x00000004  // 删除一个备注

// Error Result Value
#define MFS_NO_ERROR                          0x00000000  // 无错误
#define MFS_OPEN_FILE_FAIL                    0xC1010101  // 打开文件失败
#define MFS_MAPFILE_FAIL                      0xC1010102  // 映射文件失败
#define MFS_INVALID_MFS_FILE                  0xC1010103  // mfs文件格式无效
#define MFS_NEED_PRIVATE_KEY                  0xC1010104  // 需要私有Key
#define MFS_NEED_PUBLIC_KEY                   0xC1010105  // 需要公有Key
#define MFS_DECRYPT_FAIL                      0xC1010106  // 解密失败
#define MFS_ENCRYPT_FAIL                      0xC1010107  // 加密失败
#define MFS_OPERATION_ERROR                   0xC1010108  // 一般操作性错误
#define MFS_CREATE_FILE_FAIL                  0xC1010109  // 创建文件失败
#define MFS_FATAL_ERROR                       0xC101010A  // 致命错误，一般内存溢出
#define MFS_FILE_EXISTS                       0xC101010B  // 文件已经存在
#define MFS_INVAILD_PASSWORD                  0xC101010C  // 无效的密码
#define MFS_FILE_CRC_BAD                      0xC101010D  // 文件CRC错误

// Version
#define MFS_VERSION                           ".mfs Manager v3.0"
//---------------------------------------------------------------------------
#ifdef __BORLANDC__
#pragma option -a.
#endif //__BORLANDC__

#ifdef _MSC_VER
#pragma pack()
#endif //_MSC_VER
//---------------------------------------------------------------------------
enum TZCompressionLevel { zcNone, zcFastest, zcDefault, zcMax };
//---------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif
//---------------------------------------------------------------------------
int _stdcall ZCompress(LPCVOID inBuffer, int inSize, LPVOID &outBuffer, int &outSize, TZCompressionLevel level = zcDefault);
int _stdcall ZDecompress(LPCVOID inBuffer, int inSize, LPVOID &outBuffer, int &outSize, int outEstimate);
void _stdcall ZFreeBuffer(LPVOID pBuffer);

extern DWORD dwZRandSeed;

void _stdcall ZRandomize(void);
DWORD _stdcall ZRandInt(DWORD i);
double ZRandExt(void);
double _stdcall ZRandG(double Mean, double StdDev);
int _stdcall ZGetRand(int x);
//---------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif
//---------------------------------------------------------------------------
class TMFSManager
{
private:
        HANDLE                          m_hMFSFile, m_hMFSMapFile;
        LPVOID                          m_pvBasePointer;
        MFSHEADER                       m_mMFSHeader;
        PMFSDATADIRECTORY               m_pMFSDataDirectory;
        IDataArray<MFSDATADIRECTORY>    m_aMFSDataDirectory;
        DWORD                           m_dwTotalOfOperation;
        PMFS_OPERATION                  m_pBaseOperation, m_pCurOperation;
        DWORD                           m_dwVersionOfCompressor;
        DWORD                           m_dwLastError;
        BOOL                            m_bModified;
        BOOL                            m_bValid;
        BOOL                            m_bNewFile;
        char                            m_cPassword[64];
        char                            m_cFilename[MAX_PATH];
        BOOL                            m_bPublicKey, m_bPrivateKey;
        BYTE                            m_cPublicKey[514];        // 解密专用，公共Key
        BYTE                            m_cPrivateKey[1410];      // 专门用于加密，私有Key
protected:
        VOID                    Init(VOID);
        VOID                    CreateMFSHeader(VOID);
        DWORD _stdcall          WriteMFSSectionData(HANDLE hFile, PMFSDATADIRECTORY pMFSDataDir);
        VOID _stdcall           AddOperation(PMFS_OPERATION pMFSOperation);
        VOID _stdcall           DeleteOperation(LPCSTR lpFilename);
        PMFS_OPERATION _stdcall IndexOfOperation(LPCSTR lpFilename);
        VOID                    ClearOperation(VOID);
        int _stdcall            IndexOf(LPCSTR lpFilename);
        VOID _stdcall           SaveFileName(LPCSTR lpFilename);
        static BOOL _stdcall    DecryptBuffer(LPBYTE lpInBuffer, DWORD iInLen, LPBYTE lpOutBuffer, DWORD iOutLen, LPBYTE key, int keyLen, int iMode);
        BOOL _stdcall           DecryptBuffer(LPVOID lpBuffer, DWORD iLen, int iMode);
        static BOOL _stdcall    EncryptBuffer(LPBYTE lpInBuffer, DWORD iInLen, LPBYTE lpOutBuffer, DWORD iOutLen, LPBYTE key, int keyLen, int iMode);
        BOOL _stdcall           EncryptBuffer(LPVOID lpBuffer, DWORD iLen, int iMode);
public:
        _stdcall                TMFSManager(LPSTR lpFilename = NULL, BOOL bCreated = FALSE);
                                ~TMFSManager();

        BOOL _stdcall           OpenMFSFile(LPSTR lpFilename, BOOL bCreated);
        BOOL                    Save();
        BOOL _stdcall           SaveAs(LPSTR lpNewFilename);
        BOOL                    Close();

        VOID _stdcall           SetVersionOfCompressor(DWORD iVersion);
        BOOL _stdcall           AddDirectory(LPCSTR lpDirectory, LPCSTR lpItemName);
        BOOL _stdcall           AddFile(LPCSTR lpImportFilename, LPCSTR lpItemName, LPCSTR lpFilename);
        BOOL _stdcall           AddRemark(LPCSTR lpFilename, LPVOID lpRemarks, DWORD iSizeOfRemarks);
        BOOL _stdcall           RemoveFile(LPCSTR lpFilename);

        HANDLE _stdcall         mfsOpenFile(LPSTR lpFilename, BOOL bPreRead);
        DWORD _stdcall          mfsSetFilePointer(HANDLE hFile, DWORD iDistanceToMove, DWORD dwMoveMethod); // 非压缩格式Only
        DWORD _stdcall          mfsReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead);
        DWORD _stdcall          mfsWriteFile(HANDLE hFile, LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite); // 非压缩格式Only
        DWORD _stdcall          mfsGetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh);
        BOOL _stdcall           mfsCloseFile(HANDLE hFile);
        DWORD _stdcall          mfsGetFileBuffer(HANDLE hFile, LPBYTE *lpData);

        BOOL _stdcall           mfsFileExists(LPCSTR lpFilename);
        BOOL                    mfsGetFileAttributes(LPCSTR lpFilename, PMFSSECTIONHEADER pmfsSectionHeader);

        VOID _stdcall           mfsSetLastError(DWORD iError);
        DWORD                   mfsGetLastError();

        int                     GetFileCount(VOID);
        PMFSDATADIRECTORY       GetDataDirectory(int Index);

        static DWORD _stdcall   GetCrc32(DWORD crc, LPBYTE buf, UINT len);
        BOOL                    IsValid(VOID);
        BOOL                    IsModified(VOID);
        VOID _stdcall           SetPasswordOfFile(LPCSTR lpPassword);
        VOID _stdcall           SetPrivateKeyOfFile(LPBYTE lpPrivateKey, DWORD iKeyLen);
        VOID _stdcall           SetPublicKeyOfFile(LPBYTE lpPublicKey, DWORD iKeyLen);
        VOID _stdcall           ClearPrivateKeyOfFile(VOID);
        VOID _stdcall           ClearPublicKeyOfFile(VOID);
        VOID _stdcall           SetEncryptModeOfFile(DWORD iMode);
        VOID _stdcall           SetCopyright(LPCSTR lpCopyright);
        LPSTR                   GetFilename(void);
        LPSTR                   GetVersionString();
};
//---------------------------------------------------------------------------
#endif
