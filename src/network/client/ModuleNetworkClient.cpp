#include "network/client/ModuleNetworkClient.hpp"

ModuleNetworkClient::ModuleNetworkClient() {

}

void ModuleNetworkClient::initialize() {
#ifdef WIN32
    WSADATA wsa;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa);
    if(err != 0) {
        throw_error_os(E_INIT_WINSOCK_FAILED, err);
    }
#endif

}

void ModuleNetworkClient::destroy() {
#ifdef WIN32
    WSACleanup();
#endif
}

void ModuleNetworkClient::run() {
    SocketTcp socket;
    socket.connect(NetAddress("127.0.0.1"),50885);

    Packet packet;
    std::string str("bonjour !");
    std::cout << packet.to_string() << std::endl;
    packet << str;

    socket.send(packet);
}
