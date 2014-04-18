#ifndef MODULE_NETWORK_HPP
#define MODULE_NETWORK_HPP

#ifdef WIN32
#include <winsock2.h>
#endif

#include "tool/Singleton.hpp"
#include "Module.hpp"
#include "tool/error/ErrorManager.hpp"

class NetworkEvent {

public:
    NetworkEvent() {

    }

};

class ModuleNetwork : public Module, public Singleton<ModuleNetwork> {

    friend class Singleton<ModuleNetwork>;

public:
    void run();

protected:
    ModuleNetwork(){}
    virtual void initialize();
    virtual void destroy();

};

#endif
