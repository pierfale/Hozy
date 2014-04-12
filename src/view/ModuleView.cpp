#include "view/ModuleView.hpp"
#include "network/ModuleNetwork.hpp"

void ModuleView::network_event_handler(NetworkEvent* event) {
    std::cout << "Xaxa : " << event->_n << std::endl;
}

void ModuleView::run(void* argx) {
    std::cout << "Running" << std::endl;
}
