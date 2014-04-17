#ifndef NET_ADDRESS_IMPLEMENT_UNIX_HPP
#define NET_ADDRESS_IMPLEMENT_UNIX_HPP

#ifdef UNIX

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

#include <string>

#include "tool/log/Log.hpp"
#include "tool/error/ErrorManager.hpp"

class NetAddressImpl_unix {

    friend class SocketTcpImpl_unix;
public:
    static NetAddressImpl_unix getByIP(const std::string& ip);
    static NetAddressImpl_unix getByName(const std::string& name);
    static NetAddressImpl_unix getLocalAdress();

private:
    struct sockaddr_in _address;


};

#endif

#endif
