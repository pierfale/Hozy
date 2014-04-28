#include "client/ConfigClient.hpp"

ConfigClient::ConfigClient() {

}

void ConfigClient::initialize() {
    load_config("client.conf");
}

void ConfigClient::destroy() {

}
