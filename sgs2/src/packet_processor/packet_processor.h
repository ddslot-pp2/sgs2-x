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
void handle_CS_PING(std::shared_ptr<server_session> session, const GAME::CS_PING& read);
void handle_CS_SYNC_FIELD(std::shared_ptr<server_session> session, const GAME::CS_SYNC_FIELD& read);
void handle_CS_NOTI_MOVE(std::shared_ptr<server_session> session, const GAME::CS_NOTI_MOVE& read);
void handle_CS_FIRE(std::shared_ptr<server_session> session, const GAME::CS_FIRE& read);


void register_handlers();
void handle_packet(std::shared_ptr<server_session> session, buf_ptr buffer, int size);



#endif
