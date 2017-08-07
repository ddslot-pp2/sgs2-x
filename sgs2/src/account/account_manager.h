#ifndef __ACCOUNT_MANAGER_H
#define __ACCOUNT_MANAGER_H

#include <memory>
#include <map>
#include <mutex>
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

    std::shared_ptr<account> add_account(const account_info& acc_info);
    void del_account(const account_id id);
    
    void leave_account(const account_id id);

private:
    std::mutex account_lock_;
    std::map<account_id, std::shared_ptr<account>> accounts_;
};

#endif
