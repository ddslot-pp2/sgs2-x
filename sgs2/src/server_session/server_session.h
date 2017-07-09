#ifndef __SERVER_SESSION_H
#define __SERVER_SESSION_H

#include "session/session.h"
#include "../predeclare.h"

using boost::asio::ip::tcp;

class server_session : public network::session
{
public:

    explicit server_session(tcp::socket socket);
    virtual ~server_session();

protected:

    virtual void on_read_packet(std::shared_ptr<network::packet_buffer_type> buf, unsigned short size) override;
    virtual void on_connect() override;
    virtual void on_disconnect(boost::system::error_code& ec) override;
    virtual void on_disconnect() override;

private:
    account_id account_id_;
    //std::shared_ptr<character> character_;
};

#endif
