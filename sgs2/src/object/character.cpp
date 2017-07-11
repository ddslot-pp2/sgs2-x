#include "character.h"
#include "../field/field.h"
#include "../field/field_manager.h"

using super = object;

character::character(field_id id, std::shared_ptr<server_session> session) : object(id), session_(session)
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
}

void character::update(float delta)
{
    super::update(delta);
}

void character::leave_field() const
{
    
    field_->send_task(&field::leave_field, object_id_);

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
