#include "network/NetAddress.hpp"

NetAddress NetAddress::getByIP(const std::string& ip) {
    NetAddress addr;
   /* addr._address.sin_addr.s_addr = inet_addr(ip.c_str());
    addr._address.sin_family = AF_INET;

    if(addr._address.sin_addr.s_addr == INADDR_NONE)
       throw_error(E_ADDRESS_NOT_FOUND);
*/
    return addr;
}

NetAddress NetAddress::getByName(const std::string& name) {
    struct addrinfo* addr_info;
    struct addrinfo addr_info_conf;

    memset(&addr_info_conf, 0, sizeof(struct addrinfo));
    addr_info_conf.ai_family = AF_UNSPEC;

    if(getaddrinfo(name.c_str(), NULL, &addr_info_conf, &addr_info) != 0)
        throw_error(E_ADDRESS_NOT_FOUND);

    if(addr_info->ai_family == AF_INET) {
        NetV4Adress addr(addr_info->ai_addr);
        freeaddrinfo(addr_info);
        return addr;

    }
    else if(addr_info->ai_family == AF_INET6) {
        NetV6Adress addr(addr_info->ai_addr);
        freeaddrinfo(addr_info);
        return addr;
    }
    else
        throw_error(E_ADDRESS_NOT_FOUND);

}

NetAddress NetAddress::getLocalAdress() {
    NetAddress addr;

    return addr;
}

NetV4Adress::NetV4Adress(uint8_t* address) {
    std::copy(address, address+IPV4_SIZE, _address);
}


NetV6Adress::NetV6Adress(uint8_t* address) {
    std::copy(address, address+IPV6_SIZE, _address);
}


