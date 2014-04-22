#include "data/server/Client.hpp"

Client::Client(SocketTcp* socket) : _tcp_socket(socket) {

}

Client::Client(const Client& client __attribute__((unused))) : _tcp_socket(nullptr) {

}

Client::~Client() {
    delete _tcp_socket;
}

SocketTcp* Client::get_tcp_socket() {
    return _tcp_socket;
}

Client& Client::operator=(const Client& origin __attribute__((unused))) {
    return *this;
}
