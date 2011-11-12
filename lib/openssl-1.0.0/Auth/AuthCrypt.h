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

#ifndef AUTHCRYPTH
#define AUTHCRYPTH

#include <Common.h>
#include "HmacSha1.h"
#include "SARC4.h"

class BigNumber;

class AuthCrypt
{
    public:
        AuthCrypt();
        ~AuthCrypt();

		void Init(BigNumber *K, uint8 *ServerEncryptionKey, uint8 *ServerDecryptionKey);
		void InitServerToClient(BigNumber *K, uint8 *ServerEncryptionKey);
		void InitClientToServer(BigNumber *K, uint8 *ServerDecryptionKey);
        void ClientToServerDecrypt(uint8 *, size_t);
        void ServerToClientEncrypt(uint8 *, size_t);

		void ServerToClientDecrypt(uint8 *, size_t);
		void ServerToClientDecryptOver();
		void ClientToServerEncrypt(uint8 *, size_t);

        bool IsInitialized() { return _initialized; }

    private:
        SARC4 _clientDecrypt;
        SARC4 _serverEncrypt;
		SARC4 _clientEncrypt;
		SARC4 _serverDecrypt;
        bool _initialized;
};
#endif
