#ifndef MODULE_NETWORK_HPP
#define MODULE_NETWORK_HPP

#include "tool/Singleton.hpp"
#include "Module.hpp"

class NetworkEvent {

public:
    NetworkEvent(int n) {
        _n = n;
    }
    int _n;

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
