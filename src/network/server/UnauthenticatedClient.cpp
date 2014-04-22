#include "network/server/UnauthenticatedClient.hpp"

UnauthenticatedClient::UnauthenticatedClient() : _list_client(), _mutex(), _selector(_list_client, _mutex) {

}

void UnauthenticatedClient::initialize() {
    Thread* thread = new Thread();
    thread->create(MemberFunction<UnauthenticatedClient, void>(instance(), &UnauthenticatedClient::run));
}

void UnauthenticatedClient::destroy() {

}

void UnauthenticatedClient::add(Client* client) {
    instance()->_mutex.lock();
    instance()->_list_client.push_back(client);
    instance()->_mutex.unlock();
}

void UnauthenticatedClient::run() {
    while(true) {
        int index = _selector.next();
        Client* client = _list_client.at(index);
        Packet packet;
        client->get_tcp_socket()->receive(packet);
        if(packet.get_type() == P_AUTHENTICATION) {


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
