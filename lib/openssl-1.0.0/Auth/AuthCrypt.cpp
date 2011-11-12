/*
 * Copyright (C) 2005-2010 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "AuthCrypt.h"
//#include "Log.h"
#include "BigNumber.h"

AuthCrypt::AuthCrypt() : _clientDecrypt(SHA_DIGEST_LENGTH), _serverEncrypt(SHA_DIGEST_LENGTH), _clientEncrypt(SHA_DIGEST_LENGTH),  _serverDecrypt(SHA_DIGEST_LENGTH)
{
    _initialized = false;
}

AuthCrypt::~AuthCrypt()
{

}

void AuthCrypt::InitServerToClient(BigNumber *K, uint8 *ServerEncryptionKey)
{
	HMACSHA1 serverEncryptHmac(SEED_KEY_SIZE, (uint8*)ServerEncryptionKey);

	uint8 *encryptHash = serverEncryptHmac.ComputeHash(K);

    _serverEncrypt.Init(encryptHash);
	_serverDecrypt.Init(encryptHash);

    uint8 syncBuf[1024];
    memset(syncBuf, 0, 1024);
	_serverEncrypt.UpdateData(1024, syncBuf);
	memset(syncBuf, 0, 1024);
	_serverDecrypt.UpdateData(1024, syncBuf);
}

void AuthCrypt::InitClientToServer(BigNumber *K, uint8 *ServerDecryptionKey)
{
	HMACSHA1 clientDecryptHmac(SEED_KEY_SIZE, (uint8*)ServerDecryptionKey);

	uint8 *decryptHash = clientDecryptHmac.ComputeHash(K);

    _clientDecrypt.Init(decryptHash);

	_clientEncrypt.Init(decryptHash);
    //SARC4 _clientEncrypt(decryptHash);

	uint8 syncBuf[1024];
	memset(syncBuf, 0, 1024);
	_clientEncrypt.UpdateData(1024, syncBuf);
	memset(syncBuf, 0, 1024);
	_clientDecrypt.UpdateData(1024, syncBuf);
}

void AuthCrypt::Init(BigNumber *K, uint8 *ServerEncryptionKey, uint8 *ServerDecryptionKey)
{
	InitClientToServer(K, ServerDecryptionKey);
	InitServerToClient(K, ServerEncryptionKey);
	_initialized = true;
}

void AuthCrypt::ClientToServerDecrypt(uint8 *data, size_t len)
{
    if (!_initialized)
        return;

    _clientDecrypt.UpdateData(len, data);
}

void AuthCrypt::ServerToClientEncrypt(uint8 *data, size_t len)
{
    if (!_initialized)
        return;

    _serverEncrypt.UpdateData(len, data);
}

void AuthCrypt::ServerToClientDecrypt(uint8 *data, size_t len)
{
	if (!_initialized)
		return;

	_serverDecrypt.UpdateDataNoFinal(len, data);
}

void AuthCrypt::ServerToClientDecryptOver()
{
	if (!_initialized)
		return;

	_serverDecrypt.UpdateDataFinal();
}

void AuthCrypt::ClientToServerEncrypt(uint8 *data, size_t len)
{
	if (!_initialized)
		return;

	_clientEncrypt.UpdateData(len, data);
}