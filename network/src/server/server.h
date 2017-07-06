#ifndef __SERVER_H
#define __SERVER_H

#include <boost/asio.hpp>
#include "../io_helper.h"

namespace network
{
    template <typename T>
    class server
    {
    public:

        void stop()
        {
            boost::system::error_code ec;
            acceptor_.close(ec);
            socket_.close(ec);
        }

        server(boost::asio::io_service& io_service, const boost::asio::ip::tcp::endpoint& endpoint) :
            acceptor_(io_service, endpoint),
            socket_(io_service)
        {
            printf("서버 대기\n");
            do_accept();
        }

    private:

        void do_accept()
        {
            acceptor_.async_accept(socket_, [this](boost::system::error_code ec)
            {
                if (!ec)
                {
                    printf("접속 성공\n");
                    socket_.set_option(boost::asio::ip::tcp::no_delay(false));
                    std::make_shared<T>(std::move(socket_))->start();
                    //sess->on_connect();
                }
                else
                {
                    if (ec.value() == boost::asio::error::operation_aborted)
                    {
                        
                    }
                    else
                    {
                        
                    }

                    return;
                }

                do_accept();
            });
        }

    private:
        boost::asio::ip::tcp::acceptor       acceptor_;
        boost::asio::ip::tcp::socket         socket_;
    };
}

#endif
