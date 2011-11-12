//---------------------------------------------------------------------------
#ifndef TDreamlandH
  #define TDreamlandH

//---------------------------------------------------------------------------
  #include "opcodes.h"

//---------------------------------------------------------------------------
  #define DREAMLAND_VERSION         0x0103
  #define DREAMLAND_VERSION_STRING  "1.03"
  #define DREAMLAND_VERSION_DATE    "Jun 22 2003"

//---------------------------------------------------------------------------
  #define ASMPOS  10

//---------------------------------------------------------------------------
  #define DREAMLAND_OUTSIDECODE 0x80000000
  #define DREAMLAND_INVALIDCODE 0x80000001

//---------------------------------------------------------------------------
typedef BOOL (WINAPI *TJUMPINSTRPROC) (DWORD ValueAddress, DWORD JumpAddress, LPSTR lpResultBuffer);
typedef BOOL (WINAPI *TCALLINSTRPROC) (DWORD ValueAddress, DWORD CallAddress, LPSTR lpResultBuffer);
typedef BOOL (WINAPI *TADDRESSREFPROC) (DWORD ValueAddress, DWORD RefAddress, LPSTR lpResultBuffer);
typedef BOOL (WINAPI *TIMMIDIATEDATAPROC)
  (
    DWORD ValueAddress,
    DWORD OperandSize,
    LPSTR lpResultBuffer
  );

//---------------------------------------------------------------------------
  #ifdef __BORLANDC__
    #pragma option -a1 //对齐方式为1字节
  #endif //__BORLANDC__
  #ifdef _MSC_VER
    #pragma pack(1)     //对齐方式为1字节
  #endif //__MSC_VER						//如果不设置，默认的对齐

//---------------------------------------------------------------------------
typedef struct  tagTFarCalls
{
  BOOL    bCall;        // is it a CALL or a JMP?
  LPVOID  lpCodeAddr1;  // beginning of call instruction
  LPVOID  lpCodeAddr2;  // beginning of next instruction
  struct
  {
    BOOL    bIsValid;
    LPVOID  lpAreaBegin;
    LPVOID  lpAreaEnd;
  } CodeAreas;
  LPVOID              lpTarget;
  struct tagTFarCalls *pPrev;
  struct tagTFarCalls *pNext;
}
TFARCALLS, *PTFARCALLS;

//---------------------------------------------------------------------------
  #ifdef __BORLANDC__
    #pragma option -a.
  #endif //__BORLANDC__
  #ifdef _MSC_VER
    #pragma pack()
  #endif //_MSC_VER

//---------------------------------------------------------------------------
class TFunctionInfo
{

private:
  PTFARCALLS  pBaseFarCalls, pCurFarCalls;
  int         iTotalOfFarCall;

public:
  BOOL        bIsValid;
  LPVOID      lpEntryPoint;
  LPVOID      lpCodeBegin;
  DWORD       iCodeLen;
  LPVOID      lpLastErrorAddr;
  DWORD       iLastErrorNo;
  LPSTR       lpLastErrorStr;
  PTFARCALLS  pFarCalls;
  DWORD       iCallCount;
  DWORD       iJmpCount;

  TFunctionInfo(void);
  ~TFunctionInfo(void);
  BOOL WINAPI       Add(BOOL bCall, LPVOID lpCodeAddr1, LPVOID lpCodeAddr2, LPVOID lpTarget,
                        BOOL bIsValid, LPVOID lpAreaBegin, LPVOID lpAreaEnd);
  PTFARCALLS WINAPI Get(BOOL bCall, int iIndex);
};

//---------------------------------------------------------------------------
class TDreamland
{

private:
  BOOL  b32bitAddress;
  BOOL  bMode32;
  LPSTR lpSegmentPrefix, lpRepPrefix, lpLockPrefix;
  BOOL  bOptions_mode16, bOptions_mode32;
  DWORD iProcAddress;
  BOOL  bOperandPrefix;
  BOOL  bAddressPrefix;
  BOOL  bUnknownInstruction;
  DWORD iChkesp;
  LPSTR lpPrintBuffer;
  char  cTmpBuffer[4096];

  int   fn_strcpy(LPVOID lpStr1, LPVOID lpStr2);
  void  LastPrintBuff(char *szFormat, ...);
  void  ChangeLastPrintBuff(char c);
  void  ChangetoMinus();
  LPSTR GetString(WORD iNameIndex);

public:
  WORD          iInstructionLength;
  asmtable      *pFindTable;
  asminstdata   *pLastInstData;

  void          SwitchTo16Bit();
  void          SwitchTo32Bit();
  asminstdata   *GetInstruction(BYTE bCode, asminstdata *findasm);
  asminstdata   *FindCodeTable(LPBYTE cCodeBuffer);
  WORD          ArgLength(argtype a, byte modrmbyte, byte sibbyte, dword flgs, BOOL omode32); //NB modrm to add
  WORD          DecodeInstruction(LPBYTE cCodeBuffer, asminstdata *pCodeFound);
  void          DecodeArguments(LPBYTE cCodeBuffer, asminstdata *pCodeFound, argtype aArg);
  WORD          Disassembler(LPBYTE cCodeBuffer, DWORD lProcAddress);
  WORD          Disassembler(LPBYTE cCodeBuffer, DWORD lProcAddress, LPSTR lpBuffer);
  WORD          Disassembler(LPBYTE cCodeBuffer);
  DWORD         InsertCode(LPBYTE cCodeBuffer);
  DWORD         Transmutation(LPBYTE cInBuffer, DWORD iLength, LPBYTE cOutBuffer);
  DWORD         GetPrevInstructionLength(LPBYTE cCodeBuffer);
  DWORD         GetCallFunctionLength(LPBYTE cCodeBuffer);
  TFunctionInfo *ParseFunction(LPVOID cCodeBuffer, BOOL acceptOutsideCode);
  BOOL          CopyFunction(LPVOID lpFunc, HANDLE hProcess, BOOL acceptUnknownTargets,
                             LPVOID lpWriteBuffer);

  DWORD         GetVersion();
  LPSTR         GetVersionString();

  TDreamland();
  virtual       ~TDreamland();

};

//---------------------------------------------------------------------------
extern "C" void _chkesp(void);

//---------------------------------------------------------------------------
#endif