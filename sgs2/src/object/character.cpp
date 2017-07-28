#include "character.h"
#include "../field/field.h"
#include "../field/field_manager.h"
#include "../packet_processor/packet/GAME.pb.h"
#include "../packet_processor/send_helper.h"
#include "../../../core/src/timer/timer_helper.hpp"
#include "../../../core/src/locale/string_helper.h"

using super = object;

character::character(field_id id, std::shared_ptr<server_session> session) : object(id), session_(session), score_(0), start_time_(0), rank_(0), shield_(false), shield_time_(10000), shield_timer_(std::make_unique<timer_ptr::element_type>(network::io_service()))
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

    character_type_ = 1;
    start_time_ = core::timestamp();
}

void character::update(float delta)
{
    // destry ������ ���ؼ� component ������Ʈ�� ���� �����̴�.
    if (destroy_)
    {

        return;
    }

    update_score();
    //update_exp();

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

    auto total_time = core::timestamp() - start_time_;
    wprintf(L"������ ��ƾ �ð���: %lld ms\n", total_time.count());

    // ��ũ�Ŵ��� ����� �ű⼭ ����ؼ���
    auto create_medal_count = 1;

    //wprintf(L"pos X: %f, pos Z: %f\n", pos_.X, pos_.Z);
    field_->create_medal_item(pos_, create_medal_count);

    shield_timer_->cancel();
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
    if (score_ == score || score <= 0) return;

    auto sess = session_.lock();
    if (!sess) return;

    score_ = score;

    wprintf(L"���ھ� ����: %d\n", score);
    GAME::SC_NOTI_RANK noti;
    noti.set_rank(rank_);
    noti.set_nickname(core::wstring_to_utf8(sess->get_nickname()));
    noti.set_score(score_);

    send_packet(sess, opcode::SC_NOTI_RANK, noti);
}

void character::update_exp() const
{
    /*
    if (stat_->exp < 100.0f) return;

    if (stat_->level == max_level)
    {
        wprintf(L"�ִ� ������ ���� ���׷��̵带 �Ҽ� �����ϴ�\n");
        return;
    }

    auto exp = stat_->exp.load();

    auto level_up_count = static_cast<int>(exp / 100.0f);
    stat_->exp = stat_->exp - (level_up_count * 100.0f);

    stat_->level = stat_->level + static_cast<int>(level_up_count);
    wprintf(L"���� ����: %d\n", stat_->level.load());

    stat_->enhance_buff_count += level_up_count;

    wprintf(L"���� ī��Ʈ ����: %d\n", stat_->enhance_buff_count.load());

    GAME::SC_SELECT_BUFF noti;
    noti.set_count(level_up_count);
    auto session = session_.lock();
    if (session)
    {
        send_packet(session, opcode::SC_SELECT_BUFF, noti);
    }
    */
}

unsigned int character::get_shield_time() const
{
    return static_cast<unsigned int>(shield_time_.count());
}

void character::start_shield_timer()
{
    if (shield_) return;

    wprintf(L"���� ������ ����\n");
    shield_ = true;

    auto self = shared_from_this();
    shield_timer_->expires_from_now(shield_time_);
    shield_timer_->async_wait([this, self](const boost::system::error_code& ec) {

        if (ec)
        {
            wprintf(L"���� Ÿ�̸Ӱ� ��������\n");
            return;
        }

        wprintf(L"���� ������ �Ҹ�\n");
        shield_ = false;
    });
}
