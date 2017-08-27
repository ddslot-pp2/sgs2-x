#include "egypt_field.h"
#include "../packet_processor/packet/GAME.pb.h"
#include "../packet_processor/send_helper.h"
#include "../core/src/locale/string_helper.h"
#include "../item/hp_item.h"
#include "../item/coin_item.h"
#include "../item/shield_item.h"

using super = field;

egypt_field::egypt_field(unsigned int field_id) : field(field_id)
{

}

egypt_field::~egypt_field()
{

}

void egypt_field::initialize()
{
    // rotation: -16.873
    //colliders_.emplace_back(collider(vector3(-7.0, 0.0f, -23.4f), vector3(10.0f, 0.0f, 10.0f), -16.873f));
    //colliders_.emplace_back(collider(vector3(10.0, 0.0f, 0.0f), vector3(10.0f, 0.0f, 10.0f),  90.0f));

    colliders_.emplace_back(collider(vector3(-36.5f, 0.0f, 35.3f), vector3(10.0f, 0.0f, 10.0f),  31.815f));
    colliders_.emplace_back(collider(vector3( 45.0f, 0.0f,  44.8f), vector3(10.0f, 0.0f, 10.0f), -28.189f));
    colliders_.emplace_back(collider(vector3( 46.5f, 0.0f, -42.0f), vector3(10.0f, 0.0f, 10.0f), -38.78f));
    colliders_.emplace_back(collider(vector3(-36.1f, 0.0f, -41.2f), vector3(10.0f, 0.0f, 10.0f), -63.455f));
    colliders_.emplace_back(collider(vector3(-15.6f, 0.0f,   8.9f), vector3(10.0f, 0.0f, 10.0f), -19.766f));
    colliders_.emplace_back(collider(vector3( 24.3f, 0.0f, -11.4f), vector3(10.0f, 0.0f, 10.0f), 32.987f));
    colliders_.emplace_back(collider(vector3(-7.0f, 0.0f, -23.4f), vector3(10.0f, 0.0f, 10.0f), -16.873f));
    colliders_.emplace_back(collider(vector3(14.3f, 0.0f,  26.4f), vector3(10.0f, 0.0f, 10.0f),  16.314f));
    colliders_.emplace_back(collider(vector3(-56.0f, 0.0f,  55.1f), vector3(5.0f, 0.0f, 5.0f),  32.378f));
    colliders_.emplace_back(collider(vector3( 61.0f, 0.0f,  59.1f), vector3(5.0f, 0.0f, 5.0f), -31.039f));
    colliders_.emplace_back(collider(vector3( 49.0f, 0.0f, -14.4f), vector3(5.0f, 0.0f, 5.0f), -34.395f));
    colliders_.emplace_back(collider(vector3(-55.6f, 0.0f, -59.8f), vector3(5.0f, 0.0f, 5.0f), -23.465f));
    colliders_.emplace_back(collider(vector3(53.8f, 0.0f,  -61.3f), vector3(5.0f, 0.0f, 5.0f), -20.887f));
    colliders_.emplace_back(collider(vector3(-36.4f, 0.0f, -11.5f), vector3(5.0f, 0.0f, 5.0f),  23.794f));
    colliders_.emplace_back(collider(vector3( -9.2f, 0.0f,  44.5f), vector3(5.0f, 0.0f, 5.0f), -30.408f));
    colliders_.emplace_back(collider(vector3(42.8f, 0.0f,  19.2f), vector3(5.0f, 0.0f, 5.0f), -35.617f));
    colliders_.emplace_back(collider(vector3(26.1f, 0.0f, -47.1f), vector3(5.0f, 0.0f, 5.0f),  21.373f));
    colliders_.emplace_back(collider(vector3(-14.0f, 0.0f, -46.9f), vector3(5.0f, 0.0f, 5.0f), -41.659f));
    colliders_.emplace_back(collider(vector3( 30.6f, 0.0f,  56.4f), vector3(5.0f, 0.0f, 5.0f), -27.661f));
    colliders_.emplace_back(collider(vector3(-48.8f, 0.0f,  18.2f), vector3(5.0f, 0.0f, 5.0f), -37.117f));
    colliders_.emplace_back(collider(vector3( 13.3f, 0.0f, -23.8f), vector3(5.0f, 0.0f, 5.0f), -20.314f));
    colliders_.emplace_back(collider(vector3(-6.8f, 0.0f,  21.8f), vector3(5.0f, 0.0f, 5.0f),   31.268f));
    colliders_.emplace_back(collider(vector3(19.4f, 0.0f,   8.3f), vector3(5.0f, 0.0f, 5.0f), -29.955f));
    colliders_.emplace_back(collider(vector3(-56.4f, 0.0f, -23.8f), vector3(5.0f, 0.0f, 5.0f), -26.436f));
    colliders_.emplace_back(collider(vector3( 58.5f, 0.0f,-26.8f), vector3(5.0f, 0.0f, 5.0f), -22.443f));
    colliders_.emplace_back(collider(vector3( 15.8f, 0.0f,  49.4f), vector3(5.0f, 0.0f, 5.0f), -32.244f));
    colliders_.emplace_back(collider(vector3(-24.5f, 0.0f,  59.5f), vector3(5.0f, 0.0f, 5.0f), -23.226f));
    colliders_.emplace_back(collider(vector3( 16.5f, 0.0f, -58.8f), vector3(5.0f, 0.0f, 5.0f), -24.652f));  
 
    items_.emplace_back(std::make_shared<hp_item>(field_id_, std::chrono::milliseconds(5000), vector3(0.0f, 0.0f, 5.0f)));
    items_.emplace_back(std::make_shared<hp_item>(field_id_, std::chrono::milliseconds(5000), vector3(0.0f, 0.0f, 0.0f)));
    items_.emplace_back(std::make_shared<hp_item>(field_id_, std::chrono::milliseconds(5000), vector3(5.0f, 0.0f, 0.0f)));
    items_.emplace_back(std::make_shared<hp_item>(field_id_, std::chrono::milliseconds(5000), vector3(0.0f, 0.0f, -5.0f)));


    items_.emplace_back(std::make_shared<coin_item>(field_id_, std::chrono::milliseconds(8000), vector3(4.0f, 0.0f, 5.0f)));
    items_.emplace_back(std::make_shared<coin_item>(field_id_, std::chrono::milliseconds(8000), vector3(2.0f, 0.0f, 0.0f)));
    items_.emplace_back(std::make_shared<coin_item>(field_id_, std::chrono::milliseconds(8000), vector3(8.0f, 0.0f, 0.0f)));
    items_.emplace_back(std::make_shared<coin_item>(field_id_, std::chrono::milliseconds(8000), vector3(10.0f, 0.0f, -5.0f)));

    items_.emplace_back(std::make_shared<shield_item>(field_id_, std::chrono::milliseconds(5000), vector3(14.0f, 0.0f, 5.0f)));
    items_.emplace_back(std::make_shared<shield_item>(field_id_, std::chrono::milliseconds(5000), vector3(12.0f, 0.0f, 0.0f)));
    items_.emplace_back(std::make_shared<shield_item>(field_id_, std::chrono::milliseconds(5000), vector3(18.0f, 0.0f, 0.0f)));
    items_.emplace_back(std::make_shared<shield_item>(field_id_, std::chrono::milliseconds(5000), vector3(20.0f, 0.0f, -5.0f)));

    super::initialize();
}

void egypt_field::update(float delta)
{
    if (field_id_ == 0)
    {
        //wprintf(L"id: %d, delta: %f\n", field_id_, delta);
    }

    super::update(delta);
}

void egypt_field::destroy()
{
    super::destroy();
}

void egypt_field::sync_field(std::shared_ptr<server_session> session) const
{
    wprintf(L"sync egypt_field called\n");

    auto c = session->get_character();
    if (!c)
    {
        // 문제있음...
    }

    GAME::SC_SYNC_FIELD send;
    // 나의 정보 추가
    send.set_obj_id(c->get_object_id());
    send.set_nickname(core::wstring_to_utf8(session->get_nickname()));

    auto pos = c->get_pos();
    send.set_pos_x(pos.X);
    send.set_pos_y(pos.Y);
    send.set_pos_z(pos.Z);

    auto stat_info = c->get_stat_info();

    auto tank_type = c->get_character_type();
    send.set_tank_type(tank_type);

    auto hp = stat_info->hp.load();
    send.set_hp(hp);

    auto max_hp = stat_info->max_hp.load();
    send.set_max_hp(max_hp);

    auto speed = stat_info->speed.load();
    send.set_speed(speed);
    send.set_bullet_speed(stat_info->bullet_speed.load());
    send.set_bullet_power(stat_info->bullet_power.load());
    send.set_bullet_distance(stat_info->bullet_distance.load());
    send.set_reload_time(stat_info->reload_time.load());

    auto nickname = session->get_nickname();

    // 다른 유저에게도 나의 정보를 보내줘야함
    GAME::SC_NOTI_OTHER_ENTER_FIELD noti;
    noti.set_obj_id(c->get_object_id());
    noti.set_nickname(core::wstring_to_utf8(nickname));
    noti.set_pos_x(pos.X);
    noti.set_pos_x(pos.Y);
    noti.set_pos_x(pos.Z);
  
    noti.set_tank_type(tank_type);
    noti.set_hp(hp);

    noti.set_max_hp(max_hp);
    noti.set_speed(speed);
    noti.set_bullet_speed(stat_info->bullet_speed.load());
    noti.set_bullet_power(stat_info->bullet_power.load());
    noti.set_bullet_distance(stat_info->bullet_distance.load());
    noti.set_reload_time(stat_info->reload_time.load());

    // 주변 유저 정보 추가
    for (const auto& kv : characters_)
    {
        auto other = kv.second;

        if (other->get_object_id() == c->get_object_id()) continue;

        auto other_session = other->get_session();
        if (!other_session) continue;

        send_packet(other_session, opcode::SC_NOTI_OTHER_ENTER_FIELD, noti);

        auto other_info = send.add_other_infos();
        other_info->set_obj_id(other->get_object_id());

        other_info->set_nickname(core::wstring_to_utf8(other_session->get_nickname()));
       
        auto other_pos = other->get_pos();
        other_info->set_pos_x(other_pos.X);
        other_info->set_pos_y(other_pos.Y);
        other_info->set_pos_z(other_pos.Z);

        auto other_tank_type = other->get_character_type();
        other_info->set_tank_type(other_tank_type);

        auto other_stat_info = other->get_stat_info();
        other_info->set_hp(other_stat_info->hp);
        other_info->set_max_hp(other_stat_info->max_hp);
        other_info->set_speed(other_stat_info->speed);

        other_info->set_bullet_speed(other_stat_info->bullet_speed);
        other_info->set_bullet_power(other_stat_info->bullet_power);
        other_info->set_bullet_distance(other_stat_info->bullet_distance);
        other_info->set_reload_time(other_stat_info->reload_time);
    }

    send_packet(session, opcode::SC_SYNC_FIELD, send);

    // 아이템 정보도 보내줌
    noti_active_item(session);
}

void egypt_field::respawn_character(object_id id)
{
    //vector3 spawn_pos(10.0f, 0.0f, 0.0f);

    auto it = characters_.find(id);
    if (it == characters_.end()) return;

    auto c = it->second;
    
    auto spawn_pos = c->get_pos();
    c->respawn(spawn_pos);
}
