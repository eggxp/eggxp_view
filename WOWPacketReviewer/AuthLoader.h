//---------------------------------------------------------------------------

#ifndef AuthLoaderH
#define AuthLoaderH
//---------------------------------------------------------------------------
#include <vcl.h>

void    LoadAuthDll();

bool	InitSeed(int connectionIndex, int build, AnsiString sessionkey);

void	DecryptServerToClient(int connectionIndex, unsigned char *lpdata, int len);
void	DecryptServerToClientEnd(int connectionIndex);
void	DecryptClientToServer(int connectionIndex, unsigned char *lpdata, int len);

void	EncryptServerToClient(int connectionIndex, unsigned char *lpdata, int len);
void	EncryptClientToServer(int connectionIndex, unsigned char *lpdata, int len);

bool	InitServerToClientSeed(int build, AnsiString sessionkey);
#endif
