#ifndef ERROR_CODE_HPP
#define ERROR_CODE_HPP

enum ErrorCode {
    //General erros
    E_THREAD_CREATE_FAILED,
	E_THREAD_DESTROY_FAILED,
    E_THREAD_JOIN_FAILED,

	E_MUTEX_CREATE_FAILED,
    E_MUTEX_DESTROY_FAILED,
	E_MUTEX_LOCK_FAILED,
	E_MUTEX_UNLOCK_FAILED,

    E_SLEEP_FAILED,

    E_SINGLETON_UNREGISTERED,

    E_OUT_OF_RANGE,

    //Network errors
    E_ADDRESS_NOT_FOUND,
    E_HOST_NOT_FOUND,
    E_SOCKET_CREATE_FAILED,
    E_SOCKET_CONNECT_FAILED,
	E_SOCKET_BIND_FAILED,
	E_SOCKET_LISTEN_FAILED,
	E_SOCKET_ACCEPT_FAILED,
    E_SOCKET_RECEIVE_FAILED,
	E_SOCKET_SEND_FAILED,
    E_SOCKET_CLOSED,
	E_SOCKET_DATA,

    E_PACKET_DATA,

    E_SELECTOR_NEXT_FAILED,

    E_PACKET_EMPTY,
    E_INIT_WINSOCK_FAILED
};

#endif
