#ifndef NET_ADDRESS_HPP
#define NET_ADDRESS_HPP

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
    enum AddressType {
        ADDRESS_TYPE_UNDEFINED,
        IPV4,
        IPV6
    };


	NetAddress(const std::string& name);
    NetAddress(const NetAddress& origin);

    ~NetAddress();

	static NetAddress getLocalAdress();
    struct sockaddr* address() const;
    AddressType type() const;

    std::string to_string() const;

    NetAddress& operator=(const NetAddress& origin);


private:
    struct sockaddr* _address;
    std::size_t _size;
    AddressType _type;
};

#endif
