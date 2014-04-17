#include "network/SocketTcp.hpp"

SocketTcp::SocketTcp() {

}

void SocketTcp::connect(const NetAddress& address, unsigned int port) {
    impl.connect(address, port);
}
