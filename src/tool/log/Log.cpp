#include "tool/log/Log.hpp"

Log::OutStream Log::lout(LOG_INFO);
Log::OutStream Log::lwarning(LOG_WARNING);
Log::OutStream Log::lerr(LOG_ERROR | LOG_CRITICAL);
Log::OutStream Log::ldebug(LOG_DEBUG);

Log::Log() {

}

void Log::destroy() {
    lout.flush();
    lwarning.flush();
    lerr.flush();
    ldebug.flush();

    for(unsigned int i=0; i<instance()->_logs.size(); i++) {
        delete instance()->_logs[i];
    }
}

void Log::send(std::string message, int level) {
    for(unsigned int i=0; i<instance()->_logs.size(); i++) {
        if(instance()->_logs[i]->getLevel() & level)
            instance()->_logs[i]->send(message);
    }
}

void Log::add(AbstractLog* log) {
    instance()->_logs.push_back(log);
}
