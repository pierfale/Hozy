#include "network/NetAddress.hpp"
#include <iostream>

NetAddress::NetAddress(const std::string& name) : _address(nullptr), _size(0), _type(ADDRESS_TYPE_UNDEFINED) {
	struct addrinfo* addr_info;
	struct addrinfo addr_info_conf;

	memset(&addr_info_conf, 0, sizeof(struct addrinfo));
	addr_info_conf.ai_family = AF_UNSPEC;

	if(getaddrinfo(name.c_str(), NULL, &addr_info_conf, &addr_info) != 0)
		throw_error(E_ADDRESS_NOT_FOUND);

	if(addr_info->ai_family == AF_INET) {
/*
		while(addr_info != NULL) {
			std::cout << ">>" << inet_ntoa(((struct sockaddr_in *)addr_info->ai_addr)->sin_addr) << std::endl;
			addr_info = addr_info->ai_next;
		}
*/
        _address = (sockaddr*)malloc(addr_info->ai_addrlen);
        std::memcpy(_address, addr_info->ai_addr, addr_info->ai_addrlen);
        _size = addr_info->ai_addrlen;
        _type = IPV4;
		freeaddrinfo(addr_info);
	}
	else if(addr_info->ai_family == AF_INET6) {
        _address = (sockaddr*)malloc(addr_info->ai_addrlen);
        std::memcpy(_address, addr_info->ai_addr, addr_info->ai_addrlen);
        _size = addr_info->ai_addrlen;
        _type = IPV6;
		freeaddrinfo(addr_info);
	}
	else
		throw_error(E_ADDRESS_NOT_FOUND);
}

NetAddress::NetAddress(const NetAddress& origin) : _address(nullptr),_size(0), _type(ADDRESS_TYPE_UNDEFINED) {
    operator=(origin);
}

NetAddress::~NetAddress() {
    free(_address);
}

NetAddress NetAddress::getLocalAdress() {
    return NetAddress("127.0.0.1");
}

struct sockaddr* NetAddress::address() const {
    return _address;
}

NetAddress::AddressType NetAddress::type() const {
    return _type;
}

std::string NetAddress::to_string() const {
    if(_type == IPV4) {
        uint8_t* addr = (uint8_t*)&((sockaddr_in*)_address)->sin_addr.s_addr;
        return ct::to_string((int)*addr)+"."+ct::to_string((int)*(addr+1))+"."+ct::to_string((int)*(addr+2))+"."+ct::to_string((int)*(addr+3));
    }
    return "";
}

NetAddress& NetAddress::operator=(const NetAddress& origin) {
    _size = origin._size;
    _type = origin._type;
    _address = (struct sockaddr*)malloc(_size);
    std::memcpy(_address, origin._address, _size);
    return *this;
}
