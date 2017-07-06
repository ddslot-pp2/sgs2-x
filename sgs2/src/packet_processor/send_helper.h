#ifndef __SEND_HELPER_H
#define __SEND_HELPER_H

#include "static_if.h"
#include "opcode.h"
#include "../../../network/src/io_helper.h"
#include <google/protobuf/io/zero_copy_stream_impl_lite.h>

template <class Protobuf>
bool serialize_packet(opcode opcode, Protobuf protobuf, char* buffer, unsigned short& written)
{
    auto ret = false;
    static_if<std::is_pointer<Protobuf>::value>([&](auto f)
    {
        written = protobuf->ByteSize();
        google::protobuf::io::ArrayOutputStream os(buffer, written);
        ret = protobuf->SerializeToZeroCopyStream(&os);
    }).else_([&](auto f)
    {
        written = protobuf.ByteSize();
        google::protobuf::io::ArrayOutputStream os(buffer, written);
        ret = protobuf.SerializeToZeroCopyStream(&os);
    });

    return ret;
}

template <class Session, class Protobuf>
void send_packet(Session session, opcode opcode, Protobuf protobuf)
{
    using namespace network;
    auto buffer = std::make_shared<send_buffer>();

    // copy opcode
    std::memcpy(buffer->buf.data() + sizeof(unsigned short), &opcode, sizeof(unsigned short));

    auto r = serialize_packet(opcode, protobuf, buffer->buf.data() + sizeof(unsigned short)*2, buffer->size);

    if (r)
    {
        // header size
        buffer->size = buffer->size + sizeof(unsigned short);
        std::memcpy(buffer->buf.data(), &(buffer->size), sizeof(unsigned short));

        // total packet size
        buffer->size = buffer->size + sizeof(unsigned short);
        session->send(buffer);
    }
    else
    {
        // error 
    }
}

#endif
