#ifndef __FIELD_MANAGER_H
#define __FIELD_MANAGER_H

#include <memory>
#include <map>
#include "../predeclare.h"
#include "field.h"

using field_ptr = std::shared_ptr<field>;

class field_manager
{
public:
    static field_manager& instance() {
        static field_manager instance;
        return instance;
    }

    explicit field_manager() = default;
    field_manager(const field_manager& other) = delete;
    field_manager& operator=(const field_manager& other) = delete;

    void create_fields();
    void destroy_fields();

    void update_fields();

    void request_field_status(std::shared_ptr<server_session> session);
    void try_enter_field(int field_id, std::shared_ptr<server_session> session);
 
    field_ptr field(field_id id) { return fields_[id]; }

    std::vector<field_ptr> fields_;
};

#endif
