#include "os/unix/NetAddressImpl_unix.hpp"

#ifdef UNIX

NetAddressImpl_unix NetAddressImpl_unix::getByIP(const std::string& ip) {
    NetAddressImpl_unix addr;
    addr._address.sin_addr.s_addr = inet_addr(ip.c_str());
    addr._address.sin_family = AF_INET;

    if(addr._address.sin_addr.s_addr == INADDR_NONE)
       throw_error(E_ADDRESS_NOT_FOUND);

    return addr;
}

NetAddressImpl_unix NetAddressImpl_unix::getByName(const std::string& name) {
    struct hostent* host;

    host = gethostbyname(name.c_str());

    if(host == nullptr) {
        throw_error(E_HOST_NOT_FOUND);
    }

    NetAddressImpl_unix addr;
    memcpy(&addr._address.sin_addr, host->h_addr_list[0], host->h_length);
    addr._address.sin_family = AF_INET;
    return addr;
}

NetAddressImpl_unix NetAddressImpl_unix::getLocalAdress() {
    NetAddressImpl_unix addr;

    return addr;
}

#endif
