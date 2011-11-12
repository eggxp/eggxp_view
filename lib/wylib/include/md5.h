#ifndef MD5H
  #define MD5H
#define nMD5Size        16

class CMD5Checksum
{
public:
	//constructor/destructor
	CMD5Checksum();
	virtual ~CMD5Checksum() {};
	//interface functions for the RSA MD5 calculation
        LPSTR GetMD5(BYTE* pBuf, UINT nLength);
        void Init(void);

protected:
	//RSA MD5 implementation
	void Transform(BYTE Block[64]);
	void Update(BYTE* Input, ULONG nInputLen);
        LPBYTE Final();
	inline DWORD RotateLeft(DWORD x, int n);
	inline void FF( DWORD& A, DWORD B, DWORD C, DWORD D, DWORD X, DWORD S, DWORD T);
	inline void GG( DWORD& A, DWORD B, DWORD C, DWORD D, DWORD X, DWORD S, DWORD T);
	inline void HH( DWORD& A, DWORD B, DWORD C, DWORD D, DWORD X, DWORD S, DWORD T);
	inline void II( DWORD& A, DWORD B, DWORD C, DWORD D, DWORD X, DWORD S, DWORD T);

	//utility functions
	void DWordToByte(BYTE* Output, DWORD* Input, UINT nLength);
	void ByteToDWord(DWORD* Output, BYTE* Input, UINT nLength);

private:
	BYTE  m_lpszBuffer[64];		//input buffer
	ULONG m_nCount[2];			//number of bits, modulo 2^64 (lsb first)
	ULONG m_lMD5[4];			//MD5 checksum
	unsigned char lpszMD5[ nMD5Size ];
        char lpMD5[ nMD5Size * 2 + 1];
};
#endif
