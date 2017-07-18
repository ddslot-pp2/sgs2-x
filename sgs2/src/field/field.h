#ifndef __FIELD_H
#define __FIELD_H

#include <chrono>
#include <memory>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/deadline_timer.hpp>
#include "../predeclare.h"
#include <concurrent_queue.h>
#include "../object/character.h"
#include "../server_session/server_session.h"
#include "../object/collider.h"

class item;

class field : std::enable_shared_from_this<field>
{
public:
    explicit field(unsigned int field_id);
    virtual ~field();

    void try_update();

    virtual void initialize();
    virtual void update(float delta);

    virtual void sync_field(std::shared_ptr<server_session> session) const;
    virtual void respawn_character(object_id id);

    bool check_update_flag();

    void enter_field(std::shared_ptr<server_session> session);
    void leave_field(object_id id);

    size_t current_user_count() const { return current_user_count_; }

    template <typename Fn, typename... Args>
    void send_task(Fn fn, Args&&... args)
    {
        auto self = shared_from_this();
        auto f = std::bind(fn, self, std::forward<Args>(args)...);
        q_.push(f);
    }

    template <typename T, typename P>
    void noti_packet(T opcode, P noti) const
    {
        for (const auto& kv : characters_)
        {
            auto other = kv.second;

            auto other_session = other->get_session();
            if (!other_session) continue;

            send_packet(other_session, opcode, noti);
        }
    }

    template <typename T, typename P, typename I>
    void noti_packet(T opcode, P noti, I obj_id) const
    {
        for (const auto& kv : characters_)
        {
            auto other = kv.second;

            if (obj_id == other->get_object_id()) continue;

            auto other_session = other->get_session();
            if (!other_session) continue;

            send_packet(other_session, opcode, noti);
        }
    }

    std::map<object_id, std::shared_ptr<character>>& get_view_list();

    void update_character_status(object_id id) const;

    std::vector<collider>& get_colliders() { return colliders_; }

    void noti_active_item() const;
    void noti_active_item(std::shared_ptr<server_session> session) const;

protected:

    unsigned int field_id_;
    Concurrency::concurrent_queue<task> q_;
    std::map<object_id, std::shared_ptr<character>> characters_;

    std::vector<collider> colliders_;
    std::vector<std::shared_ptr<item>> items_;

private:
    void process_task();

    timer_ptr update_timer_;
    clock_t last_update_;
    std::atomic_flag update_flag_ = ATOMIC_FLAG_INIT;
    
    std::atomic<size_t> current_user_count_;
};

#endif
