#ifndef NET_ADDRESS_HPP
#define NET_ADDRESS_HPP

#define IPV4_SIZE 4
#define IPV6_SIZE 16

#include <string>
#include <cstring>

#ifdef WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#elif defined UNIX
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#endif


#include "tool/error/ErrorManager.hpp"


class NetAddress {

	friend class SocketTcp;

public:
	NetAddress(const std::string& name);

	static NetAddress getLocalAdress();

private:
	void* generateAddressStruct(unsigned int port) const;
	std::size_t _size;
	uint8_t _address[IPV6_SIZE];
};

#endif
