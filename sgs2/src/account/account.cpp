#include "account.h"
#include <algorithm>

account::account(const account_info& acc_info) : account_id_(acc_info.id), nickname_(acc_info.nickname), medal_count_(acc_info.medal_count), coin_count_(acc_info.coin_count)
{

}

account::~account()
{

}

account_id account::get_account_id() const
{
    return account_id_;
}

const std::wstring& account::get_nickname() const
{
    return nickname_;
}

int account::get_medal_count() const
{
    return medal_count_.load();
}

int account::get_coin_count() const
{
    return coin_count_.load();
}

void account::inc_medal_count()
{
    ++medal_count_;
}

void account::inc_coin_count()
{
    ++coin_count_;
}

void account::dec_medal_count(int count)
{
    medal_count_ = std::max(0, medal_count_ - count);
}

void account::dec_coin_count(int count)
{
    coin_count_ = std::max(0, coin_count_ - count);
}

account_info account::to_account_info() const
{
    account_info acc_info;
    acc_info.id = account_id_;
    acc_info.nickname = nickname_;
    acc_info.medal_count = medal_count_;
    acc_info.coin_count = coin_count_;

    return acc_info;
}
