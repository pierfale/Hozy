#ifndef MODULE_VIEW_HPP
#define MODULE_VIEW_HPP

#include <vector>
#include "tool/Singleton.hpp"
#include "Module.hpp"

class ViewEvent {


};

class NetworkEvent;

class ModuleView : public Module, public Singleton<ModuleView> {

    friend class Singleton<ModuleView>;

public:
    void run();
    static void network_event_handler(const NetworkEvent& event);

protected:
    virtual void initialize() {
        std::cout << "init ModuleView" << std::endl;
    }

    virtual void destroy() {
        std::cout << "destroy ModuleView" << std::endl;
    }

private:
    ModuleView();
};

#endif
