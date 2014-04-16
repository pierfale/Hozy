#ifndef NET_ADDRESS_IMPLEMENT_WIN32_HPP
#define NET_ADDRESS_IMPLEMENT_WIN32_HPP

#ifdef WIN32

#include <winsock2.h>
#include <string>

#include "tool/log/Log.hpp"
#include "tool/error/ErrorManager.hpp"

class NetAddressImpl_win32 {
public:
    static NetAddressImpl_win32 getByIP(const std::string& ip);
    static NetAddressImpl_win32 getByName(const std::string& name);
    static NetAddressImpl_win32 getLocalAdress();

private:
    SOCKADDR_IN _address;

};

#endif

#endif
