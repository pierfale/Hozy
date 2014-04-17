#ifndef ERROR_CODE_HPP
#define ERROR_CODE_HPP

enum ErrorCode {
    //General erros
    E_THREAD_CREATE_FAILED,
    E_THREAD_JOIN_FAILED,

    //Network errors
    E_ADDRESS_NOT_FOUND,
    E_HOST_NOT_FOUND,
    E_SOCKET_CREATE_FAILED,
    E_INIT_WINSOCK_FAILED
};

#endif
