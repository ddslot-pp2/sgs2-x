#!/usr/bin/env python3
#-*- coding: utf-8 -*-

import xml.etree.ElementTree as ET
import os
import subprocess
import fnmatch
import sys
import operator

BUILD_CONFIGURATION = 'Debug'
#BUILD_CONFIGURATION = 'Release'

SERVER_OUT_CPP_PATH = '../../sgs2/src/packet_processor'

# ----------------------------------
# 서버 기준 파싱 .proto 생성
# ----------------------------------
print ('create .proto')
packet_xml = ET.parse('packet.xml')
root = packet_xml.getroot()

for package in root:
	target = open(package.tag + '.proto', 'w')

	target.write('syntax = "proto3";\n')
	target.write('\n')
	target.write('package ' + package.tag + ';\n')
	target.write('\n')
	
	for packet in package:
		# packet
		if 'type' not in packet.attrib:
				print (packet.tag)

				child_count = 1
				target.write('message ' + packet.tag + '\n')
				target.write('{\n')

				for child in packet:
					if 'repeated' in child.attrib:
						target.write('\t' + 'repeated ' + child.attrib['type'] + ' ' + child.tag + ' = ' +  str(child_count) + ';\n');
					else:
						target.write('\t' + child.attrib['type'] + ' ' + child.tag + ' = ' +  str(child_count) + ';\n');
					child_count = child_count + 1
					
				target.write('}\n')
				target.write('\n')
		else:
			if 'enum' == packet.attrib['type'].lower():
			
				target.write('enum ' + packet.tag + '\n')
				target.write('{\n')

				enum_count = 0
				for child in packet:
					target.write('\t' + child.tag + ' = ' +  str(enum_count) + ';\n');
					enum_count = enum_count + 1


				target.write('}\n')
				target.write('\n')

	target.close()

#----------------------------------------------
# 서버용 패킷 핸들러 packet_processor.h
#----------------------------------------------
print ('create packet_processor.h')
target = open(SERVER_OUT_CPP_PATH + '/' + 'packet_processor.h', 'w')
target.write('#ifndef __PACKET_PROCESSOR_H\n')
target.write('#define __PACKET_PROCESSOR_H\n')
target.write('\n')

target.write('#include <memory>\n')
target.write('#include "../../../network/src/io_helper.h"\n')

target.write('\n')

for child in root:
	header = 'packet/' + child.tag + '.pb.h'

	target.write('#include "' + header + '"\n')

target.write('\n')

target.write('using buf_ptr = std::shared_ptr<network::packet_buffer_type>;\n')
target.write('\n')

target.write('class server_session;\n')
target.write('\n')


for child in root:
	for packet in child:
		# packet
		if 'type' not in packet.attrib:
			if 'cs' in packet.tag.lower():
				#target.write("void handle_" + child.tag + '_' + packet.tag + "(std::shared_ptr<server_session> session, const " + child.tag + '::' + packet.tag + '& read);\n')
				target.write("void handle_" + packet.tag + "(std::shared_ptr<server_session> session, const " + child.tag + '::' + packet.tag + '& read);\n')

target.write('\n')
target.write('\n')
target.write('void register_handlers();\n')
target.write('void handle_packet(std::shared_ptr<server_session> session, buf_ptr buffer, int size);\n')

target.write('\n')
#target.write('}\n')


target.write('\n')
target.write('\n')
target.write('#endif\n')
target.close()

#----------------------------------------------
# 서버용 패킷 핸들러 packet_processor.cpp
#----------------------------------------------
print ('create packet_processor.cpp')
target = open(SERVER_OUT_CPP_PATH + '/' + 'packet_processor.cpp', 'w')
target.write('#include "packet_processor.h"\n')
target.write('#include <array>\n')
target.write('#include <google/protobuf/io/zero_copy_stream_impl_lite.h>\n')
target.write('#include "opcode.h"\n')
target.write('#include "../server_session/server_session.h"\n')

target.write('\n')
target.write('\n')

target.write('template <typename T, typename = typename std::enable_if_t<std::is_base_of<::google::protobuf::Message, T>::value>>\n')
target.write('void deserialize(std::shared_ptr<server_session> session, buf_ptr buffer, int size, std::function<void(std::shared_ptr<server_session>, const T&)> process_function)\n')
target.write('{\n')
target.write('\tgoogle::protobuf::io::ArrayInputStream is(buffer->data() + sizeof(unsigned short), size - sizeof(unsigned short));\n')
target.write('\tT read;\n')
target.write('\n')

target.write('\ttry\n')
target.write('\t{\n')
target.write('\t\tauto r = read.ParseFromZeroCopyStream(&is);\n')
target.write('\t\tif (!r)\n')
target.write('\t\t{\n')
target.write('\t\t\tsession->close();\n')
target.write('\t\t\treturn;\n')
target.write('\t\t}\n')
target.write('\t\tprocess_function(session, read);\n')
target.write('\t}\n')
target.write('\tcatch (std::logic_error& e)\n')
target.write('\t{\n')

target.write('\t}\n')
target.write('\tcatch (std::exception& e)\n');
target.write('\t{\n')

target.write('\t}\n')
target.write('}\n') # end deserialize
target.write('\n')
target.write('using packet_handler = std::function<void(std::shared_ptr<server_session> session, buf_ptr buffer, int size)>;\n')
target.write('packet_handler packet_handlers[(std::numeric_limits<unsigned short>::max)()] = { nullptr };\n')
target.write(' auto to_index = [](opcode code)\n')
target.write('{\n')
target.write('\treturn static_cast<std::underlying_type_t<opcode>>(code);\n')
target.write('};\n')

target.write('\n')

target.write('void register_handlers()\n')
target.write('{\n')
target.write('\tfor (auto& handler : packet_handlers)\n')
target.write('\t{\n')
target.write('\t\thandler = [](std::shared_ptr<server_session> session, buf_ptr const buffer, int size)\n')
target.write('\t\t{\n')
target.write('\t\t\treturn;\n')
target.write('\t\t};\n')
target.write('\t}\n')

for child in root:
	for packet in child:
		# packet
		if 'type' not in packet.attrib:
			if 'cs' in packet.tag.lower():
				#target.write('\t' + "packet_handlers[to_index(opcode::" + packet.tag + ')] = [](std::shared_ptr<server_session> session, buf_ptr buffer, int size) { deserialize<' + child.tag + '::' + packet.tag + '>(std::move(session), std::move(buffer), size, handle_' + child.tag + '_' +  packet.tag + '); };\n')
				target.write('\t' + "packet_handlers[to_index(opcode::" + packet.tag + ')] = [](std::shared_ptr<server_session> session, buf_ptr buffer, int size) { deserialize<' + child.tag + '::' + packet.tag + '>(std::move(session), std::move(buffer), size, handle_' + packet.tag + '); };\n')

target.write('}\n')

target.write('\n')
target.write('void handle_packet(std::shared_ptr<server_session> session, buf_ptr buffer, int size)\n')
target.write('{\n')
target.write('\tif (size < sizeof(opcode) || size - sizeof(unsigned short) < 0)\n')
target.write('\t{\n')
target.write('\t\treturn;\n')
target.write('\t}\n')
target.write('\n')
target.write('\tauto packet_num = *reinterpret_cast<opcode*>(buffer->data());\n')
target.write('\n')
target.write('\tpacket_handlers[to_index(packet_num)](std::move(session), std::move(buffer), size);\n')
target.write('}\n')

target.close()


#----------------------------------------------
# opcde.h 생성 해주기
#----------------------------------------------
print ('create opcode.h')
target = open(SERVER_OUT_CPP_PATH + '/' + 'opcode.h', 'w')
target.write('#ifndef __OPCODE_H\n')
target.write('#define __OPCODE_H\n')
target.write('\n')
#target.write('namespace network\n')
#target.write('{\n')
target.write('  enum class opcode : unsigned short\n')
target.write('  {\n')


value = 0
for child in root:
	value = child.attrib['start']
	for packet in child:
		if 'type' not in packet.attrib and 'struct' not in packet.attrib:
			target.write('\t\t' + packet.tag + ' = ' + str(value) + ',\n')
			value = int(value) + 1	


target.write('  };\n')
#target.write('}\n')

#target.write('\n')
target.write('#endif')
target.write('\n')
target.close()


#----------------------------------------------
# packet.h/.cc 생성 해주기
#----------------------------------------------
print ('create .h .cc')
PATH = os.getcwd()
PROTOC_PATH = '../../protobuf-master/cmake/build/solution/' + BUILD_CONFIGURATION 


protos = []

files = [f for f in os.listdir('.') if os.path.isfile(f)]
for f in files:
    extension = os.path.splitext(f)[1][1:]
    if extension == 'proto':
        protos.append(f);


os.chdir(PROTOC_PATH)
for proto in protos:
	print(proto)
	cmd =  "protoc "  + ' -I="../../../../../data/protobuf" --cpp_out="../../../../../sgs2/src/packet_processor/packet" ' +  "../../../../../data/protobuf/" + proto
	os.system(cmd)

os.chdir(PATH)


# ----------------------------------
# 모든 proto 삭제
# ----------------------------------
print ('delete .proto')
for proto in protos:
	os.remove('./' + proto)