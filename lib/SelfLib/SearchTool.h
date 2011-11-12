//---------------------------------------------------------------------------
#ifndef SearchToolH
#define SearchToolH

//---------------------------------------------------------------------------
#define MAX_BUFFER             0x2000
#define SINGLE_WILDCARD        0x0100         // '??' Sign
#define COMPLEX_WILDCARD       0x0101         // '%%' Sign
//---------------------------------------------------------------------------
class CSearchEngine
{
private:
  DWORD                         m_nPatternLength;
  WORD                          m_wWildcardPattern[MAX_BUFFER];
  BYTE                          m_cNormalPattern[MAX_BUFFER];

private:
  static WORD WINAPI            HexToInt(WORD wCh);
  static DWORD WINAPI           WildcardSearch(LPVOID pBuffer, DWORD nLength, LPWORD pwWildcardPattern, DWORD nPatternLength, DWORD &nResultLength);
  static DWORD WINAPI           BinarySearch(LPVOID pBuffer, DWORD nLength, LPVOID pPattern, DWORD nPatternLength);
  BOOL WINAPI                   WildcardPatternPreprocess(LPSTR pWildcardPattern);
  BOOL WINAPI                   NormalPatternPreprocess(LPSTR pPattern);

public:
                                CSearchEngine(VOID);
                                ~CSearchEngine(VOID);

  LPVOID WINAPI                 WildcardSearch(LPVOID pBuffer, DWORD nLength, LPSTR pWildcardPattern, LPDWORD pResultLength = NULL);
  LPVOID WINAPI                 NormalSearch(LPVOID pBuffer, DWORD nLength, LPVOID pPattern, DWORD nPatternLength);
  LPVOID WINAPI                 NormalSearch(LPVOID pBuffer, DWORD nLength, LPSTR pPattern);
};
//---------------------------------------------------------------------------
#endif
