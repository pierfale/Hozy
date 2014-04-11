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

protected:
    ModuleNetwork(){}
    virtual void initialize() {
        std::cout << "init network" << std::endl;
    }

    virtual void destroy() {
        std::cout << "destroy network" << std::endl;
    }

};

#endif
