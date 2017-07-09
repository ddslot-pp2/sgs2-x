#ifndef __SERVER_SESSION_H
#define __SERVER_SESSION_H

#include "session/session.h"
#include "../predeclare.h"
#include "../object/character.h"

using boost::asio::ip::tcp;

using character_ptr = std::shared_ptr<character>;
using character_weak_ptr = std::weak_ptr<character>;

class server_session : public network::session
{
public:

    explicit server_session(tcp::socket socket);
    virtual ~server_session();

    void set_character(std::shared_ptr<character> character);
    std::shared_ptr<character> character();

    void destroy_character();

protected:

    virtual void on_read_packet(std::shared_ptr<network::packet_buffer_type> buf, unsigned short size) override;
    virtual void on_connect() override;
    virtual void on_disconnect(boost::system::error_code& ec) override;
    virtual void on_disconnect() override;

private:
    account_id account_id_;

    character_weak_ptr character_;
    //std::shared_ptr<character> character_;
};

#endif
