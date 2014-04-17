#ifndef NET_ADDRESS_HPP
#define NET_ADDRESS_HPP

#define IPV4_SIZE 4
#define IPV6_SIZE 16

#include <string>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include "tool/error/ErrorManager.hpp"


class NetAddress {

public:
    static NetAddress getByIP(const std::string& ip);
    static NetAddress getByName(const std::string& name);
    static NetAddress getLocalAdress();

};

class NetV4Adress : public NetAddress {

    NetV4Adress(uint8_t* address);

private:
    uint8_t _address[IPV4_SIZE];
};

class NetV6Adress : public NetAddress {

    NetV6Adress(uint8_t* address);

private:
    uint8_t _address[IPV6_SIZE];
};

#endif
