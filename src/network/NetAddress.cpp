#include "network/NetAddress.hpp"

NetAddress::NetAddress(NET_ADDRESS_IMPLEMENTATION impl) : _impl(impl) {

}

NetAddress NetAddress::getByIP(const std::string& ip) {
    NetAddress addr(NET_ADDRESS_IMPLEMENTATION::getByIP(ip));
    return addr;
}

NetAddress NetAddress::getByName(const std::string& name) {
    NetAddress addr(NET_ADDRESS_IMPLEMENTATION::getByName(name));
    return addr;
}

NetAddress NetAddress::getLocalAdress() {
    NetAddress addr(NET_ADDRESS_IMPLEMENTATION::getLocalAdress());
    return addr;
}
