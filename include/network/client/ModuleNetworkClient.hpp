#ifndef MODULE_NETWORK_CLIENT_HPP
#define MODULE_NETWORK_CLIENT_HPP

#ifdef WIN32
#include <winsock2.h>
#endif

#include "tool/Singleton.hpp"
#include "Module.hpp"
#include "tool/error/ErrorManager.hpp"
#include "network/SocketTcp.hpp"
#include "tool/log/Log.hpp"

class ModuleNetworkClient : public Module, public Singleton<ModuleNetworkClient> {

	friend class Singleton<ModuleNetworkClient>;

public:
    void run();

protected:
	ModuleNetworkClient();
    virtual void initialize();
    virtual void destroy();

};

#endif
