#include "network/server/ClientSelector.hpp"
#include "data/server/Client.hpp"
#include "tool/Thread.hpp"

ClientSelector::ClientSelector(const std::vector<Client*>& client_list, Mutex& mutex) : _client_list(client_list), _mutex(mutex) {

}

unsigned int ClientSelector::next() {



    int err;

	struct timeval time;
	time.tv_sec = 0;
	time.tv_usec = 10;

    while(true) {
		if( _client_list.size() == 0) {
			Thread::sleep(10);
			continue;
		}

        fd_set list_fd;
        FD_ZERO(&list_fd);

        _mutex.lock();

        unsigned int n = _client_list.size();
        int max = 0;
        for(unsigned int i=0; i<n; i++) {
			if(_client_list.at(i)->get_tcp_socket()->_socket > max)
				max = _client_list.at(i)->get_tcp_socket()->_socket;
            FD_SET(_client_list.at(i)->get_tcp_socket()->_socket, &list_fd);
        }

        _mutex.unlock();

		std::cout << "test..1" << std::endl;
		err = select(max+1, &list_fd, NULL, NULL, &time);
        std::cout << "test..2 => " << err << std::endl;
        _mutex.lock();

        if(err == SOCKET_ERROR) {
            throw_error_os(E_SELECTOR_NEXT_FAILED, ERR_NO);
        }
        else if(err > 0) {
            for(unsigned int i=0; i<n && i<_client_list.size(); i++) {
				if(FD_ISSET(_client_list.at(i)->get_tcp_socket()->_socket, &list_fd)) {
					 _mutex.unlock();
                    return i;
				}
            }
        }

        _mutex.unlock();

    }
}
