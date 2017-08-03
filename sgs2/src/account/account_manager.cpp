#include "account_manager.h"

std::shared_ptr<account> account_manager::add_account(const account_info& acc_info)
{
    auto acc = std::make_shared<account>(acc_info);

    std::lock_guard<std::mutex> lock(account_lock_);

    auto it = accounts_.find(acc_info.id);
    if (it != accounts_.end())
    {
        return nullptr;
    }

    accounts_[acc_info.id] = acc;

    return acc;
}

void account_manager::del_account(const account_id id)
{
    wprintf(L"어카운트 삭제 시도\n");
    std::lock_guard<std::mutex> lock(account_lock_);
    accounts_.erase(id);
}