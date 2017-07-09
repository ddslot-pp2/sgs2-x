#ifndef __IO_HELPER_H
#define __IO_HELPER_H

#include <boost/asio.hpp>

namespace network
{
    static constexpr unsigned short max_packet_size = 8000;
    static constexpr unsigned short packet_buf_size = 8096;

    using packet_buffer_type = std::array<char, packet_buf_size>;
    
    struct send_buffer
    {
        packet_buffer_type buf;
        unsigned short size = 0;
    };

    using send_buf_ptr = std::shared_ptr<send_buffer>;

    void create_io_service();
    boost::asio::io_service& io_service();

    void initialize();
    void start(size_t thread_pool_size, std::function<void()> callaback);
    void stop();
}

#endif
