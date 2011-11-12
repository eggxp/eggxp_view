// ---------------------------------------------------------------------------

#ifndef SRP6AuthH
#define SRP6AuthH
// ---------------------------------------------------------------------------
#include <vcl.h>
#include <string>
#include "BigNumber.h"
using namespace std;

//1. SRP6Client::CalcA
//2. SRP6Server::CalcKey
//3. SRP6Client::CalcKey
//4. SRP6Client::GetResultM
//5. SRP6Server::CheckClientAuth
//6. SRP6Client::CheckServerAuth

class SRP6Client
{
private:
	BigNumber a, A, B, x, u;
	BigNumber g, N, s, S, K, M, M2;

public:
	SRP6Client();
	~SRP6Client();

	// size = 32
	bool CalcA(BigNumber *output_strA);
	bool CalcKey(string username, string password, BigNumber &strs, BigNumber &strB, BigNumber *output_key);
	// size = 20
	bool GetResultM(string username, uint8 *output_M1);
	// size = 20
	bool CheckServerAuth(string username, uint8 *serverM2);
//	BigNumber *GetS(){return &S;}
//	BigNumber *Gets(){return &s;}
	void Clear();
};

////////////////////////////////////////////////////////////////////////////////

class SRP6Server
{
private:
	BigNumber N, s, S, g, v, x, u;
	BigNumber b, B;
	BigNumber K;
	BigNumber A, M;

	bool _SetVSFields(string &username, string &password);

public:
	SRP6Server();
	~SRP6Server();

	bool CalcKey(string username, string password, BigNumber &strA, BigNumber *output_s, BigNumber *output_B, BigNumber *output_key);
	// size = 20
	bool CheckClientAuth(string username, uint8 *M1, BigNumber *output_M2);
//	BigNumber *GetS(){return &S;}
//	BigNumber *Gets(){return &s;}
	void Clear();
};
#endif
