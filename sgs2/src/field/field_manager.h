#ifndef __FIELD_MANAGER_H
#define __FIELD_MANAGER_H

#include <memory>
#include <map>
#include "../predeclare.h"
#include "field.h"

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

    std::vector<std::shared_ptr<field>> fields_;
};

#endif
