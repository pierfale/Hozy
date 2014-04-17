#ifndef PACKET_HPP
#define PACKET_HPP

#include "tool/Buffer.hpp"

class Packet {

public:
	Packet();

private:
	Buffer<uint8_t> _buffer;



};

#endif
