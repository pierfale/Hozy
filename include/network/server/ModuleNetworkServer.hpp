#ifndef MODULE_NETWORK_SERVER_HPP
#define MODULE_NETWORK_SERVER_HPP

#ifdef WIN32
#include <winsock2.h>
#endif

#include "tool/Singleton.hpp"
#include "network/ServerTcp.hpp"
#include "Module.hpp"
#include "tool/error/ErrorManager.hpp"
#include "tool/log/Log.hpp"


class ModuleNetworkServer : public Module, public Singleton<ModuleNetworkServer> {

	friend class Singleton<ModuleNetworkServer>;

public:
	void run();

protected:

	virtual void initialize();
	virtual void destroy();

private:
	ModuleNetworkServer();

	ServerTcp _socket;

};

#endif
