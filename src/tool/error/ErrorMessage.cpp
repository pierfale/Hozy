#include "tool/error/ErrorMessage.hpp"

std::string get_error_message(ErrorCode error_code) {
    switch(error_code) {
            //general erros
        case E_THREAD_CREATE_FAILED:
        return "Creation of the thread failed";

            //Network errors
        case E_ADDRESS_NOT_FOUND:
        return "Address not found";
        default:
            break;

    }
    return "Undefined error code ("+ct::to_string((int)error_code)+")";
}
