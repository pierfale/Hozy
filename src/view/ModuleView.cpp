#include "view/ModuleView.hpp"
#include "network/ModuleNetwork.hpp"

ModuleView::ModuleView() {

}

void ModuleView::network_event_handler(const NetworkEvent& event) {
    std::cout << &event << std::endl;
}

void ModuleView::run() {
    std::cout << "Running : " << std::endl;
}
