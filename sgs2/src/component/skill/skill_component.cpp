#include "skill_component.h"
#include "../../object/object.h"
#include "bullet/default_bullet.h"
#include "../../packet_processor/send_helper.h"
#include "../../packet_processor/packet/GAME.pb.h"
#include "../../field/field.h"

using super = component;

skill_component::skill_component(object* obj) : component(obj)
{

}

skill_component::~skill_component()
{

}

void skill_component::update(float delta)
{
    //super::update(delta);

    for (auto& kv : bullets_)
    {
        auto& bullet = kv.second;
        if (bullet->get_destroy())
        {

        }
    }

    for (auto it = std::begin(bullets_); it != std::end(bullets_);)
    {
        auto& bullet_obj = it->second;
        bullet_obj->update(delta);

        if (bullet_obj->get_destroy())
        {
            // 삭제
            bullet_obj->destroy();
            bullets_.erase(it++);
        }
        else
        {
            ++it;
        }
    }


    //wprintf(L"스킬 컴포넌트 업데이트!\n");
}

void skill_component::fire(bullet::type type, const vector3& dir)
{
    wprintf(L"FIRE!!!!\n");
    bullet_id bullet_object_id = 0;

    auto speed = 5.0f;
    auto distance = 20.0f;
    auto power = 10.0f;

    // 추후 factory 처리
    std::unique_ptr<bullet> bullet_object = nullptr;
    if (type == bullet::type::default_bullet)
    {
        vector3 size(2.0f, 0.0f, 2.0f);
        bullet_object = std::make_unique<default_bullet>(object_, dir, size, speed, distance, power);
    }

    if (bullet_object)
    {
        noti_fire(type, object_->get_object_id(), bullet_object_id, object_->get_pos(), dir, speed, distance);
        bullet_object_id = reinterpret_cast<std::uintptr_t>(&(*bullet_object));
        bullets_[bullet_object_id] = std::move(bullet_object);
    }
}

void skill_component::noti_fire(bullet::type type, object_id obj_id, bullet_id bullet_obj_id, const vector3& pos, const vector3& dir, float speed, float distance) const
{
    // view_list에게 bullet정보를 전달해줌
    GAME::SC_NOTI_FIRE noti;

    noti.set_obj_id(obj_id);
    noti.set_bullet_id(bullet_obj_id);
    noti.set_bullet_type(to_integral(type));

    noti.set_pos_x(pos.X);
    noti.set_pos_y(pos.Y);
    noti.set_pos_z(pos.Z);

    auto bullet_info = noti.add_bullet_infos();
    bullet_info->set_dir_x(dir.X);
    bullet_info->set_dir_y(dir.Y);
    bullet_info->set_dir_z(dir.Z);

    bullet_info->set_speed(speed);
    bullet_info->set_distance(distance);

    auto& view_list = object_->get_field()->get_view_list();
    for (auto view : view_list)
    {
        auto other = view.second;
        auto other_session = other->get_session();
        if (other_session)
        {
            send_packet(other_session, opcode::SC_NOTI_FIRE, noti);
        }
    }
}
