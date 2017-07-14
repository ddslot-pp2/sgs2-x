#include "character.h"
#include "../field/field.h"
#include "../field/field_manager.h"
#include "../packet_processor/packet/GAME.pb.h"
#include "../packet_processor/send_helper.h"

using super = object;

character::character(field_id id, std::shared_ptr<server_session> session) : object(id), session_(session), score_(0)
{
    wprintf(L"케릭터 생성자 호출\n");
    field_ = field_manager::instance().get_field(id);
}

character::~character()
{
    wprintf(L"케릭터 소멸자 호출\n");
}

void character::initialize()
{
    components_[comp_id::skill_comp] = std::make_shared<skill_component>(this);
    super::initialize();

    character_type_ = 1;
}

void character::update(float delta)
{
    // destry 문제로 인해서 component 업데이트는 없을 예정이다.
    if (destroy_)
    {

        return;
    }

    update_score();
    update_exp();

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

void character::update_score()
{
    auto score = stat_->score.load();
    if (score_ != score && score > 0)
    {
        wprintf(L"스코어 증가: %d\n", score);
        /*
        GAME::SC_UPDATE_SCORE noti;
        noti.set_score(100);
        send_packet(session_, opcode::SC_UPDATE_SCORE, noti);
        */
        score_ = score;
    }
}

void character::update_exp() const
{
    if (stat_->exp < 100.0f) return;

    auto exp = stat_->exp.load();
    auto enhance_buff_count = static_cast<int>(exp / 100.0f);

    stat_->exp = exp - (100.0f * enhance_buff_count);
    stat_->enhance_buff_count += enhance_buff_count;

    wprintf(L"버프 카운트 증가: %d\n", stat_->enhance_buff_count.load());

    GAME::SC_SELECT_BUFF noti;
    noti.set_count(enhance_buff_count);
    auto session = session_.lock();
    if (session)
    {
        send_packet(session, opcode::SC_SELECT_BUFF, noti);
    }
}
