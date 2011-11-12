/***************************************************************************
 *  File name CryptoLib.cpp                                                *
 *  Version:  1.00.02a                                                     *
 *  Author:   yypcn                                                        *
 *  Target:   Crypto Library, include IDEA, RSA, DES, BLOWFISH, BASEXOR    *
 *                                                                         *
 *  History                                                                *
 *  01-17-2003    02:50am  First version.                                  *
 *                                                                         *
 ***************************************************************************/
#include <time.h>
#include <stdio.h>
#include <string.h>
#pragma hdrstop

#include "CryptoLib.h"
//---------------------------------------------------------------------------
#define R_memcpy              memcpy
#define R_memset              memset

#define TRUE            1
#define FALSE           0

/* POINTER defines a generic pointer type */
typedef unsigned char *POINTER;
typedef unsigned short UINT2;
typedef unsigned char BYTE;
typedef UINT4 NN_DIGIT;
typedef UINT2 NN_HALF_DIGIT;

/* Length of digit in bits */
#define NN_DIGIT_BITS 32
#define NN_HALF_DIGIT_BITS 16
/* Length of digit in bytes */
#define NN_DIGIT_LEN (NN_DIGIT_BITS / 8)
/* Maximum length in digits */
#define MAX_NN_DIGITS \
  ((MAX_RSA_MODULUS_LEN + NN_DIGIT_LEN - 1) / NN_DIGIT_LEN + 1)
/* Maximum digits */
#define MAX_NN_DIGIT 0xffffffff
#define MAX_NN_HALF_DIGIT 0xffff

#define NN_LT   -1
#define NN_EQ   0
#define NN_GT 1

/* Macros. */

#define LOW_HALF(x) ((x) & MAX_NN_HALF_DIGIT)
#define HIGH_HALF(x) (((x) >> NN_HALF_DIGIT_BITS) & MAX_NN_HALF_DIGIT)
#define TO_HIGH_HALF(x) (((NN_DIGIT)(x)) << NN_HALF_DIGIT_BITS)
#define DIGIT_MSB(x) (unsigned int)(((x) >> (NN_DIGIT_BITS - 1)) & 1)
#define DIGIT_2MSB(x) (unsigned int)(((x) >> (NN_DIGIT_BITS - 2)) & 3)

void NN_Decode (NN_DIGIT *, unsigned int, unsigned char *, unsigned int);
void NN_Encode (unsigned char *, unsigned int, NN_DIGIT *, unsigned int);

void NN_Assign (NN_DIGIT *, NN_DIGIT *, unsigned int);
void NN_AssignZero (NN_DIGIT *, unsigned int);
void NN_Assign2Exp (NN_DIGIT *, unsigned int, unsigned int);

NN_DIGIT NN_Add (NN_DIGIT *, NN_DIGIT *, NN_DIGIT *, unsigned int);
NN_DIGIT NN_Sub (NN_DIGIT *, NN_DIGIT *, NN_DIGIT *, unsigned int);
void NN_Mult (NN_DIGIT *, NN_DIGIT *, NN_DIGIT *, unsigned int);
void NN_Div (NN_DIGIT *, NN_DIGIT *, NN_DIGIT *, unsigned int, NN_DIGIT *,
		unsigned int);
NN_DIGIT NN_LShift (NN_DIGIT *, NN_DIGIT *, unsigned int, unsigned int);
NN_DIGIT NN_RShift (NN_DIGIT *, NN_DIGIT *, unsigned int, unsigned int);
NN_DIGIT NN_LRotate (NN_DIGIT *, NN_DIGIT *, unsigned int, unsigned int);

void NN_Mod (NN_DIGIT *, NN_DIGIT *, unsigned int, NN_DIGIT *, unsigned int);
void NN_ModMult (NN_DIGIT *, NN_DIGIT *, NN_DIGIT *, NN_DIGIT *, unsigned int);
void NN_ModExp (NN_DIGIT *, NN_DIGIT *, NN_DIGIT *, unsigned int, NN_DIGIT *,
		unsigned int);
void NN_ModInv (NN_DIGIT *, NN_DIGIT *, NN_DIGIT *, unsigned int);
void NN_Gcd (NN_DIGIT *, NN_DIGIT *, NN_DIGIT *, unsigned int);

int NN_Cmp (NN_DIGIT *, NN_DIGIT *, unsigned int);
int NN_Zero (NN_DIGIT *, unsigned int);
unsigned int NN_Bits (NN_DIGIT *, unsigned int);
unsigned int NN_Digits (NN_DIGIT *, unsigned int);

#define NN_ASSIGN_DIGIT(a, b, digits) {NN_AssignZero (a, digits); a[0] = b;}
#define NN_EQUAL(a, b, digits) (! NN_Cmp (a, b, digits))
#define NN_EVEN(a, digits) (((digits) == 0) || ! (a[0] & 1))
//---------------------------------------------------------------------------
/* MD5 context. */
typedef struct
{
  UINT4 state[4];                                   /* state (ABCD) */
  UINT4 count[2];                                   /* number of bits, modulo 2^64 (lsb first) */
  unsigned char buffer[64];                         /* input buffer */
}C_MD5_CTX;

void c_MD5Init(C_MD5_CTX *);
void c_MD5Update(C_MD5_CTX *, unsigned char *, unsigned int);
void c_MD5Final(unsigned char [16], C_MD5_CTX *);
//---------------------------------------------------------------------------
// idea
//---------------------------------------------------------------------------
#define idea_mul(r,a,b,ul) \
ul=(unsigned long)a*b; \
if (ul != 0) \
	{ \
	r=(ul&0xffff)-(ul>>16); \
	r-=((r)>>16); \
	} \
else \
	r=(-(int)a-b+1); /* assuming a or b is 0 and in range */ \

#ifdef undef
#define idea_mul(r,a,b,ul,sl) \
if (a == 0) r=(0x10001-b)&0xffff; \
else if (b == 0) r=(0x10001-a)&0xffff; \
else	{ \
	ul=(unsigned long)a*b; \
	sl=(ul&0xffff)-(ul>>16); \
	if (sl <= 0) sl+=0x10001; \
	r=sl; \
	} 
#endif

#define n2ln(c,l1,l2,n)	{ \
			c+=n; \
			l1=l2=0; \
			switch (n) { \
			case 8: l2 =((unsigned long)(*(--(c))))    ; \
			case 7: l2|=((unsigned long)(*(--(c))))<< 8; \
			case 6: l2|=((unsigned long)(*(--(c))))<<16; \
			case 5: l2|=((unsigned long)(*(--(c))))<<24; \
			case 4: l1 =((unsigned long)(*(--(c))))    ; \
			case 3: l1|=((unsigned long)(*(--(c))))<< 8; \
			case 2: l1|=((unsigned long)(*(--(c))))<<16; \
			case 1: l1|=((unsigned long)(*(--(c))))<<24; \
				} \
			}

/* NOTE - c is not incremented as per l2n */
#define l2nn(l1,l2,c,n)	{ \
			c+=n; \
			switch (n) { \
			case 8: *(--(c))=(unsigned char)(((l2)    )&0xff); \
			case 7: *(--(c))=(unsigned char)(((l2)>> 8)&0xff); \
			case 6: *(--(c))=(unsigned char)(((l2)>>16)&0xff); \
			case 5: *(--(c))=(unsigned char)(((l2)>>24)&0xff); \
			case 4: *(--(c))=(unsigned char)(((l1)    )&0xff); \
			case 3: *(--(c))=(unsigned char)(((l1)>> 8)&0xff); \
			case 2: *(--(c))=(unsigned char)(((l1)>>16)&0xff); \
			case 1: *(--(c))=(unsigned char)(((l1)>>24)&0xff); \
				} \
			}

#undef n2l
#define n2l(c,l)        (l =((unsigned long)(*((c)++)))<<24L, \
                         l|=((unsigned long)(*((c)++)))<<16L, \
                         l|=((unsigned long)(*((c)++)))<< 8L, \
                         l|=((unsigned long)(*((c)++))))

#undef l2n
#define l2n(l,c)        (*((c)++)=(unsigned char)(((l)>>24L)&0xff), \
                         *((c)++)=(unsigned char)(((l)>>16L)&0xff), \
                         *((c)++)=(unsigned char)(((l)>> 8L)&0xff), \
                         *((c)++)=(unsigned char)(((l)     )&0xff))

#undef s2n
#define s2n(l,c)	(*((c)++)=(unsigned char)(((l)     )&0xff), \
			 *((c)++)=(unsigned char)(((l)>> 8L)&0xff))

#undef n2s
#define n2s(c,l)	(l =((IDEA_INT)(*((c)++)))<< 8L, \
			 l|=((IDEA_INT)(*((c)++)))      )

#ifdef undef
/* NOTE - c is not incremented as per c2l */
#define c2ln(c,l1,l2,n)	{ \
			c+=n; \
			l1=l2=0; \
			switch (n) { \
			case 8: l2 =((unsigned long)(*(--(c))))<<24; \
			case 7: l2|=((unsigned long)(*(--(c))))<<16; \
			case 6: l2|=((unsigned long)(*(--(c))))<< 8; \
			case 5: l2|=((unsigned long)(*(--(c))));     \
			case 4: l1 =((unsigned long)(*(--(c))))<<24; \
			case 3: l1|=((unsigned long)(*(--(c))))<<16; \
			case 2: l1|=((unsigned long)(*(--(c))))<< 8; \
			case 1: l1|=((unsigned long)(*(--(c))));     \
				} \
			}

/* NOTE - c is not incremented as per l2c */
#define l2cn(l1,l2,c,n)	{ \
			c+=n; \
			switch (n) { \
			case 8: *(--(c))=(unsigned char)(((l2)>>24)&0xff); \
			case 7: *(--(c))=(unsigned char)(((l2)>>16)&0xff); \
			case 6: *(--(c))=(unsigned char)(((l2)>> 8)&0xff); \
			case 5: *(--(c))=(unsigned char)(((l2)    )&0xff); \
			case 4: *(--(c))=(unsigned char)(((l1)>>24)&0xff); \
			case 3: *(--(c))=(unsigned char)(((l1)>>16)&0xff); \
			case 2: *(--(c))=(unsigned char)(((l1)>> 8)&0xff); \
			case 1: *(--(c))=(unsigned char)(((l1)    )&0xff); \
				} \
			}

#undef c2s
#define c2s(c,l)	(l =((unsigned long)(*((c)++)))    , \
			 l|=((unsigned long)(*((c)++)))<< 8L)

#undef s2c
#define s2c(l,c)	(*((c)++)=(unsigned char)(((l)     )&0xff), \
			 *((c)++)=(unsigned char)(((l)>> 8L)&0xff))

#undef c2l
#define c2l(c,l)	(l =((unsigned long)(*((c)++)))     , \
			 l|=((unsigned long)(*((c)++)))<< 8L, \
			 l|=((unsigned long)(*((c)++)))<<16L, \
			 l|=((unsigned long)(*((c)++)))<<24L)

#undef l2c
#define l2c(l,c)	(*((c)++)=(unsigned char)(((l)     )&0xff), \
			 *((c)++)=(unsigned char)(((l)>> 8L)&0xff), \
			 *((c)++)=(unsigned char)(((l)>>16L)&0xff), \
			 *((c)++)=(unsigned char)(((l)>>24L)&0xff))
#endif

#define E_IDEA(num) \
	x1&=0xffff; \
	idea_mul(x1,x1,*p,ul); p++; \
	x2+= *(p++); \
	x3+= *(p++); \
	x4&=0xffff; \
	idea_mul(x4,x4,*p,ul); p++; \
	t0=(x1^x3)&0xffff; \
	idea_mul(t0,t0,*p,ul); p++; \
	t1=(t0+(x2^x4))&0xffff; \
	idea_mul(t1,t1,*p,ul); p++; \
	t0+=t1; \
	x1^=t1; \
	x4^=t0; \
	ul=x2^t0; /* do the swap to x3 */ \
	x2=x3^t1; \
	x3=ul;


void idea_cbc_encrypt(unsigned char *in, unsigned char *out, long length,
                      IDEA_KEY_SCHEDULE *ks, unsigned char *iv, int encrypt)
{
	register unsigned long tin0,tin1;
	register unsigned long tout0,tout1,xor0,xor1;
	register long l=length;
	unsigned long tin[2];

	if (encrypt)
		{
		n2l(iv,tout0);
		n2l(iv,tout1);
		iv-=8;
		for (l-=8; l>=0; l-=8)
			{
			n2l(in,tin0);
			n2l(in,tin1);
			tin0^=tout0;
			tin1^=tout1;
			tin[0]=tin0;
			tin[1]=tin1;
			idea_encrypt(tin,ks);
			tout0=tin[0]; l2n(tout0,out);
			tout1=tin[1]; l2n(tout1,out);
			}
		if (l != -8)
			{
			n2ln(in,tin0,tin1,l+8);
			tin0^=tout0;
			tin1^=tout1;
			tin[0]=tin0;
			tin[1]=tin1;
			idea_encrypt(tin,ks);
			tout0=tin[0]; l2n(tout0,out);
			tout1=tin[1]; l2n(tout1,out);
			}
		l2n(tout0,iv);
		l2n(tout1,iv);
		}
	else
		{
		n2l(iv,xor0);
		n2l(iv,xor1);
		iv-=8;
		for (l-=8; l>=0; l-=8)
			{
			n2l(in,tin0); tin[0]=tin0;
			n2l(in,tin1); tin[1]=tin1;
			idea_encrypt(tin,ks);
			tout0=tin[0]^xor0;
			tout1=tin[1]^xor1;
			l2n(tout0,out);
			l2n(tout1,out);
			xor0=tin0;
			xor1=tin1;
			}
		if (l != -8)
			{
			n2l(in,tin0); tin[0]=tin0;
			n2l(in,tin1); tin[1]=tin1;
			idea_encrypt(tin,ks);
			tout0=tin[0]^xor0;
			tout1=tin[1]^xor1;
			l2nn(tout0,tout1,out,l+8);
			xor0=tin0;
			xor1=tin1;
			}
		l2n(xor0,iv);
		l2n(xor1,iv);
		}
	tin0=tin1=tout0=tout1=xor0=xor1=0;
	tin[0]=tin[1]=0;
}

void idea_encrypt(unsigned long *d, IDEA_KEY_SCHEDULE *key)
{
	register IDEA_INT *p;
	register unsigned long x1,x2,x3,x4,t0,t1,ul;

	x2=d[0];
	x1=(x2>>16);
	x4=d[1];
	x3=(x4>>16);

	p= &(key->data[0][0]);

	E_IDEA(0);
	E_IDEA(1);
	E_IDEA(2);
	E_IDEA(3);
	E_IDEA(4);
	E_IDEA(5);
	E_IDEA(6);
	E_IDEA(7);

	x1&=0xffff;
	idea_mul(x1,x1,*p,ul); p++;

	t0= x3+ *(p++);
	t1= x2+ *(p++);

	x4&=0xffff;
	idea_mul(x4,x4,*p,ul);

	d[0]=(t0&0xffff)|((x1&0xffff)<<16);
	d[1]=(x4&0xffff)|((t1&0xffff)<<16);
	}

void idea_cfb64_encrypt(unsigned char *in, unsigned char *out, long length,
                        IDEA_KEY_SCHEDULE *schedule, unsigned char *ivec, int *num, int encrypt)
{
	register unsigned long v0,v1,t;
	register int n= *num;
	register long l=length;
	unsigned long ti[2];
	unsigned char *iv,c,cc;

	iv=(unsigned char *)ivec;
	if (encrypt)
		{
		while (l--)
			{
			if (n == 0)
				{
				n2l(iv,v0); ti[0]=v0;
				n2l(iv,v1); ti[1]=v1;
				idea_encrypt((unsigned long *)ti,schedule);
				iv=(unsigned char *)ivec;
				t=ti[0]; l2n(t,iv);
				t=ti[1]; l2n(t,iv);
				iv=(unsigned char *)ivec;
				}
			c= *(in++)^iv[n];
			*(out++)=c;
			iv[n]=c;
			n=(n+1)&0x07;
			}
		}
	else
		{
		while (l--)
			{
			if (n == 0)
				{
				n2l(iv,v0); ti[0]=v0;
				n2l(iv,v1); ti[1]=v1;
				idea_encrypt((unsigned long *)ti,schedule);
				iv=(unsigned char *)ivec;
				t=ti[0]; l2n(t,iv);
				t=ti[1]; l2n(t,iv);
				iv=(unsigned char *)ivec;
				}
			cc= *(in++);
			c=iv[n];
			iv[n]=cc;
			*(out++)=c^cc;
			n=(n+1)&0x07;
			}
		}
	v0=v1=ti[0]=ti[1]=t=c=cc=0;
	*num=n;
}

void idea_ofb64_encrypt(unsigned char *in, unsigned char *out, long length,
                        IDEA_KEY_SCHEDULE *schedule, unsigned char *ivec, int *num)
{
	register unsigned long v0,v1,t;
	register int n= *num;
	register long l=length;
	unsigned char d[8];
	register char *dp;
	unsigned long ti[2];
	unsigned char *iv;
	int save=0;

	iv=(unsigned char *)ivec;
	n2l(iv,v0);
	n2l(iv,v1);
	ti[0]=v0;
	ti[1]=v1;
	dp=(char *)d;
	l2n(v0,dp);
	l2n(v1,dp);
	while (l--)
		{
		if (n == 0)
			{
			idea_encrypt((unsigned long *)ti,schedule);
			dp=(char *)d;
			t=ti[0]; l2n(t,dp);
			t=ti[1]; l2n(t,dp);
			save++;
			}
		*(out++)= *(in++)^d[n];
		n=(n+1)&0x07;
		}
	if (save)
		{
		v0=ti[0];
		v1=ti[1];
		iv=(unsigned char *)ivec;
		l2n(v0,iv);
		l2n(v1,iv);
		}
	t=v0=v1=ti[0]=ti[1]=0;
	*num=n;
}


static IDEA_INT inverse(unsigned int xin);

void idea_set_encrypt_key(unsigned char *key, IDEA_KEY_SCHEDULE *ks)
{
	int i;
	register IDEA_INT *kt,*kf,r0,r1,r2;

	kt= &(ks->data[0][0]);
	n2s(key,kt[0]); n2s(key,kt[1]); n2s(key,kt[2]); n2s(key,kt[3]);
	n2s(key,kt[4]); n2s(key,kt[5]); n2s(key,kt[6]); n2s(key,kt[7]);

	kf=kt;
	kt+=8;
	for (i=0; i<6; i++)
		{
		r2= kf[1];
		r1= kf[2];
		*(kt++)= ((r2<<9) | (r1>>7))&0xffff;
		r0= kf[3];
		*(kt++)= ((r1<<9) | (r0>>7))&0xffff;
		r1= kf[4];
		*(kt++)= ((r0<<9) | (r1>>7))&0xffff;
		r0= kf[5];
		*(kt++)= ((r1<<9) | (r0>>7))&0xffff;
		r1= kf[6];
		*(kt++)= ((r0<<9) | (r1>>7))&0xffff;
		r0= kf[7];
		*(kt++)= ((r1<<9) | (r0>>7))&0xffff;
		r1= kf[0];
		if (i >= 5) break;
		*(kt++)= ((r0<<9) | (r1>>7))&0xffff;
		*(kt++)= ((r1<<9) | (r2>>7))&0xffff;
		kf+=8;
		}
	}

void idea_set_decrypt_key(IDEA_KEY_SCHEDULE *ek, IDEA_KEY_SCHEDULE *dk)
{
	int r;
	register IDEA_INT *fp,*tp,t;

	tp= &(dk->data[0][0]);
	fp= &(ek->data[8][0]);
	for (r=0; r<9; r++)
		{
		*(tp++)=inverse(fp[0]);
		*(tp++)=((int)(0x10000L-fp[2])&0xffff);
		*(tp++)=((int)(0x10000L-fp[1])&0xffff);
		*(tp++)=inverse(fp[3]);
		if (r == 8) break;
		fp-=6;
		*(tp++)=fp[4];
		*(tp++)=fp[5];
		}

	tp= &(dk->data[0][0]);
	t=tp[1];
	tp[1]=tp[2];
	tp[2]=t;

	t=tp[49];
	tp[49]=tp[50];
	tp[50]=t;
	}

static IDEA_INT inverse(unsigned int xin)
{
	long n1,n2,q,r,b1,b2,t;

	if (xin == 0)
		b2=0;
	else
		{
		n1=0x10001;
		n2=xin;
		b2=1;
		b1=0;

		do	{
			r=(n1%n2);
			q=(n1-r)/n2;
			if (r == 0)
				{ if (b2 < 0) b2=0x10001+b2; }
			else
				{
				n1=n2;
				n2=r;
				t=b2;
				b2=b1-q*b2;
				b1=t;
				}
			} while (r != 0);
		}
	return((IDEA_INT)b2);
}

void idea_ecb_encrypt(unsigned char *in, unsigned char *out, IDEA_KEY_SCHEDULE *ks)
{
	unsigned long l0,l1,d[2];

	n2l(in,l0); d[0]=l0;
	n2l(in,l1); d[1]=l1;
	idea_encrypt(d,ks);
	l0=d[0]; l2n(l0,out);
	l1=d[1]; l2n(l1,out);
	l0=l1=d[0]=d[1]=0;
}
//---------------------------------------------------------------------------
// md5
//---------------------------------------------------------------------------
/* Constants for MD5Transform routine. */
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

static void MD5Transform(UINT4 [4], unsigned char [64]);
static void Encode(unsigned char *, UINT4 *, unsigned int);
static void Decode(UINT4 *, unsigned char *, unsigned int);

static unsigned char PADDING[64] =
{
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

/* F, G, H and I are basic MD5 functions. */
#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

/* ROTATE_LEFT rotates x left n bits. */
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

/* FF, GG, HH, and II transformations for rounds 1, 2, 3, and 4.
	 Rotation is separate from addition to prevent recomputation.
 */
#define FF(a, b, c, d, x, s, ac) { \
		(a) += F ((b), (c), (d)) + (x) + (UINT4)(ac); \
		(a) = ROTATE_LEFT ((a), (s)); \
		(a) += (b); \
	}
#define GG(a, b, c, d, x, s, ac) { \
		(a) += G ((b), (c), (d)) + (x) + (UINT4)(ac); \
		(a) = ROTATE_LEFT ((a), (s)); \
		(a) += (b); \
	}
#define HH(a, b, c, d, x, s, ac) { \
		(a) += H ((b), (c), (d)) + (x) + (UINT4)(ac); \
		(a) = ROTATE_LEFT ((a), (s)); \
		(a) += (b); \
	}
#define II(a, b, c, d, x, s, ac) { \
		(a) += I ((b), (c), (d)) + (x) + (UINT4)(ac); \
		(a) = ROTATE_LEFT ((a), (s)); \
		(a) += (b); \
	}

/* MD5 initialization. Begins an MD5 operation, writing a new context. */
void c_MD5Init(C_MD5_CTX *context)
{
  context->count[0] = context->count[1] = 0;

  /* Load magic initialization constants.
   */
  context->state[0] = 0x67452301;
  context->state[1] = 0xefcdab89;
  context->state[2] = 0x98badcfe;
  context->state[3] = 0x10325476;
}

/* MD5 block update operation. Continues an MD5 message-digest
	 operation, processing another message block, and updating the
	 context. */

void c_MD5Update(C_MD5_CTX *context, unsigned char *input, unsigned int inputLen)
{
  unsigned int i, index, partLen;

  /* Compute number of bytes mod 64 */
  index = (unsigned int)((context->count[0] >> 3) & 0x3F);

  /* Update number of bits */
  if((context->count[0] += ((UINT4)inputLen << 3)) < ((UINT4)inputLen << 3))
          context->count[1]++;

  context->count[1] += ((UINT4)inputLen >> 29);

  partLen = 64 - index;

  /* Transform as many times as possible.
   */
  if(inputLen >= partLen)
  {
    R_memcpy((POINTER)&context->buffer[index], (POINTER)input, partLen);
    MD5Transform(context->state, context->buffer);

    for(i = partLen; i + 63 < inputLen; i += 64)
      MD5Transform(context->state, &input[i]);

    index = 0;
  }
  else
    i = 0;

  /* Buffer remaining input */
  R_memcpy((POINTER)&context->buffer[index], (POINTER)&input[i], inputLen-i);
}

/* MD5 finalization. Ends an MD5 message-digest operation, writing the
	 the message digest and zeroizing the context. */

void c_MD5Final(unsigned char digest[16], C_MD5_CTX *context)
{
  unsigned char bits[8];
  unsigned int index, padLen;

  /* Save number of bits */
  Encode(bits, context->count, 8);

  /* Pad out to 56 mod 64.
   */
  index = (unsigned int)((context->count[0] >> 3) & 0x3f);
  padLen = (index < 56) ? (56 - index) : (120 - index);
  c_MD5Update(context, PADDING, padLen);

  /* Append length (before padding) */
  c_MD5Update(context, bits, 8);

  /* Store state in digest */
  Encode(digest, context->state, 16);

  /* Zeroize sensitive information. */

  R_memset((POINTER)context, 0, sizeof(*context));
}

/* MD5 basic transformation. Transforms state based on block. */

static void MD5Transform(UINT4 state[4], unsigned char block[64])
{
  UINT4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];

  Decode(x, block, 64);

  /* Round 1 */
  FF(a, b, c, d, x[ 0], S11, 0xd76aa478); /* 1 */
  FF(d, a, b, c, x[ 1], S12, 0xe8c7b756); /* 2 */
  FF(c, d, a, b, x[ 2], S13, 0x242070db); /* 3 */
  FF(b, c, d, a, x[ 3], S14, 0xc1bdceee); /* 4 */
  FF(a, b, c, d, x[ 4], S11, 0xf57c0faf); /* 5 */
  FF(d, a, b, c, x[ 5], S12, 0x4787c62a); /* 6 */
  FF(c, d, a, b, x[ 6], S13, 0xa8304613); /* 7 */
  FF(b, c, d, a, x[ 7], S14, 0xfd469501); /* 8 */
  FF(a, b, c, d, x[ 8], S11, 0x698098d8); /* 9 */
  FF(d, a, b, c, x[ 9], S12, 0x8b44f7af); /* 10 */
  FF(c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */
  FF(b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */
  FF(a, b, c, d, x[12], S11, 0x6b901122); /* 13 */
  FF(d, a, b, c, x[13], S12, 0xfd987193); /* 14 */
  FF(c, d, a, b, x[14], S13, 0xa679438e); /* 15 */
  FF(b, c, d, a, x[15], S14, 0x49b40821); /* 16 */

                  /* Round 2 */
  GG(a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */
  GG(d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */
  GG(c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */
  GG(b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */
  GG(a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */
  GG(d, a, b, c, x[10], S22,  0x2441453); /* 22 */
  GG(c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */
  GG(b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */
  GG(a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */
  GG(d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */
  GG(c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */
  GG(b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */
  GG(a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */
  GG(d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */
  GG(c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */
  GG(b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */

  /* Round 3 */
  HH(a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */
  HH(d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */
  HH(c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */
  HH(b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */
  HH(a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */
  HH(d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */
  HH(c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */
  HH(b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */
  HH(a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */
  HH(d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */
  HH(c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */
  HH(b, c, d, a, x[ 6], S34,  0x4881d05); /* 44 */
  HH(a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */
  HH(d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */
  HH(c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */
  HH(b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */

  /* Round 4 */
  II(a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */
  II(d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */
  II(c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */
  II(b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */
  II(a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */
  II(d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */
  II(c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */
  II(b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */
  II(a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */
  II(d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */
  II(c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */
  II(b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */
  II(a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */
  II(d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */
  II(c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */
  II(b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */

  state[0] += a;
  state[1] += b;
  state[2] += c;
  state[3] += d;

  /* Zeroize sensitive information. */

  R_memset((POINTER)x, 0, sizeof(x));
}

/* Encodes input (UINT4) into output (unsigned char). Assumes len is
	 a multiple of 4. */

static void Encode(unsigned char *output, UINT4 *input, unsigned int len)
{
  unsigned int i, j;

  for(i = 0, j = 0; j < len; i++, j += 4)
  {
    output[j] = (unsigned char)(input[i] & 0xff);
    output[j+1] = (unsigned char)((input[i] >> 8) & 0xff);
    output[j+2] = (unsigned char)((input[i] >> 16) & 0xff);
    output[j+3] = (unsigned char)((input[i] >> 24) & 0xff);
  }
}

/* Decodes input (unsigned char) into output (UINT4). Assumes len is
	 a multiple of 4. */

static void Decode(UINT4 *output, unsigned char *input, unsigned int len)
{
  unsigned int i, j;

  for(i = 0, j = 0; j < len; i++, j += 4)
    output[i] = ((UINT4)input[j]) | (((UINT4)input[j+1]) << 8) |
                (((UINT4)input[j+2]) << 16) | (((UINT4)input[j+3]) << 24);
}
//---------------------------------------------------------------------------
// NN.C - natural numbers routines
//---------------------------------------------------------------------------
/* internal static functions */
static NN_DIGIT subdigitmult(NN_DIGIT *, NN_DIGIT *, NN_DIGIT, NN_DIGIT *, unsigned int);
static void dmult(NN_DIGIT, NN_DIGIT, NN_DIGIT *, NN_DIGIT *);
static unsigned int NN_DigitBits(NN_DIGIT);

/* Decodes character string b into a, where character string is ordered
	 from most to least significant.

	 Lengths: a[digits], b[len].
	 Assumes b[i] = 0 for i < len - digits * NN_DIGIT_LEN. (Otherwise most
	 significant bytes are truncated.)
 */
void NN_Decode (NN_DIGIT *a, unsigned int digits, unsigned char *b, unsigned int len)
{
  NN_DIGIT t;
  unsigned int i, u;
  int j;

            /* @##$ unsigned/signed bug fix added JSAK - Fri  31/05/96 18:09:11 */
  for (i = 0, j = len - 1; i < digits && j >= 0; i++) {
    t = 0;
    for (u = 0; j >= 0 && u < NN_DIGIT_BITS; j--, u += 8)
			t |= ((NN_DIGIT)b[j]) << u;
		a[i] = t;
  }
  
  for (; i < digits; i++)
    a[i] = 0;
}

/* Encodes b into character string a, where character string is ordered
   from most to least significant.

	 Lengths: a[len], b[digits].
	 Assumes NN_Bits (b, digits) <= 8 * len. (Otherwise most significant
	 digits are truncated.)
 */
void NN_Encode (unsigned char *a, unsigned int len, NN_DIGIT *b, unsigned int digits)
{
	NN_DIGIT t;
    unsigned int i, u;
    int j;

            /* @##$ unsigned/signed bug fix added JSAK - Fri  31/05/96 18:09:11 */
    for (i = 0, j = len - 1; i < digits && j >= 0; i++) {
		t = b[i];
        for (u = 0; j >= 0 && u < NN_DIGIT_BITS; j--, u += 8)
			a[j] = (unsigned char)(t >> u);
	}

    for (; j >= 0; j--)
		a[j] = 0;
}

/* Assigns a = 0. */

void NN_AssignZero (NN_DIGIT *a, unsigned int digits)
{
	if(digits) {
		do {
			*a++ = 0;
		}while(--digits);
	}
}

/* Assigns a = 2^b.

   Lengths: a[digits].
	 Requires b < digits * NN_DIGIT_BITS.
 */
void NN_Assign2Exp (NN_DIGIT *a, unsigned int b, unsigned int digits)
{
  NN_AssignZero (a, digits);

	if (b >= digits * NN_DIGIT_BITS)
    return;

  a[b / NN_DIGIT_BITS] = (NN_DIGIT)1 << (b % NN_DIGIT_BITS);
}

/* Computes a = b - c. Returns borrow.

	 Lengths: a[digits], b[digits], c[digits].
 */
NN_DIGIT NN_Sub (NN_DIGIT *a, NN_DIGIT *b, NN_DIGIT *c, unsigned int digits)
{
	NN_DIGIT temp, borrow = 0;

	if(digits)
		do {
            /* Bug fix 16/10/95 - JSK, code below removed, caused bug with
               Sun Compiler SC4.

			if((temp = (*b++) - borrow) == MAX_NN_DIGIT)
                temp = MAX_NN_DIGIT - *c++;
            */

            temp = *b - borrow;
            b++;
            if(temp == MAX_NN_DIGIT) {
                temp = MAX_NN_DIGIT - *c;
                c++;
            }else {      /* Patch to prevent bug for Sun CC */
                if((temp -= *c) > (MAX_NN_DIGIT - *c))
					borrow = 1;
				else
					borrow = 0;
                c++;
            }
			*a++ = temp;
		}while(--digits);

	return(borrow);
}

/* Computes a = b * c.

	 Lengths: a[2*digits], b[digits], c[digits].
	 Assumes digits < MAX_NN_DIGITS.
*/

void NN_Mult (NN_DIGIT *a, NN_DIGIT *b, NN_DIGIT *c, unsigned int digits)
{
	NN_DIGIT t[2*MAX_NN_DIGITS];
	NN_DIGIT dhigh, dlow, carry;
	unsigned int bDigits, cDigits, i, j;

	NN_AssignZero (t, 2 * digits);

	bDigits = NN_Digits (b, digits);
	cDigits = NN_Digits (c, digits);

	for (i = 0; i < bDigits; i++) {
		carry = 0;
		if(*(b+i) != 0) {
			for(j = 0; j < cDigits; j++) {
				dmult(*(b+i), *(c+j), &dhigh, &dlow);
				if((*(t+(i+j)) = *(t+(i+j)) + carry) < carry)
					carry = 1;
				else
					carry = 0;
				if((*(t+(i+j)) += dlow) < dlow)
					carry++;
				carry += dhigh;
			}
		}
		*(t+(i+cDigits)) += carry;
	}


	NN_Assign(a, t, 2 * digits);
}

/* Computes a = b * 2^c (i.e., shifts left c bits), returning carry.

	 Requires c < NN_DIGIT_BITS. */

NN_DIGIT NN_LShift (NN_DIGIT *a, NN_DIGIT *b, unsigned int c, unsigned int digits)
{
	NN_DIGIT temp, carry = 0;
	unsigned int t;

	if(c < NN_DIGIT_BITS)
		if(digits) {

			t = NN_DIGIT_BITS - c;

			do {
				temp = *b++;
				*a++ = (temp << c) | carry;
				carry = c ? (temp >> t) : 0;
			}while(--digits);
		}

	return (carry);
}

/* Computes a = c div 2^c (i.e., shifts right c bits), returning carry.

	 Requires: c < NN_DIGIT_BITS. */

NN_DIGIT NN_RShift (NN_DIGIT *a, NN_DIGIT *b, unsigned int c, unsigned int digits)
{
	NN_DIGIT temp, carry = 0;
	unsigned int t;

	if(c < NN_DIGIT_BITS)
		if(digits) {

			t = NN_DIGIT_BITS - c;

			do {
				digits--;
				temp = *(b+digits);
				*(a+digits) = (temp >> c) | carry;
				carry = c ? (temp << t) : 0;
			}while(digits);
		}

	return (carry);
}

/* Computes a = c div d and b = c mod d.

	 Lengths: a[cDigits], b[dDigits], c[cDigits], d[dDigits].
	 Assumes d > 0, cDigits < 2 * MAX_NN_DIGITS,
					 dDigits < MAX_NN_DIGITS.
*/

void NN_Div (NN_DIGIT *a, NN_DIGIT *b, NN_DIGIT *c, unsigned int cDigits, NN_DIGIT *d, unsigned int dDigits)
{
	NN_DIGIT ai, cc[2*MAX_NN_DIGITS+1], dd[MAX_NN_DIGITS], s;
	NN_DIGIT t[2], u, v, *ccptr;
	NN_HALF_DIGIT aHigh, aLow, cHigh, cLow;
	int i;
	unsigned int ddDigits, shift;

	ddDigits = NN_Digits (d, dDigits);
	if(ddDigits == 0)
		return;

	shift = NN_DIGIT_BITS - NN_DigitBits (d[ddDigits-1]);
	NN_AssignZero (cc, ddDigits);
	cc[cDigits] = NN_LShift (cc, c, shift, cDigits);
	NN_LShift (dd, d, shift, ddDigits);
	s = dd[ddDigits-1];

	NN_AssignZero (a, cDigits);

	for (i = cDigits-ddDigits; i >= 0; i--) {
		if (s == MAX_NN_DIGIT)
			ai = cc[i+ddDigits];
		else {
			ccptr = &cc[i+ddDigits-1];

			s++;
			cHigh = (NN_HALF_DIGIT)HIGH_HALF (s);
			cLow = (NN_HALF_DIGIT)LOW_HALF (s);

			*t = *ccptr;
			*(t+1) = *(ccptr+1);

			if (cHigh == MAX_NN_HALF_DIGIT)
				aHigh = (NN_HALF_DIGIT)HIGH_HALF (*(t+1));
			else
				aHigh = (NN_HALF_DIGIT)(*(t+1) / (cHigh + 1));
			u = (NN_DIGIT)aHigh * (NN_DIGIT)cLow;
			v = (NN_DIGIT)aHigh * (NN_DIGIT)cHigh;
			if ((*t -= TO_HIGH_HALF (u)) > (MAX_NN_DIGIT - TO_HIGH_HALF (u)))
				t[1]--;
			*(t+1) -= HIGH_HALF (u);
			*(t+1) -= v;

			while ((*(t+1) > (NN_DIGIT)cHigh) ||
						 ((*(t+1) == (NN_DIGIT)cHigh) && (*t >= TO_HIGH_HALF (cLow)))) {
				if ((*t -= TO_HIGH_HALF (cLow)) > MAX_NN_DIGIT - TO_HIGH_HALF (cLow))
					t[1]--;
				*(t+1) -= cHigh;
				aHigh++;
			}

			if (cHigh == MAX_NN_HALF_DIGIT)
				aLow = (NN_HALF_DIGIT)LOW_HALF (*(t+1));
			else
				aLow =
			(NN_HALF_DIGIT)((TO_HIGH_HALF (*(t+1)) + HIGH_HALF (*t)) / (cHigh + 1));
			u = (NN_DIGIT)aLow * (NN_DIGIT)cLow;
			v = (NN_DIGIT)aLow * (NN_DIGIT)cHigh;
			if ((*t -= u) > (MAX_NN_DIGIT - u))
				t[1]--;
			if ((*t -= TO_HIGH_HALF (v)) > (MAX_NN_DIGIT - TO_HIGH_HALF (v)))
				t[1]--;
			*(t+1) -= HIGH_HALF (v);

			while ((*(t+1) > 0) || ((*(t+1) == 0) && *t >= s)) {
				if ((*t -= s) > (MAX_NN_DIGIT - s))
					t[1]--;
				aLow++;
			}

			ai = TO_HIGH_HALF (aHigh) + aLow;
			s--;
		}

		cc[i+ddDigits] -= subdigitmult(&cc[i], &cc[i], ai, dd, ddDigits);

		while (cc[i+ddDigits] || (NN_Cmp (&cc[i], dd, ddDigits) >= 0)) {
			ai++;
			cc[i+ddDigits] -= NN_Sub (&cc[i], &cc[i], dd, ddDigits);
		}

		a[i] = ai;
	}

	NN_AssignZero (b, dDigits);
	NN_RShift (b, cc, shift, ddDigits);
}


/* Computes a = b mod c.

	 Lengths: a[cDigits], b[bDigits], c[cDigits].
	 Assumes c > 0, bDigits < 2 * MAX_NN_DIGITS, cDigits < MAX_NN_DIGITS.
*/
void NN_Mod (NN_DIGIT *a, NN_DIGIT *b, unsigned int bDigits, NN_DIGIT *c, unsigned int cDigits)
{
    NN_DIGIT t[2 * MAX_NN_DIGITS];
  
	NN_Div (t, a, b, bDigits, c, cDigits);
}

/* Computes a = b * c mod d.

   Lengths: a[digits], b[digits], c[digits], d[digits].
   Assumes d > 0, digits < MAX_NN_DIGITS.
 */
void NN_ModMult (NN_DIGIT *a, NN_DIGIT *b, NN_DIGIT *c, NN_DIGIT *d, unsigned int digits)
{
    NN_DIGIT t[2*MAX_NN_DIGITS];

	NN_Mult (t, b, c, digits);
    NN_Mod (a, t, 2 * digits, d, digits);
}

/* Computes a = b^c mod d.

   Lengths: a[dDigits], b[dDigits], c[cDigits], d[dDigits].
	 Assumes d > 0, cDigits > 0, dDigits < MAX_NN_DIGITS.
 */
void NN_ModExp (NN_DIGIT *a, NN_DIGIT *b, NN_DIGIT *c, unsigned int cDigits, NN_DIGIT *d, unsigned int dDigits)
{
    NN_DIGIT bPower[3][MAX_NN_DIGITS], ci, t[MAX_NN_DIGITS];
    int i;
	unsigned int ciBits, j, s;

	/* Store b, b^2 mod d, and b^3 mod d.
	 */
	NN_Assign (bPower[0], b, dDigits);
	NN_ModMult (bPower[1], bPower[0], b, d, dDigits);
    NN_ModMult (bPower[2], bPower[1], b, d, dDigits);
  
    NN_ASSIGN_DIGIT (t, 1, dDigits);

	cDigits = NN_Digits (c, cDigits);
    for (i = cDigits - 1; i >= 0; i--) {
		ci = c[i];
		ciBits = NN_DIGIT_BITS;

		/* Scan past leading zero bits of most significant digit.
		 */
		if (i == (int)(cDigits - 1)) {
			while (! DIGIT_2MSB (ci)) {
				ci <<= 2;
				ciBits -= 2;
			}
        }

        for (j = 0; j < ciBits; j += 2, ci <<= 2) {
        /* Compute t = t^4 * b^s mod d, where s = two MSB's of ci. */
            NN_ModMult (t, t, t, d, dDigits);
            NN_ModMult (t, t, t, d, dDigits);
            if ((s = DIGIT_2MSB (ci)) != 0)
            NN_ModMult (t, t, bPower[s-1], d, dDigits);
        }
    }
  
	NN_Assign (a, t, dDigits);
}

/* Compute a = 1/b mod c, assuming inverse exists.
   
   Lengths: a[digits], b[digits], c[digits].
	 Assumes gcd (b, c) = 1, digits < MAX_NN_DIGITS.
 */
void NN_ModInv (NN_DIGIT *a, NN_DIGIT *b, NN_DIGIT *c, unsigned int digits)
{
    NN_DIGIT q[MAX_NN_DIGITS], t1[MAX_NN_DIGITS], t3[MAX_NN_DIGITS],
		u1[MAX_NN_DIGITS], u3[MAX_NN_DIGITS], v1[MAX_NN_DIGITS],
		v3[MAX_NN_DIGITS], w[2*MAX_NN_DIGITS];
    int u1Sign;

    /* Apply extended Euclidean algorithm, modified to avoid negative
       numbers.
    */
    NN_ASSIGN_DIGIT (u1, 1, digits);
	NN_AssignZero (v1, digits);
    NN_Assign (u3, b, digits);
	NN_Assign (v3, c, digits);
    u1Sign = 1;

	while (! NN_Zero (v3, digits)) {
        NN_Div (q, t3, u3, digits, v3, digits);
        NN_Mult (w, q, v1, digits);
		NN_Add (t1, u1, w, digits);
        NN_Assign (u1, v1, digits);
		NN_Assign (v1, t1, digits);
		NN_Assign (u3, v3, digits);
		NN_Assign (v3, t3, digits);
		u1Sign = -u1Sign;
	}

    /* Negate result if sign is negative. */
	if (u1Sign < 0)
		NN_Sub (a, c, u1, digits);
	else
		NN_Assign (a, u1, digits);
}

/* Computes a = gcd(b, c).

	 Assumes b > c, digits < MAX_NN_DIGITS.
*/

#define iplus1  ( i==2 ? 0 : i+1 )      /* used by Euclid algorithms */
#define iminus1 ( i==0 ? 2 : i-1 )      /* used by Euclid algorithms */
#define g(i) (  &(t[i][0])  )

void NN_Gcd(NN_DIGIT *a, NN_DIGIT *b, NN_DIGIT *c, unsigned int digits)
{
	short i;
	NN_DIGIT t[3][MAX_NN_DIGITS];

	NN_Assign(g(0), c, digits);
	NN_Assign(g(1), b, digits);

	i=1;

	while(!NN_Zero(g(i),digits)) {
		NN_Mod(g(iplus1), g(iminus1), digits, g(i), digits);
		i = iplus1;
	}

	NN_Assign(a , g(iminus1), digits);
}

/* Returns the significant length of a in bits.

	 Lengths: a[digits]. */

unsigned int NN_Bits (NN_DIGIT *a, unsigned int digits)
{
	if ((digits = NN_Digits (a, digits)) == 0)
		return (0);

	return ((digits - 1) * NN_DIGIT_BITS + NN_DigitBits (a[digits-1]));
}

/* Returns sign of a - b. */

int NN_Cmp (NN_DIGIT *a, NN_DIGIT *b, unsigned int digits)
{

	if(digits) {
		do {
			digits--;
			if(*(a+digits) > *(b+digits))
				return(1);
			if(*(a+digits) < *(b+digits))
				return(-1);
		}while(digits);
	}

	return (0);
}

/* Returns nonzero iff a is zero. */

int NN_Zero (NN_DIGIT *a, unsigned int digits)
{
	if(digits) {
		do {
			if(*a++)
				return(0);
		}while(--digits);
	}

	return (1);
}

/* Assigns a = b. */

void NN_Assign (NN_DIGIT *a, NN_DIGIT *b, unsigned int digits)
{
	if(digits) {
		do {
			*a++ = *b++;
		}while(--digits);
	}
}

/* Returns the significant length of a in digits. */

unsigned int NN_Digits (NN_DIGIT *a, unsigned int digits)
{

	if(digits) {
		digits--;

		do {
			if(*(a+digits))
				break;
		}while(digits--);

		return(digits + 1);
	}

	return(digits);
}

/* Computes a = b + c. Returns carry.

	 Lengths: a[digits], b[digits], c[digits].
 */
NN_DIGIT NN_Add (NN_DIGIT *a, NN_DIGIT *b, NN_DIGIT *c, unsigned int digits)
{
	NN_DIGIT temp, carry = 0;

	if(digits)
		do {
			if((temp = (*b++) + carry) < carry)
				temp = *c++;
            else {      /* Patch to prevent bug for Sun CC */
                if((temp += *c) < *c)
					carry = 1;
				else
					carry = 0;
                c++;
            }
			*a++ = temp;
		}while(--digits);

	return (carry);
}

static NN_DIGIT subdigitmult(NN_DIGIT *a, NN_DIGIT *b, NN_DIGIT c, NN_DIGIT *d, unsigned int digits)
{
	NN_DIGIT borrow, thigh, tlow;
	unsigned int i;

	borrow = 0;

	if(c != 0) {
		for(i = 0; i < digits; i++) {
			dmult(c, d[i], &thigh, &tlow);
			if((a[i] = b[i] - borrow) > (MAX_NN_DIGIT - borrow))
				borrow = 1;
			else
				borrow = 0;
			if((a[i] -= tlow) > (MAX_NN_DIGIT - tlow))
				borrow++;
			borrow += thigh;
		}
	}

	return (borrow);
}

/* Returns the significant length of a in bits, where a is a digit. */

static unsigned int NN_DigitBits (NN_DIGIT a)
{
	unsigned int i;

	for (i = 0; i < NN_DIGIT_BITS; i++, a >>= 1)
		if (a == 0)
			break;

	return (i);
}

/* Computes a * b, result stored in high and low. */

static void dmult(NN_DIGIT a, NN_DIGIT b, NN_DIGIT *high, NN_DIGIT *low)
{
	NN_HALF_DIGIT al, ah, bl, bh;
	NN_DIGIT m1, m2, m, ml, mh, carry = 0;

	al = (NN_HALF_DIGIT)LOW_HALF(a);
	ah = (NN_HALF_DIGIT)HIGH_HALF(a);
	bl = (NN_HALF_DIGIT)LOW_HALF(b);
	bh = (NN_HALF_DIGIT)HIGH_HALF(b);

	*low = (NN_DIGIT) al*bl;
	*high = (NN_DIGIT) ah*bh;

	m1 = (NN_DIGIT) al*bh;
	m2 = (NN_DIGIT) ah*bl;
	m = m1 + m2;

	if(m < m1)
        carry = 1L << (NN_DIGIT_BITS / 2);

	ml = (m & MAX_NN_HALF_DIGIT) << (NN_DIGIT_BITS / 2);
	mh = m >> (NN_DIGIT_BITS / 2);

	*low += ml;

	if(*low < ml)
		carry++;

	*high += carry + mh;
}
//---------------------------------------------------------------------------
// R_RANDOM.C - random objects for RSAEURO
//---------------------------------------------------------------------------
#define RANDOM_BYTES_RQ 256
/* We use more seed data for an internally created object */
#define RANDOM_BYTES_RQINT 512

#define MIX_CNT 16

static UINT4 subrand(long);

/* Set up, random object ready for seeding. */

int R_RandomInit(R_RANDOM_STRUCT *random)
{
	/* clear and setup object for seeding */
	R_memset((POINTER)random->state, 0, sizeof(random->state));
	random->outputAvailable = 0;
	random->bytesNeeded = RANDOM_BYTES_RQ;

	return(RSA_ID_OK);
}

int R_RandomUpdate(R_RANDOM_STRUCT *random, unsigned char *block, unsigned int len)
{
	C_MD5_CTX context;
	BYTE digest[16];
    unsigned short int i, j;

	c_MD5Init(&context);
	c_MD5Update(&context, block, len);
	c_MD5Final(digest, &context);

	/* add digest to state */

	for(j = 0, i = 16; i > 0; i--) {
		j += random->state[i-1] + digest[i-1];
		random->state[i-1] = (BYTE)j;
		j >>= 8;
	}

	if(random->bytesNeeded < len)
		random->bytesNeeded = 0;
	else
		random->bytesNeeded -= len;

	/* Clear sensitive information. */

	R_memset((POINTER)digest, 0, sizeof (digest));
	j = 0;

	return(RSA_ID_OK);
}

/* Get the number of seed byte still required by the object */

int R_GetRandomBytesNeeded(unsigned int *bytesNeeded, R_RANDOM_STRUCT *random)
{
  *bytesNeeded = random->bytesNeeded;

  return(RSA_ID_OK);
}

int R_GenerateBytes(unsigned char *block, unsigned int len, R_RANDOM_STRUCT *random)
{
	C_MD5_CTX context;
	unsigned int avail, i;

	if(random->bytesNeeded)
		return(RE_NEED_RANDOM);

	avail = random->outputAvailable;

	while(avail < len) {
		R_memcpy((POINTER)block, (POINTER)&random->output[16-avail], avail);
		len -= avail;
		block += avail;

		/* generate new output */

		c_MD5Init(&context);
		c_MD5Update(&context, random->state, 16);
		c_MD5Final(random->output, &context);
		avail = 16;

		/* increment state */
		for(i = 16; i > 0; i--)
			if(random->state[i-1]++)
				break;
	}

	R_memcpy((POINTER)block, (POINTER)&random->output[16-avail], len);
	random->outputAvailable = avail - len;

	return(RSA_ID_OK);
}

/* Clear Random object when finished. */

void R_RandomFinal(R_RANDOM_STRUCT *random)
{
  R_memset((POINTER)random, 0, sizeof(R_RANDOM_STRUCT));
}

/*  Create Random object, seed ready for use.
    Requires ANSI Standard time routines to provide seed data.
*/

void R_RandomCreate(R_RANDOM_STRUCT *random)
{
  clock_t cnow;
  time_t t;
  struct tm *gmt;
  UINT4 temp;

  /* clear and setup object for seeding */
  R_memset((POINTER)random->state, 0, sizeof(random->state));
  random->outputAvailable = 0;
  random->bytesNeeded = RANDOM_BYTES_RQINT;  /* using internal value */

  /* Add data to random object */
  while(random->bytesNeeded) {
    t = time(NULL);                 /* use for seed data */
    gmt = gmtime(&t);
    cnow = clock();
    temp = subrand(t);              /* use special routine to produce seed */

    R_RandomUpdate(random, (POINTER)&temp, sizeof(UINT4));
    R_RandomUpdate(random, (POINTER)gmt, sizeof(struct tm));
    R_RandomUpdate(random, (POINTER)&cnow, sizeof(clock_t));
  }

  /* Clean Up time related data */
  R_memset((POINTER)gmt, 0, sizeof(struct tm));
  cnow = 0;
  t = 0;
  temp = 0;
}

/*  Mix up state of the current random structure.
    Again requires both clock functions this just adds something
    extra to the state, then refreshes the output.
*/

void R_RandomMix(R_RANDOM_STRUCT *random)
{
	unsigned int i;
	C_MD5_CTX context;

    for(i = 0; i < MIX_CNT; i++) {
        random->state[i] ^= (unsigned char) clock();
        random->state[15-i] ^= (unsigned char) time(NULL);
	}

	/* Clear any old state with new data */

	c_MD5Init(&context);
	c_MD5Update(&context, random->state, 16);
	c_MD5Final(random->output, &context);

	/* tell R_GenerateBytes there is new output */

	random->outputAvailable = 16;

}

/*
    This routine is based on an idea outlined in the book "Numerical Recipes
    in C" using a form of reduced DES like function.
*/

#define NITER 4

static UINT4 subrand(long idum)
{

    UINT4 irword, lword;
    static long idums = 0.0;
    UINT4 i, ia, ib, iswap, itmph=0, itmpl=0;

    static UINT4 c1[NITER] = { 0xbaa96887L, 0x1e17d32cL, 0x03dcbc3cL, 0xf033d1b2L };
    static UINT4 c2[NITER] = { 0x4bf03b58L, 0xe8740fc3L, 0x69aac5a6L, 0x55a7ca46L };

    if (idum < 0) {
        idums = -(idum);
        idum = 1;
    }

    irword = idum;
    lword = idums;

    for(i=0; i < NITER; i++) {
        ia=(iswap=irword) ^ c1[i];
        itmpl = ia & 0xffff;
        itmph = ia >> 16;
        ib = itmpl*itmpl+~(itmph*itmph);
        irword=lword ^ (((ia = (ib >> 16) | ((ib & 0xffff) << 16)) ^ c2[i])+itmpl*itmph);
        lword=iswap;
    }
    return irword;
}
//---------------------------------------------------------------------------
// PRIME.C - primality-testing routines
//---------------------------------------------------------------------------
#define SMALL_PRIME_COUNT 1027

static int probableprime(NN_DIGIT *, unsigned int);

/* Generates a probable prime a between b and c such that a-1 is
   divisible by d.

   Assumes b < c, digits < MAX_NN_DIGITS.
   Returns RE_NEED_RANDOM if randomStruct not seeded, RE_DATA if
   unsuccessful.
*/

int GeneratePrime(NN_DIGIT *a, NN_DIGIT *b, NN_DIGIT *c, NN_DIGIT *d, unsigned int digits, R_RANDOM_STRUCT *randomStruct)
{
    int status;
    unsigned char block[MAX_NN_DIGITS * NN_DIGIT_LEN];
    NN_DIGIT t[MAX_NN_DIGITS], u[MAX_NN_DIGITS];

    /* Generate random number between b and c. */

    status = R_GenerateBytes(block, digits * NN_DIGIT_LEN, randomStruct);
    if(status)
        return(status);

    NN_Decode(a, digits, block, digits * NN_DIGIT_LEN);
    NN_Sub(t, c, b, digits);
    NN_ASSIGN_DIGIT(u, 1, digits);
    NN_Add(t, t, u, digits);
    NN_Mod(a, a, digits, t, digits);
    NN_Add(a, a, b, digits);

    /* Adjust so that a-1 is divisible by d. */

    NN_Mod(t, a, digits, d, digits);
    NN_Sub(a, a, t, digits);
    NN_Add(a, a, u, digits);
    if(NN_Cmp(a, b, digits) < 0)
        NN_Add(a, a, d, digits);
    if(NN_Cmp(a, c, digits) > 0)
        NN_Sub(a, a, d, digits);

    /* Search to c in steps of d. */

    NN_Assign(t, c, digits);
    NN_Sub(t, t, d, digits);

    while(!probableprime (a, digits)) {
        if(NN_Cmp (a, t, digits) > 0)
            return(RE_DATA);
        NN_Add(a, a, d, digits);
    }

    return(RSA_ID_OK);
}

/* Returns nonzero iff a is a probable prime.

   Does small factor test and a fermat test witness 2.
*/

static int probableprime(NN_DIGIT *a, unsigned int aDigits)
{

    int status;
    NN_DIGIT t[MAX_NN_DIGITS], u[MAX_NN_DIGITS];
        /* This table can be reduced in size but the smaller
             the table the slower the testing.
        */
    static unsigned int SMALL_PRIMES[] = {
        3, 5, 7, 11, 13, 17, 19,
        23, 29, 31, 37, 41, 43, 47, 53,
        59, 61, 67, 71, 73, 79, 83, 89,
        97, 101, 103, 107, 109, 113, 127, 131,
        137, 139, 149, 151, 157, 163, 167, 173,
        179, 181, 191, 193, 197, 199, 211, 223,
        227, 229, 233, 239, 241, 251, 257, 263,
		269, 271, 277, 281, 283, 293, 307, 311,
        313, 317, 331, 337, 347, 349, 353, 359,
        367, 373, 379, 383, 389, 397, 401, 409,
        419, 421, 431, 433, 439, 443, 449, 457,
        461, 463, 467, 479, 487, 491, 499, 503,
        509, 521, 523, 541, 547, 557, 563, 569,
        571, 577, 587, 593, 599, 601, 607, 613,
        617, 619, 631, 641, 643, 647, 653, 659,
        661, 673, 677, 683, 691, 701, 709, 719,
        727, 733, 739, 743, 751, 757, 761, 769,
        773, 787, 797, 809, 811, 821, 823, 827,
        829, 839, 853, 857, 859, 863, 877, 881,
        883, 887, 907, 911, 919, 929, 937, 941,
        947, 953, 967, 971, 977, 983, 991, 997,
        1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049,
        1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097,
        1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163,
        1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223,
        1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283,
        1289, 1291, 1297, 1301, 1303, 1307, 1319, 1321,
        1327, 1361, 1367, 1373, 1381, 1399, 1409, 1423,
        1427, 1429, 1433, 1439, 1447, 1451, 1453, 1459,
        1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511,
        1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571,
        1579, 1583, 1597, 1601, 1607, 1609, 1613, 1619,
        1621, 1627, 1637, 1657, 1663, 1667, 1669, 1693,
        1697, 1699, 1709, 1721, 1723, 1733, 1741, 1747,
        1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811,
        1823, 1831, 1847, 1861, 1867, 1871, 1873, 1877,
        1879, 1889, 1901, 1907, 1913, 1931, 1933, 1949,
        1951, 1973, 1979, 1987, 1993, 1997, 1999, 2003,
        2011, 2017, 2027, 2029, 2039, 2053, 2063, 2069,
        2081, 2083, 2087, 2089, 2099, 2111, 2113, 2129,
        2131, 2137, 2141, 2143, 2153, 2161, 2179, 2203,
        2207, 2213, 2221, 2237, 2239, 2243, 2251, 2267,
        2269, 2273, 2281, 2287, 2293, 2297, 2309, 2311,
        2333, 2339, 2341, 2347, 2351, 2357, 2371, 2377,
        2381, 2383, 2389, 2393, 2399, 2411, 2417, 2423,
        2437, 2441, 2447, 2459, 2467, 2473, 2477, 2503,
        2521, 2531, 2539, 2543, 2549, 2551, 2557, 2579,
        2591, 2593, 2609, 2617, 2621, 2633, 2647, 2657,
        2659, 2663, 2671, 2677, 2683, 2687, 2689, 2693,
        2699, 2707, 2711, 2713, 2719, 2729, 2731, 2741,
        2749, 2753, 2767, 2777, 2789, 2791, 2797, 2801,
        2803, 2819, 2833, 2837, 2843, 2851, 2857, 2861,
        2879, 2887, 2897, 2903, 2909, 2917, 2927, 2939,
        2953, 2957, 2963, 2969, 2971, 2999, 3001, 3011,
        3019, 3023, 3037, 3041, 3049, 3061, 3067, 3079,
        3083, 3089, 3109, 3119, 3121, 3137, 3163, 3167,
        3169, 3181, 3187, 3191, 3203, 3209, 3217, 3221,
        3229, 3251, 3253, 3257, 3259, 3271, 3299, 3301,
        3307, 3313, 3319, 3323, 3329, 3331, 3343, 3347,
        3359, 3361, 3371, 3373, 3389, 3391, 3407, 3413,
        3433, 3449, 3457, 3461, 3463, 3467, 3469, 3491,
        3499, 3511, 3517, 3527, 3529, 3533, 3539, 3541,
        3547, 3557, 3559, 3571, 3581, 3583, 3593, 3607,
        3613, 3617, 3623, 3631, 3637, 3643, 3659, 3671,
        3673, 3677, 3691, 3697, 3701, 3709, 3719, 3727,
        3733, 3739, 3761, 3767, 3769, 3779, 3793, 3797,
        3803, 3821, 3823, 3833, 3847, 3851, 3853, 3863,
        3877, 3881, 3889, 3907, 3911, 3917, 3919, 3923,
        3929, 3931, 3943, 3947, 3967, 3989, 4001, 4003,
        4007, 4013, 4019, 4021, 4027, 4049, 4051, 4057,
        4073, 4079, 4091, 4093, 4099, 4111, 4127, 4129,
        4133, 4139, 4153, 4157, 4159, 4177, 4201, 4211,
        4217, 4219, 4229, 4231, 4241, 4243, 4253, 4259,
        4261, 4271, 4273, 4283, 4289, 4297, 4327, 4337,
        4339, 4349, 4357, 4363, 4373, 4391, 4397, 4409,
        4421, 4423, 4441, 4447, 4451, 4457, 4463, 4481,
        4483, 4493, 4507, 4513, 4517, 4519, 4523, 4547,
        4549, 4561, 4567, 4583, 4591, 4597, 4603, 4621,
        4637, 4639, 4643, 4649, 4651, 4657, 4663, 4673,
        4679, 4691, 4703, 4721, 4723, 4729, 4733, 4751,
        4759, 4783, 4787, 4789, 4793, 4799, 4801, 4813,
        4817, 4831, 4861, 4871, 4877, 4889, 4903, 4909,
        4919, 4931, 4933, 4937, 4943, 4951, 4957, 4967,
        4969, 4973, 4987, 4993, 4999, 5003, 5009, 5011,
        5021, 5023, 5039, 5051, 5059, 5077, 5081, 5087,
        5099, 5101, 5107, 5113, 5119, 5147, 5153, 5167,
        5171, 5179, 5189, 5197, 5209, 5227, 5231, 5233,
        5237, 5261, 5273, 5279, 5281, 5297, 5303, 5309,
        5323, 5333, 5347, 5351, 5381, 5387, 5393, 5399,
        5407, 5413, 5417, 5419, 5431, 5437, 5441, 5443,
        5449, 5471, 5477, 5479, 5483, 5501, 5503, 5507,
        5519, 5521, 5527, 5531, 5557, 5563, 5569, 5573,
        5581, 5591, 5623, 5639, 5641, 5647, 5651, 5653,
        5657, 5659, 5669, 5683, 5689, 5693, 5701, 5711,
        5717, 5737, 5741, 5743, 5749, 5779, 5783, 5791,
        5801, 5807, 5813, 5821, 5827, 5839, 5843, 5849,
        5851, 5857, 5861, 5867, 5869, 5879, 5881, 5897,
        5903, 5923, 5927, 5939, 5953, 5981, 5987, 6007,
        6011, 6029, 6037, 6043, 6047, 6053, 6067, 6073,
        6079, 6089, 6091, 6101, 6113, 6121, 6131, 6133,
        6143, 6151, 6163, 6173, 6197, 6199, 6203, 6211,
        6217, 6221, 6229, 6247, 6257, 6263, 6269, 6271,
        6277, 6287, 6299, 6301, 6311, 6317, 6323, 6329,
        6337, 6343, 6353, 6359, 6361, 6367, 6373, 6379,
        6389, 6397, 6421, 6427, 6449, 6451, 6469, 6473,
        6481, 6491, 6521, 6529, 6547, 6551, 6553, 6563,
        6569, 6571, 6577, 6581, 6599, 6607, 6619, 6637,
        6653, 6659, 6661, 6673, 6679, 6689, 6691, 6701,
        6703, 6709, 6719, 6733, 6737, 6761, 6763, 6779,
        6781, 6791, 6793, 6803, 6823, 6827, 6829, 6833,
        6841, 6857, 6863, 6869, 6871, 6883, 6899, 6907,
        6911, 6917, 6947, 6949, 6959, 6961, 6967, 6971,
        6977, 6983, 6991, 6997, 7001, 7013, 7019, 7027,
        7039, 7043, 7057, 7069, 7079, 7103, 7109, 7121,
        7127, 7129, 7151, 7159, 7177, 7187, 7193, 7207,
        7211, 7213, 7219, 7229, 7237, 7243, 7247, 7253,
        7283, 7297, 7307, 7309, 7321, 7331, 7333, 7349,
        7351, 7369, 7393, 7411, 7417, 7433, 7451, 7457,
        7459, 7477, 7481, 7487, 7489, 7499, 7507, 7517,
        7523, 7529, 7537, 7541, 7547, 7549, 7559, 7561,
        7573, 7577, 7583, 7589, 7591, 7603, 7607, 7621,
        7639, 7643, 7649, 7669, 7673, 7681, 7687, 7691,
        7699, 7703, 7717, 7723, 7727, 7741, 7753, 7757,
        7759, 7789, 7793, 7817, 7823, 7829, 7841, 7853,
        7867, 7873, 7877, 7879, 7883, 7901, 7907, 7919,
        7927, 7933, 7937, 7949, 7951, 7963, 7993, 8009,
        8011, 8017, 8039, 8053, 8059, 8069, 8081, 8087,
        8089, 8093, 8101, 8111, 8117, 8123, 8147, 8161,
        8167, 8171, 8179, 8191, 0
    };

    unsigned int i;

    status = 1;

    NN_AssignZero(t, aDigits);

    /* Small Primes test, weed out junk numbers before slower Fermat's */

    for(i = 0; *(SMALL_PRIMES+i); i++) {
        *t = *(SMALL_PRIMES+i);
        if(aDigits == 1)
            if(NN_Cmp (a, t, 1) == 0)
                break;
        NN_Mod(t, a, aDigits, t, 1);
        if(NN_Zero (t, 1)) {
            status = 0;
            break;
        }
    }

    /* Clear sensitive information. */

    i = 0;
    R_memset((POINTER)t, 0, sizeof(t));

        /* Fermat's test for witness 2.
             (All primes pass the test, and nearly all composites fail.)
        */

    if(status) {
        NN_ASSIGN_DIGIT(t, 2, aDigits);
        NN_ModExp(u, t, a, aDigits, a, aDigits);

        status = NN_EQUAL(t, u, aDigits);

    /* Clear sensitive information. */

    R_memset((POINTER)u, 0, sizeof(u));
    }

    return(status ? TRUE : FALSE);
}
//---------------------------------------------------------------------------
// R_KEYGEN.C - key-pair generation
//---------------------------------------------------------------------------
static int RSAFilter(NN_DIGIT *, unsigned int, NN_DIGIT *, unsigned int);

/* Generates an RSA key pair with a given length and public exponent. */

int R_GeneratePEMKeys(R_RSA_PUBLIC_KEY *publicKey, R_RSA_PRIVATE_KEY *privateKey, R_RSA_PROTO_KEY *protoKey, R_RANDOM_STRUCT *randomStruct)
{
	NN_DIGIT d[MAX_NN_DIGITS], dP[MAX_NN_DIGITS], dQ[MAX_NN_DIGITS],
		e[MAX_NN_DIGITS], n[MAX_NN_DIGITS], p[MAX_NN_DIGITS], phiN[MAX_NN_DIGITS],
		pMinus1[MAX_NN_DIGITS], q[MAX_NN_DIGITS], qInv[MAX_NN_DIGITS],
		qMinus1[MAX_NN_DIGITS], t[MAX_NN_DIGITS], u[MAX_NN_DIGITS],
		v[MAX_NN_DIGITS];
	int status;
	unsigned int nDigits, pBits, pDigits, qBits;

	if((protoKey->bits < MIN_RSA_MODULUS_BITS) || (protoKey->bits > MAX_RSA_MODULUS_BITS))
		return(RE_MODULUS_LEN);

	nDigits = (protoKey->bits + NN_DIGIT_BITS - 1) / NN_DIGIT_BITS;
	pDigits = (nDigits + 1) / 2;
	pBits = (protoKey->bits + 1) / 2;
	qBits = protoKey->bits - pBits;

	/* NB: for 65537, this means that NN_DIGIT is at least 17 bits
		 in length. */

	NN_ASSIGN_DIGIT(e, protoKey->useFermat4 ? (NN_DIGIT)65537 : (NN_DIGIT)3, nDigits);

	/* Generate prime p between 3*2^(pBits-2) and 2^pBits-1, searching
		 in steps of 2, until one satisfies gcd (p-1, e) = 1. */

	NN_Assign2Exp(t, pBits-1, pDigits);
	NN_Assign2Exp(u, pBits-2, pDigits);
	NN_Add(t, t, u, pDigits);
	NN_ASSIGN_DIGIT(v, 1, pDigits);
	NN_Sub(v, t, v, pDigits);
	NN_Add(u, u, v, pDigits);
	NN_ASSIGN_DIGIT(v, 2, pDigits);

	do {
		if((status = GeneratePrime(p, t, u, v, pDigits, randomStruct)) != 0)
			return(status);
	}while(!RSAFilter(p, pDigits, e, 1));

	/* Generate prime q between 3*2^(qBits-2) and 2^qBits-1, searching
		 in steps of 2, until one satisfies gcd (q-1, e) = 1. */

	NN_Assign2Exp(t, qBits-1, pDigits);
	NN_Assign2Exp(u, qBits-2, pDigits);
	NN_Add(t, t, u, pDigits);
	NN_ASSIGN_DIGIT(v, 1, pDigits);
	NN_Sub(v, t, v, pDigits);
	NN_Add(u, u, v, pDigits);
	NN_ASSIGN_DIGIT(v, 2, pDigits);

	do {
		if((status = GeneratePrime(q, t, u, v, pDigits, randomStruct)) != 0)
			return(status);
	}while(!RSAFilter(q, pDigits, e, 1));

	/* Sort so that p > q. (p = q case is extremely unlikely. */

	if(NN_Cmp(p, q, pDigits) < 0) {
		NN_Assign(t, p, pDigits);
		NN_Assign(p, q, pDigits);
		NN_Assign(q, t, pDigits);
	}

	/* Compute n = pq, qInv = q^{-1} mod p, d = e^{-1} mod (p-1)(q-1),
		 dP = d mod p-1, dQ = d mod q-1. */

	NN_Mult(n, p, q, pDigits);
	NN_ModInv(qInv, q, p, pDigits);

	NN_ASSIGN_DIGIT(t, 1, pDigits);
	NN_Sub(pMinus1, p, t, pDigits);
	NN_Sub(qMinus1, q, t, pDigits);
	NN_Mult(phiN, pMinus1, qMinus1, pDigits);

	NN_ModInv(d, e, phiN, nDigits);
	NN_Mod(dP, d, nDigits, pMinus1, pDigits);
	NN_Mod(dQ, d, nDigits, qMinus1, pDigits);

	publicKey->bits = privateKey->bits = protoKey->bits;
	NN_Encode(publicKey->modulus, MAX_RSA_MODULUS_LEN, n, nDigits);
	NN_Encode(publicKey->exponent, MAX_RSA_MODULUS_LEN, e, 1);
	R_memcpy((POINTER)privateKey->modulus, (POINTER)publicKey->modulus, MAX_RSA_MODULUS_LEN);
	R_memcpy((POINTER)privateKey->publicExponent, (POINTER)publicKey->exponent, MAX_RSA_MODULUS_LEN);
	NN_Encode(privateKey->exponent, MAX_RSA_MODULUS_LEN, d, nDigits);
	NN_Encode(privateKey->prime[0], MAX_RSA_PRIME_LEN, p, pDigits);
	NN_Encode(privateKey->prime[1], MAX_RSA_PRIME_LEN, q, pDigits);
	NN_Encode(privateKey->primeExponent[0], MAX_RSA_PRIME_LEN, dP, pDigits);
	NN_Encode(privateKey->primeExponent[1], MAX_RSA_PRIME_LEN, dQ, pDigits);
	NN_Encode(privateKey->coefficient, MAX_RSA_PRIME_LEN, qInv, pDigits);

	/* Clear sensitive information. */

	R_memset((POINTER)d, 0, sizeof(d));
	R_memset((POINTER)dP, 0, sizeof(dP));
	R_memset((POINTER)dQ, 0, sizeof(dQ));
	R_memset((POINTER)p, 0, sizeof(p));
	R_memset((POINTER)phiN, 0, sizeof(phiN));
	R_memset((POINTER)pMinus1, 0, sizeof(pMinus1));
	R_memset((POINTER)q, 0, sizeof(q));
	R_memset((POINTER)qInv, 0, sizeof(qInv));
	R_memset((POINTER)qMinus1, 0, sizeof(qMinus1));
	R_memset((POINTER)t, 0, sizeof(t));

	return (0);
}

/* Returns nonzero iff GCD (a-1, b) = 1.
	 Assumes aDigits < MAX_NN_DIGITS, bDigits < MAX_NN_DIGITS. */

static int RSAFilter(NN_DIGIT *a, unsigned int aDigits, NN_DIGIT *b, unsigned int bDigits)
{
	int status = 0;
	NN_DIGIT aMinus1[MAX_NN_DIGITS], t[MAX_NN_DIGITS];
	NN_DIGIT u[MAX_NN_DIGITS];

	NN_ASSIGN_DIGIT(t, 1, aDigits);
	NN_Sub(aMinus1, a, t, aDigits);

	NN_Gcd(u, aMinus1, b, aDigits);

	status = NN_EQUAL(t, u, aDigits);

	R_memset((POINTER)aMinus1, 0, sizeof(aMinus1));

	return(status);
}
//---------------------------------------------------------------------------
// RSA.C - RSA routines
//---------------------------------------------------------------------------
static int rsapublicfunc(unsigned char *, unsigned int *, unsigned char *, unsigned int, R_RSA_PUBLIC_KEY *);
static int rsaprivatefunc(unsigned char *, unsigned int *, unsigned char *, unsigned int, R_RSA_PRIVATE_KEY *);

/* RSA encryption, according to RSADSI's PKCS #1. */
int RSAPublicEncrypt(unsigned char *output, unsigned int *outputLen, unsigned char *input,
                     unsigned int inputLen, R_RSA_PUBLIC_KEY *publicKey, R_RANDOM_STRUCT *randomStruct)
{
	int status;
	unsigned char byte, pkcsBlock[MAX_RSA_MODULUS_LEN];
	unsigned int i, modulusLen;

	modulusLen = (publicKey->bits + 7) / 8;

	if(inputLen + 11 > modulusLen)
        return(RE_LEN);

    R_GetRandomBytesNeeded(&i, randomStruct);
    if(i != 0)
        return(RE_NEED_RANDOM);

	*pkcsBlock = 0;                 /* PKCS Block Makeup */

		/* block type 2 */
	*(pkcsBlock+1) = 2;

	for(i = 2; i < modulusLen - inputLen - 1; i++) {
		/* Find nonzero random byte. */
		do {    /* random bytes used to pad the PKCS Block */
			R_GenerateBytes(&byte, 1, randomStruct);
		}while(byte == 0);
		*(pkcsBlock+i) = byte;
	}

	/* separator */
	pkcsBlock[i++] = 0;

	R_memcpy((POINTER)&pkcsBlock[i], (POINTER)input, inputLen);

	status = rsapublicfunc(output, outputLen, pkcsBlock, modulusLen, publicKey);

	/* Clear sensitive information. */

	byte = 0;
	R_memset((POINTER)pkcsBlock, 0, sizeof(pkcsBlock));

	return(status);
}

/* RSA decryption, according to RSADSI's PKCS #1. */

int RSAPublicDecrypt(unsigned char *output, unsigned int *outputLen, unsigned char *input,
                     unsigned int inputLen, R_RSA_PUBLIC_KEY *publicKey)
{
	int status;
	unsigned char pkcsBlock[MAX_RSA_MODULUS_LEN];
	unsigned int i, modulusLen, pkcsBlockLen;

	modulusLen = (publicKey->bits + 7) / 8;

	if(inputLen > modulusLen)
		return(RE_LEN);

	status = rsapublicfunc(pkcsBlock, &pkcsBlockLen, input, inputLen, publicKey);
	if(status)
		return(status);

	if(pkcsBlockLen != modulusLen)
		return(RE_LEN);

	/* Require block type 1. */

	if((pkcsBlock[0] != 0) || (pkcsBlock[1] != 1))
	 return(RE_DATA);

	for(i = 2; i < modulusLen-1; i++)
		if(*(pkcsBlock+i) != 0xff)
			break;

	/* separator check */

	if(pkcsBlock[i++] != 0)
		return(RE_DATA);

	*outputLen = modulusLen - i;

	if(*outputLen + 11 > modulusLen)
		return(RE_DATA);

	R_memcpy((POINTER)output, (POINTER)&pkcsBlock[i], *outputLen);

	/* Clear sensitive information. */

	R_memset((POINTER)pkcsBlock, 0, sizeof(pkcsBlock));

	return(RSA_ID_OK);
}

/* RSA encryption, according to RSADSI's PKCS #1. */

int RSAPrivateEncrypt(unsigned char *output, unsigned int *outputLen, unsigned char *input,
                      unsigned int inputLen, R_RSA_PRIVATE_KEY *privateKey)
{
	int status;
	unsigned char pkcsBlock[MAX_RSA_MODULUS_LEN];
	unsigned int i, modulusLen;

	modulusLen = (privateKey->bits + 7) / 8;

	if(inputLen + 11 > modulusLen)
		return (RE_LEN);

	*pkcsBlock = 0;
	/* block type 1 */
	*(pkcsBlock+1) = 1;

	for (i = 2; i < modulusLen - inputLen - 1; i++)
		*(pkcsBlock+i) = 0xff;

	/* separator */
	pkcsBlock[i++] = 0;

	R_memcpy((POINTER)&pkcsBlock[i], (POINTER)input, inputLen);

	status = rsaprivatefunc(output, outputLen, pkcsBlock, modulusLen, privateKey);

	/* Clear sensitive information. */

	R_memset((POINTER)pkcsBlock, 0, sizeof(pkcsBlock));

	return(status);
}

/* RSA decryption, according to RSADSI's PKCS #1. */

int RSAPrivateDecrypt(unsigned char *output, unsigned int *outputLen, unsigned char *input,
                      unsigned int inputLen, R_RSA_PRIVATE_KEY *privateKey)
{
	int status;
	unsigned char pkcsBlock[MAX_RSA_MODULUS_LEN];
	unsigned int i, modulusLen, pkcsBlockLen;

	modulusLen = (privateKey->bits + 7) / 8;

	if(inputLen > modulusLen)
		return (RE_LEN);

	status = rsaprivatefunc(pkcsBlock, &pkcsBlockLen, input, inputLen, privateKey);
	if(status)
		return (status);

	if(pkcsBlockLen != modulusLen)
		return (RE_LEN);

	/* We require block type 2. */

	if((*pkcsBlock != 0) || (*(pkcsBlock+1) != 2))
	 return (RE_DATA);

	for(i = 2; i < modulusLen-1; i++)
		/* separator */
		if (*(pkcsBlock+i) == 0)
			break;

	i++;
	if(i >= modulusLen)
		return(RE_DATA);

	*outputLen = modulusLen - i;

	if(*outputLen + 11 > modulusLen)
		return(RE_DATA);

	R_memcpy((POINTER)output, (POINTER)&pkcsBlock[i], *outputLen);

	/* Clear sensitive information. */
	R_memset((POINTER)pkcsBlock, 0, sizeof(pkcsBlock));

	return(RSA_ID_OK);
}

/* Raw RSA public-key operation. Output has same length as modulus.

	 Requires input < modulus.
*/
static int rsapublicfunc(unsigned char *output, unsigned int *outputLen, unsigned char *input,
                         unsigned int inputLen, R_RSA_PUBLIC_KEY *publicKey)
{
	NN_DIGIT c[MAX_NN_DIGITS], e[MAX_NN_DIGITS], m[MAX_NN_DIGITS],
		n[MAX_NN_DIGITS];
	unsigned int eDigits, nDigits;


		/* decode the required RSA function input data */
	NN_Decode(m, MAX_NN_DIGITS, input, inputLen);
	NN_Decode(n, MAX_NN_DIGITS, publicKey->modulus, MAX_RSA_MODULUS_LEN);
	NN_Decode(e, MAX_NN_DIGITS, publicKey->exponent, MAX_RSA_MODULUS_LEN);

	nDigits = NN_Digits(n, MAX_NN_DIGITS);
	eDigits = NN_Digits(e, MAX_NN_DIGITS);

	if(NN_Cmp(m, n, nDigits) >= 0)
		return(RE_DATA);

	*outputLen = (publicKey->bits + 7) / 8;

	/* Compute c = m^e mod n.  To perform actual RSA calc.*/

	NN_ModExp (c, m, e, eDigits, n, nDigits);

	/* encode output to standard form */
	NN_Encode (output, *outputLen, c, nDigits);

	/* Clear sensitive information. */

	R_memset((POINTER)c, 0, sizeof(c));
	R_memset((POINTER)m, 0, sizeof(m));

	return(RSA_ID_OK);
}

/* Raw RSA private-key operation. Output has same length as modulus.

	 Requires input < modulus.
*/

static int rsaprivatefunc(unsigned char *output, unsigned int *outputLen, unsigned char *input,
                          unsigned int inputLen, R_RSA_PRIVATE_KEY *privateKey)
{
	NN_DIGIT c[MAX_NN_DIGITS], cP[MAX_NN_DIGITS], cQ[MAX_NN_DIGITS],
		dP[MAX_NN_DIGITS], dQ[MAX_NN_DIGITS], mP[MAX_NN_DIGITS],
		mQ[MAX_NN_DIGITS], n[MAX_NN_DIGITS], p[MAX_NN_DIGITS], q[MAX_NN_DIGITS],
		qInv[MAX_NN_DIGITS], t[MAX_NN_DIGITS];
	unsigned int cDigits, nDigits, pDigits;

	/* decode required input data from standard form */
	NN_Decode(c, MAX_NN_DIGITS, input, inputLen);           /* input */
					/* private key data */
	NN_Decode(p, MAX_NN_DIGITS, privateKey->prime[0], MAX_RSA_PRIME_LEN);
	NN_Decode(q, MAX_NN_DIGITS, privateKey->prime[1], MAX_RSA_PRIME_LEN);
	NN_Decode(dP, MAX_NN_DIGITS, privateKey->primeExponent[0], MAX_RSA_PRIME_LEN);
	NN_Decode(dQ, MAX_NN_DIGITS, privateKey->primeExponent[1], MAX_RSA_PRIME_LEN);
	NN_Decode(n, MAX_NN_DIGITS, privateKey->modulus, MAX_RSA_MODULUS_LEN);
	NN_Decode(qInv, MAX_NN_DIGITS, privateKey->coefficient, MAX_RSA_PRIME_LEN);
		/* work out lengths of input components */

    cDigits = NN_Digits(c, MAX_NN_DIGITS);
    pDigits = NN_Digits(p, MAX_NN_DIGITS);
	nDigits = NN_Digits(n, MAX_NN_DIGITS);


	if(NN_Cmp(c, n, nDigits) >= 0)
		return(RE_DATA);

	*outputLen = (privateKey->bits + 7) / 8;

	/* Compute mP = cP^dP mod p  and  mQ = cQ^dQ mod q. (Assumes q has
		 length at most pDigits, i.e., p > q.)
	*/

	NN_Mod(cP, c, cDigits, p, pDigits);
	NN_Mod(cQ, c, cDigits, q, pDigits);

	NN_AssignZero(mP, nDigits);
	NN_ModExp(mP, cP, dP, pDigits, p, pDigits);

	NN_AssignZero(mQ, nDigits);
	NN_ModExp(mQ, cQ, dQ, pDigits, q, pDigits);

	/* Chinese Remainder Theorem:
			m = ((((mP - mQ) mod p) * qInv) mod p) * q + mQ.
	*/

	if(NN_Cmp(mP, mQ, pDigits) >= 0) {
		NN_Sub(t, mP, mQ, pDigits);
	}else{
		NN_Sub(t, mQ, mP, pDigits);
		NN_Sub(t, p, t, pDigits);
	}

	NN_ModMult(t, t, qInv, p, pDigits);
	NN_Mult(t, t, q, pDigits);
	NN_Add(t, t, mQ, nDigits);

	/* encode output to standard form */
	NN_Encode (output, *outputLen, t, nDigits);

	/* Clear sensitive information. */
	R_memset((POINTER)c, 0, sizeof(c));
	R_memset((POINTER)cP, 0, sizeof(cP));
	R_memset((POINTER)cQ, 0, sizeof(cQ));
	R_memset((POINTER)dP, 0, sizeof(dP));
	R_memset((POINTER)dQ, 0, sizeof(dQ));
	R_memset((POINTER)mP, 0, sizeof(mP));
	R_memset((POINTER)mQ, 0, sizeof(mQ));
	R_memset((POINTER)p, 0, sizeof(p));
	R_memset((POINTER)q, 0, sizeof(q));
	R_memset((POINTER)qInv, 0, sizeof(qInv));
	R_memset((POINTER)t, 0, sizeof(t));
	return(RSA_ID_OK);
}
//---------------------------------------------------------------------------
// DESC.C - Data Encryption Standard routines
//---------------------------------------------------------------------------
static UINT2 bytebit[8] = {
	0200, 0100, 040, 020, 010, 04, 02, 01
};

static UINT4 bigbyte[24] = {
	0x800000L, 0x400000L, 0x200000L, 0x100000L,
	0x80000L,  0x40000L,  0x20000L,  0x10000L,
	0x8000L,   0x4000L,   0x2000L,   0x1000L,
	0x800L,    0x400L,    0x200L,    0x100L,
	0x80L,     0x40L,     0x20L,     0x10L,
	0x8L,      0x4L,      0x2L,      0x1L
};

static unsigned char totrot[16] = {
	1, 2, 4, 6, 8, 10, 12, 14, 15, 17, 19, 21, 23, 25, 27, 28
};

static unsigned char pc1[56] = {
	56, 48, 40, 32, 24, 16,  8,      0, 57, 49, 41, 33, 25, 17,
	 9,  1, 58, 50, 42, 34, 26,     18, 10,  2, 59, 51, 43, 35,
	62, 54, 46, 38, 30, 22, 14,      6, 61, 53, 45, 37, 29, 21,
	13,  5, 60, 52, 44, 36, 28,     20, 12,  4, 27, 19, 11,  3
};

static unsigned char pc2[48] = {
	13, 16, 10, 23,  0,  4,  2, 27, 14,  5, 20,  9,
	22, 18, 11,  3, 25,  7, 15,  6, 26, 19, 12,  1,
	40, 51, 30, 36, 46, 54, 29, 39, 50, 44, 32, 47,
	43, 48, 38, 55, 33, 52, 45, 41, 49, 35, 28, 31
};

#ifndef DES386

UINT4 Spbox[8][64] = {
	0x01010400L, 0x00000000L, 0x00010000L, 0x01010404L,
	0x01010004L, 0x00010404L, 0x00000004L, 0x00010000L,
	0x00000400L, 0x01010400L, 0x01010404L, 0x00000400L,
	0x01000404L, 0x01010004L, 0x01000000L, 0x00000004L,
	0x00000404L, 0x01000400L, 0x01000400L, 0x00010400L,
	0x00010400L, 0x01010000L, 0x01010000L, 0x01000404L,
	0x00010004L, 0x01000004L, 0x01000004L, 0x00010004L,
	0x00000000L, 0x00000404L, 0x00010404L, 0x01000000L,
	0x00010000L, 0x01010404L, 0x00000004L, 0x01010000L,
	0x01010400L, 0x01000000L, 0x01000000L, 0x00000400L,
	0x01010004L, 0x00010000L, 0x00010400L, 0x01000004L,
	0x00000400L, 0x00000004L, 0x01000404L, 0x00010404L,
	0x01010404L, 0x00010004L, 0x01010000L, 0x01000404L,
	0x01000004L, 0x00000404L, 0x00010404L, 0x01010400L,
	0x00000404L, 0x01000400L, 0x01000400L, 0x00000000L,
	0x00010004L, 0x00010400L, 0x00000000L, 0x01010004L,
	0x80108020L, 0x80008000L, 0x00008000L, 0x00108020L,
	0x00100000L, 0x00000020L, 0x80100020L, 0x80008020L,
	0x80000020L, 0x80108020L, 0x80108000L, 0x80000000L,
	0x80008000L, 0x00100000L, 0x00000020L, 0x80100020L,
	0x00108000L, 0x00100020L, 0x80008020L, 0x00000000L,
	0x80000000L, 0x00008000L, 0x00108020L, 0x80100000L,
	0x00100020L, 0x80000020L, 0x00000000L, 0x00108000L,
	0x00008020L, 0x80108000L, 0x80100000L, 0x00008020L,
	0x00000000L, 0x00108020L, 0x80100020L, 0x00100000L,
	0x80008020L, 0x80100000L, 0x80108000L, 0x00008000L,
	0x80100000L, 0x80008000L, 0x00000020L, 0x80108020L,
	0x00108020L, 0x00000020L, 0x00008000L, 0x80000000L,
	0x00008020L, 0x80108000L, 0x00100000L, 0x80000020L,
	0x00100020L, 0x80008020L, 0x80000020L, 0x00100020L,
	0x00108000L, 0x00000000L, 0x80008000L, 0x00008020L,
	0x80000000L, 0x80100020L, 0x80108020L, 0x00108000L,
	0x00000208L, 0x08020200L, 0x00000000L, 0x08020008L,
	0x08000200L, 0x00000000L, 0x00020208L, 0x08000200L,
	0x00020008L, 0x08000008L, 0x08000008L, 0x00020000L,
	0x08020208L, 0x00020008L, 0x08020000L, 0x00000208L,
	0x08000000L, 0x00000008L, 0x08020200L, 0x00000200L,
	0x00020200L, 0x08020000L, 0x08020008L, 0x00020208L,
	0x08000208L, 0x00020200L, 0x00020000L, 0x08000208L,
	0x00000008L, 0x08020208L, 0x00000200L, 0x08000000L,
	0x08020200L, 0x08000000L, 0x00020008L, 0x00000208L,
	0x00020000L, 0x08020200L, 0x08000200L, 0x00000000L,
	0x00000200L, 0x00020008L, 0x08020208L, 0x08000200L,
	0x08000008L, 0x00000200L, 0x00000000L, 0x08020008L,
	0x08000208L, 0x00020000L, 0x08000000L, 0x08020208L,
	0x00000008L, 0x00020208L, 0x00020200L, 0x08000008L,
	0x08020000L, 0x08000208L, 0x00000208L, 0x08020000L,
	0x00020208L, 0x00000008L, 0x08020008L, 0x00020200L,
	0x00802001L, 0x00002081L, 0x00002081L, 0x00000080L,
	0x00802080L, 0x00800081L, 0x00800001L, 0x00002001L,
	0x00000000L, 0x00802000L, 0x00802000L, 0x00802081L,
	0x00000081L, 0x00000000L, 0x00800080L, 0x00800001L,
	0x00000001L, 0x00002000L, 0x00800000L, 0x00802001L,
	0x00000080L, 0x00800000L, 0x00002001L, 0x00002080L,
	0x00800081L, 0x00000001L, 0x00002080L, 0x00800080L,
	0x00002000L, 0x00802080L, 0x00802081L, 0x00000081L,
	0x00800080L, 0x00800001L, 0x00802000L, 0x00802081L,
	0x00000081L, 0x00000000L, 0x00000000L, 0x00802000L,
	0x00002080L, 0x00800080L, 0x00800081L, 0x00000001L,
	0x00802001L, 0x00002081L, 0x00002081L, 0x00000080L,
	0x00802081L, 0x00000081L, 0x00000001L, 0x00002000L,
	0x00800001L, 0x00002001L, 0x00802080L, 0x00800081L,
	0x00002001L, 0x00002080L, 0x00800000L, 0x00802001L,
	0x00000080L, 0x00800000L, 0x00002000L, 0x00802080L,
	0x00000100L, 0x02080100L, 0x02080000L, 0x42000100L,
	0x00080000L, 0x00000100L, 0x40000000L, 0x02080000L,
	0x40080100L, 0x00080000L, 0x02000100L, 0x40080100L,
	0x42000100L, 0x42080000L, 0x00080100L, 0x40000000L,
	0x02000000L, 0x40080000L, 0x40080000L, 0x00000000L,
	0x40000100L, 0x42080100L, 0x42080100L, 0x02000100L,
	0x42080000L, 0x40000100L, 0x00000000L, 0x42000000L,
	0x02080100L, 0x02000000L, 0x42000000L, 0x00080100L,
	0x00080000L, 0x42000100L, 0x00000100L, 0x02000000L,
	0x40000000L, 0x02080000L, 0x42000100L, 0x40080100L,
	0x02000100L, 0x40000000L, 0x42080000L, 0x02080100L,
	0x40080100L, 0x00000100L, 0x02000000L, 0x42080000L,
	0x42080100L, 0x00080100L, 0x42000000L, 0x42080100L,
	0x02080000L, 0x00000000L, 0x40080000L, 0x42000000L,
	0x00080100L, 0x02000100L, 0x40000100L, 0x00080000L,
	0x00000000L, 0x40080000L, 0x02080100L, 0x40000100L,
	0x20000010L, 0x20400000L, 0x00004000L, 0x20404010L,
	0x20400000L, 0x00000010L, 0x20404010L, 0x00400000L,
	0x20004000L, 0x00404010L, 0x00400000L, 0x20000010L,
	0x00400010L, 0x20004000L, 0x20000000L, 0x00004010L,
	0x00000000L, 0x00400010L, 0x20004010L, 0x00004000L,
	0x00404000L, 0x20004010L, 0x00000010L, 0x20400010L,
	0x20400010L, 0x00000000L, 0x00404010L, 0x20404000L,
	0x00004010L, 0x00404000L, 0x20404000L, 0x20000000L,
	0x20004000L, 0x00000010L, 0x20400010L, 0x00404000L,
	0x20404010L, 0x00400000L, 0x00004010L, 0x20000010L,
	0x00400000L, 0x20004000L, 0x20000000L, 0x00004010L,
	0x20000010L, 0x20404010L, 0x00404000L, 0x20400000L,
	0x00404010L, 0x20404000L, 0x00000000L, 0x20400010L,
	0x00000010L, 0x00004000L, 0x20400000L, 0x00404010L,
	0x00004000L, 0x00400010L, 0x20004010L, 0x00000000L,
	0x20404000L, 0x20000000L, 0x00400010L, 0x20004010L,
	0x00200000L, 0x04200002L, 0x04000802L, 0x00000000L,
	0x00000800L, 0x04000802L, 0x00200802L, 0x04200800L,
	0x04200802L, 0x00200000L, 0x00000000L, 0x04000002L,
	0x00000002L, 0x04000000L, 0x04200002L, 0x00000802L,
	0x04000800L, 0x00200802L, 0x00200002L, 0x04000800L,
	0x04000002L, 0x04200000L, 0x04200800L, 0x00200002L,
	0x04200000L, 0x00000800L, 0x00000802L, 0x04200802L,
	0x00200800L, 0x00000002L, 0x04000000L, 0x00200800L,
	0x04000000L, 0x00200800L, 0x00200000L, 0x04000802L,
	0x04000802L, 0x04200002L, 0x04200002L, 0x00000002L,
	0x00200002L, 0x04000000L, 0x04000800L, 0x00200000L,
	0x04200800L, 0x00000802L, 0x00200802L, 0x04200800L,
	0x00000802L, 0x04000002L, 0x04200802L, 0x04200000L,
	0x00200800L, 0x00000000L, 0x00000002L, 0x04200802L,
	0x00000000L, 0x00200802L, 0x04200000L, 0x00000800L,
	0x04000002L, 0x04000800L, 0x00000800L, 0x00200002L,
	0x10001040L, 0x00001000L, 0x00040000L, 0x10041040L,
	0x10000000L, 0x10001040L, 0x00000040L, 0x10000000L,
	0x00040040L, 0x10040000L, 0x10041040L, 0x00041000L,
	0x10041000L, 0x00041040L, 0x00001000L, 0x00000040L,
	0x10040000L, 0x10000040L, 0x10001000L, 0x00001040L,
	0x00041000L, 0x00040040L, 0x10040040L, 0x10041000L,
	0x00001040L, 0x00000000L, 0x00000000L, 0x10040040L,
	0x10000040L, 0x10001000L, 0x00041040L, 0x00040000L,
	0x00041040L, 0x00040000L, 0x10041000L, 0x00001000L,
	0x00000040L, 0x10040040L, 0x00001000L, 0x00041040L,
	0x10001000L, 0x00000040L, 0x10000040L, 0x10040000L,
	0x10040040L, 0x10000000L, 0x00040000L, 0x10001040L,
	0x00000000L, 0x10041040L, 0x00040040L, 0x10000040L,
	0x10040000L, 0x10001000L, 0x10001040L, 0x00000000L,
	0x10041040L, 0x00041000L, 0x00041000L, 0x00001040L,
	0x00001040L, 0x00040040L, 0x10000000L, 0x10041000L
};

#else
	/* S box tables for assembler desfunc */

unsigned long Spbox[8][64] = {
	0x04041000,0x00000000,0x00040000,0x04041010,
	0x04040010,0x00041010,0x00000010,0x00040000,
	0x00001000,0x04041000,0x04041010,0x00001000,
	0x04001010,0x04040010,0x04000000,0x00000010,
	0x00001010,0x04001000,0x04001000,0x00041000,
	0x00041000,0x04040000,0x04040000,0x04001010,
	0x00040010,0x04000010,0x04000010,0x00040010,
	0x00000000,0x00001010,0x00041010,0x04000000,
	0x00040000,0x04041010,0x00000010,0x04040000,
	0x04041000,0x04000000,0x04000000,0x00001000,
	0x04040010,0x00040000,0x00041000,0x04000010,
	0x00001000,0x00000010,0x04001010,0x00041010,
	0x04041010,0x00040010,0x04040000,0x04001010,
	0x04000010,0x00001010,0x00041010,0x04041000,
	0x00001010,0x04001000,0x04001000,0x00000000,
	0x00040010,0x00041000,0x00000000,0x04040010,
	0x00420082,0x00020002,0x00020000,0x00420080,
	0x00400000,0x00000080,0x00400082,0x00020082,
	0x00000082,0x00420082,0x00420002,0x00000002,
	0x00020002,0x00400000,0x00000080,0x00400082,
	0x00420000,0x00400080,0x00020082,0x00000000,
	0x00000002,0x00020000,0x00420080,0x00400002,
	0x00400080,0x00000082,0x00000000,0x00420000,
	0x00020080,0x00420002,0x00400002,0x00020080,
	0x00000000,0x00420080,0x00400082,0x00400000,
	0x00020082,0x00400002,0x00420002,0x00020000,
	0x00400002,0x00020002,0x00000080,0x00420082,
	0x00420080,0x00000080,0x00020000,0x00000002,
	0x00020080,0x00420002,0x00400000,0x00000082,
	0x00400080,0x00020082,0x00000082,0x00400080,
	0x00420000,0x00000000,0x00020002,0x00020080,
	0x00000002,0x00400082,0x00420082,0x00420000,
	0x00000820,0x20080800,0x00000000,0x20080020,
	0x20000800,0x00000000,0x00080820,0x20000800,
	0x00080020,0x20000020,0x20000020,0x00080000,
	0x20080820,0x00080020,0x20080000,0x00000820,
	0x20000000,0x00000020,0x20080800,0x00000800,
	0x00080800,0x20080000,0x20080020,0x00080820,
	0x20000820,0x00080800,0x00080000,0x20000820,
	0x00000020,0x20080820,0x00000800,0x20000000,
	0x20080800,0x20000000,0x00080020,0x00000820,
	0x00080000,0x20080800,0x20000800,0x00000000,
	0x00000800,0x00080020,0x20080820,0x20000800,
	0x20000020,0x00000800,0x00000000,0x20080020,
	0x20000820,0x00080000,0x20000000,0x20080820,
	0x00000020,0x00080820,0x00080800,0x20000020,
	0x20080000,0x20000820,0x00000820,0x20080000,
	0x00080820,0x00000020,0x20080020,0x00080800,
	0x02008004,0x00008204,0x00008204,0x00000200,
	0x02008200,0x02000204,0x02000004,0x00008004,
	0x00000000,0x02008000,0x02008000,0x02008204,
	0x00000204,0x00000000,0x02000200,0x02000004,
	0x00000004,0x00008000,0x02000000,0x02008004,
	0x00000200,0x02000000,0x00008004,0x00008200,
	0x02000204,0x00000004,0x00008200,0x02000200,
	0x00008000,0x02008200,0x02008204,0x00000204,
	0x02000200,0x02000004,0x02008000,0x02008204,
	0x00000204,0x00000000,0x00000000,0x02008000,
	0x00008200,0x02000200,0x02000204,0x00000004,
	0x02008004,0x00008204,0x00008204,0x00000200,
	0x02008204,0x00000204,0x00000004,0x00008000,
	0x02000004,0x00008004,0x02008200,0x02000204,
	0x00008004,0x00008200,0x02000000,0x02008004,
	0x00000200,0x02000000,0x00008000,0x02008200,
	0x00000400,0x08200400,0x08200000,0x08000401,
	0x00200000,0x00000400,0x00000001,0x08200000,
	0x00200401,0x00200000,0x08000400,0x00200401,
	0x08000401,0x08200001,0x00200400,0x00000001,
	0x08000000,0x00200001,0x00200001,0x00000000,
	0x00000401,0x08200401,0x08200401,0x08000400,
	0x08200001,0x00000401,0x00000000,0x08000001,
	0x08200400,0x08000000,0x08000001,0x00200400,
	0x00200000,0x08000401,0x00000400,0x08000000,
	0x00000001,0x08200000,0x08000401,0x00200401,
	0x08000400,0x00000001,0x08200001,0x08200400,
	0x00200401,0x00000400,0x08000000,0x08200001,
	0x08200401,0x00200400,0x08000001,0x08200401,
	0x08200000,0x00000000,0x00200001,0x08000001,
	0x00200400,0x08000400,0x00000401,0x00200000,
	0x00000000,0x00200001,0x08200400,0x00000401,
	0x80000040,0x81000000,0x00010000,0x81010040,
	0x81000000,0x00000040,0x81010040,0x01000000,
	0x80010000,0x01010040,0x01000000,0x80000040,
	0x01000040,0x80010000,0x80000000,0x00010040,
	0x00000000,0x01000040,0x80010040,0x00010000,
	0x01010000,0x80010040,0x00000040,0x81000040,
	0x81000040,0x00000000,0x01010040,0x81010000,
	0x00010040,0x01010000,0x81010000,0x80000000,
	0x80010000,0x00000040,0x81000040,0x01010000,
	0x81010040,0x01000000,0x00010040,0x80000040,
	0x01000000,0x80010000,0x80000000,0x00010040,
	0x80000040,0x81010040,0x01010000,0x81000000,
	0x01010040,0x81010000,0x00000000,0x81000040,
	0x00000040,0x00010000,0x81000000,0x01010040,
	0x00010000,0x01000040,0x80010040,0x00000000,
	0x81010000,0x80000000,0x01000040,0x80010040,
	0x00800000,0x10800008,0x10002008,0x00000000,
	0x00002000,0x10002008,0x00802008,0x10802000,
	0x10802008,0x00800000,0x00000000,0x10000008,
	0x00000008,0x10000000,0x10800008,0x00002008,
	0x10002000,0x00802008,0x00800008,0x10002000,
	0x10000008,0x10800000,0x10802000,0x00800008,
	0x10800000,0x00002000,0x00002008,0x10802008,
	0x00802000,0x00000008,0x10000000,0x00802000,
	0x10000000,0x00802000,0x00800000,0x10002008,
	0x10002008,0x10800008,0x10800008,0x00000008,
	0x00800008,0x10000000,0x10002000,0x00800000,
	0x10802000,0x00002008,0x00802008,0x10802000,
	0x00002008,0x10000008,0x10802008,0x10800000,
	0x00802000,0x00000000,0x00000008,0x10802008,
	0x00000000,0x00802008,0x10800000,0x00002000,
	0x10000008,0x10002000,0x00002000,0x00800008,
	0x40004100,0x00004000,0x00100000,0x40104100,
	0x40000000,0x40004100,0x00000100,0x40000000,
	0x00100100,0x40100000,0x40104100,0x00104000,
	0x40104000,0x00104100,0x00004000,0x00000100,
	0x40100000,0x40000100,0x40004000,0x00004100,
	0x00104000,0x00100100,0x40100100,0x40104000,
	0x00004100,0x00000000,0x00000000,0x40100100,
	0x40000100,0x40004000,0x00104100,0x00100000,
	0x00104100,0x00100000,0x40104000,0x00004000,
	0x00000100,0x40100100,0x00004000,0x00104100,
	0x40004000,0x00000100,0x40000100,0x40100000,
	0x40100100,0x40000000,0x00100000,0x40004100,
	0x00000000,0x40104100,0x00100100,0x40000100,
	0x40100000,0x40004000,0x40004100,0x00000000,
	0x40104100,0x00104000,0x00104000,0x00004100,
	0x00004100,0x00100100,0x40000000,0x40104000,
};

#endif

void unscrunch(unsigned char *, UINT4 *);
void scrunch(UINT4 *, unsigned char *);
void deskey(UINT4 *, unsigned char *, int);
static void cookey(UINT4 *, UINT4 *, int);
void desfunc(UINT4 *, UINT4 *);

/* Initialize context.  Caller must zeroize the context when finished. */

void DES_CBCInit(DES_CBC_CTX *context, unsigned char *key, unsigned char *iv, int encrypt)
{
	/* Save encrypt flag to context. */
	context->encrypt = encrypt;

	/* Pack initializing vector into context. */

	scrunch(context->iv, iv);
	scrunch(context->originalIV, iv);

	/* Precompute key schedule */

	deskey(context->subkeys, key, encrypt);
}

/* DES-CBC block update operation. Continues a DES-CBC encryption
	 operation, processing eight-byte message blocks, and updating
	 the context.

	 This requires len to be a multiple of 8.
*/
int DES_CBCUpdate(DES_CBC_CTX *context, unsigned char *output, unsigned char *input, unsigned int len)
{
	UINT4 inputBlock[2], work[2];
	unsigned int i;

	if(len % 8)                                                                             /* block size check */
            return(RE_LEN);

	for(i = 0; i < len/8; i++) {
		scrunch(inputBlock,&input[8*i]);

		/* Chain if encrypting. */

		if(context->encrypt == 0) {
			*work = *inputBlock;
			*(work+1) = *(inputBlock+1);
		}else{
			*work = *inputBlock ^ *context->iv;
			*(work+1) = *(inputBlock+1) ^ *(context->iv+1);
		}

		desfunc(work, context->subkeys);

		/* Chain if decrypting, then update IV. */

		if(context->encrypt == 0) {
			*work ^= *context->iv;
			*(work+1) ^= *(context->iv+1);
			*context->iv = *inputBlock;
			*(context->iv+1) = *(inputBlock+1);
		}else{
			*context->iv = *work;
			*(context->iv+1) = *(work+1);
		}
		unscrunch (&output[8*i], work);
	}

	/* Clear sensitive information. */

	R_memset((POINTER)inputBlock, 0, sizeof(inputBlock));
	R_memset((POINTER)work, 0, sizeof(work));

	return(RSA_ID_OK);
}

void DES_CBCRestart(DES_CBC_CTX *context)
{
	/* Restore the original IV */

	*context->iv = *context->originalIV;
	*(context->iv+1) = *(context->originalIV+1);
}

/* Initialize context.  Caller should clear the context when finished.
	 The key has the DES key, input whitener and output whitener concatenated.
	 This is the RSADSI special DES implementation.
*/
void DESX_CBCInit(DESX_CBC_CTX *context, unsigned char *key, unsigned char *iv, int encrypt)
{
	/* Save encrypt flag to context. */

	context->encrypt = encrypt;

	/* Pack initializing vector and whiteners into context. */

	scrunch(context->iv, iv);
	scrunch(context->inputWhitener, key + 8);
	scrunch(context->outputWhitener, key + 16);
	/* Save the IV for use in Restart */
	scrunch(context->originalIV, iv);

	/* Precompute key schedule. */

	deskey (context->subkeys, key, encrypt);
}

/* DESX-CBC block update operation. Continues a DESX-CBC encryption
	 operation, processing eight-byte message blocks, and updating
	 the context.  This is the RSADSI special DES implementation.

	 Requires len to a multiple of 8.
*/

int DESX_CBCUpdate(DESX_CBC_CTX *context, unsigned char *output, unsigned char *input, unsigned int len)
{
	UINT4 inputBlock[2], work[2];
	unsigned int i;

	if(len % 8)                                                                             /* Length check */
		return(RE_LEN);

	for(i = 0; i < len/8; i++)  {
		scrunch(inputBlock, &input[8*i]);

		/* Chain if encrypting, and xor with whitener. */

		if(context->encrypt == 0) {
			*work = *inputBlock ^ *context->outputWhitener;
			*(work+1) = *(inputBlock+1) ^ *(context->outputWhitener+1);
		}else{
			*work = *inputBlock ^ *context->iv ^ *context->inputWhitener;
			*(work+1) = *(inputBlock+1) ^ *(context->iv+1) ^ *(context->inputWhitener+1);
		}

		desfunc(work, context->subkeys);

		/* Xor with whitener, chain if decrypting, then update IV. */

		if(context->encrypt == 0) {
			*work ^= *context->iv ^ *context->inputWhitener;
			*(work+1) ^= *(context->iv+1) ^ *(context->inputWhitener+1);
			*(context->iv) = *inputBlock;
			*(context->iv+1) = *(inputBlock+1);
		}else{
			*work ^= *context->outputWhitener;
			*(work+1) ^= *(context->outputWhitener+1);
			*context->iv = *work;
			*(context->iv+1) = *(work+1);
		}
		unscrunch(&output[8*i], work);
	}

	R_memset((POINTER)inputBlock, 0, sizeof(inputBlock));
	R_memset((POINTER)work, 0, sizeof(work));

	return(RSA_ID_OK);
}

void DESX_CBCRestart(DESX_CBC_CTX *context)
{
	/* Restore the original IV */
	*context->iv = *context->originalIV;
	*(context->iv+1) = *(context->originalIV+1);
}

/* Initialize context.  Caller must zeroize the context when finished. */

void DES3_CBCInit(DES3_CBC_CTX *context, unsigned char *key, unsigned char *iv, int encrypt)
{
	/* Copy encrypt flag to context. */
	context->encrypt = encrypt;

	/* Pack initializing vector into context. */

	scrunch(context->iv, iv);

	/* Save the IV for use in Restart */
	scrunch(context->originalIV, iv);

	/* Precompute key schedules. */

	deskey(context->subkeys[0], encrypt ? key : &key[16], encrypt);
	deskey(context->subkeys[1], &key[8], !encrypt);
	deskey(context->subkeys[2], encrypt ? &key[16] : key, encrypt);
}

int DES3_CBCUpdate(DES3_CBC_CTX *context, unsigned char *output, unsigned char *input, unsigned int len)
{
	UINT4 inputBlock[2], work[2];
	unsigned int i;

	if(len % 8)                  /* length check */
		return(RE_LEN);

	for(i = 0; i < len/8; i++) {
		scrunch(inputBlock, &input[8*i]);

		/* Chain if encrypting. */

		if(context->encrypt == 0) {
			*work = *inputBlock;
			*(work+1) = *(inputBlock+1);
		}
		else {
			*work = *inputBlock ^ *context->iv;
			*(work+1) = *(inputBlock+1) ^ *(context->iv+1);
		}

		desfunc(work, context->subkeys[0]);
		desfunc(work, context->subkeys[1]);
		desfunc(work, context->subkeys[2]);

		/* Chain if decrypting, then update IV. */

		if(context->encrypt == 0) {
			*work ^= *context->iv;
			*(work+1) ^= *(context->iv+1);
			*context->iv = *inputBlock;
			*(context->iv+1) = *(inputBlock+1);
		}
		else {
			*context->iv = *work;
			*(context->iv+1) = *(work+1);
		}
		unscrunch(&output[8*i], work);
	}

	R_memset((POINTER)inputBlock, 0, sizeof(inputBlock));
	R_memset((POINTER)work, 0, sizeof(work));

	return (0);
}

void DES3_CBCRestart(DES3_CBC_CTX *context)
{
	/* Restore the original IV */
	*context->iv = *context->originalIV;
	*(context->iv+1) = *(context->originalIV+1);
}

void scrunch(UINT4 *into, unsigned char *outof)
{
	*into    = (*outof++ & 0xffL) << 24;
	*into   |= (*outof++ & 0xffL) << 16;
	*into   |= (*outof++ & 0xffL) << 8;
	*into++ |= (*outof++ & 0xffL);
	*into    = (*outof++ & 0xffL) << 24;
	*into   |= (*outof++ & 0xffL) << 16;
	*into   |= (*outof++ & 0xffL) << 8;
	*into   |= (*outof   & 0xffL);
}

void unscrunch(unsigned char *into, UINT4 *outof)
{
	*into++ = (unsigned char)((*outof >> 24) & 0xffL);
	*into++ = (unsigned char)((*outof >> 16) & 0xffL);
	*into++ = (unsigned char)((*outof >>  8) & 0xffL);
	*into++ = (unsigned char)( *outof++      & 0xffL);
	*into++ = (unsigned char)((*outof >> 24) & 0xffL);
	*into++ = (unsigned char)((*outof >> 16) & 0xffL);
	*into++ = (unsigned char)((*outof >>  8) & 0xffL);
	*into   = (unsigned char)( *outof        & 0xffL);
}

/* Compute DES Subkeys */

void deskey(UINT4 subkeys[32], unsigned char key[8], int encrypt)
{
	UINT4 kn[32];
	int i, j, l, m, n;
	unsigned char pc1m[56], pcr[56];

	for(j = 0; j < 56; j++) {
		l = pc1[j];
		m = l & 07;
		pc1m[j] = (unsigned char)((key[l >> 3] & bytebit[m]) ? 1 : 0);
	}
	for(i = 0; i < 16; i++) {
		m = i << 1;
		n = m + 1;
		kn[m] = kn[n] = 0L;
		for(j = 0; j < 28; j++) {
			l = j + totrot[i];
			if(l < 28) pcr[j] = pc1m[l];
			else pcr[j] = pc1m[l - 28];
		}
		for(j = 28; j < 56; j++) {
			l = j + totrot[i];
			if(l < 56) pcr[j] = pc1m[l];
			else pcr[j] = pc1m[l - 28];
		}
		for(j = 0; j < 24; j++) {
			if(pcr[pc2[j]])
				kn[m] |= bigbyte[j];
			if(pcr[pc2[j+24]])
				kn[n] |= bigbyte[j];
		}
	}
	cookey(subkeys, kn, encrypt);

#ifdef DES386
	for(i=0;i < 32;i++)
		subkeys[i] <<= 2;
#endif

	R_memset((POINTER)pc1m, 0, sizeof(pc1m));
	R_memset((POINTER)pcr, 0, sizeof(pcr));
	R_memset((POINTER)kn, 0, sizeof(kn));
}

static void cookey(UINT4 *subkeys, UINT4 *kn, int encrypt)
{
	UINT4 *cooked, *raw0, *raw1;
	int increment;
	unsigned int i;

	raw1 = kn;
	cooked = encrypt ? subkeys : &subkeys[30];
	increment = encrypt ? 1 : -3;

	for (i = 0; i < 16; i++, raw1++) {
		raw0 = raw1++;
		*cooked    = (*raw0 & 0x00fc0000L) << 6;
		*cooked   |= (*raw0 & 0x00000fc0L) << 10;
		*cooked   |= (*raw1 & 0x00fc0000L) >> 10;
		*cooked++ |= (*raw1 & 0x00000fc0L) >> 6;
		*cooked    = (*raw0 & 0x0003f000L) << 12;
		*cooked   |= (*raw0 & 0x0000003fL) << 16;
		*cooked   |= (*raw1 & 0x0003f000L) >> 4;
		*cooked   |= (*raw1 & 0x0000003fL);
		cooked += increment;
	}
}

#ifndef DES386 /* ignore C version in favor of 386 ONLY desfunc */

#define	F_D(l,r,key){\
	work = ((r >> 4) | (r << 28)) ^ *key;\
	l ^= Spbox[6][work & 0x3f];\
	l ^= Spbox[4][(work >> 8) & 0x3f];\
	l ^= Spbox[2][(work >> 16) & 0x3f];\
	l ^= Spbox[0][(work >> 24) & 0x3f];\
	work = r ^ *(key+1);\
	l ^= Spbox[7][work & 0x3f];\
	l ^= Spbox[5][(work >> 8) & 0x3f];\
	l ^= Spbox[3][(work >> 16) & 0x3f];\
	l ^= Spbox[1][(work >> 24) & 0x3f];\
}

/* This desfunc code is marginally quicker than that uses in
	 RSAREF(tm)
*/

void desfunc(UINT4 *block, UINT4 *ks)
{
	unsigned long left,right,work;

	left = block[0];
	right = block[1];

	work = ((left >> 4) ^ right) & 0x0f0f0f0f;
	right ^= work;
	left ^= work << 4;
	work = ((left >> 16) ^ right) & 0xffff;
	right ^= work;
	left ^= work << 16;
	work = ((right >> 2) ^ left) & 0x33333333;
	left ^= work;
	right ^= (work << 2);
	work = ((right >> 8) ^ left) & 0xff00ff;
	left ^= work;
	right ^= (work << 8);
	right = (right << 1) | (right >> 31);
	work = (left ^ right) & 0xaaaaaaaa;
	left ^= work;
	right ^= work;
	left = (left << 1) | (left >> 31);

	/* Now do the 16 rounds */
	F_D(left,right,&ks[0]);
	F_D(right,left,&ks[2]);
	F_D(left,right,&ks[4]);
	F_D(right,left,&ks[6]);
	F_D(left,right,&ks[8]);
	F_D(right,left,&ks[10]);
	F_D(left,right,&ks[12]);
	F_D(right,left,&ks[14]);
	F_D(left,right,&ks[16]);
	F_D(right,left,&ks[18]);
	F_D(left,right,&ks[20]);
	F_D(right,left,&ks[22]);
	F_D(left,right,&ks[24]);
	F_D(right,left,&ks[26]);
	F_D(left,right,&ks[28]);
	F_D(right,left,&ks[30]);

	right = (right << 31) | (right >> 1);
	work = (left ^ right) & 0xaaaaaaaa;
	left ^= work;
	right ^= work;
	left = (left >> 1) | (left  << 31);
	work = ((left >> 8) ^ right) & 0xff00ff;
	right ^= work;
	left ^= work << 8;
	work = ((left >> 2) ^ right) & 0x33333333;
	right ^= work;
	left ^= work << 2;
	work = ((right >> 16) ^ left) & 0xffff;
	left ^= work;
	right ^= work << 16;
	work = ((right >> 4) ^ left) & 0x0f0f0f0f;
	left ^= work;
	right ^= work << 4;

	*block++ = right;
	*block = left;
}
#endif
//---------------------------------------------------------------------------
// blowfish.c
//---------------------------------------------------------------------------
#define N               16

static unsigned long F_F(BLOWFISH_CTX *ctx, unsigned long x);

static const unsigned long ORIG_P[16 + 2] = {
        0x243F6A88L, 0x85A308D3L, 0x13198A2EL, 0x03707344L,
        0xA4093822L, 0x299F31D0L, 0x082EFA98L, 0xEC4E6C89L,
        0x452821E6L, 0x38D01377L, 0xBE5466CFL, 0x34E90C6CL,
        0xC0AC29B7L, 0xC97C50DDL, 0x3F84D5B5L, 0xB5470917L,
        0x9216D5D9L, 0x8979FB1BL
};

static const unsigned long ORIG_S[4][256] = {
    {   0xD1310BA6L, 0x98DFB5ACL, 0x2FFD72DBL, 0xD01ADFB7L,
        0xB8E1AFEDL, 0x6A267E96L, 0xBA7C9045L, 0xF12C7F99L,
        0x24A19947L, 0xB3916CF7L, 0x0801F2E2L, 0x858EFC16L,
        0x636920D8L, 0x71574E69L, 0xA458FEA3L, 0xF4933D7EL,
        0x0D95748FL, 0x728EB658L, 0x718BCD58L, 0x82154AEEL,
        0x7B54A41DL, 0xC25A59B5L, 0x9C30D539L, 0x2AF26013L,
        0xC5D1B023L, 0x286085F0L, 0xCA417918L, 0xB8DB38EFL,
        0x8E79DCB0L, 0x603A180EL, 0x6C9E0E8BL, 0xB01E8A3EL,
        0xD71577C1L, 0xBD314B27L, 0x78AF2FDAL, 0x55605C60L,
        0xE65525F3L, 0xAA55AB94L, 0x57489862L, 0x63E81440L,
        0x55CA396AL, 0x2AAB10B6L, 0xB4CC5C34L, 0x1141E8CEL,
        0xA15486AFL, 0x7C72E993L, 0xB3EE1411L, 0x636FBC2AL,
        0x2BA9C55DL, 0x741831F6L, 0xCE5C3E16L, 0x9B87931EL,
        0xAFD6BA33L, 0x6C24CF5CL, 0x7A325381L, 0x28958677L,
        0x3B8F4898L, 0x6B4BB9AFL, 0xC4BFE81BL, 0x66282193L,
        0x61D809CCL, 0xFB21A991L, 0x487CAC60L, 0x5DEC8032L,
        0xEF845D5DL, 0xE98575B1L, 0xDC262302L, 0xEB651B88L,
        0x23893E81L, 0xD396ACC5L, 0x0F6D6FF3L, 0x83F44239L,
        0x2E0B4482L, 0xA4842004L, 0x69C8F04AL, 0x9E1F9B5EL,
        0x21C66842L, 0xF6E96C9AL, 0x670C9C61L, 0xABD388F0L,
        0x6A51A0D2L, 0xD8542F68L, 0x960FA728L, 0xAB5133A3L,
        0x6EEF0B6CL, 0x137A3BE4L, 0xBA3BF050L, 0x7EFB2A98L,
        0xA1F1651DL, 0x39AF0176L, 0x66CA593EL, 0x82430E88L,
        0x8CEE8619L, 0x456F9FB4L, 0x7D84A5C3L, 0x3B8B5EBEL,
        0xE06F75D8L, 0x85C12073L, 0x401A449FL, 0x56C16AA6L,
        0x4ED3AA62L, 0x363F7706L, 0x1BFEDF72L, 0x429B023DL,
        0x37D0D724L, 0xD00A1248L, 0xDB0FEAD3L, 0x49F1C09BL,
        0x075372C9L, 0x80991B7BL, 0x25D479D8L, 0xF6E8DEF7L,
        0xE3FE501AL, 0xB6794C3BL, 0x976CE0BDL, 0x04C006BAL,
        0xC1A94FB6L, 0x409F60C4L, 0x5E5C9EC2L, 0x196A2463L,
        0x68FB6FAFL, 0x3E6C53B5L, 0x1339B2EBL, 0x3B52EC6FL,
        0x6DFC511FL, 0x9B30952CL, 0xCC814544L, 0xAF5EBD09L,
        0xBEE3D004L, 0xDE334AFDL, 0x660F2807L, 0x192E4BB3L,
        0xC0CBA857L, 0x45C8740FL, 0xD20B5F39L, 0xB9D3FBDBL,
        0x5579C0BDL, 0x1A60320AL, 0xD6A100C6L, 0x402C7279L,
        0x679F25FEL, 0xFB1FA3CCL, 0x8EA5E9F8L, 0xDB3222F8L,
        0x3C7516DFL, 0xFD616B15L, 0x2F501EC8L, 0xAD0552ABL,
        0x323DB5FAL, 0xFD238760L, 0x53317B48L, 0x3E00DF82L,
        0x9E5C57BBL, 0xCA6F8CA0L, 0x1A87562EL, 0xDF1769DBL,
        0xD542A8F6L, 0x287EFFC3L, 0xAC6732C6L, 0x8C4F5573L,
        0x695B27B0L, 0xBBCA58C8L, 0xE1FFA35DL, 0xB8F011A0L,
        0x10FA3D98L, 0xFD2183B8L, 0x4AFCB56CL, 0x2DD1D35BL,
        0x9A53E479L, 0xB6F84565L, 0xD28E49BCL, 0x4BFB9790L,
        0xE1DDF2DAL, 0xA4CB7E33L, 0x62FB1341L, 0xCEE4C6E8L,
        0xEF20CADAL, 0x36774C01L, 0xD07E9EFEL, 0x2BF11FB4L,
        0x95DBDA4DL, 0xAE909198L, 0xEAAD8E71L, 0x6B93D5A0L,
        0xD08ED1D0L, 0xAFC725E0L, 0x8E3C5B2FL, 0x8E7594B7L,
        0x8FF6E2FBL, 0xF2122B64L, 0x8888B812L, 0x900DF01CL,
        0x4FAD5EA0L, 0x688FC31CL, 0xD1CFF191L, 0xB3A8C1ADL,
        0x2F2F2218L, 0xBE0E1777L, 0xEA752DFEL, 0x8B021FA1L,
        0xE5A0CC0FL, 0xB56F74E8L, 0x18ACF3D6L, 0xCE89E299L,
        0xB4A84FE0L, 0xFD13E0B7L, 0x7CC43B81L, 0xD2ADA8D9L,
        0x165FA266L, 0x80957705L, 0x93CC7314L, 0x211A1477L,
        0xE6AD2065L, 0x77B5FA86L, 0xC75442F5L, 0xFB9D35CFL,
        0xEBCDAF0CL, 0x7B3E89A0L, 0xD6411BD3L, 0xAE1E7E49L,
        0x00250E2DL, 0x2071B35EL, 0x226800BBL, 0x57B8E0AFL,
        0x2464369BL, 0xF009B91EL, 0x5563911DL, 0x59DFA6AAL,
        0x78C14389L, 0xD95A537FL, 0x207D5BA2L, 0x02E5B9C5L,
        0x83260376L, 0x6295CFA9L, 0x11C81968L, 0x4E734A41L,
        0xB3472DCAL, 0x7B14A94AL, 0x1B510052L, 0x9A532915L,
        0xD60F573FL, 0xBC9BC6E4L, 0x2B60A476L, 0x81E67400L,
        0x08BA6FB5L, 0x571BE91FL, 0xF296EC6BL, 0x2A0DD915L,
        0xB6636521L, 0xE7B9F9B6L, 0xFF34052EL, 0xC5855664L,
        0x53B02D5DL, 0xA99F8FA1L, 0x08BA4799L, 0x6E85076AL   },
    {   0x4B7A70E9L, 0xB5B32944L, 0xDB75092EL, 0xC4192623L,
        0xAD6EA6B0L, 0x49A7DF7DL, 0x9CEE60B8L, 0x8FEDB266L,
        0xECAA8C71L, 0x699A17FFL, 0x5664526CL, 0xC2B19EE1L,
        0x193602A5L, 0x75094C29L, 0xA0591340L, 0xE4183A3EL,
        0x3F54989AL, 0x5B429D65L, 0x6B8FE4D6L, 0x99F73FD6L,
        0xA1D29C07L, 0xEFE830F5L, 0x4D2D38E6L, 0xF0255DC1L,
        0x4CDD2086L, 0x8470EB26L, 0x6382E9C6L, 0x021ECC5EL,
        0x09686B3FL, 0x3EBAEFC9L, 0x3C971814L, 0x6B6A70A1L,
        0x687F3584L, 0x52A0E286L, 0xB79C5305L, 0xAA500737L,
        0x3E07841CL, 0x7FDEAE5CL, 0x8E7D44ECL, 0x5716F2B8L,
        0xB03ADA37L, 0xF0500C0DL, 0xF01C1F04L, 0x0200B3FFL,
        0xAE0CF51AL, 0x3CB574B2L, 0x25837A58L, 0xDC0921BDL,
        0xD19113F9L, 0x7CA92FF6L, 0x94324773L, 0x22F54701L,
        0x3AE5E581L, 0x37C2DADCL, 0xC8B57634L, 0x9AF3DDA7L,
        0xA9446146L, 0x0FD0030EL, 0xECC8C73EL, 0xA4751E41L,
        0xE238CD99L, 0x3BEA0E2FL, 0x3280BBA1L, 0x183EB331L,
        0x4E548B38L, 0x4F6DB908L, 0x6F420D03L, 0xF60A04BFL,
        0x2CB81290L, 0x24977C79L, 0x5679B072L, 0xBCAF89AFL,
        0xDE9A771FL, 0xD9930810L, 0xB38BAE12L, 0xDCCF3F2EL,
        0x5512721FL, 0x2E6B7124L, 0x501ADDE6L, 0x9F84CD87L,
        0x7A584718L, 0x7408DA17L, 0xBC9F9ABCL, 0xE94B7D8CL,
        0xEC7AEC3AL, 0xDB851DFAL, 0x63094366L, 0xC464C3D2L,
        0xEF1C1847L, 0x3215D908L, 0xDD433B37L, 0x24C2BA16L,
        0x12A14D43L, 0x2A65C451L, 0x50940002L, 0x133AE4DDL,
        0x71DFF89EL, 0x10314E55L, 0x81AC77D6L, 0x5F11199BL,
        0x043556F1L, 0xD7A3C76BL, 0x3C11183BL, 0x5924A509L,
        0xF28FE6EDL, 0x97F1FBFAL, 0x9EBABF2CL, 0x1E153C6EL,
        0x86E34570L, 0xEAE96FB1L, 0x860E5E0AL, 0x5A3E2AB3L,
        0x771FE71CL, 0x4E3D06FAL, 0x2965DCB9L, 0x99E71D0FL,
        0x803E89D6L, 0x5266C825L, 0x2E4CC978L, 0x9C10B36AL,
        0xC6150EBAL, 0x94E2EA78L, 0xA5FC3C53L, 0x1E0A2DF4L,
        0xF2F74EA7L, 0x361D2B3DL, 0x1939260FL, 0x19C27960L,
        0x5223A708L, 0xF71312B6L, 0xEBADFE6EL, 0xEAC31F66L,
        0xE3BC4595L, 0xA67BC883L, 0xB17F37D1L, 0x018CFF28L,
        0xC332DDEFL, 0xBE6C5AA5L, 0x65582185L, 0x68AB9802L,
        0xEECEA50FL, 0xDB2F953BL, 0x2AEF7DADL, 0x5B6E2F84L,
        0x1521B628L, 0x29076170L, 0xECDD4775L, 0x619F1510L,
        0x13CCA830L, 0xEB61BD96L, 0x0334FE1EL, 0xAA0363CFL,
        0xB5735C90L, 0x4C70A239L, 0xD59E9E0BL, 0xCBAADE14L,
        0xEECC86BCL, 0x60622CA7L, 0x9CAB5CABL, 0xB2F3846EL,
        0x648B1EAFL, 0x19BDF0CAL, 0xA02369B9L, 0x655ABB50L,
        0x40685A32L, 0x3C2AB4B3L, 0x319EE9D5L, 0xC021B8F7L,
        0x9B540B19L, 0x875FA099L, 0x95F7997EL, 0x623D7DA8L,
        0xF837889AL, 0x97E32D77L, 0x11ED935FL, 0x16681281L,
        0x0E358829L, 0xC7E61FD6L, 0x96DEDFA1L, 0x7858BA99L,
        0x57F584A5L, 0x1B227263L, 0x9B83C3FFL, 0x1AC24696L,
        0xCDB30AEBL, 0x532E3054L, 0x8FD948E4L, 0x6DBC3128L,
        0x58EBF2EFL, 0x34C6FFEAL, 0xFE28ED61L, 0xEE7C3C73L,
        0x5D4A14D9L, 0xE864B7E3L, 0x42105D14L, 0x203E13E0L,
        0x45EEE2B6L, 0xA3AAABEAL, 0xDB6C4F15L, 0xFACB4FD0L,
        0xC742F442L, 0xEF6ABBB5L, 0x654F3B1DL, 0x41CD2105L,
        0xD81E799EL, 0x86854DC7L, 0xE44B476AL, 0x3D816250L,
        0xCF62A1F2L, 0x5B8D2646L, 0xFC8883A0L, 0xC1C7B6A3L,
        0x7F1524C3L, 0x69CB7492L, 0x47848A0BL, 0x5692B285L,
        0x095BBF00L, 0xAD19489DL, 0x1462B174L, 0x23820E00L,
        0x58428D2AL, 0x0C55F5EAL, 0x1DADF43EL, 0x233F7061L,
        0x3372F092L, 0x8D937E41L, 0xD65FECF1L, 0x6C223BDBL,
        0x7CDE3759L, 0xCBEE7460L, 0x4085F2A7L, 0xCE77326EL,
        0xA6078084L, 0x19F8509EL, 0xE8EFD855L, 0x61D99735L,
        0xA969A7AAL, 0xC50C06C2L, 0x5A04ABFCL, 0x800BCADCL,
        0x9E447A2EL, 0xC3453484L, 0xFDD56705L, 0x0E1E9EC9L,
        0xDB73DBD3L, 0x105588CDL, 0x675FDA79L, 0xE3674340L,
        0xC5C43465L, 0x713E38D8L, 0x3D28F89EL, 0xF16DFF20L,
        0x153E21E7L, 0x8FB03D4AL, 0xE6E39F2BL, 0xDB83ADF7L   },
    {   0xE93D5A68L, 0x948140F7L, 0xF64C261CL, 0x94692934L,
        0x411520F7L, 0x7602D4F7L, 0xBCF46B2EL, 0xD4A20068L,
        0xD4082471L, 0x3320F46AL, 0x43B7D4B7L, 0x500061AFL,
        0x1E39F62EL, 0x97244546L, 0x14214F74L, 0xBF8B8840L,
        0x4D95FC1DL, 0x96B591AFL, 0x70F4DDD3L, 0x66A02F45L,
        0xBFBC09ECL, 0x03BD9785L, 0x7FAC6DD0L, 0x31CB8504L,
        0x96EB27B3L, 0x55FD3941L, 0xDA2547E6L, 0xABCA0A9AL,
        0x28507825L, 0x530429F4L, 0x0A2C86DAL, 0xE9B66DFBL,
        0x68DC1462L, 0xD7486900L, 0x680EC0A4L, 0x27A18DEEL,
        0x4F3FFEA2L, 0xE887AD8CL, 0xB58CE006L, 0x7AF4D6B6L,
        0xAACE1E7CL, 0xD3375FECL, 0xCE78A399L, 0x406B2A42L,
        0x20FE9E35L, 0xD9F385B9L, 0xEE39D7ABL, 0x3B124E8BL,
        0x1DC9FAF7L, 0x4B6D1856L, 0x26A36631L, 0xEAE397B2L,
        0x3A6EFA74L, 0xDD5B4332L, 0x6841E7F7L, 0xCA7820FBL,
        0xFB0AF54EL, 0xD8FEB397L, 0x454056ACL, 0xBA489527L,
        0x55533A3AL, 0x20838D87L, 0xFE6BA9B7L, 0xD096954BL,
        0x55A867BCL, 0xA1159A58L, 0xCCA92963L, 0x99E1DB33L,
        0xA62A4A56L, 0x3F3125F9L, 0x5EF47E1CL, 0x9029317CL,
        0xFDF8E802L, 0x04272F70L, 0x80BB155CL, 0x05282CE3L,
        0x95C11548L, 0xE4C66D22L, 0x48C1133FL, 0xC70F86DCL,
        0x07F9C9EEL, 0x41041F0FL, 0x404779A4L, 0x5D886E17L,
        0x325F51EBL, 0xD59BC0D1L, 0xF2BCC18FL, 0x41113564L,
        0x257B7834L, 0x602A9C60L, 0xDFF8E8A3L, 0x1F636C1BL,
        0x0E12B4C2L, 0x02E1329EL, 0xAF664FD1L, 0xCAD18115L,
        0x6B2395E0L, 0x333E92E1L, 0x3B240B62L, 0xEEBEB922L,
        0x85B2A20EL, 0xE6BA0D99L, 0xDE720C8CL, 0x2DA2F728L,
        0xD0127845L, 0x95B794FDL, 0x647D0862L, 0xE7CCF5F0L,
        0x5449A36FL, 0x877D48FAL, 0xC39DFD27L, 0xF33E8D1EL,
        0x0A476341L, 0x992EFF74L, 0x3A6F6EABL, 0xF4F8FD37L,
        0xA812DC60L, 0xA1EBDDF8L, 0x991BE14CL, 0xDB6E6B0DL,
        0xC67B5510L, 0x6D672C37L, 0x2765D43BL, 0xDCD0E804L,
        0xF1290DC7L, 0xCC00FFA3L, 0xB5390F92L, 0x690FED0BL,
        0x667B9FFBL, 0xCEDB7D9CL, 0xA091CF0BL, 0xD9155EA3L,
        0xBB132F88L, 0x515BAD24L, 0x7B9479BFL, 0x763BD6EBL,
        0x37392EB3L, 0xCC115979L, 0x8026E297L, 0xF42E312DL,
        0x6842ADA7L, 0xC66A2B3BL, 0x12754CCCL, 0x782EF11CL,
        0x6A124237L, 0xB79251E7L, 0x06A1BBE6L, 0x4BFB6350L,
        0x1A6B1018L, 0x11CAEDFAL, 0x3D25BDD8L, 0xE2E1C3C9L,
        0x44421659L, 0x0A121386L, 0xD90CEC6EL, 0xD5ABEA2AL,
        0x64AF674EL, 0xDA86A85FL, 0xBEBFE988L, 0x64E4C3FEL,
        0x9DBC8057L, 0xF0F7C086L, 0x60787BF8L, 0x6003604DL,
        0xD1FD8346L, 0xF6381FB0L, 0x7745AE04L, 0xD736FCCCL,
        0x83426B33L, 0xF01EAB71L, 0xB0804187L, 0x3C005E5FL,
        0x77A057BEL, 0xBDE8AE24L, 0x55464299L, 0xBF582E61L,
        0x4E58F48FL, 0xF2DDFDA2L, 0xF474EF38L, 0x8789BDC2L,
        0x5366F9C3L, 0xC8B38E74L, 0xB475F255L, 0x46FCD9B9L,
        0x7AEB2661L, 0x8B1DDF84L, 0x846A0E79L, 0x915F95E2L,
        0x466E598EL, 0x20B45770L, 0x8CD55591L, 0xC902DE4CL,
        0xB90BACE1L, 0xBB8205D0L, 0x11A86248L, 0x7574A99EL,
        0xB77F19B6L, 0xE0A9DC09L, 0x662D09A1L, 0xC4324633L,
        0xE85A1F02L, 0x09F0BE8CL, 0x4A99A025L, 0x1D6EFE10L,
        0x1AB93D1DL, 0x0BA5A4DFL, 0xA186F20FL, 0x2868F169L,
        0xDCB7DA83L, 0x573906FEL, 0xA1E2CE9BL, 0x4FCD7F52L,
        0x50115E01L, 0xA70683FAL, 0xA002B5C4L, 0x0DE6D027L,
        0x9AF88C27L, 0x773F8641L, 0xC3604C06L, 0x61A806B5L,
        0xF0177A28L, 0xC0F586E0L, 0x006058AAL, 0x30DC7D62L,
        0x11E69ED7L, 0x2338EA63L, 0x53C2DD94L, 0xC2C21634L,
        0xBBCBEE56L, 0x90BCB6DEL, 0xEBFC7DA1L, 0xCE591D76L,
        0x6F05E409L, 0x4B7C0188L, 0x39720A3DL, 0x7C927C24L,
        0x86E3725FL, 0x724D9DB9L, 0x1AC15BB4L, 0xD39EB8FCL,
        0xED545578L, 0x08FCA5B5L, 0xD83D7CD3L, 0x4DAD0FC4L,
        0x1E50EF5EL, 0xB161E6F8L, 0xA28514D9L, 0x6C51133CL,
        0x6FD5C7E7L, 0x56E14EC4L, 0x362ABFCEL, 0xDDC6C837L,
        0xD79A3234L, 0x92638212L, 0x670EFA8EL, 0x406000E0L  },
    {   0x3A39CE37L, 0xD3FAF5CFL, 0xABC27737L, 0x5AC52D1BL,
        0x5CB0679EL, 0x4FA33742L, 0xD3822740L, 0x99BC9BBEL,
        0xD5118E9DL, 0xBF0F7315L, 0xD62D1C7EL, 0xC700C47BL,
        0xB78C1B6BL, 0x21A19045L, 0xB26EB1BEL, 0x6A366EB4L,
        0x5748AB2FL, 0xBC946E79L, 0xC6A376D2L, 0x6549C2C8L,
        0x530FF8EEL, 0x468DDE7DL, 0xD5730A1DL, 0x4CD04DC6L,
        0x2939BBDBL, 0xA9BA4650L, 0xAC9526E8L, 0xBE5EE304L,
        0xA1FAD5F0L, 0x6A2D519AL, 0x63EF8CE2L, 0x9A86EE22L,
        0xC089C2B8L, 0x43242EF6L, 0xA51E03AAL, 0x9CF2D0A4L,
        0x83C061BAL, 0x9BE96A4DL, 0x8FE51550L, 0xBA645BD6L,
        0x2826A2F9L, 0xA73A3AE1L, 0x4BA99586L, 0xEF5562E9L,
        0xC72FEFD3L, 0xF752F7DAL, 0x3F046F69L, 0x77FA0A59L,
        0x80E4A915L, 0x87B08601L, 0x9B09E6ADL, 0x3B3EE593L,
        0xE990FD5AL, 0x9E34D797L, 0x2CF0B7D9L, 0x022B8B51L,
        0x96D5AC3AL, 0x017DA67DL, 0xD1CF3ED6L, 0x7C7D2D28L,
        0x1F9F25CFL, 0xADF2B89BL, 0x5AD6B472L, 0x5A88F54CL,
        0xE029AC71L, 0xE019A5E6L, 0x47B0ACFDL, 0xED93FA9BL,
        0xE8D3C48DL, 0x283B57CCL, 0xF8D56629L, 0x79132E28L,
        0x785F0191L, 0xED756055L, 0xF7960E44L, 0xE3D35E8CL,
        0x15056DD4L, 0x88F46DBAL, 0x03A16125L, 0x0564F0BDL,
        0xC3EB9E15L, 0x3C9057A2L, 0x97271AECL, 0xA93A072AL,
        0x1B3F6D9BL, 0x1E6321F5L, 0xF59C66FBL, 0x26DCF319L,
        0x7533D928L, 0xB155FDF5L, 0x03563482L, 0x8ABA3CBBL,
        0x28517711L, 0xC20AD9F8L, 0xABCC5167L, 0xCCAD925FL,
        0x4DE81751L, 0x3830DC8EL, 0x379D5862L, 0x9320F991L,
        0xEA7A90C2L, 0xFB3E7BCEL, 0x5121CE64L, 0x774FBE32L,
        0xA8B6E37EL, 0xC3293D46L, 0x48DE5369L, 0x6413E680L,
        0xA2AE0810L, 0xDD6DB224L, 0x69852DFDL, 0x09072166L,
        0xB39A460AL, 0x6445C0DDL, 0x586CDECFL, 0x1C20C8AEL,
        0x5BBEF7DDL, 0x1B588D40L, 0xCCD2017FL, 0x6BB4E3BBL,
        0xDDA26A7EL, 0x3A59FF45L, 0x3E350A44L, 0xBCB4CDD5L,
        0x72EACEA8L, 0xFA6484BBL, 0x8D6612AEL, 0xBF3C6F47L,
        0xD29BE463L, 0x542F5D9EL, 0xAEC2771BL, 0xF64E6370L,
        0x740E0D8DL, 0xE75B1357L, 0xF8721671L, 0xAF537D5DL,
        0x4040CB08L, 0x4EB4E2CCL, 0x34D2466AL, 0x0115AF84L,
        0xE1B00428L, 0x95983A1DL, 0x06B89FB4L, 0xCE6EA048L,
        0x6F3F3B82L, 0x3520AB82L, 0x011A1D4BL, 0x277227F8L,
        0x611560B1L, 0xE7933FDCL, 0xBB3A792BL, 0x344525BDL,
        0xA08839E1L, 0x51CE794BL, 0x2F32C9B7L, 0xA01FBAC9L,
        0xE01CC87EL, 0xBCC7D1F6L, 0xCF0111C3L, 0xA1E8AAC7L,
        0x1A908749L, 0xD44FBD9AL, 0xD0DADECBL, 0xD50ADA38L,
        0x0339C32AL, 0xC6913667L, 0x8DF9317CL, 0xE0B12B4FL,
        0xF79E59B7L, 0x43F5BB3AL, 0xF2D519FFL, 0x27D9459CL,
        0xBF97222CL, 0x15E6FC2AL, 0x0F91FC71L, 0x9B941525L,
        0xFAE59361L, 0xCEB69CEBL, 0xC2A86459L, 0x12BAA8D1L,
        0xB6C1075EL, 0xE3056A0CL, 0x10D25065L, 0xCB03A442L,
        0xE0EC6E0EL, 0x1698DB3BL, 0x4C98A0BEL, 0x3278E964L,
        0x9F1F9532L, 0xE0D392DFL, 0xD3A0342BL, 0x8971F21EL,
        0x1B0A7441L, 0x4BA3348CL, 0xC5BE7120L, 0xC37632D8L,
        0xDF359F8DL, 0x9B992F2EL, 0xE60B6F47L, 0x0FE3F11DL,
        0xE54CDA54L, 0x1EDAD891L, 0xCE6279CFL, 0xCD3E7E6FL,
        0x1618B166L, 0xFD2C1D05L, 0x848FD2C5L, 0xF6FB2299L,
        0xF523F357L, 0xA6327623L, 0x93A83531L, 0x56CCCD02L,
        0xACF08162L, 0x5A75EBB5L, 0x6E163697L, 0x88D273CCL,
        0xDE966292L, 0x81B949D0L, 0x4C50901BL, 0x71C65614L,
        0xE6C6C7BDL, 0x327A140AL, 0x45E1D006L, 0xC3F27B9AL,
        0xC9AA53FDL, 0x62A80F00L, 0xBB25BFE2L, 0x35BDD2F6L,
        0x71126905L, 0xB2040222L, 0xB6CBCF7CL, 0xCD769C2BL,
        0x53113EC0L, 0x1640E3D3L, 0x38ABBD60L, 0x2547ADF0L,
        0xBA38209CL, 0xF746CE76L, 0x77AFA1C5L, 0x20756060L,
        0x85CBFE4EL, 0x8AE88DD8L, 0x7AAAF9B0L, 0x4CF9AA7EL,
        0x1948C25CL, 0x02FB8A8CL, 0x01C36AE4L, 0xD6EBE1F9L,
        0x90D4F869L, 0xA65CDEA0L, 0x3F09252DL, 0xC208E69FL,
        0xB74E6132L, 0xCE77E25BL, 0x578FDFE3L, 0x3AC372E6L  }
};

unsigned long F_F(BLOWFISH_CTX *ctx, unsigned long x)
{
   unsigned short a, b, c, d;
   unsigned long  y;

   d = x & 0x00FF;
   x >>= 8;
   c = x & 0x00FF;
   x >>= 8;
   b = x & 0x00FF;
   x >>= 8;
   a = x & 0x00FF;
   y = ctx->S[0][a] + ctx->S[1][b];
   y = y ^ ctx->S[2][c];
   y = y + ctx->S[3][d];

   return y;
}

void Blowfish_Encrypt(BLOWFISH_CTX *ctx, unsigned long *xl, unsigned long *xr)
{
  unsigned long  Xl;
  unsigned long  Xr;
  unsigned long  temp;
  short       i;

  Xl = *xl;
  Xr = *xr;

  for (i = 0; i < N; ++i) {
    Xl = Xl ^ ctx->P[i];
    Xr = F_F(ctx, Xl) ^ Xr;

    temp = Xl;
    Xl = Xr;
    Xr = temp;
  }

  temp = Xl;
  Xl = Xr;
  Xr = temp;

  Xr = Xr ^ ctx->P[N];
  Xl = Xl ^ ctx->P[N + 1];

  *xl = Xl;
  *xr = Xr;
}

void Blowfish_Decrypt(BLOWFISH_CTX *ctx, unsigned long *xl, unsigned long *xr)
{
  unsigned long  Xl;
  unsigned long  Xr;
  unsigned long  temp;
  short       i;

  Xl = *xl;
  Xr = *xr;

  for (i = N + 1; i > 1; --i) {
    Xl = Xl ^ ctx->P[i];
    Xr = F_F(ctx, Xl) ^ Xr;

    /* Exchange Xl and Xr */
    temp = Xl;
    Xl = Xr;
    Xr = temp;
  }

  /* Exchange Xl and Xr */
  temp = Xl;
  Xl = Xr;
  Xr = temp;

  Xr = Xr ^ ctx->P[1];
  Xl = Xl ^ ctx->P[0];

  *xl = Xl;
  *xr = Xr;
}

void Blowfish_Init(BLOWFISH_CTX *ctx, unsigned char *key, int keyLen)
{
  int i, j, k;
  unsigned long data, datal, datar;

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 256; j++)
      ctx->S[i][j] = ORIG_S[i][j];
  }

  j = 0;
  for (i = 0; i < N + 2; ++i) {
    data = 0x00000000;
    for (k = 0; k < 4; ++k) {
      data = (data << 8) | key[j];
      j = j + 1;
      if (j >= keyLen)
        j = 0;
    }
    ctx->P[i] = ORIG_P[i] ^ data;
  }

  datal = 0x00000000;
  datar = 0x00000000;

  for (i = 0; i < N + 2; i += 2) {
    Blowfish_Encrypt(ctx, &datal, &datar);
    ctx->P[i] = datal;
    ctx->P[i + 1] = datar;
  }

  for (i = 0; i < 4; ++i) {
    for (j = 0; j < 256; j += 2) {
      Blowfish_Encrypt(ctx, &datal, &datar);
      ctx->S[i][j] = datal;
      ctx->S[i][j + 1] = datar;
    }
  }
}

int Blowfish_Test(BLOWFISH_CTX *ctx)
{
  unsigned long L = 1, R = 2;

  Blowfish_Init (ctx, (unsigned char*)"TESTKEY", 7);
  Blowfish_Encrypt(ctx, &L, &R);
  if (L != 0xDF333FD2L || R != 0x30A71BB4L)
    return (-1);
  Blowfish_Decrypt(ctx, &L, &R);
  if (L != 1 || R != 2)
    return (-1);
  return (0);
}
//---------------------------------------------------------------------------
// Base Xor Encrypt
//---------------------------------------------------------------------------
void BaseXorAdd(unsigned char *szBuffer, int ulFileLen, char *szPassword, int iPasswordLen)
{
  char *szTempStr = szPassword;
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
//---------------------------------------------------------------------------
void BaseXorSub(unsigned char *szBuffer, int ulFileLen, char *szPassword, int iPasswordLen)
{
  char *szTempStr = szPassword;
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
