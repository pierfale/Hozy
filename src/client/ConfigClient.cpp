#include "client/ConfigClient.hpp"

ConfigClient::ConfigClient() {

}

void ConfigClient::initialize() {
    load_config("client.conf");
	default_value();
}

void ConfigClient::destroy() {
	save_config("client.conf");
}

void ConfigClient::default_value() {
	set_if_not_exist("crash_report_path", "client_crash.log");
}
