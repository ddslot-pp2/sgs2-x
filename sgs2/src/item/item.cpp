#include "item.h"
#include "../field/field_manager.h"
#include "../field/field.h"

item::item(field_id id, std::chrono::milliseconds reactive_time, const vector3& pos) : field_id_(id), reactive_time_(reactive_time), pos_(pos), active_(true)
{
    field_ = field_manager::instance().get_field(id);
    active_timer_ = std::make_unique<timer_ptr::element_type>(network::io_service());
}

item::~item()
{

}

void item::update(float delta)
{

}

bool item::check_intersection(const vector3& character_pos, const vector3& character_size) const
{
    const auto half_x = (size_.X / 2.0f);
    const auto half_z = (size_.Z / 2.0f);

    const auto character_half_x = (character_size.X / 2.0f);
    const auto character_half_z = (character_size.Z / 2.0f);

    //printf("enemy => x: %f, y: %f, z: %f\n", object_pos.X, object_pos.Y, object_pos.Z);
    auto a_min_x = pos_.X - half_x;
    auto a_max_x = pos_.X + half_x;
    auto a_min_z = pos_.Z - half_z;
    auto a_max_z = pos_.Z + half_z;

    auto b_min_x = character_pos.X - character_half_x;
    auto b_max_x = character_pos.X + character_half_x;
    auto b_min_z = character_pos.Z - character_half_z;
    auto b_max_z = character_pos.Z + character_half_z;


    if (a_max_x < b_min_x || a_min_x > b_max_x) return false;
    if (a_max_z < b_min_z || a_min_z > b_max_z) return false;

    return true;
}

void item::destroy()
{
    active_timer_->cancel();
    active_ = false;
}
