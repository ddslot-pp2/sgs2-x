#include "egypt_field.h"
#include "../packet_processor/packet/GAME.pb.h"
#include "../packet_processor/send_helper.h"
#include "../core/src/locale/string_helper.h"

using super = field;

egypt_field::egypt_field(unsigned int field_id) : field(field_id)
{

}

egypt_field::~egypt_field()
{

}

void egypt_field::initialize()
{

}

void egypt_field::update(float delta)
{
    if (field_id_ == 0)
    {
        //wprintf(L"id: %d, delta: %f\n", field_id_, delta);
    }

    super::update(delta);
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

    auto pos = c->get_pos();
    send.set_pos_x(pos.X);
    send.set_pos_y(pos.Y);
    send.set_pos_z(pos.Z);

    auto hp = 100;
    send.set_hp(hp);

    auto tank_type = 1;
    send.set_tank_type(tank_type);

    auto nickname = session->get_tmp_nickname();

    // 다른 유저에게도 나의 정보를 보내줘야함
    GAME::SC_NOTI_OTHER_ENTER_FIELD noti;
    noti.set_obj_id(c->get_object_id());
    noti.set_nickname(core::wstring_to_utf8(nickname));
    noti.set_pos_x(pos.X);
    noti.set_pos_x(pos.Y);
    noti.set_pos_x(pos.Z);
    noti.set_hp(hp);
    noti.set_tank_type(tank_type);

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

        other_info->set_nickname(core::wstring_to_utf8(other_session->get_tmp_nickname()));
       
        auto pos = other->get_pos();
        other_info->set_pos_x(pos.X);
        other_info->set_pos_y(pos.Y);
        other_info->set_pos_z(pos.Z);

        auto stat_info = other->get_stat_info();

        other_info->set_hp(stat_info->hp);

        // 추후 처리해야 함
        auto tank_type = 1;
        other_info->set_tank_type(tank_type);
    }

    send_packet(session, opcode::SC_SYNC_FIELD, send);
}

void egypt_field::respawn_character(object_id id)
{
    vector3 spawn_pos(10.0f, 0.0f, 0.0f);

    auto it = characters_.find(id);
    if (it == characters_.end()) return;

    it->second->respawn(spawn_pos);
}
