#include "character.h"
#include "../field/field.h"
#include "../field/field_manager.h"
#include "../packet_processor/packet/GAME.pb.h"
#include "../packet_processor/send_helper.h"

using super = object;

character::character(field_id id, std::shared_ptr<server_session> session) : object(id), session_(session)
{
    wprintf(L"�ɸ��� ������ ȣ��\n");
    field_ = field_manager::instance().get_field(id);
}

character::~character()
{
    wprintf(L"�ɸ��� �Ҹ��� ȣ��\n");
}

void character::initialize()
{
    components_[comp_id::skill_comp] = std::make_shared<skill_component>(this);
    super::initialize();
}

void character::update(float delta)
{
    // destry ������ ���ؼ� component ������Ʈ�� ���� �����̴�.
    if (destroy_)
    {

        return;
    }

    super::update(delta);
}

void character::destroy()
{
    super::destroy();

    destroy_ = true;

    GAME::SC_NOTI_DESTROY_CHARACTER noti;
    noti.set_obj_id(object_id_);

    auto& view_list = field_->get_view_list();
    for (auto kv : view_list)
    {
        auto other = kv.second;
        auto other_session = other->get_session();
        if (other_session)
        {
            send_packet(other_session, opcode::SC_NOTI_DESTROY_CHARACTER, noti);
        }
    }
}

void character::leave_field() const
{
    //field_->send_task(&field::leave_field, object_id_);
    field_->leave_field(object_id_);
}

std::shared_ptr<server_session> character::get_session() const
{
    auto sess = session_.lock();
    if (sess)
    {
        return sess;
    }

    return nullptr;
}

void character::respawn(const vector3& spawn_pos)
{
    for (auto& comp : components_)
    {
        comp.second->reset();
    }

    stat_->copy(default_stat_);

    pos_ = spawn_pos;

    destroy_ = false;

    GAME::SC_NOTI_RESPAWN_CHARACTER noti;
    noti.set_obj_id(object_id_);
    noti.set_pos_x(pos_.X);
    noti.set_pos_y(pos_.Y);
    noti.set_pos_z(pos_.Z);

    noti.set_max_hp(stat_->max_hp);
    noti.set_hp(stat_->hp);
    noti.set_speed(stat_->speed);
    noti.set_reload_time(stat_->reload_time);

    auto& view_list = field_->get_view_list();
    for (auto kv : view_list)
    {
        auto other = kv.second;
        auto other_session = other->get_session();
        if (other_session)
        {
            send_packet(other_session, opcode::SC_NOTI_RESPAWN_CHARACTER, noti);
        }
    }
}
