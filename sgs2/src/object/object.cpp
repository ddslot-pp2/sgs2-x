#include "object.h"
#include "../field/field.h"
#include "../packet_processor/packet/GAME.pb.h"
#include "../packet_processor/opcode.h"
#include "../packet_processor/send_helper.h"

object::object(field_id id) : field_id_(id), field_(nullptr)
{
    wprintf(L"오브젝트 생성자 호출\n");
}

object::~object()
{
    wprintf(L"오브젝트 소멸자 호출\n");
}

std::shared_ptr<component> object::get_component(comp_id id)
{
    return components_[id];
}

void object::initialize()
{
    components_[comp_id::move_comp] = std::make_shared<move_component>(this);

    // session_ 한테 물어서 stat_info를 가져온다;
    // 예를들어 사이즈, 스피드 등등
    stat_ = std::make_shared<stat_info>();
    stat_->hp = 100;
    stat_->speed = 10.0f;
    stat_->size = vector3(2.0f, 2.0, 2.0f);
}

void object::update(float delta)
{
    for (auto& comp : components_)
    {
        comp.second->process_task();
        comp.second->update(delta);
    }
}

void object::set_object_id(size_t obj_id) noexcept
{
    object_id_ = obj_id;
}

size_t object::get_object_id() const
{
    return object_id_;
}

void object::set_pos(const vector3& pos)
{
    //wprintf(L"position 업데이트\n");
    //wprintf(L"x: %f, z: %f\n", pos.X, pos.Z);
    pos_ = pos;

    GAME::SC_NOTI_OTHER_MOVE noti;
    noti.set_obj_id(object_id_);
    noti.set_pos_x(pos_.X);
    noti.set_pos_y(pos_.Y);
    noti.set_pos_z(pos_.Z);
    
    auto& view_list = field_->get_view_list();
    for (auto view : view_list) 
    {
        auto other = view.second;
        if (object_id_ == other->get_object_id()) continue;

        auto other_session = other->get_session();
        if (other_session)
        {
            send_packet(other_session, opcode::SC_NOTI_OTHER_MOVE, noti);
        }
    }

}

vector3 object::get_pos()
{
    return pos_;
}
