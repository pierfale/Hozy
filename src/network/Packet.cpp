#include "network/Packet.hpp"

Packet::Packet() : Packet(P_UNDEFINED) {

}

Packet::Packet(PacketType type) : _buffer(), _out_cursor(0) {
	uint32_t header_1 = 0;
	_buffer.add((uint8_t*)&header_1, sizeof(uint32_t ));

	uint32_t header_2 = type;
	_buffer.add((uint8_t*)&header_2, sizeof(uint32_t ));

	_out_cursor = 2*sizeof(uint32_t);
}

Packet& Packet::operator<<(int32_t data) {
    _buffer.add((uint8_t*)&data, sizeof(int32_t));
    return *this;
}

Packet& Packet::operator<<(uint32_t data) {
    _buffer.add((uint8_t*)&data, sizeof(uint32_t));
    return *this;
}

Packet& Packet::operator>>(int32_t& data) {
    get(&data, sizeof(int32_t));
    return *this;
}

Packet& Packet::operator>>(uint32_t& data) {
    get(&data, sizeof(uint32_t));
    return *this;
}

void Packet::get(void* data, std::size_t size) {
    if(_out_cursor+size > _buffer.get_size())
        throw_error(E_PACKET_EMPTY);

    memcpy(data, _buffer.get(_out_cursor), size);
    _out_cursor += size;
}
