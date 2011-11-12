/*
使用API HOOK对代码页函数进行挂钩,以保证BCB6以后的C++ Builder版本对DFM窗体文件控件的简体->繁体转换能正常工作

//作者:游勇鹏
//最后更新日期: 2004.12

使用举例:


*/

//---------------------------------------------------------------------------
#ifndef UnicodeSupportH
#define UnicodeSupportH
//---------------------------------------------------------------------------
typedef int (WINAPI *WIDECHARTOMULTIBYTE)(UINT CodePage, DWORD dwFlags,
                                          LPCWSTR lpWideCharStr, int cchWideChar,
                                          LPSTR lpMultiByteStr, int cchMultiByte,
                                          LPCSTR lpDefaultChar, LPBOOL lpUsedDefaultChar);
//---------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

bool InitSimplifiedChinese(void);
bool DeInitSimplifiedChinese(void);

#ifdef __cplusplus
}
#endif //__cplusplus
//---------------------------------------------------------------------------
#endif
