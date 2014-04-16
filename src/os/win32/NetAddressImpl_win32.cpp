#include "os/win32/NetAddressImpl_win32.hpp"

#ifdef WIN32

NetAddressImpl_win32 NetAddressImpl_win32::getByIP(const std::string& ip) {
    NetAddressImpl_win32 addr;
    addr._address.sin_addr.s_addr = inet_addr(ip.c_str());
    addr._address.sin_family = AF_INET;

    if(addr._address.sin_addr.s_addr == INADDR_NONE)
        fatal_error("Erreur a gerer");

    return addr;
}

NetAddressImpl_win32 NetAddressImpl_win32::getByName(const std::string& name) {
    struct hostent* host;

    host = gethostbyname(name.c_str());

    if(host == nullptr) {
        fatal_error("Erreur a gerer");
    }

    NetAddressImpl_win32 addr;
    memcpy(&addr._address.sin_addr, host->h_addr_list[0], host->h_length);
    addr._address.sin_family = AF_INET;
    return addr;
}

NetAddressImpl_win32 NetAddressImpl_win32::getLocalAdress() {
    NetAddressImpl_win32 addr;

    return addr;
}

#endif
