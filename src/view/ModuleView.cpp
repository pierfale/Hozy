#include "view/ModuleView.hpp"
#include "network/ModuleNetwork.hpp"

void ModuleView::network_event_handler(const NetworkEvent& event) {
    std::cout << "Xaxa : " << event._n << std::endl;
}

void ModuleView::run() {
    std::cout << "Running" << std::endl;
}
