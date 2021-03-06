#ifndef __SERVER_SESSION_H
#define __SERVER_SESSION_H

#include "session/session.h"
#include "../predeclare.h"
#include "../object/character.h"
#include "../account/account.h"

struct CharacterStat;
using boost::asio::ip::tcp;

using character_ptr = std::shared_ptr<character>;
using character_weak_ptr = std::weak_ptr<character>;

using account_ptr = std::shared_ptr<account>;

class server_session : public network::session
{
public:

    explicit server_session(tcp::socket socket);
    virtual ~server_session();

    void set_account(account_ptr acc);
    account_ptr get_account() const;

    void set_character(character_ptr character);
    character_ptr get_character() const;

    //void destroy_character();
    std::wstring get_tmp_nickname() const { return L"������ũ"; }
    const std::wstring& get_nickname() const { return account_->get_nickname(); }

    void set_character_type(int type) { character_type_ = type; }
    int  get_character_type() const   { return character_type_; }

    void set_stat_info(const CharacterStat& info);
    std::shared_ptr<stat_info> get_stat_info() const;

    void set_account_id(account_id id);
    account_id get_account_id() const;

    void start_ping_timer(std::chrono::milliseconds ping_time);
    bool get_ping() const { return ping_; }
    void set_ping(bool ping) { ping_ = ping; }

protected:
    virtual void on_read_packet(std::shared_ptr<network::packet_buffer_type> buf, unsigned short size) override;
    virtual void on_connect() override;
    virtual void on_disconnect(boost::system::error_code& ec) override;
    virtual void on_disconnect() override;

private:
    void leave_field(std::shared_ptr<character> c) const;
    void update_account_info() const;

    account_id account_id_;

    account_ptr   account_;
    character_ptr character_;

    int character_type_;
    std::shared_ptr<stat_info> stat_;
    //std::shared_ptr<character> character_;

    std::chrono::milliseconds ping_time_;
    timer_ptr ping_timer_;
    std::atomic<bool> ping_;
};

#endif
