//---------------------------------------------------------------------------
#ifndef CryptoLibH
#define CryptoLibH
//---------------------------------------------------------------------------
#ifdef __BORLANDC__
#pragma option -a1			      //对齐方式为1字节
#endif //__BORLANDC__

#ifdef _MSC_VER
#pragma pack(1)				      //对齐方式为1字节
#endif //__MSC_VER
/* IDOK and IDERROR changed to ID_OK and ID_ERROR */
#define RSA_ID_OK           0
#define RSA_ID_ERROR        1
//---------------------------------------------------------------------------
#define IDEA_ENCRYPT	1
#define IDEA_DECRYPT	0

#define IDEA_INT        unsigned int
#define IDEA_BLOCK	8
#define IDEA_KEY_LENGTH	16

#ifndef UINT4
#define UINT4           unsigned int
#endif

#define RE_DATA         0x0401
#define RE_LEN          0x0406
#define RE_MODULUS_LEN  0x0407
#define RE_NEED_RANDOM  0x0408

/* RSA key lengths. */
#define MIN_RSA_MODULUS_BITS 508
#define MAX_RSA_MODULUS_BITS 2048
#define MAX_RSA_MODULUS_LEN  ((MAX_RSA_MODULUS_BITS + 7) / 8)
#define MAX_RSA_PRIME_BITS   ((MAX_RSA_MODULUS_BITS + 1) / 2)
#define MAX_RSA_PRIME_LEN    ((MAX_RSA_PRIME_BITS   + 7) / 8)

#define MAXKEYBYTES 56          /* 448 bits */

#define REDATA_FIX            11
//---------------------------------------------------------------------------
typedef struct idea_key_st
{
  IDEA_INT data[9][6];
}IDEA_KEY_SCHEDULE;

/* Random structure. */
typedef struct
{
  unsigned int bytesNeeded;                    /* seed bytes required */
  unsigned char state[16];                     /* state of object */
  unsigned int outputAvailable;                /* number byte available */
  unsigned char output[16];                    /* output bytes */
} R_RANDOM_STRUCT;

/* RSA public and private key. */
typedef struct
{
  unsigned short int bits;                     /* length in bits of modulus */
  unsigned char modulus[MAX_RSA_MODULUS_LEN];  /* modulus */
  unsigned char exponent[MAX_RSA_MODULUS_LEN]; /* public exponent */
} R_RSA_PUBLIC_KEY;

typedef struct
{
  unsigned short int bits;                               /* length in bits of modulus */
  unsigned char modulus[MAX_RSA_MODULUS_LEN];            /* modulus */
  unsigned char publicExponent[MAX_RSA_MODULUS_LEN];     /* public exponent */
  unsigned char exponent[MAX_RSA_MODULUS_LEN];           /* private exponent */
  unsigned char prime[2][MAX_RSA_PRIME_LEN];             /* prime factors */
  unsigned char primeExponent[2][MAX_RSA_PRIME_LEN];     /* exponents for CRT */
  unsigned char coefficient[MAX_RSA_PRIME_LEN];          /* CRT coefficient */
} R_RSA_PRIVATE_KEY;

/* RSA prototype key. */
typedef struct
{
  unsigned int bits;                           /* length in bits of modulus */
  int useFermat4;                              /* public exponent (1 = F4, 0 = 3) */
} R_RSA_PROTO_KEY;

typedef struct
{
  UINT4 subkeys[32];                                             /* subkeys */
  UINT4 iv[2];                                       /* initializing vector */
  UINT4 originalIV[2];                        /* for restarting the context */
  int encrypt;                                               /* encrypt flag */
} DES_CBC_CTX;

typedef struct
{
  UINT4 subkeys[32];                                             /* subkeys */
  UINT4 iv[2];                                       /* initializing vector */
  UINT4 inputWhitener[2];                                 /* input whitener */
  UINT4 outputWhitener[2];                               /* output whitener */
  UINT4 originalIV[2];                        /* for restarting the context */
  int encrypt;                                              /* encrypt flag */
} DESX_CBC_CTX;

typedef struct
{
  UINT4 subkeys[3][32];                     /* subkeys for three operations */
  UINT4 iv[2];                                       /* initializing vector */
  UINT4 originalIV[2];                        /* for restarting the context */
  int encrypt;                                              /* encrypt flag */
} DES3_CBC_CTX;

typedef struct
{
  unsigned long P[16 + 2];
  unsigned long S[4][256];
} BLOWFISH_CTX;
//---------------------------------------------------------------------------
#ifdef __BORLANDC__
#pragma option -a.
#endif //__BORLANDC__

#ifdef _MSC_VER
#pragma pack()
#endif //_MSC_VER
//---------------------------------------------------------------------------
#ifdef  __cplusplus
extern "C" {
#endif
/****************************************************************************
 * IDEA is a block cipher that operates on 64bit (8 byte) quantities.  It
 * uses a 128bit (16 byte) key.  It can be used in all the modes that DES can
 * be used.  This library implements the ecb, cbc, cfb64 and ofb64 modes.
 *
 * For all calls that have an 'input' and 'output' variables, they can be the
 * same.
 *
 * This library requires the inclusion of 'idea.h'.
 *
 * All of the encryption functions take what is called an IDEA_KEY_SCHEDULE as an
 * argument.  An IDEA_KEY_SCHEDULE is an expanded form of the idea key.
 * For all modes of the IDEA algorithm, the IDEA_KEY_SCHEDULE used for
 * decryption is different to the one used for encryption.
 *
 * The define IDEA_ENCRYPT is passed to specify encryption for the functions
 * that require an encryption/decryption flag. IDEA_DECRYPT is passed to
 * specify decryption.  For some mode there is no encryption/decryption
 * flag since this is determined by the IDEA_KEY_SCHEDULE.
 *
 * So to encrypt you would do the following
 * idea_set_encrypt_key(key,encrypt_ks);
 * idea_ecb_encrypt(...,encrypt_ks);
 * idea_cbc_encrypt(....,encrypt_ks,...,IDEA_ENCRYPT);
 *
 * To Decrypt
 * idea_set_encrypt_key(key,encrypt_ks);
 * idea_set_decrypt_key(encrypt_ks,decrypt_ks);
 * idea_ecb_encrypt(...,decrypt_ks);
 * idea_cbc_encrypt(....,decrypt_ks,...,IDEA_DECRYPT);
 ***************************************************************************/
void idea_ecb_encrypt(unsigned char *in, unsigned char *out, IDEA_KEY_SCHEDULE *ks);
void idea_set_encrypt_key(unsigned char *key, IDEA_KEY_SCHEDULE *ks);
void idea_set_decrypt_key(IDEA_KEY_SCHEDULE *ek, IDEA_KEY_SCHEDULE *dk);
void idea_cbc_encrypt(unsigned char *in, unsigned char *out,
                      long length, IDEA_KEY_SCHEDULE *ks, unsigned char *iv,int enc);
void idea_cfb64_encrypt(unsigned char *in, unsigned char *out,
                        long length, IDEA_KEY_SCHEDULE *ks, unsigned char *iv,
                        int *num,int enc);
void idea_ofb64_encrypt(unsigned char *in, unsigned char *out,
                        long length, IDEA_KEY_SCHEDULE *ks, unsigned char *iv, int *num);
void idea_encrypt(unsigned long *in, IDEA_KEY_SCHEDULE *ks);
//---------------------------------------------------------------------------
int R_RandomInit(R_RANDOM_STRUCT *);
int R_GetRandomBytesNeeded(unsigned int *, R_RANDOM_STRUCT *);
int R_RandomUpdate(R_RANDOM_STRUCT *, unsigned char *, unsigned int);
int R_GenerateBytes(unsigned char *, unsigned int, R_RANDOM_STRUCT *);
void R_RandomFinal(R_RANDOM_STRUCT *);
void R_RandomCreate(R_RANDOM_STRUCT *);
int R_GeneratePEMKeys(R_RSA_PUBLIC_KEY *, R_RSA_PRIVATE_KEY *, R_RSA_PROTO_KEY *, R_RANDOM_STRUCT *);
int RSAPublicEncrypt(unsigned char *, unsigned int *, unsigned char *, unsigned int, R_RSA_PUBLIC_KEY *, R_RANDOM_STRUCT *);
int RSAPrivateEncrypt(unsigned char *, unsigned int *, unsigned char *, unsigned int, R_RSA_PRIVATE_KEY *);
int RSAPublicDecrypt(unsigned char *, unsigned int *, unsigned char *, unsigned int, R_RSA_PUBLIC_KEY *);
int RSAPrivateDecrypt(unsigned char *, unsigned int *, unsigned char *, unsigned int, R_RSA_PRIVATE_KEY *);
//---------------------------------------------------------------------------
void DES_CBCInit(DES_CBC_CTX *, unsigned char *, unsigned char *, int);
int DES_CBCUpdate(DES_CBC_CTX *, unsigned char *, unsigned char *, unsigned int);
void DES_CBCRestart(DES_CBC_CTX *);

void DESX_CBCInit(DESX_CBC_CTX *, unsigned char *, unsigned char *, int);
int DESX_CBCUpdate(DESX_CBC_CTX *, unsigned char *, unsigned char *, unsigned int);
void DESX_CBCRestart(DESX_CBC_CTX *);

void DES3_CBCInit(DES3_CBC_CTX *, unsigned char *, unsigned char *, int);
int DES3_CBCUpdate(DES3_CBC_CTX *, unsigned char *, unsigned char *, unsigned int);
void DES3_CBCRestart(DES3_CBC_CTX *);
//---------------------------------------------------------------------------
void Blowfish_Init(BLOWFISH_CTX *ctx, unsigned char *key, int keyLen);
void Blowfish_Encrypt(BLOWFISH_CTX *ctx, unsigned long *xl, unsigned long *xr);
void Blowfish_Decrypt(BLOWFISH_CTX *ctx, unsigned long *xl, unsigned long *xr);
int Blowfish_Test(BLOWFISH_CTX *ctx);       /* 0=ok, -1=bad */
//---------------------------------------------------------------------------
void BaseXorAdd(unsigned char *szBuffer, int ulFileLen, char *szPassword, int iPasswordLen);
void BaseXorSub(unsigned char *szBuffer, int ulFileLen, char *szPassword, int iPasswordLen);
//---------------------------------------------------------------------------
#ifdef  __cplusplus
}
#endif
//---------------------------------------------------------------------------
#endif
