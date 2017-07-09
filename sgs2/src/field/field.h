#ifndef __FIELD_H
#define __FIELD_H

#include <chrono>
#include <memory>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/deadline_timer.hpp>
#include "../predeclare.h"
#include <concurrent_queue.h>
#include "../object/character.h"

class field : std::enable_shared_from_this<field>
{
public:
    explicit field(unsigned int field_id);
    virtual ~field();

    void try_update();

    virtual void initialize();
    virtual void update(float delta) {}

    bool check_update_flag();

protected:
    unsigned int field_id_;

    Concurrency::concurrent_queue<task> q_;

    std::map<uid, std::shared_ptr<character>> characters_;

private:
    void process_task();

    timer_ptr update_timer_;
    clock_t last_update_;
    std::atomic_flag update_flag_ = ATOMIC_FLAG_INIT;
    
};

#endif
