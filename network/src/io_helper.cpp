#ifndef __IO_HELPER_H
#define __IO_HELPER_H

#include <thread>
#include <functional>
#include <memory>
#include <vector>
#include <boost/asio.hpp>

namespace network
{
    std::shared_ptr<boost::asio::io_service> g_io_service;
    std::vector<std::thread> g_io_threads;

    void create_io_service()
    {
        g_io_service = std::make_shared<boost::asio::io_service>();
    }

    boost::asio::io_service& io_service()
    {
        return *(g_io_service);
    }

    void initialize()
    {
        create_io_service();

    }

    void start(size_t thread_count, std::function<void()> callback)
    {
        g_io_threads.reserve(thread_count);

        for (auto i = 0; i < thread_count; ++i)
        {
            g_io_threads.emplace_back([callback] {

                callback();

                boost::system::error_code ec;
                g_io_service->run(ec);

                if (ec)
                {
                    //

                }


            });
        }
    }

    void stop()
    {
        g_io_service->stop();

        for (auto& io_thread : g_io_threads)
        {
            io_thread.join();
        }

        g_io_threads.clear();
    }
}

#endif
