#include "session.h"

namespace network
{
    session::session(tcp::socket socket)
        : socket_(std::move(socket)), header_(0)
    {
        printf("session ctor called\n");
    }

    session::~session()
    {
        printf("session dtor called\n");
    }

    void session::start()
    {
        on_connect();
        do_read_header();
    }

    void session::close()
    {
        socket_.close();
    }

    void session::send(send_buf_ptr buf)
    {
        //wprintf(L"@@SEND@@\n");
        q_.push(buf);

        //wprintf(L"@@do_write@@\n");
        do_write();
    }

    void session::do_read_header()
    {
        auto self(shared_from_this());
        boost::asio::async_read(socket_,
            boost::asio::buffer(&header_, sizeof(header_)),
            [this, self](boost::system::error_code ec, std::size_t /*length*/)
        {
            if (ec || header_ <= 0 || header_ > max_packet_size)
            {
                if (header_ == 0)
                {
                    on_disconnect();
                    return;
                }

                on_disconnect(ec);
                return;
            }

            do_read_body();
        });
    }

    void session::do_read_body()
    {
        receive_buffer_ = std::make_shared<packet_buffer_type>();

        auto self(shared_from_this());
        boost::asio::async_read(socket_,
            boost::asio::buffer(receive_buffer_->data(), header_),
            [this, self](boost::system::error_code ec, std::size_t length)
        {
           
            if (ec || length <= 0 || length > max_packet_size)
            {
                if (length == 0)
                {
                    on_disconnect();
                    return;
                }

                on_disconnect(ec);
                return;
            }
            on_read_packet(std::move(receive_buffer_), header_);            

            do_read_header();
        });
    }

    void session::do_write()
    {
        if (write_in_progress_.test_and_set(std::memory_order_acquire))
        {
            //wprintf(L"write in progressing -> return@@\n");
            return;
        }

        auto self(shared_from_this());

        send_buf_ptr send_buf = nullptr;
        
        if (q_.try_pop(send_buf))
        {
            boost::asio::async_write(socket_,
                boost::asio::buffer(send_buf->buf.data(),
                    send_buf->size),
                [this, self](boost::system::error_code ec, std::size_t length)
            {
                //wprintf(L"send complete:%d\n", length);
                write_in_progress_.clear(std::memory_order_release);
                
                if (ec)
                {
                    wprintf(L"send error\n");
                 
                    handle_error_code(ec);
                    return;
                }

                //wprintf(L"q size: %d", q_.unsafe_size());

                if (q_.empty())
                {
                    //wprintf(L"retur q is empty\n");
                    return;
                }

                do_write();
                
            });
        }
        else
        {
            //wprintf(L"release flag\n");
            write_in_progress_.clear(std::memory_order_release);
        }
    }

    void session::handle_error_code(boost::system::error_code& ec)
    {
        q_.clear();
        wprintf(L"handle_error_code called\n");
    }
}
