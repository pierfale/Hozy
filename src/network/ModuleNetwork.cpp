#include "network/ModuleNetwork.hpp"

void ModuleNetwork::initialize() {
#ifdef WIN32
    WSADATA wsa;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa);
    if(err != 0) {
        throw_error_os(E_INIT_WINSOCK_FAILED, err);
    }
#endif

}

void ModuleNetwork::destroy() {
#ifdef WIN32
    WSACleanup();
#endif
}

void ModuleNetwork::run() {

}
