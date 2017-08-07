#include "account_manager.h"
#include "../server_session/server_session.h"

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

void account_manager::leave_account(const account_id id)
{
    wprintf(L"유저 강제로 나가게함\n");
    std::lock_guard<std::mutex> lock(account_lock_);

    auto it = accounts_.find(id);
    if (it == accounts_.end())
    {
        return;
    }

    auto acc = it->second;
    auto sess = acc->get_session();

    if (sess)
    {
        sess->close();
    }

    accounts_.erase(id);
}
