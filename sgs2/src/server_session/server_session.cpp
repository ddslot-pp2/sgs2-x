#include "server_session.h"
#include "../packet_processor/packet_processor.h"
#include "../packet_processor/send_helper.h"

server_session::server_session(tcp::socket socket) : session(std::move(socket))
{
    
}

server_session::~server_session()
{

}

void server_session::on_read_packet(std::shared_ptr<network::packet_buffer_type> buf, unsigned short size)
{
    wprintf(L"server_session on_read_packet called\n");
    auto self = std::static_pointer_cast<server_session>(shared_from_this());
    handle_packet(self, buf, size);
}

void server_session::on_connect()
{
    wprintf(L"server_session on_connected called\n");
    
    LOBBY::SC_LOG_IN send;
    send.set_result(true);
    send.set_timestamp(200000);
    send_packet(shared_from_this(), opcode::SC_LOG_IN, send);
    
}

void server_session::on_disconnect(boost::system::error_code& ec)
{
    wprintf(L"on disconnect with error\n");
}

void server_session::on_disconnect()
{
    wprintf(L"on disconnect\n");
}
