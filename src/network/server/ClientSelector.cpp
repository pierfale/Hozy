#include "network/server/ClientSelector.hpp"
#include "data/server/Client.hpp"

ClientSelector::ClientSelector(const std::vector<Client*>& client_list, Mutex& mutex) : _client_list(client_list), _mutex(mutex) {

}

unsigned int ClientSelector::next() {

    int err;

    struct timeval time;
    time.tv_sec = 0;
    time.tv_usec = 10;

    while(true) {

        fd_set list_fd;
        FD_ZERO(&list_fd);

        _mutex.lock();

        unsigned int n = _client_list.size();
        for(unsigned int i=0; i<n; i++) {
            FD_SET(_client_list.at(i)->get_tcp_socket()->_socket, &list_fd);
        }

        _mutex.unlock();

        err = select(n, &list_fd, NULL, NULL, &time);

        _mutex.lock();

        if(err == SOCKET_ERROR) {
            throw_error_os(E_SELECTOR_NEXT_FAILED, ERR_NO);
        }
        else if(err > 0) {
            for(unsigned int i=0; i<n && i<_client_list.size(); i++) {
                if(FD_ISSET(_client_list.at(i)->get_tcp_socket()->_socket, &list_fd))
                    return i;
            }
        }

        _mutex.unlock();

    }
}
