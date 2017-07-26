#include "account.h"

account::account(const account_info& acc_info) : account_id_(acc_info.id), medal_count_(acc_info.medal_count), coin_count_(acc_info.coin_count)
{

}

account::~account()
{

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

account_info account::to_account_info() const
{
    account_info acc_info;
    acc_info.id = account_id_;
    acc_info.medal_count = medal_count_;
    acc_info.coin_count = coin_count_;

    return acc_info;
}
