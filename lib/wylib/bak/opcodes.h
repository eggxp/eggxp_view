//                                              opcodes.h
//
#ifndef OpcodesH
  #define OpcodesH

//---------------------------------------------------------------------------
  #ifdef __BORLANDC__
    #pragma option -a1             //对齐方式为1字节
  #endif //__BORLANDC__
  #ifdef _MSC_VER
    #pragma pack(1)                 //对齐方式为1字节
  #endif //__MSC_VER						//如果不设置，默认的对齐

// basic type definitions.
typedef unsigned char       byte;
typedef unsigned short int  word;
typedef unsigned long       dword;
typedef char                *string;

//processor types
  #define PROC_8086       0x0001
  #define PROC_80286      0x0002
  #define PROC_80386      0x0004
  #define PROC_80486      0x0008
  #define PROC_PENTIUM    0x0010
  #define PROC_PENTMMX    0x0020
  #define PROC_PENTIUMPRO 0x0080
  #define PROC_PENTIUM2   0x0100
  #define PROC_PENTIUM3   0x0200
  #define PROC_AMD3DNOW   0x0400
  #define PROC_ALL        0xffff

//processor macros
  #define PROC_FROM3DNOW    PROC_AMD3DNOW
  #define PROC_FROMPENTIUM3 PROC_PENTIUM3
  #define PROC_FROMPENTIUM2 PROC_PENTIUM2 | PROC_FROMPENTIUM3
  #define PROC_FROMPENTMMX  PROC_PENTMMX | PROC_FROMPENTIUM2
  #define PROC_FROMPENTPRO  PROC_PENTIUMPRO | PROC_FROMPENTMMX
  #define PROC_FROMPENTIUM  PROC_PENTIUM | PROC_FROMPENTPRO
  #define PROC_FROM80486    PROC_80486 | PROC_FROMPENTIUM
  #define PROC_FROM80386    PROC_80386 | PROC_FROM80486
  #define PROC_FROM80286    PROC_80286 | PROC_FROM80386
  #define PROC_FROM8086     PROC_8086 | PROC_FROM80286

//flags
  #define FLAGS_MODRM       0x00001 //contains mod r/m byte
  #define FLAGS_8BIT        0x00002 //force 8-bit arguments
  #define FLAGS_16BIT       0x00004 //force 16-bit arguments
  #define FLAGS_32BIT       0x00008 //force 32-bit arguments
  #define FLAGS_REAL        0x00010 //real mode only
  #define FLAGS_PMODE       0x00020 //protected mode only
  #define FLAGS_PREFIX      0x00040 //for lock and rep prefix
  #define FLAGS_MMX         0x00080 //mmx instruction/registers
  #define FLAGS_FPU         0x00100 //fpu instruction/registers
  #define FLAGS_CJMP        0x00200 //codeflow - conditional jump
  #define FLAGS_JMP         0x00400 //codeflow - jump
  #define FLAGS_IJMP        0x00800 //codeflow - indexed jump
  #define FLAGS_CALL        0x01000 //codeflow - call
  #define FLAGS_ICALL       0x02000 //codeflow - indexed call
  #define FLAGS_RET         0x04000 //codeflow - return
  #define FLAGS_SEGPREFIX   0x08000 //segment prefix
  #define FLAGS_OPERPREFIX  0x10000 //operand prefix
  #define FLAGS_ADDRPREFIX  0x20000 //address prefix
  #define FLAGS_OMODE16     0x40000 //16-bit operand mode only
  #define FLAGS_OMODE32     0x80000 //32-bit operand mode only
  #define TABLE_MAIN        1
  #define TABLE_EXT         2
  #define TABLE_EXT2        3

enum argtype
{
  ARG_REG         = 1,
  ARG_IMM,
  ARG_NONE,
  ARG_MODRM,
  ARG_REG_AX,
  ARG_REG_ES,
  ARG_REG_CS,
  ARG_REG_SS,
  ARG_REG_DS,
  ARG_REG_FS,
  ARG_REG_GS,
  ARG_REG_BX,
  ARG_REG_CX,
  ARG_REG_DX,
  ARG_REG_SP,
  ARG_REG_BP,
  ARG_REG_SI,
  ARG_REG_DI,
  ARG_IMM8,
  ARG_RELIMM8,
  ARG_FADDR,
  ARG_REG_AL,
  ARG_MEMLOC,
  ARG_SREG,
  ARG_RELIMM,
  ARG_16REG_DX,
  ARG_REG_CL,
  ARG_REG_DL,
  ARG_REG_BL,
  ARG_REG_AH,
  ARG_REG_CH,
  ARG_REG_DH,
  ARG_REG_BH,
  ARG_MODREG,
  ARG_CREG,
  ARG_DREG,
  ARG_TREG_67,
  ARG_TREG,
  ARG_MREG,
  ARG_MMXMODRM,
  ARG_MODRM8,
  ARG_IMM_1,
  ARG_IMM_3,
  ARG_MODRM_FPTR,
  ARG_MODRM_S,
  ARG_MODRMM512,
  ARG_MODRMQ,
  ARG_MODRM_SREAL,
  ARG_REG_ST0,
  ARG_FREG,
  ARG_MODRM_PTR,
  ARG_MODRM_WORD,
  ARG_MODRM_SINT,
  ARG_MODRM_EREAL,
  ARG_MODRM_DREAL,
  ARG_MODRM_WINT,
  ARG_MODRM_LINT,
  ARG_IMM16_A,
  ARG_MODRM16,
  ARG_IMM8_IND,
  ARG_IMM32,
  ARG_IMM16,
  ARG_MEMLOC16,
  ARG_SIMM8,
  ARG_MODRM_BCD,
  ARG_NONEBYTE,
  ARG_XREG,
  ARG_XMMMODRM
};

enum opcodestype
{
  OPN_NONE        = 1,
  OPN_AAA,
  OPN_AAD,
  OPN_AAM,
  OPN_AAS,
  OPN_ADC,
  OPN_ADD,
  OPN_ADDPS,
  OPN_AND,
  OPN_ANDNPS,
  OPN_ANDPS,
  OPN_ARPL,
  OPN_BOUND,
  OPN_BSF,
  OPN_BSR,
  OPN_BSWAP,
  OPN_BT,
  OPN_BTC,
  OPN_BTR,
  OPN_BTS,
  OPN_CALL,
  OPN_CALLF,
  OPN_CBW,
  OPN_CDQ,
  OPN_CFLSH,
  OPN_CLC,
  OPN_CLD,
  OPN_CLI,
  OPN_CLTS,
  OPN_CMC,
  OPN_CMOVA,
  OPN_CMOVBE,
  OPN_CMOVC,
  OPN_CMOVG,
  OPN_CMOVGE,
  OPN_CMOVL,
  OPN_CMOVLE,
  OPN_CMOVNC,
  OPN_CMOVNO,
  OPN_CMOVNS,
  OPN_CMOVNZ,
  OPN_CMOVO,
  OPN_CMOVPE,
  OPN_CMOVPO,
  OPN_CMOVS,
  OPN_CMOVZ,
  OPN_CMP,
  OPN_CMPEQPS,
  OPN_CMPLEPS,
  OPN_CMPLTPS,
  OPN_CMPNEQPS,
  OPN_CMPNLEPS,
  OPN_CMPNLTPS,
  OPN_CMPORDPS,
  OPN_CMPSB,
  OPN_CMPSD,
  OPN_CMPSW,
  OPN_CMPUNORDPS,
  OPN_CMPXCH8B,
  OPN_CMPXCHG,
  OPN_CMPXCHG486,
  OPN_COMISS,
  OPN_CPUID,
  OPN_CS,
  OPN_CVTPI2PS,
  OPN_CVTPS2PI,
  OPN_CVTTPS2PI,
  OPN_CWD,
  OPN_CWDE,
  OPN_DAA,
  OPN_DAS,
  OPN_DEC,
  OPN_DIV,
  OPN_DIVPS,
  OPN_DS,
  OPN_EMMS,
  OPN_ENTER,
  OPN_ES,
  OPN_F2XM1,
  OPN_FABS,
  OPN_FADD,
  OPN_FADDP,
  OPN_FBLD,
  OPN_FBSTP,
  OPN_FCHS,
  OPN_FCLEX,
  OPN_FCMOVNB,
  OPN_FCMOVNBE,
  OPN_FCMOVNE,
  OPN_FCMOVNU,
  OPN_FCOM,
  OPN_FCOM2,
  OPN_FCOMI,
  OPN_FCOMIP,
  OPN_FCOMP,
  OPN_FCOMP3,
  OPN_FCOMP5,
  OPN_FCOMPP,
  OPN_FCOS,
  OPN_FDECSTP,
  OPN_FDISI,
  OPN_FDIV,
  OPN_FDIVP,
  OPN_FDIVR,
  OPN_FDIVRP,
  OPN_FEMMS,
  OPN_FENI,
  OPN_FFREE,
  OPN_FFREEP,
  OPN_FIADD,
  OPN_FICOM,
  OPN_FICOMP,
  OPN_FIDIV,
  OPN_FIDIVR,
  OPN_FILD,
  OPN_FIMUL,
  OPN_FINCSTP,
  OPN_FINIT,
  OPN_FIST,
  OPN_FISTP,
  OPN_FISUB,
  OPN_FISUBR,
  OPN_FLD,
  OPN_FLD1,
  OPN_FLDCW,
  OPN_FLDENV,
  OPN_FLDL2E,
  OPN_FLDL2T,
  OPN_FLDLG2,
  OPN_FLDLN2,
  OPN_FLDPI,
  OPN_FLDZ,
  OPN_FMOVB,
  OPN_FMOVBE,
  OPN_FMOVE,
  OPN_FMOVU,
  OPN_FMUL,
  OPN_FMULP,
  OPN_FNOP,
  OPN_FPATAN,
  OPN_FPREM,
  OPN_FPREM1,
  OPN_FPTAN,
  OPN_FRINEAR,
  OPN_FRINT2,
  OPN_FRNDINT,
  OPN_FRSTOR,
  OPN_FRSTPM,
  OPN_FS,
  OPN_FSAVE,
  OPN_FSCALE,
  OPN_FSETPM,
  OPN_FSIN,
  OPN_FSINCOS,
  OPN_FSQRT,
  OPN_FST,
  OPN_FSTCW,
  OPN_FSTDW,
  OPN_FSTENV,
  OPN_FSTP,
  OPN_FSTP8,
  OPN_FSTP9,
  OPN_FSTSG,
  OPN_FSTSW,
  OPN_FSUB,
  OPN_FSUBP,
  OPN_FSUBR,
  OPN_FSUBRP,
  OPN_FTST,
  OPN_FUCOM,
  OPN_FUCOMI,
  OPN_FUCOMIP,
  OPN_FUCOMP,
  OPN_FUCOMPP,
  OPN_FXAM,
  OPN_FXCH,
  OPN_FXCH4,
  OPN_FXCH7,
  OPN_FXRSTOR,
  OPN_FXSAVE,
  OPN_FXTRACT,
  OPN_FYL2X,
  OPN_FYL2XP1,
  OPN_GS,
  OPN_HLT,
  OPN_IDIV,
  OPN_IMUL,
  OPN_IN,
  OPN_INC,
  OPN_INSB,
  OPN_INSD,
  OPN_INSW,
  OPN_INT,
  OPN_INTO,
  OPN_INVD,
  OPN_INVLPG,
  OPN_IRET,
  OPN_JA,
  OPN_JBE,
  OPN_JC,
  OPN_JCXZ,
  OPN_JG,
  OPN_JGE,
  OPN_JL,
  OPN_JLE,
  OPN_JMP,
  OPN_JNC,
  OPN_JNO,
  OPN_JNS,
  OPN_JNZ,
  OPN_JO,
  OPN_JPE,
  OPN_JPO,
  OPN_JS,
  OPN_JZ,
  OPN_LAHF,
  OPN_LAR,
  OPN_LDMXCSR,
  OPN_LDS,
  OPN_LEA,
  OPN_LEAVE,
  OPN_LES,
  OPN_LFS,
  OPN_LGDT,
  OPN_LGS,
  OPN_LIDT,
  OPN_LLDT,
  OPN_LMSW,
  OPN_LOCK,
  OPN_LODSB,
  OPN_LODSD,
  OPN_LODSW,
  OPN_LOOP,
  OPN_LOOPNZ,
  OPN_LOOPZ,
  OPN_LSL,
  OPN_LSS,
  OPN_LTR,
  OPN_MASKMOVQ,
  OPN_MAXPS,
  OPN_MINPS,
  OPN_MOV,
  OPN_MOVAPS,
  OPN_MOVD,
  OPN_MOVHPS,
  OPN_MOVLPS,
  OPN_MOVMSKPS,
  OPN_MOVNTPS,
  OPN_MOVNTQ,
  OPN_MOVQ,
  OPN_MOVSB,
  OPN_MOVSD,
  OPN_MOVSW,
  OPN_MOVSX,
  OPN_MOVUPS,
  OPN_MOVZX,
  OPN_MUL,
  OPN_MULPS,
  OPN_NEG,
  OPN_NOP,
  OPN_NOT,
  OPN_OR,
  OPN_ORPS,
  OPN_OUT,
  OPN_OUTSB,
  OPN_OUTSD,
  OPN_OUTSW,
  OPN_PACKSSDW,
  OPN_PACKSSWB,
  OPN_PACKUSWB,
  OPN_PADDB,
  OPN_PADDD,
  OPN_PADDSB,
  OPN_PADDSW,
  OPN_PADDUSB,
  OPN_PADDUSW,
  OPN_PADDW,
  OPN_PAND,
  OPN_PANDN,
  OPN_PAVGB,
  OPN_PAVGW,
  OPN_PCMPEQB,
  OPN_PCMPEQD,
  OPN_PCMPEQW,
  OPN_PCMPGTB,
  OPN_PCMPGTD,
  OPN_PCMPGTW,
  OPN_PEXTRW,
  OPN_PINSRW,
  OPN_PMADDWD,
  OPN_PMAXSW,
  OPN_PMAXUB,
  OPN_PMINSW,
  OPN_PMINUB,
  OPN_PMOVMSKB,
  OPN_PMULHUW,
  OPN_PMULHW,
  OPN_PMULLW,
  OPN_POP,
  OPN_POPA,
  OPN_POPAD,
  OPN_POPF,
  OPN_POPFD,
  OPN_POR,
  OPN_PREFETCHNTA,
  OPN_PREFETCHT0,
  OPN_PREFETCHT1,
  OPN_PREFETCHT2,
  OPN_PSADBW,
  OPN_PSHUF,
  OPN_PSLLD,
  OPN_PSLLQ,
  OPN_PSLLW,
  OPN_PSRAD,
  OPN_PSRAW,
  OPN_PSRLD,
  OPN_PSRLQ,
  OPN_PSRLW,
  OPN_PSUBB,
  OPN_PSUBD,
  OPN_PSUBSB,
  OPN_PSUBSW,
  OPN_PSUBUSB,
  OPN_PSUBUSW,
  OPN_PSUBW,
  OPN_PUNPCKHBW,
  OPN_PUNPCKHDQ,
  OPN_PUNPCKHWD,
  OPN_PUNPCKLBW,
  OPN_PUNPCKLDQ,
  OPN_PUNPCKLWD,
  OPN_PUSH,
  OPN_PUSHA,
  OPN_PUSHAD,
  OPN_PUSHF,
  OPN_PUSHFD,
  OPN_PXOR,
  OPN_RCL,
  OPN_RCPPS,
  OPN_RCR,
  OPN_RDMSR,
  OPN_RDPMC,
  OPN_RDTSC,
  OPN_REP,
  OPN_REPNE,
  OPN_RET,
  OPN_RETF,
  OPN_ROL,
  OPN_ROR,
  OPN_RSM,
  OPN_RSQRTPS,
  OPN_SAHF,
  OPN_SAL,
  OPN_SAR,
  OPN_SBB,
  OPN_SCASB,
  OPN_SCASD,
  OPN_SCASW,
  OPN_SETA,
  OPN_SETALC,
  OPN_SETBE,
  OPN_SETC,
  OPN_SETG,
  OPN_SETGE,
  OPN_SETL,
  OPN_SETLE,
  OPN_SETNC,
  OPN_SETNO,
  OPN_SETNS,
  OPN_SETNZ,
  OPN_SETO,
  OPN_SETPE,
  OPN_SETPO,
  OPN_SETS,
  OPN_SETZ,
  OPN_SFENCE,
  OPN_SGDT,
  OPN_SHL,
  OPN_SHLD,
  OPN_SHR,
  OPN_SHRD,
  OPN_SHUFPS,
  OPN_SIDT,
  OPN_SLDT,
  OPN_SMI,
  OPN_SMSW,
  OPN_SQRTPS,
  OPN_SS,
  OPN_STC,
  OPN_STD,
  OPN_STI,
  OPN_STMXCSR,
  OPN_STOSB,
  OPN_STOSD,
  OPN_STOSW,
  OPN_STR,
  OPN_SUB,
  OPN_SUBPS,
  OPN_SYSCALL,
  OPN_SYSENTER,
  OPN_SYSEXIT,
  OPN_SYSRET,
  OPN_TEST,
  OPN_UCOMISS,
  OPN_UD1,
  OPN_UD2,
  OPN_UNPCKHPS,
  OPN_UNPCKLPS,
  OPN_VERR,
  OPN_VERW,
  OPN_WAIT,
  OPN_WBINVD,
  OPN_WRMSR,
  OPN_XADD,
  OPN_XCHG,
  OPN_XLAT,
  OPN_XOR,
  OPN_XORPS
};

struct asminstdata                  //Asm Instructions data
{
  word  name;                       //eg nop,NULL=subtable/undefined
  byte  instbyte;                   //   0x90/subtable number
  word  processor;                  //   8086|386|486|pentium,etc bitwise flags
  dword flags;                      //   mod r/m,8/16/32 bit
  byte  arg1, arg2, arg3;           //   argtypes=reg/none/immediate,etc
};

struct asmtable                     //Assembly instruction tables
{
  asminstdata *table;               //Pointer to table of instruction encodings
  byte        type;                 // type - main table/extension
  byte        extnum, extnum2;      // bytes= first bytes of instruction
  byte        divisor;              // number to divide by for look up
  byte        mask;                 // bit mask for look up
  byte        minlim, maxlim;       // limits on min/max entries.
  byte        modrmpos;             // modrm byte position plus
};

extern asmtable tables86[];

extern char     *reg32ascii[];
extern char     *reg16ascii[];
extern char     *reg8ascii[];
extern char     *regind16ascii[];
extern char     *regfascii[];
extern char     *regmascii[];
extern char     *regxascii[];
extern char     *regsascii[];
extern char     *regcascii[];
extern char     *regdascii[];
extern char     *regtascii[];
extern char     *opcodesname[];
extern bool     bHasOpcodesName;

  #define REG_AX  0x0000
  #define REG_CX  0x0001
  #define REG_DX  0x0002
  #define REG_BX  0x0003
  #define REG_SP  0x0004
  #define REG_BP  0x0005
  #define REG_SI  0x0006
  #define REG_DI  0x0007

  #ifdef __BORLANDC__
    #pragma option -a.
  #endif //__BORLANDC__
  #ifdef _MSC_VER
    #pragma pack()
  #endif //_MSC_VER
#endif