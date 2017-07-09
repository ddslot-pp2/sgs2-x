#include "field_manager.h"
#include "egypt_field.h"
#include "io_helper.h"

void field_manager::create_fields() 
{
    for (auto i = 0; i < 50; ++i)
    {
        fields_.emplace_back(std::make_shared<egypt_field>(i));
    }
}

void field_manager::destroy_fields()
{
    for (auto field : fields_)
    {
        //fields_->on_destry();
    }
}

void field_manager::update_fields()
{
    using namespace network;
    for (auto field : fields_)
    {   
        if (field->check_update_flag())
        {

            io_service().post([field] {
                field->try_update();
            });
        }
    }

    network::io_service().post([] {
        field_manager::instance().update_fields();
    });
}
