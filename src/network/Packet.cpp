#include "network/Packet.hpp"

Packet::Packet() : Packet(P_UNDEFINED) {

}

Packet::Packet(PacketType type) : _buffer(), _out_cursor(0) {

	struct Header header;

	header.check_code = PACKET_CHECK ;
    header.type = type;
	header.size = 0;

	_buffer.add((uint8_t*)&header, sizeof(struct Header));

	_out_cursor = 2*sizeof(uint32_t);

}

Packet& Packet::operator<<(int32_t data) {
    _buffer.add((uint8_t*)&data, sizeof(int32_t));
	add_size(sizeof(int32_t));
    return *this;
}

Packet& Packet::operator<<(uint32_t data) {
    _buffer.add((uint8_t*)&data, sizeof(uint32_t));
	add_size(sizeof(uint32_t));
    return *this;
}

Packet& Packet::operator<<(std::string data) {
	uint16_t size = data.size();
	_buffer.add((uint8_t*)&size, sizeof(uint16_t));
	_buffer.add((uint8_t*)data.c_str(), size);
	add_size(sizeof(uint16_t)+size);
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

Packet& Packet::operator>>(std::string& data) {
	uint16_t size;
	get(&size, sizeof(uint16_t));
    char* str = new char[size+1];
    get(str, size);
    for(unsigned int i=0; i<size; i++) {
        if(str[i] == '\0') {
            throw_error(E_PACKET_DATA);
        }
    }

	str[size] = '\0';
	data.assign(str);
    delete[] str;
	return *this;
}

void Packet::get(void* data, std::size_t size) {
    if(_out_cursor+size > _buffer.get_size())
        throw_error(E_PACKET_EMPTY);

    memcpy(data, _buffer.get(_out_cursor), size);
    _out_cursor += size;
}

void Packet::add_size(std::size_t size) {
	((struct Header*)_buffer.get_base())->size += size;
}

PacketType Packet::get_type() {
    return static_cast<PacketType>(((struct Header*)_buffer.get_base())->type);
}

std::string Packet::to_string() {
    struct Header* header = (struct Header*)_buffer.get_base();
	std::string str = "check_code : "+ct::to_hex_string(header->check_code)+"\ntype : "+ct::to_hex_string(header->type)+"\nsize : "+ct::to_string(header->size);
	for(unsigned int i = sizeof(struct Header); i<_buffer.get_size(); i++) {
		if((i-sizeof(struct Header))%16 == 0)
			str += "\n";
		str += ct::to_hex_string(*(_buffer.get_base()+i))+" ";
	}
	return str;
}
