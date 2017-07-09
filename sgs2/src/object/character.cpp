#include "character.h"
#include "../field/field.h"

using super = object;

character::character(field_id id, std::shared_ptr<server_session> session) : object(id), session_(session)
{

}

character::~character()
{

}

void character::initialize()
{
    super::initialize();
}

void character::update(float delta)
{
    super::update(delta);
}

void character::leave_field() const
{
    if (field_)
    {
        //field_->send_task(&field::enter_field, session_);
        //fields_[field_id]->send_task(&field::enter_field, session);
    }
}