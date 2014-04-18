#ifndef PACKET_HPP
#define PACKET_HPP

#include "tool/Buffer.hpp"
#include "tool/error/ErrorManager.hpp"

class Packet {

public:
	Packet();

    Packet& operator<<(int32_t data);
    Packet& operator<<(uint32_t data);

    Packet& operator>>(int32_t& data);
    Packet& operator>>(uint32_t& data);

private:
    void get(void* data, std::size_t size);
	Buffer<uint8_t> _buffer;
    unsigned int _out_cursor;

};

#endif
