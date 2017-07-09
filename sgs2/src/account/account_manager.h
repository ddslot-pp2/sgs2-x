#ifndef __ACCOUNT_MANAGER_H
#define __ACCOUNT_MANAGER_H

#include <memory>
#include <map>
#include "../predeclare.h"
#include "account.h"

class account_manager
{
public:
    static account_manager& instance() {
        static account_manager instance;
        return instance;
    }

    explicit account_manager() = default;
    account_manager(const account_manager& other) = delete;
    account_manager& operator=(const account_manager& other) = delete;

    std::map<account_id, std::unique_ptr<account>> accounts_;
};

#endif
