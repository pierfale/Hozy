#include "network/server/ModuleNetworkServer.hpp"

ModuleNetworkServer::ModuleNetworkServer() {

}

void ModuleNetworkServer::initialize() {
#ifdef WIN32
	WSADATA wsa;
	int err = WSAStartup(MAKEWORD(2, 2), &wsa);
	if(err != 0) {
		throw_error_os(E_INIT_WINSOCK_FAILED, err);
	}
#endif

}

void ModuleNetworkServer::destroy() {
#ifdef WIN32
	WSACleanup();
#endif
}

void ModuleNetworkServer::run() {
	try {

		_socket.listen(2342);

		SocketTcp client;

		Log::ldebug << "Listen on port 2342" << std::endl;
		/*while(_socket.accept(client)) {

		}*/
	}
	catch(Exception const& e) {
		Log::lerr << std::string(e.what()) << std::endl;
	}
}
