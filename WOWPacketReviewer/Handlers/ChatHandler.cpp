//---------------------------------------------------------------------------


#pragma hdrstop

#include "ChatHandler.h"
#include "GameWorld.h"
#include "SharedDefine.h"

//---------------------------------------------------------------------------

#pragma package(smart_init)

ChatHandler::ChatHandler(GameWorld * gameWorld)
{
    m_GameWorld = gameWorld;
	REG_HANDLER(CMSG_MESSAGECHAT)
	REG_HANDLER(SMSG_MESSAGECHAT)
}

ChatHandler::~ChatHandler()
{
}

void    ChatHandler::Handler_CMSG_MESSAGECHAT(WOWPackage * packet)
{
	int pos = 0;
	READ_DWORD(type)
	packet->GetComment()->Add(GetChatMsgName(type));
	READ_DWORD(lang)
	packet->GetComment()->Add(GetLanguageName(lang));
    switch(type)
    {
        case CHAT_MSG_SAY:
        case CHAT_MSG_EMOTE:
		case CHAT_MSG_YELL:
		{
			READ_STRING(msg)
			break;
		}
		case CHAT_MSG_WHISPER:
		{
			READ_STRING(to)
			READ_STRING(msg)
			break;
		}
		case CHAT_MSG_PARTY:
		case CHAT_MSG_PARTY_LEADER:
		{
			READ_STRING(msg)
			break;
		}
		case CHAT_MSG_GUILD:
		{
			READ_STRING(msg)
			break;
		}
		case CHAT_MSG_OFFICER:
		{
			READ_STRING(msg)
			break;
		}
		case CHAT_MSG_RAID:
		{
			READ_STRING(msg)
			break;
		}
		case CHAT_MSG_RAID_LEADER:
		{
			READ_STRING(msg)
			break;
		}
		case CHAT_MSG_RAID_WARNING:
		{
			READ_STRING(msg)
			break;
		}
		case CHAT_MSG_BATTLEGROUND:
		{
			READ_STRING(msg)
			break;
		}
		case CHAT_MSG_BATTLEGROUND_LEADER:
		{
			READ_STRING(msg)
			break;
		}
		case CHAT_MSG_CHANNEL:
		{
			READ_STRING(channel)
			READ_STRING(msg)
			break;
		}
		case CHAT_MSG_AFK:
		{
			READ_STRING(msg)
			break;
		}
		case CHAT_MSG_DND:
		{
			READ_STRING(msg)
			break;
		}
	}
	READ_FINISH
}

void    ChatHandler::Handler_SMSG_MESSAGECHAT(WOWPackage * packet)
{
    int pos = 0;
    READ_TYPE(int, type, ReadBYTE)
    packet->GetComment()->Add(GetChatMsgName(type));
    READ_TYPE(int, language, ReadDWORD)
    packet->GetComment()->Add(GetLanguageName(language));
    switch(type)
    {
        case CHAT_MSG_MONSTER_SAY:
        case CHAT_MSG_MONSTER_PARTY:
        case CHAT_MSG_MONSTER_YELL:
        case CHAT_MSG_MONSTER_WHISPER:
        case CHAT_MSG_MONSTER_EMOTE:
        case CHAT_MSG_RAID_BOSS_WHISPER:
        case CHAT_MSG_RAID_BOSS_EMOTE:
        case CHAT_MSG_BATTLENET:
        {
            READ_UINT64(guid)
            READ_DWORD(zero)
            READ_DWORD(name_len)
            READ_UTF8_STRING(name)
            READ_UINT64(listener_guid)
            if(listener_guid && !IS_PLAYER_GUID(listener_guid))
            {
                READ_DWORD(listener_name_len)
                READ_UTF8_STRING(listener_name)
            }
            READ_DWORD(message_len)
            READ_UTF8_STRING(message)
            READ_BYTE(zero1)
            return;
        }
    }

    READ_UINT64(guid)
    READ_DWORD(unk)

    if (type == CHAT_MSG_CHANNEL)
    {
        READ_UTF8_STRING(channel_name)
    }

    READ_UINT64(target_guid)
    READ_DWORD(message_length)
    READ_UTF8_STRING(message)
    READ_BYTE(chat_tag)
    READ_FINISH
}
