#include "data/server/Client.hpp"

Client::Client(SocketTcp* socket) : _tcp_socket(socket) {

}

Client::Client(const Client& client __attribute__((unused))) : _tcp_socket(nullptr) {

}

Client::~Client() {
    delete _tcp_socket;
}

bool Client::authenticate(std::string pseudo, std::string password) {
    std::cout << pseudo << ";" << password << std::endl;
    return false;
}

SocketTcp* Client::get_tcp_socket() {
    return _tcp_socket;
}

std::string Client::get_pseudo() {
    return "undefined";
}

Client& Client::operator=(const Client& origin __attribute__((unused))) {
    return *this;
}
