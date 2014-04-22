#include "network/server/ModuleNetworkServer.hpp"
#include "network/server/UnauthenticatedClient.hpp"
#include "network/server/MenuClient.hpp"
#include "data/server/Client.hpp"

ModuleNetworkServer::ModuleNetworkServer() : _socket() {

}

void ModuleNetworkServer::initialize() {
#ifdef WIN32
	WSADATA wsa;
	int err = WSAStartup(MAKEWORD(2, 2), &wsa);
	if(err != 0) {
		throw_error_os(E_INIT_WINSOCK_FAILED, err);
	}
#endif
    UnauthenticatedClient::register_singleton("UnauthenticatedClient", 100);
    MenuClient::register_singleton("MenuClient", 100);
}

void ModuleNetworkServer::destroy() {
#ifdef WIN32
	WSACleanup();
#endif
}

void ModuleNetworkServer::run() {
	try {

		_socket.listen(50885);

        SocketTcp* client = new SocketTcp();

		Log::lout << "Listen on port 2342" << std::endl;
        while(_socket.accept(*client)) {
            UnauthenticatedClient::add(new Client(client));
		}
	}
	catch(Exception const& e) {
		Log::lerr << std::string(e.what()) << std::endl;
	}
}
