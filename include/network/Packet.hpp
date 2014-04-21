#ifndef PACKET_HPP
#define PACKET_HPP

#define PACKET_CHECK 0x9C4A

#include "tool/Buffer.hpp"
#include "tool/error/ErrorManager.hpp"
#include "network/PacketType.hpp"

class Packet {

    friend class SocketTcp;

public:
	Packet();
	Packet(PacketType type);

    Packet& operator<<(int32_t data);
    Packet& operator<<(uint32_t data);
	Packet& operator<<(std::string data);

    Packet& operator>>(int32_t& data);
    Packet& operator>>(uint32_t& data);
	Packet& operator>>(std::string& data);

	struct Header {
		uint16_t check_code;
		uint16_t type;
		uint32_t size;
	} __attribute__((__packed__));

	std::string to_string();

private:
    void get(void* data, std::size_t size);
	void add_size(std::size_t size);
	Buffer<uint8_t> _buffer;
    unsigned int _out_cursor;



};

#endif
