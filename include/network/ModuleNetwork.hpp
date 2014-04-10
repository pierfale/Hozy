#ifndef MODULE_NETWORK_HPP
#define MODULE_NETWORK_HPP

#include "tool/Singleton.hpp"
#include "Module.hpp"

class NetworkEvent {


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
