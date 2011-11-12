//---------------------------------------------------------------------------

#include <vcl.h>
#include <vector>
#include <openssl/crypto.h>
#include <openssl/x509.h>
#include <openssl/pem.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "AuthCrypt.h"
#include "SRP6Auth.h"
#pragma hdrstop

#pragma link "ws2_32.lib"

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

#pragma resource "*.dfm"

using namespace std;
TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
bool	CheckEqual(BigNumber *a, BigNumber *b)
{
	string aHex = a->AsHexStr();
	string bHex = b->AsHexStr();
	if(aHex == bHex)
	{
		return	true;
	}
	return false;
}


void __fastcall TForm1::btTestClick(TObject *Sender)
{
//1. SRP6Client::CalcA
//2. SRP6Server::CalcKey
//3. SRP6Client::CalcKey
//4. SRP6Client::GetResultM
//5. SRP6Server::CheckClientAuth
//6. SRP6Client::CheckServerAuth
	SRP6Client client;
	SRP6Server server;
	BigNumber A, clientK, serverK, s, B, M1, M2;
	client.CalcA(&A);
	string username = "eggxp";
	server.CalcKey(username, username, A, &s, &B, &serverK);
	client.CalcKey(username, username, s, B, &clientK);
//	if(CheckEqual(&clientK, &serverK))
//	{
//		ShowMessage("OK!");
//	}
	uint8 clientM[20];
	client.GetResultM(username, clientM);
	BigNumber serverM2;
	if(server.CheckClientAuth(username, clientM, &serverM2))
	{
		ShowMessage("server OK");
	}
	if(client.CheckServerAuth(username, serverM2.AsByteArray()))
	{
		ShowMessage("client OK");
	}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::btClientCalcClick(TObject *Sender)
{
	SRP6Client client;
	BigNumber clientK, s, B;
	s.SetHexStr(AnsiString(edtClients->Text).c_str());
	B.SetHexStr(AnsiString(edtClientB->Text).c_str());
	client.CalcKey(AnsiString(labUserName->Text).c_str(), AnsiString(labPsw->Text).c_str(), s, B, &clientK);
	edtClientCalcResult->Text = clientK.AsHexStr();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
	AuthCrypt m_AuthCrypt;
	BigNumber K;
	K.SetHexStr("124578232E");
	uint8 ServerEncryptionKey[SEED_KEY_SIZE] = { 0x22, 0xBE, 0xE5, 0xCF, 0xBB, 0x07, 0x64, 0xD9, 0x00, 0x45, 0x1B, 0xD0, 0x24, 0xB8, 0xD5, 0x45 };
	uint8 ServerDecryptionKey[SEED_KEY_SIZE] = { 0xF4, 0x66, 0x31, 0x59, 0xFC, 0x83, 0x6E, 0x31, 0x31, 0x02, 0x51, 0xD5, 0x44, 0x31, 0x67, 0x98 };
	m_AuthCrypt.Init(&K, ServerEncryptionKey, ServerDecryptionKey);
	vector<BYTE>	data;
	data.resize(5);
	for(DWORD i=0; i<data.size(); i++)
	{
		data[i] = i;
	}
	m_AuthCrypt.ServerToClientEncrypt(&data[0], data.size());
	m_AuthCrypt.ServerToClientDecrypt(&data[0], data.size()-1);
	m_AuthCrypt.ServerToClientDecrypt(&data[data.size()-1], 1);
	for(DWORD i=0; i<data.size(); i++)
	{
		ShowMessage(int(data[i]));
	}
}
//---------------------------------------------------------------------------


