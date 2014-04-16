#ifndef NET_ADDRESS_HPP
#define NET_ADDRESS_HPP

#ifdef WIN32
#include "os/win32/NetAddressImpl_win32.hpp"
#define NET_ADDRESS_IMPLEMENTATION NetAddressImpl_win32
#elif defined UNIX
#include "os/unix/NetAddressImpl_unix.hpp"
#define NET_ADDRESS_IMPLEMENTATION NetAddressImpl_unix
#else
#error "This Operating system is unssuported"
#endif

#include <string>

class NetAddress {

public:
    static NetAddress getByIP(const std::string& ip);
    static NetAddress getByName(const std::string& name);
    static NetAddress getLocalAdress();

private:
    NetAddress(NET_ADDRESS_IMPLEMENTATION impl);
    NET_ADDRESS_IMPLEMENTATION& _impl;
};

#endif
