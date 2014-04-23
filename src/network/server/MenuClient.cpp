#include "network/server/MenuClient.hpp"

MenuClient::MenuClient() : _list_client(), _mutex(), _selector(_list_client, _mutex) {

}

void MenuClient::initialize() {
    Thread* thread = new Thread();
    thread->create(MemberFunction<MenuClient, void>(instance(), &MenuClient::run));
}

void MenuClient::destroy() {
    for(unsigned int i=0; i<_list_client.size(); i++)
        delete _list_client.at(i);
}

void MenuClient::add(Client* client) {
    instance()->_mutex.lock();
    Log::ldebug << "[Network] Client authenticate with pseudo " << client->get_pseudo() << std::endl;
    instance()->_list_client.push_back(client);
    instance()->_mutex.unlock();
}

void MenuClient::run() {
    while(true) {
        int index = _selector.next();
        Client* client = _list_client.at(index);
        Packet packet;
        client->get_tcp_socket()->receive(packet);
    }
}
