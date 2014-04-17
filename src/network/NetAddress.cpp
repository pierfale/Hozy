#include "network/NetAddress.hpp"
#include <iostream>

NetAddress::NetAddress(const std::string& name) {
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

		std::memcpy(_address, &(((struct sockaddr_in *)addr_info->ai_addr)->sin_addr), IPV4_SIZE);
		_size = IPV4_SIZE;
		freeaddrinfo(addr_info);
	}
	else if(addr_info->ai_family == AF_INET6) {

		std::memcpy(_address, &(((struct sockaddr_in6 *)addr_info->ai_addr)->sin6_addr), IPV6_SIZE);
		_size = IPV6_SIZE;
		freeaddrinfo(addr_info);
	}
	else
		throw_error(E_ADDRESS_NOT_FOUND);
}


void* NetAddress::generateAddressStruct(unsigned int port) const {
	struct sockaddr_in* addr = new struct sockaddr_in();
	std::memset(addr, 0, sizeof(struct sockaddr_in));
	addr->sin_family = AF_INET;
	addr->sin_port = htons(port);
	memcpy(&addr->sin_addr, _address, _size);
	return addr;
}


