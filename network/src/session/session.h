#ifndef __SESSION_H
#define __SESSION_H

#include <memory>
#include <boost/asio.hpp>
#include "../io_helper.h"
#include <deque>

#ifndef __linux__ 
#include <ppl.h>
#include <concurrent_queue.h>
using namespace concurrency;
#endif

namespace network
{
    using boost::asio::ip::tcp;

    class session : public std::enable_shared_from_this<session>
    {
    public:
        explicit session(tcp::socket socket);
        virtual ~session();

        void start();
        void close();

        void send(send_buf_ptr buf);

    protected:
        void do_write();

        void do_read_header();
        void do_read_body();

        virtual void on_read_packet(std::shared_ptr<packet_buffer_type> buf, unsigned short size) {}
        virtual void on_connect() {}
        virtual void on_disconnect(boost::system::error_code& ec) {}
        virtual void on_disconnect() {}

        void handle_error_code(boost::system::error_code& ec);

        tcp::socket socket_;
        unsigned short header_;
        std::shared_ptr<packet_buffer_type> receive_buffer_;

        std::atomic_flag write_in_progress_ = ATOMIC_FLAG_INIT;

#ifndef __linux__ 
        concurrent_queue<send_buf_ptr> q_;
#endif

    };
}

#endif