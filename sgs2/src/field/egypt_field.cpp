#include "egypt_field.h"

egypt_field::egypt_field(unsigned int field_id) : field(field_id)
{

}

egypt_field::~egypt_field()
{

}

void egypt_field::initialize()
{

}

void egypt_field::update(float delta)
{
    if (field_id_ == 0)
    {
        wprintf(L"id: %d, delta: %f\n", field_id_, delta);
    }
}