#include "bullet.h"
#include "../../../object/object.h"
#include "../../../field/field.h"
#include "../../../packet_processor/packet/GAME.pb.h"
#include "../../../packet_processor/opcode.h"
#include "../../../packet_processor/send_helper.h"

bullet::bullet(object* obj, const vector3& dir, const vector3& size, float speed, float distance, float power) : object_(obj), dir_(dir), size_(size), speed_(speed), distance_(distance), power_(power), destroy_(false)
{
    from_ = obj->get_pos();
    pos_  = from_;
}

bullet::~bullet()
{

}

void bullet::update(float delta)
{
    if (over_distance())
    {
        wprintf(L"사정거리 넘어가서 총알 파괴\n");
        destroy_ = true;
        return;
    }

    std::shared_ptr<character> target_object = nullptr;

    // 이 충돌 부분 속도관련 업데이트 필요
    auto& view_list = object_->get_field()->get_view_list();
    for (auto view : view_list)
    {
        auto other = view.second;

        if (other->get_object_id() == object_->get_object_id()) continue;

        auto stat_info = other->get_stat_info();
        if (check_intersection(pos_, other->get_pos(), size_, stat_info->size))
        {
            target_object = other;
            break;
        }
    }

    if (target_object)
    {
        wprintf(L"충돌체에 부딪혀서 총알 파괴\n");
        collide_with_other(target_object);
        destroy_ = true;
        return;
    }

    pos_ = pos_ + (dir_ * speed_ * delta);
    wprintf(L"총알 이동중 x: %f, z: %f\n", pos_.X, pos_.Z);
}

void bullet::destroy() const
{

}

void bullet::collide_with_other(std::shared_ptr<character> target_object)
{
    // other hp 감소
    auto stat_info = target_object->get_stat_info();
    int target_hp = static_cast<float>(stat_info->hp) - power_;

    stat_info->hp = target_hp;

    if (target_hp <= 0)
    {
        // 이 불렛이 마지막으로 destroy시킴
        // object_->get_object_id();

        // 필드에 알려줘서 처리를 해줌
        //object_->get_field()->reward_destroy_object(obj_id);

    }

    GAME::SC_NOTI_DESTROY_BULLET noti;
    noti.set_obj_id(object_->get_object_id());
    noti.set_bullet_id(id_);

    auto damage_info = noti.add_damage_infos();
    damage_info->set_target_id(target_object->get_object_id());
    damage_info->set_damage(target_hp);
    damage_info->set_damage(power_);

    auto& view_list = object_->get_field()->get_view_list();
    for (auto view : view_list)
    {
        auto other = view.second;
        auto other_session = other->get_session();
        if (other_session)
        {
            send_packet(other_session, opcode::SC_NOTI_DESTROY_BULLET, noti);
        }
    }
}

void bullet::set_bullet_id(bullet_id id)
{
    id_ = id;
}

bool bullet::over_distance() const
{
    if (distance(from_, pos_) > distance_)
    {
        GAME::SC_NOTI_DESTROY_BULLET noti;
        noti.set_obj_id(object_->get_object_id());
        noti.set_bullet_id(id_);

        auto& view_list = object_->get_field()->get_view_list();
        for (auto view : view_list)
        {
            auto other = view.second;
            auto other_session = other->get_session();
            if (other_session)
            {
                send_packet(other_session, opcode::SC_NOTI_DESTROY_BULLET, noti);
            }
        }

        return true;
    }
        
    return false;
}

bool bullet::check_intersection(const vector3& bullet_pos, const vector3& other_pos, const vector3& bullet_size, const vector3& other_size) const
{
    const auto bullet_half_x = (bullet_size.X / 2.0f);
    const auto bullet_half_z = (bullet_size.Z / 2.0f);

    const auto other_half_x = (other_size.X / 2.0f);
    const auto other_half_z = (other_size.Z / 2.0f);

    //printf("enemy => x: %f, y: %f, z: %f\n", object_pos.X, object_pos.Y, object_pos.Z);
    auto a_min_x = bullet_pos.X - bullet_half_x;
    auto a_max_x = bullet_pos.X + bullet_half_x;
    auto a_min_z = bullet_pos.Z - bullet_half_z;
    auto a_max_z = bullet_pos.Z + bullet_half_z;

    auto b_min_x = other_pos.X - other_half_x;
    auto b_max_x = other_pos.X + other_half_x;
    auto b_min_z = other_pos.Z - other_half_z;
    auto b_max_z = other_pos.Z + other_half_z;


    if (a_max_x < b_min_x || a_min_x > b_max_x) return false;
    if (a_max_z < b_min_z || a_min_z > b_max_z) return false;

    return true;
}