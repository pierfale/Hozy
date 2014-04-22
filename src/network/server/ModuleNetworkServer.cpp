#include "network/server/ModuleNetworkServer.hpp"

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
        std::cout << "REGISTER" << std::endl;
    UnauthenticatedClient::register_singleton("UnauthenticatedClient", 100);
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
			Log::ldebug << "Client connected !" << std::endl;

            UnauthenticatedClient::add(new Client(client));

			Packet packet;
            client->receive(packet);
			std::string msg;
			packet >> msg;
			Log::ldebug << "client say " << msg << std::endl;
		}
	}
	catch(Exception const& e) {
		Log::lerr << std::string(e.what()) << std::endl;
	}
}
