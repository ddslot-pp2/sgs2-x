#ifndef __ACCOUNT_H
#define __ACCOUNT_H

#include <atomic>
#include "../predeclare.h"

// db의 값과 매치되지 않을까 싶다
struct account_info
{
    account_id id;
    std::wstring nickname;
    int medal_count;
    int coin_count;
};

class account
{
public:
    explicit account(const account_info& acc_info);
    ~account();

    account_id get_account_id() const;

    const std::wstring& get_nickname() const;

    int get_medal_count() const;
    int get_coin_count() const;

    void inc_medal_count();
    void inc_coin_count();

    account_info to_account_info() const;

private:
    account_id account_id_;
    std::wstring nickname_;
    std::atomic<int> medal_count_;
    std::atomic<int> coin_count_;
};

#endif
