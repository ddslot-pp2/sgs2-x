#include "packet_processor.h"
#include <array>
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>
#include "opcode.h"
#include "../server_session/server_session.h"


template <typename T, typename = typename std::enable_if_t<std::is_base_of<::google::protobuf::Message, T>::value>>
void deserialize(std::shared_ptr<server_session> session, buf_ptr buffer, int size, std::function<void(std::shared_ptr<server_session>, const T&)> process_function)
{
	google::protobuf::io::ArrayInputStream is(buffer->data() + sizeof(unsigned short), size - sizeof(unsigned short));
	T read;

	try
	{
		auto r = read.ParseFromZeroCopyStream(&is);
		if (!r)
		{
			session->close();
			return;
		}
		process_function(session, read);
	}
	catch (std::logic_error& e)
	{
	}
	catch (std::exception& e)
	{
	}
}

using packet_handler = std::function<void(std::shared_ptr<server_session> session, buf_ptr buffer, int size)>;
packet_handler packet_handlers[(std::numeric_limits<unsigned short>::max)()] = { nullptr };
 auto to_index = [](opcode code)
{
	return static_cast<std::underlying_type_t<opcode>>(code);
};

void register_handlers()
{
	for (auto& handler : packet_handlers)
	{
		handler = [](std::shared_ptr<server_session> session, buf_ptr const buffer, int size)
		{
			return;
		};
	}
	packet_handlers[to_index(opcode::CS_LOG_IN)] = [](std::shared_ptr<server_session> session, buf_ptr buffer, int size) { deserialize<LOBBY::CS_LOG_IN>(std::move(session), std::move(buffer), size, handle_CS_LOG_IN); };
	packet_handlers[to_index(opcode::CS_FIELD_LIST)] = [](std::shared_ptr<server_session> session, buf_ptr buffer, int size) { deserialize<LOBBY::CS_FIELD_LIST>(std::move(session), std::move(buffer), size, handle_CS_FIELD_LIST); };
	packet_handlers[to_index(opcode::CS_ENTER_FIELD)] = [](std::shared_ptr<server_session> session, buf_ptr buffer, int size) { deserialize<LOBBY::CS_ENTER_FIELD>(std::move(session), std::move(buffer), size, handle_CS_ENTER_FIELD); };
	packet_handlers[to_index(opcode::CS_LEAVE_FIELD)] = [](std::shared_ptr<server_session> session, buf_ptr buffer, int size) { deserialize<LOBBY::CS_LEAVE_FIELD>(std::move(session), std::move(buffer), size, handle_CS_LEAVE_FIELD); };
	packet_handlers[to_index(opcode::CS_PURCHASE_CHARACTER)] = [](std::shared_ptr<server_session> session, buf_ptr buffer, int size) { deserialize<LOBBY::CS_PURCHASE_CHARACTER>(std::move(session), std::move(buffer), size, handle_CS_PURCHASE_CHARACTER); };
	packet_handlers[to_index(opcode::CS_CHARACTER_INFO)] = [](std::shared_ptr<server_session> session, buf_ptr buffer, int size) { deserialize<LOBBY::CS_CHARACTER_INFO>(std::move(session), std::move(buffer), size, handle_CS_CHARACTER_INFO); };
	packet_handlers[to_index(opcode::CS_MY_INFO)] = [](std::shared_ptr<server_session> session, buf_ptr buffer, int size) { deserialize<LOBBY::CS_MY_INFO>(std::move(session), std::move(buffer), size, handle_CS_MY_INFO); };
	packet_handlers[to_index(opcode::CS_MY_CHARACTER_INFO)] = [](std::shared_ptr<server_session> session, buf_ptr buffer, int size) { deserialize<LOBBY::CS_MY_CHARACTER_INFO>(std::move(session), std::move(buffer), size, handle_CS_MY_CHARACTER_INFO); };
	packet_handlers[to_index(opcode::CS_CHARACTER_UPGRADE)] = [](std::shared_ptr<server_session> session, buf_ptr buffer, int size) { deserialize<LOBBY::CS_CHARACTER_UPGRADE>(std::move(session), std::move(buffer), size, handle_CS_CHARACTER_UPGRADE); };
	packet_handlers[to_index(opcode::CS_CHARACTER_SELECT)] = [](std::shared_ptr<server_session> session, buf_ptr buffer, int size) { deserialize<LOBBY::CS_CHARACTER_SELECT>(std::move(session), std::move(buffer), size, handle_CS_CHARACTER_SELECT); };
	packet_handlers[to_index(opcode::CS_PING)] = [](std::shared_ptr<server_session> session, buf_ptr buffer, int size) { deserialize<GAME::CS_PING>(std::move(session), std::move(buffer), size, handle_CS_PING); };
	packet_handlers[to_index(opcode::CS_SYNC_FIELD)] = [](std::shared_ptr<server_session> session, buf_ptr buffer, int size) { deserialize<GAME::CS_SYNC_FIELD>(std::move(session), std::move(buffer), size, handle_CS_SYNC_FIELD); };
	packet_handlers[to_index(opcode::CS_NOTI_MOVE)] = [](std::shared_ptr<server_session> session, buf_ptr buffer, int size) { deserialize<GAME::CS_NOTI_MOVE>(std::move(session), std::move(buffer), size, handle_CS_NOTI_MOVE); };
	packet_handlers[to_index(opcode::CS_FIRE)] = [](std::shared_ptr<server_session> session, buf_ptr buffer, int size) { deserialize<GAME::CS_FIRE>(std::move(session), std::move(buffer), size, handle_CS_FIRE); };
	packet_handlers[to_index(opcode::CS_RESPAWN_CHARACTER)] = [](std::shared_ptr<server_session> session, buf_ptr buffer, int size) { deserialize<GAME::CS_RESPAWN_CHARACTER>(std::move(session), std::move(buffer), size, handle_CS_RESPAWN_CHARACTER); };
	packet_handlers[to_index(opcode::CS_ENHANCE_BUFF)] = [](std::shared_ptr<server_session> session, buf_ptr buffer, int size) { deserialize<GAME::CS_ENHANCE_BUFF>(std::move(session), std::move(buffer), size, handle_CS_ENHANCE_BUFF); };
}

void handle_packet(std::shared_ptr<server_session> session, buf_ptr buffer, int size)
{
	if (size < sizeof(opcode) || size - sizeof(unsigned short) < 0)
	{
		return;
	}

	auto packet_num = *reinterpret_cast<opcode*>(buffer->data());

	packet_handlers[to_index(packet_num)](std::move(session), std::move(buffer), size);
}
