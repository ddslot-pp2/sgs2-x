#include "server_session.h"
#include "../packet_processor/packet_processor.h"
#include "../packet_processor/send_helper.h"
#include "../field/field_manager.h"
#include "../account/account_manager.h"

server_session::server_session(tcp::socket socket) : session(std::move(socket)), account_id_(0), account_(nullptr), character_(nullptr), character_type_(0)
{
    
}

server_session::~server_session()
{

}

void server_session::on_read_packet(std::shared_ptr<network::packet_buffer_type> buf, unsigned short size)
{
    //wprintf(L"server_session on_read_packet called\n");
    auto self = std::static_pointer_cast<server_session>(shared_from_this());
    handle_packet(self, buf, size);
}

void server_session::on_connect()
{
    wprintf(L"server_session on_connected called\n");

    /*
    LOBBY::SC_LOG_IN send;
    send.set_result(true);
    send.set_timestamp(200000);
    send_packet(shared_from_this(), opcode::SC_LOG_IN, send);
    */
}

void server_session::on_disconnect(boost::system::error_code& ec)
{
    wprintf(L"on disconnect with error\n");
    if (character_)
    {
        wprintf(L"케릭터가 존재함\n");
        leave_field(character_);
    }

    if (account_)
    {
        account_manager::instance().del_account(account_->get_account_id());
    }
}

void server_session::on_disconnect()
{
    wprintf(L"on disconnect\n");
    if (character_)
    {
        wprintf(L"케릭터가 존재함\n");
        leave_field(character_);
    }

    if (account_)
    {
        account_manager::instance().del_account(account_->get_account_id());
    }
}

void server_session::leave_field(std::shared_ptr<character> c) const
{
    auto field_id = c->get_field_id();
    auto field = field_manager::instance().get_field(field_id);
    field->send_task(&field::leave_field, c->get_object_id());
}

void server_session::set_account(account_ptr acc)
{
    account_ = acc;
}

account_ptr server_session::get_account() const
{
    return account_;
}

void server_session::set_character(character_ptr character)
{
    character_ = character;
}

std::shared_ptr<character> server_session::get_character() const
{
    return character_;
}

void server_session::set_stat_info(const stat_info& info)
{
    auto stat = std::make_shared<stat_info>();
    stat->max_hp          = info.max_hp.load();
    stat->speed           = info.speed.load();
    stat->bullet_speed    = info.bullet_speed.load();
    stat->bullet_power    = info.bullet_power.load();
    stat->bullet_distance = info.bullet_distance.load();
    stat->reload_time     = info.reload_time.load();

    // 로직에서 get / set 이 동시에 일어나면 안됨 => 동시에 일어나면 atomic_exchange 사용해야함
    stat_ = stat;
}

std::shared_ptr<stat_info> server_session::get_stat_info() const
{
    // 로직에서 get / set 이 동시에 일어나면 안됨 => 동시에 일어나면 atomic_load 사용해야함
    return stat_;
}
