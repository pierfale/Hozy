#include "network/server/UnauthenticatedClient.hpp"
#include "Server.hpp"
#include "network/server/MenuClient.hpp"

UnauthenticatedClient::UnauthenticatedClient() : _list_client(), _mutex(), _selector(_list_client, _mutex) {

}

void UnauthenticatedClient::initialize() {
    Thread* thread = new Thread();
    thread->create(MemberFunction<UnauthenticatedClient, void>(instance(), &UnauthenticatedClient::run));
}

void UnauthenticatedClient::destroy() {
    for(unsigned int i=0; i<_list_client.size(); i++)
        delete _list_client.at(i);
}

void UnauthenticatedClient::add(Client* client) {
    instance()->_mutex.lock();
    Log::ldebug << "[Network] New connexion from " << client->get_tcp_socket()->get_address().to_string() << std::endl;
    instance()->_list_client.push_back(client);
    instance()->_mutex.unlock();
}

void UnauthenticatedClient::run() {
    try {
        while(Server::is_running()) {
            int index = _selector.next();
            Client* client = _list_client.at(index);
            Packet packet;
            client->get_tcp_socket()->receive(packet);
            if(packet.get_type() == P_AUTHENTICATION) {
                std::string pseudo, password;
                try {
                    packet >> pseudo >> password;
                    if(client->authenticate(pseudo, password)) {
                        MenuClient::add(client);
                        _list_client.erase(_list_client.begin()+index);
                    }

                }
                catch(Exception const& e) {
                    if(e.get_error_code() == E_PACKET_DATA || e.get_error_code() == E_PACKET_EMPTY) {
                        delete client;
                        _list_client.erase(_list_client.begin()+index);
                    }
                    else
                        Log::lerr << std::string(e.what()) << std::endl;
                }
            }
            else {
                /*
                 * Incorrect packet.
                 */
                delete client;
                _list_client.erase(_list_client.begin()+index);
            }
        }
    }
    catch(Exception const& e) {
        Log::lerr << std::string(e.what()) << std::endl;
    }
}
