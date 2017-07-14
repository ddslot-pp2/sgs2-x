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
    wprintf(L"스킬 컴포넌트 소멸자 호출\n");
}

void skill_component::update(float delta)
{
    //super::update(delta);

    /*
    for (auto& kv : bullets_)
    {
        auto& bullet = kv.second;
        if (bullet->get_destroy())
        {

        }
    }
    */

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

void skill_component::destroy()
{
    wprintf(L"skill_component destroy 호출\n");
    for (auto& kv : bullets_)
    {
        kv.second->destroy();
    }

    bullets_.clear();
}


void skill_component::fire(bullet::type type, const vector3& pos, const vector3& dir, const vector3& bullet_dir)
{
    wprintf(L"FIRE!!!!\n");
    bullet_id bullet_object_id = 0;

    //auto speed = 25.0f;
    const auto speed = object_->get_stat_info()->bullet_speed.load();
    const auto power = object_->get_stat_info()->bullet_power.load();
    const auto distance = object_->get_stat_info()->bullet_distance.load();
    vector3 size(0.0f, 0.0f, 0.0f);
    // 추후 factory 처리
    std::unique_ptr<bullet> bullet_object = nullptr;
    if (type == bullet::type::default_bullet)
    {
        size = vector3(2.0f, 2.0f, 2.0f);
        bullet_object = std::make_unique<default_bullet>(object_, bullet_dir, size, speed, distance, power);
    }

    if (bullet_object)
    {
        bullet_object_id = reinterpret_cast<std::uintptr_t>(&(*bullet_object));
        bullet_object->set_bullet_id(bullet_object_id);
        noti_fire(type, object_->get_object_id(), bullet_object_id, pos, dir, bullet_dir, size, speed, distance);
        bullets_[bullet_object_id] = std::move(bullet_object);
    }
}

// 구조체로 변경하자...
void skill_component::noti_fire(bullet::type type, object_id obj_id, bullet_id bullet_obj_id, const vector3& pos, const vector3& dir, const vector3& bullet_dir, const vector3& size, float speed, float distance) const
{
    // view_list에게 bullet정보를 전달해줌
    GAME::SC_NOTI_FIRE noti;

    noti.set_obj_id(obj_id);
    noti.set_bullet_type(to_integral(type));

    noti.set_pos_x(pos.X);
    noti.set_pos_y(pos.Y);
    noti.set_pos_z(pos.Z);

    noti.set_dir_x(dir.X);
    noti.set_dir_y(dir.Y);
    noti.set_dir_z(dir.Z);

    auto bullet_info = noti.add_bullet_infos();

    bullet_info->set_bullet_id(bullet_obj_id);

    bullet_info->set_dir_x(bullet_dir.X);
    bullet_info->set_dir_y(bullet_dir.Y);
    bullet_info->set_dir_z(bullet_dir.Z);

    bullet_info->set_size_x(size.X);
    bullet_info->set_size_y(size.Y);
    bullet_info->set_size_z(size.Z);

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

void skill_component::volley_fire(bullet::type type, const vector3& pos, const vector3& dir, int count, const std::array<vector3, 4>& dirs)
{
    wprintf(L"VOLLEY FIRE!!!!\n");
    bullet_id bullet_object_id = 0;

    const auto speed = object_->get_stat_info()->bullet_speed.load();
    const auto power = object_->get_stat_info()->bullet_power.load();
    const auto distance = object_->get_stat_info()->bullet_distance.load();

    std::array<bullet_id, 4> bullet_obj_ids;
    std::array<vector3, 4>   sizes;

    for (auto i = 0; i < count; ++i)
    {
        vector3 size(0.0f, 0.0f, 0.0f);
        // 추후 factory 처리
        std::unique_ptr<bullet> bullet_object = nullptr;
        if (type == bullet::type::default_bullet)
        {
            size = vector3(2.0f, 2.0f, 2.0f);
            sizes[i] = size;
            bullet_object = std::make_unique<default_bullet>(object_, dirs[i], size, speed, distance, power);
        }

        if (bullet_object)
        {
            bullet_object_id = reinterpret_cast<std::uintptr_t>(&(*bullet_object));
            bullet_object->set_bullet_id(bullet_object_id);

            bullet_obj_ids[i] = bullet_object_id;
            bullets_[bullet_object_id] = std::move(bullet_object);
        }
    }

    if (count > 0)
    {
        noti_volley_fire(type, object_->get_object_id(), bullet_obj_ids, pos, dir, count, dirs, sizes, speed, distance);
    }

}

void skill_component::noti_volley_fire(bullet::type type, object_id obj_id, std::array<bullet_id, 4> bullet_obj_ids, const vector3& pos, const vector3& dir, int count, const std::array<vector3, 4>& bullet_dirs, const std::array<vector3, 4>& sizes, float speed, float distance) const
{
    // view_list에게 bullet정보를 전달해줌
    GAME::SC_NOTI_FIRE noti;

    noti.set_obj_id(obj_id);
    noti.set_bullet_type(to_integral(type));

    noti.set_pos_x(pos.X);
    noti.set_pos_y(pos.Y);
    noti.set_pos_z(pos.Z);

    noti.set_dir_x(dir.X);
    noti.set_dir_y(dir.Y);
    noti.set_dir_z(dir.Z);

    for (auto i = 0; i < count; ++i)
    {
        auto bullet_info = noti.add_bullet_infos();

        bullet_info->set_bullet_id(bullet_obj_ids[i]);

        bullet_info->set_dir_x(bullet_dirs[i].X);
        bullet_info->set_dir_y(bullet_dirs[i].Y);
        bullet_info->set_dir_z(bullet_dirs[i].Z);

        bullet_info->set_size_x(sizes[i].X);
        bullet_info->set_size_y(sizes[i].Y);
        bullet_info->set_size_z(sizes[i].Z);

        bullet_info->set_speed(speed);
        bullet_info->set_distance(distance);
    }

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

void skill_component::reset()
{
    super::reset();
    bullets_.clear();
}