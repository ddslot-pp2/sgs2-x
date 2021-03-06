#include "field.h"
#include "../../../network/src/io_helper.h"
#include "../../../core/src/timer/timer_helper.hpp"
#include <iostream>
#include "../packet_processor/packet/LOBBY.pb.h"
#include "../packet_processor/send_helper.h"
#include "../packet_processor/packet/GAME.pb.h"
//#include "../item/item.h"
#include "../item/medal_item.h"
#include <random>
#include "../property/property_manager.h"
#include "../../../core/src/locale/string_helper.h"

using namespace network;

field::field(unsigned int field_id) : field_id_(field_id), last_update_(clock()), rank_timer_(std::make_unique<timer_ptr::element_type>(network::io_service())), rank_time_(2000)
{
    
}

field::~field()
{

}

void field::initialize()
{
    current_user_count_ = characters_.size();
    start_rank_timer();
}

void field::update(float delta)
{
    for (auto& c : characters_)
    {
        c.second->update(delta);
    }

    for (auto& item : items_)
    {
        item->update(delta);
    }

    for (auto it = std::begin(medal_items_); it != std::end(medal_items_);)
    {
        auto& medal_item = it->second;
        medal_item->update(delta);

        if (!medal_item->get_active())
        {
            // 삭제
            //medal_item->destroy();
            medal_items_.erase(it++);
        }
        else
        {
            ++it;
        }
    }

    update_rank();
}

void field::try_update()
{
    process_task();

    auto now = clock();
    auto t = now - last_update_;
    auto delta = static_cast<float>(t) / static_cast<float>(CLOCKS_PER_SEC);
    if (update_interval <= delta)
    {
        update(delta);
        last_update_ = now;
    }
    
    update_flag_.clear();
}

void field::process_task()
{
    task t;
    while (q_.try_pop(t))
    {
        t();
    }

    /*
    for (auto& c : characters_)
    {
        c.second->process_task();
    }
    */
}

bool field::check_update_flag()
{
    if (update_flag_.test_and_set())
    {
        //wprintf(L"write in progressing -> return@@\n");
        return false;
    }

    return true;
}

std::map<uid, std::shared_ptr<character>>& field::get_view_list()
{
    return characters_;
}

void field::enter_field(std::shared_ptr<server_session> session)
{
    wprintf(L"유저 필드 들어옴\n");

    LOBBY::SC_ENTER_FIELD send;
    send.set_result(true);

    if (characters_.size() > max_user_per_field)
    {
        send.set_result(false);
        send_packet(session, opcode::SC_ENTER_FIELD, send);
        return;
    }

    auto c = std::make_shared<character>(field_id_, session);
    c->initialize();
    c->set_character_type(session->get_character_type());

    auto object_id = reinterpret_cast<std::uintptr_t>(&(*c));

    auto it = characters_.find(object_id);
    if (it != characters_.end())
    {
        // 오브젝트 메모리 주소겹침
        send.set_result(false);
        send_packet(session, opcode::SC_ENTER_FIELD, send);
        return;
    }

    characters_[object_id] = c;
    c->set_object_id(object_id);

    std::mt19937 rng;
    rng.seed(std::random_device()());
    std::uniform_int_distribution<std::mt19937::result_type> dist(1, 10);

    auto random_x = dist(rng);
    auto random_z = dist(rng);

    vector3 spawn_pos(0.0f + random_x, 0.0f, 0.0f + random_z);
    c->set_pos(spawn_pos);

    // stat_info 설정 => default_stat_info + stat_info (account)
    /*
    const auto default_stat_info = property_manager::instance().get_default_stat_info(session->get_character_type());

    if (!default_stat_info) 
    {
        send.set_result(false);
        send_packet(session, opcode::SC_ENTER_FIELD, send);
        return;
    }

    auto stat = std::make_shared<stat_info>();

    auto buff_stat = session->get_stat_info();
    stat->max_hp       = default_stat_info->max_hp + buff_stat->max_hp;
    stat->hp           = stat->max_hp.load();
    stat->speed        = default_stat_info->speed + buff_stat->speed;
    stat->bullet_speed = default_stat_info->bullet_speed + buff_stat->bullet_speed;
    stat->bullet_power = default_stat_info->bullet_power + buff_stat->bullet_power;
    stat->bullet_distance = default_stat_info->bullet_distance + buff_stat->bullet_distance;
    stat->reload_time = std::max(0.0f, default_stat_info->reload_time - buff_stat->reload_time);
    */

    c->set_stat_info(session->get_stat_info());

    session->set_character(c);
    current_user_count_ = characters_.size();
    send_packet(session, opcode::SC_ENTER_FIELD, send);

    rank_characters_.emplace_back(c);
    wprintf(L"유저 카운트: %lld\n", characters_.size());
}

void field::leave_field(object_id id)
{
    wprintf(L"유저 필드 나감\n");
    current_user_count_ = characters_.size();
    auto it = characters_.find(id);

    if (it == characters_.end()) return;

    auto c = it->second;
    c->destroy();

    auto sess = c->get_session();
    if (sess)
    {
        sess->set_character(nullptr);
        // 정상적으로 방을 나갔다고 알려줌
        //sess->
    }

    characters_.erase(id);

    auto remove_c = std::find_if(rank_characters_.begin(), rank_characters_.end(), [c](std::shared_ptr<character> o)
    {
        if (c->get_object_id() == o->get_object_id()) return true;

        return false;
    });

    if(remove_c != rank_characters_.end()) rank_characters_.erase(remove_c);

    GAME::SC_NOTI_OTHER_LEAVE_FIELD noti;
    noti.set_obj_id(id);

    for (const auto& kv : characters_)
    {
        auto other = kv.second;

        auto other_session = other->get_session();
        if (!other_session) continue;

        send_packet(other_session, opcode::SC_NOTI_OTHER_LEAVE_FIELD, noti);
    }

    wprintf(L"유저 카운트: %lld\n", characters_.size());
}

void field::respawn_character(object_id id)
{
    /*
    auto it = characters_.find(id);
    if (it == characters_.end()) return;

    it->second->respawn();
    */
}

void field::sync_field(std::shared_ptr<server_session> session) const
{
    wprintf(L"sync field called\n");
}

void field::update_character_status(object_id id) const
{
    auto it = characters_.find(id);
    if (it == characters_.end()) return;
    
    auto stat_info = it->second->get_stat_info();

    GAME::SC_NOTI_UPDATE_CHARACTER_STATUS noti;
    noti.set_obj_id(id);
    noti.set_max_hp(stat_info->max_hp);
    noti.set_hp(stat_info->hp);
    noti.set_speed(stat_info->speed);
    noti.set_reload_time(stat_info->reload_time);

    for (const auto& kv : characters_)
    {
        auto other = kv.second;

        auto other_session = other->get_session();
        if (!other_session) continue;

        send_packet(other_session, opcode::SC_NOTI_UPDATE_CHARACTER_STATUS, noti);
    }
}

void field::noti_active_item(const item_id& id, const int& type, const vector3& pos) const
{
    GAME::SC_NOTI_ACTIVE_ITEM noti;

    auto item_info = noti.add_item_infos();
    item_info->set_item_id(id);
    item_info->set_item_type(type);
    item_info->set_pos_x(pos.X);
    item_info->set_pos_y(pos.Y);
    item_info->set_pos_z(pos.Z);
  
    noti_packet(opcode::SC_NOTI_ACTIVE_ITEM, noti);
}

void field::noti_active_item(std::shared_ptr<server_session> session) const
{
    GAME::SC_NOTI_ACTIVE_ITEM noti;
    for (const auto& item : items_)
    {
        if (item->get_active())
        {
            auto item_info = noti.add_item_infos();
            item_info->set_item_id(item->get_item_id());
            item_info->set_item_type(to_integral(item->get_type()));

            const auto& pos = item->get_pos();
            item_info->set_pos_x(pos.X);
            item_info->set_pos_y(pos.Y);
            item_info->set_pos_z(pos.Z);
        }
    }
    
    send_packet(session, opcode::SC_NOTI_ACTIVE_ITEM, noti);
}

void field::create_medal_item(const vector3& from_pos, const int count)
{
    GAME::SC_NOTI_CREATE_MEDAL_ITEM noti;

    for (auto i = 0; i < count; ++i)
    {
        // spawn_from
        // spawn_to
        std::mt19937 rng;
        rng.seed(std::random_device()());
        std::uniform_int_distribution<std::mt19937::result_type> dist(1, 10);

        auto random_x = dist(rng);
        auto random_z = dist(rng);

        //std::cout << dist(rng) << std::endl;

        vector3 to_pos(from_pos.X + random_x, 0.0f, from_pos.Z + random_z);

        auto medal = std::make_shared<medal_item>(field_id_, std::chrono::milliseconds(1000 * 10), to_pos);
        medal->start_expire_timer();

        auto medal_item_info = noti.add_medal_item_infos();

        medal_item_info->set_item_id(medal->get_item_id());
        medal_item_info->set_item_type(to_integral(medal->get_type()));
        medal_item_info->set_from_pos_x(from_pos.X);
        medal_item_info->set_from_pos_y(from_pos.Y);
        medal_item_info->set_from_pos_z(from_pos.Z);
        medal_item_info->set_to_pos_x(to_pos.X);
        medal_item_info->set_to_pos_y(to_pos.Y);
        medal_item_info->set_to_pos_z(to_pos.Z);

        medal_items_[medal->get_item_id()] = medal;
    }

    noti_packet(opcode::SC_NOTI_CREATE_MEDAL_ITEM, noti);
}

void field::update_rank()
{
    std::sort(rank_characters_.begin(), rank_characters_.end(), [](std::shared_ptr<character> l, std::shared_ptr<character> r)
    {
        if (l->get_score() > r->get_score()) return true;

        return false;
    });

    auto size = rank_characters_.size() > max_rank_size ? max_rank_size : rank_characters_.size();
    for (auto i = 0; i < size; ++i)
    {
        auto obj_id = rank_characters_[i]->get_object_id();
        auto score  = rank_characters_[i]->get_score();
        rank_characters_[i]->set_rank(i+1);
        //wprintf(L"obj_id: %lld, score: %d\n", obj_id, score);
    }
}

void field::destroy()
{
    rank_timer_->cancel();
}

void field::start_rank_timer()
{
    auto self = shared_from_this();
    rank_timer_->expires_from_now(rank_time_);
    rank_timer_->async_wait([this, self](const boost::system::error_code& ec) {

        if (ec)
        {
            wprintf(L"랭크 타이머가 문제있음\n");
            return;
        }

        send_task(&field::noti_rank_info);
        start_rank_timer();
    });
}

void field::noti_rank_info() const
{
    GAME::SC_NOTI_RANK_INFO noti;
    auto size = rank_characters_.size() > max_rank_size ? max_rank_size : rank_characters_.size();
    for (auto i = 0; i < size; ++i)
    {
        auto rank_info = noti.add_rank_infos();

        auto obj_id = rank_characters_[i]->get_object_id();
        auto score = rank_characters_[i]->get_score();

        rank_info->set_object_id(obj_id);
        rank_info->set_score(score);

        auto sess = rank_characters_[i]->get_session();
        if (sess) rank_info->set_nickname(core::wstring_to_utf8(sess->get_nickname()));
    }
    noti_packet(opcode::SC_NOTI_RANK_INFO, noti);
}