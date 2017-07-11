#include "bullet.h"
#include "../../../object/object.h"
#include "../../../field/field.h"

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
    
    // 이 충돌 부분 속도관련 업데이트 필요
    auto& view_list = object_->get_field()->get_view_list();
    for (auto view : view_list)
    {
        auto other = view.second;

        if (other->get_object_id() == object_->get_object_id()) continue;

        auto stat_info = other->get_stat_info();
        if (check_intersection(pos_, other->get_pos(), size_, stat_info->size))
        {
            wprintf(L"충돌체에 부딪혀서 총알 파괴\n");
            destroy_ = true;
            return;
        }
    }

    pos_ = pos_ + (dir_ * speed_ * delta);
    wprintf(L"총알 이동중 x: %f, z: %f\n", pos_.X, pos_.Z);
}

void bullet::destroy() const
{

}

void bullet::set_bullet_id(bullet_id id)
{
    id_ = id;
}

bool bullet::over_distance() const
{
    if (distance(from_, pos_) > distance_) return true;
        
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
