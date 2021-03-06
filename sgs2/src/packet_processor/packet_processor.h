#ifndef __PACKET_PROCESSOR_H
#define __PACKET_PROCESSOR_H

#include <memory>
#include "../../../network/src/io_helper.h"

#include "packet/LOBBY.pb.h"
#include "packet/GAME.pb.h"

using buf_ptr = std::shared_ptr<network::packet_buffer_type>;

class server_session;

void handle_CS_LOG_IN(std::shared_ptr<server_session> session, const LOBBY::CS_LOG_IN& read);
void handle_CS_FIELD_LIST(std::shared_ptr<server_session> session, const LOBBY::CS_FIELD_LIST& read);
void handle_CS_ENTER_FIELD(std::shared_ptr<server_session> session, const LOBBY::CS_ENTER_FIELD& read);
void handle_CS_LEAVE_FIELD(std::shared_ptr<server_session> session, const LOBBY::CS_LEAVE_FIELD& read);
void handle_CS_PURCHASE_CHARACTER(std::shared_ptr<server_session> session, const LOBBY::CS_PURCHASE_CHARACTER& read);
void handle_CS_CHARACTER_INFO(std::shared_ptr<server_session> session, const LOBBY::CS_CHARACTER_INFO& read);
void handle_CS_MY_INFO(std::shared_ptr<server_session> session, const LOBBY::CS_MY_INFO& read);
void handle_CS_MY_CHARACTER_INFO(std::shared_ptr<server_session> session, const LOBBY::CS_MY_CHARACTER_INFO& read);
void handle_CS_CHARACTER_UPGRADE(std::shared_ptr<server_session> session, const LOBBY::CS_CHARACTER_UPGRADE& read);
void handle_CS_CHARACTER_SELECT(std::shared_ptr<server_session> session, const LOBBY::CS_CHARACTER_SELECT& read);
void handle_CS_PING(std::shared_ptr<server_session> session, const GAME::CS_PING& read);
void handle_CS_SYNC_FIELD(std::shared_ptr<server_session> session, const GAME::CS_SYNC_FIELD& read);
void handle_CS_NOTI_MOVE(std::shared_ptr<server_session> session, const GAME::CS_NOTI_MOVE& read);
void handle_CS_FIRE(std::shared_ptr<server_session> session, const GAME::CS_FIRE& read);
void handle_CS_RESPAWN_CHARACTER(std::shared_ptr<server_session> session, const GAME::CS_RESPAWN_CHARACTER& read);
void handle_CS_ENHANCE_BUFF(std::shared_ptr<server_session> session, const GAME::CS_ENHANCE_BUFF& read);


void register_handlers();
void handle_packet(std::shared_ptr<server_session> session, buf_ptr buffer, int size);



#endif
