#include "view/ModuleView.hpp"
#include "network/ModuleNetwork.hpp"

void ModuleView::network_event_handler(NetworkEvent* event) {
    std::cout << "Xaxa : " << event->_n << std::endl;
}
